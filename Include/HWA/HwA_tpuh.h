/**
 * @file HwA_tpuh.h
 * @author Flagchip
 * @brief FC7xxx TPUH hardware access layer
 * @version 0.1.0
 * @date 2024-1-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

#ifndef _HWA_TPUH_H_
#define _HWA_TPUH_H_

#include "device_header.h"
#if 1
/********* Local typedef ************/
/** @brief TPU TCR1 clock control mode type */
typedef enum
{
    TPUH_CLK_SRC_TCRCLK     = 0U,
    UTPUH_PDOWN_CNT_MODE    = 3U,
    TPUH_CLK_SRC_TPUCLKDIV2 = 4U,
    TPUH_CLK_SRC_TPUCLK     = 5U
} TPUH_TCR1ClkCtrlModeType;

/** @brief TPU angle tick gen clk type */
typedef enum
{
    TPUH_TCR1_PRESCAL_OUTPUT = 0U,
    TPUH_TCR2_PRESCAL_OUTPUT = 1U
} TPUH_AngleTickGenClkType;

/** @brief TPU Angle Mode Selection type */
typedef enum
{
    TPUH_TCR2_TIMEBASE_EAC_DISABLE          = 0U,
    TPUH_TOOTHSIGNAL_AS_TCRCLK_TOOTH_CH_0   = 1U,
    TPUH_TOOTHSIGNAL_AS_CH1INPUT_TOOTH_CH_1 = 2U,
    TPUH_TOOTHSIGNAL_AS_CH2INPUT_TOOTH_CH_2 = 3U
} TPUH_AngleModeSel;

/** @brief TPU Angle Mode Selection type */
typedef enum
{
    TPUH_TWO_SAMPLE_MODE_TPU_CLK_DIV2       = 0U,
    TPUH_TWO_SAMPLE_MODE_CH_CLK             = 1U,
    TPUH_INTEGRATOR_MODE_TPU_CLK_DIV2       = 2U,
    TPUH_INTEGRATOR_MODE_CH_CLK             = 3U
} TPUH_TCRClkFilterType;

/** @brief TPU TCR2 clock control mode0 type */
typedef enum
{
    TPUH_GATED_DIV8_CLK                              = 0U,
    TPUH_RISE_TRANSITION_INCREMENT_TCR2_PRESCALER    = 1U,
    TPUH_FALL_TRANSITION_INCREMENT_TCR2_PRESCALER    = 2U,
    TPUH_DIV8_CLK                                    = 4U,
    TPUH_UPDOWN_CNT_MODE                             = 5U,
    TPUH_FROZEN                                      = 7U
} TPUH_TCR1ClkCtrlMode0Type;

typedef enum
{
    TPUH_RSING_EDGE                         = 1U,
    TPUH_FALLING_EDGE                       = 2U,
    TPUH_BOTH_EDGES                         = 3U,
    TPUH_NO_EDGE                            = 6U,
} TPUH_TCR1ClkCtrlMode1Type;

/** @brief Missing Tooth Counter */
typedef enum
{
    TPUH_NOT_A_MISSING_TOOTH                = 0U,
    TPUH_ONE_MISSING_TOOTH                  = 1U,
    TPUH_TWO_MISSING_TOOTH                  = 2U,
    TPUH_THREE_MISSING_TOOTH                = 3U,
} TPUH_MissToothCntType;

