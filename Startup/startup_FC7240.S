/* ================================================================================================== */
/*    BRIEF             : Startup - Startup file for FC7240                                           */
/*    PERIPHERAL        : N/A                                                                         */
/*    PLATFORM          : Flagchip FC7240                                                             */
/*    SOFTWARE VERSION  : 0.1.0                                                                       */
/*    VENDOR            : Flagchip                                                                    */
/*    Copyright      2024 Flagchip Semiconductors Co., Ltd.                                           */
/*    All Rights Reserved.                                                                            */
/* ================================================================================================== */
/* ================================================================================================== */
/*    Revision History                                                                                */
/*    Version     Date          Initials      CR#          Descriptions                               */
/*    ---------   ----------    ------------- ----------   ---------------                            */
/*    0.1.0       2024-01-12    qxw0030       N/A          Initial version                            */
/* ================================================================================================== */

    .syntax unified
    .arch armv7-m

    .extern __StackTop
    .extern __StackLimit

/* ================================================================================================== */
/*                                        Set vector table                                            */
/* ================================================================================================== */
    .section .isr_vector
    .align 2
    .globl __isr_vector

    /* vector table */
__isr_vector:
    .long   __StackTop                                      /* Top of Stack */
    .long   Reset_Handler                                   /* Reset Handler */
    .long   NMI_Handler                                     /* NMI Handler */
    .long   HardFault_Handler                               /* Hard Fault Handler */
    .long   MemManage_Handler                               /* MPU Fault Handler */
    .long   BusFault_Handler                                /* Bus Fault Handler */
    .long   UsageFault_Handler                              /* Usage Fault Handler */
    .long   0                                               /* Reserved */
    .long   0                                               /* Reserved */
    .long   0                                               /* Reserved */
    .long   0                                               /* Reserved */
    .long   SVC_Handler                                     /* SVCall Handler */
    .long   DebugMon_Handler                                /* Debug Monitor Handler */
    .long   0                                               /* Reserved */
    .long   PendSV_Handler                                  /* PendSV Handler */
    .long   SysTick_Handler                                 /* SysTick Handler */

                                                            /* External Interrupts*/
    .long   DMA0_IRQHandler                                 /*  DMA channel 0 transfer complete */
    .long   DMA1_IRQHandler                                  /*  DMA channel 1 transfer complete */
    .long   DMA2_IRQHandler                                   /*  DMA channel 2 transfer complete */
    .long   DMA3_IRQHandler                                   /*  DMA channel 3 transfer complete */
    .long   DMA4_IRQHandler                                    /*  DMA channel 4 transfer complete */
    .long   DMA5_IRQHandler                                   /*  DMA channel 5 transfer complete */
    .long   DMA6_IRQHandler                                   /*  DMA channel 6 transfer complete */
    .long   DMA7_IRQHandler                                    /*  DMA channel 7 transfer complete */
    .long   DMA8_IRQHandler                                   /*  DMA channel 8 transfer complete */
    .long   DMA9_IRQHandler                                 /*  DMA channel 9 transfer complete */
    .long   DMA10_IRQHandler                                  /*  DMA channel 10 transfer complete */
    .long   DMA11_IRQHandler                                   /*  DMA channel 11 transfer complete */
    .long   DMA12_IRQHandler                                  /*  DMA channel 12 transfer complete */
    .long   DMA13_IRQHandler                                  /*  DMA channel 13 transfer complete */
    .long   DMA14_IRQHandler                                 /*  DMA channel 14 transfer complete */
    .long   DMA15_IRQHandler                                   /*  DMA channel 15 transfer complete */
    .long   DMA_Error_IRQHandler                            /*  DMA error interrupt channels 0-31 */
    .long   CPM_IRQHandler                                  /*  FPU etc. interrupt */
    .long   FC_IRQHandler                                   /*  FC Command complete */
    .long   PMC_IRQHandler                                    /*  HVD/LVD etc. interrupt */
    .long   TMU_IRQHandler                                  /*  Temperature Monitor Unit interrupt */
    .long   WDOG0_IRQHandler                                /*  interrupt request out before wdg reset out */
    .long   WDOG1_IRQHandler                                /*  interrupt request out before wdg reset out */
    .long   FCSMU0_IRQHandler                               /*  Fault Control and Safety Manage Unit */
    .long   STCU0_IRQHandler                                /*  Safety Control Unit interrupt */
    .long   ERM_fault_IRQHandler                            /*  ERM single/double bit error correction */
    .long   MAM0_IRQHandler                                 /*  Matrix Access Monitor interrupt */
    .long   RGM_Pre_IRQHandler                                 /*  RGM pre-reset Interrupt */
    .long   INTM0_IRQHandler                                /*  INTM alarm interrupt */
    .long   ISM0_IRQHandler                                 /*  ISM0 interrupt */
    .long   MB_IRQHandler                                   /*  Mail Box interrupt */
    .long   SCG_IRQHandler                                  /*  SCG bus interrupt request */
    .long   CMU0_IRQHandler                                 /*  CMU0 interrupt */
    .long   CMU1_IRQHandler                                 /*  CMU1 interrupt */
    .long   CMU2_IRQHandler                                 /*  CMU2 interrupt */
    .long   CMU3_IRQHandler                                 /*  CMU3 interrupt */
    .long   CMU4_IRQHandler                                 /*  CMU4 interrupt */
    .long   TSTMP0_IRQHandler                               /*  TimerStamp0 interrupt */
    .long   TSTMP1_IRQHandler                               /*  TimerStamp1 interrupt */
    .long   CORDIC_IRQHandler                               /*  CORDIC Accelerator interrupt */
    .long   HSM0_IRQHandler                                 /*  HSM error interrupt */
    .long   FCPIT0_IRQHandler                               /*  FCPIT0 interrupt */
    .long   RTC_IRQHandler                                  /*  RTC alarm or seconds interrupt  */
    .long   AONTIMER_IRQHandler                             /*  AONTIMER interrupt request */
    .long   SWI_IRQHandler                                    /*  Software interrupt */
    .long   FREQM_IRQHandler                                /*  FREQM interrupt */
    .long   ADC0_IRQHandler                                 /*  ADC0 interrupt request. */
    .long   ADC1_IRQHandler                                 /*  ADC1 interrupt request. */
    .long   PTIMER0_IRQHandler                              /*  PTIMER0 interrupt */
    .long   PTIMER1_IRQHandler                              /*  PTIMER1 interrupt */
    .long   CAN0_IRQHandler                                 /*  CAN0 Interrupt */
    .long   CAN1_IRQHandler                                 /*  CAN1 Interrupt */
    .long   CAN2_IRQHandler                                 /*  CAN2 Interrupt */
    .long   CAN3_IRQHandler                                 /*  CAN3 Interrupt */
    .long   FCIIC0_IRQHandler                               /*  FCIIC0 Interrupt */
    .long   FCIIC1_IRQHandler                               /*  FCIIC1 Interrupt */
    .long   FCSPI0_IRQHandler                               /*  FCSPI0 Interrupt */
    .long   FCSPI1_IRQHandler                               /*  FCSPI1 Interrupt */
    .long   FCSPI2_IRQHandler                               /*  FCSPI2 Interrupt */
    .long   FCSPI3_IRQHandler                               /*  FCSPI3 Interrupt */
    .long   FCSPI4_IRQHandler                               /*  FCSPI4 Interrupt */
    .long   FCSPI5_IRQHandler                               /*  FCSPI5 Interrupt */
    .long   FCUART0_RxTx_IRQHandler                         /*  FCUART0 Transmit / Receive Interrupt */
    .long   FCUART1_RxTx_IRQHandler                         /*  FCUART1 Transmit / Receive  Interrupt */
    .long   FCUART2_RxTx_IRQHandler                         /*  FCUART2 Transmit / Receive  Interrupt */
    .long   FCUART3_RxTx_IRQHandler                         /*  FCUART3 Transmit / Receive Interrupt */
    .long   FCUART4_RxTx_IRQHandler                         /*  FCUART4 Transmit / Receive  Interrupt */
    .long   FCUART5_RxTx_IRQHandler                         /*  FCUART5 Transmit / Receive  Interrupt */
    .long   FCUART6_RxTx_IRQHandler                         /*  FCUART6 Transmit / Receive Interrupt */
    .long   FCUART7_RxTx_IRQHandler                         /*  FCUART7 Transmit / Receive  Interrupt */
    .long   FTU0_IRQHandler                                 /*  FTU0 all source interrupt */
    .long   FTU1_IRQHandler                                 /*  FTU1 all source interrupt */
    .long   FTU2_IRQHandler                                 /*  FTU2 all source interrupt */
    .long   FTU3_IRQHandler                                 /*  FTU3 all source interrupt */
    .long   FTU4_IRQHandler                                 /*  FTU4 all source interrupt */
    .long   FTU5_IRQHandler                                 /*  FTU5 all source interrupt */
    .long   FTU6_IRQHandler                                 /*  FTU6 all source interrupt */
    .long   FTU7_IRQHandler                                 /*  FTU7 all source interrupt */
    .long   CMP0_IRQHandler                                 /*  CMP0 interrupt request  */
    .long   CMP1_IRQHandler                                 /*  CMP1 interrupt request  */
    .long   PORTA_IRQHandler                                /*  Port A pin detect interrupt */
    .long   PORTB_IRQHandler                                /*  Port B pin detect interrupt */
    .long   PORTC_IRQHandler                                /*  Port C pin detect interrupt */
    .long   PORTD_IRQHandler                                /*  Port D pin detect interrupt */
    .long   PORTE_IRQHandler                                /*  Port E pin detect interrupt */
    .long   MSC0_IRQHandler                                 /*  MSC interrupt */
    .long   SENT0_IRQHandler                                /*  SENT all interrupt (fast or slow) */
    .long   TPU0_CH0_7_IRQHandler                           /*  TPU0 CH0-7 interrupt */
    .long   TPU0_CH8_15_IRQHandler                          /*  TPU0 CH8-15 interrupt */
    .long   TPU0_CH16_23_IRQHandler                         /*  TPU0 CH16-23 interrupt */
    .long   TPU0_CH24_31_IRQHandler                         /*  TPU0 CH24-31 interrupt */
    .long   HSM0_CRYPTO_IRQHandler                             /*  HSM crypto interrupt */
    .long   DefaultISR                                      /* 108 */
    .long   DefaultISR                                      /* 109 */
    .long   DefaultISR                                      /* 110 */
    .long   DefaultISR                                      /* 111 */
    .long   DefaultISR                                      /* 112 */
    .long   DefaultISR                                      /* 113 */
    .long   DefaultISR                                      /* 114 */
    .long   DefaultISR                                      /* 115 */
    .long   DefaultISR                                      /* 116 */
    .long   DefaultISR                                      /* 117 */
    .long   DefaultISR                                      /* 118 */
    .long   DefaultISR                                      /* 119 */
    .long   DefaultISR                                      /* 120 */
    .long   DefaultISR                                      /* 121 */
    .long   DefaultISR                                      /* 122 */
    .long   DefaultISR                                      /* 123 */
    .long   DefaultISR                                      /* 124 */
    .long   DefaultISR                                      /* 125 */
    .long   DefaultISR                                      /* 126 */
    .long   DefaultISR                                      /* 127 */
    .long   DefaultISR                                      /* 128 */
    .long   DefaultISR                                      /* 129 */
    .long   DefaultISR                                      /* 130 */
    .long   DefaultISR                                      /* 131 */
    .long   DefaultISR                                      /* 132 */
    .long   DefaultISR                                      /* 133 */
    .long   DefaultISR                                      /* 134 */
    .long   DefaultISR                                      /* 135 */
    .long   DefaultISR                                      /* 136 */
    .long   DefaultISR                                      /* 137 */
    .long   DefaultISR                                      /* 138 */
    .long   DefaultISR                                      /* 139 */
    .long   DefaultISR                                      /* 140 */
    .long   DefaultISR                                      /* 141 */
    .long   DefaultISR                                      /* 142 */
    .long   DefaultISR                                      /* 143 */
    .long   DefaultISR                                      /* 144 */
    .long   DefaultISR                                      /* 145 */
    .long   DefaultISR                                      /* 146 */
    .long   DefaultISR                                      /* 147 */
    .long   DefaultISR                                      /* 148 */
    .long   DefaultISR                                      /* 149 */
    .long   DefaultISR                                      /* 150 */
    .long   DefaultISR                                      /* 151 */
    .long   DefaultISR                                      /* 152 */
    .long   DefaultISR                                      /* 153 */
    .long   DefaultISR                                      /* 154 */
    .long   DefaultISR                                      /* 155 */
    .long   DefaultISR                                      /* 156 */
    .long   DefaultISR                                      /* 157 */
    .long   DefaultISR                                      /* 158 */
    .long   DefaultISR                                      /* 159 */
    .long   DefaultISR                                      /* 160 */
    .long   DefaultISR                                      /* 161 */
    .long   DefaultISR                                      /* 162 */
    .long   DefaultISR                                      /* 163 */
    .long   DefaultISR                                      /* 164 */
    .long   DefaultISR                                      /* 165 */
    .long   DefaultISR                                      /* 166 */
    .long   DefaultISR                                      /* 167 */
    .long   DefaultISR                                      /* 168 */
    .long   DefaultISR                                      /* 169 */
    .long   DefaultISR                                      /* 170 */
    .long   DefaultISR                                      /* 171 */
    .long   DefaultISR                                      /* 172 */
    .long   DefaultISR                                      /* 173 */
    .long   DefaultISR                                      /* 174 */
    .long   DefaultISR                                      /* 175 */
    .long   DefaultISR                                      /* 176 */
    .long   DefaultISR                                      /* 177 */
    .long   DefaultISR                                      /* 178 */
    .long   DefaultISR                                      /* 179 */
    .long   DefaultISR                                      /* 180 */
    .long   DefaultISR                                      /* 181 */
    .long   DefaultISR                                      /* 182 */
    .long   DefaultISR                                      /* 183 */
    .long   DefaultISR                                      /* 184 */
    .long   DefaultISR                                      /* 185 */
    .long   DefaultISR                                      /* 186 */
    .long   DefaultISR                                      /* 187 */
    .long   DefaultISR                                      /* 188 */
    .long   DefaultISR                                      /* 189 */
    .long   DefaultISR                                      /* 190 */
    .long   DefaultISR                                      /* 191 */
    .long   DefaultISR                                      /* 192 */
    .long   DefaultISR                                      /* 193 */
    .long   DefaultISR                                      /* 194 */
    .long   DefaultISR                                      /* 195 */
    .long   DefaultISR                                      /* 196 */
    .long   DefaultISR                                      /* 197 */
    .long   DefaultISR                                      /* 198 */
    .long   DefaultISR                                      /* 199 */
    .long   DefaultISR                                      /* 200 */
    .long   DefaultISR                                      /* 201 */
    .long   DefaultISR                                      /* 202 */
    .long   DefaultISR                                      /* 203 */
    .long   DefaultISR                                      /* 204 */
    .long   DefaultISR                                      /* 205 */
    .long   DefaultISR                                      /* 206 */
    .long   DefaultISR                                      /* 207 */
    .long   DefaultISR                                      /* 208 */
    .long   DefaultISR                                      /* 209 */
    .long   DefaultISR                                      /* 210 */
    .long   DefaultISR                                      /* 211 */
    .long   DefaultISR                                      /* 212 */
    .long   DefaultISR                                      /* 213 */
    .long   DefaultISR                                      /* 214 */
    .long   DefaultISR                                      /* 215 */
    .long   DefaultISR                                      /* 216 */
    .long   DefaultISR                                      /* 217 */
    .long   DefaultISR                                      /* 218 */
    .long   DefaultISR                                      /* 219 */
    .long   DefaultISR                                      /* 220 */
    .long   DefaultISR                                      /* 221 */
    .long   DefaultISR                                      /* 222 */
    .long   DefaultISR                                      /* 223 */
    .long   DefaultISR                                      /* 224 */
    .long   DefaultISR                                      /* 225 */
    .long   DefaultISR                                      /* 226 */
    .long   DefaultISR                                      /* 227 */
    .long   DefaultISR                                      /* 228 */
    .long   DefaultISR                                      /* 229 */
    .long   DefaultISR                                      /* 230 */
    .long   DefaultISR                                      /* 231 */
    .long   DefaultISR                                      /* 232 */
    .long   DefaultISR                                      /* 233 */
    .long   DefaultISR                                      /* 234 */
    .long   DefaultISR                                      /* 235 */
    .long   DefaultISR                                      /* 236 */
    .long   DefaultISR                                      /* 237 */
    .long   DefaultISR                                      /* 238 */
    .long   DefaultISR                                      /* 239 */
    .long   DefaultISR                                      /* 240 */
    .long   DefaultISR                                      /* 241 */
    .long   DefaultISR                                      /* 242 */
    .long   DefaultISR                                      /* 243 */
    .long   DefaultISR                                      /* 244 */
    .long   DefaultISR                                      /* 245 */
    .long   DefaultISR                                      /* 246 */
    .long   DefaultISR                                      /* 247 */
    .long   DefaultISR                                      /* 248 */
    .long   DefaultISR                                      /* 249 */
    .long   DefaultISR                                      /* 250 */
    .long   DefaultISR                                      /* 251 */
    .long   DefaultISR                                      /* 252 */
    .long   DefaultISR                                      /* 253 */
    .long   DefaultISR                                      /* 254 */
    .long   0xFFFFFFFF                                      /*  Reserved for user TRIM value */

    .size    __isr_vector, . - __isr_vector


