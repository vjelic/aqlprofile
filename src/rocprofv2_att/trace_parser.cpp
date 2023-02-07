/* Copyright (c) 2022 Advanced Micro Devices, Inc.

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE. */

#include "wave.h"
#include <sstream>
#include <cstring>

typedef struct {
  uint64_t num_waves;
  void* wavedata;
  uint64_t num_events;
  perfevent_t* perfevents;
} return_info_t;

struct wavedata_persist_t : public wavedata_t {
  wavedata_persist_t() = default;
  wavedata_persist_t(wavedata_persist_t&) = delete;
  wavedata_persist_t(const wavedata_persist_t&) = delete;

  void Copy(wave_t& data) {
    Delete();
    std::memcpy((char*)this, (char*)(wavedata_t*)&data, sizeof(wavedata_t));

    std::stringstream timeline_stream;
    for (auto& inst : data.timeline)
      timeline_stream << '(' << inst.first << ", " << inst.second << "),";

    std::string time_string = timeline_stream.str();
    if(time_string.size() == 0)
      time_string = " ";  // assert size > 0
    this->timeline_string = new char[time_string.size()];
    std::memcpy(this->timeline_string, time_string.c_str(), time_string.size());
    this->timeline_string[time_string.size()-1] = 0;  // Remove last comma, ensures null char

    std::stringstream inst_stream;
    for (instruction_t& inst : data.instructions) {
      inst_stream << '(' << inst.time << ", " << static_cast<int>(inst.value) << ", "
                  << inst.issue2inst << ", " << inst.last << "),";
    }

    std::string inst_string = inst_stream.str();
    if(inst_string.size() == 0)
      inst_string = " ";  // assert size > 0
    this->instructions_string = new char[inst_string.size()];
    std::memcpy(this->instructions_string, inst_string.c_str(), inst_string.size());
    this->instructions_string[inst_string.size()-1] = 0;  // Remove last comma, ensures null char
  }

  void Delete() {
    if (this->instructions_string) delete[] this->instructions_string;
    this->instructions_string = nullptr;

    if (this->timeline_string) delete[] this->timeline_string;
    this->timeline_string = nullptr;
  }

  ~wavedata_persist_t() { Delete(); }
};

std::vector<wavedata_persist_t> wavedata;
std::vector<perfevent_t> perfevents;

extern "C" {
__attribute__((visibility("default")))
return_info_t AnalyseBinary(const char* filename, int target_cu, bool verbose) {
  if (verbose) std::cout << ">>> Parsing SQTT tokens, this may take a while ..." << std::endl;
  std::vector<Token> tokens = Token::parse(filename);

  Token::patch_time(tokens);
  if (verbose) std::cout << ">>> Analyzing waves ..." << std::endl;
  auto result = wave_t::sqtt_simd_analysis(tokens, target_cu);
  if (verbose) std::cout << "done." << std::endl;

  int num_waves = 0;
  for (auto& Wave_j : result.first)
    for (auto& Wave_ij : Wave_j) num_waves += Wave_ij.size();

  wavedata = std::vector<wavedata_persist_t>(num_waves);
  num_waves = 0;

  for (uint64_t simd = 0; simd < SQTT_CFG_SIMDS; simd++)
    for (uint64_t wave_id = 0; wave_id < SQTT_CFG_WAVES; wave_id++)
      for (wave_t& wave : result.first[simd][wave_id]) {
        wavedata[num_waves].Copy(wave);
        wavedata[num_waves].simd = simd;
        wavedata[num_waves].wave_id = wave_id;
        num_waves += 1;
      }

  perfevents = std::move(result.second);

  return_info_t info;
  info.wavedata = wavedata.data();
  info.num_waves = wavedata.size();
  info.perfevents = perfevents.data();
  info.num_events = perfevents.size();
  return info;
}
}
