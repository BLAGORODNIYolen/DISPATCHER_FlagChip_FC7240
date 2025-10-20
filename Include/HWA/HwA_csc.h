/**
 * @file HwA_csc.h
 * @author Flagchip085
 * @brief Hardware access layer for CSC
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0      2024-01-12    Flagchip085     N/A          First version for FC7240
   ******************************************************************************** */

#ifndef _HWA_CSC_H_
#define _HWA_CSC_H_

#include "device_header.h"

#define CSC_STOP_PERIPH_GROUP_MAX        3U

#define CSC_STOP_PERIPH_GROUP0_MASK     (CSC0_STOP_MODER0_MASK & 0x00FFFFFFU)

#define CSC_STOP_PERIPH_GROUP1_MASK     (CSC0_STOP_MODER1_MASK & 0x00FFFFFFU)

#define CSC_STOP_PERIPH_GROUP2_MASK     (CSC0_STOP_MODER2_MASK & 0x00FFFFFFU)

#define CSC_SMU_CTRL_GROUP0_MASK         (CSC0_SMU_CTRL0_MASK & 0xFFFFFFFEU)

#define CSC_SMU_CTRL_GROUP1_MASK         (CSC0_SMU_CTRL1_MASK & 0xFFFFFFFEU)

#define CSC_SMU_CTRL_GROUP4_MASK         (CSC0_SMU_CTRL4_MASK & 0xFFFFFFFEU)

#define CSC_SMU_CTRL_GROUP5_MASK         (CSC0_SMU_CTRL5_MASK & 0xFFFFFFFEU)


/********* Local typedef ************/

/**
 * @brief Control cpu type
 *
 */
typedef enum
{
    CSC_WP_CPU_ALL  = 0U,  /*!< All CPUs are allowed to write this peripheral */
    CSC_WP_CPU_0    = 1U,  /*!< Only CPU0 is allowed to control this peripheral */
    CSC_WP_CPU_NONE = 2U   /*!< No CPU is allowed to control this peripheral */
} CSC_WPB_CpuType;

/**
 * @brief Hand shake mode type
 *
 */
typedef enum
{
    CSC_WAIT_ALL_ACK    = 0U, /*!< follow other master stop acknowledge state */
    CSC_WAIT_REQ_ACK    = 3U  /*!< follow cpu stop acknowledge state */
} CSC_HandShakeModeType;

/**
 * @brief CSC0 clock out divide ratio type
 *
 */
typedef enum
{
    CSC0_CLKOUT_DIV_BY1 = 0U,       /*!< Divided by 1 */
    CSC0_CLKOUT_DIV_BY2 = 1U,       /*!< Divided by 2 */
    CSC0_CLKOUT_DIV_BY3 = 2U,       /*!< Divided by 3 */
    CSC0_CLKOUT_DIV_BY4 = 3U,       /*!< Divided by 4 */
    CSC0_CLKOUT_DIV_BY5 = 4U,       /*!< Divided by 5 */
    CSC0_CLKOUT_DIV_BY6 = 5U,       /*!< Divided by 6 */
    CSC0_CLKOUT_DIV_BY7 = 6U,       /*!< Divided by 7 */
    CSC0_CLKOUT_DIV_BY8 = 7U        /*!< Divided by 8 */
} CSC0_ClockOutDivType;

/**
 * @brief CSC0 clock out source type
 *
 */
typedef enum
{
    CSC0_CLKOUT_SCG_CLKOUT    = 0U,  /*!< SCG CLKOUT */
    CSC0_CLKOUT_FOSC_DIVM_CLK = 2U,  /*!< FOSC DIVM CLK */
    CSC0_CLKOUT_SLOW_CLK      = 3U,  /*!< SLOW CLK */
    CSC0_CLKOUT_SIRC_DIVM_CLK = 4U,  /*!< SIRC DIVM CLK */
    CSC0_CLKOUT_PLL1_DIVM_CLK = 5U,  /*!< PLL1 DIVM CLK */
    CSC0_CLKOUT_FIRC_DIVM_CLK = 6U,  /*!< FIRC DIVM CLK */
    CSC0_CLKOUT_CORE_CLK      = 7U,  /*!< CORE CLK */
    CSC0_CLKOUT_PLL0_DIVM_CLK = 8U,  /*!< PLL0 DIVM CLK */
    CSC0_CLKOUT_BUS_CLK       = 9U,  /*!< BUS CLK */
    CSC0_CLKOUT_SIRC_128K_CLK = 10U, /*!< SIRC 128K CLK */
    CSC0_CLKOUT_AON_CLK       = 12U, /*!< AON CLK */
    CSC0_CLKOUT_RTC_CLK       = 14U  /*!< RTC CLK */
} CSC0_ClockOutSrcType;

/**
 * @brief Data type for CSC0_AONCLKSR[32KAONCLKSEL], set AON32KCLK source clock
 *
 */
typedef enum
{
    CSC0_AON32K_SIRCDIV_32K_CLK = 1U,  /*!< CSC0_AONCLKSR[32KAONCLKSEL], SIRCDIV_32K */
    CSC0_AON32K_SOSC32K_CLK     = 2U,  /*!< CSC0_AONCLKSR[32KAONCLKSEL], SOSC32K */
    CSC0_AON32K_SIRC32K_CLK     = 3U   /*!< CSC0_AONCLKSR[32KAONCLKSEL], SIRC32K */
} CSC0_AON32KClkSrcType;

/**
 * @brief Data type for CSC0_RTCCLKSEL[RTCCLKSEL], set RTCCLK source clock
 *
 */
typedef enum
{
    CSC0_RTC_FOSCDIVL_CLK    = 0U,  /*!< CSC0_RTCCLKSEL[RTCCLKSEL], FOSC_DIVL */
    CSC0_RTC_SIRCDIV_32K_CLK = 1U,  /*!< CSC0_RTCCLKSEL[RTCCLKSEL], SIRC_DIV */
    CSC0_RTC_SOSC_CLK        = 2U,  /*!< CSC0_RTCCLKSEL[RTCCLKSEL], SOSC */
    CSC0_RTC_SIRC32K_CLK     = 3U   /*!< CSC0_RTCCLKSEL[RTCCLKSEL], SIRC_32K */
} CSC0_RTCClkSrcType;

/**
 * @brief Data type for CSC0_AONCLKSEL[AONCLKSEL], set AONCLK source clock
 *
 */
typedef enum
{
    CSC0_AON_SIRCDIV_128K_CLK = 0U,  /*!< CSC0_AONCLKSEL[AONCLKSEL], SIRCDIV_128K */
    CSC0_AON_SIRC32K_CLK      = 1U,  /*!< CSC0_AONCLKSEL[AONCLKSEL], SIRC32K */
    CSC0_AON_SIRCDIV_32K_CLK  = 2U,  /*!< CSC0_AONCLKSEL[AONCLKSEL], SIRCDIV_32K */
    CSC0_AON_SIRC32_1K_CLK    = 3U   /*!< CSC0_AONCLKSEL[AONCLKSEL], SIRC32_1K */
} CSC0_AONClkSrcType;


/**
 * @brief Register 0 related peripheral(CSC0,CSC1,CSC2)
 */
typedef enum
{
    CSC_STOPMODE_FLEXCAN1 = (int)CSC0_STOP_MODER0_FLEXCAN1_MASK,  /*!< Stop acknowledge function FLEXCAN1 */
    CSC_STOPMODE_FLEXCAN0 = (int)CSC0_STOP_MODER0_FLEXCAN0_MASK,  /*!< Stop acknowledge function FLEXCAN0 */
    CSC_STOPMODE_FREQM    = (int)CSC0_STOP_MODER0_FREQM_MASK,     /*!< Stop acknowledge function FREQM */
    CSC_STOPMODE_FCUART3  = (int)CSC0_STOP_MODER0_FCUART3_MASK,   /*!< Stop acknowledge function FCUART3 */
    CSC_STOPMODE_FCUART2  = (int)CSC0_STOP_MODER0_FCUART2_MASK,   /*!< Stop acknowledge function FCUART2 */
    CSC_STOPMODE_FCUART1  = (int)CSC0_STOP_MODER0_FCUART1_MASK,   /*!< Stop acknowledge function FCUART1 */
    CSC_STOPMODE_FCSPI2   = (int)CSC0_STOP_MODER0_FCSPI2_MASK,    /*!< Stop acknowledge function FCSPI2 */
    CSC_STOPMODE_FCSPI1   = (int)CSC0_STOP_MODER0_FCSPI1_MASK,    /*!< Stop acknowledge function FCSPI1 */
    CSC_STOPMODE_SENT0    = (int)CSC0_STOP_MODER0_SENT0_MASK,     /*!< Stop acknowledge function SENT0 */
    CSC_STOPMODE_TMU      = (int)CSC0_STOP_MODER0_TMU_MASK,       /*!< Stop acknowledge function TMU */
    CSC_STOPMODE_ADC1     = (int)CSC0_STOP_MODER0_ADC1_MASK,      /*!< Stop acknowledge function ADC1 */
    CSC_STOPMODE_ADC0     = (int)CSC0_STOP_MODER0_ADC0_MASK,      /*!< Stop acknowledge function ADC0 */
    CSC_STOPMODE_CMU4     = (int)CSC0_STOP_MODER0_CMU4_MASK,      /*!< Stop acknowledge function CMU4 */
    CSC_STOPMODE_WDOG0    = (int)CSC0_STOP_MODER0_WDOG0_MASK,     /*!< Stop acknowledge function WDG0 */
    CSC_STOPMODE_ISM0     = (int)CSC0_STOP_MODER0_ISM0_MASK,      /*!< Stop acknowledge function ISM0 */
    CSC_STOPMODE_DMA0     = (int)CSC0_STOP_MODER0_DMA0_MASK       /*!< Stop acknowledge function DMA0 */
} CSCx_Reg0_PeriphType;

/**
 * @brief Register 1 related peripheral(CSC0,CSC1,CSC2)
 */
