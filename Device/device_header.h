/**
 * @file device_header.h
 * @author Flagchip
 * @brief include all peripheral register files
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
#ifndef DEVICE_HEADER_H
#define DEVICE_HEADER_H

#define __FPU_PRESENT                  1
#define __MPU_PRESENT                  1         /**< Defines if an MPU is present or not */
#define __ICACHE_PRESENT 1U
#define __DCACHE_PRESENT 1U

#include <stdarg.h>

#include "typedef.h"
#include "v_def.h"

#include "fclib/fcmath.h"
#include "fclib/fcfunc.h"
#include "cm7/cmsis_compiler.h"
#include "cm7/core_cm7_regs.h"
#include "cm7/arm_cortex_m7_asm.h"
#include "cm7/mpu_armv7.h"

#include "fc/fc7240_acc_regs.h"
#include "fc/fc7240_adc_regs.h"
#include "fc/fc7240_aontimer_regs.h"
#include "fc/fc7240_cmp_regs.h"
#include "fc/fc7240_cmu_regs.h"
#include "fc/fc7240_cordic_regs.h"
#include "fc/fc7240_cpm_regs.h"
#include "fc/fc7240_crc_regs.h"
#include "fc/fc7240_csc0_regs.h"
#include "fc/fc7240_dmamux_regs.h"
#include "fc/fc7240_dma_regs.h"
#include "fc/fc7240_eim_regs.h"
#include "fc/fc7240_erm_regs.h"
#include "fc/fc7240_fciic_regs.h"
#include "fc/fc7240_fcpit_regs.h"
#include "fc/fc7240_fcsmu_regs.h"
#include "fc/fc7240_fcspi_regs.h"
#include "fc/fc7240_fcuart_regs.h"
#include "fc/fc7240_flexcan_regs.h"
#include "fc/fc7240_fmc_regs.h"
#include "fc/fc7240_freqm_regs.h"
#include "fc/fc7240_ftu_regs.h"
#include "fc/fc7240_gpio_regs.h"
#include "fc/fc7240_intm_regs.h"
#include "fc/fc7240_ism_regs.h"
#include "fc/fc7240_lu_regs.h"
#include "fc/fc7240_mam_regs.h"
#include "fc/fc7240_mb_regs.h"
#include "fc/fc7240_msc_regs.h"
#include "fc/fc7240_ahb_overlay_regs.h"
#include "fc/fc7240_pcc_regs.h"
#include "fc/fc7240_pmc_regs.h"
#include "fc/fc7240_port_regs.h"
#include "fc/fc7240_ptimer_regs.h"
#include "fc/fc7240_rgm_regs.h"
#include "fc/fc7240_rtc_regs.h"
#include "fc/fc7240_scg_regs.h"
#include "fc/fc7240_scm_regs.h"
#include "fc/fc7240_stcu_regs.h"
#include "fc/fc7240_sec_regs.h"
#include "fc/fc7240_sent_regs.h"
#include "fc/fc7240_smc_regs.h"
#include "fc/fc7240_stcu_regs.h"
#include "fc/fc7240_tmu_regs.h"
#include "fc/fc7240_tpu_e_regs.h"
#include "fc/fc7240_tpu_h_regs.h"
#include "fc/fc7240_trgsel_regs.h"
#include "fc/fc7240_tstmp_regs.h"
#include "fc/fc7240_wdog_regs.h"
#include "fc/fc7240_wku_regs.h"


#define PFLASH_START          0x01000000U
#define PFLASH_END            0x011FFFFFU

#define SRAM_START            0x21000000U
#define SRAM_END              0x21017FFFU


#define INLINE_FLASHDRIVER_RAM    STD_OFF

#define WDOG0_RECONF_LOCK_DELAY_US   100U  /* 100us */



#if (defined(__ICCARM__))

#define PROCESS_UNUSED_VAR(var)        (var) = (var);

#elif defined __GNUC__
#define PROCESS_UNUSED_VAR(var)        (void)(var);

#elif defined __ghs__

#define PROCESS_UNUSED_VAR(var)        (void)(var);
#endif


#define FC4150F512                    0x01U
#define FC4150F2M                     0x02U
#define FC7300HSM                     0x03U
#define FC7300CM7                     0x04U
#define FC7240HOST					  0x05U
#define FC7240FLEXCORE				  0x06U
#define DEVICE_TYPE                   FC7240HOST

#endif /* DEVICE_HEADER_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
