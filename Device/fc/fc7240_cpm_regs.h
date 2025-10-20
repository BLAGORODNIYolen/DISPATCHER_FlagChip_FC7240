#ifndef _FC7240_CPM_NU_Tztufn6_REGS_H_
#define _FC7240_CPM_NU_Tztufn6_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- CPM Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup CPM_Peripheral_Access_Layer CPM Peripheral Access Layer

 * @{

 */



/** CPM - Size of Registers Arrays */



/** CPM - Register Layout Typedef */



typedef struct {



  __IO uint32_t FISCR                         ; /* FPU Interrupt Status and Control Register, offset: 0x0 */

  __IO uint32_t MISCR                         ; /* Miscellaneous Control Register, offset: 0x4 */

       uint8_t  RESERVED_0[24];

  __IO uint32_t TCMRCR                        ; /* TCM Retry Control Register, offset: 0x20 */



} CPM_Type, *CPM_MemMapPtr;



/** Number of instances of the CPM module. */

#define CPM_INSTANCE_COUNT                       (1u)



/* CPM - Peripheral instance base addresses */

/** Peripheral CPM base address */

#define CPM_BASE                                 (0xE0080000u)

/** Peripheral CPM base pointer */

#define CPM                                      ((CPM_Type *)CPM_BASE)

/** Array initializer of CPM peripheral base addresses */

#define CPM_BASE_ADDRS                           {CPM_BASE}

/** Array initializer of CPM peripheral base pointers */

#define CPM_BASE_PTRS                            {CPM}

// need fill by yourself

///** Number of interrupt vector arrays for the CPM module. */

//#define CPM_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the CPM module. */

//#define CPM_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the CPM peripheral type */

//#define CPM_IRQS                                 {CPM_IRQn}





/* ----------------------------------------------------------------------------

   -- CPM Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup CPM_Register_Masks CPM Register Masks

 * @{

 */



/* FISCR Bit Fields */

#define CPM_FISCR_FIXCE_MASK           0x200000u

#define CPM_FISCR_FIXCE_SHIFT          21u

#define CPM_FISCR_FIXCE_WIDTH          1u

#define CPM_FISCR_FIXCE(x)             (((uint32_t)(((uint32_t)(x))<<CPM_FISCR_FIXCE_SHIFT))&CPM_FISCR_FIXCE_MASK)

#define CPM_FISCR_FIDCE_MASK           0x100000u

#define CPM_FISCR_FIDCE_SHIFT          20u

#define CPM_FISCR_FIDCE_WIDTH          1u

#define CPM_FISCR_FIDCE(x)             (((uint32_t)(((uint32_t)(x))<<CPM_FISCR_FIDCE_SHIFT))&CPM_FISCR_FIDCE_MASK)

#define CPM_FISCR_FOFCE_MASK           0x80000u

#define CPM_FISCR_FOFCE_SHIFT          19u

#define CPM_FISCR_FOFCE_WIDTH          1u

#define CPM_FISCR_FOFCE(x)             (((uint32_t)(((uint32_t)(x))<<CPM_FISCR_FOFCE_SHIFT))&CPM_FISCR_FOFCE_MASK)

#define CPM_FISCR_FUFCE_MASK           0x40000u

#define CPM_FISCR_FUFCE_SHIFT          18u

#define CPM_FISCR_FUFCE_WIDTH          1u

#define CPM_FISCR_FUFCE(x)             (((uint32_t)(((uint32_t)(x))<<CPM_FISCR_FUFCE_SHIFT))&CPM_FISCR_FUFCE_MASK)

#define CPM_FISCR_FDZCE_MASK           0x20000u

#define CPM_FISCR_FDZCE_SHIFT          17u

#define CPM_FISCR_FDZCE_WIDTH          1u

#define CPM_FISCR_FDZCE(x)             (((uint32_t)(((uint32_t)(x))<<CPM_FISCR_FDZCE_SHIFT))&CPM_FISCR_FDZCE_MASK)

#define CPM_FISCR_FIOCE_MASK           0x10000u

#define CPM_FISCR_FIOCE_SHIFT          16u

#define CPM_FISCR_FIOCE_WIDTH          1u

#define CPM_FISCR_FIOCE(x)             (((uint32_t)(((uint32_t)(x))<<CPM_FISCR_FIOCE_SHIFT))&CPM_FISCR_FIOCE_MASK)

#define CPM_FISCR_FIXC_MASK            0x20u

#define CPM_FISCR_FIXC_SHIFT           5u

#define CPM_FISCR_FIXC_WIDTH           1u

#define CPM_FISCR_FIXC(x)              (((uint32_t)(((uint32_t)(x))<<CPM_FISCR_FIXC_SHIFT))&CPM_FISCR_FIXC_MASK)

#define CPM_FISCR_FIDC_MASK            0x10u

#define CPM_FISCR_FIDC_SHIFT           4u

#define CPM_FISCR_FIDC_WIDTH           1u

#define CPM_FISCR_FIDC(x)              (((uint32_t)(((uint32_t)(x))<<CPM_FISCR_FIDC_SHIFT))&CPM_FISCR_FIDC_MASK)

#define CPM_FISCR_FOFC_MASK            0x8u

#define CPM_FISCR_FOFC_SHIFT           3u

#define CPM_FISCR_FOFC_WIDTH           1u

#define CPM_FISCR_FOFC(x)              (((uint32_t)(((uint32_t)(x))<<CPM_FISCR_FOFC_SHIFT))&CPM_FISCR_FOFC_MASK)

#define CPM_FISCR_FUFC_MASK            0x4u

#define CPM_FISCR_FUFC_SHIFT           2u

#define CPM_FISCR_FUFC_WIDTH           1u

#define CPM_FISCR_FUFC(x)              (((uint32_t)(((uint32_t)(x))<<CPM_FISCR_FUFC_SHIFT))&CPM_FISCR_FUFC_MASK)

#define CPM_FISCR_FDZC_MASK            0x2u

#define CPM_FISCR_FDZC_SHIFT           1u

#define CPM_FISCR_FDZC_WIDTH           1u

#define CPM_FISCR_FDZC(x)              (((uint32_t)(((uint32_t)(x))<<CPM_FISCR_FDZC_SHIFT))&CPM_FISCR_FDZC_MASK)

#define CPM_FISCR_FIOC_MASK            0x1u

#define CPM_FISCR_FIOC_SHIFT           0u

#define CPM_FISCR_FIOC_WIDTH           1u

#define CPM_FISCR_FIOC(x)              (((uint32_t)(((uint32_t)(x))<<CPM_FISCR_FIOC_SHIFT))&CPM_FISCR_FIOC_MASK)

/* FISCR Reg Mask */

#define CPM_FISCR_MASK                 0x003F003Fu



/* MISCR Bit Fields */

#define CPM_MISCR_AHBS_PRIORITY_MASK   0x1u

#define CPM_MISCR_AHBS_PRIORITY_SHIFT  0u

#define CPM_MISCR_AHBS_PRIORITY_WIDTH  1u

#define CPM_MISCR_AHBS_PRIORITY(x)     (((uint32_t)(((uint32_t)(x))<<CPM_MISCR_AHBS_PRIORITY_SHIFT))&CPM_MISCR_AHBS_PRIORITY_MASK)

/* MISCR Reg Mask */

#define CPM_MISCR_MASK                 0x00000001u



/* TCMRCR Bit Fields */

#define CPM_TCMRCR_D1RBCLR_MASK        0x4000u

#define CPM_TCMRCR_D1RBCLR_SHIFT       14u

#define CPM_TCMRCR_D1RBCLR_WIDTH       1u

#define CPM_TCMRCR_D1RBCLR(x)          (((uint32_t)(((uint32_t)(x))<<CPM_TCMRCR_D1RBCLR_SHIFT))&CPM_TCMRCR_D1RBCLR_MASK)

#define CPM_TCMRCR_D0RBCLR_MASK        0x2000u

#define CPM_TCMRCR_D0RBCLR_SHIFT       13u

#define CPM_TCMRCR_D0RBCLR_WIDTH       1u

#define CPM_TCMRCR_D0RBCLR(x)          (((uint32_t)(((uint32_t)(x))<<CPM_TCMRCR_D0RBCLR_SHIFT))&CPM_TCMRCR_D0RBCLR_MASK)

#define CPM_TCMRCR_IRBCLR_MASK         0x1000u

#define CPM_TCMRCR_IRBCLR_SHIFT        12u

#define CPM_TCMRCR_IRBCLR_WIDTH        1u

#define CPM_TCMRCR_IRBCLR(x)           (((uint32_t)(((uint32_t)(x))<<CPM_TCMRCR_IRBCLR_SHIFT))&CPM_TCMRCR_IRBCLR_MASK)

#define CPM_TCMRCR_D1RBVLD_MASK        0x400u

#define CPM_TCMRCR_D1RBVLD_SHIFT       10u

#define CPM_TCMRCR_D1RBVLD_WIDTH       1u

#define CPM_TCMRCR_D1RBVLD(x)          (((uint32_t)(((uint32_t)(x))<<CPM_TCMRCR_D1RBVLD_SHIFT))&CPM_TCMRCR_D1RBVLD_MASK)

#define CPM_TCMRCR_D0RBVLD_MASK        0x200u

#define CPM_TCMRCR_D0RBVLD_SHIFT       9u

#define CPM_TCMRCR_D0RBVLD_WIDTH       1u

#define CPM_TCMRCR_D0RBVLD(x)          (((uint32_t)(((uint32_t)(x))<<CPM_TCMRCR_D0RBVLD_SHIFT))&CPM_TCMRCR_D0RBVLD_MASK)

#define CPM_TCMRCR_IRBVLD_MASK         0x100u

#define CPM_TCMRCR_IRBVLD_SHIFT        8u

#define CPM_TCMRCR_IRBVLD_WIDTH        1u

#define CPM_TCMRCR_IRBVLD(x)           (((uint32_t)(((uint32_t)(x))<<CPM_TCMRCR_IRBVLD_SHIFT))&CPM_TCMRCR_IRBVLD_MASK)

#define CPM_TCMRCR_D1RBIE_MASK         0x40u

#define CPM_TCMRCR_D1RBIE_SHIFT        6u

#define CPM_TCMRCR_D1RBIE_WIDTH        1u

#define CPM_TCMRCR_D1RBIE(x)           (((uint32_t)(((uint32_t)(x))<<CPM_TCMRCR_D1RBIE_SHIFT))&CPM_TCMRCR_D1RBIE_MASK)

#define CPM_TCMRCR_D0RBIE_MASK         0x20u

#define CPM_TCMRCR_D0RBIE_SHIFT        5u

#define CPM_TCMRCR_D0RBIE_WIDTH        1u

#define CPM_TCMRCR_D0RBIE(x)           (((uint32_t)(((uint32_t)(x))<<CPM_TCMRCR_D0RBIE_SHIFT))&CPM_TCMRCR_D0RBIE_MASK)

#define CPM_TCMRCR_IRBIE_MASK          0x10u

#define CPM_TCMRCR_IRBIE_SHIFT         4u

#define CPM_TCMRCR_IRBIE_WIDTH         1u

#define CPM_TCMRCR_IRBIE(x)            (((uint32_t)(((uint32_t)(x))<<CPM_TCMRCR_IRBIE_SHIFT))&CPM_TCMRCR_IRBIE_MASK)

#define CPM_TCMRCR_D1RBAC_MASK         0x4u

#define CPM_TCMRCR_D1RBAC_SHIFT        2u

#define CPM_TCMRCR_D1RBAC_WIDTH        1u

#define CPM_TCMRCR_D1RBAC(x)           (((uint32_t)(((uint32_t)(x))<<CPM_TCMRCR_D1RBAC_SHIFT))&CPM_TCMRCR_D1RBAC_MASK)

#define CPM_TCMRCR_D0RBAC_MASK         0x2u

#define CPM_TCMRCR_D0RBAC_SHIFT        1u

#define CPM_TCMRCR_D0RBAC_WIDTH        1u

#define CPM_TCMRCR_D0RBAC(x)           (((uint32_t)(((uint32_t)(x))<<CPM_TCMRCR_D0RBAC_SHIFT))&CPM_TCMRCR_D0RBAC_MASK)

#define CPM_TCMRCR_IRBAC_MASK          0x1u

#define CPM_TCMRCR_IRBAC_SHIFT         0u

#define CPM_TCMRCR_IRBAC_WIDTH         1u

#define CPM_TCMRCR_IRBAC(x)            (((uint32_t)(((uint32_t)(x))<<CPM_TCMRCR_IRBAC_SHIFT))&CPM_TCMRCR_IRBAC_MASK)

/* TCMRCR Reg Mask */

#define CPM_TCMRCR_MASK                0x00007777u


/*!

 * @}

 */ /* end of group CPM_Register_Masks */



/*!

 * @}

 */ /* end of group CPM_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
