#ifndef _FC7240_CORDIC_NU_Tztufn44_REGS_H_
#define _FC7240_CORDIC_NU_Tztufn44_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- CORDIC Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup CORDIC_Peripheral_Access_Layer CORDIC Peripheral Access Layer

 * @{

 */



/** CORDIC - Size of Registers Arrays */



/** CORDIC - Register Layout Typedef */



typedef struct {



  __IO uint32_t CTRL                          ; /* Control Register, offset: 0x0 */

       uint8_t  RESERVED_0[12];

  __IO uint32_t X_INPUT                       ; /* X-axis Input Data Register, offset: 0x10 */

  __IO uint32_t Y_INPUT                       ; /* Y-axis Input Data Register, offset: 0x14 */

  __IO uint32_t Z_INPUT                       ; /* Z-axis Input Data Register, offset: 0x18 */

       uint8_t  RESERVED_1[4];

  __IO uint32_t STAT                          ; /* State Register, offset: 0x20 */

  __I  uint32_t X_OUTPUT                      ; /* X-axis Output Data Register, offset: 0x24 */

  __I  uint32_t Y_OUTPUT                      ; /* Y-axis Output Data Register, offset: 0x28 */

  __I  uint32_t Z_OUTPUT                      ; /* Z-axis Output Data Register, offset: 0x2C */



} CORDIC_Type, *CORDIC_MemMapPtr;



/** Number of instances of the CORDIC module. */

#define CORDIC_INSTANCE_COUNT                    (1u)



/* CORDIC - Peripheral instance base addresses */

/** Peripheral CORDIC base address */

#define CORDIC_BASE                              (0x4002b000u)

/** Peripheral CORDIC base pointer */

#define CORDIC                                   ((CORDIC_Type *)CORDIC_BASE)

/** Array initializer of CORDIC peripheral base addresses */

#define CORDIC_BASE_ADDRS                        {CORDIC_BASE}

/** Array initializer of CORDIC peripheral base pointers */

#define CORDIC_BASE_PTRS                         {CORDIC}

// need fill by yourself

///** Number of interrupt vector arrays for the CORDIC module. */

//#define CORDIC_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the CORDIC module. */

//#define CORDIC_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the CORDIC peripheral type */

//#define CORDIC_IRQS                              {CORDIC_IRQn}





/* ----------------------------------------------------------------------------

   -- CORDIC Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup CORDIC_Register_Masks CORDIC Register Masks

 * @{

 */



/* CTRL Bit Fields */

#define CORDIC_CTRL_IE_MASK            0x80000000u

#define CORDIC_CTRL_IE_SHIFT           31u

#define CORDIC_CTRL_IE_WIDTH           1u

#define CORDIC_CTRL_IE(x)              (((uint32_t)(((uint32_t)(x))<<CORDIC_CTRL_IE_SHIFT))&CORDIC_CTRL_IE_MASK)

#define CORDIC_CTRL_SCALE_MASK         0x380u

#define CORDIC_CTRL_SCALE_SHIFT        7u

#define CORDIC_CTRL_SCALE_WIDTH        3u

#define CORDIC_CTRL_SCALE(x)           (((uint32_t)(((uint32_t)(x))<<CORDIC_CTRL_SCALE_SHIFT))&CORDIC_CTRL_SCALE_MASK)

#define CORDIC_CTRL_ITER_MASK          0x30u

#define CORDIC_CTRL_ITER_SHIFT         4u

#define CORDIC_CTRL_ITER_WIDTH         2u

#define CORDIC_CTRL_ITER(x)            (((uint32_t)(((uint32_t)(x))<<CORDIC_CTRL_ITER_SHIFT))&CORDIC_CTRL_ITER_MASK)

#define CORDIC_CTRL_OS_MASK            0xEu

#define CORDIC_CTRL_OS_SHIFT           1u

#define CORDIC_CTRL_OS_WIDTH           3u

#define CORDIC_CTRL_OS(x)              (((uint32_t)(((uint32_t)(x))<<CORDIC_CTRL_OS_SHIFT))&CORDIC_CTRL_OS_MASK)

#define CORDIC_CTRL_MODE_MASK          0x1u

#define CORDIC_CTRL_MODE_SHIFT         0u

#define CORDIC_CTRL_MODE_WIDTH         1u

#define CORDIC_CTRL_MODE(x)            (((uint32_t)(((uint32_t)(x))<<CORDIC_CTRL_MODE_SHIFT))&CORDIC_CTRL_MODE_MASK)

/* CTRL Reg Mask */

#define CORDIC_CTRL_MASK               0x800003BFu



/* X_INPUT Bit Fields */

#define CORDIC_X_INPUT_DATA_MASK       0xFFFFFFFFu

#define CORDIC_X_INPUT_DATA_SHIFT      0u

#define CORDIC_X_INPUT_DATA_WIDTH      32u

#define CORDIC_X_INPUT_DATA(x)         (((uint32_t)(((uint32_t)(x))<<CORDIC_X_INPUT_DATA_SHIFT))&CORDIC_X_INPUT_DATA_MASK)

/* X_INPUT Reg Mask */

#define CORDIC_X_INPUT_MASK            0xFFFFFFFFu



/* Y_INPUT Bit Fields */

#define CORDIC_Y_INPUT_DATA_MASK       0xFFFFFFFFu

#define CORDIC_Y_INPUT_DATA_SHIFT      0u

#define CORDIC_Y_INPUT_DATA_WIDTH      32u

#define CORDIC_Y_INPUT_DATA(x)         (((uint32_t)(((uint32_t)(x))<<CORDIC_Y_INPUT_DATA_SHIFT))&CORDIC_Y_INPUT_DATA_MASK)

/* Y_INPUT Reg Mask */

#define CORDIC_Y_INPUT_MASK            0xFFFFFFFFu



/* Z_INPUT Bit Fields */

#define CORDIC_Z_INPUT_DATA_MASK       0xFFFFFFFFu

#define CORDIC_Z_INPUT_DATA_SHIFT      0u

#define CORDIC_Z_INPUT_DATA_WIDTH      32u

#define CORDIC_Z_INPUT_DATA(x)         (((uint32_t)(((uint32_t)(x))<<CORDIC_Z_INPUT_DATA_SHIFT))&CORDIC_Z_INPUT_DATA_MASK)

/* Z_INPUT Reg Mask */

#define CORDIC_Z_INPUT_MASK            0xFFFFFFFFu



/* STAT Bit Fields */

#define CORDIC_STAT_DONE_MASK          0x1u

#define CORDIC_STAT_DONE_SHIFT         0u

#define CORDIC_STAT_DONE_WIDTH         1u

#define CORDIC_STAT_DONE(x)            (((uint32_t)(((uint32_t)(x))<<CORDIC_STAT_DONE_SHIFT))&CORDIC_STAT_DONE_MASK)

/* STAT Reg Mask */

#define CORDIC_STAT_MASK               0x00000001u



/* X_OUTPUT Bit Fields */

#define CORDIC_X_OUTPUT_DATA_MASK      0xFFFFFFFFu

#define CORDIC_X_OUTPUT_DATA_SHIFT     0u

#define CORDIC_X_OUTPUT_DATA_WIDTH     32u

#define CORDIC_X_OUTPUT_DATA(x)        (((uint32_t)(((uint32_t)(x))<<CORDIC_X_OUTPUT_DATA_SHIFT))&CORDIC_X_OUTPUT_DATA_MASK)

/* X_OUTPUT Reg Mask */

#define CORDIC_X_OUTPUT_MASK           0xFFFFFFFFu



/* Y_OUTPUT Bit Fields */

#define CORDIC_Y_OUTPUT_DATA_MASK      0xFFFFFFFFu

#define CORDIC_Y_OUTPUT_DATA_SHIFT     0u

#define CORDIC_Y_OUTPUT_DATA_WIDTH     32u

#define CORDIC_Y_OUTPUT_DATA(x)        (((uint32_t)(((uint32_t)(x))<<CORDIC_Y_OUTPUT_DATA_SHIFT))&CORDIC_Y_OUTPUT_DATA_MASK)

/* Y_OUTPUT Reg Mask */

#define CORDIC_Y_OUTPUT_MASK           0xFFFFFFFFu



/* Z_OUTPUT Bit Fields */

#define CORDIC_Z_OUTPUT_DATA_MASK      0xFFFFFFFFu

#define CORDIC_Z_OUTPUT_DATA_SHIFT     0u

#define CORDIC_Z_OUTPUT_DATA_WIDTH     32u

#define CORDIC_Z_OUTPUT_DATA(x)        (((uint32_t)(((uint32_t)(x))<<CORDIC_Z_OUTPUT_DATA_SHIFT))&CORDIC_Z_OUTPUT_DATA_MASK)

/* Z_OUTPUT Reg Mask */

#define CORDIC_Z_OUTPUT_MASK           0xFFFFFFFFu





/*!

 * @}

 */ /* end of group CORDIC_Register_Masks */



/*!

 * @}

 */ /* end of group CORDIC_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
