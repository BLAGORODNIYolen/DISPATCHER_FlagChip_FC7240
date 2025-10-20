/**
 * @file interrupt_manager.c
 * @author Flagchip
 * @brief interrupt configuration
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
#include "interrupt_manager.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


#define FC7300_PERI_VECTOR_START         16U

#define FC7300_NVIC_PRIO_BITS            3U


#define __NVIC_PRIO_BITS          2U



/*******************************************************************************
 * Code
 ******************************************************************************/

#if 0
/**
 * \brief Initial the interrupt table and data and bss
 *
 */
void IntMgr_Init(void)
{
#if defined ( __GNUC__ )  
    extern uint32 __isr0_vector[1];
    SCB->VTOR = (uint32_t)__isr0_vector;
#elif defined (__ICCARM__)
	extern uint32 __vector_table[1];
	SCB->VTOR = (uint32_t)__vector_table;
#endif
}
#endif


/**
 * \brief enable interrupt via interrupt number
 *
 * \param eIrqNumber is interrupt number
 */
void IntMgr_EnableInterrupt(IRQn_Type eIrqNumber)
{
    if ((int32_t)(eIrqNumber) >= 0)
    {
        NVIC->ISER[(((uint32_t)eIrqNumber) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)eIrqNumber) & 0x1FUL));
    }
}


/**
 * \brief disable interrupt via interrupt number
 *
 * \param eIrqNumber is interrupt number
 */
void IntMgr_DisableInterrupt(IRQn_Type eIrqNumber)
{
    if ((int32_t)(eIrqNumber) >= 0)
    {
        NVIC->ICER[(((uint32_t)eIrqNumber) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)eIrqNumber) & 0x1FUL));
        __DSB();
        __ISB();
    }

}

/**
 * \brief enable global interrupt
 *
 */
void IntMgr_EnableGlobalInterrupt(void)
{
    /* Enable the global interrupt*/
    __enable_irq();

}

/**
 * \brief disable global interrupt
 *
 */
void IntMgr_DisableGlobalInterrupt(void)
{
    /* Disable the global interrupt */
    __disable_irq();

}

/**
 * \brief Set Priority group
 *
 * \param u32PriorityGroup is the group bits
 */
void IntMgr_SetGroupPriority(uint32_t u32PriorityGroup)
{
    uint32_t reg_value;
    uint32_t PriorityGroupTmp = (u32PriorityGroup & (uint32_t)0x07UL);             /* only values 0..7 are used          */

    reg_value  =  SCB->AIRCR;                                                   /* read old register configuration    */
    reg_value &= ~((uint32_t)(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk)); /* clear bits to change               */
    reg_value  = (reg_value                                   |
                  ((uint32_t)0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
                  (PriorityGroupTmp << SCB_AIRCR_PRIGROUP_Pos));                /* Insert write key and priority group */
    SCB->AIRCR =  reg_value;
}

/**
 * \brief set the interrupt service Priority
 *
 * \param eIrqNumber is interrupt number
 * \param u8Priority is u8Priority number
 */
void IntMgr_SetPriority(IRQn_Type eIrqNumber, uint8_t u8Priority)
{

    if ((int32_t)(eIrqNumber) >= 0)
    {
        NVIC->IP[((uint32_t)eIrqNumber)]                = (uint8_t)(((uint32_t)u8Priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFU);
    }
    else
    {
        SCB->SHPR[(((uint32_t)eIrqNumber) & 0xFUL) - 4UL] = (uint8_t)(((uint32_t)u8Priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFU);
    }
}


/**
 * \brief get the interrupt service Priority
 *
 * \param eIrqNumber is interrupt number
 * \return the Priority
 */
uint8_t IntMgr_GetPriority(IRQn_Type eIrqNumber)
{
    if ((int32_t)(eIrqNumber) >= 0)
    {
        return (((uint32_t)NVIC->IP[((uint32_t)eIrqNumber)]                >> (8U - __NVIC_PRIO_BITS)));
    }
    else
    {
        return (((uint32_t)SCB->SHPR[(((uint32_t)eIrqNumber) & 0xFUL) - 4UL] >> (8U - __NVIC_PRIO_BITS)));
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
