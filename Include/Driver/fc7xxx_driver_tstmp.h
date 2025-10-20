/**
 * @file fc7xxx_driver_tstmp.h
 * @author Flagchip
 * @brief FC7xxx TSTMP driver type definition and API
 * @version 0.1.0
 * @date 2023-12-22
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
*   0.1.0       2023-12-18    Flagchip0122    N/A          FC7xxx internal release version
********************************************************************************/

#ifndef _DRIVER_FC7XXX_DRIVER_TSTMP_H_
#define _DRIVER_FC7XXX_DRIVER_TSTMP_H_
#include "HwA_tstmp.h"

/**
 * @addtogroup fc7xxx_driver_tstmp
 * @{
 */

/** @brief TSTMP max mod number*/
#define MAX_MOD_NUMBER  4U

/** @brief TSTMP return type. */
typedef enum
{
    TSTMP_STATUS_SUCCESS = 0U,
    TSTMP_STATUS_PARAM_INVALID = 1U
} TSTMP_StatusType;

/** @brief TSTMP instance */
typedef enum
{
    TSTMP_INSTANCE_0 = 0U,
    TSTMP_INSTANCE_1 = 1U,
    TSTMP_INSTANCE_MAX
} TSTMP_InstanceType;

/** @brief TSTMP interrupt notification function type */
typedef void (*TSTMP_InterruptCallBackType)(void);

/** @brief TSTMP interrupt type */
typedef struct
{
    bool bModulateIntEn[MAX_MOD_NUMBER];                               /**< whether use the modulate n interrupt */
    TSTMP_InterruptCallBackType pIsrModNotify[MAX_MOD_NUMBER];         /**< modulate n interrupt function pointer */
} TSTMP_IntType;

/** @brief TSTMP initialization type */
typedef struct
{
    uint32_t u32Modulate0Value;                         /**< modulate 0 value */
    uint32_t u32Modulate1Value;                         /**< modulate 1 value */
    uint32_t u32Modulate2Value;                         /**< modulate 2 value */
    uint32_t u32Modulate3Value;                         /**< modulate 3 value */
    TSTMP_ClockSourceType pClk[MAX_MOD_NUMBER];
} TSTMP_InitType;

/** @brief TSTMP update type */
typedef struct
{
    TSTMP_ModulateType eMod;                        /**< TSTMP modulate */
    uint32_t u32ModValue;                           /**< TSTMP modulate value */
    bool bIntEn;                                    /**< whether enable TSTMP modulate interrupt */
    TSTMP_InterruptCallBackType pIsrModNotify;      /**< TSTMP interrupt notification */
} TSTMP_UpdateType;

/* global functions */
/**
 * @brief Initialize TSTMP instance
 *
 * @param eInstance TSTMP instance
 * @param pInitStruct TSTMP initialization structure
 * @return TSTMP_StatusType TSTMP return type
 * @note TSTMP0 clock source is 1MHZ and TSTMP1,TSTMP2,TSTMP3 clock source is bus clock
 */
TSTMP_StatusType TSTMP_Init(const TSTMP_InstanceType eInstance, const TSTMP_InitType *const pInitStruct);

/**
 * @brief Set the Counting mode of modulate timer counter0,1,2,3
 *
 * @param eInstance TSTMP instance
 * @param eCounter0Mode Counting mode of counter0
 * @param eCounter1Mode Counting mode of counter1
 * @param eCounter2Mode Counting mode of counter2
 * @param eCounter3Mode Counting mode of counter3
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_SetCounterRunningMode(const TSTMP_InstanceType eInstance, const TSTMP_ModeCounterRunningMode eCounter0Mode,
        const TSTMP_ModeCounterRunningMode eCounter1Mode,const TSTMP_ModeCounterRunningMode eCounter2Mode,
        const TSTMP_ModeCounterRunningMode eCounter3Mode);

/**
 * @brief De-initialize TSTMP instance
 *
 * @param eInstance TSTMP instance
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_Deinit(const TSTMP_InstanceType eInstance);

/**
 * @brief Initialize TSTMP interrupt functionality
 *
 * @param eInstance TSTMP instance
 * @param pIntStruct TSTMP interrupt structure
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_InitInterrupt(const TSTMP_InstanceType eInstance, const TSTMP_IntType *const pIntStruct);

/**
 * @brief Enable TSTMP interrupt function
 *
 * @param eInstance TSTMP instance
 * @param eMod TSTMP modulate enumeration
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_EnableInterrupt(const TSTMP_InstanceType eInstance, const TSTMP_ModulateType eMod);

/**
 * @brief Disable TSTMP interrupt function
 *
 * @param eInstance TSTMP instance
 * @param eMod TSTMP modulate enumeration
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_DisableInterrupt(const TSTMP_InstanceType eInstance, const TSTMP_ModulateType eMod);

/**
 * @brief Get TSTMP count value
 *
 * @param eInstance TSTMP instance
 * @param u64TstmpValue in/out value
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_GetTstmpValue(const TSTMP_InstanceType eInstance, uint64_t *const u64TstmpValue);

/**
 * @brief Update Modulate configuration
 *
 * @param eInstance TSTMP instance
 * @param pUpdateStruct TSTMP update structure pointer
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_UpdateMod(const TSTMP_InstanceType eInstance,
                                 const TSTMP_UpdateType *const pUpdateStruct);
/**
 * @brief Set counter MOD(n) counting on or off
 *
 * @param eInstance TSTMP instance
 * @param eMod MOD number
 * @param bCounterEn Whether enable the selected Modulate Timer Counter
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_SetModCountConfig(const TSTMP_InstanceType eInstance, const TSTMP_ModulateType eMod,const bool bCounterEn);

/** @}*/ /* fc7xxx_driver_tstmp */
#endif
