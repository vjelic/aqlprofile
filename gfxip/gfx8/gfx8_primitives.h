#ifndef _GFX8_PRIMITIVES_H_
#define _GFX8_PRIMITIVES_H_

#include <stdint.h>

class gfx8_cntx_prim {
  public:
  const static uint32_t GRBM_GFX_INDEX_ADDR = mmGRBM_GFX_INDEX__CI__VI;
  const static uint32_t CP_PERFMON_CNTL_ADDR = mmCP_PERFMON_CNTL__CI__VI;
  const static uint32_t SQ_PERFCOUNTER_MASK_ADDR = mmSQ_PERFCOUNTER_MASK__CI__VI;
  const static uint32_t COMPUTE_PERFCOUNT_ENABLE_ADDR = mmCOMPUTE_PERFCOUNT_ENABLE__CI__VI;
  const static uint32_t COPY_DATA_SEL_REG_PRM = COPY_DATA_SEL_REG;
  const static uint32_t COPY_DATA_SEL_COUNT_1DW_PRM = COPY_DATA_SEL_COUNT_1DW;

  // GRBM broadcasting mode
  static uint32_t grbm_broadcast_value() {
    regGRBM_GFX_INDEX grbm_gfx_index = {0};
    grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }
  
  // GRBM SE indexing
  static uint32_t grbm_iindex_value(const uint32_t & instance_index) {
    regGRBM_GFX_INDEX grbm_gfx_index = {0};
    grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }
  
  // GRBM SE indexing
  static uint32_t grbm_seindex_value(const uint32_t & se_index) {
    regGRBM_GFX_INDEX grbm_gfx_index = {0};
    grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_INDEX = se_index;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }
  
  // GRBM SE/BlockInstance indexing
  static uint32_t grbm_bindex_value(const uint32_t & instance_index, const uint32_t & se_index) {
    regGRBM_GFX_INDEX grbm_gfx_index = {0};
    grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
    grbm_gfx_index.bitfields.SE_INDEX = se_index;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
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
  
  // SQ Counter Select Register value
  static uint32_t sq_select_value(const counter_des_t & counter_des) {
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
  static uint32_t sq_control_value(const counter_des_t & counter_des) {
    const uint32_t block_id = counter_des.block_des.id;
    regSQ_PERFCOUNTER_CTRL sq_cntr_ctrl = {0};
    if (block_id == kHsaViCounterBlockIdSq) {
      sq_cntr_ctrl.bits.ES_EN = 0x1;
      sq_cntr_ctrl.bits.GS_EN = 0x1;
      sq_cntr_ctrl.bits.VS_EN = 0x1;
      sq_cntr_ctrl.bits.PS_EN = 0x1;
      sq_cntr_ctrl.bits.LS_EN = 0x1;
      sq_cntr_ctrl.bits.HS_EN = 0x1;
      sq_cntr_ctrl.bits.CS_EN = 0x1;
    } else if (block_id == kHsaViCounterBlockIdSqEs) {
      sq_cntr_ctrl.bits.ES_EN = 0x1;
    } else if (block_id == kHsaViCounterBlockIdSqGs) {
      sq_cntr_ctrl.bits.GS_EN = 0x1;
    } else if (block_id == kHsaViCounterBlockIdSqVs) {
      sq_cntr_ctrl.bits.VS_EN = 0x1;
    } else if (block_id == kHsaViCounterBlockIdSqPs) {
      sq_cntr_ctrl.bits.PS_EN = 0x1;
    } else if (block_id == kHsaViCounterBlockIdSqLs) {
      sq_cntr_ctrl.bits.LS_EN = 0x1;
    } else if (block_id == kHsaViCounterBlockIdSqHs) {
      sq_cntr_ctrl.bits.HS_EN = 0x1;
    } else if (block_id == kHsaViCounterBlockIdSqCs) {
      sq_cntr_ctrl.bits.CS_EN = 0x1;
    }
    return sq_cntr_ctrl.u32All;
  }
  
  // Counter Select Register value template
  template <typename Select>
  static uint32_t selectp_value(const counter_des_t & counter_des) {
    Select select = {0};
    select.bits.PERFCOUNTER_SELECT = counter_des.id;
    return select.u32All;
  }
  template <typename Select>
  static uint32_t select_value(const counter_des_t & counter_des) {
    Select select = {0};
    select.bits.PERF_SEL = counter_des.id;
    return select.u32All;
  }
};

template<>
inline uint32_t gfx8_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT__CI__VI>(const counter_des_t & counter_des) {
  return sq_select_value(counter_des);
}
template<>
inline uint32_t gfx8_cntx_prim::select_value<regSX_PERFCOUNTER0_SELECT>(const counter_des_t & counter_des) {
  return selectp_value<regSX_PERFCOUNTER0_SELECT>(counter_des);
}
template<>
inline uint32_t gfx8_cntx_prim::select_value<regGDS_PERFCOUNTER0_SELECT>(const counter_des_t & counter_des) {
  return selectp_value<regGDS_PERFCOUNTER0_SELECT>(counter_des);
}

#endif  // _GFX8_PRIMITIVES_H_
