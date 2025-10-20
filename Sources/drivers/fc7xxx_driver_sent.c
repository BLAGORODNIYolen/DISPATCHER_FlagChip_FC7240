/**
 * @file fc7xxx_driver_sent.c
 * @author Flagchip
 * @brief FC7xxx SENT driver source code
 * @version 0.2.0
 * @date 2022-12-30
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Author        CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2022-12-14    Flagchip      N/A          First version for FC7300 SENT
   *   0.2.0       2022-12-30    Flagchip      N/A          Support SPC mode for SENT
   ******************************************************************************** */

#include "fc7xxx_driver_sent.h"
#include "interrupt_manager.h"
#include "HwA_sent.h"

#define SENT_GLBL_CTL_PRESCALER_MAX   255U
#define SENT_GLBL_CTL_WATERMARK_MAX   16U

static SENT_Type* const aSent_Base[] = SENT_BASE_PTRS;
static bool aSentInit[SENT_INSTANCE_COUNT] = {0u};
static SENT_GBISRCallbackType aGBISRCallback[SENT_INSTANCE_MAX] = {NULL};
static SENT_CHISRCallbackType aCHISRCallback[SENT_INSTANCE_MAX] = {NULL};

void SENT0_IRQHandler(void);
void SENT1_IRQHandler(void);

static void SENT_IRQ_Handler(const Sent_InstanceType eInstance)
{
    uint8_t u8Channel;
    uint32_t u32ChannelStatus;
    SENT_Type *pSent  = aSent_Base[eInstance];


    for(u8Channel = 0U; u8Channel < SENT_CHANNEL_COUNT; u8Channel++)
    {
        if(true == SENT_HWA_GetChannelReceive(pSent, u8Channel))
        {
            if(true == SENT_HWA_GetSLowMessageUnderflowFlag(pSent, u8Channel))
            {
                if(NULL != aGBISRCallback[eInstance])
                {
                    SENT_HWA_ClearSLowMessageUnderflowFlag(pSent, u8Channel);
                    aGBISRCallback[eInstance]((Sent_ChannelType)u8Channel, SENT_SLOW_MSG_DMA_UF_IT);
                }
            }
            if(true == SENT_HWA_GetFastMessageReadyFlag(pSent, u8Channel))
            {
                if(NULL != aGBISRCallback[eInstance])
                {
                    SENT_HWA_ClearFastMessageReadyFlag(pSent, u8Channel);
                    aGBISRCallback[eInstance]((Sent_ChannelType)u8Channel, SENT_FAST_MSG_READY_IT);
                }
            }
            if(true == SENT_HWA_GetSlowMessageReadyFlag(pSent, u8Channel))
            {
                if(NULL != aGBISRCallback[eInstance])
                {
                    SENT_HWA_ClearSlowMessageReadyFlag(pSent, u8Channel);
                    aGBISRCallback[eInstance]((Sent_ChannelType)u8Channel, SENT_SLOW_MSG_READY_IT);
                }
            }
            if(true == SENT_HWA_GetFastMessageFIFOOverflowFlag(pSent, u8Channel))
            {
                if(NULL != aGBISRCallback[eInstance])
                {
                    SENT_HWA_ClearFastMessageFIFOOverflowFlag(pSent, u8Channel);
                    aGBISRCallback[eInstance]((Sent_ChannelType)u8Channel, SENT_FAST_MSG_FIFO_OF_IT);
                }
            }
            if(true == SENT_HWA_GetFastMessageDMAUnderflowFlag(pSent, u8Channel))
            {
                if(NULL != aGBISRCallback[eInstance])
                {
                    SENT_HWA_ClearFastMessageDMAUnderflowFlag(pSent, u8Channel);
                    aGBISRCallback[eInstance]((Sent_ChannelType)u8Channel, SENT_FAST_MSG_DMA_DF_IT);
                }
            }
            u32ChannelStatus = SENT_HWA_GetChannelStatus(pSent, u8Channel);
            if(0U != u32ChannelStatus)
            {
                if(NULL != aCHISRCallback[eInstance])
                {
                    SENT_HWA_ClearChannelStatus(pSent, u8Channel, u32ChannelStatus);
                    aCHISRCallback[eInstance]((Sent_ChannelType)u8Channel, u32ChannelStatus);
                }
            }
        }
    }
}

