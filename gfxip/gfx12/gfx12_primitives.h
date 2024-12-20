// Copyright (c) 2024 Advanced Micro Devices, Inc. All rights reserved.

#ifndef _GFX12_PRIMITIVES_H_
#define _GFX12_PRIMITIVES_H_

#include <stdint.h>

namespace gfxip {
namespace gfx12 {

class gfx12_cntx_prim {
 public:
  static const uint32_t GFXIP_LEVEL = 12;
  static const uint32_t NUMBER_OF_BLOCKS = LastCounterBlockId + 1;
  static const uint32_t GRBM_GFX_INDEX_ADDR = mmGRBM_GFX_INDEX;
  static const uint32_t COMPUTE_PERFCOUNT_ENABLE_ADDR = mmCOMPUTE_PERFCOUNT_ENABLE;
  static const uint32_t RLC_PERFMON_CLK_CNTL_ADDR = mmRLC_PERFMON_CNTL;  //mmRLC_PERFMON_CLK_CNTL;
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

  static const uint32_t COMPUTE_THREAD_TRACE_ENABLE_ADDR = mmCOMPUTE_THREAD_TRACE_ENABLE;

  static const uint32_t MC_PERFCOUNTER_RSLT_CNTL__ENABLE_ANY_MASK_PRM = 0x01000000L;
  static const uint32_t MC_PERFCOUNTER_RSLT_CNTL__CLEAR_ALL_MASK_PRM = 0x02000000L;

  static const uint32_t SPI_SQG_EVENT_CTL_ADDR = mmSPI_SQG_EVENT_CTL;
  static const uint32_t SQ_PERFCOUNTER_CTRL_ADDR = mmSQ_PERFCOUNTER_CTRL;
  static const uint32_t SQ_PERFCOUNTER_CTRL2_ADDR = mmSQ_PERFCOUNTER_CTRL2;
  static const uint32_t SQ_PERFCOUNTER_MASK_ADDR = 0xD9E1;
  static const uint32_t SQ_THREAD_TRACE_MASK_ADDR = mmSQ_THREAD_TRACE_MASK;
  static const uint32_t SQ_THREAD_TRACE_PERF_MASK_ADDR = 0;
  static const uint32_t SQ_THREAD_TRACE_TOKEN_MASK_ADDR = mmSQ_THREAD_TRACE_TOKEN_MASK;
  static const uint32_t SQ_THREAD_TRACE_TOKEN_MASK2_ADDR = 0;
  static const uint32_t SQ_THREAD_TRACE_MODE_ADDR = 0;
  static const uint32_t SQ_THREAD_TRACE_BUF0_BASE_LO_ADDR = mmSQ_THREAD_TRACE_BUF0_BASE_LO;
  static const uint32_t SQ_THREAD_TRACE_BUF0_BASE_HI_ADDR = mmSQ_THREAD_TRACE_BUF0_BASE_HI;
  static const uint32_t SQ_THREAD_TRACE_BUF0_SIZE_ADDR = mmSQ_THREAD_TRACE_BUF0_SIZE;
  static const uint32_t SQ_THREAD_TRACE_BASE_ADDR = 0;
  static const uint32_t SQ_THREAD_TRACE_BASE2_ADDR = 0;
  static const uint32_t SQ_THREAD_TRACE_SIZE_ADDR = 0;
  static const uint32_t SQ_THREAD_TRACE_CTRL_ADDR = mmSQ_THREAD_TRACE_CTRL;
  static const uint32_t SQ_THREAD_TRACE_HIWATER_ADDR = 0;
  static const uint32_t SQ_THREAD_TRACE_HIWATER_VAL = 0x6;
  static const uint32_t SQ_THREAD_TRACE_STATUS_ADDR = mmSQ_THREAD_TRACE_STATUS;
  static const uint32_t SQ_THREAD_TRACE_CNTR_ADDR = mmSQ_THREAD_TRACE_DROPPED_CNTR;
  static const uint32_t SQ_THREAD_TRACE_WPTR_ADDR = mmSQ_THREAD_TRACE_WPTR;
  static const uint32_t SQ_THREAD_TRACE_STATUS_OFFSET =
      mmSQ_THREAD_TRACE_STATUS - UCONFIG_SPACE_START;
  static const uint32_t TT_BUFF_ALIGN_SHIFT = 12;

