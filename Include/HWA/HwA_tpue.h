/**
 * @file HwA_tpue.h
 * @author Flagchip
 * @brief FC7xxx TPUE hardware access layer
 * @version 0.1.0
 * @date 2024-1-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

#ifndef _HWA_TPUE_H_
#define _HWA_TPUE_H_

#include "device_header.h"

/********* Local typedef ************/

/** @brief TPU channel digital filter control type */
typedef enum
{
    TPUE_TWO_SAMPLE_MODE    = 0U,
    TPUE_BYPASS_MODE        = 1U,
    TPUE_THREE_SAMPLE_MODE  = 2U,
    TPUE_CONTINUOUS_MODE    = 3U
} TPUE_FilterCtrlType;

/** @brief TPU filter clock source selection type */
typedef enum
{
    TPUE_TPU_CLK_DIV2 = 0U,
    TPUE_TPU_CLK      = 1U
} TPUE_FilterClkSrcType;

/** @brief TPU channel digital filter control type */
typedef enum
{
    TPUE_SYSCLK_DIV_1    = 0U,
    TPUE_SYSCLK_DIV_2    = 1U,
    TPUE_SYSCLK_DIV_4    = 2U,
    TPUE_SYSCLK_DIV_8    = 3U,
    TPUE_SYSCLK_DIV_16   = 4U,
    TPUE_SYSCLK_DIV_32   = 5U,
    TPUE_SYSCLK_DIV_64   = 6U,
    TPUE_SYSCLK_DIV_128  = 7U
} TPUE_FilterPrescalerCtrlType;

/** @brief TPU TCR1 clock control mode type */
typedef enum
{
    TPUE_TCR1CLK_CLK_SRC            = 0U,
    TPUE_TCR1CLK_UPDOWN_CNT_MODE    = 3U,
    TPUE_TCR1CLK_CLK_SRC_TPUCLKDIV2 = 4U,
    TPUE_TCR1CLK_SRC_TPUCLK         = 5U
} TPUE_TCR1ClkCtrlModeType;

/** @brief TPU angle tick gen clk type */
typedef enum
{
    TPUE_TCR1_PRESCAL_OUTPUT = 0U,
    TPUE_TCR2_PRESCAL_OUTPUT = 1U
} TPUE_AngleTickGenClkType;

/** @brief TPU Angle Mode Selection type */
typedef enum
{
    TPUE_TCR2_TIMEBASE_EAC_DISABLE          = 0U,
    TPUE_TOOTHSIGNAL_AS_TCRCLK_TOOTH_CH_0   = 1U,
    TPUE_TOOTHSIGNAL_AS_CH1INPUT_TOOTH_CH_1 = 2U,
    TPUE_TOOTHSIGNAL_AS_CH1INPUT_TOOTH_CH_2 = 3U
} TPUE_AngleModeSel;

/** @brief TPU Angle Mode Selection type */
typedef enum
{
    TPUE_TWO_SAMPLE_MODE_TPU_CLK_DIV2       = 0U,
    TPUE_TWO_SAMPLE_MODE_CH_CLK             = 1U,
    TPUE_INTEGRATOR_MODE_TPU_CLK_DIV2       = 2U,
    TPUE_INTEGRATOR_MODE_CH_CLK             = 3U
} TPUE_TCRClkFilterType;

/** @brief TPU TCR2 clock control mode0 type */
typedef enum
{
    TPUE_GATED_DIV8_CLK                              = 0U,
    TPUE_RISE_TRANSITION_INCREMENT_TCR2_PRESCALER    = 1U,
    TPUE_FALL_TRANSITION_INCREMENT_TCR2_PRESCALER    = 2U,
    TPUE_DIV8_CLK                                    = 4U,
    TPUE_UPDOWN_CNT_MODE                             = 5U,
    TPUE_FROZEN                                      = 7U
} TPUE_TCR1ClkCtrlMode0Type;

typedef enum
{
    TPUE_RSING_EDGE                         = 1U,
    TPUE_FALLING_EDGE                       = 2U,
    TPUE_BOTH_EDGES                         = 3U,
    TPUE_NO_EDGE                            = 6U,
} TPUE_TCR1ClkCtrlMode1Type;

/** @brief Missing Tooth Counter */
typedef enum
{
    TPUE_NOT_A_MISSING_TOOTH                = 0U,
    TPUE_ONE_MISSING_TOOTH                  = 1U,
    TPUE_TWO_MISSING_TOOTH                  = 2U,
    TPUE_THREE_MISSING_TOOTH                = 3U,
} TPUE_MissToothCntType;

/** @brief Channel Trigger Configuration */
typedef enum
{
    TPUE_DISABLED                                   = 0U,
    TPUE_ANY_EVENT_GATED_BY_MSRTSR                  = 2U,
    TPUE_HSA_EVENT_ON_FLEXCORE_MODE                 = 3U,
    TPUE_MRL1_EVENT_NOT_GATED_BY_MSR                = 4U,
    TPUE_MRL2_EVENT_NOT_GATED_BY_MSR                = 5U,
    TPUE_MRL1_OR_MRL2_EVENT_NOT_GATED_BY_MSR        = 6U,
    TPUE_MRL1_AND_MRL2_EVENT_NOT_GATED_BY_MSR       = 7U,
    TPUE_TDL1_OR_TDL2_EVENT_NOT_GATED_BY_TSR        = 8U,
    TPUE_TDL1_AND_TDL2_EVENT_NOT_GATED_BY_TSR       = 9U,
    TPUE_EVENT_EQUAL_TO_CH_DO_LEVEL                 = 10U,
    TPUE_EVENT_NEGATIVE_TO_CH_DO_LEVEL              = 11U,
    TPUE_EVENT_EQUAL_TO_CH_DO_PART1_LEVEL           = 12U,
    TPUE_EVENT_EQUAL_TO_CH_DO_PART2_LEVEL           = 13U,
    TPUE_EVENT_EQUAL_TO_CH_IND_LEVEL                = 14U,
    TPUE_EVENT_EQUAL_TO_CH_IND_LATCH_LEVEL          = 15U,
} TPUE_ChTrigCFGType;

/** @brief Filter Grade for 7 value in 1 loop */
typedef enum
{
    TPUE_FILTER_DISABLE             = 0U,
    TPUE_FILTER_LOW                 = 1U,
    TPUE_FILTER_MIDDLE              = 2U,
    TPUE_FILTER_HIGH                = 3U,
} TPUE_FilterGradeType;

/** @brief Channel event triggered interrupt priority */
typedef enum
{
    TPUE_PRIORITY_DISABLE             = 0U,
    TPUE_PRIORITY_LOW                 = 1U,
    TPUE_PRIORITY_MIDDLE              = 2U,
    TPUE_PRIORITY_HIGH                = 3U,
} TPUE_EventIntPriorityType;

/** @brief Channel time base selection of part 1.  */
typedef enum
{
    TPUE_GREATER_OR_EQUAL_CAPBASE_TCR1_MATCHBASE_TCR1             = 0U,
    TPUE_GREATER_OR_EQUAL_CAPBASE_TCR1_MATCHBASE_TCR2             = 1U,
    TPUE_GREATER_OR_EQUAL_CAPBASE_TCR2_MATCHBASE_TCR1             = 2U,
    TPUE_GREATER_OR_EQUAL_CAPBASE_TCR2_MATCHBASE_TCR2             = 3U,
    TPUE_EQUAL_ONLY_CAPBASE_TCR1_MATCHBASE_TCR1                   = 4U,
    TPUE_EQUAL_ONLY_CAPBASE_TCR1_MATCHBASE_TCR2                   = 5U,
    TPUE_EQUAL_ONLY_CAPBASE_TCR2_MATCHBASE_TCR1                   = 6U,
    TPUE_EQUAL_ONLY_CAPBASE_TCR2_MATCHBASE_TCR2                   = 7U,
} TPUE_TimeBaseSelctionType;

