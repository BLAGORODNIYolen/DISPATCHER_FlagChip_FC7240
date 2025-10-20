/**
 * @file HwA_cpm.h
 * @author Flagchip
 * @brief FC7xxx FMC register API
 * @version 0.1.0
 * @date 2024-1-5
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
  *   Revision History:
  *
  *   Version     Date          Initials      CR#          Descriptions
  *   ---------   ----------    ------------  ----------   ---------------
  *   0.1.0       2024-1-5      Flagchip120   N/A          First version for FC7240
  ******************************************************************************** */

#ifndef HWA_INCLUDE_HWA_FMC_H_
#define HWA_INCLUDE_HWA_FMC_H_
#include "device_header.h"
/* ################################################################################## */
/* ####################################### Macro #################################### */



/**
 * @brief Read the FMC FAPC0 register value for all.
 *
 * @param pFMC  FMC instance.
 * @return FMC FAPC0 regsiter value.
 */
LOCAL_INLINE uint32_t FMC_HWA_GetFAPC0Value(FMC_Type *pFMC)
{
    return pFMC->FAPC0;
}

/**
 * @brief Set FMC FAPC0 value, users should write the whole value to this register.
 *
 * @param pFMC  FMC instance.
 * @param u32Value  the value which will be written to the FAPC0 register.
 */
LOCAL_INLINE void FMC_HWA_SetFAPC0Value(FMC_Type *pFMC, uint32_t u32Value)
{
    pFMC->FAPC0 = u32Value;
}

/**
 * @brief Set FAPC0 data bus prefetch enable
 *
 * @param bEnable 0:Data prefetching is disabled.   1:Data prefetching is enabled.
 */
