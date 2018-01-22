#include "core/pm4_factory.h"
#include "def/gfx9_def.h"
#include "pm4/gfx9_cmd_builder.h"
#include "pm4/pmc_builder.h"
#include "pm4/sqtt_builder.h"

namespace aql_profile {

// Gfx9 factory class
class Gfx9Factory : public Pm4Factory {
 public:
  Gfx9Factory() : Pm4Factory(BlockInfoMap(block_table_, sizeof(block_table_))) { Init(); }

 private:
  void Init();
  static const GpuBlockInfo* block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];
};

// Gfx factory init
void Gfx9Factory::Init() {
  Pm4Factory::cmd_builder_ = new pm4_builder::Gfx9CmdBuilder;
  if (Pm4Factory::cmd_builder_ == NULL) throw aql_profile_exc_msg("CmdBuilder allocation failed");

  Pm4Factory::pmc_builder_ = new pm4_builder::GpuPmcBuilder<pm4_builder::Gfx9CmdBuilder, gfx9_cntx_prim>;
  if (Pm4Factory::pmc_builder_ == NULL) throw aql_profile_exc_msg("PmcBuilder allocation failed");

  Pm4Factory::sqtt_builder_ = new pm4_builder::GpuSqttBuilder<pm4_builder::Gfx9CmdBuilder, gfx9_cntx_prim>;
  if (Pm4Factory::sqtt_builder_ == NULL) throw aql_profile_exc_msg("SqttBuilder allocation failed");
}

// GFX9 block table
const GpuBlockInfo* Gfx9Factory::block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER] = {
    &CpcCounterBlockInfo, &CpfCounterBlockInfo, &GdsCounterBlockInfo, &GrbmCounterBlockInfo,
    &GrbmSeCounterBlockInfo, &SpiCounterBlockInfo, &SqCounterBlockInfo, &SqCsCounterBlockInfo,
    NULL /*GFX8 SRBM*/, &SxCounterBlockInfo, &TaCounterBlockInfo, &TcaCounterBlockInfo,
    &TccCounterBlockInfo, &TcpCounterBlockInfo, &TdCounterBlockInfo,
    // MC blocks
    NULL /*MC_ARB*/, NULL /*MC_HUB*/, NULL /*MC_MCBVM*/, NULL /*MC_SEQ*/, &McVmL2CounterBlockInfo,
    NULL /*MC_XBAR*/, &AtcCounterBlockInfo, &AtcL2CounterBlockInfo, &GceaCounterBlockInfo,
    &RpbCounterBlockInfo,
};

// Pm4Factory create mathods
Pm4Factory* Pm4Factory::Gfx9Create() {
  auto p = new Gfx9Factory;
  if (p == NULL) throw aql_profile_exc_msg("Gfx9Factory allocation failed");
  return p;
}

}  // namespace aql_profile
