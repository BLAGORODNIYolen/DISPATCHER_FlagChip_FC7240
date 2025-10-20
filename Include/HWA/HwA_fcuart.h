/**
 * @file HwA_fcuart.h
 * @author Flagchip
 * @brief FC7xxx FCUart register API
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

#ifndef _HWA_FCUART_H_
#define _HWA_FCUART_H_

#include "device_header.h"


/**
 * @addtogroup HwA_fcuart
 * @{
 */


/********* Local typedef ************/

/**
 * @brief UART STAT register flag
 *
 */
typedef enum
{
    FCUART_STAT_LBKDIF = (int32_t)FCUART_STAT_LBKDIF_MASK, /**< FCUART_STAT_LBKDIF  LIN Break Detect Interrupt Flag,    w1c */
    FCUART_STAT_RPAEIF = (int32_t)FCUART_STAT_RPAEIF_MASK, /**< FCUART_STAT_RPAEIF  RXD Pin Active Edge Interrupt Flag, w1c */
    FCUART_STAT_MSBF   = (int32_t)FCUART_STAT_MSBF_MASK,   /**< FCUART_STAT_MSBF    MSB First,                          RW  */
    FCUART_STAT_RXINV  = (int32_t)FCUART_STAT_RXINV_MASK,  /**< FCUART_STAT_RXINV   Receive Data Inversion,             RW  */
    FCUART_STAT_RWUID  = (int32_t)FCUART_STAT_RWUID_MASK,  /**< FCUART_STAT_RWUID   Receive Wake Up Idle Detect,        RW  */
    FCUART_STAT_BCGL   = (int32_t)FCUART_STAT_BCGL_MASK,   /**< FCUART_STAT_BCGL    Break Character Generation Length,  RW  */
    FCUART_STAT_LBKDE  = (int32_t)FCUART_STAT_LBKDE_MASK,  /**< FCUART_STAT_LBKDE   LIN Break Detection Enable,         RW  */
    FCUART_STAT_RAF    = (int32_t)FCUART_STAT_RAF_MASK,    /**< FCUART_STAT_RAF     Receiver Active Flag,               RO  */
    FCUART_STAT_TDREF  = (int32_t)FCUART_STAT_TDREF_MASK,  /**< FCUART_STAT_TDREF   Transmit Data Register Empty Flag,  RO  */
    FCUART_STAT_TCF    = (int32_t)FCUART_STAT_TCF_MASK,    /**< FCUART_STAT_TCF     Transmission Complete Flag,         RO  */
    FCUART_STAT_RDRFF  = (int32_t)FCUART_STAT_RDRFF_MASK,  /**< FCUART_STAT_RDRFF   Receive Data Register Full Flag,    RO  */
    FCUART_STAT_IDLEF  = (int32_t)FCUART_STAT_IDLEF_MASK,  /**< FCUART_STAT_IDLEF   Idle Line Flag,                     w1c */
    FCUART_STAT_RORF   = (int32_t)FCUART_STAT_RORF_MASK,   /**< FCUART_STAT_RORF    Receiver Overrun Flag,              w1c */
    FCUART_STAT_NF     = (int32_t)FCUART_STAT_NF_MASK,     /**< FCUART_STAT_NF      Noise Flag,                         w1c */
    FCUART_STAT_FEF    = (int32_t)FCUART_STAT_FEF_MASK,    /**< FCUART_STAT_FEF     Frame Error Flag,                   w1c */
    FCUART_STAT_PEF    = (int32_t)FCUART_STAT_PEF_MASK,    /**< FCUART_STAT_PEF     Parity Error Flag,                  w1c */
    FCUART_STAT_M0F    = (int32_t)FCUART_STAT_M0F_MASK,    /**< FCUART_STAT_M0F     Match address 0 Flag,               w1c */
    FCUART_STAT_M1F    = (int32_t)FCUART_STAT_M1F_MASK,    /**< FCUART_STAT_M1F     Match address 1 Flag,               w1c */
    FCUART_STAT_RPEF   = (int32_t)FCUART_STAT_RPEF_MASK,   /**< FCUART_STAT_RPEF    Receive Data Parity Error Flag,     w1c */
    FCUART_STAT_TPEF   = (int32_t)FCUART_STAT_TPEF_MASK    /**< FCUART_STAT_TPEF    Transmit Data Parity Error Flag,    w1c */
} FCUART_StatType;

