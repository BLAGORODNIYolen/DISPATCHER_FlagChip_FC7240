/**
 * @file fc7xxx_driver_flexcan.h
 * @author Flagchip
 * @brief FC7xxx CAN driver type definition and API
 * @version 0.1.0
 * @date 2022-02-20
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Author           Descriptions
   *   ---------   ----------    ------------     ---------------
   *   0.1.0       2024-1-13    Flagchip0112      First version for FC7240
   ******************************************************************************** */

#ifndef _DRIVER_FC4XXX_DRIVER_FLEXCAN_H_
#define _DRIVER_FC4XXX_DRIVER_FLEXCAN_H_

#include "HwA_flexcan.h"


/* ################################################################################## */
/* ####################################### Macro #################################### */

#define FLEXCAN_CHECK_PARAMETERS      STD_ON


/* ################################################################################## */
/* ################################### Type define ################################## */

/**
 * @addtogroup fc7xxx_driver_can
 * @{
 */





/**
 * @brief FLEXCAN ID Type
 *
 */
typedef enum
{
    FLEXCAN_ID_STD = 0x00U,    /**< FLEXCAN_ID_STD standard id */
    FLEXCAN_ID_EXT = 0x01U     /**< FLEXCAN_ID_EXT extended id */
} FLEXCAN_IdType;

/**
 * @brief FLEXCAN Data Frame Type
 *
 */
typedef enum
{
    FLEXCAN_FRAME_DATA   = 0x00U,    /**< FLEXCAN_FRAME_DATA data frame     */
    FLEXCAN_FRAME_REMOTE = 0x01U     /**< FLEXCAN_FRAME_REMOTE remote frame */
} FLEXCAN_DataType;


/**
 * @brief FLEXCAN baud-rate clock source
 *
 */
typedef enum
{
    FLEXCAN_BAUDCLK_HZ_8M   = 8000000U,  /**< FLEXCAN_BAUDCLK_HZ_8M   8MHz clock source   */
    FLEXCAN_BAUDCLK_HZ_12M  = 12000000U, /**< FLEXCAN_BAUDCLK_HZ_12M  12MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_16M  = 16000000U, /**< FLEXCAN_BAUDCLK_HZ_16M  16MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_24M  = 24000000U, /**< FLEXCAN_BAUDCLK_HZ_24M  24MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_48M  = 48000000U, /**< FLEXCAN_BAUDCLK_HZ_48M  48MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_96M  = 96000000U, /**< FLEXCAN_BAUDCLK_HZ_96M  96MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_120M = 120000000U,/**< FLEXCAN_BAUDCLK_HZ_120M 120MHz clock source */
    FLEXCAN_BAUDCLK_HZ_150M = 150000000U /**< FLEXCAN_BAUDCLK_HZ_150M 150MHz clock source */
} FLEXCAN_BaudClkType;



/**
 * @brief FLEXCAN baud-rate source
 *
 */
typedef enum
{
    FLEXCAN_BAUD_100K = 100000U, /**< FLEXCAN_BAUD_100K normal bit 100Kbps */
    FLEXCAN_BAUD_125K = 125000U, /**< FLEXCAN_BAUD_100K normal bit 125Kbps */
    FLEXCAN_BAUD_250K = 250000U, /**< FLEXCAN_BAUD_250K normal bit 250Kbps */
    FLEXCAN_BAUD_500K = 500000U, /**< FLEXCAN_BAUD_500K normal bit 500Kbps */
    FLEXCAN_BAUD_800K = 800000U, /**< FLEXCAN_BAUD_500K normal bit 800Kbps */
    FLEXCAN_BAUD_1M   = 1000000U,/**< FLEXCAN_BAUD_1M   normal bit 1Mbps   */
    FLEXCAN_BAUD_2M   = 2000000U,/**< FLEXCAN_BAUD_2M   normal bit 2Mbps   */
    FLEXCAN_BAUD_3M   = 3000000U,/**< FLEXCAN_BAUD_3M   normal bit 3Mbps   */
    FLEXCAN_BAUD_4M   = 4000000U,/**< FLEXCAN_BAUD_4M   normal bit 4Mbps   */
    FLEXCAN_BAUD_5M   = 5000000U,/**< FLEXCAN_BAUD_5M   normal bit 5Mbps   */
    FLEXCAN_BAUD_6M   = 6000000U,/**< FLEXCAN_BAUD_6M   normal bit 6Mbps   */
    FLEXCAN_BAUD_8M   = 8000000U /**< FLEXCAN_BAUD_8M   normal bit 8Mbps   */
} FLEXCAN_BaudType;

