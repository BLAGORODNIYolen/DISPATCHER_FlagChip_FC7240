
/**
 * @file module_driver_tpu.c
 * @author Flagchip099
 * @brief FC7xxx TPU driver source code
 * @version 0.1.0
 * @date 2024-1-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-1-12     Flagchip099   N/A          First version for FC7240
   ******************************************************************************** */

#include "fc7xxx_driver_tpu.h"

static uint32_t u32PwmLastFrame[TPU_E_CH_COUNT];
static uint32_t u32PwmNextEdge[TPU_E_CH_COUNT];
static bool bMeasActivePeriodComplete[TPU_E_CH_COUNT] = {(bool)false};
static TPU_HSACallbackType s_TpuHSANotify[TPU_E_CH_COUNT] = {NULL};
static TPU_EventCallbackType s_TpuEventNotify[TPU_E_CH_COUNT] = {NULL};
static TPU_TCR1OverflowCallbackType s_TpuTCR1OverflowNotify = NULL;
static TPU_TCR2OverflowCallbackType s_TpuTCR2OverflowNotify = NULL;


void TPU0_CH0_7_IRQHandler(void);
void TPU0_CH8_15_IRQHandler(void);
void TPU0_CH16_23_IRQHandler(void);
void TPU0_CH24_31_IRQHandler(void);

/**
 * @brief TPU_Overflow_IRQHandler
 *
 */
static inline void TPU_Overflow_IRQHandler(void)
{
    TPU_E_Type *const pTpuE = TPU_E_BASE_PTRS;
    if (TPU_E_HWA_GetTCR1Overflow(pTpuE))
    {
        TPU_E_HWA_ClearTCR1Overflow(pTpuE);
        if (s_TpuTCR1OverflowNotify != NULL)
        {
            s_TpuTCR1OverflowNotify();
        }
    }
    if (TPU_E_HWA_GetTCR2Overflow(pTpuE))
    {
        TPU_E_HWA_ClearTCR2Overflow(pTpuE);
        if (s_TpuTCR2OverflowNotify != NULL)
        {
            s_TpuTCR2OverflowNotify();
        }
    }
}

/**
 * @brief TPU_Event_IRQHandler
 *
 */
static inline void TPU_Event_IRQHandler(uint8_t u8MinChannel, uint8_t u8MaxChannel)
{
    TPU_H_Type *const pTpuH = TPU_H_BASE_PTRS;
    uint8_t u8Channel;

    for (u8Channel = (uint8_t)u8MinChannel; u8Channel < ((uint8_t)u8MaxChannel + 1u); u8Channel++)
    {
        if (TPU_H_HWA_GetChEventTrigISRStatus(pTpuH, u8Channel) == true)
        {
            if (s_TpuEventNotify[u8Channel] != NULL)
            {
                s_TpuEventNotify[u8Channel]();
            }
        }
        if (TPU_H_HWA_GetChHSAReqStatus(pTpuH, u8Channel) == true)
        {
            TPU_H_HWA_ClearChHSA(pTpuH, u8Channel);
            s_TpuHSANotify[u8Channel]();
        }
    }
}

/**
 * @brief TPU_InitOverflowInterrupt
 *
 */
static void TPU_InitOverflowInterrupt(const TPU_InterruptCfgType *const pInterruptCfg)
{
    DEV_ASSERT(pInterruptCfg != NULL);

    TPU_E_Type *const pTPUE = TPU_E_BASE_PTRS;

    if (pInterruptCfg->bTCR1OverFlowEventIntEn)
    {
        s_TpuTCR1OverflowNotify = pInterruptCfg->pTCR1OverflowNotify;
        TPU_E_HWA_EnableTCR1OVFIRQ(pTPUE, (bool)true);
    }
    else
    {
        TPU_E_HWA_EnableTCR1OVFIRQ(pTPUE, (bool)false);
        s_TpuTCR1OverflowNotify = NULL;
    }

    if (pInterruptCfg->bTCR2OverFlowEventIntEn)
    {
        s_TpuTCR2OverflowNotify = pInterruptCfg->pTCR2OverflowNotify;
        TPU_E_HWA_EnableTCR2OVFIRQ(pTPUE, (bool)true);
    }
    else
    {
        TPU_E_HWA_EnableTCR2OVFIRQ(pTPUE, (bool)false);
        s_TpuTCR2OverflowNotify = NULL;
    }
}

