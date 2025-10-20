/**
 * @file fc7xxx_driver_fcspi.c
 * @author Flagchip
 * @brief FC7xxx FCSPI driver type definition and API
 * @version 0.1.0
 * @date 2024-01-14
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024/01/12    Flagchip071    N/A          First version for FC240
   ******************************************************************************** */

#include "interrupt_manager.h"
#include "fc7xxx_driver_fcspi.h"
#define FCSPI_DRV_STATUS_REG_W1C_U32  ((uint32_t)(  FCSPI_STATUS_DMF(1)    | \
                                                    FCSPI_STATUS_RX_FO(1)  | \
                                                    FCSPI_STATUS_TX_FU(1)  | \
                                                    FCSPI_STATUS_TCF(1)    | \
                                                    FCSPI_STATUS_FEF(1)    | \
                                                    FCSPI_STATUS_RX_WF(1)))

#define FCSPI_DRV_STATUS_REG_W1C_MASK_U32 ((uint32_t)(FCSPI_STATUS_DMF_MASK   | \
                                                      FCSPI_STATUS_RX_FO_MASK | \
                                                      FCSPI_STATUS_TX_FU_MASK | \
                                                      FCSPI_STATUS_TCF_MASK   | \
                                                      FCSPI_STATUS_FEF_MASK   | \
                                                      FCSPI_STATUS_RX_WF_MASK))

#define FCSPI_DRV_INT_EN_REG_ALL_U32   ((uint32_t)(FCSPI_INT_EN_DMIE(1)     | \
                                                    FCSPI_INT_EN_RFOIE(1)   | \
                                                    FCSPI_INT_EN_TFUIE(1)   | \
                                                    FCSPI_INT_EN_TCIE(1)    | \
                                                    FCSPI_INT_EN_FEIE(1)    | \
                                                    FCSPI_INT_EN_RWIE(1)    | \
                                                    FCSPI_INT_EN_RX_PEIE(1) | \
                                                    FCSPI_INT_EN_TX_PEIE(1) | \
                                                    FCSPI_INT_EN_RFIE(1)    | \
                                                    FCSPI_INT_EN_TFIE(1)))

#define FCSPI_DRV_RX_FIFO_WORD_CNT (8)

#define FCSPI_DRV_TX_FIFO_WORD_CNT (8)

#define FCSPI_CFGR1_PCS23_PCS_MODE_U32                  FCSPI_CFG1_PCS_CFG(0) /* PCS[3:2] as PCS feature */
#define FCSPI_CFGR1_PCS23_DATABUS_IN_4BIT_MODE_U32      FCSPI_CFG1_PCS_CFG(1) /* PCS[3:2] as data bus in 4-bit mode */

#define FCSPI_CFGR1_OUTCFG_RETAIN_LAST_WHEN_NEGATE_U32  FCSPI_CFG1_OUT_CFG(0)
#define FCSPI_CFGR1_OUTCFG_TRISTATE_WHEN_NEGATE_U32     FCSPI_CFG1_OUT_CFG(1)

#define FCSPI_CFGR1_PINCFG_SIN_INPUT_SOUT_OUTPUT_U32    FCSPI_CFG1_PIN_CFG(0) /* SIN is used for input data and SOUT for output data */
#define FCSPI_CFGR1_PINCFG_SIN_INPUT_OUTPUT_U32         FCSPI_CFG1_PIN_CFG(1) /* SIN is used for both input and output data */
#define FCSPI_CFGR1_PINCFG_SOUT_INPUT_OUTPUT_U32        FCSPI_CFG1_PIN_CFG(2) /* SOUT is used for both input and output data */
#define FCSPI_CFGR1_PINCFG_SOUT_INPUT_SIN_OUTPUT_U32    FCSPI_CFG1_PIN_CFG(3) /* SOUT is used for input data and SIN for output data */

#define FCSPI_CFGR1_PCS0_ACTIVE_HIGH_U32                FCSPI_CFG1_PCS_POL(1) /* Peripheral Chip Select Polarity - Active High */
#define FCSPI_CFGR1_PCS0_POL_MASK_U32                   FCSPI_CFG1_PCS_POL(1)
#define FCSPI_CFGR1_PCS1_ACTIVE_HIGH_U32                FCSPI_CFG1_PCS_POL(2) /* Peripheral Chip Select Polarity - Active High */
#define FCSPI_CFGR1_PCS1_POL_MASK_U32                   FCSPI_CFG1_PCS_POL(2)
#define FCSPI_CFGR1_PCS2_ACTIVE_HIGH_U32                FCSPI_CFG1_PCS_POL(4) /* Peripheral Chip Select Polarity - Active High */
#define FCSPI_CFGR1_PCS2_POL_MASK_U32                   FCSPI_CFG1_PCS_POL(4)
#define FCSPI_CFGR1_PCS3_ACTIVE_HIGH_U32                FCSPI_CFG1_PCS_POL(8) /* Peripheral Chip Select Polarity - Active High */
#define FCSPI_CFGR1_PCS3_POL_MASK_U32                   FCSPI_CFG1_PCS_POL(8)

#define FCSPI_TRCR_SCKPOL_ACTIVE_HIGH_U32               FCSPI_TR_CTRL_SCK_POL(0) /* When inactive, SCK is low */
#define FCSPI_TRCR_SCKPOL_ACTIVE_LOW_U32                FCSPI_TR_CTRL_SCK_POL(1) /* When inactive, SCK is high */

#define FCSPI_TRCR_SCKPHA_CAP_LEADING_U32               FCSPI_TR_CTRL_SCK_PHA(0) /* Data is changed on the leading edge of SCK and captured on the following edge */
#define FCSPI_TRCR_SCKPHA_CAP_TRAILING_U32              FCSPI_TR_CTRL_SCK_PHA(1) /* Data is captured on the leading edge of SCK and changed on the following edge */

#define FCSPI_TRCR_PRESCALE_1_U32                       FCSPI_TR_CTRL_PRESCALE(0) /* Divide by 1 */
#define FCSPI_TRCR_PRESCALE_2_U32                       FCSPI_TR_CTRL_PRESCALE(1) /* Divide by 2 */
#define FCSPI_TRCR_PRESCALE_4_U32                       FCSPI_TR_CTRL_PRESCALE(2) /* Divide by 4 */
#define FCSPI_TRCR_PRESCALE_8_U32                       FCSPI_TR_CTRL_PRESCALE(3) /* Divide by 8 */
#define FCSPI_TRCR_PRESCALE_16_U32                      FCSPI_TR_CTRL_PRESCALE(4) /* Divide by 16 */
#define FCSPI_TRCR_PRESCALE_32_U32                      FCSPI_TR_CTRL_PRESCALE(5) /* Divide by 32 */
#define FCSPI_TRCR_PRESCALE_64_U32                      FCSPI_TR_CTRL_PRESCALE(6) /* Divide by 64 */
#define FCSPI_TRCR_PRESCALE_128_U32                     FCSPI_TR_CTRL_PRESCALE(7) /* Divide by 128 */

#define FCSPI_TRCR_PCS0_EN_U32                          FCSPI_TR_CTRL_PCS(0) /* Transfer using FCSPI_PCS[0] */
#define FCSPI_TRCR_PCS1_EN_U32                          FCSPI_TR_CTRL_PCS(1) /* Transfer using FCSPI_PCS[1] */
#define FCSPI_TRCR_PCS2_EN_U32                          FCSPI_TR_CTRL_PCS(2) /* Transfer using FCSPI_PCS[2] */
#define FCSPI_TRCR_PCS3_EN_U32                          FCSPI_TR_CTRL_PCS(3) /* Transfer using FCSPI_PCS[3] */

#define FCSPI_TRCR_MSB_U32                              FCSPI_TR_CTRL_LSBF(0) /* Data is transferred MSB first */
#define FCSPI_TRCR_LSB_U32                              FCSPI_TR_CTRL_LSBF(1) /* Data is transferred LSB first */

#define FCSPI_TRCR_BYSW_EN_U32                          FCSPI_TR_CTRL_BYSW(1) /* Byte swap enabled */
#define FCSPI_TRCR_BYSW_DIS_U32                         FCSPI_TR_CTRL_BYSW(0) /* Byte swap disable */

#define FCSPI_TRCR_CONT_EN_U32                          FCSPI_TR_CTRL_CT_EN(1) /* Continuous transfer enabled */
#define FCSPI_TRCR_CONT_DIS_U32                         FCSPI_TR_CTRL_CT_EN(0) /* Continuous transfer disabled */

#define FCSPI_TRCR_CONTC_EN_U32                         FCSPI_TR_CTRL_CT_GO(1) /* Command word for continuing transfer */

#define FCSPI_TRCR_WIDTH_1_U32                          FCSPI_TR_CTRL_WIDTH(0) /* Single bit transfer */
#define FCSPI_TRCR_WIDTH_2_U32                          FCSPI_TR_CTRL_WIDTH(1) /* Two bita transfer */
#define FCSPI_TRCR_WIDTH_4_U32                          FCSPI_TR_CTRL_WIDTH(2) /* Four bits transfer */

#define ITCM_START_ADDRESS                              0x0u
#define ITCM_END_ADDRESS                                0xFFFFu
#define DTCM_START_ADDRESS                              0x20000000u
#define DTCM_END_ADDRESS                                0x2001FFFFu
#define ITCM_TO_BACKDOOR_OFFSET                         0x24000000u
#define DTCM_TO_BACKDOOR_OFFSET                         0x02000000u



typedef enum {
    SIN_INPUT_SOUT_OUTPUT = 0,
    SIN_INPUT_OUTPUT      = 1,
    SOUT_INPUT_OUTPUT     = 2,
    SOUT_INPUT_SIN_OUTPUT = 3
} FCSPI_PinModeType;

typedef enum {
    FCSPI_PRESCALE_1   = 0,
    FCSPI_PRESCALE_2   = 1,
    FCSPI_PRESCALE_4   = 2,
    FCSPI_PRESCALE_8   = 3,
    FCSPI_PRESCALE_16  = 4,
    FCSPI_PRESCALE_32  = 5,
    FCSPI_PRESCALE_64  = 6,
    FCSPI_PRESCALE_128 = 7,
    FCSPI_PRESCALE_MAX = 8
} FCSPI_PrescaleValueType;

typedef enum {
    FCSPI_TRANSFER_1_BIT = 0, /* 1-bit shift at a time, data out on SDO, in on SDI (normal mode) */
    FCSPI_TRANSFER_2_BIT = 1, /* 2-bits shift out on SDO/SDI and in on SDO/SDI */
    FCSPI_TRANSFER_4_BIT = 2  /* 4-bits shift out on SDO/SDI/PCS[3:2] and in on SDO/SDI/PCS[3:2] */
} FCSPI_TransferWidthType;

typedef enum {
    PINOUT_RETAIN_LAST = 0,
    PINOUT_TRISTATE    = 1
} FCSPI_NegatedPinOutStatType;

typedef enum {
    PCS2_3_PCS                   = 0,
    PCS2_3_DATA_BUS_IN_4BIT_MODE = 1
} FCSPI_PCS2_3ModeType;

typedef struct {
    FCSPI_SckPolarityType    eSckPolarity;
    FCSPI_SckSamplePhaseType eSckPhase;
    FCSPI_PrescaleValueType   ePrescalerValue;
    FCSPI_PCSType            ePCSSelect;
    FCSPI_BitFirstOrderType  eBitFirstOrder;
    FCSPI_AtomicBoolType     eByteSwap;
    FCSPI_AtomicBoolType     eContTransEnable;
    FCSPI_AtomicBoolType     eContCmdEnable;
    FCSPI_AtomicBoolType     eRxDisable;
    FCSPI_AtomicBoolType     eTxDisable;
    FCSPI_TransferWidthType  eTransferWidth;
    uint16_t                 u16FrameBitCnt;
} FCSPI_TxRxCtrlType;

typedef enum {
    FCSPI_TRANSFER_OK = 0U,    /* Transfer OK */
    FCSPI_TRANSFER_TX_FAIL,    /* Error during transmission */
    FCSPI_TRANSFER_RX_FAIL,    /* Error during reception */
    FCSPI_TRANSFER_ABORT,      /* Transfer is aborted */
} FCSPI_TransferStatusType;

typedef struct {
    uint16_t                        u16BitsPerFrame;          /* count of bits per frame: 8-4096bits */
    uint16_t                        u16BytesCntFrameNeed;     /* count of bytes per frame: 1-512bytes for external buffer passed into driver */
    FCSPI_BitFirstOrderType         eBitFirstOrder;           /* MSB/LSB first to send/receive */
    uint8_t                         u8TxFifoSize;             /* Tx fifo size */
    uint8_t                         u8RxFifoSize;             /* Rx fifo size */
    FCSPI_TriggerDmaInfType         tTriggerDmaInf;
    FCSPI_TriggerSrcType            eTransferTriggerSrc;  /* Type of transfer */
    FCSPI_StopCbType                pStopNotifyCb;        /* callback to transfer stop, transfer successfully or aborted */
    FCSPI_SemaphoreResetCbType      pSemaResetCb;         /* synchronous send need, reset the semaphore */
    FCSPI_SemaphoreTakeCbType       pSemaTakeCb;          /* synchronous send need, acquire the semaphore */
    FCSPI_SemaphorePostCbType       pSemaPostCb;          /* synchronous send need, release the semaphore outside of the interrupt */
    uint32_t                        u32DmaDummyData;      /* DMA mode, TX is NULL, just send this data, RX is NULL, just store in this var */

    FCSPI_SckSamplePhaseType        eSckSamplePhase;      /* select which edge of active sck clock to capture data */
    FCSPI_SckPolarityType           eSckPolarity;         /* select output sclk clock polarity */

    FCSPI_PCSType                   ePcs;                 /* chip select pin */
    FCSPI_PcsPolarityType           ePcsPolarity;         /* chip select pin polarity */

    /* only master mode use, slave not */
    FCSPI_AtomicBoolType            eIsPcsContinuous;     /* Option to keep chip select asserted until transfer complete; needed for TCR programming */
    uint32_t                        u32FCSpiSrcClk;       /* Module source clock */
    uint32_t                        u32Baundrate;         /* the bit per second of current transmission */

    /* dynamic state */
    volatile uint8_t                   u8WaitSemaphore;
    const uint8_t                     *pbyTxBuff;                   /* The buffer from which transmitted bytes are taken */
    uint8_t                           *pbyRxBuff;                   /* The buffer into which received bytes are placed */
    volatile uint16_t                  u16TxIndex;
    volatile uint16_t                  u16RxIndex;

    volatile uint16_t                  u16TxByteCntRemainToSend;    /* Number of bytes remaining to send  */
    volatile uint16_t                  u16RxByteCntRemainToGet;     /* Number of bytes remaining to receive */
    volatile uint16_t                  u16TxSendByteCntOfCurFrame;  /* Number of bytes from current frame which were already sent */
    volatile uint16_t                  u16RxGetByteCntOfCurFrame;   /* Number of bytes from current frame which were already received */
    volatile FCSPI_TransferStatusType  eTransferStat;               /* The status of the current */
    volatile FCSPI_AtomicBoolType      eIsInTransfer;               /* True if there is an active transfer */
} FCSPI_DrvStateType;

typedef struct
{
    FCSPI_MemMapPtr        tFCSpiInstance;
    FCSPI_DrvStateType     tFCSpiStat;
    IRQn_Type              eFCSpiIrq;
} FCSPI_DriverInfoType;

static FCSPI_DriverInfoType s_atFCSpiInfo[FCSPI_INSTANCE_COUNT] = {
                                                                     {FCSPI0, {0} ,FCSPI0_IRQn},
                                                                     {FCSPI1, {0} ,FCSPI1_IRQn},
                                                                     {FCSPI2, {0} ,FCSPI2_IRQn},
                                                                     {FCSPI3, {0} ,FCSPI3_IRQn},
                                                                     {FCSPI4, {0} ,FCSPI4_IRQn},
                                                                     {FCSPI5, {0} ,FCSPI5_IRQn}
                                                                                              };


/* soft reset just  reset the logic and registers except CTRL */
static void            FCSpi_Hw_Reset(FCSPI_InstanceType eInst,
                                FCSPI_AtomicBoolType eRxFifo,
                                FCSPI_AtomicBoolType eTxFifo,
                                FCSPI_AtomicBoolType eSoftRst);
static FCSPI_StatusType      FCSpi_Hw_Disable(FCSPI_InstanceType eInst);

/* get status value and check using macro */
#define   FCSpi_Hw_ChkBusy(status)                   (((status) & FCSPI_STATUS_BF_MASK) != 0U)
#define   FCSpi_Hw_ChkDataMatch(status)              (((status) & FCSPI_STATUS_DMF_MASK) != 0U)
#define   FCSpi_Hw_ChkRxFifoOverflow(status)         (((status) & FCSPI_STATUS_RX_FO_MASK) != 0U)
#define   FCSpi_Hw_ChkTxFifoUnderrun(status)         (((status) & FCSPI_STATUS_TX_FU_MASK) != 0U)
#define   FCSpi_Hw_ChkTransferComplete(status)       (((status) & FCSPI_STATUS_TCF_MASK) != 0U)
#define   FCSpi_Hw_ChkFrameEndDetected(status)       (((status) & FCSPI_STATUS_FEF_MASK) != 0U)
#define   FCSpi_Hw_ChkReceiveWordComplete(status)    (((status) & FCSPI_STATUS_RX_WF_MASK) != 0U)
#define   FCSpi_Hw_ChkRxGreaterThanWater(status)     (((status) & FCSPI_STATUS_RX_FF_MASK) != 0U)
#define   FCSpi_Hw_ChkTxEqualOrLessThanWater(status) (((status) & FCSPI_STATUS_TX_FF_MASK) != 0U)

static void      FCSpi_Hw_ClearSomeStatusW1CFlag(FCSPI_InstanceType eInst, uint32_t u32FlagBitSet); /* refer to FCSPI_DRV_STATUS_REG_W1C_U32 */
static void      FCSpi_Hw_EnableMoreInterrupts(FCSPI_InstanceType eInst, uint32_t u32Interrupts); /* refer to FCSPI_INT_EN_DMIE(1) */
static void      FCSpi_Hw_DisableSomeInterrupts(FCSPI_InstanceType eInst, uint32_t u32Interrupts); /* refer to FCSPI_INT_EN_DMIE(1) */
#define   FCSpi_Hw_EnableTransmitDataInterrupt(eInst)      FCSpi_Hw_EnableMoreInterrupts((eInst),  FCSPI_INT_EN_TFIE_MASK)
#define   FCSpi_Hw_DisableTransmitDataInterrupt(eInst)     FCSpi_Hw_DisableSomeInterrupts((eInst), FCSPI_INT_EN_TFIE_MASK)
#define   FCSpi_Hw_EnableReceiveDataInterrupt(eInst)       FCSpi_Hw_EnableMoreInterrupts((eInst),  FCSPI_INT_EN_RFIE_MASK)
#define   FCSpi_Hw_DisableReceiveDataInterrupt(eInst)      FCSpi_Hw_DisableSomeInterrupts((eInst), FCSPI_INT_EN_RFIE_MASK)
#define   FCSpi_Hw_EnableTransmitCompleteInterrupt(eInst)  FCSpi_Hw_EnableMoreInterrupts((eInst),  FCSPI_INT_EN_TCIE_MASK)
#define   FCSpi_Hw_DisableTransmitCompleteInterrupt(eInst) FCSpi_Hw_DisableSomeInterrupts((eInst), FCSPI_INT_EN_TCIE_MASK)

