/**
 * @file HwA_pcc.h
 * @author Flagchip085
 * @brief FC7xxx PCC register API
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-12    Flagchip085   N/A          First version for FC7240
   ******************************************************************************** */
#ifndef HWA_INCLUDE_HWA_PCC_H_
#define HWA_INCLUDE_HWA_PCC_H_
#include "device_header.h"

/**
 * @defgroup HwA_pcc
 * @ingroup HwA_pcc
 * @{
 */

/** @brief Marco for PCCn Bit Field definition */
#define PCC_CGC_MASK                        0x800000U
#define PCC_CGC_SHIFT                       23U
#define PCC_CGC_WIDTH                       1U
#define PCC_CGC(x)                          (((uint32_t)(((uint32_t)(x))<<PCC_CGC_SHIFT))&PCC_CGC_MASK)
#define PCC_GetCGC(x)                       ((((uint32_t)(x))&PCC_CGC_MASK)>>PCC_CGC_SHIFT)

#define PCC_SEL_MASK                        0x700000U
#define PCC_SEL_SHIFT                       20U
#define PCC_SEL_WIDTH                       3U
#define PCC_SEL(x)                          (((uint32_t)(((uint32_t)(x))<<PCC_SEL_SHIFT))&PCC_SEL_MASK)
#define PCC_GetSEL(x)                       ((((uint32_t)(x))&PCC_SEL_MASK)>>PCC_SEL_SHIFT)

#define PCC_DIV_MASK                        0x7U
#define PCC_DIV_SHIFT                       0U
#define PCC_DIV_WIDTH                       3U
#define PCC_DIV(x)                          (((uint32_t)(((uint32_t)(x))<<PCC_DIV_SHIFT))&PCC_DIV_MASK)
#define PCC_GetDIV(x)                       ((((uint32_t)(x))&PCC_DIV_MASK)>>PCC_DIV_SHIFT)

#define PCC_SWR_MASK                        0x10000u

/**
 * @brief defined the clock source for function clock,match with PCC_XXX[SEL] bit filed.
 */
typedef enum
{
    PCC_CLKGATE_SRC_OFF_OR_TCLK	= 0U,
    PCC_CLKGATE_SRC_FOSCDIV    	= 1U,
    PCC_CLKGATE_SRC_SIRCDIV  	= 2U,
    PCC_CLKGATE_SRC_FIRCDIV    	= 3U,
    PCC_CLKGATE_SRC_RESERVE0   	= 4U,
    PCC_CLKGATE_SRC_PLL1DIV   	= 5U,
    PCC_CLKGATE_SRC_PLL0DIV    	= 6U,
    PCC_CLKGATE_SRC_RESERVE1   	= 7U,
    PCC_CLKGATE_UNINVOLVED     	= 8U
} PCC_ClkGateSrcType;

/**
 * @brief define the clock divider,match with PCC_XXX[DIV] bit filed.
 */
typedef enum
{
    PCC_CLK_DIV_BY1     = 0U,             /*!< Divide by 1 (pass-through, no clock divide) */
    PCC_CLK_DIV_BY2     = 1U,             /*!< Divide by 2 */
    PCC_CLK_DIV_BY3     = 2U,             /*!< Divide by 3 */
    PCC_CLK_DIV_BY4     = 3U,             /*!< Divide by 4 */
    PCC_CLK_DIV_BY5     = 4U,             /*!< Divide by 5 */
    PCC_CLK_DIV_BY6     = 5U,             /*!< Divide by 6 */
    PCC_CLK_DIV_BY7     = 6U,             /*!< Divide by 7 */
    PCC_CLK_DIV_BY8     = 7U,             /*!< Divide by 8 */
    PCC_CLK_UNINVOLVED  = 8U              /*!< Current peripheral dose not contain DIV configuration */
} PCC_ClkDivType;


/**
 * @brief Get PCC register value
 *
 * @param u32Offset the PCC register offset
 * @return uint32_t PCC register value
 */