/** @brief Channel Input Pin Action Control.  */
typedef enum
{
    TPUE_NO_TRANSITIONS                                           = 0U,
    TPUE_DETECT_RISING_EDGE_ONLY                                  = 1U,
    TPUE_DETECT_FALLING_EDGE_ONLY                                 = 2U,
    TPUE_DETECT_EITHER_EDGE_ONLY                                  = 3U,
    TPUE_DETECT_SIGNAL_0_ON_MATCH                                 = 4U,
    TPUE_DETECT_SIGNAL_1_ON_MATCH                                 = 5U,
} TPUE_IPACType;

/** @brief Channel output Pin Action Control.  */
typedef enum
{
    TPUE_NO_CHANGE_OUTPUT                                         = 0U,
    TPUE_MATCH_SET_OUTPUT_HIGH                                    = 1U,
    TPUE_MATCH_SET_OUTPUT_LOW                                     = 2U,
    TPUE_MATCH_TOGGLE_OUTPUT                                      = 3U,
    TPUE_TRANSITION_SET_OUTPUT_HIGH                               = 4U,
    TPUE_TRANSITION_SET_OUTPUT_LOW                                = 5U,
    TPUE_TRANSITION_TOGGLE_OUTPUT                                 = 6U,
    TPUE_NO_CHANGE_OPAC                                           = 7U,
} TPUE_OPACType;

/** @brief PDCM Encoding.  */
typedef enum
{
    TPUE_EM_B_ST                                         = 0U,
    TPUE_EM_B_DT                                         = 1U,
    TPUE_EM_NB_ST                                        = 2U,
    TPUE_EM_NB_DT                                        = 3U,
    TPUE_M2_ST                                           = 4U,
    TPUE_M2_DT                                           = 5U,
    TPUE_BM_ST                                           = 6U,
    TPUE_BM_DT                                           = 7U,
    TPUE_M2_O_ST                                         = 8U,
    TPUE_M2_O_DT                                         = 9U,
    TPUE_SM_ST                                           = 12U,
    TPUE_SM_DT                                           = 13U,
    TPUE_SM_ST_E                                         = 14U,
} TPUE_PDCMEncodeType;

/********* Local inline function ************/
/**
 * @brief Get channel digital filter control
 *
 */
LOCAL_INLINE TPUE_FilterCtrlType TPU_E_HWA_GetFilterCtrl(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_CR & TPU_E_GCR_CR_CDFC_MASK) >> TPU_E_GCR_CR_CDFC_SHIFT;
    return (TPUE_FilterCtrlType)u32TmpVal;
}

/**
 * @brief Set channel digital filter control
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetFilterCtrl(TPU_E_Type *const pTPUE, TPUE_FilterCtrlType eControlMode)
{
    pTPUE->GCR_CR = (pTPUE->GCR_CR & ~TPU_E_GCR_CR_CDFC_MASK) | TPU_E_GCR_CR_CDFC(eControlMode);
}

/**
 * @brief Get filter clock source
 *
 */
LOCAL_INLINE TPUE_FilterClkSrcType TPU_E_HWA_GetFilterClkSrc(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_CR & TPU_E_GCR_CR_FCSS_MASK) >> TPU_E_GCR_CR_FCSS_SHIFT;
    return (TPUE_FilterClkSrcType)u32TmpVal;
}

/**
 * @brief Set filter clock source
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetFilterClkSrc(TPU_E_Type *const pTPUE, TPUE_FilterClkSrcType eClkSrc)
{
    pTPUE->GCR_CR = (pTPUE->GCR_CR & ~TPU_E_GCR_CR_FCSS_MASK) | TPU_E_GCR_CR_FCSS(eClkSrc);
}

/**
 * @brief Get filter prescaler clock control
 *
 */
LOCAL_INLINE TPUE_FilterPrescalerCtrlType TPU_E_HWA_GetFilterPrescaler(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_CR & TPU_E_GCR_CR_FPSCK_MASK) >> TPU_E_GCR_CR_FPSCK_SHIFT;
    return (TPUE_FilterPrescalerCtrlType)u32TmpVal;
}

/**
 * @brief Get filter prescaler clock control
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetFilterPrescaler(TPU_E_Type *const pTPUE, TPUE_FilterPrescalerCtrlType ePrescaler)
{
    pTPUE->GCR_CR = (pTPUE->GCR_CR & ~TPU_E_GCR_CR_FPSCK_MASK) | TPU_E_GCR_CR_FPSCK(ePrescaler);
}

/**
 * @brief Whether channel function is disabled in Stop mode
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetFuncDisableInStopMode(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_CR & TPU_E_GCR_CR_HALT_CH_MASK) >> TPU_E_GCR_CR_HALT_CH_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Enable channel function is disabled or normal in Stop mode
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetFuncDisableInStopMode(TPU_E_Type *const pTPUE, bool bEnable)
{
    pTPUE->GCR_CR = (pTPUE->GCR_CR & ~TPU_E_GCR_CR_HALT_CH_MASK) | TPU_E_GCR_CR_HALT_CH(bEnable);
}

/**
 * @brief Whether channel function is disabled in Stop mode
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetTimeBaseCntStopInStopMode(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_CR & TPU_E_GCR_CR_HALT_TB_MASK) >> TPU_E_GCR_CR_HALT_TB_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Enable channel function is disabled or normal in Stop mode
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetTimeBaseCntStopInStopMode(TPU_E_Type *const pTPUE, bool bEnable)
{
    pTPUE->GCR_CR = (pTPUE->GCR_CR & ~TPU_E_GCR_CR_HALT_TB_MASK) | TPU_E_GCR_CR_HALT_TB(bEnable);
}

/**
 * @brief Enable channel function is disabled or normal in Stop mode
 *
 */
LOCAL_INLINE void TPU_E_HWA_TrigReset(TPU_E_Type *const pTPUE)
{
    pTPUE->GCR_SRR = 0xFC005AFEU;
}

/**
 * @brief Get service request status of specific channel
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetSRStatus(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_VSR & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get pin input status of specific channel
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetInputStatus(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_VIR & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get pin output status of specific channel
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetoutputStatus(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_VOR & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get pin output enable status of specific channel
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetoutputEnStatus(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_VOBR & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get MRL1 status of specific channel
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetMRL1Status(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_VM1R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get MRL2 status of specific channel
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetMRL2Status(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_VM2R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get TDL1 status of specific channel
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetTDL1Status(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_VT1R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get TDL2 status of specific channel
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetTDL2Status(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_VT2R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get MRL1 event status of specific channel
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetMRL1EventStatus(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_EM1R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get MRL2 event status of specific channel
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetMRL2EventStatus(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_EM2R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get TDL1 event status of specific channel
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetTDL1eventStatus(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_ET1R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get TDL2 event status of specific channel
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetTDL2eventStatus(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_ET2R & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get HAS status of specific channel
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetHSRStatus(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_VHSR & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get Filter Grade
 *
 */
LOCAL_INLINE TPUE_FilterGradeType TPU_E_HWA_GetFilterGrade(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_AFGR & TPU_E_GCR_AFGR_FLT_GRD_MASK) >> TPU_E_GCR_AFGR_FLT_GRD_SHIFT;
    return (TPUE_FilterGradeType)u32TmpVal;
}

