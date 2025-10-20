/**
 * @file fc7xxx_driver_pcc.h
 * @author Flagchip085
 * @brief FC7xxx PCC driver type definition and API
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-12    Flagchip085   N/A          First version for FC7240
   ******************************************************************************** */
#ifndef _DRIVER_FC7XXX_DRIVER_PCC_H_
#define _DRIVER_FC7XXX_DRIVER_PCC_H_
#include "HWA_pcc.h"
/**
 * @addtogroup fc7xxx_driver_pcc
 * @{
 */


#define PCC_MUX_MAX_NUMBER                  8U

/** @brief PCC clock list */
typedef enum
{
    PCC_CLK_DMA0 = 0U,
    PCC_CLK_DMAMUX0,
    PCC_CLK_ROMC,
    PCC_CLK_ERM0,
    PCC_CLK_EIM0,
    PCC_CLK_INTM0,
    PCC_CLK_ISM0,
    PCC_CLK_WDOG0,
    PCC_CLK_TRGSEL0,
    PCC_CLK_TRGSEL1,
    PCC_CLK_TRGSEL2,
    PCC_CLK_TRGSEL3,
    PCC_CLK_CRC0,
    PCC_CLK_CORDIC,
    PCC_CLK_TSTMP0,
    PCC_CLK_TSTMP1,
    PCC_CLK_FCPIT0,
    PCC_CLK_AONTIMER0,
    PCC_CLK_RTC,
    PCC_CLK_CMU0,
    PCC_CLK_CMU1,
    PCC_CLK_CMU2,
    PCC_CLK_CMU3,
    PCC_CLK_CMU4,
    PCC_CLK_PTIMER0,
    PCC_CLK_PTIMER1,
    PCC_CLK_ADC0,
    PCC_CLK_ADC1,
    PCC_CLK_WKU0,
    PCC_CLK_CMP0,
    PCC_CLK_CMP1,
    PCC_CLK_TMU0,
    PCC_CLK_SENT0,
    PCC_CLK_MB0,
    PCC_CLK_FTU0,
    PCC_CLK_FTU1,
    PCC_CLK_FTU2,
    PCC_CLK_FTU3,
    PCC_CLK_FCSPI0,
    PCC_CLK_FCSPI1,
    PCC_CLK_FCSPI2,
    PCC_CLK_FCIIC0,
    PCC_CLK_FCUART0,
    PCC_CLK_FCUART1,
    PCC_CLK_FCUART2,
    PCC_CLK_FCUART3,
    PCC_CLK_LU0,
    PCC_CLK_FREQM,
    PCC_CLK_STCU,
    PCC_CLK_FLEXCAN0,
    PCC_CLK_FLEXCAN1,
    PCC_CLK_WDOG1,
    PCC_CLK_TRGSEL4,
    PCC_CLK_TRGSEL5,
	PCC_CLK_FCSPI3,
    PCC_CLK_FCSPI4,
    PCC_CLK_FCSPI5,
	PCC_CLK_FTU4,
	PCC_CLK_FTU5,
    PCC_CLK_FTU6,
    PCC_CLK_FTU7,
    PCC_CLK_FCIIC1,
    PCC_CLK_FCUART4,
    PCC_CLK_FCUART5,
    PCC_CLK_FCUART6,
    PCC_CLK_FCUART7,
    PCC_CLK_MSC0,
    PCC_CLK_FLEXCAN2,
    PCC_CLK_FLEXCAN3,
    PCC_END_OF_CLOCKS
} PCC_ClkSrcType;

/**
 * @brief Pcc clock status
*/
typedef enum
{
    PCC_STATUS_SUCCESS = 0U,
    PCC_STATUS_CLOCK_INVALID = 1U,
    PCC_STATUS_CONFIGURED_NOT_SUPPORT = 1U,
} PCC_StatusType;

/**
 * @brief define the PCC module initialization structure.
 */
typedef struct
{
    PCC_ClkSrcType eClockName;          /*!< Peripheral clock */
    bool bEn;                           /*!< Peripheral clock enable or disable */
    PCC_ClkGateSrcType eClkSrc;         /*!< Peripheral function clock source select */
    PCC_ClkDivType eDivider;            /*!< Peripheral clock divider value */
} PCC_CtrlType;

/**
 * @brief get PCC function clock status and value.
 *
 * @param pcc_ClkSrcType eClockName: used for choose PCC clock source to query.
 * @return uint32_t Pcc function clock frequency, if PCC is not enable or do not have clock mux configuration,
 *                  the function will return 0
 */
uint32_t PCC_GetPccFunctionClock(const PCC_ClkSrcType eClockName);

/**
 * @brief get PCC interface clock status and value.
 *
 * @param pcc_ClkSrcType eClockName: used for choose PCC clock source to query.
 */
uint32_t PCC_GetPccInterfaceClock(const PCC_ClkSrcType eClockName);

/**
 * @brief set PCC one peripheral clock configuration.
 *
 * @param PCC_CtrlType* pConfig: the PCC initialize value point set by user.
 * @return PCC_StatusType pcc function status
 */
PCC_StatusType PCC_SetPcc(const PCC_CtrlType *const pConfig);

/**
 * @brief Generate peripheral reset
 *
 */
void PCC_GenPeripheralReset(const PCC_ClkSrcType eClockName);


/** @}*/ /* fc7xxx_driver_pcc */
#endif
