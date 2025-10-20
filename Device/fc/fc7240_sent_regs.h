#ifndef _FC7240_SENT_NU_Tztufn40_REGS_H_
#define _FC7240_SENT_NU_Tztufn40_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- SENT Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup SENT_Peripheral_Access_Layer SENT Peripheral Access Layer

 * @{

 */



/** SENT - Size of Registers Arrays */

#define SENT_CHANNEL_COUNT                       (4u)

/** SENT - Register Layout Typedef */

typedef struct {



  __IO uint32_t GLBL_CTL                      ; /* Global Control Register, offset: 0x0 */

  __IO uint32_t CHN_EN                        ; /* Channel Enable Register, offset: 0x4 */

  __IO uint32_t GLBL_STAT                     ; /* Global Status Register, offset: 0x8 */

  __IO uint32_t FMSG_STAT                     ; /* Fast Message Status Register, offset: 0xC */

  __IO uint32_t SMSG_STAT                     ; /* Slow Message Status Register, offset: 0x10 */

  __IO uint32_t FIFO_EN                       ; /* FIFO Enable Register, offset: 0x14 */

  __IO uint32_t DATA_NUM_CTL1                 ; /* Each Channel Data Number Control Register, offset: 0x18 */

       uint8_t  RESERVED_0[4];

  __IO uint32_t OVFL_UDFL_STAT                ; /* Fast Message FIFO Overflow DMA Underflow State Register, offset: 0x20 */

  __IO uint32_t NB_MODE1                      ; /* Channel Nibble Data Mode Control 1 Register, offset: 0x24 */

       uint8_t  RESERVED_1[4];

  __IO uint32_t FDMA_CTL                      ; /* Channel Fast Message DMA Control Register, offset: 0x2C */

  __IO uint32_t SDMA_CTL                      ; /* Channel Slow Message DMA Control Register, offset: 0x30 */

  __IO uint32_t FINT_CTL                      ; /* Channel Fast Message Interrupt Control Register, offset: 0x34 */

  __IO uint32_t SINT_CTL                      ; /* Channel Slow Message Interrupt Control Register, offset: 0x38 */

  struct
  {
 	  __IO uint32_t CHN_CLK_CTL                  ; /* Channel clock control register, offset: 0x3c */

 	  __IO uint32_t CHN_STAT                     ; /* Channel status register, offset: 0x40 */

 	  __IO uint32_t CHN_CTL                      ; /* Channel control register, offset: 0x44 */

 	  __I  uint32_t CHN_FDATA                    ; /* Channel received fast data nibble values, offset: 0x48 */

 	  __I  uint32_t CHN_FCRC                     ; /* Channel fast message CRC and status & communication value, offset: 0x4c */

 	  __I  uint32_t CHN_FTS                      ; /* Channel fast timestamp value, offset: 0x50 */

 	  __I  uint32_t CHN_SBIT3                   ; /* Channel slow message status & communication bit 3 received value, offset: 0x54 */

 	  __I  uint32_t CHN_SBIT2                   ; /* Channel slow message status & communication bit 2 received value, offset: 0x58 */

 	  __IO uint32_t CHN_STS                      ; /* Channel slow message timestamp value, offset: 0x5c */

 	  __IO uint32_t CHN_DFD                      ; /* Channel n DMA fast data, offset: 0x60 */

 	  __IO uint32_t CHN_DFC                      ; /* Channel n DMA fast crc data, offset: 0x64 */

 	  __IO uint32_t CHN_DFTS                     ; /* Channel n DMA fast timestamp, offset: 0x68 */

 	       uint8_t  RESERVED_2[4];

 	  __IO uint32_t CHN_DSB3                    ; /* Channel n DMA slow messgae bit3, offset: 0x70 */

 	  __IO uint32_t CHN_DSB2                    ; /* Channel n DMA slow messgae bit2, offset: 0x74 */

 	  __IO uint32_t CHN_DSTS                     ; /* Channel n DMA slow message timestamp, offset: 0x78 */

 	  __IO uint32_t CHN_TSTMP                    ; /* Channle n timestamp, offset: 0x7c */

 	  __IO uint32_t CHN_MCNT                     ; /* Channel n message counter, offset: 0x80 */

 	  __IO uint32_t CHN_SPC_CTL                  ; /* Channel n SPC mode control, offset: 0x84 */

 	  __IO uint32_t CHN_IDLE_CTL                 ; /* CHN_IDLE_CTL0, offset: 0x88 */
  }SENT_CHN[SENT_CHANNEL_COUNT];

} SENT_Type, *SENT_MemMapPtr;



/** Number of instances of the SENT module. */

#define SENT_INSTANCE_COUNT                      (1u)



/* SENT - Peripheral instance base addresses */

/** Peripheral SENT base address */

#define SENT_BASE                                (0x40054000u)

/** Peripheral SENT base pointer */

#define SENT                                     ((SENT_Type *)SENT_BASE)

/** Array initializer of SENT peripheral base addresses */

#define SENT_BASE_ADDRS                          {SENT_BASE}

/** Array initializer of SENT peripheral base pointers */

#define SENT_BASE_PTRS                           {SENT}

// need fill by yourself

///** Number of interrupt vector arrays for the SENT module. */

//#define SENT_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the SENT module. */

//#define SENT_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the SENT peripheral type */

//#define SENT_IRQS                                {SENT_IRQn}





/* ----------------------------------------------------------------------------

   -- SENT Register Masks

   ---------------------------------------------------------------------------- */



/*!

 * @addtogroup SENT_Register_Masks SENT Register Masks

 * @{

 */



/* GLBL_CTL Bit Fields */

#define SENT_GLBL_CTL_PRE_SCALER_MASK  0xFF000000u

#define SENT_GLBL_CTL_PRE_SCALER_SHIFT 24u

#define SENT_GLBL_CTL_PRE_SCALER_WIDTH 8u

#define SENT_GLBL_CTL_PRE_SCALER(x)    (((uint32_t)(((uint32_t)(x))<<SENT_GLBL_CTL_PRE_SCALER_SHIFT))&SENT_GLBL_CTL_PRE_SCALER_MASK)

#define SENT_GLBL_CTL_DMA_WATERMARK_MASK 0x1F0000u

#define SENT_GLBL_CTL_DMA_WATERMARK_SHIFT 16u

#define SENT_GLBL_CTL_DMA_WATERMARK_WIDTH 5u

#define SENT_GLBL_CTL_DMA_WATERMARK(x) (((uint32_t)(((uint32_t)(x))<<SENT_GLBL_CTL_DMA_WATERMARK_SHIFT))&SENT_GLBL_CTL_DMA_WATERMARK_MASK)

#define SENT_GLBL_CTL_F_FIFO_OVFL_IE_MASK 0x400u

#define SENT_GLBL_CTL_F_FIFO_OVFL_IE_SHIFT 10u

#define SENT_GLBL_CTL_F_FIFO_OVFL_IE_WIDTH 1u

#define SENT_GLBL_CTL_F_FIFO_OVFL_IE(x) (((uint32_t)(((uint32_t)(x))<<SENT_GLBL_CTL_F_FIFO_OVFL_IE_SHIFT))&SENT_GLBL_CTL_F_FIFO_OVFL_IE_MASK)

#define SENT_GLBL_CTL_F_DMA_UDFL_IE_MASK 0x200u

#define SENT_GLBL_CTL_F_DMA_UDFL_IE_SHIFT 9u

#define SENT_GLBL_CTL_F_DMA_UDFL_IE_WIDTH 1u

#define SENT_GLBL_CTL_F_DMA_UDFL_IE(x) (((uint32_t)(((uint32_t)(x))<<SENT_GLBL_CTL_F_DMA_UDFL_IE_SHIFT))&SENT_GLBL_CTL_F_DMA_UDFL_IE_MASK)

#define SENT_GLBL_CTL_S_DMA_UDFL_IE_MASK 0x100u

#define SENT_GLBL_CTL_S_DMA_UDFL_IE_SHIFT 8u

#define SENT_GLBL_CTL_S_DMA_UDFL_IE_WIDTH 1u

#define SENT_GLBL_CTL_S_DMA_UDFL_IE(x) (((uint32_t)(((uint32_t)(x))<<SENT_GLBL_CTL_S_DMA_UDFL_IE_SHIFT))&SENT_GLBL_CTL_S_DMA_UDFL_IE_MASK)

#define SENT_GLBL_CTL_FAST_CLR_MASK    0x10u

#define SENT_GLBL_CTL_FAST_CLR_SHIFT   4u

#define SENT_GLBL_CTL_FAST_CLR_WIDTH   1u

#define SENT_GLBL_CTL_FAST_CLR(x)      (((uint32_t)(((uint32_t)(x))<<SENT_GLBL_CTL_FAST_CLR_SHIFT))&SENT_GLBL_CTL_FAST_CLR_MASK)

#define SENT_GLBL_CTL_DBG_EN_MASK      0x4u

#define SENT_GLBL_CTL_DBG_EN_SHIFT     2u

#define SENT_GLBL_CTL_DBG_EN_WIDTH     1u

#define SENT_GLBL_CTL_DBG_EN(x)        (((uint32_t)(((uint32_t)(x))<<SENT_GLBL_CTL_DBG_EN_SHIFT))&SENT_GLBL_CTL_DBG_EN_MASK)

#define SENT_GLBL_CTL_SENT_EN_MASK     0x1u

#define SENT_GLBL_CTL_SENT_EN_SHIFT    0u

#define SENT_GLBL_CTL_SENT_EN_WIDTH    1u

#define SENT_GLBL_CTL_SENT_EN(x)       (((uint32_t)(((uint32_t)(x))<<SENT_GLBL_CTL_SENT_EN_SHIFT))&SENT_GLBL_CTL_SENT_EN_MASK)

/* GLBL_CTL Reg Mask */

#define SENT_GLBL_CTL_MASK             0xFF1F0715u



/* CHN_EN Bit Fields */

#define SENT_CHN_EN_CHN_EN_MASK        0xFu

#define SENT_CHN_EN_CHN_EN_SHIFT       0u

#define SENT_CHN_EN_CHN_EN_WIDTH       4u

#define SENT_CHN_EN_CHN_EN(x)          (((uint32_t)(((uint32_t)(x))<<SENT_CHN_EN_CHN_EN_SHIFT))&SENT_CHN_EN_CHN_EN_MASK)

/* CHN_EN Reg Mask */

#define SENT_CHN_EN_MASK               0x0000000Fu



/* GLBL_STAT Bit Fields */

#define SENT_GLBL_STAT_S_DMA_UDFL_MASK 0xFu

#define SENT_GLBL_STAT_S_DMA_UDFL_SHIFT 0u

#define SENT_GLBL_STAT_S_DMA_UDFL_WIDTH 4u

#define SENT_GLBL_STAT_S_DMA_UDFL(x)   (((uint32_t)(((uint32_t)(x))<<SENT_GLBL_STAT_S_DMA_UDFL_SHIFT))&SENT_GLBL_STAT_S_DMA_UDFL_MASK)

/* GLBL_STAT Reg Mask */

#define SENT_GLBL_STAT_MASK            0x0000000Fu



/* FMSG_STAT Bit Fields */

#define SENT_FMSG_STAT_F_MSG_RDY_MASK  0xFu

#define SENT_FMSG_STAT_F_MSG_RDY_SHIFT 0u

#define SENT_FMSG_STAT_F_MSG_RDY_WIDTH 4u

#define SENT_FMSG_STAT_F_MSG_RDY(x)    (((uint32_t)(((uint32_t)(x))<<SENT_FMSG_STAT_F_MSG_RDY_SHIFT))&SENT_FMSG_STAT_F_MSG_RDY_MASK)

/* FMSG_STAT Reg Mask */

#define SENT_FMSG_STAT_MASK            0x0000000Fu



/* SMSG_STAT Bit Fields */

#define SENT_SMSG_STAT_S_MSG_RDY_MASK  0xFu

#define SENT_SMSG_STAT_S_MSG_RDY_SHIFT 0u

#define SENT_SMSG_STAT_S_MSG_RDY_WIDTH 4u

#define SENT_SMSG_STAT_S_MSG_RDY(x)    (((uint32_t)(((uint32_t)(x))<<SENT_SMSG_STAT_S_MSG_RDY_SHIFT))&SENT_SMSG_STAT_S_MSG_RDY_MASK)

/* SMSG_STAT Reg Mask */

#define SENT_SMSG_STAT_MASK            0x0000000Fu



/* FIFO_EN Bit Fields */

#define SENT_FIFO_EN_FIFO_EN_MASK      0xFu

#define SENT_FIFO_EN_FIFO_EN_SHIFT     0u

#define SENT_FIFO_EN_FIFO_EN_WIDTH     4u

#define SENT_FIFO_EN_FIFO_EN(x)        (((uint32_t)(((uint32_t)(x))<<SENT_FIFO_EN_FIFO_EN_SHIFT))&SENT_FIFO_EN_FIFO_EN_MASK)

/* FIFO_EN Reg Mask */

#define SENT_FIFO_EN_MASK              0x0000000Fu



/* DATA_NUM_CTL1 Bit Fields */

#define SENT_DATA_NUM_CTL1_CH0_DATA_CTL_MASK 0x70000000u

#define SENT_DATA_NUM_CTL1_CH0_DATA_CTL_SHIFT 28u

#define SENT_DATA_NUM_CTL1_CH0_DATA_CTL_WIDTH 3u

#define SENT_DATA_NUM_CTL1_CH0_DATA_CTL(x) (((uint32_t)(((uint32_t)(x))<<SENT_DATA_NUM_CTL1_CH0_DATA_CTL_SHIFT))&SENT_DATA_NUM_CTL1_CH0_DATA_CTL_MASK)

#define SENT_DATA_NUM_CTL1_CH1_DATA_CTL_MASK 0x7000000u

#define SENT_DATA_NUM_CTL1_CH1_DATA_CTL_SHIFT 24u

#define SENT_DATA_NUM_CTL1_CH1_DATA_CTL_WIDTH 3u

#define SENT_DATA_NUM_CTL1_CH1_DATA_CTL(x) (((uint32_t)(((uint32_t)(x))<<SENT_DATA_NUM_CTL1_CH1_DATA_CTL_SHIFT))&SENT_DATA_NUM_CTL1_CH1_DATA_CTL_MASK)

#define SENT_DATA_NUM_CTL1_CH2_DATA_CTL_MASK 0x700000u

#define SENT_DATA_NUM_CTL1_CH2_DATA_CTL_SHIFT 20u

#define SENT_DATA_NUM_CTL1_CH2_DATA_CTL_WIDTH 3u

#define SENT_DATA_NUM_CTL1_CH2_DATA_CTL(x) (((uint32_t)(((uint32_t)(x))<<SENT_DATA_NUM_CTL1_CH2_DATA_CTL_SHIFT))&SENT_DATA_NUM_CTL1_CH2_DATA_CTL_MASK)

#define SENT_DATA_NUM_CTL1_CH3_DATA_CTL_MASK 0x70000u

#define SENT_DATA_NUM_CTL1_CH3_DATA_CTL_SHIFT 16u

#define SENT_DATA_NUM_CTL1_CH3_DATA_CTL_WIDTH 3u

#define SENT_DATA_NUM_CTL1_CH3_DATA_CTL(x) (((uint32_t)(((uint32_t)(x))<<SENT_DATA_NUM_CTL1_CH3_DATA_CTL_SHIFT))&SENT_DATA_NUM_CTL1_CH3_DATA_CTL_MASK)

/* DATA_NUM_CTL1 Reg Mask */

#define SENT_DATA_NUM_CTL1_MASK        0x77770000u



/* OVFL_UDFL_STAT Bit Fields */

#define SENT_OVFL_UDFL_STAT_FIFO_F_OVFL_FLAG_MASK 0xF0000u

#define SENT_OVFL_UDFL_STAT_FIFO_F_OVFL_FLAG_SHIFT 16u

#define SENT_OVFL_UDFL_STAT_FIFO_F_OVFL_FLAG_WIDTH 4u

#define SENT_OVFL_UDFL_STAT_FIFO_F_OVFL_FLAG(x) (((uint32_t)(((uint32_t)(x))<<SENT_OVFL_UDFL_STAT_FIFO_F_OVFL_FLAG_SHIFT))&SENT_OVFL_UDFL_STAT_FIFO_F_OVFL_FLAG_MASK)

#define SENT_OVFL_UDFL_STAT_DMA_F_UDFL_FLAG_MASK 0xFu

#define SENT_OVFL_UDFL_STAT_DMA_F_UDFL_FLAG_SHIFT 0u

#define SENT_OVFL_UDFL_STAT_DMA_F_UDFL_FLAG_WIDTH 4u

#define SENT_OVFL_UDFL_STAT_DMA_F_UDFL_FLAG(x) (((uint32_t)(((uint32_t)(x))<<SENT_OVFL_UDFL_STAT_DMA_F_UDFL_FLAG_SHIFT))&SENT_OVFL_UDFL_STAT_DMA_F_UDFL_FLAG_MASK)

/* OVFL_UDFL_STAT Reg Mask */

#define SENT_OVFL_UDFL_STAT_MASK       0x000F000Fu



/* NB_MODE1 Bit Fields */

#define SENT_NB_MODE1_CH0_NB_MODE_MASK 0xF0000000u

#define SENT_NB_MODE1_CH0_NB_MODE_SHIFT 28u

#define SENT_NB_MODE1_CH0_NB_MODE_WIDTH 4u

#define SENT_NB_MODE1_CH0_NB_MODE(x)   (((uint32_t)(((uint32_t)(x))<<SENT_NB_MODE1_CH0_NB_MODE_SHIFT))&SENT_NB_MODE1_CH0_NB_MODE_MASK)

#define SENT_NB_MODE1_CH1_NB_MODE_MASK 0xF000000u

#define SENT_NB_MODE1_CH1_NB_MODE_SHIFT 24u

#define SENT_NB_MODE1_CH1_NB_MODE_WIDTH 4u

#define SENT_NB_MODE1_CH1_NB_MODE(x)   (((uint32_t)(((uint32_t)(x))<<SENT_NB_MODE1_CH1_NB_MODE_SHIFT))&SENT_NB_MODE1_CH1_NB_MODE_MASK)

#define SENT_NB_MODE1_CH2_NB_MODE_MASK 0xF00000u

#define SENT_NB_MODE1_CH2_NB_MODE_SHIFT 20u

#define SENT_NB_MODE1_CH2_NB_MODE_WIDTH 4u

#define SENT_NB_MODE1_CH2_NB_MODE(x)   (((uint32_t)(((uint32_t)(x))<<SENT_NB_MODE1_CH2_NB_MODE_SHIFT))&SENT_NB_MODE1_CH2_NB_MODE_MASK)

#define SENT_NB_MODE1_CH3_NB_MODE_MASK 0xF0000u

#define SENT_NB_MODE1_CH3_NB_MODE_SHIFT 16u

#define SENT_NB_MODE1_CH3_NB_MODE_WIDTH 4u

#define SENT_NB_MODE1_CH3_NB_MODE(x)   (((uint32_t)(((uint32_t)(x))<<SENT_NB_MODE1_CH3_NB_MODE_SHIFT))&SENT_NB_MODE1_CH3_NB_MODE_MASK)

/* NB_MODE1 Reg Mask */

#define SENT_NB_MODE1_MASK             0xFFFF0000u



/* FDMA_CTL Bit Fields */

#define SENT_FDMA_CTL_FDMA_EN_MASK     0xFu

#define SENT_FDMA_CTL_FDMA_EN_SHIFT    0u

#define SENT_FDMA_CTL_FDMA_EN_WIDTH    4u

#define SENT_FDMA_CTL_FDMA_EN(x)       (((uint32_t)(((uint32_t)(x))<<SENT_FDMA_CTL_FDMA_EN_SHIFT))&SENT_FDMA_CTL_FDMA_EN_MASK)

/* FDMA_CTL Reg Mask */

#define SENT_FDMA_CTL_MASK             0x0000000Fu



/* SDMA_CTL Bit Fields */

#define SENT_SDMA_CTL_SDMA_EN_MASK     0xFu

#define SENT_SDMA_CTL_SDMA_EN_SHIFT    0u

#define SENT_SDMA_CTL_SDMA_EN_WIDTH    4u

#define SENT_SDMA_CTL_SDMA_EN(x)       (((uint32_t)(((uint32_t)(x))<<SENT_SDMA_CTL_SDMA_EN_SHIFT))&SENT_SDMA_CTL_SDMA_EN_MASK)

/* SDMA_CTL Reg Mask */

#define SENT_SDMA_CTL_MASK             0x0000000Fu



/* FINT_CTL Bit Fields */

#define SENT_FINT_CTL_FINT_CTL_MASK    0xFu

#define SENT_FINT_CTL_FINT_CTL_SHIFT   0u

#define SENT_FINT_CTL_FINT_CTL_WIDTH   4u

#define SENT_FINT_CTL_FINT_CTL(x)      (((uint32_t)(((uint32_t)(x))<<SENT_FINT_CTL_FINT_CTL_SHIFT))&SENT_FINT_CTL_FINT_CTL_MASK)

/* FINT_CTL Reg Mask */

#define SENT_FINT_CTL_MASK             0x0000000Fu



/* SINT_CTL Bit Fields */

#define SENT_SINT_CTL_SINT_CTL_MASK    0xFu

#define SENT_SINT_CTL_SINT_CTL_SHIFT   0u

#define SENT_SINT_CTL_SINT_CTL_WIDTH   4u

#define SENT_SINT_CTL_SINT_CTL(x)      (((uint32_t)(((uint32_t)(x))<<SENT_SINT_CTL_SINT_CTL_SHIFT))&SENT_SINT_CTL_SINT_CTL_MASK)

/* SINT_CTL Reg Mask */

#define SENT_SINT_CTL_MASK             0x0000000Fu



/* CHN_CLK_CTL Bit Fields */

#define SENT_CHN_CLK_CTL_COMPED_PRE_SCALER_MASK 0x7FFF0000u

#define SENT_CHN_CLK_CTL_COMPED_PRE_SCALER_SHIFT 16u

#define SENT_CHN_CLK_CTL_COMPED_PRE_SCALER_WIDTH 15u

#define SENT_CHN_CLK_CTL_COMPED_PRE_SCALER(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CLK_CTL_COMPED_PRE_SCALER_SHIFT))&SENT_CHN_CLK_CTL_COMPED_PRE_SCALER_MASK)

#define SENT_CHN_CLK_CTL_COMP_EN_MASK  0x8000u

#define SENT_CHN_CLK_CTL_COMP_EN_SHIFT 15u

#define SENT_CHN_CLK_CTL_COMP_EN_WIDTH 1u

#define SENT_CHN_CLK_CTL_COMP_EN(x)    (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CLK_CTL_COMP_EN_SHIFT))&SENT_CHN_CLK_CTL_COMP_EN_MASK)

#define SENT_CHN_CLK_CTL_PRE_SCALER_MASK 0x3FFFu

#define SENT_CHN_CLK_CTL_PRE_SCALER_SHIFT 0u

#define SENT_CHN_CLK_CTL_PRE_SCALER_WIDTH 14u

#define SENT_CHN_CLK_CTL_PRE_SCALER(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CLK_CTL_PRE_SCALER_SHIFT))&SENT_CHN_CLK_CTL_PRE_SCALER_MASK)

/* CHN_CLK_CTL0 Reg Mask */

#define SENT_CHN_CLK_CTL_MASK          0x7FFFBFFFu



/* CHN_STAT Bit Fields */

#define SENT_CHN_STAT_BUS_IDLE_MASK    0x80000000u

#define SENT_CHN_STAT_BUS_IDLE_SHIFT   31u

#define SENT_CHN_STAT_BUS_IDLE_WIDTH   1u

#define SENT_CHN_STAT_BUS_IDLE(x)      (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STAT_BUS_IDLE_SHIFT))&SENT_CHN_STAT_BUS_IDLE_MASK)

#define SENT_CHN_STAT_SPC_OVERRUN_MASK 0x20000000u

#define SENT_CHN_STAT_SPC_OVERRUN_SHIFT 29u

#define SENT_CHN_STAT_SPC_OVERRUN_WIDTH 1u

#define SENT_CHN_STAT_SPC_OVERRUN(x)   (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STAT_SPC_OVERRUN_SHIFT))&SENT_CHN_STAT_SPC_OVERRUN_MASK)

#define SENT_CHN_STAT_CAL_RESYNC_MASK  0x8000000u

#define SENT_CHN_STAT_CAL_RESYNC_SHIFT 27u

#define SENT_CHN_STAT_CAL_RESYNC_WIDTH 1u

#define SENT_CHN_STAT_CAL_RESYNC(x)    (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STAT_CAL_RESYNC_SHIFT))&SENT_CHN_STAT_CAL_RESYNC_MASK)

#define SENT_CHN_STAT_CAL_20_25_MASK   0x4000000u

#define SENT_CHN_STAT_CAL_20_25_SHIFT  26u

#define SENT_CHN_STAT_CAL_20_25_WIDTH  1u

#define SENT_CHN_STAT_CAL_20_25(x)     (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STAT_CAL_20_25_SHIFT))&SENT_CHN_STAT_CAL_20_25_MASK)

#define SENT_CHN_STAT_S_OVFL_MASK      0x2000000u

#define SENT_CHN_STAT_S_OVFL_SHIFT     25u

#define SENT_CHN_STAT_S_OVFL_WIDTH     1u

#define SENT_CHN_STAT_S_OVFL(x)        (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STAT_S_OVFL_SHIFT))&SENT_CHN_STAT_S_OVFL_MASK)

#define SENT_CHN_STAT_F_OVFL_MASK      0x1000000u

#define SENT_CHN_STAT_F_OVFL_SHIFT     24u

#define SENT_CHN_STAT_F_OVFL_WIDTH     1u

#define SENT_CHN_STAT_F_OVFL(x)        (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STAT_F_OVFL_SHIFT))&SENT_CHN_STAT_F_OVFL_MASK)

#define SENT_CHN_STAT_NVAL_LESS_ERR_MASK 0x800000u

#define SENT_CHN_STAT_NVAL_LESS_ERR_SHIFT 23u

#define SENT_CHN_STAT_NVAL_LESS_ERR_WIDTH 1u

#define SENT_CHN_STAT_NVAL_LESS_ERR(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STAT_NVAL_LESS_ERR_SHIFT))&SENT_CHN_STAT_NVAL_LESS_ERR_MASK)

#define SENT_CHN_STAT_PP_DIAG_ERR_MASK 0x400000u

#define SENT_CHN_STAT_PP_DIAG_ERR_SHIFT 22u

#define SENT_CHN_STAT_PP_DIAG_ERR_WIDTH 1u

#define SENT_CHN_STAT_PP_DIAG_ERR(x)   (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STAT_PP_DIAG_ERR_SHIFT))&SENT_CHN_STAT_PP_DIAG_ERR_MASK)

#define SENT_CHN_STAT_CAL_DIAG_ERR_MASK 0x200000u

#define SENT_CHN_STAT_CAL_DIAG_ERR_SHIFT 21u

#define SENT_CHN_STAT_CAL_DIAG_ERR_WIDTH 1u

#define SENT_CHN_STAT_CAL_DIAG_ERR(x)  (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STAT_CAL_DIAG_ERR_SHIFT))&SENT_CHN_STAT_CAL_DIAG_ERR_MASK)

#define SENT_CHN_STAT_CAL_ERR_MASK     0x100000u

#define SENT_CHN_STAT_CAL_ERR_SHIFT    20u

#define SENT_CHN_STAT_CAL_ERR_WIDTH    1u

#define SENT_CHN_STAT_CAL_ERR(x)       (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STAT_CAL_ERR_SHIFT))&SENT_CHN_STAT_CAL_ERR_MASK)

#define SENT_CHN_STAT_NVAL_EXCEED_ERR_MASK 0x80000u

#define SENT_CHN_STAT_NVAL_EXCEED_ERR_SHIFT 19u

#define SENT_CHN_STAT_NVAL_EXCEED_ERR_WIDTH 1u

#define SENT_CHN_STAT_NVAL_EXCEED_ERR(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STAT_NVAL_EXCEED_ERR_SHIFT))&SENT_CHN_STAT_NVAL_EXCEED_ERR_MASK)

#define SENT_CHN_STAT_S_CRC_ERR_MASK   0x40000u

#define SENT_CHN_STAT_S_CRC_ERR_SHIFT  18u

#define SENT_CHN_STAT_S_CRC_ERR_WIDTH  1u

#define SENT_CHN_STAT_S_CRC_ERR(x)     (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STAT_S_CRC_ERR_SHIFT))&SENT_CHN_STAT_S_CRC_ERR_MASK)

#define SENT_CHN_STAT_F_CRC_ERR_MASK   0x20000u

#define SENT_CHN_STAT_F_CRC_ERR_SHIFT  17u

#define SENT_CHN_STAT_F_CRC_ERR_WIDTH  1u

#define SENT_CHN_STAT_F_CRC_ERR(x)     (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STAT_F_CRC_ERR_SHIFT))&SENT_CHN_STAT_F_CRC_ERR_MASK)

#define SENT_CHN_STAT_EDGE_ERR_MASK    0x10000u

#define SENT_CHN_STAT_EDGE_ERR_SHIFT   16u

#define SENT_CHN_STAT_EDGE_ERR_WIDTH   1u

#define SENT_CHN_STAT_EDGE_ERR(x)      (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STAT_EDGE_ERR_SHIFT))&SENT_CHN_STAT_EDGE_ERR_MASK)

/* CHN_STAT0 Reg Mask */

#define SENT_CHN_STAT_MASK             0xAFFF0000u



/* CHN_CTL Bit Fields */

#define SENT_CHN_CTL_BUS_IDLE_IE_MASK  0x80000000u

#define SENT_CHN_CTL_BUS_IDLE_IE_SHIFT 31u

#define SENT_CHN_CTL_BUS_IDLE_IE_WIDTH 1u

#define SENT_CHN_CTL_BUS_IDLE_IE(x)    (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_BUS_IDLE_IE_SHIFT))&SENT_CHN_CTL_BUS_IDLE_IE_MASK)

#define SENT_CHN_CTL_SPC_OVERRUN_IE_MASK 0x20000000u

#define SENT_CHN_CTL_SPC_OVERRUN_IE_SHIFT 29u

#define SENT_CHN_CTL_SPC_OVERRUN_IE_WIDTH 1u

#define SENT_CHN_CTL_SPC_OVERRUN_IE(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_SPC_OVERRUN_IE_SHIFT))&SENT_CHN_CTL_SPC_OVERRUN_IE_MASK)

#define SENT_CHN_CTL_ALT_4BIT_CRC_MASK 0x10000000u

#define SENT_CHN_CTL_ALT_4BIT_CRC_SHIFT 28u

#define SENT_CHN_CTL_ALT_4BIT_CRC_WIDTH 1u

#define SENT_CHN_CTL_ALT_4BIT_CRC(x)   (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_ALT_4BIT_CRC_SHIFT))&SENT_CHN_CTL_ALT_4BIT_CRC_MASK)

#define SENT_CHN_CTL_CAL_RESYNC_IE_MASK 0x8000000u

#define SENT_CHN_CTL_CAL_RESYNC_IE_SHIFT 27u

#define SENT_CHN_CTL_CAL_RESYNC_IE_WIDTH 1u

#define SENT_CHN_CTL_CAL_RESYNC_IE(x)  (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_CAL_RESYNC_IE_SHIFT))&SENT_CHN_CTL_CAL_RESYNC_IE_MASK)

#define SENT_CHN_CTL_CAL_20_25_IE_MASK 0x4000000u

#define SENT_CHN_CTL_CAL_20_25_IE_SHIFT 26u

#define SENT_CHN_CTL_CAL_20_25_IE_WIDTH 1u

#define SENT_CHN_CTL_CAL_20_25_IE(x)   (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_CAL_20_25_IE_SHIFT))&SENT_CHN_CTL_CAL_20_25_IE_MASK)

#define SENT_CHN_CTL_SMSG_OVFL_IE_MASK 0x2000000u

#define SENT_CHN_CTL_SMSG_OVFL_IE_SHIFT 25u

#define SENT_CHN_CTL_SMSG_OVFL_IE_WIDTH 1u

#define SENT_CHN_CTL_SMSG_OVFL_IE(x)   (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_SMSG_OVFL_IE_SHIFT))&SENT_CHN_CTL_SMSG_OVFL_IE_MASK)

#define SENT_CHN_CTL_FMSG_OVFL_IE_MASK 0x1000000u

#define SENT_CHN_CTL_FMSG_OVFL_IE_SHIFT 24u

#define SENT_CHN_CTL_FMSG_OVFL_IE_WIDTH 1u

#define SENT_CHN_CTL_FMSG_OVFL_IE(x)   (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_FMSG_OVFL_IE_SHIFT))&SENT_CHN_CTL_FMSG_OVFL_IE_MASK)

#define SENT_CHN_CTL_FMSG_CRC_CHECK_OFF_MASK 0x800000u

#define SENT_CHN_CTL_FMSG_CRC_CHECK_OFF_SHIFT 23u

#define SENT_CHN_CTL_FMSG_CRC_CHECK_OFF_WIDTH 1u

#define SENT_CHN_CTL_FMSG_CRC_CHECK_OFF(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_FMSG_CRC_CHECK_OFF_SHIFT))&SENT_CHN_CTL_FMSG_CRC_CHECK_OFF_MASK)

#define SENT_CHN_CTL_PP_DIAG_ERR_IE_MASK 0x400000u

#define SENT_CHN_CTL_PP_DIAG_ERR_IE_SHIFT 22u

#define SENT_CHN_CTL_PP_DIAG_ERR_IE_WIDTH 1u

#define SENT_CHN_CTL_PP_DIAG_ERR_IE(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_PP_DIAG_ERR_IE_SHIFT))&SENT_CHN_CTL_PP_DIAG_ERR_IE_MASK)

#define SENT_CHN_CTL_CAL_DIAG_ERR_IE_MASK 0x200000u

#define SENT_CHN_CTL_CAL_DIAG_ERR_IE_SHIFT 21u

#define SENT_CHN_CTL_CAL_DIAG_ERR_IE_WIDTH 1u

#define SENT_CHN_CTL_CAL_DIAG_ERR_IE(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_CAL_DIAG_ERR_IE_SHIFT))&SENT_CHN_CTL_CAL_DIAG_ERR_IE_MASK)

#define SENT_CHN_CTL_CAL_ERR_IE_MASK   0x100000u

#define SENT_CHN_CTL_CAL_ERR_IE_SHIFT  20u

#define SENT_CHN_CTL_CAL_ERR_IE_WIDTH  1u

#define SENT_CHN_CTL_CAL_ERR_IE(x)     (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_CAL_ERR_IE_SHIFT))&SENT_CHN_CTL_CAL_ERR_IE_MASK)

#define SENT_CHN_CTL_NIB_ERR_IE_MASK   0x80000u

#define SENT_CHN_CTL_NIB_ERR_IE_SHIFT  19u

#define SENT_CHN_CTL_NIB_ERR_IE_WIDTH  1u

#define SENT_CHN_CTL_NIB_ERR_IE(x)     (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_NIB_ERR_IE_SHIFT))&SENT_CHN_CTL_NIB_ERR_IE_MASK)

#define SENT_CHN_CTL_S_CRC_ERR_IE_MASK 0x40000u

#define SENT_CHN_CTL_S_CRC_ERR_IE_SHIFT 18u

#define SENT_CHN_CTL_S_CRC_ERR_IE_WIDTH 1u

#define SENT_CHN_CTL_S_CRC_ERR_IE(x)   (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_S_CRC_ERR_IE_SHIFT))&SENT_CHN_CTL_S_CRC_ERR_IE_MASK)

#define SENT_CHN_CTL_F_CRC_ERR_IE_MASK 0x20000u

#define SENT_CHN_CTL_F_CRC_ERR_IE_SHIFT 17u

#define SENT_CHN_CTL_F_CRC_ERR_IE_WIDTH 1u

#define SENT_CHN_CTL_F_CRC_ERR_IE(x)   (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_F_CRC_ERR_IE_SHIFT))&SENT_CHN_CTL_F_CRC_ERR_IE_MASK)

#define SENT_CHN_CTL_EDGE_ERR_IE_MASK  0x10000u

#define SENT_CHN_CTL_EDGE_ERR_IE_SHIFT 16u

#define SENT_CHN_CTL_EDGE_ERR_IE_WIDTH 1u

#define SENT_CHN_CTL_EDGE_ERR_IE(x)    (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_EDGE_ERR_IE_SHIFT))&SENT_CHN_CTL_EDGE_ERR_IE_MASK)

#define SENT_CHN_CTL_DATA_CHANGE_EN_MASK 0x8000u

#define SENT_CHN_CTL_DATA_CHANGE_EN_SHIFT 15u

#define SENT_CHN_CTL_DATA_CHANGE_EN_WIDTH 1u

#define SENT_CHN_CTL_DATA_CHANGE_EN(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_DATA_CHANGE_EN_SHIFT))&SENT_CHN_CTL_DATA_CHANGE_EN_MASK)

#define SENT_CHN_CTL_CAL_SEL_MASK      0x4000u

#define SENT_CHN_CTL_CAL_SEL_SHIFT     14u

#define SENT_CHN_CTL_CAL_SEL_WIDTH     1u

#define SENT_CHN_CTL_CAL_SEL(x)        (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_CAL_SEL_SHIFT))&SENT_CHN_CTL_CAL_SEL_MASK)

#define SENT_CHN_CTL_PP_CHK_DIS_MASK   0x2000u

#define SENT_CHN_CTL_PP_CHK_DIS_SHIFT  13u

#define SENT_CHN_CTL_PP_CHK_DIS_WIDTH  1u

#define SENT_CHN_CTL_PP_CHK_DIS(x)     (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_PP_CHK_DIS_SHIFT))&SENT_CHN_CTL_PP_CHK_DIS_MASK)

#define SENT_CHN_CTL_FCRC_SEL_MASK     0x1000u

#define SENT_CHN_CTL_FCRC_SEL_SHIFT    12u

#define SENT_CHN_CTL_FCRC_SEL_WIDTH    1u

#define SENT_CHN_CTL_FCRC_SEL(x)       (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_FCRC_SEL_SHIFT))&SENT_CHN_CTL_FCRC_SEL_MASK)

#define SENT_CHN_CTL_FCRC_SC_EN_MASK   0x800u

#define SENT_CHN_CTL_FCRC_SC_EN_SHIFT  11u

#define SENT_CHN_CTL_FCRC_SC_EN_WIDTH  1u

#define SENT_CHN_CTL_FCRC_SC_EN(x)     (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_FCRC_SC_EN_SHIFT))&SENT_CHN_CTL_FCRC_SC_EN_MASK)

#define SENT_CHN_CTL_SCRC_SEL_MASK     0x400u

#define SENT_CHN_CTL_SCRC_SEL_SHIFT    10u

#define SENT_CHN_CTL_SCRC_SEL_WIDTH    1u

#define SENT_CHN_CTL_SCRC_SEL(x)       (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_SCRC_SEL_SHIFT))&SENT_CHN_CTL_SCRC_SEL_MASK)

#define SENT_CHN_CTL_PAUSE_DET_EN_MASK 0x200u

#define SENT_CHN_CTL_PAUSE_DET_EN_SHIFT 9u

#define SENT_CHN_CTL_PAUSE_DET_EN_WIDTH 1u

#define SENT_CHN_CTL_PAUSE_DET_EN(x)   (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_PAUSE_DET_EN_SHIFT))&SENT_CHN_CTL_PAUSE_DET_EN_MASK)

#define SENT_CHN_CTL_SCP_CHK_MASK      0x100u

#define SENT_CHN_CTL_SCP_CHK_SHIFT     8u

#define SENT_CHN_CTL_SCP_CHK_WIDTH     1u

#define SENT_CHN_CTL_SCP_CHK(x)        (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_SCP_CHK_SHIFT))&SENT_CHN_CTL_SCP_CHK_MASK)

#define SENT_CHN_CTL_FILT_CNT_MASK     0xFFu

#define SENT_CHN_CTL_FILT_CNT_SHIFT    0u

#define SENT_CHN_CTL_FILT_CNT_WIDTH    8u

#define SENT_CHN_CTL_FILT_CNT(x)       (((uint32_t)(((uint32_t)(x))<<SENT_CHN_CTL_FILT_CNT_SHIFT))&SENT_CHN_CTL_FILT_CNT_MASK)

/* CHN_CTL0 Reg Mask */

#define SENT_CHN_CTL_MASK              0xBFFFFFFFu



/* CHN_FDATA Bit Fields */

#define SENT_CHN_FDATA_DATA1_MASK      0xF0000000u

#define SENT_CHN_FDATA_DATA1_SHIFT     28u

#define SENT_CHN_FDATA_DATA1_WIDTH     4u

#define SENT_CHN_FDATA_DATA1(x)        (((uint32_t)(((uint32_t)(x))<<SENT_CHN_FDATA_DATA1_SHIFT))&SENT_CHN_FDATA_DATA1_MASK)

#define SENT_CHN_FDATA_DATA2_MASK      0xF000000u

#define SENT_CHN_FDATA_DATA2_SHIFT     24u

#define SENT_CHN_FDATA_DATA2_WIDTH     4u

#define SENT_CHN_FDATA_DATA2(x)        (((uint32_t)(((uint32_t)(x))<<SENT_CHN_FDATA_DATA2_SHIFT))&SENT_CHN_FDATA_DATA2_MASK)

#define SENT_CHN_FDATA_DATA3_MASK      0xF00000u

#define SENT_CHN_FDATA_DATA3_SHIFT     20u

#define SENT_CHN_FDATA_DATA3_WIDTH     4u

#define SENT_CHN_FDATA_DATA3(x)        (((uint32_t)(((uint32_t)(x))<<SENT_CHN_FDATA_DATA3_SHIFT))&SENT_CHN_FDATA_DATA3_MASK)

#define SENT_CHN_FDATA_DATA4_MASK      0xF0000u

#define SENT_CHN_FDATA_DATA4_SHIFT     16u

#define SENT_CHN_FDATA_DATA4_WIDTH     4u

#define SENT_CHN_FDATA_DATA4(x)        (((uint32_t)(((uint32_t)(x))<<SENT_CHN_FDATA_DATA4_SHIFT))&SENT_CHN_FDATA_DATA4_MASK)

#define SENT_CHN_FDATA_DATA5_MASK      0xF000u

#define SENT_CHN_FDATA_DATA5_SHIFT     12u

#define SENT_CHN_FDATA_DATA5_WIDTH     4u

#define SENT_CHN_FDATA_DATA5(x)        (((uint32_t)(((uint32_t)(x))<<SENT_CHN_FDATA_DATA5_SHIFT))&SENT_CHN_FDATA_DATA5_MASK)

#define SENT_CHN_FDATA_DATA6_MASK      0xF00u

#define SENT_CHN_FDATA_DATA6_SHIFT     8u

#define SENT_CHN_FDATA_DATA6_WIDTH     4u

#define SENT_CHN_FDATA_DATA6(x)        (((uint32_t)(((uint32_t)(x))<<SENT_CHN_FDATA_DATA6_SHIFT))&SENT_CHN_FDATA_DATA6_MASK)

#define SENT_CHN_FDATA_RESERVED0_MASK  0xF0u

#define SENT_CHN_FDATA_RESERVED0_SHIFT 4u

#define SENT_CHN_FDATA_RESERVED0_WIDTH 4u

#define SENT_CHN_FDATA_RESERVED0(x)    (((uint32_t)(((uint32_t)(x))<<SENT_CHN_FDATA_RESERVED0_SHIFT))&SENT_CHN_FDATA_RESERVED0_MASK)

#define SENT_CHN_FDATA_RESERVED1_MASK  0xFu

#define SENT_CHN_FDATA_RESERVED1_SHIFT 0u

#define SENT_CHN_FDATA_RESERVED1_WIDTH 4u

#define SENT_CHN_FDATA_RESERVED1(x)    (((uint32_t)(((uint32_t)(x))<<SENT_CHN_FDATA_RESERVED1_SHIFT))&SENT_CHN_FDATA_RESERVED1_MASK)

/* CHN_FDATA0 Reg Mask */

#define SENT_CHN_FDATA_MASK            0xFFFFFFFFu



/* CHN_FCRC Bit Fields */

#define SENT_CHN_FCRC_CRC_DATA_MASK    0xF0000u

#define SENT_CHN_FCRC_CRC_DATA_SHIFT   16u

#define SENT_CHN_FCRC_CRC_DATA_WIDTH   4u

#define SENT_CHN_FCRC_CRC_DATA(x)      (((uint32_t)(((uint32_t)(x))<<SENT_CHN_FCRC_CRC_DATA_SHIFT))&SENT_CHN_FCRC_CRC_DATA_MASK)

#define SENT_CHN_FCRC_SC_NB_MASK       0xFu

#define SENT_CHN_FCRC_SC_NB_SHIFT      0u

#define SENT_CHN_FCRC_SC_NB_WIDTH      4u

#define SENT_CHN_FCRC_SC_NB(x)         (((uint32_t)(((uint32_t)(x))<<SENT_CHN_FCRC_SC_NB_SHIFT))&SENT_CHN_FCRC_SC_NB_MASK)

/* CHN_FCRC0 Reg Mask */

#define SENT_CHN_FCRC_MASK             0x000F000Fu



/* CHN_FTS Bit Fields */

#define SENT_CHN_FTS_TIMESTAMP_VAL_MASK 0xFFFFFFFFu

#define SENT_CHN_FTS_TIMESTAMP_VAL_SHIFT 0u

#define SENT_CHN_FTS_TIMESTAMP_VAL_WIDTH 32u

#define SENT_CHN_FTS_TIMESTAMP_VAL(x)  (((uint32_t)(((uint32_t)(x))<<SENT_CHN_FTS_TIMESTAMP_VAL_SHIFT))&SENT_CHN_FTS_TIMESTAMP_VAL_MASK)

/* CHN_FTS0 Reg Mask */

#define SENT_CHN_FTS_MASK              0xFFFFFFFFu



/* CHN_SBIT3_ Bit Fields */

#define SENT_CHN_SBIT3__CHN_NUM_MASK   0xF0000000u

#define SENT_CHN_SBIT3__CHN_NUM_SHIFT  28u

#define SENT_CHN_SBIT3__CHN_NUM_WIDTH  4u

#define SENT_CHN_SBIT3__CHN_NUM(x)     (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SBIT3__CHN_NUM_SHIFT))&SENT_CHN_SBIT3__CHN_NUM_MASK)

#define SENT_CHN_SBIT3__MSG_TYPE_MASK  0x8000000u

#define SENT_CHN_SBIT3__MSG_TYPE_SHIFT 27u

#define SENT_CHN_SBIT3__MSG_TYPE_WIDTH 1u

#define SENT_CHN_SBIT3__MSG_TYPE(x)    (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SBIT3__MSG_TYPE_SHIFT))&SENT_CHN_SBIT3__MSG_TYPE_MASK)

#define SENT_CHN_SBIT3__CFG_MASK       0x400u

#define SENT_CHN_SBIT3__CFG_SHIFT      10u

#define SENT_CHN_SBIT3__CFG_WIDTH      1u

#define SENT_CHN_SBIT3__CFG(x)         (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SBIT3__CFG_SHIFT))&SENT_CHN_SBIT3__CFG_MASK)

#define SENT_CHN_SBIT3__ID7_4_OR_ID3_0_MASK 0x3C0u

#define SENT_CHN_SBIT3__ID7_4_OR_ID3_0_SHIFT 6u

#define SENT_CHN_SBIT3__ID7_4_OR_ID3_0_WIDTH 4u

#define SENT_CHN_SBIT3__ID7_4_OR_ID3_0(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SBIT3__ID7_4_OR_ID3_0_SHIFT))&SENT_CHN_SBIT3__ID7_4_OR_ID3_0_MASK)

#define SENT_CHN_SBIT3__ID3_0_OR_DATA15_12_MASK 0x1Eu

#define SENT_CHN_SBIT3__ID3_0_OR_DATA15_12_SHIFT 1u

#define SENT_CHN_SBIT3__ID3_0_OR_DATA15_12_WIDTH 4u

#define SENT_CHN_SBIT3__ID3_0_OR_DATA15_12(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SBIT3__ID3_0_OR_DATA15_12_SHIFT))&SENT_CHN_SBIT3__ID3_0_OR_DATA15_12_MASK)

/* CHN_SBIT3_0 Reg Mask */

#define SENT_CHN_SBIT3__MASK           0xF80007DEu



/* CHN_SBIT2_ Bit Fields */

#define SENT_CHN_SBIT2__SMSG_CRC_MASK  0x3F0000u

#define SENT_CHN_SBIT2__SMSG_CRC_SHIFT 16u

#define SENT_CHN_SBIT2__SMSG_CRC_WIDTH 6u

#define SENT_CHN_SBIT2__SMSG_CRC(x)    (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SBIT2__SMSG_CRC_SHIFT))&SENT_CHN_SBIT2__SMSG_CRC_MASK)

#define SENT_CHN_SBIT2__SMSG_DATA_MASK 0xFFFu

#define SENT_CHN_SBIT2__SMSG_DATA_SHIFT 0u

#define SENT_CHN_SBIT2__SMSG_DATA_WIDTH 12u

#define SENT_CHN_SBIT2__SMSG_DATA(x)   (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SBIT2__SMSG_DATA_SHIFT))&SENT_CHN_SBIT2__SMSG_DATA_MASK)

/* CHN_SBIT2_0 Reg Mask */

#define SENT_CHN_SBIT2__MASK           0x003F0FFFu



/* CHN_STS Bit Fields */

#define SENT_CHN_STS_SMSG_TIMESTAMP_MASK 0xFFFFFFFFu

#define SENT_CHN_STS_SMSG_TIMESTAMP_SHIFT 0u

#define SENT_CHN_STS_SMSG_TIMESTAMP_WIDTH 32u

#define SENT_CHN_STS_SMSG_TIMESTAMP(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_STS_SMSG_TIMESTAMP_SHIFT))&SENT_CHN_STS_SMSG_TIMESTAMP_MASK)

/* CHN_STS0 Reg Mask */

#define SENT_CHN_STS_MASK              0xFFFFFFFFu



/* CHN_DFD Bit Fields */

#define SENT_CHN_DFD_FMSG_DATA_MASK    0xFFFFFFFFu

#define SENT_CHN_DFD_FMSG_DATA_SHIFT   0u

#define SENT_CHN_DFD_FMSG_DATA_WIDTH   32u

#define SENT_CHN_DFD_FMSG_DATA(x)      (((uint32_t)(((uint32_t)(x))<<SENT_CHN_DFD_FMSG_DATA_SHIFT))&SENT_CHN_DFD_FMSG_DATA_MASK)

/* CHN_DFD0 Reg Mask */

#define SENT_CHN_DFD_MASK              0xFFFFFFFFu



/* CHN_DFC Bit Fields */

#define SENT_CHN_DFC_FMSG_CRC_MASK     0xFFFFFFFFu

#define SENT_CHN_DFC_FMSG_CRC_SHIFT    0u

#define SENT_CHN_DFC_FMSG_CRC_WIDTH    32u

#define SENT_CHN_DFC_FMSG_CRC(x)       (((uint32_t)(((uint32_t)(x))<<SENT_CHN_DFC_FMSG_CRC_SHIFT))&SENT_CHN_DFC_FMSG_CRC_MASK)

/* CHN_DFC0 Reg Mask */

#define SENT_CHN_DFC_MASK              0xFFFFFFFFu



/* CHN_DFTS Bit Fields */

#define SENT_CHN_DFTS_FMSG_TSTMP_MASK  0xFFFFFFFFu

#define SENT_CHN_DFTS_FMSG_TSTMP_SHIFT 0u

#define SENT_CHN_DFTS_FMSG_TSTMP_WIDTH 32u

#define SENT_CHN_DFTS_FMSG_TSTMP(x)    (((uint32_t)(((uint32_t)(x))<<SENT_CHN_DFTS_FMSG_TSTMP_SHIFT))&SENT_CHN_DFTS_FMSG_TSTMP_MASK)

/* CHN_DFTS0 Reg Mask */

#define SENT_CHN_DFTS_MASK             0xFFFFFFFFu



/* CHN_DSB3_ Bit Fields */

#define SENT_CHN_DSB3__SMSG_BIT3_MASK  0xFFFFFFFFu

#define SENT_CHN_DSB3__SMSG_BIT3_SHIFT 0u

#define SENT_CHN_DSB3__SMSG_BIT3_WIDTH 32u

#define SENT_CHN_DSB3__SMSG_BIT3(x)    (((uint32_t)(((uint32_t)(x))<<SENT_CHN_DSB3__SMSG_BIT3_SHIFT))&SENT_CHN_DSB3__SMSG_BIT3_MASK)

/* CHN_DSB3_0 Reg Mask */

#define SENT_CHN_DSB3__MASK            0xFFFFFFFFu



/* CHN_DSB2_ Bit Fields */

#define SENT_CHN_DSB2__SMSG_BIT2_MASK  0xFFFFFFFFu

#define SENT_CHN_DSB2__SMSG_BIT2_SHIFT 0u

#define SENT_CHN_DSB2__SMSG_BIT2_WIDTH 32u

#define SENT_CHN_DSB2__SMSG_BIT2(x)    (((uint32_t)(((uint32_t)(x))<<SENT_CHN_DSB2__SMSG_BIT2_SHIFT))&SENT_CHN_DSB2__SMSG_BIT2_MASK)

/* CHN_DSB2_0 Reg Mask */

#define SENT_CHN_DSB2__MASK            0xFFFFFFFFu



/* CHN_DSTS Bit Fields */

#define SENT_CHN_DSTS_SMSG_TSTMP_MASK  0xFFFFFFFFu

#define SENT_CHN_DSTS_SMSG_TSTMP_SHIFT 0u

#define SENT_CHN_DSTS_SMSG_TSTMP_WIDTH 32u

#define SENT_CHN_DSTS_SMSG_TSTMP(x)    (((uint32_t)(((uint32_t)(x))<<SENT_CHN_DSTS_SMSG_TSTMP_SHIFT))&SENT_CHN_DSTS_SMSG_TSTMP_MASK)

/* CHN_DSTS0 Reg Mask */

#define SENT_CHN_DSTS_MASK             0xFFFFFFFFu



/* CHN_TSTMP Bit Fields */

#define SENT_CHN_TSTMP_CHN_TSTMP_MASK  0xFFFFFFFFu

#define SENT_CHN_TSTMP_CHN_TSTMP_SHIFT 0u

#define SENT_CHN_TSTMP_CHN_TSTMP_WIDTH 32u

#define SENT_CHN_TSTMP_CHN_TSTMP(x)    (((uint32_t)(((uint32_t)(x))<<SENT_CHN_TSTMP_CHN_TSTMP_SHIFT))&SENT_CHN_TSTMP_CHN_TSTMP_MASK)

/* CHN_TSTMP0 Reg Mask */

#define SENT_CHN_TSTMP_MASK            0xFFFFFFFFu



/* CHN_MCNT Bit Fields */

#define SENT_CHN_MCNT_FRAME_CNT_CLR_MASK 0x80000000u

#define SENT_CHN_MCNT_FRAME_CNT_CLR_SHIFT 31u

#define SENT_CHN_MCNT_FRAME_CNT_CLR_WIDTH 1u

#define SENT_CHN_MCNT_FRAME_CNT_CLR(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_MCNT_FRAME_CNT_CLR_SHIFT))&SENT_CHN_MCNT_FRAME_CNT_CLR_MASK)

#define SENT_CHN_MCNT_FRAME_CNT_MASK   0xFF0000u

#define SENT_CHN_MCNT_FRAME_CNT_SHIFT  16u

#define SENT_CHN_MCNT_FRAME_CNT_WIDTH  8u

#define SENT_CHN_MCNT_FRAME_CNT(x)     (((uint32_t)(((uint32_t)(x))<<SENT_CHN_MCNT_FRAME_CNT_SHIFT))&SENT_CHN_MCNT_FRAME_CNT_MASK)

#define SENT_CHN_MCNT_EDGE_CNT_CLR_MASK 0x8000u

#define SENT_CHN_MCNT_EDGE_CNT_CLR_SHIFT 15u

#define SENT_CHN_MCNT_EDGE_CNT_CLR_WIDTH 1u

#define SENT_CHN_MCNT_EDGE_CNT_CLR(x)  (((uint32_t)(((uint32_t)(x))<<SENT_CHN_MCNT_EDGE_CNT_CLR_SHIFT))&SENT_CHN_MCNT_EDGE_CNT_CLR_MASK)

#define SENT_CHN_MCNT_EDGE_CNT_MASK    0xFFu

#define SENT_CHN_MCNT_EDGE_CNT_SHIFT   0u

#define SENT_CHN_MCNT_EDGE_CNT_WIDTH   8u

#define SENT_CHN_MCNT_EDGE_CNT(x)      (((uint32_t)(((uint32_t)(x))<<SENT_CHN_MCNT_EDGE_CNT_SHIFT))&SENT_CHN_MCNT_EDGE_CNT_MASK)

/* CHN_MCNT0 Reg Mask */

#define SENT_CHN_MCNT_MASK             0x80FF80FFu



/* CHN_SPC_CTL Bit Fields */

#define SENT_CHN_SPC_CTL_SPC_ENABLE_MASK 0x80000000u

#define SENT_CHN_SPC_CTL_SPC_ENABLE_SHIFT 31u

#define SENT_CHN_SPC_CTL_SPC_ENABLE_WIDTH 1u

#define SENT_CHN_SPC_CTL_SPC_ENABLE(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SPC_CTL_SPC_ENABLE_SHIFT))&SENT_CHN_SPC_CTL_SPC_ENABLE_MASK)

#define SENT_CHN_SPC_CTL_CAL_DIAG_DIS_MASK 0x20000u

#define SENT_CHN_SPC_CTL_CAL_DIAG_DIS_SHIFT 17u

#define SENT_CHN_SPC_CTL_CAL_DIAG_DIS_WIDTH 1u

#define SENT_CHN_SPC_CTL_CAL_DIAG_DIS(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SPC_CTL_CAL_DIAG_DIS_SHIFT))&SENT_CHN_SPC_CTL_CAL_DIAG_DIS_MASK)

#define SENT_CHN_SPC_CTL_SPC_BUSY_MASK 0x10000u

#define SENT_CHN_SPC_CTL_SPC_BUSY_SHIFT 16u

#define SENT_CHN_SPC_CTL_SPC_BUSY_WIDTH 1u

#define SENT_CHN_SPC_CTL_SPC_BUSY(x)   (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SPC_CTL_SPC_BUSY_SHIFT))&SENT_CHN_SPC_CTL_SPC_BUSY_MASK)

#define SENT_CHN_SPC_CTL_SPC_MODE_MASK 0xC000u

#define SENT_CHN_SPC_CTL_SPC_MODE_SHIFT 14u

#define SENT_CHN_SPC_CTL_SPC_MODE_WIDTH 2u

#define SENT_CHN_SPC_CTL_SPC_MODE(x)   (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SPC_CTL_SPC_MODE_SHIFT))&SENT_CHN_SPC_CTL_SPC_MODE_MASK)

#define SENT_CHN_SPC_CTL_SPC_PULSE_DELAY_MASK 0x3F00u

#define SENT_CHN_SPC_CTL_SPC_PULSE_DELAY_SHIFT 8u

#define SENT_CHN_SPC_CTL_SPC_PULSE_DELAY_WIDTH 6u

#define SENT_CHN_SPC_CTL_SPC_PULSE_DELAY(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SPC_CTL_SPC_PULSE_DELAY_SHIFT))&SENT_CHN_SPC_CTL_SPC_PULSE_DELAY_MASK)

#define SENT_CHN_SPC_CTL_SPC_TICK_BASE_MASK 0x80u

#define SENT_CHN_SPC_CTL_SPC_TICK_BASE_SHIFT 7u

#define SENT_CHN_SPC_CTL_SPC_TICK_BASE_WIDTH 1u

#define SENT_CHN_SPC_CTL_SPC_TICK_BASE(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SPC_CTL_SPC_TICK_BASE_SHIFT))&SENT_CHN_SPC_CTL_SPC_TICK_BASE_MASK)

#define SENT_CHN_SPC_CTL_SPC_START_MASK 0x40u

#define SENT_CHN_SPC_CTL_SPC_START_SHIFT 6u

#define SENT_CHN_SPC_CTL_SPC_START_WIDTH 1u

#define SENT_CHN_SPC_CTL_SPC_START(x)  (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SPC_CTL_SPC_START_SHIFT))&SENT_CHN_SPC_CTL_SPC_START_MASK)

#define SENT_CHN_SPC_CTL_SPC_PULSE_WIDTH_MASK 0x3Fu

#define SENT_CHN_SPC_CTL_SPC_PULSE_WIDTH_SHIFT 0u

#define SENT_CHN_SPC_CTL_SPC_PULSE_WIDTH_WIDTH 6u

#define SENT_CHN_SPC_CTL_SPC_PULSE_WIDTH(x) (((uint32_t)(((uint32_t)(x))<<SENT_CHN_SPC_CTL_SPC_PULSE_WIDTH_SHIFT))&SENT_CHN_SPC_CTL_SPC_PULSE_WIDTH_MASK)

/* CHN_SPC_CTL0 Reg Mask */

#define SENT_CHN_SPC_CTL_MASK          0x8003FFFFu



/* CHN_IDLE_CTL Bit Fields */

#define SENT_CHN_IDLE_CTL_IDLE_CNT_MASK 0xFu

#define SENT_CHN_IDLE_CTL_IDLE_CNT_SHIFT 0u

#define SENT_CHN_IDLE_CTL_IDLE_CNT_WIDTH 4u

#define SENT_CHN_IDLE_CTL_IDLE_CNT(x)  (((uint32_t)(((uint32_t)(x))<<SENT_CHN_IDLE_CTL_IDLE_CNT_SHIFT))&SENT_CHN_IDLE_CTL_IDLE_CNT_MASK)

/* CHN_IDLE_CTL0 Reg Mask */

#define SENT_CHN_IDLE_CTL_MASK         0x0000000Fu





/*!

 * @}

 */ /* end of group SENT_Register_Masks */



/*!

 * @}

 */ /* end of group SENT_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
