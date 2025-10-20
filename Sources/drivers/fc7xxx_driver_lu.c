/**
 * @file fc7xxx_driver_lu.c
 * @author Flagchip0103
 * @brief FC7xxx LU driver type definition and API
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

#include "fc7xxx_driver_lu.h"

/**
 * @brief Initialize Lu instance
 *
 * @param pInitStruct Lu initialization structure
 * @return LU return type
 */
LU_StatusType LU_Init(const LU_InitType *const pInitStruct)
{
    uint32_t u32TempReg, u32TempCfg;
    LU_StatusType eRet = LU_STATUS_SUCCESS;
    LU_Type* pLu = LU;

    DEV_ASSERT(NULL_PTR != pInitStruct);

    /* set AOI0 value */
    LU_HWA_ConfigAOI0(pLu, pInitStruct->eLgNum, 0U);
    /* set AOI1 value */
    LU_HWA_ConfigAOI1(pLu, pInitStruct->eLgNum, 0U);
    /* set CTRL value */
    LU_HWA_ConfigCtrl(pLu, pInitStruct->eLgNum, 0U);
    /* set FILT value */
    LU_HWA_ConfigFilter(pLu, pInitStruct->eLgNum, 0U);

    u32TempCfg = (uint32_t)0U |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi0Config.tIn0Config.eInNACfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi0Config.tIn0Config.eInNBCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi0Config.tIn0Config.eInNCCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi0Config.tIn0Config.eInNDCfg);
    u32TempReg = (uint32_t)0U | LU_AOI_IN_N_CFG(LU_AOI_IN_0, u32TempCfg);

    u32TempCfg = (uint32_t)0U |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi0Config.tIn1Config.eInNACfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi0Config.tIn1Config.eInNBCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi0Config.tIn1Config.eInNCCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi0Config.tIn1Config.eInNDCfg);
    u32TempReg |= LU_AOI_IN_N_CFG(LU_AOI_IN_1, u32TempCfg);

    u32TempCfg = (uint32_t)0U |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi0Config.tIn2Config.eInNACfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi0Config.tIn2Config.eInNBCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi0Config.tIn2Config.eInNCCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi0Config.tIn2Config.eInNDCfg);
    u32TempReg |= LU_AOI_IN_N_CFG(LU_AOI_IN_2, u32TempCfg);

    u32TempCfg = (uint32_t)0U |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi0Config.tIn3Config.eInNACfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi0Config.tIn3Config.eInNBCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi0Config.tIn3Config.eInNCCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi0Config.tIn3Config.eInNDCfg);
    u32TempReg |= LU_AOI_IN_N_CFG(LU_AOI_IN_3, u32TempCfg);
    /* set AOI0 value */
    LU_HWA_ConfigAOI0(pLu, pInitStruct->eLgNum, u32TempReg);

    u32TempCfg = (uint32_t)0U |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi1Config.tIn0Config.eInNACfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi1Config.tIn0Config.eInNBCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi1Config.tIn0Config.eInNCCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi1Config.tIn0Config.eInNDCfg);
    u32TempReg = (uint32_t)0U | LU_AOI_IN_N_CFG(LU_AOI_IN_0, u32TempCfg);

    u32TempCfg = (uint32_t)0U |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi1Config.tIn1Config.eInNACfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi1Config.tIn1Config.eInNBCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi1Config.tIn1Config.eInNCCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi1Config.tIn1Config.eInNDCfg);
    u32TempReg |= LU_AOI_IN_N_CFG(LU_AOI_IN_1, u32TempCfg);

    u32TempCfg = (uint32_t)0U |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi1Config.tIn2Config.eInNACfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi1Config.tIn2Config.eInNBCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi1Config.tIn2Config.eInNCCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi1Config.tIn2Config.eInNDCfg);
    u32TempReg |= LU_AOI_IN_N_CFG(LU_AOI_IN_2, u32TempCfg);

    u32TempCfg = (uint32_t)0U |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi1Config.tIn3Config.eInNACfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi1Config.tIn3Config.eInNBCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi1Config.tIn3Config.eInNCCfg) |
                 LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi1Config.tIn3Config.eInNDCfg);
    u32TempReg |= LU_AOI_IN_N_CFG(LU_AOI_IN_3, u32TempCfg);
    /* set AOI1 value */
    LU_HWA_ConfigAOI1(pLu, pInitStruct->eLgNum, u32TempReg);

    /* force bypass mode */
    LU_HWA_SetLgBypassControl(pLu, pInitStruct->eLgNum, pInitStruct->eAoiMode);
    /* set Flip-Flop mode configure */
    LU_HWA_SetLgFlipFlopMode(pLu, pInitStruct->eLgNum, pInitStruct->eFFMode);
    u32TempCfg = 0U;
    if (pInitStruct->tSyncCtrl.bInputNA)
    {
        u32TempCfg |= LU_SYNC_CONTROL_INPUT_N(1U, LU_INPUT_N_A);
    }
    if (pInitStruct->tSyncCtrl.bInputNB)
    {
        u32TempCfg |= LU_SYNC_CONTROL_INPUT_N(1U, LU_INPUT_N_B);
    }
    if (pInitStruct->tSyncCtrl.bInputNC)
    {
        u32TempCfg |= LU_SYNC_CONTROL_INPUT_N(1U, LU_INPUT_N_C);
    }
    if (pInitStruct->tSyncCtrl.bInputND)
    {
        u32TempCfg |= LU_SYNC_CONTROL_INPUT_N(1U, LU_INPUT_N_D);
    }
    /* set LG inputs synchronous control */
    LU_HWA_SetLgInputsSyncCtrl(pLu, pInitStruct->eLgNum, u32TempCfg);

    if (LU_JKFF_MODE == pInitStruct->eFFMode)
    {
        /* set LG output feedback override control */
        LU_HWA_SetLgFeedbackOverrideCtrl(pLu, pInitStruct->eLgNum, pInitStruct->eFbMode);
    }

    if (LU_OUTPUT_INIT_DISABLE > pInitStruct->eFFInitValue)
    {
        if (LU_OUTPUT_INIT_ONE == pInitStruct->eFFInitValue)
        {
            /* Configure the output of flip-flop as "1" */
            LU_HWA_ConfigFlipFlopTo1(pLu, pInitStruct->eLgNum);
        }
        else
        {
            /* Configure the output of flip-flop as "0" */
            LU_HWA_ConfigFlipFlopTo0(pLu, pInitStruct->eLgNum);
        }
        /* Flip-Flop initial output enable control */
        LU_HWA_EnableControlFlipFlopInitOutput(pLu, pInitStruct->eLgNum);
    }

    /* set input filter sample count for AOI0 */
    LU_HWA_SetAOI0InputFilterSampleCount(pLu, pInitStruct->eLgNum, (uint32_t)pInitStruct->u8Aoi0FiltCnt);
    /* set input filter sample period for AOI0 */
    LU_HWA_SetAOI0InputFilterSamplePeriod(pLu, pInitStruct->eLgNum, (uint32_t)pInitStruct->u8Aoi0Period);
    /* set input filter sample count for AOI1 */
    LU_HWA_SetAOI1InputFilterSampleCount(pLu, pInitStruct->eLgNum, (uint32_t)pInitStruct->u8Aoi1FiltCnt);
    /* set input filter sample period for AOI0 */
    LU_HWA_SetAOI1InputFilterSamplePeriod(pLu, pInitStruct->eLgNum, (uint32_t)pInitStruct->u8Aoi1Period);

    return eRet;
}

/**
 * @brief De-initialize Lu instance
 * @param eLu LU instance
 */
void LU_Deinit()
{
    uint8_t u8Index;
    LU_Type* pLu = NULL_PTR;

    for (u8Index = 0U; u8Index < (uint8_t)LG_CNT; u8Index++)
    {
        /* set AOI0 value */
        LU_HWA_ConfigAOI0(pLu, (LU_LgType)u8Index, 0U);
        /* set AOI1 value */
        LU_HWA_ConfigAOI1(pLu, (LU_LgType)u8Index, 0U);
        /* set CTRL value */
        LU_HWA_ConfigCtrl(pLu, (LU_LgType)u8Index, 0U);
        /* set FILT value */
        LU_HWA_ConfigFilter(pLu, (LU_LgType)u8Index, 0U);
    }
}


