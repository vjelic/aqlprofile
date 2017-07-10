#ifndef _GFX8_CMD_BUILDER_H_
#define _GFX8_CMD_BUILDER_H_

#include <string.h>
#include <assert.h>

#include <iostream>
#include <iomanip>
#include <sstream>

#include "cmd_builder.h"
#include "gfxip/gfx8/si_ci_vi_merged_enum.h"
#include "gfxip/gfx8/si_ci_vi_merged_mask.h"
#include "gfxip/gfx8/si_ci_vi_merged_offset.h"
#include "gfxip/gfx8/si_ci_vi_merged_registers.h"
#include "gfxip/gfx8/si_ci_vi_merged_typedef.h"
#include "gfxip/gfx8/si_ci_vi_merged_pm4_it_opcodes.h"
#include "gfxip/gfx8/si_pm4defs.h"
#include "gfxip/gfx8/gfx8_utils.h"

namespace pm4_builder {
using namespace gfxip::gfx8;

// Desc: Initializer for various Gpu command headers
template <class T> static void GenerateCmdHeader(T* pm4, IT_OpCodeType op_code) {
  pm4->header.u32All = PM4_TYPE_3_HDR(op_code, sizeof(T) / sizeof(uint32_t), ShaderCompute, 0);
}

/// @brief class Gfx9CmdBuilder implements the virtual class CmdBuilder
/// for GFX8 chipsets
class Gfx8CmdBuilder : public CmdBuilder {
 public:
  void BuildBarrierCommand(CmdBuffer* cmdBuf) {
    PM4CMDEVENTWRITE event_write;
    memset(&event_write, 0, sizeof(event_write));

    GenerateCmdHeader(&event_write, IT_EVENT_WRITE);
    event_write.eventType = CS_PARTIAL_FLUSH;
    event_write.eventIndex = EventTypeToIndexTable[CS_PARTIAL_FLUSH];

    APPEND_COMMAND_WRAPPER(cmdBuf, event_write);
  }

  void BuildCacheFlushPacket(CmdBuffer* cmdbuf) {
    PM4CMDACQUIREMEM flushCmd;
    memset(&flushCmd, 0, sizeof(flushCmd));

    // Initialize the command header
    GenerateCmdHeader(&flushCmd, IT_ACQUIRE_MEM__CI__VI);

    // Specify the base address of memory being synchronized.
    // The starting address is indicated as follows: bits [0-48].
    flushCmd.cpCoherBase.u32All = 0;
    flushCmd.cpCoherBaseHi.u32All = 0;

    // Specify the size of memory being synchronized. It is indicated
    // as follows:
    //    COHER_SIZE_256B_MASK = 0xffffffffL
    //    COHER_SIZE_HI_256B_MASK__CI__VI = 0x000000ffL
    flushCmd.cpCoherSize.u32All = CP_COHER_SIZE__COHER_SIZE_256B_MASK;
    flushCmd.cpCoherSizeHi.u32All = CP_COHER_SIZE_HI__COHER_SIZE_HI_256B_MASK__CI__VI;

    // Periodicity of polling - interval to wait from the time
    // of unsuccessful polling result is returned and a new
    // poll is issued
    flushCmd.pollInterval = 0x04;

    // Program Coherence Control Register. Initialize L2 Cache flush
    // for Non-Coherent memory blocks
    uint32_t coher_cntl = 0;
    coher_cntl |= CP_COHER_CNTL__TC_ACTION_ENA_MASK;
    coher_cntl |= CP_COHER_CNTL__TCL1_ACTION_ENA_MASK;
    coher_cntl |= CP_COHER_CNTL__TC_WB_ACTION_ENA_MASK__CI__VI;
    coher_cntl |= CP_COHER_CNTL__SH_ICACHE_ACTION_ENA_MASK;
    coher_cntl |= CP_COHER_CNTL__SH_KCACHE_ACTION_ENA_MASK;
    flushCmd.coherCntl = coher_cntl;

    // Copy AcquireMem command buffer stream
    APPEND_COMMAND_WRAPPER(cmdbuf, flushCmd);
    return;
  }

  void BuildWriteWaitIdlePacket(CmdBuffer* cmdbuf) {
    BuildBarrierCommand(cmdbuf);
    BuildCacheFlushPacket(cmdbuf);
    return;
  }