typedef enum
{
    CSC_STOPMODE_FLEXCAN3 = (int)CSC0_STOP_MODER1_FLEXCAN3_MASK,  /*!< Stop acknowledge function FLEXCAN3 */
    CSC_STOPMODE_FLEXCAN2 = (int)CSC0_STOP_MODER1_FLEXCAN2_MASK,  /*!< Stop acknowledge function FLEXCAN2 */
    CSC_STOPMODE_MSC0     = (int)CSC0_STOP_MODER1_MSC0_MASK,      /*!< Stop acknowledge function MSC0 */
    CSC_STOPMODE_FCUART7  = (int)CSC0_STOP_MODER1_FCUART7_MASK,   /*!< Stop acknowledge function FCUART7 */
    CSC_STOPMODE_FCUART6  = (int)CSC0_STOP_MODER1_FCUART6_MASK,   /*!< Stop acknowledge function FCUART6 */
    CSC_STOPMODE_FCUART5  = (int)CSC0_STOP_MODER1_FCUART5_MASK,   /*!< Stop acknowledge function FCUART5 */
    CSC_STOPMODE_FCUART4  = (int)CSC0_STOP_MODER1_FCUART4_MASK,   /*!< Stop acknowledge function FCUART4 */
    CSC_STOPMODE_FCIIC1   = (int)CSC0_STOP_MODER1_FCIIC1_MASK,    /*!< Stop acknowledge function FCIIC1 */
    CSC_STOPMODE_FCSPI5   = (int)CSC0_STOP_MODER1_FCSPI5_MASK,    /*!< Stop acknowledge function FCSPI5 */
    CSC_STOPMODE_FCSPI4   = (int)CSC0_STOP_MODER1_FCSPI4_MASK,    /*!< Stop acknowledge function FCSPI4 */
    CSC_STOPMODE_FCSPI3   = (int)CSC0_STOP_MODER1_FCSPI3_MASK,    /*!< Stop acknowledge function FCSPI3 */
    CSC_STOPMODE_WDOG1    = (int)CSC0_STOP_MODER1_WDOG1_MASK,     /*!< Stop acknowledge function WDOG1 */
} CSCx_Reg1_PeriphType;

/**
 * @brief Regsister 2 related peripheral(CSC0,CSC1,CSC2)
 */
typedef enum
{
    CSC_STOPMODE_FCUART0 = (int)CSC0_STOP_MODER2_FCUART0_MASK,  /*!< Stop acknowledge function FCUART0 */
    CSC_STOPMODE_FCIIC0  = (int)CSC0_STOP_MODER2_FCIIC0_MASK,   /*!< Stop acknowledge function FCIIC0 */
    CSC_STOPMODE_FCSPI0  = (int)CSC0_STOP_MODER2_FCSPI0_MASK,   /*!< Stop acknowledge function FCSPI0 */
    CSC_STOPMODE_CMP1    = (int)CSC0_STOP_MODER2_CMP1_MASK,     /*!< Stop acknowledge function CMP1 */
    CSC_STOPMODE_CMP0    = (int)CSC0_STOP_MODER2_CMP0_MASK,     /*!< Stop acknowledge function CMP0 */
    CSC_STOPMODE_CMU3    = (int)CSC0_STOP_MODER2_CMU3_MASK,     /*!< Stop acknowledge function CMU3 */
    CSC_STOPMODE_CMU2    = (int)CSC0_STOP_MODER2_CMU2_MASK,     /*!< Stop acknowledge function CMU2 */
    CSC_STOPMODE_CMU1    = (int)CSC0_STOP_MODER2_CMU1_MASK,     /*!< Stop acknowledge function CMU1 */
    CSC_STOPMODE_CMU0    = (int)CSC0_STOP_MODER2_CMU0_MASK      /*!< Stop acknowledge function CMU0 */
} CSCx_Reg2_PeriphType;

/**
 * @brief CCM stop clock type(CSC0,CSC1,CSC2)
 */
typedef enum
{
    CSC_CCM_STOPCLOCK_STATUS_SYS_SLAVE  = (int)CSC0_CCM0_STATUS_CPU0_STOP_SYS_SLAVE_MASK,  /*!< System Slave Clock  */
    CSC_CCM_STOPCLOCK_STATUS_MASTER     = (int)CSC0_CCM0_STATUS_CPU0_STOP_MASTER_MASK,     /*!< Master Clock  */
    CSC_CCM_STOPCLOCK_STATUS_SLOW_SLAVE = (int)CSC0_CCM0_STATUS_CPU0_STOP_SLOW_SLAVE_MASK, /*!< Slave Clock  */
    CSC_CCM_STOPCLOCK_STATUS_BUS_SLAVE  = (int)CSC0_CCM0_STATUS_CPU0_STOP_BUS_SLAVE_MASK   /*!< Bus Slave Clock  */
} CSCx_CCM_StopClockType;

/**
 * @brief CSC0 SMU control group 0
 */
typedef enum
{
    CSC_SMU_CMU4             = (int)CSC0_SMU_CTRL0_CMU4_MASK,              /*!< CMU4 to FCSMU  */
    CSC_SMU_PMC_MON          = (int)CSC0_SMU_CTRL0_PMC_MON_MASK,           /*!< PMC Monitor to FCSMU */
    CSC_SMU_CMU2             = (int)CSC0_SMU_CTRL0_CMU2_MASK,              /*!< CMU2 to FCSMU  */
    CSC_SMU_CMU1             = (int)CSC0_SMU_CTRL0_CMU1_MASK,              /*!< CMU1 to FCSMU  */
    CSC_SMU_PMC_LVD_HVD      = (int)CSC0_SMU_CTRL0_PMC_LVD_HVD_MASK,       /*!< PMC HVD/LVD to FCSMU  */
    CSC_SMU_SRAM1_MON        = (int)CSC0_SMU_CTRL0_SRAM1_MON_MASK,         /*!< SRAM1 Decoder Monitor to FCSMU  */
    CSC_SMU_SRAM0_MON        = (int)CSC0_SMU_CTRL0_SRAM0_MON_MASK,         /*!< SRAM0 Decoder Monitor to FCSMU  */
    CSC_SMU_MCM              = (int)CSC0_SMU_CTRL0_CPM_MON_MASK,           /*!< CPU Private Module Monitor to FCSMU  */
    CSC_SMU_MAM0_S5_DS_ECC   = (int)CSC0_SMU_CTRL0_MAM0_S5_DS_ECC_MASK,    /*!< MAM0 S5 Downsize ECC to FCSMU  */
    CSC_SMU_MAM0_S8_DS       = (int)CSC0_SMU_CTRL0_MAM0_S8_DS_MASK,        /*!< MAM0 S8 Downsize Monitor to FCSMU  */
    CSC_SMU_MAM0_S5_DS       = (int)CSC0_SMU_CTRL0_MAM0_S5_DS_MASK,        /*!< MAM0 S5 Downsize Monitor to FCSMU  */
    CSC_SMU_DMA0             = (int)CSC0_SMU_CTRL0_DMA0_MASK,              /*!< DMA0 ECC to FCSMU  */
    CSC_SMU_HSM              = (int)CSC0_SMU_CTRL0_HSM_MASK,               /*!< HSM ECC to FCSMU  */
    CSC_SMU_MAM0_S2F_MON     = (int)CSC0_SMU_CTRL0_MAM0_S2F_MON_MASK,      /*!< MAM0 S5 Slow to Fast AHBS Monitor to FCSMU  */
    CSC_SMU_CPU0_AHBS        = (int)CSC0_SMU_CTRL0_CPU0_AHBS_MASK,         /*!< CPU0_AHBS ECC to FCSMU  */
    CSC_SMU_MAM0_S8          = (int)CSC0_SMU_CTRL0_MAM0_S8_MASK,           /*!< MAM0 S8 ECC to FCSMU  */
    CSC_SMU_MAM0_S7          = (int)CSC0_SMU_CTRL0_MAM0_S7_MASK,           /*!< MAM0 S7 ECC to FCSMU  */
    CSC_SMU_MAM0_S6          = (int)CSC0_SMU_CTRL0_MAM0_S6_MASK,           /*!< MAM0 S6 ECC to FCSMU  */
    CSC_SMU_MAM0_S5          = (int)CSC0_SMU_CTRL0_MAM0_S5_MASK,           /*!< MAM0 S5 ECC to FCSMU  */
    CSC_SMU_MAM0_S4          = (int)CSC0_SMU_CTRL0_MAM0_S4_MASK,           /*!< MAM0 S4 ECC to FCSMU  */
    CSC_SMU_MAM0_S3          = (int)CSC0_SMU_CTRL0_MAM0_S3_MASK,           /*!< MAM0 S3 ECC to FCSMU  */
    CSC_SMU_MAM0_S2          = (int)CSC0_SMU_CTRL0_MAM0_S2_MASK,           /*!< MAM0 S2 ECC to FCSMU  */
    CSC_SMU_MAM0_S1          = (int)CSC0_SMU_CTRL0_MAM0_S1_MASK,           /*!< MAM0 S1 ECC to FCSMU  */
    CSC_SMU_MAM0_S0          = (int)CSC0_SMU_CTRL0_MAM0_S0_MASK            /*!< MAM0 S0 ECC to FCSMU  */
} CSC_SMU_CtrlGrp0Type;

/**
 * @brief CSC0 SMU control group of CPUx(group1~3)
 */
typedef enum
{
    CSC_SMU_DTCM1_S_EN    = (int)CSC0_SMU_CTRL1_CPU0_DTCM1_S_EN_MASK, /*!< CPU0 DTCM1 Single Bit Data to FCSMU  */
    CSC_SMU_DTCM0_S_EN    = (int)CSC0_SMU_CTRL1_CPU0_DTCM0_S_EN_MASK, /*!< CPU0 DTCM0 Single Bit Data to FCSMU  */
    CSC_SMU_ITCM_S_EN     = (int)CSC0_SMU_CTRL1_CPU0_ITCM_S_EN_MASK,  /*!< CPU0 ITCM Single Bit Data to FCSMU  */
    CSC_SMU_OVERLAY       = (int)CSC0_SMU_CTRL1_CPU0_OVERLAY_MASK,    /*!< CPU0 Overlay to FCSMU  */
    CSC_SMU_DTCM1_MON     = (int)CSC0_SMU_CTRL1_CPU0_DTCM1_MON_MASK,  /*!< CPU0_DTCM1_MON to FCSMU  */
    CSC_SMU_DTCM0_MON     = (int)CSC0_SMU_CTRL1_CPU0_DTCM0_MON_MASK,  /*!< CPU0_DTCM0_MON to FCSMU  */
    CSC_SMU_ITCM_MON      = (int)CSC0_SMU_CTRL1_CPU0_ITCM_MON_MASK,   /*!< CPU0 ITCM Decoder Monitor to FCSMU  */
    CSC_SMU_AHBM1_F2S     = (int)CSC0_SMU_CTRL1_CPU0_AHBM1_F2S_MASK,  /*!< CPU0 AHBM1 Fast to Slow Monitor to FCSMU  */
    CSC_SMU_AHBM0_F2S     = (int)CSC0_SMU_CTRL1_CPU0_AHBM0_F2S_MASK,  /*!< CPU0 AHBM0 Fast to Slow Monitor to FCSMU  */
    CSC_SMU_AHBP_F2S      = (int)CSC0_SMU_CTRL1_CPU0_AHBP_F2S_MASK,   /*!< CPU0 AHBP Fast to Slow Monito to FCSMU  */
    CSC_SMU_DTCM1         = (int)CSC0_SMU_CTRL1_CPU0_DTCM1_MASK,      /*!< CPU0 DTCM1 ECC to FCSMU  */
    CSC_SMU_DTCM0         = (int)CSC0_SMU_CTRL1_CPU0_DTCM0_MASK,      /*!< CPU0 DTCM0 ECC to FCSMU  */
    CSC_SMU_ITCM          = (int)CSC0_SMU_CTRL1_CPU0_ITCM_MASK,       /*!< CPU0 ITCM ECC to FCSMU  */
    CSC_SMU_DCACHE        = (int)CSC0_SMU_CTRL1_CPU0_DCACHE_MASK,     /*!< CPU0 Data CACHE to FCSMU  */
    CSC_SMU_ICACHE        = (int)CSC0_SMU_CTRL1_CPU0_ICACHE_MASK,     /*!< CPU0 Code CACHE to FCSMU  */
    CSC_SMU_AHBP          = (int)CSC0_SMU_CTRL1_CPU0_AHBP_MASK,       /*!< CPU0 AHBP ECC to FCSMU  */
    CSC_SMU_AHBM          = (int)CSC0_SMU_CTRL1_CPU0_AHBM_MASK        /*!< CPU0 AHBM ECC to FCSMU  */
} CSC_SMU_Cpux_CtrlGrpType;

