#ifndef SRC_PM4_PMC_BUILDER_H_
#define SRC_PM4_PMC_BUILDER_H_

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

  counters_vector() : Parent(), attr_(0) {}

  void push_back(const counter_des_t& des) {
    Parent::push_back(des);
    attr_ |= des.block_info->attr;
  }

  uint32_t get_attr() const { return attr_; }

 private:
  uint32_t attr_;
};

// PMC PM4 commands builder virtual interface
class PmcBuilder {
 public:
  virtual ~PmcBuilder() {}
  // Generate start profiling commands.
  virtual void Start(CmdBuffer* cmd_buffer, const counters_vector& counters_vec) = 0;
  // Generate stop profiling commands.
  // Return actual required data buffer size.
  virtual uint32_t Stop(CmdBuffer* cmd_buffer, const counters_vector& counters_vec,
                        void* data_buffer) = 0;
  // Generate read profiling commands.
  // Return actual required data buffer size.
  virtual uint32_t Read(CmdBuffer* cmd_buffer, const counters_vector& counters_vec,
                        void* data_buffer) = 0;

 protected:
  // Shader Engines number on the GPU
  static constexpr uint32_t se_number_ = 4;
};

// PMC PM4 commands builder template
template <typename Builder, typename Primitives>
class GpuPmcBuilder : public PmcBuilder, protected Builder, protected Primitives {
 public:
  // Build PMC start PM4 comands
  void Start(CmdBuffer* cmd_buffer, const counters_vector& counters_vec) {
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Issue barrier command
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // Disable RLC Perfmon Clock Gating
    // On Vega this is needed to collect Perf Cntrs
    if (Primitives::GFXIP_LEVEL == 9)
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_PERFMON_CLK_CNTL_ADDR, 1);
    // Reset perf counters
    if (counters_vec.get_attr() & CounterBlockCpmonAttr)
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                          Primitives::cp_perfmon_cntl_reset_value());
    if (counters_vec.get_attr() & CounterBlockSrbmAttr)
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SRBM_PERFMON_CNTL_ADDR,
                                          Primitives::srbm_reset_value());
    // MC SEQ broadcasting to all MCD tiles
    if (counters_vec.get_attr() & CounterBlockMcSeqAttr)
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::MC_CONFIG_MCD_ADDR,
                                          Primitives::mc_broadcast_mcd_value());
    // MC SEQ HBM Stop/Clear all channels
    if (counters_vec.get_attr() & CounterBlockMcSeqHbmAttr) {
      // MC config to broadcast MCD tiles
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::MC_CONFIG_MCD_ADDR,
                                          Primitives::mc_hbm_broadcast_mcd_value());
      // MC_SEQ_PERFCOUNTER_RSLT_CNTL_M<CHANNEL>
      //   ::ENABLE_ANY = 0
      //   ::CLEAR_ALL = 1
      Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::MC_SEQ_PERFCOUNTER_RSLT_CNTL_ADDR,
                                         Primitives::mc_seq_hbm_reset_value());
      Builder::BuildWriteConfigRegPacket(cmd_buffer,
                                         Primitives::MC_SEQ_PERFCOUNTER_RSLT_CNTL_M1_ADDR,
                                         Primitives::mc_seq_hbm_reset_value());
      Builder::BuildWriteConfigRegPacket(cmd_buffer,
                                         Primitives::MC_SEQ_PERFCOUNTER_RSLT_CNTL_M2_ADDR,
                                         Primitives::mc_seq_hbm_reset_value());
      Builder::BuildWriteConfigRegPacket(cmd_buffer,
                                         Primitives::MC_SEQ_PERFCOUNTER_RSLT_CNTL_M3_ADDR,
                                         Primitives::mc_seq_hbm_reset_value());
    }
    // Programming perf counters
    for (const auto& counter_des : counters_vec) {
      const auto* block_info = counter_des.block_info;
      const auto& block_des = counter_des.block_des;
      const auto& reg_info = block_info->counter_reg_info[counter_des.index];

      // Set GRBM index to access proper block instance
      if (block_info->instance_count > 1) {
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                            Primitives::grbm_inst_index_value(block_des.index));
      }
      // Reset counters
      if (counters_vec.get_attr() & CounterBlockMcAttr) {
        Builder::BuildWritePConfigRegPacket(cmd_buffer, reg_info.control_addr,
                                            Primitives::mc_reset_value());
      }
      if (block_info->attr & CounterBlockMcSeqAttr) {
        Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::MC_SEQ_CONTROL_ADDR,
                                           Primitives::mc_seq_reset_value());
      }
      if (block_info->attr & CounterBlockCleanAttr) {
        for (uint32_t i = 0; i < block_info->counter_count; ++i) {
          Builder::BuildWriteConfigRegPacket(cmd_buffer,
                                             block_info->counter_reg_info[i].register_addr_lo, 0);
          Builder::BuildWriteConfigRegPacket(cmd_buffer,
                                             block_info->counter_reg_info[i].register_addr_hi, 0);
        }
      }
      // Setup counters
      if (block_info->select_value != NULL) {
        Builder::BuildWriteConfigRegPacket(cmd_buffer, reg_info.select_addr,
                                           block_info->select_value(counter_des));
      }
      if (block_info->attr & CounterBlockMcSeqAttr) {
        Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::MC_SEQ_SELECT1_ADDR,
                                           Primitives::mc_seq_select1_value(counter_des));
      }
      if (block_info->attr & CounterBlockMcSeqHbmAttr) {
        // MC_CONFIG_MCD = 1 << <MCD>
        Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::MC_CONFIG_MCD_ADDR,
                                            Primitives::mc_config_mcd_select_value(counter_des));
        // MC_SEQ_PERFCOUNTER<COUNTERID>_CFG_M<CHANNEL>
        //   ::PERF_SEL = <EVENTID>
        //   ::ENABLE = 1
        Builder::BuildWriteConfigRegPacket(
            cmd_buffer, Primitives::mc_seq_perfcounter_cfg_addr(counter_des),
            Primitives::mc_seq_perfcounter_select_value(counter_des));
      }
      // Start counters
      if (counters_vec.get_attr() & CounterBlockMcAttr) {
        Builder::BuildWritePConfigRegPacket(cmd_buffer, reg_info.control_addr,
                                            Primitives::mc_config_value(counter_des));
        Builder::BuildWritePConfigRegPacket(cmd_buffer, reg_info.control_addr,
                                            Primitives::mc_start_value());
      }
      if (block_info->attr & CounterBlockMcSeqAttr) {
        Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::MC_SEQ_CONTROL_ADDR,
                                           Primitives::mc_seq_start_value());
      }
      // Configure SQ block
      if (block_info->attr & CounterBlockSqAttr) {
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_PERFCOUNTER_MASK_ADDR,
                                            Primitives::sq_mask_value(counter_des));
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, reg_info.control_addr,
                                            Primitives::sq_control_value(counter_des));
      }
    }
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Program Compute Perfcount Enable register to support perf counting
    Builder::BuildWriteShRegPacket(cmd_buffer, Primitives::COMPUTE_PERFCOUNT_ENABLE_ADDR,
                                   Primitives::cp_perfcount_enable_value());
    // Reset the counter list
    if (counters_vec.get_attr() & CounterBlockCpmonAttr)
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                          Primitives::cp_perfmon_cntl_reset_value());
    if (counters_vec.get_attr() & CounterBlockSrbmAttr)
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SRBM_PERFMON_CNTL_ADDR,
                                          Primitives::srbm_reset_value());
    // Start the counter list
    if (counters_vec.get_attr() & CounterBlockCpmonAttr)
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                          Primitives::cp_perfmon_cntl_start_value());
    if (counters_vec.get_attr() & CounterBlockSrbmAttr)
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SRBM_PERFMON_CNTL_ADDR,
                                          Primitives::srbm_start_value());
    // MC SEQ HBM Start/Clear all channels
    if (counters_vec.get_attr() & CounterBlockMcSeqHbmAttr) {
      // MC config to broadcast MCD tiles
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::MC_CONFIG_MCD_ADDR,
                                          Primitives::mc_hbm_broadcast_mcd_value());
      // MC_SEQ_PERFCOUNTER_RSLT_CNTL_M<CHANNEL>
      //   ::ENABLE_ANY = 1
      //   ::CLEAR_ALL = 1
      Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::MC_SEQ_PERFCOUNTER_RSLT_CNTL_ADDR,
                                         Primitives::mc_seq_hbm_start_value());
      Builder::BuildWriteConfigRegPacket(cmd_buffer,
                                         Primitives::MC_SEQ_PERFCOUNTER_RSLT_CNTL_M1_ADDR,
                                         Primitives::mc_seq_hbm_start_value());
      Builder::BuildWriteConfigRegPacket(cmd_buffer,
                                         Primitives::MC_SEQ_PERFCOUNTER_RSLT_CNTL_M2_ADDR,
                                         Primitives::mc_seq_hbm_start_value());
      Builder::BuildWriteConfigRegPacket(cmd_buffer,
                                         Primitives::MC_SEQ_PERFCOUNTER_RSLT_CNTL_M3_ADDR,
                                         Primitives::mc_seq_hbm_start_value());
    }
    // Issue barrier command to apply the commands to configure perfcounters
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
  }

  // Build PMC stop PM4 comands
  uint32_t Stop(CmdBuffer* cmd_buffer, const counters_vector& counters_vec, void* data_buffer) {
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Issue barrier command to wait for dispatch to complete
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // Stop and freeze counters
    if (counters_vec.get_attr() & CounterBlockCpmonAttr)
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                          Primitives::cp_perfmon_cntl_stop_value());
    if (counters_vec.get_attr() & CounterBlockSrbmAttr)
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SRBM_PERFMON_CNTL_ADDR,
                                          Primitives::srbm_stop_value());
    // MC SEQ HBM Stop/Freeze all channels
    if (counters_vec.get_attr() & CounterBlockMcSeqHbmAttr) {
      // MC config to broadcast MCD tiles
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::MC_CONFIG_MCD_ADDR,
                                          Primitives::mc_hbm_broadcast_mcd_value());
      // Stop for all channels
      // MC_SEQ_PERFCOUNTER_RSLT_CNTL_M<CHANNEL>::ENABLE_ANY = 0
      Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::MC_SEQ_PERFCOUNTER_RSLT_CNTL_ADDR,
                                         Primitives::mc_seq_hbm_stop_value());
      Builder::BuildWriteConfigRegPacket(cmd_buffer,
                                         Primitives::MC_SEQ_PERFCOUNTER_RSLT_CNTL_M1_ADDR,
                                         Primitives::mc_seq_hbm_stop_value());
      Builder::BuildWriteConfigRegPacket(cmd_buffer,
                                         Primitives::MC_SEQ_PERFCOUNTER_RSLT_CNTL_M2_ADDR,
                                         Primitives::mc_seq_hbm_stop_value());
      Builder::BuildWriteConfigRegPacket(cmd_buffer,
                                         Primitives::MC_SEQ_PERFCOUNTER_RSLT_CNTL_M3_ADDR,
                                         Primitives::mc_seq_hbm_stop_value());
    }
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Iterate through the list of blocks to create PM4 packets to read counter values
    std::map<block_des_t, uint32_t, lt_block_des> index_map;
    uint32_t read_counter = 0;
    for (const auto& counter_des : counters_vec) {
      const auto* block_info = counter_des.block_info;
      const auto& block_des = counter_des.block_des;
      const auto& reg_info = block_info->counter_reg_info[counter_des.index];

      if (block_info->attr & CounterBlockMcSeqAttr) {
        Builder::BuildWritePConfigRegPacket(cmd_buffer, reg_info.control_addr,
                                            Primitives::mc_config_value(counter_des));
        uint32_t* data = reinterpret_cast<uint32_t*>(data_buffer) + read_counter;
        *reinterpret_cast<uint64_t*>(data) = 0;
        Builder::BuildCopyCounterDataPacket(cmd_buffer, reg_info.register_addr_lo,
                                            reg_info.register_addr_hi, data,
                                            Primitives::mc_channel_mask(counter_des));
        read_counter += 2;
      } else if (block_info->attr & CounterBlockMcSeqHbmAttr) {
        // Select the MCD tile to read from.
        // MC_CONFIG_MCD = (1 << <MCD>) | (MCD << 8)
        Builder::BuildWritePConfigRegPacket(
            cmd_buffer, Primitives::MC_CONFIG_MCD_ADDR,
            Primitives::mc_config_mcd_hbm_sample_value(counter_des));
        // Select which perf counter to read for the channel
        // MC_SEQ_PERFCOUNTER_RSLT_CNTL_M<CHANNEL>::PERF_COUNTER_SELECT = <COUNTERID>
        Builder::BuildWritePConfigRegPacket(
            cmd_buffer, Primitives::mc_seq_perfcounter_rslt_cntl_addr(counter_des),
            Primitives::mc_seq_perfcounter_rslt_cntl_value(counter_des));
        // Read the channel counter registers
        // MC_SEQ_PERFCOUNTER_LO_M<CHANNEL> and MC_SEQ_PERFCOUNTER_HI_M<CHANNEL>
        uint32_t* data = reinterpret_cast<uint32_t*>(data_buffer) + read_counter;
        Builder::BuildCopyCounterDataPacket(
            cmd_buffer, Primitives::mc_hbm_register_lo_addr(counter_des),
            Primitives::mc_hbm_register_hi_addr(counter_des), data, 3);
        read_counter += 2;
      } else if (block_info->attr & CounterBlockMcAttr) {
        if (block_info->instance_count > 1) {
          Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                              Primitives::grbm_inst_index_value(block_des.index));
        }
        Builder::BuildWritePConfigRegPacket(cmd_buffer, reg_info.control_addr,
                                            Primitives::mc_config_value(counter_des));
        uint32_t* data = reinterpret_cast<uint32_t*>(data_buffer) + read_counter;
        Builder::BuildCopyCounterDataPacket(cmd_buffer, reg_info.register_addr_lo,
                                            reg_info.register_addr_hi, data, 3);
        read_counter += 2;
      } else {
        const uint32_t se_end_index = (block_info->attr & CounterBlockSeAttr) ? se_number_ : 1;
        for (uint32_t se_index = 0; se_index < se_end_index; ++se_index) {
          uint32_t grbm_value = Primitives::grbm_broadcast_value();
          if ((block_info->instance_count > 1) && (block_info->attr & CounterBlockSeAttr)) {
            grbm_value = Primitives::grbm_inst_se_index_value(block_des.index, se_index);
          } else if (block_info->instance_count > 1) {
            grbm_value = Primitives::grbm_inst_index_value(block_des.index);
          } else if (block_info->attr & CounterBlockSeAttr) {
            grbm_value = Primitives::grbm_se_index_value(se_index);
          }
          Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                              grbm_value);
          Builder::BuildCopyCounterDataPacket(
              cmd_buffer, reg_info.register_addr_lo, reg_info.register_addr_hi,
              reinterpret_cast<uint32_t*>(data_buffer) + read_counter, 3);
          read_counter += 2;
        }
      }
    }
    // Reset MC config to broadcast MCD tiles
    if (counters_vec.get_attr() & CounterBlockMcSeqAttr)
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::MC_CONFIG_MCD_ADDR,
                                          Primitives::mc_broadcast_mcd_value());
    if (counters_vec.get_attr() & CounterBlockMcSeqHbmAttr)
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::MC_CONFIG_MCD_ADDR,
                                          Primitives::mc_hbm_broadcast_mcd_value());
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Enable RLC Perfmon Clock Gating. On Vega this
    // was disabled during Perf Cntrs collection session
    if (Primitives::GFXIP_LEVEL == 9)
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_PERFMON_CLK_CNTL_ADDR, 0);
    // Issue barrier command to wait for data copy commands to complete
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // Return amount of data to read
    return read_counter * sizeof(uint32_t);
  }

  // Build PMC read PM4 comands
  uint32_t Read(CmdBuffer* cmd_buffer, const counters_vector& counters_vec, void* data_buffer) {
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Iterate through the list of blocks to create PM4 packets to read counter values
    std::map<block_des_t, uint32_t, lt_block_des> index_map;
    uint32_t read_counter = 0;
    for (const auto& counter_des : counters_vec) {
      const auto* block_info = counter_des.block_info;
      const auto& block_des = counter_des.block_des;
      const auto& reg_info = block_info->counter_reg_info[counter_des.index];

      if (block_info->attr & CounterBlockMcSeqAttr) {
        Builder::BuildWritePConfigRegPacket(cmd_buffer, reg_info.control_addr,
                                            Primitives::mc_config_value(counter_des));
        uint32_t* data = reinterpret_cast<uint32_t*>(data_buffer) + read_counter;
        *reinterpret_cast<uint64_t*>(data) = 0;
        Builder::BuildCopyCounterDataPacket(cmd_buffer, reg_info.register_addr_lo,
                                            reg_info.register_addr_hi, data,
                                            Primitives::mc_channel_mask(counter_des));
        read_counter += 2;
      } else if (block_info->attr & CounterBlockMcSeqHbmAttr) {
        // Select the MCD tile to read from.
        // MC_CONFIG_MCD = (1 << <MCD>) | (MCD << 8)
        Builder::BuildWritePConfigRegPacket(
            cmd_buffer, Primitives::MC_CONFIG_MCD_ADDR,
            Primitives::mc_config_mcd_hbm_sample_value(counter_des));
        // Select which perf counter to read for the channel
        // MC_SEQ_PERFCOUNTER_RSLT_CNTL_M<CHANNEL>::PERF_COUNTER_SELECT = <COUNTERID>
        Builder::BuildWritePConfigRegPacket(
            cmd_buffer, Primitives::mc_seq_perfcounter_rslt_cntl_addr(counter_des),
            Primitives::mc_seq_perfcounter_rslt_cntl_value(counter_des));
        // Read the channel counter registers
        // MC_SEQ_PERFCOUNTER_LO_M<CHANNEL> and MC_SEQ_PERFCOUNTER_HI_M<CHANNEL>
        uint32_t* data = reinterpret_cast<uint32_t*>(data_buffer) + read_counter;
        Builder::BuildCopyCounterDataPacket(
            cmd_buffer, Primitives::mc_hbm_register_lo_addr(counter_des),
            Primitives::mc_hbm_register_hi_addr(counter_des), data, 3);
        read_counter += 2;
      } else if (block_info->attr & CounterBlockMcAttr) {
        if (block_info->instance_count > 1) {
          Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                              Primitives::grbm_inst_index_value(block_des.index));
        }
        Builder::BuildWritePConfigRegPacket(cmd_buffer, reg_info.control_addr,
                                            Primitives::mc_config_value(counter_des));
        uint32_t* data = reinterpret_cast<uint32_t*>(data_buffer) + read_counter;
        Builder::BuildCopyCounterDataPacket(cmd_buffer, reg_info.register_addr_lo,
                                            reg_info.register_addr_hi, data, 3);
        read_counter += 2;
      } else {
        const uint32_t se_end_index = (block_info->attr & CounterBlockSeAttr) ? se_number_ : 1;
        for (uint32_t se_index = 0; se_index < se_end_index; ++se_index) {
          uint32_t grbm_value = Primitives::grbm_broadcast_value();
          if ((block_info->instance_count > 1) && (block_info->attr & CounterBlockSeAttr)) {
            grbm_value = Primitives::grbm_inst_se_index_value(block_des.index, se_index);
          } else if (block_info->instance_count > 1) {
            grbm_value = Primitives::grbm_inst_index_value(block_des.index);
          } else if (block_info->attr & CounterBlockSeAttr) {
            grbm_value = Primitives::grbm_se_index_value(se_index);
          }
          Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                              grbm_value);
          Builder::BuildCopyCounterDataPacket(
              cmd_buffer, reg_info.register_addr_lo, reg_info.register_addr_hi,
              reinterpret_cast<uint32_t*>(data_buffer) + read_counter, 3);
          read_counter += 2;
        }
      }
    }
    // Reset MC config to broadcast MCD tiles
    if (counters_vec.get_attr() & CounterBlockMcSeqAttr)
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::MC_CONFIG_MCD_ADDR,
                                          Primitives::mc_broadcast_mcd_value());
    if (counters_vec.get_attr() & CounterBlockMcSeqHbmAttr)
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::MC_CONFIG_MCD_ADDR,
                                          Primitives::mc_hbm_broadcast_mcd_value());
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Return amount of data to read
    return read_counter * sizeof(uint32_t);
  }
};

}  // namespace pm4_builder

#endif  // SRC_PM4_PMC_BUILDER_H_
