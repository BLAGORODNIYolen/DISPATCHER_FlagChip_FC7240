#ifndef _FC7240_TPU_E_NU_Tztufn32_REGS_H_
#define _FC7240_TPU_E_NU_Tztufn32_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- TPU_E Peripheral Access Layer

   ---------------------------------------------------------------------------- */

#define TPU_E_CH_COUNT                32

/*!

 * @addtogroup TPU_E_Peripheral_Access_Layer TPU_E Peripheral Access Layer

 * @{

 */



/** TPU_E - Size of Registers Arrays */



/** TPU_E - Register Layout Typedef */



typedef struct {



  __IO uint32_t GCR_CR                        ; /* Global Control Region - Control Register, offset: 0x0 */

       uint8_t  RESERVED_0[4];

  __IO uint32_t GCR_SRR                       ; /* Global Control Region - Software Reset Register, offset: 0x8 */

       uint8_t  RESERVED_1[4];

  __I  uint32_t GCR_VSR                       ; /* Global Control Region - Visible Status Register, offset: 0x10 */

  __I  uint32_t GCR_VIR                       ; /* Global Control Region - Visible Input Status Register, offset: 0x14 */

  __I  uint32_t GCR_VOR                       ; /* Global Control Region -Visible Output Status Register, offset: 0x18 */

  __I  uint32_t GCR_VOBR                      ; /* Global Control Region - Visible Output Enable Status Register, offset: 0x1C */

  __I  uint32_t GCR_VM1R                      ; /* Global Control Region - Visible MRL1 Register, offset: 0x20 */

  __I  uint32_t GCR_VM2R                      ; /* Global Control Region - Visible MRL2 Register, offset: 0x24 */

  __I  uint32_t GCR_VT1R                      ; /* Global Control Region - Visible TDL1 Register, offset: 0x28 */

  __I  uint32_t GCR_VT2R                      ; /* Global Control Region - Visible TDL2 Register, offset: 0x2C */

  __I  uint32_t GCR_EM1R                      ; /* Global Control Region - Visible Event by MRL1 Register, offset: 0x30 */

  __I  uint32_t GCR_EM2R                      ; /* Global Control Region - Visible Event by MRL2 Register, offset: 0x34 */

  __I  uint32_t GCR_ET1R                      ; /* Global Control Region - Visible Event by TDL1 Register, offset: 0x38 */

  __I  uint32_t GCR_ET2R                      ; /* Global Control Region - Visible Event by TDL2 Register, offset: 0x3C */

  __I  uint32_t GCR_VHSR                      ; /* Global Control Region - Visible Host Request Register, offset: 0x40 */

       uint8_t  RESERVED_2[172];

  __IO uint32_t GCR_AFGR                      ; /* Global Control Region - Interrupt Arbiter Fliter Grade Register, offset: 0xF0 */

  __IO uint32_t GCR_ASR                       ; /* Global Control Region - Interrupt Arbiter Status Register, offset: 0xF4 */

  __IO uint32_t GCR_AID                       ; /* Global Control Region - Interrupt Arbiter ID Register, offset: 0xF8 */

       uint8_t  RESERVED_3[4];

  __IO uint32_t TBR_CR                        ; /* Time Bases Region - Control Register, offset: 0x100 */

  __IO uint32_t TBR_T1R                       ; /* Time Base Region - TCR1 Value Register, offset: 0x104 */

  __IO uint32_t TBR_T2R                       ; /* Time Base Region - TCR2 Value Register, offset: 0x108 */

       uint8_t  RESERVED_4[4];

  __IO uint32_t TBR_TPR                       ; /* Time Base Region - Tooth Program Register, offset: 0x110 */

  __IO uint32_t TBR_TRR                       ; /* Time Base Region - Tick Rate Register, offset: 0x114 */

  __IO uint32_t TBR_T1MR                      ; /* Time Base Region - TCR1 Maximum Register, offset: 0x118 */

  __IO uint32_t TBR_T2MR                      ; /* Time Base Region - TCR2 Maximum Register, offset: 0x11C */

  uint8_t  RESERVED_5[1760];
  struct{                                    /* offset: 0x800, array step: 0x40 */
    __IO uint32_t CR                        ; /* Channel N Control Register, offset: 0x800 */
    __I  uint32_t SR                        ; /* Channel N Status Register, offset: 0x804 */
    __IO uint32_t SCR                       ; /* Channel N Status Control Register, offset: 0x808 */
    __I  uint32_t EFR                       ; /* Channel N Event and Flag Register, offset: 0x80c */
    __IO uint32_t CR2                       ; /* Channel N Control Register 2, offset: 0x810 */
    __IO uint32_t MR                        ; /* Channel N Mode configuration visible Register, offset: 0x814 */
    __IO uint32_t ER1                       ; /* Channel N Event Control Register or Part 1, offset: 0x818 */
    __IO uint32_t ER2                       ; /* Channel N Event Control Register or Part 2, offset: 0x81c */
    __IO uint32_t ECR                       ; /* Channel N Event Clear Register, offset: 0x820 */
    __IO uint32_t OCR                       ; /* Channel N Output User Control Register, offset: 0x824 */
         uint8_t  RESERVED_6[24];
       }  CH[TPU_E_CH_COUNT];
} TPU_E_Type, *TPU_E_MemMapPtr;



/** Number of instances of the TPU_E module. */

#define TPU_E_INSTANCE_COUNT                     (1u)



/* TPU_E - Peripheral instance base addresses */

/** Peripheral TPU_E base address */

#define TPU_E_BASE                               (0x40446000u)

/** Peripheral TPU_E base pointer */

#define TPU_E                                    ((TPU_E_Type *)TPU_E_BASE)

/** Array initializer of TPU_E peripheral base addresses */

#define TPU_E_BASE_ADDRS                         {TPU_E_BASE}

/** Array initializer of TPU_E peripheral base pointers */

#define TPU_E_BASE_PTRS                          {TPU_E}

// need fill by yourself

///** Number of interrupt vector arrays for the TPU_E module. */

//#define TPU_E_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the TPU_E module. */

//#define TPU_E_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the TPU_E peripheral type */

//#define TPU_E_IRQS                               {TPU_E_IRQn}





/* ----------------------------------------------------------------------------

   -- TPU_E Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup TPU_E_Register_Masks TPU_E Register Masks

 * @{

 */



/* GCR_CR Bit Fields */

#define TPU_E_GCR_CR_CDFC_MASK         0x60000u

#define TPU_E_GCR_CR_CDFC_SHIFT        17u

#define TPU_E_GCR_CR_CDFC_WIDTH        2u

#define TPU_E_GCR_CR_CDFC(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_CR_CDFC_SHIFT))&TPU_E_GCR_CR_CDFC_MASK)

#define TPU_E_GCR_CR_FCSS_MASK         0x10000u

#define TPU_E_GCR_CR_FCSS_SHIFT        16u

#define TPU_E_GCR_CR_FCSS_WIDTH        1u

#define TPU_E_GCR_CR_FCSS(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_CR_FCSS_SHIFT))&TPU_E_GCR_CR_FCSS_MASK)

