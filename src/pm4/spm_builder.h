#ifndef SRC_PM4_SPM_BUILDER_H_
#define SRC_PM4_SPM_BUILDER_H_

#include <stdint.h>
#include <iostream>

namespace pm4_builder {
class CmdBuffer;
class CmdBuilder;
struct SpmConfig;

// SpmBuilder config
struct SpmConfig {
  uint32_t sampling_rate;
  void* buffer_ptr;
  uint32_t buffer_size;
};

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
  virtual void Begin(CmdBuffer* cmd_buffer, const SpmConfig* config) = 0;
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
    const uint32_t sampling_rate = config->sampling_rate;
    const uint64_t buffer_ptr = config->buffer_ptr;
    const uint32_t buffer_size = config->buffer_size;

    // Program Grbm to broadcast messages to all shader engines
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // SPM counters reset
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                        Primitives::cp_perfmon_cntl_spm_reset_value());
    // Initialize the [BLK]_SAMPLE_DLY_SEL registers
    // TODO: These registers are layout-dependent and allow all the blocks to receive
    //       the sample signals on a specified cycle
    // Initialize the Performance Counter Ring Structure in memory
    // TODO:
    // 1. Program the RLC_RING_BASE_H1/LO registers.
    // 2. Program the RLC_RING_SIZE register.
    // 3. Program the RLC_PERFMON_SEGMENT_SIZE register.

    // Iterate through the list of blocks to create PM4 packets to read counter values
    std::map<block_des_t, uint32_t, lt_block_des> index_map;
    uint32_t read_counter = 0;
    for (const auto& counter_des : counters_vec) {
      const auto* block_info = counter_des.block_info;
      const auto& block_des = counter_des.block_des;
      const auto& reg_info = block_info->counter_reg_info[counter_des.index];

      // Reset Grbm to its default state - broadcast
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                          Primitives::grbm_broadcast_value());

      // 4. Program the GRBM_GFX_INDEX register the appropriate SE.
      // 5. Program the RLC_[GLOBAL/SE]_MUXSEL_ADDR register with the starting address, likely zero.
      // 6. Place the WRITE_DATA packet into a queue to write the Mux Sel data into the RLC MUXSEL
      // RAM.
      //   a. Control: Engine=MEC , WR_CONFIRM=1, ADDR_INCR=0, DST_SEL=Mem-Mapped Reg
      //   b. DST_ADDR_LO = RLC_PERFMON_MUXSEL_DATA
      //   c. DST_ADDR_HI = 0x0.
      //   d. DATA = The mux selects for the SE specified in Step 3. 0xF0F0 selects the corresponding 16-
      //      bits of the GPU counter. Set unused mux-selects in the last 128-bit line with zero.
      // 7. Program the Block instance streaming performance counters in order to specify which items
      //    (events) the counters should count, if any. This is done by programming the GRBM_GFX_INDEX
      //    register to specify the type of access (broadcast or instance specific) followed by the actual
      //    register value. The first step may be to clear all counters of all instances to select zero (no
      //    counting). Then program the GRBM_GFX_INDEX, followed by the
      //    [BLK]_STRMPERFMON_SELECTx register.

      read_counter += 1;
    }
    // Reset the GRBM to broadcast mode
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
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
    // SPM counters stop
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                        Primitives::cp_perfmon_cntl_spm_stop_value());
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // SPM counters reset
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                        Primitives::cp_perfmon_cntl_spm_reset_value());
  }
};

}  // namespace pm4_builder

#endif  // SRC_PM4_SPM_BUILDER_H_
