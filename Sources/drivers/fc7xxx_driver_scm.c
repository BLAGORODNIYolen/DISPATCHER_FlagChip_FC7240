/**
 * @file fc7xxx_driver_scm.h
 * @author Flagchip
 * @brief FC7xxx csc driver type definition and API
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
   *   0.1.0      2024-01-12    Flagchip085     N/A         First version for FC7240
   ******************************************************************************** */

#include "fc7xxx_driver_scm.h"

/**
 * @brief Get unique identification for the chip, loaded from NVR.
 *
 * @param pUid Pointer to UID
 *
 */
void SCM_GetChip_UID(uint32 *pUid)
{
    DEV_ASSERT(NULL_PTR != pUid);

    pUid[0] = SCM_HWA_GetData_UIDL();
    pUid[1] = SCM_HWA_GetData_UIDML();
    pUid[2] = SCM_HWA_GetData_UIDMH();
    pUid[3] = SCM_HWA_GetData_UIDH();
}

/**
 * @brief Get CCMx status.
 *
 * @param eCCMType CCM type
 * @param u32Value selection to get
 *
 */
uint32_t SCM_GetStatus_CCMx(SCM_CCM_Type eCCMType, uint32_t u32Value)
{
    uint32_t u32Temp;

    DEV_ASSERT(eCCMType == SCM_CCM0);
    DEV_ASSERT((u32Value & SCM_CCM0_STATUS_MASK) == 0U);

    if (SCM_CCM0 == eCCMType)
    {
        u32Temp = SCM_HWA_GetStatus_CCM0();
    }

    return (u32Temp & u32Value);
}

/**
 * @brief Get matrix status.
 *
 * @param eMatrixType Matrix type
 * @param u32Value selection to get
 *
 */
uint32_t SCM_GetStatus_Matrix(SCM_MatrixStatusType eMatrixType, uint32_t u32Value)
{
    uint32_t u32Temp;
    DEV_ASSERT((uint32_t)eMatrixType <= (uint32_t)SCM_MatrixStatus_ID);

    if (SCM_MatrixStatus_0 == eMatrixType)
    {
        u32Temp = SCM_HWA_GetStatus_MATRIX_STATUS0();
    }
    else if (SCM_MatrixStatus_1 == eMatrixType)
    {
        u32Temp = SCM_HWA_GetStatus_MATRIX_STATUS1();
    }
    else if (SCM_MatrixStatus_2 == eMatrixType)
    {
        u32Temp = SCM_HWA_GetStatus_MATRIX_STATUS2();
    }
    else if (SCM_MatrixStatus_5 == eMatrixType)
    {
        u32Temp = SCM_HWA_GetStatus_MATRIX_STATUS5();
    }
    else if (SCM_MatrixStatus_6 == eMatrixType)
    {
        u32Temp = SCM_HWA_GetStatus_MATRIX_STATUS6();
    }
    else if (SCM_MatrixStatus_7 == eMatrixType)
    {
        u32Temp = SCM_HWA_GetStatus_MATRIX_STATUS7();
    }
    else
    {
        u32Temp = SCM_HWA_GetStatus_MATRIX_ID_STATUS0();
    }

    return (u32Temp & u32Value);
}

/**
 * @brief Set cpu to control MAM ECC enable register 0.
 *
 * @param eCpuType Cpu to use
 * @param bLockStatus Lock the cpu control settings
 *
 * @return Set operation success/failed
 */
SCM_RetStatusType SCM_SetCpuCtrl_MAMECCR0(const SCM_WPB_CpuType eCpuType, bool bLockStatus)
{
    SCM_RetStatusType eRetVal;
    DEV_ASSERT((uint32_t)eCpuType < (uint32_t)SCM_WP_CPU_NONE);

    if (0U == SCM_HWA_MAMECCEN0_GetWPBLockStatus())
    {
        SCM_HWA_MAMECCEN0_SetCpuWritePermit(eCpuType);

        if (true == bLockStatus)
        {
            /* Lock the cpu to control settings until reset */
            SCM_HWA_MAMECCEN0_LockWritePermit();
        }

        eRetVal = SCM_E_OK;
    }
    else
    {
        eRetVal = SCM_E_LOCK;
    }

    return eRetVal;
}

/**
 * @brief Set cpu to control MAM ECC enable register 1.
 *
 * @param eCpuType Cpu to use
 * @param bLockStatus Lock the cpu control settings
 *
 * @return Set operation success/failed
 */
SCM_RetStatusType SCM_SetCpuCtrl_MAMECCR1(const SCM_WPB_CpuType eCpuType, bool bLockStatus)
{
    SCM_RetStatusType eRetVal;
    DEV_ASSERT((uint32_t)eCpuType < (uint32_t)SCM_WP_CPU_NONE);

    if (0U == SCM_HWA_MAMECCEN1_GetWPBLockStatus())
    {
        SCM_HWA_MAMECCEN1_SetCpuWritePermit(eCpuType);

        if (true == bLockStatus)
        {
            /* Lock the cpu to control settings until reset */
            SCM_HWA_MAMECCEN1_LockWritePermit();
        }

        eRetVal = SCM_E_OK;
    }
    else
    {
        eRetVal = SCM_E_LOCK;
    }

    return eRetVal;
}

