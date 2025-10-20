/**
 * @file HwA_rgm.h
 * @author Flagchip
 * @brief FC7xxx RGM hardware access layer
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
   *   0.1.0       2024-01-12    Flagchip119    N/A          First version for FC7240
   ******************************************************************************** */
  
#ifndef _HWA_RGM_H_
#define _HWA_RGM_H_

#include "device_header.h"
/********* Local typedef ************/
/** @brief Rgm reset event */
typedef enum
{
    RGM_WAKEUP       = 0x00000001U,
    RGM_LVD          = 0x00000002U,
    RGM_CLKERR1      = 0x00000004U,
    RGM_CLKERR0      = 0x00000008U,
    RGM_FSCMU        = 0x00000010U,
    RGM_HSMWDOG      = 0x00000020U,
    RGM_PIN          = 0x00000040U,
    RGM_POR          = 0x00000080U,
    RGM_JTAG         = 0x00000100U,
    RGM_SYSAP        = 0x00000800U,
	RGM_WDOG1        = 0x00001000U,
    RGM_SACKERR      = 0x00002000U,
    RGM_CMU          = 0x00004000U,
    RGM_LBIST        = 0x00008000U,
    RGM_FSMERR       = 0x20000000U,
    RGM_PINRSTTOUT   = 0x40000000U,
    RGM_SYSRSTTOUT   = 0x80000000U
} RGM_ResetEventType;

/** @brief Rgm reset interrupt delay cycles type. */
typedef enum
{
    RGM_8_CLOCK_CYCLES      = 0x00U,
    RGM_32_CLOCK_CYCLES     = 0x01U,
    RGM_128_CLOCK_CYCLES    = 0x02U,
    RGM_512_CLOCK_CYCLES    = 0x03U
} RGM_ResetDelayType;

/** @brief Rgm reset interrupt event manger */
typedef enum
{
    RGM_INT_CLKERR0      = 0x0008U,
    RGM_INT_FCSMU        = 0x0010U,
    RGM_INT_WDG          = 0x0020U,
    RGM_INT_PIN          = 0x0040U,
    RGM_INT_JTAG         = 0x0100U,
    RGM_INT_CPULOC       = 0x0200U,
    RGM_INT_SW           = 0x0400U,
    RGM_INT_SYSAP        = 0x0800U,
    RGM_INT_WDOG1        = 0x1000U,
    RGM_INT_SACKERR      = 0x2000U,
    RGM_INT_CMU          = 0x4000U
} RGM_ResetIntMangerType;

/** @brief Select the Rgm CORE Write protection */
typedef enum
{
    RGM_WPB_ALL    = 0x00U,
    RGM_WPB_CPU0   = 0x01U,
    RGM_WPB_NOCORE = 0x04U
} RGM_WriteprotectionBitType;

/** @brief Rgm CPU0,1,2 related interrupt event manger */
typedef enum
{
    RGM_CPU_INT_LOCKUP = 0x01U,
    RGM_CPU_INT_SYSRST = 0x02U,
    RGM_CPU_INT_WDOG   = 0x04U,
    RGM_CPU_INT_INTM   = 0x08U,
    RGM_CPU_INT_SWRST  = 0x10U
} RGM_CPUIntMangerType;

/** @brief Rgm CPU0,1,2 software reset status */
typedef enum
{
    RGM_CPU_OUT_RST_UNDER = 0x00U,
    RGM_CPU_OUT_RST_OUT   = 0x01U
} RGM_CPUOutResetType;

/** @brief Rgm CPU0,1,2 reset event */
typedef enum
{
    RGM_CPU_WAKEUP       = 0x00000001U,
    RGM_CPU_LVD          = 0x00000002U,
    RGM_CPU_CLKERR1      = 0x00000004U,
    RGM_CPU_CLKERR0      = 0x00000008U,
    RGM_CPU_FSCMU        = 0x00000010U,
    RGM_CPU_HSMWDOG      = 0x00000020U,
    RGM_CPU_PIN          = 0x00000040U,
    RGM_CPU_POR          = 0x00000080U,
    RGM_CPU_JTAG         = 0x00000100U,
    RGM_CPU_SYSAP        = 0x00000800U,
    RGM_CPU_WDOG1        = 0x00001000U,
    RGM_CPU_SACKERR      = 0x00002000U,
    RGM_CPU_CMU          = 0x00004000U,
    RGM_CPU_LBIST        = 0x00008000U,
    RGM_CPU_LOCKUP       = 0x00010000U,
    RGM_CPU_SYSRST       = 0x00020000U,
    RGM_CPU_WDOG         = 0x00040000U,
    RGM_CPU_INTM         = 0x00080000U,
    RGM_CPU_SWRST        = 0x00100000U,
    RGM_CPU_FSMERR       = 0x20000000U,
    RGM_CPU_PINRSTTOUT   = 0x40000000U,
    RGM_CPU_SYSRSTTOUT   = 0x80000000U
} RGM_CPUResetEventType;