/**
 * @brief CSC0 SMU control group 4
 */
typedef enum
{
    CSC_SMU_HSM_WDOG            = (int)CSC0_SMU_CTRL4_HSM_WDOG_MASK,           /*!< HSM WDOG Request Enable to FCSMU */
    CSC_SMU_FMC_ERR             = (int)CSC0_SMU_CTRL4_FMC_ERR_MASK,            /*!< FMC ECC Error Enable to FCSMU */
    CSC_SMU_ROM_S_EN            = (int)CSC0_SMU_CTRL4_ROM_S_EN_MASK,           /*!< ROM Single Bit Data Error Enable to FCSMU */
    CSC_SMU_SRAM1_EDC_MON_EN    = (int)CSC0_SMU_CTRL4_SRAM1_EDC_MON_EN_MASK,   /*!< SRAM1_EDC Monitor Error Enable to FCSMU */
    CSC_SMU_SRAM0_EDC_MON_EN    = (int)CSC0_SMU_CTRL4_SRAM0_EDC_MON_EN_MASK,   /*!< SRAM0_EDC Monitor Error Enable to FCSMU */
    CSC_SMU_SRAM1_S_EN          = (int)CSC0_SMU_CTRL4_SRAM1_S_EN_MASK,         /*!< SRAM1 Single Bit Data Error Enable to FCSMU */
    CSC_SMU_SRAM0_S_EN          = (int)CSC0_SMU_CTRL4_SRAM0_S_EN_MASK,         /*!< SRAM0 Single Bit Data Error Enable to FCSMU */
    CSC_SMU_FLASH_ECC_EN_S      = (int)CSC0_SMU_CTRL4_FLASH_ECC_EN_S_MASK,     /*!< FLASH Single Bit Error Enable to FCSMU */
    CSC_SMU_FLASH_ECC_EN        = (int)CSC0_SMU_CTRL4_FLASH_ECC_EN_MASK,       /*!< FLASH ECC Error Enable to FCSMU */
    CSC_SMU_AFCB1_MON           = (int)CSC0_SMU_CTRL4_AFCB1_MON_MASK,          /*!< AFCB1 Monitor Error Enable to FCSMU */
    CSC_SMU_AFCB0_MON           = (int)CSC0_SMU_CTRL4_AFCB0_MON_MASK,          /*!< AFCB0 Monitor Error Enable to FCSMU */
    CSC_SMU_SCF_RST             = (int)CSC0_SMU_CTRL4_SCF_RST_EN_MASK,         /*!< Self Check Feature Enable */
    CSC_SMU_SCF_IRQ             = (int)CSC0_SMU_CTRL4_SCF_IRQ_EN_MASK,         /*!< Self Check Feature Interrupt Request Enable */
    CSC_SMU_TMU                 = (int)CSC0_SMU_CTRL4_TMU_MASK,                /*!< TMU Error Enable to FCSMU */
    CSC_SMU_SCM_CRC             = (int)CSC0_SMU_CTRL4_SCM_CRC_MASK,            /*!< SCM CRC Error Enable to FCSMU */
    CSC_SMU_SCG_CRC             = (int)CSC0_SMU_CTRL4_SCG_CRC_MASK,            /*!< SCG CRC Error Enable to FCSMU */
    CSC_SMU_SRAM1_ECC           = (int)CSC0_SMU_CTRL4_SRAM1_ECC_MASK,          /*!< SRAM1 ECC Error Enable to FCSMU */
    CSC_SMU_SRAM0_ECC           = (int)CSC0_SMU_CTRL4_SRAM0_ECC_MASK,          /*!< SRAM0 ECC Error Enable to FCSMU */
    CSC_SMU_MAM0_ERR            = (int)CSC0_SMU_CTRL4_MAM0_ERR_MASK            /*!< Matrix Access Monitor 0 Timeout Error Enable to FCSMU */
} CSC_SMU_CtrlGrp4Type;

/**
 * @brief CSC0 SMU control group 5
 */
typedef enum
{
    CSC_SMU_SRAM1_EDC           = (int)CSC0_SMU_CTRL5_SRAM1_EDC_MASK,      /*!< SRAM1 EDC Error Enable to FCSMU */
    CSC_SMU_SRAM0_EDC           = (int)CSC0_SMU_CTRL5_SRAM0_EDC_MASK,      /*!< SRAM0 EDC Error Enable to FCSMU */
    CSC_SMU_FLASH_EDC_P1_EN     = (int)CSC0_SMU_CTRL5_FLASH_EDC_P1_EN_MASK,/*!< FLASH P1 EDC Error Enable to FCSMU */
    CSC_SMU_FLASH_EDC_P0_EN     = (int)CSC0_SMU_CTRL5_FLASH_EDC_P0_EN_MASK,/*!< FLASH P0 EDC Error Enable to FCSMU */
    CSC_SMU_HSM_IRAM_S          = (int)CSC0_SMU_CTRL5_HSM_IRAM_S_MASK,     /*!< HSM IRAM Single Bit Data Error Enable to FCSMU */
    CSC_SMU_HSM_DRAM_S          = (int)CSC0_SMU_CTRL5_HSM_DRAM_S_MASK,     /*!< HSM DRAM Single Bit Data Error Enable to FCSMU */
    CSC_SMU_HSM_IRAM            = (int)CSC0_SMU_CTRL5_HSM_IRAM_MASK,       /*!< HSM IRAM ECC Error Enable to FCSMU */
    CSC_SMU_HSM_DRAM            = (int)CSC0_SMU_CTRL5_HSM_DRAM_MASK,       /*!< HSM DRAM ECC Error Enable to FCSMU */
    CSC_SMU_DMA0_ECC_S          = (int)CSC0_SMU_CTRL5_DMA0_ECC_S_MASK,     /*!< DMA0_CFG_ECC Single Bit Data Error Enable to FCSMU */
    CSC_SMU_DMA0_ECC            = (int)CSC0_SMU_CTRL5_DMA0_ECC_MASK,       /*!< DMA0 CFG ECC Error Enable to FCSMU */
    CSC_SMU_DMA0_LOCKSTEP       = (int)CSC0_SMU_CTRL5_DMA0_LOCKSTEP_MASK,  /*!< DMA0 lockstep Error Enable to FCSMU */
    CSC_SMU_FOSC_ERR            = (int)CSC0_SMU_CTRL5_FOSC_ERR_MASK,       /*!< FOSC Loss of Clock Error Enable to FCSMU */
    CSC_SMU_PLL1_ERR            = (int)CSC0_SMU_CTRL5_PLL1_ERR_MASK,       /*!< PLL1 Loss of Clock Error Enable to FCSMU */
    CSC_SMU_PLL0_ERR            = (int)CSC0_SMU_CTRL5_PLL0_ERR_MASK,       /*!< PLL0 Loss of Clock Error Enable to FCSMU */
    CSC_SMU_STCU_ERR            = (int)CSC0_SMU_CTRL5_STCU_ERR_MASK,       /*!< STCU Self Test Error Enable to FCSMU */
    CSC_SMU_NONUSER_ERR         = (int)CSC0_SMU_CTRL5_NONUSER_ERR_MASK,    /*!< STCU Non User Error Enable to FCSMU */
    CSC_SMU_NVR_ERR             = (int)CSC0_SMU_CTRL5_NVR_ERR_MASK,        /*!< NVR Error Enable to FCSMU */
} CSC_SMU_CtrlGrp5Type;

/**
 * @brief CSC0 CMU control group
 */
typedef enum
{
    CSC_CMU_DMA0_CFG_S_EN_ADDR  = (int)CSC0_CMU_CTRL_DMA0_CFG_S_EN_ADDR_MASK,/*!< Enable to Report Single Error When One Bit Address_ECC Error Inject */
    CSC_CMU_CMU3_FCSMU_RST      = (int)CSC0_CMU_CTRL_CMU3_FCSMU_RST_MASK,    /*!< CMU3 clcok error to assert reset request to RGM to reset System and FCSMU */
    CSC_CMU_CMU3_RST            = (int)CSC0_CMU_CTRL_CMU3_RST_EN_MASK,       /*!< CMU3 clock error to assert reset request to RGM to reset System */
    CSC_CMU_CMU4_LOC            = (int)CSC0_CMU_CTRL_CMU4_LOC_EN_MASK        /*!< Enable CMU4 Loss of clock error request to SCG */
} CSC0_CMU_CtrlGrpType;

/**
 * @brief CSC0 Low Power Wakeup configuration group type
 */
typedef enum
{
    CSC_LP_WAKEUP_GROUP_0 = 0U,     /*!< CSC0 Low Power Wakeup configuration group0 */
    CSC_LP_WAKEUP_GROUP_1 = 1U,     /*!< CSC0 Low Power Wakeup configuration group1 */
    CSC_LP_WAKEUP_GROUP_2 = 2U,     /*!< CSC0 Low Power Wakeup configuration group2 */
    CSC_LP_WAKEUP_GROUP_3 = 3U,     /*!< CSC0 Low Power Wakeup configuration group3 */
    CSC_LP_WAKEUP_GROUP_4 = 4U      /*!< CSC0 Low Power Wakeup configuration group4 */
} CSC0_LPWakeupGrpType;

