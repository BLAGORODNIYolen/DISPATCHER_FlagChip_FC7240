/**
 * @file fc7xxx_driver_scm.h
 * @author Flagchip085
 * @brief FC7xxx SCM driver type definition and API
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-12    Flagchip085   N/A          First version for FC7240
   ******************************************************************************** */

#ifndef _DRIVER_SCM_H_
#define _DRIVER_SCM_H_

#include "HwA_scm.h"
#include "HWA_csc.h"
#include "interrupt_manager.h"

/********* Local typedef ************/
/** 
 * @brief SCM return status
 * 
 */
typedef enum
{
    SCM_E_OK     = 0U,  /*!< Return ok */
    SCM_E_NOT_OK,       /*!< Return not ok */
    SCM_E_PARAM,        /*!< Return invalid parameters */
    SCM_E_LOCK,         /*!< Return register has been locked */
    SCM_E_TIMEOUT,       /*!< Return operation timeout */
    SCM_E_CRC           /*!< Return CRC check failed */
} SCM_RetStatusType;

/**
 * @brief CCMx type
 *
 */
typedef enum
{
    SCM_CCM0 = 0U  /*!< CCM0 */
} SCM_CCM_Type;

/**
 * @brief Matrixx type
 *
 */
typedef enum
{
    SCM_MatrixStatus_0 = 0U,  /*!< Matrix status 0 */
    SCM_MatrixStatus_1,       /*!< Matrix status 1 */
    SCM_MatrixStatus_2,       /*!< Matrix status 2 */
    SCM_MatrixStatus_5,       /*!< Matrix status 5 */
    SCM_MatrixStatus_6,       /*!< Matrix status 6 */
    SCM_MatrixStatus_7,       /*!< Matrix status 7 */
    SCM_MatrixStatus_ID       /*!< Matrix ID status */
} SCM_MatrixStatusType;

/**
 * @brief SCM registers CRC trigger mode
 */
typedef enum
{
    SCM_CRC_SW_MODE       = 0U,   /*!< SCM registers CRC software mode. */
    SCM_CRC_TRIGGER_MODE  = 1U    /*!< SCM registers CRC trigger mode. */
} SCM_CrcModeType;

/********* Local function ************/
/**
 * @brief Get unique identification for the chip, loaded from NVR.
 *
 * @param pUid Pointer to UID
 *
 */
void SCM_GetChip_UID(uint32 *pUid);

/**
 * @brief Get CCMx status.
 *
 * @param eCCMType CCM type
 * @param u32Value The or value of SCM_CCMxStatusType to select the status to get
 *
 */
uint32_t SCM_GetStatus_CCMx(SCM_CCM_Type eCCMType, uint32_t u32Value);

/**
 * @brief Get matrix status.
 *
 * @param eMatrixType Matrix type
 * @param u32Value selection to get
 *
 */
uint32_t SCM_GetStatus_Matrix(SCM_MatrixStatusType eMatrixType, uint32_t u32Value);

/**
 * @brief Set cpu to control MAM ECC enable register 0.
 *
 * @param eCpuType Cpu to use
 * @param bLockStatus Lock the cpu control settings
 *
 * @return Set operation success/failed
 */
SCM_RetStatusType SCM_SetCpuCtrl_MAMECCR0(const SCM_WPB_CpuType eCpuType, bool bLockStatus);

/**
 * @brief Set cpu to control MAM ECC enable register 1.
 *
 * @param eCpuType Cpu to use
 * @param bLockStatus Lock the cpu control settings
 *
 * @return Set operation success/failed
 */
SCM_RetStatusType SCM_SetCpuCtrl_MAMECCR1(const SCM_WPB_CpuType eCpuType, bool bLockStatus);

/**
 * @brief Set cpu to control CPU0 ECC enable register.
 *
 * @param eCpuType Cpu to use
 * @param bLockStatus Lock the cpu control settings
 *
 * @return Set operation success/failed
 */
SCM_RetStatusType SCM_SetCpuCtrl_CPU0ECCEN(const SCM_WPB_CpuType eCpuType, bool bLockStatus);

/**
 * @brief Set cpu to control SOCMISC register.
 *
 * @param eCpuType Cpu to use
 * @param bLockStatus Lock the cpu control settings
 *
 * @return Set operation success/failed
 */
SCM_RetStatusType SCM_SetCpuCtrl_SOCMISC(const SCM_WPB_CpuType eCpuType, bool bLockStatus);

/**
 * @brief Set cpu to control Subsystem pcc register.
 *
 * @param eCpuType Cpu to use
 * @param bLockStatus Lock the cpu control settings
 *
 * @return Set operation success/failed
 */
SCM_RetStatusType SCM_SetCpuCtrl_SUBSYS_PCC(const SCM_WPB_CpuType eCpuType, bool bLockStatus);

/**
 * @brief Set cpu to control master halt request register.
 *
 * @param eCpuType Cpu to use
 * @param bLockStatus Lock the cpu control settings
 *
 * @return Set operation success/failed
 */
SCM_RetStatusType SCM_SetCpuCtrl_MASTER_HALT_REQ(const SCM_WPB_CpuType eCpuType, bool bLockStatus);

/**
 * @brief Set lock FTU_ROUTING register.
 *
 */
void SCM_SetLock_FTU_ROUTING(void);

/**
 * @brief Set lock FTU_GTB register.
 *
 */
void SCM_SetLock_FTU_GTB(void);

/**
 * @brief Set lock DEBUG_TRACE register.
 *
 */
void SCM_SetLock_DEBUG_TRACE(void);

/**
 * @brief Set lock FLEXCAN_ROUTING register.
 *
 */
void SCM_SetLock_FLEXCAN_ROUTING(void);

/**
 * @brief Set lock MSC0_ROUTING register.
 *
 */
void SCM_SetLock_MSC0_ROUTING(void);

/**
 * @brief Set lock INT_ROUTER_NMI register.
 *
 */
void SCM_SetLock_INT_ROUTER_NMI(void);

/**
 * @brief Set NMI interrupt router .
 *
 * @param eCpuType Cpu to use
 * @param bEnable Enable/Disable
 * @return Set operation success/failed
 *      SCM_E_OK: Set NMI interrupt router successfully
 *      SCM_E_PARAM: eCpuType invalid
 */
SCM_RetStatusType SCM_SetEnable_NMIIntRouter(const SCM_WPB_CpuType eCpuType, bool bEnable);

/**
 * @brief Generate the origion SCM register CRC result, and configure the SCM register CRC option.
 *
 * @param eMode The SCM register CRC trigger mode
 * @return CRC configure status
 *      SCM_E_OK : CRC configure successfully
 *      SCM_E_TIMEOUT : CRC configure time out
 */
SCM_RetStatusType SCM_RegCrcConfig(SCM_CrcModeType eMode);

/**
 * @brief Trigger the SCM register CRC generation by software
 *
 */
void SCM_RegCrcGenerate(void);

/**
 * @brief Trigger the SCM register CRC generation by software,and wait the CRC check result
 *
 * @return CRC check result
 */
SCM_RetStatusType SCM_RegCrcGenerateWaitResult(void);


#endif /* end of _DRIVER_SCM_H_ */
