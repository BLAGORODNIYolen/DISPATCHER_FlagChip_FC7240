/**
 * @file fc7xxx_driver_rtc.c
 * @author Flagchip
 * @brief FC7xxx rtc driver type definition and API
 * @version 0.1.0
 * @date  2024-01-10
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
#include "fc7xxx_driver_rtc.h"

#include "fc7xxx_driver_csc.h"



/**
 *  @brief Rtc user defined alarm interrupt function
 * */
static RTC_InterruptCallBackType s_pRTCAlarmNotifyPtr = NULL;

/**
 *  @brief Rtc user defined seconds interrupt function
 * */
static RTC_InterruptCallBackType s_pRTCSecondNotifyPtr = NULL;

/**
 *  @brief Rtc user defined overflow interrupt function
 * */
static RTC_InterruptCallBackType s_pRTCOverFlowNotifyPtr = NULL;

/**
 *  @brief RTC common interrupt function
 * */
static void Rtc_CommonProcessInterrupt(const RTC_IntEventType eIntEvent);

/**
 *  @brief RTC  interrupt entry
 * */
void RTC_IRQHandler(void);


/**
 * @brief Initialize Rtc instance
 *
 * @param pInitStruct Rtc initialization structure
 * @return Rtc return type
 * @note This function could only write once after POR.
 */
void RTC_Init(const RTC_InitType *const pInitStruct)
{
    DEV_ASSERT(pInitStruct != NULL);
    /* Disable interrupt */
    RTC_HWA_DisableOverflowInterrupt();
    /*Disable Second interrupt*/
    RTC_HWA_DisableSecondInterrupt();
    /*Disable Alarm interrupt*/
    RTC_HWA_DisableAlarmInterrupt();
    /* disable the rtc clock*/
    RTC_HWA_DisableRtcCounter();
    /* clear PR register */
    RTC_HWA_SetPrescalerCounterValue(0U);
    /* clear SR register */
    RTC_HWA_SetSecondCounterValue(0U);
    /* clear CR register */
    RTC_HWA_ConfigControl(0U);
    if (pInitStruct->bStableClkoutFreq)
    {
        RTC_HWA_SetClkoutFreqStable();
    }
    else
    {
        RTC_HWA_SetClkoutFromSelectFreq();
    }
    /* TSIC should only be altered when TSIE is clear */
    RTC_HWA_SetSecondAndClkoutFreq(pInitStruct->eSecIntAndClkoutFreq);
    /* Set alarm value */
    RTC_HWA_SetAlarmCounterValue(pInitStruct->u32AlarmValue);
}

/**
 * @brief Rtc set interrupt
 *
 * @param pIntStruct interrupt structure pointer
 * @return Rtc return type
 * @note this function will stop Rtc timer
 */
RTC_StatusType RTC_InitInterrupt(const RTC_InterruptType *const pIntStruct)
{
    RTC_StatusType eRet = RTC_STATUS_SUCCESS;
    if (NULL == pIntStruct)
    {
        eRet = RTC_STATUS_PARAM_INVALID;
    }
    else
    {
        /* disable the rtc timer */
        RTC_HWA_DisableRtcCounter();
        if (pIntStruct->bAlarmIntEn)
        {
            /* enable alarm interrupt */
            RTC_HWA_EnableAlarmInterrupt();
            s_pRTCAlarmNotifyPtr = pIntStruct->pIsrAlarmNotify;
        }
        else
        {
            /* disable alarm interrupt */
            RTC_HWA_DisableAlarmInterrupt();
            s_pRTCAlarmNotifyPtr = NULL;
        }

        if (pIntStruct->bOverflowIntEn)
        {
            /* enable overflow interrupt */
            RTC_HWA_EnableOverflowInterrupt();
            s_pRTCOverFlowNotifyPtr = pIntStruct->pIsrOverflowNotify;
        }
        else
        {
            /* disable overflow interrupt */
        	RTC_HWA_DisableOverflowInterrupt();
            s_pRTCOverFlowNotifyPtr = NULL;
        }

        if (pIntStruct->bSecondIntEn)
        {
            /* enable second interrupt */
            RTC_HWA_EnableSecondInterrupt();
            s_pRTCSecondNotifyPtr = pIntStruct->pIsrSecondNotify;
        }
        else
        {
            /* disable second interrupt */
            RTC_HWA_DisableSecondInterrupt();
            s_pRTCSecondNotifyPtr = NULL;
        }
    }
    return eRet;
}

/**
 * @brief De-initialize Rtc instance
 *
 */
void RTC_Deinit(void)
{
    /* disable the rtc timer */
    RTC_HWA_DisableRtcCounter();
    /* clear PR register */
    RTC_HWA_SetPrescalerCounterValue(0U);
    /* clear SR register */
    RTC_HWA_SetSecondCounterValue(0U);
    /* clear TAR register */
    RTC_HWA_SetAlarmCounterValue(0U);
    /* clear IER register */
    RTC_HWA_SetInterruptValue(0U);
    /* clear CR register */
    RTC_HWA_ConfigControl(0U);
    s_pRTCAlarmNotifyPtr = NULL;
    s_pRTCSecondNotifyPtr = NULL;
    s_pRTCOverFlowNotifyPtr = NULL;
}

/**
 * @brief Rtc enable interrupt
 *
 * @param bAlarmIntEn whether enable alarm interrupt
 * @param bSecondIntEn whether enable second interrupt
 * @param bOverflowIntEn whether enable overflow interrupt
 */
