/**
 * @file HwA_scm.h
 * @author Flagchip085
 * @brief Hardware access layer for SCM
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

#ifndef _HWA_SCM_H_
#define _HWA_SCM_H_
#include "device_header.h"

/********* Local typedef ************/

/**
 * @brief WPB cpu type
 *
 */
typedef enum
{
    SCM_WP_CPU_ALL  = 0U,  /*!< All CPUs are allowed to write this peripheral */
    SCM_WP_CPU_0    = 1U,  /*!< Only CPU0 is allowed to control this peripheral */
    SCM_WP_CPU_NONE        /*!< No CPU is allowed to control this peripheral */
} SCM_WPB_CpuType;

/**
 * @brief ECC Enable mode Control type
 *
 */
typedef enum
{
    SCM_ECC_WRITE_EN_READ_DIS = 2U, /*!< ECC Generate Enable During Write, ECC Check Disable During Read */
    SCM_ECC_WRITE_EN_READ_EN  = 3U  /*!< ECC Generate Enable During Write, ECC Check Enable During Read */
} SCM_EccEnModeType;

/**
 * @brief MAMECCEN0 MAM ECC Enable group 0 type
 *
 */
typedef enum
{
    SCM_MAM0_S0_ECC  = 0U,  /*!< MAM0 S0 ROM Array ECC Enable Control */
    SCM_MAM0_S1_ECC  = 1U,  /*!< MAM0 S1 PFlash Slave ECC Enable Control */
    SCM_MAM0_S2_ECC  = 3U,  /*!< MAM0 S2 DFlash Slave ECC Enable Control */
    SCM_MAM0_S3_ECC  = 4U,  /*!< MAM0 S3 SRAM0 Slave ECC Enable Control */
    SCM_MAM0_S4_ECC  = 5U,  /*!< MAM0 S4 SRAM1 Slave ECC Enable Control */
    SCM_MAM0_S5_ECC  = 7U,  /*!< MAM0 S5 TCM Slave ECC Enable Control */
    SCM_MAM0_S6_ECC  = 8U,  /*!< MAM0 S6 AFCB0 Slave ECC Enable Control */
    SCM_MAM0_S7_ECC  = 9U,  /*!< MAM0 S7 AFCB1 Slave ECC Enable Control */
    SCM_MAM0_S8_ECC  = 10U, /*!< MAM0 S8 GPIO Slave ECC Enable Control */
    SCM_SRAM0_ECC    = 11U, /*!< SRAM0 Array ECC Enable Control */
    SCM_SRAM1_ECC    = 12U  /*!< SRAM1 Array ECC Enable Control */
} SCM_MAMEccCtrlGrp0Type;

/**
 * @brief MAMECCEN1 MAM ECC Enable group 1 type
 *
 */
typedef enum
{
    SCM_HSM_ECC       = 0U, /*!< HSM Master ECC Enable Control */
    SCM_DMA0_ECC      = 2U, /*!< DMA0 Master ECC Enable Control */
    SCM_DMA0_CFG_ECC  = 4U, /*!< DMA0 CFG Memory  ECC Enable Control */
    SCM_HSM_DRAM_ECC  = 5U, /*!< HSM DRAM Memory  ECC Enable Control */
    SCM_HSM_IRAM_ECC  = 6U  /*!< HSM IRAM Memory ECC Enable Control */
} SCM_MAMEccCtrlGrp1Type;

/**
 * @brief CPU0 ECC Enable Register type
 *
 */
typedef enum
{
    SCM_CPUXECCEN_CPUX_AHBM_ECC  = 0U,  /*!< SCM_CPUXECCEN_CPUX_AHBM_ECC peripheral */
    SCM_CPUXECCEN_CPUX_AHBP_ECC  = 1U,  /*!< SCM_CPUXECCEN_CPUX_AHBP_ECC peripheral */
    SCM_CPUXECCEN_CPUX_AHBS_ECC  = 2U,  /*!< SCM_CPUXECCEN_CPUX_AHBS_ECC peripheral */
    SCM_CPUXECCEN_CPUX_DTCM0_ECC = 3U,  /*!< SCM_CPUXECCEN_CPUX_DTCM0_ECC peripheral */
    SCM_CPUXECCEN_CPUX_DTCM1_ECC = 4U,  /*!< SCM_CPUXECCEN_CPUX_DTCM1_ECC peripheral */
    SCM_CPUXECCEN_CPUX_ITCM_ECC  = 5U   /*!< SCM_CPUXECCEN_CPUX_ITCM_ECC peripheral */
} SCM_CPUEccCtrlType;

/**
 * @brief FCSPI monitor type
 *
 */
typedef enum
{
    SCM_MON_FCSPI0 = 0U,  /*!< Monitor FCSPI0's transmit interface */
    SCM_MON_FCSPI1,       /*!< Monitor FCSPI1's transmit interface */
    SCM_MON_FCSPI2,       /*!< Monitor FCSPI2's transmit interface */
    SCM_MON_FCSPI3,       /*!< Monitor FCSPI3's transmit interface */
    SCM_MON_FCSPI4,       /*!< Monitor FCSPI4's transmit interface */
    SCM_MON_FCSPI5        /*!< Monitor FCSPI5's transmit interface */
} SCM_FCSPIxType;

/**
 * @brief FCUART monitor type
 *
 */
typedef enum
{
    SCM_MON_FCUART0 = 0U,  /*!< Monitor FCUART0's transmit interface */
    SCM_MON_FCUART1,       /*!< Monitor FCUART1's transmit interface */
    SCM_MON_FCUART2,       /*!< Monitor FCUART2's transmit interface */
    SCM_MON_FCUART3,       /*!< Monitor FCUART3's transmit interface */
    SCM_MON_FCUART4,       /*!< Monitor FCUART4's transmit interface */
    SCM_MON_FCUART5,       /*!< Monitor FCUART5's transmit interface */
    SCM_MON_FCUART6,       /*!< Monitor FCUART6's transmit interface */
    SCM_MON_FCUART7        /*!< Monitor FCUART7's transmit interface */
} SCM_MON_FCUARTxType;

/**
 * @brief PTIMER Loop Mode Select type
 *
 */
typedef enum
{
    SCM_LM_PTMR0CH0_PTMR1CH0       = 0U,/*!< PTIMER0 CH0 loop, PTIMER1 CH0 loop */
    SCM_LM_PTMR1CH0_CH1            = 1U,/*!< PTIMER1 CH0 and CH1 in loop mode */
    SCM_LM_PTMR0CH0_CH1            = 2U,/*!< PTIMER0 CH0 and CH1 in loop mode */
    SCM_LM_PTMR0CH0CH1_PTMR1CH0CH1 = 3U,/*!< PTIMER1 CH0 and CH1 in loop mode, PTIMER0 CH0 and CH1 in loop mode */
    SCM_LM_PTMR0_PTMR1_CH0         = 4U /*!< PTIMER0 CH0 and PTIMER1 CH0 in loop mode */
} SCM_PTimerLMSelType;

/**
 * @brief ADC Trigger Source type
 *
 */
typedef enum
{
    SCM_ADC_TRIGGER_SRC_PTIMER = 0U, /*!< ADC Trigger Source PTIMER output */
    SCM_ADC_TRIGGER_SRC_TRGSEL = 1U  /*!< ADC Trigger Source TRGSEL output */
} SCM_AdcTriggerSrcType;

/**
 * @brief ADC PreTrigger Source type
 *
 */
typedef enum
{
    SCM_ADC_PRETRIGGER_PTIMER      = 0U, /*!< ADC Pre-trigger PTIMER */
    SCM_ADC_PRETRIGGER_SCMSOFTWARE = 2U  /*!< ADC Pre-trigger SCM software */
} SCM_AdcPreTriggerSrcType;

/**
 * @brief ADC SCM software Pre-trigger Sources type
 *
 */
typedef enum
{
    SCM_SOFTWARE_PRETRIGGER_DISABLED = 0U,  /*!< SCM Software pre-trigger disabled */
    SCM_SOFTWARE_PRETRIGGER_0        = 4U,  /*!< SCM Software pre-trigger 0 */
    SCM_SOFTWARE_PRETRIGGER_1        = 5U,  /*!< SCM Software pre-trigger 1 */
    SCM_SOFTWARE_PRETRIGGER_2        = 6U,  /*!< SCM Software pre-trigger 2 */
    SCM_SOFTWARE_PRETRIGGER_3        = 7U   /*!< SCM Software pre-trigger 3 */
} SCM_SoftwarePreTriggerType;

/**
 * @brief FTUx output source selection type
 *
 */
typedef enum
{
    SCM_FTU_OUTPUT_STD = 0U,  /*!< FTUx CHx output will direct route to corresponding pad(standard) */
    SCM_FTU_OUT_COMBINE       /*!< FTUx pad output is equal to FTUx CHx output & FTUx CH1 output(combine) */
} SCM_FTU_OutputSelType;

/**
 * @brief FTU2 CH1 input selection type
 *
 */
typedef enum
{
    SCM_FTU_INPUT_STD = 0U,  /*!< FTU2_CH1 input */
    SCM_FTU_INPUT_OR         /*!< OR of FTU2_CH0,FTU2_CH1,and FTU1_CH1 */
} SCM_FTU2_CH1_InputSelType;

/**
 * @brief FTUx CH0 input selection type
 *
 */
typedef enum
{
    SCM_FTU_CH0_INPUT_STD = 0U,  /*!< FTU2_CH0 input */
    SCM_FTU_CH0_INPUT_CMP0,      /*!< CMP0 output */
    SCM_FTU_CH0_INPUT_CMP1       /*!< CMP1 output */
} SCM_FTUx_CH0_InputSelType;

/**
 * @brief FTU Global Time Base Control type
 *
 */
typedef enum
{
    SCM_FTU0_GTBC = 0x01U,     /*!< FTU0 Global Time Base Control Select */
    SCM_FTU1_GTBC = 0x02U,     /*!< FTU1 Global Time Base Control Select */
    SCM_FTU2_GTBC = 0x04U,     /*!< FTU2 Global Time Base Control Select */
    SCM_FTU3_GTBC = 0x08U,     /*!< FTU3 Global Time Base Control Select */
    SCM_FTU4_GTBC = 0x10U,     /*!< FTU4 Global Time Base Control Select */
    SCM_FTU5_GTBC = 0x20U,     /*!< FTU5 Global Time Base Control Select */
    SCM_FTU6_GTBC = 0x40U,     /*!< FTU6 Global Time Base Control Select */
    SCM_FTU7_GTBC = 0x80U,     /*!< FTU7 Global Time Base Control Select */
} SCM_FTUGTBCtrlType;

/**
 * @brief FTU SYNC Control type
 *
 */
typedef enum
{
    SCM_FTU0_SYNC = SCM_FTU_SYNC_FTU0SYNC_MASK,     /*!< FTU0 Sync Control */
    SCM_FTU1_SYNC = SCM_FTU_SYNC_FTU1SYNC_MASK,     /*!< FTU1 Sync Control */
    SCM_FTU2_SYNC = SCM_FTU_SYNC_FTU2SYNC_MASK,     /*!< FTU2 Sync Control */
    SCM_FTU3_SYNC = SCM_FTU_SYNC_FTU3SYNC_MASK,     /*!< FTU3 Sync Control */
    SCM_FTU4_SYNC = SCM_FTU_SYNC_FTU4SYNC_MASK,     /*!< FTU4 Sync Control */
    SCM_FTU5_SYNC = SCM_FTU_SYNC_FTU5SYNC_MASK,     /*!< FTU5 Sync Control */
    SCM_FTU6_SYNC = SCM_FTU_SYNC_FTU6SYNC_MASK,     /*!< FTU6 Sync Control */
    SCM_FTU7_SYNC = SCM_FTU_SYNC_FTU7SYNC_MASK,     /*!< FTU7 Sync Control */
} SCM_FTUSyncCtrlType;

/**
 * @brief Trace clock selection
 *
 */
typedef enum
{
    SCM_TRACE_CORE_CLK      = 0U,  /*!< Select platform fclk to trace clock */
    SCM_TRACE_PLL1DIVH_CLK  = 1U   /*!< Select SCG PLL1 platform clock to trace clock */
} SCM_TraceClkSrcType;

/**
 * @brief Software trigger to TRGSEL0/TRGSEL1
 *
 */
typedef enum
{
    SCM_SW_TRIG_0 = 1U,  /*!< Generate software trigger0 to (TRGSEL0 & TRGSEL4) */
    SCM_SW_TRIG_1 = 2U,  /*!< Generate software trigger1 to (TRGSEL0 & TRGSEL4) */
    SCM_SW_TRIG_2 = 4U,  /*!< Generate software trigger2 to (TRGSEL0 & TRGSEL4) */
    SCM_SW_TRIG_3 = 8U,  /*!< Generate software trigger3 to (TRGSEL0 & TRGSEL4) */
    SCM_SW_TRIG_4 = 1U,  /*!< Generate software trigger4 to (TRGSEL1 & TRGSEL5) */
    SCM_SW_TRIG_5 = 2U,  /*!< Generate software trigger5 to (TRGSEL1 & TRGSEL5) */
    SCM_SW_TRIG_6 = 4U,  /*!< Generate software trigger6 to (TRGSEL1 & TRGSEL5) */
    SCM_SW_TRIG_7 = 8U   /*!< Generate software trigger7 to (TRGSEL1 & TRGSEL5) */
} SCM_SwTrigxType;

/**
 * @brief Software trigger to TRGSEL0/TRGSEL1
 *
 */
typedef enum
{
    SCM_CCM0_STATUS_CPU_STOP_SYS_SLAVE  = SCM_CCM0_STATUS_CPU0_STOP_SYS_SLAVE_MASK, /*!< CCM0 FCG Stop Sys Slave Ack */
    SCM_CCM0_STATUS_CPU_STOP_MASTER     = SCM_CCM0_STATUS_CPU0_STOP_MASTER_MASK,    /*!< CCM0 FCG Stop Master Ack */
    SCM_CCM0_STATUS_CPU_STOP_SLOW_SLAVE = SCM_CCM0_STATUS_CPU0_STOP_SLOW_SLAVE_MASK,/*!< CCM0 FCG Stop Slow Slave Ack */
    SCM_CCM0_STATUS_CPU_STOP_BUS_SLAVE  = SCM_CCM0_STATUS_CPU0_STOP_BUS_SLAVE_MASK, /*!< CCM0 FCG Stop Bus Slave Ack */
    SCM_CCM0_STATUS_CPU_DEEPSLEEPING    = SCM_CCM0_STATUS_CPU0_DEEPSLEEPING_MASK,   /*!< CPU0 Sleepdeep */
    SCM_CCM0_STATUS_CPU_SLEEPING        = SCM_CCM0_STATUS_CPU0_SLEEPING_MASK        /*!< CPU0 Sleeping */
} SCM_CCMxStatusType;

/**
 * @brief SDDF channel clock output selection
 *
 */
typedef enum
{
    SCM_SDDF0_RESERVE = 0U,  /*!< Reserved */
    SCM_SDDF0_CLKO0,         /*!< SDDF0 CLKO0 */
    SCM_SDDF0_CLKO1,         /*!< SDDF0 CLKO1 */
    SCM_SDDF0_CLKO2          /*!< SDDF0 CLKO2 */
} SCM_SDDF_ClkOutSelType;

/**
 * @brief SDDF channel clock input selection
 *
 */
typedef enum
{
    SCM_SDDF0_CLK0_IND = 0U,  /*!< SDDF0 CLK0_IND */
    SCM_SDDF0_CLK1_IND,       /*!< SDDF0 CLK1_IND */
    SCM_SDDF0_CLK2_IND,       /*!< SDDF0 CLK2_IND */
    SCM_SDDF0_CLK3_IND        /*!< SDDF0 CLK3_IND */
} SCM_SDDF_ClkInSelType;

/**
 * @brief FLEXCAN routing selection
 *
 */
