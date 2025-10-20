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



#include "fc7xxx_driver_flexcan.h"    /* include peripheral declarations */

#include "interrupt_manager.h"


/* ################################################################################## */
/* ####################################### Macro #################################### */


#ifndef NULL
    #define NULL ((void *)0)
#endif

#define FLEXCAN_FD_INSTANCE_COUNT        FLEXCAN_INSTANCE_COUNT    /** all support can fd      */

#define FLEXCAN_MB_NUM                   32U   /** Every CAN contains message buffer number */


#define FLEXCAN_RX_FIFO_ENABLE       STD_OFF
#define FLEXCAN_DMA_ENABLE           STD_OFF

#define FLEXCAN_DET_ERROR_REPORT     STD_OFF


#define FLEXCAN_DET_ERROR_ID_FUNC_INIT                 0x01U
#define FLEXCAN_DET_ERROR_ID_FUNC_MSGCFG               0x02U
#define FLEXCAN_DET_ERROR_ID_FUNC_SETINTERRUPT         0x03U
#define FLEXCAN_DET_ERROR_ID_FUNC_START                0x04U
#define FLEXCAN_DET_ERROR_ID_FUNC_STOP                 0x05U
#define FLEXCAN_DET_ERROR_ID_FUNC_TRANSMIT             0x06U
#define FLEXCAN_DET_ERROR_ID_FUNC_RECEIVE              0x07U


#define FLEXCAN_DET_ERROR_ID_PARAM_POINTCHECK          0x01U
#define FLEXCAN_DET_ERROR_ID_PARAM_INDEXCHECK          0x02U



/* register word num */
#define FLEXCAN_MEM_WORD_LEN      0x04U


#define MB_RAM_OFFSET         0x80U
#define RXIMR_OFFSET          0x880U
#define RXFIR_TEST_OFFSET     0xA80U
#define MASK_OFFSET           0xAA0U
#define SMBTX_OFFSET          0xAB0U
#define SMBRX0_OFFSET         0xAC0U
#define SMBRX1_OFFSET         0xAD0U
#define FD_SMBTX_OFFSET       0xF28U
#define FD_SMBRX0_OFFSET      0xF70U
#define FD_SMBRX1_OFFSET      0xFB8U
#define ERX_FIFO_OFFSET       0x2000U
#define ERFFEL_OFFSET         0x3000U


#define MB_RAM_WORD_NUM       128U
#define RXIMR_WORD_NUM        32U
#define RXFIR_TEST_WORD_NUM   8U
#define MASK_WORD_NUM         4U
#define SMBTX_WORD_NUM        4U
#define SMBRX0_WORD_NUM       4U
#define SMBRX1_WORD_NUM       4U
#define FD_SMBTX_WORD_NUM     18U
#define FD_SMBRX0_WORD_NUM    18U
#define FD_SMBRX1_WORD_NUM    18U
#define ERX_FIFO_WORD_NUM     240U
#define ERFFEL_WORD_NUM       32U



#define USE_CBT_NORMAL



#define TQ_NUM_IPT                  2U

#define TQ_SYNC_NUM                 1U

/* Ctrl1 */
#define TQ_NUM_CTRL1_MAX            25U
#define TQ_NUM_CTRL1_MIN            8U

#define CTRL1_PRESDIV_MAX           256U
#define CTRL1_PRESDIV_MIN           1U

#define CTRL1_RJW_MAX               4U
#define CTRL1_RJW_MIN               1U

#define CTRL1_PROPSEG_MAX           8U
#define CTRL1_PROPSEG_MIN           1U

#define CTRL1_PSEG1_MAX             8U
#define CTRL1_PSEG1_MIN             1U

#define CTRL1_TIMERSEGMENT1_MAX     16U
#define CTRL1_TIMERSEGMENT1_MIN     2U

#define CTRL1_PSEG2_MAX             8U
#define CTRL1_PSEG2_MIN             2U


/* CBT */
#define TQ_NUM_CBT_MAX              25U /* 80U */
#define TQ_NUM_CBT_MIN              8U

#define CBT_PRESDIV_MAX             1024U
#define CBT_PRESDIV_MIN             1U

#define CBT_RJW_MAX                 32U
#define CBT_RJW_MIN                 1U

#define CBT_PROPSEG_MAX             64U
#define CBT_PROPSEG_MIN             1U

#define CBT_PSEG1_MAX               32U
#define CBT_PSEG1_MIN               1U

#define CBT_TIMERSEGMENT1_MAX       96U
#define CBT_TIMERSEGMENT1_MIN       2U

#define CBT_PSEG2_MAX               32U
#define CBT_PSEG2_MIN               2U


/* FDCBT */
#define TQ_NUM_FDCBT_MAX            25U
#define TQ_NUM_FDCBT_MIN            5U

#define FDCBT_PRESDIV_MAX           1024U
#define FDCBT_PRESDIV_MIN           1U

#define FDCBT_RJW_MAX               8U
#define FDCBT_RJW_MIN               1U

#define FDCBT_PROPSEG_MAX           31U
#define FDCBT_PROPSEG_MIN           0U

#define FDCBT_PSEG1_MAX             8U
#define FDCBT_PSEG1_MIN             1U

#define FDCBT_TIMERSEGMENT1_MAX     39U
#define FDCBT_TIMERSEGMENT1_MIN     2U

#define FDCBT_PSEG2_MAX             8U
#define FDCBT_PSEG2_MIN             2U



/* ################################################################################## */
/* ################################### Type define ################################## */







typedef enum
{
    /* RXIDA=0: bitIDE=29-19,EXT=29-1; */
    RXFIFO_FILTERFORMATA = 0,
    /* RXIDB_0: bitIDE=29-19,EXT=29-16; RXIDB_1: bitIDE=13-3,EXT=13-0; */
    RXFIFO_FILTERFORMATB = 1,
    /* RXIDC_0: bitIDE/EXT=31-24; RXIDC_1: bitIDE/EXT=23-16; RXIDC_2: bitIDE/EXT=15-8; RXIDC_3: bitIDE/EXT=7-0 */
    RXFIFO_FILTERFORMATC = 2

} FLEXCAN_RxFifoFilterFormatType;

typedef struct
{
    FLEXCAN_RxFifoFilterFormatType     eFilterFormat;
    uint32_t                           u32RxElementNum;
    uint32_t                           *pRxElementList;
} FLEXCAN_RxFifoFilterType;



/**
 * @brief CAN Baudrate setting
 *
 */
typedef struct
{
    uint8_t               bEnFd;        /**< if enable can FD, set 1U     */
    uint8_t               bEnBrs;       /**< if enable can BRS, set 1U    */
    FLEXCAN_DataWidthType eMbDataWidth; /**< Message Buffer Data Width    */

    FLEXCAN_BaudClkType   eClkSrcHz;    /**< clock source HZ              */
    FLEXCAN_BaudType      eBaudrate;    /**< normal bit rate              */
    FLEXCAN_BaudType      eDataBaud;    /**< can fd data bit rate         */

    uint32_t              u32Ctrl1;     /**< ctrl1 register value         */
    uint32_t              u32Cbt;       /**< cbt register value           */
    uint32_t              u32FdCtrl;    /**< fdctrl register value        */
    uint32_t              u32FdCbt;     /**< fdcbt register value         */

} FLEXCAN_BaudCfgType;



/**
 * @brief CAN setting configuration
 *
 */
typedef struct
{
    uint8_t                  bEnableFd;         /**< if enable can FD, set 1U                                                 */
    uint8_t                  bEnableFifo;       /**< if enable can fifo, set 1U                                               */
    uint8_t                  bEnableDMA;        /**< if enable can dma, set 1U                                                */
    uint8_t                  bEnableErrInt;     /**< if enable can error interrupt, set 1U                                    */
    uint8_t                  bEnableFifoInt;    /**< if enable can fifo interrupt, set 1U                                     */
    uint8_t                  bEnableTxMBInt;    /**< if enable can Tx MB interrupt, set 1U                                    */
    uint8_t                  bEnableRxMBInt;    /**< if enable can Rx MB interrupt, set 1U                                    */
    uint8_t                  u8EnhancedFifoDmaWM;/**< The watermark for DMA in CANFD FIFO mode                                 */
    uint8_t                  u8RxFifoCnt;       /**< can receive start message buffer index                                    */
    uint8_t                  u8RxMbStart1;      /**< can receive start message buffer index                                   */
    uint8_t                  u8RxMbCnt1;        /**< can receive message buffer count                                         */
    uint8_t                  u8TxMbStart1;      /**< can transmit start message buffer index                                  */
    uint8_t                  u8TxMbCnt1;        /**< can receive message buffer count                                         */
    FLEXCAN_DataWidthType    eMbDataWidth;      /**< Message Buffer Data Width                                              */
    FLEXCAN_RxMsgType        *pRxBuf;           /**< receive buffer address, length same to u8RxFilterCnt, must global array  */
} FLEXCAN_SettingType;

/**
 * @brief CAN Operation Sequence
 *
 */
typedef enum
{
    FLEXCAN_SEQUENCE_VAR_NOINIT,              /**< FLEXCAN_SEQUENCE_DEINIT means CAN variables data is not initialed                      */
    FLEXCAN_SEQUENCE_DEINIT,                  /**< FLEXCAN_SEQUENCE_DEINIT means CAN driver is not initialed                              */
    FLEXCAN_SEQUENCE_NOTSTART,                /**< FLEXCAN_SEQUENCE_NOTSTART means can driver initialed and not start */
    FLEXCAN_SEQUENCE_STARTED                  /**< FLEXCAN_SEQUENCE_STARTED means can driver started                        */
} FLEXCAN_SequenceType;


/**
 * @brief Baud-rate clock and divider
 *
 */
typedef struct
{
    FLEXCAN_BaudClkType  eClkHz;      /**< Clock Hz for baudrate             */
    FLEXCAN_BaudType     eBaudrate;   /**< Normal bit baudrate               */
    uint32_t             u32Presdiv;  /**< Presdiv for can                   */
    uint32_t             u32Propseg;  /**< Propseg for can                   */
    uint32_t             u32Pseg1;    /**< Pseg1 for can                     */
    uint32_t             u32Pseg2;    /**< Pseg2 for can                     */
    uint32_t             u32Rjw;      /**< RJW for can                       */
} FLEXCAN_BaudRegType;


/* ################################################################################## */
/* ############################# Local Const Variables ############################## */

/* CAN Instance */
static FLEXCAN_Type *const s_aFlexCan_InstanceTable[FLEXCAN_INSTANCE_COUNT] =
{
    FLEXCAN0,
    FLEXCAN1,
    FLEXCAN2,
    FLEXCAN3
};

/* Normal bit table */
static const FLEXCAN_BaudRegType s_aFlexCan_NormalBaudDividerTable[] =
{
    /* clock source hz          baudrate             presdiv    propseg   pseg1   pseg2   rjw  */
    { FLEXCAN_BAUDCLK_HZ_16M,   FLEXCAN_BAUD_500K,   2,         8,        4,      3,      2  },
    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_100K,   12,        7,        6,      6,      1  },
    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_125K,   12,        5,        5,      5,      1  },
    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_250K,   8,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_500K,   4,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_800K,   3,         5,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_1M,     2,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_2M,     1,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_100K,   32,        8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_125K,   24,        7,        4,      4,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_250K,   24,        3,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_500K,   6,         7,        4,      4,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_800K,   4,         8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_1M,     3,         7,        4,      4,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_2M,     2,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_100K,   80,        8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_125K,   64,        8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_250K,   32,        8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_500K,   16,        8,        3,      3,      3  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_800K,   15,        5,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_1M,     8,         8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_2M,     4,         8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_150M,  FLEXCAN_BAUD_500K,   20,        8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_150M,  FLEXCAN_BAUD_1M,     10,        8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_150M,  FLEXCAN_BAUD_2M,     5,         8,        3,      3,      1  },

};

/* Data bit table */
static const FLEXCAN_BaudRegType s_aFlexCan_DataBaudDividerTable[] =
{
    /* clock source hz          baudrate             presdiv    propseg   pseg1   pseg2   rjw  */
    { FLEXCAN_BAUDCLK_HZ_16M,   FLEXCAN_BAUD_2M,     1,         3,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_1M,     2,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_2M,     1,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_3M,     1,         3,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_1M,     3,         7,        4,      4,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_2M,     2,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_3M,     1,         7,        4,      4,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_4M,     1,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_6M,     1,         3,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_1M,     8,         8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_2M,     4,         8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_3M,     4,         5,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_4M,     3,         5,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_5M,     2,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_6M,     2,         5,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_8M,     1,         8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_150M,  FLEXCAN_BAUD_1M,     10,        8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_150M,  FLEXCAN_BAUD_2M,     5,         8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_150M,  FLEXCAN_BAUD_3M,     5,         5,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_150M,  FLEXCAN_BAUD_5M,     2,         8,        3,      3,      1  }

};


