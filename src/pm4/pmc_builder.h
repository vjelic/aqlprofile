#ifndef SRC_PM4_PMC_BUILDER_H_
#define SRC_PM4_PMC_BUILDER_H_

#include <stdint.h>

#include <set>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "def/gpu_block_info.h"
#include "pm4/cmd_config.h"
#include "util/hsa_rsrc_factory.h"

namespace pm4_builder {
// MI300 UMC constants
constexpr uint32_t VIRTUALXCCID_SELECT = 0;
constexpr uint32_t UMC_MASTER_XCC = 2;
constexpr uint32_t MAX_AID = 4;
constexpr uint32_t UMC_USR_BIT = 34 - 2;
constexpr uint32_t UMC_AID_BIT = 32 - 2;
constexpr uint32_t UMC_SAMPLE_BYTE_SIZE = 8;

class CmdBuffer;
class CmdBuilder;

// helper class for building PrecExec packet
template<typename Builder>
class PrecExecBuilder {
public:
  PrecExecBuilder(Builder* builder, CmdBuffer* cmd_buffer, uint32_t target_xcc, bool is_mi300)
    : cmd_buffer_(cmd_buffer)
    , builder_{builder}
    , is_mi300_(is_mi300)
    , target_xcc_(target_xcc)
  {
    if (is_mi300_) {
      // PRED_EXEC aplies to MI300 only
      pos_ = cmd_buffer->DwSize();
      builder_->Builder::BuildPredExecPacket(cmd_buffer, target_xcc_, 0);
      initial_buff_size_ = cmd_buffer->DwSize();
    }
  }

