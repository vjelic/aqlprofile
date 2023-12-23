#include <vector>
#include <string>
#include <string_view>

#include "stitch.hpp"
#include "../trie.h"
#include "../trace_parser.hpp"

RegisterWatchList::RegisterWatchList(labels, code, jump_map, insts)
{
    self.registers = {"v" + str(k): [[] for m in range(64)] for k in range(64)}
    for k in range(128):
        self.registers["s" + str(k)] = []
    self.labels = labels

    self.code = code
    self.jump_map = jump_map
    self.insts = insts
};

assemblyLine RegisterWatchList::jump(const assemblyLine& source)
{
    return self.jump_map[as_line[2]]
};
assemblyLine RegisterWatchList::getcode(size_t index)
{
    return self.code[line], 1
};

std::pair<StringView, StringView> RegisterWatchList::range(StringView regs)
{
    reg = r.split(":")
    if len(reg) == 1:
        return reg
    else:
        r0 = reg[0].split("[")
        return [r0[0] + str(k) for k in range(int(r0[1]), int(reg[1][:-1]) + 1)]
};

std::vector<StringView> RegisterWatchList::tokenize(StringView line)
{
    return [
        u for u in [t.split(",")[0].strip() for t in line.split(" ")] if len(u) > 0
    ];
}

void RegisterWatchList::getpc(const assemblyLine& source, const assemblyLine& next)
{
    try:
        dst = line.split(" ")[1].strip()
        label_dests = []
        try:
            label_dests = next_line[0].split(", ")
        except:
            pass
        try:
            label_dests.append(next_line[0].split(", ")[-1].split("@")[0])
        except:
            pass

        for label_dst in label_dests:
            try:
                cur_label = self.labels[label_dst]
                for reg in self.range(dst):
                    self.registers[reg] = deepcopy(cur_label)
            except:
                pass
    except:
        pass
}

pcinfo_t RegisterWatchList::setpc(const assemblyLine& source, const InstructionExt& next_inst)
{
    try:
        src = line.split(' ')[1].strip()
        return deepcopy(self.registers[self.range(src)[0]])
    except:
        return -1
}

pcinfo_t RegisterWatchList::swappc(
    const assemblyLine& source,
    const assemblyLine& next_line,
    const InstructionExt& next_inst
) {
    try:
        tokens = self.tokenize(line)
        dst = tokens[1]
        src = tokens[2]

        popped = deepcopy(self.registers[self.range(src)[0]])
        self.registers[self.range(dst)[0]] = line_num + 1
        return popped
    except:
        return -1
}

void RegisterWatchList::scratch(const assemblyLine& source)
{
    def scratch(self, line):
    try:
        tokens = self.tokenize(line)
        if "_load" in tokens[0]:
            dst = tokens[1]
            src = tokens[3] + tokens[4]
        else:
            src = tokens[2]
            dst = tokens[3] + tokens[4]
        self.registers[dst] = deepcopy(self.registers[src])
    except:
        pass
}
void RegisterWatchList::move(const assemblyLine& source)
{
    try:
        tokens = self.tokenize(line)
        if tokens[2][0] in ["s", "d"] and tokens[1][0] in ["s", "d"]:
            self.registers[self.range(tokens[1])[0]] = deepcopy(
                self.registers[self.range(tokens[2])[0]]
            )
    except:
        pass
}
void RegisterWatchList::updatelane(const assemblyLine& source)
{
    tokens = self.tokenize(line)
    try:
        if "v_readlane" in tokens[0]:
            self.registers[tokens[1]] = deepcopy(self.registers[tokens[2]][int(tokens[3])])
        elif "v_writelane" in tokens[0]:
            self.registers[tokens[1]][int(tokens[3])] = deepcopy(self.registers[tokens[2]])
    except:
        pass
}

bool RegisterWatchList::try_match_swapped(size_t inst, size_t line, size_t increment)
{
    return self.insts[i + 1].type == self.code[line][1] and self.insts[i].type == self.code[line + 1][1]
}
