#include <vector>
#include <string>
#include <string_view>

#include "stitch.hpp"
#include "../trie.h"
#include "../trace_parser.hpp"

#define MAX_FAILED_STTICHES 10000

#define STITCH_ASSERT(x) if (!(x)) { std::cerr << __FILE__ << ':' << __LINE__ << " error!" << std::endl; return inst_index; }

/*
std::unordered_map<InstCategory, std::string> assemblyLine::categories =
{
  {InstCategory::SKIP, "SKIP"},
  {InstCategory::SMEM, "SMEM"},
  {InstCategory::SALU, "SALU"},
  {InstCategory::VMEM, "VMEM"},
  {InstCategory::FLAT, "FLAT"},
  {InstCategory::LDS, "LDS"},
  {InstCategory::VALU, "VALU"},
  {InstCategory::IMMED, "IMMED"},
  {InstCategory::BRANCH, "BRANCH"},
  {InstCategory::GETPC, "GETPC"},
  {InstCategory::SETPC, "SETPC"},
  {InstCategory::SWAPPC, "SWAPPC"},
  {InstCategory::LANE, "LANE"},
  {InstCategory::DONT_KNOW, "DONT_KNOW"},
  {InstCategory::NEGATIVE, "NEGATIVE"},
};
*/

size_t Stitcher::stitch(std::vector<InstructionExt>& insts)
{
    std::vector<int> pcskip;
    int num_failed_stitches = 0;
    int inst_index = 0;
    int skipped_immed = 0;

    STITCH_ASSERT(insts.size());

    assemblyLinePtr line;
    assemblyLinePtr next;

    if (bIsAuto)
    {
        const InstructionExt& firstinst = insts.at(0);
        STITCH_ASSERT(firstinst.category == WaveInstCategory::PCINFO);
        STITCH_ASSERT(firstinst.pc.addr || firstinst.pc.marker_id);

        try {
            next = watchlist->getcode(firstinst.pc);
        } catch (...) {
            return 0;
        }

        pcskip.push_back(0);
        inst_index ++;
    }
    else
        STITCH_ASSERT(false);

    while(inst_index < insts.size() && num_failed_stitches < MAX_FAILED_STTICHES)
    {
        InstructionExt& inst = insts.at(inst_index);

        if (inst.category == WaveInstCategory::PCINFO)
        {
            pcskip.push_back(inst_index);
            inst_index ++;
        }
        else if (inst.category == WaveInstCategory::WAVE_NOT_FINISHED)
        {
            break;
        }

        STITCH_ASSERT(next.get());
        line = std::move(next);
        if (!line) return 0;
        try {
            next = watchlist->getcode(line->next);
        }
        catch(...)
        {
            next = nullptr;
        }

        if (line->cat == InstCategory::DONT_KNOW || line->cat == InstCategory::SKIP)
            continue;

        bool bMatched = true;
        if (line->cat == InstCategory::GETPC)
        {
            if (next)
                watchlist->getpc(*line, *next);
            bMatched = inst.category == WaveInstCategory::SALU || inst.category == WaveInstCategory::JUMP;
        }
        else if (line->cat == InstCategory::SETPC || line->cat == InstCategory::SWAPPC)
        {
            if (line->cat == InstCategory::SETPC)
                next = watchlist->setpc(*line, insts.at(inst_index+1));
            else
                next = watchlist->swappc(*line, next?*next:assemblyLine{}, insts.at(inst_index+1));

            bMatched = inst.category == WaveInstCategory::SALU || inst.category == WaveInstCategory::JUMP;

            if (bIsAuto)
            {
                inst_index ++;
                pcskip.push_back(inst_index);

                while (!next.get() && inst_index+1 < insts.size())
                {
                    inst_index ++;
                    if (insts.at(inst_index).category == WaveInstCategory::PCINFO)
                    {
                        // Set and swap has the same effect on Auto
                        next = watchlist->setpc(*line, insts.at(inst_index));
                        pcskip.push_back(inst_index);
                    }
                    else
                        inst.latency += insts.at(inst_index).latency;
                }
            }
            STITCH_ASSERT(next.get());
        }
        else if (line->cat == InstCategory::LANE)
        {
            watchlist->updatelane(*line);
            bMatched = inst.category == WaveInstCategory::VALU;
        }
        else if (line->cat == inst.category)
        {
            //line->print();
        }
        else if (inst.category == WaveInstCategory::JUMP && line->cat == InstCategory::BRANCH)
        {
            next = watchlist->jump(*line);
        }
        else if (inst.category == WaveInstCategory::NEXT && line->cat == InstCategory::BRANCH)
        {
            //pass
        }
        else
        {
            // std::cout << "match? " << inst.category << ' '; line->print();
            bMatched = false;
            if (insts.size() > inst_index+1 && watchlist->try_match_swapped(inst, insts.at(inst_index+1), *line))
            {
                InstructionExt temp = insts.at(inst_index);
                insts.at(inst_index) = insts.at(inst_index+1);
                insts.at(inst_index+1) = temp;
                next = line;
            }
            else if (line->line.find("s_waitcnt") == 0 || line->line.find("_load_") != std::string::npos)
            {
                if (skipped_immed > 0 && line->line.find("s_waitcnt") == 0)
                {
                    bMatched = true;
                    skipped_immed -= 1;
                }
                else
                {
                    STITCH_ASSERT(line->line.find("scratch_") != std::string::npos);
                }
            }
        }

        if (bMatched || (!bGFX9 && inst.category == WaveInstCategory::IMMED))
        {
            inst.pc = line->addr;
            inst_index ++;
            num_failed_stitches = 0;
            if (!bMatched) skipped_immed ++;
        }
        else
        {
            num_failed_stitches ++;
        }
    }

    /*if (inst_index == insts.size())
    {
        while (line.get() && line->line.find("s_endpgm") != 0)
            line = watchlist->getcode(line->next);
    }*/
    return inst_index;
}

Stitcher::Stitcher(
    std::vector<assemblyLinePtr>& code,
    std::unordered_map<int, int>& _jumps,
    bool bGFX9
): codeobj_service({}), raw_code(code), jumps(_jumps), bGFX9(bGFX9), bIsAuto(false)
{

}

Stitcher::Stitcher(
    std::shared_ptr<ICodeServicer>& service,
    bool bGFX9
): codeobj_service(service), bGFX9(bGFX9), bIsAuto(true)
{
    raw_code.push_back(std::make_shared<assemblyLine>());
    raw_code.at(0)->line = "; Begin ASM";
    watchlist = std::make_unique<PCTranslator>(raw_code, service);
}

/*
    N = max(N, 1)
    if i != N:
        print('Warning - Stitching rate: '+str(i * 100 / N)+'% matched', i, ' of ', N)
        print('Leftovers:', [WaveInstCategory[insts[i+k].type] for k in range(20) if i+k < len(insts)])
        try:
            print(line, code[line])
        except:
            pass
    else:
        while line < len(code):
            if "s_endpgm" in code[line]:
                mem_unroll.append(
                    [reverse_map[line], SMEM_INST + VLMEM_INST + VSMEM_INST + FLAT_INST]
                )
                break
            line += 1
        print('Sucessfuly parsed', i, 'tokens')

    return result, loopCount, mem_unroll, flight_count, maxline, len(result), pcskip
*/
