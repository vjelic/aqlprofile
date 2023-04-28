#ifndef SRC_PM4_SQTT_BUILDER_H_
#define SRC_PM4_SQTT_BUILDER_H_

#include <stdint.h>

#include <iostream>

#include "pm4/cmd_config.h"

// Extension for hsa_ven_amd_aqlprofile_parameter_name_t in hsa_ven_amd_aqlprofile.h
typedef enum {
  // Trace applicable parameters
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_PERF_MASK = 240,
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_PERF_CTRL = 241,
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_PERFCOUNTER = 242
} hsa_ven_amd_aqlprofile_parameter_name_ext_t;

namespace pm4_builder {
class CmdBuffer;
class CmdBuilder;

enum {
  // SE number
  SE_NUM_MAX = 8,
  // SE-mask item mask
  SE_VECTOR_MASK = SE_NUM_MAX - 1,
  // SE-mask item shift
  SE_VECTOR_SHIFT = 3  // LOG2(SE_NUM_MAX)
};

enum {
  // Mask to check if memory error was received
  TT_CONTROL_UTC_ERR_MASK = 0x10000000,
  // Mask to check if SQTT buffer is wrapped
  TT_CONTROL_FULL_MASK = 0x80000000,
  // Move them as static variables later on
  TT_WRITE_PTR_MASK = 0x3FFFFFFF,
  // Size of block in bytesper increment in WPTR
  TT_WRITE_PTR_BLK = 32
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
};

template <typename Builder, typename Primitives>
class GpuSqttBuilder : public SqttBuilder, protected Builder, protected Primitives {
 public:
  void StartPerfMon(CmdBuffer* cmd_buffer, const ThreadTraceConfig* config) {
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::RLC_PERFMON_CLK_CNTL_ADDR, 1);

    Builder::BuildWriteShRegPacket(cmd_buffer, Primitives::COMPUTE_PERFCOUNT_ENABLE_ADDR,
                                   Primitives::cp_perfcount_enable_value());
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::CP_PERFMON_CNTL_ADDR,
                                        Primitives::cp_perfmon_cntl_reset_value());

