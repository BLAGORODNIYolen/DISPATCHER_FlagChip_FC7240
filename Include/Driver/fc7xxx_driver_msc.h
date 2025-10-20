/**
 * @file fc7xxx_driver_msc.h
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

#ifndef _DRIVER_FC7XXX_DRIVER_MSC_H_
#define _DRIVER_FC7XXX_DRIVER_MSC_H_
#include "device_header.h"
#include "HwA_msc.h"
/**
 * @addtogroup fc7xxx_driver_msc
 * @{
. */

typedef enum
{
    MSC_RETURN_OK       = 0x00U, /*!< The SENT operation is succeeded */
    MSC_RETURN_E_NOT_OK = 0x01U, /*!< The SENT operation is failed */
    MSC_RETURN_E_PARAM  = 0x04U, /*!< The SENT parameter is incorrect or out of range. */
} MSC_ReturnType;

typedef enum
{
    MSC_RDR0       = 0x0U,
    MSC_RDR1       = 0x1U,
    MSC_RDR2       = 0x2U,
    MSC_RDR3       = 0x3U,
    MSC_RDRx_COUNT = 0x4U
} MSC_RDRxIndexType;

typedef enum
{
    MSC_INSTANCE_0 = 0U, /*!< MSC instance 0 is selected. */
    MSC_INSTANCE_1 = 1U  /*!< MSC instance 1 is selected. */
} MSC_InstanceType;

typedef enum
{
    MSC_RFIE_DISABLE = 0x0U, /*!< Interrupt generation disabled. */
    MSC_RFIE_MODE1   = 0x1U, /*!< The interrupt is generated when data is received and written into the RDRx. */
    MSC_RFIE_MODE2   = 0x2U, /*!< The interrupt is generated when received data is not equal to 0. */
    MSC_RFIE_MODE3   = 0x3U  /*!< The interrupt is generated when data is received and written into register RDR3. */
} MSC_RFIEModeType;

typedef enum
{
    MSC_DFIE_DISABLE = 0x0U, /*!< Disable. */
    MSC_DFIE_MODE1   = 0x1U, /*!< Interrupt is generated when the last data bit has been shifted. */
    MSC_DFIE_MODE2   = 0x2U  /*!< Interrupt is generated when the first data bit has been shifted. */
} MSC_DFIEModeType;

/**
 * @brief MSC Channel ISR callback function prototype
 *
 */
typedef void (*MSC_ISRCallbackType)(const MSC_InstanceType eInstance);

/** @brief MSC interrupt configure structure. */
typedef struct
{
    bool                bCFIntEnable;               /*!< MSC_INCR[CFIE] bit, interrupt enable, if this bit asserted, command frame can lead the interrupt. */
    bool                bTFIntEnable;               /*!< MSC_INCR[TFIE] bit, interrupt enable, if this bit asserted, time frame can lead the interrupt. */
    MSC_RFIEModeType    eRFIEMode;                  /*!< Interrupt mode of RFIE. */
    MSC_DFIEModeType    eDFIEMode;                  /*!< Interrupt mode of DFIE. */
    bool                bTOIntEnable;               /*!< Enable the interrupt of timeout. */
    uint16_t            u16TimeoutValue;            /*!< Timeout value of timeout interrupt. */
    MSC_ISRCallbackType pReceiveFrameISRCallback;   /*!< Receive frame ISR callback. */
    MSC_ISRCallbackType pTimeFrameISRCallback;      /*!< Time Frame ISR callback. */
    MSC_ISRCallbackType pCommandFrameISRCallback;   /*!< Command Frame ISR callback. */
    MSC_ISRCallbackType pDataFrameISRCallback;      /*!< Data Frame ISR callback. */
    MSC_ISRCallbackType pReceiveTimeOutISRCallback; /*!< Data Frame ISR callback. */
} MSC_InterruptCfgType;

typedef enum
{
    MSC_SDI_SEL_SDI0 = 0x0U, /*!< SDI0 input is selected for SDI. */
    MSC_SDI_SEL_SDI1 = 0x1U, /*!< SDI1 input is selected for SDI. */
    MSC_SDI_SEL_SDI2 = 0x2U, /*!< SDI2 input is selected for SDI. */
    MSC_SDI_SEL_SDI3 = 0x3U, /*!< SDI3 input is selected for SDI. */
    MSC_SDI_SEL_SDI4 = 0x4U, /*!< SDI4 input is selected for SDI. */
    MSC_SDI_SEL_SDI5 = 0x5U, /*!< SDI5 input is selected for SDI. */
    MSC_SDI_SEL_SDI6 = 0x6U, /*!< SDI6 input is selected for SDI. */
    MSC_SDI_SEL_SDI7 = 0x7U  /*!< SDI7 input is selected for SDI. */
} MSC_SDISelectionType;

