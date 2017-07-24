#ifndef _GPU_BLOCKINFO_H_
#define _GPU_BLOCKINFO_H_

#include <stdint.h>

#define GPU_BLOCK_NAME_SIZE 15

namespace gfxip {
typedef enum CntlMethod {
  CntlMethodNone = 0,
  CntlMethodByInstance = 1,
  CntlMethodBySe = 2,
  CntlMethodBySeAndInstance = 3
} CntlMethod;

// Register address corresponding to each counter
typedef struct GpuCounterRegInfo_ {
  // counter select register address
  uint32_t counterSelRegAddr;

  // counter control register address
  uint32_t counterCntlRegAddr;

  // counter read register address low
  uint32_t counterReadRegAddrLo;

  // counter read register address high
  uint32_t counterReadRegAddrHi;
} GpuCounterRegInfo;

// Structure which contains information about a specific hardware block for CI.
typedef struct GpuBlockInfo_ {
  // Unique string identifier of the block.
  const char blockName[GPU_BLOCK_NAME_SIZE];

  // Unique string identifier of the block.
  uint32_t counterGroupId;

  // Maximum number of block instances in the group per shader array
  uint32_t maxInstanceCount;

  // Counter control method
  CntlMethod method;

  // Maximum counter event ID
  uint32_t maxEventId;

  // Maximum number of counters that can be enabled at once
  uint32_t maxSimultaneousCounters;

  // Maximum number of streaming counters that can be enabled at once
  uint32_t maxStreamingCounters;

  // The number of hardware counters that are shared
  // between regular and streaming counters.
  // This is important so that resources are not double-booked
  // between the two types of counters.
  uint32_t sharedHWCounters;

  // Block counters can be configured with additional filters
  bool hasFilters;

  // Counter registers addresses
  const GpuCounterRegInfo *counter_reg_info;

} GpuBlockInfo;

}  // namespace gfxip

#endif  // _GPU_BLOCKINFO_H_