typedef enum
{
    SCM_FLEXCAN_9_9_OR_8_8 = 0U,  /*!< FLEXCAN 9 Rx/Tx pad from/to FLEXCAN 9 Rx/Tx pad or
                                       FLEXCAN 8 Rx/Tx pad from/to FLEXCAN 8 Rx/Tx pad */
    SCM_FLEXCAN_9_1_OR_8_0,       /*!< FLEXCAN 9 Rx/Tx pad from/to FLEXCAN 1 Rx/Tx pad or
                                       FLEXCAN 8 Rx/Tx pad from/to FLEXCAN 0 Rx/Tx pad */
    SCM_FLEXCAN_9_3_OR_8_2,       /*!< FLEXCAN 9 Rx/Tx pad from/to FLEXCAN 3 Rx/Tx pad or
                                       FLEXCAN 8 Rx/Tx pad from/to FLEXCAN 2 Rx/Tx pad */
    SCM_FLEXCAN_9_5_OR_8_4        /*!< FLEXCAN 9 Rx/Tx pad from/to FLEXCAN 5 Rx/Tx pad or
                                       FLEXCAN 8 Rx/Tx pad from/to FLEXCAN 4 Rx/Tx pad */
} SCM_FlexCanRouterType;

/**
 * @brief MSC routing selection
 *
 */
typedef enum
{
    SCM_MSC_FTU0_TO_MSC = 0U,   /*!< Select FTU0 ch do out[7:0] to MSCx ALTIN[31:24]/[23:16]/[15:8]/[7:0] */
    SCM_MSC_FTU1_TO_MSC,        /*!< Select FTU1 ch do out[7:0] to MSCx ALTIN[31:24]/[23:16]/[15:8]/[7:0] */
    SCM_MSC_FTU2_TO_MSC,        /*!< Select FTU2 ch do out[7:0] to MSCx ALTIN[31:24]/[23:16]/[15:8]/[7:0] */
    SCM_MSC_FTU3_TO_MSC,        /*!< Select FTU3 ch do out[7:0] to MSCx ALTIN[31:24]/[23:16]/[15:8]/[7:0] */
    SCM_MSC_FTU4_TO_MSC,        /*!< Select FTU4 ch do out[7:0] to MSCx ALTIN[31:24]/[23:16]/[15:8]/[7:0] */
    SCM_MSC_FTU5_TO_MSC,        /*!< Select FTU5 ch do out[7:0] to MSCx ALTIN[31:24]/[23:16]/[15:8]/[7:0] */
    SCM_MSC_FTU6_TO_MSC,        /*!< Select FTU6 ch do out[7:0] to MSCx ALTIN[31:24]/[23:16]/[15:8]/[7:0] */
    SCM_MSC_FTU7_TO_MSC         /*!< Select FTU7 ch do out[7:0] to MSCx ALTIN[31:24]/[23:16]/[15:8]/[7:0] */
} SCM_MSCAltInSelType;

/**
 * @brief ISM routing selection
 *
 */
typedef enum
{
    SCM_ISM_FTU0_TO_TRGSEL3 = 0U,  /*!< Select FTU0 ch do out[7:0] to TRGSEL3 source [89:82]/[81:74] */
    SCM_ISM_FTU1_TO_TRGSEL3,       /*!< Select FTU1 ch do out[7:0] to TRGSEL3 source [89:82]/[81:74] */
    SCM_ISM_FTU2_TO_TRGSEL3,       /*!< Select FTU2 ch do out[7:0] to TRGSEL3 source [89:82]/[81:74] */
    SCM_ISM_FTU3_TO_TRGSEL3,       /*!< Select FTU3 ch do out[7:0] to TRGSEL3 source [89:82]/[81:74] */
    SCM_ISM_FTU4_TO_TRGSEL3,       /*!< Select FTU4 ch do out[7:0] to TRGSEL3 source [89:82]/[81:74] */
    SCM_ISM_FTU5_TO_TRGSEL3,       /*!< Select FTU5 ch do out[7:0] to TRGSEL3 source [89:82]/[81:74] */
    SCM_ISM_FTU6_TO_TRGSEL3,       /*!< Select FTU6 ch do out[7:0] to TRGSEL3 source [89:82]/[81:74] */
    SCM_ISM_FTU7_TO_TRGSEL3        /*!< Select FTU7 ch do out[7:0] to TRGSEL3 source [89:82]/[81:74] */
} SCM_ISMRouterType;

/**
 * @brief Matrix status register 0 type
 *
 */
typedef enum
{
    SCM_MATRIX_STATUS0_MAM0_S5_M  = SCM_MATRIX_STATUS0_MAM0_S5_M_MASK,   /*!< MAM0_S5 slave ECC multi bit data error */
    SCM_MATRIX_STATUS0_MAM0_S5_AT = SCM_MATRIX_STATUS0_MAM0_S5_AT_MASK,  /*!< MAM0_S5 slave ECC attribute error */
    SCM_MATRIX_STATUS0_MAM0_S5_D  = SCM_MATRIX_STATUS0_MAM0_S5_D_MASK,   /*!< MAM0_S5 slave ECC single bit data error */
    SCM_MATRIX_STATUS0_MAM0_S5_A  = SCM_MATRIX_STATUS0_MAM0_S5_A_MASK,   /*!< MAM0_S5 slave ECC address error */
    SCM_MATRIX_STATUS0_MAM0_S4_M  = SCM_MATRIX_STATUS0_MAM0_S4_M_MASK,   /*!< MAM0_S4 slave ECC multi bit data error */
    SCM_MATRIX_STATUS0_MAM0_S4_AT = SCM_MATRIX_STATUS0_MAM0_S4_AT_MASK,  /*!< MAM0_S4 slave ECC attribute error */
    SCM_MATRIX_STATUS0_MAM0_S4_D  = SCM_MATRIX_STATUS0_MAM0_S4_D_MASK,   /*!< MAM0_S4 slave ECC single bit data error */
    SCM_MATRIX_STATUS0_MAM0_S4_A  = SCM_MATRIX_STATUS0_MAM0_S4_A_MASK,   /*!< MAM0_S4 slave ECC address error */
    SCM_MATRIX_STATUS0_MAM0_S3_M  = SCM_MATRIX_STATUS0_MAM0_S3_M_MASK,   /*!< MAM0_S3 slave ECC multi bit data error */
    SCM_MATRIX_STATUS0_MAM0_S3_AT = SCM_MATRIX_STATUS0_MAM0_S3_AT_MASK,  /*!< MAM0_S3 slave ECC attribute error */
    SCM_MATRIX_STATUS0_MAM0_S3_D  = SCM_MATRIX_STATUS0_MAM0_S3_D_MASK,   /*!< MAM0_S3 slave ECC single bit data error*/
    SCM_MATRIX_STATUS0_MAM0_S3_A  = SCM_MATRIX_STATUS0_MAM0_S3_A_MASK,   /*!< MAM0_S3 slave ECC address error */
    SCM_MATRIX_STATUS0_MAM0_S2_M  = SCM_MATRIX_STATUS0_MAM0_S2_M_MASK,   /*!< MAM0_S2 slave ECC multi bit data error*/
    SCM_MATRIX_STATUS0_MAM0_S2_AT = SCM_MATRIX_STATUS0_MAM0_S2_AT_MASK,  /*!< MAM0_S2 slave ECC attribute error */
    SCM_MATRIX_STATUS0_MAM0_S2_D  = SCM_MATRIX_STATUS0_MAM0_S2_D_MASK,   /*!< MAM0_S2 slave ECC single bit data error*/
    SCM_MATRIX_STATUS0_MAM0_S2_A  = SCM_MATRIX_STATUS0_MAM0_S2_A_MASK,   /*!< MAM0_S2 slave ECC address error */
    SCM_MATRIX_STATUS0_MAM0_S1_M  = SCM_MATRIX_STATUS0_MAM0_S1_M_MASK,   /*!< MAM0_S1 slave ECC multi bit data error */
    SCM_MATRIX_STATUS0_MAM0_S1_AT = SCM_MATRIX_STATUS0_MAM0_S1_AT_MASK,  /*!< MAM0_S1 slave ECC attribute error */
    SCM_MATRIX_STATUS0_MAM0_S1_D  = SCM_MATRIX_STATUS0_MAM0_S1_D_MASK,   /*!< MAM0_S1 slave ECC single bit data error */
    SCM_MATRIX_STATUS0_MAM0_S1_A  = SCM_MATRIX_STATUS0_MAM0_S1_A_MASK,   /*!< MAM0_S1 slave ECC address error */
    SCM_MATRIX_STATUS0_ROM_M      = SCM_MATRIX_STATUS0_ROM_M_MASK,       /*!< ROM array ECC multi bit data error */
    SCM_MATRIX_STATUS0_ROM_D      = SCM_MATRIX_STATUS0_ROM_D_MASK,       /*!< ROM array ECC single bit data error */
    SCM_MATRIX_STATUS0_ROM_A      = SCM_MATRIX_STATUS0_ROM_A_MASK        /*!< ROM array ECC address error */
} SCM_MatrixStatus0Type;

/**
 * @brief Matrix status register 1 type
 *
 */
typedef enum
{
    SCM_MATRIX_STATUS1_DMA0_M       = SCM_MATRIX_STATUS1_DMA0_M_MASK,       /*!< DMA0 master ECC multi bit data error */
    SCM_MATRIX_STATUS1_DMA0_D       = SCM_MATRIX_STATUS1_DMA0_D_MASK,       /*!< DMA0 master ECC single bit data error */
    SCM_MATRIX_STATUS1_DMA0_A       = SCM_MATRIX_STATUS1_DMA0_A_MASK,       /*!< DMA0 master ECC address error */
    SCM_MATRIX_STATUS1_HSM_M        = SCM_MATRIX_STATUS1_HSM_M_MASK,        /*!< HSM master ECC multi bit data error */
    SCM_MATRIX_STATUS1_HSM_D        = SCM_MATRIX_STATUS1_HSM_D_MASK,        /*!< HSM master ECC single bit data error */
    SCM_MATRIX_STATUS1_HSM_A        = SCM_MATRIX_STATUS1_HSM_A_MASK,        /*!< HSM master ECC address error */
    SCM_MATRIX_STATUS1_MAM0_S5_DS_M = SCM_MATRIX_STATUS1_MAM0_S5_DS_M_MASK, /*!< MAM0_S5 downsize ECC multi bit data error */
    SCM_MATRIX_STATUS1_MAM0_S5_DS_D = SCM_MATRIX_STATUS1_MAM0_S5_DS_D_MASK, /*!< MAM0_S5 downsize ECC single bit data error */
    SCM_MATRIX_STATUS1_MAM0_S5_DS_A = SCM_MATRIX_STATUS1_MAM0_S5_DS_A_MASK, /*!< MAM0_S5 downsize ECC address error */
    SCM_MATRIX_STATUS1_MAM0_S8_M    = SCM_MATRIX_STATUS1_MAM0_S8_M_MASK,    /*!< MAM0_S8 slave ECC multi bit data error */
    SCM_MATRIX_STATUS1_MAM0_S8_AT   = SCM_MATRIX_STATUS1_MAM0_S8_AT_MASK,   /*!< MAM0_S8 slave ECC attribute error */
    SCM_MATRIX_STATUS1_MAM0_S8_D    = SCM_MATRIX_STATUS1_MAM0_S8_D_MASK,    /*!< MAM0_S8 slave ECC single bit data error */
    SCM_MATRIX_STATUS1_MAM0_S8_A    = SCM_MATRIX_STATUS1_MAM0_S8_A_MASK,    /*!< MAM0_S8 slave ECC address error */
    SCM_MATRIX_STATUS1_MAM0_S7_M    = SCM_MATRIX_STATUS1_MAM0_S7_M_MASK,    /*!< MAM0_S7 slave ECC multi bit data error */
    SCM_MATRIX_STATUS1_MAM0_S7_AT   = SCM_MATRIX_STATUS1_MAM0_S7_AT_MASK,   /*!< MAM0_S7 slave ECC attribute error */
    SCM_MATRIX_STATUS1_MAM0_S7_D    = SCM_MATRIX_STATUS1_MAM0_S7_D_MASK,    /*!< MAM0_S7 slave ECC single bit data error */
    SCM_MATRIX_STATUS1_MAM0_S7_A    = SCM_MATRIX_STATUS1_MAM0_S7_A_MASK,    /*!< MAM0_S7 slave ECC address error */
    SCM_MATRIX_STATUS1_MAM0_S6_M    = SCM_MATRIX_STATUS1_MAM0_S6_M_MASK,    /*!< MAM0_S6 slave ECC multi bit data error */
    SCM_MATRIX_STATUS1_MAM0_S6_AT   = SCM_MATRIX_STATUS1_MAM0_S6_AT_MASK,   /*!< MAM0_S6 slave ECC attribute error */
    SCM_MATRIX_STATUS1_MAM0_S6_D    = SCM_MATRIX_STATUS1_MAM0_S6_D_MASK,    /*!< MAM0_S6 slave ECC single bit data error*/
    SCM_MATRIX_STATUS1_MAM0_S6_A    = SCM_MATRIX_STATUS1_MAM0_S6_A_MASK,    /*!< MAM0_S6 slave ECC address error */
} SCM_MatrixStatus1Type;

/**
 * @brief Matrix status register 2 type
 *
 */
