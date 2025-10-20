#ifndef _FC7240_MSC_NU_Tztufn7_REGS_H_
#define _FC7240_MSC_NU_Tztufn7_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- MSC Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup MSC_Peripheral_Access_Layer MSC Peripheral Access Layer

 * @{

 */



/** MSC - Size of Registers Arrays */



/** MSC - Register Layout Typedef */



typedef struct {



  __IO uint32_t GCR                           ; /* Global Control Register, offset: 0x00 */

  __O  uint32_t CCULR                         ; /* Channel Control Unlock Register, offset: 0x04 */

       uint8_t  RESERVED_0[8];

  __IO uint32_t RCCSR                         ; /* Reception Channel Control and Status Register, offset: 0x10 */

  __IO uint32_t TCCTR                         ; /* Transmitting Channel Control Register, offset: 0x14 */

  __IO uint32_t TCSTR                         ; /* Transmitting Channel Status Register, offset: 0x18 */

  __IO uint32_t TCDAR                         ; /* Transmitting Channel Data Register, offset: 0x1c */

  __IO uint32_t TCCOR                         ; /* Transmitting Channel Command Register, offset: 0x20 */

  __IO uint32_t TCSLR                         ; /* Transmitting Channel Source Selection Low Register, offset: 0x24 */

  __IO uint32_t TCSHR                         ; /* Transmitting Channel Source Selection High Register, offset: 0x28 */

  __IO uint32_t TCELR                         ; /* Transmitting Channel Emergency Load Register, offset: 0x2c */

  __IO uint32_t RDR0                          ; /* Reception Data Register0, offset: 0x30 */

  __IO uint32_t RDR1                          ; /* Reception Data Register1, offset: 0x34 */

  __IO uint32_t RDR2                          ; /* Reception Data Register2, offset: 0x38 */

  __IO uint32_t RDR3                          ; /* Reception Data Register3, offset: 0x3c */

  __IO uint32_t INCR                          ; /* Interrupt Control Register, offset: 0x40 */

  __I  uint32_t INSR                          ; /* Interrupt Status Register, offset: 0x44 */

  __O  uint32_t ISCR                          ; /* Interrupt Set/Clear Register, offset: 0x48 */

  __IO uint32_t IOCR                          ; /* Input/Output Control Register, offset: 0x4c */

       uint8_t  RESERVED_1[8];

  __IO uint32_t TCCTR1                        ; /* Transmitting Channel Control Register1, offset: 0x58 */

  __IO uint32_t RTOR                          ; /* Reception Timeout Register, offset: 0x5c */

       uint8_t  RESERVED_2[140];

  __IO uint32_t SRCR                          ; /* Software Reset Clear Register, offset: 0xec */

       uint8_t  RESERVED_3[4];

  __IO uint32_t MSR                           ; /* Software Reset Register, offset: 0xf4 */



} MSC_Type, *MSC_MemMapPtr;



/** Number of instances of the MSC module. */

#define MSC_INSTANCE_COUNT                       (1u)



/* MSC - Peripheral instance base addresses */

/** Peripheral MSC base address */

#define MSC0_BASE                                 (0x40474000u)

/** Peripheral MSC base pointer */

#define MSC0                                     ((MSC_Type *)MSC0_BASE)

/** Array initializer of MSC peripheral base addresses */

#define MSC_BASE_ADDRS                           {MSC0_BASE}

/** Array initializer of MSC peripheral base pointers */

#define MSC_BASE_PTRS                            {MSC0}

// need fill by yourself

///** Number of interrupt vector arrays for the MSC module. */

//#define MSC_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the MSC module. */

//#define MSC_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the MSC peripheral type */

//#define MSC_IRQS                                 {MSC_IRQn}





/* ----------------------------------------------------------------------------

   -- MSC Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup MSC_Register_Masks MSC Register Masks

 * @{

 */



/* GCR Bit Fields */

#define MSC_GCR_WP_EN_MASK             0x2u

#define MSC_GCR_WP_EN_SHIFT            1u

#define MSC_GCR_WP_EN_WIDTH            1u

#define MSC_GCR_WP_EN(x)               (((uint32_t)(((uint32_t)(x))<<MSC_GCR_WP_EN_SHIFT))&MSC_GCR_WP_EN_MASK)

#define MSC_GCR_EN_MASK                0x1u

#define MSC_GCR_EN_SHIFT               0u

#define MSC_GCR_EN_WIDTH               1u

#define MSC_GCR_EN(x)                  (((uint32_t)(((uint32_t)(x))<<MSC_GCR_EN_SHIFT))&MSC_GCR_EN_MASK)

/* GCR Reg Mask */

#define MSC_GCR_MASK                   0x00000003u



/* CCULR Bit Fields */

#define MSC_CCULR_SEQ_MASK             0xFFFFFFFFu

#define MSC_CCULR_SEQ_SHIFT            0u

#define MSC_CCULR_SEQ_WIDTH            32u

#define MSC_CCULR_SEQ(x)               (((uint32_t)(((uint32_t)(x))<<MSC_CCULR_SEQ_SHIFT))&MSC_CCULR_SEQ_MASK)

/* CCULR Reg Mask */

#define MSC_CCULR_MASK                 0xFFFFFFFFu



/* RCCSR Bit Fields */

#define MSC_RCCSR_RX_BUSY_MASK         0x80000000u

#define MSC_RCCSR_RX_BUSY_SHIFT        31u

#define MSC_RCCSR_RX_BUSY_WIDTH        1u

#define MSC_RCCSR_RX_BUSY(x)           (((uint32_t)(((uint32_t)(x))<<MSC_RCCSR_RX_BUSY_SHIFT))&MSC_RCCSR_RX_BUSY_MASK)

#define MSC_RCCSR_HIDC_MASK            0x20u

#define MSC_RCCSR_HIDC_SHIFT           5u

#define MSC_RCCSR_HIDC_WIDTH           1u

#define MSC_RCCSR_HIDC(x)              (((uint32_t)(((uint32_t)(x))<<MSC_RCCSR_HIDC_SHIFT))&MSC_RCCSR_HIDC_MASK)

#define MSC_RCCSR_PCTL_MASK            0x10u

#define MSC_RCCSR_PCTL_SHIFT           4u

#define MSC_RCCSR_PCTL_WIDTH           1u

#define MSC_RCCSR_PCTL(x)              (((uint32_t)(((uint32_t)(x))<<MSC_RCCSR_PCTL_SHIFT))&MSC_RCCSR_PCTL_MASK)

#define MSC_RCCSR_RBR_MASK             0xEu

#define MSC_RCCSR_RBR_SHIFT            1u

#define MSC_RCCSR_RBR_WIDTH            3u

#define MSC_RCCSR_RBR(x)               (((uint32_t)(((uint32_t)(x))<<MSC_RCCSR_RBR_SHIFT))&MSC_RCCSR_RBR_MASK)

#define MSC_RCCSR_RFT_MASK             0x1u

#define MSC_RCCSR_RFT_SHIFT            0u

#define MSC_RCCSR_RFT_WIDTH            1u

#define MSC_RCCSR_RFT(x)               (((uint32_t)(((uint32_t)(x))<<MSC_RCCSR_RFT_SHIFT))&MSC_RCCSR_RFT_MASK)

/* RCCSR Reg Mask */

#define MSC_RCCSR_MASK                 0x8000003Fu



/* TCCTR Bit Fields */

#define MSC_TCCTR_PL_MASK              0x1F000000u

#define MSC_TCCTR_PL_SHIFT             24u

#define MSC_TCCTR_PL_WIDTH             5u

#define MSC_TCCTR_PL(x)                (((uint32_t)(((uint32_t)(x))<<MSC_TCCTR_PL_SHIFT))&MSC_TCCTR_PL_MASK)

#define MSC_TCCTR_NBS_MASK             0x3F0000u

#define MSC_TCCTR_NBS_SHIFT            16u

#define MSC_TCCTR_NBS_WIDTH            6u

#define MSC_TCCTR_NBS(x)               (((uint32_t)(((uint32_t)(x))<<MSC_TCCTR_NBS_SHIFT))&MSC_TCCTR_NBS_MASK)

#define MSC_TCCTR_TCDIS_MASK           0x8000u

#define MSC_TCCTR_TCDIS_SHIFT          15u

#define MSC_TCCTR_TCDIS_WIDTH          1u

#define MSC_TCCTR_TCDIS(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCCTR_TCDIS_SHIFT))&MSC_TCCTR_TCDIS_MASK)

#define MSC_TCCTR_SELH_MASK            0x4000u

#define MSC_TCCTR_SELH_SHIFT           14u

#define MSC_TCCTR_SELH_WIDTH           1u

#define MSC_TCCTR_SELH(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCCTR_SELH_SHIFT))&MSC_TCCTR_SELH_MASK)

#define MSC_TCCTR_SELL_MASK            0x2000u

#define MSC_TCCTR_SELL_SHIFT           13u

#define MSC_TCCTR_SELL_WIDTH           1u

#define MSC_TCCTR_SELL(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCCTR_SELL_SHIFT))&MSC_TCCTR_SELL_MASK)

#define MSC_TCCTR_NHBS_MASK            0x1F00u

#define MSC_TCCTR_NHBS_SHIFT           8u

#define MSC_TCCTR_NHBS_WIDTH           5u

#define MSC_TCCTR_NHBS(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCCTR_NHBS_SHIFT))&MSC_TCCTR_NHBS_MASK)

#define MSC_TCCTR_NLBS_MASK            0xF8u

#define MSC_TCCTR_NLBS_SHIFT           3u

#define MSC_TCCTR_NLBS_WIDTH           5u

#define MSC_TCCTR_NLBS(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCCTR_NLBS_SHIFT))&MSC_TCCTR_NLBS_MASK)

#define MSC_TCCTR_DTS_MASK             0x4u

#define MSC_TCCTR_DTS_SHIFT            2u

#define MSC_TCCTR_DTS_WIDTH            1u

#define MSC_TCCTR_DTS(x)               (((uint32_t)(((uint32_t)(x))<<MSC_TCCTR_DTS_SHIFT))&MSC_TCCTR_DTS_MASK)

#define MSC_TCCTR_CTS_MASK             0x2u

#define MSC_TCCTR_CTS_SHIFT            1u

#define MSC_TCCTR_CTS_WIDTH            1u

#define MSC_TCCTR_CTS(x)               (((uint32_t)(((uint32_t)(x))<<MSC_TCCTR_CTS_SHIFT))&MSC_TCCTR_CTS_MASK)

#define MSC_TCCTR_WM_MASK              0x1u

#define MSC_TCCTR_WM_SHIFT             0u

#define MSC_TCCTR_WM_WIDTH             1u

#define MSC_TCCTR_WM(x)                (((uint32_t)(((uint32_t)(x))<<MSC_TCCTR_WM_SHIFT))&MSC_TCCTR_WM_MASK)

/* TCCTR Reg Mask */

#define MSC_TCCTR_MASK                 0x1F3FFFFFu



/* TCSTR Bit Fields */

#define MSC_TCSTR_CFB_MASK             0x2000000u

#define MSC_TCSTR_CFB_SHIFT            25u

#define MSC_TCSTR_CFB_WIDTH            1u

#define MSC_TCSTR_CFB(x)               (((uint32_t)(((uint32_t)(x))<<MSC_TCSTR_CFB_SHIFT))&MSC_TCSTR_CFB_MASK)

#define MSC_TCSTR_DFB_MASK             0x1000000u

#define MSC_TCSTR_DFB_SHIFT            24u

#define MSC_TCSTR_DFB_WIDTH            1u

#define MSC_TCSTR_DFB(x)               (((uint32_t)(((uint32_t)(x))<<MSC_TCSTR_DFB_SHIFT))&MSC_TCSTR_DFB_MASK)

#define MSC_TCSTR_NP_MASK              0xF00u

#define MSC_TCSTR_NP_SHIFT             8u

#define MSC_TCSTR_NP_WIDTH             4u

#define MSC_TCSTR_NP(x)                (((uint32_t)(((uint32_t)(x))<<MSC_TCSTR_NP_SHIFT))&MSC_TCSTR_NP_MASK)

/* TCSTR Reg Mask */

#define MSC_TCSTR_MASK                 0x03000F00u



/* TCDAR Bit Fields */

#define MSC_TCDAR_TDH_MASK             0xFFFF0000u

#define MSC_TCDAR_TDH_SHIFT            16u

#define MSC_TCDAR_TDH_WIDTH            16u

#define MSC_TCDAR_TDH(x)               (((uint32_t)(((uint32_t)(x))<<MSC_TCDAR_TDH_SHIFT))&MSC_TCDAR_TDH_MASK)

#define MSC_TCDAR_TDL_MASK             0xFFFFu

#define MSC_TCDAR_TDL_SHIFT            0u

#define MSC_TCDAR_TDL_WIDTH            16u

#define MSC_TCDAR_TDL(x)               (((uint32_t)(((uint32_t)(x))<<MSC_TCDAR_TDL_SHIFT))&MSC_TCDAR_TDL_MASK)

/* TCDAR Reg Mask */

#define MSC_TCDAR_MASK                 0xFFFFFFFFu



/* TCCOR Bit Fields */

#define MSC_TCCOR_TCH_MASK             0xFFFF0000u

#define MSC_TCCOR_TCH_SHIFT            16u

#define MSC_TCCOR_TCH_WIDTH            16u

#define MSC_TCCOR_TCH(x)               (((uint32_t)(((uint32_t)(x))<<MSC_TCCOR_TCH_SHIFT))&MSC_TCCOR_TCH_MASK)

#define MSC_TCCOR_TCL_MASK             0xFFFFu

#define MSC_TCCOR_TCL_SHIFT            0u

#define MSC_TCCOR_TCL_WIDTH            16u

#define MSC_TCCOR_TCL(x)               (((uint32_t)(((uint32_t)(x))<<MSC_TCCOR_TCL_SHIFT))&MSC_TCCOR_TCL_MASK)

/* TCCOR Reg Mask */

#define MSC_TCCOR_MASK                 0xFFFFFFFFu



/* TCSLR Bit Fields */

#define MSC_TCSLR_SSL15_MASK           0xC0000000u

#define MSC_TCSLR_SSL15_SHIFT          30u

#define MSC_TCSLR_SSL15_WIDTH          2u

#define MSC_TCSLR_SSL15(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL15_SHIFT))&MSC_TCSLR_SSL15_MASK)

#define MSC_TCSLR_SSL14_MASK           0x30000000u

#define MSC_TCSLR_SSL14_SHIFT          28u

#define MSC_TCSLR_SSL14_WIDTH          2u

#define MSC_TCSLR_SSL14(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL14_SHIFT))&MSC_TCSLR_SSL14_MASK)

#define MSC_TCSLR_SSL13_MASK           0xC000000u

#define MSC_TCSLR_SSL13_SHIFT          26u

#define MSC_TCSLR_SSL13_WIDTH          2u

#define MSC_TCSLR_SSL13(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL13_SHIFT))&MSC_TCSLR_SSL13_MASK)

#define MSC_TCSLR_SSL12_MASK           0x3000000u

#define MSC_TCSLR_SSL12_SHIFT          24u

#define MSC_TCSLR_SSL12_WIDTH          2u

#define MSC_TCSLR_SSL12(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL12_SHIFT))&MSC_TCSLR_SSL12_MASK)

#define MSC_TCSLR_SSL11_MASK           0xC00000u

#define MSC_TCSLR_SSL11_SHIFT          22u

#define MSC_TCSLR_SSL11_WIDTH          2u

#define MSC_TCSLR_SSL11(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL11_SHIFT))&MSC_TCSLR_SSL11_MASK)

#define MSC_TCSLR_SSL10_MASK           0x300000u

#define MSC_TCSLR_SSL10_SHIFT          20u

#define MSC_TCSLR_SSL10_WIDTH          2u

#define MSC_TCSLR_SSL10(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL10_SHIFT))&MSC_TCSLR_SSL10_MASK)

#define MSC_TCSLR_SSL9_MASK            0xC0000u

#define MSC_TCSLR_SSL9_SHIFT           18u

#define MSC_TCSLR_SSL9_WIDTH           2u

#define MSC_TCSLR_SSL9(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL9_SHIFT))&MSC_TCSLR_SSL9_MASK)

#define MSC_TCSLR_SSL8_MASK            0x30000u

#define MSC_TCSLR_SSL8_SHIFT           16u

#define MSC_TCSLR_SSL8_WIDTH           2u

#define MSC_TCSLR_SSL8(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL8_SHIFT))&MSC_TCSLR_SSL8_MASK)

#define MSC_TCSLR_SSL7_MASK            0xC000u

#define MSC_TCSLR_SSL7_SHIFT           14u

#define MSC_TCSLR_SSL7_WIDTH           2u

#define MSC_TCSLR_SSL7(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL7_SHIFT))&MSC_TCSLR_SSL7_MASK)

#define MSC_TCSLR_SSL6_MASK            0x3000u

#define MSC_TCSLR_SSL6_SHIFT           12u

#define MSC_TCSLR_SSL6_WIDTH           2u

#define MSC_TCSLR_SSL6(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL6_SHIFT))&MSC_TCSLR_SSL6_MASK)

#define MSC_TCSLR_SSL5_MASK            0xC00u

#define MSC_TCSLR_SSL5_SHIFT           10u

#define MSC_TCSLR_SSL5_WIDTH           2u

#define MSC_TCSLR_SSL5(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL5_SHIFT))&MSC_TCSLR_SSL5_MASK)

#define MSC_TCSLR_SSL4_MASK            0x300u

#define MSC_TCSLR_SSL4_SHIFT           8u

#define MSC_TCSLR_SSL4_WIDTH           2u

#define MSC_TCSLR_SSL4(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL4_SHIFT))&MSC_TCSLR_SSL4_MASK)

#define MSC_TCSLR_SSL3_MASK            0xC0u

#define MSC_TCSLR_SSL3_SHIFT           6u

#define MSC_TCSLR_SSL3_WIDTH           2u

#define MSC_TCSLR_SSL3(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL3_SHIFT))&MSC_TCSLR_SSL3_MASK)

#define MSC_TCSLR_SSL2_MASK            0x30u

#define MSC_TCSLR_SSL2_SHIFT           4u

#define MSC_TCSLR_SSL2_WIDTH           2u

#define MSC_TCSLR_SSL2(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL2_SHIFT))&MSC_TCSLR_SSL2_MASK)

#define MSC_TCSLR_SSL1_MASK            0xCu

#define MSC_TCSLR_SSL1_SHIFT           2u

#define MSC_TCSLR_SSL1_WIDTH           2u

#define MSC_TCSLR_SSL1(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL1_SHIFT))&MSC_TCSLR_SSL1_MASK)

#define MSC_TCSLR_SSL0_MASK            0x3u

#define MSC_TCSLR_SSL0_SHIFT           0u

#define MSC_TCSLR_SSL0_WIDTH           2u

#define MSC_TCSLR_SSL0(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSLR_SSL0_SHIFT))&MSC_TCSLR_SSL0_MASK)

/* TCSLR Reg Mask */

#define MSC_TCSLR_MASK                 0xFFFFFFFFu



/* TCSHR Bit Fields */

#define MSC_TCSHR_SSH15_MASK           0xC0000000u

#define MSC_TCSHR_SSH15_SHIFT          30u

#define MSC_TCSHR_SSH15_WIDTH          2u

#define MSC_TCSHR_SSH15(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH15_SHIFT))&MSC_TCSHR_SSH15_MASK)

#define MSC_TCSHR_SSH14_MASK           0x30000000u

#define MSC_TCSHR_SSH14_SHIFT          28u

#define MSC_TCSHR_SSH14_WIDTH          2u

#define MSC_TCSHR_SSH14(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH14_SHIFT))&MSC_TCSHR_SSH14_MASK)

#define MSC_TCSHR_SSH13_MASK           0xC000000u

#define MSC_TCSHR_SSH13_SHIFT          26u

#define MSC_TCSHR_SSH13_WIDTH          2u

#define MSC_TCSHR_SSH13(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH13_SHIFT))&MSC_TCSHR_SSH13_MASK)

#define MSC_TCSHR_SSH12_MASK           0x3000000u

#define MSC_TCSHR_SSH12_SHIFT          24u

#define MSC_TCSHR_SSH12_WIDTH          2u

#define MSC_TCSHR_SSH12(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH12_SHIFT))&MSC_TCSHR_SSH12_MASK)

#define MSC_TCSHR_SSH11_MASK           0xC00000u

#define MSC_TCSHR_SSH11_SHIFT          22u

#define MSC_TCSHR_SSH11_WIDTH          2u

#define MSC_TCSHR_SSH11(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH11_SHIFT))&MSC_TCSHR_SSH11_MASK)

#define MSC_TCSHR_SSH10_MASK           0x300000u

#define MSC_TCSHR_SSH10_SHIFT          20u

#define MSC_TCSHR_SSH10_WIDTH          2u

#define MSC_TCSHR_SSH10(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH10_SHIFT))&MSC_TCSHR_SSH10_MASK)

#define MSC_TCSHR_SSH9_MASK            0xC0000u

#define MSC_TCSHR_SSH9_SHIFT           18u

#define MSC_TCSHR_SSH9_WIDTH           2u

#define MSC_TCSHR_SSH9(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH9_SHIFT))&MSC_TCSHR_SSH9_MASK)

#define MSC_TCSHR_SSH8_MASK            0x30000u

#define MSC_TCSHR_SSH8_SHIFT           16u

#define MSC_TCSHR_SSH8_WIDTH           2u

#define MSC_TCSHR_SSH8(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH8_SHIFT))&MSC_TCSHR_SSH8_MASK)

#define MSC_TCSHR_SSH7_MASK            0xC000u

#define MSC_TCSHR_SSH7_SHIFT           14u

#define MSC_TCSHR_SSH7_WIDTH           2u

#define MSC_TCSHR_SSH7(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH7_SHIFT))&MSC_TCSHR_SSH7_MASK)

#define MSC_TCSHR_SSH6_MASK            0x3000u

#define MSC_TCSHR_SSH6_SHIFT           12u

#define MSC_TCSHR_SSH6_WIDTH           2u

#define MSC_TCSHR_SSH6(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH6_SHIFT))&MSC_TCSHR_SSH6_MASK)

#define MSC_TCSHR_SSH5_MASK            0xC00u

#define MSC_TCSHR_SSH5_SHIFT           10u

#define MSC_TCSHR_SSH5_WIDTH           2u

#define MSC_TCSHR_SSH5(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH5_SHIFT))&MSC_TCSHR_SSH5_MASK)

#define MSC_TCSHR_SSH4_MASK            0x300u

#define MSC_TCSHR_SSH4_SHIFT           8u

#define MSC_TCSHR_SSH4_WIDTH           2u

#define MSC_TCSHR_SSH4(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH4_SHIFT))&MSC_TCSHR_SSH4_MASK)

#define MSC_TCSHR_SSH3_MASK            0xC0u

#define MSC_TCSHR_SSH3_SHIFT           6u

#define MSC_TCSHR_SSH3_WIDTH           2u

#define MSC_TCSHR_SSH3(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH3_SHIFT))&MSC_TCSHR_SSH3_MASK)

#define MSC_TCSHR_SSH2_MASK            0x30u

#define MSC_TCSHR_SSH2_SHIFT           4u

#define MSC_TCSHR_SSH2_WIDTH           2u

#define MSC_TCSHR_SSH2(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH2_SHIFT))&MSC_TCSHR_SSH2_MASK)

#define MSC_TCSHR_SSH1_MASK            0xCu

#define MSC_TCSHR_SSH1_SHIFT           2u

#define MSC_TCSHR_SSH1_WIDTH           2u

#define MSC_TCSHR_SSH1(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH1_SHIFT))&MSC_TCSHR_SSH1_MASK)

#define MSC_TCSHR_SSH0_MASK            0x3u

#define MSC_TCSHR_SSH0_SHIFT           0u

#define MSC_TCSHR_SSH0_WIDTH           2u

#define MSC_TCSHR_SSH0(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCSHR_SSH0_SHIFT))&MSC_TCSHR_SSH0_MASK)

/* TCSHR Reg Mask */

#define MSC_TCSHR_MASK                 0xFFFFFFFFu



/* TCELR Bit Fields */

#define MSC_TCELR_EHE15_MASK           0x80000000u

#define MSC_TCELR_EHE15_SHIFT          31u

#define MSC_TCELR_EHE15_WIDTH          1u

#define MSC_TCELR_EHE15(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE15_SHIFT))&MSC_TCELR_EHE15_MASK)

#define MSC_TCELR_EHE14_MASK           0x40000000u

#define MSC_TCELR_EHE14_SHIFT          30u

#define MSC_TCELR_EHE14_WIDTH          1u

#define MSC_TCELR_EHE14(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE14_SHIFT))&MSC_TCELR_EHE14_MASK)

#define MSC_TCELR_EHE13_MASK           0x20000000u

#define MSC_TCELR_EHE13_SHIFT          29u

#define MSC_TCELR_EHE13_WIDTH          1u

#define MSC_TCELR_EHE13(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE13_SHIFT))&MSC_TCELR_EHE13_MASK)

#define MSC_TCELR_EHE12_MASK           0x10000000u

#define MSC_TCELR_EHE12_SHIFT          28u

#define MSC_TCELR_EHE12_WIDTH          1u

#define MSC_TCELR_EHE12(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE12_SHIFT))&MSC_TCELR_EHE12_MASK)

#define MSC_TCELR_EHE11_MASK           0x8000000u

#define MSC_TCELR_EHE11_SHIFT          27u

#define MSC_TCELR_EHE11_WIDTH          1u

#define MSC_TCELR_EHE11(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE11_SHIFT))&MSC_TCELR_EHE11_MASK)

#define MSC_TCELR_EHE10_MASK           0x4000000u

#define MSC_TCELR_EHE10_SHIFT          26u

#define MSC_TCELR_EHE10_WIDTH          1u

#define MSC_TCELR_EHE10(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE10_SHIFT))&MSC_TCELR_EHE10_MASK)

#define MSC_TCELR_EHE9_MASK            0x2000000u

#define MSC_TCELR_EHE9_SHIFT           25u

#define MSC_TCELR_EHE9_WIDTH           1u

#define MSC_TCELR_EHE9(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE9_SHIFT))&MSC_TCELR_EHE9_MASK)

#define MSC_TCELR_EHE8_MASK            0x1000000u

#define MSC_TCELR_EHE8_SHIFT           24u

#define MSC_TCELR_EHE8_WIDTH           1u

#define MSC_TCELR_EHE8(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE8_SHIFT))&MSC_TCELR_EHE8_MASK)

#define MSC_TCELR_EHE7_MASK            0x800000u

#define MSC_TCELR_EHE7_SHIFT           23u

#define MSC_TCELR_EHE7_WIDTH           1u

#define MSC_TCELR_EHE7(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE7_SHIFT))&MSC_TCELR_EHE7_MASK)

#define MSC_TCELR_EHE6_MASK            0x400000u

#define MSC_TCELR_EHE6_SHIFT           22u

#define MSC_TCELR_EHE6_WIDTH           1u

#define MSC_TCELR_EHE6(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE6_SHIFT))&MSC_TCELR_EHE6_MASK)

#define MSC_TCELR_EHE5_MASK            0x200000u

#define MSC_TCELR_EHE5_SHIFT           21u

#define MSC_TCELR_EHE5_WIDTH           1u

#define MSC_TCELR_EHE5(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE5_SHIFT))&MSC_TCELR_EHE5_MASK)

#define MSC_TCELR_EHE4_MASK            0x100000u

#define MSC_TCELR_EHE4_SHIFT           20u

#define MSC_TCELR_EHE4_WIDTH           1u

#define MSC_TCELR_EHE4(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE4_SHIFT))&MSC_TCELR_EHE4_MASK)

#define MSC_TCELR_EHE3_MASK            0x80000u

#define MSC_TCELR_EHE3_SHIFT           19u

#define MSC_TCELR_EHE3_WIDTH           1u

#define MSC_TCELR_EHE3(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE3_SHIFT))&MSC_TCELR_EHE3_MASK)

#define MSC_TCELR_EHE2_MASK            0x40000u

#define MSC_TCELR_EHE2_SHIFT           18u

#define MSC_TCELR_EHE2_WIDTH           1u

#define MSC_TCELR_EHE2(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE2_SHIFT))&MSC_TCELR_EHE2_MASK)

#define MSC_TCELR_EHE1_MASK            0x20000u

#define MSC_TCELR_EHE1_SHIFT           17u

#define MSC_TCELR_EHE1_WIDTH           1u

#define MSC_TCELR_EHE1(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE1_SHIFT))&MSC_TCELR_EHE1_MASK)

#define MSC_TCELR_EHE0_MASK            0x10000u

#define MSC_TCELR_EHE0_SHIFT           16u

#define MSC_TCELR_EHE0_WIDTH           1u

#define MSC_TCELR_EHE0(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_EHE0_SHIFT))&MSC_TCELR_EHE0_MASK)

#define MSC_TCELR_ELE15_MASK           0x8000u

#define MSC_TCELR_ELE15_SHIFT          15u

#define MSC_TCELR_ELE15_WIDTH          1u

#define MSC_TCELR_ELE15(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE15_SHIFT))&MSC_TCELR_ELE15_MASK)

#define MSC_TCELR_ELE14_MASK           0x4000u

#define MSC_TCELR_ELE14_SHIFT          14u

#define MSC_TCELR_ELE14_WIDTH          1u

#define MSC_TCELR_ELE14(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE14_SHIFT))&MSC_TCELR_ELE14_MASK)

#define MSC_TCELR_ELE13_MASK           0x2000u

#define MSC_TCELR_ELE13_SHIFT          13u

#define MSC_TCELR_ELE13_WIDTH          1u

#define MSC_TCELR_ELE13(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE13_SHIFT))&MSC_TCELR_ELE13_MASK)

#define MSC_TCELR_ELE12_MASK           0x1000u

#define MSC_TCELR_ELE12_SHIFT          12u

#define MSC_TCELR_ELE12_WIDTH          1u

#define MSC_TCELR_ELE12(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE12_SHIFT))&MSC_TCELR_ELE12_MASK)

#define MSC_TCELR_ELE11_MASK           0x800u

#define MSC_TCELR_ELE11_SHIFT          11u

#define MSC_TCELR_ELE11_WIDTH          1u

#define MSC_TCELR_ELE11(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE11_SHIFT))&MSC_TCELR_ELE11_MASK)

#define MSC_TCELR_ELE10_MASK           0x400u

#define MSC_TCELR_ELE10_SHIFT          10u

#define MSC_TCELR_ELE10_WIDTH          1u

#define MSC_TCELR_ELE10(x)             (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE10_SHIFT))&MSC_TCELR_ELE10_MASK)

#define MSC_TCELR_ELE9_MASK            0x200u

#define MSC_TCELR_ELE9_SHIFT           9u

#define MSC_TCELR_ELE9_WIDTH           1u

#define MSC_TCELR_ELE9(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE9_SHIFT))&MSC_TCELR_ELE9_MASK)

#define MSC_TCELR_ELE8_MASK            0x100u

#define MSC_TCELR_ELE8_SHIFT           8u

#define MSC_TCELR_ELE8_WIDTH           1u

#define MSC_TCELR_ELE8(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE8_SHIFT))&MSC_TCELR_ELE8_MASK)

#define MSC_TCELR_ELE7_MASK            0x80u

#define MSC_TCELR_ELE7_SHIFT           7u

#define MSC_TCELR_ELE7_WIDTH           1u

#define MSC_TCELR_ELE7(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE7_SHIFT))&MSC_TCELR_ELE7_MASK)

#define MSC_TCELR_ELE6_MASK            0x40u

#define MSC_TCELR_ELE6_SHIFT           6u

#define MSC_TCELR_ELE6_WIDTH           1u

#define MSC_TCELR_ELE6(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE6_SHIFT))&MSC_TCELR_ELE6_MASK)

#define MSC_TCELR_ELE5_MASK            0x20u

#define MSC_TCELR_ELE5_SHIFT           5u

#define MSC_TCELR_ELE5_WIDTH           1u

#define MSC_TCELR_ELE5(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE5_SHIFT))&MSC_TCELR_ELE5_MASK)

#define MSC_TCELR_ELE4_MASK            0x10u

#define MSC_TCELR_ELE4_SHIFT           4u

#define MSC_TCELR_ELE4_WIDTH           1u

#define MSC_TCELR_ELE4(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE4_SHIFT))&MSC_TCELR_ELE4_MASK)

#define MSC_TCELR_ELE3_MASK            0x8u

#define MSC_TCELR_ELE3_SHIFT           3u

#define MSC_TCELR_ELE3_WIDTH           1u

#define MSC_TCELR_ELE3(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE3_SHIFT))&MSC_TCELR_ELE3_MASK)

#define MSC_TCELR_ELE2_MASK            0x4u

#define MSC_TCELR_ELE2_SHIFT           2u

#define MSC_TCELR_ELE2_WIDTH           1u

#define MSC_TCELR_ELE2(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE2_SHIFT))&MSC_TCELR_ELE2_MASK)

#define MSC_TCELR_ELE1_MASK            0x2u

#define MSC_TCELR_ELE1_SHIFT           1u

#define MSC_TCELR_ELE1_WIDTH           1u

#define MSC_TCELR_ELE1(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE1_SHIFT))&MSC_TCELR_ELE1_MASK)

#define MSC_TCELR_ELE0_MASK            0x1u

#define MSC_TCELR_ELE0_SHIFT           0u

#define MSC_TCELR_ELE0_WIDTH           1u

#define MSC_TCELR_ELE0(x)              (((uint32_t)(((uint32_t)(x))<<MSC_TCELR_ELE0_SHIFT))&MSC_TCELR_ELE0_MASK)

/* TCELR Reg Mask */

#define MSC_TCELR_MASK                 0xFFFFFFFFu



/* RDR0 Bit Fields */

#define MSC_RDR0_RERR_MASK             0xC00000u

#define MSC_RDR0_RERR_SHIFT            22u

#define MSC_RDR0_RERR_WIDTH            2u

#define MSC_RDR0_RERR(x)               (((uint32_t)(((uint32_t)(x))<<MSC_RDR0_RERR_SHIFT))&MSC_RDR0_RERR_MASK)

#define MSC_RDR0_PF_MASK               0x200000u

#define MSC_RDR0_PF_SHIFT              21u

#define MSC_RDR0_PF_WIDTH              1u

#define MSC_RDR0_PF(x)                 (((uint32_t)(((uint32_t)(x))<<MSC_RDR0_PF_SHIFT))&MSC_RDR0_PF_MASK)

#define MSC_RDR0_LAF_MASK              0x180000u

#define MSC_RDR0_LAF_SHIFT             19u

#define MSC_RDR0_LAF_WIDTH             2u

#define MSC_RDR0_LAF(x)                (((uint32_t)(((uint32_t)(x))<<MSC_RDR0_LAF_SHIFT))&MSC_RDR0_LAF_MASK)

#define MSC_RDR0_CLR_MASK              0x40000u

#define MSC_RDR0_CLR_SHIFT             18u

#define MSC_RDR0_CLR_WIDTH             1u

#define MSC_RDR0_CLR(x)                (((uint32_t)(((uint32_t)(x))<<MSC_RDR0_CLR_SHIFT))&MSC_RDR0_CLR_MASK)

#define MSC_RDR0_PB_MASK               0x20000u

#define MSC_RDR0_PB_SHIFT              17u

#define MSC_RDR0_PB_WIDTH              1u

#define MSC_RDR0_PB(x)                 (((uint32_t)(((uint32_t)(x))<<MSC_RDR0_PB_SHIFT))&MSC_RDR0_PB_MASK)

#define MSC_RDR0_VLD_MASK              0x10000u

#define MSC_RDR0_VLD_SHIFT             16u

#define MSC_RDR0_VLD_WIDTH             1u

#define MSC_RDR0_VLD(x)                (((uint32_t)(((uint32_t)(x))<<MSC_RDR0_VLD_SHIFT))&MSC_RDR0_VLD_MASK)

#define MSC_RDR0_RDATA_MASK            0xFFu

#define MSC_RDR0_RDATA_SHIFT           0u

#define MSC_RDR0_RDATA_WIDTH           8u

#define MSC_RDR0_RDATA(x)              (((uint32_t)(((uint32_t)(x))<<MSC_RDR0_RDATA_SHIFT))&MSC_RDR0_RDATA_MASK)

/* RDR0 Reg Mask */

#define MSC_RDR0_MASK                  0x00FF00FFu



/* RDR1 Bit Fields */

#define MSC_RDR1_RERR_MASK             0xC00000u

#define MSC_RDR1_RERR_SHIFT            22u

#define MSC_RDR1_RERR_WIDTH            2u

#define MSC_RDR1_RERR(x)               (((uint32_t)(((uint32_t)(x))<<MSC_RDR1_RERR_SHIFT))&MSC_RDR1_RERR_MASK)

#define MSC_RDR1_PF_MASK               0x200000u

#define MSC_RDR1_PF_SHIFT              21u

#define MSC_RDR1_PF_WIDTH              1u

#define MSC_RDR1_PF(x)                 (((uint32_t)(((uint32_t)(x))<<MSC_RDR1_PF_SHIFT))&MSC_RDR1_PF_MASK)

#define MSC_RDR1_LAF_MASK              0x180000u

#define MSC_RDR1_LAF_SHIFT             19u

#define MSC_RDR1_LAF_WIDTH             2u

#define MSC_RDR1_LAF(x)                (((uint32_t)(((uint32_t)(x))<<MSC_RDR1_LAF_SHIFT))&MSC_RDR1_LAF_MASK)

#define MSC_RDR1_CLR_MASK              0x40000u

#define MSC_RDR1_CLR_SHIFT             18u

#define MSC_RDR1_CLR_WIDTH             1u

#define MSC_RDR1_CLR(x)                (((uint32_t)(((uint32_t)(x))<<MSC_RDR1_CLR_SHIFT))&MSC_RDR1_CLR_MASK)

#define MSC_RDR1_PB_MASK               0x20000u

#define MSC_RDR1_PB_SHIFT              17u

#define MSC_RDR1_PB_WIDTH              1u

#define MSC_RDR1_PB(x)                 (((uint32_t)(((uint32_t)(x))<<MSC_RDR1_PB_SHIFT))&MSC_RDR1_PB_MASK)

#define MSC_RDR1_VLD_MASK              0x10000u

#define MSC_RDR1_VLD_SHIFT             16u

#define MSC_RDR1_VLD_WIDTH             1u

#define MSC_RDR1_VLD(x)                (((uint32_t)(((uint32_t)(x))<<MSC_RDR1_VLD_SHIFT))&MSC_RDR1_VLD_MASK)

#define MSC_RDR1_RDATA_MASK            0xFFu

#define MSC_RDR1_RDATA_SHIFT           0u

#define MSC_RDR1_RDATA_WIDTH           8u

#define MSC_RDR1_RDATA(x)              (((uint32_t)(((uint32_t)(x))<<MSC_RDR1_RDATA_SHIFT))&MSC_RDR1_RDATA_MASK)

/* RDR1 Reg Mask */

#define MSC_RDR1_MASK                  0x00FF00FFu



/* RDR2 Bit Fields */

#define MSC_RDR2_RERR_MASK             0xC00000u

#define MSC_RDR2_RERR_SHIFT            22u

#define MSC_RDR2_RERR_WIDTH            2u

#define MSC_RDR2_RERR(x)               (((uint32_t)(((uint32_t)(x))<<MSC_RDR2_RERR_SHIFT))&MSC_RDR2_RERR_MASK)

#define MSC_RDR2_PF_MASK               0x200000u

#define MSC_RDR2_PF_SHIFT              21u

#define MSC_RDR2_PF_WIDTH              1u

#define MSC_RDR2_PF(x)                 (((uint32_t)(((uint32_t)(x))<<MSC_RDR2_PF_SHIFT))&MSC_RDR2_PF_MASK)

#define MSC_RDR2_LAF_MASK              0x180000u

#define MSC_RDR2_LAF_SHIFT             19u

#define MSC_RDR2_LAF_WIDTH             2u

#define MSC_RDR2_LAF(x)                (((uint32_t)(((uint32_t)(x))<<MSC_RDR2_LAF_SHIFT))&MSC_RDR2_LAF_MASK)

#define MSC_RDR2_CLR_MASK              0x40000u

#define MSC_RDR2_CLR_SHIFT             18u

#define MSC_RDR2_CLR_WIDTH             1u

#define MSC_RDR2_CLR(x)                (((uint32_t)(((uint32_t)(x))<<MSC_RDR2_CLR_SHIFT))&MSC_RDR2_CLR_MASK)

#define MSC_RDR2_PB_MASK               0x20000u

#define MSC_RDR2_PB_SHIFT              17u

#define MSC_RDR2_PB_WIDTH              1u

#define MSC_RDR2_PB(x)                 (((uint32_t)(((uint32_t)(x))<<MSC_RDR2_PB_SHIFT))&MSC_RDR2_PB_MASK)

#define MSC_RDR2_VLD_MASK              0x10000u

#define MSC_RDR2_VLD_SHIFT             16u

#define MSC_RDR2_VLD_WIDTH             1u

#define MSC_RDR2_VLD(x)                (((uint32_t)(((uint32_t)(x))<<MSC_RDR2_VLD_SHIFT))&MSC_RDR2_VLD_MASK)

#define MSC_RDR2_RDATA_MASK            0xFFu

#define MSC_RDR2_RDATA_SHIFT           0u

#define MSC_RDR2_RDATA_WIDTH           8u

#define MSC_RDR2_RDATA(x)              (((uint32_t)(((uint32_t)(x))<<MSC_RDR2_RDATA_SHIFT))&MSC_RDR2_RDATA_MASK)

/* RDR2 Reg Mask */

#define MSC_RDR2_MASK                  0x00FF00FFu



/* RDR3 Bit Fields */

#define MSC_RDR3_RERR_MASK             0xC00000u

#define MSC_RDR3_RERR_SHIFT            22u

#define MSC_RDR3_RERR_WIDTH            2u

#define MSC_RDR3_RERR(x)               (((uint32_t)(((uint32_t)(x))<<MSC_RDR3_RERR_SHIFT))&MSC_RDR3_RERR_MASK)

#define MSC_RDR3_PF_MASK               0x200000u

#define MSC_RDR3_PF_SHIFT              21u

#define MSC_RDR3_PF_WIDTH              1u

#define MSC_RDR3_PF(x)                 (((uint32_t)(((uint32_t)(x))<<MSC_RDR3_PF_SHIFT))&MSC_RDR3_PF_MASK)

#define MSC_RDR3_LAF_MASK              0x180000u

#define MSC_RDR3_LAF_SHIFT             19u

#define MSC_RDR3_LAF_WIDTH             2u

#define MSC_RDR3_LAF(x)                (((uint32_t)(((uint32_t)(x))<<MSC_RDR3_LAF_SHIFT))&MSC_RDR3_LAF_MASK)

#define MSC_RDR3_CLR_MASK              0x40000u

#define MSC_RDR3_CLR_SHIFT             18u

#define MSC_RDR3_CLR_WIDTH             1u

#define MSC_RDR3_CLR(x)                (((uint32_t)(((uint32_t)(x))<<MSC_RDR3_CLR_SHIFT))&MSC_RDR3_CLR_MASK)

#define MSC_RDR3_PB_MASK               0x20000u

#define MSC_RDR3_PB_SHIFT              17u

#define MSC_RDR3_PB_WIDTH              1u

#define MSC_RDR3_PB(x)                 (((uint32_t)(((uint32_t)(x))<<MSC_RDR3_PB_SHIFT))&MSC_RDR3_PB_MASK)

#define MSC_RDR3_VLD_MASK              0x10000u

#define MSC_RDR3_VLD_SHIFT             16u

#define MSC_RDR3_VLD_WIDTH             1u

#define MSC_RDR3_VLD(x)                (((uint32_t)(((uint32_t)(x))<<MSC_RDR3_VLD_SHIFT))&MSC_RDR3_VLD_MASK)

#define MSC_RDR3_RDATA_MASK            0xFFu

#define MSC_RDR3_RDATA_SHIFT           0u

#define MSC_RDR3_RDATA_WIDTH           8u

#define MSC_RDR3_RDATA(x)              (((uint32_t)(((uint32_t)(x))<<MSC_RDR3_RDATA_SHIFT))&MSC_RDR3_RDATA_MASK)

/* RDR3 Reg Mask */

#define MSC_RDR3_MASK                  0x00FF00FFu



/* INCR Bit Fields */

#define MSC_INCR_RFIE_MASK             0xC000u

#define MSC_INCR_RFIE_SHIFT            14u

#define MSC_INCR_RFIE_WIDTH            2u

#define MSC_INCR_RFIE(x)               (((uint32_t)(((uint32_t)(x))<<MSC_INCR_RFIE_SHIFT))&MSC_INCR_RFIE_MASK)

#define MSC_INCR_TFIE_MASK             0x800u

#define MSC_INCR_TFIE_SHIFT            11u

#define MSC_INCR_TFIE_WIDTH            1u

#define MSC_INCR_TFIE(x)               (((uint32_t)(((uint32_t)(x))<<MSC_INCR_TFIE_SHIFT))&MSC_INCR_TFIE_MASK)

#define MSC_INCR_CFIE_MASK             0x80u

#define MSC_INCR_CFIE_SHIFT            7u

#define MSC_INCR_CFIE_WIDTH            1u

#define MSC_INCR_CFIE(x)               (((uint32_t)(((uint32_t)(x))<<MSC_INCR_CFIE_SHIFT))&MSC_INCR_CFIE_MASK)

#define MSC_INCR_DFIE_MASK             0xCu

#define MSC_INCR_DFIE_SHIFT            2u

#define MSC_INCR_DFIE_WIDTH            2u

#define MSC_INCR_DFIE(x)               (((uint32_t)(((uint32_t)(x))<<MSC_INCR_DFIE_SHIFT))&MSC_INCR_DFIE_MASK)

/* INCR Reg Mask */

#define MSC_INCR_MASK                  0x0000C88Cu



/* INSR Bit Fields */

#define MSC_INSR_RSBFI_MASK            0x10u

#define MSC_INSR_RSBFI_SHIFT           4u

#define MSC_INSR_RSBFI_WIDTH           1u

#define MSC_INSR_RSBFI(x)              (((uint32_t)(((uint32_t)(x))<<MSC_INSR_RSBFI_SHIFT))&MSC_INSR_RSBFI_MASK)

#define MSC_INSR_RFI_MASK              0x8u

#define MSC_INSR_RFI_SHIFT             3u

#define MSC_INSR_RFI_WIDTH             1u

#define MSC_INSR_RFI(x)                (((uint32_t)(((uint32_t)(x))<<MSC_INSR_RFI_SHIFT))&MSC_INSR_RFI_MASK)

#define MSC_INSR_TFI_MASK              0x4u

#define MSC_INSR_TFI_SHIFT             2u

#define MSC_INSR_TFI_WIDTH             1u

#define MSC_INSR_TFI(x)                (((uint32_t)(((uint32_t)(x))<<MSC_INSR_TFI_SHIFT))&MSC_INSR_TFI_MASK)

#define MSC_INSR_CFI_MASK              0x2u

#define MSC_INSR_CFI_SHIFT             1u

#define MSC_INSR_CFI_WIDTH             1u

#define MSC_INSR_CFI(x)                (((uint32_t)(((uint32_t)(x))<<MSC_INSR_CFI_SHIFT))&MSC_INSR_CFI_MASK)

#define MSC_INSR_DFI_MASK              0x1u

#define MSC_INSR_DFI_SHIFT             0u

#define MSC_INSR_DFI_WIDTH             1u

#define MSC_INSR_DFI(x)                (((uint32_t)(((uint32_t)(x))<<MSC_INSR_DFI_SHIFT))&MSC_INSR_DFI_MASK)

/* INSR Reg Mask */

#define MSC_INSR_MASK                  0x0000001Fu



/* ISCR Bit Fields */

#define MSC_ISCR_CRSBFI_MASK           0x80000000u

#define MSC_ISCR_CRSBFI_SHIFT          31u

#define MSC_ISCR_CRSBFI_WIDTH          1u

#define MSC_ISCR_CRSBFI(x)             (((uint32_t)(((uint32_t)(x))<<MSC_ISCR_CRSBFI_SHIFT))&MSC_ISCR_CRSBFI_MASK)

#define MSC_ISCR_SDIS_MASK             0x400000u

#define MSC_ISCR_SDIS_SHIFT            22u

#define MSC_ISCR_SDIS_WIDTH            1u

#define MSC_ISCR_SDIS(x)               (((uint32_t)(((uint32_t)(x))<<MSC_ISCR_SDIS_SHIFT))&MSC_ISCR_SDIS_MASK)

#define MSC_ISCR_SDTS_MASK             0x100000u

#define MSC_ISCR_SDTS_SHIFT            20u

#define MSC_ISCR_SDTS_WIDTH            1u

#define MSC_ISCR_SDTS(x)               (((uint32_t)(((uint32_t)(x))<<MSC_ISCR_SDTS_SHIFT))&MSC_ISCR_SDTS_MASK)

#define MSC_ISCR_SRFI_MASK             0x80000u

#define MSC_ISCR_SRFI_SHIFT            19u

#define MSC_ISCR_SRFI_WIDTH            1u

#define MSC_ISCR_SRFI(x)               (((uint32_t)(((uint32_t)(x))<<MSC_ISCR_SRFI_SHIFT))&MSC_ISCR_SRFI_MASK)

#define MSC_ISCR_STFI_MASK             0x40000u

#define MSC_ISCR_STFI_SHIFT            18u

#define MSC_ISCR_STFI_WIDTH            1u

#define MSC_ISCR_STFI(x)               (((uint32_t)(((uint32_t)(x))<<MSC_ISCR_STFI_SHIFT))&MSC_ISCR_STFI_MASK)

#define MSC_ISCR_SCFI_MASK             0x20000u

#define MSC_ISCR_SCFI_SHIFT            17u

#define MSC_ISCR_SCFI_WIDTH            1u

#define MSC_ISCR_SCFI(x)               (((uint32_t)(((uint32_t)(x))<<MSC_ISCR_SCFI_SHIFT))&MSC_ISCR_SCFI_MASK)

#define MSC_ISCR_SDFI_MASK             0x10000u

#define MSC_ISCR_SDFI_SHIFT            16u

#define MSC_ISCR_SDFI_WIDTH            1u

#define MSC_ISCR_SDFI(x)               (((uint32_t)(((uint32_t)(x))<<MSC_ISCR_SDFI_SHIFT))&MSC_ISCR_SDFI_MASK)

#define MSC_ISCR_CDIS_MASK             0x40u

#define MSC_ISCR_CDIS_SHIFT            6u

#define MSC_ISCR_CDIS_WIDTH            1u

#define MSC_ISCR_CDIS(x)               (((uint32_t)(((uint32_t)(x))<<MSC_ISCR_CDIS_SHIFT))&MSC_ISCR_CDIS_MASK)

#define MSC_ISCR_CCTS_MASK             0x20u

#define MSC_ISCR_CCTS_SHIFT            5u

#define MSC_ISCR_CCTS_WIDTH            1u

#define MSC_ISCR_CCTS(x)               (((uint32_t)(((uint32_t)(x))<<MSC_ISCR_CCTS_SHIFT))&MSC_ISCR_CCTS_MASK)

#define MSC_ISCR_CDTS_MASK             0x10u

#define MSC_ISCR_CDTS_SHIFT            4u

#define MSC_ISCR_CDTS_WIDTH            1u

#define MSC_ISCR_CDTS(x)               (((uint32_t)(((uint32_t)(x))<<MSC_ISCR_CDTS_SHIFT))&MSC_ISCR_CDTS_MASK)

#define MSC_ISCR_CRFI_MASK             0x8u

#define MSC_ISCR_CRFI_SHIFT            3u

#define MSC_ISCR_CRFI_WIDTH            1u

#define MSC_ISCR_CRFI(x)               (((uint32_t)(((uint32_t)(x))<<MSC_ISCR_CRFI_SHIFT))&MSC_ISCR_CRFI_MASK)

#define MSC_ISCR_CTFI_MASK             0x4u

#define MSC_ISCR_CTFI_SHIFT            2u

#define MSC_ISCR_CTFI_WIDTH            1u

#define MSC_ISCR_CTFI(x)               (((uint32_t)(((uint32_t)(x))<<MSC_ISCR_CTFI_SHIFT))&MSC_ISCR_CTFI_MASK)

#define MSC_ISCR_CCFI_MASK             0x2u

#define MSC_ISCR_CCFI_SHIFT            1u

#define MSC_ISCR_CCFI_WIDTH            1u

#define MSC_ISCR_CCFI(x)               (((uint32_t)(((uint32_t)(x))<<MSC_ISCR_CCFI_SHIFT))&MSC_ISCR_CCFI_MASK)

#define MSC_ISCR_CDFI_MASK             0x1u

#define MSC_ISCR_CDFI_SHIFT            0u

#define MSC_ISCR_CDFI_WIDTH            1u

#define MSC_ISCR_CDFI(x)               (((uint32_t)(((uint32_t)(x))<<MSC_ISCR_CDFI_SHIFT))&MSC_ISCR_CDFI_MASK)

/* ISCR Reg Mask */

#define MSC_ISCR_MASK                  0x805F007Fu



/* IOCR Bit Fields */

#define MSC_IOCR_IDS_MASK              0x70000u

#define MSC_IOCR_IDS_SHIFT             16u

#define MSC_IOCR_IDS_WIDTH             3u

#define MSC_IOCR_IDS(x)                (((uint32_t)(((uint32_t)(x))<<MSC_IOCR_IDS_SHIFT))&MSC_IOCR_IDS_MASK)

#define MSC_IOCR_ESC_MASK              0x6000u

#define MSC_IOCR_ESC_SHIFT             13u

#define MSC_IOCR_ESC_WIDTH             2u

#define MSC_IOCR_ESC(x)                (((uint32_t)(((uint32_t)(x))<<MSC_IOCR_ESC_SHIFT))&MSC_IOCR_ESC_MASK)

#define MSC_IOCR_ESH_MASK              0x1800u

#define MSC_IOCR_ESH_SHIFT             11u

#define MSC_IOCR_ESH_WIDTH             2u

#define MSC_IOCR_ESH(x)                (((uint32_t)(((uint32_t)(x))<<MSC_IOCR_ESH_SHIFT))&MSC_IOCR_ESH_MASK)

#define MSC_IOCR_ESL_MASK              0x600u

#define MSC_IOCR_ESL_SHIFT             9u

#define MSC_IOCR_ESL_WIDTH             2u

#define MSC_IOCR_ESL(x)                (((uint32_t)(((uint32_t)(x))<<MSC_IOCR_ESL_SHIFT))&MSC_IOCR_ESL_MASK)

#define MSC_IOCR_FCLCTRL_MASK          0x100u

#define MSC_IOCR_FCLCTRL_SHIFT         8u

#define MSC_IOCR_FCLCTRL_WIDTH         1u

#define MSC_IOCR_FCLCTRL(x)            (((uint32_t)(((uint32_t)(x))<<MSC_IOCR_FCLCTRL_SHIFT))&MSC_IOCR_FCLCTRL_MASK)

#define MSC_IOCR_IPS_MASK              0x8u

#define MSC_IOCR_IPS_SHIFT             3u

#define MSC_IOCR_IPS_WIDTH             1u

#define MSC_IOCR_IPS(x)                (((uint32_t)(((uint32_t)(x))<<MSC_IOCR_IPS_SHIFT))&MSC_IOCR_IPS_MASK)

#define MSC_IOCR_ENP_MASK              0x4u

#define MSC_IOCR_ENP_SHIFT             2u

#define MSC_IOCR_ENP_WIDTH             1u

#define MSC_IOCR_ENP(x)                (((uint32_t)(((uint32_t)(x))<<MSC_IOCR_ENP_SHIFT))&MSC_IOCR_ENP_MASK)

#define MSC_IOCR_SOP_MASK              0x2u

#define MSC_IOCR_SOP_SHIFT             1u

#define MSC_IOCR_SOP_WIDTH             1u

#define MSC_IOCR_SOP(x)                (((uint32_t)(((uint32_t)(x))<<MSC_IOCR_SOP_SHIFT))&MSC_IOCR_SOP_MASK)

#define MSC_IOCR_FCLP_MASK             0x1u

#define MSC_IOCR_FCLP_SHIFT            0u

#define MSC_IOCR_FCLP_WIDTH            1u

#define MSC_IOCR_FCLP(x)               (((uint32_t)(((uint32_t)(x))<<MSC_IOCR_FCLP_SHIFT))&MSC_IOCR_FCLP_MASK)

/* IOCR Reg Mask */

#define MSC_IOCR_MASK                  0x00077F0Fu



/* TCCTR1 Bit Fields */

#define MSC_TCCTR1_INJP1_MASK          0x7E000000u

#define MSC_TCCTR1_INJP1_SHIFT         25u

#define MSC_TCCTR1_INJP1_WIDTH         6u

#define MSC_TCCTR1_INJP1(x)            (((uint32_t)(((uint32_t)(x))<<MSC_TCCTR1_INJP1_SHIFT))&MSC_TCCTR1_INJP1_MASK)

#define MSC_TCCTR1_INJE1_MASK          0x1000000u

#define MSC_TCCTR1_INJE1_SHIFT         24u

#define MSC_TCCTR1_INJE1_WIDTH         1u

#define MSC_TCCTR1_INJE1(x)            (((uint32_t)(((uint32_t)(x))<<MSC_TCCTR1_INJE1_SHIFT))&MSC_TCCTR1_INJE1_MASK)

#define MSC_TCCTR1_INJP0_MASK          0x7E0000u

#define MSC_TCCTR1_INJP0_SHIFT         17u

#define MSC_TCCTR1_INJP0_WIDTH         6u

#define MSC_TCCTR1_INJP0(x)            (((uint32_t)(((uint32_t)(x))<<MSC_TCCTR1_INJP0_SHIFT))&MSC_TCCTR1_INJP0_MASK)

#define MSC_TCCTR1_INJE0_MASK          0x10000u

#define MSC_TCCTR1_INJE0_SHIFT         16u

#define MSC_TCCTR1_INJE0_WIDTH         1u

#define MSC_TCCTR1_INJE0(x)            (((uint32_t)(((uint32_t)(x))<<MSC_TCCTR1_INJE0_SHIFT))&MSC_TCCTR1_INJE0_MASK)

/* TCCTR1 Reg Mask */

#define MSC_TCCTR1_MASK                0x7F7F0000u



/* RTOR Bit Fields */

#define MSC_RTOR_TOFC_MASK             0x80000u

#define MSC_RTOR_TOFC_SHIFT            19u

#define MSC_RTOR_TOFC_WIDTH            1u

#define MSC_RTOR_TOFC(x)               (((uint32_t)(((uint32_t)(x))<<MSC_RTOR_TOFC_SHIFT))&MSC_RTOR_TOFC_MASK)

#define MSC_RTOR_TOFS_MASK             0x40000u

#define MSC_RTOR_TOFS_SHIFT            18u

#define MSC_RTOR_TOFS_WIDTH            1u

#define MSC_RTOR_TOFS(x)               (((uint32_t)(((uint32_t)(x))<<MSC_RTOR_TOFS_SHIFT))&MSC_RTOR_TOFS_MASK)

#define MSC_RTOR_TOF_MASK              0x20000u

#define MSC_RTOR_TOF_SHIFT             17u

#define MSC_RTOR_TOF_WIDTH             1u

#define MSC_RTOR_TOF(x)                (((uint32_t)(((uint32_t)(x))<<MSC_RTOR_TOF_SHIFT))&MSC_RTOR_TOF_MASK)

#define MSC_RTOR_TOIE_MASK             0x10000u

#define MSC_RTOR_TOIE_SHIFT            16u

#define MSC_RTOR_TOIE_WIDTH            1u

#define MSC_RTOR_TOIE(x)               (((uint32_t)(((uint32_t)(x))<<MSC_RTOR_TOIE_SHIFT))&MSC_RTOR_TOIE_MASK)

#define MSC_RTOR_TOV_MASK              0xFFFFu

#define MSC_RTOR_TOV_SHIFT             0u

#define MSC_RTOR_TOV_WIDTH             16u

#define MSC_RTOR_TOV(x)                (((uint32_t)(((uint32_t)(x))<<MSC_RTOR_TOV_SHIFT))&MSC_RTOR_TOV_MASK)

/* RTOR Reg Mask */

#define MSC_RTOR_MASK                  0x000FFFFFu



/* SRCR Bit Fields */

#define MSC_SRCR_RCLR_MASK             0x1u

#define MSC_SRCR_RCLR_SHIFT            0u

#define MSC_SRCR_RCLR_WIDTH            1u

#define MSC_SRCR_RCLR(x)               (((uint32_t)(((uint32_t)(x))<<MSC_SRCR_RCLR_SHIFT))&MSC_SRCR_RCLR_MASK)

/* SRCR Reg Mask */

#define MSC_SRCR_MASK                  0x00000001u



/* MSR Bit Fields */

#define MSC_MSR_RDONE_MASK             0x2u

#define MSC_MSR_RDONE_SHIFT            1u

#define MSC_MSR_RDONE_WIDTH            1u

#define MSC_MSR_RDONE(x)               (((uint32_t)(((uint32_t)(x))<<MSC_MSR_RDONE_SHIFT))&MSC_MSR_RDONE_MASK)

#define MSC_MSR_RST_MASK               0x1u

#define MSC_MSR_RST_SHIFT              0u

#define MSC_MSR_RST_WIDTH              1u

#define MSC_MSR_RST(x)                 (((uint32_t)(((uint32_t)(x))<<MSC_MSR_RST_SHIFT))&MSC_MSR_RST_MASK)

/* MSR Reg Mask */

#define MSC_MSR_MASK                   0x00000003u





/*!

 * @}

 */ /* end of group MSC_Register_Masks */



/*!

 * @}

 */ /* end of group MSC_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
