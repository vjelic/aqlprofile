#ifndef _GPU_BLOCKINFO_H_
#define _GPU_BLOCKINFO_H_

#include <stdint.h>

namespace gfxip {

enum CntlMethod {
  CntlMethodNone = 0,
  CntlMethodByInstance = 1,
  CntlMethodBySe = 2,
  CntlMethodBySeAndInstance = 3
};

// Register address corresponding to each counter
struct CounterRegInfo {
  // counter select register address
  uint32_t select_addr;
  // counter control register address
  uint32_t control_addr;
  // counter register address low
  uint32_t register_addr_lo;
  // counter register address high
  uint32_t register_addr_hi;
};

struct counter_des_t;

// Structure which contains information about a specific hardware block for CI.
struct GpuBlockInfo {
  // Unique string identifier of the block.
  const char* name;
  // Block ID
  uint32_t id;
  // Maximum number of block instances in the group per shader array
  uint32_t instance_count;
  // Counter control method
  CntlMethod method;
  // Maximum counter event ID
  uint32_t event_id_max;
  // Maximum number of counters that can be enabled at once
  uint32_t counter_count;
  // Maximum number of streaming counters that can be enabled at once
  uint32_t streaming_count;
  // The number of hardware counters that are shared
  // between regular and streaming counters.
  // This is important so that resources are not double-booked
  // between the two types of counters.
  uint32_t shared_count;
  // Block counters can be configured with additional filters
  bool has_filters;
  // Counter registers addresses
  const CounterRegInfo* counter_reg_info;
  // Need to clean counter registers
  bool to_clean_regs;
  // Counter select value function
  uint32_t (*select_value)(const counter_des_t&);
  // SQ block
  bool sq_block;
};

struct block_des_t {
  uint32_t id;
  uint32_t index;
};

struct lt_block_des {
  bool operator()(const block_des_t& a1, const block_des_t& a2) const {
    return (a1.id < a2.id) || ((a1.id == a2.id) && (a1.index < a2.index));
  }
};

struct counter_des_t {
  uint32_t id;
  block_des_t block_des;
  const GpuBlockInfo* block_info;
};

}  // namespace gfxip

#endif  // _GPU_BLOCKINFO_H_
