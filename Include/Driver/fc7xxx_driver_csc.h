/**
 * @file fc7xxx_driver_csc.h
 * @author Flagchip085
 * @brief FC7xxx csc driver type definition and API
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0      2024-01-12    Flagchip085     N/A          First version for FC7240
********************************************************************************/
#ifndef _DRIVER_FC7XXX_DRIVER_CSC_H_
#define _DRIVER_FC7XXX_DRIVER_CSC_H_

#include "HwA_csc.h"

/********* Local defines ************/
#define CSC0_AONCLK_128K      128000U
#define CSC0_AONCLK_32K        32000U
#define CSC0_AONCLK_SOSC_32K   32768U
#define CSC0_AONCLK_1K          1000U


/********* Local typedef ************/
/**
 * @brief Stop ack status type
 *
 */
typedef enum
{
    STOPMODE_PROCESSS = 0U,  /*!< The peripheral is processing(not in stop mode) */
    STOPMODE_READY    = 1U   /*!< The peripheral is already in stop mode*/
} CSC_StopModeStatusType;

/** 
 * @brief CSC return status
 *
 */
typedef enum
{
    CSC_E_OK     = 0U,  /*!< Return ok */
    CSC_E_NOT_OK,     	/*!< Return not ok */
	CSC_E_LOCK,			/*!< Return error because the register is locked */
	CSC_E_NO_PERM,		/*!< Return error because the CPU has no permission */
	CSC_E_PARAM			/*!< Return error because the parameter is invalid */
} CSC_RetStatusType;

/**
 * @brief CSC setting target
 *
 */
typedef enum
{
    CSC_STOPACK = 0U,  /*!< stop ack */
    CSC_STOPREQ        /*!< stop request */
} CSC_SetTargetType;

/**
 * @brief CSC stop mode/ack/request control group info
 * @note  Must match with  peripheal enum
 */
typedef enum
{
    CSC_STOP_CTRL_GROUP_0 = 0U,  /*!< CSC stop mode/ack/request control group 0 */
    CSC_STOP_CTRL_GROUP_1,       /*!< CSC stop mode/ack/request control group 1 */
    CSC_STOP_CTRL_GROUP_2,       /*!< CSC stop mode/ack/request control group 2 */
} CSC_PeriphGrpType;

/**
 * @brief CSC0_AONCLKSR clock source info
 *
 */
typedef struct
{
    bool HclkEn;     					  /*!< CPUx HCLOCK Enable */
    CSC_HandShakeModeType eHandShakeMode; /*!< CCMx Handshake Mode */
} CSC_CCMCfgType;

/**
 * @brief Indicate the clock status for each clock source in clock tree list
 * 
 */
typedef enum
{
    CSC0_CLOCK_UNDEFINE = 0U,  /*!< Clock status undefined from power on  */
    CSC0_CLOCK_DISABLE  = 1U,  /*!< clock source set as disabled  */
    CSC0_CLOCK_VALID    = 2U,  /*!< clock set succeed  */
    CSC0_CLOCK_ERROR    = 3U,  /*!< clock set failed  */
    CSC0_CLOCK_UNKNOWN  = 4U
} CSC0_ClockStatusDef;

/** 
 * @brief CSC0 clock source type for clock infomation querry 
 * 
 */
typedef enum
{
    CSC0_AON32K_CLK    = 0U,  /*!< AON32K_CLK */
    CSC0_RTC_CLK       = 1U,  /*!< RTC_CLK */
    CSC0_AON_CLK       = 2U,  /*!< AON_CLK */
    CSC0_CLKOUT_CLK    = 3U,  /*!< CLKOUT_CLK */
    CSC0_END_OF_CLOCKS = 4U   /*!< End of CSC0 clocks */
} CSC0_ClkSrcType;

/** 
 * @brief CSC0_SMU control group info
 * 
 */
typedef enum
{
    CSC0_SMU_CTRL_GROUP_0 = 0U,  /*!< CSC0_SMU control group 0 */
    CSC0_SMU_CTRL_GROUP_1,       /*!< CSC0_SMU control group 1 */
    CSC0_SMU_CTRL_GROUP_4,       /*!< CSC0_SMU control group 4 */
	CSC0_SMU_CTRL_GROUP_5        /*!< CSC0_SMU control group 5 */
} CSC0_SmuCtrlGrpType;