/**
 * @brief Set Filter Grade
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetFilterGrade(TPU_E_Type *const pTPUE, TPUE_FilterGradeType eGrade)
{
    pTPUE->GCR_AFGR = (pTPUE->GCR_AFGR & ~TPU_E_GCR_AFGR_FLT_GRD_MASK) | TPU_E_GCR_AFGR_FLT_GRD(eGrade);
}

/**
 * @brief Get Filter Grade setting results
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetFilterGradeCFGErrFlg(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_ASR & TPU_E_GCR_ASR_ERROR_MASK) >> TPU_E_GCR_ASR_ERROR_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear filter grade setting results
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearFilterGradeCFGErrFlg(TPU_E_Type *const pTPUE)
{
    pTPUE->GCR_ASR = (pTPUE->GCR_ASR & ~TPU_E_GCR_ASR_ERROR_MASK) | TPU_E_GCR_ASR_ERROR(1U);
}

/**
 * @brief Get endian configuration
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetEndianCFG(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_ASR & TPU_E_GCR_ASR_ENDIAN_MASK) >> TPU_E_GCR_ASR_ENDIAN_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set endian configuration
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetEndianCFG(TPU_E_Type *const pTPUE)
{
    pTPUE->GCR_ASR = (pTPUE->GCR_ASR & ~TPU_E_GCR_ASR_ENDIAN_MASK) | TPU_E_GCR_ASR_ENDIAN(1U);
}

/**
 * @brief Get channel function entry table select
 *
 */
LOCAL_INLINE uint8_t TPU_E_HWA_GetEntryFuncSel(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_AID & TPU_E_GCR_AID_ETCS_MASK) >> TPU_E_GCR_AID_ETCS_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Get channel function entry table condition
 *
 */
LOCAL_INLINE uint8_t TPU_E_HWA_GetEntryFuncCond(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_AID & TPU_E_GCR_AID_COND_MASK) >> TPU_E_GCR_AID_COND_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Get channel ID info
 *
 */
LOCAL_INLINE uint8_t TPU_E_HWA_GetChIDInfo(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->GCR_AID & TPU_E_GCR_AID_ID_MASK) >> TPU_E_GCR_AID_ID_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Get TCR1 prescaler.
 *
 */
LOCAL_INLINE uint8_t TPU_E_HWA_GetTCR1Prescaler(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_CR & TPU_E_TBR_CR_TCR1P_MASK) >> TPU_E_TBR_CR_TCR1P_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Get TCR1 prescaler.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetTCR1Prescaler(TPU_E_Type *const pTPUE, uint8_t u8Prescaler)
{
    pTPUE->TBR_CR = (pTPUE->TBR_CR & ~TPU_E_TBR_CR_TCR1P_MASK) | TPU_E_TBR_CR_TCR1P(u8Prescaler);
}

/**
 * @brief Get TCR1 clock control.
 *
 */
LOCAL_INLINE TPUE_TCR1ClkCtrlModeType TPU_E_HWA_GetTCR1ClkControl(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_CR & TPU_E_TBR_CR_TCR1CTL_MASK) >> TPU_E_TBR_CR_TCR1CTL_SHIFT;
    return (TPUE_TCR1ClkCtrlModeType)u32TmpVal;
}

/**
 * @brief Set TCR1 clock control.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetTCR1ClkControl(TPU_E_Type *const pTPUE, TPUE_TCR1ClkCtrlModeType eMode)
{
    pTPUE->TBR_CR = (pTPUE->TBR_CR & ~TPU_E_TBR_CR_TCR1CTL_MASK) | TPU_E_TBR_CR_TCR1CTL(eMode);
}

/**
 * @brief Get TCR2 prescaler.
 *
 */
LOCAL_INLINE uint8_t TPU_E_HWA_GetTCR2Prescaler(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_CR & TPU_E_TBR_CR_TCR2P_MASK) >> TPU_E_TBR_CR_TCR2P_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set TCR2 prescaler.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetTCR2Prescaler(TPU_E_Type *const pTPUE, uint8_t ePrescaler)
{
    pTPUE->TBR_CR = (pTPUE->TBR_CR & ~TPU_E_TBR_CR_TCR2P_MASK) | TPU_E_TBR_CR_TCR2P(ePrescaler);
}

/**
 * @brief Get Angle tick generator clock.
 *
 */
LOCAL_INLINE TPUE_AngleTickGenClkType TPU_E_HWA_GetATGC(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_CR & TPU_E_TBR_CR_ATGC_MASK) >> TPU_E_TBR_CR_ATGC_SHIFT;
    return (TPUE_AngleTickGenClkType)u32TmpVal;
}

/**
 * @brief Set Angle tick generator clock.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetATGC(TPU_E_Type *const pTPUE, TPUE_AngleTickGenClkType eSrc)
{
    pTPUE->TBR_CR = (pTPUE->TBR_CR & ~TPU_E_TBR_CR_ATGC_MASK) | TPU_E_TBR_CR_ATGC(eSrc);
}

/**
 * @brief Get Angle Mode Selection.
 *
 */
LOCAL_INLINE TPUE_AngleModeSel TPU_E_HWA_GetAM(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_CR & TPU_E_TBR_CR_AM_MASK) >> TPU_E_TBR_CR_AM_SHIFT;
    return (TPUE_AngleModeSel)u32TmpVal;
}

/**
 * @brief Set Angle Mode Selection.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetAM(TPU_E_Type *const pTPUE, TPUE_AngleModeSel eMode)
{
    pTPUE->TBR_CR = (pTPUE->TBR_CR & ~TPU_E_TBR_CR_AM_MASK) | TPU_E_TBR_CR_AM(eMode);
}

/**
 * @brief Get TCRCLK signal Filter Control.
 *
 */
LOCAL_INLINE TPUE_TCRClkFilterType TPU_E_HWA_GetTCRClkFilter(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_CR & TPU_E_TBR_CR_TCRCF_MASK) >> TPU_E_TBR_CR_TCRCF_SHIFT;
    return (TPUE_TCRClkFilterType)u32TmpVal;
}

/**
 * @brief Set TCRCLK signal Filter Control.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetTCRClkFilter(TPU_E_Type *const pTPUE, TPUE_TCRClkFilterType eMode)
{
    pTPUE->TBR_CR = (pTPUE->TBR_CR & ~TPU_E_TBR_CR_TCRCF_MASK) | TPU_E_TBR_CR_TCRCF(eMode);
}

/**
 * @brief Get TCR2 clock control.
 *
 */
LOCAL_INLINE TPUE_TCR1ClkCtrlMode0Type TPU_E_HWA_GetTCR2ClkControlAM0(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_CR & TPU_E_TBR_CR_TCR2CTL_MASK) >> TPU_E_TBR_CR_TCR2CTL_SHIFT;
    return (TPUE_TCR1ClkCtrlMode0Type)u32TmpVal;
}

/**
 * @brief Get TCR2 clock control.
 *
 */
LOCAL_INLINE TPUE_TCR1ClkCtrlMode1Type TPU_E_HWA_GetTCR2ClkControlAM1(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_CR & TPU_E_TBR_CR_TCR2CTL_MASK) >> TPU_E_TBR_CR_TCR2CTL_SHIFT;
    return (TPUE_TCR1ClkCtrlMode1Type)u32TmpVal;
}

