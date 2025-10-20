/**
 * @file fc7xxx_driver_tmu.c
 * @author Flagchip
 * @brief FC7xxx TMU driver source code
 * @version 0.1.0
 * @date 2023-12-29
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/*********************************************************************************
*   Revision History:
*
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   0.1.0       2023-12-29    qxw074        N/A          First version for FC7240
******************************************************************************** */

#include "fc7xxx_driver_tmu.h"
#include "fc7xxx_driver_pcc.h"
#include "interrupt_manager.h"

/********* Local Variables ************/
/** @brief TMU peripheral base pointers */
static TMU_Type *const s_apTmuBase = TMU_BASE_PTRS;
/** @brief Temperature over 150 Celsius notify callback function point */
static TMU_TempOver150InterruptCallbackType s_apTmuOver150Notify = NULL;
/** @brief Temperature over 125 Celsius notify callback function point */
static TMU_TempOver125InterruptCallbackType s_apTmuOver125Notify = NULL;
/** @brief The Flag-based temperature sensor ready notify callback function point */
static TMU_TempFlagReadyInterruptCallbackType s_apTmuFlagReadyNotify = NULL;
/** @brief The Voltage-based temperature sensor ready notify callback function point */
static TMU_TempVoltageReadyInterruptCallbackType s_apTmuVoltgeReadyNotify = NULL;

/***************TMU IRQ Functions*****************/
/** @brief TMU interrupt entry */
void TMU_IRQHandler(void);
/**
 * @brief TMU irq handler
 *
 */
void TMU_IRQHandler(void)
{
    TMU_Type *const pTmu = s_apTmuBase;
    if (TMU_HWA_GetFlagTemperature150InterruptFlag(pTmu) == true)
    {
        if (TMU_HWA_Get150Flag(pTmu) == true)
        {
            if (s_apTmuOver150Notify != NULL)
            {
                s_apTmuOver150Notify();
            }
            TMU_HWA_Clear150Flag(pTmu);
        }
    }
    if (TMU_HWA_GetFlagTemperature125InterruptFlag(pTmu) == true)
    {
        if (TMU_HWA_Get125Flag(pTmu) == true)
        {
            if (s_apTmuOver125Notify != NULL)
            {
                s_apTmuOver125Notify();
            }
            TMU_HWA_Clear125Flag(pTmu);
        }
    }
    if (TMU_HWA_GetFlagTemperatureReadyInterruptFlag(pTmu) == true)
    {
        if (TMU_HWA_GetFlagTemperatureReady(pTmu) == true)
        {
            if (s_apTmuFlagReadyNotify != NULL)
            {
                s_apTmuFlagReadyNotify();
            }
            TMU_HWA_SetTemperatureLockStatus(pTmu, TMU_TF_TV_UNLOCK);
            TMU_HWA_SetFlagTemperatureReadyInterruptFlag(pTmu, false);
            TMU_HWA_SetTemperatureLockStatus(pTmu, TMU_TF_TV_LOCK);
        }
    }
    if (TMU_HWA_GetVoltageTemperatureReadyInterruptFlag(pTmu) == true)
    {
        if (TMU_HWA_GetVoltageTemperatureReady(pTmu) == true)
        {
            if (s_apTmuVoltgeReadyNotify != NULL)
            {
                s_apTmuVoltgeReadyNotify();
            }
            TMU_HWA_SetTemperatureLockStatus(pTmu, TMU_TF_TV_UNLOCK);
            TMU_HWA_SetVoltageTemperatureReadyInterruptFlag(pTmu, false);
            TMU_HWA_SetTemperatureLockStatus(pTmu, TMU_TF_TV_LOCK);
        }
    }
}

/**
 * @brief Initialize the TMU instance
 *
 * @param pInitCfg the configurations of the TMU instance
 */