static void      FCSpi_Hw_SetPcs_2_3_Mode(FCSPI_InstanceType eInst, FCSPI_PCS2_3ModeType eMode);
static void      FCSpi_Hw_SetPin(FCSPI_InstanceType eInst, FCSPI_PinModeType eMode, FCSPI_NegatedPinOutStatType eStat);

static void      FCSpi_Hw_SetOnePcsPolarity(FCSPI_InstanceType eInst,
                            FCSPI_PCSType ePcs, FCSPI_PcsPolarityType ePolarity);

static void      FCSpi_Hw_Master_SetSckLoopbackSample(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType eEnable);

#define FCSpi_Hw_PrescalerRegToActualVal(eVal)  (((uint32_t)1) << ((uint8_t)(eVal)))
static void FCSpi_Hw_SetContinuousCommand(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType eEnable);

static void      FCSpi_Hw_SelectUsePcs(FCSPI_InstanceType eInst, FCSPI_PCSType ePCS);
static uint32_t FCSpi_Hw_Master_CalcBaudRate(const FCSPI_MasterCfgType *pCfg, uint32_t *pdwPrescaleRegVal, uint32_t *pdwActualSckDiv);

static FCSPI_StatusType           FCSpi_Hw_SetTRCR(FCSPI_InstanceType eInst, FCSPI_TxRxCtrlType *ptCtrl);
static FCSPI_PrescaleValueType    FCSpi_Hw_GetRegPrescalerVal(FCSPI_InstanceType eInst);

static void FCSpi_Hw_Get_SCK_PCS_DIV_Hold(FCSPI_InstanceType eInst, uint8_t *pbySCKPCS, uint8_t *pbyPCSSCK, uint8_t *pbyPCSPCS, uint8_t *pbySCKDIV);
static void FCSpi_Hw_Set_SCK_PCS_DIV_Hold(FCSPI_InstanceType eInst, uint8_t u8SCKPCS, uint8_t u8PCSSCK, uint8_t u8PCSPCS, uint8_t u8SCKDIV);
static void FCSpi_Hw_Set_SCK_PCS_Hold(FCSPI_InstanceType eInst, uint8_t u8SCKPCS, uint8_t u8PCSSCK, uint8_t u8PCSPCS);
static void FCSpi_Hw_SetRxTxDmaEnableStatus(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType eRxEnable, FCSPI_AtomicBoolType eTxEnable);
static void fcspi_read_rx_fifo(FCSPI_InstanceType eInst);
static void fcspi_write_tx_fifo(FCSPI_InstanceType eInst);
static void fcspi_master_clean_transfer(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInInterrupt);
static void fcspi_master_abort_transfer(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInISR);
static  void fcspi_master_dma_rx_err_interrupt(FCSPI_InstanceType eInst);
static void fcspi_0_master_dma_rx_err_interrupt(void);
static void fcspi_1_master_dma_rx_err_interrupt(void);
static void fcspi_2_master_dma_rx_err_interrupt(void);
static void fcspi_3_master_dma_rx_err_interrupt(void);
static void fcspi_4_master_dma_rx_err_interrupt(void);
static void fcspi_5_master_dma_rx_err_interrupt(void);
static void fcspi_master_dma_rx_finish_interrupt(void);
static  void fcspi_master_dma_tx_err_interrupt(FCSPI_InstanceType eInst);
static void fcspi_0_master_dma_tx_err_interrupt(void);
static void fcspi_1_master_dma_tx_err_interrupt(void);
static void fcspi_2_master_dma_tx_err_interrupt(void);
static void fcspi_3_master_dma_tx_err_interrupt(void);
static void fcspi_4_master_dma_tx_err_interrupt(void);
static void fcspi_5_master_dma_tx_err_interrupt(void);
static  void fcspi_master_dma_tx_finish_interrupt(FCSPI_InstanceType eInst);
static  void fcspi_0_master_dma_tx_finish_interrupt(void);
static  void fcspi_1_master_dma_tx_finish_interrupt(void);
static  void fcspi_2_master_dma_tx_finish_interrupt(void);
static  void fcspi_3_master_dma_tx_finish_interrupt(void);
static  void fcspi_4_master_dma_tx_finish_interrupt(void);
static  void fcspi_5_master_dma_tx_finish_interrupt(void);
static FCSPI_StatusType fcspi_master_async_transfer_bytes(FCSPI_InstanceType eInst,
    const uint8_t *pSendBuffer, uint8_t *pReceiveBuffer,
    uint16_t u16TransferByteCnt);
static FCSPI_StatusType fcspi_master_trigger(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInIsr);
static void fcspi_slave_clean_transfer(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInInterrupt);
static void fcspi_slave_abort_transfer(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInInterrupt);
static  void fcspi_slave_dma_rx_err_interrupt(FCSPI_InstanceType eInst);
static void fcspi_0_slave_dma_rx_err_interrupt(void);
static void fcspi_1_slave_dma_rx_err_interrupt(void);
static void fcspi_2_slave_dma_rx_err_interrupt(void);
static void fcspi_3_slave_dma_rx_err_interrupt(void);
static void fcspi_4_slave_dma_rx_err_interrupt(void);
static void fcspi_5_slave_dma_rx_err_interrupt(void);
static  void fcspi_slave_dma_rx_finish_interrupt(FCSPI_InstanceType eInst);
static void fcspi_0_slave_dma_rx_finish_interrupt(void);
static void fcspi_1_slave_dma_rx_finish_interrupt(void);
static void fcspi_2_slave_dma_rx_finish_interrupt(void);
static void fcspi_3_slave_dma_rx_finish_interrupt(void);
static void fcspi_4_slave_dma_rx_finish_interrupt(void);
static void fcspi_5_slave_dma_rx_finish_interrupt(void);
static  void fcspi_slave_dma_tx_err_interrupt(FCSPI_InstanceType eInst);
static void fcspi_0_slave_dma_tx_err_interrupt(void);
static void fcspi_1_slave_dma_tx_err_interrupt(void);
static void fcspi_2_slave_dma_tx_err_interrupt(void);
static void fcspi_3_slave_dma_tx_err_interrupt(void);
static void fcspi_4_slave_dma_tx_err_interrupt(void);
static void fcspi_5_slave_dma_tx_err_interrupt(void);
static  void fcspi_slave_dma_tx_finish_interrupt(FCSPI_InstanceType eInst);
static  void fcspi_0_slave_dma_tx_finish_interrupt(void);
static  void fcspi_1_slave_dma_tx_finish_interrupt(void);
static  void fcspi_2_slave_dma_tx_finish_interrupt(void);
static  void fcspi_3_slave_dma_tx_finish_interrupt(void);
static  void fcspi_4_slave_dma_tx_finish_interrupt(void);
static  void fcspi_5_slave_dma_tx_finish_interrupt(void);

static FCSPI_StatusType fcspi_slave_async_transfer_bytes(FCSPI_InstanceType eInst,
    const uint8_t *pSendBuffer, uint8_t *pReceiveBuffer, uint16_t u16TransferByteCnt);
static FCSPI_StatusType fcspi_slave_trigger(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInISR);
static void fcspi_irq_handler(FCSPI_InstanceType eInst);

static void FCSpi_Hw_Reset(FCSPI_InstanceType eInst,
        FCSPI_AtomicBoolType eRxFifo, FCSPI_AtomicBoolType eTxFifo, FCSPI_AtomicBoolType eSoftRst)
{
    uint32_t u32Flag    = 0U;
    uint32_t u32OldFlag = FCSPI_HWA_GetCtrlValue(s_atFCSpiInfo[eInst].tFCSpiInstance);
    uint32_t u32Mask    = FCSPI_CTRL_MASK;

    if (eRxFifo)
    {
        u32Flag |= FCSPI_CTRL_RST_RF(1);
    }

    if (eTxFifo)
    {
        u32Flag |= FCSPI_CTRL_RST_TF(1);
    }

    if (FCSPI_TRUE == eSoftRst)
    {
        u32Flag |= FCSPI_CTRL_SW_RST(1);
    }

    u32Flag |= u32OldFlag;
    FCSPI_HWA_SetCtrlValue(s_atFCSpiInfo[eInst].tFCSpiInstance, u32Flag);

    /* no need delay */
    if (FCSPI_TRUE == eSoftRst)
    {
        FCSPI_HWA_SetCtrlValue(s_atFCSpiInfo[eInst].tFCSpiInstance, 0U);
    }
    else
    {
        FCSPI_HWA_SetCtrlValue(s_atFCSpiInfo[eInst].tFCSpiInstance, (u32OldFlag & u32Mask));
    }
}

#ifdef   FCSPI_DRV_INTERNAL_FUNC_EN
static FCSPI_AtomicBoolType FCSpi_Hw_ChkEnabled(FCSPI_InstanceType eInst)
{
    return (FCSPI_AtomicBoolType)((FCSPI_HWA_GetCtrlValue(s_atFCSpiInfo[eInst].tFCSpiInstance) &
        FCSPI_CTRL_M_EN_MASK) >> FCSPI_CTRL_M_EN_SHIFT);
}
#endif

static FCSPI_StatusType FCSpi_Hw_Disable(FCSPI_InstanceType eInst)
{
    FCSPI_StatusType eStatus = FCSPI_STATUS_SUCCESS;

    if (0U != (FCSPI_HWA_GetStatus(s_atFCSpiInfo[eInst].tFCSpiInstance) & FCSPI_STATUS_BF_MASK))
    {
        eStatus = FCSPI_STATUS_BUSY;
    }
    else
    {
        FCSPI_HWA_ModuleDisable(s_atFCSpiInfo[eInst].tFCSpiInstance);
    }

    return eStatus;
}

static void FCSpi_Hw_ClearSomeStatusW1CFlag(
    FCSPI_InstanceType eInst, uint32_t u32FlagBitSet) /* refer to FCSPI_DRV_STATUS_REG_W1C_U32 */
{
    FCSPI_HWA_ClearStatus(s_atFCSpiInfo[eInst].tFCSpiInstance, (u32FlagBitSet & FCSPI_DRV_STATUS_REG_W1C_MASK_U32));
}

#ifdef   FCSPI_DRV_INTERNAL_FUNC_EN
static void FCSpi_Hw_SetAllInterruptEnableStatus(
    FCSPI_InstanceType eInst, uint32_t u32Interrupts) /* refer to FCSPI_DRV_INT_EN_REG_ALL_U32 */
{
    FCSPI_HWA_SetInterruptEnableReg(s_atFCSpiInfo[eInst].tFCSpiInstance, (u32Interrupts & FCSPI_INT_EN_MASK));
}

static uint32_t FCSpi_Hw_GetAllInterruptEnableStatus(FCSPI_InstanceType eInst)
{
    return FCSPI_HWA_GetIntrruptEnableReg(s_atFCSpiInfo[eInst].tFCSpiInstance);
}
#endif

static void FCSpi_Hw_EnableMoreInterrupts(FCSPI_InstanceType eInst, uint32_t u32Interrupts)
{
    uint32_t u32RegVal = FCSPI_HWA_GetIntrruptEnableReg(s_atFCSpiInfo[eInst].tFCSpiInstance);
    u32RegVal |= (u32Interrupts & FCSPI_INT_EN_MASK);

    FCSPI_HWA_SetInterruptEnableReg(s_atFCSpiInfo[eInst].tFCSpiInstance, u32RegVal);
}

static void FCSpi_Hw_DisableSomeInterrupts(FCSPI_InstanceType eInst, uint32_t u32Interrupts)
{
    uint32_t u32RegVal = FCSPI_HWA_GetIntrruptEnableReg(s_atFCSpiInfo[eInst].tFCSpiInstance);
    u32RegVal &= (~(u32Interrupts & FCSPI_INT_EN_MASK));

    FCSPI_HWA_SetInterruptEnableReg(s_atFCSpiInfo[eInst].tFCSpiInstance, u32RegVal);
}

static void FCSpi_Hw_SetRxTxDmaEnableStatus(
        FCSPI_InstanceType eInst, FCSPI_AtomicBoolType eRxEnable, FCSPI_AtomicBoolType eTxEnable)
{
    uint32_t u32Flag = 0U;

    if (eRxEnable)
    {
        u32Flag |= FCSPI_DMA_EN_RFDE(1);
    }

    if (eTxEnable)
    {
        u32Flag |= FCSPI_DMA_EN_TFDE(1);
    }

    FCSPI_HWA_SetDMAEnableReg(s_atFCSpiInfo[eInst].tFCSpiInstance, u32Flag);
}

#ifdef   FCSPI_DRV_INTERNAL_FUNC_EN
static void FCSpi_Hw_SetRxDmaEnableStatus(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType eEnable)
{
    uint32_t u32RegVal = FCSPI_HWA_GetDMAEnableReg(s_atFCSpiInfo[eInst].tFCSpiInstance);

    if (eEnable)
    {
        u32RegVal |= FCSPI_DMA_EN_RFDE(1);
    }
    else
    {
        u32RegVal &= (~(FCSPI_DMA_EN_RFDE_MASK));
    }

    FCSPI_HWA_SetDMAEnableReg(s_atFCSpiInfo[eInst].tFCSpiInstance, u32RegVal);
}

static void FCSpi_Hw_SetTxDmaEnableStatus(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType eEnable)
{
    uint32_t u32RegVal = FCSPI_HWA_GetDMAEnableReg(s_atFCSpiInfo[eInst].tFCSpiInstance);

    if (FCSPI_TRUE == eEnable)
    {
        u32RegVal |= FCSPI_DMA_EN_TFDE(1);
    }
    else
    {
        u32RegVal &= (~(FCSPI_DMA_EN_TFDE_MASK));
    }

    FCSPI_HWA_SetDMAEnableReg(s_atFCSpiInfo[eInst].tFCSpiInstance, u32RegVal);
}
#endif

static void FCSpi_Hw_SetPcs_2_3_Mode(FCSPI_InstanceType eInst, FCSPI_PCS2_3ModeType eMode)
{
    uint32_t u32RegVal = FCSPI_HWA_GetCFG1Reg(s_atFCSpiInfo[eInst].tFCSpiInstance);

    if (PCS2_3_PCS == eMode)
    {
        u32RegVal &= (~(FCSPI_CFG1_PCS_CFG_MASK));
    }
    else
    {
        u32RegVal |= (FCSPI_CFGR1_PCS23_DATABUS_IN_4BIT_MODE_U32);
    }

    FCSPI_HWA_SetCFG1Reg(s_atFCSpiInfo[eInst].tFCSpiInstance, u32RegVal);
}

static void FCSpi_Hw_SetPin(FCSPI_InstanceType eInst,
        FCSPI_PinModeType eMode, FCSPI_NegatedPinOutStatType eStat)
{
    uint32_t u32Flag = FCSPI_HWA_GetCFG1Reg(s_atFCSpiInfo[eInst].tFCSpiInstance);

    u32Flag &= (~(FCSPI_CFG1_PIN_CFG_MASK));
    u32Flag &= (~(FCSPI_CFG1_OUT_CFG_MASK));

    switch (eMode)
    {
        case SIN_INPUT_OUTPUT:
            u32Flag |= FCSPI_CFGR1_PINCFG_SIN_INPUT_OUTPUT_U32;
            break;
        case SOUT_INPUT_OUTPUT:
            u32Flag |= FCSPI_CFGR1_PINCFG_SOUT_INPUT_OUTPUT_U32;
            break;
        case SOUT_INPUT_SIN_OUTPUT:
            u32Flag |= FCSPI_CFGR1_PINCFG_SOUT_INPUT_SIN_OUTPUT_U32;
            break;
        case SIN_INPUT_SOUT_OUTPUT:
            u32Flag |= FCSPI_CFGR1_PINCFG_SIN_INPUT_SOUT_OUTPUT_U32;
            break;
        default:
            u32Flag |= FCSPI_CFGR1_PINCFG_SIN_INPUT_SOUT_OUTPUT_U32;
            break;
    }

    if (PINOUT_RETAIN_LAST == eStat)
    {
        u32Flag |= FCSPI_CFGR1_OUTCFG_RETAIN_LAST_WHEN_NEGATE_U32;
    }
    else
    {
        u32Flag |= FCSPI_CFGR1_OUTCFG_TRISTATE_WHEN_NEGATE_U32;
    }

    FCSPI_HWA_SetCFG1Reg(s_atFCSpiInfo[eInst].tFCSpiInstance, u32Flag);
}

#ifdef   FCSPI_DRV_INTERNAL_FUNC_EN
static void FCSpi_Hw_SetPcsPolarity(FCSPI_InstanceType eInst,
            FCSPI_AtomicBoolType eSetPCS0, FCSPI_PcsPolarityType ePCS0Polarity,
            FCSPI_AtomicBoolType eSetPCS1, FCSPI_PcsPolarityType ePCS1Polarity,
            FCSPI_AtomicBoolType eSetPCS2, FCSPI_PcsPolarityType ePCS2Polarity,
            FCSPI_AtomicBoolType eSetPCS3, FCSPI_PcsPolarityType ePCS3Polarity)
{
    uint32_t u32Flag = FCSPI_HWA_GetCFG1Reg(s_atFCSpiInfo[eInst].tFCSpiInstance);

    if (eSetPCS0)
    {
        if (FCSPI_PCS_POL_ACTIVE_HIGH == ePCS0Polarity)
            u32Flag |= FCSPI_CFGR1_PCS0_ACTIVE_HIGH_U32;
        else
            u32Flag &= (~(FCSPI_CFGR1_PCS0_POL_MASK_U32));
    }

    if (eSetPCS1)
    {
        if (FCSPI_PCS_POL_ACTIVE_HIGH == ePCS1Polarity)
            u32Flag |= FCSPI_CFGR1_PCS1_ACTIVE_HIGH_U32;
        else
            u32Flag &= (~(FCSPI_CFGR1_PCS1_POL_MASK_U32));
    }

    if (eSetPCS2)
    {
        if (FCSPI_PCS_POL_ACTIVE_HIGH == ePCS2Polarity)
            u32Flag |= FCSPI_CFGR1_PCS2_ACTIVE_HIGH_U32;
        else
            u32Flag &= (~(FCSPI_CFGR1_PCS2_POL_MASK_U32));
    }

    if (eSetPCS3)
    {
        if (FCSPI_PCS_POL_ACTIVE_HIGH == ePCS3Polarity)
            u32Flag |= FCSPI_CFGR1_PCS3_ACTIVE_HIGH_U32;
        else
            u32Flag &= (~(FCSPI_CFGR1_PCS3_POL_MASK_U32));
    }

    FCSPI_HWA_SetCFG1Reg(s_atFCSpiInfo[eInst].tFCSpiInstance, u32Flag);
}
#endif

