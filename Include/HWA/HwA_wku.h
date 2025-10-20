/**
 * @file HwA_wku.h
 * @author Flagchip
 * @brief FC7xxx WKU hardware access layer
 * @version 0.1.0
 * @date 2024-01-05
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

#ifndef _HWA_WKU_H_
#define _HWA_WKU_H_

#include "device_header.h"
/********* Local typedef ************/
/** @brief Wku input */
typedef enum
{
    WKU_INPUT_FCSPI0 = 0x000040U,
    WKU_INPUT_FCUART = 0x000080U,
    WKU_INPUT_CMP0 = 0x000400U,
    WKU_INPUT_CMP1 = 0x000800U,
    WKU_INPUT_TSTMP0 = 0x002000U,
    WKU_INPUT_RTC_ALARM = 0x004000U,
    WKU_INPUT_RTC_SECONDS = 0x008000U,
    WKU_INPUT_FCPIT0 = 0x010000U,
    WKU_INPUT_CMU0 = 0x020000U,
    WKU_INPUT_AONTIMER = 0x040000U,
    WKU_INPUT_GPIOA = 0x080000U,
    WKU_INPUT_GPIOC = 0x100000U,
    WKU_INPUT_GPIOE = 0x200000U,
    WKU_INPUT_GPIOF = 0x400000U,
    WKU_INPUT_GPIOG = 0x800000U,
    WKU_INPUT_MAX = 0xFFFFFFU
} WKU_WakeupInputType;


/********* mcaro ************/
#define WKU_INPUT_ALL_MASK (WKU_INPUT_FCSPI0 |\
                            WKU_INPUT_FCUART |\
                            WKU_INPUT_CMP0 |\
                            WKU_INPUT_CMP1 |\
                            WKU_INPUT_TSTMP0 |\
                            WKU_INPUT_RTC_ALARM |\
                            WKU_INPUT_RTC_SECONDS |\
                            WKU_INPUT_FCPIT0 |\
                            WKU_INPUT_CMU0 |\
                            WKU_INPUT_AONTIMER |\
                            WKU_INPUT_GPIOA |\
                            WKU_INPUT_GPIOC |\
                            WKU_INPUT_GPIOE |\
                            WKU_INPUT_GPIOF |\
                            WKU_INPUT_GPIOG |\
                            WKU_INPUT_MAX)

/********* Local inline function ************/
/**
 * @brief Enable wakeup delay counter
 *
 */
LOCAL_INLINE void WKU_HWA_EnableDelayCounter(void)
{
    WKU->MDC |= (uint32_t)WKU_MDC_DLYEN_MASK;
}

/**
 * @brief Disable wakeup delay counter
 *
 */
LOCAL_INLINE void WKU_HWA_DisableDelayCounter(void)
{
    WKU->MDC &= ~((uint32_t)WKU_MDC_DLYEN_MASK);
}

/**
 * @brief Set wakeup delay time
 *
 * @param u8DelayTime delay time
 */
LOCAL_INLINE void WKU_HWA_SetDelayTime(uint8_t u8DelayTime)
{
    uint32_t u32RegVal = WKU->MDC;
    WKU->MDC = ((u32RegVal & (~WKU_MDC_DELAYTIME_MASK)) | WKU_MDC_DELAYTIME(u8DelayTime));
}

/**
 * @brief Enable wakeup source
 *
 * @param eWakeup Wakeup source type
 */
LOCAL_INLINE void WKU_HWA_EnableWakeupSource(const WKU_WakeupInputType eWakeup)
{
    if (eWakeup < WKU_INPUT_CMP0)
    {
        WKU->MWER0 |= (uint32_t)eWakeup;
    }
    else if ((eWakeup < WKU_INPUT_FCPIT0) && (eWakeup > WKU_INPUT_FCUART))
    {
        WKU->MWER1 |= ((uint32_t)eWakeup >> 8U);
    }
    else
    {
        WKU->MWER2 |= ((uint32_t)eWakeup >> 16U);
    }
}

/**
 * @brief Disable wakeup source
 *
 * @param eWakeup Wakeup source type
 */
LOCAL_INLINE void WKU_HWA_DisableWakeupSource(const WKU_WakeupInputType eWakeup)
{
    if (eWakeup < WKU_INPUT_CMP0)
    {
        WKU->MWER0 &= ((~((uint32_t)eWakeup)) & (uint32_t)0xFF);
    }
    else if ((eWakeup < WKU_INPUT_FCPIT0) && (eWakeup > WKU_INPUT_FCUART))
    {
        WKU->MWER1 &= ((~(uint32_t)((uint32_t)eWakeup >> 8U)) & (uint32_t)0xFF);
    }
    else
    {
        WKU->MWER2 &= ((~(uint32_t)((uint32_t)eWakeup >> 16U)) & (uint32_t)0xFF);
    }
}

/**
 * @brief Read WKU wakeup source
 *
 * @return WKU wakeup source value
 */
LOCAL_INLINE uint32_t WKU_HWA_ReadWakeupSource(void)
{
    uint32_t u32WakeupSource = 0U;

    u32WakeupSource = (uint32_t)(WKU->MWER0);
    u32WakeupSource |= (uint32_t)((uint32_t)(WKU->MWER1) << 8U);
    u32WakeupSource |= (uint32_t)((uint32_t)(WKU->MWER2) << 16U);

    return u32WakeupSource;
}


#endif /* #ifndef _HWA_WKU_H_ */
