/**
 * @file HwA_erm.h
 * @author Flagchip
 * @brief FC7xxx erm driver type definition and API
 * @version 0.1.0
 * @date 2024-01-14
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
  *   Revision History:
  *
  *   Version     Date          Initials      CR#          Descriptions
  *   ---------   ----------    ------------  ----------   ---------------
  *   0.1.0       2024-01-14    qxw0100       N/A          FC7240 Erm first version
  ******************************************************************************** */

#ifndef HWA_INCLUDE_HWA_ERM_H_
#define HWA_INCLUDE_HWA_ERM_H_
#include "device_header.h"

#define ERM_SR_MASK 0xCCCCCCCCu


/**
 * @defgroup HwA_erm
 * @ingroup HwA_erm
 * @{
 */

/** @brief ERM configuration type */
typedef enum
{
    ERM_NONE_CORRECTABLE       = 1U,          /*!< select Non-correctable interrupt report    */
    ERM_SINGLE_BIT             = 2U           /*!< select single correction interrupt report  */
} ERM_InterruptType;


/** @brief ERM configuration type */
typedef enum
{
    ERM_PFLASH0_ECC       = 1U,           /*!<  PFlash0 ECC Error     */
    ERM_PFLASH1_ECC       = 2U,           /*!<  PFlash1 ECC Error     */
    ERM_DFLASH_ECC        = 3U,           /*!<  DFlash ECC error      */
    ERM_DMACFG0_ECC       = 4U,           /*!<  DMACFG0 ECC Error     */
    ERM_ROM_ECC           = 6U,           /*!<  ROM ECC Error         */
    ERM_SYSRAM0_ECC       = 8U,           /*!<  SysRAM0 ECC ERROR     */
    ERM_SYSRAM1_ECC       = 9U,           /*!<  SysRAM1 ECC ERROR     */
    ERM_CPU0ITCM_ECC      = 11U,          /*!<  CPU0 ITCM ECC Error   */
    ERM_CPU0DTCM0_ECC     = 12U,          /*!<  CPU0 DTCM0 ECC Error  */
    ERM_CPU0DTCM1_ECC     = 13U,          /*!<  CPU0 DTCM1 ECC Error  */
    ERM_CPU0ICACHE_ECC    = 14U,          /*!<  CPU0 ICACHE ECC Error */
    ERM_CPU0DCACHE_ECC    = 15U,          /*!<  CPU0 DCACHE ECC Error */
    ERM_HSMDRAM_ECC       = 26U,          /*!<  HSM DRAM ECC Error    */
    ERM_HSMIRAM_ECC       = 27U,          /*!<  HSM IRAM ECC Error    */
} ERM_ChannelType;


/**
 * @brief  get ERM configuration register 0~3
 *
 * @return  ERM CRn value
 */
LOCAL_INLINE uint32_t ERM_HWA_Get_CRn(uint8_t idx)
{
    uint32_t u32RegValue;
    u32RegValue = *((volatile uint32_t *)(&(ERM->CR0) + (uint32_t)idx));
    return u32RegValue;
}

/**
 * @brief  get ERM status register 0~3
 *
 * @return  ERM SRn value
 */
LOCAL_INLINE uint32_t ERM_HWA_Get_SRn(uint8_t idx)
{
    uint32_t u32RegValue;
    u32RegValue = *((volatile uint32_t *)(&(ERM->SR0) + (uint32_t)idx));
    return u32RegValue;
}

/**
 * @brief  get ERM error address register 0~25
 *
 * @return  ERM error address register value
 */
LOCAL_INLINE uint32_t ERM_HWA_Get_EARn(uint8_t idx)
{
    uint32_t u32RegValue;
    u32RegValue = *((const volatile uint32_t *)(&(ERM->EAR0) + (uint32_t)idx * 0x10UL/4UL));

    return u32RegValue;
}

/**
 * @brief  set erm configuration register
 *
 * @param idx  index (0~3)
 * @param u32RegValue  access control value
 */
LOCAL_INLINE void ERM_HWA_Set_CRn(uint8_t idx, uint32_t u32RegValue)
{
    *((volatile uint32_t *)(&(ERM->CR0) + (int32_t)idx)) = u32RegValue;
}
/**
 * @brief  set erm error address register
 *
 * @param idx  index (0~3)
 * @param u32RegValue  access control value
 */
LOCAL_INLINE void ERM_HWA_Set_SRn(uint8_t idx, uint32_t u32RegValue)
{
    *((volatile uint32_t *)(&(ERM->SR0) + (int32_t)idx)) = u32RegValue;
}

/** @}*/
#endif /* HWA_INCLUDE_HWA_ERM_H_ */
