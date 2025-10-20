/**
 * @file fc7xxx_driver_dma.c
 * @author Flagchip0126
 * @brief FC7xxx DMA driver source code
 * @version 0.1.0
 * @date 2024-01-15
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Author        CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-15    Flagchip0126  N/A          First version for FC7240
   ******************************************************************************** */

#include "fc7xxx_driver_dma.h"
#include "interrupt_manager.h"

#define DMA_CHANNEL_INVALID   (0xFFU)

#define CPM_CORE_ID_CORE0     (0x0U)
#define CPM_CORE_ID_CORE1     (0x2U)
#define CPM_CORE_ID_CORE2     (0x4U)

static uint8_t s_aDmaDumoUsedStatus[DMA_DUMO_COUNT] = {DMA_CHANNEL_INVALID, DMA_CHANNEL_INVALID, DMA_CHANNEL_INVALID, DMA_CHANNEL_INVALID};

static DMA_TransferCompleteCallbackType s_dmaTransferCompleteNotify[DMA_INSTANCE_COUNT][DMA_CFG_COUNT] = {NULL};
static DMA_TransferErrorCallbackType s_dmaTransferErrorNotify[DMA_INSTANCE_COUNT][DMA_CFG_COUNT] = {NULL};

/**
 * @brief DMA IRQ function prototypes
 *
 */
void DMA0_IRQHandler(void);
void DMA1_IRQHandler(void);
void DMA2_IRQHandler(void);
void DMA3_IRQHandler(void);
void DMA4_IRQHandler(void);
void DMA5_IRQHandler(void);
void DMA6_IRQHandler(void);
void DMA7_IRQHandler(void);
void DMA8_IRQHandler(void);
void DMA9_IRQHandler(void);
void DMA10_IRQHandler(void);
void DMA11_IRQHandler(void);
void DMA12_IRQHandler(void);
void DMA13_IRQHandler(void);
void DMA14_IRQHandler(void);
void DMA15_IRQHandler(void);
void DMA_Error_IRQHandler(void);


/**
 * @brief Get the first unused DUMO register index
 *
 * @param [out] pDumoIndex the DUMO register index
 * @return DMA_StatusType whether there is unused DUMO index
 * @return DMA_STATUS_SUCCESS the DUMO register index is successfully get
 * @return DMA_STATUS_NO_RESOURCE all DUMO registers are already occupied
 */
static inline DMA_StatusType DMA_GetDumoIndex(uint8_t *pDumoIndex);

/**
 * @brief Check whether the value is power of 2 and return the ceil value of the log2(u32Value)
 *
 * @param [in] u32Value the value to check
 * @param [out] u8Log2 the ceil value of log2(u32Value)
 * @return true the u32Value is power of 2
 * @return false the u32Value is not power of 2
 */
static bool DMA_IsPowerOf2(uint32_t u32Value, uint8_t *u8Log2);

/**
 * @brief Reset the DMAMUX config values
 * @param Dmamux_Instance the selected DMA Instance
 *
 */
static inline void Dmamux_Reset(DMAMUX_Type * const Dmamux_Instance);

/**
 * @brief Get the data offset value of the selected increment mode and data size
 *
 * @param eIncMode the selected increment mode
 * @param eDataSize the selected data size
 * @return int16_t the calculated data offset
 */
static inline uint16_t DMA_GetDataOffset(DMA_IncrementModeType eIncMode,
        DMA_TransferSizeType eDataSize);

/**
 * @brief Get the IRQ number of the selected DMA channel
 *
 * @param u8Channel the selected DMA channel
 * @return IRQn_Type the IRQ number of the selected DMA channel
 */
//static inline IRQn_Type DMA_GetChannelIRQn(const DMA_InstanceType eDma_Instance);

/**
 * @brief The internal interrupt handler for DMA transfer complete
 *
 * @param u8Channel the channel of the DMA interrpt
 */
static inline void DMA_Transfer_Complete_IRQHandler(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel);

static inline DMA_StatusType DMA_GetDumoIndex(uint8_t *pDumoIndex)
{
    DMA_StatusType ret = DMA_STATUS_ERROR;
    for (*pDumoIndex = 0U; *pDumoIndex < DMA_DUMO_COUNT; (*pDumoIndex)++)
    {
        if (s_aDmaDumoUsedStatus[*pDumoIndex] == DMA_CHANNEL_INVALID)
        {
            ret = DMA_STATUS_SUCCESS;
            break;
        }
    }
    if (*pDumoIndex == DMA_DUMO_COUNT)
    {
        ret = DMA_STATUS_NO_RESOURCE;
    }
    return ret;
}

