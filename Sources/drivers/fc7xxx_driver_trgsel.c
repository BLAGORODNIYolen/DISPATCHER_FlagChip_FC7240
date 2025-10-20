/**
 * @file fc7xxx_driver_trgsel.c
 * @author Flagchip0103
 * @brief FC7xxx TRGSEL driver source code
 * @version 0.1.0
 * @date 2023-12-19
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0      2023-12-19    Flagchip0103   N/A          First version for FC7240
   ******************************************************************************** */

#include <interrupt_manager.h>

#include "fc7xxx_driver_trgsel.h"
#include "HwA_trgsel.h"
#include "HwA_scm.h"

/**
 * @brief Number of target outputs of TrgSel 0
 *
 */
#define TRGSEL0_NUM_OUTPUTS            38U

/**
 * @brief Number of target outputs of TrgSel 1
 *
 */
#define TRGSEL1_NUM_OUTPUTS            28U

/**
 * @brief Number of target outputs of TrgSel 2
 *
 */
#define TRGSEL2_NUM_OUTPUTS            30U

/**
 * @brief Number of target outputs of TrgSel 3
 *
 */
#define TRGSEL3_NUM_OUTPUTS            16U

/**
 * @brief Number of target outputs of TrgSel 4
 *
 */
#define TRGSEL4_NUM_OUTPUTS            10U

/**
 * @brief Number of target outputs of TrgSel 5
 *
 */
#define TRGSEL5_NUM_OUTPUTS            13U

/**
 * @brief Number of input sources of TrgSel 0
 *
 */
#define TRGSEL0_NUM_SOURCES            128U

/**
 * @brief Number of input sources of TrgSel 1
 *
 */
#define TRGSEL1_NUM_SOURCES            94U

/**
 * @brief Number of input sources of TrgSel 2
 *
 */
#define TRGSEL2_NUM_SOURCES            32U

/**
 * @brief Number of input sources of TrgSel 3
 *
 */
#define TRGSEL3_NUM_SOURCES            62U

/**
 * @brief Number of input sources of TrgSel 4
 *
 */
#define TRGSEL4_NUM_SOURCES            112U

/**
 * @brief Number of input sources of TrgSel 5
 *
 */
#define TRGSEL5_NUM_SOURCES            64U

#define TRGSEL_NUM_SW_TRG_CHANNELS     8U

static TRGSEL_Type *const s_trgselBase[TRGSEL_INSTANCE_COUNT] = TRGSEL_BASE_PTRS;

#ifndef NDEBUG
/**
 * @brief Check whether the TRGSEL target is valid for the TRGSEL instance
 *
 * @param eInstance the selected TRGSEL instance
 * @param eTarget the target value to check
 * @return true the TRGSEL target is valid
 * @return false the TRGSEL target is invalid
 */
static inline bool TRGSEL_IsValidTarget(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget);

/**
 * @brief Check whether the TRGSEL source is valid for the TRGSEL instance
 *
 * @param eInstance the selected TRGSEL instance
 * @param eSource the source value to check
 * @return true the TRGSEL source is valid
 * @return false the TRGSEL source is invalid
 */
static inline bool TRGSEL_IsValidSource(const TRGSEL_InstanceType eInstance, const TRGSEL_SourceType eSource);

