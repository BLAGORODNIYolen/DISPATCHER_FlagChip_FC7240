#ifndef _FC7240_TPU_H_NU_Tztufn35_REGS_H_
#define _FC7240_TPU_H_NU_Tztufn35_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- TPU_H Peripheral Access Layer

   ---------------------------------------------------------------------------- */

#define TPU_H_CH_COUNT                32

/*!

 * @addtogroup TPU_H_Peripheral_Access_Layer TPU_H Peripheral Access Layer

 * @{

 */



/** TPU_H - Size of Registers Arrays */



/** TPU_H - Register Layout Typedef */



typedef struct {



       uint8_t  RESERVED_0[16];

  __I  uint32_t GCR_VSR                       ; /* Global Control Region -Visible Status Register, offset: 0x10 */

  __I  uint32_t GCR_VIR                       ; /* Global Control Region - Visible Input Status Register, offset: 0x14 */

  __I  uint32_t GCR_VOR                       ; /* Global Control Region - Visible Output Status Register, offset: 0x18 */

  __I  uint32_t GCR_VOBR                      ; /* Global Control Region - Visible Output Enable Status Register, offset: 0x1C */

  __I  uint32_t GCR_VM1R                      ; /* Global Control Region - Visible MRL1 Register, offset: 0x20 */

  __I  uint32_t GCR_VM2R                      ; /* Global Control Region -Visible MRL2 Register, offset: 0x24 */

  __I  uint32_t GCR_VT1R                      ; /* Global Control Region - Visible TDL1 Register, offset: 0x28 */

  __I  uint32_t GCR_VT2R                      ; /* Global Control Region - Visible TDL2 Register, offset: 0x2C */

  __I  uint32_t GCR_EM1R                      ; /* Global Control Region - Visible Event by MRL1 Register, offset: 0x30 */

  __I  uint32_t GCR_EM2R                      ; /* Global Control Region - Visible Event by MRL2 Register, offset: 0x34 */

  __I  uint32_t GCR_ET1R                      ; /* Global Control Region - Visible Event by TDL1 Register, offset: 0x38 */

  __I  uint32_t GCR_ET2R                      ; /* Global Control Region - Visible Event by TDL2 Register, offset: 0x3C */

  __I  uint32_t GCR_VHSR                      ; /* Global Control Region - Visible Host Acknowledge Register, offset: 0x40 */

       uint8_t  RESERVED_1[188];

  __I  uint32_t TBR_CR                        ; /* Time Bases Region - Control Register, offset: 0x100 */

  __IO uint32_t TBR_T1R                       ; /* Time Base Region - TCR1 Value Register, offset: 0x104 */

  __IO uint32_t TBR_T2R                       ; /* Time Base Region - TCR2 Value Register, offset: 0x108 */

       uint8_t  RESERVED_2[4];

  __I  uint32_t TBR_TPR                       ; /* Time Base Region - Tooth Program Register, offset: 0x110 */

  __IO uint32_t TBR_TRR                       ; /* Time Base Region - Tick Rate Register, offset: 0x114 */

  __IO uint32_t TBR_T1MR                      ; /* Time Base Region - TCR1 Maximum Register, offset: 0x118 */

  __IO uint32_t TBR_T2MR                      ; /* Time Base Region - TCR2 Maximum Register, offset: 0x11C */

       uint8_t  RESERVED_3[1760];
  struct{                                    /* offset: 0x800, array step: 0x40 */
  __IO uint32_t CR                        ; /* Channel N Control Register, offset: 0x800 */
  __I  uint32_t SR                        ; /* Channel N Status Register, offset: 0x804 */
  __IO uint32_t SCR                       ; /* Channel N Status Control Register, offset: 0x808 */
  __I  uint32_t EFR                       ; /* Channel N Event and Flag Register, offset: 0x80c */
       uint8_t  RESERVED_4[48];
  }  CH[TPU_H_CH_COUNT];

} TPU_H_Type, *TPU_H_MemMapPtr;



/** Number of instances of the TPU_H module. */

#define TPU_H_INSTANCE_COUNT                     (1u)



/* TPU_H - Peripheral instance base addresses */

/** Peripheral TPU_H base address */

#define TPU_H_BASE                               (0x40445000u)

/** Peripheral TPU_H base pointer */

#define TPU_H                                    ((TPU_H_Type *)TPU_H_BASE)

/** Array initializer of TPU_H peripheral base addresses */

