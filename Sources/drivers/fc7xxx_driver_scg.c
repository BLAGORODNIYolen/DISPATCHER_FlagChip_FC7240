/**
 * @file fc7xxx_driver_scg.c
 * @author Flagchip
 * @brief FC7xxx SCG driver type definition and API
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2024-01-12    Flagchip085    N/A          First version for FC7240
********************************************************************************/
#include "fc7xxx_driver_scg.h"
#include "fc7xxx_board_conf.h"

#if ((FOSC_FREQUENCY < 16000000U) || (FOSC_FREQUENCY > 48000000U))
#error "FOSC is not in range 16M ~ 48 M"
#endif

/***************** Macros *********************/
#define SIRC_CLOCK                          12000000U
#define SIRC32K_CLOCK                       32000U
#define FIRC_CLOCK                          96000000U
#define NVM_CLOCK                           12000000U
#define FOSC_STABILIZATION_TIMEOUT          96000U
#define FIRC_STABILIZATION_TIMEOUT          20U
#define SIRC_STABILIZATION_TIMEOUT          100U
#define SOSC_STABILIZATION_TIMEOUT          320500U
#define PLL_STABILIZATION_TIMEOUT           320500U
#define SCG_CLKSRC_STABILIZATION_TIMEOUT    1000U
#define CLOCK_OFF_STABILIZATION_TIMEOUT     1000U /* clock out time is about 1us */
#define CLOCK_DIV_STABILIZATION_TIMEOUT     1000U

#define PLL0_CLK_MAX                        240000000U
#define PLL1_CLK_MAX                        320000000U
#define PLL_VCO_CLK_MAX                     800000000U
#define PLL_VCO_CLK_MIN                     300000000U
#define PLL_FEEDBACK_CLK_MAX                4000000U
#define PLL_FEEDBACK_CLK_MIN                2000000U
#define SYS_CORE_CLK_MAX                    240000000U
#define SYS_BUS_CLK_MAX                     120000000U
#define SYS_SLOW_CLK_MAX                    60000000U

#define FOSC_DIVH_MAX_CLOCK                 48000000U
#define FOSC_DIVM_MAX_CLOCK                 48000000U
#define FOSC_DIVL_MAX_CLOCK                 48000000U
#define FIRC_DIVH_MAX_CLOCK                 96000000U
#define FIRC_DIVM_MAX_CLOCK                 96000000U
#define FIRC_DIVL_MAX_CLOCK                 48000000U
#define PLL0_DIVH_MAX_CLOCK                 240000000U
#define PLL0_DIVM_MAX_CLOCK                 120000000U
#define PLL0_DIVL_MAX_CLOCK                 60000000U
#define PLL1_DIVH_MAX_CLOCK                 320000000U
#define PLL1_DIVM_MAX_CLOCK                 160000000U
#define PLL1_DIVL_MAX_CLOCK                 80000000U

/***************** mcaro function *********************/
#define SCG_CheckClockAckStatus(x, timeout, returnVal)                      \
    while ((x) && (timeout > 0U))                                           \
    {                                                                       \
        timeout--;                                                          \
    }                                                                       \
    if (timeout != 0U)                                                      \
    {                                                                       \
        returnVal = SCG_STATUS_SUCCESS;                                     \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        returnVal = SCG_STATUS_TIMEOUT;                                     \
    }


#define SCG_GetDivHClock(_clock_, input_freq, ouput_freq)                   \
    {                                                                       \
        uint32_t u32DivRegVal;                                              \
                                                                            \
        u32DivRegVal = SCG_HWA_GetClockDiv(_clock_);                        \
        ouput_freq = SCG_CALCULATE_DIVH_FREQ(input_freq, u32DivRegVal);     \
    }

#define SCG_GetDivMClock(_clock_, input_freq, ouput_freq)                   \
    {                                                                       \
        uint32_t u32DivRegVal;                                              \
        u32DivRegVal = SCG_HWA_GetClockDiv(_clock_);                        \
        ouput_freq = SCG_CALCULATE_DIVM_FREQ(input_freq, u32DivRegVal);     \
    }

#define SCG_GetDivLClock(_clock_, input_freq, ouput_freq)                   \
    {                                                                       \
        uint32_t u32DivRegVal;                                              \
        u32DivRegVal = SCG_HWA_GetClockDiv(_clock_);                        \
        ouput_freq = SCG_CALCULATE_DIVL_FREQ(input_freq, u32DivRegVal);     \
    }

/***************** Local Functions *********************/

static uint32_t SCG_CalculateSircFreq(const SCG_ClkSrcType eScgClockName)
{
    uint32_t u32Freq;

    if (SCG_SIRC_CLK == eScgClockName)
    {
        u32Freq = SIRC_CLOCK;
    }
    else if (SCG_SIRCDIVH_CLK == eScgClockName)
    {
        SCG_GetDivHClock(SCG_SIRC_CLOCK_SYMBOL, SIRC_CLOCK, u32Freq);
    }
    else if (SCG_SIRCDIVM_CLK == eScgClockName)
    {
        SCG_GetDivMClock(SCG_SIRC_CLOCK_SYMBOL, SIRC_CLOCK, u32Freq);
    }
    else if (SCG_SIRCDIVL_CLK == eScgClockName)
    {
        SCG_GetDivLClock(SCG_SIRC_CLOCK_SYMBOL, SIRC_CLOCK, u32Freq);
    }
    else
    {
        u32Freq = UNKNOWN_CLOCK;
    }

    return u32Freq;
}

static uint32_t SCG_CalculateFircFreq(const SCG_ClkSrcType eScgClockName)
{
    uint32_t u32Freq;

    if (true == SCG_HWA_GetClockVliad(SCG_FIRC_CLOCK_SYMBOL))
    {
        if (SCG_FIRC_CLK == eScgClockName)
        {
            u32Freq = FIRC_CLOCK;
        }
        else if (SCG_FIRCDIVH_CLK == eScgClockName)
        {
            SCG_GetDivHClock(SCG_FIRC_CLOCK_SYMBOL, FIRC_CLOCK, u32Freq);
        }
        else if (SCG_FIRCDIVM_CLK == eScgClockName)
        {
            SCG_GetDivMClock(SCG_FIRC_CLOCK_SYMBOL, FIRC_CLOCK, u32Freq);
        }
        else if (SCG_FIRCDIVL_CLK == eScgClockName)
        {
            SCG_GetDivLClock(SCG_FIRC_CLOCK_SYMBOL, FIRC_CLOCK, u32Freq);
        }
        else
        {
            u32Freq = UNKNOWN_CLOCK;
        }
    }
    else
    {
        u32Freq = UNKNOWN_CLOCK;
    }

    return u32Freq;
}

static uint32_t SCG_CalculateFoscFreq(const SCG_ClkSrcType eScgClockName)
{
    uint32_t u32Freq;

    if (true == SCG_HWA_GetClockVliad(SCG_FOSC_CLOCK_SYMBOL))
    {
        if (SCG_FOSC_CLK == eScgClockName)
        {
            u32Freq = FOSC_FREQUENCY;
        }
        else if (SCG_FOSCDIVH_CLK == eScgClockName)
        {
            SCG_GetDivHClock(SCG_FOSC_CLOCK_SYMBOL, FOSC_FREQUENCY, u32Freq);
        }
        else if (SCG_FOSCDIVM_CLK == eScgClockName)
        {
            SCG_GetDivMClock(SCG_FOSC_CLOCK_SYMBOL, FOSC_FREQUENCY, u32Freq);
        }
        else if (SCG_FOSCDIVL_CLK == eScgClockName)
        {
            SCG_GetDivLClock(SCG_FOSC_CLOCK_SYMBOL, FOSC_FREQUENCY, u32Freq);
        }
        else
        {
            u32Freq = UNKNOWN_CLOCK;
        }
    }
    else
    {
        u32Freq = UNKNOWN_CLOCK;
    }

    return u32Freq;
}

static uint32_t SCG_CalculatePll0Freq(const SCG_ClkSrcType eScgClockName)
{
    uint32_t u32Freq, u32ClkFreq;
    uint32_t u32Temp, u32PreDiv, u32PstDiv;
    uint32_t u32Mult;

    if (true == SCG_HWA_GetClockVliad(SCG_PLL0_CLOCK_SYMBOL))
    {
        u32Temp = SCG_HWA_GetPllSrc(SCG_PLL0_CLOCK_SYMBOL);
        if (u32Temp == (uint32_t)SCG_PLLSOURCE_FIRC)
        {

            u32ClkFreq = FIRC_CLOCK / 2U;
        }
        else
        {
            /* (u32Temp == (uint32_t)SCG_PLLSOURCE_FOSC) */
            u32ClkFreq = FOSC_FREQUENCY;
        }
        u32PreDiv = SCG_HWA_GetPllPrediv(SCG_PLL0_CLOCK_SYMBOL) + 1U;
        u32Mult = SCG_HWA_GetPllMult(SCG_PLL0_CLOCK_SYMBOL) + 1U;
        u32PstDiv = SCG_HWA_GetPllPstdiv(SCG_PLL0_CLOCK_SYMBOL);
        if(u32PstDiv == 0U)
        {
            u32PstDiv = 1U;
        }
        u32ClkFreq = (u32ClkFreq / (u32PreDiv) * (u32Mult)) >> (u32PstDiv);

        if (SCG_PLL0_CLK == eScgClockName)
        {
            u32Freq = u32ClkFreq;
        }
        else if (SCG_PLL0DIVH_CLK == eScgClockName)
        {
            SCG_GetDivHClock(SCG_PLL0_CLOCK_SYMBOL, u32ClkFreq, u32Freq);
        }
        else if (SCG_PLL0DIVM_CLK == eScgClockName)
        {
            SCG_GetDivMClock(SCG_PLL0_CLOCK_SYMBOL, u32ClkFreq, u32Freq);
        }
        else if (SCG_PLL0DIVL_CLK == eScgClockName)
        {
            SCG_GetDivLClock(SCG_PLL0_CLOCK_SYMBOL, u32ClkFreq, u32Freq);
        }
        else
        {
            u32Freq = UNKNOWN_CLOCK;
        }
    }
    else
    {
        u32Freq = UNKNOWN_CLOCK;
    }

    return u32Freq;
}

