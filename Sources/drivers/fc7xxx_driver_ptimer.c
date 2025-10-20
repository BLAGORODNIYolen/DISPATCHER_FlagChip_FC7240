/**
 * @file fc7xxx_driver_ptimer.c
 * @author Flagchip0126
 * @brief FC7xxx PTIMER driver source code
 * @version 0.1.0
 * @date 2024-01-15
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Author        CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-15    Flagchip0126  N/A          First version for FC7240
   ******************************************************************************** */

#include <interrupt_manager.h>

#include "fc7xxx_driver_ptimer.h"
#include "fc7xxx_driver_scg.h"
#include "HwA_scm.h"

static PTIMER_Type *const s_apPtimerBase[PTIMER_INSTANCE_COUNT] = PTIMER_BASE_PTRS;

static uint8_t s_u8ChnNum[PTIMER_INSTANCE_COUNT] = {0U};

static PTIMER_InterruptCallbackType s_apPtimerIntNotify[PTIMER_INSTANCE_COUNT] = {NULL};
static PTIMER_SeqErrorCallbackType s_apPtimerSeqErrorNotify[ADC_INSTANCE_COUNT] = {NULL};

/**
 * @brief Calculate the delay value base on the delay micro seconds
 *
 * @param eInstance the Ptimer instance to use
 * @param u32DelayUs the delay time in micro seconds
 * @return uint16_t the delay time in ptimer clock count
 */
static uint16_t PTIMER_CalcDelayValue(const PTIMER_InstanceType eInstance, const uint32_t u32DelayUs);

/**
 * @brief the internal Ptimer interrupt handler
 *
 * @param eInstance the Ptimer instance to use
 */
static void PTIMERn_IRQHandler(const PTIMER_InstanceType eInstance);

void PTIMER0_IRQHandler(void);

void PTIMER1_IRQHandler(void);

static uint16_t PTIMER_CalcDelayValue(const PTIMER_InstanceType eInstance, const uint32_t u32DelayUs)
{
    DEV_ASSERT((uint8_t)eInstance < PTIMER_INSTANCE_COUNT);

    const PTIMER_Type *const pPtimer = s_apPtimerBase[eInstance];

    uint32_t u32DelayVal;
    uint32_t u32SysFreq;
    uint32_t u32PtimerFreqUs = 0U;
    PTIMER_ClockPreDividerType ePreDivider = PTIMER_HWA_GetDivPrescaler(pPtimer);
    PTIMER_ClockPreDivMultiplyFactorType ePreDivMultFactor = PTIMER_HWA_GetDivMultiply(pPtimer);
    uint8_t u8Prescaler = (1U << ePreDivider);
    uint8_t u8PrescalerMult = 1U;

    switch (ePreDivMultFactor)
    {
        case PTIMER_PRE_DIVIDER_MULTIPLY_BY_1:
            u8PrescalerMult = 1U;
            break;

        case PTIMER_PRE_DIVIDER_MULTIPLY_BY_10:
            u8PrescalerMult = 10U;
            break;

        case PTIMER_PRE_DIVIDER_MULTIPLY_BY_20:
            u8PrescalerMult = 20U;
            break;

        case PTIMER_PRE_DIVIDER_MULTIPLY_BY_40:
            u8PrescalerMult = 40U;
            break;

        default:
            u8PrescalerMult = 1U;
            break;
    }

    u32SysFreq = SCG_GetScgClockFreq(SCG_CORE_CLK);
    u32PtimerFreqUs = u32SysFreq / 1000000U;

    u32DelayVal = (u32DelayUs * u32PtimerFreqUs) / ((uint32_t)u8Prescaler * u8PrescalerMult);
    DEV_ASSERT(u32DelayVal < (1U << 16U));

    return (uint16_t)u32DelayVal;
}

void PTIMER0_IRQHandler(void)
{
    PTIMERn_IRQHandler(PTIMER_INSTANCE_0);
}

void PTIMER1_IRQHandler(void)
{
    PTIMERn_IRQHandler(PTIMER_INSTANCE_1);
}

static void PTIMERn_IRQHandler(const PTIMER_InstanceType eInstance)
{
    PTIMER_Type *const pPtimer = s_apPtimerBase[eInstance];
    uint8_t u8Channel;
    if (PTIMER_HWA_GetInterruptFlag(pPtimer) == true)
    {
        PTIMER_HWA_ClearInterruptFlag(pPtimer);
        if (s_apPtimerIntNotify[eInstance] != NULL)
        {
            s_apPtimerIntNotify[eInstance]();
        }
    }

    for (u8Channel = 0U; u8Channel < s_u8ChnNum[eInstance]; u8Channel++)
    {
        if (PTIMER_HWA_GetChannelSequenceErrorFlag(pPtimer, u8Channel) == true)
        {
            PTIMER_HWA_ClearChannelSequenceErrorFlag(pPtimer, u8Channel);
            if (s_apPtimerSeqErrorNotify[eInstance] != NULL)
            {
                s_apPtimerSeqErrorNotify[eInstance](u8Channel);
            }
        }
    }
}

