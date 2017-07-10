#ifndef _GFX9_SQTT_BUILDER_H_
#define _GFX9_SQTT_BUILDER_H_

#include <string>

#include "sqtt_builder.h"
#include "gfx9_cmd_builder.h"
#include "gfxip/gfx9/gfx9_registers.h"
#include "gfxip/gfx9/gfx9_typedef.h"
#include "gfxip/gfx9/gfx9_enum.h"
#include "gfxip/gfx9/gfx9_offset.h"
#include "gfxip/gfx9/gfx9_pm4defs.h"

namespace pm4_builder {
using namespace gfxip::gfx9;

struct Gfx9ThreadTraceCfgRegs {
  Gfx9ThreadTraceCfgRegs(const ThreadTraceConfig* config) {
    // Indicates the size of buffer to use per Shader Engine instance.
    // The size is specified in terms of 4KB blocks
    ttRegSize.u32All = 0;
    ttRegSize.bits.SIZE = config->data_buffer_size >> TT_BUFF_ALIGN_SHIFT;

    // Indicates various attributes of a thread trace session.
    //
    // MASK_CS: Which shader types should be enabled for data collection
    //      Enable CS Shader types.
    //
    // WRAP: How trace buffer should be used as a ring buffer or as a linear
    //      buffer - Disable WRAP mode i.e use it as a linear buffer
    //
    // MODE: Enables a thread trace session
    //
    // CAPTURE_MODE: When thread trace data is collected immediately after MODE
    //      is enabled or wait until a Thread Trace Start event is received
    //
    // AUTOFLUSH_EN: Flush thread trace data to buffer often automatically
    //
    ttRegMode.u32All = 0;
    ttRegMode.bits.WRAP = 0;
    ttRegMode.bits.CAPTURE_MODE = 0;
    ttRegMode.bits.MASK_CS = 1;
    ttRegMode.bits.AUTOFLUSH_EN = 1;
    ttRegMode.bits.MODE = SQ_THREAD_TRACE_MODE_OFF;

    // Enable Thread Trace for all VM Id's
    // Enable all of the SIMD's of the compute unit
    // Enable Compute Unit (CU) at index Zero to be used for fine-grained data
    // Enable Shader Array (SH) at index Zero to be used for fine-grained data
    //
    // @note: Not enabling REG_STALL_EN, SPI_STALL_EN and SQ_STALL_EN bits. They
    // are useful if we wish to program buffer throttling.
    //
    ttRegMask.u32All = 0;
    ttRegMask.bits.SH_SEL = 0x0;
    ttRegMask.bits.SIMD_EN = 0xF;
    ttRegMask.bits.CU_SEL = config->targetCu;
    ttRegMask.bits.SQ_STALL_EN = 0x1;
    ttRegMask.bits.SPI_STALL_EN = 0x1;
    ttRegMask.bits.REG_STALL_EN = 0x1;
    ttRegMask.bits.VM_ID_MASK = config->vmIdMask;

    // Override Mask value if a user value is available
    const uint32_t ttMask = config->mask;
    if (ttMask) {
      ttRegMask.u32All = ttMask;
    }

    // Mask of compute units to get thread trace data from
    ttRegPerfMask.u32All = 0;
    ttRegPerfMask.bits.SH0_MASK = 0xFFFF;
    ttRegPerfMask.bits.SH1_MASK = 0xFFFF;

    // Indicate the different TT messages/tokens that should be enabled/logged
    // Indicate the different TT tokens that specify register operations to be logged
    ttRegTokenMask.u32All = 0;
    ttRegTokenMask.bits.REG_MASK = 0xFF;
    ttRegTokenMask.bits.TOKEN_MASK = 0xFFFF;
    ttRegTokenMask.bits.REG_DROP_ON_STALL = 0x1;

    // Override TokenMask1 value if a user value is available
    const uint32_t tokenMask1 = config->tokenMask;
    if (tokenMask1) {
      ttRegTokenMask.u32All = tokenMask1;
    }

    // Indicate the different TT tokens that specify instruction operations to be logged
    // Disabling specifically instruction operations updating Program Counter (PC).
    // @note: The field is defined in the spec incorrectly as a 16-bit value
    ttRegTokenMask2.u32All = 0;
    ttRegTokenMask2.bits.INST_MASK = 0xFFFFFF7F;

    // Override TokenMask2 value if a user value is available
    const uint32_t tokenMask2 = config->tokenMask2;
    if (tokenMask2) {
      ttRegTokenMask2.u32All = tokenMask2;
    }
  }