static uint32_t SCG_CalculatePll1Freq(const SCG_ClkSrcType eScgClockName)
{
    uint32_t u32Freq, u32ClkFreq;
    uint32_t u32Temp, u32PreDiv, u32PstDiv;
    uint32_t u32Mult;

    if (true == SCG_HWA_GetClockVliad(SCG_PLL1_CLOCK_SYMBOL))
    {
        u32Temp = SCG_HWA_GetPllSrc(SCG_PLL1_CLOCK_SYMBOL);
        if (u32Temp == (uint32_t)SCG_PLLSOURCE_FIRC)
        {
            u32ClkFreq = FIRC_CLOCK / 2U;
        }
        else
        {
            /* (u32Temp == (uint32_t)SCG_PLLSOURCE_FOSC) */
            u32ClkFreq = FOSC_FREQUENCY;
        }
        u32PreDiv = SCG_HWA_GetPllPrediv(SCG_PLL1_CLOCK_SYMBOL) + 1U;
        u32Mult = SCG_HWA_GetPllMult(SCG_PLL1_CLOCK_SYMBOL) + 1U;
        u32PstDiv = SCG_HWA_GetPllPstdiv(SCG_PLL1_CLOCK_SYMBOL);
        if(u32PstDiv == 0U)
        {
            u32PstDiv = 1U;
        }
        u32ClkFreq = (u32ClkFreq / (u32PreDiv) * (u32Mult)) >> (u32PstDiv);

        if (SCG_PLL1_CLK == eScgClockName)
        {
            u32Freq = u32ClkFreq;
        }
        else if (SCG_PLL1DIVH_CLK == eScgClockName)
        {
            SCG_GetDivHClock(SCG_PLL1_CLOCK_SYMBOL, u32ClkFreq, u32Freq);
        }
        else if (SCG_PLL1DIVM_CLK == eScgClockName)
        {
            SCG_GetDivMClock(SCG_PLL1_CLOCK_SYMBOL, u32ClkFreq, u32Freq);
        }
        else if (SCG_PLL1DIVL_CLK == eScgClockName)
        {
            SCG_GetDivLClock(SCG_PLL1_CLOCK_SYMBOL, u32ClkFreq, u32Freq);
        }
        else
        {
            u32Freq = UNKNOWN_CLOCK;
        }
    }
    else
    {
        u32Freq = UNKNOWN_CLOCK;
    }

    return u32Freq;
}

static uint32_t SCG_CalculateSystemFreq(const SCG_ClkSrcType eScgClockName)
{
    uint32_t u32Freq, u32ClkFreq;
    uint32_t u32Temp, u32DivCore, u32DivBus, u32DivSlow;

    u32Temp = (uint32_t)SCG_HWA_GetSysClkSrc();

    if ((uint32_t)SCG_CLOCK_SRC_FOSC == u32Temp)
    {
        u32ClkFreq = FOSC_FREQUENCY;
    }
    else if ((uint32_t)SCG_CLOCK_SRC_FIRC == u32Temp)
    {
        u32ClkFreq = FIRC_CLOCK;
    }
    else if ((uint32_t)SCG_CLOCK_SRC_PLL0 == u32Temp)
    {
        u32ClkFreq = SCG_CalculatePll0Freq(SCG_PLL0_CLK);
    }
    else if ((uint32_t)SCG_CLOCK_SRC_SIRC == u32Temp)
    {
        u32ClkFreq = SCG_CalculateSircFreq(SCG_SIRC_CLK);
    }
    else
    {
        u32ClkFreq = UNKNOWN_CLOCK;
    }

    u32DivCore = (uint32_t)(SCG_HWA_GetSysClkDivCore() + 1U);
    u32DivBus = (uint32_t)(SCG_HWA_GetSysClkDivBus() + 1U);
    u32DivSlow = (uint32_t)(SCG_HWA_GetSysClkDivSlow() + 1U);

    u32ClkFreq = (uint32_t)(u32ClkFreq / u32DivCore);

    if (SCG_CORE_CLK == eScgClockName)
    {
        u32Freq = u32ClkFreq;
    }
    else if (SCG_BUS_CLK == eScgClockName)
    {
        u32Freq = (uint32_t)(u32ClkFreq / u32DivBus);
    }
    else
    {
        /* (SCG_SLOW_CLK == eScgClockName) */
        u32Freq = (uint32_t)((u32ClkFreq / u32DivBus) / u32DivSlow);
    }

    return u32Freq;
}

static uint32_t SCG_CalculateClkOutFreq(void)
{
    uint8_t u8ClockoutSrc;
    uint32_t u32Freq;
    /* check clock out configuration */
    u8ClockoutSrc = SCG_HWA_GetClkOutSel();

    if ((uint8_t)SCG_CLOCKOUT_SRC_OFF == u8ClockoutSrc)
    {
        u32Freq = 0U;
    }
    else if ((uint8_t)SCG_CLOCKOUT_SRC_FOSC == u8ClockoutSrc)
    {
        u32Freq = FOSC_FREQUENCY;
    }
    else if ((uint8_t)SCG_CLOCKOUT_SRC_SIRC == u8ClockoutSrc)
    {
        u32Freq = SCG_CalculateSircFreq(SCG_SIRC_CLK);
    }
    else if ((uint8_t)SCG_CLOCKOUT_SRC_FIRC == u8ClockoutSrc)
    {
        u32Freq = SCG_CalculateFircFreq(SCG_FIRC_CLK);
    }
    else if ((uint8_t)SCG_CLOCKOUT_SRC_SOSC == u8ClockoutSrc)
    {
        u32Freq = SOSC_FREQUENCY;
    }
    else if ((uint8_t)SCG_CLOCKOUT_SRC_PLL1 == u8ClockoutSrc)
    {
        u32Freq = SCG_CalculatePll1Freq(SCG_PLL1_CLK);
    }
    else if ((uint8_t)SCG_CLOCKOUT_SRC_PLL0 == u8ClockoutSrc)
    {
        u32Freq = SCG_CalculatePll0Freq(SCG_PLL0_CLK);
    }
    else if ((uint8_t)SCG_CLOCKOUT_SRC_SIRC32K == u8ClockoutSrc)
    {
        u32Freq = SIRC32K_CLOCK;
    }
    else
    {
        u32Freq = UNKNOWN_CLOCK;
    }

    return u32Freq;
}

static uint32_t SCG_CalculateCMU4RefFreq(void)
{
    uint32_t u32Freq,u32Temp;

    u32Temp = SCG_HWA_GetClkOutCfg();

    if((u32Temp & SCG_CLKOUTCFG_CMU4CLK_FOSC_MASK) != 0U)
    {
        u32Freq = FOSC_FREQUENCY;
    }
    else if((u32Temp & SCG_CLKOUTCFG_CMU4CLK_SIRC_MASK) != 0U)
    {
        u32Freq = SIRC_CLOCK;
    }
    else
    {
        u32Freq = UNKNOWN_CLOCK;
    }

    return u32Freq;
}

