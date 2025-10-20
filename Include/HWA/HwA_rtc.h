/**
 * @file HwA_rtc.h
 * @author Flagchip
 * @brief FC7xxx rtc hardware access layer
 * @version 0.1.0
 * @date 2024-01-10
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-10    Flagchip0076  N/A          First version for FC7240
   ******************************************************************************** */

#ifndef HWA_INCLUDE_HWA_RTC_H_
#define HWA_INCLUDE_HWA_RTC_H_


#include "device_header.h"

/**
 * @addtogroup HwA_RTC
 * @{
 *
 */

/********* Local typedef ************/

/**
 *  @brief in the second interrupt mode, this type indicates the interrupt frequency.
 * in the clkout mode , this type indicates the clkout frequency . 
 * 
 * */
typedef enum
{
    RTC_FREQ_1HZ = 0,                       /*!< Set  the RTC Seconds interrupt and the RTC_CLKOUT prescale output frequency to 1Hz */
    RTC_FREQ_2HZ,                           /*!< Set  the RTC Seconds interrupt and the RTC_CLKOUT prescale output frequency to 2Hz */
    RTC_FREQ_4HZ,                           /*!< Set  the RTC Seconds interrupt and the RTC_CLKOUT prescale output frequency to 4Hz */
    RTC_FREQ_8HZ,                           /*!< Set  the RTC Seconds interrupt and the RTC_CLKOUT prescale output frequency to 8Hz */
    RTC_FREQ_16HZ,                          /*!< Set  the RTC Seconds interrupt and the RTC_CLKOUT prescale output frequency to 16Hz */
    RTC_FREQ_32hZ,                          /*!< Set  the RTC Seconds interrupt and the RTC_CLKOUT prescale output frequency to 32Hz */
    RTC_FREQ_64HZ,                          /*!< Set  the RTC Seconds interrupt and the RTC_CLKOUT prescale output frequency to 64Hz */
    RTC_FREQ_128HZ                          /*!< Set  the RTC Seconds interrupt and the RTC_CLKOUT prescale output frequency to 128Hz */
} RTC_ClkoutSecIntFreqType;
/********* Local inline function ************/

/**
 * @brief Read second value
 *
 * @return Second value
 */
LOCAL_INLINE uint32_t RTC_HWA_ReadSecondValue(void)
{
    return (uint32_t)RTC->SR;
}

/**
 * @brief Read RTC SR overflow flag
 *
 * @return true means Overflow flag is 1 ;false means Overflow flag is 0.
 */
LOCAL_INLINE bool RTC_HWA_GetOverflowFlag(void)
{
    return (bool)(((RTC->STR & (uint32_t)RTC_STR_TOF_MASK)!=0u)? true:false);
}

/**
 * @brief Read RTC IER overflow enable bit
 *
 * @return true means enable Overflow Interrupt ;false means disable Overflow Interrupt
 */
LOCAL_INLINE bool RTC_HWA_GetOverflowEnable(void)
{
    return  (bool)(((RTC->IER & (uint32_t)RTC_IER_TOIE_MASK)!=0u) ? true:false);
}

/**
 * @brief Read RTC alarm flag
 *
 * @return true means alarm flag is 1 ;false means alarm flag is 0.
 */
LOCAL_INLINE bool RTC_HWA_GetAlarmFlag(void)
{
    return (bool)(((RTC->STR & (uint32_t)RTC_STR_TAF_MASK)!=0u)?true:false);
}

/**
 * @brief Read RTC alarm Enable
 *
 * @return true means enable alarm Interrupt ;false means disable alarm Interrupt
 */
LOCAL_INLINE bool RTC_HWA_GetAlarmEnable(void)
{
    return (bool)(((RTC->IER & (uint32_t)RTC_IER_TAIE_MASK)!=0u)?true:false);
}

/**
 * @brief Read RTC second  interrupt Enable
 *
 * @return true means enable second Interrupt ;false means disable second Interrupt
 */
LOCAL_INLINE bool RTC_HWA_GetSecondEnable(void)
{
    return (bool)(((RTC->IER & (uint32_t)RTC_IER_TSIE_MASK)!=0u)?true:false);
}

/**
 * @brief Set RTC prescaler register
 *
 * @param u16Value PR register value
 */
LOCAL_INLINE void RTC_HWA_SetPrescalerCounterValue(uint16_t u16Value)
{
    RTC->PR = (uint32_t)u16Value;
}

/**
 * @brief Set RTC seconds register
 *
 * @param u32Value SR register value
 */
