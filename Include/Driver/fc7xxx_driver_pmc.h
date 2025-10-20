/* @file fc7xxx_driver_pmc.h
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
#ifndef _DRIVER_FC7XXX_DRIVER_PMC_H_
#define _DRIVER_FC7XXX_DRIVER_PMC_H_
#include "HwA_pmc.h"

#if defined(__cplusplus)
extern "C" {
#endif


/**
 * @addtogroup fc7xxx_driver_pmc
 * @{
 */

/***************** typedef *********************/
/**
 * @brief PMC voltage flags.
 * 
 */
typedef enum
{
    PMC_HVD5V_FLAG = PMC_LVSCR_HVD5V_FLAG_MASK, /**< interrupt flag on V5 domain in FPM */
    PMC_HVD2P5V_FLAG = PMC_LVSCR_HVD2P5V_FLAG_MASK, /**< interrupt flag on V25 domain in FPM */
    PMC_HVD1P1V_FLAG = PMC_LVSCR_HVD1P1V_FLAG_MASK, /**< interrupt flag on V11 domain in FPM */
    PMC_LVD5V_FLAG = PMC_LVSCR_LVD5V_FLAG_MASK, /**< interrupt flag on V5 domain in FPM */
    PMC_LVD1P5V_FLAG = PMC_LVSCR_LVD1P5V_FLAG_MASK, /**< interrupt flag on V15 domain in FPM */
    PMC_HVD1P5V_FLAG = PMC_LVSCR_HVD1P5V_FLAG_MASK, /**< interrupt flag on V15 domain in FPM */
    PMC_LVR5V_FPM_FLAG = PMC_LVSCR_LVR5V_FPM_FLAG_MASK, /**< Low voltage reset flag of V5 domain in FPM */
    PMC_LVR5V_RPM_FLAG = PMC_LVSCR_LVR5V_RPM_FLAG_MASK, /**< Low voltage reset flag of V5 domain in RPM */
    PMC_LVR2P5V_FPM_FLAG = PMC_LVSCR_LVR2P5V_FPM_FLAG_MASK, /**< Low voltage reset flag of V25 domain in FPM */
    PMC_LVR2P5V_RPM_FLAG = PMC_LVSCR_LVR2P5V_RPM_FLAG_MASK, /**< Low voltage reset flag of V25 domain in RPM */
    PMC_LVR1P1V_FPM_FLAG = PMC_LVSCR_LVR1P1V_FPM_FLAG_MASK, /**< Low voltage reset flag of V11 domain in FPM */
    PMC_LVR1P1V_RPM_FLAG = PMC_LVSCR_LVR1P1V_RPM_FLAG_MASK, /**< Low voltage reset flag of V11 domain in RPM */
    PMC_POR_FLAG = PMC_LVSCR_POR_FLAG_MASK /**< POR flag */
} PMC_FlagType;

/**
 * @brief PMC voltage status.
 * 
 */
typedef enum
{
    PMC_HVD5V_STATUS = PMC_LVSCR_HVD5V_STATUS_MASK, /**< HVD5V status on V5 domain in FPM */
    PMC_HVD2P5V_STATUS = PMC_LVSCR_HVD2P5V_STATUS_MASK, /**< HVD25 status on V25 domain in FPM */
    PMC_HVD1P1V_STATUS = PMC_LVSCR_HVD1P1V_STATUS_MASK, /**< HVD11 status on V11 domain in FPM */
    PMC_LVD5V_STATUS = PMC_LVSCR_LVD5V_STATUS_MASK, /**< LVD5V status on V5 domain in FPM */
    PMC_LVD1P5V_STATUS = PMC_LVSCR_LVD1P5V_STATUS_MASK, /**< LVD1P5V status on V15 domain in FPM */
    PMC_HVD1P5V_STATUS = PMC_LVSCR_HVD1P5V_STATUS_MASK, /**< HVD1P5V status on V15 domain in FPM */
    PMC_V15_LDO_STATUS = PMC_LVSCR_V15_STATUS(0U), /**< V15 is working on internal V15 LDO */
    PMC_V15_ON_BOARD_NPN_STATUS = PMC_LVSCR_V15_STATUS(1U), /**< V15 is working on internal V15 controller with on board NPN */
    PMC_V15_DRIVEN_BY_EXTERNAL_STATUS = PMC_LVSCR_V15_STATUS(2U) /**< V15 is driven by external driver such as on board DCDC, V15_CFG PAD is driven high */
} PMC_StatusType;