typedef enum
{
    MSC_ENC_SEL_EN0 = 0x0U, /*!< EN0 is selected for ENC. */
    MSC_ENC_SEL_EN1 = 0x1U, /*!< EN1 is selected for ENC. */
    MSC_ENC_SEL_EN2 = 0x2U, /*!< EN2 is selected for ENC. */
    MSC_ENC_SEL_EN3 = 0x3U  /*!< EN3 is selected for ENC. */
} MSC_ENCSelectionType;

typedef enum
{
    MSC_ENH_SEL_EN0 = 0x0U, /*!< EN0 is selected for ENH. */
    MSC_ENH_SEL_EN1 = 0x1U, /*!< EN1 is selected for ENH. */
    MSC_ENH_SEL_EN2 = 0x2U, /*!< EN2 is selected for ENH. */
    MSC_ENH_SEL_EN3 = 0x3U  /*!< EN3 is selected for ENH. */
} MSC_ENHSelectionType;

typedef enum
{
    MSC_ENL_SEL_EN0 = 0x0U, /*!< EN0 is selected for ENL. */
    MSC_ENL_SEL_EN1 = 0x1U, /*!< EN1 is selected for ENL. */
    MSC_ENL_SEL_EN2 = 0x2U, /*!< EN2 is selected for ENL. */
    MSC_ENL_SEL_EN3 = 0x3U  /*!< EN3 is selected for ENL. */
} MSC_ENLSelectionType;

typedef enum
{
    MSC_EN_SELECTION_0 = 0x00, /*!< EN0 is selected for ENX. */
    MSC_EN_SELECTION_1 = 0x01, /*!< EN1 is selected for ENX. */
    MSC_EN_SELECTION_2 = 0x02, /*!< EN2 is selected for ENX. */
    MSC_EN_SELECTION_3 = 0x03, /*!< EN3 is selected for ENX. */
} Msc_ENxActiveType;

typedef enum
{
    MSC_ENC = 0x00,
    MSC_ENL = 0x01,
    MSC_ENH = 0x02,
} Msc_ENxType;

typedef enum
{
    MSC_FLC_ACTIVE_ON_FRAMES = 0x0U, /*!< FCL is actived only during the active phases of frames. */
    MSC_FLC_ALWAYS_ACTIVE    = 0x1U  /*!< FCL is always active whether or not a downstream frame is transmitted currently.. */
} MSC_FCLControlType;

typedef enum
{
    MSC_INPUT_IDENTICAL = 0x0U, /*!< SDI and SI signal polarities are identical. */
    MSC_INPUT_INVERTED  = 0x1U  /*!< SDI and SI signal polarities are inverted. */
} MSC_InputPolarityType;

typedef enum
{
    MSC_ENX_IDENTICAL = 0x0U, /*!< Enx and ENL, ENH, ENC signal polarities are identical (high active). */
    MSC_ENX_INVERTED  = 0x1U  /*!< ENx and ENL, ENH, ENC signal polarities are inverted (low active). */
} MSC_ENxPolarityType;

typedef enum
{
    MSC_SO_IDENTICAL = 0x0U, /*!< SOP and SO signal polarity is identical. */
    MSC_SO_INVERTED  = 0x1U  /*!< SOP and SO signal polarity is inverted. */
} MSC_SOPolarityType;

typedef enum
{
    MSC_FLC_IDENTICAL = 0x0U, /*!< FCLP and FCL polarity is identical. */
    MSC_FLC_INVERTED  = 0x1U  /*!< FCLP and FCL polarity is inverted. */
} MSC_FCLpolarityType;

typedef struct
{
    MSC_SDISelectionType  eSDIsel;  /*!< SDI seletion. */
    MSC_ENCSelectionType  eENCSel;  /*!< ENC seletion. */
    MSC_ENHSelectionType  eENHSel;  /*!< ENH seletion. */
    MSC_ENLSelectionType  eENLSel;  /*!< ENL seletion. */
    MSC_FCLControlType    eFclCtrl; /*!< FCL Control. */
    MSC_InputPolarityType eSDIPol;  /*!< SDI Polarity. */
    MSC_ENxPolarityType   eENXPol;  /*!< ENX Polarity. */
    MSC_SOPolarityType    eSOPPol;  /*!< SO Polarity. */
    MSC_FCLpolarityType   eFCLPPol; /*!< FCL Polarity. */
} MSC_IOControlInitType;