/** 
 * @brief Module clock status and frequency record structure 
 * 
 * */
typedef struct
{
    CSC0_ClockStatusDef eClkStatus;  /*!< Indicate the clock status for each clock source in clock tree list */
    uint32_t            u32Freq;     /*!< frequency value */
} CSC0_ClockInfoType;

/** 
 * @brief Data type for register CSC0_CLKOUT_CTRL,mainly focus on CLKOUT setting 
 * 
 */
typedef struct
{
    bool bEnable;                      /*!< CSC0 ClockOut enable */
    CSC0_ClockOutSrcType  eClkOutSrc;  /*!< CSC0 ClockOut source select */
    CSC0_ClockOutDivType  eDivider;    /*!< CSC0 ClockOut divide ratio */
} CSC0_ClkoutType;

/** 
 * @brief CSC0_AONCLKSR clock source info
 * 
 */
typedef struct
{
    CSC0_AON32KClkSrcType eAon32KSel;  /*!< CSC0 32 KHz Always-on Clock Source Select */
    CSC0_RTCClkSrcType    eRtcSel;     /*!< CSC0 RTC Clock Source Select */
    CSC0_AONClkSrcType    eAonSel;     /*!< CSC0 AON Clock Source Select */
} CSC0_AONCLKSRType;

/**
 * @brief CSC0_LP_WAKEUP low power wakeup configure type
 *
 */
typedef struct
{
	CSC0_LPWakeupSrcType eCfgGrp0;  /*!< LP_WAKEUP_PAD0 Configure Source */
	CSC0_LPWakeupSrcType eCfgGrp1;  /*!< LP_WAKEUP_PAD1 Configure Source */
	CSC0_LPWakeupSrcType eCfgGrp2;  /*!< LP_WAKEUP_PAD2 Configure Source */
	CSC0_LPWakeupSrcType eCfgGrp3;  /*!< LP_WAKEUP_PAD3 Configure Source */
	CSC0_LPWakeupSrcType eCfgGrp4;  /*!< LP_WAKEUP_PAD4 Configure Source */
	CSC0_LPWakeupPolType ePolGrp0;  /*!< LP_WAKEUP_CFG0 Wakeup Polarity */
	CSC0_LPWakeupPolType ePolGrp1;  /*!< LP_WAKEUP_CFG1 Wakeup Polarity */
	CSC0_LPWakeupPolType ePolGrp2;  /*!< LP_WAKEUP_CFG2 Wakeup Polarity */
	CSC0_LPWakeupPolType ePolGrp3;  /*!< LP_WAKEUP_CFG3 Wakeup Polarity */
	CSC0_LPWakeupPolType ePolGrp4;  /*!< LP_WAKEUP_CFG4 Wakeup Polarity */
} CSC0_LPWakeupCfgType;


/********* Local function ************/
/**
 * @brief set clock out. with clock out pin configure, the clock would be monitored.
 *        This Function may combined with SCG_ClkOut setting
 *        need to call SCG_SetClkOut,if clock out source set to SCG_CLKOUT. *
 * @param pCsc0ClkOut to Csc0ClkOut instance for clock out configuration
 * @param bLockStatus to lock current register
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_LOCK:    The register has been locked and can not be written
 * @note  configuration sequence:
 *           1. Disable CLKOUTEN
 *           2. Set CLKOUTSEL
 *           3. Enable CLKOUTEN
 */
CSC_RetStatusType CSC0_SetClockOut(const CSC0_ClkoutType *const pCsc0ClkOut, bool bLockStatus);

/**
 * @brief set always on clock source configuration include AON32K, RTC, AONCLK clock.
 *
 * @param pAonclkSrcType pointer to AONCLKSR instance for AON clock source configuration
 * @param bLockStatus to lock current register
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_LOCK:    The register has been locked and can not be written
 */
CSC_RetStatusType CSC0_SetAonClkSrc(const CSC0_AONCLKSRType *const pAonclkSrcType, bool bLockStatus);

/**
 * @brief Report the clock source status and frequency configured in MCU run time.
 *        The clock frequency and status would change by clock set function.
 *
 * @param eClkkName: the CSC0 clock source to query
 * @param pFreq: frequency variable point to get the frequency value
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  eClkkName invalid
 */
