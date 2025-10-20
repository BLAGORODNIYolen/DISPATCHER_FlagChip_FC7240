#include "fc7xxx_driver_systick.h"



/**
 * \brief Config system tick
 *
 * \param u32ReloadVal reload value, val is decrease from reload value
 * \return 0 is ok, and others are not ok
 */
uint8_t Core_SysTick_Config(uint32_t u32ReloadVal)
{
    uint8_t u8Retval;

    if (u32ReloadVal > SysTick_LOAD_RELOAD_Msk)
    {
        u8Retval = 1U;
    }
    else
    {
        SysTick->LOAD  = u32ReloadVal;                /* set reload register */
        SysTick->VAL   = 0UL;                         /* Load the SysTick Counter Value */
        SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;  /* Processor clock */
        u8Retval = 0U;
    }

    return u8Retval;
}

void Core_SysTick_DeConfig(void)
{
    SysTick->CTRL = 0U;
    SysTick->LOAD = 0U;
    SysTick->VAL = 0U;
}

void Core_SysTick_ClearValue(void)
{
    SysTick->VAL = 0U;
}

void Core_SysTick_SetValue(uint32_t u32Value)
{
    SysTick->VAL = u32Value;
}

uint32_t Core_SysTick_GetValue(void)
{
    return SysTick->VAL;
}

void Core_SysTick_Enable(void)
{
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
}

void Core_SysTick_Disable(void)
{
    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
}
