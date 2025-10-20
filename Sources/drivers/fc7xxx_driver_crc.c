/**
 * @file fc7xxx_driver_crc.c
 * @author Flagchip
 * @brief FC7xxx CRC driver source code
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

#include "fc7xxx_driver_crc.h"



/********* Local Variables ************/
static CRC_Type *const s_apCrcBase[CRC_INSTANCE_COUNT] = CRC_BASE_PTRS;


/********* Local Functions ************/

void CRC_Init(uint8_t u8Instance, const CRC_InitType *const pInitCfg)
{
    DEV_ASSERT(u8Instance < CRC_INSTANCE_COUNT);
    DEV_ASSERT(pInitCfg != NULL);
    CRC_Type *const pCrc = s_apCrcBase[u8Instance];

    if (pInitCfg->eBitWidth == CRC_BIT_8)
    {
    	/* set CRC bit width(8-bit) */
    	CRC_HWA_Set_8Bit_Width(pCrc, (CRC_BitWidthType)(pInitCfg->eBitWidth - 1));
        CRC_HWA_SetBitWidth(pCrc, (CRC_BitWidthType)0);
    }
    else
    {
    	/* set CRC bit width(16-bit or 32-bit) */
    	CRC_HWA_Set_8Bit_Width(pCrc, (CRC_BitWidthType)0);
        CRC_HWA_SetBitWidth(pCrc, pInitCfg->eBitWidth);
    }

    /* set CRC write/read swap and FXOR */
    CRC_HWA_SetWriteDataSwap(pCrc, pInitCfg->eWriteDataSwap);
    CRC_HWA_SetReadDataSwap(pCrc, pInitCfg->eReadDataSwap);
    CRC_HWA_SetReadDataFXOR(pCrc, pInitCfg->eReadDataFXOR);

    /* set CRC polynomial value */
    CRC_HWA_SetPolyVal(pCrc, pInitCfg->u32Polynomial);

    /* set CRC seed value */
    CRC_SetSeed(u8Instance, pInitCfg->u32SeedValue);
}

void CRC_DeInit(uint8_t u8Instance)
{
    DEV_ASSERT(u8Instance < CRC_INSTANCE_COUNT);
    CRC_Type *const pCrc = s_apCrcBase[u8Instance];

    /* set CRC bit width(32-bit) */
    CRC_HWA_SetBitWidth(pCrc, CRC_BIT_32);

    /* set CRC write/read swap and FXOR */
    CRC_HWA_SetWriteDataSwap(pCrc, WRITE_DATASWAP_NONE);
    CRC_HWA_SetReadDataSwap(pCrc, READ_DATASWAP_NONE);
    CRC_HWA_SetReadDataFXOR(pCrc, READ_DATA_NORMAL);

    /* set CRC polynomial value */
    CRC_HWA_SetPolyVal(pCrc, CRC_DEFAULT_POLY);

    /* set CRC seed value */
    CRC_SetSeed(u8Instance, CRC_DEFAULT_INTVAL);
}

uint32_t CRC_GetCrcResult(uint8_t u8Instance)
{
    DEV_ASSERT(u8Instance < CRC_INSTANCE_COUNT);
    CRC_Type *const pCrc = s_apCrcBase[u8Instance];
    CRC_ReadDataSwapType eTempVal;
    uint32_t u32Ret;

    eTempVal = CRC_HWA_GetReadDataSwap(pCrc);

    if (CRC_BIT_8 == CRC_HWA_Get8BitWidth(pCrc))
    {
        /* Returns upper 8 bits of CRC because of swap in 8 bits mode */
        if ((eTempVal == READ_DATASWAP_BIT_BYTE) || (eTempVal == READ_DATASWAP_BYTE))
        {
            u32Ret = CRC_HWA_GetData_U8_H(pCrc);
        }
        else
        {
            u32Ret = CRC_HWA_GetData_U8_L(pCrc);
        }
        return u32Ret;
    }
    else if (CRC_BIT_16 == CRC_HWA_GetBitWidth(pCrc))
    {
        /* Returns upper 16 bits of CRC because of swap in 16 bits mode */
        if ((eTempVal == READ_DATASWAP_BIT_BYTE) || (eTempVal == READ_DATASWAP_BYTE))
        {
            u32Ret = CRC_HWA_GetData_U16_H(pCrc);
        }
        else
        {
            u32Ret = CRC_HWA_GetData_U16_L(pCrc);
        }
    }
    else
    {
        u32Ret = CRC_HWA_GetData_U32(pCrc);
    }

    return u32Ret;
}

void CRC_SetCalcData_U8(uint8_t u8Instance, uint8_t u8Data)
{
    DEV_ASSERT(u8Instance < CRC_INSTANCE_COUNT);
    CRC_Type *const pCrc = s_apCrcBase[u8Instance];

    CRC_HWA_SetData_U8(pCrc, u8Data);
}

void CRC_SetCalcData_U16(uint8_t u8Instance, uint16_t u16Data)
{
    DEV_ASSERT(u8Instance < CRC_INSTANCE_COUNT);
    CRC_Type *const pCrc = s_apCrcBase[u8Instance];

    CRC_HWA_SetData_U16(pCrc, u16Data);
}

void CRC_SetCalcData_U32(uint8_t u8Instance, uint32_t u32Data)
{
    DEV_ASSERT(u8Instance < CRC_INSTANCE_COUNT);
    CRC_Type *const pCrc = s_apCrcBase[u8Instance];

    CRC_HWA_SetData_U32(pCrc, u32Data);
}

void CRC_SetSeed(uint8_t u8Instance, uint32_t u32SeedVal)
{
    DEV_ASSERT(u8Instance < CRC_INSTANCE_COUNT);
    CRC_Type *const pCrc = s_apCrcBase[u8Instance];

    CRC_HWA_SetDataOrSeed(pCrc, WRITE_COMMAND_SEED);
    CRC_HWA_SetData_U32(pCrc, u32SeedVal);
    CRC_HWA_SetDataOrSeed(pCrc, WRITE_COMMAND_DATA);
}

void CRC_SetInputData(uint8_t u8Instance, const uint8_t pData[], uint32_t u32DataSize)
{
    DEV_ASSERT(u8Instance < CRC_INSTANCE_COUNT);
    uint32_t i;

    for (i = 0U; i < u32DataSize; i++)
    {
        CRC_SetCalcData_U8(u8Instance, pData[i]);
    }
}


