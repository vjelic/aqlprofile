#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <memory>
#include <unordered_map>
#include <shared_mutex>
#include "../trie.h"
#include "../trace_parser.hpp"

#define STITCH_ASSERT(x) if (!(x)) { std::cerr << __FILE__ << ':' << __LINE__ << " error!" << std::endl; exit(1); }

typedef std::string String;
typedef std::string_view StringView;
typedef std::shared_mutex SharedMutex;

struct assemblyLine
{
    String line;
    String loc;
    InstCategory cat;
    uint64_t addr;
    uint64_t next;
    size_t to_line;
    size_t index;
    size_t line_num;

    static std::unordered_map<InstCategory, std::string> categories;

    void print()
    {
        std::cout << int(cat) << " t " << categories.at(cat) << " addr: " << std::hex << addr
                  << " next " << next << std::dec << ' ' << line << " : " << loc << std::endl;
    }
};
typedef std::shared_ptr<assemblyLine> assemblyLinePtr;

class ICodeServicer
{
public:
    virtual assemblyLine GetInstruction(uint64_t addr) = 0;
    virtual void forget(uint32_t id) = 0;
    virtual ~ICodeServicer() {};
};

inline std::pair<StringView, StringView> split2(StringView view, StringView s)
{
    static std::string empty{""};

    size_t pos = view.find(s);
    if (pos == std::string::npos || pos+s.size() >= view.size())
        return {view, empty};
    return {view.substr(0, pos), view.substr(pos+s.size())};
}
inline std::vector<StringView> splitv(StringView view, char s)
{
    if (!view.size()) return {view};

    std::vector<StringView> ret;

    size_t first = 0;
    bool bIsQuotes = false;

    for (size_t idx = 0; idx < view.size(); idx++)
    {
        if (view[idx] == '\"')
            bIsQuotes = !bIsQuotes;
        else if (!bIsQuotes && view[idx] == s)
        {
            ret.push_back(StringView(view.data()+first, idx-first));
            first = idx+1;
        }
    }
    ret.push_back(StringView(view.data()+first, view.size()-first));

    for (size_t i=0; i<ret.size(); i++)
        ret.at(i) = strip(ret.at(i));

    return ret;
}

class IWatchlist
{
public:
    virtual ~IWatchlist(){};
    virtual assemblyLinePtr jump(const assemblyLine& source) = 0;
    virtual assemblyLinePtr getcode(uint64_t addr) = 0;
    virtual void getpc(const assemblyLine& source, const assemblyLine& next) = 0;
    virtual assemblyLinePtr setpc(const assemblyLine& source, const InstructionExt& next_inst) = 0;
    virtual assemblyLinePtr swappc(
        const assemblyLine& source,
        const assemblyLine& next_line,
        const InstructionExt& next_inst
    ) = 0;
    virtual void scratch(const assemblyLine& source) = 0;
    virtual void move(const assemblyLine& source) = 0;
    virtual void updatelane(const assemblyLine& source) = 0;
    virtual size_t reverse_map(uint64_t addr) = 0;

    bool try_match_swapped(
        const InstructionExt& first,
        const InstructionExt& second,
        const assemblyLine& line
    ) {
        return second.value == line.cat && first.value == getcode(line.next)->cat;
    }
};

class Register
{
public:
    char type = 0;
    bool bIsVector = false;
    int destination = 0;
    std::unique_ptr<std::unordered_map<int, int>> lanes{nullptr};
};

class RegisterWatchList : public IWatchlist
{
public:
    RegisterWatchList(std::vector<assemblyLine>& _code, std::vector<InstructionExt>& insts);
        //labels, code, jump_map, insts);
    virtual ~RegisterWatchList() {}

    virtual assemblyLinePtr jump(const assemblyLine& source) override;
    virtual assemblyLinePtr getcode(uint64_t addr) override;

    virtual void getpc(const assemblyLine& source, const assemblyLine& next) override;
    assemblyLinePtr setpc(const assemblyLine& source, const InstructionExt& next_inst) override;
    assemblyLinePtr swappc(
        const assemblyLine& source,
        const assemblyLine& next_line,
        const InstructionExt& next_inst
    ) override;

    virtual void scratch(const assemblyLine& source) override;
    virtual void move(const assemblyLine& source) override;
    virtual void updatelane(const assemblyLine& source) override;

    std::pair<StringView, StringView> range(StringView regs);
    std::vector<StringView> tokenize(StringView line);

protected:

    std::unordered_map<std::string, Register> registers;
    std::unordered_map<int, int> jumps;

    std::vector<assemblyLinePtr> code;
    std::vector<assemblyLinePtr>& raw_code;
    const std::vector<InstructionExt>& insts;

    std::unordered_map<int, int> reverse_map; //! Maps code index to raw_code index
    std::unordered_map<std::string, int> labels; // Maps label name to code index
};


// Translates PC values to instructions, for auto captured ISA
class PCTranslator: public IWatchlist
{
public:
    PCTranslator(
        std::vector<assemblyLinePtr>& _code,
        std::shared_ptr<ICodeServicer>& _service
    );
    virtual ~PCTranslator() {}
    //PCTranslator(insts, code, raw_code, reverse_map, codeservice);

    virtual assemblyLinePtr jump(const assemblyLine& source) override;
    virtual assemblyLinePtr getcode(uint64_t addr) override;

    assemblyLinePtr setpc(const assemblyLine& source, const InstructionExt& next_inst) override;
    assemblyLinePtr swappc(
        const assemblyLine& source,
        const assemblyLine& next_line,
        const InstructionExt& next_inst
    ) override;

    virtual void scratch(const assemblyLine& source) override {}
    virtual void move(const assemblyLine& source) override {}
    virtual void updatelane(const assemblyLine& source) override {}
    virtual void getpc(const assemblyLine& source, const assemblyLine& next) override {}
    virtual size_t reverse_map(uint64_t addr) { if (getcode(addr).get()) return getcode(addr)->index; return 0; };

    void addsymbol(uint64_t addr);
    uint64_t getjump_loc(const assemblyLine& line);

    std::vector<assemblyLinePtr>& code;
    std::shared_ptr<ICodeServicer> service;
    std::unordered_map<uint64_t, assemblyLinePtr> jump_map;
    std::unordered_map<uint64_t, assemblyLinePtr> addrmap;

    SharedMutex code_mut;
    SharedMutex jump_mut;
};

class Stitcher
{
public:
    Stitcher(std::shared_ptr<ICodeServicer>& service, bool bGFX9);
    Stitcher(std::vector<assemblyLinePtr>& code, std::unordered_map<int, int>& jumps, bool bGFX9);

    std::vector<uint64_t> stitch(std::vector<InstructionExt>& trace);
    std::vector<assemblyLinePtr> raw_code;
private:
    const bool bGFX9;
    const bool bIsAuto;
    std::optional<std::shared_ptr<ICodeServicer>> codeobj_service;
    std::unordered_map<int, int> jumps;
    std::unique_ptr<IWatchlist> watchlist;
};
