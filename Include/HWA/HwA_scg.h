/**
 * @file HwA_SCG.h
 * @author Flagchip
 * @brief FC7xxx SCG hardware access layer
 * @version 0.1.0
 * @date 2023-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-12    Flagchip085   N/A          First version for FC7240
   ******************************************************************************** */
#ifndef _HWA_SCG_H_
#define _HWA_SCG_H_

#include "device_header.h"

/**
 * @addtogroup HwA_SCG
 * @{
 *
 */
/********* macros ************/
#define UNKNOWN_CLOCK    0xFFFFFFFFU

#define SCG_CORE_CLOCK_SYMBOL CORE
#define SCG_BUS_CLOCK_SYMBOL BUS
#define SCG_SLOW_CLOCK_SYMBOL SLOW
#define SCG_SIRC_CLOCK_SYMBOL SIRC
#define SCG_SIRC32K_CLOCK_SYMBOL SIRC32K
#define SCG_FIRC_CLOCK_SYMBOL FIRC
#define SCG_FOSC_CLOCK_SYMBOL FOSC
#define SCG_SOSC_CLOCK_SYMBOL SOSC
#define SCG_PLL0_CLOCK_SYMBOL PLL0
#define SCG_PLL1_CLOCK_SYMBOL PLL1

/* PLL related */
#define SCG_PLLCSR_LK_MASK 0x800000u
#define SCG_PLLCSR_EN_MASK 0x1u
#define SCG_PLLCSR_CMRE_MASK 0x20000u
#define SCG_PLLCSR_CMRE_SHIFT 17u
#define SCG_PLLCSR_CMRE(x) (((uint32_t)(((uint32_t)(x))<<SCG_PLLCSR_CMRE_SHIFT))&SCG_PLLCSR_CMRE_MASK)
#define SCG_PLLCSR_CM_MASK 0x10000u
#define SCG_PLLCSR_CM_SHIFT 16u
#define SCG_PLLCSR_CM(x) (((uint32_t)(((uint32_t)(x))<<SCG_PLLCSR_CM_SHIFT))&SCG_PLLCSR_CM_MASK)
#define SCG_PLLCSR_STEN_MASK 0x2u
#define SCG_PLLCSR_STEN_SHIFT 1u
#define SCG_PLLCSR_STEN(x) (((uint32_t)(((uint32_t)(x))<<SCG_PLLCSR_STEN_SHIFT))&SCG_PLLCSR_STEN_MASK)
#define SCG_PLLDIV_DIVL_EN_MASK 0x4000000u
#define SCG_PLLDIV_DIVL_MASK 0x70000u
#define SCG_PLLDIV_DIVL_SHIFT 16u
#define SCG_PLLDIV_DIVL(x) (((uint32_t)(((uint32_t)(x))<<SCG_PLLDIV_DIVL_SHIFT))&SCG_PLLDIV_DIVL_MASK)
#define SCG_PLLDIV_DIVM_EN_MASK 0x2000000u
#define SCG_PLLDIV_DIVM_MASK 0x700u
#define SCG_PLLDIV_DIVM_SHIFT 8u
#define SCG_PLLDIV_DIVM(x) (((uint32_t)(((uint32_t)(x))<<SCG_PLLDIV_DIVM_SHIFT))&SCG_PLLDIV_DIVM_MASK)
#define SCG_PLLDIV_DIVH_EN_MASK 0x1000000u
#define SCG_PLLDIV_DIVH_MASK 0x7u
#define SCG_PLLDIV_DIVH_SHIFT 0u
#define SCG_PLLDIV_DIVH(x) (((uint32_t)(((uint32_t)(x))<<SCG_PLLDIV_DIVH_SHIFT))&SCG_PLLDIV_DIVH_MASK)
#define SCG_PLLCFG_MULT_MASK 0x1FF0000u
#define SCG_PLLCFG_MULT_SHIFT 16u
#define SCG_PLLCFG_MULT(x) (((uint32_t)(((uint32_t)(x))<<SCG_PLLCFG_MULT_SHIFT))&SCG_PLLCFG_MULT_MASK)
#define SCG_PLLCFG_PREDIV_MASK 0x1F00u
#define SCG_PLLCFG_PREDIV_SHIFT 8u
#define SCG_PLLCFG_PREDIV(x) (((uint32_t)(((uint32_t)(x))<<SCG_PLLCFG_PREDIV_SHIFT))&SCG_PLLCFG_PREDIV_MASK)
#define SCG_PLLCFG_PSTDIV_MASK 0x30u
#define SCG_PLLCFG_PSTDIV_SHIFT 4u
#define SCG_PLLCFG_PSTDIV(x) (((uint32_t)(((uint32_t)(x))<<SCG_PLLCFG_PSTDIV_SHIFT))&SCG_PLLCFG_PSTDIV_MASK)
#define SCG_PLLCFG_SOURCE_MASK 0x1u
#define SCG_PLLCFG_SOURCE_SHIFT 0u
#define SCG_PLLCFG_SOURCE(x) (((uint32_t)(((uint32_t)(x))<<SCG_PLLCFG_SOURCE_SHIFT))&SCG_PLLCFG_SOURCE_MASK)

