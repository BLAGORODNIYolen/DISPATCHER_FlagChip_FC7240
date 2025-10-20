/**
 * @file fc7xxx_driver_erm.h
 * @author Flagchip
 * @brief FC7xxx ERM driver type definition and API
 * @version 0.1.0
 * @date 2024-01-14
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2024-01-14    qxw0100        N/A          First version for FC7240
********************************************************************************/
#ifndef _DRIVER_FC7XXX_DRIVER_ERM_H_
#define _DRIVER_FC7XXX_DRIVER_ERM_H_

#include "HwA_erm.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* @addtogroup fc7xxx_driver_erm
 * @{
 */

typedef enum
{
    ERM_STATUS_SUCCESS = 0U,          /**< ERM status success */
    ERM_STATUS_PARAM_INVALID = 1U     /**< ERM status parameter invalid */
} ERM_RetType;

/** @brief Erm interrupt notification type */
typedef void (*ERM_InterruptCallBackType)(void);

/**
 * @brief Structure to configure ERM Init type
 *
 */
typedef struct
{
    ERM_ChannelType eChannel; /*!< ERM enable memory No, No 0-31 */
    ERM_InterruptType eInt;   /*!< ERM Interrupt type */
    uint8 u8ErmEnable;        /*!< ERM enable Interrupt */
    ERM_InterruptCallBackType pIsrNotify;       /**< Erm interrupt notification function pointer */   
} ERM_MemorytInitType;
/**
 * @brief Initialize ERM function
 *
 * @param pErmInt_cfg Initialization structure of ERM
 * @return return 0: initialize successful. 1: invalid parameter
 */

ERM_RetType Erm_Init(const ERM_MemorytInitType *pErmInt_cfg);

/**
 * @brief De-initialize ERM function
 * Restore the ERM instance to its reset state
 */
void Erm_DeInit(void);
/**
 * @brief ERM Read EARn address.
 * @param eChannel The channel type
 * @return u32Address The error address
 */
//uint32_t ERM_ReadAddress(ERM_channelType eChannel);

/**
 * @brief ERM Clear SRn register.
 *
 * This function Clear ERM SR0 register.
 */
void ERM_ClearSRnRegister(void);

/**
 * @brief ERM read SRn register.
 *
 * This function Clear ERM SR0 register.
 * @param u8Index the SRn channel
 */
uint32_t ERM_ReadSRnVal(uint8_t u8Index);

/**
 * @brief ERM clear CRn register.
 *
 * This function Clear ERM CRn register.
 * @param u8Index of the CRn channel
 */
void ERM_ClearCRnVal(uint8_t u8Index);

/**
 * @brief ERM clear SRn register.
 *
 * This function Clear ERM SR0 register.
 * @param u8Index the SRn channel
 */
uint32_t ERM_ClearSRnVal(uint8_t u8Index);
/** @} */ /* fc7xxx_driver_erm */

#if defined(__cplusplus)
}
#endif
#endif /* _DRIVER_FC4XXX_DRIVER_ERM_H_ */