static bool DMA_IsPowerOf2(uint32_t u32Value, uint8_t *u8Log2)
{
    bool ret = (bool)false;
    *u8Log2 = 0U;
    while (u32Value > (1UL << *u8Log2))
    {
        (*u8Log2)++;
    }
    if ((u32Value & ((1UL << *u8Log2) - 1U)) == 0U)
    {
        ret = (bool)true;
    }
    return ret;
}

static inline uint16_t DMA_GetDataOffset(DMA_IncrementModeType eIncMode,
        DMA_TransferSizeType eDataSize)
{
    uint16_t u16DataOffset = 0U;
    switch (eIncMode)
    {
    case DMA_INCREMENT_DISABLE:
    {
        u16DataOffset = 0U;
        break;
    }

    case DMA_INCREMENT_DATA_SIZE:
    {
        u16DataOffset = (uint16_t)(1UL << ((uint8_t)eDataSize));
        break;
    }

    case DMA_INCREMENT_DATA_SIZE_4BYTE_ALIGNED:
    {
        switch (eDataSize)
        {
        case DMA_TRANSFER_SIZE_1B:
        case DMA_TRANSFER_SIZE_2B:
        case DMA_TRANSFER_SIZE_4B:
            u16DataOffset = 4U;
            break;

        case DMA_TRANSFER_SIZE_8B:
            u16DataOffset = 8U;
            break;

        case DMA_TRANSFER_SIZE_32B:
            u16DataOffset = 32U;
            break;

        default:
            break;
        }
        break;
    }

    default:
        break;
    }
    return u16DataOffset;
}

void DMA0_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_0);
}

void DMA1_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_1);
}

void DMA2_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_2);
}

void DMA3_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_3);
}

void DMA4_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_4);
}

void DMA5_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_5);
}

void DMA6_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_6);
}

void DMA7_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_7);
}

void DMA8_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_8);
}

void DMA9_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_9);
}

void DMA10_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_10);
}

void DMA11_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_11);
}

void DMA12_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_12);
}

void DMA13_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_13);
}

void DMA14_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_14);
}

void DMA15_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(DMA_INSTANCE_0, DMA_CHANNEL_15);
}

void DMA_Error_IRQHandler(void)
{
    uint8_t u8Channel;
    DMA_InstanceType eDma_Instance;
    DMA_Type *pDma;
    DMA_Type * aDma[] = DMA_BASE_PTRS;

    eDma_Instance = DMA_INSTANCE_0;

    pDma = aDma[DMA_INSTANCE_0];
    for (u8Channel = 0U; u8Channel < DMA_CFG_COUNT; u8Channel++)
    {
        if (DMA_HWA_GetChannelErrorFlag(pDma, u8Channel) == true)
        {
            DMA_HWA_ClearChannelErrorFlag(pDma, u8Channel);
            if (s_dmaTransferErrorNotify[eDma_Instance][u8Channel] != NULL)
            {
                s_dmaTransferErrorNotify[eDma_Instance][u8Channel]();
            }
        }
    }
}

static inline void DMA_Transfer_Complete_IRQHandler(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel)
{
    DMA_Type * aDma[] = DMA_BASE_PTRS;
    DMA_Type *const pDma = aDma[eDma_Instance];

    DMA_HWA_ClearChannelInterruptFlag(pDma, (uint8_t)eChannel);
    if (s_dmaTransferCompleteNotify[eDma_Instance][eChannel] != NULL)
    {
        s_dmaTransferCompleteNotify[eDma_Instance][eChannel]();
    }
}

static inline void Dmamux_Reset(DMAMUX_Type * const Dmamux_Instance)
{
    uint8_t u8Index;
    for (u8Index = 0U; u8Index < DMAMUX_CHCFG_COUNT; u8Index++)
    {
        DMAMUX_HWA_SetRequestSource(Dmamux_Instance, u8Index, false, DMA_REQ_DISABLED);
    }
    for (u8Index = 0U; u8Index < DMAMUX_CHTRG_TRG_COUNT; u8Index++)
    {
    	//DMAMUX_HWA_SetPeriodicTrigFlag(Dmamux_Instance, u8Index, false);
    }
}

