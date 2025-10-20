/**
 * @file HwA_sent.h
 * @author Flagchip073
 * @brief Hardware access layer for SENT
 * @version 0.0.1
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
   *   0.0.1       2022-12-14    Flagchip073   N/A          First version for FC7300 SENT
   ******************************************************************************** */

#ifndef _HWA_SENT_H_
#define _HWA_SENT_H_

#include "device_header.h"

#define DMA_CH_TO_DCHPRI(x)   ((x) ^ 3U)

/**
 * @defgroup HwA_sent
 * @ingroup fc7xxx_driver_sent
 * @{
 */

/**
 * @brief sent running status
 *
 */
typedef enum
{
    SENT_NIBBLE_DATA_MODE_A    = 0x0U,   /*!< Frame format A */
    SENT_NIBBLE_DATA_MODE_H1   = 0x1U,   /*!< Frame format H1 */
    SENT_NIBBLE_DATA_MODE_H2   = 0x2U,   /*!< Frame format H2 */
    SENT_NIBBLE_DATA_MODE_H3   = 0x3U,   /*!< Frame format H3 */
    SENT_NIBBLE_DATA_MODE_H4   = 0x4U,   /*!< Frame format H4 */
    SENT_NIBBLE_DATA_MODE_H5   = 0x5U,   /*!< Frame format H5 */
    SENT_NIBBLE_DATA_MODE_H6   = 0x6U,   /*!< Frame format H6 */
    SENT_NIBBLE_DATA_MODE_H7   = 0x7U    /*!< Frame format H7 */
} SENT_NibbleDataModeType;

/**
 * @brief sent slow message type
 *
 */
typedef enum
{
    SENT_SLOW_MESSAGE_SHORT                = 0x0U,   /*!< short serial data message */
    SENT_SLOW_MESSAGE_ENHANCE_12DATA_8ID   = 0x1U,   /*!< enhanced serial data message with 12-bit data and 8-bit ID */
    SENT_SLOW_MESSAGE_ENHANCE_16DATA_4ID   = 0x2U,   /*!< enhanced serial data message with 16-bit data and 4-bit ID */
} SENT_SlowMessageType;

/**
 * @brief sent SPC trigger type
 *
 */
typedef enum
{
    SENT_SPC_SW_TRIGGER               = 0x0U,   /*!< SPC pulse triggered by software method */
    SENT_SPC_HW_TRIGGER               = 0x1U,   /*!< SPC pulse triggered by external trigger */
} SENT_SPCTriggerType;

/**
 * @brief sent SPC tick base
 *
 */
typedef enum
{
    SENT_SPC_TICK_PRE_RECEIVED_MESSAGE       = 0x0U,   /*!< Previous received message tick base */
    SENT_SPC_TICK_CONFIG                     = 0x1U,   /*!< SENT configured tick base */
} SENT_SPCTickType;

/**
 * @brief Set SENT Global pre-scaler value
 *
 * @param pSent the base address of the SENT instance
 * @param u8PreScaler the value of the PreSclaer.
 */
LOCAL_INLINE void SENT_HWA_SetGlobalPreScaler(SENT_Type *const pSent, uint8_t u8PreScaler)
{
    pSent->GLBL_CTL = (pSent->GLBL_CTL & ~SENT_GLBL_CTL_PRE_SCALER_MASK) | SENT_GLBL_CTL_PRE_SCALER(u8PreScaler);
}

/**
 * @brief Set SENT Global DMA watermark value
 *
 * @param pSent the base address of the SENT instance
 * @param u8WaterMark the value of the dma watermark.
 */
LOCAL_INLINE void SENT_HWA_SetDMAWaterMark(SENT_Type *const pSent, uint8_t u8WaterMark)
{
    pSent->GLBL_CTL = (pSent->GLBL_CTL & ~SENT_GLBL_CTL_DMA_WATERMARK_MASK) | SENT_GLBL_CTL_DMA_WATERMARK(u8WaterMark);
}

/**
 * @brief Enable SENT Fast message FIFO overflow interrupt
 *
 * @param pSent the base address of the SENT instance
 */
LOCAL_INLINE void SENT_HWA_EnableFastMessageFIFOOverflowInterrupt(SENT_Type *const pSent)
{
    pSent->GLBL_CTL |= SENT_GLBL_CTL_F_FIFO_OVFL_IE_MASK;
}

/**
 * @brief Disable SENT Fast message FIFO overflow interrupt
 *
 * @param pSent the base address of the SENT instance
 */
LOCAL_INLINE void SENT_HWA_DisableFastMessageFIFOOverflowInterrupt(SENT_Type *const pSent)
{
    pSent->GLBL_CTL &= ~SENT_GLBL_CTL_F_FIFO_OVFL_IE_MASK;
}

/**
 * @brief Enable SENT Fast message read underflow interrupt
 *
 * @param pSent the base address of the SENT instance
 */
LOCAL_INLINE void SENT_HWA_EnableFastMessagedmaReadUnderflowInterrupt(SENT_Type *const pSent)
{
    pSent->GLBL_CTL |= SENT_GLBL_CTL_F_DMA_UDFL_IE_MASK;
}

/**
 * @brief Disable SENT Fast message read underflow interrupt
 *
 * @param pSent the base address of the SENT instance
 */
