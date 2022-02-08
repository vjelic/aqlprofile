#ifndef SRC_PM4_GFX9_CMD_BUILDER_H_
#define SRC_PM4_GFX9_CMD_BUILDER_H_

#include <assert.h>
#include <string.h>

#include <iomanip>
#include <iostream>
#include <sstream>

#include "pm4/cmd_builder.h"
#ifndef SRC_PM4_GFX10_CMD_BUILDER_H_
  #include "def/gfx9_def.h"
#endif
namespace pm4_builder {

/// @brief class Gfx9CmdBuilder implements the virtual class CmdBuilder
/// for GFX9 chipsets
class Gfx9CmdBuilder : public CmdBuilder {
 private:
  // @brief Return a Type 3 PM4 packet header
  static PM4_MEC_TYPE_3_HEADER MakePacket3Header(uint32_t opcode, size_t packet_size) {
    PM4_MEC_TYPE_3_HEADER header{};
    header.opcode = opcode;
    header.count = packet_size / sizeof(uint32_t) - 2;
    header.type = 3;
    return header;
  }

 public:
  static constexpr bool IsPrivilegedConfigReg(uint32_t addr) {
    return ((addr >= CONFIG_SPACE_START) && (addr <= CONFIG_SPACE_END));
  }

  virtual void BuildBarrierCommand(CmdBuffer* cmdBuf) {
    PM4MEC_EVENT_WRITE event_write{};

    // Initialize the command header
    event_write.header = MakePacket3Header(IT_EVENT_WRITE, sizeof(event_write));

    event_write.bitfields2.event_type = CS_PARTIAL_FLUSH;
    event_write.bitfields2.event_index = event_index__mec_event_write__cs_partial_flush;
    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdBuf, event_write);
  }

#ifndef SRC_PM4_GFX10_CMD_BUILDER_H_
  void BuildCacheFlushPacket(CmdBuffer* cmdbuf) {
    PM4MEC_ACQUIRE_MEM cache_flush{};

    // Initialize the command header
    cache_flush.header = MakePacket3Header(IT_ACQUIRE_MEM, sizeof(cache_flush));

    // Specify the base address of memory to invalidate.
    // The address must be 256 byte aligned.
    cache_flush.coher_base_lo = 0x00000000;
    cache_flush.bitfields6.coher_base_hi = 0x000000;

    // Specify the size of memory to invalidate.
    // Size is specified in terms of 256byte chunks. A coher_size
    // of 0xFFFFFFFF actually specified 0xFFFFFFFF00 (40 bits)
    // of memory. The field coher_size_hi specifies memory from
    // bits 40-47 for a total of 256TiB-256 bytes.
    cache_flush.coher_size = 0xFFFFFFFF;
    cache_flush.bitfields4.coher_size_hi = 0xFF;

    // Specify the poll interval for determing if operation is complete
    cache_flush.bitfields7.poll_interval = 0x04;

    // Program Coherence Control Register. Initialize L2 Cache flush
    // for Non-Coherent memory blocks
    cache_flush.bitfields2.coher_cntl =
        CP_COHER_CNTL__TC_ACTION_ENA_MASK | CP_COHER_CNTL__TCL1_ACTION_ENA_MASK |
        CP_COHER_CNTL__TC_WB_ACTION_ENA_MASK | CP_COHER_CNTL__SH_ICACHE_ACTION_ENA_MASK |
        CP_COHER_CNTL__SH_KCACHE_ACTION_ENA_MASK;

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, cache_flush);
  }
