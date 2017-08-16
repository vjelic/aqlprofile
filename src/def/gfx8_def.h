#ifndef _DEF_GFX8_DEF_H_
#define _DEF_GFX8_DEF_H_
#include "def/gpu_block_info.h"
// include gfxip/gfx8/si_ci_vi_merged_enum.h

enum SQ_THREAD_TRACE_MODE_SEL {
  SQ_THREAD_TRACE_MODE_OFF = 0x00000000,
  SQ_THREAD_TRACE_MODE_ON = 0x00000001,
};

enum VGT_EVENT_TYPE {
  CS_PARTIAL_FLUSH = 0x00000007,
};
#define PERSISTENT_SPACE_START 0x00002c00
#define UCONFIG_SPACE_END__CI__VI 0x0000ffff
#define UCONFIG_SPACE_START__CI__VI 0x0000c000
// include gfxip/gfx8/si_ci_vi_merged_mask.h
#define CP_COHER_CNTL__SH_ICACHE_ACTION_ENA_MASK 0x20000000L
#define CP_COHER_CNTL__SH_KCACHE_ACTION_ENA_MASK 0x08000000L
#define CP_COHER_CNTL__TCL1_ACTION_ENA_MASK 0x00400000L
#define CP_COHER_CNTL__TC_ACTION_ENA_MASK 0x00800000L
#define CP_COHER_CNTL__TC_WB_ACTION_ENA_MASK__CI__VI 0x00040000L
#define CP_COHER_SIZE_HI__COHER_SIZE_HI_256B_MASK__CI__VI 0x000000ffL
#define CP_COHER_SIZE__COHER_SIZE_256B_MASK 0xffffffffL
// include gfxip/gfx8/si_ci_vi_merged_shift.h
#define MC_CONFIG_MCD__MC_RD_ENABLE__SHIFT 0x00000008
#define MC_SEQ_PERF_SEQ_CTL__SEL_B__SHIFT__SI__CI 0x00000004
// include gfxip/gfx8/si_ci_vi_merged_offset.h
#define mmCOMPUTE_PERFCOUNT_ENABLE__CI__VI 0x2E0B
#define mmCPC_PERFCOUNTER0_HI__CI__VI 0xD007
#define mmCPC_PERFCOUNTER0_LO__CI__VI 0xD006
#define mmCPC_PERFCOUNTER0_SELECT__CI__VI 0xD809
#define mmCPC_PERFCOUNTER1_HI__CI__VI 0xD005
#define mmCPC_PERFCOUNTER1_LO__CI__VI 0xD004
#define mmCPC_PERFCOUNTER1_SELECT__CI__VI 0xD803
#define mmCPF_PERFCOUNTER0_HI__CI__VI 0xD00B
#define mmCPF_PERFCOUNTER0_LO__CI__VI 0xD00A
#define mmCPF_PERFCOUNTER0_SELECT__CI__VI 0xD807
#define mmCPF_PERFCOUNTER1_HI__CI__VI 0xD009
#define mmCPF_PERFCOUNTER1_LO__CI__VI 0xD008
#define mmCPF_PERFCOUNTER1_SELECT__CI__VI 0xD805
#define mmCP_PERFMON_CNTL__CI__VI 0xD808
#define mmGDS_PERFCOUNTER0_HI__CI__VI 0xD281
#define mmGDS_PERFCOUNTER0_LO__CI__VI 0xD280
#define mmGDS_PERFCOUNTER0_SELECT__CI__VI 0xDA80
#define mmGDS_PERFCOUNTER1_HI__CI__VI 0xD283
#define mmGDS_PERFCOUNTER1_LO__CI__VI 0xD282
#define mmGDS_PERFCOUNTER1_SELECT__CI__VI 0xDA81
#define mmGDS_PERFCOUNTER2_HI__CI__VI 0xD285
#define mmGDS_PERFCOUNTER2_LO__CI__VI 0xD284
#define mmGDS_PERFCOUNTER2_SELECT__CI__VI 0xDA82
#define mmGDS_PERFCOUNTER3_HI__CI__VI 0xD287
#define mmGDS_PERFCOUNTER3_LO__CI__VI 0xD286
#define mmGDS_PERFCOUNTER3_SELECT__CI__VI 0xDA83
#define mmGRBM_GFX_INDEX__CI__VI 0xC200
#define mmGRBM_PERFCOUNTER0_HI__CI__VI 0xD041
#define mmGRBM_PERFCOUNTER0_LO__CI__VI 0xD040
#define mmGRBM_PERFCOUNTER0_SELECT__CI__VI 0xD840
#define mmGRBM_PERFCOUNTER1_HI__CI__VI 0xD044
#define mmGRBM_PERFCOUNTER1_LO__CI__VI 0xD043
#define mmGRBM_PERFCOUNTER1_SELECT__CI__VI 0xD841
#define mmGRBM_SE0_PERFCOUNTER_HI__CI__VI 0xD046
#define mmGRBM_SE0_PERFCOUNTER_LO__CI__VI 0xD045
#define mmGRBM_SE0_PERFCOUNTER_SELECT__CI__VI 0xD842
#define mmGRBM_SE1_PERFCOUNTER_HI__CI__VI 0xD048
#define mmGRBM_SE1_PERFCOUNTER_LO__CI__VI 0xD047
#define mmGRBM_SE1_PERFCOUNTER_SELECT__CI__VI 0xD843
#define mmGRBM_SE2_PERFCOUNTER_HI__CI__VI 0xD04A
#define mmGRBM_SE2_PERFCOUNTER_LO__CI__VI 0xD049
#define mmGRBM_SE2_PERFCOUNTER_SELECT__CI__VI 0xD844
#define mmGRBM_SE3_PERFCOUNTER_HI__CI__VI 0xD04C
#define mmGRBM_SE3_PERFCOUNTER_LO__CI__VI 0xD04B
#define mmGRBM_SE3_PERFCOUNTER_SELECT__CI__VI 0xD845
#define mmMC_CONFIG_MCD 0x0828
#define mmMC_SEQ_PERF_CNTL_1__SI__CI 0x0AFD
#define mmMC_SEQ_PERF_SEQ_CNT_A_I0__VI 0x0A79
#define mmMC_SEQ_PERF_SEQ_CNT_A_I1__VI 0x0A7A
#define mmMC_SEQ_PERF_SEQ_CNT_B_I0__VI 0x0A7B
#define mmMC_SEQ_PERF_SEQ_CNT_B_I1__VI 0x0A7C
#define mmMC_SEQ_PERF_SEQ_CNT_C_I0__VI 0x0AD9
#define mmMC_SEQ_PERF_SEQ_CNT_C_I1__VI 0x0ADA
#define mmMC_SEQ_PERF_SEQ_CNT_D_I0__VI 0x0ADB
#define mmMC_SEQ_PERF_SEQ_CNT_D_I1__VI 0x0ADC
#define mmMC_SEQ_PERF_SEQ_CTL__SI__VI 0x0A78
#define mmSPI_PERFCOUNTER0_HI__CI__VI 0xD180
#define mmSPI_PERFCOUNTER0_LO__CI__VI 0xD181
#define mmSPI_PERFCOUNTER0_SELECT__CI__VI 0xD980
#define mmSPI_PERFCOUNTER1_HI__CI__VI 0xD182
#define mmSPI_PERFCOUNTER1_LO__CI__VI 0xD183
#define mmSPI_PERFCOUNTER1_SELECT__CI__VI 0xD981
#define mmSPI_PERFCOUNTER2_HI__CI__VI 0xD184
#define mmSPI_PERFCOUNTER2_LO__CI__VI 0xD185
#define mmSPI_PERFCOUNTER2_SELECT__CI__VI 0xD982
#define mmSPI_PERFCOUNTER3_HI__CI__VI 0xD186
#define mmSPI_PERFCOUNTER3_LO__CI__VI 0xD187
#define mmSPI_PERFCOUNTER3_SELECT__CI__VI 0xD983
#define mmSPI_PERFCOUNTER4_HI__CI__VI 0xD188
#define mmSPI_PERFCOUNTER4_LO__CI__VI 0xD189
#define mmSPI_PERFCOUNTER4_SELECT__CI__VI 0xD988
#define mmSPI_PERFCOUNTER5_HI__CI__VI 0xD18A
#define mmSPI_PERFCOUNTER5_LO__CI__VI 0xD18B
#define mmSPI_PERFCOUNTER5_SELECT__CI__VI 0xD989
#define mmSQ_PERFCOUNTER0_HI__CI__VI 0xD1C1
#define mmSQ_PERFCOUNTER0_LO__CI__VI 0xD1C0
#define mmSQ_PERFCOUNTER0_SELECT__CI__VI 0xD9C0
#define mmSQ_PERFCOUNTER10_HI__CI__VI 0xD1D5
#define mmSQ_PERFCOUNTER10_LO__CI__VI 0xD1D4
#define mmSQ_PERFCOUNTER10_SELECT__CI__VI 0xD9CA
#define mmSQ_PERFCOUNTER11_HI__CI__VI 0xD1D7
#define mmSQ_PERFCOUNTER11_LO__CI__VI 0xD1D6
#define mmSQ_PERFCOUNTER11_SELECT__CI__VI 0xD9CB
#define mmSQ_PERFCOUNTER12_HI__CI__VI 0xD1D9
#define mmSQ_PERFCOUNTER12_LO__CI__VI 0xD1D8
#define mmSQ_PERFCOUNTER12_SELECT__CI__VI 0xD9CC
#define mmSQ_PERFCOUNTER13_HI__CI__VI 0xD1DB
#define mmSQ_PERFCOUNTER13_LO__CI__VI 0xD1DA
#define mmSQ_PERFCOUNTER13_SELECT__CI__VI 0xD9CD
#define mmSQ_PERFCOUNTER14_HI__CI__VI 0xD1DD
#define mmSQ_PERFCOUNTER14_LO__CI__VI 0xD1DC
#define mmSQ_PERFCOUNTER14_SELECT__CI__VI 0xD9CE
#define mmSQ_PERFCOUNTER15_HI__CI__VI 0xD1DF
#define mmSQ_PERFCOUNTER15_LO__CI__VI 0xD1DE
#define mmSQ_PERFCOUNTER15_SELECT__CI__VI 0xD9CF
#define mmSQ_PERFCOUNTER1_HI__CI__VI 0xD1C3
#define mmSQ_PERFCOUNTER1_LO__CI__VI 0xD1C2
#define mmSQ_PERFCOUNTER1_SELECT__CI__VI 0xD9C1
#define mmSQ_PERFCOUNTER2_HI__CI__VI 0xD1C5
#define mmSQ_PERFCOUNTER2_LO__CI__VI 0xD1C4
#define mmSQ_PERFCOUNTER2_SELECT__CI__VI 0xD9C2
#define mmSQ_PERFCOUNTER3_HI__CI__VI 0xD1C7
#define mmSQ_PERFCOUNTER3_LO__CI__VI 0xD1C6
#define mmSQ_PERFCOUNTER3_SELECT__CI__VI 0xD9C3
#define mmSQ_PERFCOUNTER4_HI__CI__VI 0xD1C9
#define mmSQ_PERFCOUNTER4_LO__CI__VI 0xD1C8
#define mmSQ_PERFCOUNTER4_SELECT__CI__VI 0xD9C4
#define mmSQ_PERFCOUNTER5_HI__CI__VI 0xD1CB
#define mmSQ_PERFCOUNTER5_LO__CI__VI 0xD1CA
#define mmSQ_PERFCOUNTER5_SELECT__CI__VI 0xD9C5
#define mmSQ_PERFCOUNTER6_HI__CI__VI 0xD1CD
#define mmSQ_PERFCOUNTER6_LO__CI__VI 0xD1CC
#define mmSQ_PERFCOUNTER6_SELECT__CI__VI 0xD9C6
#define mmSQ_PERFCOUNTER7_HI__CI__VI 0xD1CF
#define mmSQ_PERFCOUNTER7_LO__CI__VI 0xD1CE
#define mmSQ_PERFCOUNTER7_SELECT__CI__VI 0xD9C7
#define mmSQ_PERFCOUNTER8_HI__CI__VI 0xD1D1
#define mmSQ_PERFCOUNTER8_LO__CI__VI 0xD1D0
#define mmSQ_PERFCOUNTER8_SELECT__CI__VI 0xD9C8
#define mmSQ_PERFCOUNTER9_HI__CI__VI 0xD1D3
#define mmSQ_PERFCOUNTER9_LO__CI__VI 0xD1D2
#define mmSQ_PERFCOUNTER9_SELECT__CI__VI 0xD9C9
#define mmSQ_PERFCOUNTER_CTRL__CI__VI 0xD9E0
#define mmSQ_PERFCOUNTER_MASK__CI__VI 0xD9E1
#define mmSQ_THREAD_TRACE_CNTR 0x2390
#define mmSX_PERFCOUNTER0_HI__CI__VI 0xD241
#define mmSX_PERFCOUNTER0_LO__CI__VI 0xD240
#define mmSX_PERFCOUNTER0_SELECT__CI__VI 0xDA40
#define mmSX_PERFCOUNTER1_HI__CI__VI 0xD243
#define mmSX_PERFCOUNTER1_LO__CI__VI 0xD242
#define mmSX_PERFCOUNTER1_SELECT__CI__VI 0xDA41
#define mmSX_PERFCOUNTER2_HI__CI__VI 0xD245
#define mmSX_PERFCOUNTER2_LO__CI__VI 0xD244
#define mmSX_PERFCOUNTER2_SELECT__CI__VI 0xDA42
#define mmSX_PERFCOUNTER3_HI__CI__VI 0xD247
#define mmSX_PERFCOUNTER3_LO__CI__VI 0xD246
#define mmSX_PERFCOUNTER3_SELECT__CI__VI 0xDA43
#define mmTA_PERFCOUNTER0_HI__CI__VI 0xD2C1
#define mmTA_PERFCOUNTER0_LO__CI__VI 0xD2C0
#define mmTA_PERFCOUNTER0_SELECT__CI__VI 0xDAC0
#define mmTA_PERFCOUNTER1_HI__CI__VI 0xD2C3
#define mmTA_PERFCOUNTER1_LO__CI__VI 0xD2C2
#define mmTA_PERFCOUNTER1_SELECT__CI__VI 0xDAC2
#define mmTCA_PERFCOUNTER0_HI__CI__VI 0xD391
#define mmTCA_PERFCOUNTER0_LO__CI__VI 0xD390
#define mmTCA_PERFCOUNTER0_SELECT__CI__VI 0xDB90
#define mmTCA_PERFCOUNTER1_HI__CI__VI 0xD393
#define mmTCA_PERFCOUNTER1_LO__CI__VI 0xD392
#define mmTCA_PERFCOUNTER1_SELECT__CI__VI 0xDB92
#define mmTCA_PERFCOUNTER2_HI__CI__VI 0xD395
#define mmTCA_PERFCOUNTER2_LO__CI__VI 0xD394
#define mmTCA_PERFCOUNTER2_SELECT__CI__VI 0xDB94
#define mmTCA_PERFCOUNTER3_HI__CI__VI 0xD397
#define mmTCA_PERFCOUNTER3_LO__CI__VI 0xD396
#define mmTCA_PERFCOUNTER3_SELECT__CI__VI 0xDB95
#define mmTCC_PERFCOUNTER0_HI__CI__VI 0xD381
#define mmTCC_PERFCOUNTER0_LO__CI__VI 0xD380
#define mmTCC_PERFCOUNTER0_SELECT__CI__VI 0xDB80
#define mmTCC_PERFCOUNTER1_HI__CI__VI 0xD383
#define mmTCC_PERFCOUNTER1_LO__CI__VI 0xD382
#define mmTCC_PERFCOUNTER1_SELECT__CI__VI 0xDB82
#define mmTCC_PERFCOUNTER2_HI__CI__VI 0xD385
#define mmTCC_PERFCOUNTER2_LO__CI__VI 0xD384
#define mmTCC_PERFCOUNTER2_SELECT__CI__VI 0xDB84
#define mmTCC_PERFCOUNTER3_HI__CI__VI 0xD387
#define mmTCC_PERFCOUNTER3_LO__CI__VI 0xD386
#define mmTCC_PERFCOUNTER3_SELECT__CI__VI 0xDB85
#define mmTCP_PERFCOUNTER0_HI__CI__VI 0xD341
#define mmTCP_PERFCOUNTER0_LO__CI__VI 0xD340
#define mmTCP_PERFCOUNTER0_SELECT__CI__VI 0xDB40
#define mmTCP_PERFCOUNTER1_HI__CI__VI 0xD343
#define mmTCP_PERFCOUNTER1_LO__CI__VI 0xD342
#define mmTCP_PERFCOUNTER1_SELECT__CI__VI 0xDB42
#define mmTCP_PERFCOUNTER2_HI__CI__VI 0xD345
#define mmTCP_PERFCOUNTER2_LO__CI__VI 0xD344
#define mmTCP_PERFCOUNTER2_SELECT__CI__VI 0xDB44
#define mmTCP_PERFCOUNTER3_HI__CI__VI 0xD347
#define mmTCP_PERFCOUNTER3_LO__CI__VI 0xD346
#define mmTCP_PERFCOUNTER3_SELECT__CI__VI 0xDB45
#define mmTD_PERFCOUNTER0_HI__CI__VI 0xD301
#define mmTD_PERFCOUNTER0_LO__CI__VI 0xD300
#define mmTD_PERFCOUNTER0_SELECT__CI__VI 0xDB00
#define mmTD_PERFCOUNTER1_HI__CI__VI 0xD303
#define mmTD_PERFCOUNTER1_LO__CI__VI 0xD302
#define mmTD_PERFCOUNTER1_SELECT__CI__VI 0xDB02
#define mmRLC_PERFMON_CLK_CNTL__VI 0xDCBF
#define mmSQ_THREAD_TRACE_BASE__VI 0xC330
#define mmSQ_THREAD_TRACE_CTRL__VI 0xC335
#define mmSQ_THREAD_TRACE_HIWATER__VI 0xC33B
#define mmSQ_THREAD_TRACE_MASK__VI 0xC332
#define mmSQ_THREAD_TRACE_MODE__VI 0xC336
#define mmSQ_THREAD_TRACE_PERF_MASK__VI 0xC334
#define mmSQ_THREAD_TRACE_SIZE__VI 0xC331
#define mmSQ_THREAD_TRACE_STATUS__VI 0xC33A
#define mmSQ_THREAD_TRACE_TOKEN_MASK__VI 0xC333
#define mmSQ_THREAD_TRACE_TOKEN_MASK2__VI 0xC338
#define mmSQ_THREAD_TRACE_WPTR__VI 0xC339
#define mmSRBM_PERFCOUNTER0_HI__VI 0x7C04
#define mmSRBM_PERFCOUNTER0_LO__VI 0x7C03
#define mmSRBM_PERFCOUNTER0_SELECT__VI 0x7C01
#define mmSRBM_PERFCOUNTER1_HI__VI 0x7C06
#define mmSRBM_PERFCOUNTER1_LO__VI 0x7C05
#define mmSRBM_PERFCOUNTER1_SELECT__VI 0x7C02
#define mmSRBM_PERFMON_CNTL__VI 0x7C00
// include gfxip/gfx8/si_ci_vi_merged_registers.h

