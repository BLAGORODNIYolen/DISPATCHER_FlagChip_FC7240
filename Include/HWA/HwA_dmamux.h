/**
 * @file HwA_dmamux.h
 * @author Flagchip0126
 * @brief Hardware access layer for DMAMUX
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
   *   0.1.0       2024-01-15    Flagchip0126   N/A         First version for FC7240
   ******************************************************************************** */

#ifndef _HWA_DMAMUX_H_
#define _HWA_DMAMUX_H_

#include "device_header.h"

/**
 * @defgroup HwA_dmamux
 * @ingroup fc7xxx_driver_dma
 * @{
 */

/**
 * @brief Structure for the DMA hardware request
 *
 * Defines the structure for the DMA hardware request collections. The user can configure the
 * hardware request into DMAMUX to trigger the DMA transfer accordingly. The index
 * of the hardware request varies according  to the to SoC.
 */
typedef enum
{
    DMA_REQ_DISABLED                        = 0U,
    DMA_REQ_FCIIC0_RX                       = 1U,
    DMA_REQ_FCIIC0_TX                       = 2U,
    DMA_REQ_FCIIC1_RX                       = 3U,
    DMA_REQ_FCIIC1_TX                       = 4U,
    DMA_REQ_FCSPI0_RX                       = 5U,
    DMA_REQ_FCSPI0_TX                       = 6U,
    DMA_REQ_FCSPI1_RX                       = 7U,
    DMA_REQ_FCSPI1_TX                       = 8U,
    DMA_REQ_FCSPI2_RX                       = 9U,
    DMA_REQ_FCSPI2_TX                       = 10U,
    DMA_REQ_FCSPI3_RX                       = 11U,
    DMA_REQ_FCSPI3_TX                       = 12U,
    DMA_REQ_FCSPI4_RX                       = 13U,
    DMA_REQ_FCSPI4_TX                       = 14U,
    DMA_REQ_FCSPI5_RX                       = 15U,
    DMA_REQ_FCSPI5_TX                       = 16U,
    /* 17 ~ 22 reserved */
    DMA_REQ_FLEXCAN0                        = 23U,
    DMA_REQ_FLEXCAN1                        = 24U,
    DMA_REQ_FLEXCAN2                        = 25U,
    DMA_REQ_FLEXCAN3                        = 26U,
    /* 27 ~ 32 reserved */
    DMA_REQ_ADC0                            = 33U,
    DMA_REQ_ADC1                            = 34U,
    /* 35 ~ 40 reserved */
    DMA_REQ_FCUART0_RX                      = 41U,
    DMA_REQ_FCUART0_TX                      = 42U,
    DMA_REQ_FCUART1_RX                      = 43U,
    DMA_REQ_FCUART1_TX                      = 44U,
    DMA_REQ_FCUART2_RX                      = 45U,
    DMA_REQ_FCUART2_TX                      = 46U,
    DMA_REQ_FCUART3_RX                      = 47U,
    DMA_REQ_FCUART3_TX                      = 48U,
    DMA_REQ_FCUART4_RX                      = 49U,
    DMA_REQ_FCUART4_TX                      = 50U,
    DMA_REQ_FCUART5_RX                      = 51U,
    DMA_REQ_FCUART5_TX                      = 52U,
    DMA_REQ_FCUART6_RX                      = 53U,
    DMA_REQ_FCUART6_TX                      = 54U,
    DMA_REQ_FCUART7_RX                      = 55U,
    DMA_REQ_FCUART7_TX                      = 56U,
    /* 57 ~ 58 reserved */
    DMA_REQ_TPU0                            = 59U,
    DMA_REQ_TPU1                            = 60U,
    DMA_REQ_TPU2                            = 61U,
    DMA_REQ_TPU3                            = 62U,
    DMA_REQ_TPU4                            = 63U,
    DMA_REQ_TPU5                            = 64U,
    DMA_REQ_TPU6                            = 65U,
    DMA_REQ_TPU7                            = 66U,
    DMA_REQ_TPU8                            = 67U,
    DMA_REQ_TPU9                            = 68U,
    DMA_REQ_TPU10                           = 69U,
    DMA_REQ_TPU11                           = 70U,
    DMA_REQ_TPU12                           = 71U,
    DMA_REQ_TPU13                           = 72U,
    DMA_REQ_TPU14                           = 73U,
    DMA_REQ_TPU15                           = 74U,
    DMA_REQ_TPU16TO23                       = 75U,
    DMA_REQ_TPU24TO31                       = 76U,
    DMA_REQ_PORTA                           = 77U,
    DMA_REQ_PORTB                           = 78U,
    DMA_REQ_PORTC                           = 79U,
    DMA_REQ_PORTD                           = 80U,
    DMA_REQ_PORTE                           = 81U,
    /* 82 ~ 85 reserved */
    DMA_REQ_AONTIMER0                       = 86U,
    DMA_REQ_CMP0                            = 87U,
    DMA_REQ_CMP1                            = 88U,
    /* 89 reserved */
    DMA_REQ_PTIMER0                         = 90U,
    DMA_REQ_PTIMER1                         = 91U,
    /* 92 ~ 97 reserved */
    DMA_REQ_FTU0_ALL_CH_OR                  = 98U,
    DMA_REQ_FTU1_ALL_CH_OR                  = 99U,
    DMA_REQ_FTU2_ALL_CH_OR                  = 100U,
    DMA_REQ_FTU3_ALL_CH_OR                  = 101U,
    DMA_REQ_FTU4_ALL_CH_OR                  = 102U,
    DMA_REQ_FTU5_ALL_CH_OR                  = 103U,
    DMA_REQ_FTU6_ALL_CH_OR                  = 104U,
    DMA_REQ_FTU7_ALL_CH_OR                  = 105U,
    /* 106 ~ 109 reserved */
    DMA_REQ_SENT0_CH0_FAST                  = 110U,
    DMA_REQ_SENT0_CH1_FAST                  = 111U,
    DMA_REQ_SENT0_CH2_FAST                  = 112U,
    DMA_REQ_SENT0_CH3_FAST                  = 113U,
    /* 114 ~ 117 reserved */
    DMA_REQ_SENT0_CH0_SLOW                  = 118U,
    DMA_REQ_SENT0_CH1_SLOW                  = 119U,
    DMA_REQ_SENT0_CH2_SLOW                  = 120U,
    DMA_REQ_SENT0_CH3_SLOW                  = 121U,
    /* 122 ~ 125 reserved */
    DMA_REQ_ALWAYS_ENABLE_0                 = 126U,
    DMA_REQ_ALWAYS_ENABLE_1                 = 127U
} DMA_RequestSourceType;

