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

#define MACRO_MAX_DEPTH 20

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
    while (start_it != inpt.end() && std::isspace(*start_it)) ++start_it;
    if (start_it == inpt.end()) return "";

    while (end_it != inpt.rend() && std::isspace(*end_it)) ++end_it;
    return std::string(start_it, end_it.base());
}

struct clean_lines_t {
    int line_num;
    std::string line;
    std::string loc;
    std::string comment;
};

size_t get_comment_pos(const std::string& line) {
    size_t comment_pos = line.find("//");
    if (comment_pos != std::string::npos)
        return comment_pos;
    comment_pos = line.find("/*");
    if (comment_pos != std::string::npos)
        return comment_pos;
    return line.find(";");
}

// Returns label name as (pos, size) of substr of line
std::pair<size_t, size_t> LabelName(const std::string& line) {
    if (line.size() <= 2 || line[0] == ' ')
        return {0,0};

    size_t label_marker = line.find(':');
    if (!label_marker || label_marker == std::string::npos)
        return {0,0};

    size_t space = line.find(' ');
    if (space == std::string::npos || space+3 >= label_marker)
        return {0, label_marker};

    if (line[label_marker-1] != '>' || line[space+1] != '<')
        return {0,0};

    return {space+2, label_marker-space-3};
}

bool IsKernelStart(const std::string& line, const std::string& kernelname, size_t searchend_pos) {
    if (kernelname.size() >= line.size() || kernelname.size() > searchend_pos) // Insuficient chars
        return false;

    auto substr = LabelName(line);
    if (substr.second == 0 || substr.first+substr.second > searchend_pos)
        return false;

    return line.substr(substr.first, substr.second) == kernelname;
}

std::string getMacroName(const std::string& line) {
    size_t pos1 = line.find(".macro ");
    if (pos1 == std::string::npos || pos1 + 8 >= line.size())
        return "";
    pos1 += 7;
    while (pos1 < line.size() && line[pos1] == ' ') pos1++;
    size_t pos2 = line.find(' ', pos1);

    if (pos2 == std::string::npos)
        return line.substr(pos1);
    else
        return line.substr(pos1, pos2-pos1);
}

bool IsMacro(const std::string& line) {
    size_t mac = line.find(".macro ");
    return mac != std::string::npos && mac < line.size()+8;
}

std::vector<clean_lines_t> clean_and_loc(std::vector<std::pair<int, std::string>> code) {
    bool first = true;
    std::vector<clean_lines_t> results;
    std::string loc = "";

    for (auto& line_pair : code) {
        int line_num = line_pair.first;
        std::string& line = line_pair.second;

        size_t comment_pos = get_comment_pos(line); //.find(";");
        std::string comment = "";
        if (comment_pos != std::string::npos) {
            comment = line.substr(comment_pos);
            line = line.substr(0, comment_pos);
        }

        if (line.size() == 0 || ';' == line[0]) continue;
        if (std::regex_match(line, std::regex("^\\s*$"))) continue;
        if ('.' == line[0] && line.rfind(".loc", 0) == 0) {
            loc = strip(comment.substr(1));
            if (first) {
                assert(results.size() > 0);  // Not checked in the python code.
                results[0].loc = loc;
                first = false;
                loc = "";
            }
            continue;
        } else if ('.' == line[0] && LabelName(line).second == 0) {
            continue;
        }

        results.push_back({line_num, std::move(line), std::move(loc), std::move(comment)});
        loc = "";
    }
    return results;
}

bool MacroFill(
    std::vector<std::vector<std::string>>& defined_macros,
    std::unordered_map<std::string, int>& macro_map,
    std::vector<std::pair<int, std::string>>& code,
    const std::string& line,
    int line_num,
    int depth
) {
    if (depth >= MACRO_MAX_DEPTH)
        return false;
    size_t first_space = line.find(' ');
    int macro_id = macro_map[line.substr(0, first_space)];
    if(macro_id ==0 || macro_id > defined_macros.size() || defined_macros[macro_id-1].size() == 0) {
        printf("Invalid macro %s", line.c_str());
        return false;
    }
    auto& macro_vector = defined_macros[macro_id-1];

    code.push_back({line_num, ".macro " + macro_vector[0]});
    for (auto& v : macro_vector)
    for (size_t i=1; i<macro_vector.size(); i++) {
        if (macro_map.find(macro_vector[i]) != macro_map.end())
            MacroFill(defined_macros, macro_map, code, macro_vector[i], line_num, depth+1);
        else
            code.push_back({line_num, macro_vector[i]});
    }
    return true;
}