/**
 * @brief  UART data bit length mode
 *
 */
typedef enum
{
    UART_BITMODE_8 = 0, /**< UART_BITMODE_8 */
    UART_BITMODE_9   /**< UART_BITMODE_9 */
} FCUART_BitModeType;

/**
 * @brief UART stop bits number
 *
 */
typedef enum
{
    UART_STOPBIT_NUM_1 = 0, /**< UART_STOPBIT_NUM_1 */
    UART_STOPBIT_NUM_2   /**< UART_STOPBIT_NUM_2 */
} FCUART_StopBitNumType;

/**
 * @brief UART parity check type
 *
 */
typedef enum
{
    UART_PARITY_EVEN = 0, /**< UART_PARITY_EVEN */
    UART_PARITY_ODD    /**< UART_PARITY_ODD  */
} FCUART_ParityType;




/********* Local inline function ************/
/**
 * @brief Get Stat Flag
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_SetSoftWareReset(FCUART_Type  *pUart)
{
    pUart->RST |= FCUART_RST_RST_MASK;
    pUart->RST &= ~FCUART_RST_RST_MASK;
}

/**
 * @brief Get Stat Flag
 *
 * @param pUart  UART instance value
 * @param eStatusType  stat type
 * @return FCUART STAT status flag
 */
LOCAL_INLINE uint32_t FCUART_HWA_GetStatus(FCUART_Type  *pUart, FCUART_StatType eStatusType)
{
    return (pUart->STAT & (uint32_t)eStatusType);
}

/**
 * @brief Clear Stat Flag
 *
 * @param pUart  UART instance value
 * @param u32StatusType  stat type
 */
LOCAL_INLINE void FCUART_HWA_ClearStatus(FCUART_Type  *pUart, uint32_t u32StatusType)
{
    pUart->STAT |= u32StatusType;
}

/**
 * @brief Enable Interrupt
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_EnableInterrupt(FCUART_Type  *pUart, uint32 u32Value)
{
    pUart->CTRL |= u32Value;  /* Interrupt Enable    */
}

/**
 * @brief Disable Interrupt
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_DisableInterrupt(FCUART_Type  *pUart, uint32 u32Value)
{
    pUart->CTRL &= ~u32Value;  /* Interrupt Disable    */
}

/**
 * @brief Enable Receive Interrupt
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_EnableReceiveInterrupt(FCUART_Type  *pUart)
{
    pUart->CTRL |= FCUART_CTRL_RIE_MASK;  /* Receive Interrupt Enable    */
}

/**
 * @brief Disable Receive Interrupt
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_DisableReceiveInterrupt(FCUART_Type  *pUart)
{
    pUart->CTRL &= ~FCUART_CTRL_RIE_MASK;  /* Receive Interrupt Enable    */

}

/**
 * @brief Enable Error Interrupt
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_EnableErrorInterrupt(FCUART_Type  *pUart)
{
    pUart->CTRL |= FCUART_CTRL_ORIE_MASK                        |  /* Overrun Interrupt Enable                             */
                   FCUART_CTRL_NEIE_MASK                        |  /* Noise Error Interrupt Enable                         */
                   FCUART_CTRL_FEIE_MASK                        |  /* Frame Error Interrupt Enable                         */
                   FCUART_CTRL_PEIE_MASK;                          /* Parity Error Interrupt Enable                        */
}

/**
 * @brief Disable Error Interrupt
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_DisableErrorInterrupt(FCUART_Type  *pUart)
{
    pUart->CTRL &= ~(FCUART_CTRL_ORIE_MASK                        |  /* Overrun Interrupt Enable                             */
                     FCUART_CTRL_NEIE_MASK                        |  /* Noise Error Interrupt Enable                         */
                     FCUART_CTRL_FEIE_MASK                        |  /* Frame Error Interrupt Enable                         */
                     FCUART_CTRL_PEIE_MASK);                         /* Parity Error Interrupt Enable                        */

}

/**
 * @brief Set FCUART Ctrl register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_SetCtrl(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->CTRL = u32Value;
}

/**
 * @brief Get FCUART Ctrl register
 *
 * @param pUart UART instance value
 * @return Register value
 */