Sent_ReturnType SENT_Init(const Sent_InstanceType eInstance, const Sent_ConfigType *pCfg)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(false == aSentInit[eInstance])
    {
        if((NULL != pCfg) && (eInstance < SENT_INSTANCE_MAX) && \
                (pCfg->u8DmaWaterMark <= SENT_GLBL_CTL_WATERMARK_MAX) && \
                (pCfg->u8PreScaler < SENT_GLBL_CTL_PRESCALER_MAX))
        {
            pSent = aSent_Base[eInstance];

            SENT_HWA_SetGlobalPreScaler(pSent, pCfg->u8PreScaler);
            SENT_HWA_SetDMAWaterMark(pSent, pCfg->u8DmaWaterMark);
            if(true == pCfg->bDebugModeEn)
            {
                SENT_HWA_EnableDebugMode(pSent);
            }
            else
            {
                SENT_HWA_DisableDebugMode(pSent);
            }
            if(true == pCfg->bAutoClearReadyFlag)
            {
                SENT_HWA_EnableDataOverflowFlagFastClear(pSent);
            }
            else
            {
                SENT_HWA_DisableDataOverflowFlagFastClear(pSent);
            }
            aGBISRCallback[eInstance] = pCfg->pGBCallback;
            aCHISRCallback[eInstance] = pCfg->pCHCallback;
            SENT_HWA_EnableGlobal(pSent);
            aSentInit[eInstance] = true;
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_ALREADY_INIT;
    }

    return eRet;
}

