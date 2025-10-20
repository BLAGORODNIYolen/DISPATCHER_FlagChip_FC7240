/**
 * @file fc7xxx_driver_fcsmu.c
 * @author Flagchip
 * @brief FC7xxx FCSMU driver type definition and API
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
   *   0.1.0       2024-01-14    qxw0100       N/A          First version for FC7240
   ******************************************************************************** */
#include "fc7xxx_driver_fcsmu.h"
#include "Hwa_csc.h"

/* ################################################################################## */
/* ####################################### Macro #################################### */

#define FCSMU_FST_UNLOCK_KEY 0x951413CFU
#define FCSMU_OPC1_UNLOCK_KEY 0xFC2020CFU
#define FCSMU_OPC2_UNLOCK_KEY 0x20FCCF20U
#define FCSMU_CONFIG_TMEP_UNLOCK_KEY 0xFCU

/* ################################################################################## */
/* ################################### Type define ################################## */

/* ################################################################################## */
/* ################################ Local Variables ################################# */
static FCSMU_Type *const s_apFcsmuBase[FCSMU_INSTANCE_COUNT] = FCSMU_BASE_PTRS;
static FCSMU_ISRCallbackType s_apFcsmuISRCallback = NULL;

/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */

/* ################################################################################## */
/* ######################### Global prototype Functions  ############################ */
void FCSMU0_IRQHandler(void);
/* ################################################################################## */
/* ################################ Local Functions  ################################ */

/* ################################################################################## */
/* ################################ Global Functions ################################ */

FCSMU_StatusType FCSMU_init(const FCSMU_InitCfgType *pInitConfig)
{
    DEV_ASSERT(pInitConfig != NULL);
    FCSMU_StatusType eRet;

    FCSMU_Type *const pFcsmu = s_apFcsmuBase[FCSMU_INSTANCE_0];

    eRet = FCSMU_TransStateNTC();

    if (eRet != FCSMU_STATUS_SUCCESS)
    {
        return eRet;
    }

    if (pInitConfig->u32WarnTo > 432000U)
    {
        FCSMU_HWA_SetWaringTo(pFcsmu, 432000U);
    }
    else
    {
        FCSMU_HWA_SetWaringTo(pFcsmu, pInitConfig->u32WarnTo);
    }
    FCSMU_HWA_ClearCfgToIrq(pFcsmu);
    FCSMU_HWA_SetWarningEn0(pFcsmu, pInitConfig->u32WarnChannel);
    FCSMU_HWA_SetWarningIen(pFcsmu, pInitConfig->u32WarnInterruptChannel);
    FCSMU_HWA_SetFaultIen(pFcsmu, pInitConfig->u32FaultInterruptChannel);
    FCSMU_HWA_SetFRST0(pFcsmu, pInitConfig->u32FaultResetChannel);
    FCSMU_HWA_SetFe0(pFcsmu, pInitConfig->u32FaultChannel);
    FCSMU_HWA_SetFccr0(pFcsmu, pInitConfig->u32SoftwareClearedChannel);

    eRet = FCSMU_TransStateCTN();
    FCSMU_HWA_SetTempUnlk(pFcsmu, 0xFFU);

    s_apFcsmuISRCallback = pInitConfig->pISRCallback;

    return eRet;
}

FCSMU_StatusType FCSMU_ConfigStatusOutput(FCSMU_StatusOutputConfigType *pInitConfig)
{

    DEV_ASSERT(pInitConfig != NULL);

    FCSMU_Type *const pFcsmu = s_apFcsmuBase[FCSMU_INSTANCE_0];
    uint32_t u32TempValue;
    FCSMU_StatusType eRet;

    if (pInitConfig->eFastMode == true)
    {
        if (pInitConfig->eProtocal != FCSMU_SOUT_PROTOCOL_DUAL_RAIL && pInitConfig->eProtocal != FCSMU_SOUT_PROTOCOL_TIME_SWITCH)
        {
            return FCSMU_STATUS_ERROR;
        }
    }

    u32TempValue = FCSMU_SOCTRL_SOUT_PEN(pInitConfig->bEnable) |
                   FCSMU_SOCTRL_FASTEN(pInitConfig->eFastMode) |
                   FCSMU_SOCTRL_POLSW(pInitConfig->ePolarity) |
                   FCSMU_SOCTRL_SOUT_PTC(pInitConfig->eProtocal) |
				   FCSMU_SOCTRL_DIVEX(pInitConfig->bDivex) |
                   FCSMU_SOCTRL_SOUT_CTRL(pInitConfig->eSoutCtrl) |
                   FCSMU_SOCTRL_SOUT_DIV(pInitConfig->u32Divder) |
                   FCSMU_SOCTRL_SMRDT(pInitConfig->u32Delaytimer);

    eRet = FCSMU_TransStateNTC();

    if (eRet != FCSMU_STATUS_SUCCESS)
    {
        return eRet;
    }

    FCSMU_HWA_SetSoctrl(pFcsmu, u32TempValue);
    FCSMU_HWA_SetSoutEn(pFcsmu, pInitConfig->u32SoutChannel);

    eRet = FCSMU_TransStateCTN();

    return eRet;
}

