#ifndef _DEF_GFX9_DEF_H_
#define _DEF_GFX9_DEF_H_
#include "def/gpu_block_info.h"
// include gfxip/gfx9/gfx9_pm4_it_opcodes.h

enum IT_OpCodeType {
  IT_WAIT_REG_MEM = 0x3C,
  IT_INDIRECT_BUFFER = 0x3F,
  IT_COPY_DATA = 0x40,
  IT_EVENT_WRITE = 0x46,
  IT_ACQUIRE_MEM = 0x58,
  IT_SET_SH_REG = 0x76,
  IT_SET_UCONFIG_REG = 0x79,
};
// include gfxip/gfx9/gfx9_enum.h

enum SQ_THREAD_TRACE_MODE_SEL {
  SQ_THREAD_TRACE_MODE_OFF = 0x00000000,
  SQ_THREAD_TRACE_MODE_ON = 0x00000001,
};

enum VGT_EVENT_TYPE {
  CS_PARTIAL_FLUSH = 0x00000007,
};
#define UCONFIG_SPACE_START 0x0000c000
#define PERSISTENT_SPACE_START 0x00002c00
// include gfxip/gfx9/gfx9_utils.h
#define PM4_TYPE_SHIFT 30
#define PM4_COUNT_SHIFT 16
#define PM4_OPCODE_SHIFT 8
#define PM4_TYPE3_HDR(_opc_, _count_)                                                              \
  (uint32_t)((3) << PM4_TYPE_SHIFT | ((_count_)-2) << PM4_COUNT_SHIFT | (_opc_) << PM4_OPCODE_SHIFT)
