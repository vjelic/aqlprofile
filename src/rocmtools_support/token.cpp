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

#include "token.h"

std::unordered_map<uint32_t, uint32_t> token_len_dict = {{0, 16},
                                                         {1, 64},
                                                         {2, 64},
                                                         {3, 32},
                                                         {4, 16},
                                                         {5, 48},
                                                         {6, 16},
                                                         {7, 16},
                                                         {8, 16},
                                                         {9, 16},
                                                         {10, 16},
                                                         {11, 64},
                                                         {12, 48},
                                                         {13, 32},
                                                         {14, 64},
                                                         {15, 48}};

uint32_t get_msg_len(uint32_t type) {
  try {
    return token_len_dict[type];
  } catch (std::exception& e) {
    std::cout << "Unknown Token type " << type << ", exitting." << std::endl;
    exit(-1);
  }
}

template <typename Type> Type unpack(std::ifstream& file) {}
template <> uint32_t unpack<uint32_t>(std::ifstream& file) {
  uint32_t ret;
  file.read((char*)&ret, sizeof(ret));
  return ret;
}
template <> uint16_t unpack<uint16_t>(std::ifstream& file) {
  uint16_t ret;
  file.read((char*)&ret, sizeof(ret));
  return ret;
}

std::vector<Token> Token::parse(const std::string& filename) {
  struct stat Stat;
  stat(filename.c_str(), &Stat);
  int total_len = Stat.st_size;
  int curr_len = 0;

  std::ifstream file(filename, std::ios::in | std::ios::binary);
  if (!file.good()) {
    std::cout << ">>> Error: File empty or wrong path." << std::endl;
    exit(0);
  }

  std::vector<Token> tokens;

  while (curr_len < total_len) {
    uint64_t curr = unpack<uint16_t>(file);
    uint64_t type = curr & 15;
    int msg_len = get_msg_len(type);

    if (msg_len == 16) {
      tokens.push_back(Token(type, curr));
      curr_len += 2;
    } else if (msg_len == 32) {
      uint64_t high = unpack<uint16_t>(file);
      tokens.push_back(Token(type, (high << 16) + curr));
      curr_len += 4;
    } else if (msg_len == 48) {
      uint64_t high = unpack<uint32_t>(file);
      tokens.push_back(Token(type, (high << 16) + curr));
      curr_len += 6;
    } else if (msg_len == 64) {
      uint64_t mid = unpack<uint16_t>(file);
      uint64_t high = unpack<uint32_t>(file);
      tokens.push_back(Token(type, (high << 32) + (mid << 16) + curr));
      curr_len += 8;
    }
  }

  return tokens;
}

std::unordered_map<int, std::string> misc_token_type_dict = {
    {0, "TIME"},      {1, "TIME_RESET"},         {2, "PACKET_LOST"},
    {3, "SURF_SYNC"}, {4, "TTRACE_STALL_BEGIN"}, {5, "TTRACE_STALL_END"}};

void Token::patch_time(std::vector<Token>& tokens) {
  uint64_t base_time = 0, rel_time = 0;
  int last_reset_time_idx = -1;

  for (uint64_t i = 0; i < tokens.size(); i++) {
    Token& token = tokens[i];

    if (token.type == 1) {
      if (last_reset_time_idx < 0 && base_time != 0) {
        std::cout << "[" << rel_time
                  << "] TIMESTAMP must be the 1st packet or preceded by a TIME_RESET, skip "
                     "TIMESTAMP Token"
                  << std::endl;
        continue;
      }

      if (base_time == 0) base_time = token.time - rel_time;

      // std::cout << "32 " << token.time << " " << base_time << std::endl;
      // std::cout << "33 " << (token.time - base_time) << std::endl;
      rel_time = ((token.time - base_time) / 4) * 4 - 4;  // Set or rewind timer
      // std::cout << "35 " << rel_time << std::endl;

      if (last_reset_time_idx >= 0) {
        tokens[last_reset_time_idx].time = rel_time;
        for (uint64_t j = last_reset_time_idx + 1; j < i; j++) {
          rel_time += tokens[j].delta * 4;
          tokens[j].time = rel_time;
        }
        last_reset_time_idx = -1;
      }

      token.time = rel_time;
    } else if (token.type == 0 && token.misc_type == 1) {
      if (last_reset_time_idx >= 0) {
        std::cout << "[" << rel_time
                  << "] Cascading TIME_RESET tokens without any TIMESTAMP token in-between, skip "
                     "RESET token"
                  << std::endl;
        continue;
      }

      rel_time += token.delta * 4;
      token.time = rel_time;
      last_reset_time_idx = i;
    } else if (token.type == 0 &&
               (token.misc_type == 2 || token.misc_type == 4 || token.misc_type == 5)) {
      rel_time += token.delta * 4;
      token.time = rel_time;
      std::cout << misc_token_type_dict[token.misc_type] << " : " << rel_time << std::endl;
    } else if (last_reset_time_idx < 0) {
      rel_time += token.delta * 4;
      token.time = rel_time;
    }
  }
}
