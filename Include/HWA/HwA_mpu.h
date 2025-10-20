/**
 * @file HwA_mpu.h
 * @author Flagchip085
 * @brief  FC7xxx MPU hardware access layer
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
#ifndef _HWA_MPU_H_
#define _HWA_MPU_H_

#include "device_header.h"

/**
 * @brief  The MPU registers struct
 * 
 */
typedef struct {
    __I  uint32_t MPU_TYPE; /* TYPE, offset: 0x0 */
    __IO uint32_t MPU_CTRL; /* CTRL, offset: 0x4 */
    __IO uint32_t MPU_RNR;  /* RNR,  offset: 0x8 */
    __IO uint32_t MPU_RBAR; /* RBAR, offset: 0xC */
    __IO uint32_t MPU_RASR; /* RASR, offset: 0x10 */
} CORTEX_MPU_Type, *PCORTEX_MPU_Type;

/** mpu base Address */
#define CORTEX_MPU_BASE                              (0xE000ED90U)
#define CORTEX_MPU                                   ((CORTEX_MPU_Type *)CORTEX_MPU_BASE)


/** TYPE Bit Fields **/
#define CORTEX_MPU_TYPE_IREGION_MASK   0xFF0000U

#define CORTEX_MPU_TYPE_IREGION_SHIFT  16U

#define CORTEX_MPU_TYPE_IREGION_WIDTH  8U

#define CORTEX_MPU_TYPE_IREGION(x)     (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_TYPE_IREGION_SHIFT))&CORTEX_MPU_TYPE_IREGION_MASK)

#define CORTEX_MPU_TYPE_DREGION_MASK   0xFF00U

#define CORTEX_MPU_TYPE_DREGION_SHIFT  8U

#define CORTEX_MPU_TYPE_DREGION_WIDTH  8U

#define CORTEX_MPU_TYPE_DREGION(x)     (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_TYPE_DREGION_SHIFT))&CORTEX_MPU_TYPE_DREGION_MASK)

#define CORTEX_MPU_TYPE_SEPARATE_MASK  0x1U

#define CORTEX_MPU_TYPE_SEPARATE_SHIFT 0U

#define CORTEX_MPU_TYPE_SEPARATE_WIDTH 1U

#define CORTEX_MPU_TYPE_SEPARATE(x)    (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_TYPE_SEPARATE_SHIFT))&CORTEX_MPU_TYPE_SEPARATE_MASK)

/** TYPE Reg Mask **/

#define CORTEX_MPU_TYPE                0x00FFFF01U



/** CTRL Bit Fields **/

#define CORTEX_MPU_CTRL_RPRIVDEFENA_MASK 0x4U

#define CORTEX_MPU_CTRL_RPRIVDEFENA_SHIFT 2U

#define CORTEX_MPU_CTRL_RPRIVDEFENA_WIDTH 1U

#define CORTEX_MPU_CTRL_RPRIVDEFENA(x) (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_CTRL_RPRIVDEFENA_SHIFT))&CORTEX_MPU_CTRL_RPRIVDEFENA_MASK)

#define CORTEX_MPU_CTRL_HFNMIENA_MASK  0x2U

#define CORTEX_MPU_CTRL_HFNMIENA_SHIFT 1U

#define CORTEX_MPU_CTRL_HFNMIENA_WIDTH 1U

#define CORTEX_MPU_CTRL_HFNMIENA(x)    (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_CTRL_HFNMIENA_SHIFT))&CORTEX_MPU_CTRL_HFNMIENA_MASK)

#define CORTEX_MPU_CTRL_ENABLE_MASK    0x1U

#define CORTEX_MPU_CTRL_ENABLE_SHIFT   0U

#define CORTEX_MPU_CTRL_ENABLE_WIDTH   1U

#define CORTEX_MPU_CTRL_ENABLE(x)      (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_CTRL_ENABLE_SHIFT))&CORTEX_MPU_CTRL_ENABLE_MASK)

/** CTRL Reg Mask **/

#define CORTEX_MPU_CTRL                0x00000007U



/** RNR Bit Fields **/

#define CORTEX_MPU_RNR_REGION_MASK     0xFFu

#define CORTEX_MPU_RNR_REGION_SHIFT    0U