typedef enum
{
    SCM_MATRIX_STATUS2_C0_OVERLAY   = SCM_MATRIX_STATUS2_C0_OVERLAY_MASK,     /*!< CPU0 AHB Overlay error */
    SCM_MATRIX_STATUS2_C0_LOCKSTEP  = SCM_MATRIX_STATUS2_C0_LOCKSTEP_MASK,     /*!< CPU0 Lockstep error */
    SCM_MATRIX_STATUS2_C0_DTCM1_A   = SCM_MATRIX_STATUS2_C0_DTCM1_A_MASK,     /*!< CPU0 DTCM1 ECC Address error */
    SCM_MATRIX_STATUS2_C0_DTCM1_M   = SCM_MATRIX_STATUS2_C0_DTCM1_M_MASK,     /*!< CPU0 DTCM1 ECC Multi Bit Data error */
    SCM_MATRIX_STATUS2_C0_DTCM1_S   = SCM_MATRIX_STATUS2_C0_DTCM1_S_MASK,     /*!< CPU0 DTCM1 ECC Single Bit Data error */
    SCM_MATRIX_STATUS2_C0_DTCM0_A   = SCM_MATRIX_STATUS2_C0_DTCM0_A_MASK,     /*!< CPU0 DTCM0 ECC Address error */
    SCM_MATRIX_STATUS2_C0_DTCM0_M   = SCM_MATRIX_STATUS2_C0_DTCM0_M_MASK,     /*!< CPU0 DTCM0 ECC Multi Bit Data error */
    SCM_MATRIX_STATUS2_C0_DTCM0_S   = SCM_MATRIX_STATUS2_C0_DTCM0_S_MASK,     /*!< CPU0 DTCM0 ECC Single Bit Data error */
    SCM_MATRIX_STATUS2_C0_ITCM_A    = SCM_MATRIX_STATUS2_C0_ITCM_A_MASK,     /*!< CPU0 ITCM ECC Address error */
    SCM_MATRIX_STATUS2_C0_ITCM_M    = SCM_MATRIX_STATUS2_C0_ITCM_M_MASK,     /*!< CPU0 ITCM ECC Multi Bit Data error */
    SCM_MATRIX_STATUS2_C0_ITCM_S    = SCM_MATRIX_STATUS2_C0_ITCM_S_MASK,     /*!< CPU0 ITCM ECC Single Bit Data error */
    SCM_MATRIX_STATUS2_C0_DCACHE    = SCM_MATRIX_STATUS2_C0_DCACHE_MASK,     /*!< CPU0 DCache Array error */
    SCM_MATRIX_STATUS2_C0_ICACHE    = SCM_MATRIX_STATUS2_C0_ICACHE_MASK,     /*!< CPU0 ICache Array error */
    SCM_MATRIX_STATUS2_C0_DTCM1_DEC = SCM_MATRIX_STATUS2_C0_DTCM1_DEC_MASK,  /*!< CPU0 DTCM1 decode monitor error */
    SCM_MATRIX_STATUS2_C0_DTCM0_DEC = SCM_MATRIX_STATUS2_C0_DTCM0_DEC_MASK,  /*!< CPU0 DTCM0 decode monitor error */
    SCM_MATRIX_STATUS2_C0_ITCM_DEC  = SCM_MATRIX_STATUS2_C0_ITCM_DEC_MASK,   /*!< CPU0 ITCM decode monitor error */
    SCM_MATRIX_STATUS2_C0_AHBP_F2S  = SCM_MATRIX_STATUS2_C0_AHBP_F2S_MASK,   /*!< CPU0 AHBP fast to slow monitor error */
    SCM_MATRIX_STATUS2_C0_AHBM_M    = SCM_MATRIX_STATUS2_C0_AHBM_M_MASK,     /*!< CPU0 AHBM master ECC multi bit data error */
    SCM_MATRIX_STATUS2_C0_AHBM_D    = SCM_MATRIX_STATUS2_C0_AHBM_D_MASK,     /*!< CPU0 AHBM master ECC single bit data error */
    SCM_MATRIX_STATUS2_C0_AHBM_A    = SCM_MATRIX_STATUS2_C0_AHBM_A_MASK,     /*!< CPU0 AHBM master ECC address error */
    SCM_MATRIX_STATUS2_C0_AHBS_M    = SCM_MATRIX_STATUS2_C0_AHBS_M_MASK,     /*!< CPU0 AHBS master ECC multi bit data error */
    SCM_MATRIX_STATUS2_C0_AHBS_D    = SCM_MATRIX_STATUS2_C0_AHBS_D_MASK,     /*!< CPU0 AHBS master ECC single bit data error */
    SCM_MATRIX_STATUS2_C0_AHBS_A    = SCM_MATRIX_STATUS2_C0_AHBS_A_MASK,     /*!< CPU0 AHBS master ECC address error */
    SCM_MATRIX_STATUS2_C0_AHBP_M    = SCM_MATRIX_STATUS2_C0_AHBP_M_MASK,     /*!< CPU0 AHBP master ECC multi bit data error */
    SCM_MATRIX_STATUS2_C0_AHBP_D    = SCM_MATRIX_STATUS2_C0_AHBP_D_MASK,     /*!< CPU0 AHBP master ECC single bit data error */
    SCM_MATRIX_STATUS2_C0_AHBP_A    = SCM_MATRIX_STATUS2_C0_AHBP_A_MASK,     /*!< CPU0 AHBP master ECC address error */
} SCM_MatrixStatus2Type;

/**
 * @brief Matrix status register 5 type
 *
 */
typedef enum
{

    SCM_MATRIX_STATUS5_DMA0_CFG_M    = SCM_MATRIX_STATUS5_DMA0_CFG_M_MASK,   /*!< DMA0_CFG ECC Multi Bit Data Error */
    SCM_MATRIX_STATUS5_DMA0_LOCKSTEP = SCM_MATRIX_STATUS5_DMA0_LOCKSTEP_MASK,/*!< DMA0 Lockstep Error */
    SCM_MATRIX_STATUS5_DMA0_CFG_S    = SCM_MATRIX_STATUS5_DMA0_CFG_S_MASK,   /*!< DMA0_CFG ECC Single Bit Data Error */
    SCM_MATRIX_STATUS5_DMA0_CFG_A    = SCM_MATRIX_STATUS5_DMA0_CFG_A_MASK,   /*!< DMA0_CFG ECC Address Error */
    SCM_MATRIX_STATUS5_EDC_HI        = SCM_MATRIX_STATUS5_EDC_HI_MASK,       /*!< Flash Control OCM EDC FCCU Alarm High Error */
    SCM_MATRIX_STATUS5_LINE_SBC      = SCM_MATRIX_STATUS5_LINE_SBC_MASK,     /*!< FCCU Alarm Linebuffer Self ECC Single Bit Error */
    SCM_MATRIX_STATUS5_LINE_MULTI    = SCM_MATRIX_STATUS5_LINE_MULTI_MASK,   /*!< FCCU Alarm Linebuffer Self ECC Multi Bit Error */
    SCM_MATRIX_STATUS5_ENC           = SCM_MATRIX_STATUS5_ENC_MASK,          /*!< FLASH Control OCM ENC FCCU Alarm Error */
    SCM_MATRIX_STATUS5_EDC           = SCM_MATRIX_STATUS5_EDC_MASK,          /*!< Flash Control OCM EDC FCCU Alarm Error  */
    SCM_MATRIX_STATUS5_P2_D_M        = SCM_MATRIX_STATUS5_P2_D_M_MASK,       /*!< Flash Control Port 2 Data Multi Error */
    SCM_MATRIX_STATUS5_P1_D_M        = SCM_MATRIX_STATUS5_P1_D_M_MASK,       /*!< Flash Control Port 1 Data Multi Error */
    SCM_MATRIX_STATUS5_P0_D_M        = SCM_MATRIX_STATUS5_P0_D_M_MASK,       /*!< Flash Control Port 0 Data Multi Error */
    SCM_MATRIX_STATUS5_P2_C_M        = SCM_MATRIX_STATUS5_P2_C_M_MASK,       /*!< Flash Control Port 2 Code Multi Error */
    SCM_MATRIX_STATUS5_P1_C_M        = SCM_MATRIX_STATUS5_P1_C_M_MASK,       /*!< Flash Control Port 1 Code Multi Error */
    SCM_MATRIX_STATUS5_P0_C_M        = SCM_MATRIX_STATUS5_P0_C_M_MASK,       /*!< Flash Control Port 0 Code Multi Error */
    SCM_MATRIX_STATUS5_P2_D_S        = SCM_MATRIX_STATUS5_P2_D_S_MASK,       /*!< Flash Control Port 2 Data Single Error */
    SCM_MATRIX_STATUS5_P1_D_S        = SCM_MATRIX_STATUS5_P1_D_S_MASK,       /*!< Flash Control Port 1 Data Single Error */
    SCM_MATRIX_STATUS5_P0_D_S        = SCM_MATRIX_STATUS5_P0_D_S_MASK,       /*!< Flash Control Port 0 Data Single Error */
    SCM_MATRIX_STATUS5_P2_C_S        = SCM_MATRIX_STATUS5_P2_C_S_MASK,       /*!< Flash Control Port 2 Code Single Error */
    SCM_MATRIX_STATUS5_P1_C_S        = SCM_MATRIX_STATUS5_P1_C_S_MASK,       /*!< Flash Control Port 1 Code Single Error */
    SCM_MATRIX_STATUS5_P0_C_S        = SCM_MATRIX_STATUS5_P0_C_S_MASK        /*!< Flash Control Port 0 Code Single Error */
} SCM_MatrixStatus5Type;

/**
 * @brief Matrix status register 6 type
 *
 */
typedef enum
{
    SCM_MATRIX_STATUS6_STALL_ERR      = SCM_MATRIX_STATUS6_STALL_ERR_MASK,      /*!< MAM Stall Error */
    SCM_MATRIX_STATUS6_MAM0_S8_DS     = SCM_MATRIX_STATUS6_MAM0_S8_DS_MASK,     /*!< MAM0_S8 Downsize Monitor Error */
    SCM_MATRIX_STATUS6_MAM0_S5_DS     = SCM_MATRIX_STATUS6_MAM0_S5_DS_MASK,     /*!< MAM0_S5 Downsize Monitor Error */
    SCM_MATRIX_STATUS6_MAM0_S5_S2F    = SCM_MATRIX_STATUS6_MAM0_S5_S2F_MASK,    /*!< MAM0_S5 Slow to Fast Gasket Monitor Error */
    SCM_MATRIX_STATUS6_SRAM1_DEC      = SCM_MATRIX_STATUS6_SRAM1_DEC_MASK,      /*!< SARM1 Decode Monitor Error */
    SCM_MATRIX_STATUS6_SRAM0_DEC      = SCM_MATRIX_STATUS6_SRAM0_DEC_MASK,      /*!< SARM0 Decode Monitor Error */
    SCM_MATRIX_STATUS6_AFCB1_MON      = SCM_MATRIX_STATUS6_AFCB1_MON_MASK,      /*!< AFCB0 Monitor Error  */
    SCM_MATRIX_STATUS6_AFCB0_MON      = SCM_MATRIX_STATUS6_AFCB0_MON_MASK,      /*!< AFCB1 Monitor Error */
    SCM_MATRIX_STATUS6_STCU_ST        = SCM_MATRIX_STATUS6_STCU_ST_MASK,        /*!< STCU Self Test Monitor Error */
    SCM_MATRIX_STATUS6_DCM_SCAN       = SCM_MATRIX_STATUS6_DCM_SCAN_MASK,       /*!< FCM Scan ECC Error */
    SCM_MATRIX_STATUS6_NON_USER       = SCM_MATRIX_STATUS6_NON_USER_MASK,       /*!< STCU Nonuser Error  */
    SCM_MATRIX_STATUS6_SCM_CRC        = SCM_MATRIX_STATUS6_SCM_CRC_MASK,        /*!< SCM CRC Error */
    SCM_MATRIX_STATUS6_SCG_CRC        = SCM_MATRIX_STATUS6_SCG_CRC_MASK,        /*!< SCG CRC Error */
    SCM_MATRIX_STATUS6_SRAM1_CTRL_MON = SCM_MATRIX_STATUS6_SRAM1_CTRL_MON_MASK, /*!< SRAM1 Control Monitor Error */
    SCM_MATRIX_STATUS6_SRAM0_CTRL_MON = SCM_MATRIX_STATUS6_SRAM0_CTRL_MON_MASK, /*!< SRAM0 Control Monitor Error */
    SCM_MATRIX_STATUS6_SRAM1_M        = SCM_MATRIX_STATUS6_SRAM1_M_MASK,        /*!< SRAM1 Multi Bit Data Error  */
    SCM_MATRIX_STATUS6_SRAM1_EDC      = SCM_MATRIX_STATUS6_SRAM1_EDC_MASK,      /*!< SRAM1 EDC Error */
    SCM_MATRIX_STATUS6_SRAM1_A        = SCM_MATRIX_STATUS6_SRAM1_A_MASK,        /*!< SRAM1 Address Error */
    SCM_MATRIX_STATUS6_SRAM1_S        = SCM_MATRIX_STATUS6_SRAM1_S_MASK,        /*!< SRAM1 Single Bit Data Error  */
    SCM_MATRIX_STATUS6_SAM0_M         = SCM_MATRIX_STATUS6_SAM0_M_MASK,         /*!< SRAM0 Multi Bit Data Error  */
    SCM_MATRIX_STATUS6_SRAM0_EDC      = SCM_MATRIX_STATUS6_SRAM0_EDC_MASK,      /*!< SRAM0 EDC Error  */
    SCM_MATRIX_STATUS6_SRAM0_A        = SCM_MATRIX_STATUS6_SRAM0_A_MASK,        /*!< SRAM0 Address Error  */
    SCM_MATRIX_STATUS6_SRAM0_S        = SCM_MATRIX_STATUS6_SRAM0_S_MASK         /*!< SRAM0 Single Bit Data Error */
} SCM_MatrixStatus6Type;

/**
 * @brief Matrix status register 7 type
 *
 */
typedef enum
{
    SCM_MATRIX_STATUS7_HSM_IRAM_M  = SCM_MATRIX_STATUS7_HSM_IRAM_M_MASK,    /*!< HSM IRAM Multi Bit Data Error */
    SCM_MATRIX_STATUS7_HSM_IRAM_S  = SCM_MATRIX_STATUS7_HSM_IRAM_S_MASK,    /*!< HSM IRAM Single Bit Data Error */
    SCM_MATRIX_STATUS7_HSM_DRAM_M  = SCM_MATRIX_STATUS7_HSM_DRAM_M_MASK,    /*!< HSM DRAM Multi Bit Data Error*/
    SCM_MATRIX_STATUS7_HSM_DRAM_S  = SCM_MATRIX_STATUS7_HSM_DRAM_S_MASK,    /*!< HSM DRAM Single Bit Data Error */
    SCM_MATRIX_STATUS7_HSM_WDOG    = SCM_MATRIX_STATUS7_HSM_WDOG_MASK,      /*!< HSM WDOG Request */
    SCM_MATRIX_STATUS7_MAM0_ERR    = SCM_MATRIX_STATUS7_MAM0_ERR_MASK,      /*!< MAM0 Timeout Error*/
    SCM_MATRIX_STATUS7_FOSC_ERR    = SCM_MATRIX_STATUS7_FOSC_ERR_MASK,      /*!< FOSC Loss of Clock Error*/
    SCM_MATRIX_STATUS7_PLL1_ERR    = SCM_MATRIX_STATUS7_PLL1_ERR_MASK,      /*!< PLL1 Loss of Clock Error*/
    SCM_MATRIX_STATUS7_PLL0_ERR    = SCM_MATRIX_STATUS7_PLL0_ERR_MASK       /*!< PLL0 Loss of Clock Error */
} SCM_MatrixStatus7Type;

/**
 * @brief Matrix ID status type
 *
 */
typedef enum
{
    SCM_MATRIX_ID_STATUS0_MAM0_S3_ID = 0U,  /*!< MAM0_S3 Slave ECC Error with Which Master Access */
    SCM_MATRIX_ID_STATUS0_MAM0_S4_ID = 1U,  /*!< MAM0_S4 Slave ECC Error with Which Master Access */
    SCM_MATRIX_ID_STATUS0_MAM0_S5_ID = 3U,  /*!< MAM0_S5 Slave ECC Error with Which Master Access */
    SCM_MATRIX_ID_STATUS0_SRAM0_ID   = 4U,  /*!< SARM0 ECC error with which master access */
    SCM_MATRIX_ID_STATUS0_SRAM1_ID   = 5U   /*!< SARM1 ECC Error with Which Master Access */
} SCM_MatrixIDStatusType;

/**
 * @brief Matrix ID status master type
 *
 */
typedef enum
{
    SCM_MATRIX_ID_STATUS0_MASTER_CPU0  = 0x0U,   /*!< SARM2 ECC error with CPU0 access */
    SCM_MATRIX_ID_STATUS0_MASTER_HSM   = 0x8U,   /*!< SARM1 ECC error with HSM access */
    SCM_MATRIX_ID_STATUS0_MASTER_DMA0  = 0xAU,   /*!< SARM0 ECC error with DMA0 access */
} SCM_MatrixIDStatusMasterType;

/**
 * @brief SCM SYSAP control Status2 Register Selection typ
 *
 */
typedef enum
{
    SCM_SYSAP_STATUS2_SEL_UID0       = 0U,  /*!< Select UID0 */
    SCM_SYSAP_STATUS2_SEL_UID1       = 1U,  /*!< Select UID1 */
    SCM_SYSAP_STATUS2_SEL_UID2       = 2U,  /*!< Select UID2 */
    SCM_SYSAP_STATUS2_SEL_UID3       = 3U,  /*!< Select UID3 */
    SCM_SYSAP_STATUS2_SEL_NVRVERSION = 4U   /*!< Select NVR version */
} SCM_SysAPStatus2SelType;

/**
 * @brief Mass erase type
 *
 */
typedef enum
{
    SCM_SECTORERASE_AS_MASSERASE = 0U,  /*!< Use sector erase for mass erase */
    SCM_CHIPERASE_AS_MASSERASE          /*!< Use chip erase for mass erase */
} SCM_SysApMassEraseType;

/**
 * @brief Cpu Type of forcing to halt
 *
 */
typedef enum
{
    SCM_DEBUG_CPU0 = 1U,  /*!< Force CPU0 to halt */
} SCM_SysApCpuDebugReqType;

