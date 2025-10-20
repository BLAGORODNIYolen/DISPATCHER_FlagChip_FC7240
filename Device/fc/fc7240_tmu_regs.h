#ifndef _FC7240_TMU_NU_Tztufn28_REGS_H_
#define _FC7240_TMU_NU_Tztufn28_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- TMU Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup TMU_Peripheral_Access_Layer TMU Peripheral Access Layer

 * @{

 */



/** TMU - Size of Registers Arrays */



/** TMU - Register Layout Typedef */



typedef struct {



  __IO uint32_t UNLOCK                        ; /* Unlock Register, offset: 0x0 */

  __IO uint32_t TF_CTRL                       ; /* Temperature Flag Control Register, offset: 0x4 */

  __IO uint32_t TF_STATUS                     ; /* Temperature Flag Status Register, offset: 0x8 */

  __IO uint32_t TV_CTRL                       ; /* Temperature Voltage Control Register, offset: 0xC */

  __IO uint32_t TV_STATUS                     ; /* Temperature Voltage Status Register, offset: 0x10 */

       uint8_t  RESERVED_0[8];

  __I  uint32_t TV_TRIM                       ; /* Temperature Voltage Trim Register, offset: 0x1C */



} TMU_Type, *TMU_MemMapPtr;



/** Number of instances of the TMU module. */

#define TMU_INSTANCE_COUNT                       (1u)



/* TMU - Peripheral instance base addresses */

/** Peripheral TMU base address */

#define TMU_BASE                                 (0x40043000u)

/** Peripheral TMU base pointer */

#define TMU                                      ((TMU_Type *)TMU_BASE)

/** Array initializer of TMU peripheral base addresses */

#define TMU_BASE_ADDRS                           {TMU_BASE}

/** Array initializer of TMU peripheral base pointers */

#define TMU_BASE_PTRS                            {TMU}

// need fill by yourself

///** Number of interrupt vector arrays for the TMU module. */

//#define TMU_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the TMU module. */

//#define TMU_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the TMU peripheral type */

//#define TMU_IRQS                                 {TMU_IRQn}





/* ----------------------------------------------------------------------------

   -- TMU Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup TMU_Register_Masks TMU Register Masks

 * @{

 */



/* UNLOCK Bit Fields */

#define TMU_UNLOCK_UNLOCK_MASK         0x1u

#define TMU_UNLOCK_UNLOCK_SHIFT        0u

#define TMU_UNLOCK_UNLOCK_WIDTH        1u

#define TMU_UNLOCK_UNLOCK(x)           (((uint32_t)(((uint32_t)(x))<<TMU_UNLOCK_UNLOCK_SHIFT))&TMU_UNLOCK_UNLOCK_MASK)

/* UNLOCK Reg Mask */

#define TMU_UNLOCK_MASK                0x00000001u



/* TF_CTRL Bit Fields */

#define TMU_TF_CTRL_TF_150F_IE_MASK    0x8000000u

#define TMU_TF_CTRL_TF_150F_IE_SHIFT   27u

#define TMU_TF_CTRL_TF_150F_IE_WIDTH   1u

#define TMU_TF_CTRL_TF_150F_IE(x)      (((uint32_t)(((uint32_t)(x))<<TMU_TF_CTRL_TF_150F_IE_SHIFT))&TMU_TF_CTRL_TF_150F_IE_MASK)

#define TMU_TF_CTRL_TF_125F_IE_MASK    0x4000000u

#define TMU_TF_CTRL_TF_125F_IE_SHIFT   26u

#define TMU_TF_CTRL_TF_125F_IE_WIDTH   1u

#define TMU_TF_CTRL_TF_125F_IE(x)      (((uint32_t)(((uint32_t)(x))<<TMU_TF_CTRL_TF_125F_IE_SHIFT))&TMU_TF_CTRL_TF_125F_IE_MASK)

#define TMU_TF_CTRL_TF_RDYF_IE_MASK    0x1000000u

#define TMU_TF_CTRL_TF_RDYF_IE_SHIFT   24u

#define TMU_TF_CTRL_TF_RDYF_IE_WIDTH   1u

#define TMU_TF_CTRL_TF_RDYF_IE(x)      (((uint32_t)(((uint32_t)(x))<<TMU_TF_CTRL_TF_RDYF_IE_SHIFT))&TMU_TF_CTRL_TF_RDYF_IE_MASK)

#define TMU_TF_CTRL_TF_HYSOFF_MASK     0x10000u

#define TMU_TF_CTRL_TF_HYSOFF_SHIFT    16u

#define TMU_TF_CTRL_TF_HYSOFF_WIDTH    1u

#define TMU_TF_CTRL_TF_HYSOFF(x)       (((uint32_t)(((uint32_t)(x))<<TMU_TF_CTRL_TF_HYSOFF_SHIFT))&TMU_TF_CTRL_TF_HYSOFF_MASK)

#define TMU_TF_CTRL_TF_START_CNT_MASK  0xF00u

#define TMU_TF_CTRL_TF_START_CNT_SHIFT 8u

#define TMU_TF_CTRL_TF_START_CNT_WIDTH 4u

#define TMU_TF_CTRL_TF_START_CNT(x)    (((uint32_t)(((uint32_t)(x))<<TMU_TF_CTRL_TF_START_CNT_SHIFT))&TMU_TF_CTRL_TF_START_CNT_MASK)

#define TMU_TF_CTRL_TF_FILT_BYP_MASK   0x2u

#define TMU_TF_CTRL_TF_FILT_BYP_SHIFT  1u

#define TMU_TF_CTRL_TF_FILT_BYP_WIDTH  1u

#define TMU_TF_CTRL_TF_FILT_BYP(x)     (((uint32_t)(((uint32_t)(x))<<TMU_TF_CTRL_TF_FILT_BYP_SHIFT))&TMU_TF_CTRL_TF_FILT_BYP_MASK)

#define TMU_TF_CTRL_TF_EN_MASK         0x1u

#define TMU_TF_CTRL_TF_EN_SHIFT        0u

#define TMU_TF_CTRL_TF_EN_WIDTH        1u

#define TMU_TF_CTRL_TF_EN(x)           (((uint32_t)(((uint32_t)(x))<<TMU_TF_CTRL_TF_EN_SHIFT))&TMU_TF_CTRL_TF_EN_MASK)

/* TF_CTRL Reg Mask */

#define TMU_TF_CTRL_MASK               0x0D010F03u



/* TF_STATUS Bit Fields */

#define TMU_TF_STATUS_TF_150_MASK      0x800u

#define TMU_TF_STATUS_TF_150_SHIFT     11u

#define TMU_TF_STATUS_TF_150_WIDTH     1u

#define TMU_TF_STATUS_TF_150(x)        (((uint32_t)(((uint32_t)(x))<<TMU_TF_STATUS_TF_150_SHIFT))&TMU_TF_STATUS_TF_150_MASK)

#define TMU_TF_STATUS_TF_125_MASK      0x400u

#define TMU_TF_STATUS_TF_125_SHIFT     10u

#define TMU_TF_STATUS_TF_125_WIDTH     1u

#define TMU_TF_STATUS_TF_125(x)        (((uint32_t)(((uint32_t)(x))<<TMU_TF_STATUS_TF_125_SHIFT))&TMU_TF_STATUS_TF_125_MASK)

#define TMU_TF_STATUS_TF_150F_MASK     0x8u

#define TMU_TF_STATUS_TF_150F_SHIFT    3u

#define TMU_TF_STATUS_TF_150F_WIDTH    1u

#define TMU_TF_STATUS_TF_150F(x)       (((uint32_t)(((uint32_t)(x))<<TMU_TF_STATUS_TF_150F_SHIFT))&TMU_TF_STATUS_TF_150F_MASK)

#define TMU_TF_STATUS_TF_125F_MASK     0x4u

#define TMU_TF_STATUS_TF_125F_SHIFT    2u

#define TMU_TF_STATUS_TF_125F_WIDTH    1u

#define TMU_TF_STATUS_TF_125F(x)       (((uint32_t)(((uint32_t)(x))<<TMU_TF_STATUS_TF_125F_SHIFT))&TMU_TF_STATUS_TF_125F_MASK)

#define TMU_TF_STATUS_TF_RDYF_MASK     0x1u

#define TMU_TF_STATUS_TF_RDYF_SHIFT    0u

#define TMU_TF_STATUS_TF_RDYF_WIDTH    1u

#define TMU_TF_STATUS_TF_RDYF(x)       (((uint32_t)(((uint32_t)(x))<<TMU_TF_STATUS_TF_RDYF_SHIFT))&TMU_TF_STATUS_TF_RDYF_MASK)

/* TF_STATUS Reg Mask */

#define TMU_TF_STATUS_MASK             0x00000C0Du



/* TV_CTRL Bit Fields */

#define TMU_TV_CTRL_TV_RDYF_IE_MASK    0x1000000u

#define TMU_TV_CTRL_TV_RDYF_IE_SHIFT   24u

#define TMU_TV_CTRL_TV_RDYF_IE_WIDTH   1u

#define TMU_TV_CTRL_TV_RDYF_IE(x)      (((uint32_t)(((uint32_t)(x))<<TMU_TV_CTRL_TV_RDYF_IE_SHIFT))&TMU_TV_CTRL_TV_RDYF_IE_MASK)

#define TMU_TV_CTRL_TV_START_CNT_MASK  0x700u

#define TMU_TV_CTRL_TV_START_CNT_SHIFT 8u

#define TMU_TV_CTRL_TV_START_CNT_WIDTH 3u

#define TMU_TV_CTRL_TV_START_CNT(x)    (((uint32_t)(((uint32_t)(x))<<TMU_TV_CTRL_TV_START_CNT_SHIFT))&TMU_TV_CTRL_TV_START_CNT_MASK)

#define TMU_TV_CTRL_TV_EN_MASK         0x1u

#define TMU_TV_CTRL_TV_EN_SHIFT        0u

#define TMU_TV_CTRL_TV_EN_WIDTH        1u

#define TMU_TV_CTRL_TV_EN(x)           (((uint32_t)(((uint32_t)(x))<<TMU_TV_CTRL_TV_EN_SHIFT))&TMU_TV_CTRL_TV_EN_MASK)

/* TV_CTRL Reg Mask */

#define TMU_TV_CTRL_MASK               0x01000701u



/* TV_STATUS Bit Fields */

#define TMU_TV_STATUS_TV_RDYF_MASK     0x1u

#define TMU_TV_STATUS_TV_RDYF_SHIFT    0u

#define TMU_TV_STATUS_TV_RDYF_WIDTH    1u

#define TMU_TV_STATUS_TV_RDYF(x)       (((uint32_t)(((uint32_t)(x))<<TMU_TV_STATUS_TV_RDYF_SHIFT))&TMU_TV_STATUS_TV_RDYF_MASK)

/* TV_STATUS Reg Mask */

#define TMU_TV_STATUS_MASK             0x00000001u



/* TV_TRIM Bit Fields */

#define TMU_TV_TRIM_TV_TCODE_MASK      0xFFF0000u

#define TMU_TV_TRIM_TV_TCODE_SHIFT     16u

#define TMU_TV_TRIM_TV_TCODE_WIDTH     12u

#define TMU_TV_TRIM_TV_TCODE(x)        (((uint32_t)(((uint32_t)(x))<<TMU_TV_TRIM_TV_TCODE_SHIFT))&TMU_TV_TRIM_TV_TCODE_MASK)

#define TMU_TV_TRIM_TV_SLOPE_MASK      0x1FFFu

#define TMU_TV_TRIM_TV_SLOPE_SHIFT     0u

#define TMU_TV_TRIM_TV_SLOPE_WIDTH     13u

#define TMU_TV_TRIM_TV_SLOPE(x)        (((uint32_t)(((uint32_t)(x))<<TMU_TV_TRIM_TV_SLOPE_SHIFT))&TMU_TV_TRIM_TV_SLOPE_MASK)

/* TV_TRIM Reg Mask */

#define TMU_TV_TRIM_MASK               0x0FFF1FFFu





/*!

 * @}

 */ /* end of group TMU_Register_Masks */



/*!

 * @}

 */ /* end of group TMU_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
