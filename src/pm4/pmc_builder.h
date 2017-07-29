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

typedef std::vector<counter_des_t> counters_vector;

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
    // Reset the counter list
    Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::CP_PERFMON_CNTL_ADDR,
                                        Prim::cp_perfmon_cntl_reset_value());
    // Programming perf counters
    std::map<block_des_t, uint32_t, lt_block_des> index_map;
    for (const auto& counter_des : countersVec) {
      const auto* block_info = counter_des.block_info;
      if (block_info->counter_reg_info == NULL) continue;
      const auto& block_des = counter_des.block_des;

      // Counting counter register index per block
      const auto ret = index_map.insert({block_des, 0});
      uint32_t& reg_index = ret.first->second;

      const auto& reg_info = block_info->counter_reg_info[reg_index];

      if (block_info->method & CntlMethodByInstance) {
        Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::GRBM_GFX_INDEX_ADDR,
                                            Prim::grbm_inst_index_value(block_des.index));
      }
      if (block_info->to_clean_regs) {
        for (uint32_t i = 0; i < block_info->counter_count; ++i) {
          Builder::BuildWriteUConfigRegPacket(cmdBuff,
                                              block_info->counter_reg_info[i].register_addr_lo, 0);
          Builder::BuildWriteUConfigRegPacket(cmdBuff,
                                              block_info->counter_reg_info[i].register_addr_hi, 0);
        }
      }
      if (block_info->select_value != NULL) {
        Builder::BuildWriteUConfigRegPacket(cmdBuff, reg_info.select_addr,
                                            block_info->select_value(counter_des));
      }
      if (block_info->sq_block) {
        Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::SQ_PERFCOUNTER_MASK_ADDR,
                                            Prim::sq_mask_value(counter_des));
        Builder::BuildWriteUConfigRegPacket(cmdBuff, reg_info.control_addr,
                                            Prim::sq_control_value(counter_des));
      }

      ++reg_index;
    }
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::GRBM_GFX_INDEX_ADDR,
                                        Prim::grbm_broadcast_value());
    // Program Compute Perfcount Enable register to support perf counting
    Builder::BuildWriteShRegPacket(cmdBuff, Prim::COMPUTE_PERFCOUNT_ENABLE_ADDR,
                                   Prim::cp_perfcount_enable_value());
    // Reset the counter list
    Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::CP_PERFMON_CNTL_ADDR,
                                        Prim::cp_perfmon_cntl_reset_value());
    // Start the counter list
    Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::CP_PERFMON_CNTL_ADDR,
                                        Prim::cp_perfmon_cntl_start_value());
    // Issue barrier command to apply the commands to configure perfcounters
    Builder::BuildWriteWaitIdlePacket(cmdBuff);
  }

  // Build PMC stop PM4 comands
  uint32_t end(CmdBuffer* cmdBuff, const counters_vector& countersVec, void* dataBuff) {
    // Issue barrier command to wait for dispatch to complete
    Builder::BuildWriteWaitIdlePacket(cmdBuff);
    // Stop and freeze counters
    Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::CP_PERFMON_CNTL_ADDR,
                                        Prim::cp_perfmon_cntl_stop_value());
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

      // Counting counter register index per block
      const auto ret = index_map.insert({counter_des.block_des, 0});
      uint32_t& reg_index = ret.first->second;

      const auto& reg_info = block_info->counter_reg_info[reg_index];

      const uint32_t se_index_end = (block_info->method & CntlMethodBySe) ? se_number_ : 1;
      for (uint32_t se_index = 0; se_index < se_index_end; ++se_index) {
        uint32_t grbm_value = Prim::grbm_broadcast_value();
        if ((block_info->method & CntlMethodBySeAndInstance) == CntlMethodBySeAndInstance) {
          grbm_value = Prim::grbm_inst_se_index_value(block_des.index, se_index);
        } else if (block_info->method & CntlMethodBySe) {
          grbm_value = Prim::grbm_se_index_value(se_index);
        } else if (block_info->method & CntlMethodByInstance) {
          grbm_value = Prim::grbm_inst_index_value(block_des.index);
        }
        Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::GRBM_GFX_INDEX_ADDR, grbm_value);

        Builder::BuildCopyRegDataPacket(
            cmdBuff, Prim::COPY_DATA_SEL_REG_PRM, reg_info.register_addr_lo,
            (uint32_t*)dataBuff + read_counter, Prim::COPY_DATA_SEL_COUNT_1DW_PRM, false);
        Builder::BuildCopyRegDataPacket(
            cmdBuff, Prim::COPY_DATA_SEL_REG_PRM, reg_info.register_addr_hi,
            (uint32_t*)dataBuff + read_counter + 1, Prim::COPY_DATA_SEL_COUNT_1DW_PRM, false);
        read_counter += 2;
      }

      ++reg_index;
    }
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::GRBM_GFX_INDEX_ADDR,
                                        Prim::grbm_broadcast_value());
    // Enable RLC Perfmon Clock Gating. On Vega this is
    // was disabled during Perf Cntrs collection session
    if (Prim::GFXIP_LEVEL == 9)
      Builder::BuildWriteUConfigRegPacket(cmdBuff, Prim::RLC_PERFMON_CLK_CNTL_ADDR, 0);
    // Return amount of data to read
    return read_counter * sizeof(uint32_t);
  }
};

}  // namespace pm4_builder

#endif  // _PMC_BUILDER_H_
