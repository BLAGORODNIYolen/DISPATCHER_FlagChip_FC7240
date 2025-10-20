#ifndef _FC7240_PCC_NU_Tztufn5_REGS_H_
#define _FC7240_PCC_NU_Tztufn5_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- PCC Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup PCC_Peripheral_Access_Layer PCC Peripheral Access Layer

 * @{

 */



/** PCC - Size of Registers Arrays */



/** PCC - Register Layout Typedef */



typedef struct {



       uint8_t  RESERVED_0[32];

  __IO uint32_t PCC_DMA0                      ; /* DMA0 Clock Control Register, offset: 0x20 */

       uint8_t  RESERVED_1[4];

  __IO uint32_t PCC_DMAMUX0                   ; /* DMAMUX0 Clock Control Register, offset: 0x28 */

       uint8_t  RESERVED_2[32];

  __IO uint32_t PCC_ROMC                      ; /* ROMC Clock Control Register, offset: 0x4C */

       uint8_t  RESERVED_3[16];

  __IO uint32_t PCC_ERM                       ; /* ERM Clock Control Register, offset: 0x60 */

  __IO uint32_t PCC_EIM                       ; /* EIM Clock Control Register, offset: 0x64 */

  __IO uint32_t PCC_INTM0                     ; /* INTM0 Clock Control Register, offset: 0x68 */

  __IO uint32_t PCC_ISM0                      ; /* ISM0 Clock Control Register, offset: 0x6C */

       uint8_t  RESERVED_4[24];

  __IO uint32_t PCC_WDOG0                     ; /* WDOG0 Clock Control Register, offset: 0x88 */

       uint8_t  RESERVED_5[12];

  __IO uint32_t PCC_TRGSEL0                   ; /* TRGSEL0 Clock Control Register, offset: 0x98 */

  __IO uint32_t PCC_TRGSEL1                   ; /* TRGSEL1 Clock Control Register, offset: 0x9C */

  __IO uint32_t PCC_TRGSEL2                   ; /* TRGSEL2 Clock Control Register, offset: 0xA0 */

  __IO uint32_t PCC_TRGSEL3                   ; /* TRGSEL3 Clock Control Register, offset: 0xA4 */

  __IO uint32_t PCC_CRC0                      ; /* CRC0 Clock Control Register, offset: 0xA8 */

  __IO uint32_t PCC_CORDIC0                   ; /* CORDIC0 Clock Control Register, offset: 0xAC */

  __IO uint32_t PCC_TSTMP0                    ; /* TSTMP0 Clock Control Register, offset: 0xB0 */

  __IO uint32_t PCC_TSTMP1                    ; /* TSTMP1 Clock Control Register, offset: 0xB4 */

  __IO uint32_t PCC_FCPIT0                    ; /* FCPIT0 Clock Control Register, offset: 0xB8 */

  __IO uint32_t PCC_AONTIMER0                 ; /* AONTIMER0 Clock Control Register, offset: 0xBC */

  __IO uint32_t PCC_RTC                       ; /* RTC Clock Control Register, offset: 0xC0 */

  __IO uint32_t PCC_CMU0                      ; /* CMU0 Clock Control Register, offset: 0xC4 */

  __IO uint32_t PCC_CMU1                      ; /* CMU1 Clock Control Register, offset: 0xC8 */

  __IO uint32_t PCC_CMU2                      ; /* CMU2 Clock Control Register, offset: 0xCC */

  __IO uint32_t PCC_CMU3                      ; /* CMU3 Clock Control Register, offset: 0xD0 */

  __IO uint32_t PCC_CMU4                      ; /* CMU4 Clock Control Register, offset: 0xD4 */

       uint8_t  RESERVED_6[4];

  __IO uint32_t PCC_PTIMER0                   ; /* PTIMER0 Clock Control Register, offset: 0xDC */

  __IO uint32_t PCC_PTIMER1                   ; /* PTIMER1 Clock Control Register, offset: 0xE0 */

       uint8_t  RESERVED_7[8];

  __IO uint32_t PCC_ADC0                      ; /* ADC0 Clock Control Register, offset: 0xEC */

  __IO uint32_t PCC_ADC1                      ; /* ADC1 Clock Control Register, offset: 0xF0 */

       uint8_t  RESERVED_8[8];

  __IO uint32_t PCC_WKU                       ; /* WKU Clock Control Register, offset: 0xFC */

  __IO uint32_t PCC_CMP0                      ; /* CMP0 Clock Control Register, offset: 0x100 */

  __IO uint32_t PCC_CMP1                      ; /* CMP1 Clock Control Register, offset: 0x104 */

       uint8_t  RESERVED_9[4];

  __IO uint32_t PCC_TMU                       ; /* TMU Clock Control Register, offset: 0x10C */

       uint8_t  RESERVED_10[64];

  __IO uint32_t PCC_SENT0                     ; /* SENT0 Clock Control Register, offset: 0x150 */

       uint8_t  RESERVED_11[12];

  __IO uint32_t PCC_MB                        ; /* MB Clock Control Register, offset: 0x160 */

       uint8_t  RESERVED_12[12];

  __IO uint32_t PCC_FTU0                      ; /* FTU0 Clock Control Register, offset: 0x170 */

  __IO uint32_t PCC_FTU1                      ; /* FTU1 Clock Control Register, offset: 0x174 */

  __IO uint32_t PCC_FTU2                      ; /* FTU2 Clock Control Register, offset: 0x178 */

  __IO uint32_t PCC_FTU3                      ; /* FTU3 Clock Control Register, offset: 0x17C */

       uint8_t  RESERVED_13[8];

  __IO uint32_t PCC_FCSPI0                    ; /* FCSPI0 Clock Control Register, offset: 0x188 */

  __IO uint32_t PCC_FCSPI1                    ; /* FCSPI1 Clock Control Register, offset: 0x18C */

  __IO uint32_t PCC_FCSPI2                    ; /* FCSPI2 Clock Control Register, offset: 0x190 */

       uint8_t  RESERVED_14[4];

  __IO uint32_t PCC_FCIIC0                    ; /* FCIIC0 Clock Control Register, offset: 0x198 */

       uint8_t  RESERVED_15[4];

  __IO uint32_t PCC_FCUART0                   ; /* FCUART0 Clock Control Register, offset: 0x1A0 */

  __IO uint32_t PCC_FCUART1                   ; /* FCUART1 Clock Control Register, offset: 0x1A4 */

  __IO uint32_t PCC_FCUART2                   ; /* FCUART2 Clock Control Register, offset: 0x1A8 */

  __IO uint32_t PCC_FCUART3                   ; /* FCUART3 Clock Control Register, offset: 0x1AC */

       uint8_t  RESERVED_16[16];

  __IO uint32_t PCC_LU0                       ; /* LU0 Clock Control Register, offset: 0x1C0 */

       uint8_t  RESERVED_17[28];

  __IO uint32_t PCC_FREQM                     ; /* FREQM Clock Control Register, offset: 0x1E0 */

       uint8_t  RESERVED_18[24];

  __IO uint32_t PCC_STCU                      ; /* STCU Clock Control Register, offset: 0x1FC */

  __IO uint32_t PCC_FLEXCAN0                  ; /* FLEXCAN0 Clock Control Register, offset: 0x200 */

       uint8_t  RESERVED_19[12];

  __IO uint32_t PCC_FLEXCAN1                  ; /* FLEXCAN1 Clock Control Register, offset: 0x210 */

       uint8_t  RESERVED_20[312];

  __IO uint32_t PCC_WDOG1                     ; /* WDOG1 Clock Control Register, offset: 0x34C */

       uint8_t  RESERVED_21[28];

  __IO uint32_t PCC_TRGSEL4                   ; /* TRGSEL4 Clock Control Register, offset: 0x36C */

  __IO uint32_t PCC_TRGSEL5                   ; /* TRGSEL5 Clock Control Register, offset: 0x370 */

       uint8_t  RESERVED_22[8];

  __IO uint32_t PCC_FCSPI3                    ; /* FCSPI3 Clock Control Register, offset: 0x37C */

  __IO uint32_t PCC_FCSPI4                    ; /* FCSPI4 Clock Control Register, offset: 0x380 */

  __IO uint32_t PCC_FCSPI5                    ; /* FCSPI5 Clock Control Register, offset: 0x384 */

       uint8_t  RESERVED_23[116];

  __IO uint32_t PCC_FTU4                      ; /* FTU4 Clock Control Register, offset: 0x3FC */

  __IO uint32_t PCC_FTU5                      ; /* FTU5 Clock Control Register, offset: 0x400 */

  __IO uint32_t PCC_FTU6                      ; /* FTU6 Clock Control Register, offset: 0x404 */

  __IO uint32_t PCC_FTU7                      ; /* FTU7 Clock Control Register, offset: 0x408 */

       uint8_t  RESERVED_24[16];

  __IO uint32_t PCC_FCIIC1                    ; /* FCIIC1 Clock Control Register, offset: 0x41C */

  __IO uint32_t PCC_FCUART4                   ; /* FCUART4 Clock Control Register, offset: 0x420 */

  __IO uint32_t PCC_FCUART5                   ; /* FCUART5 Clock Control Register, offset: 0x424 */

  __IO uint32_t PCC_FCUART6                   ; /* FCUART6 Clock Control Register, offset: 0x428 */

  __IO uint32_t PCC_FCUART7                   ; /* FCUART7 Clock Control Register, offset: 0x42C */

       uint8_t  RESERVED_25[32];

  __IO uint32_t PCC_MSC0                      ; /* MSC0 Clock Control Register, offset: 0x450 */

       uint8_t  RESERVED_26[44];

  __IO uint32_t PCC_FLEXCAN2                  ; /* FLEXCAN2 Clock Control Register, offset: 0x480 */

       uint8_t  RESERVED_27[12];

  __IO uint32_t PCC_FLEXCAN3                  ; /* FLEXCAN3 Clock Control Register, offset: 0x490 */



} PCC_Type, *PCC_MemMapPtr;



/** Number of instances of the PCC module. */

#define PCC_INSTANCE_COUNT                       (1u)



/* PCC - Peripheral instance base addresses */

/** Peripheral PCC base address */

#define PCC_BASE                                 (0x40024000u)

/** Peripheral PCC base pointer */

#define PCC                                      ((PCC_Type *)PCC_BASE)

/** Array initializer of PCC peripheral base addresses */

#define PCC_BASE_ADDRS                           {PCC_BASE}

/** Array initializer of PCC peripheral base pointers */

#define PCC_BASE_PTRS                            {PCC}

// need fill by yourself

///** Number of interrupt vector arrays for the PCC module. */

//#define PCC_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the PCC module. */

//#define PCC_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the PCC peripheral type */

//#define PCC_IRQS                                 {PCC_IRQn}





/* ----------------------------------------------------------------------------

   -- PCC Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup PCC_Register_Masks PCC Register Masks

 * @{

 */



/* DMA0 Bit Fields */

#define PCC_DMA0_CGC_MASK              0x800000u

#define PCC_DMA0_CGC_SHIFT             23u

#define PCC_DMA0_CGC_WIDTH             1u

#define PCC_DMA0_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_DMA0_CGC_SHIFT))&PCC_DMA0_CGC_MASK)

#define PCC_DMA0_SWR_MASK              0x10000u

#define PCC_DMA0_SWR_SHIFT             16u

#define PCC_DMA0_SWR_WIDTH             1u

#define PCC_DMA0_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_DMA0_SWR_SHIFT))&PCC_DMA0_SWR_MASK)

/* DMA0 Reg Mask */

#define PCC_DMA0_MASK                  0x00810000u



/* DMAMUX0 Bit Fields */

#define PCC_DMAMUX0_CGC_MASK           0x800000u

#define PCC_DMAMUX0_CGC_SHIFT          23u

#define PCC_DMAMUX0_CGC_WIDTH          1u

#define PCC_DMAMUX0_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_DMAMUX0_CGC_SHIFT))&PCC_DMAMUX0_CGC_MASK)

#define PCC_DMAMUX0_SWR_MASK           0x10000u

#define PCC_DMAMUX0_SWR_SHIFT          16u

#define PCC_DMAMUX0_SWR_WIDTH          1u

#define PCC_DMAMUX0_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_DMAMUX0_SWR_SHIFT))&PCC_DMAMUX0_SWR_MASK)

/* DMAMUX0 Reg Mask */

#define PCC_DMAMUX0_MASK               0x00810000u



/* ROMC Bit Fields */

#define PCC_ROMC_CGC_MASK              0x800000u

#define PCC_ROMC_CGC_SHIFT             23u

#define PCC_ROMC_CGC_WIDTH             1u

#define PCC_ROMC_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ROMC_CGC_SHIFT))&PCC_ROMC_CGC_MASK)

#define PCC_ROMC_SWR_MASK              0x10000u

#define PCC_ROMC_SWR_SHIFT             16u

#define PCC_ROMC_SWR_WIDTH             1u

#define PCC_ROMC_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ROMC_SWR_SHIFT))&PCC_ROMC_SWR_MASK)

/* ROMC Reg Mask */

#define PCC_ROMC_MASK                  0x00810000u



/* ERM Bit Fields */

#define PCC_ERM_CGC_MASK               0x800000u

#define PCC_ERM_CGC_SHIFT              23u

#define PCC_ERM_CGC_WIDTH              1u

#define PCC_ERM_CGC(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_ERM_CGC_SHIFT))&PCC_ERM_CGC_MASK)

#define PCC_ERM_SWR_MASK               0x10000u

#define PCC_ERM_SWR_SHIFT              16u

#define PCC_ERM_SWR_WIDTH              1u

#define PCC_ERM_SWR(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_ERM_SWR_SHIFT))&PCC_ERM_SWR_MASK)

/* ERM Reg Mask */

#define PCC_ERM_MASK                   0x00810000u



/* EIM Bit Fields */

#define PCC_EIM_CGC_MASK               0x800000u

#define PCC_EIM_CGC_SHIFT              23u

#define PCC_EIM_CGC_WIDTH              1u

#define PCC_EIM_CGC(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_EIM_CGC_SHIFT))&PCC_EIM_CGC_MASK)

#define PCC_EIM_SWR_MASK               0x10000u

#define PCC_EIM_SWR_SHIFT              16u

#define PCC_EIM_SWR_WIDTH              1u

#define PCC_EIM_SWR(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_EIM_SWR_SHIFT))&PCC_EIM_SWR_MASK)

/* EIM Reg Mask */

#define PCC_EIM_MASK                   0x00810000u



/* INTM0 Bit Fields */

#define PCC_INTM0_CGC_MASK             0x800000u

#define PCC_INTM0_CGC_SHIFT            23u

#define PCC_INTM0_CGC_WIDTH            1u

#define PCC_INTM0_CGC(x)               (((uint32_t)(((uint32_t)(x))<<PCC_INTM0_CGC_SHIFT))&PCC_INTM0_CGC_MASK)

#define PCC_INTM0_SWR_MASK             0x10000u

#define PCC_INTM0_SWR_SHIFT            16u

#define PCC_INTM0_SWR_WIDTH            1u

#define PCC_INTM0_SWR(x)               (((uint32_t)(((uint32_t)(x))<<PCC_INTM0_SWR_SHIFT))&PCC_INTM0_SWR_MASK)

/* INTM0 Reg Mask */

#define PCC_INTM0_MASK                 0x00810000u



/* ISM0 Bit Fields */

#define PCC_ISM0_CGC_MASK              0x800000u

#define PCC_ISM0_CGC_SHIFT             23u

#define PCC_ISM0_CGC_WIDTH             1u

#define PCC_ISM0_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ISM0_CGC_SHIFT))&PCC_ISM0_CGC_MASK)

#define PCC_ISM0_SWR_MASK              0x10000u

#define PCC_ISM0_SWR_SHIFT             16u

#define PCC_ISM0_SWR_WIDTH             1u

#define PCC_ISM0_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ISM0_SWR_SHIFT))&PCC_ISM0_SWR_MASK)

/* ISM0 Reg Mask */

#define PCC_ISM0_MASK                  0x00810000u



/* WDOG0 Bit Fields */

#define PCC_WDOG0_SWR_MASK             0x10000u

#define PCC_WDOG0_SWR_SHIFT            16u

#define PCC_WDOG0_SWR_WIDTH            1u

#define PCC_WDOG0_SWR(x)               (((uint32_t)(((uint32_t)(x))<<PCC_WDOG0_SWR_SHIFT))&PCC_WDOG0_SWR_MASK)

/* WDOG0 Reg Mask */

#define PCC_WDOG0_MASK                 0x00010000u



/* TRGSEL0 Bit Fields */

#define PCC_TRGSEL0_CGC_MASK           0x800000u

#define PCC_TRGSEL0_CGC_SHIFT          23u

#define PCC_TRGSEL0_CGC_WIDTH          1u

#define PCC_TRGSEL0_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_TRGSEL0_CGC_SHIFT))&PCC_TRGSEL0_CGC_MASK)

#define PCC_TRGSEL0_SWR_MASK           0x10000u

#define PCC_TRGSEL0_SWR_SHIFT          16u

#define PCC_TRGSEL0_SWR_WIDTH          1u

#define PCC_TRGSEL0_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_TRGSEL0_SWR_SHIFT))&PCC_TRGSEL0_SWR_MASK)

/* TRGSEL0 Reg Mask */

#define PCC_TRGSEL0_MASK               0x00810000u



/* TRGSEL1 Bit Fields */

#define PCC_TRGSEL1_CGC_MASK           0x800000u

#define PCC_TRGSEL1_CGC_SHIFT          23u

#define PCC_TRGSEL1_CGC_WIDTH          1u

#define PCC_TRGSEL1_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_TRGSEL1_CGC_SHIFT))&PCC_TRGSEL1_CGC_MASK)

#define PCC_TRGSEL1_SWR_MASK           0x10000u

#define PCC_TRGSEL1_SWR_SHIFT          16u

#define PCC_TRGSEL1_SWR_WIDTH          1u

#define PCC_TRGSEL1_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_TRGSEL1_SWR_SHIFT))&PCC_TRGSEL1_SWR_MASK)

/* TRGSEL1 Reg Mask */

#define PCC_TRGSEL1_MASK               0x00810000u



/* TRGSEL2 Bit Fields */

#define PCC_TRGSEL2_CGC_MASK           0x800000u

#define PCC_TRGSEL2_CGC_SHIFT          23u

#define PCC_TRGSEL2_CGC_WIDTH          1u

#define PCC_TRGSEL2_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_TRGSEL2_CGC_SHIFT))&PCC_TRGSEL2_CGC_MASK)

#define PCC_TRGSEL2_SWR_MASK           0x10000u

#define PCC_TRGSEL2_SWR_SHIFT          16u

#define PCC_TRGSEL2_SWR_WIDTH          1u

#define PCC_TRGSEL2_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_TRGSEL2_SWR_SHIFT))&PCC_TRGSEL2_SWR_MASK)

/* TRGSEL2 Reg Mask */

#define PCC_TRGSEL2_MASK               0x00810000u



/* TRGSEL3 Bit Fields */

#define PCC_TRGSEL3_CGC_MASK           0x800000u

#define PCC_TRGSEL3_CGC_SHIFT          23u

#define PCC_TRGSEL3_CGC_WIDTH          1u

#define PCC_TRGSEL3_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_TRGSEL3_CGC_SHIFT))&PCC_TRGSEL3_CGC_MASK)

#define PCC_TRGSEL3_SWR_MASK           0x10000u

#define PCC_TRGSEL3_SWR_SHIFT          16u

#define PCC_TRGSEL3_SWR_WIDTH          1u

#define PCC_TRGSEL3_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_TRGSEL3_SWR_SHIFT))&PCC_TRGSEL3_SWR_MASK)

/* TRGSEL3 Reg Mask */

#define PCC_TRGSEL3_MASK               0x00810000u



/* CRC0 Bit Fields */

#define PCC_CRC0_CGC_MASK              0x800000u

#define PCC_CRC0_CGC_SHIFT             23u

#define PCC_CRC0_CGC_WIDTH             1u

#define PCC_CRC0_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CRC0_CGC_SHIFT))&PCC_CRC0_CGC_MASK)

#define PCC_CRC0_SWR_MASK              0x10000u

#define PCC_CRC0_SWR_SHIFT             16u

#define PCC_CRC0_SWR_WIDTH             1u

#define PCC_CRC0_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CRC0_SWR_SHIFT))&PCC_CRC0_SWR_MASK)

/* CRC0 Reg Mask */

#define PCC_CRC0_MASK                  0x00810000u



/* CORDIC0 Bit Fields */

#define PCC_CORDIC0_CGC_MASK           0x800000u

#define PCC_CORDIC0_CGC_SHIFT          23u

#define PCC_CORDIC0_CGC_WIDTH          1u

#define PCC_CORDIC0_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_CORDIC0_CGC_SHIFT))&PCC_CORDIC0_CGC_MASK)

#define PCC_CORDIC0_SWR_MASK           0x10000u

#define PCC_CORDIC0_SWR_SHIFT          16u

#define PCC_CORDIC0_SWR_WIDTH          1u

#define PCC_CORDIC0_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_CORDIC0_SWR_SHIFT))&PCC_CORDIC0_SWR_MASK)

/* CORDIC0 Reg Mask */

#define PCC_CORDIC0_MASK               0x00810000u



/* TSTMP0 Bit Fields */

#define PCC_TSTMP0_CGC_MASK            0x800000u

#define PCC_TSTMP0_CGC_SHIFT           23u

#define PCC_TSTMP0_CGC_WIDTH           1u

#define PCC_TSTMP0_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_TSTMP0_CGC_SHIFT))&PCC_TSTMP0_CGC_MASK)

#define PCC_TSTMP0_SWR_MASK            0x10000u

#define PCC_TSTMP0_SWR_SHIFT           16u

#define PCC_TSTMP0_SWR_WIDTH           1u

#define PCC_TSTMP0_SWR(x)              (((uint32_t)(((uint32_t)(x))<<PCC_TSTMP0_SWR_SHIFT))&PCC_TSTMP0_SWR_MASK)

/* TSTMP0 Reg Mask */

#define PCC_TSTMP0_MASK                0x00810000u



/* TSTMP1 Bit Fields */

#define PCC_TSTMP1_CGC_MASK            0x800000u

#define PCC_TSTMP1_CGC_SHIFT           23u

#define PCC_TSTMP1_CGC_WIDTH           1u

#define PCC_TSTMP1_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_TSTMP1_CGC_SHIFT))&PCC_TSTMP1_CGC_MASK)

#define PCC_TSTMP1_SWR_MASK            0x10000u

#define PCC_TSTMP1_SWR_SHIFT           16u

#define PCC_TSTMP1_SWR_WIDTH           1u

#define PCC_TSTMP1_SWR(x)              (((uint32_t)(((uint32_t)(x))<<PCC_TSTMP1_SWR_SHIFT))&PCC_TSTMP1_SWR_MASK)

/* TSTMP1 Reg Mask */

#define PCC_TSTMP1_MASK                0x00810000u



/* FCPIT0 Bit Fields */

#define PCC_FCPIT0_CGC_MASK            0x800000u

#define PCC_FCPIT0_CGC_SHIFT           23u

#define PCC_FCPIT0_CGC_WIDTH           1u

#define PCC_FCPIT0_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCPIT0_CGC_SHIFT))&PCC_FCPIT0_CGC_MASK)

#define PCC_FCPIT0_SEL_MASK            0x700000u

#define PCC_FCPIT0_SEL_SHIFT           20u

#define PCC_FCPIT0_SEL_WIDTH           3u

#define PCC_FCPIT0_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCPIT0_SEL_SHIFT))&PCC_FCPIT0_SEL_MASK)

#define PCC_FCPIT0_SWR_MASK            0x10000u

#define PCC_FCPIT0_SWR_SHIFT           16u

#define PCC_FCPIT0_SWR_WIDTH           1u

#define PCC_FCPIT0_SWR(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCPIT0_SWR_SHIFT))&PCC_FCPIT0_SWR_MASK)

/* FCPIT0 Reg Mask */

#define PCC_FCPIT0_MASK                0x00F10000u



/* AONTIMER0 Bit Fields */

#define PCC_AONTIMER0_CGC_MASK         0x800000u

#define PCC_AONTIMER0_CGC_SHIFT        23u

#define PCC_AONTIMER0_CGC_WIDTH        1u

#define PCC_AONTIMER0_CGC(x)           (((uint32_t)(((uint32_t)(x))<<PCC_AONTIMER0_CGC_SHIFT))&PCC_AONTIMER0_CGC_MASK)

#define PCC_AONTIMER0_SEL_MASK         0x700000u

#define PCC_AONTIMER0_SEL_SHIFT        20u

#define PCC_AONTIMER0_SEL_WIDTH        3u

#define PCC_AONTIMER0_SEL(x)           (((uint32_t)(((uint32_t)(x))<<PCC_AONTIMER0_SEL_SHIFT))&PCC_AONTIMER0_SEL_MASK)

#define PCC_AONTIMER0_SWR_MASK         0x10000u

#define PCC_AONTIMER0_SWR_SHIFT        16u

#define PCC_AONTIMER0_SWR_WIDTH        1u

#define PCC_AONTIMER0_SWR(x)           (((uint32_t)(((uint32_t)(x))<<PCC_AONTIMER0_SWR_SHIFT))&PCC_AONTIMER0_SWR_MASK)

#define PCC_AONTIMER0_DIV_MASK         0x7u

#define PCC_AONTIMER0_DIV_SHIFT        0u

#define PCC_AONTIMER0_DIV_WIDTH        3u

#define PCC_AONTIMER0_DIV(x)           (((uint32_t)(((uint32_t)(x))<<PCC_AONTIMER0_DIV_SHIFT))&PCC_AONTIMER0_DIV_MASK)

/* AONTIMER0 Reg Mask */

#define PCC_AONTIMER0_MASK             0x00F10007u



/* RTC Bit Fields */

#define PCC_RTC_SWR_MASK               0x10000u

#define PCC_RTC_SWR_SHIFT              16u

#define PCC_RTC_SWR_WIDTH              1u

#define PCC_RTC_SWR(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_RTC_SWR_SHIFT))&PCC_RTC_SWR_MASK)

/* RTC Reg Mask */

#define PCC_RTC_MASK                   0x00010000u



/* CMU0 Bit Fields */

#define PCC_CMU0_CGC_MASK              0x800000u

#define PCC_CMU0_CGC_SHIFT             23u

#define PCC_CMU0_CGC_WIDTH             1u

#define PCC_CMU0_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMU0_CGC_SHIFT))&PCC_CMU0_CGC_MASK)

#define PCC_CMU0_SWR_MASK              0x10000u

#define PCC_CMU0_SWR_SHIFT             16u

#define PCC_CMU0_SWR_WIDTH             1u

#define PCC_CMU0_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMU0_SWR_SHIFT))&PCC_CMU0_SWR_MASK)

/* CMU0 Reg Mask */

#define PCC_CMU0_MASK                  0x00810000u



/* CMU1 Bit Fields */

#define PCC_CMU1_CGC_MASK              0x800000u

#define PCC_CMU1_CGC_SHIFT             23u

#define PCC_CMU1_CGC_WIDTH             1u

#define PCC_CMU1_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMU1_CGC_SHIFT))&PCC_CMU1_CGC_MASK)

#define PCC_CMU1_SWR_MASK              0x10000u

#define PCC_CMU1_SWR_SHIFT             16u

#define PCC_CMU1_SWR_WIDTH             1u

#define PCC_CMU1_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMU1_SWR_SHIFT))&PCC_CMU1_SWR_MASK)

/* CMU1 Reg Mask */

#define PCC_CMU1_MASK                  0x00810000u



/* CMU2 Bit Fields */

#define PCC_CMU2_CGC_MASK              0x800000u

#define PCC_CMU2_CGC_SHIFT             23u

#define PCC_CMU2_CGC_WIDTH             1u

#define PCC_CMU2_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMU2_CGC_SHIFT))&PCC_CMU2_CGC_MASK)

#define PCC_CMU2_SWR_MASK              0x10000u

#define PCC_CMU2_SWR_SHIFT             16u

#define PCC_CMU2_SWR_WIDTH             1u

#define PCC_CMU2_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMU2_SWR_SHIFT))&PCC_CMU2_SWR_MASK)

/* CMU2 Reg Mask */

#define PCC_CMU2_MASK                  0x00810000u



/* CMU3 Bit Fields */

#define PCC_CMU3_CGC_MASK              0x800000u

#define PCC_CMU3_CGC_SHIFT             23u

#define PCC_CMU3_CGC_WIDTH             1u

#define PCC_CMU3_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMU3_CGC_SHIFT))&PCC_CMU3_CGC_MASK)

#define PCC_CMU3_SWR_MASK              0x10000u

#define PCC_CMU3_SWR_SHIFT             16u

#define PCC_CMU3_SWR_WIDTH             1u

#define PCC_CMU3_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMU3_SWR_SHIFT))&PCC_CMU3_SWR_MASK)

/* CMU3 Reg Mask */

#define PCC_CMU3_MASK                  0x00810000u



/* CMU4 Bit Fields */

#define PCC_CMU4_CGC_MASK              0x800000u

#define PCC_CMU4_CGC_SHIFT             23u

#define PCC_CMU4_CGC_WIDTH             1u

#define PCC_CMU4_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMU4_CGC_SHIFT))&PCC_CMU4_CGC_MASK)

#define PCC_CMU4_SWR_MASK              0x10000u

#define PCC_CMU4_SWR_SHIFT             16u

#define PCC_CMU4_SWR_WIDTH             1u

#define PCC_CMU4_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMU4_SWR_SHIFT))&PCC_CMU4_SWR_MASK)

/* CMU4 Reg Mask */

#define PCC_CMU4_MASK                  0x00810000u



/* PTIMER0 Bit Fields */

#define PCC_PTIMER0_CGC_MASK           0x800000u

#define PCC_PTIMER0_CGC_SHIFT          23u

#define PCC_PTIMER0_CGC_WIDTH          1u

#define PCC_PTIMER0_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_PTIMER0_CGC_SHIFT))&PCC_PTIMER0_CGC_MASK)

#define PCC_PTIMER0_SWR_MASK           0x10000u

#define PCC_PTIMER0_SWR_SHIFT          16u

#define PCC_PTIMER0_SWR_WIDTH          1u

#define PCC_PTIMER0_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_PTIMER0_SWR_SHIFT))&PCC_PTIMER0_SWR_MASK)

/* PTIMER0 Reg Mask */

#define PCC_PTIMER0_MASK               0x00810000u



/* PTIMER1 Bit Fields */

#define PCC_PTIMER1_CGC_MASK           0x800000u

#define PCC_PTIMER1_CGC_SHIFT          23u

#define PCC_PTIMER1_CGC_WIDTH          1u

#define PCC_PTIMER1_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_PTIMER1_CGC_SHIFT))&PCC_PTIMER1_CGC_MASK)

#define PCC_PTIMER1_SWR_MASK           0x10000u

#define PCC_PTIMER1_SWR_SHIFT          16u

#define PCC_PTIMER1_SWR_WIDTH          1u

#define PCC_PTIMER1_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_PTIMER1_SWR_SHIFT))&PCC_PTIMER1_SWR_MASK)

/* PTIMER1 Reg Mask */

#define PCC_PTIMER1_MASK               0x00810000u



/* ADC0 Bit Fields */

#define PCC_ADC0_CGC_MASK              0x800000u

#define PCC_ADC0_CGC_SHIFT             23u

#define PCC_ADC0_CGC_WIDTH             1u

#define PCC_ADC0_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ADC0_CGC_SHIFT))&PCC_ADC0_CGC_MASK)

#define PCC_ADC0_SEL_MASK              0x700000u

#define PCC_ADC0_SEL_SHIFT             20u

#define PCC_ADC0_SEL_WIDTH             3u

#define PCC_ADC0_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ADC0_SEL_SHIFT))&PCC_ADC0_SEL_MASK)

#define PCC_ADC0_SWR_MASK              0x10000u

#define PCC_ADC0_SWR_SHIFT             16u

#define PCC_ADC0_SWR_WIDTH             1u

#define PCC_ADC0_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ADC0_SWR_SHIFT))&PCC_ADC0_SWR_MASK)

#define PCC_ADC0_DIV_MASK              0x7u

#define PCC_ADC0_DIV_SHIFT             0u

#define PCC_ADC0_DIV_WIDTH             3u

#define PCC_ADC0_DIV(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ADC0_DIV_SHIFT))&PCC_ADC0_DIV_MASK)

/* ADC0 Reg Mask */

#define PCC_ADC0_MASK                  0x00F10007u



/* ADC1 Bit Fields */

#define PCC_ADC1_CGC_MASK              0x800000u

#define PCC_ADC1_CGC_SHIFT             23u

#define PCC_ADC1_CGC_WIDTH             1u

#define PCC_ADC1_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ADC1_CGC_SHIFT))&PCC_ADC1_CGC_MASK)

#define PCC_ADC1_SEL_MASK              0x700000u

#define PCC_ADC1_SEL_SHIFT             20u

#define PCC_ADC1_SEL_WIDTH             3u

#define PCC_ADC1_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ADC1_SEL_SHIFT))&PCC_ADC1_SEL_MASK)

#define PCC_ADC1_SWR_MASK              0x10000u

#define PCC_ADC1_SWR_SHIFT             16u

#define PCC_ADC1_SWR_WIDTH             1u

#define PCC_ADC1_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ADC1_SWR_SHIFT))&PCC_ADC1_SWR_MASK)

#define PCC_ADC1_DIV_MASK              0x7u

#define PCC_ADC1_DIV_SHIFT             0u

#define PCC_ADC1_DIV_WIDTH             3u

#define PCC_ADC1_DIV(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ADC1_DIV_SHIFT))&PCC_ADC1_DIV_MASK)

/* ADC1 Reg Mask */

#define PCC_ADC1_MASK                  0x00F10007u



/* WKU Bit Fields */

#define PCC_WKU_CGC_MASK               0x800000u

#define PCC_WKU_CGC_SHIFT              23u

#define PCC_WKU_CGC_WIDTH              1u

#define PCC_WKU_CGC(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_WKU_CGC_SHIFT))&PCC_WKU_CGC_MASK)

#define PCC_WKU_SWR_MASK               0x10000u

#define PCC_WKU_SWR_SHIFT              16u

#define PCC_WKU_SWR_WIDTH              1u

#define PCC_WKU_SWR(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_WKU_SWR_SHIFT))&PCC_WKU_SWR_MASK)

/* WKU Reg Mask */

#define PCC_WKU_MASK                   0x00810000u



/* CMP0 Bit Fields */

#define PCC_CMP0_CGC_MASK              0x800000u

#define PCC_CMP0_CGC_SHIFT             23u

#define PCC_CMP0_CGC_WIDTH             1u

#define PCC_CMP0_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMP0_CGC_SHIFT))&PCC_CMP0_CGC_MASK)

#define PCC_CMP0_SWR_MASK              0x10000u

#define PCC_CMP0_SWR_SHIFT             16u

#define PCC_CMP0_SWR_WIDTH             1u

#define PCC_CMP0_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMP0_SWR_SHIFT))&PCC_CMP0_SWR_MASK)

/* CMP0 Reg Mask */

#define PCC_CMP0_MASK                  0x00810000u



/* CMP1 Bit Fields */

#define PCC_CMP1_CGC_MASK              0x800000u

#define PCC_CMP1_CGC_SHIFT             23u

#define PCC_CMP1_CGC_WIDTH             1u

#define PCC_CMP1_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMP1_CGC_SHIFT))&PCC_CMP1_CGC_MASK)

#define PCC_CMP1_SWR_MASK              0x10000u

#define PCC_CMP1_SWR_SHIFT             16u

#define PCC_CMP1_SWR_WIDTH             1u

#define PCC_CMP1_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMP1_SWR_SHIFT))&PCC_CMP1_SWR_MASK)

/* CMP1 Reg Mask */

#define PCC_CMP1_MASK                  0x00810000u



/* TMU Bit Fields */

#define PCC_TMU_CGC_MASK               0x800000u

#define PCC_TMU_CGC_SHIFT              23u

#define PCC_TMU_CGC_WIDTH              1u

#define PCC_TMU_CGC(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_TMU_CGC_SHIFT))&PCC_TMU_CGC_MASK)

#define PCC_TMU_SEL_MASK               0x700000u

#define PCC_TMU_SEL_SHIFT              20u

#define PCC_TMU_SEL_WIDTH              3u

#define PCC_TMU_SEL(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_TMU_SEL_SHIFT))&PCC_TMU_SEL_MASK)

#define PCC_TMU_SWR_MASK               0x10000u

#define PCC_TMU_SWR_SHIFT              16u

#define PCC_TMU_SWR_WIDTH              1u

#define PCC_TMU_SWR(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_TMU_SWR_SHIFT))&PCC_TMU_SWR_MASK)

/* TMU Reg Mask */

#define PCC_TMU_MASK                   0x00F10000u



/* SENT0 Bit Fields */

#define PCC_SENT0_CGC_MASK             0x800000u

#define PCC_SENT0_CGC_SHIFT            23u

#define PCC_SENT0_CGC_WIDTH            1u

#define PCC_SENT0_CGC(x)               (((uint32_t)(((uint32_t)(x))<<PCC_SENT0_CGC_SHIFT))&PCC_SENT0_CGC_MASK)

#define PCC_SENT0_SEL_MASK             0x700000u

#define PCC_SENT0_SEL_SHIFT            20u

#define PCC_SENT0_SEL_WIDTH            3u

#define PCC_SENT0_SEL(x)               (((uint32_t)(((uint32_t)(x))<<PCC_SENT0_SEL_SHIFT))&PCC_SENT0_SEL_MASK)

#define PCC_SENT0_SWR_MASK             0x10000u

#define PCC_SENT0_SWR_SHIFT            16u

#define PCC_SENT0_SWR_WIDTH            1u

#define PCC_SENT0_SWR(x)               (((uint32_t)(((uint32_t)(x))<<PCC_SENT0_SWR_SHIFT))&PCC_SENT0_SWR_MASK)

#define PCC_SENT0_DIV_MASK             0x7u

#define PCC_SENT0_DIV_SHIFT            0u

#define PCC_SENT0_DIV_WIDTH            3u

#define PCC_SENT0_DIV(x)               (((uint32_t)(((uint32_t)(x))<<PCC_SENT0_DIV_SHIFT))&PCC_SENT0_DIV_MASK)

/* SENT0 Reg Mask */

#define PCC_SENT0_MASK                 0x00F10007u



/* MB Bit Fields */

#define PCC_MB_SWR_MASK                0x10000u

#define PCC_MB_SWR_SHIFT               16u

#define PCC_MB_SWR_WIDTH               1u

#define PCC_MB_SWR(x)                  (((uint32_t)(((uint32_t)(x))<<PCC_MB_SWR_SHIFT))&PCC_MB_SWR_MASK)

/* MB Reg Mask */

#define PCC_MB_MASK                    0x00010000u



/* FTU0 Bit Fields */

#define PCC_FTU0_CGC_MASK              0x800000u

#define PCC_FTU0_CGC_SHIFT             23u

#define PCC_FTU0_CGC_WIDTH             1u

#define PCC_FTU0_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU0_CGC_SHIFT))&PCC_FTU0_CGC_MASK)

#define PCC_FTU0_SEL_MASK              0x700000u

#define PCC_FTU0_SEL_SHIFT             20u

#define PCC_FTU0_SEL_WIDTH             3u

#define PCC_FTU0_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU0_SEL_SHIFT))&PCC_FTU0_SEL_MASK)

#define PCC_FTU0_SWR_MASK              0x10000u

#define PCC_FTU0_SWR_SHIFT             16u

#define PCC_FTU0_SWR_WIDTH             1u

#define PCC_FTU0_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU0_SWR_SHIFT))&PCC_FTU0_SWR_MASK)

/* FTU0 Reg Mask */

#define PCC_FTU0_MASK                  0x00F10000u



/* FTU1 Bit Fields */

#define PCC_FTU1_CGC_MASK              0x800000u

#define PCC_FTU1_CGC_SHIFT             23u

#define PCC_FTU1_CGC_WIDTH             1u

#define PCC_FTU1_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU1_CGC_SHIFT))&PCC_FTU1_CGC_MASK)

#define PCC_FTU1_SEL_MASK              0x700000u

#define PCC_FTU1_SEL_SHIFT             20u

#define PCC_FTU1_SEL_WIDTH             3u

#define PCC_FTU1_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU1_SEL_SHIFT))&PCC_FTU1_SEL_MASK)

#define PCC_FTU1_SWR_MASK              0x10000u

#define PCC_FTU1_SWR_SHIFT             16u

#define PCC_FTU1_SWR_WIDTH             1u

#define PCC_FTU1_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU1_SWR_SHIFT))&PCC_FTU1_SWR_MASK)

/* FTU1 Reg Mask */

#define PCC_FTU1_MASK                  0x00F10000u



/* FTU2 Bit Fields */

#define PCC_FTU2_CGC_MASK              0x800000u

#define PCC_FTU2_CGC_SHIFT             23u

#define PCC_FTU2_CGC_WIDTH             1u

#define PCC_FTU2_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU2_CGC_SHIFT))&PCC_FTU2_CGC_MASK)

#define PCC_FTU2_SEL_MASK              0x700000u

#define PCC_FTU2_SEL_SHIFT             20u

#define PCC_FTU2_SEL_WIDTH             3u

#define PCC_FTU2_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU2_SEL_SHIFT))&PCC_FTU2_SEL_MASK)

#define PCC_FTU2_SWR_MASK              0x10000u

#define PCC_FTU2_SWR_SHIFT             16u

#define PCC_FTU2_SWR_WIDTH             1u

#define PCC_FTU2_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU2_SWR_SHIFT))&PCC_FTU2_SWR_MASK)

/* FTU2 Reg Mask */

#define PCC_FTU2_MASK                  0x00F10000u



/* FTU3 Bit Fields */

#define PCC_FTU3_CGC_MASK              0x800000u

#define PCC_FTU3_CGC_SHIFT             23u

#define PCC_FTU3_CGC_WIDTH             1u

#define PCC_FTU3_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU3_CGC_SHIFT))&PCC_FTU3_CGC_MASK)

#define PCC_FTU3_SEL_MASK              0x700000u

#define PCC_FTU3_SEL_SHIFT             20u

#define PCC_FTU3_SEL_WIDTH             3u

#define PCC_FTU3_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU3_SEL_SHIFT))&PCC_FTU3_SEL_MASK)

#define PCC_FTU3_SWR_MASK              0x10000u

#define PCC_FTU3_SWR_SHIFT             16u

#define PCC_FTU3_SWR_WIDTH             1u

#define PCC_FTU3_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU3_SWR_SHIFT))&PCC_FTU3_SWR_MASK)

/* FTU3 Reg Mask */

#define PCC_FTU3_MASK                  0x00F10000u



/* FCSPI0 Bit Fields */

#define PCC_FCSPI0_CGC_MASK            0x800000u

#define PCC_FCSPI0_CGC_SHIFT           23u

#define PCC_FCSPI0_CGC_WIDTH           1u

#define PCC_FCSPI0_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI0_CGC_SHIFT))&PCC_FCSPI0_CGC_MASK)

#define PCC_FCSPI0_SEL_MASK            0x700000u

#define PCC_FCSPI0_SEL_SHIFT           20u

#define PCC_FCSPI0_SEL_WIDTH           3u

#define PCC_FCSPI0_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI0_SEL_SHIFT))&PCC_FCSPI0_SEL_MASK)

#define PCC_FCSPI0_SWR_MASK            0x10000u

#define PCC_FCSPI0_SWR_SHIFT           16u

#define PCC_FCSPI0_SWR_WIDTH           1u

#define PCC_FCSPI0_SWR(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI0_SWR_SHIFT))&PCC_FCSPI0_SWR_MASK)

/* FCSPI0 Reg Mask */

#define PCC_FCSPI0_MASK                0x00F10000u



/* FCSPI1 Bit Fields */

#define PCC_FCSPI1_CGC_MASK            0x800000u

#define PCC_FCSPI1_CGC_SHIFT           23u

#define PCC_FCSPI1_CGC_WIDTH           1u

#define PCC_FCSPI1_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI1_CGC_SHIFT))&PCC_FCSPI1_CGC_MASK)

#define PCC_FCSPI1_SEL_MASK            0x700000u

#define PCC_FCSPI1_SEL_SHIFT           20u

#define PCC_FCSPI1_SEL_WIDTH           3u

#define PCC_FCSPI1_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI1_SEL_SHIFT))&PCC_FCSPI1_SEL_MASK)

#define PCC_FCSPI1_SWR_MASK            0x10000u

#define PCC_FCSPI1_SWR_SHIFT           16u

#define PCC_FCSPI1_SWR_WIDTH           1u

#define PCC_FCSPI1_SWR(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI1_SWR_SHIFT))&PCC_FCSPI1_SWR_MASK)

/* FCSPI1 Reg Mask */

#define PCC_FCSPI1_MASK                0x00F10000u



/* FCSPI2 Bit Fields */

#define PCC_FCSPI2_CGC_MASK            0x800000u

#define PCC_FCSPI2_CGC_SHIFT           23u

#define PCC_FCSPI2_CGC_WIDTH           1u

#define PCC_FCSPI2_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI2_CGC_SHIFT))&PCC_FCSPI2_CGC_MASK)

#define PCC_FCSPI2_SEL_MASK            0x700000u

#define PCC_FCSPI2_SEL_SHIFT           20u

#define PCC_FCSPI2_SEL_WIDTH           3u

#define PCC_FCSPI2_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI2_SEL_SHIFT))&PCC_FCSPI2_SEL_MASK)

#define PCC_FCSPI2_SWR_MASK            0x10000u

#define PCC_FCSPI2_SWR_SHIFT           16u

#define PCC_FCSPI2_SWR_WIDTH           1u

#define PCC_FCSPI2_SWR(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI2_SWR_SHIFT))&PCC_FCSPI2_SWR_MASK)

/* FCSPI2 Reg Mask */

#define PCC_FCSPI2_MASK                0x00F10000u



/* FCIIC0 Bit Fields */

#define PCC_FCIIC0_CGC_MASK            0x800000u

#define PCC_FCIIC0_CGC_SHIFT           23u

#define PCC_FCIIC0_CGC_WIDTH           1u

#define PCC_FCIIC0_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCIIC0_CGC_SHIFT))&PCC_FCIIC0_CGC_MASK)

#define PCC_FCIIC0_SEL_MASK            0x700000u

#define PCC_FCIIC0_SEL_SHIFT           20u

#define PCC_FCIIC0_SEL_WIDTH           3u

#define PCC_FCIIC0_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCIIC0_SEL_SHIFT))&PCC_FCIIC0_SEL_MASK)

#define PCC_FCIIC0_SWR_MASK            0x10000u

#define PCC_FCIIC0_SWR_SHIFT           16u

#define PCC_FCIIC0_SWR_WIDTH           1u

#define PCC_FCIIC0_SWR(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCIIC0_SWR_SHIFT))&PCC_FCIIC0_SWR_MASK)

/* FCIIC0 Reg Mask */

#define PCC_FCIIC0_MASK                0x00F10000u



/* FCUART0 Bit Fields */

#define PCC_FCUART0_CGC_MASK           0x800000u

#define PCC_FCUART0_CGC_SHIFT          23u

#define PCC_FCUART0_CGC_WIDTH          1u

#define PCC_FCUART0_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART0_CGC_SHIFT))&PCC_FCUART0_CGC_MASK)

#define PCC_FCUART0_SEL_MASK           0x700000u

#define PCC_FCUART0_SEL_SHIFT          20u

#define PCC_FCUART0_SEL_WIDTH          3u

#define PCC_FCUART0_SEL(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART0_SEL_SHIFT))&PCC_FCUART0_SEL_MASK)

#define PCC_FCUART0_SWR_MASK           0x10000u

#define PCC_FCUART0_SWR_SHIFT          16u

#define PCC_FCUART0_SWR_WIDTH          1u

#define PCC_FCUART0_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART0_SWR_SHIFT))&PCC_FCUART0_SWR_MASK)

/* FCUART0 Reg Mask */

#define PCC_FCUART0_MASK               0x00F10000u



/* FCUART1 Bit Fields */

#define PCC_FCUART1_CGC_MASK           0x800000u

#define PCC_FCUART1_CGC_SHIFT          23u

#define PCC_FCUART1_CGC_WIDTH          1u

#define PCC_FCUART1_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART1_CGC_SHIFT))&PCC_FCUART1_CGC_MASK)

#define PCC_FCUART1_SEL_MASK           0x700000u

#define PCC_FCUART1_SEL_SHIFT          20u

#define PCC_FCUART1_SEL_WIDTH          3u

#define PCC_FCUART1_SEL(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART1_SEL_SHIFT))&PCC_FCUART1_SEL_MASK)

#define PCC_FCUART1_SWR_MASK           0x10000u

#define PCC_FCUART1_SWR_SHIFT          16u

#define PCC_FCUART1_SWR_WIDTH          1u

#define PCC_FCUART1_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART1_SWR_SHIFT))&PCC_FCUART1_SWR_MASK)

/* FCUART1 Reg Mask */

#define PCC_FCUART1_MASK               0x00F10000u



/* FCUART2 Bit Fields */

#define PCC_FCUART2_CGC_MASK           0x800000u

#define PCC_FCUART2_CGC_SHIFT          23u

#define PCC_FCUART2_CGC_WIDTH          1u

#define PCC_FCUART2_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART2_CGC_SHIFT))&PCC_FCUART2_CGC_MASK)

#define PCC_FCUART2_SEL_MASK           0x700000u

#define PCC_FCUART2_SEL_SHIFT          20u

#define PCC_FCUART2_SEL_WIDTH          3u

#define PCC_FCUART2_SEL(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART2_SEL_SHIFT))&PCC_FCUART2_SEL_MASK)

#define PCC_FCUART2_SWR_MASK           0x10000u

#define PCC_FCUART2_SWR_SHIFT          16u

#define PCC_FCUART2_SWR_WIDTH          1u

#define PCC_FCUART2_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART2_SWR_SHIFT))&PCC_FCUART2_SWR_MASK)

/* FCUART2 Reg Mask */

#define PCC_FCUART2_MASK               0x00F10000u



/* FCUART3 Bit Fields */

#define PCC_FCUART3_CGC_MASK           0x800000u

#define PCC_FCUART3_CGC_SHIFT          23u

#define PCC_FCUART3_CGC_WIDTH          1u

#define PCC_FCUART3_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART3_CGC_SHIFT))&PCC_FCUART3_CGC_MASK)

#define PCC_FCUART3_SEL_MASK           0x700000u

#define PCC_FCUART3_SEL_SHIFT          20u

#define PCC_FCUART3_SEL_WIDTH          3u

#define PCC_FCUART3_SEL(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART3_SEL_SHIFT))&PCC_FCUART3_SEL_MASK)

#define PCC_FCUART3_SWR_MASK           0x10000u

#define PCC_FCUART3_SWR_SHIFT          16u

#define PCC_FCUART3_SWR_WIDTH          1u

#define PCC_FCUART3_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART3_SWR_SHIFT))&PCC_FCUART3_SWR_MASK)

/* FCUART3 Reg Mask */

#define PCC_FCUART3_MASK               0x00F10000u



/* LU0 Bit Fields */

#define PCC_LU0_CGC_MASK               0x800000u

#define PCC_LU0_CGC_SHIFT              23u

#define PCC_LU0_CGC_WIDTH              1u

#define PCC_LU0_CGC(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_LU0_CGC_SHIFT))&PCC_LU0_CGC_MASK)

#define PCC_LU0_SWR_MASK               0x10000u

#define PCC_LU0_SWR_SHIFT              16u

#define PCC_LU0_SWR_WIDTH              1u

#define PCC_LU0_SWR(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_LU0_SWR_SHIFT))&PCC_LU0_SWR_MASK)

/* LU0 Reg Mask */

#define PCC_LU0_MASK                   0x00810000u



/* FREQM Bit Fields */

#define PCC_FREQM_CGC_MASK             0x800000u

#define PCC_FREQM_CGC_SHIFT            23u

#define PCC_FREQM_CGC_WIDTH            1u

#define PCC_FREQM_CGC(x)               (((uint32_t)(((uint32_t)(x))<<PCC_FREQM_CGC_SHIFT))&PCC_FREQM_CGC_MASK)

#define PCC_FREQM_SWR_MASK             0x10000u

#define PCC_FREQM_SWR_SHIFT            16u

#define PCC_FREQM_SWR_WIDTH            1u

#define PCC_FREQM_SWR(x)               (((uint32_t)(((uint32_t)(x))<<PCC_FREQM_SWR_SHIFT))&PCC_FREQM_SWR_MASK)

/* FREQM Reg Mask */

#define PCC_FREQM_MASK                 0x00810000u



/* STCU Bit Fields */

#define PCC_STCU_CGC_MASK              0x800000u

#define PCC_STCU_CGC_SHIFT             23u

#define PCC_STCU_CGC_WIDTH             1u

#define PCC_STCU_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_STCU_CGC_SHIFT))&PCC_STCU_CGC_MASK)

#define PCC_STCU_SWR_MASK              0x10000u

#define PCC_STCU_SWR_SHIFT             16u

#define PCC_STCU_SWR_WIDTH             1u

#define PCC_STCU_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_STCU_SWR_SHIFT))&PCC_STCU_SWR_MASK)

/* STCU Reg Mask */

#define PCC_STCU_MASK                  0x00810000u



/* FLEXCAN0 Bit Fields */

#define PCC_FLEXCAN0_CGC_MASK          0x800000u

#define PCC_FLEXCAN0_CGC_SHIFT         23u

#define PCC_FLEXCAN0_CGC_WIDTH         1u

#define PCC_FLEXCAN0_CGC(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN0_CGC_SHIFT))&PCC_FLEXCAN0_CGC_MASK)

#define PCC_FLEXCAN0_SEL_MASK          0x700000u

#define PCC_FLEXCAN0_SEL_SHIFT         20u

#define PCC_FLEXCAN0_SEL_WIDTH         3u

#define PCC_FLEXCAN0_SEL(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN0_SEL_SHIFT))&PCC_FLEXCAN0_SEL_MASK)

#define PCC_FLEXCAN0_SWR_MASK          0x10000u

#define PCC_FLEXCAN0_SWR_SHIFT         16u

#define PCC_FLEXCAN0_SWR_WIDTH         1u

#define PCC_FLEXCAN0_SWR(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN0_SWR_SHIFT))&PCC_FLEXCAN0_SWR_MASK)

#define PCC_FLEXCAN0_DIV_MASK          0x7u

#define PCC_FLEXCAN0_DIV_SHIFT         0u

#define PCC_FLEXCAN0_DIV_WIDTH         3u

#define PCC_FLEXCAN0_DIV(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN0_DIV_SHIFT))&PCC_FLEXCAN0_DIV_MASK)

/* FLEXCAN0 Reg Mask */

#define PCC_FLEXCAN0_MASK              0x00F10007u



/* FLEXCAN1 Bit Fields */

#define PCC_FLEXCAN1_CGC_MASK          0x800000u

#define PCC_FLEXCAN1_CGC_SHIFT         23u

#define PCC_FLEXCAN1_CGC_WIDTH         1u

#define PCC_FLEXCAN1_CGC(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN1_CGC_SHIFT))&PCC_FLEXCAN1_CGC_MASK)

#define PCC_FLEXCAN1_SEL_MASK          0x700000u

#define PCC_FLEXCAN1_SEL_SHIFT         20u

#define PCC_FLEXCAN1_SEL_WIDTH         3u

#define PCC_FLEXCAN1_SEL(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN1_SEL_SHIFT))&PCC_FLEXCAN1_SEL_MASK)

#define PCC_FLEXCAN1_SWR_MASK          0x10000u

#define PCC_FLEXCAN1_SWR_SHIFT         16u

#define PCC_FLEXCAN1_SWR_WIDTH         1u

#define PCC_FLEXCAN1_SWR(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN1_SWR_SHIFT))&PCC_FLEXCAN1_SWR_MASK)

#define PCC_FLEXCAN1_DIV_MASK          0x7u

#define PCC_FLEXCAN1_DIV_SHIFT         0u

#define PCC_FLEXCAN1_DIV_WIDTH         3u

#define PCC_FLEXCAN1_DIV(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN1_DIV_SHIFT))&PCC_FLEXCAN1_DIV_MASK)

/* FLEXCAN1 Reg Mask */

#define PCC_FLEXCAN1_MASK              0x00F10007u



/* WDOG1 Bit Fields */

#define PCC_WDOG1_SWR_MASK             0x10000u

#define PCC_WDOG1_SWR_SHIFT            16u

#define PCC_WDOG1_SWR_WIDTH            1u

#define PCC_WDOG1_SWR(x)               (((uint32_t)(((uint32_t)(x))<<PCC_WDOG1_SWR_SHIFT))&PCC_WDOG1_SWR_MASK)

/* WDOG1 Reg Mask */

#define PCC_WDOG1_MASK                 0x00010000u



/* TRGSEL4 Bit Fields */

#define PCC_TRGSEL4_CGC_MASK           0x800000u

#define PCC_TRGSEL4_CGC_SHIFT          23u

#define PCC_TRGSEL4_CGC_WIDTH          1u

#define PCC_TRGSEL4_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_TRGSEL4_CGC_SHIFT))&PCC_TRGSEL4_CGC_MASK)

#define PCC_TRGSEL4_SWR_MASK           0x10000u

#define PCC_TRGSEL4_SWR_SHIFT          16u

#define PCC_TRGSEL4_SWR_WIDTH          1u

#define PCC_TRGSEL4_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_TRGSEL4_SWR_SHIFT))&PCC_TRGSEL4_SWR_MASK)

/* TRGSEL4 Reg Mask */

#define PCC_TRGSEL4_MASK               0x00810000u



/* TRGSEL5 Bit Fields */

#define PCC_TRGSEL5_CGC_MASK           0x800000u

#define PCC_TRGSEL5_CGC_SHIFT          23u

#define PCC_TRGSEL5_CGC_WIDTH          1u

#define PCC_TRGSEL5_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_TRGSEL5_CGC_SHIFT))&PCC_TRGSEL5_CGC_MASK)

#define PCC_TRGSEL5_SWR_MASK           0x10000u

#define PCC_TRGSEL5_SWR_SHIFT          16u

#define PCC_TRGSEL5_SWR_WIDTH          1u

#define PCC_TRGSEL5_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_TRGSEL5_SWR_SHIFT))&PCC_TRGSEL5_SWR_MASK)

/* TRGSEL5 Reg Mask */

#define PCC_TRGSEL5_MASK               0x00810000u



/* FCSPI3 Bit Fields */

#define PCC_FCSPI3_CGC_MASK            0x800000u

#define PCC_FCSPI3_CGC_SHIFT           23u

#define PCC_FCSPI3_CGC_WIDTH           1u

#define PCC_FCSPI3_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI3_CGC_SHIFT))&PCC_FCSPI3_CGC_MASK)

#define PCC_FCSPI3_SEL_MASK            0x700000u

#define PCC_FCSPI3_SEL_SHIFT           20u

#define PCC_FCSPI3_SEL_WIDTH           3u

#define PCC_FCSPI3_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI3_SEL_SHIFT))&PCC_FCSPI3_SEL_MASK)

#define PCC_FCSPI3_SWR_MASK            0x10000u

#define PCC_FCSPI3_SWR_SHIFT           16u

#define PCC_FCSPI3_SWR_WIDTH           1u

#define PCC_FCSPI3_SWR(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI3_SWR_SHIFT))&PCC_FCSPI3_SWR_MASK)

/* FCSPI3 Reg Mask */

#define PCC_FCSPI3_MASK                0x00F10000u



/* FCSPI4 Bit Fields */

#define PCC_FCSPI4_CGC_MASK            0x800000u

#define PCC_FCSPI4_CGC_SHIFT           23u

#define PCC_FCSPI4_CGC_WIDTH           1u

#define PCC_FCSPI4_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI4_CGC_SHIFT))&PCC_FCSPI4_CGC_MASK)

#define PCC_FCSPI4_SEL_MASK            0x700000u

#define PCC_FCSPI4_SEL_SHIFT           20u

#define PCC_FCSPI4_SEL_WIDTH           3u

#define PCC_FCSPI4_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI4_SEL_SHIFT))&PCC_FCSPI4_SEL_MASK)

#define PCC_FCSPI4_SWR_MASK            0x10000u

#define PCC_FCSPI4_SWR_SHIFT           16u

#define PCC_FCSPI4_SWR_WIDTH           1u

#define PCC_FCSPI4_SWR(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI4_SWR_SHIFT))&PCC_FCSPI4_SWR_MASK)

/* FCSPI4 Reg Mask */

#define PCC_FCSPI4_MASK                0x00F10000u



/* FCSPI5 Bit Fields */

#define PCC_FCSPI5_CGC_MASK            0x800000u

#define PCC_FCSPI5_CGC_SHIFT           23u

#define PCC_FCSPI5_CGC_WIDTH           1u

#define PCC_FCSPI5_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI5_CGC_SHIFT))&PCC_FCSPI5_CGC_MASK)

#define PCC_FCSPI5_SEL_MASK            0x700000u

#define PCC_FCSPI5_SEL_SHIFT           20u

#define PCC_FCSPI5_SEL_WIDTH           3u

#define PCC_FCSPI5_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI5_SEL_SHIFT))&PCC_FCSPI5_SEL_MASK)

#define PCC_FCSPI5_SWR_MASK            0x10000u

#define PCC_FCSPI5_SWR_SHIFT           16u

#define PCC_FCSPI5_SWR_WIDTH           1u

#define PCC_FCSPI5_SWR(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI5_SWR_SHIFT))&PCC_FCSPI5_SWR_MASK)

/* FCSPI5 Reg Mask */

#define PCC_FCSPI5_MASK                0x00F10000u



/* FTU4 Bit Fields */

#define PCC_FTU4_CGC_MASK              0x800000u

#define PCC_FTU4_CGC_SHIFT             23u

#define PCC_FTU4_CGC_WIDTH             1u

#define PCC_FTU4_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU4_CGC_SHIFT))&PCC_FTU4_CGC_MASK)

#define PCC_FTU4_SEL_MASK              0x700000u

#define PCC_FTU4_SEL_SHIFT             20u

#define PCC_FTU4_SEL_WIDTH             3u

#define PCC_FTU4_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU4_SEL_SHIFT))&PCC_FTU4_SEL_MASK)

#define PCC_FTU4_SWR_MASK              0x10000u

#define PCC_FTU4_SWR_SHIFT             16u

#define PCC_FTU4_SWR_WIDTH             1u

#define PCC_FTU4_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU4_SWR_SHIFT))&PCC_FTU4_SWR_MASK)

/* FTU4 Reg Mask */

#define PCC_FTU4_MASK                  0x00F10000u



/* FTU5 Bit Fields */

#define PCC_FTU5_CGC_MASK              0x800000u

#define PCC_FTU5_CGC_SHIFT             23u

#define PCC_FTU5_CGC_WIDTH             1u

#define PCC_FTU5_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU5_CGC_SHIFT))&PCC_FTU5_CGC_MASK)

#define PCC_FTU5_SEL_MASK              0x700000u

#define PCC_FTU5_SEL_SHIFT             20u

#define PCC_FTU5_SEL_WIDTH             3u

#define PCC_FTU5_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU5_SEL_SHIFT))&PCC_FTU5_SEL_MASK)

#define PCC_FTU5_SWR_MASK              0x10000u

#define PCC_FTU5_SWR_SHIFT             16u

#define PCC_FTU5_SWR_WIDTH             1u

#define PCC_FTU5_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU5_SWR_SHIFT))&PCC_FTU5_SWR_MASK)

/* FTU5 Reg Mask */

#define PCC_FTU5_MASK                  0x00F10000u



/* FTU6 Bit Fields */

#define PCC_FTU6_CGC_MASK              0x800000u

#define PCC_FTU6_CGC_SHIFT             23u

#define PCC_FTU6_CGC_WIDTH             1u

#define PCC_FTU6_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU6_CGC_SHIFT))&PCC_FTU6_CGC_MASK)

#define PCC_FTU6_SEL_MASK              0x700000u

#define PCC_FTU6_SEL_SHIFT             20u

#define PCC_FTU6_SEL_WIDTH             3u

#define PCC_FTU6_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU6_SEL_SHIFT))&PCC_FTU6_SEL_MASK)

#define PCC_FTU6_SWR_MASK              0x10000u

#define PCC_FTU6_SWR_SHIFT             16u

#define PCC_FTU6_SWR_WIDTH             1u

#define PCC_FTU6_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU6_SWR_SHIFT))&PCC_FTU6_SWR_MASK)

/* FTU6 Reg Mask */

#define PCC_FTU6_MASK                  0x00F10000u



/* FTU7 Bit Fields */

#define PCC_FTU7_CGC_MASK              0x800000u

#define PCC_FTU7_CGC_SHIFT             23u

#define PCC_FTU7_CGC_WIDTH             1u

#define PCC_FTU7_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU7_CGC_SHIFT))&PCC_FTU7_CGC_MASK)

#define PCC_FTU7_SEL_MASK              0x700000u

#define PCC_FTU7_SEL_SHIFT             20u

#define PCC_FTU7_SEL_WIDTH             3u

#define PCC_FTU7_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU7_SEL_SHIFT))&PCC_FTU7_SEL_MASK)

#define PCC_FTU7_SWR_MASK              0x10000u

#define PCC_FTU7_SWR_SHIFT             16u

#define PCC_FTU7_SWR_WIDTH             1u

#define PCC_FTU7_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU7_SWR_SHIFT))&PCC_FTU7_SWR_MASK)

/* FTU7 Reg Mask */

#define PCC_FTU7_MASK                  0x00F10000u



/* FCIIC1 Bit Fields */

#define PCC_FCIIC1_CGC_MASK            0x800000u

#define PCC_FCIIC1_CGC_SHIFT           23u

#define PCC_FCIIC1_CGC_WIDTH           1u

#define PCC_FCIIC1_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCIIC1_CGC_SHIFT))&PCC_FCIIC1_CGC_MASK)

#define PCC_FCIIC1_SEL_MASK            0x700000u

#define PCC_FCIIC1_SEL_SHIFT           20u

#define PCC_FCIIC1_SEL_WIDTH           3u

#define PCC_FCIIC1_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCIIC1_SEL_SHIFT))&PCC_FCIIC1_SEL_MASK)

#define PCC_FCIIC1_SWR_MASK            0x10000u

#define PCC_FCIIC1_SWR_SHIFT           16u

#define PCC_FCIIC1_SWR_WIDTH           1u

#define PCC_FCIIC1_SWR(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCIIC1_SWR_SHIFT))&PCC_FCIIC1_SWR_MASK)

/* FCIIC1 Reg Mask */

#define PCC_FCIIC1_MASK                0x00F10000u



/* FCUART4 Bit Fields */

#define PCC_FCUART4_CGC_MASK           0x800000u

#define PCC_FCUART4_CGC_SHIFT          23u

#define PCC_FCUART4_CGC_WIDTH          1u

#define PCC_FCUART4_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART4_CGC_SHIFT))&PCC_FCUART4_CGC_MASK)

#define PCC_FCUART4_SEL_MASK           0x700000u

#define PCC_FCUART4_SEL_SHIFT          20u

#define PCC_FCUART4_SEL_WIDTH          3u

#define PCC_FCUART4_SEL(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART4_SEL_SHIFT))&PCC_FCUART4_SEL_MASK)

#define PCC_FCUART4_SWR_MASK           0x10000u

#define PCC_FCUART4_SWR_SHIFT          16u

#define PCC_FCUART4_SWR_WIDTH          1u

#define PCC_FCUART4_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART4_SWR_SHIFT))&PCC_FCUART4_SWR_MASK)

/* FCUART4 Reg Mask */

#define PCC_FCUART4_MASK               0x00F10000u



/* FCUART5 Bit Fields */

#define PCC_FCUART5_CGC_MASK           0x800000u

#define PCC_FCUART5_CGC_SHIFT          23u

#define PCC_FCUART5_CGC_WIDTH          1u

#define PCC_FCUART5_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART5_CGC_SHIFT))&PCC_FCUART5_CGC_MASK)

#define PCC_FCUART5_SEL_MASK           0x700000u

#define PCC_FCUART5_SEL_SHIFT          20u

#define PCC_FCUART5_SEL_WIDTH          3u

#define PCC_FCUART5_SEL(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART5_SEL_SHIFT))&PCC_FCUART5_SEL_MASK)

#define PCC_FCUART5_SWR_MASK           0x10000u

#define PCC_FCUART5_SWR_SHIFT          16u

#define PCC_FCUART5_SWR_WIDTH          1u

#define PCC_FCUART5_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART5_SWR_SHIFT))&PCC_FCUART5_SWR_MASK)

/* FCUART5 Reg Mask */

#define PCC_FCUART5_MASK               0x00F10000u



/* FCUART6 Bit Fields */

#define PCC_FCUART6_CGC_MASK           0x800000u

#define PCC_FCUART6_CGC_SHIFT          23u

#define PCC_FCUART6_CGC_WIDTH          1u

#define PCC_FCUART6_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART6_CGC_SHIFT))&PCC_FCUART6_CGC_MASK)

#define PCC_FCUART6_SEL_MASK           0x700000u

#define PCC_FCUART6_SEL_SHIFT          20u

#define PCC_FCUART6_SEL_WIDTH          3u

#define PCC_FCUART6_SEL(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART6_SEL_SHIFT))&PCC_FCUART6_SEL_MASK)

#define PCC_FCUART6_SWR_MASK           0x10000u

#define PCC_FCUART6_SWR_SHIFT          16u

#define PCC_FCUART6_SWR_WIDTH          1u

#define PCC_FCUART6_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART6_SWR_SHIFT))&PCC_FCUART6_SWR_MASK)

/* FCUART6 Reg Mask */

#define PCC_FCUART6_MASK               0x00F10000u



/* FCUART7 Bit Fields */

#define PCC_FCUART7_CGC_MASK           0x800000u

#define PCC_FCUART7_CGC_SHIFT          23u

#define PCC_FCUART7_CGC_WIDTH          1u

#define PCC_FCUART7_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART7_CGC_SHIFT))&PCC_FCUART7_CGC_MASK)

#define PCC_FCUART7_SEL_MASK           0x700000u

#define PCC_FCUART7_SEL_SHIFT          20u

#define PCC_FCUART7_SEL_WIDTH          3u

#define PCC_FCUART7_SEL(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART7_SEL_SHIFT))&PCC_FCUART7_SEL_MASK)

#define PCC_FCUART7_SWR_MASK           0x10000u

#define PCC_FCUART7_SWR_SHIFT          16u

#define PCC_FCUART7_SWR_WIDTH          1u

#define PCC_FCUART7_SWR(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART7_SWR_SHIFT))&PCC_FCUART7_SWR_MASK)

/* FCUART7 Reg Mask */

#define PCC_FCUART7_MASK               0x00F10000u



/* MSC0 Bit Fields */

#define PCC_MSC0_CGC_MASK              0x800000u

#define PCC_MSC0_CGC_SHIFT             23u

#define PCC_MSC0_CGC_WIDTH             1u

#define PCC_MSC0_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_MSC0_CGC_SHIFT))&PCC_MSC0_CGC_MASK)

#define PCC_MSC0_SEL_MASK              0x700000u

#define PCC_MSC0_SEL_SHIFT             20u

#define PCC_MSC0_SEL_WIDTH             3u

#define PCC_MSC0_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_MSC0_SEL_SHIFT))&PCC_MSC0_SEL_MASK)

#define PCC_MSC0_SWR_MASK              0x10000u

#define PCC_MSC0_SWR_SHIFT             16u

#define PCC_MSC0_SWR_WIDTH             1u

#define PCC_MSC0_SWR(x)                (((uint32_t)(((uint32_t)(x))<<PCC_MSC0_SWR_SHIFT))&PCC_MSC0_SWR_MASK)

#define PCC_MSC0_DIV_MASK              0x7u

#define PCC_MSC0_DIV_SHIFT             0u

#define PCC_MSC0_DIV_WIDTH             3u

#define PCC_MSC0_DIV(x)                (((uint32_t)(((uint32_t)(x))<<PCC_MSC0_DIV_SHIFT))&PCC_MSC0_DIV_MASK)

/* MSC0 Reg Mask */

#define PCC_MSC0_MASK                  0x00F10007u



/* FLEXCAN2 Bit Fields */

#define PCC_FLEXCAN2_CGC_MASK          0x800000u

#define PCC_FLEXCAN2_CGC_SHIFT         23u

#define PCC_FLEXCAN2_CGC_WIDTH         1u

#define PCC_FLEXCAN2_CGC(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN2_CGC_SHIFT))&PCC_FLEXCAN2_CGC_MASK)

#define PCC_FLEXCAN2_SEL_MASK          0x700000u

#define PCC_FLEXCAN2_SEL_SHIFT         20u

#define PCC_FLEXCAN2_SEL_WIDTH         3u

#define PCC_FLEXCAN2_SEL(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN2_SEL_SHIFT))&PCC_FLEXCAN2_SEL_MASK)

#define PCC_FLEXCAN2_SWR_MASK          0x10000u

#define PCC_FLEXCAN2_SWR_SHIFT         16u

#define PCC_FLEXCAN2_SWR_WIDTH         1u

#define PCC_FLEXCAN2_SWR(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN2_SWR_SHIFT))&PCC_FLEXCAN2_SWR_MASK)

#define PCC_FLEXCAN2_DIV_MASK          0x7u

#define PCC_FLEXCAN2_DIV_SHIFT         0u

#define PCC_FLEXCAN2_DIV_WIDTH         3u

#define PCC_FLEXCAN2_DIV(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN2_DIV_SHIFT))&PCC_FLEXCAN2_DIV_MASK)

/* FLEXCAN2 Reg Mask */

#define PCC_FLEXCAN2_MASK              0x00F10007u



/* FLEXCAN3 Bit Fields */

#define PCC_FLEXCAN3_CGC_MASK          0x800000u

#define PCC_FLEXCAN3_CGC_SHIFT         23u

#define PCC_FLEXCAN3_CGC_WIDTH         1u

#define PCC_FLEXCAN3_CGC(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN3_CGC_SHIFT))&PCC_FLEXCAN3_CGC_MASK)

#define PCC_FLEXCAN3_SEL_MASK          0x700000u

#define PCC_FLEXCAN3_SEL_SHIFT         20u

#define PCC_FLEXCAN3_SEL_WIDTH         3u

#define PCC_FLEXCAN3_SEL(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN3_SEL_SHIFT))&PCC_FLEXCAN3_SEL_MASK)

#define PCC_FLEXCAN3_SWR_MASK          0x10000u

#define PCC_FLEXCAN3_SWR_SHIFT         16u

#define PCC_FLEXCAN3_SWR_WIDTH         1u

#define PCC_FLEXCAN3_SWR(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN3_SWR_SHIFT))&PCC_FLEXCAN3_SWR_MASK)

#define PCC_FLEXCAN3_DIV_MASK          0x7u

#define PCC_FLEXCAN3_DIV_SHIFT         0u

#define PCC_FLEXCAN3_DIV_WIDTH         3u

#define PCC_FLEXCAN3_DIV(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN3_DIV_SHIFT))&PCC_FLEXCAN3_DIV_MASK)

/* FLEXCAN3 Reg Mask */

#define PCC_FLEXCAN3_MASK              0x00F10007u





/*!

 * @}

 */ /* end of group PCC_Register_Masks */



/*!

 * @}

 */ /* end of group PCC_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
