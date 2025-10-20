#ifndef _FC7240_MAM_NU_Tztufn19_REGS_H_
#define _FC7240_MAM_NU_Tztufn19_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- MAM Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup MAM_Peripheral_Access_Layer MAM Peripheral Access Layer

 * @{

 */



/** MAM - Size of Registers Arrays */



/** MAM - Register Layout Typedef */

#define MAM_ACLR_COUNT 12

#define MAM_ACR_COUNT 188



typedef struct {



  __IO uint32_t MAXCFG                        ; /* Matrix Configuration Register, offset: 0x000 */

  __IO uint32_t BSTCR                         ; /* Burst Control Register, offset: 0x004 */

       uint8_t  RESERVED_0[248];

  __IO uint32_t WDGCR                         ; /* Watchdog Control Register, offset: 0x100 */

  __IO uint32_t TOCR                          ; /* Timeout Control Register, offset: 0x104 */

  __IO uint32_t WDGDIV                        ; /* Watchdog Divider Register, offset: 0x108 */

       uint8_t  RESERVED_1[1524];

  __IO uint32_t ACLR[MAM_ACLR_COUNT]          ; /* Access Control Lock Register, offset: 0x700 */

       uint8_t  RESERVED_2[208];

  __IO uint32_t ACR[MAM_ACR_COUNT]            ; /* Access Control Register, offset: 0x800 */



} MAM_Type, *MAM_MemMapPtr;



/** Number of instances of the MAM module. */

#define MAM_INSTANCE_COUNT                       (1u)



/* MAM - Peripheral instance base addresses */

/** Peripheral MAM base address */

#define MAM_BASE                                 (0x4040d000u)

/** Peripheral MAM base pointer */

#define MAM                                      ((MAM_Type *)MAM_BASE)

/** Array initializer of MAM peripheral base addresses */

#define MAM_BASE_ADDRS                           {MAM_BASE}

/** Array initializer of MAM peripheral base pointers */

#define MAM_BASE_PTRS                            {MAM}

// need fill by yourself

///** Number of interrupt vector arrays for the MAM module. */

//#define MAM_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the MAM module. */

//#define MAM_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the MAM peripheral type */

//#define MAM_IRQS                                 {MAM_IRQn}





/* ----------------------------------------------------------------------------

   -- MAM Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup MAM_Register_Masks MAM Register Masks

 * @{

 */



/* MAXCFG Bit Fields */

#define MAM_MAXCFG_MASTERNUM_MASK      0xFF000000u

#define MAM_MAXCFG_MASTERNUM_SHIFT     24u

#define MAM_MAXCFG_MASTERNUM_WIDTH     8u

#define MAM_MAXCFG_MASTERNUM(x)        (((uint32_t)(((uint32_t)(x))<<MAM_MAXCFG_MASTERNUM_SHIFT))&MAM_MAXCFG_MASTERNUM_MASK)

#define MAM_MAXCFG_SLAVENUM_MASK       0xFF00u

#define MAM_MAXCFG_SLAVENUM_SHIFT      8u

#define MAM_MAXCFG_SLAVENUM_WIDTH      8u

#define MAM_MAXCFG_SLAVENUM(x)         (((uint32_t)(((uint32_t)(x))<<MAM_MAXCFG_SLAVENUM_SHIFT))&MAM_MAXCFG_SLAVENUM_MASK)

/* MAXCFG Reg Mask */

#define MAM_MAXCFG_MASK                0xFF00FF00u



/* BSTCR Bit Fields */

#define MAM_BSTCR_INCRBREAK3_MASK      0xC0u

#define MAM_BSTCR_INCRBREAK3_SHIFT     6u

#define MAM_BSTCR_INCRBREAK3_WIDTH     2u

#define MAM_BSTCR_INCRBREAK3(x)        (((uint32_t)(((uint32_t)(x))<<MAM_BSTCR_INCRBREAK3_SHIFT))&MAM_BSTCR_INCRBREAK3_MASK)

#define MAM_BSTCR_INCRBREAK2_MASK      0x30u

#define MAM_BSTCR_INCRBREAK2_SHIFT     4u

#define MAM_BSTCR_INCRBREAK2_WIDTH     2u

#define MAM_BSTCR_INCRBREAK2(x)        (((uint32_t)(((uint32_t)(x))<<MAM_BSTCR_INCRBREAK2_SHIFT))&MAM_BSTCR_INCRBREAK2_MASK)

#define MAM_BSTCR_INCRBREAK1_MASK      0xCu

#define MAM_BSTCR_INCRBREAK1_SHIFT     2u

#define MAM_BSTCR_INCRBREAK1_WIDTH     2u

#define MAM_BSTCR_INCRBREAK1(x)        (((uint32_t)(((uint32_t)(x))<<MAM_BSTCR_INCRBREAK1_SHIFT))&MAM_BSTCR_INCRBREAK1_MASK)

#define MAM_BSTCR_INCRBREAK0_MASK      0x3u

#define MAM_BSTCR_INCRBREAK0_SHIFT     0u

#define MAM_BSTCR_INCRBREAK0_WIDTH     2u

#define MAM_BSTCR_INCRBREAK0(x)        (((uint32_t)(((uint32_t)(x))<<MAM_BSTCR_INCRBREAK0_SHIFT))&MAM_BSTCR_INCRBREAK0_MASK)

/* BSTCR Reg Mask */

#define MAM_BSTCR_MASK                 0x000000FFu



/* WDGCR Bit Fields */

#define MAM_WDGCR_WDOGSTATUS3_MASK     0x80000u

#define MAM_WDGCR_WDOGSTATUS3_SHIFT    19u

#define MAM_WDGCR_WDOGSTATUS3_WIDTH    1u

#define MAM_WDGCR_WDOGSTATUS3(x)       (((uint32_t)(((uint32_t)(x))<<MAM_WDGCR_WDOGSTATUS3_SHIFT))&MAM_WDGCR_WDOGSTATUS3_MASK)

#define MAM_WDGCR_WDOGSTATUS2_MASK     0x40000u

#define MAM_WDGCR_WDOGSTATUS2_SHIFT    18u

#define MAM_WDGCR_WDOGSTATUS2_WIDTH    1u

#define MAM_WDGCR_WDOGSTATUS2(x)       (((uint32_t)(((uint32_t)(x))<<MAM_WDGCR_WDOGSTATUS2_SHIFT))&MAM_WDGCR_WDOGSTATUS2_MASK)

#define MAM_WDGCR_WDOGSTATUS1_MASK     0x20000u

#define MAM_WDGCR_WDOGSTATUS1_SHIFT    17u

#define MAM_WDGCR_WDOGSTATUS1_WIDTH    1u

#define MAM_WDGCR_WDOGSTATUS1(x)       (((uint32_t)(((uint32_t)(x))<<MAM_WDGCR_WDOGSTATUS1_SHIFT))&MAM_WDGCR_WDOGSTATUS1_MASK)

#define MAM_WDGCR_WDOGSTATUS0_MASK     0x10000u

#define MAM_WDGCR_WDOGSTATUS0_SHIFT    16u

#define MAM_WDGCR_WDOGSTATUS0_WIDTH    1u

#define MAM_WDGCR_WDOGSTATUS0(x)       (((uint32_t)(((uint32_t)(x))<<MAM_WDGCR_WDOGSTATUS0_SHIFT))&MAM_WDGCR_WDOGSTATUS0_MASK)

#define MAM_WDGCR_WDOGCTRL3_MASK       0x8u

#define MAM_WDGCR_WDOGCTRL3_SHIFT      3u

#define MAM_WDGCR_WDOGCTRL3_WIDTH      1u

#define MAM_WDGCR_WDOGCTRL3(x)         (((uint32_t)(((uint32_t)(x))<<MAM_WDGCR_WDOGCTRL3_SHIFT))&MAM_WDGCR_WDOGCTRL3_MASK)

#define MAM_WDGCR_WDOGCTRL2_MASK       0x4u

#define MAM_WDGCR_WDOGCTRL2_SHIFT      2u

#define MAM_WDGCR_WDOGCTRL2_WIDTH      1u

#define MAM_WDGCR_WDOGCTRL2(x)         (((uint32_t)(((uint32_t)(x))<<MAM_WDGCR_WDOGCTRL2_SHIFT))&MAM_WDGCR_WDOGCTRL2_MASK)

#define MAM_WDGCR_WDOGCTRL1_MASK       0x2u

#define MAM_WDGCR_WDOGCTRL1_SHIFT      1u

#define MAM_WDGCR_WDOGCTRL1_WIDTH      1u

#define MAM_WDGCR_WDOGCTRL1(x)         (((uint32_t)(((uint32_t)(x))<<MAM_WDGCR_WDOGCTRL1_SHIFT))&MAM_WDGCR_WDOGCTRL1_MASK)

#define MAM_WDGCR_WDOGCTRL0_MASK       0x1u

#define MAM_WDGCR_WDOGCTRL0_SHIFT      0u

#define MAM_WDGCR_WDOGCTRL0_WIDTH      1u

#define MAM_WDGCR_WDOGCTRL0(x)         (((uint32_t)(((uint32_t)(x))<<MAM_WDGCR_WDOGCTRL0_SHIFT))&MAM_WDGCR_WDOGCTRL0_MASK)

/* WDGCR Reg Mask */

#define MAM_WDGCR_MASK                 0x000F000Fu



/* TOCR Bit Fields */

#define MAM_TOCR_TIMEOUTCTRL3_MASK     0xC0u

#define MAM_TOCR_TIMEOUTCTRL3_SHIFT    6u

#define MAM_TOCR_TIMEOUTCTRL3_WIDTH    2u

#define MAM_TOCR_TIMEOUTCTRL3(x)       (((uint32_t)(((uint32_t)(x))<<MAM_TOCR_TIMEOUTCTRL3_SHIFT))&MAM_TOCR_TIMEOUTCTRL3_MASK)

#define MAM_TOCR_TIMEOUTCTRL2_MASK     0x30u

#define MAM_TOCR_TIMEOUTCTRL2_SHIFT    4u

#define MAM_TOCR_TIMEOUTCTRL2_WIDTH    2u

#define MAM_TOCR_TIMEOUTCTRL2(x)       (((uint32_t)(((uint32_t)(x))<<MAM_TOCR_TIMEOUTCTRL2_SHIFT))&MAM_TOCR_TIMEOUTCTRL2_MASK)

#define MAM_TOCR_TIMEOUTCTRL1_MASK     0xCu

#define MAM_TOCR_TIMEOUTCTRL1_SHIFT    2u

#define MAM_TOCR_TIMEOUTCTRL1_WIDTH    2u

#define MAM_TOCR_TIMEOUTCTRL1(x)       (((uint32_t)(((uint32_t)(x))<<MAM_TOCR_TIMEOUTCTRL1_SHIFT))&MAM_TOCR_TIMEOUTCTRL1_MASK)

#define MAM_TOCR_TIMEOUTCTRL0_MASK     0x3u

#define MAM_TOCR_TIMEOUTCTRL0_SHIFT    0u

#define MAM_TOCR_TIMEOUTCTRL0_WIDTH    2u

#define MAM_TOCR_TIMEOUTCTRL0(x)       (((uint32_t)(((uint32_t)(x))<<MAM_TOCR_TIMEOUTCTRL0_SHIFT))&MAM_TOCR_TIMEOUTCTRL0_MASK)

/* TOCR Reg Mask */

#define MAM_TOCR_MASK                  0x000000FFu



/* WDGDIV Bit Fields */

#define MAM_WDGDIV_WDGDIVCTRL3_MASK    0xF000u

#define MAM_WDGDIV_WDGDIVCTRL3_SHIFT   12u

#define MAM_WDGDIV_WDGDIVCTRL3_WIDTH   4u

#define MAM_WDGDIV_WDGDIVCTRL3(x)      (((uint32_t)(((uint32_t)(x))<<MAM_WDGDIV_WDGDIVCTRL3_SHIFT))&MAM_WDGDIV_WDGDIVCTRL3_MASK)

#define MAM_WDGDIV_WDGDIVCTRL2_MASK    0xF00u

#define MAM_WDGDIV_WDGDIVCTRL2_SHIFT   8u

#define MAM_WDGDIV_WDGDIVCTRL2_WIDTH   4u

#define MAM_WDGDIV_WDGDIVCTRL2(x)      (((uint32_t)(((uint32_t)(x))<<MAM_WDGDIV_WDGDIVCTRL2_SHIFT))&MAM_WDGDIV_WDGDIVCTRL2_MASK)

#define MAM_WDGDIV_WDGDIVCTRL1_MASK    0xF0u

#define MAM_WDGDIV_WDGDIVCTRL1_SHIFT   4u

#define MAM_WDGDIV_WDGDIVCTRL1_WIDTH   4u

#define MAM_WDGDIV_WDGDIVCTRL1(x)      (((uint32_t)(((uint32_t)(x))<<MAM_WDGDIV_WDGDIVCTRL1_SHIFT))&MAM_WDGDIV_WDGDIVCTRL1_MASK)

#define MAM_WDGDIV_WDGDIVCTRL0_MASK    0xFu

#define MAM_WDGDIV_WDGDIVCTRL0_SHIFT   0u

#define MAM_WDGDIV_WDGDIVCTRL0_WIDTH   4u

#define MAM_WDGDIV_WDGDIVCTRL0(x)      (((uint32_t)(((uint32_t)(x))<<MAM_WDGDIV_WDGDIVCTRL0_SHIFT))&MAM_WDGDIV_WDGDIVCTRL0_MASK)

/* WDGDIV Reg Mask */

#define MAM_WDGDIV_MASK                0x0000FFFFu



/* ACLR Bit Fields */

#define MAM_ACLR_LOCKBLOCK31_MASK      0x80000000u

#define MAM_ACLR_LOCKBLOCK31_SHIFT     31u

#define MAM_ACLR_LOCKBLOCK31_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK31(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK31_SHIFT))&MAM_ACLR_LOCKBLOCK31_MASK)

#define MAM_ACLR_LOCKBLOCK30_MASK      0x40000000u

#define MAM_ACLR_LOCKBLOCK30_SHIFT     30u

#define MAM_ACLR_LOCKBLOCK30_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK30(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK30_SHIFT))&MAM_ACLR_LOCKBLOCK30_MASK)

#define MAM_ACLR_LOCKBLOCK29_MASK      0x20000000u

#define MAM_ACLR_LOCKBLOCK29_SHIFT     29u

#define MAM_ACLR_LOCKBLOCK29_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK29(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK29_SHIFT))&MAM_ACLR_LOCKBLOCK29_MASK)

#define MAM_ACLR_LOCKBLOCK28_MASK      0x10000000u

#define MAM_ACLR_LOCKBLOCK28_SHIFT     28u

#define MAM_ACLR_LOCKBLOCK28_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK28(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK28_SHIFT))&MAM_ACLR_LOCKBLOCK28_MASK)

#define MAM_ACLR_LOCKBLOCK27_MASK      0x8000000u

#define MAM_ACLR_LOCKBLOCK27_SHIFT     27u

#define MAM_ACLR_LOCKBLOCK27_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK27(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK27_SHIFT))&MAM_ACLR_LOCKBLOCK27_MASK)

#define MAM_ACLR_LOCKBLOCK26_MASK      0x4000000u

#define MAM_ACLR_LOCKBLOCK26_SHIFT     26u

#define MAM_ACLR_LOCKBLOCK26_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK26(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK26_SHIFT))&MAM_ACLR_LOCKBLOCK26_MASK)

#define MAM_ACLR_LOCKBLOCK25_MASK      0x2000000u

#define MAM_ACLR_LOCKBLOCK25_SHIFT     25u

#define MAM_ACLR_LOCKBLOCK25_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK25(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK25_SHIFT))&MAM_ACLR_LOCKBLOCK25_MASK)

#define MAM_ACLR_LOCKBLOCK24_MASK      0x1000000u

#define MAM_ACLR_LOCKBLOCK24_SHIFT     24u

#define MAM_ACLR_LOCKBLOCK24_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK24(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK24_SHIFT))&MAM_ACLR_LOCKBLOCK24_MASK)

#define MAM_ACLR_LOCKBLOCK23_MASK      0x800000u

#define MAM_ACLR_LOCKBLOCK23_SHIFT     23u

#define MAM_ACLR_LOCKBLOCK23_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK23(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK23_SHIFT))&MAM_ACLR_LOCKBLOCK23_MASK)

#define MAM_ACLR_LOCKBLOCK22_MASK      0x400000u

#define MAM_ACLR_LOCKBLOCK22_SHIFT     22u

#define MAM_ACLR_LOCKBLOCK22_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK22(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK22_SHIFT))&MAM_ACLR_LOCKBLOCK22_MASK)

#define MAM_ACLR_LOCKBLOCK21_MASK      0x200000u

#define MAM_ACLR_LOCKBLOCK21_SHIFT     21u

#define MAM_ACLR_LOCKBLOCK21_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK21(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK21_SHIFT))&MAM_ACLR_LOCKBLOCK21_MASK)

#define MAM_ACLR_LOCKBLOCK20_MASK      0x100000u

#define MAM_ACLR_LOCKBLOCK20_SHIFT     20u

#define MAM_ACLR_LOCKBLOCK20_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK20(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK20_SHIFT))&MAM_ACLR_LOCKBLOCK20_MASK)

#define MAM_ACLR_LOCKBLOCK19_MASK      0x80000u

#define MAM_ACLR_LOCKBLOCK19_SHIFT     19u

#define MAM_ACLR_LOCKBLOCK19_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK19(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK19_SHIFT))&MAM_ACLR_LOCKBLOCK19_MASK)

#define MAM_ACLR_LOCKBLOCK18_MASK      0x40000u

#define MAM_ACLR_LOCKBLOCK18_SHIFT     18u

#define MAM_ACLR_LOCKBLOCK18_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK18(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK18_SHIFT))&MAM_ACLR_LOCKBLOCK18_MASK)

#define MAM_ACLR_LOCKBLOCK17_MASK      0x20000u

#define MAM_ACLR_LOCKBLOCK17_SHIFT     17u

#define MAM_ACLR_LOCKBLOCK17_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK17(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK17_SHIFT))&MAM_ACLR_LOCKBLOCK17_MASK)

#define MAM_ACLR_LOCKBLOCK16_MASK      0x10000u

#define MAM_ACLR_LOCKBLOCK16_SHIFT     16u

#define MAM_ACLR_LOCKBLOCK16_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK16(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK16_SHIFT))&MAM_ACLR_LOCKBLOCK16_MASK)

#define MAM_ACLR_LOCKBLOCK15_MASK      0x8000u

#define MAM_ACLR_LOCKBLOCK15_SHIFT     15u

#define MAM_ACLR_LOCKBLOCK15_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK15(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK15_SHIFT))&MAM_ACLR_LOCKBLOCK15_MASK)

#define MAM_ACLR_LOCKBLOCK14_MASK      0x4000u

#define MAM_ACLR_LOCKBLOCK14_SHIFT     14u

#define MAM_ACLR_LOCKBLOCK14_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK14(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK14_SHIFT))&MAM_ACLR_LOCKBLOCK14_MASK)

#define MAM_ACLR_LOCKBLOCK13_MASK      0x2000u

#define MAM_ACLR_LOCKBLOCK13_SHIFT     13u

#define MAM_ACLR_LOCKBLOCK13_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK13(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK13_SHIFT))&MAM_ACLR_LOCKBLOCK13_MASK)

#define MAM_ACLR_LOCKBLOCK12_MASK      0x1000u

#define MAM_ACLR_LOCKBLOCK12_SHIFT     12u

#define MAM_ACLR_LOCKBLOCK12_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK12(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK12_SHIFT))&MAM_ACLR_LOCKBLOCK12_MASK)

#define MAM_ACLR_LOCKBLOCK11_MASK      0x800u

#define MAM_ACLR_LOCKBLOCK11_SHIFT     11u

#define MAM_ACLR_LOCKBLOCK11_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK11(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK11_SHIFT))&MAM_ACLR_LOCKBLOCK11_MASK)

#define MAM_ACLR_LOCKBLOCK10_MASK      0x400u

#define MAM_ACLR_LOCKBLOCK10_SHIFT     10u

#define MAM_ACLR_LOCKBLOCK10_WIDTH     1u

#define MAM_ACLR_LOCKBLOCK10(x)        (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK10_SHIFT))&MAM_ACLR_LOCKBLOCK10_MASK)

#define MAM_ACLR_LOCKBLOCK9_MASK       0x200u

#define MAM_ACLR_LOCKBLOCK9_SHIFT      9u

#define MAM_ACLR_LOCKBLOCK9_WIDTH      1u

#define MAM_ACLR_LOCKBLOCK9(x)         (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK9_SHIFT))&MAM_ACLR_LOCKBLOCK9_MASK)

#define MAM_ACLR_LOCKBLOCK8_MASK       0x100u

#define MAM_ACLR_LOCKBLOCK8_SHIFT      8u

#define MAM_ACLR_LOCKBLOCK8_WIDTH      1u

#define MAM_ACLR_LOCKBLOCK8(x)         (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK8_SHIFT))&MAM_ACLR_LOCKBLOCK8_MASK)

#define MAM_ACLR_LOCKBLOCK7_MASK       0x80u

#define MAM_ACLR_LOCKBLOCK7_SHIFT      7u

#define MAM_ACLR_LOCKBLOCK7_WIDTH      1u

#define MAM_ACLR_LOCKBLOCK7(x)         (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK7_SHIFT))&MAM_ACLR_LOCKBLOCK7_MASK)

#define MAM_ACLR_LOCKBLOCK6_MASK       0x40u

#define MAM_ACLR_LOCKBLOCK6_SHIFT      6u

#define MAM_ACLR_LOCKBLOCK6_WIDTH      1u

#define MAM_ACLR_LOCKBLOCK6(x)         (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK6_SHIFT))&MAM_ACLR_LOCKBLOCK6_MASK)

#define MAM_ACLR_LOCKBLOCK5_MASK       0x20u

#define MAM_ACLR_LOCKBLOCK5_SHIFT      5u

#define MAM_ACLR_LOCKBLOCK5_WIDTH      1u

#define MAM_ACLR_LOCKBLOCK5(x)         (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK5_SHIFT))&MAM_ACLR_LOCKBLOCK5_MASK)

#define MAM_ACLR_LOCKBLOCK4_MASK       0x10u

#define MAM_ACLR_LOCKBLOCK4_SHIFT      4u

#define MAM_ACLR_LOCKBLOCK4_WIDTH      1u

#define MAM_ACLR_LOCKBLOCK4(x)         (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK4_SHIFT))&MAM_ACLR_LOCKBLOCK4_MASK)

#define MAM_ACLR_LOCKBLOCK3_MASK       0x8u

#define MAM_ACLR_LOCKBLOCK3_SHIFT      3u

#define MAM_ACLR_LOCKBLOCK3_WIDTH      1u

#define MAM_ACLR_LOCKBLOCK3(x)         (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK3_SHIFT))&MAM_ACLR_LOCKBLOCK3_MASK)

#define MAM_ACLR_LOCKBLOCK2_MASK       0x4u

#define MAM_ACLR_LOCKBLOCK2_SHIFT      2u

#define MAM_ACLR_LOCKBLOCK2_WIDTH      1u

#define MAM_ACLR_LOCKBLOCK2(x)         (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK2_SHIFT))&MAM_ACLR_LOCKBLOCK2_MASK)

#define MAM_ACLR_LOCKBLOCK1_MASK       0x2u

#define MAM_ACLR_LOCKBLOCK1_SHIFT      1u

#define MAM_ACLR_LOCKBLOCK1_WIDTH      1u

#define MAM_ACLR_LOCKBLOCK1(x)         (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK1_SHIFT))&MAM_ACLR_LOCKBLOCK1_MASK)

#define MAM_ACLR_LOCKBLOCK0_MASK       0x1u

#define MAM_ACLR_LOCKBLOCK0_SHIFT      0u

#define MAM_ACLR_LOCKBLOCK0_WIDTH      1u

#define MAM_ACLR_LOCKBLOCK0(x)         (((uint32_t)(((uint32_t)(x))<<MAM_ACLR_LOCKBLOCK0_SHIFT))&MAM_ACLR_LOCKBLOCK0_MASK)

/* ACLR0 Reg Mask */

#define MAM_ACLR_MASK                  0xFFFFFFFFu



/* ACR Bit Fields */

#define MAM_ACR_ACCPOLICY7_MASK        0xF0000000u

#define MAM_ACR_ACCPOLICY7_SHIFT       28u

#define MAM_ACR_ACCPOLICY7_WIDTH       4u

#define MAM_ACR_ACCPOLICY7(x)          (((uint32_t)(((uint32_t)(x))<<MAM_ACR_ACCPOLICY7_SHIFT))&MAM_ACR_ACCPOLICY7_MASK)

#define MAM_ACR_ACCPOLICY6_MASK        0xF000000u

#define MAM_ACR_ACCPOLICY6_SHIFT       24u

#define MAM_ACR_ACCPOLICY6_WIDTH       4u

#define MAM_ACR_ACCPOLICY6(x)          (((uint32_t)(((uint32_t)(x))<<MAM_ACR_ACCPOLICY6_SHIFT))&MAM_ACR_ACCPOLICY6_MASK)

#define MAM_ACR_ACCPOLICY5_MASK        0xF00000u

#define MAM_ACR_ACCPOLICY5_SHIFT       20u

#define MAM_ACR_ACCPOLICY5_WIDTH       4u

#define MAM_ACR_ACCPOLICY5(x)          (((uint32_t)(((uint32_t)(x))<<MAM_ACR_ACCPOLICY5_SHIFT))&MAM_ACR_ACCPOLICY5_MASK)

#define MAM_ACR_ACCPOLICY4_MASK        0xF0000u

#define MAM_ACR_ACCPOLICY4_SHIFT       16u

#define MAM_ACR_ACCPOLICY4_WIDTH       4u

#define MAM_ACR_ACCPOLICY4(x)          (((uint32_t)(((uint32_t)(x))<<MAM_ACR_ACCPOLICY4_SHIFT))&MAM_ACR_ACCPOLICY4_MASK)

#define MAM_ACR_ACCPOLICY3_MASK        0xF000u

#define MAM_ACR_ACCPOLICY3_SHIFT       12u

#define MAM_ACR_ACCPOLICY3_WIDTH       4u

#define MAM_ACR_ACCPOLICY3(x)          (((uint32_t)(((uint32_t)(x))<<MAM_ACR_ACCPOLICY3_SHIFT))&MAM_ACR_ACCPOLICY3_MASK)

#define MAM_ACR_ACCPOLICY2_MASK        0xF00u

#define MAM_ACR_ACCPOLICY2_SHIFT       8u

#define MAM_ACR_ACCPOLICY2_WIDTH       4u

#define MAM_ACR_ACCPOLICY2(x)          (((uint32_t)(((uint32_t)(x))<<MAM_ACR_ACCPOLICY2_SHIFT))&MAM_ACR_ACCPOLICY2_MASK)

#define MAM_ACR_ACCPOLICY1_MASK        0xF0u

#define MAM_ACR_ACCPOLICY1_SHIFT       4u

#define MAM_ACR_ACCPOLICY1_WIDTH       4u

#define MAM_ACR_ACCPOLICY1(x)          (((uint32_t)(((uint32_t)(x))<<MAM_ACR_ACCPOLICY1_SHIFT))&MAM_ACR_ACCPOLICY1_MASK)

#define MAM_ACR_ACCPOLICY0_MASK        0xFu

#define MAM_ACR_ACCPOLICY0_SHIFT       0u

#define MAM_ACR_ACCPOLICY0_WIDTH       4u

#define MAM_ACR_ACCPOLICY0(x)          (((uint32_t)(((uint32_t)(x))<<MAM_ACR_ACCPOLICY0_SHIFT))&MAM_ACR_ACCPOLICY0_MASK)

/* ACR0 Reg Mask */

#define MAM_ACR_MASK                   0xFFFFFFFFu





/*!

 * @}

 */ /* end of group MAM_Register_Masks */



/*!

 * @}

 */ /* end of group MAM_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
