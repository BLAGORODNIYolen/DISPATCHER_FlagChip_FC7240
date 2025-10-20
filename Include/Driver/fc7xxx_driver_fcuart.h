/**
 * @file fc7xxx_driver_fcuart.h
 * @author Flagchip
 * @brief FC7xxx FCUart driver type definition and API
 * @version 0.1.0
 * @date 2024-01-10
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */

/********************************************************************************
 *   Revision History:
 *
 *   Version     Date          Initials       CR#          Descriptions
 *   ---------   ----------    ------------   ----------   ---------------
 *   0.1.0      2024-01-10    Flagchip0122     N/A          FC7xxx internal release version
 ********************************************************************************/


#ifndef _DRIVER_FC7XXX_DRIVER_FCUART_H_
#define _DRIVER_FC7XXX_DRIVER_FCUART_H_


#include "HwA_fcuart.h"

/**
 * @addtogroup fc7xxx_driver_fcuart
 * @{
 */

/********* Macro ************/
#define FCUART_FIFO_DEPTH          16U

#define ESCAPE_CHARACTER   (char)0x5c
#define ENTER              (uint8_t)0x0d
#define NEW_LINE           (uint8_t)0x0a
#define SPACE              (uint8_t)0x20
#define FLOAT_ZERO         0.00000001


/********* Local typedef ************/
/**
 * @brief FCUART error status
 *
 */
typedef enum
{
    FCUART_ERROR_OK               = 0x00U,    /**< FCUART_ERROR_OK means no error                                      */
    FCUART_ERROR_INVALID_VERSION  = 0x01U,    /**< FCUART_ERROR_INVALID_VERSION means version is not same */
    FCUART_ERROR_FAILED           = 0x02U,    /**< FCUART_ERROR_FAILED means operation is failed                       */
    FCUART_ERROR_INVALID_PARAM    = 0x04U,    /**< FCUART_ERROR_INVALID_PARAM means parameters are invalid             */
    FCUART_ERROR_INVALID_SIZE     = 0x08U,    /**< FCUART_ERROR_INVALID_SIZE means size is invalid                     */
    FCUART_ERROR_INVALID_SEQUENCE = 0x10U,    /**< FCUART_ERROR_INVALID_SEQUENCE means sequence is error               */
    FCUART_ERROR_TIMEOUT          = 0x20U,    /**< FCUART_ERROR_TIMEOUT means operation is timeout                     */
}FCUART_ErrorTypeEnum;

/**
 * @brief UART fifo receive idle character number
 */
typedef enum
{
    FCUART_FIFO_RX_IDLE_DISABLE = 0U,
    FCUART_FIFO_RX_IDLE_CHARACTER_1,
    FCUART_FIFO_RX_IDLE_CHARACTER_2,
    FCUART_FIFO_RX_IDLE_CHARACTER_4,
    FCUART_FIFO_RX_IDLE_CHARACTER_8,
    FCUART_FIFO_RX_IDLE_CHARACTER_16,
    FCUART_FIFO_RX_IDLE_CHARACTER_32,
    FCUART_FIFO_RX_IDLE_CHARACTER_64
} FCUART_Fifo_RxIdleCharNumType;


/**
 * @brief UART CTRL register interrupt
 *
 */
typedef enum
{
    FCUART_INT_CTRL_ORIE = FCUART_CTRL_ORIE_MASK,
    FCUART_INT_CTRL_NEIE = FCUART_CTRL_NEIE_MASK,
    FCUART_INT_CTRL_FEIE = FCUART_CTRL_FEIE_MASK,
    FCUART_INT_CTRL_PEIE = FCUART_CTRL_PEIE_MASK,
    FCUART_INT_CTRL_TIE  = FCUART_CTRL_TIE_MASK,
    FCUART_INT_CTRL_TCIE = FCUART_CTRL_TCIE_MASK,
    FCUART_INT_CTRL_RIE  = FCUART_CTRL_RIE_MASK,
    FCUART_INT_CTRL_IIE  = FCUART_CTRL_IIE_MASK,
    FCUART_INT_CTRL_TE   = FCUART_CTRL_TE_MASK,
    FCUART_INT_CTRL_RE   = FCUART_CTRL_RE_MASK,
    FCUART_INT_CTRL_M0IE = FCUART_CTRL_M0IE_MASK,
    FCUART_INT_CTRL_M1IE = FCUART_CTRL_M1IE_MASK
} FCUART_InterruptSel;

