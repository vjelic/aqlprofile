
#include <unordered_map>
#include <vector>

#include "token.h"
#include "wave.h"
#include "trie.h"

int get_waitcnt_value(const std::string& s) {
    size_t pos1 = s.find('(');
    size_t pos2 = s.find(')');

    assert(pos1 != std::string::npos && pos2 != std::string::npos && pos1 < pos2);

    auto substr = s.substr(pos1, pos2);
    return std::atoi(substr.c_str());
}

bool contains(const std::string& str, const std::string& substr) {
    return str.find(substr) != std::string::npos;
}

typedef struct {
    int line_num;
    int num_mem;
    int wait;
} att_flightcount_t;


struct att_stitched_token_t : public instruction_t {
    att_stitched_token_t() = default;
    att_stitched_token_t(const instruction_t& t, int line) : instruction_t(t), line_num(line) {}
    int line_num;
};


void stitch(
    std::vector<instruction_t>& instructions, 
    std::vector<processed_t>& code, 
    std::unordered_map<int, int>& jumps
) {
    int line = 0;
    int NUM_SMEM = 0;
    int NUM_VMEM = 0;
    int NUM_FLAT = 0;

    std::vector<att_stitched_token_t> result;
    std::vector<std::pair<int, std::vector<int>>> mem_unroll;
    std::unordered_map<int, int> loopCount;
        
    std::vector<int> SMEM_INST;
    std::vector<int> VMEM_INST;
    std::vector<int> FLAT_INST;

    std::vector<att_flightcount_t> flight_count;

    int ordering = 0; //0 for in order/LDS, 1 for ongoing flats and 2 for SMEM

    for (int i=0; i<instructions.size(); i=i) {
        instruction_t& inst = instructions[i];
        if (line >= code.size())
            break;

        bool matched = true;
        int next = line+1;

        processed_t& as_line = code[line];
        if ((int)inst.value == (int)as_line.value) {
            if(jumps.find(line) != jumps.end()) {
                try {
                    loopCount[line-1] += 1;  // label is the previous line
                } catch (...) {
                     loopCount[line-1] = 1;
                }
            }

            matched = true;
            next = line+1;

            if (inst.value == WaveInstCategory::SMEM || inst.value == WaveInstCategory::LDS) { 
                if (inst.value == WaveInstCategory::SMEM) ordering = 2;
                NUM_SMEM += 1;
                SMEM_INST.push_back(line);
            }
            else if (inst.value == WaveInstCategory::VMEM) {
                NUM_VMEM += 1; // VMEM R/W
                VMEM_INST.push_back(line);
            }

            else if (inst.value == WaveInstCategory::FLAT) {
                NUM_FLAT += 1; // FLAT
                FLAT_INST.push_back(line);
                ordering = std::max(ordering, 1);
            }
            else if (inst.value == WaveInstCategory::IMMED && contains(as_line.line, "waitcnt")) {
                //print('WAIT:', SMEM_INST, VMEM_INST, as_line[-1], as_line[0])
                int wait_N = get_waitcnt_value(as_line.line);

                if (contains(as_line.line, "lgkmcnt")) {
                    flight_count.push_back({as_line.line_num, NUM_FLAT+NUM_SMEM, wait_N});
                    if (wait_N == 0) {
                        ordering = 0;
                        int offset = SMEM_INST.size()-wait_N;
                        FLAT_INST.insert(FLAT_INST.end(), SMEM_INST.begin(), SMEM_INST.begin()+offset);
                        mem_unroll.push_back( {line, std::move(FLAT_INST)} );

                        SMEM_INST.erase(SMEM_INST.begin(), SMEM_INST.begin()+offset);
                        FLAT_INST.clear();
                        NUM_FLAT = 0;
                        NUM_SMEM = 0;
                    } else {
                        NUM_SMEM = std::min(std::max(wait_N-NUM_FLAT, 0), NUM_SMEM);
                        NUM_FLAT = std::min(std::max(wait_N-NUM_SMEM, 0), NUM_FLAT);
                    }
                } else if (contains(as_line.line, "vmcnt")) {
                    flight_count.push_back({as_line.line_num, NUM_FLAT+NUM_VMEM, wait_N});
                    if (wait_N == 0) {
                        ordering = 0;
                        int offset = VMEM_INST.size()-wait_N;
                        FLAT_INST.insert(FLAT_INST.end(), VMEM_INST.begin(), VMEM_INST.begin()+offset);
                        mem_unroll.push_back({line, std::move(FLAT_INST)});

                        VMEM_INST.erase(VMEM_INST.begin(), VMEM_INST.begin()+offset);
                        FLAT_INST.clear();
                        NUM_FLAT = 0;
                        NUM_VMEM = 0;
                    } else {
                        NUM_VMEM = std::min(std::max(wait_N-NUM_FLAT, 0), NUM_VMEM);
                        NUM_FLAT = std::min(std::max(wait_N-NUM_VMEM, 0), NUM_FLAT);
                    }
                }
                else {
                    std::cout << "Error 130:" << std::endl; //<< inst << " " << as_line;
                    exit(-1);
                }
            }
        } else if( inst.value == WaveInstCategory::JUMP && as_line.value == InstCategory::BRANCH) {
            matched = true;
            next = as_line.to_line;
        } else if (inst.value == WaveInstCategory::NEXT && as_line.value == InstCategory::BRANCH) {
            matched = true;
            next = line + 1;
        } else {
            matched = false; // instructions with almost same timestamp swapped
            next = line + 1;
            if (
                i+1 < instructions.size() && 
                line+1 < code.size() && 
                (int)instructions[i+1].value == (int)code[line].value && 
                (int)instructions[i].value == (int)code[line+1].value
            ) {
                result.push_back({instructions[i+1], line});
                result.push_back({instructions[i], line+1});
                i += 2;
                next = line+2;
            }
        }
        
        if (matched) {
            result.push_back({inst, line});
            i += 1;
        }
        line = next;
    }

    std::cout << "Stitching " << result.size()*100.0f/std::max((int)instructions.size(), 1) << "% matched\n";

    std::cout << "R: " << result.size() << std::endl;
    std::cout << "L: " << loopCount.size() << std::endl;
    std::cout << "M: " << mem_unroll.size() << std::endl;
    std::cout << "F: " << flight_count.size() << std::endl;
    //return result, loopCount, mem_unroll, flight_count;
}

AsParseRetype as_parse(const char* assembly_file, const char* kernel);

extern "C" {
    void stitch_assembly(const char* token_filename, const char* asm_filename) {
        std::vector<Token> tokens = Token::parse(token_filename);
        Token::patch_time(tokens);

        auto result = wave_t::sqtt_simd_analysis(tokens, 1, false);
        auto code_jumps = as_parse(asm_filename, nullptr);

        std::vector<processed_t>& processed = code_jumps.first;
        std::unordered_map<int, int>& reverse_jump = code_jumps.second;
        
        for(auto& v : result.first) for(auto& u : v) for(auto& wave : u) if(wave.instructions.size() > 0)
            stitch(wave.instructions, processed, reverse_jump);
    }
}