#define _SCG_HWA_SetPllCsr(_pll_, val) SCG->_pll_##CSR = val
#define SCG_HWA_SetPllCsr(pll, val) _SCG_HWA_SetPllCsr(pll, val)

#define _SCG_HWA_UnlockPllCsr(_pll_) SCG->_pll_##CSR &= ~(uint32_t)SCG_PLLCSR_LK_MASK
#define SCG_HWA_UnlockPllCsr(pll) _SCG_HWA_UnlockPllCsr(pll)

#define _SCG_HWA_LockPllCsr(_pll_) SCG->_pll_##CSR |= (uint32_t)SCG_PLLCSR_LK_MASK
#define SCG_HWA_LockPllCsr(pll) _SCG_HWA_LockPllCsr(pll)

#define _SCG_HWA_EnablePllClockMonitor(_pll_) SCG->_pll_##CSR |= (uint32_t)SCG_PLLCSR_CM_MASK
#define SCG_HWA_EnablePllClockMonitor(pll) _SCG_HWA_EnablePllClockMonitor(pll)

#define _SCG_HWA_EnablePllClockMonitorReset(_pll_) SCG->_pll_##CSR |= (uint32_t)SCG_PLLCSR_CMRE_MASK
#define SCG_HWA_EnablePllClockMonitorReset(pll) _SCG_HWA_EnablePllClockMonitorReset(pll)

#define _SCG_HWA_SetPllCfg(_pll_, val) SCG->_pll_##CFG = val
#define SCG_HWA_SetPllCfg(pll, val) _SCG_HWA_SetPllCfg(pll, val)

#define _SCG_HWA_SetPllDiv(_pll_, val) SCG->_pll_##DIV = val
#define SCG_HWA_SetPllDiv(pll, val) _SCG_HWA_SetPllDiv(pll, val)

#define _SCG_HWA_EnablePll(_pll_) SCG->_pll_##CSR |= (uint32_t)(SCG_PLLCSR_EN_MASK)
#define SCG_HWA_EnablePll(pll) _SCG_HWA_EnablePll(pll)



#define _SCG_HWA_GetPllMult(_pll_) (uint32_t)(((uint32_t)(SCG->_pll_##CFG) & SCG_PLLCFG_MULT_MASK) >> SCG_PLLCFG_MULT_SHIFT)
#define SCG_HWA_GetPllMult(pll) _SCG_HWA_GetPllMult(pll)

#define _SCG_HWA_GetPllPrediv(_pll_) (uint32_t)(((uint32_t)(SCG->_pll_##CFG) & SCG_PLLCFG_PREDIV_MASK) >> SCG_PLLCFG_PREDIV_SHIFT)
#define SCG_HWA_GetPllPrediv(pll) _SCG_HWA_GetPllPrediv(pll)

#define _SCG_HWA_GetPllPstdiv(_pll_) (uint32_t)(((uint32_t)(SCG->_pll_##CFG) & SCG_PLLCFG_PSTDIV_MASK) >> SCG_PLLCFG_PSTDIV_SHIFT)
#define SCG_HWA_GetPllPstdiv(pll) _SCG_HWA_GetPllPstdiv(pll)

#define _SCG_HWA_GetPllSrc(_pll_) (uint32_t)(((uint32_t)(SCG->_pll_##CFG) & SCG_PLLCFG_SOURCE_MASK) >> SCG_PLLCFG_SOURCE_SHIFT)
#define SCG_HWA_GetPllSrc(pll) _SCG_HWA_GetPllSrc(pll)

/* Clock valid and div related */
#define _SCG_HWA_GetClockVliad(_clock_) (bool)((((uint32_t)SCG->_clock_##CSR & (uint32_t)SCG_##_clock_##CSR_VLD_MASK) != 0U) ? true : false)
#define SCG_HWA_GetClockVliad(_clock_) _SCG_HWA_GetClockVliad(_clock_)

#define _SCG_HWA_GetClockDiv(_clock_) (uint32_t)SCG->_clock_##DIV
#define SCG_HWA_GetClockDiv(_clock_) _SCG_HWA_GetClockDiv(_clock_)

#define SCG_CLOCKDIV_DIVL_ACK_MASK 0x40000000u
#define SCG_CLOCKDIV_DIVM_ACK_MASK 0x20000000u
#define SCG_CLOCKDIV_DIVH_ACK_MASK 0x10000000u
#define SCG_CLOCKDIV_DIVL_ACK_SHIFT 30u
#define SCG_CLOCKDIV_DIVM_ACK_SHIFT 29u
#define SCG_CLOCKDIV_DIVH_ACK_SHIFT 28u

#define SCG_CLOCKDIV_DIVL_EN_MASK 0x4000000u
#define SCG_CLOCKDIV_DIVM_EN_MASK 0x2000000u
#define SCG_CLOCKDIV_DIVH_EN_MASK 0x1000000u
#define SCG_CLOCKDIV_DIVL_EN_SHIFT 26u
#define SCG_CLOCKDIV_DIVM_EN_SHIFT 25u
#define SCG_CLOCKDIV_DIVH_EN_SHIFT 24u

