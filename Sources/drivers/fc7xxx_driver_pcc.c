/**
 * @file fc7xxx_driver_pcc.c
 * @author Flagchip
 * @brief FC7xxx PCC driver type definition and API
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

#include "fc7xxx_driver_pcc.h"
#include "fc7xxx_driver_scg.h"
#include "fc7xxx_board_conf.h"

/***************** mcaro *********************/
/* PCC property MACRO, defines every peripheral clock system architecture */
#define PCC_CLK_NOT_APPLY               (0U)
#define PCC_CGC_AVAILABLE               (1U << 0U)
#define PCC_FUNCCLK_MUXDIVH_USED        (1U << 1U)
#define PCC_FUNCCLK_MUXDIVM_USED        (1U << 2U)
#define PCC_FUNCCLK_MUXDIVL_USED        (1U << 3U)
#define PCC_FUNCCLK_MUXDIVHPIN_USED     (1U << 4U)
#define PCC_MOUDULE_DIV_USED            (1U << 5U)
#define PCC_CLK_DOMAIN_CORE             (1U << 6U)
#define PCC_CLK_DOMAIN_BUS              (1U << 7U)
#define PCC_CLK_DOMAIN_SLOW             (1U << 8U)
#define PCC_DWP_SWR_AVAILABLE			(0U << 9U)

#define PCC_PROPERTY_MUXDIV_MASK           (PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVM_USED | PCC_FUNCCLK_MUXDIVL_USED)
#define PCC_PROPERTY_MUXDIV_ALL_MASK       (PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVM_USED | PCC_FUNCCLK_MUXDIVL_USED | PCC_FUNCCLK_MUXDIVHPIN_USED)

/***************** Type define *********************/
/**
 * @brief PCC clock attribution.
 * @param u32RegOffset: the register offset base on PCC module base address 0x4002_4000h
 * @param u8ClockProperty include clock domain and clock MUX information by bit filed setting.
 */
typedef struct
{
    uint32_t u32RegOffset;
    uint32_t u32ClockProperty;
} PCC_ClockMapType;

/**
 * @brief PCC peripheral clock index map to SCG clock source
 * @param ePccClkIndex: PCC peripheral clock index
 * @param eScgClkIndex SCG clock source
 */
typedef struct
{
    PCC_ClkGateSrcType ePccClkIndex;
    SCG_ClkSrcType eScgClkIndex;
} PCC_ClockIndexMap;

/***************** Local Variables *********************/
/**
 * @brief PCC clock index to SCG clock source map.
*/
static const PCC_ClockIndexMap s_tPccClocIndexkMap[PCC_MUX_MAX_NUMBER] = {
    {PCC_CLKGATE_SRC_OFF_OR_TCLK, SCG_END_OF_CLOCKS},
    {PCC_CLKGATE_SRC_FOSCDIV, SCG_FOSCDIVH_CLK},
    {PCC_CLKGATE_SRC_SIRCDIV, SCG_SIRCDIVH_CLK},
    {PCC_CLKGATE_SRC_FIRCDIV, SCG_FIRCDIVH_CLK},
    {PCC_CLKGATE_SRC_RESERVE0, SCG_END_OF_CLOCKS},
    {PCC_CLKGATE_SRC_PLL1DIV, SCG_PLL1DIVH_CLK},
    {PCC_CLKGATE_SRC_PLL0DIV, SCG_PLL0DIVH_CLK},
    {PCC_CLKGATE_SRC_RESERVE1, SCG_END_OF_CLOCKS}
};

/**
 * @brief clock attribution map.
 */