static void FCSpi_Hw_SetOnePcsPolarity(FCSPI_InstanceType eInst,
                            FCSPI_PCSType ePcs, FCSPI_PcsPolarityType ePolarity)
{
    uint32_t u32Flag = FCSPI_HWA_GetCFG1Reg(s_atFCSpiInfo[eInst].tFCSpiInstance);

    if (FCSPI_PCS_POL_ACTIVE_HIGH == ePolarity)
    {
        if (0U == ((((uint32_t)0x1) << (FCSPI_CFG1_PCS_POL_SHIFT + (uint32_t)ePcs)) & u32Flag))
        {
            u32Flag |= (((uint32_t)0x1) << (FCSPI_CFG1_PCS_POL_SHIFT + (uint32_t)ePcs));
        }
    }
    else /* active low */
    {
        if (0U != ((((uint32_t)0x1) << (FCSPI_CFG1_PCS_POL_SHIFT + (uint32_t)ePcs)) & u32Flag))
        {
            u32Flag &= (~(((uint32_t)0x1) << (FCSPI_CFG1_PCS_POL_SHIFT + (uint32_t)ePcs)));
        }
    }

    FCSPI_HWA_SetCFG1Reg(s_atFCSpiInfo[eInst].tFCSpiInstance, u32Flag);
}

/* before call this function, ensure in master mode */
static void FCSpi_Hw_Master_SetSckLoopbackSample(
    FCSPI_InstanceType eInst, FCSPI_AtomicBoolType eEnable)
{
    uint32_t u32Flag = FCSPI_HWA_GetCFG1Reg(s_atFCSpiInfo[eInst].tFCSpiInstance);

    if (FCSPI_TRUE == eEnable)
    {
        if (FCSPI_CFG1_SCK_LB(1) != (u32Flag & FCSPI_CFG1_SCK_LB_MASK))
        {
            u32Flag |= FCSPI_CFG1_SCK_LB(1);
        }
    }
    else
    {
        if (FCSPI_CFG1_SCK_LB(0) != (u32Flag & FCSPI_CFG1_SCK_LB_MASK))
        {
            u32Flag &= (~(FCSPI_CFG1_SCK_LB_MASK));
        }
    }

    FCSPI_HWA_SetCFG1Reg(s_atFCSpiInfo[eInst].tFCSpiInstance, u32Flag);
}

static void FCSpi_Hw_Set_SCK_PCS_DIV_Hold(FCSPI_InstanceType eInst,
         uint8_t u8SCKPCS, uint8_t u8PCSSCK, uint8_t u8PCSPCS, uint8_t u8SCKDIV)
{
    uint32_t u32Flag = FCSPI_HWA_GetClockConfig(s_atFCSpiInfo[eInst].tFCSpiInstance);
    uint32_t u32Val;

    {
        u32Val = u8SCKPCS;
        u32Flag &= (~(FCSPI_CLK_CFG_SCKPCS_MASK));
        u32Flag |= (u32Val << FCSPI_CLK_CFG_SCKPCS_SHIFT);
    }

    {
        u32Val = u8PCSSCK;
        u32Flag &= (~(FCSPI_CLK_CFG_PCSSCK_MASK));
        u32Flag |= (u32Val << FCSPI_CLK_CFG_PCSSCK_SHIFT);
    }

    {
        u32Val = u8PCSPCS;
        u32Flag &= (~(FCSPI_CLK_CFG_PCSPCS_MASK));
        u32Flag |= (u32Val << FCSPI_CLK_CFG_PCSPCS_SHIFT);
    }

    {
        u32Val = u8SCKDIV;
        u32Flag &= (~(FCSPI_CLK_CFG_SCKDIV_MASK));
        u32Flag |= (u32Val << FCSPI_CLK_CFG_SCKDIV_SHIFT);
    }

    {
        FCSPI_HWA_SetClockConfig(s_atFCSpiInfo[eInst].tFCSpiInstance, u32Flag);
    }
}

static void FCSpi_Hw_Set_SCK_PCS_Hold(FCSPI_InstanceType eInst,
         uint8_t u8SCKPCS, uint8_t u8PCSSCK, uint8_t u8PCSPCS)
{
    uint32_t u32Flag = FCSPI_HWA_GetClockConfig(s_atFCSpiInfo[eInst].tFCSpiInstance);
    uint32_t u32Val;

    {
        u32Val = u8SCKPCS;
        u32Flag &= (~(FCSPI_CLK_CFG_SCKPCS_MASK));
        u32Flag |= (u32Val << FCSPI_CLK_CFG_SCKPCS_SHIFT);
    }

    {
        u32Val = u8PCSSCK;
        u32Flag &= (~(FCSPI_CLK_CFG_PCSSCK_MASK));
        u32Flag |= (u32Val << FCSPI_CLK_CFG_PCSSCK_SHIFT);
    }

    {
        u32Val = u8PCSPCS;
        u32Flag &= (~(FCSPI_CLK_CFG_PCSPCS_MASK));
        u32Flag |= (u32Val << FCSPI_CLK_CFG_PCSPCS_SHIFT);
    }

    {
        FCSPI_HWA_SetClockConfig(s_atFCSpiInfo[eInst].tFCSpiInstance, u32Flag);
    }
}

static void FCSpi_Hw_Get_SCK_PCS_DIV_Hold(FCSPI_InstanceType eInst,
                        uint8_t *pbySCKPCS,
                        uint8_t *pbyPCSSCK,
                        uint8_t *pbyPCSPCS,
                        uint8_t *pbySCKDIV)
{
    uint32_t u32Flag = FCSPI_HWA_GetClockConfig(s_atFCSpiInfo[eInst].tFCSpiInstance);

    if (pbySCKPCS != NULL)
    {
        *pbySCKPCS = (uint8_t)((u32Flag & FCSPI_CLK_CFG_SCKPCS_MASK) >> FCSPI_CLK_CFG_SCKPCS_SHIFT);
    }

    if (pbyPCSSCK != NULL)
    {
        *pbyPCSSCK = (uint8_t)((u32Flag & FCSPI_CLK_CFG_PCSSCK_MASK) >> FCSPI_CLK_CFG_PCSSCK_SHIFT);
    }

    if (pbyPCSPCS != NULL)
    {
        *pbyPCSPCS = (uint8_t)((u32Flag & FCSPI_CLK_CFG_PCSPCS_MASK) >> FCSPI_CLK_CFG_PCSPCS_SHIFT);
    }

    if (pbySCKDIV != NULL)
    {
        *pbySCKDIV = ((uint8_t)(u32Flag & FCSPI_CLK_CFG_SCKDIV_MASK) >> FCSPI_CLK_CFG_SCKDIV_SHIFT);
    }
}

#ifdef   FCSPI_DRV_INTERNAL_FUNC_EN
static void FCSpi_Hw_GetTRCR(FCSPI_InstanceType eInst, FCSPI_TxRxCtrlType *ptCtrl)
{
    uint32_t u32Flag = FCSPI_HWA_GetTxRxControl(s_atFCSpiInfo[eInst].tFCSpiInstance);

    ptCtrl->eSckPolarity = (FCSPI_SckPolarityType)
        ((u32Flag & FCSPI_TR_CTRL_SCK_POL_MASK) >> FCSPI_TR_CTRL_SCK_POL_SHIFT);
    ptCtrl->eSckPhase = (FCSPI_SckSamplePhaseType)
        ((u32Flag & FCSPI_TR_CTRL_SCK_PHA_MASK) >> FCSPI_TR_CTRL_SCK_PHA_SHIFT);
    ptCtrl->ePrescalerValue = (FCSPI_PrescaleValueType)
        ((u32Flag & FCSPI_TR_CTRL_PRESCALE_MASK) >> FCSPI_TR_CTRL_PRESCALE_SHIFT);
    ptCtrl->ePCSSelect = (FCSPI_PCSType)
        ((u32Flag & FCSPI_TR_CTRL_PCS_MASK) >> FCSPI_TR_CTRL_PCS_SHIFT);
    ptCtrl->eBitFirstOrder = (FCSPI_BitFirstOrderType)
        ((u32Flag & FCSPI_TR_CTRL_LSBF_MASK) >> FCSPI_TR_CTRL_LSBF_SHIFT);
    ptCtrl->eByteSwap = (FCSPI_AtomicBoolType)
        ((u32Flag & FCSPI_TR_CTRL_BYSW_MASK) >> FCSPI_TR_CTRL_BYSW_SHIFT);
    ptCtrl->eContTransEnable = (FCSPI_AtomicBoolType)
        ((u32Flag & FCSPI_TR_CTRL_CT_EN_MASK) >> FCSPI_TR_CTRL_CT_EN_SHIFT);

    ptCtrl->eContCmdEnable = (FCSPI_AtomicBoolType)
        ((u32Flag & FCSPI_TR_CTRL_CT_GO_MASK) >> FCSPI_TR_CTRL_CT_GO_SHIFT);
    ptCtrl->eRxDisable = (FCSPI_AtomicBoolType)
        ((u32Flag & FCSPI_TR_CTRL_RX_MSK_MASK) >> FCSPI_TR_CTRL_RX_MSK_SHIFT);
    ptCtrl->eTxDisable = (FCSPI_AtomicBoolType)
        ((u32Flag & FCSPI_TR_CTRL_TX_MSK_MASK) >> FCSPI_TR_CTRL_TX_MSK_SHIFT);
    ptCtrl->eTransferWidth = (FCSPI_TransferWidthType)
        ((u32Flag & FCSPI_TR_CTRL_WIDTH_MASK) >> FCSPI_TR_CTRL_WIDTH_SHIFT);
    ptCtrl->u16FrameBitCnt = (uint16_t)
        (((u32Flag & FCSPI_TR_CTRL_FRM_SZ_MASK) >> FCSPI_TR_CTRL_FRM_SZ_SHIFT)+1);
}
#endif

static FCSPI_StatusType FCSpi_Hw_SetTRCR(FCSPI_InstanceType eInst, FCSPI_TxRxCtrlType *ptCtrl)
{
    uint32_t         u32Flag = 0U;
    FCSPI_StatusType eRet    = FCSPI_STATUS_SUCCESS;

    if ((ptCtrl->u16FrameBitCnt < ((uint16_t)8)) ||
         (((uint16_t)0) != (ptCtrl->u16FrameBitCnt & ((uint16_t)0x1))))
    {
        eRet = FCSPI_STATUS_PARAM_ERR;
    }
    else
    {
        u32Flag |= (((uint32_t)(ptCtrl->eSckPolarity))     << FCSPI_TR_CTRL_SCK_POL_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eSckPhase))        << FCSPI_TR_CTRL_SCK_PHA_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->ePrescalerValue))  << FCSPI_TR_CTRL_PRESCALE_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->ePCSSelect))       << FCSPI_TR_CTRL_PCS_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eBitFirstOrder))   << FCSPI_TR_CTRL_LSBF_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eByteSwap))        << FCSPI_TR_CTRL_BYSW_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eContTransEnable)) << FCSPI_TR_CTRL_CT_EN_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eContCmdEnable))   << FCSPI_TR_CTRL_CT_GO_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eRxDisable))       << FCSPI_TR_CTRL_RX_MSK_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eTxDisable))       << FCSPI_TR_CTRL_TX_MSK_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eTransferWidth))   << FCSPI_TR_CTRL_WIDTH_SHIFT);
        u32Flag |= (((uint32_t)((uint16_t)(ptCtrl->u16FrameBitCnt - (uint16_t)1))) << FCSPI_TR_CTRL_FRM_SZ_SHIFT);

        FCSPI_HWA_SetTxRxControl(s_atFCSpiInfo[eInst].tFCSpiInstance, u32Flag);
    }

    return eRet;
}

/* caution:write TR_CTRL */
static void FCSpi_Hw_SelectUsePcs(FCSPI_InstanceType eInst, FCSPI_PCSType ePCS)
{
    uint32_t u32Flag = FCSPI_HWA_GetTxRxControl(s_atFCSpiInfo[eInst].tFCSpiInstance);

    u32Flag &= (~(FCSPI_TR_CTRL_PCS_MASK));
    u32Flag |= (((uint32_t)ePCS)  << FCSPI_TR_CTRL_PCS_SHIFT);

    FCSPI_HWA_SetTxRxControl(s_atFCSpiInfo[eInst].tFCSpiInstance, u32Flag);
}

static FCSPI_PrescaleValueType FCSpi_Hw_GetRegPrescalerVal(FCSPI_InstanceType eInst)
{
    return (FCSPI_PrescaleValueType)((FCSPI_HWA_GetTxRxControl(s_atFCSpiInfo[eInst].tFCSpiInstance) &
            FCSPI_TR_CTRL_PRESCALE_MASK) >> FCSPI_TR_CTRL_PRESCALE_SHIFT);
}

/* caution:write TR_CTRL */
static void FCSpi_Hw_SetContinuousCommand(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType eEnable)
{
    uint32_t u32Flag = FCSPI_HWA_GetTxRxControl(s_atFCSpiInfo[eInst].tFCSpiInstance);

    u32Flag &= (~(FCSPI_TR_CTRL_CT_GO_MASK));
    u32Flag |= (((uint32_t)eEnable)  << FCSPI_TR_CTRL_CT_GO_SHIFT);

    FCSPI_HWA_SetTxRxControl(s_atFCSpiInfo[eInst].tFCSpiInstance, u32Flag);
}

#ifdef   FCSPI_DRV_INTERNAL_FUNC_EN
static uint32_t FCSpi_Hw_ReadRxFifoFirstEntry(FCSPI_InstanceType eInst)
{
    return FCSPI_HWA_ReadData(s_atFCSpiInfo[eInst].tFCSpiInstance);
}
#endif

#ifdef   FCSPI_DRV_INTERNAL_FUNC_EN
static void FCSpi_Hw_WriteDataToTxFifo(FCSPI_InstanceType eInst, uint32_t u32TxData)
{
    FCSPI_HWA_WriteData(s_atFCSpiInfo[eInst].tFCSpiInstance, u32TxData);
}
#endif

/*
 * Before call this function, ensure the FCSPI is disabled and in MASTER mode.
 * Src Clk  -> Prescaler -> sck divider -> SCLK
 */
#define FCSPI_CAL_DISTANCE(x, y) ((x) > (y) ? ((x) - (y)) : ((y) - (x)))
typedef struct {
    uint32_t u32CacheTargetBps;
    uint32_t u32CacheSrcClkHz;
    uint32_t u32CachePrescaleRegVal;
    uint32_t u32CacheBps;
    uint32_t u32CacheSckDiv;
} FCSPI_BaundrateCacheType;
#define FCSPI_PCS_CLK_CACHE_CNT ((uint8_t)2)

/* Often use case, just set the same baundrate for specific external device linked with one FCSPI PCS */
static uint32_t FCSpi_Hw_Master_CalcBaudRate(const FCSPI_MasterCfgType *pCfg,
         uint32_t *pdwPrescaleRegVal, uint32_t *pdwActualSckDiv)
{
    uint32_t u32TargetBps = pCfg->u32BitCntPerSecond;
    uint32_t u32SrcClkHz  = pCfg->u32FCSpiSrcClk;
    uint32_t u32TestFreq = 0U;
    int16_t  s16TestSckDivRegVal = (int16_t)0;
    uint8_t  u8PrescalerRegVal = (uint8_t)0;
    int16_t  s16SckDivLow, s16SckDivHigh;
    uint32_t u32Prescale = 0U;
    uint32_t u32ActualBps = 0U;
    uint32_t u32ActualSckDiv = 0U;
    uint32_t u32ActualPrescaleRegVal = 0U;
    uint32_t u32ThisPrescaleBestBps    = 0U;
    uint32_t u32ThisPrescaleBestSckDiv = 0U;
    uint32_t u32AbsDistance1, u32AbsDistance2;
    uint8_t  u8Find  = (uint8_t)0;
    uint32_t u32Ret  = 0U;

    if (u32SrcClkHz < (u32TargetBps * 2U))
    {
        u32Ret = 0U;
    }
    else
    {
        if ((uint8_t)0 == u8Find)
        {
            u32ActualSckDiv = 0U;
            u32ActualPrescaleRegVal = 0U;
            u32ActualBps = (uint32_t)(u32SrcClkHz / ((uint32_t)((((uint32_t)1) <<
                u32ActualPrescaleRegVal) * (u32ActualSckDiv + (uint32_t)2U))));

            for (u8PrescalerRegVal = (uint8_t)0; u8PrescalerRegVal < FCSPI_PRESCALE_MAX; ++u8PrescalerRegVal)
            {
                s16SckDivLow  = (int16_t)0;

                if ((FCSPI_SCK_SAMPLE_SECOND_EDGE == pCfg->eSckSamplePhase) && /* sample the 2nd edge */
                    (FCSPI_FALSE != pCfg->eIsPcsContinuous)) /* continuous pcs */
                {
                    /* hw bug fix, sck must be 0 */
                    s16SckDivHigh = (int16_t)0;
                }
                else
                {
                    s16SckDivHigh = (int16_t)255;
                }

                u32Prescale = ((uint32_t)1) << u8PrescalerRegVal;
                u32ThisPrescaleBestSckDiv = 0U;
                u32ThisPrescaleBestBps    = (uint32_t)(u32SrcClkHz / ((uint32_t)(u32Prescale *
                            (u32ThisPrescaleBestSckDiv + (uint32_t)2U))));

                while(s16SckDivHigh > s16SckDivLow)
                {
                    s16TestSckDivRegVal = s16SckDivLow + s16SckDivHigh;
                    s16TestSckDivRegVal = (s16TestSckDivRegVal / (int16_t)2);
                    u32TestFreq = (uint32_t)(u32SrcClkHz /
                        ((uint32_t)(u32Prescale * ((uint32_t)s16TestSckDivRegVal + (uint32_t)2U))));

                    u32AbsDistance1 = FCSPI_CAL_DISTANCE(u32TargetBps, u32ThisPrescaleBestBps);
                    u32AbsDistance2 = FCSPI_CAL_DISTANCE(u32TargetBps, u32TestFreq);
                    if (u32AbsDistance1 > u32AbsDistance2)
                    {
                        u32ThisPrescaleBestBps = u32TestFreq;
                        u32ThisPrescaleBestSckDiv = (uint32_t)s16TestSckDivRegVal;
                    }

                    if (u32TestFreq == u32TargetBps)
                    {
                        break;
                    }
                    else if (u32TestFreq < u32TargetBps)
                    {
                        s16SckDivHigh = s16TestSckDivRegVal - 1;
                    }
                    else
                    {
                        s16SckDivLow  = s16TestSckDivRegVal + 1;
                    }
                }

                u32AbsDistance1 = FCSPI_CAL_DISTANCE(u32TargetBps, u32ActualBps);
                u32AbsDistance2 = FCSPI_CAL_DISTANCE(u32TargetBps, u32ThisPrescaleBestBps);
                if (u32AbsDistance1 > u32AbsDistance2)
                {
                    u32ActualBps = u32ThisPrescaleBestBps;
                    u32ActualSckDiv = u32ThisPrescaleBestSckDiv;
                    u32ActualPrescaleRegVal = u8PrescalerRegVal;
                }

                if(u32ThisPrescaleBestBps == u32TargetBps)
                {
                    break;
                }
            }

            if (0U != u32ActualBps)
            {
                if (NULL != pdwActualSckDiv)
                {
                    *pdwActualSckDiv = u32ActualSckDiv;
                }

                if (NULL != pdwPrescaleRegVal)
                {
                    *pdwPrescaleRegVal = u32ActualPrescaleRegVal;
                }
            }

            /* return the actual calculated baud rate */
            u32Ret = u32ActualBps;
        }
    }

    return u32Ret;
}

/* Master/Slave side all use */