/**
 * @brief CSC0 Low Power Wakeup configuration source type
 */
typedef enum
{
    CSC_LP_WAKEUP_DISABLE             = 0U,    /*!< Disable */
    CSC_LP_WAKEUP_AONTIMER_TRIGGER    = 1U,    /*!< AONTIMER Trigger */
    CSC_LP_WAKEUP_RTC_TIME_ALARM      = 2U,    /*!< RTC Time Alarm */
    CSC_LP_WAKEUP_CPM0_OUTPUT         = 3U,    /*!< CPM0 output */
    CSC_LP_WAKEUP_CPM1_OUTPUT         = 4U,    /*!< CPM1 output */
    CSC_LP_WAKEUP_RESERVED            = 5U,    /*!< Reserved */
    CSC_LP_WAKEUP_PMC_RPM_ENTRY       = 6U,    /*!< PMC RPM Entry */
    CSC_LP_WAKEUP_WKU_INTERRUPT       = 7U,    /*!< WKU Interrupt */
    CSC_LP_WAKEUP_TSTMP0_PWM_TRIGGER0 = 8U,    /*!< TSTMP0 PWM TRIGGER0 */
    CSC_LP_WAKEUP_TSTMP0_PWM_TRIGGER1 = 9U,    /*!< TSTMP0 PWM TRIGGER1 */
    CSC_LP_WAKEUP_FCPIT0_PWM_TRIGGER0 = 10U,   /*!< FCPT0 PWM TRIGGER0 */
    CSC_LP_WAKEUP_FCPIT0_PWM_TRIGGER1 = 11U,   /*!< FCPT0 PWM TRIGGER1 */
    CSC_LP_WAKEUP_FCPIT0_TRIGGER_OUT0 = 12U,   /*!< FCPIT0 Trigger out[0] */
    CSC_LP_WAKEUP_FCPIT0_TRIGGER_OUT1 = 13U,   /*!< FCPIT0 Trigger out[1] */
    CSC_LP_WAKEUP_FCPIT0_TRIGGER_OUT2 = 14U,   /*!< FCPIT0 Trigger out[2] */
    CSC_LP_WAKEUP_FCPIT0_TRIGGER_OUT3 = 15U    /*!< FCPIT0 Trigger out[3] */
} CSC0_LPWakeupSrcType;

/**
 * @brief CSC0 Low Power Wakeup polarity type
 */
typedef enum
{
    CSC_LP_WAKEUP_POL_KEEP   = 0U,    /*!< Keep the LP_WAKEUP CFGx */
    CSC_LP_WAKEUP_POL_INVERT = 1U,    /*!< Invert the LP_WAKEUP CFGx */
} CSC0_LPWakeupPolType;


/********* Local inline function ************/
/****** Operation on CSC0_xxxRegister0 ******/
/**
 * @brief Lock the cpu to control stop mode register 0
 *
 */
LOCAL_INLINE void CSC0_HWA_MODER0_LockWritePermit(void)
{
    CSC0->STOP_MODER0 |= (uint32_t)CSC0_STOP_MODER0_WPB_LOCK_MASK;
}

/**
 * @brief Get the stop mode register 0 lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_MODER0_GetWPBLockStatus(void)
{
    return (CSC0->STOP_MODER0 & (uint32_t)CSC0_STOP_MODER0_WPB_LOCK_MASK);
}

/**
 * @brief Get the CPU type of writing permission
 *
 * @return CSC_WPB_CpuType The CPU which has the write permission
 */
LOCAL_INLINE CSC_WPB_CpuType CSC0_HWA_MODER0_GetCpuWritePermit(void)
{
    uint32_t u32RegVal = ((CSC0->STOP_MODER0 & (uint32_t)CSC0_STOP_MODER0_WPB_MASK)>>CSC0_STOP_MODER0_WPB_SHIFT);
    return (CSC_WPB_CpuType)u32RegVal;
}

/**
 * @brief Set cpu to control this stop mode register 0
 *
 * @param eCpuType Cpu allowed to control peripheral
 */
LOCAL_INLINE void CSC0_HWA_MODER0_SetCpuWritePermit(CSC_WPB_CpuType eCpuType)
{
    uint32_t u32RegVal = CSC0->STOP_MODER0;
    CSC0->STOP_MODER0 = ((u32RegVal & (~(uint32_t)CSC0_STOP_MODER0_WPB_MASK)) | CSC0_STOP_MODER0_WPB(eCpuType));
}

/**
 * @brief Enable the stop acknowledge function of register 0 group
 *
 * @param ePeriphType Peripheral to be set
 */
LOCAL_INLINE void CSC0_HWA_MODER0_EnableStopAck(CSCx_Reg0_PeriphType ePeriphType)
{
    CSC0->STOP_MODER0 |= (uint32_t)ePeriphType;
}

/**
 * @brief Disable the stop acknowledge function of register 0 group
 *
 * @param ePeriphType Peripheral to be set
 */
LOCAL_INLINE void CSC0_HWA_MODER0_DisableStopAck(CSCx_Reg0_PeriphType ePeriphType)
{
    CSC0->STOP_MODER0 &= ~(uint32_t)ePeriphType;
}

/**
 * @brief Set multiple stop ack enable/disable value
 *
 * @param u32Value the OR value of type CSCx_Reg0_PeriphType
 */
LOCAL_INLINE void CSC0_HWA_MODER0_SetMultiStopAck(uint32_t u32Value)
{
    CSC0->STOP_MODER0 = u32Value;
}

/**
 * @brief Clear  multiple stop ack enable/disable value
 *
 * @param u32Value the OR value of type CSCx_Reg0_PeriphType
 */
LOCAL_INLINE void CSC0_HWA_MODER0_ClearMultiStopAck(uint32_t u32Value)
{
    CSC0->STOP_MODER0  = (CSC0->STOP_MODER0 & (~u32Value));
}

/**
 * @brief Lock the cpu to control this stop request register 0
 *
 * @param eLockType Cpu lock type
 */
LOCAL_INLINE void CSC0_HWA_REQR0_LockWritePermit(void)
{
    CSC0->STOP_REQR0 |= (uint32_t)CSC0_STOP_REQR0_WPB_LOCK_MASK;
}

/**
 * @brief Get the stop request register 0 lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_REQR0_GetWPBLockStatus(void)
{
    return (CSC0->STOP_REQR0 & (uint32_t)CSC0_STOP_REQR0_WPB_LOCK_MASK);
}

/**
 * @brief Get the CPU type of writing permission
 *
 * @return CSC_WPB_CpuType The CPU which has the write permission
 */
LOCAL_INLINE CSC_WPB_CpuType CSC0_HWA_REQR0_GetCpuWritePermit(void)
{
    uint32_t u32RegVal = ((CSC0->STOP_REQR0 & (uint32_t)CSC0_STOP_REQR0_WPB_MASK)>>CSC0_STOP_REQR0_WPB_SHIFT);
    return (CSC_WPB_CpuType)u32RegVal;
}

/**
 * @brief Set cpu to control stop request register 0
 *
 * @param eCpuType Cpu allowed to control peripheral
 */
LOCAL_INLINE void CSC0_HWA_REQR0_SetCpuWritePermit(CSC_WPB_CpuType eCpuType)
{
    uint32_t u32RegVal = CSC0->STOP_REQR0;
    CSC0->STOP_REQR0 = ((u32RegVal & (~(uint32_t)CSC0_STOP_REQR0_WPB_MASK)) | CSC0_STOP_REQR0_WPB(eCpuType));
}

/**
 * @brief Set stop request in register 0
 *
 * @param ePeriphType Peripheral to be set
 */
LOCAL_INLINE void CSC0_HWA_REQR0_SetStopRequest(CSCx_Reg0_PeriphType ePeriphType)
{
    CSC0->STOP_REQR0 |= (uint32_t)ePeriphType;
}

/**
 * @brief Clear stop request in register 0
 *
 * @param ePeriphType Peripheral to be cleared
 */
LOCAL_INLINE void CSC0_HWA_REQR0_ClearStopRequest(CSCx_Reg0_PeriphType ePeriphType)
{
    CSC0->STOP_REQR0 &= ~(uint32_t)ePeriphType;
}

/**
 * @brief Set multiple stop request enable/disable value
 *
 * @param u32Value the OR value of type CSCx_Reg0_PeriphType
 */
LOCAL_INLINE void CSC0_HWA_REQR0_SetMultiStopRequest(uint32_t u32Value)
{
    CSC0->STOP_REQR0 = u32Value;
}

/**
 * @brief Clear stop request in register 0
 *
 * @param u32Value the OR value of type CSCx_Reg0_PeriphType
 */
LOCAL_INLINE void CSC0_HWA_REQR0_ClearMultiStopRequest(uint32_t u32Value)
{
    CSC0->STOP_REQR0  = (CSC0->STOP_REQR0 & (~u32Value));
}

/**
 * @brief Get stop ack status in register 0
 *
 * @param u32Value value to be set
 * @return Stop ack status
 */
LOCAL_INLINE uint32_t CSC0_HWA_ACKR0_GetStopAckStatus(CSCx_Reg0_PeriphType ePeriphType)
{
    return (CSC0->STOP_ACKR0 & ((uint32_t)ePeriphType));
}

/**
 * @brief Get multiple stop ack status in register 0
 *
 * @param u32Value the OR value of type CSCx_Reg0_PeriphType
 * @return Stop ack status
 */
LOCAL_INLINE uint32_t CSC0_HWA_ACKR0_GetMultiStopAckStatus(uint32_t u32Value)
{
    return (CSC0->STOP_ACKR0 & u32Value);
}



/****** Operation on CSC0_xxxRegister1 ******/
/**
 * @brief Lock the cpu to control stop mode register 1
 *
 */
LOCAL_INLINE void CSC0_HWA_MODER1_LockWritePermit(void)
{
    CSC0->STOP_MODER1 |= (uint32_t)CSC0_STOP_MODER1_WPB_LOCK_MASK;
}

/**
 * @brief Get the stop mode register 1 lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_MODER1_GetWPBLockStatus(void)
{
    return (CSC0->STOP_MODER1 & (uint32_t)CSC0_STOP_MODER1_WPB_LOCK_MASK);
}

/**
 * @brief Set cpu to control this stop mode register 1
 *
 * @param eCpuType Cpu allowed to control peripheral
 */
