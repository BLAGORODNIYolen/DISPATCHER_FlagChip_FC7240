/**
 * @file HwA_mb.h
 * @author Flagchip070
 * @brief FC7xxx Mailbox hardware access layer
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

#ifndef _HWA_MAILBOX_H_
#define _HWA_MAILBOX_H_
#include "device_header.h"

/**
 * @brief The definition of mask all events
 *
 */
#define MB_EVENT_NONE			0u
/**
 * @brief The definition of receiving all events
 *
 */
#define MB_EVENT_ALL			0xFFFFFFFFu
/**
 * @brief The definition of receiving all request events
 *
 */
#define MB_EVENT_ALL_REQ		0x0000FFFFu
/**
 * @brief The definition of receiving all done events
 *
 */
#define MB_EVENT_ALL_DONE		0xFFFF0000u
/**
 * @brief The definition of request events on ch
 *
 */
#define MB_EVENT_REQ(ch)		(uint32_t)((uint32_t)1u << (ch))
/**
 * @brief The definition of done events on ch
 *
 */
#define MB_EVENT_DONE(ch)		(uint32_t)((uint32_t)1u << ((ch) + 16u))
/**
 * @brief The definition of issue to no core
 *
 */
#define MB_CORE_MASK_CORE_NONE	0u
/**
 * @brief The definition of issue to core 0
 *
 */
#define MB_CORE_MASK_CORE_0		1u
/**
 * @brief The definition of issue to HSM
 *
 */
#define MB_CORE_MASK_HSM		2u
/**
 * @brief The definition of issue to all cores
 *
 */
#define MB_CORE_MASK_ALL		0x3u
/**
 * @brief The definition of issue to core
 *
 */
#define MB_CORE_MASK(core)		(uint32_t)(1ul << (core))

enum
{
	MB_CORE_INDEX_CORE_0	= 0,	/*!< Core index of core 0 */
	MB_CORE_INDEX_HSM,				/*!< Core index of HSM */
};

/**
 * @brief Configure receive events of mailbox interrupt channel
 *
 * @param u32CoreIndex the index of the core
 * @param u32Mask configuration for receiving events
 */
LOCAL_INLINE void MB_HWA_ConfigFlagMask(uint32_t u32CoreIndex, uint32_t u32Mask)
{
	MB->INTR[u32CoreIndex].MB_INTn_CTRL &= ~MB_INTn_CTRL_FLG_MASK_LOCK_MASK;
	MB->INTR[u32CoreIndex].MB_INTn_FLG_MASK = u32Mask;
	MB->INTR[u32CoreIndex].MB_INTn_CTRL |= MB_INTn_CTRL_FLG_MASK_LOCK_MASK;
}

/**
 * @brief Enable receive events of mailbox interrupt channel
 *
 * @param u32CoreIndex the index of the core
 * @param u32Mask indicates the events to be enabled
 */
LOCAL_INLINE void MB_HWA_EnableEvent(uint32_t u32CoreIndex, uint32_t u32Mask)
{
	MB->INTR[u32CoreIndex].MB_INTn_CTRL &= ~MB_INTn_CTRL_FLG_MASK_LOCK_MASK;
	MB->INTR[u32CoreIndex].MB_INTn_FLG_MASK |= u32Mask;
	MB->INTR[u32CoreIndex].MB_INTn_CTRL |= MB_INTn_CTRL_FLG_MASK_LOCK_MASK;
}

/**
 * @brief Disable receive events of mailbox interrupt channel
 *
 * @param u32CoreIndex the index of the core
 * @param u32Mask indicates the events to be enabled
 */
LOCAL_INLINE void MB_HWA_DisableEvent(uint32_t u32CoreIndex, uint32_t u32Mask)
{
	MB->INTR[u32CoreIndex].MB_INTn_CTRL &= ~MB_INTn_CTRL_FLG_MASK_LOCK_MASK;
	MB->INTR[u32CoreIndex].MB_INTn_FLG_MASK &= ~u32Mask;
	MB->INTR[u32CoreIndex].MB_INTn_CTRL |= MB_INTn_CTRL_FLG_MASK_LOCK_MASK;
}

