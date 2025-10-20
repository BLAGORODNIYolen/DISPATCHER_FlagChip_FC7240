/**
 * @file HwA_lu.h
 * @author Flagchip0103
 * @brief FC7xxx LU hardware access layer
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

#ifndef _HWA_LU_H_
#define _HWA_LU_H_

#include "device_header.h"

/********* Local typedef ************/
/** @brief LU LG instance */
typedef enum
{
    LU_LG_0 = 0U,
    LU_LG_1,
    LU_LG_2,
    LU_LG_3
} LU_LgType;

/** @brief LU AOI mode */
typedef enum
{
    LU_NO_BYPASS = 0U,
    LU_AOI0_BYPASS,
    LU_AOI1_BYPASS,
    LU_AOI0_AOI1_BYPASS
} LU_BypassModeType;

/** @brief LU FF mode */
typedef enum
{
    LU_BYPASS_MODE0    = 0U,
    LU_RS_MODE,
    LU_TFF_MODE,
    LU_DFF_MODE,
    LU_JKFF_MODE,
    LU_LATCH_MODE
} LU_ConfigModeType;

/** @brief LU Input(n) type */
typedef enum
{
    LU_INPUT_N_A = 0U,
    LU_INPUT_N_B,
    LU_INPUT_N_C,
    LU_INPUT_N_D
} LU_InputNType;
/********* Local inline function ************/
/**
 * @brief Configure LU LG(n) AOI0 configuration
 *
 * @param pLu LU instance
 * @param eLg LG instance
 * @param u32RegValue AOI0 register value
 */
LOCAL_INLINE void LU_HWA_ConfigAOI0(LU_Type* pLu, LU_LgType eLg, uint32_t u32RegValue)
{
    pLu->LG[eLg].AOI_0 = u32RegValue;
}

/**
 * @brief Configure LU LG(n) AOI1 configuration
 *
 * @param pLu LU instance
 * @param eLg LG instance
 * @param u32RegValue AOI1 register value
 */
LOCAL_INLINE void LU_HWA_ConfigAOI1(LU_Type* pLu, LU_LgType eLg, uint32_t u32RegValue)
{
    pLu->LG[eLg].AOI_1 = u32RegValue;
}

/**
 * @brief Configure LU LG(n) contrl configuration
 *
 * @param pLu LU instance
 * @param eLg LG instance
 * @param u32RegValue CTRL register value
 */
LOCAL_INLINE void LU_HWA_ConfigCtrl(LU_Type* pLu, LU_LgType eLg, uint32_t u32RegValue)
{
    pLu->LG[eLg].CTRL = u32RegValue;
}

/**
 * @brief Configure LU LG(n) filter configuration
 *
 * @param pLu LU instance
 * @param eLg LG instance
 * @param u32RegValue FILT register value
 */
LOCAL_INLINE void LU_HWA_ConfigFilter(LU_Type* pLu, LU_LgType eLg, uint32_t u32RegValue)
{
    pLu->LG[eLg].FILT = u32RegValue;
}

/**
 * @brief Set LG bypass control
 *
 * @param pLu LU instance
 * @param eLg LG instance
 * @param eMode LG bypass control mode
 */
LOCAL_INLINE void LU_HWA_SetLgBypassControl(LU_Type* pLu, LU_LgType eLg, LU_BypassModeType eMode)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].CTRL;
    pLu->LG[eLg].CTRL = ((u32TempRegValue & ~(uint32_t)LU_CTRL_BYPASS_MASK) | LU_CTRL_BYPASS(eMode));
}

/**
 * @brief Set LG Flip-Flop mode
 *
 * @param pLu LU instance
 * @param eLg LG instance
 * @param eMode Flip-Flop mode
 */
LOCAL_INLINE void LU_HWA_SetLgFlipFlopMode(LU_Type* pLu, LU_LgType eLg, LU_ConfigModeType eMode)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].CTRL;
    pLu->LG[eLg].CTRL = ((u32TempRegValue & ~(uint32_t)LU_CTRL_MOD_MASK) | LU_CTRL_MOD(eMode));
}

/**
 * @brief Set LG inputs synchronous control
 *
 * @param pLu LU instance
 * @param eLg LG instance
 * @param u32Value LG input bit,0-3 bit indicate INPUT(n)A/INPUT(n)B/INPUT(n)C/INPUT(n)D
 */
