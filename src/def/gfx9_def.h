// Austomatically generated, do not edit
#ifndef SRC_DEF_GFX9_DEF_H_
#define SRC_DEF_GFX9_DEF_H_
#include "def/gpu_block_info.h"
// include gfxip/gfx9/gfx9_enum.h

enum GDS_PERFCOUNT_SELECT {
  GDS_PERF_SEL_GWS_BYPASS = 120,
};

enum PERFMON_COUNTER_MODE {
  PERFMON_COUNTER_MODE_ACCUM = 0x00000000,
};

enum SDMA_PERF_SEL {
  SDMA_PERF_SEL_MMHUB_TAG_DELAY_COUNTER = 0x000000ff,
};

enum SPI_PERFCNT_SEL {
  SPI_PERF_VWC_CSC_WR = 0x000000c3,
};

enum SQ_THREAD_TRACE_MODE_SEL {
  SQ_THREAD_TRACE_MODE_OFF = 0x00000000,
  SQ_THREAD_TRACE_MODE_ON = 0x00000001,
};

enum SQ_PERF_SEL {
  SQC_PERF_SEL_DUMMY_LAST = 0x00000175,
};

enum VGT_EVENT_TYPE {
  CS_PARTIAL_FLUSH = 0x00000007,
};

enum TA_PERFCOUNT_SEL {
  TA_PERF_SEL_first_xnack_on_phase3 = 0x00000076,
};

enum TD_PERFCOUNT_SEL {
  TD_PERF_SEL_texels_zeroed_out_by_blend_zero_prt = 0x00000038,
};

enum TCP_PERFCOUNT_SELECT {
  TCP_PERF_SEL_TCC_DCC_REQ = 0x00000054,
};

enum TCC_PERF_SEL {
  TCC_PERF_SEL_CLIENT127_REQ = 0x000000ff,
};

enum TCA_PERF_SEL {
  TCA_PERF_SEL_CROSSBAR_STALL_TCC7 = 0x00000022,
};

enum GRBM_PERF_SEL {
  GRBM_PERF_SEL_CPAXI_BUSY = 0x00000025,
};

enum CPF_PERFCOUNT_SEL {
  CPF_PERF_SEL_CPF_UTCL2IU_STALL = 0x0000001f,
};

enum CPC_PERFCOUNT_SEL {
  CPC_PERF_SEL_ME2_DC1_SPI_BUSY = 0x00000022,
};
#define CONFIG_SPACE_START 0x00002000
#define CONFIG_SPACE_END 0x00009fff
#define UCONFIG_SPACE_START 0x0000c000
#define PERSISTENT_SPACE_START 0x00002c00

enum SX_PERFCOUNTER_VALS {
  SX_PERF_SEL_DB3_SIZE = 0x000000cf,
};
// include gfxip/gfx9/gfx9_mask.h
#define CP_COHER_CNTL__TC_WB_ACTION_ENA_MASK 0x00040000L
#define CP_COHER_CNTL__TCL1_ACTION_ENA_MASK 0x00400000L
#define CP_COHER_CNTL__TC_ACTION_ENA_MASK 0x00800000L
#define CP_COHER_CNTL__SH_KCACHE_ACTION_ENA_MASK 0x08000000L
#define CP_COHER_CNTL__SH_ICACHE_ACTION_ENA_MASK 0x20000000L
// include gfxip/gfx9/gfx9_offset.h
#define mmATC_PERFCOUNTER0_CFG 0x0C3E
#define mmATC_PERFCOUNTER1_CFG 0x0C3F
#define mmATC_PERFCOUNTER2_CFG 0x0C40
#define mmATC_PERFCOUNTER3_CFG 0x0C41
#define mmATC_PERFCOUNTER_RSLT_CNTL 0x0C42
#define mmATC_PERFCOUNTER_LO 0x0C43
#define mmATC_PERFCOUNTER_HI 0x0C44
#define mmRPB_PERFCOUNTER_LO 0x0D01
#define mmRPB_PERFCOUNTER_HI 0x0D02
#define mmRPB_PERFCOUNTER0_CFG 0x0D03
#define mmRPB_PERFCOUNTER1_CFG 0x0D04
#define mmRPB_PERFCOUNTER2_CFG 0x0D05
#define mmRPB_PERFCOUNTER3_CFG 0x0D06
#define mmRPB_PERFCOUNTER_RSLT_CNTL 0x0D07
#define mmSDMA0_PERFMON_CNTL 0x12B7
#define mmSDMA0_PERFCOUNTER0_RESULT 0x12B8
#define mmSDMA0_PERFCOUNTER1_RESULT 0x12B9
#define mmSDMA1_PERFMON_CNTL 0x14B7
#define mmSDMA1_PERFCOUNTER0_RESULT 0x14B8
#define mmSDMA1_PERFCOUNTER1_RESULT 0x14B9
#define mmSDMA2_PERFMON_CNTL 0x1E057
#define mmSDMA2_PERFCOUNTER0_RESULT 0x1E058
#define mmSDMA2_PERFCOUNTER1_RESULT 0x1E059
#define mmSDMA3_PERFMON_CNTL 0x1E457
#define mmSDMA3_PERFCOUNTER0_RESULT 0x1E458
#define mmSDMA3_PERFCOUNTER1_RESULT 0x1E459
#define mmSDMA4_PERFMON_CNTL 0x1E857
#define mmSDMA4_PERFCOUNTER0_RESULT 0x1E858
#define mmSDMA4_PERFCOUNTER1_RESULT 0x1E859
#define mmSDMA5_PERFMON_CNTL 0x1EC57
#define mmSDMA5_PERFCOUNTER0_RESULT 0x1EC58
#define mmSDMA5_PERFCOUNTER1_RESULT 0x1EC59
#define mmSDMA6_PERFMON_CNTL 0x1F057
#define mmSDMA6_PERFCOUNTER0_RESULT 0x1F058
#define mmSDMA6_PERFCOUNTER1_RESULT 0x1F059
#define mmSDMA7_PERFMON_CNTL 0x1F457
#define mmSDMA7_PERFCOUNTER0_RESULT 0x1F458
#define mmSDMA7_PERFCOUNTER1_RESULT 0x1F459
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
#define mmRLC_PERFMON_CLK_CNTL 0xDCBF
#define mmRLC_SPM_PERFMON_CNTL 0xDC80
#define mmRLC_SPM_PERFMON_RING_BASE_LO 0xDC81
#define mmRLC_SPM_PERFMON_RING_BASE_HI 0xDC82
#define mmRLC_SPM_PERFMON_RING_SIZE 0xDC83
#define mmRLC_SPM_PERFMON_SEGMENT_SIZE 0xDC84
#define mmRLC_SPM_PERFMON_SEGMENT_SIZE_CORE1 0xDCAF
#define mmRLC_SPM_SE_MUXSEL_ADDR 0xDC85
#define mmRLC_SPM_SE_MUXSEL_DATA 0xDC86
#define mmRLC_SPM_CPC_PERFMON_SAMPLE_DELAY 0xDC88
#define mmRLC_SPM_CPF_PERFMON_SAMPLE_DELAY 0xDC89
#define mmRLC_SPM_GDS_PERFMON_SAMPLE_DELAY 0xDC8D
#define mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY 0xDC91
#define mmRLC_SPM_TCA_PERFMON_SAMPLE_DELAY 0xDC92
#define mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY 0xDC93
#define mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY 0xDC94
#define mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY 0xDC95
#define mmRLC_SPM_SPI_PERFMON_SAMPLE_DELAY 0xDC97
#define mmRLC_SPM_SQG_PERFMON_SAMPLE_DELAY 0xDC98
#define mmRLC_SPM_SX_PERFMON_SAMPLE_DELAY 0xDC9A
#define mmRLC_SPM_GLOBAL_MUXSEL_ADDR 0xDC9B
#define mmRLC_SPM_GLOBAL_MUXSEL_DATA 0xDC9C
#define mmRLC_SPM_MC_CNTL 0xEC71
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
#define mmSQ_THREAD_TRACE_BASE2 0xC337
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
#define mmATC_L2_PERFCOUNTER_LO 0xD500
#define mmATC_L2_PERFCOUNTER_HI 0xD501
#define mmATC_L2_PERFCOUNTER0_CFG 0xDD40
#define mmATC_L2_PERFCOUNTER1_CFG 0xDD41
#define mmATC_L2_PERFCOUNTER_RSLT_CNTL 0xDD42
#define mmMC_VM_L2_PERFCOUNTER0_CFG 0xDD4C
#define mmMC_VM_L2_PERFCOUNTER1_CFG 0xDD4D
#define mmMC_VM_L2_PERFCOUNTER2_CFG 0xDD4E
#define mmMC_VM_L2_PERFCOUNTER3_CFG 0xDD4F
#define mmMC_VM_L2_PERFCOUNTER4_CFG 0xDD50
#define mmMC_VM_L2_PERFCOUNTER5_CFG 0xDD51
#define mmMC_VM_L2_PERFCOUNTER6_CFG 0xDD52
#define mmMC_VM_L2_PERFCOUNTER7_CFG 0xDD53
#define mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL 0xDD54
#define mmMC_VM_L2_PERFCOUNTER_LO 0xD508
#define mmMC_VM_L2_PERFCOUNTER_HI 0xD509
// include gfxip/gfx9/gfx9_typedef.h
typedef union ATC_PERFCOUNTER0_CFG regATC_PERFCOUNTER0_CFG;
typedef union RPB_PERFCOUNTER0_CFG regRPB_PERFCOUNTER0_CFG;
typedef union SDMA0_PERFMON_CNTL regSDMA0_PERFMON_CNTL;
typedef union GDS_PERFCOUNTER0_SELECT regGDS_PERFCOUNTER0_SELECT;
typedef union RLC_SPM_PERFMON_CNTL regRLC_SPM_PERFMON_CNTL;
typedef union RLC_SPM_PERFMON_SEGMENT_SIZE regRLC_SPM_PERFMON_SEGMENT_SIZE;
typedef union RLC_SPM_PERFMON_SEGMENT_SIZE_CORE1 regRLC_SPM_PERFMON_SEGMENT_SIZE_CORE1;
typedef union RLC_SPM_MC_CNTL regRLC_SPM_MC_CNTL;
typedef union SPI_PERFCOUNTER0_SELECT regSPI_PERFCOUNTER0_SELECT;
typedef union SQ_THREAD_TRACE_BASE regSQ_THREAD_TRACE_BASE;
typedef union SQ_THREAD_TRACE_BASE2 regSQ_THREAD_TRACE_BASE2;
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
typedef union TD_PERFCOUNTER0_SELECT regTD_PERFCOUNTER0_SELECT;
typedef union TA_PERFCOUNTER0_SELECT regTA_PERFCOUNTER0_SELECT;
typedef union TCP_PERFCOUNTER0_SELECT regTCP_PERFCOUNTER0_SELECT;
typedef union TCC_PERFCOUNTER0_SELECT regTCC_PERFCOUNTER0_SELECT;
typedef union TCA_PERFCOUNTER0_SELECT regTCA_PERFCOUNTER0_SELECT;
typedef union GRBM_GFX_INDEX regGRBM_GFX_INDEX;
typedef union GRBM_PERFCOUNTER0_SELECT regGRBM_PERFCOUNTER0_SELECT;
typedef union GRBM_SE0_PERFCOUNTER_SELECT regGRBM_SE0_PERFCOUNTER_SELECT;
typedef union CPC_PERFCOUNTER0_SELECT regCPC_PERFCOUNTER0_SELECT;
typedef union CPF_PERFCOUNTER0_SELECT regCPF_PERFCOUNTER0_SELECT;
typedef union CP_PERFMON_CNTL regCP_PERFMON_CNTL;
typedef union SX_PERFCOUNTER0_SELECT regSX_PERFCOUNTER0_SELECT;
typedef union ATC_L2_PERFCOUNTER0_CFG regATC_L2_PERFCOUNTER0_CFG;
typedef union MC_VM_L2_PERFCOUNTER0_CFG regMC_VM_L2_PERFCOUNTER0_CFG;
// include gfxip/gfx9/gfx9_registers.h

