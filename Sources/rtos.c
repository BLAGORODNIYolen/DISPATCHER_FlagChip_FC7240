/*
 * rtos.c
 *
 */
/* Kernel includes. */


#include "GPIO.h"
#include "UART.h"
#include "FCSpi.h"
#include "CAN.h"

#include <string.h>
#include <stdbool.h>


volatile uint8_t is_listening_CAN = 0;

#define SIMPLE_TEST_COUNT (sizeof(s_SimpleTestCommands) / sizeof(s_SimpleTestCommands[0]))

/* The number of items the queue can hold.  This is 1 as the receive task
will remove items as they are added, meaning the send task should always find
the queue empty. */
#define mainQUEUE_LENGTH                    ( 1 )

/* A block time of zero simply means "don't block". */
#define mainDONT_BLOCK                      ( 0UL )

static bool parse_decimal_u8(const char* str, uint8_t* result);
static bool parse_hex_u32(const char* str, uint32_t* result);
static bool parse_hex_byte(const char* str, uint8_t* result);
static uint8_t hex_char_to_val(char c);
static bool is_hex_char(char c);
static void parse_command(UART_RX_RAW_DATA_t* cmd);
static void send_debug_message(const char* message);
static uint8_t tokenize_string(char* str, char* tokens[], uint8_t max_tokens);
static uint8_t string_length(const char* str);
static bool string_starts_with(const char* str, const char* prefix);
static bool string_equals(const char* str1, const char* str2);
static void byte_to_hex(uint8_t byte, char* hex_buf);
static void send_can_rx_debug_message(const CAN_RX_DATA_t* can_data);
//Моя реализация
QueueHandle_t xQueue_Command;  // Приём команд → Парсинг (
QueueHandle_t xQueue_SPI;      // Парсинг → SPI
QueueHandle_t xQueue_CAN_Tx;   // Парсинг → CAN Tx
QueueHandle_t xQueue_Debug;    // Задачи → Отладочный вывод ( Message_t )
QueueHandle_t xQueue_UART_Tx; // Парсинг -> UART Tx
QueueHandle_t xQueue_UART_RX_RAW; //User -> Прием команд(ISR)

//QueueHandle_t xQueue_UART_RX;
QueueHandle_t xQueue_CAN_RX;




