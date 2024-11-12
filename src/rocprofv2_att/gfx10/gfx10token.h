/* Copyright (c) 2023 Advanced Micro Devices, Inc.

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

#pragma once
#include <vector>
#include <iostream>
#include <stdint.h>
#include <cstdint>

enum gfx10type {
    UNKNOWN = 0,
    VALU_INST,
    VMEM_EXEC,
    ALU_EXEC,
    IMM_ONE,
    IMMEDIATE,
    WAVE_READY,
    NEW_PC_GFX10,
    WAVE_END,
    WAVE_START,
    WAVE_START_EXT,
    WAVE_ALLOC,
    SHADER_DATA,
    SHADER_DATA_SHORT,
    UTIL_COUNTER,
    TIME,
    NOP,
    MISC_GFX10,
    EVENT,
    EVENT_SYNC,
    REG,
    REG_INIT,
    TIMESTAMP,
    HEADER,
    INST,
    PERFCTR,
    MISC_GFX11,
    UTIL_COUNTER_GFX11,
    EXEC_POPCOUNT1,
    EXEC_POPCOUNT3,
    NEW_PC_GFX12,
    GFX10_TYPE_LAST
};

static uint32_t frombits(const std::vector<uint8_t>& vec) {
    uint32_t res = 0;
    for (int i=0; i<vec.size(); i++)
        res |= vec[i] << i;
    return res;
}
static uint32_t frombitsRight(const std::vector<uint8_t>& vec) {
    uint32_t res = 0;
    for (int i=0; i<vec.size(); i++)
        res = (res << 1) | vec[i];
    return res;
}
static std::vector<uint8_t> tobits(uint8_t value) {
    std::vector<uint8_t> vec(8, 0);
    for (int i=0; i<8; i++)
        vec[i] = (value>>i) & 0x1;
    return vec;
}


struct wstart_type_common {
    uint64_t header : 5;
    uint64_t tm : 2;
    uint64_t sa : 1;
    uint64_t simd : 2;
    uint64_t wgp : 4;
    uint64_t wid : 5;
    uint64_t pipe : 2;
    uint64_t me : 1;

    void print() const {
        /* std::cout << std::dec << "WSTART - wgp:" << wgp << " simd:" << simd << " wid: " << wid << " sa:"
                                << sa << " me:" << me << " pipe:" << pipe << std::endl; */
    }
    uint64_t SACU() const { return sa*8ul + wgp; } // TODO: Move to 16 WGP per SA
    int CUSIMD() const { return 4*SACU() + simd; }
    uint64_t getGPULocation() const { return (sa<<11) | (CUSIMD()<<5) | wid; };
};


union wstart_type_gfx10 {
    struct {
        uint64_t header : 5;
        uint64_t tm : 2;
        uint64_t sa : 1;
        uint64_t simd : 2;
        uint64_t wgp : 3;
        uint64_t wid : 5;
        uint64_t queue : 3;
        uint64_t pipe : 2;
        uint64_t me : 1;
        uint64_t dispatcher : 1;
        uint64_t count : 7;
    };
    uint64_t raw;

    wstart_type_common get() const {
        return wstart_type_common{.header = header, .tm = tm, .sa = sa, .simd = simd,
                                  .wgp = wgp, .wid = wid, .pipe = pipe, .me = me};
    }
};

struct wend_type_common {
    uint64_t header : 5;
    uint64_t tm : 3;
    uint64_t sa : 1;
    uint64_t simd : 2;
    uint64_t wgp : 4;
    uint64_t wid : 5;

    void print() const {
        /*std::cout << "WEND - wgp:" << wgp << " simd:" << simd << " wid: " << wid << " sa:" << sa << std::endl;*/
    }
    uint64_t SACU() const { return sa*8ul + wgp; }
    uint64_t CUSIMD() const { return 4*SACU() + simd; }
    uint64_t getGPULocation() const { return (sa<<11) | (CUSIMD()<<5) | wid; };
};