union ATC_PERFCOUNTER0_CFG {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 8;
    unsigned int PERF_SEL_END : 8;
    unsigned int : 8;
    unsigned int PERF_MODE : 4;
    unsigned int ENABLE : 1;
    unsigned int CLEAR : 1;
    unsigned int : 2;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 2;
    unsigned int CLEAR : 1;
    unsigned int ENABLE : 1;
    unsigned int PERF_MODE : 4;
    unsigned int : 8;
    unsigned int PERF_SEL_END : 8;
    unsigned int PERF_SEL : 8;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union RPB_PERFCOUNTER0_CFG {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 8;
    unsigned int PERF_SEL_END : 8;
    unsigned int : 8;
    unsigned int PERF_MODE : 4;
    unsigned int ENABLE : 1;
    unsigned int CLEAR : 1;
    unsigned int : 2;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 2;
    unsigned int CLEAR : 1;
    unsigned int ENABLE : 1;
    unsigned int PERF_MODE : 4;
    unsigned int : 8;
    unsigned int PERF_SEL_END : 8;
    unsigned int PERF_SEL : 8;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SDMA0_PERFMON_CNTL {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_ENABLE0 : 1;
    unsigned int PERF_CLEAR0 : 1;
    unsigned int PERF_SEL0 : 8;
    unsigned int PERF_ENABLE1 : 1;
    unsigned int PERF_CLEAR1 : 1;
    unsigned int PERF_SEL1 : 8;
    unsigned int : 12;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 12;
    unsigned int PERF_SEL1 : 8;
    unsigned int PERF_CLEAR1 : 1;
    unsigned int PERF_ENABLE1 : 1;
    unsigned int PERF_SEL0 : 8;
    unsigned int PERF_CLEAR0 : 1;
    unsigned int PERF_ENABLE0 : 1;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

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

union RLC_SPM_PERFMON_CNTL {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int RESERVED1 : 12;
    unsigned int PERFMON_RING_MODE : 2;
    unsigned int RESERVED : 2;
    unsigned int PERFMON_SAMPLE_INTERVAL : 16;
#elif defined(BIGENDIAN_CPU)
    unsigned int PERFMON_SAMPLE_INTERVAL : 16;
    unsigned int RESERVED : 2;
    unsigned int PERFMON_RING_MODE : 2;
    unsigned int RESERVED1 : 12;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union RLC_SPM_PERFMON_SEGMENT_SIZE {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERFMON_SEGMENT_SIZE : 8;
    unsigned int RESERVED1 : 3;
    unsigned int GLOBAL_NUM_LINE : 5;
    unsigned int SE0_NUM_LINE : 5;
    unsigned int SE1_NUM_LINE : 5;
    unsigned int SE2_NUM_LINE : 5;
    unsigned int RESERVED : 1;
#elif defined(BIGENDIAN_CPU)
    unsigned int RESERVED : 1;
    unsigned int SE2_NUM_LINE : 5;
    unsigned int SE1_NUM_LINE : 5;
    unsigned int SE0_NUM_LINE : 5;
    unsigned int GLOBAL_NUM_LINE : 5;
    unsigned int RESERVED1 : 3;
    unsigned int PERFMON_SEGMENT_SIZE : 8;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union RLC_SPM_PERFMON_SEGMENT_SIZE_CORE1 {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERFMON_SEGMENT_SIZE_CORE1 : 7;
    unsigned int RESERVED1 : 5;
    unsigned int SE4_NUM_LINE : 5;
    unsigned int SE5_NUM_LINE : 5;
    unsigned int SE6_NUM_LINE : 5;
    unsigned int SE7_NUM_LINE : 5;
#elif defined(BIGENDIAN_CPU)
    unsigned int SE7_NUM_LINE : 5;
    unsigned int SE6_NUM_LINE : 5;
    unsigned int SE5_NUM_LINE : 5;
    unsigned int SE4_NUM_LINE : 5;
    unsigned int RESERVED1 : 5;
    unsigned int PERFMON_SEGMENT_SIZE_CORE1 : 7;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union RLC_SPM_MUXSEL_DATA {
  struct {
  #if defined(LITTLEENDIAN_CPU)
    struct {
      unsigned int counter : 6;
      unsigned int block : 5;
      unsigned int instance : 5;
    } lo;
    struct {
      unsigned int counter : 6;
      unsigned int block : 5;
      unsigned int instance : 5;
    } hi;
  #elif defined(BIGENDIAN_CPU)
    struct {
      unsigned int instance : 5;
      unsigned int block : 5;
      unsigned int counter : 6;
    } hi;
    struct {
      unsigned int instance : 5;
      unsigned int block : 5;
      unsigned int counter : 6;
    } lo;
  #endif
  } bits;
  unsigned int u32All;
};

union RLC_SPM_MC_CNTL {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int RLC_SPM_VMID : 4;
    unsigned int RLC_SPM_POLICY : 1;
    unsigned int RLC_SPM_PERF_CNTR : 1;
    unsigned int RLC_SPM_FED : 1;
    unsigned int RLC_SPM_MTYPE_OVER : 1;
    unsigned int RLC_SPM_MTYPE : 2;
    unsigned int RESERVED : 22;
#elif defined(BIGENDIAN_CPU)
    unsigned int RESERVED : 22;
    unsigned int RLC_SPM_MTYPE : 2;
    unsigned int RLC_SPM_MTYPE_OVER : 1;
    unsigned int RLC_SPM_FED : 1;
    unsigned int RLC_SPM_PERF_CNTR : 1;
    unsigned int RLC_SPM_POLICY : 1;
    unsigned int RLC_SPM_VMID : 4;
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

union SQ_THREAD_TRACE_BASE2 {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int ADDR_HI : 4;
    unsigned int : 28;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 28;
    unsigned int ADDR_HI : 4;
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
    unsigned int : 2;
    unsigned int VMID_MASK : 16;
#elif defined(BIGENDIAN_CPU)
    unsigned int VMID_MASK : 16;
    unsigned int : 2;
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

union CPF_PERFCOUNTER0_SELECT {
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

union ATC_L2_PERFCOUNTER0_CFG {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 8;
    unsigned int PERF_SEL_END : 8;
    unsigned int : 8;
    unsigned int PERF_MODE : 4;
    unsigned int ENABLE : 1;
    unsigned int CLEAR : 1;
    unsigned int : 2;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 2;
    unsigned int CLEAR : 1;
    unsigned int ENABLE : 1;
    unsigned int PERF_MODE : 4;
    unsigned int : 8;
    unsigned int PERF_SEL_END : 8;
    unsigned int PERF_SEL : 8;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union MC_VM_L2_PERFCOUNTER0_CFG {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 8;
    unsigned int PERF_SEL_END : 8;
    unsigned int : 8;
    unsigned int PERF_MODE : 4;
    unsigned int ENABLE : 1;
    unsigned int CLEAR : 1;
    unsigned int : 2;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 2;
    unsigned int CLEAR : 1;
    unsigned int ENABLE : 1;
    unsigned int PERF_MODE : 4;
    unsigned int : 8;
    unsigned int PERF_SEL_END : 8;
    unsigned int PERF_SEL : 8;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};
// include gfxip/gfx9/gfx9_pm4defs.h
#define COPY_DATA_SEL_REG 0                   ///< Mem-mapped register
#define COPY_DATA_SEL_SRC_SYS_PERF_COUNTER 4  ///< Privileged memory performance counter
#define COPY_DATA_SEL_COUNT_1DW 0             ///< Copy 1 word (32 bits)
// include gfxip/gfx9/gfx9_pm4_it_opcodes.h

enum IT_OpCodeType {
  IT_NOP = 0x10,
  IT_WRITE_DATA = 0x37,
  IT_WAIT_REG_MEM = 0x3C,
  IT_INDIRECT_BUFFER = 0x3F,
  IT_COPY_DATA = 0x40,
  IT_EVENT_WRITE = 0x46,
  IT_ACQUIRE_MEM = 0x58,
  IT_SET_SH_REG = 0x76,
  IT_SET_UCONFIG_REG = 0x79,
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
  src_sel__mec_copy_data__perfcounters = 4,
  src_sel__mec_copy_data__immediate_data = 5,
};

enum MEC_COPY_DATA_dst_sel_enum {
  dst_sel__mec_copy_data__mem_mapped_register = 0,
  dst_sel__mec_copy_data__perfcounters = 4,
  dst_sel__mec_copy_data__memory = 5,
};

enum MEC_COPY_DATA_src_cache_policy_enum {
  src_cache_policy__mec_copy_data__lru = 0,
  src_cache_policy__mec_copy_data__stream = 1,
};

enum MEC_COPY_DATA_count_sel_enum {
  count_sel__mec_copy_data__32_bits_of_data = 0,
  count_sel__mec_copy_data__64_bits_of_data = 1,
};

enum MEC_COPY_DATA_wr_confirm_enum {
  wr_confirm__mec_copy_data__do_not_wait_for_confirmation = 0,
};

enum MEC_COPY_DATA_dst_cache_policy_enum {
  dst_cache_policy__mec_copy_data__lru = 0,
  dst_cache_policy__mec_copy_data__stream = 1,
};

enum MEC_COPY_DATA_pq_exe_status_enum {
  pq_exe_status__mec_copy_data__default = 0,
  pq_exe_status__mec_copy_data__phase_update = 1
};

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

enum MEC_SET_CONFIG_REG_index_enum {
  index__mec_set_config_reg__default = 0,
  index__mec_set_config_reg__insert_vmid = 1
};

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

enum MEC_WRITE_DATA_dst_sel_enum {
  dst_sel__mec_write_data__mem_mapped_register = 0,
};

enum MEC_WRITE_DATA_addr_incr_enum {
  addr_incr__mec_write_data__do_not_increment_address = 1,
};

enum MEC_WRITE_DATA_wr_confirm_enum {
  wr_confirm__mec_write_data__do_not_wait_for_write_confirmation = 0,
  wr_confirm__mec_write_data__wait_for_write_confirmation = 1
};

enum MEC_WRITE_DATA_cache_policy_enum {
  cache_policy__mec_write_data__lru = 0,
  cache_policy__mec_write_data__stream = 1
};

typedef struct PM4_MEC_WRITE_DATA {
  union {
    PM4_MEC_TYPE_3_HEADER header;  /// header
    uint32_t ordinal1;
  };

  union {
    struct {
      uint32_t reserved1 : 8;
      MEC_WRITE_DATA_dst_sel_enum dst_sel : 4;
      uint32_t reserved2 : 4;
      MEC_WRITE_DATA_addr_incr_enum addr_incr : 1;
      uint32_t reserved3 : 2;
      uint32_t resume_vf : 1;
      MEC_WRITE_DATA_wr_confirm_enum wr_confirm : 1;
      uint32_t reserved4 : 4;
      MEC_WRITE_DATA_cache_policy_enum cache_policy : 2;
      uint32_t reserved5 : 5;
    } bitfields2;
    uint32_t ordinal2;
  };

  union {
    struct {
      uint32_t dst_mmreg_addr : 18;
      uint32_t reserved6 : 14;
    } bitfields3a;
    struct {
      uint32_t dst_gds_addr : 16;
      uint32_t reserved7 : 16;
    } bitfields3b;
    struct {
      uint32_t reserved8 : 2;
      uint32_t dst_mem_addr_lo : 30;
    } bitfields3c;
    uint32_t ordinal3;
  };

  uint32_t dst_mem_addr_hi;

  //  uint32_t data[];  // N-DWords

} PM4MEC_WRITE_DATA, *PPM4MEC_WRITE_DATA;

enum MEC_SET_SH_REG_index_enum {
     index__mec_set_sh_reg__default = 0,
     index__mec_set_sh_reg__insert_vmid = 1 };


typedef struct PM4_MEC_SET_SH_REG
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reg_offset:16;
            uint32_t reserved1:7;
            uint32_t vmid_shift:5;
            MEC_SET_SH_REG_index_enum index:4;
        } bitfields2;
        uint32_t ordinal2;
    };

//  uint32_t reg_data[];  // N-DWords

} PM4MEC_SET_SH_REG, *PPM4MEC_SET_SH_REG;

typedef struct PM4_MEC_SET_UCONFIG_REG
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reg_offset:16;
            uint32_t reserved1:16;
        } bitfields2;
        uint32_t ordinal2;
    };

//  uint32_t reg_data[];  // N-DWords

} PM4MEC_SET_UCONFIG_REG, *PPM4MEC_SET_UCONFIG_REG;

typedef struct PM4_MEC_NOP
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1;
    };

//  uint32_t data_block[];  // N-DWords

} PM4MEC_NOP, *PPM4MEC_NOP;

// include gfxip/gfx9/gfx9_utils.h
#define PM4_TYPE_SHIFT 30
#define PM4_COUNT_SHIFT 16
#define PM4_OPCODE_SHIFT 8
#define PM4_TYPE3_HDR(_opc_, _count_)                                                              \
  (uint32_t)((3) << PM4_TYPE_SHIFT | ((_count_)-2) << PM4_COUNT_SHIFT | (_opc_) << PM4_OPCODE_SHIFT)
// include gfxip/gfx9/gfx9_block_info.h

enum CounterBlockId {
  CpcCounterBlockId,
  CpfCounterBlockId,
  GdsCounterBlockId,
  GrbmCounterBlockId,
  GrbmSeCounterBlockId,
  SpiCounterBlockId,
  SqCounterBlockId,
  SqGsCounterBlockId,
  SqVsCounterBlockId,
  SqPsCounterBlockId,
  SqHsCounterBlockId,
  SqCsCounterBlockId,
  SxCounterBlockId,
  TaCounterBlockId,
  TcaCounterBlockId,
  TccCounterBlockId,
  TcpCounterBlockId,
  TdCounterBlockId,
  GceaCounterBlockId,
  AtcCounterBlockId,
  AtcL2CounterBlockId,
  McVmL2CounterBlockId,
  RpbCounterBlockId,
  SdmaCounterBlockId,
  HwInfoCounterBlockId,
  LastCounterBlockId = HwInfoCounterBlockId,
};

enum SpmGlobalBlockId {
  SPM_GLOBAL_BLOCK_NAME_CPC = 1,
  SPM_GLOBAL_BLOCK_NAME_CPF = 2,
  SPM_GLOBAL_BLOCK_NAME_GDS = 3,
  SPM_GLOBAL_BLOCK_NAME_TCC = 4,
  SPM_GLOBAL_BLOCK_NAME_TCA = 5,
};

enum SpmSeBlockId {
  SPM_SE_BLOCK_NAME_SX  = 3,
  SPM_SE_BLOCK_NAME_TA  = 5,
  SPM_SE_BLOCK_NAME_TD  = 6,
  SPM_SE_BLOCK_NAME_TCP = 7,
  SPM_SE_BLOCK_NAME_SPI = 8,
  SPM_SE_BLOCK_NAME_SQG = 9,
};
static const uint32_t TaCounterBlockNumInstances    = 16;
static const uint32_t TdCounterBlockNumInstances    = 16;
static const uint32_t TcpCounterBlockNumInstances   = 16;
static const uint32_t TcaCounterBlockNumInstances   = 2;
static const uint32_t TccCounterBlockNumInstances   = 16;
static const uint32_t SdmaCounterBlockNumInstances  = 2;
static const uint32_t SdmaCounterBlockMaxInstances  = 8;
static const uint32_t CpcCounterBlockNumCounters    = 2;
static const uint32_t CpfCounterBlockNumCounters    = 2;
static const uint32_t GdsCounterBlockNumCounters    = 4;
static const uint32_t GrbmCounterBlockNumCounters   = 2;
static const uint32_t GrbmSeCounterBlockNumCounters = 4;
static const uint32_t SdmaCounterBlockNumCounters   = 2;
static const uint32_t SpiCounterBlockNumCounters    = 6;
static const uint32_t SqCounterBlockNumCounters     = 8;
static const uint32_t SxCounterBlockNumCounters     = 4;
static const uint32_t TaCounterBlockNumCounters     = 2;
static const uint32_t TcaCounterBlockNumCounters    = 4;
static const uint32_t TccCounterBlockNumCounters    = 4;
static const uint32_t TcpCounterBlockNumCounters    = 4;
static const uint32_t TdCounterBlockNumCounters     = 2;
static const uint32_t AtcCounterBlockNumCounters    = 4;
static const uint32_t AtcL2CounterBlockNumCounters  = 2;
static const uint32_t McVmL2CounterBlockNumCounters = 8;
static const uint32_t RpbCounterBlockNumCounters    = 4;
static const uint32_t CpcCounterBlockMaxEvent       = CPC_PERF_SEL_ME2_DC1_SPI_BUSY;
static const uint32_t CpfCounterBlockMaxEvent       = CPF_PERF_SEL_CPF_UTCL2IU_STALL;
static const uint32_t GdsCounterBlockMaxEvent       = GDS_PERF_SEL_GWS_BYPASS;
static const uint32_t GrbmCounterBlockMaxEvent      = GRBM_PERF_SEL_CPAXI_BUSY;
static const uint32_t GrbmSeCounterBlockMaxEvent    = GRBM_PERF_SEL_CPAXI_BUSY;
static const uint32_t SdmaCounterBlockMaxEvent      = SDMA_PERF_SEL_MMHUB_TAG_DELAY_COUNTER;
static const uint32_t SpiCounterBlockMaxEvent       = SPI_PERF_VWC_CSC_WR;
static const uint32_t SqCounterBlockMaxEvent        = SQC_PERF_SEL_DUMMY_LAST;
static const uint32_t SxCounterBlockMaxEvent        = SX_PERF_SEL_DB3_SIZE;
static const uint32_t TaCounterBlockMaxEvent        = TA_PERF_SEL_first_xnack_on_phase3;
static const uint32_t TcaCounterBlockMaxEvent       = TCA_PERF_SEL_CROSSBAR_STALL_TCC7;
static const uint32_t TccCounterBlockMaxEvent       = TCC_PERF_SEL_CLIENT127_REQ;
static const uint32_t TcpCounterBlockMaxEvent       = TCP_PERF_SEL_TCC_DCC_REQ;
static const uint32_t TdCounterBlockMaxEvent        = TD_PERF_SEL_texels_zeroed_out_by_blend_zero_prt;
static const uint32_t AtcCounterBlockMaxEvent       = 23;
static const uint32_t AtcL2CounterBlockMaxEvent     = 7;
static const uint32_t RpbCounterBlockMaxEvent       = 62;
static const uint32_t McVmL2CounterBlockMaxEvent    = 20;
// include gfxip/gfx9/gfx9_primitives.h

class gfx9_cntx_prim {
 public:
  static const uint32_t GFXIP_LEVEL = 9;
  static const uint32_t NUMBER_OF_BLOCKS = LastCounterBlockId + 1;
  static const uint32_t GRBM_GFX_INDEX_ADDR = mmGRBM_GFX_INDEX;
  static const uint32_t COMPUTE_PERFCOUNT_ENABLE_ADDR = mmCOMPUTE_PERFCOUNT_ENABLE;
  static const uint32_t RLC_PERFMON_CLK_CNTL_ADDR = mmRLC_PERFMON_CLK_CNTL;
  static const uint32_t CP_PERFMON_CNTL_ADDR = mmCP_PERFMON_CNTL;
  static const uint32_t SRBM_PERFMON_CNTL_ADDR = 0;

  static const uint32_t MC_CONFIG_MCD_ADDR = 0;
  static const uint32_t MC_SEQ_SELECT_ADDR = 0;
  static const uint32_t MC_SEQ_SELECT1_ADDR = 0;
  static const uint32_t MC_SEQ_CONTROL_ADDR = 0;
  static const uint32_t MC_SEQ_PERFCOUNTER_RSLT_CNTL_ADDR = 0;
  static const uint32_t MC_SEQ_PERFCOUNTER_RSLT_CNTL_M1_ADDR = 0;
  static const uint32_t MC_SEQ_PERFCOUNTER_RSLT_CNTL_M2_ADDR = 0;
  static const uint32_t MC_SEQ_PERFCOUNTER_RSLT_CNTL_M3_ADDR = 0;

  static const uint32_t MC_PERFCOUNTER_RSLT_CNTL__ENABLE_ANY_MASK_PRM = 0x01000000L;
  static const uint32_t MC_PERFCOUNTER_RSLT_CNTL__CLEAR_ALL_MASK_PRM = 0x02000000L;

  static const uint32_t SQ_PERFCOUNTER_CTRL_ADDR = mmSQ_PERFCOUNTER_CTRL;
  static const uint32_t SQ_PERFCOUNTER_CTRL2_ADDR = 0;
  static const uint32_t SQ_PERFCOUNTER_MASK_ADDR = mmSQ_PERFCOUNTER_MASK;
  static const uint32_t COMPUTE_THREAD_TRACE_ENABLE_ADDR = 0;
  static const uint32_t SQ_THREAD_TRACE_MASK_ADDR = mmSQ_THREAD_TRACE_MASK;
  static const uint32_t SQ_THREAD_TRACE_PERF_MASK_ADDR = mmSQ_THREAD_TRACE_PERF_MASK;
  static const uint32_t SQ_THREAD_TRACE_TOKEN_MASK_ADDR = mmSQ_THREAD_TRACE_TOKEN_MASK;
  static const uint32_t SQ_THREAD_TRACE_TOKEN_MASK2_ADDR = mmSQ_THREAD_TRACE_TOKEN_MASK2;
  static const uint32_t SQ_THREAD_TRACE_MODE_ADDR = mmSQ_THREAD_TRACE_MODE;
  static const uint32_t SQ_THREAD_TRACE_BASE_ADDR = mmSQ_THREAD_TRACE_BASE;
  static const uint32_t SQ_THREAD_TRACE_BASE2_ADDR = mmSQ_THREAD_TRACE_BASE2;
  static const uint32_t SQ_THREAD_TRACE_SIZE_ADDR = mmSQ_THREAD_TRACE_SIZE;
  static const uint32_t SQ_THREAD_TRACE_CTRL_ADDR = mmSQ_THREAD_TRACE_CTRL;
  static const uint32_t SQ_THREAD_TRACE_HIWATER_ADDR = mmSQ_THREAD_TRACE_HIWATER;
  static const uint32_t SQ_THREAD_TRACE_HIWATER_VAL = 0x6;
  static const uint32_t SQ_THREAD_TRACE_STATUS_ADDR = mmSQ_THREAD_TRACE_STATUS;
  static const uint32_t SQ_THREAD_TRACE_CNTR_ADDR = mmSQ_THREAD_TRACE_CNTR;
  static const uint32_t SQ_THREAD_TRACE_WPTR_ADDR = mmSQ_THREAD_TRACE_WPTR;
  static const uint32_t SQ_THREAD_TRACE_STATUS_OFFSET =
      mmSQ_THREAD_TRACE_STATUS - UCONFIG_SPACE_START;
  static const uint32_t TT_BUFF_ALIGN_SHIFT = 12;

  static const uint32_t SDMA_COUNTER_BLOCK_NUM_INSTANCES = SdmaCounterBlockMaxInstances;

  static const uint32_t RLC_SPM_PERFMON_CNTL__ADDR = mmRLC_SPM_PERFMON_CNTL;
  static const uint32_t RLC_SPM_MC_CNTL__ADDR = mmRLC_SPM_MC_CNTL;
  static const uint32_t RLC_SPM_PERFMON_RING_BASE_LO__ADDR = mmRLC_SPM_PERFMON_RING_BASE_LO;
  static const uint32_t RLC_SPM_PERFMON_RING_BASE_HI__ADDR = mmRLC_SPM_PERFMON_RING_BASE_HI;
  static const uint32_t RLC_SPM_PERFMON_RING_SIZE__ADDR = mmRLC_SPM_PERFMON_RING_SIZE;
  static const uint32_t RLC_SPM_PERFMON_SEGMENT_SIZE__ADDR = mmRLC_SPM_PERFMON_SEGMENT_SIZE;
  static const uint32_t RLC_SPM_PERFMON_SEGMENT_SIZE_CORE1__ADDR = mmRLC_SPM_PERFMON_SEGMENT_SIZE_CORE1;
  static const uint32_t RLC_SPM_GLOBAL_MUXSEL_ADDR__ADDR = mmRLC_SPM_GLOBAL_MUXSEL_ADDR;
  static const uint32_t RLC_SPM_GLOBAL_MUXSEL_DATA__ADDR = mmRLC_SPM_GLOBAL_MUXSEL_DATA;
  static const uint32_t RLC_SPM_SE_MUXSEL_ADDR__ADDR = mmRLC_SPM_SE_MUXSEL_ADDR;
  static const uint32_t RLC_SPM_SE_MUXSEL_DATA__ADDR = mmRLC_SPM_SE_MUXSEL_DATA;
  static const uint32_t RLC_SPM_COUNTERS_PER_LINE = 16;
  static const uint32_t RLC_SPM_TIMESTAMP_SIZE16 = 4;

  static uint32_t sqtt_perfcounter_addr(uint32_t index) {
    static constexpr uint32_t SQTT_PERFCOUNTERS_SELECT[16] = {
      mmSQ_PERFCOUNTER0_SELECT, mmSQ_PERFCOUNTER1_SELECT, mmSQ_PERFCOUNTER2_SELECT, mmSQ_PERFCOUNTER3_SELECT,
      mmSQ_PERFCOUNTER4_SELECT, mmSQ_PERFCOUNTER5_SELECT, mmSQ_PERFCOUNTER6_SELECT, mmSQ_PERFCOUNTER7_SELECT,
      mmSQ_PERFCOUNTER8_SELECT, mmSQ_PERFCOUNTER9_SELECT, mmSQ_PERFCOUNTER10_SELECT, mmSQ_PERFCOUNTER11_SELECT,
      mmSQ_PERFCOUNTER12_SELECT, mmSQ_PERFCOUNTER13_SELECT, mmSQ_PERFCOUNTER14_SELECT, mmSQ_PERFCOUNTER15_SELECT
    };
    return SQTT_PERFCOUNTERS_SELECT[index&0xF];
  }

  union mux_info_t {
    uint16_t data;
    struct {
      uint16_t counter  : 6;
      uint16_t block    : 5;
      uint16_t instance : 5;
    } gfx;
  };

  static const uint32_t SQ_BLOCK_ID = SqCounterBlockId;
  static const uint32_t SQ_BLOCK_SPM_ID = 9;

  static const uint32_t COPY_DATA_SEL_REG_PRM = COPY_DATA_SEL_REG;
  static const uint32_t COPY_DATA_SEL_SRC_SYS_PERF_COUNTER_PRM = COPY_DATA_SEL_SRC_SYS_PERF_COUNTER;
  static const uint32_t COPY_DATA_SEL_COUNT_1DW_PRM = COPY_DATA_SEL_COUNT_1DW;

  static uint32_t Low32(const uint64_t& v) { return (uint32_t)v; }
  static uint32_t High32(const uint64_t& v) { return (uint32_t)(v >> 32); }

  // SPM delay functions for global instance
  static uint32_t get_spm_global_delay(const counter_des_t& counter_des, const uint32_t& instance_index) {
    const auto* block_info = counter_des.block_info;
    return block_info->delay_info[instance_index].val - 1;
  }

  // SPM delay functions for se instance
  static uint32_t get_spm_se_delay(const counter_des_t& counter_des, const uint32_t& se_index, const uint32_t& instance_index) {
    const auto* block_info = counter_des.block_info;
    int delay_index = se_index * block_info->instance_count + instance_index;
    return block_info->delay_info[delay_index].val -1;
  }

  // GRBM broadcasting mode
  static uint32_t grbm_broadcast_value() {
    regGRBM_GFX_INDEX grbm_gfx_index{};
    grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }

  // GRBM SE indexing
  static uint32_t grbm_inst_index_value(const uint32_t& instance_index) {
    regGRBM_GFX_INDEX grbm_gfx_index{};
    grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }

  // GRBM SE indexing
  static uint32_t grbm_se_index_value(const uint32_t& se_index) {
    regGRBM_GFX_INDEX grbm_gfx_index{};
    grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_INDEX = se_index;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }
  static uint32_t grbm_se_sh_wgp_index_value(uint32_t se_index, uint32_t wgp, uint32_t sa) { return 0; }

  // GRBM SE/BlockInstance indexing
  static uint32_t grbm_inst_se_index_value(const uint32_t& instance_index,
                                           const uint32_t& se_index) {
    regGRBM_GFX_INDEX grbm_gfx_index{};
    grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
    grbm_gfx_index.bitfields.SE_INDEX = se_index;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }

  // GRBM SE/SH indexing
  static uint32_t grbm_se_sh_index_value(const uint32_t& se_index, const uint32_t& sh_index) {
    regGRBM_GFX_INDEX grbm_gfx_index{};
    grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_INDEX = se_index;
    grbm_gfx_index.bitfields.SH_INDEX = sh_index;
    return grbm_gfx_index.u32All;
  }

  // GRBM SH/SE/BlockInstance indexing
  static uint32_t grbm_inst_se_sh_index_value(const uint32_t& instance_index,
                                              const uint32_t& se_index,
                                              const uint32_t& sh_index) {
    regGRBM_GFX_INDEX grbm_gfx_index{};
    grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
    grbm_gfx_index.bitfields.SE_INDEX = se_index;
    grbm_gfx_index.bitfields.SH_INDEX = sh_index;
    return grbm_gfx_index.u32All;
  }

  // CP_PERFMON_CNTL value to reset counters
  static uint32_t cp_perfmon_cntl_reset_value() {
    regCP_PERFMON_CNTL cp_perfmon_cntl{};
    return cp_perfmon_cntl.u32All;
  }

  // CP_PERFMON_CNTL value to start counters
  static uint32_t cp_perfmon_cntl_start_value() {
    regCP_PERFMON_CNTL cp_perfmon_cntl{};
    cp_perfmon_cntl.bits.PERFMON_STATE = 1;
    return cp_perfmon_cntl.u32All;
  }

  // CP_PERFMON_CNTL value to stop/freeze counters
  static uint32_t cp_perfmon_cntl_stop_value() {
    regCP_PERFMON_CNTL cp_perfmon_cntl{};
    cp_perfmon_cntl.bits.PERFMON_STATE = 2;
    cp_perfmon_cntl.bits.PERFMON_SAMPLE_ENABLE = 1;
    return cp_perfmon_cntl.u32All;
  }

  // Compute Perfcount Enable register value to enable counting
  static uint32_t cp_perfcount_enable_value() {
    regCOMPUTE_PERFCOUNT_ENABLE cp_perfcount_enable{};
    cp_perfcount_enable.bits.PERFCOUNT_ENABLE = 1;
    return cp_perfcount_enable.u32All;
  }

  // Compute Perfcount Disable register value to enable counting
  static uint32_t cp_perfcount_disable_value() {
    regCOMPUTE_PERFCOUNT_ENABLE cp_perfcount_enable{};
    cp_perfcount_enable.bits.PERFCOUNT_ENABLE = 0;
    return cp_perfcount_enable.u32All;
  }

  // SQ Block primitives

  // SQ Counter Select Register value
  static uint32_t sq_select_value(const counter_des_t& counter_des) {
    regSQ_PERFCOUNTER0_SELECT sq_cntr_sel{};
    sq_cntr_sel.bits.SIMD_MASK = 0xF;
    sq_cntr_sel.bits.SQC_BANK_MASK = 0xF;
    sq_cntr_sel.bits.SQC_CLIENT_MASK = 0xF;
    sq_cntr_sel.bits.PERF_SEL = counter_des.id;
    return sq_cntr_sel.u32All;
  }
  static uint32_t sq_spm_select_value(const counter_des_t& counter_des) {
    regSQ_PERFCOUNTER0_SELECT sq_cntr_sel{};
    sq_cntr_sel.bits.SIMD_MASK = 0xF;
    sq_cntr_sel.bits.SQC_BANK_MASK = 0xF;
    sq_cntr_sel.bits.SQC_CLIENT_MASK = 0xF;
    sq_cntr_sel.bits.PERF_SEL = counter_des.id;
    sq_cntr_sel.bits.SPM_MODE = 3; // PERFMON_SPM_MODE_32BIT_CLAMP
    return sq_cntr_sel.u32All;
  }

  // SQ Counter Mask Register value
  static uint32_t sq_mask_value(const counter_des_t&) {
    regSQ_PERFCOUNTER_MASK sq_cntr_mask{};
    sq_cntr_mask.bits.SH0_MASK = 0xFFFF;
    sq_cntr_mask.bits.SH1_MASK = 0xFFFF;
    return sq_cntr_mask.u32All;
  }

  // SQ Counter Control Register value
  static uint32_t sq_control_value(const counter_des_t& counter_des) {
    const uint32_t block_id = counter_des.block_des.id;
    regSQ_PERFCOUNTER_CTRL sq_cntr_ctrl{};
    if (block_id == SqCounterBlockId) {
      sq_cntr_ctrl.bits.GS_EN = 0x1;
      sq_cntr_ctrl.bits.VS_EN = 0x1;
      sq_cntr_ctrl.bits.PS_EN = 0x1;
      sq_cntr_ctrl.bits.HS_EN = 0x1;
      sq_cntr_ctrl.bits.CS_EN = 0x1;
    } else if (block_id == SqGsCounterBlockId) {
      sq_cntr_ctrl.bits.GS_EN = 0x1;
    } else if (block_id == SqVsCounterBlockId) {
      sq_cntr_ctrl.bits.VS_EN = 0x1;
    } else if (block_id == SqPsCounterBlockId) {
      sq_cntr_ctrl.bits.PS_EN = 0x1;
    } else if (block_id == SqHsCounterBlockId) {
      sq_cntr_ctrl.bits.HS_EN = 0x1;
    } else if (block_id == SqCsCounterBlockId) {
      sq_cntr_ctrl.bits.CS_EN = 0x1;
    }
    sq_cntr_ctrl.bits.VMID_MASK = 0xFFFF;
    return sq_cntr_ctrl.u32All;
  }

  // SQ validate counter attributes
  static void validate_counters(uint32_t counters_vec_attr) {
#if SQ_CONFLICT_CHECK == 1
    const uint32_t mask = CounterBlockSqAttr | CounterBlockTcAttr;
    const bool conflict = ((counters_vec_attr & mask) == mask);
    if (conflict) abort();
#endif
  }

  // SQ Counter Control enable perfomance counter in graphics pipeline stages
  static uint32_t sq_control_enable_value() {
    regSQ_PERFCOUNTER_CTRL sq_cntr_ctrl{};
    sq_cntr_ctrl.bits.PS_EN = 0x1;
    sq_cntr_ctrl.bits.VS_EN = 0x1;
    sq_cntr_ctrl.bits.GS_EN = 0x1;
    sq_cntr_ctrl.bits.ES_EN = 0x1;
    sq_cntr_ctrl.bits.HS_EN = 0x1;
    sq_cntr_ctrl.bits.LS_EN = 0x1;
    sq_cntr_ctrl.bits.CS_EN = 0x1;
    sq_cntr_ctrl.bits.VMID_MASK = 0xFFFF;
    return sq_cntr_ctrl.u32All;
  }
  static uint32_t sq_control2_enable_value() { return 0; }
  static uint32_t sq_control2_disable_value() { return 0; }

  // MC Block primitives

  // MC Channel value
  static uint32_t mc_channel_mask(const counter_des_t& counter_des) {
    return 3;
  }
  static uint32_t mc_broadcast_mcd_value() { return 0; }
  static uint32_t mc_config_value(const counter_des_t& counter_des) {
    return counter_des.index;
  }
  // The following function is unused in gfx9.
  static uint32_t mc_seq_config_val(const counter_des_t& counter_des) {
    return 0;
  }
  static uint32_t mc_hbm_broadcast_mcd_value() { return 0; }

  // MC SQE registers values
  static uint32_t mc_seq_reset_value() { return 0; }
  static uint32_t mc_seq_start_value() { return 0; }
  static uint32_t mc_seq_select_value(const counter_des_t&) { return 0; }
  static uint32_t mc_seq_select1_value(const counter_des_t&) { return 0; }
  static uint32_t mc_seq_hbm_reset_value() { return 0; }
  static uint32_t mc_seq_hbm_start_value() { return 0; }
  static uint32_t mc_seq_hbm_stop_value() { return 0; }
  static uint32_t mc_config_mcd_select_value(const counter_des_t&) { return 0; }
  static uint32_t mc_seq_perfcounter_cfg_addr(const counter_des_t&) { return 0; }
  static uint32_t mc_seq_perfcounter_select_value(const counter_des_t&) { return 0; }
  static uint32_t mc_config_mcd_hbm_sample_value(const counter_des_t&) { return 0; }
  static uint32_t mc_seq_hbm_sample_value(const counter_des_t&) { return 0; }
  static uint32_t mc_seq_perfcounter_rslt_cntl_addr(const counter_des_t&) { return 0; }
  static uint32_t mc_seq_perfcounter_rslt_cntl_value(const counter_des_t&) { return 0; }
  static uint32_t mc_hbm_register_lo_addr(const counter_des_t& counter_des) { return 0; }
  static uint32_t mc_hbm_register_hi_addr(const counter_des_t& counter_des) { return 0; }

  // MC registers values
  template <typename Select> static uint32_t mc_select_value(const counter_des_t& counter_des) {
    Select select{};
    select.bits.PERF_SEL = counter_des.id;
    select.bits.PERF_MODE = PERFMON_COUNTER_MODE_ACCUM;
    select.bits.ENABLE = 1;
    return select.u32All;
  }
  static uint32_t mc_reset_value() {
    return MC_PERFCOUNTER_RSLT_CNTL__CLEAR_ALL_MASK_PRM;
  }
  static uint32_t mc_start_value() {
    return MC_PERFCOUNTER_RSLT_CNTL__ENABLE_ANY_MASK_PRM;
  }

  // Counter Select Register value templates
  template <typename Select> static uint32_t select_value(const counter_des_t& counter_des) {
    Select select{};
    select.bits.PERF_SEL = counter_des.id;
    return select.u32All;
  }
  template <typename Select> static uint32_t select_value_t2(const counter_des_t& counter_des) {
    Select select{};
    select.bits.PERFCOUNTER_SELECT = counter_des.id;
    return select.u32All;
  }
  template <typename Select> static uint32_t select_value_t3(const counter_des_t& counter_des) {
    Select select{};
    select.bits.CNTR_SEL0 = counter_des.id;
    return select.u32All;
  }
  static uint32_t spm_select_value(const counter_des_t& counter_des) {
    regTCC_PERFCOUNTER0_SELECT select{};
    select.bits.PERF_SEL = counter_des.id;
    select.bits.CNTR_MODE = 3;  // PERFMON_SPM_MODE_32BIT_CLAMP
    return select.u32All;
  }
  static uint32_t spm_even_select_value(const counter_des_t& counter_des) {
    regTCC_PERFCOUNTER0_SELECT select{};
    select.bits.PERF_SEL = counter_des.id;
    select.bits.CNTR_MODE = 3;  // PERFMON_SPM_MODE_32BIT_CLAMP
    return select.u32All;
  }
  static uint32_t spm_odd_select_value(const counter_des_t& counter_des) {
    regTCC_PERFCOUNTER0_SELECT select{};
    select.bits.PERF_SEL1 = counter_des.id;
    select.bits.CNTR_MODE = 3;  // PERFMON_SPM_MODE_32BIT_CLAMP
    return select.u32All;
  }
  static mux_info_t spm_mux_ram_value(const counter_des_t& counter_des) {
    mux_info_t mxinfo{0};
    mxinfo.gfx.counter = counter_des.index;
    mxinfo.gfx.block = counter_des.block_info->spm_block_id;
    mxinfo.gfx.instance = counter_des.block_des.index;
    return mxinfo;
  }
  static mux_info_t spm_mux_ram_value(uint16_t counter, uint16_t block, uint16_t instance) {
    mux_info_t mxinfo{0};
    mxinfo.gfx.counter = counter;
    mxinfo.gfx.block = block;
    mxinfo.gfx.instance = instance;
    return mxinfo;
  }
  static uint32_t spm_mux_ram_idx_incr(uint32_t idx) {
    uint32_t incr_idx = ++idx;
    if (!(incr_idx % RLC_SPM_COUNTERS_PER_LINE)) incr_idx += RLC_SPM_COUNTERS_PER_LINE;
    return incr_idx;
  }

  // SRBM Registers values
  static uint32_t srbm_reset_value() { return 0; }
  static uint32_t srbm_start_value() { return 0; }
  static uint32_t srbm_stop_value() { return 0; }

  // SDMA primitives
  static uint32_t sdma_disable_clear_value() {
    regSDMA0_PERFMON_CNTL sdma_perfmon_cntl{};
    sdma_perfmon_cntl.bits.PERF_CLEAR0  = 0x1;
    sdma_perfmon_cntl.bits.PERF_CLEAR1  = 0x1;
    return sdma_perfmon_cntl.u32All;
  }

  static uint32_t sdma_select_value(const counter_des_t& counter_des) {
    regSDMA0_PERFMON_CNTL sdma_perfmon_cntl{};
    if (counter_des.index == 0) {
      sdma_perfmon_cntl.bits.PERF_ENABLE0 = 0x1;
      sdma_perfmon_cntl.bits.PERF_CLEAR0  = 0x0;
      sdma_perfmon_cntl.bits.PERF_SEL0 = counter_des.id;
    } else {
      sdma_perfmon_cntl.bits.PERF_ENABLE1 = 0x1;
      sdma_perfmon_cntl.bits.PERF_CLEAR1  = 0x0;
      sdma_perfmon_cntl.bits.PERF_SEL1 = counter_des.id;
    }
    return sdma_perfmon_cntl.u32All;
  }

  static uint32_t sdma_stop_value() {
    regSDMA0_PERFMON_CNTL sdma_perfmon_cntl{};
    return sdma_perfmon_cntl.u32All;
  }

  // SPM trace routines
  static uint32_t rlc_spm_mc_cntl_value() {
    regRLC_SPM_MC_CNTL mc_cntl;
    mc_cntl.u32All = 0;
    mc_cntl.bits.RLC_SPM_VMID = 15;
    return mc_cntl.u32All;
  }
  static uint32_t cp_perfmon_cntl_spm_start_value() {
    regCP_PERFMON_CNTL cp_perfmon_cntl{};
    cp_perfmon_cntl.bits.SPM_PERFMON_STATE = 1;
    return cp_perfmon_cntl.u32All;
  }
  static uint32_t cp_perfmon_cntl_spm_stop_value() {
    regCP_PERFMON_CNTL cp_perfmon_cntl{};
    cp_perfmon_cntl.bits.SPM_PERFMON_STATE = 2;
    return cp_perfmon_cntl.u32All;
  }
  static uint32_t rlc_spm_muxsel_data(const uint32_t& value, const counter_des_t& counter_des,
                                      const uint32_t& block, const uint32_t& hi) {
    RLC_SPM_MUXSEL_DATA data{};
    data.u32All = value;
    if (hi == 0) {
      data.bits.lo.counter = counter_des.index;
      data.bits.lo.block = block;
      data.bits.lo.instance = counter_des.block_des.index;
    } else {
      data.bits.hi.counter = counter_des.index;
      data.bits.hi.block = block;
      data.bits.hi.instance = counter_des.block_des.index;
    }
    return data.u32All;
  }
  static uint32_t rlc_spm_perfmon_cntl_value(const uint32_t& sampling_rate) {
    regRLC_SPM_PERFMON_CNTL value{};
    value.bits.PERFMON_SAMPLE_INTERVAL = sampling_rate;
    return value.u32All;
  }
  static uint32_t rlc_spm_perfmon_segment_size_value(const uint32_t& global_count, const uint32_t& se_count) {
    const uint32_t global_nlines = global_count;
    const uint32_t se_nlines = se_count;
    const uint32_t segment_size = (global_nlines + (4 * se_nlines));
    regRLC_SPM_PERFMON_SEGMENT_SIZE value{};
    value.bits.GLOBAL_NUM_LINE = global_nlines;
    value.bits.SE0_NUM_LINE = se_nlines;
    value.bits.SE1_NUM_LINE = se_nlines;
    value.bits.SE2_NUM_LINE = se_nlines;
    value.bits.PERFMON_SEGMENT_SIZE = segment_size;
    return value.u32All;
  }
  static uint32_t rlc_spm_perfmon_segment_size_core1_value(const uint32_t& se_count) {
    const uint32_t se_nlines = se_count;
    const uint32_t segment_size = 4 * se_nlines;
    regRLC_SPM_PERFMON_SEGMENT_SIZE_CORE1 value{};
    value.bits.PERFMON_SEGMENT_SIZE_CORE1 = segment_size;
    value.bits.SE4_NUM_LINE = se_nlines;
    value.bits.SE5_NUM_LINE = se_nlines;
    value.bits.SE6_NUM_LINE = se_nlines;
    value.bits.SE7_NUM_LINE = se_nlines;
    return value.u32All;
  }

  // Enable Thread Trace for all VM Id's
  // Enable all of the SIMD's of the compute unit
  // Enable Compute Unit (CU) at index Zero to be used for fine-grained data
  // Enable Shader Array (SH) at index Zero to be used for fine-grained data
  //
  // @note: Not enabling REG_STALL_EN, SPI_STALL_EN and SQ_STALL_EN bits. They
  // are useful if we wish to program buffer throttling.
  //
  static uint32_t sqtt_mask_value(const uint32_t& targetCu, const uint32_t& vmIdMask) {
    regSQ_THREAD_TRACE_MASK mask{};
    mask.bits.SH_SEL = 0x0;
    mask.bits.SIMD_EN = 0xF;
    mask.bits.CU_SEL = targetCu;
    mask.bits.SQ_STALL_EN = 0x1;
    mask.bits.SPI_STALL_EN = 0x1;
    mask.bits.REG_STALL_EN = 0x1;
    mask.bits.VM_ID_MASK = vmIdMask;
    return mask.u32All;
  }
  
  static uint32_t sqtt_mask_value_gfx10() { return 0;}

  // Mask of compute units to get thread trace data from
  static uint32_t sqtt_perf_mask_value() {
    regSQ_THREAD_TRACE_PERF_MASK perf_mask{};
    perf_mask.bits.SH0_MASK = 0xFFFF;
    perf_mask.bits.SH1_MASK = 0xFFFF;
    return perf_mask.u32All;
  }

  // Indicate the different TT messages/tokens that should be enabled/logged
  // Indicate the different TT tokens that specify register operations to be logged
  static uint32_t sqtt_token_mask_value() {
    regSQ_THREAD_TRACE_TOKEN_MASK token_mask{};
    token_mask.bits.REG_MASK = 0xFF;
    token_mask.bits.TOKEN_MASK = 0xFFFF;
    token_mask.bits.REG_DROP_ON_STALL = 0x1;
    return token_mask.u32All;
  }

  // Indicate the different TT tokens that specify instruction operations to be logged
  // Disabling specifically instruction operations updating Program Counter (PC).
  // @note: The field is defined in the spec incorrectly as a 16-bit value
  static uint32_t sqtt_token_mask2_value() {
    regSQ_THREAD_TRACE_TOKEN_MASK2 token_mask2{};
    token_mask2.bits.INST_MASK = 0xFFFFFF7F;
    return token_mask2.u32All;
  }

  // Check if stalling is supported
  static bool sqtt_stalling_enabled(const uint32_t& mask_val, const uint32_t& token_mask_val) {
    regSQ_THREAD_TRACE_MASK mask{};
    mask.u32All = mask_val;
    regSQ_THREAD_TRACE_TOKEN_MASK token_mask{};
    token_mask.u32All = token_mask_val;
    return ((mask.bits.SQ_STALL_EN) || (mask.bits.SPI_STALL_EN) || (mask.bits.REG_STALL_EN) ||
            (token_mask.bits.REG_DROP_ON_STALL));
  }

  // Indicates various attributes of a thread trace session.
  //
  // MASK_CS: Which shader types should be enabled for data collection
  //      Enable CS Shader types.
  //
  // WRAP: How trace buffer should be used as a ring buffer or as a linear
  //      buffer - Disable WRAP mode i.e use it as a linear buffer
  //
  // MODE: Enables a thread trace session
  //
  // CAPTURE_MODE: When thread trace data is collected immediately after MODE
  //      is enabled or wait until a Thread Trace Start event is received
  //
  // AUTOFLUSH_EN: Flush thread trace data to buffer often automatically
  //
  // Thread trace mode OFF value
  static uint32_t sqtt_mode_off_value() {
    regSQ_THREAD_TRACE_MODE mode{};
    mode.bits.WRAP = 0;
    mode.bits.CAPTURE_MODE = 0;
    mode.bits.MASK_CS = 1;
    mode.bits.AUTOFLUSH_EN = 1;
    mode.bits.MODE = SQ_THREAD_TRACE_MODE_OFF;
    return mode.u32All;
  }
  // Thread trace mode ON value
  static uint32_t sqtt_mode_on_value() {
    regSQ_THREAD_TRACE_MODE mode{};
    mode.u32All = sqtt_mode_off_value();
    mode.bits.MODE = SQ_THREAD_TRACE_MODE_ON;
    return mode.u32All;
  }

  // Base address of buffer to use for thread trace
  static uint32_t sqtt_base_value_lo(const uint64_t& base_addr) {
    regSQ_THREAD_TRACE_BASE base{};
    base.bits.ADDR = Low32(base_addr >> TT_BUFF_ALIGN_SHIFT);
    return base.u32All;
  }
  static uint32_t sqtt_base_value_hi(const uint64_t& base_addr) {
    regSQ_THREAD_TRACE_BASE2 base{};
    base.bits.ADDR_HI = High32(base_addr >> TT_BUFF_ALIGN_SHIFT);
    return base.u32All;
  }

  // Indicates the size of buffer to use per Shader Engine instance.
  // The size is specified in terms of 4KB blocks
  static uint32_t sqtt_size_value(const uint32_t& size_val) {
    regSQ_THREAD_TRACE_SIZE size{};
    size.bits.SIZE = size_val >> TT_BUFF_ALIGN_SHIFT;
    return size.u32All;
  }
  static uint32_t sqtt_zero_size_value() { return 0; }

  // Thread trace ctrl register value
  static uint32_t sqtt_ctrl_value() {
    regSQ_THREAD_TRACE_CTRL ctrl{};
    ctrl.bits.RESET_BUFFER = 1;
    return ctrl.u32All;
  }

  // SPM primitives
  static uint16_t spm_timestamp_muxsel() {
    return 0xF0F0;
  }
};

template <>
inline uint32_t gfx9_cntx_prim::select_value<regSX_PERFCOUNTER0_SELECT>(
    const counter_des_t& counter_des) {
  return select_value_t2<regSX_PERFCOUNTER0_SELECT>(counter_des);
}

template <>
inline uint32_t gfx9_cntx_prim::select_value<regGDS_PERFCOUNTER0_SELECT>(
    const counter_des_t& counter_des) {
  return select_value_t2<regGDS_PERFCOUNTER0_SELECT>(counter_des);
}

template <>
inline uint32_t gfx9_cntx_prim::select_value<regCPC_PERFCOUNTER0_SELECT>(
    const counter_des_t& counter_des) {
  return select_value_t3<regCPC_PERFCOUNTER0_SELECT>(counter_des);
}

template <>
inline uint32_t gfx9_cntx_prim::select_value<regCPF_PERFCOUNTER0_SELECT>(
    const counter_des_t& counter_des) {
  return select_value_t3<regCPF_PERFCOUNTER0_SELECT>(counter_des);
}
// include gfxip/gfx9/gfx9_block_table.h

static const CounterRegInfo SqCounterRegAddr[] = {
    {mmSQ_PERFCOUNTER0_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER0_LO, mmSQ_PERFCOUNTER0_HI},
    {mmSQ_PERFCOUNTER1_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER1_LO, mmSQ_PERFCOUNTER1_HI},
    {mmSQ_PERFCOUNTER2_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER2_LO, mmSQ_PERFCOUNTER2_HI},
    {mmSQ_PERFCOUNTER3_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER3_LO, mmSQ_PERFCOUNTER3_HI},
    {mmSQ_PERFCOUNTER4_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER4_LO, mmSQ_PERFCOUNTER4_HI},
    {mmSQ_PERFCOUNTER5_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER5_LO, mmSQ_PERFCOUNTER5_HI},
    {mmSQ_PERFCOUNTER6_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER6_LO, mmSQ_PERFCOUNTER6_HI},
    {mmSQ_PERFCOUNTER7_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER7_LO, mmSQ_PERFCOUNTER7_HI},
    {mmSQ_PERFCOUNTER8_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER8_LO, mmSQ_PERFCOUNTER8_HI},
    {mmSQ_PERFCOUNTER9_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER9_LO, mmSQ_PERFCOUNTER9_HI},
    {mmSQ_PERFCOUNTER10_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER10_LO, mmSQ_PERFCOUNTER10_HI},
    {mmSQ_PERFCOUNTER11_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER11_LO, mmSQ_PERFCOUNTER11_HI},
    {mmSQ_PERFCOUNTER12_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER12_LO, mmSQ_PERFCOUNTER12_HI},
    {mmSQ_PERFCOUNTER13_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER13_LO, mmSQ_PERFCOUNTER13_HI},
    {mmSQ_PERFCOUNTER14_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER14_LO, mmSQ_PERFCOUNTER14_HI},
    {mmSQ_PERFCOUNTER15_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER15_LO, mmSQ_PERFCOUNTER15_HI}};

static const BlockDelayInfo SqBlockDelayInfo[] = {
  {mmRLC_SPM_SQG_PERFMON_SAMPLE_DELAY, 0x0000002c},
  {mmRLC_SPM_SQG_PERFMON_SAMPLE_DELAY, 0x00000029},
  {mmRLC_SPM_SQG_PERFMON_SAMPLE_DELAY, 0x0000002a},
  {mmRLC_SPM_SQG_PERFMON_SAMPLE_DELAY, 0x00000027},
};

static const CounterRegInfo GrbmCounterRegAddr[] = {
    {mmGRBM_PERFCOUNTER0_SELECT, 0, mmGRBM_PERFCOUNTER0_LO, mmGRBM_PERFCOUNTER0_HI},
    {mmGRBM_PERFCOUNTER1_SELECT, 0, mmGRBM_PERFCOUNTER1_LO, mmGRBM_PERFCOUNTER1_HI}};

static const CounterRegInfo GrbmSeCounterRegAddr[] = {
    {mmGRBM_SE0_PERFCOUNTER_SELECT, 0, mmGRBM_SE0_PERFCOUNTER_LO, mmGRBM_SE0_PERFCOUNTER_HI},
    {mmGRBM_SE1_PERFCOUNTER_SELECT, 0, mmGRBM_SE1_PERFCOUNTER_LO, mmGRBM_SE1_PERFCOUNTER_HI},
    {mmGRBM_SE2_PERFCOUNTER_SELECT, 0, mmGRBM_SE2_PERFCOUNTER_LO, mmGRBM_SE2_PERFCOUNTER_HI},
    {mmGRBM_SE3_PERFCOUNTER_SELECT, 0, mmGRBM_SE3_PERFCOUNTER_LO, mmGRBM_SE3_PERFCOUNTER_HI}};

static const CounterRegInfo SpiCounterRegAddr[] = {
    {mmSPI_PERFCOUNTER0_SELECT, 0, mmSPI_PERFCOUNTER0_LO, mmSPI_PERFCOUNTER0_HI},
    {mmSPI_PERFCOUNTER1_SELECT, 0, mmSPI_PERFCOUNTER1_LO, mmSPI_PERFCOUNTER1_HI},
    {mmSPI_PERFCOUNTER2_SELECT, 0, mmSPI_PERFCOUNTER2_LO, mmSPI_PERFCOUNTER2_HI},
    {mmSPI_PERFCOUNTER3_SELECT, 0, mmSPI_PERFCOUNTER3_LO, mmSPI_PERFCOUNTER3_HI},
    {mmSPI_PERFCOUNTER4_SELECT, 0, mmSPI_PERFCOUNTER4_LO, mmSPI_PERFCOUNTER4_HI},
    {mmSPI_PERFCOUNTER5_SELECT, 0, mmSPI_PERFCOUNTER5_LO, mmSPI_PERFCOUNTER5_HI}};

static const BlockDelayInfo SpiBlockDelayInfo[] = {
    { mmRLC_SPM_SPI_PERFMON_SAMPLE_DELAY, 0x0000002a},
    { mmRLC_SPM_SPI_PERFMON_SAMPLE_DELAY, 0x0000002a},
    { mmRLC_SPM_SPI_PERFMON_SAMPLE_DELAY, 0x00000027},
    { mmRLC_SPM_SPI_PERFMON_SAMPLE_DELAY, 0x00000027}};

static const CounterRegInfo TcaCounterRegAddr[] = {
    {mmTCA_PERFCOUNTER0_SELECT, 0, mmTCA_PERFCOUNTER0_LO, mmTCA_PERFCOUNTER0_HI},
    {mmTCA_PERFCOUNTER1_SELECT, 0, mmTCA_PERFCOUNTER1_LO, mmTCA_PERFCOUNTER1_HI},
    {mmTCA_PERFCOUNTER2_SELECT, 0, mmTCA_PERFCOUNTER2_LO, mmTCA_PERFCOUNTER2_HI},
    {mmTCA_PERFCOUNTER3_SELECT, 0, mmTCA_PERFCOUNTER3_LO, mmTCA_PERFCOUNTER3_HI}};

static const BlockDelayInfo TcaBlockDelayInfo[] = {
    { mmRLC_SPM_TCA_PERFMON_SAMPLE_DELAY, 0x00000018},
    { mmRLC_SPM_TCA_PERFMON_SAMPLE_DELAY, 0x0000001c}};

static const CounterRegInfo TccCounterRegAddr[] = {
    {mmTCC_PERFCOUNTER0_SELECT, 0, mmTCC_PERFCOUNTER0_LO, mmTCC_PERFCOUNTER0_HI},
    {mmTCC_PERFCOUNTER1_SELECT, 0, mmTCC_PERFCOUNTER1_LO, mmTCC_PERFCOUNTER1_HI},
    {mmTCC_PERFCOUNTER2_SELECT, 0, mmTCC_PERFCOUNTER2_LO, mmTCC_PERFCOUNTER2_HI},
    {mmTCC_PERFCOUNTER3_SELECT, 0, mmTCC_PERFCOUNTER3_LO, mmTCC_PERFCOUNTER3_HI}};

static const BlockDelayInfo TccBlockDelayInfo[] = {
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x0000000F},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x00000015},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x00000017},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x0000001d},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x0000001b},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x00000017},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x00000013},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x0000000f},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x00000014},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x00000018},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x0000001c},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x00000020},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x0000001d},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x00000019},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x00000015},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY, 0x00000011}};