  static const uint32_t SDMA_COUNTER_BLOCK_NUM_INSTANCES = SdmaCounterBlockMaxInstances;
  static const uint32_t UMC_COUNTER_BLOCK_NUM_INSTANCES = UmcCounterBlockMaxInstances;

  static const uint32_t RLC_SPM_PERFMON_CNTL__ADDR = mmRLC_SPM_PERFMON_CNTL;
  static const uint32_t RLC_SPM_MC_CNTL__ADDR = mmRLC_SPM_MC_CNTL;
  static const uint32_t RLC_SPM_PERFMON_RING_BASE_LO__ADDR = mmRLC_SPM_PERFMON_RING_BASE_LO;
  static const uint32_t RLC_SPM_PERFMON_RING_BASE_HI__ADDR = mmRLC_SPM_PERFMON_RING_BASE_HI;
  static const uint32_t RLC_SPM_PERFMON_RING_SIZE__ADDR = mmRLC_SPM_PERFMON_RING_SIZE;
  static const uint32_t RLC_SPM_PERFMON_SEGMENT_SIZE__ADDR = mmRLC_SPM_PERFMON_SEGMENT_SIZE;
  static const uint32_t RLC_SPM_PERFMON_SEGMENT_SIZE_CORE1__ADDR = 0;
  static const uint32_t RLC_SPM_GLOBAL_MUXSEL_ADDR__ADDR = mmRLC_SPM_GLOBAL_MUXSEL_ADDR;
  static const uint32_t RLC_SPM_GLOBAL_MUXSEL_DATA__ADDR = mmRLC_SPM_GLOBAL_MUXSEL_DATA;
  static const uint32_t RLC_SPM_SE_MUXSEL_ADDR__ADDR = mmRLC_SPM_SE_MUXSEL_ADDR;
  static const uint32_t RLC_SPM_SE_MUXSEL_DATA__ADDR = mmRLC_SPM_SE_MUXSEL_DATA;
  static const uint32_t RLC_SPM_COUNTERS_PER_LINE = 16;
  static const uint32_t RLC_SPM_TIMESTAMP_SIZE16 = 4;

  static const uint32_t SQ_THREAD_TRACE_USERDATA_0 = mmSQ_THREAD_TRACE_USERDATA_0;
  static const uint32_t SQ_THREAD_TRACE_USERDATA_1 = mmSQ_THREAD_TRACE_USERDATA_1;
  static const uint32_t SQ_THREAD_TRACE_USERDATA_2 = mmSQ_THREAD_TRACE_USERDATA_2;
  static const uint32_t SQ_THREAD_TRACE_USERDATA_3 = mmSQ_THREAD_TRACE_USERDATA_3;

  static const uint32_t REG_SPI_DEBUG_CNTL = mmSPI_DEBUG_CNTL;

  static uint32_t sqtt_perfcounter_addr(uint32_t index) { return 0; }

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
    grbm_gfx_index.bitfields.SA_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }

  // GRBM SE indexing
  static uint32_t grbm_inst_index_value(const uint32_t& instance_index) {
    regGRBM_GFX_INDEX grbm_gfx_index{};
    grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SA_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }

  // GRBM SE indexing
  static uint32_t grbm_se_index_value(const uint32_t& se_index) {
    regGRBM_GFX_INDEX grbm_gfx_index{};
    grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_INDEX = se_index;
    grbm_gfx_index.bitfields.SA_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }

  static uint32_t grbm_se_sh_wgp_index_value(uint32_t se_index, uint32_t wgp, uint32_t sa) {
    regGRBM_GFX_INDEX grbm_gfx_index{};
    grbm_gfx_index.bitfields.SE_INDEX = se_index;
    grbm_gfx_index.bitfields.SA_INDEX = sa;
    grbm_gfx_index.bitfields.INSTANCE_INDEX = wgp<<2;
    return grbm_gfx_index.u32All;
  }