/**
 * @brief FLEXCAN data length type
 *
 */
typedef enum
{
    FLEXCAN_DATAWIDTH_8  = 8U, /**< FLEXCAN_DATALEN_8  8 bytes data width  */
    FLEXCAN_DATAWIDTH_16 = 16U,/**< FLEXCAN_DATALEN_16 16 bytes data width */
    FLEXCAN_DATAWIDTH_32 = 32U,/**< FLEXCAN_DATALEN_32 32 bytes data width */
    FLEXCAN_DATAWIDTH_64 = 64U /**< FLEXCAN_DATALEN_64 64 bytes data width */

} FLEXCAN_DataWidthType;

/**
 * @brief FLEXCAN data length type
 *
 */
typedef enum
{
    FLEXCAN_DIR_DISABLE = 0U,               /**< FLEXCAN_DATALEN_8  8 bytes data width  */
    FLEXCAN_DIR_ENABLE_WITHOUT_TRIG = 1U,   /**< FLEXCAN_DATALEN_8  8 bytes data width  */
    FLEXCAN_DIR_ENABLE_WITH_TRIG = 3U       /**< FLEXCAN_DATALEN_8  8 bytes data width  */
} FLEXCAN_DirectType;

/**
  * @brief  FLEXCAN init structure definition
  */
typedef struct
{
    FLEXCAN_ClockSrcType   eClkSrcSel;               /**< Clock Source Select                                                                  */
    FLEXCAN_BaudClkType    eClkSrcHz;                /**< clock hz for baud-rate                                                               */
    uint8_t                bListenOnly;
    uint8_t                bEnFd;                    /**< enable FLEXCAN fd                                                                    */
    uint8_t                bEnBrs;                   /**< data bit baud-rate used                                                              */
    uint8_t                bEnRxFifo;                /**< Rx FIFO                                                                              */
    uint8_t                bEnDma;                   /**< The DMA feature FLEXCAN only be used in Rx FIFO                                      */
    uint8_t                u8EnhancedFifoDmaWM;      /**< The DMA watermark only work in CANFD FIFO mode, range 1- 12                          */
    FLEXCAN_BaudType       eBaudrate;                /**< normal baud-rate                                                                     */
    FLEXCAN_BaudType       eDataBaud;                /**< data baud-rate                                                                       */
    FLEXCAN_DataWidthType  eMbDataWidth;             /**< when bEnFd=0, only FLEXCAN be set 8; when bEnFd=1, FLEXCAN be set as 8/16/32/64      */
    FLEXCAN_DirectType     eDirect;                  /**<Enable Direct Connection for CAN Tx and Rx                                            */
} FLEXCAN_InitType;


/**
 * @brief Transmit Message Buffer Configuration
 *
 */
typedef struct
{
    FLEXCAN_IdType    eRxFrameType;  /**< FLEXCAN ID type, 0 STD, 1 EXT */
    uint32_t          u32TxCanId;    /**< FLEXCAN Transmit ID           */
} FLEXCAN_TxMbConfigType;

/**
 * @brief Receive Message Buffer Configuration
 *
 */
typedef struct
{
    FLEXCAN_IdType  eRxFrameType;   /**< FLEXCAN ID type, 0 STD, 1 EXT */
    uint32_t        u32RxCanId;     /**< FLEXCAN received ID           */
    uint32_t        u32RxCanIdMask; /**< FLEXCAN received ID mask, if mask bit is 1, received FLEXCAN id bit must same to u32RxCanId, or mask bit is 0, id bit is ignored */
} FLEXCAN_RxMbFilterType;


/**
  * @brief  FLEXCAN transmit message
  */
