#ifndef SRC_PM4_TRACE_CONFIG_H_
#define SRC_PM4_TRACE_CONFIG_H_

#include <stdint.h>

namespace pm4_builder {
// SqttBuilder config
struct TraceConfig {
  uint32_t targetCu;
  uint32_t vmIdMask;
  uint32_t mask;
  uint32_t tokenMask;
  uint32_t tokenMask2;
  // Sampling rate
  uint32_t sampleRate;

  void* control_buffer_ptr;
  void* data_buffer_ptr;
  uint32_t data_buffer_size;

  // SE number for tracing
  uint32_t se_number;
  // SE mask for tracing
  uint32_t se_vector;
};
}  // namespace pm4_builder

#endif  // SRC_PM4_TRACE_CONFIG_H_