/**
 * @brief UART error status type
 *
 */
typedef enum
{
    FCUART_ERROR_NONE = 0x0000U,   /**< FCUART_ERROR_NONE    No Error,                            */
    FCUART_ERROR_RORF = 0x0001U,   /**< FCUART_ERROR_RORF    Receiver Overrun Flag,               */
    FCUART_ERROR_NF   = 0x0002U,   /**< FCUART_ERROR_NF      Noise Flag,                          */
    FCUART_ERROR_FEF  = 0x0004U,   /**< FCUART_ERROR_FEF     Frame Error Flag,                    */
    FCUART_ERROR_PEF  = 0x0008U,   /**< FCUART_ERROR_PEF     Parity Error Flag,                   */
    FCUART_ERROR_RPEF = 0x0010U,   /**< FCUART_ERROR_RPEF    Receive Data Parity Error Flag,      */
    FCUART_ERROR_TPEF = 0x0020U    /**< FCUART_ERROR_TPEF    Transmit Data Parity Error Flag,     */
}FCUART_ErrorStatusType;

/**
 * @brief UART idle character number
 */
typedef enum
{
    FCUART_IDLE_CHARCTER_1  = 0U,
    FCUART_IDLE_CHARCTER_2,
    FCUART_IDLE_CHARCTER_4,
    FCUART_IDLE_CHARCTER_8,
    FCUART_IDLE_CHARCTER_16,
    FCUART_IDLE_CHARCTER_32,
    FCUART_IDLE_CHARCTER_64,
    FCUART_IDLE_CHARCTER_128
} FCUART_IdleCharNumType;

/**
 * @brief UART idle type
 */
typedef enum
{
    FCUART_START_AFTER_STARTBIT = 0U,
    FCUART_START_AFTER_STOPBIT
} FCUART_IdleStartType;

/**
 * @brief UART initial data define
 *
 */
typedef struct
{
    uint32_t                       u32ClkSrcHz;        /**< module clock hz                                         */
    FCUART_BitModeType             eBitMode;           /**< 8bits or 9bits                                          */
    bool                           bParityEnable;      /**< Parity Enable=1                                         */
    FCUART_ParityType              eParityType;        /**< parity type                                             */
    FCUART_StopBitNumType          eStopBit;           /**< stop bit num;                                           */
    bool                           bEnTxFifo;          /**< Enable Tx FIFO, 16 data words depth                     */
    uint8_t                        u8TxFifoWaterMark;  /**< Tx FIFO,When FIFO/buffer number equal or less than this
                                                            an interrupt or a DMA request will be generated         */
    bool                           bEnRxFifo;          /**< Enable Rx FIFO, 16 data words depth                     */
    uint8_t                        u8RxFifoWaterMark;  /**< Rx FIFO, When FIFO/buffer number greater than this
                                                            an interrupt or a DMA request will be generated         */
    FCUART_Fifo_RxIdleCharNumType  eFifoRxIdleCharNum; /**< Fifo Rx idle character number   */
    bool                           bEnTxEmptyDma;      /**< Enable transmit DMA                                     */
    bool                           bEnRxFullDma;       /**< Enable receiver full DMA                                */
    bool                           bEnRxIdleDma;       /**< Enable Rx Idle DMA                                      */
    FCUART_IdleCharNumType         eIdleCharNum;       /**< Idle character number                                   */
    FCUART_IdleStartType           eIdleStart;         /**< Idle character start type                               */
    uint32_t                       u32Baudrate;        /**< normal baud-rate                                        */
    uint32_t                       u32TransmitTimeout; /**< transmit timeout tick, default 3000U                    */
} FCUART_InitType;

