/**
 * @file fc7xxx_driver_fcuart.c
 * @author Flagchip
 * @brief FC7xxx FCUart driver type definition and API
 * @version 0.1.0
 * @date 2024-01-14
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */

/********************************************************************************
 *   Revision History:
 *
 *   Version     Date          Initials       CR#          Descriptions
 *   ---------   ----------    ------------   ----------   ---------------
 *   0.1.0      2024-01-14    Flagchip0122     N/A          FC7xxx internal release version
 ********************************************************************************/

#include "fc7xxx_driver_fcuart.h"




/********* Macro ************/

/********* Local typedef ************/

typedef enum
{
    UART_PRINT_RADIX_BIN = 2U,
    UART_PRINT_RADIX_OCT = 8U,
    UART_PRINT_RADIX_DEC = 10U,
    UART_PRINT_RADIX_HEX = 16U
} UART_PrintIntType;

/**
 * @brief FCUART Operation Sequence
 *
 */
typedef enum
{
    FCUART_SEQUENCE_VAR_NOINIT,       /**< FCUART_SEQUENCE_DEINIT means fcuart variables data is not initialed                       */
    FCUART_SEQUENCE_DEINIT,           /**< FCUART_SEQUENCE_DEINIT means fcuart driver is not initialed                               */
    FCUART_SEQUENCE_NOTSTART_RECEIVE, /**< FCUART_SEQUENCE_NOTSTART_RECEIVE means fcuart driver initialed and write/erase is allowed */
    FCUART_SEQUENCE_START_RECEIVE     /**< FCUART_SEQUENCE_START_RECEIVE means fcuart driver started received                        */
} FCUART_SequenceType;

/********* Local Variables ************/
/* UART instance array */
static FCUART_Type *const s_aFCUART_InstanceTable[FCUART_INSTANCE_COUNT] = FCUART_BASE_PTRS;

/* sequence table */
static FCUART_SequenceType s_aCurrentSequence[FCUART_INSTANCE_COUNT] = {FCUART_SEQUENCE_VAR_NOINIT};

/* error notify callback function point */
static FCUART_ErrorInterrupt_CallBackType s_aFCUART_ErrorNotifyTable[FCUART_INSTANCE_COUNT];

/* receive notify callback function point */
static FCUART_TxRxInterrupt_CallBackType s_aFCUART_RxNotifyTable[FCUART_INSTANCE_COUNT];

/* Transfer empty notify callback function point */
static FCUART_TxRxInterrupt_CallBackType s_aFCUART_TxEmptyNotifyTable[FCUART_INSTANCE_COUNT];

/* Transfer complete notify callback function point */
static FCUART_TxRxInterrupt_CallBackType s_aFCUART_TxCompleteNotifyTable[FCUART_INSTANCE_COUNT];

/* Idle notify callback function point */
static FCUART_IdleInterrupt_CallBackType s_aFCUART_IdleNotifyTable[FCUART_INSTANCE_COUNT];

/* check every pUart instance whether is used */
static uint8_t s_aFCUART_UartUsed[FCUART_INSTANCE_COUNT];

/* check every pUart instance transmit timeout */
static uint32_t s_aFCUART_TransmitTimeout[FCUART_INSTANCE_COUNT];

/* pUart instance receive buffer */
static FCUART_DataType *s_aFCUART_RxMsg[FCUART_INSTANCE_COUNT];

/* pUart instance transfer buffer */
static FCUART_DataType *s_aFCUART_TxMsg[FCUART_INSTANCE_COUNT];

/********* Local Prototype Functions ************/

static FCUART_ErrorType FCUART_LL_CheckInstance(uint8_t u8UartIndex);

static uint32_t FCUART_LL_Error(uint8_t u8UartIndex);

static FCUART_ErrorType FCUART_LL_ProcessBaud(uint32_t u32Smb, uint32_t *u32OverSamp, uint32_t *u32Sbr);

static FCUART_ErrorType FCUART_LL_Transmit_Char(FCUART_Type *pUart, uint8_t u8Data, uint32_t u32TimeoutTick);

static FCUART_ErrorType FCUART_LL_Receive(uint8_t u8UartIndex, FCUART_DataType *pUartData);

static FCUART_ErrorType FCUART_LL_Transmit_Empty(uint8_t u8UartIndex, FCUART_DataType *pUartData);

static FCUART_ErrorType FCUART_LL_Transmit_Complete(uint8_t u8UartIndex);

static FCUART_ErrorType FCUART_LL_Idle(uint8_t u8UartIndex);

static uint8_t FCUART_Float2Char(double Value, char *pOutStr, uint32_t u32Eps);

static uint8_t FCUART_Int2Char(int i32Value, char *pOutStr, UART_PrintIntType eRadix, bool bHexUpper);

/********* Global Prototype Functions  ************/

/********* Local Functions  ************/
/**
 * @brief Check UART instance
 *
 * @param u8UartIndex UART instance number
 * @return
 */
static FCUART_ErrorType FCUART_LL_CheckInstance(uint8_t u8UartIndex)
{
    FCUART_ErrorType tRetVal;

    if (u8UartIndex < FCUART_INSTANCE_COUNT)
    {
        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
    }
    else
    {
        tRetVal = (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    }

    return tRetVal;
}

/**
 * @brief Process get OverSamp and SBR
 *
 * @param u32Smb   the value OverSame*SBR
 * @param u32OverSamp out OverSampe
 * @param u32Sbr out
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
static FCUART_ErrorType FCUART_LL_ProcessBaud(uint32_t u32Smb, uint32_t *u32OverSamp, uint32_t *u32Sbr)
{
    FCUART_ErrorType tRetVal;
    uint32_t u32SbrTemp;
    uint32_t u32OverSampTemp;
    uint32_t u32TempSmbDiff;
    uint32_t u32SmbDiff;
    uint32_t u32CalcSmb;
    uint32_t u32OverSamp1;
    uint32_t u32Sbr1;
    uint32_t u32OriginDiff;

    u32OverSamp1 = 4U; /* 4..32 */

    /* sbr = smb / oversamp */
    u32Sbr1 = (uint16_t)(u32Smb / (u32OverSamp1));
    u32CalcSmb = (u32OverSamp1) * (u32Sbr1);

    if (u32CalcSmb > u32Smb)
    {
        u32SmbDiff = u32CalcSmb - u32Smb;
    }
    else
    {
        u32SmbDiff = u32Smb - u32CalcSmb;
    }
    u32OriginDiff = u32SmbDiff;

    if (u32SmbDiff != 0U)
    {

        /* loop to find the best u32OverSamp1 value possible, one that generates minimum u32SmbDiff
         * iterate through the rest of the supported values of u32OverSamp */
        for (u32OverSampTemp = 5U; u32OverSampTemp <= 32U; u32OverSampTemp++)
        {
            /* calculate the temporary u32Sbr value   */
            u32SbrTemp = (uint32_t)(u32Smb / u32OverSampTemp);
            /* calculate the baud rate based on the temporary u32OverSamp and u32Sbr values */
            u32CalcSmb = (uint32_t)(u32OverSampTemp * u32SbrTemp);

            if (u32CalcSmb > u32Smb)
            {
                u32TempSmbDiff = u32CalcSmb - u32Smb;
            }
            else
            {
                u32TempSmbDiff = u32Smb - u32CalcSmb;
            }

            if (u32TempSmbDiff < u32SmbDiff)
            {
                u32SmbDiff = u32TempSmbDiff;
                u32OverSamp1 = u32OverSampTemp; /* update and store the best u32OverSamp value calculated */
                u32Sbr1 = u32SbrTemp;           /* update store the best u32Sbr value calculated */
            }

            /* when differ is 0U, break */
            if (u32SmbDiff == 0U)
            {
                break;
            }
        }
    }

    /* check differ */
    if (u32SmbDiff <= u32OriginDiff)
    {
        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;

        /* out the calculated value */
        *u32Sbr = u32Sbr1;
        *u32OverSamp = u32OverSamp1;
    }
    else
    {
        tRetVal = (FCUART_ErrorType)FCUART_ERROR_FAILED;
    }

    return tRetVal;
}

