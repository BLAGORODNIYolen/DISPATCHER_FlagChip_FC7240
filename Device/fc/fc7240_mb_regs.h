#ifndef _FC7240_MB_NU_Tztufn18_REGS_H_
#define _FC7240_MB_NU_Tztufn18_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- MB Peripheral Access Layer

   ---------------------------------------------------------------------------- */

#define MB_CHANNEL_CONFIG_COUNT			4
#define MB_INT_CONFIG_COUNT				2

/*!

 * @addtogroup MB_Peripheral_Access_Layer MB Peripheral Access Layer

 * @{

 */



/** MB - Size of Registers Arrays */



/** MB - Register Layout Typedef */



typedef struct {


	struct
	{
		__I  uint32_t MB_CCn_SEMA                      ; /* Communication Channel Smeaphore Register, offset: 0x0 */

		__IO uint32_t MB_CCn_SEMA_UNLK                 ; /* Communication Channel Smeaphore Unlock Register, offset: 0x4 */

		__O  uint32_t MB_CCn_REQUEST                   ; /* Communication Channel Request Register, offset: 0x8 */

		__IO uint32_t MB_CCn_DONE                      ; /* Communication Channel Done Register, offset: 0xc */

		__IO uint32_t MB_CCn_DONE_MASK                 ; /* Communication Channel Done Mask Register, offset: 0x10 */

		__IO uint32_t MB_CCn_DATA0                     ; /* Communication Channel Data Register0, offset: 0x14 */

		__IO uint32_t MB_CCn_DATA1                     ; /* Communication Channel Data Register1, offset: 0x18 */

		__I  uint32_t MB_CCn_STAT                      ; /* Communication Channel Status Register, offset: 0x1c */

		__O  uint32_t MB_CCn_CLR                       ; /* Communication Channel Clear Register, offset: 0x20 */

		uint8_t  RESERVED_0[12];
	} CHANNEL[MB_CHANNEL_CONFIG_COUNT];

	uint8_t  RESERVED_15[1856];

	struct
	{
		__IO uint32_t MB_INTn_FLG                      ; /* Interrupt Channel Flag Register, offset: 0x800 */

		__IO uint32_t MB_INTn_FLG_MASK                 ; /* Interrupt Channel Flag Mask Register, offset: 0x804 */

		__IO uint32_t MB_INTn_INTEN                    ; /* Interrupt Channel Interrupt Enable Register, offset: 0x808 */

		__I  uint32_t MB_INTn_FLG_STAT                 ; /* Interrupt Channel Flag Status Register, offset: 0x80c */

		__IO uint32_t MB_INTn_CTRL                     ; /* Interrupt Channel Control Register, offset: 0x810 */

		uint8_t  RESERVED_2[12];
	} INTR[MB_INT_CONFIG_COUNT];
} MB_Type, *MB_MemMapPtr;



/** Number of instances of the MB module. */

#define MB_INSTANCE_COUNT                        (1u)



/* MB - Peripheral instance base addresses */

/** Peripheral MB base address */

#define MB_BASE                                  (0x40058000u)

/** Peripheral MB base pointer */

#define MB                                       ((MB_Type *)MB_BASE)

/** Array initializer of MB peripheral base addresses */

#define MB_BASE_ADDRS                            {MB_BASE}

/** Array initializer of MB peripheral base pointers */

#define MB_BASE_PTRS                             {MB}

// need fill by yourself

///** Number of interrupt vector arrays for the MB module. */

//#define MB_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the MB module. */

//#define MB_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the MB peripheral type */

//#define MB_IRQS                                  {MB_IRQn}





/* ----------------------------------------------------------------------------

   -- MB Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup MB_Register_Masks MB Register Masks

 * @{

 */



/* CCn_SEMA Bit Fields */

#define MB_CCn_SEMA_LOCK_MASK          0x80000000u

#define MB_CCn_SEMA_LOCK_SHIFT         31u

#define MB_CCn_SEMA_LOCK_WIDTH         1u

#define MB_CCn_SEMA_LOCK(x)            (((uint32_t)(((uint32_t)(x))<<MB_CCn_SEMA_LOCK_SHIFT))&MB_CCn_SEMA_LOCK_MASK)

#define MB_CCn_SEMA_LOCK_MASTER_ID_MASK 0xF0u

