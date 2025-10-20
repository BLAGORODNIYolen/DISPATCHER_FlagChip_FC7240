/**
 * @file fc7xxx_driver_intm.h
 * @author Flagchip
 * @brief FC7240 INTM driver type definition and API
 * @version 0.1.0
 * @date 2024-01-10
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
 *   Revision History:
 *
 *   Version     Date          Initials      CR#          Descriptions
 *   ---------   ----------    ------------  ----------   ---------------
 *   0.1.0       2024-01-10    Flagchip084   N/A          FC7240 release version
 ******************************************************************************** */

#ifndef _DRIVER_INTM_H_
#define _DRIVER_INTM_H_

#include "HwA_intm.h"

typedef enum
{
    INTM_INSTANCE_0   = 0U,
    INTM_INSTANCE_MAX = 1u
} INTM_InstanceType;

typedef enum
{
    INTM_IRQ_MONITOR_0   = 0U,
    INTM_IRQ_MONITOR_1   = 1U,
    INTM_IRQ_MONITOR_MAX = 2U
} INTM_IrqMonitorType;

typedef enum
{
    INTM_RETURN_OK             = 0x00U, /*!< The INTM operation is succeeded */
    INTM_RETURN_E_NOT_OK       = 0x01U, /*!< The INTM operation is failed */
    INTM_RETURN_E_ALREADY_INIT = 0x02U, /*!< The INTM has been initialized. */
    INTM_RETURN_E_UNINIT       = 0x03U, /*!< The INTM is not initialized */
    INTM_RETURN_E_PARAM        = 0x04U  /*!< The INTM parameter is incorrect or out of range. */
} INTM_ReturnType;

typedef enum
{
    INTM_INTERRUPT_MODE_ACTIVE = 0x00U, /*!< INTM is configured as active mode */
    INTM_INTERRUPT_MODE_INACTIVE        /*!< INTM is configured as inactive mode */
} INTM_InterruptModeType;

/**
 * @brief INTM Channel ISR callback function prototype
 *
 */
typedef void (*INTM_ISRCallbackType)(void);

typedef struct
{
    INTM_InterruptModeType eMode;            /*!< INTM active mode */
    bool                   bEnReset;         /*!< Enable Reset */
    bool                   bEnInterrupt;     /*!< Enable Interrupt */
    uint32_t               u32SrcDelayCnt;   /*!< Enable Interrupt */
    uint16_t               u16IrqNumber;     /*!< Monitored interrupt number */
    INTM_ISRCallbackType   pIntmIsrCallback; /*!< INTM interrupt callback. */
} INTM_InitType;

/**
 * @brief Init the INTM.
 * @param eInstance INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 * @param pInitCfg Init Configuration.
 * @return INTM_ReturnType INTM Status.
 */
INTM_ReturnType INTM_Init(INTM_InstanceType eInstance, INTM_IrqMonitorType eIrqMonitorIndex, INTM_InitType *pInitCfg);

/**
 * @brief Enable INTM.
 *
 * @param eInstance INTM instance.
 * @param bEnable Enable INTM.
 * @return INTM_ReturnType INTM Status.
 */
INTM_ReturnType INTM_enable(INTM_InstanceType eInstance, bool bEnable);

/**
 * @brief Start INTM inactive mode.
 * @param eInstance INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 * @return INTM_ReturnType INTM Status.
 */
INTM_ReturnType INTM_StartInactiveMode(INTM_InstanceType eInstance, INTM_IrqMonitorType eIrqMonitorIndex);

/**
 * @brief
 * @param eInstance INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 * @return INTM_ReturnType INTM Status.
 */
INTM_ReturnType INTM_StopInactiveMode(INTM_InstanceType eInstance, INTM_IrqMonitorType eIrqMonitorIndex);

/**
 * @brief Write the interrupt acknowledge.
 *
 * @param eInstance INTM instance.
 * @param u16IrqNumber Interrupt nunmber.
 * @return INTM_ReturnType INTM Status.
 */
INTM_ReturnType INTM_SetAcknowledge(INTM_InstanceType eInstance, uint16_t u16IrqNumber);

/**
 * @brief Return counter value.
 *
 * @param eInstance INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 * @return Counter value.
 */
uint32_t INTM_GetCounterValue(INTM_InstanceType eInstance, INTM_IrqMonitorType eIrqMonitorIndex);

/**
 * @brief Clear the interrupt flag.
 *
 * @param eInstance INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 */
INTM_ReturnType INTM_ClearIntFlag(INTM_InstanceType eInstance, INTM_IrqMonitorType eIrqMonitorIndex);

/**
 * @brief Get the timeout flag. Return true if INTM_TMR value has exceeded the INTM_LATR value.
 *
 * @param eInstance INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 * @return Timeout flag.
 */
bool INTM_GetTimeoutStatus(INTM_InstanceType eInstance, INTM_IrqMonitorType eIrqMonitorIndex);

#endif /* end of _DRIVER_INTM_H_ */
