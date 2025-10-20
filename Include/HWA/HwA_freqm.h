/**
 * @file HwA_freqm.h
 * @author Flagchip
 * @brief FC7xxx freqm hardware access layer
 * @version 0.1.0
 * @date 2024-01-14
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
   *   0.1.0       2024-01-14    qxw0100       N/A          First version for FC7240
   ******************************************************************************** */

#ifndef _HWA_FREQM_H_
#define _HWA_FREQM_H_

#include "device_header.h"

/**
 * @brief Select the measured clock
 *
 */
typedef enum
{
	MES_RSVD00            =  0U,
	MES_SLOW_CLK          =  1U,
	MES_PLL1_FEEDBACK     =  2U,
	MES_PLL0_FEEDBACK     =  3U,
	MES_SCG_CLKOUT        =  4U,
    MES_RTC_CLK           =  5U,
	MES_AON_CLK           =  6U,
	MES_SIRC128K_CLK      =  7U,
	MES_RSVD01            =  8U,
	MES_RSVD02            =  9U,
	MES_FCPIT0_FUN_CLK    = 10U,
	MES_RSVD03            = 11U,
	MES_RSVD04            = 12U,
	MES_FCSPI0_FUN_CLK    = 13U,
	MES_FCSPI1_FUN_CLK    = 14U,
	MES_FCSPI2_FUN_CLK    = 15U,
	MES_RSVD05            = 16U,
	MES_FCUART0_FUN_CLK   = 17U,
	MES_FCUART1_FUN_CLK   = 18U,
	MES_FCUART2_FUN_CLK   = 19U,
	MES_RSVD06            = 20U,
	MES_TRGSEL1_OUT4      = 21U,
	MES_FTU0_FUN_CLK      = 22U,
	MES_FTU1_FUN_CLK      = 23U,
	MES_RSVD07            = 24U,
	MES_FTU2_FUN_CLK      = 25U,
	MES_FTU3_FUN_CLK      = 26U,
	MES_ADC0_FUN_CLK      = 27U,
	MES_RSVD08            = 28U,
	MES_ADC1_FUN_CLK      = 29U,
	MES_RSVD09            = 30U,
	MES_RSVD10            = 31U,
	MES_RSVD11            = 32U,
	MES_FOSC_DIVL         = 33U,
	MES_SIRC_DIVL         = 34U,
	MES_FIRC_DIVL         = 35U,
	MES_RSVD12            = 36U,
	MES_PLL1_DIVL         = 37U,
	MES_PLL0_DIVL         = 38U,
	MES_RSVD13            = 39U,
	MES_RSVD14            = 40U,
	MES_FOSC_DIVM         = 41U,
	MES_SIRC_DIVM         = 42U,
	MES_FIRC_DIVM         = 43U,
	MES_RSVD15            = 44U,
	MES_PLL1_DIVM         = 45U,
	MES_PLL0_DIVM         = 46U,
	MES_RSVD16            = 47U,
	MES_RSVD17            = 48U,
	MES_FOSC_DIVH         = 49U,
	MES_SIRC_DIVH         = 50U,
	MES_FIRC_DIVH         = 51U,
	MES_RSVD18            = 52U,
	MES_PLL1_DIVH         = 53U,
	MES_PLL0_DIVH         = 54U,
	MES_RSVD19            = 55U,
	MES_RSVD20            = 56U,
	MES_SENT0_FUN_CLK     = 57U,
	MES_FLEXCAN0_FUN_CLK  = 58U,
	MES_FLEXCAN1_FUN_CLK  = 59U,
	MES_RSVD21            = 60U,
	MES_MSC0_FUN_CLK      = 61U,
	MES_TPU_FUN_CLK       = 62U,
	MES_RSVD22            = 63U,
} FREQM_MesClkSelType;

/**
 * @brief Set the clock selection
 *
 * @param pFreqm the base address of the FREQM
 * @param eClkSel the clock selection index
 */
LOCAL_INLINE void FREQM_HWA_MesClkSel(FREQM_Type *pFreqm,FREQM_MesClkSelType eClkSel)
{
	pFreqm->CTRL &= ~FREQM_CTRL_MES_CLK_SEL_MASK;
	pFreqm->CTRL |= FREQM_CTRL_MES_CLK_SEL((uint32_t)eClkSel);
}

/**
 * @brief Set the clock selection
 *
 * @param pFreqm the base address of the FREQM
 * @param u8PredivVal the measure clock prediv value
 */
