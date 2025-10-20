/**
 * @file HwA_fcpit.h
 * @author Flagchip
 * @brief FC7xxx FCPIT hardware access layer
 * @version 0.1.0
 * @date 2024-01-10
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0      2024-01-10    Flagchip076  N/A          First version for FC7240
   ******************************************************************************** */

#ifndef _HWA_FCPIT_H_
#define _HWA_FCPIT_H_

#include "device_header.h"
/********* Local typedef ************/
/** @brief Fcpit counter mode, the default mode is 32bit periodic count mode */
typedef enum
{
    FCPIT_32PERIODIC_COUNTER = 0,
    FCPIT_DUAL_16PERIODIC_COUNTER,
    FCPIT_ACCUMULATOR,
	FCPIT_32InputCaptue,
} FCPIT_TimerModeType;

/** @brief Fcpit channel number */
typedef enum
{
    FCPIT_CHANNEL_0 = 0U,
    FCPIT_CHANNEL_1,
    FCPIT_CHANNEL_2,
    FCPIT_CHANNEL_3
} FCPIT_ChannelType;
/********* Local inline function ************/
/**
 * @brief Set FCPIT channel value
 *
 * @param eChannel FCPIT channel number
 * @param u32RegValue Timer value
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelValue(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel, uint32_t u32RegValue)
{
    pFcpit->CONTROLS[eChannel].TVAL = u32RegValue;
}


/**
 * @brief read FCPIT channel value
 *
 * @param eChannel FCPIT channel number
 * @return   Timer value
 */
LOCAL_INLINE uint32_t FCPIT_HWA_ReadChannelValue(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
		return (uint32_t)(pFcpit->CONTROLS[eChannel].TVAL );
}

/**
 * @brief Configure FCPIT channel
 *
 * @param eChannel FCPIT channel number
 * @param u32RegValue TCTRL register value
 */
LOCAL_INLINE void FCPIT_HWA_ConfigChannel(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel, uint32_t u32RegValue)
{
    pFcpit->CONTROLS[eChannel].TCTRL = u32RegValue;
}

/**
 * @brief Configure FCPIT module
 *
 * @param u32RegValue MCR register value
 */
LOCAL_INLINE void FCPIT_HWA_ConfigModule(FCPIT_Type *pFcpit, uint32_t u32RegValue)
{
    pFcpit->MCR = u32RegValue;
}


/**
 * @brief Read FCPIT module enable
 *
 * @return MCR register with FCPIT_MCR_M_CEN_MASK
 */
LOCAL_INLINE uint32_t FCPIT_HWA_ReadModuleEnable(FCPIT_Type *pFcpit)
{
    return (uint32_t)(pFcpit->MCR & FCPIT_MCR_M_CEN_MASK);
}

/**
 * @brief Read FCPIT channel
 *
 * @param eChannel Channel number
 * @return TCTRL register with FCPIT_TCTRL_T_EN_MASK
 */
LOCAL_INLINE uint32_t FCPIT_HWA_ReadChannelEnable(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    return (uint32_t)(pFcpit->CONTROLS[eChannel].TCTRL & FCPIT_TCTRL_T_EN_MASK);
}

/**
 * @brief Read FCPIT active interrupt flag
 *
 * @return FCPIT active interrupt flag
 */
LOCAL_INLINE uint32_t FCPIT_HWA_ReadInterruptFlag(FCPIT_Type *pFcpit)
{
    return (pFcpit->MSR);
}

/**
 * @brief Read FCPIT enable interrupt flag
 *
 * @return FCPIT enable interrupt flag
 */
LOCAL_INLINE uint32_t FCPIT_HWA_ReadEnableInterruptFlag(FCPIT_Type *pFcpit)
{
    return (pFcpit->MIER);
}

/**
 * @brief Set FCPIT channel running on debug mode
 *
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelRunOnDebug(FCPIT_Type *pFcpit)
{
    pFcpit->MCR |= FCPIT_MCR_DBG_EN_MASK;
}

/**
 * @brief Set FCPIT channel running on low power mode
 *
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelRunOnLpm(FCPIT_Type *pFcpit)
{
    pFcpit->MCR |= FCPIT_MCR_LPM_EN_MASK;
}

/**
 * @brief Enable FCPIT module
 *
 */
LOCAL_INLINE void FCPIT_HWA_EnableModule(FCPIT_Type *pFcpit)
{
    pFcpit->MCR |= FCPIT_MCR_M_CEN_MASK;
}

/**
 * @brief Enable FCPIT channel(n) interrupt
 *
 * @param u32RegValue u32RegValue 0-3 bit indicate TIE0-TIE3
 */
LOCAL_INLINE void FCPIT_HWA_EnableChannelsInterrupt(FCPIT_Type *pFcpit, uint32_t u32RegValue)
{
    pFcpit->MIER |= u32RegValue;
}

/**
 * @brief Enable FCPIT channel
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_EnableChannel(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CONTROLS[eChannel].TCTRL |= FCPIT_TCTRL_T_EN_MASK;
}

/**
 * @brief Enable FCPIT channel
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_SetTimerEnable(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->SETTEN |= (FCPIT_SETTEN_SET_T_EN_0_MASK << (uint32_t)eChannel);
}


/**
 * @brief Disable FCPIT channel
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_ClearTimerEnable(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CLRTEN |= (FCPIT_CLRTEN_CLR_T_EN_0_MASK << (uint32_t)eChannel);
}

/**
 * @brief Enable FCPIT channel(n) chain mode
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_EnableChannelChainMode(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CONTROLS[eChannel].TCTRL |= FCPIT_TCTRL_CHAIN_MASK;
}

/**
 * @brief Configure FCPIT channel operation mode
 *
 * @param eChannel FCPIT channel number
 * @param eMode FCPIT operation mode
 */
