/**
 * @file fc7xxx_driver_eim.h
 * @author Flagchip
 * @brief FC7xxx EIM driver type definition and API
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
*   ---------   ----------    ------------   ----------   -------------------
*   0.1.0       2024-01-14    qxw0100        N/A          First version for FC7240
********************************************************************************/
#ifndef _DRIVER_FC7XXX_DRIVER_EIM_H_
#define _DRIVER_FC7XXX_DRIVER_EIM_H_

#include "HwA_eim.h"
#include "device_header.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup fc4xxx_driver_eim
 * @{
 */


/**
 * @brief Initialize EIM function
 *
 * @param pEimInitCfg Initialization structure of EIM
 * @return return 0: initialize successful. 1: invalid parameter
 */
EIM_RetType EIM_Init(const EIM_InitType *pEimInitCfg);

/**
 * @brief Initialize EIM function
 *
 * @param eEimChannel channel want to set
 * @param eDwpType Cpu to use
 * @param bLockStatus Lock the cpu control settings
 * @return Set operation success/failed
 */
EIM_RetType EIM_SetDwpMode(const EIM_ChannelType eEimChannel, const EIM_DWPType eDwpType, bool bLockStatus);

/**
 * @brief Deinin EIM function
 *
 */
void Eim_Deinit(void);

/**
 * @brief Enable CPU lockstep monitor
 *
 * @param eEimCpuType EIM_CPU0_LOCKSTEP or EIM_CPU1_LOCKSTEP
 * @param eMonitorType EIM_MONITOR0 or EIM_MONITOR1
 */
void EIM_CpuLockStepMonitorSet_MonSet(const EIM_CPU_ChnType eEimCpuType,const EIM_MONType eMonitorType);

/**
 * @brief Clear CPU lockstep monitor
 *
 * @param eEimCpuType EIM_CPU0_LOCKSTEP or EIM_CPU1_LOCKSTEP
 * @param eMonitorType EIM_MONITOR0 or EIM_MONITOR1
 */
void EIM_CpuLockStepMonitorSet_MonClr(const EIM_CPU_ChnType eEimCpuType,const EIM_MONType eMonitorType);

/**
 * @brief Clean CPU lockstep monitor bit
 *
 * @param eEimCpuType EIM_CPU0_LOCKSTEP or EIM_CPU1_LOCKSTEP
 * @param eMonitorType EIM_MONITOR0 or EIM_MONITOR1
 */
void EIM_CpuLockStepMonitorClr(const EIM_CPU_ChnType eEimCpuType, const EIM_MONType eMonitorType);

/** @} */ /* fc7xxx_driver_eim */

#if defined(__cplusplus)
}
#endif
#endif /* _DRIVER_FC4XXX_DRIVER_EIM_H_ */
