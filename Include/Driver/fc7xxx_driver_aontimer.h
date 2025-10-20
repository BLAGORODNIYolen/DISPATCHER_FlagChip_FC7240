/**
 * @file fc7xxx_driver_aontimer.h
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


#ifndef DRIVER_INCLUDE_FC7XXX_DRIVER_AONTIMER_H_
#define DRIVER_INCLUDE_FC7XXX_DRIVER_AONTIMER_H_

#include "HwA_aontimer.h"

/**
 * @addtogroup fc7xxx_driver_aontimer
 * @{
 */

/** @brief Aontimer return type. */
typedef enum
{                       
    AONTIMER_STATUS_SUCCESS = 0U,           /**< Aontimer status is success.*/   
    AONTIMER_STATUS_PARAM_INVALID = 1U,     /**< Aontimer failed for param invalid.*/   
    AONTIMER_STATUS_CLOCK_INVALID = 2U      /**< Aontimer failed for colck invalid.*/   
} AONTIMER_StatusType;

/** @brief Aontimer debug mode */
typedef enum
{
    AONTIMER_DBG_COUNTER_STOP = 0x00U,      /**< Aontimer is stop in debug mode.*/ 
    AONTIMER_DBG_COUNTER_RUNNING = 0x01U    /**< Aontimer is running in debug mode.*/ 
} AONTIMER_DebugType;

/** @brief Aontimer mode. */
typedef enum
{
    AONTIMER_COUNTER_MODE = 0,          /**< In this mode ,the clock source is internal.*/
    AONTIMER_PULSE_MODE                 /**< In this mode ,the clock source is external(pin/trgsel).*/
} AONTIMER_ModeType;

/** @brief callback function type */

typedef void (*Aontimer_InterruptCallBackType)(void);

typedef struct
{
    bool bIntEn;                                    /**< whether to use interrupt */
    Aontimer_InterruptCallBackType pIsrNotify;      /**< the notification function of interrupt */
} AONTIMER_IntType;

/** @brief Aontimer Initialization struct type */
typedef struct
{
    AONTIMER_ModeType eMode;                        /**< enumeration of aontier mode */

    AONTIMER_DebugType eDbgMode;                    /**< enumeration of aontier debug mode */

    bool bBypassEn;                                 /**< Whether to use prescaler in counter mode or use glitch filter in pulse mode,
                                                         if set input value is true ,then not use the prescaler or glitch filter.*/
    AONTIMER_PulseClkSrcType ePulseClkSrc;          /**< clock source of pulse mode */
    AONTIMER_PulsePolarityType ePulsePol;           /**< polarity of pulse mode */
    uint8_t u8PulseFilterWidth;                     /**< the width of glitch filter in pulse mode , the range of the input value is :1~15,
                                                         and the range of glitch filter is :2^1 ~ 2^15. */
    uint8_t u8Prescaler;                            /**< the width of prescaler in counter mode, the range of the input value is :0~15,
                                                         and the range of prescaler is :2^1 ~ 2^16. */
    AONTIMER_ClkSrcType eClkSrc;                    /**< clock source of counter mode */
    uint16_t u16StartValue;                         /**< start value of counter mode ,the range is : 0 ~ 65535 */
} AONTIMER_InitType;

/* global function */
/**
 * @brief Initialize aontimer instance
 *
 * @param pInitStruct Aontimer Initialize structure
 */
void AONTIMER_Init(const AONTIMER_InitType *const pInitStruct);

/**
 * @brief De-initialize aontimer instance
 *
 */
void AONTIMER_Deinit(void);

/**
 * @brief Initialize aontimer interrupt functionality
 *
 * @param pIntStruct Aontimer interrupt structure
 * @return Aontimer return type
 * @note this function will disable timer
 */
AONTIMER_StatusType AONTIMER_InitInterrupt(const AONTIMER_IntType *const pIntStruct);

/**
 * @brief Enable AONTIMER interrupt
 * @note this function will enable AONTIEMR timer.
 */
void AONTIMER_EnableInterrupt(void);

/**
 * @brief Disable AONTIMER interrupt
 * @note this function will enable AONTIEMR timer.
 *
 */
void AONTIMER_DisableInterrupt(void);

/**
 * @brief Start Aontimer
 *
 */
void AONTIMER_StartTimer(void);

/**
 * @brief Stop Aontimer
 *
 */
void AONTIMER_StopTimer(void);

/**
 * @brief Update value of aontimer counter
 *
 * @param u16StartValue input value, range : 0~65535
 */
void AONTIMER_UpdateCounterValue(const uint16_t u16StartValue);


/** @}*/ /* fc7xxx_driver_aontimer */

#endif /* DRIVER_INCLUDE_FC7XXX_DRIVER_AONTIMER_H_ */