#define TPU_E_GCR_CR_FPSCK_MASK        0xE000u

#define TPU_E_GCR_CR_FPSCK_SHIFT       13u

#define TPU_E_GCR_CR_FPSCK_WIDTH       3u

#define TPU_E_GCR_CR_FPSCK(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_CR_FPSCK_SHIFT))&TPU_E_GCR_CR_FPSCK_MASK)

#define TPU_E_GCR_CR_HALT_CH_MASK      0x400u

#define TPU_E_GCR_CR_HALT_CH_SHIFT     10u

#define TPU_E_GCR_CR_HALT_CH_WIDTH     1u

#define TPU_E_GCR_CR_HALT_CH(x)        (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_CR_HALT_CH_SHIFT))&TPU_E_GCR_CR_HALT_CH_MASK)

#define TPU_E_GCR_CR_HALT_TB_MASK      0x200u

#define TPU_E_GCR_CR_HALT_TB_SHIFT     9u

#define TPU_E_GCR_CR_HALT_TB_WIDTH     1u

#define TPU_E_GCR_CR_HALT_TB(x)        (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_CR_HALT_TB_SHIFT))&TPU_E_GCR_CR_HALT_TB_MASK)

/* GCR_CR Reg Mask */

#define TPU_E_GCR_CR_MASK              0x0007E600u



/* GCR_SRR Bit Fields */

#define TPU_E_GCR_SRR_SW_RST_MASK      0x1u

#define TPU_E_GCR_SRR_SW_RST_SHIFT     0u

#define TPU_E_GCR_SRR_SW_RST_WIDTH     1u

#define TPU_E_GCR_SRR_SW_RST(x)        (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_SRR_SW_RST_SHIFT))&TPU_E_GCR_SRR_SW_RST_MASK)

/* GCR_SRR Reg Mask */

#define TPU_E_GCR_SRR_MASK             0x00000001u



/* GCR_VSR Bit Fields */

#define TPU_E_GCR_VSR_SR_MASK          0xFFFFFFFFu

#define TPU_E_GCR_VSR_SR_SHIFT         0u

#define TPU_E_GCR_VSR_SR_WIDTH         32u

#define TPU_E_GCR_VSR_SR(x)            (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_VSR_SR_SHIFT))&TPU_E_GCR_VSR_SR_MASK)

/* GCR_VSR Reg Mask */

#define TPU_E_GCR_VSR_MASK             0xFFFFFFFFu



/* GCR_VIR Bit Fields */

#define TPU_E_GCR_VIR_PSTI_MASK        0xFFFFFFFFu

#define TPU_E_GCR_VIR_PSTI_SHIFT       0u

#define TPU_E_GCR_VIR_PSTI_WIDTH       32u

#define TPU_E_GCR_VIR_PSTI(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_VIR_PSTI_SHIFT))&TPU_E_GCR_VIR_PSTI_MASK)

/* GCR_VIR Reg Mask */

#define TPU_E_GCR_VIR_MASK             0xFFFFFFFFu



/* GCR_VOR Bit Fields */

#define TPU_E_GCR_VOR_PSTO_MASK        0xFFFFFFFFu

#define TPU_E_GCR_VOR_PSTO_SHIFT       0u

#define TPU_E_GCR_VOR_PSTO_WIDTH       32u

#define TPU_E_GCR_VOR_PSTO(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_VOR_PSTO_SHIFT))&TPU_E_GCR_VOR_PSTO_MASK)

/* GCR_VOR Reg Mask */

#define TPU_E_GCR_VOR_MASK             0xFFFFFFFFu



/* GCR_VOBR Bit Fields */

#define TPU_E_GCR_VOBR_PSTOE_MASK      0xFFFFFFFFu

#define TPU_E_GCR_VOBR_PSTOE_SHIFT     0u

#define TPU_E_GCR_VOBR_PSTOE_WIDTH     32u

#define TPU_E_GCR_VOBR_PSTOE(x)        (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_VOBR_PSTOE_SHIFT))&TPU_E_GCR_VOBR_PSTOE_MASK)

/* GCR_VOBR Reg Mask */

#define TPU_E_GCR_VOBR_MASK            0xFFFFFFFFu



/* GCR_VM1R Bit Fields */

#define TPU_E_GCR_VM1R_M1R_MASK        0xFFFFFFFFu

#define TPU_E_GCR_VM1R_M1R_SHIFT       0u

#define TPU_E_GCR_VM1R_M1R_WIDTH       32u

#define TPU_E_GCR_VM1R_M1R(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_VM1R_M1R_SHIFT))&TPU_E_GCR_VM1R_M1R_MASK)

/* GCR_VM1R Reg Mask */

#define TPU_E_GCR_VM1R_MASK            0xFFFFFFFFu



/* GCR_VM2R Bit Fields */

#define TPU_E_GCR_VM2R_M2R_MASK        0xFFFFFFFFu

#define TPU_E_GCR_VM2R_M2R_SHIFT       0u

#define TPU_E_GCR_VM2R_M2R_WIDTH       32u

#define TPU_E_GCR_VM2R_M2R(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_VM2R_M2R_SHIFT))&TPU_E_GCR_VM2R_M2R_MASK)

/* GCR_VM2R Reg Mask */

#define TPU_E_GCR_VM2R_MASK            0xFFFFFFFFu



/* GCR_VT1R Bit Fields */

#define TPU_E_GCR_VT1R_T1R_MASK        0xFFFFFFFFu

#define TPU_E_GCR_VT1R_T1R_SHIFT       0u

#define TPU_E_GCR_VT1R_T1R_WIDTH       32u

#define TPU_E_GCR_VT1R_T1R(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_VT1R_T1R_SHIFT))&TPU_E_GCR_VT1R_T1R_MASK)

/* GCR_VT1R Reg Mask */

#define TPU_E_GCR_VT1R_MASK            0xFFFFFFFFu



/* GCR_VT2R Bit Fields */

#define TPU_E_GCR_VT2R_T2R_MASK        0xFFFFFFFFu

#define TPU_E_GCR_VT2R_T2R_SHIFT       0u

#define TPU_E_GCR_VT2R_T2R_WIDTH       32u

#define TPU_E_GCR_VT2R_T2R(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_VT2R_T2R_SHIFT))&TPU_E_GCR_VT2R_T2R_MASK)

/* GCR_VT2R Reg Mask */

#define TPU_E_GCR_VT2R_MASK            0xFFFFFFFFu



/* GCR_EM1R Bit Fields */

#define TPU_E_GCR_EM1R_EM1R_MASK       0xFFFFFFFFu

#define TPU_E_GCR_EM1R_EM1R_SHIFT      0u

#define TPU_E_GCR_EM1R_EM1R_WIDTH      32u

#define TPU_E_GCR_EM1R_EM1R(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_EM1R_EM1R_SHIFT))&TPU_E_GCR_EM1R_EM1R_MASK)

/* GCR_EM1R Reg Mask */

#define TPU_E_GCR_EM1R_MASK            0xFFFFFFFFu



/* GCR_EM2R Bit Fields */