CSC_RetStatusType CSC0_GetCSC0ClockFreq(CSC0_ClkSrcType eClkkName, uint32_t *const pFreq);

/**
 * @brief SCG MAM stall request.
 * @details Need to assert the SCG_STALL to stall MAM when configuring the SCG clock source.
 *
 * @param bEnable: true asserts SCG MAM stall request
 * 				   false do not asserts SCG MAM stall request
 * @param bLockStatus: Lock the register.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  eClkkName invalid
 */
CSC_RetStatusType CSC0_ScgMAMStallRequest(bool bEnable, bool bLockStatus);

/**
 * @brief Set request to SMU of group 0.
 *
 * @param u32Value Value to be set(the or bits defined in CSC_SMU_CtrlGrp0Type,do not involve lock bit)
 * @param bLockStatus Lock the register.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  The u32Value contains invalid bits
 * 			CSC_E_LOCK:    The register has been locked
 */
CSC_RetStatusType CSC0_SetReqToSMUGrp0(uint32_t u32Value, bool bLockStatus);

/**
 * @brief Set request to SMU of group 1.
 *
 * @param u32Value Value to be set(the or bits defined in CSC_SMU_CtrlGrp1Type,do not involve lock bit)
 * @param bLockStatus Lock the register.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  The u32Value contains invalid bits
 * 			CSC_E_LOCK:    The register has been locked
 */
CSC_RetStatusType CSC0_SetReqToSMUGrp1(uint32_t u32Value, bool bLockStatus);

/**
 * @brief Set request to SMU of group 4.
 *
 * @param u32Value Value to be set(the or bits defined in CSC_SMU_CtrlGrp4Type,do not involve lock bit)
 * @param bLockStatus Lock the register.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:   The u32Value contains invalid bits
 * 			CSC_E_LOCK:    The register has been locked
 */
CSC_RetStatusType CSC0_SetReqToSMUGrp4(uint32_t u32Value, bool bLockStatus);

/**
 * @brief Set request to SMU of group 5.
 *
 * @param u32Value Value to be set(the or bits defined in CSC_SMU_CtrlGrp5Type,do not involve lock bit)
 * @param bLockStatus Lock the register.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  The u32Value contains invalid bits
 * 			CSC_E_LOCK:    The register has been locked
 */
CSC_RetStatusType CSC0_SetReqToSMUGrp5(uint32_t u32Value, bool bLockStatus);

/**
 * @brief Set request to SMU .
 *
 * @param eCtrlGrp CSC0_SMU control group
 * @param u32Value Value to be set(the or bits defined in CSC_SMU_CtrlGrp5Type,do not involve lock bit)
 * @param bLockStatus Lock the register.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_PARAM:   The eCtrlGrp is invalid
 * 			CSC_E_NOT_OK:  The u32Value contains invalid bits
 * 			CSC_E_LOCK:    The register has been locked
 * @note   Group must be matched with u32Value which select from CSC0_SmuCtrlGrpType
 */
CSC_RetStatusType CSC0_SetReqToSMU(CSC0_SmuCtrlGrpType eCtrlGrp, uint32_t u32Value, bool bLockStatus);

/**
 * @brief Configure the low power wakeup PAD output in CSC0_LP_WAKEUP register.
 *
 * @param eLPWakeupCfg: the low power wakeup PAD source and polarity configuration
 * @param bLockStatus: Lock the register.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_LOCK:    The WPB of CSCx_STOP_MODERx is already locked
 */
CSC_RetStatusType CSC0_LP_WakeupPadOutputCfg(const CSC0_LPWakeupCfgType * const eLPWakeupCfg, bool bLockStatus);

/**
 * @brief Set CPU stop mode control permission.
 * @detail This API is used to set the CPU write permission of a CPU's stop mode registers.
 * eg.If the CPU(eTargetCpuType) enter stop mode, it acknowledges the peripherals according to the configuration
 *    in CSCx_STOP_MODERy (x: (CPUID) range[0] , y:(GROUP) range[0,1,2]), and the CPU(eCtrlCpuType)
 *    has the write permission of CSCx_STOP_MODERy registers, the permission is controlled by this API.
 *
 * @param eTargetCpuType The target CPU to set.
 * @param eCtrlCpuType   The CPU that has the write permission to the CSCx_STOP_MODERy register.
 * @param ePeriphGrp     Peripheral group (range:0,1,2)
 * @param bLockStatus    Lock the WPB of CSCx_STOP_MODERx.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  eTargetCpuType invalid
 * 			CSC_E_LOCK:    The WPB of CSCx_STOP_MODERx is already locked
 */
