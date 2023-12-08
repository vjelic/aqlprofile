#ifndef SRC_PM4_SQTT_BUILDER_H_
#define SRC_PM4_SQTT_BUILDER_H_

#include <stdint.h>

#include <iostream>
#include <algorithm>
#include "pm4/cmd_config.h"

#define SQTT_PERFCOUNTER_TOKEN 14

// Extension for hsa_ven_amd_aqlprofile_parameter_name_t in hsa_ven_amd_aqlprofile.h
typedef enum {
  // Trace applicable parameters
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_SIMD_SELECT = 8,    //! Set SIMD Mask (GFX9) or SIMD ID for collection (Navi)
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_OCCUPANCY = 9,      //! Set true for occupancy collection only.
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_BUFFER_SIZE = 10,   //! ATT collection max data size, in MB. Shared among shader engines.
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_PERF_MASK = 240,    //! Mask of which compute units to generate perfcounters. GFX9 only.
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_PERF_CTRL = 241,    //! Select collection period for perfcounters. GFX9 only.
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_PERFCOUNTER = 242,  //! Select perfcounter ID (SQ block) for collection. GFX9 only.
} hsa_ven_amd_aqlprofile_parameter_name_ext_t;

namespace pm4_builder {
class CmdBuffer;
class CmdBuilder;

/* Class responsible for locking PM4 packets to a specific XCC (mask).
Starts locking future packets on constructor.
Stops locking when the destructor is called.
The builder and cmdbuffer must be valid for the entire lifetime os this class. */
template<typename Builder>
class XCC_Packet_Lock {
public:
  XCC_Packet_Lock(Builder* builder, CmdBuffer* cmd_buffer, uint32_t xcc_number, uint32_t xcc_mask) {
    this->xcc_number = xcc_number;
    this->cmd_buffer = cmd_buffer;
    this->xcc_mask = xcc_mask;
    this->xcc_initial_cmd_size = (uint32_t)cmd_buffer->DwSize();
    this->builder = builder;

    if (xcc_number > 1)
      builder->Builder::BuildPredExecPacket(this->cmd_buffer, this->xcc_mask, 0);
  }
  virtual ~XCC_Packet_Lock() {
    if (xcc_number < 2) return;

    CmdBuffer pred_exec;
    builder->Builder::BuildPredExecPacket(&pred_exec, 0, 0);

    auto xcc_buf_size = cmd_buffer->DwSize() - pred_exec.DwSize() - xcc_initial_cmd_size;

    // update first PRED_EXEC packet to its correct value
    pred_exec.Clear();
    builder->Builder::BuildPredExecPacket(&pred_exec, xcc_mask, xcc_buf_size);
    const uint32_t* data = (const uint32_t*)pred_exec.Data();

    for (size_t i = 0; i < pred_exec.DwSize(); ++i)
      cmd_buffer->Assign(xcc_initial_cmd_size + i, data[i]);
  }
private:
  Builder* builder;
  CmdBuffer* cmd_buffer;
  uint32_t xcc_initial_cmd_size;
  uint32_t xcc_mask;
  uint32_t xcc_number;
};

// Thread traces status register indices to determine
// status of thread trace run
enum {
  TT_STATUS_IDX_STATUS = 0,
  TT_STATUS_IDX_CNTR = 1,
  TT_STATUS_IDX_WPTR = 2,
  TT_STATUS_IDX_ID = 3,
  TT_STATUS_IDX_MAX = 4
};

typedef uint32_t ControlType;
typedef TraceConfig ThreadTraceConfig;

// Encapsulates the various Api and structures that are used to enable
// a thread trace session and collect its data. Implementations of this
// interface program device specific registers to realize the functionality
class SqttBuilder {
 public:
  // Destructor of the thread trace service handle
  virtual ~SqttBuilder() {}
  // Builds Pm4 command stream to program hardware registers that
  // enable a thread trace session, including the issue of an event
  // to begin thread session
  virtual void Begin(CmdBuffer* cmd_buffer, const ThreadTraceConfig* config) = 0;
  // Builds Pm4 command stream to program hardware registers that
  // disable a thread trace session, including the issue of an event
  // to stop currently ongoing thread session
  virtual void End(CmdBuffer* cmd_buffer, const ThreadTraceConfig* config) = 0;