void RTC_EnableInterrupt(const bool bAlarmIntEn, const bool bSecondIntEn, const bool bOverflowIntEn)
{
    /* disable the rtc timer */
    RTC_HWA_DisableRtcCounter();
    if (bAlarmIntEn)
    {
        /* enable alarm interrupt */
        RTC_HWA_EnableAlarmInterrupt();
    }
    if (bSecondIntEn)
    {
        /* enable second interrupt */
        RTC_HWA_EnableSecondInterrupt();
    }
    if (bOverflowIntEn)
    {
        /* enable overflow interrupt */
        RTC_HWA_EnableOverflowInterrupt();
    }
    /*enable the rtc clock*/
    RTC_HWA_EnableRtcCounter();
}

/**
 * @brief Rtc disable interrupt
 *
 * @param bAlarmIntEn whether disable alarm interrupt
 * @param bSecondIntEn whether disable second interrupt
 * @param boverflowIntEn whether disable overflow interrupt
 */
void RTC_DisableInterrupt(const bool bAlarmIntEn, const bool bSecondIntEn, const bool boverflowIntEn)
{
    /* disable the rtc timer */
    RTC_HWA_DisableRtcCounter();
    if (bAlarmIntEn)
    {
        /* disable alarm interrupt */
        RTC_HWA_DisableAlarmInterrupt();
    }
    if (bSecondIntEn)
    {
        /* disable second interrupt */
        RTC_HWA_DisableSecondInterrupt();
    }
    if (boverflowIntEn)
    {
        /* disable overflow interrupt */
        RTC_HWA_DisableOverflowInterrupt();
    }
    /*enable the rtc clock*/
    RTC_HWA_EnableRtcCounter();
}

/**
 * @brief rtc start
 *
 */
void RTC_Start(void)
{
    /*enable the rtc clock*/
    RTC_HWA_EnableRtcCounter();
}

/**
 * @brief Rtc stop
 *
 */
void RTC_Stop(void)
{
    /*disable the rtc clock*/
    RTC_HWA_DisableRtcCounter();
}

/**
 * @brief Rtc alarm value
 *
 * @param u32AlarmValue Input value
 */
void RTC_UpdateAlarmValue(const uint32_t u32AlarmValue)
{
    /*disable the rtc clock*/
    RTC_HWA_DisableRtcCounter();
    /* clear PR register */
    RTC_HWA_SetPrescalerCounterValue(0U);
    /* Set alarm value */
    RTC_HWA_SetAlarmCounterValue(RTC_HWA_ReadSecondValue() + u32AlarmValue - (uint32_t)1U);
    /*enable the rtc clock*/
    RTC_HWA_EnableRtcCounter();
}

/**
 * @brief Get Rtc counter value
 *
 * @return Rtc counter value
 */
uint32_t RTC_GetTime(void)
{
    return RTC_HWA_ReadSecondValue();
}

/**
 * @brief Check RTC overflow flag
 *
 * @return Overflow flag
 */
bool RTC_CheckOverflowFlag(void)
{
    return RTC_HWA_GetOverflowFlag();
}

/**
 * @brief Set second counter value
 * @param u32Value the second value.
 * */
void   RTC_SetSecondCounterValue(uint32_t u32Value)
{
	RTC_HWA_DisableRtcCounter();
    RTC_HWA_SetSecondCounterValue(u32Value);
    RTC_HWA_EnableRtcCounter();
}

/**
 * @brief RTC common interrupt function
 *
 * @param eIntEvent RTC interrupt event
 */
static void Rtc_CommonProcessInterrupt(const RTC_IntEventType eIntEvent)
{
    switch (eIntEvent)
    {
    case RTC_ALARM_INT:
        if (NULL != s_pRTCAlarmNotifyPtr)
        {
            s_pRTCAlarmNotifyPtr();
        }
        break;
    case RTC_SECOND_INT:
        if (NULL != s_pRTCSecondNotifyPtr)
        {
            s_pRTCSecondNotifyPtr();
        }
        break;
    case RTC_OVERFLOW_INT:
        if (NULL != s_pRTCOverFlowNotifyPtr)
        {
            s_pRTCOverFlowNotifyPtr();
        }
        break;
    default:
        /* do nothing*/
        break;
    }
}

/**
 * @brief RTC alarm interrupt handler entry
 *
 */
void RTC_IRQHandler(void)
{
    bool  overflow_flag = RTC_HWA_GetOverflowFlag();
    bool  overflow_enablebit = RTC_HWA_GetOverflowEnable();
    bool alarm_flag  = RTC_HWA_GetAlarmFlag();
    bool alarm_enablebit = RTC_HWA_GetAlarmEnable();
    if ((overflow_flag) && (overflow_enablebit))
    {
        /*oveflow Int*/
    	 /*disable the rtc clock*/
    	RTC_HWA_DisableRtcCounter();
    	RTC_HWA_SetSecondCounterValue(0u);
        Rtc_CommonProcessInterrupt(RTC_OVERFLOW_INT);


    }
    else if ((alarm_flag) && (alarm_enablebit))
    {
        /*alarm Int*/
    	RTC_HWA_SetAlarmCounterValue(0u);
        Rtc_CommonProcessInterrupt(RTC_ALARM_INT);

    }
    else
    {
    	/*second Int*/
        Rtc_CommonProcessInterrupt(RTC_SECOND_INT);
    }
}
