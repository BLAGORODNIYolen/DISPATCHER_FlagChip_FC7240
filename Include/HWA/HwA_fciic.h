/**
 * @file HwA_fciic.h
 * @author Flagchip
 * @brief FC7xxx FCIIC hardware access layer
 * @version 0.2.0
 * @date 2023-2-14
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2022/12/31    qxw0052      N/A          First version for FC7300
   *   0.2.0       2023/02/14    qxw0052      N/A          Fix MISRA issues
   ******************************************************************************** */

#ifndef _HWA_FCIIC_H_
#define _HWA_FCIIC_H_

#include "device_header.h"


/**
 * @addtogroup HwA_fciic
 * @{
 */


/* ################################################################################## */
/* ################################### type define ################################## */


/**
 * \brief IIC Command Type Enumeration
 *
 */
typedef enum
{
    FCIIC_TX_CMD_TRANSMIT = 0,           /**< FCIIC_TX_CMD_TRANSMIT                 transmit command */
    FCIIC_TX_CMD_RECEIVE,                /**< FCIIC_TX_CMD_RECEIVE                  receive command*/
    FCIIC_TX_CMD_STOP,                   /**< FCIIC_TX_CMD_STOP                     stop command */
    FCIIC_TX_CMD_RECANDDISCARD,          /**< FCIIC_TX_CMD_RECANDDISCARD            receive and discard data command*/
    FCIIC_TX_CMD_STARTANDTRANSMIT,       /**< FCIIC_TX_CMD_STARTANDTRANSMIT         start and then transmit data */
    FCIIC_TX_CMD_STARTANDTRANSMIT_WITHNAK/**< FCIIC_TX_CMD_STARTANDTRANSMIT_WITHNAK start and then transmit and don't care ACK */

} FCIIC_TX_CMDType;


/**
 * \brief IIC Master status type enumeration
 *
 */
typedef enum
{
    FCIIC_MSR_BBF_STATUS    = 25U,    /**< FCIIC_MSR_BBF_STATUS  Bus Busy Flag             */
    FCIIC_MSR_MBF_STATUS    = 24U,    /**< FCIIC_MSR_MBF_STATUS  Master Busy Flag          */
    FCIIC_MSR_DMF_STATUS    = 14U,    /**< FCIIC_MSR_DMF_STATUS  Data Match Flag           */
    FCIIC_MSR_PLTF_STATUS   = 13U,    /**< FCIIC_MSR_PLTF_STATUS Pin Low Timeout Flag      */
    FCIIC_MSR_FEF_STATUS    = 12U,    /**< FCIIC_MSR_FEF_STATUS  FIFO Error Flag           */
    FCIIC_MSR_ALF_STATUS    = 11U,    /**< FCIIC_MSR_ALF_STATUS  Arbitration Lost Flag     */
    FCIIC_MSR_NDF_STATUS    = 10U,    /**< FCIIC_MSR_NDF_STATUS  NACK Detect Flag          */
    FCIIC_MSR_SDF_STATUS    = 9U,     /**< FCIIC_MSR_SDF_STATUS  STOP Detect Flag          */
    FCIIC_MSR_EPF_STATUS    = 8U,     /**< FCIIC_MSR_EPF_STATUS  End Packet Flag           */
    FCIIC_MSR_RXFPEF_STATUS = 3U,     /**< FCIIC_MSR_EPF_STATUS  RX FIFO Parity Error Flag */
    FCIIC_MSR_TXFPEF_STATUS = 2U,     /**< FCIIC_MSR_EPF_STATUS  TX FIFO Parity Error Flag */
    FCIIC_MSR_RDF_STATUS    = 1U,     /**< FCIIC_MSR_RDF_STATUS  Receive Data Flag         */
    FCIIC_MSR_TDF_STATUS    = 0U      /**< FCIIC_MSR_TDF_STATUS  Transmit Data Flag        */
} FCIIC_MasterStatusType;



/**
 * \brief IIC Slave status type enumeration
 *
 */
