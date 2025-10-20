/**
 * @file fc7xxx_driver_overlay.c
 * @author Flagchip
 * @brief FC7xxx overlay driver type definition and API
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
*   0.1.0       2023-12-25    Flagchip0038   N/A          First version for FC7240
********************************************************************************/

#include "fc7xxx_driver_overlay.h"

typedef void (*Void_Type)(void);
typedef void (*U32_Type)(uint32_t u32Data);
typedef void (*SizeEnum_Type)(OVERLAY_OverlaySizeType eSize);

static Void_Type const s_aRegionEnDisable[OVERLYA_REGION_CNT] =
{
    OVERLAY_HWA_OverlayRegion0Disable,
    OVERLAY_HWA_OverlayRegion1Disable,
    OVERLAY_HWA_OverlayRegion2Disable
};


static Void_Type const s_aRegionEnEnable[OVERLYA_REGION_CNT] =
{
    OVERLAY_HWA_OverlayRegion0Enable,
    OVERLAY_HWA_OverlayRegion1Enable,
    OVERLAY_HWA_OverlayRegion2Enable
};

static U32_Type const s_aRegionSrc[OVERLYA_REGION_CNT] =
{
    OVERLAY_HWA_SetOverlayRegion0Src,
    OVERLAY_HWA_SetOverlayRegion1Src,
    OVERLAY_HWA_SetOverlayRegion2Src
};

static U32_Type const s_aRegionDst[OVERLYA_REGION_CNT] =
{
    OVERLAY_HWA_SetOverlayRegion0Dst,
    OVERLAY_HWA_SetOverlayRegion1Dst,
    OVERLAY_HWA_SetOverlayRegion2Dst
};

static SizeEnum_Type const s_aRegionSize[OVERLYA_REGION_CNT] =
{
    OVERLAY_HWA_SetOverlayRegion0Size,
    OVERLAY_HWA_SetOverlayRegion1Size,
    OVERLAY_HWA_SetOverlayRegion2Size
};

static OVERLAY_ErrorCallback_Type s_tErrorCallbackFunc;

/**
 * @brief Overlay region initial function
 *
 * @param pOverlayInitCfg initial parameters
 * @return ERROR_OK is ok, others are not ok
 */
OVERLAY_ErrorType OVERLAY_RegionInit(OVERLAY_OverlayRegionInitType *pOverlayInitCfg)
{
    OVERLAY_ErrorType eRetval;
    uint32_t u32Index;
    uint32_t u32ErrorInfo;

    eRetval = OVERLAY_ERROR_OK;

    /* global overlay Disable */
    OVERLAY_HWA_OverlayDisable();

    /* loop all region */
    for (u32Index = 0U; (u32Index < OVERLYA_REGION_CNT) && (eRetval == OVERLAY_ERROR_OK); u32Index++)
    {
        /* check overlay region enable */
        if (pOverlayInitCfg->aOverlayRegionEn[u32Index])
        {
            if ((pOverlayInitCfg->aOverlayRegionSrc[u32Index] >= PFLASH_START) &&
                (pOverlayInitCfg->aOverlayRegionSrc[u32Index] <= PFLASH_END) &&
                (pOverlayInitCfg->aOverlayRegionDst[u32Index] >= SRAM_START) &&
                (pOverlayInitCfg->aOverlayRegionDst[u32Index] <= SRAM_END)
               )
            {

                /* disable region n */
                s_aRegionEnDisable[u32Index]();

                /* source */
                s_aRegionSrc[u32Index](pOverlayInitCfg->aOverlayRegionSrc[u32Index]);

                /* dest */
                s_aRegionDst[u32Index](pOverlayInitCfg->aOverlayRegionDst[u32Index]);

                /* size */
                s_aRegionSize[u32Index](pOverlayInitCfg->aOverlayRegionSize[u32Index]);

                /* enable region n */
                s_aRegionEnEnable[u32Index]();
            }
            else
            {
                eRetval = OVERLAY_ERROR_ADDR;
            }
        }
        else
        {
            /* disable region n */
            s_aRegionEnDisable[u32Index]();
        }

    }

    if (eRetval == OVERLAY_ERROR_OK)
    {
        /* global overlay enable */
        OVERLAY_HWA_OverlayEnable();
    }

    /* check error flag */
    u32ErrorInfo = OVERLAY_HWA_GetErrorFlag();
    if (u32ErrorInfo)
    {
        eRetval = OVERLAY_ERROR_FLAG;
    }

    return eRetval;
}

/**
 * @brief De-Init Overlay Region
 *
 * @return ERROR_OK is ok, others are not ok
 */