#endif
  void BuildWriteWaitIdlePacket(CmdBuffer* cmdbuf) { BuildBarrierCommand(cmdbuf); }

  void BuildWaitRegMemCommand(CmdBuffer* cmdbuf, bool mem_space, uint64_t wait_addr, bool func_eq,
                              uint32_t mask_val, uint32_t wait_val) {
    PM4MEC_WAIT_REG_MEM wait_reg_mem{};

    // Initialize the command header
    wait_reg_mem.header = MakePacket3Header(IT_WAIT_REG_MEM, sizeof(wait_reg_mem));

    wait_reg_mem.bitfields7.poll_interval = 0x04;
    wait_reg_mem.bitfields2.operation = operation__mec_wait_reg_mem__wait_reg_mem;

    // Apply the space to which addr belongs
    wait_reg_mem.bitfields2.mem_space = mem_space ? mem_space__mec_wait_reg_mem__memory_space
                                                  : mem_space__mec_wait_reg_mem__register_space;

    // Apply the function - equal / not equal desired by user
    wait_reg_mem.bitfields2.function =
        func_eq ? function__mec_wait_reg_mem__equal_to_the_reference_value
                : function__mec_wait_reg_mem__not_equal_reference_value;

    // Apply the mask on value at address/register
    wait_reg_mem.mask = mask_val;

    // Value to use in applying equal / not equal function
    wait_reg_mem.reference = wait_val;

    // The address to poll should be DWord (4 byte) aligned
    // Update upper 32 bit address if addr is not a register
    if (mem_space) {
      assert(!(wait_addr & 0x3) && "WaitRegMem address must be 4 byte aligned");
    }
    wait_reg_mem.bitfields3a.mem_poll_addr_lo = (Low32(wait_addr) >> 2);
    if (mem_space) {
      wait_reg_mem.mem_poll_addr_hi = High32(wait_addr);
    }

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, wait_reg_mem);
  }

  void BuildWriteShRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) {
    PM4MEC_SET_SH_REG set_sh_reg{};

    // Initialize the command header
    set_sh_reg.header = MakePacket3Header(IT_SET_SH_REG, sizeof(set_sh_reg) + sizeof(value));
    set_sh_reg.bitfields2.reg_offset = (addr - PERSISTENT_SPACE_START);

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, set_sh_reg, value);
  }

  void BuildWriteUConfigRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) {
    PM4MEC_SET_UCONFIG_REG set_uconfig_reg{};

    // Initialize the command header
    set_uconfig_reg.header =
        MakePacket3Header(IT_SET_UCONFIG_REG, sizeof(set_uconfig_reg) + sizeof(value));
    set_uconfig_reg.bitfields2.reg_offset = (addr - UCONFIG_SPACE_START);

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, set_uconfig_reg, value);
  }

  void BuildWritePConfigRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) {
    PM4MEC_COPY_DATA copy_data{};

    // Initialize the command header
    copy_data.header = MakePacket3Header(IT_COPY_DATA, sizeof(copy_data));

    copy_data.bitfields2.src_sel = src_sel__mec_copy_data__immediate_data;
    copy_data.bitfields2.src_cache_policy = src_cache_policy__mec_copy_data__lru;

    copy_data.bitfields2.dst_sel = IsPrivilegedConfigReg(addr)
                                       ? dst_sel__mec_copy_data__perfcounters
                                       : dst_sel__mec_copy_data__mem_mapped_register;

    copy_data.bitfields2.dst_cache_policy = dst_cache_policy__mec_copy_data__lru;

    copy_data.bitfields2.wr_confirm = wr_confirm__mec_copy_data__do_not_wait_for_confirmation;
    copy_data.bitfields2.count_sel = count_sel__mec_copy_data__32_bits_of_data;

    copy_data.imm_data = value;

    copy_data.bitfields5a.dst_reg_offset = addr;

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, copy_data);
  }

  void BuildWriteConfigRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) {
    return IsPrivilegedConfigReg(addr) ? BuildWritePConfigRegPacket(cmdbuf, addr, value)
                                       : BuildWriteUConfigRegPacket(cmdbuf, addr, value);
  }
