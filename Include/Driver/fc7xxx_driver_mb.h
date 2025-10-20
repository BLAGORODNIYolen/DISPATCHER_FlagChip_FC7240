/**
 * @file fc7xxx_driver_mb.h
 * @author Flagchip070
 * @brief FC7xxx Mailbox driver type definition and API
 * @version 0.1.0
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2022-11-15    Flagchip070    N/A          First version for FC7300
********************************************************************************/

#ifndef _DRIVER_fc7xxx_driver_mb_H_
#define _DRIVER_fc7xxx_driver_mb_H_

#include "device_header.h"
#include "HwA_mb.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup fc7xxx_driver_mb
 * @{
 */


/**
 * @brief Mailbox channel bit flag of security information
 *
 */
#define MB_CHANNEL_STATUS_SECURE		2u

/**
 * @brief Mailbox channel bit flag of processing information
 *
 */
#define MB_CHANNEL_STATUS_PRIVILEGED	1u

/**
 * @name  Mailbox channel bit mask
 * @brief Bit of channel indicate channel number
 *
 * @{
 */
#define MB_CHANNEL_MASK_NONE			0u
#define MB_CHANNEL_MASK_ALL				0xFFFFu
#define MB_CHANNEL_MASK(ch)				((uint32_t)(1ul << (ch)))
/** @}*/

/**
 * @brief Mailbox has not initialized, the core index will be MB_NOT_INIT
 *
 */

#define MB_NOT_INIT					0xFFFFFFFFu
/**
 * @brief Mailbox operation return values
 *
 */
typedef enum {
    MB_STATUS_SUCCESS 			= 0u,	/*!< The Mailbox operation is success */
    MB_STATUS_FAILED,					/*!< The Mailbox operation is failed */
	MB_STATUS_PARAM_ERROR,				/*!< The Mailbox operation is failed because of parameter error*/
	MB_STATUS_ALREADY_INITED,			/*!< The Mailbox operation is failed because of
											 Mailbox has already initialized*/
	MB_STATUS_UNINIT,					/*!< The Mailbox operation is failed because of
											 Mailbox has not initialized*/
	MB_STATUS_LOCKED,					/*!< The Mailbox channel is locked */
	MB_STATUS_NO_REQUEST,				/*!< No valid requests */
} MB_StatusType;

/**
 * @brief Configuration of a Mailbox request
 *
 */
typedef struct
{
	uint8_t 	u8Channel;				/*!< The selected Mailbox channel */
	uint8_t 	u8RequestMask;			/*!< The mask for issuing requests */
	uint8_t		u8DoneMasterIndex;		/*!< The master ID of the core that generates a done event */
	uint8_t 	u8DoneMask;				/*!< The mask for the done events */
	uint8_t		u8AutoReleaseFlag;		/*!< Automatically clear the channel lock enable bit */
	uint8_t		u8Reserved[3];
	uint32_t	aData[2];				/*!< Sending data */
} MB_RequestType;

/**
 * @brief Configuration of a receiving request
 *
 */
typedef struct
{
	uint8_t		u8Channel;				/*!< The selected Mailbox channel */
	uint8_t		u8MasterCoreIndex;		/*!< Buffer to store the master core index */
	uint8_t		u8ChannelStatus;		/*!< Buffer to store the security information
											 and processing mode of the channel*/
	uint8_t		u8Reserved;
	uint32_t	aData[2];				/*!< Buffer to store the receiving data */
} MB_ReceiveType;

/**
 * @brief Configuration of the Mailbox
 *
 */
typedef struct
{
	uint32_t		u32EventMask;						/*!< Mask for the request events and done events */
	uint32_t		u32IntrMask;						/*!< Mask for enable the interrupts */
	void (*pRequestCallback)(MB_ReceiveType *pReceive);	/*!< Callback of the request events */
	void (*pDoneCallback)(uint32_t u32ChannelMask);		/*!< Callback of the done events */
} MB_InitType;

/**
 * @brief Initialize the Mailbox
 *
 * @param pInitConfig the configurations of the Mailbox
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_Init(const MB_InitType *pInitConfig);
/**
 * @brief De-initialize the Mailbox
 *
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_DeInit(void);
/**
 * @brief Attempt to acquire a Mailbox channel
 *
 * @param u32Channel the selected Mailbox channel
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_LockChannel(uint32_t u32Channel);
/**
 * @brief Release a Mailbox channel
 *
 * @param u32Channel the selected Mailbox channel
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_ReleaseChannel(uint32_t u32Channel);
/**
 * @brief Get the index of the core
 *
 * @return uint32_t index of the core
 */
uint32_t MB_GetCoreIndex(void);
/**
 * @brief Launching a Mailbox request
 *
 * @param pRequest Configuration of the request
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_SendRequest(MB_RequestType *pRequest);
/**
 * @brief Attempt to receive a request from the selected channel
 *
 * @param pReceive Configuration of the receiving request
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_ReceiveChannel(MB_ReceiveType *pReceive);
/**
 * @brief Software clears channel lock
 *
 * @param u32Channel the selected Mailbox channel
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_UnlockChannel(uint32_t u32Channel);
/**
 * @brief Polling the done event of all channels
 *
 * @param u32PollMask mask of the done event
 * @param pDoneMask buffer to store the done events
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_PollDone(uint32_t u32PollMask, uint32_t *pDoneMask);
/**
 * @brief Issue a done event to the selected channel
 *
 * @param u32Channel the selected Mailbox channel
 * @param u32DoneMask The mask for issuing done
 * @return MB_StatusType whether the operation is successfully
 */
MB_StatusType MB_DoneChannel(uint32_t u32Channel, uint32_t u32DoneMask);
/**
 * @brief Interrupt IRQ handle of Mailbox
 *
 */
void MB_IRQProcess(void);
/** @}*/ /* fc7xxx_driver_mb */
#if defined(__cplusplus)
}
#endif
#endif
