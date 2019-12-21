#ifndef _GFX8_BLOCKTABLE_H_
#define _GFX8_BLOCKTABLE_H_
/*
 * The following tables contain register addresses of the SQ counter registers
 */

/*
 * SQ
 */
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

static const BlockDelayInfo SqBlockDelayInfo[] = {
    {mmRLC_SPM_SQG_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013},
    {mmRLC_SPM_SQG_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f},
    {mmRLC_SPM_SQG_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015},
    {mmRLC_SPM_SQG_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013},
};

/*
 * IH
 */
static const CounterRegInfo IhCounterRegAddr[] = {
    {mmIH_PERFMON_CNTL__VI, 0, mmIH_PERFCOUNTER0_RESULT__VI, 0},
    {mmIH_PERFMON_CNTL__VI, 0, mmIH_PERFCOUNTER1_RESULT__VI, 0}};

/*
 * CPF
 */
static const CounterRegInfo CpfCounterRegAddr[] = {
    {mmCPF_PERFCOUNTER0_SELECT__CI__VI, 0, mmCPF_PERFCOUNTER0_LO__CI__VI, mmCPF_PERFCOUNTER0_HI__CI__VI},
    {mmCPF_PERFCOUNTER1_SELECT__CI__VI, 0, mmCPF_PERFCOUNTER1_LO__CI__VI, mmCPF_PERFCOUNTER1_HI__CI__VI}};

static const BlockDelayInfo CpfBlockDelayInfo[] = {
    { mmRLC_SPM_CPF_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000019 }
};

/*
 * GRBM
 */
static const CounterRegInfo GrbmCounterRegAddr[] = {
    {mmGRBM_PERFCOUNTER0_SELECT__CI__VI, 0, mmGRBM_PERFCOUNTER0_LO__CI__VI, mmGRBM_PERFCOUNTER0_HI__CI__VI},
    {mmGRBM_PERFCOUNTER1_SELECT__CI__VI, 0, mmGRBM_PERFCOUNTER1_LO__CI__VI, mmGRBM_PERFCOUNTER1_HI__CI__VI}};

/*
 * GRBM_SE
 */
static const CounterRegInfo GrbmSeCounterRegAddr[] = {
    {mmGRBM_SE0_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE0_PERFCOUNTER_LO__CI__VI, mmGRBM_SE0_PERFCOUNTER_HI__CI__VI},
    {mmGRBM_SE1_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE1_PERFCOUNTER_LO__CI__VI, mmGRBM_SE1_PERFCOUNTER_HI__CI__VI},
    {mmGRBM_SE2_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE2_PERFCOUNTER_LO__CI__VI, mmGRBM_SE2_PERFCOUNTER_HI__CI__VI},
    {mmGRBM_SE3_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE3_PERFCOUNTER_LO__CI__VI, mmGRBM_SE3_PERFCOUNTER_HI__CI__VI}};

/*
 * PA_SU
 */
static const CounterRegInfo PaSuCounterRegAddr[] = {
    {mmPA_SU_PERFCOUNTER0_SELECT__CI__VI, 0, mmPA_SU_PERFCOUNTER0_LO__CI__VI, mmPA_SU_PERFCOUNTER0_HI__CI__VI},
    {mmPA_SU_PERFCOUNTER1_SELECT__CI__VI, 0, mmPA_SU_PERFCOUNTER1_LO__CI__VI, mmPA_SU_PERFCOUNTER1_HI__CI__VI},
    {mmPA_SU_PERFCOUNTER2_SELECT__CI__VI, 0, mmPA_SU_PERFCOUNTER2_LO__CI__VI, mmPA_SU_PERFCOUNTER2_HI__CI__VI},
    {mmPA_SU_PERFCOUNTER3_SELECT__CI__VI, 0, mmPA_SU_PERFCOUNTER3_LO__CI__VI, mmPA_SU_PERFCOUNTER3_HI__CI__VI}};

static const BlockDelayInfo PaSuBlockDelayInfo[] = {
    { mmRLC_SPM_PA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013},
    { mmRLC_SPM_PA_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f},
    { mmRLC_SPM_PA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015},
    { mmRLC_SPM_PA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013}};

/*
 * PA_SC
 */
static const CounterRegInfo PaScCounterRegAddr[] = {
    {mmPA_SC_PERFCOUNTER0_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER0_LO__CI__VI, mmPA_SC_PERFCOUNTER0_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER1_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER1_LO__CI__VI, mmPA_SC_PERFCOUNTER1_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER2_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER2_LO__CI__VI, mmPA_SC_PERFCOUNTER2_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER3_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER3_LO__CI__VI, mmPA_SC_PERFCOUNTER3_HI__CI__VI}};

static const BlockDelayInfo PaScBlockDelayInfo[] = {
    { mmRLC_SPM_SC_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011},
    { mmRLC_SPM_SC_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d},
    { mmRLC_SPM_SC_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013},
    { mmRLC_SPM_SC_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011}};

/*
 * SPI
 */