#define TPU_H_BASE_ADDRS                         {TPU_H_BASE}

/** Array initializer of TPU_H peripheral base pointers */

#define TPU_H_BASE_PTRS                          {TPU_H}

// need fill by yourself

///** Number of interrupt vector arrays for the TPU_H module. */

//#define TPU_H_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the TPU_H module. */

//#define TPU_H_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the TPU_H peripheral type */

//#define TPU_H_IRQS                               {TPU_H_IRQn}





/* ----------------------------------------------------------------------------

   -- TPU_H Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup TPU_H_Register_Masks TPU_H Register Masks

 * @{

 */



/* GCR_VSR Bit Fields */

#define TPU_H_GCR_VSR_SR_MASK          0xFFFFFFFFu

#define TPU_H_GCR_VSR_SR_SHIFT         0u

#define TPU_H_GCR_VSR_SR_WIDTH         32u

#define TPU_H_GCR_VSR_SR(x)            (((uint32_t)(((uint32_t)(x))<<TPU_H_GCR_VSR_SR_SHIFT))&TPU_H_GCR_VSR_SR_MASK)

/* GCR_VSR Reg Mask */

#define TPU_H_GCR_VSR_MASK             0xFFFFFFFFu



/* GCR_VIR Bit Fields */

#define TPU_H_GCR_VIR_PSTI_MASK        0xFFFFFFFFu

#define TPU_H_GCR_VIR_PSTI_SHIFT       0u

#define TPU_H_GCR_VIR_PSTI_WIDTH       32u

#define TPU_H_GCR_VIR_PSTI(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_GCR_VIR_PSTI_SHIFT))&TPU_H_GCR_VIR_PSTI_MASK)

/* GCR_VIR Reg Mask */

#define TPU_H_GCR_VIR_MASK             0xFFFFFFFFu



/* GCR_VOR Bit Fields */

#define TPU_H_GCR_VOR_PSTO_MASK        0xFFFFFFFFu

#define TPU_H_GCR_VOR_PSTO_SHIFT       0u

#define TPU_H_GCR_VOR_PSTO_WIDTH       32u

#define TPU_H_GCR_VOR_PSTO(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_GCR_VOR_PSTO_SHIFT))&TPU_H_GCR_VOR_PSTO_MASK)

/* GCR_VOR Reg Mask */

#define TPU_H_GCR_VOR_MASK             0xFFFFFFFFu



/* GCR_VOBR Bit Fields */

#define TPU_H_GCR_VOBR_PSTOE_MASK      0xFFFFFFFFu

#define TPU_H_GCR_VOBR_PSTOE_SHIFT     0u

#define TPU_H_GCR_VOBR_PSTOE_WIDTH     32u

#define TPU_H_GCR_VOBR_PSTOE(x)        (((uint32_t)(((uint32_t)(x))<<TPU_H_GCR_VOBR_PSTOE_SHIFT))&TPU_H_GCR_VOBR_PSTOE_MASK)

/* GCR_VOBR Reg Mask */

#define TPU_H_GCR_VOBR_MASK            0xFFFFFFFFu



/* GCR_VM1R Bit Fields */

#define TPU_H_GCR_VM1R_M1R_MASK        0xFFFFFFFFu

#define TPU_H_GCR_VM1R_M1R_SHIFT       0u

#define TPU_H_GCR_VM1R_M1R_WIDTH       32u

#define TPU_H_GCR_VM1R_M1R(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_GCR_VM1R_M1R_SHIFT))&TPU_H_GCR_VM1R_M1R_MASK)

/* GCR_VM1R Reg Mask */

#define TPU_H_GCR_VM1R_MASK            0xFFFFFFFFu



/* GCR_VM2R Bit Fields */

#define TPU_H_GCR_VM2R_M2R_MASK        0xFFFFFFFFu

#define TPU_H_GCR_VM2R_M2R_SHIFT       0u

#define TPU_H_GCR_VM2R_M2R_WIDTH       32u

#define TPU_H_GCR_VM2R_M2R(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_GCR_VM2R_M2R_SHIFT))&TPU_H_GCR_VM2R_M2R_MASK)

/* GCR_VM2R Reg Mask */

#define TPU_H_GCR_VM2R_MASK            0xFFFFFFFFu



/* GCR_VT1R Bit Fields */

#define TPU_H_GCR_VT1R_T1R_MASK        0xFFFFFFFFu