void HardFault_Handler(void){
    GPIO_Toggle(GPIO_A, PORT_PIN_8);
    while(1){};
}
void vApplicationMallocFailedHook(void)
{
    /* Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	FCUART_Printf(2, "NO memory\n");
    taskDISABLE_INTERRUPTS();
    for (;;);
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    (void) pcTaskName;
    (void) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */
	FCUART_Printf(2, "STACK OVERFLOW\n");
    taskDISABLE_INTERRUPTS();
    for (;;);
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook(void)
{
    volatile size_t xFreeHeapSpace;

    /* This function is called on each cycle of the idle task.  In this case it
    does nothing useful, other than report the amount of FreeRTOS heap that
    remains unallocated. */
    xFreeHeapSpace = xPortGetFreeHeapSize();

    if (xFreeHeapSpace > 100)
    {
        /* By now, the kernel has allocated everything it is going to, so
        if there is a lot of heap remaining unallocated then
        the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
        reduced accordingly. */
    }

}

/* A tick hook is used by the "Full" build configuration.  The Full and blinky
build configurations share a FreeRTOSConfig.h header file, so this simple build
configuration also has to define a tick hook - even though it does not actually
use it for anything. */
void vApplicationTickHook(void) {}

void rtos_start(void)
{
	xQueue_UART_RX_RAW = xQueueCreate(20, sizeof(UART_RX_RAW_DATA_t));
	xQueue_Command = xQueueCreate(10, sizeof(UART_RX_RAW_DATA_t));
	xQueue_SPI = xQueueCreate(5, sizeof(SPI_TX_DATA_t));
	xQueue_CAN_Tx = xQueueCreate(5, sizeof(CAN_TX_DATA_t));
	xQueue_UART_Tx = xQueueCreate(5, sizeof(UART_TX_DATA_t));
	xQueue_Debug = xQueueCreate(20, sizeof(Message_t));
	xQueue_CAN_RX = xQueueCreate(20, sizeof(CAN_RX_DATA_t));
    if (xQueue_CAN_RX != NULL && xQueue_UART_RX_RAW != NULL && xQueue_UART_Tx != NULL && xQueue_Command != NULL && xQueue_SPI != NULL && xQueue_CAN_Tx != NULL && xQueue_Debug != NULL)
    {
		xTaskCreate(vUART_Receive_Task, "UART_Rx", 1024, NULL, 5, NULL);
		xTaskCreate(vCommand_Parser_Task, "Parser", 1024, NULL, 4, NULL);
		xTaskCreate(vCAN_Listen_Task, "CAN_Rx", 512, NULL, 3, NULL);
		xTaskCreate(vSPI_Send_Task, "SPI_Tx", 256, NULL, 2, NULL);
		xTaskCreate(vCAN_Send_Task, "CAN_Tx", 1024, NULL, 2, NULL);
		xTaskCreate(vUART_Send_Task, "UART_Tx", 1024, NULL, 2, NULL);
		xTaskCreate(vLED_Blink_Task, "LED", 1024, NULL, 1, NULL);
		xTaskCreate(vDebug_Print_Task, "Debug", 1024, NULL, 1, NULL);
		vTaskStartScheduler();
    }
}

/*		ЗАДАЧИ		*/
// Задача приёма UART
void vUART_Receive_Task(void *pvParameters) {
	UART_RX_RAW_DATA_t cmd;
	while(1){
		if (xQueueReceive(xQueue_UART_RX_RAW, &cmd, portMAX_DELAY)){
			if (cmd.len > 0){
				send_debug_message((const char *) cmd.buf);
				xQueueSend(xQueue_Command,&cmd, 0);
			}
		}
	}
    PROCESS_UNUSED_VAR(pvParameters)
}

// Задача парсинга команд
void vCommand_Parser_Task(void *pvParameters) {
    UART_RX_RAW_DATA_t cmd;
    while(1) {
        if(xQueueReceive(xQueue_Command, &cmd, portMAX_DELAY)) {
            parse_command(&cmd);
        }
    }
    PROCESS_UNUSED_VAR(pvParameters)
}

// Остальные задачи-заглушки
void vCAN_Listen_Task(void *pvParameters) {
	CAN_RX_DATA_t data;
  while(1) {
      if(xQueueReceive(xQueue_CAN_RX, &data, portMAX_DELAY)) {
    	  send_debug_message("OK: CAN GET");
    	  send_can_rx_debug_message(&data);
      }
  }
  PROCESS_UNUSED_VAR(pvParameters)
}

void vSPI_Send_Task(void *pvParameters) {
	SPI_TX_DATA_t data;
	while(1) {
		if(xQueueReceive(xQueue_SPI, &data, portMAX_DELAY)) {
			if (Bsp_FCSpi_Send_To_Trigger(data) == 0){
				send_debug_message("OK: SPI DATA SENT");
			}
			else{
				send_debug_message("ERROR: SPI NOT SENT");
			}
		}
	}
	PROCESS_UNUSED_VAR(pvParameters)
}

void vCAN_Send_Task(void *pvParameters) {
	CAN_TX_DATA_t data;

	while(1) {
		if(xQueueReceive(xQueue_CAN_Tx, &data, portMAX_DELAY)) {
			if (0 == BSP_CAN_TransmitData(data)){
				send_debug_message("OK: CAN DATA SENT");
			}
			else{
				send_debug_message("ERROR: CAN DATA NOT SENT");
			}
		}
	}
    PROCESS_UNUSED_VAR(pvParameters)
}

void vUART_Send_Task(void *pvParameters) {
	UART_TX_DATA_t data;
	while(1) {
		if(xQueueReceive(xQueue_UART_Tx, &data, portMAX_DELAY)) {
			if (BSP_FCUART_TRANSMIT(data) == 0){
				send_debug_message("OK: UART DATA SENT");
			}
			else{
				send_debug_message("ERROR: UART NOT SENT");
			}
		}
	}
    PROCESS_UNUSED_VAR(pvParameters)
}

void vLED_Blink_Task(void *pvParameters) {
	uint8_t u8TestIndex = 0;
	while(1) {
		Bsp_Gpio_Toggle();
        /*if (u8TestIndex < SIMPLE_TEST_COUNT) {
        	send_debug_message("\n test:");
        	send_debug_message(s_SimpleTestCommands[u8TestIndex].buf);
            xQueueSend(xQueue_UART_RX_RAW, &s_SimpleTestCommands[u8TestIndex], 0);
            u8TestIndex++;
        } else {
            u8TestIndex = 0; // Начинаем заново
        }*/
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
    PROCESS_UNUSED_VAR(pvParameters)

}

void vDebug_Print_Task(void *pvParameters) {
	Message_t msg;
	while(1) {
		if(xQueueReceive(xQueue_Debug, &msg, portMAX_DELAY)) {
			FCUART_Printf(2, "%s", msg.buf);
		}
	}
	PROCESS_UNUSED_VAR(pvParameters)
}

void fill_buf(uint8_t *buf, uint8_t len, uint8_t *data){
	if (len == 0) return;
	for (uint8_t i = 0; i < len; i++){
		buf[i] = data[i];
	}
}

static void send_debug_message(const char* message) {
    Message_t msg;
    fill_msg(msg.buf, (char *) message);
    msg.len = strlen(message);
    xQueueSend(xQueue_Debug, &msg, 0);
}

void fill_msg(uint8_t *buf, char *data){
    uint8_t len = strlen(data);

    if (len == 0){
        buf[0] = '\0';
        return;
    }

    // Проверяем, помещается ли строка + '\n' + '\0'
    if (len >= MESSAGE_DATA_BUF_SIZE - 2) {
        len = MESSAGE_DATA_BUF_SIZE - 2; // Оставляем место для '\n' и '\0'
    }

    for (uint8_t i = 0; i < len; i++){
        buf[i] = data[i];
    }

    buf[len] = '\n';
    buf[len + 1] = '\0';
}

// Основная функция парсера
// Вспомогательные функции для замены strcmp/strtok
static bool string_equals(const char* str1, const char* str2) {
    while (*str1 && *str2 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
}

static bool string_starts_with(const char* str, const char* prefix) {
    while (*prefix) {
        if (*str++ != *prefix++) {
            return false;
        }
    }
    return true;
}

static uint8_t string_length(const char* str) {
    uint8_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Замена strtok - токенизация без динамической памяти
static uint8_t tokenize_string(char* str, char* tokens[], uint8_t max_tokens) {
    uint8_t token_count = 0;
    bool in_token = false;

    for (uint8_t i = 0; str[i] != '\0' && token_count < max_tokens; i++) {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n') {
            str[i] = '\0'; // Заменяем разделители на нуль-терминаторы
            in_token = false;
        } else {
            if (!in_token) {
                tokens[token_count++] = &str[i];
                in_token = true;
            }
        }
    }

    return token_count;
}

// Упрощенный парсер команд
static void parse_command(UART_RX_RAW_DATA_t* cmd) {
    char* tokens[TOKEN_COUNT];
    uint8_t token_count = 0;

    // Токенизация строки (без strtok)
    token_count = tokenize_string((char*)cmd->buf, tokens, TOKEN_COUNT);

    if (token_count < 2) {
        send_debug_message("ERROR: Too few tokens");
        return;
    }

    // Обработка команд CAN (без strcmp)
    if (string_equals(tokens[0], "CAN")) {
        if (string_equals(tokens[1], "SEND")) {
            if (token_count < 5) {
                send_debug_message("ERROR: CAN SEND requires ID, length and data");
                return;
            }

            CAN_TX_DATA_t can_data = {0};

            // Парсинг ID
            if (!parse_hex_u32(tokens[2], &can_data.id)) {
                send_debug_message("ERROR: Invalid CAN ID format");
                return;
            }

            // Парсинг длины данных
            uint8_t data_len;
            if (!parse_decimal_u8(tokens[3], &data_len)) {
                send_debug_message("ERROR: Invalid data length format");
                return;
            }

            if (data_len > CAN_TX_DATA_BUF_SIZE) {
                send_debug_message("ERROR: Data length exceeds maximum");
                return;
            }

            if (token_count != 4 + data_len) {
                send_debug_message("ERROR: Data length mismatch");
                return;
            }

            // Парсинг данных
            for (uint8_t i = 0; i < data_len; i++) {
                if (!parse_hex_byte(tokens[4 + i], &can_data.buf[i])) {
                    send_debug_message("ERROR: Invalid data byte format");
                    return;
                }
            }
            can_data.len = data_len;

            // Отправка в очередь CAN
            if (xQueueSend(xQueue_CAN_Tx, &can_data, 0) == pdPASS) {
                send_debug_message("OK: CMD ACCEPT");
            } else {
                send_debug_message("ERROR: CAN queue full");
            }

        } else if (string_equals(tokens[1], "LISTEN")) {
            if (token_count != 3) {
                send_debug_message("ERROR: CAN LISTEN requires ON/OFF");
                return;
            }

            if (string_equals(tokens[2], "ON")) {
            	is_listening_CAN = 1;
                send_debug_message("OK: CAN LISTEN ON");
            } else if (string_equals(tokens[2], "OFF")) {
            	is_listening_CAN = 0;
                send_debug_message("OK: CAN LISTEN OFF");
            } else {
                send_debug_message("ERROR: Invalid CAN LISTEN parameter");
            }
        } else {
            send_debug_message("ERROR: Unknown CAN command");
        }
    }
    // Обработка команд UART
    else if (string_equals(tokens[0], "UART")) {
        if (string_equals(tokens[1], "SEND")) {
            if (token_count < 4) {
                send_debug_message("ERROR: UART SEND requires length and data");
                return;
            }

            UART_TX_DATA_t uart_data = {0};

            // Парсинг длины данных
            uint8_t data_len;
            if (!parse_decimal_u8(tokens[2], &data_len)) {
                send_debug_message("ERROR: Invalid data length format");
                return;
            }

            if (data_len > UART_TX_DATA_BUF_SIZE) {
                send_debug_message("ERROR: Data length exceeds maximum");
                return;
            }

            if (token_count != 3 + data_len) {
                send_debug_message("ERROR: Data length mismatch");
                return;
            }

            // Парсинг данных
            for (uint8_t i = 0; i < data_len; i++) {
                if (!parse_hex_byte(tokens[3 + i], &uart_data.buf[i])) {
                    send_debug_message("ERROR: Invalid data byte format");
                    return;
                }
            }
            uart_data.len = data_len;

            // Отправка в очередь UART
            if (xQueueSend(xQueue_UART_Tx, &uart_data, 0) == pdPASS) {
                send_debug_message("OK: CMD ACCEPT");
            } else {
                send_debug_message("ERROR: UART queue full");
            }

        } else if (string_equals(tokens[1], "LISTEN")) {
            if (token_count != 3) {
                send_debug_message("ERROR: UART LISTEN requires ON/OFF");
                return;
            }

            if (string_equals(tokens[2], "ON")) {
                send_debug_message("OK: UART LISTEN ON");
            } else if (string_equals(tokens[2], "OFF")) {
                send_debug_message("OK: UART LISTEN OFF");
            } else {
                send_debug_message("ERROR: Invalid UART LISTEN parameter");
            }
        } else {
            send_debug_message("ERROR: Unknown UART command");
        }
    }
    // Обработка команд SPI
    else if (string_equals(tokens[0], "SPI")) {
        if (string_equals(tokens[1], "SEND")) {
            if (token_count < 4) {
                send_debug_message("ERROR: SPI SEND requires length and data");
                return;
            }

            SPI_TX_DATA_t spi_data = {0};

            // Парсинг длины данных
            uint8_t data_len;
            if (!parse_decimal_u8(tokens[2], &data_len)) {
                send_debug_message("ERROR: Invalid data length format");
                return;
            }

            if (data_len > SPI_TX_DATA_BUF_SIZE) {
                send_debug_message("ERROR: Data length exceeds maximum");
                return;
            }

            if (token_count != 3 + data_len) {
                send_debug_message("ERROR: Data length mismatch");
                return;
            }

            // Парсинг данных
            for (uint8_t i = 0; i < data_len; i++) {
                if (!parse_hex_byte(tokens[3 + i], &spi_data.buf[i])) {
                    send_debug_message("ERROR: Invalid data byte format");
                    return;
                }
            }
            spi_data.len = data_len;

            // Отправка в очередь SPI
            if (xQueueSend(xQueue_SPI, &spi_data, 0) == pdPASS) {
                send_debug_message("OK: CMD ACCEPT");
            } else {
                send_debug_message("ERROR: SPI queue full");
            }
        } else {
            send_debug_message("ERROR: Unknown SPI command");
        }
    } else {
        send_debug_message("ERROR: Unknown interface");
    }
}
// Вспомогательные функции
static bool is_hex_char(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

static uint8_t hex_char_to_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

static bool parse_hex_byte(const char* str, uint8_t* result) {
    if (!str || strlen(str) != 2 || !is_hex_char(str[0]) || !is_hex_char(str[1])) {
        return false;
    }
    *result = (hex_char_to_val(str[0]) << 4) | hex_char_to_val(str[1]);
    return true;
}

static bool parse_hex_u32(const char* str, uint32_t* result) {
    if (!str || strlen(str) == 0) return false;

    *result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_hex_char(str[i])) return false;
        *result = (*result << 4) | hex_char_to_val(str[i]);
    }
    return true;
}

static bool parse_decimal_u8(const char* str, uint8_t* result) {
    if (!str || strlen(str) == 0) return false;

    *result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') return false;
        *result = *result * 10 + (str[i] - '0');
    }
    return true;
}

/**
 * @brief Конвертирует байт в hex строку (2 символа)
 */
static void byte_to_hex(uint8_t byte, char* hex_buf) {
    const char hex_chars[] = "0123456789ABCDEF";
    hex_buf[0] = hex_chars[(byte >> 4) & 0x0F];
    hex_buf[1] = hex_chars[byte & 0x0F];
}

/**
 * @brief Формирует отладочное сообщение для принятых CAN данных
 */
static void send_can_rx_debug_message(const CAN_RX_DATA_t* can_data) {
    char msg_buf[MESSAGE_DATA_BUF_SIZE];
    uint8_t msg_len = 0;

    // Базовое сообщение
    const char prefix[] = "CAN RX: ID=0x";
    for (uint8_t i = 0; prefix[i] != '\0' && msg_len < MESSAGE_DATA_BUF_SIZE - 1; i++) {
        msg_buf[msg_len++] = prefix[i];
    }

    // Добавляем ID в hex
    uint32_t id = can_data->id;
    char id_hex[9]; // 8 hex digits + null terminator
    for (int8_t i = 7; i >= 0; i--) {
        id_hex[i] = "0123456789ABCDEF"[(id >> (4 * (7 - i))) & 0xF];
    }
    id_hex[8] = '\0';

    // Убираем ведущие нули
    uint8_t start_pos = 0;
    while (start_pos < 7 && id_hex[start_pos] == '0') {
        start_pos++;
    }

    for (uint8_t i = start_pos; id_hex[i] != '\0' && msg_len < MESSAGE_DATA_BUF_SIZE - 1; i++) {
        msg_buf[msg_len++] = id_hex[i];
    }

    // Добавляем длину данных
    const char len_str[] = " LEN=";
    for (uint8_t i = 0; len_str[i] != '\0' && msg_len < MESSAGE_DATA_BUF_SIZE - 1; i++) {
        msg_buf[msg_len++] = len_str[i];
    }

    // Преобразуем длину в строку
    uint8_t data_len = can_data->len;
    char len_buf[4];
    uint8_t len_digits = 0;

    if (data_len == 0) {
        len_buf[len_digits++] = '0';
    } else {
        uint8_t temp = data_len;
        while (temp > 0) {
            len_buf[len_digits++] = '0' + (temp % 10);
            temp /= 10;
        }
        // Разворачиваем цифры
        for (uint8_t i = 0; i < len_digits / 2; i++) {
            char temp = len_buf[i];
            len_buf[i] = len_buf[len_digits - 1 - i];
            len_buf[len_digits - 1 - i] = temp;
        }
    }
    len_buf[len_digits] = '\0';

    for (uint8_t i = 0; i < len_digits && msg_len < MESSAGE_DATA_BUF_SIZE - 1; i++) {
        msg_buf[msg_len++] = len_buf[i];
    }

    // Добавляем данные если они есть
    if (data_len > 0) {
        const char data_str[] = " DATA=";
        for (uint8_t i = 0; data_str[i] != '\0' && msg_len < MESSAGE_DATA_BUF_SIZE - 1; i++) {
            msg_buf[msg_len++] = data_str[i];
        }

        // Добавляем данные в hex формате
        for (uint8_t i = 0; i < data_len && msg_len < MESSAGE_DATA_BUF_SIZE - 3; i++) {
            if (i > 0) {
                msg_buf[msg_len++] = ' ';
            }
            char hex_byte[3];
            byte_to_hex(can_data->buf[i], hex_byte);
            hex_byte[2] = '\0';

            msg_buf[msg_len++] = hex_byte[0];
            msg_buf[msg_len++] = hex_byte[1];
        }
    }

    msg_buf[msg_len] = '\0';
    send_debug_message(msg_buf);
}

