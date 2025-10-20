/**
 * @file fc7xxx_driver_fciic.h
 * @author Flagchip
 * @brief FC7xxx FCIIC driver type definition and API
 * @version 0.2.0
 * @date 2022-12-05
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */

/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2022/12/31    qxw0052      N/A          First version for FC7300
   *   0.2.0       2023/02/14    qxw0052      N/A          Fix MISRA issues
   *********************************************************************************/

#ifndef _DRIVER_FC7XXX_DRIVER_FCIIC_H_
#define _DRIVER_FC7XXX_DRIVER_FCIIC_H_

#include "HwA_fciic.h"

/**
 * @addtogroup fc7xxx_driver_iic
 * @{
 */

/**
 * \brief IIC initial data define
 *
 */
typedef struct
{
    uint32_t            u32ClkSrcHz;  /**< module clock hz                                                                          */
    uint8_t             bMasterMode;  /**< bMasterMode=1 master mode                                                                */
    uint8_t             u8SlaveAddr;  /**< if bMasterMode=0, this is used, and address format is 7bits , not ended with R/W bit     */
    uint8_t             bTxFifoWMrk;  /**< Tx FIFO Water Mark, FIFO always on, transmit FIFO is equal or less than TXWATER, set TDF */
    uint8_t             bRxFifoWMrk;  /**< Tx FIFO Water Mark, FIFO always on, receive FIFO is greater than RXWATER, set RDF        */
    uint8_t             bEnDma;       /**< Enable DMA)                                                */
    uint32_t            u32Frequency; /**< normal frequency, only used in master mode                                               */

} FCIIC_InitType;



/**
 * \brief IIC transmit data define
 *
 */
typedef struct
{
    FCIIC_TX_CMDType     eCmd;       /**< command type   */
    uint8_t              u8Data;     /**< 8bit data      */
} FCIIC_TxDataType;


/**
 * \brief IIC receive data define
 *
 */
typedef struct
{
    uint8_t              u8Data;      /**< 8bit data      */
} FCIIC_RxDataType;


/** Error call back function type */
typedef void (*FCIIC_ErrorInterrupt_CallBackType)(uint8_t u8IicIndex, uint8_t bMaster, uint32_t u32Error);

/** Receive call back function type */
typedef void (*FCIIC_RxInterrupt_CallBackType)(uint8_t u8IicIndex, FCIIC_RxDataType *pRxCfg);

/**
 * \brief IIC interrupt callback setting
 *
 */
typedef struct
{
    uint8_t                             bEnErrorInterrupt; /**< enable error interrupt                      */
    FCIIC_ErrorInterrupt_CallBackType   pErrorNotify;      /**< error interrupt callback function address   */
    uint8_t                             bEnRxInterrupt;    /**< enable receive interrupt                    */
    FCIIC_RxInterrupt_CallBackType      pRxNotify;         /**< receive interrupt callback function address */

} FCIIC_InterruptType;


/**
 * \brief This Function is used to initial IIC instance
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pInitCfg is the structure address of IIC initial configuration parameters, and it contains IIC instance
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Init(uint8_t u8IicIndex, FCIIC_InitType *pInitCfg);

/**
 * \brief This Function is used to de-initial IIC instance
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pInitCfg is the structure address of IIC initial configuration parameters, bMaster should be set
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_DeInit(uint8_t u8IicIndex, FCIIC_InitType *pInitCfg);

/**
 * \brief This Function is used to configure IIC master interrupt
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pIntCfg contains IIC instance and interrupt callback functions
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Master_SetInterrupt(uint8_t u8IicIndex, FCIIC_InterruptType *pIntCfg);

/**
 * \brief This Function is used to transmit data in master mode
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pTxData contains IIC instance and buffer address
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Master_Transmit(uint8_t u8IicIndex, FCIIC_TxDataType *pTxData);

/**
 * \brief This Function is used to get master status
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param eStatus is status type enumeration
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Master_GetStatus(uint8_t u8IicIndex, FCIIC_MasterStatusType eStatus);

/**
 * \brief This Function is used to receive data when polling (not used when rx interrupt enabled) in master mode
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pRxData contains IIC instance
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Master_Receive(uint8_t u8IicIndex, FCIIC_RxDataType *pRxData);

/**
 * \brief This Function is used to get master error value
 *
 * \param u8IicIndex Iic Index, 0,1
 * \return error value
 */
uint32_t FCIIC_Master_GetError(uint8_t u8IicIndex);

/**
 * \brief This Function is used to clear master error value
 *
 * \param u8IicIndex Iic Index, 0,1
 */
void FCIIC_Master_ClrError(uint8_t u8IicIndex);

/**
 * \brief This Function is used to configure IIC slave interrupt
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pIntCfg contains IIC instance and interrupt callback functions
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Slave_SetInterrupt(uint8_t u8IicIndex, FCIIC_InterruptType *pIntCfg);

/**
 * \brief This Function is used to transmit data in slave mode
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pTxData contains IIC instance and buffer address
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Slave_Transmit(uint8_t u8IicIndex, FCIIC_TxDataType *pTxData);

/**
 * \brief This Function is used to receive data when polling (not used when rx interrupt enabled) in slave mode
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pRxData contains IIC instance and buffer address
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Slave_Receive(uint8_t u8IicIndex, FCIIC_RxDataType *pRxData);

/**
 * \brief This Function is used to get slave error value
 *
 * \param u8IicIndex Iic Index, 0,1
 * \return error value
 */
uint32_t FCIIC_Slave_GetError(uint8_t u8IicIndex);

/**
 * \brief This Function is used to clear slave error value
 *
 * \param u8IicIndex Iic Index, 0,1
 */
void FCIIC_Slave_ClrError(uint8_t u8IicIndex);


#ifdef FCIIC_MASTER_STOP
    uint8_t FCIIC_Master_Stop(uint8_t u8IicIndex);
#endif


/** @}*/

#endif