static SCG_StatusType SCG_EnablePLL0(const SCG_PllType *const pPllConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32TempVal;
    uint32_t u32Freq;
    uint32_t u32FeedBackFreq,u32VcoFreq;
    uint32_t u32DivHClockFreq = 0u;
    uint32_t u32DivMClockFreq = 0u;
    uint32_t u32DivLClockFreq = 0u;
    uint32_t u32Pll0DivEn = 0u;

    /* check pll is valid, if valid, do not configure PLL */
    if (true == SCG_HWA_GetClockVliad(SCG_PLL0_CLOCK_SYMBOL))
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }
    else
    {
        /*   PLL input is FOSC or FIRC clock/2  */
        u32Freq = (SCG_PLLSOURCE_FOSC == pPllConfig->eSrc) ? (FOSC_FREQUENCY) : (FIRC_CLOCK / 2U);

        /* Check the PLL feedback clock range */
        u32FeedBackFreq = u32Freq / (pPllConfig->u8Prediv + 1U);
        if(u32FeedBackFreq < PLL_FEEDBACK_CLK_MIN || u32FeedBackFreq > PLL_FEEDBACK_CLK_MAX)
        {
            eStatusVal = SCG_STATUS_PARAM_ERROR;
        }
        else
        {
            /* Check the PLL VCO clock range */
            u32VcoFreq = u32FeedBackFreq * (pPllConfig->u16Mult + 1U);
            if((u32VcoFreq < PLL_VCO_CLK_MIN) || (u32VcoFreq > PLL_VCO_CLK_MAX))
            {
                eStatusVal = SCG_STATUS_PARAM_ERROR;
            }
            else
            {
                /* Check the PLL out clock range */
                u32Freq = u32VcoFreq >> (uint32_t)pPllConfig->ePstDiv;
                if (u32Freq > PLL0_CLK_MAX)
                {
                    eStatusVal = SCG_STATUS_PARAM_ERROR;
                }
            }
        }

        /* Check DIV clock frequency is valid or not */
        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            if(pPllConfig->eDivH != SCG_ASYNC_CLOCK_DISABLE)
            {
                u32DivHClockFreq = (uint32_t)(u32Freq >> ((uint32_t)pPllConfig->eDivH - 1u));
                u32Pll0DivEn |= (uint32_t)SCG_CLOCK_DIV_H;
            }
            if(pPllConfig->eDivM != SCG_ASYNC_CLOCK_DISABLE)
            {
                u32DivMClockFreq = (uint32_t)(u32Freq >> ((uint32_t)pPllConfig->eDivM - 1u));
                u32Pll0DivEn |= (uint32_t)SCG_CLOCK_DIV_M;
            }
            if(pPllConfig->eDivL != SCG_ASYNC_CLOCK_DISABLE)
            {
                u32DivLClockFreq = (uint32_t)(u32Freq >> ((uint32_t)pPllConfig->eDivL - 1u));
                u32Pll0DivEn |= (uint32_t)SCG_CLOCK_DIV_L;
            }
            if ((u32DivHClockFreq > PLL0_DIVH_MAX_CLOCK) || (u32DivMClockFreq > PLL0_DIVM_MAX_CLOCK) || (u32DivLClockFreq > PLL0_DIVL_MAX_CLOCK))
            {
                eStatusVal = SCG_STATUS_PARAM_ERROR;
            }
        }
    }

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* unlock PLL CSR register */
        SCG_HWA_UnlockPllCsr(SCG_PLL0_CLOCK_SYMBOL);

        /* Configure PLLCFG register */
        u32TempVal =  SCG_PLLCFG_PREDIV(pPllConfig->u8Prediv) | SCG_PLLCFG_MULT(pPllConfig->u16Mult) | SCG_PLLCFG_PSTDIV(
                          pPllConfig->ePstDiv) | SCG_PLLCFG_SOURCE(pPllConfig->eSrc) ;
        SCG_HWA_SetPllCfg(SCG_PLL0_CLOCK_SYMBOL, u32TempVal);

        /* Configure PLLCSR register */
        u32TempVal = SCG_PLLCSR_STEN(pPllConfig->bSten);
        SCG_HWA_SetPllCsr(SCG_PLL0_CLOCK_SYMBOL, u32TempVal);

        /* Configure PLLDIV */
        SCG_HWA_DiablePll0Div(SCG_CLOCK_DIV_ALL);
        u32TempVal = SCG_HWA_GetClockDiv(SCG_PLL0_CLOCK_SYMBOL);
        u32TempVal &= ~(uint32_t)(SCG_PLLDIV_DIVL_MASK | SCG_PLLDIV_DIVM_MASK | SCG_PLLDIV_DIVH_MASK);
        u32TempVal |= (SCG_PLLDIV_DIVH(pPllConfig->eDivH) | SCG_PLLDIV_DIVM(pPllConfig->eDivM) | SCG_PLLDIV_DIVL(
                           pPllConfig->eDivL));
        SCG_HWA_SetPllDiv(SCG_PLL0_CLOCK_SYMBOL, u32TempVal) ;

        /* Set CSR[EN] bit to 1 */
        SCG_HWA_EnablePll(SCG_PLL0_CLOCK_SYMBOL);

        /* Wait PLL valid */
        u32TempVal = PLL_STABILIZATION_TIMEOUT;
        SCG_CheckClockAckStatus((false == SCG_HWA_GetClockVliad(SCG_PLL0_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            /* Enable PLLDIV */
            SCG_HWA_EnablePll0Div((SCG_DivEnableType)u32Pll0DivEn);

            if (pPllConfig->bCm)
            {
                SCG_HWA_EnablePllClockMonitor(SCG_PLL0_CLOCK_SYMBOL);
            }

            if (pPllConfig->bCmre)
            {
                SCG_HWA_EnablePllClockMonitorReset(SCG_PLL0_CLOCK_SYMBOL);
            }

            if (pPllConfig->bLock)
            {
                /* lock CSR register */
                SCG_HWA_LockPllCsr(SCG_PLL0_CLOCK_SYMBOL);
            }

            /* Wait DIV[ACK] change to 1 */
            u32TempVal = CLOCK_DIV_STABILIZATION_TIMEOUT;
            SCG_CheckClockAckStatus((SCG_HWA_GetPll0DivAck((SCG_DivEnableType)u32Pll0DivEn) != true), u32TempVal, eStatusVal)
        }
        else
        {
            /* Clear CFG configuration */
            SCG_HWA_SetPllCfg(SCG_PLL0_CLOCK_SYMBOL, 0U);

            /* Clear CSR configuration */
            SCG_HWA_SetPllCsr(SCG_PLL0_CLOCK_SYMBOL, 0U);

            /* Clear DIV configuration*/
            SCG_HWA_SetPllDiv(SCG_PLL0_CLOCK_SYMBOL, 0U);
        }

    }

    return eStatusVal;
}

static SCG_StatusType SCG_EnablePLL1(const SCG_PllType *const pPllConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32TempVal;
    uint32_t u32Freq;
    uint32_t u32FeedBackFreq,u32VcoFreq;
    uint32_t u32DivHClockFreq = 0u;
    uint32_t u32DivMClockFreq = 0u;
    uint32_t u32DivLClockFreq = 0u;
    uint32_t u32Pll1DivEn = 0u;

    /* check pll is valid, if valid, do not configure PLL */
    if (true == SCG_HWA_GetClockVliad(SCG_PLL1_CLOCK_SYMBOL))
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }
    else
    {
        /*   PLL input is FOSC or FIRC clock/2  */
        u32Freq = (SCG_PLLSOURCE_FOSC == pPllConfig->eSrc) ? (FOSC_FREQUENCY) : (FIRC_CLOCK / 2U);

        /* Check the PLL feedback clock range */
        u32FeedBackFreq = u32Freq / (pPllConfig->u8Prediv + 1U);
        if(u32FeedBackFreq < PLL_FEEDBACK_CLK_MIN || u32FeedBackFreq > PLL_FEEDBACK_CLK_MAX)
        {
            eStatusVal = SCG_STATUS_PARAM_ERROR;
        }
        else
        {
            /* Check the PLL VCO clock range */
            u32VcoFreq = u32FeedBackFreq * (pPllConfig->u16Mult + 1U);
            if((u32VcoFreq < PLL_VCO_CLK_MIN) || (u32VcoFreq > PLL_VCO_CLK_MAX))
            {
                eStatusVal = SCG_STATUS_PARAM_ERROR;
            }
            else
            {
                /* Check the PLL out clock range */
                u32Freq = u32VcoFreq >> (uint32_t)pPllConfig->ePstDiv;
                if (u32Freq > PLL1_CLK_MAX)
                {
                    eStatusVal = SCG_STATUS_PARAM_ERROR;
                }
            }
        }

        /* Check DIV clock frequency is valid or not */
        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            if(pPllConfig->eDivH != SCG_ASYNC_CLOCK_DISABLE)
            {
                u32DivHClockFreq = (uint32_t)(u32Freq >> ((uint32_t)pPllConfig->eDivH - 1u));
                u32Pll1DivEn |= (uint32_t)SCG_CLOCK_DIV_H;
            }
            if(pPllConfig->eDivM != SCG_ASYNC_CLOCK_DISABLE)
            {
                u32DivMClockFreq = (uint32_t)(u32Freq >> ((uint32_t)pPllConfig->eDivM - 1u));
                u32Pll1DivEn |= (uint32_t)SCG_CLOCK_DIV_M;
            }
            if(pPllConfig->eDivL != SCG_ASYNC_CLOCK_DISABLE)
            {
                u32DivLClockFreq = (uint32_t)(u32Freq >> ((uint32_t)pPllConfig->eDivL - 1u));
                u32Pll1DivEn |= (uint32_t)SCG_CLOCK_DIV_L;
            }
            if ((u32DivHClockFreq > PLL1_DIVH_MAX_CLOCK) || (u32DivMClockFreq > PLL1_DIVM_MAX_CLOCK) || (u32DivLClockFreq > PLL1_DIVL_MAX_CLOCK))
            {
                eStatusVal = SCG_STATUS_PARAM_ERROR;
            }
        }
    }

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* unlock PLL CSR register */
        SCG_HWA_UnlockPllCsr(SCG_PLL1_CLOCK_SYMBOL);

        /* Configure PLLCFG register */
        u32TempVal =  SCG_PLLCFG_PREDIV(pPllConfig->u8Prediv) | SCG_PLLCFG_MULT(pPllConfig->u16Mult) | SCG_PLLCFG_PSTDIV(
                          pPllConfig->ePstDiv) | SCG_PLLCFG_SOURCE(pPllConfig->eSrc) ;
        SCG_HWA_SetPllCfg(SCG_PLL1_CLOCK_SYMBOL, u32TempVal);

        /* Configure PLLCSR register */
        u32TempVal = SCG_PLLCSR_STEN(pPllConfig->bSten);
        SCG_HWA_SetPllCsr(SCG_PLL1_CLOCK_SYMBOL, u32TempVal);

        /* Configure PLLDIV */
        SCG_HWA_DiablePll1Div(SCG_CLOCK_DIV_ALL);
        u32TempVal = SCG_HWA_GetClockDiv(SCG_PLL1_CLOCK_SYMBOL);
        u32TempVal &= ~(uint32_t)(SCG_PLLDIV_DIVL_MASK | SCG_PLLDIV_DIVM_MASK | SCG_PLLDIV_DIVH_MASK);
        u32TempVal |= (SCG_PLLDIV_DIVH(pPllConfig->eDivH) | SCG_PLLDIV_DIVM(pPllConfig->eDivM) | SCG_PLLDIV_DIVL(
                           pPllConfig->eDivL));
        SCG_HWA_SetPllDiv(SCG_PLL1_CLOCK_SYMBOL, u32TempVal) ;

        /* Set CSR[EN] bit to 1 */
        SCG_HWA_EnablePll(SCG_PLL1_CLOCK_SYMBOL);

        /* Wait PLL valid */
        u32TempVal = PLL_STABILIZATION_TIMEOUT;
        SCG_CheckClockAckStatus((false == SCG_HWA_GetClockVliad(SCG_PLL1_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            /* Enable PLLDIV */
            SCG_HWA_EnablePll1Div((SCG_DivEnableType)u32Pll1DivEn);

            if (pPllConfig->bCm)
            {
                SCG_HWA_EnablePllClockMonitor(SCG_PLL1_CLOCK_SYMBOL);
            }

            if (pPllConfig->bCmre)
            {
                SCG_HWA_EnablePllClockMonitorReset(SCG_PLL1_CLOCK_SYMBOL);
            }

            if (pPllConfig->bLock)
            {
                /* lock CSR register */
                SCG_HWA_LockPllCsr(SCG_PLL1_CLOCK_SYMBOL);
            }

            /* Wait DIV[ACK] change to 1 */
            u32TempVal = CLOCK_DIV_STABILIZATION_TIMEOUT;
            SCG_CheckClockAckStatus((SCG_HWA_GetPll1DivAck((SCG_DivEnableType)u32Pll1DivEn) != true), u32TempVal, eStatusVal)
        }
        else
        {
            /* Clear CFG configuration */
            SCG_HWA_SetPllCfg(SCG_PLL1_CLOCK_SYMBOL, 0U);

            /* Clear CSR configuration */
            SCG_HWA_SetPllCsr(SCG_PLL1_CLOCK_SYMBOL, 0U);

            /* Clear DIV configuration*/
            SCG_HWA_SetPllDiv(SCG_PLL1_CLOCK_SYMBOL, 0U);
        }

    }

    return eStatusVal;
}

