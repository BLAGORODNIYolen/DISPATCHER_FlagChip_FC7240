/**
 * @file fc7xxx_driver_ftu.h
 * @author Flagchip070
 * @brief FC7xxx FTU driver type definition and API
 * @version 0.1.0
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2022-11-15    Flagchip070    N/A          First version for FC7300
********************************************************************************/

#ifndef _DRIVER_FC4XXX_DRIVER_FTU_H_
#define _DRIVER_FC4XXX_DRIVER_FTU_H_
#include "HwA_ftu.h"
#include "stddef.h"
#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup fc7xxx_driver_ftu
 * @{
 */

/**
 * @name  FTU Channel Bit Flag
 * @brief Bit of channel indicate channel number
 *
 * @{
 */
#define BIT_FTU_CHANNEL_0   0x01U
#define BIT_FTU_CHANNEL_1   0x02U
#define BIT_FTU_CHANNEL_2   0x04U
#define BIT_FTU_CHANNEL_3   0x08U
#define BIT_FTU_CHANNEL_4   0x10U
#define BIT_FTU_CHANNEL_5   0x20U
#define BIT_FTU_CHANNEL_6   0x40U
#define BIT_FTU_CHANNEL_7   0x80U
/** @}*/

/**
 * @name  FTU Fault Bit Flag
 * @brief Bit of fault flag
 *
 * @{
 */
#define FTU_FAULT_INPUT_0    0x01U
#define FTU_FAULT_INPUT_1    0x02U
/** @}*/

/**
 * @brief Max number of Ftu fault
 *
 */
#define FTU_FAULT_COUNT			2u

/**
 * @brief Max number of Ftu input count
 *
 */
#define FTU_INPUT_FILTER_COUNT	4u
/**
 * @brief FTU operation return values
 *
 */
typedef enum
{
    FTU_STATUS_SUCCESS 				= 0U,	/*!< The FTU operation is success */
    FTU_STATUS_PARAM_INVALID,				/*!< The FTU operation is failed because of parameter error */
	FTU_STATUS_NO_CLOCK_SOURCE,				/*!< The FTU operation is failed because of instance clock source is not set */
} FTU_StatusType;

/**
 * @brief The FTU overflow and reload point callback function prototype
 *
 */
typedef void (*FTU_InterruptCallBackType)(void);

/**
 * @brief The FTU fault callback function prototype
 *
 */
typedef void (*FTU_FaultCallBackType)(uint32_t);

/**
 * @brief The FTU channel callback function prototype
 *
 */
typedef void (*FTU_ChannelCallBackType)(uint32_t, uint32_t);

/**
 * @brief The instance index of the FTU peripheral
 *
 */
typedef enum
{
    FTU_INSTANCE_0 = 0U,
    FTU_INSTANCE_1,
    FTU_INSTANCE_2,
    FTU_INSTANCE_3,
    FTU_INSTANCE_4,
    FTU_INSTANCE_5,
    FTU_INSTANCE_6,
    FTU_INSTANCE_7,
} FTU_InstanceType;

/**
 * @brief The channel index of the FTU peripheral
 *
 */
typedef enum
{
    FTU_CHANNEL_0 = 0U,
    FTU_CHANNEL_1,
    FTU_CHANNEL_2,
    FTU_CHANNEL_3,
    FTU_CHANNEL_4,
    FTU_CHANNEL_5,
    FTU_CHANNEL_6,
    FTU_CHANNEL_7
} FTU_ChannelType;

/**
 * @brief The clock source of FTU peripheral
 *
 */
typedef enum
{
    FTU_NO_CLK = 0U,			 	/*!< No clock selected */
    FTU_INTERNAL_CLK = 1U,			/*!< FTU input clock */
    FTU_EXTERNAL_CLK0 = 3U,			/*!< External pin 0 input clock */
    FTU_EXTERNAL_CLK1 = 4U,			/*!< External pin 1 input clock */
    FTU_EXTERNAL_CLK2 = 5U			/*!< External pin 2 input clock */
} FTU_ClkSrcType;

/**
 * @brief The channel operation of output compare mode
 *
 */
typedef enum
{
    FTU_OUTPUT_TOGGLE_PIN = 0U,		/*!< Toggle Output on match */
    FTU_OUTPUT_CLEAR_PIN,			/*!< Clear Output on match */
    FTU_OUTPUT_SET_PIN				/*!< Set Output on match */
} FTU_OutputComparePinModeType;

/**
 * @brief The initial level of the output compare channel
 *
 */
typedef enum
{
	FTU_OUTPUT_CMP_INIT_LOW = 0U,	/*!< The initial level is low */
	FTU_OUTPUT_CMP_INIT_HIGH,		/*!< The initial level is high */
} FTU_OutputCompareInitLevelType;

/**
 * @brief The channel operation of PWM mode
 *
 */
typedef enum
{
    FTU_PWM_HIGH_TRUE_PULSE 	= 0U,		/*!< High-true pulses in PWM */
    FTU_PWM_LOW_TRUE_PULSE,					/*!< Low-true pulses in PWM */
} FTU_PwmPinModeType;

/**
 * @brief PWM Aligned Mode
 *
 */
typedef enum
{
	FTU_EDGE_ALIGNED_PWM 	= 0u,				/*!< Edge-Aligned PWM */
	FTU_CENTER_ALIGNED_PWM						/*!< Center-Aligned PWM */
}FTU_PwmAlignedType;

/**
 * @brief The measurement is single or continuous
 *
 */
typedef enum
{
	FTU_MEASURE_SINGLE_MODE			= 0u,		/*!< Single mode */
	FTU_MEASURE_CONTINUOUS_MODE					/*!< Continuous mode */
} FTU_MeasureContModeType;

/**
 * @brief Timing of start measurement
 *
 */
typedef enum
{
	FTU_MEASURE_START_AFTER_EDGE		= 0u,	/*!< The channel starts measuring after the first edge is detected */
	FTU_MEASURE_START_IMMEDIATELY				/*!< The measurement starts immediately after activating the channel */
}FTU_MeasureStartModeType;

/**
 * @brief The reload point flag of FTU peripheral
 *
 */
typedef enum
{
	FTU_RELOAD_POINT_CNTMAX 	= 1u,			/*!< Maximum Loading Point */
	FTU_RELOAD_POINT_CNTMIN		= (1u << 1),	/*!< Minimum Loading Point */
	FTU_RELOAD_POINT_CHANNEL_0	= (1u << 2),	/*!< Channel 0 match is included as a reload opportunity */
	FTU_RELOAD_POINT_CHANNEL_1	= (1u << 3),	/*!< Channel 1 match is included as a reload opportunity */
	FTU_RELOAD_POINT_CHANNEL_2	= (1u << 4),	/*!< Channel 2 match is included as a reload opportunity */
	FTU_RELOAD_POINT_CHANNEL_3	= (1u << 5),	/*!< Channel 3 match is included as a reload opportunity */
	FTU_RELOAD_POINT_CHANNEL_4	= (1u << 6),	/*!< Channel 4 match is included as a reload opportunity */
	FTU_RELOAD_POINT_CHANNEL_5	= (1u << 7),	/*!< Channel 5 match is included as a reload opportunity */
	FTU_RELOAD_POINT_CHANNEL_6	= (1u << 8),	/*!< Channel 6 match is included as a reload opportunity */
	FTU_RELOAD_POINT_CHANNEL_7	= (1u << 9),	/*!< Channel 7 match is included as a reload opportunity */
} FTU_ReloadPointCfgType;

/**
 * @brief The synchronization flag of FTU peripheral
 *
 */
typedef enum
{
	FTU_SYNC_FLAG_FTUEN 		= 1u,			/*!< FTU Enable */
	FTU_SYNC_FLAG_LDOK			= (1u << 1),	/*!< Load Enable */
	FTU_SYNC_FLAG_CNTINC		= (1u << 2),	/*!< CNTIN Register Synchronization */
	FTU_SYNC_FLAG_PWMSYNC		= (1u << 3),	/*!< Synchronization Mode: Selects which triggers can be used
												   by MOD, CV, OUTMASK, and FTU counter synchronization. */
	FTU_SYNC_FLAG_REINIT		= (1u << 4),	/*!< FTU Counter re-initialization by Synchronization */
	FTU_SYNC_FLAG_SYNCHOM		= (1u << 5),	/*!< Selects when the OUTMASK register is updated with the
												   value of its buffer */
	FTU_SYNC_FLAG_SYNCEN01		= (1u << 6),	/*!< synchronization of registers C(0)V and C(1)V. */
	FTU_SYNC_FLAG_SYNCEN23		= (1u << 7),	/*!< synchronization of registers C(2)V and C(3)V. */
	FTU_SYNC_FLAG_SYNCEN45		= (1u << 8),	/*!< synchronization of registers C(4)V and C(5)V. */
	FTU_SYNC_FLAG_SYNCEN67		= (1u << 9),	/*!< synchronization of registers C(6)V and C(7)V. */
	FTU_SYNC_FLAG_HW_TRIG0		= (1u << 10),	/*!< hardware trigger 0 to the synchronization */
	FTU_SYNC_FLAG_HW_TRIG1		= (1u << 11),	/*!< hardware trigger 1 to the synchronization */
	FTU_SYNC_FLAG_HW_TRIG2		= (1u << 12),	/*!< hardware trigger 2 to the synchronization */
} FTU_SyncFlagType;

/**
 * @brief The interrupt enable/disable mask of FTU peripheral
 *
 */
typedef enum
{
	FTU_INTR_MASK_CHANNEL_0		= 1u,			/*!< interrupt mask of channel 0 */
	FTU_INTR_MASK_CHANNEL_1		= (1u << 1),	/*!< interrupt mask of channel 1 */
	FTU_INTR_MASK_CHANNEL_2		= (1u << 2),	/*!< interrupt mask of channel 2 */
	FTU_INTR_MASK_CHANNEL_3		= (1u << 3),	/*!< interrupt mask of channel 3 */
	FTU_INTR_MASK_CHANNEL_4		= (1u << 4),	/*!< interrupt mask of channel 4 */
	FTU_INTR_MASK_CHANNEL_5		= (1u << 5),	/*!< interrupt mask of channel 5 */
	FTU_INTR_MASK_CHANNEL_6		= (1u << 6),	/*!< interrupt mask of channel 6 */
	FTU_INTR_MASK_CHANNEL_7		= (1u << 7),	/*!< interrupt mask of channel 7 */
	FTU_INTR_MASK_OVERFLOW		= (1u << 8),	/*!< interrupt mask of overflow */
	FTU_INTR_MASK_FAULT			= (1u << 9),	/*!< interrupt mask of fault */
	FTU_INTR_MASK_RELOAD_POINT	= (1u << 10),	/*!< interrupt mask of reload point */
} FTU_IntrMaskType;

/**
 * @brief The fault control enable/disable mask for channels
 *
 */
typedef enum
{
	FTU_FAULT_FOR_CHANNEL01	= 1u,				/*!< fault control for channel 0 and channel 1 */
	FTU_FAULT_FOR_CHANNEL23	= (1u << 1),		/*!< fault control for channel 2 and channel 3 */
	FTU_FAULT_FOR_CHANNEL45	= (1u << 2),		/*!< fault control for channel 4 and channel 5 */
	FTU_FAULT_FOR_CHANNEL67	= (1u << 3),		/*!< fault control for channel 6 and channel 7 */
} FTU_FaultChannelEnableType;

/**
 * @brief the fault input polarity
 *
 */
typedef enum
{
	FTU_FAULT_POL_ACTIVE_HIGH 	= 0u,			/*!< The fault input polarity is active high.
													 1 at the fault input indicates a fault */
	FTU_FAULT_POL_ACTIVE_LOW	= 1u,			/*!< The fault input polarity is active low.
													 0 at the fault input indicates a fault */
}FTU_FaultPolActiveType;

/**
 * @brief the output trigger mask
 *
 */
typedef enum
{
	FTU_TRIG_OUTPUT_MASK_CHANNEL_0_MATCH 	= 1u,			/*!< Enables/Disables the channel 0 match trigger */
	FTU_TRIG_OUTPUT_MASK_CHANNEL_1_MATCH 	= (1u << 1),	/*!< Enables/Disables the channel 1 match trigger */
	FTU_TRIG_OUTPUT_MASK_CHANNEL_2_MATCH 	= (1u << 2),	/*!< Enables/Disables the channel 2 match trigger */
	FTU_TRIG_OUTPUT_MASK_CHANNEL_3_MATCH 	= (1u << 3),	/*!< Enables/Disables the channel 3 match trigger */
	FTU_TRIG_OUTPUT_MASK_CHANNEL_4_MATCH 	= (1u << 4),	/*!< Enables/Disables the channel 4 match trigger */
	FTU_TRIG_OUTPUT_MASK_CHANNEL_5_MATCH 	= (1u << 5),	/*!< Enables/Disables the channel 5 match trigger */
	FTU_TRIG_OUTPUT_MASK_CHANNEL_6_MATCH 	= (1u << 6),	/*!< Enables/Disables the channel 6 match trigger */
	FTU_TRIG_OUTPUT_MASK_CHANNEL_7_MATCH 	= (1u << 7),	/*!< Enables/Disables the channel 7 match trigger */
	FTU_TRIG_OUTPUT_MASK_ALL_CHANNEL_MATCH	= (0xFFu),		/*!< Enables/Disables all channel match trigger */
	FTU_TRIG_OUTPUT_MASK_RELOAD 		 	= (1u << 8),	/*!< Enables/Disables reload trigger */
}FTU_TriggerOutputMaskType;

/** @brief Ftu input capture mode */
typedef enum
{
    FTU_INPUT_RISING_EDGE = 0U,								/*!< capture on rising edge only */
    FTU_INPUT_FALLING_EDGE,									/*!< capture on falling edge only */
    FTU_INPUT_BOTH_EDGE										/*!< capture on rising or falling edge */
} FTU_InputCapturePinModeType;

/** @brief Ftu Global Time Base instance start mask */
typedef enum
{
	FTU_GTB_INSTANCE_START_FTU0		= 1u,				/*!< FTU0 GTB start */
	FTU_GTB_INSTANCE_START_FTU1		= (1u << 1),		/*!< FTU1 GTB start */
	FTU_GTB_INSTANCE_START_FTU2		= (1u << 2),		/*!< FTU2 GTB start */
	FTU_GTB_INSTANCE_START_FTU3		= (1u << 3),		/*!< FTU3 GTB start */
	FTU_GTB_INSTANCE_START_FTU4		= (1u << 4),		/*!< FTU4 GTB start */
	FTU_GTB_INSTANCE_START_FTU5		= (1u << 5),		/*!< FTU5 GTB start */
	FTU_GTB_INSTANCE_START_FTU6		= (1u << 6),		/*!< FTU6 GTB start */
	FTU_GTB_INSTANCE_START_FTU7		= (1u << 7),		/*!< FTU7 GTB start */
} FTU_GlobalTimeBaseStartInstanceType;

/** @brief Ftu Global Time Base start mask */
typedef enum
{
	FTU_GTB_START_AT_ONCE 			= 1u,				/*!< GTB start at once */
	FTU_GTB_START_AT_TSTMP1_MOD0 	= (1u << 1),		/*!< GTB start at modulate timer 0 of TSTMP1 */
	FTU_GTB_START_AT_TSTMP1_MOD1 	= (1u << 2),		/*!< GTB start at modulate timer 1 of TSTMP1 */
	FTU_GTB_START_AT_TSTMP1_MOD2 	= (1u << 3),		/*!< GTB start at modulate timer 2 of TSTMP1 */
	FTU_GTB_START_AT_TSTMP1_MOD3 	= (1u << 4),		/*!< GTB start at modulate timer 3 of TSTMP1 */
} FTU_GlobalTimeBaseStartType;

/** @brief FTU signal measurement mode type */
typedef enum
{
	FTU_SIGNAL_MEASURE_HIGH_TIME			= 0u,		/*!< Measurement high time */
	FTU_SIGNAL_MEASURE_LOW_TIME				= 1u,		/*!< Measurement low time */
	FTU_SIGNAL_MEASURE_PERIOD_RISING_EDGE	= 2u,		/*!< Measurement period of rising edge */
	FTU_SIGNAL_MEASURE_PERIOD_FALLING_EDGE	= 3u		/*!< Measurement period of falling edge */
} FTU_SignalMeasureModeType;

/** @brief FTU signal measurement configuration type */
typedef struct
{
	uint8_t 					u8Channel;				/*!< selected FTU channel */
	FTU_SignalMeasureModeType 	eMeasureMode;			/*!< signal measurement mode type */
	FTU_MeasureContModeType   	eContinuouslyMode;		/*!< The measurement is single or continuous */
	FTU_MeasureStartModeType	eStartMode;				/*!< Timing of start measurement */
} FTU_SignalMeasureType;

/** @brief FTU signal measurement result time */
typedef struct
{
	uint32_t u32StartTime;								/*!< start time of measured signal */
	uint32_t u32EndTime;								/*!< end time of measured signal */
} FTU_SignalMeasureValueType;

/** @brief Expect edge number result time */
typedef struct
{
	uint32_t u32FirstEdgeTime;							/*!< first edge time of measured signal */
	uint32_t u32LastEdgeTime;							/*!< last edge time of measured signal */
} FTU_ExpectEdgeNumberResultType;

/** @brief FTU edge number measurement configuration type */
typedef struct
{
	uint8_t 					u8Channel;			/*!< selected FTU channel */
	FTU_InputCapturePinModeType	eEdgeMode;			/*!< input capture mode */
	FTU_MeasureContModeType   	eContinuouslyMode;	/*!< The measurement is single or continuous */
	uint32_t 					u32StartWindow;		/*!< start-point window */
	uint32_t					u32EndWindow;		/*!< end-point window */
} FTU_EdgeNumberMeasureType;

/** @brief FTU expect edge number measurement configuration type */
typedef struct
{
	uint8_t 					u8Channel;			/*!< selected FTU channel */
	FTU_InputCapturePinModeType	eEdgeMode;			/*!< input capture mode */
	uint8_t						u8ExpectEdgeNumber;	/*!< Expected number of edges */
	FTU_MeasureContModeType   	eContinuouslyMode;	/*!< The measurement is single or continuous */
} FTU_ExpectEdgeNumberMeasureType;

/**
 * @brief The configuration option for the FTU interrupt
 *
 */
typedef struct
{
    uint32_t 					u32InterruptMask;				/*!< interrupt enable mask */
    FTU_ChannelCallBackType		pChannelCallback;				/*!< channel interrupt callback */
    FTU_FaultCallBackType		pFaultCallback;					/*!< fault interrupt callback */
    FTU_InterruptCallBackType 	pOverflowCallback;              /*!< overflow interrupt callback */
    FTU_InterruptCallBackType	pReloadPointCallback;			/*!< reload point interrupt callback */
} FTU_InterruptType;

/**
 * @brief The configuration for the Pwm channel
 *
 */
typedef struct
{
    uint8_t u8Channel;                    /*!< selected FTU channel */
    FTU_PwmPinModeType ePinMode;          /*!< pwm mode */
    uint32_t u32PwmDuty;                  /*!< pwm duty (timer ticks) */
    uint32_t u32PhaseShift;				  /*!< pwm phase shift (timer ticks)*/
    bool bLinkMode;                       /*!< pwm channel link mode enable, channel num must be even,and the linked channel is current_channel+1*/
    bool bLinkChannelComplement;          /*!< pwm link channel output complement */
    bool bDeadtimeEnable;				  /*!< Deadtime Enable */
    uint32_t u32ChannelDeadtime;          /*!< The separated deadtime (source clock ticks) */
} FTU_PwmChannelType;

/**
 * @brief The configuration option for the Pwm Mode
 *
 */
typedef struct
{
    uint32_t u32PwmPeriod;                /*!< pwm period (timer ticks) */
    uint32_t u32PublicDeadtime;           /*!< pwm deadtime (source clock ticks) */
    FTU_PwmAlignedType	eAlignedMode;	  /*!< pwm Aligned Mode */
    uint32_t u32ChannelCount;			  /*!< channel count of the Ftu instance */
    FTU_PwmChannelType *pPwmChannels;	  /*!< point to the pwm channel  */
} FTU_PwmModeType;

/**
 * @brief The configuration option for the output compare mode
 *
 */
typedef struct
{
    uint8_t u8Channel;                              /*!< selected FTU channel */
    FTU_OutputComparePinModeType eOutputMode;       /*!< ouput compare mode */
    uint32_t u32CompareValue;                       /*!< output compare value (timer ticks) */
    FTU_OutputCompareInitLevelType eInitLevel;		/*!< the initial level of the channel */
} FTU_OutputCompareModeType;

/**
 * @brief The configuration option for the time counter mode
 *
 */
typedef struct
{
    uint32_t u32CounterValue;                       /*!< counter overflow value (timer ticks) */
    uint32_t u32InitialValue;						/*!< counter initial value (timer ticks) */
} FTU_CounterModeType;

/**
 * @brief The basic configuration option for the FTU peripheral
 *
 */
typedef struct
{
    FTU_PrescalerType 		ePrescaler;            	/*!< Ftu prescaler */
    FTU_ClkSrcType 			eClkSrc;                /*!< Ftu clock source */
	FTU_FilterPrescalerType eFliterPrescaler;		/*!< Select the prescaler of the FTU filter */
    uint32_t				u32OverflowValue;		/*!< Ftu modulo value */
    uint16_t				u16ReloadPoints;		/*!< Ftu Synchronization points to update the buffered registers.Multiple
                                                   	 update modes can be used by providing an OR'ed list of options
                                                   	 available in enumeration ::FTU_ReloadPointCfgType. */
    uint8_t					u8ReloadFreq;			/*!< Frequency of the Reload Opportunities. Range is 0-31, */
    uint16_t				u16SyncFlag;			/*!< Ftu Synchronization flags to config the Synchronization and update of
    												 the buffered registers. Multiple update modes can be used by
    												 providing an OR'ed list of options available in
    												 enumeration ::FTU_SyncFlagType. */
    FTU_TrigModeType		eHwTrigMode;			/*!< hardware trigger mode */
    FTU_DebugModeType 		eDbgMode;				/*!< Ftu debug mode */
    FTU_UpDownDisableType	eUpDownDisable;			/*!< Disable channel match trigger/interrupt when count-up/down in CPWM/QUAD mode */
    bool					bGtbEnable;				/*!< Global Time Base Enable */
} FTU_CommonType;

/**
 * @brief The configuration option for initializing FTU fault
 *
 */
typedef struct
{
	FTU_FaultModeType 		eFaultMode;               	/*!< fault control mode */
	uint8_t 				u8FilterValue;				/*!< selects the filter value for the fault inputs */
	uint8_t					u8FaultChannelEnable;		/*!< fault control for channel */
	uint8_t 				u8FaultDisableDelay0;		/*!< Fault Disable Channel Output Delay Value 0 (timer ticks) */
	uint8_t 				u8FaultDisableDelay1;		/*!< Fault Disable Channel Output Delay Value 1 (timer ticks) */
} FTU_FaultInitType;

/**
 * @brief The configuration option for enabling a FTU fault
 *
 */
typedef struct
{
	uint8_t 				u8FaultIndex;				/*!< fault index */
	FTU_FaultPolActiveType 	eFaultPol;					/*!< the fault input active polarity */
	bool					bFaultFilterEnable;			/*!< whether to enable fault input glitch filter*/
} FTU_FaultControlType;

/**
 * @brief The configuration option for a input capture channel
 *
 */
typedef struct
{
	uint8_t u8Channel;								/*!< selected FTU channel */
	FTU_InputCapturePinModeType eInputMode;        	/*!< input capture mode */
	uint8_t	u8FilterValue;							/*!< selects the filter value for the channel input */
} FTU_InputChannelType;

/**
 * @brief The configuration option for the quadrature decoder mode
 *
 */
typedef struct
{
	FTU_QuadratureModeType 			eQuadMode;			/*!< selects the encoding mode used in the Quadrature Decoder mode */
	FTU_QuadratureDirectionType		eQuadDirection;		/*!< indicates the counting direction */
	FTU_TimerOverflowDirectionType	eOveflowDirection;	/*!< Indicates if the TOF bit was set on the top or the bottom of counting */
	uint8_t 						u8PhaFilterVal;		/*!< The filter value for the phase A input */
	uint8_t 						u8PhbFilterVal;		/*!< The filter value for the phase B input */
	bool 							bPhaInverted;		/*!< whether to inverted polarity of phase A input */
	bool 							bPhbInverted;		/*!< whether to inverted polarity of phase B input */
	uint16_t						u16TopValue;		/*!< the top value of counting */
	uint16_t						u16BottomValue;		/*!< the bottom value of counting */
} FTU_QuadratureInitType;

/**
 * @brief Initialize FTU basic configuration
 *
 * @param eInstance the selected FTU instance
 * @param pCommonStruct the basic configurations of the FTU instance
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_CommonInit(const FTU_InstanceType eInstance, const FTU_CommonType *const pCommonStruct);

/**
 * @brief Fills in the FTU configuration structure with the default settings.
 *
 * @param pCommonStruct Pointer to the user configuration structure
 */
void FTU_GetDefaultInitCfg(FTU_CommonType *pCommonStruct);

/**
 * @brief Configure FTU to counter mode
 *
 * @param eInstance the selected FTU instance
 * @param pCounterStruct the configurations of the counter mode
 * @return FTU_StatusType whether the operation is successfully
 * @note This function will stop timer
 */
FTU_StatusType FTU_CounterModeInit(const FTU_InstanceType eInstance,
                                   const FTU_CounterModeType *const pCounterStruct);


/**
 * @brief Configure FTU to output compare mode
 *
 * @param eInstance the selected FTU instance
 * @param pOutputModeStruct the configurations of the output compare mode
 * @return FTU_StatusType whether the operation is successfully
 * @note This function will stop timer
 */
FTU_StatusType FTU_OutputCompareModeInit(const FTU_InstanceType eInstance,
                                         const FTU_OutputCompareModeType *const pOutputModeStruct);

/**
 * @brief Configure  Configure FTU to PWM mode
 *
 * @param eInstance the selected FTU instance
 * @param pPwmModeStruct the configurations of the PWM mode
 * @return FTU_StatusType whether the operation is successfully
 * @note This function will stop timer
 */
FTU_StatusType FTU_PwmModeInit(const FTU_InstanceType eInstance, const FTU_PwmModeType *const pPwmModeStruct);

/**
 * @brief Update the duty cycle of the FTU instance
 *
 * @param eInstance the selected FTU instance
 * @param u8Channel the selected FTU channel
 * @param u32Duty duty cycle of the PWM mode
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_PwmUpdateDuty(const FTU_InstanceType eInstance, uint8_t u8Channel, uint32_t u32Duty);

/**
 * @brief Ftu initialize interrupt function
 *
 * @param eInstance the selected FTU instance
 * @param pIntStruct the configurations of the interrupt
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_InterruptInit(const FTU_InstanceType eInstance, const FTU_InterruptType *const pIntStruct);

/**
 * @brief Enable FTU interrupt
 *
 * @param eInstance the selected FTU instance
 * @param u32InterruptMask interrupt enable mask
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_EnableInterrupt(const FTU_InstanceType eInstance, uint32_t u32InterruptMask);

/**
 * @brief Enable FTU interrupt
 *
 * @param eInstance the selected FTU instance
 * @param u32InterruptMask interrupt disable mask
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_DisableInterrupt(const FTU_InstanceType eInstance, uint32_t u32InterruptMask);
/**
 * @brief Start the FTU instance
 *
 * @param eInstance the selected FTU instance
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_StartTimer(const FTU_InstanceType eInstance);
/**
 * @brief Stop the FTU global time base
 *
 * @param u32InstanceMask The selected FTU, each bit represents an instance
 */
void FTU_StopGlobalTimeBase(uint32_t u32InstanceMask);
/**
 * @brief Start the FTU global time base
 *
 * @param u32InstanceMask The selected FTU, each bit represents an instance
 * @param u32StartMask Start time, refer to FTU_GlobalTimeBaseStartType
 */
void FTU_StartGlobalTimeBase(uint32_t u32InstanceMask, uint32_t u32StartMask);
/**
 * @brief Stop the FTU instance
 *
 * @param eInstance the selected FTU instance
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_StopTimer(const FTU_InstanceType eInstance);

/**
 * @brief De-initialize the FTU instance
 *
 * @param eInstance the selected FTU instance
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_DeInit(const FTU_InstanceType eInstance);

/**
 * @brief initialize fault input of the selected Ftu instance
 *
 * @param eInstance the selected FTU instance
 * @param pFaultInit the fault configurations of the FTU instance
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_FaultInit(const FTU_InstanceType eInstance, const FTU_FaultInitType *const pFaultInit);

/**
 * @brief Enable a fault input
 *
 * @param eInstance the selected FTU instance
 * @param pFaultCtrl configurations of the fault input
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_FaultEnable(const FTU_InstanceType eInstance, const FTU_FaultControlType *const pFaultCtrl);

/**
 * @brief Select fault disable channel output delay value
 *
 * @param eInstance the selected FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 * @param eDelaySelection Fault disable channel output delay value selection.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_FaultSelectDelayValue(const FTU_InstanceType eInstance, uint8_t u8Channel, FTU_FaultDisableDelayType eDelaySelection);
/**
 * @brief Get Edge number counter
 *
 * @param eInstance the selected FTU instance
 * @param u8Channel FTU channel number.
 * @return uint8_t Edge number counter
 */
uint8_t FTU_GetEdgeNumberCount(const FTU_InstanceType eInstance, uint8_t u8Channel);
/**
 * @brief Initialize a Edge Number Measurement channel
 *
 * @param eInstance the selected FTU instance
 * @param pEdgeNumMeasure measurement configuration.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_EdgeNumberMeasureChannelInit(const FTU_InstanceType eInstance, FTU_EdgeNumberMeasureType *pEdgeNumMeasure);
/**
 * @brief Initialize a signal measure channel
 *
 * @param eInstance the selected FTU instance
 * @param pMeasure measurement configuration.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_SignalMeasureChannelInit(const FTU_InstanceType eInstance, FTU_SignalMeasureType *pMeasure);
/**
 * @brief Re-start measurement when in single mode
 *
 * @param eInstance the selected FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_SignalMeasureChannelSingle(const FTU_InstanceType eInstance, uint8_t u8Channel);
/**
 * @brief Get the measurement result of the channel
 *
 * @param eInstance the selected FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 * @param pResult point to the result buffer.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_GetSignaMeasureResult(const FTU_InstanceType eInstance, uint8_t u8Channel, FTU_SignalMeasureValueType *pResult);
/**
 * @brief Disable a fault input
 *
 * @param eInstance the selected FTU instance
 * @param u32FaultIndex index of the fault input
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_FaultDisable(const FTU_InstanceType eInstance, uint32_t u32FaultIndex);

/**
 * @brief Clear the fault flag of the FTU instance
 *
 * @param eInstance the selected FTU instance
 * @param u32FaultFlag flag to clear
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_ClearFault(const FTU_InstanceType eInstance, uint32_t u32FaultFlag);

/**
 * @brief Get the fault flag of the FTU instance
 *
 * @param eInstance the selected FTU instance
 * @return uint32_t the fault flag of the selected Ftu instance
 */
uint32_t FTU_GetFaultFlag(const FTU_InstanceType eInstance);

/**
 * @brief initialize a input capture channel of the selected Ftu instance
 *
 * @param eInstance the selected FTU instance
 * @param pInputChannel configurations of the input capture channel
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_InputCaptureChannelInit(const FTU_InstanceType eInstance,
                                          const FTU_InputChannelType *const pInputChannel);
/**
 * @brief enable the synchronization of the selected FTU
 *
 * @param eInstance the selected FTU instance
 * @param u16ReloadPoints The synchronization flag
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_EnableSync(const FTU_InstanceType eInstance, uint16_t u16SyncFlag);
/**
 * @brief disable the synchronization of the selected FTU
 *
 * @param eInstance the selected FTU instance
 * @param u16SyncFlag The synchronization flag
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_DisableSync(const FTU_InstanceType eInstance, uint16_t u16SyncFlag);
/**
 * @brief Enable the output trigger of the selected FTU instance
 *
 * @param eInstance the selected FTU instance
 * @param u32TriggerOutputMask the output trigger mask
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_EnableTriggerOutput(const FTU_InstanceType eInstance, uint32_t u32TriggerOutputMask);
/**
 * @brief Disable the output trigger of the selected FTU instance
 *
 * @param eInstance the selected FTU instance
 * @param u32TriggerOutputMask the output trigger mask
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_DisableTriggerOutput(const FTU_InstanceType eInstance, uint32_t u32TriggerOutputMask);
/**
 * @brief initialize the quadrature decoder mode
 *
 * @param eInstance the selected FTU instance
 * @param pQuadInit configurations of the quadrature decoder
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_QuadratureModeInit(const FTU_InstanceType eInstance,
                                      const FTU_QuadratureInitType *const pQuadInit);
/**
 * @brief Enable the reload points of the selected FTU instance
 *
 * @param eInstance the selected FTU instance
 * @param u16ReloadPoints The reload points flag
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_EnableReloadPoints(const FTU_InstanceType eInstance, uint16_t u16ReloadPoints);
/**
 * @brief Disable the reload points of the selected FTU instance
 *
 * @param eInstance the selected FTU instance
 * @param u16ReloadPoints The reload points flag
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_DisableReloadPoints(const FTU_InstanceType eInstance, uint16_t u16ReloadPoints);

/**
 * @brief Enable ftu channel DMA
 *
 * @param eInstance the selected FTU instance
 * @param u32DmaMask The dma channel mask.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_EnableChannelDma(const FTU_InstanceType eInstance, uint32_t u32DmaMask);
/**
 * @brief Get the expect edge number result of the channel
 *
 * @param eInstance the selected FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 * @param pResult point to the result buffer.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_GetExpectEdgeNumberResult(const FTU_InstanceType eInstance, uint8_t u8Channel, FTU_ExpectEdgeNumberResultType *pResult);
/**
 * @brief Initialize a Expect Edge Number Measurement channel
 *
 * @param eInstance the selected FTU instance
 * @param pExpectEdgeNumMeasure measurement configuration.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_ExpectEdgeNumberMeasureChannelInit(const FTU_InstanceType eInstance, FTU_ExpectEdgeNumberMeasureType *pExpectEdgeNumMeasure);
/**
 * @brief Get the measurement result of the channel
 *
 * @param eInstance the selected FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 * @param pResult point to the result buffer.
 * @return FTU_StatusType whether the operation is successfully
 */
FTU_StatusType FTU_GetSignalMeasureResult(const FTU_InstanceType eInstance, uint8_t u8Channel, FTU_SignalMeasureValueType *pResult);
/**
 * @brief Interrupt IRQ handle of FTU instance
 *
 * @param eInstance the selected FTU instance
 */
void FTUn_IRQHandler(const FTU_InstanceType eInstance);
/** @}*/ /* fc7xxx_driver_ftu */
#if defined(__cplusplus)
}
#endif
#endif
