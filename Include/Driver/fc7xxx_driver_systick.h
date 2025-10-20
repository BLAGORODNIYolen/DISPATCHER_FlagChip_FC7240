#ifndef _DRIVER_CORE_SYSTICK_H_
#define _DRIVER_CORE_SYSTICK_H_

#include "device_header.h"


/**
 * \brief Config system tick
 *
 * \param u32ReloadVal reload value, val is decrease from reload value
 * \return 0 is ok, and others are not ok
 */
uint8_t Core_SysTick_Config(uint32_t u32ReloadVal);

void Core_SysTick_DeConfig(void);

void Core_SysTick_SetValue(uint32_t u32Value);

void Core_SysTick_ClearValue(void);

uint32_t Core_SysTick_GetValue(void);

void Core_SysTick_Enable(void);

void Core_SysTick_Disable(void);


#endif /* end of _DRIVER_CORE0_SYSTICK_H_ */
