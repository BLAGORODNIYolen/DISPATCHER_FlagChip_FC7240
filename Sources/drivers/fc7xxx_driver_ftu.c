/**
 * @file fc7xxx_driver_ftu.c
 * @author Flagchip
 * @brief FC7xxx FTU driver type definition and API
 * @version 0.1.0
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2022-11-15    Flagchip070   N/A          First version for FC7300
   ******************************************************************************** */

#include "fc7xxx_driver_ftu.h"
#include "fc7xxx_driver_pcc.h"
#include "interrupt_manager.h"
#include "HwA_scm.h"

/********* Local variable ************/
static const uint32_t s_aFtuMaxCounter[FTU_INSTANCE_COUNT] = {0xFFFFu, 0xFFFFFFu, 0xFFFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu};
static FTU_Type * const s_pFtuBasePtrs[FTU_INSTANCE_COUNT] = FTU_BASE_PTRS;
static FTU_ClkSrcType s_eFtuClkSrc[FTU_INSTANCE_COUNT] = {FTU_NO_CLK};

static FTU_ChannelCallBackType		s_pChannelCallback[FTU_INSTANCE_COUNT] = {NULL};
static FTU_FaultCallBackType		s_pFaultCallback[FTU_INSTANCE_COUNT] = {NULL};
static FTU_InterruptCallBackType 	s_pOverflowCallback[FTU_INSTANCE_COUNT] = {NULL};
static FTU_InterruptCallBackType	s_pReloadPointCallback[FTU_INSTANCE_COUNT] = {NULL};

/***************** Local Prototype Functions *********************/
static void enable_sync_flag(FTU_Type *pFtu, uint16_t u16SyncFlag);
static void disable_sync_flag(FTU_Type *pFtu, uint16_t u16SyncFlag);
static void disable_reload_points(FTU_Type *pFtu, uint16_t u16ReloadPoints);
static void enable_reload_points(FTU_Type *pFtu, uint16_t u16ReloadPoints);

/********* Local Functions ************/
/**
 * @brief Configure the input capture edge of the selected FTU channel
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel index of the FTU instance
 * @param eEdge input capture edge
 */
static void set_ftu_input_edge(FTU_Type *pFtu, uint8_t u8Channel, FTU_InputCapturePinModeType eEdge)
{
	if (FTU_INPUT_RISING_EDGE == eEdge)
	{
		FTU_HWA_ConfigChannelEdgeLevel(pFtu, u8Channel, FTU_CHANNEL_EDGE_RISING);
	}
	else if (FTU_INPUT_FALLING_EDGE == eEdge)
	{
		FTU_HWA_ConfigChannelEdgeLevel(pFtu, u8Channel, FTU_CHANNEL_EDGE_FALLING);
	}
	else if (FTU_INPUT_BOTH_EDGE == eEdge)
	{
		FTU_HWA_ConfigChannelEdgeLevel(pFtu, u8Channel, FTU_CHANNEL_EDGE_BOTH);
	}
	else
	{
		FTU_HWA_ConfigChannelEdgeLevel(pFtu, u8Channel, FTU_CHANNEL_EDGE_NOT_USED);
	}
}
/**
 * @brief Enable the synchronization of the selected FTU instance
 *
 * @param pFtu the base address of the FTU instance
 * @param u16SyncFlag The synchronization flag
 */
static void enable_sync_flag(FTU_Type *pFtu, uint16_t u16SyncFlag) 
{
	uint32_t u32Loop;
    if(0u != (u16SyncFlag & (uint16_t)FTU_SYNC_FLAG_FTUEN))
    {
        FTU_HWA_SetModuleUpdateRegBySync(pFtu);
    }
    if(0u != (u16SyncFlag & (uint16_t)FTU_SYNC_FLAG_LDOK))
    {
        FTU_HWA_SetPwmLoadEnable(pFtu);
    }
    if(0u != (u16SyncFlag & (uint16_t)FTU_SYNC_FLAG_CNTINC))
    {
        FTU_HWA_SetCntinSync(pFtu);
    }
    for(u32Loop = 0; u32Loop < 4u; u32Loop++)
    {
        if(0u != (u16SyncFlag & (uint16_t)((uint16_t)FTU_SYNC_FLAG_SYNCEN01 << u32Loop)))
        {
            FTU_HWA_SetChannelSyncEnable(pFtu, u32Loop);
        }
    }
    if(0u != (u16SyncFlag & (uint16_t)FTU_SYNC_FLAG_PWMSYNC))
    {
        FTU_HWA_SetPwmSyncMode(pFtu);
    }
    if(0u != (u16SyncFlag & (uint16_t)FTU_SYNC_FLAG_REINIT))
    {
        FTU_HWA_SetReinitBySync(pFtu);
    }
    if(0u != (u16SyncFlag & (uint16_t)FTU_SYNC_FLAG_SYNCHOM))
    {
        FTU_HWA_EnableOutputMaskBySync(pFtu);
    }
}

/**
 * @brief Disable the synchronization of the selected FTU instance
 *
 * @param pFtu the base address of the FTU instance
 * @param u16SyncFlag The synchronization flag
 */
static void disable_sync_flag(FTU_Type *pFtu, uint16_t u16SyncFlag)
{
	uint32_t u32Loop;
    if(0u != (u16SyncFlag & (uint16_t)FTU_SYNC_FLAG_FTUEN))
    {
        FTU_HWA_ClearModuleUpdateRegBySync(pFtu);
    }
    if(0u != (u16SyncFlag & (uint16_t)FTU_SYNC_FLAG_LDOK))
    {
        FTU_HWA_ClearPwmLoadEnable(pFtu);
    }
    if(0u != (u16SyncFlag & (uint16_t)FTU_SYNC_FLAG_CNTINC))
    {
        FTU_HWA_ClearCntinSync(pFtu);
    }
    for(u32Loop = 0; u32Loop < 4u; u32Loop++)
    {
        if(0u != (u16SyncFlag & ((uint16_t)FTU_SYNC_FLAG_SYNCEN01 << u32Loop)))
        {
            FTU_HWA_ClearChannelSyncEnable(pFtu, u32Loop);
        }
    }
    if(0u != (u16SyncFlag & (uint16_t)FTU_SYNC_FLAG_PWMSYNC))
    {
        FTU_HWA_ClearPwmSyncMode(pFtu);
    }
    if(0u != (u16SyncFlag & (uint16_t)FTU_SYNC_FLAG_REINIT))
    {
        FTU_HWA_ClearReinitBySync(pFtu);
    }
    if(0u != (u16SyncFlag & (uint16_t)FTU_SYNC_FLAG_SYNCHOM))
    {
        FTU_HWA_DisableOutputMaskBySync(pFtu);
    }
}

/**
 * @brief Disable the reload points of the selected FTU instance
 *
 * @param pFtu the base address of the FTU instance
 * @param u16ReloadPoints The reload points flag
 */
static void disable_reload_points(FTU_Type *pFtu, uint16_t u16ReloadPoints)
{
	uint32_t u32Loop;
    if(0u != (u16ReloadPoints & (uint16_t)FTU_RELOAD_POINT_CNTMAX))
    {
        /* Enables Maximum Loading Point */
        FTU_HWA_DisableMaxLoadPoint(pFtu);
    }
    if(0u != (u16ReloadPoints & (uint16_t)FTU_RELOAD_POINT_CNTMIN))
    {
        /* Disables Minimum Loading Point */
        FTU_HWA_DisableMinLoadPoint(pFtu);
    }
    for(u32Loop = 0u; u32Loop < FTU_CHANNEL_CONTROLS_COUNT; u32Loop++)
    {
        if(0u != (u16ReloadPoints & (uint16_t)((uint16_t)FTU_RELOAD_POINT_CHANNEL_0 << u32Loop)))
        {
            /* Channel match is not included as a reload opportunity */
            FTU_HWA_DisableChannelMatchReload(pFtu, u32Loop);
        }
    }
}

/**
 * @brief Enable the reload points of the selected FTU instance
 *
 * @param pFtu the base address of the FTU instance
 * @param u16ReloadPoints The reload points flag
 */ 
static void enable_reload_points(FTU_Type *pFtu, uint16_t u16ReloadPoints)
{
	uint32_t u32Loop;
    if(0u != (u16ReloadPoints & (uint32_t)FTU_RELOAD_POINT_CNTMAX))
    {
        /* Enables Maximum Loading Point */
        FTU_HWA_EnableMaxLoadPoint(pFtu);
    }
    if(0u != (u16ReloadPoints & (uint32_t)FTU_RELOAD_POINT_CNTMIN))
    {
        /* Enables Minimum Loading Point */
        FTU_HWA_EnableMinLoadPoint(pFtu);
    }
    for(u32Loop = 0; u32Loop < FTU_CHANNEL_CONTROLS_COUNT; u32Loop++)
    {
        if(0u != (u16ReloadPoints & ((uint32_t)FTU_RELOAD_POINT_CHANNEL_0 << u32Loop)))
        {
            /* Channel match is included as a reload opportunity */
            FTU_HWA_EnableChannelMatchReload(pFtu, u32Loop);
        }
    }
}

