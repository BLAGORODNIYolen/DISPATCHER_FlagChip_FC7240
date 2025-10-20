/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Application includes. */
#include "GPIO.h"
#include "Clock.h"
#include "Fpu.h"
#include "rtos.h"

#include "UART.h"
#include "FCSPI.h"
#include "CAN.h"

uint32_t SystemCoreClock;

/*-----------------------------------------------------------*/

/*
 * Set up the hardware ready to run this demo.
 */
static void prvSetupHardware(void);

/*!
 \brief The main function for the project.
 \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
 */
int main(void)
{
    /* Configure the clock and peripherals. */
    prvSetupHardware();
    FCUART_Printf(2, "System is ready!\n");
    //FCUART_Printf(2, "nvic prio bits - %d\n", __NVIC_PRIO_BITS);
    rtos_start();

    /* If all is well, the scheduler will now be running, and the following line
    will never be reached.  If the following line does execute, then there was
    insufficient FreeRTOS heap memory available for the idle and/or timer tasks
    to be created.  See the memory management section on the FreeRTOS web site
    for more details. */
    for (;;);

    return 0;
}


static void prvSetupHardware(void)
{
    Bsp_CLOCK_Init();
    Bsp_Port_Init();
    BSP_FCUART_Init();
    Bsp_FCSpi_Init();
    BSP_CAN_Init();

    SystemCoreClock = SCG_GetScgClockFreq(SCG_CORE_CLK);
}

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     for the Flagchip FC series of microcontrollers.
 **
 ** ###################################################################
 */