void TMU_Init(const TMU_InitType *const pInitCfg)
{
    DEV_ASSERT(pInitCfg != NULL);

    TMU_Type *const pTmu = s_apTmuBase;
    uint32_t u32FlagCtrl;
    uint32_t u32VoltageCtrl;
    uint8_t u8FlagStartupCnt;
    uint8_t u8VoltageStartupCnt;

    PCC_ClkSrcType eAdcClkName = PCC_CLK_TMU0;
    uint32_t u32TmuClk;
    u32TmuClk = PCC_GetPccFunctionClock(eAdcClkName);

    u8FlagStartupCnt = (uint8_t)((u32TmuClk * 11U) / 127000000U + 1U);
    u8VoltageStartupCnt = (uint8_t)((u32TmuClk * 5U) / 127000000U + 1U);
    if (u8FlagStartupCnt > 15U)
    {
        u8FlagStartupCnt = 15U;
    }
    if (u8VoltageStartupCnt > 7U)
    {
        u8VoltageStartupCnt = 7U;
    }

    u32FlagCtrl = TMU_TF_CTRL_TF_150F_IE(pInitCfg->bTemperatureOver150IntEn) |
                  TMU_TF_CTRL_TF_125F_IE(pInitCfg->bTemperatureOver125IntEn) |
                  TMU_TF_CTRL_TF_RDYF_IE(pInitCfg->bFlagTempReadyIntEn) |
                  TMU_TF_CTRL_TF_HYSOFF(pInitCfg->eFlagTempHysteresisCon) |
                  TMU_TF_CTRL_TF_START_CNT(u8FlagStartupCnt) |
                  TMU_TF_CTRL_TF_FILT_BYP(pInitCfg->eFlagTempFilterBypassCon);
    TMU_HWA_SetFlagTempCtrl(pTmu, u32FlagCtrl);

    u32VoltageCtrl = TMU_TV_CTRL_TV_RDYF_IE(pInitCfg->bVoltageTempReadyIntEn) |
                     TMU_TV_CTRL_TV_START_CNT(u8VoltageStartupCnt);
    TMU_HWA_SetVoltageTempCtrl(pTmu, u32VoltageCtrl);

    TMU_HWA_SetStopAck(pInitCfg->bSmicsStopAckEn);

    /* interrupt callback function */
    s_apTmuOver150Notify = pInitCfg->pTemp150Notify;
    s_apTmuOver125Notify = pInitCfg->pTemp125Notify;
    s_apTmuFlagReadyNotify = pInitCfg->pFlagReadyNotify;
    s_apTmuVoltgeReadyNotify = pInitCfg->pVoltagReadyNotify;

    TMU_HWA_SetTemperatureLockStatus(pTmu, TMU_TF_TV_LOCK);
}

/**
 * @brief Enable the Flag-based temperature sensor
 *
 * @return TMU_StatusType TMU_STATUS_SUCCESS when enable successfully, others fail
 */
TMU_StatusType TMU_FlagTempEnable(void)
{
    TMU_StatusType eRet;
    uint32_t u32TimeOut = 15000000U;
    TMU_Type *const pTmu = s_apTmuBase;

    TMU_HWA_SetTemperatureLockStatus(pTmu, TMU_TF_TV_UNLOCK);
    TMU_HWA_SetFlagTemperatureEnableStatus(pTmu, true);
    while ((TMU_HWA_GetFlagTemperatureReady(pTmu) != true) && (u32TimeOut != 0U))
    {
        u32TimeOut--;
    }
    if (u32TimeOut != 0U)
    {
        eRet = TMU_STATUS_SUCCESS;
        TMU_HWA_ClearFlagTemperatureReady(pTmu);
    }
    else
    {
        eRet = TMU_STATUS_TIMEOUT;
    }
    TMU_HWA_SetTemperatureLockStatus(pTmu, TMU_TF_TV_LOCK);
    return eRet;
}

/**
 * @brief Disable the Flag-based temperature sensor
 *
 * @return TMU_StatusType TMU_STATUS_SUCCESS when disable successfully, others fail
 */
