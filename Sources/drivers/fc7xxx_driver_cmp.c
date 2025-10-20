/**
 * @file fc7xxx_driver_cmp.c
 * @author Flagchip0126
 * @brief FC7xxx CMP driver source code
 * @version 0.1.0
 * @date 2024-01-15
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Author         CR#          Descriptions
*   ---------   ----------    ------------   ----------   ------------------------
*   0.1.0       2024-01-15    Flagchip0126   N/A          First version for FC7240
**********************************************************************************/

#include "fc7xxx_driver_cmp.h"
#include "interrupt_manager.h"

/********* Local Variables ************/
static CMP_Type *const s_apCmpBase[CMP_INSTANCE_COUNT] = CMP_BASE_PTRS;
static CMP_CompleteIntCallback s_apCmpIntNotify[CMP_INSTANCE_COUNT] = {NULL};

/******* Local Function Prototype *********/

/**
 * @brief set CMPn IRQHandler
 *
 * @param eInstance the CMP instance to use
 */
static void CMPn_IRQHandler(const CMP_InstanceType eInstance);

void CMP0_IRQHandler(void);

void CMP1_IRQHandler(void);

static void CMPn_IRQHandler(const CMP_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);

    /*callback function*/
    if (s_apCmpIntNotify[eInstance] != NULL)
    {
        s_apCmpIntNotify[eInstance]();
    }
    else
    {
        /*Noting to do*/
    }

    /*clear interrupter status regs*/
    CMP_ClearIntFlag(eInstance);
}

void CMP0_IRQHandler(void)
{
    CMPn_IRQHandler(CMP_INSTANCE_0);
}

void CMP1_IRQHandler(void)
{
    CMPn_IRQHandler(CMP_INSTANCE_1);
}

/********* Local Functions ************/
void CMP_Enable(const CMP_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    CMP_Type *const pCmp = s_apCmpBase[eInstance];

    CMP_HWA_Enable(pCmp);
}

void CMP_Disable(const CMP_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    CMP_Type *const pCmp = s_apCmpBase[eInstance];

    CMP_HWA_Disable(pCmp);
}

void CMP_CSEnable(const CMP_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    CMP_Type *const pCmp = s_apCmpBase[eInstance];

    CMP_HWA_CSEnable(pCmp);
}

void CMP_CSDisable(const CMP_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    CMP_Type *const pCmp = s_apCmpBase[eInstance];

    CMP_HWA_CSDisable(pCmp);
}

bool CMP_GetCmpOut(const CMP_InstanceType eInstance)
{
    bool CmpOut;

    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    CMP_Type *const pCmp = s_apCmpBase[eInstance];

    CmpOut = CMP_HWA_GetCmpOut(pCmp);
    return CmpOut;
}

void CMP_SetDacData(const CMP_InstanceType eInstance, uint8_t u8Data)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    CMP_Type *const pCmp = s_apCmpBase[eInstance];

    CMP_HWA_SetDacData(pCmp, u8Data);
}

CMP_OutStatus CMP_GetOutFlagStatus(const CMP_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    bool bCFF_Status = false;
    bool bCFR_Status = false;
    CMP_Type *const pCmp = s_apCmpBase[eInstance];
    CMP_OutStatus eRetVal = CMP_OUT_NONE;

    bCFF_Status = CMP_HWA_GetIntFlag_Falling(pCmp);
    bCFR_Status = CMP_HWA_GetIntFlag_Rising(pCmp);

    if ((bCFF_Status == true) && (bCFR_Status == false))
    {
        eRetVal = CMP_OUT_FALLING_EDGE;
    }
    else if ((bCFF_Status == false) && (bCFR_Status == true))
    {
        eRetVal = CMP_OUT_RISING_EDGE;
    }
    else
    {
        eRetVal = CMP_OUT_NONE;
    }

    return eRetVal;
}

bool CMP_GetChannelScanFlagStatus(const CMP_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    bool bCSF_Status = false;
    CMP_Type *const pCmp = s_apCmpBase[eInstance];

    bCSF_Status = CMP_HWA_GetIntFlag_ChannelScan(pCmp);

    return bCSF_Status;
}

void CMP_ClearIntFlag(const CMP_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    CMP_Type *const pCmp = s_apCmpBase[eInstance];

    CMP_HWA_ClearIntFlag_Rising(pCmp);
    CMP_HWA_ClearIntFlag_Falling(pCmp);
    CMP_HWA_ClearIntFlag_ChannelScan(pCmp);
}

