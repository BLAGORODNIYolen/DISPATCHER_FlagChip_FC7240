/**
 * @file HwA_pmc.h
 * @author Flagchip0105
 * @brief FC7xxx PMC register API
 * @version 0.1.0
 * @date 2024-01-08
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-08    Flagchip0105   N/A          First version for FC7240
   ******************************************************************************** */
#ifndef HWA_INCLUDE_HWA_PMC_H_
#define HWA_INCLUDE_HWA_PMC_H_
#include "device_header.h"

/**
 * @defgroup HwA_pmc
 * @ingroup fc7xxx_driver_pmc
 * @{
 */

/**
 * @brief get PMC LVCSR register
 *
 * @return uint32_t LVCSR register value
 */
LOCAL_INLINE uint32_t PMC_HWA_GetLVCSRRegister(void)
{
    return (uint32)(PMC->LVSCR);
}

/**
 * @brief set PMC LVCSR register.
 *
 * This function configures the PMC LVCSR registe.
 *
 * @param u32LvcsrValue Set PMC LVCSR register value.
 */
LOCAL_INLINE void PMC_HWA_SetLVCSRRegister(uint32_t u32LvcsrValue)
{
    PMC->LVSCR = u32LvcsrValue;
}

/**
 * @brief get PMC CONFIG register
 *
 * @return uint32_t CONFIG register value
 */
LOCAL_INLINE uint32_t PMC_HWA_GetConfigRegister(void)
{
    return (uint32)(PMC -> CONFIG);
}

/**
 * @brief set PMC CONFIG register.
 *
 * This function configures the PMC CONFIG registe.
 *
 * @param u32LVSCRValue Set PMC CONFIG register value.
 */
LOCAL_INLINE void PMC_HWA_SetConfigRegister(uint32_t u32LVSCRValue)
{
    PMC -> CONFIG = u32LVSCRValue;
}

/**
 * @brief Unlock control for V15_EXT_EN and V15_AUTOSW
 * 
 */
LOCAL_INLINE void PMC_HWA_UnlockConfigRegister(void)
{
    PMC->CONFIG &= ~(uint32_t)PMC_CONFIG_V15_LOCK_MASK;
}

/**
 * @brief lock control for V15_EXT_EN and V15_AUTOSW
 *
 */
LOCAL_INLINE void PMC_HWA_LockConfigRegister(void)
{
    PMC->CONFIG |= (uint32_t)PMC_CONFIG_V15_LOCK_MASK;
}

/** @}*/

#endif /* HWA_INCLUDE_HWA_PMC_H_ */