#define SCG_CLOCKDIV_EN2ACK_SHIFT 4u

#define SCG_CLOCKDIV_DIVL_VAL_MASK 0x70000u
#define SCG_CLOCKDIV_DIVM_VAL_MASK 0x700u
#define SCG_CLOCKDIV_DIVH_VAL_MASK 0x7u
#define SCG_CLOCKDIV_DIVL_VAL_SHIFT 16u
#define SCG_CLOCKDIV_DIVM_VAL_SHIFT 8u
#define SCG_CLOCKDIV_DIVH_VAL_SHIFT 0u

#define SCG_CHECK_DIVL_ACK(reg_val)                   ((reg_val & SCG_CLOCKDIV_DIVL_ACK_MASK) >> SCG_CLOCKDIV_DIVL_ACK_SHIFT)
#define SCG_CHECK_DIVM_ACK(reg_val)                   ((reg_val & SCG_CLOCKDIV_DIVM_ACK_MASK) >> SCG_CLOCKDIV_DIVM_ACK_SHIFT)
#define SCG_CHECK_DIVH_ACK(reg_val)                   ((reg_val & SCG_CLOCKDIV_DIVH_ACK_MASK) >> SCG_CLOCKDIV_DIVH_ACK_SHIFT)
#define SCG_CHECK_DIVL_EN(reg_val)                    ((reg_val & SCG_CLOCKDIV_DIVL_EN_MASK) >> SCG_CLOCKDIV_DIVL_EN_SHIFT)
#define SCG_CHECK_DIVM_EN(reg_val)                    ((reg_val & SCG_CLOCKDIV_DIVM_EN_MASK) >> SCG_CLOCKDIV_DIVM_EN_SHIFT)
#define SCG_CHECK_DIVH_EN(reg_val)                    ((reg_val & SCG_CLOCKDIV_DIVH_EN_MASK) >> SCG_CLOCKDIV_DIVH_EN_SHIFT)
#define SCG_GET_DIVL_VAL(reg_val)                     ((0U == ((reg_val & SCG_CLOCKDIV_DIVL_VAL_MASK) >> SCG_CLOCKDIV_DIVL_VAL_SHIFT)) ? 1U : ((reg_val & SCG_CLOCKDIV_DIVL_VAL_MASK) >> SCG_CLOCKDIV_DIVL_VAL_SHIFT))
#define SCG_GET_DIVM_VAL(reg_val)                     ((0U == ((reg_val & SCG_CLOCKDIV_DIVM_VAL_MASK) >> SCG_CLOCKDIV_DIVM_VAL_SHIFT)) ? 1U : ((reg_val & SCG_CLOCKDIV_DIVM_VAL_MASK) >> SCG_CLOCKDIV_DIVM_VAL_SHIFT))
#define SCG_GET_DIVH_VAL(reg_val)                     ((0U == ((reg_val & SCG_CLOCKDIV_DIVH_VAL_MASK) >> SCG_CLOCKDIV_DIVH_VAL_SHIFT)) ? 1U : ((reg_val & SCG_CLOCKDIV_DIVH_VAL_MASK) >> SCG_CLOCKDIV_DIVH_VAL_SHIFT))
#define SCG_CALCULATE_DIVL_FREQ(clk_freq, reg_val)    (((1U == SCG_CHECK_DIVL_EN(reg_val)) && (clk_freq != UNKNOWN_CLOCK)) ? (uint32_t)clk_freq >> (uint8_t)(SCG_GET_DIVL_VAL(reg_val) - 1U) : (uint32_t)UNKNOWN_CLOCK)
#define SCG_CALCULATE_DIVM_FREQ(clk_freq, reg_val)    (((1U == SCG_CHECK_DIVM_EN(reg_val)) && (clk_freq != UNKNOWN_CLOCK)) ? (uint32_t)clk_freq >> (uint8_t)(SCG_GET_DIVM_VAL(reg_val) - 1U) : (uint32_t)UNKNOWN_CLOCK)
#define SCG_CALCULATE_DIVH_FREQ(clk_freq, reg_val)    (((1U == SCG_CHECK_DIVH_EN(reg_val)) && (clk_freq != UNKNOWN_CLOCK)) ? (uint32_t)clk_freq >> (uint8_t)(SCG_GET_DIVH_VAL(reg_val) - 1U) : (uint32_t)UNKNOWN_CLOCK)


typedef enum
{
	SCG_CLOCK_DIV_H   = 0x01000000U, /* DIVH clock enable bit [24] */
	SCG_CLOCK_DIV_M   = 0x02000000U, /* DIVM clock enable bit [25] */
	SCG_CLOCK_DIV_L   = 0x04000000U, /* DIVL clock enable bit [26] */
	SCG_CLOCK_DIV_ALL = 0x07000000U, /* DIVH DIVM DIVL clock enable bit [26:24] */
}SCG_DivEnableType;

/********* Local inline function   ************/

/**
 * @brief Get clock out configure register CLKOUTSEL value
 */
LOCAL_INLINE uint8_t SCG_HWA_GetClkOutSel(void)
{
    return (uint8_t)(((uint32_t)SCG->CLKOUTCFG & SCG_CLKOUTCFG_CLKOUTSEL_MASK) >> SCG_CLKOUTCFG_CLKOUTSEL_SHIFT);
}

