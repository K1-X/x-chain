/*
	This file is part of cpp-ethereum.

	cpp-ethereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-ethereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file Ethash.h
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 *
 * A proof of work algorithm.
 */

#pragma once

#include <libethcore/SealEngine.h>
#include <libethereum/GenericFarm.h>
#include "EthashProofOfWork.h"

namespace dev
{

namespace eth
{

class Ethash: public SealEngineBase
{
public:
	Ethash();

	std::string name() const override { return "Ethash"; }
	unsigned revision() const override { return 1; }
	unsigned sealFields() const override { return 2; }
	bytes sealRLP() const override { return rlp(h256()) + rlp(Nonce()); }


        StringHashMap jsInfo(BlockHeader const& _bi) const override;
	void verify(Strictness _s, BlockHeader const& _bi, BlockHeader const& _parent, bytesConstRef _block) const override;
	void verifyTransaction(ImportRequirements::value _ir, TransactionBase const& _t, EnvInfo const& _env) const override;
	void populateFromParent(BlockHeader& _bi, BlockHeader const& _parent) const override;
   
       strings sealers() const override;
	std::string sealer() const override { return m_sealer; }
	void setSealer(std::string const& _sealer) override { m_sealer = _sealer; }
	void cancelGeneration() override { m_farm.stop(); }
	void generateSeal(BlockHeader const& _bi, bytes const& _block_data = bytes()) override;
	bool shouldSeal(Interface* _i) override;

}
}
