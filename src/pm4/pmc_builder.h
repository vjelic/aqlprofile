#ifndef _PMC_BUILDER_H_
#define _PMC_BUILDER_H_

#include <stdint.h>

#include <vector>
#include <map>
#include <string>

#include "def/gpu_block_info.h"

namespace pm4_builder {
class CmdBuffer;
class CmdBuilder;

// Counters vector class
class counters_vector : public std::vector<counter_des_t> {
  public:
  typedef std::vector<counter_des_t> Parent;

  counters_vector() : Parent(), attr(0) {}

  void push_back(const counter_des_t & des) {
    Parent::push_back(des);
    attr |= des.block_info->attr;
  }

  uint32_t get_attr() const { return attr; }

  private:
  uint32_t attr;
};

// PMC PM4 commands builder virtual interface
class PmcBuilder {
 public:
  virtual ~PmcBuilder() {}
  // Generate start profiling commands.
  virtual void begin(CmdBuffer* cmdBuff, const counters_vector& countersVec) = 0;
  // Generate stop profiling commands.
  // Return actual required data buffer size.
  virtual uint32_t end(CmdBuffer* cmdBuff, const counters_vector& countersVec, void* dataBuff) = 0;
  // Shader Engines number on the GPU
  constexpr static uint32_t se_number_ = 4;
};

// PMC PM4 commands builder template
template <typename Builder, typename Prim>
class GpuPmcBuilder : public PmcBuilder, protected Builder, protected Prim {
 public:
  // Build PMC start PM4 comands
  void begin(CmdBuffer* cmdBuff, const counters_vector& countersVec) {
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::GRBM_GFX_INDEX_ADDR,
                                        Prim::grbm_broadcast_value());
    // Disable RLC Perfmon Clock Gating
    // On Vega this is needed to collect Perf Cntrs
    if (Prim::GFXIP_LEVEL == 9)
      Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::RLC_PERFMON_CLK_CNTL_ADDR, 1);
    // Reset perf counters
    if (countersVec.get_attr() & CounterBlockCpmonAttr)
      Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::CP_PERFMON_CNTL_ADDR,
                                          Prim::cp_perfmon_cntl_reset_value());
    if (countersVec.get_attr() & CounterBlockSrbmAttr)
      Builder::BuildWritePConfigRegPacket(cmdBuff, Prim::SRBM_PERFMON_CNTL_ADDR,
                                          Prim::srbm_reset_value());
    // Broadcasting to all MC channels
    if ((Prim::GFXIP_LEVEL == 8) && (countersVec.get_attr() & CounterBlockMcAttr))
      Builder::BuildWritePConfigRegPacket(cmdBuff, Prim::MC_CONFIG_ADDR,
                                          Prim::mc_broadcast_value());
    // Programming perf counters
    for (const auto& counter_des : countersVec) {
      const auto* block_info = counter_des.block_info;
      if (block_info->counter_reg_info == NULL) continue;
      const auto& block_des = counter_des.block_des;
      const uint32_t reg_index = counter_des.index;
      const auto& reg_info = block_info->counter_reg_info[reg_index];

      if (block_info->instance_count > 1) {
        Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::GRBM_GFX_INDEX_ADDR,
                                            Prim::grbm_inst_index_value(block_des.index));
      }
      if (block_info->attr & CounterBlockCleanAttr) {
        for (uint32_t i = 0; i < block_info->counter_count; ++i) {
          Builder::BuildWriteConfigRegPacket(cmdBuff,
                                             block_info->counter_reg_info[i].register_addr_lo, 0);
          Builder::BuildWriteConfigRegPacket(cmdBuff,
                                             block_info->counter_reg_info[i].register_addr_hi, 0);
        }
      }
      if (block_info->select_value != NULL) {
        Builder::BuildWriteConfigRegPacket(cmdBuff, reg_info.select_addr,
                                           block_info->select_value(counter_des));
      }
      if ((Prim::GFXIP_LEVEL == 8) && (block_info->attr & CounterBlockMcAttr)) {
        Builder::BuildWriteConfigRegPacket(cmdBuff, Prim::MC_SELECT1_ADDR,
                                           Prim::mc_select1_value(counter_des));
      }
      if (block_info->attr & CounterBlockSqAttr) {
        Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::SQ_PERFCOUNTER_MASK_ADDR,
                                            Prim::sq_mask_value(counter_des));
        Builder::BuildWriteUConfigRegPacket(cmdBuff, reg_info.control_addr,
                                            Prim::sq_control_value(counter_des));
      }
    }
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::GRBM_GFX_INDEX_ADDR,
                                        Prim::grbm_broadcast_value());
    // Program Compute Perfcount Enable register to support perf counting
    Builder::BuildWriteShRegPacket(cmdBuff, Prim::COMPUTE_PERFCOUNT_ENABLE_ADDR,
                                   Prim::cp_perfcount_enable_value());
    // Reset the counter list
    if (countersVec.get_attr() & CounterBlockCpmonAttr)
      Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::CP_PERFMON_CNTL_ADDR,
                                          Prim::cp_perfmon_cntl_reset_value());
    if (countersVec.get_attr() & CounterBlockSrbmAttr)
      Builder::BuildWritePConfigRegPacket(cmdBuff, Prim::SRBM_PERFMON_CNTL_ADDR,
                                          Prim::srbm_reset_value());
    // Start the counter list
    if (countersVec.get_attr() & CounterBlockCpmonAttr)
      Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::CP_PERFMON_CNTL_ADDR,
                                          Prim::cp_perfmon_cntl_start_value());
    if (countersVec.get_attr() & CounterBlockSrbmAttr)
      Builder::BuildWritePConfigRegPacket(cmdBuff, Prim::SRBM_PERFMON_CNTL_ADDR,
                                          Prim::srbm_start_value());
    // Issue barrier command to apply the commands to configure perfcounters
    Builder::BuildWriteWaitIdlePacket(cmdBuff);
  }

  // Build PMC stop PM4 comands
  uint32_t end(CmdBuffer* cmdBuff, const counters_vector& countersVec, void* dataBuff) {
    // Issue barrier command to wait for dispatch to complete
    Builder::BuildWriteWaitIdlePacket(cmdBuff);
    // Stop and freeze counters
    if (countersVec.get_attr() & CounterBlockCpmonAttr)
      Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::CP_PERFMON_CNTL_ADDR,
                                          Prim::cp_perfmon_cntl_stop_value());
    if (countersVec.get_attr() & CounterBlockSrbmAttr)
      Builder::BuildWritePConfigRegPacket(cmdBuff, Prim::SRBM_PERFMON_CNTL_ADDR,
                                          Prim::srbm_stop_value());
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::GRBM_GFX_INDEX_ADDR,
                                        Prim::grbm_broadcast_value());
    // Iterate through the list of blocks to create PM4 packets to read counter values
    std::map<block_des_t, uint32_t, lt_block_des> index_map;
    uint32_t read_counter = 0;
    for (const auto& counter_des : countersVec) {
      const auto* block_info = counter_des.block_info;
      if (block_info->counter_reg_info == NULL) continue;
      const auto& block_des = counter_des.block_des;
      const auto& reg_info = block_info->counter_reg_info[counter_des.index];

      if (block_info->attr & CounterBlockMcAttr) {
        Builder::BuildWritePConfigRegPacket(cmdBuff, reg_info.control_addr,
                                            Prim::mc_config_value(counter_des));
        uint32_t* data = (uint32_t*)dataBuff + read_counter;
        *(uint64_t*)data = 0;
        Builder::BuildCopyCounterDataPacket(cmdBuff, reg_info.register_addr_lo,
                                            reg_info.register_addr_hi, data,
                                            Prim::mc_channel_mask(counter_des));
        read_counter += 2;
      } else {
        const uint32_t se_end_index = (block_info->attr & CounterBlockSeAttr) ? se_number_ : 1;
        for (uint32_t se_index = 0; se_index < se_end_index; ++se_index) {
          uint32_t grbm_value = Prim::grbm_broadcast_value();
          if ((block_info->instance_count > 1) && (block_info->attr & CounterBlockSeAttr)) {
            grbm_value = Prim::grbm_inst_se_index_value(block_des.index, se_index);
          } else if (block_info->instance_count > 1) {
            grbm_value = Prim::grbm_inst_index_value(block_des.index);
          } else if (block_info->attr & CounterBlockSeAttr) {
            grbm_value = Prim::grbm_se_index_value(se_index);
          }
          Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::GRBM_GFX_INDEX_ADDR, grbm_value);
          Builder::BuildCopyCounterDataPacket(cmdBuff, reg_info.register_addr_lo,
                                              reg_info.register_addr_hi,
                                              (uint32_t*)dataBuff + read_counter, 3);
          read_counter += 2;
        }
      }
    }
    // Reset MC config to broadcast
    if ((Prim::GFXIP_LEVEL == 8) && (countersVec.get_attr() & CounterBlockMcAttr))
      Builder::BuildWritePConfigRegPacket(cmdBuff, Prim::MC_CONFIG_ADDR,
                                          Prim::mc_broadcast_value());
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::GRBM_GFX_INDEX_ADDR,
                                        Prim::grbm_broadcast_value());
    // Enable RLC Perfmon Clock Gating. On Vega this
    // was disabled during Perf Cntrs collection session
    if (Prim::GFXIP_LEVEL == 9)
      Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::RLC_PERFMON_CLK_CNTL_ADDR, 0);
    // Return amount of data to read
    return read_counter * sizeof(uint32_t);
  }
};

}  // namespace pm4_builder

#endif  // _PMC_BUILDER_H_
