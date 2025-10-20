/**
 * @file fc7xxx_driver_tstmp.c
 * @author Flagchip
 * @brief FC7xxx TSTMP driver source code
 * @version 0.1.0
 * @date 2024-01-14
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
*   0.1.0      2024-01-14    Flagchip0122    N/A          FC7xxx internal release version
********************************************************************************/

#include "fc7xxx_driver_tstmp.h"
#include "interrupt_manager.h"

/** @brief Tstmp instance list */
static TSTMP_Type *s_pTstmpPtrs[TSTMP_INSTANCE_COUNT] = TSTMP_BASE_PTRS;
/** @brief Tstmp user defined interrupt function */
static TSTMP_InterruptCallBackType s_pTstmpModulateNotifyPtr[TSTMP_INSTANCE_COUNT][MAX_MOD_NUMBER] = {NULL};

/** @brief TSTMP0 interrupt entry */
void TSTMP0_IRQHandler(void);
/** @brief TSTMP1 interrupt entry */
void TSTMP1_IRQHandler(void);

/** @brief TSTMP common interrupt function */
static void Tstmp_CommonProcessInterrupt(const TSTMP_InstanceType eInstance, const TSTMP_ModulateType eIntModulate);

/**
 * @brief Initialize TSTMP instance
 *
 * @param eInstance TSTMP instance
 * @param pInitStruct TSTMP initialization structure
 * @return TSTMP_StatusType TSTMP return type
 * @note TSTMP0 clock source is 1MHZ and TSTMP1,TSTMP2,TSTMP3 clock source is bus clock
 */
TSTMP_StatusType TSTMP_Init(const TSTMP_InstanceType eInstance, const TSTMP_InitType *const pInitStruct)
{
    TSTMP_Type *pTstmp;
    TSTMP_StatusType eRet = TSTMP_STATUS_SUCCESS;
    if ((NULL == pInitStruct) || (eInstance >= TSTMP_INSTANCE_MAX))
    {
        eRet = TSTMP_STATUS_PARAM_INVALID;
    }
    else
    {
        pTstmp = s_pTstmpPtrs[eInstance];
        /* clear MOD(n) match flag */
        TSTMP_HWA_ClearMod0MatchFlag(pTstmp);
        TSTMP_HWA_ClearAllMod123MatchFlag(pTstmp);

        for(uint8_t i = 0; i < MAX_MOD_NUMBER; i++)
        {
            TSTMP_HWA_SelectClkSource(pTstmp, (TSTMP_ModulateType)i, pInitStruct->pClk[i]);
        }
        /* set MOD0 match value */
        TSTMP_HWA_SetModMatchValue(pTstmp, TSTMP_MOD0, pInitStruct->u32Modulate0Value);
        /* set MOD1 match value */
        TSTMP_HWA_SetModMatchValue(pTstmp, TSTMP_MOD1, pInitStruct->u32Modulate1Value);
        /* set MOD2 match value */
        TSTMP_HWA_SetModMatchValue(pTstmp, TSTMP_MOD2, pInitStruct->u32Modulate2Value);
        /* set MOD3 match value */
        TSTMP_HWA_SetModMatchValue(pTstmp, TSTMP_MOD3, pInitStruct->u32Modulate3Value);
    }

    return eRet;
}

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
        const TSTMP_ModeCounterRunningMode eCounter3Mode)
{
    TSTMP_Type *pTstmp;
    TSTMP_StatusType eRet = TSTMP_STATUS_SUCCESS;
    if (eInstance >= TSTMP_INSTANCE_MAX)
    {
        eRet = TSTMP_STATUS_PARAM_INVALID;
    }
    if( (eCounter0Mode > TSTMP_MODE_PERIOD_RUNNING) || (eCounter1Mode > TSTMP_MODE_PERIOD_RUNNING) ||
        (eCounter2Mode > TSTMP_MODE_PERIOD_RUNNING) || (eCounter3Mode > TSTMP_MODE_PERIOD_RUNNING))
    {
        eRet = TSTMP_STATUS_PARAM_INVALID;
    }
    if(eRet == TSTMP_STATUS_SUCCESS)
    {
        pTstmp = s_pTstmpPtrs[eInstance];
        TSTMP_HWA_SetModCounterMode(pTstmp,TSTMP_MOD0, eCounter0Mode);
        TSTMP_HWA_SetModCounterMode(pTstmp,TSTMP_MOD1, eCounter1Mode);
        TSTMP_HWA_SetModCounterMode(pTstmp,TSTMP_MOD2, eCounter2Mode);
        TSTMP_HWA_SetModCounterMode(pTstmp,TSTMP_MOD3, eCounter3Mode);
    }
    return eRet;
}
/**
 * @brief De-initialize TSTMP instance
 *
 * @param eInstance TSTMP instance
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_Deinit(const TSTMP_InstanceType eInstance)
{
    TSTMP_Type *pTstmp;
    TSTMP_StatusType eRet = TSTMP_STATUS_SUCCESS;
    uint8_t u8Index;
    if (eInstance >= TSTMP_INSTANCE_MAX)
    {
        eRet = TSTMP_STATUS_PARAM_INVALID;
    }
    else
    {
        pTstmp = s_pTstmpPtrs[eInstance];
        for (u8Index = 0U; u8Index < MAX_MOD_NUMBER; u8Index++)
        {
            /* Disable TSTMP MOD(n) match interrupt */
            TSTMP_HWA_DisableModMatchInterrupt(pTstmp, (TSTMP_ModulateType)u8Index);
            /* Disable TSTMP MOD(n) counter */
            TSTMP_HWA_DisableModCounter(pTstmp, (TSTMP_ModulateType)u8Index);
            /* Clear TSTMP MOD(n) match value set*/
            TSTMP_HWA_SetModMatchValue(pTstmp, (TSTMP_ModulateType)u8Index, (uint32_t)0U);
            s_pTstmpModulateNotifyPtr[eInstance][u8Index] = NULL;
        }
        /* clear MOD(n) match flag */
        TSTMP_HWA_ClearMod0MatchFlag(pTstmp);
        TSTMP_HWA_ClearAllMod123MatchFlag(pTstmp);
    }
    return eRet;
}

