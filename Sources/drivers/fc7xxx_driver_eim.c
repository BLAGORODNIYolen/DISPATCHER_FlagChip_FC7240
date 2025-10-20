/**
 * @file fc7xxx_driver_eim.c
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
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2024-01-14    qxw0100        N/A          First version for FC7240
********************************************************************************/

#include "fc7xxx_driver_eim.h"
#include "fc7xxx_driver_pcc.h"

/******************* Local Variables ***********************/

/******************* Local Function Prototype **************/


/****************** Global Functions ***********************/
/**
 * @brief Initialize EIM function
 *
 * @param pEimInitCfg Initialization structure of EIM
 * @return return 0: initialize successful. 1: invalid parameter
 */
EIM_RetType EIM_Init(const EIM_InitType *pEimInitCfg)
{
    EIM_RetType eRet = EIM_STATUS_SUCCESS;
    uint32_t u32CtrlVal = 0U;
    uint32_t u32BusVal = 0U;
    uint8_t u8BusChn;
    if (NULL == pEimInitCfg)
    {
        eRet = EIM_STATUS_PARAM_INVALID;
    }
    else
    {
       	u32CtrlVal |= EIM_CTRL_REG_BUS_SEL(pEimInitCfg->u8BusSelIdx);
       	u8BusChn = (uint8_t)pEimInitCfg->u8BusSelIdx;
        if(pEimInitCfg->u8Attreenable != 0U)
        {
            if((pEimInitCfg->u8EimChn>=1U) && (pEimInitCfg->u8EimChn<=23U))
            {
                u32CtrlVal |= EIM_CTRL_REG_ATTREIE(1U);
                u32BusVal |= EIM_BUS_REG_ATTR(pEimInitCfg->u8AttrPosition);
            }
            else
            {
            	eRet = EIM_STATUS_PARAM_INVALID;
            }

        }
        if(pEimInitCfg->u8Addreenable != 0U)
        {
            if((pEimInitCfg->u8EimChn>=1U) && (pEimInitCfg->u8EimChn<=23U))
            {
                u32CtrlVal |= EIM_CTRL_REG_ADDREIE(1U);
                u32BusVal |= EIM_BUS_REG_ADDR(pEimInitCfg->u8AddrePosition);
            }
            else
            {
            	eRet = EIM_STATUS_PARAM_INVALID;
            }
        }
        if(pEimInitCfg->u8Data0enable != 0U)
        {
            u32CtrlVal |= EIM_CTRL_REG_DATA0EIE(1U);
            u32BusVal |= EIM_BUS_REG_DATA0(pEimInitCfg->u8Data0Val);
        }
        if(pEimInitCfg->u8Data1enable != 0U)
        {
            u32CtrlVal |= EIM_CTRL_REG_DATA1EIE(1U);
            u32BusVal |= EIM_BUS_REG_DATA1(pEimInitCfg->u8Data1Val);
        }
        EIM_HWA_Set_BUSRegn(u8BusChn,u32BusVal);
        EIM_HWA_Set_CtrlRegn((uint8_t)pEimInitCfg->u8EimChn,u32CtrlVal);
        EIM_HWA_EnableGlobalErrorInjection();
    }

    return eRet;
}

/**
 * @brief Initialize EIM function
 *
 * @param eEimChannel channel want to set
 * @param eDwpType Cpu to use
 * @param bLockStatus Lock the cpu control settings
 * @return Set operation success/failed
 */
EIM_RetType EIM_SetDwpMode(const EIM_ChannelType eEimChannel, const EIM_DWPType eDwpType, bool bLockStatus)
{
    uint8_t u8ChnIdx = (uint8_t)eEimChannel;
    EIM_RetType eRet = EIM_STATUS_SUCCESS;
    if (0U == EIM_HWA_GetCtrlDWPLockStatus(u8ChnIdx))
    {
    	EIM_HWA_Set_CtrlLockMode((uint8_t)eEimChannel,(uint8_t)eDwpType);
        if(true == bLockStatus)
        {
        	/* Lock the dwp mode until reset */
        	EIM_HWA_CtrlRegnWritePermit(u8ChnIdx);
        }
    }
    else
    {
    	eRet = EIM_STATUS_PARAM_INVALID;
    }

    return eRet;
}

