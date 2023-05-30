#ifndef SRC_PM4_PMC_BUILDER_H_
#define SRC_PM4_PMC_BUILDER_H_

#include <stdint.h>

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "def/gpu_block_info.h"
#include "pm4/cmd_config.h"
#include "util/hsa_rsrc_factory.h"

namespace pm4_builder {
class CmdBuffer;
class CmdBuilder;

// PMC PM4 commands builder virtual interface
class PmcBuilder {
 public:
  PmcBuilder() {}
  virtual ~PmcBuilder() {}
  // Generate enable profiling commands
  virtual void Enable(CmdBuffer* cmd_buffer) = 0;
  // Generate disable profiling commands
  virtual void Disable(CmdBuffer* cmd_buffer) = 0;
  // Generate wait for GPU idle commands
  virtual void WaitIdle(CmdBuffer* cmd_buffer) = 0;
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
  virtual int GetSQ_PMC_samples_per_SE() = 0;//{ return 1; };
};

// PMC PM4 commands builder template
template <typename Builder, typename Primitives, bool concurrent>
class GpuPmcBuilder : public PmcBuilder, protected Builder, protected Primitives {
 private:
  typedef uint32_t reg_addr_t;
  // Shader Engines number on the GPU
  uint32_t se_number_;
  uint32_t wgp_per_sa;
  uint32_t sarrays_per_se;
  // XCC number on the GPU
  uint32_t xcc_number_;

  // Reg-info table getting helper
  const CounterRegInfo* get_reg_table(const counter_des_t& counter_des) {
    const auto* block_info = counter_des.block_info;
    const auto& block_des = counter_des.block_des;
    const auto base_index = (block_info->attr & CounterBlockExplInstAttr)
                                ? block_des.index * block_info->counter_count
                                : 0;
    return &(block_info->counter_reg_info[base_index]);
  }

 public:
  explicit GpuPmcBuilder(const AgentInfo* agent_info): PmcBuilder(),
      se_number_(agent_info->se_num / agent_info->xcc_num),
      xcc_number_(agent_info->xcc_num),
      sarrays_per_se(agent_info->shader_arrays_per_se) {
        this->wgp_per_sa = agent_info->cu_num/sarrays_per_se/se_number_/2;
  }

  int GetSQ_PMC_samples_per_SE() override {
    if (Primitives::GFXIP_LEVEL == 11)
      return sarrays_per_se*wgp_per_sa;
    return 1;
  };

  // Build PMC enable PM4 comands - enable CP counting for a specific queue
  void Enable(CmdBuffer* cmd_buffer) {
    // Program Compute Perfcount Enable register to support perf counting
    Builder::BuildWriteShRegPacket(cmd_buffer, Primitives::COMPUTE_PERFCOUNT_ENABLE_ADDR,
                                   Primitives::cp_perfcount_enable_value());
  }
  // Build PMC disable PM4 comands - enable CP counting for a specific queue
  void Disable(CmdBuffer* cmd_buffer) {
    // Program Compute Perfcount Enable register to support perf counting
    Builder::BuildWriteShRegPacket(cmd_buffer, Primitives::COMPUTE_PERFCOUNT_ENABLE_ADDR,
                                   Primitives::cp_perfcount_disable_value());
  }
  // Build PMC waite-idle PM4 comands - enable CP counting for a specific queue
  void WaitIdle(CmdBuffer* cmd_buffer) {
    // Program Compute Perfcount WaiteIdle register to support perf counting
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
  }