CSC_RetStatusType CSC_SetStopModeAckPermission(CSC_WPB_CpuType eTargetCpuType, CSC_WPB_CpuType eCtrlCpuType,
										 	   CSC_PeriphGrpType ePeriphGrp, bool bLockStatus);

/**
 * @brief Set CPU stop mode request control permission.
 * @detail This API is used to set the CPU write permission of a CPU's stop mode request registers
 *         to generate a stop request to peripherals
 *
 * @param eTargetCpuType The target CPU to acknowledges stop mode to the enabled peripherals.
 * @param eCtrlCpuType   The CPU that has the write permission to the CSCx_STOP_REQRx register.
 * @param ePeriphGrp     Peripheral group (range:0,1,2)
 * @param bLockStatus    Lock the WPB of CSCx_STOP_REQRx.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  eTargetCpuType invalid
 * 			CSC_E_LOCK:    The WPB of CSCx_STOP_REQRx is already locked
 */
CSC_RetStatusType CSC_SetStopRequestPermission(CSC_WPB_CpuType eTargetCpuType, CSC_WPB_CpuType eCtrlCpuType,
										 	   CSC_PeriphGrpType ePeriphGrp, bool bLockStatus);

/**
 * @brief Set the stop mode ack of peripheral group 0 in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the ePeriphType when entering stop mode.
 * @param ePeriphType the peripheral to enable or disable the stop mode ACK
 * @param bEnable true: enable the stop mode ACK
 * 				  false: disable the stop mode ACK
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  eTargetCpuType invalid
 * 			CSC_E_NO_PERM: Current CPU has no permission to access the register
 */
CSC_RetStatusType CSC_SetStopModeAckGrp0(CSC_WPB_CpuType eTargetCpuType, CSCx_Reg0_PeriphType ePeriphType, bool bEnable);

/**
 * @brief Set the stop request of peripheral group 0 in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the ePeriphType when entering stop mode.
 * @param ePeriphType the peripheral to set stop request
 * @param bEnable true: set the stop request
 * 				  false: clear the stop request
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  eTargetCpuType invalid
 * 			CSC_E_NO_PERM: Current CPU has no permission to access the register
 */
CSC_RetStatusType CSC_SetStopRequestGrp0(CSC_WPB_CpuType eTargetCpuType, CSCx_Reg0_PeriphType ePeriphType, bool bEnable);

/**
 * @brief Set the stop mode ACK of peripheral group 1 in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the ePeriphType when entering stop mode.
 * @param ePeriphType the peripheral to enable or disable the stop mode ACK
 * @param bEnable true: enable the stop mode ACK
 * 				  false: disable the stop mode ACK
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  eTargetCpuType invalid
 * 			CSC_E_NO_PERM: Current CPU has no permission to access the register
 */
CSC_RetStatusType CSC_SetStopModeAckGrp1(CSC_WPB_CpuType eTargetCpuType, CSCx_Reg1_PeriphType ePeriphType, bool bEnable);

/**
 * @brief Set the stop request of peripheral group 1 in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the ePeriphType when entering stop mode.
 * @param ePeriphType the peripheral to set stop request
 * @param bEnable true: set the stop request
 * 				  false: clear the stop request
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  eTargetCpuType invalid
 * 			CSC_E_NO_PERM: Current CPU has no permission to access the register
 */
CSC_RetStatusType CSC_SetStopRequestGrp1(CSC_WPB_CpuType eTargetCpuType, CSCx_Reg1_PeriphType ePeriphType, bool bEnable);

/**
 * @brief Set the stop mode ACK of peripheral group 2 in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the ePeriphType when entering stop mode.
 * @param ePeriphType the peripheral to enable or disable the stop mode ACK
 * @param bEnable true: enable the stop mode ACK
 * 				  false: disable the stop mode ACK
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  eTargetCpuType invalid
 * 			CSC_E_NO_PERM: Current CPU has no permission to access the register
 */
