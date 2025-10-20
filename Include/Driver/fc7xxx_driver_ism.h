/**
 * @file fc7xxx_driver_ism.h
 * @author Flagchip084
 * @brief FC7xxx ISM driver type definition and API
 * @version 0.2.0
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2022-11-18    Flagchip084   N/A          First version for FC7xxx
   *   0.2.0       2023-02-13    Flagchip084   N/A          FC7xxx release version
   ******************************************************************************** */

#ifndef _DRIVER_FC7XXX_DRIVER_ISM_H_
#define _DRIVER_FC7XXX_DRIVER_ISM_H_
#include "device_header.h"
#include "HwA_ism.h"
/**
 * @addtogroup fc7xxx_driver_ism
 * @{
 */

#define ISM_ECM_CHANNEL(x)  (1<<(x))
#define ISM_LAM_CHANNEL(x)  (1<<(x))
#define ISM_FPC_CHANNEL(x)  (1<<(x))

typedef enum
{
    ISM_INSTANCE_0 = 0U,  /*!< ISM instance 0 is selected. */
} ISM_InstanceType;

typedef enum
{
    FPC_RISING_GLITCH_DETECTED = 0x01U,    /*!< PFC Rising Glitch Detected. */
    FPC_FALLING_GLITCH_DETECTED = 0x02U    /*!< PFC Falling Glitch Detected. */
} FPC_GlitchDetectType;

/**
 * @brief ISM Channel ISR callback function prototype
 *
 */
typedef void (*ISM_EventISRCallbackType)(const uint16_t u16LamStatus, const uint8_t u8EcmStatus);

/**
 * @brief FPC Channel Glitch dectection ISR callback function prototype
 *
 */
typedef void (*FPC_ISRCallbackType)(const uint32_t u32Status);

/**
 * @brief LAM Channel Overflow ISR callback function prototype
 *
 */
typedef void (*LAM_ISRCallbackType)(void);

typedef struct
{

    bool bIntEnable;
    ISM_EventISRCallbackType pEventIsrCallback;
} ISM_InitCfgType;

typedef struct
{
    bool bGlitchIntEnable;
    ISM_FPC_EdgeDetectModeType eFallingDetectMode;
    ISM_FPC_EdgeDelayModeType eFallingDelayNode;
    ISM_FPC_EdgeDetectModeType eRisingDetectMode;
    ISM_FPC_EdgeDelayModeType eRisingDelayNode;
    uint16_t u32ThresholdValue;
    FPC_ISRCallbackType pFpcIsrCallback;
} ISM_FpcCfgType;

typedef struct
{
    bool bOvflIntEnable;
    uint8_t u8SrcSel;
    uint8_t u8MonSel;
    ISM_LAM_InvertEventWindowType eInvWin;
    ISM_LAM_EventWindowEdgeType eWinEdgSel;
    ISM_LAM_EventWindowSelectType eEvtWinSel;
    ISM_LAM_RunModeSelectType eRunMode;
    ISM_LAM_MonitorSourceType eMonSrcSel;
    ISM_LAM_InvertMonitorType eInvMon;
    ISM_LAM_InvertReferenceType eInvRef;
    uint32_t u32EvtCntThreshold;
    LAM_ISRCallbackType pLamOverFlowIsrCallback;
} ISM_LamCfgType;

/**
 * @brief Init the ISM.
 *
 * @param pInitConfig ISMInstance initial configuration.
 */
void ISM_Init(const ISM_InitCfgType *pInitConfig);

/**
 * @brief Get the channels mask of ECM that has event happened.
 *
 * @return  Channels mask.
 */
uint8_t ISM_GetEcmEventHappenedChannels(void);

/**
 * @brief Get the channels mask of LAM that has event happened.
 *
 * @return Channels mask.
 */
uint16_t ISM_GetLamEventHappenedChannels(void);

/**
 * @brief Clear the channels status of ECM that has event happened.
 *
 * @param u8Channels Channels mask.
 */
