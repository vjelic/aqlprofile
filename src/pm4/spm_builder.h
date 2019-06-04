#ifndef SRC_PM4_SPM_BUILDER_H_
#define SRC_PM4_SPM_BUILDER_H_

#include <stdint.h>
#include <iostream>

#include "pm4/cmd_config.h"

namespace pm4_builder {
class CmdBuffer;
class CmdBuilder;

// SpmBuilder config
typedef TraceConfig SpmConfig;

#if 0
// WRITE_DATA PM4 command
static void write_data(CmdBuffer* cb, uint32_t reg, uint32_t *data, size_t dwCount) {
    APPEND_COMMAND_WRAPPER(cb, PM4_TYPE3_HDR(IT_WRITE_DATA, dwCount + 4));
    APPEND_COMMAND_WRAPPER(cb, (uint32_t)((1u << 16) | (1u << 20u)));  // addr_inc, write confirm, mem mapped register and me
    APPEND_COMMAND_WRAPPER(cb, reg);
    APPEND_COMMAND_WRAPPER(cb, (uint32_t)0u);
    for (size_t i = 0; i < dwCount; i++) {
        APPEND_COMMAND_WRAPPER(cb, data[i]);
    }
}
#endif

// Encapsulates the various Api and structures that are used to enable
// a SPM session and collect its data. Implementations of this
// interface program device specific registers to realize the functionality
class SpmBuilder {
 public:
  // Destructor of the SPM service handle
  virtual ~SpmBuilder() {}
  // Builds Pm4 command stream to program hardware registers that
  // enable a SPM session, including the issue of an event
  // to begin thread session
  virtual void Begin(CmdBuffer* cmd_buffer, const SpmConfig* config, const counters_vector& counters_vec) = 0;
  // Builds Pm4 command stream to program hardware registers that
  // disable a SPM session, including the issue of an event
  // to stop currently ongoing thread session
  virtual void End(CmdBuffer* cmd_buffer, const SpmConfig* config) = 0;
};

template <typename Builder, typename Primitives>
class GpuSpmBuilder : public SpmBuilder, protected Builder, protected Primitives {
 public:
  void Begin(CmdBuffer* cmd_buffer, const SpmConfig* config, const counters_vector& counters_vec) {
    // SPM parameters
    const uint32_t sampling_rate = config->sampleRate;
    const uint64_t buffer_ptr = reinterpret_cast<uint64_t>(config->data_buffer_ptr);
    const uint32_t buffer_size = config->data_buffer_size;

    // Program Grbm to broadcast messages to all shader engines
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // SPM counters reset
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                        Primitives::cp_perfmon_cntl_reset_value());

    // Initialize the [BLK]_SAMPLE_DLY_SEL registers
    // These registers are layout-dependent and allow all the blocks to receive
    // the sample signals on a specified cycle
    // global: CPC, CPF, GDS, TCC, TCA
    // SE: SX, TA, TD, TCP, SPI