/** @brief Channel Trigger Configuration */
typedef enum
{
    TPUH_DISABLED                                   = 0U,
    TPUH_ANY_EVENT_GATED_BY_MSRTSR                  = 2U,
    TPUH_HSA_EVENT_ON_FLEXCORE_MODE                 = 3U,
    TPUH_MRL1_EVENT_NOT_GATED_BY_MSR                = 4U,
    TPUH_MRL2_EVENT_NOT_GATED_BY_MSR                = 5U,
    TPUH_MRL1_OR_MRL2_EVENT_NOT_GATED_BY_MSR        = 6U,
    TPUH_MRL1_AND_MRL2_EVENT_NOT_GATED_BY_MSR       = 7U,
    TPUH_TDL1_OR_TDL2_EVENT_NOT_GATED_BY_TSR        = 8U,
    TPUH_TDL1_AND_TDL2_EVENT_NOT_GATED_BY_TSR       = 9U,
    TPUH_EVENT_EQUAL_TO_CH_DO_LEVEL                 = 10U,
    TPUH_EVENT_NEGATIVE_TO_CH_DO_LEVEL              = 11U,
    TPUH_EVENT_EQUAL_TO_CH_DO_PART1_LEVEL           = 12U,
    TPUH_EVENT_EQUAL_TO_CH_DO_PART2_LEVEL           = 13U,
    TPUH_EVENT_EQUAL_TO_CH_IND_LEVEL                = 14U,
    TPUH_EVENT_EQUAL_TO_CH_IND_LATCH_LEVEL          = 15U,
} TPUH_ChTrigCFGType;
#endif
/********* Local inline function ************/
/**
 * @brief Get service request status of specific channel
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetSRStatus(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->GCR_VSR & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get pin input status of specific channel
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetInputStatus(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->GCR_VIR & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get pin output status of specific channel
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetoutputStatus(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->GCR_VOR & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get pin output enable status of specific channel
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetoutputEnStatus(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->GCR_VOBR & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get MRL1 status of specific channel
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetMRL1Status(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->GCR_VM1R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get MRL2 status of specific channel
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetMRL2Status(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->GCR_VM2R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get TDL1 status of specific channel
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetTDL1Status(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->GCR_VT1R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get TDL2 status of specific channel
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetTDL2Status(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->GCR_VT2R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get MRL1 event status of specific channel
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetMRL1EventStatus(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->GCR_EM1R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get MRL2 event status of specific channel
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetMRL2EventStatus(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->GCR_EM2R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get TDL1 event status of specific channel
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetTDL1eventStatus(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->GCR_ET1R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get TDL2 event status of specific channel
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetTDL2eventStatus(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->GCR_ET2R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get HAS status of specific channel
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetHASStatus(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->GCR_VHSR & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get TCR1 prescaler.
 *
 */
LOCAL_INLINE uint32_t TPU_H_HWA_GetTCR1Prescaler(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_CR & TPU_H_TBR_CR_TCR1P_MASK) >> TPU_H_TBR_CR_TCR1P_SHIFT;
    return u32TmpVal;
}

/**
 * @brief Get TCR1 clock control.
 *
 */
LOCAL_INLINE TPUH_TCR1ClkCtrlModeType TPU_H_HWA_GetTCR1ClkControl(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_CR & TPU_H_TBR_CR_TCR1CTL_MASK) >> TPU_H_TBR_CR_TCR1CTL_SHIFT;
    return (TPUH_TCR1ClkCtrlModeType)u32TmpVal;
}

/**
 * @brief Get TCR2 prescaler.
 *
 */
LOCAL_INLINE uint32_t TPU_H_HWA_GetTCR2Prescaler(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_CR & TPU_H_TBR_CR_TCR2P_MASK) >> TPU_H_TBR_CR_TCR2P_SHIFT;
    return u32TmpVal;
}

/**
 * @brief Get Angle tick generator clock.
 *
 */
LOCAL_INLINE TPUH_AngleTickGenClkType TPU_H_HWA_GetATGC(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_CR & TPU_H_TBR_CR_ATGC_MASK) >> TPU_H_TBR_CR_ATGC_SHIFT;
    return (TPUH_AngleTickGenClkType)u32TmpVal;
}

/**
 * @brief Get Angle Mode Selection.
 *
 */
LOCAL_INLINE TPUH_AngleModeSel TPU_H_HWA_GetAM(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_CR & TPU_H_TBR_CR_AM_MASK) >> TPU_H_TBR_CR_AM_SHIFT;
    return (TPUH_AngleModeSel)u32TmpVal;
}