static const CounterRegInfo TcpCounterRegAddr[] = {
    {mmTCP_PERFCOUNTER0_SELECT, 0, mmTCP_PERFCOUNTER0_LO, mmTCP_PERFCOUNTER0_HI},
    {mmTCP_PERFCOUNTER1_SELECT, 0, mmTCP_PERFCOUNTER1_LO, mmTCP_PERFCOUNTER1_HI},
    {mmTCP_PERFCOUNTER2_SELECT, 0, mmTCP_PERFCOUNTER2_LO, mmTCP_PERFCOUNTER2_HI},
    {mmTCP_PERFCOUNTER3_SELECT, 0, mmTCP_PERFCOUNTER3_LO, mmTCP_PERFCOUNTER3_HI}};

static const BlockDelayInfo TcpBlockDelayInfo[] = {
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000030},  // se0
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000002e},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000002c},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000002a},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000028},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000026},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000024},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000022},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000020},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000001e},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000001c},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000001a},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000018},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000016},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000014},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000012},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000002c},  // se1
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000002a},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000028},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000026},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000024},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000022},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000020},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000001e},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000001c},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000001a},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000018},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000016},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000014},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000012},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000010},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000000e},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000002c},  // se2
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000002a},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000028},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000026},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000024},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000022},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000020},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000001e},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000001c},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000001a},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000018},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000016},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000014},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000012},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000010},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000000e},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000002c},  // se3
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000028},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000026},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000024},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000022},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000020},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000001e},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000001c},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000001a},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000018},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000016},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000014},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000012},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x00000010},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000000e},
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY, 0x0000000c}};

