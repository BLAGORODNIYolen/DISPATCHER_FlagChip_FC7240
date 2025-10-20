/**
 * @file fc7xxx_driver_flash.c
 * @author Flagchip
 * @brief FC7xxx Flash driver source code
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

#include "fc7xxx_driver_flash.h"

/* ################################################################################## */
/* ####################################### Macro #################################### */

#define    STATUS_SUCCESS                       0x001UL
#define    STATUS_HVOP                          0x8001UL
#define    FLASH_API_DISABLE                    0x0UL
#define    FLASH_API_ENABLE                     0x1UL
#define    FLASH_API_SIZE_8M                    0x0UL
#define    WDG_TUNE_DISABLE                     0x1u
#define    FLASH_AUTO_HOLD_ENABLE               0x1UL
#define    FLASH_AUTO_HOLD_DISABLE              0x0UL
#define    FLASH_REG_BIT_CFG_DISABLE            0x0UL
#define    FLASH_REG_BIT_CFG_ENABLE             0x1UL
#define    FLASH_REG_BIT_CFG_HOLD               0x2UL

#define    INVAILD_ADDR                         ((void*)0xFFFFFFFFU)

#define FLS_MAX_ERASE_BLANK_CHECK               (256U)

#define FLS_ABT_TIMEOUT_VALUE                   (1000000U)
#define FLS_ASYNC_WRITE_TIMEOUT_VALUE           (1000U)
#define FLS_ASYNC_ERASE_TIMEOUT_VALUE           (500000U)
/*=================================================================================================
*                         LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/

typedef uint32_t status_t;

typedef struct {
  uint32_t blk_sel;
  uint32_t dest;
} FLASH_DRV_ERASESECTOR_CFG_T;

typedef struct {
  uint32_t dest;
  uint32_t size;
  uint32_t *pData;
  uint32_t  wdg_tune;
  uint32_t  pgff;
} FLASH_DRV_PRGM_CFG_T;


typedef struct
{
    uint16 u16FlashRomApiMajorVersion;
    uint16 u16FlashRomApiMinorVersion;

    status_t (*FLASH_DRV_EraseBlock)(FLASH_API_BLOCK_SELECT_TYPE blk_se, uint32_t int_en, uint32_t type);
    status_t (*FLASH_DRV_EraseBlock_Clear)(void);
    status_t (*FLASH_DRV_EraseSector)(FLASH_DRV_ERASESECTOR_CFG_T * flash_api_cfg, uint32_t int_en, uint32_t type);
    status_t (*FLASH_DRV_EraseSector_Clear)(void);
    uint32_t RESERVED2[2U];
    status_t (*FLASH_DRV_Program)(FLASH_DRV_PRGM_CFG_T * flash_api_cfg, uint32_t int_en, uint32_t type);
    status_t (*FLASH_DRV_Program_Clear)(void);
    uint32_t RESERVED3[6U];
    status_t (*FLASH_DRV_HV_Status_Check)(void);
    uint32_t RESERVED4[8U];
    status_t (*FLASH_DRV_ENABLE_HOLD_CFG)(uint32_t  flash_api_cfg);
}FLASH_ROM_API_ENTRY_T;


/** flash driver header for finding function in special address */
#define FLASHAPI_IN_ROM_ADDR   0x04810200U /* flash api address in rom */
const FLASH_ROM_API_ENTRY_T *s_pFlashDriver_RomApiHeader;

/* ################################################################################## */
/* ################################ Local Variables ################################# */


/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */


/* ################################################################################## */
/* ########################### Global Prototype Functions ########################### */




/* ################################################################################## */
/* ################################ Local Functions ################################# */


/**
 * \brief PFlash Driver Function for Erasing Address Check
 *
 * \param pFlashParam flash driver erase parameter
 */
static FLASH_StatusType FLASHDRIVER_LL_PFlashEraseCheck(FLASH_DRIVER_ParamType *pFlashParam)
{
    FLASH_StatusType tRetVal;

    if (s_pFlashDriver_RomApiHeader != (FLASH_ROM_API_ENTRY_T *)FLASHAPI_IN_ROM_ADDR)
    {
        tRetVal = FLASH_ERROR_NO_INIT;
    }
    else
    {
        tRetVal = FLASH_ERROR_OK;
        /* check address align */
        if (pFlashParam->u32Address & (PFLASH_ERASE_SECTOR_SIZE - 1U))
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
            pFlashParam->u32ErrorAddress = pFlashParam->u32Address;

        }
        else
        {
            /* check length align */
            if (pFlashParam->u32Length & (PFLASH_ERASE_SECTOR_SIZE - 1U))
            {
                tRetVal = FLASH_ERROR_INVALID_SIZE;
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
            }

        }
    }
    return tRetVal;
}

