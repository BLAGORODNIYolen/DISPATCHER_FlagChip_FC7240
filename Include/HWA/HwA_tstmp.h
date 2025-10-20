/**
 * @file HwA_tstmp.h
 * @author Flagchip
 * @brief FC7xxx TSTMP hardware access layer
 * @version 0.1.0
 * @date 2024-01-14
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

/********************************************************************************
 *   Revision History:
 *
 *   Version     Date          Initials       CR#          Descriptions
 *   ---------   ----------    ------------   ----------   ---------------
 *   0.1.0      2024-01-14    Flagchip0122     N/A          FC7xxx internal release version
 ********************************************************************************/


#ifndef _HWA_TSTMP_H_
#define _HWA_TSTMP_H_

#include "device_header.h"
/********* Local typedef ************/
/** @brief Tstmp modulate number */
typedef enum
{
    TSTMP_MOD0 = 0U,
    TSTMP_MOD1,
    TSTMP_MOD2,
    TSTMP_MOD3,
} TSTMP_ModulateType;

/** @brief Tstmp running mode */
typedef enum
{
    TSTMP_MODE_ALWAYS_RUNNING = 0U,
    TSTMP_MODE_PERIOD_RUNNING = 1U
} TSTMP_ModeCounterRunningMode;

typedef enum
{
    TSTMP_SIRC1M_CLK = 0U,
    TSTMP_AON_CLK = 1U
} TSTMP_ClockSourceType;
/********* Local inline function ************/
/**
 * @brief Read TSTMP value
 *
 * @param pTstmp TSTMP instance
 * @return TSTMP value
 */
LOCAL_INLINE uint64_t TSTMP_HWA_ReadTstmpValue(TSTMP_Type *pTstmp)
{
    uint32_t u32TstmpL, u32TstmpH;
    uint64_t u64TempValue;
    u32TstmpL = pTstmp->VALL;
    u32TstmpH = pTstmp->VALH;

    u64TempValue = u32TstmpH;
    u64TempValue = (u64TempValue << 32U) + u32TstmpL;
    return u64TempValue;
}

/**
 * @brief Read TSTMP interrupt enable bits
 *
 * @param pTstmp TSTMP instance
 * @return TSTMP interrupt enable bits
 */
LOCAL_INLINE uint32_t TSTMP_HWA_ReadTstmpInterruptEnable(TSTMP_Type *pTstmp)
{
    return (uint32_t)pTstmp->MOD_INTEN;
}

/**
 * @brief Enable TSTMP MOD(n) match interrupt
 *
 * @param pTstmp TSTMP instance
 * @param eMod MOD number
 */
LOCAL_INLINE void TSTMP_HWA_EnableModMatchInterrupt(TSTMP_Type *pTstmp, TSTMP_ModulateType eMod)
{
    pTstmp->MOD_INTEN |= ((uint32_t)1U << (uint32_t)eMod);
}

/**
 * @brief Disable TSTMP MOD(n) match interrupt
 *
 * @param pTstmp TSTMP instance
 * @param eMod MOD number
 */
LOCAL_INLINE void TSTMP_HWA_DisableModMatchInterrupt(TSTMP_Type *pTstmp, TSTMP_ModulateType eMod)
{
    pTstmp->MOD_INTEN &= ~((uint32_t)1U << (uint32_t)eMod);
}

/**
 * @brief Set the counting modes of TSTMP MOD(n)
 *
 * @param pTstmp TSTMP instance
 * @param eMod MOD number
 * @param eCounterMode Counting mode set
 */
LOCAL_INLINE void TSTMP_HWA_SetModCounterMode(TSTMP_Type *pTstmp, TSTMP_ModulateType eMod, TSTMP_ModeCounterRunningMode eCounterMode)
{
    pTstmp->MOD_INTEN = (pTstmp->MOD_INTEN & ~((uint32_t)0x100U << (uint32_t)eMod)) |
            (((uint32_t)eCounterMode << TSTMP_MOD_INTEN_MOD0_MODE_SHIFT) << (uint32_t)eMod);
}

/**
 * @brief Enable TSTMP MOD(n) counter
 *
 * @param pTstmp TSTMP instance
 * @param eMod MOD number
 */