/********* Global Functions ************/
/**
 * @brief Enable the reload points of the selected FTU instance
 *
 * @param eInstance the selected FTU instance
 * @param u16ReloadPoints The reload points flag
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_EnableReloadPoints(const FTU_InstanceType eInstance, uint16_t u16ReloadPoints)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		enable_reload_points(s_pFtuBasePtrs[eInstance], u16ReloadPoints);
	}
	return eStatus;
}

/**
 * @brief Disable the reload points of the selected FTU instance
 *
 * @param eInstance the selected FTU instance
 * @param u16ReloadPoints The reload points flag
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_DisableReloadPoints(const FTU_InstanceType eInstance, uint16_t u16ReloadPoints)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		disable_reload_points(s_pFtuBasePtrs[eInstance], u16ReloadPoints);
	}
	return eStatus;
}

/**
 * @brief enable the synchronization of the selected FTU
 *
 * @param eInstance the selected FTU instance
 * @param u16ReloadPoints The synchronization flag
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_EnableSync(const FTU_InstanceType eInstance, uint16_t u16SyncFlag)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		enable_sync_flag(s_pFtuBasePtrs[eInstance], u16SyncFlag);
	}
	return eStatus;
}

/**
 * @brief disable the synchronization of the selected FTU
 *
 * @param eInstance the selected FTU instance
 * @param u16ReloadPoints The synchronization flag
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_DisableSync(const FTU_InstanceType eInstance, uint16_t u16SyncFlag)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		disable_sync_flag(s_pFtuBasePtrs[eInstance], u16SyncFlag);
	}
	return eStatus;
}

/**
 * @brief Initialize FTU basic configuration
 *
 * @param eInstance the selected FTU instance
 * @param pCommonStruct the basic configurations of the FTU instance
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_CommonInit(const FTU_InstanceType eInstance, const FTU_CommonType *const pCommonStruct)
{
    FTU_StatusType eRet = FTU_STATUS_SUCCESS;
    if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
    {
        eRet = FTU_STATUS_PARAM_INVALID;
    }
    else if (pCommonStruct->u32OverflowValue > s_aFtuMaxCounter[(uint32_t)eInstance])
    {
    	eRet = FTU_STATUS_PARAM_INVALID;
    }
    else
    {
        if (true == pCommonStruct->bGtbEnable)
        {
        	FTU_HWA_EnableGlobalTimeBase(s_pFtuBasePtrs[eInstance]);
        }
        else
        {
        	FTU_HWA_DisableGlobalTimeBase(s_pFtuBasePtrs[eInstance]);
        }
        FTU_HWA_DisableModuleCpwmMode(s_pFtuBasePtrs[eInstance]);
        /* set FTU prescale */
        FTU_HWA_SetModulePrescale(s_pFtuBasePtrs[eInstance], pCommonStruct->ePrescaler);
		/* configure fault filter prescaler */
        FTU_HWA_ConfigModuleFilterPrescale(s_pFtuBasePtrs[eInstance], pCommonStruct->eFliterPrescaler);
        /*set the compare register as max value*/
        FTU_HWA_SetModuleCompareValue(s_pFtuBasePtrs[eInstance], (uint32_t)pCommonStruct->u32OverflowValue);
        /*set initial value as 0*/
        FTU_HWA_SetCounterInitialValue(s_pFtuBasePtrs[eInstance], 0u);
        /*set any value to clear the current counter register to initial value*/
        FTU_HWA_ClearModuleCounter(s_pFtuBasePtrs[eInstance], (uint32_t)0x1U);
        /* set ftu OUTMASK sync mode, set bit SYNCHOM and OUTMASK register will update when then sync event happened */
        FTU_HWA_EnableOutputMaskBySync(s_pFtuBasePtrs[eInstance]);
        /* set ftu debug mode */
        FTU_HWA_ConfigDebugMode(s_pFtuBasePtrs[eInstance], (uint32_t)pCommonStruct->eDbgMode);
        /* Disable channel match trigger/interrupt when count-up/down in CPWM/QUAD mode */
        FTU_HWA_ConfigUpDownDisable(s_pFtuBasePtrs[eInstance], pCommonStruct->eUpDownDisable);
        /*configure the synchronization*/
        disable_sync_flag(s_pFtuBasePtrs[eInstance], ~pCommonStruct->u16SyncFlag);
        enable_sync_flag(s_pFtuBasePtrs[eInstance], pCommonStruct->u16SyncFlag);

        /*configure the reload points*/
        disable_reload_points(s_pFtuBasePtrs[eInstance], ~pCommonStruct->u16ReloadPoints);
        enable_reload_points(s_pFtuBasePtrs[eInstance], pCommonStruct->u16ReloadPoints);

        /* configure hardware trigger mode */
        FTU_HWA_ConfigTrigMode(s_pFtuBasePtrs[eInstance], pCommonStruct->eHwTrigMode);
        /* configure the frequency of the reload opportunities*/
        FTU_HWA_ConfigFreqOfReloadOp(s_pFtuBasePtrs[eInstance], pCommonStruct->u8ReloadFreq);

        /* select clock source */
        if (FTU_INTERNAL_CLK == pCommonStruct->eClkSrc)
		{
			s_eFtuClkSrc[eInstance] = FTU_INTERNAL_CLK;
		}
		else if (FTU_EXTERNAL_CLK0 == pCommonStruct->eClkSrc)
		{
			s_eFtuClkSrc[eInstance] = FTU_EXTERNAL_CLK0;
			FTU_HWA_ConfigExternalClkSrc(s_pFtuBasePtrs[eInstance], FTU_TCLK0_USED);
		}
		else if (FTU_EXTERNAL_CLK1 == pCommonStruct->eClkSrc)
		{
			s_eFtuClkSrc[eInstance] = FTU_EXTERNAL_CLK1;
			FTU_HWA_ConfigExternalClkSrc(s_pFtuBasePtrs[eInstance], FTU_TCLK1_USED);
		}
		else if (FTU_EXTERNAL_CLK2 == pCommonStruct->eClkSrc)
		{
			s_eFtuClkSrc[eInstance] = FTU_EXTERNAL_CLK2;
			FTU_HWA_ConfigExternalClkSrc(s_pFtuBasePtrs[eInstance], FTU_TCLK2_USED);
		}
		else
		{
			s_eFtuClkSrc[eInstance] = FTU_NO_CLK;
		}
    }
    return eRet;
}

/**
 * @brief De-initialize the FTU instance
 *
 * @param eInstance the selected FTU instance
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_DeInit(const FTU_InstanceType eInstance)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		s_eFtuClkSrc[eInstance] = FTU_NO_CLK;
		s_pChannelCallback[eInstance] = NULL;
		s_pFaultCallback[eInstance] = NULL;
		s_pOverflowCallback[eInstance] = NULL;
		s_pReloadPointCallback[eInstance] = NULL;

		FTU_HWA_ClearModuleRegister(s_pFtuBasePtrs[eInstance]);
	}
	return eStatus;
}

/**
 * @brief Fills in the FTU configuration structure with the default settings.
 *
 * @param pCommonStruct Pointer to the user configuration structure
 */
void FTU_GetDefaultInitCfg(FTU_CommonType *pCommonStruct)
{
	DEV_ASSERT(NULL_PTR != pCommonStruct);
	pCommonStruct->ePrescaler 			= FTU_DIV_1;
	pCommonStruct->eFliterPrescaler		= FTU_FLT_DIV_1;
	pCommonStruct->u32OverflowValue		= 0xFFFF;
	pCommonStruct->eClkSrc				= FTU_INTERNAL_CLK;
	pCommonStruct->u16ReloadPoints 		= (uint16_t)FTU_RELOAD_POINT_CNTMAX;
	pCommonStruct->u8ReloadFreq			= 0;
	pCommonStruct->u16SyncFlag			= 0;
	pCommonStruct->eHwTrigMode			= FTU_CLEARS_TRIG_WHEN_DETECTED;
	pCommonStruct->eDbgMode				= FTU_DBG_COUNTER_WORKS_CHN_WORKS;
	pCommonStruct->eUpDownDisable		= FTU_DISABLE_TRIG_INTR_NONE;
	pCommonStruct->bGtbEnable			= false;
}

/**
 * @brief Configure FTU to counter mode
 *
 * @param eInstance the selected FTU instance
 * @param pCounterStruct the configurations of the counter mode
 * @return FTU_StatusType whether the operation is successfully
 * @note This function will stop timer
 */
FTU_StatusType FTU_CounterModeInit(const FTU_InstanceType eInstance, const FTU_CounterModeType *const pCounterStruct)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else if (  (pCounterStruct->u32CounterValue > s_aFtuMaxCounter[(uint32_t)eInstance])
			|| (pCounterStruct->u32InitialValue > s_aFtuMaxCounter[(uint32_t)eInstance]))
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		/* disable ftu timer */
		FTU_HWA_ConfigModuleClkSrc(s_pFtuBasePtrs[eInstance], FTU_MODULE_NO_CLK);
		/* set FTU MOD register value */
		FTU_HWA_SetModuleCompareValue(s_pFtuBasePtrs[eInstance], (uint32_t)pCounterStruct->u32CounterValue);
		/*set initial value */
		FTU_HWA_SetCounterInitialValue(s_pFtuBasePtrs[eInstance], (uint32_t)pCounterStruct->u32InitialValue);
	}
	return eStatus;
}