Sent_ReturnType SENT_SetChannelConfig(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, const Sent_ChannelConfigType *pCfg)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((NULL != pCfg) && (eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];
            if(true == pCfg->bChannelEn)
            {
                if((pCfg->u8DataNibbleNumber > 0U) && (pCfg->u8DataNibbleNumber < 6U))
                {
                    SENT_HWA_DisableChannelReceive(pSent, (uint8_t)eChannel);

                    SENT_HWA_SetChannelIdleCount(pSent, (uint8_t)eChannel, (uint8_t)pCfg->eIdleCount);
                    SENT_HWA_SetChannelDigitalFilterCount(pSent, (uint8_t)eChannel, pCfg->u8DigitalFilterCount);
                    SENT_HWA_SetChannelNibbleNumber(pSent, (uint8_t)eChannel, pCfg->u8DataNibbleNumber);
                    SENT_HWA_SetChannelPreScaler(pSent, (uint8_t)eChannel, (uint16_t)pCfg->u16TickScaler);
                    SENT_HWA_SetChannelNibbleDataMode(pSent, (uint8_t)eChannel, (SENT_NibbleDataModeType)(pCfg->eDataNibbleMode));

                    if(SENT_CALIBRATION_PULSE_DIAG_OPTION1 != pCfg->eCalDiagOption)
                    {
                        SENT_HWA_DisableChannelSPCOption1(pSent, (uint8_t)eChannel);
                    }
                    else
                    {
                        SENT_HWA_EnableChannelSPCOption1(pSent, (uint8_t)eChannel);
                    }
                    if(true == pCfg->bPausePulseEn)
                    {
                        SENT_HWA_EnableChannelPausePulse(pSent, (uint8_t)eChannel);
                    }
                    else
                    {
                        SENT_HWA_DisableChannelPausePulse(pSent, (uint8_t)eChannel);
                    }
                    if(true == pCfg->bTickCompensateEn)
                    {
                        SENT_HWA_EnableChannelCompensate(pSent, (uint8_t)eChannel);
                    }
                    else
                    {
                        SENT_HWA_DisableChannelCompensate(pSent, (uint8_t)eChannel);
                    }

                    if(true == pCfg->bFastMessageFifoEn)
                    {
                        SENT_HWA_EnableChannelFIFO(pSent, (uint8_t)eChannel);
                    }
                    else
                    {
                        SENT_HWA_DisableChannelFIFO(pSent, (uint8_t)eChannel);
                    }

                    if(true == pCfg->bFastMsgCRCAugEn)
                    {
                        SENT_HWA_EnableChannelFastMessageAugmentation(pSent, (uint8_t)eChannel);
                    }
                    else
                    {
                        SENT_HWA_DisableChannelFastMessageAugmentation(pSent, (uint8_t)eChannel);
                    }

                    if(true == pCfg->bFastMsgCRCCheckEn)
                    {
                        SENT_HWA_EnableChannelFastMessageCRCCheck(pSent, (uint8_t)eChannel);
                    }
                    else
                    {
                        SENT_HWA_DisableChannelFastMessageCRCCheck(pSent, (uint8_t)eChannel);
                    }

                    if(true == pCfg->bFastMsgCRCWithSCEn)
                    {
                        SENT_HWA_EnableChannelFastMessageCRCWithSC(pSent, (uint8_t)eChannel);
                    }
                    else
                    {
                        SENT_HWA_DisableChannelFastMessageCRCWithSC(pSent, (uint8_t)eChannel);
                    }

                    if(true == pCfg->bFastMsgDataChangeEn)
                    {
                        SENT_HWA_EnableChannelFastMessageDataChange(pSent, (uint8_t)eChannel);
                    }
                    else
                    {
                        SENT_HWA_DisableChannelFastMessageDataChange(pSent, (uint8_t)eChannel);
                    }


                    if(true == pCfg->bSlowMsgCRCAugEn)
                    {
                        SENT_HWA_EnableChannelSlowMessageAugmentation(pSent, (uint8_t)eChannel);
                    }
                    else
                    {
                        SENT_HWA_DisableChannelSlowMessageAugmentation(pSent, (uint8_t)eChannel);
                    }

                    if(true == pCfg->bUseAlternativeCrc)
                    {
                        SENT_HWA_EnableChannelAltCRC(pSent, (uint8_t)eChannel);
                    }
                    else
                    {
                        SENT_HWA_DisableChannelAltCRC(pSent, (uint8_t)eChannel);
                    }

                    if(SENT_CALIBRATION_VALID_WITHIN_20 == pCfg->eCalValid)
                    {
                        SENT_HWA_DisableChannelCalValid20To25(pSent, (uint8_t)eChannel);
                        SENT_HWA_EnableChannelCalValidDiagnostic(pSent, (uint8_t)eChannel);
                    }
                    else if(SENT_CALIBRATION_VALID_FROM_20_TO_25 == pCfg->eCalValid)
                    {
                        SENT_HWA_EnableChannelCalValid20To25(pSent, (uint8_t)eChannel);
                        SENT_HWA_EnableChannelCalValidDiagnostic(pSent, (uint8_t)eChannel);
                    }
                    else
                    {
                        SENT_HWA_DisableChannelCalValid20To25(pSent, (uint8_t)eChannel);
                        SENT_HWA_DisableChannelCalValidDiagnostic(pSent, (uint8_t)eChannel);
                    }
                    SENT_HWA_EnableChannelReceive(pSent, (uint8_t)eChannel);
                }
                else
                {
                    eRet = SENT_RETURN_E_PARAM;
                }
            }
            else
            {
                SENT_HWA_DisableChannelReceive(pSent, (uint8_t)eChannel);
            }
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_SetDMAConfig(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, Sent_DMAConfigType *pCfg)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((NULL != pCfg) && (eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            if(true == pCfg->bFastMsgDmaEn)
            {
                SENT_HWA_EnableChannelFastMessageDmaRequest(pSent, (uint8_t)eChannel);
            }
            else
            {
                SENT_HWA_DisableChannelFastMessageDmaRequest(pSent, (uint8_t)eChannel);
            }

            if(true == pCfg->bSlowMsgDmaEn)
            {
                SENT_HWA_EnableChannelSlowMessageDmaRequest(pSent, (uint8_t)eChannel);
            }
            else
            {
                SENT_HWA_DisableChannelSlowMessageDmaRequest(pSent, (uint8_t)eChannel);
            }
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_SetSPCConfig(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, const Sent_SpcConfigType *pCfg)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((NULL != pCfg) && (eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            SENT_HWA_DisableChannelSPCMode(pSent, (uint8_t)eChannel);
            SENT_HWA_SetChannelSPCTickBase(pSent, (uint8_t)eChannel, (SENT_SPCTickType)(pCfg->eSpcTickBase));
            SENT_HWA_SetChannelSPCTriggerMethod(pSent, (uint8_t)eChannel, (SENT_SPCTriggerType)(pCfg->eSpcTrigger));
            SENT_HWA_SetChannelSPCPulseDelay(pSent, (uint8_t)eChannel, pCfg->u8PulseDelay);
            SENT_HWA_SetChannelSPCPulseWidth(pSent, (uint8_t)eChannel, pCfg->u8PulseWidth);
            if(true == pCfg->bCalDiagEn)
            {
                SENT_HWA_EnableChannelCalibrationDiag(pSent, (uint8_t)eChannel);
            }
            else
            {
                SENT_HWA_DisableChannelCalibrationDiag(pSent, (uint8_t)eChannel);
            }
            if(true == pCfg->bSpcModeEn)
            {
                SENT_HWA_EnableChannelSPCMode(pSent, (uint8_t)eChannel);
            }
            else
            {
                SENT_HWA_DisableChannelSPCMode(pSent, (uint8_t)eChannel);
            }
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_GetFastMessageData(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, Sent_FastMessageDataType *pMsg)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;
    uint8_t u8DataShift;

    if(true == aSentInit[eInstance])
    {
        if((NULL != pMsg) && (eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            pMsg->u8CRC	= SENT_HWA_GetChannelFastMessageCRCNibble(pSent, (uint8_t)eChannel);
            pMsg->u8SC = SENT_HWA_GetChannelFastMessageStatusNibble(pSent, (uint8_t)eChannel);
            pMsg->u32Timestamp = SENT_HWA_GetChannelFastMessageTimeStamp(pSent, (uint8_t)eChannel);
            u8DataShift = (5U - SENT_HWA_GetChannelNibbleNumber(pSent, (uint8_t)eChannel)) << 2U;
            pMsg->u32Data = SENT_HWA_GetChannelDataNibble(pSent, (uint8_t)eChannel) >> (SENT_CHN_FDATA_DATA6_SHIFT + u8DataShift);
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_GetSlowMessageData(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, Sent_SlowMessageDataType *pMsg)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((NULL != pMsg) && (eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            pMsg->eMsgType = (Sent_SerialMessageType)SENT_HWA_GetChannelSLowMessageType(pSent, (uint8_t)eChannel);
            pMsg->u32Timestamp = SENT_HWA_GetChannelSlowMessageTimeStamp(pSent, (uint8_t)eChannel);
            if(SENT_SERIAL_MESSAGE_SHORT == pMsg->eMsgType)
            {
                pMsg->u8CRC	= SENT_HWA_GetChannelBit2CRC(pSent, (uint8_t)eChannel) & 0xFU;
                pMsg->u16Data = (uint16_t)SENT_HWA_GetChannelBit2DATA(pSent, (uint8_t)eChannel) & 0xFFU;
                pMsg->u8ID = SENT_HWA_GetChannelBit2DATA(pSent, (uint8_t)eChannel) >> 8U;
            }
            else if(SENT_SERIAL_MESSAGE_ENHANCE_12DATA_8ID == pMsg->eMsgType)
            {
                pMsg->u8CRC	= SENT_HWA_GetChannelBit2CRC(pSent, (uint8_t)eChannel);
                pMsg->u16Data = SENT_HWA_GetChannelBit2DATA(pSent, (uint8_t)eChannel);
                pMsg->u8ID = (SENT_HWA_GetChannelBit3EnhancedID7_4_OR_ID3_0(pSent, (uint8_t)eChannel) << 4U) | SENT_HWA_GetChannelBit3EnhancedID3_0_OR_DATA15_12(pSent, (uint8_t)eChannel);
            }
            else if(SENT_SERIAL_MESSAGE_ENHANCE_16DATA_4ID == pMsg->eMsgType)
            {
                pMsg->u8CRC	= SENT_HWA_GetChannelBit2CRC(pSent, (uint8_t)eChannel);
                pMsg->u16Data = ((uint16_t)SENT_HWA_GetChannelBit3EnhancedID3_0_OR_DATA15_12(pSent, (uint8_t)eChannel) << 12U) | (uint16_t)SENT_HWA_GetChannelBit2DATA(pSent, (uint8_t)eChannel);
                pMsg->u8ID = SENT_HWA_GetChannelBit3EnhancedID7_4_OR_ID3_0(pSent, (uint8_t)eChannel);
            }
            else
            {
                eRet = SENT_RETURN_E_NOT_OK;
            }
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_DecodeFastMessageWithDMABuffer(uint32_t *pDmaBuffer, uint32_t u32BufferLength, Sent_FastMessageDataType *pMsg)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;

    if((NULL != pMsg) && (NULL != pDmaBuffer) && (12U == u32BufferLength))
    {
        pMsg->u8CRC	= (uint8_t)((pDmaBuffer[1] & SENT_CHN_FCRC_CRC_DATA_MASK) >> SENT_CHN_FCRC_CRC_DATA_SHIFT);
        pMsg->u8SC = (uint8_t)((pDmaBuffer[1] & SENT_CHN_FCRC_SC_NB_MASK) >> SENT_CHN_FCRC_SC_NB_SHIFT);
        pMsg->u32Timestamp = ((pDmaBuffer[2] & SENT_CHN_FTS_TIMESTAMP_VAL_MASK) >> SENT_CHN_FTS_TIMESTAMP_VAL_SHIFT);
        pMsg->u32Data = (pDmaBuffer[0] >> SENT_CHN_FDATA_DATA6_SHIFT);
    }
    else
    {
        eRet = SENT_RETURN_E_PARAM;
    }

    return eRet;
}

Sent_ReturnType SENT_DecodeSlowMessageWithDMABuffer(uint32_t *pDmaBuffer, uint32_t u32BufferLength, Sent_SlowMessageDataType *pMsg)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;

    if((NULL != pMsg) && (NULL != pDmaBuffer) && (12U == u32BufferLength))
    {
        if(SENT_CHN_SBIT3__MSG_TYPE_MASK == (pDmaBuffer[0] & SENT_CHN_SBIT3__MSG_TYPE_MASK))
        {
            if(SENT_CHN_SBIT3__CFG_MASK == (pDmaBuffer[0] & SENT_CHN_SBIT3__CFG_MASK))
            {
                pMsg->eMsgType = (Sent_SerialMessageType)SENT_SLOW_MESSAGE_ENHANCE_16DATA_4ID;
            }
            else
            {
                pMsg->eMsgType = (Sent_SerialMessageType)SENT_SLOW_MESSAGE_ENHANCE_12DATA_8ID;
            }
        }
        else
        {
            pMsg->eMsgType = (Sent_SerialMessageType)SENT_SLOW_MESSAGE_SHORT;
        }
        pMsg->u32Timestamp = ((pDmaBuffer[2] & SENT_CHN_STS_SMSG_TIMESTAMP_MASK) >> SENT_CHN_STS_SMSG_TIMESTAMP_SHIFT);
        if(SENT_SERIAL_MESSAGE_SHORT == pMsg->eMsgType)
        {
            pMsg->u8CRC	=(uint8_t)(((pDmaBuffer[1] & SENT_CHN_SBIT2__SMSG_CRC_MASK) >> SENT_CHN_SBIT2__SMSG_CRC_SHIFT) & 0xFU);
            pMsg->u16Data = (uint16_t)(((pDmaBuffer[1] & SENT_CHN_SBIT2__SMSG_DATA_MASK) >> SENT_CHN_SBIT2__SMSG_DATA_SHIFT) & 0xFFU);
            pMsg->u8ID = (uint8_t)(((pDmaBuffer[1] & SENT_CHN_SBIT2__SMSG_DATA_MASK) >> SENT_CHN_SBIT2__SMSG_DATA_SHIFT) >> 8U);
        }
        else if(SENT_SERIAL_MESSAGE_ENHANCE_12DATA_8ID == pMsg->eMsgType)
        {
            pMsg->u8CRC	= (uint8_t)((pDmaBuffer[1] & SENT_CHN_SBIT2__SMSG_CRC_MASK) >> SENT_CHN_SBIT2__SMSG_CRC_SHIFT);
            pMsg->u16Data = (uint16_t)((pDmaBuffer[1] & SENT_CHN_SBIT2__SMSG_DATA_MASK) >> SENT_CHN_SBIT2__SMSG_DATA_SHIFT);
            pMsg->u8ID = (uint8_t)((((pDmaBuffer[0] & SENT_CHN_SBIT3__ID7_4_OR_ID3_0_MASK) >> SENT_CHN_SBIT3__ID7_4_OR_ID3_0_SHIFT) << 4U) |\
                                   ((pDmaBuffer[0] & SENT_CHN_SBIT3__ID3_0_OR_DATA15_12_MASK) >> SENT_CHN_SBIT3__ID3_0_OR_DATA15_12_SHIFT));
        }
        else if(SENT_SERIAL_MESSAGE_ENHANCE_16DATA_4ID == pMsg->eMsgType)
        {
            pMsg->u8CRC	= (uint8_t)((pDmaBuffer[1] & SENT_CHN_SBIT2__SMSG_CRC_MASK) >> SENT_CHN_SBIT2__SMSG_CRC_SHIFT);
            pMsg->u16Data = (uint16_t)((((pDmaBuffer[0] & SENT_CHN_SBIT3__ID3_0_OR_DATA15_12_MASK) >> SENT_CHN_SBIT3__ID3_0_OR_DATA15_12_SHIFT) << 12U) |\
                                       ((pDmaBuffer[1] & SENT_CHN_SBIT2__SMSG_DATA_MASK) >> SENT_CHN_SBIT2__SMSG_DATA_SHIFT));
            pMsg->u8ID = (uint8_t)((pDmaBuffer[0] & SENT_CHN_SBIT3__ID7_4_OR_ID3_0_MASK) >> SENT_CHN_SBIT3__ID7_4_OR_ID3_0_SHIFT);
        }
        else
        {
            eRet = SENT_RETURN_E_NOT_OK;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_PARAM;
    }

    return eRet;
}

Sent_ReturnType SENT_EnableGlobalFastMsgNotification(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            SENT_HWA_EnableChannelFastMessageInterrupt(pSent, (uint8_t)eChannel);
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_DisableGlobalFastMsgNotification(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            SENT_HWA_DisableChannelFastMessageInterrupt(pSent, (uint8_t)eChannel);
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_EnableGlobalSlowMsgNotification(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            SENT_HWA_EnableChannelSlowMessageInterrupt(pSent, (uint8_t)eChannel);
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_DisableGlobalSlowMsgNotification(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            SENT_HWA_DisableChannelSlowMessageInterrupt(pSent, (uint8_t)eChannel);
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_EnableGlobalFastFifoMsgNotification(const Sent_InstanceType eInstance)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if(eInstance < SENT_INSTANCE_MAX)
        {
            pSent = aSent_Base[eInstance];

            SENT_HWA_EnableFastMessageFIFOOverflowInterrupt(pSent);
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_DisableGlobalFastFifoMsgNotification(const Sent_InstanceType eInstance)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if(eInstance < SENT_INSTANCE_MAX)
        {
            pSent = aSent_Base[eInstance];

            SENT_HWA_DisableFastMessageFIFOOverflowInterrupt(pSent);
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_ConfigChannelStatusNotification(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, const Sent_ChannelInterruptType *sInterruptEn)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            SENT_HWA_EnableChannelBusIdleInterrupt(pSent, (uint8_t)eChannel, sInterruptEn->bBusIdleITEn);
            SENT_HWA_EnableChannelSPCOverRunInterrupt(pSent, (uint8_t)eChannel, sInterruptEn->bSpcOverrunITEn);
            SENT_HWA_EnableChannelCALDiagInterrupt(pSent, (uint8_t)eChannel, sInterruptEn->bCalDiagErrITEn);
            SENT_HWA_EnableChannelCalFailInterrupt(pSent, (uint8_t)eChannel, sInterruptEn->bCalFailITEn);
            SENT_HWA_EnableChannelCalResyncInterrupt(pSent, (uint8_t)eChannel, sInterruptEn->bCalResyncErrITEn);
            SENT_HWA_EnableChannelEdgeERRInterrupt(pSent, (uint8_t)eChannel, sInterruptEn->bFallingEdgeNumErrITEn);
            SENT_HWA_EnableChannelFCRCInterrupt(pSent, (uint8_t)eChannel, sInterruptEn->bFastMsgCrcErrITEn);
            SENT_HWA_EnableChannelFOVFLInterrupt(pSent, (uint8_t)eChannel, sInterruptEn->bFastMsgOFITEn);
            SENT_HWA_EnableChannelNibbleErrorInterrupt(pSent, (uint8_t)eChannel, sInterruptEn->bNibbleValueErrITEn);
            SENT_HWA_EnableChannelPPDiagInterrupt(pSent, (uint8_t)eChannel, sInterruptEn->bPrePulseDiagErrITEn);
            SENT_HWA_EnableChannelSCRCInterrupt(pSent, (uint8_t)eChannel, sInterruptEn->bSlowMsgCrcErrITEn);
            SENT_HWA_EnableChannelSOVFLInterrupt(pSent, (uint8_t)eChannel, sInterruptEn->bSlowMsgOFITEn);
            SENT_HWA_EnableChannelCalERRInterrupt(pSent, (uint8_t)eChannel, sInterruptEn->bCalErrITEn);
            //SENT_HWA_EnableChannelAllErrorInterrupt(pSent, eChannel);
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_RequestSPCPulse(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            SENT_HWA_StartChannelSPC(pSent, (uint8_t)eChannel);
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_GetFastMsgReadyFlag(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, bool *pFlag)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            *pFlag = SENT_HWA_GetFastMessageReadyFlag(pSent, (uint8_t)eChannel);
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_GetSlowMsgReadyFlag(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, bool *pFlag)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            *pFlag = SENT_HWA_GetSlowMessageReadyFlag(pSent, (uint8_t)eChannel);
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_GetChannelStatus(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, uint32_t *pStatus)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            *pStatus = SENT_HWA_GetChannelStatus(pSent, (uint8_t)eChannel);
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_ClearChannelStatus(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, uint32_t Status)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            SENT_HWA_ClearChannelStatus(pSent, (uint8_t)eChannel, Status);
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

Sent_ReturnType SENT_GetChannelSPCBusyFlag(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, bool *pflag)
{
    Sent_ReturnType eRet = SENT_RETURN_OK;
    SENT_Type *pSent;

    if(true == aSentInit[eInstance])
    {
        if((eInstance < SENT_INSTANCE_MAX) && (eChannel < SENT_CHANNEL_MAX))
        {
            pSent = aSent_Base[eInstance];

            *pflag = SENT_HWA_GetChanneSPCBusyFlag(pSent, (uint8_t)eChannel);
        }
        else
        {
            eRet = SENT_RETURN_E_PARAM;
        }
    }
    else
    {
        eRet = SENT_RETURN_E_UNINIT;
    }

    return eRet;
}

void SENT0_IRQHandler(void)
{
    SENT_IRQ_Handler(SENT_INSTANCE_0);
}

void SENT1_IRQHandler(void)
{
    SENT_IRQ_Handler(SENT_INSTANCE_1);
}
