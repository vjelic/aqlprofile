#ifndef SRC_PM4_GFX10_CMD_BUILDER_H_
#define SRC_PM4_GFX10_CMD_BUILDER_H_

#include "def/gfx10_def.h"
#include "pm4/gfx9_cmd_builder.h"

namespace pm4_builder {
/// @brief class Gfx10CmdBuilder implements the virtual class CmdBuilder
/// for GFX10 gpus
class Gfx10CmdBuilder : public Gfx9CmdBuilder {
 private:
  // @brief Return a Type 3 PM4 packet header
  static PM4_MEC_TYPE_3_HEADER MakePacket3Header(uint32_t opcode, size_t packet_size) {
    PM4_MEC_TYPE_3_HEADER header{};
    header.opcode = opcode;
    header.count = packet_size / sizeof(uint32_t) - 2;
    header.type = 3;
    return header;
  }
//gfx10 EVENT_WRITE 2 DW packet
  typedef struct PM4_MEC_EVENT_WRITE_
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
            uint32_t reserved2:19;
            uint32_t offload_enable:1;
        } bitfields2;
        uint32_t ordinal2;
    };
  } PM4MEC_EVENT_WRITE, *PPM4MEC_EVENT_WRITE;


 public:
  static constexpr bool IsPrivilegedConfigReg(uint32_t addr) {
    return ((addr >= CONFIG_SPACE_START) && (addr <= CONFIG_SPACE_END));
  }

void BuildBarrierCommand(CmdBuffer* cmdBuf) override {
    PM4MEC_EVENT_WRITE event_write{};

    // Initialize the command header
    event_write.header = MakePacket3Header(IT_EVENT_WRITE, sizeof(event_write));

    event_write.bitfields2.event_type = CS_PARTIAL_FLUSH;
    event_write.bitfields2.reserved1 = 0;
    event_write.bitfields2.event_index = event_index__mec_event_write__cs_partial_flush;
    event_write.bitfields2.reserved2 = 0;
    // Append the built command into output Command Buffer
    APPEND_COMMAND_WRAPPER(cmdBuf, event_write);
  }

  void BuildWriteWaitIdlePacket(CmdBuffer* cmdbuf) override {
    BuildBarrierCommand(cmdbuf);
  }

  void BuildCacheFlushPacket(CmdBuffer* cmdbuf) override {
    PM4MEC_ACQUIRE_MEM cache_flush{};
  // Initialize the command header
    cache_flush.header = MakePacket3Header(IT_ACQUIRE_MEM, sizeof(cache_flush));

  // Specify the base address of memory to invalidate.
  // The address must be 256 byte aligned.
    cache_flush.coher_base_lo = 0x00;
    cache_flush.bitfields6.coher_base_hi = 0x00;

  // Specify the size of memory to invalidate.
  // Size is specified in terms of 256 byte chunks. A coher_size
  // of 0xFFFFFFFF actually specified 0xFFFFFFFF00 (40 bits)
  // of memory. The field coher_size_hi specifies memory from
  // bits 40-64 for a total of 256 TB.
    cache_flush.coher_size = 0xFFFFFFFF;
    cache_flush.bitfields4.coher_size_hi = 0xFF;

  // Specify the poll interval for determing if operation is complete
    cache_flush.bitfields7.poll_interval = 0x04;

  // Program GCR Control Register. Initialize L2 Cache flush
  // for Non-Coherent memory blocks
    cache_flush.ordinal8 = (GCR_CNTL__SEQ_FORWARD & GCR_CNTL__SEQ_MASK) | GCR_CNTL__GL2_WB_MASK;
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
  
  void BuildCopyRegDataPacket(CmdBuffer* cmdbuf, uint32_t src_reg_addr, const void* dst_addr,
                            uint32_t size, bool wait) override {
    PM4MEC_COPY_DATA copy_data{};

    // Initialize the command header
    copy_data.header = MakePacket3Header(IT_COPY_DATA, sizeof(copy_data));

    copy_data.bitfields2.src_sel = IsPrivilegedConfigReg(src_reg_addr)
                                       ? src_sel__mec_copy_data__perfcounters
                                       : src_sel__mec_copy_data__mem_mapped_register;
    copy_data.bitfields2.src_cache_policy = src_cache_policy__mec_copy_data__lru;
    copy_data.bitfields2.dst_sel = dst_sel__mec_copy_data__tc_l2;
    copy_data.bitfields2.dst_cache_policy = dst_cache_policy__mec_copy_data__lru;
    
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
  
};
}  // namespace pm4_builder

#endif //  SRC_PM4_GFX10_CMD_BUILDER_H_