CSC_RetStatusType CSC_SetStopModeAckGrp2(CSC_WPB_CpuType eTargetCpuType, CSCx_Reg2_PeriphType ePeriphType, bool bEnable);

/**
 * @brief Set the stop request of peripheral group 2 in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the ePeriphType when entering stop mode.
 * @param ePeriphType the peripheral to set stop request
 * @param bEnable true: set the stop request
 * 				  false: clear the stop request
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  eTargetCpuType invalid
 * 			CSC_E_NO_PERM: Current CPU has no permission to access the register
 */
CSC_RetStatusType CSC_SetStopRequestGrp2(CSC_WPB_CpuType eTargetCpuType, CSCx_Reg2_PeriphType ePeriphType, bool bEnable);

/**
 * @brief Set the stop mode ACK of all group peripherals in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the peripherals when entering stop mode.
 * @param ePeriphGrp the group of peripherals to set the stop mode ACK value
 * @param u32Value the CSCx_STOP_MODERx register value
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  eTargetCpuType invalid
 * 			CSC_E_PARAM:   ePeriphGrp or u32Value invalid
 * 			CSC_E_NO_PERM: Current CPU has no permission to access the register
 */
CSC_RetStatusType CSC_SetStopModeAck(CSC_WPB_CpuType eTargetCpuType, CSC_PeriphGrpType ePeriphGrp, uint32_t u32Value);

/**
 * @brief Set the stop request of all group peripherals in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the peripherals when entering stop mode.
 * @param ePeriphGrp the group of peripherals to set the stop request value
 * @param u32Value the CSCx_STOP_REQRx register value
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:     The API is successfully called
 * 			CSC_E_NOT_OK: eTargetCpuType invalid
 * 			CSC_E_PARAM:  ePeriphGrp or u32Value invalid
 * 			CSC_E_NO_PERM: Current CPU has no permission to access the register
 */
CSC_RetStatusType CSC_SetStopRequest(CSC_WPB_CpuType eTargetCpuType, CSC_PeriphGrpType ePeriphGrp, uint32_t u32Value);

/**
 * @brief Get the stop Acknowledge status of peripherals group0 in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the peripherals when entering stop mode.
 * @param ePeriphType the peripheral to get stop acknowledge status
 * @param pStatus Output parameter,to save the stop ACK status of the peripheral indicated by ePeriphType
 * 				  true:  Stop acknowledge is asserted (the module is in Stop mode)
 *			      false: Stop acknowledge is not asserted
 * @return CSC_RetStatusType Operation success/failed
 * 			CSC_E_OK:     The API is successfully called
 * 			CSC_E_NOT_OK: eTargetCpuType invalid
 */
CSC_RetStatusType CSC_GetStopAckStatusGrp0(CSC_WPB_CpuType eTargetCpuType,CSCx_Reg0_PeriphType ePeriphType, bool * const pStatus);

/**
 * @brief Get the stop Acknowledge status of peripherals group1 in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the peripherals when entering stop mode.
 * @param ePeriphType the peripheral to get stop acknowledge status
 * @param pStatus Output parameter,to save the stop ACK status of the peripheral indicated by ePeriphType
 * 				  true:  Stop acknowledge is asserted (the module is in Stop mode)
 *			      false: Stop acknowledge is not asserted
 * @return CSC_RetStatusType Operation success/failed
 * 			CSC_E_OK:     The API is successfully called
 * 			CSC_E_NOT_OK: eTargetCpuType invalid
 */
CSC_RetStatusType CSC_GetStopAckStatusGrp1(CSC_WPB_CpuType eTargetCpuType, CSCx_Reg1_PeriphType ePeriphType, bool * const pStatus);

/**
 * @brief Get the stop Acknowledge status of peripherals group2 in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the peripherals when entering stop mode.
 * @param ePeriphType the peripheral to get stop acknowledge status
 * @param pStatus Output parameter,to save the stop ACK status of the peripheral indicated by ePeriphType
 * 				  true:  Stop acknowledge is asserted (the module is in Stop mode)
 *			      false: Stop acknowledge is not asserted
 * @return CSC_RetStatusType Operation success/failed
 * 			CSC_E_OK:     The API is successfully called
 * 			CSC_E_NOT_OK: eTargetCpuType invalid
 */
CSC_RetStatusType CSC_GetStopAckStatusGrp2(CSC_WPB_CpuType eTargetCpuType,CSCx_Reg2_PeriphType ePeriphType, bool * const pStatus);