void PTIMER_DeInit(const PTIMER_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < PTIMER_INSTANCE_COUNT);

    PTIMER_Type *const pPtimer = s_apPtimerBase[eInstance];
    uint8_t u8Chn;

    /* Reset PTIMER Status Ctrl Register */
    PTIMER_HWA_SetStatusCtrl(pPtimer, 0U);
    /* Enable PTIMER */
    PTIMER_HWA_Enable(pPtimer);
    /* Reset PTIMER Max Cnt Register */
    PTIMER_HWA_SetMaxCount(pPtimer, 0xFFFFU);
    /* Reset PTIMER Int Dly Register */
    PTIMER_HWA_SetInterruptDelay(pPtimer, 0xFFFFU);

    for (u8Chn = 0U; u8Chn < PTIMER_DLY_CNT; u8Chn++)
    {
        PTIMER_HWA_SetChannelControl(pPtimer, u8Chn, false, false, false);
        PTIMER_HWA_ClearChannelCounterFlag(pPtimer, u8Chn);
        PTIMER_HWA_ClearChannelSequenceErrorFlag(pPtimer, u8Chn);
        PTIMER_HWA_SetChannelDelay(pPtimer, u8Chn, 0U);
    }

    /* For Pulse out trigger. */
    PTIMER_HWA_DisablePulseOut(pPtimer);
    PTIMER_HWA_SetPulseOutDelay(pPtimer, 0U, 0U);

    PTIMER_HWA_LoadValue(pPtimer);
    PTIMER_HWA_Disable(pPtimer);
}

void PTIMER_Init(const PTIMER_InstanceType eInstance, const PTIMER_InitType *const pInitCfg)
{
    DEV_ASSERT(pInitCfg != NULL_PTR);
    DEV_ASSERT((uint8_t)eInstance < PTIMER_INSTANCE_COUNT);

    PTIMER_Type *const pPtimer = s_apPtimerBase[(uint8_t)eInstance];

    PTIMER_DeInit(eInstance);

    PTIMER_HWA_SetLoadMode(pPtimer, pInitCfg->eLoadValueMode);
    PTIMER_HWA_SetDivPrescaler(pPtimer, pInitCfg->eClkPreDiv);
    PTIMER_HWA_SetTriggerSource(pPtimer, pInitCfg->eTriggerInput);
    PTIMER_HWA_SetDivMultiply(pPtimer, pInitCfg->eClkPreMultFactor);
    PTIMER_HWA_SetContinuoiusModeFlag(pPtimer, pInitCfg->bContinuousModeEnable);
    PTIMER_HWA_SetDMAEnableFlag(pPtimer, pInitCfg->bDmaEnable);
}

void PTIMER_InitChannel(const PTIMER_InstanceType eInstance,
                        const PTIMER_ChannelCfgType aChannelCfg[], const uint8_t u8ChnNum)
{
    DEV_ASSERT(aChannelCfg != NULL_PTR);
    DEV_ASSERT((uint8_t)eInstance < PTIMER_INSTANCE_COUNT);
    DEV_ASSERT(u8ChnNum <= PTIMER_DLY_CNT);

    PTIMER_Type *const pPtimer = s_apPtimerBase[eInstance];

    uint8_t u8ChnIdx;
    uint16_t u16PtimerChannelDelay ;

    for (u8ChnIdx = 0U; u8ChnIdx < u8ChnNum; u8ChnIdx++)
    {
        PTIMER_HWA_SetChannelControl(pPtimer, u8ChnIdx, aChannelCfg[u8ChnIdx].bPreTriggerEnable,
                                     aChannelCfg[u8ChnIdx].bPreTriggerOutputEnable, aChannelCfg[u8ChnIdx].bPreTriggerBackToBackEnable);
        u16PtimerChannelDelay = PTIMER_CalcDelayValue(eInstance, aChannelCfg[u8ChnIdx].u32DelayUs);
        PTIMER_HWA_SetChannelDelay(pPtimer, u8ChnIdx, u16PtimerChannelDelay);
    }
    s_u8ChnNum[eInstance] = u8ChnNum;
}

