#ifndef INCLUDE_BSP_CAN_H_
#define INCLUDE_BSP_CAN_H_


#include "_driver_header.h"
#include "rtos.h"
void BSP_CAN_Init(void);

uint32_t BSP_CAN_TransmitData(CAN_TX_DATA_t data);

void BSP_CAN_MainFunction(void);

#endif /* INCLUDE_BSP_CAN_H_ */