/**
 * @brief Set TCR2 clock control.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetTCR2ClkControlAM1(TPU_E_Type *const pTPUE, TPUE_TCR1ClkCtrlMode1Type eMode)
{
    pTPUE->TBR_CR = (pTPUE->TBR_CR & ~TPU_E_TBR_CR_TCR2CTL_MASK) | TPU_E_TBR_CR_TCR2CTL(eMode);
}

/**
 * @brief Get TCR1 cnt value.
 *
 */
LOCAL_INLINE uint32_t TPU_E_HWA_GetTCR1CntVal(const TPU_E_Type *const pTPUE)
{
    return pTPUE->TBR_T1R;
}

/**
 * @brief Get TCR2 cnt value.
 *
 */
LOCAL_INLINE uint32_t TPU_E_HWA_GetTCR2CntVal(const TPU_E_Type *const pTPUE)
{
    return pTPUE->TBR_T2R;
}

/**
 * @brief Get last tooth indication.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_NotLastTooth(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_TPR & TPU_E_TBR_TPR_LAST_MASK) >> TPU_E_TBR_TPR_LAST_SHIFT;
    return (bool)((u32TmpVal == 0U) ? true : false);
}

/**
 * @brief Set last tooth indication.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetLastTooth(TPU_E_Type *const pTPUE, bool bEnable)
{
    pTPUE->TBR_TPR = (pTPUE->TBR_TPR & ~TPU_E_TBR_TPR_LAST_MASK) | TPU_E_TBR_TPR_LAST(bEnable);
}

/**
 * @brief Get missing tooth counter.
 *
 */
LOCAL_INLINE TPUE_MissToothCntType TPU_E_HWA_GetMissingTooth(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_TPR & TPU_E_TBR_TPR_MISSCNT_MASK) >> TPU_E_TBR_TPR_MISSCNT_SHIFT;
    return (TPUE_MissToothCntType)u32TmpVal;
}

/**
 * @brief Set missing tooth counter.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetMissingTooth(TPU_E_Type *const pTPUE, TPUE_MissToothCntType eCnt)
{
    pTPUE->TBR_TPR = (pTPUE->TBR_TPR & ~TPU_E_TBR_TPR_MISSCNT_MASK) | TPU_E_TBR_TPR_MISSCNT(eCnt);
}

/**
 * @brief Get last tooth indication.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_NoInsertTooth(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_TPR & TPU_E_TBR_TPR_IPH_MASK) >> TPU_E_TBR_TPR_IPH_SHIFT;
    return (bool)((u32TmpVal == 0U) ? true : false);
}

/**
 * @brief Set last tooth indication to exit halt mode.
 *
 */
LOCAL_INLINE void TPU_E_HWA_InsertPhyTooth(TPU_E_Type *const pTPUE)
{
    pTPUE->TBR_TPR = (pTPUE->TBR_TPR & ~TPU_E_TBR_TPR_IPH_MASK) | TPU_E_TBR_TPR_IPH(1U);
}

/**
 * @brief Get last tooth indication.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_NoForceEACHalt(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_TPR & TPU_E_TBR_TPR_HOLD_MASK) >> TPU_E_TBR_TPR_HOLD_SHIFT;
    return (bool)((u32TmpVal == 0U) ? true : false);
}

/**
 * @brief Get last tooth indication.
 *
 */
LOCAL_INLINE void TPU_E_HWA_HaltEAC(TPU_E_Type *const pTPUE)
{
    pTPUE->TBR_TPR = (pTPUE->TBR_TPR & ~TPU_E_TBR_TPR_HOLD_MASK) | TPU_E_TBR_TPR_HOLD(1U);
}

/**
 * @brief Get angle ticks number.
 *
 */
LOCAL_INLINE uint16_t TPU_E_HWA_GetAngleTicksVal(const TPU_E_Type *const pTPUE)
{
    return (uint16_t)(pTPUE->TBR_TPR & TPU_E_TBR_TPR_TICKS_MASK) >> TPU_E_TBR_TPR_TICKS_SHIFT;
}

/**
 * @brief Get angle ticks number.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetAngleTicksVal(TPU_E_Type *const pTPUE, uint16_t u16Tick)
{
    pTPUE->TBR_TPR = (pTPUE->TBR_TPR & ~TPU_E_TBR_TPR_TICKS_MASK) | TPU_E_TBR_TPR_TICKS(u16Tick);
}

/**
 * @brief Get the integer part of TCR1 clocks in one Angle tick.
 *
 */
LOCAL_INLINE uint32_t TPU_E_HWA_GetIntergerPerAngleTick(const TPU_E_Type *const pTPUE)
{
    return (pTPUE->TBR_TRR & TPU_E_TBR_TRR_INTEGER_MASK) >> TPU_E_TBR_TRR_INTEGER_SHIFT;
}

/**
 * @brief Set the integer part of TCR1 clocks in one Angle tick.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetIntergerPerAngleTick(TPU_E_Type *const pTPUE, uint16_t u16Integer)
{
    pTPUE->TBR_TRR = (pTPUE->TBR_TRR & ~TPU_E_TBR_TRR_INTEGER_MASK) | TPU_E_TBR_TRR_INTEGER(u16Integer);
}

/**
 * @brief Get the fraction part of TCR1 clocks in one Angle tick.
 *
 */
LOCAL_INLINE uint32_t TPU_E_HWA_GetFractionPerAngleTick(const TPU_E_Type *const pTPUE)
{
    return (pTPUE->TBR_TRR & TPU_E_TBR_TRR_FRACTION_MASK) >> TPU_E_TBR_TRR_FRACTION_SHIFT;
}

/**
 * @brief Set the fraction part of TCR1 clocks in one Angle tick.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetFractionPerAngleTick(TPU_E_Type *const pTPUE, uint16_t u16Fraction)
{
    pTPUE->TBR_TRR = (pTPUE->TBR_TRR & ~TPU_E_TBR_TRR_FRACTION_MASK) | TPU_E_TBR_TRR_FRACTION(u16Fraction);
}

/**
 * @brief Get TCR1 overflow flag.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetTCR1Overflow(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_T1MR & TPU_E_TBR_T1MR_OVF_MASK) >> TPU_E_TBR_T1MR_OVF_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear TCR1 overflow flag.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearTCR1Overflow(TPU_E_Type *const pTPUE)
{
    pTPUE->TBR_T1MR = (pTPUE->TBR_T1MR | TPU_E_TBR_T1MR_OVF_MASK);
}

/**
 * @brief Get TCR1 IRQ enable flag.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetTCR1OVFIRQEn(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_T1MR & TPU_E_TBR_T1MR_IRQ_EN_MASK) >> TPU_E_TBR_T1MR_IRQ_EN_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get TCR1 IRQ enable flag.
 *
 */
LOCAL_INLINE void TPU_E_HWA_EnableTCR1OVFIRQ(TPU_E_Type *const pTPUE, bool bEn)
{
    pTPUE->TBR_T1MR = (pTPUE->TBR_T1MR & ~TPU_E_TBR_T1MR_IRQ_EN_MASK) | TPU_E_TBR_T1MR_IRQ_EN(bEn);
}

/**
 * @brief Get the maximum value of TCR1 counter in TCR1 updown mode.
 *
 */
LOCAL_INLINE uint32_t TPU_E_HWA_GetTCR1MaxCnt(const TPU_E_Type *const pTPUE)
{
    return (pTPUE->TBR_T1MR & TPU_E_TBR_T1MR_MAX_MASK) >> TPU_E_TBR_T1MR_MAX_SHIFT;
}

