/**
 * @file fc7xxx_fcmath.h
 * @author Flagchip
 * @brief include fcmath file
 * @version 0.2.1
 * @date 2022-02-20
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */
#include "fcmath.h"


uint32_t Fc_Power(uint32_t num, uint32_t u8Power)
{
    uint8_t  u8Index;
    uint32_t u32RetVal;

    u32RetVal = 1;
    for(u8Index=0;u8Index<u8Power;u8Index++)
    {
        u32RetVal *=num;
    }

    return u32RetVal;
}



uint32_t Fc_Max(uint32_t u32Val1, uint32_t u32Val2)
{
    if(u32Val1>u32Val2)
        return u32Val1;
    else
        return u32Val2;
}


uint32_t Fc_Min(uint32_t u32Val1, uint32_t u32Val2)
{
    if(u32Val1>u32Val2)
        return u32Val2;
    else
        return u32Val1;
}