static SCG_StatusType SCG_DisablePLL0(void)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32TempVal;

    /* unlock PLL CSR register */
    SCG_HWA_UnlockPllCsr(SCG_PLL0_CLOCK_SYMBOL);

    /* Clear CFG configuration */
    SCG_HWA_SetPllCfg(SCG_PLL0_CLOCK_SYMBOL, 0U);

    /* Clear CSR configuration */
    SCG_HWA_SetPllCsr(SCG_PLL0_CLOCK_SYMBOL, 0U);

    u32TempVal = CLOCK_OFF_STABILIZATION_TIMEOUT;
    SCG_CheckClockAckStatus((true == SCG_HWA_GetClockVliad(SCG_PLL0_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* Clear CSR register */
        SCG_HWA_SetPllCsr(SCG_PLL0_CLOCK_SYMBOL, 0U);

        /* In order to avoid the DIV register value not cleared, Clear PLL DIV register twice */
        SCG_HWA_SetPllDiv(SCG_PLL0_CLOCK_SYMBOL, 0U);
        SCG_HWA_SetPllDiv(SCG_PLL0_CLOCK_SYMBOL, 0U);
    }


    return eStatusVal;
}

static SCG_StatusType SCG_DisablePLL1(void)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32TempVal;

    /* unlock PLL CSR register */
    SCG_HWA_UnlockPllCsr(SCG_PLL1_CLOCK_SYMBOL);

    /* Clear CFG configuration */
    SCG_HWA_SetPllCfg(SCG_PLL1_CLOCK_SYMBOL, 0U);

    /* Clear CSR configuration */
    SCG_HWA_SetPllCsr(SCG_PLL1_CLOCK_SYMBOL, 0U);

    u32TempVal = CLOCK_OFF_STABILIZATION_TIMEOUT;
    SCG_CheckClockAckStatus((true == SCG_HWA_GetClockVliad(SCG_PLL1_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* Clear CSR register */
        SCG_HWA_SetPllCsr(SCG_PLL1_CLOCK_SYMBOL, 0U);

        /* In order to avoid the DIV register value not cleared, Clear PLL DIV register twice */
        SCG_HWA_SetPllDiv(SCG_PLL1_CLOCK_SYMBOL, 0U);
        SCG_HWA_SetPllDiv(SCG_PLL1_CLOCK_SYMBOL, 0U);
    }

    return eStatusVal;
}

/**
 * @brief Check the system clock frequency
 * @details This function check the system clock source valid and the system clock dividers valid, and get the frequency of eClock
 *
 * @param eClock selected clock source
 * @param pSysClkConfig system clock configuration
 * @param pClockFreq pointer to the memory to save clock source frequency
 * @return SCG_StatusType function status
 *
 */
static SCG_StatusType SCG_CheckSystemClockSourceFreq(const SCG_ClockSrcType eClock,const SCG_ClockCtrlType *const pSysClkConfig,uint32_t *pClockFreq)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32Freq;
    uint32_t u32FreqCore, u32FreqBus, u32FreqSlow;
    bool eClockValid;

    if (SCG_CLOCK_SRC_FOSC == eClock)
    {
        eClockValid = SCG_HWA_GetClockVliad(SCG_FOSC_CLOCK_SYMBOL);
        u32Freq = FOSC_FREQUENCY;
    }
    else if (SCG_CLOCK_SRC_FIRC == eClock)
    {
        eClockValid = SCG_HWA_GetClockVliad(SCG_FIRC_CLOCK_SYMBOL);
        u32Freq = FIRC_CLOCK;
    }
    else if (SCG_CLOCK_SRC_PLL0 == eClock)
    {
        eClockValid = SCG_HWA_GetClockVliad(SCG_PLL0_CLOCK_SYMBOL);
        u32Freq = SCG_CalculatePll0Freq(SCG_PLL0_CLK);

    }
    else if (SCG_CLOCK_SRC_SIRC == eClock)
    {
        eClockValid = SCG_HWA_GetClockVliad(SCG_SIRC_CLOCK_SYMBOL);
        u32Freq = SIRC_CLOCK;
    }
    else
    {
        eClockValid = false;
    }

    if(eClockValid == false)
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }
    else
    {
        *pClockFreq = u32Freq;

        if(pSysClkConfig != NULL_PTR)
        {
            u32FreqCore =  u32Freq / ((uint8_t)pSysClkConfig->eDivCore + 1U);
            u32FreqBus =  u32FreqCore / ((uint8_t)pSysClkConfig->eDivBus + 1U);
            u32FreqSlow =  u32FreqBus / ((uint8_t)pSysClkConfig->eDivSlow + 1U);
            if ((u32FreqCore > SYS_CORE_CLK_MAX) || (u32FreqBus > SYS_BUS_CLK_MAX) || (u32FreqSlow > SYS_SLOW_CLK_MAX))
            {
                eStatusVal = SCG_STATUS_PARAM_ERROR;
            }
        }
    }
    return eStatusVal;
}

/**
 * @brief Switch system clock source , and configure system clock divider if pSysClkConfig is not null.
 * @details If pSysClkConfig is null , and clock switch form slow to fast(eg. FIRC to PLL0),
 *          the bus and slow clock may exceed the max value. So the new divider must be configured
 *          if the system clock is switched to a faster source.
 *
 * @param eClock selected clock source
 * @return SCG_StatusType function status
 *            SCG_STATUS_SUCCESS : clock source and dividers are valid,and switch system clock successfully
 *         SCG_STATUS_SEQUENCE_ERROR: new clock source is not enabled
 *         SCG_STATUS_PARAM_ERROR: the core bus slow divider are invalid
 *         SCG_STATUS_TIMEOUT: switch system clock procedure time out
 */
static SCG_StatusType SCG_SwitchSystemClockWithConfig(const SCG_ClockSrcType eClock,const SCG_ClockCtrlType *const pSysClkConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32Timeout;
    uint32_t u32CurClkFreq = 0U,u32NewClkFreq;
    uint32_t u32RegValue;
    uint8_t u8CurClkSrc,u8ClkSrc;

    u8CurClkSrc = SCG_HWA_GetSysClkSrc();
    if(u8CurClkSrc != eClock)
    {
        eStatusVal = SCG_CheckSystemClockSourceFreq(eClock,pSysClkConfig,&u32NewClkFreq);

        if(eStatusVal == SCG_STATUS_SUCCESS)
        {
            /* Get current system clock source frequency */
            if (SCG_CLOCK_SRC_FOSC == u8CurClkSrc)
            {
                u32CurClkFreq = FOSC_FREQUENCY;
            }
            else if (SCG_CLOCK_SRC_FIRC == u8CurClkSrc)
            {
                u32CurClkFreq = FIRC_CLOCK;
            }
            else if (SCG_CLOCK_SRC_PLL0 == u8CurClkSrc)
            {
                u32CurClkFreq = SCG_CalculatePll0Freq(SCG_PLL0_CLK);
            }
            else if (SCG_CLOCK_SRC_SIRC == u8CurClkSrc)
            {
                u32CurClkFreq = SIRC_CLOCK;
            }
            else
            {
                /* Never come here */
            }

            /* To switch the system clock source from slow to fast, configure the divider first to ensure that
               the core bus slow clocks do not exceed the max value */
            if((pSysClkConfig != NULL_PTR) && (u32NewClkFreq > u32CurClkFreq))
            {
                u32RegValue = SCG_HWA_GetCCR();
                u32RegValue &= ~(SCG_CCR_SYSCLK_CME_MASK | SCG_CCR_DIVCORE_MASK | SCG_CCR_DIVBUS_MASK | SCG_CCR_DIVSLOW_MASK);
                u32RegValue |= (uint32_t)((uint32_t)SCG_CCR_SYSCLK_CME(pSysClkConfig->bSysClkMonitor) |
                                          (uint32_t)SCG_CCR_DIVCORE(pSysClkConfig->eDivCore) |
                                          (uint32_t)SCG_CCR_DIVBUS(pSysClkConfig->eDivBus)  |
                                          (uint32_t)SCG_CCR_DIVSLOW(pSysClkConfig->eDivSlow));
                SCG_HWA_SetCCR(u32RegValue);
            }

            SCG_HWA_SetSystemClock((uint8_t)eClock);

            u32Timeout = SCG_CLKSRC_STABILIZATION_TIMEOUT;
            do {
                u8ClkSrc = SCG_HWA_GetSysClkSrc();
                --u32Timeout;
                if(u32Timeout == 0U)
                {
                    eStatusVal = SCG_STATUS_TIMEOUT;
                    break;
                }
            } while((SCG_HWA_GetSysClkUPRD() == false) && (u8ClkSrc != (uint8_t)eClock));

            if (eStatusVal == SCG_STATUS_SUCCESS)
            {
                /* To change the system clock source from fast to slow, configure the divider after selecting the clock source,
                   because it is safe to divide the slow frequency with the old divider */
                if((pSysClkConfig != NULL_PTR) && (u32NewClkFreq <= u32CurClkFreq))
                {
                    u32RegValue = SCG_HWA_GetCCR();
                    u32RegValue &= ~(SCG_CCR_SYSCLK_CME_MASK | SCG_CCR_DIVCORE_MASK | SCG_CCR_DIVBUS_MASK | SCG_CCR_DIVSLOW_MASK);
                    u32RegValue |= (uint32_t)((uint32_t)SCG_CCR_SYSCLK_CME(pSysClkConfig->bSysClkMonitor) |
                                              (uint32_t)SCG_CCR_DIVCORE(pSysClkConfig->eDivCore) |
                                              (uint32_t)SCG_CCR_DIVBUS(pSysClkConfig->eDivBus)  |
                                              (uint32_t)SCG_CCR_DIVSLOW(pSysClkConfig->eDivSlow));
                    SCG_HWA_SetCCR(u32RegValue);

                    u32Timeout = SCG_CLKSRC_STABILIZATION_TIMEOUT;
                    while(SCG_HWA_GetSysClkUPRD() == false)
                    {
                        --u32Timeout;
                        if(u32Timeout == 0U)
                        {
                            eStatusVal = SCG_STATUS_TIMEOUT;
                            break;
                        }
                    }
                }
            }

        }

    }
    return eStatusVal;
}