/** @brief Rgm CPU1,2 system reset enable flag */
typedef enum
{
    RGM_CPU_EN_LOCKUP       = 0x00010000U,
    RGM_CPU_EN_SYSRST       = 0x00020000U,
    RGM_CPU_EN_WDOG         = 0x00040000U,
    RGM_CPU_EN_INTM         = 0x00080000U,
    RGM_CPU_EN_SWRST        = 0x00100000U,
} RGM_CPUSystemRstMangerType;
/********* Local inline function ************/
/**
 * @brief Read last reset flag
 *
 * @return Last reset flag
 */
LOCAL_INLINE uint32_t RGM_HWA_ReadLastResetFlag(void)
{
    return (uint32_t)RGM->SRS;
}

/**
 * @brief Read all reset flag before POR,SSRS register is reset on POR only
 *
 * @return All reset flag before POR
 */
LOCAL_INLINE uint32_t RGM_HWA_ReadAllResetFlagBeforePOR(void)
{
    return (uint32_t)RGM->SSRS;
}

/**
 * @brief Read reset pin filter register
 *
 * @return Reset pin filter register
 */
LOCAL_INLINE uint32_t RGM_HWA_ReadResetPinFilterEnable(void)
{
    return (uint32_t)RGM->RSTFLT;
}

/**
 * @brief This api can clear reset flag of SSRS register which indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @param eReset Reset flag
 */
LOCAL_INLINE void RGM_HWA_ClearResetFlagAfterPOR(RGM_ResetEventType eReset)
{
    RGM->SSRS = (uint32_t)(eReset);
}

/**
 * @brief This api can clear all reset flag of SSRS register which indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 */
LOCAL_INLINE void RGM_HWA_ClearAllResetFlagAfterPOR(void)
{
    RGM->SSRS = (uint32_t)0xE000F9FFU;
}

/**
 * @brief Set reset pin filter bus clock filter width
 *
 * @param u8Value Bus clock filter width value
 */
LOCAL_INLINE void RGM_HWA_SetBusClockFilterWidth(uint8_t u8Value)
{
    uint32_t u32RegValue = RGM->RSTFLT;
    RGM->RSTFLT = (u32RegValue & ~(uint32_t)RGM_RSTFLT_RSTFLT_BUSW_MASK) | RGM_RSTFLT_RSTFLT_BUSW(u8Value);
}

/**
 * @brief Enable reset pin filter bus clock
 *
 */
LOCAL_INLINE void RGM_HWA_EnableBusClockFilter(void)
{
    RGM->RSTFLT |= (uint32_t)RGM_RSTFLT_RSTFLT_BUS_MASK;
}

/**
 * @brief Enable reset pin filter AON32K clock
 *
 */
LOCAL_INLINE void RGM_HWA_EnableAon32kClockFilter(void)
{
    RGM->RSTFLT |= (uint32_t)RGM_RSTFLT_RSTFLT_AON_MASK;
}

/**
 * @brief Enable reset pin filter AON32K low power clock
 *
 */
LOCAL_INLINE void RGM_HWA_EnableAon32kLPClockFilter(void)
{
    RGM->RSTFLT |= (uint32_t)RGM_RSTFLT_RSTFLT_AON_LP_MASK;
}

/**
 * @brief Clear reset pin filter bus clock filter width
 *
 */
LOCAL_INLINE void RGM_HWA_ClearBusClockFilterWidth(void)
{
    RGM->RSTFLT &= ~(uint32_t)RGM_RSTFLT_RSTFLT_BUSW_MASK;
}

/**
 * @brief Disable reset pin filter bus clock
 *
 */
LOCAL_INLINE void RGM_HWA_DisableBusClockFilter(void)
{
    RGM->RSTFLT &= ~(uint32_t)RGM_RSTFLT_RSTFLT_BUS_MASK;
}

/**
 * @brief Disable reset pin filter AON32K clock
 *
 */
LOCAL_INLINE void RGM_HWA_DisableAon32kClockFilter(void)
{
    RGM->RSTFLT &= ~(uint32_t)RGM_RSTFLT_RSTFLT_AON_MASK;
}

