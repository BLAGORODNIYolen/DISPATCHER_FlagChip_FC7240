/**
 * @file fc7xxx_driver_cmp.h
 * @author Flagchip
 * @brief FC7xxx CMP driver type definition and API
 * @version 0.1.0
 * @date 2024-01-15
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2024-01-15    Flagchip0126   N/A          First version for FC7240
********************************************************************************/
#ifndef _DRIVER_FC7XXX_DRIVER_CMP_H_
#define _DRIVER_FC7XXX_DRIVER_CMP_H_
#include "HwA_cmp.h"



#if defined(__cplusplus)
extern "C" {
#endif

/********* Local typedef ************/

/**
 * @brief The CMP complete interrupt callback function prototype
 *
 */
typedef void (*CMP_CompleteIntCallback)(void);

/**
 * @brief The instance index of the CMP Dac parts
 */
typedef struct
{
    bool bDacEn;                           /*!< CMP DAC enable/disable */
    uint8_t u8DacData;                     /*!< CMP DAC output voltage, output = Vin / 256 * (aDacData + 1) */
    CMP_DacEnableSrcType eDacEnsrc;        /*!< CMP DAC enable selection(DCR,CCR0) */
    CMP_DacVinRefSelType eVinRefSel;       /*!< CMP DAC high voltage reference (vrefh0,vrefh1) */
} CMP_DacType;

/**
 * @brief The instance index of the CMP Mux parts
 */
typedef struct
{
    CMP_INSrcSelType eINPSel;                /*!< CMP input positive select(DAC or analog mux) */
    CMP_INSrcSelType eINNSel;                /*!< CMP input negative select(DAC or analog mux) */
    CMP_MuxSelType ePSelMux;                 /*!< CMP input positive mux select, this is ignored in channel scan mode */
    CMP_MuxSelType eNSelMux;                 /*!< CMP input negative mux select, this is ignored in channel scan mode */
    CMP_MuxSelType eChannelScanFixedChannel; /*!< CMP channel scan fixed channel select, this is ignored if DAC is enabled */
    CMP_PortSelType eChannelScanFixedPort;   /*!< CMP channel scan fixed channel port select */
} CMP_MuxType;

/**
 * @brief The instance index of the CMP Comparator parts
 */
typedef struct
{
    bool bStopModEn;                       /*!< CMP stop mode enable */
    bool bOutToPackagePinEn;               /*!< CMP output to package pin enable */
    bool bWinSampleInvertEn;               /*!< CMP window/sample signal invert enable */
    bool bEventCloseWinEn;                 /*!< CMP out event close window enable */
    bool bAnalogConfTransByp;			   /*!< CMP analog configuration transition bypass enable */
    uint16 u16AnalogConfTransBypCnt;	   /*!< Target count value for bypass function */
    uint8_t u8FilterPeriod;                /*!< CMP set Filter Sample Period */
    CMP_ModSelType eModSel;                /*!< CMP set function mode */
    CMP_InvertType eInvert;                /*!< CMP output Invert or not(invert, non-invert) */
    CMP_OutSelectType eOutSelect;          /*!< CMP output filter or not(CMPO = CMPOUT_FILTER/CMPOUT_WIN) */
    CMP_OutWinLevelType eOutWinLevel;      /*!< CMP output when window close(hold, userdefine) */
    CMP_OutWinLevel_UserDefType eOutWin;   /*!< CMP output under userdefine (0, 1) */
    CMP_EventType eEventSelect;            /*!< CMP output event cause window close(rising edge, falling edge) */
    CMP_FilterCntType eFilterCnt;          /*!< CMP filter count numbers(0,1,2,3,4) */
    CMP_SpeedModSelType eSpeedMod;         /*!< CMP speed mode(low,high) */
    CMP_HystCtrlType eHystCrtl;            /*!< CMP hysteresis internal control(0,1,2,3) */
} CMP_ComparatorType;

/**
 * @brief Defines the comparator interrupt configuration
 *
 * @note This structure is used to configure CMP interrupt
 *       Implements : CMP_InterruptType
 */
typedef struct
{
    bool bRisingIntEn;                            /*!< Enable/disable rising interrupt  */
    bool bFallingIntEn;                           /*!< Enable/disable falling interrupt  */
    bool bChannelScanFlagIntEn;                   /*!< Enable/disable channel scan flag interrupt  */
    CMP_CompleteIntCallback pInterrupterNotify;   /*!< CMP complete interrupt callback */
} CMP_InterruptType;

/**
 * @brief Defines the comparator dma configuration
 *
 * @note This structure is used to configure CMP dma
 *       Implements : CMP_DmaType
 */
typedef struct
{
    bool bRisingDmaEn;                            /*!< Enable/disable rising edge trigger dma  */
    bool bFallingDmaEn;                           /*!< Enable/disable falling edge trigger dma  */
} CMP_DmaType;

/**
 * @brief Defines the comparator channel selected in channel scan mode
 *
 * @note This structure is used to configure a CMP channel that want to be enabled in channel scan sequence
 *       Implements : CMP_ChannelScanChannelCfgType
 */
typedef struct
{
    CMP_MuxSelType eChannel;		/*!< Enabled channel */
    bool bPreSetState;				/*!< Preset state for the given channel */
    bool bCurState;                 /*!< Current state for the given channel */
} CMP_ChannelScanChannelCfgType;

/**
 * @brief Defines the comparator channel scan configuration
 *
 * @note This structure is used to configure CMP channel scan
 *       Implements : CMP_ChannelScanType
 */
typedef struct
{
    uint8_t u8ChannelScanInitModulus;			/*!<Compartor and DAC initialization delay modulus */
    uint8_t u8ChannelScanNumOfSampleClocks;		/*!<Number of smaple clocks later the the sample operation takes place */
    bool bComparisonResultAutoClear;			/*!<Enable/disable comparison result auto clear */
} CMP_ChannelScanType;

/**
 * @brief Defines the comparator configuration
 *
 * @note This structure is used to configure CMP
 *       Implements : CMP_InitType
 */
typedef struct
{
    CMP_DacType tDacConfig;                /*!< CMP DAC configure */
    CMP_MuxType tMuxConfig;                /*!< CMP MUX configure */
    CMP_ComparatorType tComparatorConfig;  /*!< CMP comparator configure */
    CMP_ChannelScanType tChannelScanConfig;/*!< CMP channel scan configure */
} CMP_InitType;


/********* Local function ************/
/**
 * @brief set CMP module enable
 *
 * @param eInstance the CMP instance to use
 */
void CMP_Enable(const CMP_InstanceType eInstance);

/**
 * @brief set CMP module disable
 *
 * @param eInstance the CMP instance to use
 */
void CMP_Disable(const CMP_InstanceType eInstance);

/**
 * @brief set CMP module channel scan mode enable
 *
 * @param eInstance the CMP instance to use
 */
void CMP_CSEnable(const CMP_InstanceType eInstance);

/**
 * @brief set CMP module channel scan mode disable
 *
 * @param eInstance the CMP instance to use
 */
void CMP_CSDisable(const CMP_InstanceType eInstance);

/**
 * @brief set CMP init
 *
 * @param eInstance the CMP instance to use
 * @param pInitCfg the CMP init type
 */
void CMP_Init(const CMP_InstanceType eInstance, const CMP_InitType *const pInitCfg);

/**
 * @brief set CMP init interrupt
 *
 * @param eInstance the CMP instance to use
 * @param pInterruptCfg the CMP init interrupter type
 */
void CMP_InitInterrupt(const CMP_InstanceType eInstance, const CMP_InterruptType *const pInterruptCfg);

/**
 * @brief set CMP init interrupt dma
 *
 * @param eInstance the CMP instance to use
 * @param pInterruptDmaCfg the CMP init interrupt  dma type
 */
void CMP_InitInterrupt_Dma(const CMP_InstanceType eInstance, const CMP_DmaType *const pInterruptDmaCfg);

/**
 * @brief get CMP filtered output
 *
 * @param eInstance the CMP instance to use
 * @return CMP filtered output
 */
bool CMP_GetCmpOut(const CMP_InstanceType eInstance);

/**
 * @brief set CMP Dac output
 *
 * @param eInstance the CMP instance to use
 * @param eDacData input voltage value
 * @note voltage = (VinRef / 256) * (eDacData + 1)
 */
void CMP_SetDacData(const CMP_InstanceType eInstance, uint8_t u8Data);

/**
 * @brief get CMP interrupter flag status
 *
 * @param eInstance the CMP instance to use
 * @return CMP  output status
 */
CMP_OutStatus CMP_GetOutFlagStatus(const CMP_InstanceType eInstance);

/**
 * @brief get CMP channel scan flag status
 *
 * @param eInstance the CMP instance to use
 * @return CMP channel scan status
 */
bool CMP_GetChannelScanFlagStatus(const CMP_InstanceType eInstance);

/**
 * @brief clear CMP interrupter flag
 *
 * @param eInstance the CMP instance to use
 */
void CMP_ClearIntFlag(const CMP_InstanceType eInstance);

/**
 * @brief set CMP rising & falling edge interrupter enable/disable
 *
 * @param eInstance the CMP instance to use
 * @param bRisingEn rising edge enable/disable flag
 * @param bFallingEn falling edge enable/disable flag
 */
void CMP_SetIntEn(const CMP_InstanceType eInstance, const CMP_InterruptType *const pInterruptCfg);

/**
 * @brief set CMP dma enable
 *
 * @param eInstance the CMP instance to use
 */
void CMP_DmaEnable(const CMP_InstanceType eInstance);

/**
 * @brief set CMP dma disable
 *
 * @param eInstance the CMP instance to use
 */
void CMP_DmaDisable(const CMP_InstanceType eInstance);

/**
 * @brief set CMP channel scan channels
 *
 * @param eInstance the CMP instance to use
 * @param s_tChnCfg the structure array of CMP channel channels
 * @param u8ChnCnt the length of s_tChnCfg array
 */
void CMP_SetCSChannls(const CMP_InstanceType eInstance, const CMP_ChannelScanChannelCfgType s_tChnCfg[], const uint8_t u8ChnCnt);

/**
 * @brief get CMP channel scan channels out
 *
 * @param eInstance the CMP instance to use
 * @param s_tChnCfg the structure array of CMP channel channels
 * @param u8ChnCnt the length of s_tChnCfg array
 */
void CMP_GetCSChannlsOut(const CMP_InstanceType eInstance, CMP_ChannelScanChannelCfgType s_tChnCfg[], const uint8_t u8ChnCnt);

/**
 * @brief get CMP channel scan status
 *
 * @param eInstance the CMP instance to use
 */
bool CMP_GetCmpCSActive(const CMP_InstanceType eInstance);

/* fc7xxx_driver_cmp */
#ifdef __cplusplus
}
#endif
#endif /* _DRIVER_FC4XXX_DRIVER_CMP_H_ */