/**
 * @brief Get TCRCLK signal Filter Control.
 *
 */
LOCAL_INLINE TPUH_TCRClkFilterType TPU_H_HWA_GetTCRClkFilter(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_CR & TPU_H_TBR_CR_TCRCF_MASK) >> TPU_H_TBR_CR_TCRCF_SHIFT;
    return (TPUH_TCRClkFilterType)u32TmpVal;
}

/**
 * @brief Get TCR2 clock control.
 *
 */
LOCAL_INLINE TPUH_TCR1ClkCtrlMode0Type TPU_H_HWA_GetTCR2ClkControlAM0(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_CR & TPU_H_TBR_CR_TCR2CTL_MASK) >> TPU_H_TBR_CR_TCR2CTL_SHIFT;
    return (TPUH_TCR1ClkCtrlMode0Type)u32TmpVal;
}

/**
 * @brief Get TCR2 clock control.
 *
 */
LOCAL_INLINE TPUH_TCR1ClkCtrlMode1Type TPU_H_HWA_GetTCR2ClkControlAM1(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_CR & TPU_H_TBR_CR_TCR2CTL_MASK) >> TPU_H_TBR_CR_TCR2CTL_SHIFT;
    return (TPUH_TCR1ClkCtrlMode1Type)u32TmpVal;
}

/**
 * @brief Get TCR1 cnt value.
 *
 */
LOCAL_INLINE uint32_t TPU_H_HWA_GetTCR1CntVal(const TPU_H_Type *const pTPUH)
{
    return pTPUH->TBR_T1R;
}

/**
 * @brief Get TCR2 cnt value.
 *
 */
LOCAL_INLINE uint32_t TPU_H_HWA_GetTCR2CntVal(const TPU_H_Type *const pTPUH)
{
    return pTPUH->TBR_T2R;
}

/**
 * @brief Get last tooth indication.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_NotLastTooth(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_TPR & TPU_H_TBR_TPR_LAST_MASK) >> TPU_H_TBR_TPR_LAST_SHIFT;
    return (bool)((u32TmpVal == 0U) ? true : false);
}

/**
 * @brief Get missing tooth counter.
 *
 */
LOCAL_INLINE TPUH_MissToothCntType TPU_H_HWA_GetMissingTooth(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_TPR & TPU_H_TBR_TPR_MISSCNT_MASK) >> TPU_H_TBR_TPR_MISSCNT_SHIFT;
    return (TPUH_MissToothCntType)u32TmpVal;
}

/**
 * @brief Get last tooth indication.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_NoInsertTooth(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_TPR & TPU_H_TBR_TPR_IPH_MASK) >> TPU_H_TBR_TPR_IPH_SHIFT;
    return (bool)((u32TmpVal == 0U) ? true : false);
}

/**
 * @brief Get last tooth indication.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_NoForceEACHalt(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_TPR & TPU_H_TBR_TPR_HOLD_MASK) >> TPU_H_TBR_TPR_HOLD_SHIFT;
    return (bool)((u32TmpVal == 0U) ? true : false);
}

/**
 * @brief Get angle ticks number.
 *
 */
LOCAL_INLINE uint32_t TPU_H_HWA_GetAngleTicksVal(const TPU_H_Type *const pTPUH)
{
    return (pTPUH->TBR_TPR & TPU_H_TBR_TPR_TICKS_MASK) >> TPU_H_TBR_TPR_TICKS_SHIFT;
}

/**
 * @brief Get the integer part of TCR1 clocks in one Angle tick.
 *
 */
LOCAL_INLINE uint32_t TPU_H_HWA_GetIntergerPerAngleTick(const TPU_H_Type *const pTPUH)
{
    return (pTPUH->TBR_TRR & TPU_H_TBR_TRR_INTEGER_MASK) >> TPU_H_TBR_TRR_INTEGER_SHIFT;
}

/**
 * @brief Get the fraction part of TCR1 clocks in one Angle tick.
 *
 */
