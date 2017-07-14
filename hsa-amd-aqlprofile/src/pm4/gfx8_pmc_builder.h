#ifndef _GFX8_PMC_BUILDER_H_
#define _GFX8_PMC_BUILDER_H_

#include <assert.h>
#include <stdint.h>

#include "pmc_builder.h"
#include "gfx8_cmd_builder.h"

#include "gfxip/gfx8/gfx8_block_info.h"
#include "gfxip/gfx8/si_ci_vi_merged_typedef.h"
#include "gfxip/gfx8/si_ci_vi_merged_offset.h"
#include "gfxip/gfx8/si_ci_vi_merged_enum.h"
#include "gfxip/gfx8/si_pm4defs.h"

namespace pm4_builder {
using namespace std;
using namespace pm4_builder;
using namespace gfxip::gfx8;

class Gfx8PmcBuilder : public pm4_builder::PmcBuilder, protected Gfx8CmdBuilder {
 public:
  void begin(CmdBuffer* cmdBuff, const counters_vector& countersVec) {
    // Reset Grbm to its default state - broadcast
    BuildWriteUConfigRegPacket(cmdBuff, mmGRBM_GFX_INDEX__CI__VI, grbm_reset_value());

    // Reset the counter list
    regCP_PERFMON_CNTL cp_perfmon_cntl = {0};
    BuildWriteUConfigRegPacket(cmdBuff, mmCP_PERFMON_CNTL__CI__VI, cp_perfmon_cntl.u32All);

    // Iterate through the list of blocks to generate Pm4 commands to
    // program corresponding perf counters of each block
    std::map<block_des_t, uint32_t, lt_block_des> index_map;
    for (counters_vector::const_iterator it = countersVec.begin(); it != countersVec.end(); ++it) {
      const block_des_t& block_des = it->first;
      const uint32_t& counter_id = it->second;

      auto ret = index_map.insert({block_des, 0});
      uint32_t& index = ret.first->second;

      std::cout << index << ": " << block_des.id << ", " << block_des.index << ", " << counter_id
                << std::endl;

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
    BuildWriteUConfigRegPacket(cmdBuff, mmGRBM_GFX_INDEX__CI__VI, grbm_reset_value());

    // Program Compute_Perfcount_Enable register to support perf counting
    regCOMPUTE_PERFCOUNT_ENABLE__CI__VI cp_perfcount_enable;
    cp_perfcount_enable.u32All = 0;
    cp_perfcount_enable.bits.PERFCOUNT_ENABLE = 1;
    BuildWriteShRegPacket(cmdBuff, mmCOMPUTE_PERFCOUNT_ENABLE__CI__VI, cp_perfcount_enable.u32All);

    // Reset the counter list
    BuildWriteUConfigRegPacket(cmdBuff, mmCP_PERFMON_CNTL__CI__VI, cp_perfmon_cntl.u32All);

    // Start the counter list
    cp_perfmon_cntl.bits.PERFMON_STATE = 1;
    BuildWriteUConfigRegPacket(cmdBuff, mmCP_PERFMON_CNTL__CI__VI, cp_perfmon_cntl.u32All);

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
    BuildWriteUConfigRegPacket(cmdBuff, mmCP_PERFMON_CNTL__CI__VI, cp_perfmon_cntl.u32All);

    // Reset Grbm to its default state - broadcast
    BuildWriteUConfigRegPacket(cmdBuff, mmGRBM_GFX_INDEX__CI__VI, grbm_reset_value());

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
    BuildWriteUConfigRegPacket(cmdBuff, mmGRBM_GFX_INDEX__CI__VI, grbm_reset_value());

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
    regAddr[regIdx] = mmGRBM_GFX_INDEX__CI__VI;
    regIdx++;

    regTCP_PERFCOUNTER0_SELECT__CI__VI tcp_perf_counter_select;
    tcp_perf_counter_select.u32All = 0;
    tcp_perf_counter_select.bits.PERF_SEL = blkCntrIdx;

    regVal[regIdx] = tcp_perf_counter_select.u32All;
    regAddr[regIdx] = ViTcpCounterRegAddr[tcpRegIdx].counterSelRegAddr;
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
    regAddr[regIdx] = mmGRBM_GFX_INDEX__CI__VI;
    regIdx++;

    regTD_PERFCOUNTER0_SELECT td_perf_counter_select;
    td_perf_counter_select.u32All = 0;
    td_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
    regVal[regIdx] = td_perf_counter_select.u32All;
    regAddr[regIdx] = ViTdCounterRegAddr[tdRegIdx].counterSelRegAddr;
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
    regAddr[regIdx] = mmGRBM_GFX_INDEX__CI__VI;
    regIdx++;

    regTCC_PERFCOUNTER0_SELECT__CI__VI tcc_perf_counter_select;
    tcc_perf_counter_select.u32All = 0;
    tcc_perf_counter_select.bits.PERF_SEL = blkCntrIdx;

    regVal[regIdx] = tcc_perf_counter_select.u32All;
    regAddr[regIdx] = ViTccCounterRegAddr[tccRegIdx].counterSelRegAddr;
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
    regAddr[regIdx] = mmGRBM_GFX_INDEX__CI__VI;
    regIdx++;

    regTCA_PERFCOUNTER0_SELECT__CI__VI tca_perf_counter_select;
    tca_perf_counter_select.u32All = 0;
    tca_perf_counter_select.bits.PERF_SEL = blkCntrIdx;

    regVal[regIdx] = tca_perf_counter_select.u32All;
    regAddr[regIdx] = ViTcaCounterRegAddr[tcaRegIdx].counterSelRegAddr;
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
    regAddr[regIdx] = mmGRBM_GFX_INDEX__CI__VI;
    regIdx++;

    regTA_PERFCOUNTER0_SELECT ta_perf_counter_select;
    ta_perf_counter_select.u32All = 0;
    ta_perf_counter_select.bits.PERF_SEL = blkCntrIdx;

    regVal[regIdx] = ta_perf_counter_select.u32All;
    regAddr[regIdx] = ViTaCounterRegAddr[taRegIdx].counterSelRegAddr;
    regIdx++;

    return regIdx;
  }

  uint32_t ProgramSQCntrs(uint32_t sqRegIdx, uint32_t* regAddr, uint32_t* regVal,
                          block_des_t block_des, uint32_t blkCntrIdx) {
    uint32_t regIdx = 0;

    // Program the SQ Counter Select Register
    regSQ_PERFCOUNTER0_SELECT__CI__VI sq_cntr_sel;
    sq_cntr_sel.u32All = 0;
    sq_cntr_sel.bits.SIMD_MASK = 0xF;
    sq_cntr_sel.bits.SQC_BANK_MASK = 0xF;
    sq_cntr_sel.bits.SQC_CLIENT_MASK = 0xF;
    sq_cntr_sel.bits.PERF_SEL = blkCntrIdx;
    regVal[regIdx] = sq_cntr_sel.u32All;
    regAddr[regIdx] = ViSqCounterRegAddr[sqRegIdx].counterSelRegAddr;
    regIdx++;

    // Program the SQ Counter Mask Register
    regSQ_PERFCOUNTER_MASK__CI__VI sq_cntr_mask;
    sq_cntr_mask.u32All = 0;
    sq_cntr_mask.bits.SH0_MASK = 0xFFFF;
    sq_cntr_mask.bits.SH1_MASK = 0xFFFF;
    regVal[regIdx] = sq_cntr_mask.u32All;
    regAddr[regIdx] = mmSQ_PERFCOUNTER_MASK__CI__VI;
    regIdx++;

    // Initialize the register content
    // Program the SQ Counter Control Register
    regSQ_PERFCOUNTER_CTRL sq_cntr_ctrl;
    sq_cntr_ctrl.u32All = 0;
    if (block_des.id == kHsaViCounterBlockIdSq) {
      sq_cntr_ctrl.bits.ES_EN = 0x1;
      sq_cntr_ctrl.bits.GS_EN = 0x1;
      sq_cntr_ctrl.bits.VS_EN = 0x1;
      sq_cntr_ctrl.bits.PS_EN = 0x1;
      sq_cntr_ctrl.bits.LS_EN = 0x1;
      sq_cntr_ctrl.bits.HS_EN = 0x1;
      sq_cntr_ctrl.bits.CS_EN = 0x1;
    } else if (block_des.id == kHsaViCounterBlockIdSqEs) {
      sq_cntr_ctrl.bits.ES_EN = 0x1;
    } else if (block_des.id == kHsaViCounterBlockIdSqGs) {
      sq_cntr_ctrl.bits.GS_EN = 0x1;
    } else if (block_des.id == kHsaViCounterBlockIdSqVs) {
      sq_cntr_ctrl.bits.VS_EN = 0x1;
    } else if (block_des.id == kHsaViCounterBlockIdSqPs) {
      sq_cntr_ctrl.bits.PS_EN = 0x1;
    } else if (block_des.id == kHsaViCounterBlockIdSqLs) {
      sq_cntr_ctrl.bits.LS_EN = 0x1;
    } else if (block_des.id == kHsaViCounterBlockIdSqHs) {
      sq_cntr_ctrl.bits.HS_EN = 0x1;
    } else if (block_des.id == kHsaViCounterBlockIdSqCs) {
      sq_cntr_ctrl.bits.CS_EN = 0x1;
    }

    regVal[regIdx] = sq_cntr_ctrl.u32All;
    regAddr[regIdx] = ViSqCounterRegAddr[sqRegIdx].counterCntlRegAddr;
    regIdx++;

    return regIdx;
  }

  uint32_t BuildCounterSelRegister(uint32_t cntrIdx, uint32_t* regAddr, uint32_t* regVal,
                                   block_des_t block_des, uint32_t blkCntrIdx) {
    const uint32_t block_id = block_des.id;
    const uint32_t instance_index = block_des.index;
    regGRBM_GFX_INDEX grbm_gfx_index = {0};
    uint32_t regIdx = 0;

    switch (block_id) {
      // Program counters belonging to SQ block
      case kHsaViCounterBlockIdSq:
      case kHsaViCounterBlockIdSqEs:
      case kHsaViCounterBlockIdSqGs:
      case kHsaViCounterBlockIdSqVs:
      case kHsaViCounterBlockIdSqPs:
      case kHsaViCounterBlockIdSqLs:
      case kHsaViCounterBlockIdSqHs:
      case kHsaViCounterBlockIdSqCs:
        return ProgramSQCntrs(cntrIdx, regAddr, regVal, block_des, blkCntrIdx);
      case kHsaViCounterBlockIdCb: {
        regIdx = 0;
        grbm_gfx_index.u32All = 0;
        grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
        grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
        grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

        regVal[regIdx] = grbm_gfx_index.u32All;
        regAddr[regIdx] = mmGRBM_GFX_INDEX__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER0_LO__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER0_HI__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER1_LO__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER1_HI__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER2_LO__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER2_HI__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER3_LO__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmCB_PERFCOUNTER3_HI__CI__VI;
        regIdx++;

        regCB_PERFCOUNTER0_SELECT__CI__VI cb_perf_counter_select;
        cb_perf_counter_select.u32All = 0;
        cb_perf_counter_select.bits.PERF_SEL = blkCntrIdx;

        regVal[regIdx] = cb_perf_counter_select.u32All;
        regAddr[regIdx] = ViCbCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx++;

        break;
      }
      case kHsaViCounterBlockIdCpf: {
        regCPF_PERFCOUNTER0_SELECT__CI__VI cpf_perf_counter_select;
        cpf_perf_counter_select.u32All = 0;
        cpf_perf_counter_select.bits.PERF_SEL = blkCntrIdx;

        regVal[0] = cpf_perf_counter_select.u32All;
        regAddr[0] = ViCpfCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaViCounterBlockIdDb: {
        regIdx = 0;
        grbm_gfx_index.u32All = 0;
        grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
        grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
        grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

        regVal[regIdx] = grbm_gfx_index.u32All;
        regAddr[regIdx] = mmGRBM_GFX_INDEX__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER0_LO__CI__VI;
        regIdx++;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER0_HI__CI__VI;
        regIdx++;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER1_LO__CI__VI;
        regIdx++;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER1_HI__CI__VI;
        regIdx++;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER2_LO__CI__VI;
        regIdx++;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER2_HI__CI__VI;
        regIdx++;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER3_LO__CI__VI;
        regIdx++;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmDB_PERFCOUNTER3_HI__CI__VI;
        regIdx++;

        regDB_PERFCOUNTER0_SELECT db_perf_counter_select;
        db_perf_counter_select.u32All = 0;
        db_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[regIdx] = db_perf_counter_select.u32All;
        regAddr[regIdx] = ViDbCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx++;
        break;
      }
      case kHsaViCounterBlockIdGrbm: {
        regGRBM_PERFCOUNTER0_SELECT grbm_perf_counter_select;
        grbm_perf_counter_select.u32All = 0;
        grbm_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = grbm_perf_counter_select.u32All;
        regAddr[0] = ViGrbmCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaViCounterBlockIdGrbmSe: {
        regGRBM_SE0_PERFCOUNTER_SELECT grbm_se0_perf_counter_select;
        grbm_se0_perf_counter_select.u32All = 0;
        grbm_se0_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = grbm_se0_perf_counter_select.u32All;
        regAddr[0] = ViGrbmSeCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaViCounterBlockIdPaSu: {
        regPA_SU_PERFCOUNTER0_SELECT pa_su_perf_counter_select;
        pa_su_perf_counter_select.u32All = 0;
        pa_su_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = pa_su_perf_counter_select.u32All;
        regAddr[0] = ViPaSuCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaViCounterBlockIdPaSc: {
        regPA_SC_PERFCOUNTER0_SELECT pa_sc_perf_counter_select;
        pa_sc_perf_counter_select.u32All = 0;
        pa_sc_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = pa_sc_perf_counter_select.u32All;
        regAddr[0] = ViPaScCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaViCounterBlockIdSpi: {
        regSPI_PERFCOUNTER0_SELECT spi_perf_counter_select;
        spi_perf_counter_select.u32All = 0;
        spi_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = spi_perf_counter_select.u32All;
        regAddr[0] = ViSpiCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaViCounterBlockIdSx: {
        regIdx = 0;
        regVal[regIdx] = 0;
        regAddr[regIdx] = mmSX_PERFCOUNTER0_LO__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmSX_PERFCOUNTER0_HI__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmSX_PERFCOUNTER1_LO__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmSX_PERFCOUNTER1_HI__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmSX_PERFCOUNTER2_LO__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmSX_PERFCOUNTER2_HI__CI__VI;
        regIdx++;

        regVal[regIdx] = 0;
        regAddr[regIdx] = mmSX_PERFCOUNTER3_LO__CI__VI;
        regIdx++;

        regSX_PERFCOUNTER0_SELECT sx_perf_counter_select;
        sx_perf_counter_select.u32All = 0;
        sx_perf_counter_select.bits.PERFCOUNTER_SELECT = blkCntrIdx;
        regVal[regIdx] = sx_perf_counter_select.u32All;
        regAddr[regIdx] = ViSxCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx++;
        break;
      }
      case kHsaViCounterBlockIdTa:
        return ProgramTaCntrs(cntrIdx, regAddr, regVal, block_des, blkCntrIdx);
      case kHsaViCounterBlockIdTca:
        return ProgramTcaCntrs(cntrIdx, regAddr, regVal, block_des, blkCntrIdx);
      case kHsaViCounterBlockIdTcc:
        return ProgramTccCntrs(cntrIdx, regAddr, regVal, block_des, blkCntrIdx);
      case kHsaViCounterBlockIdTd:
        return ProgramTdCntrs(cntrIdx, regAddr, regVal, block_des, blkCntrIdx);
      case kHsaViCounterBlockIdTcp:
        return ProgramTcpCntrs(cntrIdx, regAddr, regVal, block_des, blkCntrIdx);
      case kHsaViCounterBlockIdGds: {
        regGDS_PERFCOUNTER0_SELECT gds_perf_counter_select;
        gds_perf_counter_select.u32All = 0;
        gds_perf_counter_select.bits.PERFCOUNTER_SELECT = blkCntrIdx;
        regVal[0] = gds_perf_counter_select.u32All;
        regAddr[0] = ViGdsCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaViCounterBlockIdVgt: {
        regVGT_PERFCOUNTER0_SELECT__CI__VI vgt_perf_counter_select;
        vgt_perf_counter_select.u32All = 0;
        vgt_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = vgt_perf_counter_select.u32All;
        regAddr[0] = ViVgtCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaViCounterBlockIdIa: {
        regIA_PERFCOUNTER0_SELECT__CI__VI ia_perf_counter_select;
        ia_perf_counter_select.u32All = 0;
        ia_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = ia_perf_counter_select.u32All;
        regAddr[0] = ViIaCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      /*
          case kHsaViCounterBlockIdMc: {
            // To be investigated later
            //regMC_SEQ_PERF_SEQ_CTL mc_perfcounter_select;
            //mc_perfcounter_select.u32All = 0;
            //mc_perfcounter_select.bits.PERF_SEL = blkCntrIdx;
            //regVal[0] = mc_perfcounter_select.u32All;
            //regAddr[0] = ViMcCounterRegAddr[cntrIdx].counterSelRegAddr;
            //regIdx = 1;
          }
          break;
      */
      case kHsaViCounterBlockIdSrbm: {
        regSRBM_PERFCOUNTER0_SELECT srbm_perf_counter_select;
        srbm_perf_counter_select.u32All = 0;
        srbm_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = srbm_perf_counter_select.u32All;
        regAddr[0] = ViSrbmCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      /*
          case kHsaViCounterBlockIdTcs: {
            regTCS_PERFCOUNTER0_SELECT__CI tcs_perf_counter_select;
            tcs_perf_counter_select.u32All = 0;
            tcs_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
            regVal[0] = tcs_perf_counter_select.u32All;
            regAddr[0] = ViTcsCounterRegAddr[cntrIdx].counterSelRegAddr;
            regIdx = 1;
            break;
          }
      */
      case kHsaViCounterBlockIdWd: {
        regWD_PERFCOUNTER0_SELECT__CI__VI wd_perf_counter_select;
        wd_perf_counter_select.u32All = 0;
        wd_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = wd_perf_counter_select.u32All;
        regAddr[0] = ViWdCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaViCounterBlockIdCpg: {
        regCPG_PERFCOUNTER0_SELECT__CI__VI cpg_perf_counter_select;
        cpg_perf_counter_select.u32All = 0;
        cpg_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = cpg_perf_counter_select.u32All;
        regAddr[0] = ViCpgCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      case kHsaViCounterBlockIdCpc: {
        regCPC_PERFCOUNTER0_SELECT__CI__VI cpc_perf_counter_select;
        cpc_perf_counter_select.u32All = 0;
        cpc_perf_counter_select.bits.PERF_SEL = blkCntrIdx;
        regVal[0] = cpc_perf_counter_select.u32All;
        regAddr[0] = ViCpcCounterRegAddr[cntrIdx].counterSelRegAddr;
        regIdx = 1;
        break;
      }
      /*
      case kHsaViCounterBlockIdMc: {
        AddPriviledgedCountersToList(ViBlockIdMc, blkCntrIdx);
        //Num of regs equals to 0 means it is processed by KFD
        regIdx = 0;
        break;
      }
      case kHsaViCounterBlockIdIommuV2: {
        AddPriviledgedCountersToList(ViBlockIdIommuV2, blkCntrIdx);
        //Num of regs equals to 0 means it is processed by KFD
        regIdx = 0;
        break;
      }
      case kHsaViCounterBlockIdKernelDriver: {
        AddPriviledgedCountersToList(ViBlockIdKernelDriver, blkCntrIdx);
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
      case kHsaViCounterBlockIdSq:
      case kHsaViCounterBlockIdSqEs:
      case kHsaViCounterBlockIdSqGs:
      case kHsaViCounterBlockIdSqVs:
      case kHsaViCounterBlockIdSqPs:
      case kHsaViCounterBlockIdSqLs:
      case kHsaViCounterBlockIdSqHs:
      case kHsaViCounterBlockIdSqCs: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = ViSqCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = ViSqCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaViCounterBlockIdCb: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = ViCbCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = ViCbCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaViCounterBlockIdCpf: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = ViCpfCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = ViCpfCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      case kHsaViCounterBlockIdDb: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = ViDbCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = ViDbCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaViCounterBlockIdGrbm: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = ViGrbmCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = ViGrbmCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      case kHsaViCounterBlockIdGrbmSe: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = ViGrbmSeCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = ViGrbmSeCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      case kHsaViCounterBlockIdPaSu: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = ViPaSuCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = ViPaSuCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaViCounterBlockIdPaSc: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = ViPaScCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = ViPaScCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaViCounterBlockIdSpi: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = ViSpiCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = ViSpiCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaViCounterBlockIdSx: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = ViSxCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = ViSxCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaViCounterBlockIdTa: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = ViTaCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = ViTaCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaViCounterBlockIdTca: {
        grbm_gfx_index.u32All = 0;
        grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
        grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
        grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

        reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
        reg_val[reg_num] = grbm_gfx_index.u32All;
        reg_num++;

        reg_addr[reg_num] = ViTcaCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = ViTcaCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      case kHsaViCounterBlockIdTcc: {
        grbm_gfx_index.u32All = 0;
        grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
        grbm_gfx_index.bitfields.SE_BROADCAST_WRITES = 1;
        grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
        reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
        reg_val[reg_num] = grbm_gfx_index.u32All;
        reg_num++;

        reg_addr[reg_num] = ViTccCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = ViTccCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      case kHsaViCounterBlockIdTd: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;
          reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = ViTdCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = ViTdCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaViCounterBlockIdTcp: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_INDEX = instance_index;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = ViTcpCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = ViTcpCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaViCounterBlockIdGds: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = ViGdsCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = ViGdsCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      case kHsaViCounterBlockIdVgt: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = ViVgtCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = ViVgtCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      case kHsaViCounterBlockIdIa: {
        for (ii = 0; ii < se_number_; ii++) {
          grbm_gfx_index.u32All = 0;
          grbm_gfx_index.bitfields.INSTANCE_BROADCAST_WRITES = 1;
          grbm_gfx_index.bitfields.SE_INDEX = ii;
          grbm_gfx_index.bitfields.SH_BROADCAST_WRITES = 1;

          reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
          reg_val[reg_num] = grbm_gfx_index.u32All;
          reg_num++;

          reg_addr[reg_num] = ViIaCounterRegAddr[reg_index].counterReadRegAddrLo;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;

          reg_addr[reg_num] = ViIaCounterRegAddr[reg_index].counterReadRegAddrHi;
          reg_val[reg_num] = COPY_DATA_FLAG;
          reg_num++;
        }
        break;
      }
      /*
          case kHsaViCounterBlockIdMc: {
            reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
            reg_val[reg_num] = grbm_reset_value();
            reg_num++;

            reg_addr[reg_num] = ViMcCounterRegAddr[reg_index].counterReadRegAddrLo;
            reg_val[reg_num] = COPY_DATA_FLAG;
            reg_num++;

            reg_addr[reg_num] = ViMcCounterRegAddr[reg_index].counterReadRegAddrHi;
            reg_val[reg_num] = COPY_DATA_FLAG;
            reg_num++;
            break;
          }
      */
      case kHsaViCounterBlockIdSrbm: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = ViSrbmCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = ViSrbmCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      /*
          case kHsaViCounterBlockIdTcs: {
            reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
            reg_val[reg_num] = grbm_reset_value();
            reg_num++;

            reg_addr[reg_num] = ViTcsCounterRegAddr[reg_index].counterReadRegAddrLo;
            reg_val[reg_num] = COPY_DATA_FLAG;
            reg_num++;

            reg_addr[reg_num] = ViTcsCounterRegAddr[reg_index].counterReadRegAddrHi;
            reg_val[reg_num] = COPY_DATA_FLAG;
            reg_num++;
            break;
          }
      */
      case kHsaViCounterBlockIdWd: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = ViWdCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = ViWdCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      case kHsaViCounterBlockIdCpg: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = ViCpgCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = ViCpgCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }
      case kHsaViCounterBlockIdCpc: {
        reg_addr[reg_num] = mmGRBM_GFX_INDEX__CI__VI;
        reg_val[reg_num] = grbm_reset_value();
        reg_num++;

        reg_addr[reg_num] = ViCpcCounterRegAddr[reg_index].counterReadRegAddrLo;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;

        reg_addr[reg_num] = ViCpcCounterRegAddr[reg_index].counterReadRegAddrHi;
        reg_val[reg_num] = COPY_DATA_FLAG;
        reg_num++;
        break;
      }

      // IommuV2, MC, kernel driver counters are retrieved via
      // KFD implementation
      case kHsaViCounterBlockIdMc:
      case kHsaViCounterBlockIdIommuV2:
      case kHsaViCounterBlockIdKernelDriver: {
        reg_num = 0;
        break;
      }

      default: { break; }
    }

    return reg_num;
  }
};

}  // namespace pm4_builder

#endif  // _GFX8_PMC_BUILDER_H_
