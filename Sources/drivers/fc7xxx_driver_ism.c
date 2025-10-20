/**
 * @file fc7xxx_driver_ism.c
 * @author Flagchip
 * @brief FC7xxx ISM driver type definition and API
 * @version 0.1.0
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
   *   0.1.0       2024-1-10    Flagchip095   N/A          First version for FC7240
   ******************************************************************************** */
#include "fc7xxx_driver_ism.h"

/* ################################################################################## */
/* ####################################### Macro #################################### */
#define FPC_INSTANCE_COUNT (16U)
#define LAM_INSTANCE_COUNT (16U)
#define ECM_INSTANCE_COUNT (4U)
/* ################################################################################## */
/* ################################### Type define ################################## */

/* ################################################################################## */
/* ################################ Local Variables ################################# */
static ISM_Type *const s_apIsmBase[ISM_INSTANCE_COUNT] = ISM_BASE_PTRS;
static ISM_EventISRCallbackType s_apEventISRCallback = NULL;
static FPC_ISRCallbackType s_apFpcISRCallback[FPC_INSTANCE_COUNT] = {NULL};
static LAM_ISRCallbackType s_apLamOverFlowIsrCallback[LAM_INSTANCE_COUNT] = {NULL};
/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */

/* ################################################################################## */
/* ######################### Global prototype Functions  ############################ */
void ISM0_IRQHandler(void);
/* ################################################################################## */
/* ################################ Local Functions  ################################ */

/* ################################################################################## */
/* ################################ Global Functions ################################ */

void ISM_Init(const ISM_InitCfgType *pInitConfig)
{
    ISM_Type *pIsm = ISM;

    DEV_ASSERT(ISM_HWA_PARAM_ECMC(pIsm) == ECM_INSTANCE_COUNT);
    DEV_ASSERT(ISM_HWA_PARAM_FPC(pIsm) == FPC_INSTANCE_COUNT);
    DEV_ASSERT(ISM_HWA_PARAM_LAM(pIsm) == LAM_INSTANCE_COUNT);
    DEV_ASSERT(pInitConfig != NULL);

    s_apEventISRCallback = pInitConfig->pEventIsrCallback;
    ISM_HWA_InterruptEnable(pIsm, pInitConfig->bIntEnable);
}

uint8_t ISM_GetEcmEventHappenedChannels(void)
{
    ISM_Type *pIsm = ISM;

    return (uint8_t)ISM_HWA_GetEcs(pIsm);
}

uint16_t ISM_GetLamEventHappenedChannels(void)
{
    ISM_Type *pIsm = ISM;

    return ISM_HWA_GetEs(pIsm);
}

void ISM_ClearEcmEventHappenedChannels(uint8_t u8Channels)
{
    ISM_Type *pIsm = ISM;

    ISM_HWA_ClearEcs(pIsm, (uint32_t)u8Channels);
}

void ISM_ClearLamEventHappenedChannels(uint16_t u16Channels)
{
    ISM_Type *pIsm = ISM;

    ISM_HWA_ClearEs(pIsm, (uint32_t)u16Channels);
}

void ISM_EnableEcmSystemEvent(uint32_t u32Channels, bool bEnable)
{
    ISM_Type *pIsm = ISM;

    ISM_HWA_EnableEcmSystemEvent(pIsm, u32Channels, bEnable);
}

void ISM_EnableLamSystemEvent(uint32_t u32Channels, bool bEnable)
{
    ISM_Type *pIsm = ISM;

    ISM_HWA_EnableLamSystemEvent(pIsm, u32Channels, bEnable);
}

void ISM_EcmEventConfig(uint8_t u8LamIndex, uint8_t u8EcmIndex, uint8_t u8EventCount)
{
    ISM_Type *pIsm = ISM;

    DEV_ASSERT(u8LamIndex < LAM_INSTANCE_COUNT);
    DEV_ASSERT(u8EcmIndex < ECM_INSTANCE_COUNT);
    if (u8EcmIndex == 0U)
    {
        ISM_HWA_SetEcm0EcCtrl(pIsm, u8EventCount, u8LamIndex);
    }
    else if (u8EcmIndex == 1U)
    {
        ISM_HWA_SetEcm1EcCtrl(pIsm, u8EventCount, u8LamIndex);
    }
    else if (u8EcmIndex == 2U)
    {
        ISM_HWA_SetEcm2EcCtrl(pIsm, u8EventCount, u8LamIndex);
    }
    else if (u8EcmIndex == 3U)
    {
        ISM_HWA_SetEcm3EcCtrl(pIsm, u8EventCount, u8LamIndex);
    }
    else
    {

    }
}