#define TPU_E_GCR_EM2R_EM2R_MASK       0xFFFFFFFFu

#define TPU_E_GCR_EM2R_EM2R_SHIFT      0u

#define TPU_E_GCR_EM2R_EM2R_WIDTH      32u

#define TPU_E_GCR_EM2R_EM2R(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_EM2R_EM2R_SHIFT))&TPU_E_GCR_EM2R_EM2R_MASK)

/* GCR_EM2R Reg Mask */

#define TPU_E_GCR_EM2R_MASK            0xFFFFFFFFu



/* GCR_ET1R Bit Fields */

#define TPU_E_GCR_ET1R_ET1R_MASK       0xFFFFFFFFu

#define TPU_E_GCR_ET1R_ET1R_SHIFT      0u

#define TPU_E_GCR_ET1R_ET1R_WIDTH      32u

#define TPU_E_GCR_ET1R_ET1R(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_ET1R_ET1R_SHIFT))&TPU_E_GCR_ET1R_ET1R_MASK)

/* GCR_ET1R Reg Mask */

#define TPU_E_GCR_ET1R_MASK            0xFFFFFFFFu



/* GCR_ET2R Bit Fields */

#define TPU_E_GCR_ET2R_ET2R_MASK       0xFFFFFFFFu

#define TPU_E_GCR_ET2R_ET2R_SHIFT      0u

#define TPU_E_GCR_ET2R_ET2R_WIDTH      32u

#define TPU_E_GCR_ET2R_ET2R(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_ET2R_ET2R_SHIFT))&TPU_E_GCR_ET2R_ET2R_MASK)

/* GCR_ET2R Reg Mask */

#define TPU_E_GCR_ET2R_MASK            0xFFFFFFFFu



/* GCR_VHSR Bit Fields */

#define TPU_E_GCR_VHSR_HSR_MASK        0xFFFFFFFFu

#define TPU_E_GCR_VHSR_HSR_SHIFT       0u

#define TPU_E_GCR_VHSR_HSR_WIDTH       32u

#define TPU_E_GCR_VHSR_HSR(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_VHSR_HSR_SHIFT))&TPU_E_GCR_VHSR_HSR_MASK)

/* GCR_VHSR Reg Mask */

#define TPU_E_GCR_VHSR_MASK            0xFFFFFFFFu



/* GCR_AFGR Bit Fields */

#define TPU_E_GCR_AFGR_FLT_GRD_MASK    0x3FFFu

#define TPU_E_GCR_AFGR_FLT_GRD_SHIFT   0u

#define TPU_E_GCR_AFGR_FLT_GRD_WIDTH   14u

#define TPU_E_GCR_AFGR_FLT_GRD(x)      (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_AFGR_FLT_GRD_SHIFT))&TPU_E_GCR_AFGR_FLT_GRD_MASK)

/* GCR_AFGR Reg Mask */

#define TPU_E_GCR_AFGR_MASK            0x00003FFFu



/* GCR_ASR Bit Fields */

#define TPU_E_GCR_ASR_ERROR_MASK       0x80000000u

#define TPU_E_GCR_ASR_ERROR_SHIFT      31u

#define TPU_E_GCR_ASR_ERROR_WIDTH      1u

#define TPU_E_GCR_ASR_ERROR(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_ASR_ERROR_SHIFT))&TPU_E_GCR_ASR_ERROR_MASK)

#define TPU_E_GCR_ASR_ENDIAN_MASK      0x1u

#define TPU_E_GCR_ASR_ENDIAN_SHIFT     0u

#define TPU_E_GCR_ASR_ENDIAN_WIDTH     1u

#define TPU_E_GCR_ASR_ENDIAN(x)        (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_ASR_ENDIAN_SHIFT))&TPU_E_GCR_ASR_ENDIAN_MASK)

/* GCR_ASR Reg Mask */

#define TPU_E_GCR_ASR_MASK             0x80000001u



/* GCR_AID Bit Fields */

#define TPU_E_GCR_AID_ETCS_MASK        0x1F000u

#define TPU_E_GCR_AID_ETCS_SHIFT       12u

#define TPU_E_GCR_AID_ETCS_WIDTH       5u

#define TPU_E_GCR_AID_ETCS(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_AID_ETCS_SHIFT))&TPU_E_GCR_AID_ETCS_MASK)

#define TPU_E_GCR_AID_COND_MASK        0xF80u

#define TPU_E_GCR_AID_COND_SHIFT       7u

#define TPU_E_GCR_AID_COND_WIDTH       5u

#define TPU_E_GCR_AID_COND(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_AID_COND_SHIFT))&TPU_E_GCR_AID_COND_MASK)

#define TPU_E_GCR_AID_ID_MASK          0x3Fu

#define TPU_E_GCR_AID_ID_SHIFT         0u

#define TPU_E_GCR_AID_ID_WIDTH         6u

#define TPU_E_GCR_AID_ID(x)            (((uint32_t)(((uint32_t)(x))<<TPU_E_GCR_AID_ID_SHIFT))&TPU_E_GCR_AID_ID_MASK)

/* GCR_AID Reg Mask */

#define TPU_E_GCR_AID_MASK             0x0001FFBFu



/* TBR_CR Bit Fields */

#define TPU_E_TBR_CR_TCR1P_MASK        0xFF000000u

#define TPU_E_TBR_CR_TCR1P_SHIFT       24u

#define TPU_E_TBR_CR_TCR1P_WIDTH       8u

#define TPU_E_TBR_CR_TCR1P(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_CR_TCR1P_SHIFT))&TPU_E_TBR_CR_TCR1P_MASK)

#define TPU_E_TBR_CR_TCR1CTL_MASK      0x70000u

#define TPU_E_TBR_CR_TCR1CTL_SHIFT     16u

#define TPU_E_TBR_CR_TCR1CTL_WIDTH     3u

#define TPU_E_TBR_CR_TCR1CTL(x)        (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_CR_TCR1CTL_SHIFT))&TPU_E_TBR_CR_TCR1CTL_MASK)

#define TPU_E_TBR_CR_TCR2P_MASK        0xFC00u

#define TPU_E_TBR_CR_TCR2P_SHIFT       10u

#define TPU_E_TBR_CR_TCR2P_WIDTH       6u

#define TPU_E_TBR_CR_TCR2P(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_CR_TCR2P_SHIFT))&TPU_E_TBR_CR_TCR2P_MASK)

#define TPU_E_TBR_CR_ATGC_MASK         0x80u

#define TPU_E_TBR_CR_ATGC_SHIFT        7u

#define TPU_E_TBR_CR_ATGC_WIDTH        1u

#define TPU_E_TBR_CR_ATGC(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_CR_ATGC_SHIFT))&TPU_E_TBR_CR_ATGC_MASK)

#define TPU_E_TBR_CR_AM_MASK           0x60u

#define TPU_E_TBR_CR_AM_SHIFT          5u

#define TPU_E_TBR_CR_AM_WIDTH          2u

#define TPU_E_TBR_CR_AM(x)             (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_CR_AM_SHIFT))&TPU_E_TBR_CR_AM_MASK)

#define TPU_E_TBR_CR_TCRCF_MASK        0x18u

