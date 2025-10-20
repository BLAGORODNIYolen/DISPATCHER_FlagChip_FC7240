/**
 * @file HwA_cpm.h
 * @author Flagchip
 * @brief FC7xxx CPM register API
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

#ifndef HWA_INCLUDE_HWA_CPM_H_
#define HWA_INCLUDE_HWA_CPM_H_
#include "device_header.h"
/* ################################################################################## */
/* ####################################### Macro #################################### */

/** FPSCR  Bit Fields */
#define FPSCR_IOC_MASK            0x00000001U
#define FPSCR_DZC_MASK            0x00000002U
#define FPSCR_OFC_MASK            0x00000004U
#define FPSCR_UFC_MASK            0x00000008U
#define FPSCR_IXC_MASK            0x00000010U
#define FPSCR_IDC_MASK            0x00000080U
#define CPM_FPU_INTFLAGMASK       0x0000003FU

/**
 * @defgroup HwA_cpm
 * @ingroup fc7xxx_driver_cpm
 * @{
 */

/**
 * @brief FPU INTERRUPT type.
 *
 * This provides constants for FPU interrupt type for use in the FPU functions.
 * Please refer to Reference Manual chapter 14 CPM, it introduce register FISCR for details.
 *
 */


typedef enum
{
    CPM_FPU_FIO = 1U,         /*!< in function CPM_FpuIntMode, set CPM_FISCR FIOCE bit; in function CPM_GetFpuIntStatus, get CPM_FISCR FIOC Status*/
    CPM_FPU_FDZ = 2U,         /*!< in function CPM_FpuIntMode, set CPM_FISCR FDZCE bit; in function CPM_GetFpuIntStatus, get CPM_FISCR FDZC Status*/
    CPM_FPU_FUF = 4U,         /*!< in function CPM_FpuIntMode, set CPM_FISCR FUFCE bit; in function CPM_GetFpuIntStatus, get CPM_FISCR FUFC Status*/
    CPM_FPU_FOF = 8U,         /*!< in function CPM_FpuIntMode, set CPM_FISCR FOFCE bit; in function CPM_GetFpuIntStatus, get CPM_FISCR FOFC Status*/
    CPM_FPU_FID = 16U,         /*!< in function CPM_FpuIntMode, set CPM_FISCR FIDCE bit; in function CPM_GetFpuIntStatus, get CPM_FISCR FIDC Status*/
    CPM_FPU_FIX = 32U        /*!< in function CPM_FpuIntMode, set CPM_FISCR FIXCE bit; in function CPM_GetFpuIntStatus, get CPM_FISCR FIXC Status*/
} FPU_IntType;


/** @brief Cpm return type. */

typedef enum
{
    CPM_STATUS_SUCCESS = 0U,          /*!< CPM status success */
    CPM_STATUS_PARAM_INVALID = 1U     /*!< CPM status parameter invalid */
} CPM_RetType;

/**
 * @brief Get the value of CPM FISCR.
 *
 * This function returns FISCR value.
 *
 * @return uint32_t the value of the FISCR register.
 */
LOCAL_INLINE uint32_t CPM_HWA_GetFiscr(void)
{
    return CPM->FISCR;
}

/**
 * @brief Return CPM_FISCR FIOC value
 *
 * @return 0: No interrupt; 1: Interrupt occurred
 */