typedef enum
{
    FCIIC_SSR_BBF_STATUS   = 25U, /**< FCIIC_SSR_BBF_STATUS Bus Busy Flag              */
    FCIIC_SSR_SBF_STATUS   = 24U, /**< FCIIC_SSR_SBF_STATUS Slave Busy Flag            */
    FCIIC_SSR_SARF_STATUS  = 15U, /**< FCIIC_SSR_SARF_STATUS SMBus Alert Response Flag */
    FCIIC_SSR_GCF_STATUS   = 14U, /**< FCIIC_SSR_GCF_STATUS General Call Flag          */
    FCIIC_SSR_AM1F_STATUS  = 13U, /**< FCIIC_SSR_AM1F_STATUS Address Match 1 Flag      */
    FCIIC_SSR_AM0F_STATUS  = 12U, /**< FCIIC_SSR_AM0F_STATUS Address Match 0 Flag      */
    FCIIC_SSR_TREF_STATUS  = 11U, /**< FCIIC_SSR_TREF_STATUS FIFO Error Flag           */
    FCIIC_SSR_BEF_STATUS   = 10U, /**< FCIIC_SSR_BEF_STATUS Bit Error Flag             */
    FCIIC_SSR_SDF_STATUS   = 9U,  /**< FCIIC_SSR_SDF_STATUS STOP Detect Flag           */
    FCIIC_SSR_RSF_STATUS   = 8U,  /**< FCIIC_SSR_RSF_STATUS Repeated Start Flag        */
    FCIIC_SSR_TAF_STATUS   = 3U,  /**< FCIIC_SSR_TAF_STATUS Transmit ACK Flag          */
    FCIIC_SSR_AVF_STATUS   = 2U,  /**< FCIIC_SSR_AVF_STATUS Address Valid Flag         */
    FCIIC_SSR_RDF_STATUS   = 1U,  /**< FCIIC_SSR_RDF_STATUS Receive Data Flag          */
    FCIIC_SSR_TDF_STATUS   = 0U,  /**< FCIIC_SSR_TDF_STATUS Transmit Data Flag         */
} FCIIC_SlaveStatusType;


/**
 * \brief Master Transmit Data
 *
 * \param pFciic IIC instance value
 * \param tCmdType is command type
 * \param u8Data to transmit
 */
LOCAL_INLINE void FCIIC_Master_HWA_Transmit(FCIIC_Type *pFciic, FCIIC_TX_CMDType tCmdType, uint8_t u8Data)
{
    pFciic->MTDR = FCIIC_MTDR_CMD(tCmdType) | FCIIC_MTDR_DATA(u8Data);
}

/**
 * \brief Master Receive Data
 *
 * \param pFciic IIC instance value
 * \return the data received
 */
LOCAL_INLINE uint8_t FCIIC_Master_HWA_Receive(FCIIC_Type *pFciic)
{
    /* copy data */
    return (uint8_t)((uint8_t)(pFciic->MRDR) & 0xFFU);
}

/**
 * \brief Get and clear IIC master status
 *
 * \param pFciic is IIC instance value
 * \param eStatus is status type
 */
LOCAL_INLINE void FCIIC_Master_HwA_CheckClearStatus(FCIIC_Type *pFciic, FCIIC_MasterStatusType eStatus)
{
    uint32_t u32RetVal;

    u32RetVal = (pFciic->MSR >> eStatus) & 0x01U;


    if (u32RetVal != 0U)
    {
        pFciic->MSR |= (1UL << eStatus); /* w1c */
    }
}

/**
 * \brief This Function is used to get master status
 *
 * \param pFciic is IIC instance value
 * \param eStatus is status type enumeration
 * \return Status value 0 or 1 and 1 is OK
 */
LOCAL_INLINE uint8_t FCIIC_Master_HWA_GetStatus(FCIIC_Type *pFciic, FCIIC_MasterStatusType eStatus)
{
    uint32_t u32RetVal;

    u32RetVal = (pFciic->MSR >> (uint32_t)eStatus) & 0x01U;

    return (uint8_t)(u32RetVal == 1U ? 1U : 0U);
}

/**
 * \brief This Function is used to clear master status
 *
 * \param pFciic is IIC instance value
 * \param u32Value is the clear bits
 */