void DMA_Init(const DMA_InstanceType eDma_Instance, const DMA_InitType *const pInitCfg)
{
    DEV_ASSERT(eDma_Instance < DMA_INSTANCE_MAX);
    DEV_ASSERT(pInitCfg != NULL);

    DMA_Type * aDma[] = DMA_BASE_PTRS;
    DMA_Type *const pDma = aDma[eDma_Instance];

    DMA_DeInit(eDma_Instance);
    DMA_HWA_SetHaltOnErrorFlag(pDma, pInitCfg->bHaltOnError);
    DMA_HWA_SetArbitrationAlgorithm(pDma, pInitCfg->eArbitrationAlgorithm);
    DMA_HWA_SetInnerLoopMappingEnableFlag(pDma, true);
}

void DMA_DeInit(const DMA_InstanceType eDma_Instance)
{
    DEV_ASSERT(eDma_Instance < DMA_INSTANCE_MAX);

    uint8_t u8Index;
    DMA_Type * aDma[] = DMA_BASE_PTRS;
    DMA_Type *const pDma = aDma[eDma_Instance];
    DMAMUX_Type * aDmamux[] = DMAMUX_BASE_PTRS;
    DMAMUX_Type *const pDmamux = aDmamux[eDma_Instance];

    DMA_HWA_SetControlRegister(pDma, 0U);
    DMA_HWA_DisableAllChannelErrorInterrupt(pDma);
    DMA_HWA_DisableAllChannelRequest(pDma);
    DMA_HWA_ClearAllChannelDoneStatus(pDma);
    DMA_HWA_ClearAllChannelErrorFlag(pDma);
    DMA_HWA_ClearAllChannelInterruptFlag(pDma);
    pDma->DUME[0] = 0U;
    for (u8Index = 0U; u8Index < DMA_DUMO_COUNT; u8Index++)
    {
        DMA_HWA_SetUnalignModulo(pDma, u8Index, 0U, 0U);
    }
    for (u8Index = 0U; u8Index < DMA_CFG_COUNT; u8Index++)
    {
        DMA_HWA_SetUnalignModuloEnableFlag(pDma, u8Index, false, false);
        DMA_HWA_SetPriority(pDma, u8Index, u8Index);
        DMA_HWA_SetSrcAddr(pDma, u8Index, 0U);
        DMA_HWA_SetSrcOffset(pDma, u8Index, 0);
        DMA_HWA_SetSrcLastAddrAdjustment(pDma, u8Index, 0);
        DMA_HWA_SetDestAddr(pDma, u8Index, 0U);
        DMA_HWA_SetDestOffset(pDma, u8Index, 0);
        DMA_HWA_SetDestLastAddrAdjustment(pDma, u8Index, 0);
        DMA_HWA_SetSrcDataSize(pDma, u8Index, DMA_TRANSFER_SIZE_1B);
        DMA_HWA_SetSrcModulo(pDma, u8Index, 0U);
        DMA_HWA_SetDestDataSize(pDma, u8Index, DMA_TRANSFER_SIZE_1B);
        DMA_HWA_SetDestModulo(pDma, u8Index, 0U);
        DMA_HWA_SetInnerLoopSize(pDma, u8Index, 0U);
        DMA_HWA_SetChannelControlStatus(pDma, u8Index, 0U);
        DMA_HWA_SetChannelToChannelTrig(pDma, u8Index, false, 0U);
        DMA_HWA_SetLoopCount(pDma, u8Index, 0U);
    }
    Dmamux_Reset(pDmamux);

}

