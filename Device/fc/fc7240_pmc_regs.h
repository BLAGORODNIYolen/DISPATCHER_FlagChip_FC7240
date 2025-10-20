#ifndef _FC7240_PMC_NU_Tztufn12_REGS_H_
#define _FC7240_PMC_NU_Tztufn12_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- PMC Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup PMC_Peripheral_Access_Layer PMC Peripheral Access Layer

 * @{

 */



/** PMC - Size of Registers Arrays */



/** PMC - Register Layout Typedef */



typedef struct {



  __IO uint32_t LVSCR                         ; /* Low Voltage Status and Control Register, offset: 0x0 */

  __IO uint32_t CONFIG                        ; /* PMC Configuration Register, offset: 0x4 */



} PMC_Type, *PMC_MemMapPtr;



/** Number of instances of the PMC module. */

#define PMC_INSTANCE_COUNT                       (1u)



/* PMC - Peripheral instance base addresses */

/** Peripheral PMC base address */

#define PMC_BASE                                 (0x40044000u)

/** Peripheral PMC base pointer */

#define PMC                                      ((PMC_Type *)PMC_BASE)

/** Array initializer of PMC peripheral base addresses */

#define PMC_BASE_ADDRS                           {PMC_BASE}

/** Array initializer of PMC peripheral base pointers */

#define PMC_BASE_PTRS                            {PMC}

// need fill by yourself

///** Number of interrupt vector arrays for the PMC module. */

//#define PMC_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the PMC module. */

//#define PMC_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the PMC peripheral type */

//#define PMC_IRQS                                 {PMC_IRQn}





/* ----------------------------------------------------------------------------

   -- PMC Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup PMC_Register_Masks PMC Register Masks

 * @{

 */



/* LVSCR Bit Fields */

#define PMC_LVSCR_POR_FLAG_MASK        0x80000000u

#define PMC_LVSCR_POR_FLAG_SHIFT       31u

#define PMC_LVSCR_POR_FLAG_WIDTH       1u

#define PMC_LVSCR_POR_FLAG(x)          (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_POR_FLAG_SHIFT))&PMC_LVSCR_POR_FLAG_MASK)

#define PMC_LVSCR_V15_STATUS_MASK      0xC000000u

#define PMC_LVSCR_V15_STATUS_SHIFT     26u

#define PMC_LVSCR_V15_STATUS_WIDTH     2u

#define PMC_LVSCR_V15_STATUS(x)        (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_V15_STATUS_SHIFT))&PMC_LVSCR_V15_STATUS_MASK)

#define PMC_LVSCR_LVR1P1V_RPM_FLAG_MASK 0x800000u

#define PMC_LVSCR_LVR1P1V_RPM_FLAG_SHIFT 23u

#define PMC_LVSCR_LVR1P1V_RPM_FLAG_WIDTH 1u

#define PMC_LVSCR_LVR1P1V_RPM_FLAG(x)  (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVR1P1V_RPM_FLAG_SHIFT))&PMC_LVSCR_LVR1P1V_RPM_FLAG_MASK)

#define PMC_LVSCR_LVR1P1V_FPM_FLAG_MASK 0x400000u

#define PMC_LVSCR_LVR1P1V_FPM_FLAG_SHIFT 22u

#define PMC_LVSCR_LVR1P1V_FPM_FLAG_WIDTH 1u

#define PMC_LVSCR_LVR1P1V_FPM_FLAG(x)  (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVR1P1V_FPM_FLAG_SHIFT))&PMC_LVSCR_LVR1P1V_FPM_FLAG_MASK)

#define PMC_LVSCR_LVR2P5V_RPM_FLAG_MASK 0x200000u

#define PMC_LVSCR_LVR2P5V_RPM_FLAG_SHIFT 21u

#define PMC_LVSCR_LVR2P5V_RPM_FLAG_WIDTH 1u

#define PMC_LVSCR_LVR2P5V_RPM_FLAG(x)  (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVR2P5V_RPM_FLAG_SHIFT))&PMC_LVSCR_LVR2P5V_RPM_FLAG_MASK)

#define PMC_LVSCR_LVR2P5V_FPM_FLAG_MASK 0x100000u

#define PMC_LVSCR_LVR2P5V_FPM_FLAG_SHIFT 20u

#define PMC_LVSCR_LVR2P5V_FPM_FLAG_WIDTH 1u

#define PMC_LVSCR_LVR2P5V_FPM_FLAG(x)  (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVR2P5V_FPM_FLAG_SHIFT))&PMC_LVSCR_LVR2P5V_FPM_FLAG_MASK)

#define PMC_LVSCR_LVR5V_RPM_FLAG_MASK  0x20000u

#define PMC_LVSCR_LVR5V_RPM_FLAG_SHIFT 17u

#define PMC_LVSCR_LVR5V_RPM_FLAG_WIDTH 1u

#define PMC_LVSCR_LVR5V_RPM_FLAG(x)    (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVR5V_RPM_FLAG_SHIFT))&PMC_LVSCR_LVR5V_RPM_FLAG_MASK)

#define PMC_LVSCR_LVR5V_FPM_FLAG_MASK  0x10000u

#define PMC_LVSCR_LVR5V_FPM_FLAG_SHIFT 16u

#define PMC_LVSCR_LVR5V_FPM_FLAG_WIDTH 1u

#define PMC_LVSCR_LVR5V_FPM_FLAG(x)    (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVR5V_FPM_FLAG_SHIFT))&PMC_LVSCR_LVR5V_FPM_FLAG_MASK)

#define PMC_LVSCR_HVD1P5V_STATUS_MASK  0x4000u

#define PMC_LVSCR_HVD1P5V_STATUS_SHIFT 14u

#define PMC_LVSCR_HVD1P5V_STATUS_WIDTH 1u

#define PMC_LVSCR_HVD1P5V_STATUS(x)    (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD1P5V_STATUS_SHIFT))&PMC_LVSCR_HVD1P5V_STATUS_MASK)

#define PMC_LVSCR_LVD1P5V_STATUS_MASK  0x2000u

#define PMC_LVSCR_LVD1P5V_STATUS_SHIFT 13u

#define PMC_LVSCR_LVD1P5V_STATUS_WIDTH 1u

#define PMC_LVSCR_LVD1P5V_STATUS(x)    (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVD1P5V_STATUS_SHIFT))&PMC_LVSCR_LVD1P5V_STATUS_MASK)

#define PMC_LVSCR_LVD5V_STATUS_MASK    0x1000u

#define PMC_LVSCR_LVD5V_STATUS_SHIFT   12u

#define PMC_LVSCR_LVD5V_STATUS_WIDTH   1u

#define PMC_LVSCR_LVD5V_STATUS(x)      (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVD5V_STATUS_SHIFT))&PMC_LVSCR_LVD5V_STATUS_MASK)

#define PMC_LVSCR_HVD1P1V_STATUS_MASK  0x800u

#define PMC_LVSCR_HVD1P1V_STATUS_SHIFT 11u

#define PMC_LVSCR_HVD1P1V_STATUS_WIDTH 1u

#define PMC_LVSCR_HVD1P1V_STATUS(x)    (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD1P1V_STATUS_SHIFT))&PMC_LVSCR_HVD1P1V_STATUS_MASK)

#define PMC_LVSCR_HVD2P5V_STATUS_MASK  0x400u

#define PMC_LVSCR_HVD2P5V_STATUS_SHIFT 10u

#define PMC_LVSCR_HVD2P5V_STATUS_WIDTH 1u

#define PMC_LVSCR_HVD2P5V_STATUS(x)    (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD2P5V_STATUS_SHIFT))&PMC_LVSCR_HVD2P5V_STATUS_MASK)

#define PMC_LVSCR_HVD5V_STATUS_MASK    0x100u

#define PMC_LVSCR_HVD5V_STATUS_SHIFT   8u

#define PMC_LVSCR_HVD5V_STATUS_WIDTH   1u

#define PMC_LVSCR_HVD5V_STATUS(x)      (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD5V_STATUS_SHIFT))&PMC_LVSCR_HVD5V_STATUS_MASK)

#define PMC_LVSCR_HVD1P5V_FLAG_MASK    0x40u

#define PMC_LVSCR_HVD1P5V_FLAG_SHIFT   6u

#define PMC_LVSCR_HVD1P5V_FLAG_WIDTH   1u

#define PMC_LVSCR_HVD1P5V_FLAG(x)      (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD1P5V_FLAG_SHIFT))&PMC_LVSCR_HVD1P5V_FLAG_MASK)

#define PMC_LVSCR_LVD1P5V_FLAG_MASK    0x20u

#define PMC_LVSCR_LVD1P5V_FLAG_SHIFT   5u

#define PMC_LVSCR_LVD1P5V_FLAG_WIDTH   1u

#define PMC_LVSCR_LVD1P5V_FLAG(x)      (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVD1P5V_FLAG_SHIFT))&PMC_LVSCR_LVD1P5V_FLAG_MASK)

#define PMC_LVSCR_LVD5V_FLAG_MASK      0x10u

#define PMC_LVSCR_LVD5V_FLAG_SHIFT     4u

#define PMC_LVSCR_LVD5V_FLAG_WIDTH     1u

#define PMC_LVSCR_LVD5V_FLAG(x)        (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVD5V_FLAG_SHIFT))&PMC_LVSCR_LVD5V_FLAG_MASK)

#define PMC_LVSCR_HVD1P1V_FLAG_MASK    0x8u

#define PMC_LVSCR_HVD1P1V_FLAG_SHIFT   3u

#define PMC_LVSCR_HVD1P1V_FLAG_WIDTH   1u

#define PMC_LVSCR_HVD1P1V_FLAG(x)      (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD1P1V_FLAG_SHIFT))&PMC_LVSCR_HVD1P1V_FLAG_MASK)

#define PMC_LVSCR_HVD2P5V_FLAG_MASK    0x4u

#define PMC_LVSCR_HVD2P5V_FLAG_SHIFT   2u

#define PMC_LVSCR_HVD2P5V_FLAG_WIDTH   1u

#define PMC_LVSCR_HVD2P5V_FLAG(x)      (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD2P5V_FLAG_SHIFT))&PMC_LVSCR_HVD2P5V_FLAG_MASK)

#define PMC_LVSCR_HVD5V_FLAG_MASK      0x1u

#define PMC_LVSCR_HVD5V_FLAG_SHIFT     0u

#define PMC_LVSCR_HVD5V_FLAG_WIDTH     1u

#define PMC_LVSCR_HVD5V_FLAG(x)        (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD5V_FLAG_SHIFT))&PMC_LVSCR_HVD5V_FLAG_MASK)

/* LVSCR Reg Mask */

#define PMC_LVSCR_MASK                 0x8CF37D7Du



/* CONFIG Bit Fields */

#define PMC_CONFIG_V15_LOCK_MASK       0x8000u

#define PMC_CONFIG_V15_LOCK_SHIFT      15u

#define PMC_CONFIG_V15_LOCK_WIDTH      1u

#define PMC_CONFIG_V15_LOCK(x)         (((uint32_t)(((uint32_t)(x))<<PMC_CONFIG_V15_LOCK_SHIFT))&PMC_CONFIG_V15_LOCK_MASK)

#define PMC_CONFIG_LVD_IE_MASK         0x200u

#define PMC_CONFIG_LVD_IE_SHIFT        9u

#define PMC_CONFIG_LVD_IE_WIDTH        1u

#define PMC_CONFIG_LVD_IE(x)           (((uint32_t)(((uint32_t)(x))<<PMC_CONFIG_LVD_IE_SHIFT))&PMC_CONFIG_LVD_IE_MASK)

#define PMC_CONFIG_HVD_IE_MASK         0x100u

#define PMC_CONFIG_HVD_IE_SHIFT        8u

#define PMC_CONFIG_HVD_IE_WIDTH        1u

#define PMC_CONFIG_HVD_IE(x)           (((uint32_t)(((uint32_t)(x))<<PMC_CONFIG_HVD_IE_SHIFT))&PMC_CONFIG_HVD_IE_MASK)

#define PMC_CONFIG_V15_CTRL_EN_MASK    0x20u

#define PMC_CONFIG_V15_CTRL_EN_SHIFT   5u

#define PMC_CONFIG_V15_CTRL_EN_WIDTH   1u

#define PMC_CONFIG_V15_CTRL_EN(x)      (((uint32_t)(((uint32_t)(x))<<PMC_CONFIG_V15_CTRL_EN_SHIFT))&PMC_CONFIG_V15_CTRL_EN_MASK)

#define PMC_CONFIG_V15_AUTOSW_MASK     0x10u

#define PMC_CONFIG_V15_AUTOSW_SHIFT    4u

#define PMC_CONFIG_V15_AUTOSW_WIDTH    1u

#define PMC_CONFIG_V15_AUTOSW(x)       (((uint32_t)(((uint32_t)(x))<<PMC_CONFIG_V15_AUTOSW_SHIFT))&PMC_CONFIG_V15_AUTOSW_MASK)

#define PMC_CONFIG_RPM_VDD2P5_EN_MASK  0x8u

#define PMC_CONFIG_RPM_VDD2P5_EN_SHIFT 3u

#define PMC_CONFIG_RPM_VDD2P5_EN_WIDTH 1u

#define PMC_CONFIG_RPM_VDD2P5_EN(x)    (((uint32_t)(((uint32_t)(x))<<PMC_CONFIG_RPM_VDD2P5_EN_SHIFT))&PMC_CONFIG_RPM_VDD2P5_EN_MASK)

/* CONFIG Reg Mask */

#define PMC_CONFIG_MASK                0x00008338u





/*!

 * @}

 */ /* end of group PMC_Register_Masks */



/*!

 * @}

 */ /* end of group PMC_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
