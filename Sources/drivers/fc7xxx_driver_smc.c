/**
 * @file fc7xxx_driver_smc.c
 * @author Flagchip0105
 * @brief FC7xxx SMC driver type definition and API
 * @version 0.1.0
 * @date 2024-01-08
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2024-01-08    Flagchip0105    N/A          FC7240 First version
********************************************************************************/
#include "fc7xxx_driver_smc.h"

/**
 * @brief Set system mode
 *
 * @param eMode MCU low power mode
 * @return Smc return type
 */
SMC_StatusType SMC_SetSystemMode(const SMC_ModeType eMode)
{
    SMC_StatusType eRet = SMC_STATUS_SUCCESS;

    DEV_ASSERT(eMode <= SMC_MODE_STANBY_3);

    switch (eMode)
    {
    case SMC_MODE_RUN:
        /* Clear the SLEEPDEEP bit to disable deep sleep mode */
        CM7_HWA_DisableDeepSleep();

        break;
    case SMC_MODE_STOP:
        /* switch smc mode to stop mode */
        SMC_HWA_SetStopModeCtrl(SMC_STOP_MODE);
        /* Set the SLEEPDEEP bit to enable deep sleep mode (STOP)*/
        CM7_HWA_EnableDeepSleep();

        /* Cpu is going into deep sleep state */
        STANDBY();

        break;

    case SMC_MODE_WAIT:
        /* Clear the SLEEPDEEP bit to disable deep sleep mode */
        CM7_HWA_DisableDeepSleep();

        /* Cpu is going into sleep state */
        STANDBY();

        break;

    case SMC_MODE_STANBY_0:
        /* select standby mode*/
        SMC_HWA_SetStandbyMode(SMC_CFG_STANDBY_0);

        /* switch smc mode to standby mode */
        SMC_HWA_SetStopModeCtrl(SMC_STANDBY_MODE);
        /* Set the SLEEPDEEP bit to enable deep sleep mode */
        CM7_HWA_EnableDeepSleep();

        /* Cpu is going into deep sleep state */
        STANDBY();

        break;

    case SMC_MODE_STANBY_1:
        /* select standby mode*/
        SMC_HWA_SetStandbyMode(SMC_CFG_STANDBY_1);

        /* switch smc mode to standby mode */
        SMC_HWA_SetStopModeCtrl(SMC_STANDBY_MODE);

        /* Set the SLEEPDEEP bit to enable deep sleep mode */
        CM7_HWA_EnableDeepSleep();

        /* Cpu is going into deep sleep state */
        STANDBY();
        break;

    case SMC_MODE_STANBY_2:
        /* select standby mode*/
        SMC_HWA_SetStandbyMode(SMC_CFG_STANDBY_2);

        /* switch smc mode to standby mode */
        SMC_HWA_SetStopModeCtrl(SMC_STANDBY_MODE);

        /* Set the SLEEPDEEP bit to enable deep sleep mode */
        CM7_HWA_EnableDeepSleep();

        /* Cpu is going into deep sleep state */
        STANDBY();
        break;

    case SMC_MODE_STANBY_3:
        /* select standby mode*/
        SMC_HWA_SetStandbyMode(SMC_CFG_STANDBY_3);

        /* switch smc mode to standby mode */
        SMC_HWA_SetStopModeCtrl(SMC_STANDBY_MODE);

        /* Set the SLEEPDEEP bit to enable deep sleep mode */
        CM7_HWA_EnableDeepSleep();

        /* Cpu is going into deep sleep state */
        STANDBY();
        break;
    default:
        /* do nothing */
        break;

    }

    return eRet;
}
