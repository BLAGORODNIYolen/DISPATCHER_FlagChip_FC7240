/**
 * @file fc7xxx_driver_intm.c
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

#include "fc7xxx_driver_intm.h"
#include "interrupt_manager.h"

/* ################################################################################## */
/* ##################################### Macros ##################################### */

/* ################################################################################## */
/* ################################# Local Variables ################################ */

static INTM_Type *const     s_aIntm_Base[INTM_INSTANCE_MAX]                             = INTM_BASE_PTRS;
static INTM_ISRCallbackType s_aIntmISRCallback[INTM_INSTANCE_MAX][INTM_IRQ_MONITOR_MAX] = {NULL};
/* ################################################################################## */
/* ########################### Local Functions Prototype ############################ */
void INTM0_IRQHandler(void);
void INTMn_IRQHandler(INTM_InstanceType eInstance);

/* ################################################################################## */
/* ################################# Local Functions ############################### */

/* ################################################################################## */
/* ################################# Global Functions ############################### */

INTM_ReturnType INTM_Init(INTM_InstanceType eInstance, INTM_IrqMonitorType eIrqMonitorIndex, INTM_InitType *pInitCfg)
{
    INTM_MonitorType *pMonitor;

    if ((NULL == pInitCfg) || (eInstance >= INTM_INSTANCE_MAX) || (eIrqMonitorIndex >= INTM_IRQ_MONITOR_MAX))
    {
        return INTM_RETURN_E_PARAM;
    }

    if (pInitCfg->u32SrcDelayCnt >= 0xFFFFFFU)
    {
        return INTM_RETURN_E_PARAM;
    }

    if (pInitCfg->u16IrqNumber >= IRQn_MAX)
    {
        return INTM_RETURN_E_PARAM;
    }

    pMonitor = INTM_HWA_GetIrqMonitor(s_aIntm_Base[eInstance], (uint8_t)eIrqMonitorIndex);
    INTM_HWA_SetIRQReqNum(pMonitor, pInitCfg->u16IrqNumber);
    INTM_HWA_EnableReset(pMonitor, pInitCfg->bEnReset);
    INTM_HWA_EnableInterrupt(pMonitor, pInitCfg->bEnInterrupt);
    INTM_HWA_SetLatency(pMonitor, pInitCfg->u32SrcDelayCnt);
    if (pInitCfg->eMode == INTM_INTERRUPT_MODE_INACTIVE)
    {
        INTM_HWA_EnableInactiveMode(pMonitor, true);
    }
    else
    {
        INTM_HWA_EnableInactiveMode(pMonitor, false);
    }
    s_aIntmISRCallback[eInstance][eIrqMonitorIndex] = pInitCfg->pIntmIsrCallback;
    return INTM_RETURN_OK;
}

INTM_ReturnType INTM_enable(INTM_InstanceType eInstance, bool bEnable)
{
    if (eInstance >= INTM_INSTANCE_MAX)
    {
        return INTM_RETURN_E_PARAM;
    }

    INTM_HWA_Enable(s_aIntm_Base[eInstance], bEnable);

    return INTM_RETURN_OK;
}

INTM_ReturnType INTM_StartInactiveMode(INTM_InstanceType eInstance, INTM_IrqMonitorType eIrqMonitorIndex)
{
    INTM_MonitorType *pMonitor;

    if ((eInstance >= INTM_INSTANCE_MAX) || (eIrqMonitorIndex >= INTM_IRQ_MONITOR_MAX))
    {
        return INTM_RETURN_E_PARAM;
    }

    pMonitor = INTM_HWA_GetIrqMonitor(s_aIntm_Base[eInstance], (uint8_t)eIrqMonitorIndex);
    INTM_HWA_StartInactiveMode(pMonitor);
    return INTM_RETURN_OK;
}

INTM_ReturnType INTM_StopInactiveMode(INTM_InstanceType eInstance, INTM_IrqMonitorType eIrqMonitorIndex)
{
    INTM_MonitorType *pMonitor;

    if ((eInstance >= INTM_INSTANCE_MAX) || (eIrqMonitorIndex >= INTM_IRQ_MONITOR_MAX))
    {
        return INTM_RETURN_E_PARAM;
    }

    pMonitor = INTM_HWA_GetIrqMonitor(s_aIntm_Base[eInstance], (uint8_t)eIrqMonitorIndex);
    INTM_HWA_StopInactiveMode(pMonitor);
    return INTM_RETURN_OK;
}

INTM_ReturnType INTM_SetAcknowledge(INTM_InstanceType eInstance, uint16_t u16IrqNumber)
{
    if (eInstance >= INTM_INSTANCE_MAX)
    {
        return INTM_RETURN_E_PARAM;
    }

    INTM_HWA_SetIACKR(s_aIntm_Base[eInstance], u16IrqNumber);

    return INTM_RETURN_OK;
}

uint32_t INTM_GetCounterValue(INTM_InstanceType eInstance, INTM_IrqMonitorType eIrqMonitorIndex)
{
    INTM_MonitorType *pMonitor;

    if ((eInstance >= INTM_INSTANCE_MAX) || (eIrqMonitorIndex >= INTM_IRQ_MONITOR_MAX))
    {
        return 0;
    }

    pMonitor = INTM_HWA_GetIrqMonitor(s_aIntm_Base[eInstance], (uint8_t)eIrqMonitorIndex);
    return INTM_HWA_GetTimerCounter(pMonitor);
}

INTM_ReturnType INTM_ClearIntFlag(INTM_InstanceType eInstance, INTM_IrqMonitorType eIrqMonitorIndex)
{
    INTM_MonitorType *pMonitor;

    if ((eInstance >= INTM_INSTANCE_MAX) || (eIrqMonitorIndex >= INTM_IRQ_MONITOR_MAX))
    {
        return INTM_RETURN_E_PARAM;
    }

    pMonitor = INTM_HWA_GetIrqMonitor(s_aIntm_Base[eInstance], (uint8_t)eIrqMonitorIndex);
    INTM_HWA_SetTimerCounter(pMonitor, 0U);
    return INTM_RETURN_OK;
}

bool INTM_GetTimeoutStatus(INTM_InstanceType eInstance, INTM_IrqMonitorType eIrqMonitorIndex)
{
    INTM_MonitorType *pMonitor;

    if ((eInstance >= INTM_INSTANCE_MAX) || (eIrqMonitorIndex >= INTM_IRQ_MONITOR_MAX))
    {
        return false;
    }

    pMonitor = INTM_HWA_GetIrqMonitor(s_aIntm_Base[eInstance], (uint8_t)eIrqMonitorIndex);
    return INTM_HWA_ReadStatus(pMonitor);
}

void INTMn_IRQHandler(INTM_InstanceType eInstance)
{
    uint8_t           u8i;
    INTM_MonitorType *pMonitor;

    for (u8i = 0; u8i < (uint8_t)INTM_IRQ_MONITOR_MAX; u8i++)
    {
        pMonitor = INTM_HWA_GetIrqMonitor(s_aIntm_Base[eInstance], u8i);
        if (INTM_HWA_ReadStatus(pMonitor))
        {
            if (s_aIntmISRCallback[eInstance][u8i] != NULL)
            {
                s_aIntmISRCallback[eInstance][u8i]();
            }
        }
    }
}

void INTM0_IRQHandler(void)
{
    INTMn_IRQHandler(INTM_INSTANCE_0);
}