LOCAL_INLINE void RTC_HWA_SetSecondCounterValue(uint32_t u32Value)
{
    RTC->SR = u32Value;
}

/**
 * @brief Set RTC alarm value
 *
 * @param u32Value TAR register value
 */
LOCAL_INLINE void RTC_HWA_SetAlarmCounterValue(uint32_t u32Value)
{
    RTC->AR = u32Value;
}

/**
 * @brief Set RTC interrupt value
 *
 * @param u32Value IER register value
 */
LOCAL_INLINE void RTC_HWA_SetInterruptValue(uint32_t u32Value)
{
    RTC->IER = u32Value;
}

/**
 * @brief Configure control register
 *
 * @param u32Value Control value
 */
LOCAL_INLINE void RTC_HWA_ConfigControl(uint32_t u32Value)
{
    RTC->CR = u32Value;
}

/**
 * @brief Enable RTC time counter
 *
 */
LOCAL_INLINE void RTC_HWA_EnableRtcCounter(void)
{
    RTC->STR |= (uint32_t)RTC_STR_TCE_MASK;
}

/**
 * @brief Set RTC_CLKOUT is from the 32.768 khz clock
 *
 */
LOCAL_INLINE void RTC_HWA_SetClkoutFreqStable(void)
{
    RTC->CR |= (uint32_t)RTC_CR_CKPS_MASK;
}

/**
 * @brief Enable alarm interrupt
 *
 */
LOCAL_INLINE void RTC_HWA_EnableAlarmInterrupt(void)
{
    RTC->IER |= (uint32_t)RTC_IER_TAIE_MASK;
}

/**
 * @brief Enable second interrupt
 *
 */
LOCAL_INLINE void RTC_HWA_EnableSecondInterrupt(void)
{
    RTC->IER |= (uint32_t)RTC_IER_TSIE_MASK;
}

/**
 * @brief Enable overflow interrupt
 *
 */
LOCAL_INLINE void RTC_HWA_EnableOverflowInterrupt(void)
{
    RTC->IER |= (uint32_t)RTC_IER_TOIE_MASK;
}

/**
 * @brief Unlock lock/status/control/compensation register
 *
 */
LOCAL_INLINE void RTC_HWA_UnlockStatusControlCompensationReg(void)
{
    RTC->LR |= (uint32_t)(RTC_LR_LRL_MASK | RTC_LR_STRL_MASK | RTC_LR_CRL_MASK | RTC_LR_CPL_MASK);
}

/**
 * @brief Set second interrupt and RTC_CLKOUT frequency
 *
 * @param eFreq Frequency value
 */
LOCAL_INLINE void RTC_HWA_SetSecondAndClkoutFreq(RTC_ClkoutSecIntFreqType eFreq)
{
	uint32_t u32RegValue = RTC->IER;
	RTC->IER &= ~(uint32_t)RTC_IER_TSIE_MASK;
	RTC->IER = (u32RegValue & ~(uint32_t)RTC_IER_TSIC_MASK) | RTC_IER_TSIC(eFreq);
}

/**
 * @brief Disable RTC time counter
 *
 */
LOCAL_INLINE void RTC_HWA_DisableRtcCounter(void)
{
    RTC->STR &= ~(uint32_t)RTC_STR_TCE_MASK;
}

/**
 * @brief Set RTC_CLKOUT is from the prescaler output clock selected by IER[TSIC]
 *
 */
LOCAL_INLINE void RTC_HWA_SetClkoutFromSelectFreq(void)
{
    RTC->CR &= ~(uint32_t)RTC_CR_CKPS_MASK;
}

/**
 * @brief Disable alarm interrupt
 *
 */
LOCAL_INLINE void RTC_HWA_DisableAlarmInterrupt(void)
{
    RTC->IER &= ~(uint32_t)RTC_IER_TAIE_MASK;
}

/**
 * @brief Disable second interrupt
 *
 */
LOCAL_INLINE void RTC_HWA_DisableSecondInterrupt(void)
{
    RTC->IER &= ~(uint32_t)RTC_IER_TSIE_MASK;
}

/**
 * @brief Disable overflow interrupt
 *
 */
LOCAL_INLINE void RTC_HWA_DisableOverflowInterrupt(void)
{
    RTC->IER &= ~(uint32_t)RTC_IER_TOIE_MASK;
}



/** @}*/ /* HwA_RTC */
#endif /* HWA_INCLUDE_HWA_RTC_H_ */
