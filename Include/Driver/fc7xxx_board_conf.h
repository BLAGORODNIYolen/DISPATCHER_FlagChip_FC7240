/**
 * @file fc7xxx_board_conf.h
 * @author Flagchip032
 * @brief FC7xxx board configuration file
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-12    Flagchip032   N/A          First version for FC7240
   ******************************************************************************** */

#ifndef _DRIVER_FC7XXX_BOARD_CONF_H_
#define _DRIVER_FC7XXX_BOARD_CONF_H_
#include "device_header.h"

#if defined(__cplusplus)
extern "C" {
#endif
/**
 * @addtogroup fc7xxx_board_conf
 * @{
 */

/******************* Oscillator Values *******************/
/**
  * @brief Fast OSC frequency
  */
#ifndef FOSC_FREQUENCY
#define FOSC_FREQUENCY   24000000U
#endif

/**
  * @brief Slow OSC frequency
  */
#ifndef SOSC_FREQUENCY
#define SOSC_FREQUENCY   32768U
#endif

/**
  * @brief FTU input TCLK frequency
  */
#ifndef PCC_FTU_TCLK_FREQ
#define PCC_FTU_TCLK_FREQ   0U
#endif


/** @}*/ /* fc7xxx_board_conf */
#if defined(__cplusplus)
}
#endif
#endif