#define TPU_H_GCR_VT1R_T1R_SHIFT       0u

#define TPU_H_GCR_VT1R_T1R_WIDTH       32u

#define TPU_H_GCR_VT1R_T1R(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_GCR_VT1R_T1R_SHIFT))&TPU_H_GCR_VT1R_T1R_MASK)

/* GCR_VT1R Reg Mask */

#define TPU_H_GCR_VT1R_MASK            0xFFFFFFFFu



/* GCR_VT2R Bit Fields */

#define TPU_H_GCR_VT2R_T2R_MASK        0xFFFFFFFFu

#define TPU_H_GCR_VT2R_T2R_SHIFT       0u

#define TPU_H_GCR_VT2R_T2R_WIDTH       32u

#define TPU_H_GCR_VT2R_T2R(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_GCR_VT2R_T2R_SHIFT))&TPU_H_GCR_VT2R_T2R_MASK)

/* GCR_VT2R Reg Mask */

#define TPU_H_GCR_VT2R_MASK            0xFFFFFFFFu



/* GCR_EM1R Bit Fields */

#define TPU_H_GCR_EM1R_EM1R_MASK       0xFFFFFFFFu

#define TPU_H_GCR_EM1R_EM1R_SHIFT      0u

#define TPU_H_GCR_EM1R_EM1R_WIDTH      32u

#define TPU_H_GCR_EM1R_EM1R(x)         (((uint32_t)(((uint32_t)(x))<<TPU_H_GCR_EM1R_EM1R_SHIFT))&TPU_H_GCR_EM1R_EM1R_MASK)

/* GCR_EM1R Reg Mask */

#define TPU_H_GCR_EM1R_MASK            0xFFFFFFFFu



/* GCR_EM2R Bit Fields */

#define TPU_H_GCR_EM2R_EM2R_MASK       0xFFFFFFFFu

#define TPU_H_GCR_EM2R_EM2R_SHIFT      0u

#define TPU_H_GCR_EM2R_EM2R_WIDTH      32u

#define TPU_H_GCR_EM2R_EM2R(x)         (((uint32_t)(((uint32_t)(x))<<TPU_H_GCR_EM2R_EM2R_SHIFT))&TPU_H_GCR_EM2R_EM2R_MASK)

/* GCR_EM2R Reg Mask */

#define TPU_H_GCR_EM2R_MASK            0xFFFFFFFFu



/* GCR_ET1R Bit Fields */

#define TPU_H_GCR_ET1R_ET1R_MASK       0xFFFFFFFFu

#define TPU_H_GCR_ET1R_ET1R_SHIFT      0u

#define TPU_H_GCR_ET1R_ET1R_WIDTH      32u

#define TPU_H_GCR_ET1R_ET1R(x)         (((uint32_t)(((uint32_t)(x))<<TPU_H_GCR_ET1R_ET1R_SHIFT))&TPU_H_GCR_ET1R_ET1R_MASK)

/* GCR_ET1R Reg Mask */

#define TPU_H_GCR_ET1R_MASK            0xFFFFFFFFu



/* GCR_ET2R Bit Fields */

#define TPU_H_GCR_ET2R_ET2R_MASK       0xFFFFFFFFu

#define TPU_H_GCR_ET2R_ET2R_SHIFT      0u

#define TPU_H_GCR_ET2R_ET2R_WIDTH      32u

#define TPU_H_GCR_ET2R_ET2R(x)         (((uint32_t)(((uint32_t)(x))<<TPU_H_GCR_ET2R_ET2R_SHIFT))&TPU_H_GCR_ET2R_ET2R_MASK)

/* GCR_ET2R Reg Mask */

#define TPU_H_GCR_ET2R_MASK            0xFFFFFFFFu



/* GCR_VHSR Bit Fields */

#define TPU_H_GCR_VHSR_HAS_MASK        0xFFFFFFFFu

#define TPU_H_GCR_VHSR_HAS_SHIFT       0u

#define TPU_H_GCR_VHSR_HAS_WIDTH       32u

#define TPU_H_GCR_VHSR_HAS(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_GCR_VHSR_HAS_SHIFT))&TPU_H_GCR_VHSR_HAS_MASK)

/* GCR_VHSR Reg Mask */

#define TPU_H_GCR_VHSR_MASK            0xFFFFFFFFu



/* TBR_CR Bit Fields */

#define TPU_H_TBR_CR_TCR1P_MASK        0xFF000000u

