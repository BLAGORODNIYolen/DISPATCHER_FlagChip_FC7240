/**
 * @file HwA_cmu.h
 * @author Flagchip085
 * @brief FC7xxx CMU hardware access layer
 * @version 0.1.0
 * @date 2024-01-12
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

#ifndef _HWA_CMU_H_
#define _HWA_CMU_H_

#include "device_header.h"

/********* Local inline function ************/
/**
 * @brief Set Reference Window value.
 * @param pCmu CMU Instance.
 * @param u32Value Ref Window value.
*/
LOCAL_INLINE void CMU_HWA_SetRefWindow(CMU_Type *const pCmu, uint32_t u32Value)
{
    pCmu->REF_WINDOW = CMU_REF_WINDOW_REF_WINDOW(u32Value);
}

/**
 * @brief Get Reference Window value.
 * @param pCmu CMU Instance.
 * @return Reference Window value.
 */
LOCAL_INLINE uint32_t CMU_HWA_GetRefWindow(const CMU_Type *const pCmu)
{
    return (pCmu->REF_WINDOW & CMU_REF_WINDOW_REF_WINDOW_MASK) >> CMU_REF_WINDOW_REF_WINDOW_SHIFT;
}

/**
* @brief Set Minimun Counter value
 * @param pCmu CMU Instance.
 * @param u32Value Min Count value.
*/
LOCAL_INLINE void CMU_HWA_SetMinCnts(CMU_Type *const pCmu, uint32_t u32Value)
{
    pCmu->MIN = CMU_MIN_MIN(u32Value);
}

/**
 * @brief Get Minimun Counter value.
 * @param pCmu CMU Instance.
 * @return Min count value.
 */
LOCAL_INLINE uint32_t CMU_HWA_GetMinCnts(const CMU_Type *const pCmu)
{
    return (pCmu->MIN & CMU_MIN_MIN_MASK) >> CMU_MIN_MIN_SHIFT;
}

/**
 * @brief Set Maximun Counter value.
 * @param pCmu CMU Instance.
 * @param u32Value Max count value.
*/
LOCAL_INLINE void CMU_HWA_SetMaxCnts(CMU_Type *const pCmu, uint32_t u32Value)
{
    pCmu->MAX = CMU_MAX_MAX(u32Value);
}

/**
 * @brief Get Maximun Counter value.
 * @param pCmu CMU Instance.
 * @return Max count value.
 */
LOCAL_INLINE uint32_t CMU_HWA_GetMaxCnts(const CMU_Type *const pCmu)
{
    return (pCmu->MAX & CMU_MAX_MAX_MASK) >> CMU_MAX_MAX_SHIFT;
}

/**
 * @brief Get Counter value.
 * @param pCmu CMU Instance.
 * @return Counter value.
 */
LOCAL_INLINE uint32_t CMU_HWA_GetCount(const CMU_Type *const pCmu)
{
    return (pCmu->MON_CNT & CMU_MON_CNT_MON_CNT_MASK) >> CMU_MON_CNT_MON_CNT_SHIFT;
}

/**
 * @brief Set period window Counter.
 * @param pCmu CMU Instance.
 * @param u32Value Period value.
*/
LOCAL_INLINE void CMU_HWA_SetPeriodWindow(CMU_Type *const pCmu, uint32_t u32Value)
{
    pCmu->PERIOD = (pCmu->PERIOD & ~CMU_PERIOD_WINDOW_MASK) | CMU_PERIOD_WINDOW(u32Value);
}

/**
 * @brief Set period enble bit.
*
 * @param pCmu CMU Instance.
 * @param bEnable Set enable bit.
*/
LOCAL_INLINE void CMU_HWA_SetPeriodEnable(CMU_Type *const pCmu, bool bEnable)
{
    pCmu->PERIOD = (pCmu->PERIOD & ~((uint32_t)CMU_PERIOD_EN_MASK)) | CMU_PERIOD_EN(bEnable);
}

/**
* @brief Set control register value.
 *
 * @param pCmu CMU Instance.
 * @param u32Value Control value.
*/
LOCAL_INLINE void CMU_HWA_SETCTRL(CMU_Type *const pCmu, uint32_t u32Value)
{
    pCmu->CTRL = u32Value;
}

/**
* @brief return control register value.
 *
 * @param pCmu CMU Instance.
 * @return CMU Control register value
*/
LOCAL_INLINE uint32_t CMU_HWA_GetCTRL(const CMU_Type *const pCmu)
{
    return pCmu->CTRL;
}

/**
 * @brief return status register value.
 * @param pCmu CMU Instance.
 * @return Status value.
*/
LOCAL_INLINE uint32_t CMU_HWA_GetST(const CMU_Type *const pCmu)
{
    return pCmu->ST;
}

/**
 * @brief Clear clock monitor status
 * @param pCmu CMU Instance.
*/
LOCAL_INLINE void CMU_HWA_ClearST(CMU_Type *const pCmu)
{
    pCmu->ST = (uint32_t)(CMU_ST_MIS_MASK | CMU_ST_LOC_MASK);
}

