#if !defined(ETH_EMSCRIPTEN)

#include <thread>
#include <libdevcore/db.h>
#include <libdevcore/Common.h>
#include "OverlayDB.h"
using namespace std;
using namespace dev;

namespace dev
{

h256 const EmptyTrie = sha3(rlp(""));

OverlayDB::~OverlayDB()
{
	if (m_db.use_count() == 1 && m_db.get())
		ctrace << "Closing state DB";
}


class WriteBatchNoter: public ldb::WriteBatch::Handler
{
	virtual void Put(ldb::Slice const& _key, ldb::Slice const& _value) { cnote << "Put" << toHex(bytesConstRef(_key)) << "=>" << toHex(bytesConstRef(_value)); }
	virtual void Delete(ldb::Slice const& _key) { cnote << "Delete" << toHex(bytesConstRef(_key)); }
};

void OverlayDB::commit()
{
	if (m_db)
	{
		ldb::WriteBatch batch;
//		cnote << "Committing nodes to disk DB:";
#if DEV_GUARDED_DB
		DEV_READ_GUARDED(x_this)
#endif
		{
			for (auto const& i: m_main)
			{
				if (i.second.second)
					batch.Put(ldb::Slice((char const*)i.first.data(), i.first.size), ldb::Slice(i.second.first.data(), i.second.first.size()));
//				cnote << i.first << "#" << m_main[i.first].second;
			}
			for (auto const& i: m_aux)
				if (i.second.second)
				{
					bytes b = i.first.asBytes();
					b.push_back(255);	// for aux
					batch.Put(bytesConstRef(&b), bytesConstRef(&i.second.first));
				}
		}

		for (unsigned i = 0; i < 10; ++i)
		{
			ldb::Status o = m_db->Write(m_writeOptions, &batch);
			if (o.ok())
				break;
			if (i == 9)
			{
				cwarn << "Fail writing to state database. Bombing out.";
				exit(-1);
			}
			cwarn << "Error writing to state database: " << o.ToString();
			WriteBatchNoter n;
			batch.Iterate(&n);
			cwarn << "Sleeping for" << (i + 1) << "seconds, then retrying.";
			this_thread::sleep_for(chrono::seconds(i + 1));
		}
#if DEV_GUARDED_DB
		DEV_WRITE_GUARDED(x_this)
#endif
		{
			m_aux.clear();
			m_main.clear();
		}
	}
}

}

#endif // ETH_EMSCRIPTEN
