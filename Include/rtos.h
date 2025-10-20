/*
 * rtos.h
 *
 */

#ifndef INCLUDE_RTOS_H_
#define INCLUDE_RTOS_H_
#include "_driver_header.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

extern QueueHandle_t xQueue_UART_RX_RAW;
//extern QueueHandle_t xQueue_UART_RX;
extern QueueHandle_t xQueue_CAN_RX;

typedef struct {
	uint8_t buf[MESSAGE_DATA_BUF_SIZE];
	uint8_t len;
}Message_t;
typedef struct {
	uint8_t buf[SPI_TX_DATA_BUF_SIZE];
	uint8_t len;
	uint8_t rx_buf[SPI_TX_DATA_BUF_SIZE];
}SPI_TX_DATA_t;
typedef struct {
	uint8_t buf[CAN_TX_DATA_BUF_SIZE];
	uint8_t len;
	uint32_t id;
}CAN_TX_DATA_t;
typedef struct {
	uint8_t buf[CAN_RX_DATA_BUF_SIZE];
	uint8_t len;
	uint32_t id;
}CAN_RX_DATA_t;
typedef struct {
	uint8_t buf[UART_TX_DATA_BUF_SIZE];
	uint8_t len;
}UART_TX_DATA_t;

extern volatile uint8_t is_listening_CAN;

void rtos_start(void);
void fill_buf(uint8_t *buf, uint8_t len, uint8_t *data);
void fill_msg(uint8_t *buf, char *data);

void vUART_Receive_Task(void *pvParameters);
void vCommand_Parser_Task(void *pvParameters);
void vCAN_Listen_Task(void *pvParameters);
void vSPI_Send_Task(void *pvParameters);
void vCAN_Send_Task(void *pvParameters);
void vUART_Send_Task(void *pvParameters);
void vLED_Blink_Task(void *pvParameters);
void vDebug_Print_Task(void *pvParameters);


#endif /* INCLUDE_RTOS_H_ */
