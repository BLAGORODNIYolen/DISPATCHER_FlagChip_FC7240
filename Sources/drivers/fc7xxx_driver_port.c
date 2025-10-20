/**
 * @file fc7xxx_driver_port.c
 * @author Flagchip
 * @brief FC7xxx PORT driver type definition and API
 * @version 0.1.0
 * @date 2023-2-4
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
#include "fc7xxx_driver_port.h"
#include "interrupt_manager.h"

/** @brief PORTA interrupt entry */
void PORTA_IRQHandler(void);
/** @brief PORTB interrupt entry */
void PORTB_IRQHandler(void);
/** @brief PORTC interrupt entry */
void PORTC_IRQHandler(void);
/** @brief PORTD interrupt entry */
void PORTD_IRQHandler(void);
/** @brief PORTE interrupt entry */
void PORTE_IRQHandler(void);



/********* Local Variables ************/
/** @brief PORT instance list */
static PORT_Type *const s_pPortInstanceTable[PORT_INSTANCE_COUNT] = PORT_BASE_PTRS;
/** @brief PORT user defined interrupt function */
static PORT_PinInterruptCallBackType s_pPortPinNotifyTable[PORT_PIN_NUM_MAX] = {NULL};
/** @brief PORT interrupt mode table */
static PORT_IntConfigType s_aPortPinIrqTable[PORT_PIN_NUM_MAX] = {PORT_IRQ_DISABLE};
/** @brief port common interrupt handle function */
static void Port_CommonProcessInterrupt(const PORT_InstanceType ePort, const uint8_t u8Pin);


/***************PORT Global Functions*****************/
/**
 * @brief Initialize port
 *
 * @param ePort Port instance
 * @param pInitStruct Initialization structure of port
 * @return Port return type.
 */
PORT_StatusType PORT_InitPins(const PORT_InstanceType ePort, const PORT_InitType *const pInitStruct)
{
	PORT_StatusType eRet = PORT_STATUS_SUCCESS;
	PORT_Type *pPort;
	uint32_t u32PcrRegValue = 0U;
	uint32_t u32LowPcrRegValue = 0U;
	uint32_t u32HighPcrRegValue = 0U;

	if (((uint32_t)ePort >= PORT_INSTANCE_COUNT) || (NULL == pInitStruct))
	{
		eRet = PORT_STATUS_PARAM_INVALID;
	}
	else
	{
		pPort = s_pPortInstanceTable[(uint32_t)ePort];

		u32PcrRegValue |= PORT_PCR_MUX(pInitStruct->uPortPinMux.u32PortPinMode);

	    u32PcrRegValue |= PORT_PCR_IRQC(pInitStruct->eTriggrtMode);

		u32PcrRegValue |= PORT_PCR_PE(pInitStruct->bPullEn);
		u32PcrRegValue |= PORT_PCR_PS(pInitStruct->ePullSel);

		u32PcrRegValue |= PORT_PCR_DSE0(pInitStruct->bDrvStrength0En);
        u32PcrRegValue |= PORT_PCR_DSE1(pInitStruct->bDrvStrength1En);

		u32PcrRegValue |= PORT_PCR_PFE(pInitStruct->u8PassiveFilterEn);

		u32PcrRegValue |= PORT_PCR_ISF_MASK;

		u32LowPcrRegValue = u32PcrRegValue & PORT_PCR_LOW_16BITS_MASK;
		u32HighPcrRegValue = u32PcrRegValue & PORT_PCR_HIGH_16BITS_MASK;

	    PORT_HWA_WriteGPCLR(pPort,pInitStruct->u32PortPins,u32LowPcrRegValue);
	    PORT_HWA_WriteGPCHR(pPort,pInitStruct->u32PortPins,u32LowPcrRegValue);
	    PORT_HWA_WriteGICLR(pPort,pInitStruct->u32PortPins,u32HighPcrRegValue);
	    PORT_HWA_WriteGICHR(pPort,pInitStruct->u32PortPins,u32HighPcrRegValue);
	}
	return eRet;
}

/**
 * @brief De-initialize the Port instance
 *
 * @param ePort Port instance enumeration
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 * @return Port return type.
 */