LOCAL_INLINE void SENT_HWA_DisableFastMessagedmaReadUnderflowInterrupt(SENT_Type *const pSent)
{
    pSent->GLBL_CTL &= ~SENT_GLBL_CTL_F_DMA_UDFL_IE_MASK;
}

/**
 * @brief Enable SENT slow message read underflow interrupt
 *
 * @param pSent the base address of the SENT instance
 */
LOCAL_INLINE void SENT_HWA_EnableSlowMessagedmaReadUnderflowInterrupt(SENT_Type *const pSent)
{
    pSent->GLBL_CTL |= SENT_GLBL_CTL_S_DMA_UDFL_IE_MASK;
}

/**
 * @brief Disable SENT slow message read underflow interrupt
 *
 * @param pSent the base address of the SENT instance
 */
LOCAL_INLINE void SENT_HWA_DisableSlowMessagedmaReadUnderflowInterrupt(SENT_Type *const pSent)
{
    pSent->GLBL_CTL &= ~SENT_GLBL_CTL_S_DMA_UDFL_IE_MASK;
}

/**
 * @brief Enable SENT debug mode
 *
 * @param pSent the base address of the SENT instance
 */
LOCAL_INLINE void SENT_HWA_EnableDebugMode(SENT_Type *const pSent)
{
    pSent->GLBL_CTL |= SENT_GLBL_CTL_DBG_EN_MASK;
}

/**
 * @brief Disable SENT debug mode
 *
 * @param pSent the base address of the SENT instance
 */
LOCAL_INLINE void SENT_HWA_DisableDebugMode(SENT_Type *const pSent)
{
    pSent->GLBL_CTL &= ~SENT_GLBL_CTL_DBG_EN_MASK;
}

/**
 * @brief Enable Global SENT debug mode
 *
 * @param pSent the base address of the SENT instance
 */
LOCAL_INLINE void SENT_HWA_EnableGlobal(SENT_Type *const pSent)
{
    pSent->GLBL_CTL |= SENT_GLBL_CTL_SENT_EN_MASK;
}

/**
 * @brief Disable Global SENT debug mode
 *
 * @param pSent the base address of the SENT instance
 */
LOCAL_INLINE void SENT_HWA_DisableGlobal(SENT_Type *const pSent)
{
    pSent->GLBL_CTL &= ~SENT_GLBL_CTL_SENT_EN_MASK;
}

/**
 * @brief Enable Global SENT debug mode
 *
 * @param pSent the base address of the SENT instance
 */
LOCAL_INLINE void SENT_HWA_EnableDataOverflowFlagFastClear(SENT_Type *const pSent)
{
    pSent->GLBL_CTL |= SENT_GLBL_CTL_FAST_CLR_MASK;
}

/**
 * @brief Disable Global SENT debug mode
 *
 * @param pSent the base address of the SENT instance
 */
LOCAL_INLINE void SENT_HWA_DisableDataOverflowFlagFastClear(SENT_Type *const pSent)
{
    pSent->GLBL_CTL &= ~SENT_GLBL_CTL_FAST_CLR_MASK;
}

/**
 * @brief Enable SENT channel receive
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelReceive(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->CHN_EN |= SENT_CHN_EN_CHN_EN((uint32_t)1u << u8Channel);
}

/**
 * @brief Disable SENT channel receive
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelReceive(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->CHN_EN &= ~SENT_CHN_EN_CHN_EN((uint32_t)1u << u8Channel);
}

/**
 * @brief Get SENT channel receive
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE bool SENT_HWA_GetChannelReceive(const SENT_Type *const pSent, uint8_t u8Channel)
{
    if(SENT_CHN_EN_CHN_EN((uint32_t)1u << u8Channel) == (pSent->CHN_EN & SENT_CHN_EN_CHN_EN((uint32_t)1u << u8Channel)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Get Channel slow message dma read underflow flag
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @return bool true: the related channel slow message dma is underflow
 */