#define CORTEX_MPU_RNR_REGION_WIDTH    8U

#define CORTEX_MPU_RNR_REGION(x)       (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_RNR_REGION_SHIFT))&CORTEX_MPU_RNR_REGION_MASK)

/** MPU_RNR Reg Mask **/

#define CORTEX_MPU_RNR                 0x000000FFu



/** RBAR Bit Fields **/

#define CORTEX_MPU_RBAR_ADDR_MASK      0xFFFFFFE0U

#define CORTEX_MPU_RBAR_ADDR_SHIFT     5U

#define CORTEX_MPU_RBAR_ADDR_WIDTH     27U

#define CORTEX_MPU_RBAR_ADDR(x)        (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_RBAR_ADDR_SHIFT))&CORTEX_MPU_RBAR_ADDR_MASK)

#define CORTEX_MPU_RBAR_VALID_MASK     0x10U

#define CORTEX_MPU_RBAR_VALID_SHIFT    4U

#define CORTEX_MPU_RBAR_VALID_WIDTH    1U

#define CORTEX_MPU_RBAR_VALID(x)       (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_RBAR_VALID_SHIFT))&CORTEX_MPU_RBAR_VALID_MASK)

#define CORTEX_MPU_RBAR_REGION_MASK    0xFu

#define CORTEX_MPU_RBAR_REGION_SHIFT   0U

#define CORTEX_MPU_RBAR_REGION_WIDTH   4U

#define CORTEX_MPU_RBAR_REGION(x)      (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_RBAR_REGION_SHIFT))&CORTEX_MPU_RBAR_REGION_MASK)

/** RBAR Reg Mask **/

#define CORTEX_MPU_RBAR                0xFFFFFFFFu



/** RASR Bit Fields **/

#define CORTEX_MPU_RASR_ATTRS_MASK     0xFFFF0000U

#define CORTEX_MPU_RASR_ATTRS_SHIFT    16U

#define CORTEX_MPU_RASR_ATTRS_WIDTH    16U

#define CORTEX_MPU_RASR_ATTRS(x)       (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_RASR_ATTRS_SHIFT))&CORTEX_MPU_RASR_ATTRS_MASK)

#define CORTEX_MPU_RASR_XN_MASK        0x10000000U

#define CORTEX_MPU_RASR_XN_SHIFT       28U

#define CORTEX_MPU_RASR_XN_WIDTH       1U

#define CORTEX_MPU_RASR_XN(x)         (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_RASR_XN_SHIFT))&CORTEX_MPU_RASR_XN_MASK)

#define CORTEX_MPU_RASR_AP_MASK        0x7000000U

#define CORTEX_MPU_RASR_AP_SHIFT       24U

#define CORTEX_MPU_RASR_AP_WIDTH       3U

#define CORTEX_MPU_RASR_AP(x)         (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_RASR_AP_SHIFT))&CORTEX_MPU_RASR_AP_MASK)

#define CORTEX_MPU_RASR_TEX_MASK        0x380000U

#define CORTEX_MPU_RASR_TEX_SHIFT       19U

#define CORTEX_MPU_RASR_TEX_WIDTH       3U

#define CORTEX_MPU_RASR_TEX(x)         (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_RASR_TEX_SHIFT))&CORTEX_MPU_RASR_TEX_MASK)

#define CORTEX_MPU_RASR_S_MASK        0x40000U

#define CORTEX_MPU_RASR_S_SHIFT       18U

#define CORTEX_MPU_RASR_S_WIDTH       1U

#define CORTEX_MPU_RASR_S(x)         (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_RASR_S_SHIFT))&CORTEX_MPU_RASR_S_MASK)

#define CORTEX_MPU_RASR_C_MASK        0x20000U

#define CORTEX_MPU_RASR_C_SHIFT       17U

#define CORTEX_MPU_RASR_C_WIDTH       1U

#define CORTEX_MPU_RASR_C(x)         (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_RASR_C_SHIFT))&CORTEX_MPU_RASR_C_MASK)

#define CORTEX_MPU_RASR_B_MASK        0x10000U

#define CORTEX_MPU_RASR_B_SHIFT       16U