/* ################################################################################## */
/* ################################ Local Variables ################################# */


/* sequence var */
static FLEXCAN_SequenceType s_aCurrentSequence[FLEXCAN_INSTANCE_COUNT] = {FLEXCAN_SEQUENCE_VAR_NOINIT};


/* message buffer word length, default pCan is 16bytes, 4words */
/* static uint8_t s_aFlexCan_DataLen[FLEXCAN_INSTANCE_COUNT]; */

/* pCan message buffer used count stored */
/* static FLEXCAN_MBConfigType s_aFlexCan_MBCfg_Table[FLEXCAN_INSTANCE_COUNT]; */

/* can setting */
static FLEXCAN_SettingType  s_aFlexCan_Setting_Table[FLEXCAN_INSTANCE_COUNT];


/* store notify callback function point */
static FLEXCAN_ErrorInterruptCallBackType   s_aFlexCan_ErrorNotifyTable[FLEXCAN_INSTANCE_COUNT];
static FLEXCAN_TxInterruptCallBackType      s_aFlexCan_TxNotifyTable[FLEXCAN_INSTANCE_COUNT];
static FLEXCAN_RxInterruptCallBackType      s_aFlexCan_RxNotifyTable[FLEXCAN_INSTANCE_COUNT];
static FLEXCAN_RxInterruptCallBackType      s_aFlexCan_RxFifoNotifyTable[FLEXCAN_INSTANCE_COUNT];

/* check every pCan instance whether is used */
/* static FLEXCAN_RxMsgType const * s_aFlexCan_RxBufList[FLEXCAN_INSTANCE_COUNT]; */

/* check every pCan instance whether is used */
static uint8_t s_aFlexCan_CanUsed[FLEXCAN_INSTANCE_COUNT];

#if FLEXCAN_DET_ERROR_REPORT == STD_ON
typedef struct
{
    uint8_t   u8FunctionID;
    uint8_t   u8ParameterID;
} FLEXCAN_DetErrorType;

static FLEXCAN_DetErrorType s_tFlexCan_DetErrorId;
#endif


/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */




/* ################################################################################## */
/* ########################### Global Prototype Functions ########################### */


/* ################################################################################## */
/* ################################ Local Functions ################################# */

#if FLEXCAN_DET_ERROR_REPORT == STD_ON
static void FLEXCAN_ReportDet(uint8_t funcId, uint8_t paramId)
{
    s_tFlexCan_DetErrorId.u8FunctionID = funcId;
    s_tFlexCan_DetErrorId.u8ParameterID = paramId;

    while (1)
    {

    }

}

#endif


#if FLEXCAN_CHECK_PARAMETERS == STD_ON
/**
 * @brief Check FLEXCAN instance
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @return FLEXCAN_ERROR_OK is OK
 */
LOCAL_INLINE FLEXCAN_ErrorType FLEXCAN_LL_CheckInstance(uint8_t u8CanIndex)
{
    FLEXCAN_ErrorType tRetVal;

    if (u8CanIndex < FLEXCAN_INSTANCE_COUNT)
    {
        tRetVal = FLEXCAN_ERROR_OK;
    }
    else
    {
        tRetVal = FLEXCAN_ERROR_INVALID_PARAM;
    }

    return tRetVal;
}

#endif

/**
 * @brief Check FLEXCAN Fd Support instance
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @return FLEXCAN_ERROR_OK is OK
 */
LOCAL_INLINE FLEXCAN_ErrorType FLEXCAN_LL_CheckFdInstance(uint8_t u8CanIndex)
{
    FLEXCAN_ErrorType tRetVal;

    if (u8CanIndex < FLEXCAN_FD_INSTANCE_COUNT)
    {
        tRetVal = FLEXCAN_ERROR_OK;
    }
    else
    {
        tRetVal = FLEXCAN_ERROR_INVALID_PARAM;
    }

    return tRetVal;
}


/**
 * @brief Initial embedded can ram area
 *
 * @param u8CanIndex CanIndex, Must less than FLEXCAN_INSTANCE_COUNT
 */
static void FLEXCAN_LL_EmbededRam_Init(uint8_t u8CanIndex)
{
    volatile uint32_t u8Index ;
    volatile uint32_t ramAddr;
    FLEXCAN_Type *pCan;

    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

    for (u8Index = 0U; u8Index < MB_RAM_WORD_NUM; u8Index++)
    {
        ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, MB_RAM_OFFSET, u8Index * FLEXCAN_MEM_WORD_LEN);
        FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
    }

    for (u8Index = 0U; u8Index < RXIMR_WORD_NUM; u8Index++)
    {
        ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, RXIMR_OFFSET, u8Index * FLEXCAN_MEM_WORD_LEN);
        FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
    }

    for (u8Index = 0U; u8Index < RXFIR_TEST_WORD_NUM; u8Index++)
    {
        ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, RXFIR_TEST_OFFSET, u8Index * FLEXCAN_MEM_WORD_LEN);
        FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
    }

    for (u8Index = 0U; u8Index < MASK_WORD_NUM; u8Index++)
    {
        ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, MASK_OFFSET, u8Index * FLEXCAN_MEM_WORD_LEN);
        FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
    }
    for (u8Index = 0U; u8Index < SMBTX_WORD_NUM; u8Index++)
    {
        ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, SMBTX_OFFSET, u8Index * FLEXCAN_MEM_WORD_LEN);
        FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
    }

    for (u8Index = 0U; u8Index < SMBRX0_WORD_NUM; u8Index++)
    {
        ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, SMBRX0_OFFSET, u8Index * FLEXCAN_MEM_WORD_LEN);
        FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
    }

    for (u8Index = 0U; u8Index < SMBRX1_WORD_NUM; u8Index++)
    {
        ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, SMBRX1_OFFSET, u8Index * FLEXCAN_MEM_WORD_LEN);
        FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
    }

    /* can fd only */
    if (FLEXCAN_LL_CheckFdInstance(u8CanIndex) == FLEXCAN_ERROR_OK)
    {
        for (u8Index = 0U; u8Index < FD_SMBTX_WORD_NUM; u8Index++)
        {
            ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FD_SMBTX_OFFSET, u8Index * FLEXCAN_MEM_WORD_LEN);
            FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
        }

        for (u8Index = 0U; u8Index < FD_SMBRX0_WORD_NUM; u8Index++)
        {
            ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FD_SMBRX0_OFFSET, u8Index * FLEXCAN_MEM_WORD_LEN);
            FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
        }

        for (u8Index = 0U; u8Index < FD_SMBRX1_WORD_NUM; u8Index++)
        {
            ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FD_SMBRX1_OFFSET, u8Index * FLEXCAN_MEM_WORD_LEN);
            FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
        }


        /** initial rx fifo */
        for (u8Index = 0U; u8Index < ERX_FIFO_WORD_NUM; u8Index++)
        {
            ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, ERX_FIFO_OFFSET, u8Index * FLEXCAN_MEM_WORD_LEN);
            FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
        }

        for (u8Index = 0U; u8Index < ERFFEL_WORD_NUM; u8Index++)
        {
            ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, ERFFEL_OFFSET, u8Index * FLEXCAN_MEM_WORD_LEN);
            FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
        }

    }

}



/**
 * @brief This Function is used to receive Special Message Buffer data
 *
 * @param u8CanIndex Can Index, Must less than FLEXCAN_INSTANCE_COUNT
 * @param u8RealMbIndex, message buffer index 0...31, if fifo enable, always 0
 * @param u8MbDataLen, message buffer data length
 * @param pRxMsg, received data buffer
 * @return 0 means no data, others means received data
 */
static uint8_t FLEXCAN_LL_ReceiveMb(uint8_t u8CanIndex, uint8_t u8RealMbIndex, uint8 bEnFifo, uint8_t u8MbDataLen, FLEXCAN_RxMsgType *const pRxMsg)
{

    FLEXCAN_Type *pCan;
    uint32_t u32Status;

    uint32_t *pSrc;
    uint32_t *pDest;
    uint8_t  u8Index;

    uint32_t u32TempAddr;
    uint32_t u32WordLen;
    uint8    u8IflagIndex;

    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

    if (bEnFifo != 0U)
    {
        u8IflagIndex = 5U;  /* IFLAG1[BIT5] (Frames available in Rx FIFO) is asserted when there is at least one frame available to be read from the FIFO */
        u8RealMbIndex = 0U; /* fifo received always in MB0 */
    }
    else
    {
        u8IflagIndex = u8RealMbIndex;
    }

    pRxMsg->u32DataLen = 0U;

    u32Status = FLEXCAN_HWA_GetFlag1NoFifoFlag(pCan, (uint32_t)u8IflagIndex);

    if (u32Status != 0U)
    {
        pRxMsg->u8CanIndex = u8CanIndex;
        pRxMsg->u8MbIndex = u8RealMbIndex;

        /* message buffer 1th word */
        u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8RealMbIndex, u8MbDataLen, 0U);

        pRxMsg->bEnFd = (uint8_t)((FLEXCAN_MB_EDL_GET(u32TempAddr) == 0U) ? 0U : 1U);
        pRxMsg->bEnBrs = (uint8_t)((FLEXCAN_MB_BRS_GET(u32TempAddr) == 0U) ? 0U : 1U);


        pRxMsg->u32DataLen = FLEXCAN_MB_DLC_GET(u32TempAddr);
        pRxMsg->u32DataLen = FLEXCAN_DlcToDataLen(pRxMsg->u32DataLen);
        pRxMsg->eFrameType = (FLEXCAN_IdType)(FLEXCAN_MB_IDE_GET(u32TempAddr));

        /* message buffer 2th word */
        u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8RealMbIndex, u8MbDataLen, 4U);

        if (pRxMsg->eFrameType)
        {
            pRxMsg->u32CanId = FLEXCAN_MB_EXTID_GET(u32TempAddr);
        }
        else
        {
            pRxMsg->u32CanId = FLEXCAN_MB_STDID_GET(u32TempAddr);
        }



        pDest = (uint32_t *)pRxMsg->aData;
        /* message buffer 3th word */
        pSrc = (uint32_t *)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8RealMbIndex, u8MbDataLen, 8U);


        u32WordLen = pRxMsg->u32DataLen / 4U + (pRxMsg->u32DataLen % 4U > 0U ? 1U : 0U);

        for (u8Index = 0U; u8Index < u32WordLen; u8Index++)
        {
            /* big endian to little endian */
            REV_BYTES_32(pSrc[u8Index], pDest[u8Index]);
        }

        FLEXCAN_HWA_UnlockMbNoFifoFlag(pCan, (uint32_t)u8IflagIndex);

    }
    else
    {
    }

    return pRxMsg->u32DataLen > 0U;
}


/**
 * @brief This Function is used to receive Enhance FIFO Buffer data
 *
 * @param u8CanIndex Can Index, Must less than FLEXCAN_INSTANCE_COUNT
 * @param pRxMsg, received data buffer
 * @return 0 means no data, others means received data
 */
