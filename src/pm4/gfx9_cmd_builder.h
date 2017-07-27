#ifndef _GFX9_CMD_BUILDER_H_
#define _GFX9_CMD_BUILDER_H_

#include <string.h>
#include <assert.h>

#include <iostream>
#include <iomanip>
#include <sstream>

#include "pm4/cmd_builder.h"
#include "def/gfx9_def.h"

namespace pm4_builder {

// @brief Initializer for various Gpu command headers
template <class T> static void GenerateCmdHeader(T* pm4, IT_OpCodeType op_code) {
  pm4->header.u32All = PM4_TYPE3_HDR(op_code, sizeof(T) / sizeof(uint32_t));
}

/// @brief class Gfx9CmdBuilder implements the virtual class CmdBuilder
/// for GFX9 chipsets
class Gfx9CmdBuilder : public CmdBuilder {
 public:
  void BuildBarrierCommand(CmdBuffer* cmdBuf) {
    PM4MEC_EVENT_WRITE event_write;
    memset(&event_write, 0, sizeof(event_write));
    GenerateCmdHeader(&event_write, IT_EVENT_WRITE);

    event_write.bitfields2.event_type = CS_PARTIAL_FLUSH;
    event_write.bitfields2.event_index = event_index__mec_event_write__cs_partial_flush;

    APPEND_COMMAND_WRAPPER(cmdBuf, event_write);
  }

  void BuildCacheFlushPacket(CmdBuffer* cmdbuf) {
    PM4MEC_ACQUIRE_MEM cache_flush;
    memset(&cache_flush, 0, sizeof(cache_flush));
    GenerateCmdHeader(&cache_flush, IT_ACQUIRE_MEM);

    // Specify the size of memory to invalidate. Size is
    // specified in terms of 256 byte chunks. A coher_size
    // of 0xFFFFFFFF actually specified 0xFFFFFFFF00 (40 bits)
    // of memory. The field coher_size_hi specifies memory from
    // bits 40-64 for a total of 256 TB.
    cache_flush.coher_size = 0xFFFFFFFF;
    cache_flush.bitfields4.coher_size_hi = 0xFFFFFF;

    // Specify the address of memory to invalidate. The
    // address must be 256 byte aligned.
    cache_flush.coher_base_lo = 0x00;
    cache_flush.bitfields6.coher_base_hi = 0x00;

    // Specify the poll interval for determing if operation is complete
    cache_flush.bitfields7.poll_interval = 0x04;

    // Program Coherence Control Register. Initialize L2 Cache flush
    // for Non-Coherent memory blocks
    uint32_t coher_cntl = 0;
    coher_cntl |= CP_COHER_CNTL__TC_ACTION_ENA_MASK;
    coher_cntl |= CP_COHER_CNTL__TCL1_ACTION_ENA_MASK;
    coher_cntl |= CP_COHER_CNTL__TC_WB_ACTION_ENA_MASK;
    coher_cntl |= CP_COHER_CNTL__SH_ICACHE_ACTION_ENA_MASK;
    coher_cntl |= CP_COHER_CNTL__SH_KCACHE_ACTION_ENA_MASK;
    cache_flush.bitfields2.coher_cntl = coher_cntl;

    // Copy AcquireMem command buffer stream
    APPEND_COMMAND_WRAPPER(cmdbuf, cache_flush);
  }

  void BuildWriteWaitIdlePacket(CmdBuffer* cmdbuf) {
    BuildBarrierCommand(cmdbuf);
    BuildCacheFlushPacket(cmdbuf);
  }

  void BuildWaitRegMemCommand(CmdBuffer* cmdbuf, bool mem_space, uint64_t wait_addr, bool func_eq,
                              uint32_t mask_val, uint32_t wait_val) {
    PM4MEC_WAIT_REG_MEM wait_reg_mem;
    memset(&wait_reg_mem, 0, sizeof(wait_reg_mem));
    GenerateCmdHeader(&wait_reg_mem, IT_WAIT_REG_MEM);

    wait_reg_mem.bitfields7.poll_interval = 0x04;
    wait_reg_mem.bitfields2.operation = operation__mec_wait_reg_mem__wait_reg_mem;

    // Apply the space to which addr belongs
    if (mem_space) {
      wait_reg_mem.bitfields2.mem_space = mem_space__mec_wait_reg_mem__memory_space;
    } else {
      wait_reg_mem.bitfields2.mem_space = mem_space__mec_wait_reg_mem__register_space;
    }

    // Apply the function - equal / not equal desired by user
    if (func_eq) {
      wait_reg_mem.bitfields2.function = function__mec_wait_reg_mem__equal_to_the_reference_value;
    } else {
      wait_reg_mem.bitfields2.function = function__mec_wait_reg_mem__not_equal_reference_value;
    }

    // Value to use in applying equal / not equal function
    wait_reg_mem.reference = wait_val;

    // Apply the mask on value at address/register
    wait_reg_mem.mask = mask_val;

    // The address to poll should be DWord (4 byte) aligned
    // Update upper 32 bit address if addr is not a register
    if (mem_space) {
      assert(!(wait_addr & 0x3) && "WaitRegMem address must be 4 byte aligned");
    }
    wait_reg_mem.bitfields3a.mem_poll_addr_lo = (Low32(wait_addr) >> 2);
    if (mem_space) {
      wait_reg_mem.mem_poll_addr_hi = High32(wait_addr);
    }

    // Append the command to cmd stream
    APPEND_COMMAND_WRAPPER(cmdbuf, wait_reg_mem);
  }