/**
 * @brief Update the duty cycle of the FTU instance
 *
 * @param eInstance the selected FTU instance
 * @param u8Channel the selected FTU channel
 * @param u32Duty duty cycle of the PWM mode
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_PwmUpdateDuty(const FTU_InstanceType eInstance, uint8_t u8Channel, uint32_t u32Duty)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	uint8_t u8CpwmFlag;
	if (((uint32_t)eInstance >= FTU_INSTANCE_COUNT) ||
		(u8Channel >= FTU_CHANNEL_CONTROLS_COUNT) ||
		(u32Duty > s_aFtuMaxCounter[(uint32_t)eInstance]))
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		/* get the cpwm flag*/
		u8CpwmFlag = FTU_HWA_GetModuleCpwmMode(s_pFtuBasePtrs[eInstance]);
		if(0u != u8CpwmFlag)
		{
			/* Duty value div 2 if cpwm mode*/
			FTU_HWA_SetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel, (uint32_t)u32Duty >> 1u);
		}
		else
		{
			FTU_HWA_SetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel, u32Duty);
		}
	}
	return eStatus;
}

static void set_deadtime(FTU_Type *pFtu, uint8_t u8Channel, uint32_t u32Deadtime, bool bPair)
{
	/* enable channel deadtime, channel 0/1 2/3 4/5 6/7 are combined*/
	FTU_HWA_EnableChannelDeadtime(pFtu, u8Channel);
	if(u32Deadtime < 1024u)
	{
		if(bPair)
		{
			/* PAIRDEADTIME has a high priority*/
			FTU_HWA_ConfigPairDeadtimePrescaler(pFtu, u8Channel, FTU_DEADTIME_PRESCALER_DIV_1);
			FTU_HWA_ConfigPairDeadtimeValue(pFtu, u8Channel, u32Deadtime);
		}
		else
		{
			/* DEADTIME shoud recover PAIRDEADTIME*/
			FTU_HWA_ConfigDeadtimePrescaler(pFtu, FTU_DEADTIME_PRESCALER_DIV_1);
			FTU_HWA_ConfigDeadtimeValue(pFtu, u32Deadtime);
		}
	}
	else if(u32Deadtime < 4096u)
	{
		/*deadtime should multiply 2*/
		if(bPair)
		{
			/* PAIRDEADTIME has a high priority*/
			FTU_HWA_ConfigPairDeadtimePrescaler(pFtu, u8Channel,
												FTU_DEADTIME_PRESCALER_DIV_4);
			FTU_HWA_ConfigPairDeadtimeValue(pFtu, (uint32_t)u8Channel, u32Deadtime >> 2u);
		}
		else
		{
			/* DEADTIME shoud recover PAIRDEADTIME*/
			FTU_HWA_ConfigDeadtimePrescaler(pFtu, FTU_DEADTIME_PRESCALER_DIV_4);
			FTU_HWA_ConfigDeadtimeValue(pFtu, u32Deadtime >> 2u);
		}
	}
	else
	{
		/*deadtime should multiply 4*/
		if(bPair)
		{
			/* PAIRDEADTIME has a high priority*/
			FTU_HWA_ConfigPairDeadtimePrescaler(pFtu, u8Channel, FTU_DEADTIME_PRESCALER_DIV_16);
			FTU_HWA_ConfigPairDeadtimeValue(pFtu, u8Channel, u32Deadtime >> 4u);
		}
		else
		{
			/* DEADTIME shoud recover PAIRDEADTIME*/
			FTU_HWA_ConfigDeadtimePrescaler(pFtu, FTU_DEADTIME_PRESCALER_DIV_16);
			FTU_HWA_ConfigDeadtimeValue(pFtu, u32Deadtime >> 4u);
		}
	}
}

/**
 * @brief Configure FTU to PWM mode
 *
 * @param eInstance the selected FTU instance
 * @param pPwmModeStruct the configurations of the PWM mode
 * @return FTU_StatusType whether the operation is successfully
 * @note This function will stop timer
 */
FTU_StatusType FTU_PwmModeInit(const FTU_InstanceType eInstance, const FTU_PwmModeType *const pPwmModeStruct)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	uint8_t u8Channel;
	uint32_t u32Loop;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else if (pPwmModeStruct->u32PwmPeriod > s_aFtuMaxCounter[(uint32_t)eInstance])
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}

	for (u32Loop = 0u; u32Loop < pPwmModeStruct->u32ChannelCount; u32Loop++)
	{
		if (pPwmModeStruct->pPwmChannels[u32Loop].u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
		{
			eStatus = FTU_STATUS_PARAM_INVALID;
			break;
		}

		if (   (pPwmModeStruct->pPwmChannels[u32Loop].u32PwmDuty > s_aFtuMaxCounter[(uint32_t)eInstance])
			|| (pPwmModeStruct->pPwmChannels[u32Loop].u32PhaseShift > s_aFtuMaxCounter[(uint32_t)eInstance]))
		{
			eStatus = FTU_STATUS_PARAM_INVALID;
			break;
		}

		if (   (FTU_CENTER_ALIGNED_PWM == pPwmModeStruct->eAlignedMode)
			&& (0u < pPwmModeStruct->pPwmChannels[u32Loop].u32PhaseShift))
		{
			eStatus = FTU_STATUS_PARAM_INVALID;
			break;
		}
		if (   (true == pPwmModeStruct->pPwmChannels[u32Loop].bLinkMode)
			&& (0u < pPwmModeStruct->pPwmChannels[u32Loop].u32PhaseShift))
		{
			eStatus = FTU_STATUS_PARAM_INVALID;
			break;
		}
		if ((   (true == pPwmModeStruct->pPwmChannels[u32Loop].bLinkMode)
			|| (0u < pPwmModeStruct->pPwmChannels[u32Loop].u32PhaseShift))
			&& (pPwmModeStruct->pPwmChannels[u32Loop].u8Channel & 1u))
		{
			eStatus = FTU_STATUS_PARAM_INVALID;
			break;
		}
	}

	if (FTU_STATUS_SUCCESS == eStatus)
	{
		/* disable ftu timer */
		FTU_HWA_ConfigModuleClkSrc(s_pFtuBasePtrs[eInstance], FTU_MODULE_NO_CLK);
		if (FTU_EDGE_ALIGNED_PWM == pPwmModeStruct->eAlignedMode)
		{
			FTU_HWA_DisableModuleCpwmMode(s_pFtuBasePtrs[eInstance]);
			FTU_HWA_SetModuleCompareValue(s_pFtuBasePtrs[eInstance], pPwmModeStruct->u32PwmPeriod);
		}
		else
		{
			FTU_HWA_EnableModuleCpwmMode(s_pFtuBasePtrs[eInstance]);
			FTU_HWA_SetModuleCompareValue(s_pFtuBasePtrs[eInstance], pPwmModeStruct->u32PwmPeriod >> 1u);
		}
		set_deadtime(s_pFtuBasePtrs[eInstance], 0u, pPwmModeStruct->u32PublicDeadtime, false);

		for (u32Loop = 0u; u32Loop < pPwmModeStruct->u32ChannelCount; u32Loop++)
		{
			FTU_PwmChannelType *pChannelCfg = &pPwmModeStruct->pPwmChannels[u32Loop];
			u8Channel = pChannelCfg->u8Channel;
			if(pChannelCfg->bLinkMode)
			{
				/* set channel(n+1) complement of channel(n) output */
				FTU_HWA_EnableChannelComplement(s_pFtuBasePtrs[eInstance], u8Channel);
				if (!pChannelCfg->bLinkChannelComplement)
				{
					FTU_HWA_ClearChannelPolarity(s_pFtuBasePtrs[eInstance], (uint8_t)1U << u8Channel);
					FTU_HWA_SetChannelPolarity(s_pFtuBasePtrs[eInstance], (uint8_t)1U << (u8Channel + (uint8_t)1U));
				}
				else
				{
					FTU_HWA_ClearChannelPolarity(s_pFtuBasePtrs[eInstance],
												(uint8_t)1U << u8Channel| (uint8_t)1U << (u8Channel  + 1u));
				}
				/*link mode, the u8Channel+1->csc.ELSB bit must be set*/
				FTU_HWA_ConfigChannelPwmLinkMode(s_pFtuBasePtrs[eInstance], u8Channel + (uint8_t)1U);
				/* enable u8Channel sync function of the ftu*/
				FTU_HWA_EnableChannelSync(s_pFtuBasePtrs[eInstance], u8Channel);
				/* configure pin output as channel mode*/
				FTU_HWA_ConfigTrigOutputMode(s_pFtuBasePtrs[eInstance], u8Channel, FTU_TRIG_OUTPUT_AS_CHANNEL_MODE);
				FTU_HWA_ConfigTrigOutputMode(s_pFtuBasePtrs[eInstance], u8Channel + 1u, FTU_TRIG_OUTPUT_AS_CHANNEL_MODE);
				/* enable FTU output */
				FTU_HWA_EnableChannelsOutput(s_pFtuBasePtrs[eInstance], (uint8_t)3U << u8Channel);
			}
			else
			{
				if (pChannelCfg->u32PhaseShift)
				{
					FTU_HWA_ClearChannelPolarity(s_pFtuBasePtrs[eInstance], (uint8_t)1U << (u8Channel + 1));
					/* enable u8Channel sync function of the ftu*/
					FTU_HWA_EnableChannelSync(s_pFtuBasePtrs[eInstance], u8Channel);

					/*Enable enhanced phase shift mode*/
					FTU_HWA_EnableChannelPhase(s_pFtuBasePtrs[eInstance], u8Channel);
					FTU_HWA_EnableChannelEnhancedPhase(s_pFtuBasePtrs[eInstance], u8Channel);
				}
				else
				{
					/* enable u8Channel sync function of the ftu*/
					FTU_HWA_DisableChannelSync(s_pFtuBasePtrs[eInstance], u8Channel);

					/*Enable enhanced phase shift mode*/
					FTU_HWA_DisableChannelPhase(s_pFtuBasePtrs[eInstance], u8Channel);
					FTU_HWA_DisableChannelPhase(s_pFtuBasePtrs[eInstance], u8Channel);
				}

				/* disable channel(n+1) complement of channel(n) output */
				FTU_HWA_DisableChannelComplement(s_pFtuBasePtrs[eInstance], u8Channel);
				FTU_HWA_ClearChannelPolarity(s_pFtuBasePtrs[eInstance], (uint8_t)1U << u8Channel);
				/* enable FTU output */
				FTU_HWA_EnableChannelsOutput(s_pFtuBasePtrs[eInstance], (uint8_t)1U << u8Channel);
				/* configure pin output as channel mode*/
				FTU_HWA_ConfigTrigOutputMode(s_pFtuBasePtrs[eInstance], u8Channel, FTU_TRIG_OUTPUT_AS_CHANNEL_MODE);

			}
			/* set FTU pwm mode */
			if (   (FTU_PWM_HIGH_TRUE_PULSE == pChannelCfg->ePinMode)
				&& (FTU_EDGE_ALIGNED_PWM == pPwmModeStruct->eAlignedMode))
			{
				FTU_HWA_ConfigChannelMode(s_pFtuBasePtrs[eInstance], u8Channel, FTU_CHANNEL_MODE_EDGE_ALIGN_PWM);
				FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], u8Channel, FTU_CHANNEL_PWM_HIGH_TRUE);
			}
			else if (   (FTU_PWM_LOW_TRUE_PULSE == pChannelCfg->ePinMode)
					 && (FTU_EDGE_ALIGNED_PWM == pPwmModeStruct->eAlignedMode))
			{
				FTU_HWA_ConfigChannelMode(s_pFtuBasePtrs[eInstance], u8Channel, FTU_CHANNEL_MODE_EDGE_ALIGN_PWM);
				FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], u8Channel, FTU_CHANNEL_PWM_LOW_TRUE);
			}
			else if (   (FTU_PWM_HIGH_TRUE_PULSE == pChannelCfg->ePinMode)
					&& (FTU_CENTER_ALIGNED_PWM == pPwmModeStruct->eAlignedMode))
			{
				FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], u8Channel, FTU_CHANNEL_PWM_HIGH_TRUE);
			}
			else if (   (FTU_PWM_LOW_TRUE_PULSE == pChannelCfg->ePinMode)
					 && (FTU_CENTER_ALIGNED_PWM == pPwmModeStruct->eAlignedMode))
			{
				FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], u8Channel, FTU_CHANNEL_PWM_LOW_TRUE);
			}

			if (pChannelCfg->bDeadtimeEnable)
			{
				FTU_HWA_EnableChannelDeadtime(s_pFtuBasePtrs[eInstance], u8Channel);
			}
			else
			{
				FTU_HWA_DisableChannelDeadtime(s_pFtuBasePtrs[eInstance], u8Channel);
			}

			/* set the period time and duty time */
			if(FTU_CENTER_ALIGNED_PWM == pPwmModeStruct->eAlignedMode)
			{
				FTU_HWA_SetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel, pChannelCfg->u32PwmDuty >> 1u);
			}
			else
			{
				if (pChannelCfg->u32PhaseShift)
				{
					FTU_HWA_SetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel, pChannelCfg->u32PhaseShift);
					if ((pChannelCfg->u32PhaseShift + pChannelCfg->u32PwmDuty) > pPwmModeStruct->u32PwmPeriod)
					{
						FTU_HWA_SetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel + 1,
												pChannelCfg->u32PhaseShift + pChannelCfg->u32PwmDuty - pPwmModeStruct->u32PwmPeriod - 1);
					}
					else
					{
						FTU_HWA_SetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel + 1,
								pChannelCfg->u32PhaseShift + pChannelCfg->u32PwmDuty);
					}

				}
				else
				{
					FTU_HWA_SetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel, pChannelCfg->u32PwmDuty);
				}
			}
			set_deadtime(s_pFtuBasePtrs[eInstance], u8Channel, pChannelCfg->u32ChannelDeadtime, true);
		}
	}
	return eStatus;
}

