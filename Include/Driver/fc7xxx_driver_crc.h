/**
 * @file fc7xxx_driver_crc.h
 * @author Flagchip
 * @brief FC7xxx CRC driver type definition and API
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2024-01-12    Flagchip119    N/A          First version for FC7240
********************************************************************************/
#ifndef _DRIVER_FC7XXX_DRIVER_CRC_H_
#define _DRIVER_FC7XXX_DRIVER_CRC_H_
#include "HwA_crc.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup fc7xxx_driver_crc
 * @{
 */

#define   CRC_INSTANCE   (0U)
#define   CRC_DEFAULT_POLY   (0x1021U)
#define   CRC_DEFAULT_INTVAL (0U)


/********* Local typedef ************/

/**
 * @brief Defines the crc configuration
 *
 * This structure is used to configure the crc
 *
 * Implements : CRC_InitType
 */
typedef struct
{
    uint32_t u32Polynomial;                       /*!< the polynomial value of crc */
    uint32_t u32SeedValue;                        /*!< the seed value of crc */
    CRC_WriteDataSwapType eWriteDataSwap;       /*!< the data swap for write(none,bits,bytes or both) */
    CRC_ReadDataSwapType eReadDataSwap;         /*!< the data swap for read(none,bits,bytes or both) */
    CRC_ReadDataFXORType eReadDataFXOR;         /*!< complement of reading crc data(none or FXOR) */
    CRC_BitWidthType eBitWidth;
} CRC_InitType;


/******* Function Prototype *********/
/**
 * @brief set CRC module initialization
 *
 * @param eInstance the CRC instance to use
 * @param pInitCfg the CRC_InitType type
 */
void CRC_Init(uint8_t u8Instance, const CRC_InitType *const pInitCfg);

/**
 * @brief CRC default Init
 *
 * @param eInstance the CRC instance to use
 * @note initialization CRC module with default value
 *       CRC-32, initial value(seed value) = 0,
 *       polynomial value = 0x1021,
 *       none swap and FXOR
 */
void CRC_DeInit(uint8_t u8Instance);

/**
 * @brief get CRC result
 *
 * @param eInstance the CRC instance to use
 */
uint32_t CRC_GetCrcResult(uint8_t u8Instance);

/**
 * @brief set CRC DATA register 8bits
 *
 * @param eInstance the CRC instance to use
 * @param u8Data the data to be set
 */
void CRC_SetCalcData_U8(uint8_t u8Instance, uint8_t u8Data);

/**
 * @brief set CRC DATA register 16bits
 *
 * @param eInstance the CRC instance to use
 * @param u16Data the data to be set
 */
void CRC_SetCalcData_U16(uint8_t u8Instance, uint16_t u16Data);

/**
 * @brief set CRC low lower register
 *
 * @param eInstance the CRC instance to use
 * @param u32Data the data to be set
 */
void CRC_SetCalcData_U32(uint8_t u8Instance, uint32_t u32Data);

/**
 * @brief set CRC seed value
 *
 * @param eInstance the CRC instance to use
 * @param u32SeedVal seed value
 */
void CRC_SetSeed(uint8_t u8Instance, uint32_t u32SeedVal);

/**
 * @brief set CRC input data
 *
 * @param eInstance the CRC instance to use
 * @param pData data pointer
 * @param u32DataSize input data size
 */
void CRC_SetInputData(uint8_t u8Instance, const uint8_t * pData, uint32_t u32DataSize);


/** @}*/ /* fc7xxx_driver_crc */
#if defined(__cplusplus)
}
#endif
#endif  /* _DRIVER_FC4XXX_DRIVER_CRC_H_ */

