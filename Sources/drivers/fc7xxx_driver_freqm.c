/**
 * @file fc7xxx_driver_freqm.c
 * @author Flagchip
 * @brief FC7xxx FREQM driver type definition and API
 * @version 0.1.0
 * @date 2024-01-14
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-14    qxw0100       N/A          First version for FC7240
   ******************************************************************************** */

#include "fc7xxx_driver_freqm.h"
#include "fc7xxx_driver_pcc.h"
#include "interrupt_manager.h"

/********* Local variable ************/
static FREQM_Type * const pFreqmPtrs = FREQM;

static FREQM_MesCntStartCallBackType	s_pMesCntStartCallback = NULL;
static FREQM_MesCntStopCallBackType		s_pMesCntStopCallback = NULL;
static FREQM_RefCntStopCallBackType 	s_pRefCntStopCallback = NULL;
static FREQM_FaultCallBackType          s_pFaultCallback = NULL;


/********* Global Functions ************/
/**
 * @brief Initialize FREQM configuration
 *
 * @param pInitStruct the basic configurations of the FREQM
 * @return FREQM_StatusType whether the operation is successfully
 */
FREQM_StatusType FREQM_Init(const FREQM_InitType *const pInitStruct)
{
    FREQM_StatusType eRet = FREQM_STATUS_SUCCESS;
    if (NULL == pInitStruct)
    {
        eRet = FREQM_STATUS_PARAM_INVALID;
    }
    else
    {
		/* Configure the clock divider value */
		FREQM_HWA_MesClk_PreDiv(pFreqmPtrs,pInitStruct->u8PredivVal);
		/* Select the clock source to be measured */
		FREQM_HWA_MesClkSel(pFreqmPtrs,pInitStruct->eClkSel);
		/* Set and clear the S/W reset */
		PCC_GenPeripheralReset(PCC_CLK_FREQM);
		/* Configure the measure counter targer value */
		FREQM_HWA_SetMesLength(pFreqmPtrs,pInitStruct->u32MesLen);
		/* Configure the reference counter target value */
		FREQM_HWA_SetRefTimeout(pFreqmPtrs,pInitStruct->u32RefTo);		
    }
    return eRet;
}

/**
 * @brief De-initialize the FREQM 
 *
 * @param eInstance the selected FREQM 
 * @return FREQM_StatusType whether the operation is successfully
 */
FREQM_StatusType FREQM_DeInit()
{
	FREQM_StatusType eStatus = FREQM_STATUS_SUCCESS;
	/* Set register to reset value */	
	FREQM_HWA_MesClk_PreDiv(pFreqmPtrs,0U);
	FREQM_HWA_MesClkSel(pFreqmPtrs,(FREQM_MesClkSelType)0);
	FREQM_HWA_SetMesLength(pFreqmPtrs,0xFFFFFFFFU);
	FREQM_HWA_SetRefTimeout(pFreqmPtrs,0xFFFFFFFFU);
	
	FREQM_HWA_DisableCntEventInterrupt(pFreqmPtrs);
	s_pMesCntStartCallback = NULL;
	s_pMesCntStopCallback = NULL;
	s_pRefCntStopCallback = NULL;
	s_pFaultCallback = NULL;
	
	return eStatus;
}

/**
 * @brief Clear all FREQM status
 *
 * @return FREQM_StatusType whether the operation is successfully
 */
FREQM_StatusType FREQM_ClearStatus()
{
	FREQM_StatusType eStatus = FREQM_STATUS_SUCCESS;
	uint32_t u32TimeOutVal = 0xffff;
	uint32_t u32CntStatus;	
	
	FREQM_HWA_SetRefCnt(pFreqmPtrs,0U);
	
	do 
	{
		u32CntStatus = FREQM_HWA_GetCntStatus(pFreqmPtrs);
		u32TimeOutVal--;
	}while(u32CntStatus!=0U);
	
	if(u32TimeOutVal == 0U)
	{
		eStatus = FREQM_STATUS_TIMEOUT;
	}
	return eStatus;
}

/**
 * @brief Start the reference/measure counter
 *
 */
void FREQM_StartMeasureCnt()
{
	FREQM_HWA_SetMesCnt(pFreqmPtrs,0U);
}

/**
 * @brief Get saved reference counter value
 *
 * @return uint32_t saved reference counter value
 */
uint32_t FREQM_GetRefCntSave()
{
	return FREQM_HWA_GetRefCntSave(pFreqmPtrs);
}

/**
 * @brief FREQM initialize interrupt function
 *
 * @param pIntStruct FREQM interrupt structure
 * @return FREQM_StatusType whether the operation is successfully
 */
FREQM_StatusType FREQM_InterruptInit(const FREQM_InterruptType *const pIntrStruct)
{
	FREQM_StatusType eStatus = FREQM_STATUS_SUCCESS;
	
	FREQM_HWA_EnableCntEventInterrupt(pFreqmPtrs);
	/*register callback functions*/
	s_pMesCntStartCallback = pIntrStruct->pMesCntStartCallback;
	s_pMesCntStopCallback = pIntrStruct->pMesCntStopCallback;
	s_pRefCntStopCallback = pIntrStruct->pRefCntStopCallback;
	s_pFaultCallback      = pIntrStruct->pFaultCallback;

	return eStatus;
}

/**
 * @brief Interrupt IRQ handle of FREQM
 *
 */
void FREQM_IRQHandler(void)
{
	uint32_t u32CntStatus;
	bool bIntFlag;
	
	bIntFlag = FREQM_HWA_GetInterruptFlag(pFreqmPtrs);	
	if(bIntFlag)
	{
		FREQM_HWA_ClearInterruptFlag(pFreqmPtrs);
	}
	
	u32CntStatus = FREQM_HWA_GetCntStatus(pFreqmPtrs);

	if(u32CntStatus == FREQM_CNT_STATUS_MES_CNT_START_MASK)//0x4
	{
		s_pMesCntStartCallback();
	}
	else if(u32CntStatus == (FREQM_CNT_STATUS_MES_CNT_START_MASK|FREQM_CNT_STATUS_MES_CNT_STOP_MASK) )//0x6
	{

		s_pMesCntStopCallback();
	}
	else if(u32CntStatus == (FREQM_CNT_STATUS_MES_CNT_START_MASK|FREQM_CNT_STATUS_MES_CNT_STOP_MASK|FREQM_CNT_STATUS_REF_CNT_STOP_MASK) )//0x7
	{
		s_pRefCntStopCallback();
	}
	else
	{
		s_pFaultCallback();
	}
}
