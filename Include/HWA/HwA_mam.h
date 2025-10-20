/**
 * @file HwA_mam.h
 * @author Flagchip
 * @brief Hardware access layer for MAM
 * @version 0.2.0
 * @date 2023-02-08
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2023-02-08    Flagchip054   N/A          First version for FC7300
   ******************************************************************************** */
#ifndef _HWA_MAM_H_
#define _HWA_MAM_H_
#include "device_header.h"

/**
 * @brief Set Mam module Matrix Configure register
 *
 * @param1 MAM base pointer
 *
 * @param2 u32Value Matrix Configure register value
 */
LOCAL_INLINE void Mam_HWA_SetMatrixCfg(MAM_Type *MAMInstance, uint32_t u32Value)
{
	MAMInstance->MAXCFG = u32Value;
}

/**
 * @brief Read Mam module Ctrl register
 *
 * @param MAM base pointer
 *
 * @return Matrix Configure register value
 */
LOCAL_INLINE uint32_t Mam_HWA_GetMatrixCfg(MAM_Type *MAMInstance)
{
    return (uint32_t)(MAMInstance->MAXCFG);
}

/**
 * @brief Set Mam module Wdgctr register
 *
 * @param1 MAM base pointer
 *
 * @param2 u32Value Wdgctr register value
 */
LOCAL_INLINE void Mam_HWA_Set_Wdgctr(MAM_Type *MAMInstance, uint32_t u32Value)
{
	MAMInstance->WDGCR = u32Value;
}

/**
 * @brief Read Mam module Wdgctr register
 *
 * @param MAM base pointer
 *
 * @return Wdgctr register value
 */
LOCAL_INLINE uint32 Mam_HWA_Get_Wdgctr(MAM_Type *MAMInstance)
{
	return MAMInstance->WDGCR;
}

/**
 * @brief Set Mam module ACR register
 *
 * @param1 MAM base pointer
 *
 * @param2 idx ACR register index
 *
 * @param3 u32Value ACR register value
 */
LOCAL_INLINE void Mam_HWA_Set_ACR(MAM_Type *MAMInstance, uint32_t idx, uint32_t u32Value)
{
	MAMInstance->ACR[idx] = u32Value;
}

/**
 * @brief Read Mam module ACR register
 *
 * @param1 MAM base pointer
 *
 * @param2 idx ACR register index
 *
 * @return ACR register value
 */
LOCAL_INLINE uint32_t Mam_HWA_Get_ACR(MAM_Type *MAMInstance, uint32_t idx)
{
    return MAMInstance->ACR[idx];
}

/**
 * @brief Set Mam module ACLR register
 *
 * @param1 MAM base pointer
 *
 * @param2 idx ACLR register index
 *
 * @param3 u32Value ACLR register value
 */
LOCAL_INLINE void Mam_HWA_Set_ACLR(MAM_Type *MAMInstance, uint32_t idx, uint32_t u32Value)
{
	MAMInstance->ACLR[idx] = u32Value;
}

/**
 * @brief Read Mam module ACLR register
 *
 * @param1 MAM base pointer
 *
 * @param2 idx ACLR register index
 *
 * @return ACLR register value
 */
LOCAL_INLINE uint32_t Mam_HWA_Get_ACLR(MAM_Type *MAMInstance, uint32_t idx)
{
    return MAMInstance->ACLR[idx];
}

#endif
