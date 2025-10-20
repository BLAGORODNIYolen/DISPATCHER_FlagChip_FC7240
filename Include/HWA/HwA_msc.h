/**
 * @file HwA_msc.h
 * @author Flagchip
 * @brief FC7240 MSC HWA driver type definition and API
 * @version 0.1.0
 * @date 2024-01-10
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
 *   Revision History:
 *
 *   Version     Date          Initials      CR#          Descriptions
 *   ---------   ----------    ------------  ----------   ---------------
 *   0.1.0       2024-01-10    Flagchip084   N/A          FC7240 release version
 ******************************************************************************** */

#ifndef _HWA_MSC_H_
#define _HWA_MSC_H_

#include "device_header.h"

/**
 * @addtogroup HwA_msc
 * @{
 *
 */
/********* macros ************/

typedef enum
{
    MSC_RSV_SUCCESS         = 0x0U, /*!< MSC receive status is successful. */
    MSC_RSV_PARITY_ERROR    = 0x1U, /*!< MSC receive has parity error. */
    MSC_RSV_STOP_ERROR      = 0x2U  /*!< MSC receive has stop error. */
} MSC_ReceiveStatusType;

/********* Local typedef ************/

/********* Local inline function   ************/

/*********  xxx Register interface ************/

/**
 * @brief Get the msc TCCTR register
 *
 * @param pMsc MSCInstance
 * @param u32Value TCCTR register value
 */
LOCAL_INLINE void MSC_HWA_SetTcctr(MSC_Type *const pMsc, uint32_t u32Value)
{
    pMsc->TCCTR = u32Value;
}

/**
 * @brief Get the msc TCCTR register DTS bit
 *
 * @param pMsc MSCInstance
 * @return DTS value
 */
LOCAL_INLINE bool MSC_HWA_GetDataNeedSend(MSC_Type *const pMsc)
{
    return (pMsc->TCCTR & MSC_TCCTR_DTS_MASK) == MSC_TCCTR_DTS_MASK ? true : false;
}

/**
 * @brief Set the msc TCCTR register DTS bit
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_SetDataNeedSend(MSC_Type *const pMsc)
{
    pMsc->ISCR  = MSC_ISCR_SDTS_MASK;
}

/**
 * @brief Get the msc TCCTR register CTS bit
 *
 * @param pMsc MSCInstance
 * @return CTS value
 */
LOCAL_INLINE bool MSC_HWA_GetCmdNeedSend(MSC_Type *const pMsc)
{
    return (pMsc->TCCTR & MSC_TCCTR_CTS_MASK) == MSC_TCCTR_CTS_MASK ? true : false;
}

/**
 * @brief Get the CFB value of TCSTR register
 *
 * @param pMsc MSCInstance
 * @return CFB value
 */
LOCAL_INLINE bool MSC_HWA_GetCfb(MSC_Type *const pMsc)
{
    return (bool)(((pMsc->TCSTR & (uint32_t)MSC_TCSTR_CFB_MASK) != 0U) ? true : false);
}

/**
 * @brief Get the DFB value of TCSTR register
 *
 * @param pMsc MSCInstance
 * @return DFB value
 */
LOCAL_INLINE bool MSC_HWA_GetDfb(MSC_Type *const pMsc)
{
    return ((pMsc->TCSTR & (uint32_t)MSC_TCSTR_DFB_MASK) != 0U) ? true : false;
}

/**
 * @brief Set the NP value of TCSTR register
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_SetNp(MSC_Type *const pMsc, uint8_t u8Np)
{
    pMsc->TCSTR = (pMsc->TCSTR & ~MSC_TCSTR_NP_MASK) | MSC_TCSTR_NP(u8Np);
}

/**
 * @brief Get the NP value of TCSTR register
 *
 * @param pMsc MSCInstance
 * @return NP value
 */
LOCAL_INLINE uint32_t MSC_HWA_GetNp(MSC_Type *const pMsc)
{
    return ((pMsc->TCSTR & (uint32_t)MSC_TCSTR_NP_MASK)) >> MSC_TCSTR_NP_SHIFT;
}

/**
 * @brief Set the msc TCDAR register
 *
 * @param pMsc MSCInstance
 * @param u32Value TCDAR value
 */
LOCAL_INLINE void MSC_HWA_SetTcdar(MSC_Type *const pMsc, uint32_t u32Value)
{
    pMsc->TCDAR = u32Value;
}

