/**
 * @file HwA_fpu.h
 * @author Flagchip051
 * @brief  FC4xxx FPU hardware access layer
 * @version 0.1.0
 * @date 2024-01-11
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-11    Flagchip054   N/A          First version for FC7240
   ******************************************************************************** */

#ifndef _HWA_FPU_H_
#define _HWA_FPU_H_

#include "device_header.h"

/* CPACR Bit Fields */
#define FC7240_SCB_CPACR_CP10_MASK                  0x300000u
#define FC7240_SCB_CPACR_CP10_SHIFT                 20u
#define FC7240_SCB_CPACR_CP10_WIDTH                 2u
#define FC7240_SCB_CPACR_CP10(x)                    (((uint32_t)(((uint32_t)(x))<<FC7240_SCB_CPACR_CP10_SHIFT))&FC7240_SCB_CPACR_CP10_MASK)
#define FC7240_SCB_CPACR_CP11_MASK                  0xC00000u
#define FC7240_SCB_CPACR_CP11_SHIFT                 22u
#define FC7240_SCB_CPACR_CP11_WIDTH                 2u
#define FC7240_SCB_CPACR_CP11(x)                    (((uint32_t)(((uint32_t)(x))<<FC7240_SCB_CPACR_CP11_SHIFT))&FC7240_SCB_CPACR_CP11_MASK)
/**
 * @brief enable fpu
 *
 */
LOCAL_INLINE void FPU_HWA_Enable(void)
{
   SCB->CPACR |= (FC7240_SCB_CPACR_CP10(3) | FC7240_SCB_CPACR_CP11(3));  /* set CP10 and CP11 Full Access */
}

/**
 * @brief disable fpu
 *
 */
LOCAL_INLINE void FPU_HWA_Disable(void)
{
   SCB->CPACR &= ~((FC7240_SCB_CPACR_CP10(3) | FC7240_SCB_CPACR_CP11(3)));  /* Access denied. Any attempted access generates a NOCP UsageFault */
}


#endif /* HWA_INCLUDE_HWA_FPU_H_ */