typedef enum
{
    MSC_TRANS_SOURCE_DATA_REG  = 0x0U, /*!< SSL[x] is taken from TCDAR.DL[x]. */
    MSC_TRANS_SOURCE_ALTIN     = 0x2U, /*!< SSL[x] is taken from the ALTINL input line x. */
    MSC_TRANS_SOURCE_ALTIN_INV = 0x3U, /*!< SSL[x] is taken from the ALTINL input line x in inverted state. */
} MSC_TransSourceType;

typedef enum
{
    MSC_TRIGGER_MODE    = 0x00U, /*!< Trigger work mode. */
    MSC_REPETITION_MODE = 0x01U  /*!< Repetition work mode. */
} MSC_WorkModeType;

typedef enum
{
    MSC_EVEN_PARITY = 0x00U, /*!< Reception even parity. */
    MSC_ODD_PARITY  = 0x01U  /*!< Reception odd parity. */
} MSC_ParityType;

typedef enum
{
    MSC_RECEIVE_DISABLED     = 0x00U, /*!< Receiving channel is disabled. */
    MSC_BAUDRATE_FMSC_DIV4   = 0x01U, /*!< Baud rate=fmsc/4. */
    MSC_BAUDRATE_FMSC_DIV8   = 0x02U, /*!< Baud rate=fmsc/8. */
    MSC_BAUDRATE_FMSC_DIV16  = 0x03U, /*!< Baud rate=fmsc/16. */
    MSC_BAUDRATE_FMSC_DIV32  = 0x04U, /*!< Baud rate=fmsc/32. */
    MSC_BAUDRATE_FMSC_DIV64  = 0x05U, /*!< Baud rate=fmsc/64. */
    MSC_BAUDRATE_FMSC_DIV128 = 0x06U, /*!< Baud rate=fmsc/128. */
    MSC_BAUDRATE_FMSC_DIV256 = 0x07U  /*!< Baud rate=fmsc/256. */
} MSC_ReceiveBaudRateType;

typedef enum
{
    MSC_FRAME_12_BIT = 0x00U, /*!< 12-bit frame selected. */
    MSC_FRAME_16_BIT = 0x01U  /*!< 16-bit frame selected. */
} MSC_ReceiveFrameType;

typedef struct
{
    uint8_t                 u8PassiveLength;    /*!< Frame Passive length. */
    uint8_t                 u8PTFNumber;        /*!< The number of passive time frames that are inserted in repetition mode between two data frames. */
    MSC_WorkModeType        eWorkMode;          /*!< MSC work mode. */
    uint8_t                 u8CommandBitLength; /*!< Bit length of command frame. */
    bool                    bSelSRH;            /*!< Select SRH. */
    uint8_t                 u8SRHDataBitLength; /*!< Bit length of SRH. */
    bool                    bSelSRL;            /*!< Select SRL. */
    uint8_t                 u8SRLDataBitLength; /*!< Bit length of SRL. */
    bool                    bDelayControl;      /*!< Hardware Receive Interrupt Delay Control. */
    MSC_ParityType          eParity;            /*!< Parity mode. */
    MSC_ReceiveBaudRateType eBaudRate;          /*!< Baudrate. */
    MSC_ReceiveFrameType    eRsvFrameType;      /*!< Frame type. */
} MSC_InitCfgType;

/**
 * @brief Init the MSC.
 *
 * @param eInstance MSCInstance.
 * @param pInitConfig MSCInstance initial configuration.
 */
MSC_ReturnType MSC_init(const MSC_InstanceType eInstance, const MSC_InitCfgType *pInitConfig);

/**
 * @brief Init the MSC interrupt.
 *
 * @param eInstance MSCInstance.
 * @param pInteruptConfig MSCInstance interrupt configuration.
 */
void MSC_initInterrupt(const MSC_InstanceType eInstance, const MSC_InterruptCfgType *pInteruptConfig);

/**
 * @brief Select the transmitting sources.
 *
 * @param eInstance MSCInstance.
 * @param u32SourceMask Transmitting sources.
 * @param eSourceType Transmitting sources type.
 */
void MSC_SelTranmittingSource(const MSC_InstanceType eInstance, uint32_t u32SourceMask, MSC_TransSourceType eSourceType);

/**
 * @brief Set Emergency load value.
 *
 * @param eInstance MSCInstance.
 * @param u32Value Emergency load value.
 */
void MSC_SetEmergencyLoad(const MSC_InstanceType eInstance, uint32_t u32Value);

