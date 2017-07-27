#ifndef _GFX9_BLOCKTABLE_H_
#define _GFX9_BLOCKTABLE_H_

/*
 * The following tables contain register addresses of the SQ counter registers
 */

/*
 * SQ
 */
static const CounterRegInfo AiSqCounterRegAddr[] = {
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
    {mmSQ_PERFCOUNTER10_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER10_LO,
     mmSQ_PERFCOUNTER10_HI},
    {mmSQ_PERFCOUNTER11_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER11_LO,
     mmSQ_PERFCOUNTER11_HI},
    {mmSQ_PERFCOUNTER12_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER12_LO,
     mmSQ_PERFCOUNTER12_HI},
    {mmSQ_PERFCOUNTER13_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER13_LO,
     mmSQ_PERFCOUNTER13_HI},
    {mmSQ_PERFCOUNTER14_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER14_LO,
     mmSQ_PERFCOUNTER14_HI},
    {mmSQ_PERFCOUNTER15_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER15_LO,
     mmSQ_PERFCOUNTER15_HI}};

/*
 * DRMDMA
 */
static const CounterRegInfo AiDrmdmaCounterRegAddr[] = {
    {mmSDMA0_PERFMON_CNTL, 0, mmSDMA0_PERFCOUNTER0_RESULT, 0},
    {mmSDMA0_PERFMON_CNTL, 0, mmSDMA0_PERFCOUNTER1_RESULT, 0},
    {mmSDMA1_PERFMON_CNTL, 0, mmSDMA1_PERFCOUNTER0_RESULT, 0},
    {mmSDMA1_PERFMON_CNTL, 0, mmSDMA1_PERFCOUNTER1_RESULT, 0},
};

/*
 * IH
 */
static const CounterRegInfo AiIhCounterRegAddr[] = {
    {mmIH_PERFMON_CNTL, 0, mmIH_PERFCOUNTER0_RESULT, 0},
    {mmIH_PERFMON_CNTL, 0, mmIH_PERFCOUNTER1_RESULT, 0}};

/*
 * CPF
 */
static const CounterRegInfo AiCpfCounterRegAddr[] = {
    {mmCPF_PERFCOUNTER0_SELECT, 0, mmCPF_PERFCOUNTER0_LO, mmCPF_PERFCOUNTER0_HI},
    {mmCPF_PERFCOUNTER1_SELECT, 0, mmCPF_PERFCOUNTER1_LO, mmCPF_PERFCOUNTER1_HI}};

/*
 * DRM
 */
static const CounterRegInfo AiDrmCounterRegAddr[] = {
    /*
    {mmDRM_PERFCOUNTER1_SELECT, 0, mmDRM_PERFCOUNTER1_LO, mmDRM_PERFCOUNTER1_HI},
    {mmDRM_PERFCOUNTER2_SELECT, 0, mmDRM_PERFCOUNTER2_LO, mmDRM_PERFCOUNTER2_HI}
    */
};

/*
 * GRBM
 */
static const CounterRegInfo AiGrbmCounterRegAddr[] = {
    {mmGRBM_PERFCOUNTER0_SELECT, 0, mmGRBM_PERFCOUNTER0_LO, mmGRBM_PERFCOUNTER0_HI},
    {mmGRBM_PERFCOUNTER1_SELECT, 0, mmGRBM_PERFCOUNTER1_LO, mmGRBM_PERFCOUNTER1_HI}};

/*
 * GRBM_SE
 */
static const CounterRegInfo AiGrbmSeCounterRegAddr[] = {
    {mmGRBM_SE0_PERFCOUNTER_SELECT, 0, mmGRBM_SE0_PERFCOUNTER_LO, mmGRBM_SE0_PERFCOUNTER_HI},
    {mmGRBM_SE1_PERFCOUNTER_SELECT, 0, mmGRBM_SE1_PERFCOUNTER_LO, mmGRBM_SE1_PERFCOUNTER_HI},
    {mmGRBM_SE2_PERFCOUNTER_SELECT, 0, mmGRBM_SE2_PERFCOUNTER_LO, mmGRBM_SE2_PERFCOUNTER_HI},
    {mmGRBM_SE3_PERFCOUNTER_SELECT, 0, mmGRBM_SE3_PERFCOUNTER_LO, mmGRBM_SE3_PERFCOUNTER_HI}};

/*
 * SPI
 */
