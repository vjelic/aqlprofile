#ifndef SRC_PM4_SQTT_BUILDER_H_
#define SRC_PM4_SQTT_BUILDER_H_

#include <stdint.h>

namespace pm4_builder {
class CmdBuffer;
class CmdBuilder;
struct ThreadTraceConfig;

enum {
  // Mask to check if SQTT buffer is wrapped
  TT_CONTROL_WRAP_MASK = 0x80000000,
  // Move them as static variables later on
  TT_WRITE_PTR_MASK = 0x3FFFFFFF,
  // Size of block in bytesper increment in WPTR
  TT_WRITE_PTR_BLK = 32,
};

// Thread traces status register indices to determine
// status of thread trace run
enum {
  TT_STATUS_IDX_STATUS = 0,
  TT_STATUS_IDX_CNTR = 1,
  TT_STATUS_IDX_WPTR = 2,
  TT_STATUS_IDX_MAX = 3
};

typedef uint32_t ControlType;

// SqttBuilder config
struct ThreadTraceConfig {
  uint32_t targetCu;
  uint32_t vmIdMask;
  uint32_t mask;
  uint32_t tokenMask;
  uint32_t tokenMask2;

  void* control_buffer_ptr;
  void* data_buffer_ptr;
  uint32_t data_buffer_size;

