/**
 * @file HwA_smc.h
 * @author Flagchip
 * @brief FC7xxx SMC hardware access layer
 * @version 0.1.0
 * @date 2022-11-21
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

#ifndef _HWA_SMC_H_
#define _HWA_SMC_H_

#include "device_header.h"
/********* Local typedef ************/
/** @brief SMC stop mode control */
typedef enum
{
    SMC_STOP_MODE = 0U,
    SMC_STANDBY_MODE = 4U
} SMC_LpwModeCtrlType;

/** @brief SMC standby mode */
typedef enum
{
    SMC_CFG_STANDBY_0 = 0U,
    SMC_CFG_STANDBY_1 = 1U,
    SMC_CFG_STANDBY_2 = 2U,
    SMC_CFG_STANDBY_3 = 3U
} SMC_StandbyModeType;

/********* Local inline function ************/
/**
 * @brief Clear stop mode control value
 *
 */
LOCAL_INLINE void SMC_HWA_ClearStopModeCtrl(void)
{
    SMC->PMCTRL &= ~(uint32_t)SMC_PMCTRL_STOP_MODE_MASK;
}

/**
 * @brief Set stop mode control
 *
 * @param eMode Stop mode control type
 */
LOCAL_INLINE void SMC_HWA_SetStopModeCtrl(SMC_LpwModeCtrlType eMode)
{
    SMC->PMCTRL = (uint32_t)eMode;
}

/**
 * @brief Clear standby mode
 *
 */
LOCAL_INLINE void SMC_HWA_ClearStandbyMode(void)
{
    SMC->STANDBY_CFG &= ~(uint32_t)SMC_STANDBY_CFG_OPTION_MASK;
}

/**
 * @brief Set standby mode
 *
 * @param eMode Standby mode type
 */
LOCAL_INLINE void SMC_HWA_SetStandbyMode(SMC_StandbyModeType eMode)
{
    SMC->STANDBY_CFG = (uint32_t)eMode;
}


#endif /* #ifndef _HWA_SMC_H_ */