LOCAL_INLINE bool SENT_HWA_GetSLowMessageUnderflowFlag(const SENT_Type *const pSent, uint8_t u8Channel)
{
    if(((uint32_t)1u << u8Channel) == (pSent->GLBL_STAT & SENT_GLBL_STAT_S_DMA_UDFL((uint32_t)1u << u8Channel)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Clear Channel slow message dma read underflow flag
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_ClearSLowMessageUnderflowFlag(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->GLBL_STAT |= SENT_GLBL_STAT_S_DMA_UDFL((uint32_t)1u << u8Channel);
}

/**
 * @brief Get Channel fast message ready flag
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @return bool true: the related channel fast message is ready
 */
LOCAL_INLINE bool SENT_HWA_GetFastMessageReadyFlag(const SENT_Type *const pSent, uint8_t u8Channel)
{
    if(SENT_FMSG_STAT_F_MSG_RDY((uint32_t)1u << u8Channel) == (pSent->FMSG_STAT & SENT_FMSG_STAT_F_MSG_RDY((uint32_t)1u << u8Channel)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Clear Channel fast message ready flag
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_ClearFastMessageReadyFlag(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->FMSG_STAT |= SENT_FMSG_STAT_F_MSG_RDY((uint32_t)1u << u8Channel);
}

/**
 * @brief Get Channel slow message ready flag
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @return bool true: the related channel slow message is ready
 */
LOCAL_INLINE bool SENT_HWA_GetSlowMessageReadyFlag(const SENT_Type *const pSent, uint8_t u8Channel)
{
    if(((uint32_t)1u << u8Channel) == (pSent->SMSG_STAT & ((uint32_t)1u << u8Channel)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Clear Channel slow message ready flag
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_ClearSlowMessageReadyFlag(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SMSG_STAT |= SENT_FMSG_STAT_F_MSG_RDY((uint32_t)1u << u8Channel);
}

/**
 * @brief Enable SENT channel FIFO function
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelFIFO(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->FIFO_EN |= SENT_FIFO_EN_FIFO_EN((uint32_t)1u << u8Channel);
}

/**
 * @brief Disable SENT channel receive function
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelFIFO(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->FIFO_EN &= ~SENT_FIFO_EN_FIFO_EN((uint32_t)1u << u8Channel);
}

/**
 * @brief Set SENT channel data nibble number
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param u8Number the received data number
 */
LOCAL_INLINE void SENT_HWA_SetChannelNibbleNumber(SENT_Type *const pSent, uint8_t u8Channel, uint8_t u8Number)
{
    pSent->DATA_NUM_CTL1 = (pSent->DATA_NUM_CTL1 & ~(SENT_DATA_NUM_CTL1_CH0_DATA_CTL_MASK >> (4u * u8Channel))) | (SENT_DATA_NUM_CTL1_CH0_DATA_CTL(u8Number) >> (4u * u8Channel));
}

/**
 * @brief Get SENT channel data nibble number
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param uint8_t the config data number
 */
LOCAL_INLINE uint8_t SENT_HWA_GetChannelNibbleNumber(const SENT_Type *const pSent, uint8_t u8Channel)
{
    return (uint8_t)((pSent->DATA_NUM_CTL1 & (SENT_DATA_NUM_CTL1_CH0_DATA_CTL_MASK >> (4u * u8Channel))) >> (SENT_DATA_NUM_CTL1_CH0_DATA_CTL_SHIFT - (4u * u8Channel)));
}

/**
 * @brief Get Channel fast message FIFO overflow flag
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @return bool true: the related channel fast message FIFO is overflow
 */
LOCAL_INLINE bool SENT_HWA_GetFastMessageFIFOOverflowFlag(const SENT_Type *const pSent, uint8_t u8Channel)
{
    if(SENT_OVFL_UDFL_STAT_FIFO_F_OVFL_FLAG((uint32_t)1u << u8Channel) == (pSent->OVFL_UDFL_STAT & SENT_OVFL_UDFL_STAT_FIFO_F_OVFL_FLAG((uint32_t)1u << u8Channel)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Clear Channel fast message FIFO overflow flag
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_ClearFastMessageFIFOOverflowFlag(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->OVFL_UDFL_STAT |= SENT_OVFL_UDFL_STAT_FIFO_F_OVFL_FLAG((uint32_t)1u << u8Channel);
}

/**
 * @brief Get Channel fast message DMA underflow flag
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @return bool true: the related channel fast message DMA read is underflow
 */
LOCAL_INLINE bool SENT_HWA_GetFastMessageDMAUnderflowFlag(const SENT_Type *const pSent, uint8_t u8Channel)
{
    if(SENT_OVFL_UDFL_STAT_DMA_F_UDFL_FLAG((uint32_t)1u << u8Channel) == (pSent->OVFL_UDFL_STAT & SENT_OVFL_UDFL_STAT_DMA_F_UDFL_FLAG((uint32_t)1u << u8Channel)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Clear Channel fast message DMA underflow flag
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_ClearFastMessageDMAUnderflowFlag(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->OVFL_UDFL_STAT |= SENT_OVFL_UDFL_STAT_DMA_F_UDFL_FLAG((uint32_t)1u << u8Channel);
}

/**
 * @brief Set SENT channel nibble data mode
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param eMode the nibble data mode
 */
LOCAL_INLINE void SENT_HWA_SetChannelNibbleDataMode(SENT_Type *const pSent, uint8_t u8Channel, SENT_NibbleDataModeType eMode)
{
    pSent->NB_MODE1 = (pSent->NB_MODE1 & ~(SENT_NB_MODE1_CH0_NB_MODE_MASK >> (4u * u8Channel))) | (SENT_NB_MODE1_CH0_NB_MODE(eMode) >> (4u * u8Channel));
}

/**
 * @brief Enable SENT channel fast message DMA request
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelFastMessageDmaRequest(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->FDMA_CTL |= SENT_FDMA_CTL_FDMA_EN((uint32_t)1u << u8Channel);
}

/**
 * @brief Disable SENT channel fast message DMA request
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelFastMessageDmaRequest(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->FDMA_CTL &= ~SENT_FDMA_CTL_FDMA_EN((uint32_t)1u << u8Channel);
}

/**
 * @brief Enable SENT channel slow message DMA request
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelSlowMessageDmaRequest(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SDMA_CTL |= SENT_SDMA_CTL_SDMA_EN((uint32_t)1u << u8Channel);
}

/**
 * @brief Disable SENT channel slow message DMA request
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelSlowMessageDmaRequest(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SDMA_CTL &= ~SENT_SDMA_CTL_SDMA_EN((uint32_t)1u << u8Channel);
}

/**
 * @brief Enable SENT channel Fast message interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelFastMessageInterrupt(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->FINT_CTL |= SENT_FINT_CTL_FINT_CTL((uint32_t)1u << u8Channel);
}

/**
 * @brief Disable SENT channel Fast message interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelFastMessageInterrupt(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->FINT_CTL &= ~SENT_FINT_CTL_FINT_CTL((uint32_t)1u << u8Channel);
}

/**
 * @brief Enable SENT channel slow message interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelSlowMessageInterrupt(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SINT_CTL |= SENT_SINT_CTL_SINT_CTL((uint32_t)1u << u8Channel);
}

/**
 * @brief Disable SENT channel slow message interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelSlowMessageInterrupt(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SINT_CTL &= ~SENT_SINT_CTL_SINT_CTL((uint32_t)1u << u8Channel);
}

/**
 * @brief Enable SENT channel Compensate
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelCompensate(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CLK_CTL |= SENT_CHN_CLK_CTL_COMP_EN_MASK;
}

/**
 * @brief Disable SENT channel Compensate
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelCompensate(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CLK_CTL &= ~SENT_CHN_CLK_CTL_COMP_EN_MASK;
}

/**
 * @brief Set SENT channel pre-scaler
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param u16PreScaler the related Channel Prescaler value
 */
LOCAL_INLINE void SENT_HWA_SetChannelPreScaler(SENT_Type *const pSent, uint8_t u8Channel, uint16_t u16PreScaler)
{
    pSent->SENT_CHN[u8Channel].CHN_CLK_CTL = (pSent->SENT_CHN[u8Channel].CHN_CLK_CTL & ~SENT_CHN_CLK_CTL_PRE_SCALER_MASK) | SENT_CHN_CLK_CTL_PRE_SCALER(u16PreScaler);
}

/**
 * @brief Get Channel Prescaler value after compensate
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @return uint8_t the related Channel Prescaler value after compensate
 */
LOCAL_INLINE uint16_t SENT_HWA_GetChannelCompensatePreScaler(const SENT_Type *const pSent, uint8_t u8Channel)
{
    return (uint16_t)((pSent->SENT_CHN[u8Channel].CHN_CLK_CTL & SENT_CHN_CLK_CTL_COMPED_PRE_SCALER_MASK) >> SENT_CHN_CLK_CTL_COMPED_PRE_SCALER_SHIFT);
}

/**
 * @brief Get Channel status
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @return uint32_t the related Channel status
 */
LOCAL_INLINE uint32_t SENT_HWA_GetChannelStatus(const SENT_Type *const pSent, uint8_t u8Channel)
{
    return pSent->SENT_CHN[u8Channel].CHN_STAT;
}

/**
 * @brief Clear Channel status
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param u32W1CBit the status bits need to be clear.
 */
LOCAL_INLINE void SENT_HWA_ClearChannelStatus(SENT_Type *const pSent, uint8_t u8Channel, uint32_t u32W1CBit)
{
    pSent->SENT_CHN[u8Channel].CHN_STAT |= u32W1CBit;
}

/**
 * @brief Enable SENT channel all error interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelAllErrorInterrupt(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL |= (SENT_CHN_CTL_CAL_RESYNC_IE_MASK | SENT_CHN_CTL_CAL_20_25_IE_MASK | SENT_CHN_CTL_SMSG_OVFL_IE_MASK | \
                                           SENT_CHN_CTL_FMSG_OVFL_IE_MASK | SENT_CHN_CTL_PP_DIAG_ERR_IE_MASK | SENT_CHN_CTL_CAL_DIAG_ERR_IE_MASK | \
                                           SENT_CHN_CTL_CAL_ERR_IE_MASK | SENT_CHN_CTL_NIB_ERR_IE_MASK | SENT_CHN_CTL_S_CRC_ERR_IE_MASK | \
                                           SENT_CHN_CTL_F_CRC_ERR_IE_MASK | SENT_CHN_CTL_EDGE_ERR_IE_MASK | SENT_CHN_CTL_SPC_OVERRUN_IE_MASK);
}

/**
 * @brief Disable SENT channel all error interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelAllErrorInterrupt(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL &= ~(SENT_CHN_CTL_CAL_RESYNC_IE_MASK | SENT_CHN_CTL_CAL_20_25_IE_MASK | SENT_CHN_CTL_SMSG_OVFL_IE_MASK | \
                                            SENT_CHN_CTL_FMSG_OVFL_IE_MASK | SENT_CHN_CTL_PP_DIAG_ERR_IE_MASK | SENT_CHN_CTL_CAL_DIAG_ERR_IE_MASK | \
                                            SENT_CHN_CTL_CAL_ERR_IE_MASK | SENT_CHN_CTL_NIB_ERR_IE_MASK | SENT_CHN_CTL_S_CRC_ERR_IE_MASK | \
                                            SENT_CHN_CTL_F_CRC_ERR_IE_MASK | SENT_CHN_CTL_EDGE_ERR_IE_MASK | SENT_CHN_CTL_SPC_OVERRUN_IE_MASK);
}

/**
 * @brief Enable/disable SENT channel idle flag interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param bEn Enable or disable the interrupt
 */
LOCAL_INLINE void SENT_HWA_EnableChannelBusIdleInterrupt(SENT_Type *const pSent, uint8_t u8Channel, bool bEn)
{
    if(bEn)
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_BUS_IDLE_IE_MASK;
    }
    else
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_BUS_IDLE_IE_MASK;
    }
}

/**
 * @brief Enable/disable SENT channel sync/calibration pulse error interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param bEn Enable or disable the interrupt
 */
LOCAL_INLINE void SENT_HWA_EnableChannelCalResyncInterrupt(SENT_Type *const pSent, uint8_t u8Channel, bool bEn)
{
    if(bEn)
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_CAL_RESYNC_IE_MASK;
    }
    else
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_CAL_RESYNC_IE_MASK;
    }
}

/**
 * @brief Enable/disable Sync/calibration pulse difference eceed 1.5625% error interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param bEn Enable or disable the interrupt
 */
LOCAL_INLINE void SENT_HWA_EnableChannelCalERRInterrupt(SENT_Type *const pSent, uint8_t u8Channel, bool bEn)
{
    if(bEn)
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_CAL_ERR_IE_MASK;
    }
    else
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_CAL_ERR_IE_MASK;
    }
}

/**
 * @brief Enable/disable SENT channel Calibration 20% pass 25% fail interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param bEn Enable or disable the interrupt
 */
LOCAL_INLINE void SENT_HWA_EnableChannelCalFailInterrupt(SENT_Type *const pSent, uint8_t u8Channel, bool bEn)
{
    if(bEn)
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_CAL_20_25_IE_MASK;
    }
    else
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_CAL_20_25_IE_MASK;
    }
}

/**
 * @brief Enable/disable SENT channel Slow message overflow interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param bEn Enable or disable the interrupt
 */
LOCAL_INLINE void SENT_HWA_EnableChannelSOVFLInterrupt(SENT_Type *const pSent, uint8_t u8Channel, bool bEn)
{
    if(bEn)
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_SMSG_OVFL_IE_MASK;
    }
    else
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_SMSG_OVFL_IE_MASK;
    }
}

/**
 * @brief Enable/disable SENT channel fast message overflow interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param bEn Enable or disable the interrupt
 */
LOCAL_INLINE void SENT_HWA_EnableChannelFOVFLInterrupt(SENT_Type *const pSent, uint8_t u8Channel, bool bEn)
{
    if(bEn)
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_FMSG_OVFL_IE_MASK;
    }
    else
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_FMSG_OVFL_IE_MASK;
    }
}

/**
 * @brief Enable/disable SENT channel Nibble value error interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param bEn Enable or disable the interrupt
 */
LOCAL_INLINE void SENT_HWA_EnableChannelNibbleErrorInterrupt(SENT_Type *const pSent, uint8_t u8Channel, bool bEn)
{
    if(bEn)
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_NIB_ERR_IE_MASK;
    }
    else
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_NIB_ERR_IE_MASK;
    }
}

/**
 * @brief Enable/disable SENT channel Previous pulse diagnosis error interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param bEn Enable or disable the interrupt
 */
LOCAL_INLINE void SENT_HWA_EnableChannelPPDiagInterrupt(SENT_Type *const pSent, uint8_t u8Channel, bool bEn)
{
    if(bEn)
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_PP_DIAG_ERR_IE_MASK;
    }
    else
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_PP_DIAG_ERR_IE_MASK;
    }
}