#define TPU_E_TBR_CR_TCRCF_SHIFT       3u

#define TPU_E_TBR_CR_TCRCF_WIDTH       2u

#define TPU_E_TBR_CR_TCRCF(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_CR_TCRCF_SHIFT))&TPU_E_TBR_CR_TCRCF_MASK)

#define TPU_E_TBR_CR_TCR2CTL_MASK      0x7u

#define TPU_E_TBR_CR_TCR2CTL_SHIFT     0u

#define TPU_E_TBR_CR_TCR2CTL_WIDTH     3u

#define TPU_E_TBR_CR_TCR2CTL(x)        (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_CR_TCR2CTL_SHIFT))&TPU_E_TBR_CR_TCR2CTL_MASK)

/* TBR_CR Reg Mask */

#define TPU_E_TBR_CR_MASK              0xFF07FCFFu



/* TBR_T1R Bit Fields */

#define TPU_E_TBR_T1R_TCR1_MASK        0xFFFFFFu

#define TPU_E_TBR_T1R_TCR1_SHIFT       0u

#define TPU_E_TBR_T1R_TCR1_WIDTH       24u

#define TPU_E_TBR_T1R_TCR1(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_T1R_TCR1_SHIFT))&TPU_E_TBR_T1R_TCR1_MASK)

/* TBR_T1R Reg Mask */

#define TPU_E_TBR_T1R_MASK             0x00FFFFFFu



/* TBR_T2R Bit Fields */

#define TPU_E_TBR_T2R_TCR2_MASK        0xFFFFFFu

#define TPU_E_TBR_T2R_TCR2_SHIFT       0u

#define TPU_E_TBR_T2R_TCR2_WIDTH       24u

#define TPU_E_TBR_T2R_TCR2(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_T2R_TCR2_SHIFT))&TPU_E_TBR_T2R_TCR2_MASK)

/* TBR_T2R Reg Mask */

#define TPU_E_TBR_T2R_MASK             0x00FFFFFFu



/* TBR_TPR Bit Fields */

#define TPU_E_TBR_TPR_LAST_MASK        0x8000u

#define TPU_E_TBR_TPR_LAST_SHIFT       15u

#define TPU_E_TBR_TPR_LAST_WIDTH       1u

#define TPU_E_TBR_TPR_LAST(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_TPR_LAST_SHIFT))&TPU_E_TBR_TPR_LAST_MASK)

#define TPU_E_TBR_TPR_MISSCNT_MASK     0x6000u

#define TPU_E_TBR_TPR_MISSCNT_SHIFT    13u

#define TPU_E_TBR_TPR_MISSCNT_WIDTH    2u

#define TPU_E_TBR_TPR_MISSCNT(x)       (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_TPR_MISSCNT_SHIFT))&TPU_E_TBR_TPR_MISSCNT_MASK)

#define TPU_E_TBR_TPR_IPH_MASK         0x1000u

#define TPU_E_TBR_TPR_IPH_SHIFT        12u

#define TPU_E_TBR_TPR_IPH_WIDTH        1u

#define TPU_E_TBR_TPR_IPH(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_TPR_IPH_SHIFT))&TPU_E_TBR_TPR_IPH_MASK)

#define TPU_E_TBR_TPR_HOLD_MASK        0x800u

#define TPU_E_TBR_TPR_HOLD_SHIFT       11u

#define TPU_E_TBR_TPR_HOLD_WIDTH       1u

#define TPU_E_TBR_TPR_HOLD(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_TPR_HOLD_SHIFT))&TPU_E_TBR_TPR_HOLD_MASK)

#define TPU_E_TBR_TPR_TPR10_MASK       0x400u

#define TPU_E_TBR_TPR_TPR10_SHIFT      10u

#define TPU_E_TBR_TPR_TPR10_WIDTH      1u

#define TPU_E_TBR_TPR_TPR10(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_TPR_TPR10_SHIFT))&TPU_E_TBR_TPR_TPR10_MASK)

#define TPU_E_TBR_TPR_TICKS_MASK       0x3FFu

#define TPU_E_TBR_TPR_TICKS_SHIFT      0u

#define TPU_E_TBR_TPR_TICKS_WIDTH      10u

#define TPU_E_TBR_TPR_TICKS(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_TPR_TICKS_SHIFT))&TPU_E_TBR_TPR_TICKS_MASK)

/* TBR_TPR Reg Mask */

#define TPU_E_TBR_TPR_MASK             0x0000FFFFu



/* TBR_TRR Bit Fields */

#define TPU_E_TBR_TRR_INTEGER_MASK     0xFFFE00u

#define TPU_E_TBR_TRR_INTEGER_SHIFT    9u

#define TPU_E_TBR_TRR_INTEGER_WIDTH    15u

#define TPU_E_TBR_TRR_INTEGER(x)       (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_TRR_INTEGER_SHIFT))&TPU_E_TBR_TRR_INTEGER_MASK)

#define TPU_E_TBR_TRR_FRACTION_MASK    0x1FFu

#define TPU_E_TBR_TRR_FRACTION_SHIFT   0u

#define TPU_E_TBR_TRR_FRACTION_WIDTH   9u

#define TPU_E_TBR_TRR_FRACTION(x)      (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_TRR_FRACTION_SHIFT))&TPU_E_TBR_TRR_FRACTION_MASK)

/* TBR_TRR Reg Mask */

#define TPU_E_TBR_TRR_MASK             0x00FFFFFFu



/* TBR_T1MR Bit Fields */

#define TPU_E_TBR_T1MR_OVF_MASK        0x80000000u

#define TPU_E_TBR_T1MR_OVF_SHIFT       31u

#define TPU_E_TBR_T1MR_OVF_WIDTH       1u

#define TPU_E_TBR_T1MR_OVF(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_T1MR_OVF_SHIFT))&TPU_E_TBR_T1MR_OVF_MASK)

#define TPU_E_TBR_T1MR_IRQ_EN_MASK     0x8000000u

#define TPU_E_TBR_T1MR_IRQ_EN_SHIFT    27u

#define TPU_E_TBR_T1MR_IRQ_EN_WIDTH    1u

#define TPU_E_TBR_T1MR_IRQ_EN(x)       (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_T1MR_IRQ_EN_SHIFT))&TPU_E_TBR_T1MR_IRQ_EN_MASK)

#define TPU_E_TBR_T1MR_MAX_MASK        0xFFFFFFu

#define TPU_E_TBR_T1MR_MAX_SHIFT       0u

#define TPU_E_TBR_T1MR_MAX_WIDTH       24u

#define TPU_E_TBR_T1MR_MAX(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_T1MR_MAX_SHIFT))&TPU_E_TBR_T1MR_MAX_MASK)

/* TBR_T1MR Reg Mask */

#define TPU_E_TBR_T1MR_MASK            0x88FFFFFFu



/* TBR_T2MR Bit Fields */

#define TPU_E_TBR_T2MR_OVF_MASK        0x80000000u

#define TPU_E_TBR_T2MR_OVF_SHIFT       31u

#define TPU_E_TBR_T2MR_OVF_WIDTH       1u

