#ifndef _GFX8_PRIMITIVES_H_
#define _GFX8_PRIMITIVES_H_

#include <stdint.h>

class gfx8_cntx_prim {
 public:
  const static uint32_t GFXIP_LEVEL = 8;
  const static uint32_t GRBM_GFX_INDEX_ADDR = mmGRBM_GFX_INDEX__CI__VI;
  const static uint32_t COMPUTE_PERFCOUNT_ENABLE_ADDR = mmCOMPUTE_PERFCOUNT_ENABLE__CI__VI;
  const static uint32_t RLC_PERFMON_CLK_CNTL_ADDR = mmRLC_PERFMON_CLK_CNTL__VI;
  const static uint32_t CP_PERFMON_CNTL_ADDR = mmCP_PERFMON_CNTL__CI__VI;
  const static uint32_t MC_SELECT1_ADDR = mmMC_SEQ_PERF_CNTL_1__SI__CI;

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
  static uint32_t mc_config_value(const counter_des_t& counter_des) {
    const uint32_t read_enable_mask = counter_des.block_des.index << MC_CONFIG_MCD__MC_RD_ENABLE__SHIFT;
    const uint32_t write_enable_mask = (1 << McCounterBlockNumInstances) - 1;
    return read_enable_mask | write_enable_mask;
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

#endif  // _GFX8_PRIMITIVES_H_
