/**
 * @file fc7xxx_driver_cpm.h
 * @author Flagchip
 * @brief FC7xxx CPM driver type definition and API
 * @version 0.1.0
 * @date 2024-01-5
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
  *   Revision History:
  *
  *   Version     Date          Initials      CR#          Descriptions
  *   ---------   ----------    ------------  ----------   ---------------
  *   0.1.0       2024-1-5      Flagchip120   N/A          First version for FC7240 
  ******************************************************************************** */
#ifndef _DRIVER_FC7XXX_DRIVER_CPM_H_
#define _DRIVER_FC7XXX_DRIVER_CPM_H_
#include "device_header.h"
#include "HwA_cpm.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup fc7xxx_driver_cpm
 * @{
 */

/** @brief Cpm interrupt notification type */
typedef void (*CPM_InterruptCallBackType)(void);
/** @brief Cpm interrupt configuration type */
typedef struct
{
    uint8_t u8CpmEnable;                    /**< whether enable cpm interrupt */
    FPU_IntType eFPU_IntType;                    /**< the type of interrupt */
    CPM_InterruptCallBackType pIsrNotify;       /**< Cpm interrupt notification function pointer */
} CPM_InterruptType;


#ifdef FPU_USED_ENABLE
/**
 * @brief CPM_Read_FPSCR
 * Return the current value of FPSCR
 * @return u32RetVal
 */
uint32_t CPM_Read_FPSCR(void);

/**
 * @brief CPM_Write_FPSCR
 *
 * @param u32SetVal set the value for FPSCR
 */
void CPM_Write_FPSCR(uint32_t u32SetVal);

/**
 * @brief Deinit Cpm set interrupt
 *
 * Restore the Cpm FISCR to its reset state
 */
void CPM_DeInitInterrupt(void);

#endif



/* ----------------------------------------------------------------------------
   --   Global Api
   ---------------------------------------------------------------------------- */
/**
 * @brief Configures the CPM module interrupts.
 *
 * This function configures the CPM module interrupts to enable/disable various interrupt sources.
 *
 * @param eIntSrc CPM FPU interrupt type. refer CPM FISCR register
 * @param bEnable true: interrupt enable, false:interrupt disable.
 */
void CPM_FpuIntMode(FPU_IntType eIntSrc, bool bEnable);

/**
 * @brief Get CPM Interrupt occurred flag
 *
 *  This function returns the interrupt flag.
 *
 * @param eIntSrc CPM FPU interrupt type. refer CPM FISCR register
 * @return true interrupt occurred
 * @return false No interrupt
 */
bool CPM_GetFpuIntStatus(FPU_IntType eIntSrc);

/**
 * @brief Cpm set interrupt
 *
 * @param pIntStruct interrupt structure pointer
 * @return Cpm return type
 */
CPM_RetType CPM_InitInterrupt(const CPM_InterruptType *pIntStruct);

#if defined(__cplusplus)
}
#endif

/** @}*/ /* fc7xxx_driver_cpm */
#endif