/**
 * @brief Get clock out configure register value
 */
LOCAL_INLINE uint32_t SCG_HWA_GetClkOutCfg(void)
{
    return SCG->CLKOUTCFG;
}

/**
 * @brief Unlock SOSC CSR register
 *
 */
LOCAL_INLINE void SCG_HWA_UnlockSoscCsrReg(void)
{
    SCG->SOSCCSR &= ~(uint32_t)(SCG_SOSCCSR_LK_MASK);
}

/**
 * @brief Lock SOSC CSR register
 *
 */
LOCAL_INLINE void SCG_HWA_LockSoscCsrReg(void)
{
    SCG->SOSCCSR |= (uint32_t)(SCG_SOSCCSR_LK_MASK);
}

/**
 * @brief Enable SOSC clock monitor
 *
 */
LOCAL_INLINE void SCG_HWA_EnableSoscClockMonitor(void)
{
    SCG->SOSCCSR |= (uint32_t)(SCG_SOSCCSR_CM_MASK);
}

/**
 * @brief Enable SOSC clock monitor Reset
 *
 */
LOCAL_INLINE void SCG_HWA_EnableSoscClockMonitorReset(void)
{
    SCG->SOSCCSR |= (uint32_t)(SCG_SOSCCSR_CMRE_MASK);
}

/**
 * @brief Set SOSC enable
 */
LOCAL_INLINE void SCG_HWA_EnableSosc(void)
{
    SCG->SOSCCSR |= (uint32_t)SCG_SOSCCSR_EN_MASK;
}

/**
 * @brief Diable SOSC
 */
LOCAL_INLINE void SCG_HWA_DisableSosc(void)
{
    SCG->SOSCCSR &= ~(uint32_t)SCG_SOSCCSR_EN_MASK;
}

/**
 * @brief Set recommend value to SOSCCFG register
 *
 */
LOCAL_INLINE void SCG_HWA_SetSoscRecommendCfg(void)
{
    SCG->SOSCCFG = (uint32_t)(SCG_SOSCCFG_EOCV(64U) | SCG_SOSCCFG_GM_SEL(3U) | SCG_SOSCCFG_CURPRG_SF(3U) | SCG_SOSCCFG_CURPRG_COMP(3U));
}

/**
 * @brief Set SOSC CSR register value
 *
 * @param u32CsrValue configured register value
 */
LOCAL_INLINE void SCG_HWA_SetSoscCsr(uint32_t u32CsrValue)
{
    SCG->SOSCCSR = u32CsrValue;
}

/**
 * @brief Get SOSC CSR register value
 *
 */
LOCAL_INLINE uint32_t SCG_HWA_GetSoscCsr(void)
{
    return (uint32_t)SCG->SOSCCSR;
}

/********* Fosc Register interface ************/
/**
 * @brief Enable FOSC
 */
LOCAL_INLINE void SCG_HWA_EnableFosc(void)
{
    SCG->FOSCCSR |= (uint32_t)SCG_FOSCCSR_EN_MASK;
}

/**
 * @brief Disable FOSC
 */
LOCAL_INLINE void SCG_HWA_DisableFosc(void)
{
    SCG->FOSCCSR &= ~SCG_FOSCCSR_EN_MASK;
}

/**
 * @brief Set FOSCCFG register value
 *
 * @param u32CfgValue configured register value
 */
LOCAL_INLINE void SCG_HWA_SetFoscCfg(uint32_t u32CfgValue)
{
    SCG->FOSCCFG = u32CfgValue;
}

/**
 * @brief Set FOSCCSR register value
 *
 * @param u32CsrValue configured register value
 */
LOCAL_INLINE void SCG_HWA_SetFoscCsr(uint32_t u32CsrValue)
{
    SCG->FOSCCSR = u32CsrValue;
}

/**
 * @brief Get FOSCCSR register value
 *
 */
LOCAL_INLINE uint32_t SCG_HWA_GetFoscCsr(void)
{
    return (uint32_t)SCG->FOSCCSR;
}

/**
 * @brief Unlock FOSC CSR register
 *
 */
LOCAL_INLINE void SCG_HWA_UnlockFoscCsrReg(void)
{
    SCG->FOSCCSR &= ~(uint32_t)(SCG_FOSCCSR_LK_MASK);
}

/**
 * @brief lock FOSC CSR register
 *
 */
LOCAL_INLINE void SCG_HWA_LockFoscCsrReg(void)
{
    SCG->FOSCCSR |= (uint32_t)(SCG_FOSCCSR_LK_MASK);
}

/**
 * @brief Enable FOSC clock monitor
 *
 */
LOCAL_INLINE void SCG_HWA_EnableFoscClockMonitor(void)
{
    SCG->FOSCCSR |= (uint32_t)(SCG_FOSCCSR_CM_MASK);
}

/**
 * @brief Enable FOSC clock monitor Reset
 *
 */
LOCAL_INLINE void SCG_HWA_EnableFoscClockMonitorReset(void)
{
    SCG->FOSCCSR |= (uint32_t)(SCG_FOSCCSR_CMRE_MASK);
}