/**
 * @brief Function to Transmit single Char
 *
 * @param pUart UART Instance point
 * @param u8Data UART data
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
static FCUART_ErrorType FCUART_LL_Transmit_Char(FCUART_Type *pUart, uint8_t u8Data, uint32_t u32TimeoutTick)
{
    uint32_t u32Result;
    uint32_t u32TryCount;

    /* check transmit ready flag */
    u32Result = FCUART_HWA_GetStatus(pUart, FCUART_STAT_TDREF);

    if (u32Result != 0U)
    {
        FCUART_HWA_SetData(pUart, (uint32_t)u8Data); /* Send data */
        FCUART_HWA_SetTxTransfer(pUart, true);       /* start transmit */

        u32Result = 0U;
        u32TryCount = 0U;

        while ((u32Result == 0U) && (u32TryCount < u32TimeoutTick))
        {
            /* check transmit flag */
            u32Result = FCUART_HWA_GetStatus(pUart, FCUART_STAT_TCF);
            u32TryCount++;
        }

        /* after transmit completed, close TE */
        FCUART_HWA_SetTxTransfer(pUart, false);
    }

    return (u32Result == 0U) ? (FCUART_ErrorType)FCUART_ERROR_FAILED : (FCUART_ErrorType)FCUART_ERROR_OK;
}

/**
 * @brief Function to Transmit single Char by interrupt
 *
 * @param u8UartIndex UART Instance
 * @param pUartData UART receive buffer
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
static FCUART_ErrorType FCUART_LL_Transmit_Empty(uint8_t u8UartIndex, FCUART_DataType *pUartData)
{
    FCUART_ErrorType tRetVal = (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    FCUART_Type *pUart;
    uint32_t u32TempStats;
    uint32_t u32Index;
    uint8_t  u8Index;
    uint8_t  u8TxWaterMark;

    pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];
    if ((pUartData != NULL) && (pUartData->pDatas != NULL))
    {
        /* get and clear receive flag */
        u32TempStats = FCUART_HWA_GetStatus(pUart, FCUART_STAT_TDREF);
        if (u32TempStats > 0U)
        {
            /* TDRFF Flag has been got */
            tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
            if(pUartData->u32DataLen > 0U)
            {
                if(true == FCUART_HWA_GetEnStatusTxFifo(pUart))
                {
                    /* Tx fifo enable */
                    u8TxWaterMark = FCUART_HWA_GetTxWaterMark(pUart);

                    if(((pUartData->u32DataLen) >= (uint32_t)(FCUART_FIFO_DEPTH - u8TxWaterMark) ))
                    {
                        for(u8Index=0U; u8Index<(FCUART_FIFO_DEPTH - u8TxWaterMark); u8Index++)
                        {
                            FCUART_HWA_SetData(pUart, (uint8_t)(pUartData->pDatas[0U])); /* Send data */

                            /* Update pointer position */
                            (pUartData->pDatas)++;
                            (pUartData->u32DataLen)--;
                        }
                    }
                    else
                    {
                        for(u32Index=0U; u32Index<(pUartData->u32DataLen); u32Index++)
                        {
                            FCUART_HWA_SetData(pUart, (uint8_t)(pUartData->pDatas[0U])); /* Send data */

                            /* Update pointer position */
                            (pUartData->pDatas)++;
                            (pUartData->u32DataLen)--;
                        }
                    }
                }
                else
                {
                    /* Tx fifo disable */
                    FCUART_HWA_SetData(pUart, (uint8_t)(pUartData->pDatas[0U])); /* Send data */

                    /* Update pointer position */
                    (pUartData->pDatas)++;
                    (pUartData->u32DataLen)--;
                }

                if(0U == pUartData->u32DataLen)
                {
                    /* There's no new data, disable transmit empty interrupt and enable transmit complete interrupt */
                    FCUART_HWA_DisableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_TIE);
                    FCUART_HWA_EnableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_TCIE);
                }
            }
        }
    }

    return tRetVal;
}

/**
 * @brief Function to deal transmit complete
 *
 * @param u8UartIndex UART Instance
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
static FCUART_ErrorType FCUART_LL_Transmit_Complete(uint8_t u8UartIndex)
{
    FCUART_ErrorType tRetVal = (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    FCUART_Type *pUart;
    uint32_t u32TempStats;

    /* No need to check instance */
    pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];
    /* get and clear receive flag */
    u32TempStats = FCUART_HWA_GetStatus(pUart, FCUART_STAT_TCF);

    if (u32TempStats > 0U)
    {
        /* TCF Flag has been got */
        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;

        FCUART_HWA_DisableInterrupt(pUart, (uint32_t)(FCUART_INT_CTRL_TE | FCUART_INT_CTRL_TCIE));
    }
    return tRetVal;
}

/**
 * @brief Function to deal idle line
 *
 * @param u8UartIndex UART Instance
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
static FCUART_ErrorType FCUART_LL_Idle(uint8_t u8UartIndex)
{
    FCUART_ErrorType tRetVal = (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    FCUART_Type *pUart;
    uint32_t u32TempStats;

    /* get and clear receive flag */
    pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];
    /* No need to check instance */
    u32TempStats = FCUART_HWA_GetStatus(pUart, FCUART_STAT_IDLEF);

    if (u32TempStats > 0U)
    {
        /* IDLF Flag has been got */
        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
        FCUART_HWA_ClearStatus(pUart, (uint32_t)FCUART_STAT_IDLEF);
    }
    return tRetVal;
}

/**
 * @brief Receive UART data
 *
 * @param u8UartIndex UART Instance
 * @param pUartData UART receive buffer
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
static FCUART_ErrorType FCUART_LL_Receive(uint8_t u8UartIndex, FCUART_DataType *pUartData)
{
    FCUART_ErrorType tRetVal = (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    FCUART_Type *pUart;
    uint8_t u8ReadData;
    uint32_t u32TempStats;
    uint8_t  u8RxCount;
    uint8_t  u8Index;

    pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

    if ((pUartData != NULL) && (pUartData->pDatas != NULL))
    {
        /* get and clear receive flag */
        u32TempStats = FCUART_HWA_GetStatus(pUart, FCUART_STAT_RDRFF);

        if (u32TempStats > 0U)
        {
            /* RDRFF Flag has been got */
            tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;

            pUartData->u32DataLen = 0U;
            if( true == FCUART_HWA_GetEnStatusRxFifo(pUart))
            {
                /* Rx fifo enable */
                u8RxCount = FCUART_HWA_GetFifoRxCount(pUart);
                for(u8Index = 0U; u8Index < u8RxCount; u8Index++)
                {
                    u8ReadData = FCUART_HWA_GetData(pUart);
                    pUartData->pDatas[u8Index] = u8ReadData;
                    pUartData->u32DataLen++;
                }
            }
            else
            {
                /* Rx fifo disable */
                u8ReadData = FCUART_HWA_GetData(pUart);
                pUartData->pDatas[0U] = u8ReadData;
                pUartData->u32DataLen++;
            }
        }
    }

    return tRetVal;
}

/**
 * @brief Get Error Status
 *
 * @param u8UartIndex
 * @return All Error Combine, 0U is no error
 */