LOCAL_INLINE uint32_t FCUART_HWA_GetCtrl(FCUART_Type  *pUart)
{
    return pUart->CTRL;
}

/**
 * @brief Attach FCUART Ctrl register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_AttachCtrl(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->CTRL |= u32Value;
}

/**
 * @brief Set FCUART Baud register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_SetBaud(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->BAUD = u32Value;
}

/**
 * @brief Get FCUART baud register
 *
 * @param pUart UART instance value
 * @return Register value
 */
LOCAL_INLINE uint32_t FCUART_HWA_GetBaud(FCUART_Type  *pUart)
{
    return pUart->BAUD;
}

/**
 * @brief Attach FCUART Baud register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_AttachBaud(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->BAUD |= u32Value;
}

/**
 * @brief Set FCUART Fifo register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_SetFifo(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->FIFO = u32Value;
}

/**
 * @brief Get FCUART fifo register
 *
 * @param pUart UART instance value
 * @return Register value
 */
LOCAL_INLINE uint32_t FCUART_HWA_GetFifo(FCUART_Type  *pUart)
{
    return pUart->FIFO;
}

/**
 * @brief Get FCUART fifo register
 *
 * @param pUart UART instance value
 * @return Register value
 */
LOCAL_INLINE bool FCUART_HWA_GetEnStatusRxFifo(FCUART_Type  *pUart)
{
    return ((((pUart->FIFO & FCUART_FIFO_RXFEN_MASK) >> FCUART_FIFO_RXFEN_SHIFT) == 1U) ? true: false);
}

/**
 * @brief Get FCUART fifo register
 *
 * @param pUart UART instance value
 * @return Register value
 */
LOCAL_INLINE bool FCUART_HWA_GetEnStatusTxFifo(FCUART_Type  *pUart)
{
    return ((((pUart->FIFO & FCUART_FIFO_TXFEN_MASK) >> FCUART_FIFO_TXFEN_SHIFT) == 1U) ? true: false);
}

/**
 * @brief Attach FCUART Fifo register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_AttachFifo(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->FIFO |= u32Value;
}

/**
 * @brief Set FCUART WaterMark register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_SetWaterMark(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->WATERMARK = u32Value;
}

/**
 * @brief Get FCUART Rx WaterMark
 *
 * @param pUart UART instance value
 * @return Rxcount value
 */
LOCAL_INLINE uint8_t FCUART_HWA_GetRxWaterMark(FCUART_Type  *pUart)
{
    return ((uint8_t)(((pUart->WATERMARK) & FCUART_WATERMARK_RXWATER_MASK) >> FCUART_WATERMARK_RXWATER_SHIFT));
}

/**
 * @brief Get FCUART Tx WaterMark
 *
 * @param pUart UART instance value
 * @return Rxcount value
 */
LOCAL_INLINE uint8_t FCUART_HWA_GetTxWaterMark(FCUART_Type  *pUart)
{
    return ((uint8_t)(((pUart->WATERMARK) & FCUART_WATERMARK_TXWATER_MASK) >> FCUART_WATERMARK_TXWATER_SHIFT));
}

/**
 * @brief Get FCUART WaterMark Rxcount
 *
 * @param pUart UART instance value
 * @return Rxcount value
 */
LOCAL_INLINE uint8_t FCUART_HWA_GetFifoRxCount(FCUART_Type  *pUart)
{
    return ((uint8_t)(((pUart->WATERMARK) & FCUART_WATERMARK_RXCOUNT_MASK) >> FCUART_WATERMARK_RXCOUNT_SHIFT));
}

/**
 * @brief Get FCUART WaterMark Txcount
 *
 * @param pUart UART instance value
 * @return Rxcount value
 */
LOCAL_INLINE uint8_t FCUART_HWA_GetFifoTxCount(FCUART_Type  *pUart)
{
    return ((uint8_t)(((pUart->WATERMARK) & FCUART_WATERMARK_TXCOUNT_MASK) >> FCUART_WATERMARK_TXCOUNT_SHIFT));
}

