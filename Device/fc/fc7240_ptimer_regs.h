#ifndef _FC7240_PTIMER_NU_Tztufn31_REGS_H_
#define _FC7240_PTIMER_NU_Tztufn31_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- PTIMER Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup PTIMER_Peripheral_Access_Layer PTIMER Peripheral Access Layer

 * @{

 */



/** PTIMER - Size of Registers Arrays */
#define PTIMER_CH_CNT                               4u
#define PTIMER_CH_DLY_CNT                           8u
#define PTIMER_DLY_CNT                              (PTIMER_CH_CNT * PTIMER_CH_DLY_CNT)

/** PTIMER - Register Layout Typedef */

typedef struct {

  __IO uint32_t STATUS_CTRL                   ; /* Status and Control Register, offset: 0x0 */

  __IO uint32_t MAX_CNT                       ; /* Max Count Number Register, offset: 0x4 */

  __IO uint32_t CNT                           ; /* Counter Register, offset: 0x8 */

  __IO uint32_t INT_DLY                       ; /* Interrupt Delay Register, offset: 0xC */

  struct{
     __IO uint32_t CTRL                       ; /* Channel n Control register 1, array offset: 0x10, array step: 0x28 */
     __IO uint32_t STATUS                     ; /* Channel n Status register, array offset: 0x14, array step: 0x28 */
     __IO uint32_t DLY[PTIMER_CH_DLY_CNT]     ; /* Channel n Delay 0 register..Channel n Delay 7 register, array offset: 0x18, array step: index*0x28, index2*0x4 */
  } CH[PTIMER_CH_CNT]                         ; /* Channel n registers, array offset: 0x10, array step: 0x28 */

       uint8_t  RESERVED_0[224];

  __IO uint32_t POEN                          ; /* Pulse-Out Enable Register, offset: 0x190 */

  __IO uint32_t PODLY                         ; /* Pulse-Out Delay Register, offset: 0x194 */

} PTIMER_Type, *PTIMER_MemMapPtr;



/** Number of instances of the PTIMER module. */

#define PTIMER_INSTANCE_COUNT                    (2u)



/* PTIMER - Peripheral instance base addresses */

/** Peripheral PTIMER0 base address */

#define PTIMER0_BASE                             (0x40037000u)

/** Peripheral PTIMER0 base pointer */

#define PTIMER0                                  ((PTIMER_Type *)PTIMER0_BASE)

/** Peripheral PTIMER1 base address */

#define PTIMER1_BASE                             (0x40038000u)

/** Peripheral PTIMER1 base pointer */

#define PTIMER1                                  ((PTIMER_Type *)PTIMER1_BASE)

/** Array initializer of PTIMER peripheral base addresses */

#define PTIMER_BASE_ADDRS                        {PTIMER0_BASE, PTIMER1_BASE}

/** Array initializer of PTIMER peripheral base pointers */

#define PTIMER_BASE_PTRS                         {PTIMER0, PTIMER1}

// need fill by yourself

///** Number of interrupt vector arrays for the PTIMER module. */

//#define PTIMER_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the PTIMER module. */

//#define PTIMER_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the PTIMER peripheral type */

//#define PTIMER_IRQS                              {PTIMER0_IRQn, PTIMER1_IRQn}





/* ----------------------------------------------------------------------------

   -- PTIMER Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup PTIMER_Register_Masks PTIMER Register Masks

 * @{

 */



/* STATUS_CTRL Bit Fields */

#define PTIMER_STATUS_CTRL_LDMODE_MASK 0xC0000u

#define PTIMER_STATUS_CTRL_LDMODE_SHIFT 18u

#define PTIMER_STATUS_CTRL_LDMODE_WIDTH 2u

#define PTIMER_STATUS_CTRL_LDMODE(x)   (((uint32_t)(((uint32_t)(x))<<PTIMER_STATUS_CTRL_LDMODE_SHIFT))&PTIMER_STATUS_CTRL_LDMODE_MASK)

#define PTIMER_STATUS_CTRL_SERR_INTEN_MASK 0x20000u

#define PTIMER_STATUS_CTRL_SERR_INTEN_SHIFT 17u

#define PTIMER_STATUS_CTRL_SERR_INTEN_WIDTH 1u

#define PTIMER_STATUS_CTRL_SERR_INTEN(x) (((uint32_t)(((uint32_t)(x))<<PTIMER_STATUS_CTRL_SERR_INTEN_SHIFT))&PTIMER_STATUS_CTRL_SERR_INTEN_MASK)

#define PTIMER_STATUS_CTRL_SWTRG_MASK  0x10000u

#define PTIMER_STATUS_CTRL_SWTRG_SHIFT 16u

#define PTIMER_STATUS_CTRL_SWTRG_WIDTH 1u

#define PTIMER_STATUS_CTRL_SWTRG(x)    (((uint32_t)(((uint32_t)(x))<<PTIMER_STATUS_CTRL_SWTRG_SHIFT))&PTIMER_STATUS_CTRL_SWTRG_MASK)

#define PTIMER_STATUS_CTRL_DMAEN_MASK  0x8000u

#define PTIMER_STATUS_CTRL_DMAEN_SHIFT 15u

#define PTIMER_STATUS_CTRL_DMAEN_WIDTH 1u

#define PTIMER_STATUS_CTRL_DMAEN(x)    (((uint32_t)(((uint32_t)(x))<<PTIMER_STATUS_CTRL_DMAEN_SHIFT))&PTIMER_STATUS_CTRL_DMAEN_MASK)

#define PTIMER_STATUS_CTRL_PRESCALER_MASK 0x7000u

#define PTIMER_STATUS_CTRL_PRESCALER_SHIFT 12u

#define PTIMER_STATUS_CTRL_PRESCALER_WIDTH 3u

#define PTIMER_STATUS_CTRL_PRESCALER(x) (((uint32_t)(((uint32_t)(x))<<PTIMER_STATUS_CTRL_PRESCALER_SHIFT))&PTIMER_STATUS_CTRL_PRESCALER_MASK)

#define PTIMER_STATUS_CTRL_TRGSEL_MASK 0xF00u

#define PTIMER_STATUS_CTRL_TRGSEL_SHIFT 8u

#define PTIMER_STATUS_CTRL_TRGSEL_WIDTH 4u

#define PTIMER_STATUS_CTRL_TRGSEL(x)   (((uint32_t)(((uint32_t)(x))<<PTIMER_STATUS_CTRL_TRGSEL_SHIFT))&PTIMER_STATUS_CTRL_TRGSEL_MASK)

#define PTIMER_STATUS_CTRL_ENABLE_MASK 0x80u

#define PTIMER_STATUS_CTRL_ENABLE_SHIFT 7u

#define PTIMER_STATUS_CTRL_ENABLE_WIDTH 1u

#define PTIMER_STATUS_CTRL_ENABLE(x)   (((uint32_t)(((uint32_t)(x))<<PTIMER_STATUS_CTRL_ENABLE_SHIFT))&PTIMER_STATUS_CTRL_ENABLE_MASK)

#define PTIMER_STATUS_CTRL_INTFLAG_MASK 0x40u

#define PTIMER_STATUS_CTRL_INTFLAG_SHIFT 6u

#define PTIMER_STATUS_CTRL_INTFLAG_WIDTH 1u

#define PTIMER_STATUS_CTRL_INTFLAG(x)  (((uint32_t)(((uint32_t)(x))<<PTIMER_STATUS_CTRL_INTFLAG_SHIFT))&PTIMER_STATUS_CTRL_INTFLAG_MASK)

#define PTIMER_STATUS_CTRL_INTEN_MASK  0x20u

#define PTIMER_STATUS_CTRL_INTEN_SHIFT 5u

#define PTIMER_STATUS_CTRL_INTEN_WIDTH 1u

#define PTIMER_STATUS_CTRL_INTEN(x)    (((uint32_t)(((uint32_t)(x))<<PTIMER_STATUS_CTRL_INTEN_SHIFT))&PTIMER_STATUS_CTRL_INTEN_MASK)

#define PTIMER_STATUS_CTRL_MULT_MASK   0xCu

#define PTIMER_STATUS_CTRL_MULT_SHIFT  2u

#define PTIMER_STATUS_CTRL_MULT_WIDTH  2u

#define PTIMER_STATUS_CTRL_MULT(x)     (((uint32_t)(((uint32_t)(x))<<PTIMER_STATUS_CTRL_MULT_SHIFT))&PTIMER_STATUS_CTRL_MULT_MASK)

#define PTIMER_STATUS_CTRL_CONT_MASK   0x2u

#define PTIMER_STATUS_CTRL_CONT_SHIFT  1u

#define PTIMER_STATUS_CTRL_CONT_WIDTH  1u

#define PTIMER_STATUS_CTRL_CONT(x)     (((uint32_t)(((uint32_t)(x))<<PTIMER_STATUS_CTRL_CONT_SHIFT))&PTIMER_STATUS_CTRL_CONT_MASK)

#define PTIMER_STATUS_CTRL_LDOK_MASK   0x1u

#define PTIMER_STATUS_CTRL_LDOK_SHIFT  0u

#define PTIMER_STATUS_CTRL_LDOK_WIDTH  1u

#define PTIMER_STATUS_CTRL_LDOK(x)     (((uint32_t)(((uint32_t)(x))<<PTIMER_STATUS_CTRL_LDOK_SHIFT))&PTIMER_STATUS_CTRL_LDOK_MASK)

/* STATUS_CTRL Reg Mask */

#define PTIMER_STATUS_CTRL_MASK        0x000FFFEFu



/* MAX_CNT Bit Fields */

#define PTIMER_MAX_CNT_MAX_CNT_MASK    0xFFFFu

#define PTIMER_MAX_CNT_MAX_CNT_SHIFT   0u

#define PTIMER_MAX_CNT_MAX_CNT_WIDTH   16u

#define PTIMER_MAX_CNT_MAX_CNT(x)      (((uint32_t)(((uint32_t)(x))<<PTIMER_MAX_CNT_MAX_CNT_SHIFT))&PTIMER_MAX_CNT_MAX_CNT_MASK)

/* MAX_CNT Reg Mask */

#define PTIMER_MAX_CNT_MASK            0x0000FFFFu



/* CNT Bit Fields */

#define PTIMER_CNT_CNT_MASK            0xFFFFu

#define PTIMER_CNT_CNT_SHIFT           0u

#define PTIMER_CNT_CNT_WIDTH           16u

#define PTIMER_CNT_CNT(x)              (((uint32_t)(((uint32_t)(x))<<PTIMER_CNT_CNT_SHIFT))&PTIMER_CNT_CNT_MASK)

/* CNT Reg Mask */

#define PTIMER_CNT_MASK                0x0000FFFFu



/* INT_DLY Bit Fields */

#define PTIMER_INT_DLY_INT_DLY_MASK    0xFFFFu

#define PTIMER_INT_DLY_INT_DLY_SHIFT   0u

#define PTIMER_INT_DLY_INT_DLY_WIDTH   16u

#define PTIMER_INT_DLY_INT_DLY(x)      (((uint32_t)(((uint32_t)(x))<<PTIMER_INT_DLY_INT_DLY_SHIFT))&PTIMER_INT_DLY_INT_DLY_MASK)

/* INT_DLY Reg Mask */

#define PTIMER_INT_DLY_MASK            0x0000FFFFu



/* CTRL_CH Bit Fields */

#define PTIMER_CTRL_CH_BTB_MASK        0xFF0000u

#define PTIMER_CTRL_CH_BTB_SHIFT       16u

#define PTIMER_CTRL_CH_BTB_WIDTH       8u

#define PTIMER_CTRL_CH_BTB(x)          (((uint32_t)(((uint32_t)(x))<<PTIMER_CTRL_CH_BTB_SHIFT))&PTIMER_CTRL_CH_BTB_MASK)

#define PTIMER_CTRL_CH_PTOS_MASK       0xFF00u

#define PTIMER_CTRL_CH_PTOS_SHIFT      8u

#define PTIMER_CTRL_CH_PTOS_WIDTH      8u

#define PTIMER_CTRL_CH_PTOS(x)         (((uint32_t)(((uint32_t)(x))<<PTIMER_CTRL_CH_PTOS_SHIFT))&PTIMER_CTRL_CH_PTOS_MASK)

#define PTIMER_CTRL_CH_PTEN_MASK       0xFFu

#define PTIMER_CTRL_CH_PTEN_SHIFT      0u

#define PTIMER_CTRL_CH_PTEN_WIDTH      8u

#define PTIMER_CTRL_CH_PTEN(x)         (((uint32_t)(((uint32_t)(x))<<PTIMER_CTRL_CH_PTEN_SHIFT))&PTIMER_CTRL_CH_PTEN_MASK)

/* CTRL_CH Reg Mask */

#define PTIMER_CTRL_CH_MASK            0x00FFFFFFu



/* STATUS_CH Bit Fields */

#define PTIMER_STATUS_CH_CHN_FLAG_MASK 0xFF0000u

#define PTIMER_STATUS_CH_CHN_FLAG_SHIFT 16u

#define PTIMER_STATUS_CH_CHN_FLAG_WIDTH 8u

#define PTIMER_STATUS_CH_CHN_FLAG(x)   (((uint32_t)(((uint32_t)(x))<<PTIMER_STATUS_CH_CHN_FLAG_SHIFT))&PTIMER_STATUS_CH_CHN_FLAG_MASK)

#define PTIMER_STATUS_CH_SERR_FLAG_MASK 0xFFu

#define PTIMER_STATUS_CH_SERR_FLAG_SHIFT 0u

#define PTIMER_STATUS_CH_SERR_FLAG_WIDTH 8u

#define PTIMER_STATUS_CH_SERR_FLAG(x)  (((uint32_t)(((uint32_t)(x))<<PTIMER_STATUS_CH_SERR_FLAG_SHIFT))&PTIMER_STATUS_CH_SERR_FLAG_MASK)

/* STATUS_CH Reg Mask */

#define PTIMER_STATUS_CH_MASK          0x00FF00FFu



/* DLYn_CHm Bit Fields */

#define PTIMER_DLY_CH_CHNDLY_MASK     0xFFFFu

#define PTIMER_DLY_CH_CHNDLY_SHIFT    0u

#define PTIMER_DLY_CH_CHNDLY_WIDTH    16u

#define PTIMER_DLY_CH_CHNDLY(x)       (((uint32_t)(((uint32_t)(x))<<PTIMER_DLY_CH_CHNDLY_SHIFT))&PTIMER_DLY_CH_CHNDLY_MASK)

/* DLYn_CHm Reg Mask */

#define PTIMER_DLY_CH_MASK            0x0000FFFFu




/* POEN Bit Fields */

#define PTIMER_POEN_POEN_MASK          0x1u

#define PTIMER_POEN_POEN_SHIFT         0u

#define PTIMER_POEN_POEN_WIDTH         1u

#define PTIMER_POEN_POEN(x)            (((uint32_t)(((uint32_t)(x))<<PTIMER_POEN_POEN_SHIFT))&PTIMER_POEN_POEN_MASK)

/* POEN Reg Mask */

#define PTIMER_POEN_MASK               0x00000001u



/* PODLY Bit Fields */

#define PTIMER_PODLY_DLY1_MASK         0xFFFF0000u

#define PTIMER_PODLY_DLY1_SHIFT        16u

#define PTIMER_PODLY_DLY1_WIDTH        16u

#define PTIMER_PODLY_DLY1(x)           (((uint32_t)(((uint32_t)(x))<<PTIMER_PODLY_DLY1_SHIFT))&PTIMER_PODLY_DLY1_MASK)

#define PTIMER_PODLY_DLY2_MASK         0xFFFFu

#define PTIMER_PODLY_DLY2_SHIFT        0u

#define PTIMER_PODLY_DLY2_WIDTH        16u

#define PTIMER_PODLY_DLY2(x)           (((uint32_t)(((uint32_t)(x))<<PTIMER_PODLY_DLY2_SHIFT))&PTIMER_PODLY_DLY2_MASK)

/* PODLY Reg Mask */

#define PTIMER_PODLY_MASK              0xFFFFFFFFu





/*!

 * @}

 */ /* end of group PTIMER_Register_Masks */



/*!

 * @}

 */ /* end of group PTIMER_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
