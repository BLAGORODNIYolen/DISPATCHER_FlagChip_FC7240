#ifndef _FC7240_ERM_NU_Tztufn21_REGS_H_
#define _FC7240_ERM_NU_Tztufn21_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- ERM Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup ERM_Peripheral_Access_Layer ERM Peripheral Access Layer

 * @{

 */



/** ERM - Size of Registers Arrays */



/** ERM - Register Layout Typedef */



typedef struct {



  __IO uint32_t CR0                           ; /* Configuration Register 0, offset: 0x0 */

  __IO uint32_t CR1                           ; /* Configuration Register 1, offset: 0x4 */

  __IO uint32_t CR2                           ; /* Configuration Register 2, offset: 0x8 */

  __IO uint32_t CR3                           ; /* Configuration Register 3, offset: 0xC */

  __IO uint32_t SR0                           ; /* Status Register 0, offset: 0x10 */

  __IO uint32_t SR1                           ; /* Status Register 1, offset: 0x14 */

  __IO uint32_t SR2                           ; /* Status Register 2, offset: 0x18 */

  __IO uint32_t SR3                           ; /* Status Register 3, offset: 0x1C */

       uint8_t  RESERVED_0[224];

  __I  uint32_t EAR0                          ; /* Error Address Register, offset: 0x100 */

       uint8_t  RESERVED_1[12];

  __I  uint32_t EAR1                          ; /* Error Address Register, offset: 0x110 */

       uint8_t  RESERVED_2[12];

  __I  uint32_t EAR2                          ; /* Error Address Register, offset: 0x120 */

       uint8_t  RESERVED_3[12];

  __I  uint32_t EAR3                          ; /* Error Address Register, offset: 0x130 */

       uint8_t  RESERVED_4[12];

  __I  uint32_t EAR4                          ; /* Error Address Register, offset: 0x140 */

       uint8_t  RESERVED_5[12];

  __I  uint32_t EAR5                          ; /* Error Address Register, offset: 0x150 */

       uint8_t  RESERVED_6[12];

  __I  uint32_t EAR6                          ; /* Error Address Register, offset: 0x160 */

       uint8_t  RESERVED_7[12];

  __I  uint32_t EAR7                          ; /* Error Address Register, offset: 0x170 */

       uint8_t  RESERVED_8[12];

  __I  uint32_t EAR8                          ; /* Error Address Register, offset: 0x180 */

       uint8_t  RESERVED_9[12];

  __I  uint32_t EAR9                          ; /* Error Address Register, offset: 0x190 */

       uint8_t  RESERVED_10[12];

  __I  uint32_t EAR10                         ; /* Error Address Register, offset: 0x1a0 */

       uint8_t  RESERVED_11[12];

  __I  uint32_t EAR11                         ; /* Error Address Register, offset: 0x1b0 */

       uint8_t  RESERVED_12[12];

  __I  uint32_t EAR12                         ; /* Error Address Register, offset: 0x1c0 */

       uint8_t  RESERVED_13[12];

  __I  uint32_t EAR13                         ; /* Error Address Register, offset: 0x1d0 */

       uint8_t  RESERVED_14[12];

  __I  uint32_t EAR14                         ; /* Error Address Register, offset: 0x1e0 */

       uint8_t  RESERVED_15[12];

  __I  uint32_t EAR15                         ; /* Error Address Register, offset: 0x1f0 */

       uint8_t  RESERVED_16[12];

  __I  uint32_t EAR16                         ; /* Error Address Register, offset: 0x200 */

       uint8_t  RESERVED_17[12];

  __I  uint32_t EAR17                         ; /* Error Address Register, offset: 0x210 */

       uint8_t  RESERVED_18[12];

  __I  uint32_t EAR18                         ; /* Error Address Register, offset: 0x220 */

       uint8_t  RESERVED_19[12];

  __I  uint32_t EAR19                         ; /* Error Address Register, offset: 0x230 */

       uint8_t  RESERVED_20[12];

  __I  uint32_t EAR20                         ; /* Error Address Register, offset: 0x240 */

       uint8_t  RESERVED_21[12];

  __I  uint32_t EAR21                         ; /* Error Address Register, offset: 0x250 */

       uint8_t  RESERVED_22[12];

  __I  uint32_t EAR22                         ; /* Error Address Register, offset: 0x260 */

       uint8_t  RESERVED_23[12];

  __I  uint32_t EAR23                         ; /* Error Address Register, offset: 0x270 */

       uint8_t  RESERVED_24[12];

  __I  uint32_t EAR24                         ; /* Error Address Register, offset: 0x280 */

       uint8_t  RESERVED_25[12];

  __I  uint32_t EAR25                         ; /* Error Address Register, offset: 0x290 */

       uint8_t  RESERVED_26[12];

  __I  uint32_t EAR26                         ; /* Error Address Register, offset: 0x2a0 */

       uint8_t  RESERVED_27[12];

  __I  uint32_t EAR27                         ; /* Error Address Register, offset: 0x2b0 */



} ERM_Type, *ERM_MemMapPtr;



/** Number of instances of the ERM module. */

#define ERM_INSTANCE_COUNT                       (1u)



/* ERM - Peripheral instance base addresses */

/** Peripheral ERM base address */

#define ERM_BASE                                 (0x40018000u)

/** Peripheral ERM base pointer */

#define ERM                                      ((ERM_Type *)ERM_BASE)

/** Array initializer of ERM peripheral base addresses */

#define ERM_BASE_ADDRS                           {ERM_BASE}

/** Array initializer of ERM peripheral base pointers */

#define ERM_BASE_PTRS                            {ERM}

// need fill by yourself

///** Number of interrupt vector arrays for the ERM module. */

//#define ERM_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the ERM module. */

//#define ERM_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the ERM peripheral type */

//#define ERM_IRQS                                 {ERM_IRQn}





/* ----------------------------------------------------------------------------

   -- ERM Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup ERM_Register_Masks ERM Register Masks

 * @{

 */



/* CR0 Bit Fields */

#define ERM_CR0_ESCIE0_MASK            0x80000000u

#define ERM_CR0_ESCIE0_SHIFT           31u

#define ERM_CR0_ESCIE0_WIDTH           1u

#define ERM_CR0_ESCIE0(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ESCIE0_SHIFT))&ERM_CR0_ESCIE0_MASK)

#define ERM_CR0_ENCIE0_MASK            0x40000000u

#define ERM_CR0_ENCIE0_SHIFT           30u

#define ERM_CR0_ENCIE0_WIDTH           1u

#define ERM_CR0_ENCIE0(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ENCIE0_SHIFT))&ERM_CR0_ENCIE0_MASK)

#define ERM_CR0_ESCIE1_MASK            0x8000000u

#define ERM_CR0_ESCIE1_SHIFT           27u

#define ERM_CR0_ESCIE1_WIDTH           1u

#define ERM_CR0_ESCIE1(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ESCIE1_SHIFT))&ERM_CR0_ESCIE1_MASK)

#define ERM_CR0_ENCIE1_MASK            0x4000000u

#define ERM_CR0_ENCIE1_SHIFT           26u

#define ERM_CR0_ENCIE1_WIDTH           1u

#define ERM_CR0_ENCIE1(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ENCIE1_SHIFT))&ERM_CR0_ENCIE1_MASK)

#define ERM_CR0_ESCIE2_MASK            0x800000u

#define ERM_CR0_ESCIE2_SHIFT           23u

#define ERM_CR0_ESCIE2_WIDTH           1u

#define ERM_CR0_ESCIE2(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ESCIE2_SHIFT))&ERM_CR0_ESCIE2_MASK)

#define ERM_CR0_ENCIE2_MASK            0x400000u

#define ERM_CR0_ENCIE2_SHIFT           22u

#define ERM_CR0_ENCIE2_WIDTH           1u

#define ERM_CR0_ENCIE2(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ENCIE2_SHIFT))&ERM_CR0_ENCIE2_MASK)

#define ERM_CR0_ESCIE3_MASK            0x80000u

#define ERM_CR0_ESCIE3_SHIFT           19u

#define ERM_CR0_ESCIE3_WIDTH           1u

#define ERM_CR0_ESCIE3(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ESCIE3_SHIFT))&ERM_CR0_ESCIE3_MASK)

#define ERM_CR0_ENCIE3_MASK            0x40000u

#define ERM_CR0_ENCIE3_SHIFT           18u

#define ERM_CR0_ENCIE3_WIDTH           1u

#define ERM_CR0_ENCIE3(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ENCIE3_SHIFT))&ERM_CR0_ENCIE3_MASK)

#define ERM_CR0_ESCIE4_MASK            0x8000u

#define ERM_CR0_ESCIE4_SHIFT           15u

#define ERM_CR0_ESCIE4_WIDTH           1u

#define ERM_CR0_ESCIE4(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ESCIE4_SHIFT))&ERM_CR0_ESCIE4_MASK)

#define ERM_CR0_ENCIE4_MASK            0x4000u

#define ERM_CR0_ENCIE4_SHIFT           14u

#define ERM_CR0_ENCIE4_WIDTH           1u

#define ERM_CR0_ENCIE4(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ENCIE4_SHIFT))&ERM_CR0_ENCIE4_MASK)

#define ERM_CR0_ESCIE5_MASK            0x800u

#define ERM_CR0_ESCIE5_SHIFT           11u

#define ERM_CR0_ESCIE5_WIDTH           1u

#define ERM_CR0_ESCIE5(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ESCIE5_SHIFT))&ERM_CR0_ESCIE5_MASK)

#define ERM_CR0_ENCIE5_MASK            0x400u

#define ERM_CR0_ENCIE5_SHIFT           10u

#define ERM_CR0_ENCIE5_WIDTH           1u

#define ERM_CR0_ENCIE5(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ENCIE5_SHIFT))&ERM_CR0_ENCIE5_MASK)

#define ERM_CR0_ESCIE6_MASK            0x80u

#define ERM_CR0_ESCIE6_SHIFT           7u

#define ERM_CR0_ESCIE6_WIDTH           1u

#define ERM_CR0_ESCIE6(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ESCIE6_SHIFT))&ERM_CR0_ESCIE6_MASK)

#define ERM_CR0_ENCIE6_MASK            0x40u

#define ERM_CR0_ENCIE6_SHIFT           6u

#define ERM_CR0_ENCIE6_WIDTH           1u

#define ERM_CR0_ENCIE6(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ENCIE6_SHIFT))&ERM_CR0_ENCIE6_MASK)

#define ERM_CR0_ESCIE7_MASK            0x8u

#define ERM_CR0_ESCIE7_SHIFT           3u

#define ERM_CR0_ESCIE7_WIDTH           1u

#define ERM_CR0_ESCIE7(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ESCIE7_SHIFT))&ERM_CR0_ESCIE7_MASK)

#define ERM_CR0_ENCIE7_MASK            0x4u

#define ERM_CR0_ENCIE7_SHIFT           2u

#define ERM_CR0_ENCIE7_WIDTH           1u

#define ERM_CR0_ENCIE7(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ENCIE7_SHIFT))&ERM_CR0_ENCIE7_MASK)

/* CR0 Reg Mask */

#define ERM_CR0_MASK                   0xCCCCCCCCu



/* CR1 Bit Fields */

#define ERM_CR1_ESCIE8_MASK            0x80000000u

#define ERM_CR1_ESCIE8_SHIFT           31u

#define ERM_CR1_ESCIE8_WIDTH           1u

#define ERM_CR1_ESCIE8(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ESCIE8_SHIFT))&ERM_CR1_ESCIE8_MASK)

#define ERM_CR1_ENCIE8_MASK            0x40000000u

#define ERM_CR1_ENCIE8_SHIFT           30u

#define ERM_CR1_ENCIE8_WIDTH           1u

#define ERM_CR1_ENCIE8(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ENCIE8_SHIFT))&ERM_CR1_ENCIE8_MASK)

#define ERM_CR1_ESCIE9_MASK            0x8000000u

#define ERM_CR1_ESCIE9_SHIFT           27u

#define ERM_CR1_ESCIE9_WIDTH           1u

#define ERM_CR1_ESCIE9(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ESCIE9_SHIFT))&ERM_CR1_ESCIE9_MASK)

#define ERM_CR1_ENCIE9_MASK            0x4000000u

#define ERM_CR1_ENCIE9_SHIFT           26u

#define ERM_CR1_ENCIE9_WIDTH           1u

#define ERM_CR1_ENCIE9(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ENCIE9_SHIFT))&ERM_CR1_ENCIE9_MASK)

#define ERM_CR1_ESCIE10_MASK           0x800000u

#define ERM_CR1_ESCIE10_SHIFT          23u

#define ERM_CR1_ESCIE10_WIDTH          1u

#define ERM_CR1_ESCIE10(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ESCIE10_SHIFT))&ERM_CR1_ESCIE10_MASK)

#define ERM_CR1_ENCIE10_MASK           0x400000u

#define ERM_CR1_ENCIE10_SHIFT          22u

#define ERM_CR1_ENCIE10_WIDTH          1u

#define ERM_CR1_ENCIE10(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ENCIE10_SHIFT))&ERM_CR1_ENCIE10_MASK)

#define ERM_CR1_ESCIE11_MASK           0x80000u

#define ERM_CR1_ESCIE11_SHIFT          19u

#define ERM_CR1_ESCIE11_WIDTH          1u

#define ERM_CR1_ESCIE11(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ESCIE11_SHIFT))&ERM_CR1_ESCIE11_MASK)

#define ERM_CR1_ENCIE11_MASK           0x40000u

#define ERM_CR1_ENCIE11_SHIFT          18u

#define ERM_CR1_ENCIE11_WIDTH          1u

#define ERM_CR1_ENCIE11(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ENCIE11_SHIFT))&ERM_CR1_ENCIE11_MASK)

#define ERM_CR1_ESCIE12_MASK           0x8000u

#define ERM_CR1_ESCIE12_SHIFT          15u

#define ERM_CR1_ESCIE12_WIDTH          1u

#define ERM_CR1_ESCIE12(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ESCIE12_SHIFT))&ERM_CR1_ESCIE12_MASK)

#define ERM_CR1_ENCIE12_MASK           0x4000u

#define ERM_CR1_ENCIE12_SHIFT          14u

#define ERM_CR1_ENCIE12_WIDTH          1u

#define ERM_CR1_ENCIE12(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ENCIE12_SHIFT))&ERM_CR1_ENCIE12_MASK)

#define ERM_CR1_ESCIE13_MASK           0x800u

#define ERM_CR1_ESCIE13_SHIFT          11u

#define ERM_CR1_ESCIE13_WIDTH          1u

#define ERM_CR1_ESCIE13(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ESCIE13_SHIFT))&ERM_CR1_ESCIE13_MASK)

#define ERM_CR1_ENCIE13_MASK           0x400u

#define ERM_CR1_ENCIE13_SHIFT          10u

#define ERM_CR1_ENCIE13_WIDTH          1u

#define ERM_CR1_ENCIE13(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ENCIE13_SHIFT))&ERM_CR1_ENCIE13_MASK)

#define ERM_CR1_ESCIE14_MASK           0x80u

#define ERM_CR1_ESCIE14_SHIFT          7u

#define ERM_CR1_ESCIE14_WIDTH          1u

#define ERM_CR1_ESCIE14(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ESCIE14_SHIFT))&ERM_CR1_ESCIE14_MASK)

#define ERM_CR1_ENCIE14_MASK           0x40u

#define ERM_CR1_ENCIE14_SHIFT          6u

#define ERM_CR1_ENCIE14_WIDTH          1u

#define ERM_CR1_ENCIE14(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ENCIE14_SHIFT))&ERM_CR1_ENCIE14_MASK)

#define ERM_CR1_ESCIE15_MASK           0x8u

#define ERM_CR1_ESCIE15_SHIFT          3u

#define ERM_CR1_ESCIE15_WIDTH          1u

#define ERM_CR1_ESCIE15(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ESCIE15_SHIFT))&ERM_CR1_ESCIE15_MASK)

#define ERM_CR1_ENCIE15_MASK           0x4u

#define ERM_CR1_ENCIE15_SHIFT          2u

#define ERM_CR1_ENCIE15_WIDTH          1u

#define ERM_CR1_ENCIE15(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR1_ENCIE15_SHIFT))&ERM_CR1_ENCIE15_MASK)

/* CR1 Reg Mask */

#define ERM_CR1_MASK                   0xCCCCCCCCu



/* CR2 Bit Fields */

#define ERM_CR2_ESCIE16_MASK           0x80000000u

#define ERM_CR2_ESCIE16_SHIFT          31u

#define ERM_CR2_ESCIE16_WIDTH          1u

#define ERM_CR2_ESCIE16(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ESCIE16_SHIFT))&ERM_CR2_ESCIE16_MASK)

#define ERM_CR2_ENCIE16_MASK           0x40000000u

#define ERM_CR2_ENCIE16_SHIFT          30u

#define ERM_CR2_ENCIE16_WIDTH          1u

#define ERM_CR2_ENCIE16(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ENCIE16_SHIFT))&ERM_CR2_ENCIE16_MASK)

#define ERM_CR2_ESCIE17_MASK           0x8000000u

#define ERM_CR2_ESCIE17_SHIFT          27u

#define ERM_CR2_ESCIE17_WIDTH          1u

#define ERM_CR2_ESCIE17(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ESCIE17_SHIFT))&ERM_CR2_ESCIE17_MASK)

#define ERM_CR2_ENCIE17_MASK           0x4000000u

#define ERM_CR2_ENCIE17_SHIFT          26u

#define ERM_CR2_ENCIE17_WIDTH          1u

#define ERM_CR2_ENCIE17(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ENCIE17_SHIFT))&ERM_CR2_ENCIE17_MASK)

#define ERM_CR2_ESCIE18_MASK           0x800000u

#define ERM_CR2_ESCIE18_SHIFT          23u

#define ERM_CR2_ESCIE18_WIDTH          1u

#define ERM_CR2_ESCIE18(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ESCIE18_SHIFT))&ERM_CR2_ESCIE18_MASK)

#define ERM_CR2_ENCIE18_MASK           0x400000u

#define ERM_CR2_ENCIE18_SHIFT          22u

#define ERM_CR2_ENCIE18_WIDTH          1u

#define ERM_CR2_ENCIE18(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ENCIE18_SHIFT))&ERM_CR2_ENCIE18_MASK)

#define ERM_CR2_ESCIE19_MASK           0x80000u

#define ERM_CR2_ESCIE19_SHIFT          19u

#define ERM_CR2_ESCIE19_WIDTH          1u

#define ERM_CR2_ESCIE19(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ESCIE19_SHIFT))&ERM_CR2_ESCIE19_MASK)

#define ERM_CR2_ENCIE19_MASK           0x40000u

#define ERM_CR2_ENCIE19_SHIFT          18u

#define ERM_CR2_ENCIE19_WIDTH          1u

#define ERM_CR2_ENCIE19(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ENCIE19_SHIFT))&ERM_CR2_ENCIE19_MASK)

#define ERM_CR2_ESCIE20_MASK           0x8000u

#define ERM_CR2_ESCIE20_SHIFT          15u

#define ERM_CR2_ESCIE20_WIDTH          1u

#define ERM_CR2_ESCIE20(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ESCIE20_SHIFT))&ERM_CR2_ESCIE20_MASK)

#define ERM_CR2_ENCIE20_MASK           0x4000u

#define ERM_CR2_ENCIE20_SHIFT          14u

#define ERM_CR2_ENCIE20_WIDTH          1u

#define ERM_CR2_ENCIE20(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ENCIE20_SHIFT))&ERM_CR2_ENCIE20_MASK)

#define ERM_CR2_ESCIE21_MASK           0x800u

#define ERM_CR2_ESCIE21_SHIFT          11u

#define ERM_CR2_ESCIE21_WIDTH          1u

#define ERM_CR2_ESCIE21(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ESCIE21_SHIFT))&ERM_CR2_ESCIE21_MASK)

#define ERM_CR2_ENCIE21_MASK           0x400u

#define ERM_CR2_ENCIE21_SHIFT          10u

#define ERM_CR2_ENCIE21_WIDTH          1u

#define ERM_CR2_ENCIE21(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ENCIE21_SHIFT))&ERM_CR2_ENCIE21_MASK)

#define ERM_CR2_ESCIE22_MASK           0x80u

#define ERM_CR2_ESCIE22_SHIFT          7u

#define ERM_CR2_ESCIE22_WIDTH          1u

#define ERM_CR2_ESCIE22(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ESCIE22_SHIFT))&ERM_CR2_ESCIE22_MASK)

#define ERM_CR2_ENCIE22_MASK           0x40u

#define ERM_CR2_ENCIE22_SHIFT          6u

#define ERM_CR2_ENCIE22_WIDTH          1u

#define ERM_CR2_ENCIE22(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ENCIE22_SHIFT))&ERM_CR2_ENCIE22_MASK)

#define ERM_CR2_ESCIE23_MASK           0x8u

#define ERM_CR2_ESCIE23_SHIFT          3u

#define ERM_CR2_ESCIE23_WIDTH          1u

#define ERM_CR2_ESCIE23(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ESCIE23_SHIFT))&ERM_CR2_ESCIE23_MASK)

#define ERM_CR2_ENCIE23_MASK           0x4u

#define ERM_CR2_ENCIE23_SHIFT          2u

#define ERM_CR2_ENCIE23_WIDTH          1u

#define ERM_CR2_ENCIE23(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR2_ENCIE23_SHIFT))&ERM_CR2_ENCIE23_MASK)

/* CR2 Reg Mask */

#define ERM_CR2_MASK                   0xCCCCCCCCu



/* CR3 Bit Fields */

#define ERM_CR3_ESCIE24_MASK           0x80000000u

#define ERM_CR3_ESCIE24_SHIFT          31u

#define ERM_CR3_ESCIE24_WIDTH          1u

#define ERM_CR3_ESCIE24(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ESCIE24_SHIFT))&ERM_CR3_ESCIE24_MASK)

#define ERM_CR3_ENCIE24_MASK           0x40000000u

#define ERM_CR3_ENCIE24_SHIFT          30u

#define ERM_CR3_ENCIE24_WIDTH          1u

#define ERM_CR3_ENCIE24(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ENCIE24_SHIFT))&ERM_CR3_ENCIE24_MASK)

#define ERM_CR3_ESCIE25_MASK           0x8000000u

#define ERM_CR3_ESCIE25_SHIFT          27u

#define ERM_CR3_ESCIE25_WIDTH          1u

#define ERM_CR3_ESCIE25(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ESCIE25_SHIFT))&ERM_CR3_ESCIE25_MASK)

#define ERM_CR3_ENCIE25_MASK           0x4000000u

#define ERM_CR3_ENCIE25_SHIFT          26u

#define ERM_CR3_ENCIE25_WIDTH          1u

#define ERM_CR3_ENCIE25(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ENCIE25_SHIFT))&ERM_CR3_ENCIE25_MASK)

#define ERM_CR3_ESCIE26_MASK           0x800000u

#define ERM_CR3_ESCIE26_SHIFT          23u

#define ERM_CR3_ESCIE26_WIDTH          1u

#define ERM_CR3_ESCIE26(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ESCIE26_SHIFT))&ERM_CR3_ESCIE26_MASK)

#define ERM_CR3_ENCIE26_MASK           0x400000u

#define ERM_CR3_ENCIE26_SHIFT          22u

#define ERM_CR3_ENCIE26_WIDTH          1u

#define ERM_CR3_ENCIE26(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ENCIE26_SHIFT))&ERM_CR3_ENCIE26_MASK)

#define ERM_CR3_ESCIE27_MASK           0x80000u

#define ERM_CR3_ESCIE27_SHIFT          19u

#define ERM_CR3_ESCIE27_WIDTH          1u

#define ERM_CR3_ESCIE27(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ESCIE27_SHIFT))&ERM_CR3_ESCIE27_MASK)

#define ERM_CR3_ENCIE27_MASK           0x40000u

#define ERM_CR3_ENCIE27_SHIFT          18u

#define ERM_CR3_ENCIE27_WIDTH          1u

#define ERM_CR3_ENCIE27(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ENCIE27_SHIFT))&ERM_CR3_ENCIE27_MASK)

#define ERM_CR3_ESCIE28_MASK           0x8000u

#define ERM_CR3_ESCIE28_SHIFT          15u

#define ERM_CR3_ESCIE28_WIDTH          1u

#define ERM_CR3_ESCIE28(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ESCIE28_SHIFT))&ERM_CR3_ESCIE28_MASK)

#define ERM_CR3_ENCIE28_MASK           0x4000u

#define ERM_CR3_ENCIE28_SHIFT          14u

#define ERM_CR3_ENCIE28_WIDTH          1u

#define ERM_CR3_ENCIE28(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ENCIE28_SHIFT))&ERM_CR3_ENCIE28_MASK)

#define ERM_CR3_ESCIE29_MASK           0x800u

#define ERM_CR3_ESCIE29_SHIFT          11u

#define ERM_CR3_ESCIE29_WIDTH          1u

#define ERM_CR3_ESCIE29(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ESCIE29_SHIFT))&ERM_CR3_ESCIE29_MASK)

#define ERM_CR3_ENCIE29_MASK           0x400u

#define ERM_CR3_ENCIE29_SHIFT          10u

#define ERM_CR3_ENCIE29_WIDTH          1u

#define ERM_CR3_ENCIE29(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ENCIE29_SHIFT))&ERM_CR3_ENCIE29_MASK)

#define ERM_CR3_ESCIE30_MASK           0x80u

#define ERM_CR3_ESCIE30_SHIFT          7u

#define ERM_CR3_ESCIE30_WIDTH          1u

#define ERM_CR3_ESCIE30(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ESCIE30_SHIFT))&ERM_CR3_ESCIE30_MASK)

#define ERM_CR3_ENCIE30_MASK           0x40u

#define ERM_CR3_ENCIE30_SHIFT          6u

#define ERM_CR3_ENCIE30_WIDTH          1u

#define ERM_CR3_ENCIE30(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ENCIE30_SHIFT))&ERM_CR3_ENCIE30_MASK)

#define ERM_CR3_ESCIE31_MASK           0x8u

#define ERM_CR3_ESCIE31_SHIFT          3u

#define ERM_CR3_ESCIE31_WIDTH          1u

#define ERM_CR3_ESCIE31(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ESCIE31_SHIFT))&ERM_CR3_ESCIE31_MASK)

#define ERM_CR3_ENCIE31_MASK           0x4u

#define ERM_CR3_ENCIE31_SHIFT          2u

#define ERM_CR3_ENCIE31_WIDTH          1u

#define ERM_CR3_ENCIE31(x)             (((uint32_t)(((uint32_t)(x))<<ERM_CR3_ENCIE31_SHIFT))&ERM_CR3_ENCIE31_MASK)

/* CR3 Reg Mask */

#define ERM_CR3_MASK                   0xCCCCCCCCu



/* SR0 Bit Fields */

#define ERM_SR0_SBC0_MASK              0x80000000u

#define ERM_SR0_SBC0_SHIFT             31u

#define ERM_SR0_SBC0_WIDTH             1u

#define ERM_SR0_SBC0(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_SBC0_SHIFT))&ERM_SR0_SBC0_MASK)

#define ERM_SR0_NCE0_MASK              0x40000000u

#define ERM_SR0_NCE0_SHIFT             30u

#define ERM_SR0_NCE0_WIDTH             1u

#define ERM_SR0_NCE0(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_NCE0_SHIFT))&ERM_SR0_NCE0_MASK)

#define ERM_SR0_SBC1_MASK              0x8000000u

#define ERM_SR0_SBC1_SHIFT             27u

#define ERM_SR0_SBC1_WIDTH             1u

#define ERM_SR0_SBC1(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_SBC1_SHIFT))&ERM_SR0_SBC1_MASK)

#define ERM_SR0_NCE1_MASK              0x4000000u

#define ERM_SR0_NCE1_SHIFT             26u

#define ERM_SR0_NCE1_WIDTH             1u

#define ERM_SR0_NCE1(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_NCE1_SHIFT))&ERM_SR0_NCE1_MASK)

#define ERM_SR0_SBC2_MASK              0x800000u

#define ERM_SR0_SBC2_SHIFT             23u

#define ERM_SR0_SBC2_WIDTH             1u

#define ERM_SR0_SBC2(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_SBC2_SHIFT))&ERM_SR0_SBC2_MASK)

#define ERM_SR0_NCE2_MASK              0x400000u

#define ERM_SR0_NCE2_SHIFT             22u

#define ERM_SR0_NCE2_WIDTH             1u

#define ERM_SR0_NCE2(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_NCE2_SHIFT))&ERM_SR0_NCE2_MASK)

#define ERM_SR0_SBC3_MASK              0x80000u

#define ERM_SR0_SBC3_SHIFT             19u

#define ERM_SR0_SBC3_WIDTH             1u

#define ERM_SR0_SBC3(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_SBC3_SHIFT))&ERM_SR0_SBC3_MASK)

#define ERM_SR0_NCE3_MASK              0x40000u

#define ERM_SR0_NCE3_SHIFT             18u

#define ERM_SR0_NCE3_WIDTH             1u

#define ERM_SR0_NCE3(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_NCE3_SHIFT))&ERM_SR0_NCE3_MASK)

#define ERM_SR0_SBC4_MASK              0x8000u

#define ERM_SR0_SBC4_SHIFT             15u

#define ERM_SR0_SBC4_WIDTH             1u

#define ERM_SR0_SBC4(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_SBC4_SHIFT))&ERM_SR0_SBC4_MASK)

#define ERM_SR0_NCE4_MASK              0x4000u

#define ERM_SR0_NCE4_SHIFT             14u

#define ERM_SR0_NCE4_WIDTH             1u

#define ERM_SR0_NCE4(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_NCE4_SHIFT))&ERM_SR0_NCE4_MASK)

#define ERM_SR0_SBC5_MASK              0x800u

#define ERM_SR0_SBC5_SHIFT             11u

#define ERM_SR0_SBC5_WIDTH             1u

#define ERM_SR0_SBC5(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_SBC5_SHIFT))&ERM_SR0_SBC5_MASK)

#define ERM_SR0_NCE5_MASK              0x400u

#define ERM_SR0_NCE5_SHIFT             10u

#define ERM_SR0_NCE5_WIDTH             1u

#define ERM_SR0_NCE5(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_NCE5_SHIFT))&ERM_SR0_NCE5_MASK)

#define ERM_SR0_SBC6_MASK              0x80u

#define ERM_SR0_SBC6_SHIFT             7u

#define ERM_SR0_SBC6_WIDTH             1u

#define ERM_SR0_SBC6(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_SBC6_SHIFT))&ERM_SR0_SBC6_MASK)

#define ERM_SR0_NCE6_MASK              0x40u

#define ERM_SR0_NCE6_SHIFT             6u

#define ERM_SR0_NCE6_WIDTH             1u

#define ERM_SR0_NCE6(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_NCE6_SHIFT))&ERM_SR0_NCE6_MASK)

#define ERM_SR0_SBC7_MASK              0x8u

#define ERM_SR0_SBC7_SHIFT             3u

#define ERM_SR0_SBC7_WIDTH             1u

#define ERM_SR0_SBC7(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_SBC7_SHIFT))&ERM_SR0_SBC7_MASK)

#define ERM_SR0_NCE7_MASK              0x4u

#define ERM_SR0_NCE7_SHIFT             2u

#define ERM_SR0_NCE7_WIDTH             1u

#define ERM_SR0_NCE7(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_NCE7_SHIFT))&ERM_SR0_NCE7_MASK)

/* SR0 Reg Mask */

#define ERM_SR0_MASK                   0xCCCCCCCCu



/* SR1 Bit Fields */

#define ERM_SR1_SBC8_MASK              0x80000000u

#define ERM_SR1_SBC8_SHIFT             31u

#define ERM_SR1_SBC8_WIDTH             1u

#define ERM_SR1_SBC8(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR1_SBC8_SHIFT))&ERM_SR1_SBC8_MASK)

#define ERM_SR1_NCE8_MASK              0x40000000u

#define ERM_SR1_NCE8_SHIFT             30u

#define ERM_SR1_NCE8_WIDTH             1u

#define ERM_SR1_NCE8(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR1_NCE8_SHIFT))&ERM_SR1_NCE8_MASK)

#define ERM_SR1_SBC9_MASK              0x8000000u

#define ERM_SR1_SBC9_SHIFT             27u

#define ERM_SR1_SBC9_WIDTH             1u

#define ERM_SR1_SBC9(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR1_SBC9_SHIFT))&ERM_SR1_SBC9_MASK)

#define ERM_SR1_NCE9_MASK              0x4000000u

#define ERM_SR1_NCE9_SHIFT             26u

#define ERM_SR1_NCE9_WIDTH             1u

#define ERM_SR1_NCE9(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR1_NCE9_SHIFT))&ERM_SR1_NCE9_MASK)

#define ERM_SR1_SBC10_MASK             0x800000u

#define ERM_SR1_SBC10_SHIFT            23u

#define ERM_SR1_SBC10_WIDTH            1u

#define ERM_SR1_SBC10(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR1_SBC10_SHIFT))&ERM_SR1_SBC10_MASK)

#define ERM_SR1_NCE10_MASK             0x400000u

#define ERM_SR1_NCE10_SHIFT            22u

#define ERM_SR1_NCE10_WIDTH            1u

#define ERM_SR1_NCE10(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR1_NCE10_SHIFT))&ERM_SR1_NCE10_MASK)

#define ERM_SR1_SBC11_MASK             0x80000u

#define ERM_SR1_SBC11_SHIFT            19u

#define ERM_SR1_SBC11_WIDTH            1u

#define ERM_SR1_SBC11(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR1_SBC11_SHIFT))&ERM_SR1_SBC11_MASK)

#define ERM_SR1_NCE11_MASK             0x40000u

#define ERM_SR1_NCE11_SHIFT            18u

#define ERM_SR1_NCE11_WIDTH            1u

#define ERM_SR1_NCE11(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR1_NCE11_SHIFT))&ERM_SR1_NCE11_MASK)

#define ERM_SR1_SBC12_MASK             0x8000u

#define ERM_SR1_SBC12_SHIFT            15u

#define ERM_SR1_SBC12_WIDTH            1u

#define ERM_SR1_SBC12(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR1_SBC12_SHIFT))&ERM_SR1_SBC12_MASK)

#define ERM_SR1_NCE12_MASK             0x4000u

#define ERM_SR1_NCE12_SHIFT            14u

#define ERM_SR1_NCE12_WIDTH            1u

#define ERM_SR1_NCE12(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR1_NCE12_SHIFT))&ERM_SR1_NCE12_MASK)

#define ERM_SR1_SBC13_MASK             0x800u

#define ERM_SR1_SBC13_SHIFT            11u

#define ERM_SR1_SBC13_WIDTH            1u

#define ERM_SR1_SBC13(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR1_SBC13_SHIFT))&ERM_SR1_SBC13_MASK)

#define ERM_SR1_NCE13_MASK             0x400u

#define ERM_SR1_NCE13_SHIFT            10u

#define ERM_SR1_NCE13_WIDTH            1u

#define ERM_SR1_NCE13(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR1_NCE13_SHIFT))&ERM_SR1_NCE13_MASK)

#define ERM_SR1_SBC14_MASK             0x80u

#define ERM_SR1_SBC14_SHIFT            7u

#define ERM_SR1_SBC14_WIDTH            1u

#define ERM_SR1_SBC14(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR1_SBC14_SHIFT))&ERM_SR1_SBC14_MASK)

#define ERM_SR1_NCE14_MASK             0x40u

#define ERM_SR1_NCE14_SHIFT            6u

#define ERM_SR1_NCE14_WIDTH            1u

#define ERM_SR1_NCE14(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR1_NCE14_SHIFT))&ERM_SR1_NCE14_MASK)

#define ERM_SR1_SBC15_MASK             0x8u

#define ERM_SR1_SBC15_SHIFT            3u

#define ERM_SR1_SBC15_WIDTH            1u

#define ERM_SR1_SBC15(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR1_SBC15_SHIFT))&ERM_SR1_SBC15_MASK)

#define ERM_SR1_NCE15_MASK             0x4u

#define ERM_SR1_NCE15_SHIFT            2u

#define ERM_SR1_NCE15_WIDTH            1u

#define ERM_SR1_NCE15(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR1_NCE15_SHIFT))&ERM_SR1_NCE15_MASK)

/* SR1 Reg Mask */

#define ERM_SR1_MASK                   0xCCCCCCCCu



/* SR2 Bit Fields */

#define ERM_SR2_SBC16_MASK             0x80000000u

#define ERM_SR2_SBC16_SHIFT            31u

#define ERM_SR2_SBC16_WIDTH            1u

#define ERM_SR2_SBC16(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_SBC16_SHIFT))&ERM_SR2_SBC16_MASK)

#define ERM_SR2_NCE16_MASK             0x40000000u

#define ERM_SR2_NCE16_SHIFT            30u

#define ERM_SR2_NCE16_WIDTH            1u

#define ERM_SR2_NCE16(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_NCE16_SHIFT))&ERM_SR2_NCE16_MASK)

#define ERM_SR2_SBC17_MASK             0x8000000u

#define ERM_SR2_SBC17_SHIFT            27u

#define ERM_SR2_SBC17_WIDTH            1u

#define ERM_SR2_SBC17(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_SBC17_SHIFT))&ERM_SR2_SBC17_MASK)

#define ERM_SR2_NCE17_MASK             0x4000000u

#define ERM_SR2_NCE17_SHIFT            26u

#define ERM_SR2_NCE17_WIDTH            1u

#define ERM_SR2_NCE17(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_NCE17_SHIFT))&ERM_SR2_NCE17_MASK)

#define ERM_SR2_SBC18_MASK             0x800000u

#define ERM_SR2_SBC18_SHIFT            23u

#define ERM_SR2_SBC18_WIDTH            1u

#define ERM_SR2_SBC18(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_SBC18_SHIFT))&ERM_SR2_SBC18_MASK)

#define ERM_SR2_NCE18_MASK             0x400000u

#define ERM_SR2_NCE18_SHIFT            22u

#define ERM_SR2_NCE18_WIDTH            1u

#define ERM_SR2_NCE18(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_NCE18_SHIFT))&ERM_SR2_NCE18_MASK)

#define ERM_SR2_SBC19_MASK             0x80000u

#define ERM_SR2_SBC19_SHIFT            19u

#define ERM_SR2_SBC19_WIDTH            1u

#define ERM_SR2_SBC19(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_SBC19_SHIFT))&ERM_SR2_SBC19_MASK)

#define ERM_SR2_NCE19_MASK             0x40000u

#define ERM_SR2_NCE19_SHIFT            18u

#define ERM_SR2_NCE19_WIDTH            1u

#define ERM_SR2_NCE19(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_NCE19_SHIFT))&ERM_SR2_NCE19_MASK)

#define ERM_SR2_SBC20_MASK             0x8000u

#define ERM_SR2_SBC20_SHIFT            15u

#define ERM_SR2_SBC20_WIDTH            1u

#define ERM_SR2_SBC20(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_SBC20_SHIFT))&ERM_SR2_SBC20_MASK)

#define ERM_SR2_NCE20_MASK             0x4000u

#define ERM_SR2_NCE20_SHIFT            14u

#define ERM_SR2_NCE20_WIDTH            1u

#define ERM_SR2_NCE20(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_NCE20_SHIFT))&ERM_SR2_NCE20_MASK)

#define ERM_SR2_SBC21_MASK             0x800u

#define ERM_SR2_SBC21_SHIFT            11u

#define ERM_SR2_SBC21_WIDTH            1u

#define ERM_SR2_SBC21(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_SBC21_SHIFT))&ERM_SR2_SBC21_MASK)

#define ERM_SR2_NCE21_MASK             0x400u

#define ERM_SR2_NCE21_SHIFT            10u

#define ERM_SR2_NCE21_WIDTH            1u

#define ERM_SR2_NCE21(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_NCE21_SHIFT))&ERM_SR2_NCE21_MASK)

#define ERM_SR2_SBC22_MASK             0x80u

#define ERM_SR2_SBC22_SHIFT            7u

#define ERM_SR2_SBC22_WIDTH            1u

#define ERM_SR2_SBC22(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_SBC22_SHIFT))&ERM_SR2_SBC22_MASK)

#define ERM_SR2_NCE22_MASK             0x40u

#define ERM_SR2_NCE22_SHIFT            6u

#define ERM_SR2_NCE22_WIDTH            1u

#define ERM_SR2_NCE22(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_NCE22_SHIFT))&ERM_SR2_NCE22_MASK)

#define ERM_SR2_SBC23_MASK             0x8u

#define ERM_SR2_SBC23_SHIFT            3u

#define ERM_SR2_SBC23_WIDTH            1u

#define ERM_SR2_SBC23(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_SBC23_SHIFT))&ERM_SR2_SBC23_MASK)

#define ERM_SR2_NCE23_MASK             0x4u

#define ERM_SR2_NCE23_SHIFT            2u

#define ERM_SR2_NCE23_WIDTH            1u

#define ERM_SR2_NCE23(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR2_NCE23_SHIFT))&ERM_SR2_NCE23_MASK)

/* SR2 Reg Mask */

#define ERM_SR2_MASK                   0xCCCCCCCCu



/* SR3 Bit Fields */

#define ERM_SR3_SBC24_MASK             0x80000000u

#define ERM_SR3_SBC24_SHIFT            31u

#define ERM_SR3_SBC24_WIDTH            1u

#define ERM_SR3_SBC24(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_SBC24_SHIFT))&ERM_SR3_SBC24_MASK)

#define ERM_SR3_NCE24_MASK             0x40000000u

#define ERM_SR3_NCE24_SHIFT            30u

#define ERM_SR3_NCE24_WIDTH            1u

#define ERM_SR3_NCE24(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_NCE24_SHIFT))&ERM_SR3_NCE24_MASK)

#define ERM_SR3_SBC25_MASK             0x8000000u

#define ERM_SR3_SBC25_SHIFT            27u

#define ERM_SR3_SBC25_WIDTH            1u

#define ERM_SR3_SBC25(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_SBC25_SHIFT))&ERM_SR3_SBC25_MASK)

#define ERM_SR3_NCE25_MASK             0x4000000u

#define ERM_SR3_NCE25_SHIFT            26u

#define ERM_SR3_NCE25_WIDTH            1u

#define ERM_SR3_NCE25(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_NCE25_SHIFT))&ERM_SR3_NCE25_MASK)

#define ERM_SR3_SBC26_MASK             0x800000u

#define ERM_SR3_SBC26_SHIFT            23u

#define ERM_SR3_SBC26_WIDTH            1u

#define ERM_SR3_SBC26(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_SBC26_SHIFT))&ERM_SR3_SBC26_MASK)

#define ERM_SR3_NCE26_MASK             0x400000u

#define ERM_SR3_NCE26_SHIFT            22u

#define ERM_SR3_NCE26_WIDTH            1u

#define ERM_SR3_NCE26(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_NCE26_SHIFT))&ERM_SR3_NCE26_MASK)

#define ERM_SR3_SBC27_MASK             0x80000u

#define ERM_SR3_SBC27_SHIFT            19u

#define ERM_SR3_SBC27_WIDTH            1u

#define ERM_SR3_SBC27(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_SBC27_SHIFT))&ERM_SR3_SBC27_MASK)

#define ERM_SR3_NCE27_MASK             0x40000u

#define ERM_SR3_NCE27_SHIFT            18u

#define ERM_SR3_NCE27_WIDTH            1u

#define ERM_SR3_NCE27(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_NCE27_SHIFT))&ERM_SR3_NCE27_MASK)

#define ERM_SR3_SBC28_MASK             0x8000u

#define ERM_SR3_SBC28_SHIFT            15u

#define ERM_SR3_SBC28_WIDTH            1u

#define ERM_SR3_SBC28(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_SBC28_SHIFT))&ERM_SR3_SBC28_MASK)

#define ERM_SR3_NCE28_MASK             0x4000u

#define ERM_SR3_NCE28_SHIFT            14u

#define ERM_SR3_NCE28_WIDTH            1u

#define ERM_SR3_NCE28(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_NCE28_SHIFT))&ERM_SR3_NCE28_MASK)

#define ERM_SR3_SBC29_MASK             0x800u

#define ERM_SR3_SBC29_SHIFT            11u

#define ERM_SR3_SBC29_WIDTH            1u

#define ERM_SR3_SBC29(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_SBC29_SHIFT))&ERM_SR3_SBC29_MASK)

#define ERM_SR3_NCE29_MASK             0x400u

#define ERM_SR3_NCE29_SHIFT            10u

#define ERM_SR3_NCE29_WIDTH            1u

#define ERM_SR3_NCE29(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_NCE29_SHIFT))&ERM_SR3_NCE29_MASK)

#define ERM_SR3_SBC30_MASK             0x80u

#define ERM_SR3_SBC30_SHIFT            7u

#define ERM_SR3_SBC30_WIDTH            1u

#define ERM_SR3_SBC30(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_SBC30_SHIFT))&ERM_SR3_SBC30_MASK)

#define ERM_SR3_NCE30_MASK             0x40u

#define ERM_SR3_NCE30_SHIFT            6u

#define ERM_SR3_NCE30_WIDTH            1u

#define ERM_SR3_NCE30(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_NCE30_SHIFT))&ERM_SR3_NCE30_MASK)

#define ERM_SR3_SBC31_MASK             0x8u

#define ERM_SR3_SBC31_SHIFT            3u

#define ERM_SR3_SBC31_WIDTH            1u

#define ERM_SR3_SBC31(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_SBC31_SHIFT))&ERM_SR3_SBC31_MASK)

#define ERM_SR3_NCE31_MASK             0x4u

#define ERM_SR3_NCE31_SHIFT            2u

#define ERM_SR3_NCE31_WIDTH            1u

#define ERM_SR3_NCE31(x)               (((uint32_t)(((uint32_t)(x))<<ERM_SR3_NCE31_SHIFT))&ERM_SR3_NCE31_MASK)

/* SR3 Reg Mask */

#define ERM_SR3_MASK                   0xCCCCCCCCu



/* EAR Bit Fields */

#define ERM_EAR_EAR_MASK               0xFFFFFFFFu

#define ERM_EAR_EAR_SHIFT              0u

#define ERM_EAR_EAR_WIDTH              32u

#define ERM_EAR_EAR(x)                 (((uint32_t)(((uint32_t)(x))<<ERM_EAR_EAR_SHIFT))&ERM_EAR_EAR_MASK)

/* EAR0 Reg Mask */

#define ERM_EAR_MASK                   0xFFFFFFFFu





/*!

 * @}

 */ /* end of group ERM_Register_Masks */



/*!

 * @}

 */ /* end of group ERM_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