#define TPU_E_TBR_T2MR_OVF(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_T2MR_OVF_SHIFT))&TPU_E_TBR_T2MR_OVF_MASK)

#define TPU_E_TBR_T2MR_IRQ_EN_MASK     0x8000000u

#define TPU_E_TBR_T2MR_IRQ_EN_SHIFT    27u

#define TPU_E_TBR_T2MR_IRQ_EN_WIDTH    1u

#define TPU_E_TBR_T2MR_IRQ_EN(x)       (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_T2MR_IRQ_EN_SHIFT))&TPU_E_TBR_T2MR_IRQ_EN_MASK)

#define TPU_E_TBR_T2MR_MAX_MASK        0xFFFFFFu

#define TPU_E_TBR_T2MR_MAX_SHIFT       0u

#define TPU_E_TBR_T2MR_MAX_WIDTH       24u

#define TPU_E_TBR_T2MR_MAX(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_TBR_T2MR_MAX_SHIFT))&TPU_E_TBR_T2MR_MAX_MASK)

/* TBR_T2MR Reg Mask */

#define TPU_E_TBR_T2MR_MASK            0x88FFFFFFu



/* CHn_CR Bit Fields */

#define TPU_E_CHn_CR_CIE_MASK          0x80000000u

#define TPU_E_CHn_CR_CIE_SHIFT         31u

#define TPU_E_CHn_CR_CIE_WIDTH         1u

#define TPU_E_CHn_CR_CIE(x)            (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR_CIE_SHIFT))&TPU_E_CHn_CR_CIE_MASK)

#define TPU_E_CHn_CR_CPR_MASK          0x60000000u

#define TPU_E_CHn_CR_CPR_SHIFT         29u

#define TPU_E_CHn_CR_CPR_WIDTH         2u

#define TPU_E_CHn_CR_CPR(x)            (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR_CPR_SHIFT))&TPU_E_CHn_CR_CPR_MASK)

#define TPU_E_CHn_CR_CFB_MASK          0x10000000u

#define TPU_E_CHn_CR_CFB_SHIFT         28u

#define TPU_E_CHn_CR_CFB_WIDTH         1u

#define TPU_E_CHn_CR_CFB(x)            (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR_CFB_SHIFT))&TPU_E_CHn_CR_CFB_MASK)

#define TPU_E_CHn_CR_CFS_MASK          0xF800000u

#define TPU_E_CHn_CR_CFS_SHIFT         23u

#define TPU_E_CHn_CR_CFS_WIDTH         5u

#define TPU_E_CHn_CR_CFS(x)            (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR_CFS_SHIFT))&TPU_E_CHn_CR_CFS_MASK)

#define TPU_E_CHn_CR_ETPD_MASK         0x400000u

#define TPU_E_CHn_CR_ETPD_SHIFT        22u

#define TPU_E_CHn_CR_ETPD_WIDTH        1u

#define TPU_E_CHn_CR_ETPD(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR_ETPD_SHIFT))&TPU_E_CHn_CR_ETPD_MASK)

#define TPU_E_CHn_CR_ECTS_MASK         0x200000u

#define TPU_E_CHn_CR_ECTS_SHIFT        21u

#define TPU_E_CHn_CR_ECTS_WIDTH        1u

#define TPU_E_CHn_CR_ECTS(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR_ECTS_SHIFT))&TPU_E_CHn_CR_ECTS_MASK)

#define TPU_E_CHn_CR_FLG1_MASK         0x100000u

#define TPU_E_CHn_CR_FLG1_SHIFT        20u

#define TPU_E_CHn_CR_FLG1_WIDTH        1u

#define TPU_E_CHn_CR_FLG1(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR_FLG1_SHIFT))&TPU_E_CHn_CR_FLG1_MASK)

#define TPU_E_CHn_CR_FLG0_MASK         0x80000u

#define TPU_E_CHn_CR_FLG0_SHIFT        19u

#define TPU_E_CHn_CR_FLG0_WIDTH        1u

#define TPU_E_CHn_CR_FLG0(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR_FLG0_SHIFT))&TPU_E_CHn_CR_FLG0_MASK)

#define TPU_E_CHn_CR_OPOL_MASK         0x20000u

#define TPU_E_CHn_CR_OPOL_SHIFT        17u

#define TPU_E_CHn_CR_OPOL_WIDTH        1u

#define TPU_E_CHn_CR_OPOL(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR_OPOL_SHIFT))&TPU_E_CHn_CR_OPOL_MASK)

#define TPU_E_CHn_CR_ODIS_MASK         0x10000u

#define TPU_E_CHn_CR_ODIS_SHIFT        16u

#define TPU_E_CHn_CR_ODIS_WIDTH        1u

#define TPU_E_CHn_CR_ODIS(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR_ODIS_SHIFT))&TPU_E_CHn_CR_ODIS_MASK)

#define TPU_E_CHn_CR_CHSA_MASK         0x7u

#define TPU_E_CHn_CR_CHSA_SHIFT        0u

#define TPU_E_CHn_CR_CHSA_WIDTH        3u

#define TPU_E_CHn_CR_CHSA(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR_CHSA_SHIFT))&TPU_E_CHn_CR_CHSA_MASK)

/* CH0_CR Reg Mask */

#define TPU_E_CHn_CR_MASK              0xFFFB0007u



/* CHn_SR Bit Fields */

#define TPU_E_CHn_SR_CIS_MASK          0x80000000u

#define TPU_E_CHn_SR_CIS_SHIFT         31u

#define TPU_E_CHn_SR_CIS_WIDTH         1u

#define TPU_E_CHn_SR_CIS(x)            (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_SR_CIS_SHIFT))&TPU_E_CHn_SR_CIS_MASK)

#define TPU_E_CHn_SR_CHRS_MASK         0x1000000u

#define TPU_E_CHn_SR_CHRS_SHIFT        24u

#define TPU_E_CHn_SR_CHRS_WIDTH        1u

#define TPU_E_CHn_SR_CHRS(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_SR_CHRS_SHIFT))&TPU_E_CHn_SR_CHRS_MASK)

#define TPU_E_CHn_SR_CHRI_MASK         0x70000u

#define TPU_E_CHn_SR_CHRI_SHIFT        16u

#define TPU_E_CHn_SR_CHRI_WIDTH        3u

#define TPU_E_CHn_SR_CHRI(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_SR_CHRI_SHIFT))&TPU_E_CHn_SR_CHRI_MASK)

#define TPU_E_CHn_SR_CEIS_MASK         0x8000u

#define TPU_E_CHn_SR_CEIS_SHIFT        15u

#define TPU_E_CHn_SR_CEIS_WIDTH        1u

#define TPU_E_CHn_SR_CEIS(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_SR_CEIS_SHIFT))&TPU_E_CHn_SR_CEIS_MASK)

#define TPU_E_CHn_SR_CHDS_MASK         0x4000u

#define TPU_E_CHn_SR_CHDS_SHIFT        14u

#define TPU_E_CHn_SR_CHDS_WIDTH        1u