PORT_StatusType PORT_Deinit(const PORT_InstanceType ePort, const uint32_t u32Pins)
{
    PORT_StatusType eRet = PORT_STATUS_SUCCESS;
    PORT_Type *pPort = s_pPortInstanceTable[ePort];
    uint8_t u8PinIndex = 0U;
    uint32_t u32TempPins = u32Pins;
    if ((uint32_t)ePort >= PORT_INSTANCE_COUNT)
    {
        eRet = PORT_STATUS_PARAM_INVALID;
    }
    else
    {
        while (u32TempPins != 0u)
        {
            if ((u32TempPins & ((uint32_t)1 << u8PinIndex)) != 0u)
            {
                PORT_HWA_ConfigPin(pPort, u8PinIndex, (uint32_t)0U);
                s_aPortPinIrqTable[PORT_PIN_NUM(ePort, u8PinIndex)] = PORT_IRQ_DISABLE;
                s_pPortPinNotifyTable[PORT_PIN_NUM(ePort, u8PinIndex)] = NULL;
            }
            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
        }
    }
    return eRet;
}

/**
 * @brief Enable interrupt function of port
 *
 * @param ePort Port instance enumeration
 * @param pIntStruct Interrupt structure of port.
 * @return Port return type.
 */
PORT_StatusType PORT_InitInterrupt(const PORT_InstanceType ePort, const PORT_InterruptType *const pIntStruct)
{
    PORT_StatusType eRet = PORT_STATUS_SUCCESS;
    uint8_t u8PinIndex = 0U;
    uint32_t u32TempPins = 0U;
    PORT_Type *pPort = s_pPortInstanceTable[ePort];
    if (((uint32_t)ePort >= PORT_INSTANCE_COUNT) || (NULL == pIntStruct))
    {
        eRet = PORT_STATUS_PARAM_INVALID;
    }
    else
    {
        u32TempPins = pIntStruct->u32PortPins;
        while (u32TempPins != 0u)
        {
            if ((u32TempPins & ((uint32_t)1 << u8PinIndex)) != 0u)
            {
                PORT_HWA_ClearPinInterruptFlag(pPort, u8PinIndex);
                PORT_HWA_SetPinInterruptMode(pPort, u8PinIndex, (PORT_IntConfigType)pIntStruct->ePortIsrMode);

                s_aPortPinIrqTable[PORT_PIN_NUM(ePort, u8PinIndex)] = pIntStruct->ePortIsrMode;
                if (NULL != pIntStruct->pIsrNotify)
                {
                    s_pPortPinNotifyTable[PORT_PIN_NUM(ePort, u8PinIndex)] = pIntStruct->pIsrNotify;
                }
            }

            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
        }
        /* IntMgr_EnableInterrupt((IRQn_Type)((uint32_t)PORTA_IRQn + (uint32_t)ePort)); */
    }
    return eRet;
}

/**
 * @brief Enable interrupt function of port
 *
 * @param ePort Port instance enumeration
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 * @return Port return type.
 */
PORT_StatusType PORT_EnableInterrupt(const PORT_InstanceType ePort, const uint32_t u32Pins)
{
    PORT_StatusType eRet = PORT_STATUS_SUCCESS;
    uint8_t u8PinIndex = 0U;
    uint32_t u32TempPins = u32Pins;
    PORT_Type *pPort = s_pPortInstanceTable[ePort];
    if ((uint32_t)ePort >= PORT_INSTANCE_COUNT)
    {
        eRet = PORT_STATUS_PARAM_INVALID;
    }
    else
    {
        while (u32TempPins != 0u)
        {
            if ((u32TempPins & ((uint32_t)1 << u8PinIndex)) != 0u)
            {
                PORT_HWA_ClearPinInterruptFlag(pPort, u8PinIndex);
                PORT_HWA_SetPinInterruptMode(pPort, u8PinIndex, (PORT_IntConfigType)s_aPortPinIrqTable[PORT_PIN_NUM(ePort,
                                             u8PinIndex)]);
            }
            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
        }
    }
    return eRet;
}

/**
 * @brief Disable interrupt function of port
 *
 * @param ePort Port instance enumeration
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 * @return Port return type.
 */
PORT_StatusType PORT_DisableInterrupt(const PORT_InstanceType ePort, const uint32_t u32Pins)
{
    PORT_StatusType eRet = PORT_STATUS_SUCCESS;
    uint8_t u8PinIndex = 0U;
    uint32_t u32TempPins = u32Pins;
    PORT_Type *pPort = s_pPortInstanceTable[ePort];
    if ((uint32_t)ePort >= PORT_INSTANCE_COUNT)
    {
        eRet = PORT_STATUS_PARAM_INVALID;
    }
    else
    {
        while (u32TempPins != 0u)
        {
            if ((u32TempPins & ((uint32_t)1 << u8PinIndex)) != 0u)
            {
                PORT_HWA_ClearPinInterruptFlag(pPort, u8PinIndex);
                PORT_HWA_ClearPinInterruptMode(pPort, u8PinIndex);
            }
            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
        }
    }
    return eRet;
}