/**
 * @brief Attach FCUART WaterMark register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_AttachWaterMark(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->WATERMARK |= u32Value;
}

/**
 * @brief Set FCUART Match register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_SetMatch(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->MATCH = u32Value;
}

/**
 * @brief Attach FCUART Match register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_AttachMatch(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->MATCH |= u32Value;
}

/**
 * @brief Get FCUART Match register
 *
 * @param pUart UART instance value
 * @return Register value
 */
LOCAL_INLINE uint32_t FCUART_HWA_GetMatch(FCUART_Type  *pUart)
{
    return pUart->MATCH;
}

/**
 * @brief Read FCUART STAT register
 *
 * @param pUart UART instance value
 * @return STAT read value
 */
LOCAL_INLINE uint32_t FCUART_HWA_GetSTAT(FCUART_Type  *pUart)
{
    return pUart->STAT;
}

/**
 * @brief Write 1 Clear FCUART STAT register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_WriteClearSTAT(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->STAT |= u32Value;
}

/**
 * @brief Set Bit Mode and Parity
 *
 * @param pUart  UART instance value
 * @param eBitMode  is bit mode, 8 or 9 bits
 */
LOCAL_INLINE void FCUART_HWA_SetBitMode(FCUART_Type  *pUart, FCUART_BitModeType eBitMode)
{
    uint32_t u32RegVal = pUart->CTRL;
    pUart->CTRL = ((u32RegVal & (~ FCUART_CTRL_BMSEL_MASK)) | FCUART_CTRL_BMSEL(eBitMode));
}

/**
 * @brief Set Bit Mode and Parity
 *
 * @param pUart  UART instance value
 * @param bParityEnable  If enable Parity, set 1U, or set 0U
 * @param eParityType  Parity type, odd-even
 */
LOCAL_INLINE void FCUART_HWA_SetParity(FCUART_Type  *pUart,  FCUART_ParityType eParityType, bool bParityEnable)
{
    uint32_t u32RegVal = pUart->CTRL;
    pUart->CTRL = ((u32RegVal & (~ FCUART_CTRL_PE_MASK | FCUART_CTRL_PT_MASK)) |
                    FCUART_CTRL_PE(bParityEnable)                              |
                    FCUART_CTRL_PT(eParityType) );
}

/**
 * @brief Set Bit Mode and Parity
 *
 * @param pUart  UART instance value
 * @param eStopBit  stop bits number 1 or 2 bits
 */
LOCAL_INLINE void FCUART_HWA_SetStopBit(FCUART_Type  *pUart, FCUART_StopBitNumType  eStopBit)
{
    uint32_t u32RegVal = pUart->BAUD;
    pUart->BAUD = ((u32RegVal & (~ FCUART_BAUD_SBNS_MASK)) | FCUART_BAUD_SBNS(eStopBit));
}

/**
 * @brief Enable Receive DMA
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_EnableReceiveDMA(FCUART_Type  *pUart)
{
    pUart->BAUD |= FCUART_BAUD_RDMAEN_MASK;
}

/**
 * @brief Disable Receive DMA
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_DisableReceiveDMA(FCUART_Type  *pUart)
{
    pUart->BAUD &= ~FCUART_BAUD_RDMAEN_MASK;

}

/**
 * @brief Enable Receive FIFO
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_EnableReceiveFIFO(FCUART_Type  *pUart)
{
    pUart->FIFO |= FCUART_FIFO_RXFEN_MASK;
}

/**
 * @brief Disable Receive FIFO
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_DisableReceiveFIFO(FCUART_Type  *pUart)
{
    pUart->FIFO &= ~FCUART_FIFO_RXFEN_MASK;

}

/**
 * @brief Clear Fifo Overflow/Underflow flag
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_ClearFIFOErrorFlag(FCUART_Type  *pUart)
{
    pUart->FIFO |= FCUART_FIFO_TXOF_MASK | FCUART_FIFO_RXUF_MASK;
}


/**
 * @brief Set Data Value
 *
 * @param pUart  UART instance value
 * @param u32Data Set data
 */
LOCAL_INLINE void FCUART_HWA_SetData(FCUART_Type  *pUart, uint32_t u32Data)
{
    pUart->DATA = u32Data; /* data 32 bit */
}

/**
 * @brief Get Data Value
 *
 * @param pUart  UART instance value
 * @return the data value
 */
