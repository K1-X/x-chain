/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_DEV_RPC_ETHFACE_H_
#define JSONRPC_CPP_STUB_DEV_RPC_ETHFACE_H_

#include "ModularServer.h"

namespace dev {
    namespace rpc {
        class EthFace : public ServerInterface<EthFace>
        {
            public:
                EthFace()
                {
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_protocolVersion", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING,  NULL), &dev::rpc::EthFace::eth_protocolVersionI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_hashrate", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING,  NULL), &dev::rpc::EthFace::eth_hashrateI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_coinbase", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING,  NULL), &dev::rpc::EthFace::eth_coinbaseI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_mining", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN,  NULL), &dev::rpc::EthFace::eth_miningI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_gasPrice", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING,  NULL), &dev::rpc::EthFace::eth_gasPriceI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_accounts", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_ARRAY,  NULL), &dev::rpc::EthFace::eth_accountsI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_blockNumber", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING,  NULL), &dev::rpc::EthFace::eth_blockNumberI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getBalance", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getBalanceI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getStorageAt", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_STRING,"param3",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getStorageAtI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getStorageRoot", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getStorageRootI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getTransactionCount", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getTransactionCountI);
                    //this->bindAndAddMethod(jsonrpc::Procedure("eth_pendingTransactions", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING,  NULL), &dev::rpc::EthFace::eth_pendingTransactionsI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_pendingTransactions", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT,  NULL), &dev::rpc::EthFace::eth_pendingTransactionsI);
		    this->bindAndAddMethod(jsonrpc::Procedure("eth_getBlockTransactionCountByHash", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getBlockTransactionCountByHashI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getBlockTransactionCountByNumber", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getBlockTransactionCountByNumberI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getUncleCountByBlockHash", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getUncleCountByBlockHashI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getUncleCountByBlockNumber", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getUncleCountByBlockNumberI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getCode", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getCodeI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_sendTransaction", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_OBJECT, NULL), &dev::rpc::EthFace::eth_sendTransactionI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_call", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_OBJECT,"param2",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_callI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_flush", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN,  NULL), &dev::rpc::EthFace::eth_flushI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getBlockByHash", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_BOOLEAN, NULL), &dev::rpc::EthFace::eth_getBlockByHashI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getBlockByNumber", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_BOOLEAN, NULL), &dev::rpc::EthFace::eth_getBlockByNumberI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getTransactionByHash", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getTransactionByHashI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getTransactionByBlockHashAndIndex", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getTransactionByBlockHashAndIndexI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getTransactionByBlockNumberAndIndex", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getTransactionByBlockNumberAndIndexI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getTransactionReceipt", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getTransactionReceiptI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getUncleByBlockHashAndIndex", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getUncleByBlockHashAndIndexI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getUncleByBlockNumberAndIndex", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getUncleByBlockNumberAndIndexI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_newFilter", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_OBJECT, NULL), &dev::rpc::EthFace::eth_newFilterI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_newFilterEx", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_OBJECT, NULL), &dev::rpc::EthFace::eth_newFilterExI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_newBlockFilter", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING,  NULL), &dev::rpc::EthFace::eth_newBlockFilterI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_newPendingTransactionFilter", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING,  NULL), &dev::rpc::EthFace::eth_newPendingTransactionFilterI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_uninstallFilter", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_uninstallFilterI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getFilterChanges", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_ARRAY, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getFilterChangesI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getFilterChangesEx", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_ARRAY, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getFilterChangesExI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getFilterLogs", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_ARRAY, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getFilterLogsI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getFilterLogsEx", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_ARRAY, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_getFilterLogsExI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getLogs", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_ARRAY, "param1",jsonrpc::JSON_OBJECT, NULL), &dev::rpc::EthFace::eth_getLogsI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getLogsEx", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_ARRAY, "param1",jsonrpc::JSON_OBJECT, NULL), &dev::rpc::EthFace::eth_getLogsExI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_getWork", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_ARRAY,  NULL), &dev::rpc::EthFace::eth_getWorkI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_submitWork", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_STRING,"param3",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_submitWorkI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_submitHashrate", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_submitHashrateI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_register", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_registerI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_unregister", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_unregisterI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_fetchQueuedTransactions", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_ARRAY, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_fetchQueuedTransactionsI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_signTransaction", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_OBJECT, NULL), &dev::rpc::EthFace::eth_signTransactionI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_inspectTransaction", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_inspectTransactionI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_sendRawTransaction", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_sendRawTransactionI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_notePassword", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN, "param1",jsonrpc::JSON_STRING, NULL), &dev::rpc::EthFace::eth_notePasswordI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_syncing", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT,  NULL), &dev::rpc::EthFace::eth_syncingI);
                    this->bindAndAddMethod(jsonrpc::Procedure("eth_estimateGas", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_OBJECT, NULL), &dev::rpc::EthFace::eth_estimateGasI);
                }

                inline virtual void eth_protocolVersionI(const Json::Value &request, Json::Value &response)
                {
                    (void)request;
                    response = this->eth_protocolVersion();
                }
                inline virtual void eth_hashrateI(const Json::Value &request, Json::Value &response)
                {
                    (void)request;
                    response = this->eth_hashrate();
                }
                inline virtual void eth_coinbaseI(const Json::Value &request, Json::Value &response)
                {
                    (void)request;
                    response = this->eth_coinbase();
                }
                inline virtual void eth_miningI(const Json::Value &request, Json::Value &response)
                {
                    (void)request;
                    response = this->eth_mining();
                }
                inline virtual void eth_gasPriceI(const Json::Value &request, Json::Value &response)
                {
                    (void)request;
                    response = this->eth_gasPrice();
                }
                inline virtual void eth_accountsI(const Json::Value &request, Json::Value &response)
                {
                    (void)request;
                    response = this->eth_accounts();
                }
                inline virtual void eth_blockNumberI(const Json::Value &request, Json::Value &response)
                {
                    (void)request;
                    response = this->eth_blockNumber();
                }
                inline virtual void eth_getBalanceI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getBalance(request[0u].asString(), request[1u].asString());
                }
                inline virtual void eth_getStorageAtI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getStorageAt(request[0u].asString(), request[1u].asString(), request[2u].asString());
                }
                inline virtual void eth_getStorageRootI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getStorageRoot(request[0u].asString(), request[1u].asString());
                }
                inline virtual void eth_getTransactionCountI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getTransactionCount(request[0u].asString(), request[1u].asString());
                }
                inline virtual void eth_pendingTransactionsI(const Json::Value &request, Json::Value &response)
                {
                    (void)request;
                    response = this->eth_pendingTransactions();
                }
                inline virtual void eth_getBlockTransactionCountByHashI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getBlockTransactionCountByHash(request[0u].asString());
                }
                inline virtual void eth_getBlockTransactionCountByNumberI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getBlockTransactionCountByNumber(request[0u].asString());
                }
                inline virtual void eth_getUncleCountByBlockHashI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getUncleCountByBlockHash(request[0u].asString());
                }
                inline virtual void eth_getUncleCountByBlockNumberI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getUncleCountByBlockNumber(request[0u].asString());
                }
                inline virtual void eth_getCodeI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getCode(request[0u].asString(), request[1u].asString());
                }
                inline virtual void eth_sendTransactionI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_sendTransaction(request[0u]);
                }
                inline virtual void eth_callI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_call(request[0u], request[1u].asString());
                }
                inline virtual void eth_flushI(const Json::Value &request, Json::Value &response)
                {
                    (void)request;
                    response = this->eth_flush();
                }
                inline virtual void eth_getBlockByHashI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getBlockByHash(request[0u].asString(), request[1u].asBool());
                }
                inline virtual void eth_getBlockByNumberI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getBlockByNumber(request[0u].asString(), request[1u].asBool());
                }
                inline virtual void eth_getTransactionByHashI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getTransactionByHash(request[0u].asString());
                }
                inline virtual void eth_getTransactionByBlockHashAndIndexI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getTransactionByBlockHashAndIndex(request[0u].asString(), request[1u].asString());
                }
                inline virtual void eth_getTransactionByBlockNumberAndIndexI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getTransactionByBlockNumberAndIndex(request[0u].asString(), request[1u].asString());
                }
                inline virtual void eth_getTransactionReceiptI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getTransactionReceipt(request[0u].asString());
                }
                inline virtual void eth_getUncleByBlockHashAndIndexI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getUncleByBlockHashAndIndex(request[0u].asString(), request[1u].asString());
                }
                inline virtual void eth_getUncleByBlockNumberAndIndexI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getUncleByBlockNumberAndIndex(request[0u].asString(), request[1u].asString());
                }
                inline virtual void eth_newFilterI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_newFilter(request[0u]);
                }
                inline virtual void eth_newFilterExI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_newFilterEx(request[0u]);
                }
                inline virtual void eth_newBlockFilterI(const Json::Value &request, Json::Value &response)
                {
                    (void)request;
                    response = this->eth_newBlockFilter();
                }
                inline virtual void eth_newPendingTransactionFilterI(const Json::Value &request, Json::Value &response)
                {
                    (void)request;
                    response = this->eth_newPendingTransactionFilter();
                }
                inline virtual void eth_uninstallFilterI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_uninstallFilter(request[0u].asString());
                }
                inline virtual void eth_getFilterChangesI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getFilterChanges(request[0u].asString());
                }
                inline virtual void eth_getFilterChangesExI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getFilterChangesEx(request[0u].asString());
                }
                inline virtual void eth_getFilterLogsI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getFilterLogs(request[0u].asString());
                }
                inline virtual void eth_getFilterLogsExI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getFilterLogsEx(request[0u].asString());
                }
                inline virtual void eth_getLogsI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getLogs(request[0u]);
                }
                inline virtual void eth_getLogsExI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_getLogsEx(request[0u]);
                }
                inline virtual void eth_getWorkI(const Json::Value &request, Json::Value &response)
                {
                    (void)request;
                    response = this->eth_getWork();
                }
                inline virtual void eth_submitWorkI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_submitWork(request[0u].asString(), request[1u].asString(), request[2u].asString());
                }
                inline virtual void eth_submitHashrateI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_submitHashrate(request[0u].asString(), request[1u].asString());
                }
                inline virtual void eth_registerI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_register(request[0u].asString());
                }
                inline virtual void eth_unregisterI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_unregister(request[0u].asString());
                }
                inline virtual void eth_fetchQueuedTransactionsI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_fetchQueuedTransactions(request[0u].asString());
                }
                inline virtual void eth_signTransactionI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_signTransaction(request[0u]);
                }
                inline virtual void eth_inspectTransactionI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_inspectTransaction(request[0u].asString());
                }
                inline virtual void eth_sendRawTransactionI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_sendRawTransaction(request[0u].asString());
                }
                inline virtual void eth_notePasswordI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_notePassword(request[0u].asString());
                }
                inline virtual void eth_syncingI(const Json::Value &request, Json::Value &response)
                {
                    (void)request;
                    response = this->eth_syncing();
                }
                inline virtual void eth_estimateGasI(const Json::Value &request, Json::Value &response)
                {
                    response = this->eth_estimateGas(request[0u]);
                }
                virtual std::string eth_protocolVersion() = 0;
                virtual std::string eth_hashrate() = 0;
                virtual std::string eth_coinbase() = 0;
                virtual bool eth_mining() = 0;
                virtual std::string eth_gasPrice() = 0;
                virtual Json::Value eth_accounts() = 0;
                virtual std::string eth_blockNumber() = 0;
                virtual std::string eth_getBalance(const std::string& param1, const std::string& param2) = 0;
                virtual std::string eth_getStorageAt(const std::string& param1, const std::string& param2, const std::string& param3) = 0;
                virtual std::string eth_getStorageRoot(const std::string& param1, const std::string& param2) = 0;
                virtual std::string eth_getTransactionCount(const std::string& param1, const std::string& param2) = 0;
                //virtual std::string eth_pendingTransactions() = 0;
		virtual Json::Value eth_pendingTransactions() = 0;
                virtual Json::Value eth_getBlockTransactionCountByHash(const std::string& param1) = 0;
                virtual Json::Value eth_getBlockTransactionCountByNumber(const std::string& param1) = 0;
                virtual Json::Value eth_getUncleCountByBlockHash(const std::string& param1) = 0;
                virtual Json::Value eth_getUncleCountByBlockNumber(const std::string& param1) = 0;
                virtual std::string eth_getCode(const std::string& param1, const std::string& param2) = 0;
                virtual std::string eth_sendTransaction(const Json::Value& param1) = 0;
                virtual std::string eth_call(const Json::Value& param1, const std::string& param2) = 0;
                virtual bool eth_flush() = 0;
                virtual Json::Value eth_getBlockByHash(const std::string& param1, bool param2) = 0;
                virtual Json::Value eth_getBlockByNumber(const std::string& param1, bool param2) = 0;
                virtual Json::Value eth_getTransactionByHash(const std::string& param1) = 0;
                virtual Json::Value eth_getTransactionByBlockHashAndIndex(const std::string& param1, const std::string& param2) = 0;
                virtual Json::Value eth_getTransactionByBlockNumberAndIndex(const std::string& param1, const std::string& param2) = 0;
                virtual Json::Value eth_getTransactionReceipt(const std::string& param1) = 0;
                virtual Json::Value eth_getUncleByBlockHashAndIndex(const std::string& param1, const std::string& param2) = 0;
                virtual Json::Value eth_getUncleByBlockNumberAndIndex(const std::string& param1, const std::string& param2) = 0;
                virtual std::string eth_newFilter(const Json::Value& param1) = 0;
                virtual std::string eth_newFilterEx(const Json::Value& param1) = 0;
                virtual std::string eth_newBlockFilter() = 0;
                virtual std::string eth_newPendingTransactionFilter() = 0;
                virtual bool eth_uninstallFilter(const std::string& param1) = 0;
                virtual Json::Value eth_getFilterChanges(const std::string& param1) = 0;
                virtual Json::Value eth_getFilterChangesEx(const std::string& param1) = 0;
                virtual Json::Value eth_getFilterLogs(const std::string& param1) = 0;
                virtual Json::Value eth_getFilterLogsEx(const std::string& param1) = 0;
                virtual Json::Value eth_getLogs(const Json::Value& param1) = 0;
                virtual Json::Value eth_getLogsEx(const Json::Value& param1) = 0;
                virtual Json::Value eth_getWork() = 0;
                virtual bool eth_submitWork(const std::string& param1, const std::string& param2, const std::string& param3) = 0;
                virtual bool eth_submitHashrate(const std::string& param1, const std::string& param2) = 0;
                virtual std::string eth_register(const std::string& param1) = 0;
                virtual bool eth_unregister(const std::string& param1) = 0;
                virtual Json::Value eth_fetchQueuedTransactions(const std::string& param1) = 0;
                virtual std::string eth_signTransaction(const Json::Value& param1) = 0;
                virtual Json::Value eth_inspectTransaction(const std::string& param1) = 0;
                virtual std::string eth_sendRawTransaction(const std::string& param1) = 0;
                virtual bool eth_notePassword(const std::string& param1) = 0;
                virtual Json::Value eth_syncing() = 0;
                virtual std::string eth_estimateGas(const Json::Value& param1) = 0;
        };

    }
}
#endif //JSONRPC_CPP_STUB_DEV_RPC_ETHFACE_H_