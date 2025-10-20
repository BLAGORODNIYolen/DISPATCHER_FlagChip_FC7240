/**
 * @file HwA_cordic.h
 * @author Flagchip
 * @brief Hardware access layer for Cordic
 * @version 0.1.0
 * @date 2024-01-11
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-11    Flagchip054   N/A          First version for FC7240
   ******************************************************************************** */
#ifndef _HWA_CORDIC_H_
#define _HWA_CORDIC_H_
#include "device_header.h"

typedef enum
{
	CORDIC_Iteration_8 = 0,
	CORDIC_Iteration_16,
	CORDIC_Iteration_24
}CORDIC_IterationType;

typedef enum
{
	CORDIC_Trigonometric = 0,
	CORDIC_Hyperbolic,
	CORDIC_Linear
}CORDIC_SystemType;

typedef enum
{
	CORDIC_Rotate = 0,
	CORDIC_Vector
}CORDIC_ModeType;


#define CORDIC_CTR_VAL(s,a,b,c,d)  (CORDIC_CTRL_SCALE(s) | CORDIC_CTRL_IE(a) | CORDIC_CTRL_ITER(b) | CORDIC_CTRL_OS(c) |  CORDIC_CTRL_MODE(d))
/**
 * @brief Set Cordic module Ctrl register
 *
 * @param u32Value Ctrl register value
 */
LOCAL_INLINE void Cordic_HWA_SetCtrl(uint32_t u32Value)
{
	CORDIC->CTRL = u32Value;
}

/**
 * @brief Read Cordic module Ctrl register
 *
 * @return Ctrl register value
 */
LOCAL_INLINE uint32_t Cordic_HWA_GetCtrl(void)
{
    return (uint32_t)(CORDIC->CTRL);
}

/**
 * @brief Set Cordic module XInput register
 *
 * @param u32Value XInput register value
 */
LOCAL_INLINE void Cordic_HWA_Set_XInput(int32_t u32Value)
{
	CORDIC->X_INPUT = (uint32_t)u32Value;
}

/**
 * @brief Set Cordic module YInput register
 *
 * @param u32Value YInput register value
 */
LOCAL_INLINE void Cordic_HWA_Set_YInput(int32_t u32Value)
{
	CORDIC->Y_INPUT = (uint32_t)u32Value;
}

/**
 * @brief Set Cordic module ZInput register
 *
 * @param u32Value ZInput register value
 */
LOCAL_INLINE void Cordic_HWA_Set_ZInput(int32_t u32Value)
{
	CORDIC->Z_INPUT = (uint32_t)u32Value;
}

/**
 * @brief Read Cordic module XOutput register
 *
 * @return XOutput register value
 */
LOCAL_INLINE uint32_t Cordic_HWA_Get_XOutput(void)
{
    return (uint32_t)(CORDIC->X_OUTPUT);
}

/**
 * @brief Read Cordic module YOutput register
 *
 * @return YOutput register value
 */
LOCAL_INLINE uint32_t Cordic_HWA_Get_YOutput(void)
{
    return (uint32_t)(CORDIC->Y_OUTPUT);
}

/**
 * @brief Read Cordic module ZOutput register
 *
 * @return ZOutput register value
 */
LOCAL_INLINE uint32_t Cordic_HWA_Get_ZOutput(void)
{
    return (uint32_t)(CORDIC->Z_OUTPUT);
}

/**
 * @brief Read Cordic module state
 *
 * @return Cordic module current state
 */
LOCAL_INLINE bool Cordic_HWA_Get_Stat(void)
{
    return (bool)(CORDIC->STAT & CORDIC_STAT_DONE_MASK);
}

#endif
