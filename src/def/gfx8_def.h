#ifndef _DEF_GFX8_DEF_H_
#define _DEF_GFX8_DEF_H_

// include gfxip/gfx8/si_ci_vi_merged_pm4cmds.h
#define PM4_CMD(op, count) PM4_TYPE_3_HDR(op, count, ShaderGraphics, PredDisable)
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
// include gfxip/gfx8/si_ci_vi_merged_typedef.h
typedef union CB_PERFCOUNTER0_SELECT__CI__VI regCB_PERFCOUNTER0_SELECT__CI__VI;
typedef union COMPUTE_PERFCOUNT_ENABLE__CI__VI regCOMPUTE_PERFCOUNT_ENABLE__CI__VI;
typedef union CPC_PERFCOUNTER0_SELECT__CI__VI regCPC_PERFCOUNTER0_SELECT__CI__VI;
typedef union CPF_PERFCOUNTER0_SELECT__CI__VI regCPF_PERFCOUNTER0_SELECT__CI__VI;
typedef union CPG_PERFCOUNTER0_SELECT__CI__VI regCPG_PERFCOUNTER0_SELECT__CI__VI;
typedef union CP_COHER_BASE regCP_COHER_BASE;
typedef union CP_COHER_BASE_HI__CI__VI regCP_COHER_BASE_HI__CI__VI;
typedef union CP_COHER_SIZE regCP_COHER_SIZE;
typedef union CP_COHER_SIZE_HI__CI__VI regCP_COHER_SIZE_HI__CI__VI;
typedef union CP_PERFMON_CNTL regCP_PERFMON_CNTL;
typedef union DB_PERFCOUNTER0_SELECT regDB_PERFCOUNTER0_SELECT;
typedef union GDS_PERFCOUNTER0_SELECT regGDS_PERFCOUNTER0_SELECT;
typedef union GRBM_GFX_INDEX regGRBM_GFX_INDEX;
typedef union GRBM_PERFCOUNTER0_SELECT regGRBM_PERFCOUNTER0_SELECT;
typedef union GRBM_SE0_PERFCOUNTER_SELECT regGRBM_SE0_PERFCOUNTER_SELECT;
typedef union IA_PERFCOUNTER0_SELECT__CI__VI regIA_PERFCOUNTER0_SELECT__CI__VI;
typedef union PA_SC_PERFCOUNTER0_SELECT regPA_SC_PERFCOUNTER0_SELECT;
typedef union PA_SU_PERFCOUNTER0_SELECT regPA_SU_PERFCOUNTER0_SELECT;
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
typedef union SX_PERFCOUNTER0_SELECT regSX_PERFCOUNTER0_SELECT;
typedef union TA_PERFCOUNTER0_SELECT regTA_PERFCOUNTER0_SELECT;
typedef union TCA_PERFCOUNTER0_SELECT__CI__VI regTCA_PERFCOUNTER0_SELECT__CI__VI;
typedef union TCC_PERFCOUNTER0_SELECT__CI__VI regTCC_PERFCOUNTER0_SELECT__CI__VI;
typedef union TCP_PERFCOUNTER0_SELECT__CI__VI regTCP_PERFCOUNTER0_SELECT__CI__VI;
typedef union TD_PERFCOUNTER0_SELECT regTD_PERFCOUNTER0_SELECT;
typedef union VGT_PERFCOUNTER0_SELECT__CI__VI regVGT_PERFCOUNTER0_SELECT__CI__VI;
typedef union WD_PERFCOUNTER0_SELECT__CI__VI regWD_PERFCOUNTER0_SELECT__CI__VI;
// include gfxip/gfx8/si_ci_vi_merged_registers.h