LOCAL_INLINE void CSC0_HWA_MODER1_SetCpuWritePermit(CSC_WPB_CpuType eCpuType)
{
    uint32_t u32RegVal = CSC0->STOP_MODER1;
    CSC0->STOP_MODER1 = ((u32RegVal & (~(uint32_t)CSC0_STOP_MODER1_WPB_MASK)) | CSC0_STOP_MODER1_WPB(eCpuType));
}

/**
 * @brief Get the CPU type of writing permission
 *
 * @return CSC_WPB_CpuType The Cpu which has the write permission
 */
LOCAL_INLINE CSC_WPB_CpuType CSC0_HWA_MODER1_GetCpuWritePermit(void)
{
    uint32_t u32RegVal = ((CSC0->STOP_MODER1 & (uint32_t)CSC0_STOP_MODER1_WPB_MASK)>>CSC0_STOP_MODER1_WPB_SHIFT);
    return (CSC_WPB_CpuType)u32RegVal;
}

/**
 * @brief Enable the stop acknowledge function of register 1 group
 *
 * @param ePeriphType Peripheral to be set
 */
LOCAL_INLINE void CSC0_HWA_MODER1_EnableStopAck(CSCx_Reg1_PeriphType ePeriphType)
{
    CSC0->STOP_MODER1 |= (uint32_t)ePeriphType;
}

/**
 * @brief Disable the stop acknowledge function of register 1 group
 *
 * @param ePeriphType Peripheral to be set
 */
LOCAL_INLINE void CSC0_HWA_MODER1_DisableStopAck(CSCx_Reg1_PeriphType ePeriphType)
{
    CSC0->STOP_MODER1 &= ~(uint32_t)ePeriphType;
}

/**
 * @brief Set multiple stop ack enable/disable value
 *
 * @param u32Value the OR value of type CSCx_Reg1_PeriphType
 */
LOCAL_INLINE void CSC0_HWA_MODER1_SetMultiStopAck(uint32_t u32Value)
{
    CSC0->STOP_MODER1 = u32Value;
}

/**
 * @brief Clear multiple stop ack enable/disable value
 *
 * @param u32Value the OR value of type CSCx_Reg1_PeriphType
 */
LOCAL_INLINE void CSC0_HWA_MODER1_ClearMultiStopAck(uint32_t u32Value)
{
    CSC0->STOP_MODER1  = (CSC0->STOP_MODER1 & (~u32Value));
}

/**
 * @brief Lock the cpu to control this stop request register 1
 *
 */
LOCAL_INLINE void CSC0_HWA_REQR1_LockWritePermit(void)
{
    CSC0->STOP_REQR1 |= (uint32_t)CSC0_STOP_REQR1_WPB_LOCK_MASK;
}

/**
 * @brief Get the stop request register 1 lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_REQR1_GetWPBLockStatus(void)
{
    return (CSC0->STOP_REQR1 & (uint32_t)CSC0_STOP_REQR1_WPB_LOCK_MASK);
}

/**
 * @brief Get the CPU type of writing permission
 *
 * @return CSC_WPB_CpuType CPU type which has the write permission
 */
LOCAL_INLINE CSC_WPB_CpuType CSC0_HWA_REQR1_GetCpuWritePermit(void)
{
    uint32_t u32RegVal = ((CSC0->STOP_REQR1 & (uint32_t)CSC0_STOP_REQR1_WPB_MASK)>>CSC0_STOP_REQR1_WPB_SHIFT);
    return (CSC_WPB_CpuType)u32RegVal;
}

/**
 * @brief Set cpu to control stop request register 1
 *
 * @param eCpuType Cpu allowed to control peripheral
 */
LOCAL_INLINE void CSC0_HWA_REQR1_SetCpuWritePermit(CSC_WPB_CpuType eCpuType)
{
    uint32_t u32RegVal = CSC0->STOP_REQR1;
    CSC0->STOP_REQR1 |= ((u32RegVal & (~(uint32_t)CSC0_STOP_REQR1_WPB_MASK)) | CSC0_STOP_REQR1_WPB(eCpuType));
}

/**
 * @brief Set stop request in register 1
 *
 * @param ePeriphType Peripheral to be set
 */
LOCAL_INLINE void CSC0_HWA_REQR1_SetStopRequest(CSCx_Reg1_PeriphType ePeriphType)
{
    CSC0->STOP_REQR1 |= (uint32_t)ePeriphType;
}

/**
 * @brief Clear stop request in register 1
 *
 * @param ePeriphType Peripheral to be cleared
 */
LOCAL_INLINE void CSC0_HWA_REQR1_ClearStopRequest(CSCx_Reg1_PeriphType ePeriphType)
{
    CSC0->STOP_REQR1 &= ~(uint32_t)ePeriphType;
}

/**
 * @brief Set multiple stop request enable/disable value
 *
 * @param u32Value the OR value of type CSCx_Reg1_PeriphType
 */
LOCAL_INLINE void CSC0_HWA_REQR1_SetMultiStopRequest(uint32_t u32Value)
{
    CSC0->STOP_REQR1 = u32Value;
}

/**
 * @brief Clear multiple stop request in register 0
 *
 * @param u32Value the OR value of type CSCx_Reg1_PeriphType
 */
LOCAL_INLINE void CSC0_HWA_REQR1_ClearMultiStopRequest(uint32_t u32Value)
{
    CSC0->STOP_REQR1  = (CSC0->STOP_REQR1 & (~u32Value));
}

/**
 * @brief Get stop ack status in register 1
 *
 * @param u32Value value to be set
 * @return Stop ack status
 */
LOCAL_INLINE uint32_t CSC0_HWA_ACKR1_GetStopAckStatus(CSCx_Reg1_PeriphType ePeriphType)
{
    return (CSC0->STOP_ACKR1 & (uint32_t)ePeriphType);
}

/**
 * @brief Get multiple stop ack status in register 1
 *
 * @param u32Value the OR value of type CSCx_Reg1_PeriphType
 * @return Stop ack status
 */
LOCAL_INLINE uint32_t CSC0_HWA_ACKR1_GetMultiStopAckStatus(uint32_t u32Value)
{
    return (CSC0->STOP_ACKR1 & u32Value);
}

/****** Operation on CSC0_xxxRegister2 ******/
/**
 * @brief Lock the cpu to control stop mode register 2
 *
 */
LOCAL_INLINE void CSC0_HWA_MODER2_LockWritePermit(void)
{
    CSC0->STOP_MODER2 |= (uint32_t)CSC0_STOP_MODER2_WPB_LOCK_MASK;
}

/**
 * @brief Get the stop mode register 2 lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_MODER2_GetWPBLockStatus(void)
{
    return (CSC0->STOP_MODER2 & (uint32_t)CSC0_STOP_MODER2_WPB_LOCK_MASK);
}

/**
 * @brief Set cpu to control this stop mode register 2
 *
 * @param eCpuType Cpu allowed to control peripheral
 */
LOCAL_INLINE void CSC0_HWA_MODER2_SetCpuWritePermit(CSC_WPB_CpuType eCpuType)
{
    uint32_t u32RegVal = CSC0->STOP_MODER2;
    CSC0->STOP_MODER2 = ((u32RegVal & (~(uint32_t)CSC0_STOP_MODER2_WPB_MASK)) | CSC0_STOP_MODER2_WPB(eCpuType));
}

/**
 * @brief Get the CPU type of writing permission
 *
 * @return CSC_WPB_CpuType The Cpu which has the write permission
 */
LOCAL_INLINE CSC_WPB_CpuType CSC0_HWA_MODER2_GetCpuWritePermit(void)
{
    uint32_t u32RegVal = ((CSC0->STOP_MODER2 & (uint32_t)CSC0_STOP_MODER2_WPB_MASK)>>CSC0_STOP_MODER2_WPB_SHIFT);
    return (CSC_WPB_CpuType)u32RegVal;
}


/**
 * @brief Enable the stop acknowledge function of register 2 group
 *
 * @param ePeriphType Peripheral to be set
 */
LOCAL_INLINE void CSC0_HWA_MODER2_EnableStopAck(CSCx_Reg2_PeriphType ePeriphType)
{
    CSC0->STOP_MODER2 |= (uint32_t)ePeriphType;
}

/**
 * @brief Disable the stop acknowledge function of register 1 group
 *
 * @param ePeriphType Peripheral to be set
 */
LOCAL_INLINE void CSC0_HWA_MODER2_DisableStopAck(CSCx_Reg2_PeriphType ePeriphType)
{
    CSC0->STOP_MODER2 &= ~(uint32_t)ePeriphType;
}

/**
 * @brief Set multiple stop ack enable/disable value
 *
 * @param u32Value value to be set
 */
LOCAL_INLINE void CSC0_HWA_MODER2_SetMultiStopAck(uint32_t u32Value)
{
    CSC0->STOP_MODER2 = u32Value;
}

/**
 * @brief Clear multiple stop ack enable/disable value
 *
 * @param u32Value value to be set
 */
LOCAL_INLINE void CSC0_HWA_MODER2_ClearMultiStopAck(uint32_t u32Value)
{
    CSC0->STOP_MODER2  = (CSC0->STOP_MODER2 & (~u32Value));
}

/**
 * @brief Lock the cpu to control this stop request register 2
 *
 */
LOCAL_INLINE void CSC0_HWA_REQR2_LockWritePermit(void)
{
    CSC0->STOP_REQR2 |= (uint32_t)CSC0_STOP_REQR2_WPB_LOCK_MASK;
}

/**
 * @brief Get the stop request register 2 lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_REQR2_GetWPBLockStatus(void)
{
    return (CSC0->STOP_REQR2 & (uint32_t)CSC0_STOP_REQR2_WPB_LOCK_MASK);
}

/**
 * @brief Set cpu to control stop request register 2
 *
 * @param eCpuType Cpu allowed to control peripheral
 */
LOCAL_INLINE void CSC0_HWA_REQR2_SetCpuWritePermit(CSC_WPB_CpuType eCpuType)
{
    uint32_t u32RegVal = CSC0->STOP_REQR2;
    CSC0->STOP_REQR2 = ((u32RegVal & (~(uint32_t)CSC0_STOP_REQR2_WPB_MASK)) | CSC0_STOP_REQR2_WPB(eCpuType));
}

/**
 * @brief Get the CPU type of writing permission
 *
 * @return CSC_WPB_CpuType The Cpu which has the write permission
 */
LOCAL_INLINE CSC_WPB_CpuType CSC0_HWA_REQR2_GetCpuWritePermit(void)
{
    uint32_t u32RegVal = ((CSC0->STOP_REQR2 & (uint32_t)CSC0_STOP_REQR2_WPB_MASK)>>CSC0_STOP_REQR2_WPB_SHIFT);
    return (CSC_WPB_CpuType)u32RegVal;
}