static const CounterRegInfo SpiCounterRegAddr[] = {
    {mmSPI_PERFCOUNTER0_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER0_LO__CI__VI, mmSPI_PERFCOUNTER0_HI__CI__VI},
    {mmSPI_PERFCOUNTER1_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER1_LO__CI__VI, mmSPI_PERFCOUNTER1_HI__CI__VI},
    {mmSPI_PERFCOUNTER2_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER2_LO__CI__VI, mmSPI_PERFCOUNTER2_HI__CI__VI},
    {mmSPI_PERFCOUNTER3_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER3_LO__CI__VI, mmSPI_PERFCOUNTER3_HI__CI__VI},
    {mmSPI_PERFCOUNTER4_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER4_LO__CI__VI, mmSPI_PERFCOUNTER4_HI__CI__VI},
    {mmSPI_PERFCOUNTER5_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER5_LO__CI__VI, mmSPI_PERFCOUNTER5_HI__CI__VI}};

static const BlockDelayInfo SpiBlockDelayInfo[] = {
    { mmRLC_SPM_SPI_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013},
    { mmRLC_SPM_SPI_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f},
    { mmRLC_SPM_SPI_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015},
    { mmRLC_SPM_SPI_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013}};

/*
 * TCA
 */
static const CounterRegInfo TcaCounterRegAddr[] = {
    {mmTCA_PERFCOUNTER0_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER0_LO__CI__VI, mmTCA_PERFCOUNTER0_HI__CI__VI},
    {mmTCA_PERFCOUNTER1_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER1_LO__CI__VI, mmTCA_PERFCOUNTER1_HI__CI__VI},
    {mmTCA_PERFCOUNTER2_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER2_LO__CI__VI, mmTCA_PERFCOUNTER2_HI__CI__VI},
    {mmTCA_PERFCOUNTER3_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER3_LO__CI__VI, mmTCA_PERFCOUNTER3_HI__CI__VI}};

static const BlockDelayInfo TcaBlockDelayInfo[] = {
    { mmRLC_SPM_TCA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000009},
    { mmRLC_SPM_TCA_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000b}};

/*
 * TCC
 */
static const CounterRegInfo TccCounterRegAddr[] = {
    {mmTCC_PERFCOUNTER0_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER0_LO__CI__VI, mmTCC_PERFCOUNTER0_HI__CI__VI},
    {mmTCC_PERFCOUNTER1_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER1_LO__CI__VI, mmTCC_PERFCOUNTER1_HI__CI__VI},
    {mmTCC_PERFCOUNTER2_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER2_LO__CI__VI, mmTCC_PERFCOUNTER2_HI__CI__VI},
    {mmTCC_PERFCOUNTER3_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER3_LO__CI__VI, mmTCC_PERFCOUNTER3_HI__CI__VI}};

static const BlockDelayInfo TccBlockDelayInfo[] = {
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000b},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000007},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000009},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000007},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000b},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d},
    { mmRLC_SPM_TCC_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000b}};

/*
 * TCP
 */
static const CounterRegInfo TcpCounterRegAddr[] = {
    {mmTCP_PERFCOUNTER0_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER0_LO__CI__VI, mmTCP_PERFCOUNTER0_HI__CI__VI},
    {mmTCP_PERFCOUNTER1_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER1_LO__CI__VI, mmTCP_PERFCOUNTER1_HI__CI__VI},
    {mmTCP_PERFCOUNTER2_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER2_LO__CI__VI, mmTCP_PERFCOUNTER2_HI__CI__VI},
    {mmTCP_PERFCOUNTER3_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER3_LO__CI__VI, mmTCP_PERFCOUNTER3_HI__CI__VI}};

static const BlockDelayInfo TcpBlockDelayInfo[] = {
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000017 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000017 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000017 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000017 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TCP_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d }
};

/*
 * CB
 */
static const CounterRegInfo CbCounterRegAddr[] = {
    {mmCB_PERFCOUNTER0_SELECT__CI__VI, 0, mmCB_PERFCOUNTER0_LO__CI__VI, mmCB_PERFCOUNTER0_HI__CI__VI},
    {mmCB_PERFCOUNTER1_SELECT__CI__VI, 0, mmCB_PERFCOUNTER1_LO__CI__VI, mmCB_PERFCOUNTER1_HI__CI__VI},
    {mmCB_PERFCOUNTER2_SELECT__CI__VI, 0, mmCB_PERFCOUNTER2_LO__CI__VI, mmCB_PERFCOUNTER2_HI__CI__VI},
    {mmCB_PERFCOUNTER3_SELECT__CI__VI, 0, mmCB_PERFCOUNTER3_LO__CI__VI, mmCB_PERFCOUNTER3_HI__CI__VI}};

static const BlockDelayInfo CbBlockDelayInfo[] = {
    { mmRLC_SPM_CB_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000004 },
    { mmRLC_SPM_CB_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000008 },
    { mmRLC_SPM_CB_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000001 },
    { mmRLC_SPM_CB_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000007 },
    { mmRLC_SPM_CB_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000005 },
    { mmRLC_SPM_CB_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000b },
    { mmRLC_SPM_CB_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000004 },
    { mmRLC_SPM_CB_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000008 }};

/*
 * DB
 */
static const CounterRegInfo DbCounterRegAddr[] = {
    {mmDB_PERFCOUNTER0_SELECT__CI__VI, 0, mmDB_PERFCOUNTER0_LO__CI__VI, mmDB_PERFCOUNTER0_HI__CI__VI},
    {mmDB_PERFCOUNTER1_SELECT__CI__VI, 0, mmDB_PERFCOUNTER1_LO__CI__VI, mmDB_PERFCOUNTER1_HI__CI__VI},
    {mmDB_PERFCOUNTER2_SELECT__CI__VI, 0, mmDB_PERFCOUNTER2_LO__CI__VI, mmDB_PERFCOUNTER2_HI__CI__VI},
    {mmDB_PERFCOUNTER3_SELECT__CI__VI, 0, mmDB_PERFCOUNTER3_LO__CI__VI, mmDB_PERFCOUNTER3_HI__CI__VI}};

