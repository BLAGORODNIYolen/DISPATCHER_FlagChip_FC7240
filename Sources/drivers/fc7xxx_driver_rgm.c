/**
 * @file fc7xxx_driver_rgm.c
 * @author Flagchip
 * @brief FC7xxx RGM driver source code
 * @version 0.1.0
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2024-01-12    Flagchip119    N/A          First version for FC7240
********************************************************************************/
#include "fc7xxx_driver_rgm.h"
#include "interrupt_manager.h"

/** @brief Rgm user defined CPU0 core related system interrupt function */
static RGM_InterruptCallBackType s_pRgmCPU0PreIntPtr = NULL;

/** @brief Rgm pre-reset interrupt entry */
void RGM_Pre_IRQHandler(void);

/**
 * @brief This api can get RGM_SRS register that indicate the source of the most recent reset.
 *
 * @return RGM->RGM_SRS register, bit 0-15,29-31 corresponding to RGM_ResetEventType, refer to reference manual for details.
 * @note Multiple flags can be set if multiple reset events occur at the same time
 */
uint32_t RGM_GetLastResetFLag(void)
{
    return RGM_HWA_ReadLastResetFlag();
}

/**
 * @brief This api can get RGM_SSRS register that indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @return RGM->RGM_SSRS register, bit 0-15,29-31 corresponding to RGM_ResetEventType, refer to reference manual for details.
 */
uint32_t RGM_GetAllResetFlag(void)
{
    return RGM_HWA_ReadAllResetFlagBeforePOR();
}

/**
 * @brief This api can clear reset flag of RGM_SSRS register which indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @param eReset Enumeration of reset event flag
 */
void RGM_ClearResetFlagAfterPOR(const RGM_ResetEventType eReset)
{
    RGM_HWA_ClearResetFlagAfterPOR(eReset);
}

/**
 * @brief This api can clear all reset flag of RGM_SSRS register which indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 */
void RGM_ClearAllResetFlagAfterPOR(void)
{
    RGM_HWA_ClearAllResetFlagAfterPOR();
}

/**
 * @brief Enable reset pin filter
 *
 * @param eClk Reset pin filter clock source
 * @param u8BusClockFilterWidth Bus clock filter width
 * @param bLpClkEn select whether enable reset pin filter using AON32clock in low power mode
 * @return RGM return type
 * @note If use AON32K clock, A reset signal whose length is less than 2 AON32K clock periods will be filtered
 */
RGM_StatusType RGM_EnableResetFilter(RGM_FilterClkSrc eClk, uint8_t u8BusClockFilterWidth, bool bLpClkEn)
{
    RGM_StatusType eRet = RGM_STATUS_SUCCESS;
    if(eClk > RGM_RESET_FILTER_AON32K_CLOCK)
    {
        eRet = RGM_STATUS_PARAM_INVALID;
    }
    if (RGM_STATUS_SUCCESS == eRet)
    {
        if (RGM_RESET_FILTER_AON32K_CLOCK == eClk)
        {
            if ((RGM_HWA_ReadResetPinFilterEnable() & RGM_RSTFLT_RSTFLT_BUS_MASK) >> RGM_RSTFLT_RSTFLT_BUS_SHIFT == 1U)
            {
                RGM_HWA_DisableBusClockFilter();
            }
            RGM_HWA_EnableAon32kClockFilter();
        }
        if (RGM_RESET_FILTER_BUS_CLOCK == eClk)
        {
            if ((RGM_HWA_ReadResetPinFilterEnable() & RGM_RSTFLT_RSTFLT_AON_MASK) >> RGM_RSTFLT_RSTFLT_AON_SHIFT == 1U)
            {
                RGM_HWA_DisableAon32kClockFilter();
            }
            RGM_HWA_SetBusClockFilterWidth(u8BusClockFilterWidth);
            RGM_HWA_EnableBusClockFilter();
        }
        if (bLpClkEn)
        {
            RGM_HWA_EnableAon32kLPClockFilter();
        }
    }
    return eRet;
}

/**
 * @brief Disable reset pin filter
 *
 * @param eClk Reset pin filter clock source
 * @param bLpClkEn select whether disable reset pin filter using AON32clock in low power mode
 * @return RGM return type
 */
RGM_StatusType RGM_DisableResetFilter(RGM_FilterClkSrc eClk, bool bLpClkEn)
{
    RGM_StatusType eRet = RGM_STATUS_SUCCESS;
    if (eClk > RGM_RESET_FILTER_AON32K_CLOCK)
    {
        eRet = RGM_STATUS_PARAM_INVALID;
    }
    if (RGM_STATUS_SUCCESS == eRet)
    {
        if (RGM_RESET_FILTER_AON32K_CLOCK == eClk)
        {
            RGM_HWA_DisableAon32kClockFilter();
        }
        if (bLpClkEn)
        {
            RGM_HWA_DisableAon32kLPClockFilter();
        }
        if (RGM_RESET_FILTER_BUS_CLOCK == eClk)
        {
            RGM_HWA_ClearBusClockFilterWidth();
            RGM_HWA_DisableBusClockFilter();
        }
    }
    return eRet;
}

/**
 * @brief This api can enable interrupt before an system reset appear.
 *
 * @param eDelay Enumeration of delay cycles
 * @param eResetInterrupt Reset event flag, like: RGM_INT_CLKERR0 | RGM_INT_FCSMU
 * @return RGM return type
 *
 * @note Here is the interrupted master switch control
 */