#define TPU_H_TBR_CR_TCR1P_SHIFT       24u

#define TPU_H_TBR_CR_TCR1P_WIDTH       8u

#define TPU_H_TBR_CR_TCR1P(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_CR_TCR1P_SHIFT))&TPU_H_TBR_CR_TCR1P_MASK)

#define TPU_H_TBR_CR_TCR1CTL_MASK      0x70000u

#define TPU_H_TBR_CR_TCR1CTL_SHIFT     16u

#define TPU_H_TBR_CR_TCR1CTL_WIDTH     3u

#define TPU_H_TBR_CR_TCR1CTL(x)        (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_CR_TCR1CTL_SHIFT))&TPU_H_TBR_CR_TCR1CTL_MASK)

#define TPU_H_TBR_CR_TCR2P_MASK        0xFC00u

#define TPU_H_TBR_CR_TCR2P_SHIFT       10u

#define TPU_H_TBR_CR_TCR2P_WIDTH       6u

#define TPU_H_TBR_CR_TCR2P(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_CR_TCR2P_SHIFT))&TPU_H_TBR_CR_TCR2P_MASK)

#define TPU_H_TBR_CR_ATGC_MASK         0x80u

#define TPU_H_TBR_CR_ATGC_SHIFT        7u

#define TPU_H_TBR_CR_ATGC_WIDTH        1u

#define TPU_H_TBR_CR_ATGC(x)           (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_CR_ATGC_SHIFT))&TPU_H_TBR_CR_ATGC_MASK)

#define TPU_H_TBR_CR_AM_MASK           0x60u

#define TPU_H_TBR_CR_AM_SHIFT          5u

#define TPU_H_TBR_CR_AM_WIDTH          2u

#define TPU_H_TBR_CR_AM(x)             (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_CR_AM_SHIFT))&TPU_H_TBR_CR_AM_MASK)

#define TPU_H_TBR_CR_TCRCF_MASK        0x18u

#define TPU_H_TBR_CR_TCRCF_SHIFT       3u

#define TPU_H_TBR_CR_TCRCF_WIDTH       2u

#define TPU_H_TBR_CR_TCRCF(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_CR_TCRCF_SHIFT))&TPU_H_TBR_CR_TCRCF_MASK)

#define TPU_H_TBR_CR_TCR2CTL_MASK      0x7u

#define TPU_H_TBR_CR_TCR2CTL_SHIFT     0u

#define TPU_H_TBR_CR_TCR2CTL_WIDTH     3u

#define TPU_H_TBR_CR_TCR2CTL(x)        (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_CR_TCR2CTL_SHIFT))&TPU_H_TBR_CR_TCR2CTL_MASK)

/* TBR_CR Reg Mask */

#define TPU_H_TBR_CR_MASK              0xFF07FCFFu



/* TBR_T1R Bit Fields */

#define TPU_H_TBR_T1R_TCR1_MASK        0xFFFFFFu

#define TPU_H_TBR_T1R_TCR1_SHIFT       0u

#define TPU_H_TBR_T1R_TCR1_WIDTH       24u

#define TPU_H_TBR_T1R_TCR1(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_T1R_TCR1_SHIFT))&TPU_H_TBR_T1R_TCR1_MASK)

/* TBR_T1R Reg Mask */

#define TPU_H_TBR_T1R_MASK             0x00FFFFFFu



/* TBR_T2R Bit Fields */

#define TPU_H_TBR_T2R_TCR2_MASK        0xFFFFFFu

#define TPU_H_TBR_T2R_TCR2_SHIFT       0u

#define TPU_H_TBR_T2R_TCR2_WIDTH       24u

#define TPU_H_TBR_T2R_TCR2(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_T2R_TCR2_SHIFT))&TPU_H_TBR_T2R_TCR2_MASK)

/* TBR_T2R Reg Mask */

#define TPU_H_TBR_T2R_MASK             0x00FFFFFFu



/* TBR_TPR Bit Fields */

#define TPU_H_TBR_TPR_LAST_MASK        0x8000u

#define TPU_H_TBR_TPR_LAST_SHIFT       15u

#define TPU_H_TBR_TPR_LAST_WIDTH       1u

#define TPU_H_TBR_TPR_LAST(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_TPR_LAST_SHIFT))&TPU_H_TBR_TPR_LAST_MASK)

#define TPU_H_TBR_TPR_MISSCNT_MASK     0x6000u