    // Initialize the Performance Counter Ring Structure in memory
    // 1. Program the RLC_RING_BASE_H1/LO registers.
    // 2. Program the RLC_RING_SIZE register.
    // 3. Program the RLC_PERFMON_SEGMENT_SIZE register.
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_PERFMON_CNTL__ADDR,
                                        Primitives::rlc_spm_perfmon_cntl_value(sampling_rate));
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_PERFMON_RING_BASE_LO__ADDR, buffer_ptr);
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_PERFMON_RING_BASE_HI__ADDR, buffer_ptr >> 32);
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_PERFMON_RING_SIZE__ADDR, buffer_size);

    // 4. Program the GRBM_GFX_INDEX register the appropriate SE.
    // 5. Program the RLC_[GLOBAL/SE]_MUXSEL_ADDR register with the starting address, likely zero.
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_SE_MUXSEL_ADDR__ADDR, 0);
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_GLOBAL_MUXSEL_ADDR__ADDR, 0);
    // Register timestamp
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_GLOBAL_MUXSEL_DATA__ADDR, 0xf0f0f0f0);
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_GLOBAL_MUXSEL_DATA__ADDR, 0xf0f0f0f0);

    // Iterate through the list of blocks to create PM4 packets to read counter values
    bool is_spm_inited = false;
    uint32_t muxsel_data = 0;
    uint32_t muxsel_count = 0;
    uint32_t global_count = 4;
    uint32_t se_count = 0;
    for (const auto& counter_des : counters_vec) {
      const auto* block_info = counter_des.block_info;
      const auto& block_des = counter_des.block_des;
      const auto& reg_info = block_info->counter_reg_info[counter_des.index];

      if (block_des.id != Primitives::SQ_BLOCK_ID) {
        printf("SPM implemented for SQ\n");
        abort();
      }

      if (is_spm_inited == false) {
        is_spm_inited = true;
        for (int i = 0; i < 4; i++) {
          Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                              Primitives::grbm_se_index_value(i));
          Builder::BuildWriteUConfigRegPacket(cmd_buffer, block_info->delay_info[i].reg,
                                              block_info->delay_info[i].val);
        }
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                            Primitives::grbm_broadcast_value());
      }

      // 6. Place the WRITE_DATA packet into a queue to write the Mux Sel data into the RLC MUXSEL
      // RAM.
      //   a. Control: Engine=MEC , WR_CONFIRM=1, ADDR_INCR=0, DST_SEL=Mem-Mapped Reg
      //   b. DST_ADDR_LO = RLC_PERFMON_MUXSEL_DATA
      //   c. DST_ADDR_HI = 0x0.
      //   d. DATA = The mux selects for the SE specified in Step 3. 0xF0F0 selects the corresponding 16-
      //      bits of the GPU counter. Set unused mux-selects in the last 128-bit line with zero.
      const uint32_t odd_muxsel = (muxsel_count & 1);
      muxsel_count += 1;
      if (odd_muxsel == 0) muxsel_data = 0;
      muxsel_data = Primitives::rlc_spm_muxsel_data(muxsel_data, counter_des,
                                                    9 /*Primitives::SQ_BLOCK_SPM_ID*/, odd_muxsel);
      if (block_info->attr & CounterBlockSeAttr) {
        se_count += 1;
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_SE_MUXSEL_DATA__ADDR, muxsel_data);
      } else {
        global_count += 1;
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_GLOBAL_MUXSEL_DATA__ADDR, muxsel_data);
      }

      // 7. Program the Block instance streaming performance counters in order to specify which items
      //    (events) the counters should count, if any. This is done by programming the GRBM_GFX_INDEX
      //    register to specify the type of access (broadcast or instance specific) followed by the actual
      //    register value. The first step may be to clear all counters of all instances to select zero (no
      //    counting). Then program the GRBM_GFX_INDEX, followed by the
      //    [BLK]_STRMPERFMON_SELECTx register.
      // Setup counters
      // Configure SQ block
      if (block_info->attr & CounterBlockSqAttr) {
        Builder::BuildWriteConfigRegPacket(cmd_buffer, reg_info.select_addr,
                                           Primitives::sq_spm_select_value(counter_des));
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_PERFCOUNTER_MASK_ADDR,
                                            Primitives::sq_mask_value(counter_des));
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, reg_info.control_addr,
                                            Primitives::sq_control_value(counter_des));
      }
    }
    // Finish MUXSEL RAM
    // Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_SE_MUXSEL_DATA__ADDR, 0xffff);
    // se_count++;

    se_count = ((se_count + 1) >> 1);
    global_count = ((global_count + 1) >> 1);
    const uint32_t muxsel_line_size = 4;
    const uint32_t muxsel_line_mask = muxsel_line_size - 1;
    const uint32_t se_data_remain = (muxsel_line_size - (se_count & muxsel_line_mask)) & muxsel_line_mask;
    const uint32_t global_data_remain = (muxsel_line_size - (global_count & muxsel_line_mask)) & muxsel_line_mask;
    for (uint32_t i = 0; i < se_data_remain; i++) {
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_SE_MUXSEL_DATA__ADDR, 0);
    }
    for (uint32_t i = 0; i < global_data_remain; i++) {
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_GLOBAL_MUXSEL_DATA__ADDR, 0);
    }
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_GLOBAL_MUXSEL_ADDR__ADDR, 0);
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_SE_MUXSEL_ADDR__ADDR, 0);
    // Set segment size
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_SPM_PERFMON_SEGMENT_SIZE__ADDR,
                                        Primitives::rlc_spm_perfmon_segment_size_value(global_count, se_count));
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // Program Compute Perfcount Enable register to support perf counting
    Builder::BuildWriteShRegPacket(cmd_buffer, Primitives::COMPUTE_PERFCOUNT_ENABLE_ADDR,
                                   Primitives::cp_perfcount_enable_value());
    // SPM counters start
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                        Primitives::cp_perfmon_cntl_spm_start_value());
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
  }

  void End(CmdBuffer* cmd_buffer, const SpmConfig* config) {
    // Program Grbm to broadcast messages to all shader engines
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // SPM counters stop
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                        Primitives::cp_perfmon_cntl_spm_stop_value());
    // SPM counters reset
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                        Primitives::cp_perfmon_cntl_reset_value());
  }
};

}  // namespace pm4_builder

#endif  // SRC_PM4_SPM_BUILDER_H_
