/**
 * @file system_init.c
 * @author Flagchip
 * @brief interrupt configuration
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/* ********************************************************************************
  *   Revision History:
  *
  *   Version     Date          Author           Descriptions
  *   ---------   ----------    ------------     ---------------
  *   0.1.0       2024-01-12    Flagchip038      First version for gcc, iar, keil, ghs data init
  ******************************************************************************** */


#include "system_init.h"
#include "fc7xxx_driver_fpu.h"

static void data_clear(uint32_t u32StartAddr, uint32_t u32EndAddr);
static void data_copy(uint32_t u32SourceAddr, uint32_t u32DestAddr, uint32_t u32DestEndAddr);

/**
 * \brief System Initialization
 *
 */
void System_Init(void)
{
    /* disable wdog 0 */
    *(volatile uint32 *)0x40022004 = 0x08181982;
    while (0U == (0x800u & *(volatile uint32 *)0x40022000));
    *(volatile uint32 *)0x40022000 = 0x2920;
    *(volatile uint32 *)0x40022008 = 0xF000;
    while (0U == (0x400u & *(volatile uint32 *)0x40022000));

    /* disable wdog 1 */
    *(volatile uint32 *)0x40433004 = 0x08181982;
    while (0U == (0x800u & *(volatile uint32 *)0x40433000));
    *(volatile uint32 *)0x40433000 = 0x2920;
    *(volatile uint32 *)0x40433008 = 0xF000;
    while (0U == (0x400u & *(volatile uint32 *)0x40433000));

#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
    FPU_Enable();    /* Enable FPU */
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

}

void Data_Init(void)
{
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    extern uint32_t Load$$RW_m_dtcm$$Base;
    extern uint32_t Image$$RW_m_dtcm$$Base;
    extern uint32_t Image$$RW_m_dtcm$$Limit;

    extern uint32_t Image$$RW_m_dtcm$$ZI$$Limit;
    extern uint32_t Image$$RW_m_dtcm$$ZI$$Base;

    extern uint32_t Image$$ARM_LIB_HEAP$$ZI$$Base;
    extern uint32_t Image$$ARM_LIB_HEAP$$ZI$$Limit;

    /* data/bss/heap clear */
    data_clear((uint32_t)&Image$$RW_m_dtcm$$Base, (uint32_t)&Image$$RW_m_dtcm$$Limit);
    data_clear((uint32_t)&Image$$RW_m_dtcm$$ZI$$Base, (uint32_t)&Image$$RW_m_dtcm$$ZI$$Limit);
    data_clear((uint32_t)&Image$$ARM_LIB_HEAP$$ZI$$Base, (uint32_t)&Image$$ARM_LIB_HEAP$$ZI$$Limit);

    /* data */
    data_copy((uint32_t)&Load$$RW_m_dtcm$$Base, (uint32_t)&Image$$RW_m_dtcm$$Base, (uint32_t)&Image$$RW_m_dtcm$$Limit);

#elif defined(__GNUC__) || defined(__ghs__)
    extern uint32 __rom_data_start[];
    extern uint32 __ram_data_start[];
    extern uint32 __ram_data_end[];
    extern uint32 __bss_start[];
    extern uint32 __bss_end[];
    extern uint32 __rom_ncache_data_start[];
    extern uint32 __ram_ncache_data_start[];
    extern uint32 __ram_ncache_data_end[];
    extern uint32 __ncache_bss_start[];
    extern uint32 __ncache_bss_end[];


    /* data clear */
    data_clear((uint32_t)__ram_data_start, (uint32_t)__ram_data_end);
    data_clear((uint32_t)__bss_start, (uint32_t)__bss_end);
    data_clear((uint32_t)__ram_ncache_data_start, (uint32_t)__ram_ncache_data_end);
    data_clear((uint32_t)__ncache_bss_start, (uint32_t)__ncache_bss_end);

    /* data copy */
    data_copy((uint32_t)__rom_data_start, (uint32_t)__ram_data_start, (uint32_t)__ram_data_end);
    data_copy((uint32_t)__rom_ncache_data_start, (uint32_t)__ram_ncache_data_start, (uint32_t)__ram_ncache_data_end);

#elif defined(__ICCARM__)
    #pragma section=".data"
    #pragma section=".data_init"
    #pragma section=".ncsram"
    #pragma section=".ncsram_init"
    #pragma section=".bss"
    #pragma section="RAM_VECTOR"
    #pragma section=".intvec"

    data_clear((uint32_t)__section_begin(".bss"), (uint32_t)__section_end(".bss"));
  
    data_copy((uint32_t)__section_begin(".data_init"), (uint32_t)__section_begin(".data"), (uint32_t)__section_end(".data"));

    data_copy((uint32_t)__section_begin(".ncsram_init"), (uint32_t)__section_begin(".ncsram"), (uint32_t)__section_end(".ncsram"));

#endif
}

/* to avoid ecc issue, FC7240 clear ram with 64bits once after power on reset */
static void data_clear(uint32_t u32StartAddr, uint32_t u32EndAddr)
{
    /* 64 bits align */
    uint32_t u32AlignStart = u32StartAddr & 0xFFFFFFF8;
    uint32_t u32AlignEnd = (u32EndAddr - u32AlignStart);
    volatile uint64_t *pData = (uint64_t *)u32AlignStart;

    /* 32 word Align */
    uint32_t u32LeftCount = u32AlignEnd & 0x1Fu;
    u32AlignEnd = u32EndAddr - u32LeftCount;

    while ((uint32_t)pData < u32AlignEnd)
    {
        *pData++ = 0u;
        *pData++ = 0u;
        *pData++ = 0u;
        *pData++ = 0u;
    }

    while ((uint32_t)pData < u32EndAddr)
    {
        *pData++ = 0u;
    }
}

static void data_copy(uint32_t u32SourceAddr, uint32_t u32DestAddr, uint32_t u32DestEndAddr)
{
    uint32_t *pSource = (uint32_t *)u32SourceAddr;
    uint32_t *pDest = (uint32_t *)u32DestAddr;

    while ((uint32_t)pDest < u32DestEndAddr)
    {
        *pDest = *pSource;
        pDest++;
        pSource++;
    }
}