/**************************************************************/
/************************ set other  ***************************/
    .text
    .thumb

/* Reset Handler */

    .thumb_func
    .align 2
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, %function

Reset_Handler:
    cpsid   i               /* Mask interrupts */

    /* Init the rest of the registers */
    ldr     r1,=0
    ldr     r2,=0
    ldr     r3,=0
    ldr     r4,=0
    ldr     r5,=0
    ldr     r6,=0
    ldr     r7,=0
    mov     r8,r7
    mov     r9,r7
    mov     r10,r7
    mov     r11,r7
    mov     r12,r7

    ldr        r0, =0xE000ED08
    ldr        r1, =__vector_table
    str        r1, [r0]

    /* Initialize the stack pointer */
    ldr     r0,=__StackTop
    mov     sp,r0   ; sp=r13 

    /* Clear Stack */
    ldr r2, =__StackLimit
    ldr r4, =__StackTop
    movs r3, #0
    b LoopFillZero_STACK

FillZero_STACK:
    str  r3, [r2]
    adds r2, r2, #4

LoopFillZero_STACK:
    cmp r2, r4
    bcc FillZero_STACK

    /* System Initialization */
    ldr     r0,=System_Init
    blx     r0

    /* Initialize .data and .bss sections */
    ldr     r0,=Data_Init
    blx     r0
    
    cpsie   i               /* Unmask interrupts */
    bl      main