/**
 * @brief Get the stop Acknowledge status of all group peripherals in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the peripherals when entering stop mode.
 * @param ePeriphType the peripheral to get stop acknowledge status
 * @param pU32Status Output parameter,to save the stop ACK status of all the peripherals in the group indicated by ePeriphGrp.
 * 				     The corresponding bit is 1, indicates that stop acknowledge is asserted,and 0 not asserted.
 * @return CSC_RetStatusType Operation success/failed
 * 			CSC_E_OK:     The API is successfully called
 * 			CSC_E_NOT_OK: eTargetCpuType invalid
 */
CSC_RetStatusType CSC_GetStopAckStatus(CSC_WPB_CpuType eTargetCpuType,CSC_PeriphGrpType ePeriphGrp, uint32_t * const pU32Status);

/**
 * @brief Set the CPU write permission of CSCx_CCMx_CFG register in CSC.
 *
 * @param eTargetCpuType The target CPU controlled by CSCx_CCMx_CFG register.
 * @param eCtrlCpuType   The CPU that has the permission to access the CSCx_CCMx_CFG register.
 * @param bLockStatus    Lock the WPB of CSCx_CCMx_CFG register.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:     The API is successfully called
 * 			CSC_E_NOT_OK: eTargetCpuType invalid
 * 			CSC_E_LOCK:   WPB is locked(WPB_LOCK set 1) and can not be written
 */
CSC_RetStatusType CSC_SetCCMCfgPermission(CSC_WPB_CpuType eTargetCpuType, CSC_WPB_CpuType eCtrlCpuType, bool bLockStatus);

/**
 * @brief Set the CCM configuration of CPUx indicated by eTargetCpuType.
 *
 * @param eTargetCpuType The target CPU controlled by CSCx_CCMx_CFG register.
 * @param pCCMCfg   Pointer to the configuration of CSCx_CCMx_CFG register.
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:     The API is successfully called
 * 			CSC_E_NOT_OK: eTargetCpuType invalid
 * 			CSC_E_LOCK:   Current CPU has no permission to access the register
 */
CSC_RetStatusType CSC_SetCCMConfiguration(CSC_WPB_CpuType eTargetCpuType,const CSC_CCMCfgType *const pCCMCfg);

/**
 * @brief Get the CCM stop clock status.
 *
 * @param eTargetCpuType The target CPU controlled by CSCx_CCMx_CFG register.
 * @param eCCMType CCM stop clock type.
 * @param pStatus Pointer to memory to save the clock status.
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:     The API is successfully called
 * 			CSC_E_NOT_OK: eTargetCpuType invalid
 */
CSC_RetStatusType CSC_GetCCMStopClockStatus(CSC_WPB_CpuType eTargetCpuType, CSCx_CCM_StopClockType eCCMType, bool * const pStatus);

/**
 * @brief Set the CPU write permission of CSCx_CPUx_INT register in CSC.
 *
 * @param eTargetCpuType The target CPU controlled by CSCx_CPUx_INT register.
 * @param eCtrlCpuType   The CPU that has the permission to access the CSCx_CPUx_INT register.
 * @param bLockStatus    Lock the WPB of CSCx_CPUx_INT register.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:     The API is successfully called
 * 			CSC_E_NOT_OK: eTargetCpuType invalid
 * 			CSC_E_LOCK:   WPB is locked(WPB_LOCK set 1) and can not be written
 */
CSC_RetStatusType CSC_SetCpuIntPermission(CSC_WPB_CpuType eTargetCpuType, CSC_WPB_CpuType eCtrlCpuType, bool bLockStatus);

/**
 * @brief Generate software interrupt via CSCx_CPUx_INT.
 *
 * @param eTargetCpuType The target CPU to generate interrupt.
 * @param bEnable  true:  Generate software interrupt.
 * 				   false: Do not generate software interrupt.
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:     The API is successfully called
 * 			CSC_E_NOT_OK: eTargetCpuType invalid
 * 			CSC_E_LOCK:   The current CPU has no permission to access this bit
 */
CSC_RetStatusType CSC_CpuSwInterruptGen(CSC_WPB_CpuType eTargetCpuType, bool bEnable);


#endif /* End of _DRIVER_CSC_H_ */
