#include "CAN.h"
#include "rtos.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/* ################################################################################## */
/* ####################################### Macro #################################### */
//CAN0 is USED
#define CAN_RECEIVE_INTERRUPT STD_ON

#define CAN_FD_ENABLE STD_OFF

#define CAN_CLOCK_FROM_BUS STD_OFF

#define CAN_DIRECT_MODE_ENABLE STD_OFF


/* ################################################################################## */
/* ################################ Local Variables ################################# */

static FLEXCAN_RxMsgType s_aaRxDataBuf;
static volatile uint8_t flag_Tx_Finished = 1;

static const PCC_ClkSrcType s_ePccCan = PCC_CLK_FLEXCAN0;
/* ################################################################################## */
/* ############################ Local Prototype Functions ########################### */
static void BSP_CAN_LL_Init(uint8_t u8CanIndex);
static void BSP_CAN_LL_TransmitData(uint8_t u8CanIndex, CAN_TX_DATA_t data);

/* ################################################################################## */
/* ########################### Global Prototype Functions ########################### */
#if CAN_RECEIVE_INTERRUPT == STD_ON
    static void CAN_ErrorInterrupt_CallBack(uint8_t u8CanIndex, FLEXCAN_ErrorInfoType *pErrorInfo);
    static void CAN_RxInterrupt_CallBack(uint8_t u8CanIndex, FLEXCAN_RxMsgType *pRxCfg);
    static void CAN_TxInterrupt_CallBack(uint8_t u8CanIndex, uint8_t u8TxHandler);

#endif


void CAN0_IRQHandler(){
	FLEXCAN_IRQHandler(0U);
}
/* ################################################################################## */
/* ################################ Local Functions ################################# */
static void BSP_CAN_INIT_CFG(FLEXCAN_InitType *pCfg)
{
    pCfg->bListenOnly = 0U;
    pCfg->bEnBrs = 0;
    pCfg->bEnDma = 0;
    pCfg->bEnFd = 0;
    pCfg->bEnRxFifo = 0;
    pCfg->eBaudrate = FLEXCAN_BAUD_100K;
    pCfg->eClkSrcHz = FLEXCAN_BAUDCLK_HZ_8M;
    pCfg->eClkSrcSel = FLEXCAN_CLOCK_FUNCTION;
    pCfg->eDataBaud = FLEXCAN_BAUD_100K;
    pCfg->eMbDataWidth = FLEXCAN_DATAWIDTH_8;
    pCfg->u8EnhancedFifoDmaWM = 0;
    pCfg->eDirect = FLEXCAN_DIR_DISABLE;
}

/**
 * \brief CAN init with index
 *
 * \param u8CanIndex
 */