    for (int perf = 0; perf < config->n_perfcounters && perf < 16; perf++) {
      Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::sqtt_perfcounter_addr(perf),
                                        config->perfcounters[perf]);
    }
    uint32_t perfmask = config->perfMASK ? config->perfMASK : 0xFFFFFFFF;
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_PERFCOUNTER_MASK_ADDR,
                                        perfmask);
    uint32_t perfctrl = config->perfCTRL ? config->perfCTRL : 0xFFFF0F7F;
    Builder::BuildWriteConfigRegPacket(cmd_buffer, Primitives::SQ_PERFCOUNTER_CTRL_ADDR,
                                        perfctrl);
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

  // ###########


  void Begin(CmdBuffer* cmd_buffer, const ThreadTraceConfig* config) {
   if (Primitives::GFXIP_LEVEL == 9){
    // Program Grbm to broadcast messages to all shader engines
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                        Primitives::grbm_broadcast_value());
    // Issue a CSPartialFlush cmd including cache flush
    if (config->concurrent == 0) Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // Program the thread trace mask - specifies SH, CU, SIMD and
    // VM Id masks to apply. Enabling SQ/SPI/REG_STALL_EN bits
    const uint32_t mask_value = (config->mask) ? config->mask
                       : Primitives::sqtt_mask_value(config->targetCu, config->vmIdMask);
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MASK_ADDR,
                                        mask_value);
    // Program the thread trace Perf mask
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_PERF_MASK_ADDR,
                                        Primitives::sqtt_perf_mask_value());

    if (config->n_perfcounters) StartPerfMon(cmd_buffer, config);

    // Program the thread trace token mask
    const uint32_t token_mask_value =
        (config->tokenMask) ? config->tokenMask : Primitives::sqtt_token_mask_value();
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_TOKEN_MASK_ADDR,
                                        token_mask_value);
    // Program the thread trace token mask2 to specify the list of instruction
    // tokens to record. Disabling INST_PC instruction tokens
    const uint32_t token_mask2_value = (config->tokenMask2) ? Primitives::sqtt_token_mask2_value() : 0;
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_TOKEN_MASK2_ADDR,
                                        token_mask2_value);

    // Program the thread trace mode register, mode OFF
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MODE_ADDR,
                                        Primitives::sqtt_mode_off_value());
    // Program the HiWaterMark register to support stalling
    /*if (Primitives::sqtt_stalling_enabled(mask_value, token_mask_value)) {
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_HIWATER_ADDR,
                                          Primitives::SQ_THREAD_TRACE_HIWATER_VAL);
    } */
    // Iterate through the list of SE's and program the register
    // for carrying address of thread trace buffer which is aligned
    // to 4KB per thread trace specification
    const uint32_t se_number = config->se_number;
    uint32_t se_vector = config->se_vector;
    uint64_t base_addr = reinterpret_cast<uint64_t>(config->data_buffer_ptr);
    const uint32_t base_step_nal = config->data_buffer_size / se_number;
    const uint32_t sqtt_size = Primitives::sqtt_size_value(base_step_nal);
    const uint32_t base_step = sqtt_size << Primitives::TT_BUFF_ALIGN_SHIFT;
    for (unsigned se_count = se_number; se_count > 0;
         --se_count, se_vector >>= SE_VECTOR_SHIFT, base_addr += base_step) {
      const unsigned se_index = se_vector & SE_VECTOR_MASK;
      // Program Grbm to direct writes to one SE
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                          Primitives::grbm_se_sh_index_value(se_index, 0));
      // Set SQTT STATUS to 0
      Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_STATUS_ADDR, 0);
      // Program base address of buffer to use for thread trace
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_BASE_ADDR,
                                          Primitives::sqtt_base_value_lo(base_addr));
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_BASE2_ADDR,
                                          Primitives::sqtt_base_value_hi(base_addr));
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
    if (config->concurrent == 0) Builder::BuildWriteWaitIdlePacket(cmd_buffer);
    // Program the thread trace mode register, mode ON
    Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MODE_ADDR,
                                        Primitives::sqtt_mode_on_value());
    // Issue a CSPartialFlush cmd including cache flush
    if (config->concurrent == 0) Builder::BuildWriteWaitIdlePacket(cmd_buffer);
   } else {
      // Iterate through the list of SE's and program the register
      // for carrying address of thread trace buffer which is aligned
      // to 4KB per thread trace specification
      const uint32_t se_number = config->se_number;
      uint32_t se_vector = config->se_vector;
      uint64_t base_addr = reinterpret_cast<uint64_t>(config->data_buffer_ptr);
      const uint32_t base_step_nal = config->data_buffer_size / se_number;
      const uint32_t sqtt_size = base_step_nal >> Primitives::TT_BUFF_ALIGN_SHIFT;
      const uint32_t base_step = sqtt_size << Primitives::TT_BUFF_ALIGN_SHIFT;

      for (unsigned se_count = se_number; se_count > 0;
         --se_count, se_vector >>= SE_VECTOR_SHIFT, base_addr += base_step) {
        const unsigned se_index = se_vector & SE_VECTOR_MASK;
        // Program Grbm to direct writes to one SE
        Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                          Primitives::grbm_se_sh_index_value(se_index, 0));

        const unsigned baddr_hi= High32(base_addr >> Primitives::TT_BUFF_ALIGN_SHIFT);
        const uint32_t size = sqtt_size | baddr_hi;

        // Program size of buffer to use for thread trace
        Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_SIZE_ADDR, size);

        // Program base address of buffer to use for thread trace
        const unsigned baddr_lo = Low32(base_addr >> Primitives::TT_BUFF_ALIGN_SHIFT);
        Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_BASE_ADDR, baddr_lo);

        // Program the thread trace mask
        const uint32_t simd_sel = (config->mask >> 8) & 0x3;
        const uint32_t mask_value = Primitives::sqtt_mask_value(config->mask & 0xF, simd_sel);
        Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_MASK_ADDR, mask_value);

        // Program the thread trace token mask
        Builder::BuildWritePConfigRegPacket(cmd_buffer, Primitives::SQ_THREAD_TRACE_TOKEN_MASK_ADDR,
                                          Primitives::sqtt_token_mask_value());

        if (config->concurrent == 0) Builder::BuildWriteWaitIdlePacket(cmd_buffer);
        // Program the thread trace ctrl register
        const uint32_t ctrl_val = Primitives::sqtt_ctrl_value();
        Builder::BuildWritePConfigRegPacket(cmd_buffer,Primitives::SQ_THREAD_TRACE_CTRL_ADDR, ctrl_val);

        if (config->concurrent == 0) Builder::BuildWriteWaitIdlePacket(cmd_buffer);
      }
     // Reset the GRBM to broadcast mode
     Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                         Primitives::grbm_broadcast_value());

     Builder::BuildWriteShRegPacket(cmd_buffer, Primitives::COMPUTE_THREAD_TRACE_ENABLE_ADDR, 1); //enabling thread trace by setting COMPUTE_THREAD_TRACE_ENABLE GpuF0MMReg:0xb878
   }
  }

  void End(CmdBuffer* cmd_buffer, const ThreadTraceConfig* config) {
   if (Primitives::GFXIP_LEVEL == 9){
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

    if (config->n_perfcounters) StopPerfMon(cmd_buffer);

    // Iterate through the list of SE's and read the Status, Counter and
    // Write Pointer registers of Thread Trace subsystem
    const uint32_t se_number = config->se_number;
    uint32_t se_vector = config->se_vector;
    for (unsigned se_count = se_number; se_count > 0; --se_count, se_vector >>= SE_VECTOR_SHIFT) {
      const unsigned se_index = se_vector & SE_VECTOR_MASK;
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

    // Issue a WaitIdle before disabling thread trace
    Builder::BuildWriteWaitIdlePacket(cmd_buffer);

    Builder::BuildWriteShRegPacket(cmd_buffer, Primitives::COMPUTE_THREAD_TRACE_ENABLE_ADDR, 0); //disabling thread trace

    const uint32_t se_number = config->se_number;
    uint32_t se_vector = config->se_vector;
    for (unsigned se_count = se_number; se_count > 0; --se_count, se_vector >>= SE_VECTOR_SHIFT) {
      const unsigned se_index = se_vector & SE_VECTOR_MASK;
      // Program Grbm to direct writes to one SE
      Builder::BuildWriteUConfigRegPacket(cmd_buffer, Primitives::GRBM_GFX_INDEX_ADDR,
                                          Primitives::grbm_se_sh_index_value(se_index, 0));
      // Issue WaitRegMem command to wait until SQTT event has completed
      const bool func_eq = false;
      const bool mem_space = false;
      const uint32_t wait_val = 0x0; //this is reference value
      const uint32_t mask_val = ~0x3ff000;  //wait for finish_done 
      const uint32_t status_offset = Primitives::SQ_THREAD_TRACE_STATUS_ADDR;
      Builder::BuildWaitRegMemCommand(cmd_buffer, mem_space, status_offset, func_eq, mask_val,
                                      wait_val);

      // Program the thread trace ctrl register to set mode to 0
      const uint32_t ctrl_val = Primitives::sqtt_ctrl_value() & 0xffffffc0;
      Builder::BuildWritePConfigRegPacket(cmd_buffer,Primitives::SQ_THREAD_TRACE_CTRL_ADDR, ctrl_val);

      //wait for NOT busy
      //Builder::BuildWaitRegMemCommand(cmd_buffer, mem_space, status_offset, func_eq, ~0x2000000L,
      //                                 wait_val);
  
      ReadValues(cmd_buffer, config, se_index);
    } //end of for loop


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
};

}  // namespace pm4_builder

#endif  // SRC_PM4_SQTT_BUILDER_H_
