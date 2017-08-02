#ifndef _GFX8_CMD_BUILDER_H_
#define _GFX8_CMD_BUILDER_H_

#include <string.h>
#include <assert.h>

#include <iostream>
#include <iomanip>
#include <sstream>

#include "pm4/cmd_builder.h"
#include "def/gfx8_def.h"

namespace pm4_builder {

// Desc: Initializer for various Gpu command headers
template <class T> static void GenerateCmdHeader(T* pm4, IT_OpCodeType op_code) {
  pm4->header.u32All = PM4_TYPE_3_HDR(op_code, sizeof(T) / sizeof(uint32_t), ShaderCompute, 0);
}

/// @brief class Gfx9CmdBuilder implements the virtual class CmdBuilder
/// for GFX8 chipsets
class Gfx8CmdBuilder : public CmdBuilder {
 public:
  static bool IsUserConfigReg(const uint32_t& addr) {
    return ((addr >= UCONFIG_SPACE_START__CI__VI) && (addr <= UCONFIG_SPACE_END__CI__VI));
  }

  void BuildBarrierCommand(CmdBuffer* cmdBuf) {
    PM4CMDEVENTWRITE event_write;
    memset(&event_write, 0, sizeof(event_write));

    // Initialize the command header
    GenerateCmdHeader(&event_write, IT_EVENT_WRITE);

    event_write.eventType = CS_PARTIAL_FLUSH;
    event_write.eventIndex = EVENT_WRITE_INDEX_VS_PS_PARTIAL_FLUSH;

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdBuf, event_write);
  }

