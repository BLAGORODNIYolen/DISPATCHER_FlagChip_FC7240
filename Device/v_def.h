/**
 * @file v_def.h
 * @author Flagchip
 * @brief variables type define
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
#ifndef DEVICE_V_DEF_H_
#define DEVICE_V_DEF_H_

#ifndef TRUE
    #define TRUE   1U
#endif

#ifndef FALSE
    #define FALSE  0U
#endif

#ifndef NULL_PTR
    #define NULL_PTR  ((void*)0)
#endif

#ifndef int8
    typedef signed char int8;
#endif

#ifndef int16
    typedef signed short int16;
#endif

#ifndef int32
    typedef signed int int32;
#endif

#ifndef uint8
    typedef unsigned char uint8;
#endif

#ifndef uint16
    typedef unsigned short uint16;
#endif

#ifndef uint32
    typedef unsigned int uint32;
#endif

#ifndef boolean
    typedef uint8_t boolean;
#endif

typedef void (*void_functype)(void);

#ifdef __GUNC__

#endif

#endif /* DEVICE_V_DEF_H_ */
