/**
 * @file fc7xxx_driver_gpio.h
 * @author Flagchip
 * @brief FC7xxx GPIO driver type definition and API
 * @version 0.1.0
 * @date 2023-2-14
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       31/12/2022    Flagchip0121    N/A          First version for FC7240
********************************************************************************/

#include "fc7xxx_driver_gpio.h"

/** @brief Gpio instance list */
static GPIO_Type *s_pGpioInstanceTable[GPIO_INSTANCE_COUNT] = GPIO_BASE_PTRS;

/**
 * @brief Initialize GPIO.
 *
 * @param eGpio GPIO instance
 * @param pInitStruct Initialization structure of GPIO.
 */
GPIO_StatusType GPIO_InitPins(const GPIO_InstanceType eGpio, const GPIO_InitType *const pInitStruct)
{
    GPIO_StatusType eRet = GPIO_STATUS_SUCCESS;
    GPIO_Type *pGpio;
    uint32_t u32TempPins = 0U;
    uint8_t u8PinIndex = 0U;
    
    if ((uint32_t)eGpio >= GPIO_INSTANCE_COUNT)
    {
        eRet = GPIO_STATUS_PARAM_INVALID;
    }
    else
    {
        pGpio = s_pGpioInstanceTable[(uint32_t)(eGpio)];
        u32TempPins = pInitStruct->u32GpioPins;
        while (u32TempPins != 0u)
        {
            if ((u32TempPins & ((uint32_t)1 << u8PinIndex)) != 0u)
            {
                if (GPIO_OUT == pInitStruct->ePinDirection)
                {
                    if (GPIO_LOW == pInitStruct->ePinLevel)
                    {
                        GPIO_HWA_ClearPinOutput(pGpio, u8PinIndex);
                    }
                    else
                    {
                        GPIO_HWA_SetPinOutput(pGpio, u8PinIndex);
                    }
                    GPIO_HWA_SetPinDirection(pGpio, u8PinIndex);
                }
                else if (GPIO_IN == pInitStruct->ePinDirection)
				{
					GPIO_HWA_ClearPinDirection(pGpio, u8PinIndex);
				}
				else
				{
					GPIO_HWA_SetPinInputDisable(pGpio, u8PinIndex);   /* GPIO_ZERO == pInitStruct->ePinDirection */
				}
            }
            else
            {

            }
            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
        }
    }
    return eRet;
}
/**
 * @brief De-initialize the GPIO pin
 *
 * @param eGpio Gpio instance enumeration
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Gpio instance.
 * @return GPIO status type.
 */
GPIO_StatusType GPIO_Deinit(const GPIO_InstanceType eGpio, const uint32_t u32Pins)
{
    DEV_ASSERT(eGpio < GPIO_INSTANCE_COUNT);

    GPIO_StatusType eRet = GPIO_STATUS_SUCCESS;
    GPIO_Type *pGpio = s_pGpioInstanceTable[(uint32_t)(eGpio)];
    uint8_t u8PinIndex = 0U;
    uint32_t u32TempPins = u32Pins;

    while (u32TempPins != 0)
    {
        if (u32TempPins & ((uint32_t)1 << u8PinIndex))
            {
                GPIO_HWA_ClearPinDirection(pGpio, u8PinIndex);
                GPIO_HWA_ClearPinDataOutput(pGpio, u8PinIndex);
                GPIO_HWA_ClearPinInputDisable(pGpio, u8PinIndex);
            }
            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
    }
    return eRet;
}

/**
 * @brief Read level of input port pins.
 *
 * @param eGpio Port instance for GPIO functionality
 * @param u32Pins The bit of u32Pins indicate the pin number of this Port.
 * @return Pins level
 */
uint32_t GPIO_ReadPins(const GPIO_InstanceType eGpio, const uint32_t u32Pins)
{
    DEV_ASSERT(eGpio < GPIO_INSTANCE_COUNT);
    GPIO_Type *pGpio = s_pGpioInstanceTable[(uint32_t)eGpio];
    return (GPIO_HWA_ReadPortDataInput(pGpio) & u32Pins);
}

/**
 * @brief Write gpio level to u32Pins.
 *
 * @param eGpio Port instance for GPIO functionality
 * @param u32Pins The bit of u32Pins indicate the pin number of this Port.
 * @param eOutput Output level enumeration
 * @return Port return type.
 */
GPIO_StatusType GPIO_WritePins(const GPIO_InstanceType eGpio, const uint32_t u32Pins, const GPIO_PinLevelType eOutput)
{
    GPIO_StatusType eRet = GPIO_STATUS_SUCCESS;
    GPIO_Type *pGpio = s_pGpioInstanceTable[(uint32_t)eGpio];
    if (((uint32_t)eGpio >= GPIO_INSTANCE_COUNT) || (eOutput > GPIO_HIGH))
    {
        eRet = GPIO_STATUS_PARAM_INVALID;
    }
    else
    {
        if (GPIO_HIGH == eOutput)
        {
            GPIO_HWA_SetPortOutput(pGpio, u32Pins);
        }
        else
        {
            GPIO_HWA_ClearPortOutput(pGpio, u32Pins);
        }
    }
    return eRet;
}

/**
 * @brief Toggle gpio api
 *
 * @param eGpio eGpio Port instance for GPIO functionality
 * @param u32Pins The bit of u32Pins indicate the pin number of this Port.
 * @return Port return type.
 */
GPIO_StatusType GPIO_Toggle(const GPIO_InstanceType eGpio, const uint32_t u32Pins)
{
    GPIO_StatusType eRet = GPIO_STATUS_SUCCESS;
    GPIO_Type *pGpio = s_pGpioInstanceTable[(uint32_t)eGpio];
    if ((uint32_t)(eGpio >= GPIO_INSTANCE_COUNT))
    {
        eRet = GPIO_STATUS_PARAM_INVALID;
    }
    else
    {
        GPIO_HWA_TogglePort(pGpio, u32Pins);
    }
    return eRet;
}