typedef struct
{
    uint8_t                 u8TxHandler;     /**< one message buffer used one handler, range 0 ~ txMbCnt-1     */
    uint8_t                 bWaitTxCompleted;/**< wait transmit complete and clear iflag                       */
    uint16_t                u16WaitTxTimeout;  /**< wait transmit complete timeout                               */
    uint8_t                 bEnFd;           /**< enable FLEXCAN fd                                            */
    uint8_t                 bEnBrs;          /**< enable canfd data bit switch                                 */
    uint32_t                u32CanId;        /**< FLEXCAN id                                                   */
    FLEXCAN_IdType          eFrameType;      /**< 0 STD, 1 EXT                                                 */
    FLEXCAN_DataType        eDataType;       /**< 0 Data, 1 remote                                             */
    uint32_t                u32DataLen;      /**< data length                                                  */
    uint8_t                 aData[64];       /**< data buffer                                                  */
} FLEXCAN_TxMsgType;


/**
  * @brief  FLEXCAN receive message
  */
typedef struct
{
    uint8_t             u8CanIndex;    /**< FLEXCAN Index, 0,1,2..NUM        */
    uint8_t             u8MbIndex;     /**< Mb Index, 0,1,2...31             */
    uint8_t             bEnFd;         /**< enable FLEXCAN fd                */
    uint8_t             bEnBrs;        /**< enable canfd data bit switch     */
    uint32_t            u32CanId;      /**< FLEXCAN id                       */
    FLEXCAN_IdType      eFrameType;    /**< 0 STD, 1 EXT                     */
    FLEXCAN_DataType    eDataType;     /**< 0 Data, 1 remote                 */
    uint32_t            u32DataLen;    /**< data length                      */
    uint8_t             aData[80];     /**< data buffer                      */

} FLEXCAN_RxMsgType;

/**
  * @brief  FLEXCAN polling receive message
  */
typedef struct
{
    uint8_t             u8RxMsgCnt;     /**< Receive Message Buffer Count    */
    FLEXCAN_RxMsgType   *pRxMsgBuf;     /**< Receive Message Buffer Address  */

} FLEXCAN_RxMsgListType;


/**
  * @brief  FLEXCAN rx config structure definition
  */
typedef struct
{
    FLEXCAN_RxMbFilterType   *pRxFilterFifoList;    /**< rx id list, occupy first n MB, one filter in one MB, or fifo                       */
    uint8_t                  u8RxFilterFifoCnt;     /**< rx id filter count, if set enhanced rx fifo, standard id number must multiple of 2 */
    FLEXCAN_RxMbFilterType   *pRxFilterMBList;    /**< rx id list, occupy first n MB, one filter in one MB, or fifo                       */
    uint8_t                  u8RxFilterMBCnt;     /**< rx id filter count, if set enhanced rx fifo, standard id number must multiple of 2 */
    uint8_t                  u8TxMsgCnt;         /**< tx occupy next n MB, every id occupy one MB                                        */

    FLEXCAN_RxMsgType        *pRxBuf;            /**< receive buffer address, length same to u8RxFilterCnt                               */

} FLEXCAN_MBConfigType;


typedef struct
{
	uint8_t u8Error_FLEXCAN_ESR1_BIT1ERR_FAST;
	uint8_t u8Error_FLEXCAN_ESR1_BIT0ERR_FAST;
	uint8_t u8Error_FLEXCAN_ESR1_CRCERR_FAST;
	uint8_t u8Error_FLEXCAN_ESR1_FRMERR_FAST;
	uint8_t u8Error_FLEXCAN_ESR1_STFERR_FAST;
	uint8_t u8Error_FLEXCAN_ESR1_ERROVR;
	uint8_t u8Error_FLEXCAN_ESR1_ERRINT_FAST;
	uint8_t u8Error_FLEXCAN_ESR1_BOFFDONEINT;
	uint8_t u8Error_FLEXCAN_ESR1_TWRNINT;
	uint8_t u8Error_FLEXCAN_ESR1_RWRNINT;
	uint8_t u8Error_FLEXCAN_ESR1_BIT1ERR;
	uint8_t u8Error_FLEXCAN_ESR1_BIT0ERR;
	uint8_t u8Error_FLEXCAN_ESR1_ACKERR;
	uint8_t u8Error_FLEXCAN_ESR1_CRCERR;
	uint8_t u8Error_FLEXCAN_ESR1_FRMERR;
	uint8_t u8Error_FLEXCAN_ESR1_STFERR;
	uint8_t u8Error_FLEXCAN_ESR1_TXWRN;
	uint8_t u8Error_FLEXCAN_ESR1_RXWRN;
	uint8_t u8Error_FLEXCAN_ESR1_FLTCONF;
	uint8_t u8Error_FLEXCAN_ESR1_BOFFINT;
	uint8_t u8Error_FLEXCAN_ESR1_ERRINT;
}FLEXCAN_ErrorDetailType;