/**
 * @brief TPU0_CH0_7_IRQHandler
 *
 */
void TPU0_CH0_7_IRQHandler(void)
{
    TPU_Event_IRQHandler(TPU_CHANNEL_0, TPU_CHANNEL_7);
}

/**
 * @brief TPU0_CH8_15_IRQHandler
 *
 */
void TPU0_CH8_15_IRQHandler(void)
{
    TPU_Event_IRQHandler(TPU_CHANNEL_8, TPU_CHANNEL_15);
}

/**
 * @brief TPU0_CH16_23_IRQHandler
 *
 */
void TPU0_CH16_23_IRQHandler(void)
{
    TPU_Event_IRQHandler(TPU_CHANNEL_16, TPU_CHANNEL_23);
}

/**
 * @brief TPU0_CH24_31_IRQHandler
 *
 */
void TPU0_CH24_31_IRQHandler(void)
{
    TPU_Overflow_IRQHandler();
    TPU_Event_IRQHandler(TPU_CHANNEL_24, TPU_CHANNEL_31);
}

/**
 * @brief TPU_InitChannelInterrupt
 *
 */
void TPU_InitChannelInterrupt(uint8_t u8Channel, const TPU_InterruptCfgType *const pInterruptCfg)
{
    DEV_ASSERT(u8Channel < TPU_E_CH_COUNT);
    DEV_ASSERT(pInterruptCfg != NULL);

    TPU_E_Type *const pTPUE = TPU_E_BASE_PTRS;
    TPU_H_Type *const pTPUH = TPU_H_BASE_PTRS;

    if (pInterruptCfg->bEventIntEn)
    {
        s_TpuEventNotify[u8Channel] = pInterruptCfg->pEventNotify;
        TPU_E_HWA_EnableChEventInt(pTPUE, u8Channel, (bool)true);
        TPU_E_HWA_EnableSrvReq(pTPUE, u8Channel, (bool)true);
        TPU_H_HWA_SetChTrig(pTPUH, u8Channel, pInterruptCfg->eChTrigType);
    }
    else
    {
        s_TpuEventNotify[u8Channel] = NULL;
    }
    TPU_InitOverflowInterrupt(pInterruptCfg);
}

/**
 * @brief TPU_Init
 *
 */
void TPU_Init(void)
{
    TPU_E_Type *const pTPUE = TPU_E_BASE_PTRS;

    SCM_HWA_SUBSYS_PCC_SetEnable_TPUClock((bool)true);
    TPU_E_HWA_SetTimeBaseCntStopInStopMode(pTPUE, (bool)true);
}

/**
 * @brief TPU_DeInit
 *
 */
void TPU_DeInit(void)
{
    TPU_E_Type *const pTPUE = TPU_E_BASE_PTRS;

    TPU_E_HWA_TrigReset(pTPUE);
}

/**
 * @brief TPU_StartChannel
 *
 */
void TPU_StartChannel(void)
{
    SCM_HWA_ConfigTpuGTBSelect((bool)true);
}

/**
 * @brief TPU_SetHSR
 *
 */
void TPU_SetHSR(uint8_t u8channel, uint8_t u8HSRIdx)
{
    TPU_H_Type *const pTPUH = TPU_H_BASE_PTRS;

    TPU_H_HWA_SetChHSA(pTPUH, u8channel, true);
    TPU_H_HWA_SetChHSRIdx(pTPUH, u8channel, u8HSRIdx);
    TPU_H_HWA_SetChHSRISR(pTPUH, u8channel, (bool)true);
    TPU_H_HWA_SetChSyncISR(pTPUH, u8channel, (bool)false);
}

/**
 * @brief TPU_SendHSR
 *
 */
void TPU_SendHSR(uint8_t u8channel)
{
    TPU_H_Type *const pTPUH = TPU_H_BASE_PTRS;

    TPU_H_HWA_ClearChHSR(pTPUH, u8channel);
}