/**
 * \brief DFlash Driver Function for Erasing Address Check
 *
 * \param pFlashParam flash driver erase parameter
 */
static FLASH_StatusType FLASHDRIVER_LL_DFlashEraseCheck(FLASH_DRIVER_ParamType *pFlashParam)
{
    FLASH_StatusType tRetVal;

    if (s_pFlashDriver_RomApiHeader != (FLASH_ROM_API_ENTRY_T *)FLASHAPI_IN_ROM_ADDR)
    {
        tRetVal = FLASH_ERROR_NO_INIT;
    }
    else
    {

        tRetVal = FLASH_ERROR_OK;

        /* check address align */
        if (pFlashParam->u32Address & (DFLASH_ERASE_SECTOR_SIZE - 1U))
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
            pFlashParam->u32ErrorAddress = pFlashParam->u32Address;

        }
        else
        {
            /* check length align */
            if (pFlashParam->u32Length & (DFLASH_ERASE_SECTOR_SIZE - 1U))
            {
                tRetVal = FLASH_ERROR_INVALID_SIZE;
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
            }

        }

    }
    return tRetVal;
}

/**
 * \brief PFlash Driver Function for Writing address Check
 *
 * \param pFlashParam flash driver write parameter
 */
static FLASH_StatusType FLASHDRIVER_PFlashWriteCheck(FLASH_DRIVER_ParamType *pFlashParam)
{
    FLASH_StatusType tRetVal;

    if (s_pFlashDriver_RomApiHeader != (FLASH_ROM_API_ENTRY_T *)FLASHAPI_IN_ROM_ADDR)
    {
        tRetVal = FLASH_ERROR_NO_INIT;
    }
    else
    {
        tRetVal = FLASH_ERROR_OK;

        /* check address align */
        if (pFlashParam->u32Address & (PFLASH_PROGRAM_PAGE_MIN_SIZE - 1U))
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
            pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
        }

        else
        {
            /* check length align */
            if (pFlashParam->u32Length & (PFLASH_PROGRAM_PAGE_MIN_SIZE - 1U))
            {
                tRetVal = FLASH_ERROR_INVALID_SIZE;
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
            }
        }
    }
    return tRetVal;
}

/**
 * \brief DFlash Driver Function for Writing address Check
 *
 * \param pFlashParam flash driver write parameter
 */
static FLASH_StatusType FLASHDRIVER_DFlashWriteCheck(FLASH_DRIVER_ParamType *pFlashParam)
{
    FLASH_StatusType tRetVal;

    if (s_pFlashDriver_RomApiHeader != (FLASH_ROM_API_ENTRY_T *)FLASHAPI_IN_ROM_ADDR)
    {
        tRetVal = FLASH_ERROR_NO_INIT;
    }
    else
    {
        tRetVal = FLASH_ERROR_OK;

        /* check address align */
        if (pFlashParam->u32Address & (DFLASH_PROGRAM_PAGE_MIN_SIZE - 1U))
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
            pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
        }

        else
        {
            /* check length align */
            if (pFlashParam->u32Length & (DFLASH_PROGRAM_PAGE_MIN_SIZE - 1U))
            {
                tRetVal = FLASH_ERROR_INVALID_SIZE;
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
            }
        }
    }
    return tRetVal;
}

/**
 * \brief PFlash Driver Function for lock/unlock sector
 *
 * \param u32Address sector address
 * \param bLock 0U-unlock, 1U-lock
 */
