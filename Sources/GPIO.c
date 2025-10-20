#include <Gpio.h>

void Bsp_Port_Init(void)
{
    PORT_InitType tInitStruct     = {0};
    GPIO_InitType tGpioInitStruct = {0};

    //UART2 settings
    tInitStruct.u32PortPins = PORT_PIN_6;
    tInitStruct.uPortPinMux.u32PortPinMode = PORTD_6_FCUART2_RX;
    PORT_InitPins(PORT_D, &tInitStruct);
    tGpioInitStruct.u32GpioPins   = GPIO_PIN_6;
    tGpioInitStruct.ePinDirection = GPIO_IN;
    GPIO_InitPins(GPIO_D, &tGpioInitStruct);

    tInitStruct.u32PortPins = PORT_PIN_7;
    tInitStruct.uPortPinMux.u32PortPinMode = PORTD_7_FCUART2_TX;
    PORT_InitPins(PORT_D, &tInitStruct);
    tGpioInitStruct.u32GpioPins   = GPIO_PIN_7;
    tGpioInitStruct.ePinDirection = GPIO_OUT;
    tGpioInitStruct.ePinLevel     = GPIO_HIGH;
    GPIO_InitPins(GPIO_D, &tGpioInitStruct);
    //END OF UART2 settings

    //	CAN0 settings
    /* PortC 30: MUX = GPIO output  ???????????????   */
    tInitStruct.u32PortPins = 1U << 30;
    tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
    PORT_InitPins(PORT_C, &tInitStruct);
    tGpioInitStruct.u32GpioPins = 1U << 30;
    tGpioInitStruct.ePinDirection = GPIO_OUT;
    tGpioInitStruct.ePinLevel = GPIO_LOW;
    GPIO_InitPins(GPIO_C, &tGpioInitStruct);
    /*CAN0_RX*/
    tInitStruct.u32PortPins = (1U << 2);
    tInitStruct.uPortPinMux.u32PortPinMode = PORTC_2_FLEXCAN0_RX;
    tInitStruct.bPullEn = FALSE;
    tInitStruct.ePullSel = PORT_PULL_UP;
    PORT_InitPins(PORT_C, &tInitStruct);
    tGpioInitStruct.u32GpioPins = 1U << 2;
    tGpioInitStruct.ePinDirection = GPIO_IN;
    GPIO_InitPins(PORT_C, &tGpioInitStruct);
    /*CAN0_TX*/
    tInitStruct.u32PortPins = (1U << 3);
    tInitStruct.uPortPinMux.u32PortPinMode = PORTC_3_FLEXCAN0_TX;
    PORT_InitPins(PORT_C, &tInitStruct);
    tGpioInitStruct.u32GpioPins = 1U << 3;
    tGpioInitStruct.ePinDirection = GPIO_OUT;
    tGpioInitStruct.ePinLevel = GPIO_HIGH;
    GPIO_InitPins(GPIO_C, &tGpioInitStruct);
    //	END OF CAN0 settings


    //	SPI1 settings
    PORT_InitType           tPortCfg         = {0};
    tPortCfg.u32PortPins             = PORT_PIN_6;
    tPortCfg.uPortPinMux.u32PortPinMode = PORTA_6_FCSPI1_PCS1;
    PORT_InitPins(PORT_A, &tPortCfg);
    /*SOUT */
    tPortCfg.u32PortPins             = PORT_PIN_9;
    tPortCfg.uPortPinMux.u32PortPinMode = PORTC_9_FCSPI1_SOUT;
    PORT_InitPins(PORT_C, &tPortCfg);
    /*SCK*/
    tPortCfg.u32PortPins               = PORT_PIN_7;
    tPortCfg.uPortPinMux.u32PortPinMode  = PORTA_7_FCSPI1_SCK;
    PORT_InitPins(PORT_A, &tPortCfg);
    /*SIN*/
    tPortCfg.u32PortPins              = PORT_PIN_8;
    tPortCfg.uPortPinMux.u32PortPinMode  = PORTC_8_FCSPI1_SIN;
    PORT_InitPins(PORT_C, &tPortCfg);
    //	END of SPI1 settings

    //LED SETTINGs
    /*LED1*/
    tInitStruct.u32PortPins = PORT_PIN_8;
	tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
	PORT_InitPins(PORT_A, &tInitStruct);
    tGpioInitStruct.u32GpioPins = GPIO_PIN_8;
    tGpioInitStruct.ePinDirection = GPIO_OUT;
   	tGpioInitStruct.ePinLevel = GPIO_LOW;
   	GPIO_InitPins(GPIO_A, &tGpioInitStruct);
	/*LED2*/
	tInitStruct.u32PortPins = PORT_PIN_11;
	PORT_InitPins(PORT_A, &tInitStruct);
    tGpioInitStruct.u32GpioPins = GPIO_PIN_11;
	GPIO_InitPins(GPIO_A, &tGpioInitStruct);
	/*LED3*/
	tInitStruct.u32PortPins = PORT_PIN_15;
	PORT_InitPins(PORT_A, &tInitStruct);
    tGpioInitStruct.u32GpioPins = GPIO_PIN_15;
	GPIO_InitPins(GPIO_A, &tGpioInitStruct);
    //END OF LED SETTINGs
}

void Bsp_Gpio_Toggle(void)
{
    /* led toggle */
    GPIO_Toggle(GPIO_A, PORT_PIN_8);
    GPIO_Toggle(GPIO_A, PORT_PIN_11);
    GPIO_Toggle(GPIO_A, PORT_PIN_15);
}