/**
 * @brief Enable/disable SENT channel Calibration diagnosis over 25% error interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param bEn Enable or disable the interrupt
 */
LOCAL_INLINE void SENT_HWA_EnableChannelCALDiagInterrupt(SENT_Type *const pSent, uint8_t u8Channel, bool bEn)
{
    if(bEn)
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_CAL_DIAG_ERR_IE_MASK;
    }
    else
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_CAL_DIAG_ERR_IE_MASK;
    }
}

/**
 * @brief Enable/disable SENT channel SPC overrun error interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param bEn Enable or disable the interrupt
 */
LOCAL_INLINE void SENT_HWA_EnableChannelSPCOverRunInterrupt(SENT_Type *const pSent, uint8_t u8Channel, bool bEn)
{
    if(bEn)
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_SPC_OVERRUN_IE_MASK;
    }
    else
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_SPC_OVERRUN_IE_MASK;
    }
}

/**
 * @brief Enable/disable SENT channel Fast message CRC check error interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param bEn Enable or disable the interrupt
 */
LOCAL_INLINE void SENT_HWA_EnableChannelFCRCInterrupt(SENT_Type *const pSent, uint8_t u8Channel, bool bEn)
{
    if(bEn)
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_F_CRC_ERR_IE_MASK;
    }
    else
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_F_CRC_ERR_IE_MASK;
    }
}

