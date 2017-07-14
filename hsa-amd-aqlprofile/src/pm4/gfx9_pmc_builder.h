#ifndef _GFX9_PMC_BUILDER_H_
#define _GFX9_PMC_BUILDER_H_

#include <assert.h>
#include <stdint.h>

#include "pmc_builder.h"
#include "gfx9_cmd_builder.h"

#include "gfxip/gfx9/gfx9_block_info.h"
#include "gfxip/gfx9/gfx9_registers.h"
#include "gfxip/gfx9/gfx9_typedef.h"
#include "gfxip/gfx9/gfx9_offset.h"
#include "gfxip/gfx9/gfx9_pm4defs.h"

namespace pm4_builder {
using namespace std;
using namespace pm4_builder;
using namespace gfxip::gfx9;

class Gfx9PmcBuilder : public pm4_builder::PmcBuilder, protected Gfx9CmdBuilder {
 public:
  void begin(CmdBuffer* cmdBuff, const counters_vector& countersVec) {
    // Reset Grbm to its default state - broadcast
    BuildWriteUConfigRegPacket(cmdBuff, mmGRBM_GFX_INDEX, grbm_reset_value());

    // Disable RLC Perfmon Clock Gating
    // On Vega this is needed to collect Perf Cntrs
    BuildWriteUConfigRegPacket(cmdBuff, mmRLC_PERFMON_CLK_CNTL, 1);

    // Reset the counter list
    regCP_PERFMON_CNTL cp_perfmon_cntl = {0};
    BuildWriteUConfigRegPacket(cmdBuff, mmCP_PERFMON_CNTL, cp_perfmon_cntl.u32All);

    // Iterate through the list of blocks to generate Pm4 commands to
    // program corresponding perf counters of each block
    std::map<block_des_t, uint32_t, lt_block_des> index_map;
    for (counters_vector::const_iterator it = countersVec.begin(); it != countersVec.end(); ++it) {
      const block_des_t& block_des = it->first;
      const uint32_t& counter_id = it->second;

      auto ret = index_map.insert({block_des, 0});
      uint32_t& index = ret.first->second;

      // Build the list of control registers to program which
      // varies per perf counter block
      uint32_t reg_addr[MAX_REG_NUM], reg_val[MAX_REG_NUM];
      const uint32_t reg_num =
          BuildCounterSelRegister(index, reg_addr, reg_val, block_des, counter_id);

      // Build the list of Pm4 commands that support control
      // register programming
      for (uint32_t n = 0; n < reg_num; ++n) {
        BuildWriteUConfigRegPacket(cmdBuff, reg_addr[n], reg_val[n]);
      }

      ++index;
    }

    // Reset Grbm to its default state - broadcast
    BuildWriteUConfigRegPacket(cmdBuff, mmGRBM_GFX_INDEX, grbm_reset_value());

    // Program Compute_Perfcount_Enable register to support perf counting
    regCOMPUTE_PERFCOUNT_ENABLE cp_perfcount_enable;
    cp_perfcount_enable.u32All = 0;
    cp_perfcount_enable.bits.PERFCOUNT_ENABLE = 1;
    BuildWriteShRegPacket(cmdBuff, mmCOMPUTE_PERFCOUNT_ENABLE, cp_perfcount_enable.u32All);

    // Reset the counter list
    BuildWriteUConfigRegPacket(cmdBuff, mmCP_PERFMON_CNTL, cp_perfmon_cntl.u32All);

    // Start the counter list
    cp_perfmon_cntl.bits.PERFMON_STATE = 1;
    BuildWriteUConfigRegPacket(cmdBuff, mmCP_PERFMON_CNTL, cp_perfmon_cntl.u32All);

    // Issue barrier command to apply the commands to configure perfcounters
    BuildWriteWaitIdlePacket(cmdBuff);
  }