LOCAL_INLINE uint32_t PCC_HWA_GetRegister(uint32_t u32Offset)
{
    return *((uint32_t *)((uint32_t)PCC_BASE + u32Offset));
}

/**
 * @brief Set PCC register value
 *
 * @param u32Offset the PCC register offset
 * @param eValue  value to set
 */
LOCAL_INLINE void PCC_HWA_SetRegister(uint32_t u32Offset,uint32_t eValue)
{
    *((uint32_t *)((uint32_t)PCC_BASE + u32Offset)) = eValue;
}

/**
 * @brief Get PCC clock gate control
 *
 * @param u32Offset the PCC register offset
 * @return bool PCC clock enabled or disabled
 */
LOCAL_INLINE bool PCC_HWA_GetClockGateControl(uint32_t u32Offset)
{
	uint32_t u32Value = *((uint32_t *)((uint32_t)PCC_BASE + u32Offset));
    return (bool)PCC_GetCGC(u32Value);
}

/**
 * @brief Set PCC clock gate control
 *
 * @param u32Offset the PCC register offset
 * @param eSrc  PCC clock source
 */
LOCAL_INLINE void PCC_HWA_SetClockGateControl(uint32_t u32Offset,bool  bEnable)
{
	uint32_t *pRegister = (uint32_t *)((uint32_t)PCC_BASE + u32Offset);
	*pRegister = ((*pRegister) & (~PCC_CGC_MASK)) | PCC_CGC(bEnable);
}

/**
 * @brief Get PCC clock source
 *
 * @param u32Offset the PCC register offset
 * @return PCC_ClkGateSrcType PCC clock source
 */
LOCAL_INLINE PCC_ClkGateSrcType PCC_HWA_GetClockSource(uint32_t u32Offset)
{
	uint32_t u32Value = *((uint32_t *)((uint32_t)PCC_BASE + u32Offset));
    return (PCC_ClkGateSrcType)PCC_GetSEL(u32Value);
}

/**
 * @brief Set PCC clock source
 *
 * @param u32Offset the PCC register offset
 * @param eSrc  PCC clock source
 */
LOCAL_INLINE void PCC_HWA_SetClockSource(uint32_t u32Offset,PCC_ClkGateSrcType eSrc)
{
	uint32_t *pRegister = (uint32_t *)((uint32_t)PCC_BASE + u32Offset);
	*pRegister = ((*pRegister) & (~PCC_SEL_MASK)) | PCC_SEL(eSrc);
}

/**
 * @brief PCC peripheral software reset
 *
 * @param u32Offset the PCC register offset
 */
LOCAL_INLINE void PCC_HWA_SoftwareReset(uint32_t u32Offset)
{
    *((uint32_t *)((uint32_t)PCC_BASE + u32Offset)) |= (uint32_t)PCC_SWR_MASK;
    *((uint32_t *)((uint32_t)PCC_BASE + u32Offset)) &= ~(uint32_t)PCC_SWR_MASK;
}

/**
 * @brief Get PCC divider
 *
 * @param u32Offset the PCC register offset
 * @return PCC_ClkDivType PCC clock divider
 */
LOCAL_INLINE PCC_ClkDivType PCC_HWA_GetDivider(uint32_t u32Offset)
{
	uint32_t u32Value = *((uint32_t *)((uint32_t)PCC_BASE + u32Offset));
    return (PCC_ClkDivType)PCC_GetDIV(u32Value);
}

/**
 * @brief Set PCC register value
 *
 * @param u32Offset the PCC register offset
 * @param eDivider  PCC clock divider
 */
LOCAL_INLINE void PCC_HWA_SetDivider(uint32_t u32Offset,PCC_ClkDivType eDivider)
{
	uint32_t *pRegister = (uint32_t *)((uint32_t)PCC_BASE + u32Offset);
	*pRegister = ((*pRegister) & (~PCC_DIV_MASK)) | PCC_DIV(eDivider);
}



/** @}*/

#endif /* HWA_INCLUDE_HWA_PCC_H_ */
