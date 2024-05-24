#pragma once

#include <unordered_map>
#include <cstdint>
#include <vector>

namespace pm4_builder
{
// SqttBuilder config
struct TraceConfig {
  uint32_t targetCu = 0;
  uint32_t vmIdMask = 0xF;
  uint32_t simd_sel = 0x3;
  uint32_t occupancy_mode = 0;
  uint32_t deprecated_mask = 0;
  uint32_t deprecated_tokenMask = 0;
  uint32_t deprecated_tokenMask2 = 0;
  // Sampling rate
  uint32_t sampleRate = 625;
  // PERF
  uint32_t perfMASK = (1ul << 32) - 1;
  uint32_t perfCTRL = 0;
  std::vector<size_t> perfcounters{};
  // SPM mode
  bool spm_sq_32bit_mode = true;
  bool spm_kfd_mode = true;
  bool mi100 = false;

  void* control_buffer_ptr = nullptr;
  uint32_t control_buffer_size = 0;
  void* data_buffer_ptr = nullptr;
  uint32_t data_buffer_size = 0;

  // SE number for tracing
  uint32_t spm_se_number_total = 0;
  // concurrent kernels mode
  uint32_t concurrent = 0;
  // SE mask for tracing; note -> replicated for all XCCs
  uint64_t se_mask = 0x11;

  uint64_t capacity_per_se = 0x1000;
  uint64_t capacity_per_disabled_se = 0x1000;
  std::unordered_map<int, int> target_cu_per_se{};
  std::unordered_map<int, uint64_t> se_base_addresses{};

  int GetTargetCU(int SE) const { return target_cu_per_se.at(SE); };
  uint64_t GetSEmask() const { return se_mask; };
  uint64_t GetSEBaseAddr(int SE) const { return se_base_addresses.at(SE); }
  uint64_t GetCapacity(int SE) const {
    return (GetTargetCU(SE) >= 0) ? capacity_per_se : capacity_per_disabled_se;
  }
};

}