void ISM_ClearLamStatusCounter(uint8_t u8LamIndex)
{
    LAM_Type *pLam;

    DEV_ASSERT(u8LamIndex < LAM_INSTANCE_COUNT);

    pLam = ISM_HWA_GetLam(ISM, u8LamIndex);

    ISM_HWA_ClearLamStatusCounter(pLam);
}

uint32_t  ISM_GetLamStatusCounter(uint8_t u8LamIndex)
{
    LAM_Type *pLam;

    DEV_ASSERT(u8LamIndex < LAM_INSTANCE_COUNT);

    pLam = ISM_HWA_GetLam(ISM, u8LamIndex);

    return ISM_HWA_GetLamStatusCounter(pLam);
}

void ISM_ClearLamStatusOvfl(uint8_t u8LamIndex)
{
    LAM_Type *pLam;

    DEV_ASSERT(u8LamIndex < LAM_INSTANCE_COUNT);

    pLam = ISM_HWA_GetLam(ISM, u8LamIndex);

    ISM_HWA_ClearLamStatusOvfl(pLam);
}

bool ISM_GetLamStatusOvfl(uint8_t u8LamIndex)
{
    LAM_Type *pLam;

    DEV_ASSERT(u8LamIndex < LAM_INSTANCE_COUNT);

    pLam = ISM_HWA_GetLam(ISM, u8LamIndex);

    return ISM_HWA_GetLamStatusOvfl(pLam);
}

void ISM_Enable(bool bEnable)
{
    ISM_Type *pIsm = ISM;

    ISM_HWA_Enable(pIsm, bEnable);
}

void ISM_InterruptEnable(bool bEnable)
{
    ISM_Type *pIsm = ISM;

    ISM_HWA_InterruptEnable(pIsm, bEnable);
}

void ISM_LamOverflowInterruptEnable(uint8_t u8LamIndex, bool bEnable)
{
    LAM_Type *pLam;

    DEV_ASSERT(u8LamIndex < LAM_INSTANCE_COUNT);

    pLam = ISM_HWA_GetLam(ISM, u8LamIndex);

    ISM_HWA_SetLamCtrIen(pLam, bEnable);
}

void ISM_LamEnable(uint8_t u8LamIndex, bool bEnable)
{
    LAM_Type *pLam;

    DEV_ASSERT(u8LamIndex < LAM_INSTANCE_COUNT);

    pLam = ISM_HWA_GetLam(ISM, u8LamIndex);

    ISM_HWA_SetLamCtrEn(pLam, bEnable);
}

void ISM_LamConfig(uint8_t u8LamIndex, const ISM_LamCfgType *pConfig)
{
    uint32_t u32TempValue = 0;
    LAM_Type *pLam;

    DEV_ASSERT(u8LamIndex < LAM_INSTANCE_COUNT);
    DEV_ASSERT(pConfig != NULL);

    pLam = ISM_HWA_GetLam(ISM, u8LamIndex);

    ISM_HWA_SetLamCtrIen(pLam, pConfig->bOvflIntEnable);
    ISM_HWA_SetLamCounter(pLam, pConfig->u32EvtCntThreshold);

    u32TempValue |= ISM_LAM_CONFIG_RCS(pConfig->u8SrcSel);
    u32TempValue |= ISM_LAM_CONFIG_MCS(pConfig->u8MonSel);
    u32TempValue |= ISM_LAM_CONFIG_IVW(pConfig->eInvWin);
    u32TempValue |= ISM_LAM_CONFIG_EDS(pConfig->eWinEdgSel);
    u32TempValue |= ISM_LAM_CONFIG_EWS(pConfig->eEvtWinSel);
    u32TempValue |= ISM_LAM_CONFIG_RMS(pConfig->eRunMode);
    u32TempValue |= ISM_LAM_CONFIG_MOS(pConfig->eMonSrcSel);
    u32TempValue |= ISM_LAM_CONFIG_IVM(pConfig->eInvMon);
    u32TempValue |= ISM_LAM_CONFIG_IVR(pConfig->eInvRef);

    s_apLamOverFlowIsrCallback[u8LamIndex] = pConfig->pLamOverFlowIsrCallback;

    ISM_HWA_SetLamConfig(pLam, u32TempValue);
}

void ISM_FpcGlitchInterruptEnable(uint8_t u8FpcIndex, bool bEnable)
{
    FPC_Type *pFpc;

    DEV_ASSERT(u8FpcIndex < FPC_INSTANCE_COUNT);

    pFpc = ISM_HWA_GetFpc(ISM, u8FpcIndex);

    ISM_HWA_SetFpcCtrlIen(pFpc, bEnable);
}

