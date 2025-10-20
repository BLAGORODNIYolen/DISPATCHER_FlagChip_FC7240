/**
 * @file fc7xxx_driver_mam.h
 * @author Flagchip
 * @brief FC7xxx MAM driver type definition and API
 * @version 0.2.0
 * @date 2023-02-08
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2023-02-08    Flagchip095   N/A          First version for FC7240
   ******************************************************************************** */
#ifndef _DRIVER_FC7XXX_DRIVER_MAM_H_
#define _DRIVER_FC7XXX_DRIVER_MAM_H_

#include "device_header.h"
#include "HwA_mam.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief The master index of the mam peripheral
 *
 */
typedef enum {
    MAM_MASTER_CPU0_AXIM = 0,
	MAM_MASTER_CPU0_AHBP,
	MAM_MASTER_DMA0,
	MAM_MASTER_HSM,
	MAM_MASTER_NUM
} MAM_Master_Type;

/**
 * @brief The mam index
 *
 */
typedef enum {
	NVM_MAM0 = 0,
	RAM_MAM1,
	PERIPHERAL_MAM2
} MAM_Index_Type;


/**
 * @brief  the MAM slave information
 *
 */
typedef struct
{
	uint8_t  error;
    uint32_t block_num;
} MAM_Inf_Type;


typedef enum {
	FORBID_READ_ACCESS = 1,
	FORBID_WRITE_ACCESS = 2,
	FORBID_EXECUTE_ACCESS = 4,
	FORBID_USER_ACCESS = 8
} MAM_Forbid_Access_Type;

/**
 * @brief The function of software reset to MAM
 *
 * @param number mam index
 */
void MAM_Reset(MAM_Index_Type idx);

/**
 * @brief The function to enable MAM watch dog
 *
 * @param1 Master The master index
 *
 * @param2 u32Addr The input address
 */
uint8_t MAM_Enable_Wdg(MAM_Master_Type Master,uint32_t u32Addr);

/**
 * @brief The function to disable MAM watch dog
 *
 * @param1 Master The master index
 *
 * @param2 u32Addr The input address
 */
uint8_t MAM_Disable_Wdg(MAM_Master_Type Master,uint32_t u32Addr);

/**
 * @brief The function to config MAM
 *
 * @param1 Master The master index
 *
 * @param2 u32Addr The input address
 *
 * @param3 u32Val The value to set
 */
uint8_t MAM_Config(MAM_Master_Type Master, uint32_t u32Addr, uint32_t u32Val);

#if defined(__cplusplus)
}
#endif

#endif /* end of DRIVER_UART_H_ */
