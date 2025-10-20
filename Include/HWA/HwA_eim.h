/**
 * @file HwA_eim.h
 * @author Flagchip
 * @brief FC7xxx FCEim register API
 * @version 0.1.0
 * @date 2024-01-14
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
 *   Revision History:
 *
 *   Version     Date          Initials      CR#          Descriptions
 *   ---------   ----------    ------------  ----------   ---------------
 *   0.1.0       2024-01-14    qxw0100       N/A          FC7240 Eim first version
 *********************************************************************************/

#ifndef HWA_INCLUDE_HWA_EIM_H_
#define HWA_INCLUDE_HWA_EIM_H_
#include "device_header.h"
#define EIM_MAXCHANNEL  76U /*!< EIM max channel support */

/**
 * @defgroup HwA_eim
 * @ingroup HwA_eim
 * @{
 */

/** @brief EIM channel number configuration type */
typedef enum
{
    EIM_MAM0_S0                 = 0U,               /*!<  Channel 0 SCM Matrix Access Monitor Error Inection0(MAM0_S0)     */
    EIM_MAM0_S1                 = 1U,               /*!<  Channel 1 SCM Matrix Access Monitor Error Inection1(MAM0_S1)     */
    EIM_MAM0_S2                 = 2U,               /*!<  Channel 2 SCM Matrix Access Monitor Error Inection2(MAM0_S2)     */
    EIM_MAM0_S3                 = 4U,               /*!<  Channel 4 SCM Matrix Access Monitor Error Inection3(MAM0_S3)     */
    EIM_MAM0_S4                 = 5U,               /*!<  Channel 5 SCM Matrix Access Monitor Error Inection4(MAM0_S4)     */
    EIM_MAM0_S5                 = 7U,               /*!<  Channel 7 SCM Matrix Access Monitor Error Inection5(MAM0_S5)     */
    EIM_MAM0_S6                 = 8U,               /*!<  Channel 8 SCM Matrix Access Monitor Error Inection6(MAM0_S6)     */
    EIM_MAM0_S7                 = 9U,               /*!<  Channel 9 SCM Matrix Access Monitor Error Inection7(MAM0_S7)     */
    EIM_MAM0_S8                 = 10U,              /*!<  Channel 10 SCM Matrix Access Monitor Error Inection8(MAM0_S8)    */
    EIM_CPU0_AHBM               = 11U,              /*!<  Channel 11 SCM Matrix Access Monitor Error Inection9(CPU0_AHBM)  */
    EIM_CPU0_AHBP               = 12U,              /*!<  Channel 12 SCM Matrix Access Monitor Error Inection10(CPU0_AHBP) */
    EIM_HSM                     = 18U,              /*!<  Channel 18 SCM Matrix Access Monitor Error Inection12(HSM)       */
    EIM_DMA0                    = 19U,              /*!<  Channel 19 SCM Matrix Access Monitor Error Inection13(DMA0)      */
    EIM_CPU0_AHBS               = 21U,              /*!<  Channel 21 SCM Matrix Access Monitor Error Inection11(CPU0_AHBS) */
    EIM_CPU0_ITCM               = 24U,              /*!<  Channel 24 CPU0_ITCM                                             */
    EIM_CPU0_DTCM0              = 25U,              /*!<  Channel 25 CPU0_DTCM0                                            */
    EIM_CPU0_DTCM1              = 26U,              /*!<  Channel 26 CPU0_DTCM1                                            */
    EIM_SRAM0                   = 33U,              /*!<  Channel 33 SRAM0_INJECTION                                       */
    EIM_SRAM1                   = 34U,              /*!<  Channel 34 SRAM1_INJECTION                                       */
    EIM_CPU0DCACHE_DATA0_01     = 36U,              /*!<  Channel 36 CPU0_DCACHE_DATA0_01 Injection                        */
    EIM_CPU0DCACHE_DATA0_23     = 37U,              /*!<  Channel 37 CPU0_DCACHE_DATA0_23 Injection                        */
    EIM_CPU0DCACHE_DATA1_01     = 38U,              /*!<  Channel 38 CPU0_DCACHE_DATA1_01 Injection                        */
    EIM_CPU0DCACHE_DATA1_23     = 39U,              /*!<  Channel 39 CPU0_DCACHE_DATA1_23 Injection                        */
    EIM_CPU0DCACHE_TAG_01       = 40U,              /*!<  Channel 40 CPU0_DCACHE_TAG_01 Injection                          */
    EIM_CPU0DCACHE_TAG_23       = 41U,              /*!<  Channel 41 CPU0_DCACHE_TAG_23 Injection                          */
    EIM_CPU0ICACHE_DATA0        = 42U,              /*!<  Channel 42 CPU0_ICACHE_DATA0 Injection                           */
    EIM_CPU0ICACHE_DATA1        = 43U,              /*!<  Channel 43 CPU0_ICACHE_DATA1 Injection                           */
    EIM_CPU0ICACHE_TAG          = 44U,              /*!<  Channel 44 CPU0_ICACHE_TAG Injection                             */
    EIM_SCM_S5_DOWNSIZE         = 63U,              /*!<  Channel 63 SCM S5 64:32 DownSize Monitor Error Injection         */
    EIM_DMA0_CFG                = 65U,              /*!<  Channel 65 DMA0_CFG_ECC Injection                                */
    EIM_ROM_ECC                 = 67U,              /*!<  Channel 67 ROM_ECC Injection                                     */
    EIM_SCM_S5_DOWNSIZE_AHBS    = 68U,              /*!<  Channel 68 SCM S5 DownSize ECC Check with AHBS Error Injection   */
    EIM_CPU0AHBP_AHBS_MONITOR   = 70U,              /*!<  Channel 70 SCM CPU0 AHBP and AHBS gasket Monitor Error Injection */
    EIM_SCM_S8_DOWNSIZE_MONITOR = 75U,              /*!<  Channel 75 SCM S8 64:32 DownSize Monitor Error Injection         */
    EIM_RAM_DECODER_MONITOR     = 77U,              /*!<  Channel 77 RAM Decoder Monitor Error Injection                   */
	EIM_AFCB0_MONITOR           = 78U,              /*!<  Channel 78 AFCB0 Monitor Error Injection                         */
	EIM_AFCB1_MONITOR           = 79U,              /*!<  Channel 79 AFCB1 Monitor Error Injection                         */
	EIM_CPU0_OVERLAY_MONITOR    = 80U,              /*!<  Channel 80 CPU0 Overlay Monitor                                  */
	EIM_HSM_DRAM                = 82U,              /*!<  Channel 82 HSM DRAM ECC Error Injection                          */
	EIM_HSM_IRAM                = 83U,              /*!<  Channel 83 HSM IRAM ECC Error Injection                          */
} EIM_ChannelType;