/**
 * @brief Get the maximum value of TCR1 counter in TCR1 updown mode.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetTCR1MaxCnt(TPU_E_Type *const pTPUE, uint32_t u32MaxCnt)
{
    pTPUE->TBR_T1MR = (pTPUE->TBR_T1MR & ~TPU_E_TBR_T1MR_MAX_MASK) | TPU_E_TBR_T1MR_MAX(u32MaxCnt);
}

/**
 * @brief Get TCR2 overflow flag.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetTCR2Overflow(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_T2MR & TPU_E_TBR_T2MR_OVF_MASK) >> TPU_E_TBR_T2MR_OVF_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear TCR2 overflow flag.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearTCR2Overflow(TPU_E_Type *const pTPUE)
{
    pTPUE->TBR_T2MR = (pTPUE->TBR_T2MR | TPU_E_TBR_T2MR_OVF_MASK);
}

/**
 * @brief Get TCR2 IRQ enable flag.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetTCR2OVFIRQEnable(const TPU_E_Type *const pTPUE)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->TBR_T2MR & TPU_E_TBR_T2MR_IRQ_EN_MASK) >> TPU_E_TBR_T2MR_IRQ_EN_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Enable TCR2 IRQ enable flag.
 *
 */
LOCAL_INLINE void TPU_E_HWA_EnableTCR2OVFIRQ(TPU_E_Type *const pTPUE, bool bEn)
{
    pTPUE->TBR_T2MR = (pTPUE->TBR_T2MR & ~TPU_E_TBR_T2MR_IRQ_EN_MASK) | TPU_E_TBR_T2MR_IRQ_EN(bEn);
}

/**
 * @brief Get the maximum value of TCR2 counter in TCR1 updown mode.
 *
 */
LOCAL_INLINE uint32_t TPU_E_HWA_GetTCR2MaxCnt(const TPU_E_Type *const pTPUE)
{
    return (pTPUE->TBR_T2MR & TPU_E_TBR_T2MR_MAX_MASK) >> TPU_E_TBR_T2MR_MAX_SHIFT;
}

/**
 * @brief Set the maximum value of TCR2 counter in TCR2 updown mode.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetTCR2MaxCnt(TPU_E_Type *const pTPUE, uint32_t u32MaxCnt)
{
    pTPUE->TBR_T2MR = (pTPUE->TBR_T2MR & ~TPU_E_TBR_T2MR_MAX_MASK) | TPU_E_TBR_T2MR_MAX(u32MaxCnt);
}

/**
 * @brief Get channel event triggered interrupt enable flag.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChEventIntEnable(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR & TPU_E_CHn_CR_CIE_MASK) >> TPU_E_CHn_CR_CIE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Enable channel event triggered interrupt.
 *
 */
LOCAL_INLINE void TPU_E_HWA_EnableChEventInt(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEn)
{
    pTPUE->CH[u8Channel].CR = (pTPUE->CH[u8Channel].CR & ~TPU_E_CHn_CR_CIE_MASK) | TPU_E_CHn_CR_CIE(bEn);
}

/**
 * @brief Get channel event triggered interrupt priority.
 *
 */
LOCAL_INLINE TPUE_EventIntPriorityType TPU_E_HWA_GetChEventIntPriority(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR & TPU_E_CHn_CR_CPR_MASK) >> TPU_E_CHn_CR_CPR_SHIFT;
    return (TPUE_EventIntPriorityType)u32TmpVal;
}

/**
 * @brief Set channel event triggered interrupt priority.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetChEventIntPriority(TPU_E_Type *const pTPUE, uint8_t u8Channel, TPUE_EventIntPriorityType ePriority)
{
    pTPUE->CH[u8Channel].CR = (pTPUE->CH[u8Channel].CR & ~TPU_E_CHn_CR_CPR_MASK) | TPU_E_CHn_CR_CPR(ePriority);
}

/**
 * @brief Get channel Filter Bypass
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChFilterBypassEnable(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR & TPU_E_CHn_CR_CFB_MASK) >> TPU_E_CHn_CR_CFB_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set channel Filter Bypass
 *
 */
LOCAL_INLINE void TPU_E_HWA_OpenChFilter(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEn)
{
    pTPUE->CH[u8Channel].CR = (pTPUE->CH[u8Channel].CR & ~TPU_E_CHn_CR_CFB_MASK) | TPU_E_CHn_CR_CFB(bEn);
}

/**
 * @brief Get channel entry function
 *
 */
LOCAL_INLINE uint8_t TPU_E_HWA_GetChEntryFunc(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR & TPU_E_CHn_CR_CFS_MASK) >> TPU_E_CHn_CR_CFS_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set channel entry function
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetChEntryFunc(TPU_E_Type *const pTPUE, uint8_t u8Channel, uint8_t u8EntryFunc)
{
    pTPUE->CH[u8Channel].CR = (pTPUE->CH[u8Channel].CR & ~TPU_E_CHn_CR_CFS_MASK) | TPU_E_CHn_CR_CFS(u8EntryFunc);
}

/**
 * @brief Get channel entry table pin direction
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChEntryTblPinDirOutput(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR & TPU_E_CHn_CR_ETPD_MASK) >> TPU_E_CHn_CR_ETPD_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set channel entry table pin direction
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetChEntryTblPinDirOutput(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEn)
{
    pTPUE->CH[u8Channel].CR = (pTPUE->CH[u8Channel].CR & ~TPU_E_CHn_CR_ETPD_MASK) | TPU_E_CHn_CR_ETPD(bEn);
}

/**
 * @brief Get channel entry table condition select
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChEntryTblCondSelAlt(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR & TPU_E_CHn_CR_ECTS_MASK) >> TPU_E_CHn_CR_ECTS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set channel entry table condition select
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetChEntryTblCondSelAlt(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEn)
{
    pTPUE->CH[u8Channel].CR = (pTPUE->CH[u8Channel].CR & ~TPU_E_CHn_CR_ECTS_MASK) | TPU_E_CHn_CR_ECTS(bEn);
}

/**
 * @brief Get channel entry table flag1
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChEntryTblflag1(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR & TPU_E_CHn_CR_FLG1_MASK) >> TPU_E_CHn_CR_FLG1_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set channel entry table flag1
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetChEntryTblflag1(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEn)
{
    pTPUE->CH[u8Channel].CR = (pTPUE->CH[u8Channel].CR & ~TPU_E_CHn_CR_FLG1_MASK) | TPU_E_CHn_CR_FLG1(bEn);
}

/**
 * @brief Get channel entry table flag0
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChEntryTblflag0(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR & TPU_E_CHn_CR_FLG0_MASK) >> TPU_E_CHn_CR_FLG0_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set channel entry table flag0
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetChEntryTblflag0(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEn)
{
    pTPUE->CH[u8Channel].CR = (pTPUE->CH[u8Channel].CR & ~TPU_E_CHn_CR_FLG0_MASK) | TPU_E_CHn_CR_FLG0(bEn);
}

/**
 * @brief Get channel output polarity
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChOutputHigh(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR & TPU_E_CHn_CR_OPOL_MASK) >> TPU_E_CHn_CR_OPOL_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set channel output polarity
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetChOutputActiveHigh(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEn)
{
    pTPUE->CH[u8Channel].CR = (pTPUE->CH[u8Channel].CR & ~TPU_E_CHn_CR_OPOL_MASK) | TPU_E_CHn_CR_OPOL(bEn);
}

/**
 * @brief Get channel output disable
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChOutputDisable(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR & TPU_E_CHn_CR_ODIS_MASK) >> TPU_E_CHn_CR_ODIS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set channel output disable
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetChOutputDisable(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEn)
{
    pTPUE->CH[u8Channel].CR = (pTPUE->CH[u8Channel].CR & ~TPU_E_CHn_CR_ODIS_MASK) | TPU_E_CHn_CR_ODIS(bEn);
}

/**
 * @brief Get channel HSA index.
 *
 */