  uint32_t end(CmdBuffer* cmdBuff, const counters_vector& countersVec, void* dataBuff) {
    // Issue barrier command to wait for dispatch to complete
    BuildWriteWaitIdlePacket(cmdBuff);

    // Build PM4 packet to stop and freeze counters
    regCP_PERFMON_CNTL cp_perfmon_cntl;
    cp_perfmon_cntl.u32All = 0;
    cp_perfmon_cntl.bits.PERFMON_STATE = 2;
    cp_perfmon_cntl.bits.PERFMON_SAMPLE_ENABLE = 1;
    BuildWriteUConfigRegPacket(cmdBuff, mmCP_PERFMON_CNTL, cp_perfmon_cntl.u32All);

    // Reset Grbm to its default state - broadcast
    BuildWriteUConfigRegPacket(cmdBuff, mmGRBM_GFX_INDEX, grbm_reset_value());

    // Iterate through the list of blocks to create PM4 packets to read counter values
    std::map<block_des_t, uint32_t, lt_block_des> index_map;
    uint32_t read_counter = 0;
    for (counters_vector::const_iterator it = countersVec.begin(); it != countersVec.end(); ++it) {
      const block_des_t& block_des = it->first;
      const uint32_t& counter_id = it->second;

      auto ret = index_map.insert({block_des, 0});
      uint32_t& index = ret.first->second;

      // retrieve the registers to be set
      uint32_t reg_addr[MAX_REG_NUM], reg_val[MAX_REG_NUM];
      const uint32_t reg_num = BuildCounterReadRegisters(index, block_des, reg_addr, reg_val);

      for (uint32_t n = 0; n < reg_num; n++) {
        if (reg_val[n] == COPY_DATA_FLAG) {
          BuildCopyDataPacket(cmdBuff, COPY_DATA_SEL_REG, reg_addr[n], 0,
                              (uint32_t*)dataBuff + read_counter, COPY_DATA_SEL_COUNT_1DW, false);
          ++read_counter;
        } else {
          BuildWriteUConfigRegPacket(cmdBuff, reg_addr[n], reg_val[n]);
        }
      }

      ++index;
    }

    // Reset Grbm to its default state - broadcast
    BuildWriteUConfigRegPacket(cmdBuff, mmGRBM_GFX_INDEX, grbm_reset_value());

    // Enable RLC Perfmon Clock Gating. On Vega this is
    // was disabled during Perf Cntrs collection session
    BuildWriteUConfigRegPacket(cmdBuff, mmRLC_PERFMON_CLK_CNTL, 0);

    return read_counter * sizeof(uint32_t);
  }

 private:
  // Used to reset GRBM to its default state
  static uint32_t grbm_reset_value() {
    // Initialize the value to use in resetting GRBM
    regGRBM_GFX_INDEX grbm_gfx_index;
    grbm_gfx_index.u32All = 0;
    grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    return grbm_gfx_index.u32All;
  }

  uint32_t ProgramTcpCntrs(uint32_t tcpRegIdx, uint32_t* regAddr, uint32_t* regVal,
                           block_des_t block_des, uint32_t blkCntrIdx) {
    regGRBM_GFX_INDEX grbm_gfx_index;

    grbm_gfx_index.u32All = 0;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.INSTANCE_INDEX = block_des.index;

    uint32_t regIdx = 0;
    regVal[regIdx] = grbm_gfx_index.u32All;
    regAddr[regIdx] = mmGRBM_GFX_INDEX;
    regIdx++;

    regTCP_PERFCOUNTER0_SELECT tcp_perf_counter_select;
    tcp_perf_counter_select.u32All = 0;
    tcp_perf_counter_select.bits.PERF_SEL = blkCntrIdx;

    regVal[regIdx] = tcp_perf_counter_select.u32All;
    regAddr[regIdx] = AiTcpCounterRegAddr[tcpRegIdx].counterSelRegAddr;
    regIdx++;

    return regIdx;
  }

  uint32_t ProgramTdCntrs(uint32_t tdRegIdx, uint32_t* regAddr, uint32_t* regVal,
                          block_des_t block_des, uint32_t blkCntrIdx) {
    regGRBM_GFX_INDEX grbm_gfx_index;

    grbm_gfx_index.u32All = 0;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.INSTANCE_INDEX = block_des.index;

    uint32_t regIdx = 0;
    regVal[regIdx] = grbm_gfx_index.u32All;
    regAddr[regIdx] = mmGRBM_GFX_INDEX;
    regIdx++;

    regTD_PERFCOUNTER0_SELECT td_perf_counter_select;
    td_perf_counter_select.u32All = 0;
    td_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
    regVal[regIdx] = td_perf_counter_select.u32All;
    regAddr[regIdx] = AiTdCounterRegAddr[tdRegIdx].counterSelRegAddr;
    regIdx++;

    return regIdx;
  }

