/**
 * @file fc7xxx_driver_fcsmu.h
 * @author Flagchip
 * @brief FC7xxx FCSMU driver type definition and API
 * @version 0.1.0
 * @date 2024-01-14
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-14    qxw0100       N/A          First version for FC7240
   ******************************************************************************** */
#ifndef _DRIVER_FC7XXX_DRIVER_FCSMU_H_
#define _DRIVER_FC7XXX_DRIVER_FCSMU_H_
#include "device_header.h"
#include "HwA_fcsmu.h"
/**
 * @addtogroup fc7xxx_driver_fcsmu
 * @{
. */

typedef enum
{
    FCSMU_INSTANCE_0 = 0U,  /*!< FCSMU instance 0 is selected. */
} FCSMU_InstanceType;

typedef enum
{
    FCSMU_STATUS_SUCCESS    = 0U,  /*!< FCSMU operation is succeed. */
    FCSMU_STATUS_ERROR      = 1U   /*!< FCSMU operation is failed. */
} FCSMU_StatusType;

typedef enum
{
    FCSMU_STATE_NORMAL  = 0U,    /*!< FCSMU state normal */
    FCSMU_STATE_CONGIG  = 1U,    /*!< FCSMU state config */
    FCSMU_STATE_WARN    = 2U,    /*!< FCSMU state warn */
    FCSMU_STATE_FAULT   = 3U     /*!< FCSMU state fault */
} FCSMU_StateType;

typedef enum
{
    FCSMU_OP_STATE_IDLE         = 0U,   /*!< FCSMU operation status idle */
    FCSMU_OP_STATE_BUSY         = 1U,   /*!< FCSMU operation status busy */
    FCSMU_OP_STATE_FAILED       = 2U,   /*!< FCSMU operation status failed */
    FCSMU_OP_STATE_SUCCESSFUL   = 3U    /*!< FCSMU operation status successful */
} FCSMU_OperationStatusType;

typedef enum
{
    FCSMU_CRC_SW_MODE       = 0U,   /*!< FCSMU crc software mode. */
    FCSMU_CRC_TRIGGER_MODE  = 1U    /*!< FCSMU crc trigger mode. */
} FCSMU_CrcModeType;

typedef enum
{
    FCSMU_SOUT_CTRL_BY_FSM              = 0U,   /*!< SOUT is controlled by the FSM. */
    FCSMU_SOUT_CTRL_KEEP_LOW            = 1U,   /*!< SOUT keeps low. */
    FCSMU_SOUT_CTRL_BY_FSM2             = 2U,   /*!< SOUT is controlled by the FSM. */
    FCSMU_SOUT_CTRL_KEEP_HIGH_THEN_FSM  = 3U    /*!< SOUT keeps high until a fault occures on a channel, then controlled by FSM. */
} FCSMU_SoutControlType;

typedef enum
{
    FCSMU_SOUT_DEFAUT_POLARITY = 0U,    /*!< Default polarity. */
    FCSMU_SOUT_SWITCH_POLARITY = 1U     /*!< Switch polarity. */
} FCSMU_SoutPolarityType;

typedef enum
{
    FCSMU_SOUT_PROTOCOL_DUAL_RAIL       = 0U,
    FCSMU_SOUT_PROTOCOL_TIME_SWITCH     = 1U,
    FCSMU_SOUT_PROTOCOL_BISTABLE        = 2U,
    FCSMU_SOUT_PROTOCOL_FAULT_TOGGLE    = 3U,
    FCSMU_SOUT_PROTOCOL_TIME_DUAL_RAIL  = 4U,
    FCSMU_SOUT_PROTOCOL_DIAG0           = 5U,
    FCSMU_SOUT_PROTOCOL_DIAG1           = 6U,
    FCSMU_SOUT_PROTOCOL_DIAG2           = 7U,
} FCSMU_SoutProtocolType;

typedef enum
{
    FCSMU_WARNING_IRQ   = 0U,
    FCSMU_FAULT_IRQ     = 1U,
    FCSMU_CFG_TIMEOUT   = 2U
} FCSMU_IQRType;

