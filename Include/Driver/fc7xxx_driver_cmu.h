/**
 * @file fc7xxx_driver_cmu.h
 * @author  Flagchip085
 * @brief FC7xxx CMU driver type definition and API
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2024-01-12    Flagchip085    N/A          First version for FC7240
********************************************************************************/
#ifndef _DRIVER_FC7XXX_DRIVER_CMU_H_
#define _DRIVER_FC7XXX_DRIVER_CMU_H_

#if defined(__cplusplus)
extern "C" {
#endif
/**
 * @addtogroup fc7xxx_driver_cmu
 * @{
 */

#include "device_header.h"

/** @brief CMU Instance type. */
typedef enum
{
    CMU_INSTANCE_0   = 0,
    CMU_INSTANCE_1   = 1,
    CMU_INSTANCE_2   = 2,
    CMU_INSTANCE_3   = 3,
    CMU_INSTANCE_4   = 4,
    CMU_INSTANCE_INVALID = CMU_INSTANCE_COUNT
} CMU_InstanceType;

/**
 * @brief CMU operation return values
 *
 */
typedef enum
{
    CMU_VALID        = 0x0U,       	/*!< The CMU status valid */
    CMU_CLK_ERROR    = 0x1U,       	/*!< The CMU related clock error */
} CMU_StatusType;

typedef enum
{
    CMU_CMU4_REF_CLK_NONE = 0U, /*Not Select Cmu4 Reference clock.*/
    CMU_CMU4_REF_CLK_FOSC = 1U, /*Select the FOSC as Cmu4 Reference clock.*/
    CMU_CMU4_REF_CLK_SIRC = 2U  /*Select the SIRC as Cmu4 Reference clock.*/
} CMU_Cmu4ClkSrcType;

typedef enum
{
    CMU_INTERRUPT_NONE  = 0,            /*!< No CMU interrupt. */
    CMU_INTERRUPT_LOC   = 1,            /*!< CMU_ST[LOC] bit, Monitor clock is loss. */
    CMU_INTERRUPT_MIS   = 2            /*!< CMU_ST[MIS] bit, Monitor clock is mismatched. */
} CMU_InterruptType;

typedef enum
{
    CMU_STOP_MODE       = 0,             /*!< CMU enable in Stop Mode. */
    CMU_STANDBY_MODE    = 1             /*!< CMU enable in Standby Mode. */
} CMU_LowpowerModeType;

typedef enum
{
    CMU_REFCLK_NODIV      = 0U,        /*!< Clock output is disabled.  */
    CMU_REFCLK_DIV_BY2    = 1U,        /*!< Divided by 2.              */
    CMU_REFCLK_DIV_BY4    = 2U,        /*!< Divided by 4.              */
    CMU_REFCLK_DIV_BY8    = 3U,        /*!< Divided by 8.              */
    CMU_REFCLK_DIV_BY16   = 4U,        /*!< Divided by 16.              */
    CMU_REFCLK_DIV_BY32   = 5U,        /*!< Divided by 32.             */
    CMU_REFCLK_DIV_BY64   = 6U,        /*!< Divided by 64.             */
    CMU_REFCLK_DIV_BY128  = 7U         /*!< Divided by 128.             */
} CMU_RefClockDivType;

/**
 * @brief CMU Channel ISR callback function prototype
 *
 */
typedef void (*CMU_ISRCallbackType)(const CMU_InstanceType eInstance, const CMU_InterruptType eStatus);

/** @brief CMU configure structure. */
typedef struct
{
    bool bIntEnable;                   /*!< CMU_CTRL[IRQ_EN] bit, interrupt enable, if this bit asserted, either LOC or MIS asserted can lead the interrupt.*/
    bool bLpen;                        /*!< CMU_CTRL[LP_EN] bit, standby mode enable, need STOP_EN asserted.*/
    bool bSten;                        /*!< CMU_CTRL[STOP_EN] bit, stop mode enable.*/
    bool bEnable;                      /*!< CMU_CTRL[EN] bit, CMU enable on initialization. If bEnable is false, the CMU is configured only,
    										and should be enabled by calling CMU_Enable.*/
    uint8_t u8PerMonitorWindow;        /*!< CMU_PERIOD[WINDOW] bits, Period Monitor mode WIDOW. If u8PerMonitorWindow exceed the max period,
    										the max period value will be used instead of u8PerMonitorWindow.*/
    bool bPerMonitorEnable;            /*!< CMU_PERIOD[EN] bit, Period Monitor mode ENABLE.*/
    CMU_RefClockDivType eDiv;          /*!< Divider of reference clock.*/
    CMU_ISRCallbackType pIsrCallback;  /*!< ISR Callback.*/
} CMU_CfgType;


/* global functions */
/**
 * @brief Initialize the CMU instance.
 *
 * @param eInstance Cmu instance.
 * @param pInitCfg Init configuration.
 * @return Cmu status.
 */
CMU_StatusType CMU_Init(CMU_InstanceType eInstance, const CMU_CfgType *pInitCfg);

/**
 * @brief Enable CMU
 *
 * @param eInstance CMU Instance
 */
void CMU_Enable(CMU_InstanceType eInstance);

/**
 * @brief Disable CMU instance, this would needed for low powermode if monitor/referrence clock would be shut down
 *
 * @param eInstance CMU Instance
 */
void CMU_Disable(CMU_InstanceType eInstance);

/**
 * @brief Get the interrupt type of CMU.
 *
 * @param eInstance CMU Instance
 * @return The interrupt type.
 */
CMU_InterruptType CMU_GetInterruptType(CMU_InstanceType eInstance);

/**
 * @brief Set the cmu4 reference source clock.
 *
 * @param eSrc Source clock type.
 * @return CMU_VALID Set CMU reference clock successfully
 * 		   CMU_CLK_ERROR Set CMU reference clock failed
 */
CMU_StatusType CMU_SetCmu4RefSrc(CMU_Cmu4ClkSrcType eSrc);

/**
 * @brief Enable CMU interrupt.
 *
 * @param eInstance CMU Instance.
 */
void CMU_EnableInterrupt(CMU_InstanceType eInstance);

/**
 * @brief Disable CMU interrupt.
 *
 * @param eInstance CMU Instance.
 */
void CMU_DisableInterrupt(CMU_InstanceType eInstance);

/**
 * @brief Get CMU counter value.
 *
 * @param eInstance CMU Instance.
 */
uint32_t CMU_GetCount(CMU_InstanceType eInstance);

/**
 * @brief Get Min counter value.
 *
 * @param eInstance CMU Instance.
 */
uint32_t CMU_GetMinCount(CMU_InstanceType eInstance);

/**
 * @brief Get Max counter value.
 *
 * @param eInstance CMU Instance.
 */
uint32_t CMU_GetMaxCount(CMU_InstanceType eInstance);

/**
 * @brief Enable cmu low power mode.
 *
 * @param eInstance CMU Instance.
 * @param eMode Low power mode.
 * @param bModeEnable Mode enable
 * @param bRestartEnable Restart enable.
 */
void CMU_LowPowerModeEnable(CMU_InstanceType eInstance, CMU_LowpowerModeType eMode, bool bModeEnable, bool bRestartEnable);

/** @}*/ /* fc7xxx_driver_cmu */
#if defined(__cplusplus)
}
#endif
#endif