static uint8_t FLEXCAN_LL_ReceiveEnhanceFifo(uint8_t u8CanIndex, FLEXCAN_RxMsgType *const pRxMsg)
{
    uint32_t                u32Status;

    volatile uint32_t       *pSrc;
    volatile uint32_t       *pDest;
    uint8_t                 u8Index;
    FLEXCAN_Type                *pCan;

    pRxMsg->u32DataLen = 0U;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    if (FLEXCAN_LL_CheckFdInstance(u8CanIndex) == FLEXCAN_ERROR_OK)
    {
    #endif
        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

        /* The enhanced Rx FIFO has a watermark that is configured by setting EFRCR[ERFWM].
         * If EFRCR[ERFWM] is set, the CPU is notified only if a minimum number of messages is stored in the FIFO.
         * When the number of stored messages is greater than the value in EFRCR[ERFWM], ERFSR[ERFWMI] is set by the hardware. */

        /* check fd fifo data available */
        u32Status = FLEXCAN_HWA_ERFSRGetEnhancedFifoFlag(pCan, FLEXCAN_ERFSR_ERFDA_SHIFT, FLEXCAN_ERFSR_ERFDA_MASK);

        if (u32Status != 0U)
        {

            pRxMsg->u8CanIndex = u8CanIndex;
            pRxMsg->u8MbIndex = 0U;

            pRxMsg->bEnFd = (uint8_t)(FLEXCAN_EFIFOMB_EDL_GET());
            pRxMsg->bEnBrs = (uint8_t)(FLEXCAN_EFIFOMB_BRS_GET());


            pRxMsg->u32DataLen = FLEXCAN_EFIFOMB_DLC_GET();
            pRxMsg->u32DataLen = (uint8_t)(FLEXCAN_DlcToDataLen(pRxMsg->u32DataLen));
            pRxMsg->eFrameType = (FLEXCAN_IdType)(FLEXCAN_EFIFOMB_IDE_GET());


            if (pRxMsg->eFrameType)
            {
                pRxMsg->u32CanId = FLEXCAN_EFIFOMB_EXTID_GET();
            }
            else
            {
                pRxMsg->u32CanId = FLEXCAN_EFIFOMB_STDID_GET();
            }

            pDest = (uint32_t *)pRxMsg->aData;
            /* message buffer 3th word */
            pSrc = (volatile uint32_t *)FLEXCAN_EFIFOMB_DATAADDR_GET(0U);


            //u32WordLen = pRxMsg->u32DataLen / 4U + (pRxMsg->u32DataLen % 4U > 0U ? 1U : 0U);

            for (u8Index = 0U; u8Index < 18U; u8Index++)
            {
                /* big endian to little endian */
                REV_BYTES_32(pSrc[u8Index], pDest[u8Index]);
            }

            //u32WordLen = FLEXCAN_EFIFOMB_HRTIMESTAMP_GET(u32WordLen);             /* Read TIMER to unlock message buffers */

            /* clear fifo data available status */
            FLEXCAN_HWA_ERFSRClearEnhancedFifoFlag(pCan, FLEXCAN_ERFSR_ERFDA_MASK);

            /* get fifo data available status */
            u32Status = FLEXCAN_HWA_ERFSRGetEnhancedFifoFlag(pCan, FLEXCAN_ERFSR_ERFDA_SHIFT, FLEXCAN_ERFSR_ERFDA_MASK);

        }
        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
        #endif

    return pRxMsg->u32DataLen > 0U;
}


/**
 * @brief Polling Message Buffer Received Data
 *
 * @param u8CanIndex Can Index, Must less than FLEXCAN_INSTANCE_COUNT
 * @param pRxMsgList Message Stored buffer point
 * @return Received message count
 */
static uint8_t FLEXCAN_LL_PollingMb(uint8_t u8CanIndex, FLEXCAN_RxMsgType *const pRxMsgList)
{
    uint8_t                 u8MsgNum;
    uint32_t                u32Status;
    uint8_t                 u8RealMbIndex;

    FLEXCAN_SettingType     *pCurSetting;

    uint8_t                 u8MBindex;
    uint8_t                 u8MbDataWidth;

    pCurSetting = &s_aFlexCan_Setting_Table[u8CanIndex];

    u8MsgNum = 0U;

    /* loop check all receive message buffer */
    for (u8MBindex = 0U; u8MBindex < pCurSetting->u8RxMbCnt1; u8MBindex++)
    {
        u8RealMbIndex = (uint8_t)(pCurSetting->u8RxMbStart1 + u8MBindex);
        u8MbDataWidth = pCurSetting->eMbDataWidth;

        u32Status = FLEXCAN_LL_ReceiveMb(u8CanIndex, u8RealMbIndex, 0U, u8MbDataWidth, &pRxMsgList[u8MsgNum]);

        if (u32Status != 0U)
        {
            u8MsgNum ++;
        }
        else
        {
        }
    }

    return u8MsgNum;
}

/**
 * @brief Polling Legacy Rx FIFO
 *
 * @param u8CanIndex CanIndex, Must less than FLEXCAN_INSTANCE_COUNT
 * @param u8MbDataWidth Message Buffer Data Width
 * @param pRxMsgList received data buffer
 * @return receive message count
 */
static uint8_t FLEXCAN_LL_PollingLegacyFifo(uint8_t u8CanIndex, uint8_t u8MbDataWidth, FLEXCAN_RxMsgType *pRxMsgList)
{
    uint8_t                 u8MsgNum;
    uint32_t                u32Status;
    uint8_t                 u8MBindex;

    u8MsgNum = 0U;
    pRxMsgList[u8MsgNum].u32DataLen = 0U;

    /* legacy fifo only receive in MB 0 */
    u8MBindex = 0U;

    /* IFLAG1[BIT5] (Frames available in Rx FIFO) is asserted when there is at least one frame available to be read from the FIFO. */
    u32Status = 1U;

    while (u32Status != 0U)
    {
        u32Status = FLEXCAN_LL_ReceiveMb(u8CanIndex, u8MBindex, 1U, u8MbDataWidth, &pRxMsgList[u8MsgNum]);

        if (u32Status != 0U)
        {
            u8MsgNum ++;
        }
        else
        {
        }

    }

    return u8MsgNum;
}

/**
 * @brief Polling Enhanced Rx FIFO Data
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pRxMsgList received data buffer
 * @return receive message count
 */
static uint8_t FLEXCAN_LL_PollingEnhancedFifo(uint8_t u8CanIndex, FLEXCAN_RxMsgType *pRxMsgList)
{
    uint8_t                 u8MsgNum;
    uint32_t                u32Status;

    /* The enhanced Rx FIFO has a watermark that is configured by setting EFRCR[ERFWM].
     * If EFRCR[ERFWM] is set, the CPU is notified only if a minimum number of messages is stored in the FIFO.
     * When the number of stored messages is greater than the value in EFRCR[ERFWM], ERFSR[ERFWMI] is set by the hardware. */

    /* check fd fifo data available */
    u8MsgNum = 0U;
    u32Status = 1U;
    while (u32Status != 0U)
    {
        u32Status = FLEXCAN_LL_ReceiveEnhanceFifo(u8CanIndex, &pRxMsgList[u8MsgNum]);
        if (u32Status > 0U)
        {
            u8MsgNum ++;
        }
    }

    return u8MsgNum;
}


/**
 * @brief Receive Can FIFO Data
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param bEnableFd if it is CAN FD Fifo
 * @param pRxMsgList received data buffer
 * @return receive message count
 */
static uint8_t FLEXCAN_LL_ReceiveFifo(uint8_t u8CanIndex, uint8_t bEnableFd, FLEXCAN_RxMsgType *pRxMsgList)
{

    uint8_t                 u8MsgNum;

    FLEXCAN_SettingType     *pCurSetting;

    pCurSetting = &s_aFlexCan_Setting_Table[u8CanIndex];


    if (bEnableFd) /* can fd fifo receive */
    {
        u8MsgNum = FLEXCAN_LL_PollingEnhancedFifo(u8CanIndex, pRxMsgList);

    }
    else /* legacy fifo receive */
    {
        u8MsgNum = FLEXCAN_LL_PollingLegacyFifo(u8CanIndex, pCurSetting->eMbDataWidth, pRxMsgList);

    }

    return u8MsgNum;
}


/**
 * @brief Process CAN Baudrate from table
 *
 * @param pBaudCfg baudrate configuration
 * @return 0 is ok
 */
static uint8_t FLEXCAN_LL_ProcessBaud(FLEXCAN_BaudCfgType *pBaudCfg)
{
    uint32_t       u32Mod;
    uint8_t        u8RetVal;
    uint32_t       u32Index;


    u8RetVal = 1U;

    if (pBaudCfg->bEnFd)
    {
        u32Mod = (uint32_t)pBaudCfg->eClkSrcHz % (uint32_t)pBaudCfg->eBaudrate;
        if (u32Mod != 0U)
        {
            u8RetVal = 1U;
        }
        else
        {

            /* loop check for normal bit rate */
            for (u32Index = 0U; u32Index < sizeof(s_aFlexCan_NormalBaudDividerTable) / sizeof(s_aFlexCan_NormalBaudDividerTable[0]); u32Index++)
            {
                if ((pBaudCfg->eClkSrcHz == s_aFlexCan_NormalBaudDividerTable[u32Index].eClkHz) && (pBaudCfg->eBaudrate == s_aFlexCan_NormalBaudDividerTable[u32Index].eBaudrate))
                {
                    /* when pCan fd enabled, pCan normal bit set by CBT !!!! */
                    pBaudCfg->u32Cbt = FLEXCAN_CBT_EPRESDIV(s_aFlexCan_NormalBaudDividerTable[u32Index].u32Presdiv - 1U) |
                                       FLEXCAN_CBT_ERJW(s_aFlexCan_NormalBaudDividerTable[u32Index].u32Rjw - 1U) |
                                       FLEXCAN_CBT_EPSEG1(s_aFlexCan_NormalBaudDividerTable[u32Index].u32Pseg1 - 1U) |
                                       FLEXCAN_CBT_EPSEG2(s_aFlexCan_NormalBaudDividerTable[u32Index].u32Pseg2 - 1U) |
                                       FLEXCAN_CBT_EPROPSEG(s_aFlexCan_NormalBaudDividerTable[u32Index].u32Propseg - 1U) |
                                       FLEXCAN_CBT_BTF(1U);         /* SMP = 1: use 3 bits per CAN sample   */

                    u8RetVal = 0U;
                    break;
                }
            }


            if (u8RetVal == 0U)
            {
                u8RetVal = 1U;

                /* loop for fd data bit rate */
                for (u32Index = 0U; u32Index < sizeof(s_aFlexCan_DataBaudDividerTable) / sizeof(s_aFlexCan_DataBaudDividerTable[0]); u32Index++)
                {
                    if ((pBaudCfg->eClkSrcHz == s_aFlexCan_DataBaudDividerTable[u32Index].eClkHz) && (pBaudCfg->eDataBaud == s_aFlexCan_DataBaudDividerTable[u32Index].eBaudrate))
                    {
                        pBaudCfg->u32FdCtrl = FLEXCAN_FDCTRL_FDRATE(pBaudCfg->bEnBrs) |
                                              /* MBDSR0, pMb 0-31 data length, 8-0,16-1,32-2,64-3 */
                                              FLEXCAN_FDCTRL_MBDSR0(pBaudCfg->eMbDataWidth == FLEXCAN_DATAWIDTH_8 ? 0U : (pBaudCfg->eMbDataWidth == FLEXCAN_DATAWIDTH_16 ? 1U :
                                                                    (pBaudCfg->eMbDataWidth == FLEXCAN_DATAWIDTH_32 ? 2U : 3U)))
                                              | FLEXCAN_FDCTRL_TDCOFF(1U);


                        /* when pCan fd enabled, pCan normal bit set by CBT !!!! */
                        pBaudCfg->u32FdCbt = FLEXCAN_FDCBT_FPRESDIV(s_aFlexCan_DataBaudDividerTable[u32Index].u32Presdiv - 1U) |
                                             FLEXCAN_FDCBT_FRJW(s_aFlexCan_DataBaudDividerTable[u32Index].u32Rjw - 1U) |
                                             FLEXCAN_FDCBT_FPSEG1(s_aFlexCan_DataBaudDividerTable[u32Index].u32Pseg1 - 1U) |
                                             FLEXCAN_FDCBT_FPSEG2(s_aFlexCan_DataBaudDividerTable[u32Index].u32Pseg2 - 1U) |
                                             FLEXCAN_FDCBT_FPROPSEG(s_aFlexCan_DataBaudDividerTable[u32Index].u32Propseg);

                        u8RetVal = 0U;
                        break;
                    }
                }
            }


        }
    }
    else
    {
        u32Mod = (uint32_t)pBaudCfg->eClkSrcHz % (uint32_t)pBaudCfg->eBaudrate;
        if (u32Mod != 0U)
        {
            u8RetVal = 1U;
        }

        else
        {
            u8RetVal = 1U;
            /* loop check for normal bit rate */
            for (u32Index = 0U; u32Index < sizeof(s_aFlexCan_NormalBaudDividerTable) / sizeof(s_aFlexCan_NormalBaudDividerTable[0]); u32Index++)
            {
                if ((pBaudCfg->eClkSrcHz == s_aFlexCan_NormalBaudDividerTable[u32Index].eClkHz) && (pBaudCfg->eBaudrate == s_aFlexCan_NormalBaudDividerTable[u32Index].eBaudrate))
                {
                    /* when pCan fd enabled, pCan normal bit set by CBT !!!! */
                    pBaudCfg->u32Ctrl1 = FLEXCAN_CTRL1_PRESDIV(s_aFlexCan_NormalBaudDividerTable[u32Index].u32Presdiv - 1U) |
                                         FLEXCAN_CTRL1_RJW(s_aFlexCan_NormalBaudDividerTable[u32Index].u32Rjw - 1U) |
                                         FLEXCAN_CTRL1_PSEG1(s_aFlexCan_NormalBaudDividerTable[u32Index].u32Pseg1 - 1U) |
                                         FLEXCAN_CTRL1_PSEG2(s_aFlexCan_NormalBaudDividerTable[u32Index].u32Pseg2 - 1U) |
                                         FLEXCAN_CTRL1_PROPSEG(s_aFlexCan_NormalBaudDividerTable[u32Index].u32Propseg - 1U);

                    u8RetVal = 0U;
                }
            }


        }
    }


    return u8RetVal;

}

/**
 * @brief Set Legacy Rx FIFO
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pRxFilterList Filter id list
 * @param u32RxFilterCnt Filter id list length
 * @return FLEXCAN_ERROR_OK is ok
 */
static FLEXCAN_ErrorType FLEXCAN_LL_SetLegacyFifo(uint8_t u8CanIndex, FLEXCAN_RxMbFilterType *pRxFilterList, uint32_t u32RxFilterCnt)
{
    FLEXCAN_ErrorType tRetVal;
    uint32_t          u32FilterNum;
    uint32_t          u32FilterNumLeft;
    uint32_t          u32Index;

    FLEXCAN_Type     *pCan;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    tRetVal = FLEXCAN_LL_CheckFdInstance(u8CanIndex);

    if (tRetVal == FLEXCAN_ERROR_OK)
    {
    #else
    tRetVal = FLEXCAN_ERROR_OK;
    #endif
        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

        /* set legacy fifo */
        FLEXCAN_HWA_EnableLegacyFifo(pCan);


        /*           31   30      29  28  27  26  25  24       23  22  21  20  19  18  17  16          15  14  13  12  11  10  9   8          7   6   5   4   3   2   1   0        */
        /* Format A: RTR  IDE |                                  RXIDA (standard =29-19, extended = 29-1)                                                               |          */
        /* Format B: RTR  IDE |   RXIDB_0 (standart = 29-19, extended = 29-16) MSB compare          |  RTR IDE|RXIDB_1 (standart = 13-3, extended = 13-0) MSB compare              */
        /* Format C: RXIDC_0 (std/ext = 31-24) MSB compare |  RXIDC_1 (std/ext = 23-16) MSB compare |  RXIDC_2 (std/ext =15-8) MSB compare  |  RXIDC_3 (std/ext =7-0) MSB compare  */

        /* set always format A */


        u32FilterNum = 0U;

        /* filter start from MB 6 */
        for (u32Index = 0U; u32Index < u32RxFilterCnt; u32Index++)
        {
            /* extended id */
            if (pRxFilterList[u32Index].eRxFrameType == FLEXCAN_ID_EXT)
            {
                FLEXCAN_HWA_MbRam(pCan, 4U * 6U + u32FilterNum, (1U << 30) | (pRxFilterList[u32Index].u32RxCanId << 1)); /* id */
                FLEXCAN_HWA_SetIndividualMask(pCan, u32FilterNum, (1U << 30) | pRxFilterList[u32Index].u32RxCanIdMask) ;     /* mask */
            }
            else /* standard id */
            {
                FLEXCAN_HWA_MbRam(pCan, 4U * 6U + u32FilterNum, pRxFilterList[u32Index].u32RxCanId << 19);                /* id */
                FLEXCAN_HWA_SetIndividualMask(pCan, u32FilterNum, (1U << 30) | (pRxFilterList[u32Index].u32RxCanIdMask << 19)) ; /* mask */
            }

            u32FilterNum++;
        }

        /* filter elements number are multiple of 8 */
        u32FilterNumLeft = 8U - u32RxFilterCnt % 8U;
        /* set left same to last filter */
        for (u32Index = 0U; u32Index < u32FilterNumLeft; u32Index++)
        {
            /* extended id */
            if (pRxFilterList[u32FilterNum - 1U].eRxFrameType == FLEXCAN_ID_EXT)
            {
                FLEXCAN_HWA_MbRam(pCan, 4U * 6U + u32FilterNum + u32Index, (1U << 30) | (pRxFilterList[u32FilterNum - 1U].u32RxCanId << 1)); /* id */
                FLEXCAN_HWA_SetIndividualMask(pCan, u32FilterNum + u32Index, (1U << 30) | pRxFilterList[u32FilterNum - 1U].u32RxCanIdMask); /* mask */
            }
            else /* standard id */
            {
                FLEXCAN_HWA_MbRam(pCan, 4U * 6U + u32FilterNum + u32Index, pRxFilterList[u32FilterNum - 1U].u32RxCanId << 19);           /* id */
                FLEXCAN_HWA_SetIndividualMask(pCan, u32FilterNum + u32Index, (1U << 30) | (pRxFilterList[u32FilterNum - 1U].u32RxCanIdMask << 19)); /* mask */

            }
        }

        /* set fifo filter, 1 group filter contains 8 filter elements (2MBs) */
        /* left for tx = MaxMb-6 - (RFFN+1)*2 */
        u32FilterNum = u32FilterNum / 8U + (u32FilterNum % 8U > 0U ? 1U : 0U);
        FLEXCAN_HWA_SetLegacyFifoFilterNum(pCan, u32FilterNum);
        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
        #endif

    return tRetVal;
}

/**
 * @brief Set Enhanced Rx FIFO
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pRxFilterList Filter id list
 * @param u32RxFilterCnt Filter id list length
 * @param u8WaterMark DMA Wartmark
 * @return FLEXCAN_ERROR_OK is ok
 */
static FLEXCAN_ErrorType FLEXCAN_LL_SetEnhancedFifo(uint8_t u8CanIndex, FLEXCAN_RxMbFilterType *pRxFilterList, uint32_t u32RxFilterCnt, uint8_t u8WaterMark)
{
    FLEXCAN_ErrorType tRetVal;
    uint32_t          u32FilterERFCRNum;
    uint32_t          u32Index;
    FLEXCAN_Type     *pCan;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    tRetVal = FLEXCAN_LL_CheckFdInstance(u8CanIndex);

    if (tRetVal == FLEXCAN_ERROR_OK)
    {
    #else
    tRetVal = FLEXCAN_ERROR_OK;
    #endif

        uint32_t    u32ExtIDFilterNum;
        uint32_t    u32StdIDFilterNum;
        uint32_t    u32TempERFCR;

        /* current pCan instance */
        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

        /* Configure the filter elements by writing in the ERFFELn registers (ERFFELn registers are implemented in RAM; thus, they must be explicitly initialized prior to any reception). */

        /* standard id filter */
        /* 31-30     29-28     27           26-16           15-12      11           10-0                                           */
        /* FSCH=b00  Reserved  RTR filter   STD ID filter   Reserved   RTR mask     STD ID mask       id_filter&id_mask            */
        /* FSCH=b01  Reserved  RTR filter   STD ID filter2  Reserved   RTR mask     STD ID filter1    id filter1<=id<= id filter2  */
        /* FSCH=b10  Reserved  RTR filter2  STD ID filter2  Reserved   RTR filter1  STD ID filter1    id filter1= id = id filter2  */

        /* extended id filter */
        /* 31-30      29           28-0             */
        /* FSCH=00b   RTR filter   EXT ID filter    */
        /* Reserved   RTR mask     EXT ID mask      */
        /* FSCH=01b   RTR filter   EXT ID filter2   */
        /* Reserved   RTR mask     EXT ID filter1   */
        /* FSCH=10b   RTR filter2  EXT ID filter2   */
        /* Reserved   RTR filter1  EXT ID filter1   */

        u32ExtIDFilterNum = 0U;
        u32StdIDFilterNum = 0U;

        /* get extended id count and standard id count */
        for (u32Index = 0U; u32Index < u32RxFilterCnt; u32Index++)
        {
            if (pRxFilterList[u32Index].eRxFrameType == FLEXCAN_ID_EXT)
            {
                /* extended id first */
                /* pCan->ERFFEL[u32Index] &= 0xFFFFFFFU; */
                FLEXCAN_HWA_EnhancedFifoFilter(pCan, u32ExtIDFilterNum * 2U, pRxFilterList[u32Index].u32RxCanId);    /* id   */
                FLEXCAN_HWA_EnhancedFifoFilter(pCan, u32ExtIDFilterNum * 2U + 1U, pRxFilterList[u32Index].u32RxCanIdMask); /* mask */

                u32ExtIDFilterNum++;
            }
        }

        for (u32Index = 0U; u32Index < u32RxFilterCnt; u32Index++)
        {
            /* standard id */
            if (pRxFilterList[u32Index].eRxFrameType == FLEXCAN_ID_STD)
            {
                FLEXCAN_HWA_EnhancedFifoFilter(pCan, u32ExtIDFilterNum * 2U + u32StdIDFilterNum, (pRxFilterList[u32Index].u32RxCanId << 16) | pRxFilterList[u32Index].u32RxCanIdMask);
                u32StdIDFilterNum++;
            }
        }

        /* standard id number must multiple of 2 */
        tRetVal = (FLEXCAN_ErrorType)(tRetVal | ((u32StdIDFilterNum % 2U == 1U) ? FLEXCAN_ERROR_INVALID_PARAM : FLEXCAN_ERROR_OK));

        if (tRetVal == FLEXCAN_ERROR_OK)
        {
            /* total id filter number in ERFCR, two std  */
            u32FilterERFCRNum = u32StdIDFilterNum / 2U + u32ExtIDFilterNum - 1U;



            /* Write one to ERFSR[ERFCLR] to reset Enhanced Rx FIFO engine */
            FLEXCAN_HWA_ERFSRResetEnhancedFifo(pCan);
            /* Clear EFRSR[ERFUFW], EFRSR[ERFOVF], EFRSR[ERFWMI], and EFRSR[ERFDA], if they are set. */
            FLEXCAN_HWA_ERFSRClearEnhancedFifoFlag(pCan, FLEXCAN_ERFSR_ERFUFW_MASK | FLEXCAN_ERFSR_ERFWMI_MASK | FLEXCAN_ERFSR_ERFDA_MASK);
            /* Write EFRCR[NFE] to configure the total number of enhanced Rx FIFO filter elements to be used in Enhanced Rx FIFO reception. */


            /* set rx fifo filter num */
            u32TempERFCR = ((u32FilterERFCRNum) << FLEXCAN_ERFCR_NFE_SHIFT)&FLEXCAN_ERFCR_NFE_MASK;

            /* Write ERFCR[NEXIF] to configure the number of extended ID and standard ID filter elements to be used in Enhanced Rx FIFO reception (NEXIF �� NFE + 1). */
            /* set rx fifo extended id filter num, <= NFE+1 */
            u32TempERFCR |= (u32ExtIDFilterNum << FLEXCAN_ERFCR_NEXIF_SHIFT)&FLEXCAN_ERFCR_NEXIF_MASK;

            u32TempERFCR |= FLEXCAN_ERFCR_ERFWM(u8WaterMark - 1U); /* receive 1 message will indicate to fifo water mark */

            u32TempERFCR |= FLEXCAN_ERFCR_DMALW(19U);

            u32TempERFCR |= FLEXCAN_ERFCR_ERFEN_MASK; /* enable enhance fifo dma */

            FLEXCAN_HWA_SetERFCR(pCan, u32TempERFCR);

            /* set enhanced fifo */
            FLEXCAN_HWA_EnableFDFifo(pCan);

            /* Configure the Enhanced Rx FIFO watermark by writing ERFCR[ERFWM]. */

            /* If interrupts will be used, set the interrupt enables in the ERIER register */

            /* If DMA will be used, set MCR[DMA] to enable DMA operation and write ERFCR[DMALW] to configure the number of words to transfer for each Enhanced Rx FIFO data element */

        }
        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
        #endif

    return tRetVal;

}



/**
 * @brief Process Tx Iflag and return result
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param u8Handler  Transmit Handler
 * @return 1 means process successfully and can transmit next time, 0 means no active flag, 0xff means out of range
 */
static uint8_t FLEXCAN_LL_ProcessTx(uint8_t u8CanIndex, uint8_t u8Handler)
{
    uint8_t             u8Index;
    FLEXCAN_Type        *pCan;
    FLEXCAN_SettingType *pCurSetting;
    uint32_t            u32Iflag;
    uint32_t            u32HandlerMask;

	pCurSetting = &s_aFlexCan_Setting_Table[u8CanIndex];

#if FLEXCAN_CHECK_PARAMETERS == STD_ON
    if(u8Handler < pCurSetting->u8TxMbCnt1)
    {
#endif
		pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

		u32Iflag = FLEXCAN_HWA_GetFlag1(pCan);;
		u32HandlerMask = (1U << (pCurSetting->u8TxMbStart1+u8Handler));

		u32Iflag = u32Iflag & u32HandlerMask;

		if(u32Iflag>0U)
			FLEXCAN_HWA_SetFlag1(pCan, u32Iflag);

		u8Index = ((u32Iflag>0U)?1U:0U);
#if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
    else
    {
    	u8Index = 0xFFU;
    }
#endif

    return u8Index;
}


/* ################################################################################## */
/* ################################ Global Functions ################################ */



/**
 * @brief Initial FLEXCAN variables Memory
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 */
void FLEXCAN_InitMemory(uint8_t u8CanIndex)
{

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    FLEXCAN_ErrorType    tRetVal;
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(u8CanIndex);
    if (tRetVal == FLEXCAN_ERROR_OK)
    {
    #endif

        s_aFlexCan_Setting_Table[u8CanIndex].bEnableFd = 0U;
        s_aFlexCan_Setting_Table[u8CanIndex].bEnableFifo = 0U;
        s_aFlexCan_Setting_Table[u8CanIndex].bEnableDMA = 0U;
        s_aFlexCan_Setting_Table[u8CanIndex].pRxBuf = NULL;
        s_aFlexCan_Setting_Table[u8CanIndex].u8RxMbCnt1 = 0U;
        s_aFlexCan_Setting_Table[u8CanIndex].u8RxMbStart1 = 0U;
        s_aFlexCan_Setting_Table[u8CanIndex].u8TxMbCnt1 = 0U;
        s_aFlexCan_Setting_Table[u8CanIndex].u8TxMbStart1 = 0U;
        s_aFlexCan_Setting_Table[u8CanIndex].u8RxFifoCnt = 0U;
        s_aFlexCan_Setting_Table[u8CanIndex].eMbDataWidth = FLEXCAN_DATAWIDTH_8;
        s_aFlexCan_Setting_Table[u8CanIndex].u8EnhancedFifoDmaWM = 0U;
        s_aFlexCan_ErrorNotifyTable[u8CanIndex] = NULL;
        s_aFlexCan_TxNotifyTable[u8CanIndex] = NULL;
        s_aFlexCan_RxNotifyTable[u8CanIndex] = NULL;

        s_aFlexCan_CanUsed[u8CanIndex] = 0U;

        /* set first state */
        s_aCurrentSequence[u8CanIndex] = FLEXCAN_SEQUENCE_DEINIT;
        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
        #endif

}


/**
 * @brief Initial CAN
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pInitCfg  clock, baud-rate, canfd, data length and so on.
 * @return 0 is ok, others are not ok
 */
FLEXCAN_ErrorType FLEXCAN_Init(uint8_t u8CanIndex, const FLEXCAN_InitType *const pInitCfg)
{
    FLEXCAN_ErrorType    tRetVal;
    uint32_t             u32TempCtrl1;
    uint32_t             u32TempMcr;
    uint8_t              u8Result;
    FLEXCAN_Type             *pCan;
    FLEXCAN_BaudCfgType  tBaudCfg;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(u8CanIndex);

    if ((tRetVal == FLEXCAN_ERROR_OK) && (s_aCurrentSequence[u8CanIndex] == FLEXCAN_SEQUENCE_DEINIT))
    {
        tRetVal = FLEXCAN_ERROR_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_SEQUENCE;
    }


    if (pInitCfg == NULL || (pInitCfg->u8EnhancedFifoDmaWM > 12U))
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_PARAM;
    }
    else
    {
        /* DMA only support in Legacy Rx FIFO and Enhance Rx FIFO */
        if (pInitCfg->bEnDma != 0U)
        {
            if ((pInitCfg->bEnRxFifo == 0U))
            {
                tRetVal |= FLEXCAN_ERROR_INVALID_PARAM;
            }
        }
    }

    if ((pInitCfg->bEnFd == 0U) && (pInitCfg->bEnBrs == 1U))
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_PARAM;
    }

    if ((pInitCfg->bEnFd == 1U) && (u8CanIndex >= FLEXCAN_FD_INSTANCE_COUNT))
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_PARAM;
    }

    if (tRetVal == FLEXCAN_ERROR_OK)
    {
    #endif
        /* set not start state */
        s_aCurrentSequence[u8CanIndex] = FLEXCAN_SEQUENCE_NOTSTART;

        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

        u8Result = 0U;
        tRetVal = FLEXCAN_ERROR_OK;

        FLEXCAN_HWA_SetMcrDisable(pCan, TRUE);
        FLEXCAN_HWA_SetCtrl1(pCan, 0U);
        FLEXCAN_HWA_SetCtrl1BaudSrc(pCan, pInitCfg->eClkSrcSel);

        FLEXCAN_HWA_SetMcrDisable(pCan, FALSE);

        /*  mcr->B.bitMDIS = 0; */

        FLEXCAN_HWA_SetHaltFreeze(pCan);

        /* wait for bitFRZACK=1 on freeze mode entry/exit */
        if (FLEXCAN_HWA_WaitMcrFreezen(pCan, 10000U) != 0U)
        {
            tRetVal |= FLEXCAN_ERROR_TIMEOUT;
        }
        else
        {
//            FLEXCAN_HWA_SetCtrl2(pCan,
//                                 FLEXCAN_CTRL2_WRMFRZ(1U)      |  /* initial ram ecc */
//                                 FLEXCAN_CTRL2_TASD(20U)       |
//                                 FLEXCAN_CTRL2_DIRECT_EN(((pInitCfg->eDirect) & FLEXCAN_CTRL2_DIRECT_EN_MASK) ? 1U : 0U)     |
//                                 FLEXCAN_CTRL2_DIRECT_TRIG(((pInitCfg->eDirect) & FLEXCAN_CTRL2_DIRECT_TRIG_MASK) ? 1U : 0U) |
//                                 FLEXCAN_CTRL2_ISOCANFDEN(1U));
            FLEXCAN_HWA_SetCtrl2(pCan,
                                 FLEXCAN_CTRL2_WRMFRZ(1U)      |  /* initial ram ecc */
                                 FLEXCAN_CTRL2_TASD(20U)       |
                                 FLEXCAN_CTRL2_ISOCANFDEN(1U));



            tBaudCfg.bEnFd = pInitCfg->bEnFd;
            tBaudCfg.bEnBrs = pInitCfg->bEnBrs;
            tBaudCfg.eMbDataWidth = pInitCfg->eMbDataWidth;

            tBaudCfg.eClkSrcHz = pInitCfg->eClkSrcHz;
            tBaudCfg.eBaudrate = pInitCfg->eBaudrate;
            tBaudCfg.eDataBaud = pInitCfg->eDataBaud;


            u8Result = FLEXCAN_LL_ProcessBaud(&tBaudCfg);


            if (u8Result)
            {
                tRetVal = FLEXCAN_ERROR_INVALID_PARAM;
            }
            else
            {
                /* when pCan fd disabled, pCan normal bit set by CTRL1 !!!! */
                u32TempCtrl1 = FLEXCAN_CTRL1_CLKSRC(pInitCfg->eClkSrcSel) | FLEXCAN_CTRL1_LOM(pInitCfg->bListenOnly);

                if (!tBaudCfg.bEnFd)
                {
                    u32TempCtrl1 |= tBaudCfg.u32Ctrl1;         /* SMP = 1: use 3 bits per CAN sample   */
                }
                else
                {
                    FLEXCAN_HWA_SetCBT(pCan, tBaudCfg.u32Cbt);

                    FLEXCAN_HWA_SetFDCTRL(pCan, tBaudCfg.u32FdCtrl);
                    FLEXCAN_HWA_SetFDCBT(pCan, tBaudCfg.u32FdCbt);
                }


                FLEXCAN_HWA_SetCtrl1(pCan, u32TempCtrl1);

                /* initial RAM to avoid ECC error */
                FLEXCAN_LL_EmbededRam_Init(u8CanIndex);

                u32TempMcr = FLEXCAN_MCR_MDIS(0) |               /* enable pCan module */
                             FLEXCAN_MCR_FRZ(1)    |                 /* not frozen */
                             FLEXCAN_MCR_RFEN(((!pInitCfg->bEnFd) && pInitCfg->bEnRxFifo) ? 1U : 0U) | /* Legacy RX FIFO, only when canfd not enable */
                             FLEXCAN_MCR_HALT(1)   |                 /* not halt */
                             FLEXCAN_MCR_SOFTRST(0) |                /* not reset */
                             FLEXCAN_MCR_SUPV(1)   |                 /* supervisor mode */
                             FLEXCAN_MCR_WRNEN(0)  |                 /* wake up disable */
                             FLEXCAN_MCR_SRXDIS(1) |                 /* self reception disable */
                             FLEXCAN_MCR_IRMQ(0)   |                 /* individual Rx masking */
                             FLEXCAN_MCR_DMA(pInitCfg->bEnDma) |     /* DMA enable */
                             FLEXCAN_MCR_PNET_EN(0) |                /* Pretended Networking Enable */
                             FLEXCAN_MCR_LPRIOEN(0) |                /* Local Priority disable */
                             FLEXCAN_MCR_AEN(0)    |                 /* abort disable */
                             FLEXCAN_MCR_FDEN(pInitCfg->bEnFd) |     /* CAN FD enable */
                             FLEXCAN_MCR_IDAM(0)   |                 /* ID Acceptance Mode for Rx FIFO, format A */
                             FLEXCAN_MCR_MAXMB(0);                   /* Max number of Message Buffer, num 31 is the 32th MB */

                FLEXCAN_HWA_SetMCR(pCan, u32TempMcr);       /* Negate FlexCAN 1 halt state for 32 MBs */

                /* store setting value */
                s_aFlexCan_Setting_Table[u8CanIndex].bEnableFd = pInitCfg->bEnFd;
                s_aFlexCan_Setting_Table[u8CanIndex].bEnableFifo = pInitCfg->bEnRxFifo;
                s_aFlexCan_Setting_Table[u8CanIndex].bEnableDMA = pInitCfg->bEnDma;
                s_aFlexCan_Setting_Table[u8CanIndex].eMbDataWidth = pInitCfg->eMbDataWidth;
                s_aFlexCan_Setting_Table[u8CanIndex].u8EnhancedFifoDmaWM =  pInitCfg->u8EnhancedFifoDmaWM;
            }
        }
        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
        #endif

    return tRetVal;

}


/**
 * @brief De-initial can instance
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @return 0 is ok, others are not ok
 */
FLEXCAN_ErrorType FLEXCAN_DeInit(uint8_t u8CanIndex)
{
    FLEXCAN_ErrorType tRetVal;
    uint32_t          u32TempMcr;
    FLEXCAN_Type          *pCan;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(u8CanIndex);

    if (tRetVal == FLEXCAN_ERROR_OK)
    {
        tRetVal = FLEXCAN_ERROR_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_SEQUENCE;
    }

    if (tRetVal == FLEXCAN_ERROR_OK)
    {
    #else
    tRetVal = FLEXCAN_ERROR_OK;
    #endif
        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];
		FLEXCAN_HWA_SetHaltFreeze(pCan);

        /* wait for bitFRZACK=1 on freeze mode entry/exit */
        if (FLEXCAN_HWA_WaitMcrFreezen(pCan, 10000U) != 0U)
        {
            tRetVal |= FLEXCAN_ERROR_TIMEOUT;
        }
        else
        {
	        if(u8CanIndex < FLEXCAN_FD_INSTANCE_COUNT)
	        {
	        	FLEXCAN_HWA_DisableFDFifo(pCan);
	        }


	    	FLEXCAN_HWA_DisableLegacyFifo(pCan);

	        u32TempMcr = FLEXCAN_MCR_MDIS(1)   |                 /* enable pCan module */
	                     FLEXCAN_MCR_FRZ(0)    |                 /* not frozen */
	                     FLEXCAN_MCR_RFEN(0U)  |                 /* RX FIFO disable */
	                     FLEXCAN_MCR_HALT(0)   |                 /* not halt */
	                     FLEXCAN_MCR_SOFTRST(0) |                /* not reset */
	                     FLEXCAN_MCR_SUPV(1)   |                 /* supervisor mode */
	                     FLEXCAN_MCR_WRNEN(0)  |                 /* wake up disable */
	                     FLEXCAN_MCR_SRXDIS(1) |                 /* self reception disable */
	                     FLEXCAN_MCR_IRMQ(0)   |                 /* individual Rx masking */
	                     FLEXCAN_MCR_DMA(0)    |                 /* DMA enable */
	                     FLEXCAN_MCR_PNET_EN(0) |                /* Pretended Networking Enable */
	                     FLEXCAN_MCR_LPRIOEN(0) |                /* Local Priority disable */
	                     FLEXCAN_MCR_AEN(0)    |                 /* abort disable */
	                     FLEXCAN_MCR_FDEN(0)   |                 /* CAN FD enable */
	                     FLEXCAN_MCR_IDAM(0)   |                 /* ID Acceptance Mode for Rx FIFO, format A */
	                     FLEXCAN_MCR_MAXMB(0);                   /* Max number of Message Buffer, num 31 is the 32th MB */


	        FLEXCAN_HWA_SetCtrl1(pCan, 0U);
	        FLEXCAN_HWA_SetMCR(pCan, u32TempMcr);       /* Negate FlexCAN 1 halt state for 32 MBs */

	        /* clear setting value */
	        FLEXCAN_InitMemory(u8CanIndex);
	    }

        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
        #endif

    return tRetVal;
}


/**
 * @brief Configure can receive message box and id filter
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pRxMbCfg contains CAN Instance, Rx CAN ID and Mask
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_RxFilterConfig(uint8_t u8CanIndex, const FLEXCAN_MBConfigType *const pRxMbCfg)
{
    FLEXCAN_ErrorType       tRetVal;
    FLEXCAN_Type                *pCan;
    FLEXCAN_RxMbFilterType  *pCurRxCfg;
    uint32_t                u32Mask;
    uint8_t                 u8Index;
    FLEXCAN_SettingType     *pCurSetting;
    uint8_t                 bIndividualMask;
    uint32_t                u32TempAddr;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(u8CanIndex);

    if ((tRetVal == FLEXCAN_ERROR_OK) && (s_aCurrentSequence[u8CanIndex] == FLEXCAN_SEQUENCE_NOTSTART))
    {
        tRetVal = FLEXCAN_ERROR_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_SEQUENCE;
    }

    if (pRxMbCfg == NULL)
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_PARAM;
    }
    else
    {
        /* check buffer point if it is null */
        if ((pRxMbCfg->pRxBuf == NULL) || (((pRxMbCfg->u8RxFilterFifoCnt > 0U) && (pRxMbCfg->pRxFilterFifoList == NULL))))
        {
            tRetVal |= FLEXCAN_ERROR_INVALID_PARAM;
        }
    }

    if (tRetVal == FLEXCAN_ERROR_OK)
    {
    #else
    tRetVal = FLEXCAN_ERROR_OK;
    #endif
        bIndividualMask = 1U;

        /* current pCan instance */
        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

        /* current pCan message pMb cnt */
        pCurSetting = &s_aFlexCan_Setting_Table[u8CanIndex];


        pCurSetting->pRxBuf = pRxMbCfg->pRxBuf;

        pCurSetting->u8RxMbStart1 = 0U;   /* receive message buffer always start from 0 */
        pCurSetting->u8TxMbStart1 = 0U;
        pCurSetting->u8RxMbCnt1 = pRxMbCfg->u8RxFilterMBCnt;
        pCurSetting->u8TxMbCnt1 = pRxMbCfg->u8TxMsgCnt;
        pCurSetting->u8RxFifoCnt = pRxMbCfg->u8RxFilterFifoCnt;

        if (pCurSetting->bEnableFifo)
        {
            /* only non-fd fifo need rx filter between rx and tx message buffer */
            if (pCurSetting->bEnableFd)
            {
#if 0
                /* must multiple of 2 */
                if (pRxMbCfg->u8RxFilterFifoCnt % 2U)
                {
                    tRetVal |= FLEXCAN_ERROR_INVALID_PARAM;
                }
#endif

                /* set fifo filter parameter */
                tRetVal = (FLEXCAN_ErrorType)(tRetVal | FLEXCAN_LL_SetEnhancedFifo(u8CanIndex, pRxMbCfg->pRxFilterFifoList, (uint32_t)pRxMbCfg->u8RxFilterFifoCnt,
                                                                                   pCurSetting->u8EnhancedFifoDmaWM));
            }
            else
            {
                /* insert rx filter before tx message buffer, every group filter contains 8 elements(2MBs), at least 2 groups */
                if (pRxMbCfg->u8RxFilterFifoCnt <= 8U)
                {
                    pCurSetting->u8RxMbStart1 = 8U;
                }
                else
                {
                    pCurSetting->u8RxMbStart1 = (uint8_t)(6U + 2U * (pRxMbCfg->u8RxFilterFifoCnt / 8U + (pRxMbCfg->u8RxFilterFifoCnt % 8U > 0U ? 1U : 0U)));

                }
                pCurSetting->u8TxMbStart1 = (uint8_t)(pCurSetting->u8RxMbStart1 + pCurSetting->u8RxMbCnt1);


                /* set fifo filter parameter */
                tRetVal |= FLEXCAN_LL_SetLegacyFifo(u8CanIndex, pRxMbCfg->pRxFilterFifoList, (uint32_t)pRxMbCfg->u8RxFilterFifoCnt);
            }


        }
        else
        {
            if (pCurSetting->bEnableFd)
            {

                /* clear enhanced fifo */
                FLEXCAN_HWA_DisableFDFifo(pCan);
            }
            else
            {
                /* clear legacy fifo */
                FLEXCAN_HWA_DisableLegacyFifo(pCan);
            }
        }


        /* For normal message buffer. */

        /* fifo can exist with normal mb */
        /* Receive MB first set */

        for (u8Index = 0U; u8Index < pCurSetting->u8RxMbCnt1; u8Index++)
        {
            uint8_t u8MBIndex;
            /* ############## current rx pMb #################### */
            u8MBIndex = (uint8_t)(pCurSetting->u8RxMbStart1 + u8Index);
            pCurSetting->u8TxMbStart1 ++;
            /* current rx filter */
            pCurRxCfg = &(pRxMbCfg->pRxFilterMBList[u8Index]);
            /* message buffer 1th word */
            u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8MBIndex, pCurSetting->eMbDataWidth, 0U);

            FLEXCAN_MB_IDE_SET(u32TempAddr, pCurRxCfg->eRxFrameType);

            /* message buffer 2th word */
            u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8MBIndex, pCurSetting->eMbDataWidth, 4U);

            /* 1. set filter id */
            if (pCurRxCfg->eRxFrameType == FLEXCAN_ID_STD)
            {
                FLEXCAN_MB_STDID_SET(u32TempAddr, pCurRxCfg->u32RxCanId);

                u32Mask = pCurRxCfg->u32RxCanIdMask << 18U; /* stardard id left shift 18 bits */
            }
            else /* extended id filter */
            {
                FLEXCAN_MB_EXTID_SET(u32TempAddr, pCurRxCfg->u32RxCanId);
                u32Mask = pCurRxCfg->u32RxCanIdMask; /* stardard id */
            }

            /* message buffer 1th word */
            u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8MBIndex, pCurSetting->eMbDataWidth, 0U);
            /* set code 0x04U to enable rx */
            FLEXCAN_MB_CODE_SET(u32TempAddr, 4U);

            /* 3. set rx filter u32Mask */
            if (bIndividualMask)
            {
                /* In FRZ mode, init CAN1 16 msg buf filters */
                FLEXCAN_HWA_SetIndividualMask(pCan, (uint32_t)u8MBIndex, u32Mask);
            }
            else
            {
                /* global u32Mask */
                /* Global acceptance u32Mask: check all ID bits     */
                if (u8MBIndex == 14U)
                {
                    FLEXCAN_HWA_SetRx14Mask(pCan, u32Mask);
                }
                else if (u8MBIndex == 15U)
                {
                    FLEXCAN_HWA_SetRx15Mask(pCan, u32Mask);
                }
                else
                {
                    FLEXCAN_HWA_SetGlobalMask(pCan, u32Mask);
                }
            }


        }
        u8Index = (uint8_t)(pCurSetting->u8TxMbStart1 + pCurSetting->u8TxMbCnt1 - (uint8_t)0x1U);

        /* set max pMb number */
        FLEXCAN_HWA_AttachMCR(pCan, FLEXCAN_MCR_MAXMB(u8Index)   /* Maximum pMb index */
                              | FLEXCAN_MCR_IRMQ(bIndividualMask));   /* individual Rx masking */

        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
        #endif

    return tRetVal;
}