void ISM_FpcEnable(uint8_t u8FpcIndex, bool bEnable)
{
    FPC_Type *pFpc;

    DEV_ASSERT(u8FpcIndex < FPC_INSTANCE_COUNT);

    pFpc = ISM_HWA_GetFpc(ISM, u8FpcIndex);

    ISM_HWA_SetFpcCtrlEn(pFpc, bEnable);
}

void ISM_FpcConfig(uint8_t u8FpcIndex, const ISM_FpcCfgType *pConfig)
{
    uint32_t u32TempValue = 0;
    FPC_Type *pFpc;

    DEV_ASSERT(u8FpcIndex < FPC_INSTANCE_COUNT);
    DEV_ASSERT(pConfig != NULL);

    pFpc = ISM_HWA_GetFpc(ISM, u8FpcIndex);

    ISM_HWA_SetFpcCtrlIen(pFpc, pConfig->bGlitchIntEnable);

    u32TempValue |= ISM_FPC_CONFIG_FED(pConfig->eFallingDelayNode);
    u32TempValue |= ISM_FPC_CONFIG_FEG(pConfig->eFallingDetectMode);
    u32TempValue |= ISM_FPC_CONFIG_RED(pConfig->eRisingDelayNode);
    u32TempValue |= ISM_FPC_CONFIG_REG(pConfig->eRisingDetectMode);
    u32TempValue |= ISM_FPC_CONFIG_CMP(pConfig->u32ThresholdValue);

    s_apFpcISRCallback[u8FpcIndex] = pConfig->pFpcIsrCallback;

    ISM_HWA_SetFpcConfig(pFpc, u32TempValue);
}

void ISM0_IRQHandler(void)
{
    uint8_t u8i;
    FPC_Type *pFpc;
    LAM_Type *pLam;
    uint8_t u8EcmFlags;
    uint16_t u16LamFlags;
    ISM_Type *pIsm = s_apIsmBase[ISM_INSTANCE_0];

    u8EcmFlags = ISM_HWA_GetEcs(pIsm)&ISM_HWA_GetEnabledEcmSystemEvent(pIsm);
    u16LamFlags = ISM_HWA_GetEs(pIsm)&ISM_HWA_GetEnabledLamSystemEvent(pIsm);

    if (s_apEventISRCallback != NULL)
    {
        s_apEventISRCallback(u16LamFlags, u8EcmFlags);
    }

    ISM_HWA_ClearEcs(pIsm, u8EcmFlags);
    ISM_HWA_ClearEs(pIsm, u16LamFlags);

    for (u8i = 0; u8i < FPC_INSTANCE_COUNT; u8i++)
    {
        pFpc = ISM_HWA_GetFpc(s_apIsmBase[ISM_INSTANCE_0], u8i);
        if (ISM_HWA_GetFpcCtrlIen(pFpc))
        {
            uint32_t u32Status = 0U;
            if (ISM_HWA_GetFpcRgd(pFpc))
            {
                u32Status |= (uint32_t)FPC_RISING_GLITCH_DETECTED;
            }
            if (ISM_HWA_GetFpcFgd(pFpc))
            {
                u32Status |= (uint32_t)FPC_FALLING_GLITCH_DETECTED;
            }
            if (s_apFpcISRCallback[u8i] != NULL)
            {
                s_apFpcISRCallback[u8i](u32Status);
            }
            if ((u32Status & (uint32_t)FPC_RISING_GLITCH_DETECTED) == (uint32_t)FPC_RISING_GLITCH_DETECTED)
            {
                ISM_HWA_ClearFpcRgd(pFpc);
            }
            if ((u32Status & (uint32_t)FPC_FALLING_GLITCH_DETECTED) == (uint32_t)FPC_FALLING_GLITCH_DETECTED)
            {
                ISM_HWA_ClearFpcFgd(pFpc);
            }
        }
    }

    for (u8i = 0; u8i < LAM_INSTANCE_COUNT; u8i++)
    {
        pLam = ISM_HWA_GetLam(s_apIsmBase[ISM_INSTANCE_0], u8i);
        if (ISM_HWA_GetLamCtrIen(pLam))
        {
            if (ISM_HWA_GetLamStatusOvfl(pLam))
            {
                if (s_apLamOverFlowIsrCallback[u8i] != NULL)
                {
                    s_apLamOverFlowIsrCallback[u8i]();
                }
            }
            ISM_HWA_ClearLamStatusOvfl(pLam);
        }
    }

}
