/**
 * @file fc7xxx_driver_wku.c
 * @author Flagchip
 * @brief FC7xxx WKU driver type definition and API
 * @version 0.1.0
 * @date 2023-02-13
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
*   0.1.0       2024-01-05    Flagchip055    N/A          FC7240 First version
********************************************************************************/
#include "fc7xxx_driver_wku.h"

/**
 * @brief WKU Enable wakeup source for single input
 *
 * @param u32Input Number of input, WKU_WakeupInputType type is wakeup source definition
 * @return WKU return type
 */
WKU_StatusType WKU_EnableWakeupSource(const uint32_t u32Input)
{
    uint32_t u32TempValue = 0U;
    uint8_t u8Index = 0U;
    WKU_StatusType eRet = WKU_STATUS_SUCCESS;

    DEV_ASSERT(((u32Input & ~(uint32_t)WKU_INPUT_ALL_MASK) == 0U));

    u32TempValue = u32Input;
    while (u32TempValue)
    {
        if (1U == (u32TempValue & ((uint32_t)1)))
        {
            WKU_HWA_EnableWakeupSource((WKU_WakeupInputType)((uint32_t)1 << u8Index));
        }
        u32TempValue >>= 1U;
        u8Index++;
    }

    return eRet;
}

/**
 * @brief WKU Disable wakeup source for single input
 *
 * @param u32Input Number of input, WKU_WakeupInputType type is wakeup source definition
 * @return WKU return type
 */
WKU_StatusType WKU_DisableWakeupSource(const uint32_t u32Input)
{
    uint32_t u32TempValue = 0U;
    uint8_t u8Index = 0U;
    WKU_StatusType eRet = WKU_STATUS_SUCCESS;

    DEV_ASSERT(((u32Input & ~(uint32_t)WKU_INPUT_ALL_MASK) == 0U));

    u32TempValue = u32Input;
    while (u32TempValue)
    {
        if (u32TempValue & ((uint32_t)1 << u8Index))
        {
            WKU_HWA_DisableWakeupSource((WKU_WakeupInputType)((uint32_t)1 << u8Index));
        }
        u32TempValue &= (uint32_t)~((uint32_t)1 << u8Index);
        u8Index++;
    }

    return eRet;
}

/**
 * @brief WKU get wakeup source
 *
 * @return output wakeup source
 */
uint32_t WKU_GetWakeupSources(void)
{
    return WKU_HWA_ReadWakeupSource();
}

/**
 * @brief WKU set wake up delay time
 *
 * @param u8Delaytime The delay time is 2^(u8Delaytime+3) AON_CLK cycles
 */
void WKU_SetWakeupDelay(uint8_t u8Delaytime)
{
    WKU_HWA_DisableDelayCounter();
    WKU_HWA_SetDelayTime(u8Delaytime);
    WKU_HWA_EnableDelayCounter();
}
