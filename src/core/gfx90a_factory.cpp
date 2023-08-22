#include "core/gfx9_factory.h"
#include "def/gfx90a_def.h"
#include "pm4/gfx9_cmd_builder.h"
#include "pm4/pmc_builder.h"
#include "pm4/sqtt_builder.h"

namespace aql_profile {


// Mi200 factory class
class Mi200Factory : public Gfx9Factory {
 public:
  explicit Mi200Factory(const AgentInfo* agent_info);

 protected:
  static const GpuBlockInfo* block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];
};

const GpuBlockInfo* Mi200Factory::block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER] = {};

Mi200Factory::Mi200Factory(const AgentInfo* agent_info)
  : Gfx9Factory(block_table_, sizeof(block_table_), agent_info) {
  for (unsigned i = 0; i < HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER; ++i) {
    const GpuBlockInfo* base_table_ptr = Gfx9Factory::block_table_[i];
    if (base_table_ptr == NULL) continue;
    GpuBlockInfo* block_info = new GpuBlockInfo(*base_table_ptr);
    if (i == HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_UMC)
      block_info = new GpuBlockInfo(UmcCounterBlockInfo);
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
    case UmcCounterBlockId:
      block_info->counter_count = 9;
      break;
    }
  }
}

Pm4Factory* Pm4Factory::Mi200Create(const AgentInfo* agent_info) {
  auto p = new Mi200Factory(agent_info);
  if (p == NULL) throw aql_profile_exc_msg("Mi200Factory allocation failed");
  return p;
}

}
