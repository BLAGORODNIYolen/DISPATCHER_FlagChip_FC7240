#ifndef INCLUDE_Bsp_FCSPI_H_
#define INCLUDE_Bsp_FCSPI_H_


#include "_driver_header.h"
#include "rtos.h"
#define SPI_REC_BUF_COUNT 5
#define FRAME_COUNT  1
void Bsp_FCSpi_Init(void);
uint32_t Bsp_FCSpi_Send_To_Trigger(SPI_TX_DATA_t data);

#endif /* INCLUDE_Bsp_FCSPI_H_ */