static const CounterRegInfo AiSpiCounterRegAddr[] = {
    {mmSPI_PERFCOUNTER0_SELECT, 0, mmSPI_PERFCOUNTER0_LO, mmSPI_PERFCOUNTER0_HI},
    {mmSPI_PERFCOUNTER1_SELECT, 0, mmSPI_PERFCOUNTER1_LO, mmSPI_PERFCOUNTER1_HI},
    {mmSPI_PERFCOUNTER2_SELECT, 0, mmSPI_PERFCOUNTER2_LO, mmSPI_PERFCOUNTER2_HI},
    {mmSPI_PERFCOUNTER3_SELECT, 0, mmSPI_PERFCOUNTER3_LO, mmSPI_PERFCOUNTER3_HI},
    {mmSPI_PERFCOUNTER4_SELECT, 0, mmSPI_PERFCOUNTER4_LO, mmSPI_PERFCOUNTER4_HI},
    {mmSPI_PERFCOUNTER5_SELECT, 0, mmSPI_PERFCOUNTER5_LO, mmSPI_PERFCOUNTER5_HI}};

/*
 * TCA
 */
static const CounterRegInfo AiTcaCounterRegAddr[] = {
    {mmTCA_PERFCOUNTER0_SELECT, 0, mmTCA_PERFCOUNTER0_LO, mmTCA_PERFCOUNTER0_HI},
    {mmTCA_PERFCOUNTER1_SELECT, 0, mmTCA_PERFCOUNTER1_LO, mmTCA_PERFCOUNTER1_HI},
    {mmTCA_PERFCOUNTER2_SELECT, 0, mmTCA_PERFCOUNTER2_LO, mmTCA_PERFCOUNTER2_HI},
    {mmTCA_PERFCOUNTER3_SELECT, 0, mmTCA_PERFCOUNTER3_LO, mmTCA_PERFCOUNTER3_HI}};

/*
 * TCC
 */
static const CounterRegInfo AiTccCounterRegAddr[] = {
    {mmTCC_PERFCOUNTER0_SELECT, 0, mmTCC_PERFCOUNTER0_LO, mmTCC_PERFCOUNTER0_HI},
    {mmTCC_PERFCOUNTER1_SELECT, 0, mmTCC_PERFCOUNTER1_LO, mmTCC_PERFCOUNTER1_HI},
    {mmTCC_PERFCOUNTER2_SELECT, 0, mmTCC_PERFCOUNTER2_LO, mmTCC_PERFCOUNTER2_HI},
    {mmTCC_PERFCOUNTER3_SELECT, 0, mmTCC_PERFCOUNTER3_LO, mmTCC_PERFCOUNTER3_HI}};

/*
 * TCP
 */
static const CounterRegInfo AiTcpCounterRegAddr[] = {
    {mmTCP_PERFCOUNTER0_SELECT, 0, mmTCP_PERFCOUNTER0_LO, mmTCP_PERFCOUNTER0_HI},
    {mmTCP_PERFCOUNTER1_SELECT, 0, mmTCP_PERFCOUNTER1_LO, mmTCP_PERFCOUNTER1_HI},
    {mmTCP_PERFCOUNTER2_SELECT, 0, mmTCP_PERFCOUNTER2_LO, mmTCP_PERFCOUNTER2_HI},
    {mmTCP_PERFCOUNTER3_SELECT, 0, mmTCP_PERFCOUNTER3_LO, mmTCP_PERFCOUNTER3_HI}};

/*
 * RLC
 */
static const CounterRegInfo AiRlcCounterRegAddr[] = {
    {mmRLC_PERFCOUNTER0_SELECT, 0, mmRLC_PERFCOUNTER0_LO, mmRLC_PERFCOUNTER0_HI},
    {mmRLC_PERFCOUNTER1_SELECT, 0, mmRLC_PERFCOUNTER1_LO, mmRLC_PERFCOUNTER1_HI}};

/*
 * SC
 */
static const CounterRegInfo AiScCounterRegAddr[] = {
    {mmPA_SC_PERFCOUNTER0_SELECT, 0, mmPA_SC_PERFCOUNTER0_LO, mmPA_SC_PERFCOUNTER0_HI},
    {mmPA_SC_PERFCOUNTER1_SELECT, 0, mmPA_SC_PERFCOUNTER1_LO, mmPA_SC_PERFCOUNTER1_HI},
    {mmPA_SC_PERFCOUNTER2_SELECT, 0, mmPA_SC_PERFCOUNTER2_LO, mmPA_SC_PERFCOUNTER2_HI},
    {mmPA_SC_PERFCOUNTER3_SELECT, 0, mmPA_SC_PERFCOUNTER3_LO, mmPA_SC_PERFCOUNTER3_HI},
    {mmPA_SC_PERFCOUNTER4_SELECT, 0, mmPA_SC_PERFCOUNTER4_LO, mmPA_SC_PERFCOUNTER4_HI},
    {mmPA_SC_PERFCOUNTER5_SELECT, 0, mmPA_SC_PERFCOUNTER5_LO, mmPA_SC_PERFCOUNTER5_HI},
    {mmPA_SC_PERFCOUNTER6_SELECT, 0, mmPA_SC_PERFCOUNTER6_LO, mmPA_SC_PERFCOUNTER6_HI},
    {mmPA_SC_PERFCOUNTER7_SELECT, 0, mmPA_SC_PERFCOUNTER7_LO, mmPA_SC_PERFCOUNTER7_HI}};

