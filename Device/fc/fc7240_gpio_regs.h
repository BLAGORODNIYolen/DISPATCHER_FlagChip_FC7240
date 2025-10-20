#ifndef _FC7240_GPIO_NU_Tztufn42_REGS_H_
#define _FC7240_GPIO_NU_Tztufn42_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- GPIO Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup GPIO_Peripheral_Access_Layer GPIO Peripheral Access Layer

 * @{

 */



/** GPIO - Size of Registers Arrays */



/** GPIO - Register Layout Typedef */



typedef struct {



  __IO uint32_t PDOR                          ; /* Port Data Output Register, offset: 0x0 */

  __O  uint32_t PSOR                          ; /* Port Set Output Register, offset: 0x4 */

  __O  uint32_t PCOR                          ; /* Port Clear Output Register, offset: 0x8 */

  __O  uint32_t PTOR                          ; /* Port Toggle Output Register, offset: 0xC */

  __I  uint32_t PDIR                          ; /* Port Data Input Register, offset: 0x10 */

  __IO uint32_t PDDR                          ; /* Port Data Direction Register, offset: 0x14 */

  __IO uint32_t PIDR                          ; /* Port Input Disable Register, offset: 0x18 */



} GPIO_Type, *GPIO_MemMapPtr;



/** Number of instances of the GPIO module. */

#define GPIO_INSTANCE_COUNT                      (5u)



/* GPIO - Peripheral instance base addresses */

/** Peripheral GPIOA base address */

#define GPIOA_BASE                               (0x41000000u)

/** Peripheral GPIOA base pointer */

#define GPIOA                                    ((GPIO_Type *)GPIOA_BASE)

/** Peripheral GPIOB base address */

#define GPIOB_BASE                               (0x41000040u)

/** Peripheral GPIOB base pointer */

#define GPIOB                                    ((GPIO_Type *)GPIOB_BASE)

/** Peripheral GPIOC base address */

#define GPIOC_BASE                               (0x41000080u)

/** Peripheral GPIOC base pointer */

#define GPIOC                                    ((GPIO_Type *)GPIOC_BASE)

/** Peripheral GPIOD base address */

#define GPIOD_BASE                               (0x410000c0u)

/** Peripheral GPIOD base pointer */

#define GPIOD                                    ((GPIO_Type *)GPIOD_BASE)

/** Peripheral GPIOE base address */

#define GPIOE_BASE                               (0x41000100u)

/** Peripheral GPIOE base pointer */

#define GPIOE                                    ((GPIO_Type *)GPIOE_BASE)

/** Array initializer of GPIO peripheral base addresses */

#define GPIO_BASE_ADDRS                          {GPIOA_BASE, GPIOB_BASE, GPIOC_BASE, GPIOD_BASE, GPIOE_BASE}

/** Array initializer of GPIO peripheral base pointers */

#define GPIO_BASE_PTRS                           {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE}

// need fill by yourself

///** Number of interrupt vector arrays for the GPIO module. */

//#define GPIO_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the GPIO module. */

//#define GPIO_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the GPIO peripheral type */

//#define GPIO_IRQS                                {GPIOA_IRQn, GPIOB_IRQn, GPIOC_IRQn, GPIOD_IRQn, GPIOE_IRQn}





/* ----------------------------------------------------------------------------

   -- GPIO Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup GPIO_Register_Masks GPIO Register Masks

 * @{

 */



/* PDOR Bit Fields */

#define GPIO_PDOR_PDO_MASK             0xFFFFFFFFu

#define GPIO_PDOR_PDO_SHIFT            0u

#define GPIO_PDOR_PDO_WIDTH            32u

#define GPIO_PDOR_PDO(x)               (((uint32_t)(((uint32_t)(x))<<GPIO_PDOR_PDO_SHIFT))&GPIO_PDOR_PDO_MASK)

/* PDOR Reg Mask */

#define GPIO_PDOR_MASK                 0xFFFFFFFFu



/* PSOR Bit Fields */

#define GPIO_PSOR_PSO_MASK             0xFFFFFFFFu

#define GPIO_PSOR_PSO_SHIFT            0u

#define GPIO_PSOR_PSO_WIDTH            32u

#define GPIO_PSOR_PSO(x)               (((uint32_t)(((uint32_t)(x))<<GPIO_PSOR_PSO_SHIFT))&GPIO_PSOR_PSO_MASK)

/* PSOR Reg Mask */

#define GPIO_PSOR_MASK                 0xFFFFFFFFu



/* PCOR Bit Fields */

#define GPIO_PCOR_PCO_MASK             0xFFFFFFFFu

#define GPIO_PCOR_PCO_SHIFT            0u

#define GPIO_PCOR_PCO_WIDTH            32u

#define GPIO_PCOR_PCO(x)               (((uint32_t)(((uint32_t)(x))<<GPIO_PCOR_PCO_SHIFT))&GPIO_PCOR_PCO_MASK)

/* PCOR Reg Mask */

#define GPIO_PCOR_MASK                 0xFFFFFFFFu



/* PTOR Bit Fields */

#define GPIO_PTOR_PTO_MASK             0xFFFFFFFFu

#define GPIO_PTOR_PTO_SHIFT            0u

#define GPIO_PTOR_PTO_WIDTH            32u

#define GPIO_PTOR_PTO(x)               (((uint32_t)(((uint32_t)(x))<<GPIO_PTOR_PTO_SHIFT))&GPIO_PTOR_PTO_MASK)

/* PTOR Reg Mask */

#define GPIO_PTOR_MASK                 0xFFFFFFFFu



/* PDIR Bit Fields */

#define GPIO_PDIR_PDI_MASK             0xFFFFFFFFu

#define GPIO_PDIR_PDI_SHIFT            0u

#define GPIO_PDIR_PDI_WIDTH            32u

#define GPIO_PDIR_PDI(x)               (((uint32_t)(((uint32_t)(x))<<GPIO_PDIR_PDI_SHIFT))&GPIO_PDIR_PDI_MASK)

/* PDIR Reg Mask */

#define GPIO_PDIR_MASK                 0xFFFFFFFFu



/* PDDR Bit Fields */

#define GPIO_PDDR_PDD_MASK             0xFFFFFFFFu

#define GPIO_PDDR_PDD_SHIFT            0u

#define GPIO_PDDR_PDD_WIDTH            32u

#define GPIO_PDDR_PDD(x)               (((uint32_t)(((uint32_t)(x))<<GPIO_PDDR_PDD_SHIFT))&GPIO_PDDR_PDD_MASK)

/* PDDR Reg Mask */

#define GPIO_PDDR_MASK                 0xFFFFFFFFu



/* PIDR Bit Fields */

#define GPIO_PIDR_PID_MASK             0xFFFFFFFFu

#define GPIO_PIDR_PID_SHIFT            0u

#define GPIO_PIDR_PID_WIDTH            32u

#define GPIO_PIDR_PID(x)               (((uint32_t)(((uint32_t)(x))<<GPIO_PIDR_PID_SHIFT))&GPIO_PIDR_PID_MASK)

/* PIDR Reg Mask */

#define GPIO_PIDR_MASK                 0xFFFFFFFFu





/*!

 * @}

 */ /* end of group GPIO_Register_Masks */



/*!

 * @}

 */ /* end of group GPIO_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