/**
 * @brief TPU_GetHSA
 *
 */
uint8_t TPU_GetHSA(uint8_t u8Channel)
{
    TPU_H_Type *const pTPUH = TPU_H_BASE_PTRS;

    return TPU_H_HWA_GetChHSAIdx(pTPUH, (uint8_t)u8Channel);
}

/**
 * @brief TPU_InitChannelInterrupt
 *
 */
void TPU_InitChannelHSAInterrupt(uint8_t u8Channel, const TPU_InterruptCfgType *const pInterruptCfg)
{
    s_TpuHSANotify[u8Channel] = pInterruptCfg->pHSANotify;
}

/**
 * @brief TPU_InitChannelOverflowInterrupt
 *
 */
void TPU_InitChannelOverflowInterrupt(const TPU_InterruptCfgType *const pInterruptCfg)
{
    s_TpuTCR1OverflowNotify = pInterruptCfg->pTCR1OverflowNotify;
    s_TpuTCR2OverflowNotify = pInterruptCfg->pTCR2OverflowNotify;
}

/**
 * @brief TPU_EnableSubSystem
 *
 */
void TPU_EnableSubSystem(void)
{
    SCM_HWA_SUBSYS_PCC_SetEnable_SubSystemClock((bool)true);
}

/**
 * @brief TPU_EnableEventTrigDma
 *
 */
void TPU_EnableEventTrigDma(uint8_t u8Channel)
{
    TPU_H_Type *const pTPUH = TPU_H_BASE_PTRS;

    TPU_H_HWA_SetChEventDMAEnable(pTPUH, (uint8_t)u8Channel, (bool)true);
}

void TPU_EnableEventTrigTrgSel(uint8_t u8Channel, const TPU_InterruptCfgType *const pInterruptCfg)
{
    TPU_H_Type *const pTPUH = TPU_H_BASE_PTRS;

    TPU_H_HWA_SetChTrig(pTPUH, u8Channel, pInterruptCfg->eChTrigType);
}

/**
 * @brief TPU_EnableFlexcoreTrigDma
 *
 */
void TPU_EnableFlexcoreTrigDma(uint8_t u8Channel)
{
    TPU_H_Type *const pTPUH = TPU_H_BASE_PTRS;

    TPU_H_HWA_SetChReqDMAEnable(pTPUH, (uint8_t)u8Channel, (bool)true);
}

/**
 * @brief TPU_PwmModeInit
 *
 */
