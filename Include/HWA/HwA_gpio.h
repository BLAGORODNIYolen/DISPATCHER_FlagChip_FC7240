/**
 * @file HwA_gpio.h
 * @author Flagchip
 * @brief FC7xxx GPIO hardware access layer
 * @version 0.1.0
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2022-11-18    Flagchip071   N/A          First version for FC7xxx
   ******************************************************************************** */

#ifndef _HWA_GPIO_H_
#define _HWA_GPIO_H_

#include "device_header.h"

/** @brief GPIO initialization level */
typedef enum
{
    GPIO_LOW  = 0U,
    GPIO_HIGH = 1U
} GPIO_PinLevelType;


/**
 * @brief Set port data output, port output can set 1 or 0
 *
 * @param pGpio Gpio instance
 * @param u32Value Written value
 */
LOCAL_INLINE void GPIO_HWA_ConfigPortDataOutput(GPIO_Type *pGpio, uint32_t u32Value)
{
    pGpio->PDOR = u32Value;
}

/**
 * @brief Set pin data output, pin output can set 1 or 0
 *
 * @param pGpio Gpio instance
 * @param u32Pin Pin mask
 * @param ePinLevel Pin level
 */
LOCAL_INLINE void GPIO_HWA_ConfigPinDataOutput(GPIO_Type *pGpio, uint32_t u32Pin, GPIO_PinLevelType ePinLevel)
{
    if (GPIO_HIGH == ePinLevel)
    {
        pGpio->PDOR |= GPIO_PDOR_PDO(u32Pin);
    }
    else
    {
        pGpio->PDOR &= ~GPIO_PDOR_PDO(u32Pin);
    }
}

/**
 * @brief Set port output to 1
 *
 * @param pGpio Gpio instance
 * @param u32Value Written value
 */
LOCAL_INLINE void GPIO_HWA_SetPortOutput(GPIO_Type *pGpio, uint32_t u32Value)
{
    pGpio->PSOR |= u32Value;
}

/**
 * @brief Set port output to 0
 *
 * @param pGpio Gpio instance
 * @param u32Value Written value
 */
LOCAL_INLINE void GPIO_HWA_ClearPortOutput(GPIO_Type *pGpio, uint32_t u32Value)
{
    pGpio->PCOR |= u32Value;
}

/**
 * @brief Toggle port output
 *
 * @param pGpio Gpio instance
 * @param u32Value Written value
 */
LOCAL_INLINE void GPIO_HWA_TogglePort(GPIO_Type *pGpio, uint32_t u32Value)
{
    pGpio->PTOR = u32Value;
}

/**
 * @brief Set port direction
 *
 * @param pGpio Gpio instance
 * @param u32Value Written value
 */
LOCAL_INLINE void GPIO_HWA_SetPortDirection(GPIO_Type *pGpio, uint32_t u32Value)
{
    pGpio->PDDR = u32Value;
}

/**
 * @brief Set port input disable
 *
 * @param pGpio Gpio instance
 * @param u32Value Written value
 */
LOCAL_INLINE void GPIO_HWA_SetPortInputDisable(GPIO_Type *pGpio, uint32_t u32Value)
{
    pGpio->PIDR = u32Value;
}


/**
 * @brief Read port data output
 *
 * @param pGpio Gpio instance
 * @return PDOR register value
 */
LOCAL_INLINE uint32_t GPIO_HWA_ReadPortDataOutput(GPIO_Type *pGpio)
{
    return pGpio->PDOR;
}

/**
 * @brief Read port data input, this register indicate data on pad.
 *
 * @param pGpio Gpio instance
 * @return PDIR register value
 */
LOCAL_INLINE uint32_t GPIO_HWA_ReadPortDataInput(GPIO_Type *pGpio)
{
    return pGpio->PDIR;
}


/**
 * @brief Set pin data output, pin output can set 1 or 0
 *
 * @param pGpio Gpio instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void GPIO_HWA_SetPinDataOutput(GPIO_Type *pGpio, uint8_t u8Pin)
{
    pGpio->PDOR |= (uint32_t)1 << u8Pin;
}

/**
 * @brief Set pin output to 1
 *
 * @param pGpio Gpio instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void GPIO_HWA_SetPinOutput(GPIO_Type *pGpio, uint8_t u8Pin)
{
    pGpio->PSOR |= (uint32_t)1 << u8Pin;
}

/**
 * @brief Set pin output to 0
 *
 * @param pGpio Gpio instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void GPIO_HWA_ClearPinOutput(GPIO_Type *pGpio, uint8_t u8Pin)
{
    pGpio->PCOR |= (uint32_t)1 << u8Pin;
}

/**
 * @brief Toggle pin
 *
 * @param pGpio Gpio instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void GPIO_HWA_TogglePin(GPIO_Type *pGpio, uint8_t u8Pin)
{
    pGpio->PTOR |= (uint32_t)1 << u8Pin;
}

/**
 * @brief Set pin direction
 *
 * @param pGpio Gpio instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void GPIO_HWA_SetPinDirection(GPIO_Type *pGpio, uint8_t u8Pin)
{
    pGpio->PDDR |= (uint32_t)1 << u8Pin;
}

/**
 * @brief Set pin input disable
 *
 * @param pGpio Gpio instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void GPIO_HWA_SetPinInputDisable(GPIO_Type *pGpio, uint8_t u8Pin)
{
    pGpio->PIDR |= (uint32_t)1 << u8Pin;
}


/**
 * @brief Clear pin data output
 *
 * @param pGpio Gpio instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void GPIO_HWA_ClearPinDataOutput(GPIO_Type *pGpio, uint8_t u8Pin)
{
    pGpio->PDOR &= ~((uint32_t)1 << u8Pin);
}

/**
 * @brief Clear pin direction
 *
 * @param pGpio Gpio instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void GPIO_HWA_ClearPinDirection(GPIO_Type *pGpio, uint8_t u8Pin)
{
    pGpio->PDDR &= ~((uint32_t)1 << u8Pin);
}

/**
 * @brief Clear pin input disable
 *
 * @param pGpio Gpio instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void GPIO_HWA_ClearPinInputDisable(GPIO_Type *pGpio, uint8_t u8Pin)
{
    pGpio->PIDR &= ~((uint32_t)1 << u8Pin);
}




#endif /* #ifndef _HWA_GPIO_H_ */