  // GRBM SE/BlockInstance indexing
  static uint32_t grbm_inst_se_index_value(const uint32_t& instance_index,
                                           const uint32_t& se_index) {
    regGRBM_GFX_INDEX grbm_gfx_index{};
    grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
    grbm_gfx_index.bitfields.SE_INDEX = se_index;
    grbm_gfx_index.bitfields.SA_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }

  // GRBM SE/SH indexing
  static uint32_t grbm_se_sh_index_value(const uint32_t& se_index, const uint32_t& sa_index) {
    regGRBM_GFX_INDEX grbm_gfx_index{};
    grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_INDEX = se_index;
    grbm_gfx_index.bitfields.SA_INDEX = sa_index;
    return grbm_gfx_index.u32All;
  }

  // GRBM SH/SE/BlockInstance indexing
  static uint32_t grbm_inst_se_sh_index_value(const uint32_t& instance_index,
                                              const uint32_t& se_index,
                                              const uint32_t& sa_index) {
    regGRBM_GFX_INDEX grbm_gfx_index{};
    grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
    grbm_gfx_index.bitfields.SE_INDEX = se_index;
    grbm_gfx_index.bitfields.SA_INDEX = sa_index;
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

  // CP_PERFMON_CNTL value to stop/freeze counters
  static uint32_t cp_perfmon_cntl_read_value() {
    regCP_PERFMON_CNTL cp_perfmon_cntl{};
    cp_perfmon_cntl.bits.PERFMON_STATE = 1;
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
    //sq_cntr_sel.bits.SQC_BANK_MASK = 0xF;
    sq_cntr_sel.bits.PERF_SEL = counter_des.id;
    return sq_cntr_sel.u32All;
  }
  static uint32_t sq_spm_select_value(const counter_des_t& counter_des) {
    regSQ_PERFCOUNTER0_SELECT sq_cntr_sel{};
    //sq_cntr_sel.bits.SQC_BANK_MASK = 0xF;
    sq_cntr_sel.bits.PERF_SEL = counter_des.id;
    sq_cntr_sel.bits.SPM_MODE = 3; // PERFMON_SPM_MODE_32BIT_CLAMP
    return sq_cntr_sel.u32All;
  }

  // SQ Counter Mask Register value - not used in gfx12
  static uint32_t sq_mask_value(const counter_des_t&) { return 0xFFFFFFFF; }

  // SQ Counter Control Register value
  static uint32_t sq_control_value(const counter_des_t& counter_des) {
    const uint32_t block_id = counter_des.block_des.id;
    regSQ_PERFCOUNTER_CTRL sq_cntr_ctrl{};
    if (block_id == SqCounterBlockId) {
      sq_cntr_ctrl.bits.GS_EN = 0x1;
      //sq_cntr_ctrl.bits.VS_EN = 0x1;
      sq_cntr_ctrl.bits.PS_EN = 0x1;
      sq_cntr_ctrl.bits.HS_EN = 0x1;
      sq_cntr_ctrl.bits.CS_EN = 0x1;
    } else if (block_id == SqGsCounterBlockId) {
      sq_cntr_ctrl.bits.GS_EN = 0x1;
    } /*else if (block_id == SqVsCounterBlockId) {
      sq_cntr_ctrl.bits.VS_EN = 0x1;
    } */else if (block_id == SqPsCounterBlockId) {
      sq_cntr_ctrl.bits.PS_EN = 0x1;
    } else if (block_id == SqHsCounterBlockId) {
      sq_cntr_ctrl.bits.HS_EN = 0x1;
    } else if (block_id == SqCsCounterBlockId) {
      sq_cntr_ctrl.bits.CS_EN = 0x1;
    }
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
    //sq_cntr_ctrl.bits.VS_EN = 0x1;
    sq_cntr_ctrl.bits.GS_EN = 0x1;
    //sq_cntr_ctrl.bits.ES_EN = 0x1;
    sq_cntr_ctrl.bits.HS_EN = 0x1;
    //sq_cntr_ctrl.bits.LS_EN = 0x1;
    sq_cntr_ctrl.bits.CS_EN = 0x1;
    return sq_cntr_ctrl.u32All;
  }
  static uint32_t sq_control2_enable_value() {
    regSQ_PERFCOUNTER_CTRL2 sq_cntr_ctrl{};
    sq_cntr_ctrl.bits.FORCE_EN = true;
    sq_cntr_ctrl.bits.VMID_EN = 0xFFFF;
    return sq_cntr_ctrl.u32All;
  }
  static uint32_t sq_control2_disable_value() {
    regSQ_PERFCOUNTER_CTRL2 sq_cntr_ctrl{};
    sq_cntr_ctrl.bits.FORCE_EN = false;
    sq_cntr_ctrl.bits.VMID_EN = 0xFFFF;
    return sq_cntr_ctrl.u32All;
  }

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
    select.bits.PERF_SEL = counter_des.id;
    return select.u32All;
  }
  template <typename Select> static uint32_t select_value_t3(const counter_des_t& counter_des) {
    Select select{};
    select.bits.CNTR_SEL0 = counter_des.id;
    return select.u32All;
  }
  static uint32_t spm_select_value(const counter_des_t& counter_des) {
    regTCP_PERFCOUNTER0_SELECT select{};
    select.bits.PERF_SEL = counter_des.id;
    select.bits.CNTR_MODE = 3;  // PERFMON_SPM_MODE_32BIT_CLAMP
    return select.u32All;
  }
  static uint32_t spm_even_select_value(const counter_des_t& counter_des) {
    regTCP_PERFCOUNTER0_SELECT select{};
    select.bits.PERF_SEL = counter_des.id;
    select.bits.CNTR_MODE = 3;  // PERFMON_SPM_MODE_32BIT_CLAMP
    return select.u32All;
  }
  static uint32_t spm_odd_select_value(const counter_des_t& counter_des) {
    regTCP_PERFCOUNTER0_SELECT select{};
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
  static uint32_t sdma_enable_value() {
    //regSDMA0_PERFMON_CNTL sdma_perfmon_cntl{};
    //sdma_perfmon_cntl.bits.PERF_ENABLE0  = 0x1;
    //sdma_perfmon_cntl.bits.PERF_ENABLE1  = 0x1;
    return 0;//sdma_perfmon_cntl.u32All;
  }

  static uint32_t sdma_disable_clear_value() {
    //regSDMA0_PERFMON_CNTL sdma_perfmon_cntl{};
    //sdma_perfmon_cntl.bits.PERF_CLEAR0  = 0x1;
    //sdma_perfmon_cntl.bits.PERF_CLEAR1  = 0x1;
    return 0; //sdma_perfmon_cntl.u32All;
  }

  static uint32_t sdma_select_value(const counter_des_t& counter_des) {
#if 0
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
#endif
    return 0; //sdma_perfmon_cntl.u32All;
  }

  static uint32_t sdma_stop_value(const counter_des_t& counter_des) {
   // regSDMA0_PERFMON_CNTL sdma_perfmon_cntl{};
    return 0;  //sdma_perfmon_cntl.u32All;
  }

  // UMC primitives
  static uint32_t umc_disable_clear_value() {
    // register: PERFMONCTLCLK
    uint32_t disable_clear_value = 0;
    // clear - GlblReset
    disable_clear_value |= 1 << 24;
    return disable_clear_value;
  }

  static uint32_t umc_enable_value() {
    // register: PERFMONCTLCLK
    uint32_t enable_value = 0;
    // global enable
    enable_value |= 1 << 25;
    return enable_value;
  }

  static uint32_t umc_select_value(const counter_des_t& counter_des) {
    // register: PERFMONCTR1-4
    uint32_t select_value = 0;
    // enable counter
    select_value |= 1 << 31;
    // perf select
    select_value |= counter_des.id;
    return select_value;
  }

  static uint32_t umc_select_cycle() {
    // register: PERFMONCTR1-4
    uint32_t select_cycle = 0;
    // enable cycle
    select_cycle |= 1 << 31;
    return select_cycle;
  }

  static uint32_t umc_stop_value() {
    // register: PERFMONCTR1-4/CLK
    return 0;
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
#if 0    
    RLC_SPM_SE_MUXSEL_DATA data{};
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
#endif
    return 0; //data.u32All;
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
    value.bits.TOTAL_NUM_SEGMENT = segment_size;
    value.bits.GLOBAL_NUM_SEGMENT = global_nlines;
    //value.bits.SE0_NUM_LINE = se_nlines;
    //value.bits.SE1_NUM_LINE = se_nlines;
    //value.bits.SE2_NUM_LINE = se_nlines;
    //value.bits.PERFMON_SEGMENT_SIZE = segment_size;
    return value.u32All;
  }

  static uint32_t rlc_spm_perfmon_segment_size_core1_value(const uint32_t& se_count) {
    return 0;
  }

  // Enable all of the WTYPEs
  // Enable Shader Array (SH) at index Zero to be used for fine-grained data
  static uint32_t sqtt_mask_value(uint32_t wgp, uint32_t simd, uint32_t vmid){
    regSQ_THREAD_TRACE_MASK mask{};
    mask.bits.SIMD_SEL = simd;
    mask.bits.WGP_SEL = wgp;
    mask.bits.SA_SEL = 0x0;
    mask.bits.WTYPE_INCLUDE = 1<<6; // SQ_TT_WTYPE_INCLUDE_CS_BIT
    mask.bits.EXCLUDE_NONDETAIL_SHADERDATA = 1;
    //mask.bits.EXCLUDE_NONDETAIL_WAVESTART_EXT = 1;
    //mask.bits.EXCLUDE_NONDETAIL_ALLOC = 1;
    return mask.u32All;
  }

  // not supported in gfx12
  static uint32_t sqtt_perf_mask_value() { return 0; }

  // Indicate the different TT messages/tokens that should be enabled/logged
  // Indicate the different TT tokens that specify register operations to be logged
  static uint32_t sqtt_token_mask_on_value() {
    regSQ_THREAD_TRACE_TOKEN_MASK token_mask{};
    token_mask.bits.REG_DETAIL_ALL = 1;
    token_mask.bits.REG_EXCLUDE = 0x3; //0x7;
    token_mask.bits.REG_INCLUDE = (SQ_TT_TOKEN_MASK_SQDEC_BIT   |
                                   SQ_TT_TOKEN_MASK_SHDEC_BIT   |
                                   SQ_TT_TOKEN_MASK_GFXUDEC_BIT |
                                   SQ_TT_TOKEN_MASK_CONTEXT_BIT |
                                   SQ_TT_TOKEN_MASK_COMP_BIT); // 0x8;
    token_mask.bits.TOKEN_EXCLUDE = ((1 << SQ_TT_TOKEN_EXCLUDE_VMEMEXEC_SHIFT) |
                                     (1 << SQ_TT_TOKEN_EXCLUDE_ALUEXEC_SHIFT));
    token_mask.bits.EXCLUDE_BARRIER_WAIT = 1; // See DEGFX12-10117
    return token_mask.u32All;
  }
  static uint32_t sqtt_token_mask_off_value() {
    regSQ_THREAD_TRACE_TOKEN_MASK token_mask{};
    token_mask.bits.REG_EXCLUDE = 0x7;
    token_mask.bits.INST_EXCLUDE = 0x3;
    token_mask.bits.TOKEN_EXCLUDE = 0x7FF;
    return token_mask.u32All;
  }

  static uint32_t sqtt_token_mask_occupancy_value() {
    regSQ_THREAD_TRACE_TOKEN_MASK token_mask{};
    token_mask.bits.REG_INCLUDE = 0x8;
    token_mask.bits.INST_EXCLUDE = 0x3;
    token_mask.bits.TOKEN_EXCLUDE = 0x7FF;
    return token_mask.u32All;
  }

  // not supported in gfx12
  static uint32_t sqtt_token_mask2_value() { return 0; }

  // Check if stalling is supported
  static bool sqtt_stalling_enabled(const uint32_t& mask_val, const uint32_t& token_mask_val) { return 0; }

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
  static uint32_t sqtt_mode_off_value() { return 0; }
  // Thread trace mode ON value
  static uint32_t sqtt_mode_on_value() { return 0; }

  // Base address of buffer to use for thread trace
  static uint32_t sqtt_base_value_lo(const uint64_t& base_addr) {
    regSQ_THREAD_TRACE_BUF0_BASE_LO base_lo{};
    base_lo.bits.BASE_LO = Low32(base_addr >> TT_BUFF_ALIGN_SHIFT);
    return base_lo.u32All;
  }

  static uint32_t sqtt_base_value_hi(const uint64_t& base_addr) {
    regSQ_THREAD_TRACE_BUF0_BASE_HI base_hi{};
    base_hi.bits.BASE_HI = High32(base_addr >> TT_BUFF_ALIGN_SHIFT);
    return base_hi.u32All;
  }

  // Indicates the size of buffer to use per Shader Engine instance.
  // The size is specified in terms of 4KB blocks
  static uint32_t sqtt_buffer0_size_value(uint32_t size_val) {
    regSQ_THREAD_TRACE_BUF0_SIZE size{};
    size.bits.SIZE = size_val >> TT_BUFF_ALIGN_SHIFT;
    return size.u32All;
  }

  static uint32_t spi_sqg_event_ctl(bool enableSqgEvents) {
    regSPI_SQG_EVENT_CTL event_ctl{};
    event_ctl.bits.ENABLE_SQG_TOP_EVENTS = enableSqgEvents;
    event_ctl.bits.ENABLE_SQG_BOP_EVENTS = enableSqgEvents;
    return event_ctl.u32All;
  }

  static uint32_t sqtt_buffer_size_value(uint32_t size_val, uint32_t base_hi) {
    return 0;
  }

  static uint32_t sqtt_zero_size_value() { return 0; }

  // Thread trace ctrl register value
  static uint32_t sqtt_ctrl_value(bool on) {
    regSQ_THREAD_TRACE_CTRL ctrl{};
    if (on)
      ctrl.bits.MODE = SQ_TT_MODE_ON;
    else
      ctrl.bits.MODE = SQ_TT_MODE_OFF;
    ctrl.bits.HIWATER = 5;
    ctrl.bits.UTIL_TIMER = 1;
    ctrl.bits.DRAW_EVENT_EN = 1;
    ctrl.bits.SPI_STALL_EN = 1;
    ctrl.bits.SQ_STALL_EN = 1;
    ctrl.bits.SQ_STALL_EN = 1;
    ctrl.bits.LOWATER_OFFSET = 4;
    ctrl.bits.AUTO_FLUSH_MODE = 1;
    return ctrl.u32All;
  }

  // SPM primitives
  static uint16_t spm_timestamp_muxsel() {
    return 0xF0F0;
  }

  enum ESQTT_STATUS_MASK {
    // Mask to check if memory error was received
    TT_CONTROL_UTC_ERR_MASK = 0x1000000,
    // TODO: Navi has 2 full bits on status2, one for each buffer
    TT_CONTROL_FULL_MASK = 0x0,
    TT_WRITE_PTR_MASK = 0x1FFFFFFF
  };

  static uint32_t sqtt_busy_mask() {
    const uint32_t BUSY_BIT = 25;
    return 1u << BUSY_BIT;
  }

  static uint32_t sqtt_pending_mask() {
    const uint32_t PIPE_START = 2;
    const uint32_t NUM_PIPES = 8;
    return (1u << (NUM_PIPES+PIPE_START)) - (1u << PIPE_START);
  }

  static uint32_t spi_cntl_debug(int pipe)
  {
    SPI_DEBUG_CNTL cntl{};
    cntl.bitfields.DEBUG_PIPE_SEL = pipe;
    return cntl.u32All;
  };
};

template <>
inline uint32_t gfx12_cntx_prim::select_value<regSX_PERFCOUNTER0_SELECT>(
    const counter_des_t& counter_des) {
  return select_value_t2<regSX_PERFCOUNTER0_SELECT>(counter_des);
}

}  // namespace gfx12
}  // namespace gfxip

#endif  // _GFX12_PRIMITIVES_H_