void TPU_PwmModeInit(uint8_t u8channel, const TPU_PwmCfgType *const p_etpu_config)
{
    TPU_E_Type *const pTPUE = TPU_E_BASE_PTRS;
    uint32_t u32ER1_Val;

    TPU_E_HWA_ClearMatch1CFGFlg(pTPUE, u8channel);
    TPU_E_HWA_ClearMatch1Event(pTPUE, u8channel);
    TPU_E_HWA_ClearTransDetect1Event(pTPUE, u8channel);
    TPU_E_HWA_ClearMatch2CFGFlg(pTPUE, u8channel);
    TPU_E_HWA_ClearMatch2Event(pTPUE, u8channel);
    TPU_E_HWA_ClearTransDetect2Event(pTPUE, u8channel);
    TPU_E_HWA_SetOPAC1(pTPUE, u8channel, TPUE_NO_CHANGE_OUTPUT);
    TPU_E_HWA_SetOPAC2(pTPUE, u8channel, TPUE_NO_CHANGE_OUTPUT);
    TPU_E_HWA_SetTCR1ClkControl(pTPUE, TPUE_TCR1CLK_CLK_SRC_TPUCLKDIV2);
    TPU_E_HWA_SetPDCM(pTPUE, u8channel, TPUE_EM_NB_ST);
    TPU_E_HWA_SetTCR1MaxCnt(pTPUE, TPU_TCR1_MAXVALUE);
    TPU_E_HWA_SetTCR2MaxCnt(pTPUE, TPU_TCR1_MAXVALUE);

    if (p_etpu_config->bPwmUseTCR1)
    {
        TPU_E_HWA_SetMatchER1(pTPUE, u8channel, (TPU_E_HWA_GetTCR1CntVal(pTPUE) + 1U));
        u32ER1_Val = TPU_E_HWA_GetER1Val(pTPUE, u8channel);
        TPU_E_HWA_SetER2(pTPUE, u8channel, (p_etpu_config->u32ActiveTime + u32ER1_Val));
    }

    u32PwmNextEdge[u8channel] = TPU_E_HWA_GetER2Val(pTPUE, u8channel);

    TPU_E_HWA_SetChOutputActiveHigh(pTPUE, u8channel, p_etpu_config->bActiveHigh);
    if (p_etpu_config->bActiveHigh)
    {
        TPU_E_HWA_SetOPAC1(pTPUE, u8channel, TPUE_MATCH_SET_OUTPUT_HIGH);
        TPU_E_HWA_SetOPAC2(pTPUE, u8channel, TPUE_MATCH_SET_OUTPUT_LOW);
        TPU_E_HWA_SetChTBS1(pTPUE, u8channel, p_etpu_config->eTBS1);
        TPU_E_HWA_SetChTBS2(pTPUE, u8channel, p_etpu_config->eTBS2);
        TPU_E_HWA_SetChEntryTblflag1(pTPUE, u8channel, (bool)true);
    }
    else
    {
        TPU_E_HWA_SetOPAC1(pTPUE, u8channel, TPUE_MATCH_SET_OUTPUT_LOW);
        TPU_E_HWA_SetOPAC2(pTPUE, u8channel, TPUE_MATCH_SET_OUTPUT_HIGH);
        TPU_E_HWA_SetChTBS1(pTPUE, u8channel, p_etpu_config->eTBS1);
        TPU_E_HWA_SetChTBS2(pTPUE, u8channel, p_etpu_config->eTBS2);
        TPU_E_HWA_SetChEntryTblflag1(pTPUE, u8channel, (bool)false);
    }
    /* Set channel priority */

    /* Here do not enable NVIC */

    TPU_E_HWA_SetOutputSelOPAC1(pTPUE, u8channel, (bool)true);
    TPU_E_HWA_SetOutputSelOPAC2(pTPUE, u8channel, (bool)true);
    TPU_E_HWA_EnableChOutputBuf(pTPUE, u8channel, (bool)true);
    TPU_E_HWA_EnableMatch(pTPUE, u8channel, (bool)true);
    TPU_E_HWA_EnableSrvReq(pTPUE, u8channel, (bool)true);

    return;
}

/**
 * @brief TPU_PwmServiceReq
 *
 */
void TPU_PwmServiceReq(uint8_t u8channel, uint32_t u32ActiveTime, uint32_t u32Period)
{
    TPU_E_Type *const pTPUE = TPU_E_BASE_PTRS;

    if (TPU_E_HWA_GetChMatchRecLatch1Status(pTPUE, u8channel) == (bool)true)
    {
        /* in match1 */
        TPU_E_HWA_ClearMatch1Event(pTPUE, u8channel);
        TPU_E_HWA_SetChEntryTblflag0(pTPUE, u8channel, (bool)false);
        u32PwmLastFrame[u8channel] = TPU_E_HWA_GetER1Val(pTPUE, u8channel);
        /* Next ER1 */
        if ((u32PwmLastFrame[u8channel] + u32Period) > TPU_TCR1_MAXVALUE)
        {
            TPU_E_HWA_SetMatchER1(pTPUE, u8channel, (u32PwmLastFrame[u8channel] + u32Period - TPU_TCR1_MAXVALUE - 1U));
        }
        else
        {
            TPU_E_HWA_SetMatchER1(pTPUE, u8channel, (u32PwmLastFrame[u8channel] + u32Period));
        }

        if ((TPU_E_HWA_GetER1Val(pTPUE, u8channel) + u32ActiveTime) > TPU_TCR1_MAXVALUE)
        {
            u32PwmNextEdge[u8channel] = TPU_E_HWA_GetER1Val(pTPUE, u8channel) + u32ActiveTime - TPU_TCR1_MAXVALUE - 1U;
        }
        else
        {
            u32PwmNextEdge[u8channel] = TPU_E_HWA_GetER1Val(pTPUE, u8channel) + u32ActiveTime;
        }
        TPU_E_HWA_EnableMatch(pTPUE, u8channel, (bool)true);
    }
    else if (TPU_E_HWA_GetChMatchRecLatch2Status(pTPUE, u8channel) == (bool)true)
    {
        /* in match2 */
        TPU_E_HWA_ClearMatch2Event(pTPUE, u8channel);
        TPU_E_HWA_SetChEntryTblflag0(pTPUE, u8channel, (bool)true);
        /* Next ER2 */
        TPU_E_HWA_SetER2(pTPUE, u8channel, u32PwmNextEdge[u8channel]);
        TPU_E_HWA_EnableMatch(pTPUE, u8channel, (bool)true);
    }
    TPU_E_HWA_ClearChEventISRFlg(pTPUE, (uint8_t)u8channel);
}