OVERLAY_ErrorType OVERLAY_RegionDeInit(void)
{
    OVERLAY_ErrorType eRetval;
    uint32_t u32Index;

    eRetval = OVERLAY_ERROR_OK;

    /* disable global overlay */
    OVERLAY_HWA_OverlayDisable();

    for (u32Index = 0U; u32Index < OVERLYA_REGION_CNT; u32Index++)
    {
        /* disable region n */
        s_aRegionEnDisable[u32Index]();

        /* source */
        s_aRegionSrc[u32Index](0U);

        /* dest */
        s_aRegionDst[u32Index](0U);

        /* size */
        s_aRegionSize[u32Index](OVERLAY_OVERLAYSIZE_1KB);
    }

    return eRetval;
}


/**
 * @brief Far initial function
 *
 * @param pFarInitCfg initial parameters
 * @return ERROR_OK is ok, others are not ok
 */
OVERLAY_ErrorType OVERLAY_FARInit(OVERLAY_FARInitType *pFarInitCfg)
{
    OVERLAY_ErrorType eRetval;
    uint32_t u32ErrorInfo;

    eRetval = OVERLAY_ERROR_OK;

    if (pFarInitCfg->u32FAREn == 0U)
    {

        /* disable far */
        OVERLAY_HWA_FARDisable();
    }
    else
    {
        /* must align to 64KB, */
        if ((pFarInitCfg->u32FARSize <= OVERLAY_FAR_SIZE_MAX) &&
            ((pFarInitCfg->u32FARSize & OVERLAY_FAR_SIZE_MASK) == 0U)
           )
        {
            if ((pFarInitCfg->u32FARDst >= PFLASH_START) &&
                (pFarInitCfg->u32FARDst <= PFLASH_END)
               )
            {
                /* disable far */
                OVERLAY_HWA_FARDisable();

                /* set far dest */
                OVERLAY_HWA_SetFarDst(pFarInitCfg->u32FARDst);
                /* set far size */
                OVERLAY_HWA_SetFarSize(pFarInitCfg->u32FARSize / OVERLAY_FAR_SIZE_ALIGN - 1);
                /* disable enable */
                OVERLAY_HWA_FAREnable();
            }
            else
            {
                eRetval = OVERLAY_ERROR_ADDR;
            }
        }
        else
        {
            eRetval = OVERLAY_ERROR_SIZE;
        }
    }

    if (eRetval == OVERLAY_ERROR_OK)
    {
        /* enable far */
        OVERLAY_HWA_FAREnable();
    }


    /* check error flag */
    u32ErrorInfo = OVERLAY_HWA_GetErrorFlag();
    if (u32ErrorInfo)
    {
        eRetval = OVERLAY_ERROR_FLAG;
    }


    return eRetval;
}

/**
 * @brief De-Init FAR Region
 *
 * @return ERROR_OK is ok, others are not ok
 */
OVERLAY_ErrorType OVERLAY_FARDeInit(void)
{
    OVERLAY_ErrorType eRetval;

    eRetval = OVERLAY_ERROR_OK;

    /* disable global far */
    OVERLAY_HWA_FARDisable();

    /* set far dest */
    OVERLAY_HWA_SetFarDst(0x01000000U);
    /* set far size */
    OVERLAY_HWA_SetFarSize(0U);

    return eRetval;
}

/**
 * @brief Enable or Disable Interrupt
 *
 * @param pInterruptCfg interrupt config parameter
 */
void OVERLAY_SetInterrupt(OVERLAY_InterruptType *pInterruptCfg)
{
    if (pInterruptCfg->bEnableInterrupt)
    {
        OVERLAY_HWA_ErrorInterruptEnable();
        s_tErrorCallbackFunc = pInterruptCfg->pCallBack;
    }
    else
    {
        OVERLAY_HWA_ErrorInterruptDisable();
        s_tErrorCallbackFunc = NULL;
    }

}

/**
 * @brief Get Error Info
 *
 * @param pErrorInfo error info point
 */
