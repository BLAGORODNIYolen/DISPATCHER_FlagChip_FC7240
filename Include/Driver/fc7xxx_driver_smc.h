/**
 * @file fc7xxx_driver_smc.h
 * @author Flagchip
 * @brief FC7xxx SMC driver type definition and API
 * @version 0.1.0
 * @date 2022-11-21
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
#ifndef _DRIVER_FC4XXX_DRIVER_SMC_H_
#define _DRIVER_FC4XXX_DRIVER_SMC_H_
#include "HwA_smc.h"
#include "HwA_pmc.h"
#include "HwA_cm7.h"
/**
 * @addtogroup fc7xxx_driver_smc
 * @{
 */

/** @brief Smc return type. */
typedef enum
{
    SMC_STATUS_SUCCESS = 0U,
    SMC_STATUS_PARAM_INVALID = 1U
} SMC_StatusType;

/** @brief Smc mode */
typedef enum
{
    SMC_MODE_RUN = 0U,         /**< The MCU can run at full speed and the internal supply is fully regulated, that is, in run regulation */
    SMC_MODE_STOP,             /**< Core enters sleep mode and no other clock is gated. Only the core clock is gated. */
    SMC_MODE_WAIT,             /**< Both core and bus clocks are gated off. */
    SMC_MODE_STANBY_0,         /**< All clocks except some low-power clocks can keep on are gated off and the PD1 domain is powered off. please refer to reference manual for detail about standby mode 0. */
    SMC_MODE_STANBY_1,         /**< All clocks except some low-power clocks can keep on are gated off and the PD1 domain is powered off. please refer to reference manual for detail about standby mode 1. */
    SMC_MODE_STANBY_2,         /**< All clocks except some low-power clocks can keep on are gated off and the PD1 domain is powered off. please refer to reference manual for detail about standby mode 2. */
    SMC_MODE_STANBY_3          /**< All clocks except some low-power clocks can keep on are gated off and the PD1 domain is powered off. please refer to reference manual for detail about standby mode 3. */
} SMC_ModeType;

#define SMC_MODE_MAX_ID         6U


/* global functions */
/**
 * @brief Set system mode
 *
 * @param eMode MCU low power mode
 * @return Smc return type
 */
SMC_StatusType SMC_SetSystemMode(const SMC_ModeType eMode);


/** @}*/ /* fc7xxx_driver_smc */
#endif