static const CounterRegInfo SxCounterRegAddr[] = {
    {mmSX_PERFCOUNTER0_SELECT, 0, mmSX_PERFCOUNTER0_LO, mmSX_PERFCOUNTER0_HI},
    {mmSX_PERFCOUNTER1_SELECT, 0, mmSX_PERFCOUNTER1_LO, mmSX_PERFCOUNTER1_HI},
    {mmSX_PERFCOUNTER2_SELECT, 0, mmSX_PERFCOUNTER2_LO, mmSX_PERFCOUNTER2_HI},
    {mmSX_PERFCOUNTER3_SELECT, 0, mmSX_PERFCOUNTER3_LO, mmSX_PERFCOUNTER3_HI}};

static const BlockDelayInfo SxBlockDelayInfo[] = {
    { mmRLC_SPM_SX_PERFMON_SAMPLE_DELAY, 0x00000006 },
    { mmRLC_SPM_SX_PERFMON_SAMPLE_DELAY, 0x00000006 },
    { mmRLC_SPM_SX_PERFMON_SAMPLE_DELAY, 0x00000008 },
    { mmRLC_SPM_SX_PERFMON_SAMPLE_DELAY, 0x00000004 }};

static const CounterRegInfo TaCounterRegAddr[] = {
    {mmTA_PERFCOUNTER0_SELECT, 0, mmTA_PERFCOUNTER0_LO, mmTA_PERFCOUNTER0_HI},
    {mmTA_PERFCOUNTER1_SELECT, 0, mmTA_PERFCOUNTER1_LO, mmTA_PERFCOUNTER1_HI}};