  void BuildWaitRegMemCommand(CmdBuffer* cmdbuf, bool mem_space, uint64_t wait_addr, bool func_eq,
                              uint32_t mask_val, uint32_t wait_val) {
    PM4CMDWAITREGMEM wait_reg_mem;
    memset(&wait_reg_mem, 0, sizeof(wait_reg_mem));

    GenerateCmdHeader(&wait_reg_mem, IT_WAIT_REG_MEM);
    wait_reg_mem.atc__CI = (atc_support_) ? 1 : 0;
    wait_reg_mem.cachePolicy__CI = 2;  // bypass
    wait_reg_mem.pollInterval = 0;
    wait_reg_mem.engine = WAIT_REG_MEM_ENGINE_ME;

    // Apply the space to which addr belongs
    if (mem_space) {
      wait_reg_mem.memSpace = WAIT_REG_MEM_SPACE_MEMORY;
    } else {
      wait_reg_mem.memSpace = WAIT_REG_MEM_SPACE_REGISTER;
    }

    // Apply the function - equal / not equal desired by user
    if (func_eq) {
      wait_reg_mem.function = WAIT_REG_MEM_FUNC_EQUAL;
    } else {
      wait_reg_mem.function = WAIT_REG_MEM_FUNC_NOT_EQUAL;
    }

    // Apply the mask on value at address/register
    wait_reg_mem.mask = mask_val;

    // Value to use in applying equal / not equal function
    wait_reg_mem.reference = wait_val;

    // Update upper 32 bit address if addr is not a register
    if (mem_space) {
      assert(!(wait_addr & 0x3) && "WaitRegMem address must be 4 byte aligned");
    }
    wait_reg_mem.pollAddressLo = Low32(wait_addr);
    if (mem_space) {
      wait_reg_mem.pollAddressHi = High32(wait_addr);
    }

    APPEND_COMMAND_WRAPPER(cmdbuf, wait_reg_mem);
  }

  void BuildWriteUConfigRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) {
    struct {
      uint32_t item[3];
    } packet;
    packet.item[0] = (PM4_TYPE_3_HDR(IT_SET_UCONFIG_REG__CI__VI, 1 + PM4_CMD_SET_CONFIG_REG_DWORDS,
                                     ShaderCompute, 0));
    packet.item[1] = (addr - UCONFIG_SPACE_START__CI__VI);
    packet.item[2] = value;

    APPEND_COMMAND_WRAPPER(cmdbuf, packet);

    return;
  }

  void BuildWriteShRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) {
    struct {
      uint32_t item[3];
    } packet;
    packet.item[0] =
        (PM4_TYPE_3_HDR(IT_SET_SH_REG, 1 + PM4_CMD_SET_SH_REG_DWORDS, ShaderCompute, 0));
    packet.item[1] = (addr - PERSISTENT_SPACE_START);
    packet.item[2] = value;

    APPEND_COMMAND_WRAPPER(cmdbuf, packet);

    return;
  }

  void BuildCopyDataPacket(CmdBuffer* cmdbuf, uint32_t src_sel, uint32_t src_addr_lo,
                           uint32_t src_addr_hi, uint32_t* dst_addr, uint32_t size, bool wait) {
    PM4CMDCOPYDATA cmd_data;
    memset(&cmd_data, 0, sizeof(PM4CMDCOPYDATA));

    // Initialize the command header
    GenerateCmdHeader(&cmd_data, IT_COPY_DATA);

    cmd_data.srcAtc__CI = atc_support_;
    cmd_data.srcCachePolicy__CI = COPY_DATA_SRC_CACHE_POLICY_BYPASS;
    cmd_data.srcSel = src_sel;

    cmd_data.dstAtc__CI = atc_support_;
    cmd_data.dstSel = COPY_DATA_SEL_DST_ASYNC_MEMORY;
    cmd_data.dstCachePolicy__CI = COPY_DATA_DST_CACHE_POLICY_BYPASS;

    uint32_t dst_addr_lo, dst_addr_hi;

    dst_addr_lo = PtrLow32(dst_addr);
    dst_addr_hi = PtrHigh32(dst_addr);

    cmd_data.srcAddressLo = src_addr_lo;
    cmd_data.srcAddressHi = src_addr_hi;
    cmd_data.dstAddressLo = dst_addr_lo;
    cmd_data.dstAddressHi = dst_addr_hi;

    cmd_data.countSel = size;
    cmd_data.wrConfirm = wait;
    cmd_data.engineSel = COPY_DATA_ENGINE_ME;

    APPEND_COMMAND_WRAPPER(cmdbuf, cmd_data);

    return;
  }

  void BuildIndirectBufferCmd(CmdBuffer* cmdbuf, const void* cmd_addr, std::size_t cmd_size) {
    PM4CMDINDIRECTBUFFER indirect_buffer;
    memset(&indirect_buffer, 0, sizeof(indirect_buffer));

    GenerateCmdHeader(&indirect_buffer, IT_INDIRECT_BUFFER);
    indirect_buffer.CI.valid = true;

    indirect_buffer.ibBaseLo = PtrLow32(cmd_addr);
    indirect_buffer.ibBaseHi = PtrHigh32(cmd_addr);
    indirect_buffer.CI.ibSize = cmd_size / sizeof(uint32_t);

    APPEND_COMMAND_WRAPPER(cmdbuf, indirect_buffer);
  }

  constexpr static bool atc_support_ = false;
};

}  // pm4_builder

#endif  //  _GFX8_CMD_BUILDER_H_
