#ifndef _FC7240_CMU_NU_Tztufn2_REGS_H_
#define _FC7240_CMU_NU_Tztufn2_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- CMU Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup CMU_Peripheral_Access_Layer CMU Peripheral Access Layer

 * @{

 */



/** CMU - Size of Registers Arrays */



/** CMU - Register Layout Typedef */



typedef struct {



       uint8_t  RESERVED_0[8];

  __IO uint32_t CTRL                          ; /* Control Register, offset: 0x8 */

       uint8_t  RESERVED_1[4];

  __IO uint32_t MIN                           ; /* Minimum Threshold Register, offset: 0x10 */

  __IO uint32_t MAX                           ; /* Maximum Threshold Register, offset: 0x14 */

  __IO uint32_t REF_WINDOW                    ; /* Reference Window Register, offset: 0x18 */

  __I  uint32_t MON_CNT                       ; /* Monitor Counter Register, offset: 0x1C */

  __IO uint32_t ST                            ; /* Status Register, offset: 0x20 */

  __IO uint32_t PERIOD                        ; /* Period Monitor Mode Configuration Register, offset: 0x24 */



} CMU_Type, *CMU_MemMapPtr;



/** Number of instances of the CMU module. */

#define CMU_INSTANCE_COUNT                       (5u)



/* CMU - Peripheral instance base addresses */

/** Peripheral CMU0 base address */

#define CMU0_BASE                                (0x40031000u)

/** Peripheral CMU0 base pointer */

#define CMU0                                     ((CMU_Type *)CMU0_BASE)

/** Peripheral CMU1 base address */

#define CMU1_BASE                                (0x40032000u)

/** Peripheral CMU1 base pointer */

#define CMU1                                     ((CMU_Type *)CMU1_BASE)

/** Peripheral CMU2 base address */

#define CMU2_BASE                                (0x40033000u)

/** Peripheral CMU2 base pointer */

#define CMU2                                     ((CMU_Type *)CMU2_BASE)

/** Peripheral CMU3 base address */

#define CMU3_BASE                                (0x40034000u)

/** Peripheral CMU3 base pointer */

#define CMU3                                     ((CMU_Type *)CMU3_BASE)

/** Peripheral CMU4 base address */

#define CMU4_BASE                                (0x40035000u)

/** Peripheral CMU4 base pointer */

#define CMU4                                     ((CMU_Type *)CMU4_BASE)

/** Array initializer of CMU peripheral base addresses */

#define CMU_BASE_ADDRS                           {CMU0_BASE, CMU1_BASE, CMU2_BASE, CMU3_BASE, CMU4_BASE}

/** Array initializer of CMU peripheral base pointers */

#define CMU_BASE_PTRS                            {CMU0, CMU1, CMU2, CMU3, CMU4}

// need fill by yourself

///** Number of interrupt vector arrays for the CMU module. */

//#define CMU_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the CMU module. */

//#define CMU_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the CMU peripheral type */

//#define CMU_IRQS                                 {CMU0_IRQn, CMU1_IRQn, CMU2_IRQn, CMU3_IRQn, CMU4_IRQn}





/* ----------------------------------------------------------------------------

   -- CMU Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup CMU_Register_Masks CMU Register Masks

 * @{

 */



/* CTRL Bit Fields */

#define CMU_CTRL_REF_DIV_MASK          0x70000u

#define CMU_CTRL_REF_DIV_SHIFT         16u

#define CMU_CTRL_REF_DIV_WIDTH         3u

#define CMU_CTRL_REF_DIV(x)            (((uint32_t)(((uint32_t)(x))<<CMU_CTRL_REF_DIV_SHIFT))&CMU_CTRL_REF_DIV_MASK)

#define CMU_CTRL_IRQ_EN_MASK           0x40u

#define CMU_CTRL_IRQ_EN_SHIFT          6u

#define CMU_CTRL_IRQ_EN_WIDTH          1u

#define CMU_CTRL_IRQ_EN(x)             (((uint32_t)(((uint32_t)(x))<<CMU_CTRL_IRQ_EN_SHIFT))&CMU_CTRL_IRQ_EN_MASK)

#define CMU_CTRL_RESTART_EN_MASK       0x20u

#define CMU_CTRL_RESTART_EN_SHIFT      5u

#define CMU_CTRL_RESTART_EN_WIDTH      1u

#define CMU_CTRL_RESTART_EN(x)         (((uint32_t)(((uint32_t)(x))<<CMU_CTRL_RESTART_EN_SHIFT))&CMU_CTRL_RESTART_EN_MASK)

#define CMU_CTRL_LP_EN_MASK            0x10u

#define CMU_CTRL_LP_EN_SHIFT           4u

#define CMU_CTRL_LP_EN_WIDTH           1u

#define CMU_CTRL_LP_EN(x)              (((uint32_t)(((uint32_t)(x))<<CMU_CTRL_LP_EN_SHIFT))&CMU_CTRL_LP_EN_MASK)

#define CMU_CTRL_STOP_EN_MASK          0x8u

#define CMU_CTRL_STOP_EN_SHIFT         3u

#define CMU_CTRL_STOP_EN_WIDTH         1u

#define CMU_CTRL_STOP_EN(x)            (((uint32_t)(((uint32_t)(x))<<CMU_CTRL_STOP_EN_SHIFT))&CMU_CTRL_STOP_EN_MASK)

#define CMU_CTRL_SW_RST_MASK           0x2u

#define CMU_CTRL_SW_RST_SHIFT          1u

#define CMU_CTRL_SW_RST_WIDTH          1u

#define CMU_CTRL_SW_RST(x)             (((uint32_t)(((uint32_t)(x))<<CMU_CTRL_SW_RST_SHIFT))&CMU_CTRL_SW_RST_MASK)

#define CMU_CTRL_ENABLE_MASK           0x1u

#define CMU_CTRL_ENABLE_SHIFT          0u

#define CMU_CTRL_ENABLE_WIDTH          1u

#define CMU_CTRL_ENABLE(x)             (((uint32_t)(((uint32_t)(x))<<CMU_CTRL_ENABLE_SHIFT))&CMU_CTRL_ENABLE_MASK)

/* CTRL Reg Mask */

#define CMU_CTRL_MASK                  0x0007007Bu



/* MIN Bit Fields */

#define CMU_MIN_MIN_MASK               0xFFFFFFu

#define CMU_MIN_MIN_SHIFT              0u

#define CMU_MIN_MIN_WIDTH              24u

#define CMU_MIN_MIN(x)                 (((uint32_t)(((uint32_t)(x))<<CMU_MIN_MIN_SHIFT))&CMU_MIN_MIN_MASK)

/* MIN Reg Mask */

#define CMU_MIN_MASK                   0x00FFFFFFu



/* MAX Bit Fields */

#define CMU_MAX_MAX_MASK               0xFFFFFFu

#define CMU_MAX_MAX_SHIFT              0u

#define CMU_MAX_MAX_WIDTH              24u

#define CMU_MAX_MAX(x)                 (((uint32_t)(((uint32_t)(x))<<CMU_MAX_MAX_SHIFT))&CMU_MAX_MAX_MASK)

/* MAX Reg Mask */

#define CMU_MAX_MASK                   0x00FFFFFFu



/* REF_WINDOW Bit Fields */

#define CMU_REF_WINDOW_REF_WINDOW_MASK 0xFFFFFFu

#define CMU_REF_WINDOW_REF_WINDOW_SHIFT 0u

#define CMU_REF_WINDOW_REF_WINDOW_WIDTH 24u

#define CMU_REF_WINDOW_REF_WINDOW(x)   (((uint32_t)(((uint32_t)(x))<<CMU_REF_WINDOW_REF_WINDOW_SHIFT))&CMU_REF_WINDOW_REF_WINDOW_MASK)

/* REF_WINDOW Reg Mask */

#define CMU_REF_WINDOW_MASK            0x00FFFFFFu



/* MON_CNT Bit Fields */

#define CMU_MON_CNT_MON_CNT_MASK       0xFFFFFFu

#define CMU_MON_CNT_MON_CNT_SHIFT      0u

#define CMU_MON_CNT_MON_CNT_WIDTH      24u

#define CMU_MON_CNT_MON_CNT(x)         (((uint32_t)(((uint32_t)(x))<<CMU_MON_CNT_MON_CNT_SHIFT))&CMU_MON_CNT_MON_CNT_MASK)

/* MON_CNT Reg Mask */

#define CMU_MON_CNT_MASK               0x00FFFFFFu



/* ST Bit Fields */

#define CMU_ST_LOC_MASK                0x8000u

#define CMU_ST_LOC_SHIFT               15u

#define CMU_ST_LOC_WIDTH               1u

#define CMU_ST_LOC(x)                  (((uint32_t)(((uint32_t)(x))<<CMU_ST_LOC_SHIFT))&CMU_ST_LOC_MASK)

#define CMU_ST_MIS_MASK                0x100u

#define CMU_ST_MIS_SHIFT               8u

#define CMU_ST_MIS_WIDTH               1u

#define CMU_ST_MIS(x)                  (((uint32_t)(((uint32_t)(x))<<CMU_ST_MIS_SHIFT))&CMU_ST_MIS_MASK)

/* ST Reg Mask */

#define CMU_ST_MASK                    0x00008100u



/* PERIOD Bit Fields */

#define CMU_PERIOD_WINDOW_MASK         0xF0000u

#define CMU_PERIOD_WINDOW_SHIFT        16u

#define CMU_PERIOD_WINDOW_WIDTH        4u

#define CMU_PERIOD_WINDOW(x)           (((uint32_t)(((uint32_t)(x))<<CMU_PERIOD_WINDOW_SHIFT))&CMU_PERIOD_WINDOW_MASK)

#define CMU_PERIOD_EN_MASK             0x1u

#define CMU_PERIOD_EN_SHIFT            0u

#define CMU_PERIOD_EN_WIDTH            1u

#define CMU_PERIOD_EN(x)               (((uint32_t)(((uint32_t)(x))<<CMU_PERIOD_EN_SHIFT))&CMU_PERIOD_EN_MASK)

/* PERIOD Reg Mask */

#define CMU_PERIOD_MASK                0x000F0001u





/*!

 * @}

 */ /* end of group CMU_Register_Masks */



/*!

 * @}

 */ /* end of group CMU_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
