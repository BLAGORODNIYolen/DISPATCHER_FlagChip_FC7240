/**
 * @file fc7xxx_driver_rgm.h
 * @author Flagchip
 * @brief FC7xxx RGM driver type definition and API
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
*   0.1.0       2024-01-12    Flagchip119    N/A          First version for FC7240
********************************************************************************/
#ifndef _DRIVER_FC7XXX_DRIVER_RCM_H_
#define _DRIVER_FC7XXX_DRIVER_RCM_H_

#include "HwA_rgm.h"

/**
 * @addtogroup fc7xxx_driver_rcgm
 * @{
 */

/** @brief Get which core currently belongs to. */
#define GET_CORE_NUM (*(uint32_t *)0xE0080004)

/** @brief Rgm return type. */
typedef enum
{
    RGM_STATUS_SUCCESS = 0U,
    RGM_STATUS_PARAM_INVALID  = 1U,
    RGM_STATUS_COREID_INVALID = 2U
} RGM_StatusType;

/** @brief Rgm reset pin filter clock type. */
typedef enum
{
    RGM_RESET_FILTER_BUS_CLOCK = 0U,
    RGM_RESET_FILTER_AON32K_CLOCK = 1U
} RGM_FilterClkSrc;

/** @brief Rgm interrupt notification type */
typedef void (*RGM_InterruptCallBackType)(uint32_t u32SRS);

/**
 * @brief This api can get RGM_SRS register that indicate the source of the most recent reset.
 *
 * @return RGM->RGM_SRS register, bit 0-15,29-31 corresponding to RGM_ResetEventType, refer to reference manual for details.
 * @note Multiple flags can be set if multiple reset events occur at the same time
 */
uint32_t RGM_GetLastResetFLag(void);

/**
 * @brief This api can get RGM_SSRS register that indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @returnRGM->RGM_SSRS register, bit 0-15,29-31 corresponding to RGM_ResetEventType, refer to reference manual for details.
 */
uint32_t RGM_GetAllResetFlag(void);

/**
 * @brief This api can clear reset flag of RGM_SSRS register which indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @param eReset Enumeration of reset event flag
 */
void RGM_ClearResetFlagAfterPOR(const RGM_ResetEventType eReset);

/**
 * @brief This api can clear all reset flag of RGM_SSRS register which indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 */
void RGM_ClearAllResetFlagAfterPOR(void);

/**
 * @brief Enable reset pin filter
 *
 * @param eClk Reset pin filter clock source
 * @param u8BusClockFilterWidth Bus clock filter width
 * @param bLpClkEn select whether enable reset pin filter using AON32clock in low power mode
 * @return RGM return type
 * @note If use AON32K clock, A reset signal whose length is less than 2 AON32K clock periods will be filtered
 */
RGM_StatusType RGM_EnableResetFilter(RGM_FilterClkSrc eClk, uint8_t u8BusClockFilterWidth, bool bLpClkEn);

/**
 * @brief Disable reset pin filter
 *
 * @param eClk Reset pin filter clock source
 * @param bLpClkEn select whether disable reset pin filter using AON32clock in low power mode
 * @return RGM return type
 */
RGM_StatusType RGM_DisableResetFilter(RGM_FilterClkSrc eClk, bool bLpClkEn);

/**
 * @brief This api can enable interrupt before an system reset appear.
 *
 * @param eDelay Enumeration of delay cycles
 * @param eResetInterrupt Reset event flag, like: RGM_INT_CLKERR0 | RGM_INT_FCSMU
 * @return RGM return type
 */
RGM_StatusType RGM_EnableSystemResetInt(RGM_ResetDelayType eDelay, RGM_ResetIntMangerType eResetInterrupt);

/**
 * @brief This api can disable interrupt before an system reset appear.
 *
 * @param eResetInterrupt Reset event flag, like: RGM_INT_CLKERR0 | RGM_INT_FCSMU
 * @param bClearDelay Whether to clear delay configuration
 * @return RGM return type
 */
RGM_StatusType RGM_DisableSystemResetInt(RGM_ResetIntMangerType eResetInterrupt, bool bClearDelay);

/**
 * @brief Generate software reset through cotex-m register
 *
 */
void RGM_GenerateSwReset(void);

/**
 * @brief This api can enable interrupt before an CPU0 core related reset appear.
 *
 * @param eCPU0Interrupt Reset event flag, like: RGM_CPU_INT_SWRST | RGM_CPU_INT_SYSRST
 * @param pIsrNotify Interrupt function
 * @return RGM return type
 */
RGM_StatusType RGM_EnableCPU0CoreResetInt(RGM_CPUIntMangerType eCPU0Interrupt,RGM_InterruptCallBackType pIsrNotify);

/**
 * @brief This api can disable interrupt before an CPU0 core related reset appear.
 *
 * @param eCPU0Interrupt Reset event flag, like: RGM_CPU_INT_SWRST | RGM_CPU_INT_SYSRST
 * @return RGM return type
 */
RGM_StatusType RGM_DisableCPU0CoreResetInt(RGM_CPUIntMangerType eCPU0Interrupt);

/**
 * @brief Get the CPU0 exit reset flag
 *
 * @return RGM_CPU_OUT_RST_UNDER CPU0 is under reset
 * @return RGM_CPU_OUT_RST_OUT CPU0 is out of reset
 */
RGM_CPUOutResetType RGM_GetCPU0OutResetFlag(void);

/**
 * @brief Generate a CPU0 software reset.
 *
 */
void RGM_GenerateCPU0SwReset(void);

/**
 * @brief This api can get RGM_C0_SRS register that indicate the source of the most recent CPU0 reset.
 *
 * @return RGM->RGM_C0_SRS register, bit 0-20 corresponding to RGM_ResetEventType, refer to reference manual for details.
 * @note Multiple flags can be set if multiple reset events occur at the same time
 */
uint32_t RGM_GetCPU0LastResetFLag(void);

/**
 * @brief This api can get RGM_C0_SSRS register that indicate all CPU0 reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @returnRGM->RGM_C0_SSRS register, bit 0-20,29-31 corresponding to RGM_CPUResetEventType, refer to reference manual for details.
 */
uint32_t RGM_GetCPU0AllResetFlag(void);

/**
 * @brief This api can clear reset flag of RGM_C0_SSRS register which indicate CPU0 all reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @param eReset Enumeration of reset event flag
 */
void RGM_ClearCPU0ResetFlagAfterPOR(const RGM_CPUResetEventType eReset);

/**
 * @brief This api can clear all reset flag of RGM_C0_SSRS register which indicate CPU0 all reset sources since the last POR or LVD that have not been cleared by software.
 *
 */
void RGM_ClearCPU0AllResetFlagAfterPOR(void);

/** @}*/ /* fc7xxx_driver_rgm */
#endif /* end of _DRIVER_FC7XXX_DRIVER_RGM_H_ */