static inline bool TRGSEL_IsValidTarget(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget)
{
    bool bRet = false;
    switch (eInstance)
    {
        case TRGSEL_INSTANCE_0:
        {
            bRet = (bool)((eTarget < TRGSEL0_NUM_OUTPUTS) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_1:
        {
            bRet = (bool)((eTarget < TRGSEL1_NUM_OUTPUTS) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_2:
        {
            bRet = (bool)((eTarget < TRGSEL2_NUM_OUTPUTS) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_3:
        {
            bRet = (bool)((eTarget < TRGSEL3_NUM_OUTPUTS) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_4:
        {
            bRet = (bool)((eTarget < TRGSEL4_NUM_OUTPUTS) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_5:
        {
            bRet = (bool)((eTarget < TRGSEL5_NUM_OUTPUTS) ? true : false);
            break;
        }

        default:
            break;
    }
    return bRet;
}

static inline bool TRGSEL_IsValidSource(const TRGSEL_InstanceType eInstance, const TRGSEL_SourceType eSource)
{
    bool bRet = false;
    switch (eInstance)
    {
        case TRGSEL_INSTANCE_0:
        {
            bRet = (bool)((eSource < TRGSEL0_NUM_SOURCES) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_1:
        {
            bRet = (bool)((eSource < TRGSEL1_NUM_SOURCES) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_2:
        {
            bRet = (bool)((eSource < TRGSEL2_NUM_SOURCES) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_3:
        {
            bRet = (bool)((eSource < TRGSEL3_NUM_SOURCES) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_4:
        {
            bRet = (bool)((eSource < TRGSEL4_NUM_SOURCES) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_5:
        {
            bRet = (bool)((eSource < TRGSEL5_NUM_SOURCES) ? true : false);
            break;
        }

        default:
            break;
    }
    return bRet;
}
#endif

TRGSEL_SourceType TRGSEL_GetTargetTriggerSource(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget)
{
    DEV_ASSERT(eInstance < TRGSEL_INSTANCE_COUNT);
    DEV_ASSERT(TRGSEL_IsValidTarget(eInstance, eTarget));

    const TRGSEL_Type *const pTrgsel = s_trgselBase[eInstance];

    uint32_t u32Tmp = TRGSEL_HWA_GetTargetTriggerSource(pTrgsel, eTarget);

    return (TRGSEL_SourceType)u32Tmp;
}

void TRGSEL_SetTargetTriggerSource(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget,
                                   const TRGSEL_SourceType eSource)
{
    DEV_ASSERT(eInstance < TRGSEL_INSTANCE_COUNT);
    DEV_ASSERT(TRGSEL_IsValidTarget(eInstance, eTarget));
    DEV_ASSERT(TRGSEL_IsValidSource(eInstance, eSource));
    DEV_ASSERT(TRGSEL_GetTargetLockStatus(eInstance, eTarget) != true);

    TRGSEL_Type *const pTrgsel = s_trgselBase[eInstance];

    TRGSEL_HWA_SetTargetTriggerSource(pTrgsel, eTarget, eSource);
}

bool TRGSEL_GetTargetLockStatus(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget)
{
    DEV_ASSERT(eInstance < TRGSEL_INSTANCE_COUNT);
    DEV_ASSERT(TRGSEL_IsValidTarget(eInstance, eTarget));

    const TRGSEL_Type *const pTrgsel = s_trgselBase[eInstance];

    return TRGSEL_HWA_GetTargetLockStatus(pTrgsel, eTarget);
}

void TRGSEL_LockTargetTriggerSource(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget)
{
    DEV_ASSERT(eInstance < TRGSEL_INSTANCE_COUNT);
    DEV_ASSERT(TRGSEL_IsValidTarget(eInstance, eTarget));

    TRGSEL_Type *const pTrgsel = s_trgselBase[eInstance];

    if (TRGSEL_GetTargetLockStatus(eInstance, eTarget) != true)
    {
        TRGSEL_HWA_LockTargetTriggerSource(pTrgsel, eTarget);
    }
}

void TRGSEL_GenerateSwTrigger(const TRGSEL_SwTriggerChannelType eChannel)
{
    DEV_ASSERT(eChannel < TRGSEL_NUM_SW_TRG_CHANNELS);

    switch (eChannel)
    {
        case TRGSEL_SW_TRIGGER_CHANNEL_0:
        {
        	SCM_HWA_SetSwTrigx_Trgsel04(SCM_SW_TRIG_0);
            break;
        }
        case TRGSEL_SW_TRIGGER_CHANNEL_1:
        {
        	SCM_HWA_SetSwTrigx_Trgsel04(SCM_SW_TRIG_1);
            break;
        }
        case TRGSEL_SW_TRIGGER_CHANNEL_2:
        {
        	SCM_HWA_SetSwTrigx_Trgsel04(SCM_SW_TRIG_2);
            break;
        }
        case TRGSEL_SW_TRIGGER_CHANNEL_3:
        {
        	SCM_HWA_SetSwTrigx_Trgsel04(SCM_SW_TRIG_3);
            break;
        }
        case TRGSEL_SW_TRIGGER_CHANNEL_4:
        {
        	SCM_HWA_SetSwTrigx_Trgsel15(SCM_SW_TRIG_4);
            break;
        }
        case TRGSEL_SW_TRIGGER_CHANNEL_5:
        {
        	SCM_HWA_SetSwTrigx_Trgsel15(SCM_SW_TRIG_5);
            break;
        }
        case TRGSEL_SW_TRIGGER_CHANNEL_6:
        {
        	SCM_HWA_SetSwTrigx_Trgsel15(SCM_SW_TRIG_6);
            break;
        }
        case TRGSEL_SW_TRIGGER_CHANNEL_7:
        {
        	SCM_HWA_SetSwTrigx_Trgsel15(SCM_SW_TRIG_7);
            break;
        }
        default:
            break;
    }
}