static const PCC_ClockMapType s_tPccClockMap[PCC_END_OF_CLOCKS] =
{
    {0x20, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_DWP_SWR_AVAILABLE},        /* DMA0 */
    {0x28, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_DWP_SWR_AVAILABLE},        /* DMAMUX0 */
    {0x4C, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_DWP_SWR_AVAILABLE},        /* ROMC */
    {0x60, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_DWP_SWR_AVAILABLE},        /* ERM0 */
    {0x64, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* EIM0 */
    {0x68, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* INTM0 */
    {0x6C, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_DWP_SWR_AVAILABLE},        /* ISM0 */
    {0x88, PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* WDOG0 */
    {0x98, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* TRGSEL0 */
    {0x9C, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* TRGSEL1 */
    {0xA0, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* TRGSEL2 */
    {0xA4, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* TRGSEL3 */
    {0xA8, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_DWP_SWR_AVAILABLE},        /* CRC0 */
    {0xAC, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_DWP_SWR_AVAILABLE},        /* CORDIC */
    {0xB0, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_DWP_SWR_AVAILABLE},        /* TSTMP0 */
    {0xB4, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_DWP_SWR_AVAILABLE},        /* TSTMP1 */
    {0xB8, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_DWP_SWR_AVAILABLE},        /* FCPIT0 */
    {0xBC, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_FUNCCLK_MUXDIVL_USED | PCC_MOUDULE_DIV_USED | PCC_DWP_SWR_AVAILABLE},        /* AONTIMER0 */
    {0xC0, PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* RTC */
    {0xC4, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* CMU0 */
    {0xC8, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* CMU1 */
    {0xCC, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* CMU2 */
    {0xD0, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* CMU3 */
    {0xD4, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* CMU4 */
    {0xDC, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_DWP_SWR_AVAILABLE},        /* PTIMER0 */
    {0xE0, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_DWP_SWR_AVAILABLE},        /* PTIMER1 */
    {0xEC, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_MOUDULE_DIV_USED | PCC_DWP_SWR_AVAILABLE},        /* ADC0 */
    {0xF0, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_MOUDULE_DIV_USED | PCC_DWP_SWR_AVAILABLE},        /* ADC1 */
    {0xFC, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* WKU0 */
    {0x100, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* CMP0 */
    {0x104, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* CMP1 */
    {0x10C, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_FUNCCLK_MUXDIVL_USED | PCC_DWP_SWR_AVAILABLE},        /* TMU0 */
    {0x150, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVL_USED | PCC_MOUDULE_DIV_USED | PCC_DWP_SWR_AVAILABLE},        /* SENT0 */
    {0x160, PCC_CLK_DOMAIN_BUS | PCC_DWP_SWR_AVAILABLE},        /* MB0 */
    {0x170, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED | PCC_DWP_SWR_AVAILABLE},        /* FTU0 */
    {0x174, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED | PCC_DWP_SWR_AVAILABLE},        /* FTU1 */
    {0x178, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED | PCC_DWP_SWR_AVAILABLE},        /* FTU2 */
    {0x17C, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED | PCC_DWP_SWR_AVAILABLE},        /* FTU3 */
    {0x188, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCSPI0 */
    {0x18C, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCSPI1 */
    {0x190, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCSPI2 */
    {0x198, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCIIC0 */
    {0x1A0, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCUART0 */
    {0x1A4, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCUART1 */
    {0x1A8, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCUART2 */
    {0x1AC, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCUART3 */
    {0x1C0, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* LU0 */
    {0x1E0, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_DWP_SWR_AVAILABLE},        /* FREQM */
    {0x1FC, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* STCU */
    {0x200, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_MOUDULE_DIV_USED | PCC_DWP_SWR_AVAILABLE},        /* FLEXCAN0 */
    {0x210, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_MOUDULE_DIV_USED | PCC_DWP_SWR_AVAILABLE},        /* FLEXCAN1 */
    {0x34C, PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* WDOG1 */
    {0x36C, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* TRGSEL4 */
    {0x370, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_SLOW | PCC_DWP_SWR_AVAILABLE},        /* TRGSEL5 */
	{0x37C, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCSPI3 */
    {0x380, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCSPI4 */
    {0x384, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCSPI5 */
    {0x3FC, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED | PCC_DWP_SWR_AVAILABLE},        /* FTU4 */
    {0x400, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED | PCC_DWP_SWR_AVAILABLE},        /* FTU5 */
    {0x404, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED | PCC_DWP_SWR_AVAILABLE},        /* FTU6 */
    {0x408, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED | PCC_DWP_SWR_AVAILABLE},        /* FTU7 */
	{0x41C, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCIIC1 */
    {0x420, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCUART4 */
    {0x424, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCUART5 */
    {0x428, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCUART6 */
    {0x42C, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_DWP_SWR_AVAILABLE},        /* FCUART7 */
    {0x450, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVM_USED | PCC_MOUDULE_DIV_USED | PCC_DWP_SWR_AVAILABLE},        /* MSC0 */
    {0x480, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_MOUDULE_DIV_USED | PCC_DWP_SWR_AVAILABLE},        /* FLEXCAN2 */
    {0x490, PCC_CGC_AVAILABLE | PCC_CLK_DOMAIN_BUS | PCC_FUNCCLK_MUXDIVH_USED | PCC_MOUDULE_DIV_USED | PCC_DWP_SWR_AVAILABLE},        /* FLEXCAN3 */
};

/***************** Local Prototype Functions *********************/

/***************** Local Functions *********************/

/***************** Global Functions *********************/

/**
 * @brief get PCC function clock status and value.
 *
 * @param pcc_ClkSrcType eClockName: used for choose PCC clock source to query.
 */
uint32_t PCC_GetPccFunctionClock(const PCC_ClkSrcType eClockName)
{
    uint32_t u32DivVal;
    PCC_ClkGateSrcType eSelVal;
    uint32_t u32ScgClkIndex = 0U;
    uint32_t u32FunctionFreqVal = 0U;
    uint32_t u32RegVal, u32ScgClkDivIndex;
    const PCC_ClockMapType *pAttributeVal;

    DEV_ASSERT((uint32_t)eClockName < (uint32_t)PCC_END_OF_CLOCKS);

    /* Get peripheral PCC register value */
    u32RegVal = PCC_HWA_GetRegister(s_tPccClockMap[(uint32_t)eClockName].u32RegOffset);
    pAttributeVal = &s_tPccClockMap[(uint32_t)eClockName];

    /* Check peripheral PCC is valid or not and peripheral have function clock or not */
    if ((PCC_CGC_MASK == (u32RegVal & PCC_CGC_MASK)) && (0U != (pAttributeVal->u32ClockProperty & PCC_PROPERTY_MUXDIV_ALL_MASK)))
    {
        eSelVal = (PCC_ClkGateSrcType)((uint8_t)PCC_GetSEL(u32RegVal));
        /* Get PCC divide value */
        if (PCC_MOUDULE_DIV_USED == (pAttributeVal->u32ClockProperty & PCC_MOUDULE_DIV_USED))
        {
            u32DivVal = PCC_GetDIV(u32RegVal) + (uint32_t)1U;
        }
        else
        {
            u32DivVal = 1U;
        }

        /* Get peripheral function clock source which is from SCG or TCLK */
        if (PCC_CLKGATE_SRC_OFF_OR_TCLK == eSelVal)
        {
            if (PCC_FUNCCLK_MUXDIVHPIN_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVHPIN_USED))
            {
                u32FunctionFreqVal = PCC_FTU_TCLK_FREQ;
            }
            else
            {
                u32FunctionFreqVal = 0U;
            }
        }
        else
        {
            if (PCC_FUNCCLK_MUXDIVH_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVH_USED))
            {
                u32ScgClkDivIndex = 0U;
            }
            else if (PCC_FUNCCLK_MUXDIVM_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVM_USED))
            {
                u32ScgClkDivIndex = 1U;
            }
            else if (PCC_FUNCCLK_MUXDIVL_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVL_USED))
            {
                u32ScgClkDivIndex = 2U;
            }
            else
            {
                u32ScgClkDivIndex = 0U;
            }
            u32ScgClkIndex = (uint32_t)s_tPccClocIndexkMap[eSelVal].eScgClkIndex + u32ScgClkDivIndex;
        }

        /* If clock source is valid, calculate peripheral function clock */
        if (u32ScgClkIndex < (uint32_t)SCG_END_OF_CLOCKS)
        {
            u32FunctionFreqVal = SCG_GetScgClockFreq((SCG_ClkSrcType)u32ScgClkIndex) / u32DivVal;
        }
    }

    return u32FunctionFreqVal;
}

/**
 * @brief get PCC interface clock status and value.
 *
 * @param pcc_ClkSrcType eClockName: used for choose PCC clock source to query.
 */
uint32_t PCC_GetPccInterfaceClock(const PCC_ClkSrcType eClockName)
{
    uint32_t u32InterfaceFreqVal, u32AttributeVal;

    DEV_ASSERT((uint32_t)eClockName < (uint32_t)PCC_END_OF_CLOCKS);

    u32AttributeVal = s_tPccClockMap[(uint32_t)eClockName].u32ClockProperty;
    if (PCC_CLK_DOMAIN_BUS == (u32AttributeVal & PCC_CLK_DOMAIN_BUS))
    {
        u32InterfaceFreqVal = SCG_GetScgClockFreq(SCG_BUS_CLK);
    }
    else if (PCC_CLK_DOMAIN_SLOW == (u32AttributeVal & PCC_CLK_DOMAIN_SLOW))
    {
        u32InterfaceFreqVal = SCG_GetScgClockFreq(SCG_SLOW_CLK);
    }
    else
    {
        u32InterfaceFreqVal = 0U;
    }

    return u32InterfaceFreqVal;
}


/**
 * @brief set PCC one peripheral clock configuration.
 *
 * @param PCC_CtrlType* pConfig: the PCC initialize value point set by user.
 * @return PCC_StatusType pcc function status
 */
PCC_StatusType PCC_SetPcc(const PCC_CtrlType *const pConfig)
{
    PCC_StatusType eStatus = PCC_STATUS_SUCCESS;
    uint32_t u32DivVal;
    uint32_t u32ScgClkIndex = 0U, u32ScgClkDivIndex;
    uint32_t u32FreqVal = 0U;
    uint32_t u32FunctionFreqVal = 0U;
    uint32_t u32RegVal = 0U;
    uint32_t u32ExpectedRegVal;
    const PCC_ClockMapType *pAttributeVal;

    DEV_ASSERT(NULL_PTR != pConfig);
    DEV_ASSERT((uint32_t)pConfig->eClockName < (uint32_t)PCC_END_OF_CLOCKS);

    pAttributeVal = &s_tPccClockMap[(uint32_t)pConfig->eClockName];
    /* check peripheral clock domain to calculate module clock */
    if (PCC_CLK_DOMAIN_BUS == (pAttributeVal->u32ClockProperty & PCC_CLK_DOMAIN_BUS))
    {
        u32FreqVal = SCG_GetScgClockFreq(SCG_BUS_CLK);
    }
    else if (PCC_CLK_DOMAIN_SLOW == (pAttributeVal->u32ClockProperty & PCC_CLK_DOMAIN_SLOW))
    {
        u32FreqVal = SCG_GetScgClockFreq(SCG_SLOW_CLK);
    }
    else
    {
        /* Do nothing */
    }

    if (0U == u32FreqVal)
    {
        /* Please call SCG function first */
        eStatus = PCC_STATUS_CLOCK_INVALID;
    }

    if (PCC_STATUS_SUCCESS == eStatus)
    {
        /* Disable PCC gate */
        PCC_HWA_SetClockGateControl(pAttributeVal->u32RegOffset,false);
        if (pConfig->bEn)
        {
            if (PCC_MOUDULE_DIV_USED == (pAttributeVal->u32ClockProperty & PCC_MOUDULE_DIV_USED))
            {
                u32DivVal = (uint32_t)pConfig->eDivider + (uint32_t)1U;
                u32RegVal |= PCC_DIV(pConfig->eDivider);
            }
            else
            {
                u32DivVal = 1U;
            }

            if (0U != (pAttributeVal->u32ClockProperty & PCC_PROPERTY_MUXDIV_ALL_MASK))
            {
                u32RegVal |= PCC_SEL(pConfig->eClkSrc);
            }

            if (PCC_CGC_AVAILABLE == (pAttributeVal->u32ClockProperty & PCC_CGC_AVAILABLE))
            {
                /* Enable peripheral clock */
                u32RegVal |= PCC_CGC_MASK;
            }

            /* Configure PCC register */
            PCC_HWA_SetRegister(pAttributeVal->u32RegOffset,u32RegVal);

            /* Get peripheral function clock source which is from SCG or TCLK */
            if (PCC_CLKGATE_SRC_OFF_OR_TCLK == pConfig->eClkSrc)
            {
                if (PCC_FUNCCLK_MUXDIVHPIN_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVHPIN_USED))
                {
                    u32FunctionFreqVal = PCC_FTU_TCLK_FREQ;
                }
                else
                {
                    u32FunctionFreqVal = 0U;
                }
            }
            else if (PCC_CLKGATE_UNINVOLVED == pConfig->eClkSrc)
            {
            	/* do nothing */
            }
            else
            {
                if (PCC_FUNCCLK_MUXDIVH_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVH_USED))
                {
                    u32ScgClkDivIndex = 0U;
                }
                else if (PCC_FUNCCLK_MUXDIVM_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVM_USED))
                {
                    u32ScgClkDivIndex = 1U;
                }
                else if (PCC_FUNCCLK_MUXDIVL_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVL_USED))
                {
                    u32ScgClkDivIndex = 2U;
                }
                else
                {
                    u32ScgClkDivIndex = 0U;
                }
                u32ScgClkIndex = (uint32_t)s_tPccClocIndexkMap[(uint32_t)pConfig->eClkSrc].eScgClkIndex + u32ScgClkDivIndex;
            }

            /* Calculate peripheral function clock */
            if (u32ScgClkIndex < (uint32_t)SCG_END_OF_CLOCKS)
            {
                u32FunctionFreqVal = SCG_GetScgClockFreq((SCG_ClkSrcType)u32ScgClkIndex) / u32DivVal;
            }
            u32ExpectedRegVal = u32RegVal;
        }
        else
        {
            /* Clear PCC register */
            PCC_HWA_SetRegister(pAttributeVal->u32RegOffset,0U);
            u32ExpectedRegVal = 0U;
            u32FunctionFreqVal = 0U;
        }

        /* Check PCC register has been configured, If current CPU do not have permission to configure the PCC register, the except value
         * will not match the actual value */
        if (u32ExpectedRegVal != PCC_HWA_GetRegister(pAttributeVal->u32RegOffset))
        {
            /* In this case, current core does not have permission to control the register */
            eStatus = PCC_STATUS_CONFIGURED_NOT_SUPPORT;
        }
        else if (u32FunctionFreqVal > 160000000U)
        {
            /* In this case, current function clock too high, must configured below 150M */
            eStatus = PCC_STATUS_CONFIGURED_NOT_SUPPORT;
        }
        else
        {
            /* do nothing */
        }
    }

    return eStatus;
}

/**
 * @brief Generate peripheral reset
 *
 */
void PCC_GenPeripheralReset(const PCC_ClkSrcType eClockName)
{
	DEV_ASSERT((uint32_t)eClockName < (uint32_t)PCC_END_OF_CLOCKS);
    PCC_HWA_SoftwareReset(s_tPccClockMap[(uint32_t)eClockName].u32RegOffset);
}