  // Size of thread trace buffer
  regSQ_THREAD_TRACE_SIZE ttRegSize;
  // Thread trace mode
  regSQ_THREAD_TRACE_MODE ttRegMode;
  // Thread trace wave mask
  regSQ_THREAD_TRACE_MASK ttRegMask;
  // Thread trace token mask
  regSQ_THREAD_TRACE_TOKEN_MASK ttRegTokenMask;
  // Thread trace token mask2
  regSQ_THREAD_TRACE_TOKEN_MASK2 ttRegTokenMask2;
  // Thread trace perf mask
  regSQ_THREAD_TRACE_PERF_MASK ttRegPerfMask;
};

class Gfx9SqttBuilder : public SqttBuilder, protected Gfx9CmdBuilder {
 public:
  void BeginSession(CmdBuffer* cmdBuff, const ThreadTraceConfig* config) {
    Gfx9ThreadTraceCfgRegs cfg_regs(config);

    // Program Grbm to broadcast messages to all shader engines
    regGRBM_GFX_INDEX grbm_gfx_index;
    grbm_gfx_index.u32All = 0;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
    BuildWriteUConfigRegPacket(cmdBuff, mmGRBM_GFX_INDEX, grbm_gfx_index.u32All);

    // Issue a CSPartialFlush cmd including cache flush
    BuildWriteWaitIdlePacket(cmdBuff);

    // Disable RLC Perfmon Clock Gating
    // On Vega this is needed to collect Perf Cntrs
    // BuildWriteUConfigRegPacket(cmdBuff, mmRLC_PERFMON_CLK_CNTL, 1);

    // Program the Compute register to indicate SQTT is enabled
    /*
    regCOMPUTE_THREAD_TRACE_ENABLE enableTT = {0};
    enableTT.bits.THREAD_TRACE_ENABLE = 1;
    BuildWriteUConfigRegPacket(cmdBuff,
                                          mmCOMPUTE_THREAD_TRACE_ENABLE,
                                          enableTT.u32All);
    */

    // Program the thread trace mask - specifies SH, CU, SIMD and
    // VM Id masks to apply. Enabling SQ/SPI/REG_STALL_EN bits
    BuildWriteUConfigRegPacket(cmdBuff, mmSQ_THREAD_TRACE_MASK, cfg_regs.ttRegMask.u32All);

    // Program the thread trace Perf mask
    BuildWriteUConfigRegPacket(cmdBuff, mmSQ_THREAD_TRACE_PERF_MASK, cfg_regs.ttRegPerfMask.u32All);

    // Program the thread trace token mask
    BuildWriteUConfigRegPacket(cmdBuff, mmSQ_THREAD_TRACE_TOKEN_MASK,
                               cfg_regs.ttRegTokenMask.u32All);

    // Program the thread trace token mask2 to specify the list of instruction
    // tokens to record. Disabling INST_PC instruction tokens
    BuildWriteUConfigRegPacket(cmdBuff, mmSQ_THREAD_TRACE_TOKEN_MASK2,
                               cfg_regs.ttRegTokenMask2.u32All);

    // Program the thread trace mode register
    BuildWriteUConfigRegPacket(cmdBuff, mmSQ_THREAD_TRACE_MODE, cfg_regs.ttRegMode.u32All);

    // Program the HiWaterMark register to support stalling
    if ((cfg_regs.ttRegMask.bits.SQ_STALL_EN) || (cfg_regs.ttRegMask.bits.SPI_STALL_EN) ||
        (cfg_regs.ttRegMask.bits.REG_STALL_EN) ||
        (cfg_regs.ttRegTokenMask.bits.REG_DROP_ON_STALL)) {
      BuildWriteUConfigRegPacket(cmdBuff, mmSQ_THREAD_TRACE_HIWATER, 0x06);
    }

    // Iterate through the list of SE's and program the register
    // for carrying address of thread trace buffer which is aligned
    // to 4KB per thread trace specification
    uint64_t base_addr = reinterpret_cast<uint64_t>(config->data_buffer_ptr);
    const uint32_t base_step = config->data_buffer_size / config->se_number;
    for (int idx = 0; idx < config->se_number; ++idx, base_addr += base_step) {
      // Program Grbm to direct writes to one SE
      grbm_gfx_index.bitfields.SH_INDEX = 0;
      grbm_gfx_index.bitfields.SE_INDEX = idx;
      grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 0;
      grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 0;
      BuildWriteUConfigRegPacket(cmdBuff, mmGRBM_GFX_INDEX, grbm_gfx_index.u32All);

      // Program base2 address of buffer to use for thread trace
      /*
      regSQ_THREAD_TRACE_BASE2 sqttBase2 = {};
      sqttBase2.u32All = 0;
      sqttBase2.bits.ADDR_HI = 0;
      BuildWriteUConfigRegPacket(cmdBuff,
                                            mmSQ_THREAD_TRACE_BASE2,
                                            sqttBase2.u32All);
      */

      // Program base address of buffer to use for thread trace
      regSQ_THREAD_TRACE_BASE sqttBase = {};
      sqttBase.bits.ADDR = Low32(base_addr >> TT_BUFF_ALIGN_SHIFT);
      BuildWriteUConfigRegPacket(cmdBuff, mmSQ_THREAD_TRACE_BASE, sqttBase.u32All);

      // Program the size of thread trace buffer
      BuildWriteUConfigRegPacket(cmdBuff, mmSQ_THREAD_TRACE_SIZE, cfg_regs.ttRegSize.u32All);

      // Program the thread trace ctrl register
      regSQ_THREAD_TRACE_CTRL sqttCtrl = {};
      sqttCtrl.u32All = 0;
      sqttCtrl.bits.RESET_BUFFER = 1;
      BuildWriteUConfigRegPacket(cmdBuff, mmSQ_THREAD_TRACE_CTRL, sqttCtrl.u32All);
    }

    // Reset the GRBM to broadcast mode
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    BuildWriteUConfigRegPacket(cmdBuff, mmGRBM_GFX_INDEX, grbm_gfx_index.u32All);

    // Issue a CSPartialFlush cmd including cache flush
    BuildWriteWaitIdlePacket(cmdBuff);

    // Program the thread trace mode register
    cfg_regs.ttRegMode.bits.MODE = SQ_THREAD_TRACE_MODE_ON;
    BuildWriteUConfigRegPacket(cmdBuff, mmSQ_THREAD_TRACE_MODE, cfg_regs.ttRegMode.u32All);

    // Issue a CSPartialFlush cmd including cache flush
    BuildWriteWaitIdlePacket(cmdBuff);
    return;
  }