TMU_StatusType TMU_FlagTempDisable(void)
{
    TMU_StatusType eRet;
    uint32_t u32TimeOut = 15000000U;
    TMU_Type *const pTmu = s_apTmuBase;

    TMU_HWA_SetTemperatureLockStatus(pTmu, TMU_TF_TV_UNLOCK);
    TMU_HWA_SetFlagTemperatureEnableStatus(pTmu, false);
    TMU_HWA_ClearFlagTemperatureReady(pTmu);
    while ((TMU_HWA_GetFlagTemperatureEnableStatus(pTmu) == true) && (u32TimeOut != 0U))
    {
        u32TimeOut--;
    }
    if (u32TimeOut != 0U)
    {
        eRet = TMU_STATUS_SUCCESS;
    }
    else
    {
        eRet = TMU_STATUS_TIMEOUT;
    }
    TMU_HWA_SetTemperatureLockStatus(pTmu, TMU_TF_TV_LOCK);
    return eRet;
}

/**
 * @brief Enable the Voltage-based temperature sensor
 *
 * @return TMU_StatusType TMU_STATUS_SUCCESS when enable successfully, others fail
 */
TMU_StatusType TMU_VoltageTempEnable(void)
{
    TMU_StatusType eRet;
    uint32_t u32TimeOut = 15000000U;
    TMU_Type *const pTmu = s_apTmuBase;

    TMU_HWA_SetTemperatureLockStatus(pTmu, TMU_TF_TV_UNLOCK);
    TMU_HWA_SetVoltageTemperatureEnableStatus(pTmu, true);
    while ((TMU_HWA_GetVoltageTemperatureReady(pTmu) != true) && (u32TimeOut != 0U))
    {
        u32TimeOut--;
    }
    if (u32TimeOut != 0U)
    {
        eRet = TMU_STATUS_SUCCESS;
        TMU_HWA_ClearVoltageTemperatureReady(pTmu);
    }
    else
    {
        eRet = TMU_STATUS_TIMEOUT;
    }
    TMU_HWA_SetTemperatureLockStatus(pTmu, TMU_TF_TV_LOCK);
    return eRet;
}

/**
 * @brief Disable the Voltage-based temperature sensor
 *
 * @return TMU_StatusType TMU_STATUS_SUCCESS when disable successfully, others fail
 */
TMU_StatusType TMU_VoltageTempDisable(void)
{
    TMU_StatusType eRet;
    uint32_t u32TimeOut = 15000000U;
    TMU_Type *const pTmu = s_apTmuBase;

    TMU_HWA_SetTemperatureLockStatus(pTmu, TMU_TF_TV_UNLOCK);
    TMU_HWA_SetVoltageTemperatureEnableStatus(pTmu, false);
    TMU_HWA_ClearVoltageTemperatureReady(pTmu);
    while ((TMU_HWA_GetVoltageTemperatureEnableStatus(pTmu) == true) && (u32TimeOut != 0U))
    {
        u32TimeOut--;
    }
    if (u32TimeOut != 0U)
    {
        eRet = TMU_STATUS_SUCCESS;
    }
    else
    {
        eRet = TMU_STATUS_TIMEOUT;
    }
    TMU_HWA_SetTemperatureLockStatus(pTmu, TMU_TF_TV_LOCK);
    return eRet;
}

/**
 * @brief Check if cleaning flag is required
 *
 */
void TMU_TempOverClear(void)
{
    TMU_Type *const pTmu = s_apTmuBase;
    if (TMU_HWA_Get150Flag(pTmu))
    {
        if (!TMU_HWA_Get150Status(pTmu))
        {
            TMU_HWA_Clear150Flag(pTmu);
        }
    }
    if (TMU_HWA_Get125Flag(pTmu))
    {
        if (!TMU_HWA_Get125Status(pTmu))
        {
            TMU_HWA_Clear125Flag(pTmu);
        }
    }
}

/**
 * @brief Get the temperature code from ADC
 *
 * @return uint32_t the value records the ADC conversion results for voltage-based temperature sensor result in 135 Celsius
 */
uint32_t TMU_GetTcode(void)
{
    TMU_Type *const pTmu = s_apTmuBase;
    return TMU_HWA_GetTemperatureCode(pTmu);
}

/**
 * @brief Get the slope factor
 *
 * @return uint32_t the value records the slope factor for voltage-based temperature sensor
 */
uint32_t TMU_GetTslope(void)
{
    TMU_Type *const pTmu = s_apTmuBase;
    return TMU_HWA_GetSlopeFactor(pTmu);
}