/**
 * @brief UART transmit and receive data define
 *
 */
typedef struct
{
    uint8_t*            pDatas;       /**< Data buffer point, Must be initial with a array address */
    uint32_t            u32DataLen;    /**< data length                                             */
}FCUART_DataType;

/** Error call back function type, errors are combine with FCUART_ErrorStatusType */
typedef void (*FCUART_ErrorInterrupt_CallBackType)(uint8_t u8UartIndex, uint32_t u32Error);

/** Transmit/Receive call back function type */
typedef void (*FCUART_TxRxInterrupt_CallBackType)(uint8_t u8UartIndex, FCUART_DataType *pTxRxCfg);

/** Idle call back function type */
typedef void (*FCUART_IdleInterrupt_CallBackType)(uint8_t u8UartIndex);

/**
 * @brief UART callback functions data define
 *
 */
typedef struct
{
    bool                                bEnErrorInterrupt;  /**< enable error interrupt                      */
    FCUART_ErrorInterrupt_CallBackType  pErrorNotify;       /**< error interrupt callback function address   */
    bool                                bEnRxInterrupt;     /**< enable receive interrupt                    */
    FCUART_DataType                     *pRxBuf;            /**< receive interrupt message buffer            */
    FCUART_TxRxInterrupt_CallBackType   pRxNotify;          /**< receive interrupt callback function address */
    bool                                bEnTxInterrupt;     /**< enable receive interrupt                    */
    FCUART_DataType                     *pTxBuf;            /**< transfer interrupt message buffer            */
    FCUART_TxRxInterrupt_CallBackType   pTxEmptyNotify;     /**< transfer empty interrupt callback function address */
    FCUART_TxRxInterrupt_CallBackType   pTxCompleteNotify;  /**< transfer complete interrupt callback function address */
    bool                                bEnIdleInterrupt;   /**< enable idle interrupt */
    FCUART_IdleInterrupt_CallBackType   pIdleNotify;        /**< idle interrupt callback function address */
} FCUART_InterruptType;

/**
 * @brief UART WakeUp functions data define
 *
 */
typedef struct
{
    bool     bEnWakeup;          /**< enable wake-up   */
    uint32_t  u32WakeUpData;      /**< wake-up data  */

} FCUART_WakeupType;



/** Errortype Define as uint8 */
typedef uint8_t  FCUART_ErrorType;

/* ################################################################################## */
/* ########################### Global Prototype Functions ########################### */


/**
 * @brief Initial UART variables Memory
 *
 */
void FCUART_InitMemory(uint8_t u8UartIndex);

/**
 * @brief This Function is used to initial UART instance
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pInitCfg contains clock, baud-rate, Bit Mode, parity and so on.
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Init(uint8_t u8UartIndex, FCUART_InitType *pInitCfg);

/**
 * @brief This Function is used to de-initial UART instance
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_DeInit(uint8_t u8UartIndex);

/**
 * @brief This Function is used to set UART interrupt
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pInterruptCfg contains callback functions
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_SetInterrupt(uint8_t u8UartIndex, FCUART_InterruptType *pInterruptCfg);

/**
 * @brief This Function is used to set UART WakeUp
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pWakeupCfg contains UART wake-up parameters
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_SetWakeup(uint8_t u8UartIndex, FCUART_WakeupType *pWakeupCfg);

/**
 * @brief This Function is used to start receiving
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_StartReceive(uint8_t u8UartIndex);

/**
 * @brief This Function is used to stop receiving
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_StopReceive(uint8_t u8UartIndex);

/**
 * @brief This Function is used to start transmit
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_StartTransmit(uint8_t u8UartIndex);

/**
 * @brief This Function is used to stop transmitting
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_StopTransmit(uint8_t u8UartIndex);

/**
 * @brief This Function is used to transmit UART data
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pUartData contains UART data and length
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Transmit(uint8_t u8UartIndex, FCUART_DataType *pUartData);


/**
 * @brief This Function is used to print ASCII char from UART
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param fmt is char format
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Printf(uint8_t u8UartIndex, char* fmt,...);

/**
 * @brief Get Stat Flag
 *
 * @param u8UartIndex  UART instance
 * @param eStatusType  stat type
 * @return FCUART STAT status flag
 */