#define TPU_E_CHn_SR_CHDS(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_SR_CHDS_SHIFT))&TPU_E_CHn_SR_CHDS_MASK)

#define TPU_E_CHn_SR_CTS_MASK          0x1000u

#define TPU_E_CHn_SR_CTS_SHIFT         12u

#define TPU_E_CHn_SR_CTS_WIDTH         1u

#define TPU_E_CHn_SR_CTS(x)            (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_SR_CTS_SHIFT))&TPU_E_CHn_SR_CTS_MASK)

#define TPU_E_CHn_SR_CHAS_MASK         0x100u

#define TPU_E_CHn_SR_CHAS_SHIFT        8u

#define TPU_E_CHn_SR_CHAS_WIDTH        1u

#define TPU_E_CHn_SR_CHAS(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_SR_CHAS_SHIFT))&TPU_E_CHn_SR_CHAS_MASK)

/* CH0_SR Reg Mask */

#define TPU_E_CHn_SR_MASK              0x8107D100u



/* CHn_SCR Bit Fields */

#define TPU_E_CHn_SCR_CISC_MASK        0x80000000u

#define TPU_E_CHn_SCR_CISC_SHIFT       31u

#define TPU_E_CHn_SCR_CISC_WIDTH       1u

#define TPU_E_CHn_SCR_CISC(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_SCR_CISC_SHIFT))&TPU_E_CHn_SCR_CISC_MASK)

#define TPU_E_CHn_SCR_CHDT_MASK        0x40000000u

#define TPU_E_CHn_SCR_CHDT_SHIFT       30u

#define TPU_E_CHn_SCR_CHDT_WIDTH       1u

#define TPU_E_CHn_SCR_CHDT(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_SCR_CHDT_SHIFT))&TPU_E_CHn_SCR_CHDT_MASK)

#define TPU_E_CHn_SCR_CHRC_MASK        0x1000000u

#define TPU_E_CHn_SCR_CHRC_SHIFT       24u

#define TPU_E_CHn_SCR_CHRC_WIDTH       1u

#define TPU_E_CHn_SCR_CHRC(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_SCR_CHRC_SHIFT))&TPU_E_CHn_SCR_CHRC_MASK)

#define TPU_E_CHn_SCR_CHAT_MASK        0x10000u

#define TPU_E_CHn_SCR_CHAT_SHIFT       16u

#define TPU_E_CHn_SCR_CHAT_WIDTH       1u

#define TPU_E_CHn_SCR_CHAT(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_SCR_CHAT_SHIFT))&TPU_E_CHn_SCR_CHAT_MASK)

/* CH0_SCR Reg Mask */

#define TPU_E_CHn_SCR_MASK             0xC1010000u



/* CHn_EFR Bit Fields */

#define TPU_E_CHn_EFR_CSR_MASK         0x80000000u

#define TPU_E_CHn_EFR_CSR_SHIFT        31u

#define TPU_E_CHn_EFR_CSR_WIDTH        1u

#define TPU_E_CHn_EFR_CSR(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_EFR_CSR_SHIFT))&TPU_E_CHn_EFR_CSR_MASK)

#define TPU_E_CHn_EFR_CHSR_MASK        0x40000000u

#define TPU_E_CHn_EFR_CHSR_SHIFT       30u

#define TPU_E_CHn_EFR_CHSR_WIDTH       1u

#define TPU_E_CHn_EFR_CHSR(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_EFR_CHSR_SHIFT))&TPU_E_CHn_EFR_CHSR_MASK)

#define TPU_E_CHn_EFR_EMRL1_MASK       0x200u

#define TPU_E_CHn_EFR_EMRL1_SHIFT      9u

#define TPU_E_CHn_EFR_EMRL1_WIDTH      1u

#define TPU_E_CHn_EFR_EMRL1(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_EFR_EMRL1_SHIFT))&TPU_E_CHn_EFR_EMRL1_MASK)

#define TPU_E_CHn_EFR_EMRL2_MASK       0x100u

#define TPU_E_CHn_EFR_EMRL2_SHIFT      8u

#define TPU_E_CHn_EFR_EMRL2_WIDTH      1u

#define TPU_E_CHn_EFR_EMRL2(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_EFR_EMRL2_SHIFT))&TPU_E_CHn_EFR_EMRL2_MASK)

#define TPU_E_CHn_EFR_ETDL1_MASK       0x80u

#define TPU_E_CHn_EFR_ETDL1_SHIFT      7u

#define TPU_E_CHn_EFR_ETDL1_WIDTH      1u

#define TPU_E_CHn_EFR_ETDL1(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_EFR_ETDL1_SHIFT))&TPU_E_CHn_EFR_ETDL1_MASK)

#define TPU_E_CHn_EFR_ETDL2_MASK       0x40u

#define TPU_E_CHn_EFR_ETDL2_SHIFT      6u

#define TPU_E_CHn_EFR_ETDL2_WIDTH      1u

#define TPU_E_CHn_EFR_ETDL2(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_EFR_ETDL2_SHIFT))&TPU_E_CHn_EFR_ETDL2_MASK)

#define TPU_E_CHn_EFR_MRLE1_MASK       0x20u

#define TPU_E_CHn_EFR_MRLE1_SHIFT      5u

#define TPU_E_CHn_EFR_MRLE1_WIDTH      1u

#define TPU_E_CHn_EFR_MRLE1(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_EFR_MRLE1_SHIFT))&TPU_E_CHn_EFR_MRLE1_MASK)

#define TPU_E_CHn_EFR_MRLE2_MASK       0x10u

#define TPU_E_CHn_EFR_MRLE2_SHIFT      4u

#define TPU_E_CHn_EFR_MRLE2_WIDTH      1u

#define TPU_E_CHn_EFR_MRLE2(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_EFR_MRLE2_SHIFT))&TPU_E_CHn_EFR_MRLE2_MASK)

#define TPU_E_CHn_EFR_MRL1_MASK        0x8u

#define TPU_E_CHn_EFR_MRL1_SHIFT       3u

#define TPU_E_CHn_EFR_MRL1_WIDTH       1u

#define TPU_E_CHn_EFR_MRL1(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_EFR_MRL1_SHIFT))&TPU_E_CHn_EFR_MRL1_MASK)

#define TPU_E_CHn_EFR_MRL2_MASK        0x4u

#define TPU_E_CHn_EFR_MRL2_SHIFT       2u

#define TPU_E_CHn_EFR_MRL2_WIDTH       1u

#define TPU_E_CHn_EFR_MRL2(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_EFR_MRL2_SHIFT))&TPU_E_CHn_EFR_MRL2_MASK)

#define TPU_E_CHn_EFR_TDL1_MASK        0x2u

#define TPU_E_CHn_EFR_TDL1_SHIFT       1u

#define TPU_E_CHn_EFR_TDL1_WIDTH       1u

#define TPU_E_CHn_EFR_TDL1(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_EFR_TDL1_SHIFT))&TPU_E_CHn_EFR_TDL1_MASK)

#define TPU_E_CHn_EFR_TDL2_MASK        0x1u

#define TPU_E_CHn_EFR_TDL2_SHIFT       0u