LOCAL_INLINE uint8_t TPU_E_HWA_GetChHSAIdx(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR & TPU_E_CHn_CR_CHSA_MASK) >> TPU_E_CHn_CR_CHSA_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set channel HSA index.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetChHSAIdx(TPU_E_Type *const pTPUE, uint8_t u8Channel, uint8_t u8HSAIdx)
{
    pTPUE->CH[u8Channel].CR = ((pTPUE->CH[u8Channel].CR & ~TPU_E_CHn_CR_CHSA_MASK) | TPU_E_CHn_CR_CHSA(u8HSAIdx));
}

/**
 * @brief Get channel event trigger interrupt status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChEventTrigISRStatus(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].SR & TPU_E_CHn_SR_CIS_MASK) >> TPU_E_CHn_SR_CIS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get channel host service request (HSR) status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChHSRStatus(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].SR & TPU_E_CHn_SR_CHRS_MASK) >> TPU_E_CHn_SR_CHRS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get Channel HSR Info & Index .
 *
 */
LOCAL_INLINE uint8_t TPU_E_HWA_GetChHSRIdx(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].SR & TPU_E_CHn_SR_CHRI_MASK) >> TPU_E_CHn_SR_CHRI_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Get channel event as interrupt status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChEventReqISRStatus(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].SR & TPU_E_CHn_SR_CEIS_MASK) >> TPU_E_CHn_SR_CEIS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get channel event as interrupt status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChDMAReq(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].SR & TPU_E_CHn_SR_CHDS_MASK) >> TPU_E_CHn_SR_CHDS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get channel trigger status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChTrigStatus(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].SR & TPU_E_CHn_SR_CTS_MASK) >> TPU_E_CHn_SR_CTS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get channel host service acknowledge (HSA) interrupt status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChHSAReqStatus(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].SR & TPU_E_CHn_SR_CHAS_MASK) >> TPU_E_CHn_SR_CHAS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear channel interrupt by event.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearChEventISRFlg(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].SCR = TPU_E_CHn_SCR_CISC_MASK;
}

/**
 * @brief Clear channel HSA Dma.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ChReqDMA(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].SCR = TPU_E_CHn_SCR_CHDT_MASK;
}

/**
 * @brief Clear channel HSA.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearChHSAISR(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].SCR = TPU_E_CHn_SCR_CHAT_MASK;
}

/**
 * @brief Clear channel HSR.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearChHSR(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].SCR = TPU_E_CHn_SCR_CHRC_MASK;
}

/**
 * @brief Get channel service request.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChServiceReq(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].EFR & TPU_E_CHn_EFR_CSR_MASK) >> TPU_E_CHn_EFR_CSR_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get channel service request to HOST.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChServiceReqToHost(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].EFR & TPU_E_CHn_EFR_CHSR_MASK) >> TPU_E_CHn_EFR_CHSR_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get match recognition latch 1 event status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChMatchRecLatch1Event(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].EFR & TPU_E_CHn_EFR_EMRL1_MASK) >> TPU_E_CHn_EFR_EMRL1_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get match recognition latch 2 event status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChMatchRecLatch2Event(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].EFR & TPU_E_CHn_EFR_EMRL2_MASK) >> TPU_E_CHn_EFR_EMRL2_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get transition detect latch 1 event status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChTransDetectLatch1Event(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].EFR & TPU_E_CHn_EFR_ETDL1_MASK) >> TPU_E_CHn_EFR_ETDL1_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get transition detect latch 2 event status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChTransDetectLatch2Event(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].EFR & TPU_E_CHn_EFR_ETDL2_MASK) >> TPU_E_CHn_EFR_ETDL2_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get match recognition latch 1 enable status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChMatchRecLatch1En(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].EFR & TPU_E_CHn_EFR_MRLE1_MASK) >> TPU_E_CHn_EFR_MRLE1_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get match recognition latch 2 enable status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChMatchRecLatch2En(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].EFR & TPU_E_CHn_EFR_MRLE2_MASK) >> TPU_E_CHn_EFR_MRLE2_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get match recognition latch 1 enable status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChMatchRecLatch1Status(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].EFR & TPU_E_CHn_EFR_MRL1_MASK) >> TPU_E_CHn_EFR_MRL1_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get match recognition latch 2 enable status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChMatchRecLatch2Status(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].EFR & TPU_E_CHn_EFR_MRL2_MASK) >> TPU_E_CHn_EFR_MRL2_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get Transition Detect latch 1 enable status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChTransDetectLatch1Status(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].EFR & TPU_E_CHn_EFR_TDL1_MASK) >> TPU_E_CHn_EFR_TDL1_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get Transition Detect latch 2 enable status.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChTransDetectLatch2Status(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].EFR & TPU_E_CHn_EFR_TDL2_MASK) >> TPU_E_CHn_EFR_TDL2_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get comparator selection for time base selection.
 *
 */
LOCAL_INLINE TPUE_TimeBaseSelctionType TPU_E_HWA_GetChTBS1(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR2 & TPU_E_CHn_CR2_TBS1_MASK) >> TPU_E_CHn_CR2_TBS1_SHIFT;
    return (TPUE_TimeBaseSelctionType)u32TmpVal;
}

/**
 * @brief Set comparator selection for time base selection.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetChTBS1(TPU_E_Type *const pTPUE, uint8_t u8Channel, TPUE_TimeBaseSelctionType eType)
{
    pTPUE->CH[u8Channel].CR2 = (pTPUE->CH[u8Channel].CR2 & ~TPU_E_CHn_CR2_TBS1_MASK) | TPU_E_CHn_CR2_TBS1(eType);
}

/**
 * @brief Get pin state input.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChPinStateInputHigh(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR2 & TPU_E_CHn_CR2_PSTI_MASK) >> TPU_E_CHn_CR2_PSTI_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get pin state output.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChPinStateOutputHigh(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR2 & TPU_E_CHn_CR2_PSTO_MASK) >> TPU_E_CHn_CR2_PSTO_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get pin request service sample.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChPinReqSrvSample(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR2 & TPU_E_CHn_CR2_PRSS_MASK) >> TPU_E_CHn_CR2_PRSS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get Input Pin Action Control of Part 1 .
 *
 */
LOCAL_INLINE TPUE_IPACType TPU_E_HWA_GetIPAC1(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR2 & TPU_E_CHn_CR2_IPAC1_MASK) >> TPU_E_CHn_CR2_IPAC1_SHIFT;
    return (TPUE_IPACType)u32TmpVal;
}

/**
 * @brief Set Input Pin Action Control of Part 1 .
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetIPAC1(TPU_E_Type *const pTPUE, uint8_t u8Channel, TPUE_IPACType eType)
{
    pTPUE->CH[u8Channel].CR2 = (pTPUE->CH[u8Channel].CR2 & ~TPU_E_CHn_CR2_IPAC1_MASK) | TPU_E_CHn_CR2_IPAC1(eType);
}

/**
 * @brief Get Output Buffer Enable.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetChOutputBufEn(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR2 & TPU_E_CHn_CR2_OBE_MASK) >> TPU_E_CHn_CR2_OBE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get Output Buffer Enable.
 *
 */
