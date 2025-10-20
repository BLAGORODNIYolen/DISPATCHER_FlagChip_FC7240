/**
 * @file fc7xxx_driver_flash.c
 * @author Flagchip
 * @brief FC7xxx Flash driver type definition and API
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
   *   0.1.0       2024-01-11    Flagchip054   N/A          First version for FC7200
   ******************************************************************************** */
#ifndef _DRIVER_FC7XXX_DRIVER_FLASH_H_
#define _DRIVER_FC7XXX_DRIVER_FLASH_H_

#include "device_header.h"


/**
 * @addtogroup fc7xxx_driver_flash
 * @{
 */
/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/

/* ------------------------- PFlash ------------------------ */
/** PFlash start address */
#define PFLASH_ADDR_START                         0x01000000U

#define PFLASH_ADDR_END                           0x011FFFFFU

#define PFLASH_SIZE                               0x00200000U  /* 256KB */

#define PFLASH_BANK_SIZE                          0x00100000U

#define PFLASH_LAST256K_OFFSET                    0xC0000UL

/** Program minimum size */
#define PFLASH_PROGRAM_PAGE_MIN_SIZE              0x08U    /* 8 bytes   */
/** Program maximum */
#define PFLASH_PROGRAM_PAGE_MAX_SIZE              0x80U    /* 128 bytes  */

/** Erase size */
#define PFLASH_ERASE_SECTOR_SIZE                  0x800U   /* 2 KBytes   */

/** Erase value of flash memory       */
#define PFLASH_ERASED_VALUE                       0xFFU

/** 4 PFlash Banks, every bank is 2MB */
#define PFLASH_BANK_NUM                           0x02U


/* ------------------------- DFlash ------------------------ */

/** DFlash total size */
#define DFLASH_SIZE                               0x00040000U  /* 256KB */
/** DFlash start address */
#define DFLASH_ADDR_START                         0x04000000U
/** DFlash end address */
#define DFLASH_ADDR_END                           0x0401FFFFU

/** Program minimum size */
#define DFLASH_PROGRAM_PAGE_MIN_SIZE              0x08U    /* 16 bytes   */
/** Program maximum */
#define DFLASH_PROGRAM_PAGE_MAX_SIZE              0x80U    /* 128 bytes  */

/** Erase size */
#define DFLASH_ERASE_SECTOR_SIZE                  0x800U  /* 8 KBytes   */

/** Erase value of flash memory       */
#define DFLASH_ERASED_VALUE                       0xFFU

/** 1 DFlash Banks, every bank is 2MB */
#define DFLASH_BANK_NUM                           0x01U

/** DFlash Bank 0 size */
#define DFLASH_BANK0_SIZE                         0x00040000U



#define FLASH_256KB_SIZE                          0x00040000U


/** ########################################## Error Code ################################################ */


/**
 * \brief FLASH API error status
 *
 */
typedef enum
{
    FLASH_ERROR_OK                  =  0x00U,/**< FLASH_ERROR_OK means no error */
    FLASH_ERROR_NO_INIT,                     /**< FLASH_ERROR_NO_INIT means rom code api address is not initialed */
    FLASH_ERROR_INVALID_VERSION,             /**< FLASH_ERROR_INVALID_VERSION means rom code api version is not same */
    FLASH_ERROR_FAILED,                      /**< FLASH_ERROR_FAILED means operation is failed */
    FLASH_ERROR_INVALID_PARAM,               /**< FLASH_ERROR_INVALID_PARAM means parameters are invalid */
    FLASH_ERROR_INVALID_ADDR,                /**< FLASH_ERROR_INVALID_ADDR means address is invalid */
    FLASH_ERROR_INVALID_SIZE,                /**< FLASH_ERROR_INVALID_SIZE means size is invalid */
    FLASH_ERROR_INVALID_SEQUENCE,            /**< FLASH_ERROR_INVALID_SEQUENCE means sequence is error */
    FLASH_ERROR_TIMEOUT,                     /**< FLASH_ERROR_TIMEOUT means operation is timeout */
    FLASH_ERROR_END           = 0xFFFFFFFFU  /**< FLASH_ERROR_END make aligned 32bits */
}FLASH_StatusType;

typedef enum
{
    FLASH_BLOCK_SELECT0               =0x000u,
    FLASH_BLOCK_SELECT1               =0x001u,
    FLASH_DATA_BLOCK_SELECT0          =0x002u
}FLASH_API_BLOCK_SELECT_TYPE;

/** ########################################## Type define ################################################ */


/**
 * \brief Flash driver parameter define
 *
 */
typedef struct
{
    uint32_t         u32Address;             /**< Logical target address                  */
    uint32_t         u32Length;              /**< Length in logical sectors or bytes      */
    uint8_t          *pData;                 /**< Pointer to data buffer (read only)      */
    uint8_t         (*wdTriggerFct)(void);   /**< Pointer to watchdog handling function   */
    uint32_t         u32ErrorAddress;        /**< Error address                           */

} FLASH_DRIVER_ParamType;

/**
 * \brief Initial Flash api address
 *
 */
void FLASHDRIVER_Init(void);

/**
 * \brief flash driver erase block function
 *
 * \param blk_sel c
 * \return ErrorType
 */
FLASH_StatusType FLASHDRIVER_FlashEraseBlock ( FLASH_API_BLOCK_SELECT_TYPE blk_sel );

/**
 * \brief Pflash driver erase function, called after FLASHDRIVER_ArrayCopyToRam
 *
 * \param pFlashParam contains flash erase function parameter, address is align to 0x400, and length is align to 0x400
 * \return ErrorType
 */
FLASH_StatusType FLASHDRIVER_PFlashEraseSector ( FLASH_DRIVER_ParamType * pFlashParam );

/**
 * \brief Pflash driver write function, called after FLASHDRIVER_ArrayCopyToRam
 *
 * \param pFlashParam contains flash write function parameter, address is align to 0x08, and length is align to 0x08
 * \return ErrorType
 */
FLASH_StatusType FLASHDRIVER_PFlashWrite ( FLASH_DRIVER_ParamType * pFlashParam );

/**
 * \brief DFlash Driver Function for Erasing
 *
 * \param pFlashParam flash driver erase parameter
 * \return ErrorType
 */
FLASH_StatusType FLASHDRIVER_DFlashEraseSector(FLASH_DRIVER_ParamType *pFlashParam);

/**
 * \brief DFlash Driver Function for Writing
 *
 * \param pFlashParam flash driver write parameter
 * \return ErrorType
 */
FLASH_StatusType FLASHDRIVER_DFlashWrite(FLASH_DRIVER_ParamType *pFlashParam);


#endif /* end of DRIVER_FLASH_H_ */