LOCAL_INLINE bool CPM_HWA_GetFpuFiocFlag(void)
{
    uint32_t u32TmpVal = CPM->FISCR;
    u32TmpVal = (u32TmpVal & CPM_FISCR_FIOC_MASK) >> CPM_FISCR_FIOC_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Return CPM_FISCR FDZC value
 *
 * @return 0: No interrupt; 1: Interrupt occurred
 */
LOCAL_INLINE bool CPM_HWA_GetFpuFdzcFlag(void)
{
    uint32_t u32TmpVal = CPM->FISCR;
    u32TmpVal = (u32TmpVal & CPM_FISCR_FDZC_MASK) >> CPM_FISCR_FDZC_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Return CPM_FISCR FOFC value
 *
 * @return 0: No interrupt; 1: Interrupt occurred
 */
LOCAL_INLINE bool CPM_HWA_GetFpuFofcFlag(void)
{
    uint32_t u32TmpVal = CPM->FISCR;
    u32TmpVal = (u32TmpVal & CPM_FISCR_FOFC_MASK) >> CPM_FISCR_FOFC_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Return CPM_FISCR FUFC value
 *
 * @return 0: No interrupt; 1: Interrupt occurred
 */
LOCAL_INLINE bool CPM_HWA_GetFpuFufcFlag(void)
{
    uint32_t u32TmpVal = CPM->FISCR;
    u32TmpVal = (u32TmpVal & CPM_FISCR_FUFC_MASK) >> CPM_FISCR_FUFC_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Return CPM_FISCR FIXC value
 *
 * @return 0: No interrupt; 1: Interrupt occurred
 */
LOCAL_INLINE bool CPM_HWA_GetFpuFixcFlag(void)
{
    uint32_t u32TmpVal = CPM->FISCR;
    u32TmpVal = (u32TmpVal & CPM_FISCR_FIXC_MASK) >> CPM_FISCR_FIXC_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Return CPM_FISCR FIDC value
 *
 * @return 0: No interrupt; 1: Interrupt occurred
 */
LOCAL_INLINE bool CPM_HWA_GetFpuFidcFlag(void)
{
    uint32_t u32TmpVal = CPM->FISCR;
    u32TmpVal = (u32TmpVal & CPM_FISCR_FIDC_MASK) >> CPM_FISCR_FIDC_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set FIOCE interrupt
 *
 * @param bEnable 1: enable interrupt 0: disable interrupt
 */
LOCAL_INLINE void CPM_HWA_SetFioceInt(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_FISCR_FIOCE_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_FISCR_FIOCE_SHIFT));
}

/**
 * @brief Set FDZCE interrupt
 *
 * @param bEnable 1: enable interrupt 0: disable interrupt
 */
LOCAL_INLINE void CPM_HWA_SetFdzceInt(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_FISCR_FDZCE_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_FISCR_FDZCE_SHIFT));
}

/**
 * @brief Set FOFCE interrupt
 *
 * @param bEnable 1: enable interrupt 0: disable interrupt
 */
LOCAL_INLINE void CPM_HWA_SetFofceInt(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_FISCR_FOFCE_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_FISCR_FOFCE_SHIFT));
}

/**
 * @brief Set FUFCE interrupt
 *
 * @param bEnable 1: enable interrupt 0: disable interrupt
 */
LOCAL_INLINE void CPM_HWA_SetFufceInt(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_FISCR_FUFCE_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_FISCR_FUFCE_SHIFT));
}

/**
 * @brief Set FIXCE interrupt
 *
 * @param bEnable 1: enable interrupt 0: disable interrupt
 */
LOCAL_INLINE void CPM_HWA_SetFixceInt(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_FISCR_FIXCE_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_FISCR_FIXCE_SHIFT));
}

/**
 * @brief Set FIDCE interrupt
 *
 * @param bEnable 1: enable interrupt 0: disable interrupt
 */
LOCAL_INLINE void CPM_HWA_SetFidceInt(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_FISCR_FIDCE_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_FISCR_FIDCE_SHIFT));
}

/**
 * @brief Set FISCR value
 *
 * @param u32Val the value want to set the register
 */
LOCAL_INLINE void CPM_HWA_SetFiscr(uint32_t u32Val)
{
    CPM->FISCR = u32Val;
}

/**
 * @brief Get the value of CPM TCMRCR.
 *
 * This function returns TCMRCR value.
 *
 * @return uint32_t the value of the TCMRCR register.
 */
LOCAL_INLINE uint32_t CPM_HWA_GetTcmrcr(void)
{
    return CPM->TCMRCR;
}

/**
 * @brief Set DTCM1 retry buffer force clear
 *
 * @param bEnable 1:Force clear DTCM1 retry buffer  0: No operation
 */
