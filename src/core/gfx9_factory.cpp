#include "core/gfx9_factory.h"
#include "def/gfx9_def.h"
#include "pm4/gfx9_cmd_builder.h"
#include "pm4/pmc_builder.h"
#include "pm4/sqtt_builder.h"

namespace aql_profile {

// Gfx factory init
void Gfx9Factory::Init(const AgentInfo* agent_info) {
  Pm4Factory::cmd_builder_ = new pm4_builder::Gfx9CmdBuilder;
  if (Pm4Factory::cmd_builder_ == NULL) throw aql_profile_exc_msg("CmdBuilder allocation failed");

  // Mark and set the mode
  if (Pm4Factory::IsConcurrent()) {
    Pm4Factory::pmc_builder_ =
        new pm4_builder::GpuPmcBuilder<pm4_builder::Gfx9CmdBuilder, gfx9_cntx_prim, true>(
            agent_info);
  } else {
    Pm4Factory::pmc_builder_ =
        new pm4_builder::GpuPmcBuilder<pm4_builder::Gfx9CmdBuilder, gfx9_cntx_prim, false>(
            agent_info);
  }
  if (Pm4Factory::pmc_builder_ == NULL) throw aql_profile_exc_msg("PmcBuilder allocation failed");

  Pm4Factory::spm_builder_ =
      new pm4_builder::GpuSpmBuilder<pm4_builder::Gfx9CmdBuilder, gfx9_cntx_prim>;
  if (Pm4Factory::spm_builder_ == NULL) throw aql_profile_exc_msg("SpmBuilder allocation failed");

  Pm4Factory::sqtt_builder_ =
      new pm4_builder::GpuSqttBuilder<pm4_builder::Gfx9CmdBuilder, gfx9_cntx_prim>(agent_info);
  if (Pm4Factory::sqtt_builder_ == NULL) throw aql_profile_exc_msg("SqttBuilder allocation failed");

  agent_info_ = agent_info;
}

// GFX9 block table
const GpuBlockInfo* Gfx9Factory::block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER] = {
    &CpcCounterBlockInfo, &CpfCounterBlockInfo, &GdsCounterBlockInfo, &GrbmCounterBlockInfo,
    &GrbmSeCounterBlockInfo, &SpiCounterBlockInfo, &SqCounterBlockInfo, &SqCsCounterBlockInfo,
    NULL /*GFX? SRBM*/, &SxCounterBlockInfo, &TaCounterBlockInfo, &TcaCounterBlockInfo,
    &TccCounterBlockInfo, &TcpCounterBlockInfo, &TdCounterBlockInfo,
    // MC blocks
    NULL /*MC_ARB*/, NULL /*MC_HUB*/, NULL /*MC_MCBVM*/, NULL /*MC_SEQ*/, &McVmL2CounterBlockInfo,
    NULL /*MC_XBAR*/, &AtcCounterBlockInfo, &AtcL2CounterBlockInfo, &GceaCounterBlockInfo,
    &RpbCounterBlockInfo,
    // System blocks
    &SdmaCounterBlockInfo, NULL/*GL1A*/, NULL/*GL1C*/, NULL/*GL2A*/, NULL/*GL2C*/, NULL/*GCR*/, NULL/*GUS*/,
    &UmcCounterBlockInfo};

// Pm4Factory create mathods
Pm4Factory* Pm4Factory::Gfx9Create(const AgentInfo* agent_info) {
  auto p = new Gfx9Factory(agent_info);
  if (p == NULL) throw aql_profile_exc_msg("Gfx9Factory allocation failed");
  return p;
}

}  // namespace aql_profile
