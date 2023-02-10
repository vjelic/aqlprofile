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

#include "trie.h"

typedef struct {
  const char* line = 0;
  const char* loc = 0;
  int value = -1;
  int to_line = -1;
  int index = -1;
  int line_num = -1;
} code_wrapped_t;

typedef struct {
  code_wrapped_t* code;
  std::pair<int, int>* jumps;
  int code_len;
  int jumps_len;
} return_assembly_info_t;


Trie Trie::root_trie;
std::vector<code_wrapped_t> code_wrapped;
std::vector<std::pair<int, int>> jumps_wrapped;
AsParseRetype code_jumps;

std::string strip(const std::string& inpt) {
  auto start_it = inpt.begin();
  auto end_it = inpt.rbegin();
  while (std::isspace(*start_it)) ++start_it;
  while (std::isspace(*end_it)) ++end_it;
  return std::string(start_it, end_it.base());
}

struct clean_lines_t {
  int line_num;
  std::string line;
  std::string loc;
};

std::vector<clean_lines_t> clean_and_loc(std::vector<std::pair<int, std::string>> code) {
  bool first = true;
  std::vector<clean_lines_t> results;
  std::string loc = "";

  for (auto& line_pair : code) {
    int line_num = line_pair.first;
    std::string& line = line_pair.second;
    if (line.size() == 0) continue;  // Additional check
    if (';' == line[0]) continue;
    if (std::regex_match(line, std::regex("^\\s*$"))) continue;
    if ('.' == line[0]) {
      if (line.rfind(".loc", 0) == 0) {
        std::smatch m;
        std::regex regexp("\\.loc.+;\\s*(.+)$");

        auto iterator = std::sregex_iterator(line.begin(), line.end(), regexp);
        assert(iterator != std::sregex_iterator());

        std::smatch match = *iterator;
        assert(match.size() > 1);  // Not 100% sure if match==1 is possible
        loc = std::string(match[1]);

        if (first) {
          assert(results.size() > 0);  // Not checked in the python code.
          results[0].loc = loc;
          first = false;
          loc = "";
        }

        continue;
      } else if (line.rfind(".LBB", 0) != 0 && line.rfind("BB", 0) != 0) {
        continue;
      }
    }

    results.push_back({line_num, line, loc});
    loc = "";
  }

  return results;
}

std::vector<std::pair<int, std::string>> extract_kernel(
  const char* assembly_file,
  const char* kernel_string
) {
  std::regex beg("-- Begin function (\\w+)");
  std::string fin = ".end_amdhsa_kernel";

  std::ifstream file(assembly_file, std::ifstream::in);

  std::string line;
  std::string kernel_beg = "";
  bool kernel_started = false;
  std::vector<std::pair<int, std::string>> code;
  const size_t npos = std::string::npos;
  int line_num = 0;

  while (file.good()) {
    line_num += 1;
    getline(file, line);

    if (kernel_started) {
      // code += strip(std::string(line));
      code.push_back({line_num, strip(line)});
      if (line.find(fin) != npos) break;
    } else if (kernel_beg == "") {
      auto iterator = std::sregex_iterator(line.begin(), line.end(), beg);

      if (iterator != std::sregex_iterator()) {
        std::smatch match = *iterator;
        if (match.size() > 1 && std::string(match[1]).size() > 0) {
          std::string kname = std::string(match[1]);
          if (kernel_string == nullptr || kname.find(kernel_string) != npos)
            kernel_beg = "^(" + kname + "):";
        }
      }
    } else {
      std::regex rkernel(kernel_beg);
      auto iterator = std::sregex_iterator(line.begin(), line.end(), rkernel);

      if (iterator != std::sregex_iterator()) {
        std::smatch match = *iterator;
        if (match.size() > 1 && std::string(match[1]).size() > 0) {
          code.push_back({line_num, std::string(match[1])});
          kernel_started = true;
        }
      }
    }
  }
  if (code.size() == 0) {
    printf("Failed to extract kernel\n");
    exit(-1);
  }

  return code;
}

InstCategory inst_type(const std::string& line) {
  if (line.rfind(".LBB") == 0 || line.rfind("BB") == 0)
    return InstCategory::COMMENT;
  else if (line.find("branch") != std::string::npos)
    return InstCategory::BRANCH;
  else
    return Trie::root_trie.type_from_trie(line.substr(0, line.find(' ')));
}

AsParseRetype as_parse(const char* assembly_file, const char* kernel) {
  std::unordered_map<std::string, int> jump_table;

  std::vector<clean_lines_t> raw = clean_and_loc(extract_kernel(assembly_file, kernel));

  for (uint64_t i = 0; i < raw.size(); i++) {
    auto& line = raw[i].line;
    std::regex match_regex("^(\\.LBB\\w+)|^(BB\\w+):");
    auto it = std::sregex_iterator(line.begin(), line.end(), match_regex);
    if (it != std::sregex_iterator()) {
      std::smatch match_label = *it;
      assert(match_label.size() > 0);  // Not checked in python file
      jump_table[std::string(match_label[1])] = i + 1;
    }
  }

  std::unordered_map<int, int> reverse_jump;
  std::vector<processed_t> processed;

  for (uint32_t i = 0; i < raw.size(); i++) {
    auto& line = raw[i].line;
    std::regex match_regex("(\\.LBB\\w+)$|(BB\\w+)$");
    auto it = std::sregex_iterator(line.begin(), line.end(), match_regex);

    if (it != std::sregex_iterator()) {
      std::smatch match_label = *it;
      assert(match_label.size() > 0);  // Not checked in python file
      int to_line = jump_table[std::string(match_label[1])];

      processed_t proc({line, InstCategory::BRANCH, to_line, raw[i].loc, i, raw[i].line_num});
      processed.push_back(std::move(proc));
      reverse_jump[to_line] = i;
    } else {
      processed_t proc({line, inst_type(line), -1, raw[i].loc, i, raw[i].line_num});
      processed.push_back(std::move(proc));
    }
  }
  return std::make_pair(processed, reverse_jump);
}

extern "C" {
__attribute__((visibility("default")))
return_assembly_info_t wrapped_parse_binary(const char* p_filename, const char* kernel) {
  code_jumps = as_parse(p_filename, kernel);

  std::vector<processed_t>& processed = code_jumps.first;
  std::unordered_map<int, int>& reverse_jump = code_jumps.second;

  code_wrapped = std::vector<code_wrapped_t>();
  code_wrapped.reserve(processed.size());

  for (processed_t& s : processed) {
    code_wrapped_t wrapper;

    wrapper.line = s.line.data();
    wrapper.value = static_cast<int>(s.value);
    wrapper.to_line = s.to_line;
    wrapper.loc = s.loc.data();
    wrapper.index = s.index;
    wrapper.line_num = s.line_num;

    code_wrapped.push_back(wrapper);
  }

  jumps_wrapped = std::vector<std::pair<int, int>>();
  jumps_wrapped.reserve(reverse_jump.size());

  for (std::pair<const int, int>& pair : reverse_jump) jumps_wrapped.push_back(pair);

  return_assembly_info_t info;
  info.code_len = code_wrapped.size();
  info.code = code_wrapped.data();
  info.jumps_len = jumps_wrapped.size();
  info.jumps = jumps_wrapped.data();

  return info;
}
}