/**
 * @brief Configure FTU to output compare mode
 *
 * @param eInstance the selected FTU instance
 * @param pOutputModeStruct the configurations of the output compare mode
 * @return FTU_StatusType whether the operation is successfully
 * @note This function will stop timer
 */
FTU_StatusType FTU_OutputCompareModeInit(const FTU_InstanceType eInstance,
                                         const FTU_OutputCompareModeType *const pOCConfig)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if (((uint32_t)eInstance >= FTU_INSTANCE_COUNT) || (pOCConfig->u8Channel >= FTU_CHANNEL_CONTROLS_COUNT))
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else if ( pOCConfig->u32CompareValue > s_aFtuMaxCounter[(uint32_t)eInstance])
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		/* disable ftu timer */
		FTU_HWA_ConfigModuleClkSrc(s_pFtuBasePtrs[eInstance], FTU_MODULE_NO_CLK);
		FTU_HWA_DisableChannelEnhancedPhase(s_pFtuBasePtrs[eInstance], pOCConfig->u8Channel);
		FTU_HWA_DisableChannelPhase(s_pFtuBasePtrs[eInstance], pOCConfig->u8Channel);
		FTU_HWA_ConfigInputCaptureMeasureMode(s_pFtuBasePtrs[eInstance], pOCConfig->u8Channel,
											  FTU_MEASURE_MODE_OFF);
		FTU_HWA_ConfigChannelMode(s_pFtuBasePtrs[eInstance], pOCConfig->u8Channel, FTU_CHANNEL_MODE_OUTPUT_COMPARE);
		if (FTU_OUTPUT_TOGGLE_PIN == pOCConfig->eOutputMode)
		{
			FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], pOCConfig->u8Channel, FTU_CHANNEL_OC_TOGGLE);
		}
		else if (FTU_OUTPUT_CLEAR_PIN == pOCConfig->eOutputMode)
		{
			FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], pOCConfig->u8Channel, FTU_CHANNEL_OC_CLEAR);
		}
		else if (FTU_OUTPUT_SET_PIN == pOCConfig->eOutputMode)
		{
			FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], pOCConfig->u8Channel, FTU_CHANNEL_OC_SET);
		}
		/* Disable Up-Down Mode*/
		FTU_HWA_DisableModuleCpwmMode(s_pFtuBasePtrs[eInstance]);
		/* enable FTU output */
		FTU_HWA_EnableChannelsOutput(s_pFtuBasePtrs[eInstance], (uint8_t)1U << pOCConfig->u8Channel);
		/* configure initial level */
		if (FTU_OUTPUT_CMP_INIT_LOW == pOCConfig->eInitLevel)
		{
			FTU_HWA_ClearChannelPolarity(s_pFtuBasePtrs[eInstance], (uint8_t)1U << pOCConfig->u8Channel);
		}
		else
		{
			FTU_HWA_SetChannelPolarity(s_pFtuBasePtrs[eInstance], (uint8_t)1U << pOCConfig->u8Channel);
		}
		/* configure pin output as channel mode*/
		FTU_HWA_ConfigTrigOutputMode(s_pFtuBasePtrs[eInstance], pOCConfig->u8Channel, FTU_TRIG_OUTPUT_AS_CHANNEL_MODE);
		/* set FTU CV register value*/
		FTU_HWA_SetChannelValue(s_pFtuBasePtrs[eInstance], pOCConfig->u8Channel, (uint32_t)pOCConfig->u32CompareValue);

	}
	return eStatus;
}

/**
 * @brief Enable the output trigger of the selected FTU instance
 *
 * @param eInstance the selected FTU instance
 * @param u32TriggerOutputMask the output trigger mask
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_EnableTriggerOutput(const FTU_InstanceType eInstance, uint32_t u32TriggerOutputMask)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;

	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		/* enable the channel match trigger */
		FTU_HWA_EnableChannelTriggerOut(s_pFtuBasePtrs[eInstance], (uint8_t)(u32TriggerOutputMask & (uint32_t)FTU_TRIG_OUTPUT_MASK_ALL_CHANNEL_MATCH));
		if (0u != (u32TriggerOutputMask & (uint32_t)FTU_TRIG_OUTPUT_MASK_RELOAD))
		{
			/* enable reload trigger */
			FTU_HWA_EnableReloadTrigger(s_pFtuBasePtrs[eInstance]);
		}
	}
	return eStatus;
}

