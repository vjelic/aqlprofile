#include "core/pm4_factory.h"
#include "def/gfx9_def.h"
#include "pm4/gfx9_cmd_builder.h"
#include "pm4/pmc_builder.h"
#include "pm4/sqtt_builder.h"

namespace aql_profile {

// Gfx9 factory class
class Gfx9Factory : public Pm4Factory {
 public:
  explicit Gfx9Factory(uint32_t se_number) :
    Pm4Factory(BlockInfoMap(block_table_, sizeof(block_table_)))
  {
    Init(se_number);
  }
  Gfx9Factory(const GpuBlockInfo** table, const uint32_t& size, uint32_t se_number) :
    Pm4Factory(BlockInfoMap(table, size))
  {
    Init(se_number);
  }

 protected:
  void Init(uint32_t se_number);
  static const GpuBlockInfo* block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];
};

// Gfx factory init
void Gfx9Factory::Init(uint32_t se_number) {
  Pm4Factory::cmd_builder_ = new pm4_builder::Gfx9CmdBuilder;
  if (Pm4Factory::cmd_builder_ == NULL) throw aql_profile_exc_msg("CmdBuilder allocation failed");

  Pm4Factory::pmc_builder_ =
    new pm4_builder::GpuPmcBuilder<pm4_builder::Gfx9CmdBuilder, gfx9_cntx_prim>(se_number);
  if (Pm4Factory::pmc_builder_ == NULL) throw aql_profile_exc_msg("PmcBuilder allocation failed");

  Pm4Factory::spm_builder_ =
      new pm4_builder::GpuSpmBuilder<pm4_builder::Gfx9CmdBuilder, gfx9_cntx_prim>;
  if (Pm4Factory::spm_builder_ == NULL) throw aql_profile_exc_msg("SpmBuilder allocation failed");

  Pm4Factory::sqtt_builder_ =
      new pm4_builder::GpuSqttBuilder<pm4_builder::Gfx9CmdBuilder, gfx9_cntx_prim>;
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
    // System blocks
    &Sdma0CounterBlockInfo, &Sdma1CounterBlockInfo,
};

// Fiji factory class
class Mi100Factory : public Gfx9Factory {
 public:
  explicit Mi100Factory(uint32_t se_number) : Gfx9Factory(block_table_, sizeof(block_table_), se_number) {
    for (unsigned i = 0; i < HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER; ++i) {
      const GpuBlockInfo* base_table_ptr = Gfx9Factory::block_table_[i];
      if (base_table_ptr == NULL) continue;
      GpuBlockInfo* block_info = new GpuBlockInfo(*base_table_ptr);
      block_table_[i] = block_info;

      // overerite block info for any update from gfx9 to mi100
      switch (block_info->id) {
        case SqCounterBlockId:
          block_info->event_id_max = 303;
          break;
        case TcpCounterBlockId:
          block_info->event_id_max = 87;
          break;
        case TccCounterBlockId:
          block_info->instance_count = 32;
          block_info->event_id_max = 295;
          break;
        case TcaCounterBlockId:
          block_info->instance_count = 32;
          block_info->event_id_max = 58;
          break;
        case GceaCounterBlockId:
          block_info->instance_count = 32;
          block_info->event_id_max = 83;
      }
    }
  }

 protected:
  static const GpuBlockInfo* block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];
};

const GpuBlockInfo* Mi100Factory::block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER] = {};

// Pm4Factory create mathods
Pm4Factory* Pm4Factory::Gfx9Create(uint32_t se_number) {
  auto p = new Gfx9Factory(se_number);
  if (p == NULL) throw aql_profile_exc_msg("Gfx9Factory allocation failed");
  return p;
}

Pm4Factory* Pm4Factory::Mi100Create(uint32_t se_number) {
  auto p = new Mi100Factory(se_number);
  if (p == NULL) throw aql_profile_exc_msg("FijiFactory allocation failed");
  return p;
}

}  // namespace aql_profile