void FCSMU_CrcGen(void)
{
    FCSMU_Type *const pFcsmu = s_apFcsmuBase[FCSMU_INSTANCE_0];
    FCSMU_HWA_GenerateCrc(pFcsmu);
}

bool FCSMU_IsCrcBusy(void)
{
    FCSMU_Type *const pFcsmu = s_apFcsmuBase[FCSMU_INSTANCE_0];
    return FCSMU_HWA_GetCrcBusy(pFcsmu);
}

FCSMU_StatusType FCSMU_CrcConfig(FCSMU_CrcModeType eMode)
{
    FCSMU_Type *const pFcsmu = s_apFcsmuBase[FCSMU_INSTANCE_0];
    uint32_t u32TimeoutTimes = 65535U;
    FCSMU_StatusType eRet = FCSMU_STATUS_SUCCESS;

    FCSMU_HWA_GenerateCrc(pFcsmu);
    while (FCSMU_HWA_GetCrcBusy(pFcsmu) == FCSMU_Crc_STATE_BUSY)
    {
        u32TimeoutTimes--;
        if (u32TimeoutTimes == 0U)
        {
            eRet = FCSMU_STATUS_ERROR;
            break;
        }
    }

    if (eRet == FCSMU_STATUS_SUCCESS)
    {
        if (eMode == FCSMU_CRC_TRIGGER_MODE)
        {
            FCSMU_HWA_EnableTrigger(pFcsmu, true);
        }
        else
        {

        }

        CSC0_HWA_CTRL4_EnableReqToSMU(CSC_SMU_SCF_IRQ);
        FCSMU_HWA_EnableErrorOutput(pFcsmu, true);
        FCSMU_HWA_EnableCrcChecker(pFcsmu, true);
    }

    return eRet;

}

FCSMU_StatusType FCSMU_ClearFaultFlag(uint32_t u32FaultChannel)
{
    FCSMU_Type *const pFcsmu = s_apFcsmuBase[FCSMU_INSTANCE_0];
    uint32_t u32TimeoutTimes = 65535U;
    FCSMU_StatusType eRet = FCSMU_STATUS_SUCCESS;

    FCSMU_HWA_SetFunlk(pFcsmu, FCSMU_FST_UNLOCK_KEY);
    FCSMU_HWA_SetFst0(pFcsmu, u32FaultChannel);

    while (FCSMU_HWA_GetCtrlOps(pFcsmu) != (uint32_t)FCSMU_OP_STATE_SUCCESSFUL)
    {
        u32TimeoutTimes--;
        if (u32TimeoutTimes == 0U)
        {
            eRet = FCSMU_STATUS_ERROR;
            break;
        }
    }

    return eRet;
}

FCSMU_StatusType FCSMU_TransStateCTN(void)
{
    FCSMU_Type *const pFcsmu = s_apFcsmuBase[FCSMU_INSTANCE_0];
    uint32_t u32TimeoutTimes;
    uint32_t u32RetryTimes = 65535U;
    uint32_t u32Temp;
    FCSMU_StatusType eRet = FCSMU_STATUS_ERROR;

    while (u32RetryTimes != 0U)
    {
        u32TimeoutTimes = 65535U;
        u32Temp = (uint32_t)FCSMU_HWA_GetCtrl(pFcsmu);
        u32Temp |= (uint32_t)FCSMU_OPC_MOVE_TO_NORMAL;

        FCSMU_HWA_SetOprk(pFcsmu, FCSMU_OPC2_UNLOCK_KEY);
        FCSMU_HWA_SetCrtl(pFcsmu, u32Temp);

        while (FCSMU_HWA_GetCtrlOps(pFcsmu) != (uint32_t)FCSMU_OP_STATE_SUCCESSFUL)
        {
            u32TimeoutTimes--;
            if (u32TimeoutTimes == 0U)
            {
                break;
            }
        }

        if (u32TimeoutTimes != 0U)
        {
            if (FCSMU_HWA_GetState(pFcsmu) == (uint32_t)FCSMU_STATE_NORMAL)
            {
                break;
            }
        }

        u32RetryTimes--;
    }

    if (u32RetryTimes != 0U)
    {
        eRet = FCSMU_STATUS_SUCCESS;
    }

    return eRet;
}