  uint32_t ProgramTccCntrs(uint32_t tccRegIdx, uint32_t* regAddr, uint32_t* regVal,
                           block_des_t block_des, uint32_t blkCntrIdx) {
    regGRBM_GFX_INDEX grbm_gfx_index;

    grbm_gfx_index.u32All = 0;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.INSTANCE_INDEX = block_des.index;

    uint32_t regIdx = 0;
    regVal[regIdx] = grbm_gfx_index.u32All;
    regAddr[regIdx] = mmGRBM_GFX_INDEX;
    regIdx++;

    regTCC_PERFCOUNTER0_SELECT tcc_perf_counter_select;
    tcc_perf_counter_select.u32All = 0;
    tcc_perf_counter_select.bits.PERF_SEL = blkCntrIdx;

    regVal[regIdx] = tcc_perf_counter_select.u32All;
    regAddr[regIdx] = AiTccCounterRegAddr[tccRegIdx].counterSelRegAddr;
    regIdx++;

    return regIdx;
  }

  uint32_t ProgramTcaCntrs(uint32_t tcaRegIdx, uint32_t* regAddr, uint32_t* regVal,
                           block_des_t block_des, uint32_t blkCntrIdx) {
    regGRBM_GFX_INDEX grbm_gfx_index;

    grbm_gfx_index.u32All = 0;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.INSTANCE_INDEX = block_des.index;

    uint32_t regIdx = 0;
    regVal[regIdx] = grbm_gfx_index.u32All;
    regAddr[regIdx] = mmGRBM_GFX_INDEX;
    regIdx++;

    regTCA_PERFCOUNTER0_SELECT tca_perf_counter_select;
    tca_perf_counter_select.u32All = 0;
    tca_perf_counter_select.bits.PERF_SEL = blkCntrIdx;

    regVal[regIdx] = tca_perf_counter_select.u32All;
    regAddr[regIdx] = AiTcaCounterRegAddr[tcaRegIdx].counterSelRegAddr;
    regIdx++;
    return regIdx;
  }

  uint32_t ProgramTaCntrs(uint32_t taRegIdx, uint32_t* regAddr, uint32_t* regVal,
                          block_des_t block_des, uint32_t blkCntrIdx) {
    regGRBM_GFX_INDEX grbm_gfx_index;

    grbm_gfx_index.u32All = 0;
    grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
    grbm_gfx_index.bitfields.INSTANCE_INDEX = block_des.index;

    uint32_t regIdx = 0;
    regVal[regIdx] = grbm_gfx_index.u32All;
    regAddr[regIdx] = mmGRBM_GFX_INDEX;
    regIdx++;

    regTA_PERFCOUNTER0_SELECT ta_perf_counter_select;
    ta_perf_counter_select.u32All = 0;
    ta_perf_counter_select.bits.PERF_SEL = blkCntrIdx;

    regVal[regIdx] = ta_perf_counter_select.u32All;
    regAddr[regIdx] = AiTaCounterRegAddr[taRegIdx].counterSelRegAddr;
    regIdx++;

    return regIdx;
  }

