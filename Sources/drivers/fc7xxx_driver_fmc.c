/**
 * @file fc7xxx_driver_fmc.c
 * @author Flagchip
 * @brief FC7xxx Fmc driver source code
 * @version 0.1.0
 * @date 2024-1-5
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 */
/* ********************************************************************************
  *   Revision History:
  *
  *   Version     Date          Initials      CR#          Descriptions
  *   ---------   ----------    ------------  ----------   ---------------
  *   0.1.0       2024-1-5      Flagchip120   N/A          First version for FC7240
  ******************************************************************************** */

#include "fc7xxx_driver_fmc.h"

/* ################################################################################## */
/* ####################################### Macro #################################### */


/* ################################################################################## */
/* ################################ Local Variables ################################# */
static FMC_Type *const s_apFmcBase[FMC_INSTANCE_COUNT] = FMC_BASE_PTRS;

/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */


/**
 * \brief FMC PFlash Driver Function for lock/unlock sector
 *
 * \param pFMC  FMC instance
 * \param u32Address sector address
 * \param bLock 0U-unlock, 1U-lock
 */
static FMC_Lock_StatusType FMCDRIVER_PFlashLockRegion(const FMC_InstanceType eInstance, uint32_t u32Address, uint8_t bLock);

/**
 * \brief FMC DFlash Driver Function for lock/unlock sector
 *
 * \param pFMC  FMC instance
 * \param u32Address sector address
 * \param bLock 0U-unlock, 1U-lock
 */
static FMC_Lock_StatusType FMCDRIVER_DFlashLockRegion(const FMC_InstanceType eInstance, uint32_t u32Address, uint8_t bLock);

/* ################################################################################## */
/* ########################### Global Prototype Functions ########################### */


/* ################################################################################## */
/* ################################ Local Functions ################################# */

/**
 * \brief FMC PFlash Driver Function for lock/unlock sector
 *
 * \param eInstance  FMC instance
 * \param u32Address sector address
 * \param bLock 0U-unlock, 1U-lock
 */
static FMC_Lock_StatusType FMCDRIVER_PFlashLockRegion(const FMC_InstanceType eInstance, uint32_t u32Address, uint8_t bLock)
{
    FMC_Type *const pFMC = s_apFmcBase[eInstance];
    FMC_Lock_StatusType tRetVal;
    uint32_t u32Index;
    uint32_t u32Length;
    uint32_t u32Temp;

    tRetVal = FMC_LOCK_ERROR_OK;

    /* 1 bank contains more than 256KB, used FB_CPELCK for first and last 256KB used FB_FPELCK */
    if ((u32Address >= PFLASH_ADDR_START) && (u32Address <= (PFLASH_ADDR_START + PFLASH_TOTAL_SIZE)))
    {
        /* PFLASH bank index */
        u32Index = (u32Address - PFLASH_ADDR_START) / PFLASH_BANK_SIZE;
        u32Length = ((u32Address - PFLASH_ADDR_START) % PFLASH_BANK_SIZE) ;
        if (u32Length < (PFLASH_BANK_SIZE - FLASH_256KB_SIZE)) /* first 768KB */
        {
            u32Temp = ((uint32_t)1UL << ((u32Address - PFLASH_ADDR_START - PFLASH_BANK_SIZE * u32Index) >> 16));
            u32Temp = bLock ? (FMC_HWA_GetFBCPELCKValue(pFMC, u32Index) | u32Temp) : (FMC_HWA_GetFBCPELCKValue(pFMC, u32Index) & ~u32Temp);
            FMC_HWA_SetFBCPELCKValue(pFMC, u32Index, u32Temp);
        }
        else /* last 256KB */
        {
            u32Temp = ((u32Address - PFLASH_ADDR_START - PFLASH_BANK_SIZE * u32Index - PFLASH_PHANTOM_OFFSET) >> 13);
            u32Temp = ((uint32_t)1UL << u32Temp);
            u32Temp = bLock ? (FMC_HWA_GetFBFPELCKValue(pFMC, u32Index) | u32Temp) : (FMC_HWA_GetFBFPELCKValue(pFMC, u32Index) & ~u32Temp);
            FMC_HWA_SetFBFPELCKValue(pFMC, u32Index, u32Temp);
        }
    }
    else
    {
        tRetVal = FMC_LOCK_ERROR_INVALID_ADDR;
    }
    return tRetVal;
}