LOCAL_INLINE void FCPIT_HWA_ConfigChannelMode(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel, FCPIT_TimerModeType eMode)
{
    uint32_t u32RegValue = pFcpit->CONTROLS[eChannel].TCTRL;
    pFcpit->CONTROLS[eChannel].TCTRL = (u32RegValue & ~(uint32_t)FCPIT_TCTRL_MODE_MASK) | FCPIT_TCTRL_MODE(eMode);
}

/**
 * @brief Set FCPIT channel start on trigger
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelStartOnTrig(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CONTROLS[eChannel].TCTRL |= FCPIT_TCTRL_TSOT_MASK;
}

/**
 * @brief Set FCPIT channel stop on interrupt
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelStopOnInterrupt(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CONTROLS[eChannel].TCTRL |= FCPIT_TCTRL_TSOI_MASK;
}

/**
 * @brief Set FCPIT channel reload on trigger
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelReloadOnTrig(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CONTROLS[eChannel].TCTRL |= FCPIT_TCTRL_TROT_MASK;
}

/**
 * @brief Set FCPIT channel trigger source
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelTriggerSrc(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CONTROLS[eChannel].TCTRL |= FCPIT_TCTRL_TRG_SRC_MASK;
}

/**
 * @brief Select FCPIT channel trigger
 *
 * @param eChannel FCPIT channel number
 * @param u8SelChannel Select channel, range is 0-3
 */
LOCAL_INLINE void FCPIT_HWA_SelectChannelTrigger(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel, uint8_t u8SelChannel)
{
    uint32_t u32RegValue = pFcpit->CONTROLS[eChannel].TCTRL;
    pFcpit->CONTROLS[eChannel].TCTRL = (u32RegValue & ~(uint32_t)FCPIT_TCTRL_TRG_SEL_MASK) | 
                                                    FCPIT_TCTRL_TRG_SEL(u8SelChannel);
}

/**
 * @brief Set FCPIT channel stop on debug mode
 *
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelStopOnDebug(FCPIT_Type *pFcpit)
{
    pFcpit->MCR &= ~(uint32_t)FCPIT_MCR_DBG_EN_MASK;
}

/**
 * @brief Set FCPIT channel stop on low power mode
 *
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelStopOnLpm(FCPIT_Type *pFcpit)
{
    pFcpit->MCR &= ~(uint32_t)FCPIT_MCR_LPM_EN_MASK;
}

/**
 * @brief Disable FCPIT module
 *
 */
LOCAL_INLINE void FCPIT_HWA_DisableModule(FCPIT_Type *pFcpit)
{
    pFcpit->MCR &= ~(uint32_t)FCPIT_MCR_M_CEN_MASK;
}

/**
 * @brief Clear FCPIT channel(n) interrupt flag
 *
 * @param u32RegValue 0-3 bit indicate TIF0-TIF3
 */
LOCAL_INLINE void FCPIT_HWA_ClearChannelsInterruptFlag(FCPIT_Type *pFcpit, uint32_t u32RegValue)
{
    pFcpit->MSR |= u32RegValue;
}

/**
 * @brief Disable FCPIT channel(n) interrupt
 *
 * @param u32RegValue u32RegValue 0-3 bit indicate TIE0-TIE3
 */
LOCAL_INLINE void FCPIT_HWA_DisableChannelsInterrupt(FCPIT_Type *pFcpit, uint32_t u32RegValue)
{
    pFcpit->MIER &= ~u32RegValue;
}

/**
 * @brief Disable FCPIT channel
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_DisableChannel(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_T_EN_MASK;
}

/**
 * @brief Disable FCPIT channel chain mode
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_DisableChannelChainMode(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_CHAIN_MASK;
}

/**
 * @brief Clear FCPIT channel operation mode
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_ClearChannelMode(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_MODE_MASK;
}

/**
 * @brief read FCPIT channel operation mode
 *
 * @param eChannel FCPIT channel number
 */

LOCAL_INLINE uint32 FCPIT_HWA_ReadChannelMode(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
	return (uint32) ((pFcpit->CONTROLS[eChannel].TCTRL & (uint32_t)FCPIT_TCTRL_MODE_MASK) >>FCPIT_TCTRL_MODE_SHIFT);
}


/**
 * @brief Clear FCPIT channel start on trigger
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_ClearChannelStartOnTrig(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_TSOT_MASK;
}

/**
 * @brief Clear FCPIT channel stop on interrupt
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_ClearChannelStopOnInterrupt(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_TSOI_MASK;
}

/**
 * @brief Clear FCPIT channel reload on trigger
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_ClearChannelReloadOnTrig(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_TROT_MASK;
}

/**
 * @brief Clear FCPIT channel trigger source
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_ClearChannelTriggerSrc(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_TRG_SRC_MASK;
}

/**
 * @brief Clear FCPIT channel trigger select
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_ClearChannelTriggerSelect(FCPIT_Type *pFcpit, FCPIT_ChannelType eChannel)
{
    pFcpit->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_TRG_SEL_MASK;
}


#endif /* #ifndef _HWA_FCPIT_H_ */