LOCAL_INLINE void CPM_HWA_SetDTCM1BufClear(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_TCMRCR_D1RBCLR_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_TCMRCR_D1RBCLR_SHIFT));
}

/**
 * @brief Set DTCM0 retry buffer force clear
 *
 * @param bEnable 1:Force clear DTCM0 retry buffer  0: No operation
 */
LOCAL_INLINE void CPM_HWA_SetDTCM0BufClear(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_TCMRCR_D0RBCLR_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_TCMRCR_D0RBCLR_SHIFT));
}

/**
 * @brief Set ITCM retry buffer force clear
 *
 * @param bEnable 1:Force clear ITCM retry buffer  0: No operation
 */
LOCAL_INLINE void CPM_HWA_SetITCMBufClear(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_TCMRCR_IRBCLR_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_TCMRCR_IRBCLR_SHIFT));
}

/**
 * @brief Set DTCM1 retry buffer invalid
 */
LOCAL_INLINE void CPM_HWA_SetDTCM1BufInvalid(void)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_TCMRCR_D1RBVLD_MASK)) | (1U << CPM_TCMRCR_D1RBCLR_SHIFT));
}

/**
 * @brief Set DTCM0 retry buffer invalid
 */
LOCAL_INLINE void CPM_HWA_SetDTCM0BufInvalid(void)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_TCMRCR_D0RBVLD_MASK)) | (1U << CPM_TCMRCR_D0RBCLR_SHIFT));
}

/**
 * @brief Set ITCM retry buffer invalid
 */
LOCAL_INLINE void CPM_HWA_SetITCMBufInvalid(void)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_TCMRCR_IRBVLD_MASK)) | (1U << CPM_TCMRCR_IRBCLR_SHIFT));
}

/**
 * @brief Set DTCM1 retry buffer timeout interrupt enable
 *
 * @param bEnable 1:Interrupt enable  0: No operation
 */
LOCAL_INLINE void CPM_HWA_SetDTCM1TimeoutInt(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_TCMRCR_D1RBIE_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_TCMRCR_D1RBIE_SHIFT));
}

/**
 * @brief Set DTCM0 retry buffer timeout interrupt enable
 *
 * @param bEnable 1:Interrupt enable  0: No operation
 */
LOCAL_INLINE void CPM_HWA_SetDTCM0TimeoutInt(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_TCMRCR_D0RBIE_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_TCMRCR_D0RBIE_SHIFT));
}

/**
 * @brief Set ITCM retry buffer timeout interrupt enable
 *
 * @param bEnable 1:Interrupt enable  0: No operation
 */
LOCAL_INLINE void CPM_HWA_SetITCMTimeoutInt(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_TCMRCR_IRBIE_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_TCMRCR_IRBIE_SHIFT));
}

/**
 * @brief Set DTCM1 retry buffer autoclear
 *
 * @param bEnable 1:Enable autoclear  0: No operation
 */
LOCAL_INLINE void CPM_HWA_SetDTCM1AutoClear(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_TCMRCR_D1RBAC_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_TCMRCR_D1RBAC_SHIFT));
}

/**
 * @brief Set DTCM0 retry buffer autoclear
 *
 * @param bEnable 1:Enable autoclear  0: No operation
 */
LOCAL_INLINE void CPM_HWA_SetDTCM0AutoClear(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_TCMRCR_D0RBAC_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_TCMRCR_D0RBAC_SHIFT));
}

/**
 * @brief Set ITCM retry buffer autoclear
 *
 * @param bEnable 1:Enable autoclear  0: No operation
 */
LOCAL_INLINE void CPM_HWA_SetITCMAutoClear(bool bEnable)
{
    CPM->FISCR = ((CPM->FISCR & (~CPM_TCMRCR_IRBAC_MASK)) | ((uint32_t)(bEnable ? 1U : 0U) << CPM_TCMRCR_IRBAC_SHIFT));
}

/** @}*/

#endif /* HWA_INCLUDE_HWA_CPM_H_ */