/**
 * @brief Configure the interrupt of mailbox interrupt channel
 *
 * @param u32CoreIndex the index of the core
 * @param u32Mask configuration for interrupts
 */
LOCAL_INLINE void MB_HWA_ConfigIntrEnable(uint32_t u32CoreIndex, uint32_t u32Mask)
{
	MB->INTR[u32CoreIndex].MB_INTn_CTRL &= ~MB_INTn_CTRL_INTEN_LOCK_MASK;
	MB->INTR[u32CoreIndex].MB_INTn_INTEN = u32Mask;
	MB->INTR[u32CoreIndex].MB_INTn_CTRL |= MB_INTn_CTRL_INTEN_LOCK_MASK;
}

/**
 * @brief Enable the interrupt of mailbox interrupt channel
 *
 * @param u32CoreIndex the index of the core
 * @param u32Mask indicates the interrupts to be enabled
 */
LOCAL_INLINE void MB_HWA_EnableIntr(uint32_t u32CoreIndex, uint32_t u32Mask)
{
	MB->INTR[u32CoreIndex].MB_INTn_CTRL &= ~MB_INTn_CTRL_INTEN_LOCK_MASK;
	MB->INTR[u32CoreIndex].MB_INTn_INTEN |= u32Mask;
	MB->INTR[u32CoreIndex].MB_INTn_CTRL |= MB_INTn_CTRL_INTEN_LOCK_MASK;
}

/**
 * @brief Disable the interrupt of mailbox interrupt channel
 *
 * @param u32CoreIndex the index of the core
 * @param u32Mask indicates the interrupts to be disabled
 */
LOCAL_INLINE void MB_HWA_DisableIntr(uint32_t u32CoreIndex, uint32_t u32Mask)
{
	MB->INTR[u32CoreIndex].MB_INTn_CTRL &= ~MB_INTn_CTRL_INTEN_LOCK_MASK;
	MB->INTR[u32CoreIndex].MB_INTn_INTEN &= ~u32Mask;
	MB->INTR[u32CoreIndex].MB_INTn_CTRL |= MB_INTn_CTRL_INTEN_LOCK_MASK;
}

/**
 * @brief Clear the flag of mailbox interrupt channel
 *
 * @param u32CoreIndex the index of the core
 * @param u32Mask indicates the flags to be cleared
 */
LOCAL_INLINE void MB_HWA_ClearFlag(uint32_t u32CoreIndex, uint32_t u32Mask)
{
	MB->INTR[u32CoreIndex].MB_INTn_CTRL &= ~MB_INTn_CTRL_FLG_LOCK_MASK;
	MB->INTR[u32CoreIndex].MB_INTn_FLG |= u32Mask;
	MB->INTR[u32CoreIndex].MB_INTn_CTRL |= MB_INTn_CTRL_FLG_LOCK_MASK;
}

/**
 * @brief Get the flag masks of mailbox interrupt channel
 *
 * @param u32CoreIndex the index of the core
 * @param u32Mask the mask to get
 * @return the flag masks of the mailbox interrupt channel
 */
LOCAL_INLINE uint32_t MB_HWA_GetFlagMask(uint32_t u32CoreIndex, uint32_t u32Mask)
{
	uint32_t u32RegValue = MB->INTR[u32CoreIndex].MB_INTn_FLG_MASK & u32Mask;
	return u32RegValue;
}

/**
 * @brief Get the flags of mailbox interrupt channel
 *
 * @param u32CoreIndex the index of the core
 * @param u32Mask the mask to get
 * @return the flags of the mailbox interrupt channel
 */
LOCAL_INLINE uint32_t MB_HWA_GetFlag(uint32_t u32CoreIndex, uint32_t u32Mask)
{
	uint32_t u32RegValue = MB->INTR[u32CoreIndex].MB_INTn_FLG & u32Mask;
	return u32RegValue;
}

/**
 * @brief Get the result of flag & inten of mailbox interrupt channel
 *
 * @param u32CoreIndex the index of the core
 * @param u32Mask the mask to get
 * @return the result of flag & inten of the mailbox interrupt channel
 */
