/**
 * @file fc7xxx_driver_dma.h
 * @author Flagchip0126
 * @brief FC7xxx DMA driver type definition and API
 * @version 0.1.0
 * @date 2024-01-15
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-15    Flagchip0126  N/A          First version for FC240
   ******************************************************************************** */

#ifndef _DRIVER_FC4XXX_DRIVER_DMA_H_
#define _DRIVER_FC4XXX_DRIVER_DMA_H_
#include "device_header.h"
#include "HwA_dma.h"
#include "HwA_dmamux.h"

#if defined(__cplusplus)
extern "C" {
#endif
    /**
     * @addtogroup fc7xxx_driver_dma
     * @{
     */

    /**
     * @brief DMA transfer complete callback function prototype
     *
     */
    typedef void (*DMA_TransferCompleteCallbackType)(void);

    /**
     * @brief DMA transfer error callback function prototype
     *
     */
    typedef void (*DMA_TransferErrorCallbackType)(void);

    /**
     * @brief Available DMA Instances
     *
     */
    typedef enum
    {
        DMA_INSTANCE_0  = 0U,
        DMA_INSTANCE_MAX = DMA_INSTANCE_COUNT
    } DMA_InstanceType;

    /**
     * @brief Available DMA channels
     *
     */
    typedef enum
    {
        DMA_CHANNEL_0  = 0U,
        DMA_CHANNEL_1  = 1U,
        DMA_CHANNEL_2  = 2U,
        DMA_CHANNEL_3  = 3U,
        DMA_CHANNEL_4  = 4U,
        DMA_CHANNEL_5  = 5U,
        DMA_CHANNEL_6  = 6U,
        DMA_CHANNEL_7  = 7U,
        DMA_CHANNEL_8  = 8U,
        DMA_CHANNEL_9  = 9U,
        DMA_CHANNEL_10 = 10U,
        DMA_CHANNEL_11 = 11U,
        DMA_CHANNEL_12 = 12U,
        DMA_CHANNEL_13 = 13U,
        DMA_CHANNEL_14 = 14U,
        DMA_CHANNEL_15 = 15U,
        DMA_CHANNEL_MAX = DMA_CFG_COUNT
    } DMA_ChannelType;

    /**
     * @brief DMA operation return values
     *
     */
    typedef enum
    {
        DMA_STATUS_SUCCESS         = 0x00U,   /*!< The DMA operation is succeeded */
        DMA_STATUS_ERROR           = 0x01U,   /*!< The DMA operation is failed */
        DMA_STATUS_BUSY            = 0x02U,   /*!< The DMA operation is failed because DMA engine is busy */
        DMA_STATUS_TIMEOUT         = 0x03U,   /*!< The DMA operation is failed because operation time out */
        DMA_STATUS_UNSUPPORTED     = 0x04U,   /*!< The DMA configuration parameter is unsupported */
        DMA_STATUS_INVALID_ADDRESS = 0x05U,   /*!< The DMA source/destination address is invalid */
        DMA_STATUS_NO_RESOURCE     = 0x06U    /*!< The DMA operation is failed because there is no resource */
    } DMA_StatusType;

    /**
     * @brief DMA data increment size
     *
     * Specify the data increment size after DMA engine transferred a datum
     *
     */
    typedef enum
    {
        DMA_INCREMENT_DISABLE                 = 0x0U, /*!< The data address not increase */
        DMA_INCREMENT_DATA_SIZE               = 0x1U, /*!< The data address increase by the data size */
        DMA_INCREMENT_DATA_SIZE_4BYTE_ALIGNED = 0x2U  /*!< The data address increase by the data size,
                                                       and is 4 byte aligned */
    } DMA_IncrementModeType;

    /**
     * @brief The size of the circular buffer
     *
     * @note The start address of the circular buffer should be aligned by the circular
     * buffer size
     *
     */
    typedef enum
    {
        DMA_CIRCULAR_BUFFER_SIZE_1B    = (int32)0x1U,
        DMA_CIRCULAR_BUFFER_SIZE_2B    = (int32)0x2U,
        DMA_CIRCULAR_BUFFER_SIZE_4B    = (int32)0x4U,
        DMA_CIRCULAR_BUFFER_SIZE_8B    = (int32)0x8U,
        DMA_CIRCULAR_BUFFER_SIZE_16B   = (int32)0x10U,
        DMA_CIRCULAR_BUFFER_SIZE_32B   = (int32)0x20U,
        DMA_CIRCULAR_BUFFER_SIZE_64B   = (int32)0x40U,
        DMA_CIRCULAR_BUFFER_SIZE_128B  = (int32)0x80U,
        DMA_CIRCULAR_BUFFER_SIZE_256B  = (int32)0x100U,
        DMA_CIRCULAR_BUFFER_SIZE_512B  = (int32)0x200U,
        DMA_CIRCULAR_BUFFER_SIZE_1KB   = (int32)0x400U,
        DMA_CIRCULAR_BUFFER_SIZE_2KB   = (int32)0x800U,
        DMA_CIRCULAR_BUFFER_SIZE_4KB   = (int32)0x1000U,
        DMA_CIRCULAR_BUFFER_SIZE_8KB   = (int32)0x2000U,
        DMA_CIRCULAR_BUFFER_SIZE_16KB  = (int32)0x4000U,
        DMA_CIRCULAR_BUFFER_SIZE_32KB  = (int32)0x8000U,
        DMA_CIRCULAR_BUFFER_SIZE_64KB  = (int32)0x10000U,
        DMA_CIRCULAR_BUFFER_SIZE_128KB = (int32)0x20000U,
        DMA_CIRCULAR_BUFFER_SIZE_256KB = (int32)0x40000U,
        DMA_CIRCULAR_BUFFER_SIZE_512KB = (int32)0x80000U,
        DMA_CIRCULAR_BUFFER_SIZE_1MB   = (int32)0x100000U,
        DMA_CIRCULAR_BUFFER_SIZE_2MB   = (int32)0x200000U,
        DMA_CIRCULAR_BUFFER_SIZE_4MB   = (int32)0x400000U,
        DMA_CIRCULAR_BUFFER_SIZE_8MB   = (int32)0x800000U,
        DMA_CIRCULAR_BUFFER_SIZE_16MB  = (int32)0x1000000U,
        DMA_CIRCULAR_BUFFER_SIZE_32MB  = (int32)0x2000000U,
        DMA_CIRCULAR_BUFFER_SIZE_64MB  = (int32)0x4000000U,
        DMA_CIRCULAR_BUFFER_SIZE_128MB = (int32)0x8000000U,
        DMA_CIRCULAR_BUFFER_SIZE_256MB = (int32)0x10000000U,
        DMA_CIRCULAR_BUFFER_SIZE_512MB = (int32)0x20000000U,
        DMA_CIRCULAR_BUFFER_SIZE_1GB   = (int32)0x40000000U,
        DMA_CIRCULAR_BUFFER_SIZE_2GB   = (int32)0x80000000U,
    } DMA_CircularBufferSizeType;

    /**
     * @brief The eBufferRole of the circular buffer
     *
     */
    typedef enum
    {
        DMA_CIRCULAR_BUFFEER_ROLE_SOURCE      = 0x0U, /*!< The circular buffer is used as the data source */
        DMA_CIRCULAR_BUFFEER_ROLE_DESTINATION = 0x1U  /*!< The circular buffer is used as the data destination */
    } DMA_CircularBufferRoleType;

    /**
     * @brief The configuration parameters of the DMA engine
     *
     */
    typedef struct
    {
        DMA_ArbitrationAlgorithmType eArbitrationAlgorithm; /*!< Channel Arbitration Algorithm */
        bool bHaltOnError;                                  /*!< Whether DMA halts when error occured */
    } DMA_InitType;

    /**
     * @brief The interrupt configurations of the DMA channel
     *
     */
    typedef struct
    {
        bool bTransferCompleteIntEn; /*!< Enable interrupt after transfer complete */
        DMA_TransferCompleteCallbackType pTransferCompleteNotify; /*!< transfer complete notification */
        bool bTransferErrorIntEn;    /*!< Enable interrupt when transfer error occured */
        DMA_TransferErrorCallbackType pTransferErrorNotify;       /*!< transfer error notification */
    } DMA_InterruptCfgType;

    /**
     * @brief The configutation parameters of the DMA channel
     *
     * @note The u8ChannelPriority must be unique for different channels, the default is the channel number.
     * The u16BlockCount must be greater than 0.
     * @note When Circular buffer is enabled, the data address should be power of 2 aligned to the buffer size.
     * For example, if the circular buffer size is 32 byte, the data address should be 32 byte aligned. If the
     * circular buffer size is 40 byte, then the data address should be 64 byte aligned.
     *
     */
    typedef struct
    {
        const volatile void *pSrcBuffer;       /*!< the source address of the data */
        volatile void *pDestBuffer;            /*!< the destination address of the data */
        uint32_t u32BlockSize;                 /*!< the data size of one block in byte */
        uint16_t u16BlockCount;                /*!< the number of data blocks in one transfer */
        uint8_t u8ChannelPriority;             /*!< channel priority, greater number means higher priority */
        DMA_TransferSizeType eSrcDataSize;     /*!< source data size */
        DMA_TransferSizeType eDestDataSize;    /*!< destination data size */
        DMA_IncrementModeType eSrcIncMode;     /*!< source data address increment mode */
        DMA_IncrementModeType eDestIncMode;    /*!< destination data address increment mode */
        bool bSrcBlockOffsetEn;                /*!< whether to add a block offset to the source address after
                                                a block transfer */
        bool bDestBlockOffsetEn;               /*!< whether to add a block offset to the destination address after
                                                a block transfer */
        int32_t s32BlockOffset;                /*!< the signed address offset applied to the src/dest address
                                                after a block transfer */
        bool bSrcAddrLoopbackEn;               /*!< whether the source address return to the set value after transfer */
        bool bDestAddrLoopbackEn;              /*!< whether the destination address return to the set value after transfer */
        bool bAutoStop;                        /*!< whether the DMA channel transfer automatically stops after one
                                                transfer finishes when the channel is triggered by hardware */
        bool bSrcCircularBufferEn;             /*!< the source buffer of the DMA channel is a circular buffer */
        uint32_t u32SrcCircBufferSize;         /*!< the source circular buffer size in byte, the buffer size is suggested
                                                to be power of 2 aligned */
        bool bDestCircularBufferEn;            /*!< the destination buffer of the DMA channel is a circular buffer */
        uint32_t u32DestCircBufferSize;        /*!< the destination circular buffer size in byte, the buffer size is suggested
                                                to be power of 2 aligned */
    bool bInnerChannelChain;
    DMA_RequestSourceType eTriggerSrc;     /*!< Select the DMA channel trigger source, if the trigger source is
                                                DMA_REQ_DISABLED, the channel is triggered by software */
    } DMA_ChannelCfgType;

    /**
     * @brief The parameters to configure the DMA channel as a circular buffer engine
     *
     */
    typedef struct
    {
        bool bCircularBufferEn;                 /*!< enable the DMA channel as a circular buffer engine */
        DMA_CircularBufferRoleType eBufferRole; /*!< the source or the destination address is a circular buffer */
        DMA_CircularBufferSizeType eBufferSize; /*!< the circular buffer size */
    } DMA_CircularBufferType;

    /**
     * @brief The paarameters to configure the DMA chainned transfer
     *
     */
    typedef struct
    {
        bool bChanelChainEn;      /*!< Whether to start the chained channel when the current completed */
        uint8_t u8ChainedChannel; /*!< The chained channel */
    } DMA_ChainTransferType;

    /**
     * @brief Initialize the DMA instance
     *
     * @param pInitCfg the configuration of the DMA instance
     */
    void DMA_Init(const DMA_InstanceType eDma_Instance, const DMA_InitType *const pInitCfg);

    /**
     * @brief De-initialize the DMA instance
     *
     * Disable the DMA and restore its configure values to default
     *
     */
    void DMA_DeInit(const DMA_InstanceType eDma_Instance);

    /**
     * @brief Initialize the DMA channel
     *
     * @param u8Channel the DMA channel to initialize
     * @param pChnCfg the configuration of the channel
     * @return DMA_StatusType whether the channel is initiallized successfully
     */
    DMA_StatusType DMA_InitChannel(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel, const DMA_ChannelCfgType *const pChnCfg);

    /**
     * @brief De-initialize the DMA channel
     *
     * @param u8Channel the DMA channel to de-initialize
     */
    void DMA_DeinitChannel(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel);

    /**
     * @brief Initialize the DMA channel interrupt
     *
     * @param u8Channel the DMA channel to use
     * @param pInterruptCfg the interrupt configuration of the DMA channel
     */
    void DMA_InitChannelInterrupt(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel, const DMA_InterruptCfgType *const pInterruptCfg);

    /**
     * @brief Config the DMA channel chained transfer
     *
     * @param u8Channel the DMA channel to use
     * @param pChainTransferCfg the parameters of the chained channel
     */
    void DMA_ConfigChainedTransfer(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel,
                                   const DMA_ChainTransferType *const pChainTransferCfg);

    /**
     * @brief Modify the source and destination address of the DMA channel
     *
     * @note This function should be called when the DMA channel is not actively transferring
     *
     * @param u8Channel the channel to modify
     * @param pSrcBuffer the new source address of data, set NULL to remain unmodified
     * @param pDestBuffer the new destination address of data, set NULL to remain unmodified
     * @return DMA_StatusType whether the address is successfully modified
     */
    DMA_StatusType DMA_ModifyAddress(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel,
                                     const volatile void *pSrcBuffer, const volatile void *pDestBuffer);

    /**
     * @brief Start the DMA channel transfer
     *
     * If the trigger source for the DMA channel is DMA_REQ_DISABLED, the channel will start
     * immediately after called this function. Otherwise, the channel will start when the
     * trigger source is generated on the channel.
     *
     * @param u8Channel the DMA channel to start
     */
    void DMA_StartChannel(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel);

    /**
     * @brief Stop the DMA channel transfer
     *
     * If the trigger source for the DMA channel is DMA_REQ_DISABLED, the channel will stop
     * automatically after the transfer completed. Otherwise, you should call this function
     * manually if you do not want the DMA to be triggered when hardware request is generated.
     *
     * @note If there is ongoing transfer on the channel, the channel will be stopped after the
     * transfer completed.
     *
     * @param u8Channel the DMA channel to stop
     */
    void DMA_StopChannel(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel);

    /**
     * @brief Cancel the ongoing DMA transfer
     *
     * @param bGenerateErr whether an error will be generated on the transferring channel
     * @return DMA_StatusType whether the transfer is stopped successfully
     */
    DMA_StatusType DMA_CancelTransfer(const DMA_InstanceType eDma_Instance, bool bGenerateErr);

    /**
     * @brief Get the request source of the selected channel
     *
     * @param u8Channel the DMA channel to get the request source
     * @return DMA_RequestSourceType the request source of the selected channel
     */
    DMA_RequestSourceType DMA_GetChannelRequestSrc(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel);

    /**
     * @brief Get the status of the DMA engine
     *
     * @return DMA_RunningStatusType the status of the DMA engine
     */
    DMA_RunningStatusType DMA_GetStatus(const DMA_InstanceType eDma_Instance);

    /**
     * @brief Get the status of the DMA channel
     *
     * @param u8Channel the DMA channel to get the status
     * @return DMA_RunningStatusType the status of the DMA channel
     */
    DMA_RunningStatusType DMA_GetChannelStatus(const DMA_InstanceType eDma_Instance, const DMA_ChannelType eChannel);

    /** @}*/ /* fc7xxx_driver_dma */
#if defined(__cplusplus)
}
#endif
#endif