LOCAL_INLINE void TPU_E_HWA_EnableChOutputBuf(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEnable)
{
    pTPUE->CH[u8Channel].CR2 = (pTPUE->CH[u8Channel].CR2 & ~TPU_E_CHn_CR2_OBE_MASK) | TPU_E_CHn_CR2_OBE(bEnable);
}

/**
 * @brief Get Output Pin Action Control of Part 1.
 *
 */
LOCAL_INLINE TPUE_OPACType TPU_E_HWA_GetOPAC1(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR2 & TPU_E_CHn_CR2_OPAC1_MASK) >> TPU_E_CHn_CR2_OPAC1_SHIFT;
    return (TPUE_OPACType)u32TmpVal;
}

/**
 * @brief Set Input Pin Action Control of Part 2 .
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetOPAC1(TPU_E_Type *const pTPUE, uint8_t u8Channel, TPUE_OPACType eType)
{
    pTPUE->CH[u8Channel].CR2 = (pTPUE->CH[u8Channel].CR2 & ~TPU_E_CHn_CR2_OPAC1_MASK) | TPU_E_CHn_CR2_OPAC1(eType);
}

/**
 * @brief Get comparator selection for time base selection.
 *
 */
LOCAL_INLINE TPUE_TimeBaseSelctionType TPU_E_HWA_GetChTBS2(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR2 & TPU_E_CHn_CR2_TBS2_MASK) >> TPU_E_CHn_CR2_TBS2_SHIFT;
    return (TPUE_TimeBaseSelctionType)u32TmpVal;
}

/**
 * @brief Set comparator selection for time base selection.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetChTBS2(TPU_E_Type *const pTPUE, uint8_t u8Channel, TPUE_TimeBaseSelctionType eType)
{
    pTPUE->CH[u8Channel].CR2 = (pTPUE->CH[u8Channel].CR2 & ~TPU_E_CHn_CR2_TBS2_MASK) | TPU_E_CHn_CR2_TBS2(eType);
}

/**
 * @brief Get Input Pin Action Control of Part 2.
 *
 */
LOCAL_INLINE TPUE_IPACType TPU_E_HWA_GetIPAC2(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR2 & TPU_E_CHn_CR2_IPAC2_MASK) >> TPU_E_CHn_CR2_IPAC2_SHIFT;
    return (TPUE_IPACType)u32TmpVal;
}

/**
 * @brief Set Input Pin Action Control of Part 2.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetIPAC2(TPU_E_Type *const pTPUE, uint8_t u8Channel, TPUE_IPACType eType)
{
    pTPUE->CH[u8Channel].CR2 = (pTPUE->CH[u8Channel].CR2 & ~TPU_E_CHn_CR2_IPAC2_MASK) | TPU_E_CHn_CR2_IPAC2(eType);
}

/**
 * @brief Get Output Pin Action Control of Part 1.
 *
 */
LOCAL_INLINE TPUE_OPACType TPU_E_HWA_GetOPAC2(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].CR2 & TPU_E_CHn_CR2_OPAC2_MASK) >> TPU_E_CHn_CR2_OPAC2_SHIFT;
    return (TPUE_OPACType)u32TmpVal;
}

/**
 * @brief Set Input Pin Action Control of Part 2 .
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetOPAC2(TPU_E_Type *const pTPUE, uint8_t u8Channel, TPUE_OPACType eType)
{
    pTPUE->CH[u8Channel].CR2 = (pTPUE->CH[u8Channel].CR2 & ~TPU_E_CHn_CR2_OPAC2_MASK) | TPU_E_CHn_CR2_OPAC2(eType);
}

/**
 * @brief Clear sevice request write enable.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearSrvReqEn(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].MR = (pTPUE->CH[u8Channel].MR | TPU_E_CHn_MR_SRIE_MASK);
}

/**
 * @brief Get service request inhibit latch.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetSrvReqEn(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].MR & TPU_E_CHn_MR_SRI_MASK) >> TPU_E_CHn_MR_SRI_SHIFT;
    return (bool)((u32TmpVal == 0U) ? true : false);
}

/**
 * @brief Set service request inhibit latch.
 *
 */
LOCAL_INLINE void TPU_E_HWA_EnableSrvReq(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEn)
{
    if (bEn)
    {
        pTPUE->CH[u8Channel].MR = (pTPUE->CH[u8Channel].MR & ~TPU_E_CHn_MR_SRI_MASK) | TPU_E_CHn_MR_SRIE_MASK;
    }
    else
    {
        pTPUE->CH[u8Channel].MR = (pTPUE->CH[u8Channel].MR & TPU_E_CHn_MR_SRI_MASK) | TPU_E_CHn_MR_SRIE_MASK;
    }

}

/**
 * @brief Clear PDCM Write Enable.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearPDCMEn(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].MR = (pTPUE->CH[u8Channel].MR | TPU_E_CHn_MR_PDME_MASK);
}

/**
 * @brief Get Predefined Channel Mode.
 *
 */
LOCAL_INLINE uint8_t TPU_E_HWA_GetPDCM(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].MR & TPU_E_CHn_MR_PDCM_MASK) >> TPU_E_CHn_MR_PDCM_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set Predefined Channel Mode.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetPDCM(TPU_E_Type *const pTPUE, uint8_t u8Channel, TPUE_PDCMEncodeType eMode)
{
    pTPUE->CH[u8Channel].MR = (pTPUE->CH[u8Channel].MR & ~TPU_E_CHn_MR_PDCM_MASK) | TPU_E_CHn_MR_PDCM(eMode) | TPU_E_CHn_MR_PDME_MASK;
}

/**
 * @brief Get transition continuous capture enable.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetTransContinueEn(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].MR & TPU_E_CHn_MR_TCCE_MASK) >> TPU_E_CHn_MR_TCCE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set Predefined Channel Mode.
 *
 */
LOCAL_INLINE void TPU_E_HWA_EnableTransContinue(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEn)
{
    pTPUE->CH[u8Channel].MR = (pTPUE->CH[u8Channel].MR & ~TPU_E_CHn_MR_TCCE_MASK) | TPU_E_CHn_MR_TCCE(bEn);
}

/**
 * @brief Clear UDCM Write Enable.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearUDCMWriteEn(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].MR = (pTPUE->CH[u8Channel].MR | TPU_E_CHn_MR_UDME_MASK);
}

/**
 * @brief Get User Defined Channel Mode.
 *
 */
LOCAL_INLINE uint16_t TPU_E_HWA_GetUDCM(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].MR & TPU_E_CHn_MR_UDCM_MASK) >> TPU_E_CHn_MR_UDCM_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set User Defined Channel Mode.
 *
 */
LOCAL_INLINE void TPU_E_HWA_EnableUDCM(TPU_E_Type *const pTPUE, uint8_t u8Channel, uint16_t u16Mode)
{
    pTPUE->CH[u8Channel].MR = (pTPUE->CH[u8Channel].MR & ~TPU_E_CHn_MR_UDCM_MASK) | TPU_E_CHn_MR_UDCM(u16Mode) | TPU_E_CHn_MR_UDME_MASK;
}

/**
 * @brief Clear Match Configuration Enable part1.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearMatchEn1(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].ER1 = (pTPUE->CH[u8Channel].ER1 | TPU_E_CHn_ER1_ERW_MASK);
}

/**
 * @brief Get User Defined Channel Mode part1.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetMatchEn(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].ER1 & TPU_E_CHn_ER1_MEF_MASK) >> TPU_E_CHn_ER1_MEF_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set User Defined Channel Mode.
 *
 */
LOCAL_INLINE void TPU_E_HWA_EnableMatch(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEn)
{
    pTPUE->CH[u8Channel].ER1 = (pTPUE->CH[u8Channel].ER1 & ~TPU_E_CHn_ER1_MEF_MASK) | TPU_E_CHn_ER1_MEF(bEn);
}

