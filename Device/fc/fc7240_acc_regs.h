#ifndef _FC7240_ACC_NU_Tztufn3_REGS_H_
#define _FC7240_ACC_NU_Tztufn3_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- ACC Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup ACC_Peripheral_Access_Layer ACC Peripheral Access Layer

 * @{

 */



/** ACC - Size of Registers Arrays */



/** ACC - Register Layout Typedef */

#define ACC_IEBR_COUNT 2

#define ACC_DEBR_COUNT 2



typedef struct {



       uint8_t  RESERVED_0[20];

  __IO uint32_t CCR                           ; /* Configuration and Control Register, offset: 0x14 */

       uint8_t  RESERVED_1[96];

  __I  uint32_t CLIDR                         ; /* Cache Level ID Register, offset: 0x78 */

  __I  uint32_t CTR                           ; /* Cache Type Register, offset: 0x7C */

  __I  uint32_t CCSIDR                        ; /* Cache Size ID Register, offset: 0x80 */

  __IO uint32_t CSSELR                        ; /* Cache Size Selection Register, offset: 0x84 */

       uint8_t  RESERVED_2[456];

  __O  uint32_t ICIALLU                       ; /* I-cache Invalidate All to PoU Register, offset: 0x250 */

       uint8_t  RESERVED_3[4];

  __O  uint32_t ICIMVAU                       ; /* I-cache Invalidate by MVA to PoU Register, offset: 0x258 */

  __O  uint32_t DCIMVAC                       ; /* D-cache Invalidate by MVA to PoC Register, offset: 0x25C */

  __O  uint32_t DCISW                         ; /* D-cache Invalidate by Set-way Register, offset: 0x260 */

  __O  uint32_t DCCMVAU                       ; /* D-cache Clean by MVA to PoU Register, offset: 0x264 */

  __O  uint32_t DCCMVAC                       ; /* D-cache Clean by MVA to PoC Register, offset: 0x268 */

  __O  uint32_t DCCSW                         ; /* D-cache Clean by Set-way Register, offset: 0x26C */

  __O  uint32_t DCCIMVAC                      ; /* D-cache Clean and Invalidate by MVA to PoC Register, offset: 0x270 */

  __O  uint32_t DCCISW                        ; /* D-cache Clean and Invalidate by Set-way Register, offset: 0x274 */

       uint8_t  RESERVED_4[36];

  __IO uint32_t CACR                          ; /* L1 Cache Control Register, offset: 0x29C */

       uint8_t  RESERVED_5[16];

  __IO uint32_t IEBR[ACC_IEBR_COUNT]          ; /* Instruction Error Bank Register, offset: 0x2b0 */

  __IO uint32_t DEBR[ACC_DEBR_COUNT]          ; /* Data Error Bank Register, offset: 0x2b8 */



} ACC_Type, *ACC_MemMapPtr;



/** Number of instances of the ACC module. */

#define ACC_INSTANCE_COUNT                       (1u)



/* ACC - Peripheral instance base addresses */

/** Peripheral ACC base address */

#define ACC_BASE                                 (0xE000ED00u)

/** Peripheral ACC base pointer */

#define ACC                                      ((ACC_Type *)ACC_BASE)

/** Array initializer of ACC peripheral base addresses */

#define ACC_BASE_ADDRS                           {ACC_BASE}

/** Array initializer of ACC peripheral base pointers */

#define ACC_BASE_PTRS                            {ACC}

// need fill by yourself

///** Number of interrupt vector arrays for the ACC module. */

//#define ACC_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the ACC module. */

//#define ACC_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the ACC peripheral type */

//#define ACC_IRQS                                 {ACC_IRQn}





/* ----------------------------------------------------------------------------

   -- ACC Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup ACC_Register_Masks ACC Register Masks

 * @{

 */



/* CCR Bit Fields */

#define ACC_CCR_BP_MASK                0x40000u

#define ACC_CCR_BP_SHIFT               18u

#define ACC_CCR_BP_WIDTH               1u

#define ACC_CCR_BP(x)                  (((uint32_t)(((uint32_t)(x))<<ACC_CCR_BP_SHIFT))&ACC_CCR_BP_MASK)

#define ACC_CCR_IC_MASK                0x20000u

#define ACC_CCR_IC_SHIFT               17u

#define ACC_CCR_IC_WIDTH               1u

#define ACC_CCR_IC(x)                  (((uint32_t)(((uint32_t)(x))<<ACC_CCR_IC_SHIFT))&ACC_CCR_IC_MASK)

#define ACC_CCR_DC_MASK                0x10000u

#define ACC_CCR_DC_SHIFT               16u

#define ACC_CCR_DC_WIDTH               1u

#define ACC_CCR_DC(x)                  (((uint32_t)(((uint32_t)(x))<<ACC_CCR_DC_SHIFT))&ACC_CCR_DC_MASK)

#define ACC_CCR_STKALIGN_MASK          0x200u

#define ACC_CCR_STKALIGN_SHIFT         9u

#define ACC_CCR_STKALIGN_WIDTH         1u

#define ACC_CCR_STKALIGN(x)            (((uint32_t)(((uint32_t)(x))<<ACC_CCR_STKALIGN_SHIFT))&ACC_CCR_STKALIGN_MASK)

#define ACC_CCR_BFHFNMIGN_MASK         0x100u

#define ACC_CCR_BFHFNMIGN_SHIFT        8u

#define ACC_CCR_BFHFNMIGN_WIDTH        1u

#define ACC_CCR_BFHFNMIGN(x)           (((uint32_t)(((uint32_t)(x))<<ACC_CCR_BFHFNMIGN_SHIFT))&ACC_CCR_BFHFNMIGN_MASK)

#define ACC_CCR_DIV_0_TRP_MASK         0x10u

#define ACC_CCR_DIV_0_TRP_SHIFT        4u

#define ACC_CCR_DIV_0_TRP_WIDTH        1u

#define ACC_CCR_DIV_0_TRP(x)           (((uint32_t)(((uint32_t)(x))<<ACC_CCR_DIV_0_TRP_SHIFT))&ACC_CCR_DIV_0_TRP_MASK)

#define ACC_CCR_UNALIGN_TRP_MASK       0x8u

#define ACC_CCR_UNALIGN_TRP_SHIFT      3u

#define ACC_CCR_UNALIGN_TRP_WIDTH      1u

#define ACC_CCR_UNALIGN_TRP(x)         (((uint32_t)(((uint32_t)(x))<<ACC_CCR_UNALIGN_TRP_SHIFT))&ACC_CCR_UNALIGN_TRP_MASK)

#define ACC_CCR_USERSETMPEND_MASK      0x2u

#define ACC_CCR_USERSETMPEND_SHIFT     1u

#define ACC_CCR_USERSETMPEND_WIDTH     1u

#define ACC_CCR_USERSETMPEND(x)        (((uint32_t)(((uint32_t)(x))<<ACC_CCR_USERSETMPEND_SHIFT))&ACC_CCR_USERSETMPEND_MASK)

#define ACC_CCR_NONBASETHRDENA_MASK    0x1u

#define ACC_CCR_NONBASETHRDENA_SHIFT   0u

#define ACC_CCR_NONBASETHRDENA_WIDTH   1u

#define ACC_CCR_NONBASETHRDENA(x)      (((uint32_t)(((uint32_t)(x))<<ACC_CCR_NONBASETHRDENA_SHIFT))&ACC_CCR_NONBASETHRDENA_MASK)

/* CCR Reg Mask */

#define ACC_CCR_MASK                   0x0007031Bu



/* CLIDR Bit Fields */

#define ACC_CLIDR_LOUU_MASK            0x38000000u

#define ACC_CLIDR_LOUU_SHIFT           27u

#define ACC_CLIDR_LOUU_WIDTH           3u

#define ACC_CLIDR_LOUU(x)              (((uint32_t)(((uint32_t)(x))<<ACC_CLIDR_LOUU_SHIFT))&ACC_CLIDR_LOUU_MASK)

#define ACC_CLIDR_LOC_MASK             0x7000000u

#define ACC_CLIDR_LOC_SHIFT            24u

#define ACC_CLIDR_LOC_WIDTH            3u

#define ACC_CLIDR_LOC(x)               (((uint32_t)(((uint32_t)(x))<<ACC_CLIDR_LOC_SHIFT))&ACC_CLIDR_LOC_MASK)

#define ACC_CLIDR_LOCT_MASK            0x7u

#define ACC_CLIDR_LOCT_SHIFT           0u

#define ACC_CLIDR_LOCT_WIDTH           3u

#define ACC_CLIDR_LOCT(x)              (((uint32_t)(((uint32_t)(x))<<ACC_CLIDR_LOCT_SHIFT))&ACC_CLIDR_LOCT_MASK)

/* CLIDR Reg Mask */

#define ACC_CLIDR_MASK                 0x3F000007u



/* CTR Bit Fields */

#define ACC_CTR_FMT_MASK               0xE0000000u

#define ACC_CTR_FMT_SHIFT              29u

#define ACC_CTR_FMT_WIDTH              3u

#define ACC_CTR_FMT(x)                 (((uint32_t)(((uint32_t)(x))<<ACC_CTR_FMT_SHIFT))&ACC_CTR_FMT_MASK)

#define ACC_CTR_CWG_MASK               0xF000000u

#define ACC_CTR_CWG_SHIFT              24u

#define ACC_CTR_CWG_WIDTH              4u

#define ACC_CTR_CWG(x)                 (((uint32_t)(((uint32_t)(x))<<ACC_CTR_CWG_SHIFT))&ACC_CTR_CWG_MASK)

#define ACC_CTR_ERG_MASK               0xF00000u

#define ACC_CTR_ERG_SHIFT              20u

#define ACC_CTR_ERG_WIDTH              4u

#define ACC_CTR_ERG(x)                 (((uint32_t)(((uint32_t)(x))<<ACC_CTR_ERG_SHIFT))&ACC_CTR_ERG_MASK)

#define ACC_CTR_DMINLINE_MASK          0xF0000u

#define ACC_CTR_DMINLINE_SHIFT         16u

#define ACC_CTR_DMINLINE_WIDTH         4u

#define ACC_CTR_DMINLINE(x)            (((uint32_t)(((uint32_t)(x))<<ACC_CTR_DMINLINE_SHIFT))&ACC_CTR_DMINLINE_MASK)

#define ACC_CTR_IMINLINE_MASK          0xFu

#define ACC_CTR_IMINLINE_SHIFT         0u

#define ACC_CTR_IMINLINE_WIDTH         4u

#define ACC_CTR_IMINLINE(x)            (((uint32_t)(((uint32_t)(x))<<ACC_CTR_IMINLINE_SHIFT))&ACC_CTR_IMINLINE_MASK)

/* CTR Reg Mask */

#define ACC_CTR_MASK                   0xEFFF000Fu



/* CCSIDR Bit Fields */

#define ACC_CCSIDR_WT_MASK             0x80000000u

#define ACC_CCSIDR_WT_SHIFT            31u

#define ACC_CCSIDR_WT_WIDTH            1u

#define ACC_CCSIDR_WT(x)               (((uint32_t)(((uint32_t)(x))<<ACC_CCSIDR_WT_SHIFT))&ACC_CCSIDR_WT_MASK)

#define ACC_CCSIDR_WB_MASK             0x40000000u

#define ACC_CCSIDR_WB_SHIFT            30u

#define ACC_CCSIDR_WB_WIDTH            1u

#define ACC_CCSIDR_WB(x)               (((uint32_t)(((uint32_t)(x))<<ACC_CCSIDR_WB_SHIFT))&ACC_CCSIDR_WB_MASK)

#define ACC_CCSIDR_RA_MASK             0x20000000u

#define ACC_CCSIDR_RA_SHIFT            29u

#define ACC_CCSIDR_RA_WIDTH            1u

#define ACC_CCSIDR_RA(x)               (((uint32_t)(((uint32_t)(x))<<ACC_CCSIDR_RA_SHIFT))&ACC_CCSIDR_RA_MASK)

#define ACC_CCSIDR_WA_MASK             0x10000000u

#define ACC_CCSIDR_WA_SHIFT            28u

#define ACC_CCSIDR_WA_WIDTH            1u

#define ACC_CCSIDR_WA(x)               (((uint32_t)(((uint32_t)(x))<<ACC_CCSIDR_WA_SHIFT))&ACC_CCSIDR_WA_MASK)

#define ACC_CCSIDR_NUMSETS_MASK        0xFFFE000u

#define ACC_CCSIDR_NUMSETS_SHIFT       13u

#define ACC_CCSIDR_NUMSETS_WIDTH       15u

#define ACC_CCSIDR_NUMSETS(x)          (((uint32_t)(((uint32_t)(x))<<ACC_CCSIDR_NUMSETS_SHIFT))&ACC_CCSIDR_NUMSETS_MASK)

#define ACC_CCSIDR_ASSOCIATIVITY_MASK  0x1FF8u

#define ACC_CCSIDR_ASSOCIATIVITY_SHIFT 3u

#define ACC_CCSIDR_ASSOCIATIVITY_WIDTH 10u

#define ACC_CCSIDR_ASSOCIATIVITY(x)    (((uint32_t)(((uint32_t)(x))<<ACC_CCSIDR_ASSOCIATIVITY_SHIFT))&ACC_CCSIDR_ASSOCIATIVITY_MASK)

#define ACC_CCSIDR_LINESIZE_MASK       0x7u

#define ACC_CCSIDR_LINESIZE_SHIFT      0u

#define ACC_CCSIDR_LINESIZE_WIDTH      3u

#define ACC_CCSIDR_LINESIZE(x)         (((uint32_t)(((uint32_t)(x))<<ACC_CCSIDR_LINESIZE_SHIFT))&ACC_CCSIDR_LINESIZE_MASK)

/* CCSIDR Reg Mask */

#define ACC_CCSIDR_MASK                0xFFFFFFFFu



/* CSSELR Bit Fields */

#define ACC_CSSELR_LEVEL_MASK          0xEu

#define ACC_CSSELR_LEVEL_SHIFT         1u

#define ACC_CSSELR_LEVEL_WIDTH         3u

#define ACC_CSSELR_LEVEL(x)            (((uint32_t)(((uint32_t)(x))<<ACC_CSSELR_LEVEL_SHIFT))&ACC_CSSELR_LEVEL_MASK)

#define ACC_CSSELR_IND_MASK            0x1u

#define ACC_CSSELR_IND_SHIFT           0u

#define ACC_CSSELR_IND_WIDTH           1u

#define ACC_CSSELR_IND(x)              (((uint32_t)(((uint32_t)(x))<<ACC_CSSELR_IND_SHIFT))&ACC_CSSELR_IND_MASK)

/* CSSELR Reg Mask */

#define ACC_CSSELR_MASK                0x0000000Fu



/* ICIALLU Bit Fields */

#define ACC_ICIALLU_ICIALLU_MASK       0xFFFFFFFFu

#define ACC_ICIALLU_ICIALLU_SHIFT      0u

#define ACC_ICIALLU_ICIALLU_WIDTH      32u

#define ACC_ICIALLU_ICIALLU(x)         (((uint32_t)(((uint32_t)(x))<<ACC_ICIALLU_ICIALLU_SHIFT))&ACC_ICIALLU_ICIALLU_MASK)

/* ICIALLU Reg Mask */

#define ACC_ICIALLU_MASK               0xFFFFFFFFu



/* ICIMVAU Bit Fields */

#define ACC_ICIMVAU_MVA_MASK           0xFFFFFFE0u

#define ACC_ICIMVAU_MVA_SHIFT          5u

#define ACC_ICIMVAU_MVA_WIDTH          27u

#define ACC_ICIMVAU_MVA(x)             (((uint32_t)(((uint32_t)(x))<<ACC_ICIMVAU_MVA_SHIFT))&ACC_ICIMVAU_MVA_MASK)

/* ICIMVAU Reg Mask */

#define ACC_ICIMVAU_MASK               0xFFFFFFE0u



/* DCIMVAC Bit Fields */

#define ACC_DCIMVAC_MVA_MASK           0xFFFFFFE0u

#define ACC_DCIMVAC_MVA_SHIFT          5u

#define ACC_DCIMVAC_MVA_WIDTH          27u

#define ACC_DCIMVAC_MVA(x)             (((uint32_t)(((uint32_t)(x))<<ACC_DCIMVAC_MVA_SHIFT))&ACC_DCIMVAC_MVA_MASK)

/* DCIMVAC Reg Mask */

#define ACC_DCIMVAC_MASK               0xFFFFFFE0u



/* DCISW Bit Fields */

#define ACC_DCISW_WAY_MASK             0xC0000000u

#define ACC_DCISW_WAY_SHIFT            30u

#define ACC_DCISW_WAY_WIDTH            2u

#define ACC_DCISW_WAY(x)               (((uint32_t)(((uint32_t)(x))<<ACC_DCISW_WAY_SHIFT))&ACC_DCISW_WAY_MASK)

#define ACC_DCISW_SET_MASK             0x3FE0u

#define ACC_DCISW_SET_SHIFT            5u

#define ACC_DCISW_SET_WIDTH            9u

#define ACC_DCISW_SET(x)               (((uint32_t)(((uint32_t)(x))<<ACC_DCISW_SET_SHIFT))&ACC_DCISW_SET_MASK)

/* DCISW Reg Mask */

#define ACC_DCISW_MASK                 0xC0003FE0u



/* DCCMVAU Bit Fields */

#define ACC_DCCMVAU_MVA_MASK           0xFFFFFFE0u

#define ACC_DCCMVAU_MVA_SHIFT          5u

#define ACC_DCCMVAU_MVA_WIDTH          27u

#define ACC_DCCMVAU_MVA(x)             (((uint32_t)(((uint32_t)(x))<<ACC_DCCMVAU_MVA_SHIFT))&ACC_DCCMVAU_MVA_MASK)

/* DCCMVAU Reg Mask */

#define ACC_DCCMVAU_MASK               0xFFFFFFE0u



/* DCCMVAC Bit Fields */

#define ACC_DCCMVAC_MVA_MASK           0xFFFFFFE0u

#define ACC_DCCMVAC_MVA_SHIFT          5u

#define ACC_DCCMVAC_MVA_WIDTH          27u

#define ACC_DCCMVAC_MVA(x)             (((uint32_t)(((uint32_t)(x))<<ACC_DCCMVAC_MVA_SHIFT))&ACC_DCCMVAC_MVA_MASK)

/* DCCMVAC Reg Mask */

#define ACC_DCCMVAC_MASK               0xFFFFFFE0u



/* DCCSW Bit Fields */

#define ACC_DCCSW_WAY_MASK             0xC0000000u

#define ACC_DCCSW_WAY_SHIFT            30u

#define ACC_DCCSW_WAY_WIDTH            2u

#define ACC_DCCSW_WAY(x)               (((uint32_t)(((uint32_t)(x))<<ACC_DCCSW_WAY_SHIFT))&ACC_DCCSW_WAY_MASK)

#define ACC_DCCSW_SET_MASK             0x3FE0u

#define ACC_DCCSW_SET_SHIFT            5u

#define ACC_DCCSW_SET_WIDTH            9u

#define ACC_DCCSW_SET(x)               (((uint32_t)(((uint32_t)(x))<<ACC_DCCSW_SET_SHIFT))&ACC_DCCSW_SET_MASK)

/* DCCSW Reg Mask */

#define ACC_DCCSW_MASK                 0xC0003FE0u



/* DCCIMVAC Bit Fields */

#define ACC_DCCIMVAC_MVA_MASK          0xFFFFFFE0u

#define ACC_DCCIMVAC_MVA_SHIFT         5u

#define ACC_DCCIMVAC_MVA_WIDTH         27u

#define ACC_DCCIMVAC_MVA(x)            (((uint32_t)(((uint32_t)(x))<<ACC_DCCIMVAC_MVA_SHIFT))&ACC_DCCIMVAC_MVA_MASK)

/* DCCIMVAC Reg Mask */

#define ACC_DCCIMVAC_MASK              0xFFFFFFE0u



/* DCCISW Bit Fields */

#define ACC_DCCISW_WAY_MASK            0xC0000000u

#define ACC_DCCISW_WAY_SHIFT           30u

#define ACC_DCCISW_WAY_WIDTH           2u

#define ACC_DCCISW_WAY(x)              (((uint32_t)(((uint32_t)(x))<<ACC_DCCISW_WAY_SHIFT))&ACC_DCCISW_WAY_MASK)

#define ACC_DCCISW_SET_MASK            0x3FE0u

#define ACC_DCCISW_SET_SHIFT           5u

#define ACC_DCCISW_SET_WIDTH           9u

#define ACC_DCCISW_SET(x)              (((uint32_t)(((uint32_t)(x))<<ACC_DCCISW_SET_SHIFT))&ACC_DCCISW_SET_MASK)

/* DCCISW Reg Mask */

#define ACC_DCCISW_MASK                0xC0003FE0u



/* CACR Bit Fields */

#define ACC_CACR_FORCEWT_MASK          0x4u

#define ACC_CACR_FORCEWT_SHIFT         2u

#define ACC_CACR_FORCEWT_WIDTH         1u

#define ACC_CACR_FORCEWT(x)            (((uint32_t)(((uint32_t)(x))<<ACC_CACR_FORCEWT_SHIFT))&ACC_CACR_FORCEWT_MASK)

#define ACC_CACR_ECCDIS_MASK           0x2u

#define ACC_CACR_ECCDIS_SHIFT          1u

#define ACC_CACR_ECCDIS_WIDTH          1u

#define ACC_CACR_ECCDIS(x)             (((uint32_t)(((uint32_t)(x))<<ACC_CACR_ECCDIS_SHIFT))&ACC_CACR_ECCDIS_MASK)

#define ACC_CACR_SIWT_MASK             0x1u

#define ACC_CACR_SIWT_SHIFT            0u

#define ACC_CACR_SIWT_WIDTH            1u

#define ACC_CACR_SIWT(x)               (((uint32_t)(((uint32_t)(x))<<ACC_CACR_SIWT_SHIFT))&ACC_CACR_SIWT_MASK)

/* CACR Reg Mask */

#define ACC_CACR_MASK                  0x00000007u



/* IEBR Bit Fields */

#define ACC_IEBR_TOE_MASK              0x20000u

#define ACC_IEBR_TOE_SHIFT             17u

#define ACC_IEBR_TOE_WIDTH             1u

#define ACC_IEBR_TOE(x)                (((uint32_t)(((uint32_t)(x))<<ACC_IEBR_TOE_SHIFT))&ACC_IEBR_TOE_MASK)

#define ACC_IEBR_RB_MASK               0x10000u

#define ACC_IEBR_RB_SHIFT              16u

#define ACC_IEBR_RB_WIDTH              1u

#define ACC_IEBR_RB(x)                 (((uint32_t)(((uint32_t)(x))<<ACC_IEBR_RB_SHIFT))&ACC_IEBR_RB_MASK)

#define ACC_IEBR_RL_MASK               0xFFFCu

#define ACC_IEBR_RL_SHIFT              2u

#define ACC_IEBR_RL_WIDTH              14u

#define ACC_IEBR_RL(x)                 (((uint32_t)(((uint32_t)(x))<<ACC_IEBR_RL_SHIFT))&ACC_IEBR_RL_MASK)

#define ACC_IEBR_LOCKED_MASK           0x2u

#define ACC_IEBR_LOCKED_SHIFT          1u

#define ACC_IEBR_LOCKED_WIDTH          1u

#define ACC_IEBR_LOCKED(x)             (((uint32_t)(((uint32_t)(x))<<ACC_IEBR_LOCKED_SHIFT))&ACC_IEBR_LOCKED_MASK)

#define ACC_IEBR_VALID_MASK            0x1u

#define ACC_IEBR_VALID_SHIFT           0u

#define ACC_IEBR_VALID_WIDTH           1u

#define ACC_IEBR_VALID(x)              (((uint32_t)(((uint32_t)(x))<<ACC_IEBR_VALID_SHIFT))&ACC_IEBR_VALID_MASK)

/* IEBR0 Reg Mask */

#define ACC_IEBR_MASK                  0x0003FFFFu



/* DEBR Bit Fields */

#define ACC_DEBR_TOE_MASK              0x20000u

#define ACC_DEBR_TOE_SHIFT             17u

#define ACC_DEBR_TOE_WIDTH             1u

#define ACC_DEBR_TOE(x)                (((uint32_t)(((uint32_t)(x))<<ACC_DEBR_TOE_SHIFT))&ACC_DEBR_TOE_MASK)

#define ACC_DEBR_RB_MASK               0x10000u

#define ACC_DEBR_RB_SHIFT              16u

#define ACC_DEBR_RB_WIDTH              1u

#define ACC_DEBR_RB(x)                 (((uint32_t)(((uint32_t)(x))<<ACC_DEBR_RB_SHIFT))&ACC_DEBR_RB_MASK)

#define ACC_DEBR_RL_MASK               0xFFFCu

#define ACC_DEBR_RL_SHIFT              2u

#define ACC_DEBR_RL_WIDTH              14u

#define ACC_DEBR_RL(x)                 (((uint32_t)(((uint32_t)(x))<<ACC_DEBR_RL_SHIFT))&ACC_DEBR_RL_MASK)

#define ACC_DEBR_LOCKED_MASK           0x2u

#define ACC_DEBR_LOCKED_SHIFT          1u

#define ACC_DEBR_LOCKED_WIDTH          1u

#define ACC_DEBR_LOCKED(x)             (((uint32_t)(((uint32_t)(x))<<ACC_DEBR_LOCKED_SHIFT))&ACC_DEBR_LOCKED_MASK)

#define ACC_DEBR_VALID_MASK            0x1u

#define ACC_DEBR_VALID_SHIFT           0u

#define ACC_DEBR_VALID_WIDTH           1u

#define ACC_DEBR_VALID(x)              (((uint32_t)(((uint32_t)(x))<<ACC_DEBR_VALID_SHIFT))&ACC_DEBR_VALID_MASK)

/* DEBR0 Reg Mask */

#define ACC_DEBR_MASK                  0x0003FFFFu





/*!

 * @}

 */ /* end of group ACC_Register_Masks */



/*!

 * @}

 */ /* end of group ACC_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