union wend_type_gfx10 {
    struct {
        uint64_t header : 5;
        uint64_t tm : 3;
        uint64_t sa : 1;
        uint64_t simd : 2;
        uint64_t wgp : 3;
        uint64_t _unused : 1;
        uint64_t wid : 5;
    };
    uint64_t raw;

    wend_type_common get() const {
        return wend_type_common{.header = header, .tm = tm, .sa = sa, .simd = simd, .wgp = wgp, .wid = wid};
    }
};

union header_type {
    struct {
        uint64_t header : 7;
        uint64_t version : 6;
        uint64_t DSIMD : 2;
        uint64_t DWGP : 3;
        uint64_t _unused : 1;
        uint64_t DSA : 1;
        uint64_t NSA : 1;
        uint64_t NWGP : 3;
        uint64_t _unused2 : 1;
        uint64_t WSM : 2;
        uint64_t UCF : 1;
        uint64_t DPRate : 4;
        uint64_t wv20 : 1;
        uint64_t dp_derate : 3;
    };
    uint64_t raw;

    void print() const {
        /*std::cout << "TT Version:" << version << " NWGP:" << NWGP << std::endl;*/
        /*std::cout << "DWGP:" << DWGP << " DSIMD:" << DSIMD << std::endl;*/
        /*std::cout << "DSA:" << DSA << " NSA:" << NSA << " UCF:" << UCF << std::endl;*/
        /*std::cout << "DPRate:" << DPRate << " WSM:" << WSM << std::endl;*/
    }
};

struct inst_type_common {
    uint64_t header : 6;
    uint64_t tm : 6;
    uint64_t w64h : 1;
    uint64_t wid : 7;
    uint64_t inst : 10;
    uint64_t bGFX12 : 2;

    void print() const {
        /*std::cout << "INST - wid:" << wid << " inst:" << inst << " w64:" << (bool)w64h << std::endl;*/
    }
};

union inst_type_gfx10 {
    struct {
        uint64_t header : 3;
        uint64_t _unused : 1;
        uint64_t tm : 3;
        uint64_t w64h : 1;
        uint64_t wid : 5;
        uint64_t inst : 7;
    };
    uint64_t raw;

    inst_type_common get() const {
        return inst_type_common{.header = header, .tm = tm, .w64h = w64h, .wid = wid, .inst = inst, .bGFX12 = 0};
    }
};

union alu_exec_type {
    struct {
        uint64_t header : 4;
        uint64_t tm : 2;
        uint64_t SA : 1;
        uint64_t VA : 1;
    };
    uint64_t raw;

    void print() const {
        /*std::cout << "ALUX - SA:" << (bool)SA << " VA:" << (bool)VA << std::endl;*/
    }
};

union mem_exec_type {
    struct {
        uint64_t header : 4;
        uint64_t tm : 2;
        uint64_t SC : 1;
        uint64_t TEX : 1;
    };
    uint64_t raw;

    void print() const {
        /*std::cout << "MEMX - SC:" << (bool)SC << " TEX:" << (bool)TEX << std::endl;*/
    }
};

union valu_inst_type {
    struct {
        uint64_t header : 3;
        uint64_t tm : 3;
        uint64_t w64h : 1;
        uint64_t wid : 5;
    };
    uint64_t raw;

    void print() const {
        /*std::cout << "VALU - wid:" << wid << " w64:" << (bool)w64h << std::endl;*/
    }
};

union immed_one_type {
    struct {
        uint64_t header : 4;
        uint64_t tm : 3;
        uint64_t wid : 5;
    };
    uint64_t raw;

    void print() const {
        /*std::cout << "IMM1w - wid:" << wid << std::endl;*/
    }
};

union immediate_type {
    struct {
        uint64_t header : 5;
        uint64_t tm : 3;
        uint64_t waves : 16;
    };
    uint64_t raw;

    void print() const {
        /*std::cout << "IMMED - waves:" << std::hex << waves << std::endl;*/
    }
};

