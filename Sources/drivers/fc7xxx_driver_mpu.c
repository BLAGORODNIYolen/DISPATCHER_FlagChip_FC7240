/**
 * @file fc7xxx_driver_mpu.c
 * @author Flagchip085
 * @brief FC7xxx MPU driver type definition and API
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details The MPU only checks the CPU master access to CTCM and DTCM memory. When access denied, it will cause MemManage Interrupt.
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-12    Flagchip085   N/A          First version for FC7240
   ******************************************************************************** */

#include "fc7xxx_driver_mpu.h"

void MPU_Disable(void)
{
    __DMB(); /* make sure outstanding transfers are done */
    MPU_HWA_Fault_Disable();
    MPU_HWA_Set_CR(0U); /* disable mpu and clear its control register*/
}

void MPU_Enable(MPU_EnableOptionType eOption)
{
    uint32_t u32Option;

    switch (eOption)
    {
        case MPU_EN_HARDFAULT_NMI:
            u32Option = CORTEX_MPU_CTRL_HFNMIENA_MASK;
            break;

        case MPU_EN_PRIVILEGED_DEFAULT:
            u32Option = CORTEX_MPU_CTRL_RPRIVDEFENA_MASK;
            break;

        case MPU_EN_HFNMI_PRIVDEF:
            u32Option = (CORTEX_MPU_CTRL_HFNMIENA_MASK | CORTEX_MPU_CTRL_RPRIVDEFENA_MASK);
            break;

        case MPU_EN_HFNMI_PRIVDEF_NONE:
            u32Option = 0U;
            break;

        default:
            u32Option = 0U;
            break;
    }
    MPU_HWA_Set_CR(CORTEX_MPU_CTRL_ENABLE_MASK | (((uint32_t)u32Option) & MPU_EN_MASK_U32));
    MPU_HWA_Fault_Enable(); /* mpu fault MemManage INT enable */
    __DSB();
    __ISB();
}

MPU_StatusType MPU_RegionDisable(MPU_RegionNumberType eRegion)
{
    MPU_HWA_Set_NR((uint8_t)eRegion);
    MPU_HWA_Set_BAR(0x00U);
    MPU_HWA_Set_ASR(0x00U);

    return MPU_STATUS_SUCCESS;
}

MPU_StatusType MPU_RegionEnable(MPU_RegionNumberType eRegion, const MPU_RegionConfigurationType *pConfig)
{
    MPU_StatusType  eRet   = MPU_STATUS_SUCCESS;
    uint32_t        u32Srd;
    uint32_t        u32Asr;

    if ((NULL == pConfig)              ||
        ((uint32_t)eRegion > (uint32_t)MPU_REGION_NUMBER_15) ||
        (0U != (pConfig->u32BaseAddr & MPU_RBAR_VALID_REGION_MASK_U32)) ||
		((uint32_t)pConfig->eRegionSize < (uint32_t)MPU_REGION_SIZE_32B) ||
		((uint32_t)pConfig->eRegionSize > (uint32_t)MPU_REGION_SIZE_4GB))
    {
        eRet = MPU_STATUS_ERROR;
    }
    else
    {
        /* use bit shift is surely safe */
        u32Srd =    (((((uint32_t)pConfig->eSubRegionDis_0) << 0) |
                      (((uint32_t)pConfig->eSubRegionDis_1) << 1) |
                      (((uint32_t)pConfig->eSubRegionDis_2) << 2) |
                      (((uint32_t)pConfig->eSubRegionDis_3) << 3) |
                      (((uint32_t)pConfig->eSubRegionDis_4) << 4) |
                      (((uint32_t)pConfig->eSubRegionDis_5) << 5) |
                      (((uint32_t)pConfig->eSubRegionDis_6) << 6) |
                      (((uint32_t)pConfig->eSubRegionDis_7) << 7)) & 0xFFU);

        u32Asr =    CORTEX_MPU_RASR_XN(pConfig->eExecuteNever)     |
                    CORTEX_MPU_RASR_AP(pConfig->eAccessPermission) |
                    CORTEX_MPU_RASR_TEX(pConfig->eTypeExtLevel)    |
                    CORTEX_MPU_RASR_S(pConfig->eShareable)         |
                    CORTEX_MPU_RASR_C(pConfig->eCacheable)         |
                    CORTEX_MPU_RASR_B(pConfig->eBufferable)        |
                    CORTEX_MPU_RASR_SRD(u32Srd)                    |
                    CORTEX_MPU_RASR_SIZE(pConfig->eRegionSize)     |
                    CORTEX_MPU_RASR_ENABLE_MASK;

        MPU_HWA_Set_NR((uint8_t)eRegion);
        MPU_HWA_Set_BAR(pConfig->u32BaseAddr & MPU_RBAR_BASEADDR_MASK_U32);   /* ignore VALID and REGION bits */
        MPU_HWA_Set_ASR(u32Asr);
    }

    return eRet;
}




MPU_StatusType MPU_CheckExist(void)
{
    uint32_t       u32RegVal = MPU_HWA_Get_Type();
    MPU_StatusType eRet      = MPU_STATUS_SUCCESS;

    if (0U == u32RegVal)
    {
        eRet = MPU_STATUS_ERROR;
    }

    return eRet;
}
