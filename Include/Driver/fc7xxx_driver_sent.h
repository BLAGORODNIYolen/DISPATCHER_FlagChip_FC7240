/**
 * @file fc4xxx_driver_sent.h
 * @author Flagchip073
 * @brief FC7xxx SENT driver type definition and API
 * @version 0.1.0
 * @date 2022-12-14
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2022-12-14    Flagchip073   N/A          First version for FC7300 SENT module
   ******************************************************************************** */

#ifndef _DRIVER_FC4XXX_DRIVER_SENT_H_
#define _DRIVER_FC4XXX_DRIVER_SENT_H_
#include "device_header.h"

#if defined(__cplusplus)
extern "C" {
#endif
    /**
     * @addtogroup fc7xxx_driver_sent
     * @{
     */

    /**
     * @brief SENT buffer address and size in DMA mode
     *
     */
#define SENT0_GET_FAST_MSG_DMA_ADDR(echannel)         (&(SENT->SENT_CHN[echannel].CHN_DFD))
#define SENT_GET_FAST_MSG_DMA_BYTELENGTH              (12U)
#define SENT0_GET_SLOW_MSG_DMA_ADDR(echannel)         (&(SENT->SENT_CHN[echannel].CHN_DSB3))
#define SENT_GET_SLOW_MSG_DMA_BYTELENGTH              (12U)

    /**
     * @brief SENT operation return values
     *
     */
    typedef enum
    {
        SENT_RETURN_OK                 = 0x00U,   /*!< The SENT operation is succeeded */
        SENT_RETURN_E_NOT_OK           = 0x01U,   /*!< The SENT operation is failed */
        SENT_RETURN_E_ALREADY_INIT     = 0x02U,   /*!< The SENT has been initialized. */
        SENT_RETURN_E_UNINIT           = 0x03U,   /*!< The SENT is not initialized */
        SENT_RETURN_E_PARAM            = 0x04U,   /*!< The SENT parameter is incorrect or out of range. */
    }
    Sent_ReturnType;

    /**
     * @brief SENT Channel index
     *
     */
    typedef enum
    {
        SENT_CHANNEL_0                 = 0x00U,   /*!< The SENT channel 0 */
        SENT_CHANNEL_1                 = 0x01U,   /*!< The SENT channel 1 */
        SENT_CHANNEL_2                 = 0x02U,   /*!< The SENT channel 2 */
        SENT_CHANNEL_3                 = 0x03U,   /*!< The SENT channel 3 */
        SENT_CHANNEL_MAX               = SENT_CHANNEL_COUNT
    } Sent_ChannelType;

    /**
     * @brief SENT instance index
     *
     */
    typedef enum
    {
        SENT_INSTANCE_0                 = 0x00U,   /*!< The SENT channel 0 */
        SENT_INSTANCE_1                 = 0x01U,   /*!< The SENT channel 1 */
        SENT_INSTANCE_MAX               = SENT_INSTANCE_COUNT
    } Sent_InstanceType;

    /**
     * @brief SENT nibble data mode control. Refer to SENT SAE J2716 2010 for detail protocol definition
     *
     */
    typedef enum
    {
        SENT_DATA_NIBBLE_MODE_A    = 0x0U,   /*!< Frame format A */
        SENT_DATA_NIBBLE_MODE_H1   = 0x1U,   /*!< Frame format H1 */
        SENT_DATA_NIBBLE_MODE_H2   = 0x2U,   /*!< Frame format H2 */
        SENT_DATA_NIBBLE_MODE_H3   = 0x3U,   /*!< Frame format H3 */
        SENT_DATA_NIBBLE_MODE_H4   = 0x4U,   /*!< Frame format H4 */
        SENT_DATA_NIBBLE_MODE_H5   = 0x5U,   /*!< Frame format H5 */
        SENT_DATA_NIBBLE_MODE_H6   = 0x6U,   /*!< Frame format H6 */
        SENT_DATA_NIBBLE_MODE_H7   = 0x7U    /*!< Frame format H7 */
    } Sent_DataNibbleModeType;

    /**
     * @brief SENT calibration valid type
     *
     */
    typedef enum
    {
        SENT_CALIBRATION_VALID_DISABLE         = 0x0U,   /*!< The successive calibration pulses diagnostic will be disabled */
        SENT_CALIBRATION_VALID_WITHIN_20       = 0x1U,   /*!< The difference of received calibration pulse and receiver configuration is within 20%, the message is deemed to be valid */
        SENT_CALIBRATION_VALID_FROM_20_TO_25   = 0x2U,   /*!< The difference of received calibration pulse and receiver configuration is more than 20% but less than 25%, the message is deemed to be valid */
    } Sent_CalibrationValidType;

    /**
     * @brief SENT Successive calibration pulses diagnostic option
     *
     */
    typedef enum
    {
        SENT_CALIBRATION_PULSE_DIAG_OPTION2       = 0x0U,   /*!< Option 2 i.e. Low Latency Option as per SAE Specification */
        SENT_CALIBRATION_PULSE_DIAG_OPTION1       = 0x1U,   /*!< Option 1 i.e. Preferred but High Latency Option as per SAE Specification */
    } Sent_CalDiagOptionType;

    /**
     * @brief Determines how long the bus idle flag will assert when SENT bus is idle
     *
     */
    typedef enum
    {
        SENT_IDLE_COUNT_FLAG_DISABLE           = 0x0U,   /*!< The bus idle flag will never assert */
        SENT_IDLE_COUNT_FLAG_254_TICKS         = 0x1U,   /*!< The bus is idle for more than 127*2 ticks, then the bus idle flag will assert */
        SENT_IDLE_COUNT_FLAG_508_TICKS         = 0x2U,   /*!< The bus is idle for more than 127*2 ticks, then the bus idle flag will assert */
        SENT_IDLE_COUNT_FLAG_1016_TICKS        = 0x4U,   /*!< The bus is idle for more than 127*2 ticks, then the bus idle flag will assert */
        SENT_IDLE_COUNT_FLAG_2032_TICKS        = 0x8U,   /*!< The bus is idle for more than 127*2 ticks, then the bus idle flag will assert */
    } Sent_IdleCountType;

    /**
     * @brief SENT Slow message type.
     *
     */
    typedef enum
    {
        SENT_SERIAL_MESSAGE_SHORT                = 0x0U,   /*!< short serial data message */
        SENT_SERIAL_MESSAGE_ENHANCE_12DATA_8ID   = 0x1U,   /*!< enhanced serial data message with 12-bit data and 8-bit ID */
        SENT_SERIAL_MESSAGE_ENHANCE_16DATA_4ID   = 0x2U,   /*!< enhanced serial data message with 16-bit data and 4-bit ID */
    } Sent_SerialMessageType;

    /**
     * @brief SENT trigger type in SPC mode
     *
     */
    typedef enum
    {
        SENT_SPC_SOFTWARE_TRIGGER               = 0x0U,   /*!< SPC pulse triggered by software method */
        SENT_SPC_EXTERNAL_TRIGGER               = 0x1U,   /*!< SPC pulse triggered by external trigger */
    } Sent_SpcTriggerType;

    /**
     * @brief Select the tick base in SPC mode
     *
     */
    typedef enum
    {
        SENT_SPC_TICK_BASE_PRE_MSG         = 0x0U,   /*!< Previous received message tick base */
        SENT_SPC_TICK_BASE_CONFIGURED      = 0x1U,   /*!< SENT configured tick base */
    } Sent_SpcTickBaseType;

    /**
     * @brief Sent global interrupt type.
     *
     */
    typedef enum
    {
        SENT_SLOW_MSG_DMA_UF_IT        = 0U,     /*!< Slow message dma read underflow interrupt enable. */
        SENT_FAST_MSG_DMA_DF_IT        = 1U,     /*!< Fast message dma read underflow interrupt enable. */
        SENT_FAST_MSG_READY_IT         = 2U,     /*!< Fast message ready interrupt enable. */
        SENT_SLOW_MSG_READY_IT         = 3U,     /*!< Slow message ready interrupt enable. */
        SENT_FAST_MSG_FIFO_OF_IT       = 4U,     /*!< Fast message FIFO overflow interrupt enable. */
    } Sent_GlobalInterruptType;

    /**
     * @brief Structure to enable or disable the channel interrupts.
     *
     */
    typedef struct
    {
        bool bBusIdleITEn;              /*!< Bus idle interrupt enable. */
        bool bSpcOverrunITEn;           /*!< SPC overrun interrupt enable. */
        bool bCalResyncErrITEn;         /*!< Continuous 2 sync/calibration pulse difference exceed 1.5625% error interrupt enable. */
        bool bCalFailITEn;              /*!< Calibation 20% pass 25% fail interrupt enable. */
        bool bSlowMsgOFITEn;            /*!< Slow message overflow interrupt enable. */
        bool bFastMsgOFITEn;            /*!< Fast message overflow interrupt enable. */
        bool bNibbleValueErrITEn;       /*!< Nibble value more than 15 or less than 0 error interrupt enable. */
        bool bPrePulseDiagErrITEn;      /*!< Previous pulse diagnosis error interrupt enable. */
        bool bCalDiagErrITEn;           /*!< Calibration diagnosis over 25% error interrupt enable. */
        bool bCalErrITEn;               /*!< Sync/calibration pulse difference eceed 1.5625% error interrupt enable. */
        bool bSlowMsgCrcErrITEn;        /*!< Slow message CRC check error interrupt enable. */
        bool bFastMsgCrcErrITEn;        /*!< Fast message CRC check error interrupt enable. */
        bool bFallingEdgeNumErrITEn;    /*!< Falling edge number error interrupt enable. */
    } Sent_ChannelInterruptType;

    /**
     * @brief Structure for fast message buffer.
     *
     */
    typedef struct
    {
        uint8_t  u8CRC;             /*!< Receied fast message CRC data. */
        uint8_t  u8SC;              /*!< Fast message status communication nibble value. */
        uint32_t u32Timestamp;      /*!< Fast message timestamp value. */
        uint32_t u32Data;           /*!< Received fast message data nibble. */
    } Sent_FastMessageDataType;

    /**
     * @brief Structure for slow message buffer.
     *
     */
    typedef struct
    {
        Sent_SerialMessageType eMsgType;        /*!< Slow message type. */
        uint8_t  u8CRC;                         /*!< Slow message crc data. */
        uint8_t  u8ID;                          /*!< Slow message ID. */
        uint16_t u16Data;                       /*!< Slow message data. */
        uint32_t u32Timestamp;                  /*!< Slow message timestamp value. */
    } Sent_SlowMessageDataType;

    /**
     * @brief SENT Global ISR callback function prototype
     *
     */
    typedef void (*SENT_GBISRCallbackType)(Sent_ChannelType eChannel, const Sent_GlobalInterruptType eInterrupt);

    /**
     * @brief SENT Channel ISR callback function prototype
     *
     */
    typedef void (*SENT_CHISRCallbackType)(Sent_ChannelType eChannel, const uint32_t u32ChannelStatus);

    /**
     * @brief structure to configure the SENT.
     *
     */
    typedef struct
    {
        uint8_t                 u8PreScaler;          /*<! This value is used to divide the function clock to count the timestamp */
        uint8_t                 u8DmaWaterMark;       /*<! When Fast message DMA request is enabled, the request will asserts if data number in FIFO is more than watermark */
        bool                    bDebugModeEn;         /*<! If enable, the SENT will keep running under debug mode. */
        bool                    bAutoClearReadyFlag;  /*!< When enabled after data ready read of received data, crc and timestamp register will prevent the assert of data overflow flag. */
        SENT_GBISRCallbackType  pGBCallback;          /*<! Global interrupt callback function */
        SENT_CHISRCallbackType  pCHCallback;          /*<! Channel interrupt callback function */
    } Sent_ConfigType;

    /**
     * @brief structure to configure the SENT channel.
     *
     */
    typedef struct
    {
        uint8_t                     u8DataNibbleNumber;      /*!< The received data number will be configured value plus 1, 0 and value bigger than 5 is forbidden. */
        uint8_t                     u8DigitalFilterCount;    /*!< The input signal needs keep stable for (filt_cnt<<2)* function_clk cycles to pass through the digital filter. */
        uint16_t                    u16TickScaler;           /*!< The value plus 1 is used to divide the function clock to tick clock. */
        Sent_CalDiagOptionType      eCalDiagOption;          /*!< Successive calibration pulses diagnostic option. */
        Sent_DataNibbleModeType     eDataNibbleMode;         /*!< Refer to SENT SAE J2716 2010 for detail protocol definition. */
        Sent_CalibrationValidType   eCalValid;               /*!< Select valid Calibration pulse range */
        Sent_IdleCountType          eIdleCount;              /*!< Select how long the bus idle flag will assert when bus is idle */
        bool                        bFastMessageFifoEn;      /*!< Enable Channel FIFO function. */
        bool                        bTickCompensateEn;       /*!< Enable the tick period compensate function. */
        bool                        bUseAlternativeCrc;      /*!< Use alternative 4-bit CRC algorithm instead of SAE CRC algorithm. */
        bool                        bFastMsgCRCCheckEn;      /*!< Enable Fast message CRC check.  */
        bool                        bFastMsgDataChangeEn;    /*!< If enabled, the SENT will only assert the fast message ready flag when received data has changed compared with previous data */
        bool                        bFastMsgCRCAugEn;        /*!< Augmentation is selected for Fast Message CRC calculation. */
        bool                        bFastMsgCRCWithSCEn;     /*!< If enabled, the crc calculation will includes S&C nibble. */
        bool                        bSlowMsgCRCAugEn;        /*!< Augmentation is selected for Short Serial Message CRC calculation. */
        bool                        bPausePulseEn;           /*!< If enabled, a pause pulse will be appended at the end of a frame. */
        bool                        bChannelEn;              /*!< Enable the SENT Channel. */
    } Sent_ChannelConfigType;

    /**
     * @brief structure to configure the SENT channel DMA.
     *
     */
    typedef struct
    {
        bool                        bFastMsgDmaEn;           /*!< Fast message DMA request enable. */
        bool                        bSlowMsgDmaEn;           /*!< Slow message DMA request enable. */
    } Sent_DMAConfigType;

    /**
     * @brief structure to configure the SENT channel SPC.
     *
     */
    typedef struct
    {
        uint8_t                     u8PulseWidth;         /*!< Configure the width of the SPC pulse. */
        uint8_t                     u8PulseDelay;         /*!< Configure the delay between SPC-trigger assert and finally generate a SPC pulse. */
        Sent_SpcTickBaseType        eSpcTickBase;         /*!< Select the tick base of SPC */
        Sent_SpcTriggerType         eSpcTrigger;          /*!< Select the SPC pulse trigger type. */
        bool                        bCalDiagEn;           /*!< Enable Calibration diagnosis. */
        bool                        bSpcModeEn;           /*!< Enable SPC mode. */
    } Sent_SpcConfigType;

    /**
     * @brief Initialize SENT configuration
     *
     * @param  eInstance The instance of SENT
     * @param  ConfigPtr The basic configurations of the SENT
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_Init(const Sent_InstanceType eInstance, const Sent_ConfigType *ConfigPtr);

    /**
     * @brief Set SENT channel configuration
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @param  ConfigPtr The channel configurations of the SENT
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_SetChannelConfig(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, const Sent_ChannelConfigType *pCfg);

    /**
     * @brief Set SENT DMA configuration
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @param  ConfigPtr The channel configurations of the DMA
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_SetDMAConfig(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, Sent_DMAConfigType *pCfg);

    /**
     * @brief Set SENT SPC configuration
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @param  ConfigPtr The channel configurations of the SPC
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_SetSPCConfig(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, const Sent_SpcConfigType *pCfg);

    /**
     * @brief Get Fast message data.
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @param  pMsg      The Fast message structure buffer.
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_GetFastMessageData(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, Sent_FastMessageDataType *pMsg);

    /**
     * @brief Get Slow message data.
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @param  pMsg      The slow message structure buffer.
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_GetSlowMessageData(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, Sent_SlowMessageDataType *pMsg);

    /**
     * @brief Decode the fast message with DMA buffer.
     *
     * @param  pDmaBuffer       The pointer for DMA buffer. the buffer length should be 12bytes.
     * @param  u32BufferLength  The byte length of dma buffer.
     * @param  pMsg             The fast message structure buffer.
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_DecodeFastMessageWithDMABuffer(uint32_t *pDmaBuffer, uint32_t u32BufferLength, Sent_FastMessageDataType *pMsg);

    /**
     * @brief Decode the slow message with DMA buffer.
     *
     * @param  pDmaBuffer       The pointer for DMA buffer. the buffer length should be 12bytes.
     * @param  u32BufferLength  The byte length of dma buffer.
     * @param  pMsg             The slow message structure buffer.
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_DecodeSlowMessageWithDMABuffer(uint32_t *pDmaBuffer, uint32_t u32BufferLength, Sent_SlowMessageDataType *pMsg);

    /**
     * @brief Enable the fast message ready interrupt
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_EnableGlobalFastMsgNotification(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel);

    /**
     * @brief Disable the fast message ready interrupt
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_DisableGlobalFastMsgNotification(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel);

    /**
     * @brief Enable the slow message ready interrupt
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_EnableGlobalSlowMsgNotification(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel);
    /**
     * @brief Disable the slow message ready interrupt
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_DisableGlobalSlowMsgNotification(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel);

    /**
     * @brief Enable the fast message fifo interrupt
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_EnableGlobalFastFifoMsgNotification(const Sent_InstanceType eInstance);

    /**
     * @brief Disable the fast message fifo interrupt
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_DisableGlobalFastFifoMsgNotification(const Sent_InstanceType eInstance);

    /**
     * @brief configure the channel interrupt.
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @param  sInterruptEn the structure of interrupt enable
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_ConfigChannelStatusNotification(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, const Sent_ChannelInterruptType *sInterruptEn);

    /**
     * @brief Request the SPC pulse
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_RequestSPCPulse(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel);

    /**
     * @brief Get the fast message ready flag
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @param  pFlag     The point of flag(true or false)
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_GetFastMsgReadyFlag(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, bool *pFlag);

    /**
     * @brief Get the slow message ready flag
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @param  pFlag     The point of flag(true or false)
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_GetSlowMsgReadyFlag(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, bool *pFlag);

    /**
     * @brief Get the channel status
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @param  pStatus   The point of channel status
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_GetChannelStatus(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, uint32_t *pStatus);

    /**
     * @brief Clear the channel status
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @param  Status    The channel status, the bits are used for W1c
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_ClearChannelStatus(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, uint32_t Status);

    /**
     * @brief Get the channel SPC busy flag
     *
     * @param  eInstance The instance of SENT
     * @param  eChannel  The channel of the selected SENT instance
     * @param  pflag     The point of flag(true or false)
     * @return Sent_ReturnType whether the operation is successfully
     */
    Sent_ReturnType SENT_GetChannelSPCBusyFlag(const Sent_InstanceType eInstance, const Sent_ChannelType eChannel, bool *pflag);

    /** @}*/ /* fc7xxx_driver_sent */
#if defined(__cplusplus)
}
#endif
#endif