/**
 * @brief enable FOSCDIV as user manual request sequence
 * @param DivEn the or value of SCG_DivEnableType
 */
LOCAL_INLINE void SCG_HWA_EnableFoscDiv(SCG_DivEnableType DivEn)
{
    SCG->FOSCDIV |= (uint32_t)DivEn;
}

/**
 * @brief Disable FOSCDIV as user manual request sequence
 * @param DivEn the or value of SCG_DivEnableType
 */
LOCAL_INLINE void SCG_HWA_DiableFoscDiv(SCG_DivEnableType DivEn)
{
    SCG->FOSCDIV &= ~(uint32_t)DivEn;
}

/**
 * @brief Get the acknowledgment of DIV clocks enabled by SCG_HWA_EnableFoscDiv
 * @param DivEn the or value of SCG_DivEnableType
 * @return bool true : The enabled DIV clocks are acknowledged
 * 			    false : The enabled DIV clocks are not acknowledged
 */
LOCAL_INLINE bool SCG_HWA_GetFoscDivAck(SCG_DivEnableType DivEn)
{
    return (bool)((SCG->FOSCDIV & (DivEn << SCG_CLOCKDIV_EN2ACK_SHIFT)) == (DivEn << SCG_CLOCKDIV_EN2ACK_SHIFT));
}

/**
 * @brief Set FOSCDIV register value
 *
 * @param u32DivValue configured register value
 */
LOCAL_INLINE void SCG_HWA_SetFoscDiv(uint32_t u32DivValue)
{
    SCG->FOSCDIV = u32DivValue;
}

/**
 * @brief Set Low Power Wakeup WDOG Register
 *
 * @param u8MSBVal Most Significant value, if OSC is 40M
 *                 and FOSC not valid after 1.8ms wakeup,
 *                 the chip will reset and RGM register will
 *                 report clock error reset reason.
 */
LOCAL_INLINE void SCG_HWA_SetWKPWDG(uint8_t u8MSBVal)
{
    SCG->WKPWDG = SCG_WKPWDG_MSB(u8MSBVal) | SCG_WKPWDG_EN_MASK;
}



/*********  Sirc Register interface  ************/
/**
 * @brief Set SIRCCSR register value
 *
 * @param u32CsrValue configured register value
 */
LOCAL_INLINE void SCG_HWA_SetSircCsr(uint32_t u32CsrValue)
{
    SCG->SIRCCSR = u32CsrValue;
}

/**
 * @brief Get SIRCCSR register value
 *
 */
LOCAL_INLINE uint32_t SCG_HWA_GetSircCsr(void)
{
    return (uint32_t)SCG->SIRCCSR;
}

/**
 * @brief Unlock SIRC CSR register
 *
 */
LOCAL_INLINE void SCG_HWA_UnlockSircCsrReg(void)
{
    SCG->SIRCCSR &= ~(uint32_t)SCG_SIRCCSR_LK_MASK;
}

/**
 * @brief Lock SIRC CSR register
 *
 */
LOCAL_INLINE void SCG_HWA_LockSircCsrReg(void)
{
    SCG->SIRCCSR |= (uint32_t)SCG_SIRCCSR_LK_MASK;
}

/**
 * @brief Enable SIRC clock monitor
 *
 */
LOCAL_INLINE void SCG_HWA_EnableSircClockMonitor(void)
{
    SCG->SIRCCSR |= (uint32_t)(SCG_SIRCCSR_CM_MASK);
}

/**
 * @brief Set SIRCDIV register value
 *
 * @param u32DivValue configured register value
 */
LOCAL_INLINE void SCG_HWA_SetSircDiv(uint32_t u32DivValue)
{
    SCG->SIRCDIV = u32DivValue;
}

/**
 * @brief enable SIRCDIV as user manual request sequence
 * @param DivEn the or value of SCG_DivEnableType
 */
LOCAL_INLINE void SCG_HWA_EnableSircDiv(SCG_DivEnableType DivEn)
{
    SCG->SIRCDIV |= (uint32_t)DivEn;
}

/**
 * @brief Disable SIRCDIV as user manual request sequence
 * @param DivEn the or value of SCG_DivEnableType
 */
LOCAL_INLINE void SCG_HWA_DiableSircDiv(SCG_DivEnableType DivEn)
{
    SCG->SIRCDIV &= ~(uint32_t)DivEn;
}

/**
 * @brief Get the acknowledgment of DIV clocks enabled by SCG_HWA_EnableSircDiv
 * @param DivEn the or value of SCG_DivEnableType
 * @return bool true : The enabled DIV clocks are acknowledged
 * 			    false : The enabled DIV clocks are not acknowledged
 */
LOCAL_INLINE bool SCG_HWA_GetSircDivAck(SCG_DivEnableType DivEn)
{
    return (bool)((SCG->SIRCDIV & (DivEn << SCG_CLOCKDIV_EN2ACK_SHIFT)) == (DivEn << SCG_CLOCKDIV_EN2ACK_SHIFT));
}

/**
 * @brief Set SIRCTCFG register value for SIRC Trim configure.
 *
 * @param u32TcfgValue configured register value
 */