/**
 * @brief TPU_CaptureModeInit
 *
 */
void TPU_CaptureModeInit(uint8_t u8channel, const TPU_CaptureCfgType *const p_etpu_config)
{
    TPU_E_Type *const pTPUE = TPU_E_BASE_PTRS;

    TPU_E_HWA_ClearMatchEn1(pTPUE, u8channel);
    TPU_E_HWA_ClearMatch1CFGFlg(pTPUE, u8channel);
    TPU_E_HWA_ClearMatch1Event(pTPUE, u8channel);
    TPU_E_HWA_ClearTransDetect1Event(pTPUE, u8channel);
    TPU_E_HWA_ClearMatch2CFGFlg(pTPUE, u8channel);
    TPU_E_HWA_ClearMatch2Event(pTPUE, u8channel);
    TPU_E_HWA_ClearTransDetect2Event(pTPUE, u8channel);
    TPU_E_HWA_SetTCR1ClkControl(pTPUE, TPUE_TCR1CLK_CLK_SRC_TPUCLKDIV2);
    TPU_E_HWA_SetChTBS1(pTPUE, u8channel, TPUE_GREATER_OR_EQUAL_CAPBASE_TCR1_MATCHBASE_TCR1);
    TPU_E_HWA_SetChTBS2(pTPUE, u8channel, TPUE_GREATER_OR_EQUAL_CAPBASE_TCR1_MATCHBASE_TCR1);
    TPU_E_HWA_SetOPAC1(pTPUE, u8channel, TPUE_NO_CHANGE_OUTPUT);
    TPU_E_HWA_SetOPAC2(pTPUE, u8channel, TPUE_NO_CHANGE_OUTPUT);
    TPU_E_HWA_SetChEntryTblflag1(pTPUE, u8channel, (bool)false);
    TPU_E_HWA_SetChEntryTblflag0(pTPUE, u8channel, (bool)false);
    TPU_E_HWA_SetTCR1MaxCnt(pTPUE, TPU_TCR1_MAXVALUE);
    TPU_E_HWA_SetTCR2MaxCnt(pTPUE, TPU_TCR1_MAXVALUE);

    if (p_etpu_config->eMeasureMode == TPU_DutyMeasurementActiveHigh)
    {
        TPU_E_HWA_SetPDCM(pTPUE, u8channel, TPUE_SM_DT);
        TPU_E_HWA_SetIPAC1(pTPUE, u8channel, TPUE_DETECT_RISING_EDGE_ONLY);
        TPU_E_HWA_SetIPAC2(pTPUE, u8channel, TPUE_DETECT_FALLING_EDGE_ONLY);
    }
    else if (p_etpu_config->eMeasureMode == TPU_DutyMeasurementActiveLow)
    {
        TPU_E_HWA_SetPDCM(pTPUE, u8channel, TPUE_SM_DT);
        TPU_E_HWA_SetIPAC1(pTPUE, u8channel, TPUE_DETECT_FALLING_EDGE_ONLY);
        TPU_E_HWA_SetIPAC2(pTPUE, u8channel, TPUE_DETECT_RISING_EDGE_ONLY);
    }
    else if (p_etpu_config->eMeasureMode == TPU_PeriodMeasurement)
    {
        TPU_E_HWA_SetPDCM(pTPUE, u8channel, TPUE_SM_ST);
        TPU_E_HWA_SetIPAC1(pTPUE, u8channel, p_etpu_config->eInputType);
        TPU_E_HWA_SetIPAC2(pTPUE, u8channel, TPUE_NO_TRANSITIONS);
    }
    else
    {
        /* do nothing */
    }

    TPU_E_HWA_SetMatchER1(pTPUE, u8channel, (TPU_E_HWA_GetTCR1CntVal(pTPUE) + p_etpu_config->u32SampleTime));
    TPU_E_HWA_EnableTransContinue(pTPUE, u8channel, (bool)true);

    /* Here not set channel priority */

    /* Here not enable NVIC */

    TPU_E_HWA_EnableChEventInt(pTPUE, u8channel, (bool)true);
    TPU_E_HWA_EnableMatch(pTPUE, u8channel, (bool)true);
    TPU_E_HWA_EnableSrvReq(pTPUE, u8channel, (bool)true);

    return;
}