/*
 * SX
 */
static const CounterRegInfo AiSxCounterRegAddr[] = {
    {mmSX_PERFCOUNTER0_SELECT, 0, mmSX_PERFCOUNTER0_LO, mmSX_PERFCOUNTER0_HI},
    {mmSX_PERFCOUNTER1_SELECT, 0, mmSX_PERFCOUNTER1_LO, mmSX_PERFCOUNTER1_HI},
    {mmSX_PERFCOUNTER2_SELECT, 0, mmSX_PERFCOUNTER2_LO, mmSX_PERFCOUNTER2_HI},
    {mmSX_PERFCOUNTER3_SELECT, 0, mmSX_PERFCOUNTER3_LO, mmSX_PERFCOUNTER3_HI}};

/*
 * TA
 */
static const CounterRegInfo AiTaCounterRegAddr[] = {
    {mmTA_PERFCOUNTER0_SELECT, 0, mmTA_PERFCOUNTER0_LO, mmTA_PERFCOUNTER0_HI},
    {mmTA_PERFCOUNTER1_SELECT, 0, mmTA_PERFCOUNTER1_LO, mmTA_PERFCOUNTER1_HI}};

/*
 * TD
 */
static const CounterRegInfo AiTdCounterRegAddr[] = {
    {mmTD_PERFCOUNTER0_SELECT, 0, mmTD_PERFCOUNTER0_LO, mmTD_PERFCOUNTER0_HI},
    {mmTD_PERFCOUNTER1_SELECT, 0, mmTD_PERFCOUNTER1_LO, mmTD_PERFCOUNTER1_HI}};

/*
 * GDS
 */
static const CounterRegInfo AiGdsCounterRegAddr[] = {
    {mmGDS_PERFCOUNTER0_SELECT, 0, mmGDS_PERFCOUNTER0_LO, mmGDS_PERFCOUNTER0_HI},
    {mmGDS_PERFCOUNTER1_SELECT, 0, mmGDS_PERFCOUNTER1_LO, mmGDS_PERFCOUNTER1_HI},
    {mmGDS_PERFCOUNTER2_SELECT, 0, mmGDS_PERFCOUNTER2_LO, mmGDS_PERFCOUNTER2_HI},
    {mmGDS_PERFCOUNTER3_SELECT, 0, mmGDS_PERFCOUNTER3_LO, mmGDS_PERFCOUNTER3_HI}};

/*
 * IA
 */
static const CounterRegInfo AiIaCounterRegAddr[] = {
    {mmIA_PERFCOUNTER0_SELECT, 0, mmIA_PERFCOUNTER0_LO, mmIA_PERFCOUNTER0_HI},
    {mmIA_PERFCOUNTER1_SELECT, 0, mmIA_PERFCOUNTER1_LO, mmIA_PERFCOUNTER1_HI},
    {mmIA_PERFCOUNTER2_SELECT, 0, mmIA_PERFCOUNTER2_LO, mmIA_PERFCOUNTER2_HI},
    {mmIA_PERFCOUNTER3_SELECT, 0, mmIA_PERFCOUNTER3_LO, mmIA_PERFCOUNTER3_HI}};

/*
 * MC
 */
static const CounterRegInfo AiMcCounterRegAddr[] = {
    /*

    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, 0, mmMC_SEQ_PERF_SEQ_CNT_A_I0__VI,
     mmMC_SEQ_PERF_SEQ_CNT_A_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, 0, mmMC_SEQ_PERF_SEQ_CNT_B_I0__VI,
     mmMC_SEQ_PERF_SEQ_CNT_B_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, 0, mmMC_SEQ_PERF_SEQ_CNT_C_I0__VI,
     mmMC_SEQ_PERF_SEQ_CNT_C_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, 0, mmMC_SEQ_PERF_SEQ_CNT_D_I0__VI,
     mmMC_SEQ_PERF_SEQ_CNT_D_I1__VI}

     */
};

/*
 * SRBM
 */