/**
 * @brief Subsystem status type
 *
 */
typedef enum
{
    SCM_SUBSYS_STATUS_CHIP_IS_FT      = SCM_SUBSYS_STATUS_CHIP_IS_FT_MASK,      /*!< SEC dc lifecycle ft */
    SCM_SUBSYS_STATUS_CHIP_IS_VIRGIN  = SCM_SUBSYS_STATUS_CHIP_IS_VIRGIN_MASK,  /*!< SEC dc lifecycle virgin */
    SCM_SUBSYS_STATUS_TPU_CLK_EN      = SCM_SUBSYS_STATUS_TPU_CLK_EN_MASK,      /*!< TPU Clock Enable */
    SCM_SUBSYS_STATUS_HSM_RST         = SCM_SUBSYS_STATUS_HSM_RST_MASK,         /*!< Subsystem reset state */
    SCM_SUBSYS_STATUS_HSM_SYS_ERR_INT = SCM_SUBSYS_STATUS_HSM_SYS_ERR_INT_MASK, /*!< Subsystem error interrupt */
    SCM_SUBSYS_STATUS_WDG_RST         = SCM_SUBSYS_STATUS_WDG_RST_MASK,         /*!< Subsystem WDG generated reset flag */
    SCM_SUBSYS_STATUS_INIT_DONE       = SCM_SUBSYS_STATUS_INIT_DONE_MASK,       /*!< Subsystem Initial done flag */
    SCM_SUBSYS_STATUS_ISP_TOGGLE      = SCM_SUBSYS_STATUS_ISP_TOGGLE_MASK,      /*!< Subsystem ISP PIN toggle flag */
    SCM_SUBSYS_STATUS_SUBSYS_SLEEP    = SCM_SUBSYS_STATUS_HSM_SLEEP_MASK,       /*!< Subsystem sleep state */
    SCM_SUBSYS_STATUS_STOP_ACK        = SCM_SUBSYS_STATUS_STOP_ACK_MASK         /*!< Subsystem stop mode ack */
} SCM_SUBSYSStatusType;

/**
 * @brief Master halt request type
 *
 */
typedef enum
{
    SCM_MASTER_HALT_REQ_HSM_REQ  = 0U,  /*!< HSM Halt Request */
    SCM_MASTER_HALT_REQ_DMA0_REQ = 2U,  /*!< DMA0 Halt Request */
} SCM_HaltReqType;

/**
 * @brief Master halt request type
 *
 */
typedef enum
{
    SCM_MASTER_HALT_REQ_NOT_HALTED   = 0U,  /*!< Not Halted state */
    SCM_MASTER_HALT_REQ_HALTED_STATE = 1U,  /*!< Halted state */
} SCM_HaltReqAckType;


/********* Local inline function ************/
/**
 * @brief Get UIDL data(Unique identification for the chip. Loaded from NVR)
 *
 * @return return value
 */
LOCAL_INLINE uint32_t SCM_HWA_GetData_UIDL(void)
{
    return SCM->UIDL;
}

/**
 * @brief Get UIDML data(Unique identification for the chip. Loaded from NVR)
 *
 * @return return value
 */
LOCAL_INLINE uint32_t SCM_HWA_GetData_UIDML(void)
{
    return SCM->UIDML;
}

/**
 * @brief Get UIDMH data(Unique identification for the chip. Loaded from NVR)
 *
 * @return return value
 */
LOCAL_INLINE uint32_t SCM_HWA_GetData_UIDMH(void)
{
    return SCM->UIDMH;
}

/**
 * @brief Get UIDH data(Unique identification for the chip. Loaded from NVR)
 *
 * @return return value
 */
LOCAL_INLINE uint32_t SCM_HWA_GetData_UIDH(void)
{
    return SCM->UIDH;
}

/**
 * @brief Get Family Identification
 *
 * @return return value
 */
LOCAL_INLINE uint8_t SCM_HWA_GetData_FamilyID(void)
{
    return (uint8_t)((SCM->PARTID0 & (uint32_t)SCM_PARTID0_FAM_ID_MASK) >> (uint32_t)SCM_PARTID0_FAM_ID_SHIFT);
}

/**
 * @brief Get Revision Identification
 *
 * @return return value
 */
LOCAL_INLINE uint8_t SCM_HWA_GetData_RevID(void)
{
    return (uint8_t)((SCM->PARTID0 & (uint32_t)SCM_PARTID0_REVID_MASK));
}

/**
 * @brief Get CHIPCFG0 register status
 *
 * @return  return value
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_CHIPCFG0(void)
{
    return SCM->CHIPCFG0;
}

/**
 * @brief Get CPU lock step enable/disable status
 *
 * @return  1: CPU lock step is enabled
 *          0: CPU lock step is disabled
 */
LOCAL_INLINE uint32_t SCM_HWA_GetLockStepStatus_Cpu0(void)
{
    return ((SCM->CHIPCFG0 & (uint32_t)SCM_CHIPCFG0_CPU0_LOCKSTEP_EN_MASK)>>(uint32_t)SCM_CHIPCFG0_CPU0_LOCKSTEP_EN_SHIFT);
}

/**
 * @brief Get CANFD enable/disable status
 *
 * @return  1: CANFD is enabled
 *          0: CANFD is disabled
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_CANFD(void)
{
    return ((SCM->CHIPCFG0 & (uint32_t)SCM_CHIPCFG0_CAN_FD_MASK)>>(uint32_t)SCM_CHIPCFG0_CAN_FD_SHIFT);
}

/**
 * @brief Get device ID
 *
 * @return The device ID
 */
LOCAL_INLINE uint32_t SCM_HWA_GetData_DeviceID(void)
{
    return ((SCM->CHIPCFG1 & (uint32_t)SCM_CHIPCFG1_DEVICE_ID_MASK) >> (uint32_t)SCM_CHIPCFG1_DEVICE_ID_SHIFT);
}

/**
 * @brief Lock the CPU permission(WPB) in MAMECCEN0 register, and WPB cannot be written until a power-on reset
 *
 */
LOCAL_INLINE void SCM_HWA_MAMECCEN0_LockWritePermit(void)
{
    SCM->MAMECCEN0 |= (uint32_t)SCM_MAMECCEN0_WPB_LOCK_MASK;
}

/**
 * @brief Get the lock status of CPU permission(WPB) in MAMECCEN0 register
 *
 * @return 1: The WPB of MAMECCEN0 register is locked
 *         0: The WPB of MAMECCEN0 register is not locked
 */
LOCAL_INLINE uint32_t SCM_HWA_MAMECCEN0_GetWPBLockStatus(void)
{
    return (SCM->MAMECCEN0 & (uint32_t)SCM_MAMECCEN0_WPB_LOCK_MASK) >> SCM_MAMECCEN0_WPB_LOCK_SHIFT;
}

/**
 * @brief Get the CPU type of writing permission to MAMECCEN0 register
 *
 * @return SCM_WPB_CpuType The CPU which has the write permission
 */
LOCAL_INLINE SCM_WPB_CpuType SCM_HWA_MAMECCEN0_GetCpuWritePermit(void)
{
    uint32_t u32RegVal = ((SCM->MAMECCEN0 & (uint32_t)SCM_MAMECCEN0_WPB_MASK) >> SCM_MAMECCEN0_WPB_SHIFT);
    return (SCM_WPB_CpuType)u32RegVal;
}

/**
 * @brief Set CPU to control the MAMECCEN0 register
 *
 * @param eCpuType CPU allowed to control peripheral
 */
LOCAL_INLINE void SCM_HWA_MAMECCEN0_SetCpuWritePermit(SCM_WPB_CpuType eCpuType)
{
    SCM->MAMECCEN0 = ((SCM->MAMECCEN0 & (~(uint32_t)SCM_MAMECCEN0_WPB_MASK)) | SCM_MAMECCEN0_WPB(eCpuType));
}

/**
 * @brief Get the value of MAMECCEN0 register
 * @return register value
 */
LOCAL_INLINE uint32_t SCM_HWA_MAMECCEN0_GetValue(void)
{
    return SCM->MAMECCEN0;
}

/**
 * @brief Set the value of MAMECCEN0 register
 * @param u32Value value to be set, the value must be the or value of SCM_MAMEccCtrlGrp0Type
 */
LOCAL_INLINE void SCM_HWA_MAMECCEN0_SetValue(uint32_t u32Value)
{
    SCM->MAMECCEN0 = u32Value & 0x03FFCFCFu;
}

/**
 * @brief Set the MAMECCEN0 ECC enable
 * @param eMamEccType the MAM peripheral to enable ECC
 * @param eEnable the ECC enable mode
 */
LOCAL_INLINE void SCM_HWA_MAMECCEN0_Ctrl(SCM_MAMEccCtrlGrp0Type eMamEccType, SCM_EccEnModeType eEnable)
{

    SCM->MAMECCEN0 = (SCM->MAMECCEN0 & (~(SCM_MAMECCEN0_ECC_MASK << ((uint32_t)eMamEccType * SCM_MAMECCEN0_ECC_WIDTH)))) |
            SCM_MAMECCEN0_ECC(eEnable) << ((uint32_t)eMamEccType * SCM_MAMECCEN0_ECC_WIDTH);
}

/**
 * @brief Lock the CPU permission(WPB) in MAMECCEN1 register, and WPB cannot be written until a power-on reset
 *
 */
LOCAL_INLINE void SCM_HWA_MAMECCEN1_LockWritePermit(void)
{
    SCM->MAMECCEN1 |= (uint32_t)SCM_MAMECCEN1_WPB_LOCK_MASK;
}

/**
 * @brief Get the lock status of CPU permission(WPB) in MAMECCEN1 register
 *
 * @return 1: The WPB of MAMECCEN1 register is locked
 *         0: The WPB of MAMECCEN1 register is not locked
 */
LOCAL_INLINE uint32_t SCM_HWA_MAMECCEN1_GetWPBLockStatus(void)
{
    return (SCM->MAMECCEN1 & (uint32_t)SCM_MAMECCEN1_WPB_LOCK_MASK) >> SCM_MAMECCEN1_WPB_LOCK_SHIFT;
}

/**
 * @brief Get the CPU type of writing permission to MAMECCEN1 register
 *
 * @return SCM_WPB_CpuType The CPU which has the write permission
 */
LOCAL_INLINE SCM_WPB_CpuType SCM_HWA_MAMECCEN1_GetCpuWritePermit(void)
{
    uint32_t u32RegVal = ((SCM->MAMECCEN1 & (uint32_t)SCM_MAMECCEN1_WPB_MASK) >> SCM_MAMECCEN1_WPB_SHIFT);
    return (SCM_WPB_CpuType)u32RegVal;
}

/**
 * @brief Set CPU to control the MAMECCEN1 register
 *
 * @param eCpuType CPU allowed to control peripheral
 */
LOCAL_INLINE void SCM_HWA_MAMECCEN1_SetCpuWritePermit(SCM_WPB_CpuType eCpuType)
{
    SCM->MAMECCEN1 = ((SCM->MAMECCEN1 & (~(uint32_t)SCM_MAMECCEN1_WPB_MASK)) | SCM_MAMECCEN1_WPB(eCpuType));
}

/**
 * @brief Get the value of MAMECCEN1 register
 * @return register value
 */
LOCAL_INLINE uint32_t SCM_HWA_MAMECCEN1_GetValue(void)
{
    return SCM->MAMECCEN1;
}

/**
 * @brief Set the value of MAMECCEN1 register
 * @param u32Value value to be set
 */
LOCAL_INLINE void SCM_HWA_MAMECCEN1_SetValue(uint32_t u32Value)
{
    SCM->MAMECCEN1 = u32Value & 0x00003D33u;
}

/**
 * @brief Set the MAMECCEN1 ECC enable
 * @param eMamEccType the MAM peripheral to enable ECC
 * @param eEnable the ECC enable mode
 */
LOCAL_INLINE void SCM_HWA_MAMECCEN1_Ctrl(SCM_MAMEccCtrlGrp1Type eMamEccType, SCM_EccEnModeType eEnable)
{
    if(SCM_DMA0_CFG_ECC == eMamEccType)
    {
        SCM->MAMECCEN1 = (SCM->MAMECCEN1 & (~(SCM_MAMECCEN1_DMA0_CFG_ECC_MASK))) |
                         SCM_MAMECCEN1_DMA0_CFG_ECC(eEnable);
    }
    else
    {
        SCM->MAMECCEN1 = (SCM->MAMECCEN1 & (~(SCM_MAMECCEN1_ECC_MASK << ((uint32_t)eMamEccType * SCM_MAMECCEN1_ECC_WIDTH)))) |
                         SCM_MAMECCEN1_ECC(eEnable) << ((uint32_t)eMamEccType * SCM_MAMECCEN1_ECC_WIDTH);
    }
}

/**
 * @brief Lock the CPU permission(WPB) in CPU0ECCEN register, and WPB cannot be written until a power-on reset
 *
 */
LOCAL_INLINE void SCM_HWA_CPU0ECCEN_LockWritePermit(void)
{
    SCM->CPU0ECCEN |= (uint32_t)SCM_CPU0ECCEN_WPB_LOCK_MASK;
}

/**
 * @brief Get the lock status of CPU permission(WPB) in CPU0ECCEN register
 *
 * @return 1: The WPB of CPU0ECCEN register is locked
 *         0: The WPB of CPU0ECCEN register is not locked
 */
LOCAL_INLINE uint32_t SCM_HWA_CPU0ECCEN_GetWPBLockStatus(void)
{
    return (SCM->CPU0ECCEN & (uint32_t)SCM_CPU0ECCEN_WPB_LOCK_MASK) >> SCM_CPU0ECCEN_WPB_LOCK_SHIFT;
}

/**
 * @brief Get the CPU type of writing permission to CPU0ECCEN register
 *
 * @return SCM_WPB_CpuType The CPU which has the write permission
 */
LOCAL_INLINE SCM_WPB_CpuType SCM_HWA_CPU0ECCEN_GetCpuWritePermit(void)
{
    uint32_t u32RegVal = ((SCM->CPU0ECCEN & (uint32_t)SCM_CPU0ECCEN_WPB_MASK) >> SCM_CPU0ECCEN_WPB_SHIFT);
    return (SCM_WPB_CpuType)u32RegVal;
}

/**
 * @brief Set CPU to control the CPU0ECCEN register
 *
 * @param eCpuType CPU allowed to control peripheral
 */
LOCAL_INLINE void SCM_HWA_CPU0ECCEN_SetCpuWritePermit(SCM_WPB_CpuType eCpuType)
{
    uint32_t u32RegVal = SCM->CPU0ECCEN;
    SCM->CPU0ECCEN = ((u32RegVal & (~(uint32_t)SCM_CPU0ECCEN_WPB_MASK)) | SCM_CPU0ECCEN_WPB(eCpuType));
}

/**
 * @brief Get the value of CPU0ECCEN register
 * @return register value
 */
LOCAL_INLINE uint32_t SCM_HWA_CPU0ECCEN_GetValue(void)
{
    return SCM->CPU0ECCEN;
}

/**
 * @brief Set the value of CPU0ECCEN register
 * @param u32Value value to be set
 */
LOCAL_INLINE void SCM_HWA_CPU0ECCEN_SetValue(uint32_t u32Value)
{
    SCM->CPU0ECCEN = u32Value & 0x00000FFFu;
}

/**
 * @brief Set the peripheral ECC enable of CPU0
 * @param eCpuEccType the peripheral to enable ECC
 * @param eEnable the ECC enable mode
 */