static void fcspi_read_rx_fifo(FCSPI_InstanceType eInst)
{
    uint32_t u32RxWordData     = 0U;
    uint16_t u16ByteCount      = (uint16_t)0;
    uint8_t  u8ByteIndex       = (uint8_t)0;
    uint8_t  u8WordCntInRxFifo = FCSPI_HWA_GetRxFifoStoredCount(s_atFCSpiInfo[eInst].tFCSpiInstance);

    while (u8WordCntInRxFifo > (uint8_t)0)
    {
        u32RxWordData = FCSPI_HWA_ReadData(s_atFCSpiInfo[eInst].tFCSpiInstance);
        /* Get the number of bytes which can be read from this 32 bites */
        if (s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed <=
            (s_atFCSpiInfo[eInst].tFCSpiStat.u16RxGetByteCntOfCurFrame + (uint16_t)4))
        {
            u16ByteCount = (uint16_t)(s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed -
                                s_atFCSpiInfo[eInst].tFCSpiStat.u16RxGetByteCntOfCurFrame);
        }
        else
        {
            u16ByteCount = (uint16_t)4;
        }

        /* Generate the word which will be write in buffer. */
        for (u8ByteIndex = (uint8_t)0; u8ByteIndex < u16ByteCount; ++u8ByteIndex)
        {
            (s_atFCSpiInfo[eInst].tFCSpiStat.pbyRxBuff)[s_atFCSpiInfo[eInst].tFCSpiStat.u16RxIndex] =
                (uint8_t)((u32RxWordData >> (uint32_t)((uint32_t)u8ByteIndex * (uint32_t)8)) & (uint8_t)0xFF);
            (s_atFCSpiInfo[eInst].tFCSpiStat.u16RxIndex)++;
        }

        s_atFCSpiInfo[eInst].tFCSpiStat.u16RxGetByteCntOfCurFrame =
            (uint16_t)((s_atFCSpiInfo[eInst].tFCSpiStat.u16RxGetByteCntOfCurFrame +
                u16ByteCount) % s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed);

        /* Update internal variable used in transmission. */
        s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet =
            (uint16_t)(s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet - u16ByteCount);
        /* Verify if all bytes were sent. */
        if ((uint16_t)0 == s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet)
        {
            break;
        }

        u8WordCntInRxFifo--;
    }
}

static void fcspi_write_tx_fifo(FCSPI_InstanceType eInst)
{
    uint32_t u32DataToSend       = 0U;
    uint16_t u16ThisSendByteCnt  = (uint16_t)0;
    uint8_t  u8TxFifoFreeWordCnt = (uint8_t)(s_atFCSpiInfo[eInst].tFCSpiStat.u8TxFifoSize -
                                      (uint8_t)FCSPI_HWA_GetTxFifoStoredCount(s_atFCSpiInfo[eInst].tFCSpiInstance));
    uint16_t u16BytesTxLeft      = s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend;

    while ((u8TxFifoFreeWordCnt != (uint8_t)0) && ((uint16_t)0 != u16BytesTxLeft))
    {
        if (FCSPI_TRUE == s_atFCSpiInfo[eInst].tFCSpiStat.eIsPcsContinuous)
        {
            if((uint16_t)1 == s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend)
            {
                /* Disable continuous PCS */
                FCSpi_Hw_SetContinuousCommand(eInst, FCSPI_FALSE);
                s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend = (uint16_t)0;
                u16BytesTxLeft = (uint16_t)0;
                break;
            }
        }

        /* Get the number of bytes which can be written in a single 32 bits word. */
        if ((s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed -
                s_atFCSpiInfo[eInst].tFCSpiStat.u16TxSendByteCntOfCurFrame) <= (uint16_t)4)
        {
            u16ThisSendByteCnt = (uint16_t)(s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed -
                            s_atFCSpiInfo[eInst].tFCSpiStat.u16TxSendByteCntOfCurFrame);
        }
        else
        {
            u16ThisSendByteCnt = (uint16_t)4;
        }

        u32DataToSend = 0U;

        if (NULL != s_atFCSpiInfo[eInst].tFCSpiStat.pbyTxBuff)
        {
            switch(s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed)
            {
                case 1:
                    u32DataToSend = *((const uint8_t *)&(s_atFCSpiInfo[eInst].tFCSpiStat.pbyTxBuff[s_atFCSpiInfo[eInst].tFCSpiStat.u16TxIndex]));
                    s_atFCSpiInfo[eInst].tFCSpiStat.u16TxIndex += sizeof(uint8_t);
                    break;

                case 2:
                    u32DataToSend = *((const uint16_t *)&(s_atFCSpiInfo[eInst].tFCSpiStat.pbyTxBuff[s_atFCSpiInfo[eInst].tFCSpiStat.u16TxIndex]));
                    s_atFCSpiInfo[eInst].tFCSpiStat.u16TxIndex += sizeof(uint16_t);
                    break;

                default:
                    u32DataToSend = *((const uint32_t *)&(s_atFCSpiInfo[eInst].tFCSpiStat.pbyTxBuff[s_atFCSpiInfo[eInst].tFCSpiStat.u16TxIndex]));
                    s_atFCSpiInfo[eInst].tFCSpiStat.u16TxIndex += sizeof(uint32_t);
                    break;
            }

            s_atFCSpiInfo[eInst].tFCSpiStat.u16TxSendByteCntOfCurFrame =
                (uint16_t)((s_atFCSpiInfo[eInst].tFCSpiStat.u16TxSendByteCntOfCurFrame + u16ThisSendByteCnt) %
                                    s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed);
        }

        FCSPI_HWA_WriteData(s_atFCSpiInfo[eInst].tFCSpiInstance, u32DataToSend);
        /* Update internal variable used in transmission. */
        s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend -= u16ThisSendByteCnt;
        u16BytesTxLeft = s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend;
        u8TxFifoFreeWordCnt -= (uint8_t)1;
    }
}

/* MASTER side API */
/*----------------------------------------------------------------------------*/
/**
 * @brief Init the FCSpi instance as spi master side
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Configuration of the FCSpi, MUST NOT NULL
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_Master_Init(const FCSPI_InstanceType eInst, const FCSPI_MasterCfgType *pCfg)
{
    uint32_t           u32BaudRate       = 0U;
    uint32_t           u32PrescaleRegVal = 0U;
    uint32_t           u32SckDiv         = 0U;
    FCSPI_TxRxCtrlType tTxRxCtrlCfg;
    FCSPI_StatusType   eRet              = FCSPI_STATUS_SUCCESS;

    if (NULL != pCfg)
    {
        if ((pCfg->u16BitCountPerFrame >= (uint16_t)8) &&
            (pCfg->u16BitCountPerFrame <= (uint16_t)4096)) /* TR_CTRL[FRM_SZ] 12bits */
        {
            u32BaudRate = FCSpi_Hw_Master_CalcBaudRate(pCfg, &u32PrescaleRegVal, &u32SckDiv);
            if (0U != u32BaudRate)
            {
                FCSpi_Hw_Reset(eInst, FCSPI_FALSE, FCSPI_FALSE, FCSPI_TRUE);
                FCSPI_HWA_SetMasterMode(s_atFCSpiInfo[eInst].tFCSpiInstance);
                FCSpi_Hw_SetPcs_2_3_Mode(eInst, PCS2_3_PCS);
                FCSpi_Hw_SetPin(eInst, SIN_INPUT_SOUT_OUTPUT, PINOUT_RETAIN_LAST);

                /* set internal state parameters for spi */
                s_atFCSpiInfo[eInst].tFCSpiStat.u8TxFifoSize          = (uint8_t)FCSPI_DRV_TX_FIFO_WORD_CNT;
                s_atFCSpiInfo[eInst].tFCSpiStat.u8RxFifoSize          = (uint8_t)FCSPI_DRV_RX_FIFO_WORD_CNT;
                s_atFCSpiInfo[eInst].tFCSpiStat.u32DmaDummyData       = 0U;
                s_atFCSpiInfo[eInst].tFCSpiStat.u16BitsPerFrame       = pCfg->u16BitCountPerFrame;
                s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed  = (uint16_t)(((pCfg->u16BitCountPerFrame + (uint16_t)7)) >> (uint16_t)3);
                s_atFCSpiInfo[eInst].tFCSpiStat.eIsPcsContinuous      = pCfg->eIsPcsContinuous;
                s_atFCSpiInfo[eInst].tFCSpiStat.u32FCSpiSrcClk        = pCfg->u32FCSpiSrcClk;
                s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer         = FCSPI_FALSE;
                s_atFCSpiInfo[eInst].tFCSpiStat.eBitFirstOrder        = pCfg->eBitFirstOrder;
                s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc   = pCfg->eTransferTriggerSrc;
                s_atFCSpiInfo[eInst].tFCSpiStat.eSckPolarity          = pCfg->eSckPolarity;
                s_atFCSpiInfo[eInst].tFCSpiStat.eSckSamplePhase       = pCfg->eSckSamplePhase;
                s_atFCSpiInfo[eInst].tFCSpiStat.ePcs                  = pCfg->ePcs;
                s_atFCSpiInfo[eInst].tFCSpiStat.ePcsPolarity          = pCfg->ePcsPolarity;
                s_atFCSpiInfo[eInst].tFCSpiStat.u32Baundrate          = u32BaudRate;

                /* DMA require frames of 3 bytes per frame handled as 4 bytes per frame. */
                if (s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed == (uint16_t)3)
                {
                    s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed = (uint16_t)4;
                }
                /* 4 bytes align requirement when > 32bits */
                if (s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed > (uint16_t)4)
                {
                    s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed =
                        ((((s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed + (uint16_t)3)) >> (uint16_t)2)) << (uint16_t)2;
                }

                s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf  = pCfg->tTriggerDmaInf;
                s_atFCSpiInfo[eInst].tFCSpiStat.pStopNotifyCb   = pCfg->pStopNotifyCb;
                s_atFCSpiInfo[eInst].tFCSpiStat.pSemaResetCb    = pCfg->pSemaResetCb;
                s_atFCSpiInfo[eInst].tFCSpiStat.pSemaTakeCb     = pCfg->pSemaTakeCb;
                s_atFCSpiInfo[eInst].tFCSpiStat.pSemaPostCb     = pCfg->pSemaPostCb;

                /* Configure the desired PCS polarity */
                FCSpi_Hw_SetOnePcsPolarity(eInst, pCfg->ePcs, pCfg->ePcsPolarity);

                /* enable sample delay */
                FCSpi_Hw_Master_SetSckLoopbackSample(eInst, FCSPI_TRUE);

                /* set up the baudrate */
                FCSpi_Hw_Set_SCK_PCS_DIV_Hold(eInst,
                    (uint8_t)(u32SckDiv >> 2U),
                    (uint8_t)(u32SckDiv >> 2U),
                    (uint8_t)(u32SckDiv >> 2U),
                    (uint8_t)u32SckDiv); /* write best baudrate scaler to SCKDIV */

                /* Write the TCR for this transfer. */
                tTxRxCtrlCfg.eSckPolarity       = pCfg->eSckPolarity;
                tTxRxCtrlCfg.eSckPhase          = pCfg->eSckSamplePhase;
                tTxRxCtrlCfg.ePrescalerValue    = (FCSPI_PrescaleValueType)u32PrescaleRegVal;
                tTxRxCtrlCfg.ePCSSelect         = pCfg->ePcs;
                tTxRxCtrlCfg.eBitFirstOrder     = pCfg->eBitFirstOrder;
                tTxRxCtrlCfg.eByteSwap          = FCSPI_FALSE;
                tTxRxCtrlCfg.eContTransEnable   = pCfg->eIsPcsContinuous;
                tTxRxCtrlCfg.eContCmdEnable     = FCSPI_FALSE;
                tTxRxCtrlCfg.eRxDisable         = FCSPI_FALSE;
                tTxRxCtrlCfg.eTxDisable         = FCSPI_FALSE;
                tTxRxCtrlCfg.eTransferWidth     = FCSPI_TRANSFER_1_BIT;
                tTxRxCtrlCfg.u16FrameBitCnt     = pCfg->u16BitCountPerFrame;
                eRet = FCSpi_Hw_SetTRCR(eInst, &tTxRxCtrlCfg);

                if (FCSPI_STATUS_SUCCESS == eRet)
                {
                    if (FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL != pCfg->eTransferTriggerSrc)
                    {
                        IntMgr_EnableInterrupt(s_atFCSpiInfo[eInst].eFCSpiIrq);
                    }

                    FCSPI_HWA_ModuleEnable(s_atFCSpiInfo[eInst].tFCSpiInstance);
                }
                else
                {
                    eRet = FCSPI_STATUS_ERROR;
                }
            }
            else
            {
                eRet = FCSPI_STATUS_ERROR;
            }
        }
        else
        {
            eRet = FCSPI_STATUS_PARAM_ERR;
        }
    }
    else
    {
        eRet = FCSPI_STATUS_PARAM_ERR;
    }

    return eRet;
}

/**
 * @brief Deinit the FCSpi
 *
 * @param eInst Which FCSpi Hardware instance
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when deinit the FCSpi successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Deinit(const FCSPI_InstanceType eInst)
{
    FCSPI_StatusType eRet = FCSPI_STATUS_SUCCESS;

    if (FCSPI_TRUE != s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer)
    {
        /* reset registers,  disabling spi module */
        FCSpi_Hw_Reset(eInst, FCSPI_FALSE, FCSPI_FALSE, FCSPI_TRUE);
    }
    else
    {
        eRet = FCSPI_STATUS_BUSY;
    }

    return eRet;
}

/**
 * @brief Configure the holding time (in us) between PCS and SCK
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Configure the delay parameters between PCS and SCK, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Master_SetSckPcsHoldTime(const FCSPI_InstanceType eInst,
                                    const FCSPI_MasterSckPcsHoldTimeType *pCfg)
{
    FCSPI_StatusType        eStat         = FCSPI_STATUS_SUCCESS;
    uint32_t                u32PCSPCSCycle,
                            u32SCKPCSCycle,
                            u32PCSSCKCycle;
    FCSPI_PrescaleValueType ePrescaler;
    uint32_t                u32PrescaleValue;
    uint32_t                u32ClkAfterScalePerUs;

    if (NULL != pCfg)
    {
        /* disable FCSPI first */
        eStat = FCSpi_Hw_Disable(eInst);
        if (FCSPI_STATUS_SUCCESS == eStat)
        {
            ePrescaler = FCSpi_Hw_GetRegPrescalerVal(eInst);
            u32PrescaleValue = FCSpi_Hw_PrescalerRegToActualVal(ePrescaler);
            if (0U != u32PrescaleValue) /* actually unreachable */
            {
                u32ClkAfterScalePerUs = (uint32_t)(s_atFCSpiInfo[eInst].tFCSpiStat.u32FCSpiSrcClk /
                                        u32PrescaleValue / (uint32_t)1000000);
                u32PCSPCSCycle = pCfg->u32PCStoPCSHoldUs * u32ClkAfterScalePerUs;
                u32SCKPCSCycle = pCfg->u32SCKtoPCSHoldUs * u32ClkAfterScalePerUs;
                u32PCSSCKCycle = pCfg->u32PCStoSCKHoldUs * u32ClkAfterScalePerUs;

                if (u32PCSPCSCycle > (uint32_t)257U)
                {
                    u32PCSPCSCycle = (uint32_t)257U;
                }

                if(u32SCKPCSCycle > (uint32_t)256U)
                {
                    u32SCKPCSCycle = (uint32_t)256U;
                }

                if(u32PCSSCKCycle > (uint32_t)256U)
                {
                    u32PCSSCKCycle = (uint32_t)256U;
                }

                if (u32PCSPCSCycle < (uint32_t)2U)
                {
                    u32PCSPCSCycle = (uint32_t)2U;
                }

                if(u32SCKPCSCycle == (uint32_t)0)
                {
                    u32SCKPCSCycle = (uint32_t)1U;
                }

                if(u32PCSSCKCycle == (uint32_t)0U)
                {
                    u32PCSSCKCycle = (uint32_t)1U;
                }

                FCSpi_Hw_Set_SCK_PCS_Hold(eInst,
                    (uint8_t)(u32SCKPCSCycle - 1U),
                    (uint8_t)(u32PCSSCKCycle - 1U),
                    (uint8_t)(u32PCSPCSCycle - 2U));
                /* Enable module */
                FCSPI_HWA_ModuleEnable(s_atFCSpiInfo[eInst].tFCSpiInstance);
            }
            else
            {
                eStat = FCSPI_STATUS_ERROR;
            }
        }
        else
        {
            eStat = FCSPI_STATUS_BUSY;
        }
    }
    else
    {
        eStat = FCSPI_STATUS_PARAM_ERR;
    }

    return eStat;
}

/**
 * @brief Configure the holding time (in SCK/100) between PCS and SCK
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Configure the delay parameters between PCS and SCK, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Master_SetSckPcsHoldSckPercentage(
    const FCSPI_InstanceType eInst, const FCSPI_MasterSckPcsHoldSckCycleType *pCfg)
{
    uint8_t             u8PCSPCSCycle;
    uint8_t             u8SCKPCSCycle;
    uint8_t             u8PCSSCKCycle;
    uint8_t             u8SckDiv;
    FCSPI_StatusType    eRet = FCSPI_STATUS_SUCCESS;

    if (NULL != pCfg)
    {
        /* disable FCSPI first */
        eRet = FCSpi_Hw_Disable(eInst);
        if (FCSPI_STATUS_SUCCESS == eRet)
        {
            FCSpi_Hw_Get_SCK_PCS_DIV_Hold(eInst, NULL, NULL, NULL, &u8SckDiv);

            u8PCSPCSCycle = (uint8_t)((uint32_t)pCfg->u32PCStoPCSHoldPercentage *
                                      (uint32_t)u8SckDiv / (uint32_t)100);
            u8SCKPCSCycle = (uint8_t)((uint32_t)pCfg->u32SCKtoPCSHoldPercentage *
                                      (uint32_t)u8SckDiv / (uint32_t)100);
            u8PCSSCKCycle = (uint8_t)((uint32_t)pCfg->u32PCStoSCKHoldPercentage *
                                      (uint32_t)u8SckDiv / (uint32_t)100);

            if (u8PCSPCSCycle < (uint8_t)2)
            {
                u8PCSPCSCycle = (uint8_t)2;
            }

            if(u8SCKPCSCycle == (uint8_t)0)
            {
                u8SCKPCSCycle = (uint8_t)1;
            }

            if(u8PCSSCKCycle == (uint8_t)0)
            {
                u8PCSSCKCycle = (uint8_t)1;
            }

            FCSpi_Hw_Set_SCK_PCS_Hold(eInst,
                (uint8_t)(u8SCKPCSCycle - (uint8_t)1),
                (uint8_t)(u8PCSSCKCycle - (uint8_t)1),
                (uint8_t)(u8PCSPCSCycle - (uint8_t)2));
            /* Enable module */
            FCSPI_HWA_ModuleEnable(s_atFCSpiInfo[eInst].tFCSpiInstance);
        }
        else
        {
            eRet = FCSPI_STATUS_BUSY;
        }
    }
    else
    {
        eRet = FCSPI_STATUS_PARAM_ERR;
    }

    return eRet;
}

