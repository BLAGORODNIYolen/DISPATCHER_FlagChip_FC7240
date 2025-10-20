/**
 * @file fc7xxx_driver_msc.c
 * @author Flagchip
 * @brief FC7240 MSC driver type definition and API
 * @version 0.1.0
 * @date 2024-01-10
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
 *   Revision History:
 *
 *   Version     Date          Initials      CR#          Descriptions
 *   ---------   ----------    ------------  ----------   ---------------
 *   0.1.0       2024-01-10    Flagchip084   N/A          FC7240 release version
 ******************************************************************************** */

#include "fc7xxx_driver_msc.h"

/* ################################################################################## */
/* ####################################### Macro #################################### */

/* ################################################################################## */
/* ################################### Type define ################################## */

/* ################################################################################## */
/* ################################ Local Variables ################################# */
static MSC_Type *const     s_apMscBase[MSC_INSTANCE_COUNT]          = MSC_BASE_PTRS;
static MSC_ISRCallbackType s_apMscRFISRCallback[MSC_INSTANCE_COUNT] = {NULL};
static MSC_ISRCallbackType s_apMscTFISRCallback[MSC_INSTANCE_COUNT] = {NULL};
static MSC_ISRCallbackType s_apMscCFISRCallback[MSC_INSTANCE_COUNT] = {NULL};
static MSC_ISRCallbackType s_apMscDFISRCallback[MSC_INSTANCE_COUNT] = {NULL};
static MSC_ISRCallbackType s_apMscTOISRCallback[MSC_INSTANCE_COUNT] = {NULL};

/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */
static void MSCn_IRQHandler(const MSC_InstanceType eInstance);
static void MSC_ClearReceiveInterruptFlag(const MSC_InstanceType eInstance);
static void MSC_ClearTimeFrameInterruptFlag(const MSC_InstanceType eInstance);
static void MSC_ClearCommandFrameInterruptFlag(const MSC_InstanceType eInstance);
static void MSC_ClearDataFrameInterruptFlag(const MSC_InstanceType eInstance);
/* ################################################################################## */
/* ######################### Global prototype Functions  ############################ */
void MSC0_IRQHandler(void);
/* ################################################################################## */
/* ################################ Local Functions  ################################ */
static void MSCn_IRQHandler(const MSC_InstanceType eInstance)
{
    uint32_t u32IntFlag = MSC_GetInterruptStatus(eInstance);
    MSC_Type *const pMsc = s_apMscBase[eInstance];

    if (u32IntFlag & MSC_INSR_RFI_MASK)
    {
        MSC_ClearReceiveInterruptFlag(eInstance);
        if (MSC_HWA_GetRfieEnable(pMsc) && s_apMscRFISRCallback[eInstance] != NULL)
        {
            s_apMscRFISRCallback[eInstance](eInstance);
        }
    }
    if (u32IntFlag & MSC_INSR_TFI_MASK)
    {
        MSC_ClearTimeFrameInterruptFlag(eInstance);
        if (MSC_HWA_GetTfieEnable(pMsc) && s_apMscTFISRCallback[eInstance] != NULL)
        {
            s_apMscTFISRCallback[eInstance](eInstance);
        }
    }
    if (u32IntFlag & MSC_INSR_CFI_MASK)
    {
        MSC_ClearCommandFrameInterruptFlag(eInstance);
        if (MSC_HWA_GetCfieEnable(pMsc) && s_apMscCFISRCallback[eInstance] != NULL)
        {
            s_apMscCFISRCallback[eInstance](eInstance);
        }
    }
    if (u32IntFlag & MSC_INSR_DFI_MASK)
    {
        MSC_ClearDataFrameInterruptFlag(eInstance);
        if (MSC_HWA_GetDfieEnable(pMsc) && s_apMscDFISRCallback[eInstance] != NULL)
        {
            s_apMscDFISRCallback[eInstance](eInstance);
        }
    }
    if (MSC_HWA_GetTofEnable(pMsc))
    {
        MSC_HWA_ClearTofEnable(pMsc);
        if (MSC_HWA_GetToieEnable(pMsc) && s_apMscTOISRCallback[eInstance] != NULL)
        {
            s_apMscTOISRCallback[eInstance](eInstance);
        }
    }
}
/* ################################################################################## */
/* ################################ Global Functions ################################ */