static void FLASHDRIVER_PFlashLockBlock(FLASH_API_BLOCK_SELECT_TYPE blk_sel, uint8_t bLock)
{
    uint32_t u32Index;
    uint32_t u32Temp;

    u32Index = (uint32_t)blk_sel;
    /* 1 bank contains more than 256KB, used FB_CPELCK for first and last 256KB used FB_FPELCK */
        /* PFLASH bank index */
	u32Temp = bLock ? 0xFFFFFFFFUL : 0x0UL;
	if(blk_sel < FLASH_DATA_BLOCK_SELECT0)
	{
		FMC1->FB_CPELCK[u32Index] = u32Temp;
		FMC1->FB_FPELCK[u32Index] = u32Temp;
	}
	else
	{
		FMC1->FB_FPELCK[u32Index] = u32Temp;
	}
}

/**
 * \brief PFlash Driver Function for lock/unlock sector
 *
 * \param u32Address sector address
 * \param bLock 0U-unlock, 1U-lock
 */
static FLASH_StatusType FLASHDRIVER_PFlashLockSector(uint32_t u32Address, uint8_t bLock)
{
    FLASH_StatusType tRetVal;
    uint32_t u32Index;
    uint32_t u32Length;
    uint32_t u32Temp;

    tRetVal = FLASH_ERROR_OK;

    /* 1 bank contains more than 256KB, used FB_CPELCK for first and last 256KB used FB_FPELCK */
    if ((u32Address >= PFLASH_ADDR_START) && (u32Address <= PFLASH_ADDR_END))
    {
        /* PFLASH bank index */
        u32Index = (u32Address - PFLASH_ADDR_START) / PFLASH_BANK_SIZE;
        u32Length = ((u32Address - PFLASH_ADDR_START) % PFLASH_BANK_SIZE) ;
        if (u32Length < (PFLASH_BANK_SIZE - FLASH_256KB_SIZE)) /* first 1792KB */
        {
            u32Temp = ((uint32_t)1UL << ((u32Address - PFLASH_ADDR_START - PFLASH_BANK_SIZE * u32Index) >> 16));
            u32Temp = bLock ? 0xFFFFFFFFUL : (0xFFFFFFFFUL ^ u32Temp);
            FMC1->FB_CPELCK[u32Index] = u32Temp;
        }
        else /* last 256KB */
        {
            u32Temp =  ((u32Address - PFLASH_ADDR_START - PFLASH_BANK_SIZE * u32Index - PFLASH_LAST256K_OFFSET) >> 13);
            u32Temp =  ((uint32_t)1UL << u32Temp);
            u32Temp = bLock ? 0xFFFFFFFFUL : (0xFFFFFFFFUL ^ u32Temp);
            /* 0x1C0000UL */
            FMC1->FB_FPELCK[u32Index] = u32Temp;
        }
    }
    else
    {
        tRetVal = FLASH_ERROR_INVALID_ADDR;
    }
    return tRetVal;
}

/**
 * \brief DFlash Driver Function for lock/unlock sector
 *
 * \param u32Address sector address
 * \param bLock 0U-unlock, 1U-lock
 */
static FLASH_StatusType FLASHDRIVER_DFlashLockSector(uint32_t u32Address, uint8_t bLock)
{
    FLASH_StatusType tRetVal;
    uint32_t u32Index;
    uint32_t u32Temp;
    tRetVal = FLASH_ERROR_OK;

    /* 1 bank contains only 256KB, only used FB_FPELCK */
    u32Index = 2U;
    if ((u32Address >= DFLASH_ADDR_START) && (u32Address <= DFLASH_ADDR_END))
    {
        u32Temp = 0xFFFFFFFFUL ^ (1UL << ((u32Address - DFLASH_ADDR_START - DFLASH_BANK0_SIZE * (u32Index - 2U)) >> 13));
        FMC1->FB_FPELCK[u32Index] = bLock ? 0xFFFFFFFFUL : u32Temp ;
    }
    else
    {
        tRetVal = FLASH_ERROR_INVALID_ADDR;
    }
    return tRetVal;
}

/**
 * \brief Get Flash Configuration
 *
 * \param u32Address the flash address
 * \param pFlash_api_cfg out flash parameter
 */
