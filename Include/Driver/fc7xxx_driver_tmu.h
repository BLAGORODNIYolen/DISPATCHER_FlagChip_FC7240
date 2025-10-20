/**
 * @file fc7xxx_driver_tmu.h
 * @author Flagchip
 * @brief FC7xxx TMU driver type definition and API
 * @version 0.1.0
 * @date 2023-12-29
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*   Revision History:
*
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   0.1.0       2023-12-29    qxw074        N/A          First version for FC7240
******************************************************************************** */

#ifndef _DRIVER_FC7XXX_DRIVER_TMU_H_
#define _DRIVER_FC7XXX_DRIVER_TMU_H_
#include "device_header.h"
#include "HwA_tmu.h"

#if defined(__cplusplus)
extern "C" {
#endif
/**
 * @addtogroup fc7xxx_driver_tmu
 * @{
 */

/**
 * @brief The Flag-based temperature sensor over 150 Celsius callback function prototype
 *
 */
typedef void (*TMU_TempOver150InterruptCallbackType)(void);

/**
 * @brief The Flag-based temperature sensor over 125 Celsius callback function prototype
 *
 */
typedef void (*TMU_TempOver125InterruptCallbackType)(void);

/**
 * @brief The Flag-based temperature sensor ready callback function prototype
 *
 */
typedef void (*TMU_TempFlagReadyInterruptCallbackType)(void);

/**
 * @brief The Voltage-based temperature sensor ready callback function prototype
 *
 */
typedef void (*TMU_TempVoltageReadyInterruptCallbackType)(void);

/**
 * @brief TMU operation return values
 *
 */
typedef enum
{
    TMU_STATUS_ERROR   = 0x0U,  /*!< The TMU operation is failed */
    TMU_STATUS_SUCCESS = 0x1U,  /*!< The TMU operation is succeed */
    TMU_STATUS_TIMEOUT = 0x2U   /*!< The TMU operation is failed because of time out */
} TMU_StatusType;

/**
 * @brief Defines the temperature sensor configuration
 *
 * This structure is used to configure for Flag-based temperature sensor ane Voltage-based temperature sensor
 *
 * Implements : TMU_InitType
 */
typedef struct
{
    TMU_LockType eTempRegisterLockCon;          /*!<Temperature Register lock status */

    bool bTemperatureOver150IntEn;              /*!< Enable interrupt when Temperature over 150 Celsius */
    bool bTemperatureOver125IntEn;              /*!< Enable interrupt when Temperature over 125 Celsius */
    bool bFlagTempReadyIntEn;                   /*!< Enable interrupt when Flag-based temperature sensor ready */
    TMU_HysteresisType eFlagTempHysteresisCon;  /*!< Flag-based temperature sensor hysteresis control (on,off) */
    TMU_bypassType eFlagTempFilterBypassCon;    /*!< Flag-based temperature sensor filter bypass control */
    bool bFlagTempEn;                           /*!< Flag-based temperature sensor enable */

    bool bVoltageTempReadyIntEn;                /*!< Enable interrupt when VVoltage-based temperature sensor ready */
    bool bVoltageTempEn;                        /*!< Voltage-based temperature sensor enable */

    bool bSmicsStopAckEn;                       /*!< Controls the stop ack function enable or not to the TMU0 */

    TMU_TempOver150InterruptCallbackType pTemp150Notify;         /*!< Flag-based temperature over 150 Celsius interrupt callback */
    TMU_TempOver125InterruptCallbackType pTemp125Notify;         /*!< Flag-based temperature over 125 Celsius interrupt callback */
    TMU_TempFlagReadyInterruptCallbackType pFlagReadyNotify;     /*!< Flag-based temperature ready interrupt callback */

    TMU_TempVoltageReadyInterruptCallbackType pVoltagReadyNotify;/*!< Voltage-based temperature ready interrupt callback */
}TMU_InitType;

/**
 * @brief Initialize the TMU instance
 *
 * @param pInitCfg the configurations of the TMU instance
 */
void TMU_Init(const TMU_InitType *const pInitCfg);

/**
 * @brief Enable the Flag-based temperature sensor
 *
 * @return TMU_StatusType TMU_STATUS_SUCCESS when enable successfully, others fail
 */
TMU_StatusType TMU_FlagTempEnable(void);

/**
 * @brief Disable the Flag-based temperature sensor
 *
 * @return TMU_StatusType TMU_STATUS_SUCCESS when disable successfully, others fail
 */
TMU_StatusType TMU_FlagTempDisable(void);

/**
 * @brief Enable the Voltage-based temperature sensor
 *
 * @return TMU_StatusType TMU_STATUS_SUCCESS when enable successfully, others fail
 */
TMU_StatusType TMU_VoltageTempEnable(void);

/**
 * @brief Disable the Voltage-based temperature sensor
 *
 * @return TMU_StatusType TMU_STATUS_SUCCESS when disable successfully, others fail
 */
TMU_StatusType TMU_VoltageTempDisable(void);

/**
 * @brief Check if cleaning flag is required
 *
 */
void TMU_TempOverClear(void);

/**
 * @brief Get the temperature code from ADC
 *
 * @return uint32_t the value records the ADC conversion results for voltage-based temperature sensor result in 135 Celsius
 */
uint32_t TMU_GetTcode(void);

/**
 * @brief Get the slope factor
 *
 * @return uint32_t the value records the slope factor for voltage-based temperature sensor
 */
uint32_t TMU_GetTslope(void);

/** @}*/ /* fc7xxx_driver_tmu */
#if defined(__cplusplus)
}
#endif
#endif
