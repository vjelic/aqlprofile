#ifndef SRC_PM4_GFX12_CMD_BUILDER_H_
#define SRC_PM4_GFX12_CMD_BUILDER_H_

#include <assert.h>
#include <string.h>

#include <iomanip>
#include <iostream>
#include <sstream>

#include "pm4/cmd_builder.h"
#include "def/gfx12_def.h"
namespace pm4_builder {

/// @brief class Gfx12CmdBuilder implements the virtual class CmdBuilder
/// for GFX12 chipsets
class Gfx12CmdBuilder : public CmdBuilder {
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

  struct PM4MEC_EVENT_WRITE_NON_SAMPLE
  {
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1;
    };

    union
    {
        struct
        {
            uint32_t event_type:6;
            uint32_t reserved1:2;
            MEC_EVENT_WRITE_event_index_enum event_index:4;
            uint32_t reserved2:17;
            MEC_EVENT_WRITE_samp_plst_cntr_mode_enum samp_plst_cntr_mode:2;
            uint32_t offload_enable:1;
        } bitfields2;
        uint32_t ordinal2;
    };
  };

  void BuildThreadTraceCommand(CmdBuffer* cmdBuf, uint32_t event_type) {
    PM4MEC_EVENT_WRITE_NON_SAMPLE event_write{};

    // Initialize the command header
    event_write.header = MakePacket3Header(IT_EVENT_WRITE, sizeof(event_write));

    event_write.bitfields2.event_type = event_type;
    event_write.bitfields2.event_index = event_index__mec_event_write__other;

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdBuf, event_write);
  }

  void BuildThreadTraceEventFinish(CmdBuffer* cmdBuf) {
    BuildThreadTraceCommand(cmdBuf, THREAD_TRACE_FINISH);
  }

  virtual void BuildBarrierCommand(CmdBuffer* cmdBuf) {
    PM4MEC_EVENT_WRITE_NON_SAMPLE event_write{};

    // Initialize the command header
    event_write.header = MakePacket3Header(IT_EVENT_WRITE, sizeof(event_write));

    event_write.bitfields2.event_type = CS_PARTIAL_FLUSH;
    event_write.bitfields2.event_index = event_index__mec_event_write__cs_partial_flush;

    //event_write.bitfields2.offload_enable = 1;

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdBuf, event_write);
  }

  void BuildWriteWaitIdlePacket(CmdBuffer* cmdbuf) {
    BuildBarrierCommand(cmdbuf);
  }

  void BuildCacheFlushPacket(CmdBuffer* cmdbuf, size_t addr, size_t size) override
  {
    PM4MEC_ACQUIRE_MEM cache_flush{};
    // Initialize the command header
    cache_flush.header = MakePacket3Header(IT_ACQUIRE_MEM, sizeof(cache_flush));

    // Specify the base address of memory to invalidate.
    // The address must be 256 byte aligned.
    cache_flush.coher_base_lo = uint32_t(addr>>8);
    cache_flush.bitfields6.coher_base_hi = uint8_t(addr>>40);

    // Specify the size of memory to invalidate.
    // Size is specified in terms of 256 byte chunks. A coher_size
    // of 0xFFFFFFFF actually specified 0xFFFFFFFF00 (40 bits)
    // of memory. The field coher_size_hi specifies memory from
    // bits 40-64 for a total of 256 TB.
    size = ((addr%256+size)>>8) + ((size+0xFF)>>8) - (size>>8);
    cache_flush.coher_size = uint32_t(size);
    cache_flush.bitfields4.coher_size_hi = uint32_t(size>>32);

    // Specify the poll interval for determing if operation is complete
    cache_flush.bitfields7.poll_interval = 0x10;

    // Program GCR Control Register. Initialize L2 Cache flush
    // for Non-Coherent memory blocks
    //cache_flush.ordinal8 = (GCR_CNTL__SEQ_FORWARD & GCR_CNTL__SEQ_MASK) | GCR_CNTL__GL2_WB_MASK;
    cache_flush.ordinal8 = (0x00010000L & 0x00030000L) | 0x00008000L;
    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, cache_flush);
  }

  void BuildWaitRegMemCommand(CmdBuffer* cmdbuf, bool mem_space, uint64_t wait_addr, bool func_eq,
                              uint32_t mask_val, uint32_t wait_val) override {
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
      wait_reg_mem.bitfields3a.mem_poll_addr_lo = (Low32(wait_addr) >> 2);
      wait_reg_mem.mem_poll_addr_hi = High32(wait_addr);
     }
     else
       wait_reg_mem.bitfields3b.reg_poll_addr = wait_addr;

     // Append the built command into output Command Buffer
     APPEND_COMMAND_WRAPPER(cmdbuf, wait_reg_mem);
    }

  void BuildWriteShRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) override {
      PM4MEC_SET_SH_REG set_sh_reg{};

      // Initialize the command header
      set_sh_reg.header = MakePacket3Header(IT_SET_SH_REG, sizeof(set_sh_reg) + sizeof(value));
      set_sh_reg.bitfields2.reg_offset = (addr - PERSISTENT_SPACE_START);
      set_sh_reg.bitfields2.index = index__mec_set_sh_reg__default;
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
    copy_data.bitfields2.src_temporal = src_temporal__mec_copy_data__lu;

    copy_data.bitfields2.dst_sel = IsPrivilegedConfigReg(addr)
                                       ? dst_sel__mec_copy_data__perfcounters
                                       : dst_sel__mec_copy_data__mem_mapped_register;

    copy_data.bitfields2.dst_temporal = dst_temporal__mec_copy_data__lu;

    // wr_confirm__mec_copy_data__wait_for_confirmation
    copy_data.bitfields2.wr_confirm = wr_confirm__mec_copy_data__do_not_wait_for_confirmation;
    copy_data.bitfields2.count_sel = count_sel__mec_copy_data__32_bits_of_data;

    copy_data.imm_data = value;

    copy_data.dst_reg_offset_lo = addr;

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, copy_data);
  }

  void BuildWriteConfigRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) {
    return IsPrivilegedConfigReg(addr) ? BuildWritePConfigRegPacket(cmdbuf, addr, value)
                                       : BuildWriteUConfigRegPacket(cmdbuf, addr, value);
  }

 void BuildCopyRegDataPacket(CmdBuffer* cmdbuf, uint32_t src_reg_addr, const void* dst_addr,
                            uint32_t size, bool wait){
    PM4MEC_COPY_DATA copy_data{};

    // Initialize the command header
    copy_data.header = MakePacket3Header(IT_COPY_DATA, sizeof(copy_data));

    copy_data.bitfields2.src_sel = IsPrivilegedConfigReg(src_reg_addr)
                                       ? src_sel__mec_copy_data__perfcounters
                                       : src_sel__mec_copy_data__mem_mapped_register;
    copy_data.bitfields2.src_temporal = src_temporal__mec_copy_data__lu;
    copy_data.bitfields2.dst_sel = dst_sel__mec_copy_data__tc_l2;
    copy_data.bitfields2.dst_temporal = dst_temporal__mec_copy_data__lu;

    copy_data.bitfields2.wr_confirm = (MEC_COPY_DATA_wr_confirm_enum)wait;
    copy_data.bitfields2.count_sel = (size == 0) ? count_sel__mec_copy_data__32_bits_of_data
                                                 : count_sel__mec_copy_data__64_bits_of_data;

    // Specify the source register offset
    copy_data.src_reg_offset_lo = src_reg_addr;

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
    write_data.dst_mmreg_addr_lo = dst_reg_addr;  // mem-mapped reg

    // ordinal4
    write_data.dst_mem_addr_hi = 0;  // mem-mapped reg

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, write_data);

    // appending data dwords
    APPEND_COMMAND_WRAPPER(cmdbuf, data, count);

    if (count & 1) {
      // Insert a NOP spacer
      BuildNopPacket(cmdbuf, 1);
    }
  }

  void BuildNopPacket(CmdBuffer* cmdbuf, uint32_t num_dwords) {
      PM4MEC_NOP nop{};
      nop.header = MakePacket3Header(IT_NOP, num_dwords * sizeof(uint32_t));
      APPEND_COMMAND_WRAPPER(cmdbuf, nop);
      if (num_dwords > 1) {
        std::vector<uint32_t> data_block((num_dwords - 1), 0);
        APPEND_COMMAND_WRAPPER(cmdbuf, data_block.data(), (num_dwords - 1));
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
    indirect_buffer.bitfields4.temporal = temporal__mec_indirect_buffer__lu;

    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdbuf, indirect_buffer);
  }

  void BuildPredExecPacket(CmdBuffer* cmdbuf, uint32_t xcc_id = 0, uint32_t exec_count = 0) {}

  void BuildMutexAcquirePacket(CmdBuffer* cmdbuf, size_t addr) override
  {
    PM4_MEC_ATOMIC_MEM atomic{};
    atomic.header = MakePacket3Header(IT_ATOMIC_MEM, sizeof(atomic));

    atomic.bitfields2.command = command__mec_atomic_mem__loop_until_compare_satisfied;
    atomic.bitfields2.atomic = atomic__mec_atomic_mem__gl2_op_atomic_cmpswap_rtn_32;
    atomic.bitfields9.loop_interval = 16;

    atomic.addr_lo = uint32_t(addr);
    atomic.addr_hi = addr >> 32;
    atomic.src_data_lo = MakeMutexSlot();
    atomic.cmp_data_lo = 0;

    APPEND_COMMAND_WRAPPER(cmdbuf, atomic);
  }

  void BuildMutexReleasePacket(CmdBuffer* cmdbuf, size_t addr) override
  {
    PM4_MEC_ATOMIC_MEM atomic{};
    atomic.header = MakePacket3Header(IT_ATOMIC_MEM, sizeof(atomic));

    atomic.bitfields2.command = command__mec_atomic_mem__single_pass_atomic;
    atomic.bitfields2.atomic = atomic__mec_atomic_mem__gl2_op_atomic_swap_rtn_32;

    atomic.addr_lo = uint32_t(addr);
    atomic.addr_hi = addr >> 32;
    atomic.src_data_lo = 0;

    APPEND_COMMAND_WRAPPER(cmdbuf, atomic);
  }
};

}  // namespace pm4_builder

#endif  //  SRC_PM4_GFX12_CMD_BUILDER_H_