static const BlockDelayInfo DbBlockDelayInfo[] = {
    { mmRLC_SPM_DB_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000006 },
    { mmRLC_SPM_DB_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000b },
    { mmRLC_SPM_DB_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000003 },
    { mmRLC_SPM_DB_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000007 },
    { mmRLC_SPM_DB_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000009 },
    { mmRLC_SPM_DB_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d },
    { mmRLC_SPM_DB_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000007 },
    { mmRLC_SPM_DB_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000b }};

/*
 * RLC
 */
static const CounterRegInfo RlcCounterRegAddr[] = {
    {mmRLC_PERFCOUNTER0_SELECT__CI__VI, 0, mmRLC_PERFCOUNTER0_LO__CI__VI, mmRLC_PERFCOUNTER0_HI__CI__VI},
    {mmRLC_PERFCOUNTER1_SELECT__CI__VI, 0, mmRLC_PERFCOUNTER1_LO__CI__VI, mmRLC_PERFCOUNTER1_HI__CI__VI}};

/*
 * SC
 */
static const CounterRegInfo ScCounterRegAddr[] = {
    {mmPA_SC_PERFCOUNTER0_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER0_LO__CI__VI, mmPA_SC_PERFCOUNTER0_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER1_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER1_LO__CI__VI, mmPA_SC_PERFCOUNTER1_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER2_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER2_LO__CI__VI, mmPA_SC_PERFCOUNTER2_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER3_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER3_LO__CI__VI, mmPA_SC_PERFCOUNTER3_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER4_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER4_LO__CI__VI, mmPA_SC_PERFCOUNTER4_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER5_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER5_LO__CI__VI, mmPA_SC_PERFCOUNTER5_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER6_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER6_LO__CI__VI, mmPA_SC_PERFCOUNTER6_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER7_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER7_LO__CI__VI, mmPA_SC_PERFCOUNTER7_HI__CI__VI}};

/*
 * SX
 */
static const CounterRegInfo SxCounterRegAddr[] = {
    {mmSX_PERFCOUNTER0_SELECT__CI__VI, 0, mmSX_PERFCOUNTER0_LO__CI__VI, mmSX_PERFCOUNTER0_HI__CI__VI},
    {mmSX_PERFCOUNTER1_SELECT__CI__VI, 0, mmSX_PERFCOUNTER1_LO__CI__VI, mmSX_PERFCOUNTER1_HI__CI__VI},
    {mmSX_PERFCOUNTER2_SELECT__CI__VI, 0, mmSX_PERFCOUNTER2_LO__CI__VI, mmSX_PERFCOUNTER2_HI__CI__VI},
    {mmSX_PERFCOUNTER3_SELECT__CI__VI, 0, mmSX_PERFCOUNTER3_LO__CI__VI, mmSX_PERFCOUNTER3_HI__CI__VI}};

static const BlockDelayInfo SxBlockDelayInfo[] = {
    { mmRLC_SPM_SX_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000b },
    { mmRLC_SPM_SX_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000009 },
    { mmRLC_SPM_SX_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d },
    { mmRLC_SPM_SX_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000b }};

/*
 * TA
 */
static const CounterRegInfo TaCounterRegAddr[] = {
    {mmTA_PERFCOUNTER0_SELECT__CI__VI, 0, mmTA_PERFCOUNTER0_LO__CI__VI, mmTA_PERFCOUNTER0_HI__CI__VI},
    {mmTA_PERFCOUNTER1_SELECT__CI__VI, 0, mmTA_PERFCOUNTER1_LO__CI__VI, mmTA_PERFCOUNTER1_HI__CI__VI}};

static const BlockDelayInfo TaBlockDelayInfo[] = {
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000012 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000b },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000016 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000014 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TA_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d }};

/*
 * TD
 */
static const CounterRegInfo TdCounterRegAddr[] = {
    {mmTD_PERFCOUNTER0_SELECT__CI__VI, 0, mmTD_PERFCOUNTER0_LO__CI__VI, mmTD_PERFCOUNTER0_HI__CI__VI},
    {mmTD_PERFCOUNTER1_SELECT__CI__VI, 0, mmTD_PERFCOUNTER1_LO__CI__VI, mmTD_PERFCOUNTER1_HI__CI__VI}};

static const BlockDelayInfo TdBlockDelayInfo[] = {
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000014 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000014 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000b },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000017 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000014 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000013 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_TD_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000d }};

/*
 * GDS
 */
static const CounterRegInfo GdsCounterRegAddr[] = {
    {mmGDS_PERFCOUNTER0_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER0_LO__CI__VI, mmGDS_PERFCOUNTER0_HI__CI__VI},
    {mmGDS_PERFCOUNTER1_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER1_LO__CI__VI, mmGDS_PERFCOUNTER1_HI__CI__VI},
    {mmGDS_PERFCOUNTER2_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER2_LO__CI__VI, mmGDS_PERFCOUNTER2_HI__CI__VI},
    {mmGDS_PERFCOUNTER3_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER3_LO__CI__VI, mmGDS_PERFCOUNTER3_HI__CI__VI}};

static const BlockDelayInfo GdsBlockDelayInfo[] = {
    { mmRLC_SPM_GDS_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 }
};

