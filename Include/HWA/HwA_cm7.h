/**
 * @file HwA_cm7.h
 * @author Flagchip
 * @brief FC7xxx cortex m4 hardware access layer
 * @version 0.1.0
 * @date 2022-11-21
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

#ifndef _HWA_CM7_H_
#define _HWA_CM7_H_

#include "device_header.h"

/**
 * @brief Enable deepsleep mode
 *
 */
LOCAL_INLINE void CM7_HWA_EnableDeepSleep(void)
{
    SCB->SCR |= (uint32_t)SCB_SCR_SLEEPDEEP_Msk;
}

/**
 * @brief Disable deepsleep mode
 *
 */
LOCAL_INLINE void CM7_HWA_DisableDeepSleep(void)
{
    SCB->SCR &= ~(uint32_t)SCB_SCR_SLEEPDEEP_Msk;
}




#endif /* #ifndef _HWA_CM7_H_ */