/**
 * @brief Disable reset pin filter AON32K low power clock
 *
 */
LOCAL_INLINE void RGM_HWA_DisableAon32kLPClockFilter(void)
{
    RGM->RSTFLT &= ~(uint32_t)RGM_RSTFLT_RSTFLT_AON_LP_MASK;
}

/**
 * @brief Set Reset delay
 *
 * @param eDelay Reset delay type
 */
LOCAL_INLINE void RGM_HWA_SetResetDelay(RGM_ResetDelayType eDelay)
{
    uint32_t u32RegValue = RGM->SRIE;
    RGM->SRIE = (u32RegValue & ~(uint32_t)RGM_SRIE_DELAY_MASK) | RGM_SRIE_DELAY(eDelay);
}

/**
 * @brief Clear Reset delay
 */
LOCAL_INLINE void RGM_HWA_ClearResetDelay(void)
{
    RGM->SRIE &= ~(uint32_t)RGM_SRIE_DELAY_MASK;
}

/**
 * @brief Enable global reset interrupt
 *
 */
LOCAL_INLINE void RGM_HWA_EnableGlobalResetInterrupt(void)
{
    RGM->SRIE |= (uint32_t)RGM_SRIE_GLOBAL_RIE_MASK;
}

/**
 * @brief Enable reset interrupt
 *
 * @param eResetInterrupt Reset interrupt type
 */
LOCAL_INLINE void RGM_HWA_EnableResetInterrupt(RGM_ResetIntMangerType eResetInterrupt)
{
    RGM->SRIE |= (uint32_t)((uint32_t)eResetInterrupt & (RGM_SRIE_CLKERR0_RIE_MASK | RGM_SRIE_WDG_RIE_MASK |
                 RGM_SRIE_PIN_RIE_MASK | RGM_SRIE_JTAG_RIE_MASK | RGM_SRIE_CPULOC_RIE_MASK | RGM_SRIE_SW_RIE_MASK |
                 RGM_SRIE_SYSAP_RIE_MASK | RGM_SRIE_WDOG1_RIE_MASK | RGM_SRIE_SACKERR_RIE_MASK));
}

/**
 * @brief Disable reset interrupt
 *
 * @param eResetInterrupt Reset interrupt type
 */
LOCAL_INLINE void RGM_HWA_DisableResetInterrupt(RGM_ResetIntMangerType eResetInterrupt)
{
    RGM->SRIE &= ~(uint32_t)((uint32_t)eResetInterrupt & (RGM_SRIE_CLKERR0_RIE_MASK | RGM_SRIE_WDG_RIE_MASK |
                 RGM_SRIE_PIN_RIE_MASK | RGM_SRIE_JTAG_RIE_MASK | RGM_SRIE_CPULOC_RIE_MASK | RGM_SRIE_SW_RIE_MASK |
                 RGM_SRIE_SYSAP_RIE_MASK | RGM_SRIE_WDOG1_RIE_MASK | RGM_SRIE_SACKERR_RIE_MASK));
}

/**
 * @brief Get enabling status of system reset
 *
 * @return Interrupt enabling status of system reset
 */
LOCAL_INLINE uint32_t RGM_HWA_GetResetInterrupt(void)
{
    return (uint32_t)(RGM->SRIE & (RGM_SRIE_CLKERR0_RIE_MASK | RGM_SRIE_WDG_RIE_MASK |
            RGM_SRIE_PIN_RIE_MASK | RGM_SRIE_GLOBAL_RIE_MASK | RGM_SRIE_JTAG_RIE_MASK | RGM_SRIE_CPULOC_RIE_MASK |
            RGM_SRIE_SW_RIE_MASK | RGM_SRIE_SYSAP_RIE_MASK | RGM_SRIE_WDOG1_RIE_MASK | RGM_SRIE_SACKERR_RIE_MASK));
}

/**
 * @brief Perform system reset.
 *
 */
LOCAL_INLINE void CM7_HWA_SystemReset(void)
{
    uint32 u32Temp;
    u32Temp = SCB->AIRCR;
    u32Temp &= ~(uint32)(SCB_AIRCR_VECTKEY_Msk);
    u32Temp |= (uint32)((((uint32_t)(((uint32_t)(0x5FAU))<<SCB_AIRCR_VECTKEY_Pos))&SCB_AIRCR_VECTKEY_Msk) |
               SCB_AIRCR_SYSRESETREQ_Msk | SCB_AIRCR_PRIGROUP_Msk);
    SCB->AIRCR = u32Temp;
}