/**
 * @brief Disable the output trigger of the selected FTU instance
 *
 * @param eInstance the selected FTU instance
 * @param u32TriggerOutputMask the output trigger mask
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_DisableTriggerOutput(const FTU_InstanceType eInstance, uint32_t u32TriggerOutputMask)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		/* disenable the channel match trigger */
		FTU_HWA_DisableChannelTriggerOut(s_pFtuBasePtrs[eInstance], (uint8_t)(u32TriggerOutputMask & (uint32_t)FTU_TRIG_OUTPUT_MASK_ALL_CHANNEL_MATCH));
		if (0u != (u32TriggerOutputMask & (uint32_t)FTU_TRIG_OUTPUT_MASK_RELOAD))
		{
			/* disable reload trigger */
			FTU_HWA_DisableReloadTrigger(s_pFtuBasePtrs[eInstance]);
		}
	}
	return eStatus;
}

/**
 * @brief Start the FTU instance
 *
 * @param eInstance the selected FTU instance
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_StartTimer(const FTU_InstanceType eInstance)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		/* set FTU module clock source */
		if (s_eFtuClkSrc[eInstance] == FTU_NO_CLK)
		{
			eStatus = FTU_STATUS_NO_CLOCK_SOURCE;
		}
		else if(s_eFtuClkSrc[eInstance] == FTU_INTERNAL_CLK)
		{
			FTU_HWA_ConfigModuleClkSrc(s_pFtuBasePtrs[eInstance], FTU_MODULE_INTERNAL_CLK);
		}
		else
		{
			FTU_HWA_ConfigModuleClkSrc(s_pFtuBasePtrs[eInstance], FTU_MODULE_EXTERNAL_CLK);
		}
	}
	return eStatus;
}

/**
 * @brief Stop the FTU global time base
 *
 * @param u32InstanceMask The selected FTU, each bit represents an instance
 */
void FTU_StopGlobalTimeBase(uint32_t u32InstanceMask)
{
	uint32_t u32GTB = 0u, u32Loop0;
	for (u32Loop0 = 0u; u32Loop0 < FTU_INSTANCE_COUNT; u32Loop0++)
	{
		uint32_t u32InstanceFlag = 1u << u32Loop0;
		if (0u != (u32InstanceMask & u32InstanceFlag))
		{
			u32GTB |= u32InstanceFlag;
			SCM_HWA_ClearFtuGTBMask((uint8_t)u32Loop0);
		}
	}
	SCM_HWA_ClearFtuGTBSelect(u32GTB);
}

/**
 * @brief Start the FTU global time base
 *
 * @param u32InstanceMask The selected FTU, each bit represents an instance
 * @param u32StartMask Start time, refer to FTU_GlobalTimeBaseStartType
 */
void FTU_StartGlobalTimeBase(uint32_t u32InstanceMask, uint32_t u32StartMask)
{
	uint32_t u32GTB = 0u, u32Loop0, u32Loop1;
	for (u32Loop0 = 0u; u32Loop0 < FTU_INSTANCE_COUNT; u32Loop0++)
	{
		uint32_t u32InstanceFlag = 1u << u32Loop0;
		if (0u != (u32InstanceMask & u32InstanceFlag))
		{
			if (u32StartMask & FTU_GTB_START_AT_ONCE)
			{
				u32GTB |= u32InstanceFlag;
			}
			for (u32Loop1 = 0u; u32Loop1 < TSTMP_MODULATE_COUNT; u32Loop1++)
			{
				if (u32StartMask & (FTU_GTB_START_AT_TSTMP1_MOD0 << u32Loop1))
				{
					SCM_HWA_ConfigFtuGTBMask((uint8_t)u32Loop0, (1u << u32Loop1));
				}
			}
		}
	}
	SCM_HWA_SetFtuGTBSelect(u32GTB);
}

/**
 * @brief Stop the FTU instance
 *
 * @param eInstance the selected FTU instance
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_StopTimer(const FTU_InstanceType eInstance)
{
    FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
    if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
    {
    	eStatus = FTU_STATUS_PARAM_INVALID;
    }
    else
    {
        /* clear FTU module clock source */
    	FTU_HWA_ConfigModuleClkSrc(s_pFtuBasePtrs[eInstance], FTU_MODULE_NO_CLK);
    	//FTU_HWA_ClearModuleCounter(s_pFtuBasePtrs[eInstance], 0);
    }
    return eStatus;
}

/**
 * @brief Ftu initialize interrupt function
 *
 * @param eInstance the selected FTU instance
 * @param pIntStruct the configurations of the interrupt
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_InterruptInit(const FTU_InstanceType eInstance, const FTU_InterruptType *const pIntrStruct)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	uint32_t u32Loop;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		for(u32Loop = 0u; u32Loop < FTU_CHANNEL_CONTROLS_COUNT; u32Loop++)
		{
			if (0u != (pIntrStruct->u32InterruptMask & ((uint32_t)FTU_INTR_MASK_CHANNEL_0 << u32Loop)))
			{
				/* Enable Channel Interrupt */
				FTU_HWA_EnableChannelInterrupt(s_pFtuBasePtrs[eInstance], (uint8_t)u32Loop);
			}
			else
			{
				/* Disable Channel Interrupt */
				FTU_HWA_DisableChannelInterrupt(s_pFtuBasePtrs[eInstance], (uint8_t)u32Loop);
			}
		}

		if (0u != (pIntrStruct->u32InterruptMask & (uint32_t)FTU_INTR_MASK_OVERFLOW))
		{
			/* Enable Overflow Interrupt */
			FTU_HWA_EnableOverflowInterrupt(s_pFtuBasePtrs[eInstance]);
		}
		else
		{
			/* Disable Overflow Interrupt */
			FTU_HWA_DisableOverflowInterrupt(s_pFtuBasePtrs[eInstance]);
		}

		if (0u != (pIntrStruct->u32InterruptMask & (uint32_t)FTU_INTR_MASK_FAULT))
		{
			/* Enable Fault Interrupt */
			FTU_HWA_EnableModuleFaultInterrupt(s_pFtuBasePtrs[eInstance]);
		}
		else
		{
			/* Disable Fault Interrupt */
			FTU_HWA_DisableModuleFaultInterrupt(s_pFtuBasePtrs[eInstance]);
		}

		if (0u != (pIntrStruct->u32InterruptMask & (uint32_t)FTU_INTR_MASK_RELOAD_POINT))
		{
			/* Enable Reload Point Interrupt */
			FTU_HWA_EnableReloadPointInterrupt(s_pFtuBasePtrs[eInstance]);
		}
		else
		{
			/* Disable Reload Point Interrupt */
			FTU_HWA_DisableReloadPointInterrupt(s_pFtuBasePtrs[eInstance]);
		}

		/*register callback functions*/
		s_pChannelCallback[eInstance] = pIntrStruct->pChannelCallback;
		s_pFaultCallback[eInstance] = pIntrStruct->pFaultCallback;
		s_pOverflowCallback[eInstance] = pIntrStruct->pOverflowCallback;
		s_pReloadPointCallback[eInstance] = pIntrStruct->pReloadPointCallback;
	}
	return eStatus;
}

/**
 * @brief initialize fault input of the selected Ftu instance
 *
 * @param eInstance the selected FTU instance
 * @param pFaultInit the fault configurations of the FTU instance
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_FaultInit(const FTU_InstanceType eInstance, const FTU_FaultInitType *const pFaultInit)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	uint32_t u32Loop, u32Temp;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		/* configure fault mode */
		FTU_HWA_ConfigModuleFaultMode(s_pFtuBasePtrs[eInstance], pFaultInit->eFaultMode);
		/* Disable all fault inputs*/
		u32Temp = FTU_HWA_GetFaultEnable(s_pFtuBasePtrs[eInstance]);
		FTU_HWA_DisableModuleFault(s_pFtuBasePtrs[eInstance], 0xFu);
		/* configure fault filter value */
		FTU_HWA_SetModuleFaultFilterValue(s_pFtuBasePtrs[eInstance], pFaultInit->u8FilterValue);
		/* recover fault inputs*/
		FTU_HWA_EnableModuleFault(s_pFtuBasePtrs[eInstance], (uint8_t)u32Temp);
		/* enables the fault control in channels */
		for(u32Loop = 0u; u32Loop < FTU_FAULT_COUNT; u32Loop++)
		{
			if (0u != (pFaultInit->u8FaultChannelEnable & ((uint8_t)FTU_FAULT_FOR_CHANNEL01 << u32Loop)))
			{
				FTU_HWA_EnableChannelFault(s_pFtuBasePtrs[eInstance], (uint8_t)u32Loop << 1u);
			}
			else
			{
				FTU_HWA_DisableChannelFault(s_pFtuBasePtrs[eInstance], (uint8_t)u32Loop << 1u);
			}
		}

		/* set fault disable channel output delay value */
		FTU_HWA_SetFaultDelay0(s_pFtuBasePtrs[eInstance], pFaultInit->u8FaultDisableDelay0);
		FTU_HWA_SetFaultDelay1(s_pFtuBasePtrs[eInstance], pFaultInit->u8FaultDisableDelay1);
	}
	return eStatus;
}