static uint32_t FCUART_LL_Error(uint8_t u8UartIndex)
{
    uint32_t u32RetVal;
    uint32_t u32ErrorValue;
    FCUART_Type *pUart;

    u32ErrorValue = 0U;

    pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

    /* receive overrun */
    u32RetVal = FCUART_HWA_GetStatus(pUart, FCUART_STAT_RORF);

    /* FCUART_HWA_ClearStatus(pUart, FCUART_STAT_RORF); */
    if (u32RetVal != 0U)
    {
        u32ErrorValue = (uint32_t)FCUART_ERROR_RORF;
    }

    /* noise flag */
    u32RetVal = FCUART_HWA_GetStatus(pUart, FCUART_STAT_NF);

    /*FCUART_HWA_ClearStatus(pUart, FCUART_STAT_NF);*/
    if (u32RetVal != 0U)
    {
        u32ErrorValue |= (uint32_t)FCUART_ERROR_NF;
    }

    /* Frame Error flag */
    u32RetVal = FCUART_HWA_GetStatus(pUart, FCUART_STAT_FEF);

    /*FCUART_HWA_ClearStatus(pUart, FCUART_STAT_FEF);*/
    if (u32RetVal != 0U)
    {
        u32ErrorValue |= (uint32_t)FCUART_ERROR_FEF;
    }

    /* Parity Error Flag */
    u32RetVal = FCUART_HWA_GetStatus(pUart, FCUART_STAT_PEF);

    /*FCUART_HWA_ClearStatus(pUart, FCUART_STAT_PEF);*/
    if (u32RetVal != 0U)
    {
        u32ErrorValue |= (uint32_t)FCUART_ERROR_PEF;
    }

    /* Receive Data Parity Error Flag */
    u32RetVal = FCUART_HWA_GetStatus(pUart, FCUART_STAT_RPEF);

    /*FCUART_HWA_ClearStatus(pUart, FCUART_STAT_RPEF);*/
    if (u32RetVal != 0U)
    {
        u32ErrorValue |= (uint32_t)FCUART_ERROR_RPEF;
    }

    /* Transmit Data Parity Error Flag */
    u32RetVal = FCUART_HWA_GetStatus(pUart, FCUART_STAT_TPEF);

    /*FCUART_HWA_ClearStatus(pUart, FCUART_STAT_TPEF);*/
    if (u32RetVal != 0U)
    {
        u32ErrorValue |= (uint32_t)FCUART_ERROR_TPEF;
    }

    /* clear error flags */
    FCUART_HWA_ClearStatus(pUart, u32ErrorValue);

    return u32ErrorValue;
}

/********************* Global Functions *********************/

/**
 * @brief Initial UART variables Memory
 *
 */
void FCUART_InitMemory(uint8_t u8UartIndex)
{

    s_aFCUART_ErrorNotifyTable[u8UartIndex] = NULL;

    s_aFCUART_RxNotifyTable[u8UartIndex] = NULL;

    s_aFCUART_TxEmptyNotifyTable[u8UartIndex] = NULL;

    s_aFCUART_TxCompleteNotifyTable[u8UartIndex] = NULL;

    s_aFCUART_IdleNotifyTable[u8UartIndex] = NULL;

    s_aFCUART_UartUsed[u8UartIndex] = 0U;

    /* set first state */
    s_aCurrentSequence[u8UartIndex] = FCUART_SEQUENCE_DEINIT;

}