void OVERLAY_GetErrorInfo(OVERLAY_ErrorInfoType *pErrorInfo)
{
    uint32_t u32ErrorInfo;
    u32ErrorInfo = OVERLAY_HWA_GetErrorFlag();

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_FAR_SIZE_INTR_MASK)
    {
        pErrorInfo->bError_FAR_SIZE_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_FAR_SIZE_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_FAR_DST_OVERFLOW_INTR_MASK)
    {
        pErrorInfo->bError_FAR_DST_OVERFLOW_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_FAR_DST_OVERFLOW_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_FAR_DST_NO_FLASH_INTR_MASK)
    {
        pErrorInfo->bError_FAR_DST_NO_FLASH_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_FAR_DST_NO_FLASH_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION2_D_CROS_INTR_MASK)
    {
        pErrorInfo->bError_REGION2_D_CROS_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION2_D_CROS_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION2_S_CROS_INTR_MASK)
    {
        pErrorInfo->bError_REGION2_S_CROS_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION2_S_CROS_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION2_SIZE_INTR_MASK)
    {
        pErrorInfo->bError_REGION2_SIZE_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION2_SIZE_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION2_DST_INTR_MASK)
    {
        pErrorInfo->bError_REGION2_DST_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION2_DST_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION2_SRC_INTR_MASK)
    {
        pErrorInfo->bError_REGION2_SRC_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION2_SRC_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION1_D_CROS_INTR_MASK)
    {
        pErrorInfo->bError_REGION1_D_CROS_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION1_D_CROS_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION1_S_CROS_INTR_MASK)
    {
        pErrorInfo->bError_REGION1_S_CROS_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION1_S_CROS_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION1_SIZE_INTR_MASK)
    {
        pErrorInfo->bError_REGION1_SIZE_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION1_SIZE_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION1_DST_INTR_MASK)
    {
        pErrorInfo->bError_REGION1_DST_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION1_DST_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION1_SRC_INTR_MASK)
    {
        pErrorInfo->bError_REGION1_SRC_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION1_SRC_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION0_D_CROS_INTR_MASK)
    {
        pErrorInfo->bError_REGION0_D_CROS_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION0_D_CROS_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION0_S_CROS_INTR_MASK)
    {
        pErrorInfo->bError_REGION0_S_CROS_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION0_S_CROS_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION0_SIZE_INTR_MASK)
    {
        pErrorInfo->bError_REGION0_SIZE_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION0_SIZE_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION0_DST_INTR_MASK)
    {
        pErrorInfo->bError_REGION0_DST_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION0_DST_INTR = 0U;
    }

    if (u32ErrorInfo & AHB_OVERLAY_INTR_FLAG_REGION0_SRC_INTR_MASK)
    {
        pErrorInfo->bError_REGION0_SRC_INTR = 1U;
    }
    else
    {
        pErrorInfo->bError_REGION0_SRC_INTR = 0U;
    }
}

/**
 * @brief Clear Error Info
 *
 * @param pErrorInfo error info point
 */
void OVERLAY_ClrErrorInfo(OVERLAY_ErrorInfoType *pErrorInfo)
{
    uint32_t u32ErrorInfo;

    u32ErrorInfo = AHB_OVERLAY_INTR_FLAG_FAR_SIZE_INTR(pErrorInfo->bError_FAR_SIZE_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_FAR_DST_OVERFLOW_INTR(pErrorInfo->bError_FAR_DST_OVERFLOW_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_FAR_DST_NO_FLASH_INTR(pErrorInfo->bError_FAR_DST_NO_FLASH_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION2_D_CROS_INTR(pErrorInfo->bError_REGION2_D_CROS_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION2_S_CROS_INTR(pErrorInfo->bError_REGION2_S_CROS_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION2_SIZE_INTR(pErrorInfo->bError_REGION2_SIZE_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION2_DST_INTR(pErrorInfo->bError_REGION2_DST_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION2_SRC_INTR(pErrorInfo->bError_REGION2_SRC_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION1_D_CROS_INTR(pErrorInfo->bError_REGION1_D_CROS_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION1_S_CROS_INTR(pErrorInfo->bError_REGION1_S_CROS_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION1_SIZE_INTR(pErrorInfo->bError_REGION1_SIZE_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION1_DST_INTR(pErrorInfo->bError_REGION1_DST_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION1_SRC_INTR(pErrorInfo->bError_REGION1_SRC_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION0_D_CROS_INTR(pErrorInfo->bError_REGION0_D_CROS_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION0_S_CROS_INTR(pErrorInfo->bError_REGION0_S_CROS_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION0_SIZE_INTR(pErrorInfo->bError_REGION0_SIZE_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION0_DST_INTR(pErrorInfo->bError_REGION0_DST_INTR);
    u32ErrorInfo |= AHB_OVERLAY_INTR_FLAG_REGION0_SRC_INTR(pErrorInfo->bError_REGION0_SRC_INTR);

    OVERLAY_HWA_ClrErrorFlag(u32ErrorInfo);
}
/**
 * @brief Call Me in Overlay Error interrupt handler
 *
 */
void OVERLAY_ErrorInterruptRoutine(void)
{
    OVERLAY_ErrorInfoType tErrorInfo;
    if (s_tErrorCallbackFunc != NULL)
    {
        OVERLAY_GetErrorInfo(&tErrorInfo);
        s_tErrorCallbackFunc(tErrorInfo);
    }
}