/**
 * @brief Select fault disable channel output delay value
 *
 * @param eInstance the selected FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 * @param eSelection Fault disable channel output delay value selection.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_FaultSelectDelayValue(const FTU_InstanceType eInstance, uint8_t u8Channel, FTU_FaultDisableDelayType eDelaySelection)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else if (u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		FTU_HWA_SelectFaultDelay(s_pFtuBasePtrs[eInstance], u8Channel, eDelaySelection);
	}
	return eStatus;
}

/**
 * @brief Enable a fault input
 *
 * @param eInstance the selected FTU instance
 * @param pFaultCtrl configurations of the fault input
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_FaultEnable(const FTU_InstanceType eInstance, const FTU_FaultControlType *const pFaultCtrl)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;

	if (((uint32_t)eInstance >= FTU_INSTANCE_COUNT) ||
	    (pFaultCtrl->u8FaultIndex >= FTU_FAULT_COUNT))
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		/* configure fault input polarity */
		FTU_HWA_ConfigFaultPolarity(s_pFtuBasePtrs[eInstance], pFaultCtrl->u8FaultIndex, (uint8_t)pFaultCtrl->eFaultPol);
		if(true == pFaultCtrl->bFaultFilterEnable)
		{
			FTU_HWA_EnableModuleFaultGlitchFilter(s_pFtuBasePtrs[eInstance], 1u << pFaultCtrl->u8FaultIndex);
		}
		else
		{
			FTU_HWA_DisableModuleFaultGlitchFilter(s_pFtuBasePtrs[eInstance], 1u << pFaultCtrl->u8FaultIndex);
		}
		/* enable fault input */
		FTU_HWA_EnableModuleFault(s_pFtuBasePtrs[eInstance], 1u << pFaultCtrl->u8FaultIndex);
	}
	return eStatus;
}

/**
 * @brief Disable a fault input
 *
 * @param eInstance the selected FTU instance
 * @param u32FaultIndex index of the fault input
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_FaultDisable(const FTU_InstanceType eInstance, uint32_t u32FaultIndex)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if (((uint32_t)eInstance >= FTU_INSTANCE_COUNT) ||
		(u32FaultIndex >= FTU_FAULT_COUNT))
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		FTU_HWA_DisableModuleFault(s_pFtuBasePtrs[eInstance], 0x1u << u32FaultIndex);
	}
	return eStatus;
}

/**
 * @brief initialize a input capture channel of the selected Ftu instance
 *
 * @param eInstance the selected FTU instance
 * @param pInputChannel configurations of the input capture channel
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_InputCaptureChannelInit(const FTU_InstanceType eInstance,
                                          const FTU_InputChannelType *const pInputChannel)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;

	if (((uint32_t)eInstance >= FTU_INSTANCE_COUNT) ||
		(pInputChannel->u8Channel >= FTU_CHANNEL_CONTROLS_COUNT))
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		FTU_HWA_DisableQuadratureMode(s_pFtuBasePtrs[eInstance]);
		FTU_HWA_DisableChannelEnhancedPhase(s_pFtuBasePtrs[eInstance], pInputChannel->u8Channel);
		FTU_HWA_DisableChannelPhase(s_pFtuBasePtrs[eInstance], pInputChannel->u8Channel);
		FTU_HWA_ConfigInputCaptureMeasureMode(s_pFtuBasePtrs[eInstance], pInputChannel->u8Channel,
											  FTU_MEASURE_MODE_OFF);
		FTU_HWA_ConfigChannelMode(s_pFtuBasePtrs[eInstance], pInputChannel->u8Channel, FTU_CHANNEL_MODE_INPUT);
		if(pInputChannel->u8Channel < FTU_INPUT_FILTER_COUNT)
		{
			/* set FTU input capture filter value */
			FTU_HWA_ConfigInputCaptureFilter(
					s_pFtuBasePtrs[eInstance], pInputChannel->u8Channel,
					pInputChannel->u8FilterValue);

		}

		set_ftu_input_edge(s_pFtuBasePtrs[eInstance], pInputChannel->u8Channel, pInputChannel->eInputMode);
	}
	return eStatus;
}

/**
 * @brief initialize the quadrature decoder mode
 *
 * @param eInstance the selected FTU instance
 * @param pQuadInit configurations of the quadrature decoder
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_QuadratureModeInit(const FTU_InstanceType eInstance,
                                      const FTU_QuadratureInitType *const pQuadInit)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;

	if (((uint32_t)eInstance != FTU_INSTANCE_1) &&
		((uint32_t)eInstance != FTU_INSTANCE_2) &&
		((uint32_t)eInstance != FTU_INSTANCE_4) &&
		((uint32_t)eInstance != FTU_INSTANCE_5))
	{
		/* Only FTU1/2/4/5 support quadrature decode*/
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		/* set quadrature mode */
		FTU_HWA_ConfigQuadratureMode(s_pFtuBasePtrs[eInstance], pQuadInit->eQuadMode);
		/* set PHA polarity*/
		if(pQuadInit->bPhaInverted)
		{
			FTU_HWA_EnablePhaInv(s_pFtuBasePtrs[eInstance]);
		}
		else
		{
			FTU_HWA_DisablePhaInv(s_pFtuBasePtrs[eInstance]);
		}
		/* set PHB polarity*/
		if(pQuadInit->bPhbInverted)
		{
			FTU_HWA_EnablePhbInv(s_pFtuBasePtrs[eInstance]);
		}
		else
		{
			FTU_HWA_DisablePhbInv(s_pFtuBasePtrs[eInstance]);
		}

		/* Set counter direction */
		FTU_HWA_ConfigQuadDirection(s_pFtuBasePtrs[eInstance], pQuadInit->eQuadDirection);
		/* Set overflow direction */
		FTU_HWA_ConfigTimerOverflowDir(s_pFtuBasePtrs[eInstance], pQuadInit->eOveflowDirection);
		/* set top value */
		FTU_HWA_SetModuleCompareValue(s_pFtuBasePtrs[eInstance], pQuadInit->u16TopValue);
		/* set bottom value */
		FTU_HWA_SetCounterInitialValue(s_pFtuBasePtrs[eInstance], pQuadInit->u16BottomValue);

		/* Set phase A glitch filter value */
		if (0U != pQuadInit->u8PhaFilterVal)
		{
			FTU_HWA_ConfigChannelFilterValue(s_pFtuBasePtrs[eInstance], 0, pQuadInit->u8PhaFilterVal);
			FTU_HWA_EnablePhaGlitchFilter(s_pFtuBasePtrs[eInstance]);
		}
		else
		{
			FTU_HWA_DisablePhaGlitchFilter(s_pFtuBasePtrs[eInstance]);
		}
		/* Set phase B glitch filter value */
		if (0U != pQuadInit->u8PhbFilterVal)
		{
			FTU_HWA_ConfigChannelFilterValue(s_pFtuBasePtrs[eInstance], 1, pQuadInit->u8PhbFilterVal);
			FTU_HWA_EnablePhbGlitchFilter(s_pFtuBasePtrs[eInstance]);
		}
		else
		{
			FTU_HWA_DisablePhbGlitchFilter(s_pFtuBasePtrs[eInstance]);
		}
		/* enable the quadrature*/
		FTU_HWA_EnableQuadratureMode(s_pFtuBasePtrs[eInstance]);
	}
	return eStatus;
}
/**
 * @brief Enable FTU interrupt
 *
 * @param eInstance the selected FTU instance
 * @param u32InterruptMask interrupt enable mask
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_EnableInterrupt(const FTU_InstanceType eInstance, uint32_t u32InterruptMask)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	uint32_t u32Loop;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		for(u32Loop = 0u; u32Loop < FTU_CHANNEL_CONTROLS_COUNT; u32Loop++)
		{
			if (0u != (u32InterruptMask & ((uint32_t)FTU_INTR_MASK_CHANNEL_0 << u32Loop)))
			{
				/* Enable Channel Interrupt */
				FTU_HWA_EnableChannelInterrupt(s_pFtuBasePtrs[eInstance], (uint8_t)u32Loop);
			}
		}

		if (0u != (u32InterruptMask & (uint32_t)FTU_INTR_MASK_OVERFLOW))
		{
			/* Enable Overflow Interrupt */
			FTU_HWA_EnableOverflowInterrupt(s_pFtuBasePtrs[eInstance]);
		}

		if (0u != (u32InterruptMask & (uint32_t)FTU_INTR_MASK_FAULT))
		{
			/* Enable Fault Interrupt */
			FTU_HWA_EnableModuleFaultInterrupt(s_pFtuBasePtrs[eInstance]);
		}

		if (0u != (u32InterruptMask & (uint32_t)FTU_INTR_MASK_RELOAD_POINT))
		{
			/* Enable Reload Point Interrupt */
			FTU_HWA_EnableReloadPointInterrupt(s_pFtuBasePtrs[eInstance]);
		}
	}
	return eStatus;
}

/**
 * @brief Disable FTU interrupt
 *
 * @param eInstance the selected FTU instance
 * @param u32InterruptMask interrupt disable mask
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_DisableInterrupt(const FTU_InstanceType eInstance, uint32_t u32InterruptMask)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	uint32_t u32Loop;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		for(u32Loop = 0; u32Loop < FTU_CHANNEL_CONTROLS_COUNT; u32Loop++)
		{
			if (0u != (u32InterruptMask & ((uint32_t)FTU_INTR_MASK_CHANNEL_0 << u32Loop)))
			{
				/* Disable Channel Interrupt */
				FTU_HWA_DisableChannelInterrupt(s_pFtuBasePtrs[eInstance], (uint8_t)u32Loop);
			}
		}

		if (0u != (u32InterruptMask & (uint32_t)FTU_INTR_MASK_OVERFLOW))
		{
			/* Disable Overflow Interrupt */
			FTU_HWA_DisableOverflowInterrupt(s_pFtuBasePtrs[eInstance]);
		}

		if (0u != (u32InterruptMask & (uint32_t)FTU_INTR_MASK_FAULT))
		{
			/* Disable Fault Interrupt */
			FTU_HWA_DisableModuleFaultInterrupt(s_pFtuBasePtrs[eInstance]);
		}

		if (0u != (u32InterruptMask & (uint32_t)FTU_INTR_MASK_RELOAD_POINT))
		{
			/* Disable Reload Point Interrupt */
			FTU_HWA_DisableReloadPointInterrupt(s_pFtuBasePtrs[eInstance]);
		}
	}
	return eStatus;
}