#define TPU_H_TBR_TPR_MISSCNT_SHIFT    13u

#define TPU_H_TBR_TPR_MISSCNT_WIDTH    2u

#define TPU_H_TBR_TPR_MISSCNT(x)       (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_TPR_MISSCNT_SHIFT))&TPU_H_TBR_TPR_MISSCNT_MASK)

#define TPU_H_TBR_TPR_IPH_MASK         0x1000u

#define TPU_H_TBR_TPR_IPH_SHIFT        12u

#define TPU_H_TBR_TPR_IPH_WIDTH        1u

#define TPU_H_TBR_TPR_IPH(x)           (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_TPR_IPH_SHIFT))&TPU_H_TBR_TPR_IPH_MASK)

#define TPU_H_TBR_TPR_HOLD_MASK        0x800u

#define TPU_H_TBR_TPR_HOLD_SHIFT       11u

#define TPU_H_TBR_TPR_HOLD_WIDTH       1u

#define TPU_H_TBR_TPR_HOLD(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_TPR_HOLD_SHIFT))&TPU_H_TBR_TPR_HOLD_MASK)

#define TPU_H_TBR_TPR_TPR10_MASK       0x400u

#define TPU_H_TBR_TPR_TPR10_SHIFT      10u

#define TPU_H_TBR_TPR_TPR10_WIDTH      1u

#define TPU_H_TBR_TPR_TPR10(x)         (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_TPR_TPR10_SHIFT))&TPU_H_TBR_TPR_TPR10_MASK)

#define TPU_H_TBR_TPR_TICKS_MASK       0x3FFu

#define TPU_H_TBR_TPR_TICKS_SHIFT      0u

#define TPU_H_TBR_TPR_TICKS_WIDTH      10u

#define TPU_H_TBR_TPR_TICKS(x)         (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_TPR_TICKS_SHIFT))&TPU_H_TBR_TPR_TICKS_MASK)

/* TBR_TPR Reg Mask */

#define TPU_H_TBR_TPR_MASK             0x0000FFFFu



/* TBR_TRR Bit Fields */

#define TPU_H_TBR_TRR_INTEGER_MASK     0xFFFE00u

#define TPU_H_TBR_TRR_INTEGER_SHIFT    9u

#define TPU_H_TBR_TRR_INTEGER_WIDTH    15u

#define TPU_H_TBR_TRR_INTEGER(x)       (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_TRR_INTEGER_SHIFT))&TPU_H_TBR_TRR_INTEGER_MASK)

#define TPU_H_TBR_TRR_FRACTION_MASK    0x1FFu

#define TPU_H_TBR_TRR_FRACTION_SHIFT   0u

#define TPU_H_TBR_TRR_FRACTION_WIDTH   9u

#define TPU_H_TBR_TRR_FRACTION(x)      (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_TRR_FRACTION_SHIFT))&TPU_H_TBR_TRR_FRACTION_MASK)

/* TBR_TRR Reg Mask */

#define TPU_H_TBR_TRR_MASK             0x00FFFFFFu



/* TBR_T1MR Bit Fields */

#define TPU_H_TBR_T1MR_OVF_MASK        0x80000000u

#define TPU_H_TBR_T1MR_OVF_SHIFT       31u

#define TPU_H_TBR_T1MR_OVF_WIDTH       1u

#define TPU_H_TBR_T1MR_OVF(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_T1MR_OVF_SHIFT))&TPU_H_TBR_T1MR_OVF_MASK)

#define TPU_H_TBR_T1MR_IRQ_EN_MASK     0x8000000u

#define TPU_H_TBR_T1MR_IRQ_EN_SHIFT    27u

#define TPU_H_TBR_T1MR_IRQ_EN_WIDTH    1u

#define TPU_H_TBR_T1MR_IRQ_EN(x)       (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_T1MR_IRQ_EN_SHIFT))&TPU_H_TBR_T1MR_IRQ_EN_MASK)

#define TPU_H_TBR_T1MR_MAX_MASK        0xFFFFFFu

#define TPU_H_TBR_T1MR_MAX_SHIFT       0u

#define TPU_H_TBR_T1MR_MAX_WIDTH       24u

#define TPU_H_TBR_T1MR_MAX(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_T1MR_MAX_SHIFT))&TPU_H_TBR_T1MR_MAX_MASK)

/* TBR_T1MR Reg Mask */