LOCAL_INLINE void SCM_HWA_CPU0ECCEN_Ctrl(SCM_CPUEccCtrlType eCpuEccType, SCM_EccEnModeType eEnable)
{
    SCM->CPU0ECCEN = (SCM->CPU0ECCEN & (~(SCM_CPU0ECCEN_CPU0_ECC_MASK << ((uint32_t)eCpuEccType * SCM_CPU0ECCEN_CPU0_ECC_WIDTH)))) |
                     SCM_CPU0ECCEN_CPU0_ECC(eEnable) << ((uint32_t)eCpuEccType * SCM_CPU0ECCEN_CPU0_ECC_WIDTH);
}

/**
 * @brief Get SRAM1 ECC Detect Control
 * @return 0: Disable EDC error when SRAM1 Multi Bit ECC Error Exist
 *         1: Only Enable EDC error when SRAM1 Multi Bit ECC Error Exist
 */
LOCAL_INLINE uint32_t SCM_HWA_SRAM1_EDCErrorEnStatus(void)
{
    return (SCM->SRAM_EDC_CTRL & SCM_SRAM_EDC_CTRL_SRAM1_EDC_MASK) >> SCM_SRAM_EDC_CTRL_SRAM1_EDC_SHIFT;
}

/**
 * @brief Set SRAM1 ECC Detect Control
 * @param bEnable true: Disable EDC error when SRAM1 Multi Bit ECC Error Exist
 *                false: Only Enable EDC error when SRAM1 Multi Bit ECC Error Exist
 */
LOCAL_INLINE void SCM_HWA_SRAM1_EDCErrorEnable(bool bEnable)
{
    SCM->SRAM_EDC_CTRL = (SCM->SRAM_EDC_CTRL & (~SCM_SRAM_EDC_CTRL_SRAM1_EDC_MASK)) | SCM_SRAM_EDC_CTRL_SRAM1_EDC(bEnable);
}

/**
 * @brief Get SRAM0 ECC Detect Control
 * @return 0: Disable EDC error when SRAM0 Multi Bit ECC Error Exist
 *         1: Only Enable EDC error when SRAM0 Multi Bit ECC Error Exist
 */
LOCAL_INLINE uint32_t SCM_HWA_SRAM0_EDCErrorEnStatus(void)
{
    return (SCM->SRAM_EDC_CTRL & SCM_SRAM_EDC_CTRL_SRAM0_EDC_MASK) >> SCM_SRAM_EDC_CTRL_SRAM0_EDC_SHIFT;
}

/**
 * @brief Set SRAM0 ECC Detect Control
 * @param bEnable false: Disable EDC error when SRAM0 Multi Bit ECC Error Exist
 *                true: Only Enable EDC error when SRAM0 Multi Bit ECC Error Exist
 */
LOCAL_INLINE void SCM_HWA_SRAM0_EDCErrorEnable(bool bEnable)
{
    SCM->SRAM_EDC_CTRL = (SCM->SRAM_EDC_CTRL & (~SCM_SRAM_EDC_CTRL_SRAM0_EDC_MASK)) | SCM_SRAM_EDC_CTRL_SRAM0_EDC(bEnable);
}

/**
 * @brief Lock ROM Configuration Register
 *
 */
LOCAL_INLINE void SCM_HWA_LockROMCFG(void)
{
    SCM->ROMCFG |= (uint32_t)SCM_ROMCFG_LOCK_MASK;
}

/**
 * @brief Get ROMCFG register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t SCM_HWA_ROMCFG_GetLockStatus(void)
{
    return(SCM->ROMCFG & (uint32_t)SCM_ROMCFG_LOCK_MASK) >> SCM_ROMCFG_LOCK_SHIFT;
}

/**
 * @brief Get HSM ROM Power Gating Enable status
 * @return 0: Not Power Gating
 *         1: Power Gating
 */
LOCAL_INLINE uint32_t SCM_HWA_GetHsmRomPowerGatingEnStatus(void)
{
    return (SCM->ROMCFG & SCM_ROMCFG_HSMROM_PGEN_MASK) >> SCM_ROMCFG_HSMROM_PGEN_SHIFT;
}

/**
 * @brief Set HSM ROM Power Gating Enable
 * @param bEnable false: Not Power Gating
 *                true: Power Gating
 */
LOCAL_INLINE void SCM_HWA_HsmRomPowerGatingEnable(bool bEnable)
{
    SCM->ROMCFG = (SCM->ROMCFG & (~SCM_ROMCFG_HSMROM_PGEN_MASK)) | SCM_ROMCFG_HSMROM_PGEN(bEnable);
}

/**
 * @brief Get System ROM Power Gating Enable status
 * @return 0: Not Power Gating
 *         1: Power Gating
 */
LOCAL_INLINE uint32_t SCM_HWA_GetSysRomPowerGatingEnStatus(void)
{
    return (SCM->ROMCFG & SCM_ROMCFG_SYSROM_PGEN_MASK) >> SCM_ROMCFG_SYSROM_PGEN_SHIFT;
}

/**
 * @brief Set System ROM Power Gating Enable
 * @param bEnable false: Not Power Gating
 *                true: Power Gating
 */
LOCAL_INLINE void SCM_HWA_SysRomPowerGatingEnable(bool bEnable)
{
    SCM->ROMCFG = (SCM->ROMCFG & (~SCM_ROMCFG_SYSROM_PGEN_MASK)) | SCM_ROMCFG_SYSROM_PGEN(bEnable);
}

/**
 * @brief Use FCSPI5 to monitor other FCSPI's transmit interface
 *
 * @param eSPIxType SPI type
 */
LOCAL_INLINE void SCM_HWA_FCSPI5MonSPIx(SCM_FCSPIxType eSPIxType)
{
    uint32_t u32RegVal = SCM->FCSPI_ROUTING;
    SCM->FCSPI_ROUTING = ((u32RegVal & (~(uint32_t)SCM_FCSPI_ROUTING_SPI5_ROUTER_MASK)) | SCM_FCSPI_ROUTING_SPI5_ROUTER(eSPIxType));
}

/**
 * @brief Use FCSPI4 to monitor other FCSPI's transmit interface
 *
 * @param eSPIxType SPI type
 */
LOCAL_INLINE void SCM_HWA_FCSPI4MonSPIx(SCM_FCSPIxType eSPIxType)
{
    uint32_t u32RegVal = SCM->FCSPI_ROUTING;
    SCM->FCSPI_ROUTING = ((u32RegVal & (~(uint32_t)SCM_FCSPI_ROUTING_SPI4_ROUTER_MASK)) | SCM_FCSPI_ROUTING_SPI4_ROUTER(eSPIxType));
}

/**
 * @brief Use FCSPI3 to monitor other FCSPI's transmit interface
 *
 * @param eSPIxType SPI type
 */
LOCAL_INLINE void SCM_HWA_FCSPI3MonSPIx(SCM_FCSPIxType eSPIxType)
{
    uint32_t u32RegVal = SCM->FCSPI_ROUTING;
    SCM->FCSPI_ROUTING = ((u32RegVal & (~(uint32_t)SCM_FCSPI_ROUTING_SPI3_ROUTER_MASK)) | SCM_FCSPI_ROUTING_SPI3_ROUTER(eSPIxType));
}

/**
 * @brief Use FCSPI2 to monitor other FCSPI's transmit interface
 *
 * @param eSPIxType SPI type
 */
LOCAL_INLINE void SCM_HWA_FCSPI2MonSPIx(SCM_FCSPIxType eSPIxType)
{
    uint32_t u32RegVal = SCM->FCSPI_ROUTING;
    SCM->FCSPI_ROUTING = ((u32RegVal & (~(uint32_t)SCM_FCSPI_ROUTING_SPI2_ROUTER_MASK)) | SCM_FCSPI_ROUTING_SPI2_ROUTER(eSPIxType));
}

/**
 * @brief Use FCSPI1 to monitor other FCSPI's transmit interface
 *
 * @param eSPIxType SPI type
 */
LOCAL_INLINE void SCM_HWA_FCSPI1MonSPIx(SCM_FCSPIxType eSPIxType)
{
    uint32_t u32RegVal = SCM->FCSPI_ROUTING;
    SCM->FCSPI_ROUTING = ((u32RegVal & (~(uint32_t)SCM_FCSPI_ROUTING_SPI1_ROUTER_MASK)) | SCM_FCSPI_ROUTING_SPI1_ROUTER(eSPIxType));
}

/**
 * @brief Use FCSPI0 to monitor other FCSPI's transmit interface
 *
 * @param eSPIxType SPI type
 */
LOCAL_INLINE void SCM_HWA_FCSPI0MonSPIx(SCM_FCSPIxType eSPIxType)
{
    uint32_t u32RegVal = SCM->FCSPI_ROUTING;
    SCM->FCSPI_ROUTING = ((u32RegVal & (~(uint32_t)SCM_FCSPI_ROUTING_SPI0_ROUTER_MASK)) | SCM_FCSPI_ROUTING_SPI0_ROUTER(eSPIxType));
}

/**
 * @brief Use FCUART7 to monitor other FCSPI's transmit interface
 *
 * @param eUartxType Uart type
 */
LOCAL_INLINE void SCM_HWA_FCUART7MonUARTx(SCM_MON_FCUARTxType eUartxType)
{
    uint32_t u32RegVal = SCM->FCUART_ROUTING0;
    SCM->FCUART_ROUTING0 = ((u32RegVal & (~(uint32_t)SCM_FCUART_ROUTING0_UART7_ROUTER_MASK)) | SCM_FCUART_ROUTING0_UART7_ROUTER(eUartxType));
}

/**
 * @brief Use FCUART6 to monitor other FCSPI's transmit interface
 *
 * @param eUartxType Uart type
 */
LOCAL_INLINE void SCM_HWA_FCUART6MonUARTx(SCM_MON_FCUARTxType eUartxType)
{
    uint32_t u32RegVal = SCM->FCUART_ROUTING0;
    SCM->FCUART_ROUTING0 = ((u32RegVal & (~(uint32_t)SCM_FCUART_ROUTING0_UART6_ROUTER_MASK)) | SCM_FCUART_ROUTING0_UART6_ROUTER(eUartxType));
}

/**
 * @brief Use FCUART5 to monitor other FCSPI's transmit interface
 *
 * @param eUartxType Uart type
 */
LOCAL_INLINE void SCM_HWA_FCUART5MonUARTx(SCM_MON_FCUARTxType eUartxType)
{
    uint32_t u32RegVal = SCM->FCUART_ROUTING0;
    SCM->FCUART_ROUTING0 = ((u32RegVal & (~(uint32_t)SCM_FCUART_ROUTING0_UART5_ROUTER_MASK)) | SCM_FCUART_ROUTING0_UART5_ROUTER(eUartxType));
}

/**
 * @brief Use FCUART4 to monitor other FCSPI's transmit interface
 *
 * @param eUartxType Uart type
 */
LOCAL_INLINE void SCM_HWA_FCUART4MonUARTx(SCM_MON_FCUARTxType eUartxType)
{
    uint32_t u32RegVal = SCM->FCUART_ROUTING0;
    SCM->FCUART_ROUTING0 = ((u32RegVal & (~(uint32_t)SCM_FCUART_ROUTING0_UART4_ROUTER_MASK)) | SCM_FCUART_ROUTING0_UART4_ROUTER(eUartxType));
}

/**
 * @brief Use FCUART3 to monitor other FCSPI's transmit interface
 *
 * @param eUartxType Uart type
 */
LOCAL_INLINE void SCM_HWA_FCUART3MonUARTx(SCM_MON_FCUARTxType eUartxType)
{
    uint32_t u32RegVal = SCM->FCUART_ROUTING0;
    SCM->FCUART_ROUTING0 = ((u32RegVal & (~(uint32_t)SCM_FCUART_ROUTING0_UART3_ROUTER_MASK)) | SCM_FCUART_ROUTING0_UART3_ROUTER(eUartxType));
}

/**
 * @brief Use FCUART2 to monitor other FCSPI's transmit interface
 *
 * @param eUartxType Uart type
 */
LOCAL_INLINE void SCM_HWA_FCUART2MonUARTx(SCM_MON_FCUARTxType eUartxType)
{
    uint32_t u32RegVal = SCM->FCUART_ROUTING0;
    SCM->FCUART_ROUTING0 = ((u32RegVal & (~(uint32_t)SCM_FCUART_ROUTING0_UART2_ROUTER_MASK)) | SCM_FCUART_ROUTING0_UART2_ROUTER(eUartxType));
}

/**
 * @brief Use FCUART1 to monitor other FCSPI's transmit interface
 *
 * @param eUartxType Uart type
 */
LOCAL_INLINE void SCM_HWA_FCUART1MonUARTx(SCM_MON_FCUARTxType eUartxType)
{
    uint32_t u32RegVal = SCM->FCUART_ROUTING0;
    SCM->FCUART_ROUTING0 = ((u32RegVal & (~(uint32_t)SCM_FCUART_ROUTING0_UART1_ROUTER_MASK)) | SCM_FCUART_ROUTING0_UART1_ROUTER(eUartxType));
}

/**
 * @brief Use FCUART0 to monitor other FCSPI's transmit interface
 *
 * @param eUartxType Uart type
 */
LOCAL_INLINE void SCM_HWA_FCUART0MonUARTx(SCM_MON_FCUARTxType eUartxType)
{
    uint32_t u32RegVal = SCM->FCUART_ROUTING0;
    SCM->FCUART_ROUTING0 = ((u32RegVal & (~(uint32_t)SCM_FCUART_ROUTING0_UART0_ROUTER_MASK)) | SCM_FCUART_ROUTING0_UART0_ROUTER(eUartxType));
}

/**
 * @brief Set PTIMER Loop Mode selection
 *
 * @param ePTimerLoopMode  PTIMER Loop Mode
 */
LOCAL_INLINE void SCM_HWA_PTimerLoopModeSel(SCM_PTimerLMSelType ePTimerLoopMode)
{
    uint32_t u32RegVal = SCM->ADC_ROUTING;
    SCM->ADC_ROUTING = ((u32RegVal &
                         (~(uint32_t)(SCM_ADC_ROUTING_PTIMER01LOOP_MASK |
                                      SCM_ADC_ROUTING_PTIMER01LOOP_1_MASK |
                                      SCM_ADC_ROUTING_PTIMER01LOOP_2_MASK))) |
                       SCM_ADC_ROUTING_PTIMER01LOOP((uint32_t)ePTimerLoopMode >> 2U)) |
                       SCM_ADC_ROUTING_PTIMER01LOOP_1((uint32_t)ePTimerLoopMode >> 1U) |
                       SCM_ADC_ROUTING_PTIMER01LOOP_2((uint32_t)ePTimerLoopMode);
}

/**
 * @brief Set ADC1 Trigger Source selection
 *
 * @param eAdcTriggerSrc  ADC1 Trigger Source
 */
LOCAL_INLINE void SCM_HWA_ADC1TriggerSrcSel(SCM_AdcTriggerSrcType eAdcTriggerSrc)
{
    uint32_t u32RegVal = SCM->ADC_ROUTING;
    SCM->ADC_ROUTING = ((u32RegVal & (~(uint32_t)SCM_ADC_ROUTING_ADC1_TRGSEL_MASK)) |
                        SCM_ADC_ROUTING_ADC1_TRGSEL(eAdcTriggerSrc));
}

/**
 * @brief Set ADC1 Pre-trigger Source selection
 *
 * @param eAdcTriggerSrc  ADC1 Pre-trigger Source
 */
LOCAL_INLINE void SCM_HWA_ADC1PreTriggerSrcSel(SCM_AdcPreTriggerSrcType eAdcPreTriggerSrc)
{
    uint32_t u32RegVal = SCM->ADC_ROUTING;
    SCM->ADC_ROUTING = ((u32RegVal & (~(uint32_t)SCM_ADC_ROUTING_ADC1_PRETRGSEL_MASK)) |
                        SCM_ADC_ROUTING_ADC1_PRETRGSEL(eAdcPreTriggerSrc));
}

/**
 * @brief Set ADC1 SCM Pre-trigger Source selection
 *
 * @param eScmSoftwarePreTriggerSrc  ADC1 SCM software Pre-trigger Source
 */