static const BlockDelayInfo TaBlockDelayInfo[] = {
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000002c },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000002a },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000028 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000026 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000024 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000022 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000020 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000001e },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000001c },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000001a },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000018 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000016 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000014 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000012 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000010 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000000e },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000028 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000026 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000025 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000023 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000021 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000001f },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000001d },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000001b },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000019 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000017 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000015 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000013 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000011 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000000f },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000000d },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000000b },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000028 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000026 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000024 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000022 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000020 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000001e },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000001c },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000001a },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000018 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000016 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000014 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000012 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000010 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000000e },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000000c },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000000a },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000027 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000025 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000023 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000021 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000001f },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000001d },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000001b },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000019 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000017 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000015 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000013 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000011 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000000f },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000000d },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x0000000b },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY, 0x00000009 }};

static const CounterRegInfo TdCounterRegAddr[] = {
    {mmTD_PERFCOUNTER0_SELECT, 0, mmTD_PERFCOUNTER0_LO, mmTD_PERFCOUNTER0_HI},
    {mmTD_PERFCOUNTER1_SELECT, 0, mmTD_PERFCOUNTER1_LO, mmTD_PERFCOUNTER1_HI}};

static const BlockDelayInfo TdBlockDelayInfo[] = {
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000002c },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000002a },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000028 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000026 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000024 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000022 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000020 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000001e },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000001c },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000001a },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000018 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000016 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000014 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000012 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000010 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000000e },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000028 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000026 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000025 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000023 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000021 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000001f },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000001d },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000001b },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000019 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000017 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000015 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000013 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000011 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000000f },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000000d },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000000b },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000028 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000027 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000025 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000023 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000021 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000001f },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000001d },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000001b },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000019 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000017 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000015 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000013 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000011 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000000f },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000000d },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000000b },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000027 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000025 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000023 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000021 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000001f },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000001d },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000001b },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000019 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000017 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000015 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000013 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000011 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000000f },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000000d },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x0000000b },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY, 0x00000009 }};