LOCAL_INLINE void FCIIC_Master_HWA_ClrStatus(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MSR |= u32Value;
}

/**
 * \brief This Function is used to get slave status
 *
 * \param pFciic is IIC instance value
 * \param eStatus is status type enumeration
 * \return Status value 0 or 1 and 1 is OK
 */
LOCAL_INLINE uint8_t FCIIC_Slave_HWA_GetStatus(FCIIC_Type *pFciic, FCIIC_SlaveStatusType eStatus)
{
    uint32_t u32RetVal;

    u32RetVal = (pFciic->SSR >> (uint32_t)eStatus) & 0x01U;

    return (uint8_t)(u32RetVal == 1U ? 1U : 0U);
}

/**
 * \brief This Function is used to clear slave status
 *
 * \param pFciic is IIC instance value
 * \param u32Value is the clear bits value
 */
LOCAL_INLINE void FCIIC_Slave_HWA_ClrStatus(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->SSR |= u32Value;
}

/**
 * \brief Slave Transmit Data
 *
 * \param pFciic IIC instance value
 * \param u8Data to transmit
 */
LOCAL_INLINE void FCIIC_Slave_HWA_Transmit(FCIIC_Type *pFciic, uint8_t u8Data)
{
    pFciic->STDR = FCIIC_STDR_DATA(u8Data);
}


/**
 * \brief Slave Get Data
 *
 * \param pFciic IIC instance value
 * \return the data value
 */
LOCAL_INLINE uint8_t FCIIC_Slave_HWA_Receive(FCIIC_Type *pFciic)
{
    /* copy data */
    return (uint8_t)((uint8_t)(pFciic->SRDR) & 0xFFU);
}

/**
 * \brief Enable Receive Interrupt
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE void FCIIC_Master_HWA_EnableReceiveInterrupt(FCIIC_Type *pFciic)
{
    pFciic->MIER |= FCIIC_MIER_RDIE_MASK;
}

/**
 * \brief Disable Receive Interrupt
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE void FCIIC_Master_HWA_DisableReceiveInterrupt(FCIIC_Type *pFciic)
{
    pFciic->MIER &= ~FCIIC_MIER_RDIE_MASK;
}

/**
 * \brief Enable Error Interrupt
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE void FCIIC_Master_HWA_EnableErrorInterrupt(FCIIC_Type *pFciic)
{
    pFciic->MIER |= FCIIC_MIER_FEIE_MASK;
}

/**
 * \brief Disable Error Interrupt
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE void FCIIC_Master_HWA_DisableErrorInterrupt(FCIIC_Type *pFciic)
{
    pFciic->MIER &= FCIIC_MIER_FEIE_MASK;
}

/**
 * \brief Get Error Flag
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE uint32_t FCIIC_Master_HWA_GetErrorFlag(FCIIC_Type *pFciic)
{
    return pFciic->MSR & FCIIC_MSR_FEF_MASK;
}

/**
 * \brief Clr Error Flag
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE void FCIIC_Master_HWA_ClrErrorFlag(FCIIC_Type *pFciic)
{
    pFciic->MSR |= FCIIC_MSR_FEF_MASK;
}

/**
 * \brief Enable Transmit Interrupt
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE void FCIIC_Master_HWA_EnableTransmitInterrupt(FCIIC_Type *pFciic)
{
    pFciic->MIER |= FCIIC_MIER_TDIE_MASK;
}

/**
 * \brief Disable Transmit Interrupt
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE void FCIIC_Master_HWA_DisableTransmitInterrupt(FCIIC_Type *pFciic)
{
    pFciic->MIER &= ~FCIIC_MIER_TDIE_MASK;
}


/**
 * \brief Enable Receive Interrupt
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE void FCIIC_Slave_HWA_EnableReceiveInterrupt(FCIIC_Type *pFciic)
{
    pFciic->SIER |= FCIIC_SIER_RDIE_MASK;
}

/**
 * \brief Disable Receive Interrupt
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE void FCIIC_Slave_HWA_DisableReceiveInterrupt(FCIIC_Type *pFciic)
{
    pFciic->SIER &= ~FCIIC_SIER_RDIE_MASK;
}

/**
 * \brief Enable Error Interrupt
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE void FCIIC_Slave_HWA_EnableErrorInterrupt(FCIIC_Type *pFciic)
{
    pFciic->SIER |= FCIIC_SIER_TREIE_MASK | FCIIC_SIER_BEIE_MASK ;
}

/**
 * \brief Disable Error Interrupt
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE void FCIIC_Slave_HWA_DisableErrorInterrupt(FCIIC_Type *pFciic)
{
    pFciic->SIER &= ~(FCIIC_SIER_TREIE_MASK | FCIIC_SIER_BEIE_MASK);
}

/**
 * \brief Get Error Flag
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE uint32_t FCIIC_Slave_HWA_GetErrorFlag(FCIIC_Type *pFciic)
{
    return pFciic->SSR & (FCIIC_SSR_TREF_MASK | FCIIC_SSR_BEF_MASK);
}

/**
 * \brief Clear Error Flag
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE void FCIIC_Slave_HWA_ClrErrorFlag(FCIIC_Type *pFciic)
{
    pFciic->SSR |= (FCIIC_SSR_TREF_MASK | FCIIC_SSR_BEF_MASK);
}

/**
 * \brief Enable Transmit Interrupt
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE void FCIIC_Slave_HWA_EnableTransmitInterrupt(FCIIC_Type *pFciic)
{
    pFciic->SIER |= FCIIC_SIER_TDIE_MASK;
}

/**
 * \brief FCIIC Disable Transmit Interrupt
 *
 * \param pFciic  IIC instance value
 */