/**
 * @brief Configure can interrupt
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pIntCfg Contians interrupt enable and call back function points
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_SetInterrupt(uint8_t u8CanIndex, const FLEXCAN_InterruptType *const pIntCfg)
{
    FLEXCAN_ErrorType    tRetVal;
    FLEXCAN_Type         *pCan;
    uint32_t             u32Mask;
    uint8_t              u8Index;
    FLEXCAN_SettingType  *pCurSetting;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(u8CanIndex);

    if ((tRetVal == FLEXCAN_ERROR_OK) && (s_aCurrentSequence[u8CanIndex] == FLEXCAN_SEQUENCE_NOTSTART))
    {
        tRetVal = FLEXCAN_ERROR_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_SEQUENCE;
    }

    if (pIntCfg == NULL)
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_PARAM;
    }
    else
    {
        /* check buffer point if it is null */
        if (((pIntCfg->bEnRxFifoInterrupt == 1U)  && (pIntCfg->pRxFifoNotify == NULL))
            || ((pIntCfg->bEnRxMBInterrupt == 1U) && (pIntCfg->pRxMBNotify == NULL))
            || ((pIntCfg->bEnErrorInterrupt == 1U) && (pIntCfg->pErrorNotify == NULL)))
        {
            tRetVal |= FLEXCAN_ERROR_INVALID_PARAM;
        }
    }

    if (tRetVal == FLEXCAN_ERROR_OK)
    {
    #else
    tRetVal = FLEXCAN_ERROR_OK;
    #endif
        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

        pCurSetting = &s_aFlexCan_Setting_Table[u8CanIndex];

        if ((pIntCfg->bEnErrorInterrupt) || (pIntCfg->bEnRxFifoInterrupt) || (pIntCfg->bEnRxMBInterrupt))
        {
        }


        if (pIntCfg->bEnErrorInterrupt)
        {
            FLEXCAN_HWA_AttachCtrl1(pCan, FLEXCAN_CTRL1_ERRMSK(1U) |   /* error interrupt u32Mask */
                                    FLEXCAN_CTRL1_BOFFMSK(1U));  /* busoff interrupt u32Mask */


            FLEXCAN_HWA_AttachCtrl2(pCan, FLEXCAN_CTRL2_ERRMSK_FAST(1U) /* fast error */);

            s_aFlexCan_ErrorNotifyTable[u8CanIndex] = pIntCfg->pErrorNotify;
        }

        if (pIntCfg->bEnRxFifoInterrupt)
        {
            /* interrupt for fifo */
            if (pCurSetting->bEnableFifo)
            {
                /* can fd fifo interrupt */
                if (pCurSetting->bEnableFd)
                {
                    /* enhanced fifo data available interrupt */
                    FLEXCAN_HWA_SetERFIERDataInterrupt(pCan);
                }
                else /* non-fd fifo interrupt */
                {
                    /* MB 5 at least one message in fifo interrupt */
                    FLEXCAN_HWA_SetMaskFifoInterrupt(pCan);
                }
                s_aFlexCan_RxFifoNotifyTable[u8CanIndex] = pIntCfg->pRxFifoNotify;
            }
        }
        if (pIntCfg->bEnTxMBInterrupt)
        {
            u32Mask = 0U;

            for (u8Index = 0U; u8Index < pCurSetting->u8TxMbCnt1; u8Index++)
            {
                u32Mask = (u32Mask << 1U) | (1U << pCurSetting->u8TxMbStart1);
            }

            /* MB 31-0 u32Mask */
            FLEXCAN_HWA_AttachMaskMbInterrupt(pCan, u32Mask);

            s_aFlexCan_TxNotifyTable[u8CanIndex] = pIntCfg->pTxMBNotify;
        }

        if (pIntCfg->bEnRxMBInterrupt)
        {
            u32Mask = 0U;

            for (u8Index = 0U; u8Index < pCurSetting->u8RxMbCnt1; u8Index++)
            {
                u32Mask = (u32Mask << 1U) | (1U << pCurSetting->u8RxMbStart1);
            }

            /* MB 31-0 u32Mask */
            FLEXCAN_HWA_AttachMaskMbInterrupt(pCan, u32Mask);

            s_aFlexCan_RxNotifyTable[u8CanIndex] = pIntCfg->pRxMBNotify;
        }
        s_aFlexCan_Setting_Table[u8CanIndex].bEnableFifoInt = pIntCfg->bEnRxFifoInterrupt;
        s_aFlexCan_Setting_Table[u8CanIndex].bEnableTxMBInt = pIntCfg->bEnTxMBInterrupt;
        s_aFlexCan_Setting_Table[u8CanIndex].bEnableRxMBInt = pIntCfg->bEnRxMBInterrupt;
        s_aFlexCan_Setting_Table[u8CanIndex].bEnableErrInt = pIntCfg->bEnRxMBInterrupt;
        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
        #endif

    return tRetVal;
}