/**
 * @brief Enable CPU lockstep monitor
 *
 * @param eEimCpuType EIM_CPU0_LOCKSTEP or EIM_CPU1_LOCKSTEP
 * @param eMonitorType EIM_MONITOR0 or EIM_MONITOR1
 */
void EIM_CpuLockStepMonitorSet_MonSet(const EIM_CPU_ChnType eEimCpuType,const EIM_MONType eMonitorType)
{
    uint32_t u32val = 0U;

    u32val = EIM_HWA_Get_CPULockstep((uint8_t)eEimCpuType);

    if(eMonitorType == EIM_MONITOR0)
    {
    	u32val &= 0xFFFFFFFD;//clear mon0 clr
      	u32val |= EIM_CPU0_LOCKSTEP_LOCKSTEP_MON0_SET(1U);
    }

    if(eMonitorType == EIM_MONITOR1)
    {
    	u32val &= 0xFFFFFFFE;//clear mon1 clr
        u32val |= EIM_CPU0_LOCKSTEP_LOCKSTEP_MON1_SET(1U);
    }

    EIM_HWA_Set_CPULockstep((uint8_t)eEimCpuType, u32val);
}

/**
 * @brief Clear CPU lockstep monitor
 *
 * @param eEimCpuType EIM_CPU0_LOCKSTEP or EIM_CPU1_LOCKSTEP
 * @param eMonitorType EIM_MONITOR0 or EIM_MONITOR1
 */
void EIM_CpuLockStepMonitorSet_MonClr(const EIM_CPU_ChnType eEimCpuType,const EIM_MONType eMonitorType)
{
	uint32_t u32val = 0U;

	u32val = EIM_HWA_Get_CPULockstep((uint8_t)eEimCpuType);

    if(eMonitorType == EIM_MONITOR0)
    {
        u32val |= EIM_CPU0_LOCKSTEP_LOCKSTEP_MON0_CLR(1U);
    }
    if(eMonitorType == EIM_MONITOR1)
    {
        u32val |= EIM_CPU0_LOCKSTEP_LOCKSTEP_MON1_CLR(1U);
    }

    EIM_HWA_Set_CPULockstep((uint8_t)eEimCpuType, u32val);
}

/**
 * @brief Clean CPU lockstep monitor bit
 *
 * @param eEimCpuType EIM_CPU0_LOCKSTEP or EIM_CPU1_LOCKSTEP
 * @param eMonitorType EIM_MONITOR0 or EIM_MONITOR1
 */
void EIM_CpuLockStepMonitorClr(const EIM_CPU_ChnType eEimCpuType, const EIM_MONType eMonitorType)
{
	uint32_t u32val = 0U;

	u32val = EIM_HWA_Get_CPULockstep((uint8_t)eEimCpuType);

	if(eMonitorType == EIM_MONITOR0)
	{
		u32val &= 0xFFFFFFF5;//clear mon0 clr
	}

	if(eMonitorType == EIM_MONITOR1)
	{
		u32val &= 0xFFFFFFFA;//clear mon1 clr
	}

	EIM_HWA_Set_CPULockstep((uint8_t)eEimCpuType, u32val);
}

/**
 * @brief Deinin EIM function
 *
 */
void Eim_Deinit(void)
{
    uint8_t u8loop;
    EIM_HWA_DisableGlobalErrorInjection();
    for (u8loop = 0U; u8loop < EIM_CTRL_REG_COUNT; u8loop++)
    {
        EIM_HWA_Set_CtrlRegn(u8loop, 0U);
    }

    EIM_HWA_Set_CPULockstep(EIM_CPU0_LOCKSTEP, 0U);
    EIM_HWA_Set_CPULockstep(EIM_DMA0_LOCKSTEP, 0U);

    for (u8loop = 0U; u8loop < EIM_BUS_REG_COUNT; u8loop++)
    {
        EIM_HWA_Set_BUSRegn(u8loop, 0U);
    }
}