LOCAL_INLINE void FREQM_HWA_MesClk_PreDiv(FREQM_Type *pFreqm,uint8_t u8PredivVal)
{
	pFreqm->CTRL &= ~FREQM_CTRL_MES_CLK_PREDIV_MASK;
	pFreqm->CTRL |= FREQM_CTRL_MES_CLK_PREDIV(u8PredivVal);
}

/**
 * @brief Enable count event interrupt
 *
 * @param pFreqm the base address of the FREQM
 */
LOCAL_INLINE void FREQM_HWA_EnableCntEventInterrupt(FREQM_Type *pFreqm)
{
	pFreqm->CTRL |= FREQM_CTRL_CNT_EVENT_IE_MASK;
}

/**
 * @brief Disable count event interrupt
 *
 * @param pFreqm the base address of the FREQM
 */
LOCAL_INLINE void FREQM_HWA_DisableCntEventInterrupt(FREQM_Type *pFreqm)
{
	pFreqm->CTRL &= ~((uint32_t)FREQM_CTRL_CNT_EVENT_IE_MASK);
}

/**
 * @brief Set counting length of measure counter
 *
 * @param pFreqm the base address of the FREQM
 * @param u32MesLen counting length of measure counter
 */
LOCAL_INLINE void FREQM_HWA_SetMesLength(FREQM_Type *pFreqm,uint32_t u32MesLen)
{
	pFreqm->MES_LENGTH = u32MesLen;
}

/**
 * @brief Set timeout value of reference counter
 *
 * @param pFreqm the base address of the FREQM
 * @param u32RefTo timeout value of reference counter
 */
LOCAL_INLINE void FREQM_HWA_SetRefTimeout(FREQM_Type *pFreqm,uint32_t u32RefTo)
{
	pFreqm->REF_TIMEOUT = u32RefTo;
}

/**
 * @brief Set value of reference counter
 *
 * @param pFreqm the base address of the FREQM
 * @param u32RefCnt value of reference counter
 */
LOCAL_INLINE void FREQM_HWA_SetRefCnt(FREQM_Type *pFreqm,uint32_t u32RefCnt)
{
	pFreqm->REF_CNT = u32RefCnt;
}

/**
 * @brief Clear counter event interrupt flag
 *
 * @param pFreqm the base address of the FREQM
 */
LOCAL_INLINE void FREQM_HWA_ClearInterruptFlag(FREQM_Type *pFreqm)
{
	pFreqm->CNT_STATUS |= FREQM_CNT_STATUS_CNT_EVENT_MASK;
}

/**
 * @brief  Get counter event interrupt flag
 *
 * @param pFreqm the base address of the FREQM
 * @param return   false for disable, true for enable.
 */
LOCAL_INLINE bool FREQM_HWA_GetInterruptFlag(FREQM_Type *pFreqm)
{
   return ((pFreqm->CNT_STATUS & FREQM_CNT_STATUS_CNT_EVENT_MASK) == FREQM_CNT_STATUS_CNT_EVENT_MASK) ? true : false;
}

/**
 * @brief  Get counter status
 *
 * @param pFreqm the base address of the FREQM
 * @param return Counter status.
 */
LOCAL_INLINE uint32_t FREQM_HWA_GetCntStatus(FREQM_Type *pFreqm)
{
	uint32_t u32Mask = (FREQM_CNT_STATUS_MES_CNT_START_MASK|FREQM_CNT_STATUS_MES_CNT_STOP_MASK|FREQM_CNT_STATUS_REF_CNT_STOP_MASK);
    return (pFreqm->CNT_STATUS & u32Mask);
}

/**
 * @brief Set value of measure counter
 *
 * @param pFreqm the base address of the FREQM
 * @param u32MesCnt value of measure counter
 */
LOCAL_INLINE void FREQM_HWA_SetMesCnt(FREQM_Type *pFreqm,uint32_t u32MesCnt)
{
	pFreqm->MES_CNT = u32MesCnt;
}

/**
 * @brief  Get saved reference counter value
 *
 * @param pFreqm the base address of the FREQM
 * @param return saved reference counter value.
 */
LOCAL_INLINE uint32_t FREQM_HWA_GetRefCntSave(FREQM_Type *pFreqm)
{
    return pFreqm->REF_CNT_SAVE;
}

#endif /* #ifndef _HWA_FREQM_H_ */