/***************** Global Functions *********************/
/**
 * @brief Enable SOSC
 *
 * @param pSoscConfig SOSC configuration
 * @return SCG_StatusType Function status
 */
SCG_StatusType SCG_EnableSOSC(const SCG_SoscType *const pSoscConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32TempVal;

    DEV_ASSERT(NULL_PTR != pSoscConfig);
    DEV_ASSERT(32768U == SOSC_FREQUENCY);

    /* Configure SOSC */
    SCG_HWA_SetSoscRecommendCfg();

    /* Unlock CSR register first */
    SCG_HWA_UnlockSoscCsrReg();

    /* Configure SOSC CSR register */
    u32TempVal = SCG_HWA_GetSoscCsr();
    u32TempVal &= ~(uint32_t)(SCG_SOSCCSR_BYPASS_MASK | SCG_SOSCCSR_CM_MASK | SCG_SOSCCSR_CMRE_MASK);
    u32TempVal |= SCG_SOSCCSR_BYPASS(pSoscConfig->bBypass);
    SCG_HWA_SetSoscCsr(u32TempVal);

    /* Enable SOSC*/
    SCG_HWA_EnableSosc();

    /* Wait SOSC valid */
    u32TempVal = SOSC_STABILIZATION_TIMEOUT;
    SCG_CheckClockAckStatus((false == SCG_HWA_GetClockVliad(SCG_SOSC_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        if (pSoscConfig->bCm)
        {
            SCG_HWA_EnableSoscClockMonitor();
        }

        if (pSoscConfig->bCmre)
        {
            SCG_HWA_EnableSoscClockMonitorReset();
        }

        if (pSoscConfig->bLock)
        {
            /* Lock CSR */
            SCG_HWA_LockSoscCsrReg();
        }
    }
    else
    {
        SCG_HWA_SetSoscCsr(0U);
    }

    return eStatusVal;
}

/**
 * @brief Disable SOSC
 *
 * @return SCG_StatusType Function status
 */
SCG_StatusType SCG_DisableSOSC(void)
{
    SCG_StatusType eStatusVal;
    uint32_t u32TempVal;

    /* Unlock CSR register first */
    SCG_HWA_UnlockSoscCsrReg();

    /* Disable SOSC */
    SCG_HWA_DisableSosc();

    /* Wait SOSC valid */
    u32TempVal = SOSC_STABILIZATION_TIMEOUT;
    SCG_CheckClockAckStatus((true == SCG_HWA_GetClockVliad(SCG_SOSC_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* Clear CSR register */
        SCG_HWA_SetSoscCsr(0U);
    }

    return eStatusVal;
}

/**
 * @brief Enable FOSC clock with input configuration
 *
 * @param pFoscConfig FOSC configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnableFOSC(const SCG_FoscType *const pFoscConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32TempVal,u32FoscFreq;
    uint8_t u8MSBVal;
    uint32_t u32DivHClockFreq = 0U;
    uint32_t u32DivMClockFreq = 0U;
    uint32_t u32DivLClockFreq = 0U;
    uint32_t u32FoscDivEn = 0U;

    DEV_ASSERT(NULL_PTR != pFoscConfig);

    /* Check DIV clock frequency is valid or not */
    if(pFoscConfig->eDivH != SCG_ASYNC_CLOCK_DISABLE)
    {
        u32DivHClockFreq = (uint32_t)FOSC_FREQUENCY >> ((uint32_t)pFoscConfig->eDivH - 1U);
        u32FoscDivEn |= (uint32_t)SCG_CLOCK_DIV_H;
    }
    if(pFoscConfig->eDivM != SCG_ASYNC_CLOCK_DISABLE)
    {
        u32DivMClockFreq = (uint32_t)FOSC_FREQUENCY >> ((uint32_t)pFoscConfig->eDivM - 1U);
        u32FoscDivEn |= (uint32_t)SCG_CLOCK_DIV_M;
    }
    if(pFoscConfig->eDivL != SCG_ASYNC_CLOCK_DISABLE)
    {
        u32DivLClockFreq = (uint32_t)FOSC_FREQUENCY >> ((uint32_t)pFoscConfig->eDivL - 1U);
        u32FoscDivEn |= (uint32_t)SCG_CLOCK_DIV_L;
    }

    if ((u32DivHClockFreq > FOSC_DIVH_MAX_CLOCK) || (u32DivMClockFreq > FOSC_DIVM_MAX_CLOCK) || (u32DivLClockFreq > FOSC_DIVL_MAX_CLOCK))
    {
        eStatusVal = SCG_STATUS_PARAM_ERROR;
    }

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* Unlock CSR register */
        SCG_HWA_UnlockFoscCsrReg();

        /* COMP_EN is setting to 1  COMP_EN must be 1 when using an external crystal */
        /* Configure GM to the max value, GM_SEL: 15U */
        u32TempVal = SCG_FOSCCFG_BYPASS(pFoscConfig->bBypass) | SCG_FOSCCFG_COMP_EN(!pFoscConfig->bBypass) |
                     SCG_FOSCCFG_EOCV(50U) | SCG_FOSCCFG_GM_SEL(15U) |
                     SCG_FOSCCFG_ALC_D(1U) | SCG_FOSCCFG_HYST_D(0U);
        SCG_HWA_SetFoscCfg(u32TempVal);

        /* Configure CSR register */
        u32TempVal = SCG_HWA_GetFoscCsr();
        u32TempVal &= ~(uint32_t)(SCG_FOSCCSR_STEN_MASK | SCG_FOSCCSR_CM_MASK | SCG_FOSCCSR_CMRE_MASK);
        u32TempVal |= SCG_FOSCCSR_STEN(pFoscConfig->bSten);
        SCG_HWA_SetFoscCsr(u32TempVal);

        /* Configure DIV value */
        SCG_HWA_DiableFoscDiv(SCG_CLOCK_DIV_ALL);
        u32TempVal = SCG_HWA_GetClockDiv(SCG_FOSC_CLOCK_SYMBOL);
        u32TempVal &= ~(uint32_t)(SCG_FOSCDIV_DIVL_MASK | SCG_FOSCDIV_DIVM_MASK | SCG_FOSCDIV_DIVH_MASK);
        u32TempVal |= (SCG_FOSCDIV_DIVH(pFoscConfig->eDivH) | SCG_FOSCDIV_DIVM(pFoscConfig->eDivM) | SCG_FOSCDIV_DIVL(
                           pFoscConfig->eDivL));
        SCG_HWA_SetFoscDiv(u32TempVal) ;

        /* Enable FOSC */
        SCG_HWA_EnableFosc();

        /* Wait FOSC vaild */
        u32TempVal = FOSC_STABILIZATION_TIMEOUT;
        SCG_CheckClockAckStatus((false == SCG_HWA_GetClockVliad(SCG_FOSC_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            /* Enable DIV */
            SCG_HWA_EnableFoscDiv((SCG_DivEnableType)u32FoscDivEn);

            if (pFoscConfig->bCm)
            {
                SCG_HWA_EnableFoscClockMonitor();
            }

            if (pFoscConfig->bCmre)
            {
                SCG_HWA_EnableFoscClockMonitorReset();
            }

            if (pFoscConfig->bLock)
            {
                /* Lock FOSC CSR register */
                SCG_HWA_LockFoscCsrReg();
            }

            /* Wait DIV[ACK] change to 1 */
            u32TempVal = CLOCK_DIV_STABILIZATION_TIMEOUT;
            SCG_CheckClockAckStatus((SCG_HWA_GetFoscDivAck((SCG_DivEnableType)u32FoscDivEn) != true), u32TempVal, eStatusVal)

            /* if OSC >= 40M ,set 5, if OSC = 32M,set 10, if OSC = 24M, set 15, if OSC = 16M, set 20, if OSC = 8M, set 25*/
            /* This is the protection measure during low power wake up, if SCG register not valid after the setting time, the chip will reset
             * and will set clock error flag in RGM register */
            u32FoscFreq = FOSC_FREQUENCY;
            u8MSBVal = ((u32FoscFreq / 8000000U) >= 5U) ? (uint8_t)5U : (uint8_t)((6U - (FOSC_FREQUENCY / 8000000U)) * 5U);
            SCG_HWA_SetWKPWDG(u8MSBVal);
        }
        else
        {
            /* Clear CSR configuration */
            SCG_HWA_SetFoscCsr(0U);

            /* Clear CFG configuration*/
            SCG_HWA_SetFoscCfg(0U);

            /* Clear DIV configuration*/
            SCG_HWA_SetFoscDiv(0U);
        }
    }
    return eStatusVal;
}

/**
 * @brief Disable FOSC
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisableFOSC(void)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32TempVal;
    uint8_t u8ClkSrc;

    u8ClkSrc = SCG_HWA_GetSysClkSrc();
    if ((uint8_t)SCG_CLOCK_SRC_FOSC == u8ClkSrc)
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }
    else if ((SCG_HWA_GetPllSrc(SCG_PLL0_CLOCK_SYMBOL) == (uint8_t)SCG_PLLSOURCE_FOSC) && ((uint8_t)SCG_CLOCK_SRC_PLL0 == u8ClkSrc))
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }
    else
    {
        /* do nothing */
    }

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* Unlock CSR register */
        SCG_HWA_UnlockFoscCsrReg();

        /* Clear FOSC[EN] bit */
        SCG_HWA_DisableFosc();

        u32TempVal = CLOCK_OFF_STABILIZATION_TIMEOUT;
        SCG_CheckClockAckStatus((true == SCG_HWA_GetClockVliad(SCG_FOSC_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            /* Clear CSR register */
            SCG_HWA_SetFoscCsr(0U);

            /* In order to avoid the DIV register value not cleared, Clear FOSC DIV register twice */
            SCG_HWA_SetFoscDiv(0U);
            SCG_HWA_SetFoscDiv(0U);
        }
    }

    return eStatusVal;
}

/**
 * @brief Set SIRC configuration and configure SIRC DIV
 *
 * @param pSircConfig SIRC configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_SetSIRC(const SCG_SircType *const pSircConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32TempVal;
    uint32_t u32SircDivEn = 0U;
    uint16_t u16TrimDiv = 0U;

    DEV_ASSERT(NULL_PTR != pSircConfig);
    DEV_ASSERT(pSircConfig->eDivH <= (uint32_t)SCG_ASYNCCLOCKDIV_BY64);
    DEV_ASSERT(pSircConfig->eDivM <= (uint32_t)SCG_ASYNCCLOCKDIV_BY64);
    DEV_ASSERT(pSircConfig->eDivL <= (uint32_t)SCG_ASYNCCLOCKDIV_BY64);

    /* Unlock SIRC CSR register */
    SCG_HWA_UnlockSircCsrReg();

    /* Configure CSR register */
    u32TempVal = SCG_HWA_GetSircCsr();
    u32TempVal &= ~(uint32_t)(SCG_SIRCCSR_STEN_MASK | SCG_SIRCCSR_LPEN_MASK | SCG_SIRCCSR_TREN_MASK | SCG_SIRCCSR_TRUP_MASK | SCG_SIRCCSR_CM_MASK);
    u32TempVal |= (uint32_t)(SCG_SIRCCSR_TRUP(pSircConfig->bTrEn) | SCG_SIRCCSR_TREN(pSircConfig->bTrEn) | SCG_SIRCCSR_LPEN(pSircConfig->bLpen) | SCG_SIRCCSR_STEN(pSircConfig->bSten));
    SCG_HWA_SetSircCsr(u32TempVal);

    /* Disable SIRC DIV[EN] bit */
    SCG_HWA_DiableSircDiv(SCG_CLOCK_DIV_ALL);

    if (pSircConfig->bCm)
    {
        SCG_HWA_EnableSircClockMonitor();
    }

    if (pSircConfig->bLock)
    {
        /* lock CSR */
        SCG_HWA_LockSircCsrReg();
    }

    /* Configure SIRC DIV */
    u32TempVal = SCG_HWA_GetClockDiv(SCG_SIRC_CLOCK_SYMBOL);
    u32TempVal &= ~(uint32_t)(SCG_SIRCDIV_DIVL_MASK | SCG_SIRCDIV_DIVM_MASK | SCG_SIRCDIV_DIVH_MASK);
    u32TempVal |= (uint32_t)(SCG_SIRCDIV_DIVL(pSircConfig->eDivL) | SCG_SIRCDIV_DIVM(pSircConfig->eDivM) | SCG_SIRCDIV_DIVH(
                                 pSircConfig->eDivH));
    SCG_HWA_SetSircDiv(u32TempVal);

    /* Enable SIRC DIV */
    u32SircDivEn |= (pSircConfig->eDivH != SCG_ASYNC_CLOCK_DISABLE) ? (uint32_t)SCG_CLOCK_DIV_H : 0U;
    u32SircDivEn |= (pSircConfig->eDivM != SCG_ASYNC_CLOCK_DISABLE) ? (uint32_t)SCG_CLOCK_DIV_M : 0U;
    u32SircDivEn |= (pSircConfig->eDivL != SCG_ASYNC_CLOCK_DISABLE) ? (uint32_t)SCG_CLOCK_DIV_L : 0U;
    SCG_HWA_EnableSircDiv((SCG_DivEnableType)u32SircDivEn);
    u32TempVal = CLOCK_DIV_STABILIZATION_TIMEOUT;
    SCG_CheckClockAckStatus((SCG_HWA_GetSircDivAck((SCG_DivEnableType)u32SircDivEn) != true), u32TempVal, eStatusVal)

    if (SCG_STATUS_SUCCESS != eStatusVal)
    {
        /* Clear SIRC DIV register */
        SCG_HWA_SetSircDiv(0U);
    }

    /* Set SIRCTCFG register */
    if (pSircConfig->bTrEn == true)
    {
        /*   set SIRCTCFG trim configuration    */
        if (pSircConfig->u8TrimSrc == (uint8_t)SCG_IRC_TRIMSRC_FOSC)
        {
            /*   Trim clock source choose FOSC   */
            u16TrimDiv = (uint16_t)(FOSC_FREQUENCY / 250000U - 1U);
        }
        else if (pSircConfig->u8TrimSrc == (uint8_t)SCG_IRC_TRIMSRC_SOSC)
        {
            /*   Trim clock source choose SOSC   */
            u16TrimDiv = 0U;
        }
        else
        {
            /* Do nothing */
        }
        u32TempVal = (uint32_t)(SCG_SIRCTCFG_TRIMSRC(pSircConfig->u8TrimSrc) | SCG_SIRCTCFG_TRIMDIV(u16TrimDiv));
        SCG_HWA_SetSircTcfg(u32TempVal);
    }

    return eStatusVal;
}

/**
 * @brief Disable SIRC DIV and clear DIV configuration
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_ClearSIRC(void)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;

    /* check SIRC is invalid, if invalid, do not configure SIRC */
    if (true != SCG_HWA_GetClockVliad(SCG_SIRC_CLOCK_SYMBOL))
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* Unlock SIRC CSR register */
        SCG_HWA_UnlockSircCsrReg();

        /* Disable SIRC DIV[EN] bit */
        SCG_HWA_DiableSircDiv(SCG_CLOCK_DIV_ALL);

        /* Clear SIRC DIV register */
        SCG_HWA_SetSircDiv(0U);
    }

    return eStatusVal;
}

