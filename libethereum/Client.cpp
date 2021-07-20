#include "Client.h"
#include <chrono>
#include <memory>
#include <thread>
#include <boost/filesystem.hpp>
#include <libdevcore/Log.h>
#include <libp2p/Host.h>
#include "Defaults.h"
#include "Executive.h"
#include "EthereumHost.h"
#include "Block.h"
#include "TransactionQueue.h"
using namespace std;
using namespace dev;
using namespace dev::eth;
using namespace p2p;

static_assert(BOOST_VERSION == 106300, "Wrong boost headers version");

std::ostream& dev::eth::operator<<(std::ostream& _out, ActivityReport const& _r)
{
	_out << "Since " << toString(_r.since) << " (" << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _r.since).count();
	_out << "): " << _r.ticks << "ticks";
	return _out;
}

#if defined(_WIN32)
const char* ClientNote::name() { return EthTeal "^" EthBlue " i"; }
const char* ClientChat::name() { return EthTeal "^" EthWhite " o"; }
const char* ClientTrace::name() { return EthTeal "^" EthGray " O"; }
const char* ClientDetail::name() { return EthTeal "^" EthCoal " 0"; }
#else
const char* ClientNote::name() { return EthTeal "⧫" EthBlue " ℹ"; }
const char* ClientChat::name() { return EthTeal "⧫" EthWhite " ◌"; }
const char* ClientTrace::name() { return EthTeal "⧫" EthGray " ◎"; }
const char* ClientDetail::name() { return EthTeal "⧫" EthCoal " ●"; }
#endif

Client::Client(
	ChainParams const& _params,
	int _networkID,
	p2p::Host* _host,
	std::shared_ptr<GasPricer> _gpForAdoption,
	std::string const& _dbPath,
	WithExisting _forceAction,
	TransactionQueue::Limits const& _l
):
	ClientBase(_l),
	Worker("eth", 0),
	m_bc(_params, _dbPath, _forceAction, [](unsigned d, unsigned t){ std::cerr << "REVISING BLOCKCHAIN: Processed " << d << " of " << t << "...\r"; }),
	m_gp(_gpForAdoption ? _gpForAdoption : make_shared<TrivialGasPricer>()),
	m_preSeal(chainParams().accountStartNonce),
	m_postSeal(chainParams().accountStartNonce),
	m_working(chainParams().accountStartNonce)
{
	init(_host, _dbPath, _forceAction, _networkID);
}

Client::~Client()
{
	stopWorking();
}

void Client::init(p2p::Host* _extNet, std::string const& _dbPath, WithExisting _forceAction, u256 _networkId)
{
	DEV_TIMED_FUNCTION_ABOVE(500);

	// Cannot be opened until after blockchain is open, since BlockChain may upgrade the database.
	// TODO: consider returning the upgrade mechanism here. will delaying the opening of the blockchain database
	// until after the construction.
	m_stateDB = State::openDB(_dbPath, bc().genesisHash(), _forceAction);
	// LAZY. TODO: move genesis state construction/commiting to stateDB openning and have this just take the root from the genesis block.
	m_preSeal = bc().genesisBlock(m_stateDB);
	m_postSeal = m_preSeal;

	m_bq.setChain(bc());

	m_lastGetWork = std::chrono::system_clock::now() - chrono::seconds(30);
	m_tqReady = m_tq.onReady([=](){ this->onTransactionQueueReady(); });	// TODO: should read m_tq->onReady(thisThread, syncTransactionQueue);
	m_tqReplaced = m_tq.onReplaced([=](h256 const&){ m_needStateReset = true; });
	m_bqReady = m_bq.onReady([=](){ this->onBlockQueueReady(); });			// TODO: should read m_bq->onReady(thisThread, syncBlockQueue);
	m_bq.setOnBad([=](Exception& ex){ this->onBadBlock(ex); });
	bc().setOnBad([=](Exception& ex){ this->onBadBlock(ex); });
	bc().setOnBlockImport([=](BlockHeader const& _info){
		if (auto h = m_host.lock())
			h->onBlockImported(_info);
	});

	if (_forceAction == WithExisting::Rescue)
		bc().rescue(m_stateDB);

	m_gp->update(bc());

	auto host = _extNet->registerCapability(make_shared<EthereumHost>(bc(), m_stateDB, m_tq, m_bq, _networkId));
	m_host = host;

	_extNet->addCapability(host, EthereumHost::staticName(), EthereumHost::c_oldProtocolVersion); //TODO: remove this once v61+ protocol is common


	if (_dbPath.size())
		Defaults::setDBPath(_dbPath);
	doWork(false);
	startWorking();
}

