/**
 * @file HwA_overlay.h
 * @author Flagchip
 * @brief  FC4xxx Overlay hardware access layer
 * @version 0.1.0
 * @date 2023-12-25
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */

/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2023-12-29    Flagchip0038   N/A          First version for FC7240
********************************************************************************/

#ifndef _HWA_OVERLAY_H_
#define _HWA_OVERLAY_H_

#include "device_header.h"

/**
 * @defgroup HwA_overlay
 * @ingroup fc7xxx_hwa_overlay
 * @{
 */


/** Overlay Region Count */
#define OVERLYA_REGION_CNT      3U

/** FAR source address */
#define OVERLAY_FAR_SRC         0x08000000U

/** FAR max size */
#define OVERLAY_FAR_SIZE_MAX    0x2000000U
/** FAR size align */
#define OVERLAY_FAR_SIZE_ALIGN  0x10000U
/** FAR size max mask **/
#define OVERLAY_FAR_SIZE_MASK   0xFFFFU

/**
 * @brief OVERlay Region size
 *
 */
typedef enum
{
	OVERLAY_OVERLAYSIZE_1KB  = 0x1,     /**< OVERLAY_OVERLAYSIZE_1KB, remapping overlay region size to 1KB          */
	OVERLAY_OVERLAYSIZE_2KB  = 0x2,     /**< OVERLAY_OVERLAYSIZE_2KB, remapping overlay region size to 2KB          */
	OVERLAY_OVERLAYSIZE_4KB  = 0x4,     /**< OVERLAY_OVERLAYSIZE_4KB, remapping overlay region size to 4KB          */
	OVERLAY_OVERLAYSIZE_8KB  = 0x8,     /**< OVERLAY_OVERLAYSIZE_8KB, remapping overlay region size to 8KB          */
	OVERLAY_OVERLAYSIZE_16KB = 0x10,    /**< OVERLAY_OVERLAYSIZE_16KB, remapping overlay region size to 16KB        */
	OVERLAY_OVERLAYSIZE_32KB = 0x20,    /**< OVERLAY_OVERLAYSIZE_32KB, remapping overlay region size to 32KB        */
	OVERLAY_OVERLAYSIZE_64KB = 0x40     /**< OVERLAY_OVERLAYSIZE_64KB, remapping overlay region size to 64KB        */
}OVERLAY_OverlaySizeType;

/**
 * @brief FAR Size
 *
 */
typedef enum
{
	OVERLAY_FARUINTSIZE_64KB  = 0x10000,     /**< OVERLAY_FARUINTSIZE_64KB, remapping far uint size to 64KB          */
}OVERLAY_FARSizeType;

/**
 * @brief enable overlay global switch
 *
 */
LOCAL_INLINE void OVERLAY_HWA_OverlayEnable(void)
{
	AHB_OVERLAY->GLOBAL_EN |= AHB_OVERLAY_GLOBAL_EN_OVERLAY_EN_MASK;
}

/**
 * @brief disable overlay global switch
 *
 */
LOCAL_INLINE void OVERLAY_HWA_OverlayDisable(void)
{
	AHB_OVERLAY->GLOBAL_EN &= ~((uint32_t)AHB_OVERLAY_GLOBAL_EN_OVERLAY_EN_MASK);
}

/**
 * @brief enable far global switch
 *
 */
LOCAL_INLINE void OVERLAY_HWA_FAREnable(void)
{
	AHB_OVERLAY->GLOBAL_EN |= AHB_OVERLAY_GLOBAL_EN_FAR_EN_MASK;
}

/**
 * @brief disable far global switch
 *
 */
LOCAL_INLINE void OVERLAY_HWA_FARDisable(void)
{
	AHB_OVERLAY->GLOBAL_EN &= ~((uint32_t)AHB_OVERLAY_GLOBAL_EN_FAR_EN_MASK);
}

/**
 * @brief enable overlay region 0
 *
 */
LOCAL_INLINE void OVERLAY_HWA_OverlayRegion0Enable(void)
{
	AHB_OVERLAY->REGION_0_EN |= AHB_OVERLAY_REGION_0_EN_REGION0_EN_MASK;
}

/**
 * @brief disable overlay region 0
 *
 */
LOCAL_INLINE void OVERLAY_HWA_OverlayRegion0Disable(void)
{
	AHB_OVERLAY->REGION_0_EN &= ~((uint32_t)AHB_OVERLAY_REGION_0_EN_REGION0_EN_MASK);
}

/**
 * @brief Set Overlay Region 0 Source
 *
 * @param u32Src Source address
 */
LOCAL_INLINE void OVERLAY_HWA_SetOverlayRegion0Src(uint32_t u32Src)
{
	AHB_OVERLAY->REGION_0_SRC = AHB_OVERLAY_REGION_0_SRC_REGION0_SRC(u32Src);
}

/**
 * @brief Set Overlay Region 0 Destination
 *
 * @param u32Dst Destination address
 */
LOCAL_INLINE void OVERLAY_HWA_SetOverlayRegion0Dst(uint32_t u32Dst)
{
	AHB_OVERLAY->REGION_0_DST = AHB_OVERLAY_REGION_0_DST_REGION0_DST(u32Dst);
}

/**
 * @brief Set Overlay Region 0 Size
 *
 * @param eSize size
 */
LOCAL_INLINE void OVERLAY_HWA_SetOverlayRegion0Size(OVERLAY_OverlaySizeType eSize)
{
	AHB_OVERLAY->REGION_0_SIZE = AHB_OVERLAY_REGION_0_SIZE_REGION0_SIZE((uint32_t)eSize);
}