LOCAL_INLINE void LU_HWA_SetLgInputsSyncCtrl(LU_Type* pLu, LU_LgType eLg, uint32_t u32Value)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].CTRL;
    pLu->LG[eLg].CTRL = ((u32TempRegValue & ~(uint32_t)LU_CTRL_SYNC_MASK) | LU_CTRL_SYNC(u32Value));
}

/**
 * @brief Set LG output feedback override control
 *
 * @param pLu LU instance
 * @param eLg LG instance
 * @param eInput Feedback to LG input
 */
LOCAL_INLINE void LU_HWA_SetLgFeedbackOverrideCtrl(LU_Type* pLu, LU_LgType eLg, LU_InputNType eInput)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].CTRL;
    pLu->LG[eLg].CTRL = ((u32TempRegValue & ~(uint32_t)LU_CTRL_FB_OVRD_MASK) | LU_CTRL_FB_OVRD(eInput));
}

/**
 * @brief Configure the output of flip-flop as "1"
 *
 * @param pLu LU instance
 * @param eLg LG instance
 */
LOCAL_INLINE void LU_HWA_ConfigFlipFlopTo1(LU_Type* pLu, LU_LgType eLg)
{
    pLu->LG[eLg].CTRL |= (uint32_t)LU_CTRL_FF_INIT_MASK;
}

/**
 * @brief Generate enable pulse
 *
 * @param pLu LU instance
 * @param eLg LG instance
 */
LOCAL_INLINE void LU_HWA_EnableControlFlipFlopInitOutput(LU_Type* pLu, LU_LgType eLg)
{
    pLu->LG[eLg].CTRL |= (uint32_t)LU_CTRL_INIT_EN_MASK;
}

/**
 * @brief Input filter sample count for AOI0
 *
 * @param pLu LU instance
 * @param eLg LG instance
 * @param u32Value Sample count value
 */
LOCAL_INLINE void LU_HWA_SetAOI0InputFilterSampleCount(LU_Type* pLu, LU_LgType eLg, uint32_t u32Value)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].FILT;
    pLu->LG[eLg].FILT = ((u32TempRegValue & ~(uint32_t)LU_FILT_CNT0_MASK) | LU_FILT_CNT0(u32Value));
}

/**
 * @brief Input filter sample period for AOI0
 *
 * @param pLu LU instance
 * @param eLg LG instance
 * @param u32Value Sample period value
 */
LOCAL_INLINE void LU_HWA_SetAOI0InputFilterSamplePeriod(LU_Type* pLu, LU_LgType eLg, uint32_t u32Value)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].FILT;
    pLu->LG[eLg].FILT = ((u32TempRegValue & ~(uint32_t)LU_FILT_PRE0_MASK) | LU_FILT_PRE0(u32Value));
}

/**
 * @brief Input filter sample count for AOI1
 *
 * @param pLu LU instance
 * @param eLg LG instance
 * @param u32Value Sample count value
 */
LOCAL_INLINE void LU_HWA_SetAOI1InputFilterSampleCount(LU_Type* pLu, LU_LgType eLg, uint32_t u32Value)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].FILT;
    pLu->LG[eLg].FILT = ((u32TempRegValue & ~(uint32_t)LU_FILT_CNT1_MASK) | LU_FILT_CNT1(u32Value));
}

/**
 * @brief Input filter sample period for AOI1
 *
 * @param pLu LU instance
 * @param eLg LG instance
 * @param u32Value Sample period value
 */
LOCAL_INLINE void LU_HWA_SetAOI1InputFilterSamplePeriod(LU_Type* pLu, LU_LgType eLg, uint32_t u32Value)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].FILT;
    pLu->LG[eLg].FILT = ((u32TempRegValue & ~(uint32_t)LU_FILT_PRE1_MASK) | LU_FILT_PRE1(u32Value));
}

/**
 * @brief Configure the output of flip-flop as "0"
 *
 * @param pLu LU instance
 * @param eLg LG instance
 */
LOCAL_INLINE void LU_HWA_ConfigFlipFlopTo0(LU_Type* pLu, LU_LgType eLg)
{
    pLu->LG[eLg].CTRL &= ~(uint32_t)LU_CTRL_FF_INIT_MASK;
}

#endif /* #ifndef _HWA_LU_H_ */