ImportResult Client::queueBlock(bytes const& _block, bool _isSafe)
{
	if (m_bq.status().verified + m_bq.status().verifying + m_bq.status().unverified > 10000)
		this_thread::sleep_for(std::chrono::milliseconds(500));
	return m_bq.import(&_block, _isSafe);
}

tuple<ImportRoute, bool, unsigned> Client::syncQueue(unsigned _max)
{
	stopWorking();
	return bc().sync(m_bq, m_stateDB, _max);
}

void Client::onBadBlock(Exception& _ex) const
{
	// BAD BLOCK!!!
	bytes const* block = boost::get_error_info<errinfo_block>(_ex);
	if (!block)
	{
		cwarn << "ODD: onBadBlock called but exception (" << _ex.what() << ") has no block in it.";
		cwarn << boost::diagnostic_information(_ex);
		return;
	}

	badBlock(*block, _ex.what());
}

void Client::callQueuedFunctions()
{
	while (true)
	{
		function<void()> f;
		DEV_WRITE_GUARDED(x_functionQueue)
			if (!m_functionQueue.empty())
			{
				f = m_functionQueue.front();
				m_functionQueue.pop();
			}
		if (f)
			f();
		else
			break;
	}
}

u256 Client::networkId() const
{
	if (auto h = m_host.lock())
		return h->networkId();
	return 0;
}

void Client::setNetworkId(u256 const& _n)
{
	if (auto h = m_host.lock())
		h->setNetworkId(_n);
}

bool Client::isSyncing() const
{
	if (auto h = m_host.lock())
		return h->isSyncing();
	return false;
}

bool Client::isMajorSyncing() const
{
	if (auto h = m_host.lock())
	{
		SyncState state = h->status().state;
		return (state != SyncState::Idle && state != SyncState::NewBlocks) || h->bq().items().first > 10;
	}
	return false;
}

void Client::startedWorking()
{
	// Synchronise the state according to the head of the block chain.
	// TODO: currently it contains keys for *all* blocks. Make it remove old ones.
	clog(ClientTrace) << "startedWorking()";

	DEV_WRITE_GUARDED(x_preSeal)
		m_preSeal.sync(bc());
	DEV_READ_GUARDED(x_preSeal)
	{
		DEV_WRITE_GUARDED(x_working)
			m_working = m_preSeal;
		DEV_WRITE_GUARDED(x_postSeal)
			m_postSeal = m_preSeal;
	}
}

void Client::doneWorking()
{
	// Synchronise the state according to the head of the block chain.
	// TODO: currently it contains keys for *all* blocks. Make it remove old ones.
	DEV_WRITE_GUARDED(x_preSeal)
		m_preSeal.sync(bc());
	DEV_READ_GUARDED(x_preSeal)
	{
		DEV_WRITE_GUARDED(x_working)
			m_working = m_preSeal;
		DEV_WRITE_GUARDED(x_postSeal)
			m_postSeal = m_preSeal;
	}
}

void Client::reopenChain(WithExisting _we)
{
	reopenChain(bc().chainParams(), _we);
}

void Client::reopenChain(ChainParams const& _p, WithExisting _we)
{
	bool wasSealing = wouldSeal();
	if (wasSealing)
		stopSealing();
	stopWorking();

	m_tq.clear();
	m_bq.clear();
	sealEngine()->cancelGeneration();

	{
		WriteGuard l(x_postSeal);
		WriteGuard l2(x_preSeal);
		WriteGuard l3(x_working);

		auto author = m_preSeal.author();	// backup and restore author.
		m_preSeal = Block(chainParams().accountStartNonce);
		m_postSeal = Block(chainParams().accountStartNonce);
		m_working = Block(chainParams().accountStartNonce);

		m_stateDB = OverlayDB();
		bc().reopen(_p, _we);
		m_stateDB = State::openDB(Defaults::dbPath(), bc().genesisHash(), _we);

		m_preSeal = bc().genesisBlock(m_stateDB);
		m_preSeal.setAuthor(author);
		m_postSeal = m_preSeal;
		m_working = Block(chainParams().accountStartNonce);
	}

	if (auto h = m_host.lock())
		h->reset();

	startedWorking();
	doWork();

	startWorking();
	if (wasSealing)
		startSealing();
}

void Client::executeInMainThread(function<void ()> const& _function)
{
	DEV_WRITE_GUARDED(x_functionQueue)
		m_functionQueue.push(_function);
	m_signalled.notify_all();
}