LOCAL_INLINE uint32_t TPU_H_HWA_GetFractionPerAngleTick(const TPU_H_Type *const pTPUH)
{
    return (pTPUH->TBR_TRR & TPU_H_TBR_TRR_FRACTION_MASK) >> TPU_H_TBR_TRR_FRACTION_SHIFT;
}

/**
 * @brief Get TCR1 overflow flag.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetTCR1Overflow(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_T1MR & TPU_H_TBR_T1MR_OVF_MASK) >> TPU_H_TBR_T1MR_OVF_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get TCR1 IRQ enable flag.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_TCR1IRQEnable(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_T1MR & TPU_H_TBR_T1MR_IRQ_EN_MASK) >> TPU_H_TBR_T1MR_IRQ_EN_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get the maximum value of TCR1 counter in TCR1 updown mode.
 *
 */
LOCAL_INLINE uint32_t TPU_H_HWA_GetTCR1MaxCnt(const TPU_H_Type *const pTPUH)
{
    return (pTPUH->TBR_T1MR & TPU_H_TBR_T1MR_MAX_MASK) >> TPU_H_TBR_T1MR_MAX_SHIFT;
}

/**
 * @brief Get TCR2 overflow flag.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_TCR2Overflow(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_T2MR & TPU_H_TBR_T2MR_OVF_MASK) >> TPU_H_TBR_T2MR_OVF_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get TCR2 IRQ enable flag.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_TCR2IRQEnable(const TPU_H_Type *const pTPUH)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->TBR_T2MR & TPU_H_TBR_T2MR_IRQ_EN_MASK) >> TPU_H_TBR_T2MR_IRQ_EN_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get the maximum value of TCR2 counter in TCR1 updown mode.
 *
 */
LOCAL_INLINE uint32_t TPU_H_HWA_GetTCR2MaxCnt(const TPU_H_Type *const pTPUH)
{
    return (pTPUH->TBR_T2MR & TPU_H_TBR_T2MR_MAX_MASK) >> TPU_H_TBR_T2MR_MAX_SHIFT;
}

/**
 * @brief Get channel HSA enable flag.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChHSAEnable(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].CR & TPU_H_CHn_CR_CHAE_MASK) >> TPU_H_CHn_CR_CHAE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set channel HSA enable or disable.
 *
 */
LOCAL_INLINE void TPU_H_HWA_SetChHSA(TPU_H_Type *const pTPUH, uint8_t u8Channel, bool benable)
{
    pTPUH->CH[u8Channel].CR = ((pTPUH->CH[u8Channel].CR & ~TPU_H_CHn_CR_CHAE_MASK) | TPU_H_CHn_CR_CHAE(benable));
}

/**
 * @brief Set channel event trigger dma enable or disable.
 *
 */
LOCAL_INLINE void TPU_H_HWA_SetChEventDMAEnable(TPU_H_Type *const pTPUH, uint8_t u8Channel, bool benable)
{
    pTPUH->CH[u8Channel].CR = ((pTPUH->CH[u8Channel].CR & ~TPU_H_CHn_CR_CDFD_MASK) | TPU_H_CHn_CR_CDFD(benable));
}

/**
 * @brief Set channel request Dma enable or disable.
 *
 */
LOCAL_INLINE void TPU_H_HWA_SetChReqDMAEnable(TPU_H_Type *const pTPUH, uint8_t u8Channel, bool benable)
{
    pTPUH->CH[u8Channel].CR = ((pTPUH->CH[u8Channel].CR & ~TPU_H_CHn_CR_CHDE_MASK) | TPU_H_CHn_CR_CHDE(benable));
}

/**
 * @brief Get channel HSR Dma request enable flag.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChDMAEnable(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].CR & TPU_H_CHn_CR_CHDE_MASK) >> TPU_H_CHn_CR_CHDE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set channel Sync isr from flexcore enable or disable.
 *
 */
