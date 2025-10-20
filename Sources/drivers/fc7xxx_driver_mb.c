/**
 * @file fc7xxx_driver_mb.c
 * @author Flagchip070
 * @brief FC7xxx Mailbox driver type definition and API
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

#include "fc7xxx_driver_mb.h"


/********* Local variable ************/
static uint32_t s_u32CoreIndex = MB_NOT_INIT;
static const uint8_t s_aMasterIdTab[MB_INT_CONFIG_COUNT] = {
    0u, 8u
};

static void (*s_pRequestCallback)(MB_ReceiveType *pReceive) 	= NULL;
static void (*s_pDoneCallback)(uint32_t u32ChannelMask) 		= NULL;

/******* Local Function Prototype *********/
static uint32_t core_id_2_index(uint32_t u32MasterId);
static uint8_t get_channel_status(uint32_t u32Channel);

/**
 * @brief Convert core master id to index
 *
 * @param u32MasterId Core master ID
 *
 */
static uint32_t core_id_2_index(uint32_t u32MasterId)
{
	uint32_t u32Index = 0;
	uint32_t u32Loop;
	for(u32Loop = 0; u32Loop < MB_INT_CONFIG_COUNT; u32Loop++)
	{
		if(s_aMasterIdTab[u32Loop] == u32MasterId)
		{
			u32Index = u32Loop;
			break;
		}
	}
	return u32Index;
}

/**
 * @brief Get the master security information and processing mode of the channel
 *
 * @param u32Channel the selected MB channel
 *
 */
static uint8_t get_channel_status(uint32_t u32Channel)
{
	uint8_t u8Status = 0;
	if(0u == MB_HWA_GetSecure(u32Channel))
	{
		u8Status |= MB_CHANNEL_STATUS_SECURE;
	}
	if(0u != MB_HWA_GetSupervisor(u32Channel))
	{
		u8Status |= MB_CHANNEL_STATUS_PRIVILEGED;
	}
	return u8Status;
}

/********* Global Functions ************/

/**
 * @brief Get the index of the core
 *
 * @return uint32_t index of the core
 */
uint32_t MB_GetCoreIndex(void)
{
	return s_u32CoreIndex;
}

/**
 * @brief Initialize the Mailbox
 *
 * @param pInitConfig the configurations of the Mailbox
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_Init(const MB_InitType *pInitConfig)
{
	MB_StatusType eStatus = MB_STATUS_SUCCESS;
	if(MB_NOT_INIT != s_u32CoreIndex)
	{
		eStatus = MB_STATUS_ALREADY_INITED;
	}
	else
	{
		/* Get Core Index */
#if defined(DEVICE_TYPE) && (DEVICE_TYPE == FC7XXXHSM)
		s_u32CoreIndex = HSM_MAILBOX_CORE_INDEX;
#else
		uint32_t u32CoreId;
		uint32_t u32Index;
		u32CoreId = (MCM->MICR & MCM_MICR_COREID_Msk) >> MCM_MICR_COREID_Pos;
		for(u32Index = 0; u32Index < MB_INT_CONFIG_COUNT; u32Index++)
		{
			if(u32CoreId == s_aMasterIdTab[u32Index])
			{
				s_u32CoreIndex = u32Index;
				break;
			}
		}
#endif
		if(MB_NOT_INIT != s_u32CoreIndex)
		{
			/*Registering callback functions*/
			s_pRequestCallback = pInitConfig->pRequestCallback;
			s_pDoneCallback = pInitConfig->pDoneCallback;
			/*Configure the event mask*/
			MB_HWA_ConfigFlagMask(s_u32CoreIndex, pInitConfig->u32EventMask);
			/*Enable event interrupts */
			MB_HWA_ConfigIntrEnable(s_u32CoreIndex, pInitConfig->u32IntrMask);
		}
		else
		{
			eStatus = MB_STATUS_FAILED;
		}
	}

	return eStatus;
}

/**
 * @brief De-initialize the Mailbox
 *
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_DeInit(void)
{
	MB_StatusType eStatus = MB_STATUS_UNINIT;
	if(MB_NOT_INIT != s_u32CoreIndex)
	{
		/*Disable all event interrupts and flag*/
		MB_HWA_ConfigFlagMask(s_u32CoreIndex, 0);
		MB_HWA_ConfigIntrEnable(s_u32CoreIndex, 0);
		s_u32CoreIndex = MB_NOT_INIT;
	}
	return eStatus;
}