void ISM_ClearEcmEventHappenedChannels(uint8_t u8Channels);

/**
 * @brief  Clear the channels status of LAM that has event happened.
 *
 * @param u16Channels Channels mask.
 */
void ISM_ClearLamEventHappenedChannels(uint16_t u16Channels);

/**
 * @brief Enable or disable ISM.
 *
 * @param bEnable Enable value.
 */
void ISM_Enable(bool bEnable);

/**
 * @brief Enable or disable ISM interrupt.
 *
 * @param bEnable Enable value.
 */
void ISM_InterruptEnable(bool bEnable);

/**
 * @brief ENable LAM overflow interrupt.
 *
 * @param u8LamIndex LAM index.
 * @param bEnable Enable value.
 */
void ISM_LamOverflowInterruptEnable(uint8_t u8LamIndex, bool bEnable);

/**
 * @brief Enable LAM Channel.
 *
 * @param u8LamIndex LAM index.
 * @param bEnable Enable value.
 */
void ISM_LamEnable(uint8_t u8LamIndex, bool bEnable);

/**
 * @brief Config the LAM channel.
 *
 * @param u8LamIndex LAM index.
 * @param pConfig LAM configuration.
 */
void ISM_LamConfig(uint8_t u8LamIndex, const ISM_LamCfgType *pConfig);

/**
 * @brief Enable FPC glitch interrupt.
 *
 * @param u8FpcIndex FPC index.
 * @param bEnable Enable value.
 */
void ISM_FpcGlitchInterruptEnable(uint8_t u8FpcIndex, bool bEnable);

/**
 * @brief Enable FPC channel.
 *
 * @param u8FpcIndex FPC index.
 * @param bEnable Enable value.
 */
void ISM_FpcEnable(uint8_t u8FpcIndex, bool bEnable);

/**
 * @brief Config the FPC channel.
 *
 * @param u8FpcIndex FPC index.
 * @param pConfig FPC configuration.
 */
void ISM_FpcConfig(uint8_t u8FpcIndex, const ISM_FpcCfgType *pConfig);

/**
 * @brief Enable ECM system event
 *
 * @param u32Channels Channel masks.
 * @param bEnable Enable value.
 */
void ISM_EnableEcmSystemEvent(uint32_t u32Channels, bool bEnable);

/**
 * @brief Enable LAM system event
 *
 * @param u32Channels Channel masks.
 * @param bEnable Enable value.
 */
void ISM_EnableLamSystemEvent(uint32_t u32Channels, bool bEnable);

/**
 * @brief Enable LAM system event
 *
 * @param u32LamIndex Lam channel index.
 * @param u32EcmIndex Ecm channel index.
 * @param u8EventCount Threshold of the ECM channel counter value.
 */
void ISM_EcmEventConfig(uint8_t u32LamIndex, uint8_t u32EcmIndex, uint8_t u8EventCount);

/**
 * @brief Clears the value of the LAM counter.
 *
 * @param u32LamIndex Lam channel index.
 */
void ISM_ClearLamStatusCounter(uint8_t u8LamIndex);

/**
 * @brief Gets the value of the LAM counter when a LAM event is triggered.
 *
 * @param u32LamIndex Lam channel index.
 * @return Counter value.
 */
uint32_t  ISM_GetLamStatusCounter(uint8_t u8LamIndex);

/**
 * @brief Clears LAM Timer Overflow Flag.
 *
 * @param u32LamIndex Lam channel index.
 */
void ISM_ClearLamStatusOvfl(uint8_t u8LamIndex);

/**
 * @brief Gets LAM Timer Overflow Flag.
 *
 * @param u32LamIndex Lam channel index.
 * @return Overflow flag.
 */
bool ISM_GetLamStatusOvfl(uint8_t u8LamIndex);

/** @}*/ /* fc7xxx_driver_ism. */
#endif
