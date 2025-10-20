/**
 * @file fc7xxx_driver_cordic.c
 * @author Flagchip
 * @brief FC7xxx Cordic driver source code
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
#include "fc7xxx_driver_cordic.h"
#include "interrupt_manager.h"

#define CORDIC_SIGN_BIT               0x80000000UL
#define CORDIC_EXP_BIT                0x7F800000UL
#define CORDIC_TAIL_BIT               0x007FFFFFUL

#define REVERSE_SCALEING_FACTOR_K     0x4dba76b2
#define REVERSE_SCALEING_FACTOR_KA    0x9A8F4314

#define USE_FPU_HARDWARE 0


/**
 * @brief Floating-point conversion to 24 bit fixed-point
 *
 * @param nFloat Input value
 */


/*************** Local Functions ***************/
/**
   * @brief Clips Q63 to Q31 values.
   */
__attribute__((always_inline)) static inline int32_t clip_q63_to_q31(
            int64_t x)
{
    return ((int32_t)(x >> 32) != ((int32_t) x >> 31)) ?
           ((0x7FFFFFFF ^ ((int32_t)(x >> 63)))) : (int32_t) x;
}


static int32_t Float2Fix_Convert(const float data)
{
    return clip_q63_to_q31((int64_t)(data * 2147483648.0f));
}

/*****************  Global Functions *******************/
/**
 * @brief The function to calculate sin & cos
 *
 * @param radian the input value to calculate
 *
 * input range (−90°, +90°)/180°
 */
CORDIC_SinCos_Type Cordic_Circular_Sin_Cos(const float radian)
{
    /* angles are expressed in radian, multiplied by a constant number. 𝜃/180 * 𝜋c (where 𝜋c is 13.42177) */
    CORDIC_SinCos_Type tRetVal;
    //float tmp = REVERSE_SCALEING_FACTOR_K;
    float tmp = 0;
    int32_t fix_radian = Float2Fix_Convert(radian);
    int32_t x_input = REVERSE_SCALEING_FACTOR_K;
    Cordic_HWA_Set_XInput(x_input);
    Cordic_HWA_Set_YInput(0);
    Cordic_HWA_Set_ZInput(fix_radian);
    /* Disable interrupt + Iteration Number16 + Trigonometric system + Rotate mode */
    Cordic_HWA_SetCtrl(CORDIC_CTR_VAL(0, false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Trigonometric, (uint32_t)CORDIC_Rotate));
    while (!Cordic_HWA_Get_Stat()) {}
    tmp = (int32_t)Cordic_HWA_Get_YOutput() / 2147483648.f; //134217728.f;
    tRetVal.sinx = tmp;
    tmp = (int32_t)Cordic_HWA_Get_XOutput() / 2147483648.f; //134217728.f;
    tRetVal.cosx = tmp;
    return tRetVal;
}

/**
 * @brief The function to calculate circular radical add
 *
 * @param1 x the first input value
 *
 * @param2 y the second input value
 */
CORDIC_Radical_Type Cordic_Circular_Radical_Add(const float x, const float y)
{
    CORDIC_Radical_Type tRetVal;
    /*** 40752053.5625 = REVERSE_SCALEING_FACTOR_K / 32 ***/
    int32_t x_input = (int32_t)(40752053.5625 * x);
    int32_t y_input = (int32_t)(40752053.5625 * y);
    Cordic_HWA_Set_XInput(x_input);
    Cordic_HWA_Set_YInput(y_input);
    Cordic_HWA_Set_ZInput(0);
    /* Disable interrupt + Iteration Number16 + Trigonometric system + Vector mode */
    Cordic_HWA_SetCtrl(CORDIC_CTR_VAL(5, false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Trigonometric, (uint32_t)CORDIC_Vector));
    while (!Cordic_HWA_Get_Stat()) {}
    /*** 67,108,864 = 2147483648.f / 32 ***/
    tRetVal = Cordic_HWA_Get_XOutput() / 67108864.f;
    return tRetVal;
}

