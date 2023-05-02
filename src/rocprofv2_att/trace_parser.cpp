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

#include <sys/stat.h>
#include <sstream>
#include <cstring>
#include <cassert>
#include "gfx9/gfx9wave.h"
#include "gfx9/gfx9token.h"
#include "gfx10/gfx10wave.h"
#include "gfx10/gfx10token.h"
#include "gfx11/gfx11wave.h"
#include "gfx11/gfx11token.h"

struct wavedata_persist_t : public wavedata_t {
  wavedata_persist_t() = default;
  wavedata_persist_t(wavedata_persist_t&) = delete;
  wavedata_persist_t(const wavedata_persist_t&) = delete;

  void Copy(gfx9wave_t& data) {
    Delete();
    std::memcpy(static_cast<void*>(this), static_cast<wavedata_t*>(&data), sizeof(wavedata_t));

    std::stringstream timeline_stream;
    for (auto& inst : data.timeline)
      timeline_stream << '(' << inst.first << ", " << inst.second << "),";

    std::string time_string = timeline_stream.str();
    if (time_string.size() == 0)
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
    if (inst_string.size() == 0)
      inst_string = " ";  // assert size > 0
    this->instructions_string = new char[inst_string.size()];
    std::memcpy(this->instructions_string, inst_string.c_str(), inst_string.size());
    this->instructions_string[inst_string.size()-1] = 0;  // Remove last comma, ensures null char
  }

  void Copy(gfx10wave_t& data) {
    Delete();
    std::memcpy(static_cast<void*>(this), static_cast<wavedata_t*>(&data), sizeof(wavedata_t));

    std::stringstream timeline_stream;
    for (auto& inst : data.timeline)
      timeline_stream << '(' << inst.first << ", " << inst.second << "),";

    std::string time_string = timeline_stream.str();
    if (time_string.size() == 0)
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
    if (inst_string.size() == 0)
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
std::vector<occupancy_info_t> occupancy;


return_info_t AnalyseBinary_GFX9(const uint8_t* tokendata, int buffersize, int target_cu) {
  std::vector<gfx9Token> tokens = gfx9Token::parse(tokendata, buffersize);

  gfx9Token::patch_time(tokens);
  auto result = gfx9wave_t::sqtt_simd_analysis(tokens, target_cu);
  occupancy = std::get<2>(result);

  int num_waves = 0;
  for (auto& Wave_j : std::get<0>(result))
    for (auto& Wave_ij : Wave_j) num_waves += Wave_ij.size();

  wavedata = std::vector<wavedata_persist_t>(num_waves);
  num_waves = 0;

  for (uint64_t simd = 0; simd < gfx9wave_t::SQTT_CFG_SIMDS; simd++)
    for (uint64_t wave_id = 0; wave_id < gfx9wave_t::SQTT_CFG_WAVES; wave_id++)
      for (gfx9wave_t& wave : std::get<0>(result)[simd][wave_id]) {
        wavedata[num_waves].Copy(wave);
        wavedata[num_waves].simd = simd;
        wavedata[num_waves].wave_id = wave_id;
        num_waves += 1;
      }

  perfevents = std::move(std::get<1>(result));

  return_info_t info;
  info.wavedata = wavedata.data();
  info.num_waves = wavedata.size();
  info.perfevents = perfevents.data();
  info.num_events = perfevents.size();
  info.occupancy = occupancy.data();
  info.num_occupancy = occupancy.size();
  info.flags = _output_flags_t{ .isNavi = false };
  return info;
}

return_info_t AnalyseBinary_GFX10(const uint8_t* tokendata, int buffersize, int target_cu) {
  std::vector<gfx10Token> tokens = gfx10Token::parse(tokendata, buffersize);

  auto result = gfx10wave_t::sqtt_simd_analysis(tokens, target_cu);
  occupancy = std::get<2>(result);

  int num_waves = 0;
    for (auto& Wave_ij : std::get<0>(result)) num_waves += Wave_ij.size();

  wavedata = std::vector<wavedata_persist_t>(num_waves);
  num_waves = 0;

  for (uint64_t wave_id = 0; wave_id < gfx10wave_t::SQTT_CFG_WAVES; wave_id++) {
    for (gfx10wave_t& wave : std::get<0>(result)[wave_id]) {
      wavedata[num_waves].Copy(wave);
      wavedata[num_waves].simd = wave.target_simd;
      wavedata[num_waves].wave_id = wave_id;
      num_waves += 1;
    }
  }

  perfevents = std::move(std::get<1>(result));

  return_info_t info;
  info.wavedata = wavedata.data();
  info.num_waves = wavedata.size();
  info.perfevents = perfevents.data();
  info.num_events = perfevents.size();
  info.occupancy = occupancy.data();
  info.num_occupancy = occupancy.size();
  info.flags = _output_flags_t{ .isNavi = true };
  return info;
}

return_info_t AnalyseBinary_GFX11(const uint8_t* tokendata, int buffersize, int target_cu) {
  std::vector<gfx10Token> tokens = gfx11Token::parse(tokendata, buffersize);

  auto result = gfx11wave_t::sqtt_simd_analysis(tokens, target_cu);
  occupancy = std::get<2>(result);

  int num_waves = 0;
  for (auto& Wave_ij : std::get<0>(result)) num_waves += Wave_ij.size();

  wavedata = std::vector<wavedata_persist_t>(num_waves);
  num_waves = 0;

  for (uint64_t wave_id = 0; wave_id < gfx11wave_t::SQTT_CFG_WAVES; wave_id++) {
    for (gfx10wave_t& wave : std::get<0>(result)[wave_id]) {
      wavedata[num_waves].Copy(wave);
      wavedata[num_waves].simd = wave.target_simd;
      wavedata[num_waves].wave_id = wave_id;
      num_waves += 1;
    }
  }

  perfevents = std::move(std::get<1>(result));

  return_info_t info;
  info.wavedata = wavedata.data();
  info.num_waves = wavedata.size();
  info.perfevents = perfevents.data();
  info.num_events = perfevents.size();
  info.occupancy = occupancy.data();
  info.num_occupancy = occupancy.size();
  info.flags = _output_flags_t{ .isNavi = true };
  return info;
}

static int filesize(const char* filename) {
    struct stat stat_buf;
    int rc = stat(filename, &stat_buf);
    return (rc != -1) ? stat_buf.st_size : -1;
}

extern "C" {
__attribute__((visibility("default")))
return_info_t AnalyseBinary(const char* filename, int target_cu, bool verbose) {
  const int BUFFER_SIZE = filesize(filename);

  if (BUFFER_SIZE < 8) {
    std::cout << "Invalid filename: " << filename << std::endl;
    return {};
  }

  std::ifstream file(filename, std::ios::binary);
  assert(file.good());

  uint8_t* buffer = new uint8_t[BUFFER_SIZE+8];
  std::memset(buffer+BUFFER_SIZE, 0, 8); // Extra space to avoid overflow
  file.read((char*)buffer, BUFFER_SIZE);

  header_type header = *reinterpret_cast<header_type*>(buffer);

  if (header.version == 3)
    return AnalyseBinary_GFX11(buffer, BUFFER_SIZE, target_cu);
  else if (header.version == 2 || header.version == 1)
    return AnalyseBinary_GFX10(buffer, BUFFER_SIZE, target_cu);
  else
    return AnalyseBinary_GFX9(buffer, BUFFER_SIZE, target_cu);
}
}