// include gfxip/gfx9/gfx9_offset.h
#define mmIH_PERFMON_CNTL 0x1163
#define mmIH_PERFCOUNTER0_RESULT 0x1164
#define mmIH_PERFCOUNTER1_RESULT 0x1165
#define mmSDMA0_PERFMON_CNTL 0x12B7
#define mmSDMA0_PERFCOUNTER0_RESULT 0x12B8
#define mmSDMA0_PERFCOUNTER1_RESULT 0x12B9
#define mmSDMA1_PERFMON_CNTL 0x14B7
#define mmSDMA1_PERFCOUNTER0_RESULT 0x14B8
#define mmSDMA1_PERFCOUNTER1_RESULT 0x14B9
#define mmGDS_PERFCOUNTER0_LO 0xD280
#define mmGDS_PERFCOUNTER1_LO 0xD282
#define mmGDS_PERFCOUNTER2_LO 0xD284
#define mmGDS_PERFCOUNTER3_LO 0xD286
#define mmGDS_PERFCOUNTER0_HI 0xD281
#define mmGDS_PERFCOUNTER1_HI 0xD283
#define mmGDS_PERFCOUNTER2_HI 0xD285
#define mmGDS_PERFCOUNTER3_HI 0xD287
#define mmGDS_PERFCOUNTER0_SELECT 0xDA80
#define mmGDS_PERFCOUNTER1_SELECT 0xDA81
#define mmGDS_PERFCOUNTER2_SELECT 0xDA82
#define mmGDS_PERFCOUNTER3_SELECT 0xDA83
#define mmRLC_PERFCOUNTER0_LO 0xD480
#define mmRLC_PERFCOUNTER1_LO 0xD482
#define mmRLC_PERFCOUNTER0_HI 0xD481
#define mmRLC_PERFCOUNTER1_HI 0xD483
#define mmRLC_PERFMON_CLK_CNTL 0xDCBF
#define mmRLC_PERFCOUNTER0_SELECT 0xDCC1
#define mmRLC_PERFCOUNTER1_SELECT 0xDCC2
#define mmSPI_PERFCOUNTER0_HI 0xD180
#define mmSPI_PERFCOUNTER0_LO 0xD181
#define mmSPI_PERFCOUNTER1_HI 0xD182
#define mmSPI_PERFCOUNTER1_LO 0xD183
#define mmSPI_PERFCOUNTER2_HI 0xD184
#define mmSPI_PERFCOUNTER2_LO 0xD185
#define mmSPI_PERFCOUNTER3_HI 0xD186
#define mmSPI_PERFCOUNTER3_LO 0xD187
#define mmSPI_PERFCOUNTER4_HI 0xD188
#define mmSPI_PERFCOUNTER4_LO 0xD189
#define mmSPI_PERFCOUNTER5_HI 0xD18A
#define mmSPI_PERFCOUNTER5_LO 0xD18B
#define mmSPI_PERFCOUNTER0_SELECT 0xD980
#define mmSPI_PERFCOUNTER1_SELECT 0xD981
#define mmSPI_PERFCOUNTER2_SELECT 0xD982
#define mmSPI_PERFCOUNTER3_SELECT 0xD983
#define mmSPI_PERFCOUNTER4_SELECT 0xD988
#define mmSPI_PERFCOUNTER5_SELECT 0xD989
#define mmSQ_THREAD_TRACE_BASE 0xC330
#define mmSQ_THREAD_TRACE_SIZE 0xC331
#define mmSQ_THREAD_TRACE_MASK 0xC332
#define mmSQ_THREAD_TRACE_MODE 0xC336
#define mmSQ_THREAD_TRACE_CTRL 0xC335
#define mmSQ_THREAD_TRACE_TOKEN_MASK 0xC333
#define mmSQ_THREAD_TRACE_TOKEN_MASK2 0xC338
#define mmSQ_THREAD_TRACE_PERF_MASK 0xC334
#define mmSQ_THREAD_TRACE_WPTR 0xC339
#define mmSQ_THREAD_TRACE_STATUS 0xC33A
#define mmSQ_THREAD_TRACE_CNTR 0xC33C
#define mmSQ_THREAD_TRACE_HIWATER 0xC33B
#define mmSQ_PERFCOUNTER0_LO 0xD1C0
#define mmSQ_PERFCOUNTER1_LO 0xD1C2
#define mmSQ_PERFCOUNTER2_LO 0xD1C4
#define mmSQ_PERFCOUNTER3_LO 0xD1C6
#define mmSQ_PERFCOUNTER4_LO 0xD1C8
#define mmSQ_PERFCOUNTER5_LO 0xD1CA
#define mmSQ_PERFCOUNTER6_LO 0xD1CC
#define mmSQ_PERFCOUNTER7_LO 0xD1CE
#define mmSQ_PERFCOUNTER8_LO 0xD1D0
#define mmSQ_PERFCOUNTER9_LO 0xD1D2
#define mmSQ_PERFCOUNTER10_LO 0xD1D4
#define mmSQ_PERFCOUNTER11_LO 0xD1D6
#define mmSQ_PERFCOUNTER12_LO 0xD1D8
#define mmSQ_PERFCOUNTER13_LO 0xD1DA
#define mmSQ_PERFCOUNTER14_LO 0xD1DC
#define mmSQ_PERFCOUNTER15_LO 0xD1DE
#define mmSQ_PERFCOUNTER0_HI 0xD1C1
#define mmSQ_PERFCOUNTER1_HI 0xD1C3
#define mmSQ_PERFCOUNTER2_HI 0xD1C5
#define mmSQ_PERFCOUNTER3_HI 0xD1C7
#define mmSQ_PERFCOUNTER4_HI 0xD1C9
#define mmSQ_PERFCOUNTER5_HI 0xD1CB
#define mmSQ_PERFCOUNTER6_HI 0xD1CD
#define mmSQ_PERFCOUNTER7_HI 0xD1CF
#define mmSQ_PERFCOUNTER8_HI 0xD1D1
#define mmSQ_PERFCOUNTER9_HI 0xD1D3
#define mmSQ_PERFCOUNTER10_HI 0xD1D5
#define mmSQ_PERFCOUNTER11_HI 0xD1D7
#define mmSQ_PERFCOUNTER12_HI 0xD1D9
#define mmSQ_PERFCOUNTER13_HI 0xD1DB
#define mmSQ_PERFCOUNTER14_HI 0xD1DD
#define mmSQ_PERFCOUNTER15_HI 0xD1DF
#define mmSQ_PERFCOUNTER_CTRL 0xD9E0
#define mmSQ_PERFCOUNTER_MASK 0xD9E1
#define mmSQ_PERFCOUNTER0_SELECT 0xD9C0
#define mmSQ_PERFCOUNTER1_SELECT 0xD9C1
#define mmSQ_PERFCOUNTER2_SELECT 0xD9C2
#define mmSQ_PERFCOUNTER3_SELECT 0xD9C3
#define mmSQ_PERFCOUNTER4_SELECT 0xD9C4
#define mmSQ_PERFCOUNTER5_SELECT 0xD9C5
#define mmSQ_PERFCOUNTER6_SELECT 0xD9C6
#define mmSQ_PERFCOUNTER7_SELECT 0xD9C7
#define mmSQ_PERFCOUNTER8_SELECT 0xD9C8
#define mmSQ_PERFCOUNTER9_SELECT 0xD9C9
#define mmSQ_PERFCOUNTER10_SELECT 0xD9CA
#define mmSQ_PERFCOUNTER11_SELECT 0xD9CB
#define mmSQ_PERFCOUNTER12_SELECT 0xD9CC
#define mmSQ_PERFCOUNTER13_SELECT 0xD9CD
#define mmSQ_PERFCOUNTER14_SELECT 0xD9CE
#define mmSQ_PERFCOUNTER15_SELECT 0xD9CF
#define mmCOMPUTE_PERFCOUNT_ENABLE 0x2E0B
#define mmIA_PERFCOUNTER0_LO 0xD088
#define mmIA_PERFCOUNTER1_LO 0xD08A
#define mmIA_PERFCOUNTER2_LO 0xD08C
#define mmIA_PERFCOUNTER3_LO 0xD08E
#define mmIA_PERFCOUNTER0_HI 0xD089
#define mmIA_PERFCOUNTER1_HI 0xD08B
#define mmIA_PERFCOUNTER2_HI 0xD08D
#define mmIA_PERFCOUNTER3_HI 0xD08F
#define mmIA_PERFCOUNTER0_SELECT 0xD884
#define mmIA_PERFCOUNTER1_SELECT 0xD885
#define mmIA_PERFCOUNTER2_SELECT 0xD886
#define mmIA_PERFCOUNTER3_SELECT 0xD887
#define mmTD_PERFCOUNTER0_LO 0xD300
#define mmTD_PERFCOUNTER1_LO 0xD302
#define mmTD_PERFCOUNTER0_HI 0xD301
#define mmTD_PERFCOUNTER1_HI 0xD303
#define mmTA_PERFCOUNTER0_LO 0xD2C0
#define mmTA_PERFCOUNTER1_LO 0xD2C2
#define mmTA_PERFCOUNTER0_HI 0xD2C1
#define mmTA_PERFCOUNTER1_HI 0xD2C3
#define mmTCP_PERFCOUNTER0_LO 0xD340
#define mmTCP_PERFCOUNTER1_LO 0xD342
#define mmTCP_PERFCOUNTER2_LO 0xD344
#define mmTCP_PERFCOUNTER3_LO 0xD346
#define mmTCP_PERFCOUNTER0_HI 0xD341
#define mmTCP_PERFCOUNTER1_HI 0xD343
#define mmTCP_PERFCOUNTER2_HI 0xD345
#define mmTCP_PERFCOUNTER3_HI 0xD347
#define mmTD_PERFCOUNTER0_SELECT 0xDB00
#define mmTD_PERFCOUNTER1_SELECT 0xDB02
#define mmTA_PERFCOUNTER0_SELECT 0xDAC0
#define mmTA_PERFCOUNTER1_SELECT 0xDAC2
#define mmTCP_PERFCOUNTER0_SELECT 0xDB40
#define mmTCP_PERFCOUNTER1_SELECT 0xDB42
#define mmTCP_PERFCOUNTER2_SELECT 0xDB44
#define mmTCP_PERFCOUNTER3_SELECT 0xDB45
#define mmTCC_PERFCOUNTER0_LO 0xD380
#define mmTCC_PERFCOUNTER1_LO 0xD382
#define mmTCC_PERFCOUNTER2_LO 0xD384
#define mmTCC_PERFCOUNTER3_LO 0xD386
#define mmTCC_PERFCOUNTER0_HI 0xD381
#define mmTCC_PERFCOUNTER1_HI 0xD383
#define mmTCC_PERFCOUNTER2_HI 0xD385
#define mmTCC_PERFCOUNTER3_HI 0xD387
#define mmTCA_PERFCOUNTER0_LO 0xD390
#define mmTCA_PERFCOUNTER1_LO 0xD392
#define mmTCA_PERFCOUNTER2_LO 0xD394
#define mmTCA_PERFCOUNTER3_LO 0xD396
#define mmTCA_PERFCOUNTER0_HI 0xD391
#define mmTCA_PERFCOUNTER1_HI 0xD393
#define mmTCA_PERFCOUNTER2_HI 0xD395
#define mmTCA_PERFCOUNTER3_HI 0xD397
#define mmTCC_PERFCOUNTER0_SELECT 0xDB80
#define mmTCC_PERFCOUNTER1_SELECT 0xDB82
#define mmTCC_PERFCOUNTER2_SELECT 0xDB84
#define mmTCC_PERFCOUNTER3_SELECT 0xDB85
#define mmTCA_PERFCOUNTER0_SELECT 0xDB90
#define mmTCA_PERFCOUNTER1_SELECT 0xDB92
#define mmTCA_PERFCOUNTER2_SELECT 0xDB94
#define mmTCA_PERFCOUNTER3_SELECT 0xDB95
#define mmGRBM_GFX_INDEX 0xC200
#define mmGRBM_PERFCOUNTER0_LO 0xD040
#define mmGRBM_PERFCOUNTER0_HI 0xD041
#define mmGRBM_PERFCOUNTER1_LO 0xD043
#define mmGRBM_PERFCOUNTER1_HI 0xD044
#define mmGRBM_SE0_PERFCOUNTER_LO 0xD045
#define mmGRBM_SE0_PERFCOUNTER_HI 0xD046
#define mmGRBM_SE1_PERFCOUNTER_LO 0xD047
#define mmGRBM_SE1_PERFCOUNTER_HI 0xD048
#define mmGRBM_SE2_PERFCOUNTER_LO 0xD049
#define mmGRBM_SE2_PERFCOUNTER_HI 0xD04A
#define mmGRBM_SE3_PERFCOUNTER_LO 0xD04B
#define mmGRBM_SE3_PERFCOUNTER_HI 0xD04C
#define mmGRBM_PERFCOUNTER0_SELECT 0xD840
#define mmGRBM_PERFCOUNTER1_SELECT 0xD841
#define mmGRBM_SE0_PERFCOUNTER_SELECT 0xD842
#define mmGRBM_SE1_PERFCOUNTER_SELECT 0xD843
#define mmGRBM_SE2_PERFCOUNTER_SELECT 0xD844
#define mmGRBM_SE3_PERFCOUNTER_SELECT 0xD845
#define mmCPC_PERFCOUNTER1_LO 0xD004
#define mmCPC_PERFCOUNTER1_HI 0xD005
#define mmCPC_PERFCOUNTER0_LO 0xD006
#define mmCPC_PERFCOUNTER0_HI 0xD007
#define mmCPF_PERFCOUNTER1_LO 0xD008
#define mmCPF_PERFCOUNTER1_HI 0xD009
#define mmCPF_PERFCOUNTER0_LO 0xD00A
#define mmCPF_PERFCOUNTER0_HI 0xD00B
#define mmCPC_PERFCOUNTER1_SELECT 0xD803
#define mmCPC_PERFCOUNTER0_SELECT 0xD809
#define mmCPF_PERFCOUNTER1_SELECT 0xD805
#define mmCPF_PERFCOUNTER0_SELECT 0xD807
#define mmCP_PERFMON_CNTL 0xD808
#define mmSX_PERFCOUNTER0_LO 0xD240
#define mmSX_PERFCOUNTER0_HI 0xD241
#define mmSX_PERFCOUNTER1_LO 0xD242
#define mmSX_PERFCOUNTER1_HI 0xD243
#define mmSX_PERFCOUNTER2_LO 0xD244
#define mmSX_PERFCOUNTER2_HI 0xD245
#define mmSX_PERFCOUNTER3_LO 0xD246
#define mmSX_PERFCOUNTER3_HI 0xD247
#define mmSX_PERFCOUNTER0_SELECT 0xDA40
#define mmSX_PERFCOUNTER1_SELECT 0xDA41
#define mmSX_PERFCOUNTER2_SELECT 0xDA42
#define mmSX_PERFCOUNTER3_SELECT 0xDA43
#define mmPA_SC_PERFCOUNTER0_LO 0xD140
#define mmPA_SC_PERFCOUNTER0_HI 0xD141
#define mmPA_SC_PERFCOUNTER1_LO 0xD142
#define mmPA_SC_PERFCOUNTER1_HI 0xD143
#define mmPA_SC_PERFCOUNTER2_LO 0xD144
#define mmPA_SC_PERFCOUNTER2_HI 0xD145
#define mmPA_SC_PERFCOUNTER3_LO 0xD146
#define mmPA_SC_PERFCOUNTER3_HI 0xD147
#define mmPA_SC_PERFCOUNTER4_LO 0xD148
#define mmPA_SC_PERFCOUNTER4_HI 0xD149
#define mmPA_SC_PERFCOUNTER5_LO 0xD14A
#define mmPA_SC_PERFCOUNTER5_HI 0xD14B
#define mmPA_SC_PERFCOUNTER6_LO 0xD14C
#define mmPA_SC_PERFCOUNTER6_HI 0xD14D
#define mmPA_SC_PERFCOUNTER7_LO 0xD14E
#define mmPA_SC_PERFCOUNTER7_HI 0xD14F
#define mmPA_SC_PERFCOUNTER0_SELECT 0xD940
#define mmPA_SC_PERFCOUNTER1_SELECT 0xD942
#define mmPA_SC_PERFCOUNTER2_SELECT 0xD943
#define mmPA_SC_PERFCOUNTER3_SELECT 0xD944
#define mmPA_SC_PERFCOUNTER4_SELECT 0xD945
#define mmPA_SC_PERFCOUNTER5_SELECT 0xD946
#define mmPA_SC_PERFCOUNTER6_SELECT 0xD947
#define mmPA_SC_PERFCOUNTER7_SELECT 0xD948
// include gfxip/gfx9/gfx9_registers.h