  typedef struct WriteRegPacket_ { uint32_t item[3]; } WriteRegPacket;

  void BuildWriteUConfigRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) {
    struct {
      uint32_t item[3];
    } packet;
    packet.item[0] =
        PM4_TYPE3_HDR(IT_SET_UCONFIG_REG, (1 + sizeof(PM4MEC_SET_CONFIG_REG) / sizeof(uint32_t)));
    packet.item[1] = (addr - UCONFIG_SPACE_START);
    packet.item[2] = value;

    APPEND_COMMAND_WRAPPER(cmdbuf, packet);
  }

  void BuildWriteShRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) {
    WriteRegPacket packet;
    packet.item[0] =
        PM4_TYPE3_HDR(IT_SET_SH_REG, (1 + sizeof(PM4MEC_SET_CONFIG_REG) / sizeof(uint32_t)));
    packet.item[1] = (addr - PERSISTENT_SPACE_START);
    packet.item[2] = value;

    APPEND_COMMAND_WRAPPER(cmdbuf, packet);
  }

  void BuildCopyDataPacket(CmdBuffer* cmdbuf, uint32_t src_sel, uint32_t src_addr_lo,
                           uint32_t src_addr_hi, uint32_t* dst_addr, uint32_t size, bool wait) {
    PM4MEC_COPY_DATA cmd_data;
    memset(&cmd_data, 0, sizeof(PM4MEC_COPY_DATA));
    cmd_data.ordinal1 = PM4_TYPE3_HDR(IT_COPY_DATA, (sizeof(PM4MEC_COPY_DATA) / sizeof(uint32_t)));

    MEC_COPY_DATA_src_sel_enum data_src = src_sel__mec_copy_data__memory;
    switch (src_sel) {
      case 0:
        data_src = src_sel__mec_copy_data__mem_mapped_register;
        break;
      case 4:
        data_src = src_sel__mec_copy_data__perfcounters;
        break;
      default:
        assert(false && "CopyData Illegal value for source of data");
        break;
    }
    cmd_data.bitfields2.src_sel = data_src;
    cmd_data.bitfields2.src_cache_policy = src_cache_policy__mec_copy_data__stream;

    cmd_data.bitfields2.dst_sel = dst_sel__mec_copy_data__memory;
    cmd_data.bitfields2.dst_cache_policy = dst_cache_policy__mec_copy_data__stream;

    cmd_data.bitfields2.wr_confirm = (MEC_COPY_DATA_wr_confirm_enum)wait;
    cmd_data.bitfields2.count_sel = (size == 0) ? count_sel__mec_copy_data__32_bits_of_data
                                                : count_sel__mec_copy_data__64_bits_of_data;

    // Specify the source register offset
    cmd_data.bitfields3a.src_reg_offset = src_addr_lo;

    // Specify the destination memory address
    cmd_data.dst_addr_hi = PtrHigh32(dst_addr);
    if (size == 0) {
      cmd_data.bitfields5b.dst_32b_addr_lo = (PtrLow32(dst_addr) >> 2);
    } else {
      cmd_data.bitfields5c.dst_64b_addr_lo = (PtrLow32(dst_addr) >> 3);
    }

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, cmd_data);
  }

  void BuildIndirectBufferCmd(CmdBuffer* cmdbuf, const void* cmd_addr, std::size_t cmd_size) {
    // Verify the address is 4-byte aligned
    uint64_t addr = uintptr_t(cmd_addr);
    assert(!(addr & 0x3) && "IndirectBuffer address must be 4 byte aligned");

    // Specify the address of indirect buffer encoding cmd stream
    PM4MEC_INDIRECT_BUFFER indirect_buffer;
    memset(&indirect_buffer, 0, sizeof(indirect_buffer));
    GenerateCmdHeader(&indirect_buffer, IT_INDIRECT_BUFFER);

    indirect_buffer.bitfields2.ib_base_lo = (PtrLow32(cmd_addr) >> 2);
    indirect_buffer.ib_base_hi = PtrHigh32(cmd_addr);

    // Specify the size of indirect buffer and cache policy to set
    // upon executing the cmds of indirect buffer
    indirect_buffer.bitfields4.priv = 0;
    indirect_buffer.bitfields4.valid = 1;
    indirect_buffer.bitfields4.ib_size = cmd_size / sizeof(uint32_t);
    indirect_buffer.bitfields4.cache_policy = cache_policy__mec_indirect_buffer__stream;

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, indirect_buffer);
  }
};

}  // pm4_builder

#endif  //  _GFX9_CMD_BUILDER_H_