/**
 * @brief Enable SIRC32K
 *
 * @param pSirc32kConfig SIRC32K configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnableSIRC32K(const SCG_Sirc32kType *const pSirc32kConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32TempVal;

    DEV_ASSERT(NULL_PTR != pSirc32kConfig);

    /* Unlock SIRC32K CSR register */
    SCG_HWA_UnlockSirc32kCsrReg();

    /* Enable SIRC32K */
    SCG_HWA_EnableSirc32kCsr();

    /* Wait SIRC32K valid */
    u32TempVal = SIRC_STABILIZATION_TIMEOUT;
    SCG_CheckClockAckStatus((false == SCG_HWA_GetClockVliad(SCG_SIRC32K_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        if (pSirc32kConfig->bLock)
        {
            /* Lock SIRC32K CSR register */
            SCG_HWA_LockSirc32kCsrReg();
        }
    }

    return eStatusVal;
}

/**
 * @brief Disable SIRC32K
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisableSIRC32K(void)
{
    SCG_StatusType eStatusVal;
    uint32_t u32TempVal;

    /* Unlock SIRC32K CSR register */
    SCG_HWA_UnlockSirc32kCsrReg();

    /* Disable SIRC32K */
    SCG_HWA_DisableSirc32kCsr();

    /* Wait SIRC32K not valid */
    u32TempVal = SIRC_STABILIZATION_TIMEOUT;
    SCG_CheckClockAckStatus((true == SCG_HWA_GetClockVliad(SCG_SIRC32K_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

    return eStatusVal;
}

/**
 * @brief Enable FIRC
 *
 * @param pFircConfig FIRC configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnableFIRC(const SCG_FircType *const pFircConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32TempVal, u32DivLClockFreq = 0U;
    uint32_t u32FircDivEn = 0U;
    uint16_t u16TrimDiv = 0U;

    DEV_ASSERT(NULL_PTR != pFircConfig);
    DEV_ASSERT(pFircConfig->eDivH <= (uint32_t)SCG_ASYNCCLOCKDIV_BY64);
    DEV_ASSERT(pFircConfig->eDivM <= (uint32_t)SCG_ASYNCCLOCKDIV_BY64);
    DEV_ASSERT(pFircConfig->eDivL <= (uint32_t)SCG_ASYNCCLOCKDIV_BY64);

    /* Check DIV clock frequency is valid or not */
    if(pFircConfig->eDivL != SCG_ASYNC_CLOCK_DISABLE)
    {
        u32DivLClockFreq = (uint32_t)(FIRC_CLOCK >> (pFircConfig->eDivL - 1));
        u32FircDivEn |= (uint32_t)SCG_CLOCK_DIV_L;
    }
    if (u32DivLClockFreq > FIRC_DIVL_MAX_CLOCK)
    {
        eStatusVal = SCG_STATUS_PARAM_ERROR;
    }

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* Unlock CSR register */
        SCG_HWA_UnlockFircCsrReg();

        /* Configure recommend value */
        SCG_HWA_SetFircCfg(SCG_FIRCCFG_CLKEN(3U));

        /* Configure CSR register */
        u32TempVal = SCG_HWA_GetFircCsr();
        u32TempVal &= ~(uint32_t)(SCG_FIRCCSR_STEN_MASK | SCG_FIRCCSR_TREN_MASK | SCG_FIRCCSR_TRUP_MASK | SCG_FIRCCSR_CM_MASK);
        u32TempVal |= (uint32_t)(SCG_FIRCCSR_TRUP(pFircConfig->bTrEn) |    /*    configure TRUP and EN together with TREN setting   */
                                 SCG_FIRCCSR_TREN(pFircConfig->bTrEn) |
                                 SCG_FIRCCSR_STEN(pFircConfig->bSten));
        SCG_HWA_SetFircCsr(u32TempVal);

        /* Configure DIV value */
        SCG_HWA_DiableFircDiv(SCG_CLOCK_DIV_ALL);
        u32TempVal = SCG_HWA_GetClockDiv(SCG_FIRC_CLOCK_SYMBOL);
        u32TempVal &= ~(uint32_t)(SCG_FIRCDIV_DIVL_MASK | SCG_FIRCDIV_DIVM_MASK | SCG_FIRCDIV_DIVH_MASK);
        u32TempVal |= (SCG_FIRCDIV_DIVH(pFircConfig->eDivH) | SCG_FIRCDIV_DIVM(pFircConfig->eDivM) | SCG_FIRCDIV_DIVL(
                           pFircConfig->eDivL));
        SCG_HWA_SetFircDiv(u32TempVal) ;

        /* Set CSR[EN] bit to 1 */
        SCG_HWA_EnableFirc();

        /* Wait FIRC valid */
        u32TempVal = FIRC_STABILIZATION_TIMEOUT;
        SCG_CheckClockAckStatus((false == SCG_HWA_GetClockVliad(SCG_FIRC_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            if (pFircConfig->bCm)
            {
                SCG_HWA_EnableFircClockMonitor();
            }

            if (pFircConfig->bLock)
            {
                /* lock CSR register */
                SCG_HWA_LockFircCsrReg();
            }

            /* Enable DIV */
            u32FircDivEn |= (pFircConfig->eDivH != SCG_ASYNC_CLOCK_DISABLE) ? (uint32_t)SCG_CLOCK_DIV_H : 0U;
            u32FircDivEn |= (pFircConfig->eDivM != SCG_ASYNC_CLOCK_DISABLE) ? (uint32_t)SCG_CLOCK_DIV_M : 0U;
            SCG_HWA_EnableFircDiv((SCG_DivEnableType)u32FircDivEn);

            /* Wait DIV[ACK] change to 1 */
            u32TempVal = CLOCK_DIV_STABILIZATION_TIMEOUT;
            SCG_CheckClockAckStatus((SCG_HWA_GetSircDivAck((SCG_DivEnableType)u32FircDivEn) != true), u32TempVal, eStatusVal)

            /*   For clock auto trim, set TREN to True together with TRUP to True   */
            if (pFircConfig->bTrEn == true)
            {
                /*   set FIRCTCFG trim configuration    */
                if (pFircConfig->u8TrimSrc == (uint8_t)SCG_IRC_TRIMSRC_FOSC)
                {
                    /*   Trim clock source choose FOSC   */
                    u16TrimDiv = (uint16_t)(FOSC_FREQUENCY / 250000U - 1U);
                }
                else if (pFircConfig->u8TrimSrc == (uint8_t)SCG_IRC_TRIMSRC_SOSC)
                {
                    /*   Trim clock source choose SOSC   */
                    u16TrimDiv = 0U;
                }
                else
                {
                    /*   do nothing   */
                }
                u32TempVal = (uint32_t)(SCG_FIRCTCFG_TRIMSRC(pFircConfig->u8TrimSrc) | SCG_FIRCTCFG_TRIMDIV(u16TrimDiv));
                SCG_HWA_SetFircTcfg(u32TempVal);
            }
            else
            {
                /*   Trim disabled, just using IC internal IRC trim value */
            }

        }
        else
        {
            /* Clear CSR configuration */
            SCG_HWA_SetFircCsr(0U);

            /* Clear DIV configuration*/
            SCG_HWA_SetFircDiv(0U);
        }
    }
    return eStatusVal;
}

/**
 * @brief Disable FIRC
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisableFIRC(void)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32TempVal;
    uint8_t u8ClkSrc;

    u8ClkSrc = SCG_HWA_GetSysClkSrc();
    if ((uint8_t)SCG_CLOCK_SRC_FIRC == u8ClkSrc)
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }
    else if ((SCG_HWA_GetPllSrc(SCG_PLL0_CLOCK_SYMBOL) == (uint8_t)SCG_PLLSOURCE_FIRC) && ((uint8_t)SCG_CLOCK_SRC_PLL0 == u8ClkSrc))
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }
    else
    {
        /* do nothing */
    }

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* Unlock CSR register */
        SCG_HWA_UnlockFircCsrReg();

        /* Disable FIRC */
        SCG_HWA_DisableFirc();

        /* Wait FIRC not valid */
        u32TempVal = FIRC_STABILIZATION_TIMEOUT;
        SCG_CheckClockAckStatus((true == SCG_HWA_GetClockVliad(SCG_FIRC_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            /* Clear CSR register */
            SCG_HWA_SetFircCsr(0U);

            /* In order to avoid the DIV register value not cleared, Clear FIRC DIV register twice */
            SCG_HWA_SetFircDiv(0U);
            SCG_HWA_SetFircDiv(0U);
        }
    }
    return eStatusVal;
}


/**
 * @brief Enable PLL
 *
 * @param ePLL PLL instance
 * @param pPllConfig PLL configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnablePLL(const SCG_PllClkType ePll, const SCG_PllType *const pPllConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;

    DEV_ASSERT(NULL_PTR != pPllConfig);
    DEV_ASSERT(((ePll == SCG_PLL0) || (ePll == SCG_PLL1)));
    DEV_ASSERT(((pPllConfig->eSrc == SCG_PLLSOURCE_FOSC) || (pPllConfig->eSrc == SCG_PLLSOURCE_FIRC)));
    DEV_ASSERT((pPllConfig->u16Mult > 95U) && (pPllConfig->u16Mult < 512U));
    DEV_ASSERT(pPllConfig->u8Prediv < 32U);
    DEV_ASSERT(pPllConfig->u8Prediv != 2U);
    DEV_ASSERT((pPllConfig->ePstDiv == SCG_PLLPSTDIV_BY2) ||
               (pPllConfig->ePstDiv == SCG_PLLPSTDIV_BY4) ||
               (pPllConfig->ePstDiv == SCG_PLLPSTDIV_BY8));
    DEV_ASSERT(pPllConfig->eDivH <= (uint32_t)SCG_ASYNCCLOCKDIV_BY64);
    DEV_ASSERT(pPllConfig->eDivM <= (uint32_t)SCG_ASYNCCLOCKDIV_BY64);
    DEV_ASSERT(pPllConfig->eDivL <= (uint32_t)SCG_ASYNCCLOCKDIV_BY64);


    if ((true != SCG_HWA_GetClockVliad(SCG_FOSC_CLOCK_SYMBOL)) && (SCG_PLLSOURCE_FOSC == pPllConfig->eSrc))
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }
    else if ((true != SCG_HWA_GetClockVliad(SCG_FIRC_CLOCK_SYMBOL)) && (SCG_PLLSOURCE_FIRC == pPllConfig->eSrc))
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }
    else
    {
        /* do nothing */
    }

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        if (SCG_PLL0 == ePll)
        {
            eStatusVal = SCG_EnablePLL0(pPllConfig);
        }
        else if (SCG_PLL1 == ePll)
        {
            eStatusVal = SCG_EnablePLL1(pPllConfig);
        }
        else
        {
            /* do nothing */
        }
    }

    return eStatusVal;
}