/**
 * @brief This Function is used to initial UART instance
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pInitCfg contains clock, baud-rate, Bit Mode, parity and so on.
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Init(uint8_t u8UartIndex, FCUART_InitType *pInitCfg)
{
    FCUART_ErrorType tRetVal;
    uint32_t         u32TempBaudReg;
    uint32_t         u32TempCtrlReg;
    uint32_t         u32TempFifoReg;
    uint32_t         u32TempWatermarkReg;
    uint32_t         u32TempStat;
    uint32_t         u32TempModir;
    FCUART_Type      *pUart;
    uint32_t         u32Sbr      = 0U;
    uint32_t         u32OverSamp = 0U;
    uint32_t         u32Smb      = 0U;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);

    if ((tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK) && (s_aCurrentSequence[u8UartIndex] == FCUART_SEQUENCE_DEINIT))
    {

        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
    }
    else
    {
        tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_SEQUENCE;
    }

    if (pInitCfg != NULL)
    {
        if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
        {

            /* set not start state */
            s_aCurrentSequence[u8UartIndex] = FCUART_SEQUENCE_NOTSTART_RECEIVE;

            if(0U != pInitCfg->u32Baudrate)
            {
                u32Smb = pInitCfg->u32ClkSrcHz / pInitCfg->u32Baudrate;
            }
            else
            {
                u32Smb = 0;
                tRetVal = (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
            }

            pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

            /* process for baud-rate */
            if ((FCUART_ErrorType)FCUART_ERROR_OK == FCUART_LL_ProcessBaud(u32Smb, &u32OverSamp, &u32Sbr))
            {
                /* temporary BAUD register */
                u32TempBaudReg = (uint32_t)0U |                                 /* initial value                                                           */
                                 FCUART_BAUD_MAEN0(0U) |                        /* Match mode enable 0                                                     */
                                 FCUART_BAUD_MAEN1(0U) |                        /* Match mode enable 1                                                     */
                                 FCUART_BAUD_10BIT_MODE(0U) |                   /* 10bit mode select                                                       */
                                 FCUART_BAUD_OVR_SAMP(u32OverSamp - 1U)      |  /* Over sampling Ratio, n+1                                                */
                                 FCUART_BAUD_TDMAEN(pInitCfg->bEnTxEmptyDma) |  /* Transmitter DMA Enable                                                  */
                                 FCUART_BAUD_RDMAEN(pInitCfg->bEnRxFullDma)  |  /* Receiver Full DMA Enable                                                */
                                 FCUART_BAUD_RIDMAEN(0U) |                      /* Receiver Idle DMA Enable                                                */
                                 FCUART_BAUD_MATCH_CFG(0U) |                    /* Match Configuration                                                     */
                                 FCUART_BAUD_BEDGE_SAMP(1U) |                   /* Both Edge Sampling                                                      */
                                 FCUART_BAUD_RESYNC_DIS(0U) |                   /* Re-synchronization Disable                                              */
                                 FCUART_BAUD_LBKDIE(0U) |                       /* LIN Break Detect Interrupt Enable                                       */
                                 FCUART_BAUD_RIAEIE(0U) |                       /* RX Input Active Edge Interrupt Enable                                   */
                                 FCUART_BAUD_SBNS(pInitCfg->eStopBit) |         /* Stop Bit Number Select                                                  */
                                 FCUART_BAUD_SBR(u32Sbr);                       /* Baud Rate Modulo Divisor. baud-rate = baud clock / ((OVR_SAMP+1) * SBR) */

                /* temporary CTRL register */
                u32TempCtrlReg = (uint32_t)0U |                                /* initial value                                       */
                                 FCUART_CTRL_R8T9(0U) |                        /* Receive Bit 8 / Transmit Bit 9                       */
                                 FCUART_CTRL_R9T8(0U) |                        /* Receive Bit 9 / Transmit Bit 8                       */
                                 FCUART_CTRL_TXDIR(0U) |                       /* TXD Pin Direction in Single-Wire Mode                */
                                 FCUART_CTRL_TXINV(0U) |                       /* Transmit Data Inversion                              */
                                 FCUART_CTRL_ORIE(0U) |                        /* Overrun Interrupt Enable                             */
                                 FCUART_CTRL_NEIE(0U) |                        /* Noise Error Interrupt Enable                         */
                                 FCUART_CTRL_FEIE(0U) |                        /* Frame Error Interrupt Enable                         */
                                 FCUART_CTRL_PEIE(0U) |                        /* Parity Error Interrupt Enable                        */
                                 FCUART_CTRL_TIE(0U) |                         /* Transmit Interrupt Enable                            */
                                 FCUART_CTRL_TCIE(0U) |                        /* Transmission Complete Interrupt Enable               */
                                 FCUART_CTRL_RIE(0U) |                         /* Receiver Interrupt Enable                            */
                                 FCUART_CTRL_IIE(0U) |                         /* Idle Line Interrupt Enable                           */
                                 FCUART_CTRL_TE(0U) |                          /* Transmitter Enable                                   */
                                 FCUART_CTRL_RE(0U) |                          /* Receiver Enable                                      */
                                 FCUART_CTRL_RWC(0U) |                         /* Receiver WakeUp Control                              */
                                 FCUART_CTRL_SBK(0U) |                         /* Send Break                                           */
                                 FCUART_CTRL_M0IE(0U) |                        /* Match address 0 Interrupt Enable                     */
                                 FCUART_CTRL_M1IE(0U) |                        /* Match address 1 Interrupt Enable                     */
                                 FCUART_CTRL_7BMS(0U) |                        /* 7-Bit Mode Select                                    */
                                 FCUART_CTRL_IDLECFG(pInitCfg->eIdleCharNum) | /* Idle Configuration 2^n bytes time no data entry IDLE */
                                 FCUART_CTRL_LOOPMS(0U) |                      /* Loop Mode Select                                     */
                                 FCUART_CTRL_WAITEN(0U) |                      /* WAIT Enable                                          */
                                 FCUART_CTRL_RXSRC(0U) |                       /* Receiver Source Select                               */
                                 FCUART_CTRL_BMSEL(pInitCfg->eBitMode) |       /* 9-Bit or 8-Bit Mode Select                           */
                                 FCUART_CTRL_RSWMS(0U) |                       /* Receiver WakeUp Method Select                        */
                                 FCUART_CTRL_ITS(pInitCfg->eIdleStart) |       /* Idle Line Type Select                                */
                                 FCUART_CTRL_PE(pInitCfg->bParityEnable) |     /* Parity Enable                                        */
                                 FCUART_CTRL_PT(pInitCfg->eParityType);        /* Parity Type                                          */

                /* temporary FIFO register */
                u32TempFifoReg = (uint32_t)0U |                           /* initial value                              */
                                 FCUART_FIFO_TXEMPTY(0U) |                /* Transmit Buffer/FIFO Empty                 */
                                 FCUART_FIFO_RXEMPTY(0U) |                /* Receive Buffer/FIFO Empty                  */
                                 FCUART_FIFO_TXOF(0U) |                   /* Transmitter Buffer Overflow Flag           */
                                 FCUART_FIFO_RXUF(0U) |                   /* Receiver Buffer Underflow Flag             */
                                 FCUART_FIFO_TXFLUSH(1U) |                /* Transmit FIFO/Buffer Flush                 */
                                 FCUART_FIFO_RXFLUSH(1U) |                /* Receive FIFO/Buffer Flush                  */
                                 FCUART_FIFO_RXIDEN(pInitCfg->eFifoRxIdleCharNum) |                 /* Receiver Idle Empty Enable                 */
                                 FCUART_FIFO_TXOFIE(0U) |                 /* Transmit FIFO Overflow Interrupt Enable    */
                                 FCUART_FIFO_RXUFIE(0U) |                 /* Receive FIFO Underflow Interrupt Enable    */
                                 FCUART_FIFO_TXFEN(pInitCfg->bEnTxFifo) | /* Transmit FIFO Enable                       */
                                 FCUART_FIFO_TXFIFODEP(1U) |              /* Transmit FIFO Buffer Depth                 */
                                 FCUART_FIFO_RXFEN(pInitCfg->bEnRxFifo) | /* Receive FIFO Enable, enable RX FIFO        */
                                 FCUART_FIFO_RXFIFODEP(1U);               /* Receive FIFO Buffer Depth     */

                /* temporary WATERMARK register */
                u32TempWatermarkReg = (uint32_t)0U |                                         /* initial value                                          */
                                      FCUART_WATERMARK_RXCOUNT(0U) |                         /* Receive Counter                                         */
                                      FCUART_WATERMARK_RXWATER(pInitCfg->u8RxFifoWaterMark) | /* Receive WaterMark, receive n-1 request interrupt or DMA */
                                      FCUART_WATERMARK_TXCOUNT(0U) |                         /* Transmit Counter                                        */
                                      FCUART_WATERMARK_TXWATER(pInitCfg->u8TxFifoWaterMark);  /* Transmit WaterMark                                      */

              /* temporary MODIR register */
                u32TempModir = (uint32_t)0U                 |   /* initial value                                          */
                                FCUART_MODIR_RXRTSCFG(0U)    |   /* Receive RTS Configuration                              */
                                FCUART_MODIR_TXCTSSRC(0U)    |   /* Transmit CTS Source                                    */
                                FCUART_MODIR_TXCTSCFG(0U)    |   /* Transmit CTS Configuration                             */
                                FCUART_MODIR_RXRTSEN(0U)     |   /* Receiver Request-to-Send Enable                        */
                                FCUART_MODIR_TXRTSPOL(0U)    |   /* Transmitter Request-to-Send Polarity                   */
                                FCUART_MODIR_TXRTSEN(0U)     |   /* Transmitter Request-to-Send Enable                     */
                                FCUART_MODIR_TXCTSEN(0U);        /* Transmitter Clear-to-Send Enable                       */

            /* write register with temporary data */
                FCUART_HWA_SetBaud(pUart, u32TempBaudReg); /* 0x19000008; */
                FCUART_HWA_SetFifo(pUart, u32TempFifoReg);
                FCUART_HWA_SetWaterMark(pUart, u32TempWatermarkReg);
                FCUART_HWA_SetModir(pUart, u32TempModir);

                FCUART_HWA_SetCtrl(pUart, u32TempCtrlReg);

                /* clear all status */
                u32TempStat = FCUART_HWA_GetSTAT(pUart);
                FCUART_HWA_WriteClearSTAT(pUart, u32TempStat);
                FCUART_HWA_ClearFIFOErrorFlag(pUart);

                /* instance used */
                s_aFCUART_UartUsed[u8UartIndex] = 1U;
                s_aFCUART_TransmitTimeout[u8UartIndex] = pInitCfg->u32TransmitTimeout > 0U ? pInitCfg->u32TransmitTimeout : 3000U;
            }
            else
            {
                tRetVal |= (FCUART_ErrorType)FCUART_ERROR_FAILED;
            }
        }
    }
    else
    {
        tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    }

    return tRetVal;
}

/**
 * @brief This Function is used to de-initial UART instance
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_DeInit(uint8_t u8UartIndex)
{
    FCUART_ErrorType tRetVal;
    FCUART_Type *pUart;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);

    if ((tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK) && (s_aCurrentSequence[u8UartIndex] > FCUART_SEQUENCE_DEINIT))
    {

        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
    }
    else
    {
        tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_SEQUENCE;
    }

    if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {
        /* set deinit state */
        s_aCurrentSequence[u8UartIndex] = FCUART_SEQUENCE_DEINIT;
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

        FCUART_HWA_SetSoftWareReset(pUart);
    }

    return tRetVal;
}

