/**
 * @file system_init.h
 * @author Flagchip
 * @brief interrupt configuration
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
#if !defined(SYSTEM_INIT_H)
#define SYSTEM_INIT_H


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/


#include "device_header.h"

void System_Init(void);

void Data_Init(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/



#endif /* SYSTEM_INIT_H */