/**
 * @brief TPU_CaptureMeasPeriodServiceReq
 *
 */
void TPU_CaptureMeasPeriodServiceReq(uint8_t u8channel, TPU_CaptureCfgType *p_etpu_config)
{
    TPU_E_Type *const pTPUE = TPU_E_BASE_PTRS;
    volatile bool bMeasurement = TPU_E_HWA_GetChEntryTblflag1(pTPUE, u8channel);

    if (TPU_E_HWA_GetChMatchRecLatch1Status(pTPUE, u8channel) == (bool)true)
    {
        TPU_E_HWA_ClearMatch1Event(pTPUE, u8channel);
        TPU_E_HWA_ClearTransDetect1Event(pTPUE, u8channel);
        TPU_E_HWA_ClearTransDetect2Event(pTPUE, u8channel);
        p_etpu_config->LastTime = TPU_E_HWA_GetER1Val(pTPUE, u8channel);
        TPU_E_HWA_SetMatchER1(pTPUE, u8channel, (p_etpu_config->LastTime + p_etpu_config->u32SampleTime));
        TPU_E_HWA_EnableMatch(pTPUE, u8channel, (bool)true);
        TPU_E_HWA_ClearChEventISRFlg(pTPUE, (uint8_t)u8channel);
        TPU_E_HWA_SetChEntryTblflag1(pTPUE, u8channel, (bool)false);
        p_etpu_config->u32PeriodTime = 0;
    }
    else if (TPU_E_HWA_GetChTransDetectLatch1Status(pTPUE, u8channel) == (bool)true)
    {
        TPU_E_HWA_ClearTransDetect1Event(pTPUE, u8channel);
        TPU_E_HWA_ClearChEventISRFlg(pTPUE, (uint8_t)u8channel);
        /* transition happened */
        if (bMeasurement)
        {
            /* Complete once normal measurement */
            if (TPU_E_HWA_GetCaptureER1Val(pTPUE, u8channel) >= p_etpu_config->LastTime)
            {
                p_etpu_config->u32PeriodTime = (TPU_E_HWA_GetCaptureER1Val(pTPUE, u8channel) - p_etpu_config->LastTime);
            }
            else
            {
                p_etpu_config->u32PeriodTime = (TPU_E_HWA_GetCaptureER1Val(pTPUE, u8channel) + TPU_TCR1_MAXVALUE - p_etpu_config->LastTime + 1U);
            }

            TPU_E_HWA_SetChEntryTblflag1(pTPUE, u8channel, (bool)false);
        }
        /* Start normal measurement */
        p_etpu_config->LastTime = TPU_E_HWA_GetCaptureER1Val(pTPUE, u8channel);
        TPU_E_HWA_SetMatchER1(pTPUE, u8channel, (p_etpu_config->LastTime + p_etpu_config->u32SampleTime));

        /* bMeasurement = active */
        TPU_E_HWA_EnableMatch(pTPUE, u8channel, (bool)true);
        TPU_E_HWA_SetChEntryTblflag1(pTPUE, u8channel, (bool)true);
    }
}