/** @brief EIM Lockstep channel configuration type */
typedef enum
{
    EIM_CPU0_LOCKSTEP,           /*!<  CPU0 LOCKSTEP Injection   */
	EIM_CHNTYPE_RESVD,
	EIM_DMA0_LOCKSTEP,           /*!<  DMA0 LOCKSTEP Injection   */
} EIM_CPU_ChnType;

/** @brief EIM CPU monitor configuration type */
typedef enum
{
    EIM_MONITOR0,           /*!<  CPU0 LOCKSTEP monitor0 Injection   */
    EIM_MONITOR1,           /*!<  CPU0 LOCKSTEP monitor1 Injection   */
} EIM_MONType;

/** @brief Eim return type. */

typedef enum
{
    EIM_STATUS_SUCCESS = 0U,          /*!< EIM status success */
    EIM_STATUS_PARAM_INVALID = 1U     /*!< EIM status parameter invalid */
} EIM_RetType;

/**
 * @brief Select the EIM DWP mode
 *
 */
typedef enum
{
	EIM_CPU0ALLOWED_0   = 0U,               /**< cpu0 is allowed   */
    EIM_CPU0ALLOWED_1   = 1U,               /**< cpu0 is allowed   */
} EIM_DWPType;

/**
 * @brief Select error injection bus sel
 *
 */
typedef enum
{
    EIM_BUSREG0   = 0U,               /**< Sel bus REG0 to injection */
    EIM_BUSREG1   = 1U,               /**< Sel bus REG1 to injection */
    EIM_BUSREG2   = 2U,               /**< Sel bus REG2 to injection */
    EIM_BUSREG3   = 3U                /**< Sel bus REG3 to injection */
} EIM_BUSChnType;
/**
 * @brief Select the EIM InitType
 *
 */
typedef struct
{
    uint8_t u8EimChn;
    uint8_t u8BusSelIdx;
    uint8_t u8Attreenable;
    uint8_t u8AttrPosition;
    uint8_t u8Addreenable;
    uint8_t u8AddrePosition;
    uint8_t u8Data0enable;
    uint8_t u8Data0Val;
    uint8_t u8Data1enable;
    uint8_t u8Data1Val;
} EIM_InitType;

/**
 * @brief Select the CPU Lockstep InitType
 *
 */
typedef struct
{
    uint8_t u8CpuChn;
    uint8_t u8Monitor0Set;
    uint8_t u8Monitor0Clr;
    uint8_t u8Monitor1Set;
    uint8_t u8Monitor1Clr;
} EIM_CpuLockType;