/**
 * @brief Start can instance
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_Start(uint8_t u8CanIndex)
{
    FLEXCAN_ErrorType tRetVal;
    uint32_t   u32TempMcr;
    FLEXCAN_Type *pCan;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(u8CanIndex);

    if ((tRetVal == FLEXCAN_ERROR_OK) && (s_aCurrentSequence[u8CanIndex] == FLEXCAN_SEQUENCE_NOTSTART))
    {
        tRetVal = FLEXCAN_ERROR_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_SEQUENCE;
    }


    if (tRetVal == FLEXCAN_ERROR_OK)
    {
    #else
    tRetVal = FLEXCAN_ERROR_OK;
    #endif
        /* set started state */
        s_aCurrentSequence[u8CanIndex] = FLEXCAN_SEQUENCE_STARTED;

        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

        u32TempMcr = FLEXCAN_HWA_GetMCR(pCan);

        u32TempMcr &= ~(FLEXCAN_MCR_FRZ(1U)    |  /* not frozen */
                        FLEXCAN_MCR_HALT(1U)    /* not halt */
                        /*| FLEXCAN_MCR_SUPV(1)   user mode */
                       ); /* not reset */

        FLEXCAN_HWA_SetMCR(pCan, u32TempMcr);

        if (FLEXCAN_HWA_WaitMcrExitFreezen(pCan, 10000U) != 0U)
        {
            tRetVal |= FLEXCAN_ERROR_TIMEOUT;
        }
        else
        {

            if (FLEXCAN_HWA_WaitMcrReady(pCan, 10000U) != 0U)
            {
                tRetVal |= FLEXCAN_ERROR_TIMEOUT;
            }
            else
            {

                s_aFlexCan_CanUsed[u8CanIndex] = 1U;
            }
        }
        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
        #endif

    return tRetVal;
}