/**
 * @brief Set the TDH of TCDAR register
 *
 * @param pMsc MSCInstance
 * @param u16Value TDH value
 */
LOCAL_INLINE void MSC_HWA_SetTcdarTdh(MSC_Type *const pMsc, uint16_t u16Value)
{
    pMsc->TCDAR = (pMsc->TCDAR & ~MSC_TCDAR_TDH_MASK) | MSC_TCDAR_TDH(u16Value);
}

/**
 * @brief Set the TDL of TCDAR register
 *
 * @param pMsc MSCInstance
 * @param u16Value TDL value
 */
LOCAL_INLINE void MSC_HWA_SetTcdarTdl(MSC_Type *const pMsc, uint16_t u16Value)
{
    pMsc->TCDAR = (pMsc->TCDAR & ~MSC_TCDAR_TDL_MASK) | MSC_TCDAR_TDL(u16Value);
}

/**
 * @brief Set the TCCOR register
 *
 * @param pMsc MSCInstance
 * @param u32Value TCCOR value
 */
LOCAL_INLINE void MSC_HWA_SetTccor(MSC_Type *const pMsc, uint32_t u32Value)
{
    pMsc->TCCOR = u32Value;
}

/**
 * @brief Set the TCH of TCCOR register
 *
 * @param pMsc MSCInstance
 * @param u16Value TCH value
 */
LOCAL_INLINE void MSC_HWA_SetTccorTch(MSC_Type *const pMsc, uint16_t u16Value)
{
    pMsc->TCCOR = (pMsc->TCCOR & ~MSC_TCCOR_TCH_MASK) | MSC_TCCOR_TCH(u16Value);
}

/**
 * @brief Set the TCL of TCCOR register
 *
 * @param pMsc MSCInstance
 * @param u16Value TCL value
 */
LOCAL_INLINE void MSC_HWA_SetTccorTcl(MSC_Type *const pMsc, uint16_t u16Value)
{
    pMsc->TCCOR = (pMsc->TCCOR & ~MSC_TCCOR_TCL_MASK) | MSC_TCCOR_TCL(u16Value);
}

/**
 * @brief Set the TCSLR register
 *
 * @param pMsc MSCInstance
 * @param u32Value TCSLR value
 */
LOCAL_INLINE void MSC_HWA_SetTcslr(MSC_Type *const pMsc, uint32_t u32Value)
{
    pMsc->TCSLR = u32Value;
}

/**
 * @brief Set the TCSHR register
 *
 * @param pMsc MSCInstance
 * @param u32Value TCSHR value
 */
LOCAL_INLINE void MSC_HWA_SetTcshr(MSC_Type *const pMsc, uint32_t u32Value)
{
    pMsc->TCSHR = u32Value;
}

/**
 * @brief Set the TCELR register
 *
 * @param pMsc MSCInstance
 * @param u32Value TCELR value
 */
LOCAL_INLINE void MSC_HWA_SetTcelr(MSC_Type *const pMsc, uint32_t u32Value)
{
    pMsc->TCELR = u32Value;
}

/**
 * @brief Get the IOCR register value
 *
 * @param pMsc MSCInstance
 * @return IOCR value
 */
LOCAL_INLINE uint32_t MSC_HWA_GetIocr(MSC_Type *const pMsc)
{
    return pMsc->IOCR;
}

/**
 * @brief Set the IOCR register
 *
 * @param pMsc MSCInstance
 * @param u32Value IOCR value
 */
LOCAL_INLINE void MSC_HWA_SetIocr(MSC_Type *const pMsc, uint32_t u32Value)
{
    pMsc->IOCR = u32Value;
}

/**
 * @brief Set the ISCR register
 *
 * @param pMsc MSCInstance
 * @param u32Value ISCR value
 */
LOCAL_INLINE void MSC_HWA_SetIscr(MSC_Type *const pMsc, uint32_t u32Value)
{
    pMsc->ISCR = u32Value;
}