/**
 * @brief Enable/disable SENT channel slow message CRC check error interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param bEn Enable or disable the interrupt
 */
LOCAL_INLINE void SENT_HWA_EnableChannelSCRCInterrupt(SENT_Type *const pSent, uint8_t u8Channel, bool bEn)
{
    if(bEn)
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_S_CRC_ERR_IE_MASK;
    }
    else
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_S_CRC_ERR_IE_MASK;
    }
}

/**
 * @brief Enable/disable SENT channel Falling edge number error interrupt
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param bEn Enable or disable the interrupt
 */
LOCAL_INLINE void SENT_HWA_EnableChannelEdgeERRInterrupt(SENT_Type *const pSent, uint8_t u8Channel, bool bEn)
{
    if(bEn)
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_EDGE_ERR_IE_MASK;
    }
    else
    {
        pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_EDGE_ERR_IE_MASK;
    }
}

/**
 * @brief Enable SENT channel Alternative 4-bit CRC algorithm
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelAltCRC(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_ALT_4BIT_CRC_MASK;
}

/**
 * @brief Disable SENT channel Alternative 4-bit CRC algorithm
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelAltCRC(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_ALT_4BIT_CRC_MASK;
}

/**
 * @brief Enable SENT channel Fast message data change
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelFastMessageDataChange(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_DATA_CHANGE_EN_MASK;
}

/**
 * @brief Disable SENT channel Fast message data change
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelFastMessageDataChange(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_DATA_CHANGE_EN_MASK;
}

/**
 * @brief Enable SENT channel calibration valid range from 20% tp 25%
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelCalValid20To25(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_CAL_SEL_MASK;
}

/**
 * @brief Disable SENT channel calibration valid range from 20% tp 25%
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelCalValid20To25(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_CAL_SEL_MASK;
}

/**
 * @brief Enable SENT channel calibration valid diagnostic
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelCalValidDiagnostic(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_PP_CHK_DIS_MASK;
}

/**
 * @brief Disable SENT channel calibration valid diagnostic
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelCalValidDiagnostic(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_PP_CHK_DIS_MASK;
}

/**
 * @brief Enable SENT channel fast message CRC with Augmentation
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelFastMessageAugmentation(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_FCRC_SEL_MASK;
}

/**
 * @brief Disable SENT channel fast message CRC with Augmentation
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelFastMessageAugmentation(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_FCRC_SEL_MASK;
}

/**
 * @brief Enable SENT channel Fast message crc with S&C
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelFastMessageCRCWithSC(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_FCRC_SC_EN_MASK;
}

/**
 * @brief Disable SENT channel Fast message crc with S&C
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelFastMessageCRCWithSC(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_FCRC_SC_EN_MASK;
}

/**
 * @brief Enable SENT channel slow message CRC with Augmentation
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelSlowMessageAugmentation(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_SCRC_SEL_MASK;
}

/**
 * @brief Disable SENT channel slow message CRC with Augmentation
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelSlowMessageAugmentation(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_SCRC_SEL_MASK;
}

/**
 * @brief Enable SENT channel Pause pulse
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelPausePulse(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_PAUSE_DET_EN_MASK;
}

/**
 * @brief Disable SENT channel Successive calibration pulses diagnostic option1
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelPausePulse(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_PAUSE_DET_EN_MASK;
}

/**
 * @brief Enable SENT channel Successive calibration pulses diagnostic option1
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelSPCOption1(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_SCP_CHK_MASK;
}

/**
 * @brief Disable SENT channel Pause pulse
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelSPCOption1(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_SCP_CHK_MASK;
}

/**
 * @brief Enable SENT channel Fast message crc check
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelFastMessageCRCCheck(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL &= ~SENT_CHN_CTL_FMSG_CRC_CHECK_OFF_MASK;
}

/**
 * @brief Disable SENT channel Fast message crc check
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelFastMessageCRCCheck(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL |= SENT_CHN_CTL_FMSG_CRC_CHECK_OFF_MASK;
}

/**
 * @brief Set SENT channel digital filter count
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param u8Count the count of channel digital filter
 */
