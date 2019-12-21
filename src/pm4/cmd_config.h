#ifndef SRC_PM4_CMD_CONFIG_H_
#define SRC_PM4_CMD_CONFIG_H_

#include <stdint.h>

namespace pm4_builder {
// Counters vector class
class counters_vector : public std::vector<counter_des_t> {
 public:
  typedef std::vector<counter_des_t> Parent;

  counters_vector() : Parent(), attr_(0) {}

  void push_back(const counter_des_t& des) {
    Parent::push_back(des);
    attr_ |= des.block_info->attr;
  }

  uint32_t get_attr() const { return attr_; }

 private:
  uint32_t attr_;
};

// SqttBuilder config
struct TraceConfig {
  uint32_t targetCu;
  uint32_t vmIdMask;
  uint32_t mask;
  uint32_t tokenMask;
  uint32_t tokenMask2;
  // Sampling rate
  uint32_t sampleRate;
  bool sq_spm_32_bit;

  void* control_buffer_ptr;
  void* data_buffer_ptr;
  uint32_t data_buffer_size;

  // SE number for tracing
  uint32_t se_number;
  // SE mask for tracing
  uint32_t se_vector;

  // concurrent kernels mode
  uint32_t concurrent;
};
}  // namespace pm4_builder

#endif  // SRC_PM4_CMD_CONFIG_H_
