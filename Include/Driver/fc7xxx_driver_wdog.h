/**
 * @file fc7xxx_driver_wdog.h
 * @author Flagchip
 * @brief FC7xxx WDOG driver type definition and API
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

#ifndef _DRIVER_FC7XXX_DRIVER_WDOG_H_
#define _DRIVER_FC7XXX_DRIVER_WDOG_H_
#include "HwA_wdog.h"

/**
 * @addtogroup fc7xxx_driver_wdog
 * @{
 */

/** @brief  WDOG ISR callback function declaration. */
typedef void (*WDOG_IRQ_Callback)(void);

/** @brief  WDOG clock instance declaration. */
typedef enum
{
    WDOG_INSTANCE_0 = 0U,  /*!< WDOG instance 0 is selected */
    WDOG_INSTANCE_1 = 1U,  /*!< WDOG instance 1 is selected */
    WDOG_INSTANCE_MAX      /*!< WDOG instance MAX number */
} WDOG_InstanceType;

/** @brief  WDOG clock source select, mapping with WDOG_CS[CLK_SEL] bit filed definition. */
typedef enum
{
    WDOG_BUS_CLK                        = 0x00U, /* Bus clock */
    WDOG_AON_CLK                        = 0x01U, /* AON clock, if choose this clock need to configure AON clock in SMISC setting */
    WDOG_SOSC_CLK                       = 0x02U, /* SOSC clock */
    WDOG_SIRC_CLK                       = 0x03U  /* SIRC clock */
} WDOG_ClkSelType;

/** @brief  WDOG test mode, mapping with WDOG_CS[TST] bit filed definition. */
typedef enum
{
    WDOG_TST_DISABLED                      = 0x00U, /* Test mode disabled */
    WDOG_USER_MODE                         = 0x01U, /* User mode enabled. (Test mode disabled.) */
    WDOG_TST_MODE_LOW                      = 0x02U, /* Test mode enabled, only the low byte is used. */
    WDOG_TST_MODE_HIGH                     = 0x03U  /* Test mode enabled, only the high byte is used. */
} WDOG_TestType;

/** @brief  WDOG delay time to generate the reset. */
typedef enum
{
    WDOG_REACTION_INT_128_CYCLE                  = 0x00U, /* Enable the timeout interrupt, and the delay to generate the reset is configured to 128 bus clock cycles */
    WDOG_REACTION_INT_256_CYCLE                  = 0x01U, /* Enable the timeout interrupt, and the delay to generate the reset is configured to 256 bus clock cycles */
    WDOG_REACTION_INT_512_CYCLE                  = 0x02U, /* Enable the timeout interrupt, and the delay to generate the reset is configured to 512 bus clock cycles */
    WDOG_REACTION_INT_1024_CYCLE                 = 0x03U, /* Enable the timeout interrupt, and the delay to generate the reset is configured to 1024 bus clock cycles */
    WDOG_REACTION_NO_INT                         = 0x04U  /* Disable the timeout interrupt, and generate the reset immediately */
} WDOG_TimeoutReactionType;

/** @brief WDOG init module type, include register setting for WDOG_CS/WDOG_TIMEOUT/WDOG_WINDOW. */
typedef struct
{
    bool                      bWinEnable;         /**@  windowed watch dog mode */
    bool                      bPrescalerEnable;   /**@  fixed 256 prescaler from clock input */
    WDOG_ClkSelType           eClkSource;         /**@  WDOG clock source  */
    WDOG_TimeoutReactionType  eTimeoutReaction;   /**@  WDOG timeout reaction. */
    bool                      bEnable;            /**@  WDOG enable bit */
    WDOG_TestType             eTesttype;          /**@  WDOG_CS[TST] */
    bool                      bEnableInDebug;     /**@  WDOG_CS[DBG] */
    bool                      bEnableInWait;      /**@  WDOG_CS[WAIT] */
    bool                      bEnableInStop;      /**@  WDOG_CS[STOP] */
    uint16_t                  u16WindowValue;     /**@  The window value */
    uint16_t                  u16TimeoutValue;    /**@  The timeout value */
    WDOG_IRQ_Callback         pISRCallback;       /**@  The WDOG ISR callback function. */
} WDOG_CfgType;

/**
 * @brief unlock the wdog before Watch dog reconfigure set.
 * @param eInstance: WDOG module instance: WDOG0/WDOG1 defined in FC4150.
 */
void WDOG_Unlock(WDOG_InstanceType eInstance);

/**
 * @brief feed the watch dog by writing typical CMD to counter.
 * @param eInstance: WDOG module instance: WDOG0/WDOG1 defined in FC4150.
 */
void WDOG_Refresh(WDOG_InstanceType eInstance);

/**
 * @brief Initialize the WDOG configuration setting.
 * @param eInstance: WDOG module instance: WDOG0/WDOG1 defined in FC4150.
 * @param pWdogCfg: point to WDOG initial module type.
 */
void WDOG_Init(WDOG_InstanceType eInstance, WDOG_CfgType* pWdogCfg);

/**
 * @brief WDOG_ReInit reserved. *
 * @param eInstance Wdog instance for re-init.
 */
void WDOG_ReInit(WDOG_InstanceType eInstance);
/** @}*/ /* fc7xxx_driver_wdog */


#endif


