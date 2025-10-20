/**
 * @file fc7xxx_driver_fcpit.h
 * @author Flagchip
 * @brief FC7xxx FCPIT driver type definition and API
 * @version 0.1.0
 * @date 2024-01-10
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2024-01-10    Flagchip0076  N/A          First version for FC7240
********************************************************************************/
#include "fc7xxx_driver_fcpit.h"
#include "interrupt_manager.h"


/********* Local Variables ************/
/** @brief FCPIT instance list */
static FCPIT_Type *s_pFcpitInstanceTable[FCPIT_INSTANCE_COUNT] = FCPIT_BASE_PTRS;

/** @brief Fcpit user defined interrupt function */
static FCPIT_InterruptCallBackType   s_aFcpitIntNotifyTab[FCPIT_INSTANCE_COUNT][MAX_FCPIT_CHANNEL_NUM] = {0};




/** @brief Fcpit interrupt entry */
void FCPIT0_IRQHandler(void);

/** @brief Fcpit common interrupt handle function */
static void Fcpit_CommonProcessInterrupt(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel);


/**
 * @brief Initialize Fcpit instance.
 * @param  eFcpit  instance
 * @param pInitStruct Fcpit initialization structure
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_Init(const FCPIT_InstanceType eFcpit, const FCPIT_InitType *const pInitStruct)
{
    FCPIT_Type *pFcpit;
    FCPIT_StatusType eRet = FCPIT_STATUS_SUCCESS;

    if ( ((uint32_t)eFcpit >= FCPIT_INSTANCE_COUNT) || (NULL == pInitStruct) )
    {
        eRet = FCPIT_STATUS_PARAM_INVALID;
    }
    else
    {
        pFcpit = s_pFcpitInstanceTable[eFcpit];
        /*Enable module clock*/
        FCPIT_HWA_EnableModule(pFcpit);
        if (pInitStruct->bDebugEn)
        {
            FCPIT_HWA_SetChannelRunOnDebug(pFcpit);
        }
        else
        {
            FCPIT_HWA_SetChannelStopOnDebug(pFcpit);
        }

        if (pInitStruct->bLowPowerModeEn)
        {
            FCPIT_HWA_SetChannelRunOnLpm(pFcpit);
        }
        else
        {
            FCPIT_HWA_SetChannelStopOnLpm(pFcpit);
        }
        /* w1c , clear channel interrupt flag*/
        FCPIT_HWA_ClearChannelsInterruptFlag(pFcpit, (uint32_t)1U << (uint32_t)pInitStruct->eFcpitChannel);

        FCPIT_HWA_ConfigChannel(pFcpit, pInitStruct->eFcpitChannel, (uint32_t)0U);
        FCPIT_HWA_ConfigChannelMode(pFcpit, pInitStruct->eFcpitChannel, pInitStruct->eMode);

        if (pInitStruct->bChainModeEn)
        {
        	if (pInitStruct->eFcpitChannel > FCPIT_CHANNEL_0)
        	{
        		FCPIT_HWA_EnableChannelChainMode(pFcpit, pInitStruct->eFcpitChannel);
        	}
        	else
        	{
        		/* channel 0 is the first channel can not be chained to last channel */
        		eRet = FCPIT_STATUS_PARAM_INVALID;
        	}
        }
        else
        {
        	/*Chain mode is not enabled, no operation */
        }

        FCPIT_HWA_SetChannelValue(pFcpit, pInitStruct->eFcpitChannel, pInitStruct->u32TimerValue);
    }

    return eRet;
}

