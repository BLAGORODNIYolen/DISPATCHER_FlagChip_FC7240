/**
 * @file fc7xxx_driver_wku.h
 * @author Flagchip
 * @brief FC7xxx WKU driver type definition and API
 * @version 0.1.0
 * @date 2024-01-05
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
#ifndef _DRIVER_FC7XXX_DRIVER_WKU_H_
#define _DRIVER_FC7XXX_DRIVER_WKU_H_
#include "HwA_wku.h"
/**
 * @addtogroup fc7xxx_driver_wku
 * @{
 */

/** @brief WKU return type. */
typedef enum
{
    WKU_STATUS_SUCCESS = 0U,
    WKU_STATUS_PARAM_INVALID = 1U
} WKU_StatusType;

/* global apis */
/**
 * @brief WKU Enable wakeup source for single input
 *
 * @param u32Input Number of input, WKU_WakeupInputType type is wakeup source definition
 * @return WKU return type
 */
WKU_StatusType WKU_EnableWakeupSource(const uint32_t u32Input);

/**
 * @brief WKU Disable wakeup source for single input
 *
 * @param u32Input Number of input, WKU_WakeupInputType type is wakeup source definition
 * @return WKU return type
 */
WKU_StatusType WKU_DisableWakeupSource(const uint32_t u32Input);

/**
 * @brief WKU get wakeup source
 *
 * @return output wakeup source
 */
uint32_t WKU_GetWakeupSources(void);

/**
 * @brief WKU Disable wakeup source for single input
 *
 * @param u8Delaytime The delay time is 2^(u8Delaytime+3) AON_CLK cycles
 */
void WKU_SetWakeupDelay(uint8_t u8Delaytime);


/** @}*/ /* fc7xxx_driver_wku */
#endif