std::vector<std::pair<int, std::string>> extract_kernel(
    const char* assembly_file,
    const char* kernel_string_ptr
) {
    std::ifstream file(assembly_file, std::ifstream::in);

    std::string kernel_string_ss = kernel_string_ptr ? std::string(kernel_string_ptr) : "";
    std::string line;
    std::string kernel_beg = "";
    bool kernel_started = false;
    std::vector<std::pair<int, std::string>> code;
    int line_num = 0;
    bool bIsBlockCommented = false;
    bool bIsMacro = false;

    std::unordered_map<std::string, int> macro_map;
    std::vector<std::vector<std::string>> defined_macros;

    if (kernel_string_ptr == nullptr)
        kernel_started = true;

    while (file.good()) {
        line_num += 1;
        getline(file, line);

        if (line.size() <= 1) continue;

        size_t comment_pos = get_comment_pos(line);
        if (comment_pos < line.size()-1 && line[comment_pos+1] == '*') /*-style-*/
            bIsBlockCommented = true;

        if (bIsBlockCommented) {
            size_t uncomment_pos = line.find("*/");
            if (uncomment_pos != std::string::npos)
                bIsBlockCommented = false;
            continue;
        }

        if (!kernel_started && IsKernelStart(line, kernel_string_ss, comment_pos))
            kernel_started = true;

        line = strip(line);
        if (!line.size() || line.substr(0,4) == ".set")
            continue;

        size_t first_space = line.find(' ');

        if (bIsMacro) {
            defined_macros.back().push_back(line);
            if (line.find(".endm") != std::string::npos)
                bIsMacro = false;
        } else if (IsMacro(line)) {
            bIsMacro = true;
            std::string macname = getMacroName(line);
            defined_macros.push_back({(first_space < line.size()-1) ? line.substr(first_space+1) : line});
            macro_map[macname] = defined_macros.size();
        } else if (kernel_started) {
            if (first_space != std::string::npos && defined_macros.size() &&
                macro_map.find(line.substr(0, first_space)) != macro_map.end()
            )
                MacroFill(defined_macros, macro_map, code, line, line_num, 0);
            else
                code.push_back({line_num, line});
        }
    }
    if (code.size() == 0) {
        printf("Failed to extract kernel\n");
        exit(-1);
    }

    return code;
}

InstCategory inst_type(const std::string& line) {
    if (line.find("branch") != std::string::npos)
        return InstCategory::BRANCH;
    else
        return Trie::root_trie.type_from_trie(line.substr(0, line.find(' ')));
}

AsParseRetype as_parse(const char* assembly_file, const char* kernel) {
    std::unordered_map<std::string, int> jump_table;

    std::vector<clean_lines_t> raw = clean_and_loc(extract_kernel(assembly_file, kernel));

    for (uint64_t i = 0; i < raw.size(); i++) {
        auto pos = LabelName(raw[i].line);
        if (pos.second != 0)
            jump_table[raw[i].line.substr(pos.first, pos.second)] = i + 1;
    }

    std::unordered_map<int, int> reverse_jump;
    std::vector<processed_t> processed;

    for (uint32_t i = 0; i < raw.size(); i++) {
        auto& line = raw[i].line;
        auto instruction_type = inst_type(line);

        if (instruction_type == InstCategory::BRANCH) {
            size_t bpos = line.find("branch"); // Todo: What happens with label named "branch"?
            size_t label_begin_pos = line.find(" ", bpos);

            if (label_begin_pos == std::string::npos)
                continue;

            size_t label_end_pos = line.find(" ", label_begin_pos+1);

            if (label_end_pos == std::string::npos)
                label_end_pos = line.size();

            int to_line = jump_table[line.substr(label_begin_pos+1, label_end_pos-label_begin_pos-1)];

            processed_t proc({line+raw[i].comment, InstCategory::BRANCH, to_line, raw[i].loc, i, raw[i].line_num});
            processed.push_back(std::move(proc));
            reverse_jump[to_line] = i;
        } else {
            processed_t proc({line+raw[i].comment, instruction_type, -1, raw[i].loc, i, raw[i].line_num});
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
