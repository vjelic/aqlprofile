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

#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype>
#include <algorithm>
#include <regex>
#include <vector>
#include <fstream>
#include <cassert>
#include <utility>
#include <string_view>
#include <cstdint>
#include <stdint.h>
enum class InstCategory {
  SKIP = 0,
  SMEM = 1,
  SALU = 2,
  VMEM = 3,
  FLAT = 4,
  LDS = 5,
  VALU = 6,
  IMMED = 9,
  BRANCH = 10,
  GETPC = 11,
  SETPC = 12,
  SWAPPC = 13,
  LANE = 14,
  DONT_KNOW = 100,
  NEGATIVE = -1
};

inline bool operator==(const InstCategory& cat, uint64_t value) { return static_cast<uint64_t>(cat) == value; }
inline bool operator==(uint64_t value, const InstCategory& cat) { return static_cast<uint64_t>(cat) == value; }

class Trie {
 public:
  Trie() = default;
  ~Trie();

  InstCategory type_from_trie(const std::string_view inst);

  static Trie root_trie;
  static std::unordered_map<std::string, InstCategory> type_dict;

  static InstCategory inst_type(const std::string_view line) {
    if (line.find("branch") != std::string::npos)
        return InstCategory::BRANCH;
    else
        return root_trie.type_from_trie(line.substr(0, line.find(' ')));
  }

 private:
  void add_type(const std::string& inst_header, InstCategory type);

  bool bInit = false;
  InstCategory type = InstCategory::NEGATIVE;
  std::unordered_map<char, Trie*> paths;  //  Change to smart pointer
};

typedef struct {
  std::string line;
  InstCategory value;
  int to_line;
  std::string loc;
  uint32_t index;
  int line_num;
  int64_t addr;
} processed_t;

typedef std::pair<std::vector<processed_t>, std::unordered_map<int, int>> AsParseRetype;

inline std::string_view strip(std::string_view input)
{
  if (input.size() == 0) return input; 
  const char* start_it = input.data();
  const char* end_it = input.data()+input.size()-1;

  while (start_it != end_it && std::isspace(*start_it)) ++start_it;
  while (end_it != start_it && std::isspace(*end_it)) --end_it;
  return std::string_view(start_it, static_cast<uint64_t>(end_it+1-start_it));
}