/**
 * @brief Select the PCS to use and configure
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Parameters about PCS configuration, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Master_SelectPcs(
    const FCSPI_InstanceType eInst, const FCSPI_MasterPcsConfType *pCfg)
{
    FCSPI_StatusType eRet = FCSPI_STATUS_SUCCESS;

    if (pCfg)
    {
        eRet = FCSpi_Hw_Disable(eInst);
        if (FCSPI_STATUS_SUCCESS == eRet)
        {
            FCSpi_Hw_SetOnePcsPolarity(eInst, pCfg->ePcs, pCfg->ePolarity);
            FCSPI_HWA_ModuleEnable(s_atFCSpiInfo[eInst].tFCSpiInstance);
            FCSpi_Hw_SelectUsePcs(eInst, pCfg->ePcs);
        }
        else
        {
            eRet = FCSPI_STATUS_BUSY;
        }
    }
    else
    {
        eRet = FCSPI_STATUS_PARAM_ERR;
    }

    return eRet;
}

static void fcspi_master_clean_transfer(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInInterrupt)
{
    s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer = FCSPI_FALSE;

    if (FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR == s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc)
    {
        FCSpi_Hw_SetRxTxDmaEnableStatus(eInst, FCSPI_FALSE, FCSPI_FALSE);
    }
    else
    {
        FCSpi_Hw_DisableSomeInterrupts(eInst,
            FCSPI_INT_EN_RFIE(1) | FCSPI_INT_EN_TFIE(1));
    }

    FCSpi_Hw_DisableSomeInterrupts(eInst,
        FCSPI_INT_EN_RFOIE(1) | FCSPI_INT_EN_TFUIE(1) | FCSPI_INT_EN_TCIE(1));
    FCSpi_Hw_ClearSomeStatusW1CFlag(eInst,
        FCSPI_STATUS_RX_FO(1) | FCSPI_STATUS_TX_FU(1) | FCSPI_STATUS_TCF(1));

    if (FCSPI_TRUE == bIsInInterrupt)
    {
        if (NULL != s_atFCSpiInfo[eInst].tFCSpiStat.pStopNotifyCb)
        {
            s_atFCSpiInfo[eInst].tFCSpiStat.pStopNotifyCb(eInst, FCSPI_TRUE);
        }

        if (s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore)
        {
            s_atFCSpiInfo[eInst].tFCSpiStat.pSemaPostCb(eInst, FCSPI_TRUE);
            s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore = (uint8_t)0;
        }
    }
    else
    {
        if (NULL != s_atFCSpiInfo[eInst].tFCSpiStat.pStopNotifyCb)
        {
            s_atFCSpiInfo[eInst].tFCSpiStat.pStopNotifyCb(eInst, FCSPI_FALSE);
        }

        if (s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore)
        {
            s_atFCSpiInfo[eInst].tFCSpiStat.pSemaPostCb(eInst, FCSPI_FALSE);
            s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore = (uint8_t)0;
        }
    }
}

static void fcspi_master_abort_transfer(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInISR)
{
    fcspi_master_clean_transfer(eInst, bIsInISR);

    /* clean the fifo */
    FCSpi_Hw_Reset(eInst, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE);
    FCSpi_Hw_Reset(eInst, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE); /* for shifter */
}

static  void fcspi_master_dma_rx_err_interrupt(FCSPI_InstanceType eInst)
{
    s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_RX_FAIL;
    fcspi_master_abort_transfer(eInst, FCSPI_TRUE);
}

static void fcspi_0_master_dma_rx_err_interrupt(void)
{
    fcspi_master_dma_rx_err_interrupt(FCSPI_0);
}

static void fcspi_1_master_dma_rx_err_interrupt(void)
{
    fcspi_master_dma_rx_err_interrupt(FCSPI_1);
}

static void fcspi_2_master_dma_rx_err_interrupt(void)
{
    fcspi_master_dma_rx_err_interrupt(FCSPI_2);
}

static void fcspi_3_master_dma_rx_err_interrupt(void)
{
    fcspi_master_dma_rx_err_interrupt(FCSPI_3);
}

static void fcspi_4_master_dma_rx_err_interrupt(void)
{
    fcspi_master_dma_rx_err_interrupt(FCSPI_4);
}

static void fcspi_5_master_dma_rx_err_interrupt(void)
{
    fcspi_master_dma_rx_err_interrupt(FCSPI_5);
}

static void fcspi_master_dma_rx_finish_interrupt(void)
{
    ; /* in master mode, the tx trigger the sclk output, so when rx finish, ignore. */
}

static  void fcspi_master_dma_tx_err_interrupt(FCSPI_InstanceType eInst)
{
    s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_TX_FAIL;
    fcspi_master_abort_transfer(eInst, FCSPI_TRUE);
}

static void fcspi_0_master_dma_tx_err_interrupt(void)
{
    fcspi_master_dma_tx_err_interrupt(FCSPI_0);
}

static void fcspi_1_master_dma_tx_err_interrupt(void)
{
    fcspi_master_dma_tx_err_interrupt(FCSPI_1);
}

static void fcspi_2_master_dma_tx_err_interrupt(void)
{
    fcspi_master_dma_tx_err_interrupt(FCSPI_2);
}

static void fcspi_3_master_dma_tx_err_interrupt(void)
{
   fcspi_master_dma_tx_err_interrupt(FCSPI_3);
}

static void fcspi_4_master_dma_tx_err_interrupt(void)
{
   fcspi_master_dma_tx_err_interrupt(FCSPI_4);
}

static void fcspi_5_master_dma_tx_err_interrupt(void)
{
   fcspi_master_dma_tx_err_interrupt(FCSPI_5);
}

static  void fcspi_master_dma_tx_finish_interrupt(FCSPI_InstanceType eInst)
{
    if (FCSPI_TRUE == s_atFCSpiInfo[eInst].tFCSpiStat.eIsPcsContinuous)
    {
        FCSpi_Hw_SetContinuousCommand(eInst, FCSPI_FALSE);
    }

    s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend = (uint16_t)0;
    s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet  = (uint16_t)0;

    /* DMA -> TX FIFO -> PIN, DMA send to tx fifo finish, enable tx fifo finish interrupt */
    FCSpi_Hw_EnableTransmitCompleteInterrupt(eInst);
}

static  void fcspi_0_master_dma_tx_finish_interrupt(void)
{
    fcspi_master_dma_tx_finish_interrupt(FCSPI_0);
}

static  void fcspi_1_master_dma_tx_finish_interrupt(void)
{
    fcspi_master_dma_tx_finish_interrupt(FCSPI_1);
}

static  void fcspi_2_master_dma_tx_finish_interrupt(void)
{
    fcspi_master_dma_tx_finish_interrupt(FCSPI_2);
}

static  void fcspi_3_master_dma_tx_finish_interrupt(void)
{
    fcspi_master_dma_tx_finish_interrupt(FCSPI_3);
}

static  void fcspi_4_master_dma_tx_finish_interrupt(void)
{
    fcspi_master_dma_tx_finish_interrupt(FCSPI_4);
}

static  void fcspi_5_master_dma_tx_finish_interrupt(void)
{
    fcspi_master_dma_tx_finish_interrupt(FCSPI_5);
}

/* if enter transfer state, return success, others, not start tranfer */
static FCSPI_StatusType fcspi_master_async_transfer_bytes(FCSPI_InstanceType eInst,
    const uint8_t *pSendBuffer, uint8_t *pReceiveBuffer,
    uint16_t u16TransferByteCnt)
{
    DMA_InterruptCfgType tDmaTxInterruptCfg = {0};
    DMA_ChannelCfgType   tDmaTxChnlCfg      = {0};
    uint8_t              u8DmaTxBlkByteCnt  = (uint8_t)1;
    DMA_InterruptCfgType tDmaRxInterruptCfg = {0};
    DMA_ChannelCfgType   tDmaRxChnlCfg      = {0};
    uint8_t              u8DmaRxBlkByteCnt  = (uint8_t)1;
    FCSPI_StatusType     eRet               = FCSPI_STATUS_SUCCESS;
    uint32_t             u32StatRegVal      = 0u;

    if ((uint16_t)0 != s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed)
    {
        if ((uint16_t)0 != u16TransferByteCnt)
        {
            if ((u16TransferByteCnt % s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed) == (uint16_t)0)
            {
                u32StatRegVal = FCSPI_HWA_GetStatus(s_atFCSpiInfo[eInst].tFCSpiInstance);
                if ((FCSPI_TRUE != s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer) &&
                    (!FCSpi_Hw_ChkBusy(u32StatRegVal)))
                {
                    if (!FCSpi_Hw_ChkBusy(FCSPI_HWA_GetStatus(s_atFCSpiInfo[eInst].tFCSpiInstance)))
                    {
                         FCSpi_Hw_Reset(eInst, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE);
                         FCSpi_Hw_Reset(eInst, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE); /* ensure clear data in shifter */

                         /* if pcs need continuous, set command continuous bit */
                         if (s_atFCSpiInfo[eInst].tFCSpiStat.eIsPcsContinuous)
                         {
                             FCSpi_Hw_SetContinuousCommand(eInst, FCSPI_TRUE);
                         }

                         s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_OK;

                         FCSPI_HWA_SetWatermark(s_atFCSpiInfo[eInst].tFCSpiInstance,  (uint8_t)0,  (uint8_t)2);

                         FCSpi_Hw_ClearSomeStatusW1CFlag(eInst, FCSPI_DRV_STATUS_REG_W1C_U32);
                         FCSpi_Hw_EnableMoreInterrupts(eInst, FCSPI_INT_EN_TFUIE(1));

                         /* if rx needed, enable overflow interrupt and rx */
                         if (NULL != pReceiveBuffer)
                         {
                             FCSpi_Hw_EnableMoreInterrupts(eInst, FCSPI_INT_EN_RFOIE(1));
                             s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet = u16TransferByteCnt;
                             FCSPI_HWA_EnableRxDataMask(s_atFCSpiInfo[eInst].tFCSpiInstance, FCSPI_TRUE);
                         }
                         else
                         {
                             s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet = (uint16_t)0;
                             FCSPI_HWA_EnableRxDataMask(s_atFCSpiInfo[eInst].tFCSpiInstance, FCSPI_FALSE);
                         }

                         if (FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR == s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc)
                         {
                            /* TX */
                            tDmaTxChnlCfg.u8ChannelPriority     = s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8TxDMAChannelPriority;
                            tDmaTxChnlCfg.bDestAddrLoopbackEn   = false;
                            tDmaTxChnlCfg.bSrcAddrLoopbackEn    = false;
                            tDmaTxChnlCfg.bAutoStop             = true; /* auto stop dma after send finish */
                            tDmaTxChnlCfg.bSrcCircularBufferEn  = false;
                            tDmaTxChnlCfg.bDestCircularBufferEn = false;

                            switch (s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed)
                            {
                                case 1:
                                    tDmaTxChnlCfg.eSrcDataSize          = DMA_TRANSFER_SIZE_1B;
                                    tDmaTxChnlCfg.eDestDataSize         = DMA_TRANSFER_SIZE_1B;
                                    tDmaTxChnlCfg.bSrcBlockOffsetEn     = true;
                                    tDmaTxChnlCfg.s32BlockOffset        = (int32_t)1;
                                    u8DmaTxBlkByteCnt                   = (uint8_t)1;
                                    break;

                                case 2:
                                    tDmaTxChnlCfg.eSrcDataSize          = DMA_TRANSFER_SIZE_2B;
                                    tDmaTxChnlCfg.eDestDataSize         = DMA_TRANSFER_SIZE_2B;
                                    tDmaTxChnlCfg.bSrcBlockOffsetEn     = true;
                                    tDmaTxChnlCfg.s32BlockOffset        = (int32_t)2;
                                    u8DmaTxBlkByteCnt                   = (uint8_t)2;
                                    break;

                                default:
                                    tDmaTxChnlCfg.eSrcDataSize          = DMA_TRANSFER_SIZE_4B;
                                    tDmaTxChnlCfg.eDestDataSize         = DMA_TRANSFER_SIZE_4B;
                                    tDmaTxChnlCfg.bSrcBlockOffsetEn     = true;
                                    tDmaTxChnlCfg.s32BlockOffset        = (int32_t)4;
                                    u8DmaTxBlkByteCnt                   = (uint8_t)4;
                                    break;
                            }

                            tDmaTxChnlCfg.u16BlockCount      = u16TransferByteCnt / u8DmaTxBlkByteCnt;
                            tDmaTxChnlCfg.bDestBlockOffsetEn = false;

                            tDmaTxInterruptCfg.bTransferCompleteIntEn = true;
                            tDmaTxInterruptCfg.bTransferErrorIntEn    = true;
                            switch (eInst)
                            {
                                case FCSPI_0:
                                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI0_TX;
                                    tDmaTxInterruptCfg.pTransferCompleteNotify = fcspi_0_master_dma_tx_finish_interrupt;
                                    tDmaTxInterruptCfg.pTransferErrorNotify = fcspi_0_master_dma_tx_err_interrupt;
                                    break;

                                case FCSPI_1:
                                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI1_TX;
                                    tDmaTxInterruptCfg.pTransferCompleteNotify = fcspi_1_master_dma_tx_finish_interrupt;
                                    tDmaTxInterruptCfg.pTransferErrorNotify = fcspi_1_master_dma_tx_err_interrupt;
                                    break;

                                case FCSPI_2:
                                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI2_TX;
                                    tDmaTxInterruptCfg.pTransferCompleteNotify = fcspi_2_master_dma_tx_finish_interrupt;
                                    tDmaTxInterruptCfg.pTransferErrorNotify = fcspi_2_master_dma_tx_err_interrupt;
                                    break;

                                case FCSPI_3:
                                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_TX;
                                    tDmaTxInterruptCfg.pTransferCompleteNotify = fcspi_3_master_dma_tx_finish_interrupt;
                                    tDmaTxInterruptCfg.pTransferErrorNotify = fcspi_3_master_dma_tx_err_interrupt;
                                    break;

                                case FCSPI_4:
                                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI4_TX;
                                    tDmaTxInterruptCfg.pTransferCompleteNotify = fcspi_4_master_dma_tx_finish_interrupt;
                                    tDmaTxInterruptCfg.pTransferErrorNotify = fcspi_4_master_dma_tx_err_interrupt;
                                    break;

                                case FCSPI_5:
                                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI5_TX;
                                    tDmaTxInterruptCfg.pTransferCompleteNotify = fcspi_5_master_dma_tx_finish_interrupt;
                                    tDmaTxInterruptCfg.pTransferErrorNotify = fcspi_5_master_dma_tx_err_interrupt;
                                    break;

                                default:
                                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_TX;
                                    tDmaTxInterruptCfg.pTransferCompleteNotify = fcspi_3_master_dma_tx_finish_interrupt;
                                    tDmaTxInterruptCfg.pTransferErrorNotify = fcspi_3_master_dma_tx_err_interrupt;
                                    break;
                            }

                            tDmaTxChnlCfg.eDestIncMode = DMA_INCREMENT_DISABLE;
                            tDmaTxChnlCfg.eSrcIncMode  = DMA_INCREMENT_DISABLE;
                            tDmaTxChnlCfg.pDestBuffer  = FCSPI_HWA_GetTxDataAddr(s_atFCSpiInfo[eInst].tFCSpiInstance);
                            tDmaTxChnlCfg.u32BlockSize = (uint32_t)u8DmaTxBlkByteCnt;

                            if (NULL != pSendBuffer)
                            {
                            	tDmaTxChnlCfg.pSrcBuffer = pSendBuffer;
                            }
                            else
                            {
                            	tDmaTxChnlCfg.pSrcBuffer = &(s_atFCSpiInfo[eInst].tFCSpiStat.u32DmaDummyData);
                                tDmaTxChnlCfg.bSrcBlockOffsetEn = false; /* if send buffer is NULL, just send dummy data, MUST fix the source to the dummy variable */
                                tDmaTxChnlCfg.s32BlockOffset    = (int32_t)0;
                            }

                            DMA_InitChannel(s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.eDMAInstance, (DMA_ChannelType)s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8TxDMAChannel, &tDmaTxChnlCfg);

                            /* RX */
                            /* if needed, configure the DMA Rx function */
                            if (NULL != pReceiveBuffer)
                            {
                                tDmaRxChnlCfg.u8ChannelPriority     = s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8RxDMAChannelPriority;
                                tDmaRxChnlCfg.bDestAddrLoopbackEn   = false;
                                tDmaRxChnlCfg.bSrcAddrLoopbackEn    = false;
                                tDmaRxChnlCfg.bAutoStop             = true; /* auto stop dma after send finish */
                                tDmaRxChnlCfg.bSrcCircularBufferEn  = false;
                                tDmaRxChnlCfg.bDestCircularBufferEn = false;

                                switch (s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed)
                                {
                                    case 1:
                                        tDmaRxChnlCfg.eDestDataSize          = DMA_TRANSFER_SIZE_1B;
                                        tDmaRxChnlCfg.eSrcDataSize           = DMA_TRANSFER_SIZE_1B;
                                        tDmaRxChnlCfg.bDestBlockOffsetEn     = true;
                                        tDmaRxChnlCfg.s32BlockOffset         = (int32_t)1;
                                        u8DmaRxBlkByteCnt                    = (uint8_t)1;
                                        break;

                                    case 2:
                                        tDmaRxChnlCfg.eDestDataSize          = DMA_TRANSFER_SIZE_2B;
                                        tDmaRxChnlCfg.eSrcDataSize           = DMA_TRANSFER_SIZE_2B;
                                        tDmaRxChnlCfg.bDestBlockOffsetEn     = true;
                                        tDmaRxChnlCfg.s32BlockOffset         = (int32_t)2;
                                        u8DmaRxBlkByteCnt                    = (uint8_t)2;
                                        break;

                                    default:
                                        tDmaRxChnlCfg.eDestDataSize          = DMA_TRANSFER_SIZE_4B;
                                        tDmaRxChnlCfg.eSrcDataSize           = DMA_TRANSFER_SIZE_4B;
                                        tDmaRxChnlCfg.bDestBlockOffsetEn     = true;
                                        tDmaRxChnlCfg.s32BlockOffset         = (int32_t)4;
                                        u8DmaRxBlkByteCnt                    = (uint8_t)4;
                                        break;
                                }

                                tDmaRxChnlCfg.u16BlockCount      = u16TransferByteCnt / u8DmaRxBlkByteCnt;
                                tDmaRxChnlCfg.bSrcBlockOffsetEn  = false;

                                tDmaRxInterruptCfg.bTransferCompleteIntEn = true;
                                tDmaRxInterruptCfg.bTransferErrorIntEn    = true;
                                switch (eInst)
                                {
                                    case FCSPI_0:
                                        tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI0_RX;
                                        tDmaRxInterruptCfg.pTransferCompleteNotify = fcspi_master_dma_rx_finish_interrupt;
                                        tDmaRxInterruptCfg.pTransferErrorNotify = fcspi_0_master_dma_rx_err_interrupt;
                                        break;

                                    case FCSPI_1:
                                        tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI1_RX;
                                        tDmaRxInterruptCfg.pTransferCompleteNotify = fcspi_master_dma_rx_finish_interrupt;
                                        tDmaRxInterruptCfg.pTransferErrorNotify = fcspi_1_master_dma_rx_err_interrupt;
                                        break;

                                    case FCSPI_2:
                                        tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI2_RX;
                                        tDmaRxInterruptCfg.pTransferCompleteNotify = fcspi_master_dma_rx_finish_interrupt;
                                        tDmaRxInterruptCfg.pTransferErrorNotify = fcspi_2_master_dma_rx_err_interrupt;
                                        break;

                                    case FCSPI_3:
                                        tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_RX;
                                        tDmaRxInterruptCfg.pTransferCompleteNotify = fcspi_master_dma_rx_finish_interrupt;
                                        tDmaRxInterruptCfg.pTransferErrorNotify = fcspi_3_master_dma_rx_err_interrupt;
                                        break;

                                    case FCSPI_4:
                                        tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI4_RX;
                                        tDmaRxInterruptCfg.pTransferCompleteNotify = fcspi_master_dma_rx_finish_interrupt;
                                        tDmaRxInterruptCfg.pTransferErrorNotify = fcspi_4_master_dma_rx_err_interrupt;
                                        break;

                                    case FCSPI_5:
                                        tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI5_RX;
                                        tDmaRxInterruptCfg.pTransferCompleteNotify = fcspi_master_dma_rx_finish_interrupt;
                                        tDmaRxInterruptCfg.pTransferErrorNotify = fcspi_5_master_dma_rx_err_interrupt;
                                        break;

                                    default:
                                        tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_RX;
                                        tDmaRxInterruptCfg.pTransferCompleteNotify = fcspi_master_dma_rx_finish_interrupt;
                                        tDmaRxInterruptCfg.pTransferErrorNotify = fcspi_3_master_dma_rx_err_interrupt;
                                        break;
                                }

                                tDmaRxChnlCfg.eDestIncMode = DMA_INCREMENT_DISABLE;
                                tDmaRxChnlCfg.eSrcIncMode  = DMA_INCREMENT_DISABLE;
                                tDmaRxChnlCfg.pSrcBuffer   = FCSPI_HWA_GetRxDataAddr(s_atFCSpiInfo[eInst].tFCSpiInstance);
                                tDmaRxChnlCfg.u32BlockSize = (uint32_t)u8DmaRxBlkByteCnt;
                                tDmaRxChnlCfg.pDestBuffer = pReceiveBuffer;

                                DMA_InitChannel(s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.eDMAInstance, 
                                                   (DMA_ChannelType)s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8RxDMAChannel, &tDmaRxChnlCfg);
                                DMA_InitChannelInterrupt(s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.eDMAInstance, 
                                                            (DMA_ChannelType)s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8RxDMAChannel, &tDmaRxInterruptCfg);
                                DMA_StartChannel(s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.eDMAInstance, 
                                                    (DMA_ChannelType)s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8RxDMAChannel);
                            }

                            DMA_InitChannelInterrupt(s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.eDMAInstance, 
                                                     (DMA_ChannelType)s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8TxDMAChannel, &tDmaTxInterruptCfg);

                            DMA_StartChannel(s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.eDMAInstance, 
                                                 (DMA_ChannelType)s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8TxDMAChannel);

                            s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer = FCSPI_TRUE;

                            if (pReceiveBuffer)
                            {
                                FCSpi_Hw_SetRxTxDmaEnableStatus(eInst, FCSPI_TRUE, FCSPI_TRUE);
                            }
                            else
                            {
                                /* only enable TX DMA */
                                FCSpi_Hw_SetRxTxDmaEnableStatus(eInst, FCSPI_FALSE, FCSPI_TRUE);
                            }
                         }
                         else
                         {
                             s_atFCSpiInfo[eInst].tFCSpiStat.pbyTxBuff                  = pSendBuffer;
                             s_atFCSpiInfo[eInst].tFCSpiStat.pbyRxBuff                  = pReceiveBuffer;
                             s_atFCSpiInfo[eInst].tFCSpiStat.u16TxIndex                 = (uint16_t)0;
                             s_atFCSpiInfo[eInst].tFCSpiStat.u16RxIndex                 = (uint16_t)0;
                             s_atFCSpiInfo[eInst].tFCSpiStat.u16TxSendByteCntOfCurFrame = (uint16_t)0;
                             s_atFCSpiInfo[eInst].tFCSpiStat.u16RxGetByteCntOfCurFrame  = (uint16_t)0;
                             s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend   = u16TransferByteCnt;
                             if (FCSPI_TRUE == s_atFCSpiInfo[eInst].tFCSpiStat.eIsPcsContinuous)
                             {
                                 /* continuous transfer need an extra word to negate PCS */
                                 s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend++;
                             }
                             s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer = FCSPI_TRUE;

                             if (NULL != pReceiveBuffer) /* need rx fifo */
                             {
                                 FCSpi_Hw_EnableMoreInterrupts(eInst, FCSPI_INT_EN_RFIE(1) | FCSPI_INT_EN_TFIE(1));
                             }
                             else
                             {
                                 FCSpi_Hw_EnableMoreInterrupts(eInst, FCSPI_INT_EN_TFIE(1));
                             }
                         }
                         eRet = FCSPI_STATUS_SUCCESS;
                    }
                    else
                    {
                        eRet = FCSPI_STATUS_BUSY;
                    }
                }
                else
                {
                    eRet = FCSPI_STATUS_BUSY;
                }
            }
            else
            {
                eRet = FCSPI_STATUS_ERROR;
            }
        }
        else
        {
            eRet = FCSPI_STATUS_NO_DATA;
        }
    }
    else
    {
        eRet = FCSPI_STATUS_ERROR;
    }

    return eRet;
}