DMA_StatusType DMA_InitChannel(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel, const DMA_ChannelCfgType *const pChnCfg)
{
    DEV_ASSERT(eDma_Instance < DMA_INSTANCE_MAX);
    DEV_ASSERT(eChannel < DMA_CHANNEL_MAX);
    DEV_ASSERT(pChnCfg != NULL);
    DEV_ASSERT(pChnCfg->u16BlockCount > 0U);
    DEV_ASSERT(pChnCfg->u32BlockSize > 0U);
    DEV_ASSERT(((pChnCfg->u32BlockSize >> pChnCfg->eSrcDataSize) << pChnCfg->eSrcDataSize == pChnCfg->u32BlockSize) &&
               ((pChnCfg->u32BlockSize >> pChnCfg->eDestDataSize) << pChnCfg->eDestDataSize == pChnCfg->u32BlockSize));

    DMA_Type * aDma[] = DMA_BASE_PTRS;
    DMA_Type *const pDma = aDma[eDma_Instance];
    DMAMUX_Type * aDmamux[] = DMAMUX_BASE_PTRS;
    DMAMUX_Type *const pDmamux = aDmamux[eDma_Instance];

    DMA_StatusType ret;

    uint16_t u16SrcDataOffset = DMA_GetDataOffset(pChnCfg->eSrcIncMode, pChnCfg->eSrcDataSize);
    uint16_t u16DestDataOffset = DMA_GetDataOffset(pChnCfg->eDestIncMode, pChnCfg->eDestDataSize);

    int32_t s32SrcLastOffset;
    int32_t s32DestLastOffset;

    uint8_t u8SrcMod = 0U;
    uint8_t u8DestMod = 0U;

    bool bUseSrcDumo = (bool)false;
    bool bUseDestDumo = (bool)false;
    uint8_t u8DumoIndex = 0U;
    uint16_t u16Sumo = 0U;
    uint16_t u16Dumo = 0U;

    if ((pChnCfg->bSrcCircularBufferEn == true) || (pChnCfg->bDestCircularBufferEn == true))
    {
        /* If the circular buffer size is not power of 2 aligned, need to use the DUMO */
        if (pChnCfg->bSrcCircularBufferEn == true)
        {
            DEV_ASSERT(pChnCfg->u32SrcCircBufferSize != 0U);
            bUseSrcDumo = (bool)(DMA_IsPowerOf2(pChnCfg->u32SrcCircBufferSize, &u8SrcMod) ? false : true);
        }
        if (pChnCfg->bDestCircularBufferEn == true)
        {
            DEV_ASSERT(pChnCfg->u32DestCircBufferSize != 0U);
            bUseDestDumo = (bool)(DMA_IsPowerOf2(pChnCfg->u32DestCircBufferSize, &u8DestMod) ? false : true);
        }

        /* If circular buffer is enabled, the buffer address must be power of 2 aligned */
        if (((pChnCfg->bSrcCircularBufferEn == true) &&
                (((uint32_t)pChnCfg->pSrcBuffer & ((1UL << u8SrcMod) - 1U)) != 0U)) ||
                ((pChnCfg->bDestCircularBufferEn == true) &&
                 (((uint32_t)pChnCfg->pDestBuffer & ((1UL << u8DestMod) - 1U)) != 0U)))
        {
            ret = DMA_STATUS_INVALID_ADDRESS;
        }
        /* If circular buffer is enabled, the buffer size must not less than the data offset */
        else if (((pChnCfg->bSrcCircularBufferEn == true) &&
                  (pChnCfg->u32SrcCircBufferSize < u16SrcDataOffset)) ||
                 ((pChnCfg->bDestCircularBufferEn == true) &&
                  (pChnCfg->u32DestCircBufferSize < u16SrcDataOffset)))
        {
            ret = DMA_STATUS_UNSUPPORTED;
        }
        /* If source or destination unalign modulo is used, check whether all DUMO registers are occupied */
        else if ((bUseSrcDumo == true) || (bUseDestDumo == true))
        {
            ret = DMA_GetDumoIndex(&u8DumoIndex);
            if (ret == DMA_STATUS_SUCCESS)
            {
                s_aDmaDumoUsedStatus[u8DumoIndex] = (uint8_t)eChannel;
            }
        }
        else
        {
            ret = DMA_STATUS_SUCCESS;
        }
    }
    else
    {
        ret = DMA_STATUS_SUCCESS;
    }

    if (ret == DMA_STATUS_SUCCESS)
    {
        if (pChnCfg->bSrcAddrLoopbackEn == true)
        {
            if (pChnCfg->bSrcBlockOffsetEn == false)
            {
                s32SrcLastOffset = -((int32_t)((pChnCfg->u32BlockSize >> pChnCfg->eSrcDataSize) * u16SrcDataOffset) *
                                     (int32_t)(pChnCfg->u16BlockCount));
            }
            else
            {
                s32SrcLastOffset = -(((int32_t)((pChnCfg->u32BlockSize >> pChnCfg->eSrcDataSize) * u16SrcDataOffset)) *
                		            (int32_t)(pChnCfg->u16BlockCount)) - ((pChnCfg->s32BlockOffset) * (int32_t)(pChnCfg->u16BlockCount - 1U));
            }
        }
        else
        {
            s32SrcLastOffset = 0;
        }
        if (pChnCfg->bDestAddrLoopbackEn == true)
        {
            if (pChnCfg->bDestBlockOffsetEn == false)
            {
                s32DestLastOffset = -(((pChnCfg->u32BlockSize >> pChnCfg->eDestDataSize) * u16DestDataOffset) *
                                      (pChnCfg->u16BlockCount));
            }
            else
            {
                s32DestLastOffset = -(((int32_t)((pChnCfg->u32BlockSize >> pChnCfg->eDestDataSize) * u16DestDataOffset)) *
                		             (int32_t)(pChnCfg->u16BlockCount)) - ((pChnCfg->s32BlockOffset) * (int32_t)(pChnCfg->u16BlockCount - 1U));
            }
        }
        else
        {
            s32DestLastOffset = 0;
        }

        DMA_HWA_SetSrcAddr(pDma, (uint8_t)eChannel, (uint32_t)pChnCfg->pSrcBuffer);
        DMA_HWA_SetDestAddr(pDma, (uint8_t)eChannel, (uint32_t)pChnCfg->pDestBuffer);
        DMA_HWA_SetPriority(pDma, (uint8_t)eChannel, pChnCfg->u8ChannelPriority);

        if ((pChnCfg->bSrcCircularBufferEn == true) && (pChnCfg->bDestCircularBufferEn == true))
        {
            DMA_HWA_SetSrcDataSize(pDma, (uint8_t)eChannel, pChnCfg->eSrcDataSize);
            DMA_HWA_SetSrcModulo(pDma, (uint8_t)eChannel, u8SrcMod);
            DMA_HWA_SetDestDataSize(pDma, (uint8_t)eChannel, pChnCfg->eDestDataSize);
            DMA_HWA_SetDestModulo(pDma, (uint8_t)eChannel, u8DestMod);
        }
        else if (pChnCfg->bSrcCircularBufferEn == true)
        {
            DMA_HWA_SetSrcDataSize(pDma, (uint8_t)eChannel, pChnCfg->eSrcDataSize);
            DMA_HWA_SetSrcModulo(pDma, (uint8_t)eChannel, u8SrcMod);
            DMA_HWA_SetDestDataSize(pDma, (uint8_t)eChannel, pChnCfg->eDestDataSize);
            DMA_HWA_SetDestModulo(pDma, (uint8_t)eChannel, 0U);
        }
        else if (pChnCfg->bDestCircularBufferEn == true)
        {
            DMA_HWA_SetSrcDataSize(pDma, (uint8_t)eChannel, pChnCfg->eSrcDataSize);
            DMA_HWA_SetSrcModulo(pDma, (uint8_t)eChannel, 0U);
            DMA_HWA_SetDestDataSize(pDma, (uint8_t)eChannel, pChnCfg->eDestDataSize);
            DMA_HWA_SetDestModulo(pDma, (uint8_t)eChannel, u8DestMod);
        }
        else
        {
            DMA_HWA_SetSrcDataSize(pDma, (uint8_t)eChannel, pChnCfg->eSrcDataSize);
            DMA_HWA_SetSrcModulo(pDma, (uint8_t)eChannel, 0U);
            DMA_HWA_SetDestDataSize(pDma, (uint8_t)eChannel, pChnCfg->eDestDataSize);
            DMA_HWA_SetDestModulo(pDma, (uint8_t)eChannel, 0U);
        }

        if (bUseSrcDumo == true)
        {
            u16Sumo = (uint16_t)((pChnCfg->u32SrcCircBufferSize / u16SrcDataOffset - 1U) * u16SrcDataOffset);
        }
        if (bUseDestDumo == true)
        {
            u16Dumo = (uint16_t)((pChnCfg->u32DestCircBufferSize / u16DestDataOffset - 1U) * u16DestDataOffset);
        }
        if ((bUseSrcDumo == true) || (bUseDestDumo == true))
        {
            DMA_HWA_SetUnalignModulo(pDma, u8DumoIndex, u16Sumo, u16Dumo);
            DMA_HWA_SetUnalignModuloEnableFlag(pDma, (uint8_t)eChannel, bUseSrcDumo, bUseDestDumo);
            DMA_HWA_SetUnalignModuloSel(pDma, (uint8_t)eChannel, u8DumoIndex);
        }
        DMA_HWA_SetAutoDisableReuqestEnableFlag(pDma, (uint8_t)eChannel, pChnCfg->bAutoStop);

        DMA_HWA_SetSrcOffset(pDma, (uint8_t)eChannel, (int16_t)u16SrcDataOffset);
        DMA_HWA_SetDestOffset(pDma, (uint8_t)eChannel, (int16_t)u16DestDataOffset);

        DMA_HWA_SetInnerLoopOffset(pDma, (uint8_t)eChannel, pChnCfg->bSrcBlockOffsetEn, pChnCfg->bDestBlockOffsetEn,
                                   pChnCfg->s32BlockOffset);
        DMA_HWA_SetInnerLoopSize(pDma, (uint8_t)eChannel, pChnCfg->u32BlockSize);

        if ((pChnCfg->u16BlockCount > 1U) && (true == pChnCfg->bInnerChannelChain))
        {
            DMA_HWA_SetChannelToChannelTrig(pDma, (uint8_t)eChannel, true, (uint8_t)eChannel);
            DMA_HWA_SetLoopCount(pDma, (uint8_t)eChannel, pChnCfg->u16BlockCount);
        }
        else
        {
            DMA_HWA_SetChannelToChannelTrig(pDma, (uint8_t)eChannel, false, 0U);
            DMA_HWA_SetLoopCount(pDma, (uint8_t)eChannel, pChnCfg->u16BlockCount);
        }

        DMA_HWA_SetSrcLastAddrAdjustment(pDma, (uint8_t)eChannel, s32SrcLastOffset);
        DMA_HWA_SetDestLastAddrAdjustment(pDma, (uint8_t)eChannel, s32DestLastOffset);

        if (pChnCfg->eTriggerSrc == DMA_REQ_DISABLED)
        {
            DMAMUX_HWA_SetRequestSource(pDmamux, (uint8_t)eChannel, false, DMA_REQ_DISABLED);
        }
        else
        {
            DMAMUX_HWA_SetRequestSource(pDmamux, (uint8_t)eChannel, true, pChnCfg->eTriggerSrc);
        }
    }
    return ret;
}