/**
 * @brief Set cpu to control CPU0 ECC enable register.
 *
 * @param eCpuType Cpu to use
 * @param bLockStatus Lock the cpu control settings
 *
 * @return Set operation success/failed
 */
SCM_RetStatusType SCM_SetCpuCtrl_CPU0ECCEN(const SCM_WPB_CpuType eCpuType, bool bLockStatus)
{
    SCM_RetStatusType eRetVal;
    DEV_ASSERT((uint32_t)eCpuType < (uint32_t)SCM_WP_CPU_NONE);

    if (0U == SCM_HWA_CPU0ECCEN_GetWPBLockStatus())
    {
        SCM_HWA_CPU0ECCEN_SetCpuWritePermit(eCpuType);

        if (true == bLockStatus)
        {
            /* Lock the cpu to control settings until reset */
            SCM_HWA_CPU0ECCEN_LockWritePermit();
        }

        eRetVal = SCM_E_OK;
    }
    else
    {
        eRetVal = SCM_E_LOCK;
    }

    return eRetVal;
}

/**
 * @brief Set cpu to control SOCMISC register.
 *
 * @param eCpuType Cpu to use
 * @param bLockStatus Lock the cpu control settings
 *
 * @return Set operation success/failed
 */
SCM_RetStatusType SCM_SetCpuCtrl_SOCMISC(const SCM_WPB_CpuType eCpuType, bool bLockStatus)
{
    SCM_RetStatusType eRetVal;

    if (0U == SCM_HWA_SOCMISC_GetWPBLockStatus())
    {
        SCM_HWA_SOCMISC_SetCpuWritePermit(eCpuType);

        if (true == bLockStatus)
        {
            /* Lock the cpu to control settings until reset */
            SCM_HWA_SOCMISC_LockWritePermit();
        }

        eRetVal = SCM_E_OK;
    }
    else
    {
        eRetVal = SCM_E_LOCK;
    }

    return eRetVal;
}

/**
 * @brief Set cpu to control Subsystem pcc register.
 *
 * @param eCpuType Cpu to use
 * @param bLockStatus Lock the cpu control settings
 *
 * @return Set operation success/failed
 */
SCM_RetStatusType SCM_SetCpuCtrl_SUBSYS_PCC(const SCM_WPB_CpuType eCpuType, bool bLockStatus)
{
    SCM_RetStatusType eRetVal;

    if (0U == SCM_HWA_SUBSYS_PCC_GetWPBLockStatus())
    {
        SCM_HWA_SUBSYS_PCC_SetCpuWritePermit(eCpuType);

        if (true == bLockStatus)
        {
            /* Lock the cpu to control settings until reset */
            SCM_HWA_SUBSYS_PCC_LockWritePermit();
        }

        eRetVal = SCM_E_OK;
    }
    else
    {
        eRetVal = SCM_E_LOCK;
    }

    return eRetVal;
}

/**
 * @brief Set cpu to control master halt request register.
 *
 * @param eCpuType Cpu to use
 * @param bLockStatus Lock the cpu control settings
 *
 * @return Set operation success/failed
 */
SCM_RetStatusType SCM_SetCpuCtrl_MASTER_HALT_REQ(const SCM_WPB_CpuType eCpuType, bool bLockStatus)
{
    SCM_RetStatusType eRetVal;

    if (0U == SCM_HWA_MASTER_HALT_REQ_GetWPBLockStatus())
    {
        SCM_HWA_MASTER_HALT_REQ_SetCpuWritePermit(eCpuType);

        if (true == bLockStatus)
        {
            /* Lock the cpu to control settings until reset */
            SCM_HWA_MASTER_HALT_REQ_LockWritePermit();
        }

        eRetVal = SCM_E_OK;
    }
    else
    {
        eRetVal = SCM_E_LOCK;
    }

    return eRetVal;
}

/**
 * @brief Set lock FTU_ROUTING register.
 *
 */
void SCM_SetLock_FTU_ROUTING(void)
{
    if (0U == SCM_HWA_FTU_ROUTING_GetLockStatus())
    {
        SCM_HWA_LockFTU_ROUTING();
    }
}

/**
 * @brief Set lock FTU_GTB register.
 *
 */
void SCM_SetLock_FTU_GTB(void)
{
    if (0U == SCM_HWA_FTU_GTB_GetLockStatus())
    {
        SCM_HWA_LockFTU_GTB();
    }
}

/**
 * @brief Set lock DEBUG_TRACE register.
 *
 */