#define MB_CCn_SEMA_LOCK_MASTER_ID_SHIFT 4u

#define MB_CCn_SEMA_LOCK_MASTER_ID_WIDTH 4u

#define MB_CCn_SEMA_LOCK_MASTER_ID(x)  (((uint32_t)(((uint32_t)(x))<<MB_CCn_SEMA_LOCK_MASTER_ID_SHIFT))&MB_CCn_SEMA_LOCK_MASTER_ID_MASK)

#define MB_CCn_SEMA_LOCK_MASTER_SEC_MASK 0x2u

#define MB_CCn_SEMA_LOCK_MASTER_SEC_SHIFT 1u

#define MB_CCn_SEMA_LOCK_MASTER_SEC_WIDTH 1u

#define MB_CCn_SEMA_LOCK_MASTER_SEC(x) (((uint32_t)(((uint32_t)(x))<<MB_CCn_SEMA_LOCK_MASTER_SEC_SHIFT))&MB_CCn_SEMA_LOCK_MASTER_SEC_MASK)

#define MB_CCn_SEMA_LOCK_MASTER_SUPERVISOR_MASK 0x1u

#define MB_CCn_SEMA_LOCK_MASTER_SUPERVISOR_SHIFT 0u

#define MB_CCn_SEMA_LOCK_MASTER_SUPERVISOR_WIDTH 1u

#define MB_CCn_SEMA_LOCK_MASTER_SUPERVISOR(x) (((uint32_t)(((uint32_t)(x))<<MB_CCn_SEMA_LOCK_MASTER_SUPERVISOR_SHIFT))&MB_CCn_SEMA_LOCK_MASTER_SUPERVISOR_MASK)

/* CC0_SEMA Reg Mask */

#define MB_CCn_SEMA_MASK               0x800000F3u



/* CCn_SEMA_UNLK Bit Fields */

#define MB_CCn_SEMA_UNLK_AUTO_CLEAR_EN_MASK 0x3u

#define MB_CCn_SEMA_UNLK_AUTO_CLEAR_EN_SHIFT 0u

#define MB_CCn_SEMA_UNLK_AUTO_CLEAR_EN_WIDTH 2u

#define MB_CCn_SEMA_UNLK_AUTO_CLEAR_EN(x) (((uint32_t)(((uint32_t)(x))<<MB_CCn_SEMA_UNLK_AUTO_CLEAR_EN_SHIFT))&MB_CCn_SEMA_UNLK_AUTO_CLEAR_EN_MASK)

/* CCn_REQUEST Bit Fields */

#define MB_CCn_REQUEST_REQ_MASK       		0x3u

#define MB_CCn_REQUEST_REQ_SHIFT      		0u

#define MB_CCn_REQUEST_REQ_WIDTH      		2u

#define MB_CCn_REQUEST_REQ(x)         		(((uint32_t)(((uint32_t)(x))<<MB_CCn_REQUEST_REQ_SHIFT))&MB_CCn_REQUEST_REQ_MASK)


/* CCn_DONE Bit Fields */
#define MB_CCn_DONE_DONE_MASK         		0x3u

#define MB_CCn_DONE_DONE_SHIFT        		0u

#define MB_CCn_DONE_DONE_WIDTH        		2u

#define MB_CCn_DONE_DONE(x)           		(((uint32_t)(((uint32_t)(x))<<MB_CCn_DONE_DONE_SHIFT))&MB_CCn_DONE_DONE_MASK)


/* CCn_DONE_MASK Bit Fields */

#define MB_CCn_DONE_MASK_DONE_MASTER_ID_MASK 0xF0000u

#define MB_CCn_DONE_MASK_DONE_MASTER_ID_SHIFT 16u

#define MB_CCn_DONE_MASK_DONE_MASTER_ID_WIDTH 4u

#define MB_CCn_DONE_MASK_DONE_MASTER_ID(x) (((uint32_t)(((uint32_t)(x))<<MB_CCn_DONE_MASK_DONE_MASTER_ID_SHIFT))&MB_CCn_DONE_MASK_DONE_MASTER_ID_MASK)

#define MB_CCn_DONE_MASK_DONE_MASK_MASK 0x3u

#define MB_CCn_DONE_MASK_DONE_MASK_SHIFT 0u