LOCAL_INLINE void TPU_H_HWA_SetChSyncISR(TPU_H_Type *const pTPUH, uint8_t u8Channel, bool benable)
{
    pTPUH->CH[u8Channel].CR = ((pTPUH->CH[u8Channel].CR & ~TPU_H_CHn_CR_CHEE_MASK) | TPU_H_CHn_CR_CHEE(benable));
}

/**
 * @brief Get channel HSR event as interrupt enable flag.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChHSRISREnable(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].CR & TPU_H_CHn_CR_CHEE_MASK) >> TPU_H_CHn_CR_CHEE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set channel channel HSR event as interrupt enable or disable.
 *
 */
LOCAL_INLINE void TPU_H_HWA_SetChHSRISR(TPU_H_Type *const pTPUH, uint8_t u8Channel, bool benable)
{
    pTPUH->CH[u8Channel].CR = ((pTPUH->CH[u8Channel].CR & ~TPU_H_CHn_CR_CHEE_MASK) | TPU_H_CHn_CR_CHEE(benable));
}

/**
 * @brief Get channel trigger configuration.
 *
 */
LOCAL_INLINE TPUH_ChTrigCFGType TPU_H_HWA_GetChTrigCondition(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].CR & TPU_H_CHn_CR_CTC_MASK) >> TPU_H_CHn_CR_CTC_SHIFT;
    return (TPUH_ChTrigCFGType)u32TmpVal;
}

/**
 * @brief Set channel trigger configuration.
 *
 */
LOCAL_INLINE void TPU_H_HWA_SetChTrig(TPU_H_Type *const pTPUH, uint8_t u8Channel, TPUH_ChTrigCFGType etrgcfg)
{
    pTPUH->CH[u8Channel].CR = ((pTPUH->CH[u8Channel].CR & ~TPU_H_CHn_CR_CTC_MASK) | TPU_H_CHn_CR_CTC(etrgcfg));
}

/**
 * @brief Get channel trigger DMA enable.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChTrigDMAEnable(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].CR & TPU_H_CHn_CR_CDFD_MASK) >> TPU_H_CHn_CR_CDFD_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set channel trigger DMA enable.
 *
 */
LOCAL_INLINE void TPU_H_HWA_SetChTrigDMAEnable(TPU_H_Type *const pTPUH, uint8_t u8Channel, bool benable)
{
    pTPUH->CH[u8Channel].CR = ((pTPUH->CH[u8Channel].CR & ~TPU_H_CHn_CR_CDFD_MASK) | TPU_H_CHn_CR_CDFD(benable));
}

/**
 * @brief Get channel HSR index.
 *
 */
LOCAL_INLINE uint8 TPU_H_HWA_GetChHSRIdx(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].CR & TPU_H_CHn_CR_CHSR_MASK) >> TPU_H_CHn_CR_CHSR_SHIFT;
    return (uint8)u32TmpVal;
}

/**
 * @brief Get channel HSR index.
 *
 */
LOCAL_INLINE void TPU_H_HWA_SetChHSRIdx(TPU_H_Type *const pTPUH, uint8_t u8Channel, uint8_t u8HSRIdx)
{
    pTPUH->CH[u8Channel].CR = ((pTPUH->CH[u8Channel].CR & ~TPU_H_CHn_CR_CHSR_MASK) | TPU_H_CHn_CR_CHSR(u8HSRIdx));
}

/**
 * @brief Get channel event trigger interrupt status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChEventTrigISRStatus(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].SR & TPU_H_CHn_SR_CIS_MASK) >> TPU_H_CHn_SR_CIS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get channel host service request (HSR) status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChHSRStatus(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (uint8_t)(pTPUH->CH[u8Channel].SR & TPU_H_CHn_SR_CHRS_MASK) >> TPU_H_CHn_SR_CHRS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get HSA.
 *
 */
LOCAL_INLINE uint8 TPU_H_HWA_GetChHSAIdx(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].SR & TPU_H_CHn_SR_CHRI_MASK) >> TPU_H_CHn_SR_CHRI_SHIFT;
    return (uint8_t)u32TmpVal;
}