/**
 * @brief Set the Divider for Reference Clock
 * @param pCmu CMU Instance.
 * @param eDivider The Divider of Reference Clock
*/
LOCAL_INLINE void CMU_HWA_SetRefClockDiv(CMU_Type *const pCmu, uint8_t eDivider)
{
    pCmu->CTRL = (pCmu->CTRL & ~((uint32_t)CMU_CTRL_REF_DIV_MASK)) | CMU_CTRL_REF_DIV(eDivider);
}

/**
 * @brief Get the Divider for Reference Clock
 * @param pCmu CMU Instance.
 * @return The Divider of Reference Clock
*/
LOCAL_INLINE uint8_t CMU_HWA_GetRefClockDiv(const CMU_Type *const pCmu)
{
	uint32_t u32Temp = (pCmu->CTRL & (uint32_t)CMU_CTRL_REF_DIV_MASK) >> CMU_CTRL_REF_DIV_SHIFT;
    return (uint8_t)u32Temp;
}

/**
 * @brief Enable interrupt when LOC or MIS asserted
 * @param pCmu CMU Instance.
 * @param bEnable Enable or disable CMU interrupt
*/
LOCAL_INLINE void CMU_HWA_IrqEnable(CMU_Type *const pCmu, bool bEnable)
{
    pCmu->CTRL = (pCmu->CTRL & (~((uint32_t)CMU_CTRL_IRQ_EN_MASK))) | CMU_CTRL_IRQ_EN(bEnable);
}

/**
 * @brief Get CMU interrupt enable flag
 * @param pCmu CMU Instance.
 * @return 1 : CMU interrupt enabled
 * 		   0 : CMU interrupt disabled
*/
LOCAL_INLINE uint8_t CMU_HWA_GetIrqEnableFlag(const CMU_Type *const pCmu)
{
	uint32_t u32Temp = (pCmu->CTRL & (uint32_t)CMU_CTRL_IRQ_EN_MASK) >> CMU_CTRL_IRQ_EN_SHIFT;
    return (uint8_t)u32Temp;
}

/**
 * @brief Enable Standby mode
 * @param pCmu CMU Instance.
 * @param bEnable Enable mode
*/
LOCAL_INLINE void CMU_HWA_StanbyModeEnable(CMU_Type *const pCmu, bool bEnable)
{
    pCmu->CTRL = (pCmu->CTRL & ~((uint32_t)CMU_CTRL_LP_EN_MASK)) | CMU_CTRL_LP_EN(bEnable);
}

/**
 * @brief Enable Stop mode
 * @param pCmu CMU Instance.
 * @param bEnable Enable mode
*/
LOCAL_INLINE void CMU_HWA_StopModeEnable(CMU_Type *const pCmu, bool bEnable)
{
    pCmu->CTRL = (pCmu->CTRL & ~((uint32_t)CMU_CTRL_STOP_EN_MASK)) | CMU_CTRL_STOP_EN(bEnable);
}

/**
 * @brief Enable hardware restart CMU after exiting from the low-power mode
 * @param pCmu CMU Instance.
 * @param bEnable Enable mode
*/
LOCAL_INLINE void CMU_HWA_LPRestartEnable(CMU_Type *const pCmu, bool bEnable)
{
    pCmu->CTRL = (pCmu->CTRL & ~((uint32_t)CMU_CTRL_RESTART_EN_MASK)) | CMU_CTRL_RESTART_EN(bEnable);
}

/**
 * @brief  Software Reset the CMU
 * @param pCmu CMU Instance.
*/
LOCAL_INLINE void CMU_HWA_SoftwareReset(CMU_Type *const pCmu)
{
    pCmu->CTRL |= CMU_CTRL_SW_RST_MASK;
}

/**
 * @brief Enable the CMU
 * @param pCmu CMU Instance.
*/
LOCAL_INLINE void CMU_HWA_Enable(CMU_Type *const pCmu)
{
    pCmu->CTRL |= CMU_CTRL_ENABLE_MASK;
}

/**
 * @brief Disable the CMU
 * @param pCmu CMU Instance.
*/
LOCAL_INLINE void CMU_HWA_Disable(CMU_Type *const pCmu)
{
    pCmu->CTRL &=  ~(CMU_CTRL_ENABLE_MASK | CMU_CTRL_IRQ_EN_MASK);

}

/**
 * @brief Get the CMU enabled status
 * @param pCmu CMU Instance.
 * @return 1 : CMU is enabled
 * 		   0 : CMU is disabled
*/
LOCAL_INLINE uint8_t CMU_HWA_GetEnableStatus(const CMU_Type *const pCmu)
{
	uint32_t u32Temp = (pCmu->CTRL & (uint32_t)CMU_CTRL_ENABLE_MASK) >> CMU_CTRL_ENABLE_SHIFT;
    return (uint8_t)u32Temp;
}

#endif /* #ifndef _HWA_CMU_H_ */
