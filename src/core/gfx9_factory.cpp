#include "core/pm4_factory.h"
#include "def/gfx9_def.h"
#include "pm4/gfx9_cmd_builder.h"
#include "pm4/pmc_builder.h"
#include "pm4/sqtt_builder.h"

namespace aql_profile {

// Gfx9 factory class
class Gfx9Factory : public Pm4Factory {
 public:
  explicit Gfx9Factory(const AgentInfo* agent_info)
      : Pm4Factory(BlockInfoMap(block_table_, sizeof(block_table_))) {
    Init(agent_info);
  }
  Gfx9Factory(const GpuBlockInfo** table, const uint32_t& size, const AgentInfo* agent_info)
      : Pm4Factory(BlockInfoMap(table, size)) {
    Init(agent_info);
  }

 protected:
  void Init(const AgentInfo* agent_info);
  static const GpuBlockInfo* block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];
};

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
    NULL /*MC_XBAR*/, &AtcCounterBlockInfo, &AtcL2CounterBlockInfo, NULL /*&GceaCounterBlockInfo*/,
    &RpbCounterBlockInfo,
    // System blocks
    &SdmaCounterBlockInfo};

// Mi100 factory class
class Mi100Factory : public Gfx9Factory {
 public:
  explicit Mi100Factory(const AgentInfo* agent_info)
      : Gfx9Factory(block_table_, sizeof(block_table_), agent_info) {
    for (unsigned i = 0; i < HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER; ++i) {
      const GpuBlockInfo* base_table_ptr = Gfx9Factory::block_table_[i];
      if (base_table_ptr == NULL) continue;
      GpuBlockInfo* block_info = new GpuBlockInfo(*base_table_ptr);
      block_table_[i] = block_info;

      // overwrite block info for any update from gfx9 to mi100
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
          break;
        case SdmaCounterBlockId:
          block_info->instance_count = gfx9_cntx_prim::SDMA_COUNTER_BLOCK_NUM_INSTANCES;
          break;
      }
    }
  }

 protected:
  static const GpuBlockInfo* block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];
};

const GpuBlockInfo* Mi100Factory::block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER] = {};

// Mi200 factory class
class Mi200Factory : public Mi100Factory {
 public:
  explicit Mi200Factory(const AgentInfo* agent_info) : Mi100Factory(agent_info) {}
};

class Mi300Factory : public Mi100Factory {
 public:
  explicit Mi300Factory(const AgentInfo* agent_info) : Mi100Factory(agent_info) {}
};

// Pm4Factory create mathods
Pm4Factory* Pm4Factory::Gfx9Create(const AgentInfo* agent_info) {
  auto p = new Gfx9Factory(agent_info);
  if (p == NULL) throw aql_profile_exc_msg("Gfx9Factory allocation failed");
  return p;
}

Pm4Factory* Pm4Factory::Mi100Create(const AgentInfo* agent_info) {
  auto p = new Mi100Factory(agent_info);
  if (p == NULL) throw aql_profile_exc_msg("Mi100Factory allocation failed");
  return p;
}

Pm4Factory* Pm4Factory::Mi200Create(const AgentInfo* agent_info) {
  auto p = new Mi200Factory(agent_info);
  if (p == NULL) throw aql_profile_exc_msg("Mi200Factory allocation failed");
  return p;
}

Pm4Factory* Pm4Factory::Mi300Create(const AgentInfo* agent_info) {
  auto p = new Mi300Factory(agent_info);
  if (p == NULL) throw aql_profile_exc_msg("FijiFactory allocation failed");
  return p;
}

}  // namespace aql_profile