/**
 * @brief Send and receive asynchronously
 * 1) If the trigger source is driver user poll, this api not support this mode.
 * 2) If the trigger source is interrupt or DMA, this api will start the transmission, then return immediately.
 *    After transmission stop, it will trigger an interrupt.
 *    During the transmission, the send data buffer and receive data buffer
 *    should keep valid until the transmission stop.
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg the data information, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when start transfer successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_AsyncTransfer(const FCSPI_InstanceType eInst, const FCSPI_AsyncDataInfType *pCfg)
{
    FCSPI_StatusType eRet = FCSPI_STATUS_SUCCESS;

    if (NULL != pCfg)
    {
        if (FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL != s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc)
        {
            if (FCSPI_MODE_MASTER == FCSPI_HWA_CheckMode(s_atFCSpiInfo[eInst].tFCSpiInstance))
            {
                eRet = fcspi_master_async_transfer_bytes(eInst,
                    pCfg->pSendBuffer, pCfg->pReceiveBuffer,
                    pCfg->u16FrameCount * s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed);
            }
            else
            {
                eRet = fcspi_slave_async_transfer_bytes(eInst, pCfg->pSendBuffer, pCfg->pReceiveBuffer,
                    s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed * pCfg->u16FrameCount);
            }
        }
        else
        {
            eRet = FCSPI_STATUS_ERROR;
        }
    }
    else
    {
        eRet = FCSPI_STATUS_PARAM_ERR;
    }

    return eRet;
}

/**
 * @brief Send and receive synchronously
 * 1) If the semaphore callbacks are configured,
 *    and the driver is configured transmitting triggered by interrupt, or by DMA,
 *    the driver will use semaphore to wait the transmission stopped.
 *    In this case, the timeout value is passed to semaphore callback directly.
 * 2) If the semaphore callbacks are not configured,
 *    this api will poll the status when triggered by interrupt or DMA,
 *    or poll to trigger the transmission when the mode is "FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL".
 *    In this case, the timeout value has different meaning for different trigger mode.
 *    Read the source code for detail.
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg the data information, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when transfer successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_SyncTransfer(const FCSPI_InstanceType eInst, const FCSPI_SyncDataInfType *pCfg)
{
    FCSPI_StatusType          tStatus;
    FCSPI_SemaphoreStatType   tSemaStat;
    FCSPI_StatusType          eRet = FCSPI_STATUS_SUCCESS;
    FCSPI_AtomicBoolType      bIsMaster;
    uint32_t                  u32MonitorTimeout  = 0xFFFFFFFFu;
    uint16_t                  u16RxRemain = (uint16_t)0;
    uint16_t                  u16TxRemain = (uint16_t)0;
    uint16_t                  u16PreRxRemain = (uint16_t)0;
    uint16_t                  u16PreTxRemain = (uint16_t)0;
    uint32_t                  u32TryTimeout = 0xFFFFFFFFu;
    FCSPI_AtomicBoolType      bIsBlockType = FCSPI_TRUE;
    bIsMaster = (FCSPI_MODE_MASTER == FCSPI_HWA_CheckMode(s_atFCSpiInfo[eInst].tFCSpiInstance)) ? FCSPI_TRUE : FCSPI_FALSE;
    FCSPI_AtomicBoolType      bNeedExitLoop = FCSPI_FALSE;

    if (NULL != pCfg)
    {
        if ((uint16_t)0 != pCfg->u16FrameCount)
        {
            if ((NULL != s_atFCSpiInfo[eInst].tFCSpiStat.pSemaResetCb) &&
                (NULL != s_atFCSpiInfo[eInst].tFCSpiStat.pSemaTakeCb) &&
                (NULL != s_atFCSpiInfo[eInst].tFCSpiStat.pSemaPostCb) &&
                ((FCSPI_TRANSFER_TRIGGER_SRC_ISR == s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc) ||
                 (FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR == s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc)))
            {
                if (FCSPI_SEMAPHORE_SUCCESS == s_atFCSpiInfo[eInst].tFCSpiStat.pSemaResetCb(eInst))
                {
                    s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore = (uint8_t)1;

                    if (FCSPI_TRUE == bIsMaster)
                    {
                        tStatus = fcspi_master_async_transfer_bytes(eInst, pCfg->pSendBuffer, pCfg->pReceiveBuffer,
                            s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed * pCfg->u16FrameCount);
                    }
                    else
                    {
                        tStatus = fcspi_slave_async_transfer_bytes(eInst, pCfg->pSendBuffer, pCfg->pReceiveBuffer,
                            s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed * pCfg->u16FrameCount);
                    }

                    if (FCSPI_STATUS_SUCCESS == tStatus)
                    {
                        tSemaStat = s_atFCSpiInfo[eInst].tFCSpiStat.pSemaTakeCb(eInst, pCfg->u32Timeout);
                        if (FCSPI_SEMAPHORE_FAIL == tSemaStat)
                        {
                            s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore = (uint8_t)0;
                            s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_ABORT;
                            if (FCSPI_TRUE == bIsMaster)
                            {
                                fcspi_master_abort_transfer(eInst, FCSPI_FALSE);
                            }
                            else
                            {
                                fcspi_slave_abort_transfer(eInst, FCSPI_FALSE);
                            }

                            eRet = FCSPI_STATUS_ERROR;
                        }
                        else if (FCSPI_SEMAPHORE_TIMEOUT == tSemaStat)
                        {
                            s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore = (uint8_t)0;
                            s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_ABORT;
                            if (FCSPI_TRUE == bIsMaster)
                            {
                                fcspi_master_abort_transfer(eInst, FCSPI_FALSE);
                            }
                            else
                            {
                                fcspi_slave_abort_transfer(eInst, FCSPI_FALSE);
                            }
                            eRet = FCSPI_STATUS_SYNC_TIMEOUT;
                        }
                        else
                        {
                            s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore = (uint8_t)0;
                            if (FCSPI_TRANSFER_OK != s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat)
                            {
                                eRet = FCSPI_STATUS_TRANSFER_FAIL;
                            }
                            else
                            {
                                eRet = FCSPI_STATUS_SUCCESS;
                            }
                        }
                    }
                    else
                    {
                        s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore = (uint8_t)0;
                        eRet = tStatus;
                    }
                }
                else
                {
                    eRet = FCSPI_STATUS_ERROR;
                }
            }
            else
            {
                if (FCSPI_TRUE == bIsMaster)
                {
                    tStatus = fcspi_master_async_transfer_bytes(eInst, pCfg->pSendBuffer, pCfg->pReceiveBuffer,
                        s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed * pCfg->u16FrameCount);
                }
                else
                {
                    tStatus = fcspi_slave_async_transfer_bytes(eInst, pCfg->pSendBuffer, pCfg->pReceiveBuffer,
                        s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed * pCfg->u16FrameCount);
                }

                if (FCSPI_STATUS_SUCCESS == tStatus)
                {
                    if (pCfg->u32Timeout > 0u)
                    {
                        u32TryTimeout = pCfg->u32Timeout;
                        bIsBlockType = FCSPI_FALSE;
                    }
                    else
                    {
                        bIsBlockType = FCSPI_TRUE;
                    }

                    if (FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL == s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc)
                    {
                        if (FCSPI_TRUE == bIsMaster)
                        {
                            do {
                                eRet = fcspi_master_trigger(eInst, FCSPI_FALSE);
                                if (FCSPI_FALSE == bIsBlockType)
                                {
                                    u32TryTimeout--;
                                    if (0u == u32TryTimeout)
                                    {
                                        break;
                                    }
                                }
                            } while (FCSPI_STATUS_TRIGGER_OK == eRet);
                        }
                        else
                        {
                            do {
                                eRet = fcspi_slave_trigger(eInst, FCSPI_FALSE);

                                if (FCSPI_FALSE == bIsBlockType)
                                {
                                    u32TryTimeout--;
                                    if (0u == u32TryTimeout)
                                    {
                                        break;
                                    }
                                }
                            } while (FCSPI_STATUS_TRIGGER_OK == eRet);
                        }

                        if (FCSPI_STATUS_TRIGGER_FINISH == eRet)
                        {
                            eRet = FCSPI_STATUS_SUCCESS;
                        }
                        else if ((FCSPI_FALSE == bIsBlockType) && (0u == u32TryTimeout))
                        {
                            s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_ABORT;
                            if (FCSPI_TRUE == bIsMaster)
                            {
                                fcspi_master_abort_transfer(eInst, FCSPI_FALSE);
                            }
                            else
                            {
                                fcspi_slave_abort_transfer(eInst, FCSPI_FALSE);
                            }
                            eRet = FCSPI_STATUS_SYNC_TIMEOUT;
                        }
                        else
                        {
                            eRet = FCSPI_STATUS_TRANSFER_FAIL;
                        }
                    }
                    else if ((FCSPI_TRANSFER_TRIGGER_SRC_ISR == s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc) ||
                             (FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR == s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc))
                    {
                        u32MonitorTimeout = 0xfffff00u; /* ensure 1s */

                        u16PreRxRemain = s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet;
                        u16PreTxRemain = s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend;

                        while (FCSPI_TRUE == s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer)
                        {
                            u32MonitorTimeout--;
                            if (0u == u32MonitorTimeout)
                            {
                                bNeedExitLoop = FCSPI_FALSE;
                                u16RxRemain = s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet;
                                u16TxRemain = s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend;
                                if (((u16PreRxRemain == u16RxRemain) && ((uint16_t)0 != u16RxRemain)) ||
                                    ((u16PreTxRemain == u16TxRemain) && ((uint16_t)0 != u16TxRemain)))
                                {
                                    s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_ABORT;
                                    if (FCSPI_TRUE == bIsMaster)
                                    {
                                        fcspi_master_abort_transfer(eInst, FCSPI_FALSE);
                                    }
                                    else
                                    {
                                        fcspi_slave_abort_transfer(eInst, FCSPI_FALSE);
                                    }

                                    bNeedExitLoop = FCSPI_TRUE;
                                }
                                else
                                {
                                    u16PreRxRemain = u16RxRemain;
                                    u16PreTxRemain = u16TxRemain;
                                    u32MonitorTimeout = 0xfffff00u;

                                    if (FCSPI_FALSE == bIsBlockType)
                                    {
                                        u32TryTimeout--;
                                        if (0u == u32TryTimeout)
                                        {
                                            bNeedExitLoop = FCSPI_TRUE;
                                        }
                                    }
                                }

                                if (FCSPI_TRUE == bNeedExitLoop)
                                {
                                    break;
                                }
                            }
                        }

                        if ((FCSPI_FALSE == bIsBlockType) && (0u == u32TryTimeout))
                        {
                            s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_ABORT;
                            if (FCSPI_TRUE == bIsMaster)
                            {
                                fcspi_master_abort_transfer(eInst, FCSPI_FALSE);
                            }
                            else
                            {
                                fcspi_slave_abort_transfer(eInst, FCSPI_FALSE);
                            }
                            eRet = FCSPI_STATUS_SYNC_TIMEOUT;
                        }
                        else if (FCSPI_TRANSFER_OK == s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat)
                        {
                            eRet = FCSPI_STATUS_SUCCESS;
                        }
                        else
                        {
                            eRet = FCSPI_STATUS_TRANSFER_FAIL;
                        }
                    }
                    else
                    {
                        s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_ABORT;
                        if (FCSPI_TRUE == bIsMaster)
                        {
                            fcspi_master_abort_transfer(eInst, FCSPI_FALSE);
                        }
                        else
                        {
                            fcspi_slave_abort_transfer(eInst, FCSPI_FALSE);
                        }

                        eRet = FCSPI_STATUS_TRANSFER_FAIL;
                    }
                }
                else
                {
                    eRet = tStatus;
                }
            }
        }
        else
        {
            eRet = FCSPI_STATUS_SUCCESS;
        }
    }
    else
    {
        eRet = FCSPI_STATUS_PARAM_ERR;
    }

    return eRet;
}

static FCSPI_StatusType fcspi_master_trigger(
    FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInIsr)
{
    uint32_t   u32StatusRegValue;
    FCSPI_StatusType eRet = FCSPI_STATUS_TRIGGER_OK;

    /* if an error is detected the transfer will be aborted */
    u32StatusRegValue = FCSPI_HWA_GetStatus(s_atFCSpiInfo[eInst].tFCSpiInstance);

    /* if tx need more data but hungry, and has data, sth wrong */
    if (FCSpi_Hw_ChkTxFifoUnderrun(u32StatusRegValue) &&
        (NULL != s_atFCSpiInfo[eInst].tFCSpiStat.pbyTxBuff))
    {
        s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_TX_FAIL;
        fcspi_master_abort_transfer(eInst, bIsInIsr);
        eRet = FCSPI_STATUS_TRIGGER_ABORT_TX_FAIL;
    }
    /* if rx need more space but overflow, and has space to store, sth wrong */
    else if (FCSpi_Hw_ChkRxFifoOverflow(u32StatusRegValue) &&
        (NULL != s_atFCSpiInfo[eInst].tFCSpiStat.pbyRxBuff))
    {
        s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_RX_FAIL;
        fcspi_master_abort_transfer(eInst, bIsInIsr);
        eRet = FCSPI_STATUS_TRIGGER_ABORT_RX_FAIL;
    }
    /* rx data ready */
    else
    {
        if (FCSpi_Hw_ChkRxGreaterThanWater(u32StatusRegValue))
        {
            if ((uint16_t)0 != s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet)
            {
                fcspi_read_rx_fifo(eInst);
            }
        }

        /* transmit some, need add more */
        if (FCSpi_Hw_ChkTxEqualOrLessThanWater(u32StatusRegValue))
        {
            if ((uint16_t)0 != s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend)
            {
                fcspi_write_tx_fifo(eInst);
            }
        }

        if ((uint16_t)0 == s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend)
        {
            /* disable tx interrupt. enable tx completion interrupt.*/
            FCSpi_Hw_DisableTransmitDataInterrupt(eInst);
            FCSpi_Hw_EnableTransmitCompleteInterrupt(eInst);

            /* tx finish first, if rx also finish, just check completion */
            if ((uint16_t)0 == s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet)
            {
                u32StatusRegValue = FCSPI_HWA_GetStatus(s_atFCSpiInfo[eInst].tFCSpiInstance);
                if (FCSpi_Hw_ChkTransferComplete(u32StatusRegValue))
                {
                    fcspi_master_clean_transfer(eInst, bIsInIsr);
                    eRet = FCSPI_STATUS_TRIGGER_FINISH;
                }
            }
        }
    }
    return eRet;
}

