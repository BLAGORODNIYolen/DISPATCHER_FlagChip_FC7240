/**
 * @file fc7xxx_driver_aontimer.c
 * @author Flagchip
 * @brief FC7xxx aontimer driver type definition and API
 * @version 0.1.0
 * @date 2024-01-10
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2024-01-10    Flagchip0076  N/A          First version for FC7240
********************************************************************************/
#include "fc7xxx_driver_aontimer.h"

#include "fc7xxx_driver_csc.h"

extern void AONTIMER_IRQHandler(void);

/** @brief Aontimer common interrupt handle function */
static void Aontimer_CommonProcessInterrupt(void);

/** @brief Aontimer user defined interrupt function */
static Aontimer_InterruptCallBackType   s_pAontimerNotifyPtr = NULL;

/**
 * @brief Initialize aontimer instance
 *
 * @param pInitStruct Aontimer Initialize structure
 */
void AONTIMER_Init(const AONTIMER_InitType *const pInitStruct)
{
    DEV_ASSERT(pInitStruct != NULL);
    /* Disable the Aontimer, and clear control register. */
    AONTIMER_HWA_ConfigModule((uint32_t)0U);
    AONTIMER_HWA_ConfigModulePrescale((uint32_t)0U);
    AONTIMER->CSR |= AONTIMER_CSR_DBGEN(pInitStruct->eDbgMode);
    if (AONTIMER_PULSE_MODE == pInitStruct->eMode)
    {
        AONTIMER_HWA_SelectClkSrcOnPulseMode(pInitStruct->ePulseClkSrc);
        AONTIMER_HWA_ConfigModulePolarity(pInitStruct->ePulsePol);
        AONTIMER_HWA_EnablePulseMode();
        if (pInitStruct->bBypassEn)
        {
            AONTIMER_HWA_EnableBypassMode();
        }
        else
        {
            AONTIMER_HWA_DisableBypassMode();
        }
        AONTIMER_HWA_SetPrescale(pInitStruct->u8PulseFilterWidth);
    }
    else
    {
        AONTIMER_HWA_SetPrescale(pInitStruct->u8Prescaler);
    }
    AONTIMER_HWA_SetModuleRunOnDebug();
    AONTIMER_HWA_SelectModuleClkSrc(pInitStruct->eClkSrc);
    AONTIMER_HWA_SetModuleCompareValue((uint32_t)pInitStruct->u16StartValue);
}

/**
 * @brief De-initialize aontimer instance
 *
 */
void AONTIMER_Deinit(void)
{
    AONTIMER_HWA_ConfigModule((uint32_t)0U);
    AONTIMER_HWA_ConfigModulePrescale((uint32_t)0U);
    AONTIMER_HWA_SetModuleCompareValue((uint32_t)0xFFFFFFFFU);
    s_pAontimerNotifyPtr = NULL;
}

/**
 * @brief Initialize aontimer interrupt functionality
 *
 * @param pIntStruct Aontimer interrupt structure
 * @return Aontimer return type
 * @note this function will disable timer
 */
AONTIMER_StatusType AONTIMER_InitInterrupt(const AONTIMER_IntType *const pIntStruct)
{
    AONTIMER_StatusType eRet = AONTIMER_STATUS_SUCCESS;
    if (NULL == pIntStruct)
    {
        eRet = AONTIMER_STATUS_PARAM_INVALID;
    }
    else
    {
        AONTIMER_HWA_DisableTimer();
        if (pIntStruct->bIntEn)
        {
            AONTIMER_HWA_EnableModuleInterrupt();
            s_pAontimerNotifyPtr = pIntStruct->pIsrNotify;
        }
        else
        {
            AONTIMER_HWA_DisableModuleInterrupt();
            s_pAontimerNotifyPtr = NULL;
        }
    }
    return eRet;
}

/**
 * @brief Enable AONTIMER interrupt
 * @note this function will enable AONTIEMR timer.
 */
void AONTIMER_EnableInterrupt(void)
{
    AONTIMER_HWA_DisableTimer();
    AONTIMER_HWA_EnableModuleInterrupt();
    AONTIMER_HWA_EnableTimer();
}

/**
 * @brief Disable AONTIMER interrupt
 * @note this function will enable AONTIEMR timer.
 *
 */
void AONTIMER_DisableInterrupt(void)
{
    AONTIMER_HWA_DisableTimer();
    AONTIMER_HWA_DisableModuleInterrupt();
    AONTIMER_HWA_EnableTimer();
}

/**
 * @brief Start Aontimer
 *
 */
void AONTIMER_StartTimer(void)
{
    AONTIMER_HWA_EnableTimer();
}

/**
 * @brief Stop Aontimer
 *
 */
void AONTIMER_StopTimer(void)
{
    AONTIMER_HWA_DisableTimer();
}

/**
 * @brief Update value of aontimer counter
 *
 * @param u16StartValue input value, range : 0~65535
 */
void AONTIMER_UpdateCounterValue(const uint16_t u16StartValue)
{
    if (0U == (AONTIMER->CSR & AONTIMER_CSR_TMS_MASK))
    {
        AONTIMER_HWA_DisableTimer();
        AONTIMER_HWA_SetModuleCompareValue((uint32_t)u16StartValue);
        AONTIMER_HWA_EnableTimer();
    }
}

/**
 * @brief Aontimer common interrupt handle function
 *
 */
static void Aontimer_CommonProcessInterrupt(void)
{
    if (NULL != s_pAontimerNotifyPtr)
    {
        s_pAontimerNotifyPtr();
    }
}

/**
 * @brief Aontimer interrupt entry
 *
 */
void AONTIMER_IRQHandler(void)
{
    Aontimer_CommonProcessInterrupt();
    AONTIMER_HWA_ClearInterruptFlag();
    AONTIMER_HWA_EnableTimer();
}
