#include "FCSpi.h"
#include "string.h"
#include "rtos.h"

void FCSpiCompleteCallback(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInIsr);

uint8_t adwBspFCSpiData[FRAME_COUNT] = {0xAA};
uint8_t adwBspFCSpiDataRecv[FRAME_COUNT] = {0};

volatile uint8_t bFinished = 1; /* due to the isr will change this value, use volatile */

volatile uint8_t spiDataReceived = 0;
volatile uint8_t spiError = 0;
volatile uint32_t spiReceivedBytes = 0;


FCSPI_StatusType eStatus;


void FCSpiCompleteCallback(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInIsr)
{
    (void)eInst;
    (void)bIsInIsr;
    bFinished = 1;
    //
}

void Bsp_FCSpi_Init(void)
{
    FCSPI_MasterCfgType tFCSpiInitCfg = {0};
    FCSPI_StatusType    eStat         = FCSPI_STATUS_SUCCESS;

    tFCSpiInitCfg.u32BitCntPerSecond   = 1000000;
    tFCSpiInitCfg.ePcs                = FCSPI_PCS_1;
    tFCSpiInitCfg.ePcsPolarity        = FCSPI_PCS_POL_ACTIVE_LOW;
    tFCSpiInitCfg.eIsPcsContinuous    = FCSPI_FALSE;
    tFCSpiInitCfg.u16BitCountPerFrame   = 8;
    tFCSpiInitCfg.u32FCSpiSrcClk = SCG_GetScgClockFreq(SCG_FOSCDIVM_CLK);
    tFCSpiInitCfg.eSckSamplePhase     = FCSPI_SCK_SAMPLE_FIRST_EDGE;
    tFCSpiInitCfg.eSckPolarity        = FCSPI_SCK_ACTIVE_HIGH;
    tFCSpiInitCfg.eBitFirstOrder      = FCSPI_MSB_FIRST;
    tFCSpiInitCfg.eTransferTriggerSrc       = FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL;
    tFCSpiInitCfg.pStopNotifyCb = FCSpiCompleteCallback;
    //IntMgr_SetPriority(FCSPI1_IRQn, 3U);
    //IntMgr_EnableInterrupt(FCSPI1_IRQn);
    eStat = FCSPI_Master_Init(FCSPI_1, &tFCSpiInitCfg);
    if (FCSPI_STATUS_SUCCESS != eStat){
        return;
    }
	FCUART_Printf(2, "MASTER INIT\n");
}


uint32_t Bsp_FCSpi_Send_To_Trigger(SPI_TX_DATA_t data)
{
    FCSPI_StatusType eStatus;
    FCSPI_AsyncDataInfType tDataInf2;
    FCSPI_SyncDataInfType tDataInf;

    if (!bFinished)
        return -1;
    eStatus = FCSPI_GetLatestTransferStat(FCSPI_1, NULL); /* check previous send status */
    bFinished = 0;
    tDataInf.pReceiveBuffer = data.rx_buf;
    tDataInf.pSendBuffer = (const uint8_t*)data.buf;
    tDataInf.u16FrameCount = (uint16_t) data.len;
    tDataInf.u32Timeout = (uint32_t) 100U;
    eStatus = FCSPI_SyncTransfer(FCSPI_1, &tDataInf);
    if (FCSPI_STATUS_SUCCESS != eStatus)
    {
        bFinished = 1;
        FCUART_Printf(2, "ERROR: SPI ERROR\n");
        return -1;
    }
    bFinished = 1;
    return 0;
}