/******************************************************************************/

static void fcspi_slave_clean_transfer(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInInterrupt)
{
    s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer = FCSPI_FALSE;

    if (FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR == s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc)
    {
        FCSpi_Hw_SetRxTxDmaEnableStatus(eInst, FCSPI_FALSE, FCSPI_FALSE);
    }
    else
    {
        FCSpi_Hw_DisableSomeInterrupts(eInst, FCSPI_INT_EN_RFIE(1) | FCSPI_INT_EN_TFIE(1));
    }

    FCSpi_Hw_DisableSomeInterrupts(eInst, FCSPI_INT_EN_RFOIE(1) | FCSPI_INT_EN_TFUIE(1));
    FCSpi_Hw_ClearSomeStatusW1CFlag(eInst, FCSPI_STATUS_RX_FO(1) | FCSPI_STATUS_TX_FU(1));

    if (FCSPI_TRUE == bIsInInterrupt)
    {
        if (NULL != s_atFCSpiInfo[eInst].tFCSpiStat.pStopNotifyCb)
        {
            s_atFCSpiInfo[eInst].tFCSpiStat.pStopNotifyCb(eInst, FCSPI_TRUE);
        }

        if (s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore)
        {
            s_atFCSpiInfo[eInst].tFCSpiStat.pSemaPostCb(eInst, FCSPI_TRUE);
            s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore = (uint8_t)0;
        }
    }
    else
    {
        if (NULL != s_atFCSpiInfo[eInst].tFCSpiStat.pStopNotifyCb)
        {
            s_atFCSpiInfo[eInst].tFCSpiStat.pStopNotifyCb(eInst, FCSPI_FALSE);
        }

        if (s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore)
        {
            s_atFCSpiInfo[eInst].tFCSpiStat.pSemaPostCb(eInst, FCSPI_FALSE);
            s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore = (uint8_t)0;
        }
    }
}

static void fcspi_slave_abort_transfer(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInInterrupt)
{
    fcspi_slave_clean_transfer(eInst, bIsInInterrupt);
    FCSpi_Hw_Reset(eInst, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE);
    FCSpi_Hw_Reset(eInst, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE); /* for shifter */
}

/**
 * @brief Init the FCSpi instance as spi slave side
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Configuration of the FCSpi
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_Slave_Init(const FCSPI_InstanceType eInst, const FCSPI_SlaveCfgType * pCfg)
{
    FCSPI_TxRxCtrlType tTxRxCtrlCfg;
    FCSPI_StatusType   eRet = FCSPI_STATUS_SUCCESS;

    s_atFCSpiInfo[eInst].tFCSpiStat.eBitFirstOrder          = pCfg->eBitFirstOrder;
    s_atFCSpiInfo[eInst].tFCSpiStat.u16BitsPerFrame         = pCfg->u16BitCountPerFrame;
    s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc     = pCfg->eTransferTriggerSrc;
    s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf          = pCfg->tTriggerDmaInf;
    s_atFCSpiInfo[eInst].tFCSpiStat.pStopNotifyCb           = pCfg->pStopNotifyCb;
    s_atFCSpiInfo[eInst].tFCSpiStat.pSemaResetCb            = pCfg->pSemaResetCb;
    s_atFCSpiInfo[eInst].tFCSpiStat.pSemaTakeCb             = pCfg->pSemaTakeCb;
    s_atFCSpiInfo[eInst].tFCSpiStat.pSemaPostCb             = pCfg->pSemaPostCb;
    s_atFCSpiInfo[eInst].tFCSpiStat.eSckPolarity            = pCfg->eSckPolarity;
    s_atFCSpiInfo[eInst].tFCSpiStat.eSckSamplePhase         = pCfg->eSckSamplePhase;
    s_atFCSpiInfo[eInst].tFCSpiStat.ePcs                    = pCfg->ePcs;
    s_atFCSpiInfo[eInst].tFCSpiStat.ePcsPolarity            = pCfg->ePcsPolarity;

    s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed   =
            (uint16_t)((s_atFCSpiInfo[eInst].tFCSpiStat.u16BitsPerFrame + (uint16_t)7) >> (uint16_t)3);

    /* DMA use 4 bytes/frame. */
    if ((uint16_t)3 == s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed)
    {
        s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed = (uint16_t)4;
    }

    /* FCSPI require 4 bytes align when > 32bits. */
    if (s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed > (uint16_t)4)
    {
        s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed = (uint16_t)
         ((((s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed + (uint16_t)3)) >> (uint16_t)2) << (uint16_t)2);
    }

    s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer = FCSPI_FALSE;

    FCSpi_Hw_Reset(eInst, FCSPI_FALSE, FCSPI_FALSE, FCSPI_TRUE);
    FCSPI_HWA_SetSlaveMode(s_atFCSpiInfo[eInst].tFCSpiInstance);
    FCSpi_Hw_SetPcs_2_3_Mode(eInst, PCS2_3_PCS);
    FCSpi_Hw_SetPin(eInst, SIN_INPUT_SOUT_OUTPUT, PINOUT_RETAIN_LAST);
    /* set fifo size param */
    s_atFCSpiInfo[eInst].tFCSpiStat.u8TxFifoSize     = (uint8_t)FCSPI_DRV_TX_FIFO_WORD_CNT;
    s_atFCSpiInfo[eInst].tFCSpiStat.u8RxFifoSize     = (uint8_t)FCSPI_DRV_RX_FIFO_WORD_CNT;
    s_atFCSpiInfo[eInst].tFCSpiStat.u32DmaDummyData   = 0xFFu;

    /* Set polarity */
    FCSpi_Hw_SetOnePcsPolarity(eInst, pCfg->ePcs, pCfg->ePcsPolarity);

     /* Write the TCR for this transfer */
    tTxRxCtrlCfg.eSckPolarity       = pCfg->eSckPolarity;
    tTxRxCtrlCfg.eSckPhase          = pCfg->eSckSamplePhase;
    tTxRxCtrlCfg.ePrescalerValue    = FCSPI_PRESCALE_1; /* not use */
    tTxRxCtrlCfg.ePCSSelect         = pCfg->ePcs;
    tTxRxCtrlCfg.eBitFirstOrder     = pCfg->eBitFirstOrder;
    tTxRxCtrlCfg.eByteSwap          = FCSPI_FALSE;
    tTxRxCtrlCfg.eContTransEnable   = FCSPI_FALSE; /* not use */
    tTxRxCtrlCfg.eContCmdEnable     = FCSPI_FALSE; /* not use */
    tTxRxCtrlCfg.eRxDisable         = FCSPI_FALSE;
    tTxRxCtrlCfg.eTxDisable         = FCSPI_FALSE;
    tTxRxCtrlCfg.eTransferWidth     = FCSPI_TRANSFER_1_BIT;
    tTxRxCtrlCfg.u16FrameBitCnt     = pCfg->u16BitCountPerFrame;

    eRet = FCSpi_Hw_SetTRCR(eInst, &tTxRxCtrlCfg);
    if (FCSPI_STATUS_SUCCESS == eRet)
    {
        FCSPI_HWA_ModuleEnable(s_atFCSpiInfo[eInst].tFCSpiInstance);

        if (FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL != pCfg->eTransferTriggerSrc)
        {
            IntMgr_EnableInterrupt(s_atFCSpiInfo[eInst].eFCSpiIrq);
        }
    }
    else
    {
        eRet = FCSPI_STATUS_ERROR;
    }

    return eRet;
}

static  void fcspi_slave_dma_rx_err_interrupt(FCSPI_InstanceType eInst)
{
    s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_RX_FAIL;
    fcspi_slave_abort_transfer(eInst, FCSPI_TRUE);
}

static void fcspi_0_slave_dma_rx_err_interrupt(void)
{
    fcspi_slave_dma_rx_err_interrupt(FCSPI_0);
}

static void fcspi_1_slave_dma_rx_err_interrupt(void)
{
    fcspi_slave_dma_rx_err_interrupt(FCSPI_1);
}

static void fcspi_2_slave_dma_rx_err_interrupt(void)
{
    fcspi_slave_dma_rx_err_interrupt(FCSPI_2);
}

static void fcspi_3_slave_dma_rx_err_interrupt(void)
{
    fcspi_slave_dma_rx_err_interrupt(FCSPI_3);
}

static void fcspi_4_slave_dma_rx_err_interrupt(void)
{
    fcspi_slave_dma_rx_err_interrupt(FCSPI_4);
}

static void fcspi_5_slave_dma_rx_err_interrupt(void)
{
    fcspi_slave_dma_rx_err_interrupt(FCSPI_5);
}

static  void fcspi_slave_dma_rx_finish_interrupt(FCSPI_InstanceType eInst)
{
    fcspi_slave_abort_transfer(eInst, FCSPI_TRUE);
}

static void fcspi_0_slave_dma_rx_finish_interrupt(void)
{
    fcspi_slave_dma_rx_finish_interrupt(FCSPI_0);
}

static void fcspi_1_slave_dma_rx_finish_interrupt(void)
{
    fcspi_slave_dma_rx_finish_interrupt(FCSPI_1);
}

static void fcspi_2_slave_dma_rx_finish_interrupt(void)
{
    fcspi_slave_dma_rx_finish_interrupt(FCSPI_2);
}

static void fcspi_3_slave_dma_rx_finish_interrupt(void)
{
    fcspi_slave_dma_rx_finish_interrupt(FCSPI_3);
}

static void fcspi_4_slave_dma_rx_finish_interrupt(void)
{
    fcspi_slave_dma_rx_finish_interrupt(FCSPI_4);
}

static void fcspi_5_slave_dma_rx_finish_interrupt(void)
{
    fcspi_slave_dma_rx_finish_interrupt(FCSPI_5);
}

static void fcspi_slave_dma_tx_err_interrupt(FCSPI_InstanceType eInst)
{
    s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_TX_FAIL;
    fcspi_slave_abort_transfer(eInst, FCSPI_TRUE);
}

static void fcspi_0_slave_dma_tx_err_interrupt(void)
{
    fcspi_slave_dma_tx_err_interrupt(FCSPI_0);
}

static void fcspi_1_slave_dma_tx_err_interrupt(void)
{
    fcspi_slave_dma_tx_err_interrupt(FCSPI_1);
}

static void fcspi_2_slave_dma_tx_err_interrupt(void)
{
    fcspi_slave_dma_tx_err_interrupt(FCSPI_2);
}

static void fcspi_3_slave_dma_tx_err_interrupt(void)
{
   fcspi_slave_dma_tx_err_interrupt(FCSPI_3);
}

static void fcspi_4_slave_dma_tx_err_interrupt(void)
{
   fcspi_slave_dma_tx_err_interrupt(FCSPI_4);
}

static void fcspi_5_slave_dma_tx_err_interrupt(void)
{
   fcspi_slave_dma_tx_err_interrupt(FCSPI_5);
}

static  void fcspi_slave_dma_tx_finish_interrupt(FCSPI_InstanceType eInst)
{
    fcspi_slave_abort_transfer(eInst, FCSPI_TRUE);
}

static  void fcspi_0_slave_dma_tx_finish_interrupt(void)
{
    fcspi_slave_dma_tx_finish_interrupt(FCSPI_0);
}

static  void fcspi_1_slave_dma_tx_finish_interrupt(void)
{
    fcspi_slave_dma_tx_finish_interrupt(FCSPI_1);
}

static  void fcspi_2_slave_dma_tx_finish_interrupt(void)
{
    fcspi_slave_dma_tx_finish_interrupt(FCSPI_2);
}

static  void fcspi_3_slave_dma_tx_finish_interrupt(void)
{
    fcspi_slave_dma_tx_finish_interrupt(FCSPI_3);
}

static  void fcspi_4_slave_dma_tx_finish_interrupt(void)
{
    fcspi_slave_dma_tx_finish_interrupt(FCSPI_4);
}

static  void fcspi_5_slave_dma_tx_finish_interrupt(void)
{
    fcspi_slave_dma_tx_finish_interrupt(FCSPI_5);
}