  // Build PMC start PM4 comands
  void Start(CmdBuffer* cmd_buffer, const counters_vector& counters_vec) {
    // sdma performance monitor control value accumulator
    std::pair<reg_addr_t, uint32_t>
        sdma_select_accumulator[Primitives::SDMA_COUNTER_BLOCK_NUM_INSTANCES];
    // Issue barrier command
    if (!concurrent) Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
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
    // Enable SQ Counter Control enable perfomance counter in graphics pipeline if implied
    Primitives::validate_counters(counters_vec.get_attr());
    if (counters_vec.get_attr() & CounterBlockTcAttr) {
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_PERFCOUNTER_CTRL_ADDR,
                                          Primitives::sq_control_enable_value());
    }
    if (Primitives::GFXIP_LEVEL == 11 && (counters_vec.get_attr() & (CounterBlockTcAttr|CounterBlockSqAttr))) {
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_PERFCOUNTER_CTRL2_ADDR,
                                          Primitives::sq_control2_enable_value());
    }
#if defined(_GFX10_PRIMITIVES_H_) || defined (_GFX11_PRIMITIVES_H_)
    // Clear and enable GUS counters
    if (counters_vec.get_attr() & CounterBlockGusAttr) {
      Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::GUS_PERFCOUNTER_RSLT_CNTL_ADDR,
                                         Primitives::gus_disable_clear_value());
      Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::GUS_PERFCOUNTER_RSLT_CNTL_ADDR,
                                         Primitives::gus_start_value());
    }
#endif
    // SDMA mask
    uint32_t sdma_mask = 0;
    // Programming perf counters
    for (const auto& counter_des : counters_vec) {
      const auto* block_info = counter_des.block_info;
      const auto& block_des = counter_des.block_des;
      const auto* reg_table = get_reg_table(counter_des);
      const auto& reg_info = reg_table[counter_des.index];

      //std:: cout << std::hex << "block id("<<block_des.id<<") index("<<block_des.index<<") counter id ("<<counter_des.id
      //            <<") index("<<counter_des.index<<") sel-addr("<<reg_info.select_addr<<")" << std::endl;

      // Set GRBM index to access proper block instance
      const uint32_t grbm_value = (block_info->instance_count > 1)
                                      ? Primitives::grbm_inst_index_value(block_des.index)
                                      : Primitives::grbm_broadcast_value();
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR, grbm_value);
      // Reset counters
      if (block_info->attr & CounterBlockMcAttr) {
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
      if (block_info->attr & CounterBlockSdmaAttr) {
        const auto sdma_index = counter_des.block_des.index;
        sdma_mask |= 1u << sdma_index;
        sdma_select_accumulator[sdma_index].first = reg_info.select_addr;
        sdma_select_accumulator[sdma_index].second |= Primitives::sdma_select_value(counter_des);
      }
      // Start counters
      if (block_info->attr & CounterBlockMcAttr) {
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
        if (Primitives::GFXIP_LEVEL == 9)
          Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_PERFCOUNTER_MASK_ADDR,
                                            Primitives::sq_mask_value(counter_des));
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, reg_info.control_addr,
                                            Primitives::sq_control_value(counter_des));
      }
#if defined(_GFX10_PRIMITIVES_H_) || defined (_GFX11_PRIMITIVES_H_)
      // Configure GUS block
      if (block_info->attr & CounterBlockGusAttr)
        Builder::BuildWriteConfigRegPacket(cmd_buffer, reg_info.select_addr,
                                           Primitives::gus_select_value(counter_des));