/**
 * @brief Enable CPU0 interrupt
 *
 * @param eCPU0ResetInterrupt CPU0 related interrupt type
 */
LOCAL_INLINE void RGM_HWA_EnableCPU0InterruptFlag(RGM_CPUIntMangerType eCPU0ResetInterrupt)
{
    RGM->C0_CFG |= (uint32_t)((uint32_t)eCPU0ResetInterrupt & (RGM_C0_CFG_C0_SWRST_IE_MASK | RGM_C0_CFG_C0_INTM_IE_MASK | RGM_C0_CFG_C0_WDOG_IE_MASK |
                   RGM_C0_CFG_C0_SYSRST_IE_MASK | RGM_C0_CFG_C0_LOCKUP_IE_MASK));
}

/**
 * @brief Disable CPU0 interrupt
 *
 * @param eCPU0ResetInterrupt CPU0 related interrupt type
 */
LOCAL_INLINE void RGM_HWA_DisableCPU0InterruptFlag(RGM_CPUIntMangerType eCPU0ResetInterrupt)
{
    RGM->C0_CFG &= ~(uint32_t)((uint32_t)eCPU0ResetInterrupt & (RGM_C0_CFG_C0_SWRST_IE_MASK | RGM_C0_CFG_C0_INTM_IE_MASK | RGM_C0_CFG_C0_WDOG_IE_MASK |
                   RGM_C0_CFG_C0_SYSRST_IE_MASK | RGM_C0_CFG_C0_LOCKUP_IE_MASK));
}

/**
 * @brief Get enabling status of CPU0 core related reset
 *
 * @return Interrupt enabling status of CPU0 core related reset
 */
LOCAL_INLINE uint32_t RGM_HWA_GetCPU0ResetInterrupt(void)
{
    return (uint32_t)(RGM->C0_CFG & (RGM_C0_CFG_C0_SWRST_IE_MASK | RGM_C0_CFG_C0_INTM_IE_MASK | RGM_C0_CFG_C0_WDOG_IE_MASK |
            RGM_C0_CFG_C0_SYSRST_IE_MASK | RGM_C0_CFG_C0_LOCKUP_IE_MASK));
}

/**
 * @brief Get the CPU0 exit reset flag
 *
 * @return RGM_CPU_OUT_RST_UNDER CPU0 is under reset
 * @return RGM_CPU_OUT_RST_OUT CPU0 is out of reset
 */
LOCAL_INLINE RGM_CPUOutResetType RGM_HWA_GetCPU0OutResetFlag(void)
{
    uint8_t u8TmpVal = (uint8_t)(RGM->C0_RST & RGM_C0_RST_C0_OUT_OF_RST_MASK) >> RGM_C0_RST_C0_OUT_OF_RST_SHIFT;
    return (RGM_CPUOutResetType)u8TmpVal;
}

/**
 * @brief Issue a CPU0 software reset.
 *
 */
LOCAL_INLINE void RGM_HWA_CPU0SWReset(void)
{
    RGM->C0_RST |= (uint32_t)RGM_C0_RST_C0_SWRST_MASK;
}

/**
 * @brief Read CPU0 last reset flag
 *
 * @return CPU0 last reset flag
 */
LOCAL_INLINE uint32_t RGM_HWA_ReadCPU0LastResetFlag(void)
{
    return (uint32_t)RGM->C0_SRS;
}

/**
 * @brief Read CPU0 all reset flag before POR,SSRS register is reset on POR only
 *
 * @return CPU0 all reset flag before POR
 */
LOCAL_INLINE uint32_t RGM_HWA_ReadCPU0AllResetFlagBeforePOR(void)
{
    return (uint32_t)RGM->C0_SSRS;
}

/**
 * @brief This api can clear reset flag of RGM_C0_SSRS register which indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @param eReset Reset flag
 */
LOCAL_INLINE void RGM_HWA_ClearC0ResetFlagAfterPOR(RGM_CPUResetEventType eReset)
{
    RGM->C0_SSRS = (uint32_t)(eReset);
}

/**
 * @brief This api can clear all reset flag of SSRGM_C0_SSRSRS register which indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 */
LOCAL_INLINE void RGM_HWA_ClearC0AllResetFlagAfterPOR(void)
{
    RGM->C0_SSRS = (uint32_t)0xE01FF9FFU;
}
#endif /* #ifndef _HWA_RGM_H_ */
