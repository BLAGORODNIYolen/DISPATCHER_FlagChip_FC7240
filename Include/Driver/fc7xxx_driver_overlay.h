/**
 * @file fc7xxx_driver_overlay.h
 * @author Flagchip
 * @brief FC7xxx overlay driver type definition and API
 * @version 0.1.0
 * @date 2023-12-25
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */

/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2023-12-25    Flagchip0038   N/A          First version for FC7240
********************************************************************************/

#ifndef _DRIVER_FC7XXX_DRIVER_OVERLAY_H_
#define _DRIVER_FC7XXX_DRIVER_OVERLAY_H_
#include "HwA_overlay.h"

/**
 * @addtogroup fc7xxx_driver_overlay
 * @{
 */


/**
 * @brief Overlay Error Information
 *
 */
typedef enum
{
    OVERLAY_ERROR_OK,         /**< no error                             */
    OVERLAY_ERROR_ADDR,       /**< error address                        */
    OVERLAY_ERROR_SIZE,       /**< error size                           */
    OVERLAY_ERROR_FLAG,       /**< error flag                           */
} OVERLAY_ErrorType;


/**
 * @brief Overlay Region parameters
 *
 */
typedef struct
{
	uint32_t                aOverlayRegionEn[OVERLYA_REGION_CNT];     /**< Overlay region enable array              */
	uint32_t                aOverlayRegionSrc[OVERLYA_REGION_CNT];    /**< Overlay region source array, pflash      */
	uint32_t                aOverlayRegionDst[OVERLYA_REGION_CNT];    /**< Overlay region destination array, sram   */
	OVERLAY_OverlaySizeType aOverlayRegionSize[OVERLYA_REGION_CNT];   /**< Overlay region size array                */
}OVERLAY_OverlayRegionInitType;

/**
 * @brief FAR parameter
 *
 */
typedef struct
{
	uint32_t u32FAREn;     /**< Overlay region enable array                                           */
	uint32_t u32FARDst;    /**< Overlay region destination array, pflash, source always is 0x08000000 */
	uint32_t u32FARSize;   /**< Overlay region size array, must align to 64KB                         */
}OVERLAY_FARInitType;


/**
 * @brief Error Info
 *
 */
typedef struct
{
	uint8_t bError_FAR_SIZE_INTR;          /**< bit 17, The FAR of size value is invalid */
	uint8_t bError_FAR_DST_OVERFLOW_INTR;  /**< bit 16, FAR of destination region is overflow with size */
	uint8_t bError_FAR_DST_NO_FLASH_INTR;  /**< bit 15, FAR of destination address is not flash */
	uint8_t bError_REGION2_D_CROS_INTR;    /**< bit 14, The range of region 2 destination address is crossed with other region */
	uint8_t bError_REGION2_S_CROS_INTR;    /**< bit 13, The range of region 2 source address is crossed with other region */
	uint8_t bError_REGION2_SIZE_INTR;      /**< bit 12, The region 2 of size value is invalid */
	uint8_t bError_REGION2_DST_INTR;       /**< bit 11, The region 2 of destination address is not aligned with size */
	uint8_t bError_REGION2_SRC_INTR;       /**< bit 10, The region 2 of source address is not aligned with size */
	uint8_t bError_REGION1_D_CROS_INTR;    /**< bit 9, The range of region 1 destination address is crossed with other region */
	uint8_t bError_REGION1_S_CROS_INTR;    /**< bit 8, The range of region 1 source address is crossed with other region */
	uint8_t bError_REGION1_SIZE_INTR;      /**< bit 7, The region 1 of size value is invalid */
	uint8_t bError_REGION1_DST_INTR;       /**< bit 6, The region 1 of destination address is not aligned with size */
	uint8_t bError_REGION1_SRC_INTR;       /**< bit 5, The region 1 of source address is not aligned with size */
	uint8_t bError_REGION0_D_CROS_INTR;    /**< bit 4, The range of region 0 destination address is crossed with other region */
	uint8_t bError_REGION0_S_CROS_INTR;    /**< bit 3, The range of region 0 source address is crossed with other region */
	uint8_t bError_REGION0_SIZE_INTR;      /**< bit 2, The region 0 of size value is invalid */
	uint8_t bError_REGION0_DST_INTR;       /**< bit 1, The region 0 of destination address is not aligned with size */
	uint8_t bError_REGION0_SRC_INTR;       /**< bit 0, The region 0 of source address is not aligned with size */
}OVERLAY_ErrorInfoType;


/** Overlay Setting Error callback type */
typedef void (*OVERLAY_ErrorCallback_Type)(OVERLAY_ErrorInfoType u16ErrorFlag);


/**
 * @brief Interrupt Parameter
 *
 */
typedef struct
{
	uint32_t                   bEnableInterrupt;  /**< Enable interrupt, 0 is disable, 1 is enable */
	OVERLAY_ErrorCallback_Type pCallBack;         /**< Callback function for error interrupt       */
}OVERLAY_InterruptType;


/**
 * @brief Overlay region initial function
 *
 * @param pOverlayInitCfg initial parameters
 * @return ERROR_OK is ok, others are not ok
 */
OVERLAY_ErrorType OVERLAY_RegionInit(OVERLAY_OverlayRegionInitType *pOverlayInitCfg);

/**
 * @brief De-Init Overlay Region
 *
 * @return ERROR_OK is ok, others are not ok
 */
OVERLAY_ErrorType OVERLAY_RegionDeInit(void);

/**
 * @brief Far initial function
 *
 * @param pFarInitCfg initial parameters
 * @return ERROR_OK is ok, others are not ok
 */
OVERLAY_ErrorType OVERLAY_FARInit(OVERLAY_FARInitType *pFarInitCfg);

/**
 * @brief De-Init FAR Region
 *
 * @return ERROR_OK is ok, others are not ok
 */
OVERLAY_ErrorType OVERLAY_FARDeInit(void);

/**
 * @brief Enable or Disable Interrupt
 *
 * @param pInterruptCfg interrupt config parameter
 */
void OVERLAY_SetInterrupt(OVERLAY_InterruptType *pInterruptCfg);

/**
 * @brief Get Error Info
 *
 * @param pErrorInfo error info point
 */
void OVERLAY_GetErrorInfo(OVERLAY_ErrorInfoType *pErrorInfo);

/**
 * @brief Clear Error Info
 *
 * @param pErrorInfo error info point
 */
void OVERLAY_ClrErrorInfo(OVERLAY_ErrorInfoType *pErrorInfo);

/**
 * @brief Call Me in Overlay Error interrupt handler
 *
 */
void OVERLAY_ErrorInterruptRoutine(void);


/** @}*/ /* fc7xxx_driver_overlay */


#endif


