#include "core/gfx9_factory.h"
#include "def/gfx940_def.h"
#include "pm4/gfx9_cmd_builder.h"
#include "pm4/pmc_builder.h"
#include "pm4/sqtt_builder.h"

namespace aql_profile {

class Mi300Factory : public Mi100Factory {
 public:
  explicit Mi300Factory(const AgentInfo* agent_info) : Mi100Factory(agent_info) {
    for (unsigned i = 0; i < HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER; ++i) {
      const GpuBlockInfo* base_table_ptr = Gfx9Factory::block_table_[i];
      if (base_table_ptr == NULL) continue;
      GpuBlockInfo* block_info = new GpuBlockInfo(*base_table_ptr);
      block_table_[i] = block_info;
      // overwrite block info for any update from gfx9 to mi300
      switch (block_info->id) {
      case SqCounterBlockId:
        block_info->event_id_max = 373;
        break;
      case TcpCounterBlockId:
        block_info->event_id_max = 84;
        break;
      case TccCounterBlockId:
        block_info->instance_count = 16;
        block_info->event_id_max = 199;
        break;
      case TcaCounterBlockId:
        block_info->instance_count = 32;
        block_info->event_id_max = 34;
        break;
      case GceaCounterBlockId:
        block_info->instance_count = 32;
        block_info->event_id_max = 82;
        break;
      case SdmaCounterBlockId:
        block_info->instance_count = gfx9_cntx_prim::SDMA_COUNTER_BLOCK_NUM_INSTANCES;
        break;
      case UmcCounterBlockId:
        block_info->counter_count = 11;
        block_info->instance_count = 128;
        break;
      }
    }
  }
};

Pm4Factory* Pm4Factory::Mi300Create(const AgentInfo* agent_info) {
  auto p = new Mi300Factory(agent_info);
  if (p == NULL) throw aql_profile_exc_msg("FijiFactory allocation failed");
  return p;
}

}