#endif
    }
    // SDMA start
    if (sdma_mask != 0) {
      for (uint32_t sdma_index = 0, mask = sdma_mask; mask != 0; sdma_index++, mask >>= 1) {
        if (mask & 1) {
          Builder::BuildWritePConfigRegPacket(cmd_buffer, sdma_select_accumulator[sdma_index].first,
                                              Primitives::sdma_disable_clear_value());
          Builder::BuildWritePConfigRegPacket(cmd_buffer, sdma_select_accumulator[sdma_index].first,
                                              sdma_select_accumulator[sdma_index].second);
        }
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
    if (!concurrent) Builder::BuildWriteWaitIdlePacket(cmd_buffer);
  }

  // Build PMC read PM4 packets
  uint32_t ReadXccPackets(CmdBuffer* cmd_buffer, const counters_vector& counters_vec,
                          void* data_buffer, uint32_t& read_counter) {
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Stop and freeze counters
    if (counters_vec.get_attr() & CounterBlockCpmonAttr) {
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                          Primitives::cp_perfmon_cntl_stop_value());
      // After setting CP_PERFMON_CNTL_ADDR on GFX10, the first reg read is invalid if from SQ block
      if (Primitives::GFXIP_LEVEL == 10 && counters_vec.size() && counters_vec[0].block_des.id == 12) {
        const auto& reg_info = get_reg_table(counters_vec[0])[counters_vec[0].index];
        Builder::BuildCopyCounterDataPacket(cmd_buffer, reg_info.register_addr_lo,
                                        reg_info.register_addr_hi, data_buffer, 3);
        Builder::BuildWriteWaitIdlePacket(cmd_buffer);
      }
      // Uncommenting this will cause the bug to happen again
      //Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
      //                                    Primitives::cp_perfmon_cntl_stop_value());
    }
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
#if defined(_GFX10_PRIMITIVES_H_) || defined (_GFX11_PRIMITIVES_H_)
    // Stop GUS counters
    if (counters_vec.get_attr() & CounterBlockGusAttr)
      Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::GUS_PERFCOUNTER_RSLT_CNTL_ADDR,
                                         Primitives::gus_stop_value());