#define TPU_E_CHn_EFR_TDL2_WIDTH       1u

#define TPU_E_CHn_EFR_TDL2(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_EFR_TDL2_SHIFT))&TPU_E_CHn_EFR_TDL2_MASK)

/* CH0_EFR Reg Mask */

#define TPU_E_CHn_EFR_MASK             0xC00003FFu



/* CHn_CR2 Bit Fields */

#define TPU_E_CHn_CR2_TBS1_MASK        0xE0000000u

#define TPU_E_CHn_CR2_TBS1_SHIFT       29u

#define TPU_E_CHn_CR2_TBS1_WIDTH       3u

#define TPU_E_CHn_CR2_TBS1(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR2_TBS1_SHIFT))&TPU_E_CHn_CR2_TBS1_MASK)

#define TPU_E_CHn_CR2_PSTI_MASK        0x10000000u

#define TPU_E_CHn_CR2_PSTI_SHIFT       28u

#define TPU_E_CHn_CR2_PSTI_WIDTH       1u

#define TPU_E_CHn_CR2_PSTI(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR2_PSTI_SHIFT))&TPU_E_CHn_CR2_PSTI_MASK)

#define TPU_E_CHn_CR2_PSTO_MASK        0x8000000u

#define TPU_E_CHn_CR2_PSTO_SHIFT       27u

#define TPU_E_CHn_CR2_PSTO_WIDTH       1u

#define TPU_E_CHn_CR2_PSTO(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR2_PSTO_SHIFT))&TPU_E_CHn_CR2_PSTO_MASK)

#define TPU_E_CHn_CR2_PRSS_MASK        0x4000000u

#define TPU_E_CHn_CR2_PRSS_SHIFT       26u

#define TPU_E_CHn_CR2_PRSS_WIDTH       1u

#define TPU_E_CHn_CR2_PRSS(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR2_PRSS_SHIFT))&TPU_E_CHn_CR2_PRSS_MASK)

#define TPU_E_CHn_CR2_IPAC1_MASK       0x700000u

#define TPU_E_CHn_CR2_IPAC1_SHIFT      20u

#define TPU_E_CHn_CR2_IPAC1_WIDTH      3u

#define TPU_E_CHn_CR2_IPAC1(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR2_IPAC1_SHIFT))&TPU_E_CHn_CR2_IPAC1_MASK)

#define TPU_E_CHn_CR2_OBE_MASK         0x80000u

#define TPU_E_CHn_CR2_OBE_SHIFT        19u

#define TPU_E_CHn_CR2_OBE_WIDTH        1u

#define TPU_E_CHn_CR2_OBE(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR2_OBE_SHIFT))&TPU_E_CHn_CR2_OBE_MASK)

#define TPU_E_CHn_CR2_OPAC1_MASK       0x70000u

#define TPU_E_CHn_CR2_OPAC1_SHIFT      16u

#define TPU_E_CHn_CR2_OPAC1_WIDTH      3u

#define TPU_E_CHn_CR2_OPAC1(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR2_OPAC1_SHIFT))&TPU_E_CHn_CR2_OPAC1_MASK)

#define TPU_E_CHn_CR2_TBS2_MASK        0xE000u

#define TPU_E_CHn_CR2_TBS2_SHIFT       13u

#define TPU_E_CHn_CR2_TBS2_WIDTH       3u

#define TPU_E_CHn_CR2_TBS2(x)          (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR2_TBS2_SHIFT))&TPU_E_CHn_CR2_TBS2_MASK)

#define TPU_E_CHn_CR2_IPAC2_MASK       0x70u

#define TPU_E_CHn_CR2_IPAC2_SHIFT      4u

#define TPU_E_CHn_CR2_IPAC2_WIDTH      3u

#define TPU_E_CHn_CR2_IPAC2(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR2_IPAC2_SHIFT))&TPU_E_CHn_CR2_IPAC2_MASK)

#define TPU_E_CHn_CR2_OPAC2_MASK       0x7u

#define TPU_E_CHn_CR2_OPAC2_SHIFT      0u

#define TPU_E_CHn_CR2_OPAC2_WIDTH      3u

#define TPU_E_CHn_CR2_OPAC2(x)         (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_CR2_OPAC2_SHIFT))&TPU_E_CHn_CR2_OPAC2_MASK)

/* CH0_CR2 Reg Mask */

#define TPU_E_CHn_CR2_MASK             0xFC7FE077u



/* CHn_MR Bit Fields */

#define TPU_E_CHn_MR_SRIE_MASK         0x80000000u

#define TPU_E_CHn_MR_SRIE_SHIFT        31u

#define TPU_E_CHn_MR_SRIE_WIDTH        1u

#define TPU_E_CHn_MR_SRIE(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_MR_SRIE_SHIFT))&TPU_E_CHn_MR_SRIE_MASK)

#define TPU_E_CHn_MR_SRI_MASK          0x40000000u

#define TPU_E_CHn_MR_SRI_SHIFT         30u

#define TPU_E_CHn_MR_SRI_WIDTH         1u

#define TPU_E_CHn_MR_SRI(x)            (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_MR_SRI_SHIFT))&TPU_E_CHn_MR_SRI_MASK)

#define TPU_E_CHn_MR_PDME_MASK         0x100000u

#define TPU_E_CHn_MR_PDME_SHIFT        20u

#define TPU_E_CHn_MR_PDME_WIDTH        1u

#define TPU_E_CHn_MR_PDME(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_MR_PDME_SHIFT))&TPU_E_CHn_MR_PDME_MASK)

#define TPU_E_CHn_MR_PDCM_MASK         0xF0000u

#define TPU_E_CHn_MR_PDCM_SHIFT        16u

#define TPU_E_CHn_MR_PDCM_WIDTH        4u

#define TPU_E_CHn_MR_PDCM(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_MR_PDCM_SHIFT))&TPU_E_CHn_MR_PDCM_MASK)

#define TPU_E_CHn_MR_TCCE_MASK         0x8000u

#define TPU_E_CHn_MR_TCCE_SHIFT        15u

#define TPU_E_CHn_MR_TCCE_WIDTH        1u

#define TPU_E_CHn_MR_TCCE(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_MR_TCCE_SHIFT))&TPU_E_CHn_MR_TCCE_MASK)

#define TPU_E_CHn_MR_UDME_MASK         0x4000u

#define TPU_E_CHn_MR_UDME_SHIFT        14u

#define TPU_E_CHn_MR_UDME_WIDTH        1u

#define TPU_E_CHn_MR_UDME(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_MR_UDME_SHIFT))&TPU_E_CHn_MR_UDME_MASK)

#define TPU_E_CHn_MR_UDCM_MASK         0x3FFFu

#define TPU_E_CHn_MR_UDCM_SHIFT        0u

#define TPU_E_CHn_MR_UDCM_WIDTH        14u

#define TPU_E_CHn_MR_UDCM(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_MR_UDCM_SHIFT))&TPU_E_CHn_MR_UDCM_MASK)

/* CH0_MR Reg Mask */

#define TPU_E_CHn_MR_MASK              0xC01FFFFFu



/* CHn_ER1 Bit Fields */