#define MB_CCn_DONE_MASK_DONE_MASK_WIDTH 2u

#define MB_CCn_DONE_MASK_DONE_MASK(x) 	(((uint32_t)(((uint32_t)(x))<<MB_CCn_DONE_MASK_DONE_MASK_SHIFT))&MB_CCn_DONE_MASK_DONE_MASK_MASK)

/* CC0_DONE_MASK Reg Mask */

#define MB_CCn_DONE_MASK_MASK          0x000F0003u



/* CCn_DATA0 Bit Fields */

#define MB_CCn_DATA0_DATA0_MASK        0xFFFFFFFFu

#define MB_CCn_DATA0_DATA0_SHIFT       0u

#define MB_CCn_DATA0_DATA0_WIDTH       32u

#define MB_CCn_DATA0_DATA0(x)          (((uint32_t)(((uint32_t)(x))<<MB_CCn_DATA0_DATA0_SHIFT))&MB_CCn_DATA0_DATA0_MASK)

/* CC0_DATA0 Reg Mask */

#define MB_CCn_DATA0_MASK              0xFFFFFFFFu



/* CCn_DATA1 Bit Fields */

#define MB_CCn_DATA1_DATA1_MASK        0xFFFFFFFFu

#define MB_CCn_DATA1_DATA1_SHIFT       0u

#define MB_CCn_DATA1_DATA1_WIDTH       32u

#define MB_CCn_DATA1_DATA1(x)          (((uint32_t)(((uint32_t)(x))<<MB_CCn_DATA1_DATA1_SHIFT))&MB_CCn_DATA1_DATA1_MASK)

/* CC0_DATA1 Reg Mask */

#define MB_CCn_DATA1_MASK              0xFFFFFFFFu



/* CCn_STAT Bit Fields */

#define MB_CCn_STAT_CURRENT_LOCK_STATUS_MASK 0x80000000u

#define MB_CCn_STAT_CURRENT_LOCK_STATUS_SHIFT 31u

#define MB_CCn_STAT_CURRENT_LOCK_STATUS_WIDTH 1u

#define MB_CCn_STAT_CURRENT_LOCK_STATUS(x) (((uint32_t)(((uint32_t)(x))<<MB_CCn_STAT_CURRENT_LOCK_STATUS_SHIFT))&MB_CCn_STAT_CURRENT_LOCK_STATUS_MASK)

#define MB_CCn_STAT_CURRENT_CPU_STATUS_MASK 0xFFFF00u

#define MB_CCn_STAT_CURRENT_CPU_STATUS_SHIFT 8u

#define MB_CCn_STAT_CURRENT_CPU_STATUS_WIDTH 16u

#define MB_CCn_STAT_CURRENT_CPU_STATUS(x) (((uint32_t)(((uint32_t)(x))<<MB_CCn_STAT_CURRENT_CPU_STATUS_SHIFT))&MB_CCn_STAT_CURRENT_CPU_STATUS_MASK)

#define MB_CCn_STAT_CURRENT_LOCK_MASTER_ID_MASK 0xF0u

#define MB_CCn_STAT_CURRENT_LOCK_MASTER_ID_SHIFT 4u

#define MB_CCn_STAT_CURRENT_LOCK_MASTER_ID_WIDTH 4u

#define MB_CCn_STAT_CURRENT_LOCK_MASTER_ID(x) (((uint32_t)(((uint32_t)(x))<<MB_CCn_STAT_CURRENT_LOCK_MASTER_ID_SHIFT))&MB_CCn_STAT_CURRENT_LOCK_MASTER_ID_MASK)

#define MB_CCn_STAT_CURRENT_LOCK_MASTER_SEC_MASK 0x2u

#define MB_CCn_STAT_CURRENT_LOCK_MASTER_SEC_SHIFT 1u

#define MB_CCn_STAT_CURRENT_LOCK_MASTER_SEC_WIDTH 1u

#define MB_CCn_STAT_CURRENT_LOCK_MASTER_SEC(x) (((uint32_t)(((uint32_t)(x))<<MB_CCn_STAT_CURRENT_LOCK_MASTER_SEC_SHIFT))&MB_CCn_STAT_CURRENT_LOCK_MASTER_SEC_MASK)

#define MB_CCn_STAT_CURRENT_LOCK_MASTER_SUPERVISOR_MASK 0x1u