LOCAL_INLINE void SCM_HWA_ADC1ScmSoftWarePreTriggerSrcSel(SCM_SoftwarePreTriggerType eScmSoftwarePreTriggerSrc)
{
    uint32_t u32RegVal = SCM->ADC_ROUTING;
    SCM->ADC_ROUTING = ((u32RegVal & (~(uint32_t)SCM_ADC_ROUTING_ADC1_SWPRETRG_MASK)) |
                        SCM_ADC_ROUTING_ADC1_SWPRETRG(eScmSoftwarePreTriggerSrc));
}

/**
 * @brief Set ADC0 Trigger Source selection
 *
 * @param eAdcTriggerSrc  ADC0 Trigger Source
 */
LOCAL_INLINE void SCM_HWA_ADC0TriggerSrcSel(SCM_AdcTriggerSrcType eAdcTriggerSrc)
{
    uint32_t u32RegVal = SCM->ADC_ROUTING;
    SCM->ADC_ROUTING = ((u32RegVal & (~(uint32_t)SCM_ADC_ROUTING_ADC0_TRGSEL_MASK)) |
                        SCM_ADC_ROUTING_ADC0_TRGSEL(eAdcTriggerSrc));
}

/**
 * @brief Set ADC0 Pre-trigger Source selection
 *
 * @param eAdcTriggerSrc  ADC0 Pre-trigger Source
 */
LOCAL_INLINE void SCM_HWA_ADC0PreTriggerSrcSel(SCM_AdcPreTriggerSrcType eAdcPreTriggerSrc)
{
    uint32_t u32RegVal = SCM->ADC_ROUTING;
    SCM->ADC_ROUTING = ((u32RegVal & (~(uint32_t)SCM_ADC_ROUTING_ADC0_PRETRGSEL_MASK)) |
                        SCM_ADC_ROUTING_ADC0_PRETRGSEL(eAdcPreTriggerSrc));
}

/**
 * @brief Set ADC0 SCM Pre-trigger Source selection
 *
 * @param eScmSoftwarePreTriggerSrc  ADC0 SCM software Pre-trigger Source
 */
LOCAL_INLINE void SCM_HWA_ADC0ScmSoftWarePreTriggerSrcSel(SCM_SoftwarePreTriggerType eScmSoftwarePreTriggerSrc)
{
    uint32_t u32RegVal = SCM->ADC_ROUTING;
    SCM->ADC_ROUTING = ((u32RegVal & (~(uint32_t)SCM_ADC_ROUTING_ADC0_SWPRETRG_MASK)) |
                        SCM_ADC_ROUTING_ADC0_SWPRETRG(eScmSoftwarePreTriggerSrc));
}

/**
 * @brief Select the FTU3 output source, should be ignored when FTU3 in input mode
 *
 * @param eOutSelType  FTU3 output source selection type
 */
LOCAL_INLINE void SCM_HWA_SetOutSel_FTU3(SCM_FTU_OutputSelType eOutSelType)
{
    uint32_t u32RegVal = SCM->FTU_ROUTING;
    SCM->FTU_ROUTING = ((u32RegVal & (~(uint32_t)SCM_FTU_ROUTING_FTU3_OUTSEL_MASK)) | SCM_FTU_ROUTING_FTU3_OUTSEL(eOutSelType));
}

/**
 * @brief Select the FTU0 output source, should be ignored when FTU0 in input mode
 *
 * @param eOutSelType  FTU0 output source selection type
 */
LOCAL_INLINE void SCM_HWA_SetOutSel_FTU0(SCM_FTU_OutputSelType eOutSelType)
{
    uint32_t u32RegVal = SCM->FTU_ROUTING;
    SCM->FTU_ROUTING = ((u32RegVal & (~(uint32_t)SCM_FTU_ROUTING_FTU0_OUTSEL_MASK)) | SCM_FTU_ROUTING_FTU0_OUTSEL(eOutSelType));
}

/**
 * @brief Selects FTU2 CH1 input
 *
 * @param eInputSelType  FTU2 CH1 input selection type
 */
LOCAL_INLINE void SCM_HWA_SetInSel_FTU2_CH1(SCM_FTU2_CH1_InputSelType eInputSelType)
{
    uint32_t u32RegVal = SCM->FTU_ROUTING;
    SCM->FTU_ROUTING = ((u32RegVal & (~(uint32_t)SCM_FTU_ROUTING_FTU2_CH1SEL_MASK)) | SCM_FTU_ROUTING_FTU2_CH1SEL(eInputSelType));
}

/**
 * @brief Selects FTU2 CH0 input
 *
 * @param eInputSelType  FTU2 CH0 input selection type
 */
LOCAL_INLINE void SCM_SetInSel_FTU2_CH0(SCM_FTUx_CH0_InputSelType eInputSelType)
{
    uint32_t u32RegVal = SCM->FTU_ROUTING;
    SCM->FTU_ROUTING = ((u32RegVal & (~(uint32_t)SCM_FTU_ROUTING_FTU2_CH0SEL_MASK)) | SCM_FTU_ROUTING_FTU2_CH0SEL(eInputSelType));
}

/**
 * @brief Selects FTU1 CH0 input
 *
 * @param eInputSelType  FTU1 CH0 input selection type
 */
LOCAL_INLINE void SCM_SetInSel_FTU1_CH0(SCM_FTUx_CH0_InputSelType eInputSelType)
{
    uint32_t u32RegVal = SCM->FTU_ROUTING;
    SCM->FTU_ROUTING = ((u32RegVal & (~(uint32_t)SCM_FTU_ROUTING_FTU1_CH0SEL_MASK)) | SCM_FTU_ROUTING_FTU1_CH0SEL(eInputSelType));
}

/**
 * @brief Lock FTU Routing Register
 *
 */
LOCAL_INLINE void SCM_HWA_LockFTU_ROUTING(void)
{
    SCM->FTU_ROUTING |= (uint32_t)SCM_FTU_ROUTING_LOCK_MASK;
}

/**
 * @brief Get FTU_ROUTING register lock status
 *
 * @return Lock status
 *         1: FTU_ROUTING register is lock
 *         0: FTU_ROUTING register is not lock
 */
LOCAL_INLINE uint32_t SCM_HWA_FTU_ROUTING_GetLockStatus(void)
{
    return (SCM->FTU_ROUTING & (uint32_t)SCM_FTU_ROUTING_LOCK_MASK) >> SCM_FTU_ROUTING_LOCK_SHIFT;
}

/**
 * @brief Lock FTU Global Time Base Control Register
 *
 */
LOCAL_INLINE void SCM_HWA_LockFTU_GTB(void)
{
    SCM->FTU_GTBC |= (uint32_t)SCM_FTU_GTBC_LOCK_MASK;
}

/**
 * @brief Get FTU GTB register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t SCM_HWA_FTU_GTB_GetLockStatus(void)
{
    return (SCM->FTU_GTBC & (uint32_t)SCM_FTU_GTBC_LOCK_MASK) >> SCM_FTU_GTBC_LOCK_SHIFT;
}

/**
 * @brief Configure FTU global time base control selection
 *
 * @param u32SelectedFtu The GTBC mask of Selected Ftu instance,it is the or value of SCM_FTUGTBCtrlType.
 *        eg.u32SelectedFtu == 1 means FTU0 selected, u32SelectedFtu == 5 means FTU0 and FTU2 selected.
 */
LOCAL_INLINE void SCM_HWA_ConfigFtuGTBSelect(uint32_t u32SelectedFtu)
{
	SCM->FTU_GTBC &= ~(uint32_t)SCM_FTU_GTBC_FTU_GTBC_MASK;
	SCM->FTU_GTBC |= (uint32_t)SCM_FTU_GTBC_FTU_GTBC(u32SelectedFtu);
}

/**
 * @brief Set FTU global time base control selection
 *
 * @param u32SelectedFtu The GTBC mask of Selected Ftu instance,it is the or value of SCM_FTUGTBCtrlType.
 *        eg.u32SelectedFtu == 1 means FTU0 selected, u32SelectedFtu == 5 means FTU0 and FTU2 selected.
 */
LOCAL_INLINE void SCM_HWA_SetFtuGTBSelect(uint32_t u32SelectedFtu)
{
	SCM->FTU_GTBC |= (uint32_t)SCM_FTU_GTBC_FTU_GTBC(u32SelectedFtu);
}

/**
 * @brief Clear FTU global time base control selection
 *
 * @param u32SelectedFtu The GTBC mask of Selected Ftu instance,it is the or value of SCM_FTUGTBCtrlType.
 *        eg.u32SelectedFtu == 1 means FTU0 selected, u32SelectedFtu == 5 means FTU0 and FTU2 selected.
 */
LOCAL_INLINE void SCM_HWA_ClearFtuGTBSelect(uint32_t u32SelectedFtu)
{
	SCM->FTU_GTBC &= ~(uint32_t)SCM_FTU_GTBC_FTU_GTBC(u32SelectedFtu);
}

/**
 * @brief Configure TPU global time base control selection
 *
 * @param bEn Enable or disable TPU Global Time Base
 */
LOCAL_INLINE void SCM_HWA_ConfigTpuGTBSelect(bool bEn)
{
	SCM->FTU_GTBC &= ~(uint32_t)SCM_FTU_GTBC_TPU_GTBC_MASK;
	SCM->FTU_GTBC |= (uint32_t)SCM_FTU_GTBC_TPU_GTBC(bEn);
}

/**
 * @brief Set the value of TPU Global Time Base Control Mask Register
 *
 * @param u32Value Value to be set
 */
LOCAL_INLINE void SCM_HWA_SetTpuGTBMValue(uint32_t u32Value)
{
	SCM->FTU_GTBCM = u32Value;
}

/**
 * @brief Configure TPU Channel [31:24] Source Select
 *
 * @param eTrgSelMask The TPU Channel [31:24] Source Select mask bits
 */
LOCAL_INLINE void SCM_HWA_ConfigTpuTrgSel(uint8_t eTrgSelMask)
{
    SCM->FTU_GTBCM = (SCM->FTU_GTBCM & (~(uint32_t)SCM_TPU_GTBCM_TPU_TRGSEL_MASK)) |
                     (uint32_t)SCM_TPU_GTBCM_TPU_TRGSEL(eTrgSelMask);
}

/**
 * @brief Configure TPU GTBC Mask is corresponding to channel trigger of TSTMP1
 *
 * @param eTpuGTBMask The TPU GTBC Mask (must be 0 ~ 15)
 */
LOCAL_INLINE void SCM_HWA_ConfigTpuGTBMask(uint8_t eTpuGTBMask)
{
    SCM->FTU_GTBCM = (SCM->FTU_GTBCM & (~(uint32_t)SCM_TPU_GTBCM_TPU_GTBCM_MASK)) |
                     (uint32_t)SCM_TPU_GTBCM_TPU_GTBCM(eTpuGTBMask);
}

/**
 * @brief Configure FTU Global Time Base Control Mask Register
 *
 * @param u8FtuIndex The selected FTU instance (must be 0 ~ 7)
 * @param u32Value Value to be set (must be 0 ~ 15)
 */
LOCAL_INLINE void SCM_HWA_ConfigFtuGTBMask(uint8_t u8FtuIndex, uint32_t u32Value)
{
	SCM->FTU_GTBCM &= ~ ((uint32_t)SCM_FTU_GTBCM_FTU0_GTBCM_MASK << (SCM_FTU_GTBCM_FTU0_GTBCM_WIDTH * u8FtuIndex));
	SCM->FTU_GTBCM |= (((uint32_t)u32Value & SCM_FTU_GTBCM_FTU0_GTBCM_MASK) << (SCM_FTU_GTBCM_FTU0_GTBCM_WIDTH * u8FtuIndex));
}

/**
 * @brief Clear FTU Global Time Base Control Mask Register
 *
 * @param u8FtuIndex The selected FTU instance (must be 0 ~ 7)
 */
LOCAL_INLINE void SCM_HWA_ClearFtuGTBMask(uint8_t u8FtuIndex)
{
	SCM->FTU_GTBCM &= ~ ((uint32_t)SCM_FTU_GTBCM_FTU0_GTBCM_MASK << (SCM_FTU_GTBCM_FTU0_GTBCM_WIDTH * u8FtuIndex));
}

/**
 * @brief Set FTU sync control
 *
 * @param u32Value The sync mask of selected FTU instance
 *        u32Value must be the or value of SCM_FTUSyncCtrlType
 */
LOCAL_INLINE void SCM_HWA_SetFTUSync(uint32_t u32Value)
{
    SCM->FTU_SYNC = u32Value & SCM_FTU_SYNC_MASK;
}

/**
 * @brief Lock FTU GTB Register
 *
 */
LOCAL_INLINE void SCM_HWA_LockDEBUG_TRACE(void)
{
    SCM->DEBUG_TRACE |= (uint32_t)SCM_DEBUG_TRACE_LOCK_MASK;
}

/**
 * @brief Get FTU GTB register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t SCM_HWA_DEBUG_TRACE_GetLockStatus(void)
{
    return(SCM->DEBUG_TRACE & (uint32_t)SCM_DEBUG_TRACE_LOCK_MASK) >> SCM_DEBUG_TRACE_LOCK_SHIFT;
}

/**
 * @brief Set debug atclk enable/disable
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SetEnable_DebugATClk(bool bEnable)
{
    SCM->DEBUG_TRACE = (SCM->DEBUG_TRACE & (~(SCM_DEBUG_TRACE_DEBUG_ATCLK_EN_MASK))) |
                       SCM_DEBUG_TRACE_DEBUG_ATCLK_EN(bEnable);
}

/**
 * @brief Set trace clock divider value
 *
 * @param u32Value The divider value to be set
 */
LOCAL_INLINE void SCM_HWA_SetTraceClkDiv(uint32_t u32Value)
{
    SCM->DEBUG_TRACE = ((SCM->DEBUG_TRACE & (~(uint32_t)SCM_DEBUG_TRACE_TRACECLK_DIV_MASK)) |
                       SCM_DEBUG_TRACE_TRACECLK_DIV(u32Value));
}

/**
 * @brief Set trace clock selection
 *
 * @param eSrcClkType Clock selection
 */
LOCAL_INLINE void SCM_HWA_SetTraceClkSrc(SCM_TraceClkSrcType eSrcClkType)
{
    SCM->DEBUG_TRACE = ((SCM->DEBUG_TRACE & (~(uint32_t)SCM_DEBUG_TRACE_TRACECLK_SEL_MASK)) |
                       SCM_DEBUG_TRACE_TRACECLK_SEL(eSrcClkType));
}

/**
 * @brief Set trace clock divider enable/disable
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SetEnable_TraceClk(bool bEnable)
{
    SCM->DEBUG_TRACE = (SCM->DEBUG_TRACE & (~(SCM_DEBUG_TRACE_TRACECLK_EN_MASK))) |
                       SCM_DEBUG_TRACE_TRACECLK_EN(bEnable);
}

/**
 * @brief Lock the SOCMISC register
 *
 */
LOCAL_INLINE void SCM_HWA_SOCMISC_LockWritePermit(void)
{
    SCM->SOCMISC |= (uint32_t)SCM_SOCMISC_WPB_LOCK_MASK;
}

/**
 * @brief Get the SOCMISC register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t SCM_HWA_SOCMISC_GetWPBLockStatus(void)
{
    return (SCM->SOCMISC & (uint32_t)SCM_SOCMISC_WPB_LOCK_MASK) >> SCM_SOCMISC_WPB_LOCK_SHIFT;
}

/**
 * @brief Get the CPU type of writing permission to SOCMISC register
 *
 * @return SCM_WPB_CpuType The CPU which has the write permission
 */
LOCAL_INLINE SCM_WPB_CpuType SCM_HWA_SOCMISC_GetCpuWritePermit(void)
{
    uint32_t u32RegVal = (SCM->SOCMISC & (uint32_t)SCM_SOCMISC_WPB_MASK) >> SCM_SOCMISC_WPB_SHIFT;
     return (SCM_WPB_CpuType)u32RegVal;
}