static const CounterRegInfo GdsCounterRegAddr[] = {
    {mmGDS_PERFCOUNTER0_SELECT, 0, mmGDS_PERFCOUNTER0_LO, mmGDS_PERFCOUNTER0_HI},
    {mmGDS_PERFCOUNTER1_SELECT, 0, mmGDS_PERFCOUNTER1_LO, mmGDS_PERFCOUNTER1_HI},
    {mmGDS_PERFCOUNTER2_SELECT, 0, mmGDS_PERFCOUNTER2_LO, mmGDS_PERFCOUNTER2_HI},
    {mmGDS_PERFCOUNTER3_SELECT, 0, mmGDS_PERFCOUNTER3_LO, mmGDS_PERFCOUNTER3_HI}};

static const BlockDelayInfo GdsBlockDelayInfo[] = {
    { mmRLC_SPM_GDS_PERFMON_SAMPLE_DELAY, 0x0000002d }
};

static const CounterRegInfo CpcCounterRegAddr[] = {
    {mmCPC_PERFCOUNTER0_SELECT, 0, mmCPC_PERFCOUNTER0_LO, mmCPC_PERFCOUNTER0_HI},
    {mmCPC_PERFCOUNTER1_SELECT, 0, mmCPC_PERFCOUNTER1_LO, mmCPC_PERFCOUNTER1_HI}};