  // Returns TT_CONTROL_UTC_ERR_MASK
  virtual size_t GetUTCErrorMask() = 0;
  // Returns TT_CONTROL_FULL_MASK
  virtual size_t GetBufferFullMask() = 0;
  // Returns TT_WRITE_PTR_MASK
  virtual size_t GetWritePtrMask() = 0;
  // Returns size of block in bytes per increment in WPTR
  virtual size_t GetWritePtrBlk() = 0;
};

template <typename Builder, typename Primitives>
class GpuSqttBuilder : public SqttBuilder, protected Builder, protected Primitives {
 public:
 explicit GpuSqttBuilder(const AgentInfo* agent_info)
      : Builder(), xcc_number_(agent_info->xcc_num) {}

  // Returns TT_CONTROL_UTC_ERR_MASK
  virtual size_t GetUTCErrorMask() override { return Primitives::TT_CONTROL_UTC_ERR_MASK; };
  // Returns TT_CONTROL_FULL_MASK
  virtual size_t GetBufferFullMask() override { return Primitives::TT_CONTROL_FULL_MASK; };
  // Returns TT_WRITE_PTR_MASK
  virtual size_t GetWritePtrMask() override { return Primitives::TT_WRITE_PTR_MASK; };
  // Returns size of block in bytes per increment in WPTR
  virtual size_t GetWritePtrBlk() { return 32; };

  void StartPerfMon(CmdBuffer* cmd_buffer, const ThreadTraceConfig* config) {
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_PERFMON_CLK_CNTL_ADDR, 1);

    Builder::BuildWriteShRegPacket(cmd_buffer, Primitives::COMPUTE_PERFCOUNT_ENABLE_ADDR,
                                   Primitives::cp_perfcount_enable_value());
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                        Primitives::cp_perfmon_cntl_reset_value());