#define TPU_H_TBR_T1MR_MASK            0x88FFFFFFu



/* TBR_T2MR Bit Fields */

#define TPU_H_TBR_T2MR_OVF_MASK        0x80000000u

#define TPU_H_TBR_T2MR_OVF_SHIFT       31u

#define TPU_H_TBR_T2MR_OVF_WIDTH       1u

#define TPU_H_TBR_T2MR_OVF(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_T2MR_OVF_SHIFT))&TPU_H_TBR_T2MR_OVF_MASK)

#define TPU_H_TBR_T2MR_IRQ_EN_MASK     0x8000000u

#define TPU_H_TBR_T2MR_IRQ_EN_SHIFT    27u

#define TPU_H_TBR_T2MR_IRQ_EN_WIDTH    1u

#define TPU_H_TBR_T2MR_IRQ_EN(x)       (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_T2MR_IRQ_EN_SHIFT))&TPU_H_TBR_T2MR_IRQ_EN_MASK)

#define TPU_H_TBR_T2MR_MAX_MASK        0xFFFFFFu

#define TPU_H_TBR_T2MR_MAX_SHIFT       0u

#define TPU_H_TBR_T2MR_MAX_WIDTH       24u

#define TPU_H_TBR_T2MR_MAX(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_TBR_T2MR_MAX_SHIFT))&TPU_H_TBR_T2MR_MAX_MASK)

/* TBR_T2MR Reg Mask */

#define TPU_H_TBR_T2MR_MASK            0x88FFFFFFu



/* CHn_CR Bit Fields */

#define TPU_H_CHn_CR_CHAE_MASK         0x8000u

#define TPU_H_CHn_CR_CHAE_SHIFT        15u

#define TPU_H_CHn_CR_CHAE_WIDTH        1u

#define TPU_H_CHn_CR_CHAE(x)           (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_CR_CHAE_SHIFT))&TPU_H_CHn_CR_CHAE_MASK)

#define TPU_H_CHn_CR_CHDE_MASK         0x4000u

#define TPU_H_CHn_CR_CHDE_SHIFT        14u

#define TPU_H_CHn_CR_CHDE_WIDTH        1u

#define TPU_H_CHn_CR_CHDE(x)           (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_CR_CHDE_SHIFT))&TPU_H_CHn_CR_CHDE_MASK)

#define TPU_H_CHn_CR_CHEE_MASK         0x2000u

#define TPU_H_CHn_CR_CHEE_SHIFT        13u

#define TPU_H_CHn_CR_CHEE_WIDTH        1u

#define TPU_H_CHn_CR_CHEE(x)           (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_CR_CHEE_SHIFT))&TPU_H_CHn_CR_CHEE_MASK)

#define TPU_H_CHn_CR_CTC_MASK          0x1E00u

#define TPU_H_CHn_CR_CTC_SHIFT         9u

#define TPU_H_CHn_CR_CTC_WIDTH         4u

#define TPU_H_CHn_CR_CTC(x)            (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_CR_CTC_SHIFT))&TPU_H_CHn_CR_CTC_MASK)

#define TPU_H_CHn_CR_CDFD_MASK         0x100u

#define TPU_H_CHn_CR_CDFD_SHIFT        8u

#define TPU_H_CHn_CR_CDFD_WIDTH        1u

#define TPU_H_CHn_CR_CDFD(x)           (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_CR_CDFD_SHIFT))&TPU_H_CHn_CR_CDFD_MASK)

#define TPU_H_CHn_CR_CHSR_MASK         0x7u

#define TPU_H_CHn_CR_CHSR_SHIFT        0u

#define TPU_H_CHn_CR_CHSR_WIDTH        3u

#define TPU_H_CHn_CR_CHSR(x)           (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_CR_CHSR_SHIFT))&TPU_H_CHn_CR_CHSR_MASK)

/* CH0_CR Reg Mask */

#define TPU_H_CHn_CR_MASK              0x0000FF07u



/* CHn_SR Bit Fields */

#define TPU_H_CHn_SR_CIS_MASK          0x80000000u

#define TPU_H_CHn_SR_CIS_SHIFT         31u

#define TPU_H_CHn_SR_CIS_WIDTH         1u

#define TPU_H_CHn_SR_CIS(x)            (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_SR_CIS_SHIFT))&TPU_H_CHn_SR_CIS_MASK)

#define TPU_H_CHn_SR_CHRS_MASK         0x1000000u