LOCAL_INLINE void SENT_HWA_SetChannelDigitalFilterCount(SENT_Type *const pSent, uint8_t u8Channel, uint8_t u8Count)
{
    pSent->SENT_CHN[u8Channel].CHN_CTL = (pSent->SENT_CHN[u8Channel].CHN_CTL & ~SENT_CHN_CTL_FILT_CNT_MASK) | SENT_CHN_CTL_FILT_CNT(u8Count);
}

/**
 * @brief Get Channel fast message data nibble
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel(0-3)
 * @return uint32_t  the corresponding channel data nibble value
 */
LOCAL_INLINE uint32_t SENT_HWA_GetChannelDataNibble(const SENT_Type *const pSent, uint8_t u8Channel)
{
    return pSent->SENT_CHN[u8Channel].CHN_FDATA;
}

/**
 * @brief Get Channel fast message crc nibble
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel(0-3)
 * @return uint8_t  the corresponding channel crc nibble value
 */
LOCAL_INLINE uint8_t SENT_HWA_GetChannelFastMessageCRCNibble(const SENT_Type *const pSent, uint8_t u8Channel)
{
    return (uint8_t)((pSent->SENT_CHN[u8Channel].CHN_FCRC & SENT_CHN_FCRC_CRC_DATA_MASK) >> SENT_CHN_FCRC_CRC_DATA_SHIFT);
}

/**
 * @brief Get Channel fast message status communication nibble
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel(0-3)
 * @return uint8_t  the corresponding channel status communication nibble value
 */
LOCAL_INLINE uint8_t SENT_HWA_GetChannelFastMessageStatusNibble(const SENT_Type *const pSent, uint8_t u8Channel)
{
    return (uint8_t)((pSent->SENT_CHN[u8Channel].CHN_FCRC & SENT_CHN_FCRC_SC_NB_MASK) >> SENT_CHN_FCRC_SC_NB_SHIFT);
}

/**
 * @brief Get Channel fast message status timestamp
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel(0-3)
 * @return uint32_t  the corresponding channel timestamp value
 */
LOCAL_INLINE uint32_t SENT_HWA_GetChannelFastMessageTimeStamp(const SENT_Type *const pSent, uint8_t u8Channel)
{
    return ((pSent->SENT_CHN[u8Channel].CHN_FTS & SENT_CHN_FTS_TIMESTAMP_VAL_MASK) >> SENT_CHN_FTS_TIMESTAMP_VAL_SHIFT);
}

