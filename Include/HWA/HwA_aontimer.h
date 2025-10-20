/**
 * @file HwA_aontimer.h
 * @author Flagchip
 * @brief FC7xxx aontimer hardware access layer
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
   *   0.1.0       2024-01-10    Flagchip076  N/A          First version for FC7240
   ******************************************************************************** */

#ifndef HWA_INCLUDE_HWA_AONTIMER_H_
#define HWA_INCLUDE_HWA_AONTIMER_H_

#include "device_header.h"

/**
 * @addtogroup HwA_AONTIMER
 * @{
 *
 */

/********* Local typedef ************/
/**
 *  @brief The clock source of the pulse mode
 * 
 */
typedef enum
{

    AONTIMER_CLK0_PIN  = 0,                /*!< select the Aontimer_clk0 pin as pulse sourse*/
    AONTIMER_CLK1_PIN,                     /*!< select the Aontimer_clk1 pin as pulse sourse*/
    AONTIMER_CLK2_PIN,                     /*!< select the Aontimer_clk2 pin as pulse sourse*/
    AONTIMER_TRGSEL_OUTPUT,                /*!< select the tresel as pulse sourse*/

} AONTIMER_PulseClkSrcType;

/** 
 * @brief Aontimer clock source, please refer to Reference Manual chapter8.Aontimer for details. 
 *
 *  */
typedef enum
{
    AONTIMER_SIRC_1MHZ = 0U,  /*!< AONTIMER SIRC 1mhz clock */
    AONTIMER_RTC_CLK = 2U,    /*!< AONTIMER RTC clock  */
    AONTIMER_IRC_CLK = 3U     /*!< AONTIMER internal clock, which comes from PCC */
} AONTIMER_ClkSrcType;

/** 
 * @brief The polarity of pulse mode 
 * 
 * */
typedef enum
{
    AONTIMER_PulsePolarityType_HIGH = 0,        /*!< select the high polarity */
    AONTIMER_PulsePolarityType_LOW              /*!< select the low polarity */
} AONTIMER_PulsePolarityType;

/********* Local inline function ************/
/**
 * @brief Configure AONTIMER module
 *
 * @param u32RegValue CSR register value
 */
LOCAL_INLINE void AONTIMER_HWA_ConfigModule(uint32_t u32RegValue)
{
    AONTIMER->CSR = u32RegValue;
}

/**
 * @brief Configure AONTIMER module prescale
 *
 * @param u32RegValue PSR register value
 */
LOCAL_INLINE void AONTIMER_HWA_ConfigModulePrescale(uint32_t u32RegValue)
{
    AONTIMER->PSR = u32RegValue;
}

/**
 * @brief Set AONTIMER compare value
 *
 * @param u32RegValue CMR register value
 */
LOCAL_INLINE void AONTIMER_HWA_SetModuleCompareValue(uint32_t u32RegValue)
{
    AONTIMER->CMR = u32RegValue;
}

/**
 * @brief Set AONTIMER current counter value
 *
 * @param u32RegValue CNR register value
 */
LOCAL_INLINE void AONTIMER_HWA_SetModuleCounterValue(uint32_t u32RegValue)
{
    AONTIMER->CNR = u32RegValue;
}

/**
 * @brief Set AONTIMER module running on debug mode
 *
 */
LOCAL_INLINE void AONTIMER_HWA_SetModuleRunOnDebug(void)
{
    AONTIMER->CSR |= (uint32_t)AONTIMER_CSR_DBGEN_MASK;
}

/**
 * @brief Enable AONTIMER module interrupt
 *
 */
LOCAL_INLINE void AONTIMER_HWA_EnableModuleInterrupt(void)
{
    AONTIMER->CSR |= (uint32_t)AONTIMER_CSR_TIE_MASK;
}

/**
 * @brief Select AONTIMER module external clock source when timer configured to pulse mode
 *
 * @param eClk Input counter clock source
 */
LOCAL_INLINE void AONTIMER_HWA_SelectClkSrcOnPulseMode(AONTIMER_PulseClkSrcType eClk)
{
    uint32_t u32RegValue = AONTIMER->CSR;
    AONTIMER->CSR |= (u32RegValue & ~(uint32_t)AONTIMER_CSR_TPS_MASK) | AONTIMER_CSR_TPS(eClk);
}

/**
 * @brief Clear AONTIMER interrupt flags
 *
 */
LOCAL_INLINE void AONTIMER_HWA_ClearInterruptFlag(void)
{
    AONTIMER->CSR |= (uint32_t)AONTIMER_CSR_TCF_MASK;
}

/**
 * @brief Set AONTIMER module polarity. Pulse counter input source is active-low, and the CNR increments on falling-edge.
 *
 */
LOCAL_INLINE void AONTIMER_HWA_SetModulePolarity(void)
{
    AONTIMER->CSR |= (uint32_t)AONTIMER_CSR_TPP_MASK;
}

/**
 * @brief Configure AONTIMER module polarity. If ePol is 0:Pulse counter input source is active-high, and the CNR increments on rising-edge.
 *                                            If ePol is 1:Pulse counter input source is active-low, and the CNR increments on falling-edge.
 *
 * @param ePol Polarity enumeration
 */