/**
 * @brief Initialize Fcpit trigger configuration
 * @param  eFcpit  instance
 * @param pTrgStruct Fcpit trigger structure
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_InitTrigger(const FCPIT_InstanceType eFcpit, const FCPIT_TrggerType *const pTrgStruct)
{
    FCPIT_Type *pFcpit;
    FCPIT_StatusType eRet = FCPIT_STATUS_SUCCESS;

    if ( ((uint32_t)eFcpit >= FCPIT_INSTANCE_COUNT) || (NULL == pTrgStruct) )
    {
        eRet = FCPIT_STATUS_PARAM_INVALID;
    }
    else
    {
        pFcpit = s_pFcpitInstanceTable[eFcpit];
        if ( (uint32_t)0U == FCPIT_HWA_ReadModuleEnable(pFcpit) )
        {
            eRet = FCPIT_STATUS_FUNCTION_ERROR;
        }
        else
        {
            if (pTrgStruct->bStartOnTrigger)
            {
                FCPIT_HWA_SetChannelStartOnTrig(pFcpit, pTrgStruct->eFcpitChannel);
            }
            else
            {
                FCPIT_HWA_ClearChannelStartOnTrig(pFcpit, pTrgStruct->eFcpitChannel);
            }

            if (pTrgStruct->bStopOnInterrupt)
            {
                FCPIT_HWA_SetChannelStopOnInterrupt(pFcpit, pTrgStruct->eFcpitChannel);
            }
            else
            {
                FCPIT_HWA_ClearChannelStopOnInterrupt(pFcpit, pTrgStruct->eFcpitChannel);
            }

            if (pTrgStruct->bReloadOnTrigger)
            {
                FCPIT_HWA_SetChannelReloadOnTrig(pFcpit, pTrgStruct->eFcpitChannel);
            }
            else
            {
                FCPIT_HWA_ClearChannelReloadOnTrig(pFcpit, pTrgStruct->eFcpitChannel);
            }

            if (FCPIT_TRIGGER_EXTERNAL != pTrgStruct->eTriggerSel)
            {
                FCPIT_HWA_SetChannelTriggerSrc(pFcpit, pTrgStruct->eFcpitChannel);
                FCPIT_HWA_SelectChannelTrigger(pFcpit, pTrgStruct->eFcpitChannel, (uint8_t)pTrgStruct->eTriggerSel);
            }
            else
            {
                FCPIT_HWA_ClearChannelTriggerSrc(pFcpit, pTrgStruct->eFcpitChannel);
                FCPIT_HWA_SelectChannelTrigger(pFcpit, pTrgStruct->eFcpitChannel, (uint8_t)pTrgStruct->eFcpitChannel);
            }

        }

    }

    return eRet;
}

/**
 * @brief De-initialize Fcpit instance.
 * @param  eFcpit  instance
 */
FCPIT_StatusType FCPIT_Deinit(const FCPIT_InstanceType eFcpit)
{
    uint8_t u8Index;
    FCPIT_Type *pFcpit;
    FCPIT_StatusType eRet = FCPIT_STATUS_SUCCESS;

    if ((uint32_t)eFcpit >= FCPIT_INSTANCE_COUNT)
    {
        eRet = FCPIT_STATUS_PARAM_INVALID;
    }
    else
    {
        pFcpit = s_pFcpitInstanceTable[eFcpit];
        FCPIT_HWA_ConfigModule(pFcpit, (uint32_t)FCPIT_MCR_M_CEN_MASK);
        FCPIT_HWA_ClearChannelsInterruptFlag(pFcpit, (uint32_t)(FCPIT_MSR_TIF3_MASK | FCPIT_MSR_TIF2_MASK | FCPIT_MSR_TIF1_MASK |
                                                        FCPIT_MSR_TIF0_MASK));
        FCPIT_HWA_DisableChannelsInterrupt(pFcpit, (uint32_t)0U);
        for (u8Index = 0U; u8Index < MAX_FCPIT_CHANNEL_NUM; u8Index++)
        {
            FCPIT_HWA_ConfigChannel(pFcpit, (FCPIT_ChannelType)u8Index, (uint32_t)0U);
            FCPIT_HWA_SetChannelValue(pFcpit, (FCPIT_ChannelType)u8Index, (uint32_t)0U);
            s_aFcpitIntNotifyTab[eFcpit][u8Index] = NULL;
        }
        FCPIT_HWA_ConfigModule(pFcpit, (uint32_t)0U);
    }

    return eRet;
}