/**
 * @brief This Function is used to set UART interrupt
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pIntCfg contains callback functions
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_SetInterrupt(uint8_t u8UartIndex, FCUART_InterruptType *pInterruptCfg)
{
    FCUART_ErrorType tRetVal;
    FCUART_Type *pUart;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);

    if ((tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK) && (s_aCurrentSequence[u8UartIndex] == FCUART_SEQUENCE_NOTSTART_RECEIVE))
    {
        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
    }
    else
    {
        tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_SEQUENCE;
    }

    if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {
        if (pInterruptCfg != NULL)
        {
            pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

            /* error interrupt */
            if (true == pInterruptCfg->bEnErrorInterrupt)
            {
                FCUART_HWA_EnableInterrupt(pUart, (uint32_t)(FCUART_INT_CTRL_ORIE |FCUART_INT_CTRL_NEIE |FCUART_INT_CTRL_FEIE |FCUART_INT_CTRL_PEIE));

                s_aFCUART_ErrorNotifyTable[u8UartIndex] = pInterruptCfg->pErrorNotify;
            }
            else
            {
                FCUART_HWA_DisableInterrupt(pUart, (uint32_t)(FCUART_INT_CTRL_ORIE |FCUART_INT_CTRL_NEIE |FCUART_INT_CTRL_FEIE |FCUART_INT_CTRL_PEIE));
            }

            /* receive interrupt */
            if (true == pInterruptCfg->bEnRxInterrupt)
            {
                /* check buffer point if it is null */
                if (pInterruptCfg->pRxBuf != NULL)
                {
                    FCUART_HWA_EnableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_RIE);

                    s_aFCUART_RxMsg[u8UartIndex] = pInterruptCfg->pRxBuf;
                    s_aFCUART_RxNotifyTable[u8UartIndex] = pInterruptCfg->pRxNotify;
                }
                else
                {
                    tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
                }

            }
            else
            {
                FCUART_HWA_DisableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_RIE);
            }

            /* Transfer interrupt */
            if (true == pInterruptCfg->bEnTxInterrupt)
            {
                /* check buffer point if it is null */
                if (pInterruptCfg->pTxBuf != NULL)
                {
                    FCUART_HWA_EnableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_TIE);
                    s_aFCUART_TxMsg[u8UartIndex] = pInterruptCfg->pTxBuf;
                    s_aFCUART_TxEmptyNotifyTable[u8UartIndex] = pInterruptCfg->pTxEmptyNotify;
                    s_aFCUART_TxCompleteNotifyTable[u8UartIndex] = pInterruptCfg->pTxCompleteNotify;
                }
                else
                {
                    tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
                }

            }
            else
            {
                FCUART_HWA_DisableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_TIE);
            }

            /* Idle interrupt */
            if (true == pInterruptCfg->bEnIdleInterrupt)
            {
                FCUART_HWA_EnableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_IIE);
                s_aFCUART_IdleNotifyTable[u8UartIndex] = pInterruptCfg->pIdleNotify;
            }
            else
            {
                FCUART_HWA_DisableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_IIE);
            }
        }
        else
        {
            tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
        }
    }
    else
    {
        /* No deal with */
    }

    return tRetVal;
}

/**
 * @brief This Function is used to set UART WakeUp
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pWakeupCfg contains UART wake-up parameters
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_SetWakeup(uint8_t u8UartIndex, FCUART_WakeupType *pWakeupCfg)
{
    FCUART_ErrorType tRetVal;
    FCUART_Type *pUart;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);

    if ((tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK) && (s_aCurrentSequence[u8UartIndex] == FCUART_SEQUENCE_NOTSTART_RECEIVE))
    {
        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
    }
    else
    {
        tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_SEQUENCE;
    }

    if (pWakeupCfg != NULL)
    {
        if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
        {
            pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

            /*
             *  RWC   MATCH0|MATCH1   MATCH_CFG  [RSWMS,RWUID]    Receiver Wakeup
                0    0                X           X               Normal operation
                1    0                00          00              Receiver wakeup on idle line, IDLE flag not set
                1    0                00          01              Receiver wakeup on idle line, IDLE flag set
                1    0                00          10              Receiver wakeup on address mark
                1    1                11          10              Receiver wakeup on address match
                0    1                00          X0              Address mark address match, IDLE flag not set for discarded characters
                0    1                00          X1              Address mark address match, IDLE flag set for discarded characters
                0    1                01          X0              Idle line address match
                0    1                10          X0              Address match on and address match off, IDLE flag not set for discarded characters
                0    1                10          X1              Address match on and address match off, IDLE flag set for discarded characters
             *
             */

            FCUART_HWA_AttachCtrl(pUart, FCUART_CTRL_RWC_MASK | FCUART_CTRL_RSWMS_MASK);     /* WakeUp enable and method select address-mark */
            FCUART_HWA_AttachBaud(pUart, FCUART_BAUD_MATCH_CFG(3U) | FCUART_BAUD_MAEN0(1U)); /* match0 data                                  */
            FCUART_HWA_AttachMatch(pUart, FCUART_MATCH_MATCH0(pWakeupCfg->u32WakeUpData));   /* set wake-up data*/
        }
    }
    else
    {
        tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    }

    return tRetVal;
}

/**
 * @brief This Function is used to start receiving
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_StartReceive(uint8_t u8UartIndex)
{
    FCUART_ErrorType tRetVal;
    FCUART_Type *pUart;

    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);

    if((FCUART_ErrorType)FCUART_ERROR_OK == tRetVal)
    {
        if (s_aCurrentSequence[u8UartIndex] == FCUART_SEQUENCE_NOTSTART_RECEIVE)
        {
            tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
            /* set started receive state */
            s_aCurrentSequence[u8UartIndex] = FCUART_SEQUENCE_START_RECEIVE;

            pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

            /* start receive */
            FCUART_HWA_SetRxTransfer(pUart, true);
        }
        else
        {
            tRetVal = (FCUART_ErrorType)FCUART_ERROR_INVALID_SEQUENCE;
        }
    }
    else
    {
        tRetVal = (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    }

    return tRetVal;
}

/**
 * @brief This Function is used to stop receiving
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_StopReceive(uint8_t u8UartIndex)
{
    FCUART_ErrorType tRetVal;
    FCUART_Type *pUart;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);

    if ((tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK) && ((s_aCurrentSequence[u8UartIndex] == FCUART_SEQUENCE_START_RECEIVE) || (s_aCurrentSequence[u8UartIndex] == FCUART_SEQUENCE_NOTSTART_RECEIVE)))
    {

        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
    }
    else
    {
        tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_SEQUENCE;
    }

    if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {
        /* set stop state */
        s_aCurrentSequence[u8UartIndex] = FCUART_SEQUENCE_NOTSTART_RECEIVE;
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

        /* stop receive */
        FCUART_HWA_SetRxTransfer(pUart, false);
    }

    return tRetVal;
}

/**
 * @brief This Function is used to start transmit through interrupt
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_StartTransmit(uint8_t u8UartIndex)
{
    FCUART_ErrorType tRetVal;
    FCUART_Type *pUart;

    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);

    if((FCUART_ErrorType)FCUART_ERROR_OK == tRetVal)
    {

        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;

        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

        /* start transmit */
        FCUART_HWA_SetTxTransfer(pUart, true);

        if(false == FCUART_GetInterruptMode(u8UartIndex, (uint32_t)FCUART_INT_CTRL_TIE))
        {
            FCUART_HWA_EnableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_TIE);
        }
    }
    else
    {
        tRetVal = (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    }

    return tRetVal;
}

/**
 * @brief This Function is used to stop transmitting
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_StopTransmit(uint8_t u8UartIndex)
{
    FCUART_ErrorType tRetVal;
    FCUART_Type *pUart;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);

    if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {

        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

        /* stop receive */
        FCUART_HWA_SetTxTransfer(pUart, false);
    }
    else
    {
        /* No deal with */
    }

    return tRetVal;
}