union COMPUTE_PERFCOUNT_ENABLE__CI__VI {
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

union CPC_PERFCOUNTER0_SELECT__CI__VI {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 6;
    unsigned int : 4;
    unsigned int PERF_SEL1 : 6;
    unsigned int : 4;
    unsigned int CNTR_MODE : 4;
    unsigned int : 8;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 8;
    unsigned int CNTR_MODE : 4;
    unsigned int : 4;
    unsigned int PERF_SEL1 : 6;
    unsigned int : 4;
    unsigned int PERF_SEL : 6;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union CPF_PERFCOUNTER0_SELECT__CI__VI {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 6;
    unsigned int : 4;
    unsigned int PERF_SEL1 : 6;
    unsigned int : 4;
    unsigned int CNTR_MODE : 4;
    unsigned int : 8;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 8;
    unsigned int CNTR_MODE : 4;
    unsigned int : 4;
    unsigned int PERF_SEL1 : 6;
    unsigned int : 4;
    unsigned int PERF_SEL : 6;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union CP_COHER_BASE {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int COHER_BASE_256B : 32;
#elif defined(BIGENDIAN_CPU)
    unsigned int COHER_BASE_256B : 32;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union CP_COHER_BASE_HI__CI__VI {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int COHER_BASE_HI_256B : 8;
    unsigned int : 24;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 24;
    unsigned int COHER_BASE_HI_256B : 8;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union CP_COHER_SIZE {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int COHER_SIZE_256B : 32;
#elif defined(BIGENDIAN_CPU)
    unsigned int COHER_SIZE_256B : 32;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union CP_COHER_SIZE_HI__CI__VI {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int COHER_SIZE_HI_256B : 8;
    unsigned int : 24;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 24;
    unsigned int COHER_SIZE_HI_256B : 8;
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
    unsigned int SPM_PERFMON_STATE__CI__VI : 4;
    unsigned int PERFMON_ENABLE_MODE : 2;
    unsigned int PERFMON_SAMPLE_ENABLE : 1;
    unsigned int : 21;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 21;
    unsigned int PERFMON_SAMPLE_ENABLE : 1;
    unsigned int PERFMON_ENABLE_MODE : 2;
    unsigned int SPM_PERFMON_STATE__CI__VI : 4;
    unsigned int PERFMON_STATE : 4;
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
    unsigned int PERFCOUNTER_SELECT1__CI__VI : 10;
    unsigned int CNTR_MODE__CI__VI : 4;
    unsigned int : 8;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 8;
    unsigned int CNTR_MODE__CI__VI : 4;
    unsigned int PERFCOUNTER_SELECT1__CI__VI : 10;
    unsigned int PERFCOUNTER_SELECT : 10;
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
    unsigned int WD_BUSY_USER_DEFINED_MASK__CI__VI : 1;
    unsigned int : 3;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 3;
    unsigned int WD_BUSY_USER_DEFINED_MASK__CI__VI : 1;
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
    unsigned int : 10;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 10;
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

union MC_SEQ_PERF_CNTL_1__SI__CI {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PAUSE : 1;
    unsigned int : 7;
    unsigned int SEL_A_MSB : 1;
    unsigned int SEL_B_MSB : 1;
    unsigned int SEL_CH0_C_MSB : 1;
    unsigned int SEL_CH0_D_MSB : 1;
    unsigned int SEL_CH1_A_MSB : 1;
    unsigned int SEL_CH1_B_MSB : 1;
    unsigned int SEL_CH1_C_MSB : 1;
    unsigned int SEL_CH1_D_MSB : 1;
    unsigned int : 16;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 16;
    unsigned int SEL_CH1_D_MSB : 1;
    unsigned int SEL_CH1_C_MSB : 1;
    unsigned int SEL_CH1_B_MSB : 1;
    unsigned int SEL_CH1_A_MSB : 1;
    unsigned int SEL_CH0_D_MSB : 1;
    unsigned int SEL_CH0_C_MSB : 1;
    unsigned int SEL_B_MSB : 1;
    unsigned int SEL_A_MSB : 1;
    unsigned int : 7;
    unsigned int PAUSE : 1;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union MC_SEQ_PERF_SEQ_CTL__SI__CI {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int SEL_A : 4;
    unsigned int SEL_B : 4;
    unsigned int SEL_CH0_C : 4;
    unsigned int SEL_CH0_D : 4;
    unsigned int SEL_CH1_A : 4;
    unsigned int SEL_CH1_B : 4;
    unsigned int SEL_CH1_C : 4;
    unsigned int SEL_CH1_D : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int SEL_CH1_D : 4;
    unsigned int SEL_CH1_C : 4;
    unsigned int SEL_CH1_B : 4;
    unsigned int SEL_CH1_A : 4;
    unsigned int SEL_CH0_D : 4;
    unsigned int SEL_CH0_C : 4;
    unsigned int SEL_B : 4;
    unsigned int SEL_A : 4;
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
    unsigned int PERF_SEL1__CI__VI : 10;
    unsigned int CNTR_MODE__CI__VI : 4;
    unsigned int : 8;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 8;
    unsigned int CNTR_MODE__CI__VI : 4;
    unsigned int PERF_SEL1__CI__VI : 10;
    unsigned int PERF_SEL : 10;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SQ_PERFCOUNTER0_SELECT__CI__VI {
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

union SQ_PERFCOUNTER_MASK__CI__VI {
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

union SQ_THREAD_TRACE_MASK {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int CU_SEL : 5;
    unsigned int SH_SEL : 1;
    unsigned int : 1;
    unsigned int REG_STALL_EN__CI__VI : 1;
    unsigned int SIMD_EN : 4;
    unsigned int VM_ID_MASK : 2;
    unsigned int SPI_STALL_EN__CI__VI : 1;
    unsigned int SQ_STALL_EN__CI__VI : 1;
    unsigned int RANDOM_SEED : 16;
#elif defined(BIGENDIAN_CPU)
    unsigned int RANDOM_SEED : 16;
    unsigned int SQ_STALL_EN__CI__VI : 1;
    unsigned int SPI_STALL_EN__CI__VI : 1;
    unsigned int VM_ID_MASK : 2;
    unsigned int SIMD_EN : 4;
    unsigned int REG_STALL_EN__CI__VI : 1;
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
    unsigned int PRIV : 1;
    unsigned int ISSUE_MASK : 2;
    unsigned int TEST_MODE : 1;
    unsigned int INTERRUPT_EN : 1;
    unsigned int WRAP : 1;
#elif defined(BIGENDIAN_CPU)
    unsigned int WRAP : 1;
    unsigned int INTERRUPT_EN : 1;
    unsigned int TEST_MODE : 1;
    unsigned int ISSUE_MASK : 2;
    unsigned int PRIV : 1;
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

union SQ_THREAD_TRACE_TOKEN_MASK {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int TOKEN_MASK : 16;
    unsigned int REG_MASK : 8;
    unsigned int REG_DROP_ON_STALL__CI__VI : 1;
    unsigned int : 7;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 7;
    unsigned int REG_DROP_ON_STALL__CI__VI : 1;
    unsigned int REG_MASK : 8;
    unsigned int TOKEN_MASK : 16;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SQ_THREAD_TRACE_TOKEN_MASK2__VI {
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

union SRBM_PERFCOUNTER0_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 6;
    unsigned int : 26;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 26;
    unsigned int PERF_SEL : 6;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union SRBM_PERFMON_CNTL {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERFMON_STATE : 4;
    unsigned int : 4;
    unsigned int PERFMON_ENABLE_MODE : 2;
    unsigned int PERFMON_SAMPLE_ENABLE : 1;
    unsigned int : 21;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 21;
    unsigned int PERFMON_SAMPLE_ENABLE : 1;
    unsigned int PERFMON_ENABLE_MODE : 2;
    unsigned int : 4;
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
    unsigned int PERFCOUNTER_SELECT1__CI__VI : 10;
    unsigned int CNTR_MODE__CI__VI : 4;
    unsigned int : 8;
#elif defined(BIGENDIAN_CPU)
    unsigned int : 8;
    unsigned int CNTR_MODE__CI__VI : 4;
    unsigned int PERFCOUNTER_SELECT1__CI__VI : 10;
    unsigned int PERFCOUNTER_SELECT : 10;
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
    unsigned int PERF_SEL1__CI__VI : 8;
    unsigned int : 2;
    unsigned int CNTR_MODE__CI__VI : 4;
    unsigned int PERF_MODE1__CI__VI : 4;
    unsigned int PERF_MODE : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int PERF_MODE : 4;
    unsigned int PERF_MODE1__CI__VI : 4;
    unsigned int CNTR_MODE__CI__VI : 4;
    unsigned int : 2;
    unsigned int PERF_SEL1__CI__VI : 8;
    unsigned int : 2;
    unsigned int PERF_SEL : 8;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

union TCA_PERFCOUNTER0_SELECT__CI__VI {
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

union TCC_PERFCOUNTER0_SELECT__CI__VI {
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

union TCP_PERFCOUNTER0_SELECT__CI__VI {
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
    unsigned int PERF_SEL1__CI__VI : 8;
    unsigned int : 2;
    unsigned int CNTR_MODE__CI__VI : 4;
    unsigned int PERF_MODE1__CI__VI : 4;
    unsigned int PERF_MODE : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int PERF_MODE : 4;
    unsigned int PERF_MODE1__CI__VI : 4;
    unsigned int CNTR_MODE__CI__VI : 4;
    unsigned int : 2;
    unsigned int PERF_SEL1__CI__VI : 8;
    unsigned int : 2;
    unsigned int PERF_SEL : 8;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};
// include gfxip/gfx8/si_ci_vi_merged_typedef.h
typedef union COMPUTE_PERFCOUNT_ENABLE__CI__VI regCOMPUTE_PERFCOUNT_ENABLE__CI__VI;
typedef union CPC_PERFCOUNTER0_SELECT__CI__VI regCPC_PERFCOUNTER0_SELECT__CI__VI;
typedef union CPF_PERFCOUNTER0_SELECT__CI__VI regCPF_PERFCOUNTER0_SELECT__CI__VI;
typedef union CP_COHER_BASE regCP_COHER_BASE;
typedef union CP_COHER_BASE_HI__CI__VI regCP_COHER_BASE_HI__CI__VI;
typedef union CP_COHER_SIZE regCP_COHER_SIZE;
typedef union CP_COHER_SIZE_HI__CI__VI regCP_COHER_SIZE_HI__CI__VI;
typedef union CP_PERFMON_CNTL regCP_PERFMON_CNTL;
typedef union GDS_PERFCOUNTER0_SELECT regGDS_PERFCOUNTER0_SELECT;
typedef union GRBM_GFX_INDEX regGRBM_GFX_INDEX;
typedef union GRBM_PERFCOUNTER0_SELECT regGRBM_PERFCOUNTER0_SELECT;
typedef union GRBM_SE0_PERFCOUNTER_SELECT regGRBM_SE0_PERFCOUNTER_SELECT;
typedef union MC_SEQ_PERF_CNTL_1__SI__CI regMC_SEQ_PERF_CNTL_1__SI__CI;
typedef union SPI_PERFCOUNTER0_SELECT regSPI_PERFCOUNTER0_SELECT;
typedef union SQ_PERFCOUNTER0_SELECT__CI__VI regSQ_PERFCOUNTER0_SELECT__CI__VI;
typedef union SQ_PERFCOUNTER_CTRL regSQ_PERFCOUNTER_CTRL;
typedef union SQ_PERFCOUNTER_MASK__CI__VI regSQ_PERFCOUNTER_MASK__CI__VI;
typedef union SQ_THREAD_TRACE_BASE regSQ_THREAD_TRACE_BASE;
typedef union SQ_THREAD_TRACE_CTRL regSQ_THREAD_TRACE_CTRL;
typedef union SQ_THREAD_TRACE_MASK regSQ_THREAD_TRACE_MASK;
typedef union SQ_THREAD_TRACE_MODE regSQ_THREAD_TRACE_MODE;
typedef union SQ_THREAD_TRACE_PERF_MASK regSQ_THREAD_TRACE_PERF_MASK;
typedef union SQ_THREAD_TRACE_SIZE regSQ_THREAD_TRACE_SIZE;
typedef union SQ_THREAD_TRACE_TOKEN_MASK regSQ_THREAD_TRACE_TOKEN_MASK;
typedef union SQ_THREAD_TRACE_TOKEN_MASK2__VI regSQ_THREAD_TRACE_TOKEN_MASK2__VI;
typedef union SRBM_PERFCOUNTER0_SELECT regSRBM_PERFCOUNTER0_SELECT;
typedef union SRBM_PERFMON_CNTL regSRBM_PERFMON_CNTL;
typedef union SX_PERFCOUNTER0_SELECT regSX_PERFCOUNTER0_SELECT;
typedef union TA_PERFCOUNTER0_SELECT regTA_PERFCOUNTER0_SELECT;
typedef union TCA_PERFCOUNTER0_SELECT__CI__VI regTCA_PERFCOUNTER0_SELECT__CI__VI;
typedef union TCC_PERFCOUNTER0_SELECT__CI__VI regTCC_PERFCOUNTER0_SELECT__CI__VI;
typedef union TCP_PERFCOUNTER0_SELECT__CI__VI regTCP_PERFCOUNTER0_SELECT__CI__VI;
typedef union TD_PERFCOUNTER0_SELECT regTD_PERFCOUNTER0_SELECT;
// include gfxip/gfx8/si_ci_vi_merged_pm4_it_opcodes.h

enum IT_OpCodeType {
  IT_NOP = 0x10,
  IT_WAIT_REG_MEM = 0x3C,
  IT_INDIRECT_BUFFER = 0x3F,
  IT_COPY_DATA = 0x40,
  IT_EVENT_WRITE = 0x46,
  IT_SET_SH_REG = 0x76,
  IT_RELEASE_MEM__CI__VI = 0x49,
  IT_ACQUIRE_MEM__CI__VI = 0x58,
  IT_SET_UCONFIG_REG__CI__VI = 0x79,
};
#define PM4_TYPE_3 3
// include gfxip/gfx8/si_ci_vi_merged_pm4cmds.h
#define PM4_CMD(op, count) PM4_TYPE_3_HDR(op, count, ShaderGraphics, PredDisable)
// include gfxip/gfx8/si_pm4defs.h
#define PM4_PREDICATE_SHIFT 0
#define PM4_SHADERTYPE_SHIFT 1
#define PM4_OP_SHIFT 8
#define PM4_COUNT_SHIFT 16
#define PM4_TYPE_SHIFT 30

enum PM4ShaderType {
  ShaderGraphics = 0,  ///< Graphics shader,
  ShaderCompute = 1    ///< Compute shader,
};

enum PM4Predicate {
  PredDisable = 0,  ///< Predicate disabled,
};
#define PM4_TYPE_3_HDR(opCode, count, shaderType, predicate)                                       \
  ((unsigned int)(predicate << PM4_PREDICATE_SHIFT) | (shaderType << PM4_SHADERTYPE_SHIFT) |       \
   (PM4_TYPE_3 << PM4_TYPE_SHIFT) | ((count - 2) << PM4_COUNT_SHIFT) | (opCode << PM4_OP_SHIFT))

typedef union PM4_TYPE_3_HEADER {
  struct {
    unsigned int predicate : 1;   ///< predicated version of packet when set
    unsigned int shaderType : 1;  ///< 0: Graphics, 1: Compute Shader
    unsigned int reserved1 : 6;   ///< reserved
    unsigned int opcode : 8;      ///< IT opcode
    unsigned int count : 14;      ///< number of DWORDs - 1 in the information body.
    unsigned int type : 2;        ///< packet identifier. It should be 3 for type 3 packets
  };
  unsigned int u32All;
} PM4_TYPE_3_HEADER;

typedef struct _PM4CMDSETDATA {
  union {
    PM4_TYPE_3_HEADER header;  ///< header
    unsigned int ordinal1;
  };
  union {
    unsigned int regOffset;  ///< offset in DWords from the register base address
    unsigned int ordinal2;
  };
  // This is a variable length packet. So, based on size in header, the layout following this
  // looks as follows:
  // Data for SET_CONTEXT_REG
  // DW Offset into Patch table for SET_CONTEXT_REG_INDIRECT
  // unsigned int data0;
  // ...
  // unsigned int dataN;

} PM4CMDSETDATA, *PPM4CMDSETDATA;
#define WAIT_REG_MEM_SPACE_REGISTER 0
#define WAIT_REG_MEM_SPACE_MEMORY 1
#define WAIT_REG_MEM_FUNC_EQUAL 3
#define WAIT_REG_MEM_FUNC_NOT_EQUAL 4
#define WAIT_REG_MEM_ENGINE_ME 0

typedef struct _PM4CMDWAITREGMEM {
  union {
    PM4_TYPE_3_HEADER header;  ///< header
    unsigned int ordinal1;
  };
  union {
    struct {
      unsigned int function : 3;   ///< function. WAIT_REG_MEM_FUNC_XXXX
      unsigned int reserved1 : 1;  ///< reserved
      unsigned int
          memSpace : 2;  ///< memory space (0 = register, 1 = memory, 2=TC/L2, 3 = reserved)
      unsigned int operation : 2;        ///< reserved
      unsigned int engine : 1;           ///< 0 = ME, 1 = PFP
      unsigned int reserved3 : 15;       ///< reserved
      unsigned int atc__CI : 1;          ///< ATC steting for MC read transactions
      unsigned int cachePolicy__CI : 2;  ///< Reserved for future use of CACHE_POLICY
      unsigned int volatile__CI : 1;     ///< Reserved for future use of VOLATILE
      unsigned int reserved4 : 4;        ///< reserved
    };
    unsigned int ordinal2;
  };
  union {
    unsigned int pollAddressLo;  ///< lower portion of Address to poll or register offset
    unsigned int ordinal3;
  };
  union {
    unsigned int pollAddressHi;  ///< high portion of Address to poll, dont care for regs
    unsigned int ordinal4;
  };
  union {
    unsigned int reference;  ///< reference value
    unsigned int ordinal5;
  };
  union {
    unsigned int mask;  ///< mask for comparison
    unsigned int ordinal6;
  };
  union {
    unsigned int pollInterval;  ///< interval to wait when issuing new poll requests
    unsigned int ordinal7;
  };

} PM4CMDWAITREGMEM, *PPM4CMDWAITREGMEM;

typedef struct _PM4CMDEVENTWRITE {
  union {
    PM4_TYPE_3_HEADER header;  ///< header
    unsigned int ordinal1;
  };
  union {
    struct {
      unsigned int eventType : 6;     ///< event type written to VGT_EVENT_INITIATOR
      unsigned int reserved1 : 2;     ///< reserved
      unsigned int eventIndex : 4;    ///< event index
      unsigned int reserved2 : 8;     ///< reserved
      unsigned int invalidateL2 : 1;  ///< invalidate L2 cache
      unsigned int reserved3 : 11;    ///< reserved
    };
    unsigned int ordinal2;
  };

} PM4CMDEVENTWRITE, *PPM4CMDEVENTWRITE;
#define EVENT_WRITE_INDEX_VS_PS_PARTIAL_FLUSH 4
#define EVENT_WRITE_INDEX_CACHE_FLUSH_EVENT 7

typedef struct _PM4CMDRELEASEMEM {
  union {
    PM4_TYPE_3_HEADER header;  /// header
    unsigned int ordinal1;
  };

  union {
    struct {
      unsigned int eventType : 6;
      unsigned int reserved1 : 2;
      unsigned int eventIndex : 4;
      unsigned int l1Volatile : 1;
      unsigned int l2Volatile : 1;
      unsigned int reserved : 1;
      unsigned int l2WriteBack : 1;
      unsigned int l1Invalidate : 1;
      unsigned int l2Invlidate : 1;
      unsigned int reserved2 : 6;
      unsigned int atc : 1;
      unsigned int cachePolicy : 2;
      unsigned int volatile : 1;
      unsigned int reserved3 : 4;
    };
    unsigned int ordinal2;
  };

  union {
    struct {
      unsigned int reserved4 : 16;
      unsigned int dstSel : 2;
      unsigned int reserved5 : 6;
      unsigned int intSel : 2;
      unsigned int reserved6 : 3;
      unsigned int dataSel : 3;
    };
    unsigned int ordinal3;
  };

  union {
    struct {
      unsigned int reserved7 : 2;
      unsigned int addressLoDwordAligned : 30;
    };
    struct {
      unsigned int reserved8 : 3;
      unsigned int addressLoQwordAligned : 29;
    };
    unsigned int ordinal4;
  };

  union {
    unsigned int addrHi;
    unsigned int ordinal5;
  };

  union {
    unsigned int dataLo;
    struct {
      unsigned int offset : 16;
      unsigned int numDwords : 16;
    };
    unsigned int ordinal6;
  };

  union {
    unsigned int dataHi;
    unsigned int ordinal7;
  };
} PM4CMDRELEASEMEM, *PPM4CMDRELEASEMEM;

typedef struct _PM4CMDACQUIREMEM {
  union {
    PM4_TYPE_3_HEADER header;  ///< header
    unsigned int ordinal1;
  };
  union {
    struct {
      unsigned int coherCntl : 31;
      unsigned int engine : 1;
    };
    unsigned int ordinal2;
  };
  union {
    regCP_COHER_SIZE cpCoherSize;
    unsigned int ordinal3;
  };
  union {
    regCP_COHER_SIZE_HI__CI__VI cpCoherSizeHi;
    unsigned int ordinal4;
  };
  union {
    regCP_COHER_BASE cpCoherBase;
    unsigned int ordinal5;
  };
  union {
    regCP_COHER_BASE_HI__CI__VI cpCoherBaseHi;
    unsigned int ordinal6;
  };
  union {
    struct {
      unsigned int pollInterval : 16;
      unsigned int reserved : 16;
    };
    unsigned int ordinal7;
  };
} PM4CMDACQUIREMEM, *PPM4CMDACQUIREMEM;

typedef struct _PM4CMDINDIRECTBUFFER {
  union {
    PM4_TYPE_3_HEADER header;  ///< header
    unsigned int ordinal1;
  };
  union {
    unsigned int ibBaseLo;  ///< Indirect buffer base address, must be 4 byte aligned
    unsigned int ordinal2;
  };
  union {
    struct {
      unsigned int ibBaseHi : 16;  ///< Indirect buffer base address
      unsigned int reserved1 : 16;
    };
    unsigned int ordinal3;
  };
  union {
    union {
      struct {
        unsigned int ibSize : 20;    ///< Indirect buffer size
        unsigned int reserved1 : 4;  ///< reserved
        unsigned int vmid : 8;       ///< Virtual memory domain ID for command buffer
      } SI;

      struct {
        unsigned int ibSize : 20;  ///< Indirect buffer size
        unsigned int chain : 1;
        unsigned int offLoadPolling : 1;
        unsigned int volatile__CI : 1;
        unsigned int valid : 1;
        unsigned int vmid : 4;
        unsigned int cachePolicy : 2;
        unsigned int reserved1 : 1;
        unsigned int priv : 1;
      } CI;
    };
    unsigned int ordinal4;
  };
} PM4CMDINDIRECTBUFFER, *PPM4CMDINDIRECTBUFFER;
#define COPY_DATA_SEL_REG 0                   ///< Mem-mapped register
#define COPY_DATA_SEL_SRC_IMME_DATA 5         ///< Immediate data
#define COPY_DATA_SEL_SRC_SYS_PERF_COUNTER 4  ///< Privileged memory performance counter
#define COPY_DATA_SEL_DST_ASYNC_MEMORY 5      ///< Memory (async - direct)
#define COPY_DATA_SEL_DST_SYS_PERF_COUNTER 4  ///< Privileged memory performance counter
#define COPY_DATA_SEL_COUNT_1DW 0             ///< Copy 1 word (32 bits)
#define COPY_DATA_SRC_CACHE_POLICY_LRU 0
#define COPY_DATA_SRC_CACHE_POLICY_BYPASS 2
#define COPY_DATA_DST_CACHE_POLICY_LRU 0
#define COPY_DATA_DST_CACHE_POLICY_BYPASS 2
#define COPY_DATA_ENGINE_ME 0
#define COPY_DATA_WR_CONFIRM_NO_WAIT 0

typedef struct _PM4CMDCOPYDATA  // only supported on NI and later asics
{
  union {
    PM4_TYPE_3_HEADER header;  ///< header
    unsigned int ordinal1;
  };

  union {
    struct {
      unsigned int srcSel : 4;      ///< 0 = register, 1 = memory, 5 = immediate data, others are
                                    /// reserved for future use
      unsigned int reserved1 : 4;   ///< reserved
      unsigned int dstSel : 4;      ///< 0 = register, 1 = memory (sync - across GRBM), 5 = memory
                                    ///(async - direct), others are reserved for future use
      unsigned int srcAtc__CI : 1;  ///< ATC setting for read requests to the MC and TCL2
      unsigned int srcCachePolicy__CI : 2;  ///< Cache policy settings for read requests to the TCL2
      unsigned int srcVolatile__CI : 1;     ///< Volatile setting for read requests to the TCL2
      unsigned int countSel : 1;            ///< 0 = 32-bits (1 DW), 1 = 64-bits (2 DW)
      unsigned int reserved3 : 3;           ///< reserved
      unsigned int wrConfirm : 1;   ///< 0 = do not wait for write confirm, 1  wait for confirmation
                                    /// that the write has completed
      unsigned int reserved4 : 3;   ///< reserved
      unsigned int dstAtc__CI : 1;  ///< ATC setting for read requests to the MC and TCL2
      unsigned int dstCachePolicy__CI : 2;  ///< Cache policy settings for read requests to the TCL2
      unsigned int dstVolatile__CI : 1;     ///< Volatile setting for read requests to the TCL2
      unsigned int reserved5 : 2;           ///< reserved
      unsigned int engineSel : 2;           ///< 0 = ME, 1 = PFP, 2 = CE (SI only)
    };
    unsigned int ordinal2;
  };
  union {
    unsigned int
        srcAddressLo;  ///< low bits of source address, memory-mapped register, or immediate data
    unsigned int ordinal3;
  };
  union {
    unsigned int srcAddressHi;  ///< high bits of source address, or immediate data
    unsigned int ordinal4;
  };
  union {
    unsigned int dstAddressLo;  ///< low bits of dst address, or memory-mapped register
    unsigned int ordinal5;
  };
  union {
    unsigned int dstAddressHi;  ///< high dst address
    unsigned int ordinal6;
  };

} PM4CMDCOPYDATA, *PPM4CMDCOPYDATA;
#define PM4_CMD_SET_CONFIG_REG_DWORDS (sizeof(PM4CMDSETDATA) / sizeof(unsigned int))
#define PM4_CMD_SET_SH_REG_DWORDS (sizeof(PM4CMDSETDATA) / sizeof(unsigned int))
// include gfxip/gfx8/gfx8_block_info.h

enum CounterBlockId {
  CpfCounterBlockId,
  GrbmCounterBlockId,
  GrbmSeCounterBlockId,
  SpiCounterBlockId,
  SqCounterBlockId,
  SqEsCounterBlockId,
  SqGsCounterBlockId,
  SqVsCounterBlockId,
  SqPsCounterBlockId,
  SqLsCounterBlockId,
  SqHsCounterBlockId,
  SqCsCounterBlockId,
  SxCounterBlockId,
  TaCounterBlockId,
  TcaCounterBlockId,
  TccCounterBlockId,
  TdCounterBlockId,
  TcpCounterBlockId,
  GdsCounterBlockId,
  McCounterBlockId,
  SrbmCounterBlockId,
  CpcCounterBlockId,
};
static const uint32_t TaCounterBlockNumInstances    = 16;
static const uint32_t TdCounterBlockNumInstances    = 16;
static const uint32_t TcpCounterBlockNumInstances   = 16;
static const uint32_t TcaCounterBlockNumInstances   = 2;
static const uint32_t TccCounterBlockNumInstances   = 16;
static const uint32_t McCounterBlockNumInstances    = 8; // Fiji, 2 channels
static const uint32_t CpcCounterBlockNumCounters    = 2;
static const uint32_t CpfCounterBlockNumCounters    = 2;
static const uint32_t GdsCounterBlockNumCounters    = 4;
static const uint32_t GrbmCounterBlockNumCounters   = 2;
static const uint32_t GrbmSeCounterBlockNumCounters = 1;
static const uint32_t McCounterBlockNumCounters     = 4;
static const uint32_t SpiCounterBlockNumCounters    = 6;
static const uint32_t SqCounterBlockNumCounters     = 16;
static const uint32_t SrbmCounterBlockNumCounters   = 2;
static const uint32_t SxCounterBlockNumCounters     = 4;
static const uint32_t TaCounterBlockNumCounters     = 2;
static const uint32_t TcaCounterBlockNumCounters    = 4;
static const uint32_t TccCounterBlockNumCounters    = 4;
static const uint32_t TcpCounterBlockNumCounters    = 4;
static const uint32_t TdCounterBlockNumCounters     = 2;
static const uint32_t CpfCounterBlockMaxEvent       = 18;
static const uint32_t CpcCounterBlockMaxEvent       = 23;
static const uint32_t GrbmCounterBlockMaxEvent      = 33;
static const uint32_t GrbmSeCounterBlockMaxEvent    = 14;
static const uint32_t SrbmCounterBlockMaxEvent      = 27;
static const uint32_t SpiCounterBlockMaxEvent       = 196;
static const uint32_t SqCounterBlockMaxEvent        = 297; // Fiji
static const uint32_t TaCounterBlockMaxEvent        = 118;
static const uint32_t TdCounterBlockMaxEvent        = 54;
static const uint32_t TcpCounterBlockMaxEvent       = 179;
static const uint32_t TccCounterBlockMaxEvent       = 191;
static const uint32_t TcaCounterBlockMaxEvent       = 34;
static const uint32_t GdsCounterBlockMaxEvent       = 120;
static const uint32_t SxCounterBlockMaxEvent        = 32;
static const uint32_t McSeqCounterBlockMaxEvent     = 21;
// include gfxip/gfx8/gfx8_primitives.h

class gfx8_cntx_prim {
 public:
  const static uint32_t GFXIP_LEVEL = 8;
  const static uint32_t GRBM_GFX_INDEX_ADDR = mmGRBM_GFX_INDEX__CI__VI;
  const static uint32_t COMPUTE_PERFCOUNT_ENABLE_ADDR = mmCOMPUTE_PERFCOUNT_ENABLE__CI__VI;
  const static uint32_t RLC_PERFMON_CLK_CNTL_ADDR = mmRLC_PERFMON_CLK_CNTL__VI;
  const static uint32_t CP_PERFMON_CNTL_ADDR = mmCP_PERFMON_CNTL__CI__VI;
  const static uint32_t SRBM_PERFMON_CNTL_ADDR = mmSRBM_PERFMON_CNTL__VI;
  const static uint32_t MC_SELECT_ADDR = mmMC_SEQ_PERF_SEQ_CTL__SI__VI;
  const static uint32_t MC_SELECT1_ADDR = mmMC_SEQ_PERF_CNTL_1__SI__CI;
  const static uint32_t MC_CONFIG_ADDR = mmMC_CONFIG_MCD;

  const static uint32_t SQ_PERFCOUNTER_MASK_ADDR = mmSQ_PERFCOUNTER_MASK__CI__VI;
  const static uint32_t SQ_THREAD_TRACE_MASK_ADDR = mmSQ_THREAD_TRACE_MASK__VI;
  const static uint32_t SQ_THREAD_TRACE_PERF_MASK_ADDR = mmSQ_THREAD_TRACE_PERF_MASK__VI;
  const static uint32_t SQ_THREAD_TRACE_TOKEN_MASK_ADDR = mmSQ_THREAD_TRACE_TOKEN_MASK__VI;
  const static uint32_t SQ_THREAD_TRACE_TOKEN_MASK2_ADDR = mmSQ_THREAD_TRACE_TOKEN_MASK2__VI;
  const static uint32_t SQ_THREAD_TRACE_MODE_ADDR = mmSQ_THREAD_TRACE_MODE__VI;
  const static uint32_t SQ_THREAD_TRACE_BASE_ADDR = mmSQ_THREAD_TRACE_BASE__VI;
  const static uint32_t SQ_THREAD_TRACE_SIZE_ADDR = mmSQ_THREAD_TRACE_SIZE__VI;
  const static uint32_t SQ_THREAD_TRACE_CTRL_ADDR = mmSQ_THREAD_TRACE_CTRL__VI;
  const static uint32_t SQ_THREAD_TRACE_HIWATER_ADDR = mmSQ_THREAD_TRACE_HIWATER__VI;
  const static uint32_t SQ_THREAD_TRACE_HIWATER_VAL = 0x6;
  const static uint32_t SQ_THREAD_TRACE_STATUS_ADDR = mmSQ_THREAD_TRACE_STATUS__VI;
  const static uint32_t SQ_THREAD_TRACE_CNTR_ADDR = mmSQ_THREAD_TRACE_CNTR;
  const static uint32_t SQ_THREAD_TRACE_WPTR_ADDR = mmSQ_THREAD_TRACE_WPTR__VI;
  const static uint32_t SQ_THREAD_TRACE_STATUS_OFFSET =
      mmSQ_THREAD_TRACE_STATUS__VI - UCONFIG_SPACE_START__CI__VI;
  const static uint32_t TT_BUFF_ALIGN_SHIFT = 12;

  const static uint32_t COPY_DATA_SEL_REG_PRM = COPY_DATA_SEL_REG;
  const static uint32_t COPY_DATA_SEL_SRC_SYS_PERF_COUNTER_PRM = COPY_DATA_SEL_SRC_SYS_PERF_COUNTER;
  const static uint32_t COPY_DATA_SEL_COUNT_1DW_PRM = COPY_DATA_SEL_COUNT_1DW;

  static uint32_t Low32(const uint64_t& v) { return (v & 0xFFFFFFFFul); }

  // GRBM broadcasting mode
  static uint32_t grbm_broadcast_value() {
    regGRBM_GFX_INDEX grbm_gfx_index = {0};
    grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }

  // GRBM SE indexing
  static uint32_t grbm_inst_index_value(const uint32_t& instance_index) {
    regGRBM_GFX_INDEX grbm_gfx_index = {0};
    grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }

  // GRBM SE indexing
  static uint32_t grbm_se_index_value(const uint32_t& se_index) {
    regGRBM_GFX_INDEX grbm_gfx_index = {0};
    grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_INDEX = se_index;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }

  // GRBM SE/BlockInstance indexing
  static uint32_t grbm_inst_se_index_value(const uint32_t& instance_index,
                                           const uint32_t& se_index) {
    regGRBM_GFX_INDEX grbm_gfx_index = {0};
    grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
    grbm_gfx_index.bitfields.SE_INDEX = se_index;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }

  // GRBM SE/SH indexing
  static uint32_t grbm_se_sh_index_value(const uint32_t& se_index, const uint32_t& sh_index) {
    regGRBM_GFX_INDEX grbm_gfx_index = {0};
    grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_INDEX = se_index;
    grbm_gfx_index.bitfields.SH_INDEX = sh_index;
    return grbm_gfx_index.u32All;
  }

  // CP_PERFMON_CNTL value to reset counters
  static uint32_t cp_perfmon_cntl_reset_value() {
    regCP_PERFMON_CNTL cp_perfmon_cntl = {0};
    return cp_perfmon_cntl.u32All;
  }

  // CP_PERFMON_CNTL value to start counters
  static uint32_t cp_perfmon_cntl_start_value() {
    regCP_PERFMON_CNTL cp_perfmon_cntl = {0};
    cp_perfmon_cntl.bits.PERFMON_STATE = 1;
    return cp_perfmon_cntl.u32All;
  }

  // CP_PERFMON_CNTL value to stop/freeze counters
  static uint32_t cp_perfmon_cntl_stop_value() {
    regCP_PERFMON_CNTL cp_perfmon_cntl = {0};
    cp_perfmon_cntl.bits.PERFMON_STATE = 2;
    cp_perfmon_cntl.bits.PERFMON_SAMPLE_ENABLE = 1;
    return cp_perfmon_cntl.u32All;
  }

  // Compute Perfcount Enable register value to enable counting
  static uint32_t cp_perfcount_enable_value() {
    regCOMPUTE_PERFCOUNT_ENABLE__CI__VI cp_perfcount_enable = {0};
    cp_perfcount_enable.bits.PERFCOUNT_ENABLE = 1;
    return cp_perfcount_enable.u32All;
  }

  // SQ Block primitives

  // SQ Counter Select Register value
  static uint32_t sq_select_value(const counter_des_t& counter_des) {
    regSQ_PERFCOUNTER0_SELECT__CI__VI sq_cntr_sel = {0};
    sq_cntr_sel.bits.SIMD_MASK = 0xF;
    sq_cntr_sel.bits.SQC_BANK_MASK = 0xF;
    sq_cntr_sel.bits.SQC_CLIENT_MASK = 0xF;
    sq_cntr_sel.bits.PERF_SEL = counter_des.id;
    return sq_cntr_sel.u32All;
  }

  // SQ Counter Mask Register value
  static uint32_t sq_mask_value(const counter_des_t&) {
    regSQ_PERFCOUNTER_MASK__CI__VI sq_cntr_mask = {0};
    sq_cntr_mask.bits.SH0_MASK = 0xFFFF;
    sq_cntr_mask.bits.SH1_MASK = 0xFFFF;
    return sq_cntr_mask.u32All;
  }

  // SQ Counter Control Register value
  static uint32_t sq_control_value(const counter_des_t& counter_des) {
    const uint32_t block_id = counter_des.block_des.id;
    regSQ_PERFCOUNTER_CTRL sq_cntr_ctrl = {0};
    if (block_id == SqCounterBlockId) {
      sq_cntr_ctrl.bits.ES_EN = 0x1;
      sq_cntr_ctrl.bits.GS_EN = 0x1;
      sq_cntr_ctrl.bits.VS_EN = 0x1;
      sq_cntr_ctrl.bits.PS_EN = 0x1;
      sq_cntr_ctrl.bits.LS_EN = 0x1;
      sq_cntr_ctrl.bits.HS_EN = 0x1;
      sq_cntr_ctrl.bits.CS_EN = 0x1;
    } else if (block_id == SqEsCounterBlockId) {
      sq_cntr_ctrl.bits.ES_EN = 0x1;
    } else if (block_id == SqGsCounterBlockId) {
      sq_cntr_ctrl.bits.GS_EN = 0x1;
    } else if (block_id == SqVsCounterBlockId) {
      sq_cntr_ctrl.bits.VS_EN = 0x1;
    } else if (block_id == SqPsCounterBlockId) {
      sq_cntr_ctrl.bits.PS_EN = 0x1;
    } else if (block_id == SqLsCounterBlockId) {
      sq_cntr_ctrl.bits.LS_EN = 0x1;
    } else if (block_id == SqHsCounterBlockId) {
      sq_cntr_ctrl.bits.HS_EN = 0x1;
    } else if (block_id == SqCsCounterBlockId) {
      sq_cntr_ctrl.bits.CS_EN = 0x1;
    }
    return sq_cntr_ctrl.u32All;
  }

  // MC Block primitives

  // MC Channel value
  static uint32_t mc_channel_value(const counter_des_t& counter_des) {
    return counter_des.block_des.index & 1;
  }
  static uint32_t mc_channel_mask(const counter_des_t& counter_des) {
    return 1u << mc_channel_value(counter_des);
  }

  // MC Counter Select Register value
  static uint32_t mc_select_value(const counter_des_t& counter_des) {
    MC_SEQ_PERF_SEQ_CTL__SI__CI select = {0};
    const uint32_t channel = mc_channel_value(counter_des);
    const uint32_t event_id = counter_des.id;
    if (channel == 0) {
      switch (counter_des.index) {
        case 0:
          select.bits.SEL_A = event_id;
        case 1:
          select.bits.SEL_B = event_id;
        case 2:
          select.bits.SEL_CH0_C = event_id;
        case 3:
          select.bits.SEL_CH0_D = event_id;
      }
    } else {
      switch (counter_des.index) {
        case 0:
          select.bits.SEL_CH1_A = event_id;
        case 1:
          select.bits.SEL_CH1_B = event_id;
        case 2:
          select.bits.SEL_CH1_C = event_id;
        case 3:
          select.bits.SEL_CH1_D = event_id;
      }
    }
    return select.u32All;
  }

  static uint32_t mc_select1_value(const counter_des_t& counter_des) {
    regMC_SEQ_PERF_CNTL_1__SI__CI select = {0};
    const uint32_t channel = mc_channel_value(counter_des);
    const uint32_t event_id_msb = counter_des.id >> MC_SEQ_PERF_SEQ_CTL__SEL_B__SHIFT__SI__CI;
    if (channel == 0) {
      switch (counter_des.index) {
        case 0:
          select.bits.SEL_A_MSB = event_id_msb;
        case 1:
          select.bits.SEL_B_MSB = event_id_msb;
        case 2:
          select.bits.SEL_CH0_C_MSB = event_id_msb;
        case 3:
          select.bits.SEL_CH0_D_MSB = event_id_msb;
      }
    } else {
      switch (counter_des.index) {
        case 0:
          select.bits.SEL_CH1_A_MSB = event_id_msb;
        case 1:
          select.bits.SEL_CH1_B_MSB = event_id_msb;
        case 2:
          select.bits.SEL_CH1_C_MSB = event_id_msb;
        case 3:
          select.bits.SEL_CH1_D_MSB = event_id_msb;
      }
    }
    return select.u32All;
  }

  // MC Counter Config Register value
  static uint32_t mc_broadcast_value() {
    const uint32_t write_enable_mask = (1 << McCounterBlockNumInstances) - 1;
    return write_enable_mask;
  }
  static uint32_t mc_config_value(const counter_des_t& counter_des) {
    const uint32_t read_enable_mask = counter_des.block_des.index << MC_CONFIG_MCD__MC_RD_ENABLE__SHIFT;
    return read_enable_mask | mc_broadcast_value();
  }

  // Counter Select Register value templates
  template <typename Select> static uint32_t select_value(const counter_des_t& counter_des) {
    Select select = {0};
    select.bits.PERF_SEL = counter_des.id;
    return select.u32All;
  }
  template <typename Select> static uint32_t select_value_t2(const counter_des_t& counter_des) {
    Select select = {0};
    select.bits.PERFCOUNTER_SELECT = counter_des.id;
    return select.u32All;
  }

  // SRBM Registers values
  static uint32_t srbm_reset_value() {
    regSRBM_PERFMON_CNTL cntl = {0};
    return cntl.u32All;
  }
  static uint32_t srbm_start_value() {
    regSRBM_PERFMON_CNTL cntl = {0};
    cntl.bits.PERFMON_STATE = 1;
    return cntl.u32All;
  }
  static uint32_t srbm_stop_value() {
    regSRBM_PERFMON_CNTL cntl = {0};
    cntl.bits.PERFMON_STATE = 2;
    cntl.bits.PERFMON_SAMPLE_ENABLE = 1;
    return cntl.u32All;
  }

  // SQTT primitives

  // Enable Thread Trace for all VM Id's
  // Enable all of the SIMD's of the compute unit
  // Enable Compute Unit (CU) at index Zero to be used for fine-grained data
  // Enable Shader Array (SH) at index Zero to be used for fine-grained data
  //
  // @note: Not enabling REG_STALL_EN, SPI_STALL_EN and SQ_STALL_EN bits. They
  // are useful if we wish to program buffer throttling.
  //
  static uint32_t sqtt_mask_value(const uint32_t& targetCu, const uint32_t& vmIdMask) {
    regSQ_THREAD_TRACE_MASK mask = {0};
    mask.bits.SH_SEL = 0x0;
    mask.bits.SIMD_EN = 0xF;
    mask.bits.CU_SEL = targetCu;
    mask.bits.SQ_STALL_EN__CI__VI = 0x1;
    mask.bits.SPI_STALL_EN__CI__VI = 0x1;
    mask.bits.REG_STALL_EN__CI__VI = 0x1;
    mask.bits.VM_ID_MASK = vmIdMask;
    return mask.u32All;
  }

  // Mask of compute units to get thread trace data from
  static uint32_t sqtt_perf_mask_value() {
    regSQ_THREAD_TRACE_PERF_MASK perf_mask = {0};
    perf_mask.bits.SH0_MASK = 0xFFFF;
    perf_mask.bits.SH1_MASK = 0xFFFF;
    return perf_mask.u32All;
  }

  // Indicate the different TT messages/tokens that should be enabled/logged
  // Indicate the different TT tokens that specify register operations to be logged
  static uint32_t sqtt_token_mask_value() {
    regSQ_THREAD_TRACE_TOKEN_MASK token_mask = {0};
    token_mask.bits.REG_MASK = 0xFF;
    token_mask.bits.TOKEN_MASK = 0xFFFF;
    token_mask.bits.REG_DROP_ON_STALL__CI__VI = 0x1;
    return token_mask.u32All;
  }

  // Indicate the different TT tokens that specify instruction operations to be logged
  // Disabling specifically instruction operations updating Program Counter (PC).
  // @note: The field is defined in the spec incorrectly as a 16-bit value
  static uint32_t sqtt_token_mask2_value() {
    regSQ_THREAD_TRACE_TOKEN_MASK2__VI token_mask2 = {0};
    token_mask2.bits.INST_MASK = 0xFFFFFF7F;
    return token_mask2.u32All;
  }

  // Check if stalling is supported
  static bool sqtt_stalling_enabled(const uint32_t& mask_val, const uint32_t& token_mask_val) {
    regSQ_THREAD_TRACE_MASK mask = {0};
    mask.u32All = mask_val;
    regSQ_THREAD_TRACE_TOKEN_MASK token_mask = {0};
    token_mask.u32All = token_mask_val;
    return ((mask.bits.SQ_STALL_EN__CI__VI) || (mask.bits.SPI_STALL_EN__CI__VI) ||
            (mask.bits.REG_STALL_EN__CI__VI) || (token_mask.bits.REG_DROP_ON_STALL__CI__VI));
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
    regSQ_THREAD_TRACE_MODE mode = {0};
    mode.bits.WRAP = 0;
    mode.bits.CAPTURE_MODE = 0;
    mode.bits.MASK_CS = 1;
    mode.bits.AUTOFLUSH_EN = 1;
    mode.bits.MODE = SQ_THREAD_TRACE_MODE_OFF;
    return mode.u32All;
  }
  // Thread trace mode ON value
  static uint32_t sqtt_mode_on_value() {
    regSQ_THREAD_TRACE_MODE mode = {0};
    mode.u32All = sqtt_mode_off_value();
    mode.bits.MODE = SQ_THREAD_TRACE_MODE_ON;
    return mode.u32All;
  }

  // Base address of buffer to use for thread trace
  static uint32_t sqtt_base_value(const uint64_t& base_addr) {
    regSQ_THREAD_TRACE_BASE base = {0};
    base.bits.ADDR = Low32(base_addr >> TT_BUFF_ALIGN_SHIFT);
    return base.u32All;
  }

  // Indicates the size of buffer to use per Shader Engine instance.
  // The size is specified in terms of 4KB blocks
  static uint32_t sqtt_size_value(const uint32_t& size_val) {
    regSQ_THREAD_TRACE_SIZE size = {0};
    size.bits.SIZE = size_val >> TT_BUFF_ALIGN_SHIFT;
    return size.u32All;
  }
  static uint32_t sqtt_zero_size_value() { return 0; }

  // Thread trace ctrl register value
  static uint32_t sqtt_ctrl_value() {
    regSQ_THREAD_TRACE_CTRL ctrl = {0};
    ctrl.bits.RESET_BUFFER = 1;
    return ctrl.u32All;
  }
};

template <>
inline uint32_t gfx8_cntx_prim::select_value<regSX_PERFCOUNTER0_SELECT>(
    const counter_des_t& counter_des) {
  return select_value_t2<regSX_PERFCOUNTER0_SELECT>(counter_des);
}

template <>
inline uint32_t gfx8_cntx_prim::select_value<regGDS_PERFCOUNTER0_SELECT>(
    const counter_des_t& counter_des) {
  return select_value_t2<regGDS_PERFCOUNTER0_SELECT>(counter_des);
}
// include gfxip/gfx8/gfx8_block_table.h

static const CounterRegInfo SqCounterRegAddr[] = {
    {mmSQ_PERFCOUNTER0_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER0_LO__CI__VI, mmSQ_PERFCOUNTER0_HI__CI__VI},
    {mmSQ_PERFCOUNTER1_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER1_LO__CI__VI, mmSQ_PERFCOUNTER1_HI__CI__VI},
    {mmSQ_PERFCOUNTER2_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER2_LO__CI__VI, mmSQ_PERFCOUNTER2_HI__CI__VI},
    {mmSQ_PERFCOUNTER3_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER3_LO__CI__VI, mmSQ_PERFCOUNTER3_HI__CI__VI},
    {mmSQ_PERFCOUNTER4_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER4_LO__CI__VI, mmSQ_PERFCOUNTER4_HI__CI__VI},
    {mmSQ_PERFCOUNTER5_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER5_LO__CI__VI, mmSQ_PERFCOUNTER5_HI__CI__VI},
    {mmSQ_PERFCOUNTER6_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER6_LO__CI__VI, mmSQ_PERFCOUNTER6_HI__CI__VI},
    {mmSQ_PERFCOUNTER7_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER7_LO__CI__VI, mmSQ_PERFCOUNTER7_HI__CI__VI},
    {mmSQ_PERFCOUNTER8_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER8_LO__CI__VI, mmSQ_PERFCOUNTER8_HI__CI__VI},
    {mmSQ_PERFCOUNTER9_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER9_LO__CI__VI, mmSQ_PERFCOUNTER9_HI__CI__VI},
    {mmSQ_PERFCOUNTER10_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER10_LO__CI__VI, mmSQ_PERFCOUNTER10_HI__CI__VI},
    {mmSQ_PERFCOUNTER11_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER11_LO__CI__VI, mmSQ_PERFCOUNTER11_HI__CI__VI},
    {mmSQ_PERFCOUNTER12_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER12_LO__CI__VI, mmSQ_PERFCOUNTER12_HI__CI__VI},
    {mmSQ_PERFCOUNTER13_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER13_LO__CI__VI, mmSQ_PERFCOUNTER13_HI__CI__VI},
    {mmSQ_PERFCOUNTER14_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER14_LO__CI__VI, mmSQ_PERFCOUNTER14_HI__CI__VI},
    {mmSQ_PERFCOUNTER15_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER15_LO__CI__VI, mmSQ_PERFCOUNTER15_HI__CI__VI}};

static const CounterRegInfo CpfCounterRegAddr[] = {
    {mmCPF_PERFCOUNTER0_SELECT__CI__VI, 0, mmCPF_PERFCOUNTER0_LO__CI__VI, mmCPF_PERFCOUNTER0_HI__CI__VI},
    {mmCPF_PERFCOUNTER1_SELECT__CI__VI, 0, mmCPF_PERFCOUNTER1_LO__CI__VI, mmCPF_PERFCOUNTER1_HI__CI__VI}};

static const CounterRegInfo GrbmCounterRegAddr[] = {
    {mmGRBM_PERFCOUNTER0_SELECT__CI__VI, 0, mmGRBM_PERFCOUNTER0_LO__CI__VI, mmGRBM_PERFCOUNTER0_HI__CI__VI},
    {mmGRBM_PERFCOUNTER1_SELECT__CI__VI, 0, mmGRBM_PERFCOUNTER1_LO__CI__VI, mmGRBM_PERFCOUNTER1_HI__CI__VI}};

static const CounterRegInfo GrbmSeCounterRegAddr[] = {
    {mmGRBM_SE0_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE0_PERFCOUNTER_LO__CI__VI, mmGRBM_SE0_PERFCOUNTER_HI__CI__VI},
    {mmGRBM_SE1_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE1_PERFCOUNTER_LO__CI__VI, mmGRBM_SE1_PERFCOUNTER_HI__CI__VI},
    {mmGRBM_SE2_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE2_PERFCOUNTER_LO__CI__VI, mmGRBM_SE2_PERFCOUNTER_HI__CI__VI},
    {mmGRBM_SE3_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE3_PERFCOUNTER_LO__CI__VI, mmGRBM_SE3_PERFCOUNTER_HI__CI__VI}};

static const CounterRegInfo SpiCounterRegAddr[] = {
    {mmSPI_PERFCOUNTER0_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER0_LO__CI__VI, mmSPI_PERFCOUNTER0_HI__CI__VI},
    {mmSPI_PERFCOUNTER1_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER1_LO__CI__VI, mmSPI_PERFCOUNTER1_HI__CI__VI},
    {mmSPI_PERFCOUNTER2_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER2_LO__CI__VI, mmSPI_PERFCOUNTER2_HI__CI__VI},
    {mmSPI_PERFCOUNTER3_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER3_LO__CI__VI, mmSPI_PERFCOUNTER3_HI__CI__VI},
    {mmSPI_PERFCOUNTER4_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER4_LO__CI__VI, mmSPI_PERFCOUNTER4_HI__CI__VI},
    {mmSPI_PERFCOUNTER5_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER5_LO__CI__VI, mmSPI_PERFCOUNTER5_HI__CI__VI}};

static const CounterRegInfo TcaCounterRegAddr[] = {
    {mmTCA_PERFCOUNTER0_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER0_LO__CI__VI, mmTCA_PERFCOUNTER0_HI__CI__VI},
    {mmTCA_PERFCOUNTER1_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER1_LO__CI__VI, mmTCA_PERFCOUNTER1_HI__CI__VI},
    {mmTCA_PERFCOUNTER2_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER2_LO__CI__VI, mmTCA_PERFCOUNTER2_HI__CI__VI},
    {mmTCA_PERFCOUNTER3_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER3_LO__CI__VI, mmTCA_PERFCOUNTER3_HI__CI__VI}};

static const CounterRegInfo TccCounterRegAddr[] = {
    {mmTCC_PERFCOUNTER0_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER0_LO__CI__VI, mmTCC_PERFCOUNTER0_HI__CI__VI},
    {mmTCC_PERFCOUNTER1_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER1_LO__CI__VI, mmTCC_PERFCOUNTER1_HI__CI__VI},
    {mmTCC_PERFCOUNTER2_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER2_LO__CI__VI, mmTCC_PERFCOUNTER2_HI__CI__VI},
    {mmTCC_PERFCOUNTER3_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER3_LO__CI__VI, mmTCC_PERFCOUNTER3_HI__CI__VI}};

static const CounterRegInfo TcpCounterRegAddr[] = {
    {mmTCP_PERFCOUNTER0_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER0_LO__CI__VI, mmTCP_PERFCOUNTER0_HI__CI__VI},
    {mmTCP_PERFCOUNTER1_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER1_LO__CI__VI, mmTCP_PERFCOUNTER1_HI__CI__VI},
    {mmTCP_PERFCOUNTER2_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER2_LO__CI__VI, mmTCP_PERFCOUNTER2_HI__CI__VI},
    {mmTCP_PERFCOUNTER3_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER3_LO__CI__VI, mmTCP_PERFCOUNTER3_HI__CI__VI}};

static const CounterRegInfo SxCounterRegAddr[] = {
    {mmSX_PERFCOUNTER0_SELECT__CI__VI, 0, mmSX_PERFCOUNTER0_LO__CI__VI, mmSX_PERFCOUNTER0_HI__CI__VI},
    {mmSX_PERFCOUNTER1_SELECT__CI__VI, 0, mmSX_PERFCOUNTER1_LO__CI__VI, mmSX_PERFCOUNTER1_HI__CI__VI},
    {mmSX_PERFCOUNTER2_SELECT__CI__VI, 0, mmSX_PERFCOUNTER2_LO__CI__VI, mmSX_PERFCOUNTER2_HI__CI__VI},
    {mmSX_PERFCOUNTER3_SELECT__CI__VI, 0, mmSX_PERFCOUNTER3_LO__CI__VI, mmSX_PERFCOUNTER3_HI__CI__VI}};

static const CounterRegInfo TaCounterRegAddr[] = {
    {mmTA_PERFCOUNTER0_SELECT__CI__VI, 0, mmTA_PERFCOUNTER0_LO__CI__VI, mmTA_PERFCOUNTER0_HI__CI__VI},
    {mmTA_PERFCOUNTER1_SELECT__CI__VI, 0, mmTA_PERFCOUNTER1_LO__CI__VI, mmTA_PERFCOUNTER1_HI__CI__VI}};

static const CounterRegInfo TdCounterRegAddr[] = {
    {mmTD_PERFCOUNTER0_SELECT__CI__VI, 0, mmTD_PERFCOUNTER0_LO__CI__VI, mmTD_PERFCOUNTER0_HI__CI__VI},
    {mmTD_PERFCOUNTER1_SELECT__CI__VI, 0, mmTD_PERFCOUNTER1_LO__CI__VI, mmTD_PERFCOUNTER1_HI__CI__VI}};

static const CounterRegInfo GdsCounterRegAddr[] = {
    {mmGDS_PERFCOUNTER0_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER0_LO__CI__VI, mmGDS_PERFCOUNTER0_HI__CI__VI},
    {mmGDS_PERFCOUNTER1_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER1_LO__CI__VI, mmGDS_PERFCOUNTER1_HI__CI__VI},
    {mmGDS_PERFCOUNTER2_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER2_LO__CI__VI, mmGDS_PERFCOUNTER2_HI__CI__VI},
    {mmGDS_PERFCOUNTER3_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER3_LO__CI__VI, mmGDS_PERFCOUNTER3_HI__CI__VI}};

static const CounterRegInfo McSeqCounterRegAddr[] = {
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, mmMC_CONFIG_MCD, mmMC_SEQ_PERF_SEQ_CNT_A_I0__VI, mmMC_SEQ_PERF_SEQ_CNT_A_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, mmMC_CONFIG_MCD, mmMC_SEQ_PERF_SEQ_CNT_B_I0__VI, mmMC_SEQ_PERF_SEQ_CNT_B_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, mmMC_CONFIG_MCD, mmMC_SEQ_PERF_SEQ_CNT_C_I0__VI, mmMC_SEQ_PERF_SEQ_CNT_C_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, mmMC_CONFIG_MCD, mmMC_SEQ_PERF_SEQ_CNT_D_I0__VI, mmMC_SEQ_PERF_SEQ_CNT_D_I1__VI}};

static const CounterRegInfo SrbmCounterRegAddr[] = {
    {mmSRBM_PERFCOUNTER0_SELECT__VI, mmSRBM_PERFMON_CNTL__VI, mmSRBM_PERFCOUNTER0_LO__VI, mmSRBM_PERFCOUNTER0_HI__VI},
    {mmSRBM_PERFCOUNTER1_SELECT__VI, mmSRBM_PERFMON_CNTL__VI, mmSRBM_PERFCOUNTER1_LO__VI, mmSRBM_PERFCOUNTER1_HI__VI}};

static const CounterRegInfo CpcCounterRegAddr[] = {
    {mmCPC_PERFCOUNTER0_SELECT__CI__VI, 0, mmCPC_PERFCOUNTER0_LO__CI__VI, mmCPC_PERFCOUNTER0_HI__CI__VI},
    {mmCPC_PERFCOUNTER1_SELECT__CI__VI, 0, mmCPC_PERFCOUNTER1_LO__CI__VI, mmCPC_PERFCOUNTER1_HI__CI__VI}};
static const GpuBlockInfo CpcCounterBlockInfo = {"CPC", CpcCounterBlockId, 1, CpcCounterBlockMaxEvent, CpcCounterBlockNumCounters, CpcCounterRegAddr, gfx8_cntx_prim::select_value<regCPC_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr};
static const GpuBlockInfo CpfCounterBlockInfo = {"CPF", CpfCounterBlockId, 1, CpfCounterBlockMaxEvent, CpfCounterBlockNumCounters, CpfCounterRegAddr, gfx8_cntx_prim::select_value<regCPF_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr};
static const GpuBlockInfo GrbmCounterBlockInfo = {"GRBM", GrbmCounterBlockId, 1, GrbmCounterBlockMaxEvent, GrbmCounterBlockNumCounters, GrbmCounterRegAddr, gfx8_cntx_prim::select_value<regGRBM_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
static const GpuBlockInfo GrbmSeCounterBlockInfo = {"GRBMSE", GrbmSeCounterBlockId, 1, GrbmSeCounterBlockMaxEvent, GrbmSeCounterBlockNumCounters, GrbmSeCounterRegAddr, gfx8_cntx_prim::select_value<regGRBM_SE0_PERFCOUNTER_SELECT>, CounterBlockDfltAttr};
static const GpuBlockInfo SpiCounterBlockInfo = {"SPI", SpiCounterBlockId, 1, SpiCounterBlockMaxEvent, SpiCounterBlockNumCounters, SpiCounterRegAddr, gfx8_cntx_prim::select_value<regSPI_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
static const GpuBlockInfo SqCounterBlockInfo = {"SQ", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqCsCounterBlockInfo = {"SQ_CS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SxCounterBlockInfo = {"SX", SxCounterBlockId, 1, SxCounterBlockMaxEvent, SxCounterBlockNumCounters, SxCounterRegAddr, gfx8_cntx_prim::select_value<regSX_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
static const GpuBlockInfo TaCounterBlockInfo = {"TA", TaCounterBlockId, TaCounterBlockNumInstances, TaCounterBlockMaxEvent, TaCounterBlockNumCounters, TaCounterRegAddr, gfx8_cntx_prim::select_value<regTA_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
static const GpuBlockInfo TcaCounterBlockInfo = {"TCA", TcaCounterBlockId, TcaCounterBlockNumInstances, TcaCounterBlockMaxEvent, TcaCounterBlockNumCounters, TcaCounterRegAddr, gfx8_cntx_prim::select_value<regTCA_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr};
static const GpuBlockInfo TccCounterBlockInfo = {"TCC", TccCounterBlockId, TccCounterBlockNumInstances, TccCounterBlockMaxEvent, TccCounterBlockNumCounters, TccCounterRegAddr, gfx8_cntx_prim::select_value<regTCC_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr};
static const GpuBlockInfo TdCounterBlockInfo = {"TD", TdCounterBlockId, TdCounterBlockNumInstances, TdCounterBlockMaxEvent, TdCounterBlockNumCounters, TdCounterRegAddr, gfx8_cntx_prim::select_value<regTD_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
static const GpuBlockInfo TcpCounterBlockInfo = {"TCP", TcpCounterBlockId, TcpCounterBlockNumInstances, TcpCounterBlockMaxEvent, TcpCounterBlockNumCounters, TcpCounterRegAddr, gfx8_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockSeAttr};
static const GpuBlockInfo GdsCounterBlockInfo = {"GDS", GdsCounterBlockId, 1, GdsCounterBlockMaxEvent, GdsCounterBlockNumCounters, GdsCounterRegAddr, gfx8_cntx_prim::select_value<regGDS_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
static const GpuBlockInfo SrbmCounterBlockInfo = {"SRBM", SrbmCounterBlockId, 1, SrbmCounterBlockMaxEvent, SrbmCounterBlockNumCounters, SrbmCounterRegAddr, gfx8_cntx_prim::select_value<regSRBM_PERFCOUNTER0_SELECT>, CounterBlockSrbmAttr};
static const GpuBlockInfo McSeqCounterBlockInfo = {"MC_SEQ", McCounterBlockId, McCounterBlockNumInstances, McSeqCounterBlockMaxEvent, McCounterBlockNumCounters, McSeqCounterRegAddr, gfx8_cntx_prim::mc_select_value, CounterBlockMcAttr};
#endif  // _DEF_GFX8_DEF_H_