#define MB_CCn_STAT_CURRENT_LOCK_MASTER_SUPERVISOR_SHIFT 0u

#define MB_CCn_STAT_CURRENT_LOCK_MASTER_SUPERVISOR_WIDTH 1u

#define MB_CCn_STAT_CURRENT_LOCK_MASTER_SUPERVISOR(x) (((uint32_t)(((uint32_t)(x))<<MB_CCn_STAT_CURRENT_LOCK_MASTER_SUPERVISOR_SHIFT))&MB_CCn_STAT_CURRENT_LOCK_MASTER_SUPERVISOR_MASK)

/* CC0_STAT Reg Mask */

#define MB_CCn_STAT_MASK               0x80FFFFF3u



/* CCn_CLR Bit Fields */

#define MB_CCn_CLR_SOFTWARE_CLEAR_LOCK_MASK 0xFFFFFFFFu

#define MB_CCn_CLR_SOFTWARE_CLEAR_LOCK_SHIFT 0u

#define MB_CCn_CLR_SOFTWARE_CLEAR_LOCK_WIDTH 32u

#define MB_CCn_CLR_SOFTWARE_CLEAR_LOCK(x) (((uint32_t)(((uint32_t)(x))<<MB_CCn_CLR_SOFTWARE_CLEAR_LOCK_SHIFT))&MB_CCn_CLR_SOFTWARE_CLEAR_LOCK_MASK)

/* CC0_CLR Reg Mask */

#define MB_CCn_CLR_MASK                0xFFFFFFFFu



/* INTn_FLG Bit Fields */

#define MB_INTn_FLG_DONE_FLAG_MASK     0xF0000u

#define MB_INTn_FLG_DONE_FLAG_SHIFT    16u

#define MB_INTn_FLG_DONE_FLAG_WIDTH    4u

#define MB_INTn_FLG_DONE_FLAG(x)       (((uint32_t)(((uint32_t)(x))<<MB_INTn_FLG_DONE_FLAG_SHIFT))&MB_INTn_FLG_DONE_FLAG_MASK)

#define MB_INTn_FLG_REQ_FLAG_MASK      0xFu

#define MB_INTn_FLG_REQ_FLAG_SHIFT     0u

#define MB_INTn_FLG_REQ_FLAG_WIDTH     4u

#define MB_INTn_FLG_REQ_FLAG(x)        (((uint32_t)(((uint32_t)(x))<<MB_INTn_FLG_REQ_FLAG_SHIFT))&MB_INTn_FLG_REQ_FLAG_MASK)

/* INTn_FLG_MASK Bit Fields */

#define MB_INTn_FLG_MASK_DONE_FLAG_MASK_MASK 0xF0000u

#define MB_INTn_FLG_MASK_DONE_FLAG_MASK_SHIFT 16u

#define MB_INTn_FLG_MASK_DONE_FLAG_MASK_WIDTH 4u

#define MB_INTn_FLG_MASK_DONE_FLAG_MASK(x) (((uint32_t)(((uint32_t)(x))<<MB_INTn_FLG_MASK_DONE_FLAG_MASK_SHIFT))&MB_INTn_FLG_MASK_DONE_FLAG_MASK_MASK)

#define MB_INTn_FLG_MASK_REQ_FLAG_MASK_MASK 0xFu

#define MB_INTn_FLG_MASK_REQ_FLAG_MASK_SHIFT 0u

#define MB_INTn_FLG_MASK_REQ_FLAG_MASK_WIDTH 4u

#define MB_INTn_FLG_MASK_REQ_FLAG_MASK(x) (((uint32_t)(((uint32_t)(x))<<MB_INTn_FLG_MASK_REQ_FLAG_MASK_SHIFT))&MB_INTn_FLG_MASK_REQ_FLAG_MASK_MASK)

/* INT0_FLG_MASK Reg Mask */

#define MB_INTn_FLG_MASK_MASK          0x000F000Fu



/* INTn_INTEN Bit Fields */

#define MB_INTn_INTEN_DONE_INT_EN_MASK 0xF0000u

#define MB_INTn_INTEN_DONE_INT_EN_SHIFT 16u

#define MB_INTn_INTEN_DONE_INT_EN_WIDTH 4u

