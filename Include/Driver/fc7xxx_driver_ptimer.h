/**
 * @file fc7xxx_driver_ptimer.h
 * @author Flagchip0126
 * @brief FC7xxx PTIMER driver type definition and API
 * @version 0.1.0
 * @date 2024-01-15
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-15    Flagchip0126  N/A          First version for FC7240
   ******************************************************************************** */

#ifndef _DRIVER_FC7XXX_DRIVER_PTIMER_H_
#define _DRIVER_FC7XXX_DRIVER_PTIMER_H_
#include "device_header.h"
#include "HwA_ptimer.h"
#include "HwA_Scm.h"

#if defined(__cplusplus)
extern "C" {
#endif
/**
 * @addtogroup fc7xxx_driver_ptimer
 * @{
 */

/**
 * @brief PTIMER interrupt callback function prototype
 *
 */
typedef void (*PTIMER_InterruptCallbackType)(void);

/**
 * @brief PTIMER sequence error callback function prototype
 *
 */
typedef void (*PTIMER_SeqErrorCallbackType)(uint8_t u8Channel);

/**
 * @brief The instance index of the PTIMER peripheral
 *
 */
typedef enum
{
    PTIMER_INSTANCE_0 = 0U,
    PTIMER_INSTANCE_1 = 1U
} PTIMER_InstanceType;

/**
 * @brief Ptimer instance initialization parameters
 *
 */
typedef struct
{
    PTIMER_LoadValueModeType eLoadValueMode;                /*!< Select the load mode */
    PTIMER_ClockPreDividerType eClkPreDiv;                  /*!< Select the prescaler divider */
    PTIMER_ClockPreDivMultiplyFactorType eClkPreMultFactor; /*!< Select multiplication factor for prescaler */
    PTIMER_TrgSrcType eTriggerInput;                        /*!< Select the trigger input source */
    bool bContinuousModeEnable;     /*!< Enable the continuous mode */
    bool bDmaEnable;                /*!< Enable the dma for timer */
} PTIMER_InitType;

/**
 * @brief Ptimer interrupt configuration parameters
 *
 */
typedef struct
{
    bool bDelayIntEnable;                        /*!< Enable the interrupt for timer */
    uint32_t u32IntDelayPeriodUs;                /*!< The period in micro second */
    PTIMER_InterruptCallbackType pIntNotify;     /*!< Ptimer interrupt callback function pointer */
    bool bSeqErrIntEnable;                       /*!< Enable PTIMER Sequence Error Interrupt */
    PTIMER_SeqErrorCallbackType pSeqErrorNotify; /*!< Ptimer sequence error callback function pointer */
} PTIMER_InterruptType;

/**
 * @brief Ptimer channel configuration parameters
 *
 */
typedef struct
{
    uint32_t u32DelayUs;                   /*!< Setting pre_trigger's delay in microsecond. */
    bool bPreTriggerEnable;                /*!< Enable the pre_trigger. */
    bool bPreTriggerOutputEnable;          /*!< Enable the pre_trigger output.  */
    bool bPreTriggerBackToBackEnable;      /*!< Enable the back to back mode for ADC pre_trigger. */
} PTIMER_ChannelCfgType;

/**
 * @brief Ptimer pulse out configgurations
 *
 * When the Ptimer counter time reaches u32PulseOutDlyHighUs, the pulse-out goes high;
 * When the Ptimer counter time reaches u32PulseOutDlyLowUs, the pulse-out goes low.
 *
 */
typedef struct
{
    uint32_t u32PulseOutDlyHighUs;  /*!< Microsecond delay for pulse out to output high */
    uint32_t u32PulseOutDlyLowUs;   /*!< Microsecond delay for pulse out to output low */
} PTIMER_PulseOutType;

/**
 * @brief Initialize the Ptimer instance
 *
 * @param eInstance the Ptimer instance to use
 * @param pInitCfg the Ptimer initialization parameters
 */
void PTIMER_Init(const PTIMER_InstanceType eInstance, const PTIMER_InitType *const pInitCfg);

/**
 * @brief De-initialize the Ptimer instance
 * Disable the Ptimer instance and reset the configurations to its reset values
 *
 * @param eInstance the Ptimer instance to use
 */
void PTIMER_DeInit(const PTIMER_InstanceType eInstance);

/**
 * @brief Initialize the Ptimer interrupt
 * 
 * @note the interrupt delay value is buffered and will take effect only after called PTIMER_LoadValue()
 * function.
 *
 * @param eInstance the Ptimer instance to configure
 * @param pInterruptCfg the Ptimer initialization parameters
 */
void PTIMER_InitInterrupt(const PTIMER_InstanceType eInstance,
                          const PTIMER_InterruptType *const pInterruptCfg);

/**
 * @brief Initialize the Ptimer channels
 * 
 * @note the channel delay value is buffered and will take effect only after called PTIMER_LoadValue()
 * function.
 *
 * @param eInstance the Ptimer instance to use
 * @param aChannelCfg the array of channels to config
 * @param u8ChnNum the channel numbers in the channel array
 */
void PTIMER_InitChannel(const PTIMER_InstanceType eInstance,
                        const PTIMER_ChannelCfgType aChannelCfg[], const uint8_t u8ChnNum);

/**
 * @brief Set the Ptimer max counter period in microsecond
 * When the Ptimer counter reaches the period, it will return to zero
 *
 * @note the period parameter is buffered and will take effect only after called PTIMER_LoadValue()
 * function.
 * 
 * @param eInstance the Ptimer instance to use
 * @param u32PeriodUs the max counter period in microsecond
 */
void PTIMER_SetPeriod(const PTIMER_InstanceType eInstance, uint32_t u32PeriodUs);

/**
 * @brief Set the Ptimer pulse-out function
 *
 * @note the pulse-out delay values are buffered and will take effect only after called PTIMER_LoadValue()
 * function.
 * 
 * @param eInstance the Ptimer instance to use
 * @param pPulseOutCfg the pulse-out configuration
 */
void PTIMER_SetPulseOut(const PTIMER_InstanceType eInstance, const PTIMER_PulseOutType *pPulseOutCfg);

/**
 * @brief Load the buffered values into register
 *
 * Some Ptimer registers are buffered and will only take effect after called
 * this function
 *
 * @param eInstance the Ptimer instance to use
 */
void PTIMER_LoadValue(const PTIMER_InstanceType eInstance);

/**
 * @brief Enable the Ptimer instance
 *
 * @param eInstance the Ptimer instance to use
 */
void PTIMER_Enable(const PTIMER_InstanceType eInstance);

/**
 * @brief Disable the Ptimer instance
 *
 * @param eInstance the Ptimer instance to use
 */
void PTIMER_Disable(const PTIMER_InstanceType eInstance);

/**
 * @brief Enable the Ptimer pulse-out function
 *
 * @param eInstance the Ptimer instance to use
 */
void PTIMER_EnablePulseOut(const PTIMER_InstanceType eInstance);

/**
 * @brief Disable the Ptimer pulse-out function
 *
 * @param eInstance the Ptimer instance to use
 */
void PTIMER_DisablePulseOut(const PTIMER_InstanceType eInstance);

void PTIMER_SelectInstance01BackToBackMode(SCM_PTimerLMSelType ePTimerLoopMode);

/**
 * @brief Generate the software trigger signal for the Ptimer instance
 *
 * If the Ptimer trigger source is selected as PTIMER_TRGSRC_SW, call this function
 * will make the Ptimer instance to start.
 *
 * @param eInstance the Ptimer instance to use
 */
void PTIMER_GenerateSWTrigger(const PTIMER_InstanceType eInstance);

/** @}*/ /* fc7xxx_driver_ptimer */

#if defined(__cplusplus)
}
#endif
#endif