LOCAL_INLINE uint32_t MB_HWA_GetFlagStat(uint32_t u32CoreIndex, uint32_t u32Mask)
{
	uint32_t u32RegValue = MB->INTR[u32CoreIndex].MB_INTn_FLG_STAT & u32Mask;
	return u32RegValue;
}

/**
 * @brief Get the master ID of the currently obtained channel
 *
 * @param u32Channel the index of the channel
 * @return the master ID
 */
LOCAL_INLINE uint32_t MB_HWA_GetMasterID(uint32_t u32Channel)
{
	uint32_t u32MasterId = MB->CHANNEL[u32Channel].MB_CCn_STAT;
	u32MasterId = (u32MasterId & MB_CCn_STAT_CURRENT_LOCK_MASTER_ID_MASK) >> MB_CCn_STAT_CURRENT_LOCK_MASTER_ID_SHIFT;
	return u32MasterId;
}

/**
 * @brief Get the security information of the currently obtained channel
 *
 * @param u32Channel the index of the channel
 * @return the security information
 */
LOCAL_INLINE uint32_t MB_HWA_GetSecure(uint32_t u32Channel)
{
	uint32_t u32Secure = MB->CHANNEL[u32Channel].MB_CCn_STAT & MB_CCn_STAT_CURRENT_LOCK_MASTER_SEC_MASK;
	return u32Secure;
}

/**
 * @brief Get the processing mode of the currently obtained channel
 *
 * @param u32Channel the index of the channel
 * @return the processing mode
 */
LOCAL_INLINE uint32_t MB_HWA_GetSupervisor(uint32_t u32Channel)
{
	uint32_t u32Supervisor = MB->CHANNEL[u32Channel].MB_CCn_STAT & MB_CCn_STAT_CURRENT_LOCK_MASTER_SUPERVISOR_MASK;
	return u32Supervisor;
}

/**
 * @brief Send data to the mailbox channel
 *
 * @param u32Channel the index of the channel
 * @param pData the buffer to be written
 */
LOCAL_INLINE void MB_HWA_WriteData(uint32_t u32Channel, uint32_t *pData)
{
	MB->CHANNEL[u32Channel].MB_CCn_DATA0 = pData[0];
	MB->CHANNEL[u32Channel].MB_CCn_DATA1 = pData[1];
}

/**
 * @brief Receive data from the mailbox channel
 *
 * @param u32Channel the index of the channel
 * @param pData the buffer to receive data
 */
LOCAL_INLINE void MB_HWA_GetData(uint32_t u32Channel, uint32_t *pData)
{
	pData[0] = MB->CHANNEL[u32Channel].MB_CCn_DATA0;
	pData[1] = MB->CHANNEL[u32Channel].MB_CCn_DATA1;
}

/**
 * @brief Get the automatically clear status of the mailbox channel
 *
 * @param u32Channel the index of the channel
 * @param u32CoreIndex the index of the core
 * @return automatically clear the channel lock enable bit
 */
LOCAL_INLINE uint32_t MB_HWA_GetAutoClear(uint32_t u32Channel, uint32_t u32CoreIndex)
{
	uint32_t u32SemaUnlock = MB->CHANNEL[u32Channel].MB_CCn_SEMA_UNLK;
	u32SemaUnlock &= (uint32_t)1u << (u32CoreIndex + MB_CCn_SEMA_UNLK_AUTO_CLEAR_EN_SHIFT);
	return u32SemaUnlock;
}

/**
 * @brief Release the mailbox channel
 *
 * @param u32Channel the index of the channel
 */
LOCAL_INLINE void MB_HWA_ReleaseChannel(uint32_t u32Channel)
{
	MB->CHANNEL[u32Channel].MB_CCn_DONE = MB_MASTER_DONE_CODE;
}

/**
 * @brief Software clears channel lock
 *
 * @param u32Channel the index of the channel
 */
LOCAL_INLINE void MB_HWA_UnlockChanne(uint32_t u32Channel)
{
	MB->CHANNEL[u32Channel].MB_CCn_CLR = MB_FORCE_UNLOCK_CODE;
}

