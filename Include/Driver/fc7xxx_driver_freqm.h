/**
 * @file fc7xxx_driver_freqm.h
 * @author Flagchip
 * @brief FC7xxx FREQM driver type definition and API
 * @version 0.1.0
 * @date 2024-01-14
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2024-01-14    qxw0100       N/A          First version for FC7240
********************************************************************************/

#ifndef _DRIVER_FC4XXX_DRIVER_FREQM_H_
#define _DRIVER_FC4XXX_DRIVER_FREQM_H_

#include "HwA_freqm.h"
#include "stddef.h"
#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief FREQM operation return values
 *
 */
typedef enum
{
    FREQM_STATUS_SUCCESS 				= 0U,	/*!< The FREQM operation is succeed */
    FREQM_STATUS_PARAM_INVALID,				/*!< The FREQM operation is failed because of parameter error */
	FREQM_STATUS_TIMEOUT,                   /*!< The FREQM operation is failed because of time out */
} FREQM_StatusType;

/**
 * @brief The FREQM measure counter start interrupt callback function prototype
 *
 */
typedef void (*FREQM_MesCntStartCallBackType)(void);

/**
 * @brief The FREQM measure counter stop interrupt callback function prototype
 *
 */
typedef void (*FREQM_MesCntStopCallBackType)(void);

/**
 * @brief The FREQM reference counter stop interrupt callback function prototype
 *
 */
typedef void (*FREQM_RefCntStopCallBackType)(void);
/**
 * @brief The FREQM fault interrupt callback function prototype
 *
 */
typedef void (*FREQM_FaultCallBackType)(void);


/**
 * @brief The configuration option for the FREQM interrupt
 *
 */
typedef struct
{
    bool                            bIntEnable;				/*!< interrupt enable mask */
    FREQM_MesCntStartCallBackType	pMesCntStartCallback;	/*!< Measure Counter Start interrupt callback */
    FREQM_MesCntStopCallBackType	pMesCntStopCallback;	/*!< Measure Counter Stop interrupt callback */
    FREQM_RefCntStopCallBackType 	pRefCntStopCallback;    /*!< Reference Counter Stop interrupt callback */
	FREQM_FaultCallBackType         pFaultCallback;         /*!< Fault interrupt callback */
} FREQM_InterruptType;

/**
 * @brief The basic configuration option for the FREQM peripheral
 *
 */
typedef struct
{
	uint32_t              u32MesLen;
	uint32_t              u32RefTo;
    FREQM_MesClkSelType   eClkSel;                /*!< Ftu clock source */
    uint8_t				  u8PredivVal;			/*!< Frequency of the Reload Opportunities. Range is 0-31, */
} FREQM_InitType;


/**
 * @brief Initialize FREQM configuration
 *
 * @param pInitStruct the basic configurations of the FREQM
 * @return FREQM_StatusType whether the operation is successfully
 */
FREQM_StatusType FREQM_Init(const FREQM_InitType *const pInitStruct);

/**
 * @brief De-initialize the FREQM 
 *
 * @param eInstance the selected FREQM 
 * @return FREQM_StatusType whether the operation is successfully
 */
FREQM_StatusType FREQM_DeInit(void);

/**
 * @brief Start the FREQM
 *
 * @return FREQM_StatusType whether the operation is successfully
 */
FREQM_StatusType FREQM_ClearStatus(void);

/**
 * @brief Start the reference/measure counter
 *
 */
void FREQM_StartMeasureCnt(void);

/**
 * @brief Get saved reference counter value
 *
 * @return uint32_t saved reference counter value
 */
uint32_t FREQM_GetRefCntSave(void);

/**
 * @brief Interrupt IRQ handle of FREQM
 *
 */
void FREQM_IRQHandler(void);
/**
 * @brief FREQM initialize interrupt function
 *
 * @param pIntStruct FREQM interrupt structure
 * @return FREQM_StatusType whether the operation is successfully
 */
FREQM_StatusType FREQM_InterruptInit(const FREQM_InterruptType *const pIntrStruct);

/** @}*/ /* fc7xxx_driver_freqm */
#if defined(__cplusplus)
}
#endif
#endif
