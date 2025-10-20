#ifndef _FC7240_SMC_NU_Tztufn46_REGS_H_
#define _FC7240_SMC_NU_Tztufn46_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- SMC Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup SMC_Peripheral_Access_Layer SMC Peripheral Access Layer

 * @{

 */



/** SMC - Size of Registers Arrays */



/** SMC - Register Layout Typedef */



typedef struct {



       uint8_t  RESERVED_0[12];

  __IO uint32_t PMCTRL                        ; /* Power Mode Control Register, offset: 0xc */

  __IO uint32_t STANDBY_CFG                   ; /* Standby Mode Configuration Register, offset: 0x10 */



} SMC_Type, *SMC_MemMapPtr;



/** Number of instances of the SMC module. */

#define SMC_INSTANCE_COUNT                       (1u)



/* SMC - Peripheral instance base addresses */

/** Peripheral SMC base address */

#define SMC_BASE                                 (0x40045000u)

/** Peripheral SMC base pointer */

#define SMC                                      ((SMC_Type *)SMC_BASE)

/** Array initializer of SMC peripheral base addresses */

#define SMC_BASE_ADDRS                           {SMC_BASE}

/** Array initializer of SMC peripheral base pointers */

#define SMC_BASE_PTRS                            {SMC}

// need fill by yourself

///** Number of interrupt vector arrays for the SMC module. */

//#define SMC_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the SMC module. */

//#define SMC_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the SMC peripheral type */

//#define SMC_IRQS                                 {SMC_IRQn}





/* ----------------------------------------------------------------------------

   -- SMC Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup SMC_Register_Masks SMC Register Masks

 * @{

 */



/* PMCTRL Bit Fields */

#define SMC_PMCTRL_STOP_MODE_MASK      0x7u

#define SMC_PMCTRL_STOP_MODE_SHIFT     0u

#define SMC_PMCTRL_STOP_MODE_WIDTH     3u

#define SMC_PMCTRL_STOP_MODE(x)        (((uint32_t)(((uint32_t)(x))<<SMC_PMCTRL_STOP_MODE_SHIFT))&SMC_PMCTRL_STOP_MODE_MASK)

/* PMCTRL Reg Mask */

#define SMC_PMCTRL_MASK                0x00000007u



/* STANDBY_CFG Bit Fields */

#define SMC_STANDBY_CFG_OPTION_MASK    0x3u

#define SMC_STANDBY_CFG_OPTION_SHIFT   0u

#define SMC_STANDBY_CFG_OPTION_WIDTH   2u

#define SMC_STANDBY_CFG_OPTION(x)      (((uint32_t)(((uint32_t)(x))<<SMC_STANDBY_CFG_OPTION_SHIFT))&SMC_STANDBY_CFG_OPTION_MASK)

/* STANDBY_CFG Reg Mask */

#define SMC_STANDBY_CFG_MASK           0x00000003u





/*!

 * @}

 */ /* end of group SMC_Register_Masks */



/*!

 * @}

 */ /* end of group SMC_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