typedef enum
{
    FCSMU_FAULT_CHANNEL_NONE                    = 0x0U,
    FCSMU_FAULT_CHANNEL_TEMP_ERROR              = 0x1U,         /*!< Event from temperature sensor. */
    FCSMU_FAULT_CHANNEL_PMC_ERROR               = 0x2U,         /*!< Voltage out of range indication from PMC. */
    FCSMU_FAULT_CHANNEL_NVR_ERROR               = 0x4U,         /*!< NVR load error/System abnormal alarm signal. */
    FCSMU_FAULT_CHANNEL_STCU_BIST_ERROR         = 0x8U,         /*!< STCU MBIST or LBIST fail. */
    FCSMU_FAULT_CHANNEL_STCU_LS0_ERROR          = 0x10U,        /*!< Lockstep compare fault. */
    FCSMU_FAULT_CHANNEL_SYSTEM_CPU0_ERROR       = 0x40U,        /*!< System RAM CPU0 access error. */
    FCSMU_FAULT_CHANNEL_SYSTEM_NON_CPU_ERROR    = 0x200U,       /*!< System RAM None CPU access error. */
    FCSMU_FAULT_CHANNEL_SCM_CPU0_ERROR          = 0x400U,       /*!< Matrix Access Monitor ECC check CPU0 error. */
    FCSMU_FAULT_CHANNEL_SCM_NON_CPU_ERROR       = 0x2000U,      /*!< Matrix Access Monitor ECC check non CPU error. */
    FCSMU_FAULT_CHANNEL_CPU0_ECC_ERROR          = 0x4000U,      /*!< Including ITCM/DTCM/ICACHE/DCACHE. */
    FCSMU_FAULT_CHANNEL_CMU4_FAIL_ERROR         = 0x80000U,     /*!< CMU4 failure interrupt. */
    FCSMU_FAULT_CHANNEL_CMU_FAIL_ERROR          = 0x100000U,    /*!< CMU1/2 failure interrupt. */
    FCSMU_FAULT_CHANNEL_FLASH_ECC_ERROR         = 0x200000U,    /*!< Flash ECC error. */
    FCSMU_FAULT_CHANNEL_SCG_PLL_FOSC_ERROR      = 0x400000U,    /*!< PLL/FOSC loss of clock. */
    FCSMU_FAULT_CHANNEL_DMA0_ERROR              = 0x800000U,    /*!< DM0 AHB Error/LS Error/CFG RAM Error. */
    FCSMU_FAULT_CHANNEL_INTM0_ERROR             = 0x2000000U,   /*!< Interrupt Monitor error. */
    FCSMU_FAULT_CHANNEL_FMC_ERROR               = 0x10000000U,  /*!< FMC ECC error. */
    FCSMU_FAULT_CHANNEL_SCG_SCM_CRC_ERROR       = 0x20000000U,  /*!< SCG and SCM etc. CRC check error. */
    FCSMU_FAULT_CHANNEL_MAM_WDG_ERROR           = 0x80000000U,  /*!< MAM master access time out error. */
} FCSMU_ChannelAssignmentType;

/**
 * @brief FCSMU Channel ISR callback function prototype
 *
 */
typedef void (*FCSMU_ISRCallbackType)(FCSMU_IQRType eIrqType, uint32_t u32IrqChannel);

typedef struct
{
    bool bEnable;                       /*!< Enable or disable status output. */
    bool eFastMode;                     /*!< Enable or disable fast mode. */
    bool bDivex;						/*!< SOUT Divider Extend Control. */
    FCSMU_SoutControlType eSoutCtrl;    /*!< Configure Sout Control. */
    FCSMU_SoutPolarityType ePolarity;   /*!< Status output polarity. */
    FCSMU_SoutProtocolType eProtocal;   /*!< Status output protocal. */
    uint32_t u32Delaytimer;             /*!< Configure the safe mode request delay in cycles of CLKSAFE. */
    uint32_t u32Divder;                 /*!< Configure the status output divider ratio.
                                             bDevex = 0, SOUT_freq = CLKSAFE_freq/((SOUT_DIV+1)*2*256)
                                             bDevex = 1, SOUT_freq = CLKSAFE_freq/((SOUT_DIV+1)*2*64)
                                         */
    uint32_t u32SoutChannel;            /*!< Configure the status output channel. */
} FCSMU_StatusOutputConfigType;