static FCSPI_StatusType fcspi_slave_async_transfer_bytes(FCSPI_InstanceType eInst,
    const uint8_t *pSendBuffer, uint8_t *pReceiveBuffer, uint16_t u16TransferByteCnt)
{
    DMA_InterruptCfgType tDmaTxInterruptCfg = {0};
    DMA_ChannelCfgType   tDmaTxChnlCfg = {0};
    uint8_t              u8DmaTxBlkByteCnt = (uint8_t)1;
    DMA_InterruptCfgType tDmaRxInterruptCfg = {0};
    DMA_ChannelCfgType   tDmaRxChnlCfg = {0};
    uint8_t              u8DmaRxBlkByteCnt = (uint8_t)1;
    FCSPI_StatusType     eRet = FCSPI_STATUS_SUCCESS;

    if ((NULL == pSendBuffer) && (NULL == pReceiveBuffer))
    {
        eRet = FCSPI_STATUS_ERROR;
    }
    else if ((uint16_t)0 == s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed)
    {
        eRet = FCSPI_STATUS_ERROR;
    }
    else if ((uint16_t)0 == u16TransferByteCnt)
    {
        eRet = FCSPI_STATUS_NO_DATA;
    }
    else if ((uint16_t)0 != (u16TransferByteCnt % s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed))
    {
        eRet = FCSPI_STATUS_ERROR;
    }
    else if (FCSPI_TRUE == s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer)
    {
        eRet = FCSPI_STATUS_BUSY;
    }
    else
    {
        s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_OK;
        FCSpi_Hw_Reset(eInst, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE);
        FCSpi_Hw_Reset(eInst, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE); /* for shifter */

        FCSpi_Hw_ClearSomeStatusW1CFlag(eInst, FCSPI_DRV_STATUS_REG_W1C_U32);

        /* in slave mode, rx and tx all enabled */
        FCSpi_Hw_EnableMoreInterrupts(eInst, FCSPI_INT_EN_TFUIE(1) | FCSPI_INT_EN_RFOIE(1));

        s_atFCSpiInfo[eInst].tFCSpiStat.pbyTxBuff  = pSendBuffer;
        s_atFCSpiInfo[eInst].tFCSpiStat.pbyRxBuff  = pReceiveBuffer;
        s_atFCSpiInfo[eInst].tFCSpiStat.u16TxIndex = (uint16_t)0;
        s_atFCSpiInfo[eInst].tFCSpiStat.u16RxIndex = (uint16_t)0;

        if (FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR == s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc)
        {
            FCSPI_HWA_SetWatermark(s_atFCSpiInfo[eInst].tFCSpiInstance,  (uint8_t)0,  (uint8_t)3);

            /* TX */
            tDmaTxChnlCfg.u8ChannelPriority     = s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8TxDMAChannelPriority;
            tDmaTxChnlCfg.bDestAddrLoopbackEn   = false;
            tDmaTxChnlCfg.bSrcAddrLoopbackEn    = false;
            tDmaTxChnlCfg.bAutoStop             = true; /* auto stop dma after send finish */
            tDmaTxChnlCfg.bSrcCircularBufferEn  = false;
            tDmaTxChnlCfg.bDestCircularBufferEn = false;

            switch (s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed)
            {
                case 1:
                    tDmaTxChnlCfg.eSrcDataSize           = DMA_TRANSFER_SIZE_1B;
                    tDmaTxChnlCfg.eDestDataSize          = DMA_TRANSFER_SIZE_1B;
                    tDmaTxChnlCfg.bSrcBlockOffsetEn      = true;
                    tDmaTxChnlCfg.s32BlockOffset         = (int32_t)1;
                    u8DmaTxBlkByteCnt                    = (uint8_t)1;
                    break;

                case 2:
                    tDmaTxChnlCfg.eSrcDataSize           = DMA_TRANSFER_SIZE_2B;
                    tDmaTxChnlCfg.eDestDataSize          = DMA_TRANSFER_SIZE_2B;
                    tDmaTxChnlCfg.bSrcBlockOffsetEn      = true;
                    tDmaTxChnlCfg.s32BlockOffset         = (int32_t)2;
                    u8DmaTxBlkByteCnt                    = (uint8_t)2;
                    break;

                default:
                    tDmaTxChnlCfg.eSrcDataSize           = DMA_TRANSFER_SIZE_4B;
                    tDmaTxChnlCfg.eDestDataSize          = DMA_TRANSFER_SIZE_4B;
                    tDmaTxChnlCfg.bSrcBlockOffsetEn      = true;
                    tDmaTxChnlCfg.s32BlockOffset         = (int32_t)4;
                    u8DmaTxBlkByteCnt                    = (uint8_t)4;
                    break;
            }

            tDmaTxChnlCfg.u16BlockCount               = u16TransferByteCnt / u8DmaTxBlkByteCnt;
            tDmaTxChnlCfg.bDestBlockOffsetEn          = false;
            tDmaTxInterruptCfg.bTransferCompleteIntEn = true;
            tDmaTxInterruptCfg.bTransferErrorIntEn    = true;
            switch (eInst)
            {
                case FCSPI_0:
                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI0_TX;
                    tDmaTxInterruptCfg.pTransferCompleteNotify = fcspi_0_slave_dma_tx_finish_interrupt;
                    tDmaTxInterruptCfg.pTransferErrorNotify = fcspi_0_slave_dma_tx_err_interrupt;
                    break;

                case FCSPI_1:
                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI1_TX;
                    tDmaTxInterruptCfg.pTransferCompleteNotify = fcspi_1_slave_dma_tx_finish_interrupt;
                    tDmaTxInterruptCfg.pTransferErrorNotify = fcspi_1_slave_dma_tx_err_interrupt;
                    break;

                case FCSPI_2:
                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI2_TX;
                    tDmaTxInterruptCfg.pTransferCompleteNotify = fcspi_2_slave_dma_tx_finish_interrupt;
                    tDmaTxInterruptCfg.pTransferErrorNotify = fcspi_2_slave_dma_tx_err_interrupt;
                    break;

                case FCSPI_3:
                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_TX;
                    tDmaTxInterruptCfg.pTransferCompleteNotify = fcspi_3_slave_dma_tx_finish_interrupt;
                    tDmaTxInterruptCfg.pTransferErrorNotify = fcspi_3_slave_dma_tx_err_interrupt;
                    break;

                case FCSPI_4:
                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI4_TX;
                    tDmaTxInterruptCfg.pTransferCompleteNotify = fcspi_4_slave_dma_tx_finish_interrupt;
                    tDmaTxInterruptCfg.pTransferErrorNotify = fcspi_4_slave_dma_tx_err_interrupt;
                    break;

                case FCSPI_5:
                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI5_TX;
                    tDmaTxInterruptCfg.pTransferCompleteNotify = fcspi_5_slave_dma_tx_finish_interrupt;
                    tDmaTxInterruptCfg.pTransferErrorNotify = fcspi_5_slave_dma_tx_err_interrupt;
                    break;

                default:
                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_TX;
                    tDmaTxInterruptCfg.pTransferCompleteNotify = fcspi_3_slave_dma_tx_finish_interrupt;
                    tDmaTxInterruptCfg.pTransferErrorNotify = fcspi_3_slave_dma_tx_err_interrupt;
                    break;
            }

            tDmaTxChnlCfg.eDestIncMode = DMA_INCREMENT_DISABLE;
            tDmaTxChnlCfg.eSrcIncMode  = DMA_INCREMENT_DISABLE;
            tDmaTxChnlCfg.pDestBuffer  = FCSPI_HWA_GetTxDataAddr(s_atFCSpiInfo[eInst].tFCSpiInstance);
            tDmaTxChnlCfg.u32BlockSize = (uint32_t)u8DmaTxBlkByteCnt;

            if (NULL != pSendBuffer)
            {
                s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend = u16TransferByteCnt;
                tDmaTxChnlCfg.pSrcBuffer = pSendBuffer;
            }
            else
            {
                s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend = (uint16_t)0;
                tDmaTxChnlCfg.bSrcBlockOffsetEn                          = false; /* if send buffer is NULL, just send dummy data, MUST fix the source to the dummy variable */
                tDmaTxChnlCfg.s32BlockOffset                             = (int32_t)0;
                tDmaTxChnlCfg.pSrcBuffer = &(s_atFCSpiInfo[eInst].tFCSpiStat.u32DmaDummyData);
            }

            DMA_InitChannel(s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.eDMAInstance, 
                                  (DMA_ChannelType)s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8TxDMAChannel, &tDmaTxChnlCfg);

            /* RX */
            tDmaRxChnlCfg.u8ChannelPriority     = s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8RxDMAChannelPriority;
            tDmaRxChnlCfg.bDestAddrLoopbackEn   = false;
            tDmaRxChnlCfg.bSrcAddrLoopbackEn    = false;
            tDmaRxChnlCfg.bAutoStop             = true; /* auto stop dma after send finish */
            tDmaRxChnlCfg.bSrcCircularBufferEn  = false;
            tDmaRxChnlCfg.bDestCircularBufferEn = false;

            switch (s_atFCSpiInfo[eInst].tFCSpiStat.u16BytesCntFrameNeed)
            {
                case 1:
                    tDmaRxChnlCfg.eDestDataSize      = DMA_TRANSFER_SIZE_1B;
                    tDmaRxChnlCfg.eSrcDataSize       = DMA_TRANSFER_SIZE_1B;
                    tDmaRxChnlCfg.bDestBlockOffsetEn = true;
                    tDmaRxChnlCfg.s32BlockOffset     = (int32_t)1;
                    u8DmaRxBlkByteCnt                = (uint8_t)1;
                    break;

                case 2:
                    tDmaRxChnlCfg.eDestDataSize      = DMA_TRANSFER_SIZE_2B;
                    tDmaRxChnlCfg.eSrcDataSize       = DMA_TRANSFER_SIZE_2B;
                    tDmaRxChnlCfg.bDestBlockOffsetEn = true;
                    tDmaRxChnlCfg.s32BlockOffset     = (int32_t)2;
                    u8DmaRxBlkByteCnt                = (uint8_t)2;
                    break;

                default:
                    tDmaRxChnlCfg.eDestDataSize      = DMA_TRANSFER_SIZE_4B;
                    tDmaRxChnlCfg.eSrcDataSize       = DMA_TRANSFER_SIZE_4B;
                    tDmaRxChnlCfg.bDestBlockOffsetEn = true;
                    tDmaRxChnlCfg.s32BlockOffset     = (int32_t)4;
                    u8DmaRxBlkByteCnt                = (uint8_t)4;
                    break;
            }

            tDmaRxChnlCfg.u16BlockCount               = u16TransferByteCnt / u8DmaRxBlkByteCnt;
            tDmaRxChnlCfg.bSrcBlockOffsetEn           = false;
            tDmaRxInterruptCfg.bTransferCompleteIntEn = true;
            tDmaRxInterruptCfg.bTransferErrorIntEn    = true;
            switch (eInst)
            {
                case FCSPI_0:
                    tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI0_RX;
                    tDmaRxInterruptCfg.pTransferCompleteNotify = fcspi_0_slave_dma_rx_finish_interrupt;
                    tDmaRxInterruptCfg.pTransferErrorNotify = fcspi_0_slave_dma_rx_err_interrupt;
                    break;

                case FCSPI_1:
                    tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI1_RX;
                    tDmaRxInterruptCfg.pTransferCompleteNotify = fcspi_1_slave_dma_rx_finish_interrupt;
                    tDmaRxInterruptCfg.pTransferErrorNotify = fcspi_1_slave_dma_rx_err_interrupt;
                    break;

                case FCSPI_2:
                    tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI2_RX;
                    tDmaRxInterruptCfg.pTransferCompleteNotify = fcspi_2_slave_dma_rx_finish_interrupt;
                    tDmaRxInterruptCfg.pTransferErrorNotify = fcspi_2_slave_dma_rx_err_interrupt;
                    break;

                case FCSPI_3:
                    tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_RX;
                    tDmaRxInterruptCfg.pTransferCompleteNotify = fcspi_3_slave_dma_rx_finish_interrupt;
                    tDmaRxInterruptCfg.pTransferErrorNotify = fcspi_3_slave_dma_rx_err_interrupt;
                    break;

                case FCSPI_4:
                    tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI4_RX;
                    tDmaRxInterruptCfg.pTransferCompleteNotify = fcspi_4_slave_dma_rx_finish_interrupt;
                    tDmaRxInterruptCfg.pTransferErrorNotify = fcspi_4_slave_dma_rx_err_interrupt;
                    break;

                case FCSPI_5:
                    tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI5_RX;
                    tDmaRxInterruptCfg.pTransferCompleteNotify = fcspi_5_slave_dma_rx_finish_interrupt;
                    tDmaRxInterruptCfg.pTransferErrorNotify = fcspi_5_slave_dma_rx_err_interrupt;
                    break;

                default:
                    tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_RX;
                    tDmaRxInterruptCfg.pTransferCompleteNotify = fcspi_3_slave_dma_rx_finish_interrupt;
                    tDmaRxInterruptCfg.pTransferErrorNotify = fcspi_3_slave_dma_rx_err_interrupt;
                    break;
            }

            tDmaRxChnlCfg.eSrcIncMode  = DMA_INCREMENT_DISABLE;
            tDmaRxChnlCfg.eDestIncMode = DMA_INCREMENT_DISABLE;
            tDmaRxChnlCfg.pSrcBuffer   = FCSPI_HWA_GetRxDataAddr(s_atFCSpiInfo[eInst].tFCSpiInstance);
            tDmaRxChnlCfg.u32BlockSize = (uint32_t)u8DmaRxBlkByteCnt;

            if (NULL != pReceiveBuffer)
            {
                s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet = u16TransferByteCnt;
                tDmaRxChnlCfg.pDestBuffer  = pReceiveBuffer;
            }
            else
            {
                s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet = (uint16_t)0;
                tDmaRxChnlCfg.bDestBlockOffsetEn                        = false;
                tDmaRxChnlCfg.s32BlockOffset                            = (int32_t)0;
                tDmaRxChnlCfg.pDestBuffer = &(s_atFCSpiInfo[eInst].tFCSpiStat.u32DmaDummyData);
            }

            DMA_InitChannel(s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.eDMAInstance, 
                                (DMA_ChannelType)s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8RxDMAChannel, &tDmaRxChnlCfg);

            s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer = FCSPI_TRUE;

            DMA_InitChannelInterrupt(s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.eDMAInstance, 
                                        (DMA_ChannelType)s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8RxDMAChannel, &tDmaRxInterruptCfg);
            DMA_InitChannelInterrupt(s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.eDMAInstance, 
                                       (DMA_ChannelType)s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8TxDMAChannel, &tDmaTxInterruptCfg);
            DMA_StartChannel(s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.eDMAInstance, 
                                (DMA_ChannelType)s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8RxDMAChannel);
            DMA_StartChannel(s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.eDMAInstance, 
                                (DMA_ChannelType)s_atFCSpiInfo[eInst].tFCSpiStat.tTriggerDmaInf.u8TxDMAChannel);
            FCSpi_Hw_SetRxTxDmaEnableStatus(eInst, FCSPI_TRUE, FCSPI_TRUE);
        }
        else
        {
            FCSPI_HWA_SetWatermark(s_atFCSpiInfo[eInst].tFCSpiInstance,  (uint8_t)0,  (uint8_t)2);

            if (NULL == s_atFCSpiInfo[eInst].tFCSpiStat.pbyTxBuff)
            {
                s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend = (uint16_t)0;
                FCSPI_HWA_EnableTxDataMask(s_atFCSpiInfo[eInst].tFCSpiInstance, FCSPI_FALSE);
            }
            else
            {
                s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend = u16TransferByteCnt;
                FCSPI_HWA_EnableTxDataMask(s_atFCSpiInfo[eInst].tFCSpiInstance, FCSPI_TRUE);
            }

            if (NULL == s_atFCSpiInfo[eInst].tFCSpiStat.pbyRxBuff)
            {
                s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet = (uint16_t)0;
                FCSPI_HWA_EnableRxDataMask(s_atFCSpiInfo[eInst].tFCSpiInstance, FCSPI_FALSE);
            }
            else
            {
                s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet = u16TransferByteCnt;
                FCSPI_HWA_EnableRxDataMask(s_atFCSpiInfo[eInst].tFCSpiInstance, FCSPI_TRUE);
            }

            s_atFCSpiInfo[eInst].tFCSpiStat.u16RxGetByteCntOfCurFrame   = (uint16_t)0;
            s_atFCSpiInfo[eInst].tFCSpiStat.u16TxSendByteCntOfCurFrame  = (uint16_t)0;
            s_atFCSpiInfo[eInst].tFCSpiStat.eIsPcsContinuous          = FCSPI_FALSE;
            s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer             = FCSPI_TRUE;

            if (NULL != pReceiveBuffer) /* need rx fifo */
            {
                FCSpi_Hw_EnableMoreInterrupts(eInst, FCSPI_INT_EN_RFIE(1));
            }

            if (NULL != pSendBuffer)
            {
                FCSpi_Hw_EnableMoreInterrupts(eInst, FCSPI_INT_EN_TFIE(1));
            }
        }
    }

    return eRet;
}

static FCSPI_StatusType fcspi_slave_trigger(
    FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInISR)
{
    uint32_t   u32StatusRegValue;
    uint16_t   u16RemainTx = (uint16_t)0;
    uint16_t   u16RemainRx = (uint16_t)0;
    FCSPI_StatusType eRet = FCSPI_STATUS_TRIGGER_OK;

    /* If an error is detected the transfer will be aborted */
    u32StatusRegValue = FCSPI_HWA_GetStatus(s_atFCSpiInfo[eInst].tFCSpiInstance);
    if (FCSpi_Hw_ChkTxFifoUnderrun(u32StatusRegValue) &&
        (NULL != s_atFCSpiInfo[eInst].tFCSpiStat.pbyTxBuff))
    {
        s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_TX_FAIL;
        fcspi_slave_abort_transfer(eInst, bIsInISR);
        eRet = FCSPI_STATUS_TRIGGER_ABORT_TX_FAIL;
    }
    else if (FCSpi_Hw_ChkRxFifoOverflow(u32StatusRegValue) &&
        (NULL != s_atFCSpiInfo[eInst].tFCSpiStat.pbyRxBuff))
    {
        s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_RX_FAIL;
        fcspi_slave_abort_transfer(eInst, bIsInISR);
        eRet = FCSPI_STATUS_TRIGGER_ABORT_RX_FAIL;
    }
    /* rx data ready */
    else
    {
        if (FCSpi_Hw_ChkRxGreaterThanWater(u32StatusRegValue))
        {
            if ((uint16_t)0 != s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet)
            {
                fcspi_read_rx_fifo(eInst);
            }
        }

        /* transmit some, need add more */
        if (FCSpi_Hw_ChkTxEqualOrLessThanWater(u32StatusRegValue))
        {
            if ((uint16_t)0 != s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend)
            {
                fcspi_write_tx_fifo(eInst);
            }
        }

        if ((uint16_t)0 == s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend)
        {
            /* Disable TX flag. Software buffer is empty.*/
            FCSpi_Hw_DisableTransmitDataInterrupt(eInst);
        }

        if ((uint16_t)0 == s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet)
        {
            FCSpi_Hw_DisableReceiveDataInterrupt(eInst);
        }

        u16RemainTx = s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend;
        u16RemainRx = s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet;
        if (((uint16_t)0 == u16RemainTx) && ((uint16_t)0 == u16RemainRx))
        {
            FCSpi_Hw_DisableSomeInterrupts(eInst, FCSPI_INT_EN_RFOIE(1) | FCSPI_INT_EN_TFUIE(1));

            if (s_atFCSpiInfo[eInst].tFCSpiStat.pStopNotifyCb)
            {
                s_atFCSpiInfo[eInst].tFCSpiStat.pStopNotifyCb(eInst, bIsInISR);
            }

            if (s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore)
            {
                s_atFCSpiInfo[eInst].tFCSpiStat.pSemaPostCb(eInst, bIsInISR);
                s_atFCSpiInfo[eInst].tFCSpiStat.u8WaitSemaphore = (uint8_t)0;
            }

            s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer = FCSPI_FALSE;
            eRet = FCSPI_STATUS_TRIGGER_FINISH;
        }
    }

    return eRet;
}

/*----------------------------------------------------------------------------*/
/**
 * @brief If it's in transfer, get its stat, or get the last transfer's stat.
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg the transfer information, can be null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when the last transfer is finish successfully. Others, busy or error occur.
 */
FCSPI_StatusType FCSPI_GetLatestTransferStat(const FCSPI_InstanceType eInst, FCSPI_TransferRemainInfType *pCfg)
{
    FCSPI_StatusType eRet = FCSPI_STATUS_SUCCESS;

    if (NULL != pCfg)
    {
        pCfg->u32ByteCountReceiveRemained  = s_atFCSpiInfo[eInst].tFCSpiStat.u16RxByteCntRemainToGet;
        pCfg->u32ByteCountSendRemained = s_atFCSpiInfo[eInst].tFCSpiStat.u16TxByteCntRemainToSend;
    }

    if (FCSPI_TRANSFER_OK != s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat)
    {
        eRet = FCSPI_STATUS_ERROR;
    }
    else if (FCSPI_TRUE == s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer)
    {
        eRet = FCSPI_STATUS_BUSY;
    }
    else
    {
        eRet = FCSPI_STATUS_SUCCESS;
    }

    return eRet;
}

#ifdef   FCSPI_DRV_INTERNAL_FUNC_EN
/**
 * @brief Trigger the driver to transfer data when select FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL
 *
 * @param eInst Which FCSpi Hardware instance
 * @return FCSPI_StatusType FCSPI_STATUS_TRIGGER_OK when api trigger successfully, FCSPI_STATUS_TRIGGER_FINISH when all data transfer finish. Others, error happen.
 */
FCSPI_StatusType FCSPI_PollTrigger(FCSPI_InstanceType eInst)
{
    FCSPI_StatusType eRet = FCSPI_STATUS_TRIGGER_OK;

    if (FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL == s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc)
    {
        if (FCSPI_TRUE == s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer)
        {
            if (FCSPI_MODE_MASTER == FCSPI_HWA_CheckMode(s_atFCSpiInfo[eInst].tFCSpiInstance))
            {
                eRet = fcspi_master_trigger(eInst, FCSPI_FALSE);
            }
            else
            {
                eRet = fcspi_slave_trigger(eInst, FCSPI_FALSE);
            }
        }
        else
        {
            eRet = FCSPI_STATUS_ERROR;
        }
    }
    else
    {
        eRet = FCSPI_STATUS_ERROR;
    }

    return eRet;
}
#endif

/**
 * @brief Select the trigger source(DMA with interrupt / interrupt / user poll)
 *
 * @param eInst Which FCSpi Hardware instance
 * @param eSrc three source, 1) DMA move data between memory and registers, notified when finish by interrupt; 2) purely by interrupt; 3) purely by user poll.
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when successfully. Others, error.
 */
FCSPI_StatusType FCSPI_SelectTriggerSrc(
    FCSPI_InstanceType eInst, FCSPI_TriggerSrcType eSrc)
{
    FCSPI_StatusType eRet = FCSPI_STATUS_SUCCESS;
    uint32_t         u32StatRegVal = 0u;

    u32StatRegVal = FCSPI_HWA_GetStatus(s_atFCSpiInfo[eInst].tFCSpiInstance);
    if ((FCSPI_TRUE != s_atFCSpiInfo[eInst].tFCSpiStat.eIsInTransfer) &&
        (!FCSpi_Hw_ChkBusy(u32StatRegVal)))
    {
        switch (eSrc)
        {
            case FCSPI_TRANSFER_TRIGGER_SRC_ISR:
                s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc = eSrc;
                break;
            case FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR:
                s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc = eSrc;
                break;
            case FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL:
                s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc = eSrc;
                break;
            default:
                s_atFCSpiInfo[eInst].tFCSpiStat.eTransferTriggerSrc = eSrc;
                break;
        }
    }
    else
    {
        eRet = FCSPI_STATUS_BUSY;
    }

    return eRet;
}

/**
 * @brief Abort current transfer if exist, or just recovery the hardware.
 *
 * @param eInst Which FCSpi Hardware instance
 */
void FCSPI_AbortTransfer(const FCSPI_InstanceType eInst)
{
    s_atFCSpiInfo[eInst].tFCSpiStat.eTransferStat = FCSPI_TRANSFER_ABORT;

    if (FCSPI_MODE_MASTER == FCSPI_HWA_CheckMode(s_atFCSpiInfo[eInst].tFCSpiInstance))
    {
        fcspi_master_abort_transfer(eInst, FCSPI_FALSE);
    }
    else
    {
        fcspi_slave_abort_transfer(eInst, FCSPI_FALSE);
    }
}

static void fcspi_irq_handler(FCSPI_InstanceType eInst)
{
    if (FCSPI_MODE_MASTER == FCSPI_HWA_CheckMode(s_atFCSpiInfo[eInst].tFCSpiInstance))
    {
        fcspi_master_trigger(eInst, FCSPI_TRUE);
    }
    else
    {
        fcspi_slave_trigger(eInst, FCSPI_TRUE);
    }
}

/**
 * @brief fcspi 0 interrupt handler
 *
 * @note This function should be called as/in FCSPI 0 interrupt handler
 */
void FCSPI0_IRQHandler(void)
{
    fcspi_irq_handler(FCSPI_0);
}

/**
 * @brief fcspi 1 interrupt handler
 *
 * @note This function should be called as/in FCSPI 1 interrupt handler
 */
void FCSPI1_IRQHandler(void)
{
    fcspi_irq_handler(FCSPI_1);
}

/**
 * @brief fcspi 2 interrupt handler
 *
 * @note This function should be called as/in FCSPI 2 interrupt handler
 */
void FCSPI2_IRQHandler(void)
{
    fcspi_irq_handler(FCSPI_2);
}

/**
 * @brief fcspi 3 interrupt handler
 *
 * @note This function should be called as/in FCSPI 3 interrupt handler
 */
void FCSPI3_IRQHandler(void)
{
    fcspi_irq_handler(FCSPI_3);
}

/**
 * @brief fcspi 4 interrupt handler
 *
 * @note This function should be called as/in FCSPI 4 interrupt handler
 */
void FCSPI4_IRQHandler(void)
{
    fcspi_irq_handler(FCSPI_4);
}

/**
 * @brief fcspi 5 interrupt handler
 *
 * @note This function should be called as/in FCSPI 5 interrupt handler
 */
void FCSPI5_IRQHandler(void)
{
    fcspi_irq_handler(FCSPI_5);
}