LOCAL_INLINE uint8_t FCUART_HWA_GetData(FCUART_Type  *pUart)
{
    uint8_t u8Data;

    u8Data = *((volatile uint8_t *)&pUart->DATA); /* data 32 bit */

    return u8Data;
}

/**
 * @brief Set R8T9 bit
 *
 * @param pUart  UART instance value
 * @return the data value
 */
LOCAL_INLINE void FCUART_HWA_SetR8T9(FCUART_Type  *pUart, uint8_t u8Data)
{
    uint32_t u32RegVal = pUart->CTRL;
    pUart->CTRL = ((u32RegVal & (~ FCUART_CTRL_R8T9_MASK)) | FCUART_CTRL_R8T9(u8Data));
}

/**
 * @brief Get R8T9 bit
 *
 * @param pUart  UART instance value
 * @return the data value
 */
LOCAL_INLINE uint8_t FCUART_HWA_GetR8T9(FCUART_Type  *pUart)
{
    return (uint8_t)((pUart->CTRL & FCUART_CTRL_R8T9_MASK) >> FCUART_CTRL_R8T9_SHIFT);
}

/**
 * @brief Set R9T8 bit
 *
 * @param pUart  UART instance value
 * @return the data value
 */
LOCAL_INLINE void FCUART_HWA_SetR9T8(FCUART_Type  *pUart, uint8_t u8Data)
{
    uint32_t u32RegVal = pUart->CTRL;
    pUart->CTRL = ((u32RegVal & (~ FCUART_CTRL_R9T8_MASK)) | FCUART_CTRL_R9T8(u8Data));
}

/**
 * @brief Get R9T8 bit
 *
 * @param pUart  UART instance value
 * @return the data value
 */
LOCAL_INLINE uint8_t FCUART_HWA_GetR9T8(FCUART_Type  *pUart)
{
    return (uint8_t)((pUart->CTRL & FCUART_CTRL_R9T8_MASK) >> FCUART_CTRL_R9T8_SHIFT);
}

/**
 * @brief Reset the instance by software.
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_SoftwareReset(FCUART_Type  *pUart)
{
    pUart->RST |= FCUART_RST_RST_MASK;
    pUart->RST &= ~FCUART_RST_RST_MASK;
}

/**
 * @brief Set fcuart TX Transfer enable or disable.
 *
 * @param pUart  UART instance value
 * @param bEnable  Enable cmd, false for disable, true for enable.
 */
LOCAL_INLINE void FCUART_HWA_SetTxTransfer(FCUART_Type  *pUart, bool bEnable)
{
    if (true == bEnable)
    {
        pUart->CTRL |= FCUART_CTRL_TE_MASK;
    }
    else
    {
        pUart->CTRL &= ~FCUART_CTRL_TE_MASK;
    }
}

/**
 * @brief Set fcuart RX Transfer enable or disable.
 *
 * @param pUart  UART instance value
 * @param bEnable  Enable cmd, false for disable, true for enable.
 */
LOCAL_INLINE void FCUART_HWA_SetRxTransfer(FCUART_Type  *pUart, bool bEnable)
{
    if (true == bEnable)
    {
        pUart->CTRL |= FCUART_CTRL_RE_MASK;
    }
    else
    {
        pUart->CTRL &= ~FCUART_CTRL_RE_MASK;
    }
}

/**
 * @brief Set lin break detect interrupt.
 *
 * @param pUart  UART instance value
 * @param bEnable  Enable cmd, false for disable, true for enable.
 */
LOCAL_INLINE void FCUART_HWA_SetLinBreakDetectInterrupt(FCUART_Type  *pUart, bool bEnable)
{
    if (true == bEnable)
    {
        pUart->BAUD |= FCUART_BAUD_LBKDIE_MASK;
    }
    else
    {
        pUart->BAUD &= ~FCUART_BAUD_LBKDIE_MASK;
    }
}

/**
 * @brief Set lin break detect feature enable.
 *
 * @param pUart  UART instance value
 * @param bEnable  Enable cmd, false for disable, true for enable.
 */
LOCAL_INLINE void FCUART_HWA_SetLinBreakDetectEnable(FCUART_Type  *pUart, bool bEnable)
{
    if (true == bEnable)
    {
        pUart->STAT |= (FCUART_STAT_LBKDE_MASK | FCUART_STAT_BCGL_MASK);
    }
    else
    {
        pUart->STAT &= ~(FCUART_STAT_LBKDE_MASK | FCUART_STAT_BCGL_MASK);
    }
}

