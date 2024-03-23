#include <vector>
#include <string>
#include <string_view>

#include "stitch.hpp"
#include "../trie.h"
#include "../trace_parser.hpp"

PCTranslator::PCTranslator(
    std::vector<assemblyLinePtr>& _code,
    std::shared_ptr<ICodeServicer>& _service
): service(_service), code(_code)
{
    std::unique_lock<SharedMutex> lk(jump_mut);
    {
        std::unique_lock<SharedMutex> lk(code_mut);
        for (auto& c : code)
            addrmap[c->addr] = c;
    }
}

assemblyLinePtr PCTranslator::jump(const assemblyLine& source)
{
    {
        std::shared_lock<SharedMutex> lk(jump_mut);
        if (jump_map.find(source.addr) != jump_map.end())
            return jump_map.at(source.addr);
    }

    std::unique_lock<SharedMutex> lk(jump_mut);
    return jump_map.emplace(source.addr, getcode(getjump_loc(source))).first->second;
}

assemblyLinePtr PCTranslator::getcode(pcinfo_t addr)
{
    {
        std::shared_lock<SharedMutex> lk(code_mut);
        if (addrmap.find(addr) != addrmap.end())
            return addrmap.at(addr);
    }

    std::unique_lock<SharedMutex> lk(code_mut);

    assemblyLine newline = service->GetInstruction(addr);
    newline.index = code.size();
    newline.line_num = code.size();

    if (newline.cat == InstCategory::BRANCH)
        newline.to_line = getjump_loc(newline);

    auto line = std::make_shared<assemblyLine>(std::move(newline));
    code.push_back(line);
    addrmap[addr] = line;
    return line;
}

assemblyLinePtr PCTranslator::setpc(
    const assemblyLine& source,
    const InstructionExt& next_inst
) {
    return getcode(next_inst.pc);

    /*except:
        print('SETPC warning: Could not find addr', hex(self.insts[inst_index+1].cycles), 'for', inst_index, line)
        return -1 */
}
assemblyLinePtr PCTranslator::swappc(
    const assemblyLine& source,
    const assemblyLine& next_line,
    const InstructionExt& next_inst
) {
    return getcode(next_inst.pc);
    /*except:
        print('SWAPPC warning: Could not find addr', hex(self.insts[inst_index+1].cycles), 'for', inst_index, line)
        return -1 */
}

void PCTranslator::addsymbol(uint64_t addr)
{
    /*if addr in self.addrmap:
        return

    symbol = self.codeservice.getSymbolName(addr)
    if symbol is None:
        symbol = "Unkown symbol at 0x" + hex(addr)

    last_line = self.raw_code[-1]
    newline = ['; ' + symbol, 100, last_line[2], 0, last_line[4], last_line[5], 0, 0, 0]
    self.raw_code.append(newline) */
}

pcinfo_t PCTranslator::getjump_loc(const assemblyLine& line)
{
    int64_t delta = std::stoi(splitv(line.line, ' ').back().data());
    if (delta >= 32768) delta -= 65536;
    return {line.addr.addr + 4 + 4*delta, line.addr.marker_id};
}