/**
 * @brief This Function is used to transmit UART data
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pUartData contains UART data and length
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Transmit(uint8_t u8UartIndex, FCUART_DataType *pUartData)
{
    FCUART_ErrorType tRetVal;

    FCUART_Type *pUart;
    uint8_t *pData;
    uint32_t u32DataLen;
    uint8_t  u8Index;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);

    if ((tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK) &&((s_aCurrentSequence[u8UartIndex] == FCUART_SEQUENCE_START_RECEIVE) || (s_aCurrentSequence[u8UartIndex] == FCUART_SEQUENCE_NOTSTART_RECEIVE)))
    {

        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
    }
    else
    {
        tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_SEQUENCE;
    }

    if (pUartData != NULL)
    {
        if (pUartData->pDatas != NULL)
        {
            if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
            {
                pData = pUartData->pDatas;
                u32DataLen = pUartData->u32DataLen;
                pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

                for (u8Index = 0U; u8Index < u32DataLen; u8Index++)
                {
                    tRetVal |= FCUART_LL_Transmit_Char(pUart, pData[u8Index], s_aFCUART_TransmitTimeout[u8UartIndex]);

                    if (tRetVal != (FCUART_ErrorType)FCUART_ERROR_OK)
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
        }
    }
    else
    {
        tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    }

    return tRetVal;
}

/**
 * @brief Get Stat Flag
 *
 * @param u8UartIndex  UART instance
 * @param eStatusType  stat type
 * @return FCUART STAT status flag
 */
uint32_t FCUART_GetStatus(uint8_t u8UartIndex, FCUART_StatType eStatusType)
{
    FCUART_ErrorType tRetVal;
    FCUART_Type *pUart;
    uint32_t u32RetVal;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);

    if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];
        u32RetVal = FCUART_HWA_GetStatus(pUart, eStatusType);
    }
    else
    {
        u32RetVal = 0U;
    }

    return u32RetVal;
}

/**
 * @brief This Function is used to receive data when polling (not used when rx interrupt enabled)
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pRxMsg is data buffer address, and pDatas need to be initialed with external buffer
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Receive_Polling(uint8_t u8UartIndex, FCUART_DataType *pRxMsg)
{
    FCUART_ErrorType tRetVal;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);

    if ((tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK) && (s_aCurrentSequence[u8UartIndex] == FCUART_SEQUENCE_START_RECEIVE))
    {

        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
    }
    else
    {
        tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_SEQUENCE;
    }

    if (pRxMsg != NULL)
    {
        if (pRxMsg->pDatas != NULL)
        {
            if (s_aFCUART_UartUsed[u8UartIndex] == 1U)
            {
                tRetVal = FCUART_LL_Receive(u8UartIndex, pRxMsg);
            }
        }
        else
        {
            tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
        }
    }
    else
    {
        tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    }

    return tRetVal;
}

/**
 * @brief This Function is used to get error when polling (not used when error interrupt enabled)
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pErrorValue is error value
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Error_Polling(uint8_t u8UartIndex, uint32_t *pErrorValue)
{
    FCUART_ErrorType tRetVal;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);

    if ((tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK) && (s_aCurrentSequence[u8UartIndex] >= FCUART_SEQUENCE_NOTSTART_RECEIVE))
    {

        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
    }
    else
    {
        tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_SEQUENCE;
    }

    if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {
        if (s_aFCUART_UartUsed[u8UartIndex] == 1U)
        {
            /* check error */
            *pErrorValue = FCUART_LL_Error(u8UartIndex);
        }
        else
        {
            tRetVal = (FCUART_ErrorType)FCUART_ERROR_FAILED;
        }
    }

    return tRetVal;
}

/**
 * @brief This Function is used to enable fcuart loop mode
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param bStatus  enable/disable status of loop mode
 * @return FCUART_ERROR_OK is ok, others are not ok
 *
 */
FCUART_ErrorType FCUART_SetLoopMode(uint8_t u8UartIndex, bool bStatus)
{
    FCUART_Type *pUart;
    FCUART_ErrorType tRetVal;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);

    if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

        if (true == bStatus)
        {
            FCUART_HWA_EnableLoopMode(pUart);
        }
        else
        {
            FCUART_HWA_DisableLoopMode(pUart);
        }
    }
    else
    {
        /* No deal with */
    }
    return tRetVal;
}

/**
 * @brief This Function is used to send 9 bits data
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param u16Data  data to send
 * @return FCUART_ERROR_OK is ok, others are not ok
 *
 */
FCUART_ErrorType FCUART_SendData_9Bits(uint8_t u8UartIndex, uint16_t u16Data)
{
    FCUART_Type *pUart;
    FCUART_ErrorType tRetVal;
    uint8_t u8SingleBit_8;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);
    if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

        u8SingleBit_8  = (uint8_t)((u16Data >> 8U) & 1U);

        /* Set bit8 */
        FCUART_HWA_SetR9T8(pUart, u8SingleBit_8);
        /* Set 0 ~ 7 bits */
        FCUART_HWA_SetData(pUart, (uint8_t)u16Data);
    }
    else
    {
        /* No deal with */
    }
    return tRetVal;

}

/**
 * @brief This Function is used to Get 9 bits data
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pData  pointer to data
 * @return FCUART_ERROR_OK is ok, others are not ok
 *
 */
FCUART_ErrorType FCUART_GetData_9Bits(uint8_t u8UartIndex, uint16_t *pData)
{
    FCUART_Type *pUart;
    FCUART_ErrorType tRetVal;
    uint8_t u8SingleBit_8;
    uint8_t u8Temp;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);
    if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];
        /* Get bit8 */
        u8SingleBit_8  = FCUART_HWA_GetR8T9(pUart);
        /* Get 0 ~ 7 bits */
        u8Temp  = FCUART_HWA_GetData(pUart);
        /* Get 0 ~ 8 bits */
        *pData = (((uint16_t)u8SingleBit_8 << 8U) | (uint16_t)u8Temp);
    }
    else
    {
        /* No deal with */
    }
    return tRetVal;

}

/**
 * @brief This Function is used to send 10 bits data
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param u16Data  data to send
 * @return FCUART_ERROR_OK is ok, others are not ok
 *
 */
FCUART_ErrorType FCUART_SendData_10Bits(uint8_t u8UartIndex, uint16_t u16Data)
{
    FCUART_Type *pUart;
    FCUART_ErrorType tRetVal;
    uint8_t u8SingleBit_8;
    uint8_t u8SingleBit_9;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);
    if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

        u8SingleBit_8   = (uint8_t)((u16Data >> 8U) & 1U);
        u8SingleBit_9  = (uint8_t)((u16Data >> 9U) & 1U);

        /* Set bit8 */
        FCUART_HWA_SetR9T8(pUart, u8SingleBit_8);
        /* Set bit9 */
        FCUART_HWA_SetR8T9(pUart, u8SingleBit_9);
        /* Set 0 ~ 7 bits */
        FCUART_HWA_SetData(pUart, (uint8_t)u16Data);
    }
    else
    {
        /* No deal with */
    }
    return tRetVal;

}

/**
 * @brief This Function is used to Get 10 bits data
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pData  pointer to data
 * @return FCUART_ERROR_OK is ok, others are not ok
 *
 */
FCUART_ErrorType FCUART_GetData_10Bits(uint8_t u8UartIndex, uint16_t *pData)
{
    FCUART_Type *pUart;
    FCUART_ErrorType tRetVal;
    uint8_t u8SingleBit_8;
    uint8_t u8SingleBit_9;
    uint8_t u8Temp;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);
    if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];
        /* Get bit8 */
        u8SingleBit_8  = FCUART_HWA_GetR8T9(pUart);
        /* Get bit9 */
        u8SingleBit_9  = FCUART_HWA_GetR9T8(pUart);
        /* Get 0 ~ 7 bits */
        u8Temp  = FCUART_HWA_GetData(pUart);
        /* Get 0 ~ 9 bits */
        *pData = (((uint16_t)u8SingleBit_8 << 8U) | ((uint16_t)u8SingleBit_9 << 9U) | (uint16_t)u8Temp);
    }
    else
    {
        /* No deal with */
    }
    return tRetVal;

}

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
                                             )
{
    FCUART_Type *pUart;
    FCUART_ErrorType tRetVal;

    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);
    if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

        FCUART_HWA_SetBitMode(pUart, eBitMode);
        FCUART_HWA_SetStopBit(pUart, eStopBit);
        FCUART_HWA_SetParity(pUart, eParityType, bParityEnable);
    }
    else
    {
        /* No deal with */
    }
    return tRetVal;
}