/**
 * @brief Set ER1 value for match.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetMatchER1(TPU_E_Type *const pTPUE, uint8_t u8Channel, uint32_t u32ER1)
{
    uint32_t u32Temp;
    u32Temp = pTPUE->CH[u8Channel].ER1 | TPU_E_CHn_ER1_ERS_MASK;
    pTPUE->CH[u8Channel].ER1 = (u32Temp & ~TPU_E_CHn_ER1_ER1_MASK) | TPU_E_CHn_ER1_ER1(u32ER1) | TPU_E_CHn_ER1_ERW_MASK;
}

/**
 * @brief Set ER1 value for capture.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetCaptureER1(TPU_E_Type *const pTPUE, uint8_t u8Channel, uint32_t u32ER1)
{
    uint32_t u32Temp;
    u32Temp = (pTPUE->CH[u8Channel].ER1 & ~TPU_E_CHn_ER1_ERS_MASK) | TPU_E_CHn_ER1_ERS(0U);
    pTPUE->CH[u8Channel].ER1 = (u32Temp & ~TPU_E_CHn_ER1_ER1_MASK) | TPU_E_CHn_ER1_ER1(u32ER1) | TPU_E_CHn_ER1_ERW_MASK;
}

/**
 * @brief Get Capture/Match Select for Value of ER1/ER2.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetMatchSelForERx(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].ER1 & TPU_E_CHn_ER1_ERS_MASK) >> TPU_E_CHn_ER1_ERS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get ER1 value.
 *
 */
LOCAL_INLINE uint32_t TPU_E_HWA_GetER1Val(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].ER1 & TPU_E_CHn_ER1_ER1_MASK) >> TPU_E_CHn_ER1_ER1_SHIFT;
    return u32TmpVal;
}

/**
 * @brief Get ER1 value.
 *
 */
LOCAL_INLINE uint32_t TPU_E_HWA_GetCaptureER1Val(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;
    pTPUE->CH[u8Channel].ER1 = (pTPUE->CH[u8Channel].ER1 & ~TPU_E_CHn_ER1_ERS_MASK) | TPU_E_CHn_ER1_ERS(0U);
    u32TmpVal = (pTPUE->CH[u8Channel].ER1 & TPU_E_CHn_ER1_ER1_MASK) >> TPU_E_CHn_ER1_ER1_SHIFT;
    return u32TmpVal;
}

/**
 * @brief Set ER1 value.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetER1(TPU_E_Type *const pTPUE, uint8_t u8Channel, uint32_t u32ER1)
{
    pTPUE->CH[u8Channel].ER1 = (pTPUE->CH[u8Channel].ER1 & ~TPU_E_CHn_ER1_ER1_MASK) | TPU_E_CHn_ER1_ER1(u32ER1) | TPU_E_CHn_ER1_ERW_MASK;
}

/**
 * @brief Clear Match Configuration Enable part2.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearMatchEn2(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].ER2 = (pTPUE->CH[u8Channel].ER2 | TPU_E_CHn_ER2_ERW_MASK);
}

/**
 * @brief Get ER2 value.
 *
 */
LOCAL_INLINE uint32_t TPU_E_HWA_GetER2Val(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].ER2 & TPU_E_CHn_ER2_ER2_MASK) >> TPU_E_CHn_ER2_ER2_SHIFT;
    return u32TmpVal;
}

/**
 * @brief Get ER2 value.
 *
 */
LOCAL_INLINE uint32_t TPU_E_HWA_GetCaptureER2Val(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;
    pTPUE->CH[u8Channel].ER1 = (pTPUE->CH[u8Channel].ER1 & ~TPU_E_CHn_ER1_ERS_MASK);
    u32TmpVal = (pTPUE->CH[u8Channel].ER2 & TPU_E_CHn_ER2_ER2_MASK) >> TPU_E_CHn_ER2_ER2_SHIFT;
    return u32TmpVal;
}

/**
 * @brief Set ER2 value.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetER2(TPU_E_Type *const pTPUE, uint8_t u8Channel, uint32_t u32ER2)
{
    pTPUE->CH[u8Channel].ER2 = (pTPUE->CH[u8Channel].ER2 & ~TPU_E_CHn_ER2_ER2_MASK) | TPU_E_CHn_ER2_ER2(u32ER2) | TPU_E_CHn_ER2_ERW_MASK;
}

/**
 * @brief Clear Match1 Configuration Enable.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearMatch1CFGFlg(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].ECR = TPU_E_CHn_ECR_MRE1_CLR_MASK;
}

/**
 * @brief Clear Match1 event Enable.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearMatch1Event(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].ECR = TPU_E_CHn_ECR_MRL1_CLR_MASK;
}

/**
 * @brief Clear transition detect1 Enable.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearTransDetect1Event(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].ECR = TPU_E_CHn_ECR_TDL1_CLR_MASK;
}

/**
 * @brief Clear Match2 Configuration Enable.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearMatch2CFGFlg(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].ECR = TPU_E_CHn_ECR_MRE2_CLR_MASK;
}

/**
 * @brief Clear Match2 event Enable.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearMatch2Event(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].ECR = TPU_E_CHn_ECR_MRL2_CLR_MASK;
}

/**
 * @brief Clear transition detect2 Enable.
 *
 */
LOCAL_INLINE void TPU_E_HWA_ClearTransDetect2Event(TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    pTPUE->CH[u8Channel].ECR = TPU_E_CHn_ECR_TDL2_CLR_MASK;
}

/**
 * @brief Get output user control, high or low select.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetOutputSelHigh(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].OCR & TPU_E_CHn_OCR_OUT_HIS_MASK) >> TPU_E_CHn_OCR_OUT_HIS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear output user control.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetOutputSelHigh(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEn)
{
    pTPUE->CH[u8Channel].OCR = TPU_E_CHn_OCR_OUT_HIS(bEn);
}

/**
 * @brief Get output user control, select OPAC1.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetOutputUsrCtrlSelOPAC1(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].OCR & TPU_E_CHn_OCR_OUT_OP1_MASK) >> TPU_E_CHn_OCR_OUT_OP1_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set output user control, select OPAC1.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetOutputSelOPAC1(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEn)
{
    pTPUE->CH[u8Channel].OCR = (pTPUE->CH[u8Channel].OCR & ~TPU_E_CHn_OCR_OUT_OP1_MASK) | TPU_E_CHn_OCR_OUT_OP1(bEn);
}

/**
 * @brief Get output user control, select OPAC2.
 *
 */
LOCAL_INLINE bool TPU_E_HWA_GetOutputUsrCtrlSelOPAC2(const TPU_E_Type *const pTPUE, uint8_t u8Channel)
{
    uint32_t u32TmpVal;

    u32TmpVal = (pTPUE->CH[u8Channel].OCR & TPU_E_CHn_OCR_OUT_OP2_MASK) >> TPU_E_CHn_OCR_OUT_OP2_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set output user control, select OPAC2.
 *
 */
LOCAL_INLINE void TPU_E_HWA_SetOutputSelOPAC2(TPU_E_Type *const pTPUE, uint8_t u8Channel, bool bEn)
{
    pTPUE->CH[u8Channel].OCR = (pTPUE->CH[u8Channel].OCR & ~TPU_E_CHn_OCR_OUT_OP2_MASK) | TPU_E_CHn_OCR_OUT_OP2(bEn);
}

#endif /* #ifndef _HWA_TPUE_H_ */
