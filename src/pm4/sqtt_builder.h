#ifndef SRC_PM4_SQTT_BUILDER_H_
#define SRC_PM4_SQTT_BUILDER_H_

#include <stdint.h>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include "pm4/cmd_config.h"
#include "src/rocprofv2_att/thread_trace_viewer_def.h"

#define SQTT_PERFCOUNTER_TOKEN (1u << 14)
#define SQTT_PERFCOUNTER_SIMD_EN (0xFu << 24)

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

struct TraceControl {
  uint32_t status;
  uint32_t cntr;
  uint32_t wptr;
  uint32_t _reserved;
};

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
  virtual void Begin(CmdBuffer* cmd_buffer, const TraceConfig* config) = 0;
  // Builds Pm4 command stream to program hardware registers that
  // disable a thread trace session, including the issue of an event
  // to stop currently ongoing thread session
  virtual void End(CmdBuffer* cmd_buffer, const TraceConfig* config) = 0;
  // Builds Pm4 command stream to program hardware registers that
  // inserts "data" into the SQTT buffer as USERDATA_2 (data_lo) and USERDATA_3 (data_hi)
  virtual hsa_status_t InsertMarker(
    CmdBuffer* cmd_buffer,
    uint32_t data,
    unsigned channel
  ) = 0;

  // returns the target CU
  virtual int GetTargetCU(int SE) const = 0;
  virtual uint64_t GetSEmask() const = 0;
  virtual uint64_t GetSEBaseAddr(int SE) const = 0;
  virtual uint64_t GetCapacity(int SE) const = 0;

  // Returns TT_CONTROL_UTC_ERR_MASK
  virtual size_t GetUTCErrorMask() const = 0;
  // Returns TT_CONTROL_FULL_MASK
  virtual size_t GetBufferFullMask() const = 0;
  // Returns TT_WRITE_PTR_MASK
  virtual size_t GetWritePtrMask() const = 0;
  // Returns size of block in bytes per increment in WPTR
  virtual size_t GetWritePtrBlk() const = 0;
  // Returns number of bits used for TTrace buffer alignement (e.g. 12 for 4KB alignment)
  virtual size_t BufferAlignment() const = 0;
  // Returns BaseStep for TTrace buffer.
  virtual uint64_t GetBaseStep(uint64_t buffersize, uint64_t se_mask) const = 0;
};

template <typename Builder, typename Primitives>
class GpuSqttBuilder : public SqttBuilder, protected Builder, protected Primitives {
 public:
 explicit GpuSqttBuilder(const AgentInfo* agent_info)
    : Builder(), xcc_number_(agent_info->xcc_num), se_number_total(agent_info->se_num) {}

  // returns the target CU for a particular SE
  virtual int GetTargetCU(int SE) const override { return target_cu_per_se.at(SE); };
  virtual uint64_t GetSEmask() const override { return se_mask; };
  virtual uint64_t GetSEBaseAddr(int SE) const override { return se_base_addresses.at(SE); }
  virtual uint64_t GetCapacity(int SE) const override {
    return (GetTargetCU(SE) >= 0) ? capacity_per_se : capacity_per_disabled_se;
  }

  // Returns TT_CONTROL_UTC_ERR_MASK
  virtual size_t GetUTCErrorMask() const override { return Primitives::TT_CONTROL_UTC_ERR_MASK; };
  // Returns TT_CONTROL_FULL_MASK
  virtual size_t GetBufferFullMask() const override { return Primitives::TT_CONTROL_FULL_MASK; };
  // Returns TT_WRITE_PTR_MASK
  virtual size_t GetWritePtrMask() const override { return Primitives::TT_WRITE_PTR_MASK; };
  // Returns size of block in bytes per increment in WPTR
  virtual size_t GetWritePtrBlk() const override { return 32; };
  // Returns number of bits used for TTrace buffer alignement (e.g. 12 for 4KB alignment)
  virtual size_t BufferAlignment() const override { return Primitives::TT_BUFF_ALIGN_SHIFT; }