/**
 * @brief Get Channel slow message type
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel(0-3)
 * @return SENT_SlowMessageType  the corresponding channel slow message type
 */
LOCAL_INLINE SENT_SlowMessageType SENT_HWA_GetChannelSLowMessageType(const SENT_Type *const pSent, uint8_t u8Channel)
{
    SENT_SlowMessageType eRet = SENT_SLOW_MESSAGE_SHORT;

    if(SENT_CHN_SBIT3__MSG_TYPE_MASK == (pSent->SENT_CHN[u8Channel].CHN_SBIT3 & SENT_CHN_SBIT3__MSG_TYPE_MASK))
    {
        if(SENT_CHN_SBIT3__CFG_MASK == (pSent->SENT_CHN[u8Channel].CHN_SBIT3 & SENT_CHN_SBIT3__CFG_MASK))
        {
            eRet = SENT_SLOW_MESSAGE_ENHANCE_16DATA_4ID;
        }
        else
        {
            eRet = SENT_SLOW_MESSAGE_ENHANCE_12DATA_8ID;
        }
    }
    else
    {
        //do nothing
    }
    return eRet;
}

/**
 * @brief Get Channel enhanced serial message id bit 7 to bit4 or id bit 3 to id bit 0
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel(0-3)
 * @return uint8_t  the corresponding channel enhanced serial message id bit 7 to bit4 or id bit 3 to id bit 0
 */
LOCAL_INLINE uint8_t SENT_HWA_GetChannelBit3EnhancedID7_4_OR_ID3_0(const SENT_Type *const pSent, uint8_t u8Channel)
{
    return (uint8_t)((pSent->SENT_CHN[u8Channel].CHN_SBIT3 & SENT_CHN_SBIT3__ID7_4_OR_ID3_0_MASK) >> SENT_CHN_SBIT3__ID7_4_OR_ID3_0_SHIFT);
}

/**
 * @brief Get Channel enhanced serial message id bit 3 to bit0 or data bit 15 to id bit 12
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel(0-3)
 * @return uint8_t  the corresponding channel enhanced serial message id bit 3 to bit0 or data bit 15 to id bit 12
 */
LOCAL_INLINE uint8_t SENT_HWA_GetChannelBit3EnhancedID3_0_OR_DATA15_12(const SENT_Type *const pSent, uint8_t u8Channel)
{
    return (uint8_t)((pSent->SENT_CHN[u8Channel].CHN_SBIT3 & SENT_CHN_SBIT3__ID3_0_OR_DATA15_12_MASK) >> SENT_CHN_SBIT3__ID3_0_OR_DATA15_12_SHIFT);
}

/**
 * @brief Get Channel slow message bit2 with CRC
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel(0-3)
 * @return uint8_t  the corresponding channel slow message CRC value
 */
LOCAL_INLINE uint8_t SENT_HWA_GetChannelBit2CRC(const SENT_Type *const pSent, uint8_t u8Channel)
{
    return (uint8_t)((pSent->SENT_CHN[u8Channel].CHN_SBIT2 & SENT_CHN_SBIT2__SMSG_CRC_MASK) >> SENT_CHN_SBIT2__SMSG_CRC_SHIFT);
}

/**
 * @brief Get Channel slow message bit2 with DATA
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel(0-3)
 * @return uint16_t  the corresponding channel slow message DATA value
 */
LOCAL_INLINE uint16_t SENT_HWA_GetChannelBit2DATA(const SENT_Type *const pSent, uint8_t u8Channel)
{
    return (uint16_t)((pSent->SENT_CHN[u8Channel].CHN_SBIT2 & SENT_CHN_SBIT2__SMSG_DATA_MASK) >> SENT_CHN_SBIT2__SMSG_DATA_SHIFT);
}

/**
 * @brief Get Channel slow message status timestamp
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel(0-3)
 * @return uint32_t  the corresponding channel timestamp value
 */
LOCAL_INLINE uint32_t SENT_HWA_GetChannelSlowMessageTimeStamp(const SENT_Type *const pSent, uint8_t u8Channel)
{
    return ((pSent->SENT_CHN[u8Channel].CHN_STS & SENT_CHN_STS_SMSG_TIMESTAMP_MASK) >> SENT_CHN_STS_SMSG_TIMESTAMP_SHIFT);
}

/**
 * @brief Get Channel number of received frames
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel(0-3)
 * @return uint32_t  the number of received frames
 */
LOCAL_INLINE uint32_t SENT_HWA_GetChanneReceivedFrameNumber(const SENT_Type *const pSent, uint8_t u8Channel)
{
    return ((pSent->SENT_CHN[u8Channel].CHN_MCNT & SENT_CHN_MCNT_FRAME_CNT_MASK) >> SENT_CHN_MCNT_FRAME_CNT_SHIFT);
}

/**
 * @brief Get Channel number of received edges
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel(0-3)
 * @return uint32_t  the number of received edges
 */
LOCAL_INLINE uint32_t SENT_HWA_GetChanneReceivedEdgeNumber(const SENT_Type *const pSent, uint8_t u8Channel)
{
    return ((pSent->SENT_CHN[u8Channel].CHN_MCNT & SENT_CHN_MCNT_EDGE_CNT_MASK) >> SENT_CHN_MCNT_EDGE_CNT_SHIFT);
}