void DMA_DeinitChannel(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel)
{
    DEV_ASSERT(eDma_Instance < DMA_INSTANCE_MAX);
    DEV_ASSERT(eChannel < DMA_CHANNEL_MAX);

    DMA_Type * aDma[] = DMA_BASE_PTRS;
    DMA_Type *const pDma = aDma[eDma_Instance];
    uint8_t u8DumoIndex;

    for (u8DumoIndex = 0U; u8DumoIndex < DMA_DUMO_COUNT; u8DumoIndex++)
    {
        if (s_aDmaDumoUsedStatus[u8DumoIndex] == (uint8_t)eChannel)
        {
            s_aDmaDumoUsedStatus[u8DumoIndex] = DMA_CHANNEL_INVALID;
            DMA_HWA_SetUnalignModulo(pDma, u8DumoIndex, 0U, 0U);
        }
    }
    DMA_HWA_SetUnalignModuloEnableFlag(pDma, (uint8_t)eChannel, false, false);
    DMA_HWA_DisableChannelErrorInterrupt(pDma, (uint8_t)eChannel);
    DMA_HWA_DisableChannelRequest(pDma, (uint8_t)eChannel);
    DMA_HWA_ClearChannelDoneStatus(pDma, (uint8_t)eChannel);
    DMA_HWA_ClearChannelErrorFlag(pDma, (uint8_t)eChannel);
    DMA_HWA_ClearChannelInterruptFlag(pDma, (uint8_t)eChannel);

    DMA_HWA_SetSrcAddr(pDma, (uint8_t)eChannel, 0U);
    DMA_HWA_SetSrcOffset(pDma, (uint8_t)eChannel, 0);
    DMA_HWA_SetSrcLastAddrAdjustment(pDma, (uint8_t)eChannel, 0);
    DMA_HWA_SetDestAddr(pDma, (uint8_t)eChannel, 0U);
    DMA_HWA_SetDestOffset(pDma, (uint8_t)eChannel, 0);
    DMA_HWA_SetDestLastAddrAdjustment(pDma, (uint8_t)eChannel, 0);
    DMA_HWA_SetSrcDataSize(pDma, (uint8_t)eChannel, DMA_TRANSFER_SIZE_1B);
    DMA_HWA_SetSrcModulo(pDma, (uint8_t)eChannel, 0U);
    DMA_HWA_SetDestDataSize(pDma, (uint8_t)eChannel, DMA_TRANSFER_SIZE_1B);
    DMA_HWA_SetDestModulo(pDma, (uint8_t)eChannel, 0U);
    DMA_HWA_SetInnerLoopOffset(pDma, (uint8_t)eChannel, false, false, 0);
    DMA_HWA_SetInnerLoopSize(pDma, (uint8_t)eChannel, 0U);
    DMA_HWA_SetChannelControlStatus(pDma, (uint8_t)eChannel, 0U);
    DMA_HWA_SetChannelToChannelTrig(pDma, (uint8_t)eChannel, false, 0U);
    DMA_HWA_SetLoopCount(pDma, (uint8_t)eChannel, 0U);
}