/**
 * @brief Set the msc TCDIS
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_SetTcdis(MSC_Type *const pMsc)
{
    pMsc->ISCR = MSC_ISCR_SDIS_MASK;
}

/**
 * @brief Clear the msc TCDIS
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_ClearTcdis(MSC_Type *const pMsc)
{
    pMsc->ISCR = MSC_ISCR_CDIS_MASK;
}

/**
 * @brief Clear the msc CRFI
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_ClearCrfi(MSC_Type *const pMsc)
{
    pMsc->ISCR = MSC_ISCR_CRFI_MASK;
}

/**
 * @brief Clear the msc CTFI
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_ClearCtfi(MSC_Type *const pMsc)
{
    pMsc->ISCR = MSC_ISCR_CTFI_MASK;
}

/**
 * @brief Clear the msc CCFI
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_ClearCcfi(MSC_Type *const pMsc)
{
    pMsc->ISCR = MSC_ISCR_CCFI_MASK;
}

/**
 * @brief Clear the msc CDFI
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_ClearCdfi(MSC_Type *const pMsc)
{
    pMsc->ISCR = MSC_ISCR_CDFI_MASK;
}

/**
 * @brief Get the msc INSR register
 *
 * @param pMsc MSCInstance
 * @return INSR register value
 */
LOCAL_INLINE uint32_t MSC_HWA_GetInsr(MSC_Type *const pMsc)
{
    return pMsc->INSR & (uint32_t)MSC_INSR_MASK;
}

/**
 * @brief Set the INCR register
 *
 * @param pMsc MSCInstance
 * @param u32Value INCR value
 */
LOCAL_INLINE void MSC_HWA_SetIncr(MSC_Type *const pMsc, uint32_t u32Value)
{
    pMsc->INCR = u32Value;
}

/**
 * @brief Check the RFIE of INCR register
 *
 * @param pMsc MSCInstance
 * @return RFIE enable
 */
LOCAL_INLINE bool MSC_HWA_GetRfieEnable(MSC_Type *const pMsc)
{
    return (pMsc->INCR & MSC_INCR_RFIE_MASK) != 0U ? true : false;
}

/**
 * @brief Set the RFIE of INCR register
 *
 * @param pMsc MSCInstance
 * @param bEnable enable RFIE
 */
LOCAL_INLINE void MSC_HWA_SetRfieEnable(MSC_Type *const pMsc, bool bEnable)
{
    pMsc->INCR = (pMsc->INCR & ~MSC_INCR_RFIE_MASK) | MSC_INCR_RFIE(bEnable);
}

/**
 * @brief Check the TFIE of INCR register
 *
 * @param pMsc MSCInstance
 * @return TFIE enable
 */
LOCAL_INLINE bool MSC_HWA_GetTfieEnable(MSC_Type *const pMsc)
{
    return (pMsc->INCR & MSC_INCR_TFIE_MASK) == MSC_INCR_TFIE_MASK ? true : false;
}

/**
 * @brief Set the TFIE of INCR register
 *
 * @param pMsc MSCInstance
 * @param bEnable enable TFIE
 */
LOCAL_INLINE void MSC_HWA_SetTfieEnable(MSC_Type *const pMsc, bool bEnable)
{
    pMsc->INCR = (pMsc->INCR & ~MSC_INCR_TFIE_MASK) | MSC_INCR_TFIE(bEnable);
}

/**
 * @brief Check the CFIE of INCR register
 *
 * @param pMsc MSCInstance
 * @return CFIE enable
 */
LOCAL_INLINE bool MSC_HWA_GetCfieEnable(MSC_Type *const pMsc)
{
    return (pMsc->INCR & MSC_INCR_CFIE_MASK) == MSC_INCR_CFIE_MASK ? true : false;
}

/**
 * @brief Set the CFIE of INCR register
 *
 * @param pMsc MSCInstance
 * @param bEnable enable CFIE
 */
LOCAL_INLINE void MSC_HWA_SetCfieEnable(MSC_Type *const pMsc, bool bEnable)
{
    pMsc->INCR = (pMsc->INCR & ~MSC_INCR_CFIE_MASK) | MSC_INCR_CFIE(bEnable);
}

/**
 * @brief Check the DFIE of INCR register
 *
 * @param pMsc MSCInstance
 * @return DFIE enable
 */
LOCAL_INLINE bool MSC_HWA_GetDfieEnable(MSC_Type *const pMsc)
{
    return (pMsc->INCR & MSC_INCR_DFIE_MASK) == MSC_INCR_DFIE_MASK ? true : false;
}

/**
 * @brief Set the DFIE of INCR register
 *
 * @param pMsc MSCInstance
 * @param bEnable enable DFIE
 */
LOCAL_INLINE void MSC_HWA_SetDfieEnable(MSC_Type *const pMsc, bool bEnable)
{
    pMsc->INCR = (pMsc->INCR & ~MSC_INCR_DFIE_MASK) | MSC_INCR_DFIE(bEnable);
}