/**
 * @brief TPU_CaptureMeasActiveLowServiceReq
 *
 */
void TPU_CaptureMeasActivePeriodServiceReq(uint8_t u8channel, TPU_CaptureCfgType *p_etpu_config)
{
    TPU_E_Type *const pTPUE = TPU_E_BASE_PTRS;

    if (TPU_E_HWA_GetChMatchRecLatch1Status(pTPUE, u8channel) == (bool)true)
    {
        TPU_E_HWA_ClearMatch1Event(pTPUE, u8channel);
        TPU_E_HWA_ClearTransDetect1Event(pTPUE, u8channel);
        TPU_E_HWA_ClearTransDetect2Event(pTPUE, u8channel);
        p_etpu_config->LastTime = TPU_E_HWA_GetER1Val(pTPUE, u8channel);
        TPU_E_HWA_SetMatchER1(pTPUE, u8channel, (p_etpu_config->LastTime + p_etpu_config->u32SampleTime));
        TPU_E_HWA_EnableMatch(pTPUE, u8channel, (bool)true);
        TPU_E_HWA_ClearChEventISRFlg(pTPUE, (uint8_t)u8channel);
        p_etpu_config->u32PeriodTime = 0;
        p_etpu_config->u32ActiveTime = 0;
        bMeasActivePeriodComplete[u8channel] = (bool)false;
    }
    else if ((TPU_E_HWA_GetChTransDetectLatch1Status(pTPUE, u8channel) == (bool)true) || (TPU_E_HWA_GetChTransDetectLatch2Status(pTPUE, u8channel) == (bool)true))
    {
        /* transition1 or 2 happened */
        TPU_E_HWA_ClearTransDetect1Event(pTPUE, u8channel);
        TPU_E_HWA_ClearTransDetect2Event(pTPUE, u8channel);
        TPU_E_HWA_ClearChEventISRFlg(pTPUE, (uint8_t)u8channel);

        /* ER1 stores TCR1 in IPAC1 edge */
        /* Here calculate period */
        if (bMeasActivePeriodComplete[u8channel])
        {
            /* Complete once normal measurement */
            if (TPU_E_HWA_GetCaptureER1Val(pTPUE, u8channel) >= p_etpu_config->StartTime)
            {
                p_etpu_config->u32PeriodTime = (TPU_E_HWA_GetCaptureER1Val(pTPUE, u8channel) - p_etpu_config->StartTime);
            }
            else
            {
                p_etpu_config->u32PeriodTime = (TPU_E_HWA_GetCaptureER1Val(pTPUE, u8channel) + TPU_TCR1_MAXVALUE - p_etpu_config->StartTime + 1);
            }

            /* MeasurementComplete = inactive */
            bMeasActivePeriodComplete[u8channel] = (bool)false;
        }

        /* Start normal low measurement */
        p_etpu_config->LastTime = TPU_E_HWA_GetCaptureER1Val(pTPUE, u8channel);
        p_etpu_config->StartTime = p_etpu_config->LastTime;

        /* ER2 stores TCR1 in IPAC2 edge */
        /* Complete once normal measurement */
        if (TPU_E_HWA_GetCaptureER2Val(pTPUE, u8channel) >= p_etpu_config->LastTime)
        {
            p_etpu_config->u32ActiveTime = (TPU_E_HWA_GetCaptureER2Val(pTPUE, u8channel) - p_etpu_config->LastTime);
        }
        else
        {
            p_etpu_config->u32ActiveTime = (TPU_E_HWA_GetCaptureER2Val(pTPUE, u8channel) + TPU_TCR1_MAXVALUE - p_etpu_config->LastTime + 1);
        }

        /* MeasurementComplete = active */
        bMeasActivePeriodComplete[u8channel] = (bool)true;

        /* Waiting for first IPAC1 edge */
        p_etpu_config->LastTime = TPU_E_HWA_GetCaptureER2Val(pTPUE, u8channel);
        TPU_E_HWA_SetMatchER1(pTPUE, u8channel, (p_etpu_config->LastTime + p_etpu_config->u32SampleTime));
        TPU_E_HWA_EnableMatch(pTPUE, u8channel, (bool)true);
    }
}