/**
 * @brief Stop can instance
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 */
FLEXCAN_ErrorType FLEXCAN_Stop(uint8_t u8CanIndex)
{
    FLEXCAN_ErrorType tRetVal;
    uint32_t   u32TempMcr;
    FLEXCAN_Type *pCan;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(u8CanIndex);

    if ((tRetVal == FLEXCAN_ERROR_OK) && (s_aCurrentSequence[u8CanIndex] >= FLEXCAN_SEQUENCE_DEINIT))
    {
        tRetVal = FLEXCAN_ERROR_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_SEQUENCE;
    }


    if (tRetVal == FLEXCAN_ERROR_OK)
    {
    #else
    tRetVal = FLEXCAN_ERROR_OK;
    #endif
        /* set started state */
        s_aCurrentSequence[u8CanIndex] = FLEXCAN_SEQUENCE_NOTSTART;

        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

        u32TempMcr = FLEXCAN_HWA_GetMCR(pCan);

        u32TempMcr |= FLEXCAN_MCR_FRZ(1U)    |  /* not frozen */
                      FLEXCAN_MCR_HALT(1U)    /* not halt */
                      /*| FLEXCAN_MCR_SUPV(1)   user mode */
                      ; /* not reset */

        FLEXCAN_HWA_SetMCR(pCan, u32TempMcr);

        /* must wait */
        if (FLEXCAN_HWA_WaitMcrFreezen(pCan, 10000U) != 0U)
        {
            tRetVal |= FLEXCAN_ERROR_TIMEOUT;
        }
        else
        {

            /* must wait */
            if (FLEXCAN_HWA_WaitMcrNoReady(pCan, 10000U) != 0U)
            {
                tRetVal |= FLEXCAN_ERROR_TIMEOUT;
            }
            else
            {
                s_aFlexCan_CanUsed[u8CanIndex] = 0U;
            }
        }
        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }

        #endif

    return tRetVal;
}