/**
 * @brief Set cpu to control SOCMISC register
 *
 * @param eCpuType Cpu allowed to control peripheral
 */
LOCAL_INLINE void SCM_HWA_SOCMISC_SetCpuWritePermit(SCM_WPB_CpuType eCpuType)
{
    SCM->SOCMISC = ((SCM->SOCMISC & (~(uint32_t)SCM_SOCMISC_WPB_MASK)) | SCM_SOCMISC_WPB(eCpuType));
}

/**
 * @brief Set software trigger 4~7 to TRGSEL1 & TRGSEL5
 *
 * @param eTriggerType software trigger number (SCM_SW_TRIG_0 ~ SCM_SW_TRIG_3)
 */
LOCAL_INLINE void SCM_HWA_SetSwTrigx_Trgsel15(SCM_SwTrigxType eTriggerType)
{
    SCM->SOCMISC = ((SCM->SOCMISC & (~(uint32_t)SCM_SOCMISC_GPR_SW_TRIG_7_4_MASK)) |
                   SCM_SOCMISC_GPR_SW_TRIG_7_4(eTriggerType));
}

/**
 * @brief Set software trigger 0~3 to TRGSEL0 & TRGSEL4
 *
 * @param eTriggerType software trigger number (SCM_SW_TRIG_4 ~ SCM_SW_TRIG_7)
 */
LOCAL_INLINE void SCM_HWA_SetSwTrigx_Trgsel04(SCM_SwTrigxType eTriggerType)
{
    SCM->SOCMISC = ((SCM->SOCMISC & (~(uint32_t)SCM_SOCMISC_GPR_SW_TRIG_3_0_MASK)) |
                   SCM_SOCMISC_GPR_SW_TRIG_3_0(eTriggerType));
}

/**
 * @brief Get CCM0 status
 *
 * @return CCM0 Status, it is the or value of SCM_CCMxStatusType
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_CCM0( void )
{
    return SCM->CCM0_STATUS & SCM_CCM0_STATUS_MASK;
}

/**
 * @brief Lock FLEXCAN_ROUTING Register
 *
 */
LOCAL_INLINE void SCM_HWA_LockFLEXCAN_ROUTING(void)
{
    SCM->FLEXCAN_ROUTING |= (uint32_t)SCM_FLEXCAN_ROUTING_LOCK_MASK;
}

/**
 * @brief Get FLEXCAN_ROUTING register lock status
 *
 * @return Lock status
 *         1: FLEXCAN_ROUTING register is lock
 *         0: FLEXCAN_ROUTING register is not lock
 */
LOCAL_INLINE uint32_t SCM_HWA_FLEXCAN_ROUTING_GetLockStatus(void)
{
    return (SCM->FLEXCAN_ROUTING & (uint32_t)SCM_FLEXCAN_ROUTING_LOCK_MASK) >> SCM_FLEXCAN_ROUTING_LOCK_SHIFT;
}

/**
 * @brief Select TRESEL input from pad TRGSEL_IN0~TRGSEL_IN15 for FLEXCAN0/1/2/3 RX
 *
 * @param u16TrgSel Enable Select TRESEL input from pad TRGSEL_IN0~TRGSEL_IN15 for FLEXCAN0/1/2/3 RX
 */
LOCAL_INLINE void SCM_HWA_FLEXCAN_ROUTING_SetTriggerSel(uint16_t u16TrgSel)
{
    SCM->FLEXCAN_ROUTING = ((SCM->FLEXCAN_ROUTING & (~(uint32_t)SCM_FLEXCAN_ROUTING_FLEXCAN_TRIGGER_MASK_MASK)) |
                           SCM_FLEXCAN_ROUTING_FLEXCAN_TRIGGER_MASK(u16TrgSel));
}

/**
 * @brief Set MSC0 ALTIN high higher bits[31:24] source selection
 *
 * @param eInSelType Router selection
 */
LOCAL_INLINE void SCM_HWA_SetSel_MSC0AltInHH(SCM_MSCAltInSelType eInSelType)
{
    uint32_t u32RegVal = SCM->MSC0_ROUTING;
    SCM->MSC0_ROUTING = ((u32RegVal & (~(uint32_t)SCM_MSC0_ROUTING_MSC0_31_24_SEL_MASK)) | SCM_MSC0_ROUTING_MSC0_31_24_SEL(eInSelType));
}

/**
 * @brief Set MSC0 ALTIN high lower bits[23:16] source selection
 *
 * @param eInSelType Router selection
 */
LOCAL_INLINE void SCM_HWA_SetSel_MSC0AltInHL(SCM_MSCAltInSelType eInSelType)
{
    uint32_t u32RegVal = SCM->MSC0_ROUTING;
    SCM->MSC0_ROUTING = ((u32RegVal & (~(uint32_t)SCM_MSC0_ROUTING_MSC0_23_16_SEL_MASK)) | SCM_MSC0_ROUTING_MSC0_23_16_SEL(eInSelType));
}

/**
 * @brief Set MSC0 ALTIN low higher bits[15:8] source selection
 *
 * @param eInSelType Router selection
 */
LOCAL_INLINE void SCM_HWA_SetSel_MSC0AltInLH(SCM_MSCAltInSelType eInSelType)
{
    uint32_t u32RegVal = SCM->MSC0_ROUTING;
    SCM->MSC0_ROUTING = ((u32RegVal & (~(uint32_t)SCM_MSC0_ROUTING_MSC0_15_8_SEL_MASK)) | SCM_MSC0_ROUTING_MSC0_15_8_SEL(eInSelType));
}

/**
 * @brief Set MSC0 ALTIN low lower bits[7:0] source selection
 *
 * @param eInSelType Router selection
 */
LOCAL_INLINE void SCM_HWA_SetSel_MSC0AltInLL(SCM_MSCAltInSelType eInSelType)
{
    uint32_t u32RegVal = SCM->MSC0_ROUTING;
    SCM->MSC0_ROUTING = ((u32RegVal & (~(uint32_t)SCM_MSC0_ROUTING_MSC0_7_0_SEL_MASK)) | SCM_MSC0_ROUTING_MSC0_7_0_SEL(eInSelType));
}

/**
 * @brief Lock MSC0_ROUTING Register
 *
 */
LOCAL_INLINE void SCM_HWA_LockMSC0_ROUTING(void)
{
    SCM->MSC0_ROUTING |= (uint32_t)SCM_MSC0_ROUTING_LOCK_MASK;
}

/**
 * @brief Get MSC0_ROUTING register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t SCM_HWA_MSC0_ROUTING_GetLockStatus(void)
{
    return(SCM->MSC0_ROUTING & (uint32_t)SCM_MSC0_ROUTING_LOCK_MASK) >> SCM_MSC0_ROUTING_LOCK_SHIFT;
}

/**
 * @brief Set FCSMU software trigger enable/disable
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SetEnable_FCSMUSwTrigger(bool bEnable)
{
    SCM->FCSMU_SW = (SCM->FCSMU_SW & (~(SCM_FCSMU_SW_FCSMU_SW_MASK))) |
                    SCM_FCSMU_SW_FCSMU_SW(bEnable);
}

/**
 * @brief FTU_IN[15:8] Source Select
 *
 * @param eRouterType Router source selection
 */
LOCAL_INLINE void SCM_HWA_SetIsmRouterFtuD(SCM_ISMRouterType eRouterType)
{
    SCM->ISM_ROUTING = ((SCM->ISM_ROUTING & (~(uint32_t)SCM_ISM_ROUTING_ISM_ROUT_FTU_D_MASK)) |
                       SCM_ISM_ROUTING_ISM_ROUT_FTU_D(eRouterType));
}

/**
 * @brief FTU_IN[7:0] Source Select
 *
 * @param eRouterType Router source selection
 */
LOCAL_INLINE void SCM_HWA_SetIsmRouterFtuC(SCM_ISMRouterType eRouterType)
{
    SCM->ISM_ROUTING = ((SCM->ISM_ROUTING & (~(uint32_t)SCM_ISM_ROUTING_ISM_ROUT_FTU_C_MASK)) |
                       SCM_ISM_ROUTING_ISM_ROUT_FTU_C(eRouterType));
}

/**
 * @brief Set ISM_FTU_ROUT[15:8] source select
 *
 * @param eRouterType Router source selection
 */
LOCAL_INLINE void SCM_HWA_SetIsmRouterFtuB(SCM_ISMRouterType eRouterType)
{
    SCM->ISM_ROUTING = ((SCM->ISM_ROUTING & (~(uint32_t)SCM_ISM_ROUTING_ISM_ROUT_FTU_B_MASK)) |
                       SCM_ISM_ROUTING_ISM_ROUT_FTU_B(eRouterType));
}

/**
 * @brief Set ISM_FTU_ROUT[7:0] source select
 *
 * @param eRouterType Router source selection
 */
LOCAL_INLINE void SCM_HWA_SetIsmRouterFtuA(SCM_ISMRouterType eRouterType)
{
    SCM->ISM_ROUTING = ((SCM->ISM_ROUTING & (~(uint32_t)SCM_ISM_ROUTING_ISM_ROUT_FTU_A_MASK)) |
                       SCM_ISM_ROUTING_ISM_ROUT_FTU_A(eRouterType));
}

/**
 * @brief Get matrix status register 0 status
 *
 * @return Register status
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_MATRIX_STATUS0(void)
{
    return SCM->MATRIX_STATUS0;
}

/**
 * @brief clear matrix status register 0 status
 *
 * @u32Status Matrix status
 */
LOCAL_INLINE void SCM_HWA_Clear_MATRIX_STATUS0(uint32_t u32Status)
{
    SCM->MATRIX_STATUS0 |= u32Status & SCM_MATRIX_STATUS0_MASK;
}

/**
 * @brief Get matrix status register 1 status
 *
 * @return Register status
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_MATRIX_STATUS1(void)
{
    return SCM->MATRIX_STATUS1;
}

/**
 * @brief clear matrix status register 1 status
 *
 * @u32Status Matrix status
 */
LOCAL_INLINE void SCM_HWA_Clear_MATRIX_STATUS1(uint32_t u32Status)
{
    SCM->MATRIX_STATUS1 |= u32Status & SCM_MATRIX_STATUS1_MASK;
}

/**
 * @brief Get matrix status register 2 status
 *
 * @return Register status
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_MATRIX_STATUS2(void)
{
    return SCM->MATRIX_STATUS2;
}

/**
 * @brief clear matrix status register 2 status
 *
 * @u32Status Matrix status
 */
LOCAL_INLINE void SCM_HWA_Clear_MATRIX_STATUS2(uint32_t u32Status)
{
    SCM->MATRIX_STATUS2 |= u32Status & SCM_MATRIX_STATUS2_MASK;
}

/**
 * @brief Get matrix status register 5 status
 *
 * @return Register status
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_MATRIX_STATUS5(void)
{
    return SCM->MATRIX_STATUS5;
}

/**
 * @brief clear matrix status register 5 status
 *
 * @u32Status Matrix status
 */
LOCAL_INLINE void SCM_HWA_Clear_MATRIX_STATUS5(uint32_t u32Status)
{
    SCM->MATRIX_STATUS5 |= u32Status & SCM_MATRIX_STATUS5_MASK;
}

/**
 * @brief Get matrix status register 6 status
 *
 * @return Register status
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_MATRIX_STATUS6(void)
{
    return SCM->MATRIX_STATUS6;
}

/**
 * @brief clear matrix status register 6 status
 *
 * @u32Status Matrix status
 */
LOCAL_INLINE void SCM_HWA_Clear_MATRIX_STATUS6(uint32_t u32Status)
{
    SCM->MATRIX_STATUS6 |= u32Status & SCM_MATRIX_STATUS6_MASK;
}

/**
 * @brief Get matrix status register 7 status
 *
 * @return Register status
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_MATRIX_STATUS7(void)
{
    return SCM->MATRIX_STATUS7;
}

/**
 * @brief clear matrix status register 7 status
 *
 * @u32Status Matrix status
 */
LOCAL_INLINE void SCM_HWA_Clear_MATRIX_STATUS7(uint32_t u32Status)
{
    SCM->MATRIX_STATUS7 |= u32Status & SCM_MATRIX_STATUS7_MASK;
}

/**
 * @brief Get matrix ID status register status
 *
 * @return Register status
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_MATRIX_ID_STATUS0(void)
{
    return SCM->MATRIX_ID_STATUS0;
}

/**
 * @brief clear matrix ID status register status
 *
 * @u32Status Matrix ID status
 */
LOCAL_INLINE void SCM_HWA_Clear_MATRIX_ID_STATUS0(uint32_t u32Status)
{
    SCM->MATRIX_ID_STATUS0 |= u32Status & SCM_MATRIX_ID_STATUS0_MASK;
}

/**
 * @brief Set SCM module mailbox data out, output from device to debug
 *
 * @param u32Value Ouputdata value
 */
LOCAL_INLINE void SCM_HWA_SetData_MDO(uint32_t u32Value)
{
    SCM->SYSAP_MDO = u32Value;
}

/**
 * @brief Get SCM module mailbox data in, input from debug to device
 *
 * @return u32Value Input data value
 */
LOCAL_INLINE uint32_t SCM_HWA_GetData_MDI(void)
{
    return SCM->SYSAP_MDI;
}

/**
 * @brief Select the type of Status2 Register
 *
 * @param eStatus2Sel Selected Status2 type
 */
LOCAL_INLINE void SCM_HWA_Status2RegisterSelection(SCM_SysAPStatus2SelType eStatus2Sel)
{
    SCM->SYSAP_CTRL = (SCM->SYSAP_CTRL & (~(SCM_SYSAP_CTRL_STATUS2_REG_SEL_MASK))) |
                      SCM_SYSAP_CTRL_STATUS2_REG_SEL(eStatus2Sel);
}

/**
 * @brief Get new mailbox data input available flag,
 *        device read MDI regiser will automatically clear the bit
 *
 * @return Mailbox data input available/disable
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_NewMDIAvailable(void)
{
    return ((SCM->SYSAP_CTRL & (uint32_t)SCM_SYSAP_CTRL_NEW_MDI_AVAILABLE_MASK)>>(uint32_t)SCM_SYSAP_CTRL_NEW_MDI_AVAILABLE_SHIFT);
}

/**
 * @brief Control if CPU0 hold in wait at the end of reset sequence
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SetEnable_Cpu0HoldInWait(bool bEnable)
{
    SCM->SYSAP_CTRL = (SCM->SYSAP_CTRL & (~(SCM_SYSAP_CTRL_CPU0_HOLD_IN_WAIT_MASK))) |
                      SCM_SYSAP_CTRL_CPU0_HOLD_IN_WAIT(bEnable);
}

/**
 * @brief Control if hold CPU0 in reset at the end of reset sequence
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SetEnable_Cpu0HoldInReset(bool bEnable)
{
    SCM->SYSAP_CTRL = (SCM->SYSAP_CTRL & (~(SCM_SYSAP_CTRL_CPU0_HOLD_IN_RESET_MASK))) |
                      SCM_SYSAP_CTRL_CPU0_HOLD_IN_RESET(bEnable);
}

/**
 * @brief Set to force a system reset, clear the bit to release system from reset
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SetEnable_SystemReset(bool bEnable)
{
    SCM->SYSAP_CTRL = (SCM->SYSAP_CTRL & (~(SCM_SYSAP_CTRL_SYSTEM_RESET_REQ_MASK))) |
                      SCM_SYSAP_CTRL_SYSTEM_RESET_REQ(bEnable);
}

/**
 * @brief Set to force all CPU debug restarted, CPU to exit halt state
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SetEnable_AllCpuDebugRestart(bool bEnable)
{
    SCM->SYSAP_CTRL = (SCM->SYSAP_CTRL & (~(SCM_SYSAP_CTRL_CPU_DEBUG_RESTART_MASK))) |
                      SCM_SYSAP_CTRL_CPU_DEBUG_RESTART(bEnable);
}

/**
 * @brief Set to force core to halt, if core is in stop mode.
 *        This bit can be used to wakeup the core and transition to halt state
 *
 * @param eSelType Cpu type selection
 */