/**
 * @brief Initialize Fcpit interrupt functionality
 * @param  eFcpit  instance
 * @param  pIntStruct  Fcpit interrupt structure
 * @return Fcpit return type
 * @note this function will stop timer
 */
FCPIT_StatusType FCPIT_InitInterrupt(const FCPIT_InstanceType eFcpit, const FCPIT_IntType *const pIntStruct)
{
    FCPIT_Type *pFcpit;
    FCPIT_StatusType eRet = FCPIT_STATUS_SUCCESS;

    if ( ((uint8_t)eFcpit >= FCPIT_INSTANCE_COUNT) || (NULL == pIntStruct) )
    {
        eRet = FCPIT_STATUS_PARAM_INVALID;
    }
    else
    {
        pFcpit = s_pFcpitInstanceTable[eFcpit];
        if ((uint32_t)0U == (uint32_t)FCPIT_HWA_ReadModuleEnable(pFcpit))
        {
            eRet = FCPIT_STATUS_FUNCTION_ERROR;
        }
        else
        {
            FCPIT_HWA_DisableChannel(pFcpit, pIntStruct->eFcpitChannel);
            /* w1c , clear channel interrupt flag*/
            FCPIT_HWA_ClearChannelsInterruptFlag(pFcpit, (uint32_t)1U << (uint32_t)pIntStruct->eFcpitChannel);
            if (pIntStruct->bChannelIsrEn)
            {
                FCPIT_HWA_EnableChannelsInterrupt(pFcpit, (uint32_t)1U << (uint32_t)pIntStruct->eFcpitChannel);
                s_aFcpitIntNotifyTab[eFcpit][pIntStruct->eFcpitChannel] = pIntStruct->pIsrNotify;
            }
            else
            {
                FCPIT_HWA_DisableChannelsInterrupt(pFcpit, (uint32_t)1U << (uint32_t)pIntStruct->eFcpitChannel);
                s_aFcpitIntNotifyTab[eFcpit][pIntStruct->eFcpitChannel] = pIntStruct->pIsrNotify;
            }
        }
    }

    return eRet;
}

/**
 * @brief Enable Fcpit interrupt
 * @param  eFcpit  instance
 * @param  eChannel Fcpit channel
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_EnableInterrupt(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel)
{
    FCPIT_Type *pFcpit;
    FCPIT_StatusType eRet = FCPIT_STATUS_SUCCESS;

    if ( ((uint32_t)eFcpit >= FCPIT_INSTANCE_COUNT) || ((uint32_t)eChannel >= MAX_FCPIT_CHANNEL_NUM))
    {
        eRet = FCPIT_STATUS_PARAM_INVALID;
    }
    else
    {
        pFcpit = s_pFcpitInstanceTable[eFcpit];

        if ((uint32_t)0U == (uint32_t)FCPIT_HWA_ReadModuleEnable(pFcpit))
        {
            eRet = FCPIT_STATUS_FUNCTION_ERROR;
        }
        else
        {
            FCPIT_HWA_DisableChannel(pFcpit, eChannel);
            /* w1c , clear channel interrupt flag*/
            FCPIT_HWA_ClearChannelsInterruptFlag(pFcpit, (uint32_t)1U << (uint32_t)eChannel);
            FCPIT_HWA_EnableChannelsInterrupt(pFcpit, (uint32_t)1U << (uint32_t)eChannel);
            FCPIT_HWA_EnableChannel(pFcpit, eChannel);
        }

    }

    return eRet;
}