union CB_PERFCOUNTER0_SELECT__CI__VI {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 9;
    unsigned int : 1;
    unsigned int PERF_SEL1 : 9;
    unsigned int : 1;
    unsigned int CNTR_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int PERF_MODE : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int PERF_MODE : 4;
    unsigned int PERF_MODE1 : 4;
    unsigned int CNTR_MODE : 4;
    unsigned int : 1;
    unsigned int PERF_SEL1 : 9;
    unsigned int : 1;
    unsigned int PERF_SEL : 9;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};

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

union CPG_PERFCOUNTER0_SELECT__CI__VI {
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

union DB_PERFCOUNTER0_SELECT {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 10;
    unsigned int PERF_SEL1__CI__VI : 10;
    unsigned int CNTR_MODE__CI__VI : 4;
    unsigned int PERF_MODE1__CI__VI : 4;
    unsigned int PERF_MODE : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int PERF_MODE : 4;
    unsigned int PERF_MODE1__CI__VI : 4;
    unsigned int CNTR_MODE__CI__VI : 4;
    unsigned int PERF_SEL1__CI__VI : 10;
    unsigned int PERF_SEL : 10;
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

union IA_PERFCOUNTER0_SELECT__CI__VI {
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

union PA_SC_PERFCOUNTER0_SELECT {
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

union PA_SU_PERFCOUNTER0_SELECT {
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

union VGT_PERFCOUNTER0_SELECT__CI__VI {
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

union WD_PERFCOUNTER0_SELECT__CI__VI {
  struct {
#if defined(LITTLEENDIAN_CPU)
    unsigned int PERF_SEL : 8;
    unsigned int : 20;
    unsigned int PERF_MODE : 4;
#elif defined(BIGENDIAN_CPU)
    unsigned int PERF_MODE : 4;
    unsigned int : 20;
    unsigned int PERF_SEL : 8;
#endif
  } bitfields, bits;
  unsigned int u32All;
  signed int i32All;
  float f32All;
};
// include gfxip/gfx8/si_ci_vi_merged_enum.h

enum SQ_THREAD_TRACE_MODE_SEL {
  SQ_THREAD_TRACE_MODE_OFF = 0x00000000,
  SQ_THREAD_TRACE_MODE_ON = 0x00000001,
};

enum VGT_EVENT_TYPE {
  CS_PARTIAL_FLUSH = 0x00000007,
};
#define PERSISTENT_SPACE_START 0x00002c00
#define UCONFIG_SPACE_START__CI__VI 0x0000c000
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
#define COPY_DATA_SEL_SRC_SYS_PERF_COUNTER 4  ///< Privileged memory performance counter
#define COPY_DATA_SEL_DST_ASYNC_MEMORY 5      ///< Memory (async - direct)
#define COPY_DATA_SEL_COUNT_1DW 0             ///< Copy 1 word (32 bits)
#define COPY_DATA_SRC_CACHE_POLICY_BYPASS 2
#define COPY_DATA_DST_CACHE_POLICY_BYPASS 2
#define COPY_DATA_ENGINE_ME 0

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
// include gfxip/gfx8/si_ci_vi_merged_mask.h
#define CP_COHER_CNTL__SH_ICACHE_ACTION_ENA_MASK 0x20000000L
#define CP_COHER_CNTL__SH_KCACHE_ACTION_ENA_MASK 0x08000000L
#define CP_COHER_CNTL__TCL1_ACTION_ENA_MASK 0x00400000L
#define CP_COHER_CNTL__TC_ACTION_ENA_MASK 0x00800000L
#define CP_COHER_CNTL__TC_WB_ACTION_ENA_MASK__CI__VI 0x00040000L
#define CP_COHER_SIZE_HI__COHER_SIZE_HI_256B_MASK__CI__VI 0x000000ffL
#define CP_COHER_SIZE__COHER_SIZE_256B_MASK 0xffffffffL
// include gfxip/gfx8/si_ci_vi_merged_offset.h
#define mmCB_PERFCOUNTER0_HI__CI__VI 0xD407
#define mmCB_PERFCOUNTER0_LO__CI__VI 0xD406
#define mmCB_PERFCOUNTER0_SELECT__CI__VI 0xDC01
#define mmCB_PERFCOUNTER1_HI__CI__VI 0xD409
#define mmCB_PERFCOUNTER1_LO__CI__VI 0xD408
#define mmCB_PERFCOUNTER1_SELECT__CI__VI 0xDC03
#define mmCB_PERFCOUNTER2_HI__CI__VI 0xD40B
#define mmCB_PERFCOUNTER2_LO__CI__VI 0xD40A
#define mmCB_PERFCOUNTER2_SELECT__CI__VI 0xDC04
#define mmCB_PERFCOUNTER3_HI__CI__VI 0xD40D
#define mmCB_PERFCOUNTER3_LO__CI__VI 0xD40C
#define mmCB_PERFCOUNTER3_SELECT__CI__VI 0xDC05
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
#define mmCPG_PERFCOUNTER0_HI__CI__VI 0xD003
#define mmCPG_PERFCOUNTER0_LO__CI__VI 0xD002
#define mmCPG_PERFCOUNTER0_SELECT__CI__VI 0xD802
#define mmCPG_PERFCOUNTER1_HI__CI__VI 0xD001
#define mmCPG_PERFCOUNTER1_LO__CI__VI 0xD000
#define mmCPG_PERFCOUNTER1_SELECT__CI__VI 0xD800
#define mmCP_PERFMON_CNTL__CI__VI 0xD808
#define mmDB_PERFCOUNTER0_HI__CI__VI 0xD441
#define mmDB_PERFCOUNTER0_LO__CI__VI 0xD440
#define mmDB_PERFCOUNTER0_SELECT__CI__VI 0xDC40
#define mmDB_PERFCOUNTER1_HI__CI__VI 0xD443
#define mmDB_PERFCOUNTER1_LO__CI__VI 0xD442
#define mmDB_PERFCOUNTER1_SELECT__CI__VI 0xDC42
#define mmDB_PERFCOUNTER2_HI__CI__VI 0xD445
#define mmDB_PERFCOUNTER2_LO__CI__VI 0xD444
#define mmDB_PERFCOUNTER2_SELECT__CI__VI 0xDC44
#define mmDB_PERFCOUNTER3_HI__CI__VI 0xD447
#define mmDB_PERFCOUNTER3_LO__CI__VI 0xD446
#define mmDB_PERFCOUNTER3_SELECT__CI__VI 0xDC46
#define mmDRM_PERFCOUNTER1_HI 0x156E
#define mmDRM_PERFCOUNTER1_LO 0x156D
#define mmDRM_PERFCOUNTER1_SELECT 0x156B
#define mmDRM_PERFCOUNTER2_HI 0x1570
#define mmDRM_PERFCOUNTER2_LO 0x156F
#define mmDRM_PERFCOUNTER2_SELECT 0x156C
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
#define mmIA_PERFCOUNTER0_HI__CI__VI 0xD089
#define mmIA_PERFCOUNTER0_LO__CI__VI 0xD088
#define mmIA_PERFCOUNTER0_SELECT__CI__VI 0xD884
#define mmIA_PERFCOUNTER1_HI__CI__VI 0xD08B
#define mmIA_PERFCOUNTER1_LO__CI__VI 0xD08A
#define mmIA_PERFCOUNTER1_SELECT__CI__VI 0xD885
#define mmIA_PERFCOUNTER2_HI__CI__VI 0xD08D
#define mmIA_PERFCOUNTER2_LO__CI__VI 0xD08C
#define mmIA_PERFCOUNTER2_SELECT__CI__VI 0xD886
#define mmIA_PERFCOUNTER3_HI__CI__VI 0xD08F
#define mmIA_PERFCOUNTER3_LO__CI__VI 0xD08E
#define mmIA_PERFCOUNTER3_SELECT__CI__VI 0xD887
#define mmMC_SEQ_PERF_SEQ_CNT_A_I0__VI 0x0A79
#define mmMC_SEQ_PERF_SEQ_CNT_A_I1__VI 0x0A7A
#define mmMC_SEQ_PERF_SEQ_CNT_B_I0__VI 0x0A7B
#define mmMC_SEQ_PERF_SEQ_CNT_B_I1__VI 0x0A7C
#define mmMC_SEQ_PERF_SEQ_CNT_C_I0__VI 0x0AD9
#define mmMC_SEQ_PERF_SEQ_CNT_C_I1__VI 0x0ADA
#define mmMC_SEQ_PERF_SEQ_CNT_D_I0__VI 0x0ADB
#define mmMC_SEQ_PERF_SEQ_CNT_D_I1__VI 0x0ADC
#define mmMC_SEQ_PERF_SEQ_CTL__SI__VI 0x0A78
#define mmPA_SC_PERFCOUNTER0_HI__CI__VI 0xD141
#define mmPA_SC_PERFCOUNTER0_LO__CI__VI 0xD140
#define mmPA_SC_PERFCOUNTER0_SELECT__CI__VI 0xD940
#define mmPA_SC_PERFCOUNTER1_HI__CI__VI 0xD143
#define mmPA_SC_PERFCOUNTER1_LO__CI__VI 0xD142
#define mmPA_SC_PERFCOUNTER1_SELECT__CI__VI 0xD942
#define mmPA_SC_PERFCOUNTER2_HI__CI__VI 0xD145
#define mmPA_SC_PERFCOUNTER2_LO__CI__VI 0xD144
#define mmPA_SC_PERFCOUNTER2_SELECT__CI__VI 0xD943
#define mmPA_SC_PERFCOUNTER3_HI__CI__VI 0xD147
#define mmPA_SC_PERFCOUNTER3_LO__CI__VI 0xD146
#define mmPA_SC_PERFCOUNTER3_SELECT__CI__VI 0xD944
#define mmPA_SC_PERFCOUNTER4_HI__CI__VI 0xD149
#define mmPA_SC_PERFCOUNTER4_LO__CI__VI 0xD148
#define mmPA_SC_PERFCOUNTER4_SELECT__CI__VI 0xD945
#define mmPA_SC_PERFCOUNTER5_HI__CI__VI 0xD14B
#define mmPA_SC_PERFCOUNTER5_LO__CI__VI 0xD14A
#define mmPA_SC_PERFCOUNTER5_SELECT__CI__VI 0xD946
#define mmPA_SC_PERFCOUNTER6_HI__CI__VI 0xD14D
#define mmPA_SC_PERFCOUNTER6_LO__CI__VI 0xD14C
#define mmPA_SC_PERFCOUNTER6_SELECT__CI__VI 0xD947
#define mmPA_SC_PERFCOUNTER7_HI__CI__VI 0xD14F
#define mmPA_SC_PERFCOUNTER7_LO__CI__VI 0xD14E
#define mmPA_SC_PERFCOUNTER7_SELECT__CI__VI 0xD948
#define mmPA_SU_PERFCOUNTER0_HI__CI__VI 0xD101
#define mmPA_SU_PERFCOUNTER0_LO__CI__VI 0xD100
#define mmPA_SU_PERFCOUNTER0_SELECT__CI__VI 0xD900
#define mmPA_SU_PERFCOUNTER1_HI__CI__VI 0xD103
#define mmPA_SU_PERFCOUNTER1_LO__CI__VI 0xD102
#define mmPA_SU_PERFCOUNTER1_SELECT__CI__VI 0xD902
#define mmPA_SU_PERFCOUNTER2_HI__CI__VI 0xD105
#define mmPA_SU_PERFCOUNTER2_LO__CI__VI 0xD104
#define mmPA_SU_PERFCOUNTER2_SELECT__CI__VI 0xD904
#define mmPA_SU_PERFCOUNTER3_HI__CI__VI 0xD107
#define mmPA_SU_PERFCOUNTER3_LO__CI__VI 0xD106
#define mmPA_SU_PERFCOUNTER3_SELECT__CI__VI 0xD905
#define mmRLC_PERFCOUNTER0_HI__CI__VI 0xD481
#define mmRLC_PERFCOUNTER0_LO__CI__VI 0xD480
#define mmRLC_PERFCOUNTER0_SELECT__CI__VI 0xDCC1
#define mmRLC_PERFCOUNTER1_HI__CI__VI 0xD483
#define mmRLC_PERFCOUNTER1_LO__CI__VI 0xD482
#define mmRLC_PERFCOUNTER1_SELECT__CI__VI 0xDCC2
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
#define mmVGT_PERFCOUNTER0_HI__CI__VI 0xD091
#define mmVGT_PERFCOUNTER0_LO__CI__VI 0xD090
#define mmVGT_PERFCOUNTER0_SELECT__CI__VI 0xD88C
#define mmVGT_PERFCOUNTER1_HI__CI__VI 0xD093
#define mmVGT_PERFCOUNTER1_LO__CI__VI 0xD092
#define mmVGT_PERFCOUNTER1_SELECT__CI__VI 0xD88D
#define mmVGT_PERFCOUNTER2_HI__CI__VI 0xD095
#define mmVGT_PERFCOUNTER2_LO__CI__VI 0xD094
#define mmVGT_PERFCOUNTER2_SELECT__CI__VI 0xD88E
#define mmVGT_PERFCOUNTER3_HI__CI__VI 0xD097
#define mmVGT_PERFCOUNTER3_LO__CI__VI 0xD096
#define mmVGT_PERFCOUNTER3_SELECT__CI__VI 0xD88F
#define mmWD_PERFCOUNTER0_HI__CI__VI 0xD081
#define mmWD_PERFCOUNTER0_LO__CI__VI 0xD080
#define mmWD_PERFCOUNTER0_SELECT__CI__VI 0xD880
#define mmWD_PERFCOUNTER1_HI__CI__VI 0xD083
#define mmWD_PERFCOUNTER1_LO__CI__VI 0xD082
#define mmWD_PERFCOUNTER1_SELECT__CI__VI 0xD881
#define mmWD_PERFCOUNTER2_HI__CI__VI 0xD085
#define mmWD_PERFCOUNTER2_LO__CI__VI 0xD084
#define mmWD_PERFCOUNTER2_SELECT__CI__VI 0xD882
#define mmWD_PERFCOUNTER3_HI__CI__VI 0xD087
#define mmWD_PERFCOUNTER3_LO__CI__VI 0xD086
#define mmWD_PERFCOUNTER3_SELECT__CI__VI 0xD883
#define mmIH_PERFCOUNTER0_RESULT__VI 0x0E3A
#define mmIH_PERFCOUNTER1_RESULT__VI 0x0E3B
#define mmIH_PERFMON_CNTL__VI 0x0E39
#define mmRLC_PERFMON_CLK_CNTL__VI 0xDCBF
#define mmSDMA0_PERFCOUNTER0_RESULT__VI 0x9001
#define mmSDMA0_PERFCOUNTER1_RESULT__VI 0x9002
#define mmSDMA0_PERFMON_CNTL__VI 0x9000
#define mmSDMA1_PERFCOUNTER0_RESULT__VI 0x9011
#define mmSDMA1_PERFCOUNTER1_RESULT__VI 0x9012
#define mmSDMA1_PERFMON_CNTL__VI 0x9010
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

#include "def/gpu_block_info.h"
#include "def/gfx8_block_info.h"
#include "def/gfx8_primitives.h"
#include "def/gfx8_block_table.h"
#endif  // _DEF_GFX8_DEF_H_