static FLASH_StatusType FLASHDRIVER_GetFlashConfig(uint32_t u32Address, FLASH_DRV_ERASESECTOR_CFG_T *pFlash_api_cfg)
{
    FLASH_StatusType tRetVal;
    tRetVal = FLASH_ERROR_OK;

    if ((u32Address >= PFLASH_ADDR_START) && (u32Address < PFLASH_ADDR_START + PFLASH_BANK_SIZE))
    {
        pFlash_api_cfg->blk_sel = FLASH_BLOCK_SELECT0;
        pFlash_api_cfg->dest = u32Address;

    }
    else if ((u32Address >= PFLASH_ADDR_START) && (u32Address < PFLASH_ADDR_START + PFLASH_BANK_SIZE*2U))
    {
        pFlash_api_cfg->blk_sel = FLASH_BLOCK_SELECT1;
        pFlash_api_cfg->dest = u32Address;
    }
    else if ((u32Address >= DFLASH_ADDR_START) && (u32Address < DFLASH_ADDR_START + DFLASH_BANK0_SIZE))
    {
        pFlash_api_cfg->blk_sel = FLASH_DATA_BLOCK_SELECT0;
        pFlash_api_cfg->dest = u32Address;
    }
    else
    {
        tRetVal = FLASH_ERROR_INVALID_ADDR;
    }
    return tRetVal;
}

/* ################################################################################## */
/* ################################# Global Functions ############################### */

void FLASHDRIVER_Init(void)
{
    s_pFlashDriver_RomApiHeader = (FLASH_ROM_API_ENTRY_T *)FLASHAPI_IN_ROM_ADDR;
}

/**
 * \brief PFlash Driver Function for Erasing
 *
 * \param pFlashParam flash driver erase parameter
 * \return ErrorType
 */
