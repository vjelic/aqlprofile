#include "core/pm4_factory.h"
#include "def/gfx12_def.h"
#include "pm4/gfx12_cmd_builder.h"
#include "pm4/pmc_builder.h"
#include "pm4/sqtt_builder.h"

namespace aql_profile {

// Gfx12 factory class
class Gfx12Factory : public Pm4Factory {
 public:
  explicit Gfx12Factory(const AgentInfo* agent_info) :
    Pm4Factory(BlockInfoMap(block_table_, sizeof(block_table_)))
  {
    Init(agent_info);
  }
  Gfx12Factory(const GpuBlockInfo** table, const uint32_t& size, const AgentInfo* agent_info) :
    Pm4Factory(BlockInfoMap(table, size))
  {
    Init(agent_info);
  }
  bool IsGFX12() const override { return true; }

 protected:
  void ConstructBuilders(const AgentInfo* agent_info);
  void ConstructTable(const AgentInfo* agent_info);
  void Init(const AgentInfo* agent_info) {
    agent_info_ = agent_info;
    ConstructBuilders(agent_info);
    ConstructTable(agent_info);
  }
  const GpuBlockInfo* block_table_[LastCounterBlockId + 1]{};
};

void Gfx12Factory::ConstructBuilders(const AgentInfo* agent_info) {
  Pm4Factory::cmd_builder_ = new pm4_builder::Gfx12CmdBuilder;
  if (Pm4Factory::cmd_builder_ == NULL) throw aql_profile_exc_msg("CmdBuilder allocation failed");

  // Mark and set the mode
  if (Pm4Factory::IsConcurrent()) {
    Pm4Factory::pmc_builder_ =
      new pm4_builder::GpuPmcBuilder<pm4_builder::Gfx12CmdBuilder, gfx12_cntx_prim, true>(agent_info);
  } else {
    Pm4Factory::pmc_builder_ =
      new pm4_builder::GpuPmcBuilder<pm4_builder::Gfx12CmdBuilder, gfx12_cntx_prim, false>(agent_info);
  }
  if (Pm4Factory::pmc_builder_ == NULL) throw aql_profile_exc_msg("PmcBuilder allocation failed");

  Pm4Factory::spm_builder_ =
      new pm4_builder::GpuSpmBuilder<pm4_builder::Gfx12CmdBuilder, gfx12_cntx_prim>;
  if (Pm4Factory::spm_builder_ == NULL) throw aql_profile_exc_msg("SpmBuilder allocation failed");

  Pm4Factory::sqtt_builder_ =
      new pm4_builder::GpuSqttBuilder<pm4_builder::Gfx12CmdBuilder, gfx12_cntx_prim>(agent_info);
  if (Pm4Factory::sqtt_builder_ == NULL) throw aql_profile_exc_msg("SqttBuilder allocation failed");
}

void Gfx12Factory::ConstructTable(const AgentInfo* agent_info) {
  block_table_[__BLOCK_ID(GRBM)] = &GrbmCounterBlockInfo;
  block_table_[__BLOCK_ID(CPC)]  = &CpcCounterBlockInfo;
  block_table_[__BLOCK_ID(CPF)]  = &CpfCounterBlockInfo;
  block_table_[__BLOCK_ID(GCR)]  = &GcrCounterBlockInfo;
  block_table_[__BLOCK_ID(GL2A)] = &Gl2aCounterBlockInfo;
  block_table_[__BLOCK_ID(GL2C)] = &Gl2cCounterBlockInfo;
  block_table_[__BLOCK_ID(SPI)]  = &SpiCounterBlockInfo;
  block_table_[__BLOCK_ID(SQ)]   = &SqgCounterBlockInfo;
  block_table_[__BLOCK_ID(GL1A)] = &Gl1aCounterBlockInfo;
  block_table_[__BLOCK_ID(GL1C)] = &Gl1cCounterBlockInfo;
  block_table_[__BLOCK_ID(SX)]   = &SxCounterBlockInfo;
  block_table_[__BLOCK_ID(TA)]   = &TaCounterBlockInfo;
  block_table_[__BLOCK_ID(TD)]   = &TdCounterBlockInfo;
  block_table_[__BLOCK_ID(TCP)]  = &TcpCounterBlockInfo;
  block_table_[__BLOCK_ID(CHA)]  = &ChaCounterBlockInfo;
  block_table_[__BLOCK_ID(CHC)]  = &ChcCounterBlockInfo;
}

// Pm4Factory create mathods
Pm4Factory* Pm4Factory::Gfx12Create(const AgentInfo* agent_info) {
  auto p = new Gfx12Factory(agent_info);
  if (p == NULL) throw aql_profile_exc_msg("Gfx12Factory allocation failed");
  return p;
}

}  // namespace aql_profile
