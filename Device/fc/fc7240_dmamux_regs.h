#ifndef _FC7240_DMAMUX_NU_Tztufn36_REGS_H_
#define _FC7240_DMAMUX_NU_Tztufn36_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- DMAMUX Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup DMAMUX_Peripheral_Access_Layer DMAMUX Peripheral Access Layer

 * @{

 */



/** DMAMUX - Size of Registers Arrays */



/** DMAMUX - Register Layout Typedef */

#define DMAMUX_CHCFG_COUNT 16
#define DMAMUX_CHTRG_TRG_COUNT 4



typedef struct {



  __IO uint8_t  CHCFG[DMAMUX_CHCFG_COUNT]     ; /* Channel N Configuration Register, offset: 0x0 */

       uint8_t  RESERVED_0[16];

  __IO uint8_t  CHTRG                         ; /* Channel N Trigger Register, offset: 0x20 */



} DMAMUX_Type, *DMAMUX_MemMapPtr;



/** Number of instances of the DMAMUX module. */

#define DMAMUX_INSTANCE_COUNT                    (1u)



/* DMAMUX - Peripheral instance base addresses */

/** Peripheral DMAMUX base address */

#define DMAMUX_BASE                              (0x4000a000u)

/** Peripheral DMAMUX base pointer */

#define DMAMUX                                   ((DMAMUX_Type *)DMAMUX_BASE)

/** Array initializer of DMAMUX peripheral base addresses */

#define DMAMUX_BASE_ADDRS                        {DMAMUX_BASE}

/** Array initializer of DMAMUX peripheral base pointers */

#define DMAMUX_BASE_PTRS                         {DMAMUX}

// need fill by yourself

///** Number of interrupt vector arrays for the DMAMUX module. */

//#define DMAMUX_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the DMAMUX module. */

//#define DMAMUX_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the DMAMUX peripheral type */

//#define DMAMUX_IRQS                              {DMAMUX_IRQn}





/* ----------------------------------------------------------------------------

   -- DMAMUX Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup DMAMUX_Register_Masks DMAMUX Register Masks

 * @{

 */



/* CHCFG Bit Fields */

#define DMAMUX_CHCFG_ENBL_MASK         0x80u

#define DMAMUX_CHCFG_ENBL_SHIFT        7u

#define DMAMUX_CHCFG_ENBL_WIDTH        1u

#define DMAMUX_CHCFG_ENBL(x)           (((uint8_t)(((uint8_t)(x))<<DMAMUX_CHCFG_ENBL_SHIFT))&DMAMUX_CHCFG_ENBL_MASK)

#define DMAMUX_CHCFG_SOURCE_MASK       0x7Fu

#define DMAMUX_CHCFG_SOURCE_SHIFT      0u

#define DMAMUX_CHCFG_SOURCE_WIDTH      7u

#define DMAMUX_CHCFG_SOURCE(x)         (((uint8_t)(((uint8_t)(x))<<DMAMUX_CHCFG_SOURCE_SHIFT))&DMAMUX_CHCFG_SOURCE_MASK)

/* CHCFG Reg Mask */

#define DMAMUX_CHCFG_MASK              0xFFu



/* CHTRG Bit Fields */

#define DMAMUX_CHTRG_TRIG_MASK        0x1u

#define DMAMUX_CHTRG_TRIG_SHIFT       0u

#define DMAMUX_CHTRG_TRIG_WIDTH       1u

#define DMAMUX_CHTRG_TRIG(x)          (((uint8_t)(((uint8_t)(x))<<DMAMUX_CHTRG_TRIG_SHIFT))&DMAMUX_CHTRG_TRIG_MASK)

/* CHTRG Reg Mask */

#define DMAMUX_CHTRG_MASK              0x0Fu





/*!

 * @}

 */ /* end of group DMAMUX_Register_Masks */



/*!

 * @}

 */ /* end of group DMAMUX_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
