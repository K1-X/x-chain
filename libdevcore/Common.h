#pragma once
fdef _M_IX86
#pragma warning(disable:4244)
#endif

#if _MSC_VER && _MSC_VER < 1900
#define _ALLOW_KEYWORD_MACROS
#define noexcept throw()
#endif

#ifdef __INTEL_COMPILER
#pragma warning(disable:3682) //call through incomplete class
#endif

#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <set>
#include <unordered_set>
#include <functional>
#include <string>
#include <chrono>
#include <sys/time.h>
#pragma warning(push)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <boost/multiprecision/cpp_int.hpp>
#pragma warning(pop)
#pragma GCC diagnostic pop
#include "vector_ref.h"

// CryptoPP defines byte in the global namespace, so must we.
using byte = uint8_t;

// Quote a given token stream to turn it into a string.
#define DEV_QUOTED_HELPER(s) #s
#define DEV_QUOTED(s) DEV_QUOTED_HELPER(s)

#define DEV_IGNORE_EXCEPTIONS(X) try { X; } catch (...) {}

#define DEV_IF_THROWS(X) try{X;}catch(...)

namespace dev
{

extern char const* Version;

static const std::string EmptyString;

// Binary data types.
using bytes = std::vector<byte>;
using bytesRef = vector_ref<byte>;
using bytesConstRef = vector_ref<byte const>;

template <class T>
class secure_vector
{
public:
	secure_vector() {}
	secure_vector(secure_vector<T> const& /*_c*/) = default;  // See https://github.com/ethereum/libweb3core/pull/44
	explicit secure_vector(size_t _size): m_data(_size) {}
	explicit secure_vector(size_t _size, T _item): m_data(_size, _item) {}
	explicit secure_vector(std::vector<T> const& _c): m_data(_c) {}
	explicit secure_vector(vector_ref<T> _c): m_data(_c.data(), _c.data() + _c.size()) {}
	explicit secure_vector(vector_ref<const T> _c): m_data(_c.data(), _c.data() + _c.size()) {}
	~secure_vector() { ref().cleanse(); }

	secure_vector<T>& operator=(secure_vector<T> const& _c)
	{
		if (&_c == this)
			return *this;

		ref().cleanse();
		m_data = _c.m_data;
		return *this;
	}
	std::vector<T>& writable() { clear(); return m_data; }
	std::vector<T> const& makeInsecure() const { return m_data; }

	void clear() { ref().cleanse(); }

	vector_ref<T> ref() { return vector_ref<T>(&m_data); }
	vector_ref<T const> ref() const { return vector_ref<T const>(&m_data); }

	size_t size() const { return m_data.size(); }
	bool empty() const { return m_data.empty(); }

	void swap(secure_vector<T>& io_other) { m_data.swap(io_other.m_data); }

private:
	std::vector<T> m_data;
};

using bytesSec = secure_vector<byte>;

// Numeric types.
using bigint = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<>>;
using u64 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<64, 64, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>>;
using u128 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<128, 128, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>>;
using u256 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<256, 256, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>>;
using s256 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<256, 256, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>>;
using u160 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<160, 160, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>>;
using s160 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<160, 160, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>>;
using u512 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<512, 512, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>>;
using s512 =  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<512, 512, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>>;
using u256s = std::vector<u256>;
using u160s = std::vector<u160>;
using u256Set = std::set<u256>;
using u160Set = std::set<u160>;

// Map types.
using StringMap = std::map<std::string, std::string>;
using BytesMap = std::map<bytes, bytes>;
using u256Map = std::map<u256, u256>;
using HexMap = std::map<bytes, bytes>;

// Hash types.
using StringHashMap = std::unordered_map<std::string, std::string>;
using u256HashMap = std::unordered_map<u256, u256>;

// String types.
using strings = std::vector<std::string>;

// Fixed-length string types.
using string32 = std::array<char, 32>;
static const string32 ZeroString32 = {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};

// Null/Invalid values for convenience.
static const bytes NullBytes;
static const std::map<u256, u256> EmptyMapU256U256;
extern const u256 Invalid256;

/// Interprets @a _u as a two's complement signed number and returns the resulting s256.
inline s256 u2s(u256 _u)
{
	static const bigint c_end = bigint(1) << 256;
	if (boost::multiprecision::bit_test(_u, 255))
		return s256(-(c_end - _u));
	else
		return s256(_u);
}

/// @returns the two's complement signed representation of the signed number _u.
inline u256 s2u(s256 _u)
{
	static const bigint c_end = bigint(1) << 256;
    if (_u >= 0)
		return u256(_u);
    else
		return u256(c_end + _u);
}

/// Converts given int to a string and appends one of a series of units according to its size.
std::string inUnits(bigint const& _b, strings const& _units);

/// @returns the smallest n >= 0 such that (1 << n) >= _x
inline unsigned int toLog2(u256 _x)
{
	unsigned ret;
	for (ret = 0; _x >>= 1; ++ret) {}
	return ret;
}

template <size_t n> inline u256 exp10()
{
	return exp10<n - 1>() * u256(10);
}

template <> inline u256 exp10<0>()
{
	return u256(1);
}

/// @returns the absolute distance between _a and _b.
template <class N>
inline N diff(N const& _a, N const& _b)
{
	return std::max(_a, _b) - std::min(_a, _b);
}

/// RAII utility class whose destructor calls a given function.
class ScopeGuard
{
public:
	ScopeGuard(std::function<void(void)> _f): m_f(_f) {}
	~ScopeGuard() { m_f(); }

private:
	std::function<void(void)> m_f;
};

/// Inheritable for classes that have invariants.
class HasInvariants
{
public:
	/// Reimplement to specify the invariants.
	virtual bool invariants() const = 0;
};

/// RAII checker for invariant assertions.
class InvariantChecker
{
public:
	InvariantChecker(HasInvariants* _this, char const* _fn, char const* _file, int _line): m_this(_this), m_function(_fn), m_file(_file), m_line(_line) { checkInvariants(_this, _fn , _file, _line, true); }
	~InvariantChecker() { checkInvariants(m_this, m_function, m_file, m_line, false); }
	/// Check invariants are met, throw if not.
	static void checkInvariants(HasInvariants const* _this, char const* _fn, char const* _file, int line, bool _pre);

private:
	HasInvariants const* m_this;
	char const* m_function;
	char const* m_file;
	int m_line;
};

/// Scope guard for invariant check in a class derived from HasInvariants.
#if ETH_DEBUG
#define DEV_INVARIANT_CHECK ::dev::InvariantChecker __dev_invariantCheck(this, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__)
#define DEV_INVARIANT_CHECK_HERE ::dev::InvariantChecker::checkInvariants(this, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__, true)
#else
#define DEV_INVARIANT_CHECK (void)0;
#define DEV_INVARIANT_CHECK_HERE (void)0;
#endif

/// Simple scope-based timer helper.
class TimerHelper
{
public:
	TimerHelper(std::string const& _id, unsigned _msReportWhenGreater = 0): m_t(std::chrono::high_resolution_clock::now()), m_id(_id), m_ms(_msReportWhenGreater) {}
	~TimerHelper();

private:
	std::chrono::high_resolution_clock::time_point m_t;
	std::string m_id;
	unsigned m_ms;
};
}
