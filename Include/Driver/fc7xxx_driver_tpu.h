/**
 * @file module_driver_tpu.c
 * @author Flagchip099
 * @brief FC7xxx TPU driver source code
 * @version 0.1.0
 * @date 2024-1-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-1-12     Flagchip099   N/A          First version for FC7240
   ******************************************************************************** */

#ifndef FC7XXX_DRIVER_TPU_H
#define FC7XXX_DRIVER_TPU_H

/* ----------------------------------------------------------------------------
   -- TPU_H Peripheral Access Layer
   ---------------------------------------------------------------------------- */

#include "HwA_tpuh.h"
#include "HwA_tpue.h"
#include "HwA_scm.h"

#define TPU_TCR1_MAXVALUE                                             0xFFFFFFU
#define TPU_CHANNEL_NUM                                                     32U

extern void RTT_Printf(char *fmt, ...);
#define DEBUG_INFO(str, ...) RTT_Printf(str, ##__VA_ARGS__)

/**
 * @brief TPU event callback function prototype
 *
 */
typedef void (*TPU_EventCallbackType)(void);

typedef void (*TPU_TCR1OverflowCallbackType)(void);

typedef void (*TPU_TCR2OverflowCallbackType)(void);

typedef void (*TPU_HSACallbackType)(void);

typedef enum
{
    TPU_DutyMeasurementActiveHigh   = 0x0U,
    TPU_DutyMeasurementActiveLow    = 0x1U,
    TPU_PeriodMeasurement           = 0x2U,
} TPU_MeasureModeType;

typedef enum
{
    TPU_CHANNEL_0  = 0U,
    TPU_CHANNEL_1  = 1U,
    TPU_CHANNEL_2  = 2U,
    TPU_CHANNEL_3  = 3U,
    TPU_CHANNEL_4  = 4U,
    TPU_CHANNEL_5  = 5U,
    TPU_CHANNEL_6  = 6U,
    TPU_CHANNEL_7  = 7U,
    TPU_CHANNEL_8  = 8U,
    TPU_CHANNEL_9  = 9U,
    TPU_CHANNEL_10 = 10U,
    TPU_CHANNEL_11 = 11U,
    TPU_CHANNEL_12 = 12U,
    TPU_CHANNEL_13 = 13U,
    TPU_CHANNEL_14 = 14U,
    TPU_CHANNEL_15 = 15U,
    TPU_CHANNEL_16 = 16U,
    TPU_CHANNEL_17 = 17U,
    TPU_CHANNEL_18 = 18U,
    TPU_CHANNEL_19 = 19U,
    TPU_CHANNEL_20 = 20U,
    TPU_CHANNEL_21 = 21U,
    TPU_CHANNEL_22 = 22U,
    TPU_CHANNEL_23 = 23U,
    TPU_CHANNEL_24 = 24U,
    TPU_CHANNEL_25 = 25U,
    TPU_CHANNEL_26 = 26U,
    TPU_CHANNEL_27 = 27U,
    TPU_CHANNEL_28 = 28U,
    TPU_CHANNEL_29 = 29U,
    TPU_CHANNEL_30 = 30U,
    TPU_CHANNEL_31 = 31U,
    TPU_CHANNEL_MAX = TPU_E_CH_COUNT
} TPU_ChannelType;

/** TPU_H - Register Layout Typedef */

/** @brief ETPU config type */

typedef struct
{
    TPUE_TimeBaseSelctionType eTBS1;                     /**< modulate 0 value */
    TPUE_TimeBaseSelctionType eTBS2;                     /**< modulate 1 value */
    bool bPwmUseTCR1;                                   /**< modulate 2 value */
    bool bPwmUseTCR2;                                   /**< modulate 3 value */
    uint32_t u32ActiveTime;
    uint32_t u32PeriodTime;
    bool bActiveHigh;
} TPU_PwmCfgType;

typedef struct
{
    uint32_t u32PeriodTime;
    TPU_MeasureModeType eMeasureMode;
    TPUE_IPACType eInputType;
    uint32_t u32SampleTime;
    uint32_t u32ActiveTime;
    uint32_t LastTime;
    uint32_t StartTime;
} TPU_CaptureCfgType;

/**
 * @brief The interrupt configurations of the Tpu channel
 *
 */
typedef struct
{
    bool bEventIntEn; /*!< Enable interrupt after match */
    bool bTCR1OverFlowEventIntEn; /*!< Enable interrupt after TCR1 OverFlow */
    bool bTCR2OverFlowEventIntEn; /*!< Enable interrupt after TCR2 OverFlow */
    TPU_EventCallbackType pEventNotify; /*!< transfer complete notification */
    TPU_HSACallbackType pHSANotify; /*!< HSA notification */
    TPU_TCR1OverflowCallbackType  pTCR1OverflowNotify;
    TPU_TCR2OverflowCallbackType  pTCR2OverflowNotify;
    TPUH_ChTrigCFGType eChTrigType;
} TPU_InterruptCfgType;



void TPU_InitChannelInterrupt(uint8_t u8Channel, const TPU_InterruptCfgType *const pInterruptCfg);

void TPU_PwmModeInit(uint8_t u8channel, const TPU_PwmCfgType *const p_etpu_config);

void TPU_PwmServiceReq(uint8_t u8channel, uint32_t u32ActiveTime, uint32_t u32Period);

void TPU_CaptureModeInit(uint8_t u8channel, const TPU_CaptureCfgType *const p_etpu_config);

void TPU_StartChannel(void);

void TPU_SetHSR(uint8_t u8channel, uint8_t u8HSRIdx);

void TPU_SendHSR(uint8_t u8channel);

uint8_t TPU_GetHSA(uint8_t u8Channel);

void TPU_InitChannelHSAInterrupt(uint8_t u8Channel, const TPU_InterruptCfgType *const pInterruptCfg);

void TPU_InitChannelOverflowInterrupt(const TPU_InterruptCfgType *const pInterruptCfg);

void TPU_EnableSubSystem(void);

void TPU_EnableEventTrigDma(uint8_t u8Channel);

void TPU_CaptureMeasPeriodServiceReq(uint8_t u8channel, TPU_CaptureCfgType *p_etpu_config);

void TPU_CaptureMeasActivePeriodServiceReq(uint8_t u8channel, TPU_CaptureCfgType *p_etpu_config);

void TPU_DeInit(void);

void TPU_Init(void);

void TPU_EnableFlexcoreTrigDma(uint8_t u8Channel);

void TPU_EnableEventTrigTrgSel(uint8_t u8Channel, const TPU_InterruptCfgType *const pInterruptCfg);

/*!
 * @}
 */ /* end of group TPU_H_Peripheral_Access_Layer */

#endif  /* #ifndef FC7XXX_DRIVER_TPU_H */