/**
 * @brief The function to calculate circular arctan
 *
 * @param y the input value
 */
CORDIC_Arctan_Type Cordic_Circular_Arctan_F(const float y)
{
    CORDIC_Arctan_Type tRetVal;
    if ((y > 96.6) || (y < -96.6))
    {
        tRetVal = 89.4069;
    }
    else
    {
        int32_t x_input = 2147484;
        int32_t y_input = (int32_t)(y * 2147484);
        Cordic_HWA_Set_XInput(x_input);
        Cordic_HWA_Set_YInput(y_input);
        Cordic_HWA_Set_ZInput(0);
        /* Disable interrupt + Iteration Number16 + Trigonometric system + Vector mode */
        Cordic_HWA_SetCtrl(CORDIC_CTR_VAL(0, false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Trigonometric, (uint32_t)CORDIC_Vector));
        while (!Cordic_HWA_Get_Stat()) {}
        /*** 11,930,464.711111 = 12147483648 / 180 ***/;
        tRetVal = (int32_t)Cordic_HWA_Get_ZOutput() / 11930464.711111;
    }
    return tRetVal;
}

/**
 * @brief The function to calculate circular arctan
 *
 * @param1 x the first input value
 *
 * @param2 y the second input value
 */
CORDIC_Arctan_Type Cordic_Circular_Arctan(const int32_t x, const int32_t y)
{
    CORDIC_Arctan_Type tRetVal;

    Cordic_HWA_Set_XInput(x);
    Cordic_HWA_Set_YInput(y);
    Cordic_HWA_Set_ZInput(0);
    /* Disable interrupt + Iteration Number16 + Trigonometric system + Vector mode */
    Cordic_HWA_SetCtrl(CORDIC_CTR_VAL(0, false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Trigonometric, (uint32_t)CORDIC_Vector));
    while (!Cordic_HWA_Get_Stat()) {}
    /*** 11,930,464.711111 = 12147483648 / 180 ***/;
    tRetVal = (int32_t)Cordic_HWA_Get_ZOutput() / 11930464.711111;
    return tRetVal;
}

/**
 * @brief The function to calculate circular Sinh & Cosh
 *
 * @param z the input value
 */
CORDIC_SinhCosh_Type Cordic_Circular_Sinh_Cosh(const float z)
{
    CORDIC_SinhCosh_Type tRetVal;
    float tmp = 0;

    /*** 1073741824 = 2147483648 / 2 ***/
    int32_t z_input = (int32_t)(z * 1073741824.f);
    /*** 1296540042 = REVERSE_SCALEING_FACTOR_KA / 2 ***/
    int32_t x_input = 1296540042;

    Cordic_HWA_Set_XInput(x_input);
    Cordic_HWA_Set_YInput(0);
    Cordic_HWA_Set_ZInput(z_input);
    /* Scale 1 + Disable interrupt + Iteration Number16 + Hyperbolic system + Rotate mode */
    Cordic_HWA_SetCtrl(CORDIC_CTR_VAL(1, false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Hyperbolic, (uint32_t)CORDIC_Rotate));
    while (!Cordic_HWA_Get_Stat()) {}
    /*** 1073741824 = 2147483648 / 2 ***/
    tmp = (int32_t)Cordic_HWA_Get_YOutput() / 1073741824.f ;
    tRetVal.sinxh = tmp;
    /*** 1073741824 = 2147483648 / 2 ***/
    tmp = (int32_t)Cordic_HWA_Get_XOutput() / 1073741824.f;
    tRetVal.cosxh = tmp;
    return tRetVal;
}

/**
 * @brief The function to calculate circular radical sub
 *
 * @param1 x the first input value
 *
 * @param2 y the second input value
 */
