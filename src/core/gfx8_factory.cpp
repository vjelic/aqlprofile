#include "core/pm4_factory.h"
#include "def/gfx8_def.h"
#include "pm4/gfx8_cmd_builder.h"
#include "pm4/pmc_builder.h"
#include "pm4/sqtt_builder.h"

namespace aql_profile {

// Gfx8 factory class
class Gfx8Factory : public Pm4Factory {
 public:
  Gfx8Factory() : Pm4Factory(BlockInfoMap(block_table_, sizeof(block_table_))) { Init(); }
  Gfx8Factory(const GpuBlockInfo** table, const uint32_t& size)
      : Pm4Factory(BlockInfoMap(table, size)) {
    Init();
  }

 protected:
  void Init();
  static const GpuBlockInfo* block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];
};

// Gfx8 factory init
void Gfx8Factory::Init() {
  Pm4Factory::cmd_builder_ = new pm4_builder::Gfx8CmdBuilder;
  if (Pm4Factory::cmd_builder_ == NULL) throw aql_profile_exc_msg("CmdBuilder allocation failed");

  Pm4Factory::pmc_builder_ =
      new pm4_builder::GpuPmcBuilder<pm4_builder::Gfx8CmdBuilder, gfx8_cntx_prim>;
  if (Pm4Factory::pmc_builder_ == NULL) throw aql_profile_exc_msg("PmcBuilder allocation failed");

  Pm4Factory::spm_builder_ =
      new pm4_builder::GpuSpmBuilder<pm4_builder::Gfx8CmdBuilder, gfx8_cntx_prim>;
  if (Pm4Factory::spm_builder_ == NULL) throw aql_profile_exc_msg("SpmBuilder allocation failed");

  Pm4Factory::sqtt_builder_ =
      new pm4_builder::GpuSqttBuilder<pm4_builder::Gfx8CmdBuilder, gfx8_cntx_prim>;
  if (Pm4Factory::sqtt_builder_ == NULL) throw aql_profile_exc_msg("SqttBuilder allocation failed");
}

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
    // System blocks
    &Sdma0CounterBlockInfo, &Sdma1CounterBlockInfo,
};

// Fiji factory class
class FijiFactory : public Gfx8Factory {
 public:
  FijiFactory() : Gfx8Factory(block_table_, sizeof(block_table_)) {
    for (unsigned i = 0; i < HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER; ++i) {
      block_table_[i] = Gfx8Factory::block_table_[i];
    }
    block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCSEQ] = &McSeqHbmCounterBlockInfo;
  }

 protected:
  static const GpuBlockInfo* block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];
};

const GpuBlockInfo* FijiFactory::block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER] = {};

// Pm4Factory create mathods
Pm4Factory* Pm4Factory::Gfx8Create() {
  auto p = new Gfx8Factory;
  if (p == NULL) throw aql_profile_exc_msg("Gfx8Factory allocation failed");
  return p;
}

Pm4Factory* Pm4Factory::FijiCreate() {
  auto p = new FijiFactory;
  if (p == NULL) throw aql_profile_exc_msg("FijiFactory allocation failed");
  return p;
}

}  // namespace aql_profile