LOCAL_INLINE void AONTIMER_HWA_ConfigModulePolarity(AONTIMER_PulsePolarityType ePol)
{
    AONTIMER->CSR |= AONTIMER_CSR_TPP(ePol);
}

/**
 * @brief Enable AONTIMER module pulse mode
 *
 */
LOCAL_INLINE void AONTIMER_HWA_EnablePulseMode(void)
{
    AONTIMER->CSR |= (uint32_t)AONTIMER_CSR_TMS_MASK;
}

/**
 * @brief Enable AONTIMER timer
 *
 */
LOCAL_INLINE void AONTIMER_HWA_EnableTimer(void)
{
    AONTIMER->CSR |= (uint32_t)AONTIMER_CSR_TEN_MASK;
}

/**
 * @brief Set AONTIMER prescale
 *
 * @param u8PrescalerValue Prescaler value,the range of the input value is :0~15, and the range of prescaler is :2^1 ~ 2^16.
 */
LOCAL_INLINE void AONTIMER_HWA_SetPrescale(uint8_t u8PrescalerValue)
{
    uint32_t u32RegValue = AONTIMER->PSR;
    AONTIMER->PSR = ((u32RegValue & ~(uint32_t)AONTIMER_PSR_PRESCALE_MASK) | AONTIMER_PSR_PRESCALE(u8PrescalerValue));
}

/**
 * @brief If enable bypass mode, the timer will bypass the prescaler in timer counter mode or glitch filter in pulse mode
 *
 */
LOCAL_INLINE void AONTIMER_HWA_EnableBypassMode(void)
{
    AONTIMER->PSR |= (uint32_t)AONTIMER_PSR_PBYP_MASK;
}

/**
 * @brief Select AONTIMER mdoule clock source
 *
 * @param eClk Aontimer clock source
 */
LOCAL_INLINE void AONTIMER_HWA_SelectModuleClkSrc(AONTIMER_ClkSrcType eClk)
{
    uint32_t u32RegValue = AONTIMER->PSR;
    AONTIMER->PSR = ((u32RegValue & ~(uint32_t)AONTIMER_PSR_PCS_MASK) | AONTIMER_PSR_PCS(eClk));
}

/**
 * @brief Set AONTIMER module stop on debug mode
 *
 */
LOCAL_INLINE void AONTIMER_HWA_SetModuleStopOnDebug(void)
{
    AONTIMER->CSR &= ~(uint32_t)AONTIMER_CSR_DBGEN_MASK;
}


/**
 * @brief Disable AONTIMER module interrupt
 *
 */
LOCAL_INLINE void AONTIMER_HWA_DisableModuleInterrupt(void)
{
    AONTIMER->CSR &= ~(uint32_t)AONTIMER_CSR_TIE_MASK;
}

/**
 * @brief Clear AONTIMER module mode
 *
 */
LOCAL_INLINE void AONTIMER_HWA_ClearModuleMode(void)
{
    AONTIMER->CSR &= ~(uint32_t)AONTIMER_CSR_TPS_MASK;
}

/**
 * @brief Clear AONTIMER module polarity. Pulse counter input source is active-high, and the CNR increments on rising-edge.
 *
 */
LOCAL_INLINE void AONTIMER_HWA_ClearModulePolarity(void)
{
    AONTIMER->CSR &= ~(uint32_t)AONTIMER_CSR_TPP_MASK;
}

/**
 * @brief Disable AONTIEMR module pulse mode
 *
 */
LOCAL_INLINE void AONTIMER_HWA_DisablePulseMode(void)
{
    AONTIMER->CSR &= ~(uint32_t)AONTIMER_CSR_TMS_MASK;
}

/**
 * @brief Disable AONTIMER module timer
 *
 */
LOCAL_INLINE void AONTIMER_HWA_DisableTimer(void)
{
    AONTIMER->CSR &= ~(uint32_t)AONTIMER_CSR_TEN_MASK;
}

/**
 * @brief Clear AONTIMER module prescaler
 *
 */
LOCAL_INLINE void AONTIMER_HWA_ClearPrescale(void)
{
    AONTIMER->PSR &= ~(uint32_t)AONTIMER_PSR_PRESCALE_MASK;
}

/**
 * @brief If disable bypass mode, the timer will enable the prescaler in timer counter mode or glitch filter in pulse mode
 *
 */
LOCAL_INLINE void AONTIMER_HWA_DisableBypassMode(void)
{
    AONTIMER->PSR &= ~(uint32_t)AONTIMER_PSR_PBYP_MASK;
}

/**
 * @brief Clear AONTIMER module clock source
 *
 */
LOCAL_INLINE void AONTIMER_HWA_ClearModuleClkSrc(void)
{
    AONTIMER->PSR &= ~(uint32_t)AONTIMER_PSR_PCS_MASK;
}

/** @}*/ /* HwA_AONTIMER */

#endif /* HWA_INCLUDE_HWA_AONTIMER_H_ */