/**
 * @brief enable overlay region 1
 *
 */
LOCAL_INLINE void OVERLAY_HWA_OverlayRegion1Enable(void)
{
	AHB_OVERLAY->REGION_1_EN |= AHB_OVERLAY_REGION_1_EN_REGION1_EN_MASK;
}

/**
 * @brief disable overlay region 1
 *
 */
LOCAL_INLINE void OVERLAY_HWA_OverlayRegion1Disable(void)
{
	AHB_OVERLAY->REGION_1_EN &= ~((uint32_t)AHB_OVERLAY_REGION_1_EN_REGION1_EN_MASK);
}

/**
 * @brief Set Overlay Region 1 Source
 *
 * @param u32Src Source address
 */
LOCAL_INLINE void OVERLAY_HWA_SetOverlayRegion1Src(uint32_t u32Src)
{
	AHB_OVERLAY->REGION_1_SRC = AHB_OVERLAY_REGION_1_SRC_REGION1_SRC(u32Src);
}

/**
 * @brief Set Overlay Region 1 Destination
 *
 * @param u32Dst Destination address
 */
LOCAL_INLINE void OVERLAY_HWA_SetOverlayRegion1Dst(uint32_t u32Dst)
{
	AHB_OVERLAY->REGION_1_DST = AHB_OVERLAY_REGION_1_DST_REGION1_DST(u32Dst);
}

/**
 * @brief Set Overlay Region 1 Size
 *
 * @param eSize size
 */
LOCAL_INLINE void OVERLAY_HWA_SetOverlayRegion1Size(OVERLAY_OverlaySizeType eSize)
{
	AHB_OVERLAY->REGION_1_SIZE = AHB_OVERLAY_REGION_1_SIZE_REGION1_SIZE((uint32_t)eSize);
}


/**
 * @brief enable overlay region 2
 *
 */
LOCAL_INLINE void OVERLAY_HWA_OverlayRegion2Enable(void)
{
	AHB_OVERLAY->REGION_2_EN |= AHB_OVERLAY_REGION_2_EN_REGION2_EN_MASK;
}

/**
 * @brief disable overlay region 2
 *
 */
LOCAL_INLINE void OVERLAY_HWA_OverlayRegion2Disable(void)
{
	AHB_OVERLAY->REGION_2_EN &= ~((uint32_t)AHB_OVERLAY_REGION_2_EN_REGION2_EN_MASK);
}

/**
 * @brief Set Overlay Region 2 Source
 *
 * @param u32Src Source address
 */
LOCAL_INLINE void OVERLAY_HWA_SetOverlayRegion2Src(uint32_t u32Src)
{
	AHB_OVERLAY->REGION_2_SRC = AHB_OVERLAY_REGION_2_SRC_REGION2_SRC(u32Src);
}

/**
 * @brief Set Overlay Region 2 Destination
 *
 * @param u32Dst Destination address
 */
LOCAL_INLINE void OVERLAY_HWA_SetOverlayRegion2Dst(uint32_t u32Dst)
{
	AHB_OVERLAY->REGION_2_DST = AHB_OVERLAY_REGION_2_DST_REGION2_DST(u32Dst);
}

/**
 * @brief Set Overlay Region 2 Size
 *
 * @param eSize size
 */
LOCAL_INLINE void OVERLAY_HWA_SetOverlayRegion2Size(OVERLAY_OverlaySizeType eSize)
{
	AHB_OVERLAY->REGION_2_SIZE = AHB_OVERLAY_REGION_2_SIZE_REGION2_SIZE((uint32_t)eSize);
}




/**
 * @brief Set Far Destination
 *
 * @param u32Dst Destination address, must pflash
 */
LOCAL_INLINE void OVERLAY_HWA_SetFarDst(uint32_t u32Dst)
{
	AHB_OVERLAY->FAR_DST = AHB_OVERLAY_FAR_DST_FAR_DST_ADDR(u32Dst);
}

/**
 * @brief Set Far Size
 *
 * @param u32Size size=(u32Size+1)*64KB
 */
LOCAL_INLINE void OVERLAY_HWA_SetFarSize(uint32_t u32Size)
{
	AHB_OVERLAY->FAR_SIZE = AHB_OVERLAY_FAR_SIZE_FAR_SIZE_VAL(u32Size);
}


/**
 * @brief enable error interrupt
 *
 */
LOCAL_INLINE void OVERLAY_HWA_ErrorInterruptEnable(void)
{
	AHB_OVERLAY->INTR_EN |= AHB_OVERLAY_INTR_EN_INTR_ENABLE_MASK;
}

/**
 * @brief disable error interrupt
 *
 */
LOCAL_INLINE void OVERLAY_HWA_ErrorInterruptDisable(void)
{
	AHB_OVERLAY->INTR_EN &= ~((uint32_t)AHB_OVERLAY_INTR_EN_INTR_ENABLE_MASK);
}

/**
 * @brief get error flag
 *
 */
LOCAL_INLINE uint32 OVERLAY_HWA_GetErrorFlag(void)
{
	return (AHB_OVERLAY->INTR_FLAG & AHB_OVERLAY_INTR_FLAG_MASK);
}

/**
 * @brief clear error flag
 *
 */
LOCAL_INLINE uint32 OVERLAY_HWA_ClrErrorFlag(uint32_t u32ClrBits)
{
	return AHB_OVERLAY->INTR_CLR |= AHB_OVERLAY_INTR_FLAG_MASK & u32ClrBits;
}


/** @}*/

#endif /* _HWA_OVERLAY_H_ */
