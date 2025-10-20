#ifndef _FC7240_RTC_NU_Tztufn39_REGS_H_
#define _FC7240_RTC_NU_Tztufn39_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- RTC Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup RTC_Peripheral_Access_Layer RTC Peripheral Access Layer

 * @{

 */



/** RTC - Size of Registers Arrays */



/** RTC - Register Layout Typedef */



typedef struct {



  __IO uint32_t SR                            ; /* Seconds Register, offset: 0x0 */

  __IO uint32_t PR                            ; /* Prescaler Register, offset: 0x4 */

  __IO uint32_t AR                            ; /* Alarm Register, offset: 0x8 */

  __IO uint32_t COMPR                         ; /* Compensation Register, offset: 0xC */

  __IO uint32_t CR                            ; /* Control Register, offset: 0x10 */

  __IO uint32_t STR                           ; /* Status Register, offset: 0x14 */

  __IO uint32_t LR                            ; /* Lock Register, offset: 0x18 */

  __IO uint32_t IER                           ; /* Interrupt Enable Register, offset: 0x1C */



} RTC_Type, *RTC_MemMapPtr;



/** Number of instances of the RTC module. */

#define RTC_INSTANCE_COUNT                       (1u)



/* RTC - Peripheral instance base addresses */

/** Peripheral RTC base address */

#define RTC_BASE                                 (0x40030000u)

/** Peripheral RTC base pointer */

#define RTC                                      ((RTC_Type *)RTC_BASE)

/** Array initializer of RTC peripheral base addresses */

#define RTC_BASE_ADDRS                           {RTC_BASE}

/** Array initializer of RTC peripheral base pointers */

#define RTC_BASE_PTRS                            {RTC}

// need fill by yourself

///** Number of interrupt vector arrays for the RTC module. */

//#define RTC_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the RTC module. */

//#define RTC_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the RTC peripheral type */

//#define RTC_IRQS                                 {RTC_IRQn}





/* ----------------------------------------------------------------------------

   -- RTC Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup RTC_Register_Masks RTC Register Masks

 * @{

 */



/* SR Bit Fields */

#define RTC_SR_TSR_MASK                0xFFFFFFFFu

#define RTC_SR_TSR_SHIFT               0u

#define RTC_SR_TSR_WIDTH               32u

#define RTC_SR_TSR(x)                  (((uint32_t)(((uint32_t)(x))<<RTC_SR_TSR_SHIFT))&RTC_SR_TSR_MASK)

/* SR Reg Mask */

#define RTC_SR_MASK                    0xFFFFFFFFu



/* PR Bit Fields */

#define RTC_PR_TPR_MASK                0xFFFFu

#define RTC_PR_TPR_SHIFT               0u

#define RTC_PR_TPR_WIDTH               16u

#define RTC_PR_TPR(x)                  (((uint32_t)(((uint32_t)(x))<<RTC_PR_TPR_SHIFT))&RTC_PR_TPR_MASK)

/* PR Reg Mask */

#define RTC_PR_MASK                    0x0000FFFFu



/* AR Bit Fields */

#define RTC_AR_TAR_MASK                0xFFFFFFFFu

#define RTC_AR_TAR_SHIFT               0u

#define RTC_AR_TAR_WIDTH               32u

#define RTC_AR_TAR(x)                  (((uint32_t)(((uint32_t)(x))<<RTC_AR_TAR_SHIFT))&RTC_AR_TAR_MASK)

/* AR Reg Mask */

#define RTC_AR_MASK                    0xFFFFFFFFu



/* COMPR Bit Fields */

#define RTC_COMPR_CIC_MASK             0xFF000000u

#define RTC_COMPR_CIC_SHIFT            24u

#define RTC_COMPR_CIC_WIDTH            8u

#define RTC_COMPR_CIC(x)               (((uint32_t)(((uint32_t)(x))<<RTC_COMPR_CIC_SHIFT))&RTC_COMPR_CIC_MASK)

#define RTC_COMPR_TCV_MASK             0xFF0000u

#define RTC_COMPR_TCV_SHIFT            16u

#define RTC_COMPR_TCV_WIDTH            8u

#define RTC_COMPR_TCV(x)               (((uint32_t)(((uint32_t)(x))<<RTC_COMPR_TCV_SHIFT))&RTC_COMPR_TCV_MASK)

#define RTC_COMPR_CIR_MASK             0xFF00u

#define RTC_COMPR_CIR_SHIFT            8u

#define RTC_COMPR_CIR_WIDTH            8u

#define RTC_COMPR_CIR(x)               (((uint32_t)(((uint32_t)(x))<<RTC_COMPR_CIR_SHIFT))&RTC_COMPR_CIR_MASK)

#define RTC_COMPR_TCR_MASK             0xFFu

#define RTC_COMPR_TCR_SHIFT            0u

#define RTC_COMPR_TCR_WIDTH            8u

#define RTC_COMPR_TCR(x)               (((uint32_t)(((uint32_t)(x))<<RTC_COMPR_TCR_SHIFT))&RTC_COMPR_TCR_MASK)

/* COMPR Reg Mask */

#define RTC_COMPR_MASK                 0xFFFFFFFFu



/* CR Bit Fields */

#define RTC_CR_CKO_MASK                0x200u

#define RTC_CR_CKO_SHIFT               9u

#define RTC_CR_CKO_WIDTH               1u

#define RTC_CR_CKO(x)                  (((uint32_t)(((uint32_t)(x))<<RTC_CR_CKO_SHIFT))&RTC_CR_CKO_MASK)

#define RTC_CR_CKPS_MASK               0x20u

#define RTC_CR_CKPS_SHIFT              5u

#define RTC_CR_CKPS_WIDTH              1u

#define RTC_CR_CKPS(x)                 (((uint32_t)(((uint32_t)(x))<<RTC_CR_CKPS_SHIFT))&RTC_CR_CKPS_MASK)

#define RTC_CR_UM_MASK                 0x8u

#define RTC_CR_UM_SHIFT                3u

#define RTC_CR_UM_WIDTH                1u

#define RTC_CR_UM(x)                   (((uint32_t)(((uint32_t)(x))<<RTC_CR_UM_SHIFT))&RTC_CR_UM_MASK)

#define RTC_CR_SWRST_MASK              0x1u

#define RTC_CR_SWRST_SHIFT             0u

#define RTC_CR_SWRST_WIDTH             1u

#define RTC_CR_SWRST(x)                (((uint32_t)(((uint32_t)(x))<<RTC_CR_SWRST_SHIFT))&RTC_CR_SWRST_MASK)

/* CR Reg Mask */

#define RTC_CR_MASK                    0x00000229u



/* STR Bit Fields */

#define RTC_STR_TCE_MASK               0x10u

#define RTC_STR_TCE_SHIFT              4u

#define RTC_STR_TCE_WIDTH              1u

#define RTC_STR_TCE(x)                 (((uint32_t)(((uint32_t)(x))<<RTC_STR_TCE_SHIFT))&RTC_STR_TCE_MASK)

#define RTC_STR_TAF_MASK               0x4u

#define RTC_STR_TAF_SHIFT              2u

#define RTC_STR_TAF_WIDTH              1u

#define RTC_STR_TAF(x)                 (((uint32_t)(((uint32_t)(x))<<RTC_STR_TAF_SHIFT))&RTC_STR_TAF_MASK)

#define RTC_STR_TOF_MASK               0x2u

#define RTC_STR_TOF_SHIFT              1u

#define RTC_STR_TOF_WIDTH              1u

#define RTC_STR_TOF(x)                 (((uint32_t)(((uint32_t)(x))<<RTC_STR_TOF_SHIFT))&RTC_STR_TOF_MASK)

/* STR Reg Mask */

#define RTC_STR_MASK                   0x00000016u



/* LR Bit Fields */

#define RTC_LR_LRL_MASK                0x40u

#define RTC_LR_LRL_SHIFT               6u

#define RTC_LR_LRL_WIDTH               1u

#define RTC_LR_LRL(x)                  (((uint32_t)(((uint32_t)(x))<<RTC_LR_LRL_SHIFT))&RTC_LR_LRL_MASK)

#define RTC_LR_STRL_MASK               0x20u

#define RTC_LR_STRL_SHIFT              5u

#define RTC_LR_STRL_WIDTH              1u

#define RTC_LR_STRL(x)                 (((uint32_t)(((uint32_t)(x))<<RTC_LR_STRL_SHIFT))&RTC_LR_STRL_MASK)

#define RTC_LR_CRL_MASK                0x10u

#define RTC_LR_CRL_SHIFT               4u

#define RTC_LR_CRL_WIDTH               1u

#define RTC_LR_CRL(x)                  (((uint32_t)(((uint32_t)(x))<<RTC_LR_CRL_SHIFT))&RTC_LR_CRL_MASK)

#define RTC_LR_CPL_MASK                0x8u

#define RTC_LR_CPL_SHIFT               3u

#define RTC_LR_CPL_WIDTH               1u

#define RTC_LR_CPL(x)                  (((uint32_t)(((uint32_t)(x))<<RTC_LR_CPL_SHIFT))&RTC_LR_CPL_MASK)

/* LR Reg Mask */

#define RTC_LR_MASK                    0x00000078u



/* IER Bit Fields */

#define RTC_IER_TSIC_MASK              0x70000u

#define RTC_IER_TSIC_SHIFT             16u

#define RTC_IER_TSIC_WIDTH             3u

#define RTC_IER_TSIC(x)                (((uint32_t)(((uint32_t)(x))<<RTC_IER_TSIC_SHIFT))&RTC_IER_TSIC_MASK)

#define RTC_IER_TSIE_MASK              0x10u

#define RTC_IER_TSIE_SHIFT             4u

#define RTC_IER_TSIE_WIDTH             1u

#define RTC_IER_TSIE(x)                (((uint32_t)(((uint32_t)(x))<<RTC_IER_TSIE_SHIFT))&RTC_IER_TSIE_MASK)

#define RTC_IER_TAIE_MASK              0x4u

#define RTC_IER_TAIE_SHIFT             2u

#define RTC_IER_TAIE_WIDTH             1u

#define RTC_IER_TAIE(x)                (((uint32_t)(((uint32_t)(x))<<RTC_IER_TAIE_SHIFT))&RTC_IER_TAIE_MASK)

#define RTC_IER_TOIE_MASK              0x2u

#define RTC_IER_TOIE_SHIFT             1u

#define RTC_IER_TOIE_WIDTH             1u

#define RTC_IER_TOIE(x)                (((uint32_t)(((uint32_t)(x))<<RTC_IER_TOIE_SHIFT))&RTC_IER_TOIE_MASK)

/* IER Reg Mask */

#define RTC_IER_MASK                   0x00070016u





/*!

 * @}

 */ /* end of group RTC_Register_Masks */



/*!

 * @}

 */ /* end of group RTC_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