/*
 * VGT
 */
static const CounterRegInfo VgtCounterRegAddr[] = {
    {mmVGT_PERFCOUNTER0_SELECT__CI__VI, 0, mmVGT_PERFCOUNTER0_LO__CI__VI, mmVGT_PERFCOUNTER0_HI__CI__VI},
    {mmVGT_PERFCOUNTER1_SELECT__CI__VI, 0, mmVGT_PERFCOUNTER1_LO__CI__VI, mmVGT_PERFCOUNTER1_HI__CI__VI},
    {mmVGT_PERFCOUNTER2_SELECT__CI__VI, 0, mmVGT_PERFCOUNTER2_LO__CI__VI, mmVGT_PERFCOUNTER2_HI__CI__VI},
    {mmVGT_PERFCOUNTER3_SELECT__CI__VI, 0, mmVGT_PERFCOUNTER3_LO__CI__VI, mmVGT_PERFCOUNTER3_HI__CI__VI}};

static const BlockDelayInfo VgtBlockDelayInfo[] = {
    { mmRLC_SPM_VGT_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f },
    { mmRLC_SPM_VGT_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000b },
    { mmRLC_SPM_VGT_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000011 },
    { mmRLC_SPM_VGT_PERFMON_SAMPLE_DELAY__CI__VI, 0x0000000f }};

/*
 * IA
 */
static const CounterRegInfo IaCounterRegAddr[] = {
    {mmIA_PERFCOUNTER0_SELECT__CI__VI, 0, mmIA_PERFCOUNTER0_LO__CI__VI, mmIA_PERFCOUNTER0_HI__CI__VI},
    {mmIA_PERFCOUNTER1_SELECT__CI__VI, 0, mmIA_PERFCOUNTER1_LO__CI__VI, mmIA_PERFCOUNTER1_HI__CI__VI},
    {mmIA_PERFCOUNTER2_SELECT__CI__VI, 0, mmIA_PERFCOUNTER2_LO__CI__VI, mmIA_PERFCOUNTER2_HI__CI__VI},
    {mmIA_PERFCOUNTER3_SELECT__CI__VI, 0, mmIA_PERFCOUNTER3_LO__CI__VI, mmIA_PERFCOUNTER3_HI__CI__VI}};

static const BlockDelayInfo IaBlockDelayInfo[] = {
    { mmRLC_SPM_IA_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 }};

/*
 * SRBM
 */
static const CounterRegInfo SrbmCounterRegAddr[] = {
    {mmSRBM_PERFCOUNTER0_SELECT__VI, mmSRBM_PERFMON_CNTL__VI, mmSRBM_PERFCOUNTER0_LO__VI, mmSRBM_PERFCOUNTER0_HI__VI},
    {mmSRBM_PERFCOUNTER1_SELECT__VI, mmSRBM_PERFMON_CNTL__VI, mmSRBM_PERFCOUNTER1_LO__VI, mmSRBM_PERFCOUNTER1_HI__VI}};

/*
 * WD
 */
static const CounterRegInfo WdCounterRegAddr[] = {
    {mmWD_PERFCOUNTER0_SELECT__CI__VI, 0, mmWD_PERFCOUNTER0_LO__CI__VI, mmWD_PERFCOUNTER0_HI__CI__VI},
    {mmWD_PERFCOUNTER1_SELECT__CI__VI, 0, mmWD_PERFCOUNTER1_LO__CI__VI, mmWD_PERFCOUNTER1_HI__CI__VI},
    {mmWD_PERFCOUNTER2_SELECT__CI__VI, 0, mmWD_PERFCOUNTER2_LO__CI__VI, mmWD_PERFCOUNTER2_HI__CI__VI},
    {mmWD_PERFCOUNTER3_SELECT__CI__VI, 0, mmWD_PERFCOUNTER3_LO__CI__VI, mmWD_PERFCOUNTER3_HI__CI__VI}};

/*
 * CPG
 */
static const CounterRegInfo CpgCounterRegAddr[] = {
    {mmCPG_PERFCOUNTER0_SELECT__CI__VI, 0, mmCPG_PERFCOUNTER0_LO__CI__VI, mmCPG_PERFCOUNTER0_HI__CI__VI},
    {mmCPG_PERFCOUNTER1_SELECT__CI__VI, 0, mmCPG_PERFCOUNTER1_LO__CI__VI, mmCPG_PERFCOUNTER1_HI__CI__VI}};

static const BlockDelayInfo CpgBlockDelayInfo[] = {
    { mmRLC_SPM_CPG_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015 }
};

/*
 * CPC
 */
static const CounterRegInfo CpcCounterRegAddr[] = {
    {mmCPC_PERFCOUNTER0_SELECT__CI__VI, 0, mmCPC_PERFCOUNTER0_LO__CI__VI, mmCPC_PERFCOUNTER0_HI__CI__VI},
    {mmCPC_PERFCOUNTER1_SELECT__CI__VI, 0, mmCPC_PERFCOUNTER1_LO__CI__VI, mmCPC_PERFCOUNTER1_HI__CI__VI}};

static const BlockDelayInfo CpcBlockDelayInfo[] = {
    { mmRLC_SPM_CPC_PERFMON_SAMPLE_DELAY__CI__VI, 0x00000015}
};