/**
 * @brief FLEXCAN Error Information
 *
 */
typedef struct
{
    uint32_t             u32RxErrCnt_Fast;  /**< Receive Error Counter for fast bits      */
    uint32_t             u32RxErrCnt;       /**< Receive Error Counter                    */
    uint32_t             u32TxErrCnt_Fast;  /**< Transmit Error Counter for fast bits     */
    uint32_t             u32TxErrCnt;       /**< Transmit Error Counter                   */
    uint32_t             u32ErrorValue;     /**< Error Register ESR1 Value                */
    FLEXCAN_ErrorDetailType tErrorDetail;      /**< Detail error information for u32ErrorValue */
} FLEXCAN_ErrorInfoType;

/** Error callback function type */
typedef void (*FLEXCAN_ErrorInterruptCallBackType)(uint8_t u8CanIndex, FLEXCAN_ErrorInfoType *pErrorInfo);
/** transmit callback function type, u8TxHandler (0,1,2 and so on) */
typedef void (*FLEXCAN_TxInterruptCallBackType)(uint8_t u8CanIndex, uint8_t u8TxHandler);
/** Receive callback function type */
typedef void (*FLEXCAN_RxInterruptCallBackType)(uint8_t u8CanIndex, FLEXCAN_RxMsgType *pRxCfg);

/**
 * @brief FLEXCAN interrupt callback setting
 *
 */
typedef struct
{
    uint8_t                              bEnErrorInterrupt;    /**< enable error interrupt                      */
    FLEXCAN_ErrorInterruptCallBackType   pErrorNotify;         /**< error interrupt callback function address   */
    uint8_t                              bEnTxMBInterrupt;     /**< enable transmit interrupt                    */
    FLEXCAN_TxInterruptCallBackType      pTxMBNotify;          /**< transmit interrupt callback function address */
    uint8_t                              bEnRxMBInterrupt;     /**< enable message buffer receive interrupt      */
    FLEXCAN_RxInterruptCallBackType      pRxMBNotify;          /**< receive message buffer interrupt callback function address */
    uint8_t                              bEnRxFifoInterrupt;   /**< enable receive fifo interrupt                    */
    FLEXCAN_RxInterruptCallBackType      pRxFifoNotify;        /**< receive fifo interrupt callback function address */
} FLEXCAN_InterruptType;



/**
 * @brief FLEXCAN error status
 *
 */
typedef enum
{
    FLEXCAN_ERROR_OK                = 0x00U,      /**< FLEXCAN_ERROR_OK means no error                                      */

    FLEXCAN_ERROR_INVALID_VERSION   = 0x01U,      /**< FLEXCAN_ERROR_INVALID_VERSION means version is not same */
    FLEXCAN_ERROR_FAILED            = 0x02U,      /**< FLEXCAN_ERROR_FAILED means operation is failed                       */
    FLEXCAN_ERROR_INVALID_PARAM     = 0x04U,      /**< FLEXCAN_ERROR_INVALID_PARAM means parameters are invalid             */
    FLEXCAN_ERROR_INVALID_SIZE      = 0x08U,      /**< FLEXCAN_ERROR_INVALID_SIZE means size is invalid                     */
    FLEXCAN_ERROR_INVALID_SEQUENCE  = 0x10U,      /**< FLEXCAN_ERROR_INVALID_SEQUENCE means sequence is error               */
    FLEXCAN_ERROR_TIMEOUT           = 0x20U,      /**< FLEXCAN_ERROR_TIMEOUT means operation is timeout                     */
    FLEXCAN_ERROR_BUSY              = 0x40U,      /**< FLEXCAN_ERROR_BUSY means current mb is busy                          */
} FLEXCAN_ErrorTypeEnum;

