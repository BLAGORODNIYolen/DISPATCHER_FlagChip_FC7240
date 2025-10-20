/**
 * @file compiler.h
 * @author Flagchip
 * @brief compiler define
 * @version 0.1.1
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
#ifndef DEVICE_COMPILER_H_
#define DEVICE_COMPILER_H_


#ifndef __IO
    #ifdef __cplusplus
        #define   __I     volatile             /*!< Defines 'read only' permissions                 */
    #else
        #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
    #endif
    #define     __O     volatile             /*!< Defines 'write only' permissions                */
    #define     __IO    volatile             /*!< Defines 'read / write' permissions              */
#endif


#if defined (__GNUC__)
    #define INLINE           __attribute__((always_inline)) inline
    #define LOCAL_INLINE     __attribute__((always_inline)) static inline

#else
    #define INLINE           inline
    #define LOCAL_INLINE     static inline

#endif

#if (defined(__ICCARM__))
#define STRINGIZE(x)     #x
#define ALIGN(n)         _Pragma(STRINGIZE(data_alignment=(n)))
#define PACKED           __packed
#endif

#if (defined(__GNUC__))
#define ALIGN(n)         __attribute__ ((aligned (n)))
#define PACKED           __packed
#endif

#if (defined(__ghs__))
#define INLINE           inline
#define LOCAL_INLINE     static inline
#define ALIGN(n)         __attribute__((aligned(n)))
#define PCAKED           __attribute__((packed))
#endif

#endif /* DEVICE_COMPILER_H_ */