FLASH_StatusType FLASHDRIVER_FlashEraseBlock(FLASH_API_BLOCK_SELECT_TYPE blk_sel)
{
    uint32_t u32TryCount;

    FLASH_StatusType tRetVal;
    uint32_t u32Temp;

    tRetVal = FLASH_ERROR_OK;

    if(blk_sel > FLASH_DATA_BLOCK_SELECT0)
    {
    	tRetVal = FLASH_ERROR_INVALID_PARAM;
    }
    else
    {
		s_pFlashDriver_RomApiHeader->FLASH_DRV_ENABLE_HOLD_CFG(FLASH_AUTO_HOLD_ENABLE);
		FLASHDRIVER_PFlashLockBlock(blk_sel, 0);
		__asm(" cpsid i");
		u32Temp = s_pFlashDriver_RomApiHeader-> FLASH_DRV_EraseBlock(blk_sel, FLASH_API_DISABLE, 0);
		__asm(" cpsie i");
		tRetVal = (u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;
		/* check erase operation valid */
		if (tRetVal != FLASH_ERROR_OK)
		{

		}
		else
		{
			/* check erasing still in progress */
			tRetVal = FLASH_ERROR_FAILED;
			u32TryCount = 0;
			while ((tRetVal != FLASH_ERROR_OK) && (u32TryCount++ < 1000000))
			{
				u32Temp = s_pFlashDriver_RomApiHeader->FLASH_DRV_HV_Status_Check();
				/* check if finished */
				if (u32Temp == STATUS_HVOP)
				{
					tRetVal = FLASH_ERROR_FAILED;
				}
				else
				{
					tRetVal = FLASH_ERROR_OK;
				}
			}

			if (tRetVal != FLASH_ERROR_OK)
			{
				/* erasing timeout, exit */
				*(uint32_t*)(0x00000014U) = *((uint32_t*)0x40020004U);
			}
			else
			{
				/* check erasing result */
				u32Temp = s_pFlashDriver_RomApiHeader-> FLASH_DRV_EraseBlock_Clear();
				tRetVal = (u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;
			}
		}
    }
    return tRetVal;
}

/**
 * \brief PFlash Driver Function for Erasing
 *
 * \param pFlashParam flash driver erase parameter
 * \return ErrorType
 */
FLASH_StatusType FLASHDRIVER_PFlashEraseSector(FLASH_DRIVER_ParamType *pFlashParam)
{
    uint32_t u32Addr, u32Length;
    uint32_t u32TryCount;
    FLASH_DRV_ERASESECTOR_CFG_T tFlash_api_cfg;

    FLASH_StatusType tRetVal;
    uint32_t u32Temp;

    tRetVal = FLASH_ERROR_OK;

    /* FLASH_DRV_WDG_CFG_T tFlash_wdg_cfg; */

    u32Addr = pFlashParam->u32Address;
    u32Length = pFlashParam->u32Length;

    tRetVal = FLASH_ERROR_OK;
    pFlashParam->u32ErrorAddress = 0x0U;

    tRetVal = FLASHDRIVER_LL_PFlashEraseCheck(pFlashParam);

    if (tRetVal == FLASH_ERROR_OK)
    {
        /* config flash wdog */
        //ConfigFlashWdog();

        s_pFlashDriver_RomApiHeader->FLASH_DRV_ENABLE_HOLD_CFG(FLASH_AUTO_HOLD_ENABLE);


        pFlashParam->u32Length = PFLASH_ERASE_SECTOR_SIZE;

        /* loop erase */
        for (pFlashParam->u32Address = u32Addr; pFlashParam->u32Address < u32Addr + u32Length;
             pFlashParam->u32Address += PFLASH_ERASE_SECTOR_SIZE)
        {

            FLASHDRIVER_PFlashLockSector(pFlashParam->u32Address, 0U);
            FLASHDRIVER_GetFlashConfig(pFlashParam->u32Address, &tFlash_api_cfg);
            /* start erase */
            __asm(" cpsid i");
            u32Temp = s_pFlashDriver_RomApiHeader->FLASH_DRV_EraseSector(&tFlash_api_cfg, FLASH_API_DISABLE, 0);
            __asm(" cpsie i");
            tRetVal = (u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;


            /* check erase operation valid */
            if (tRetVal != FLASH_ERROR_OK)
            {
                /* erase operation failed, exit */
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                break;
            }
            else
            {
                /* check erasing still in progress */
                tRetVal = FLASH_ERROR_FAILED;
                u32TryCount = 0;
                while ((tRetVal != FLASH_ERROR_OK) && (u32TryCount++ < 100000))
                {
                    u32Temp = s_pFlashDriver_RomApiHeader->FLASH_DRV_HV_Status_Check();
                    /* check if finished */
                    if (u32Temp == STATUS_HVOP)
                    {
                        tRetVal = FLASH_ERROR_FAILED;
                    }
                    else
                    {
                        tRetVal = FLASH_ERROR_OK;
                    }
                }

                if (tRetVal != FLASH_ERROR_OK)
                {
                    /* erasing timeout, exit */
                    *(uint32_t*)(0x00000014U) = *((uint32_t*)0x40020004U);
                    break;
                }
                else
                {
                    /* check erasing result */
                    u32Temp = s_pFlashDriver_RomApiHeader->FLASH_DRV_EraseSector_Clear();
                    tRetVal = (u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;

                    if (tRetVal != FLASH_ERROR_OK)
                    {
                        /* erasing failed, exit */
                        pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                        break;
                    }
                    else
                    {

                        if (tRetVal != FLASH_ERROR_OK)
                        {
                            /* erasing failed, exit */
                            pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                            break;
                        }
                        else
                        {

                            /* trigger watchdog function */
                            if (pFlashParam->wdTriggerFct != ((void *)0))
                            {
                                pFlashParam->wdTriggerFct();
                            }
                        }


                    }
                }
            }
            /* lock sector */
            FLASHDRIVER_PFlashLockSector(pFlashParam->u32Address, 1U);
        }
    }
    return tRetVal;
}

/**
 * \brief PFlash Driver Function for Writing
 *
 * \param pFlashParam flash driver write parameter
 * \return ErrorType
 */
FLASH_StatusType FLASHDRIVER_PFlashWrite(FLASH_DRIVER_ParamType *pFlashParam)
{
    uint32_t u32Addr, u32Length, u32DataAddr, u32AlignLen, u32TempLen;
    /* uint8_t *pTempBuf; */
    uint32_t u32AlignOffset, u32Index, u32Count;
    uint32_t u32TryCount;
    FLASH_DRV_PRGM_CFG_T tFlash_api_cfg;

    FLASH_StatusType tRetVal;
    uint32_t u32Temp;


    tRetVal = FLASH_ERROR_OK;

    u32Addr = pFlashParam->u32Address;
    u32Length = pFlashParam->u32Length;

    pFlashParam->u32ErrorAddress = 0x0U;


    tRetVal = FLASHDRIVER_PFlashWriteCheck(pFlashParam);

    if (tRetVal == FLASH_ERROR_OK)
    {
        /* config flash wdog */
        //ConfigFlashWdog();

        s_pFlashDriver_RomApiHeader->FLASH_DRV_ENABLE_HOLD_CFG(FLASH_AUTO_HOLD_ENABLE);

        /* align address, write must align to FLASH_PROGRAM_PAGE_MAX_SIZE */
        u32AlignOffset = u32Addr & (PFLASH_PROGRAM_PAGE_MAX_SIZE - 1U);
        u32AlignLen = u32Length + u32AlignOffset;

        u32Count = u32AlignLen & (PFLASH_PROGRAM_PAGE_MAX_SIZE - 1U);

        u32Count = u32Count > 0U ? 1U : 0U;

        u32Count += u32AlignLen / PFLASH_PROGRAM_PAGE_MAX_SIZE;

        u32DataAddr = (uint32_t)pFlashParam->pData;
        u32TempLen = u32AlignLen;

        for (u32Index = 0U; u32Index < u32Count; u32Index++)
        {
            /* real write length in this cycle */
            u32TempLen = u32Length + u32AlignOffset;
            u32TempLen = u32TempLen >= PFLASH_PROGRAM_PAGE_MAX_SIZE ? PFLASH_PROGRAM_PAGE_MAX_SIZE : u32TempLen;
            u32TempLen -= u32AlignOffset;

            pFlashParam->u32Address = u32Addr;
            pFlashParam->u32Length = u32TempLen;

            /* unlock sector */
            FLASHDRIVER_PFlashLockSector(pFlashParam->u32Address, 0U);
            tFlash_api_cfg.pgff = FLASH_REG_BIT_CFG_DISABLE;
            tFlash_api_cfg.dest = pFlashParam->u32Address;
            tFlash_api_cfg.size = (pFlashParam->u32Length / 4); /* one data is 4 bytes */
            tFlash_api_cfg.pData = (uint32_t *)u32DataAddr;
            tFlash_api_cfg.wdg_tune = WDG_TUNE_DISABLE;

            /* next address and length */
            u32Addr += u32TempLen;
            u32DataAddr += u32TempLen;
            u32Length -= u32TempLen;

            u32AlignOffset = 0U;

            /* start write */
            __asm(" cpsid i");
            u32Temp = s_pFlashDriver_RomApiHeader->FLASH_DRV_Program(&tFlash_api_cfg, FLASH_API_DISABLE, 0);
            __asm(" cpsie i");
            tRetVal = u32Temp == STATUS_SUCCESS ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;

            /* check erase operation valid */
            if (tRetVal != FLASH_ERROR_OK)
            {
                /* write operation failed, exit */
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                break;
            }
            else
            {
                /* FLASHDRIVER_LL_Delay(); */

                /* check write still in progress */
                tRetVal = FLASH_ERROR_FAILED;
                u32TryCount = 0;
                while ((tRetVal != FLASH_ERROR_OK) && (u32TryCount++ < 10000))
                {
                    u32Temp = s_pFlashDriver_RomApiHeader->FLASH_DRV_HV_Status_Check();
                    /* check if finished */
                    if (u32Temp == STATUS_HVOP)
                    {
                        tRetVal = FLASH_ERROR_FAILED;
                    }
                    else
                    {
                        tRetVal = FLASH_ERROR_OK;
                    }
                }


                if (tRetVal != FLASH_ERROR_OK)
                {
                    /* erasing timeout, exit */
                    pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                    break;
                }
                else
                {

                    /* check write result */
                    u32Temp = s_pFlashDriver_RomApiHeader->FLASH_DRV_Program_Clear();
                    tRetVal = (u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;

                    if (tRetVal != FLASH_ERROR_OK)
                    {
                        /* write failed, exit */
                        pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                        break;
                    }
                    else
                    {
                        /* trigger watchdog function */
                        if (pFlashParam->wdTriggerFct != ((void *)0))
                        {
                            pFlashParam->wdTriggerFct();
                        }

                    }
                }
            }

            /* lock sector */
            FLASHDRIVER_PFlashLockSector(pFlashParam->u32Address, 1U);
        }
    }
    return tRetVal;
}

/**
 * \brief DFlash Driver Function for Erasing
 *
 * \param pFlashParam flash driver erase parameter
 * \return ErrorType
 */
FLASH_StatusType FLASHDRIVER_DFlashEraseSector(FLASH_DRIVER_ParamType *pFlashParam)
{
    uint32_t u32Addr, u32Length;
    uint32_t u32TryCount;
    FLASH_DRV_ERASESECTOR_CFG_T tFlash_api_cfg;
    FLASH_StatusType tRetVal;
    uint32_t u32Temp;

    tRetVal = FLASH_ERROR_OK;


    u32Addr = pFlashParam->u32Address;
    u32Length = pFlashParam->u32Length;

    tRetVal = FLASH_ERROR_OK;
    pFlashParam->u32ErrorAddress = 0x0U;

    tRetVal = FLASHDRIVER_LL_DFlashEraseCheck(pFlashParam);

    if (tRetVal == FLASH_ERROR_OK)
    {
        /* config flash wdog */
        //ConfigFlashWdog();

        s_pFlashDriver_RomApiHeader->FLASH_DRV_ENABLE_HOLD_CFG(FLASH_AUTO_HOLD_ENABLE);


        pFlashParam->u32Length = DFLASH_ERASE_SECTOR_SIZE;

        /* loop erase */
        for (pFlashParam->u32Address = u32Addr; pFlashParam->u32Address < u32Addr + u32Length;
             pFlashParam->u32Address += DFLASH_ERASE_SECTOR_SIZE)
        {
            /* unlock data flash */
            FLASHDRIVER_DFlashLockSector(pFlashParam->u32Address, 0U);

            FLASHDRIVER_GetFlashConfig(pFlashParam->u32Address, &tFlash_api_cfg);
            /* start erase */
            __asm(" cpsid i");
            u32Temp = s_pFlashDriver_RomApiHeader->FLASH_DRV_EraseSector(&tFlash_api_cfg, FLASH_API_DISABLE, 0);
            __asm(" cpsie i");
            tRetVal = (u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;


            /* check erase operation valid */
            if (tRetVal != FLASH_ERROR_OK)
            {
                /* erase operation failed, exit */
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                break;
            }
            else
            {
                /* check erasing still in progress */
                tRetVal = FLASH_ERROR_FAILED;
                u32TryCount = 0;
                while ((tRetVal != FLASH_ERROR_OK) && (u32TryCount++ < 100000))
                {
                    u32Temp = s_pFlashDriver_RomApiHeader->FLASH_DRV_HV_Status_Check();
                    /* check if finished */
                    if (u32Temp == STATUS_HVOP)
                    {
                        tRetVal = FLASH_ERROR_FAILED;
                    }
                    else
                    {
                        tRetVal = FLASH_ERROR_OK;
                    }
                }

                if (tRetVal != FLASH_ERROR_OK)
                {
                    /* erasing timeout, exit */
                    pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                    break;
                }
                else
                {
                    /* check erasing result */
                    u32Temp = s_pFlashDriver_RomApiHeader->FLASH_DRV_EraseSector_Clear();
                    tRetVal = (u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;

                    if (tRetVal != FLASH_ERROR_OK)
                    {
                        /* erasing failed, exit */
                        pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                        break;
                    }
                    else
                    {

                        if (tRetVal != FLASH_ERROR_OK)
                        {
                            /* erasing failed, exit */
                            pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                            break;
                        }
                        else
                        {

                            /* trigger watchdog function */
                            if (pFlashParam->wdTriggerFct != ((void *)0))
                            {
                                pFlashParam->wdTriggerFct();
                            }
                        }


                    }
                }
            }

            /* lock data flash */
            FLASHDRIVER_DFlashLockSector(pFlashParam->u32Address, 1U);
        }
    }
    return tRetVal;
}

/**
 * \brief DFlash Driver Function for Writing
 *
 * \param pFlashParam flash driver write parameter
 * \return ErrorType
 */
FLASH_StatusType FLASHDRIVER_DFlashWrite(FLASH_DRIVER_ParamType *pFlashParam)
{
    uint32_t u32Addr, u32Length, u32DataAddr, u32AlignLen, u32TempLen;
    /* uint8_t *pTempBuf; */
    uint32_t u32AlignOffset, u32Index, u32Count;
    uint32_t u32TryCount;
    FLASH_DRV_PRGM_CFG_T tFlash_api_cfg;

    FLASH_StatusType tRetVal;
    uint32_t u32Temp;

    tRetVal = FLASH_ERROR_OK;

    u32Addr = pFlashParam->u32Address;
    u32Length = pFlashParam->u32Length;

    pFlashParam->u32ErrorAddress = 0x0U;


    tRetVal = FLASHDRIVER_DFlashWriteCheck(pFlashParam);

    if (tRetVal == FLASH_ERROR_OK)
    {
        /* config flash wdog */
        //ConfigFlashWdog();

        s_pFlashDriver_RomApiHeader->FLASH_DRV_ENABLE_HOLD_CFG(FLASH_AUTO_HOLD_ENABLE);

        /* align address, write must align to FLASH_PROGRAM_PAGE_MAX_SIZE */
        u32AlignOffset = u32Addr & (DFLASH_PROGRAM_PAGE_MAX_SIZE - 1U);
        u32AlignLen = u32Length + u32AlignOffset;

        u32Count = u32AlignLen & (DFLASH_PROGRAM_PAGE_MAX_SIZE - 1U);

        u32Count = u32Count > 0U ? 1U : 0U;

        u32Count += u32AlignLen / DFLASH_PROGRAM_PAGE_MAX_SIZE;

        u32DataAddr = (uint32_t)pFlashParam->pData;
        u32TempLen = u32AlignLen;

        for (u32Index = 0U; u32Index < u32Count; u32Index++)
        {
            /* real write length in this cycle */
            u32TempLen = u32Length + u32AlignOffset;
            u32TempLen = u32TempLen >= DFLASH_PROGRAM_PAGE_MAX_SIZE ? DFLASH_PROGRAM_PAGE_MAX_SIZE : u32TempLen;
            u32TempLen -= u32AlignOffset;

            pFlashParam->u32Address = u32Addr;
            pFlashParam->u32Length = u32TempLen;

            /* unlock sector */
            FLASHDRIVER_DFlashLockSector(pFlashParam->u32Address, 0U);
            tFlash_api_cfg.pgff = FLASH_REG_BIT_CFG_DISABLE;
            tFlash_api_cfg.dest = pFlashParam->u32Address;
            tFlash_api_cfg.size = (pFlashParam->u32Length / 4); /* one data is 4 bytes */
            tFlash_api_cfg.pData = (uint32_t *)u32DataAddr;
            tFlash_api_cfg.wdg_tune = WDG_TUNE_DISABLE;

            /* next address and length */
            u32Addr += u32TempLen;
            u32DataAddr += u32TempLen;
            u32Length -= u32TempLen;

            u32AlignOffset = 0U;

            /* start write */
            __asm(" cpsid i");
            u32Temp = s_pFlashDriver_RomApiHeader->FLASH_DRV_Program(&tFlash_api_cfg, FLASH_API_DISABLE, 0);
            __asm(" cpsie i");
            tRetVal = u32Temp == STATUS_SUCCESS ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;

            /* check erase operation valid */
            if (tRetVal != FLASH_ERROR_OK)
            {
                /* write operation failed, exit */
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                break;
            }
            else
            {
                /* FLASHDRIVER_LL_Delay(); */

                /* check write still in progress */
                tRetVal = FLASH_ERROR_FAILED;
                u32TryCount = 0;
                while ((tRetVal != FLASH_ERROR_OK) && (u32TryCount++ < 10000))
                {
                    u32Temp = s_pFlashDriver_RomApiHeader->FLASH_DRV_HV_Status_Check();
                    /* check if finished */
                    if (u32Temp == STATUS_HVOP)
                    {
                        tRetVal = FLASH_ERROR_FAILED;
                    }
                    else
                    {
                        tRetVal = FLASH_ERROR_OK;
                    }
                }


                if (tRetVal != FLASH_ERROR_OK)
                {
                    /* erasing timeout, exit */
                    pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                    break;
                }
                else
                {
                    /* check write result */
                    u32Temp = s_pFlashDriver_RomApiHeader->FLASH_DRV_Program_Clear();
                    tRetVal = (u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;

                    if (tRetVal != FLASH_ERROR_OK)
                    {
                        /* write failed, exit */
                        pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                        break;
                    }
                    else
                    {
                        /* trigger watchdog function */
                        if (pFlashParam->wdTriggerFct != ((void *)0))
                        {
                            pFlashParam->wdTriggerFct();
                        }

                    }
                }
            }
            /* lock data flash */
            FLASHDRIVER_DFlashLockSector(pFlashParam->u32Address, 1U);

        }
    }
    return tRetVal;
}