/**
 * @brief Attempt to acquire a Mailbox channel
 *
 * @param u32Channel the selected Mailbox channel
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_LockChannel(uint32_t u32Channel)
{
	MB_StatusType eStatus = MB_STATUS_SUCCESS;
	uint32_t u32Lock;

	if(MB_NOT_INIT == s_u32CoreIndex)
	{
		eStatus = MB_STATUS_UNINIT;
	}
	else
	{
		if(u32Channel < MB_CHANNEL_CONFIG_COUNT)
		{
			/*Read SEMA to lock the selected channel*/
			u32Lock = MB_HWA_LockChannel(u32Channel);
			if(0u == u32Lock)
			{
				eStatus = MB_STATUS_LOCKED;
			}
		}
		else
		{
			eStatus = MB_STATUS_PARAM_ERROR;
		}
	}
	return eStatus;
}

/**
 * @brief Release a Mailbox channel
 *
 * @param u32Channel the selected Mailbox channel
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_ReleaseChannel(uint32_t u32Channel)
{
	MB_StatusType eStatus = MB_STATUS_SUCCESS;
	uint32_t u32MasterId;
	if(MB_NOT_INIT == s_u32CoreIndex)
	{
		eStatus = MB_STATUS_UNINIT;
	}
	else
	{
		if(u32Channel < MB_CHANNEL_CONFIG_COUNT)
		{
			/*Check the master core of the channel*/
			u32MasterId = MB_HWA_GetMasterID(u32Channel);
			if(u32MasterId == s_aMasterIdTab[s_u32CoreIndex])
			{
				/*Release the selected channel*/
				MB_HWA_ReleaseChannel(u32Channel);
			}
			else
			{
				eStatus = MB_STATUS_FAILED;
			}
		}
		else
		{
			eStatus = MB_STATUS_PARAM_ERROR;
		}
	}
	return eStatus;
}

/**
 * @brief Software clears channel lock
 *
 * @param u32Channel the selected Mailbox channel
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_UnlockChannel(uint32_t u32Channel)
{
	MB_StatusType eStatus = MB_STATUS_SUCCESS;
	if(MB_NOT_INIT == s_u32CoreIndex)
	{
		eStatus = MB_STATUS_UNINIT;
	}
	else
	{
		if(u32Channel < MB_CHANNEL_CONFIG_COUNT)
		{
			MB_HWA_UnlockChanne(u32Channel);
		}
		else
		{
			eStatus = MB_STATUS_PARAM_ERROR;
		}
	}
	return eStatus;
}

/**
 * @brief Launching a Mailbox request
 *
 * @param pRequest Configuration of the request
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_SendRequest(MB_RequestType *pRequest)
{
	MB_StatusType eStatus = MB_LockChannel(pRequest->u8Channel);
	if(MB_STATUS_SUCCESS == eStatus)
	{
		if(pRequest->u8DoneMasterIndex < MB_INT_CONFIG_COUNT)
		{
			MB_HWA_ConfigDoneMasterId(pRequest->u8Channel, s_aMasterIdTab[pRequest->u8DoneMasterIndex]);
			MB_HWA_ConfigDoneMask(pRequest->u8Channel, pRequest->u8DoneMask);
			MB_HWA_ConfigAutoUnlock(pRequest->u8Channel, pRequest->u8AutoReleaseFlag);
			MB_HWA_WriteData(pRequest->u8Channel, pRequest->aData);
			MB_HWA_ConfigRequest(pRequest->u8Channel, pRequest->u8RequestMask);
		}
		else
		{
			eStatus = MB_STATUS_PARAM_ERROR;
		}
	}
	return eStatus;
}

/**
 * @brief Attempt to receive a request from the selected channel
 *
 * @param pReceive Configuration of the receiving request
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_ReceiveChannel(MB_ReceiveType *pReceive)
{
	MB_StatusType eStatus = MB_STATUS_SUCCESS;
	uint32_t u32Flag;
	if(MB_NOT_INIT == s_u32CoreIndex)
	{
		eStatus = MB_STATUS_UNINIT;
	}
	else if(pReceive->u8Channel < MB_CHANNEL_CONFIG_COUNT)
	{
		u32Flag = MB_HWA_GetFlag(s_u32CoreIndex, MB_EVENT_REQ(pReceive->u8Channel));
		if(0u != u32Flag)
		{
			/* Clear events flag */
			MB_HWA_ClearFlag(s_u32CoreIndex, u32Flag);
			/* receiving data */
			MB_HWA_GetData(pReceive->u8Channel, pReceive->aData);
			/* get the security information and processing mode */
			pReceive->u8ChannelStatus = get_channel_status(pReceive->u8Channel);
			/*get the master core index of the request*/
			pReceive->u8MasterCoreIndex = (uint8_t)MB_HWA_GetMasterID(pReceive->u8Channel);
			pReceive->u8MasterCoreIndex = (uint8_t)core_id_2_index((uint32_t)pReceive->u8MasterCoreIndex);
		}
		else
		{
			eStatus = MB_STATUS_NO_REQUEST;
		}
	}
	else
	{
		eStatus = MB_STATUS_PARAM_ERROR;
	}
	return eStatus;
}

