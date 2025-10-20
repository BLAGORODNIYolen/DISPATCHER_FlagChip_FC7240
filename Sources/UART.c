#include "UART.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "rtos.h"

static uint8_t s_u8_UART_Rx_Buf[UART_RX_BUF_SIZE]; //is used in receiving in interrupt
static uint16_t s_u16_UART_Rx_Index = 0; //is used in receiving in interrupt

/* data buffer and struct in RAM, only used in Initial */
static FCUART_DataType uart_initial_RX_isr_buf_struct;
static uint8_t  uart_initial_RX_isr_buf[UART_RX_BUF_SIZE];

static volatile uint8_t recv_finish_flag = 1;

static void BSP_FCUART_LL_Init(uint8_t u8UartIndex, uint32_t u32Baud);
static void FCUART_ErrorInterrupt_CallBack(uint8_t u8UartIndex, uint32_t u32Error);
static void FCUART_RxInterrupt_CallBack(uint8_t u8UartIndex, FCUART_DataType *pRxData);
static void FCUART_IldeInterrupt_CallBack(uint8_t u8UartIndex);



void BSP_FCUART_Init(void)
{
    uint8_t          u8UartIndex;
    u8UartIndex = 2;
    FCUART_InitMemory(u8UartIndex);
    BSP_FCUART_LL_Init(u8UartIndex,115200U);
}

uint32_t BSP_FCUART_TRANSMIT(UART_TX_DATA_t data)
{
    uint8_t u8UartIndex= 2;
    FCUART_DataType dataToSend;
    FCUART_ErrorType tRetVal;
    if(1 == recv_finish_flag){
    	dataToSend.pDatas = data.buf;
    	dataToSend.u32DataLen = (uint32_t) data.len;
    	recv_finish_flag = 0;
        tRetVal = FCUART_Transmit(u8UartIndex, &dataToSend);
        if (tRetVal != FCUART_ERROR_OK){
        	return -1;
        }
        recv_finish_flag = 1;
        return 0;
    }
    else{
    	return -1;
    }
}

void FCUART2_RxTx_IRQHandler(void)
{
    FCUARTN_RxTx_IRQHandler(2);
}


static void FCUART_RxInterrupt_CallBack(uint8_t u8UartIndex, FCUART_DataType *pRxData)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    UART_RX_RAW_DATA_t tCmdData;
    // Обрабатываем каждый пришедший байт
    for (uint32_t i = 0; i < pRxData->u32DataLen; i++) {
        uint8_t u8Byte = pRxData->pDatas[i];

        // Если буфер переполнен - сбрасываем
        if (s_u16_UART_Rx_Index >= UART_RX_BUF_SIZE - 1) {
            s_u16_UART_Rx_Index = 0;
        }

        // Если конец команды
        if (u8Byte == '\n' || u8Byte == '\r') {
            if (s_u16_UART_Rx_Index > 0) {
                tCmdData.len = s_u16_UART_Rx_Index;
                FC_OwnMemcpy(tCmdData.buf, s_u8_UART_Rx_Buf, s_u16_UART_Rx_Index);
                tCmdData.buf[s_u16_UART_Rx_Index] = '\0';
                //FCUART_Printf(2, "!\n");
                if (pdPASS != xQueueSendFromISR(xQueue_UART_RX_RAW, &tCmdData, &xHigherPriorityTaskWoken)){
                	FCUART_Printf(2, "UQueue ERROR\n");
                }
            }
            s_u16_UART_Rx_Index = 0;
        } else {
            // Добавляем байт в буфер
            s_u8_UART_Rx_Buf[s_u16_UART_Rx_Index++] = u8Byte;
        }
    }

    //portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

}

static void BSP_FCUART_LL_Init(uint8_t u8UartIndex, uint32_t u32Baud)
{
    FCUART_ErrorType     tRetVal;
    FCUART_InitType      tInitCfg = {0};
    uint32_t             u32PccFuncClk;
    FCUART_InterruptType tInterruptCfg = {0};;

    u32PccFuncClk = PCC_GetPccFunctionClock(PCC_CLK_FCUART2);
    if(u32PccFuncClk != 0U)
    {
        tInitCfg.bEnRxFifo = false;                                       /* UART rx fifo ensable           */
        //tInitCfg.u8RxFifoWaterMark = 15U;                                /* UART rx fifo watermark         */
        //tInitCfg.eFifoRxIdleCharNum = FCUART_FIFO_RX_IDLE_CHARACTER_64;  /* UART rx fifo idle character    */
        //tInitCfg.eIdleCharNum = FCUART_IDLE_CHARCTER_64;  /* UART idle interrupt character       */
        //tInitCfg.eIdleStart = FCUART_START_AFTER_STOPBIT; /* UART idle interrupt start           */
        tInitCfg.u32Baudrate = u32Baud;                   /* UART baud-rate            */
        tInitCfg.eBitMode = UART_BITMODE_8;               /* UART bit mode             */
        tInitCfg.bParityEnable = false;                   /* UART parity check enable  */
        tInitCfg.eStopBit = UART_STOPBIT_NUM_1;           /* UART stop bit number      */
        tInitCfg.u32ClkSrcHz = u32PccFuncClk;             /* UART function clock       */
        tInitCfg.u32TransmitTimeout = 3000U;;       /* Transmit timeout tick     */
        /* start initial UART */
        tRetVal = FCUART_Init(u8UartIndex, &tInitCfg);

        if(tRetVal == FCUART_ERROR_OK)
        {
        	uart_initial_RX_isr_buf_struct.pDatas = uart_initial_RX_isr_buf;   /* data buffer must set an array address */
        	tInterruptCfg.pRxBuf = &uart_initial_RX_isr_buf_struct;
            //error
            tInterruptCfg.bEnErrorInterrupt = false;
            tInterruptCfg.pErrorNotify = FCUART_ErrorInterrupt_CallBack;
            //rx
            tInterruptCfg.bEnRxInterrupt = true;
            tInterruptCfg.pRxNotify = FCUART_RxInterrupt_CallBack;
            //tx
            tInterruptCfg.bEnTxInterrupt = false;
            tInterruptCfg.pTxEmptyNotify = NULL;
            tInterruptCfg.pTxCompleteNotify = NULL;
            //idle
            tInterruptCfg.bEnIdleInterrupt = false;
            tInterruptCfg.pIdleNotify = FCUART_IldeInterrupt_CallBack;

            tRetVal = FCUART_SetInterrupt(u8UartIndex, &tInterruptCfg);

            IntMgr_SetPriority(FCUART2_IRQn, 3U);
            IntMgr_EnableInterrupt(FCUART2_IRQn);

            tRetVal = FCUART_StartReceive(u8UartIndex);
            if(tRetVal != FCUART_ERROR_OK){
            	FCUART_Printf(2, "UART is not READY\n");
            }
        }
        else
        {
          /* No deal with */
        }
    }
}

static void FCUART_ErrorInterrupt_CallBack(uint8_t u8UartIndex, uint32_t u32Error)
{
    GPIO_Toggle(GPIO_A, PORT_PIN_8);
}

static void FCUART_IldeInterrupt_CallBack(uint8_t u8UartIndex)
{
    PROCESS_UNUSED_VAR(u8UartIndex)
}

