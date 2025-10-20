/**
 * @file fc7xxx_driver_wdog.c
 * @author Flagchip
 * @brief FC7xxx WDOG driver source code
 * @version 0.1.0
 * @date 2023-12-29
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */

/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2023-12-29    qxw0074        N/A          First version for FC7240
********************************************************************************/

#include "fc7xxx_driver_wdog.h"

/**
 * @brief UNLOCK and REFRESH CMD For MPW FC100. this may not match with FC4150 user manual
 */
#define WDOG_UNLOCK_CMD                 (uint32_t)(0x08181982U)
#define WDOG_REFRESH_CMD                (uint32_t)(0x20CFFC20U)

static WDOG_Type *const s_apWdogBase[WDOG_INSTANCE_COUNT] = WDOG_BASE_PTRS;

static WDOG_IRQ_Callback aIRQCallback[WDOG_INSTANCE_MAX] = {0U};

void WDOG0_IRQHandler(void);
void WDOG1_IRQHandler(void);
/**
 * @brief unlock the wdog before Watch dog reconfigure set.
 * @param instance: WDOG module instance: WDOG0/WDOG1 defined in FC4150.
 */
void WDOG_Unlock(WDOG_InstanceType eInstance)
{
    WDOG_Type *pWdog = s_apWdogBase[eInstance];
    WDOG_HWA_SetCounter(pWdog,WDOG_UNLOCK_CMD);
}

/**
 * @brief feed the watch dog by writing typical cmd to counter.
 * @param instance: WDOG module instance: WDOG0/WDOG1 defined in FC4150.
 */
void WDOG_Refresh(WDOG_InstanceType eInstance)
{
    WDOG_Type *pWdog = s_apWdogBase[eInstance];
    WDOG_HWA_SetCounter(pWdog,WDOG_REFRESH_CMD);
}

/**
 * @brief Initialize the WDOG configuration setting. *
 * @param pWdogCfg: point to WDOG init module type.
 */
void WDOG_Init(WDOG_InstanceType eInstance,WDOG_CfgType* pWdogCfg)
{
    WDOG_Type *pWdog = s_apWdogBase[eInstance];
    uint32_t u32Temp = 0U;

    /* Disable the global interrupt */
    __disable_irq();

    u32Temp = WDOG_CS_WIN(pWdogCfg->bWinEnable)  | WDOG_CS_PRESCALER(pWdogCfg->bPrescalerEnable) |
              WDOG_CS_CLK_SEL(pWdogCfg->eClkSource) | WDOG_CS_TST(pWdogCfg->eTesttype) |
              WDOG_CS_DBG(pWdogCfg->bEnableInDebug)  | WDOG_CS_UPDATE_MASK | WDOG_CS_ENABLE_MASK |
              WDOG_CS_WAIT(pWdogCfg->bEnableInWait)  | WDOG_CS_STOP(pWdogCfg->bEnableInStop);
    if(WDOG_REACTION_NO_INT != pWdogCfg->eTimeoutReaction)
    {
        u32Temp |= (WDOG_CS_INT_MASK | WDOG_CS_DLY_CNT_MSB(pWdogCfg->eTimeoutReaction));
    }
    else
    {
        //Do nothing. Keep disabling the wdog interrupt and no reset dealy.
    }

    WDOG_Unlock(eInstance);

    while (WDOG_HWA_GetUnlockStatus(pWdog) == false)
    {
        /* 0 indicate WDOG locked. Wait until registers are unlocked */
    }

    WDOG_HWA_SetCs(pWdog,u32Temp);

    WDOG_Unlock(eInstance);

    while (WDOG_HWA_GetUnlockStatus(pWdog) == false)
    {
        /* 0 indicate WDOG locked. Wait until registers are unlocked */
    }

    /*  configure the timeout value   */
    WDOG_HWA_SetTimeout(pWdog,pWdogCfg->u16TimeoutValue);

    WDOG_Unlock(eInstance);

    while (WDOG_HWA_GetUnlockStatus(pWdog) == false)
    {
        /* 0 indicate WDOG locked. Wait until registers are unlocked */
    }
    /*  configure window value   */
    WDOG_HWA_SetWindow(pWdog,pWdogCfg->u16WindowValue);

    aIRQCallback[eInstance] = pWdogCfg->pISRCallback;

    /* Enable the global interrupt */
    __enable_irq();


}

void WDOG0_IRQHandler(void)
{
	WDOG_HWA_ClearInterruptFlag(WDOG0);
	if(NULL != aIRQCallback[WDOG_INSTANCE_0])
	{
		(aIRQCallback[WDOG_INSTANCE_0])();
	}
}

void WDOG1_IRQHandler(void)
{
	WDOG_HWA_ClearInterruptFlag(WDOG1);
	if(NULL != aIRQCallback[WDOG_INSTANCE_1])
	{
		(aIRQCallback[WDOG_INSTANCE_1])();
	}
}