/**
 * @brief Issue a done event to the selected channel
 *
 * @param u32Channel the selected Mailbox channel
 * @param u32DoneMask The mask for issuing done
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_DoneChannel(uint32_t u32Channel, uint32_t u32DoneMask)
{
	MB_StatusType eStatus = MB_STATUS_SUCCESS;
	uint32_t u32DoneMasterId, u32DoneMaskAllow;
	if(MB_NOT_INIT == s_u32CoreIndex)
	{
		eStatus = MB_STATUS_UNINIT;
	}
	else if(u32Channel < MB_CHANNEL_CONFIG_COUNT)
	{
		/* Check the done master of the channel*/
		u32DoneMasterId = MB_HWA_GetDoneMasterId(u32Channel);
		if(u32DoneMasterId == s_aMasterIdTab[s_u32CoreIndex])
		{
			/* Check if the done mask is allowed */
			u32DoneMaskAllow = MB_HWA_GetDoneMask(u32Channel);
			if((u32DoneMaskAllow & u32DoneMask) == u32DoneMask)
			{
				/* issue a done event */
				MB_HWA_SetDone(u32Channel, u32DoneMask);
			}
			else
			{
				eStatus = MB_STATUS_FAILED;
			}
		}
		else
		{
			eStatus = MB_STATUS_FAILED;
		}
	}
	else
	{
		eStatus = MB_STATUS_PARAM_ERROR;
	}
	return eStatus;
}

/**
 * @brief Polling the done event of all channels
 *
 * @param u32PollMask mask of the done event
 * @param pDoneMask buffer to store the done events
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_PollDone(uint32_t u32PollMask, uint32_t *pDoneMask)
{
	MB_StatusType eStatus = MB_STATUS_SUCCESS;
	uint32_t u32Flag, u32Index;
	*pDoneMask = 0;

	if(MB_NOT_INIT == s_u32CoreIndex)
	{
		eStatus = MB_STATUS_UNINIT;
	}
	else if(0u != u32PollMask)
	{
		for(u32Index = 0; u32Index < MB_CHANNEL_CONFIG_COUNT; u32Index++)
		{
			if(0u != (u32PollMask & ((uint32_t)1u << u32Index)))
			{
				u32Flag = MB_HWA_GetFlag(s_u32CoreIndex, MB_EVENT_DONE(u32Index));
				if(0u != u32Flag)
				{
					/* Clear done flag */
					MB_HWA_ClearFlag(s_u32CoreIndex, u32Flag);
					/* store the done event */
					*pDoneMask |= (uint32_t)1u << u32Index;
				}
			}
		}
	}
	else
	{
		eStatus = MB_STATUS_PARAM_ERROR;
	}
	return eStatus;
}

/**
 * @brief Interrupt IRQ handle of Mailbox
 *
 */
void MB_IRQProcess(void)
{
	uint32_t u32FlagStat = MB_HWA_GetFlagStat(s_u32CoreIndex, MB_INTn_FLG_STAT_MASK);
	uint32_t u32Index, u32MasterCore, u32ChannelMask = 0;
	MB_ReceiveType tReceive;

	MB_HWA_ClearFlag(s_u32CoreIndex, u32FlagStat);
	for(u32Index = 0; u32Index < MB_CHANNEL_CONFIG_COUNT; u32Index++)
	{
		/* get the master core index of the channel*/
		u32MasterCore = MB_HWA_GetMasterID(u32Index);
		u32MasterCore = core_id_2_index(u32MasterCore);
		if(0u != (u32FlagStat & ((uint32_t)1u << u32Index)))
		{
			/* request event */
			if(NULL != s_pRequestCallback)
			{
				tReceive.u8Channel = (uint8_t)u32Index;
				tReceive.u8ChannelStatus = get_channel_status(u32Index);
				tReceive.u8MasterCoreIndex = (uint8_t)u32MasterCore;
				MB_HWA_GetData(u32Index, tReceive.aData);
				/* call the request callback*/
				s_pRequestCallback(&tReceive);
			}
		}
		if(0u != (u32FlagStat & ((uint32_t)1u << (u32Index + MB_INTn_FLG_STAT_FLG_DONE_INT_STAT_SHIFT))))
		{
			u32ChannelMask |= (uint32_t)1u << u32Index;
			/*done event*/
			if((0u == MB_HWA_GetAutoClear(u32Index, s_u32CoreIndex)) && (u32MasterCore == s_u32CoreIndex))
			{
				/* if channel is not automatically clear,
				 * and master core is self, release the channel */
				MB_HWA_ReleaseChannel(u32Index);
			}
		}
	}

	if((NULL != s_pDoneCallback) && (0u != u32ChannelMask))
	{
		s_pDoneCallback(u32ChannelMask);
	}
}
