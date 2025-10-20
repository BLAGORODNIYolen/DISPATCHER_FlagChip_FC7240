/**
 * @file interrupt_manager.h
 * @author Flagchip
 * @brief interrupt configuration
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
#if !defined(INTERRUPT_MANAGER_H)
#define INTERRUPT_MANAGER_H


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/


#include "device_header.h"


typedef enum
{
    /* Auxiliary constants */
    NotAvail_IRQn                      = -128,       /**< Not available device specific interrupt */

    /* Core interrupts */
    NonMaskableInt_IRQn                = -14,   /**< Non Maskable Interrupt */
    HardFault_IRQn                     = -13,   /**< Cortex-M4 SV Hard Fault Interrupt */
    MemoryManagement_IRQn              = -12,   /**< Cortex-M4 Memory Management Interrupt */
    BusFault_IRQn                      = -11,   /**< Cortex-M4 Bus Fault Interrupt */
    UsageFault_IRQn                    = -10,   /**< Cortex-M4 Usage Fault Interrupt */
    SVCall_IRQn                        = -5,    /**< Cortex-M4 SV Call Interrupt */
    DebugMonitor_IRQn                  = -4,    /**< Cortex-M4 Debug Monitor Interrupt */
    PendSV_IRQn                        = -2,    /**< Cortex-M4 Pend SV Interrupt */
    SysTick_IRQn                       = -1,    /**< Cortex-M4 System Tick Interrupt */

    /* FC100 Device specific interrupts */
    DMA0_IRQn                          = 0U,     /**< DMA channel 0 transfer complete */
    DMA1_IRQn                          = 1U,     /**< DMA channel 1 transfer complete */
    DMA2_IRQn                          = 2U,     /**< DMA channel 2 transfer complete */
    DMA3_IRQn                          = 3U,     /**< DMA channel 3 transfer complete */
    DMA4_IRQn                          = 4U,     /**< DMA channel 4 transfer complete */
    DMA5_IRQn                          = 5U,     /**< DMA channel 5 transfer complete */
    DMA6_IRQn                          = 6U,     /**< DMA channel 6 transfer complete */
    DMA7_IRQn                          = 7U,     /**< DMA channel 7 transfer complete */
    DMA8_IRQn                          = 8U,     /**< DMA channel 8 transfer complete */
    DMA9_IRQn                          = 9U,     /**< DMA channel 9 transfer complete */
    DMA10_IRQn                         = 10U,    /**< DMA channel 10 transfer complete */
    DMA11_IRQn                         = 11U,    /**< DMA channel 11 transfer complete */
    DMA12_IRQn                         = 12U,    /**< DMA channel 12 transfer complete */
    DMA13_IRQn                         = 13U,    /**< DMA channel 13 transfer complete */
    DMA14_IRQn                         = 14U,    /**< DMA channel 14 transfer complete */
    DMA15_IRQn                         = 15U,    /**< DMA channel 15 transfer complete */
	DMA_Error_IRQn                     = 16U,    /**< DMA error interrupt channels 0-63 */
	CPM_IRQn                           = 17U,    /**< FPU etc. interrupt */
	FC_IRQn                            = 18U,    /**< Flash Controller Command complete, time out etc. interrupt  */
	LVD_LVW_IRQn                       = 19U,    /**< HVD/LVD etc. interrupt */
	TMU_IRQn                           = 20U,    /**< Temperature Monitor Unit interrupt */
	WDOG0_IRQn                         = 21U,    /**< Interrupt request out before wdg0 reset out */
	WDOG1_IRQn                         = 22U,    /**< Interrupt request out before wdg1 reset out */
	FCSMU0_IRQn                        = 23U,    /**< Fault Control and Safety Manage Unit */
	STCU0_IRQn                         = 24U,    /**< Safety Control Unit interrupt */
	ERM_fault_IRQn                     = 25U,    /**< ERM single- or double-bit error interrupt */
	MAM0_IRQn                          = 26U,    /**< Matrix Access Monitor interrupt */
	RGM_Pre_IRQn                       = 27U,    /**< RGM pre-reset Interrupt */
	INTM0_IRQn                         = 28U,    /**< INTM0 timeout interrupt */
	ISM0_IRQn                          = 29U,    /**< ISM0 interrupt */
	MB_IRQn                            = 30U,    /**< Mail Box interrupt */
	SCG_IRQn                           = 31U,    /**< SCG bus interrupt request  */
	CMU0_IRQn                          = 32U,    /**< CMU0 interrupt */
	CMU1_IRQn                          = 33U,    /**< CMU1 interrupt */
	CMU2_IRQn                          = 34U,    /**< CMU2 interrupt */
	CMU3_IRQn                          = 35U,    /**< CMU3 interrupt */
	CMU4_IRQn                          = 36U,    /**< CMU4 interrupt */
	TSTMP0_IRQn                        = 37U,    /**< TimerStamp0 interrupt */
	TSTMP1_IRQn                        = 38U,    /**< TimerStamp1 interrupt */
	CORDIC_IRQn                        = 39U,    /**< CORDIC Accelerator interrupt */
	HSM0_ERR_IRQn                          = 40U,    /**< HSM error interrupt */
	FCPIT0_IRQn                        = 41U,    /**< FCPIT interrupt */
	RTC_IRQn                           = 42U,    /**< RTC alarm or seconds interrupt */
	AONTIMER_IRQn                      = 43U,    /**< AONTIMER interrupt request */
	SWI_IRQn                           = 44U,    /**< Software interrupt  */
	FREQM_IRQn                         = 45U,    /**< FREQM interrupt */
	ADC0_IRQn                          = 46U,    /**< ADC0 interrupt request */
	ADC1_IRQn                          = 47U,    /**< ADC1 interrupt request */
	PTIMER0_IRQn                       = 48U,    /**< PTIMER0 interrupt */
	PTIMER1_IRQn                       = 49U,    /**< PTIMER1 interrupt */
	FlexCAN0_IRQn                      = 50U,    /**< FLEXCAN0 interrupt */
	FlexCAN1_IRQn                      = 51U,    /**< FLEXCAN1 interrupt */
	FlexCAN2_IRQn                      = 52U,    /**< FLEXCAN2 interrupt */
	FlexCAN3_IRQn                      = 53U,    /**< FLEXCAN3 interrupt */
	FCIIC0_IRQn                        = 54U,    /**< FCIIC0 Interrupt */
	FCIIC1_IRQn                        = 55U,    /**< FCIIC1 Interrupt */
	FCSPI0_IRQn                        = 56U,    /**< FCSPI0 Interrupt */
	FCSPI1_IRQn                        = 57U,    /**< FCSPI1 Interrupt */
	FCSPI2_IRQn                        = 58U,    /**< FCSPI2 Interrupt */
	FCSPI3_IRQn                        = 59U,    /**< FCSPI3 Interrupt */
	FCSPI4_IRQn                        = 60U,    /**< FCSPI4 Interrupt */
	FCSPI5_IRQn                        = 61U,    /**< FCSPI5 Interrupt */
	FCUART0_IRQn                       = 62U,    /**< FCUART0 Interrupt */
	FCUART1_IRQn                       = 63U,    /**< FCUART1 Interrupt */
	FCUART2_IRQn                       = 64U,    /**< FCUART2 Interrupt */
	FCUART3_IRQn                       = 65U,    /**< FCUART3 Interrupt */
	FCUART4_IRQn                       = 66U,    /**< FCUART4 Interrupt */
	FCUART5_IRQn                       = 67U,    /**< FCUART5 Interrupt */
	FCUART6_IRQn                       = 68U,    /**< FCUART6 Interrupt */
	FCUART7_IRQn                       = 69U,    /**< FCUART7 Interrupt */
	FTU0_IRQn                          = 70U,    /**< FTU0 all source interrupt */
	FTU1_IRQn                          = 71U,    /**< FTU1 all source interrupt */
	FTU2_IRQn                          = 72U,    /**< FTU2 all source interrupt */
	FTU3_IRQn                          = 73U,    /**< FTU3 all source interrupt */
	FTU4_IRQn                          = 74U,    /**< FTU4 all source interrupt */
	FTU5_IRQn                          = 75U,    /**< FTU5 all source interrupt */
	FTU6_IRQn                          = 76U,    /**< FTU6 all source interrupt */
	FTU7_IRQn                          = 77U,    /**< FTU7 all source interrupt */
	CMP0_IRQn                          = 78U,    /**< CMP0 all source interrupt */
	CMP1_IRQn                          = 79U,    /**< CMP1 all source interrupt */
    PORTA_IRQn                         = 80U,    /**< Port A pin detect interrupt */
    PORTB_IRQn                         = 81U,    /**< Port B pin detect interrupt */
    PORTC_IRQn                         = 82U,    /**< Port C pin detect interrupt */
    PORTD_IRQn                         = 83U,    /**< Port D pin detect interrupt */
	PORTE_IRQn                         = 84U,    /**< Port E pin detect interrupt */
	MSC0_IRQn                          = 85U,    /**< MSC Interrupt */
	SENT0_IRQn                         = 86U,    /**< SENT all interrupt (fast or slow) */
    TPU0_CH0_7_IRQn                    = 87U,    /**< TPU0 CH0-7 interrupt */
	TPU0_CH8_15_IRQn                   = 88U,    /**< TPU0 CH8-15 interrupt */
	TPU0_CH16_23_IRQn                  = 89U,    /**< TPU0 CH16-23 interrupt */
	TPU0_CH24_31_IRQn                  = 90U,    /**< TPU0 CH24-31 interrupt */
    HSM0_IRQn                          = 91U,    /**< HSM crypto interrupt */
    IRQn_MAX                           = 92U
} IRQn_Type;