#define MB_INTn_INTEN_DONE_INT_EN(x)   (((uint32_t)(((uint32_t)(x))<<MB_INTn_INTEN_DONE_INT_EN_SHIFT))&MB_INTn_INTEN_DONE_INT_EN_MASK)

#define MB_INTn_INTEN_REQ_INT_EN_MASK  0xFu

#define MB_INTn_INTEN_REQ_INT_EN_SHIFT 0u

#define MB_INTn_INTEN_REQ_INT_EN_WIDTH 4u

#define MB_INTn_INTEN_REQ_INT_EN(x)    (((uint32_t)(((uint32_t)(x))<<MB_INTn_INTEN_REQ_INT_EN_SHIFT))&MB_INTn_INTEN_REQ_INT_EN_MASK)

/* INT0_INTEN Reg Mask */

#define MB_INTn_INTEN_MASK             0x000F000Fu



/* INTn_FLG_STAT Bit Fields */

#define MB_INTn_FLG_STAT_FLG_DONE_INT_STAT_MASK 0xF0000u

#define MB_INTn_FLG_STAT_FLG_DONE_INT_STAT_SHIFT 16u

#define MB_INTn_FLG_STAT_FLG_DONE_INT_STAT_WIDTH 4u

#define MB_INTn_FLG_STAT_FLG_DONE_INT_STAT(x) (((uint32_t)(((uint32_t)(x))<<MB_INTn_FLG_STAT_FLG_DONE_INT_STAT_SHIFT))&MB_INTn_FLG_STAT_FLG_DONE_INT_STAT_MASK)

#define MB_INTn_FLG_STAT_FLG_REQ_INT_STAT_MASK 0xFu

#define MB_INTn_FLG_STAT_FLG_REQ_INT_STAT_SHIFT 0u

#define MB_INTn_FLG_STAT_FLG_REQ_INT_STAT_WIDTH 4u

#define MB_INTn_FLG_STAT_FLG_REQ_INT_STAT(x) (((uint32_t)(((uint32_t)(x))<<MB_INTn_FLG_STAT_FLG_REQ_INT_STAT_SHIFT))&MB_INTn_FLG_STAT_FLG_REQ_INT_STAT_MASK)

/* INT0_FLG_STAT Reg Mask */

#define MB_INTn_FLG_STAT_MASK          0x000F000Fu



/* INTn_CTRL Bit Fields */

#define MB_INTn_CTRL_INTEN_LOCK_MASK   0x4u

#define MB_INTn_CTRL_INTEN_LOCK_SHIFT  2u

#define MB_INTn_CTRL_INTEN_LOCK_WIDTH  1u

#define MB_INTn_CTRL_INTEN_LOCK(x)     (((uint32_t)(((uint32_t)(x))<<MB_INTn_CTRL_INTEN_LOCK_SHIFT))&MB_INTn_CTRL_INTEN_LOCK_MASK)

#define MB_INTn_CTRL_FLG_MASK_LOCK_MASK 0x2u

#define MB_INTn_CTRL_FLG_MASK_LOCK_SHIFT 1u

#define MB_INTn_CTRL_FLG_MASK_LOCK_WIDTH 1u

#define MB_INTn_CTRL_FLG_MASK_LOCK(x)  (((uint32_t)(((uint32_t)(x))<<MB_INTn_CTRL_FLG_MASK_LOCK_SHIFT))&MB_INTn_CTRL_FLG_MASK_LOCK_MASK)

#define MB_INTn_CTRL_FLG_LOCK_MASK     0x1u

#define MB_INTn_CTRL_FLG_LOCK_SHIFT    0u

#define MB_INTn_CTRL_FLG_LOCK_WIDTH    1u

#define MB_INTn_CTRL_FLG_LOCK(x)       (((uint32_t)(((uint32_t)(x))<<MB_INTn_CTRL_FLG_LOCK_SHIFT))&MB_INTn_CTRL_FLG_LOCK_MASK)

/* INT0_CTRL Reg Mask */

#define MB_INTn_CTRL_MASK              0x00000007u



/* Channel master done code */
#define MB_MASTER_DONE_CODE                         0xFC730000u

/* force unlock channel */
#define MB_FORCE_UNLOCK_CODE                        0xFC350000u

/*!

 * @}

 */ /* end of group MB_Register_Masks */



/*!

 * @}

 */ /* end of group MB_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