void MSC0_IRQHandler(void)
{
    MSCn_IRQHandler(MSC_INSTANCE_0);
}

MSC_ReturnType MSC_init(const MSC_InstanceType eInstance, const MSC_InitCfgType *pInitConfig)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);
    DEV_ASSERT(pInitConfig != NULL);

    MSC_Type *const pMsc = s_apMscBase[eInstance];
    uint32_t        u32TempValue;
    uint32_t        u32TimeoutCount = 0xFFFFFFU;

    if (pInitConfig->u8CommandBitLength > 32U || pInitConfig->u8SRLDataBitLength > 16U || pInitConfig->u8SRHDataBitLength > 16U)
    {
        return MSC_RETURN_E_PARAM;
    }

    MSC_HWA_SetMsrRst(pMsc);

    while (MSC_HWA_GetMsrRdone(pMsc) == false)
    {
        u32TimeoutCount--;
        if (u32TimeoutCount == 0U)
        {
            break;
        }
    }

    if (u32TimeoutCount == 0U)
    {
        return MSC_RETURN_E_NOT_OK;
    }

    MSC_HWA_ClearMsrDone(pMsc);

    u32TempValue = MSC_TCCTR_PL(pInitConfig->u8PassiveLength) | MSC_TCCTR_WM(pInitConfig->eWorkMode) | MSC_TCCTR_SELH(pInitConfig->bSelSRH) | MSC_TCCTR_SELL(pInitConfig->bSelSRL) |
                   MSC_TCCTR_NBS(pInitConfig->u8CommandBitLength) | MSC_TCCTR_NHBS(pInitConfig->u8SRHDataBitLength) | MSC_TCCTR_NLBS(pInitConfig->u8SRLDataBitLength);
    MSC_HWA_SetTcctr(pMsc, u32TempValue);

    MSC_HWA_SetNp(pMsc, pInitConfig->u8PTFNumber);

    u32TempValue =
        MSC_RCCSR_RFT(pInitConfig->eRsvFrameType) | MSC_RCCSR_RBR(pInitConfig->eBaudRate) | MSC_RCCSR_PCTL(pInitConfig->eParity) | MSC_RCCSR_HIDC(pInitConfig->bDelayControl);
    MSC_HWA_SetRccsr(pMsc, u32TempValue);

    return MSC_RETURN_OK;
}

void MSC_initInterrupt(const MSC_InstanceType eInstance, const MSC_InterruptCfgType *pInteruptConfig)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);
    DEV_ASSERT(pInteruptConfig != NULL);
    uint32_t        u32TempValue;
    MSC_Type *const pMsc = s_apMscBase[eInstance];

    u32TempValue = MSC_INCR_RFIE(pInteruptConfig->eRFIEMode) | MSC_INCR_TFIE(pInteruptConfig->bTFIntEnable) | MSC_INCR_CFIE(pInteruptConfig->bCFIntEnable) |
                   MSC_INCR_DFIE(pInteruptConfig->eDFIEMode);
    MSC_HWA_SetIncr(pMsc, u32TempValue);

    u32TempValue = MSC_RTOR_TOIE(pInteruptConfig->bTOIntEnable) | MSC_RTOR_TOV(pInteruptConfig->u16TimeoutValue);
    MSC_HWA_SetRtor(pMsc, u32TempValue);

    s_apMscRFISRCallback[eInstance] = pInteruptConfig->pReceiveFrameISRCallback;
    s_apMscTFISRCallback[eInstance] = pInteruptConfig->pTimeFrameISRCallback;
    s_apMscCFISRCallback[eInstance] = pInteruptConfig->pCommandFrameISRCallback;
    s_apMscDFISRCallback[eInstance] = pInteruptConfig->pDataFrameISRCallback;
    s_apMscTOISRCallback[eInstance] = pInteruptConfig->pReceiveTimeOutISRCallback;
}