/**
 * @brief Initialize TSTMP interrupt functionality
 *
 * @param eInstance TSTMP instance
 * @param pIntStruct TSTMP interrupt structure
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_InitInterrupt(const TSTMP_InstanceType eInstance, const TSTMP_IntType *const pIntStruct)
{
    TSTMP_StatusType eRet = TSTMP_STATUS_SUCCESS;
    TSTMP_Type *pTstmp;
    uint8_t u8Index;
    if ((NULL == pIntStruct) || (eInstance >= TSTMP_INSTANCE_MAX))
    {
        eRet = TSTMP_STATUS_PARAM_INVALID;
    }
    else
    {
        pTstmp = s_pTstmpPtrs[eInstance];
        for (u8Index = 0U; u8Index < MAX_MOD_NUMBER; u8Index++)
        {
            if (pIntStruct->bModulateIntEn[u8Index] == true)
            {
                /* Enable TSTMP MOD(n) match interrupt */
                TSTMP_HWA_EnableModMatchInterrupt(pTstmp, (TSTMP_ModulateType)u8Index);
                s_pTstmpModulateNotifyPtr[eInstance][u8Index] = pIntStruct->pIsrModNotify[u8Index];
            }
            else
            {
                /* Disable TSTMP MOD(n) match interrupt */
                TSTMP_HWA_DisableModMatchInterrupt(pTstmp, (TSTMP_ModulateType)u8Index);
                s_pTstmpModulateNotifyPtr[eInstance][u8Index] = NULL;
            }
        }
    }
    return eRet;
}

/**
 * @brief Enable TSTMP interrupt function
 *
 * @param eInstance TSTMP instance
 * @param eMod TSTMP modulate enumeration
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_EnableInterrupt(const TSTMP_InstanceType eInstance, const TSTMP_ModulateType eMod)
{
    TSTMP_StatusType eRet = TSTMP_STATUS_SUCCESS;
    TSTMP_Type *pTstmp;
    if (((uint8_t)eMod >= MAX_MOD_NUMBER) || (eInstance >= TSTMP_INSTANCE_MAX))
    {
        eRet = TSTMP_STATUS_PARAM_INVALID;
    }
    else
    {
        pTstmp = s_pTstmpPtrs[eInstance];
        /* Enable TSTMP MOD(n) match interrupt */
        TSTMP_HWA_EnableModMatchInterrupt(pTstmp, eMod);
    }

    return eRet;
}

/**
 * @brief Disable TSTMP interrupt function
 *
 * @param eInstance TSTMP instance
 * @param eMod TSTMP modulate enumeration
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_DisableInterrupt(const TSTMP_InstanceType eInstance, const TSTMP_ModulateType eMod)
{
    TSTMP_StatusType eRet = TSTMP_STATUS_SUCCESS;
    TSTMP_Type *pTstmp;
    if (((uint8_t)eMod >= MAX_MOD_NUMBER) || (eInstance >= TSTMP_INSTANCE_MAX))
    {
        eRet = TSTMP_STATUS_PARAM_INVALID;
    }
    else
    {
        pTstmp = s_pTstmpPtrs[eInstance];
        /* Disable TSTMP MOD(n) match interrupt */
        TSTMP_HWA_DisableModMatchInterrupt(pTstmp, eMod);
    }

    return eRet;
}