  void StopSession(CmdBuffer* cmdBuff, const ThreadTraceConfig* config) {
    Gfx9ThreadTraceCfgRegs cfg_regs(config);

    // Program Grbm to broadcast messages to all shader engines
    regGRBM_GFX_INDEX grbm_gfx_index;
    grbm_gfx_index.u32All = 0;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
    BuildWriteUConfigRegPacket(cmdBuff, mmGRBM_GFX_INDEX, grbm_gfx_index.u32All);

    // Issue a CSPartialFlush cmd including cache flush
    BuildWriteWaitIdlePacket(cmdBuff);

    // Program the thread trace mode register to disable thread trace
    cfg_regs.ttRegMode.bits.MODE = SQ_THREAD_TRACE_MODE_OFF;
    BuildWriteUConfigRegPacket(cmdBuff, mmSQ_THREAD_TRACE_MODE, cfg_regs.ttRegMode.u32All);

    // Issue a CSPartialFlush cmd including cache flush
    BuildWriteWaitIdlePacket(cmdBuff);

    // Iterate through the list of SE's and read the Status, Counter and
    // Write Pointer registers of Thread Trace subsystem
    for (int idx = 0; idx < config->se_number; idx++) {
      // Program Grbm to direct writes to one SE
      grbm_gfx_index.bitfields.SH_INDEX = 0;
      grbm_gfx_index.bitfields.SE_INDEX = idx;
      grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 0;
      grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 0;
      BuildWriteUConfigRegPacket(cmdBuff, mmGRBM_GFX_INDEX, grbm_gfx_index.u32All);

      // Issue WaitRegMem command to wait until SQTT event has completed
      bool funcEq = false;
      bool memSpace = false;
      uint32_t waitVal = 0x01;
      uint32_t maskVal = 0x40000000L;
      uint32_t statusOffset = mmSQ_THREAD_TRACE_STATUS - UCONFIG_SPACE_START;
      BuildWaitRegMemCommand(cmdBuff, memSpace, statusOffset, funcEq, maskVal, waitVal);

      // Retrieve the values from various status registers
      ControlType* control_buffer = reinterpret_cast<ControlType*>(config->control_buffer_ptr);
      const uint32_t statusIdx = ((TT_STATUS_IDX_MAX * idx) + TT_STATUS_IDX_STATUS);
      BuildCopyDataPacket(cmdBuff, COPY_DATA_SEL_SRC_SYS_PERF_COUNTER, mmSQ_THREAD_TRACE_STATUS, 0,
                          control_buffer + statusIdx, COPY_DATA_SEL_COUNT_1DW, true);

      const uint32_t cntrIdx = ((TT_STATUS_IDX_MAX * idx) + TT_STATUS_IDX_CNTR);
      BuildCopyDataPacket(cmdBuff, COPY_DATA_SEL_SRC_SYS_PERF_COUNTER, mmSQ_THREAD_TRACE_CNTR, 0,
                          control_buffer + cntrIdx, COPY_DATA_SEL_COUNT_1DW, true);

      const uint32_t wptrIdx = ((TT_STATUS_IDX_MAX * idx) + TT_STATUS_IDX_WPTR);
      BuildCopyDataPacket(cmdBuff, COPY_DATA_SEL_SRC_SYS_PERF_COUNTER, mmSQ_THREAD_TRACE_WPTR, 0,
                          control_buffer + wptrIdx, COPY_DATA_SEL_COUNT_1DW, true);
    }

    // Reset the GRBM to broadcast mode
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    BuildWriteUConfigRegPacket(cmdBuff, mmGRBM_GFX_INDEX, grbm_gfx_index.u32All);

    // Initialize cache flush request object
    BuildCacheFlushPacket(cmdBuff);

    // Program the size of thread trace buffer
    regSQ_THREAD_TRACE_SIZE ttRegSize = {0};
    ttRegSize.u32All = 0;
    BuildWriteUConfigRegPacket(cmdBuff, mmSQ_THREAD_TRACE_SIZE, ttRegSize.u32All);

    // Program the thread trace ctrl register
    regSQ_THREAD_TRACE_CTRL sqttCtrl = {};
    sqttCtrl.u32All = 0;
    sqttCtrl.bits.RESET_BUFFER = 1;
    BuildWriteUConfigRegPacket(cmdBuff, mmSQ_THREAD_TRACE_CTRL, sqttCtrl.u32All);

    // Program the compute_thread_trace_enable register
    /*
    regCOMPUTE_THREAD_TRACE_ENABLE disableTT = {0};
    BuildWriteUConfigRegPacket(cmdBuff,
                                          mmCOMPUTE_THREAD_TRACE_ENABLE,
                                          disableTT.u32All);
    */

    // Disable RLC Perfmon Clock Gating
    // On Vega this is needed to collect Perf Cntrs
    // BuildWriteUConfigRegPacket(cmdBuff, mmRLC_PERFMON_CLK_CNTL, 0);

    // Issue a CSPartialFlush cmd including cache flush
    BuildWriteWaitIdlePacket(cmdBuff);
    return;
  }
};

}  // pm4_builder

#endif  // _GFX9_SQTT_BUILDER_H_