LOCAL_INLINE void SCG_HWA_SetSircTcfg(uint32_t u32TcfgValue)
{
    SCG->SIRCTCFG = u32TcfgValue;
}

/*********  Sirc32k Register interface  ************/
/**
 * @brief Enable SIRC32KCSR register
 *
 */
LOCAL_INLINE void SCG_HWA_EnableSirc32kCsr(void)
{
    SCG->SIRC32KCSR |= (uint32_t)SCG_SIRC32KCSR_EN_MASK;
}

/**
 * @brief Disable SIRC32KCSR register
 *
 */
LOCAL_INLINE void SCG_HWA_DisableSirc32kCsr(void)
{
    SCG->SIRC32KCSR &= ~(uint32_t)SCG_SIRC32KCSR_EN_MASK;
}

/**
 * @brief Unlock SIRC32K CSR register
 */
LOCAL_INLINE void SCG_HWA_UnlockSirc32kCsrReg(void)
{
    SCG->SIRC32KCSR &= ~(uint32_t)(SCG_SIRC32KCSR_LK_MASK);
}

/**
 * @brief Lock SIRC32K CSR register
 */
LOCAL_INLINE void SCG_HWA_LockSirc32kCsrReg(void)
{
    SCG->SIRC32KCSR |= (uint32_t)(SCG_SIRC32KCSR_LK_MASK);
}

/********* Firc Register interface ************/
/**
 * @brief Get FIRC CSR register value.
 */
LOCAL_INLINE uint32_t SCG_HWA_GetFircCsr(void)
{
    return (uint32_t)SCG->FIRCCSR;
}

/**
 * @brief Enable FIRC.
 */
LOCAL_INLINE void SCG_HWA_EnableFirc(void)
{
    SCG->FIRCCSR |= (uint32_t)SCG_FIRCCSR_EN_MASK;
}

/**
 * @brief Unlock FIRC CSR register
 */
LOCAL_INLINE void SCG_HWA_UnlockFircCsrReg(void)
{
    SCG->FIRCCSR &= ~(uint32_t)(SCG_FIRCCSR_LK_MASK);
}

/**
 * @brief Lock FIRC CSR register
 */
LOCAL_INLINE void SCG_HWA_LockFircCsrReg(void)
{
    SCG->FIRCCSR |= (uint32_t)(SCG_FIRCCSR_LK_MASK);
}

/**
 * @brief Enable FIRC clock monitor
 *
 */
LOCAL_INLINE void SCG_HWA_EnableFircClockMonitor(void)
{
    SCG->FIRCCSR |= (uint32_t)(SCG_FIRCCSR_CM_MASK);
}

/**
 * @brief Disable FIRC.
 */
LOCAL_INLINE void SCG_HWA_DisableFirc(void)
{
    SCG->FIRCCSR &= ~(uint32_t)SCG_FIRCCSR_EN_MASK;
}

/**
 * @brief Set FIRCCSR register value
 *
 * @param u32CsrValue configured register value
 */
LOCAL_INLINE void SCG_HWA_SetFircCsr(uint32_t u32CsrValue)
{
    SCG->FIRCCSR = u32CsrValue;
}

/**
 * @brief Set FIRCCFG register value
 *
 * @param u32CfgValue configured register value
 */
LOCAL_INLINE void SCG_HWA_SetFircCfg(uint32_t u32CfgValue)
{
    SCG->FIRCCFG = u32CfgValue;
}

/**
 * @brief Set FOSCDIV register value
 *
 * @param u32DivValue configured register value
 */
LOCAL_INLINE void SCG_HWA_SetFircDiv(uint32_t u32DivValue)
{
    SCG->FIRCDIV = u32DivValue;
}

/**
 * @brief enable FIRCDIV as user manual request sequence
 * @param DivEn the or value of SCG_DivEnableType
 */
LOCAL_INLINE void SCG_HWA_EnableFircDiv(SCG_DivEnableType DivEn)
{
    SCG->FIRCDIV |= (uint32_t)DivEn;
}

/**
 * @brief Disable FIRCDIV as user manual request sequence
 * @param DivEn the or value of SCG_DivEnableType
 */
LOCAL_INLINE void SCG_HWA_DiableFircDiv(SCG_DivEnableType DivEn)
{
    SCG->FIRCDIV &= ~(uint32_t)DivEn;
}

/**
 * @brief Get the acknowledgment of DIV clocks enabled by SCG_HWA_EnableFircDiv
 * @param DivEn the or value of SCG_DivEnableType
 * @return bool true : The enabled DIV clocks are acknowledged
 * 			    false : The enabled DIV clocks are not acknowledged
 */
LOCAL_INLINE bool SCG_HWA_GetFircDivAck(SCG_DivEnableType DivEn)
{
    return (bool)((SCG->FIRCDIV & (DivEn << SCG_CLOCKDIV_EN2ACK_SHIFT)) == (DivEn << SCG_CLOCKDIV_EN2ACK_SHIFT));
}

/**
 * @brief Set FIRCTCFG register value for FIRC clock trim configure.
 *
 * @param u32TcfgValue configured register value.
 */