/**
 * \brief enable interrupt via interrupt number
 *
 * \param eIrqNumber is interrupt number
 */
void IntMgr_EnableInterrupt(IRQn_Type eIrqNumber);

/**
 * \brief disable interrupt via interrupt number
 *
 * \param eIrqNumber is interrupt number
 */
void IntMgr_DisableInterrupt(IRQn_Type eIrqNumber);

/**
 * \brief enable global interrupt
 *
 */
void IntMgr_EnableGlobalInterrupt(void);

/**
 * \brief disable global interrupt
 *
 */
void IntMgr_DisableGlobalInterrupt(void);

/**
 * \brief Set Priority group
 *
 * \param u32PriorityGroup is the group bits
 */
void IntMgr_SetGroupPriority(uint32_t u32PriorityGroup);

/**
 * \brief set the interrupt service priority
 *
 * \param eIrqNumber is interrupt number
 * \param u8Priority is priority number
 */
void IntMgr_SetPriority(IRQn_Type eIrqNumber, uint8_t u8Priority);

/**
 * \brief get the interrupt service priority
 *
 * \param eIrqNumber is interrupt number
 * \return the priority
 */
uint8_t IntMgr_GetPriority(IRQn_Type eIrqNumber);



#if defined(__cplusplus)
}
#endif /* __cplusplus*/



#endif /* INTERRUPT_MANAGER_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
