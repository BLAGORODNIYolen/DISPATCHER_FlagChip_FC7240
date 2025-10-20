#ifndef _FC7240_FCSMU_NU_Tztufn38_REGS_H_
#define _FC7240_FCSMU_NU_Tztufn38_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- FCSMU Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup FCSMU_Peripheral_Access_Layer FCSMU Peripheral Access Layer

 * @{

 */



/** FCSMU - Size of Registers Arrays */



/** FCSMU - Register Layout Typedef */



typedef struct {



  __IO uint32_t CTRL                          ; /* Control Register, offset: 0x0 */

  __O  uint32_t OPRK                          ; /* Operation Key Register, offset: 0x4 */

  __IO uint32_t SOCTRL                        ; /* Status Output Control Register, offset: 0x8 */

  __IO uint32_t FCCR0                         ; /* Fault Clear Control Register 0, offset: 0xC */

       uint8_t  RESERVED_0[12];

  __IO uint32_t FRST0                         ; /* Fault Reset Control Register 0, offset: 0x1C */

       uint8_t  RESERVED_1[12];

  __IO uint32_t FST0                          ; /* Fault Status Register, offset: 0x2C */

       uint8_t  RESERVED_2[12];

  __O  uint32_t FST_UNLK                      ; /* Fault Status Register Unlock Register, offset: 0x3C */

  __IO uint32_t FE0                           ; /* Fault Enable Register, offset: 0x40 */

       uint8_t  RESERVED_3[12];

  __IO uint32_t WARNING_EN0                   ; /* Warning State Enable Register 0, offset: 0x50 */

       uint8_t  RESERVED_4[12];

  __IO uint32_t WARNING_TO                    ; /* Warning Timeout Interval Register, offset: 0x60 */

  __IO uint32_t CFG_TO                        ; /* Configuration State Timeout Interval Register, offset: 0x64 */

  __IO uint32_t SOUT_DIAG                     ; /* SOUT Diagnostic Register, offset: 0x68 */

  __I  uint32_t STATUS                        ; /* Status Register, offset: 0x6C */

  __I  uint32_t NTW                           ; /* Normal to Warning Register, offset: 0x70 */

  __I  uint32_t WTF                           ; /* Warning to Fault Register, offset: 0x74 */

  __I  uint32_t NTF                           ; /* Normal to Fault Register, offset: 0x78 */

  __I  uint32_t FTW                           ; /* Fault to Warning Register, offset: 0x7C */

       uint8_t  RESERVED_5[4];

  __O  uint32_t INJECT                        ; /* Fault Injection Register, offset: 0x84 */

  __IO uint32_t IRQ_STAT                      ; /* IRQ Status Register, offset: 0x88 */

  __IO uint32_t IRQ_EN                        ; /* IRQ Enable Register, offset: 0x8C */

       uint8_t  RESERVED_6[4];

  __O  uint32_t TEMP_UNLK                     ; /* Temporary Configuration State Unlock Register, offset: 0x94 */

  __O  uint32_t PERMNT_LOCK                   ; /* Permanent Configuration State Lock Register, offset: 0x98 */

  __IO uint32_t STMR                          ; /* SOUT Timer Interval Register, offset: 0x9C */

  __IO uint32_t WARNING_IEN0                  ; /* Warning State Interrupt Enable Register, offset: 0xA0 */

       uint8_t  RESERVED_7[12];

  __IO uint32_t FAULT_IEN0                    ; /* Fault State Interrupt Enable Register, offset: 0xB0 */

       uint8_t  RESERVED_8[12];

  __IO uint32_t SOUT_EN0                      ; /* SOUT Enable Register, offset: 0xC0 */

       uint8_t  RESERVED_9[12];

  __I  uint32_t WARNING_TMR                   ; /* Warning State Timer Register, offset: 0xD0 */

  __I  uint32_t SM_TMR                        ; /* Safe Mode State Timer Register, offset: 0xD4 */

  __I  uint32_t CFG_TMR                       ; /* Configuration State Timer Register, offset: 0xD8 */

  __I  uint32_t SOUT_TMR                      ; /* SOUT Timer Register, offset: 0xDC */

  __IO uint32_t CRC_CTRL                      ; /* CRC Control Register, offset: 0xE0 */

  __I  uint32_t CRC_RES                       ; /* CRC Result Register, offset: 0xE4 */



} FCSMU_Type, *FCSMU_MemMapPtr;



/** Number of instances of the FCSMU module. */

#define FCSMU_INSTANCE_COUNT                     (1u)



/* FCSMU - Peripheral instance base addresses */

/** Peripheral FCSMU base address */

#define FCSMU_BASE                               (0x4000f000u)

/** Peripheral FCSMU base pointer */

#define FCSMU                                    ((FCSMU_Type *)FCSMU_BASE)

/** Array initializer of FCSMU peripheral base addresses */

#define FCSMU_BASE_ADDRS                         {FCSMU_BASE}

/** Array initializer of FCSMU peripheral base pointers */

#define FCSMU_BASE_PTRS                          {FCSMU}

// need fill by yourself

///** Number of interrupt vector arrays for the FCSMU module. */

//#define FCSMU_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the FCSMU module. */

//#define FCSMU_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the FCSMU peripheral type */

//#define FCSMU_IRQS                               {FCSMU_IRQn}





/* ----------------------------------------------------------------------------

   -- FCSMU Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup FCSMU_Register_Masks FCSMU Register Masks

 * @{

 */



/* CTRL Bit Fields */

#define FCSMU_CTRL_DBGEN_MASK          0x200u

#define FCSMU_CTRL_DBGEN_SHIFT         9u

#define FCSMU_CTRL_DBGEN_WIDTH         1u

#define FCSMU_CTRL_DBGEN(x)            (((uint32_t)(((uint32_t)(x))<<FCSMU_CTRL_DBGEN_SHIFT))&FCSMU_CTRL_DBGEN_MASK)

#define FCSMU_CTRL_OPS_MASK            0xC0u

#define FCSMU_CTRL_OPS_SHIFT           6u

#define FCSMU_CTRL_OPS_WIDTH           2u

#define FCSMU_CTRL_OPS(x)              (((uint32_t)(((uint32_t)(x))<<FCSMU_CTRL_OPS_SHIFT))&FCSMU_CTRL_OPS_MASK)

#define FCSMU_CTRL_OPC_MASK            0x1Fu

#define FCSMU_CTRL_OPC_SHIFT           0u

#define FCSMU_CTRL_OPC_WIDTH           5u

#define FCSMU_CTRL_OPC(x)              (((uint32_t)(((uint32_t)(x))<<FCSMU_CTRL_OPC_SHIFT))&FCSMU_CTRL_OPC_MASK)

/* CTRL Reg Mask */

#define FCSMU_CTRL_MASK                0x000002DFu



/* OPRK Bit Fields */

#define FCSMU_OPRK_OPKEY_MASK          0xFFFFFFFFu

#define FCSMU_OPRK_OPKEY_SHIFT         0u

#define FCSMU_OPRK_OPKEY_WIDTH         32u

#define FCSMU_OPRK_OPKEY(x)            (((uint32_t)(((uint32_t)(x))<<FCSMU_OPRK_OPKEY_SHIFT))&FCSMU_OPRK_OPKEY_MASK)

/* OPRK Reg Mask */

#define FCSMU_OPRK_MASK                0xFFFFFFFFu



/* SOCTRL Bit Fields */

#define FCSMU_SOCTRL_SOUT_PEN_MASK     0x2000000u

#define FCSMU_SOCTRL_SOUT_PEN_SHIFT    25u

#define FCSMU_SOCTRL_SOUT_PEN_WIDTH    1u

#define FCSMU_SOCTRL_SOUT_PEN(x)       (((uint32_t)(((uint32_t)(x))<<FCSMU_SOCTRL_SOUT_PEN_SHIFT))&FCSMU_SOCTRL_SOUT_PEN_MASK)

#define FCSMU_SOCTRL_SOUT_CTRL_MASK    0x1800000u

#define FCSMU_SOCTRL_SOUT_CTRL_SHIFT   23u

#define FCSMU_SOCTRL_SOUT_CTRL_WIDTH   2u

#define FCSMU_SOCTRL_SOUT_CTRL(x)      (((uint32_t)(((uint32_t)(x))<<FCSMU_SOCTRL_SOUT_CTRL_SHIFT))&FCSMU_SOCTRL_SOUT_CTRL_MASK)

#define FCSMU_SOCTRL_DIVEX_MASK        0x200000u

#define FCSMU_SOCTRL_DIVEX_SHIFT       21u

#define FCSMU_SOCTRL_DIVEX_WIDTH       1u

#define FCSMU_SOCTRL_DIVEX(x)          (((uint32_t)(((uint32_t)(x))<<FCSMU_SOCTRL_DIVEX_SHIFT))&FCSMU_SOCTRL_DIVEX_MASK)

#define FCSMU_SOCTRL_SMRDT_MASK        0x1E0000u

#define FCSMU_SOCTRL_SMRDT_SHIFT       17u

#define FCSMU_SOCTRL_SMRDT_WIDTH       4u

#define FCSMU_SOCTRL_SMRDT(x)          (((uint32_t)(((uint32_t)(x))<<FCSMU_SOCTRL_SMRDT_SHIFT))&FCSMU_SOCTRL_SMRDT_MASK)

#define FCSMU_SOCTRL_FASTEN_MASK       0x4000u

#define FCSMU_SOCTRL_FASTEN_SHIFT      14u

#define FCSMU_SOCTRL_FASTEN_WIDTH      1u

#define FCSMU_SOCTRL_FASTEN(x)         (((uint32_t)(((uint32_t)(x))<<FCSMU_SOCTRL_FASTEN_SHIFT))&FCSMU_SOCTRL_FASTEN_MASK)

#define FCSMU_SOCTRL_POLSW_MASK        0x2000u

#define FCSMU_SOCTRL_POLSW_SHIFT       13u

#define FCSMU_SOCTRL_POLSW_WIDTH       1u

#define FCSMU_SOCTRL_POLSW(x)          (((uint32_t)(((uint32_t)(x))<<FCSMU_SOCTRL_POLSW_SHIFT))&FCSMU_SOCTRL_POLSW_MASK)

#define FCSMU_SOCTRL_SOUT_PTC_MASK     0x1C00u

#define FCSMU_SOCTRL_SOUT_PTC_SHIFT    10u

#define FCSMU_SOCTRL_SOUT_PTC_WIDTH    3u

#define FCSMU_SOCTRL_SOUT_PTC(x)       (((uint32_t)(((uint32_t)(x))<<FCSMU_SOCTRL_SOUT_PTC_SHIFT))&FCSMU_SOCTRL_SOUT_PTC_MASK)

#define FCSMU_SOCTRL_SOUT_DIV_MASK     0x3FFu

#define FCSMU_SOCTRL_SOUT_DIV_SHIFT    0u

#define FCSMU_SOCTRL_SOUT_DIV_WIDTH    10u

#define FCSMU_SOCTRL_SOUT_DIV(x)       (((uint32_t)(((uint32_t)(x))<<FCSMU_SOCTRL_SOUT_DIV_SHIFT))&FCSMU_SOCTRL_SOUT_DIV_MASK)

/* SOCTRL Reg Mask */

#define FCSMU_SOCTRL_MASK              0x03BE7FFFu



/* FCCR0 Bit Fields */

#define FCSMU_FCCR0_FCC_MASK           0xFFFFFFFFu

#define FCSMU_FCCR0_FCC_SHIFT          0u

#define FCSMU_FCCR0_FCC_WIDTH          32u

#define FCSMU_FCCR0_FCC(x)             (((uint32_t)(((uint32_t)(x))<<FCSMU_FCCR0_FCC_SHIFT))&FCSMU_FCCR0_FCC_MASK)

/* FCCR0 Reg Mask */

#define FCSMU_FCCR0_MASK               0xFFFFFFFFu



/* FRST0 Bit Fields */

#define FCSMU_FRST0_FRST_MASK          0xFFFFFFFFu

#define FCSMU_FRST0_FRST_SHIFT         0u

#define FCSMU_FRST0_FRST_WIDTH         32u

#define FCSMU_FRST0_FRST(x)            (((uint32_t)(((uint32_t)(x))<<FCSMU_FRST0_FRST_SHIFT))&FCSMU_FRST0_FRST_MASK)

/* FRST0 Reg Mask */

#define FCSMU_FRST0_MASK               0xFFFFFFFFu



/* FST0 Bit Fields */

#define FCSMU_FST0_ST_MASK             0xFFFFFFFFu

#define FCSMU_FST0_ST_SHIFT            0u

#define FCSMU_FST0_ST_WIDTH            32u

#define FCSMU_FST0_ST(x)               (((uint32_t)(((uint32_t)(x))<<FCSMU_FST0_ST_SHIFT))&FCSMU_FST0_ST_MASK)

/* FST0 Reg Mask */

#define FCSMU_FST0_MASK                0xFFFFFFFFu



/* FST_UNLK Bit Fields */

#define FCSMU_FST_UNLK_KEY_MASK        0xFFFFFFFFu

#define FCSMU_FST_UNLK_KEY_SHIFT       0u

#define FCSMU_FST_UNLK_KEY_WIDTH       32u

#define FCSMU_FST_UNLK_KEY(x)          (((uint32_t)(((uint32_t)(x))<<FCSMU_FST_UNLK_KEY_SHIFT))&FCSMU_FST_UNLK_KEY_MASK)

/* FST_UNLK Reg Mask */

#define FCSMU_FST_UNLK_MASK            0xFFFFFFFFu



/* FE0 Bit Fields */

#define FCSMU_FE0_EN_MASK              0xFFFFFFFFu

#define FCSMU_FE0_EN_SHIFT             0u

#define FCSMU_FE0_EN_WIDTH             32u

#define FCSMU_FE0_EN(x)                (((uint32_t)(((uint32_t)(x))<<FCSMU_FE0_EN_SHIFT))&FCSMU_FE0_EN_MASK)

/* FE0 Reg Mask */

#define FCSMU_FE0_MASK                 0xFFFFFFFFu



/* WARNING_EN0 Bit Fields */

#define FCSMU_WARNING_EN0_EN_MASK      0xFFFFFFFFu

#define FCSMU_WARNING_EN0_EN_SHIFT     0u

#define FCSMU_WARNING_EN0_EN_WIDTH     32u

#define FCSMU_WARNING_EN0_EN(x)        (((uint32_t)(((uint32_t)(x))<<FCSMU_WARNING_EN0_EN_SHIFT))&FCSMU_WARNING_EN0_EN_MASK)

/* WARNING_EN0 Reg Mask */

#define FCSMU_WARNING_EN0_MASK         0xFFFFFFFFu



/* WARNING_TO Bit Fields */

#define FCSMU_WARNING_TO_TIME_MASK     0xFFFFFFFFu

#define FCSMU_WARNING_TO_TIME_SHIFT    0u

#define FCSMU_WARNING_TO_TIME_WIDTH    32u

#define FCSMU_WARNING_TO_TIME(x)       (((uint32_t)(((uint32_t)(x))<<FCSMU_WARNING_TO_TIME_SHIFT))&FCSMU_WARNING_TO_TIME_MASK)

/* WARNING_TO Reg Mask */

#define FCSMU_WARNING_TO_MASK          0xFFFFFFFFu



/* CFG_TO Bit Fields */

#define FCSMU_CFG_TO_TIME_MASK         0x7u

#define FCSMU_CFG_TO_TIME_SHIFT        0u

#define FCSMU_CFG_TO_TIME_WIDTH        3u

#define FCSMU_CFG_TO_TIME(x)           (((uint32_t)(((uint32_t)(x))<<FCSMU_CFG_TO_TIME_SHIFT))&FCSMU_CFG_TO_TIME_MASK)

/* CFG_TO Reg Mask */

#define FCSMU_CFG_TO_MASK              0x00000007u



/* SOUT_DIAG Bit Fields */

#define FCSMU_SOUT_DIAG_SIN1_MASK      0x20u

#define FCSMU_SOUT_DIAG_SIN1_SHIFT     5u

#define FCSMU_SOUT_DIAG_SIN1_WIDTH     1u

#define FCSMU_SOUT_DIAG_SIN1(x)        (((uint32_t)(((uint32_t)(x))<<FCSMU_SOUT_DIAG_SIN1_SHIFT))&FCSMU_SOUT_DIAG_SIN1_MASK)

#define FCSMU_SOUT_DIAG_SIN0_MASK      0x10u

#define FCSMU_SOUT_DIAG_SIN0_SHIFT     4u

#define FCSMU_SOUT_DIAG_SIN0_WIDTH     1u

#define FCSMU_SOUT_DIAG_SIN0(x)        (((uint32_t)(((uint32_t)(x))<<FCSMU_SOUT_DIAG_SIN0_SHIFT))&FCSMU_SOUT_DIAG_SIN0_MASK)

#define FCSMU_SOUT_DIAG_SOUT1_MASK     0x2u

#define FCSMU_SOUT_DIAG_SOUT1_SHIFT    1u

#define FCSMU_SOUT_DIAG_SOUT1_WIDTH    1u

#define FCSMU_SOUT_DIAG_SOUT1(x)       (((uint32_t)(((uint32_t)(x))<<FCSMU_SOUT_DIAG_SOUT1_SHIFT))&FCSMU_SOUT_DIAG_SOUT1_MASK)

#define FCSMU_SOUT_DIAG_SOUT0_MASK     0x1u

#define FCSMU_SOUT_DIAG_SOUT0_SHIFT    0u

#define FCSMU_SOUT_DIAG_SOUT0_WIDTH    1u

#define FCSMU_SOUT_DIAG_SOUT0(x)       (((uint32_t)(((uint32_t)(x))<<FCSMU_SOUT_DIAG_SOUT0_SHIFT))&FCSMU_SOUT_DIAG_SOUT0_MASK)

/* SOUT_DIAG Reg Mask */

#define FCSMU_SOUT_DIAG_MASK           0x00000033u



/* STATUS Bit Fields */

#define FCSMU_STATUS_SOUTPIN_MASK      0x30u

#define FCSMU_STATUS_SOUTPIN_SHIFT     4u

#define FCSMU_STATUS_SOUTPIN_WIDTH     2u

#define FCSMU_STATUS_SOUTPIN(x)        (((uint32_t)(((uint32_t)(x))<<FCSMU_STATUS_SOUTPIN_SHIFT))&FCSMU_STATUS_SOUTPIN_MASK)

#define FCSMU_STATUS_FIF_MASK          0x8u

#define FCSMU_STATUS_FIF_SHIFT         3u

#define FCSMU_STATUS_FIF_WIDTH         1u

#define FCSMU_STATUS_FIF(x)            (((uint32_t)(((uint32_t)(x))<<FCSMU_STATUS_FIF_SHIFT))&FCSMU_STATUS_FIF_MASK)

#define FCSMU_STATUS_STAT_MASK         0x7u

#define FCSMU_STATUS_STAT_SHIFT        0u

#define FCSMU_STATUS_STAT_WIDTH        3u

#define FCSMU_STATUS_STAT(x)           (((uint32_t)(((uint32_t)(x))<<FCSMU_STATUS_STAT_SHIFT))&FCSMU_STATUS_STAT_MASK)

/* STATUS Reg Mask */

#define FCSMU_STATUS_MASK              0x0000003Fu



/* NTW Bit Fields */

#define FCSMU_NTW_INDEX_MASK           0xFFu

#define FCSMU_NTW_INDEX_SHIFT          0u

#define FCSMU_NTW_INDEX_WIDTH          8u

#define FCSMU_NTW_INDEX(x)             (((uint32_t)(((uint32_t)(x))<<FCSMU_NTW_INDEX_SHIFT))&FCSMU_NTW_INDEX_MASK)

/* NTW Reg Mask */

#define FCSMU_NTW_MASK                 0x000000FFu



/* WTF Bit Fields */

#define FCSMU_WTF_FLAG_MASK            0x200u

#define FCSMU_WTF_FLAG_SHIFT           9u

#define FCSMU_WTF_FLAG_WIDTH           1u

#define FCSMU_WTF_FLAG(x)              (((uint32_t)(((uint32_t)(x))<<FCSMU_WTF_FLAG_SHIFT))&FCSMU_WTF_FLAG_MASK)

#define FCSMU_WTF_INDEX_MASK           0xFFu

#define FCSMU_WTF_INDEX_SHIFT          0u

#define FCSMU_WTF_INDEX_WIDTH          8u

#define FCSMU_WTF_INDEX(x)             (((uint32_t)(((uint32_t)(x))<<FCSMU_WTF_INDEX_SHIFT))&FCSMU_WTF_INDEX_MASK)

/* WTF Reg Mask */

#define FCSMU_WTF_MASK                 0x000002FFu



/* NTF Bit Fields */

#define FCSMU_NTF_FLAG_MASK            0x200u

#define FCSMU_NTF_FLAG_SHIFT           9u

#define FCSMU_NTF_FLAG_WIDTH           1u

#define FCSMU_NTF_FLAG(x)              (((uint32_t)(((uint32_t)(x))<<FCSMU_NTF_FLAG_SHIFT))&FCSMU_NTF_FLAG_MASK)

#define FCSMU_NTF_INDEX_MASK           0xFFu

#define FCSMU_NTF_INDEX_SHIFT          0u

#define FCSMU_NTF_INDEX_WIDTH          8u

#define FCSMU_NTF_INDEX(x)             (((uint32_t)(((uint32_t)(x))<<FCSMU_NTF_INDEX_SHIFT))&FCSMU_NTF_INDEX_MASK)

/* NTF Reg Mask */

#define FCSMU_NTF_MASK                 0x000002FFu



/* FTW Bit Fields */

#define FCSMU_FTW_INDEX_MASK           0xFFu

#define FCSMU_FTW_INDEX_SHIFT          0u

#define FCSMU_FTW_INDEX_WIDTH          8u

#define FCSMU_FTW_INDEX(x)             (((uint32_t)(((uint32_t)(x))<<FCSMU_FTW_INDEX_SHIFT))&FCSMU_FTW_INDEX_MASK)

/* FTW Reg Mask */

#define FCSMU_FTW_MASK                 0x000000FFu



/* INJECT Bit Fields */

#define FCSMU_INJECT_INDEX_MASK        0x7Fu

#define FCSMU_INJECT_INDEX_SHIFT       0u

#define FCSMU_INJECT_INDEX_WIDTH       7u

#define FCSMU_INJECT_INDEX(x)          (((uint32_t)(((uint32_t)(x))<<FCSMU_INJECT_INDEX_SHIFT))&FCSMU_INJECT_INDEX_MASK)

/* INJECT Reg Mask */

#define FCSMU_INJECT_MASK              0x0000007Fu



/* IRQ_STAT Bit Fields */

#define FCSMU_IRQ_STAT_FAULT_IRQ_MASK  0x4u

#define FCSMU_IRQ_STAT_FAULT_IRQ_SHIFT 2u

#define FCSMU_IRQ_STAT_FAULT_IRQ_WIDTH 1u

#define FCSMU_IRQ_STAT_FAULT_IRQ(x)    (((uint32_t)(((uint32_t)(x))<<FCSMU_IRQ_STAT_FAULT_IRQ_SHIFT))&FCSMU_IRQ_STAT_FAULT_IRQ_MASK)

#define FCSMU_IRQ_STAT_WARNING_IRQ_MASK 0x2u

#define FCSMU_IRQ_STAT_WARNING_IRQ_SHIFT 1u

#define FCSMU_IRQ_STAT_WARNING_IRQ_WIDTH 1u

#define FCSMU_IRQ_STAT_WARNING_IRQ(x)  (((uint32_t)(((uint32_t)(x))<<FCSMU_IRQ_STAT_WARNING_IRQ_SHIFT))&FCSMU_IRQ_STAT_WARNING_IRQ_MASK)

#define FCSMU_IRQ_STAT_CFG_TO_IRQ_MASK 0x1u

#define FCSMU_IRQ_STAT_CFG_TO_IRQ_SHIFT 0u

#define FCSMU_IRQ_STAT_CFG_TO_IRQ_WIDTH 1u

#define FCSMU_IRQ_STAT_CFG_TO_IRQ(x)   (((uint32_t)(((uint32_t)(x))<<FCSMU_IRQ_STAT_CFG_TO_IRQ_SHIFT))&FCSMU_IRQ_STAT_CFG_TO_IRQ_MASK)

/* IRQ_STAT Reg Mask */

#define FCSMU_IRQ_STAT_MASK            0x00000007u



/* IRQ_EN Bit Fields */

#define FCSMU_IRQ_EN_CFG_TO_IEN_MASK   0x1u

#define FCSMU_IRQ_EN_CFG_TO_IEN_SHIFT  0u

#define FCSMU_IRQ_EN_CFG_TO_IEN_WIDTH  1u

#define FCSMU_IRQ_EN_CFG_TO_IEN(x)     (((uint32_t)(((uint32_t)(x))<<FCSMU_IRQ_EN_CFG_TO_IEN_SHIFT))&FCSMU_IRQ_EN_CFG_TO_IEN_MASK)

/* IRQ_EN Reg Mask */

#define FCSMU_IRQ_EN_MASK              0x00000001u



/* TEMP_UNLK Bit Fields */

#define FCSMU_TEMP_UNLK_KEY_MASK       0x1FFu

#define FCSMU_TEMP_UNLK_KEY_SHIFT      0u

#define FCSMU_TEMP_UNLK_KEY_WIDTH      9u

#define FCSMU_TEMP_UNLK_KEY(x)         (((uint32_t)(((uint32_t)(x))<<FCSMU_TEMP_UNLK_KEY_SHIFT))&FCSMU_TEMP_UNLK_KEY_MASK)

/* TEMP_UNLK Reg Mask */

#define FCSMU_TEMP_UNLK_MASK           0x000001FFu



/* PERMNT_LOCK Bit Fields */

#define FCSMU_PERMNT_LOCK_KEY_MASK     0x1FFu

#define FCSMU_PERMNT_LOCK_KEY_SHIFT    0u

#define FCSMU_PERMNT_LOCK_KEY_WIDTH    9u

#define FCSMU_PERMNT_LOCK_KEY(x)       (((uint32_t)(((uint32_t)(x))<<FCSMU_PERMNT_LOCK_KEY_SHIFT))&FCSMU_PERMNT_LOCK_KEY_MASK)

/* PERMNT_LOCK Reg Mask */

#define FCSMU_PERMNT_LOCK_MASK         0x000001FFu



/* STMR Bit Fields */

#define FCSMU_STMR_FTTI_MASK           0xC0000000u

#define FCSMU_STMR_FTTI_SHIFT          30u

#define FCSMU_STMR_FTTI_WIDTH          2u

#define FCSMU_STMR_FTTI(x)             (((uint32_t)(((uint32_t)(x))<<FCSMU_STMR_FTTI_SHIFT))&FCSMU_STMR_FTTI_MASK)

#define FCSMU_STMR_MTE_MASK            0x4000u

#define FCSMU_STMR_MTE_SHIFT           14u

#define FCSMU_STMR_MTE_WIDTH           1u

#define FCSMU_STMR_MTE(x)              (((uint32_t)(((uint32_t)(x))<<FCSMU_STMR_MTE_SHIFT))&FCSMU_STMR_MTE_MASK)

#define FCSMU_STMR_MINI_TIME_MASK      0x3FFFu

#define FCSMU_STMR_MINI_TIME_SHIFT     0u

#define FCSMU_STMR_MINI_TIME_WIDTH     14u

#define FCSMU_STMR_MINI_TIME(x)        (((uint32_t)(((uint32_t)(x))<<FCSMU_STMR_MINI_TIME_SHIFT))&FCSMU_STMR_MINI_TIME_MASK)

/* STMR Reg Mask */

#define FCSMU_STMR_MASK                0xC0007FFFu



/* WARNING_IEN0 Bit Fields */

#define FCSMU_WARNING_IEN0_EN_MASK     0xFFFFFFFFu

#define FCSMU_WARNING_IEN0_EN_SHIFT    0u

#define FCSMU_WARNING_IEN0_EN_WIDTH    32u

#define FCSMU_WARNING_IEN0_EN(x)       (((uint32_t)(((uint32_t)(x))<<FCSMU_WARNING_IEN0_EN_SHIFT))&FCSMU_WARNING_IEN0_EN_MASK)

/* WARNING_IEN0 Reg Mask */

#define FCSMU_WARNING_IEN0_MASK        0xFFFFFFFFu



/* FAULT_IEN0 Bit Fields */

#define FCSMU_FAULT_IEN0_EN_MASK       0xFFFFFFFFu

#define FCSMU_FAULT_IEN0_EN_SHIFT      0u

#define FCSMU_FAULT_IEN0_EN_WIDTH      32u

#define FCSMU_FAULT_IEN0_EN(x)         (((uint32_t)(((uint32_t)(x))<<FCSMU_FAULT_IEN0_EN_SHIFT))&FCSMU_FAULT_IEN0_EN_MASK)

/* FAULT_IEN0 Reg Mask */

#define FCSMU_FAULT_IEN0_MASK          0xFFFFFFFFu



/* SOUT_EN0 Bit Fields */

#define FCSMU_SOUT_EN0_EN_MASK         0xFFFFFFFFu

#define FCSMU_SOUT_EN0_EN_SHIFT        0u

#define FCSMU_SOUT_EN0_EN_WIDTH        32u

#define FCSMU_SOUT_EN0_EN(x)           (((uint32_t)(((uint32_t)(x))<<FCSMU_SOUT_EN0_EN_SHIFT))&FCSMU_SOUT_EN0_EN_MASK)

/* SOUT_EN0 Reg Mask */

#define FCSMU_SOUT_EN0_MASK            0xFFFFFFFFu



/* WARNING_TMR Bit Fields */

#define FCSMU_WARNING_TMR_VAL_MASK     0xFFFFFFFFu

#define FCSMU_WARNING_TMR_VAL_SHIFT    0u

#define FCSMU_WARNING_TMR_VAL_WIDTH    32u

#define FCSMU_WARNING_TMR_VAL(x)       (((uint32_t)(((uint32_t)(x))<<FCSMU_WARNING_TMR_VAL_SHIFT))&FCSMU_WARNING_TMR_VAL_MASK)

/* WARNING_TMR Reg Mask */

#define FCSMU_WARNING_TMR_MASK         0xFFFFFFFFu



/* SM_TMR Bit Fields */

#define FCSMU_SM_TMR_VAL_MASK          0xFFFFu

#define FCSMU_SM_TMR_VAL_SHIFT         0u

#define FCSMU_SM_TMR_VAL_WIDTH         16u

#define FCSMU_SM_TMR_VAL(x)            (((uint32_t)(((uint32_t)(x))<<FCSMU_SM_TMR_VAL_SHIFT))&FCSMU_SM_TMR_VAL_MASK)

/* SM_TMR Reg Mask */

#define FCSMU_SM_TMR_MASK              0x0000FFFFu



/* CFG_TMR Bit Fields */

#define FCSMU_CFG_TMR_VAL_MASK         0x1FFFFFu

#define FCSMU_CFG_TMR_VAL_SHIFT        0u

#define FCSMU_CFG_TMR_VAL_WIDTH        21u

#define FCSMU_CFG_TMR_VAL(x)           (((uint32_t)(((uint32_t)(x))<<FCSMU_CFG_TMR_VAL_SHIFT))&FCSMU_CFG_TMR_VAL_MASK)

/* CFG_TMR Reg Mask */

#define FCSMU_CFG_TMR_MASK             0x001FFFFFu



/* SOUT_TMR Bit Fields */

#define FCSMU_SOUT_TMR_VAL_MASK        0x7FFFFFu

#define FCSMU_SOUT_TMR_VAL_SHIFT       0u

#define FCSMU_SOUT_TMR_VAL_WIDTH       23u

#define FCSMU_SOUT_TMR_VAL(x)          (((uint32_t)(((uint32_t)(x))<<FCSMU_SOUT_TMR_VAL_SHIFT))&FCSMU_SOUT_TMR_VAL_MASK)

/* SOUT_TMR Reg Mask */

#define FCSMU_SOUT_TMR_MASK            0x007FFFFFu



/* CRC_CTRL Bit Fields */

#define FCSMU_CRC_CTRL_DONE_MASK       0x40u

#define FCSMU_CRC_CTRL_DONE_SHIFT      6u

#define FCSMU_CRC_CTRL_DONE_WIDTH      1u

#define FCSMU_CRC_CTRL_DONE(x)         (((uint32_t)(((uint32_t)(x))<<FCSMU_CRC_CTRL_DONE_SHIFT))&FCSMU_CRC_CTRL_DONE_MASK)

#define FCSMU_CRC_CTRL_EF_MASK         0x20u

#define FCSMU_CRC_CTRL_EF_SHIFT        5u

#define FCSMU_CRC_CTRL_EF_WIDTH        1u

#define FCSMU_CRC_CTRL_EF(x)           (((uint32_t)(((uint32_t)(x))<<FCSMU_CRC_CTRL_EF_SHIFT))&FCSMU_CRC_CTRL_EF_MASK)

#define FCSMU_CRC_CTRL_BUSY_MASK       0x10u

#define FCSMU_CRC_CTRL_BUSY_SHIFT      4u

#define FCSMU_CRC_CTRL_BUSY_WIDTH      1u

#define FCSMU_CRC_CTRL_BUSY(x)         (((uint32_t)(((uint32_t)(x))<<FCSMU_CRC_CTRL_BUSY_SHIFT))&FCSMU_CRC_CTRL_BUSY_MASK)

#define FCSMU_CRC_CTRL_EOEN_MASK       0x8u

#define FCSMU_CRC_CTRL_EOEN_SHIFT      3u

#define FCSMU_CRC_CTRL_EOEN_WIDTH      1u

#define FCSMU_CRC_CTRL_EOEN(x)         (((uint32_t)(((uint32_t)(x))<<FCSMU_CRC_CTRL_EOEN_SHIFT))&FCSMU_CRC_CTRL_EOEN_MASK)

#define FCSMU_CRC_CTRL_CHKEN_MASK      0x4u

#define FCSMU_CRC_CTRL_CHKEN_SHIFT     2u

#define FCSMU_CRC_CTRL_CHKEN_WIDTH     1u

#define FCSMU_CRC_CTRL_CHKEN(x)        (((uint32_t)(((uint32_t)(x))<<FCSMU_CRC_CTRL_CHKEN_SHIFT))&FCSMU_CRC_CTRL_CHKEN_MASK)

#define FCSMU_CRC_CTRL_TRGEN_MASK      0x2u

#define FCSMU_CRC_CTRL_TRGEN_SHIFT     1u

#define FCSMU_CRC_CTRL_TRGEN_WIDTH     1u

#define FCSMU_CRC_CTRL_TRGEN(x)        (((uint32_t)(((uint32_t)(x))<<FCSMU_CRC_CTRL_TRGEN_SHIFT))&FCSMU_CRC_CTRL_TRGEN_MASK)

#define FCSMU_CRC_CTRL_GEN_MASK        0x1u

#define FCSMU_CRC_CTRL_GEN_SHIFT       0u

#define FCSMU_CRC_CTRL_GEN_WIDTH       1u

#define FCSMU_CRC_CTRL_GEN(x)          (((uint32_t)(((uint32_t)(x))<<FCSMU_CRC_CTRL_GEN_SHIFT))&FCSMU_CRC_CTRL_GEN_MASK)

/* CRC_CTRL Reg Mask */

#define FCSMU_CRC_CTRL_MASK            0x0000007Fu



/* CRC_RES Bit Fields */

#define FCSMU_CRC_RES_RESULT_MASK      0xFFFFFFFFu

#define FCSMU_CRC_RES_RESULT_SHIFT     0u

#define FCSMU_CRC_RES_RESULT_WIDTH     32u

#define FCSMU_CRC_RES_RESULT(x)        (((uint32_t)(((uint32_t)(x))<<FCSMU_CRC_RES_RESULT_SHIFT))&FCSMU_CRC_RES_RESULT_MASK)

/* CRC_RES Reg Mask */

#define FCSMU_CRC_RES_MASK             0xFFFFFFFFu





/*!

 * @}

 */ /* end of group FCSMU_Register_Masks */



/*!

 * @}

 */ /* end of group FCSMU_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