#endif
    // SDMA mask
    uint32_t sdma_mask = 0;
    // Iterate through the list of blocks to create PM4 packets to read counter values
    for (const auto& counter_des : counters_vec) {
      const auto* block_info = counter_des.block_info;
      const auto& block_des = counter_des.block_des;
      const auto* reg_table = get_reg_table(counter_des);
      const auto& reg_info = reg_table[counter_des.index];

      // Reset Grbm to its default state - broadcast
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                          Primitives::grbm_broadcast_value());

      if (block_info->attr & CounterBlockMcSeqAttr) {
        Builder::BuildWritePConfigRegPacket(cmd_buffer, reg_info.control_addr,
                                            Primitives::mc_seq_config_val(counter_des));
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
        const uint32_t grbm_value = (block_info->instance_count > 1)
                                        ? Primitives::grbm_inst_index_value(block_des.index)
                                        : Primitives::grbm_broadcast_value();
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                            grbm_value);
        Builder::BuildWritePConfigRegPacket(cmd_buffer, reg_info.control_addr,
                                            Primitives::mc_config_value(counter_des));
        uint32_t* data = reinterpret_cast<uint32_t*>(data_buffer) + read_counter;
        Builder::BuildCopyCounterDataPacket(cmd_buffer, reg_info.register_addr_lo,
                                            reg_info.register_addr_hi, data, 3);
        read_counter += 2;
      } else if (block_info->attr & CounterBlockSdmaAttr) {
        // Stop SDMA
        if (block_info->attr & CounterBlockSdmaAttr) {
          const uint32_t mask = 1u << counter_des.block_des.index;
          if ((sdma_mask & mask) == 0) {
            sdma_mask |= mask;
            Builder::BuildWritePConfigRegPacket(cmd_buffer, reg_info.select_addr,
                                                Primitives::sdma_stop_value());
          }
        }
        // Read SDMA
        uint32_t* data = reinterpret_cast<uint32_t*>(data_buffer) + read_counter;
        if (data_buffer != 0) {
          *reinterpret_cast<uint64_t*>(data) = 0;
        }
        Builder::BuildCopyCounterDataPacket(cmd_buffer, reg_info.register_addr_lo, 0x0, data, 0x1);
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

          bool bIsWGPcounter = Primitives::GFXIP_LEVEL == 11 && (block_info->attr & CounterBlockSqAttr);

          if (bIsWGPcounter) {
            for (int sa=0; sa<sarrays_per_se; sa++) for (int wgp=0; wgp<wgp_per_sa; wgp++) {
              if (data_buffer)
                memset(reinterpret_cast<uint32_t*>(data_buffer)+read_counter, 0, sizeof(uint64_t));
              grbm_value = Primitives::grbm_se_sh_wgp_index_value(se_index, wgp, sa);
              Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR, grbm_value);
              Builder::BuildCopyCounterDataPacket(
                  cmd_buffer, reg_info.register_addr_lo, reg_info.register_addr_hi,
                  reinterpret_cast<uint32_t*>(data_buffer) + read_counter, 1);
              read_counter += 2;
            }
          } else {
            Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR, grbm_value);
            Builder::BuildCopyCounterDataPacket(
                cmd_buffer, reg_info.register_addr_lo, reg_info.register_addr_hi,
                reinterpret_cast<uint32_t*>(data_buffer) + read_counter, 3);
            read_counter += 2;
          }
        }
      }
    }
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Reset MC config to broadcast MCD tiles
    if (counters_vec.get_attr() & CounterBlockMcSeqAttr)
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::MC_CONFIG_MCD_ADDR,
                                          Primitives::mc_broadcast_mcd_value());
    if (counters_vec.get_attr() & CounterBlockMcSeqHbmAttr)
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::MC_CONFIG_MCD_ADDR,
                                          Primitives::mc_hbm_broadcast_mcd_value());
    // Return amount of data to read
    return read_counter * sizeof(uint32_t);
  }

  // Build PMC stop PM4 comands
  uint32_t Stop(CmdBuffer* cmd_buffer, const counters_vector& counters_vec, void* data_buffer) {
    // Issue barrier command to wait for dispatch to complete

    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // Generate read commands
    const uint32_t data_size = ReadPackets(cmd_buffer, counters_vec, data_buffer);
    // Enable RLC Perfmon Clock Gating. On Vega this
    // was disabled during Perf Cntrs collection session
    if (Primitives::GFXIP_LEVEL == 9)
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_PERFMON_CLK_CNTL_ADDR, 0);
    // Issue barrier command to wait commands to complete
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // Return amount of data to read
    return data_size;
  }

  // Build PMC read PM4 comands
  uint32_t Read(CmdBuffer* cmd_buffer, const counters_vector& counters_vec, void* data_buffer) {
    // Generate read commands
    const uint32_t data_size = ReadPackets(cmd_buffer, counters_vec, data_buffer);
    // Start the counter list
    if (counters_vec.get_attr() & CounterBlockCpmonAttr)
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                          Primitives::cp_perfmon_cntl_start_value());
    if (counters_vec.get_attr() & CounterBlockSrbmAttr)
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SRBM_PERFMON_CNTL_ADDR,
                                          Primitives::srbm_start_value());
    // Issue barrier command to wait commands to complete
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // Return amount of data to read
    return data_size;
  }

  // Build PMC read PM4 packets
  uint32_t ReadPackets(CmdBuffer* cmd_buffer, const counters_vector& counters_vec,
                       void* data_buffer) {
    uint32_t read_counter = 0;

    for (size_t xcc_selected = 0; xcc_selected < xcc_number_; ++xcc_selected) {
      int pos = cmd_buffer->DwSize();
      if (xcc_number_ > 1){
        Builder::BuildPredExecPacket(cmd_buffer, xcc_selected, 0);
      }

      int initial_buff_size = cmd_buffer->DwSize();
      ReadXccPackets(cmd_buffer, counters_vec, data_buffer, read_counter);
      int delta = cmd_buffer->DwSize() - initial_buff_size;

      // std::cout << "pos, initial_buff_size, delta: " << pos << ", " << initial_buff_size << ", " << delta << std::endl;

      if (xcc_number_ > 1) {
        CmdBuffer pred_exec;
        //Builder::BuildPredExecPacket(&pred_exec, 0, 0);

        auto xcc_buf_size = delta;

        // update first PRED_EXEC packet to its correct value
        //pred_exec.Clear();
        Builder::BuildPredExecPacket(&pred_exec, xcc_selected, xcc_buf_size);
        const uint32_t* data = (const uint32_t*)pred_exec.Data();

        for (size_t i = 0; i < pred_exec.DwSize(); ++i)
          cmd_buffer->Assign(pos + i, data[i]);
      }
    }
    // Return amount of data to read
    return read_counter * sizeof(uint32_t);
  }
};

}  // namespace pm4_builder

#endif  // SRC_PM4_PMC_BUILDER_H_
