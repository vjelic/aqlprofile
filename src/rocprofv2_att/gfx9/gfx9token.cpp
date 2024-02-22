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

#include "gfx9token.h"

typedef gfx9Token Token;

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

template <typename Type> std::pair<Type, const uint8_t*> unpack(const uint8_t* data) {
  return {*reinterpret_cast<const Type*>(data), data+sizeof(Type)};
}

std::vector<Token> Token::parse(const uint8_t* buffer, const int BUFFER_SIZE) {
  int total_len = BUFFER_SIZE;
  int curr_len = 0;

  std::vector<Token> tokens;

  while (curr_len < total_len) {
    uint64_t curr;
    std::tie(curr, buffer) = unpack<uint16_t>(buffer);
    uint64_t type = curr & 15;
    int msg_len = 0;
    try {
      msg_len = token_len_dict[type];
    } catch (std::exception& e) {
      return tokens;
    }

    if (msg_len == 16) {
      tokens.push_back(Token(type, curr));
      curr_len += 2;
    } else if (msg_len == 32) {
      uint64_t high;
      std::tie(high, buffer) = unpack<uint16_t>(buffer);
      tokens.push_back(Token(type, (high << 16) + curr));
      curr_len += 4;
    } else if (msg_len == 48) {
      uint64_t high;
      std::tie(high, buffer) = unpack<uint32_t>(buffer);
      tokens.push_back(Token(type, (high << 16) + curr));
      curr_len += 6;
    } else if (msg_len == 64) {
      uint64_t mid;
      uint64_t high;
      std::tie(mid, buffer) = unpack<uint16_t>(buffer);
      std::tie(high, buffer) = unpack<uint32_t>(buffer);
      tokens.push_back(Token(type, (high << 32) + (mid << 16) + curr));
      curr_len += 8;
    }
  }

  return tokens;
}

/*std::unordered_map<int, std::string> misc_token_type_dict = {
    {0, "TIME"},      {1, "TIME_RESET"},         {2, "PACKET_LOST"},
    {3, "SURF_SYNC"}, {4, "TTRACE_STALL_BEGIN"}, {5, "TTRACE_STALL_END"}}; */

void Token::patch_time(std::vector<Token>& tokens) {
  uint64_t base_time = 0, rel_time = 0;
  int last_reset_time_idx = -1;

  for (uint64_t i = 0; i < tokens.size(); i++) {
    Token& token = tokens[i];

    if (token.type == 1) {
      if (last_reset_time_idx < 0 && base_time != 0) {
        /*std::cout << "[" << rel_time
                  << "] TIMESTAMP must be the 1st packet or preceded by a TIME_RESET, skip "
                     "TIMESTAMP Token"
                  << std::endl; */
        continue;
      }

      if (base_time == 0) base_time = token.time - rel_time;
      rel_time = ((token.time - base_time) / 4) * 4 - 4;  // Set or rewind timer

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
        /*std::cout << "[" << rel_time
                  << "] Cascading TIME_RESET tokens without any TIMESTAMP token in-between, skip "
                     "RESET token"
                  << std::endl; */
        continue;
      }

      rel_time += token.delta * 4;
      token.time = rel_time;
      last_reset_time_idx = i;
    } else if (token.type == 0 &&
               (token.misc_type == 2 || token.misc_type == 4 || token.misc_type == 5)) {
      rel_time += token.delta * 4;
      token.time = rel_time;
      // std::cout << misc_token_type_dict[token.misc_type] << " : " << rel_time << std::endl;
    } else if (last_reset_time_idx < 0) {
      rel_time += token.delta * 4;
      token.time = rel_time;
    }
  }
}