#ifndef SRC_PM4_GFX10_CMD_BUILDER_H_
  void BuildCopyRegDataPacket(CmdBuffer* cmdbuf, uint32_t src_reg_addr, const void* dst_addr,
                              uint32_t size, bool wait) {
    PM4MEC_COPY_DATA copy_data{};

    // Initialize the command header
    copy_data.header = MakePacket3Header(IT_COPY_DATA, sizeof(copy_data));

    copy_data.bitfields2.src_sel = IsPrivilegedConfigReg(src_reg_addr)
                                       ? src_sel__mec_copy_data__perfcounters
                                       : src_sel__mec_copy_data__mem_mapped_register;
    copy_data.bitfields2.src_cache_policy = src_cache_policy__mec_copy_data__stream;

    copy_data.bitfields2.dst_sel = dst_sel__mec_copy_data__memory;
    copy_data.bitfields2.dst_cache_policy = dst_cache_policy__mec_copy_data__stream;

    copy_data.bitfields2.wr_confirm = (MEC_COPY_DATA_wr_confirm_enum)wait;
    copy_data.bitfields2.count_sel = (size == 0) ? count_sel__mec_copy_data__32_bits_of_data
                                                 : count_sel__mec_copy_data__64_bits_of_data;

    // Specify the source register offset
    copy_data.bitfields3a.src_reg_offset = src_reg_addr;

    // Specify the destination memory address
    copy_data.dst_addr_hi = PtrHigh32(dst_addr);
    if (size == 0) {
      copy_data.bitfields5b.dst_32b_addr_lo = (PtrLow32(dst_addr) >> 2);
    } else {
      copy_data.bitfields5c.dst_64b_addr_lo = (PtrLow32(dst_addr) >> 3);
    }

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, copy_data);
  }
#endif
  uint32_t BuildCopyCounterDataPacket(CmdBuffer* cmdbuf, uint32_t src_reg_addr_lo,
                                      uint32_t src_reg_addr_hi, const void* dst_addr,
                                      uint32_t dw_mask) {
    uint32_t read_counter = 0;
    if (dw_mask & 0x1) {
      BuildCopyRegDataPacket(cmdbuf, src_reg_addr_lo, (uint32_t*)dst_addr + read_counter,
                             count_sel__mec_copy_data__32_bits_of_data, false);
      ++read_counter;
    }
    if (dw_mask & 0x2) {
      BuildCopyRegDataPacket(cmdbuf, src_reg_addr_hi, (uint32_t*)dst_addr + read_counter,
                             count_sel__mec_copy_data__32_bits_of_data, false);
      ++read_counter;
    }
    return read_counter;
  }

  void BuildWriteRegDataPacket(CmdBuffer* cmdbuf, uint32_t dst_reg_addr, const uint32_t* data,
                               uint32_t count, bool wait) {
    PM4MEC_WRITE_DATA write_data{};

    // Initialize the command header
    write_data.header =
        MakePacket3Header(IT_WRITE_DATA, sizeof(write_data) + count * sizeof(data[0]));

    // ordinal2
    write_data.bitfields2.dst_sel = dst_sel__mec_write_data__mem_mapped_register;  // mem-mapped reg
    write_data.bitfields2.addr_incr =
        addr_incr__mec_write_data__do_not_increment_address;  // not increment address
    write_data.bitfields2.wr_confirm = (MEC_WRITE_DATA_wr_confirm_enum)wait;

    // ordinal3
    write_data.bitfields3a.dst_mmreg_addr = dst_reg_addr;  // mem-mapped reg

    // ordinal4
    write_data.dst_mem_addr_hi = 0;  // mem-mapped reg

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, write_data);

    // appending data dwords
    for (uint32_t i = 0; i < count; ++i) {
      APPEND_COMMAND_WRAPPER(cmdbuf, data[i]);
    }

    if (count & 1) {
      // Insert a NOP spacer
      PM4MEC_NOP nop{};
      nop.header = MakePacket3Header(IT_NOP, sizeof(nop));
      APPEND_COMMAND_WRAPPER(cmdbuf, nop);
    }
  }

  void BuildIndirectBufferCmd(CmdBuffer* cmdbuf, const void* cmd_addr, std::size_t cmd_size) {
    // Verify the address is 4-byte aligned
    assert(!(uintptr_t(cmd_addr) & 0x3) && "IndirectBuffer address must be 4 byte aligned");

    PM4MEC_INDIRECT_BUFFER indirect_buffer{};

    // Initialize the command header
    indirect_buffer.header = MakePacket3Header(IT_INDIRECT_BUFFER, sizeof(indirect_buffer));

    // Specify the address of indirect buffer encoding cmd stream
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

}  // namespace pm4_builder

#endif  //  SRC_PM4_GFX9_CMD_BUILDER_H_