  void SetGRBMToBroadcast(CmdBuffer* cmd_buffer)
  {
    auto broadcast = Primitives::grbm_broadcast_value();
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR, broadcast);
  }

  void Select_GRBM_SE_SH0(CmdBuffer* cmd_buffer, int se_index)
  {
    auto sh0 = Primitives::grbm_se_sh_index_value(se_index, 0);
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR, sh0);
  }

  void StartPerfMon(CmdBuffer* cmd_buffer, const TraceConfig* config) {
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_PERFMON_CLK_CNTL_ADDR, 1);

    Builder::BuildWriteShRegPacket(cmd_buffer, Primitives::COMPUTE_PERFCOUNT_ENABLE_ADDR,
                                   Primitives::cp_perfcount_enable_value());
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                        Primitives::cp_perfmon_cntl_reset_value());

    for (int perf = 0; perf < config->n_perfcounters && perf < 8; perf++) {
      Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::sqtt_perfcounter_addr(perf),
                                          config->perfcounters[perf] | SQTT_PERFCOUNTER_SIMD_EN);
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

  void Begin(CmdBuffer* cmd_buffer, const TraceConfig* config) override
  {
    // Iterate through the list of SE's and program the register
    // for carrying address of thread trace buffer which is aligned
    // to 4KB per thread trace specification
    const uint64_t se_number_xcc = se_number_total / GetXCCNumber();
    uint64_t base_addr = reinterpret_cast<uint64_t>(config->data_buffer_ptr);
    const uint64_t base_step = GetBaseStep(config->data_buffer_size, config->se_mask);
    this->capacity_per_se = base_step;
    this->capacity_per_disabled_se = 1 << Primitives::TT_BUFF_ALIGN_SHIFT;

    const bool legacy_mode = config->deprecated_mask &&
                             config->deprecated_tokenMask &&
                             config->deprecated_tokenMask2;

    this->se_mask = config->se_mask;
    for (uint64_t se_index=0; se_index < se_number_total; se_index++)
    {
      bool bMaskedIn = ((1 << se_index) & se_mask) != 0;
      target_cu_per_se[se_index] = bMaskedIn ? config->targetCu : -1;
    }

    if (Primitives::GFXIP_LEVEL == 9) {
      // Program Grbm to broadcast messages to all shader engines
      SetGRBMToBroadcast(cmd_buffer);

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
                              Primitives::sqtt_token_mask_occupancy_value() :
                              Primitives::sqtt_token_mask_on_value();
      if (config->n_perfcounters && config->perfCTRL) token_mask_value |= SQTT_PERFCOUNTER_TOKEN;
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
      for (uint64_t se_index = 0; se_index < se_number_total; se_index++)
      {
          se_base_addresses[se_index] = base_addr;
          if (target_cu_per_se.at(se_index) < 0)
          {
            base_addr += capacity_per_disabled_se;
            continue;
          }

          uint32_t token_mask2_value = Primitives::sqtt_token_mask2_value();
          if (legacy_mode)
            token_mask2_value = config->deprecated_tokenMask2;
          else if ( ((1 << se_index) & config->se_mask) == 0 )
            token_mask2_value = 0;

          uint64_t xcc_index = se_index / se_number_xcc;
          uint64_t se_index_xcc = se_index % se_number_xcc;

          XCC_Packet_Lock<Builder> lock(this, cmd_buffer, GetXCCNumber(), xcc_index);

          // Program Grbm to direct writes to one SE
          Select_GRBM_SE_SH0(cmd_buffer, se_index_xcc);
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
      SetGRBMToBroadcast(cmd_buffer);
    } else {
      SetGRBMToBroadcast(cmd_buffer);
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_STATUS_ADDR, 0);

      for (uint64_t index = 0; index < se_number_total; index ++)
      {
        se_base_addresses[index] = base_addr;
        bool bMaskedIn = target_cu_per_se.at(index) >= 0;

        const unsigned baddr_lo = Low32(base_addr >> Primitives::TT_BUFF_ALIGN_SHIFT);
        const unsigned baddr_hi = High32(base_addr >> Primitives::TT_BUFF_ALIGN_SHIFT);
        const uint32_t sqtt_size = bMaskedIn ? base_step : capacity_per_disabled_se;
        const uint32_t sqtt_reg_size = Primitives::sqtt_buffer_size_value(sqtt_size, baddr_hi);
        const uint32_t ctrl_val = Primitives::sqtt_ctrl_value();
        
        Select_GRBM_SE_SH0(cmd_buffer, index);

        // Program size of buffer to use for thread trace
        WriteConfigPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_SIZE_ADDR, sqtt_reg_size);
        // Program base address of buffer to use for thread trace
        WriteConfigPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_BASE_ADDR, baddr_lo);

        // Program the thread trace mask
        const uint32_t mask_value = Primitives::sqtt_mask_value(config->targetCu, config->simd_sel, config->vmIdMask);
        WriteConfigPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MASK_ADDR, mask_value);

        uint32_t token_mask = (config->occupancy_mode) ?
                                Primitives::sqtt_token_mask_occupancy_value():
                                Primitives::sqtt_token_mask_on_value();
        if (((1 << index) & config->se_mask) == 0)
          token_mask = Primitives::sqtt_token_mask_off_value();

        WriteConfigPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_TOKEN_MASK_ADDR, token_mask);
        // Program the thread trace ctrl register
        WriteConfigPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_CTRL_ADDR, ctrl_val);

        base_addr += sqtt_size;
      }
      // Reset the GRBM to broadcast mode
      SetGRBMToBroadcast(cmd_buffer);
      Builder::BuildWriteShRegPacket(cmd_buffer, Primitives::COMPUTE_THREAD_TRACE_ENABLE_ADDR, 1);
    }
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);

    thread_trace_viewer_user_data_header_fourcc fourcc;
    fourcc.opcode = thread_trace_viewer_user_data_opcode_fourcc;
    fourcc.char2 = 'R';
    fourcc.char3 = 'O';
    fourcc.char4 = 'C';
    auto userdata_channel = Primitives::SQ_THREAD_TRACE_USERDATA_2;

    Builder::BuildWriteUConfigRegPacket(cmd_buffer, userdata_channel, fourcc.u32All);

    thread_trace_viewer_user_data_header_version version;
    version.opcode = thread_trace_viewer_user_data_opcode_version;
    version.major = TT_VIEWER_USER_DATA_FORMAT_MAJOR_VERSION;
    version.minor = TT_VIEWER_USER_DATA_FORMAT_MINOR_VERSION;

    Builder::BuildWriteUConfigRegPacket(cmd_buffer, userdata_channel, version.u32All);
  }

  void End(CmdBuffer* cmd_buffer, const TraceConfig* config) override {
    SetGRBMToBroadcast(cmd_buffer);
    // Issue a CSPartialFlush cmd including cache flush
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);

    if (Primitives::GFXIP_LEVEL == 9) {
      const uint32_t se_number_xcc = se_number_total / std::max(1u, GetXCCNumber());

      // Program the thread trace mode register to disable thread trace
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MODE_ADDR,
                                          Primitives::sqtt_mode_off_value());
      // Issue a CSPartialFlush cmd including cache flush
      Builder::BuildWriteWaitIdlePacket(cmd_buffer);

      if (config->n_perfcounters) StopPerfMon(cmd_buffer);

      // Iterate through the list of SE's and read the Status, Counter and
      // Write Pointer registers of Thread Trace subsystem
      for (size_t se_index = 0; se_index < se_number_total; se_index++) {
        if (target_cu_per_se.at(se_index) < 0)
          continue;

        size_t xcc_index = se_index / se_number_xcc;
        size_t se_index_xcc = se_index % se_number_xcc;

        XCC_Packet_Lock<Builder> lock(this, cmd_buffer, GetXCCNumber(), xcc_index);

        // Program Grbm to direct writes to one SE
        Select_GRBM_SE_SH0(cmd_buffer, se_index_xcc);

        // Issue WaitRegMem command to wait until SQTT event has completed
        const uint32_t mask_val = Primitives::sqtt_busy_mask();
        const uint32_t status_offset = Primitives::SQ_THREAD_TRACE_STATUS_OFFSET;
        Builder::BuildWaitRegMemCommand(cmd_buffer, false, status_offset, false, mask_val, 1);

        ReadValues(cmd_buffer, config, se_index);
      }
      // Reset the GRBM to broadcast mode
      SetGRBMToBroadcast(cmd_buffer);
      // Initialize cache flush request object
      Builder::BuildCacheFlushPacket(cmd_buffer, size_t(config->control_buffer_ptr), config->control_buffer_size);
      Builder::BuildCacheFlushPacket(cmd_buffer, size_t(config->data_buffer_size), config->data_buffer_size);
      // Program zero size of thread trace buffer
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_SIZE_ADDR,
                                          Primitives::sqtt_zero_size_value());
      // Program the thread trace ctrl register
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_CTRL_ADDR,
                                          Primitives::sqtt_ctrl_value());
      // Issue a CSPartialFlush cmd including cache flush
      Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    } else {
      SetGRBMToBroadcast(cmd_buffer);
      Builder::BuildWriteShRegPacket(cmd_buffer, Primitives::COMPUTE_THREAD_TRACE_ENABLE_ADDR, 0);

      {
        // Wait for FINISH_PENDING
        const uint32_t mask_val = Primitives::sqtt_pending_mask();
        const uint32_t status_offset = Primitives::SQ_THREAD_TRACE_STATUS_ADDR;
        Builder::BuildWaitRegMemCommand(cmd_buffer, false, status_offset, true, mask_val, 0);
      }

      // Program the thread trace ctrl register to set mode to 0
      const uint32_t ctrl_val = Primitives::sqtt_ctrl_value() & 0xffffffc0;
      WriteConfigPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_CTRL_ADDR, ctrl_val);
  
      {
        // Wait until SQTT_BUSY is 0
        const uint32_t mask_val = Primitives::sqtt_busy_mask();
        const uint32_t status_offset = Primitives::SQ_THREAD_TRACE_STATUS_ADDR;
        Builder::BuildWaitRegMemCommand(cmd_buffer, false, status_offset, true, mask_val, 0);
      }

      for (uint64_t index = 0; index < se_number_total; index ++)
      {
        Select_GRBM_SE_SH0(cmd_buffer, index);
        ReadValues(cmd_buffer, config, index);
      }

      // Reset the GRBM to broadcast mode
      SetGRBMToBroadcast(cmd_buffer);
    }

    if (Primitives::GFXIP_LEVEL != 10)
        Builder::BuildCacheFlushPacket(cmd_buffer, size_t(config->control_buffer_ptr), config->control_buffer_size);
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);
  }

  void ReadValues(CmdBuffer* cmd_buffer, const TraceConfig* config, size_t se_index)
  {
    // Retrieve the values from various status registers
    auto& control = reinterpret_cast<TraceControl*>(config->control_buffer_ptr)[se_index];

    Builder::BuildCopyRegDataPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_STATUS_ADDR,
                                  &control.status, Primitives::COPY_DATA_SEL_COUNT_1DW_PRM, true);

    Builder::BuildCopyRegDataPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_CNTR_ADDR,
                                  &control.cntr, Primitives::COPY_DATA_SEL_COUNT_1DW_PRM, true);

    Builder::BuildCopyRegDataPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_WPTR_ADDR,
                                  &control.wptr, Primitives::COPY_DATA_SEL_COUNT_1DW_PRM, true);
  }

  uint32_t GetXCCNumber() const { return xcc_number_; }

  uint64_t PopCount(uint64_t se_mask) const
  {
    uint64_t num_enabled = 0;
    while (se_mask) {
      num_enabled += se_mask & 1;
      se_mask >>= 1;
    }
    return std::max<uint64_t>(num_enabled, 1u);
  }

  virtual uint64_t GetBaseStep(uint64_t buffersize, uint64_t se_mask) const override
  {
    // Get selected
    uint64_t num_enabled = PopCount(se_mask);
    int64_t num_disabled = (64 - num_enabled)<<12;
    // Make sure num divides buffersize
    int64_t buffer_per_se = std::max<int64_t>(0, buffersize - num_disabled) / num_enabled;
    return uint64_t(buffer_per_se) & ~((1<<Primitives::TT_BUFF_ALIGN_SHIFT)-1);
  }

  virtual hsa_status_t InsertMarker(
    CmdBuffer* cmd_buffer,
    uint32_t data,
    unsigned channel
  ) override
  {
    ttv_user_data_header_codeobj header{};
    header.opcode = thread_trace_viewer_user_data_opcode_codeobj;
    header.type = channel;
    auto userdata_channel = Primitives::SQ_THREAD_TRACE_USERDATA_2;

    SetGRBMToBroadcast(cmd_buffer);
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, userdata_channel, header.u32All);
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, userdata_channel, data);
    return HSA_STATUS_SUCCESS;
  }

  virtual void WriteConfigPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) {
    if (Primitives::GFXIP_LEVEL == 11)
      Builder::BuildWriteUConfigRegPacket(cmdbuf, addr, value);
    else
      Builder::BuildWritePConfigRegPacket(cmdbuf, addr, value);

  }

  size_t se_number_total;
  size_t xcc_number_;
  size_t xcc_current_cmd_size;
  uint64_t se_mask;
  uint64_t capacity_per_se;
  uint64_t capacity_per_disabled_se;
  std::unordered_map<int, int> target_cu_per_se;
  std::unordered_map<int, uint64_t> se_base_addresses;
};

}  // namespace pm4_builder

#endif  // SRC_PM4_SQTT_BUILDER_H_