PORT_StatusType PORT_SetPinsDmaReqMode(const PORT_InstanceType ePort, const uint32_t u32Pins, const PORT_DMAReqType eDMAReqMode)
{
	PORT_StatusType eRet = PORT_STATUS_SUCCESS;
    uint8_t u8PinIndex = 0U;
    uint32_t u32TempPins = u32Pins;
    PORT_Type *pPort = s_pPortInstanceTable[ePort];
    if ((uint32_t)ePort >= PORT_INSTANCE_COUNT)
    {
        eRet = PORT_STATUS_PARAM_INVALID;
    }
    else
    {
        while (u32TempPins != 0u)
        {
            if ((u32TempPins & ((uint32_t)1 << u8PinIndex)) != 0u)
            {
            	PORT_HWA_SetPinDMAReqMode(pPort, u8PinIndex, eDMAReqMode);
            }
            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
        }
    }
    return eRet;
}

/**
 * @brief Initialize digital filter for Port instance
 *
 * @param ePort Port instance enumeration
 * @param pDFStruct Digital filter initialization structure of port
 * @return Port return type.
 */
PORT_StatusType PORT_InitDigitalFilterPort(const PORT_InstanceType ePort, const PORT_DigitalFilterType *pDFStruct)
{
    PORT_StatusType eRet = PORT_STATUS_SUCCESS;
    PORT_Type *pPort = s_pPortInstanceTable[ePort];
    if ((NULL == pDFStruct) || ((uint32_t)ePort >= PORT_INSTANCE_COUNT))
    {
        eRet = PORT_STATUS_PARAM_INVALID;
    }
    else
    {
        if (pDFStruct->u32PortPinsEn != 0u)
        {
            if (PORT_FILTER_AON32K_CLK == pDFStruct->eClkSrc)
            {
                PORT_HWA_SetDigitalFilterClkSrc(pPort, pDFStruct->eClkSrc);
            }
            else
            {
                PORT_HWA_ClearDigitalFilterClkSrc(pPort);
            }
            PORT_HWA_ConfigDigitalFilterWidth(pPort, (uint32_t)pDFStruct->u8FilterLength);
            PORT_HWA_ConfigDigitalFilter(pPort, pDFStruct->u32PortPinsEn);
        }
    }
    return eRet;
}

/**
 * @brief De-initialize digital filter for Port instance
 *
 * @param ePort Port instance enumeration
 * @return Port return type.
 */
PORT_StatusType PORT_DeinitDigitalFilterPort(const PORT_InstanceType ePort)
{
    PORT_StatusType eRet = PORT_STATUS_SUCCESS;
    PORT_Type *pPort = s_pPortInstanceTable[ePort];
    if ((uint32_t)ePort >= PORT_INSTANCE_COUNT)
    {
        eRet = PORT_STATUS_PARAM_INVALID;
    }
    else
    {
        PORT_HWA_ClearDigitalFilterClkSrc(pPort);
        PORT_HWA_ClearDigitalFilterWidth(pPort);
        PORT_HWA_ClearDigitalFilterEnable(pPort);
    }
    return eRet;
}

/**
 * @brief Enable the digital filter function for the specific pin.
 *
 * @param ePort Port instance enumeration
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 * @return Port return type.
 */
PORT_StatusType PORT_EnableDigitalFilterPin(const PORT_InstanceType ePort, const uint32_t u32Pins)
{
    PORT_StatusType eRet = PORT_STATUS_SUCCESS;
    uint8_t u8PinIndex = 0U;
    uint32_t u32TempPins = u32Pins;
    PORT_Type *pPort;
    if ((uint32_t)ePort >= PORT_INSTANCE_COUNT)
    {
        eRet = PORT_STATUS_PARAM_INVALID;
    }
    else
    {
        pPort = s_pPortInstanceTable[ePort];
        while (u32TempPins != 0u)
        {
            if ((u32TempPins & ((uint32_t)1 << u8PinIndex)) != 0u)
            {
                PORT_HWA_SetDigitalFilterEnable(pPort, u8PinIndex);
            }
            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
        }
    }
    return eRet;
}