static const CounterRegInfo AiSrbmCounterRegAddr[] = {
    /*
    {mmSRBM_PERFCOUNTER0_SELECT, 0, mmSRBM_PERFCOUNTER0_LO,
     mmSRBM_PERFCOUNTER0_HI},
    {mmSRBM_PERFCOUNTER1_SELECT, 0, mmSRBM_PERFCOUNTER1_LO,
     mmSRBM_PERFCOUNTER1_HI}
     */
};

/*
 * CPC
 */
static const CounterRegInfo AiCpcCounterRegAddr[] = {
    {mmCPC_PERFCOUNTER0_SELECT, 0, mmCPC_PERFCOUNTER0_LO, mmCPC_PERFCOUNTER0_HI},
    {mmCPC_PERFCOUNTER1_SELECT, 0, mmCPC_PERFCOUNTER1_LO, mmCPC_PERFCOUNTER1_HI}};

/**
 * Table containing CounterGroups which represent AI hardware blocks
 * as defined by \ref GpuBlockInfo structure
 */
// Temp commented for Vega10
// Counter block CPF
/*
static GpuBlockInfo AiCpfCounterBlockInfo = {"AI_CPF", kHsaAiCounterBlockIdCpf, 1, CntlMethodNone,
19, AI_COUNTER_NUM_PER_CPF, 0, 0, true, AiCpfCounterRegAddr, false,
gfx9_cntx_prim::select_value<regCPF_PERFCOUNTER0_SELECT>, false};
*/
// Counter block GRBM
static GpuBlockInfo AiGrbmCounterBlockInfo = {
    "AI_GRBM", kHsaAiCounterBlockIdGrbm,
    1,         CntlMethodNone,
    33,        AI_COUNTER_NUM_PER_GRBM,
    0,         0,
    true,      AiGrbmCounterRegAddr,
    false,     gfx9_cntx_prim::select_value<regGRBM_PERFCOUNTER0_SELECT>,
    false};
// Counter block GRBMSE
static GpuBlockInfo AiGrbmSeCounterBlockInfo = {
    "AI_GRBMSE", kHsaAiCounterBlockIdGrbmSe,
    1,           CntlMethodNone,
    14,          AI_COUNTER_NUM_PER_GRBMSE,
    0,           0,
    true,        AiGrbmSeCounterRegAddr,
    false,       gfx9_cntx_prim::select_value<regGRBM_SE0_PERFCOUNTER_SELECT>,
    false};
// Counter block SPI
static GpuBlockInfo AiSpiCounterBlockInfo = {
    "AI_SPI", kHsaAiCounterBlockIdSpi,
    1,        CntlMethodBySe,
    196,      AI_COUNTER_NUM_PER_SPI,
    0,        0,
    true,     AiSpiCounterRegAddr,
    false,    gfx9_cntx_prim::select_value<regSPI_PERFCOUNTER0_SELECT>,
    false};
// Counter block SQ
static GpuBlockInfo AiSqCounterBlockInfo = {
    "AI_SQ", kHsaAiCounterBlockIdSq, 1,     CntlMethodBySe,
    171,     AI_COUNTER_NUM_PER_SQ,  0,     0,
    true,    AiSqCounterRegAddr,     false, gfx9_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT>,
    true};
static GpuBlockInfo AiSqCsCounterBlockInfo = {
    "AI_SQ_CS", kHsaAiCounterBlockIdSqCs,
    1,          CntlMethodBySe,
    298,        AI_COUNTER_NUM_PER_SQ,
    0,          0,
    true,       AiSqCounterRegAddr,
    false,      gfx9_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT>,
    true};
// Counter block SX
static GpuBlockInfo AiSxCounterBlockInfo = {
    "AI_SX", kHsaAiCounterBlockIdSx, 1,    CntlMethodBySe,
    33,      AI_COUNTER_NUM_PER_SX,  0,    0,
    true,    AiSxCounterRegAddr,     true, gfx9_cntx_prim::select_value<regSX_PERFCOUNTER0_SELECT>,
    false};
// Counter block TA
static GpuBlockInfo AiTaCounterBlockInfo = {
    "AI_TA",   kHsaAiCounterBlockIdTa,
    AI_NUM_TA, CntlMethodBySeAndInstance,
    118,       AI_COUNTER_NUM_PER_TA,
    0,         0,
    true,      AiTaCounterRegAddr,
    false,     gfx9_cntx_prim::select_value<regTA_PERFCOUNTER0_SELECT>,
    false};