void Client::clearPending()
{
	DEV_WRITE_GUARDED(x_postSeal)
	{
		if (!m_postSeal.pending().size())
			return;
		m_tq.clear();
		DEV_READ_GUARDED(x_preSeal)
			m_postSeal = m_preSeal;
	}

	startSealing();
	h256Hash changeds;
	noteChanged(changeds);
}

template <class S, class T>
static S& filtersStreamOut(S& _out, T const& _fs)
{
	_out << "{";
	unsigned i = 0;
	for (h256 const& f: _fs)
	{
		_out << (i++ ? ", " : "");
		if (f == PendingChangedFilter)
			_out << LogTag::Special << "pending";
		else if (f == ChainChangedFilter)
			_out << LogTag::Special << "chain";
		else
			_out << f;
	}
	_out << "}";
	return _out;
}

void Client::appendFromNewPending(TransactionReceipt const& _receipt, h256Hash& io_changed, h256 _sha3)
{
	Guard l(x_filtersWatches);
	io_changed.insert(PendingChangedFilter);
	m_specialFilters.at(PendingChangedFilter).push_back(_sha3);
	for (pair<h256 const, InstalledFilter>& i: m_filters)
	{
		// acceptable number.
		auto m = i.second.filter.matches(_receipt);
		if (m.size())
		{
			// filter catches them
			for (LogEntry const& l: m)
				i.second.changes.push_back(LocalisedLogEntry(l));
			io_changed.insert(i.first);
		}
	}
}

void Client::appendFromBlock(h256 const& _block, BlockPolarity _polarity, h256Hash& io_changed)
{
	// TODO: more precise check on whether the txs match.
	auto receipts = bc().receipts(_block).receipts;

	Guard l(x_filtersWatches);
	io_changed.insert(ChainChangedFilter);
	m_specialFilters.at(ChainChangedFilter).push_back(_block);
	for (pair<h256 const, InstalledFilter>& i: m_filters)
	{
		// acceptable number & looks like block may contain a matching log entry.
		for (size_t j = 0; j < receipts.size(); j++)
		{
			auto tr = receipts[j];
			auto m = i.second.filter.matches(tr);
			if (m.size())
			{
				auto transactionHash = transaction(_block, j).sha3();
				// filter catches them
				for (LogEntry const& l: m)
					i.second.changes.push_back(LocalisedLogEntry(l, _block, (BlockNumber)bc().number(_block), transactionHash, j, 0, _polarity));
				io_changed.insert(i.first);
			}
		}
	}
}

ExecutionResult Client::call(Address _dest, bytes const& _data, u256 _gas, u256 _value, u256 _gasPrice, Address const& _from)
{
	ExecutionResult ret;
	try
	{
		Block temp(chainParams().accountStartNonce);
		clog(ClientDetail) << "Nonce at " << _dest << " pre:" << m_preSeal.transactionsFrom(_dest) << " post:" << m_postSeal.transactionsFrom(_dest);
		DEV_READ_GUARDED(x_postSeal)
			temp = m_postSeal;
		temp.mutableState().addBalance(_from, _value + _gasPrice * _gas);
		Executive e(temp);
		e.setResultRecipient(ret);
		if (!e.call(_dest, _from, _value, _gasPrice, &_data, _gas))
			e.go();
		e.finalize();
	}
	catch (...)
	{
		cwarn << "Client::call failed: " << boost::current_exception_diagnostic_information();
	}
	return ret;
}

unsigned static const c_syncMin = 1;
unsigned static const c_syncMax = 1000;
double static const c_targetDuration = 1;

void Client::syncBlockQueue()
{
//	cdebug << "syncBlockQueue()";

	ImportRoute ir;
	unsigned count;
	Timer t;
	tie(ir, m_syncBlockQueue, count) = bc().sync(m_bq, m_stateDB, m_syncAmount);
	double elapsed = t.elapsed();

	if (count)
	{
		clog(ClientNote) << count << "blocks imported in" << unsigned(elapsed * 1000) << "ms (" << (count / elapsed) << "blocks/s) in #" << bc().number();
	}

	if (elapsed > c_targetDuration * 1.1 && count > c_syncMin)
		m_syncAmount = max(c_syncMin, count * 9 / 10);
	else if (count == m_syncAmount && elapsed < c_targetDuration * 0.9 && m_syncAmount < c_syncMax)
		m_syncAmount = min(c_syncMax, m_syncAmount * 11 / 10 + 1);
	if (ir.liveBlocks.empty())
		return;
	onChainChanged(ir);
}