/**
 * @brief Disable the digital filter function for the specific pin.
 *
 * @param ePort Port instance enumeration
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 */
PORT_StatusType PORT_DisableDigitalFilterPin(const PORT_InstanceType ePort, const uint32_t u32Pins)
{
    PORT_StatusType eRet = PORT_STATUS_SUCCESS;
    uint8_t u8PinIndex = 0U;
    uint32_t u32TempPins = u32Pins;
    PORT_Type *pPort;
    if ((uint32_t)ePort >= PORT_INSTANCE_COUNT)
    {
        eRet = PORT_STATUS_PARAM_INVALID;
    }
    else
    {
        pPort = s_pPortInstanceTable[ePort];
        while (u32TempPins != 0u)
        {
            if ((u32TempPins & ((uint32_t)1 << u8PinIndex)) != 0u)
            {
                PORT_HWA_ClearDigitalFilterPin(pPort, u8PinIndex);
            }
            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
        }
    }
    return eRet;
}


/**
 * \brief port common interrupt handle function
 *
 * \param ePort port instance
 * \param u8Pin bit of u8Pin indicate pin number
 */
static void Port_CommonProcessInterrupt(const PORT_InstanceType ePort, const uint8_t u8Pin)
{
    if (NULL != s_pPortPinNotifyTable[PORT_PIN_NUM(ePort, u8Pin)])
    {
        s_pPortPinNotifyTable[PORT_PIN_NUM(ePort, u8Pin)]();
    }
}


/***************PORT IRQ Functions*****************/
/**
 * \brief PORTA interrupt entry
 *
 */
void PORTA_IRQHandler(void)
{
    uint8_t u8PinIndex;
    for (u8PinIndex = 0U; u8PinIndex < (uint32_t)32; u8PinIndex++)
    {
        if (PORT_HWA_ReadPinInterruptFlag(PORTA, u8PinIndex))
        {
            PORT_HWA_ClearPinInterruptFlag(PORTA, u8PinIndex);
            Port_CommonProcessInterrupt(PORT_A, u8PinIndex);
        }
    }
}

/**
 * \brief PORTB interrupt entry
 *
 */
void PORTB_IRQHandler(void)
{
    uint8_t u8PinIndex;
    for (u8PinIndex = 0U; u8PinIndex < (uint8_t)32; u8PinIndex++)
    {
        if (PORT_HWA_ReadPinInterruptFlag(PORTB, u8PinIndex))
        {
            PORT_HWA_ClearPinInterruptFlag(PORTB, u8PinIndex);
            Port_CommonProcessInterrupt(PORT_B, u8PinIndex);
        }
    }
}

/**
 * \brief PORTC interrupt entry
 *
 */
void PORTC_IRQHandler(void)
{
    uint8_t u8PinIndex;
    for (u8PinIndex = 0U; u8PinIndex < (uint8_t)32; u8PinIndex++)
    {
        if (PORT_HWA_ReadPinInterruptFlag(PORTC, u8PinIndex))
        {
            PORT_HWA_ClearPinInterruptFlag(PORTC, u8PinIndex);
            Port_CommonProcessInterrupt(PORT_C, u8PinIndex);
        }
    }
}

/**
 * \brief PORTD interrupt entry
 *
 */
void PORTD_IRQHandler(void)
{
    uint8_t u8PinIndex;
    for (u8PinIndex = 0U; u8PinIndex < (uint8_t)32; u8PinIndex++)
    {
        if (PORT_HWA_ReadPinInterruptFlag(PORTD, u8PinIndex))
        {
            PORT_HWA_ClearPinInterruptFlag(PORTD, u8PinIndex);
            Port_CommonProcessInterrupt(PORT_D, u8PinIndex);
        }
    }
}

/**
 * \brief PORTE interrupt entry
 *
 */
void PORTE_IRQHandler(void)
{
    uint8_t u8PinIndex;
    for (u8PinIndex = 0U; u8PinIndex < (uint8_t)32; u8PinIndex++)
    {
        if (PORT_HWA_ReadPinInterruptFlag(PORTE, u8PinIndex))
        {
            PORT_HWA_ClearPinInterruptFlag(PORTE, u8PinIndex);
            Port_CommonProcessInterrupt(PORT_E, u8PinIndex);
        }
    }
}