static const BlockDelayInfo CpcBlockDelayInfo[] = {
    { mmRLC_SPM_CPC_PERFMON_SAMPLE_DELAY, 0x0000002c}
};

static const CounterRegInfo CpfCounterRegAddr[] = {
    {mmCPF_PERFCOUNTER0_SELECT, 0, mmCPF_PERFCOUNTER0_LO, mmCPF_PERFCOUNTER0_HI},
    {mmCPF_PERFCOUNTER1_SELECT, 0, mmCPF_PERFCOUNTER1_LO, mmCPF_PERFCOUNTER1_HI}};

static const BlockDelayInfo CpfBlockDelayInfo[] = {
    { mmRLC_SPM_CPF_PERFMON_SAMPLE_DELAY, 0x00000032 }
};

static const CounterRegInfo AtcCounterRegAddr[] = {
    {mmATC_PERFCOUNTER0_CFG, mmATC_PERFCOUNTER_RSLT_CNTL, mmATC_PERFCOUNTER_LO, mmATC_PERFCOUNTER_HI},
    {mmATC_PERFCOUNTER1_CFG, mmATC_PERFCOUNTER_RSLT_CNTL, mmATC_PERFCOUNTER_LO, mmATC_PERFCOUNTER_HI},
    {mmATC_PERFCOUNTER2_CFG, mmATC_PERFCOUNTER_RSLT_CNTL, mmATC_PERFCOUNTER_LO, mmATC_PERFCOUNTER_HI},
    {mmATC_PERFCOUNTER3_CFG, mmATC_PERFCOUNTER_RSLT_CNTL, mmATC_PERFCOUNTER_LO, mmATC_PERFCOUNTER_HI}};