/**
 * @brief Set stop request in register 2
 *
 * @param ePeriphType Peripheral to be set
 */
LOCAL_INLINE void CSC0_HWA_REQR2_SetStopRequest(CSCx_Reg2_PeriphType ePeriphType)
{
    CSC0->STOP_REQR2 |= (uint32_t)ePeriphType;
}

/**
 * @brief Clear stop request in register 2
 *
 * @param ePeriphType Peripheral to be cleared
 */
LOCAL_INLINE void CSC0_HWA_REQR2_ClearStopRequest(CSCx_Reg2_PeriphType ePeriphType)
{
    CSC0->STOP_REQR2 &= ~(uint32_t)ePeriphType;
}

/**
 * @brief Set multiple stop request enable/disable value
 *
 * @param u32Value the OR value of type CSCx_Reg2_PeriphType
 */
LOCAL_INLINE void CSC0_HWA_REQR2_SetMultiStopRequest(uint32_t u32Value)
{
    CSC0->STOP_REQR2 = u32Value;
}

/**
 * @brief Clear multiple stop request in register 0
 *
 * @param u32Value the OR value of type CSCx_Reg2_PeriphType
 */
LOCAL_INLINE void CSC0_HWA_REQR2_ClearMultiStopRequest(uint32_t u32Value)
{
    CSC0->STOP_REQR2  = (CSC0->STOP_REQR2 & (~u32Value));
}

/**
 * @brief Get stop ack status in register 2
 *
 * @param u32Value value to be set
 * @return Stop ack status
 */
LOCAL_INLINE uint32_t CSC0_HWA_ACKR2_GetStopAckStatus(CSCx_Reg2_PeriphType ePeriphType)
{
    return (CSC0->STOP_ACKR2 & (uint32_t)ePeriphType);
}

/**
 * @brief Get multiple stop ack status in register 2
 *
 * @param u32Value the OR value of type CSCx_Reg2_PeriphType
 * @return Stop ack status
 */
LOCAL_INLINE uint32_t CSC0_HWA_ACKR2_GetMultiStopAckStatus(uint32_t u32Value)
{
    return (CSC0->STOP_ACKR2 & u32Value);
}

/**
 * @brief Lock the cpu to control CCM0 register
 *
 */
LOCAL_INLINE void CSC0_HWA_CCM0_LockWritePermit(void)
{
    CSC0->CCM0_CFG |= (uint32_t)CSC0_CCM0_CFG_WPB_LOCK_MASK;
}

/**
 * @brief Unlock the cpu to control CCM0 register
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_CCM0_GetWPBLockStatus(void)
{
    return (CSC0->CCM0_CFG & (uint32_t)CSC0_CCM0_CFG_WPB_LOCK_MASK);
}

/**
 * @brief Get the CPU type of writing permission
 *
 * @param CSC_WPB_CpuType The Cpu which has the write permission
 */
LOCAL_INLINE CSC_WPB_CpuType CSC0_HWA_CCM0_GetCpuWritePermit(void)
{
    uint32_t u32RegVal = (CSC0->CCM0_CFG & CSC0_CCM0_CFG_WPB_MASK) >> CSC0_CCM0_CFG_WPB_SHIFT;
    return (CSC_WPB_CpuType)u32RegVal;
}

/**
 * @brief Set cpu to control this CCM0 register
 *
 * @param eCpuType Cpu allowed to control peripheral
 */
LOCAL_INLINE void CSC0_HWA_CCM0_SetCpuWritePermit(CSC_WPB_CpuType eCpuType)
{
    uint32_t u32RegVal = CSC0->CCM0_CFG;
    CSC0->CCM0_CFG = ((u32RegVal & (~(uint32_t)CSC0_CCM0_CFG_WPB_MASK)) | CSC0_CCM0_CFG_WPB(eCpuType));
}

/**
 * @brief Force enable HClock of cpu 0
 *
 */
LOCAL_INLINE bool CSC0_HWA_GetHClockEnFlag(void)
{
    return (bool)((CSC0->CCM0_CFG & CSC0_CCM0_CFG_CPU0_FORCE_HCLKEN_MASK) != 0U);
}

/**
 * @brief Force enable HClock of cpu 0
 *
 */
LOCAL_INLINE void CSC0_HWA_HClockEnable(bool bEnable)
{
    CSC0->CCM0_CFG = (CSC0->CCM0_CFG & (~(uint32_t)CSC0_CCM0_CFG_CPU0_FORCE_HCLKEN_MASK)) |
                     CSC0_CCM0_CFG_CPU0_FORCE_HCLKEN(bEnable);
}

/**
 * @brief Get CCM0 hand shake mode
 *
 * @param eHandShakeType CCM0 hand shake mode
 */
LOCAL_INLINE CSC_HandShakeModeType CSC0_HWA_GetHandShakeMode(void)
{
    uint32_t u32RegVal = (CSC0->CCM0_CFG & CSC0_CCM0_CFG_CCM0_HANDSHAKE_MODE_MASK) >> CSC0_CCM0_CFG_CCM0_HANDSHAKE_MODE_SHIFT;
    return (CSC_HandShakeModeType)u32RegVal;
}

/**
 * @brief Set CCM0 hand shake mode
 *
 * @param eHandShakeType CCM0 hand shake mode
 */
LOCAL_INLINE void CSC0_HWA_SetHandShakeMode(CSC_HandShakeModeType eHandShakeType)
{
    uint32_t u32RegVal = CSC0->CCM0_CFG;
    CSC0->CCM0_CFG = ((u32RegVal & (~(uint32_t)CSC0_CCM0_CFG_CCM0_HANDSHAKE_MODE_MASK)) | CSC0_CCM0_CFG_CCM0_HANDSHAKE_MODE(eHandShakeType));
}

/**
 * @brief Get CCM0 clock status
 *
 * @param eStopClockType CCM0 stop clock type
 * @return CCM0 clock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_CCM0_GetClockStatus(CSCx_CCM_StopClockType eStopClockType)
{
    return (CSC0->CCM0_STATUS & (uint32_t)eStopClockType);
}

/**
 * @brief Enable SCG MAM stall
 *
 */
LOCAL_INLINE void CSC0_HWA_EnalbeSCGStall(void)
{
    CSC0->SCG_MAM_STALL |= (uint32_t)CSC0_SCG_MAM_STALL_SCG_STALL_MASK;
}

/**
 * @brief Disable SCG MAM stall
 *
 */
LOCAL_INLINE void CSC0_HWA_DisableSCGStall(void)
{
    CSC0->SCG_MAM_STALL &= ~(uint32_t)CSC0_SCG_MAM_STALL_SCG_STALL_MASK;
}

/**
 * @brief Lock SCG_MAM_STALL register status
 *
 */
LOCAL_INLINE void CSC0_HWA_LockSCG_MAM_STALL(void)
{
    CSC0->SCG_MAM_STALL |= (uint32_t)CSC0_SCG_MAM_STALL_LOCK_MASK;
}

/**
 * @brief Get SCG_MAM_STALL register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_SCG_MAM_STALL_GetLockStatus(void)
{
    return (CSC0->SCG_MAM_STALL & (uint32_t)CSC0_SCG_MAM_STALL_LOCK_MASK);
}

/**
 * @brief Lock the cpu to control CPU0_INT register
 *
 */
LOCAL_INLINE void CSC0_HWA_CPU0INT_LockWritePermit(void)
{
    CSC0->CPU0_INT |= (uint32_t)CSC0_CPU0_INT_WPB_LOCK_MASK;
}

/**
 * @brief Get CPU0_INT register WPB lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_CPU0INT_GetWPBLockStatus(void)
{
    return (CSC0->CPU0_INT & (uint32_t)CSC0_CPU0_INT_WPB_LOCK_MASK);
}

/**
 * @brief Get the CPU type of writing permission
 *
 * @param CSC_WPB_CpuType The Cpu which has the write permission
 */
LOCAL_INLINE CSC_WPB_CpuType CSC0_HWA_CPU0INT_GetCpuWritePermit(void)
{
    uint32_t u32RegVal = (CSC0->CPU0_INT & CSC0_CPU0_INT_WPB_MASK) >> CSC0_CPU0_INT_WPB_SHIFT;
    return (CSC_WPB_CpuType)u32RegVal;
}

/**
 * @brief Set cpu to control this CPU0_INT register
 *
 * @param eCpuType Cpu allowed to control peripheral
 */
LOCAL_INLINE void CSC0_HWA_CPU0INT_SetCpuWritePermit(CSC_WPB_CpuType eCpuType)
{
    uint32_t u32RegVal = CSC0->CPU0_INT;
    CSC0->CPU0_INT = ((u32RegVal & (~(uint32_t)CSC0_CPU0_INT_WPB_MASK)) | CSC0_CPU0_INT_WPB(eCpuType));
}

/**
 * @brief Enable cpu0 software interrupt
 *
 */
LOCAL_INLINE void CSC0_HWA_CPU0INT_EnableSWInterrupt(void)
{
    CSC0->CPU0_INT |= (uint32_t)CSC0_CPU0_INT_SW_INT_MASK;
}

/**
 * @brief Disable cpu0 software interrupt
 *
 */
LOCAL_INLINE void CSC0_HWA_CPU0INT_DisableSWInterrupt(void)
{
    CSC0->CPU0_INT &= ~(uint32_t)CSC0_CPU0_INT_SW_INT_MASK;
}

/**
 * @brief Enable CSC0 clock out
 *
 */
LOCAL_INLINE void CSC0_HWA_EnableClockOut(void)
{
    CSC0->CLKOUT_CTRL |= (uint32_t)CSC0_CLKOUT_CTRL_CLKOUT_EN_MASK;
}

/**
 * @brief Disable CSC0 clock out
 *
 */
LOCAL_INLINE void CSC0_HWA_DisableClockOut(void)
{
    CSC0->CLKOUT_CTRL &= ~(uint32_t)CSC0_CLKOUT_CTRL_CLKOUT_EN_MASK;
}

/**
 * @brief Get CLKOUT CSC0 clock out divider
 *
 * @return CSC0_ClockOutDivType CSC0 clock out divider
 */
LOCAL_INLINE CSC0_ClockOutDivType CSC0_HWA_GetClkOutDiv(void)
{
    uint32_t u32RegVal = (CSC0->CLKOUT_CTRL & CSC0_CLKOUT_CTRL_CLKOUT_DIV_MASK) >> CSC0_CLKOUT_CTRL_CLKOUT_DIV_SHIFT;
    return (CSC0_ClockOutDivType)u32RegVal;
}

