/*
 * driver_header.h
 *
 */

#ifndef INCLUDE_DRIVER_HEADER_H_
#define INCLUDE_DRIVER_HEADER_H_

#define SPI_TX_DATA_BUF_SIZE 8
#define UART_TX_DATA_BUF_SIZE 8
#define CAN_TX_DATA_BUF_SIZE 8
#define CAN_RX_DATA_BUF_SIZE 128
#define MESSAGE_DATA_BUF_SIZE 128
#define TOKEN_COUNT 15 // количество параметров команды UART



#include <interrupt_manager.h>
#include "fc7xxx_driver_fpu.h"
#include "fc7xxx_driver_pcc.h"
#include "fc7xxx_driver_port.h"
#include "fc7xxx_driver_scg.h"
#include "fc7xxx_driver_gpio.h"
#include "fc7xxx_driver_fcuart.h"
#include "fc7xxx_driver_fcspi.h"
#include "fc7xxx_driver_flexcan.h"

#endif /* INCLUDE_DRIVER_HEADER_H_ */