  uint32_t ProgramSQCntrs(uint32_t sqRegIdx, uint32_t* regAddr, uint32_t* regVal,
                          block_des_t block_des, uint32_t blkCntrIdx) {
    uint32_t regIdx = 0;

    // Program the SQ Counter Select Register
    regSQ_PERFCOUNTER0_SELECT sq_cntr_sel;
    sq_cntr_sel.u32All = 0;
    sq_cntr_sel.bits.SIMD_MASK = 0xF;
    sq_cntr_sel.bits.SQC_BANK_MASK = 0xF;
    sq_cntr_sel.bits.SQC_CLIENT_MASK = 0xF;
    sq_cntr_sel.bits.PERF_SEL = blkCntrIdx;
    regVal[regIdx] = sq_cntr_sel.u32All;
    regAddr[regIdx] = AiSqCounterRegAddr[sqRegIdx].counterSelRegAddr;
    regIdx++;

    // Program the SQ Counter Mask Register
    regSQ_PERFCOUNTER_MASK sq_cntr_mask;
    sq_cntr_mask.u32All = 0;
    sq_cntr_mask.bits.SH0_MASK = 0xFFFF;
    sq_cntr_mask.bits.SH1_MASK = 0xFFFF;
    regVal[regIdx] = sq_cntr_mask.u32All;
    regAddr[regIdx] = mmSQ_PERFCOUNTER_MASK;
    regIdx++;

    // Initialize the register content
    // Program the SQ Counter Control Register
    regSQ_PERFCOUNTER_CTRL sq_cntr_ctrl;
    sq_cntr_ctrl.u32All = 0;
    if (block_des.id == kHsaAiCounterBlockIdSq) {
      sq_cntr_ctrl.bits.PS_EN = 0x1;
      sq_cntr_ctrl.bits.VS_EN = 0x1;
      sq_cntr_ctrl.bits.GS_EN = 0x1;
      sq_cntr_ctrl.bits.HS_EN = 0x1;
      sq_cntr_ctrl.bits.CS_EN = 0x1;
    } else if (block_des.id == kHsaAiCounterBlockIdSqGs) {
      sq_cntr_ctrl.bits.GS_EN = 0x1;
    } else if (block_des.id == kHsaAiCounterBlockIdSqVs) {
      sq_cntr_ctrl.bits.VS_EN = 0x1;
    } else if (block_des.id == kHsaAiCounterBlockIdSqPs) {
      sq_cntr_ctrl.bits.PS_EN = 0x1;
    } else if (block_des.id == kHsaAiCounterBlockIdSqHs) {
      sq_cntr_ctrl.bits.HS_EN = 0x1;
    } else if (block_des.id == kHsaAiCounterBlockIdSqCs) {
      sq_cntr_ctrl.bits.CS_EN = 0x1;
    }

    regVal[regIdx] = sq_cntr_ctrl.u32All;
    regAddr[regIdx] = AiSqCounterRegAddr[sqRegIdx].counterCntlRegAddr;
    regIdx++;

    return regIdx;
  }