RGM_StatusType RGM_EnableSystemResetInt(RGM_ResetDelayType eDelay, RGM_ResetIntMangerType eResetInterrupt)
{
    RGM_StatusType eRet = RGM_STATUS_SUCCESS;
    if (eDelay > RGM_512_CLOCK_CYCLES)
    {
        eRet = RGM_STATUS_PARAM_INVALID;
    }
    if (RGM_STATUS_SUCCESS == eRet)
    {
        RGM_HWA_EnableGlobalResetInterrupt();
        RGM_HWA_SetResetDelay(eDelay);
        RGM_HWA_EnableResetInterrupt(eResetInterrupt);
    }
    return eRet;
}

/**
 * @brief This api can disable interrupt before an system reset appear.
 *
 * @param eResetInterrupt Reset event flag, like: RGM_INT_CLKERR0 | RGM_INT_FCSMU
 * @param bClearDelay Whether to clear delay configuration
 * @return RGM return type
 */
RGM_StatusType RGM_DisableSystemResetInt(RGM_ResetIntMangerType eResetInterrupt, bool bClearDelay)
{
    RGM_StatusType eRet = RGM_STATUS_SUCCESS;
    if (bClearDelay)
    {
        RGM_HWA_ClearResetDelay();
    }
    RGM_HWA_DisableResetInterrupt(eResetInterrupt);
    return eRet;
}

/**
 * @brief Generate software reset through cotex-m register
 *
 */
void RGM_GenerateSwReset(void)
{
    CM7_HWA_SystemReset();
}

/**
 * @brief This api can enable interrupt before an CPU0 core related reset appear.
 *
 * @param eCPU0Interrupt Reset event flag, like: RGM_CPU_INT_SWRST | RGM_CPU_INT_SYSRST
 * @param pIsrNotify Interrupt function
 * @return RGM return type
 */
RGM_StatusType RGM_EnableCPU0CoreResetInt(RGM_CPUIntMangerType eCPU0Interrupt,RGM_InterruptCallBackType pIsrNotify)
{
    RGM_StatusType eRet = RGM_STATUS_SUCCESS;
    if((uint8_t)eCPU0Interrupt > 0x1FU)
    {
        eRet = RGM_STATUS_PARAM_INVALID;
    }
    if (RGM_STATUS_SUCCESS == eRet)
    {
        RGM_HWA_EnableCPU0InterruptFlag(eCPU0Interrupt);
        s_pRgmCPU0PreIntPtr = pIsrNotify;
    }
    return eRet;
}

/**
 * @brief This api can disable interrupt before an CPU0 core related reset appear.
 *
 * @param eCPU0Interrupt Reset event flag, like: RGM_CPU_INT_SWRST | RGM_CPU_INT_SYSRST
 * @return RGM return type
 */
RGM_StatusType RGM_DisableCPU0CoreResetInt(RGM_CPUIntMangerType eCPU0Interrupt)
{
    RGM_StatusType eRet = RGM_STATUS_SUCCESS;
    if((uint8_t)eCPU0Interrupt > 0x1FU)
    {
        eRet = RGM_STATUS_PARAM_INVALID;
    }
    if (RGM_STATUS_SUCCESS == eRet)
    {
        RGM_HWA_DisableCPU0InterruptFlag(eCPU0Interrupt);
    }
    return eRet;
}

/**
 * @brief Get the CPU0 exit reset flag
 *
 * @return RGM_CPU_OUT_RST_UNDER CPU0 is under reset
 * @return RGM_CPU_OUT_RST_OUT CPU0 is out of reset
 */
RGM_CPUOutResetType RGM_GetCPU0OutResetFlag(void)
{
    return RGM_HWA_GetCPU0OutResetFlag();
}

/**
 * @brief Generate a CPU0 software reset.
 *
 */
void RGM_GenerateCPU0SwReset(void)
{
    RGM_HWA_CPU0SWReset();
}

/**
 * @brief This api can get RGM_C0_SRS register that indicate the source of the most recent CPU0 reset.
 *
 * @return RGM->RGM_C0_SRS register, bit 0-20 corresponding to RGM_ResetEventType, refer to reference manual for details.
 * @note Multiple flags can be set if multiple reset events occur at the same time
 */
uint32_t RGM_GetCPU0LastResetFLag(void)
{
    return RGM_HWA_ReadCPU0LastResetFlag();
}

/**
 * @brief This api can get RGM_C0_SSRS register that indicate all CPU0 reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @returnRGM->RGM_C0_SSRS register, bit 0-20,29-31 corresponding to RGM_CPUResetEventType, refer to reference manual for details.
 */
uint32_t RGM_GetCPU0AllResetFlag(void)
{
    return RGM_HWA_ReadCPU0AllResetFlagBeforePOR();
}

/**
 * @brief This api can clear reset flag of RGM_C0_SSRS register which indicate CPU0 all reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @param eReset Enumeration of reset event flag
 */
void RGM_ClearCPU0ResetFlagAfterPOR(const RGM_CPUResetEventType eReset)
{
    RGM_HWA_ClearC0ResetFlagAfterPOR(eReset);
}

/**
 * @brief This api can clear all reset flag of RGM_C0_SSRS register which indicate CPU0 all reset sources since the last POR or LVD that have not been cleared by software.
 *
 */
void RGM_ClearCPU0AllResetFlagAfterPOR(void)
{
    RGM_HWA_ClearC0AllResetFlagAfterPOR();
}

/**
 * @brief RGM Pre-interrupt entry
 *
 */
void RGM_Pre_IRQHandler(void)
{
	IntMgr_DisableGlobalInterrupt();

	if (NULL != s_pRgmCPU0PreIntPtr)
	{
		s_pRgmCPU0PreIntPtr(RGM_GetCPU0LastResetFLag());
	}
    IntMgr_EnableGlobalInterrupt();
}

