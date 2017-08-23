#include "core/pm4_factory.h"
#include "def/gfx9_def.h"
#include "pm4/gfx9_cmd_builder.h"
#include "pm4/pmc_builder.h"
#include "pm4/sqtt_builder.h"

namespace aql_profile {

class Gfx9Factory : public Pm4Factory {
 public:
  Gfx9Factory() : Pm4Factory(BlockMap(block_table_, sizeof(block_table_))) {}
  pm4_builder::CmdBuilder* GetCmdBuilder();
  pm4_builder::PmcBuilder* GetPmcBuilder();
  pm4_builder::SqttBuilder* GetSqttBuilder();

 private:
  static const GpuBlockInfo* block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];
};

// GFX9 block table
const GpuBlockInfo* Gfx9Factory::block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER] = {
    &CpcCounterBlockInfo, &CpfCounterBlockInfo, &GdsCounterBlockInfo, &GrbmCounterBlockInfo,
    &GrbmSeCounterBlockInfo, &RmiCounterBlockInfo, &SpiCounterBlockInfo, &SqCounterBlockInfo,
    &SqCsCounterBlockInfo, NULL /*GFX8 SRBM*/, &SxCounterBlockInfo, &TaCounterBlockInfo,
    &TcaCounterBlockInfo, &TccCounterBlockInfo, &TcpCounterBlockInfo, &TdCounterBlockInfo,
    // MC blocks
    NULL /*MC_ARB*/, NULL /*MC_HUB*/, NULL /*MC_MCBVM*/, NULL /*MC_SEQ*/, &McVmL2CounterBlockInfo,
    NULL /*MC_XBAR*/, &AtcCounterBlockInfo, &AtcL2CounterBlockInfo, &GceaCounterBlockInfo,
    &RpbCounterBlockInfo,
};

Pm4Factory* Pm4Factory::Gfx9Create() {
  auto p = new Gfx9Factory;
  if (p == NULL) throw aql_profile_exc_msg("Gfx8Factory allocation failed");
  return p;
}

pm4_builder::CmdBuilder* Gfx9Factory::GetCmdBuilder() {
  auto p = new pm4_builder::Gfx9CmdBuilder;
  if (p == NULL) throw aql_profile_exc_msg("CmdBuilder allocation failed");
  return p;
}

pm4_builder::PmcBuilder* Gfx9Factory::GetPmcBuilder() {
  auto p = new pm4_builder::GpuPmcBuilder<pm4_builder::Gfx9CmdBuilder, gfx9_cntx_prim>;
  if (p == NULL) throw aql_profile_exc_msg("PmcBuilder mgr allocation failed");
  return p;
}

pm4_builder::SqttBuilder* Gfx9Factory::GetSqttBuilder() {
  auto p = new pm4_builder::GpuSqttBuilder<pm4_builder::Gfx9CmdBuilder, gfx9_cntx_prim>;
  if (p == NULL) throw aql_profile_exc_msg("SqttBuilder mgr allocation failed");
  return p;
}

}  // namespace aql_profile
