#include "core/pm4_factory.h"
#include "def/gfx8_def.h"
#include "pm4/gfx8_cmd_builder.h"
#include "pm4/pmc_builder.h"
#include "pm4/sqtt_builder.h"

namespace aql_profile {

class Gfx8Factory : public Pm4Factory {
 public:
  Gfx8Factory() : Pm4Factory(BlockMap(block_table_, sizeof(block_table_))) {}
  pm4_builder::CmdBuilder* GetCmdBuilder();
  pm4_builder::PmcBuilder* GetPmcBuilder();
  pm4_builder::SqttBuilder* GetSqttBuilder();

 private:
  static const GpuBlockInfo* block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];
};

// GFX8 block table
const GpuBlockInfo* Gfx8Factory::block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER] = {
    &CpcCounterBlockInfo, &CpfCounterBlockInfo, &GdsCounterBlockInfo, &GrbmCounterBlockInfo,
    &GrbmSeCounterBlockInfo, &SpiCounterBlockInfo, &SqCounterBlockInfo, &SqCsCounterBlockInfo,
    &SrbmCounterBlockInfo, &SxCounterBlockInfo, &TaCounterBlockInfo, &TcaCounterBlockInfo,
    &TccCounterBlockInfo, &TcpCounterBlockInfo, &TdCounterBlockInfo,
    // MC blocks
    &McArbCounterBlockInfo, &McHubCounterBlockInfo, &McMcbvmCounterBlockInfo,
    &McSeqCounterBlockInfo, &McVmL2CounterBlockInfo, &McXbarCounterBlockInfo, NULL /*GFX9 ATC*/,
    NULL /*GFX9 ATC_L2*/, NULL /*GFX9 GCEA*/, NULL /*GFX9 RPB*/,
};

Pm4Factory* Pm4Factory::Gfx8Create() {
  auto p = new Gfx8Factory;
  if (p == NULL) throw aql_profile_exc_msg("Gfx8Factory allocation failed");
  return p;
}

pm4_builder::CmdBuilder* Gfx8Factory::GetCmdBuilder() {
  auto p = new pm4_builder::Gfx8CmdBuilder;
  if (p == NULL) throw aql_profile_exc_msg("CmdBuilder allocation failed");
  return p;
}

pm4_builder::PmcBuilder* Gfx8Factory::GetPmcBuilder() {
  auto p = new pm4_builder::GpuPmcBuilder<pm4_builder::Gfx8CmdBuilder, gfx8_cntx_prim>;
  if (p == NULL) throw aql_profile_exc_msg("PmcBuilder allocation failed");
  return p;
}

pm4_builder::SqttBuilder* Gfx8Factory::GetSqttBuilder() {
  auto p = new pm4_builder::GpuSqttBuilder<pm4_builder::Gfx8CmdBuilder, gfx8_cntx_prim>;
  if (p == NULL) throw aql_profile_exc_msg("SqttBuilder allocation failed");
  return p;
}

}  // namespace aql_profile
