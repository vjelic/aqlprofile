#include "core/pm4_factory.h"
#include "def/gfx9_def.h"
#include "pm4/gfx9_cmd_builder.h"
#include "pm4/pmc_builder.h"
#include "pm4/sqtt_builder.h"

namespace aql_profile {

class Gfx9Factory : public Pm4Factory {
 public:
  Gfx9Factory() : Pm4Factory(BlockMap(block_table, sizeof(block_table))) {}
  pm4_builder::CmdBuilder* getCmdBuilder();
  pm4_builder::PmcBuilder* getPmcBuilder();
  pm4_builder::SqttBuilder* getSqttBuilder();

 private:
  static const GpuBlockInfo* block_table[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];
};

// GFX9 block table
const GpuBlockInfo* Gfx9Factory::block_table[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER] = {
    &CpcCounterBlockInfo, &CpfCounterBlockInfo, &GdsCounterBlockInfo, &GrbmCounterBlockInfo,
    &GrbmSeCounterBlockInfo, &RmiCounterBlockInfo, &SpiCounterBlockInfo, &SqCounterBlockInfo,
    &SqCsCounterBlockInfo, NULL /*GFX8 SRBM*/, &SxCounterBlockInfo, &TaCounterBlockInfo,
    &TcaCounterBlockInfo, &TccCounterBlockInfo, &TcpCounterBlockInfo, &TdCounterBlockInfo,
    // MC blocks
    NULL /*GFX8 MC*/, NULL /*&AtcCounterBlockInfo*/, &AtcL2CounterBlockInfo, NULL /*&GceaCounterBlockInfo*/,
    &McVmL2CounterBlockInfo, NULL /*&RpbCounterBlockInfo*/,
};

Pm4Factory* Pm4Factory::Gfx9Create() {
  auto p = new Gfx9Factory;
  if (p == NULL) throw aql_profile_exc_msg("Gfx8Factory allocation failed");
  return p;
}

pm4_builder::CmdBuilder* Gfx9Factory::getCmdBuilder() {
  auto p = new pm4_builder::Gfx9CmdBuilder;
  if (p == NULL) throw aql_profile_exc_msg("CmdBuilder allocation failed");
  return p;
}

pm4_builder::PmcBuilder* Gfx9Factory::getPmcBuilder() {
  auto p = new pm4_builder::GpuPmcBuilder<pm4_builder::Gfx9CmdBuilder, gfx9_cntx_prim>;
  if (p == NULL) throw aql_profile_exc_msg("PmcBuilder mgr allocation failed");
  return p;
}

pm4_builder::SqttBuilder* Gfx9Factory::getSqttBuilder() {
  auto p = new pm4_builder::GpuSqttBuilder<pm4_builder::Gfx9CmdBuilder, gfx9_cntx_prim>;
  if (p == NULL) throw aql_profile_exc_msg("SqttBuilder mgr allocation failed");
  return p;
}

}  // namespace aql_profile