/**
 * @brief Check the TOIE of RTOR register
 *
 * @param pMsc MSCInstance
 * @return TOIE enable
 */
LOCAL_INLINE bool MSC_HWA_GetToieEnable(MSC_Type *const pMsc)
{
    return (pMsc->RTOR & MSC_RTOR_TOIE_MASK) == MSC_RTOR_TOIE_MASK ? true : false;
}

/**
 * @brief Set the TOIE of RTOR register
 *
 * @param pMsc MSCInstance
 * @param bEnable enable TOIE
 */
LOCAL_INLINE void MSC_HWA_SetToieEnable(MSC_Type *const pMsc, bool bEnable)
{
    pMsc->RTOR = (pMsc->RTOR & ~MSC_RTOR_TOIE_MASK) | MSC_RTOR_TOIE(bEnable);
}

/**
 * @brief Check the TOF of RTOR register
 *
 * @param pMsc MSCInstance
 * @return TOIE enable
 */
LOCAL_INLINE bool MSC_HWA_GetTofEnable(MSC_Type *const pMsc)
{
    return (pMsc->RTOR & MSC_RTOR_TOF_MASK) == MSC_RTOR_TOF_MASK ? true : false;
}

/**
 * @brief Check the TOF of RTOR register
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_ClearTofEnable(MSC_Type *const pMsc)
{
    pMsc->RTOR = (pMsc->RTOR & (~(MSC_RTOR_TOFC_MASK | MSC_RTOR_TOFS_MASK))) | MSC_RTOR_TOFC_MASK;
}

/**
 * @brief Check the RX busy status of RCCSR register
 *
 * @param pMsc MSCInstance
 * @return rx busy status
 */
LOCAL_INLINE bool MSC_HWA_GetRxBusy(MSC_Type *const pMsc)
{
    return (pMsc->RCCSR & MSC_RCCSR_RX_BUSY_MASK) == MSC_RCCSR_RX_BUSY_MASK ? true : false;
}

/**
 * @brief Get the msc RCCSR register
 *
 * @param pMsc MSCInstance
 * @return RCCSR register value
 */
LOCAL_INLINE uint32_t MSC_HWA_GetRccsr(MSC_Type *const pMsc)
{
    return pMsc->RCCSR;
}

/**
 * @brief Set the RCCSR register
 *
 * @param pMsc MSCInstance
 * @param u32Value RCCSR value
 */
LOCAL_INLINE void MSC_HWA_SetRccsr(MSC_Type *const pMsc, uint32_t u32Value)
{
    pMsc->RCCSR = u32Value;
}

/**
 * @brief Get the DATA of RDR0 register
 *
 * @param pMsc MSCInstance
 * @return RDATA value
 */
LOCAL_INLINE uint8_t MSC_HWA_GetRdr0Data(MSC_Type *const pMsc)
{
    return (uint8_t)((pMsc->RDR0 & MSC_RDR0_RDATA_MASK) >> MSC_RDR0_RDATA_SHIFT);
}

/**
 * @brief Get the LAF of RDR0 register
 *
 * @param pMsc MSCInstance
 * @return LAF value
 */
LOCAL_INLINE uint8_t MSC_HWA_GetRdr0Addr(MSC_Type *const pMsc)
{
    return (uint8_t)((pMsc->RDR0 & MSC_RDR0_LAF_MASK) >> MSC_RDR0_LAF_SHIFT);
}

/**
 * @brief Get the VLD of RDR0 register
 *
 * @param pMsc MSCInstance
 * @return VLD value
 */
LOCAL_INLINE bool MSC_HWA_GetRdr0Vld(MSC_Type *const pMsc)
{
    return (pMsc->RDR0 & MSC_RDR0_VLD_MASK) == MSC_RDR0_VLD_MASK ? true : false;
}

/**
 * @brief Get the RERR of RDR0 register
 *
 * @param pMsc MSCInstance
 * @return RERR value
 */
LOCAL_INLINE MSC_ReceiveStatusType MSC_HWA_GetRdr0Rerr(MSC_Type *const pMsc)
{
    uint32_t u32Tempvalue = (pMsc->RDR0 & MSC_RDR0_RERR_MASK) >> MSC_RDR0_RERR_SHIFT;
    return (MSC_ReceiveStatusType)u32Tempvalue;
}

/**
 * @brief Clear the VLD of register
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_ClearRdr0Vld(MSC_Type *const pMsc)
{
    pMsc->RDR0 |= MSC_RDR0_CLR_MASK;
}


/**
 * @brief Get the DATA of RDR1 register
 *
 * @param pMsc MSCInstance
 * @return RDATA value
 */