static void BSP_CAN_LL_Init(uint8_t u8CanIndex)
{
    FLEXCAN_ErrorType tRetVal;
    FLEXCAN_InitType tInitCfg;
    BSP_CAN_INIT_CFG(&tInitCfg);
    #if CAN_RECEIVE_INTERRUPT == STD_ON
    FLEXCAN_InterruptType tIntCfg = {0};
    #endif
    tInitCfg.eBaudrate = FLEXCAN_BAUD_250K;
    tInitCfg.bEnRxFifo = FALSE;
    tInitCfg.bEnDma = FALSE;
    #if CAN_FD_ENABLE == STD_ON
    tInitCfg.bEnFd = TRUE;
    tInitCfg.bEnBrs = TRUE;
    tInitCfg.eMbDataWidth = FLEXCAN_DATAWIDTH_64;
    tInitCfg.eDataBaud = FLEXCAN_BAUD_2M;
    #else
    tInitCfg.bEnFd = FALSE;
    tInitCfg.bEnBrs = FALSE;
    tInitCfg.eMbDataWidth = FLEXCAN_DATAWIDTH_8;
    #endif
    #if (CAN_CLOCK_FROM_BUS == STD_ON)
    tInitCfg.eClkSrcSel = CAN_CLOCK_MODULE; /* core/bus clock */
    tInitCfg.eClkSrcHz = SCG_GetCore_Freq();
    #else
    uint32_t u32FuncClk;
    u32FuncClk = PCC_GetPccFunctionClock(s_ePccCan);
    tInitCfg.eClkSrcSel = FLEXCAN_CLOCK_FUNCTION;         /* functional clock */
    tInitCfg.eClkSrcHz = (FLEXCAN_BaudClkType)u32FuncClk; /* function clock frequency */
    #endif
    #if CAN_DIRECT_MODE_ENABLE == STD_ON
    tInitCfg.eDirect = FLEXCAN_DIR_ENABLE_WITHOUT_TRIG;
    #endif
    /* initial can */
    tRetVal = FLEXCAN_Init(u8CanIndex, &tInitCfg);

    if (tRetVal == FLEXCAN_ERROR_OK)
    {
		/* +++++++++++++++++++++++++++++++++++++++ */
		/* +++++++++++ can mb initial ++++++++++++ */

		/* rx config */
		FLEXCAN_MBConfigType tMbCfg = {0};
		FLEXCAN_RxMbFilterType aRxFiltList[2];
		aRxFiltList[0].eRxFrameType = FLEXCAN_ID_STD;
		aRxFiltList[0].u32RxCanId = 0x123;
		aRxFiltList[0].u32RxCanIdMask = 0x7FEU;

        aRxFiltList[1].eRxFrameType = FLEXCAN_ID_STD;
        aRxFiltList[1].u32RxCanId = 0x333U;
        aRxFiltList[1].u32RxCanIdMask = 0x7FFU;
		#if 1
		tMbCfg.pRxFilterMBList = aRxFiltList;
		tMbCfg.u8RxFilterMBCnt = sizeof(aRxFiltList) / sizeof(aRxFiltList[0]);
		#else
		tMbCfg.pRxFilterFifoList = aRxFiltList;
		tMbCfg.u8RxFilterFifoCnt = sizeof(aRxFiltList) / sizeof(aRxFiltList[0]);
		#endif
        tMbCfg.pRxBuf = &s_aaRxDataBuf;
        tMbCfg.pRxFilterFifoList = NULL;      // Не используем FIFO
        tMbCfg.u8RxFilterFifoCnt = 0;
        /* tx config */
        tMbCfg.u8TxMsgCnt = 3U; /* tx occupy 1 mb */
        tRetVal = FLEXCAN_RxFilterConfig(u8CanIndex, &tMbCfg);
        #if CAN_RECEIVE_INTERRUPT == STD_ON
        tIntCfg.bEnErrorInterrupt = 1U;
        tIntCfg.bEnRxMBInterrupt = 1U;
        tIntCfg.bEnTxMBInterrupt = 1U;
        tIntCfg.pErrorNotify = CAN_ErrorInterrupt_CallBack;
        tIntCfg.pRxMBNotify = CAN_RxInterrupt_CallBack;
        tIntCfg.pTxMBNotify = CAN_TxInterrupt_CallBack;
        FLEXCAN_SetInterrupt(u8CanIndex, &tIntCfg);
        //IntMgr_SetPriority(FlexCAN0_IRQn, 3U);

        #endif

        tRetVal = FLEXCAN_Start(u8CanIndex); /* Start CAN */
        IntMgr_SetPriority(FlexCAN0_IRQn, 3U);
        IntMgr_EnableInterrupt(FlexCAN0_IRQn);
        if (tRetVal == FLEXCAN_ERROR_OK) FCUART_Printf(2, "Start CAN%d\n", u8CanIndex);
    }
}

/**
 * \brief CAN transmit special data
 *
 * \param u8CanIndex
 */
static void BSP_CAN_LL_TransmitData(uint8_t u8CanIndex, CAN_TX_DATA_t data)
{
    FLEXCAN_TxMsgType tTxMsg = {0};
    FLEXCAN_ErrorType tRetval;

    FC_OwnMemcpy(tTxMsg.aData, (const uint8_t *)data.buf, data.len);
    tTxMsg.u32CanId = data.id;
    tTxMsg.u8TxHandler = 1U;
    #if CAN_FD_ENABLE == STD_ON
    tTxMsg.bEnFd = TRUE;
    tTxMsg.bEnBrs = TRUE;
    tTxMsg.u32DataLen = 12U;
    #else
    tTxMsg.bEnFd = FALSE;
    tTxMsg.bEnBrs = FALSE;
    tTxMsg.u32DataLen = (uint32_t)data.len;
    #endif
    tTxMsg.eDataType = FLEXCAN_FRAME_DATA;
    tTxMsg.eFrameType = FLEXCAN_ID_STD;
    tTxMsg.bWaitTxCompleted = 1U;
    tTxMsg.u16WaitTxTimeout = 1000U;
    //tRetval = 0U;
    if (flag_Tx_Finished == 1U){
    	flag_Tx_Finished = 0U;
        tRetval = FLEXCAN_TransmitData(u8CanIndex, &tTxMsg);
    }
    else {
    	FCUART_Printf(2, "CAN BUSY\n");
    	return;
    }
    if (tRetval != FLEXCAN_ERROR_OK)
    {
    	flag_Tx_Finished = 1U;
        FLEXCAN_TransmitAbort(u8CanIndex, tTxMsg.u8TxHandler);
        //FCUART_Printf(2, "TX Error: %d\n", tRetval);
    }
    else
    {
        FLEXCAN_TransmitProcess(u8CanIndex, tTxMsg.u8TxHandler);
    }
}

#if CAN_RECEIVE_INTERRUPT == STD_OFF
/**
 * \brief CAN Polling Receive data
 *
 * \param u8CanIndex
 */