/**
 * @brief Send a lin break field.
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_SendBreakField(FCUART_Type  *pUart)
{
    pUart->DATA |= FCUART_DATA_FETSC_MASK;
}

/**
 * @brief Set uart receive active interrupt.
 *
 * @param pUart  UART instance value
 * @param bEnable  Enable cmd, false for disable, true for enable.
 */
LOCAL_INLINE void FCUART_HWA_SetReceiveActiveInterrupt(FCUART_Type  *pUart, bool bEnable)
{
    if (true == bEnable)
    {
        pUart->BAUD |= FCUART_BAUD_RIAEIE_MASK;
    }
    else
    {
        pUart->BAUD &= ~FCUART_BAUD_RIAEIE_MASK;
    }
}

/**
 * @brief Set uart receive active interrupt.
 *
 * @param pUart  UART instance value
 * @param return   false for disable, true for enable.
 */
LOCAL_INLINE bool FCUART_HWA_GetReceiveActiveInterrupt(FCUART_Type  *pUart)
{
    bool bRetVal = false;
    
    if (0U != (pUart->BAUD & FCUART_BAUD_RIAEIE_MASK))
    {
        bRetVal = true;
    }

    return bRetVal;
}

/**
 * @brief Set FCUART inverse feature.
 *
 * @param pUart  UART instance value
 * @param bEnable   false for disable, true for enable.
 */
LOCAL_INLINE void FCUART_HWA_SetReceiveDataInverse(FCUART_Type  *pUart, bool bEnable)
{
    if (true == bEnable)
    {
        pUart->STAT |= FCUART_STAT_RXINV_MASK;
    }
    else
    {
        pUart->STAT &= ~FCUART_STAT_RXINV_MASK;
    }
}

/**
 * @brief Get the FCUART inverse bit value.
 *
 * @param pUart  UART instance value
 * @param return   false for disable, true for enable.
 */
LOCAL_INLINE bool FCUART_HWA_GetReceiveDataInverse(FCUART_Type  *pUart)
{
    bool bRetVal = false;
    
    if (0U != (pUart->STAT & FCUART_STAT_RXINV_MASK))
    {
        bRetVal = true;
    }

    return bRetVal;
}

/**
 * @brief Set the FCUART frame error interrupt.
 *
 * @param pUart     UART instance value
 * @param bEnable   false for disable, true for enable.
 */
LOCAL_INLINE void FCUART_HWA_SetFrameErrorInterrupt(FCUART_Type  *pUart, bool bEnable)
{
    if (true == bEnable)
    {
        pUart->CTRL |= FCUART_CTRL_FEIE_MASK;
    }
    else
    {
        pUart->CTRL &= ~FCUART_CTRL_FEIE_MASK;
    }
}

/**
 * @brief Enable the FCUART loop mode.
 *
 * @param pUart     UART instance value
 */
LOCAL_INLINE void FCUART_HWA_EnableLoopMode(FCUART_Type  *pUart)
{
    pUart->CTRL |= FCUART_CTRL_LOOPMS_MASK;
}

/**
 * @brief Disable the FCUART loop mode.
 *
 * @param pUart     UART instance value
 */
LOCAL_INLINE void FCUART_HWA_DisableLoopMode(FCUART_Type  *pUart)
{
    pUart->CTRL &= ~FCUART_CTRL_LOOPMS_MASK;
}

/**
 * \brief Set FCUART MODIR value
 *
 * \param pUart  UART instance value
 * \param u32Data Set data
 */
LOCAL_INLINE void FCUART_HWA_SetModir(FCUART_Type  *pUart, uint32_t u32Data)
{
    pUart->MODIR = u32Data; /* data 32 bit */
}

/**
 * \brief Get FCUART MODIR value
 *
 * \param pUart  UART instance value
 * \param u32Data Get data
 */
LOCAL_INLINE uint32_t FCUART_HWA_GetModir(FCUART_Type  *pUart)
{
    return pUart->MODIR ;
}

/** @}*/

#endif /* end for #ifndef _HWA_FCUART_H_ */
