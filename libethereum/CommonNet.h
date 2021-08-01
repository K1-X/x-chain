#pragma once

#include <string>
#include <chrono>
#include <libdevcore/Common.h>
#include <libdevcore/Log.h>

namespace dev
{

class OverlayDB;

namespace eth
{

#if ETH_DEBUG
static const unsigned c_maxHeaders = 2048;		///< Maximum number of hashes BlockHashes will ever send.
static const unsigned c_maxHeadersAsk = 2048;	///< Maximum number of hashes GetBlockHashes will ever ask for.
static const unsigned c_maxBlocks = 128;		///< Maximum number of blocks Blocks will ever send.
static const unsigned c_maxBlocksAsk = 128;		///< Maximum number of blocks we ask to receive in Blocks (when using GetChain).
static const unsigned c_maxPayload = 262144;	///< Maximum size of packet for us to send.
#else
static const unsigned c_maxHeaders = 2048;		///< Maximum number of hashes BlockHashes will ever send.
static const unsigned c_maxHeadersAsk = 2048;	///< Maximum number of hashes GetBlockHashes will ever ask for.
static const unsigned c_maxBlocks = 128;		///< Maximum number of blocks Blocks will ever send.
static const unsigned c_maxBlocksAsk = 128;		///< Maximum number of blocks we ask to receive in Blocks (when using GetChain).
static const unsigned c_maxPayload = 262144;	///< Maximum size of packet for us to send.
#endif
static const unsigned c_maxNodes = c_maxBlocks; ///< Maximum number of nodes will ever send.
static const unsigned c_maxReceipts = c_maxBlocks; ///< Maximum number of receipts will ever send.

class BlockChain;
class TransactionQueue;
class EthereumHost;
class EthereumPeer;

}
}