/**
 * @brief This Function is used to Get current interrupt mode
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param u32Data  Interrupt type to get
 * @return true/false
 *
 */
bool FCUART_GetInterruptMode(uint8_t u8UartIndex, uint32_t u32Data)
{
    FCUART_ErrorType tTempVal;
    bool bRetVal;
    FCUART_Type *pUart;
    uint32_t u32CtrlRegData;

    /* check parameter */
    tTempVal = FCUART_LL_CheckInstance(u8UartIndex);
    if (tTempVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

        u32CtrlRegData = FCUART_HWA_GetCtrl(pUart);
        bRetVal = ((u32CtrlRegData & u32Data) > 0U ) ? true : false;
    }
    else
    {
        bRetVal = false;
    }

    return bRetVal;
}

/**
 * @brief This Function is used to assign data to send through interrupt
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param pData  data pointer
 * @param u32Length data length to send
 * @return FCUART_ERROR_OK is ok, others are not ok
 *
 */
FCUART_ErrorType FCUART_AssignTxInterruptData(uint8_t u8UartIndex, uint8_t * pData, uint32_t u32Length)
{
    FCUART_ErrorType tTempVal;
    /* check parameter */
    tTempVal = FCUART_LL_CheckInstance(u8UartIndex);
    if (tTempVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {
        if(pData != NULL)
        {
            s_aFCUART_TxMsg[u8UartIndex]->pDatas     = pData;
            s_aFCUART_TxMsg[u8UartIndex]->u32DataLen = u32Length;
        }
        else
        {
            tTempVal = (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
        }
    }
    else
    {
        /* No deal with */
    }

    return tTempVal;
}


/* ################################################################################## */
/* ############################## Interrupt Services ################################ */
/**
 * @brief This Function is used to deal with FCUART TxRx interrupt
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 *
 */
void FCUARTN_RxTx_IRQHandler(uint8_t u8UartIndex)
{
    FCUART_ErrorType tTempVal;
    FCUART_DataType *pRxMsgList;
    FCUART_DataType *pTxMsgList;
    uint32_t u32ErrorValue;
    uint32_t u32CtrlRegData;

    //Do not check instance because it should be checked before
    u32CtrlRegData = FCUART_HWA_GetCtrl((FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex]);

    /* Handle receive interrupt */
    if(((uint32_t)FCUART_INT_CTRL_RIE) == (u32CtrlRegData & ((uint32_t)FCUART_INT_CTRL_RIE)))
    {
        /* get buffer point and it stored when called SetInterrupt */
        pRxMsgList = s_aFCUART_RxMsg[u8UartIndex];
        /* check pUart receive data */
        tTempVal = FCUART_LL_Receive(u8UartIndex, pRxMsgList);

        /* check buffer valid */
        if ( (tTempVal == (FCUART_ErrorType)FCUART_ERROR_OK) && (pRxMsgList != NULL))
        {
            if (s_aFCUART_RxNotifyTable[u8UartIndex] != NULL)
            {
                s_aFCUART_RxNotifyTable[u8UartIndex](u8UartIndex, pRxMsgList);
            }
        }
    }

    /* Handle transmit interrupt */
    if(((uint32_t)FCUART_INT_CTRL_TIE) == (u32CtrlRegData & ((uint32_t)FCUART_INT_CTRL_TIE)))
    {
        /* get buffer point and it stored when called SetInterrupt */
        pTxMsgList = s_aFCUART_TxMsg[u8UartIndex];
        /* transfer data */
        tTempVal = FCUART_LL_Transmit_Empty(u8UartIndex, pTxMsgList);

        if((tTempVal == (FCUART_ErrorType)FCUART_ERROR_OK)  && (pTxMsgList != NULL))
        {
            if (s_aFCUART_TxEmptyNotifyTable[u8UartIndex] != NULL)
            {
                s_aFCUART_TxEmptyNotifyTable[u8UartIndex](u8UartIndex, pTxMsgList);
            }
        }
    }

    /* Handle transmit complete interrupt */
    if(((uint32_t)FCUART_INT_CTRL_TCIE) == (u32CtrlRegData & ((uint32_t)FCUART_INT_CTRL_TCIE)))
    {
        tTempVal = FCUART_LL_Transmit_Complete(u8UartIndex);

        if ((tTempVal == (FCUART_ErrorType)FCUART_ERROR_OK) && (s_aFCUART_TxCompleteNotifyTable[u8UartIndex] != NULL))
        {
            s_aFCUART_TxCompleteNotifyTable[u8UartIndex](u8UartIndex, NULL);
        }
    }

    /* Handle idle interrupt */
    if(((uint32_t)FCUART_INT_CTRL_IIE) == (u32CtrlRegData & ((uint32_t)FCUART_INT_CTRL_IIE)))
    {
        tTempVal = FCUART_LL_Idle(u8UartIndex);
        if ((tTempVal == (FCUART_ErrorType)FCUART_ERROR_OK) && (s_aFCUART_IdleNotifyTable[u8UartIndex] != NULL))
        {
            s_aFCUART_IdleNotifyTable[u8UartIndex](u8UartIndex);
        }
    }

    /* Handle error interrupt */
    if(0U != (u32CtrlRegData & ((uint32_t)(FCUART_INT_CTRL_ORIE | FCUART_INT_CTRL_NEIE | FCUART_INT_CTRL_FEIE | FCUART_INT_CTRL_PEIE))))
    {
        /* check error */
        u32ErrorValue = FCUART_LL_Error(u8UartIndex);

        if ((u32ErrorValue != 0U) && (s_aFCUART_ErrorNotifyTable[u8UartIndex] != NULL))
        {
            s_aFCUART_ErrorNotifyTable[u8UartIndex](u8UartIndex, u32ErrorValue);
        }

        PROCESS_UNUSED_VAR(u32ErrorValue)
    }
}

/************************ Uart Print Library ************************/

/**
 * @brief This Function is used to print ASCII char from UART
 *
 * @param u8UartIndex is UART instance, 0U..(FCUART_INSTANCE_COUNT-1U)
 * @param fmt is char format
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Printf(uint8_t u8UartIndex, char *fmt, ...)
{
    FCUART_Type *pUart;
    FCUART_ErrorType tRetVal;
    const char *pStr;
    int i32Temp;
    unsigned char TxData;
    uint8_t u8Number;
    uint8_t u8LenthNumber = 4U;
    char TempBuffer[16];
    va_list ap;

    va_start(ap, fmt);
    /* check parameter */
    tRetVal = FCUART_LL_CheckInstance(u8UartIndex);

    if ((tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK) && ((s_aCurrentSequence[u8UartIndex] == FCUART_SEQUENCE_START_RECEIVE) || (s_aCurrentSequence[u8UartIndex] == FCUART_SEQUENCE_NOTSTART_RECEIVE)))
    {

        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
    }
    else
    {
        tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_SEQUENCE;
    }

    if (tRetVal == (FCUART_ErrorType)FCUART_ERROR_OK)
    {
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

        while (*fmt != (char)0)
        {
            /* Escape character */
            if ((*fmt) == ESCAPE_CHARACTER)
            {
                switch (*(++fmt))
                {
                case 'r':
                {
                    TxData = ENTER;
                    tRetVal = FCUART_LL_Transmit_Char(pUart, TxData, s_aFCUART_TransmitTimeout[u8UartIndex]);
                    fmt++;
                }
                break;

                case 'n':
                {
                    TxData = NEW_LINE;
                    tRetVal = FCUART_LL_Transmit_Char(pUart, TxData, s_aFCUART_TransmitTimeout[u8UartIndex]);
                    fmt++;
                }
                break;

                default:
                    fmt++;
                    break;
                }
            }
            else if ((*fmt) == (char)'%')
            {
                switch (*(++fmt))
                {
                case 's':
                {
                    pStr = va_arg(ap, const char *);
                    for (; *pStr; pStr++)
                    {
                        tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)pStr), s_aFCUART_TransmitTimeout[u8UartIndex]);
                    }
                    fmt++;
                }
                break;

                case 'd':
                {
                    i32Temp = va_arg(ap, int);
                    if (0U == FCUART_Int2Char(i32Temp, TempBuffer, UART_PRINT_RADIX_DEC, false))
                    {
                        for (pStr = TempBuffer; *pStr; pStr++)
                        {
                            tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)pStr), s_aFCUART_TransmitTimeout[u8UartIndex]);
                        }
                    }
                    fmt++;
                }
                break;

                case 'x':
                {
                    i32Temp = va_arg(ap, int);
                    if (0U == FCUART_Int2Char(i32Temp, TempBuffer, UART_PRINT_RADIX_HEX, false))
                    {
                        for (pStr = TempBuffer; *pStr; pStr++)
                        {
                            tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)pStr), s_aFCUART_TransmitTimeout[u8UartIndex]);
                        }
                    }
                    fmt++;
                }
                break;

                case 'X':
                {
                    i32Temp = va_arg(ap, int);
                    if (0U == FCUART_Int2Char(i32Temp, TempBuffer, UART_PRINT_RADIX_HEX, true))
                    {
                        for (pStr = TempBuffer; *pStr; pStr++)
                        {
                            tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)pStr), s_aFCUART_TransmitTimeout[u8UartIndex]);
                        }
                    }
                    fmt++;
                }
                break;

                case '.':
                {
                    u8Number = (uint8_t)(*(++fmt) - '0');
                    if ((*(++fmt)) == 'f')
                    {
                        double num = va_arg(ap, double);
                        if (0U == FCUART_Float2Char(num, TempBuffer, u8Number))
                        {
                            for (pStr = TempBuffer; *pStr; pStr++)
                            {
                                tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)pStr), s_aFCUART_TransmitTimeout[u8UartIndex]);
                            }
                        }
                        fmt++;
                    }
                }
                break;

                case 'f':
                {
                    double num = va_arg(ap, double);
                    if (0U == FCUART_Float2Char(num, TempBuffer, u8LenthNumber))
                    {
                        for (pStr = TempBuffer; *pStr; pStr++)
                        {
                            tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)pStr), s_aFCUART_TransmitTimeout[u8UartIndex]);
                        }
                    }
                    fmt++;
                }
                break;

                default:
                    fmt++;
                    break;
                }
            }
            else
            {
                tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)fmt), s_aFCUART_TransmitTimeout[u8UartIndex]);

                if (tRetVal != FCUART_ERROR_OK)
                {
                    break;
                }

                fmt++;
            }
        }
    }

    va_end(ap);

    return tRetVal;
}

