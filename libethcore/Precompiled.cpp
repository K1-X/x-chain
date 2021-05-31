#include "Precompiled.h"
#include <libdevcore/Log.h>
#include <libdevcore/SHA3.h>
#include <libdevcrypto/Hash.h>
#include <libdevcrypto/Common.h>
#include <libethcore/Common.h>
using namespace std;
using namespace dev;
using namespace dev::eth;

PrecompiledRegistrar* PrecompiledRegistrar::s_this = nullptr;

PrecompiledExecutor const& PrecompiledRegistrar::executor(std::string const& _name)
{
	if (!get()->m_execs.count(_name))
		BOOST_THROW_EXCEPTION(ExecutorNotFound());
	return get()->m_execs[_name];
}

PrecompiledPricer const& PrecompiledRegistrar::pricer(std::string const& _name)
{
	if (!get()->m_pricers.count(_name))
		BOOST_THROW_EXCEPTION(PricerNotFound());
	return get()->m_pricers[_name];
}

namespace
{

ETH_REGISTER_PRECOMPILED(ecrecover)(bytesConstRef _in)
{
	struct
	{
		h256 hash;
		h256 v;
		h256 r;
		h256 s;
	} in;

	memcpy(&in, _in.data(), min(_in.size(), sizeof(in)));

	h256 ret;
	u256 v = (u256)in.v;
	if (v >= 27 && v <= 28)
	{
		SignatureStruct sig(in.r, in.s, (byte)((int)v - 27));
		if (sig.isValid())
		{
			try
			{
				if (Public rec = recover(sig, in.hash))
				{
					ret = dev::sha3(rec);
					memset(ret.data(), 0, 12);
					return {true, ret.asBytes()};
				}
			}
			catch (...) {}
		}
	}
	return {true, {}};
}

ETH_REGISTER_PRECOMPILED(sha256)(bytesConstRef _in)
{
	return {true, dev::sha256(_in).asBytes()};
}

ETH_REGISTER_PRECOMPILED(ripemd160)(bytesConstRef _in)
{
	return {true, h256(dev::ripemd160(_in), h256::AlignRight).asBytes()};
}

ETH_REGISTER_PRECOMPILED(identity)(bytesConstRef _in)
{
	return {true, _in.toBytes()};
}

// Parse _count bytes of _in starting with _begin offset as big endian int.
// If there's not enough bytes in _in, consider it infinitely right-padded with zeroes.
bigint parseBigEndianRightPadded(bytesConstRef _in, size_t _begin, size_t _count)
{
	if (_begin > _in.count())
		return 0;

	// crop _in, not going beyond its size
	bytesConstRef cropped = _in.cropped(_begin, min(_count, _in.count() - _begin));

	bigint ret = fromBigEndian<bigint>(cropped);
	// shift as if we had right-padding zeroes
	ret <<= 8 * (_count - cropped.count());
	
	return ret;
}

ETH_REGISTER_PRECOMPILED(modexp)(bytesConstRef _in)
{
	size_t const baseLength(parseBigEndianRightPadded(_in, 0, 32));
	size_t const expLength(parseBigEndianRightPadded(_in, 32, 32));
	size_t const modLength(parseBigEndianRightPadded(_in, 64, 32));

	bigint const base(parseBigEndianRightPadded(_in, 96, baseLength));
	bigint const exp(parseBigEndianRightPadded(_in, 96 + baseLength, expLength));
	bigint const mod(parseBigEndianRightPadded(_in, 96 + baseLength + expLength, modLength));

	bigint const result = mod != 0 ? boost::multiprecision::powm(base, exp, mod) : bigint{0};
	
	bytes ret(modLength); 
	toBigEndian(result, ret);

	return {true, ret};
}

ETH_REGISTER_PRECOMPILED_PRICER(modexp)(bytesConstRef _in)
{
	bigint const baseLength(parseBigEndianRightPadded(_in, 0, 32));
	bigint const expLength(parseBigEndianRightPadded(_in, 32, 32));
	bigint const modLength(parseBigEndianRightPadded(_in, 64, 32));

	bigint const maxLength = max(modLength, baseLength);

	return maxLength * maxLength * max<bigint>(expLength, 1) / 20;
}
}

