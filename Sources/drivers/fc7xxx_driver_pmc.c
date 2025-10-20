/* @file fc7xxx_driver_pmc.c
* @author Flagchip032
* @brief FC7xxx PMC driver type definition and API
* @version 0.1.0
* @date 2022-11-21
*
* @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
*
*/
/* ********************************************************************************
  *   Revision History:
  *
  *   Version     Date          Initials          Descriptions
  *   ---------   ----------    ------------     ---------------
  *   0.1.0       2022-11-21    Flagchip032      First version for FC7xxx
  ******************************************************************************** */
#include "fc7xxx_driver_pmc.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/***************** Local variable *********************/
static PMC_VolIntCallbackType pIsrNotify = NULL_PTR;


/***************** prototype *********************/
/**
 * @brief PMC interrupt function entry
 *
 */
void PMC_IRQHandler(void);

/***************** Global Functions *********************/
/**
 * @brief Get LVCSRRegister Value
 *
 * @return uint32_t LVCSRRegister Value
 */
uint32_t PMC_GetLVCSRRegister(void)
{
	return PMC_HWA_GetLVCSRRegister();
}

/**
 * @brief Get All voltage flag
 *
 * @return uint32_t All voltage flag
 */
uint32_t PMC_GetAllVolFlag(void)
{
    uint32_t u32AllVolFlag = 0U;
    u32AllVolFlag = (PMC_HWA_GetLVCSRRegister() & PMC_LVCSR_ALLFLAG_MASK);
    return u32AllVolFlag;
}

/**
 * @brief Get specific voltage flag
 *
 * @param eFlag Voltage flag
 * @return boolean If return true, the specific voltage flag is 0, otherwise, the flag is 1.
 */
boolean PMC_GetSpecificVolFlag(const PMC_FlagType eFlag)
{
    return ((PMC_HWA_GetLVCSRRegister() & eFlag) != 0U) ? true : false;
}

/**
 * @brief Clear all voltage flag
 *
 */
void PMC_ClearAllVolFlag(void)
{
    PMC_HWA_SetLVCSRRegister(PMC_LVCSR_ALLFLAG_MASK);
}

/**
 * @brief Clear specific voltage flag
 *
 * @param eFlag Voltage flag
 */
void PMC_ClearSpecificVolFlag(const PMC_FlagType eFlag)
{
    PMC_HWA_SetLVCSRRegister(eFlag);
}

/**
 * @brief Get All voltage status
 *
 * @return uint32_t All voltage status
 */
uint32_t PMC_GetAllVolStatus(void)
{
    uint32_t u32AllVolStatus = 0U;
    u32AllVolStatus = (PMC_HWA_GetLVCSRRegister() & PMC_LVCSR_ALLSTATUS_MASK);
    return u32AllVolStatus;
}

/**
 * @brief Get specific voltage status
 *
 * @param eStatus Specific voltage status
 * @return boolean If return true, the specific voltage status is 0, otherwise, the status is 1.
 */
boolean PMC_GetSpecificVolStatus(const PMC_StatusType eStatus)
{
    return ((PMC_HWA_GetLVCSRRegister() & eStatus) != 0U) ? true : false;
}

/**
 * @brief Configure Voltage
 *
 * @param pCtrl Configuration of voltage
 */
void PMC_ConfigVoltage(const PMC_CtrlType *const pCtrl)
{
    uint32_t u32ConfigVal = 0U;
    PMC_HWA_UnlockConfigRegister();

    if ((pCtrl->bLvdIntEn) || (pCtrl->bHvdIntEn) || (pCtrl->b5VBMonEn) \
    		|| (pCtrl->bRpmV25En) || (pCtrl->bV15AutoswEn) || (pCtrl->bV15CtrlEn))
    {
        pIsrNotify = pCtrl->pIsrNotify;
    }

    u32ConfigVal = PMC_CONFIG_LVD_IE(pCtrl->bLvdIntEn) | PMC_CONFIG_HVD_IE(pCtrl->bHvdIntEn) | PMC_CONFIG_V15_CTRL_EN(pCtrl->bV15CtrlEn) | PMC_CONFIG_V15_AUTOSW(
                       pCtrl->bV15AutoswEn) | PMC_CONFIG_RPM_VDD2P5_EN(pCtrl->bRpmV25En);
    PMC_HWA_SetConfigRegister(u32ConfigVal);
}

/**
 * @brief Clear all PMC register
 *
 */
void PMC_Deinit(void)
{
    PMC_HWA_SetLVCSRRegister(0x93ff0030U);
    PMC_HWA_SetConfigRegister(0x8000U);
}

/**
 * @brief PMC interrupt function entry
 *
 */
void PMC_IRQHandler(void)
{
    if (NULL_PTR != pIsrNotify)
    {
        pIsrNotify();
    }
	if(PMC_GetSpecificVolFlag(PMC_HVD5V_FLAG))
	{
		PMC_ClearSpecificVolFlag(PMC_HVD5V_FLAG);
	}
	if (PMC_GetSpecificVolFlag(PMC_HVD2P5V_FLAG))
	{
		PMC_ClearSpecificVolFlag(PMC_HVD2P5V_FLAG);
	}
	if (PMC_GetSpecificVolFlag(PMC_HVD1P1V_FLAG))
	{
		PMC_ClearSpecificVolFlag(PMC_HVD1P1V_FLAG);
	}
	if (PMC_GetSpecificVolFlag(PMC_LVD5V_FLAG))
	{
		PMC_ClearSpecificVolFlag(PMC_LVD5V_FLAG);
	}
	if (PMC_GetSpecificVolFlag(PMC_LVD1P5V_FLAG))
	{
		PMC_ClearSpecificVolFlag(PMC_LVD1P5V_FLAG);
	}
	if (PMC_GetSpecificVolFlag(PMC_HVD1P5V_FLAG))
	{
		PMC_ClearSpecificVolFlag(PMC_HVD1P5V_FLAG);
	}
}