/**
 * @brief Transmit data, if tx disable, must call FLEXCAN_TransmitProcess after transmiting
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pTxMsg contains CAN instance, CAN ID, CAN FD and CAN data.
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_TransmitData(uint8_t u8CanIndex, const FLEXCAN_TxMsgType *const pTxMsg)
{
    FLEXCAN_ErrorType     tRetVal;
    uint32_t              *pSrc;
    uint32_t              *pDest;
    uint32_t              u32Index;
    FLEXCAN_Type          *pCan;
    FLEXCAN_SettingType   *pCurSetting;
    uint8_t               u8TxRealMbIndex;
    uint32_t              u32WordLen;
    uint32_t              u32TempAddr;
    uint32_t              u32Code;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(u8CanIndex);

    if ((tRetVal == FLEXCAN_ERROR_OK) && (s_aCurrentSequence[u8CanIndex] == FLEXCAN_SEQUENCE_STARTED))
    {
        tRetVal = FLEXCAN_ERROR_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_SEQUENCE;
    }

    if (pTxMsg == NULL)
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_PARAM;
    }
    else
    {
        /* check buffer point if it is null */
        if (&(pTxMsg->aData) == NULL)
        {
            tRetVal |= FLEXCAN_ERROR_INVALID_PARAM;
        }
        else
        {
            if (pTxMsg->u32DataLen > (uint32_t)s_aFlexCan_Setting_Table[u8CanIndex].eMbDataWidth)
            {
                tRetVal |= FLEXCAN_ERROR_INVALID_PARAM;
            }
        }
    }

    if ((pTxMsg->bEnFd == 1U) && (u8CanIndex >= FLEXCAN_FD_INSTANCE_COUNT))
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_PARAM;
    }


    if (tRetVal == FLEXCAN_ERROR_OK)
    {
    #endif

        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

        pCurSetting = &s_aFlexCan_Setting_Table[u8CanIndex];
        if (pTxMsg->u8TxHandler >= pCurSetting->u8TxMbCnt1)
        {
            tRetVal = FLEXCAN_ERROR_INVALID_PARAM;
        }
        else
        {
            u8TxRealMbIndex = (uint8_t)(pTxMsg->u8TxHandler + pCurSetting->u8TxMbStart1);

            /* message buffer 1th word */
            u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8TxRealMbIndex, pCurSetting->eMbDataWidth, 0U);
            u32Code = FLEXCAN_MB_CODE_GET(u32TempAddr);
            if((0x8 != u32Code) && (0U != u32Code))
            {
                tRetVal = FLEXCAN_ERROR_BUSY;
            }
            else
            {

                /* message buffer 1th word */
                u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8TxRealMbIndex, pCurSetting->eMbDataWidth, 0U);
                /* clear last value */
                FLEXCAN_REG32_CONTENT(u32TempAddr) = 0U;

                FLEXCAN_MB_EDL_SET(u32TempAddr, pTxMsg->bEnFd);
                FLEXCAN_MB_BRS_SET(u32TempAddr, pTxMsg->bEnBrs);

                FLEXCAN_MB_IDE_SET(u32TempAddr, pTxMsg->eFrameType);

                /* SRR */
                FLEXCAN_MB_SRR_SET(u32TempAddr, 0U);
                /* DLC */
                u32Index = FLEXCAN_DataLenToDlc(pTxMsg->u32DataLen);
                FLEXCAN_MB_DLC_SET(u32TempAddr, u32Index);

                /* message buffer 2th word */
                u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8TxRealMbIndex, pCurSetting->eMbDataWidth, 4U);
                /* clear last value */
                FLEXCAN_REG32_CONTENT(u32TempAddr) = 0U;

                /* standard id */
                if (pTxMsg->eFrameType == FLEXCAN_ID_STD)
                {
                    FLEXCAN_MB_STDID_SET(u32TempAddr, pTxMsg->u32CanId);
                }
                else /* extended id */
                {
                    FLEXCAN_MB_EXTID_SET(u32TempAddr, pTxMsg->u32CanId);
                }

                FLEXCAN_MB_PRIO_SET(u32TempAddr, 0U);

                pSrc = (uint32_t *)(uint32_t)(&(pTxMsg->aData[0]));
                /* message buffer 3th word */
                pDest = (uint32_t *)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8TxRealMbIndex, pCurSetting->eMbDataWidth, 8U);

                u32WordLen = pTxMsg->u32DataLen / 4U + (pTxMsg->u32DataLen % 4U > 0U ? 1U : 0U);

                /* revert data to little endian */
                for (u32Index = 0U; u32Index < u32WordLen; u32Index++)
                {
                    /* big endian to little endian */
                    REV_BYTES_32(pSrc[u32Index], pDest[u32Index]);
                }


                /* message buffer 1th word */
                u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8TxRealMbIndex, pCurSetting->eMbDataWidth, 0U);


                /* CODE set 0x0C to transmit */
                FLEXCAN_MB_CODE_SET(u32TempAddr, 0x0CU);


                if (pTxMsg->bWaitTxCompleted)
                {
                    u32TempAddr = 0U;
                    u32WordLen = FLEXCAN_HWA_GetFlag1NoFifoFlag(pCan, u8TxRealMbIndex);
                    while ((u32WordLen == 0U) && (u32TempAddr++ < pTxMsg->u16WaitTxTimeout))
                    {
                        u32WordLen = FLEXCAN_HWA_GetFlag1NoFifoFlag(pCan, u8TxRealMbIndex);
                    }

                    if (u32WordLen == 0U)
                    {
                        tRetVal = FLEXCAN_ERROR_TIMEOUT;
                    }

                }
                else
                {
                    u32WordLen = FLEXCAN_HWA_GetFlag1NoFifoFlag(pCan, u8TxRealMbIndex);
                    if (u32WordLen == 0U)
                    {
                        tRetVal = FLEXCAN_ERROR_TIMEOUT;
                    }
                }

            }
        }
        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
        #endif

    return tRetVal;
}


/**
 * @brief Process flag after transmit
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param u8Handler  Transmit Handler
 * @return 1 means process successfully and can transmit next time, 0 means no active flag, 0xff means out of range
 */
uint8_t FLEXCAN_TransmitProcess(uint8_t u8CanIndex, uint8_t u8TxHandler)
{
    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    FLEXCAN_ErrorType    tRetVal;
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(u8CanIndex);
    if (tRetVal == FLEXCAN_ERROR_OK)
    {
    #endif
        return FLEXCAN_LL_ProcessTx(u8CanIndex, u8TxHandler);
        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
    else
    {
        return 0U;
    }
        #endif
}


/**
 * @brief Abort transmit with special transmit handler
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param u8TxHandler Transmit handler
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_TransmitAbort(uint8_t u8CanIndex, uint8_t u8TxHandler)
{
    FLEXCAN_ErrorType     tRetVal;
    FLEXCAN_SettingType   *pCurSetting;
    FLEXCAN_Type          *pCan;
    uint8_t               u8TxRealMbIndex;
    uint32_t              u32TempAddr;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(u8CanIndex);

    if ((tRetVal == FLEXCAN_ERROR_OK) && (s_aCurrentSequence[u8CanIndex] == FLEXCAN_SEQUENCE_STARTED))
    {
        tRetVal = FLEXCAN_ERROR_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_SEQUENCE;
    }


    if (tRetVal == FLEXCAN_ERROR_OK)
    {

    #endif

        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

        pCurSetting = &s_aFlexCan_Setting_Table[u8CanIndex];
        if (u8TxHandler >= pCurSetting->u8TxMbCnt1)
        {
            tRetVal = FLEXCAN_ERROR_INVALID_PARAM;
        }

        else
        {
            u8TxRealMbIndex = (uint8_t)(u8TxHandler + pCurSetting->u8TxMbStart1);
            /* message buffer 1th word */
            u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8TxRealMbIndex, pCurSetting->eMbDataWidth, 0U);


            /* CODE set 0x09 to aborting transmit */
            FLEXCAN_MB_CODE_SET(u32TempAddr, 0x09U);
        }
        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
        #endif

    return tRetVal;
}


/**
 * @brief Receive data when polling (not used when rx interrupt enabled)
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pRxBufList is FLEXCAN_RxMsgType type point point, and don't need to be initialed
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_Receive_Polling(uint8_t u8CanIndex, FLEXCAN_RxMsgListType *const pRxBufList)
{
    FLEXCAN_ErrorType   tRetVal;
    uint8_t             u8RetVal;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(u8CanIndex);

    if ((tRetVal == FLEXCAN_ERROR_OK) && (s_aCurrentSequence[u8CanIndex] == FLEXCAN_SEQUENCE_STARTED))
    {
        tRetVal = FLEXCAN_ERROR_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_SEQUENCE;
    }

    if (pRxBufList == NULL)
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_PARAM;
    }


    if (tRetVal == FLEXCAN_ERROR_OK)
    {

    #else
    tRetVal = FLEXCAN_ERROR_OK;
    #endif
        u8RetVal = 0U;

        pRxBufList->u8RxMsgCnt = 0U;
        pRxBufList->pRxMsgBuf = s_aFlexCan_Setting_Table[u8CanIndex].pRxBuf;


        if (s_aFlexCan_CanUsed[u8CanIndex] == 1U)
        {
            /* receive from fifo or normal */
            if (s_aFlexCan_Setting_Table[u8CanIndex].bEnableFifo)
            {
                u8RetVal = FLEXCAN_LL_ReceiveFifo(u8CanIndex, s_aFlexCan_Setting_Table[u8CanIndex].bEnableFd, pRxBufList->pRxMsgBuf);
            }
            else
            {
                u8RetVal = FLEXCAN_LL_PollingMb(u8CanIndex, pRxBufList->pRxMsgBuf);
            }
            pRxBufList->u8RxMsgCnt = u8RetVal;
        }
        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
        #endif

    return tRetVal;
}



/**
 * @brief Get can error
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pErrorInfo is error information
 * @return 0 is no error, others contains error
 */