LOCAL_INLINE uint8_t MSC_HWA_GetRdr1Data(MSC_Type *const pMsc)
{
    return (uint8_t)((pMsc->RDR1 & MSC_RDR1_RDATA_MASK) >> MSC_RDR1_RDATA_SHIFT);
}

/**
 * @brief Get the LAF of RDR1 register
 *
 * @param pMsc MSCInstance
 * @return LAF value
 */
LOCAL_INLINE uint8_t MSC_HWA_GetRdr1Addr(MSC_Type *const pMsc)
{
    return (uint8_t)((pMsc->RDR1 & MSC_RDR1_LAF_MASK) >> MSC_RDR1_LAF_SHIFT);
}

/**
 * @brief Get the VLD of RDR1 register
 *
 * @param pMsc MSCInstance
 * @return VLD value
 */
LOCAL_INLINE bool MSC_HWA_GetRdr1Vld(MSC_Type *const pMsc)
{
    return (pMsc->RDR1 & MSC_RDR1_VLD_MASK) == MSC_RDR1_VLD_MASK ? true : false;
}

/**
 * @brief Get the RERR of RDR1 register
 *
 * @param pMsc MSCInstance
 * @return RERR value
 */
LOCAL_INLINE MSC_ReceiveStatusType MSC_HWA_GetRdr1Rerr(MSC_Type *const pMsc)
{
    uint32_t u32Tempvalue = (pMsc->RDR1 & MSC_RDR1_RERR_MASK) >> MSC_RDR1_RERR_SHIFT;
    return (MSC_ReceiveStatusType)u32Tempvalue ;
}

/**
 * @brief Clear the VLD of register
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_ClearRdr1Vld(MSC_Type *const pMsc)
{
    pMsc->RDR1 |= MSC_RDR1_CLR_MASK;
}


/**
 * @brief Get the DATA of RDR2 register
 *
 * @param pMsc MSCInstance
 * @return RDATA value
 */
LOCAL_INLINE uint8_t MSC_HWA_GetRdr2Data(MSC_Type *const pMsc)
{
    return (uint8_t)((pMsc->RDR2 & MSC_RDR2_RDATA_MASK) >> MSC_RDR2_RDATA_SHIFT);
}

/**
 * @brief Get the LAF of RDR2 register
 *
 * @param pMsc MSCInstance
 * @return LAF value
 */
LOCAL_INLINE uint8_t MSC_HWA_GetRdr2Addr(MSC_Type *const pMsc)
{
    return (uint8_t)((pMsc->RDR2 & MSC_RDR2_LAF_MASK) >> MSC_RDR2_LAF_SHIFT);
}

/**
 * @brief Get the VLD of RDR2 register
 *
 * @param pMsc MSCInstance
 * @return VLD value
 */
LOCAL_INLINE bool MSC_HWA_GetRdr2Vld(MSC_Type *const pMsc)
{
    return (pMsc->RDR2 & MSC_RDR2_VLD_MASK) == MSC_RDR2_VLD_MASK ? true : false;
}

/**
 * @brief Get the RERR of RDR2 register
 *
 * @param pMsc MSCInstance
 * @return RERR value
 */
LOCAL_INLINE MSC_ReceiveStatusType MSC_HWA_GetRdr2Rerr(MSC_Type *const pMsc)
{
    uint32_t u32Tempvalue = (pMsc->RDR2 & MSC_RDR2_RERR_MASK) >> MSC_RDR2_RERR_SHIFT;
    return (MSC_ReceiveStatusType)u32Tempvalue;
}

/**
 * @brief Clear the VLD of register
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_ClearRdr2Vld(MSC_Type *const pMsc)
{
    pMsc->RDR2 |= MSC_RDR2_CLR_MASK;
}


/**
 * @brief Get the DATA of RDR3 register
 *
 * @param pMsc MSCInstance
 * @return RDATA value
 */
LOCAL_INLINE uint8_t MSC_HWA_GetRdr3Data(MSC_Type *const pMsc)
{
    return (uint8_t)(pMsc->RDR3 & MSC_RDR3_RDATA_MASK) >> MSC_RDR3_RDATA_SHIFT;
}

/**
 * @brief Get the LAF of RDR3 register
 *
 * @param pMsc MSCInstance
 * @return LAF value
 */