typedef struct
{
    uint32_t u32WarnTo;                 /*!< FCSMU warning timeoout value. */
    uint32_t u32WarnChannel;            /*!< FCSMU warning channel. */
    uint32_t u32FaultChannel;           /*!< FCSMU fault channel. */
    uint32_t u32WarnInterruptChannel;   /*!< FCSMU warning interrupt channel. */
    uint32_t u32FaultInterruptChannel;  /*!< FCSMU fault interrupt channel. */
    uint32_t u32FaultResetChannel;      /*!< FCSMU fault reset channel. */
    uint32_t u32SoftwareClearedChannel; /*!< FCSMU fault is Cleard by software. */
    FCSMU_ISRCallbackType pISRCallback; /*!< ISR callback. */
} FCSMU_InitCfgType;

/**
 * @brief Init the FCSMU.
 *
 * @param pInitConfig FCSMU initial configuration.
 */
FCSMU_StatusType FCSMU_init(const FCSMU_InitCfgType *pInitConfig);

/**
 * @brief Config the FCSMU status output.
 *
 * @param pInitConfig FCSMU status output configuration.
 */
FCSMU_StatusType FCSMU_ConfigStatusOutput(FCSMU_StatusOutputConfigType *pInitConfig);

/**
 * @brief Generate the CRC.
 *
 */
void FCSMU_CrcGen(void);

/**
 * @brief Query CRC busy status.
 *
 * @return FCSMU_CrcModeType CRC status.
 */
bool FCSMU_IsCrcBusy(void);

/**
 * @brief Configure the FCSMU CRC.
 *
 * @param eMode Crc mode.
 * @return FCSMU_StatusType Status of configuration.
 */
FCSMU_StatusType FCSMU_CrcConfig(FCSMU_CrcModeType eMode);

/**
 * @brief Clear the falut flag.
 *
 * @param u32FaultChannel Channel flag to be cleared.
 * @return FCSMU_StatusType Status of clear.
 */
FCSMU_StatusType FCSMU_ClearFaultFlag(uint32_t u32FaultChannel);

/**
 * @brief Transform state from configuration to normal.
 *
 * @return FCSMU_StatusType Status of Transformation.
 */
FCSMU_StatusType FCSMU_TransStateCTN(void);

/**
 * @brief Transform state from normal to configuration.
 *
 * @return FCSMU_StatusType Status of Transformation.
 */
FCSMU_StatusType FCSMU_TransStateNTC(void);

/**
 * @brief Inject the fault tp fcsmu.
 *
 * @param u32ChannelIndex channel to be injected.
 */
void FCSMU_InjectionFault(uint32_t u32ChannelIndex);

/**
 * @brief Get the fault channels fcsmu.
 *
 * @return Fault channels.
 */
uint32_t FCSMU_GetFaultChannel(void);

/**
 * @brief Get the interrupt state of fcsmu.
 *
 * @return interrupt state.
 */
uint32_t FCSMU_GetIrqState(void);

/**
 * @brief Get the NTF flags of fcsmu.
 *
 * @return NTF flags.
 */
uint32_t FCSMU_GetNtfFlag(void);

/**
 * @brief Get the WTF flags of fcsmu.
 *
 * @return WTF flags.
 */
uint32_t FCSMU_GetWtfFlag(void);

/**
 * @brief Get the NTW flags of fcsmu.
 *
 * @return NTW flags.
 */
uint32_t FCSMU_GetNtwFlag(void);

/** @}*/ /* fc7xxx_driver_fcsmu. */
#endif