  ~PrecExecBuilder() {
    if (is_mi300_) {
      // PRED_EXEC aplies to MI300 only
      CmdBuffer pred_exec;
      // update first PRED_EXEC packet to its correct value
      builder_->Builder::BuildPredExecPacket(&pred_exec, target_xcc_,
                                             cmd_buffer_->DwSize() - initial_buff_size_);
      const uint32_t* data = (const uint32_t*)pred_exec.Data();

      for (size_t i = 0; i < pred_exec.DwSize(); ++i)
        cmd_buffer_->Assign(pos_ + i, data[i]);
    }
  }

private:
  CmdBuffer* cmd_buffer_ {nullptr};
  Builder* builder_ {nullptr};
  bool is_mi300_ {false};
  uint32_t target_xcc_ {0};
  int pos_ {0};
  int initial_buff_size_ {0};
};

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
  virtual void Stop(CmdBuffer* cmd_buffer, const counters_vector& counters_vec) = 0;
  // Generate read profiling commands.
  // Return actual required data buffer size.
  virtual uint32_t Read(CmdBuffer* cmd_buffer, const counters_vector& counters_vec,
                        void* data_buffer) = 0;
  virtual int GetNumWGPs() = 0;
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
    auto base_index = block_des.index;
    if ((block_info->attr & CounterBlockAidAttr) && (xcc_number_ > 1))
      // MI300 all AID style instances fold back to per AID counter_reg_info
      base_index %= (block_info->instance_count / MAX_AID);
    base_index = (block_info->attr & CounterBlockExplInstAttr)
                                ? base_index * block_info->counter_count
                                : 0;
    return &(block_info->counter_reg_info[base_index]);
  }

  // helper function to convert a 32-bit address to a 64-bit SMN address.
  // Returns the address seen by UMC_MASTER_XCC of register at reg_addr on target_aid_index.
  uint64_t get_smn_addr(uint32_t reg_addr, uint32_t target_aid_index) {
    return reg_addr | ((uint64_t)1 << UMC_USR_BIT) | ((uint64_t)target_aid_index << UMC_AID_BIT);
  }

 public:
  explicit GpuPmcBuilder(const AgentInfo* agent_info): PmcBuilder(),
      se_number_(agent_info->se_num / agent_info->xcc_num),
      xcc_number_(agent_info->xcc_num),
      sarrays_per_se(agent_info->shader_arrays_per_se) {
        this->wgp_per_sa = (agent_info->cu_num/2+sarrays_per_se*se_number_-1)/(se_number_*sarrays_per_se);
        // Due to MI300 CP firmware issue we need to use mem_mapped_register mode to patch for GCEA hang.
        // Otherwise both perfcounters mode and mem_mapped_register mode should work.
        this->bUsePerfCounterMode = (xcc_number_ > 1) ? false : true;
  }

  int GetNumWGPs() override {
    if (Primitives::GFXIP_LEVEL >= 11)
      return wgp_per_sa;
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
  void Start(CmdBuffer* cmd_buffer, const counters_vector& counters_vec) override
  {
    // sdma performance monitor control value accumulator
    std::pair<reg_addr_t, uint32_t>
        sdma_select_accumulator[Primitives::SDMA_COUNTER_BLOCK_NUM_INSTANCES];
    // umc performance monitor control address
    reg_addr_t umc_control_accumulator[Primitives::UMC_COUNTER_BLOCK_NUM_INSTANCES];
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
    if (Primitives::GFXIP_LEVEL >= 11 && (counters_vec.get_attr() & (CounterBlockTcAttr|CounterBlockSqAttr))) {
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
    // UMC channels and their control register (for enable/disable) per channel
    std::map<uint32_t, uint64_t> umcchs;
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
      if (block_info->attr & CounterBlockUmcAttr) {
        const auto umc_index = counter_des.block_des.index;
        const auto target_aid_index = umc_index >> 5;
        uint64_t control_addr = (xcc_number_ > 1) ? get_smn_addr(reg_info.control_addr, target_aid_index) :
          (uint64_t)reg_info.control_addr;
        umcchs.insert({umc_index, control_addr});

        // insert master XCC PRED_EXEC packet here if it is MI300
        PrecExecBuilder<Builder> prec_exec_builder(this, cmd_buffer, VIRTUALXCCID_SELECT, xcc_number_ > 1);

        // umc counter select
        uint64_t select_addr = (xcc_number_ > 1) ? get_smn_addr(reg_info.select_addr, target_aid_index) :
          (uint64_t)reg_info.select_addr;
        Builder::BuildWritePConfigRegPacket(cmd_buffer, select_addr,
                                            Primitives::umc_select_value(counter_des));
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

    // UMC start for all UMC chnnels/instances recorded earlier
    if (!umcchs.empty())
    {
      // insert master XCC PRED_EXEC packet here if it is MI300
      PrecExecBuilder<Builder> prec_exec_builder(this, cmd_buffer, VIRTUALXCCID_SELECT, xcc_number_ > 1);
      for (const auto& i : umcchs)
      {
        uint32_t umc_index = i.first;
        uint64_t control_addr = i.second;
        // umc channel/instance clear
        Builder::BuildWritePConfigRegPacket(cmd_buffer, control_addr, Primitives::umc_disable_clear_value());
        // umc channel/instance enable
        Builder::BuildWritePConfigRegPacket(cmd_buffer, control_addr, Primitives::umc_enable_value());
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

    if (Primitives::GFXIP_LEVEL == 10)
    for (auto& elem : counters_vec) {
      if ((elem.block_info->attr & CounterBlockGRBMAttr) == 0) continue;
      const auto& reg_info = get_reg_table(elem)[elem.index];
      Builder::BuildCopyCounterDataPacket(cmd_buffer, reg_info.register_addr_lo,
                                          reg_info.register_addr_hi, data_buffer, 3);
      break;
    }

    Builder::BuildWriteWaitIdlePacket(cmd_buffer);

#if defined(_GFX10_PRIMITIVES_H_) || defined (_GFX11_PRIMITIVES_H_)
    // Stop GUS counters
    if (counters_vec.get_attr() & CounterBlockGusAttr)
      Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::GUS_PERFCOUNTER_RSLT_CNTL_ADDR,
                                         Primitives::gus_stop_value());
#endif
    // SDMA mask
    uint32_t sdma_mask = 0;
    // UMC mask
    uint32_t umc_mask = 0;
    // Iterate through the list of blocks to create PM4 packets to read counter values
    for (const auto& counter_des : counters_vec) {
      const auto* block_info = counter_des.block_info;
      const auto& block_des = counter_des.block_des;
      const auto* reg_table = get_reg_table(counter_des);
      const auto& reg_info = reg_table[counter_des.index];

      // Skip UMC counters
      if (block_info->attr & CounterBlockUmcAttr)
        continue;

      // Reset Grbm to its default state - broadcast
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                          Primitives::grbm_broadcast_value());

      if (block_info->attr & CounterBlockMcSeqAttr) {
        Builder::BuildWritePConfigRegPacket(cmd_buffer, reg_info.control_addr,
                                            Primitives::mc_seq_config_val(counter_des));
        uint32_t* data = reinterpret_cast<uint32_t*>(data_buffer) + read_counter;
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
        Builder::BuildCopyCounterDataPacket(cmd_buffer, reg_info.register_addr_lo, 0x0, data, 0x1);
        read_counter += 2;
      } else {
        const uint32_t se_end_index = (block_info->attr & CounterBlockSeAttr) ? se_number_ : 1;
        const uint32_t sa_end_index = (block_info->attr & CounterBlockSaAttr) ? 2 : 1;
        for (uint32_t se_index = 0; se_index < se_end_index; ++se_index)
        for (uint32_t sarray = 0; sarray < sa_end_index; ++sarray)
        {
          uint32_t grbm_value = Primitives::grbm_broadcast_value();
          if ((block_info->instance_count > 1) && (block_info->attr & CounterBlockSaAttr)) {
            grbm_value = Primitives::grbm_inst_se_sh_index_value(block_des.index, se_index, sarray);
          } else if ((block_info->instance_count > 1) && (block_info->attr & CounterBlockSeAttr)) {
            grbm_value = Primitives::grbm_inst_se_index_value(block_des.index, se_index);
          } else if (block_info->instance_count > 1) {
            grbm_value = Primitives::grbm_inst_index_value(block_des.index);
          } else if (block_info->attr & CounterBlockSeAttr) {
            grbm_value = Primitives::grbm_se_index_value(se_index);
          }

          bool bIsWGPcounter = Primitives::GFXIP_LEVEL >= 11 && (block_info->attr & CounterBlockSqAttr);

          if (bIsWGPcounter) {
            for (int wgp=0; wgp<wgp_per_sa; wgp++) {
              grbm_value = Primitives::grbm_se_sh_wgp_index_value(se_index, wgp, sarray);
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
  void Stop(CmdBuffer* cmd_buffer, const counters_vector& counters_vec) override
  {
    // Reset Grbm to its default state - broadcast
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
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
  
    // Issue barrier command to wait commands to complete
    if (counters_vec.get_attr() & CounterBlockCpmonAttr)
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                          Primitives::cp_perfmon_cntl_stop_value());

    // Enable RLC Perfmon Clock Gating. On Vega this
    // was disabled during Perf Cntrs collection session
    if (Primitives::GFXIP_LEVEL == 9)
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_PERFMON_CLK_CNTL_ADDR, 0);

    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
  }

  // Build PMC read PM4 comands
  uint32_t Read(CmdBuffer* cmd_buffer, const counters_vector& counters_vec, void* data_buffer) override
  {
    uint32_t read_counter = 0;
    auto counters_attr = counters_vec.get_attr();

    if (counters_vec.get_attr() & CounterBlockCpmonAttr)
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                          Primitives::cp_perfmon_cntl_read_value());

    // counters have UMC events: MI300 Loop over MI300 XCCs for each counter_des
    if (counters_attr & CounterBlockUmcAttr)
    for (const auto& counter_des : counters_vec)
    {
      const auto* block_info = counter_des.block_info;
      if (block_info->attr & CounterBlockAidAttr)
      {
        const auto& block_des = counter_des.block_des;
        const auto* reg_table = get_reg_table(counter_des);
        const auto& reg_info = reg_table[counter_des.index];
        // MI300 UMC event: insert master XCC PRED_EXEC packet here
        PrecExecBuilder<Builder> prec_exec_builder(this, cmd_buffer, VIRTUALXCCID_SELECT, xcc_number_ > 1);

        const auto umc_index = counter_des.block_des.index;
        const auto target_aid_index = umc_index >> 5;

        // Stop UMC
        auto smn_control_addr = get_smn_addr(reg_info.control_addr, target_aid_index);
        Builder::BuildWritePConfigRegPacket(cmd_buffer, smn_control_addr, Primitives::umc_stop_value());

        // Read UMC
        uint32_t* smn_data_buffer = reinterpret_cast<uint32_t*>(data_buffer) + read_counter;
        auto smn_register_addr_lo = get_smn_addr(reg_info.register_addr_lo, target_aid_index);
        auto smn_register_addr_hi = get_smn_addr(reg_info.register_addr_hi, target_aid_index);
        Builder::BuildCopyCounterDataPacket(cmd_buffer, smn_register_addr_lo, smn_register_addr_hi,
                                            smn_data_buffer, 3);
        read_counter += 2;
      }
    }

    for (size_t xcc_selected = 0; xcc_selected < xcc_number_; ++xcc_selected)
    {
      PrecExecBuilder<Builder> prec_exec_builder(this, cmd_buffer, xcc_selected, xcc_number_ > 1);
      ReadXccPackets(cmd_buffer, counters_vec, data_buffer, read_counter);
    }
 
    Builder::BuildCacheFlushPacket(cmd_buffer, size_t(data_buffer), read_counter * sizeof(uint32_t));

    // Return amount of data to read
    return read_counter * sizeof(uint32_t);
  }
};

};  // namespace pm4_builder

#endif  // SRC_PM4_PMC_BUILDER_H_