#define TPU_E_CHn_ER1_ERW_MASK         0x80000000u

#define TPU_E_CHn_ER1_ERW_SHIFT        31u

#define TPU_E_CHn_ER1_ERW_WIDTH        1u

#define TPU_E_CHn_ER1_ERW(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_ER1_ERW_SHIFT))&TPU_E_CHn_ER1_ERW_MASK)

#define TPU_E_CHn_ER1_MEF_MASK         0x2000000u

#define TPU_E_CHn_ER1_MEF_SHIFT        25u

#define TPU_E_CHn_ER1_MEF_WIDTH        1u

#define TPU_E_CHn_ER1_MEF(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_ER1_MEF_SHIFT))&TPU_E_CHn_ER1_MEF_MASK)

#define TPU_E_CHn_ER1_ERS_MASK         0x1000000u

#define TPU_E_CHn_ER1_ERS_SHIFT        24u

#define TPU_E_CHn_ER1_ERS_WIDTH        1u

#define TPU_E_CHn_ER1_ERS(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_ER1_ERS_SHIFT))&TPU_E_CHn_ER1_ERS_MASK)

#define TPU_E_CHn_ER1_ER1_MASK         0xFFFFFFu

#define TPU_E_CHn_ER1_ER1_SHIFT        0u

#define TPU_E_CHn_ER1_ER1_WIDTH        24u

#define TPU_E_CHn_ER1_ER1(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_ER1_ER1_SHIFT))&TPU_E_CHn_ER1_ER1_MASK)

/* CH0_ER1 Reg Mask */

#define TPU_E_CHn_ER1_MASK             0x83FFFFFFu



/* CHn_ER2 Bit Fields */

#define TPU_E_CHn_ER2_ERW_MASK         0x80000000u

#define TPU_E_CHn_ER2_ERW_SHIFT        31u

#define TPU_E_CHn_ER2_ERW_WIDTH        1u

#define TPU_E_CHn_ER2_ERW(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_ER2_ERW_SHIFT))&TPU_E_CHn_ER2_ERW_MASK)

#define TPU_E_CHn_ER2_ER2_MASK         0xFFFFFFu

#define TPU_E_CHn_ER2_ER2_SHIFT        0u

#define TPU_E_CHn_ER2_ER2_WIDTH        24u

#define TPU_E_CHn_ER2_ER2(x)           (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_ER2_ER2_SHIFT))&TPU_E_CHn_ER2_ER2_MASK)

/* CH0_ER2 Reg Mask */

#define TPU_E_CHn_ER2_MASK             0x80FFFFFFu



/* CHn_ECR Bit Fields */

#define TPU_E_CHn_ECR_MRE1_CLR_MASK    0x80000000u

#define TPU_E_CHn_ECR_MRE1_CLR_SHIFT   31u

#define TPU_E_CHn_ECR_MRE1_CLR_WIDTH   1u

#define TPU_E_CHn_ECR_MRE1_CLR(x)      (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_ECR_MRE1_CLR_SHIFT))&TPU_E_CHn_ECR_MRE1_CLR_MASK)

#define TPU_E_CHn_ECR_MRL1_CLR_MASK    0x40000000u

#define TPU_E_CHn_ECR_MRL1_CLR_SHIFT   30u

#define TPU_E_CHn_ECR_MRL1_CLR_WIDTH   1u

#define TPU_E_CHn_ECR_MRL1_CLR(x)      (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_ECR_MRL1_CLR_SHIFT))&TPU_E_CHn_ECR_MRL1_CLR_MASK)

#define TPU_E_CHn_ECR_TDL1_CLR_MASK    0x20000000u

#define TPU_E_CHn_ECR_TDL1_CLR_SHIFT   29u

#define TPU_E_CHn_ECR_TDL1_CLR_WIDTH   1u

#define TPU_E_CHn_ECR_TDL1_CLR(x)      (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_ECR_TDL1_CLR_SHIFT))&TPU_E_CHn_ECR_TDL1_CLR_MASK)

#define TPU_E_CHn_ECR_MRE2_CLR_MASK    0x8000u

#define TPU_E_CHn_ECR_MRE2_CLR_SHIFT   15u

#define TPU_E_CHn_ECR_MRE2_CLR_WIDTH   1u

#define TPU_E_CHn_ECR_MRE2_CLR(x)      (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_ECR_MRE2_CLR_SHIFT))&TPU_E_CHn_ECR_MRE2_CLR_MASK)

#define TPU_E_CHn_ECR_MRL2_CLR_MASK    0x4000u

#define TPU_E_CHn_ECR_MRL2_CLR_SHIFT   14u

#define TPU_E_CHn_ECR_MRL2_CLR_WIDTH   1u

#define TPU_E_CHn_ECR_MRL2_CLR(x)      (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_ECR_MRL2_CLR_SHIFT))&TPU_E_CHn_ECR_MRL2_CLR_MASK)

#define TPU_E_CHn_ECR_TDL2_CLR_MASK    0x2000u

#define TPU_E_CHn_ECR_TDL2_CLR_SHIFT   13u

#define TPU_E_CHn_ECR_TDL2_CLR_WIDTH   1u

#define TPU_E_CHn_ECR_TDL2_CLR(x)      (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_ECR_TDL2_CLR_SHIFT))&TPU_E_CHn_ECR_TDL2_CLR_MASK)

/* CH0_ECR Reg Mask */

#define TPU_E_CHn_ECR_MASK             0xE000E000u



/* CHn_OCR Bit Fields */

#define TPU_E_CHn_OCR_OUT_HIS_MASK     0x1000u

#define TPU_E_CHn_OCR_OUT_HIS_SHIFT    12u

#define TPU_E_CHn_OCR_OUT_HIS_WIDTH    1u

#define TPU_E_CHn_OCR_OUT_HIS(x)       (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_OCR_OUT_HIS_SHIFT))&TPU_E_CHn_OCR_OUT_HIS_MASK)

#define TPU_E_CHn_OCR_OUT_OP1_MASK     0x800u

#define TPU_E_CHn_OCR_OUT_OP1_SHIFT    11u

#define TPU_E_CHn_OCR_OUT_OP1_WIDTH    1u

#define TPU_E_CHn_OCR_OUT_OP1(x)       (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_OCR_OUT_OP1_SHIFT))&TPU_E_CHn_OCR_OUT_OP1_MASK)

#define TPU_E_CHn_OCR_OUT_OP2_MASK     0x400u

#define TPU_E_CHn_OCR_OUT_OP2_SHIFT    10u

#define TPU_E_CHn_OCR_OUT_OP2_WIDTH    1u

#define TPU_E_CHn_OCR_OUT_OP2(x)       (((uint32_t)(((uint32_t)(x))<<TPU_E_CHn_OCR_OUT_OP2_SHIFT))&TPU_E_CHn_OCR_OUT_OP2_MASK)

/* CH0_OCR Reg Mask */

#define TPU_E_CHn_OCR_MASK             0x00001C00u





/*!

 * @}

 */ /* end of group TPU_E_Register_Masks */



/*!

 * @}

 */ /* end of group TPU_E_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