static void BSP_CAN_LL_ReceivePolling(uint8_t u8CanIndex)
{
    FLEXCAN_TxMsgType tTxMsg = {0};
    FLEXCAN_ErrorType tRetval;
    FLEXCAN_RxMsgListType tCanRxMsgList = {0};
    uint8_t u8Index;
    tRetval = FLEXCAN_Receive_Polling(u8CanIndex, &tCanRxMsgList);
    if (tRetval != FLEXCAN_ERROR_OK){
        FCUART_Printf(2, "CAN%d receive error: 0x%X\n", u8CanIndex, tRetval);
    }
    for (u8Index = 0; u8Index < tCanRxMsgList.u8RxMsgCnt; u8Index++)
    {
        if (tCanRxMsgList.pRxMsgBuf[u8Index].u32DataLen > 0U)
        {
            FCFUNC_FcOwnMemcpy(tTxMsg.aData, tCanRxMsgList.pRxMsgBuf[u8Index].aData, tCanRxMsgList.pRxMsgBuf[u8Index].u32DataLen, NULL);

            u8CanIndex = tCanRxMsgList.pRxMsgBuf[u8Index].u8CanIndex;
            tTxMsg.u8TxHandler = 1U;
            tTxMsg.u32CanId = tCanRxMsgList.pRxMsgBuf[u8Index].u32CanId + 1;

            tTxMsg.u32DataLen = tCanRxMsgList.pRxMsgBuf[u8Index].u32DataLen;

            tTxMsg.bEnFd = tCanRxMsgList.pRxMsgBuf[u8Index].bEnFd;
            tTxMsg.bEnBrs = tCanRxMsgList.pRxMsgBuf[u8Index].bEnBrs;

            tTxMsg.eDataType = tCanRxMsgList.pRxMsgBuf[u8Index].eDataType;
            tTxMsg.eFrameType = tCanRxMsgList.pRxMsgBuf[u8Index].eFrameType;

            tTxMsg.bWaitTxCompleted = 1U;
            tTxMsg.u16WaitTxTimeout = 10000U;
            FCUART_Printf(2, "Received by CAN%d: adata[0]= %d\n", u8CanIndex, tCanRxMsgList.pRxMsgBuf[u8Index].aData[0]);
            /*tRetval = FLEXCAN_TransmitData(u8CanIndex, &tTxMsg);

            if (tRetval != FLEXCAN_ERROR_OK)
            {
                FLEXCAN_TransmitAbort(u8CanIndex, tTxMsg.u8TxHandler);
            }
            else
            {
                FLEXCAN_TransmitProcess(u8CanIndex, tTxMsg.u8TxHandler);
            }
            */
        }
    }
}
#endif

/* ################################################################################## */
/* ################################ Global Functions ################################ */

void BSP_CAN_Init(void)
{
    uint8_t u8CanIndex;
    u8CanIndex = 0U;
    FLEXCAN_InitMemory(u8CanIndex);
    BSP_CAN_LL_Init(u8CanIndex);
}

uint32_t BSP_CAN_TransmitData(CAN_TX_DATA_t data)
{
    uint8_t u8CanIndex;
    u8CanIndex = 0U;
    BSP_CAN_LL_TransmitData(u8CanIndex, data);
    return 0;
}

void BSP_CAN_MainFunction(void)
{
    #if CAN_RECEIVE_INTERRUPT == STD_OFF
    uint8_t u8CanIndex;
    u8CanIndex = 0U;
    BSP_CAN_LL_ReceivePolling(u8CanIndex);
    #endif
}

#if CAN_RECEIVE_INTERRUPT == STD_ON

static void CAN_ErrorInterrupt_CallBack(uint8_t u8CanIndex, FLEXCAN_ErrorInfoType *pErrorInfo)
{
    FCUART_Printf(2, "CAN%d Error: 0x%X\n", u8CanIndex, pErrorInfo->u32ErrorValue);
    FLEXCAN_ClrErrorInfo(u8CanIndex, pErrorInfo);
}

static void CAN_RxInterrupt_CallBack(uint8_t u8CanIndex, FLEXCAN_RxMsgType *pRxCfg)
{
	//FCUART_Printf(2, "CAN RECEAIVED!");
	if (is_listening_CAN == 1){
		CAN_RX_DATA_t data;
	    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	    FCFUNC_FcOwnMemcpy(data.buf, pRxCfg->aData, (uint32_t)pRxCfg->u32DataLen, NULL);
	    data.len = (uint8_t)pRxCfg->u32DataLen;
	    data.id = pRxCfg->u32CanId;
	    //FCUART_Printf(2, "CAN%d:ID=%X L=%d\n",u8CanIndex, pRxCfg->u32CanId, pRxCfg->u32DataLen);
	    xQueueSendFromISR(xQueue_CAN_RX, &data, &xHigherPriorityTaskWoken);
	    //portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}
static void CAN_TxInterrupt_CallBack(uint8_t u8CanIndex, uint8_t u8TxHandler){
	flag_Tx_Finished = 1U;
    PROCESS_UNUSED_VAR(u8TxHandler)
    PROCESS_UNUSED_VAR(u8CanIndex)
}
#endif