LOCAL_INLINE void SCG_HWA_SetFircTcfg(uint32_t u32TcfgValue)
{
    SCG->FIRCTCFG = u32TcfgValue;
}


/********* PLL0 clock Register interface ************/
/**
 * @brief enable PLL0DIV as user manual request sequence
 * @param DivEn the or value of SCG_DivEnableType
 */
LOCAL_INLINE void SCG_HWA_EnablePll0Div(SCG_DivEnableType DivEn)
{
    SCG->PLL0DIV |= (uint32_t)DivEn;
}

/**
 * @brief Disable FOSCDIV as user manual request sequence
 * @param DivEn the or value of SCG_DivEnableType
 */
LOCAL_INLINE void SCG_HWA_DiablePll0Div(SCG_DivEnableType DivEn)
{
    SCG->PLL0DIV &= ~(uint32_t)DivEn;
}

/**
 * @brief Get the acknowledgment of DIV clocks enabled by SCG_HWA_EnablePll0Div
 * @param DivEn the or value of SCG_DivEnableType
 * @return bool true : The enabled DIV clocks are acknowledged
 * 			    false : The enabled DIV clocks are not acknowledged
 */
LOCAL_INLINE bool SCG_HWA_GetPll0DivAck(SCG_DivEnableType DivEn)
{
    return (bool)((SCG->PLL0DIV & (DivEn << SCG_CLOCKDIV_EN2ACK_SHIFT)) == (DivEn << SCG_CLOCKDIV_EN2ACK_SHIFT));
}


/********* PLL1 clock Register interface ************/
/**
 * @brief enable PLL0DIV as user manual request sequence
 * @param DivEn the or value of SCG_DivEnableType
 */
LOCAL_INLINE void SCG_HWA_EnablePll1Div(SCG_DivEnableType DivEn)
{
    SCG->PLL1DIV |= (uint32_t)DivEn;
}

/**
 * @brief Disable FOSCDIV as user manual request sequence
 * @param DivEn the or value of SCG_DivEnableType
 */
LOCAL_INLINE void SCG_HWA_DiablePll1Div(SCG_DivEnableType DivEn)
{
    SCG->PLL1DIV &= ~(uint32_t)DivEn;
}

/**
 * @brief Get the acknowledgment of DIV clocks enabled by SCG_HWA_EnablePll1Div
 * @param DivEn the or value of SCG_DivEnableType
 * @return bool true : The enabled DIV clocks are acknowledged
 * 			    false : The enabled DIV clocks are not acknowledged
 */
LOCAL_INLINE bool SCG_HWA_GetPll1DivAck(SCG_DivEnableType DivEn)
{
    return (bool)((SCG->PLL1DIV & (DivEn << SCG_CLOCKDIV_EN2ACK_SHIFT)) == (DivEn << SCG_CLOCKDIV_EN2ACK_SHIFT));
}

/********* System clock Register interface ************/
/**
 * @brief Get system clock CCR register value
 *
 * @return system clock CCR register value
 */
LOCAL_INLINE uint32_t SCG_HWA_GetCCR(void)
{
    return SCG->CCR;
}

/**
 * @brief Set system clock CCR register value
 *
 * @param u32CcrValue configured register value
 */
LOCAL_INLINE void SCG_HWA_SetCCR(uint32_t u32CcrValue)
{
    SCG->CCR = u32CcrValue;
}

/**
 * @brief Set system clock
 *
 * @param u8SystemCLock System clock value
 */
LOCAL_INLINE void SCG_HWA_SetSystemClock(uint8_t u8SystemCLock)
{
    SCG->CCR = ((SCG->CCR & ~(uint32_t)SCG_CCR_SCS_MASK) | SCG_CCR_SCS(u8SystemCLock));
}

/**
 * @brief Get system clock source. used to calculate system clock frequency at startup.
 *        used to check if the target clock soure successfully switched.
 * @return uint8_t. system clock source.
 */