#define TPU_H_CHn_SR_CHRS_SHIFT        24u

#define TPU_H_CHn_SR_CHRS_WIDTH        1u

#define TPU_H_CHn_SR_CHRS(x)           (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_SR_CHRS_SHIFT))&TPU_H_CHn_SR_CHRS_MASK)

#define TPU_H_CHn_SR_CHRI_MASK         0x70000u

#define TPU_H_CHn_SR_CHRI_SHIFT        16u

#define TPU_H_CHn_SR_CHRI_WIDTH        3u

#define TPU_H_CHn_SR_CHRI(x)           (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_SR_CHRI_SHIFT))&TPU_H_CHn_SR_CHRI_MASK)

#define TPU_H_CHn_SR_CEIS_MASK         0x8000u

#define TPU_H_CHn_SR_CEIS_SHIFT        15u

#define TPU_H_CHn_SR_CEIS_WIDTH        1u

#define TPU_H_CHn_SR_CEIS(x)           (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_SR_CEIS_SHIFT))&TPU_H_CHn_SR_CEIS_MASK)

#define TPU_H_CHn_SR_CHDS_MASK         0x4000u

#define TPU_H_CHn_SR_CHDS_SHIFT        14u

#define TPU_H_CHn_SR_CHDS_WIDTH        1u

#define TPU_H_CHn_SR_CHDS(x)           (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_SR_CHDS_SHIFT))&TPU_H_CHn_SR_CHDS_MASK)

#define TPU_H_CHn_SR_CTS_MASK          0x1000u

#define TPU_H_CHn_SR_CTS_SHIFT         12u

#define TPU_H_CHn_SR_CTS_WIDTH         1u

#define TPU_H_CHn_SR_CTS(x)            (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_SR_CTS_SHIFT))&TPU_H_CHn_SR_CTS_MASK)

#define TPU_H_CHn_SR_CHAS_MASK         0x100u

#define TPU_H_CHn_SR_CHAS_SHIFT        8u

#define TPU_H_CHn_SR_CHAS_WIDTH        1u

#define TPU_H_CHn_SR_CHAS(x)           (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_SR_CHAS_SHIFT))&TPU_H_CHn_SR_CHAS_MASK)

/* CH0_SR Reg Mask */

#define TPU_H_CHn_SR_MASK              0x8107D100u



/* CHn_SCR Bit Fields */

#define TPU_H_CHn_SCR_CEIC_MASK        0x8000u

#define TPU_H_CHn_SCR_CEIC_SHIFT       15u

#define TPU_H_CHn_SCR_CEIC_WIDTH       1u

#define TPU_H_CHn_SCR_CEIC(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_SCR_CEIC_SHIFT))&TPU_H_CHn_SCR_CEIC_MASK)

#define TPU_H_CHn_SCR_CHAC_MASK        0x100u

#define TPU_H_CHn_SCR_CHAC_SHIFT       8u

#define TPU_H_CHn_SCR_CHAC_WIDTH       1u

#define TPU_H_CHn_SCR_CHAC(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_SCR_CHAC_SHIFT))&TPU_H_CHn_SCR_CHAC_MASK)

#define TPU_H_CHn_SCR_CHRT_MASK        0x1u

#define TPU_H_CHn_SCR_CHRT_SHIFT       0u

#define TPU_H_CHn_SCR_CHRT_WIDTH       1u

#define TPU_H_CHn_SCR_CHRT(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_SCR_CHRT_SHIFT))&TPU_H_CHn_SCR_CHRT_MASK)

/* CH0_SCR Reg Mask */

#define TPU_H_CHn_SCR_MASK             0x00008101u



/* CHn_EFR Bit Fields */

#define TPU_H_CHn_EFR_CSR_MASK         0x80000000u

#define TPU_H_CHn_EFR_CSR_SHIFT        31u

#define TPU_H_CHn_EFR_CSR_WIDTH        1u

#define TPU_H_CHn_EFR_CSR(x)           (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_EFR_CSR_SHIFT))&TPU_H_CHn_EFR_CSR_MASK)

#define TPU_H_CHn_EFR_CHSR_MASK        0x40000000u

#define TPU_H_CHn_EFR_CHSR_SHIFT       30u

#define TPU_H_CHn_EFR_CHSR_WIDTH       1u

#define TPU_H_CHn_EFR_CHSR(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_EFR_CHSR_SHIFT))&TPU_H_CHn_EFR_CHSR_MASK)