/**
 * @brief Configure the MSC IO control.
 *
 * @param eInstance MSCInstance.
 * @param pIOConfig MSC IO control configuration.
 */
void MSC_SetIOControl(const MSC_InstanceType eInstance, const MSC_IOControlInitType *pIOConfig);

/**
 * @brief Enable MSC.
 *
 * @param eInstance MSCInstance.
 */
void MSC_Enable(const MSC_InstanceType eInstance);

/**
 * @brief Disable MSC.
 *
 * @param eInstance MSCInstance.
 */
void MSC_Disable(const MSC_InstanceType eInstance);

/**
 * @brief MSC set data frame.
 *
 * @param eInstance MSCInstance.
 * @param u32Data Data to be sent.
 */
void MSC_SetDataFrame(const MSC_InstanceType eInstance, uint32_t u32Data);

/**
 * @brief MSC send data frame.
 *
 * @param eInstance MSCInstance.
 */
void MSC_SendDataFrame(const MSC_InstanceType eInstance);

/**
 * @brief MSC send command frame.
 *
 * @param eInstance MSCInstance.
 * @param u32Command command to be sent.
 */
void MSC_SendCommandFrame(const MSC_InstanceType eInstance, uint32_t u32Command);

/**
 * @brief Get the msc received data address.
 *
 * @param eInstance MSCInstance.
 * @param eIndex Receive data register index.
 * @return uint8_t Receiverd data address.
 */
uint8_t MSC_GetReceivedFrameAddr(const MSC_InstanceType eInstance, MSC_RDRxIndexType eIndex);

/**
 * @brief Get the msc received data.
 *
 * @param eInstance MSCInstance.
 * @param eIndex Receive data register index.
 * @param pData Received data value.
 * @return MSC_ReceiveStatusType  Status of getting received data.
 */
MSC_ReceiveStatusType MSC_GetReceivedFrame(const MSC_InstanceType eInstance, MSC_RDRxIndexType eIndex, uint8_t *pData);

/**
 * @brief Get the msc interrupt status.
 *
 * @param eInstance MSCInstance.
 * @return uint32_t Interrupt status.
 */
uint32_t MSC_GetInterruptStatus(const MSC_InstanceType eInstance);

/**
 * @brief Get the msc interrupt status.
 *
 * @param eInstance MSCInstance.
 * @param bEnable Enable transmit channel.
 */
void MSC_EnableTrasmit(const MSC_InstanceType eInstance, bool bEnable);

/**
 * @brief Enable the msc data frame interrupt.
 *
 * @param eInstance MSCInstance.
 */
void MSC_EnableDataFrameInterrupt(const MSC_InstanceType eInstance, bool bEnable);

/**
 * @brief Enable the msc command frame interrupt.
 *
 * @param eInstance MSCInstance.
 */
void MSC_EnableCommandFrameInterrupt(const MSC_InstanceType eInstance, bool bEnable);

/**
 * @brief Enable the msc time frame interrupt.
 *
 * @param eInstance MSCInstance.
 */
void MSC_EnableTimeFrameInterrupt(const MSC_InstanceType eInstance, bool bEnable);

/**
 * @brief Enable the msc receive interrupt.
 *
 * @param eInstance MSCInstance.
 */
void MSC_EnableReceiveInterrupt(const MSC_InstanceType eInstance, bool bEnable);

/**
 * @brief Enable the msc timeout interrupt.
 *
 * @param eInstance MSCInstance.
 */
void MSC_EnableTimeoutInterrupt(const MSC_InstanceType eInstance, bool bEnable);

/**
 * @brief Switch ENC/ENH/ENL active EN selection.
 * @param eInstance MSCInstance.
 * @param eEnx ENC/ENH/ENL.
 * @param eENn ENX selection.
 * @param u32TimeoutLoops Wait timeout if transmission is busy.
 * @return
 */
MSC_ReturnType Msc_SwitchENXChannel(const MSC_InstanceType eInstance, Msc_ENxType eEnx, Msc_ENxActiveType eENn, uint32_t u32TimeoutLoops);

/**
 * @brief Switch the SDI Channel.
 * @param eInstance MSCInstance.
 * @param eSDIChannel SDI channel.
 * @param u32TimeoutLoops Wait timeout if receiving is busy.
 * @return
 */
MSC_ReturnType Msc_SwitchSDIChannel(const MSC_InstanceType eInstance, MSC_SDISelectionType eSDIChannel, uint32_t u32TimeoutLoops);

/** @}*/ /* fc7xxx_driver_msc. */
#endif