/**
 * @brief Set CLKOUTDIV
 *
 * @param eDivType CSC0 clock out divider
 */
LOCAL_INLINE void CSC0_HWA_SetClkOutDiv(CSC0_ClockOutDivType eDivType)
{
    uint32_t u32RegVal = CSC0->CLKOUT_CTRL;
    CSC0->CLKOUT_CTRL = ((u32RegVal & (~(uint32_t)CSC0_CLKOUT_CTRL_CLKOUT_DIV_MASK)) | CSC0_CLKOUT_CTRL_CLKOUT_DIV(eDivType));
}

/**
 * @brief Get CLKOUT source Select
 *
 * @return CSC0_ClockOutSrcType CSC0 clock out source
 */
LOCAL_INLINE CSC0_ClockOutSrcType CSC0_HWA_GetClkOutSel(void)
{
    uint32_t u32RegVal = (CSC0->CLKOUT_CTRL & CSC0_CLKOUT_CTRL_CLKOUT_SEL_MASK) >> CSC0_CLKOUT_CTRL_CLKOUT_SEL_SHIFT;
    return (CSC0_ClockOutSrcType)u32RegVal;
}

/**
 * @brief Set CLKOUT source Select
 *
 * @param eClkSrcType CSC0 clock out source
 */
LOCAL_INLINE void CSC0_HWA_SetClkOutSel(CSC0_ClockOutSrcType eClkSrcType)
{
    uint32_t u32RegVal = CSC0->CLKOUT_CTRL;
    CSC0->CLKOUT_CTRL = ((u32RegVal & (~(uint32_t)CSC0_CLKOUT_CTRL_CLKOUT_SEL_MASK)) | CSC0_CLKOUT_CTRL_CLKOUT_SEL(eClkSrcType));
}

/**
 * @brief Lock CSC0_CLKOUT_CTRL register
 *
 */
LOCAL_INLINE void CSC0_HWA_LockCLKOUT_CTRL(void)
{
    CSC0->CLKOUT_CTRL |= (uint32_t)CSC0_CLKOUT_CTRL_LOCK_MASK;
}

/**
 * @brief Get CSC0_CLKOUT_CTRL register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_CLKOUT_CTRL_GetLockStatus(void)
{
    return (CSC0->CLKOUT_CTRL & (uint32_t)CSC0_CLKOUT_CTRL_LOCK_MASK);
}

/**
 * @brief Get AONCLKSR register status
 *
 * @return AONCLKSR register status
 */
LOCAL_INLINE uint32_t CSC0_HWA_GetStatus_AONCLKSR(void)
{
    return CSC0->AONCLKSR;
}

/**
 * @brief Get CSC0_AON32KCLK source clock
 *
 * @return CSC0_AON32KClkSrcType CSC0_AON32KCLK source type
 */
LOCAL_INLINE CSC0_AON32KClkSrcType CSC0_HWA_GetAON32kClkSrc(void)
{
    uint32_t u32RegVal = (CSC0->AONCLKSR & CSC0_AONCLKSR_AON32KCLKSEL_MASK) >> CSC0_AONCLKSR_AON32KCLKSEL_SHIFT;
    return (CSC0_AON32KClkSrcType)u32RegVal;
}

/**
 * @brief Set CSC0_AON32KCLK source clock
 *
 * @param CSC0_AON32KClkSrcType CSC0_AON32KCLK source type
 */
LOCAL_INLINE void CSC0_HWA_SetAON32kClkSrc(CSC0_AON32KClkSrcType eClkSrcType)
{
    uint32_t u32RegVal = CSC0->AONCLKSR;
    CSC0->AONCLKSR = ((u32RegVal & (~(uint32_t)CSC0_AONCLKSR_AON32KCLKSEL_MASK)) | CSC0_AONCLKSR_AON32KCLKSEL(eClkSrcType));
}

/**
 * @brief Get CSC0_RTCCLK source clock
 *
 * @return CSC0_RTCClkSrcType CSC0_RTCCLK source type
 */
LOCAL_INLINE CSC0_RTCClkSrcType CSC0_HWA_GetRTCClkSrc(void)
{
    uint32_t u32RegVal = (CSC0->AONCLKSR & CSC0_AONCLKSR_RTCCLKSEL_MASK) >> CSC0_AONCLKSR_RTCCLKSEL_SHIFT;
    return (CSC0_RTCClkSrcType)u32RegVal;
}

/**
 * @brief Set CSC0_RTCCLK source clock
 *
 * @param CSC0_RTCClkSrcType CSC0_RTCCLK source type
 */
LOCAL_INLINE void CSC0_HWA_SetRTCClkSrc(CSC0_RTCClkSrcType eClkSrcType)
{
    uint32_t u32RegVal = CSC0->AONCLKSR;
    CSC0->AONCLKSR = ((u32RegVal & (~(uint32_t)CSC0_AONCLKSR_RTCCLKSEL_MASK)) | CSC0_AONCLKSR_RTCCLKSEL(eClkSrcType));
}

/**
 * @brief Get CSC0_AONCLK source clock
 *
 * @return CSC0_AONClkSrcType CSC0_AONCLK source type
 */
LOCAL_INLINE CSC0_AONClkSrcType CSC0_HWA_GetAONClkSrc(void)
{
    uint32_t u32RegVal = (CSC0->AONCLKSR & CSC0_AONCLKSR_AONCLKSEL_MASK) >> CSC0_AONCLKSR_AONCLKSEL_SHIFT;
    return (CSC0_AONClkSrcType)u32RegVal;
}

/**
 * @brief Set CSC0_AONCLK source clock
 *
 * @param CSC0_AONClkSrcType CSC0_AONCLK source type
 */
LOCAL_INLINE void CSC0_HWA_SetAONClkSrc(CSC0_AONClkSrcType eClkSrcType)
{
    uint32_t u32RegVal = CSC0->AONCLKSR;
    CSC0->AONCLKSR = ((u32RegVal & (~(uint32_t)CSC0_AONCLKSR_AONCLKSEL_MASK)) | CSC0_AONCLKSR_AONCLKSEL(eClkSrcType));
}

/**
 * @brief Enable CSC0_SIRCDIV32K clock out
 *
 */
LOCAL_INLINE void CSC0_HWA_EnableSIRCDIV_32KClkOut(void)
{
    CSC0->AONCLKSR |= (uint32_t)CSC0_AONCLKSR_SIRCDIV32KEN_MASK;
}

/**
 * @brief Disable CSC0_SIRCDIV32K clock out
 *
 */
LOCAL_INLINE void CSC0_HWA_DisableSIRCDIV_32KClkOut(void)
{
    CSC0->AONCLKSR &= ~(uint32_t)CSC0_AONCLKSR_SIRCDIV32KEN_MASK;
}

/**
 * @brief Enable CSC0_SIRC32_1K clock out
 *
 */
LOCAL_INLINE void CSC0_HWA_EnableSIRC32_1KClkOut(void)
{
    CSC0->AONCLKSR |= (uint32_t)CSC0_AONCLKSR_AON1KCLKEN_MASK;
}

/**
 * @brief Disable CSC0_SIRC32_1K clock out
 *
 */
LOCAL_INLINE void CSC0_HWA_DisableSIRC32_1KClkOut(void)
{
    CSC0->AONCLKSR &= ~(uint32_t)CSC0_AONCLKSR_AON1KCLKEN_MASK;
}

/**
 * @brief Lock CSC0_AONCLKSR register
 *
 */
LOCAL_INLINE void CSC0_HWA_LockAONCLKSR(void)
{
    CSC0->AONCLKSR |= (uint32_t)CSC0_AONCLKSR_LOCK_MASK;
}

/**
 * @brief Get CSC0_AONCLKSR register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_AONCLKSR_GetLockStaus(void)
{
    return (CSC0->AONCLKSR & (uint32_t)CSC0_AONCLKSR_LOCK_MASK);
}

/**
 * @brief Set count for reduce power mode exit
 *
 * @param u8Conut count to be set
 */
LOCAL_INLINE void CSC0_HWA_SetRpmExitCount(uint8_t u8Conut)
{
    uint32_t u32RegVal = CSC0->PCU_CTRL;
    CSC0->PCU_CTRL = ((u32RegVal & (~(uint32_t)CSC0_PCU_CTRL_RPM_EXIT_CNT_MASK)) | CSC0_PCU_CTRL_RPM_EXIT_CNT(u8Conut));
}

/**
 * @brief Get count of reduce power mode exit
 *
 *  @return count be got
 */
LOCAL_INLINE uint8_t CSC0_HWA_GetRpmExitCount(void)
{
    return (uint8_t)((CSC0->PCU_CTRL & (uint32_t)CSC0_PCU_CTRL_RPM_EXIT_CNT_MASK)>>CSC0_PCU_CTRL_RPM_EXIT_CNT_SHIFT);
}

/**
 * @brief Set power domain 1 isolation enable hold
 *
 */
LOCAL_INLINE void CSC0_HWA_SetPadIsoHold(void)
{
    CSC0->PCU_CTRL |= CSC0_PCU_CTRL_PAD_ISO_HOLD_MASK;
}

/**
 * @brief Power domain 1 isolation enable hold clear
 *
 */
LOCAL_INLINE void CSC0_HWA_CLearPadIsoHold(void)
{
    CSC0->PCU_CTRL |= CSC0_PCU_CTRL_PAD_ISO_HOLD_CLR_MASK;
}

/**
 * @brief Lock CSC0_PCU_CTRL register
 *
 */
LOCAL_INLINE void CSC0_HWA_LockPCU_CTRL(void)
{
    CSC0->PCU_CTRL |= (uint32_t)CSC0_PCU_CTRL_LOCK_MASK;
}

/**
 * @brief Unlock CSC0_PCU_CTRL register
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_PCU_CTRL_GetLockStatus(void)
{
    return (CSC0->PCU_CTRL & (uint32_t)CSC0_PCU_CTRL_LOCK_MASK);
}

/**
 * @brief Enable CSC_SMU  control group 0
 *
 * @param eType CSC_SMU  control group 0 type
 */
LOCAL_INLINE void CSC0_HWA_CTRL0_EnableReqToSMU(CSC_SMU_CtrlGrp0Type eType)
{
    CSC0->SMU_CTRL0 |= (uint32_t)eType;
}

/**
 * @brief Disable CSC_SMU  control group 0
 *
 * @param eType CSC_SMU  control group 0 type
 */