/**
 * @brief Get whether DMAMUX is enabled for the specified DMA channel
 *
 * @param pDmamux the base address of the DMAMUX instance
 * @param u8Channel the selected DMA channel
 * @return true DMAMUX is enabled for the specified DMA channel
 * @return false DMAMUX is disabled for the specified DMA channel
 */
LOCAL_INLINE bool DMAMUX_HWA_GetEnableFlag(const DMAMUX_Type *const pDmamux, uint8_t u8Channel)
{
    uint8_t u8TmpVal = (pDmamux->CHCFG[u8Channel] & DMAMUX_CHCFG_ENBL_MASK) >> DMAMUX_CHCFG_ENBL_SHIFT;
    return (bool)((u8TmpVal != 0U) ? true : false);
}

/**
 * @brief Get the request source for the specified DMA channel
 *
 * @param pDmamux the base address of the DMAMUX instance
 * @param u8Channel the selected DMA channel
 * @return DMA_RequestSourceType the request source of the specified DMA channel
 */
LOCAL_INLINE DMA_RequestSourceType DMAMUX_HWA_GetRequestSource(const DMAMUX_Type *const pDmamux, uint8_t u8Channel)
{
    uint8_t u8TmpVal = (pDmamux->CHCFG[u8Channel] & DMAMUX_CHCFG_SOURCE_MASK) >> DMAMUX_CHCFG_SOURCE_SHIFT;
    return (DMA_RequestSourceType)u8TmpVal;
}

/**
 * @brief Set the request source for the specified DMA channel
 *
 * @param pDmamux the base address of the DMAMUX instance
 * @param u8Channel the selected DMA channel
 * @param bEnable whether to enable DMAMUX for the specified DMA channel
 * @param eReqSrc the request source to set for the specified DMA channel
 */
LOCAL_INLINE void DMAMUX_HWA_SetRequestSource(DMAMUX_Type *const pDmamux, uint8_t u8Channel, bool bEnable,
                                              DMA_RequestSourceType eReqSrc)
{
    pDmamux->CHCFG[u8Channel] = (pDmamux->CHCFG[u8Channel] & ~(DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE_MASK)) |
                                DMAMUX_CHCFG_ENBL(bEnable) | DMAMUX_CHCFG_SOURCE(eReqSrc);
}

/**
 * @brief Get whether periodic trig is enabled for the specified DMA channel
 *
 * @note Only DMA channel 0~3 supports periodic trig
 *
 * @param pDmamux the base address of the DMAMUX instance
 * @param u8Channel the selected DMA channel
 * @return true periodic trig is enabled for the specified DMA channel
 * @return true periodic trig is disabled for the specified DMA channel
 */
LOCAL_INLINE bool DMAMUX_HWA_GetPeriodicTrigFlag(const DMAMUX_Type *const pDmamux, uint8_t u8Channel)
{
    uint8_t u8TmpVal = (pDmamux->CHTRG & (DMAMUX_CHTRG_TRIG_MASK << u8Channel)) >> u8Channel;
    return (bool)((u8TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable periodic trig for the specified DMA channel
 *
 * @note Only DMA channel 0~3 supports periodic trig
 *
 * @param pDmamux the base address of the DMAMUX instance
 * @param u8Channel the selected DMA channel
 * @param bEnable whether to enable periodic trig for the specified DMA channel
 */
LOCAL_INLINE void DMAMUX_HWA_SetPeriodicTrigFlag(DMAMUX_Type *const pDmamux, uint8_t u8Channel, bool bEnable)
{
    pDmamux->CHTRG = (pDmamux->CHTRG & ~(DMAMUX_CHTRG_TRIG_MASK << u8Channel)) | (DMAMUX_CHTRG_TRIG(bEnable) << u8Channel);
}

/** @}*/

#endif /* _HWA_DMAMUX_H_ */
