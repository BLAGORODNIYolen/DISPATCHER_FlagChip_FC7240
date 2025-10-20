#ifndef INCLUDE_BSP_UART_H_
#define INCLUDE_BSP_UART_H_

#include "_driver_header.h"
#include "rtos.h"
#define UART_RX_BUF_SIZE 250 //is used in receiving in interrupt

#define UART_CMD_MAX_LENGTH 128 //is used in UART_RX_RAW_DATA_t(прием данных)
typedef struct {
    uint8_t buf[UART_CMD_MAX_LENGTH];
    uint8_t len;
} UART_RX_RAW_DATA_t;

//@brief Initial UART as baud-rate 115200/8/N/1
void BSP_FCUART_Init(void);
uint32_t BSP_FCUART_TRANSMIT(UART_TX_DATA_t data);
//call HAndler from uart driver
void FCUART2_RxTx_IRQHandler(void);

#endif /* INCLUDE_BSP_UART_H_ */
