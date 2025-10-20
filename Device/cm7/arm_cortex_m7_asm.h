#ifndef _DEVICE_CM7_ARM_CORTEXM7_ASM_H_
#define _DEVICE_CM7_ARM_CORTEXM7_ASM_H_


/** \brief  Reverse byte order in a word.
 */
#if defined (__GNUC__) || defined (__ICCARM__) || defined (__ghs__) || defined (__ARMCC_VERSION)
#define REV_BYTES_32(a, b) __asm volatile ("rev %0, %1" : "=r" (b) : "r" (a))
#else
#define REV_BYTES_32(a, b) (b = ((a & 0xFF000000U) >> 24U) | ((a & 0xFF0000U) >> 8U) \
                                | ((a & 0xFF00U) << 8U) | ((a & 0xFFU) << 24U))
#endif

/** \brief  Enter low-power standby state
 *    WFI (Wait For Interrupt) makes the processor suspend execution (Clock is stopped) until an IRQ interrupts.
 */
#if defined (__GNUC__)
#define STANDBY() __asm volatile ("wfi")
#else
#define STANDBY() __asm("wfi")
#endif

#endif