/**
 * @brief Clear the fault flag of the FTU instance
 *
 * @param eInstance the selected FTU instance
 * @param u32FaultFlag flag to clear
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_ClearFault(const FTU_InstanceType eInstance, uint32_t u32FaultFlag)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		FTU_HWA_ClearModuleFaultFlag(s_pFtuBasePtrs[eInstance], (uint8_t)u32FaultFlag);
	}
	return eStatus;
}

/**
 * @brief Get the fault flag of the FTU instance
 *
 * @param eInstance the selected FTU instance
 * @return uint32_t the fault flag of the selected Ftu instance
 */
uint32_t FTU_GetFaultFlag(const FTU_InstanceType eInstance)
{
	uint32_t u32FaultFlag = 0;
	if ((uint32_t)eInstance < FTU_INSTANCE_COUNT)
	{
		u32FaultFlag = FTU_HWA_ReadModuleFaultFlag(s_pFtuBasePtrs[eInstance]);
	}
	return u32FaultFlag;
}


/**
 * @brief Enable ftu channel DMA
 *
 * @param eInstance the selected FTU instance
 * @param u32DmaMask The dma channel mask.
 * @return FTU_StatusType whether the operation is successfully
 */

FTU_StatusType FTU_EnableChannelDma(const FTU_InstanceType eInstance, uint32_t u32DmaMask)
{
    FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
    uint32_t u32Loop;
    if ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
    {
        eStatus = FTU_STATUS_PARAM_INVALID;
    }
    else
    {
        for(u32Loop = 0u; u32Loop < FTU_CHANNEL_CONTROLS_COUNT; u32Loop++)
        {
            if (0u != (u32DmaMask & ((uint32_t)FTU_INTR_MASK_CHANNEL_0 << u32Loop)))
            {
                /* Enable Channel Interrupt */
                FTU_HWA_EnableChannelDma(s_pFtuBasePtrs[eInstance], (uint8_t)u32Loop);
            }
        }

    }
    return eStatus;
}

/**
 * @brief Initialize a Expect Edge Number Measurement channel
 *
 * @param eInstance the selected FTU instance
 * @param pExpectEdgeNumMeasure measurement configuration.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_ExpectEdgeNumberMeasureChannelInit(const FTU_InstanceType eInstance, FTU_ExpectEdgeNumberMeasureType *pExpectEdgeNumMeasure)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if (   ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
		|| (pExpectEdgeNumMeasure->u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
		|| (pExpectEdgeNumMeasure->u8Channel & 1u))
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		FTU_HWA_ConfigChannelMode(s_pFtuBasePtrs[eInstance], pExpectEdgeNumMeasure->u8Channel,
								  FTU_CHANNEL_MODE_INPUT);
		set_ftu_input_edge(s_pFtuBasePtrs[eInstance], pExpectEdgeNumMeasure->u8Channel,
						   pExpectEdgeNumMeasure->eEdgeMode);
		FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], pExpectEdgeNumMeasure->u8Channel + 1u,
									   FTU_CHANNEL_EDGE_NOT_USED);
		FTU_HWA_ConfigEdgeNumber(s_pFtuBasePtrs[eInstance], pExpectEdgeNumMeasure->u8Channel + 1,
								 pExpectEdgeNumMeasure->u8ExpectEdgeNumber);
		if (FTU_MEASURE_CONTINUOUS_MODE == pExpectEdgeNumMeasure->eContinuouslyMode)
		{
			FTU_HWA_EnableMeasureContinous(s_pFtuBasePtrs[eInstance], pExpectEdgeNumMeasure->u8Channel);
		}
		else
		{
			FTU_HWA_DisableMeasureContinous(s_pFtuBasePtrs[eInstance], pExpectEdgeNumMeasure->u8Channel);
		}
		/* Must put the ICM_MODE setting at the end, otherwise it will not be configured correctly. */
		FTU_HWA_ConfigInputCaptureMeasureMode(	s_pFtuBasePtrs[eInstance], pExpectEdgeNumMeasure->u8Channel,
												FTU_MEASURE_EXPECT_EDGE_NUMBER);
	}
	return eStatus;
}

/**
 * @brief Initialize a Edge Number Measurement channel
 *
 * @param eInstance the selected FTU instance
 * @param pEdgeNumMeasure measurement configuration.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_EdgeNumberMeasureChannelInit(const FTU_InstanceType eInstance, FTU_EdgeNumberMeasureType *pEdgeNumMeasure)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if (   ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
		|| (pEdgeNumMeasure->u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
		|| (pEdgeNumMeasure->u8Channel & 1u)
		|| (pEdgeNumMeasure->u32StartWindow >= pEdgeNumMeasure->u32EndWindow)
		|| (pEdgeNumMeasure->u32StartWindow > s_aFtuMaxCounter[eInstance]))
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		FTU_HWA_ConfigChannelMode(s_pFtuBasePtrs[eInstance], pEdgeNumMeasure->u8Channel,
								  FTU_CHANNEL_MODE_INPUT);
		set_ftu_input_edge(s_pFtuBasePtrs[eInstance], pEdgeNumMeasure->u8Channel, pEdgeNumMeasure->eEdgeMode);

		FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], pEdgeNumMeasure->u8Channel + 1u,
									   FTU_CHANNEL_EDGE_NOT_USED);
		FTU_HWA_ConfigInputCaptureMeasureMode(s_pFtuBasePtrs[eInstance], pEdgeNumMeasure->u8Channel,
											  FTU_MEASURE_ICENM_WIND_WRITE);
		FTU_HWA_SetChannelValue(s_pFtuBasePtrs[eInstance], pEdgeNumMeasure->u8Channel,
								pEdgeNumMeasure->u32StartWindow);
		FTU_HWA_SetChannelValue(s_pFtuBasePtrs[eInstance], pEdgeNumMeasure->u8Channel + 1u,
								pEdgeNumMeasure->u32EndWindow);
		FTU_HWA_ConfigInputCaptureMeasureMode(  s_pFtuBasePtrs[eInstance], pEdgeNumMeasure->u8Channel,
												FTU_MEASURE_EDGE_NUMBER);
		if (FTU_MEASURE_CONTINUOUS_MODE == pEdgeNumMeasure->eContinuouslyMode)
		{
			FTU_HWA_EnableMeasureContinous(s_pFtuBasePtrs[eInstance], pEdgeNumMeasure->u8Channel);
		}
		else
		{
			FTU_HWA_DisableMeasureContinous(s_pFtuBasePtrs[eInstance], pEdgeNumMeasure->u8Channel);
		}

	}
	return eStatus;
}

/**
 * @brief Get the expect edge number result of the channel
 *
 * @param eInstance the selected FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 * @param pResult point to the result buffer.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_GetExpectEdgeNumberResult(const FTU_InstanceType eInstance, uint8_t u8Channel, FTU_ExpectEdgeNumberResultType *pResult)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if (   ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
		|| (u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
		|| (u8Channel & 1u))
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		pResult->u32FirstEdgeTime = FTU_HWA_GetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel);
		pResult->u32LastEdgeTime = FTU_HWA_GetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel + 1);
	}
	return eStatus;
}

/**
 * @brief Get Edge number counter
 *
 * @param eInstance the selected FTU instance
 * @param u8Channel FTU channel number.
 * @return uint8_t Edge number counter
 */
