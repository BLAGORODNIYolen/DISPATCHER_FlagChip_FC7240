/**
 * @file fc7xxx_driver_fmc.h
 * @author Flagchip
 * @brief FC7xxx FMC driver type definition and API
 * @version 0.1.0
 * @date 2024-01-5
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
  *   Revision History:
  *
  *   Version     Date          Initials      CR#          Descriptions
  *   ---------   ----------    ------------  ----------   ---------------
  *   0.1.0       2024-1-5      Flagchip120   N/A          First version for FC7240
  ******************************************************************************** */
#ifndef _DRIVER_FC7XXX_DRIVER_FMC_H_
#define _DRIVER_FC7XXX_DRIVER_FMC_H_
#include "device_header.h"
#include "HwA_fmc.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup fc7xxx_driver_fmc
 * @{
 */

/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/
/** Program minimum size */
#define FLASH_PROGRAM_PAGE_SIZE                  0x10U    /* 16 bytes   */

/** Erase size */
#define FLASH_ERASE_SECTOR_SIZE                  0x800U   /* 2 KBytes   */

/* ------------------------- PFlash ------------------------ */
/** PFlash start address */
#define PFLASH_ADDR_START                         0x01000000U

/** Erase value of flash memory       */
#define PFLASH_ERASED_VALUE                       0xFFU

/** 2 PFlash Banks, every bank is 1MB */
#define PFLASH_BANK_NUM                           0x02U

#define PFLASH_TOTAL_SIZE                         0x200000U

#define PFLASH_BANK_SIZE                          0x100000U

#define PFLASH_PHANTOM_OFFSET                     0xC0000UL

/* ------------------------- DFlash ------------------------ */

/** DFlash total size */
#define DFLASH_SIZE                               0x00020000U  /* 128KB */
/** DFlash start address */
#define DFLASH_ADDR_START                         0x04000000U
/** DFlash end address */
#define DFLASH_ADDR_END                           0x0401FFFFU

/** Erase value of flash memory       */
#define DFLASH_ERASED_VALUE                       0xFFU

/** 1 DFlash Banks, every bank is 2MB */
#define DFLASH_BANK_NUM                           0x01U

/** DFlash Bank 0 size */
#define DFLASH_BANK0_SIZE                         0x00020000U


#define FLASH_256KB_SIZE                          0x00040000U

/** ########################################## Error Code ################################################ */


/**
 * \brief FMC lock API error status
 *
 */
typedef enum
{
    FMC_LOCK_ERROR_OK                  =  0x00U,/**< FMC_LOCK_ERROR_OK means no error */
    FMC_LOCK_ERROR_FAILED,                      /**< FMC_LOCK_ERROR_FAILED means operation is failed */
    FMC_LOCK_ERROR_INVALID_PARAM,               /**< FMC_LOCK_ERROR_INVALID_PARAM means parameters are invalid */
    FMC_LOCK_ERROR_INVALID_ADDR,                /**< FMC_LOCK_ERROR_INVALID_ADDR means address is invalid */
    FMC_LOCK_ERROR_INVALID_SIZE,                /**< FMC_LOCK_ERROR_INVALID_SIZE means size is invalid */
    FMC_LOCK_ERROR_INVALID_SEQUENCE             /**< FMC_LOCK_ERROR_INVALID_SEQUENCE means sequence is error */
} FMC_Lock_StatusType;


/** ########################################## Type define ################################################ */

/**
 * \brief The instance index of the FMC peripheral
 *
 */
typedef enum
{
    FMC_INSTANCE_0 = 0x000u,  /*!< FMC instance 0 is selected */
    FMC_INSTANCE_1 = 0x001u  /*!< FMC instance 1 is selected */
} FMC_InstanceType;

/**
 * \brief FMC lock type
 *
 */
typedef enum
{
    FMC_UNLOCK           = 0x000u,
    FMC_LOCK             = 0x001u
} FMC_API_LOCK_TYPE;

/**
 * \brief FMC Flash type
 *
 */
typedef enum
{
    FMC_PFlash          = 0x000u,
    FMC_DFlash          = 0x001u
} FMC_API_FLASH_TYPE;

/**
 * \brief FMC Flash type
 *
 */
typedef enum
{
    FMC_Page          = 0x000u,
    FMC_Sector        = 0x001u
} FMC_API_CLASS_TYPE;

/**
 * \brief FMC active block type
 *
 */
typedef enum
{
    FMC_Active0          = 0x000u,
    FMC_Active1          = 0x001u
} FMC_API_ACTIVE_BLOCK_TYPE;

/**
 * \brief Flash driver parameter define
 *
 */
typedef struct
{
    uint32_t                    u32Address;             /**< Logical target address                  */
    uint32_t                    u32Length;              /**< Length in logical sectors or pages      */
    uint32_t                    u32ErrorAddress;        /**< Error address                           */
    FMC_API_LOCK_TYPE           bLock;                  /**< lock type                               */
    FMC_API_FLASH_TYPE          bFlash;                 /**< flash type                              */
    FMC_API_CLASS_TYPE          bClass;                 /**< class type                              */
    FMC_InstanceType            bFMC;                   /**< FMC instance                            */
} FMC_DRIVER_Lock_ParamType;

/**
 * \brief FMC Driver Function for flash lock
 *
 * \param pFmcParam FMC driver flash lock parameter
 * \return ErrorType
 */

FMC_Lock_StatusType FMCDRIVER_FlashLock(FMC_DRIVER_Lock_ParamType *pFmcParam);


/**
 * \brief FMC set ota active block
 *
 * \param eInstance  FMC instance
 * \param bLock 0U-active block 0, 1U-active block 1
 */
void FMCDRIVER_SwapBlock(const FMC_InstanceType eInstance, FMC_API_ACTIVE_BLOCK_TYPE bActive);

#if defined(__cplusplus)
}
#endif

/** @}*/ /* fc7xxx_driver_fmc */
#endif