  // number of Shader Engines on the device
  uint32_t se_number;
};

// Encapsulates the various Api and structures that are used to enable
// a thread trace session and collect its data. Implementations of this
// interface program device specific registers to realize the functionality
class SqttBuilder {
 public:
  // Destructor of the thread trace service handle
  virtual ~SqttBuilder(){};
  // Builds Pm4 command stream to program hardware registers that
  // enable a thread trace session, including the issue of an event
  // to begin thread session
  virtual void Begin(CmdBuffer* cmd_buffer, const ThreadTraceConfig* config) = 0;
  // Builds Pm4 command stream to program hardware registers that
  // disable a thread trace session, including the issue of an event
  // to stop currently ongoing thread session
  virtual void End(CmdBuffer* cmd_buffer, const ThreadTraceConfig* config) = 0;
};

template <typename Builder, typename Primitives>
class GpuSqttBuilder : public SqttBuilder, protected Builder, protected Primitives {
 public:
  void Begin(CmdBuffer* cmd_buffer, const ThreadTraceConfig* config) {
    // Program Grbm to broadcast messages to all shader engines
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // Program the thread trace mask - specifies SH, CU, SIMD and
    // VM Id masks to apply. Enabling SQ/SPI/REG_STALL_EN bits
    const uint32_t mask_value = (config->mask)
        ? config->mask
        : Primitives::sqtt_mask_value(config->targetCu, config->vmIdMask);
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MASK_ADDR,
                                        mask_value);
    // Program the thread trace Perf mask
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_PERF_MASK_ADDR,
                                        Primitives::sqtt_perf_mask_value());
    // Program the thread trace token mask
    const uint32_t token_mask_value =
        (config->tokenMask) ? config->tokenMask : Primitives::sqtt_token_mask_value();
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_TOKEN_MASK_ADDR,
                                        token_mask_value);
    // Program the thread trace token mask2 to specify the list of instruction
    // tokens to record. Disabling INST_PC instruction tokens
    const uint32_t token_mask2_value =
        (config->tokenMask2) ? config->tokenMask2 : Primitives::sqtt_token_mask2_value();
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_TOKEN_MASK2_ADDR,
                                        token_mask2_value);
    // Program the thread trace mode register, mode OFF
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MODE_ADDR,
                                        Primitives::sqtt_mode_off_value());
    // Program the HiWaterMark register to support stalling
    if (Primitives::sqtt_stalling_enabled(mask_value, token_mask_value)) {
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_HIWATER_ADDR,
                                          Primitives::SQ_THREAD_TRACE_HIWATER_VAL);
    }
    // Iterate through the list of SE's and program the register
    // for carrying address of thread trace buffer which is aligned
    // to 4KB per thread trace specification
    uint64_t base_addr = reinterpret_cast<uint64_t>(config->data_buffer_ptr);
    const uint32_t base_step = config->data_buffer_size / config->se_number;
    const uint32_t sqtt_size = Primitives::sqtt_size_value(base_step);
    for (unsigned se_index = 0; se_index < config->se_number; ++se_index, base_addr += base_step) {
      // Program Grbm to direct writes to one SE
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                          Primitives::grbm_se_sh_index_value(se_index, 0));
      // Program base address of buffer to use for thread trace
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_BASE_ADDR,
                                          Primitives::sqtt_base_value(base_addr));
      // Program the size of thread trace buffer
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_SIZE_ADDR,
                                          sqtt_size);
      // Program the thread trace ctrl register
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_CTRL_ADDR,
                                          Primitives::sqtt_ctrl_value());
    }
    // Reset the GRBM to broadcast mode
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // Program the thread trace mode register, mode ON
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MODE_ADDR,
                                        Primitives::sqtt_mode_on_value());
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
  }

  void End(CmdBuffer* cmd_buffer, const ThreadTraceConfig* config) {
    // Program Grbm to broadcast messages to all shader engines
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // Program the thread trace mode register to disable thread trace
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MODE_ADDR,
                                        Primitives::sqtt_mode_off_value());
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // Iterate through the list of SE's and read the Status, Counter and
    // Write Pointer registers of Thread Trace subsystem
    for (unsigned se_index = 0; se_index < config->se_number; se_index++) {
      // Program Grbm to direct writes to one SE
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                          Primitives::grbm_se_sh_index_value(se_index, 0));

      // Issue WaitRegMem command to wait until SQTT event has completed
      const bool func_eq = false;
      const bool mem_space = false;
      const uint32_t wait_val = 0x01;
      const uint32_t mask_val = 0x40000000L;
      const uint32_t status_offset = Primitives::SQ_THREAD_TRACE_STATUS_OFFSET;
      Builder::BuildWaitRegMemCommand(cmd_buffer, mem_space, status_offset, func_eq, mask_val,
                                      wait_val);

      // Retrieve the values from various status registers
      ControlType* control_buffer = reinterpret_cast<ControlType*>(config->control_buffer_ptr);
      const uint32_t status_idx = ((TT_STATUS_IDX_MAX * se_index) + TT_STATUS_IDX_STATUS);
      Builder::BuildCopyRegDataPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_STATUS_ADDR,
                                      control_buffer + status_idx,
                                      Primitives::COPY_DATA_SEL_COUNT_1DW_PRM, true);
      const uint32_t cntr_idx = ((TT_STATUS_IDX_MAX * se_index) + TT_STATUS_IDX_CNTR);
      Builder::BuildCopyRegDataPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_CNTR_ADDR,
                                      control_buffer + cntr_idx,
                                      Primitives::COPY_DATA_SEL_COUNT_1DW_PRM, true);
      const uint32_t wptr_idx = ((TT_STATUS_IDX_MAX * se_index) + TT_STATUS_IDX_WPTR);
      Builder::BuildCopyRegDataPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_WPTR_ADDR,
                                      control_buffer + wptr_idx,
                                      Primitives::COPY_DATA_SEL_COUNT_1DW_PRM, true);
    }
    // Reset the GRBM to broadcast mode
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Initialize cache flush request object
    Builder::BuildCacheFlushPacket(cmd_buffer);
    // Program zero size of thread trace buffer
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_SIZE_ADDR,
                                        Primitives::sqtt_zero_size_value());
    // Program the thread trace ctrl register
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_CTRL_ADDR,
                                        Primitives::sqtt_ctrl_value());
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
  }
};

}  // pm4_builder

#endif  // SRC_PM4_SQTT_BUILDER_H_