/**
 * @brief Get channel event as interrupt status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChDMAReq(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].SR & TPU_H_CHn_SR_CHDS_MASK) >> TPU_H_CHn_SR_CHDS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get channel trigger status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChTrigStatus(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].SR & TPU_H_CHn_SR_CTS_MASK) >> TPU_H_CHn_SR_CTS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get channel host service acknowledge (HSA) interrupt status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChHSAReqStatus(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].SR & TPU_H_CHn_SR_CHAS_MASK) >> TPU_H_CHn_SR_CHAS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear channel interrupt by event.
 *
 */
LOCAL_INLINE void TPU_H_HWA_ClearChEventISRFlg(TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    pTPUH->CH[u8Channel].SCR = TPU_H_CHn_SCR_CEIC_MASK;
}

/**
 * @brief Clear channel HSA.
 *
 */
LOCAL_INLINE void TPU_H_HWA_ClearChHSA(TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    pTPUH->CH[u8Channel].SCR = TPU_H_CHn_SCR_CHAC_MASK;
}

/**
 * @brief Clear channel HSR.
 *
 */
LOCAL_INLINE void TPU_H_HWA_ClearChHSR(TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    pTPUH->CH[u8Channel].SCR = TPU_H_CHn_SCR_CHRT_MASK;
}

/**
 * @brief Get channel service request.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChServiceReq(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].EFR & TPU_H_CHn_EFR_CSR_MASK) >> TPU_H_CHn_EFR_CSR_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get channel service request to HOST.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChServiceReqToHost(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].EFR & TPU_H_CHn_EFR_CHSR_MASK) >> TPU_H_CHn_EFR_CHSR_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get match recognition latch 1 event status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChMatchRecLatch1Event(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].EFR & TPU_H_CHn_EFR_EMRL1_MASK) >> TPU_H_CHn_EFR_EMRL1_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get match recognition latch 2 event status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChMatchRecLatch2Event(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].EFR & TPU_H_CHn_EFR_EMRL2_MASK) >> TPU_H_CHn_EFR_EMRL2_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get transition detect latch 1 event status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChTransDetectLatch1Event(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].EFR & TPU_H_CHn_EFR_ETDL1_MASK) >> TPU_H_CHn_EFR_ETDL1_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get transition detect latch 2 event status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChTransDetectLatch2Event(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].EFR & TPU_H_CHn_EFR_ETDL2_MASK) >> TPU_H_CHn_EFR_ETDL2_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get match recognition latch 1 enable status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChMatchRecLatch1En(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].EFR & TPU_H_CHn_EFR_MRLE1_MASK) >> TPU_H_CHn_EFR_MRLE1_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get match recognition latch 2 enable status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChMatchRecLatch2En(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].EFR & TPU_H_CHn_EFR_MRLE2_MASK) >> TPU_H_CHn_EFR_MRLE2_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get match recognition latch 1 enable status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChMatchRecLatch1Status(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].EFR & TPU_H_CHn_EFR_MRL1_MASK) >> TPU_H_CHn_EFR_MRL1_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get match recognition latch 2 enable status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChMatchRecLatch2Status(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].EFR & TPU_H_CHn_EFR_MRL2_MASK) >> TPU_H_CHn_EFR_MRL2_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get Transition Detect latch 1 enable status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChTransDetectLatch1Status(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].EFR & TPU_H_CHn_EFR_TDL1_MASK) >> TPU_H_CHn_EFR_TDL1_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get Transition Detect latch 2 enable status.
 *
 */
LOCAL_INLINE bool TPU_H_HWA_GetChTransDetectLatch2Status(const TPU_H_Type *const pTPUH, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUH->CH[u8Channel].EFR & TPU_H_CHn_EFR_TDL2_MASK) >> TPU_H_CHn_EFR_TDL2_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}


#endif /* #ifndef _HWA_TPUH_H_ */
