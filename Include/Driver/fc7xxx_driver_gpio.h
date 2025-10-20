/**
 * @file fc7xxx_driver_gpio.h
 * @author Flagchip
 * @brief FC7xxx GPIO driver type definition and API
 * @version 0.1.0
 * @date 2023-2-14
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2022/12/31    Flagchip071    N/A          First version for FC7240
********************************************************************************/
#ifndef DRIVER_GPIO_H_
#define DRIVER_GPIO_H_
#include "HwA_gpio.h"

/**
 * @addtogroup fc7xxx_driver_port
 * @{
 */

/********* global define ************/

#define GPIO_MAX_PORT_PINS   32

#define GPIO_PIN_0        ((uint32_t)0x00000001)    /**< GPIO Pin 0 select */
#define GPIO_PIN_1        ((uint32_t)0x00000002)    /**< GPIO Pin 1 select */
#define GPIO_PIN_2        ((uint32_t)0x00000004)    /**< GPIO Pin 2 select */
#define GPIO_PIN_3        ((uint32_t)0x00000008)    /**< GPIO Pin 3 select */
#define GPIO_PIN_4        ((uint32_t)0x00000010)    /**< GPIO Pin 4 select */
#define GPIO_PIN_5        ((uint32_t)0x00000020)    /**< GPIO Pin 5 select */
#define GPIO_PIN_6        ((uint32_t)0x00000040)    /**< GPIO Pin 6 select */
#define GPIO_PIN_7        ((uint32_t)0x00000080)    /**< GPIO Pin 7 select */
#define GPIO_PIN_8        ((uint32_t)0x00000100)    /**< GPIO Pin 8 select */
#define GPIO_PIN_9        ((uint32_t)0x00000200)    /**< GPIO Pin 9 select */
#define GPIO_PIN_10       ((uint32_t)0x00000400)    /**< GPIO Pin 10 select */
#define GPIO_PIN_11       ((uint32_t)0x00000800)    /**< GPIO Pin 11 select */
#define GPIO_PIN_12       ((uint32_t)0x00001000)    /**< GPIO Pin 12 select */
#define GPIO_PIN_13       ((uint32_t)0x00002000)    /**< GPIO Pin 13 select */
#define GPIO_PIN_14       ((uint32_t)0x00004000)    /**< GPIO Pin 14 select */
#define GPIO_PIN_15       ((uint32_t)0x00008000)    /**< GPIO Pin 15 select */
#define GPIO_PIN_16       ((uint32_t)0x00010000)    /**< GPIO Pin 16 select */
#define GPIO_PIN_17       ((uint32_t)0x00020000)    /**< GPIO Pin 17 select */
#define GPIO_PIN_18       ((uint32_t)0x00040000)    /**< GPIO Pin 18 select */
#define GPIO_PIN_19       ((uint32_t)0x00080000)    /**< GPIO Pin 19 select */
#define GPIO_PIN_20       ((uint32_t)0x00100000)    /**< GPIO Pin 20 select */
#define GPIO_PIN_21       ((uint32_t)0x00200000)    /**< GPIO Pin 21 select */
#define GPIO_PIN_22       ((uint32_t)0x00400000)    /**< GPIO Pin 22 select */
#define GPIO_PIN_23       ((uint32_t)0x00800000)    /**< GPIO Pin 23 select */
#define GPIO_PIN_24       ((uint32_t)0x01000000)    /**< GPIO Pin 24 select */
#define GPIO_PIN_25       ((uint32_t)0x02000000)    /**< GPIO Pin 25 select */
#define GPIO_PIN_26       ((uint32_t)0x04000000)    /**< GPIO Pin 26 select */
#define GPIO_PIN_27       ((uint32_t)0x08000000)    /**< GPIO Pin 27 select */
#define GPIO_PIN_28       ((uint32_t)0x10000000)    /**< GPIO Pin 28 select */
#define GPIO_PIN_29       ((uint32_t)0x20000000)    /**< GPIO Pin 29 select */
#define GPIO_PIN_30       ((uint32_t)0x40000000)    /**< GPIO Pin 30 select */
#define GPIO_PIN_31       ((uint32_t)0x80000000)    /**< GPIO Pin 31 select */

/************************************global typedef ***************************************/

/** @brief GPIO return structure */
typedef enum
{
    GPIO_STATUS_SUCCESS = 0U,
    GPIO_STATUS_PARAM_INVALID = 1U
} GPIO_StatusType;

/** @brief GPIO instance number */
typedef enum
{
    GPIO_A = 0U,
    GPIO_B,
    GPIO_C,
    GPIO_D,
    GPIO_E
} GPIO_InstanceType;

/** @brief GPIO direction */
typedef enum
{
    GPIO_OUT    = 0U,      /* GPIO pin directon is output */
    GPIO_IN     = 1U,      /* GPIO pin directon is input */
    GPIO_ZERO   = 2U       /* GPIO pin directon is input disable */
} GPIO_PinDirectionType;

typedef struct
{
    uint32_t u32GpioPins;
    GPIO_PinDirectionType ePinDirection;
    GPIO_PinLevelType ePinLevel;
}GPIO_InitType;

/************************************global typedef ***************************************/

/**
 * @brief Initialize GPIO.
 *
 * @param eGpio GPIO instance
 * @param pInitStruct Initialization structure of GPIO.
 */
GPIO_StatusType GPIO_InitPins(const GPIO_InstanceType eGpio, const GPIO_InitType *const pInitStruct);

/**
 * @brief Initialize GPIO.
 *
 * @param eGpio GPIO instance
 * @param u32Pins The bit of u32Pins indicate the pin number of this GPIO.
 */
GPIO_StatusType GPIO_Deinit(const GPIO_InstanceType eGpio, const uint32_t u32Pins);

/**
 * @brief Read level of input port pins.
 *
 * @param ePort Port instance for GPIO functionality
 * @param u32Pins The bit of u32Pins indicate the pin number of this Port.
 * @return Pins level
 */
uint32_t GPIO_ReadPins(const GPIO_InstanceType ePort, const uint32_t u32Pins);

/**
 * @brief Write gpio level to u32Pins.
 *
 * @param ePort Port instance for GPIO functionality
 * @param u32Pins The bit of u32Pins indicate the pin number of this Port.
 * @param eOutput Output level enumeration
 * @return Port return type.
 */
GPIO_StatusType GPIO_WritePins(const GPIO_InstanceType ePort, const uint32_t u32Pins, const GPIO_PinLevelType eOutput);

/**
 * @brief Toggle gpio api
 *
 * @param ePort ePort Port instance for GPIO functionality
 * @param u32Pins The bit of u32Pins indicate the pin number of this Port.
 * @return Port return type.
 */
GPIO_StatusType GPIO_Toggle(const GPIO_InstanceType ePort, const uint32_t u32Pins);


#endif /* end of DRIVER_GPIO_H_ */
