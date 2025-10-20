/**
 * @file fc7xxx_driver_adc.h
 * @author Flagchip0126
 * @brief FC7xxx ADC driver type definition and API
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
   *   0.1.0       2024-01-15    Flagchip0126  N/A          First version for FC7240
   ******************************************************************************** */

#ifndef _DRIVER_FC7XXX_DRIVER_ADC_H_
#define _DRIVER_FC7XXX_DRIVER_ADC_H_
#include "device_header.h"
#include "HwA_adc.h"
#include "fc7xxx_driver_dma.h"

#if defined(__cplusplus)
extern "C" {
#endif
/**
 * @addtogroup fc7xxx_driver_adc
 * @{
 */

/**
 * @name  ADC0 Internal Channels
 * @brief Available internal ADC channels for ADC Instance 0
 *
 * @{
 */
#define ADC0_CHANNEL_VBG_BUFFER                ADC_CHANNEL_INTERNAL_0
#define ADC0_CHANNEL_V25                       ADC_CHANNEL_INTERNAL_1
#define ADC0_CHANNEL_V11                       ADC_CHANNEL_INTERNAL_2
#define ADC0_CHANNEL_CMP0_DAC                  ADC_CHANNEL_INTERNAL_4
#define ADC0_CHANNEL_TEMPSENSOR_OUT            ADC_CHANNEL_INTERNAL_5   /* Must be in differential mode */
/** @}*/

/**
 * @name  ADC1 Internal channels
 * @brief Available internal ADC channels for ADC Instance 1
 *
 * @{
 */
#define ADC1_CHANNEL_V11_PD0                   ADC_CHANNEL_INTERNAL_0
#define ADC1_CHANNEL_VREFH                     ADC_CHANNEL_INTERNAL_1
#define ADC1_CHANNEL_VDDA                      ADC_CHANNEL_INTERNAL_2
#define ADC1_CHANNEL_V15                       ADC_CHANNEL_INTERNAL_3
#define ADC1_CHANNEL_CMP1_DAC                  ADC_CHANNEL_INTERNAL_4
/** @}*/

/**
 * @brief The ADC conversion complete callback function prototype
 *
 */
typedef void (*ADC_ConvCompleteCallbackType)(const uint32_t *const pBuff);

/**
 * @brief The ADC overrun callback function prototype
 *
 */
typedef void (*ADC_OverRunInterruptCallbackType)(void);

/**
 * @brief The ADC compare callback function prototype
 *
 */
typedef void (*ADC_CompareInterruptCallbackType)(void);

/**
 * @brief The ADC end of sequence group callback function prototype
 *
 */
typedef void (*ADC_EndOfSeqGroupInterruptCallbackType)(uint8_t u8SeqGroupIdx);

/**
 * @brief The instance index of the ADC peripheral
 *
 */
typedef enum
{
    ADC_INSTANCE_0 = 0U,  /*!< ADC instance 0 is selected */
    ADC_INSTANCE_1 = 1U,  /*!< ADC instance 1 is selected */
} ADC_InstanceType;

/**
 * @brief The channel selected for ADC conversion
 *
 */
typedef enum
{
    ADC_CHANNEL_0          = 0U,
    ADC_CHANNEL_1          = 1U,
    ADC_CHANNEL_2          = 2U,
    ADC_CHANNEL_3          = 3U,
    ADC_CHANNEL_4          = 4U,
    ADC_CHANNEL_5          = 5U,
    ADC_CHANNEL_6          = 6U,
    ADC_CHANNEL_7          = 7U,
    ADC_CHANNEL_8          = 8U,
    ADC_CHANNEL_9          = 9U,
    ADC_CHANNEL_10         = 10U,
    ADC_CHANNEL_11         = 11U,
    ADC_CHANNEL_12         = 12U,
    ADC_CHANNEL_13         = 13U,
    ADC_CHANNEL_14         = 14U,
    ADC_CHANNEL_15         = 15U,
    ADC_CHANNEL_16         = 16U,
    ADC_CHANNEL_17         = 17U,
    ADC_CHANNEL_18         = 18U,
    ADC_CHANNEL_19         = 19U,
    ADC_CHANNEL_20         = 20U,
    ADC_CHANNEL_21         = 21U,
    ADC_CHANNEL_22         = 22U,
    ADC_CHANNEL_23         = 23U,
    ADC_CHANNEL_24         = 24U,
    ADC_CHANNEL_25         = 25U,
    ADC_CHANNEL_26         = 26U,
    ADC_CHANNEL_27         = 27U,
    ADC_CHANNEL_28         = 28U,
    ADC_CHANNEL_29         = 29U,
    ADC_CHANNEL_30         = 30U,
    ADC_CHANNEL_31         = 31U,
    ADC_CHANNEL_INTERNAL_0 = 32U,
    ADC_CHANNEL_INTERNAL_1 = 33U,
    ADC_CHANNEL_INTERNAL_2 = 34U,
    ADC_CHANNEL_INTERNAL_3 = 35U,
    ADC_CHANNEL_INTERNAL_4 = 36U,
    ADC_CHANNEL_INTERNAL_5 = 37U
} ADC_ChannelType;

/**
 * @brief The channel selected for ADC conversion in differential mode
 *
 */
typedef enum
{
    ADC_CHANNEL_0_4        = 0U,
    ADC_CHANNEL_1_5        = 1U,
    ADC_CHANNEL_2_6        = 2U,
    ADC_CHANNEL_3_7        = 3U,
    ADC_CHANNEL_TEMPSENSOR = 37U
} ADC_DifferentialChannelType;

/**
 * @brief The ADC sample time option for selection
 *
 */
typedef enum
{
    ADC_SAMPLE_TIME_OPTION_0 = 0U,
    ADC_SAMPLE_TIME_OPTION_1 = 1U,
    ADC_SAMPLE_TIME_OPTION_2 = 2U,
    ADC_SAMPLE_TIME_OPTION_3 = 3U
} ADC_SampleTimeOptionType;

/**
 * @brief The ADC SequenceGroup Index
 *
 */
typedef enum
{
    ADC_SEQUENCE_GROUP_0 = 0U,
    ADC_SEQUENCE_GROUP_1 = 1U,
    ADC_SEQUENCE_GROUP_2 = 2U,
    ADC_SEQUENCE_GROUP_3 = 3U
} ADC_SequenceGroupIndex;

/**
 * @brief ADC operation return values
 *
 */
typedef enum
{
    ADC_STATUS_SUCCESS = 0x0U,  /*!< The ADC operation is succeed */
    ADC_STATUS_ERROR   = 0x1U,  /*!< The ADC operation is failed */
    ADC_STATUS_TIMEOUT = 0x2U   /*!< The ADC operation is failed because of time out */
} ADC_StatusType;

/**
 * @brief Defines the converter configuration
 *
 * This structure is used to configure the ADC converter
 *
 * Implements : ADC_InitType
 */
typedef struct
{
    ADC_ResolutionType eResolution;      /*!< ADC eResolution (8,10,12 bit) */
    ADC_AlignType eAlign;                /*!< ADC alignment (left, right) */
    ADC_TrigModeType eTriggerMode;       /*!< ADC trigger type (software, hardware)
                                             - affects only the first control channel */
    bool bWaitEnable;                    /*!< Whether to enable ADC wait conversion mode */
    bool bSequenceGroupModeEnable;       /*!< Whether to enable ADC sequence group mode, if true, ignore eSequenceMode*/
    bool bCalEnable;					 /*!< Whether to enable ADC calibration > */
    int32_t s32CalOffset;				 /*!< ADC calibration offset value > */
    int32_t s32CalGain;					 /*!< ADC calibration gain value > */
    ADC_TrgLatchUnitPri eTrgLatchUnitPri;  /*!< Select priority of Trigger Latch Unit */
    ADC_ClockDivideType eClockDivider;   /*!< ADC clock divider */
    ADC_SeqModeType eSequenceMode;       /*!< ADC sequence mode (single, continuous, discontinuous) */
    bool bAutoDis;                       /*!< Whether to enable audo disable mode, only set this when adc in off state */
    ADC_OvrModeType eOverrunMode;        /*!< Whether to preserve data when ADC overruns */
    ADC_RefType eVoltageRef;             /*!< Voltage reference used (external, internal) */
    bool bHwAvgEnable;                   /*!< Enable averaging functionality */
    ADC_AverageType eHwAverage;          /*!< Selection for number of samples used for averaging */
    uint8_t aSampleTimes[ADC_SAMPLE_TIME_OPTION_CNT];  /*!< ADC sample time options, range: 4 ~ 257 */
} ADC_InitType;

/**
 * @brief The configuration option for the ADC channel
 *
 */
typedef struct
{
    ADC_ChannelType          eChannel;          /*!< Selected ADC channel */
    ADC_SampleTimeOptionType eSampleTimeOption; /*!< The sample time selection for the channel */
    bool                     bDiff;             /*!< Whether diff mode, if a channel do not support differential mode, ignore this */
} ADC_ChannelCfgType;

/**
 * @brief The configuration option for the ADC sequence group
 *
 */
typedef struct
{
    uint8_t u8Start;       /*!< Sequence channel start */
    uint8_t u8Len;         /*!< Sequence group length, is must be >= 0 */
} ADC_SequenceGroupType;


/**
 * @brief Defines the hardware compare configuration
 *
 * This structure is used to configure the hardware compare feature for the ADC
 *
 * Implements : ADC_CompareType
 */
typedef struct
{
    /* ADC_CMP_CTRL */
    bool bCmpEnable;                     /*!< Enable hardware compare */
    ADC_CmpChannelType eCmpSingleChn;    /*!< 0: ADC compare on all channels;
                                              1: ADC compare on the selected channel */
    uint8_t u8CmpChnSel;                 /*!< Compare channel selection */

    /* ADC_CMP_TR */
    uint16_t u16HighThres;               /*!< Compare high threshold */
    uint16_t u16LowThres;                /*!< Compare low threshold */
} ADC_CompareType;

/**
 * @brief Defines the interrupt configuration
 *
 * This structure is used to configure the enabled interrupts and interrupt
 * callbacks for ADC
 *
 */
typedef struct
{
    /* ADC_INT_ENABLE */
    bool bConversionCompleteIntEn;    /*!< Enable interrupt when conversion completed */
    bool bOverRunIntEn;               /*!< Enable interrupt when overrun occured */
    bool bAnalogCmpIntEn;             /*!< Enable interrupt when conversion result lays in the compare threshold */
    bool bEndOfSeqGroupIntEn;		  /*!< Enable interrupt when sequence group complete >*/
    uint32_t *pResultBuffer;          /*!< When conversion complete interrupt is enabled, you shall provide the
                                           result buffer to store the conversion results, this buffer only used for mode 0 ~ 3  */
    uint32_t *pSequenceGroupResultBuffer[ADC_SEQUENCE_GROUP_CNT];         /*!< When conversion complete interrupt is enabled, you shall provide the
                                                                               result buffer to store the conversion results, these buffer only used for mode 4 */
    ADC_ConvCompleteCallbackType pConvCompleteNotify; /*!< Conversion complete interrupt callback */
    ADC_OverRunInterruptCallbackType pOverRunNotify;  /*!< Overrun interrupt callback */
    ADC_CompareInterruptCallbackType pCompareNotify;  /*!< Compare interrupt callback */
    ADC_EndOfSeqGroupInterruptCallbackType pEndOfSeqGroupNotify; /*!< End of Sequence End callback >*/
} ADC_InterruptType;

/**
 * @brief Defines the DMA configuretion
 *
 * This structure is used to configure the DMA result transfer feature for ADC
 *
 */
typedef struct
{
    bool bDmaEnable;                     /*!< Enable DMA for the ADC */
    ADC_SequenceGroupIndex eSeqGroupIndex;  /*!< Only valid when SequenceGroupEn = true, otherwish ignore this */
    DMA_InstanceType eDmaInstance;       /*!< The instance of DMA to use */
    DMA_ChannelType eDmaChannel;         /*!< The DMA channel used to transfer the ADC conversion results */
    uint8_t u8ChannelPriority;           /*!< The DMA channel priority, higher value means higher priority.
                                              The priority for different channels must be unique. Default priority
                                              value is same the channel number */
    uint32_t *pResultBuffer;             /*!< Buffer to store the ADC conversion results */
    ADC_ConvCompleteCallbackType pConvCompleteNotify;  /*!< DMA transfer complete callback */
} ADC_DmaType;

/**
 * @brief Provide the default values of ADC_InitType
 *
 * @param pInitCfg the structure to initialize
 */
void ADC_InitStructure(ADC_InitType *const pInitCfg);

/**
 * @brief Initialize the ADC instance
 *
 * @param eInstance the ADC instance to init
 * @param pInitCfg the configurations of the ADC instance
 */
void ADC_Init(const ADC_InstanceType eInstance, const ADC_InitType *const pInitCfg);

/**
 * @brief De-initialize the ADC instance
 *
 * Restore the ADC instance to its reset state
 *
 * @param eInstance the ADC instance to de-init
 */
void ADC_DeInit(const ADC_InstanceType eInstance);

/**
 * @brief Configure the ADC sample channels
 *
 * @param eInstance the ADC instance to use
 * @param pChannels the channels to use
 * @param u8ChnCnt the quantity of channels
 */
void ADC_InitChannel(const ADC_InstanceType eInstance, const ADC_ChannelCfgType aChannels[],
                     const uint8_t u8ChnCnt);

/**
 * @brief Configure the Sequence groups
 *
 * @param eInstance the ADC instance to use
 * @param aSeqGroup the sequence groups to use
 * @param u8SeqGroupCnt the quantity of sequence groups
 */
void ADC_InitSequenceGroup(const ADC_InstanceType eInstance, const ADC_SequenceGroupType aSeqGroup[],
                     const uint8_t u8SeqGroupCnt);

/**
 * @brief Configure the hardware compare feature of ADC
 *
 * @param eInstance the ADC instance to use
 * @param pCmpCfg the compare paremeters
 */
void ADC_InitCompare(const ADC_InstanceType eInstance, const ADC_CompareType *const pCmpCfg);

/**
 * @brief Configure the interrupt of ADC
 *
 * @param eInstance the ADC instance to use
 * @param pInterruptCfg the interrupt paremeters
 */
void ADC_InitInterrupt(const ADC_InstanceType eInstance,
                       const ADC_InterruptType *const pInterruptCfg);

/**
 * @brief Configure the DMA feature of ADC
 *
 * @param eInstance the ADC instance to use
 * @param pAdcDmaCfg the DMA paremeters for the ADC instance
 */
void ADC_InitDmaChannel(const ADC_InstanceType eInstance, const ADC_DmaType *const pAdcDmaCfg);

/**
 * @brief Enable the ADC instance
 *
 * @param eInstance the ADC instance to enable
 * @return ADC_StatusType whether ADC is enabled successfully
 */
ADC_StatusType ADC_Enable(const ADC_InstanceType eInstance);

/**
 * @brief Disable the ADC instance
 *
 * @param eInstance the ADC instance to disable
 * @return ADC_StatusType whether ADC is disabled successfully
 */
ADC_StatusType ADC_Disable(const ADC_InstanceType eInstance);

/**
 * @brief Start the ADC conversion
 *
 * If the ADC sequence mode is single or continuous, and the trigger mode is ADC_TRIGMODE_SW,
 * the adc conversion will start immediately. Otherwise, the ADC will wait for the trigger
 * signal to start the conversion
 *
 * @param eInstance the ADC instance to start
 */
void ADC_Start(const ADC_InstanceType eInstance);

/**
 * @brief Stop the ADC conversion
 *
 * If the ADC sequence mode is single, it will stop the ongoing conversion. If no ongoing
 * conversion, it will have no effect. If the ADC sequence mode is continuous or discontinuous,
 * it will stop the ongoing conversion and meanwhile the further conversions.
 *
 * @param eInstance the ADC instance to stop
 * @return ADC_StatusType whether ADC is stopped successfully
 */
ADC_StatusType ADC_Stop(const ADC_InstanceType eInstance);

/**
 * @brief Reset the ADC hardware
 *
 * @param eInstance the ADC instance to reset
 */
void ADC_Reset(const ADC_InstanceType eInstance);

/** @}*/

/** @}*/ /* fc7xxx_driver_adc */
#if defined(__cplusplus)
}
#endif
#endif
