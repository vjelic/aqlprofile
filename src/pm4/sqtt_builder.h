#ifndef _THREAD_TRACE_H_
#define _THREAD_TRACE_H_

#include <stdint.h>

namespace pm4_builder {
class CmdBuffer;
class CmdBuilder;
class ThreadTraceConfig;

enum {
  // Mask to check if SQTT buffer is wrapped
  TT_CONTROL_WRAP_MASK = 0x80000000,
  // Move them as static variables later on
  TT_WRITE_PTR_MASK = 0x3FFFFFFF,
  // Size of block in bytesper increment in WPTR
  TT_WRITE_PTR_BLK = 32,
  // Factor by which to shift buffer address
  TT_BUFF_ALIGN_SHIFT = 12
};

// Thread traces status register indices to determine
// status of thread trace run
enum {
  TT_STATUS_IDX_STATUS = 0,
  TT_STATUS_IDX_CNTR = 1,
  TT_STATUS_IDX_WPTR = 2,
  TT_STATUS_IDX_MAX = 3
};
typedef uint32_t ControlType;


// SqttBuilder config
struct ThreadTraceConfig {
  uint32_t targetCu;
  uint32_t vmIdMask;
  uint32_t mask;
  uint32_t tokenMask;
  uint32_t tokenMask2;

  void* control_buffer_ptr;
  void* data_buffer_ptr;
  uint32_t data_buffer_size;

  // number of Shader Engines on the device
  uint32_t se_number;
};

// Encapsulates the various Api and structures that are used to enable
// a thread trace session and collect its data. Implementations of this
// interface program device specific registers to realize the functionality
class SqttBuilder {
 public:
  // Destructor of the thread trace service handle
  virtual ~SqttBuilder(){};

  // Builds Pm4 command stream to program hardware registers that
  // enable a thread trace session, including the issue of an event
  // to begin thread session
  virtual void BeginSession(CmdBuffer* cmdBuff, const ThreadTraceConfig* config) = 0;

  // Builds Pm4 command stream to program hardware registers that
  // disable a thread trace session, including the issue of an event
  // to stop currently ongoing thread session
  virtual void StopSession(CmdBuffer* cmdBuff, const ThreadTraceConfig* config) = 0;
};

}  // pm4_builder

#endif  // _THREAD_TRACE_H_