typedef void (*PMC_VolIntCallbackType)(void);

/** @brief Pmc control type */
typedef struct
{
    boolean bLvdIntEn;                /**< bit9, low voltage detect interrupt enable */
    boolean bHvdIntEn;                /**< bit8, high voltage detect interrupt enable */
    boolean b5VBMonEn;                /**< bit6, VDD5V_B LVR monitor enable during RPM */
    boolean bV15CtrlEn;               /**< bit5, V15 controller with on board NPN enable */
    boolean bV15AutoswEn;             /**< bit4, V15 auto switch enable */
    boolean bRpmV25En;                /**< bit3, V25 domain enable during RPM  */
    PMC_VolIntCallbackType pIsrNotify; /**< interrupt notification */
} PMC_CtrlType;

/***************** macro *********************/
/**< All flags of LVCSR MSASK */
#define PMC_LVCSR_ALLFLAG_MASK       (uint32_t)(PMC_LVSCR_HVD5V_FLAG_MASK|\
                                                PMC_LVSCR_HVD2P5V_FLAG_MASK|\
                                                PMC_LVSCR_HVD1P1V_FLAG_MASK|\
                                                PMC_LVSCR_LVD5V_FLAG_MASK|\
                                                PMC_LVSCR_LVD1P5V_FLAG_MASK|\
                                                PMC_LVSCR_HVD1P5V_FLAG_MASK|\
                                                PMC_LVSCR_LVR5V_FPM_FLAG_MASK|\
                                                PMC_LVSCR_LVR5V_RPM_FLAG_MASK|\
                                                PMC_LVSCR_LVR2P5V_FPM_FLAG_MASK|\
                                                PMC_LVSCR_LVR2P5V_RPM_FLAG_MASK|\
                                                PMC_LVSCR_LVR1P1V_FPM_FLAG_MASK|\
                                                PMC_LVSCR_LVR1P1V_RPM_FLAG_MASK|\
                                                PMC_LVSCR_POR_FLAG_MASK)

#define PMC_LVCSR_ALLSTATUS_MASK      (uint32_t)(PMC_LVSCR_HVD5V_STATUS_MASK|\
                                                 PMC_LVSCR_HVD2P5V_STATUS_MASK|\
                                                 PMC_LVSCR_HVD1P1V_STATUS_MASK|\
                                                 PMC_LVSCR_LVD5V_STATUS_MASK|\
                                                 PMC_LVSCR_LVD1P5V_STATUS_MASK|\
                                                 PMC_LVSCR_HVD1P5V_STATUS_MASK|\
                                                 PMC_LVSCR_V15_STATUS_MASK)






/***************** API *********************/
/**
 * @brief Get LVCSRRegister Value
 *
 * @return uint32_t LVCSRRegister Value
 */
uint32_t PMC_GetLVCSRRegister(void);
/**
 * @brief Get All voltage flag
 * 
 * @return uint32_t All voltage flag
 */
uint32_t PMC_GetAllVolFlag(void);

/**
 * @brief Get specific voltage flag
 * 
 * @param eFlag Voltage flag
 * @return boolean If return true, the specific voltage flag is 0, otherwise, the flag is 1.
 */
boolean PMC_GetSpecificVolFlag(const PMC_FlagType eFlag);

/**
 * @brief Clear all voltage flag
 * 
 */
void PMC_ClearAllVolFlag(void);

/**
 * @brief Clear specific voltage flag
 * 
 * @param eFlag Voltage flag
 */
void PMC_ClearSpecificVolFlag(const PMC_FlagType eFlag);

/**
 * @brief Get All voltage status
 * 
 * @return uint32_t All voltage status
 */
uint32_t PMC_GetAllVolStatus(void);

/**
 * @brief Get specific voltage status
 * 
 * @param eStatus Specific voltage status
 * @return boolean If return true, the specific voltage status is 0, otherwise, the status is 1.
 */
boolean PMC_GetSpecificVolStatus(const PMC_StatusType eStatus);

/**
 * @brief Configure Voltage
 * 
 * @param pCtrl Configuration of voltage
 */
void PMC_ConfigVoltage(const PMC_CtrlType *const pCtrl);

/**
 * @brief Clear all PMC register
 * 
 */
void PMC_Deinit(void);


#if defined(__cplusplus)
}
#endif
/** @}*/  /* fc7xxx_driver_pmc */
#endif
