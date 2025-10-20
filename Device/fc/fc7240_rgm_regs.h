#ifndef _FC7240_RGM_NU_Tztufn9_REGS_H_
#define _FC7240_RGM_NU_Tztufn9_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- RGM Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup RGM_Peripheral_Access_Layer RGM Peripheral Access Layer

 * @{

 */



/** RGM - Size of Registers Arrays */



/** RGM - Register Layout Typedef */



typedef struct {



       uint8_t  RESERVED_0[8];

  __IO uint32_t SRS                           ; /* System Reset Status Register, offset: 0x8 */

  __IO uint32_t RSTFLT                        ; /* Reset Filter Control Register, offset: 0xC */

       uint8_t  RESERVED_1[8];

  __IO uint32_t SSRS                          ; /* Sticky System Reset Status Register, offset: 0x18 */

  __IO uint32_t SRIE                          ; /* System Reset Interrupt Enable Register, offset: 0x1C */

       uint8_t  RESERVED_2[224];

  __IO uint32_t C0_CFG                        ; /* CPU0 Reset Configuration Register, offset: 0x100 */

  __IO uint32_t C0_RST                        ; /* CPU0 Reset Register, offset: 0x104 */

  __IO uint32_t C0_SRS                        ; /* CPU0 System Reset Status Register, offset: 0x108 */

       uint8_t  RESERVED_3[8];

  __IO uint32_t C0_SSRS                       ; /* CPU0 Sticky System Reset Status Register, offset: 0x114 */



} RGM_Type, *RGM_MemMapPtr;



/** Number of instances of the RGM module. */

#define RGM_INSTANCE_COUNT                       (1u)



/* RGM - Peripheral instance base addresses */

/** Peripheral RGM base address */

#define RGM_BASE                                 (0x40046000u)

/** Peripheral RGM base pointer */

#define RGM                                      ((RGM_Type *)RGM_BASE)

/** Array initializer of RGM peripheral base addresses */

#define RGM_BASE_ADDRS                           {RGM_BASE}

/** Array initializer of RGM peripheral base pointers */

#define RGM_BASE_PTRS                            {RGM}

/* ----------------------------------------------------------------------------

   -- RGM Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup RGM_Register_Masks RGM Register Masks

 * @{

 */



/* SRS Bit Fields */

#define RGM_SRS_SYSRST_TOUT_MASK       0x80000000u

#define RGM_SRS_SYSRST_TOUT_SHIFT      31u

#define RGM_SRS_SYSRST_TOUT_WIDTH      1u

#define RGM_SRS_SYSRST_TOUT(x)         (((uint32_t)(((uint32_t)(x))<<RGM_SRS_SYSRST_TOUT_SHIFT))&RGM_SRS_SYSRST_TOUT_MASK)

#define RGM_SRS_PINRST_TOUT_MASK       0x40000000u

#define RGM_SRS_PINRST_TOUT_SHIFT      30u

#define RGM_SRS_PINRST_TOUT_WIDTH      1u

#define RGM_SRS_PINRST_TOUT(x)         (((uint32_t)(((uint32_t)(x))<<RGM_SRS_PINRST_TOUT_SHIFT))&RGM_SRS_PINRST_TOUT_MASK)

#define RGM_SRS_FSM_ERR_MASK           0x20000000u

#define RGM_SRS_FSM_ERR_SHIFT          29u

#define RGM_SRS_FSM_ERR_WIDTH          1u

#define RGM_SRS_FSM_ERR(x)             (((uint32_t)(((uint32_t)(x))<<RGM_SRS_FSM_ERR_SHIFT))&RGM_SRS_FSM_ERR_MASK)

#define RGM_SRS_LBIST_MASK             0x8000u

#define RGM_SRS_LBIST_SHIFT            15u

#define RGM_SRS_LBIST_WIDTH            1u

#define RGM_SRS_LBIST(x)               (((uint32_t)(((uint32_t)(x))<<RGM_SRS_LBIST_SHIFT))&RGM_SRS_LBIST_MASK)

#define RGM_SRS_CMU_MASK               0x4000u

#define RGM_SRS_CMU_SHIFT              14u

#define RGM_SRS_CMU_WIDTH              1u

#define RGM_SRS_CMU(x)                 (((uint32_t)(((uint32_t)(x))<<RGM_SRS_CMU_SHIFT))&RGM_SRS_CMU_MASK)

#define RGM_SRS_SACKERR_MASK           0x2000u

#define RGM_SRS_SACKERR_SHIFT          13u

#define RGM_SRS_SACKERR_WIDTH          1u

#define RGM_SRS_SACKERR(x)             (((uint32_t)(((uint32_t)(x))<<RGM_SRS_SACKERR_SHIFT))&RGM_SRS_SACKERR_MASK)

#define RGM_SRS_WDOG1_MASK             0x1000u

#define RGM_SRS_WDOG1_SHIFT            12u

#define RGM_SRS_WDOG1_WIDTH            1u

#define RGM_SRS_WDOG1(x)               (((uint32_t)(((uint32_t)(x))<<RGM_SRS_WDOG1_SHIFT))&RGM_SRS_WDOG1_MASK)

#define RGM_SRS_SYSAP_MASK             0x800u

#define RGM_SRS_SYSAP_SHIFT            11u

#define RGM_SRS_SYSAP_WIDTH            1u

#define RGM_SRS_SYSAP(x)               (((uint32_t)(((uint32_t)(x))<<RGM_SRS_SYSAP_SHIFT))&RGM_SRS_SYSAP_MASK)

#define RGM_SRS_JTAG_MASK              0x100u

#define RGM_SRS_JTAG_SHIFT             8u

#define RGM_SRS_JTAG_WIDTH             1u

#define RGM_SRS_JTAG(x)                (((uint32_t)(((uint32_t)(x))<<RGM_SRS_JTAG_SHIFT))&RGM_SRS_JTAG_MASK)

#define RGM_SRS_POR_MASK               0x80u

#define RGM_SRS_POR_SHIFT              7u

#define RGM_SRS_POR_WIDTH              1u

#define RGM_SRS_POR(x)                 (((uint32_t)(((uint32_t)(x))<<RGM_SRS_POR_SHIFT))&RGM_SRS_POR_MASK)

#define RGM_SRS_PIN_MASK               0x40u

#define RGM_SRS_PIN_SHIFT              6u

#define RGM_SRS_PIN_WIDTH              1u

#define RGM_SRS_PIN(x)                 (((uint32_t)(((uint32_t)(x))<<RGM_SRS_PIN_SHIFT))&RGM_SRS_PIN_MASK)

#define RGM_SRS_HSM_WDOG_MASK          0x20u

#define RGM_SRS_HSM_WDOG_SHIFT         5u

#define RGM_SRS_HSM_WDOG_WIDTH         1u

#define RGM_SRS_HSM_WDOG(x)            (((uint32_t)(((uint32_t)(x))<<RGM_SRS_HSM_WDOG_SHIFT))&RGM_SRS_HSM_WDOG_MASK)

#define RGM_SRS_FCSMU_MASK             0x10u

#define RGM_SRS_FCSMU_SHIFT            4u

#define RGM_SRS_FCSMU_WIDTH            1u

#define RGM_SRS_FCSMU(x)               (((uint32_t)(((uint32_t)(x))<<RGM_SRS_FCSMU_SHIFT))&RGM_SRS_FCSMU_MASK)

#define RGM_SRS_CLKERR0_MASK           0x8u

#define RGM_SRS_CLKERR0_SHIFT          3u

#define RGM_SRS_CLKERR0_WIDTH          1u

#define RGM_SRS_CLKERR0(x)             (((uint32_t)(((uint32_t)(x))<<RGM_SRS_CLKERR0_SHIFT))&RGM_SRS_CLKERR0_MASK)

#define RGM_SRS_CLKERR1_MASK           0x4u

#define RGM_SRS_CLKERR1_SHIFT          2u

#define RGM_SRS_CLKERR1_WIDTH          1u

#define RGM_SRS_CLKERR1(x)             (((uint32_t)(((uint32_t)(x))<<RGM_SRS_CLKERR1_SHIFT))&RGM_SRS_CLKERR1_MASK)

#define RGM_SRS_LVR_MASK               0x2u

#define RGM_SRS_LVR_SHIFT              1u

#define RGM_SRS_LVR_WIDTH              1u

#define RGM_SRS_LVR(x)                 (((uint32_t)(((uint32_t)(x))<<RGM_SRS_LVR_SHIFT))&RGM_SRS_LVR_MASK)

#define RGM_SRS_WAKEUP_MASK            0x1u

#define RGM_SRS_WAKEUP_SHIFT           0u

#define RGM_SRS_WAKEUP_WIDTH           1u

#define RGM_SRS_WAKEUP(x)              (((uint32_t)(((uint32_t)(x))<<RGM_SRS_WAKEUP_SHIFT))&RGM_SRS_WAKEUP_MASK)

/* SRS Reg Mask */

#define RGM_SRS_MASK                   0xE000F9FFu



/* RSTFLT Bit Fields */

#define RGM_RSTFLT_RSTFLT_BUSW_MASK    0x1F00u

#define RGM_RSTFLT_RSTFLT_BUSW_SHIFT   8u

#define RGM_RSTFLT_RSTFLT_BUSW_WIDTH   5u

#define RGM_RSTFLT_RSTFLT_BUSW(x)      (((uint32_t)(((uint32_t)(x))<<RGM_RSTFLT_RSTFLT_BUSW_SHIFT))&RGM_RSTFLT_RSTFLT_BUSW_MASK)

#define RGM_RSTFLT_RSTFLT_AON_LP_MASK  0x4u

#define RGM_RSTFLT_RSTFLT_AON_LP_SHIFT 2u

#define RGM_RSTFLT_RSTFLT_AON_LP_WIDTH 1u

#define RGM_RSTFLT_RSTFLT_AON_LP(x)    (((uint32_t)(((uint32_t)(x))<<RGM_RSTFLT_RSTFLT_AON_LP_SHIFT))&RGM_RSTFLT_RSTFLT_AON_LP_MASK)

#define RGM_RSTFLT_RSTFLT_AON_MASK     0x2u

#define RGM_RSTFLT_RSTFLT_AON_SHIFT    1u

#define RGM_RSTFLT_RSTFLT_AON_WIDTH    1u

#define RGM_RSTFLT_RSTFLT_AON(x)       (((uint32_t)(((uint32_t)(x))<<RGM_RSTFLT_RSTFLT_AON_SHIFT))&RGM_RSTFLT_RSTFLT_AON_MASK)

#define RGM_RSTFLT_RSTFLT_BUS_MASK     0x1u

#define RGM_RSTFLT_RSTFLT_BUS_SHIFT    0u

#define RGM_RSTFLT_RSTFLT_BUS_WIDTH    1u

#define RGM_RSTFLT_RSTFLT_BUS(x)       (((uint32_t)(((uint32_t)(x))<<RGM_RSTFLT_RSTFLT_BUS_SHIFT))&RGM_RSTFLT_RSTFLT_BUS_MASK)

/* RSTFLT Reg Mask */

#define RGM_RSTFLT_MASK                0x00001F07u



/* SSRS Bit Fields */

#define RGM_SSRS_SYSRST_TOUT_MASK      0x80000000u

#define RGM_SSRS_SYSRST_TOUT_SHIFT     31u

#define RGM_SSRS_SYSRST_TOUT_WIDTH     1u

#define RGM_SSRS_SYSRST_TOUT(x)        (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_SYSRST_TOUT_SHIFT))&RGM_SSRS_SYSRST_TOUT_MASK)

#define RGM_SSRS_PINRST_TOUT_MASK      0x40000000u

#define RGM_SSRS_PINRST_TOUT_SHIFT     30u

#define RGM_SSRS_PINRST_TOUT_WIDTH     1u

#define RGM_SSRS_PINRST_TOUT(x)        (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_PINRST_TOUT_SHIFT))&RGM_SSRS_PINRST_TOUT_MASK)

#define RGM_SSRS_FSM_ERR_MASK          0x20000000u

#define RGM_SSRS_FSM_ERR_SHIFT         29u

#define RGM_SSRS_FSM_ERR_WIDTH         1u

#define RGM_SSRS_FSM_ERR(x)            (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_FSM_ERR_SHIFT))&RGM_SSRS_FSM_ERR_MASK)

#define RGM_SSRS_LBIST_MASK            0x8000u

#define RGM_SSRS_LBIST_SHIFT           15u

#define RGM_SSRS_LBIST_WIDTH           1u

#define RGM_SSRS_LBIST(x)              (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_LBIST_SHIFT))&RGM_SSRS_LBIST_MASK)

#define RGM_SSRS_CMU_MASK              0x4000u

#define RGM_SSRS_CMU_SHIFT             14u

#define RGM_SSRS_CMU_WIDTH             1u

#define RGM_SSRS_CMU(x)                (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_CMU_SHIFT))&RGM_SSRS_CMU_MASK)

#define RGM_SSRS_SACKERR_ST_MASK       0x2000u

#define RGM_SSRS_SACKERR_ST_SHIFT      13u

#define RGM_SSRS_SACKERR_ST_WIDTH      1u

#define RGM_SSRS_SACKERR_ST(x)         (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_SACKERR_ST_SHIFT))&RGM_SSRS_SACKERR_ST_MASK)

#define RGM_SSRS_WDOG1_MASK            0x1000u

#define RGM_SSRS_WDOG1_SHIFT           12u

#define RGM_SSRS_WDOG1_WIDTH           1u

#define RGM_SSRS_WDOG1(x)              (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_WDOG1_SHIFT))&RGM_SSRS_WDOG1_MASK)

#define RGM_SSRS_SYSAP_ST_MASK         0x800u

#define RGM_SSRS_SYSAP_ST_SHIFT        11u

#define RGM_SSRS_SYSAP_ST_WIDTH        1u

#define RGM_SSRS_SYSAP_ST(x)           (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_SYSAP_ST_SHIFT))&RGM_SSRS_SYSAP_ST_MASK)

#define RGM_SSRS_JTAG_ST_MASK          0x100u

#define RGM_SSRS_JTAG_ST_SHIFT         8u

#define RGM_SSRS_JTAG_ST_WIDTH         1u

#define RGM_SSRS_JTAG_ST(x)            (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_JTAG_ST_SHIFT))&RGM_SSRS_JTAG_ST_MASK)

#define RGM_SSRS_POR_ST_MASK           0x80u

#define RGM_SSRS_POR_ST_SHIFT          7u

#define RGM_SSRS_POR_ST_WIDTH          1u

#define RGM_SSRS_POR_ST(x)             (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_POR_ST_SHIFT))&RGM_SSRS_POR_ST_MASK)

#define RGM_SSRS_PIN_ST_MASK           0x40u

#define RGM_SSRS_PIN_ST_SHIFT          6u

#define RGM_SSRS_PIN_ST_WIDTH          1u

#define RGM_SSRS_PIN_ST(x)             (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_PIN_ST_SHIFT))&RGM_SSRS_PIN_ST_MASK)

#define RGM_SSRS_HSMWDOG_ST_MASK       0x20u

#define RGM_SSRS_HSMWDOG_ST_SHIFT      5u

#define RGM_SSRS_HSMWDOG_ST_WIDTH      1u

#define RGM_SSRS_HSMWDOG_ST(x)         (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_HSMWDOG_ST_SHIFT))&RGM_SSRS_HSMWDOG_ST_MASK)

#define RGM_SSRS_FCSMU_ST_MASK         0x10u

#define RGM_SSRS_FCSMU_ST_SHIFT        4u

#define RGM_SSRS_FCSMU_ST_WIDTH        1u

#define RGM_SSRS_FCSMU_ST(x)           (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_FCSMU_ST_SHIFT))&RGM_SSRS_FCSMU_ST_MASK)

#define RGM_SSRS_CLKERR0_ST_MASK       0x8u

#define RGM_SSRS_CLKERR0_ST_SHIFT      3u

#define RGM_SSRS_CLKERR0_ST_WIDTH      1u

#define RGM_SSRS_CLKERR0_ST(x)         (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_CLKERR0_ST_SHIFT))&RGM_SSRS_CLKERR0_ST_MASK)

#define RGM_SSRS_CLKERR1_ST_MASK       0x4u

#define RGM_SSRS_CLKERR1_ST_SHIFT      2u

#define RGM_SSRS_CLKERR1_ST_WIDTH      1u

#define RGM_SSRS_CLKERR1_ST(x)         (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_CLKERR1_ST_SHIFT))&RGM_SSRS_CLKERR1_ST_MASK)

#define RGM_SSRS_LVR_MASK              0x2u

#define RGM_SSRS_LVR_SHIFT             1u

#define RGM_SSRS_LVR_WIDTH             1u

#define RGM_SSRS_LVR(x)                (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_LVR_SHIFT))&RGM_SSRS_LVR_MASK)

#define RGM_SSRS_WAKEUP_ST_MASK        0x1u

#define RGM_SSRS_WAKEUP_ST_SHIFT       0u

#define RGM_SSRS_WAKEUP_ST_WIDTH       1u

#define RGM_SSRS_WAKEUP_ST(x)          (((uint32_t)(((uint32_t)(x))<<RGM_SSRS_WAKEUP_ST_SHIFT))&RGM_SSRS_WAKEUP_ST_MASK)

/* SSRS Reg Mask */

#define RGM_SSRS_MASK                  0xE000F9FFu



/* SRIE Bit Fields */

#define RGM_SRIE_SACKERR_RIE_MASK      0x2000u

#define RGM_SRIE_SACKERR_RIE_SHIFT     13u

#define RGM_SRIE_SACKERR_RIE_WIDTH     1u

#define RGM_SRIE_SACKERR_RIE(x)        (((uint32_t)(((uint32_t)(x))<<RGM_SRIE_SACKERR_RIE_SHIFT))&RGM_SRIE_SACKERR_RIE_MASK)

#define RGM_SRIE_WDOG1_RIE_MASK        0x1000u

#define RGM_SRIE_WDOG1_RIE_SHIFT       12u

#define RGM_SRIE_WDOG1_RIE_WIDTH       1u

#define RGM_SRIE_WDOG1_RIE(x)          (((uint32_t)(((uint32_t)(x))<<RGM_SRIE_WDOG1_RIE_SHIFT))&RGM_SRIE_WDOG1_RIE_MASK)

#define RGM_SRIE_SYSAP_RIE_MASK        0x800u

#define RGM_SRIE_SYSAP_RIE_SHIFT       11u

#define RGM_SRIE_SYSAP_RIE_WIDTH       1u

#define RGM_SRIE_SYSAP_RIE(x)          (((uint32_t)(((uint32_t)(x))<<RGM_SRIE_SYSAP_RIE_SHIFT))&RGM_SRIE_SYSAP_RIE_MASK)

#define RGM_SRIE_SW_RIE_MASK           0x400u

#define RGM_SRIE_SW_RIE_SHIFT          10u

#define RGM_SRIE_SW_RIE_WIDTH          1u

#define RGM_SRIE_SW_RIE(x)             (((uint32_t)(((uint32_t)(x))<<RGM_SRIE_SW_RIE_SHIFT))&RGM_SRIE_SW_RIE_MASK)

#define RGM_SRIE_CPULOC_RIE_MASK       0x200u

#define RGM_SRIE_CPULOC_RIE_SHIFT      9u

#define RGM_SRIE_CPULOC_RIE_WIDTH      1u

#define RGM_SRIE_CPULOC_RIE(x)         (((uint32_t)(((uint32_t)(x))<<RGM_SRIE_CPULOC_RIE_SHIFT))&RGM_SRIE_CPULOC_RIE_MASK)

#define RGM_SRIE_JTAG_RIE_MASK         0x100u

#define RGM_SRIE_JTAG_RIE_SHIFT        8u

#define RGM_SRIE_JTAG_RIE_WIDTH        1u

#define RGM_SRIE_JTAG_RIE(x)           (((uint32_t)(((uint32_t)(x))<<RGM_SRIE_JTAG_RIE_SHIFT))&RGM_SRIE_JTAG_RIE_MASK)

#define RGM_SRIE_GLOBAL_RIE_MASK       0x80u

#define RGM_SRIE_GLOBAL_RIE_SHIFT      7u

#define RGM_SRIE_GLOBAL_RIE_WIDTH      1u

#define RGM_SRIE_GLOBAL_RIE(x)         (((uint32_t)(((uint32_t)(x))<<RGM_SRIE_GLOBAL_RIE_SHIFT))&RGM_SRIE_GLOBAL_RIE_MASK)

#define RGM_SRIE_PIN_RIE_MASK          0x40u

#define RGM_SRIE_PIN_RIE_SHIFT         6u

#define RGM_SRIE_PIN_RIE_WIDTH         1u

#define RGM_SRIE_PIN_RIE(x)            (((uint32_t)(((uint32_t)(x))<<RGM_SRIE_PIN_RIE_SHIFT))&RGM_SRIE_PIN_RIE_MASK)

#define RGM_SRIE_WDG_RIE_MASK          0x20u

#define RGM_SRIE_WDG_RIE_SHIFT         5u

#define RGM_SRIE_WDG_RIE_WIDTH         1u

#define RGM_SRIE_WDG_RIE(x)            (((uint32_t)(((uint32_t)(x))<<RGM_SRIE_WDG_RIE_SHIFT))&RGM_SRIE_WDG_RIE_MASK)

#define RGM_SRIE_CLKERR0_RIE_MASK      0x8u

#define RGM_SRIE_CLKERR0_RIE_SHIFT     3u

#define RGM_SRIE_CLKERR0_RIE_WIDTH     1u

#define RGM_SRIE_CLKERR0_RIE(x)        (((uint32_t)(((uint32_t)(x))<<RGM_SRIE_CLKERR0_RIE_SHIFT))&RGM_SRIE_CLKERR0_RIE_MASK)

#define RGM_SRIE_DELAY_MASK            0x3u

#define RGM_SRIE_DELAY_SHIFT           0u

#define RGM_SRIE_DELAY_WIDTH           2u

#define RGM_SRIE_DELAY(x)              (((uint32_t)(((uint32_t)(x))<<RGM_SRIE_DELAY_SHIFT))&RGM_SRIE_DELAY_MASK)

/* SRIE Reg Mask */

#define RGM_SRIE_MASK                  0x00003FEBu



/* C0_CFG Bit Fields */

#define RGM_C0_CFG_C0_SWRST_EN_MASK    0x100000u

#define RGM_C0_CFG_C0_SWRST_EN_SHIFT   20u

#define RGM_C0_CFG_C0_SWRST_EN_WIDTH   1u

#define RGM_C0_CFG_C0_SWRST_EN(x)      (((uint32_t)(((uint32_t)(x))<<RGM_C0_CFG_C0_SWRST_EN_SHIFT))&RGM_C0_CFG_C0_SWRST_EN_MASK)

#define RGM_C0_CFG_C0_INTM_EN_MASK     0x80000u

#define RGM_C0_CFG_C0_INTM_EN_SHIFT    19u

#define RGM_C0_CFG_C0_INTM_EN_WIDTH    1u

#define RGM_C0_CFG_C0_INTM_EN(x)       (((uint32_t)(((uint32_t)(x))<<RGM_C0_CFG_C0_INTM_EN_SHIFT))&RGM_C0_CFG_C0_INTM_EN_MASK)

#define RGM_C0_CFG_C0_WDOG_EN_MASK     0x40000u

#define RGM_C0_CFG_C0_WDOG_EN_SHIFT    18u

#define RGM_C0_CFG_C0_WDOG_EN_WIDTH    1u

#define RGM_C0_CFG_C0_WDOG_EN(x)       (((uint32_t)(((uint32_t)(x))<<RGM_C0_CFG_C0_WDOG_EN_SHIFT))&RGM_C0_CFG_C0_WDOG_EN_MASK)

#define RGM_C0_CFG_C0_SYSRST_EN_MASK   0x20000u

#define RGM_C0_CFG_C0_SYSRST_EN_SHIFT  17u

#define RGM_C0_CFG_C0_SYSRST_EN_WIDTH  1u

#define RGM_C0_CFG_C0_SYSRST_EN(x)     (((uint32_t)(((uint32_t)(x))<<RGM_C0_CFG_C0_SYSRST_EN_SHIFT))&RGM_C0_CFG_C0_SYSRST_EN_MASK)

#define RGM_C0_CFG_C0_LOCKUP_EN_MASK   0x10000u

#define RGM_C0_CFG_C0_LOCKUP_EN_SHIFT  16u

#define RGM_C0_CFG_C0_LOCKUP_EN_WIDTH  1u

#define RGM_C0_CFG_C0_LOCKUP_EN(x)     (((uint32_t)(((uint32_t)(x))<<RGM_C0_CFG_C0_LOCKUP_EN_SHIFT))&RGM_C0_CFG_C0_LOCKUP_EN_MASK)

#define RGM_C0_CFG_C0_SWRST_IE_MASK    0x10u

#define RGM_C0_CFG_C0_SWRST_IE_SHIFT   4u

#define RGM_C0_CFG_C0_SWRST_IE_WIDTH   1u

#define RGM_C0_CFG_C0_SWRST_IE(x)      (((uint32_t)(((uint32_t)(x))<<RGM_C0_CFG_C0_SWRST_IE_SHIFT))&RGM_C0_CFG_C0_SWRST_IE_MASK)

#define RGM_C0_CFG_C0_INTM_IE_MASK     0x8u

#define RGM_C0_CFG_C0_INTM_IE_SHIFT    3u

#define RGM_C0_CFG_C0_INTM_IE_WIDTH    1u

#define RGM_C0_CFG_C0_INTM_IE(x)       (((uint32_t)(((uint32_t)(x))<<RGM_C0_CFG_C0_INTM_IE_SHIFT))&RGM_C0_CFG_C0_INTM_IE_MASK)

#define RGM_C0_CFG_C0_WDOG_IE_MASK     0x4u

#define RGM_C0_CFG_C0_WDOG_IE_SHIFT    2u

#define RGM_C0_CFG_C0_WDOG_IE_WIDTH    1u

#define RGM_C0_CFG_C0_WDOG_IE(x)       (((uint32_t)(((uint32_t)(x))<<RGM_C0_CFG_C0_WDOG_IE_SHIFT))&RGM_C0_CFG_C0_WDOG_IE_MASK)

#define RGM_C0_CFG_C0_SYSRST_IE_MASK   0x2u

#define RGM_C0_CFG_C0_SYSRST_IE_SHIFT  1u

#define RGM_C0_CFG_C0_SYSRST_IE_WIDTH  1u

#define RGM_C0_CFG_C0_SYSRST_IE(x)     (((uint32_t)(((uint32_t)(x))<<RGM_C0_CFG_C0_SYSRST_IE_SHIFT))&RGM_C0_CFG_C0_SYSRST_IE_MASK)

#define RGM_C0_CFG_C0_LOCKUP_IE_MASK   0x1u

#define RGM_C0_CFG_C0_LOCKUP_IE_SHIFT  0u

#define RGM_C0_CFG_C0_LOCKUP_IE_WIDTH  1u

#define RGM_C0_CFG_C0_LOCKUP_IE(x)     (((uint32_t)(((uint32_t)(x))<<RGM_C0_CFG_C0_LOCKUP_IE_SHIFT))&RGM_C0_CFG_C0_LOCKUP_IE_MASK)

/* C0_CFG Reg Mask */

#define RGM_C0_CFG_MASK                0x001F001Fu



/* C0_RST Bit Fields */

#define RGM_C0_RST_C0_OUT_OF_RST_MASK  0x2u

#define RGM_C0_RST_C0_OUT_OF_RST_SHIFT 1u

#define RGM_C0_RST_C0_OUT_OF_RST_WIDTH 1u

#define RGM_C0_RST_C0_OUT_OF_RST(x)    (((uint32_t)(((uint32_t)(x))<<RGM_C0_RST_C0_OUT_OF_RST_SHIFT))&RGM_C0_RST_C0_OUT_OF_RST_MASK)

#define RGM_C0_RST_C0_SWRST_MASK       0x1u

#define RGM_C0_RST_C0_SWRST_SHIFT      0u

#define RGM_C0_RST_C0_SWRST_WIDTH      1u

#define RGM_C0_RST_C0_SWRST(x)         (((uint32_t)(((uint32_t)(x))<<RGM_C0_RST_C0_SWRST_SHIFT))&RGM_C0_RST_C0_SWRST_MASK)

/* C0_RST Reg Mask */

#define RGM_C0_RST_MASK                0x00000003u



/* C0_SRS Bit Fields */

#define RGM_C0_SRS_SYSRST_TOUT_MASK    0x80000000u

#define RGM_C0_SRS_SYSRST_TOUT_SHIFT   31u

#define RGM_C0_SRS_SYSRST_TOUT_WIDTH   1u

#define RGM_C0_SRS_SYSRST_TOUT(x)      (((uint32_t)(((uint32_t)(x))<<RGM_C0_SRS_SYSRST_TOUT_SHIFT))&RGM_C0_SRS_SYSRST_TOUT_MASK)

#define RGM_C0_SRS_PINRST_TOUT_MASK    0x40000000u

#define RGM_C0_SRS_PINRST_TOUT_SHIFT   30u

#define RGM_C0_SRS_PINRST_TOUT_WIDTH   1u

#define RGM_C0_SRS_PINRST_TOUT(x)      (((uint32_t)(((uint32_t)(x))<<RGM_C0_SRS_PINRST_TOUT_SHIFT))&RGM_C0_SRS_PINRST_TOUT_MASK)

#define RGM_C0_SRS_FSM_ERR_MASK        0x20000000u

#define RGM_C0_SRS_FSM_ERR_SHIFT       29u

#define RGM_C0_SRS_FSM_ERR_WIDTH       1u

#define RGM_C0_SRS_FSM_ERR(x)          (((uint32_t)(((uint32_t)(x))<<RGM_C0_SRS_FSM_ERR_SHIFT))&RGM_C0_SRS_FSM_ERR_MASK)

#define RGM_C0_SRS_C0_SWRST_MASK       0x100000u

#define RGM_C0_SRS_C0_SWRST_SHIFT      20u

#define RGM_C0_SRS_C0_SWRST_WIDTH      1u

#define RGM_C0_SRS_C0_SWRST(x)         (((uint32_t)(((uint32_t)(x))<<RGM_C0_SRS_C0_SWRST_SHIFT))&RGM_C0_SRS_C0_SWRST_MASK)

#define RGM_C0_SRS_C0_INTM_MASK        0x80000u

#define RGM_C0_SRS_C0_INTM_SHIFT       19u

#define RGM_C0_SRS_C0_INTM_WIDTH       1u

#define RGM_C0_SRS_C0_INTM(x)          (((uint32_t)(((uint32_t)(x))<<RGM_C0_SRS_C0_INTM_SHIFT))&RGM_C0_SRS_C0_INTM_MASK)

#define RGM_C0_SRS_C0_WDOG_MASK        0x40000u

#define RGM_C0_SRS_C0_WDOG_SHIFT       18u

#define RGM_C0_SRS_C0_WDOG_WIDTH       1u

#define RGM_C0_SRS_C0_WDOG(x)          (((uint32_t)(((uint32_t)(x))<<RGM_C0_SRS_C0_WDOG_SHIFT))&RGM_C0_SRS_C0_WDOG_MASK)

#define RGM_C0_SRS_C0_SYSRST_MASK      0x20000u

#define RGM_C0_SRS_C0_SYSRST_SHIFT     17u

#define RGM_C0_SRS_C0_SYSRST_WIDTH     1u

#define RGM_C0_SRS_C0_SYSRST(x)        (((uint32_t)(((uint32_t)(x))<<RGM_C0_SRS_C0_SYSRST_SHIFT))&RGM_C0_SRS_C0_SYSRST_MASK)

#define RGM_C0_SRS_C0_LOCKUP_MASK      0x10000u

#define RGM_C0_SRS_C0_LOCKUP_SHIFT     16u

#define RGM_C0_SRS_C0_LOCKUP_WIDTH     1u

#define RGM_C0_SRS_C0_LOCKUP(x)        (((uint32_t)(((uint32_t)(x))<<RGM_C0_SRS_C0_LOCKUP_SHIFT))&RGM_C0_SRS_C0_LOCKUP_MASK)

#define RGM_C0_SRS_C0_SRS_MASK         0xFFFFu

#define RGM_C0_SRS_C0_SRS_SHIFT        0u

#define RGM_C0_SRS_C0_SRS_WIDTH        16u

#define RGM_C0_SRS_C0_SRS(x)           (((uint32_t)(((uint32_t)(x))<<RGM_C0_SRS_C0_SRS_SHIFT))&RGM_C0_SRS_C0_SRS_MASK)

/* C0_SRS Reg Mask */

#define RGM_C0_SRS_MASK                0xE01FFFFFu



/* C0_SSRS Bit Fields */

#define RGM_C0_SSRS_SYSRST_TOUT_MASK   0x80000000u

#define RGM_C0_SSRS_SYSRST_TOUT_SHIFT  31u

#define RGM_C0_SSRS_SYSRST_TOUT_WIDTH  1u

#define RGM_C0_SSRS_SYSRST_TOUT(x)     (((uint32_t)(((uint32_t)(x))<<RGM_C0_SSRS_SYSRST_TOUT_SHIFT))&RGM_C0_SSRS_SYSRST_TOUT_MASK)

#define RGM_C0_SSRS_PINRST_TOUT_MASK   0x40000000u

#define RGM_C0_SSRS_PINRST_TOUT_SHIFT  30u

#define RGM_C0_SSRS_PINRST_TOUT_WIDTH  1u

#define RGM_C0_SSRS_PINRST_TOUT(x)     (((uint32_t)(((uint32_t)(x))<<RGM_C0_SSRS_PINRST_TOUT_SHIFT))&RGM_C0_SSRS_PINRST_TOUT_MASK)

#define RGM_C0_SSRS_FSM_ERR_MASK       0x20000000u

#define RGM_C0_SSRS_FSM_ERR_SHIFT      29u

#define RGM_C0_SSRS_FSM_ERR_WIDTH      1u

#define RGM_C0_SSRS_FSM_ERR(x)         (((uint32_t)(((uint32_t)(x))<<RGM_C0_SSRS_FSM_ERR_SHIFT))&RGM_C0_SSRS_FSM_ERR_MASK)

#define RGM_C0_SSRS_C0_SWRST_MASK      0x100000u

#define RGM_C0_SSRS_C0_SWRST_SHIFT     20u

#define RGM_C0_SSRS_C0_SWRST_WIDTH     1u

#define RGM_C0_SSRS_C0_SWRST(x)        (((uint32_t)(((uint32_t)(x))<<RGM_C0_SSRS_C0_SWRST_SHIFT))&RGM_C0_SSRS_C0_SWRST_MASK)

#define RGM_C0_SSRS_C0_INTM_MASK       0x80000u

#define RGM_C0_SSRS_C0_INTM_SHIFT      19u

#define RGM_C0_SSRS_C0_INTM_WIDTH      1u

#define RGM_C0_SSRS_C0_INTM(x)         (((uint32_t)(((uint32_t)(x))<<RGM_C0_SSRS_C0_INTM_SHIFT))&RGM_C0_SSRS_C0_INTM_MASK)

#define RGM_C0_SSRS_C0_WDOG_MASK       0x40000u

#define RGM_C0_SSRS_C0_WDOG_SHIFT      18u

#define RGM_C0_SSRS_C0_WDOG_WIDTH      1u

#define RGM_C0_SSRS_C0_WDOG(x)         (((uint32_t)(((uint32_t)(x))<<RGM_C0_SSRS_C0_WDOG_SHIFT))&RGM_C0_SSRS_C0_WDOG_MASK)

#define RGM_C0_SSRS_C0_SYSRST_MASK     0x20000u

#define RGM_C0_SSRS_C0_SYSRST_SHIFT    17u

#define RGM_C0_SSRS_C0_SYSRST_WIDTH    1u

#define RGM_C0_SSRS_C0_SYSRST(x)       (((uint32_t)(((uint32_t)(x))<<RGM_C0_SSRS_C0_SYSRST_SHIFT))&RGM_C0_SSRS_C0_SYSRST_MASK)

#define RGM_C0_SSRS_C0_LOCKUP_MASK     0x10000u

#define RGM_C0_SSRS_C0_LOCKUP_SHIFT    16u

#define RGM_C0_SSRS_C0_LOCKUP_WIDTH    1u

#define RGM_C0_SSRS_C0_LOCKUP(x)       (((uint32_t)(((uint32_t)(x))<<RGM_C0_SSRS_C0_LOCKUP_SHIFT))&RGM_C0_SSRS_C0_LOCKUP_MASK)

#define RGM_C0_SSRS_SSRS_MASK          0xFFFFu

#define RGM_C0_SSRS_SSRS_SHIFT         0u

#define RGM_C0_SSRS_SSRS_WIDTH         16u

#define RGM_C0_SSRS_SSRS(x)            (((uint32_t)(((uint32_t)(x))<<RGM_C0_SSRS_SSRS_SHIFT))&RGM_C0_SSRS_SSRS_MASK)

/* C0_SSRS Reg Mask */

#define RGM_C0_SSRS_MASK               0xE01FFFFFu





/*!

 * @}

 */ /* end of group RGM_Register_Masks */



/*!

 * @}

 */ /* end of group RGM_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