    for (int perf = 0; perf < config->n_perfcounters && perf < 8; perf++) {
      Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::sqtt_perfcounter_addr(perf),
                                        config->perfcounters[perf]);
    }
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_PERFCOUNTER_MASK_ADDR,
                                        config->perfMASK);
    Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::SQ_PERFCOUNTER_CTRL_ADDR,
                                        config->perfCTRL);
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                        Primitives::cp_perfmon_cntl_start_value());
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
  }

  void StopPerfMon(CmdBuffer* cmd_buffer) {
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                        Primitives::cp_perfmon_cntl_stop_value());
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                        Primitives::cp_perfmon_cntl_reset_value());
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_PERFMON_CLK_CNTL_ADDR, 0);
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
  }

  void Begin(CmdBuffer* cmd_buffer, const ThreadTraceConfig* config) {
    // Iterate through the list of SE's and program the register
    // for carrying address of thread trace buffer which is aligned
    // to 4KB per thread trace specification
    const uint32_t se_number_xcc = config->se_number_total / GetXCCNumber();
    const uint32_t base_step_nal = config->data_buffer_size / config->se_number_total;
    uint64_t base_addr = reinterpret_cast<uint64_t>(config->data_buffer_ptr);
    const uint32_t sqtt_size = base_step_nal >> Primitives::TT_BUFF_ALIGN_SHIFT;
    const uint32_t base_step = sqtt_size << Primitives::TT_BUFF_ALIGN_SHIFT;

    const bool legacy_mode = config->deprecated_mask &&
                             config->deprecated_tokenMask &&
                             config->deprecated_tokenMask2;

    if (Primitives::GFXIP_LEVEL == 9) {
      // Program Grbm to broadcast messages to all shader engines
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                          Primitives::grbm_broadcast_value());

      // Issue a CSPartialFlush cmd including cache flush
      if (config->concurrent == 0) Builder::BuildWriteWaitIdlePacket(cmd_buffer);
      // Program the thread trace mask - specifies SH, CU, SIMD and
      // VM Id masks to apply. Enabling SQ/SPI/REG_STALL_EN bits
      const uint32_t mask_value = (legacy_mode) ? config->deprecated_mask :
                Primitives::sqtt_mask_value(config->targetCu, config->simd_sel, config->vmIdMask);
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MASK_ADDR,
                                          mask_value);
      // Program the thread trace Perf mask
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_PERF_MASK_ADDR,
                                          Primitives::sqtt_perf_mask_value());

      if (config->n_perfcounters && config->perfCTRL) StartPerfMon(cmd_buffer, config);

      // Program the thread trace token mask
      uint32_t token_mask_value = (config->occupancy_mode) ?
                              Primitives::sqtt_token_mask_off_value() :
                              Primitives::sqtt_token_mask_on_value();
      if (config->n_perfcounters && config->perfCTRL)
        token_mask_value |= 1 << SQTT_PERFCOUNTER_TOKEN;
      if (legacy_mode) token_mask_value = config->deprecated_tokenMask;

      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_TOKEN_MASK_ADDR,
                                          token_mask_value);
      // Program the thread trace token mask2 to specify the list of instruction
      // tokens to record. Disabling INST_PC instruction tokens

      // Program the thread trace mode register, mode OFF
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MODE_ADDR,
                                          Primitives::sqtt_mode_off_value());
      // Program the HiWaterMark register to support stalling
      if (Primitives::sqtt_stalling_enabled(mask_value, token_mask_value)) {
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_HIWATER_ADDR,
                                            Primitives::SQ_THREAD_TRACE_HIWATER_VAL);
      }
      for (unsigned se_index = 0; se_index < config->se_number_total; se_index++) {
          if ( ((1 << se_index) & config->se_mask) == 0 && !config->occupancy_mode)
          {
            base_addr += base_step;
            continue;
          }

          uint32_t token_mask2_value = Primitives::sqtt_token_mask2_value();
          if (legacy_mode)
            token_mask2_value = config->deprecated_tokenMask2;
          else if ( ((1 << se_index) & config->se_mask) == 0 )
            token_mask2_value = 0;

          unsigned xcc_index = se_index / se_number_xcc;
          unsigned se_index_xcc = se_index % se_number_xcc;

          XCC_Packet_Lock<Builder> lock(this, cmd_buffer, GetXCCNumber(), xcc_index);

          // Program Grbm to direct writes to one SE
          Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                              Primitives::grbm_se_sh_index_value(se_index_xcc, 0));
          // Program tokenmask2
          Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_TOKEN_MASK2_ADDR,
                                              token_mask2_value);
          // Set SQTT STATUS to 0
          Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_STATUS_ADDR, 0);
          // Program base address of buffer to use for thread trace
          Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_BASE_ADDR,
                                              Primitives::sqtt_base_value_lo(base_addr));
          Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_BASE2_ADDR,
                                              Primitives::sqtt_base_value_hi(base_addr));
          // Program the size of thread trace buffer
          Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_SIZE_ADDR,
                                              Primitives::sqtt_buffer_size_value(base_step, 0));
          // Program the thread trace ctrl register
          Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_CTRL_ADDR,
                                              Primitives::sqtt_ctrl_value());
          // Issue a CSPartialFlush cmd including cache flush
          if (config->concurrent == 0) Builder::BuildWriteWaitIdlePacket(cmd_buffer);
          // Program the thread trace mode register, mode ON
          Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MODE_ADDR,
                                          Primitives::sqtt_mode_on_value());
          base_addr += base_step;
      }
      // Reset the GRBM to broadcast mode
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                          Primitives::grbm_broadcast_value());
      // Issue a CSPartialFlush cmd including cache flush
      if (config->concurrent == 0) Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    } else {
      for (unsigned index = 0; index < config->se_number_total; index ++) {
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                      Primitives::grbm_se_sh_index_value(index, 0));

        const unsigned baddr_hi = High32(base_addr >> Primitives::TT_BUFF_ALIGN_SHIFT);
        // Program size of buffer to use for thread trace
        Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_SIZE_ADDR,
                                      Primitives::sqtt_buffer_size_value(base_step, baddr_hi));

        // Program base address of buffer to use for thread trace
        const unsigned baddr_lo = Low32(base_addr >> Primitives::TT_BUFF_ALIGN_SHIFT);
        Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_BASE_ADDR, baddr_lo);

        // Program the thread trace mask
        const uint32_t mask_value = Primitives::sqtt_mask_value(config->targetCu, config->simd_sel, config->vmIdMask);
        Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MASK_ADDR, mask_value);

        uint32_t token_mask = ((1 << index) & config->se_mask) ?
                                Primitives::sqtt_token_mask_on_value():
                                Primitives::sqtt_token_mask_off_value();
        if (config->occupancy_mode) token_mask &= ~((1<<10) | (1<<4));
        Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_TOKEN_MASK_ADDR, token_mask);

        if (config->concurrent == 0) Builder::BuildWriteWaitIdlePacket(cmd_buffer);
        // Program the thread trace ctrl register
        const uint32_t ctrl_val = Primitives::sqtt_ctrl_value();
        Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_CTRL_ADDR, ctrl_val);

        if (config->concurrent == 0) Builder::BuildWriteWaitIdlePacket(cmd_buffer);
        base_addr += base_step;
      }
      // Reset the GRBM to broadcast mode
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                          Primitives::grbm_broadcast_value());

      Builder::BuildWriteShRegPacket(cmd_buffer, Primitives::COMPUTE_THREAD_TRACE_ENABLE_ADDR, 1);
    }
  }

  void End(CmdBuffer* cmd_buffer, const ThreadTraceConfig* config) {
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                          Primitives::grbm_broadcast_value());
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);

    if (Primitives::GFXIP_LEVEL == 9) {
      const uint32_t se_number_xcc = config->se_number_total / std::max(1u, GetXCCNumber());

      // Program the thread trace mode register to disable thread trace
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MODE_ADDR,
                                          Primitives::sqtt_mode_off_value());
      // Issue a CSPartialFlush cmd including cache flush
      Builder::BuildWriteWaitIdlePacket(cmd_buffer);

      if (config->n_perfcounters) StopPerfMon(cmd_buffer);

      // Iterate through the list of SE's and read the Status, Counter and
      // Write Pointer registers of Thread Trace subsystem
      for (unsigned se_index = 0; se_index < config->se_number_total; se_index++) {
        if ( ((1 << se_index) & config->se_mask) == 0 )
          continue;

        unsigned xcc_index = se_index / se_number_xcc;
        unsigned se_index_xcc = se_index % se_number_xcc;

        XCC_Packet_Lock<Builder> lock(this, cmd_buffer, GetXCCNumber(), xcc_index);

        // Program Grbm to direct writes to one SE
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                            Primitives::grbm_se_sh_index_value(se_index_xcc, 0));

        // Issue WaitRegMem command to wait until SQTT event has completed
        const bool func_eq = false;
        const bool mem_space = false;
        const uint32_t wait_val = 0x01;
        const uint32_t mask_val = 0x40000000L;
        const uint32_t status_offset = Primitives::SQ_THREAD_TRACE_STATUS_OFFSET;
        Builder::BuildWaitRegMemCommand(cmd_buffer, mem_space, status_offset, func_eq, mask_val,
                                        wait_val);

        ReadValues(cmd_buffer, config, se_index);
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
    } else {
      // disabling thread trace
      Builder::BuildWriteShRegPacket(cmd_buffer, Primitives::COMPUTE_THREAD_TRACE_ENABLE_ADDR, 0);

      for (unsigned index = 0; index < config->se_number_total; index ++) {
        // Program Grbm to direct writes to one SE
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                            Primitives::grbm_se_sh_index_value(index, 0));
        // Issue WaitRegMem command to wait until SQTT event has completed
        const bool func_eq = false;
        const bool mem_space = false;
        const uint32_t wait_val = 0x0; // this is reference value
        const uint32_t mask_val = ~0x3ff000;  // wait for finish_done
        const uint32_t status_offset = Primitives::SQ_THREAD_TRACE_STATUS_ADDR;
        Builder::BuildWaitRegMemCommand(cmd_buffer, mem_space, status_offset, func_eq, mask_val,
                                        wait_val);

        // Program the thread trace ctrl register to set mode to 0
        const uint32_t ctrl_val = Primitives::sqtt_ctrl_value() & 0xffffffc0;
        Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_CTRL_ADDR, ctrl_val);
        ReadValues(cmd_buffer, config, index);
      }

      // Reset the GRBM to broadcast mode
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                          Primitives::grbm_broadcast_value());
    }
  }

  void ReadValues(CmdBuffer* cmd_buffer, const ThreadTraceConfig* config, const unsigned se_index){
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

  uint32_t GetXCCNumber() const { return xcc_number_; }

  uint32_t GetBaseStep(uint32_t buffersize, uint32_t se_mask) const {
    // Get selected
    uint32_t num = 0;
    while (se_mask) {
      num += se_mask & 1;
      se_mask >>= 1;
    }
    num = std::max(num, 1u);
    // Make sure num divides buffersize
    return buffersize / num;
  }

  long GetXCCMask() const {
    const char* xcc_id = getenv("AQLPROFILE_SET_XCC_ID");
    return (xcc_id != NULL) ? strtol(xcc_id, NULL, 10) : 0xFFFF;
  }

  uint32_t xcc_number_;
  uint32_t xcc_current_cmd_size;
};

}  // namespace pm4_builder

#endif  // SRC_PM4_SQTT_BUILDER_H_
