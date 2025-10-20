/**
 * @file fc7xxx_driver_cordic.h
 * @author Flagchip
 * @brief FC7xxx Cordic driver type definition and API
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
#ifndef _DRIVER_FC7XXX_DRIVER_CORDIC_H_
#define _DRIVER_FC7XXX_DRIVER_CORDIC_H_

#include "device_header.h"
#include "HwA_cordic.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief The circular Sin and cos type
 *
 */
typedef struct
{
    float sinx;
    float cosx;
} CORDIC_SinCos_Type;

/**
 * @brief The circular Sinh and cosh type
 *
 */
typedef struct
{
    float sinxh;
    float cosxh;
} CORDIC_SinhCosh_Type ;

/**
 * @brief The radical type
 *
 */
typedef  float CORDIC_Radical_Type;

/**
 * @brief The arctan type
 *
 */
typedef  float CORDIC_Arctan_Type;

/**
 * @brief The arctanh type
 *
 */
typedef  float CORDIC_Arctanh_Type;

/**
 * @brief The arctan type
 *
 */
typedef  float CORDIC_Ln_Type;

/**
 * @brief The arctanh type
 *
 */
typedef  float CORDIC_Sqrt_Type;

/**
 * @brief The function to calculate sin & cos
 *
 * @param radian the input value to calculate
 */
CORDIC_SinCos_Type Cordic_Circular_Sin_Cos(const float radian);

/**
 * @brief The function to calculate circular radical add
 *
 * @param1 x the first input value
 *
 * @param2 y the second input value
 */
CORDIC_Radical_Type Cordic_Circular_Radical_Add(const float x, const float y);

/**
 * @brief The function to calculate circular arctan
 *
 * @param y the input value
 */
CORDIC_Arctan_Type Cordic_Circular_Arctan_F(const float y);

/**
 * @brief The function to calculate circular arctan
 *
 * @param1 x the first input value
 *
 * @param2 y the second input value
 */
CORDIC_Arctan_Type Cordic_Circular_Arctan(const int32_t x, const int32_t y);

/**
 * @brief The function to calculate circular Sinh & Cosh
 *
 * @param z the input value
 */
CORDIC_SinhCosh_Type Cordic_Circular_Sinh_Cosh(const float z);

/**
 * @brief The function to calculate circular radical sub
 *
 * @param1 x the first input value
 *
 * @param2 y the second input value
 */
CORDIC_Radical_Type Cordic_Circular_Radical_Sub(const float x, const float y);

/**
 * @brief The function to calculate circular arctanh
 *
 * @param y the input value
 */
CORDIC_Arctanh_Type Cordic_Circular_Arctanh(const float y);
/**
 * @brief The function to calculate ln
 *
 * @param y the input value
 */
CORDIC_Ln_Type Cordic_Extended_LN(const float y);

/**
 * @brief The function to calculate sqrt
 *
 * @param y the input value (0.0267120594,2.3397671865)
 */
CORDIC_Sqrt_Type Cordic_Extended_Sqrt(const float y);

#if defined(__cplusplus)
}
#endif

#endif /* end of DRIVER_UART_H_ */