union wave_ready_type {
    struct {
        uint64_t header : 5;
        uint64_t tm : 3;
        uint64_t waves : 16;
    };
    uint64_t raw;

    void print() const {
        /*std::cout << "READY - waves:" << std::hex << waves << std::endl;*/
    }
};

union miscgfx10_type {
    struct {
        uint64_t header : 7;
        uint64_t tm : 9;
        uint64_t packetlost : 1;
        uint64_t _flags : 15;
    };
    uint64_t raw;

    void print() const {
        /*if (packetlost)
            std::cout << "MISC - PACKET LOST! - flags:" << std::hex << _flags << std::endl;
        else
            std::cout << "MISC - flags:" << std::hex << _flags << std::endl;*/
    }
};

union miscgfx11_type {
    struct {
        uint64_t header : 7;
        uint64_t tm : 9;
        uint64_t SPM : 1;
        uint64_t _flags : 15;
    };
    uint64_t raw;

    void print() const {
        /*std::cout << "MISC - flags:" << std::hex << _flags << std::endl;*/
    }
};

union timestamp_gfx10_type {
    struct {
        uint64_t header : 7;
        uint64_t _unused : 7;
        uint64_t type : 2;
        uint64_t time : 48;
    };
    uint64_t raw;
};

union util_ctr_gfx10_type {
    struct {
        uint64_t header : 7;
        uint64_t tm : 2;
        uint64_t spi_busy_or_lds1 : 8;
        uint64_t vdata0 : 8;
        uint64_t vdata1 : 8;
        uint64_t sdata0 : 8;
        uint64_t sdata1 : 8;
        uint64_t lds0 : 8;
        uint64_t cID : 6;
        uint64_t SA : 1;
    };
    uint64_t raw;

    static const int ctr_size = 8;
    void print() const {}
};

union new_pc_type_gfx10 {
    struct {
        uint64_t header : 8;
        uint64_t tm : 3;
        uint64_t wave : 5;
        uint64_t pc : 46;
        uint64_t err : 1;
    };
    uint64_t raw;

    void print() const { /*std::cout << "NEW PC: w" << wave << " 0x" << std::hex << pc << " 0x" << (pc<<2) << std::dec << std::endl;*/ }
};

union reg_write_type {
    struct {
        uint64_t header : 4;
        uint64_t tm : 3;
        uint64_t pipe : 2;
        uint64_t me : 2;
        uint64_t RDP : 1;
        uint64_t context : 3;
        uint64_t CS : 1;
        uint64_t regaddr : 16;
        uint64_t regdata : 32;
    };
    uint64_t raw;
    void print() const {
        /*
        std::cout << "reg_write : -pipe/addr/data " << pipe << std::hex << " " << addr << " " << data << std::dec << std::endl;
        //*/
    }
};

union reg_init_type {
    struct {
        uint64_t header : 7;
        uint64_t tm : 3;
        uint64_t vmid : 4;
        uint64_t pipe : 2;
        uint64_t me : 2;
        uint64_t type : 2;
        uint64_t data : 24;
        uint64_t context : 3;
        uint64_t data2 : 5;
        uint64_t sync_id : 10;
        uint64_t rsvd : 2;
    };
    uint64_t raw;
    void print() const {
        /*
        std::cout << "reg_init : -pipe " << pipe << " -type " << type << " -context " << context
                  << std::hex << " -data " << data << " -data2 " << data2 << std::dec << std::endl;
        //*/
    }
};

class gfx10Token {
public:
    gfx10Token() = default;
    gfx10Token(int64_t globaltime, uint64_t _contents, gfx10type _type):
        time(globaltime), contents(_contents), type(_type) {}
    int64_t time;
    uint64_t contents;
    gfx10type type;
    /* virtual void print() const { std::cout << "Undefined" << std::endl; }; */

    static std::vector<gfx10Token> parse(const uint8_t* buffer, const int BUFFER_SIZE);
    static std::array<uint8_t, 64> TOKEN_LEN;
};