/** FLEXCAN Error Type */
typedef uint8_t   FLEXCAN_ErrorType;


/* ################################################################################## */
/* ################################ Global Functions ################################ */



/**
 * @brief Initial FLEXCAN variables Memory
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 */

void FLEXCAN_InitMemory(uint8_t u8CanIndex);

/**
 * @brief Initial CAN
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pInitCfg  clock, baud-rate, canfd, data length and so on.
 * @return 0 is ok, others are not ok
 */
FLEXCAN_ErrorType FLEXCAN_Init(uint8_t u8CanIndex, const FLEXCAN_InitType *const pInitCfg);

/**
 * @brief De-initial can instance
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @return 0 is ok, others are not ok
 */
FLEXCAN_ErrorType FLEXCAN_DeInit(uint8_t u8CanIndex);


/**
 * @brief Configure can receive message box and id filter
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pRxMbCfg contains CAN Instance, Rx CAN ID and Mask
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_RxFilterConfig(uint8_t u8CanIndex, const FLEXCAN_MBConfigType *const pRxMbCfg);

/**
 * @brief Configure can interrupt
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pIntCfg Contians interrupt enable and call back function points
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_SetInterrupt(uint8_t u8CanIndex, const FLEXCAN_InterruptType *const pIntCfg);

/**
 * @brief Start can instance
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_Start(uint8_t u8CanIndex);

/**
 * @brief Stop can instance
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 */
FLEXCAN_ErrorType FLEXCAN_Stop(uint8_t u8CanIndex);

/**
 * @brief Transmit data, if tx disable, must call FLEXCAN_TransmitProcess after transmiting
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pTxMsg contains CAN instance, CAN ID, CAN FD and CAN data.
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_TransmitData(uint8_t u8CanIndex, const FLEXCAN_TxMsgType *const pTxMsg);

/**
 * @brief Process flag after transmit
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param u8Handler  Transmit Handler
 * @return 1 means process successfully and can transmit next time, 0 means no active flag, 0xff means out of range
 */
uint8_t FLEXCAN_TransmitProcess(uint8_t u8CanIndex, uint8_t u8TxHandler);

/**
 * @brief Abort transmit with special transmit handler
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param u8TxHandler Transmit handler
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_TransmitAbort(uint8_t u8CanIndex, uint8_t u8TxHandler);

/**
 * @brief Receive data when polling (not used when rx interrupt enabled)
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pRxBufList is FLEXCAN_RxMsgType type point point, and don't need to be initialed
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_Receive_Polling(uint8_t u8CanIndex, FLEXCAN_RxMsgListType *const pRxBufList);


/**
 * @brief Get can error
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pErrorInfo is error information
 * @return 0 is no error, others contains error
 */
FLEXCAN_ErrorType FLEXCAN_GetErrorInfo(uint8_t u8CanIndex, FLEXCAN_ErrorInfoType *const pErrorInfo);

/**
 * @brief Clear can error
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pErrorInfo is error information
 * @return 0 is no error, others contains error
 */
FLEXCAN_ErrorType FLEXCAN_ClrErrorInfo(uint8_t u8CanIndex, const FLEXCAN_ErrorInfoType *const pErrorInfo);


/**
 * @brief Transfer Data length to DLC
 *
 * @param u32DataLen data length
 * @return DLC
 */
uint32_t FLEXCAN_DataLenToDlc(uint32_t u32DataLen);

/**
 * @brief Transfer DLC to Data length
 *
 * @param u32Dlc DLC Data Length
 * @return
 */
uint32_t FLEXCAN_DlcToDataLen(uint32_t u32Dlc);

/**
 * @brief Can interrupt process
 *
 * @param u8CanIndex  Can Index, Must less than FLEXCAN_INSTANCE_COUNT
 */
void FLEXCAN_IRQHandler(uint8_t u8CanIndex);

/** @}*/

#endif