/**
 * @brief Clear the number of received frames
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_ClearChannelReceivedFrameNumber(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_MCNT |= SENT_CHN_MCNT_FRAME_CNT_CLR_MASK;
}

/**
 * @brief Clear the number of received edges
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_ClearChannelReceivedEdgeNumber(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_MCNT |= SENT_CHN_MCNT_EDGE_CNT_CLR_MASK;
}

/**
 * @brief Enable SENT channel SPC mode
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelSPCMode(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_SPC_CTL |= SENT_CHN_SPC_CTL_SPC_ENABLE_MASK;
}

/**
 * @brief Disable SENT channel SPC mode
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelSPCMode(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_SPC_CTL &= ~SENT_CHN_SPC_CTL_SPC_ENABLE_MASK;
}

/**
 * @brief Enable SENT channel calibration diagnosis in SPC mod
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_EnableChannelCalibrationDiag(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_SPC_CTL &= ~SENT_CHN_SPC_CTL_CAL_DIAG_DIS_MASK;
}

/**
 * @brief Disable SENT channel calibration diagnosis in SPC mod
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_DisableChannelCalibrationDiag(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_SPC_CTL |= SENT_CHN_SPC_CTL_CAL_DIAG_DIS_MASK;
}


/**
 * @brief Set the SPC pulse trigger method
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param eTrigger the SPC pulse trigger method
 */
LOCAL_INLINE void SENT_HWA_SetChannelSPCTriggerMethod(SENT_Type *const pSent, uint8_t u8Channel, SENT_SPCTriggerType eTrigger)
{
    pSent->SENT_CHN[u8Channel].CHN_SPC_CTL = (pSent->SENT_CHN[u8Channel].CHN_SPC_CTL & ~SENT_CHN_SPC_CTL_SPC_MODE_MASK) | SENT_CHN_SPC_CTL_SPC_MODE(eTrigger);
}

/**
 * @brief Set the delay between SPC-trigger assert and finally generate a SPC pulse
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param eTrigger the delay value
 */
LOCAL_INLINE void SENT_HWA_SetChannelSPCPulseDelay(SENT_Type *const pSent, uint8_t u8Channel, uint8 u8Delay)
{
    pSent->SENT_CHN[u8Channel].CHN_SPC_CTL = (pSent->SENT_CHN[u8Channel].CHN_SPC_CTL & ~SENT_CHN_SPC_CTL_SPC_PULSE_DELAY_MASK) | SENT_CHN_SPC_CTL_SPC_PULSE_DELAY(u8Delay);
}

/**
 * @brief Set the delay between SPC-trigger assert and finally generate a SPC pulse
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param eTick the selected tick base of SPC
 */
LOCAL_INLINE void SENT_HWA_SetChannelSPCTickBase(SENT_Type *const pSent, uint8_t u8Channel, SENT_SPCTickType eTick)
{
    pSent->SENT_CHN[u8Channel].CHN_SPC_CTL = (pSent->SENT_CHN[u8Channel].CHN_SPC_CTL & ~SENT_CHN_SPC_CTL_SPC_TICK_BASE_MASK) | SENT_CHN_SPC_CTL_SPC_TICK_BASE(eTick);
}

/**
 * @brief trigger the SENT to generate a SPC pulse by software
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 */
LOCAL_INLINE void SENT_HWA_StartChannelSPC(SENT_Type *const pSent, uint8_t u8Channel)
{
    pSent->SENT_CHN[u8Channel].CHN_SPC_CTL |= SENT_CHN_SPC_CTL_SPC_START_MASK;
}

/**
 * @brief Set the width of the SPC pulse.
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param u8Width the width of the SPC pulse.
 */
LOCAL_INLINE void SENT_HWA_SetChannelSPCPulseWidth(SENT_Type *const pSent, uint8_t u8Channel, uint8_t u8Width)
{
    pSent->SENT_CHN[u8Channel].CHN_SPC_CTL = (pSent->SENT_CHN[u8Channel].CHN_SPC_CTL & ~SENT_CHN_SPC_CTL_SPC_PULSE_WIDTH_MASK) | SENT_CHN_SPC_CTL_SPC_PULSE_WIDTH(u8Width);
}

/**
 * @brief Set the idle count determines how long the bus idle flag will assert when bus is idle
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel
 * @param u8Count the idle count
 */
LOCAL_INLINE void SENT_HWA_SetChannelIdleCount(SENT_Type *const pSent, uint8_t u8Channel, uint8_t u8Count)
{
    pSent->SENT_CHN[u8Channel].CHN_IDLE_CTL = (pSent->SENT_CHN[u8Channel].CHN_IDLE_CTL & ~SENT_CHN_IDLE_CTL_IDLE_CNT_MASK) | SENT_CHN_IDLE_CTL_IDLE_CNT(u8Count);
}

/**
 * @brief Get the flag indicating the spc is busy
 *
 * @param pSent the base address of the SENT instance
 * @param u8Channel the index of sent channel(0-3)
 * @return bool  the flag indicating the spc is busy
 */
LOCAL_INLINE bool SENT_HWA_GetChanneSPCBusyFlag(const SENT_Type *const pSent, uint8_t u8Channel)
{
    if(SENT_CHN_SPC_CTL_SPC_BUSY_MASK == (pSent->SENT_CHN[u8Channel].CHN_SPC_CTL & SENT_CHN_SPC_CTL_SPC_BUSY_MASK))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/** @}*/

#endif /* _HWA_SENT_H_ */