/**
 * @brief Disable PLL
 *
 * @param ePll PLL instance
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisablePLL(const SCG_PllClkType ePll)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;

    if (SCG_PLL0 == ePll)
    {
        if (SCG_HWA_GetSysClkSrc() == (uint8_t)SCG_CLOCK_SRC_PLL0)
        {
            eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
        }
        else
        {
            eStatusVal = SCG_DisablePLL0();
        }
    }
    else
    {
        /* (SCG_PLL1 == ePll) */
        eStatusVal = SCG_DisablePLL1();
    }

    return eStatusVal;
}

/**
 * @brief Set system run time clock and related CORE/BUS/SLOW clock.
 *
 * @param pSysClkConfig pointer to the clockCtrlType structure data instance,which defined for system clock selection.
 * @return SCG_StatusType function status
 *           SCG_STATUS_SUCCESS : clock source and dividers are valid,and switch system clock successfully
 *         SCG_STATUS_SEQUENCE_ERROR: new clock source is not enabled
 *         SCG_STATUS_PARAM_ERROR: the core bus slow divider are invalid
 *         SCG_STATUS_TIMEOUT: switch system clock procedure time out
 */
SCG_StatusType SCG_SetClkCtrl(const SCG_ClockCtrlType *const pSysClkConfig)
{
    DEV_ASSERT(NULL_PTR != pSysClkConfig);

    return SCG_SwitchSystemClockWithConfig(pSysClkConfig->eSrc,pSysClkConfig);
}

