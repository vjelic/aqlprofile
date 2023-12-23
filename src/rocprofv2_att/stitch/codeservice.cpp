#include <vector>
#include <string>
#include <string_view>

#include "stitch.hpp"
#include "../trie.h"
#include "../trace_parser.hpp"

class CSVContent
{
public:
    CSVContent() = default;
    CSVContent(const std::string& line)
    {
        auto tokens = splitv(line, ','); // wrong, need deal with quotes

        this->index = std::stoi(std::string(tokens.at(0)));
        this->line = std::string(tokens.at(1));
        this->hitcount = std::stoul(std::string(tokens.at(2)));
        this->cycles = std::stoul(std::string(tokens.at(3)));
        this->addr = std::stoul(std::string(tokens.at(4).substr(2)), 0, 16); // wrong, is hex

        if (tokens.size() > 5)
            this->cpp = std::string(tokens.at(5));
    }
    uint64_t index;
    std::string line;
    uint64_t hitcount;
    uint64_t cycles;
    uint64_t addr;
    std::string cpp;
    uint64_t next;
};

auto global_csv = std::unordered_map<uint64_t, CSVContent>();

/*
CodeService::CodeService()
{
    std::string PATH = "/home/giovanni/Desktop/HIP-Examples-master/vectorAdd/";
    std::ifstream csvfile(PATH+"att_output_ATT_Contiguous_v0.csv", std::ios::in);

    {
        std::string line;
        std::getline(csvfile, line);
    }

    size_t last_addr = 0;

    global_csv.clear();
    while (csvfile.good())
    {
        std::string line;
        std::getline(csvfile, line);
        if (line.size() < 2) continue;
        if (line.back() == '\n') line = line.substr(0, line.size()-1);
        line = strip(line);
        if (line.size() < 2) continue;

        line.resize(line.size()+1);

        CSVContent csv2(line);
        global_csv[csv2.addr] = csv2;
    }

    for (auto& [k, v] : global_csv)
    {
        for (size_t i = 4; i < 34; i += 4) if (global_csv.find(k+i) != global_csv.end())
        {
            v.next = k+i;
            break;
        }
    }
}

assemblyLine CodeService::GetInstruction(uint64_t addr)
{
    assemblyLine ret;
    const CSVContent& csv = global_csv.at(addr);

    ret.line = csv.line;
    ret.loc = csv.cpp;
    ret.cat = Trie::inst_type({csv.line.data(), csv.line.size()});
    ret.addr = csv.addr;
    ret.next = csv.next;
    ret.index = csv.index;
    ret.line_num = csv.index;

    return ret;
}
*/