/**
 * @brief Disable Fcpit interrupt
 * @param  eFcpit  instance
 * @param eChannel Fcpit channel
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_DisableInterrupt(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel)
{
    FCPIT_Type *pFcpit;
    FCPIT_StatusType eRet = FCPIT_STATUS_SUCCESS;

    if ( ((uint32_t)eFcpit >= FCPIT_INSTANCE_COUNT) || ((uint32_t)eChannel >= MAX_FCPIT_CHANNEL_NUM) )
    {
        eRet = FCPIT_STATUS_PARAM_INVALID;
    }
    else
    {
        pFcpit = s_pFcpitInstanceTable[eFcpit];

        if ((uint32_t)0U == (uint32_t)FCPIT_HWA_ReadModuleEnable(pFcpit))
        {
            eRet = FCPIT_STATUS_FUNCTION_ERROR;
        }
        else
        {
            FCPIT_HWA_DisableChannel(pFcpit, eChannel);
            /* w1c , clear channel interrupt flag*/
            FCPIT_HWA_ClearChannelsInterruptFlag(pFcpit, (uint32_t)1U << (uint32_t)eChannel);
            FCPIT_HWA_DisableChannelsInterrupt(pFcpit, (uint32_t)1U << (uint32_t)eChannel);
            FCPIT_HWA_EnableChannel(pFcpit, eChannel);
        }
    }

    return eRet;
}

/**
 * @brief Fcpit start timer
  * @param  eFcpit  instance
 * @param eChannel Fcpit channel
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_Start(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel)
{
    FCPIT_Type *pFcpit;
    FCPIT_StatusType eRet = FCPIT_STATUS_SUCCESS;
    if ( ((uint32_t)eFcpit >= FCPIT_INSTANCE_COUNT) || ((uint32_t)eChannel >= MAX_FCPIT_CHANNEL_NUM) )
    {
        eRet = FCPIT_STATUS_PARAM_INVALID;
    }
    else
    {
        pFcpit = s_pFcpitInstanceTable[eFcpit];
        if ((uint32_t)0U == (uint32_t)FCPIT_HWA_ReadModuleEnable(pFcpit))
        {
            eRet = FCPIT_STATUS_FUNCTION_ERROR;
        }

        if (FCPIT_STATUS_SUCCESS == eRet)
        {
            FCPIT_HWA_EnableChannel(pFcpit, eChannel);
        }
    }

    return eRet;
}

/**
 * @brief Fcpit stop
 * @param  eFcpit  instance
 * @param eChannel Fcpit channel
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_Stop(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel)
{
    FCPIT_Type *pFcpit;
    FCPIT_StatusType eRet = FCPIT_STATUS_SUCCESS;

    if ( ((uint32_t)eFcpit >= FCPIT_INSTANCE_COUNT) || ((uint32_t)eChannel >= MAX_FCPIT_CHANNEL_NUM) )
    {
        eRet = FCPIT_STATUS_PARAM_INVALID;
    }
    else
    {
        pFcpit = s_pFcpitInstanceTable[eFcpit];
        if ((uint32_t)0U == (uint32_t)FCPIT_HWA_ReadModuleEnable(pFcpit))
        {
            eRet = FCPIT_STATUS_FUNCTION_ERROR;
        }
        else
        {
            FCPIT_HWA_DisableChannel(pFcpit, eChannel);
        }
    }

    return eRet;
}

/**
 * @brief Immediately update Fcpit channel value
 * @param  eFcpit  instance
 * @param eChannel Fcpit channel
 * @param u32ChannelValue in/Out value
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_ImmediateUpdateChannelValue(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel, const uint32_t u32ChannelValue)
{
    FCPIT_Type *pFcpit;
    FCPIT_StatusType eRet;

    pFcpit = s_pFcpitInstanceTable[eFcpit];

    eRet = FCPIT_Stop(eFcpit, eChannel);

    if (FCPIT_STATUS_SUCCESS == eRet)
    {
        FCPIT_HWA_SetChannelValue(pFcpit, eChannel, u32ChannelValue);
        eRet = FCPIT_Start(eFcpit, eChannel);
    }
    else
    {
        return eRet;
    }
    
    return eRet;
}

/**
 * @brief Update Fcpit channel value
 * @param  eFcpit  instance
 * @param eChannel Fcpit channel
 * @param u32ChannelValue in/Out value
 * @return Fcpit return type
 */