uint32_t FCUART_GetStatus(uint8_t u8UartIndex, FCUART_StatType eStatusType);

/**
 * @brief This Function is used to receive data when polling (not used when rx interrupt enabled)
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pRxMsg is data buffer address, and pDatas need to be initialed with external buffer
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Receive_Polling(uint8_t u8UartIndex, FCUART_DataType *pRxMsg);


/**
 * @brief This Function is used to get error when polling (not used when error interrupt enabled)
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pErrorValue is error value
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Error_Polling(uint8_t u8UartIndex, uint32_t *pErrorValue);

/**
 * @brief This Function is used to enable fcuart loop mode
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param bStatus  enable/disable status of loop mode
 * @return FCUART_ERROR_OK is ok, others are not ok
 *
 */
FCUART_ErrorType FCUART_SetLoopMode(uint8_t u8UartIndex, bool bStatus);

/**
 * @brief This Function is used to deal with FCUART TxRx interrupt
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 *
 */
void FCUARTN_RxTx_IRQHandler(uint8_t u8UartIndex);

/**
 * @brief This Function is used to send 9 bits data
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param u16Data  data to send
 * @return FCUART_ERROR_OK is ok, others are not ok
 *
 */
FCUART_ErrorType FCUART_SendData_9Bits(uint8_t u8UartIndex, uint16_t u16Data);

/**
 * @brief This Function is used to Get 9 bits data
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pData  pointer to data
 * @return FCUART_ERROR_OK is ok, others are not ok
 *
 */
FCUART_ErrorType FCUART_GetData_9Bits(uint8_t u8UartIndex, uint16_t *pData);

/**
 * @brief This Function is used to send 10 bits data
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param u16Data  data to send
 * @return FCUART_ERROR_OK is ok, others are not ok
 *
 */
FCUART_ErrorType FCUART_SendData_10Bits(uint8_t u8UartIndex, uint16_t u16Data);

/**
 * @brief This Function is used to Get 10 bits data
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pData  pointer to data
 * @return FCUART_ERROR_OK is ok, others are not ok
 *
 */
FCUART_ErrorType FCUART_GetData_10Bits(uint8_t u8UartIndex, uint16_t *pData);

/**
 * @brief This Function is used to set bit mode,parity and stop bit
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pData  pointer to data
 * @return FCUART_ERROR_OK is ok, others are not ok
 *
 */
FCUART_ErrorType FCUART_SetBitModeAndParity( uint8_t               u8UartIndex,
                                            FCUART_BitModeType    eBitMode,
                                            FCUART_StopBitNumType eStopBit,
                                            FCUART_ParityType     eParityType,
                                            bool                  bParityEnable
                                            );

/**
 * @brief This Function is used to Get current interrupt mode
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param u32Data  Interrupt type to get
 * @return true/false
 *
 */
bool FCUART_GetInterruptMode(uint8_t u8UartIndex, uint32_t u32Data);

/**
 * @brief This Function is used to assign data to send through interrupt
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pData  data pointer
 * @param u32Length data length to send
 * @return FCUART_ERROR_OK is ok, others are not ok
 *
 */
FCUART_ErrorType FCUART_AssignTxInterruptData(uint8_t u8UartIndex, uint8_t * pData, uint32_t u32Length);

/** @}*/

#endif