  uint32_t BuildCounterSelRegister(uint32_t cntrIdx, uint32_t* regAddr, uint32_t* regVal,
                                   block_des_t block_des, uint32_t blkCntrIdx) {
    uint32_t block_id = block_des.id;
    uint32_t instance_index = block_des.index;
    regGRBM_GFX_INDEX grbm_gfx_index = {0};
    uint32_t regIdx = 0;

    switch (block_id) {
      // Program counters belonging to SQ block
      case kHsaAiCounterBlockIdSq:
      case kHsaAiCounterBlockIdSqGs:
      case kHsaAiCounterBlockIdSqVs:
      case kHsaAiCounterBlockIdSqPs:
      case kHsaAiCounterBlockIdSqHs:
      case kHsaAiCounterBlockIdSqCs:
        return ProgramSQCntrs(cntrIdx, regAddr, regVal, block_des, blkCntrIdx);
      case kHsaAiCounterBlockIdCb: {
        regIdx = 0;
        grbm_gfx_index.u32All = 0;
        grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
        grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
        grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

        regVal[regIdx] = grbm_gfx_index.u32All;
        regAddr[regIdx] = mmGRBM_GFX_INDEX;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER0_LO;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER0_HI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER1_LO;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER1_HI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER2_LO;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER2_HI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER3_LO;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER3_HI;
        regIdx++;

        regCB_PERFCOUNTER0_SELECT cb_perf_counter_select;
        cb_perf_counter_select.u32All = 0;
        cb_perf_counter_select.bits.PERF_SEL = blkCntrIdx;

        regVal[regIdx] = cb_perf_counter_select.u32All;
        regAddr[regIdx] = AiCbCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx++;

        break;
      }
      // Temp commented for Vega10
      /*
      case kHsaAiCounterBlockIdCpf: {
        regCPF_PERFCOUNTER0_SELECT cpf_perf_counter_select;
        cpf_perf_counter_select.u32All = 0;
        cpf_perf_counter_select.bits.PERF_SEL = blkCntrIdx;

        regVal[0] = cpf_perf_counter_select.u32All;
        regAddr[0] = AiCpfCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      */
      case kHsaAiCounterBlockIdDb: {
        regIdx = 0;
        grbm_gfx_index.u32All = 0;
        grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
        grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
        grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

        regVal[regIdx] = grbm_gfx_index.u32All;
        regAddr[regIdx] = mmGRBM_GFX_INDEX;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER0_LO;
        regIdx++;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER0_HI;
        regIdx++;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER1_LO;
        regIdx++;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER1_HI;
        regIdx++;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER2_LO;
        regIdx++;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER2_HI;
        regIdx++;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER3_LO;
        regIdx++;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER3_HI;
        regIdx++;

        regDB_PERFCOUNTER0_SELECT db_perf_counter_select;
        db_perf_counter_select.u32All = 0;
        db_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[regIdx] = db_perf_counter_select.u32All;
        regAddr[regIdx] = AiDbCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx++;
        break;
      }
      case kHsaAiCounterBlockIdGrbm: {
        regGRBM_PERFCOUNTER0_SELECT grbm_perf_counter_select;
        grbm_perf_counter_select.u32All = 0;
        grbm_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = grbm_perf_counter_select.u32All;
        regAddr[0] = AiGrbmCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaAiCounterBlockIdGrbmSe: {
        regGRBM_SE0_PERFCOUNTER_SELECT grbm_se0_perf_counter_select;
        grbm_se0_perf_counter_select.u32All = 0;
        grbm_se0_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = grbm_se0_perf_counter_select.u32All;
        regAddr[0] = AiGrbmSeCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaAiCounterBlockIdPaSu: {
        regPA_SU_PERFCOUNTER0_SELECT pa_su_perf_counter_select;
        pa_su_perf_counter_select.u32All = 0;
        pa_su_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = pa_su_perf_counter_select.u32All;
        regAddr[0] = AiPaSuCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaAiCounterBlockIdPaSc: {
        regPA_SC_PERFCOUNTER0_SELECT pa_sc_perf_counter_select;
        pa_sc_perf_counter_select.u32All = 0;
        pa_sc_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = pa_sc_perf_counter_select.u32All;
        regAddr[0] = AiPaScCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaAiCounterBlockIdSpi: {
        regSPI_PERFCOUNTER0_SELECT spi_perf_counter_select;
        spi_perf_counter_select.u32All = 0;
        spi_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = spi_perf_counter_select.u32All;
        regAddr[0] = AiSpiCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaAiCounterBlockIdSx: {
        regIdx = 0;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmSX_PERFCOUNTER0_LO;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmSX_PERFCOUNTER0_HI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmSX_PERFCOUNTER1_LO;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmSX_PERFCOUNTER1_HI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmSX_PERFCOUNTER2_LO;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmSX_PERFCOUNTER2_HI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmSX_PERFCOUNTER3_LO;
        regIdx++;

        regSX_PERFCOUNTER0_SELECT sx_perf_counter_select;
        sx_perf_counter_select.u32All = 0;
        sx_perf_counter_select.bits.PERFCOUNTER_SELECT = blkCntrIdx;
        regVal[regIdx] = sx_perf_counter_select.u32All;
        regAddr[regIdx] = AiSxCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx++;
        break;
      }
      case kHsaAiCounterBlockIdTa:
        return ProgramTaCntrs(cntrIdx, regAddr, regVal, block_des, blkCntrIdx);
      case kHsaAiCounterBlockIdTca:
        return ProgramTcaCntrs(cntrIdx, regAddr, regVal, block_des, blkCntrIdx);
      case kHsaAiCounterBlockIdTcc:
        return ProgramTccCntrs(cntrIdx, regAddr, regVal, block_des, blkCntrIdx);
      case kHsaAiCounterBlockIdTd:
        return ProgramTdCntrs(cntrIdx, regAddr, regVal, block_des, blkCntrIdx);
      case kHsaAiCounterBlockIdTcp:
        return ProgramTcpCntrs(cntrIdx, regAddr, regVal, block_des, blkCntrIdx);
      case kHsaAiCounterBlockIdGds: {
        regGDS_PERFCOUNTER0_SELECT gds_perf_counter_select;
        gds_perf_counter_select.u32All = 0;
        gds_perf_counter_select.bits.PERFCOUNTER_SELECT = blkCntrIdx;
        regVal[0] = gds_perf_counter_select.u32All;
        regAddr[0] = AiGdsCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaAiCounterBlockIdVgt: {
        regVGT_PERFCOUNTER0_SELECT vgt_perf_counter_select;
        vgt_perf_counter_select.u32All = 0;
        vgt_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = vgt_perf_counter_select.u32All;
        regAddr[0] = AiVgtCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaAiCounterBlockIdIa: {
        regIA_PERFCOUNTER0_SELECT ia_perf_counter_select;
        ia_perf_counter_select.u32All = 0;
        ia_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = ia_perf_counter_select.u32All;
        regAddr[0] = AiIaCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      /*
      case kHsaAiCounterBlockIdMc: {
        // To be investigated later
        //regMC_SEQ_PERF_SEQ_CTL mc_perfcounter_select;
        //mc_perfcounter_select.u32All = 0;
        //mc_perfcounter_select.bits.PERF_SEL = blkCntrIdx;
        //regVal[0] = mc_perfcounter_select.u32All;
        //regAddr[0] = AiMcCounterRegAddr[cntrIdx].counterSelRegAddr;
        //regIdx = 1;
      }
      break;
      */
      // Temp Commented out for Vega10
      /*
      case kHsaAiCounterBlockIdSrbm: {
        regSRBM_PERFCOUNTER0_SELECT srbm_perf_counter_select;
        srbm_perf_counter_select.u32All = 0;
        srbm_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = srbm_perf_counter_select.u32All;
        regAddr[0] = AiSrbmCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      */
      /*
      case kHsaAiCounterBlockIdTcs: {
        regTCS_PERFCOUNTER0_SELECT__CI tcs_perf_counter_select;
        tcs_perf_counter_select.u32All = 0;
        tcs_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = tcs_perf_counter_select.u32All;
        regAddr[0] = AiTcsCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      */
      case kHsaAiCounterBlockIdWd: {
        regWD_PERFCOUNTER0_SELECT wd_perf_counter_select;
        wd_perf_counter_select.u32All = 0;
        wd_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = wd_perf_counter_select.u32All;
        regAddr[0] = AiWdCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      // Temp commented for Vega10
      /*
      case kHsaAiCounterBlockIdCpg: {
        regCPG_PERFCOUNTER0_SELECT cpg_perf_counter_select;
        cpg_perf_counter_select.u32All = 0;
        cpg_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = cpg_perf_counter_select.u32All;
        regAddr[0] = AiCpgCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      */
      case kHsaAiCounterBlockIdCpc: {
        regCPC_PERFCOUNTER0_SELECT cpc_perf_counter_select;
        cpc_perf_counter_select.u32All = 0;
        cpc_perf_counter_select.bits.CNTR_SEL0 = blkCntrIdx;
        regVal[0] = cpc_perf_counter_select.u32All;
        regAddr[0] = AiCpcCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      /*
      case kHsaAiCounterBlockIdMc: {
        AddPriviledgedCountersToList(AiBlockIdMc, blkCntrIdx);
        //Num of regs equals to 0 means it is processed by KFD
        regIdx = 0;
        break;
      }
      case kHsaAiCounterBlockIdIommuV2: {
        AddPriviledgedCountersToList(AiBlockIdIommuV2, blkCntrIdx);
        //Num of regs equals to 0 means it is processed by KFD
        regIdx = 0;
        break;
      }
      case kHsaAiCounterBlockIdKernelDriver: {
        AddPriviledgedCountersToList(AiBlockIdKernelDriver, blkCntrIdx);
        //Num of regs equals to 0 means it is processed by KFD
        regIdx = 0;
        break;
      }
      */
      default: {
        regIdx = 0;
        break;
      }
    }

    return regIdx;
  }

  uint32_t BuildCounterReadRegisters(uint32_t reg_index, block_des_t block_des, uint32_t* reg_addr,
                                     uint32_t* reg_val) {
    uint32_t ii;
    uint32_t reg_num = 0;
    const uint32_t block_id = block_des.id;
    const uint32_t instance_index = block_des.index;
    regGRBM_GFX_INDEX grbm_gfx_index;
    switch (block_id) {
      case kHsaAiCounterBlockIdSq:
      case kHsaAiCounterBlockIdSqGs:
      case kHsaAiCounterBlockIdSqVs:
      case kHsaAiCounterBlockIdSqPs:
      case kHsaAiCounterBlockIdSqHs:
      case kHsaAiCounterBlockIdSqCs: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = AiSqCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = AiSqCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaAiCounterBlockIdCb: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = AiCbCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = AiCbCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      // Temp commented for Vega10
      /*
      case kHsaAiCounterBlockIdCpf: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = AiCpfCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = AiCpfCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      */
      case kHsaAiCounterBlockIdDb: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = AiDbCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = AiDbCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaAiCounterBlockIdGrbm: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = AiGrbmCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = AiGrbmCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      case kHsaAiCounterBlockIdGrbmSe: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = AiGrbmSeCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = AiGrbmSeCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      case kHsaAiCounterBlockIdPaSu: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = AiPaSuCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = AiPaSuCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaAiCounterBlockIdPaSc: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = AiPaScCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = AiPaScCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaAiCounterBlockIdSpi: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = AiSpiCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = AiSpiCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaAiCounterBlockIdSx: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = AiSxCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = AiSxCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaAiCounterBlockIdTa: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = AiTaCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = AiTaCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaAiCounterBlockIdTca: {
        grbm_gfx_index.u32All = 0;
        grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
        grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
        grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

        reg_addr[reg_num] = mmGRBM_GFX_INDEX;
        reg_val[reg_num] = grbm_gfx_index.u32All;
        reg_num++;

        reg_addr[reg_num] = AiTcaCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = AiTcaCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      case kHsaAiCounterBlockIdTcc: {
        grbm_gfx_index.u32All = 0;
        grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
        grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
        grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

        reg_addr[reg_num] = mmGRBM_GFX_INDEX;
        reg_val[reg_num] = grbm_gfx_index.u32All;
        reg_num++;

        reg_addr[reg_num] = AiTccCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = AiTccCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      case kHsaAiCounterBlockIdTd: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = AiTdCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = AiTdCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaAiCounterBlockIdTcp: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = AiTcpCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = AiTcpCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaAiCounterBlockIdGds: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = AiGdsCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = AiGdsCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      case kHsaAiCounterBlockIdVgt: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = AiVgtCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = AiVgtCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaAiCounterBlockIdIa: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = AiIaCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = AiIaCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      /*
      case kHsaAiCounterBlockIdMc: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = AiMcCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = AiMcCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      */
      // Temp Commented out for Vega10
      /*
      case kHsaAiCounterBlockIdSrbm: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = AiSrbmCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = AiSrbmCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      */
      /*
      case kHsaAiCounterBlockIdTcs: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = AiTcsCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = AiTcsCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      */
      case kHsaAiCounterBlockIdWd: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = AiWdCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = AiWdCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }

      // Temp commented for Vega10
      /*
      case kHsaAiCounterBlockIdCpg: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = AiCpgCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = AiCpgCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      */
      case kHsaAiCounterBlockIdCpc: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = AiCpcCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = AiCpcCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      // IommuV2, MC, kernel driver counters are retrieved via
      // KFD implementation
      case kHsaAiCounterBlockIdMc:
      case kHsaAiCounterBlockIdIommuV2:
      case kHsaAiCounterBlockIdKernelDriver: {
        reg_num = 0;
        break;
      }
      default: { break; }
    }

    return reg_num;
  }
};

}  // namespace pm4_builder

#endif  // _GFX9_PMC_BUILDER_H_