/**
 * \brief FMC DFlash Driver Function for lock/unlock sector
 *
 * \param eInstance  FMC instance
 * \param u32Address sector address
 * \param bLock 0U-unlock, 1U-lock
 */
static FMC_Lock_StatusType FMCDRIVER_DFlashLockRegion(const FMC_InstanceType eInstance, uint32_t u32Address, uint8_t bLock)
{
    FMC_Type *const pFMC = s_apFmcBase[eInstance];
    FMC_Lock_StatusType tRetVal;
    uint32_t u32Index;
    uint32_t u32Temp;
    tRetVal = FMC_LOCK_ERROR_OK;

    /* 1 bank contains only 128KB, only used FB_FPELCK */
    u32Index = 2U;
    if ((u32Address >= DFLASH_ADDR_START) && (u32Address <= DFLASH_ADDR_END))
    {
        u32Temp = 1UL << ((u32Address - DFLASH_ADDR_START - DFLASH_BANK0_SIZE * (u32Index - 2U)) >> 13);
        u32Temp = bLock ? (FMC_HWA_GetFBFPELCKValue(pFMC, u32Index) | u32Temp) : (FMC_HWA_GetFBFPELCKValue(pFMC, u32Index) & ~u32Temp);
        FMC_HWA_SetFBFPELCKValue(pFMC, u32Index, u32Temp);
    }
    else
    {
        tRetVal = FMC_LOCK_ERROR_INVALID_ADDR;
    }
    return tRetVal;
}


/* ################################################################################## */
/* ################################# Global Functions ############################### */

/**
 * \brief FMC Driver Function for flash lock
 *
 * \param pFmcParam FMC driver flash lock parameter
 * \return ErrorType
 */
FMC_Lock_StatusType FMCDRIVER_FlashLock(FMC_DRIVER_Lock_ParamType *pFmcParam)
{
    uint32_t u32Addr, u32Length, u32LockSize, u32TempAddr;

    FMC_Lock_StatusType tRetVal;
    tRetVal = FMC_LOCK_ERROR_OK;

    u32Addr = pFmcParam->u32Address;
    u32Length = pFmcParam->u32Length;
    u32LockSize = (pFmcParam->bClass == FMC_Page) ? FLASH_PROGRAM_PAGE_SIZE : FLASH_ERASE_SECTOR_SIZE;

    /* Address and length should aligned by page/sector */
    if (pFmcParam->u32Address & (u32LockSize - 1U))
    {
        tRetVal = FMC_LOCK_ERROR_INVALID_ADDR;
        pFmcParam->u32ErrorAddress = pFmcParam->u32Address;
    }
    if (pFmcParam->u32Length & (u32LockSize - 1U))
    {
        tRetVal = FMC_LOCK_ERROR_INVALID_SIZE;
        pFmcParam->u32ErrorAddress = pFmcParam->u32Address;
    }

    if (tRetVal == FMC_LOCK_ERROR_OK)
    {
        for (u32TempAddr = u32Addr; u32TempAddr < u32Addr + u32Length; u32TempAddr += u32LockSize)
        {
            if (pFmcParam->bFlash == FMC_PFlash)
            {
                tRetVal = FMCDRIVER_PFlashLockRegion(pFmcParam->bFMC, u32TempAddr, pFmcParam->bLock);
            }
            else
            {
                tRetVal = FMCDRIVER_DFlashLockRegion(pFmcParam->bFMC, u32TempAddr, pFmcParam->bLock);
            }
        }
    }
    return tRetVal;
}

/**
 * \brief FMC set ota active block
 *
 * \param eInstance  FMC instance
 * \param bLock 0U-active block 0, 1U-active block 1
 */
void FMCDRIVER_SwapBlock(const FMC_InstanceType eInstance, FMC_API_ACTIVE_BLOCK_TYPE bActive)
{
    FMC_Type *const pFMC = s_apFmcBase[eInstance];
    if (0U == FMC_HWA_GetOTACtrlValue(pFMC, 0))
    {
        FMC_HWA_SetOTAActive(pFMC, 0, bActive);
        FMC_HWA_SetOTAEnable(pFMC, 0);
    }
}