void MSC_SelTranmittingSource(const MSC_InstanceType eInstance, uint32_t u32SourceMask, MSC_TransSourceType eSourceType)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);

    MSC_Type *const pMsc          = s_apMscBase[eInstance];
    uint32_t        u32TempValue1 = 0;
    uint16_t        u32TempValue2;
    uint8_t         u8i;

    u32TempValue2 = (uint16_t)(u32SourceMask & 0xFFFFU);

    for (u8i = 0U; u8i < 16U; u8i++)
    {
        if ((u32TempValue2 & 0x01U) != 0U)
        {
            u32TempValue1 |= (uint32_t)eSourceType << (u8i << 1U);
        }
        u32TempValue2 = u32TempValue2 >> 1;
    }
    MSC_HWA_SetTcslr(pMsc, u32TempValue1);

    u32TempValue2 = (uint16_t)((u32SourceMask >> 16) & 0xFFFFU);
    for (u8i = 0U; u8i < 16U; u8i++)
    {
        if ((u32TempValue2 & 0x01U) != 0U)
        {
            u32TempValue1 |= (uint32_t)eSourceType << (u8i << 1U);
        }
        u32TempValue2 = u32TempValue2 >> 1;
    }
    MSC_HWA_SetTcshr(pMsc, u32TempValue1);
}

void MSC_SetEmergencyLoad(const MSC_InstanceType eInstance, uint32_t u32Value)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);

    MSC_Type *const pMsc = s_apMscBase[eInstance];

    MSC_HWA_SetTcelr(pMsc, u32Value);
}

void MSC_SetIOControl(const MSC_InstanceType eInstance, const MSC_IOControlInitType *pIOConfig)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);

    uint32_t        u32TempValue = 0;
    MSC_Type *const pMsc         = s_apMscBase[eInstance];

    u32TempValue |= MSC_IOCR_IDS(pIOConfig->eSDIsel);
    u32TempValue |= MSC_IOCR_ESC(pIOConfig->eENCSel);
    u32TempValue |= MSC_IOCR_ESH(pIOConfig->eENHSel);
    u32TempValue |= MSC_IOCR_ESL(pIOConfig->eENLSel);
    u32TempValue |= MSC_IOCR_FCLCTRL(pIOConfig->eFclCtrl);
    u32TempValue |= MSC_IOCR_IPS(pIOConfig->eSDIPol);
    u32TempValue |= MSC_IOCR_ENP(pIOConfig->eENXPol);
    u32TempValue |= MSC_IOCR_SOP(pIOConfig->eSOPPol);
    u32TempValue |= MSC_IOCR_FCLP(pIOConfig->eFCLPPol);

    MSC_HWA_SetIocr(pMsc, u32TempValue);
}

void MSC_Enable(const MSC_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);
    MSC_Type *const pMsc = s_apMscBase[eInstance];

    MSC_HWA_SetMscEnable(pMsc, true);
}

void MSC_Disable(const MSC_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);
    MSC_Type *const pMsc = s_apMscBase[eInstance];

    MSC_HWA_SetMscEnable(pMsc, false);
}

void MSC_SetDataFrame(const MSC_InstanceType eInstance, uint32_t u32Data)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);
    MSC_Type *const pMsc = s_apMscBase[eInstance];

    MSC_HWA_SetTcdar(pMsc, u32Data);
}

void MSC_SendDataFrame(const MSC_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);
    MSC_Type *const pMsc = s_apMscBase[eInstance];
    MSC_HWA_SetDataNeedSend(pMsc);
}

void MSC_SendCommandFrame(const MSC_InstanceType eInstance, uint32_t u32Command)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);
    MSC_Type *const pMsc = s_apMscBase[eInstance];

    MSC_HWA_SetTccor(pMsc, u32Command);
}

uint8_t MSC_GetReceivedFrameAddr(const MSC_InstanceType eInstance, MSC_RDRxIndexType eIndex)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);
    DEV_ASSERT(eIndex < MSC_RDRx_COUNT);

    MSC_Type *const pMsc   = s_apMscBase[eInstance];
    uint8_t         u8Addr = 0U;

    if (eIndex == MSC_RDR0)
    {
        u8Addr = MSC_HWA_GetRdr0Addr(pMsc);
    }
    else if (eIndex == MSC_RDR1)
    {
        u8Addr = MSC_HWA_GetRdr1Addr(pMsc);
    }
    else if (eIndex == MSC_RDR2)
    {
        u8Addr = MSC_HWA_GetRdr2Addr(pMsc);
    }
    else if (eIndex == MSC_RDR3)
    {
        u8Addr = MSC_HWA_GetRdr3Addr(pMsc);
    }
    else {}

    return u8Addr;
}

