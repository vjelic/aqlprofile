// Header file for CmdBuilder and CmdBuffer interfaces

#ifndef _CMD_BUILDER_H_
#define _CMD_BUILDER_H_

#include <stdint.h>
#include <string.h>

#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

#define APPEND_COMMAND_WRAPPER(cmdbuf, command)                                                    \
  PrintPacket(command, __FUNCTION__);                                                              \
  cmdbuf->append(&command, sizeof(command));

namespace pm4_builder {

template <class T> static void PrintPacket(const T& command, const char* name) {
#if !defined(NDEBUG)
  uint32_t* cmd = (uint32_t*)&command;
  uint32_t size = sizeof(command) / sizeof(uint32_t);
  std::ostringstream oss;
  oss << "'" << name << "' size(" << std::dec << size << ")";
  std::clog << std::setw(40) << std::left << oss.str() << ":";
  for (uint32_t idx = 0; idx < size; idx++) {
    std::clog << " " << std::hex << std::right << std::setw(8) << std::setfill('0') << cmd[idx];
  }
  std::clog << std::setfill(' ') << std::endl;
#endif
}

/// @brief Implements the interface CmdBuffer and thus can be used to
/// translate various Gpu commands as byte stream.
/// @note: The Api does not require implementations to be thread safe.
/// Users are therefore required to be access in a serialized manner.
class CmdBuffer {
 public:
  typedef uint32_t value_type;

  /// @brief Append the command into the underlying buffer
  /// @param cmd Buffer containing one or more instances of Gpu commands
  /// @param size Size of Gpu command(s) in bytes
  void append(const void* cmd, uint32_t size) { memcpy(reserve(size), cmd, size); }

  /// @brief Return size of Gpu commands in bytes in the underlying buffer
  size_t size() const { return data_.size() * sizeof(value_type); }

  /// @brief Return address of the start of accumulated commands.
  const void* data() const { return &data_[0]; }

 private:
  /// @brief Increase Gpu command buffer by specified size
  /// @param size Size in bytes by which command buffer should be resized.
  /// @return Pointer into the buffer where the next command can be written
  void* reserve(std::size_t size) {
    const size_t len = data_.size();
    data_.resize(len + size / sizeof(value_type));
    return &data_[len];
  }

  /// @brief Defines Gpu command buffer as a vector of value_type
  std::vector<value_type> data_;
};

/// @brief Specifies the public interface of CmdBuilder for use by
/// clients to build Gpu command streams.
class CmdBuilder {
 public:
  /// @brief Flush all caches
  /// @param CmdBuf Buffer to write commands to
  virtual void BuildCacheFlushPacket(CmdBuffer* cmdbuf) = 0;

  /// @brief Build and copy a WaitIdle Gpu command into command buffer
  /// @param cmdbuf Pointer to command buffer to be appended
  virtual void BuildWriteWaitIdlePacket(CmdBuffer* cmdbuf) = 0;

  /// @bried Builds a Gpu command to wait until condition is realized
  /// @param cmdbuf command buffer to be appended with launch command
  /// @param mem_space if the address is in memory or is a register offset
  /// @param wait_addr address to wait on
  /// @param func_eq true means equal, false means not-equal
  /// @param mask_val Mask to apply on value from addr in comparison
  /// @param wait_val value to apply for the func given above
  virtual void BuildWaitRegMemCommand(CmdBuffer* cmdbuf, bool mem_space, uint64_t wait_addr,
                                      bool func_eq, uint32_t mask_val, uint32_t wait_val) = 0;

  /// @brief Build CP command to program a Gpu register
  /// @param cmdbuf Pointer to command buffer to be appended
  /// @param addr Register to be programmed
  /// @param value Value to write into register
  virtual void BuildWriteUConfigRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) = 0;

  /// @brief Build and copy WriteShReg command
  /// @param cmdbuf Pointer to command buffer to be appended
  /// @param addr Offset of the register
  /// @param value Value to write into register
  virtual void BuildWriteShRegPacket(CmdBuffer* cmdbuf, uint32_t addr, uint32_t value) = 0;

  /// @brief Build a Gpu command that copies data from a specified
  /// source register to destination
  /// @param cmdbuf Pointer to command buffer to be appended
  /// @param src_sel Source register selector
  /// @param src_reg_add 32-bit Source register address of the data to read from
  /// @param dst_addr Destination address for the data to be written to
  /// @param size Size of the data to be written
  /// @param  wait True if Gpu command should confirm the write operation
  /// operation has completed successfully
  virtual void BuildCopyRegDataPacket(CmdBuffer* cmdbuf, uint32_t src_reg_addr, void* dst_addr,
                                      uint32_t size, bool wait) = 0;

  /// @brief Builds the Gpu command to reference indirectly a stream
  /// of other Gpu commands. The launch command is then copied into
  /// the command buffer parameter.
  /// @param cmdBuf command buffer to be appended with launch command
  /// @param cmd_addr Address of command buffer carrying command stream
  /// @param cmd_size Size of dispatch command stream in bytes
  virtual void BuildIndirectBufferCmd(CmdBuffer* cmdbuf, const void* cmd_addr,
                                      std::size_t cmd_size) = 0;

  /// @brief Release resources used by CmdBuilder
  virtual ~CmdBuilder(){};
};

/// @brief Returns the lower 32-bits of a value
inline uint32_t Low32(uint64_t u) { return (u & 0xFFFFFFFFUL); }

/// @brief Returns the upper 32-bits of a value
inline uint32_t High32(uint64_t u) { return (u >> 32); }

/// @brief Returns the lower 32-bits of an address
inline uint32_t PtrLow32(const void* p) { return reinterpret_cast<uintptr_t>(p); }

/// @brief Returns the upper 32-bits of an address
inline uint32_t PtrHigh32(const void* p) { return reinterpret_cast<uintptr_t>(p) >> 32; }

}  // pm4_builder

#endif  // _CMD_BUILDER_H_