FCSMU_StatusType FCSMU_TransStateNTC(void)
{
    FCSMU_Type *const pFcsmu = s_apFcsmuBase[FCSMU_INSTANCE_0];
    uint32_t u32TimeoutTimes;
    uint32_t u32RetryTimes = 65535U;
    FCSMU_StatusType eRet = FCSMU_STATUS_ERROR;
    uint32_t u32Temp;

    while (u32RetryTimes != 0U)
    {
        u32TimeoutTimes = 65535U;
        u32Temp = FCSMU_HWA_GetCtrl(pFcsmu);
        u32Temp |= (uint32_t)FCSMU_OPC_MOVE_TO_CONFIG;
        FCSMU_HWA_SetTempUnlk(pFcsmu, FCSMU_CONFIG_TMEP_UNLOCK_KEY);
        FCSMU_HWA_SetOprk(pFcsmu, FCSMU_OPC1_UNLOCK_KEY);
        FCSMU_HWA_SetCrtl(pFcsmu, u32Temp);

        while (FCSMU_HWA_GetCtrlOps(pFcsmu) != (uint32_t)FCSMU_OP_STATE_SUCCESSFUL)
        {
            if (FCSMU_HWA_GetCtrlOps(pFcsmu) == (uint32_t)FCSMU_OP_STATE_BUSY)
            {
                u32TimeoutTimes--;
                if (u32TimeoutTimes == 0U)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }

        if (u32TimeoutTimes != 0U)
        {
            if (FCSMU_HWA_GetState(pFcsmu) == (uint32_t)FCSMU_STATE_CONGIG)
            {
                break;
            }
        }

        u32RetryTimes--;
    }

    if (u32RetryTimes != 0U)
    {
        eRet = FCSMU_STATUS_SUCCESS;
    }

    return eRet;
}

void FCSMU_InjectionFault(uint32_t u32ChannelIndex)
{
    FCSMU_Type *const pFcsmu = s_apFcsmuBase[FCSMU_INSTANCE_0];

    FCSMU_HWA_SetInject(pFcsmu, u32ChannelIndex);
}

uint32_t FCSMU_GetFaultChannel(void)
{
    FCSMU_Type *const pFcsmu = s_apFcsmuBase[FCSMU_INSTANCE_0];

    return FCSMU_HWA_GetFst0(pFcsmu);
}

uint32_t FCSMU_GetIrqState(void)
{
    FCSMU_Type *const pFcsmu = s_apFcsmuBase[FCSMU_INSTANCE_0];

    return FCSMU_HWA_GetIrqStat(pFcsmu);
}

uint32_t FCSMU_GetNtfFlag(void)
{
    FCSMU_Type *const pFcsmu = s_apFcsmuBase[FCSMU_INSTANCE_0];

    return FCSMU_HWA_GetNtf(pFcsmu);
}

uint32_t FCSMU_GetWtfFlag(void)
{
    FCSMU_Type *const pFcsmu = s_apFcsmuBase[FCSMU_INSTANCE_0];

    return FCSMU_HWA_GetWtf(pFcsmu);
}

uint32_t FCSMU_GetNtwFlag(void)
{
    FCSMU_Type *const pFcsmu = s_apFcsmuBase[FCSMU_INSTANCE_0];

    return FCSMU_HWA_GetNtw(pFcsmu);
}

static void FCSMUn_IRQHandler(void)
{
    uint32_t u32TempValue = FCSMU_GetIrqState();
    uint32_t u32IrqChannel;

    if ((FCSMU_IRQ_STAT_FAULT_IRQ_MASK & u32TempValue) == FCSMU_IRQ_STAT_FAULT_IRQ_MASK)
    {
        if ((FCSMU_GetNtfFlag() & FCSMU_NTF_FLAG_MASK) == FCSMU_NTF_FLAG_MASK)
        {
            u32IrqChannel = FCSMU_GetNtfFlag() & 0xFFU;
        }
        else
        {
            u32IrqChannel = FCSMU_GetWtfFlag() & 0xFFU;
        }

        if (u32IrqChannel == 0xFFU)
        {
            u32IrqChannel = FCSMU_GetFaultChannel();
        }
        else
        {
            if (u32IrqChannel > 0U && u32IrqChannel <= 32U)
            {
                u32IrqChannel = (uint32_t)1U << (u32IrqChannel - (uint32_t)1U);
            }
            else
            {
                u32IrqChannel = 0U;
            }
        }

        s_apFcsmuISRCallback(FCSMU_FAULT_IRQ, u32IrqChannel);
    }
    else if ((FCSMU_IRQ_STAT_WARNING_IRQ_MASK & u32TempValue) == FCSMU_IRQ_STAT_WARNING_IRQ_MASK)
    {
        u32IrqChannel = FCSMU_GetNtwFlag() & 0xFFU;

        if (u32IrqChannel == 0xFFU)
        {
            u32IrqChannel = FCSMU_GetFaultChannel();
        }
        else
        {
            if (u32IrqChannel > 0U && u32IrqChannel <= 32U)
            {
                u32IrqChannel = (uint32_t)1U << (u32IrqChannel - (uint32_t)1U);
            }
            else
            {
                u32IrqChannel = 0U;
            }
        }

        s_apFcsmuISRCallback(FCSMU_WARNING_IRQ, u32IrqChannel);

    }
    else if ((FCSMU_IRQ_STAT_CFG_TO_IRQ_MASK & u32TempValue) == FCSMU_IRQ_STAT_CFG_TO_IRQ_MASK)
    {
        s_apFcsmuISRCallback(FCSMU_CFG_TIMEOUT, 0);
    }
    else
    {

    }
}

void FCSMU0_IRQHandler(void)
{
    FCSMUn_IRQHandler();
}