LOCAL_INLINE void SCM_HWA_SetSel_CpuDebugRequest(SCM_SysApCpuDebugReqType eSelType)
{
    SCM->SYSAP_CTRL = ((SCM->SYSAP_CTRL & (~(uint32_t)SCM_SYSAP_CTRL_CPU_DEBUG_REQ_MASK)) |
                      SCM_SYSAP_CTRL_CPU_DEBUG_REQ(eSelType));
}

/**
 * @brief Set to disable the debug, clear to allow debug operation
 *
 * @param bDisable Disable/Enable
 */
LOCAL_INLINE void SCM_HWA_SetDisable_Debug(bool bDisable)
{
    SCM->SYSAP_CTRL = ((SCM->SYSAP_CTRL & (~(uint32_t)SCM_SYSAP_CTRL_DEBUG_DIS_MASK)) |
                      SCM_SYSAP_CTRL_DEBUG_DIS(bDisable));
}

/**
 * @brief Set to Trigger Flash Mass Erase.Cleared by hardware after mass erase is done
 *
 */
LOCAL_INLINE void SCM_HWA_TriggerFlashMassErase(void)
{
    SCM->SYSAP_CTRL |= SCM_SYSAP_CTRL_FLASH_MASS_ERASE_MASK;
}

/**
 * @brief Lock the CPU permission(WPB) in SUBSYS_PCC register, and WPB cannot be written until a power-on reset
 *
 */
LOCAL_INLINE void SCM_HWA_SUBSYS_PCC_LockWritePermit(void)
{
    SCM->SUBSYS_PCC |= (uint32_t)SCM_SUBSYS_PCC_WPB_LOCK_MASK;
}

/**
 * @brief Get the lock status of CPU permission(WPB) in SUBSYS_PCC register
 *
 * @return 1: The WPB of SUBSYS_PCC register is locked
 *         0: The WPB of SUBSYS_PCC register is not locked
 */
LOCAL_INLINE uint32_t SCM_HWA_SUBSYS_PCC_GetWPBLockStatus(void)
{
    return (SCM->SUBSYS_PCC & (uint32_t)SCM_SUBSYS_PCC_WPB_LOCK_MASK) >> SCM_SUBSYS_PCC_WPB_LOCK_SHIFT;
}

/**
 * @brief Get the CPU type of writing permission to SUBSYS_PCC register
 *
 * @return SCM_WPB_CpuType The CPU which has the write permission
 */
LOCAL_INLINE SCM_WPB_CpuType SCM_HWA_SUBSYS_PCC_GetCpuWritePermit(void)
{
    uint32_t u32RegVal = ((SCM->SUBSYS_PCC & (uint32_t)SCM_SUBSYS_PCC_WPB_MASK) >> SCM_SUBSYS_PCC_WPB_SHIFT);
    return (SCM_WPB_CpuType)u32RegVal;
}

/**
 * @brief Set CPU to control the SUBSYS_PCC register
 *
 * @param eCpuType CPU allowed to control peripheral
 */
LOCAL_INLINE void SCM_HWA_SUBSYS_PCC_SetCpuWritePermit(SCM_WPB_CpuType eCpuType)
{
    SCM->SUBSYS_PCC = ((SCM->SUBSYS_PCC & (~(uint32_t)SCM_SUBSYS_PCC_WPB_MASK)) | SCM_SUBSYS_PCC_WPB(eCpuType));
}

/**
 * @brief Get TPU clock enable/disable status
 *
 * @return 1: TPU clock disabled
 *         0: TPU clock enabled
 */
LOCAL_INLINE uint32_t SCM_HWA_SUBSYS_PCC_GetStatus_TPUClock(void)
{
    return (SCM->SUBSYS_PCC & SCM_SUBSYS_PCC_CLKEN_TPU_MASK) >> SCM_SUBSYS_PCC_CLKEN_TPU_SHIFT;
}

/**
 * @brief Set TPU clock enable/disable
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SUBSYS_PCC_SetEnable_TPUClock(bool bEnable)
{
    SCM->SUBSYS_PCC = ((SCM->SUBSYS_PCC & (~(uint32_t)SCM_SUBSYS_PCC_CLKEN_TPU_MASK)) |
                        SCM_SUBSYS_PCC_CLKEN_TPU(bEnable));
}

/**
 * @brief Get HSM clock enable/disable status
 *
 * @return 1: HSM clock disabled
 *         0: HSM clock enabled
 */
LOCAL_INLINE uint32_t SCM_HWA_SUBSYS_PCC_GetStatus_HSMClock(void)
{
    return (SCM->SUBSYS_PCC & SCM_SUBSYS_PCC_CLKEN_HSM_ENGINE_MASK) >> SCM_SUBSYS_PCC_CLKEN_HSM_ENGINE_SHIFT;
}

/**
 * @brief Set HSM clock enable/disable
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SUBSYS_PCC_SetEnable_HSMClock(bool bEnable)
{
    SCM->SUBSYS_PCC = ((SCM->SUBSYS_PCC & (~(uint32_t)SCM_SUBSYS_PCC_CLKEN_HSM_ENGINE_MASK)) |
                        SCM_SUBSYS_PCC_CLKEN_HSM_ENGINE(bEnable));
}

/**
 * @brief Get SubSystem clock enable/disable status
 *
 * @return 1: SubSystem clock disabled
 *         0: SubSystem clock enabled
 */
LOCAL_INLINE uint32_t SCM_HWA_SUBSYS_PCC_GetStatus_SubSystemClock(void)
{
    return (SCM->SUBSYS_PCC & SCM_SUBSYS_PCC_CLKEN_SUBSYS_MASK) >> SCM_SUBSYS_PCC_CLKEN_SUBSYS_SHIFT;
}

/**
 * @brief Set SubSystem clock enable/disable
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SUBSYS_PCC_SetEnable_SubSystemClock(bool bEnable)
{
    SCM->SUBSYS_PCC = ((SCM->SUBSYS_PCC & (~(uint32_t)SCM_SUBSYS_PCC_CLKEN_SUBSYS_MASK)) |
                        SCM_SUBSYS_PCC_CLKEN_SUBSYS(bEnable));
}

/**
 * @brief Set SubSystem software reset
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SUBSYS_PCC_SetEnable_SwReset(bool bEnable)
{
    SCM->SUBSYS_PCC = ((SCM->SUBSYS_PCC & (~(uint32_t)SCM_SUBSYS_PCC_SWRST_MASK)) |
                        SCM_SUBSYS_PCC_SWRST(bEnable));
}

/**
 * @brief Set SubSystem watchdog reset
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SUBSYS_PCC_SetEnable_SubsysWdgReset(bool bEnable)
{
    SCM->SUBSYS_PCC = ((SCM->SUBSYS_PCC & (~(uint32_t)SCM_SUBSYS_PCC_WDG_RSTEN_MASK)) |
                        SCM_SUBSYS_PCC_WDG_RSTEN(bEnable));
}

/**
 * @brief Set SubSystem stop mode request
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SUBSYS_PCC_SetEnable_SubsysStopModReq(bool bEnable)
{
    SCM->SUBSYS_PCC = ((SCM->SUBSYS_PCC & (~(uint32_t)SCM_SUBSYS_PCC_STOP_REQ_MASK)) |
                        SCM_SUBSYS_PCC_STOP_REQ(bEnable));
}

/**
 * @brief Subsystem status register value
 *
 * @return Subsystem status register
 */
LOCAL_INLINE uint32_t SCM_HWA_GetValue_SUBSYS_STATUS(void)
{
    return SCM->SUBSYS_STATUS;
}

/**
 * @brief Get Subsystem Error Report
 *
 * @return Subsystem Error Report
 */
LOCAL_INLINE uint16_t SCM_HWA_GetStatus_SUBSYS_ERR(void)
{
    return (SCM->SUBSYS_STATUS & SCM_SUBSYS_STATUS_HSM_SYS_ERR_MASK) >> SCM_SUBSYS_STATUS_HSM_SYS_ERR_SHIFT;
}

/**
 * @brief Get Subsystem status
 *
 * @return true: Subsystem status asserted
 *         false: Subsystem status not asserted
 */
LOCAL_INLINE bool SCM_HWA_GetStatus_SUBSYS_STATUS(SCM_SUBSYSStatusType eStatusType)
{
    return ((SCM->SUBSYS_STATUS & (uint32_t)eStatusType) != 0U) ? true : false;
}

/**
 * @brief Get mailbox data output from device to debug flag
 *
 * @return Flag status
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_MDOFlag(void)
{
    return (SCM->MDO_FLAG & SCM_MDO_FLAG_MDO_FLAG_MASK) >> SCM_MDO_FLAG_MDO_FLAG_SHIFT;
}

/**
 * @brief Lock the CPU permission(WPB) in MASTER_HALT_REQ register, and WPB cannot be written until a power-on reset
 *
 */
LOCAL_INLINE void SCM_HWA_MASTER_HALT_REQ_LockWritePermit(void)
{
    SCM->MASTER_HALT_REQ |= (uint32_t)SCM_MASTER_HALT_REQ_WPB_LOCK_MASK;
}

/**
 * @brief Get the lock status of CPU permission(WPB) in MASTER_HALT_REQ register
 *
 * @return 1: The WPB of MASTER_HALT_REQ register is locked
 *         0: The WPB of MASTER_HALT_REQ register is not locked
 */
LOCAL_INLINE uint32_t SCM_HWA_MASTER_HALT_REQ_GetWPBLockStatus(void)
{
    return (SCM->MASTER_HALT_REQ & (uint32_t)SCM_MASTER_HALT_REQ_WPB_LOCK_MASK);
}

/**
 * @brief Get the CPU type of writing permission to MASTER_HALT_REQ register
 *
 * @return SCM_WPB_CpuType The CPU which has the write permission
 */
LOCAL_INLINE SCM_WPB_CpuType SCM_HWA_MASTER_HALT_REQ_GetCpuWritePermit(void)
{
    uint32_t u32RegVal = ((SCM->MASTER_HALT_REQ & (uint32_t)SCM_MASTER_HALT_REQ_WPB_MASK) >> SCM_MASTER_HALT_REQ_WPB_SHIFT);
    return (SCM_WPB_CpuType)u32RegVal;
}

/**
 * @brief Set CPU to control the MASTER_HALT_REQ register
 *
 * @param eCpuType CPU allowed to control peripheral
 */
LOCAL_INLINE void SCM_HWA_MASTER_HALT_REQ_SetCpuWritePermit(SCM_WPB_CpuType eCpuType)
{
    SCM->MASTER_HALT_REQ = ((SCM->MASTER_HALT_REQ & (~(uint32_t)SCM_MASTER_HALT_REQ_WPB_MASK)) |
                           SCM_MASTER_HALT_REQ_WPB(eCpuType));
}

/**
 * @brief Set MASTER_HALT_REQ halt request
 *
 * @param eHaltReq halt request defined in SCM_HaltReqType
 */
LOCAL_INLINE void SCM_HWA_SetSel_MASTER_HALT_REQ(SCM_HaltReqType eHaltReq)
{
    SCM->MASTER_HALT_REQ |= (uint32_t)1U << ((uint32_t)eHaltReq * 8U);
}

/**
 * @brief Get MASTER_HALT_ACK halt ACK status
 *
 * @return SCM_HaltReqAckType Ack status
 */
LOCAL_INLINE SCM_HaltReqAckType SCM_HWA_GetStatus_MASTER_HALT_ACK(SCM_HaltReqType eHaltReq)
{
    uint32_t u32RegVal = (SCM->MASTER_HALT_ACK >> ((uint32_t)eHaltReq * 8U)) & 0x7U;
     return (SCM_HaltReqAckType)u32RegVal;
}

/**
 * @brief Set CPU0 NMI interrupt router enable/disable
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SetEnable_Cpu0NMIIrqRouter(bool bEnable)
{
    SCM->INT_ROUTER_NMI = (SCM->INT_ROUTER_NMI & (~(SCM_INT_ROUTER_NMI_C0_EN_MASK))) |
                          SCM_INT_ROUTER_NMI_C0_EN(bEnable);
}

/**
 * @brief Lock SCM_INT_ROUTER_NMI register
 *
 */
LOCAL_INLINE void SCM_HWA_LockINT_ROUTER_NMI(void)
{
    SCM->INT_ROUTER_NMI |= (uint32_t)SCM_INT_ROUTER_NMI_LOCK_MASK;
}

/**
 * @brief Get SCM_INT_ROUTER_NMI register lock status
 *
 * @return Lock status
 */
LOCAL_INLINE uint32_t SCM_HWA_INT_ROUTER_NMI_GetLockStatus(void)
{
    return (SCM->INT_ROUTER_NMI & (uint32_t)SCM_INT_ROUTER_NMI_LOCK_MASK) >> SCM_INT_ROUTER_NMI_LOCK_SHIFT;
}

/**
 * @brief Get CRC done Flag
 *
 * @return CRC done Flag
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_CrcDoneFlag(void)
{
    return((SCM->CRCCSR & (uint32_t)SCM_CRCCSR_DONE_MASK)>>(uint32_t)SCM_CRCCSR_DONE_SHIFT);
}

/**
 * @brief Get CRC Error Flag
 *
 * @return CRC Error Flag
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_CrcErrFlag(void)
{
    return((SCM->CRCCSR & (uint32_t)SCM_CRCCSR_ERR_MASK)>>(uint32_t)SCM_CRCCSR_ERR_SHIFT);
}

/**
 * @brief Clear CRC error flag
 */
LOCAL_INLINE void SCM_HWA_ClearCrcErrorFlag(void)
{
    SCM->CRCCSR |= (uint32_t)SCM_CRCCSR_ERR_MASK;
}

/**
 * @brief Get CRC Busy Flag
 *
 * @return CRC Busy Flag
 */
LOCAL_INLINE uint32_t SCM_HWA_GetStatus_CrcBusyFlag(void)
{
    return((SCM->CRCCSR & (uint32_t)SCM_CRCCSR_BUY_MASK)>>(uint32_t)SCM_CRCCSR_BUY_SHIFT);
}

/**
 * @brief Set CRC error out enable/disable
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SetEnable_CrcErrOut(bool bEnable)
{
    SCM->CRCCSR = (SCM->CRCCSR & (~(SCM_CRCCSR_EOEN_MASK))) | SCM_CRCCSR_EOEN(bEnable);
}

/**
 * @brief Set CRC check enable/disable
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SetEnable_CrcCheck(bool bEnable)
{
    SCM->CRCCSR = (SCM->CRCCSR & (~(SCM_CRCCSR_CHKEN_MASK))) | SCM_CRCCSR_CHKEN(bEnable);
}

/**
 * @brief Set CRC trigger enable/disable
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SetEnable_CrcTrigger(bool bEnable)
{
    SCM->CRCCSR = (SCM->CRCCSR & (~(SCM_CRCCSR_TRGEN_MASK))) | SCM_CRCCSR_TRGEN(bEnable);
}

/**
 * @brief Set CRC software generate enable/disable
 *
 * @param bEnable Enable/Disable
 */
LOCAL_INLINE void SCM_HWA_SetEnable_CrcSwGen(bool bEnable)
{
    SCM->CRCCSR = (SCM->CRCCSR & (~(SCM_CRCCSR_GEN_MASK))) | SCM_CRCCSR_GEN(bEnable);
}

/**
 * @brief Get CRC result
 *
 * @return CRC result
 */
LOCAL_INLINE uint32_t SCM_HWA_GetCrcResult(void)
{
    return SCM->CRCRES;
}




#endif  /*#ifndef _HWA_SCM_H_ */