FLEXCAN_ErrorType FLEXCAN_GetErrorInfo(uint8_t u8CanIndex, FLEXCAN_ErrorInfoType *const pErrorInfo)
{
    FLEXCAN_ErrorType tRetVal;
    uint32_t u32ESR1Status, u32ECRStatus;
    FLEXCAN_Type *pCan;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(u8CanIndex);

    if ((tRetVal == FLEXCAN_ERROR_OK) && (s_aCurrentSequence[u8CanIndex] >= FLEXCAN_SEQUENCE_NOTSTART))
    {
        tRetVal = FLEXCAN_ERROR_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_SEQUENCE;
    }


    if (tRetVal == FLEXCAN_ERROR_OK)
    {

    #else
    tRetVal = FLEXCAN_ERROR_OK;
    #endif
        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

        u32ESR1Status = FLEXCAN_HWA_GetErrorInfo(pCan);
        pErrorInfo->u32ErrorValue = u32ESR1Status;

        u32ECRStatus = FLEXCAN_HWA_GetErrorCount(pCan);
        pErrorInfo->u32ErrorValue &= FLEXCAN_ESR1_BIT1ERR_FAST_MASK | FLEXCAN_ESR1_BIT0ERR_FAST_MASK | FLEXCAN_ESR1_CRCERR_FAST_MASK | FLEXCAN_ESR1_FRMERR_FAST_MASK |
                                     FLEXCAN_ESR1_STFERR_FAST_MASK |
                                     FLEXCAN_ESR1_ERROVR_MASK | FLEXCAN_ESR1_ERRINT_FAST_MASK | FLEXCAN_ESR1_BOFFDONEINT_MASK | FLEXCAN_ESR1_TWRNINT_MASK | FLEXCAN_ESR1_RWRNINT_MASK |
                                     FLEXCAN_ESR1_BIT1ERR_MASK | FLEXCAN_ESR1_BIT0ERR_MASK | FLEXCAN_ESR1_ACKERR_MASK | FLEXCAN_ESR1_CRCERR_MASK | FLEXCAN_ESR1_FRMERR_MASK | FLEXCAN_ESR1_STFERR_MASK |
                                     FLEXCAN_ESR1_TXWRN_MASK | FLEXCAN_ESR1_RXWRN_MASK | FLEXCAN_ESR1_FLTCONF_MASK | FLEXCAN_ESR1_BOFFINT_MASK | FLEXCAN_ESR1_ERRINT_MASK;

        if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_BIT1ERR_FAST_MASK)
        	pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_BIT1ERR_FAST = 1U;
        else
        	pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_BIT1ERR_FAST = 0U;

        if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_BIT0ERR_FAST_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_BIT0ERR_FAST = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_BIT0ERR_FAST = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_CRCERR_FAST_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_CRCERR_FAST = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_CRCERR_FAST = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_FRMERR_FAST_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_FRMERR_FAST = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_FRMERR_FAST = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_STFERR_FAST_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_STFERR_FAST = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_STFERR_FAST = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_ERROVR_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_ERROVR = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_ERROVR = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_ERRINT_FAST_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_ERRINT_FAST = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_ERRINT_FAST = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_BOFFDONEINT_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_BOFFDONEINT = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_BOFFDONEINT = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_TWRNINT_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_TWRNINT = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_TWRNINT = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_RWRNINT_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_RWRNINT = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_RWRNINT = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_BIT1ERR_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_BIT1ERR = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_BIT1ERR = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_BIT0ERR_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_BIT0ERR = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_BIT0ERR = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_ACKERR_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_ACKERR = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_ACKERR = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_CRCERR_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_CRCERR = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_CRCERR = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_FRMERR_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_FRMERR = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_FRMERR = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_STFERR_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_STFERR = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_STFERR = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_TXWRN_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_TXWRN = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_TXWRN = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_RXWRN_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_RXWRN = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_RXWRN = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_FLTCONF_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_FLTCONF = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_FLTCONF = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_BOFFINT_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_BOFFINT = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_BOFFINT = 0U;

		if(pErrorInfo->u32ErrorValue & FLEXCAN_ESR1_ERRINT_MASK)
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_ERRINT = 1U;
        else
            pErrorInfo->tErrorDetail.u8Error_FLEXCAN_ESR1_ERRINT = 0U;

        pErrorInfo->u32RxErrCnt = (u32ECRStatus & FLEXCAN_ECR_RXERRCNT_MASK) >> FLEXCAN_ECR_RXERRCNT_SHIFT;
        pErrorInfo->u32RxErrCnt_Fast = (u32ECRStatus & FLEXCAN_ECR_RXERRCNT_FAST_MASK) >> FLEXCAN_ECR_RXERRCNT_FAST_SHIFT;
        pErrorInfo->u32TxErrCnt = (u32ECRStatus & FLEXCAN_ECR_TXERRCNT_MASK) >> FLEXCAN_ECR_TXERRCNT_SHIFT;
        pErrorInfo->u32TxErrCnt_Fast = (u32ECRStatus & FLEXCAN_ECR_TXERRCNT_FAST_MASK) >> FLEXCAN_ECR_TXERRCNT_FAST_SHIFT;

        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
    else
    {
        PROCESS_UNUSED_VAR(u32ESR1Status);
        PROCESS_UNUSED_VAR(u32ECRStatus);
    }
        #endif

    return tRetVal;
}

/**
 * @brief Clear can error
 *
 * @param u8CanIndex Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param pErrorInfo is error information
 * @return 0 is no error, others contains error
 */
FLEXCAN_ErrorType FLEXCAN_ClrErrorInfo(uint8_t u8CanIndex, const FLEXCAN_ErrorInfoType *const pErrorInfo)
{
    FLEXCAN_ErrorType tRetVal;
    FLEXCAN_Type *pCan;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(u8CanIndex);

    if ((tRetVal == FLEXCAN_ERROR_OK) && (s_aCurrentSequence[u8CanIndex] >= FLEXCAN_SEQUENCE_NOTSTART))
    {
        tRetVal = FLEXCAN_ERROR_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_ERROR_INVALID_SEQUENCE;
    }


    if (tRetVal == FLEXCAN_ERROR_OK)
    {
    #else
    tRetVal = FLEXCAN_ERROR_OK;
    #endif
        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

        FLEXCAN_HWA_ClrErrorInfo(pCan, pErrorInfo->u32ErrorValue);
        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
        #endif

    return tRetVal;
}




/**
 * @brief Transfer Data length to DLC
 *
 * @param u32DataLen data length
 * @return DLC
 */
uint32_t FLEXCAN_DataLenToDlc(uint32_t u32DataLen)
{
    uint32_t u32Dlc;

    switch (u32DataLen)
    {
        case 0U:
        case 1U:
        case 2U:
        case 3U:
        case 4U:
        case 5U:
        case 6U:
        case 7U:
        case 8U:
        {
            u32Dlc = u32DataLen;
        }
        break;
        case 12U:
        {
            u32Dlc = 9U;
        }
        break;
        case 16U:
        {
            u32Dlc = 10U;
        }
        break;
        case 20U:
        {
            u32Dlc = 11U;
        }
        break;
        case 24U:
        {
            u32Dlc = 12U;
        }
        break;
        case 32U:
        {
            u32Dlc = 13U;
        }
        break;
        case 48U:
        {
            u32Dlc = 14U;
        }
        break;
        case 64U:
        {
            u32Dlc = 15U;

        }
        break;

        default:
            u32Dlc = 0U;
            break;
    }

    return u32Dlc;
}


/**
 * @brief Transfer DLC to Data length
 *
 * @param u32Dlc DLC Data Length
 * @return
 */
uint32_t FLEXCAN_DlcToDataLen(uint32_t u32Dlc)
{
    uint32_t u32DataLen;


    switch (u32Dlc)
    {
        case 0U:
        case 1U:
        case 2U:
        case 3U:
        case 4U:
        case 5U:
        case 6U:
        case 7U:
        case 8U:
        {
            u32DataLen = u32Dlc;
        }
        break;
        case 9U:
        {
            u32DataLen = 12U;
        }
        break;
        case 10U:
        {
            u32DataLen = 16U;
        }
        break;
        case 11U:
        {
            u32DataLen = 20U;
        }
        break;
        case 12U:
        {
            u32DataLen = 24U;
        }
        break;
        case 13U:
        {
            u32DataLen = 32U;
        }
        break;
        case 14U:
        {
            u32DataLen = 48U;
        }
        break;
        case 15U:
        {
            u32DataLen = 64U;
        }
        break;

        default:
            u32DataLen = 0U;
            break;
    }

    return u32DataLen;
}


/* ################################################################################## */
/* ############################## Interrupt Services ################################ */

/**
 * @brief Can interrupt process
 *
 * @param u8CanIndex  Can Index, Must less than FLEXCAN_INSTANCE_COUNT
 */
void FLEXCAN_IRQHandler(uint8_t u8CanIndex)
{
    uint8_t               u8RecNum, u8Index;
    uint32_t              u32Flag1, u32ERFSR;
    FLEXCAN_Type          *pCan;
    FLEXCAN_RxMsgType     *pRxMsgList;
    uint8_t               u8FifoInterrupt;
    FLEXCAN_ErrorType     tRetVal;

    FLEXCAN_ErrorInfoType pErrorInfo;

    #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(u8CanIndex);
    if (tRetVal == FLEXCAN_ERROR_OK)
    {
    #endif

        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

        FLEXCAN_GetErrorInfo(u8CanIndex, &pErrorInfo);

        pRxMsgList = s_aFlexCan_Setting_Table[u8CanIndex].pRxBuf;

        u32Flag1 = FLEXCAN_HWA_GetFlag1(pCan);


        /* check pCan error */
        if (pErrorInfo.u32ErrorValue != 0U)
        {
            /* error notification */
            if (s_aFlexCan_ErrorNotifyTable[u8CanIndex] != NULL)
            {
                /* clear can error */
                s_aFlexCan_ErrorNotifyTable[u8CanIndex](u8CanIndex, &pErrorInfo);
            }
        }

        tRetVal = FLEXCAN_LL_CheckFdInstance(u8CanIndex);

        if (tRetVal == FLEXCAN_ERROR_OK)
        {
            u32ERFSR = FLEXCAN_HWA_ERFSRGetEnhancedFifoFlag(pCan, FLEXCAN_ERFSR_ERFDA_SHIFT, FLEXCAN_ERFSR_ERFDA_MASK);
            u8FifoInterrupt = ((true == s_aFlexCan_Setting_Table[u8CanIndex].bEnableFd) && (0U != u32ERFSR) && (s_aFlexCan_Setting_Table[u8CanIndex].bEnableFifoInt));
        }
        else
        {
            u8FifoInterrupt = 0U;
        }
        u8FifoInterrupt = (uint8_t)(u8FifoInterrupt | ((false == s_aFlexCan_Setting_Table[u8CanIndex].bEnableFd) && (u32Flag1 & 0x20U) &&
                                                       (s_aFlexCan_Setting_Table[u8CanIndex].bEnableFifoInt)));

        /* check pCan receive data from fifo or normal */
        if ((s_aFlexCan_Setting_Table[u8CanIndex].bEnableFifo) && u8FifoInterrupt)
        {
            u8RecNum = FLEXCAN_LL_ReceiveFifo(u8CanIndex, s_aFlexCan_Setting_Table[u8CanIndex].bEnableFd, pRxMsgList);
            /* rx notification */
            if ((u8RecNum > 0U) && (s_aFlexCan_RxFifoNotifyTable[u8CanIndex] != NULL))
            {
                for (u8Index = 0U; u8Index < u8RecNum; u8Index++)
                {
                    s_aFlexCan_RxFifoNotifyTable[u8CanIndex](u8CanIndex, &pRxMsgList[u8Index]);
                }
            }
        }

        /* check transmit interrupt */
        if (s_aFlexCan_Setting_Table[u8CanIndex].bEnableTxMBInt)
        {
        	for (u8Index = 0U; u8Index < s_aFlexCan_Setting_Table[u8CanIndex].u8TxMbCnt1; u8Index++)
        	{
        		u8RecNum = FLEXCAN_LL_ProcessTx(u8CanIndex,u8Index);
				if ((u8RecNum == 1U) && (s_aFlexCan_TxNotifyTable[u8CanIndex] != NULL))
				{
					s_aFlexCan_TxNotifyTable[u8CanIndex](u8CanIndex, u8Index);
				}
        	}
        }

        /* check receive interrupt */
        if (s_aFlexCan_Setting_Table[u8CanIndex].bEnableRxMBInt)
        {
            u8RecNum = FLEXCAN_LL_PollingMb(u8CanIndex, pRxMsgList);
            if ((u8RecNum > 0U) && (s_aFlexCan_RxNotifyTable[u8CanIndex] != NULL))
            {
                for (u8Index = 0U; u8Index < u8RecNum; u8Index++)
                {
                    s_aFlexCan_RxNotifyTable[u8CanIndex](u8CanIndex, &pRxMsgList[u8Index]);
                }
            }
        }

        PROCESS_UNUSED_VAR(pCan);

        #if FLEXCAN_CHECK_PARAMETERS == STD_ON
    }
        #endif
}