void PTIMER_InitInterrupt(const PTIMER_InstanceType eInstance,
                          const PTIMER_InterruptType *const pInterruptCfg)
{
    DEV_ASSERT(pInterruptCfg != NULL_PTR);
    DEV_ASSERT((uint8_t)eInstance < PTIMER_INSTANCE_COUNT);
    PTIMER_Type *const pPtimer = s_apPtimerBase[eInstance];

    PTIMER_HWA_SetSeqErrIntEnableFlag(pPtimer, pInterruptCfg->bSeqErrIntEnable);
    uint16_t u16IntDelay = PTIMER_CalcDelayValue(eInstance, pInterruptCfg->u32IntDelayPeriodUs);
    PTIMER_HWA_SetInterruptDelay(pPtimer, u16IntDelay);
    PTIMER_HWA_SetInterruptEnableFlag(pPtimer, pInterruptCfg->bDelayIntEnable);

    if (pInterruptCfg->bDelayIntEnable)
    {
        s_apPtimerIntNotify[eInstance] = pInterruptCfg->pIntNotify;
    }
    else
    {
        s_apPtimerIntNotify[eInstance] = NULL;
    }

    if (pInterruptCfg->bSeqErrIntEnable)
    {
        s_apPtimerSeqErrorNotify[eInstance] = pInterruptCfg->pSeqErrorNotify;
    }
    else
    {
        s_apPtimerSeqErrorNotify[eInstance] = NULL;
    }

    if ((pInterruptCfg->bSeqErrIntEnable == true) || (pInterruptCfg->bDelayIntEnable == true))
    {
        switch ((uint8_t)eInstance)
        {
            case (uint8_t)PTIMER_INSTANCE_0:
                IntMgr_EnableInterrupt(PTIMER0_IRQn);
                break;

            case (uint8_t)PTIMER_INSTANCE_1:
                IntMgr_EnableInterrupt(PTIMER1_IRQn);
                break;

            default:
                break;
        }
    }
}

void PTIMER_SetPeriod(const PTIMER_InstanceType eInstance, uint32_t u32PeriodUs)
{
    DEV_ASSERT((uint8_t)eInstance < PTIMER_INSTANCE_COUNT);

    PTIMER_Type *const pPtimer = s_apPtimerBase[eInstance];

    uint16_t u16MaxCnt = PTIMER_CalcDelayValue(eInstance, u32PeriodUs);
    PTIMER_HWA_SetMaxCount(pPtimer, u16MaxCnt);
}

void PTIMER_SetPulseOut(const PTIMER_InstanceType eInstance, const PTIMER_PulseOutType *pPulseOutCfg)
{
    DEV_ASSERT((uint8_t)eInstance < PTIMER_INSTANCE_COUNT);
    DEV_ASSERT(pPulseOutCfg != NULL_PTR);
    PTIMER_Type *const pPtimer = s_apPtimerBase[eInstance];

    uint16_t u16PulseOutCfgDlyHigh = PTIMER_CalcDelayValue(eInstance, pPulseOutCfg->u32PulseOutDlyHighUs);
    uint16_t u16PulseOutCfgDlyLow = PTIMER_CalcDelayValue(eInstance, pPulseOutCfg->u32PulseOutDlyLowUs);

    PTIMER_HWA_SetPulseOutDelay(pPtimer, u16PulseOutCfgDlyHigh, u16PulseOutCfgDlyLow);
}

void PTIMER_LoadValue(const PTIMER_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < PTIMER_INSTANCE_COUNT);

    PTIMER_Type *const pPtimer = s_apPtimerBase[eInstance];
    PTIMER_HWA_LoadValue(pPtimer);
}

void PTIMER_Enable(const PTIMER_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < PTIMER_INSTANCE_COUNT);

    PTIMER_Type *const pPtimer = s_apPtimerBase[eInstance];
    PTIMER_HWA_Enable(pPtimer);
}

void PTIMER_Disable(const PTIMER_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < PTIMER_INSTANCE_COUNT);

    PTIMER_Type *const pPtimer = s_apPtimerBase[eInstance];
    PTIMER_HWA_Disable(pPtimer);
}

void PTIMER_EnablePulseOut(const PTIMER_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < PTIMER_INSTANCE_COUNT);

    PTIMER_Type *const pPtimer = s_apPtimerBase[eInstance];
    PTIMER_HWA_EnablePulseOut(pPtimer);
}

void PTIMER_DisablePulseOut(const PTIMER_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < PTIMER_INSTANCE_COUNT);

    PTIMER_Type *const pPtimer = s_apPtimerBase[eInstance];
    PTIMER_HWA_DisablePulseOut(pPtimer);
}

void PTIMER_SelectInstance01BackToBackMode(SCM_PTimerLMSelType ePTimerLoopMode)
{
	SCM_HWA_PTimerLoopModeSel(ePTimerLoopMode);
}

void PTIMER_GenerateSWTrigger(const PTIMER_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < PTIMER_INSTANCE_COUNT);

    PTIMER_Type *const pPtimer = s_apPtimerBase[eInstance];
    PTIMER_HWA_GenerateSwTrigger(pPtimer);
}
