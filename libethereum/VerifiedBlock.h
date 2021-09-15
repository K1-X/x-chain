#include <libdevcore/Common.h>
#include <libethcore/BlockHeader.h>

#pragma once

namespace dev
{
namespace eth
{

class Transaction;

/// @brief Verified block info, does not hold block data, but a reference instead
struct VerifiedBlockRef
{
	bytesConstRef block; 					///<  Block data reference
	BlockHeader info;							///< Prepopulated block info
	std::vector<Transaction> transactions;	///< Verified list of block transactions
};

}
}