void CMP_Init(const CMP_InstanceType eInstance, const CMP_InitType *const pInitCfg)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    DEV_ASSERT(pInitCfg != NULL);
    CMP_Type *const pCmp = s_apCmpBase[eInstance];

    /* disable CMP module */
    CMP_HWA_Disable(pCmp);

    /* determine comparator function mode */
    CMP_HWA_SetComparatorMod(pCmp, (pInitCfg->tComparatorConfig).eModSel, ((pInitCfg->tComparatorConfig).u8FilterPeriod), ((pInitCfg->tComparatorConfig).eFilterCnt));

    /* configure CMP module */
    /* CCR0 register */
    CMP_HWA_SetEnStopMod(pCmp, (pInitCfg->tComparatorConfig).bStopModEn);
    CMP_HWA_SetDacEnableSrc(pCmp, (pInitCfg->tDacConfig).eDacEnsrc);

    /* CCR1 register */
    CMP_HWA_SetCmpOutInvert(pCmp, (pInitCfg->tComparatorConfig).eInvert);
    CMP_HWA_SetCmpOutSel(pCmp, (pInitCfg->tComparatorConfig).eOutSelect);
    CMP_HWA_SetEnCmpOutPack(pCmp, (pInitCfg->tComparatorConfig).bOutToPackagePinEn);
    CMP_HWA_SetCmpOutWinLevel(pCmp, (pInitCfg->tComparatorConfig).eOutWinLevel);
    CMP_HWA_SetCmpOutWin(pCmp, (pInitCfg->tComparatorConfig).eOutWin);
    CMP_HWA_SetEnWinSampleInvert(pCmp, (pInitCfg->tComparatorConfig).bWinSampleInvertEn);
    CMP_HWA_SetEnEventCloseWin(pCmp, (pInitCfg->tComparatorConfig).bEventCloseWinEn);
    CMP_HWA_SetEventCloseWin(pCmp, (pInitCfg->tComparatorConfig).eEventSelect);

    /* CCR2 register */
    CMP_HWA_SetSpeedMod(pCmp, (pInitCfg->tComparatorConfig).eSpeedMod);
    CMP_HWA_SetHystCtrl(pCmp, (pInitCfg->tComparatorConfig).eHystCrtl);
    CMP_HWA_SetPSelMux(pCmp, (pInitCfg->tMuxConfig).ePSelMux);
    CMP_HWA_SetNSelMux(pCmp, (pInitCfg->tMuxConfig).eNSelMux);
    CMP_HWA_SetINPSel(pCmp, (pInitCfg->tMuxConfig).eINPSel);
    CMP_HWA_SetINNSel(pCmp, (pInitCfg->tMuxConfig).eINNSel);

	/* CCR3 register */
	CMP_HWA_SetAnalogConfTransByp(pCmp, (pInitCfg->tComparatorConfig).bAnalogConfTransByp);
	CMP_HWA_SetAnalogConfTransBypCnt(pCmp, (pInitCfg->tComparatorConfig).u16AnalogConfTransBypCnt);

    /* DCR register */
    CMP_HWA_SetEnDac(pCmp, (pInitCfg->tDacConfig).bDacEn);
    CMP_HWA_SetVinRefSel(pCmp, (pInitCfg->tDacConfig).eVinRefSel);
    CMP_HWA_SetDacData(pCmp, (pInitCfg->tDacConfig).u8DacData);

    if ((pInitCfg->tComparatorConfig).eModSel == CMP_MOD_CHANNEL_SCAN)
    {
        /* CSCR0 register */
        CMP_HWA_SetCSInitModulus(pCmp, (pInitCfg->tChannelScanConfig).u8ChannelScanInitModulus);
        CMP_HWA_SetCSNumOfSampleClocks(pCmp, (pInitCfg->tChannelScanConfig).u8ChannelScanNumOfSampleClocks);

        /* CSCR1 register */
        CMP_HWA_SetCSFixedChannel(pCmp, (pInitCfg->tMuxConfig).eChannelScanFixedChannel);
        CMP_HWA_SetCSFixedPort(pCmp, (pInitCfg->tMuxConfig).eChannelScanFixedPort);

        /* CSCSR register */
        CMP_HWA_SetCSComparisonResultsAutoClearEn(pCmp, (pInitCfg->tChannelScanConfig).bComparisonResultAutoClear);
    }
}