/**
 * @brief Get TSTMP count value
 *
 * @param eInstance TSTMP instance
 * @param u64TstmpValue in/out value
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_GetTstmpValue(const TSTMP_InstanceType eInstance, uint64_t *const u64TstmpValue)
{
    TSTMP_StatusType eRet = TSTMP_STATUS_SUCCESS;
    TSTMP_Type *pTstmp;
    if ((NULL == u64TstmpValue) || (eInstance >= TSTMP_INSTANCE_MAX))
    {
        eRet = TSTMP_STATUS_PARAM_INVALID;
    }
    else
    {
        pTstmp = s_pTstmpPtrs[eInstance];
        *u64TstmpValue = TSTMP_HWA_ReadTstmpValue(pTstmp);
    }
    return eRet;
}

/**
 * @brief Update Modulate configuration
 *
 * @param eInstance TSTMP instance
 * @param pUpdateStruct TSTMP update structure pointer
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_UpdateMod(const TSTMP_InstanceType eInstance, const TSTMP_UpdateType *const pUpdateStruct)
{
    TSTMP_StatusType eRet = TSTMP_STATUS_SUCCESS;
    TSTMP_Type *pTstmp;
    bool bIntEnStatus;
    if ((NULL == pUpdateStruct) || (eInstance >= TSTMP_INSTANCE_MAX))
    {
        eRet = TSTMP_STATUS_PARAM_INVALID;
    }
    else
    {
        pTstmp = s_pTstmpPtrs[eInstance];
        /* Clear MOD(n) interrupt flag */
        if (TSTMP_MOD0 == pUpdateStruct->eMod)
        {
            TSTMP_HWA_ClearMod0MatchFlag(pTstmp);
        }
        else
        {
            TSTMP_HWA_ClearSingleMod123MatchFlag(pTstmp, pUpdateStruct->eMod);
        }
        bIntEnStatus = (bool)(((uint32_t)0U == (TSTMP_HWA_ReadTstmpInterruptEnable(pTstmp) & 
                                                TSTMP_MOD_INTEN_MOD0_INTEN_MASK << (pUpdateStruct->eMod))) ? true : false);
        if ((pUpdateStruct->bIntEn) == true)
        {
            if(bIntEnStatus == true)
            {
                /* Enable TSTMP MOD(n) match interrupt */
                TSTMP_HWA_EnableModMatchInterrupt(pTstmp, pUpdateStruct->eMod);
                if (NULL != pUpdateStruct->pIsrModNotify)
                {
                    s_pTstmpModulateNotifyPtr[eInstance][pUpdateStruct->eMod] = pUpdateStruct->pIsrModNotify;
                }
            }
        }else
        {
            if(bIntEnStatus == false)
            {
                /* Disable TSTMP MOD(n) match interrupt */
                TSTMP_HWA_DisableModMatchInterrupt(pTstmp, pUpdateStruct->eMod);
            }
        }
        /* set MOD(n) match value */
        TSTMP_HWA_SetModMatchValue(pTstmp, pUpdateStruct->eMod, pUpdateStruct->u32ModValue);
    }
    return eRet;
}

/**
 * @brief Set counter MOD(n) counting on or off
 *
 * @param eInstance TSTMP instance
 * @param eMod MOD number
 * @param bCounterEn Whether enable the selected Modulate Timer Counter
 * @return TSTMP_StatusType TSTMP return type
 */
TSTMP_StatusType TSTMP_SetModCountConfig(const TSTMP_InstanceType eInstance, const TSTMP_ModulateType eMod, const bool bCounterEn)
{
    TSTMP_StatusType eRet = TSTMP_STATUS_SUCCESS;
    TSTMP_Type *pTstmp;
    if (eInstance >= TSTMP_INSTANCE_MAX || eMod > TSTMP_MOD3)
    {
        eRet = TSTMP_STATUS_PARAM_INVALID;
    }
    else
    {
        pTstmp = s_pTstmpPtrs[eInstance];
        if(bCounterEn)
        {
            TSTMP_HWA_EnableModCounter(pTstmp, eMod);
        }else
        {
            TSTMP_HWA_DisableModCounter(pTstmp, eMod);
        }
    }
    return eRet;
}

/**
 * @brief TSTMP common interrupt function
 *
 * @param eInstance TSTMP instance
 * @param eIntModulate TSTMP modulate
 */