LOCAL_INLINE void CSC0_HWA_CTRL0_DisableReqToSMU(CSC_SMU_CtrlGrp0Type eType)
{
    CSC0->SMU_CTRL0 &= ~(uint32_t)eType;
}

/**
 * @brief Set multiple CSC_SMU  control group 0
 *
 * @param u32Value The or value of CSC_SMU_CtrlGrp0Type
 */
LOCAL_INLINE void CSC0_HWA_CTRL0_SetMultiReqToSMU(uint32_t u32Value)
{
    CSC0->SMU_CTRL0 = u32Value;
}

/**
 * @brief Clear multiple CSC_SMU  control group 0
 *
 * @param u32Value The or value of CSC_SMU_CtrlGrp0Type
 */
LOCAL_INLINE void CSC0_HWA_CTRL0_ClearMultiReqToSMU(uint32_t u32Value)
{
    CSC0->SMU_CTRL0 &= ~u32Value;
}

/**
 * @brief Lock CSC0_SMU_CTRL0 register
 *
 */
LOCAL_INLINE void CSC0_HWA_LockSMU_CTRL0(void)
{
    CSC0->SMU_CTRL0 |= (uint32_t)CSC0_SMU_CTRL0_LOCK_MASK;
}

/**
 * @brief Get CSC0_SMU_CTRL0 register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_SMU_CTRL0_GetLockStatus(void)
{
    return (CSC0->SMU_CTRL0 & (uint32_t)CSC0_SMU_CTRL0_LOCK_MASK);
}

/**
 * @brief Enable CSC_SMU  control group 1
 *
 * @param eType CSC_SMU  control group 1 type
 */
LOCAL_INLINE void CSC0_HWA_CTRL1_EnableReqToSMU(CSC_SMU_Cpux_CtrlGrpType eType)
{
    CSC0->SMU_CTRL1 |= (uint32_t)eType;
}

/**
 * @brief Disable CSC_SMU  control group 1
 *
 * @param eType CSC_SMU  control group 1 type
 */
LOCAL_INLINE void CSC0_HWA_CTRL1_DisableReqToSMU(CSC_SMU_Cpux_CtrlGrpType eType)
{
    CSC0->SMU_CTRL1 &= ~(uint32_t)eType;
}

/**
 * @brief Set multiple CSC_SMU  control group 1
 *
 * @param u32Value The or value of CSC_SMU_Cpux_CtrlGrpType
 */
LOCAL_INLINE void CSC0_HWA_CTRL1_SetMultiReqToSMU(uint32_t u32Value)
{
    CSC0->SMU_CTRL1 = u32Value;
}

/**
 * @brief Clear multiple CSC_SMU  control group 1
 *
 * @param u32Value The or value of CSC_SMU_Cpux_CtrlGrpType
 */
LOCAL_INLINE void CSC0_HWA_CTRL1_ClearMultiReqToSMU(uint32_t u32Value)
{
    CSC0->SMU_CTRL1 &= ~u32Value;
}

/**
 * @brief Lock CSC0_SMU_CTRL1 register
 *
 */
LOCAL_INLINE void CSC0_HWA_LockSMU_CTRL1(void)
{
    CSC0->SMU_CTRL1 |= (uint32_t)CSC0_SMU_CTRL1_LOCK_MASK;
}

/**
 * @brief Get CSC0_SMU_CTRL1 register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_SMU_CTRL1_GetLockStatus(void)
{
    return (CSC0->SMU_CTRL1 & (uint32_t)CSC0_SMU_CTRL1_LOCK_MASK);
}

/**
 * @brief Enable CSC_SMU  control group 4
 *
 * @param eType CSC_SMU  control group 4 type
 */
LOCAL_INLINE void CSC0_HWA_CTRL4_EnableReqToSMU(CSC_SMU_CtrlGrp4Type eType)
{
    CSC0->SMU_CTRL4 |= (uint32_t)eType;
}

/**
 * @brief Disable CSC_SMU  control group 4
 *
 * @param eType CSC_SMU  control group 4 type
 */
LOCAL_INLINE void CSC0_HWA_CTRL4_DisableReqToSMU(CSC_SMU_CtrlGrp4Type eType)
{
    CSC0->SMU_CTRL4 &= ~(uint32_t)eType;
}

/**
 * @brief Set multiple CSC_SMU  control group 4
 *
 * @param u32Value The or value of CSC_SMU_CtrlGrp4Type
 */
LOCAL_INLINE void CSC0_HWA_CTRL4_SetMultiReqToSMU(uint32_t u32Value)
{
    CSC0->SMU_CTRL4 = u32Value;
}

/**
 * @brief Clear multiple CSC_SMU  control group 4
 *
 * @param u32Value The or value of CSC_SMU_CtrlGrp4Type
 */
LOCAL_INLINE void CSC0_HWA_CTRL4_ClearMultiReqToSMU(uint32_t u32Value)
{
    CSC0->SMU_CTRL4 &= ~u32Value;
}

/**
 * @brief Lock CSC0_SMU_CTRL4 register
 *
 */
LOCAL_INLINE void CSC0_HWA_LockSMU_CTRL4(void)
{
    CSC0->SMU_CTRL4 |= (uint32_t)CSC0_SMU_CTRL4_LOCK_MASK;
}

/**
 * @brief Get CSC0_SMU_CTRL4 register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_SMU_CTRL4_GetLockStatus(void)
{
    return (CSC0->SMU_CTRL4 & (uint32_t)CSC0_SMU_CTRL4_LOCK_MASK);
}

/**
 * @brief Enable CSC_SMU  control group 5
 *
 * @param eType CSC_SMU  control group 5 type
 */
LOCAL_INLINE void CSC0_HWA_CTRL5_EnableReqToSMU(CSC_SMU_CtrlGrp5Type eType)
{
    CSC0->SMU_CTRL5 |= (uint32_t)eType;
}

/**
 * @brief Disable CSC_SMU  control group 5
 *
 * @param eType CSC_SMU  control group 5 type
 */
LOCAL_INLINE void CSC0_HWA_CTRL5_DisableReqToSMU(CSC_SMU_CtrlGrp5Type eType)
{
    CSC0->SMU_CTRL5 &= ~(uint32_t)eType;
}

/**
 * @brief Set multiple CSC_SMU  control group 5
 *
 * @param u32Value The or value of CSC_SMU_CtrlGrp5Type
 */
LOCAL_INLINE void CSC0_HWA_CTRL5_SetMultiReqToSMU(uint32_t u32Value)
{
    CSC0->SMU_CTRL5 = u32Value;
}

/**
 * @brief Clear multiple CSC_SMU  control group 5
 *
 * @param u32Value The or value of CSC_SMU_CtrlGrp4Type
 */
LOCAL_INLINE void CSC0_HWA_CTRL5_ClearMultiReqToSMU(uint32_t u32Value)
{
    CSC0->SMU_CTRL5 &= ~u32Value;
}

/**
 * @brief Lock CSC0_SMU_CTRL5 register
 *
 */
LOCAL_INLINE void CSC0_HWA_LockSMU_CTRL5(void)
{
    CSC0->SMU_CTRL5 |= (uint32_t)CSC0_SMU_CTRL5_LOCK_MASK;
}

/**
 * @brief Get CSC0_SMU_CTRL5 register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_SMU_CTRL5_GetLockStatus(void)
{
    return (CSC0->SMU_CTRL5 & (uint32_t)CSC0_SMU_CTRL5_LOCK_MASK);
}

/**
 * @brief Enable CSC_CMU  control group
 *
 * @param eType CSC_CMU  control group type
 */
LOCAL_INLINE void CSC0_HWA_EnableReqToCMU(CSC0_CMU_CtrlGrpType eType)
{
    CSC0->CMU_CTRL |= (uint32_t)eType;
}

/**
 * @brief Disable CSC_CMU  control group
 *
 * @param eType CSC_CMU  control group type
 */
LOCAL_INLINE void CSC0_HWA_DisableReqToCMU(CSC0_CMU_CtrlGrpType eType)
{
    CSC0->CMU_CTRL &= ~(uint32_t)eType;
}

/**
 * @brief Lock CSC0_SMU_CTRL4 register
 *
 */
LOCAL_INLINE void CSC0_HWA_LockCMU_CTRL(void)
{
    CSC0->CMU_CTRL |= (uint32_t)CSC0_CMU_CTRL_LOCK_MASK;
}

/**
 * @brief Get CSC0_SMU_CTRL4 register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_CMU_CTRL_GetLockStatus(void)
{
    return (CSC0->CMU_CTRL & (uint32_t)CSC0_CMU_CTRL_LOCK_MASK);
}

/**
 * @brief Set low power wakeup PADx configure source
 *
 * @param eGroup Low power PADx group type
 * @eSrc eSrc Low power wakeup PADx configure source
 */
LOCAL_INLINE void CSC0_HWA_SetLP_WAKEUPCfgSrc(CSC0_LPWakeupGrpType eGroup, CSC0_LPWakeupSrcType eSrc)
{
    CSC0->LP_WAKEUP = (CSC0->LP_WAKEUP & (~(CSC0_LP_WAKEUP_LP_WAKEUP_CFG0_MASK >> (4U * (uint32_t)eGroup)))) |
                      (CSC0_LP_WAKEUP_LP_WAKEUP_CFG0(eSrc) >> (4U * (uint32_t)eGroup));
}


/**
 * @brief Set low power wakeup PADx configure source polarity
 *
 * @param eGroup Low power PADx group type
 * @eSrc eSrc Low power wakeup PADx configure source polarity
 */
LOCAL_INLINE void CSC0_HWA_SetLP_WAKEUPCfgPol(CSC0_LPWakeupGrpType eGroup, CSC0_LPWakeupPolType ePolarity)
{
    CSC0->LP_WAKEUP = (CSC0->LP_WAKEUP & (~(CSC0_LP_WAKEUP_LP0_POL_MASK >> (uint32_t)eGroup))) |
                      (CSC0_LP_WAKEUP_LP0_POL(ePolarity) >> (uint32_t)eGroup);
}

/**
 * @brief Lock low power wakeup register
 *
 */
LOCAL_INLINE void CSC0_HWA_LockLP_WAKEUP(void)
{
    CSC0->LP_WAKEUP |= (uint32_t)CSC0_LP_WAKEUP_LOCK_MASK;
}

/**
 * @brief Get low power wakeup register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t CSC0_HWA_LP_WAKEUP_GetLockStatus(void)
{
    return (CSC0->LP_WAKEUP & (uint32_t)CSC0_LP_WAKEUP_LOCK_MASK);
}

#endif  /*#ifndef _HWA_CSC_H_*/