// MC blocks
// ATC
static const CounterRegInfo AtcCounterRegAddr[] = {
    {mmATC_PERFCOUNTER0_CFG__CI__VI, mmATC_PERFCOUNTER_RSLT_CNTL__CI__VI, mmATC_PERFCOUNTER_LO__CI__VI, mmATC_PERFCOUNTER_HI__CI__VI},
    {mmATC_PERFCOUNTER1_CFG__CI__VI, mmATC_PERFCOUNTER_RSLT_CNTL__CI__VI, mmATC_PERFCOUNTER_LO__CI__VI, mmATC_PERFCOUNTER_HI__CI__VI},
    {mmATC_PERFCOUNTER2_CFG__CI__VI, mmATC_PERFCOUNTER_RSLT_CNTL__CI__VI, mmATC_PERFCOUNTER_LO__CI__VI, mmATC_PERFCOUNTER_HI__CI__VI},
    {mmATC_PERFCOUNTER3_CFG__CI__VI, mmATC_PERFCOUNTER_RSLT_CNTL__CI__VI, mmATC_PERFCOUNTER_LO__CI__VI, mmATC_PERFCOUNTER_HI__CI__VI}};
// RPB
static const CounterRegInfo RpbCounterRegAddr[] = {
    {mmMC_RPB_PERFCOUNTER0_CFG__CI__VI, mmMC_RPB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_RPB_PERFCOUNTER_LO__CI__VI, mmMC_RPB_PERFCOUNTER_HI__CI__VI},
    {mmMC_RPB_PERFCOUNTER1_CFG__CI__VI, mmMC_RPB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_RPB_PERFCOUNTER_LO__CI__VI, mmMC_RPB_PERFCOUNTER_HI__CI__VI},
    {mmMC_RPB_PERFCOUNTER2_CFG__CI__VI, mmMC_RPB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_RPB_PERFCOUNTER_LO__CI__VI, mmMC_RPB_PERFCOUNTER_HI__CI__VI},
    {mmMC_RPB_PERFCOUNTER3_CFG__CI__VI, mmMC_RPB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_RPB_PERFCOUNTER_LO__CI__VI, mmMC_RPB_PERFCOUNTER_HI__CI__VI}};
// MC_ARB
static const CounterRegInfo McArbCounterRegAddr[] = {
    {mmMC_ARB_PERFCOUNTER0_CFG__CI__VI, mmMC_ARB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_ARB_PERFCOUNTER_LO__CI__VI, mmMC_ARB_PERFCOUNTER_HI__CI__VI},
    {mmMC_ARB_PERFCOUNTER1_CFG__CI__VI, mmMC_ARB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_ARB_PERFCOUNTER_LO__CI__VI, mmMC_ARB_PERFCOUNTER_HI__CI__VI},
    {mmMC_ARB_PERFCOUNTER2_CFG__CI__VI, mmMC_ARB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_ARB_PERFCOUNTER_LO__CI__VI, mmMC_ARB_PERFCOUNTER_HI__CI__VI},
    {mmMC_ARB_PERFCOUNTER3_CFG__CI__VI, mmMC_ARB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_ARB_PERFCOUNTER_LO__CI__VI, mmMC_ARB_PERFCOUNTER_HI__CI__VI}};
// MC_HUB
static const CounterRegInfo McHubCounterRegAddr[] = {
    {mmMC_HUB_PERFCOUNTER0_CFG__CI__VI, mmMC_HUB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_HUB_PERFCOUNTER_LO__CI__VI, mmMC_HUB_PERFCOUNTER_HI__CI__VI},
    {mmMC_HUB_PERFCOUNTER1_CFG__CI__VI, mmMC_HUB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_HUB_PERFCOUNTER_LO__CI__VI, mmMC_HUB_PERFCOUNTER_HI__CI__VI},
    {mmMC_HUB_PERFCOUNTER2_CFG__CI__VI, mmMC_HUB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_HUB_PERFCOUNTER_LO__CI__VI, mmMC_HUB_PERFCOUNTER_HI__CI__VI},
    {mmMC_HUB_PERFCOUNTER3_CFG__CI__VI, mmMC_HUB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_HUB_PERFCOUNTER_LO__CI__VI, mmMC_HUB_PERFCOUNTER_HI__CI__VI}};
// MC_MCBVM
static const CounterRegInfo McMcbvmCounterRegAddr[] = {
    {mmMC_MCBVM_PERFCOUNTER0_CFG__CI__VI, mmMC_HUB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_HUB_PERFCOUNTER_LO__CI__VI, mmMC_HUB_PERFCOUNTER_HI__CI__VI},
    {mmMC_MCBVM_PERFCOUNTER1_CFG__CI__VI, mmMC_HUB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_HUB_PERFCOUNTER_LO__CI__VI, mmMC_HUB_PERFCOUNTER_HI__CI__VI},
    {mmMC_MCBVM_PERFCOUNTER2_CFG__CI__VI, mmMC_HUB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_HUB_PERFCOUNTER_LO__CI__VI, mmMC_HUB_PERFCOUNTER_HI__CI__VI},
    {mmMC_MCBVM_PERFCOUNTER3_CFG__CI__VI, mmMC_HUB_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_HUB_PERFCOUNTER_LO__CI__VI, mmMC_HUB_PERFCOUNTER_HI__CI__VI}};