uint8_t FTU_GetEdgeNumberCount(const FTU_InstanceType eInstance, uint8_t u8Channel)
{
	uint8_t u8Count = 0;
	if (   ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
		|| (u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
		|| (u8Channel & 1u))
	{

	}
	else
	{
		u8Count = FTU_HWA_GetEdgeNumberCount(s_pFtuBasePtrs[eInstance], u8Channel);
	}
	return u8Count;
}
/**
 * @brief Initialize a signal measure channel
 *
 * @param eInstance the selected FTU instance
 * @param pMeasure measurement configuration.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_SignalMeasureChannelInit(const FTU_InstanceType eInstance, FTU_SignalMeasureType *pMeasure)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if (   ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
		|| (pMeasure->u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
		|| (pMeasure->u8Channel & 1u))
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		FTU_HWA_ConfigInputCaptureMeasureMode(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel, FTU_MEASURE_MODE_OFF);
		FTU_HWA_ConfigInputCaptureMeasureMode(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel + 1u, FTU_MEASURE_MODE_OFF);
		FTU_HWA_DisableChannelEnhancedPhase(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel);
		FTU_HWA_DisableChannelPhase(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel);
		FTU_HWA_DisableChannelEnhancedPhase(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel + 1u);
		FTU_HWA_DisableChannelPhase(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel + 1u);
		FTU_HWA_DisableModuleCpwmMode(s_pFtuBasePtrs[eInstance]);

		FTU_HWA_ConfigChannelMode(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel, FTU_CHANNEL_MODE_INPUT);
		FTU_HWA_ConfigChannelMode(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel + 1u, FTU_CHANNEL_MODE_INPUT);
		if (FTU_SIGNAL_MEASURE_HIGH_TIME == pMeasure->eMeasureMode)
		{
			FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel, FTU_CHANNEL_EDGE_RISING);
			FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel + 1u, FTU_CHANNEL_EDGE_FALLING);
			FTU_HWA_ConfigInputCaptureMeasureMode(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel, FTU_MEASURE_MODE_DUTY_CYCLE);
			FTU_HWA_ConfigInputCaptureMeasureMode(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel + 1, FTU_MEASURE_MODE_DUTY_CYCLE);
			FTU_HWA_SetChannelPolarity(s_pFtuBasePtrs[eInstance], 1u << pMeasure->u8Channel);
		}
		else if (FTU_SIGNAL_MEASURE_LOW_TIME == pMeasure->eMeasureMode)
		{
			FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel, FTU_CHANNEL_EDGE_RISING);
			FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel + 1u, FTU_CHANNEL_EDGE_FALLING);
			FTU_HWA_ConfigInputCaptureMeasureMode(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel, FTU_MEASURE_MODE_DUTY_CYCLE);
			FTU_HWA_ConfigInputCaptureMeasureMode(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel + 1u, FTU_MEASURE_MODE_DUTY_CYCLE);
			FTU_HWA_ClearChannelPolarity(s_pFtuBasePtrs[eInstance], 1u << pMeasure->u8Channel);
		}
		else if (FTU_SIGNAL_MEASURE_PERIOD_RISING_EDGE == pMeasure->eMeasureMode)
		{
			FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel, FTU_CHANNEL_EDGE_RISING);
			FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel + 1u, FTU_CHANNEL_EDGE_NOT_USED);
			FTU_HWA_ConfigInputCaptureMeasureMode(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel, FTU_MEASURE_MODE_PERIOD);
			FTU_HWA_ConfigInputCaptureMeasureMode(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel + 1u, FTU_MEASURE_MODE_PERIOD);
		}
		else if (FTU_SIGNAL_MEASURE_PERIOD_FALLING_EDGE == pMeasure->eMeasureMode)
		{
			FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel, FTU_CHANNEL_EDGE_FALLING);
			FTU_HWA_ConfigChannelEdgeLevel(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel + 1u, FTU_CHANNEL_EDGE_NOT_USED);
			FTU_HWA_ConfigInputCaptureMeasureMode(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel, FTU_MEASURE_MODE_PERIOD);
			FTU_HWA_ConfigInputCaptureMeasureMode(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel + 1u, FTU_MEASURE_MODE_PERIOD);
		}

		if (FTU_MEASURE_CONTINUOUS_MODE == pMeasure->eContinuouslyMode)
		{
			FTU_HWA_EnableMeasureContinous(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel);
		}
		else
		{
			FTU_HWA_DisableMeasureContinous(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel);
		}

		if (FTU_MEASURE_START_IMMEDIATELY == pMeasure->eStartMode)
		{
			FTU_HWA_EnableMeasureStartImmd(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel);
		}
		else
		{
			FTU_HWA_DisableMeasureStartImmd(s_pFtuBasePtrs[eInstance], pMeasure->u8Channel);
		}
	}
	return eStatus;
}
/**
 * @brief Re-start measurement when in single mode
 *
 * @param eInstance the selected FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_SignalMeasureChannelSingle(const FTU_InstanceType eInstance, uint8_t u8Channel)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if (   ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
		|| (u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
		|| (u8Channel & 1u))
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		FTU_HWA_SingleMeasurement(s_pFtuBasePtrs[eInstance], u8Channel);
	}
	return eStatus;
}

/**
 * @brief Get the measurement result of the channel
 *
 * @param eInstance the selected FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 * @param pResult point to the result buffer.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_GetSignalMeasureResult(const FTU_InstanceType eInstance, uint8_t u8Channel, FTU_SignalMeasureValueType *pResult)
{
	FTU_StatusType eStatus = FTU_STATUS_SUCCESS;
	if (   ((uint32_t)eInstance >= FTU_INSTANCE_COUNT)
		|| (u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
		|| (u8Channel & 1u))
	{
		eStatus = FTU_STATUS_PARAM_INVALID;
	}
	else
	{
		FTU_MeasurementModeType eMeasureMode = FTU_HWA_GetMeasureMode(s_pFtuBasePtrs[eInstance], u8Channel);
		if (FTU_MEASURE_MODE_DUTY_CYCLE == eMeasureMode)
		{
			if (FTU_HWA_GetChannelPolarity(s_pFtuBasePtrs[eInstance], 1u << u8Channel))
			{
				pResult->u32StartTime = FTU_HWA_GetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel);
				pResult->u32EndTime = FTU_HWA_GetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel + 1);
			}
			else
			{
				pResult->u32StartTime = FTU_HWA_GetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel + 1);
				pResult->u32EndTime = FTU_HWA_GetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel);
			}
		}
		else if(FTU_MEASURE_MODE_PERIOD == eMeasureMode)
		{
			pResult->u32StartTime = FTU_HWA_GetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel + 1);
			pResult->u32EndTime = FTU_HWA_GetChannelValue(s_pFtuBasePtrs[eInstance], u8Channel);
		}
		else
		{
			pResult->u32StartTime = 0u;
			pResult->u32EndTime = 0u;
		}
	}
	return eStatus;
}



/**
 * @brief Interrupt IRQ handle of FTU instance
 *
 * @param eInstance the selected FTU instance
 */
void FTUn_IRQHandler(const FTU_InstanceType eInstance)
{
	uint32_t u32FaultFlag = 0u;
	uint8_t u8FaultEnable = FTU_HWA_ReadFaultIntrEnable(s_pFtuBasePtrs[eInstance]);
	uint8_t u8OverflowFlag = FTU_HWA_ReadModuleOverflowFlag(s_pFtuBasePtrs[eInstance]);
	uint8_t u8ReloadFlag = FTU_HWA_ReadReloadIntrEnable(s_pFtuBasePtrs[eInstance]);
	uint32_t u32Loop, u32ChannelIntrFlag = 0;
	uint16_t u16TimeStamp;
    
	u8OverflowFlag = FTU_HWA_ReadModuleOverflowIntrEnable(s_pFtuBasePtrs[eInstance]) & u8OverflowFlag;
	u8ReloadFlag = FTU_HWA_ReadModuleReloadFlag(s_pFtuBasePtrs[eInstance]) & u8ReloadFlag;
	if(0u != u8FaultEnable)
	{
		u32FaultFlag = FTU_HWA_ReadModuleFaultFlag(s_pFtuBasePtrs[eInstance]);
	}

	/* Clear interrupt flag*/
	if (0u != u8OverflowFlag)
	{
		FTU_HWA_ClearOverflowFlag(s_pFtuBasePtrs[eInstance]);
	}
	if (0u != u8ReloadFlag)
	{
		FTU_HWA_ClearReloadFlag(s_pFtuBasePtrs[eInstance]);
	}

	for (u32Loop = 0U; u32Loop < FTU_CHANNEL_CONTROLS_COUNT; u32Loop++)
	{
		if ((0u != FTU_HWA_ReadChannelInterruptFlag(s_pFtuBasePtrs[eInstance], (uint8_t)u32Loop)) &&
			(0u != FTU_HWA_ReadChannelInterruptEnableFlag(s_pFtuBasePtrs[eInstance], (uint8_t)u32Loop)))
		{
			FTU_HWA_ClearChannelInterruptFlag(s_pFtuBasePtrs[eInstance], (uint8_t)u32Loop);
			u32ChannelIntrFlag |= (uint8_t)(1u << u32Loop);
		}
	}

	/* call callback functions*/
	if ((0u != u8OverflowFlag) && (NULL != s_pOverflowCallback[eInstance]))
	{
		s_pOverflowCallback[eInstance]();
	}

	if ((0u != u8ReloadFlag) && (NULL != s_pReloadPointCallback[eInstance]))
	{
		s_pReloadPointCallback[eInstance]();
	}

	if ((0u != u32FaultFlag) && (NULL != s_pFaultCallback[eInstance]))
	{
		for (u32Loop = 0U; u32Loop < FTU_FAULT_COUNT; u32Loop++)
		{
			if (0u != (u32FaultFlag & ((uint32_t)1u << u32Loop)))
			{
				s_pFaultCallback[eInstance](u32Loop);
			}
		}
	}

	if ((0u != u32ChannelIntrFlag) && (NULL != s_pChannelCallback[eInstance]))
	{
		for (u32Loop = 0U; u32Loop < FTU_CHANNEL_CONTROLS_COUNT; u32Loop++)
		{
			if (0u != (u32ChannelIntrFlag & ((uint32_t)1u << u32Loop)))
			{
				u16TimeStamp = (uint16_t)FTU_HWA_GetChannelValue(s_pFtuBasePtrs[eInstance], (uint8_t)u32Loop);
				s_pChannelCallback[eInstance](u32Loop, u16TimeStamp);
			}
		}
	}
}
