/**
 * @file fc7xxx_driver_rtc.h
 * @author Flagchip
 * @brief FC7xxx rtc driver type definition and API
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


#ifndef DRIVER_INCLUDE_FC7XXX_DRIVER_RTC_H_
#define DRIVER_INCLUDE_FC7XXX_DRIVER_RTC_H_

#include"HwA_rtc.h"


/**
 * @addtogroup fc7xxx_driver_rtc
 * @{
 */

/** @brief Rtc return type. */
typedef enum
{
    RTC_STATUS_SUCCESS = 0U,                        /**< rtc status is success */
    RTC_STATUS_PARAM_INVALID = 1U,                  /**< rtc status is failed because the param is invalid */
    RTC_STATUS_FUNCTION_ERROR = 2U,                 /**< rtc status is failed because the function is error */
    RTC_STATUS_CLOCK_INVALID = 3U                   /**< rtc status is failed because the clock is invalid */
} RTC_StatusType;

/** @brief Rtc mode */
typedef enum
{
    RTC_ALARM_INT = 0U,                          /**< rtc interrupt mode is alarm */
    RTC_SECOND_INT = 1U,                         /**< rtc interrupt mode is second */
    RTC_OVERFLOW_INT = 2U                        /**< rtc interrupt mode is overflow */
} RTC_IntEventType;

/** @brief Rtc interrupt notification type */
typedef void (*RTC_InterruptCallBackType)(void);

/** @brief Rtc interrupt configuration type */
typedef struct
{
    bool bAlarmIntEn;                               /**< whether enable rtc alarm interrupt */
    RTC_InterruptCallBackType pIsrAlarmNotify;      /**< rtc alarm notification function pointer */
    bool bSecondIntEn;                              /**< whether to use the second interrupt */
    RTC_InterruptCallBackType pIsrSecondNotify;     /**< second interrupt notification function pointer */
    bool bOverflowIntEn ;                           /**< overflow interrupt notification function pointer */
    RTC_InterruptCallBackType pIsrOverflowNotify;   /**< overflow interrupt notification function pointer */
} RTC_InterruptType;

/** @brief Rtc initialization type */
typedef struct
{
    uint32_t u32AlarmValue;                         /**< rtc alarm value */
    RTC_ClkoutSecIntFreqType eSecIntAndClkoutFreq;  /**< Select the RTC Seconds interrupt and the RTC_CLKOUT prescaler output frequency */
    bool bStableClkoutFreq;                         /**< Select the RTC Seconds interrupt and the RTC_CLKOUT prescaler output frequency or RTC_CLKOUT is from the 32.768 kHz clock. */
} RTC_InitType;

/* global functions */
/**
 * @brief Initialize Rtc instance
 * @param pInitStruct Rtc initialization structure
 */
void RTC_Init(const RTC_InitType *const pInitStruct);

/**
 * @brief Rtc set interrupt
 *
 * @param pIntStruct interrupt structure pointer
 * @return Rtc return type
 * @note this function will stop Rtc timer
 */
RTC_StatusType RTC_InitInterrupt(const RTC_InterruptType *const pIntStruct);

/**
 * @brief De-initialize Rtc instance
 *
 */
void RTC_Deinit(void);

/**
 * @brief Rtc enable interrupt
 *
 * @param bAlarmIntEn whether enable alarm interrupt
 * @param bSecondIntEn whether enable second interrupt
 */
void RTC_EnableInterrupt(const bool bAlarmIntEn, const bool bSecondIntEn, const bool bOverflowIntEn);

/**
 * @brief Rtc disable interrupt
 *
 * @param bAlarmIntEn whether disable alarm interrupt
 * @param bSecondIntEn whether disable second interrupt
 */
void RTC_DisableInterrupt(const bool bAlarmIntEn, const bool bSecondIntEn, const bool boverflowIntEn);

/**
 * @brief Rtc start
 *
 */
void RTC_Start(void);

/**
 * @brief Rtc stop
 *
 */
void RTC_Stop(void);

/**
 * @brief Rtc alarm value
 *
 * @param u32AlarmValue Input value
 */
void RTC_UpdateAlarmValue(const uint32_t u32AlarmValue);

/**
 * @brief Get Rtc counter value
 *
 * @return Rtc counter value
 */
uint32_t RTC_GetTime(void);

/**
 * @brief Check RTC overflow flag
 *
 * @return Overflow flag
 */
bool RTC_CheckOverflowFlag(void);


/**
 * @brief Set second counter value
 * @param u32Value the second value.
 * */

void   RTC_SetSecondCounterValue(uint32_t u32Value);


/** @}*/ /* fc7xxx_driver_rtc */
#endif /* DRIVER_INCLUDE_FC7XXX_DRIVER_RTC_H_ */