/**
 * @brief Get clock frequency
 *
 * @param eScgClockName Clock source type
 * @return uint32_t frequency value
 */
uint32_t SCG_GetScgClockFreq(const SCG_ClkSrcType eScgClockName)
{
    uint32_t u32Freq;
    DEV_ASSERT(eScgClockName < SCG_END_OF_CLOCKS);

    if ((SCG_CORE_CLK == eScgClockName) ||
            (SCG_BUS_CLK == eScgClockName) ||
            (SCG_SLOW_CLK == eScgClockName))
    {
        u32Freq = SCG_CalculateSystemFreq(eScgClockName);
    }
    else if ((SCG_SIRC_CLK == eScgClockName) ||
             (SCG_SIRCDIVH_CLK == eScgClockName) ||
             (SCG_SIRCDIVM_CLK == eScgClockName) ||
             (SCG_SIRCDIVL_CLK == eScgClockName))
    {
        u32Freq = SCG_CalculateSircFreq(eScgClockName);
    }
    else if ((SCG_FIRC_CLK == eScgClockName) ||
             (SCG_FIRCDIVH_CLK == eScgClockName) ||
             (SCG_FIRCDIVM_CLK == eScgClockName) ||
             (SCG_FIRCDIVL_CLK == eScgClockName))
    {
        u32Freq = SCG_CalculateFircFreq(eScgClockName);
    }
    else if ((SCG_FOSC_CLK == eScgClockName) ||
             (SCG_FOSCDIVH_CLK == eScgClockName) ||
             (SCG_FOSCDIVM_CLK == eScgClockName) ||
             (SCG_FOSCDIVL_CLK == eScgClockName))
    {
        u32Freq = SCG_CalculateFoscFreq(eScgClockName);
    }
    else if ((SCG_PLL0_CLK == eScgClockName) ||
             (SCG_PLL0DIVH_CLK == eScgClockName) ||
             (SCG_PLL0DIVM_CLK == eScgClockName) ||
             (SCG_PLL0DIVL_CLK == eScgClockName))
    {
        u32Freq = SCG_CalculatePll0Freq(eScgClockName);
    }
    else if ((SCG_PLL1_CLK == eScgClockName) ||
             (SCG_PLL1DIVH_CLK == eScgClockName) ||
             (SCG_PLL1DIVM_CLK == eScgClockName) ||
             (SCG_PLL1DIVL_CLK == eScgClockName))
    {
        u32Freq = SCG_CalculatePll1Freq(eScgClockName);
    }
    else if (SCG_SIRC32K_CLK == eScgClockName)
    {
        u32Freq = SIRC32K_CLOCK;
    }
    else if (SCG_SOSC_CLK == eScgClockName)
    {
        u32Freq = SOSC_FREQUENCY;
    }
    else if (SCG_SCG_CLKOUT_CLK == eScgClockName)
    {
        u32Freq = SCG_CalculateClkOutFreq();
    }
    else if(SCG_NVMINIT_CLK == eScgClockName)
    {
        u32Freq = NVM_CLOCK;
    }
    else if(SCG_CMU4REF_CLK == eScgClockName)
    {
        u32Freq = SCG_CalculateCMU4RefFreq();
    }
    else
    {
        u32Freq = UNKNOWN_CLOCK;
    }

    if (UNKNOWN_CLOCK == u32Freq)
    {
        u32Freq = 0U;
    }

    return u32Freq;
}

/**
 * @brief Select clock out source
 *
 * @param eClkoutSel clock out source
 */
void SCG_SetClkOut(const SCG_ClockoutSrcType eClkoutSel)
{
    DEV_ASSERT(eClkoutSel <= SCG_CLOCKOUT_SRC_SIRC32K);

    SCG_HWA_SetClkOutSel((uint8_t)eClkoutSel);
}

/**
 * @brief Select NVM clock source
 *
 * @param eNvmClkSrc NVM clock source
 * @return uint32_t function status
 */
SCG_StatusType SCG_SetNvmClk(const SCG_NvmClkSrcType eNvmClkSrc)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    DEV_ASSERT((eNvmClkSrc == SCG_NVMCLK_SRC_SIRC) || (eNvmClkSrc == SCG_NVMCLK_SRC_FIRC));

    if ((true != SCG_HWA_GetClockVliad(SCG_FIRC_CLOCK_SYMBOL)) && (eNvmClkSrc == SCG_NVMCLK_SRC_FIRC))
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        SCG_HWA_SetNvmClk(((uint32_t)1U << eNvmClkSrc));
    }

    return eStatusVal;
}

/**
 * @brief Select CMU4 clock source
 *
 * @param eCmu4ClkSrc CMU4 clock source
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_SetCmu4Clk(const SCG_Cmu4ClkSrcType eCmu4ClkSrc)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    DEV_ASSERT((eCmu4ClkSrc == SCG_CMU4CLK_SRC_SIRC) || (eCmu4ClkSrc == SCG_CMU4CLK_SRC_FOSC));

    if ((true != SCG_HWA_GetClockVliad(SCG_FOSC_CLOCK_SYMBOL)) && (eCmu4ClkSrc == SCG_CMU4CLK_SRC_FOSC))
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        SCG_HWA_SetCmu4Clk(((uint32_t)1U << eCmu4ClkSrc));
    }
    return eStatusVal;
}

/**
 * @brief Generate the origion SCG register CRC result, and configure the SCG register CRC option.
 *
 * @param eMode The SCG register CRC trigger mode
 * @return CRC configure status
 *  SCG_STATUS_SUCCESS : CRC configure successfully
 *  SCG_STATUS_TIMEOUT : CRC configure time out
 */
SCG_StatusType SCG_RegCrcConfig(SCG_CrcModeType eMode)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32Timeout = 0xFFFFU;

    DEV_ASSERT((eMode == SCG_CRC_SW_MODE) || (eMode == SCG_CRC_TRIGGER_MODE));

    /* Deinit CRC register */
    SCG_HWA_DisableCrcCheck();
    SCG_HWA_DisableCrcTriggerMode();
    SCG_HWA_DisableCrcErrorOutput();
    SCG_HWA_ClearCrcErrorFlag();

    /* Generate original CRC result */
    SCG_HWA_GenCrcVal();
    while (SCG_HWA_GetCrcBusyStatus() == true)
    {
        u32Timeout--;
        if (u32Timeout == 0U)
        {
            eStatusVal = SCG_STATUS_TIMEOUT;
            break;
        }
    }

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        if (eMode == SCG_CRC_TRIGGER_MODE)
        {
            SCG_HWA_EnableCrcTriggerMode();
        }

        /* Enable SCG CRC error to FCSMU in CSC0_SMU_CTRL4[SCG_CRC] */
        CSC0_HWA_CTRL4_EnableReqToSMU(CSC_SMU_SCG_CRC);
        /* Generate CRC error output */
        SCG_HWA_EnableCrcErrorOutput();
        /* Generate CRC check */
        SCG_HWA_EnableCrcCheck();
    }
    return eStatusVal;
}

/**
 * @brief Trigger the SCG register CRC generation by software
 *
 */
void SCG_RegCrcGenerate(void)
{
    SCG_HWA_GenCrcVal();
}

/**
 * @brief Trigger the SCG register CRC generation by software,and wait the CRC check result
 *
 * @return CRC check result
 */
SCG_CrcCheckResType SCG_RegCrcGenerateWaitResult(void)
{
    SCG_CrcCheckResType eStatusVal = SCG_CRC_CHECK_SUCCESS;
    uint32_t u32Timeout = 0xFFFFU;

    SCG_HWA_GenCrcVal();
    while (SCG_HWA_GetCrcBusyStatus() == true)
    {
        u32Timeout--;
        if (u32Timeout == 0U)
        {
            eStatusVal = SCG_CRC_GEN_TIMEOUT;
            break;
        }
    }

    /* Check CRC is success or not */
    if (SCG_HWA_GetCrcErrorStatus())
    {
        eStatusVal = SCG_CRC_CHECK_FAILED;
    }

    return eStatusVal;
}

/**
 * @brief Clock source De-init
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_Deinit(void)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    SCG_FircType tFircCfg =
    {
        .bLock = false,
        .bCm = false,
        .bTrEn = false,
        .bSten = false,
        .u8TrimSrc = 0U,
        .eDivL = SCG_ASYNCCLOCKDIV_BY4,
        .eDivM = SCG_ASYNCCLOCKDIV_BY2,
        .eDivH = SCG_ASYNCCLOCKDIV_BY1
    };

    if (SCG_HWA_GetSysClkSrc() != (uint8_t)SCG_CLOCK_SRC_FIRC)
    {
        eStatusVal = SCG_SwitchSystemClockWithConfig(SCG_CLOCK_SRC_FIRC,NULL_PTR);
        if (SCG_STATUS_SEQUENCE_ERROR == eStatusVal)
        {
            eStatusVal = SCG_EnableFIRC(&tFircCfg);
            if (SCG_STATUS_TIMEOUT != eStatusVal)
            {
                eStatusVal = SCG_SwitchSystemClockWithConfig(SCG_CLOCK_SRC_FIRC,NULL_PTR);
            }
        }
    }

    if (SCG_STATUS_SUCCESS == eStatusVal)
    {
        /* Disable all clock source */
        (void)SCG_DisablePLL(SCG_PLL1);
        (void)SCG_DisablePLL(SCG_PLL0);
        (void)SCG_DisableFOSC();
        (void)SCG_DisableSOSC();
        (void)SCG_DisableSIRC32K();
    }

    return eStatusVal;
}