void DMA_InitChannelInterrupt(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel, const DMA_InterruptCfgType *const pInterruptCfg)
{
    DEV_ASSERT(eDma_Instance < DMA_INSTANCE_MAX);
    DEV_ASSERT(eChannel < DMA_CHANNEL_MAX);
    DEV_ASSERT(pInterruptCfg != NULL);

    DMA_Type * aDma[] = DMA_BASE_PTRS;
    DMA_Type *const pDma = aDma[eDma_Instance];

    if (pInterruptCfg->bTransferCompleteIntEn)
    {
        s_dmaTransferCompleteNotify[eDma_Instance][eChannel] = pInterruptCfg->pTransferCompleteNotify;
        DMA_HWA_EnableTransferCompleteInterrupt(pDma, (uint8_t)eChannel);
        //IntMgr_EnableInterrupt(DMA_GetChannelIRQn(eChannel));
    }
    else
    {
        DMA_HWA_DisableTransferCompleteInterrupt(pDma, (uint8_t)eChannel);
        s_dmaTransferCompleteNotify[eDma_Instance][eChannel] = NULL;
        //IntMgr_DisableInterrupt(DMA_GetChannelIRQn(eChannel));
    }

    if (pInterruptCfg->bTransferErrorIntEn)
    {
        s_dmaTransferErrorNotify[eDma_Instance][eChannel] = pInterruptCfg->pTransferErrorNotify;
        DMA_HWA_EnableChannelErrorInterrupt(pDma, (uint8_t)eChannel);
        //IntMgr_EnableInterrupt(DMA_error_IRQn);
    }
    else
    {
        DMA_HWA_DisableChannelErrorInterrupt(pDma, (uint8_t)eChannel);
        s_dmaTransferErrorNotify[eDma_Instance][eChannel] = NULL;
        //if (DMA_HWA_GetAllChannelErrorInterruptEnableFlag(pDma) == 0U)
        //{
        //IntMgr_DisableInterrupt(DMA_error_IRQn);
        //}
    }
}