void CMP_InitInterrupt(const CMP_InstanceType eInstance, const CMP_InterruptType *const pInterruptCfg)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    DEV_ASSERT(pInterruptCfg != NULL);
    CMP_Type *const pCmp = s_apCmpBase[eInstance];

    /*disable DMA*/
    CMP_HWA_DmaDisable(pCmp);

    /*clear interrupter flag*/
    CMP_ClearIntFlag(eInstance);

    /*configure interrupter */
    CMP_SetIntEn(eInstance, pInterruptCfg);

    s_apCmpIntNotify[eInstance] = pInterruptCfg->pInterrupterNotify;
}

void CMP_InitInterrupt_Dma(const CMP_InstanceType eInstance, const CMP_DmaType *const pInterruptDmaCfg)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    DEV_ASSERT(pInterruptDmaCfg != NULL);

    CMP_InterruptType pInterruptCfg;

    pInterruptCfg.bRisingIntEn = pInterruptDmaCfg->bRisingDmaEn;
    pInterruptCfg.bFallingIntEn = pInterruptDmaCfg->bFallingDmaEn;
    pInterruptCfg.bChannelScanFlagIntEn = false;
    pInterruptCfg.pInterrupterNotify = NULL;

    /* Set rising/falling edge interrupt to trigger Dma*/
    CMP_SetIntEn(eInstance, &pInterruptCfg);

    if ((pInterruptDmaCfg->bRisingDmaEn == true) || (pInterruptDmaCfg->bFallingDmaEn == true))
    {
        CMP_DmaEnable(eInstance);
    }
    else
    {
        CMP_DmaDisable(eInstance);
    }
}

void CMP_SetIntEn(const CMP_InstanceType eInstance, const CMP_InterruptType *const pInterruptCfg)
{
    CMP_Type *const pCmp = s_apCmpBase[eInstance];

    /*set rising edges interrupter enable*/
    CMP_HWA_SetIntEn_Rising(pCmp, pInterruptCfg->bRisingIntEn);
    /*set falling edges interrupter enable*/
    CMP_HWA_SetIntEn_Falling(pCmp, pInterruptCfg->bFallingIntEn);
    /*set channel scan flag interrupter enable*/
    CMP_HWA_SetIntEn_ChannelScan(pCmp, pInterruptCfg->bChannelScanFlagIntEn);
}

void CMP_DmaEnable(const CMP_InstanceType eInstance)
{
    CMP_Type *const pCmp = s_apCmpBase[eInstance];
    CMP_HWA_DmaEnable(pCmp);
}

void CMP_DmaDisable(const CMP_InstanceType eInstance)
{
    CMP_Type *const pCmp = s_apCmpBase[eInstance];
    CMP_HWA_DmaDisable(pCmp);
}

void CMP_SetCSChannls(const CMP_InstanceType eInstance, const CMP_ChannelScanChannelCfgType s_tChnCfg[], const uint8_t u8ChnCnt)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    uint8_t u8ChnIndex;

    CMP_Type *const pCmp = s_apCmpBase[eInstance];
    for (u8ChnIndex = 0U; u8ChnIndex < u8ChnCnt; u8ChnIndex++)
    {
        CMP_HWA_SetCSChannelEn(pCmp, s_tChnCfg[u8ChnIndex].eChannel, true);
        CMP_HWA_SetCSChannelPresetstate(pCmp, s_tChnCfg[u8ChnIndex].eChannel, s_tChnCfg[u8ChnIndex].bPreSetState);
    }
}

void CMP_GetCSChannlsOut(const CMP_InstanceType eInstance, CMP_ChannelScanChannelCfgType s_tChnCfg[], const uint8_t u8ChnCnt)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    uint8_t u8ChnIndex;

    CMP_Type *const pCmp = s_apCmpBase[eInstance];
    for (u8ChnIndex = 0U; u8ChnIndex < u8ChnCnt; u8ChnIndex++)
    {
        s_tChnCfg[u8ChnIndex].bCurState = CMP_HWA_GetCSChannelsOut(pCmp, s_tChnCfg[u8ChnIndex].eChannel);
    }
}

bool CMP_GetCmpCSActive(const CMP_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < CMP_INSTANCE_COUNT);
    CMP_Type *const pCmp = s_apCmpBase[eInstance];

    return CMP_HWA_GetCSActive(pCmp);
}
