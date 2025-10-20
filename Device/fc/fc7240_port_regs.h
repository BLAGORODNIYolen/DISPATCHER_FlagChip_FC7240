#ifndef _FC7240_PORT_NU_Tztufn47_REGS_H_
#define _FC7240_PORT_NU_Tztufn47_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- PORT Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup PORT_Peripheral_Access_Layer PORT Peripheral Access Layer

 * @{

 */



/** PORT - Size of Registers Arrays */



/** PORT - Register Layout Typedef */

#define PORT_PCR_COUNT 32



typedef struct {



  __IO uint32_t PCR[PORT_PCR_COUNT]           ; /* Port Control Register, offset: 0x0 */

  __O  uint32_t GPCLR                         ; /* Global Pin Control Low Register, offset: 0x80 */

  __O  uint32_t GPCHR                         ; /* Global Pin Control High Register, offset: 0x84 */

  __O  uint32_t GICLR                         ; /* Global Interrupt Control Low Register, offset: 0x88 */

  __O  uint32_t GICHR                         ; /* Global Interrupt Control High Register, offset: 0x8C */

       uint8_t  RESERVED_0[16];

  __IO uint32_t ISFR                          ; /* Interrupt Status Flag Register, offset: 0xA0 */

       uint8_t  RESERVED_1[28];

  __IO uint32_t DFER                          ; /* Digital Filter Enable Register, offset: 0xC0 */

  __IO uint32_t DFCR                          ; /* Digital Filter Clock Register, offset: 0xC4 */

  __IO uint32_t DFWR                          ; /* Digital Filter Width Register, offset: 0xC8 */

  __IO uint32_t GLDWP                         ; /* Global Domain Write Protection Register, offset: 0xCC */



} PORT_Type, *PORT_MemMapPtr;



/** Number of instances of the PORT module. */

#define PORT_INSTANCE_COUNT                      (5u)



/* PORT - Peripheral instance base addresses */

/** Peripheral PORTA base address */

#define PORTA_BASE                               (0x40047000u)

/** Peripheral PORTA base pointer */

#define PORTA                                    ((PORT_Type *)PORTA_BASE)

/** Peripheral PORTB base address */

#define PORTB_BASE                               (0x40048000u)

/** Peripheral PORTB base pointer */

#define PORTB                                    ((PORT_Type *)PORTB_BASE)

/** Peripheral PORTC base address */

#define PORTC_BASE                               (0x40049000u)

/** Peripheral PORTC base pointer */

#define PORTC                                    ((PORT_Type *)PORTC_BASE)

/** Peripheral PORTD base address */

#define PORTD_BASE                               (0x4004a000u)

/** Peripheral PORTD base pointer */

#define PORTD                                    ((PORT_Type *)PORTD_BASE)

/** Peripheral PORTE base address */

#define PORTE_BASE                               (0x4004b000u)

/** Peripheral PORTE base pointer */

#define PORTE                                    ((PORT_Type *)PORTE_BASE)

/** Array initializer of PORT peripheral base addresses */

#define PORT_BASE_ADDRS                          {PORTA_BASE, PORTB_BASE, PORTC_BASE, PORTD_BASE, PORTE_BASE}

/** Array initializer of PORT peripheral base pointers */

#define PORT_BASE_PTRS                           {PORTA, PORTB, PORTC, PORTD, PORTE}

// need fill by yourself

///** Number of interrupt vector arrays for the PORT module. */

//#define PORT_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the PORT module. */

//#define PORT_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the PORT peripheral type */

//#define PORT_IRQS                                {PORTA_IRQn, PORTB_IRQn, PORTC_IRQn, PORTD_IRQn, PORTE_IRQn}





/* ----------------------------------------------------------------------------

   -- PORT Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup PORT_Register_Masks PORT Register Masks

 * @{

 */



/* PCR Bit Fields */

#define PORT_PCR_DWPLK_MASK            0x80000000u

#define PORT_PCR_DWPLK_SHIFT           31u

#define PORT_PCR_DWPLK_WIDTH           1u

#define PORT_PCR_DWPLK(x)              (((uint32_t)(((uint32_t)(x))<<PORT_PCR_DWPLK_SHIFT))&PORT_PCR_DWPLK_MASK)

#define PORT_PCR_DWP_MASK              0x3E000000u

#define PORT_PCR_DWP_SHIFT             25u

#define PORT_PCR_DWP_WIDTH             5u

#define PORT_PCR_DWP(x)                (((uint32_t)(((uint32_t)(x))<<PORT_PCR_DWP_SHIFT))&PORT_PCR_DWP_MASK)

#define PORT_PCR_ISF_MASK              0x1000000u

#define PORT_PCR_ISF_SHIFT             24u

#define PORT_PCR_ISF_WIDTH             1u

#define PORT_PCR_ISF(x)                (((uint32_t)(((uint32_t)(x))<<PORT_PCR_ISF_SHIFT))&PORT_PCR_ISF_MASK)

#define PORT_PCR_ESTOP_MASK            0x200000u

#define PORT_PCR_ESTOP_SHIFT           21u

#define PORT_PCR_ESTOP_WIDTH           1u

#define PORT_PCR_ESTOP(x)              (((uint32_t)(((uint32_t)(x))<<PORT_PCR_ESTOP_SHIFT))&PORT_PCR_ESTOP_MASK)

#define PORT_PCR_WKUDIS_MASK           0x100000u

#define PORT_PCR_WKUDIS_SHIFT          20u

#define PORT_PCR_WKUDIS_WIDTH          1u

#define PORT_PCR_WKUDIS(x)             (((uint32_t)(((uint32_t)(x))<<PORT_PCR_WKUDIS_SHIFT))&PORT_PCR_WKUDIS_MASK)

#define PORT_PCR_IRQC_MASK             0xF0000u

#define PORT_PCR_IRQC_SHIFT            16u

#define PORT_PCR_IRQC_WIDTH            4u

#define PORT_PCR_IRQC(x)               (((uint32_t)(((uint32_t)(x))<<PORT_PCR_IRQC_SHIFT))&PORT_PCR_IRQC_MASK)

#define PORT_PCR_LK_MASK               0x8000u

#define PORT_PCR_LK_SHIFT              15u

#define PORT_PCR_LK_WIDTH              1u

#define PORT_PCR_LK(x)                 (((uint32_t)(((uint32_t)(x))<<PORT_PCR_LK_SHIFT))&PORT_PCR_LK_MASK)

#define PORT_PCR_MUX_MASK              0x700u

#define PORT_PCR_MUX_SHIFT             8u

#define PORT_PCR_MUX_WIDTH             3u

#define PORT_PCR_MUX(x)                (((uint32_t)(((uint32_t)(x))<<PORT_PCR_MUX_SHIFT))&PORT_PCR_MUX_MASK)

#define PORT_PCR_DSE1_MASK             0x80u

#define PORT_PCR_DSE1_SHIFT            7u

#define PORT_PCR_DSE1_WIDTH            1u

#define PORT_PCR_DSE1(x)               (((uint32_t)(((uint32_t)(x))<<PORT_PCR_DSE1_SHIFT))&PORT_PCR_DSE1_MASK)

#define PORT_PCR_DSE0_MASK             0x40u

#define PORT_PCR_DSE0_SHIFT            6u

#define PORT_PCR_DSE0_WIDTH            1u

#define PORT_PCR_DSE0(x)               (((uint32_t)(((uint32_t)(x))<<PORT_PCR_DSE0_SHIFT))&PORT_PCR_DSE0_MASK)

#define PORT_PCR_ODE_MASK              0x20u

#define PORT_PCR_ODE_SHIFT             5u

#define PORT_PCR_ODE_WIDTH             1u

#define PORT_PCR_ODE(x)                (((uint32_t)(((uint32_t)(x))<<PORT_PCR_ODE_SHIFT))&PORT_PCR_ODE_MASK)

#define PORT_PCR_PFE_MASK              0x10u

#define PORT_PCR_PFE_SHIFT             4u

#define PORT_PCR_PFE_WIDTH             1u

#define PORT_PCR_PFE(x)                (((uint32_t)(((uint32_t)(x))<<PORT_PCR_PFE_SHIFT))&PORT_PCR_PFE_MASK)

#define PORT_PCR_SRE_MASK              0x4u

#define PORT_PCR_SRE_SHIFT             2u

#define PORT_PCR_SRE_WIDTH             1u

#define PORT_PCR_SRE(x)                (((uint32_t)(((uint32_t)(x))<<PORT_PCR_SRE_SHIFT))&PORT_PCR_SRE_MASK)

#define PORT_PCR_PE_MASK               0x2u

#define PORT_PCR_PE_SHIFT              1u

#define PORT_PCR_PE_WIDTH              1u

#define PORT_PCR_PE(x)                 (((uint32_t)(((uint32_t)(x))<<PORT_PCR_PE_SHIFT))&PORT_PCR_PE_MASK)

#define PORT_PCR_PS_MASK               0x1u

#define PORT_PCR_PS_SHIFT              0u

#define PORT_PCR_PS_WIDTH              1u

#define PORT_PCR_PS(x)                 (((uint32_t)(((uint32_t)(x))<<PORT_PCR_PS_SHIFT))&PORT_PCR_PS_MASK)

#define PORT_PCR_LOW_16BITS_MASK       0xFFFFU
#define PORT_PCR_HIGH_16BITS_MASK      0xFFFF0000U

/* PCR0 Reg Mask */

#define PORT_PCR_MASK                  0xBF3F87F7u



/* GPCLR Bit Fields */

#define PORT_GPCLR_GPWE_MASK           0xFFFF0000u

#define PORT_GPCLR_GPWE_SHIFT          16u

#define PORT_GPCLR_GPWE_WIDTH          16u

#define PORT_GPCLR_GPWE(x)             (((uint32_t)(((uint32_t)(x))<<PORT_GPCLR_GPWE_SHIFT))&PORT_GPCLR_GPWE_MASK)

#define PORT_GPCLR_GPWD_MASK           0xFFFFu

#define PORT_GPCLR_GPWD_SHIFT          0u

#define PORT_GPCLR_GPWD_WIDTH          16u

#define PORT_GPCLR_GPWD(x)             (((uint32_t)(((uint32_t)(x))<<PORT_GPCLR_GPWD_SHIFT))&PORT_GPCLR_GPWD_MASK)

/* GPCLR Reg Mask */

#define PORT_GPCLR_MASK                0xFFFFFFFFu



/* GPCHR Bit Fields */

#define PORT_GPCHR_GPWE_MASK           0xFFFF0000u

#define PORT_GPCHR_GPWE_SHIFT          16u

#define PORT_GPCHR_GPWE_WIDTH          16u

#define PORT_GPCHR_GPWE(x)             (((uint32_t)(((uint32_t)(x))<<PORT_GPCHR_GPWE_SHIFT))&PORT_GPCHR_GPWE_MASK)

#define PORT_GPCHR_GPWD_MASK           0xFFFFu

#define PORT_GPCHR_GPWD_SHIFT          0u

#define PORT_GPCHR_GPWD_WIDTH          16u

#define PORT_GPCHR_GPWD(x)             (((uint32_t)(((uint32_t)(x))<<PORT_GPCHR_GPWD_SHIFT))&PORT_GPCHR_GPWD_MASK)

/* GPCHR Reg Mask */

#define PORT_GPCHR_MASK                0xFFFFFFFFu



/* GICLR Bit Fields */

#define PORT_GICLR_GIWD_MASK           0xFFFF0000u

#define PORT_GICLR_GIWD_SHIFT          16u

#define PORT_GICLR_GIWD_WIDTH          16u

#define PORT_GICLR_GIWD(x)             (((uint32_t)(((uint32_t)(x))<<PORT_GICLR_GIWD_SHIFT))&PORT_GICLR_GIWD_MASK)

#define PORT_GICLR_GIWE_MASK           0xFFFFu

#define PORT_GICLR_GIWE_SHIFT          0u

#define PORT_GICLR_GIWE_WIDTH          16u

#define PORT_GICLR_GIWE(x)             (((uint32_t)(((uint32_t)(x))<<PORT_GICLR_GIWE_SHIFT))&PORT_GICLR_GIWE_MASK)

/* GICLR Reg Mask */

#define PORT_GICLR_MASK                0xFFFFFFFFu



/* GICHR Bit Fields */

#define PORT_GICHR_GIWD_MASK           0xFFFF0000u

#define PORT_GICHR_GIWD_SHIFT          16u

#define PORT_GICHR_GIWD_WIDTH          16u

#define PORT_GICHR_GIWD(x)             (((uint32_t)(((uint32_t)(x))<<PORT_GICHR_GIWD_SHIFT))&PORT_GICHR_GIWD_MASK)

#define PORT_GICHR_GIWE_MASK           0xFFFFu

#define PORT_GICHR_GIWE_SHIFT          0u

#define PORT_GICHR_GIWE_WIDTH          16u

#define PORT_GICHR_GIWE(x)             (((uint32_t)(((uint32_t)(x))<<PORT_GICHR_GIWE_SHIFT))&PORT_GICHR_GIWE_MASK)

/* GICHR Reg Mask */

#define PORT_GICHR_MASK                0xFFFFFFFFu



/* ISFR Bit Fields */

#define PORT_ISFR_ISF_MASK             0xFFFFFFFFu

#define PORT_ISFR_ISF_SHIFT            0u

#define PORT_ISFR_ISF_WIDTH            32u

#define PORT_ISFR_ISF(x)               (((uint32_t)(((uint32_t)(x))<<PORT_ISFR_ISF_SHIFT))&PORT_ISFR_ISF_MASK)

/* ISFR Reg Mask */

#define PORT_ISFR_MASK                 0xFFFFFFFFu



/* DFER Bit Fields */

#define PORT_DFER_DFE_MASK             0xFFFFFFFFu

#define PORT_DFER_DFE_SHIFT            0u

#define PORT_DFER_DFE_WIDTH            32u

#define PORT_DFER_DFE(x)               (((uint32_t)(((uint32_t)(x))<<PORT_DFER_DFE_SHIFT))&PORT_DFER_DFE_MASK)

/* DFER Reg Mask */

#define PORT_DFER_MASK                 0xFFFFFFFFu



/* DFCR Bit Fields */

#define PORT_DFCR_CS_MASK              0x1u

#define PORT_DFCR_CS_SHIFT             0u

#define PORT_DFCR_CS_WIDTH             1u

#define PORT_DFCR_CS(x)                (((uint32_t)(((uint32_t)(x))<<PORT_DFCR_CS_SHIFT))&PORT_DFCR_CS_MASK)

/* DFCR Reg Mask */

#define PORT_DFCR_MASK                 0x00000001u



/* DFWR Bit Fields */

#define PORT_DFWR_FILT_MASK            0x1Fu

#define PORT_DFWR_FILT_SHIFT           0u

#define PORT_DFWR_FILT_WIDTH           5u

#define PORT_DFWR_FILT(x)              (((uint32_t)(((uint32_t)(x))<<PORT_DFWR_FILT_SHIFT))&PORT_DFWR_FILT_MASK)

/* DFWR Reg Mask */

#define PORT_DFWR_MASK                 0x0000001Fu



/* GLDWP Bit Fields */

#define PORT_GLDWP_DWPLK_MASK          0x80000000u

#define PORT_GLDWP_DWPLK_SHIFT         31u

#define PORT_GLDWP_DWPLK_WIDTH         1u

#define PORT_GLDWP_DWPLK(x)            (((uint32_t)(((uint32_t)(x))<<PORT_GLDWP_DWPLK_SHIFT))&PORT_GLDWP_DWPLK_MASK)

#define PORT_GLDWP_DWP_MASK            0x3E000000u

#define PORT_GLDWP_DWP_SHIFT           25u

#define PORT_GLDWP_DWP_WIDTH           5u

#define PORT_GLDWP_DWP(x)              (((uint32_t)(((uint32_t)(x))<<PORT_GLDWP_DWP_SHIFT))&PORT_GLDWP_DWP_MASK)

/* GLDWP Reg Mask */

#define PORT_GLDWP_MASK                0xBE000000u





/*!

 * @}

 */ /* end of group PORT_Register_Masks */



/*!

 * @}

 */ /* end of group PORT_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