static const CounterRegInfo AtcL2CounterRegAddr[] = {
    {mmATC_L2_PERFCOUNTER0_CFG, mmATC_L2_PERFCOUNTER_RSLT_CNTL, mmATC_L2_PERFCOUNTER_LO, mmATC_L2_PERFCOUNTER_HI},
    {mmATC_L2_PERFCOUNTER1_CFG, mmATC_L2_PERFCOUNTER_RSLT_CNTL, mmATC_L2_PERFCOUNTER_LO, mmATC_L2_PERFCOUNTER_HI}};

static const CounterRegInfo RpbCounterRegAddr[] = {
    {mmRPB_PERFCOUNTER0_CFG, mmRPB_PERFCOUNTER_RSLT_CNTL, mmRPB_PERFCOUNTER_LO, mmRPB_PERFCOUNTER_HI},
    {mmRPB_PERFCOUNTER1_CFG, mmRPB_PERFCOUNTER_RSLT_CNTL, mmRPB_PERFCOUNTER_LO, mmRPB_PERFCOUNTER_HI},
    {mmRPB_PERFCOUNTER2_CFG, mmRPB_PERFCOUNTER_RSLT_CNTL, mmRPB_PERFCOUNTER_LO, mmRPB_PERFCOUNTER_HI},
    {mmRPB_PERFCOUNTER3_CFG, mmRPB_PERFCOUNTER_RSLT_CNTL, mmRPB_PERFCOUNTER_LO, mmRPB_PERFCOUNTER_HI}};

static const CounterRegInfo McVmL2CounterRegAddr[] = {
    {mmMC_VM_L2_PERFCOUNTER0_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI},
    {mmMC_VM_L2_PERFCOUNTER1_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI},
    {mmMC_VM_L2_PERFCOUNTER2_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI},
    {mmMC_VM_L2_PERFCOUNTER3_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI},
    {mmMC_VM_L2_PERFCOUNTER4_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI},
    {mmMC_VM_L2_PERFCOUNTER5_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI},
    {mmMC_VM_L2_PERFCOUNTER6_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI},
    {mmMC_VM_L2_PERFCOUNTER7_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI}};

static const CounterRegInfo SdmaCounterRegAddr[] = {
    {mmSDMA0_PERFMON_CNTL, 0, mmSDMA0_PERFCOUNTER0_RESULT, 0},
    {mmSDMA0_PERFMON_CNTL, 0, mmSDMA0_PERFCOUNTER1_RESULT, 0},
    {mmSDMA1_PERFMON_CNTL, 0, mmSDMA1_PERFCOUNTER0_RESULT, 0},
    {mmSDMA1_PERFMON_CNTL, 0, mmSDMA1_PERFCOUNTER1_RESULT, 0},
    {mmSDMA2_PERFMON_CNTL, 0, mmSDMA2_PERFCOUNTER0_RESULT, 0},
    {mmSDMA2_PERFMON_CNTL, 0, mmSDMA2_PERFCOUNTER1_RESULT, 0},
    {mmSDMA3_PERFMON_CNTL, 0, mmSDMA3_PERFCOUNTER0_RESULT, 0},
    {mmSDMA3_PERFMON_CNTL, 0, mmSDMA3_PERFCOUNTER1_RESULT, 0},
    {mmSDMA4_PERFMON_CNTL, 0, mmSDMA4_PERFCOUNTER0_RESULT, 0},
    {mmSDMA4_PERFMON_CNTL, 0, mmSDMA4_PERFCOUNTER1_RESULT, 0},
    {mmSDMA5_PERFMON_CNTL, 0, mmSDMA5_PERFCOUNTER0_RESULT, 0},
    {mmSDMA5_PERFMON_CNTL, 0, mmSDMA5_PERFCOUNTER1_RESULT, 0},
    {mmSDMA6_PERFMON_CNTL, 0, mmSDMA6_PERFCOUNTER0_RESULT, 0},
    {mmSDMA6_PERFMON_CNTL, 0, mmSDMA6_PERFCOUNTER1_RESULT, 0},
    {mmSDMA7_PERFMON_CNTL, 0, mmSDMA7_PERFCOUNTER0_RESULT, 0},
    {mmSDMA7_PERFMON_CNTL, 0, mmSDMA7_PERFCOUNTER1_RESULT, 0}
};
static const GpuBlockInfo GrbmCounterBlockInfo = {"GRBM", GrbmCounterBlockId, 1, GrbmCounterBlockMaxEvent, GrbmCounterBlockNumCounters, GrbmCounterRegAddr, gfx9_cntx_prim::select_value<regGRBM_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
static const GpuBlockInfo GrbmSeCounterBlockInfo = {"GRBM_SE", GrbmSeCounterBlockId, 1, GrbmSeCounterBlockMaxEvent, GrbmSeCounterBlockNumCounters, GrbmSeCounterRegAddr, gfx9_cntx_prim::select_value<regGRBM_SE0_PERFCOUNTER_SELECT>, CounterBlockDfltAttr};
static const GpuBlockInfo SpiCounterBlockInfo = {"SPI", SpiCounterBlockId, 1, SpiCounterBlockMaxEvent, SpiCounterBlockNumCounters, SpiCounterRegAddr, gfx9_cntx_prim::select_value<regSPI_PERFCOUNTER0_SELECT>, CounterBlockSeAttr, SpiBlockDelayInfo, SPM_SE_BLOCK_NAME_SPI};
static const GpuBlockInfo SqCounterBlockInfo = {"SQ", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx9_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr, SqBlockDelayInfo, SPM_SE_BLOCK_NAME_SQG};
static const GpuBlockInfo SqCsCounterBlockInfo = {"SQ_CS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx9_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SxCounterBlockInfo = {"SX", SxCounterBlockId, 1, SxCounterBlockMaxEvent, SxCounterBlockNumCounters, SxCounterRegAddr, gfx9_cntx_prim::select_value<regSX_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockCleanAttr, SxBlockDelayInfo, SPM_SE_BLOCK_NAME_SX};
static const GpuBlockInfo TaCounterBlockInfo = {"TA", TaCounterBlockId, TaCounterBlockNumInstances, TaCounterBlockMaxEvent, TaCounterBlockNumCounters, TaCounterRegAddr, gfx9_cntx_prim::select_value<regTA_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockTcAttr, TaBlockDelayInfo, SPM_SE_BLOCK_NAME_TA};
static const GpuBlockInfo TcaCounterBlockInfo = {"TCA", TcaCounterBlockId, TcaCounterBlockNumInstances, TcaCounterBlockMaxEvent, TcaCounterBlockNumCounters, TcaCounterRegAddr, gfx9_cntx_prim::select_value<regTCA_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockTcAttr|CounterBlockSpmGlobalAttr, TcaBlockDelayInfo, SPM_GLOBAL_BLOCK_NAME_TCA};
static const GpuBlockInfo TccCounterBlockInfo = {"TCC", TccCounterBlockId, TccCounterBlockNumInstances, TccCounterBlockMaxEvent, TccCounterBlockNumCounters, TccCounterRegAddr, gfx9_cntx_prim::select_value<regTCC_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockTcAttr|CounterBlockSpmGlobalAttr, TccBlockDelayInfo, SPM_GLOBAL_BLOCK_NAME_TCC};
static const GpuBlockInfo TdCounterBlockInfo = {"TD", TdCounterBlockId, TdCounterBlockNumInstances, TdCounterBlockMaxEvent, TdCounterBlockNumCounters, TdCounterRegAddr, gfx9_cntx_prim::select_value<regTD_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockTcAttr, TdBlockDelayInfo, SPM_SE_BLOCK_NAME_TD};
static const GpuBlockInfo TcpCounterBlockInfo = {"TCP", TcpCounterBlockId, TcpCounterBlockNumInstances, TcpCounterBlockMaxEvent, TcpCounterBlockNumCounters, TcpCounterRegAddr, gfx9_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockTcAttr, TcpBlockDelayInfo, SPM_SE_BLOCK_NAME_TCP};
static const GpuBlockInfo GdsCounterBlockInfo = {"GDS", GdsCounterBlockId, 1, GdsCounterBlockMaxEvent, GdsCounterBlockNumCounters, GdsCounterRegAddr, gfx9_cntx_prim::select_value<regGDS_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockSpmGlobalAttr, GdsBlockDelayInfo, SPM_GLOBAL_BLOCK_NAME_GDS};
static const GpuBlockInfo CpcCounterBlockInfo = {"CPC", CpcCounterBlockId, 1, CpcCounterBlockMaxEvent, CpcCounterBlockNumCounters, CpcCounterRegAddr, gfx9_cntx_prim::select_value<regCPC_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockSpmGlobalAttr, CpcBlockDelayInfo, SPM_GLOBAL_BLOCK_NAME_CPC};
static const GpuBlockInfo CpfCounterBlockInfo = {"CPF", CpfCounterBlockId, 1, CpfCounterBlockMaxEvent, CpfCounterBlockNumCounters, CpfCounterRegAddr, gfx9_cntx_prim::select_value<regCPF_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockSpmGlobalAttr, CpfBlockDelayInfo, SPM_GLOBAL_BLOCK_NAME_CPF/*2*/};
static const GpuBlockInfo McVmL2CounterBlockInfo = {"MCVML2", McVmL2CounterBlockId, 1, McVmL2CounterBlockMaxEvent, McVmL2CounterBlockNumCounters, McVmL2CounterRegAddr, gfx9_cntx_prim::mc_select_value<regMC_VM_L2_PERFCOUNTER0_CFG>, CounterBlockMcAttr};
static const GpuBlockInfo AtcL2CounterBlockInfo = {"ATCL2", AtcL2CounterBlockId, 1, AtcL2CounterBlockMaxEvent, AtcL2CounterBlockNumCounters, AtcL2CounterRegAddr, gfx9_cntx_prim::mc_select_value<regATC_L2_PERFCOUNTER0_CFG>, CounterBlockMcAttr};
static const GpuBlockInfo AtcCounterBlockInfo = {"ATC", AtcCounterBlockId, 1, AtcCounterBlockMaxEvent, AtcCounterBlockNumCounters, AtcCounterRegAddr, gfx9_cntx_prim::mc_select_value<regATC_PERFCOUNTER0_CFG>, CounterBlockMcAttr};
static const GpuBlockInfo RpbCounterBlockInfo = {"RPB", RpbCounterBlockId, 1, RpbCounterBlockMaxEvent, RpbCounterBlockNumCounters, RpbCounterRegAddr, gfx9_cntx_prim::mc_select_value<regRPB_PERFCOUNTER0_CFG>, CounterBlockMcAttr};
static const GpuBlockInfo SdmaCounterBlockInfo = {"SDMA", SdmaCounterBlockId, SdmaCounterBlockNumInstances, SdmaCounterBlockMaxEvent, SdmaCounterBlockNumCounters, SdmaCounterRegAddr, NULL, CounterBlockSdmaAttr|CounterBlockExplInstAttr};
#endif  // SRC_DEF_GFX9_DEF_H_