FCPIT_StatusType FCPIT_UpdateChannelValue(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel, const uint32_t u32ChannelValue)
{
    FCPIT_Type *pFcpit;
    FCPIT_StatusType eRet = FCPIT_STATUS_SUCCESS;

    if ( ((uint32_t)eFcpit >= FCPIT_INSTANCE_COUNT) || ((uint32_t)eChannel >= MAX_FCPIT_CHANNEL_NUM) )
    {
        eRet = FCPIT_STATUS_PARAM_INVALID;
    }
    else
    {
        pFcpit = s_pFcpitInstanceTable[eFcpit];
        if ((uint32_t)0U == (uint32_t)FCPIT_HWA_ReadModuleEnable(pFcpit))
        {
            eRet = FCPIT_STATUS_FUNCTION_ERROR;
        }

        if (FCPIT_STATUS_SUCCESS == eRet)
        {
            FCPIT_HWA_SetChannelValue(pFcpit, eChannel, u32ChannelValue);
        }
    }

    return eRet;
}

/**
 * @brief read Fcpit channel time stamps.
 * #param eFcpit Fcpit instance
 * @param eChannel Fcpit channel
 * @param *u32timeStampValue  value
 * @return Fcpit return type
 */

FCPIT_StatusType FCPIT_ReadTimstamp(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel,uint32_t *u32timeStampValue)
{
	FCPIT_Type *pFcpit;
	FCPIT_StatusType eRet = FCPIT_STATUS_SUCCESS;
	if ( ((uint32_t)eFcpit >= FCPIT_INSTANCE_COUNT) || ((uint32_t)eChannel >= MAX_FCPIT_CHANNEL_NUM) )
	{
		eRet = FCPIT_STATUS_PARAM_INVALID;
	}
	 pFcpit = s_pFcpitInstanceTable[eFcpit];

	if((uint32_t)0x3u != FCPIT_HWA_ReadChannelMode(pFcpit,eChannel))
	{
		eRet = FCPIT_STATUS_PARAM_INVALID;
	}
	else
	{

		*u32timeStampValue = FCPIT_HWA_ReadChannelValue(pFcpit,eChannel);
	}
	return eRet;
}



/**
 * @brief Fcpit common interrupt handle function
 * @param  eFcpit  instance
 * @param eChannel Fcpit interrupt channel
 */
static void Fcpit_CommonProcessInterrupt(const FCPIT_InstanceType eFcpit, const FCPIT_ChannelType eChannel)
{
    if (NULL != s_aFcpitIntNotifyTab[eFcpit][eChannel])
    {
        s_aFcpitIntNotifyTab[eFcpit][eChannel]();
    }
}

/**
 * @brief Fcpit_0 interrupt handler entry
 *
 */
void FCPIT0_IRQHandler(void)
{
    uint32_t u32TifValue = FCPIT_HWA_ReadEnableInterruptFlag(FCPIT) & FCPIT_HWA_ReadInterruptFlag(FCPIT);

    if ((u32TifValue & FCPIT_MSR_TIF0_MASK) != 0u)
    {
        Fcpit_CommonProcessInterrupt(FCPIT_0, FCPIT_CHANNEL_0);
        FCPIT_HWA_ClearChannelsInterruptFlag(FCPIT, (uint32_t)FCPIT_MSR_TIF0_MASK);
    }
    if ((u32TifValue & FCPIT_MSR_TIF1_MASK) != 0u)
    {
        Fcpit_CommonProcessInterrupt(FCPIT_0, FCPIT_CHANNEL_1);
        FCPIT_HWA_ClearChannelsInterruptFlag(FCPIT, (uint32_t)FCPIT_MSR_TIF1_MASK);
    }
    if ((u32TifValue & FCPIT_MSR_TIF2_MASK) != 0u)
    {
        Fcpit_CommonProcessInterrupt(FCPIT_0, FCPIT_CHANNEL_2);
        FCPIT_HWA_ClearChannelsInterruptFlag(FCPIT, (uint32_t)FCPIT_MSR_TIF2_MASK);
    }
    if ((u32TifValue & FCPIT_MSR_TIF3_MASK) != 0u)
    {
        Fcpit_CommonProcessInterrupt(FCPIT_0, FCPIT_CHANNEL_3);
        FCPIT_HWA_ClearChannelsInterruptFlag(FCPIT, (uint32_t)FCPIT_MSR_TIF3_MASK);
    }

}