// MC_SEQ
static const CounterRegInfo McSeqCounterRegAddr[] = {
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, mmMC_CONFIG_MCD, mmMC_SEQ_PERF_SEQ_CNT_A_I0__VI, mmMC_SEQ_PERF_SEQ_CNT_A_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, mmMC_CONFIG_MCD, mmMC_SEQ_PERF_SEQ_CNT_B_I0__VI, mmMC_SEQ_PERF_SEQ_CNT_B_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, mmMC_CONFIG_MCD, mmMC_SEQ_PERF_SEQ_CNT_C_I0__VI, mmMC_SEQ_PERF_SEQ_CNT_C_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, mmMC_CONFIG_MCD, mmMC_SEQ_PERF_SEQ_CNT_D_I0__VI, mmMC_SEQ_PERF_SEQ_CNT_D_I1__VI}};
// MC_VM_L2
static const CounterRegInfo McVmL2CounterRegAddr[] = {
    {mmMC_VM_L2_PERFCOUNTER0_CFG__CI__VI, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_VM_L2_PERFCOUNTER_LO__CI__VI, mmMC_VM_L2_PERFCOUNTER_HI__CI__VI},
    {mmMC_VM_L2_PERFCOUNTER1_CFG__CI__VI, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_VM_L2_PERFCOUNTER_LO__CI__VI, mmMC_VM_L2_PERFCOUNTER_HI__CI__VI}};
// MC_XBAR
static const CounterRegInfo McXbarCounterRegAddr[] = {
    {mmMC_XBAR_PERFCOUNTER0_CFG__CI__VI, mmMC_XBAR_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_XBAR_PERFCOUNTER_LO__CI__VI, mmMC_XBAR_PERFCOUNTER_HI__CI__VI},
    {mmMC_XBAR_PERFCOUNTER1_CFG__CI__VI, mmMC_XBAR_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_XBAR_PERFCOUNTER_LO__CI__VI, mmMC_XBAR_PERFCOUNTER_HI__CI__VI},
    {mmMC_XBAR_PERFCOUNTER2_CFG__CI__VI, mmMC_XBAR_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_XBAR_PERFCOUNTER_LO__CI__VI, mmMC_XBAR_PERFCOUNTER_HI__CI__VI},
    {mmMC_XBAR_PERFCOUNTER3_CFG__CI__VI, mmMC_XBAR_PERFCOUNTER_RSLT_CNTL__CI__VI, mmMC_XBAR_PERFCOUNTER_LO__CI__VI, mmMC_XBAR_PERFCOUNTER_HI__CI__VI}};
// SDMA
static const CounterRegInfo SdmaCounterRegAddr[] = {
    {mmSDMA0_PERFMON_CNTL__VI, 0, mmSDMA0_PERFCOUNTER0_RESULT__VI, 0},
    {mmSDMA0_PERFMON_CNTL__VI, 0, mmSDMA0_PERFCOUNTER1_RESULT__VI, 0},
    {mmSDMA1_PERFMON_CNTL__VI, 0, mmSDMA1_PERFCOUNTER0_RESULT__VI, 0},
    {mmSDMA1_PERFMON_CNTL__VI, 0, mmSDMA1_PERFCOUNTER1_RESULT__VI, 0}};