CORDIC_Radical_Type Cordic_Circular_Radical_Sub(const float x, const float y)
{
    CORDIC_Radical_Type tRetVal;
    /*** 162067505 = REVERSE_SCALEING_FACTOR_KA / 16 ***/
    int32_t x_input = (int32_t)(162067505.f * x);
    int32_t y_input = (int32_t)(162067505.f * y);

    Cordic_HWA_Set_XInput(x_input);
    Cordic_HWA_Set_YInput(y_input);
    Cordic_HWA_Set_ZInput(0);
    /* Disable interrupt + Iteration Number16 + Hyperbolic system + Vector mode */
    Cordic_HWA_SetCtrl(CORDIC_CTR_VAL(4, false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Hyperbolic, (uint32_t)CORDIC_Vector));
    while (!Cordic_HWA_Get_Stat()) {}
    /*** 134217728 = 2147483648.f / 16 ***/
    tRetVal = Cordic_HWA_Get_XOutput() / 134217728.f;
    return tRetVal;
}

/**
 * @brief The function to calculate circular arctanh
 *
 * @param y the input value
 */
CORDIC_Arctanh_Type Cordic_Circular_Arctanh(const float y)
{
    CORDIC_Arctanh_Type tRetVal;

    /*** 1073741824 = 2147483648 / 2 ***/
    int32_t x_input = 1073741824;
    int32_t y_input = (int32_t)(y * 1073741824.f);

    Cordic_HWA_Set_XInput(x_input);
    Cordic_HWA_Set_YInput(y_input);
    Cordic_HWA_Set_ZInput(0);
    /* Disable interrupt + Iteration Number16 + Hyperbolic system + Vector mode */
    Cordic_HWA_SetCtrl(CORDIC_CTR_VAL(1, false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Hyperbolic, (uint32_t)CORDIC_Vector));
    while (!Cordic_HWA_Get_Stat()) {}
    /*** 1073741824 = 2147483648 / 2 ***/
    tRetVal = (int32_t)Cordic_HWA_Get_ZOutput() / 1073741824.f;
    return tRetVal;
}

/**
 * @brief The function to calculate ln
 *
 * @param y the input value (0.1068482375 , 9.3590687463)
 */
CORDIC_Ln_Type Cordic_Extended_LN(const float y)
{
    CORDIC_Ln_Type tRetVal;
    /*** 134217728 = 2147483648 / 16 ***/
    int32_t x_input = (int32_t)((y + 1) * 134217728.f);
    int32_t f_input = (int32_t)((y - 1) * 134217728.f);
    Cordic_HWA_Set_XInput(x_input);
    Cordic_HWA_Set_YInput(f_input);
    Cordic_HWA_Set_ZInput(0);
    /* Disable interrupt + Iteration Number16 + Hyperbolic system + Vector mode */
    Cordic_HWA_SetCtrl(CORDIC_CTR_VAL(4, false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Hyperbolic, (uint32_t)CORDIC_Vector));
    while (!Cordic_HWA_Get_Stat()) {}
    /*** 67108864 = 12147483648.f / 32 ***/;
    tRetVal = (int32_t)Cordic_HWA_Get_ZOutput() / 67108864.f;
    return tRetVal;
}

/**
 * @brief The function to calculate sqrt
 *
 * @param y the input value (0.0267120594,2.3397671865)
 */
CORDIC_Ln_Type Cordic_Extended_Sqrt(const float y)
{
    CORDIC_Radical_Type tRetVal;
    /*** 648270021 = 2593080084 / 4 ***/
    int32_t x_input = (int32_t)(648270021.f * (y + 0.25));
    int32_t y_input = (int32_t)(648270021.f * (y - 0.25));

    Cordic_HWA_Set_XInput(x_input);
    Cordic_HWA_Set_YInput(y_input);
    Cordic_HWA_Set_ZInput(0);
    /* Disable interrupt + Iteration Number16 + Hyperbolic system + Vector mode */
    Cordic_HWA_SetCtrl(CORDIC_CTR_VAL(2, false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Hyperbolic, (uint32_t)CORDIC_Vector));
    while (!Cordic_HWA_Get_Stat()) {}
    /*** 536870912 = 2147483648 / 4 ***/
    tRetVal = Cordic_HWA_Get_XOutput() / 536870912.f;
    return tRetVal;
}