/**
 * @brief  Convert integer to char
 *
 * @param  i32Value
 * @param  pOutStr
 * @param  eRadix
 * @return 0 is ok
 */
static uint8_t FCUART_Int2Char(int i32Value, char *pOutStr, UART_PrintIntType eRadix, bool bHexUpper)
{
    uint8_t u8Retval;
    char aCharListUpper[] = "0123456789ABCDEF";
    char aCharListLower[] = "0123456789abcdef";
    char aNumList[]       = "0123456789";
    char *pCharList;
    uint32_t u32Temp;
    uint8_t u8Index = 0U;
    uint8_t u8ValueStart = 0U;
    char Temp = 0;
    uint32_t j;

    if (NULL == pOutStr)
    {
        u8Retval = 1U;
    }
    else
    {
        u8Retval = 0U;
        if ((UART_PRINT_RADIX_DEC == eRadix) && (i32Value < 0))
        {
            // Decimal and negative
            u32Temp = (uint32_t)(0 - i32Value);
            pOutStr[u8Index++] = '-';
            u8ValueStart = 1U;
            pCharList = aNumList;
        }
        else
        {
            if (true == bHexUpper)
            {
                pCharList = aCharListUpper;
            }
            else
            {
                pCharList = aCharListLower;
            }
            u32Temp = (uint32_t)i32Value;
        }

        // Data is converted to a string and stored in reverse order
        do
        {
            pOutStr[u8Index++] = pCharList[u32Temp % (uint8_t)eRadix];
            u32Temp /= (uint8_t)eRadix;
        } while (u32Temp);

        pOutStr[u8Index] = '\0';

        // Convert the string with reverse order to positive
        for (j = u8ValueStart; j < (u8Index + u8ValueStart) / 2U; j++)
        {
            Temp = pOutStr[j];
            pOutStr[j] = pOutStr[u8Index - j - 1U + u8ValueStart];
            pOutStr[u8Index - j - 1U + u8ValueStart] = Temp;
        }
    }
    return u8Retval;
}

/**
 * @brief  Convert float to char
 *
 * @param  Value
 * @param  pOutStr
 * @param  U32Eps
 * @return 0 is ok
 */
static uint8_t FCUART_Float2Char(double Value, char *pOutStr, uint32_t u32Eps)
{
    uint32_t u32Integer;
    double Decimal;
    char aCharList[] = "0123456789";
    uint8_t u8ValueStart = 0U;
    uint32_t u32TempCnt = 1U;
    char Temp = 0;
    double TempFactor = 0.1;
    uint8_t u8Index = 0U;
    uint32_t u32TempDecimal;
    uint8_t u8Retval;
    uint32_t j;

    if (NULL == pOutStr)
    {
        u8Retval = 1U;
    }
    else
    {
        u8Retval = 0U;
        // Extract integer and decimal from the input number
        if (Value < FLOAT_ZERO)
        {
            Decimal = (double)((int32_t)Value - Value);
            u32Integer = (uint32_t)(0.0 - Value);
            pOutStr[u8Index++] = '-';
            u8ValueStart = 1U;
        }
        else
        {
            u32Integer = (uint32_t)Value;
            Decimal = (double)(Value - u32Integer);
        }
        // The integer part of the data is converted into a string and stored in reverse order
        do
        {
            pOutStr[u8Index++] = aCharList[u32Integer % 10U];
            u32Integer /= 10U;
        } while (0U != u32Integer);

        pOutStr[u8Index] = '\0';

        // Convert the string with reverse order to positive
        for (j = u8ValueStart; j < (u8Index + u8ValueStart) / 2U; j++)
        {
            Temp = pOutStr[j];
            pOutStr[j] = pOutStr[u8Index - j - 1U + u8ValueStart];
            pOutStr[u8Index - j - 1U + u8ValueStart] = Temp;
        }

        // Accuracy problem, preventing input 1.2 and output 1.19
        for (j = 0U; j <= u32Eps; j++)
        {
            TempFactor *= 0.1;
        }
        Decimal += TempFactor;

        for (j = 0; j < u32Eps; j++)
        {
            Decimal *= (double)10.0;
            u32TempCnt *= 10U;
        }

        u32TempDecimal = (uint32_t)Decimal;
        pOutStr[u8Index++] = '.';
        for (j = 0; j < u32Eps; j++)
        {
            u32TempCnt /= 10U;
            if (0U != u32TempCnt)
            {
                pOutStr[u8Index++] = u32TempDecimal / u32TempCnt + '0';
                u32TempDecimal %= u32TempCnt;
            }
        }
        pOutStr[u8Index] = '\0';
    }
    return u8Retval;
}