void SCM_SetLock_DEBUG_TRACE(void)
{
    if (0U == SCM_HWA_DEBUG_TRACE_GetLockStatus())
    {
        SCM_HWA_LockDEBUG_TRACE();
    }
}

/**
 * @brief Set lock FLEXCAN_ROUTING register.
 *
 */
void SCM_SetLock_FLEXCAN_ROUTING(void)
{
    if (0U == SCM_HWA_FLEXCAN_ROUTING_GetLockStatus())
    {
        SCM_HWA_LockFLEXCAN_ROUTING();
    }
}

/**
 * @brief Set lock MSC0_ROUTING register.
 *
 */
void SCM_SetLock_MSC0_ROUTING(void)
{
    if (0U == SCM_HWA_MSC0_ROUTING_GetLockStatus())
    {
        SCM_HWA_LockMSC0_ROUTING();
    }
}

/**
 * @brief Set lock INT_ROUTER_NMI register.
 *
 */
void SCM_SetLock_INT_ROUTER_NMI(void)
{
    if (0U == SCM_HWA_INT_ROUTER_NMI_GetLockStatus())
    {
        SCM_HWA_LockINT_ROUTER_NMI();
    }
}

/**
 * @brief Set NMI interrupt router .
 *
 * @param eCpuType Cpu to use
 * @param bEnable Enable/Disable
 * @return Set operation success/failed
 */
SCM_RetStatusType SCM_SetEnable_NMIIntRouter(const SCM_WPB_CpuType eCpuType, bool bEnable)
{
    SCM_RetStatusType eRetVal;

    if (SCM_WP_CPU_0 == eCpuType)
    {
        SCM_HWA_SetEnable_Cpu0NMIIrqRouter(bEnable);
        eRetVal = SCM_E_OK;
    }
    else
    {
        eRetVal = SCM_E_PARAM;
    }

    return eRetVal;
}

/**
 * @brief Generate the origion SCM register CRC result, and configure the SCM register CRC option.
 *
 * @param eMode The SCM register CRC trigger mode
 * @return CRC configure status
 *      SCM_E_OK : CRC configure successfully
 *      SCM_E_TIMEOUT : CRC configure time out
 */
SCM_RetStatusType SCM_RegCrcConfig(SCM_CrcModeType eMode)
{
    SCM_RetStatusType eStatusVal = SCM_E_OK;
    uint32_t u32Timeout = 0xFFFFU;

    DEV_ASSERT((eMode == SCM_CRC_SW_MODE) || (eMode == SCM_CRC_TRIGGER_MODE));

    /* Deinit CRC register */
    SCM_HWA_SetEnable_CrcCheck(false);
    SCM_HWA_SetEnable_CrcTrigger(false);
    SCM_HWA_SetEnable_CrcErrOut(false);
    SCM_HWA_ClearCrcErrorFlag();

    /* Generate original CRC result */
    SCM_HWA_SetEnable_CrcSwGen(true);
    while (SCM_HWA_GetStatus_CrcBusyFlag() != 0U)
    {
        u32Timeout--;
        if (u32Timeout == 0U)
        {
            eStatusVal = SCM_E_TIMEOUT;
            break;
        }
    }

    if (eStatusVal == SCM_E_OK)
    {
        if (eMode == SCM_CRC_TRIGGER_MODE)
        {
            SCM_HWA_SetEnable_CrcTrigger(true);
        }

        /* Enable SCM CRC error to FCSMU in CSC0_SMU_CTRL4[SCM_CRC] */
        CSC0_HWA_CTRL4_EnableReqToSMU(CSC_SMU_SCM_CRC);
        /* Generate CRC error output */
        SCM_HWA_SetEnable_CrcErrOut(true);
        /* Generate CRC check */
        SCM_HWA_SetEnable_CrcCheck(true);
    }
    return eStatusVal;
}

/**
 * @brief Trigger the SCM register CRC generation by software
 *
 */
void SCM_RegCrcGenerate(void)
{
    SCM_HWA_SetEnable_CrcSwGen(true);
}

/**
 * @brief Trigger the SCM register CRC generation by software,and wait the CRC check result
 *
 * @return CRC check result
 */
SCM_RetStatusType SCM_RegCrcGenerateWaitResult(void)
{
    SCM_RetStatusType eStatusVal = SCM_E_OK;
    uint32_t u32Timeout = 0xFFFFU;

    SCM_HWA_SetEnable_CrcSwGen(true);
    while (SCM_HWA_GetStatus_CrcBusyFlag() != 0U)
    {
        u32Timeout--;
        if (u32Timeout == 0U)
        {
            eStatusVal = SCM_E_TIMEOUT;
            break;
        }
    }

    /* Check CRC is success or not */
    if (0U != SCM_HWA_GetStatus_CrcErrFlag())
    {
        eStatusVal = SCM_E_CRC;
    }

    return eStatusVal;
}