  void BuildCacheFlushPacket(CmdBuffer* cmdbuf) {
    PM4CMDACQUIREMEM cache_flush;
    memset(&cache_flush, 0, sizeof(cache_flush));

    // Initialize the command header
    GenerateCmdHeader(&cache_flush, IT_ACQUIRE_MEM__CI__VI);

    // Specify the base address of memory to invalidate.
    cache_flush.cpCoherBase.u32All = 0;
    cache_flush.cpCoherBaseHi.u32All = 0;

    // Specify the size of memory to invalidate.
    cache_flush.cpCoherSize.u32All = CP_COHER_SIZE__COHER_SIZE_256B_MASK;
    cache_flush.cpCoherSizeHi.u32All = CP_COHER_SIZE_HI__COHER_SIZE_HI_256B_MASK__CI__VI;

    // Specify the poll interval for determing if operation is complete
    cache_flush.pollInterval = 0x04;

    // Program Coherence Control Register. Initialize L2 Cache flush
    // for Non-Coherent memory blocks
    uint32_t coher_cntl = 0;
    coher_cntl |= CP_COHER_CNTL__TC_ACTION_ENA_MASK;
    coher_cntl |= CP_COHER_CNTL__TCL1_ACTION_ENA_MASK;
    coher_cntl |= CP_COHER_CNTL__TC_WB_ACTION_ENA_MASK__CI__VI;
    coher_cntl |= CP_COHER_CNTL__SH_ICACHE_ACTION_ENA_MASK;
    coher_cntl |= CP_COHER_CNTL__SH_KCACHE_ACTION_ENA_MASK;
    cache_flush.coherCntl = coher_cntl;

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, cache_flush);
  }

  void BuildWriteWaitIdlePacket(CmdBuffer* cmdbuf) {
    BuildBarrierCommand(cmdbuf);
    BuildCacheFlushPacket(cmdbuf);
  }

  void BuildWaitRegMemCommand(CmdBuffer* cmdbuf, bool mem_space, uint64_t wait_addr, bool func_eq,
                              uint32_t mask_val, uint32_t wait_val) {
    PM4CMDWAITREGMEM wait_reg_mem;
    memset(&wait_reg_mem, 0, sizeof(wait_reg_mem));

    // Initialize the command header
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

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, wait_reg_mem);
  }

  void BuildWriteShRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) {
    struct {
      uint32_t item[3];
    } packet;

    // Initialize the command header
    packet.item[0] = PM4_TYPE_3_HDR(IT_SET_SH_REG, 1 + PM4_CMD_SET_SH_REG_DWORDS, ShaderCompute, 0);

    packet.item[1] = (addr - PERSISTENT_SPACE_START);
    packet.item[2] = value;

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, packet);
  }

  void BuildWriteUConfigRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) {
    struct {
      uint32_t item[3];
    } packet;

    // Initialize the command header
    packet.item[0] = PM4_TYPE_3_HDR(IT_SET_UCONFIG_REG__CI__VI, 1 + PM4_CMD_SET_CONFIG_REG_DWORDS,
                                    ShaderCompute, 0);

    packet.item[1] = (addr - UCONFIG_SPACE_START__CI__VI);
    packet.item[2] = value;

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, packet);
  }

  void BuildWritePConfigRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) {
    PM4CMDCOPYDATA cmd_data;
    memset(&cmd_data, 0, sizeof(PM4CMDCOPYDATA));

    // Initialize the command header
    GenerateCmdHeader(&cmd_data, IT_COPY_DATA);

    cmd_data.srcAtc__CI = atc_support_;
    cmd_data.srcSel = COPY_DATA_SEL_SRC_IMME_DATA;
    cmd_data.srcCachePolicy__CI = COPY_DATA_SRC_CACHE_POLICY_LRU;

    cmd_data.dstAtc__CI = atc_support_;
    cmd_data.dstSel = COPY_DATA_SEL_DST_SYS_PERF_COUNTER;
    cmd_data.dstCachePolicy__CI = COPY_DATA_DST_CACHE_POLICY_LRU;

    cmd_data.srcAddressLo = value;
    cmd_data.srcAddressHi = 0;
    cmd_data.dstAddressLo = addr;
    cmd_data.dstAddressHi = 0;

    cmd_data.countSel = COPY_DATA_SEL_COUNT_1DW;
    cmd_data.wrConfirm = COPY_DATA_WR_CONFIRM_NO_WAIT;
    cmd_data.engineSel = COPY_DATA_ENGINE_ME;

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, cmd_data);
  }

  void BuildWriteConfigRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) {
    return (IsUserConfigReg(addr)) ? BuildWriteUConfigRegPacket(cmdbuf, addr, value)
                                   : BuildWritePConfigRegPacket(cmdbuf, addr, value);
  }

  void BuildCopyRegDataPacket(CmdBuffer* cmdbuf, uint32_t src_sel, uint32_t src_reg_addr,
                              void* dst_addr, uint32_t size, bool wait) {
    PM4CMDCOPYDATA cmd_data;
    memset(&cmd_data, 0, sizeof(PM4CMDCOPYDATA));

    // Initialize the command header
    GenerateCmdHeader(&cmd_data, IT_COPY_DATA);

    cmd_data.srcAtc__CI = atc_support_;
    cmd_data.srcSel = src_sel;
    cmd_data.srcCachePolicy__CI = COPY_DATA_SRC_CACHE_POLICY_BYPASS;

    cmd_data.dstAtc__CI = atc_support_;
    cmd_data.dstSel = COPY_DATA_SEL_DST_ASYNC_MEMORY;
    cmd_data.dstCachePolicy__CI = COPY_DATA_DST_CACHE_POLICY_BYPASS;

    cmd_data.srcAddressLo = src_reg_addr;
    cmd_data.srcAddressHi = 0;
    cmd_data.dstAddressLo = PtrLow32(dst_addr);
    cmd_data.dstAddressHi = PtrHigh32(dst_addr);

    cmd_data.countSel = size;
    cmd_data.wrConfirm = wait;
    cmd_data.engineSel = COPY_DATA_ENGINE_ME;

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, cmd_data);
  }

  uint32_t BuildCopyCounterDataPacket(CmdBuffer* cmdbuf, uint32_t src_sel, uint32_t src_reg_addr_lo,
                                      uint32_t src_reg_addr_hi, void* dst_addr, uint32_t dw_mask) {
    uint32_t read_counter = 0;
    if (dw_mask & 0x1) {
      BuildCopyRegDataPacket(cmdbuf, src_sel, src_reg_addr_lo, (uint32_t*)dst_addr + read_counter,
                             COPY_DATA_SEL_COUNT_1DW, false);
      ++read_counter;
    }
    if (dw_mask & 0x2) {
      BuildCopyRegDataPacket(cmdbuf, src_sel, src_reg_addr_hi, (uint32_t*)dst_addr + read_counter,
                             COPY_DATA_SEL_COUNT_1DW, false);
      ++read_counter;
    }
    return read_counter;
  }

  void BuildIndirectBufferCmd(CmdBuffer* cmdbuf, const void* cmd_addr, std::size_t cmd_size) {
    PM4CMDINDIRECTBUFFER indirect_buffer;
    memset(&indirect_buffer, 0, sizeof(indirect_buffer));

    // Initialize the command header
    GenerateCmdHeader(&indirect_buffer, IT_INDIRECT_BUFFER);

    indirect_buffer.ibBaseLo = PtrLow32(cmd_addr);
    indirect_buffer.ibBaseHi = PtrHigh32(cmd_addr);
    indirect_buffer.CI.ibSize = cmd_size / sizeof(uint32_t);
    indirect_buffer.CI.valid = true;

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, indirect_buffer);
  }

  constexpr static bool atc_support_ = false;
};

}  // pm4_builder

#endif  //  _GFX8_CMD_BUILDER_H_