MSC_ReceiveStatusType MSC_GetReceivedFrame(const MSC_InstanceType eInstance, MSC_RDRxIndexType eIndex, uint8_t *pData)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);
    DEV_ASSERT(eIndex < MSC_RDRx_COUNT);

    MSC_Type *const       pMsc       = s_apMscBase[eInstance];
    MSC_ReceiveStatusType eRsvStatus = MSC_RSV_SUCCESS;

    if (eIndex == MSC_RDR0)
    {
        eRsvStatus = MSC_HWA_GetRdr0Rerr(pMsc);
        if (MSC_RSV_SUCCESS == eRsvStatus)
        {
            *pData = MSC_HWA_GetRdr0Data(pMsc);
        }
    }
    else if (eIndex == MSC_RDR1)
    {
        eRsvStatus = MSC_HWA_GetRdr1Rerr(pMsc);
        if (MSC_RSV_SUCCESS == eRsvStatus)
        {
            *pData = MSC_HWA_GetRdr1Data(pMsc);
        }
    }
    else if (eIndex == MSC_RDR2)
    {
        eRsvStatus = MSC_HWA_GetRdr2Rerr(pMsc);
        if (MSC_RSV_SUCCESS == eRsvStatus)
        {
            *pData = MSC_HWA_GetRdr2Data(pMsc);
        }
    }
    else if (eIndex == MSC_RDR3)
    {
        eRsvStatus = MSC_HWA_GetRdr3Rerr(pMsc);
        if (MSC_RSV_SUCCESS == eRsvStatus)
        {
            *pData = MSC_HWA_GetRdr3Data(pMsc);
        }
    }
    else {}

    return eRsvStatus;
}

uint32_t MSC_GetInterruptStatus(const MSC_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);

    MSC_Type *const pMsc = s_apMscBase[eInstance];
    return MSC_HWA_GetInsr(pMsc);
}

void MSC_EnableTrasmit(const MSC_InstanceType eInstance, bool bEnable)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);

    MSC_Type *const pMsc = s_apMscBase[eInstance];

    if (bEnable)
    {
        MSC_HWA_ClearTcdis(pMsc);
    }
    else
    {
        MSC_HWA_SetTcdis(pMsc);
    }
}

void MSC_ClearReceiveInterruptFlag(const MSC_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);

    MSC_Type *const pMsc = s_apMscBase[eInstance];

    MSC_HWA_ClearCrfi(pMsc);
}

void MSC_ClearTimeFrameInterruptFlag(const MSC_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);

    MSC_Type *const pMsc = s_apMscBase[eInstance];

    MSC_HWA_ClearCtfi(pMsc);
}

void MSC_ClearCommandFrameInterruptFlag(const MSC_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);

    MSC_Type *const pMsc = s_apMscBase[eInstance];

    MSC_HWA_ClearCcfi(pMsc);
}

void MSC_ClearDataFrameInterruptFlag(const MSC_InstanceType eInstance)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);

    MSC_Type *const pMsc = s_apMscBase[eInstance];

    MSC_HWA_ClearCdfi(pMsc);
}

void MSC_EnableDataFrameInterrupt(const MSC_InstanceType eInstance, bool bEnable)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);

    MSC_Type *const pMsc = s_apMscBase[eInstance];

    MSC_HWA_SetDfieEnable(pMsc, bEnable);
}

void MSC_EnableCommandFrameInterrupt(const MSC_InstanceType eInstance, bool bEnable)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);

    MSC_Type *const pMsc = s_apMscBase[eInstance];

    MSC_HWA_SetCfieEnable(pMsc, bEnable);
}

void MSC_EnableTimeFrameInterrupt(const MSC_InstanceType eInstance, bool bEnable)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);

    MSC_Type *const pMsc = s_apMscBase[eInstance];

    MSC_HWA_SetTfieEnable(pMsc, bEnable);
}

void MSC_EnableReceiveInterrupt(const MSC_InstanceType eInstance, bool bEnable)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);

    MSC_Type *const pMsc = s_apMscBase[eInstance];

    MSC_HWA_SetRfieEnable(pMsc, bEnable);
}

void MSC_EnableTimeoutInterrupt(const MSC_InstanceType eInstance, bool bEnable)
{
    DEV_ASSERT((uint8_t)eInstance < MSC_INSTANCE_COUNT);

    MSC_Type *const pMsc = s_apMscBase[eInstance];

    MSC_HWA_SetToieEnable(pMsc, bEnable);
}