LOCAL_INLINE uint8_t SCG_HWA_GetSysClkSrc(void)
{
    return (uint8_t)(((uint32_t)(SCG->CSR) & (uint32_t)SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT);
}

/**
 * @brief Get system clock valid status, use this status to check system clock update finished or not.
 * @return bool. true as updated; false as not updated.
 */
LOCAL_INLINE bool SCG_HWA_GetSysClkUPRD(void)
{
    return (bool)((((uint32_t)SCG->CSR & (uint32_t)SCG_CSR_CCR_UPRD_MASK) != 0U) ? true : false);
}

/**
 * @brief Get system clock Divcore. used to calculate core clock frequency at startup.
 * @return uint8_t. system clock Divcore.
 */
LOCAL_INLINE uint8_t SCG_HWA_GetSysClkDivCore(void)
{
    return (uint8_t)(((uint32_t)(SCG->CSR) & SCG_CSR_DIVCORE_MASK) >> SCG_CSR_DIVCORE_SHIFT);
}

/**
 * @brief Get system clock Divbus. used to calculate bus clock frequency at startup.
 * @return uint8_t. system clock Divbus.
 */
LOCAL_INLINE uint8_t SCG_HWA_GetSysClkDivBus(void)
{
    return (uint8_t)(((uint32_t)(SCG->CSR) & SCG_CSR_DIVBUS_MASK) >> SCG_CSR_DIVBUS_SHIFT);
}

/**
 * @brief Get system clock Divslow. used to calculate slow clock frequency at startup.
 * @return uint8_t. system clock Divslow.
 */
LOCAL_INLINE uint8_t SCG_HWA_GetSysClkDivSlow(void)
{
    return (uint8_t)(((uint32_t)(SCG->CSR) & SCG_CSR_DIVSLOW_MASK) >> SCG_CSR_DIVSLOW_SHIFT);
}

/*********  Clkout Register interface ************/
/**
 * @brief Select clock out source
 *
 * @param u8ClkOutSel Clock out select
 */
LOCAL_INLINE void SCG_HWA_SetClkOutSel(uint8_t u8ClkOutSel)
{
    SCG->CLKOUTCFG = ((SCG->CLKOUTCFG & ~(uint32_t)SCG_CLKOUTCFG_CLKOUTSEL_MASK) | SCG_CLKOUTCFG_CLKOUTSEL(u8ClkOutSel));
}

/**
 * @brief Set Nvm clock source
 *
 * @param u32NvmClkMask Nvm clock source mask
 */
LOCAL_INLINE void SCG_HWA_SetNvmClk(uint32_t u32NvmClkMask)
{
    SCG->CLKOUTCFG &= ~(uint32_t)(SCG_CLKOUTCFG_NVMCLK_FIRC_MASK | SCG_CLKOUTCFG_NVMCLK_SIRC_MASK);
    SCG->CLKOUTCFG |= u32NvmClkMask;
}

/**
 * @brief Set CMU4 clock source
 *
 * @param u32Cmu4ClkMask CMU4 clock source mask
 */
LOCAL_INLINE void SCG_HWA_SetCmu4Clk(uint32_t u32Cmu4ClkMask)
{
    SCG->CLKOUTCFG &= ~(uint32_t)(SCG_CLKOUTCFG_CMU4CLK_FOSC_MASK | SCG_CLKOUTCFG_CMU4CLK_SIRC_MASK);
    SCG->CLKOUTCFG |= u32Cmu4ClkMask;
}

/*********  CRC Register interface ************/
/**
 * @brief Generate SCG register CRC value
 */
LOCAL_INLINE void SCG_HWA_GenCrcVal(void)
{
    SCG->CRCCSR |= (uint32_t)SCG_CRCCSR_GEN_MASK;
}

/**
 * @brief Enable SCG register CRC check
 */
LOCAL_INLINE void SCG_HWA_EnableCrcCheck(void)
{
    SCG->CRCCSR |= (uint32_t)SCG_CRCCSR_CHKEN_MASK;
}

/**
 * @brief Disable SCG register CRC check
 */
LOCAL_INLINE void SCG_HWA_DisableCrcCheck(void)
{
    SCG->CRCCSR &= ~(uint32_t)SCG_CRCCSR_CHKEN_MASK;
}

/**
 * @brief Enable SCG register CRC error output
 */
LOCAL_INLINE void SCG_HWA_EnableCrcErrorOutput(void)
{
    SCG->CRCCSR |= (uint32_t)SCG_CRCCSR_EOEN_MASK;
}

/**
 * @brief Disable SCG register CRC error output
 */
LOCAL_INLINE void SCG_HWA_DisableCrcErrorOutput(void)
{
    SCG->CRCCSR &= ~(uint32_t)SCG_CRCCSR_EOEN_MASK;
}

/**
 * @brief Get CRC busy status
 */
LOCAL_INLINE bool SCG_HWA_GetCrcBusyStatus(void)
{
    return (0U != (SCG->CRCCSR & (uint32_t)SCG_CRCCSR_BUSY_MASK));
}

/**
 * @brief Get CRC error status
 */
LOCAL_INLINE bool SCG_HWA_GetCrcErrorStatus(void)
{
    return (0U != (SCG->CRCCSR & (uint32_t)SCG_CRCCSR_ERR_MASK));
}

/**
 * @brief Clear CRC error flag
 */
LOCAL_INLINE void SCG_HWA_ClearCrcErrorFlag(void)
{
    SCG->CRCCSR |= (uint32_t)SCG_CRCCSR_ERR_MASK;
}

/**
 * @brief Get CRC result
 */
LOCAL_INLINE uint32_t SCG_HWA_GetCrcResult(void)
{
    return SCG->CRCRES;
}

/**
 * @brief Enable SCG register CRC trigger mode
 */
LOCAL_INLINE void SCG_HWA_EnableCrcTriggerMode(void)
{
    SCG->CRCCSR |= (uint32_t)SCG_CRCCSR_TRGEN_MASK;
}

/**
 * @brief Disable SCG register CRC trigger mode
 */
LOCAL_INLINE void SCG_HWA_DisableCrcTriggerMode(void)
{
    SCG->CRCCSR &= ~(uint32_t)SCG_CRCCSR_TRGEN_MASK;
}

/** @}*/ /* HwA_SCG */

#endif /* #ifndef _HWA_SCG_H_ */
