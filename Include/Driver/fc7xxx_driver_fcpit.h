/**
 * @file fc7xxx_driver_fcpit.h
 * @author Flagchip
 * @brief FC7xxx FCPIT driver type definition and API
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

#ifndef _DRIVER_FC7XXX_DRIVER_FCPIT_H_
#define _DRIVER_FC7XXX_DRIVER_FCPIT_H_
#include "HwA_fcpit.h"

/**
 * @addtogroup fc7xxx_driver_fcpit
 * @{
 */

/** @brief Fcpit return type. */
typedef enum
{
    FCPIT_STATUS_SUCCESS = 0U,
    FCPIT_STATUS_PARAM_INVALID = 1U,
    FCPIT_STATUS_FUNCTION_ERROR = 2U
} FCPIT_StatusType;

/** @brief Fcpit trigger source */
typedef enum
{
    FCPIT_TRIGGER_INTERNAL_0 = 0,
    FCPIT_TRIGGER_INTERNAL_1,
    FCPIT_TRIGGER_INTERNAL_2,
    FCPIT_TRIGGER_INTERNAL_3,
    FCPIT_TRIGGER_EXTERNAL
} FCPIT_TriggerSelectType;

/** @brief callback function type */
typedef void (*FCPIT_InterruptCallBackType)(void);

typedef struct
{
    FCPIT_ChannelType eFcpitChannel;            /**< Fcpit channel number */
    FCPIT_TriggerSelectType eTriggerSel;        /**< trigger source */
    bool bStartOnTrigger;                       /**< Fcpit timer start when triggered */
    bool bStopOnInterrupt;                      /**< Fcpit timer stop on interrupt */
    bool bReloadOnTrigger;                      /**< Fcpit timer reload when triggered */
} FCPIT_TrggerType;

/** @brief Fcpit interrupt structure */
typedef struct
{
    FCPIT_ChannelType eFcpitChannel;            /**< Fcpit channel number */
    bool bChannelIsrEn;                         /**< whether to use interrupt */
    FCPIT_InterruptCallBackType pIsrNotify;     /**< interrupt notification function */
} FCPIT_IntType;

/** @brief Fcpit initialization type */
typedef struct
{
    FCPIT_ChannelType eFcpitChannel;            /**< Fcpit channel number */
    FCPIT_TimerModeType eMode;                  /**< Fcpit counter mode */
    bool bChainModeEn;                          /**< whether to use chain mode, if use this mode, channel must not be the channel 0 */
    uint32_t u32TimerValue;                     /**< timer compare value, the range of value is related to the counter mode */

    bool bDebugEn;                              /**< whether to use debug mode ,if enable this mode, the counter will stop when debugging. */
    bool bLowPowerModeEn;                       /**< Configure the timer channels to continue running or stop when the device enters the LPM mode */
} FCPIT_InitType;

/** @brief FCPIT instance number */
typedef enum
{
    FCPIT_0 = 0U,
} FCPIT_InstanceType;


/* global functions */
/**
 * @brief Initialize Fcpit instance.
 * @param eFcpit  instance
 * @param pInitStruct Fcpit initialization structure
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_Init(const FCPIT_InstanceType eFcpit, const FCPIT_InitType *const pInitStruct);

/**
 * @brief Initialize Fcpit trigger configuration
 * @param eFcpit  instance
 * @param pTrgStruct Fcpit trigger structure
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_InitTrigger(const FCPIT_InstanceType eFcpit, const FCPIT_TrggerType *const pTrgStruct);

/**
 * @brief De-initialize Fcpit instance.
 * @param eFcpit  instance
 */
FCPIT_StatusType FCPIT_Deinit(const FCPIT_InstanceType eFcpit);

/**
 * @brief Initialize Fcpit interrupt functionality
 * @param  eFcpit  instance
 * @param pTrgStruct Fcpit interrupt structure
 * @return Fcpit return type
 * @note this function will stop timer
 */
FCPIT_StatusType FCPIT_InitInterrupt(const FCPIT_InstanceType eFcpit, const FCPIT_IntType *const pIntStruct);

/**
 * @brief Enable Fcpit interrupt
 * @param eFcpit  instance
 * @param pIntStruct Fcpit interrupt structure
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_EnableInterrupt(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel);

/**
 * @brief Disable Fcpit interrupt
 * @param eFcpit  instance
 * @param eChannel Fcpit channel
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_DisableInterrupt(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel);

/**
 * @brief Fcpit start timer
 * @param eFcpit  instance
 * @param eChannel Fcpit channel
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_Start(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel);

/**
 * @brief Fcpit stop
 * @param eFcpit  instance
 * @param eChannel Fcpit channel
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_Stop(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel);

/**
 * @brief Update Fcpit channel value
 * @param eFcpit  instance
 * @param eChannel Fcpit channel
 * @param u32ChannelValue in/Out value
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_UpdateChannelValue(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel, const uint32_t u32ChannelValue);

/**
 * @brief read Fcpit channel time stamps.
 * @param eFcpit  instance
 * @param eChannel Fcpit channel
 * @param *u32timeStampValue channel  value
 * @return Fcpit return type
 */

FCPIT_StatusType FCPIT_ReadTimstamp(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel,uint32_t *u32timeStampValue);

/**
 * @brief Immediately update Fcpit channel value
 * @param eFcpit  instance
 * @param eChannel Fcpit channel
 * @param u32ChannelValue in/Out value
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_ImmediateUpdateChannelValue(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel, const uint32_t u32ChannelValue);

/** @}*/ /* fc7xxx_driver_fcpit */
#endif