JumpToSelf:
    b       JumpToSelf

    .pool
    .size Reset_Handler, . - Reset_Handler

    .align  1
    .thumb_func
    .weak DefaultISR
    .type DefaultISR, %function
DefaultISR:
    b       DefaultISR
    .size DefaultISR, . - DefaultISR

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro def_irq_handler    handler_name
    .weak \handler_name
    .set  \handler_name, DefaultISR
    .endm

/* Exception Handlers */
    def_irq_handler NMI_Handler
    def_irq_handler HardFault_Handler
    def_irq_handler MemManage_Handler
    def_irq_handler BusFault_Handler
    def_irq_handler UsageFault_Handler
    def_irq_handler SVC_Handler
    def_irq_handler DebugMon_Handler
    def_irq_handler PendSV_Handler
    def_irq_handler SysTick_Handler
    def_irq_handler DMA0_IRQHandler
    def_irq_handler DMA1_IRQHandler
    def_irq_handler DMA2_IRQHandler
    def_irq_handler DMA3_IRQHandler
    def_irq_handler DMA4_IRQHandler
    def_irq_handler DMA5_IRQHandler
    def_irq_handler DMA6_IRQHandler
    def_irq_handler DMA7_IRQHandler
    def_irq_handler DMA8_IRQHandler
    def_irq_handler DMA9_IRQHandler
    def_irq_handler DMA10_IRQHandler
    def_irq_handler DMA11_IRQHandler
    def_irq_handler DMA12_IRQHandler
    def_irq_handler DMA13_IRQHandler
    def_irq_handler DMA14_IRQHandler
    def_irq_handler DMA15_IRQHandler
    def_irq_handler DMA_Error_IRQHandler
    def_irq_handler CPM_IRQHandler
    def_irq_handler FC_IRQHandler
    def_irq_handler PMC_IRQHandler
    def_irq_handler TMU_IRQHandler
    def_irq_handler WDOG0_IRQHandler
    def_irq_handler WDOG1_IRQHandler
    def_irq_handler FCSMU0_IRQHandler
    def_irq_handler STCU0_IRQHandler
    def_irq_handler ERM_fault_IRQHandler
    def_irq_handler MAM0_IRQHandler
    def_irq_handler RGM_Pre_IRQHandler
    def_irq_handler INTM0_IRQHandler
    def_irq_handler ISM0_IRQHandler
    def_irq_handler MB_IRQHandler
    def_irq_handler SCG_IRQHandler
    def_irq_handler CMU0_IRQHandler
    def_irq_handler CMU1_IRQHandler
    def_irq_handler CMU2_IRQHandler
    def_irq_handler CMU3_IRQHandler
    def_irq_handler CMU4_IRQHandler
    def_irq_handler TSTMP0_IRQHandler
    def_irq_handler TSTMP1_IRQHandler
    def_irq_handler CORDIC_IRQHandler
    def_irq_handler HSM0_IRQHandler
    def_irq_handler FCPIT0_IRQHandler
    def_irq_handler RTC_IRQHandler
    def_irq_handler AONTIMER_IRQHandler
    def_irq_handler SWI_IRQHandler
    def_irq_handler FREQM_IRQHandler
    def_irq_handler ADC0_IRQHandler
    def_irq_handler ADC1_IRQHandler
    def_irq_handler PTIMER0_IRQHandler
    def_irq_handler PTIMER1_IRQHandler
    def_irq_handler CAN0_IRQHandler
    def_irq_handler CAN1_IRQHandler
    def_irq_handler CAN2_IRQHandler
    def_irq_handler CAN3_IRQHandler
    def_irq_handler FCIIC0_IRQHandler
    def_irq_handler FCIIC1_IRQHandler
    def_irq_handler FCSPI0_IRQHandler
    def_irq_handler FCSPI1_IRQHandler
    def_irq_handler FCSPI2_IRQHandler
    def_irq_handler FCSPI3_IRQHandler
    def_irq_handler FCSPI4_IRQHandler
    def_irq_handler FCSPI5_IRQHandler
    def_irq_handler FCUART0_RxTx_IRQHandler
    def_irq_handler FCUART1_RxTx_IRQHandler
    def_irq_handler FCUART2_RxTx_IRQHandler
    def_irq_handler FCUART3_RxTx_IRQHandler
    def_irq_handler FCUART4_RxTx_IRQHandler
    def_irq_handler FCUART5_RxTx_IRQHandler
    def_irq_handler FCUART6_RxTx_IRQHandler
    def_irq_handler FCUART7_RxTx_IRQHandler
    def_irq_handler FTU0_IRQHandler
    def_irq_handler FTU1_IRQHandler
    def_irq_handler FTU2_IRQHandler
    def_irq_handler FTU3_IRQHandler
    def_irq_handler FTU4_IRQHandler
    def_irq_handler FTU5_IRQHandler
    def_irq_handler FTU6_IRQHandler
    def_irq_handler FTU7_IRQHandler
    def_irq_handler CMP0_IRQHandler
    def_irq_handler CMP1_IRQHandler
    def_irq_handler PORTA_IRQHandler
    def_irq_handler PORTB_IRQHandler
    def_irq_handler PORTC_IRQHandler
    def_irq_handler PORTD_IRQHandler
    def_irq_handler PORTE_IRQHandler
    def_irq_handler MSC0_IRQHandler
    def_irq_handler SENT0_IRQHandler
    def_irq_handler TPU0_CH0_7_IRQHandler
    def_irq_handler TPU0_CH8_15_IRQHandler
    def_irq_handler TPU0_CH16_23_IRQHandler
    def_irq_handler TPU0_CH24_31_IRQHandler
    def_irq_handler HSM0_CRYPTO_IRQHandler
    .end