// Counter block info table
// SPM global blocks: CPG, CPC, CPF, GDS, TCC, TCA, IA, TCS
// SPM shader engine blocks: CB, DB, SC, SX, TA, TD, TCP, VGT, SQG, SPI, PA
// Counter block CB
static const GpuBlockInfo CbCounterBlockInfo = {"CB", CbCounterBlockId, CbCounterBlockNumInstances, CbCounterBlockMaxEvent, CbCounterBlockNumCounters, CbCounterRegAddr, gfx8_cntx_prim::select_value<regCB_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockSeAttr|CounterBlockCleanAttr, CbBlockDelayInfo, SPM_SE_BLOCK_NAME_CB};
// Counter block CPC
static const GpuBlockInfo CpcCounterBlockInfo = {"CPC", CpcCounterBlockId, 1, CpcCounterBlockMaxEvent, CpcCounterBlockNumCounters, CpcCounterRegAddr, gfx8_cntx_prim::select_value<regCPC_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr|CounterBlockSpmGlobalAttr, CpcBlockDelayInfo, SPM_GLOBAL_BLOCK_NAME_CPC};
// Counter block CPF
static const GpuBlockInfo CpfCounterBlockInfo = {"CPF", CpfCounterBlockId, 1, CpfCounterBlockMaxEvent, CpfCounterBlockNumCounters, CpfCounterRegAddr, gfx8_cntx_prim::select_value<regCPF_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr|CounterBlockSpmGlobalAttr, CpfBlockDelayInfo, SPM_GLOBAL_BLOCK_NAME_CPF};
// Counter block DB
static const GpuBlockInfo DbCounterBlockInfo = {"DB", DbCounterBlockId, DbCounterBlockNumInstances, DbCounterBlockMaxEvent, DbCounterBlockNumCounters, DbCounterRegAddr, gfx8_cntx_prim::select_value<regDB_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockCleanAttr, DbBlockDelayInfo, SPM_SE_BLOCK_NAME_DB};
// Counter block GRBM
static const GpuBlockInfo GrbmCounterBlockInfo = {"GRBM", GrbmCounterBlockId, 1, GrbmCounterBlockMaxEvent, GrbmCounterBlockNumCounters, GrbmCounterRegAddr, gfx8_cntx_prim::select_value<regGRBM_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
// Counter block GRBMSE
static const GpuBlockInfo GrbmSeCounterBlockInfo = {"GRBMSE", GrbmSeCounterBlockId, 1, GrbmSeCounterBlockMaxEvent, GrbmSeCounterBlockNumCounters, GrbmSeCounterRegAddr, gfx8_cntx_prim::select_value<regGRBM_SE0_PERFCOUNTER_SELECT>, CounterBlockDfltAttr};
// Counter block PA_SU
static const GpuBlockInfo PaSuCounterBlockInfo = {"PA_SU", PaSuCounterBlockId, 1, PaSuCounterBlockMaxEvent, PaSuCounterBlockNumCounters, PaSuCounterRegAddr, gfx8_cntx_prim::select_value<regPA_SU_PERFCOUNTER0_SELECT>, CounterBlockSeAttr, PaSuBlockDelayInfo, SPM_SE_BLOCK_NAME_PA};
// Counter block PA_SC
static const GpuBlockInfo PaScCounterBlockInfo = {"PA_SC", PaScCounterBlockId, 1, PaScCounterBlockMaxEvent, PaScCounterBlockNumCounters, PaScCounterRegAddr, gfx8_cntx_prim::select_value<regPA_SC_PERFCOUNTER0_SELECT>, CounterBlockSeAttr, PaScBlockDelayInfo, SPM_SE_BLOCK_NAME_SC};
// Counter block SPI
static const GpuBlockInfo SpiCounterBlockInfo = {"SPI", SpiCounterBlockId, 1, SpiCounterBlockMaxEvent, SpiCounterBlockNumCounters, SpiCounterRegAddr, gfx8_cntx_prim::select_value<regSPI_PERFCOUNTER0_SELECT>, CounterBlockSeAttr, SpiBlockDelayInfo, SPM_SE_BLOCK_NAME_SPI};
// Counter block SQ
static const GpuBlockInfo SqCounterBlockInfo = {"SQ", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr, SqBlockDelayInfo, SPM_SE_BLOCK_NAME_SQG};
static const GpuBlockInfo SqEsCounterBlockInfo = {"SQ_ES", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqGsCounterBlockInfo = {"SQ_GS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqVsCounterBlockInfo = {"SQ_VS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqPsCounterBlockInfo = {"SQ_PS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqLsCounterBlockInfo = {"SQ_LS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqHsCounterBlockInfo = {"SQ_HS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqCsCounterBlockInfo = {"SQ_CS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
// Counter block SX
static const GpuBlockInfo SxCounterBlockInfo = {"SX", SxCounterBlockId, 1, SxCounterBlockMaxEvent, SxCounterBlockNumCounters, SxCounterRegAddr, gfx8_cntx_prim::select_value<regSX_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockCleanAttr, SxBlockDelayInfo, SPM_SE_BLOCK_NAME_SX};
// Counter block TA
static const GpuBlockInfo TaCounterBlockInfo = {"TA", TaCounterBlockId, TaCounterBlockNumInstances, TaCounterBlockMaxEvent, TaCounterBlockNumCounters, TaCounterRegAddr, gfx8_cntx_prim::select_value<regTA_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockTcAttr, TaBlockDelayInfo, SPM_SE_BLOCK_NAME_TA};
// Counter block TCA
static const GpuBlockInfo TcaCounterBlockInfo = {"TCA", TcaCounterBlockId, TcaCounterBlockNumInstances, TcaCounterBlockMaxEvent, TcaCounterBlockNumCounters, TcaCounterRegAddr, gfx8_cntx_prim::select_value<regTCA_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr|CounterBlockTcAttr|CounterBlockSpmGlobalAttr, TcaBlockDelayInfo, SPM_GLOBAL_BLOCK_NAME_TCA};
// Counter block TCC
static const GpuBlockInfo TccCounterBlockInfo = {"TCC", TccCounterBlockId, TccCounterBlockNumInstances, TccCounterBlockMaxEvent, TccCounterBlockNumCounters, TccCounterRegAddr, gfx8_cntx_prim::select_value<regTCC_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr|CounterBlockTcAttr|CounterBlockSpmGlobalAttr, TccBlockDelayInfo, SPM_GLOBAL_BLOCK_NAME_TCC};
// Counter block TD
static const GpuBlockInfo TdCounterBlockInfo = {"TD", TdCounterBlockId, TdCounterBlockNumInstances, TdCounterBlockMaxEvent, TdCounterBlockNumCounters, TdCounterRegAddr, gfx8_cntx_prim::select_value<regTD_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockTcAttr, TdBlockDelayInfo, SPM_SE_BLOCK_NAME_TD};
// Counter block TCP
static const GpuBlockInfo TcpCounterBlockInfo = {"TCP", TcpCounterBlockId, TcpCounterBlockNumInstances, TcpCounterBlockMaxEvent, TcpCounterBlockNumCounters, TcpCounterRegAddr, gfx8_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockSeAttr|CounterBlockTcAttr, TcpBlockDelayInfo, SPM_SE_BLOCK_NAME_TCP};
// Counter block GDS
static const GpuBlockInfo GdsCounterBlockInfo = {"GDS", GdsCounterBlockId, 1, GdsCounterBlockMaxEvent, GdsCounterBlockNumCounters, GdsCounterRegAddr, gfx8_cntx_prim::select_value<regGDS_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockSpmGlobalAttr, GdsBlockDelayInfo, SPM_GLOBAL_BLOCK_NAME_GDS};
// Counter block VGT
static const GpuBlockInfo VgtCounterBlockInfo = {"VGT", VgtCounterBlockId, 1, VgtCounterBlockMaxEvent, VgtCounterBlockNumCounters, VgtCounterRegAddr, gfx8_cntx_prim::select_value<regVGT_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockSeAttr, VgtBlockDelayInfo, SPM_SE_BLOCK_NAME_VGT};
// Counter block IA
static const GpuBlockInfo IaCounterBlockInfo = {"IA", IaCounterBlockId, 1, IaCounterBlockMaxEvent, IaCounterBlockNumCounters, IaCounterRegAddr, gfx8_cntx_prim::select_value<regIA_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockSeAttr|CounterBlockSpmGlobalAttr, IaBlockDelayInfo, SPM_GLOBAL_BLOCK_NAME_IA};
// Counter block SRBM
static const GpuBlockInfo SrbmCounterBlockInfo = {"SRBM", SrbmCounterBlockId, 1, SrbmCounterBlockMaxEvent, SrbmCounterBlockNumCounters, SrbmCounterRegAddr, gfx8_cntx_prim::select_value<regSRBM_PERFCOUNTER0_SELECT>, CounterBlockSrbmAttr};
// Counter block WD
static const GpuBlockInfo WdCounterBlockInfo = {"WD", WdCounterBlockId, 1, WdCounterBlockMaxEvent, WdCounterBlockNumCounters, WdCounterRegAddr, gfx8_cntx_prim::select_value<regWD_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr};
// Counter block ATC
static const GpuBlockInfo AtcCounterBlockInfo = {"ATC", AtcCounterBlockId, 1, AtcCounterBlockMaxEvent, AtcCounterBlockNumCounters, AtcCounterRegAddr, gfx8_cntx_prim::mc_select_value<regATC_PERFCOUNTER0_CFG__CI__VI>, CounterBlockMcAttr};
// Counter block RPB
static const GpuBlockInfo RpbCounterBlockInfo = {"RPB", RpbCounterBlockId, 1, RpbCounterBlockMaxEvent, RpbCounterBlockNumCounters, RpbCounterRegAddr, gfx8_cntx_prim::mc_select_value<regMC_RPB_PERFCOUNTER0_CFG__CI__VI>, CounterBlockMcAttr};
// Counter block MC_ARB
static const GpuBlockInfo McArbCounterBlockInfo = {"MC_ARB", McArbCounterBlockId, McCounterBlockNumInstances, McArbCounterBlockMaxEvent, McArbCounterBlockNumCounters, McArbCounterRegAddr, gfx8_cntx_prim::mc_select_value<regMC_ARB_PERFCOUNTER0_CFG__CI__VI>, CounterBlockMcAttr};
// Counter block MC_HUB
static const GpuBlockInfo McHubCounterBlockInfo = {"MC_HUB", McHubCounterBlockId, McCounterBlockNumInstances, McHubCounterBlockMaxEvent, McHubCounterBlockNumCounters, McHubCounterRegAddr, gfx8_cntx_prim::mc_select_value<regMC_HUB_PERFCOUNTER0_CFG__CI__VI>, CounterBlockMcAttr};
// Counter block MC_MCBVM
static const GpuBlockInfo McMcbvmCounterBlockInfo = {"MC_MCBVM", McMcbvmCounterBlockId, McCounterBlockNumInstances, McMcbvmCounterBlockMaxEvent, McMcbvmCounterBlockNumCounters, McMcbvmCounterRegAddr, gfx8_cntx_prim::mc_select_value<regMC_MCBVM_PERFCOUNTER0_CFG__CI__VI>, CounterBlockMcAttr};
// Counter block MC_SEQ
static const GpuBlockInfo McSeqCounterBlockInfo = {"MC_SEQ", McSeqCounterBlockId, McCounterBlockNumInstances, McSeqCounterBlockMaxEvent, McSeqCounterBlockNumCounters, McSeqCounterRegAddr, gfx8_cntx_prim::mc_seq_select_value, CounterBlockMcSeqAttr};
// Counter block MC_SEQ High Bandwidth Memory (HBM)
static const GpuBlockInfo McSeqHbmCounterBlockInfo = {"MC_SEQ", McSeqCounterBlockId, McHbmCounterBlockNumInstances, McSeqHbmCounterBlockMaxEvent, McSeqCounterBlockNumCounters, NULL, NULL, CounterBlockMcSeqHbmAttr};
// Counter block MC_VM_L2
static const GpuBlockInfo McVmL2CounterBlockInfo = {"MC_VM_L2", McVmL2CounterBlockId, McCounterBlockNumInstances, McVmL2CounterBlockMaxEvent, McVmL2CounterBlockNumCounters, McVmL2CounterRegAddr, gfx8_cntx_prim::mc_select_value<regMC_VM_L2_PERFCOUNTER0_CFG__CI__VI>, CounterBlockMcAttr};
// Counter block MC_XBAR
static const GpuBlockInfo McXbarCounterBlockInfo = {"MC_XBAR", McXbarCounterBlockId, McCounterBlockNumInstances, McXbarCounterBlockMaxEvent, McXbarCounterBlockNumCounters, McXbarCounterRegAddr, gfx8_cntx_prim::mc_select_value<regMC_XBAR_PERFCOUNTER0_CFG__CI__VI>, CounterBlockMcAttr};
// Counter block SDMA
static const GpuBlockInfo SdmaCounterBlockInfo = {"SDMA", SdmaCounterBlockId, 2, SdmaCounterBlockMaxEvent, SdmaCounterBlockNumCounters, SdmaCounterRegAddr, NULL, CounterBlockSdmaAttr|CounterBlockExplInstAttr};
#endif  // _GFX8_BLOCKTABLE_H_