/**
 * @brief Enable EIM Global Error Injection
 *
 */
LOCAL_INLINE void EIM_HWA_EnableGlobalErrorInjection(void)
{
    EIM->CR = 1U;
}

/**
 * @brief Disable EIM Global Error Injection
 *
 */
LOCAL_INLINE void EIM_HWA_DisableGlobalErrorInjection(void)
{
    EIM->CR &= ~(uint32_t) EIM_CR_GEIEN_MASK;
}

/**
 * @brief  get EIM channel N control register, N:0~82
 *
 * @return  EIM channel N control register value
 */
LOCAL_INLINE uint32_t EIM_HWA_Get_CtrlRegn(uint8_t idx)
{
    uint32_t u32RegValue;
    u32RegValue = EIM->CTRL_REG[idx];
    return u32RegValue;
}

/**
 * @brief  get EIM bus register, idx:0~3
 *
 * @return  EIM bus register value
 */
LOCAL_INLINE uint32_t EIM_HWA_Get_BUSRegn(uint8_t idx)
{
    uint32_t u32RegValue;
    u32RegValue = EIM->BUS_REG[idx];
    return u32RegValue;
}

/**
 * @brief Get EIM_CTRL_GEGn register DWP lock status
 * @param u8idx  index (0~82)
 * @return Lock status
 */
LOCAL_INLINE uint8_t EIM_HWA_GetCtrlDWPLockStatus(uint8_t u8idx)
{
    uint32_t u32RegValue;
    u32RegValue = EIM->CTRL_REG[u8idx];
    u32RegValue = (u32RegValue & EIM_CTRL_REG_DWP_LOCK_MASK) >> EIM_CTRL_REG_DWP_LOCK_SHIFT;
    return (uint8_t)((u32RegValue != 0U) ? true : false);
}

/**
 * @brief  set EIM_CTRL_GEGn register DWP lock mode, idx:0~76
 *
 * @param u8idx  index (0~82)
 * @param u8DwpMode DWP mode
 */
LOCAL_INLINE void EIM_HWA_Set_CtrlLockMode(uint8_t u8idx, uint8_t u8DwpMode)
{
    uint32_t u32Value = EIM->CTRL_REG[u8idx];
    EIM->CTRL_REG[u8idx] = ((u32Value & (~(uint32_t)EIM_CTRL_REG_DWP_MASK)) | EIM_CTRL_REG_DWP(u8DwpMode));
}

/**
 * @brief  set EIM_CTRL_GEGn register DWP lock status, idx:0~76
 *
 * @param u8idx  index (0~82)
 * @param u8Enable  enable or disable
 */
LOCAL_INLINE void EIM_HWA_CtrlRegnWritePermit(uint8_t u8idx)
{
    uint32_t u32Value = EIM->CTRL_REG[u8idx];
    EIM->CTRL_REG[u8idx] = (u32Value | EIM_CTRL_REG_DWP_LOCK_MASK);
}

/**
 * @brief  set eim channel N control register
 *
 * @param idx  index (0~82)
 * @param u32RegValue  access control value
 */
LOCAL_INLINE void EIM_HWA_Set_CtrlRegn(uint8_t idx, uint32_t u32RegValue)
{
    EIM->CTRL_REG[idx] = u32RegValue;
}

/**
 * @brief  set EIM CPU LOCKSTEP error injection register, idx:0~2
 *
 * @param idx  index (0~2)
 * @param u32RegValue  access control value
 */
LOCAL_INLINE void EIM_HWA_Set_CPULockstep(uint8_t idx, uint32_t u32RegValue)
{
    *((volatile uint32_t *)(&(EIM->CPU0_LOCKSTEP) + (int32_t)idx)) = u32RegValue;
}

/**
 * @brief  set EIM CPU LOCKSTEP error injection register, idx:0~2
 *
 * @param idx  index (0~2)
 * @return     access control value
 */
LOCAL_INLINE uint32_t EIM_HWA_Get_CPULockstep(uint8_t idx)
{
    return *((volatile uint32_t *)(&(EIM->CPU0_LOCKSTEP) + (int32_t)idx));
}

/**
 * @brief  set EIM bus register, idx:0~3
 *
 * @param idx  index (0~3)
 * @param u32RegValue  access control value
 */
LOCAL_INLINE void EIM_HWA_Set_BUSRegn(uint8_t idx, uint32_t u32RegValue)
{
    EIM->BUS_REG[idx] |= u32RegValue;
}


/** @}*/
#endif /* HWA_INCLUDE_HWA_EIM_H_ */