LOCAL_INLINE void FCIIC_Slave_HWA_DisableTransmitInterrupt(FCIIC_Type *pFciic)
{
    pFciic->SIER &= ~FCIIC_SIER_TDIE_MASK;  /* Receive Interrupt Enable    */
}


/**
 * \brief Set FCIIC MCR register
 *
 * \param pFciic FCIIC instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetMcr(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MCR = u32Value;
}

/**
 * \brief Attach FCIIC MCR register
 *
 * \param pFciic FCIIC instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_AttachMcr(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MCR |= u32Value;
}


/**
 * \brief Set FCIIC MDER register
 *
 * \param pFciic FCIIC instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetMder(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MDER = u32Value;
}

/**
 * \brief Set FCIIC MCFGR0 register
 *
 * \param pFciic FCIIC instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetMCFGR0(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MCFGR0 = u32Value;
}

/**
 * \brief Set FCIIC MCFGR1 register
 *
 * \param pFciic FCIIC instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetMCFGR1(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MCFGR1 = u32Value;
}

/**
 * \brief Set FCIIC MCFGR2 register
 *
 * \param pFciic FCIIC instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetMCFGR2(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MCFGR2 = u32Value;
}

/**
 * \brief Set FCIIC MCFGR3 register
 *
 * \param pFciic FCIIC instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetMCFGR3(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MCFGR3 = u32Value;
}

/**
 * \brief Set FCIIC MFCR register
 *
 * \param pFciic FCIIC instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetMFCR(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MFCR = u32Value;
}

/**
 * \brief Set FCIIC MCCR register
 *
 * \param pFciic FCIIC instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetMCCR(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MCCR = u32Value;
}

/**
 * \brief Set FCIIC SDER register
 *
 * \param pFciic FCIIC instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetSDER(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->SDER = u32Value;
}



/**
 * \brief Set FCIIC SCFGR1 register
 *
 * \param pFciic FCIIC instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetSCFGR1(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->SCFGR1 = u32Value;
}

/**
 * \brief Set FCIIC MCCR register
 *
 * \param pFciic FCIIC instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetSCFGR2(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->SCFGR2 = u32Value;
}

/**
 * \brief Set FCIIC MCCR register
 *
 * \param pFciic FCIIC instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetSAMR(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->SAMR = u32Value;
}

/**
 * \brief Set FCIIC MCCR register
 *
 * \param pFciic FCIIC instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetSCR(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->SCR = u32Value;
}



/** @}*/

#endif /* end for #ifndef _HWA_FCIIC_H_ */