// Counter block TCA
static GpuBlockInfo AiTcaCounterBlockInfo = {
    "AI_TCA",   kHsaAiCounterBlockIdTca,
    AI_NUM_TCA, CntlMethodByInstance,
    34,         AI_COUNTER_NUM_PER_TCA,
    0,          0,
    true,       AiTcaCounterRegAddr,
    false,      gfx9_cntx_prim::select_value<regTCA_PERFCOUNTER0_SELECT>,
    false};
// Counter block TCC
static GpuBlockInfo AiTccCounterBlockInfo = {
    "AI_TCC",   kHsaAiCounterBlockIdTcc,
    AI_NUM_TCC, CntlMethodByInstance,
    191,        AI_COUNTER_NUM_PER_TCC,
    0,          0,
    true,       AiTccCounterRegAddr,
    false,      gfx9_cntx_prim::select_value<regTCC_PERFCOUNTER0_SELECT>,
    false};
// Counter block TD
static GpuBlockInfo AiTdCounterBlockInfo = {
    "AI_TD",   kHsaAiCounterBlockIdTd,
    AI_NUM_TD, CntlMethodBySeAndInstance,
    54,        AI_COUNTER_NUM_PER_TD,
    0,         0,
    true,      AiTdCounterRegAddr,
    false,     gfx9_cntx_prim::select_value<regTD_PERFCOUNTER0_SELECT>,
    false};
// Counter block TCP
static GpuBlockInfo AiTcpCounterBlockInfo = {
    "AI_TCP",   kHsaAiCounterBlockIdTcp,
    AI_NUM_TCP, CntlMethodBySeAndInstance,
    182,        AI_COUNTER_NUM_PER_TCP,
    0,          0,
    true,       AiTcpCounterRegAddr,
    false,      gfx9_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>,
    false};
// Counter block GDS
static GpuBlockInfo AiGdsCounterBlockInfo = {
    "AI_GDS", kHsaAiCounterBlockIdGds,
    1,        CntlMethodNone,
    120,      AI_COUNTER_NUM_PER_GDS,
    0,        0,
    true,     AiGdsCounterRegAddr,
    false,    gfx9_cntx_prim::select_value<regGDS_PERFCOUNTER0_SELECT>,
    false};
// Counter block IA
static GpuBlockInfo AiIaCounterBlockInfo = {
    "AI_IA", kHsaAiCounterBlockIdIa, 1,     CntlMethodBySe,
    23,      AI_COUNTER_NUM_PER_IA,  0,     0,
    true,    AiIaCounterRegAddr,     false, gfx9_cntx_prim::select_value<regIA_PERFCOUNTER0_SELECT>,
    false};
// Counter block MC
static GpuBlockInfo AiMcCounterBlockInfo = {
    "AI_MC", kHsaAiCounterBlockIdMc, 1,     CntlMethodNone, 22,   AI_COUNTER_NUM_PER_MC, 0, 0,
    true,    AiMcCounterRegAddr,     false, NULL,           false};
// Temp commented out for Vega10
// Counter block SRBM
/*
static GpuBlockInfo AiSrbmCounterBlockInfo = {"AI_SRBM", kHsaAiCounterBlockIdSrbm, 1,
CntlMethodNone, 19, AI_COUNTER_NUM_PER_SRBM, 0, 0, true, AiSrbmCounterRegAddr, false,
gfx9_cntx_prim::select_value<regSRBM_PERFCOUNTER0_SELECT>, false};
*/
// Counter block CPC
static GpuBlockInfo AiCpcCounterBlockInfo = {
    "AI_CPC", kHsaAiCounterBlockIdCpc,
    1,        CntlMethodNone,
    34,       AI_COUNTER_NUM_PER_CPC,
    0,        0,
    true,     AiCpcCounterRegAddr,
    false,    gfx9_cntx_prim::select_value<regCPC_PERFCOUNTER0_SELECT>,
    false};
// Counter block IOMMUV2
static GpuBlockInfo AiIommuV2CounterBlockInfo = {"AI_IOMMUV2",
                                                 kHsaAiCounterBlockIdIommuV2,
                                                 1,
                                                 CntlMethodNone,
                                                 25,
                                                 8,
                                                 0,
                                                 0,
                                                 true,
                                                 NULL,
                                                 false,
                                                 NULL,
                                                 false};
// Counter block KernelDriver
static GpuBlockInfo AiKernelDriverCounterBlockInfo = {"AI_KD", kHsaAiCounterBlockIdKernelDriver,
                                                      1,       CntlMethodNone,
                                                      0,       0,
                                                      0,       0,
                                                      true,    NULL,
                                                      false,   NULL,
                                                      false};

#endif  //  _GFX9_BLOCKTABLE_H_