LOCAL_INLINE void FMC_HWA_SetFAPC0DataPrefechEnable(FMC_Type *pFMC, bool bEnable)
{
    pFMC->FAPC0 = ((pFMC->FAPC0 & (~FMC_FAPC0_DBPEN_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_FAPC0_DBPEN_SHIFT));
}

/**
 * @brief Set FAPC0 code bus prefetch enable
 *
 * @param bEnable 0:Code prefetching is disabled.   1:Code prefetching is disabled.
 */
LOCAL_INLINE void FMC_HWA_SetFAPC0CodePrefechEnable(FMC_Type *pFMC, bool bEnable)
{
    pFMC->FAPC0 = ((pFMC->FAPC0 & (~FMC_FAPC0_CBPEN_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_FAPC0_CBPEN_SHIFT));
}

/**
 * @brief Set FAPC0 data bus read buffers enable
 *
 * @param bEnable 0:Read data buffers are disabled.   1:Read data buffers are enabled.
 */
LOCAL_INLINE void FMC_HWA_SetFAPC0DataBuffersEnable(FMC_Type *pFMC, bool bEnable)
{
    pFMC->FAPC0 = ((pFMC->FAPC0 & (~FMC_FAPC0_DBBEN_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_FAPC0_DBBEN_SHIFT));
}

/**
 * @brief Set FAPC0 code bus read buffers enable
 *
 * @param bEnable 0:Read code buffers are disabled.   1:Read code buffers are enabled.
 */
LOCAL_INLINE void FMC_HWA_SetFAPC0CodeBuffersEnable(FMC_Type *pFMC, bool bEnable)
{
    pFMC->FAPC0 = ((pFMC->FAPC0 & (~FMC_FAPC0_CBBEN_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_FAPC0_CBBEN_SHIFT));
}

/**
 * @brief Set FAPC1 data bus prefetch enable
 *
 * @param bEnable 0:Data prefetching is disabled.   1:Data prefetching is enabled.
 */
LOCAL_INLINE void FMC_HWA_SetFAPC1DataPrefechEnable(FMC_Type *pFMC, bool bEnable)
{
    pFMC->FAPC1 = ((pFMC->FAPC1 & (~FMC_FAPC1_DBPEN_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_FAPC1_DBPEN_SHIFT));
}

/**
 * @brief Set FAPC1 code bus prefetch enable
 *
 * @param bEnable 0:Code prefetching is disabled.   1:Code prefetching is disabled.
 */
LOCAL_INLINE void FMC_HWA_SetFAPC1CodePrefechEnable(FMC_Type *pFMC, bool bEnable)
{
    pFMC->FAPC1 = ((pFMC->FAPC1 & (~FMC_FAPC1_CBPEN_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_FAPC1_CBPEN_SHIFT));
}

/**
 * @brief Set FAPC1 data bus read buffers enable
 *
 * @param bEnable 0:Read data buffers are disabled.   1:Read data buffers are enabled.
 */
LOCAL_INLINE void FMC_HWA_SetFAPC1DataBuffersEnable(FMC_Type *pFMC, bool bEnable)
{
    pFMC->FAPC1 = ((pFMC->FAPC1 & (~FMC_FAPC1_DBBEN_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_FAPC1_DBBEN_SHIFT));
}

/**
 * @brief Set FAPC1 code bus read buffers enable
 *
 * @param bEnable 0:Read code buffers are disabled.   1:Read code buffers are enabled.
 */
LOCAL_INLINE void FMC_HWA_SetFAPC1CodeBuffersEnable(FMC_Type *pFMC, bool bEnable)
{
    pFMC->FAPC1 = ((pFMC->FAPC1 & (~FMC_FAPC1_CBBEN_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_FAPC1_CBBEN_SHIFT));
}

/**
 * @brief Set FAPC2 data bus prefetch enable
 *
 * @param bEnable 0:Data prefetching is disabled.   1:Data prefetching is enabled.
 */
LOCAL_INLINE void FMC_HWA_SetFAPC2DataPrefechEnable(FMC_Type *pFMC, bool bEnable)
{
    pFMC->FAPC2 = ((pFMC->FAPC2 & (~FMC_FAPC2_DBPEN_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_FAPC2_DBPEN_SHIFT));
}

/**
 * @brief Set FAPC2 code bus prefetch enable
 *
 * @param bEnable 0:Code prefetching is disabled.   1:Code prefetching is disabled.
 */
LOCAL_INLINE void FMC_HWA_SetFAPC2CodePrefechEnable(FMC_Type *pFMC, bool bEnable)
{
    pFMC->FAPC2 = ((pFMC->FAPC2 & (~FMC_FAPC2_CBPEN_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_FAPC2_CBPEN_SHIFT));
}

/**
 * @brief Set FAPC2 data bus read buffers enable
 *
 * @param bEnable 0:Read data buffers are disabled.   1:Read data buffers are enabled.
 */
LOCAL_INLINE void FMC_HWA_SetFAPC2DataBuffersEnable(FMC_Type *pFMC, bool bEnable)
{
    pFMC->FAPC2 = ((pFMC->FAPC2 & (~FMC_FAPC2_DBBEN_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_FAPC2_DBBEN_SHIFT));
}

/**
 * @brief Set FAPC2 code bus read buffers enable
 *
 * @param bEnable 0:Read code buffers are disabled.   1:Read code buffers are enabled.
 */
LOCAL_INLINE void FMC_HWA_SetFAPC2CodeBuffersEnable(FMC_Type *pFMC, bool bEnable)
{
    pFMC->FAPC2 = ((pFMC->FAPC2 & (~FMC_FAPC2_CBBEN_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_FAPC2_CBBEN_SHIFT));
}

/**
 * @brief Read the FMC FEEC register value for all.
 *
 * @param pFMC  FMC instance.
 * @return FMC FEEC regsiter value.
 */
LOCAL_INLINE uint32_t FMC_HWA_GetFEECValue(FMC_Type *pFMC)
{
    return pFMC->FEEC;
}

/**
 * @brief Set FMC FEEC value, users should write the whole value to this register.
 *
 * @param pFMC  FMC instance.
 * @param u32Value the value which will be written to the FEEC register.
 */
LOCAL_INLINE void FMC_HWA_SetFEECValue(FMC_Type *pFMC, uint32_t u32Value)
{
    pFMC->FEEC = u32Value;
}

/**
 * @brief Read the FMC FEIPC register value for all.
 *
 * @param pFMC  FMC instance.
 * @return FMC FEIPC regsiter value.
 */
LOCAL_INLINE uint32_t FMC_HWA_GetFEIPCValue(FMC_Type *pFMC)
{
    return pFMC->FEIPC;
}

/**
 * @brief Set the date error position 1 & position 2
 *
 * @param pFMC  FMC instance.
 * @param u32Position1 Data error position 1
 * @param u32Position2 Data error position 2
 */
LOCAL_INLINE void FMC_HWA_SetInjectPositon(FMC_Type *pFMC, uint32_t u32Position1, uint32_t u32Position2)
{
    pFMC->FEIPC = (pFMC->FEIPC & ~FMC_FEIPC_EDATA_POS1_MASK) | FMC_FEIPC_EDATA_POS1(u32Position1);
    pFMC->FEIPC = (pFMC->FEIPC & ~FMC_FEIPC_EDATA_POS2_MASK) | FMC_FEIPC_EDATA_POS2(u32Position2);
}

/**
 * @brief Read the FMC FPESA_L register value for all.
 *
 * @param pFMC  FMC instance.
 * @return FMC FPESA_L regsiter value.
 */
LOCAL_INLINE uint32_t FMC_HWA_GetFPESALValue(FMC_Type *pFMC)
{
    return pFMC->FPESA_L;
}

/**
 * @brief Set FMC FPESA_L value.
 *
 * @param pFMC  FMC instance.
 * @param u32Value the value which will be written to the FPESA_L register.
 */
LOCAL_INLINE void FMC_HWA_SetFPESALValue(FMC_Type *pFMC, uint32_t u32Value)
{
    pFMC->FPESA_L = u32Value;
}

/**
 * @brief Read the FMC FPESA_P register value for all.
 *
 * @param pFMC  FMC instance.
 * @return FMC FPESA_P regsiter value.
 */
LOCAL_INLINE uint32_t FMC_HWA_GetFPESAPValue(FMC_Type *pFMC)
{
    return pFMC->FPESA_P;
}

/**
 * @brief Read the FMC FB_FPELCK register value for all.
 *
 * @param pFMC  FMC instance.
 * @param u8SeqGroupIndex the index of the sequence group
 * @return FMC FB_FPELCK regsiter value.
 */
LOCAL_INLINE uint32_t FMC_HWA_GetFBFPELCKValue(FMC_Type *pFMC, uint8_t u8SeqGroupIndex)
{
    return pFMC->FB_FPELCK[u8SeqGroupIndex];
}

/**
 * @brief Set FMC FB_FPELCK value.
 *
 * @param pFMC  FMC instance.
 * @param u8SeqGroupIndex the index of the sequence group
 * @param u32Value the value which will be written to the FB_FPELCK register.
 */
LOCAL_INLINE void FMC_HWA_SetFBFPELCKValue(FMC_Type *pFMC, uint8_t u8SeqGroupIndex, uint32_t u32Value)
{
    pFMC->FB_FPELCK[u8SeqGroupIndex] = u32Value;
}

/**
 * @brief NVI program erase Lock
 *
 * @param bEnable 0:unlock.   1:locked.
 */
LOCAL_INLINE void FMC_HWA_SetNVRLocked(FMC_Type *pFMC, bool bEnable)
{
    pFMC->FN_FPELCK = ((pFMC->FN_FPELCK & (~FMC_FN_FPELCK_FPELCK_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_FN_FPELCK_FPELCK_SHIFT));
}

/**
 * @brief Get NVR lock status.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return the NVR status(1:locked  0:unlocked).
 */
LOCAL_INLINE uint8_t FCSPI_HWA_GetNVRLockedStatus(FMC_Type *pFMC)
{
    return (uint8_t)(((pFMC->FN_FPELCK) & FMC_FN_FPELCK_FPELCK_MASK) >> FMC_FN_FPELCK_FPELCK_SHIFT);
}

/**
 * @brief Read the FMC FB_CPELCK register value for all.
 *
 * @param pFMC  FMC instance.
 * @param u8SeqGroupIndex the index of the sequence group
 * @return FMC FB_CPELCK regsiter value.
 */
LOCAL_INLINE uint32_t FMC_HWA_GetFBCPELCKValue(FMC_Type *pFMC, uint8_t u8SeqGroupIndex)
{
    return pFMC->FB_CPELCK[u8SeqGroupIndex];
}

/**
 * @brief Set FMC FB_CPELCK value.
 *
 * @param pFMC  FMC instance.
 * @param u8SeqGroupIndex the index of the sequence group
 * @param u32Value the value which will be written to the FB_CPELCK register.
 */
LOCAL_INLINE void FMC_HWA_SetFBCPELCKValue(FMC_Type *pFMC, uint8_t u8SeqGroupIndex, uint32_t u32Value)
{
    pFMC->FB_CPELCK[u8SeqGroupIndex] = u32Value;
}

/**
 * @brief Set OTA register lock
 *
 * @param pFMC  FMC instance.
 * @param u8SeqGroupIndex the index of the sequence group
 * @param bEnable 0:OTA_CTRL can be written.   1:OTA_CTRL is locked.
 */
LOCAL_INLINE void FMC_HWA_SetOTALock(FMC_Type *pFMC, uint8_t u8SeqGroupIndex, bool bEnable)
{
    pFMC->OTA_CTRL[u8SeqGroupIndex] = ((pFMC->OTA_CTRL[u8SeqGroupIndex] & (~FMC_OTA_CTRL_OTA_LOCK_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_OTA_CTRL_OTA_LOCK_SHIFT));
}

/**
 * @brief Set OTA active block
 *
 * @param pFMC  FMC instance.
 * @param u8SeqGroupIndex the index of the sequence group
 * @param bEnable 0: block0 is the currently active OTA region.   1: block1 is the currently active OTA region.
 */
LOCAL_INLINE void FMC_HWA_SetOTAActive(FMC_Type *pFMC, uint8_t u8SeqGroupIndex, bool bEnable)
{
    pFMC->OTA_CTRL[u8SeqGroupIndex] = ((pFMC->OTA_CTRL[u8SeqGroupIndex] & (~FMC_OTA_CTRL_OTA_ACTIVE_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << FMC_OTA_CTRL_OTA_ACTIVE_SHIFT));
}

/**
 * @brief Enable OTA
 *
 * @param pFMC  FMC instance.
 * @param u8SeqGroupIndex the index of the sequence group
 */
LOCAL_INLINE void FMC_HWA_SetOTAEnable(FMC_Type *pFMC, uint8_t u8SeqGroupIndex)
{
    pFMC->OTA_CTRL[u8SeqGroupIndex] = ((pFMC->OTA_CTRL[u8SeqGroupIndex] & (~FMC_OTA_CTRL_OTA_EN_MASK)) | FMC_OTA_CTRL_OTA_EN(0xA));
}

/**
 * @brief Disable OTA
 *
 * @param pFMC  FMC instance.
 * @param u8SeqGroupIndex the index of the sequence group
 */
LOCAL_INLINE void FMC_HWA_SetOTADisable(FMC_Type *pFMC, uint8_t u8SeqGroupIndex)
{
    pFMC->OTA_CTRL[u8SeqGroupIndex] = ((pFMC->OTA_CTRL[u8SeqGroupIndex] & (~FMC_OTA_CTRL_OTA_EN_MASK)) | FMC_OTA_CTRL_OTA_EN(0x15));
}

/**
 * @brief Read the FMC OTA_CTRL register value for all.
 *
 * @param pFMC  FMC instance.
 * @param u8SeqGroupIndex the index of the sequence group
 * @return FMC OTA_CTRL regsiter value.
 */
LOCAL_INLINE uint32_t FMC_HWA_GetOTACtrlValue(FMC_Type *pFMC, uint8_t u8SeqGroupIndex)
{
    return pFMC->OTA_CTRL[u8SeqGroupIndex];
}

/**
 * @brief Read the FMC OTA_VER_LOC register value for all.
 *
 * @param pFMC  FMC instance.
 * @param u8SeqGroupIndex the index of the sequence group
 * @return FMC OTA_VER_LOC regsiter value.
 */
LOCAL_INLINE uint32_t FMC_HWA_GetOTAVerLocValue(FMC_Type *pFMC, uint8_t u8SeqGroupIndex)
{
    return pFMC->OTA_VER_LOC[u8SeqGroupIndex];
}

/**
 * @brief Read the FMC OTA_ACT_VER register value for all.
 *
 * @param pFMC  FMC instance.
 * @param u8SeqGroupIndex the index of the sequence group
 * @return FMC OTA_ACT_VER regsiter value.
 */
LOCAL_INLINE uint32_t FMC_HWA_GetOTAActVerValue(FMC_Type *pFMC, uint8_t u8SeqGroupIndex)
{
    return pFMC->OTA_ACT_VER[u8SeqGroupIndex];
}


/** @}*/

#endif /* HWA_INCLUDE_HWA_FMC_H_ */
