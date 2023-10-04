#ifndef _GFX9_PRIMITIVES_H_
#define _GFX9_PRIMITIVES_H_

#include <stdint.h>

namespace gfxip {
namespace gfx9 {

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
  static const uint32_t COMPUTE_THREAD_TRACE_ENABLE_ADDR = 0;
  static const uint32_t SQ_PERFCOUNTER_MASK_ADDR = mmSQ_PERFCOUNTER_MASK;
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
  static const uint32_t UMC_COUNTER_BLOCK_NUM_INSTANCES = UmcCounterBlockMaxInstances;

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

  // UMC primitives
  static uint32_t umc_disable_clear_value() {
    // register: UMCCH_PERFMONCTLCLK
    regUMCCH_PerfMonCtlClk perfmon_ctl_clk{};
    // clear - GlblReset
    perfmon_ctl_clk.bits.GlblReset = 1;
    return perfmon_ctl_clk.u32All;
  }

  static uint32_t umc_enable_value() {
    // register: UMCCH_PERFMONCTLCLK
    regUMCCH_PerfMonCtlClk perfmon_ctl_clk{};
    // global enable
    perfmon_ctl_clk.bits.GlblMonEn = 1;
    return perfmon_ctl_clk.u32All;
  }

  static uint32_t umc_select_value(const counter_des_t& counter_des) {
    // register: UMCCH_PERFMONCTR1-4
    regUMCCH_PerfMonCtl1 perfmon_ctl{};
    // enable counter
    perfmon_ctl.bits.Enable = 1;
    // perf select
    perfmon_ctl.bits.EventSelect = counter_des.id;
    return perfmon_ctl.u32All;
  }

  static uint32_t umc_select_cycle() {
    // register: UMCCH_PERFMONCTR1-4
    regUMCCH_PerfMonCtl1 perfmon_ctl{};
    // enable cycle
    perfmon_ctl.bits.Enable = 1;
    return perfmon_ctl.u32All;
  }

  static uint32_t umc_stop_value() {
    // register: UMCCH_PERFMONCTR1-4/CLK
    regUMCCH_PerfMonCtl1 perfmon_ctl{};
    return perfmon_ctl.u32All;
  }

  // SPM trace routines
  static uint32_t rlc_spm_mc_cntl_value() {
    regRLC_SPM_MC_CNTL mc_cntl{};
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
  static uint32_t sqtt_mask_value(uint32_t targetCu, uint32_t simd, uint32_t vmIdMask) {
    regSQ_THREAD_TRACE_MASK mask{};
    mask.bits.SH_SEL = 0x0;
    mask.bits.SIMD_EN = simd;
    mask.bits.CU_SEL = targetCu;
    mask.bits.SQ_STALL_EN = 0x1;
    mask.bits.SPI_STALL_EN = 0x1;
    mask.bits.REG_STALL_EN = 0x1;
    mask.bits.VM_ID_MASK = vmIdMask;
    return mask.u32All;
  }

  // Mask of compute units to get thread trace data from
  static uint32_t sqtt_perf_mask_value() {
    regSQ_THREAD_TRACE_PERF_MASK perf_mask{};
    perf_mask.bits.SH0_MASK = 0xFFFF;
    return perf_mask.u32All;
  }

  // Indicate the different TT messages/tokens that should be enabled/logged
  // Indicate the different TT tokens that specify register operations to be logged
  static uint32_t sqtt_token_mask_on_value() {
    regSQ_THREAD_TRACE_TOKEN_MASK token_mask{};
    token_mask.bits.REG_MASK = 0xF;
    token_mask.bits.TOKEN_MASK = 0xBC6B;
    return token_mask.u32All;
  }

  static uint32_t sqtt_token_mask_off_value() {
    regSQ_THREAD_TRACE_TOKEN_MASK token_mask{};
    token_mask.bits.REG_MASK = 0x0;
    token_mask.bits.TOKEN_MASK = 0x104A;
    return token_mask.u32All;
  }

  // Indicate the different TT tokens that specify instruction operations to be logged
  // Disabling specifically instruction operations updating Program Counter (PC).
  // @note: The field is defined in the spec incorrectly as a 16-bit value
  static uint32_t sqtt_token_mask2_value() {
    regSQ_THREAD_TRACE_TOKEN_MASK2 token_mask2{};
    token_mask2.bits.INST_MASK = 0xFFFFFFFF;
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
  static uint32_t sqtt_buffer_size_value(uint32_t size_val, uint32_t base_hi) {
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

  enum ESQTT_STATUS_MASK {
    // Mask to check if memory error was received
    TT_CONTROL_UTC_ERR_MASK = 0x10000000,
    // Mask to check if SQTT buffer is wrapped
    TT_CONTROL_FULL_MASK = 0x80000000,
    TT_WRITE_PTR_MASK = 0x3FFFFFFF
  };
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

}  // namespace gfx9
}  // namespace gfxip

#endif  // _GFX9_PRIMITIVES_H_