/**
 * @brief Issue a done event
 *
 * @param u32Channel the index of the channel
 * @param u32DoneMask the cores to issue
 */
LOCAL_INLINE void MB_HWA_SetDone(uint32_t u32Channel, uint32_t u32DoneMask)
{
	MB->CHANNEL[u32Channel].MB_CCn_DONE |= (u32DoneMask & MB_CCn_DONE_DONE_MASK);
}

/**
 * @brief Try to lock a channel
 *
 * @param u32Channel the index of the channel
 * @return Channel Lock Acquisition
 */
LOCAL_INLINE uint32_t MB_HWA_LockChannel(uint32_t u32Channel)
{
	uint32_t u32RegValue = MB->CHANNEL[u32Channel].MB_CCn_SEMA;
	return u32RegValue & MB_CCn_SEMA_LOCK_MASK;
}

/**
 * @brief Configure the master ID of the core that generates a done event
 *
 * @param u32Channel the index of the channel
 * @param u32MasterId master ID
 */
LOCAL_INLINE void MB_HWA_ConfigDoneMasterId(uint32_t u32Channel, uint32_t u32MasterId)
{
	MB->CHANNEL[u32Channel].MB_CCn_DONE_MASK &= ~MB_CCn_DONE_MASK_DONE_MASTER_ID_MASK;
	MB->CHANNEL[u32Channel].MB_CCn_DONE_MASK |= MB_CCn_DONE_MASK_DONE_MASTER_ID(u32MasterId);
}

/**
 * @brief Get the master ID of the core that generates a done event
 *
 * @param u32Channel the index of the channel
 * @return the master ID
 */
LOCAL_INLINE uint32_t MB_HWA_GetDoneMasterId(uint32_t u32Channel)
{
	uint32_t u32MasterId =
			(MB->CHANNEL[u32Channel].MB_CCn_DONE_MASK & MB_CCn_DONE_MASK_DONE_MASTER_ID_MASK)
			>> MB_CCn_DONE_MASK_DONE_MASTER_ID_SHIFT;
	return u32MasterId;

}

/**
 * @brief Configure the mask of the done events
 *
 * @param u32Channel the index of the channel
 * @param u32DoneMask the cores to issue
 */
LOCAL_INLINE void MB_HWA_ConfigDoneMask(uint32_t u32Channel, uint32_t u32DoneMask)
{
	MB->CHANNEL[u32Channel].MB_CCn_DONE_MASK &= ~MB_CCn_DONE_DONE_MASK;
	MB->CHANNEL[u32Channel].MB_CCn_DONE_MASK |= (u32DoneMask << MB_CCn_DONE_DONE_SHIFT) & MB_CCn_DONE_DONE_MASK;
}

/**
 * @brief Get the mask of the done events
 *
 * @param u32Channel the index of the channel
 * @return the mask of the done events
 */
LOCAL_INLINE uint32_t MB_HWA_GetDoneMask(uint32_t u32Channel)
{
	uint32_t u32Mask = MB->CHANNEL[u32Channel].MB_CCn_DONE_MASK & MB_CCn_DONE_DONE_MASK;
	return u32Mask;
}

/**
 * @brief Configure the automatically clear of the lock enable bit
 *
 * @param u32Channel the index of the channel
 * @param u32AutoUnlockMask the automatically clear of the lock enable bit
 */
LOCAL_INLINE void MB_HWA_ConfigAutoUnlock(uint32_t u32Channel, uint32_t u32AutoUnlockMask)
{
	MB->CHANNEL[u32Channel].MB_CCn_SEMA_UNLK = MB_CCn_SEMA_UNLK_AUTO_CLEAR_EN(u32AutoUnlockMask);
}

/**
 * @brief Issue request events
 *
 * @param u32Channel the index of the channel
 * @param u32RequestMask the cores to issue
 */
LOCAL_INLINE void MB_HWA_ConfigRequest(uint32_t u32Channel, uint32_t u32RequestMask)
{
	MB->CHANNEL[u32Channel].MB_CCn_REQUEST = MB_CCn_REQUEST_REQ(u32RequestMask);
}

#endif