MSC_ReturnType Msc_SwitchENXChannel(const MSC_InstanceType eInstance, Msc_ENxType eEnx, Msc_ENxActiveType eENn, uint32_t u32TimeoutLoops)
{
    MSC_ReturnType  eTempReturn = MSC_RETURN_E_NOT_OK;
    uint32          u32TempValue;
    uint32          u32TempTryCount = 0u;
    uint8           u8CmdNeedSend;
    uint8           u8CmdFrameBusy;
    uint8           u8DataNeedSend;
    uint8           u8DataFrameBusy;
    MSC_Type *const pMsc = s_apMscBase[eInstance];

    if (eEnx == MSC_ENC)
    {
        do
        {
            u8CmdFrameBusy = MSC_HWA_GetCfb(pMsc);
            u8CmdNeedSend  = MSC_HWA_GetCmdNeedSend(pMsc);

            if ((u8CmdNeedSend == TRUE) || (u8CmdFrameBusy == TRUE))
            {
                u32TempValue = TRUE;
            }
            else
            {
                u32TempValue = FALSE;
            }

            /* check receive rc flag */
            if (u32TempValue == FALSE)
            {
                break;
            }
            else
            {
                u32TempTryCount++;
            }
        } while (u32TempTryCount < u32TimeoutLoops);

        if (u32TempTryCount != u32TimeoutLoops)
        {
            u32TempValue = (MSC_HWA_GetIocr(pMsc) & ~MSC_IOCR_ESC_MASK) | MSC_IOCR_ESC(eENn);
            MSC_HWA_SetIocr(pMsc, u32TempValue);
            eTempReturn = MSC_RETURN_OK;
        }
    }
    else
    {
        do
        {
            u8DataFrameBusy = MSC_HWA_GetDfb(pMsc);
            u8DataNeedSend  = MSC_HWA_GetDataNeedSend(pMsc);

            if ((u8DataFrameBusy == TRUE) || (u8DataNeedSend == TRUE))
            {
                u32TempValue = TRUE;
            }
            else
            {
                u32TempValue = FALSE;
            }

            /* check receive rc flag */
            if (u32TempValue == FALSE)
            {
                break;
            }
            else
            {
                u32TempTryCount++;
            }
        } while (u32TempTryCount < u32TimeoutLoops);

        if (u32TempTryCount != u32TimeoutLoops)
        {
            if (eEnx == MSC_ENH)
            {
                u32TempValue = (MSC_HWA_GetIocr(pMsc) & ~MSC_IOCR_ESH_MASK) | MSC_IOCR_ESH(eENn);
                MSC_HWA_SetIocr(pMsc, u32TempValue);
            }
            else
            {
                u32TempValue = (MSC_HWA_GetIocr(pMsc) & ~MSC_IOCR_ESL_MASK) | MSC_IOCR_ESL(eENn);
                MSC_HWA_SetIocr(pMsc, u32TempValue);
            }
            eTempReturn = MSC_RETURN_OK;
        }
    }

    return eTempReturn;
}

MSC_ReturnType Msc_SwitchSDIChannel(const MSC_InstanceType eInstance, MSC_SDISelectionType eSDIChannel, uint32_t u32TimeoutLoops)
{
    MSC_ReturnType  eTempReturn = MSC_RETURN_E_NOT_OK;
    uint32_t        u32TempValue;
    uint32_t        u32TempTryCount = 0u;
    MSC_Type *const pMsc            = s_apMscBase[eInstance];

    do
    {
        u32TempValue = MSC_HWA_GetRxBusy(pMsc);

        /* check receive rc flag */
        if (u32TempValue == 0U)
        {
            break;
        }
        else
        {
            u32TempTryCount++;
        }
    } while (u32TempTryCount < u32TimeoutLoops);

    if (u32TempTryCount != u32TimeoutLoops)
    {
        u32TempValue = (MSC_HWA_GetIocr(pMsc) & ~MSC_IOCR_IDS_MASK) | MSC_IOCR_IDS(eSDIChannel);
        MSC_HWA_SetIocr(pMsc, u32TempValue);

        eTempReturn = MSC_RETURN_OK;
    }
    return eTempReturn;
}