#define TPU_H_CHn_EFR_EMRL1_MASK       0x200u

#define TPU_H_CHn_EFR_EMRL1_SHIFT      9u

#define TPU_H_CHn_EFR_EMRL1_WIDTH      1u

#define TPU_H_CHn_EFR_EMRL1(x)         (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_EFR_EMRL1_SHIFT))&TPU_H_CHn_EFR_EMRL1_MASK)

#define TPU_H_CHn_EFR_EMRL2_MASK       0x100u

#define TPU_H_CHn_EFR_EMRL2_SHIFT      8u

#define TPU_H_CHn_EFR_EMRL2_WIDTH      1u

#define TPU_H_CHn_EFR_EMRL2(x)         (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_EFR_EMRL2_SHIFT))&TPU_H_CHn_EFR_EMRL2_MASK)

#define TPU_H_CHn_EFR_ETDL1_MASK       0x80u

#define TPU_H_CHn_EFR_ETDL1_SHIFT      7u

#define TPU_H_CHn_EFR_ETDL1_WIDTH      1u

#define TPU_H_CHn_EFR_ETDL1(x)         (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_EFR_ETDL1_SHIFT))&TPU_H_CHn_EFR_ETDL1_MASK)

#define TPU_H_CHn_EFR_ETDL2_MASK       0x40u

#define TPU_H_CHn_EFR_ETDL2_SHIFT      6u

#define TPU_H_CHn_EFR_ETDL2_WIDTH      1u

#define TPU_H_CHn_EFR_ETDL2(x)         (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_EFR_ETDL2_SHIFT))&TPU_H_CHn_EFR_ETDL2_MASK)

#define TPU_H_CHn_EFR_MRLE1_MASK       0x20u

#define TPU_H_CHn_EFR_MRLE1_SHIFT      5u

#define TPU_H_CHn_EFR_MRLE1_WIDTH      1u

#define TPU_H_CHn_EFR_MRLE1(x)         (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_EFR_MRLE1_SHIFT))&TPU_H_CHn_EFR_MRLE1_MASK)

#define TPU_H_CHn_EFR_MRLE2_MASK       0x10u

#define TPU_H_CHn_EFR_MRLE2_SHIFT      4u

#define TPU_H_CHn_EFR_MRLE2_WIDTH      1u

#define TPU_H_CHn_EFR_MRLE2(x)         (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_EFR_MRLE2_SHIFT))&TPU_H_CHn_EFR_MRLE2_MASK)

#define TPU_H_CHn_EFR_MRL1_MASK        0x8u

#define TPU_H_CHn_EFR_MRL1_SHIFT       3u

#define TPU_H_CHn_EFR_MRL1_WIDTH       1u

#define TPU_H_CHn_EFR_MRL1(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_EFR_MRL1_SHIFT))&TPU_H_CHn_EFR_MRL1_MASK)

#define TPU_H_CHn_EFR_MRL2_MASK        0x4u

#define TPU_H_CHn_EFR_MRL2_SHIFT       2u

#define TPU_H_CHn_EFR_MRL2_WIDTH       1u

#define TPU_H_CHn_EFR_MRL2(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_EFR_MRL2_SHIFT))&TPU_H_CHn_EFR_MRL2_MASK)

#define TPU_H_CHn_EFR_TDL1_MASK        0x2u

#define TPU_H_CHn_EFR_TDL1_SHIFT       1u

#define TPU_H_CHn_EFR_TDL1_WIDTH       1u

#define TPU_H_CHn_EFR_TDL1(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_EFR_TDL1_SHIFT))&TPU_H_CHn_EFR_TDL1_MASK)

#define TPU_H_CHn_EFR_TDL2_MASK        0x1u

#define TPU_H_CHn_EFR_TDL2_SHIFT       0u

#define TPU_H_CHn_EFR_TDL2_WIDTH       1u

#define TPU_H_CHn_EFR_TDL2(x)          (((uint32_t)(((uint32_t)(x))<<TPU_H_CHn_EFR_TDL2_SHIFT))&TPU_H_CHn_EFR_TDL2_MASK)

/* CH0_EFR Reg Mask */

#define TPU_H_CHn_EFR_MASK             0xC00003FFu





/*!

 * @}

 */ /* end of group TPU_H_Register_Masks */



/*!

 * @}

 */ /* end of group TPU_H_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