union GDS_PERFCOUNTER0_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERFCOUNTER_SELECT : 10;
    unsigned int PERFCOUNTER_SELECT1 : 10;
    unsigned int CNTR_MODE : 4;
    unsigned int : 8;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 8;
    unsigned int CNTR_MODE : 4;
    unsigned int PERFCOUNTER_SELECT1 : 10;
    unsigned int PERFCOUNTER_SELECT : 10;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SPI_PERFCOUNTER0_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 10;
    unsigned int PERF_SEL1 : 10;
    unsigned int CNTR_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int PERF_MODE : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int PERF_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int CNTR_MODE : 4;
    unsigned int PERF_SEL1 : 10;
    unsigned int PERF_SEL : 10;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SQ_THREAD_TRACE_BASE {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int ADDR : 32;
#elif defined(BIGENDIAN_CPU)
    unsigned int ADDR : 32;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SQ_THREAD_TRACE_SIZE {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int SIZE : 22;
    unsigned int : 10;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 10;
    unsigned int SIZE : 22;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SQ_THREAD_TRACE_MASK {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int CU_SEL : 5;
    unsigned int SH_SEL : 1;
    unsigned int : 1;
    unsigned int REG_STALL_EN : 1;
    unsigned int SIMD_EN : 4;
    unsigned int VM_ID_MASK : 2;
    unsigned int SPI_STALL_EN : 1;
    unsigned int SQ_STALL_EN : 1;
    unsigned int : 16;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 16;
    unsigned int SQ_STALL_EN : 1;
    unsigned int SPI_STALL_EN : 1;
    unsigned int VM_ID_MASK : 2;
    unsigned int SIMD_EN : 4;
    unsigned int REG_STALL_EN : 1;
    unsigned int : 1;
    unsigned int SH_SEL : 1;
    unsigned int CU_SEL : 5;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SQ_THREAD_TRACE_MODE {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int MASK_PS : 3;
    unsigned int MASK_VS : 3;
    unsigned int MASK_GS : 3;
    unsigned int MASK_ES : 3;
    unsigned int MASK_HS : 3;
    unsigned int MASK_LS : 3;
    unsigned int MASK_CS : 3;
    unsigned int MODE : 2;
    unsigned int CAPTURE_MODE : 2;
    unsigned int AUTOFLUSH_EN : 1;
    unsigned int TC_PERF_EN : 1;
    unsigned int ISSUE_MASK : 2;
    unsigned int TEST_MODE : 1;
    unsigned int INTERRUPT_EN : 1;
    unsigned int WRAP : 1;
#elif defined(BIGENDIAN_CPU)
    unsigned int WRAP : 1;
    unsigned int INTERRUPT_EN : 1;
    unsigned int TEST_MODE : 1;
    unsigned int ISSUE_MASK : 2;
    unsigned int TC_PERF_EN : 1;
    unsigned int AUTOFLUSH_EN : 1;
    unsigned int CAPTURE_MODE : 2;
    unsigned int MODE : 2;
    unsigned int MASK_CS : 3;
    unsigned int MASK_LS : 3;
    unsigned int MASK_HS : 3;
    unsigned int MASK_ES : 3;
    unsigned int MASK_GS : 3;
    unsigned int MASK_VS : 3;
    unsigned int MASK_PS : 3;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SQ_THREAD_TRACE_CTRL {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int : 31;
    unsigned int RESET_BUFFER : 1;
#elif defined(BIGENDIAN_CPU)
    unsigned int RESET_BUFFER : 1;
    unsigned int : 31;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SQ_THREAD_TRACE_TOKEN_MASK {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int TOKEN_MASK : 16;
    unsigned int REG_MASK : 8;
    unsigned int REG_DROP_ON_STALL : 1;
    unsigned int : 7;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 7;
    unsigned int REG_DROP_ON_STALL : 1;
    unsigned int REG_MASK : 8;
    unsigned int TOKEN_MASK : 16;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SQ_THREAD_TRACE_TOKEN_MASK2 {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int INST_MASK : 32;
#elif defined(BIGENDIAN_CPU)
    unsigned int INST_MASK : 32;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SQ_THREAD_TRACE_PERF_MASK {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int SH0_MASK : 16;
    unsigned int SH1_MASK : 16;
#elif defined(BIGENDIAN_CPU)
    unsigned int SH1_MASK : 16;
    unsigned int SH0_MASK : 16;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SQ_PERFCOUNTER_CTRL {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PS_EN : 1;
    unsigned int VS_EN : 1;
    unsigned int GS_EN : 1;
    unsigned int ES_EN : 1;
    unsigned int HS_EN : 1;
    unsigned int LS_EN : 1;
    unsigned int CS_EN : 1;
    unsigned int : 1;
    unsigned int CNTR_RATE : 5;
    unsigned int DISABLE_FLUSH : 1;
    unsigned int : 18;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 18;
    unsigned int DISABLE_FLUSH : 1;
    unsigned int CNTR_RATE : 5;
    unsigned int : 1;
    unsigned int CS_EN : 1;
    unsigned int LS_EN : 1;
    unsigned int HS_EN : 1;
    unsigned int ES_EN : 1;
    unsigned int GS_EN : 1;
    unsigned int VS_EN : 1;
    unsigned int PS_EN : 1;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SQ_PERFCOUNTER_MASK {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int SH0_MASK : 16;
    unsigned int SH1_MASK : 16;
#elif defined(BIGENDIAN_CPU)
    unsigned int SH1_MASK : 16;
    unsigned int SH0_MASK : 16;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SQ_PERFCOUNTER0_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 9;
    unsigned int : 3;
    unsigned int SQC_BANK_MASK : 4;
    unsigned int SQC_CLIENT_MASK : 4;
    unsigned int SPM_MODE : 4;
    unsigned int SIMD_MASK : 4;
    unsigned int PERF_MODE : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int PERF_MODE : 4;
    unsigned int SIMD_MASK : 4;
    unsigned int SPM_MODE : 4;
    unsigned int SQC_CLIENT_MASK : 4;
    unsigned int SQC_BANK_MASK : 4;
    unsigned int : 3;
    unsigned int PERF_SEL : 9;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union COMPUTE_PERFCOUNT_ENABLE {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERFCOUNT_ENABLE : 1;
    unsigned int : 31;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 31;
    unsigned int PERFCOUNT_ENABLE : 1;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union IA_PERFCOUNTER0_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 10;
    unsigned int PERF_SEL1 : 10;
    unsigned int CNTR_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int PERF_MODE : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int PERF_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int CNTR_MODE : 4;
    unsigned int PERF_SEL1 : 10;
    unsigned int PERF_SEL : 10;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union TD_PERFCOUNTER0_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 8;
    unsigned int : 2;
    unsigned int PERF_SEL1 : 8;
    unsigned int : 2;
    unsigned int CNTR_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int PERF_MODE : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int PERF_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int CNTR_MODE : 4;
    unsigned int : 2;
    unsigned int PERF_SEL1 : 8;
    unsigned int : 2;
    unsigned int PERF_SEL : 8;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union TA_PERFCOUNTER0_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 8;
    unsigned int : 2;
    unsigned int PERF_SEL1 : 8;
    unsigned int : 2;
    unsigned int CNTR_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int PERF_MODE : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int PERF_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int CNTR_MODE : 4;
    unsigned int : 2;
    unsigned int PERF_SEL1 : 8;
    unsigned int : 2;
    unsigned int PERF_SEL : 8;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union TCP_PERFCOUNTER0_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 10;
    unsigned int PERF_SEL1 : 10;
    unsigned int CNTR_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int PERF_MODE : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int PERF_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int CNTR_MODE : 4;
    unsigned int PERF_SEL1 : 10;
    unsigned int PERF_SEL : 10;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union TCC_PERFCOUNTER0_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 10;
    unsigned int PERF_SEL1 : 10;
    unsigned int CNTR_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int PERF_MODE : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int PERF_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int CNTR_MODE : 4;
    unsigned int PERF_SEL1 : 10;
    unsigned int PERF_SEL : 10;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union TCA_PERFCOUNTER0_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 10;
    unsigned int PERF_SEL1 : 10;
    unsigned int CNTR_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int PERF_MODE : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int PERF_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int CNTR_MODE : 4;
    unsigned int PERF_SEL1 : 10;
    unsigned int PERF_SEL : 10;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union GRBM_GFX_INDEX {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int INSTANCE_INDEX : 8;
    unsigned int SH_INDEX : 8;
    unsigned int SE_INDEX : 8;
    unsigned int : 5;
    unsigned int SH_BROADCAST_WRITES : 1;
    unsigned int INSTANCE_BROADCAST_WRITES : 1;
    unsigned int SE_BROADCAST_WRITES : 1;
#elif defined(BIGENDIAN_CPU)
    unsigned int SE_BROADCAST_WRITES : 1;
    unsigned int INSTANCE_BROADCAST_WRITES : 1;
    unsigned int SH_BROADCAST_WRITES : 1;
    unsigned int : 5;
    unsigned int SE_INDEX : 8;
    unsigned int SH_INDEX : 8;
    unsigned int INSTANCE_INDEX : 8;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union GRBM_PERFCOUNTER0_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 6;
    unsigned int : 4;
    unsigned int DB_CLEAN_USER_DEFINED_MASK : 1;
    unsigned int CB_CLEAN_USER_DEFINED_MASK : 1;
    unsigned int VGT_BUSY_USER_DEFINED_MASK : 1;
    unsigned int TA_BUSY_USER_DEFINED_MASK : 1;
    unsigned int SX_BUSY_USER_DEFINED_MASK : 1;
    unsigned int : 1;
    unsigned int SPI_BUSY_USER_DEFINED_MASK : 1;
    unsigned int SC_BUSY_USER_DEFINED_MASK : 1;
    unsigned int PA_BUSY_USER_DEFINED_MASK : 1;
    unsigned int GRBM_BUSY_USER_DEFINED_MASK : 1;
    unsigned int DB_BUSY_USER_DEFINED_MASK : 1;
    unsigned int CB_BUSY_USER_DEFINED_MASK : 1;
    unsigned int CP_BUSY_USER_DEFINED_MASK : 1;
    unsigned int IA_BUSY_USER_DEFINED_MASK : 1;
    unsigned int GDS_BUSY_USER_DEFINED_MASK : 1;
    unsigned int BCI_BUSY_USER_DEFINED_MASK : 1;
    unsigned int RLC_BUSY_USER_DEFINED_MASK : 1;
    unsigned int TC_BUSY_USER_DEFINED_MASK : 1;
    unsigned int WD_BUSY_USER_DEFINED_MASK : 1;
    unsigned int UTCL2_BUSY_USER_DEFINED_MASK : 1;
    unsigned int EA_BUSY_USER_DEFINED_MASK : 1;
    unsigned int RMI_BUSY_USER_DEFINED_MASK : 1;
#elif defined(BIGENDIAN_CPU)
    unsigned int RMI_BUSY_USER_DEFINED_MASK : 1;
    unsigned int EA_BUSY_USER_DEFINED_MASK : 1;
    unsigned int UTCL2_BUSY_USER_DEFINED_MASK : 1;
    unsigned int WD_BUSY_USER_DEFINED_MASK : 1;
    unsigned int TC_BUSY_USER_DEFINED_MASK : 1;
    unsigned int RLC_BUSY_USER_DEFINED_MASK : 1;
    unsigned int BCI_BUSY_USER_DEFINED_MASK : 1;
    unsigned int GDS_BUSY_USER_DEFINED_MASK : 1;
    unsigned int IA_BUSY_USER_DEFINED_MASK : 1;
    unsigned int CP_BUSY_USER_DEFINED_MASK : 1;
    unsigned int CB_BUSY_USER_DEFINED_MASK : 1;
    unsigned int DB_BUSY_USER_DEFINED_MASK : 1;
    unsigned int GRBM_BUSY_USER_DEFINED_MASK : 1;
    unsigned int PA_BUSY_USER_DEFINED_MASK : 1;
    unsigned int SC_BUSY_USER_DEFINED_MASK : 1;
    unsigned int SPI_BUSY_USER_DEFINED_MASK : 1;
    unsigned int : 1;
    unsigned int SX_BUSY_USER_DEFINED_MASK : 1;
    unsigned int TA_BUSY_USER_DEFINED_MASK : 1;
    unsigned int VGT_BUSY_USER_DEFINED_MASK : 1;
    unsigned int CB_CLEAN_USER_DEFINED_MASK : 1;
    unsigned int DB_CLEAN_USER_DEFINED_MASK : 1;
    unsigned int : 4;
    unsigned int PERF_SEL : 6;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union GRBM_SE0_PERFCOUNTER_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 6;
    unsigned int : 4;
    unsigned int DB_CLEAN_USER_DEFINED_MASK : 1;
    unsigned int CB_CLEAN_USER_DEFINED_MASK : 1;
    unsigned int TA_BUSY_USER_DEFINED_MASK : 1;
    unsigned int SX_BUSY_USER_DEFINED_MASK : 1;
    unsigned int : 1;
    unsigned int SPI_BUSY_USER_DEFINED_MASK : 1;
    unsigned int SC_BUSY_USER_DEFINED_MASK : 1;
    unsigned int DB_BUSY_USER_DEFINED_MASK : 1;
    unsigned int CB_BUSY_USER_DEFINED_MASK : 1;
    unsigned int VGT_BUSY_USER_DEFINED_MASK : 1;
    unsigned int PA_BUSY_USER_DEFINED_MASK : 1;
    unsigned int BCI_BUSY_USER_DEFINED_MASK : 1;
    unsigned int RMI_BUSY_USER_DEFINED_MASK : 1;
    unsigned int : 9;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 9;
    unsigned int RMI_BUSY_USER_DEFINED_MASK : 1;
    unsigned int BCI_BUSY_USER_DEFINED_MASK : 1;
    unsigned int PA_BUSY_USER_DEFINED_MASK : 1;
    unsigned int VGT_BUSY_USER_DEFINED_MASK : 1;
    unsigned int CB_BUSY_USER_DEFINED_MASK : 1;
    unsigned int DB_BUSY_USER_DEFINED_MASK : 1;
    unsigned int SC_BUSY_USER_DEFINED_MASK : 1;
    unsigned int SPI_BUSY_USER_DEFINED_MASK : 1;
    unsigned int : 1;
    unsigned int SX_BUSY_USER_DEFINED_MASK : 1;
    unsigned int TA_BUSY_USER_DEFINED_MASK : 1;
    unsigned int CB_CLEAN_USER_DEFINED_MASK : 1;
    unsigned int DB_CLEAN_USER_DEFINED_MASK : 1;
    unsigned int : 4;
    unsigned int PERF_SEL : 6;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union CPC_PERFCOUNTER0_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int CNTR_SEL0 : 10;
    unsigned int CNTR_SEL1 : 10;
    unsigned int SPM_MODE : 4;
    unsigned int CNTR_MODE1 : 4;
    unsigned int CNTR_MODE0 : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int CNTR_MODE0 : 4;
    unsigned int CNTR_MODE1 : 4;
    unsigned int SPM_MODE : 4;
    unsigned int CNTR_SEL1 : 10;
    unsigned int CNTR_SEL0 : 10;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union CP_PERFMON_CNTL {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERFMON_STATE : 4;
    unsigned int SPM_PERFMON_STATE : 4;
    unsigned int PERFMON_ENABLE_MODE : 2;
    unsigned int PERFMON_SAMPLE_ENABLE : 1;
    unsigned int : 21;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 21;
    unsigned int PERFMON_SAMPLE_ENABLE : 1;
    unsigned int PERFMON_ENABLE_MODE : 2;
    unsigned int SPM_PERFMON_STATE : 4;
    unsigned int PERFMON_STATE : 4;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SX_PERFCOUNTER0_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERFCOUNTER_SELECT : 10;
    unsigned int PERFCOUNTER_SELECT1 : 10;
    unsigned int CNTR_MODE : 4;
    unsigned int : 8;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 8;
    unsigned int CNTR_MODE : 4;
    unsigned int PERFCOUNTER_SELECT1 : 10;
    unsigned int PERFCOUNTER_SELECT : 10;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};
// include gfxip/gfx9/f32_mec_pm4_packets_vg10.h

typedef union PM4_MEC_TYPE_3_HEADER {
  struct {
    uint32_t reserved1 : 8;  ///< reserved
    uint32_t opcode : 8;     ///< IT opcode
    uint32_t count : 14;     ///< number of DWORDs - 1 in the information body.
    uint32_t type : 2;       ///< packet identifier. It should be 3 for type 3 packets
  };
  uint32_t u32All;
} PM4_MEC_TYPE_3_HEADER;

typedef struct PM4_MEC_ACQUIRE_MEM {
  union {
    PM4_MEC_TYPE_3_HEADER header;  /// header
    uint32_t ordinal1;
  };

  union {
    struct {
      uint32_t coher_cntl : 31;
      uint32_t reserved1 : 1;
    } bitfields2;
    uint32_t ordinal2;
  };

  uint32_t coher_size;

  union {
    struct {
      uint32_t coher_size_hi : 24;
      uint32_t reserved2 : 8;
    } bitfields4;
    uint32_t ordinal4;
  };

  uint32_t coher_base_lo;

  union {
    struct {
      uint32_t coher_base_hi : 24;
      uint32_t reserved3 : 8;
    } bitfields6;
    uint32_t ordinal6;
  };

  union {
    struct {
      uint32_t poll_interval : 16;
      uint32_t reserved4 : 16;
    } bitfields7;
    uint32_t ordinal7;
  };

} PM4MEC_ACQUIRE_MEM, *PPM4MEC_ACQUIRE_MEM;

enum MEC_COPY_DATA_src_sel_enum {
  src_sel__mec_copy_data__mem_mapped_register = 0,
  src_sel__mec_copy_data__memory = 1,
  src_sel__mec_copy_data__perfcounters = 4,
};

enum MEC_COPY_DATA_dst_sel_enum {
  dst_sel__mec_copy_data__memory = 5,
};

enum MEC_COPY_DATA_src_cache_policy_enum {
  src_cache_policy__mec_copy_data__stream = 1,
};

enum MEC_COPY_DATA_count_sel_enum {
  count_sel__mec_copy_data__32_bits_of_data = 0,
  count_sel__mec_copy_data__64_bits_of_data = 1,
};
typedef uint32_t MEC_COPY_DATA_wr_confirm_enum;

enum MEC_COPY_DATA_dst_cache_policy_enum {
  dst_cache_policy__mec_copy_data__stream = 1,
};
typedef uint32_t MEC_COPY_DATA_pq_exe_status_enum;

typedef struct PM4_MEC_COPY_DATA {
  union {
    PM4_MEC_TYPE_3_HEADER header;  /// header
    uint32_t ordinal1;
  };

  union {
    struct {
      MEC_COPY_DATA_src_sel_enum src_sel : 4;
      uint32_t reserved1 : 4;
      MEC_COPY_DATA_dst_sel_enum dst_sel : 4;
      uint32_t reserved2 : 1;
      MEC_COPY_DATA_src_cache_policy_enum src_cache_policy : 2;
      uint32_t reserved3 : 1;
      MEC_COPY_DATA_count_sel_enum count_sel : 1;
      uint32_t reserved4 : 3;
      MEC_COPY_DATA_wr_confirm_enum wr_confirm : 1;
      uint32_t reserved5 : 4;
      MEC_COPY_DATA_dst_cache_policy_enum dst_cache_policy : 2;
      uint32_t reserved6 : 2;
      MEC_COPY_DATA_pq_exe_status_enum pq_exe_status : 1;
      uint32_t reserved7 : 2;
    } bitfields2;
    uint32_t ordinal2;
  };

  union {
    struct {
      uint32_t src_reg_offset : 18;
      uint32_t reserved8 : 14;
    } bitfields3a;
    struct {
      uint32_t reserved9 : 2;
      uint32_t src_32b_addr_lo : 30;
    } bitfields3b;
    struct {
      uint32_t reserved10 : 3;
      uint32_t src_64b_addr_lo : 29;
    } bitfields3c;
    struct {
      uint32_t src_gds_addr_lo : 16;
      uint32_t reserved11 : 16;
    } bitfields3d;
    uint32_t imm_data;

    uint32_t ordinal3;
  };

  union {
    uint32_t src_memtc_addr_hi;

    uint32_t src_imm_data;

    uint32_t ordinal4;
  };

  union {
    struct {
      uint32_t dst_reg_offset : 18;
      uint32_t reserved12 : 14;
    } bitfields5a;
    struct {
      uint32_t reserved13 : 2;
      uint32_t dst_32b_addr_lo : 30;
    } bitfields5b;
    struct {
      uint32_t reserved14 : 3;
      uint32_t dst_64b_addr_lo : 29;
    } bitfields5c;
    struct {
      uint32_t dst_gds_addr_lo : 16;
      uint32_t reserved15 : 16;
    } bitfields5d;
    uint32_t ordinal5;
  };

  uint32_t dst_addr_hi;

} PM4MEC_COPY_DATA, *PPM4MEC_COPY_DATA;

enum MEC_EVENT_WRITE_event_index_enum {
  event_index__mec_event_write__cs_partial_flush = 4,
};

typedef struct PM4_MEC_EVENT_WRITE {
  union {
    PM4_MEC_TYPE_3_HEADER header;  /// header
    uint32_t ordinal1;
  };

  union {
    struct {
      uint32_t event_type : 6;
      uint32_t reserved1 : 2;
      MEC_EVENT_WRITE_event_index_enum event_index : 4;
      uint32_t reserved2 : 19;
      uint32_t offload_enable : 1;
    } bitfields2;
    uint32_t ordinal2;
  };

} PM4MEC_EVENT_WRITE, *PPM4MEC_EVENT_WRITE;

enum MEC_INDIRECT_BUFFER_cache_policy_enum {
  cache_policy__mec_indirect_buffer__stream = 1,
};

typedef struct PM4_MEC_INDIRECT_BUFFER {
  union {
    PM4_MEC_TYPE_3_HEADER header;  /// header
    uint32_t ordinal1;
  };

  union {
    struct {
      uint32_t reserved1 : 2;
      uint32_t ib_base_lo : 30;
    } bitfields2;
    uint32_t ordinal2;
  };

  uint32_t ib_base_hi;

  union {
    struct {
      uint32_t ib_size : 20;
      uint32_t chain : 1;
      uint32_t offload_polling : 1;
      uint32_t reserved2 : 1;
      uint32_t valid : 1;
      uint32_t vmid : 4;
      MEC_INDIRECT_BUFFER_cache_policy_enum cache_policy : 2;
      uint32_t reserved3 : 1;
      uint32_t priv : 1;
    } bitfields4;
    uint32_t ordinal4;
  };

} PM4MEC_INDIRECT_BUFFER, *PPM4MEC_INDIRECT_BUFFER;
typedef uint32_t MEC_SET_CONFIG_REG_index_enum;

typedef struct PM4_MEC_SET_CONFIG_REG {
  union {
    PM4_MEC_TYPE_3_HEADER header;  /// header
    uint32_t ordinal1;
  };

  union {
    struct {
      uint32_t reg_offset : 16;
      uint32_t reserved1 : 7;
      uint32_t vmid_shift : 5;
      MEC_SET_CONFIG_REG_index_enum index : 4;
    } bitfields2;
    uint32_t ordinal2;
  };

  //  uint32_t reg_data[];  // N-DWords

} PM4MEC_SET_CONFIG_REG, *PPM4MEC_SET_CONFIG_REG;

enum MEC_WAIT_REG_MEM_function_enum {
  function__mec_wait_reg_mem__equal_to_the_reference_value = 3,
  function__mec_wait_reg_mem__not_equal_reference_value = 4,
};

enum MEC_WAIT_REG_MEM_mem_space_enum {
  mem_space__mec_wait_reg_mem__register_space = 0,
  mem_space__mec_wait_reg_mem__memory_space = 1,
};

enum MEC_WAIT_REG_MEM_operation_enum {
  operation__mec_wait_reg_mem__wait_reg_mem = 0,
};

typedef struct PM4_MEC_WAIT_REG_MEM {
  union {
    PM4_MEC_TYPE_3_HEADER header;  /// header
    uint32_t ordinal1;
  };

  union {
    struct {
      MEC_WAIT_REG_MEM_function_enum function : 3;
      uint32_t reserved1 : 1;
      MEC_WAIT_REG_MEM_mem_space_enum mem_space : 2;
      MEC_WAIT_REG_MEM_operation_enum operation : 2;
      uint32_t reserved2 : 24;
    } bitfields2;
    uint32_t ordinal2;
  };

  union {
    struct {
      uint32_t reserved3 : 2;
      uint32_t mem_poll_addr_lo : 30;
    } bitfields3a;
    struct {
      uint32_t reg_poll_addr : 18;
      uint32_t reserved4 : 14;
    } bitfields3b;
    struct {
      uint32_t reg_write_addr1 : 18;
      uint32_t reserved5 : 14;
    } bitfields3c;
    uint32_t ordinal3;
  };

  union {
    uint32_t mem_poll_addr_hi;

    struct {
      uint32_t reg_write_addr2 : 18;
      uint32_t reserved6 : 14;
    } bitfields4b;
    uint32_t ordinal4;
  };

  uint32_t reference;

  uint32_t mask;

  union {
    struct {
      uint32_t poll_interval : 16;
      uint32_t reserved7 : 16;
    } bitfields7;
    uint32_t ordinal7;
  };

} PM4MEC_WAIT_REG_MEM, *PPM4MEC_WAIT_REG_MEM;
// include gfxip/gfx9/gfx9_block_info.h
#define AI_NUM_TA 16
#define AI_COUNTER_NUM_PER_TA 2
#define AI_NUM_TD 16
#define AI_COUNTER_NUM_PER_TD 2
#define AI_NUM_TCP 16
#define AI_COUNTER_NUM_PER_TCP 4
#define AI_NUM_TCA 2
#define AI_COUNTER_NUM_PER_TCA 4
#define AI_NUM_TCC 16
#define AI_COUNTER_NUM_PER_TCC 4
#define AI_COUNTER_NUM_PER_GRBM 2
#define AI_COUNTER_NUM_PER_GRBMSE 4
#define AI_COUNTER_NUM_PER_SPI 6  // [Shucai: To do: double check the value]
#define AI_COUNTER_NUM_PER_SQ 16
#define AI_COUNTER_NUM_PER_SX 4
#define AI_COUNTER_NUM_PER_GDS 4
#define AI_COUNTER_NUM_PER_IA 4
#define AI_COUNTER_NUM_PER_MC 4
#define AI_COUNTER_NUM_PER_CPC 2

enum HsaAiCounterBlockId {
  kHsaAiCounterBlockIdGrbm,
  kHsaAiCounterBlockIdGrbmSe,
  kHsaAiCounterBlockIdSpi,
  kHsaAiCounterBlockIdSq,
  kHsaAiCounterBlockIdSqGs,
  kHsaAiCounterBlockIdSqVs,
  kHsaAiCounterBlockIdSqPs,
  kHsaAiCounterBlockIdSqHs,
  kHsaAiCounterBlockIdSqCs,
  kHsaAiCounterBlockIdSx,
  kHsaAiCounterBlockIdTa,
  kHsaAiCounterBlockIdTca,
  kHsaAiCounterBlockIdTcc,
  kHsaAiCounterBlockIdTd,
  kHsaAiCounterBlockIdTcp,
  kHsaAiCounterBlockIdGds,
  kHsaAiCounterBlockIdIa,
  kHsaAiCounterBlockIdMc,
  kHsaAiCounterBlockIdCpc,
  kHsaAiCounterBlockIdIommuV2,
  kHsaAiCounterBlockIdKernelDriver,
};
// include gfxip/gfx9/gfx9_pm4defs.h
#define COPY_DATA_SEL_REG 0                   ///< Mem-mapped register
#define COPY_DATA_SEL_SRC_SYS_PERF_COUNTER 4  ///< Privileged memory performance counter
#define COPY_DATA_SEL_COUNT_1DW 0             ///< Copy 1 word (32 bits)
// include gfxip/gfx9/gfx9_typedef.h
typedef union GDS_PERFCOUNTER0_SELECT regGDS_PERFCOUNTER0_SELECT;
typedef union SPI_PERFCOUNTER0_SELECT regSPI_PERFCOUNTER0_SELECT;
typedef union SQ_THREAD_TRACE_BASE regSQ_THREAD_TRACE_BASE;
typedef union SQ_THREAD_TRACE_SIZE regSQ_THREAD_TRACE_SIZE;
typedef union SQ_THREAD_TRACE_MASK regSQ_THREAD_TRACE_MASK;
typedef union SQ_THREAD_TRACE_MODE regSQ_THREAD_TRACE_MODE;
typedef union SQ_THREAD_TRACE_CTRL regSQ_THREAD_TRACE_CTRL;
typedef union SQ_THREAD_TRACE_TOKEN_MASK regSQ_THREAD_TRACE_TOKEN_MASK;
typedef union SQ_THREAD_TRACE_TOKEN_MASK2 regSQ_THREAD_TRACE_TOKEN_MASK2;
typedef union SQ_THREAD_TRACE_PERF_MASK regSQ_THREAD_TRACE_PERF_MASK;
typedef union SQ_PERFCOUNTER_CTRL regSQ_PERFCOUNTER_CTRL;
typedef union SQ_PERFCOUNTER_MASK regSQ_PERFCOUNTER_MASK;
typedef union SQ_PERFCOUNTER0_SELECT regSQ_PERFCOUNTER0_SELECT;
typedef union COMPUTE_PERFCOUNT_ENABLE regCOMPUTE_PERFCOUNT_ENABLE;
typedef union IA_PERFCOUNTER0_SELECT regIA_PERFCOUNTER0_SELECT;
typedef union TD_PERFCOUNTER0_SELECT regTD_PERFCOUNTER0_SELECT;
typedef union TA_PERFCOUNTER0_SELECT regTA_PERFCOUNTER0_SELECT;
typedef union TCP_PERFCOUNTER0_SELECT regTCP_PERFCOUNTER0_SELECT;
typedef union TCC_PERFCOUNTER0_SELECT regTCC_PERFCOUNTER0_SELECT;
typedef union TCA_PERFCOUNTER0_SELECT regTCA_PERFCOUNTER0_SELECT;
typedef union GRBM_GFX_INDEX regGRBM_GFX_INDEX;
typedef union GRBM_PERFCOUNTER0_SELECT regGRBM_PERFCOUNTER0_SELECT;
typedef union GRBM_SE0_PERFCOUNTER_SELECT regGRBM_SE0_PERFCOUNTER_SELECT;
typedef union CPC_PERFCOUNTER0_SELECT regCPC_PERFCOUNTER0_SELECT;
typedef union CP_PERFMON_CNTL regCP_PERFMON_CNTL;
typedef union SX_PERFCOUNTER0_SELECT regSX_PERFCOUNTER0_SELECT;
// include gfxip/gfx9/gfx9_mask.h
#define CP_COHER_CNTL__TC_WB_ACTION_ENA_MASK 0x00040000L
#define CP_COHER_CNTL__TCL1_ACTION_ENA_MASK 0x00400000L
#define CP_COHER_CNTL__TC_ACTION_ENA_MASK 0x00800000L
#define CP_COHER_CNTL__SH_KCACHE_ACTION_ENA_MASK 0x08000000L
#define CP_COHER_CNTL__SH_ICACHE_ACTION_ENA_MASK 0x20000000L
#include "def/gfx9_primitives.h"
#include "def/gfx9_block_table.h"
#endif  // _DEF_GFX9_DEF_H_