LOCAL_INLINE void TSTMP_HWA_EnableModCounter(TSTMP_Type *pTstmp, TSTMP_ModulateType eMod)
{
    pTstmp->MOD_INTEN |= (TSTMP_MOD_INTEN_MOD0_ENABLE_MASK << (uint32_t)eMod);
}

/**
 * @brief Disable TSTMP MOD(n) counter
 *
 * @param pTstmp TSTMP instance
 * @param eMod MOD number
 */
LOCAL_INLINE void TSTMP_HWA_DisableModCounter(TSTMP_Type *pTstmp, TSTMP_ModulateType eMod)
{
    pTstmp->MOD_INTEN &= ~(TSTMP_MOD_INTEN_MOD0_ENABLE_MASK << (uint32_t)eMod);
}

/**
 * @brief Select TSTMP MOD(n) clock source
 *
 * @param pTstmp TSTMP instance
 * @param eMod MOD number
 */
LOCAL_INLINE void TSTMP_HWA_SelectClkSource(TSTMP_Type *pTstmp, TSTMP_ModulateType eMod, TSTMP_ClockSourceType eClk)
{
    pTstmp->MOD_INTEN |= (((uint32_t)eClk) << (TSTMP_MOD_INTEN_MOD0_CLK_SHIFT + (uint32_t)eMod));
}

/**
 * @brief Read TSTMP all MOD match flag
 *
 * @param pTstmp TSTMP instance
 * @return TSTMP all MOD match flag
 */
LOCAL_INLINE uint32_t TSTMP_HWA_ReadModMatchFlag(TSTMP_Type *pTstmp)
{
    return ((uint32_t)(pTstmp->MOD_STATUS) & (uint32_t)(TSTMP_MOD_STATUS_MOD0_MATCH_MASK | TSTMP_MOD_STATUS_MOD1_MATCH_MASK
                                                        | TSTMP_MOD_STATUS_MOD2_MATCH_MASK | TSTMP_MOD_STATUS_MOD3_MATCH_MASK));
}

/**
 * @brief Clear TSTMP all MOD(0) match flag
 *
 * @param pTstmp TSTMP instance
 */
LOCAL_INLINE void TSTMP_HWA_ClearMod0MatchFlag(TSTMP_Type *pTstmp)
{
    pTstmp->MOD_STATUS = (uint32_t)(TSTMP_MOD_STATUS_MOD0_MATCH_MASK);
}

/**
 * @brief Clear TSTMP all MOD(1,2,3) match flag
 *
 * @param pTstmp TSTMP instance
 */
LOCAL_INLINE void TSTMP_HWA_ClearAllMod123MatchFlag(TSTMP_Type *pTstmp)
{
    pTstmp->MOD_STATUS = (uint32_t)(TSTMP_MOD_STATUS_MOD1_MATCH_MASK | TSTMP_MOD_STATUS_MOD2_MATCH_MASK |
                                    TSTMP_MOD_STATUS_MOD3_MATCH_MASK);
}

/**
 * @brief Clear TSTMP single MOD(1,2,3) match flag
 *
 * @param pTstmp TSTMP instance
 * @param eMod MOD number
 */
LOCAL_INLINE void TSTMP_HWA_ClearSingleMod123MatchFlag(TSTMP_Type *pTstmp, TSTMP_ModulateType eMod)
{
    pTstmp->MOD_STATUS = ((uint32_t)1U << (uint32_t)eMod);
}

/**
 * @brief Set MOD match value
 *
 * @param pTstmp TSTMP instance
 * @param eMod MOD number
 * @param u32ModValue MOD value
 */
LOCAL_INLINE void TSTMP_HWA_SetModMatchValue(TSTMP_Type *pTstmp, TSTMP_ModulateType eMod, uint32_t u32ModValue)
{
    switch(eMod)
    {
        case TSTMP_MOD0:
            pTstmp->MOD0_SETVAL = u32ModValue;
        break;

        case TSTMP_MOD1:
            pTstmp->MOD1_SETVAL = u32ModValue;
        break;

        case TSTMP_MOD2:
            pTstmp->MOD2_SETVAL = u32ModValue;
        break;

        case TSTMP_MOD3:
            pTstmp->MOD3_SETVAL = u32ModValue;
        break;

        default:
            break;
    }
}

#endif /* #ifndef _HWA_TSTMP_H_ */