static void Tstmp_CommonProcessInterrupt(const TSTMP_InstanceType eInstance, const TSTMP_ModulateType eIntModulate)
{
    if (NULL != s_pTstmpModulateNotifyPtr[eInstance][eIntModulate])
    {
        s_pTstmpModulateNotifyPtr[eInstance][eIntModulate]();
    }
}

/**
 * @brief TSTMP0 interrupt handler entry
 *
 */
void TSTMP0_IRQHandler(void)
{
    uint32_t u32TstmpStatus = TSTMP_HWA_ReadModMatchFlag(TSTMP0);
    if ((u32TstmpStatus & TSTMP_MOD_STATUS_MOD0_MATCH_MASK)>>TSTMP_MOD_STATUS_MOD0_MATCH_SHIFT == 1U)
    {
        Tstmp_CommonProcessInterrupt(TSTMP_INSTANCE_0, TSTMP_MOD0);
        /* Clear MOD0 interrupt flag */
        TSTMP_HWA_ClearMod0MatchFlag(TSTMP0);
    }
    if ((u32TstmpStatus & TSTMP_MOD_STATUS_MOD1_MATCH_MASK)>>TSTMP_MOD_STATUS_MOD1_MATCH_SHIFT == 1U)
    {
        Tstmp_CommonProcessInterrupt(TSTMP_INSTANCE_0, TSTMP_MOD1);
        /* Clear MOD1 interrupt flag */
        TSTMP_HWA_ClearSingleMod123MatchFlag(TSTMP0, TSTMP_MOD1);
    }
    if ((u32TstmpStatus & TSTMP_MOD_STATUS_MOD2_MATCH_MASK)>>TSTMP_MOD_STATUS_MOD2_MATCH_SHIFT == 1U)
    {
        Tstmp_CommonProcessInterrupt(TSTMP_INSTANCE_0, TSTMP_MOD2);
        /* Clear MOD2 interrupt flag */
        TSTMP_HWA_ClearSingleMod123MatchFlag(TSTMP0, TSTMP_MOD2);
    }
    if ((u32TstmpStatus & TSTMP_MOD_STATUS_MOD3_MATCH_MASK)>>TSTMP_MOD_STATUS_MOD3_MATCH_SHIFT == 1U)
    {
        Tstmp_CommonProcessInterrupt(TSTMP_INSTANCE_0, TSTMP_MOD3);
        /* Clear MOD3 interrupt flag */
        TSTMP_HWA_ClearSingleMod123MatchFlag(TSTMP0, TSTMP_MOD3);
    }
}

/**
 * @brief TSTMP1 interrupt handler entry
 *
 */
void TSTMP1_IRQHandler(void)
{
    uint32_t u32TstmpStatus = TSTMP_HWA_ReadModMatchFlag(TSTMP1);
    if ((u32TstmpStatus & TSTMP_MOD_STATUS_MOD0_MATCH_MASK)>>TSTMP_MOD_STATUS_MOD0_MATCH_SHIFT == 1U)
    {
        Tstmp_CommonProcessInterrupt(TSTMP_INSTANCE_1, TSTMP_MOD0);
        /* Clear MOD0 interrupt flag */
        TSTMP_HWA_ClearMod0MatchFlag(TSTMP1);
    }
    if ((u32TstmpStatus & TSTMP_MOD_STATUS_MOD1_MATCH_MASK)>>TSTMP_MOD_STATUS_MOD1_MATCH_SHIFT == 1U)
    {
        Tstmp_CommonProcessInterrupt(TSTMP_INSTANCE_1, TSTMP_MOD1);
        /* Clear MOD1 interrupt flag */
        TSTMP_HWA_ClearSingleMod123MatchFlag(TSTMP1, TSTMP_MOD1);
    }
    if ((u32TstmpStatus & TSTMP_MOD_STATUS_MOD2_MATCH_MASK)>>TSTMP_MOD_STATUS_MOD2_MATCH_SHIFT == 1U)
    {
        Tstmp_CommonProcessInterrupt(TSTMP_INSTANCE_1, TSTMP_MOD2);
        /* Clear MOD2 interrupt flag */
        TSTMP_HWA_ClearSingleMod123MatchFlag(TSTMP1, TSTMP_MOD2);
    }
    if ((u32TstmpStatus & TSTMP_MOD_STATUS_MOD3_MATCH_MASK)>>TSTMP_MOD_STATUS_MOD3_MATCH_SHIFT == 1U)
    {
        Tstmp_CommonProcessInterrupt(TSTMP_INSTANCE_1, TSTMP_MOD3);
        /* Clear MOD3 interrupt flag */
        TSTMP_HWA_ClearSingleMod123MatchFlag(TSTMP1, TSTMP_MOD3);
    }
}