void DMA_ConfigChainedTransfer(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel,
                               const DMA_ChainTransferType *const pChainTransferCfg)
{
    DEV_ASSERT(eDma_Instance < DMA_INSTANCE_MAX);
    DEV_ASSERT(eChannel < DMA_CHANNEL_MAX);
    DEV_ASSERT(pChainTransferCfg != NULL);

    DMA_Type * aDma[] = DMA_BASE_PTRS;
    DMA_Type *const pDma = aDma[eDma_Instance];

    DMA_HWA_SetOuterLoopTrigEnableFlag(pDma, (uint8_t)eChannel, pChainTransferCfg->bChanelChainEn);
    DMA_HWA_SetOuterLoopTrigChannel(pDma, (uint8_t)eChannel, pChainTransferCfg->u8ChainedChannel);
}

DMA_StatusType DMA_ModifyAddress(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel,
                                 const volatile void *pSrcBuffer, const volatile void *pDestBuffer)
{
    DEV_ASSERT(eDma_Instance < DMA_INSTANCE_MAX);
    DEV_ASSERT(eChannel < DMA_CHANNEL_MAX);

    DMA_Type * aDma[] = DMA_BASE_PTRS;
    DMA_Type *const pDma = aDma[eDma_Instance];
    DMA_StatusType ret;

    if (DMA_GetChannelStatus(eDma_Instance, eChannel) == DMA_RUNNING_STATUS_IDLE)
    {
        if (pSrcBuffer != NULL)
        {
            DMA_HWA_SetSrcAddr(pDma, (uint8_t)eChannel, (uint32_t)pSrcBuffer);
        }
        if (pDestBuffer != NULL)
        {
            DMA_HWA_SetDestAddr(pDma, (uint8_t)eChannel, (uint32_t)pDestBuffer);
        }
        ret = DMA_STATUS_SUCCESS;
    }
    else
    {
        ret = DMA_STATUS_BUSY;
    }
    return ret;
}