LOCAL_INLINE uint8_t MSC_HWA_GetRdr3Addr(MSC_Type *const pMsc)
{
    return (uint8_t)((pMsc->RDR3 & MSC_RDR3_LAF_MASK) >> MSC_RDR3_LAF_SHIFT);
}

/**
 * @brief Get the VLD of RDR3 register
 *
 * @param pMsc MSCInstance
 * @return VLD value
 */
LOCAL_INLINE bool MSC_HWA_GetRdr3Vld(MSC_Type *const pMsc)
{
    return (pMsc->RDR3 & MSC_RDR3_VLD_MASK) == MSC_RDR3_VLD_MASK ? true : false;
}

/**
 * @brief Get the RERR of RDR3 register
 *
 * @param pMsc MSCInstance
 * @return RERR value
 */
LOCAL_INLINE MSC_ReceiveStatusType MSC_HWA_GetRdr3Rerr(MSC_Type *const pMsc)
{
    uint32_t u32Tempvalue = (pMsc->RDR3 & MSC_RDR3_RERR_MASK) >> MSC_RDR3_RERR_SHIFT;
    return (MSC_ReceiveStatusType)u32Tempvalue;
}

/**
 * @brief Clear the VLD of register
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_ClearRdr3Vld(MSC_Type *const pMsc)
{
    pMsc->RDR3 |= MSC_RDR3_CLR_MASK;
}

/**
 * @brief Reset the msc
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_SetMsrRst(MSC_Type *const pMsc)
{
    pMsc->MSR |= MSC_MSR_RST_MASK;
}

/**
 * @brief Get the reset status
 *
 * @param pMsc MSCInstance
 * @return reset status
 */
LOCAL_INLINE bool MSC_HWA_GetMsrRdone(MSC_Type *const pMsc)
{
    return (bool)(((pMsc->MSR & MSC_MSR_RDONE_MASK) != 0U) ? true : false);
}

/**
 * @brief clear reset status
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_ClearMsrDone(MSC_Type *const pMsc)
{
    pMsc->SRCR = MSC_SRCR_RCLR_MASK;
}

/**
 * @brief Get the msc RTOR register
 *
 * @param pMsc MSCInstance
 * @return RTOR register value
 */
LOCAL_INLINE uint32_t MSC_HWA_GetRtor(MSC_Type *const pMsc)
{
    return pMsc->RTOR;
}

/**
 * @brief Set the msc RTOR register
 *
 * @param pMsc MSCInstance
 * @param u32Value RTOR value
 */
LOCAL_INLINE void MSC_HWA_SetRtor(MSC_Type *const pMsc, uint32_t u32Value)
{
    pMsc->RTOR = u32Value;
}

/**
 * @brief Get the msc TCCTR1 register
 *
 * @param pMsc MSCInstance
 * @return TCCTR1 register value
 */
LOCAL_INLINE uint32_t MSC_HWA_GetTcctr1(MSC_Type *const pMsc)
{
    return pMsc->TCCTR1;
}

/**
 * @brief Set the msc TCCTR1 register
 *
 * @param pMsc MSCInstance
 * @param u32Value TCCTR1 value
 */
LOCAL_INLINE void MSC_HWA_SetTcctr1(MSC_Type *const pMsc, uint32_t u32Value)
{
    pMsc->TCCTR1 = u32Value;
}

/**
 * @brief Set the EN msc GCR register
 *
 * @param pMsc MSCInstance
 * @param bEnable EN value
 */
LOCAL_INLINE void MSC_HWA_SetMscEnable(MSC_Type *const pMsc, bool bEnable)
{
    pMsc->GCR = (pMsc->GCR & ~MSC_GCR_EN_MASK) | MSC_GCR_EN(bEnable);
}

/**
 * @brief Set the WP_EN of msc GCR register
 *
 * @param pMsc MSCInstance
 * @param bEnable WP_EN value
 */
LOCAL_INLINE void MSC_HWA_SetMscWriteProtection(MSC_Type *const pMsc, bool bEnable)
{
    pMsc->GCR = (pMsc->GCR & ~MSC_GCR_WP_EN_MASK) | MSC_GCR_WP_EN(bEnable);
}

/**
 * @brief Unlock the msc CCULR register
 *
 * @param pMsc MSCInstance
 */
LOCAL_INLINE void MSC_HWA_Unlock(MSC_Type *const pMsc)
{
    pMsc->CCULR = 0x10248888U;
}


/** @}*/ /* HwA_msc */

#endif /* #ifndef _HWA_MSC_H_ */