#define CORTEX_MPU_RASR_B_WIDTH       1U

#define CORTEX_MPU_RASR_B(x)         (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_RASR_B_SHIFT))&CORTEX_MPU_RASR_B_MASK)

#define CORTEX_MPU_RASR_SRD_MASK       0xFF00U

#define CORTEX_MPU_RASR_SRD_SHIFT      8U

#define CORTEX_MPU_RASR_SRD_WIDTH      8U

#define CORTEX_MPU_RASR_SRD(x)         (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_RASR_SRD_SHIFT))&CORTEX_MPU_RASR_SRD_MASK)

#define CORTEX_MPU_RASR_SIZE_MASK      0x3Eu

#define CORTEX_MPU_RASR_SIZE_SHIFT     1U

#define CORTEX_MPU_RASR_SIZE_WIDTH     5U

#define CORTEX_MPU_RASR_SIZE(x)        (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_RASR_SIZE_SHIFT))&CORTEX_MPU_RASR_SIZE_MASK)

#define CORTEX_MPU_RASR_ENABLE_MASK    0x1U

#define CORTEX_MPU_RASR_ENABLE_SHIFT   0U

#define CORTEX_MPU_RASR_ENABLE_WIDTH   1U

#define CORTEX_MPU_RASR_ENABLE(x)      (((uint32_t)(((uint32_t)(x))<<CORTEX_MPU_RASR_ENABLE_SHIFT))&CORTEX_MPU_RASR_ENABLE_MASK)

/** RASR Reg Mask **/

#define CORTEX_MPU_RASR                0xFFFFFF3Fu
#define MPU_RBAR_BASEADDR_MASK_U32     (0xFFFFFFE0u)
#define MPU_RBAR_VALID_REGION_MASK_U32 (0x1Fu)
#define MPU_EN_MASK_U32 ((uint32_t)(CORTEX_MPU_CTRL_HFNMIENA_MASK | CORTEX_MPU_CTRL_RPRIVDEFENA_MASK))


#define MPU_REGION_MASK_U32  ((uint32_t)0xFF)

/**
 * @brief get mpu type register
 * 
 * @return type value
 */
LOCAL_INLINE uint32_t  MPU_HWA_Get_Type(void)
{
   return CORTEX_MPU->MPU_TYPE;
}

/**
 * @brief disable fault exceptions
 * 
 * 
 */
LOCAL_INLINE void  MPU_HWA_Fault_Disable(void)
{
   SCB->SHCSR &= ~((uint32_t)SCB_SHCSR_MEMFAULTENA_Msk);
}

/**
 * @brief enable fault exceptions
 * 
 * 
 */
LOCAL_INLINE void  MPU_HWA_Fault_Enable(void)
{
	SCB->SHCSR |= (uint32_t)SCB_SHCSR_MEMFAULTENA_Msk;
}

/**
 * @brief set mpu control register
 * 
 * @param u32RegValue   the value write to register
 * @return LOCAL_INLINE 
 */
LOCAL_INLINE void  MPU_HWA_Set_CR(uint32_t u32RegValue)
{
   CORTEX_MPU->MPU_CTRL = u32RegValue;
}

/**
 * @brief set mpu number register
 * 
 * @param u32RegValue  the value write to register
 * @return LOCAL_INLINE 
 */
LOCAL_INLINE void  MPU_HWA_Set_NR(uint8_t u32RegValue)
{
   CORTEX_MPU->MPU_RNR  = (MPU_REGION_MASK_U32 & u32RegValue);
}

/**
 * @brief set mpu base address register
 * 
 * @param u32RegValue  the value write to register
 * @return LOCAL_INLINE 
 */
LOCAL_INLINE void  MPU_HWA_Set_BAR(uint32_t u32RegValue)
{
   CORTEX_MPU->MPU_RBAR = u32RegValue;
}


/**
 * @brief set mpu attribute and size register
 * 
 * @param u32RegValue the value write to registe
 * @return LOCAL_INLINE 
 */
LOCAL_INLINE void  MPU_HWA_Set_ASR(uint32_t u32RegValue)
{
   CORTEX_MPU->MPU_RASR  = u32RegValue;
}


#endif /* _HWA_MPU_H_ */