void DMA_StartChannel(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel)
{
    DEV_ASSERT(eDma_Instance < DMA_INSTANCE_MAX);
    DEV_ASSERT(eChannel < DMA_CHANNEL_MAX);

    DMA_Type * aDma[] = DMA_BASE_PTRS;
    DMA_Type *const pDma = aDma[eDma_Instance];

    if (DMA_GetChannelRequestSrc(eDma_Instance, eChannel) == DMA_REQ_DISABLED)
    {
        DMA_HWA_SetChannelStart(pDma, (uint8_t)eChannel);
    }
    else
    {
        DMA_HWA_EnableChannelRequest(pDma, (uint8_t)eChannel);
    }
}

void DMA_StopChannel(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel)
{
    DEV_ASSERT(eDma_Instance < DMA_INSTANCE_MAX);
    DEV_ASSERT(eChannel < DMA_CHANNEL_MAX);

    DMA_Type * aDma[] = DMA_BASE_PTRS;
    DMA_Type *const pDma = aDma[eDma_Instance];

    DMA_HWA_DisableChannelRequest(pDma, (uint8_t)eChannel);
}

DMA_StatusType DMA_CancelTransfer(const DMA_InstanceType eDma_Instance, bool bGenerateErr)
{
    DEV_ASSERT(eDma_Instance < DMA_INSTANCE_MAX);

    DMA_Type * aDma[] = DMA_BASE_PTRS;
    DMA_Type *const pDma = aDma[eDma_Instance];
    DMA_StatusType eRet;
    uint32_t u32TimeOut = 15000000U;

    if (bGenerateErr)
    {
        DMA_HWA_ErrorCancelTransfer(pDma);
        while ((DMA_HWA_GetErrorCancelTransferStatus(pDma) == true) && (u32TimeOut != 0U))
        {
            u32TimeOut--;
        }
    }
    else
    {
        DMA_HWA_CancelTransfer(pDma);
        while ((DMA_HWA_GetCancelTransferStatus(pDma) == true) && (u32TimeOut != 0U))
        {
            u32TimeOut--;
        }
    }
    if (u32TimeOut != 0U)
    {
        eRet = DMA_STATUS_SUCCESS;
    }
    else
    {
        eRet = DMA_STATUS_TIMEOUT;
    }
    return eRet;
}

DMA_RequestSourceType DMA_GetChannelRequestSrc(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel)
{
    DEV_ASSERT(eDma_Instance < DMA_INSTANCE_MAX);
    DEV_ASSERT(eChannel < DMA_CHANNEL_MAX);

    DMAMUX_Type * aDmamux[] = DMAMUX_BASE_PTRS;
    DMAMUX_Type *const pDmamux = aDmamux[eDma_Instance];

    DMA_RequestSourceType eReqSrc = DMAMUX_HWA_GetRequestSource(pDmamux, (uint8_t)eChannel);

    return eReqSrc;
}

DMA_RunningStatusType DMA_GetStatus(const DMA_InstanceType eDma_Instance)
{
    DEV_ASSERT(eDma_Instance < DMA_INSTANCE_MAX);

    DMA_Type * aDma[] = DMA_BASE_PTRS;
    DMA_Type *const pDma = aDma[eDma_Instance];
    DMA_RunningStatusType eDMAStatus = DMA_HWA_GetStatus(pDma);
    return eDMAStatus;
}

DMA_RunningStatusType DMA_GetChannelStatus(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel)
{
    DEV_ASSERT(eDma_Instance < DMA_INSTANCE_MAX);
    DEV_ASSERT(eChannel < DMA_CHANNEL_MAX);

    DMA_Type * aDma[] = DMA_BASE_PTRS;
    DMA_Type *const pDma = aDma[eDma_Instance];
    DMA_RunningStatusType eChannelStatus = DMA_HWA_GetChannelActiveStatus(pDma, (uint8_t)eChannel);
    return eChannelStatus;
}
