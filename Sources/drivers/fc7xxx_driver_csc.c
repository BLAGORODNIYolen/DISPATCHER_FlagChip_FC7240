/**
 * @file fc7xxx_driver_csc.h
 * @author Flagchip
 * @brief FC7xxx csc driver type definition and API
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

#include "fc7xxx_driver_csc.h"
#include "fc7xxx_driver_scg.h"

/********* Local Macros ************/
#define CSC_GET_CPU_ID()			((CSC_WPB_CpuType)1U)

/********* Local Variables ************/

/********* Local functions ************/

/**
 * @brief Get the frequency of AONCLK clock selected by CSC0_AONCLKSR[AONCLKSEL].
 *
 * @return the frequency of AONCLK
 */
static uint32_t CSC0_GetAONClkFreq(void)
{
    CSC0_AONClkSrcType eAonClkSrc;
    uint32_t u32Freq;

	eAonClkSrc = CSC0_HWA_GetAONClkSrc();

	if (CSC0_AON_SIRCDIV_128K_CLK == eAonClkSrc)
	{
		u32Freq = CSC0_AONCLK_128K;
	}
	else if (CSC0_AON_SIRC32_1K_CLK == eAonClkSrc)
	{
		u32Freq = CSC0_AONCLK_1K;
	}
	else
	{
		u32Freq = CSC0_AONCLK_32K;
	}
	return u32Freq;
}

/**
 * @brief Get the frequency of AON32K clock selected by CSC0_AONCLKSR[AON32KCLKSEL].
 *
 * @return the frequency of AON32K
 */
static uint32_t CSC0_GetAON32kClkFreq(void)
{
    CSC0_AON32KClkSrcType eAon32KSrc;
    uint32_t u32Freq;

	eAon32KSrc = CSC0_HWA_GetAON32kClkSrc();

	if (CSC0_AON32K_SOSC32K_CLK == eAon32KSrc)
	{
		u32Freq = CSC0_AONCLK_SOSC_32K;
	}
	else
	{
		u32Freq = CSC0_AONCLK_32K;
	}
	return u32Freq;
}

/**
 * @brief Get the frequency of RTC clock selected by CSC0_AONCLKSR[RTCCLKSEL].
 *
 * @return the frequency of RTC
 */
static uint32_t CSC0_GetRTCClkFreq(void)
{
    CSC0_RTCClkSrcType eRtcClkSrc;
    uint32_t u32Freq;

	eRtcClkSrc = CSC0_HWA_GetRTCClkSrc();
	if (CSC0_RTC_FOSCDIVL_CLK == eRtcClkSrc)
	{
		u32Freq = SCG_GetScgClockFreq(SCG_FOSCDIVL_CLK);
	}
	else if (CSC0_RTC_SOSC_CLK == eRtcClkSrc)
	{
		u32Freq = CSC0_AONCLK_SOSC_32K;
	}
	else
	{
		u32Freq = CSC0_AONCLK_32K;
	}

	return u32Freq;
}

/**
 * @brief Get the frequency of output clock selected by CSC0_CLKOUT_CTRL[CLKOUT_SEL].
 *
 * @return the frequency of CSC0 output clock
 */
static uint32_t CSC0_GetClockOutFreq(void)
{
	uint32_t u32Freq;
	CSC0_ClockOutSrcType eClkOutSrc;
	CSC0_ClockOutDivType eClkOutDiv;


	eClkOutSrc = CSC0_HWA_GetClkOutSel();
	eClkOutDiv = CSC0_HWA_GetClkOutDiv();

	if(eClkOutSrc == CSC0_CLKOUT_SCG_CLKOUT)
	{
		u32Freq = SCG_GetScgClockFreq(SCG_SCG_CLKOUT_CLK);
	}
	else if(eClkOutSrc == CSC0_CLKOUT_FOSC_DIVM_CLK)
	{
		u32Freq = SCG_GetScgClockFreq(SCG_FOSCDIVM_CLK);
	}
	else if(eClkOutSrc == CSC0_CLKOUT_SLOW_CLK)
	{
		u32Freq = SCG_GetScgClockFreq(SCG_SLOW_CLK);
	}
	else if(eClkOutSrc == CSC0_CLKOUT_SIRC_DIVM_CLK)
	{
		u32Freq = SCG_GetScgClockFreq(SCG_SIRCDIVM_CLK);
	}
	else if(eClkOutSrc == CSC0_CLKOUT_PLL1_DIVM_CLK)
	{
		u32Freq = SCG_GetScgClockFreq(SCG_PLL1DIVM_CLK);
	}
	else if(eClkOutSrc == CSC0_CLKOUT_FIRC_DIVM_CLK)
	{
		u32Freq = SCG_GetScgClockFreq(SCG_FIRCDIVM_CLK);
	}
	else if(eClkOutSrc == CSC0_CLKOUT_CORE_CLK)
	{
		u32Freq = SCG_GetScgClockFreq(SCG_CORE_CLK);
	}
	else if(eClkOutSrc == CSC0_CLKOUT_PLL0_DIVM_CLK)
	{
		u32Freq = SCG_GetScgClockFreq(SCG_PLL0DIVM_CLK);
	}
	else if(eClkOutSrc == CSC0_CLKOUT_BUS_CLK)
	{
		u32Freq = SCG_GetScgClockFreq(SCG_BUS_CLK);
	}
	else if(eClkOutSrc == CSC0_CLKOUT_SIRC_128K_CLK)
	{
		u32Freq = CSC0_AONCLK_128K;
	}
	else if(eClkOutSrc == CSC0_CLKOUT_AON_CLK)
	{
		u32Freq = CSC0_GetAONClkFreq();
	}
	else if(eClkOutSrc == CSC0_CLKOUT_RTC_CLK)
	{
		u32Freq = CSC0_GetRTCClkFreq();
	}
	else
	{
		u32Freq = 0U;
	}

	return u32Freq / ((uint32_t)eClkOutDiv + 1U);
}

/**
 * @brief Set cpu to control peripheral group 0 in CSC0.
 *
 * @param eCpuType Cpu to use
 * @param eTarget Target to be set stop ack/request
 * @param bLockStatus    Lock current register.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return Set clock out operation success/failed
 */
static CSC_RetStatusType CSC0_SetCpuCtrlGrp0(const CSC_WPB_CpuType eCpuType, CSC_SetTargetType eTarget, bool bLockStatus)
{
    CSC_RetStatusType eRetVal = CSC_E_LOCK;

    if (CSC_STOPACK == eTarget)
    {
        if (0U == CSC0_HWA_MODER0_GetWPBLockStatus())
        {
            CSC0_HWA_MODER0_SetCpuWritePermit(eCpuType);

            if(bLockStatus != false)
            {
            	CSC0_HWA_MODER0_LockWritePermit();
            }
            eRetVal = CSC_E_OK;
        }
    }
    else
    {
        if (0U == CSC0_HWA_REQR0_GetWPBLockStatus())
        {
            CSC0_HWA_REQR0_SetCpuWritePermit(eCpuType);
            if(bLockStatus != false)
            {
            	CSC0_HWA_REQR0_LockWritePermit();
            }
            eRetVal = CSC_E_OK;
        }
    }

    return eRetVal;
}

/**
 * @brief Set cpu to control peripheral group 1 in CSC0.
 *
 * @param eCpuType Cpu to use
 * @param eTarget Target to be set stop ack/request
 *
 * @return Set clock out operation success/failed
 */
static CSC_RetStatusType CSC0_SetCpuCtrlGrp1(const CSC_WPB_CpuType eCpuType, CSC_SetTargetType eTarget, bool bLockStatus)
{
    CSC_RetStatusType eRetVal = CSC_E_LOCK;

    if (CSC_STOPACK == eTarget)
    {
        if (0U == CSC0_HWA_MODER1_GetWPBLockStatus())
        {
            CSC0_HWA_MODER1_SetCpuWritePermit(eCpuType);
            if(bLockStatus != false)
            {
            	CSC0_HWA_MODER1_LockWritePermit();
            }
            eRetVal = CSC_E_OK;
        }
    }
    else
    {
        if (0U == CSC0_HWA_REQR1_GetWPBLockStatus())
        {
            CSC0_HWA_REQR1_SetCpuWritePermit(eCpuType);
            if(bLockStatus != false)
            {
            	CSC0_HWA_REQR1_LockWritePermit();
            }
            eRetVal = CSC_E_OK;
        }
    }

    return eRetVal;
}

/**
 * @brief Set cpu to control peripheral group 2 in CSC0.
 *
 * @param eCpuType Cpu to use
 * @param eTarget Target to be set stop ack/request
 *
 * @return Set clock out operation success/failed
 */
static CSC_RetStatusType CSC0_SetCpuCtrlGrp2(const CSC_WPB_CpuType eCpuType, CSC_SetTargetType eTarget, bool bLockStatus)
{
    CSC_RetStatusType eRetVal = CSC_E_LOCK;

    if (CSC_STOPACK == eTarget)
    {
        if (0U == CSC0_HWA_MODER2_GetWPBLockStatus())
        {
            CSC0_HWA_MODER2_SetCpuWritePermit(eCpuType);
            if(bLockStatus != false)
            {
            	CSC0_HWA_MODER2_LockWritePermit();
            }
            eRetVal = CSC_E_OK;
        }
    }
    else
    {
        if (0U == CSC0_HWA_REQR2_GetWPBLockStatus())
        {
            CSC0_HWA_REQR2_SetCpuWritePermit(eCpuType);
            if(bLockStatus != false)
            {
            	CSC0_HWA_REQR2_LockWritePermit();
            }
            eRetVal = CSC_E_OK;
        }
    }

    return eRetVal;
}

/**
 * @brief Set the stop mode ACK of all group peripherals in CSC0.
 *
 * @param ePeriphGrp the group of peripherals to set the stop mode ACK value
 * @param u32Value the CSCx_STOP_MODERx register value
 *
 * @return Operation success/failed
 */
static CSC_RetStatusType CSC0_SetStopModeAck(const CSC_PeriphGrpType ePeriphGrp,uint32_t u32Value)
{
	CSC_RetStatusType eRetVal = CSC_E_NO_PERM;
	CSC_WPB_CpuType eCtrlCpu;

	if(ePeriphGrp == CSC_STOP_CTRL_GROUP_0)
	{
		eCtrlCpu = CSC0_HWA_MODER0_GetCpuWritePermit();

		if((eCtrlCpu == CSC_GET_CPU_ID()) || (eCtrlCpu == CSC_WP_CPU_ALL))
		{
			CSC0_HWA_MODER0_SetMultiStopAck(u32Value);
			eRetVal = CSC_E_OK;
		}

	}
	else if(ePeriphGrp == CSC_STOP_CTRL_GROUP_1)
	{
		eCtrlCpu = CSC0_HWA_MODER1_GetCpuWritePermit();

		if((eCtrlCpu == CSC_GET_CPU_ID()) || (eCtrlCpu == CSC_WP_CPU_ALL))
		{
			CSC0_HWA_MODER1_SetMultiStopAck(u32Value);
			eRetVal = CSC_E_OK;
		}

	}
	else
	{
		eCtrlCpu = CSC0_HWA_MODER2_GetCpuWritePermit();

		if((eCtrlCpu == CSC_GET_CPU_ID()) || (eCtrlCpu == CSC_WP_CPU_ALL))
		{
			CSC0_HWA_MODER2_SetMultiStopAck(u32Value);
			eRetVal = CSC_E_OK;
		}

	}

	return eRetVal;
}

/**
 * @brief Set the stop request of all group peripherals in CSC0.
 *
 * @param eTargetCpuType The target CPU which acknowledges the peripherals when entering stop mode.
 * @param ePeriphGrp the group of peripherals to set the stop request value
 * @param u32Value the CSCx_STOP_REQRx register value
 *
 * @return Operation success/failed
 */
static CSC_RetStatusType CSC0_SetStopRequest(const CSC_PeriphGrpType ePeriphGrp,uint32_t u32Value)
{
	CSC_RetStatusType eRetVal = CSC_E_NO_PERM;
	CSC_WPB_CpuType eCtrlCpu;

	if(ePeriphGrp == CSC_STOP_CTRL_GROUP_0)
	{
		eCtrlCpu = CSC0_HWA_REQR0_GetCpuWritePermit();

		if((eCtrlCpu == CSC_GET_CPU_ID()) || (eCtrlCpu == CSC_WP_CPU_ALL))
		{
			CSC0_HWA_REQR0_SetMultiStopRequest(u32Value);
			eRetVal = CSC_E_OK;
		}

	}
	else if(ePeriphGrp == CSC_STOP_CTRL_GROUP_1)
	{
		eCtrlCpu = CSC0_HWA_REQR1_GetCpuWritePermit();

		if((eCtrlCpu == CSC_GET_CPU_ID()) || (eCtrlCpu == CSC_WP_CPU_ALL))
		{
			CSC0_HWA_REQR1_SetMultiStopRequest(u32Value);
			eRetVal = CSC_E_OK;
		}

	}
	else
	{
		eCtrlCpu = CSC0_HWA_REQR2_GetCpuWritePermit();

		if((eCtrlCpu == CSC_GET_CPU_ID()) || (eCtrlCpu == CSC_WP_CPU_ALL))
		{
			CSC0_HWA_REQR2_SetMultiStopRequest(u32Value);
			eRetVal = CSC_E_OK;
		}

	}

	return eRetVal;
}

/**
 * @brief Get the stop Acknowledge status of all group peripherals in CSC0.
 *
 * @param ePeriphType the peripheral to get stop acknowledge status
 * @return uint32_t the stop ACK status of all the peripherals in the group indicated by ePeriphGrp.
 */
static uint32_t CSC0_GetStopAckStatus(const CSC_PeriphGrpType ePeriphGrp)
{
	uint32_t eRetVal;

	if(CSC_STOP_CTRL_GROUP_0 == ePeriphGrp)
	{
		eRetVal = CSC0_HWA_ACKR0_GetMultiStopAckStatus(CSC_STOP_PERIPH_GROUP0_MASK);
	}
	else if(CSC_STOP_CTRL_GROUP_1 == ePeriphGrp)
	{
		eRetVal = CSC0_HWA_ACKR1_GetMultiStopAckStatus(CSC_STOP_PERIPH_GROUP1_MASK);
	}
	else
	{
		eRetVal = CSC0_HWA_ACKR2_GetMultiStopAckStatus(CSC_STOP_PERIPH_GROUP2_MASK);
	}
	return eRetVal;
}






/********* Global functions ************/
/**
 * @brief set clock out. with clock out pin configure, the clock would be monitored.
 *        This Function may combined with SCG_ClkOut setting
 *        need to call SCG_SetClkOut,if clock out source set to SCG_CLKOUT. *
 * @param pCsc0ClkOut to Csc0ClkOut instance for clock out configuration
 * @param bLockStatus to lock current register.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_LOCK:    The register has been locked and can not be written
 * @note  configuration sequence:
 *           1. Disable CLKOUTEN
 *           2. Set CLKOUTSEL
 *           3. Enable CLKOUTEN
 */
CSC_RetStatusType CSC0_SetClockOut(const CSC0_ClkoutType *const pCsc0ClkOut, bool bLockStatus)
{
    DEV_ASSERT(pCsc0ClkOut != NULL);
    CSC_RetStatusType eRetVal;

    /* Check CSC0_CLKOUT_CTRL register lock status */
    if (0U == CSC0_HWA_CLKOUT_CTRL_GetLockStatus())
    {
        eRetVal = CSC_E_OK;
        /* Disable CLKOUTEN */
        CSC0_HWA_DisableClockOut();
        /* Set CLKOUTDIV */
        CSC0_HWA_SetClkOutDiv(pCsc0ClkOut->eDivider);
        /* Set CLKOUTSEL */
        CSC0_HWA_SetClkOutSel(pCsc0ClkOut->eClkOutSrc);
        /* Enable CLKOUTEN */
        CSC0_HWA_EnableClockOut();

        if (true == bLockStatus)
        {
            /* Lock CSC0_CLKOUT_CTRL register */
            CSC0_HWA_LockCLKOUT_CTRL();
        }
    }
    else
    {
        eRetVal = CSC_E_LOCK;
    }

    return eRetVal;
}

/**
 * @brief set always on clock source configuration include AON32K, RTC, AONCLK clock.
 *
 * @param pAonclkSrcType pointer to AONCLKSR instance for AON clock source configuration
 * @param bLockStatus to lock current register.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_LOCK:    The register has been locked and can not be written
 */
CSC_RetStatusType CSC0_SetAonClkSrc(const CSC0_AONCLKSRType *const pAonclkSrcType, bool bLockStatus)
{
	CSC_RetStatusType eRetVal;

    DEV_ASSERT(pAonclkSrcType != NULL);
    DEV_ASSERT(pAonclkSrcType->eAon32KSel == CSC0_AON32K_SIRCDIV_32K_CLK ||
    		   pAonclkSrcType->eAon32KSel == CSC0_AON32K_SOSC32K_CLK ||
			   pAonclkSrcType->eAon32KSel == CSC0_AON32K_SIRC32K_CLK);
    DEV_ASSERT(pAonclkSrcType->eRtcSel == CSC0_RTC_FOSCDIVL_CLK ||
    		   pAonclkSrcType->eRtcSel == CSC0_RTC_SIRCDIV_32K_CLK ||
			   pAonclkSrcType->eRtcSel == CSC0_RTC_SOSC_CLK ||
			   pAonclkSrcType->eRtcSel == CSC0_RTC_SIRC32K_CLK);
    DEV_ASSERT(pAonclkSrcType->eAonSel == CSC0_AON_SIRCDIV_128K_CLK ||
    		   pAonclkSrcType->eAonSel == CSC0_AON_SIRC32K_CLK ||
			   pAonclkSrcType->eAonSel == CSC0_AON_SIRCDIV_32K_CLK ||
			   pAonclkSrcType->eAonSel == CSC0_AON_SIRC32_1K_CLK);


    /* Check CSC0_AONCLKSR register lock status */
    if (0U == CSC0_HWA_AONCLKSR_GetLockStaus())
    {
        eRetVal = CSC_E_OK;

        /* Gating SIRC_32K clock*/
        if ((CSC0_AON32K_SIRCDIV_32K_CLK == pAonclkSrcType->eAon32KSel) ||
            (CSC0_AON_SIRCDIV_32K_CLK == pAonclkSrcType->eAonSel) ||
            (CSC0_RTC_SIRCDIV_32K_CLK == pAonclkSrcType->eRtcSel))
        {
            CSC0_HWA_EnableSIRCDIV_32KClkOut();
        }

        /* Gating SIRC32_1K clock*/
        if (CSC0_AON_SIRC32_1K_CLK == pAonclkSrcType->eAonSel)
        {
            CSC0_HWA_EnableSIRC32_1KClkOut();
        }

        /* Set AONCLOCK configuration */
        CSC0_HWA_SetAON32kClkSrc(pAonclkSrcType->eAon32KSel);
        CSC0_HWA_SetRTCClkSrc(pAonclkSrcType->eRtcSel);
        CSC0_HWA_SetAONClkSrc(pAonclkSrcType->eAonSel);

        if (true == bLockStatus)
        {
            /* Lock CSC0_AONCLKSR register */
            CSC0_HWA_LockAONCLKSR();
        }
    }
    else
    {
        eRetVal = CSC_E_LOCK;
    }

    return eRetVal;
}

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
CSC_RetStatusType CSC0_GetCSC0ClockFreq(CSC0_ClkSrcType eClkkName, uint32_t *const pFreq)
{
	CSC_RetStatusType eRetVal;
	DEV_ASSERT(pFreq != NULL);

	if ((uint32_t)eClkkName >= (uint32_t)CSC0_END_OF_CLOCKS)
    {
        eRetVal = CSC_E_NOT_OK;
        *pFreq = 0U;
    }
    else
    {
        eRetVal = CSC_E_OK;

        if (CSC0_AON_CLK == eClkkName)
        {
        	*pFreq = CSC0_GetAONClkFreq();
        }
        else if (CSC0_AON32K_CLK == eClkkName)
        {
        	*pFreq = CSC0_GetAON32kClkFreq();
        }
        else if (CSC0_RTC_CLK == eClkkName)
        {
        	*pFreq = CSC0_GetRTCClkFreq();
        }
        else
        {
        	/* CSC0_CLKOUT_CLK */
        	*pFreq = CSC0_GetClockOutFreq();
        }
    }

    return eRetVal;
}

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
 * 			CSC_E_LOCK:    The register has been locked
 */
CSC_RetStatusType CSC0_ScgMAMStallRequest(bool bEnable, bool bLockStatus)
{
	CSC_RetStatusType eRetVal= CSC_E_LOCK;

	if (0U == CSC0_HWA_SCG_MAM_STALL_GetLockStatus())
    {
		if(bEnable != false)
		{
			CSC0_HWA_EnalbeSCGStall();
		}
		else
		{
			CSC0_HWA_DisableSCGStall();
		}

		if(bLockStatus != false)
		{
			CSC0_HWA_LockSCG_MAM_STALL();
		}

        eRetVal = CSC_E_OK;
    }

    return eRetVal;
}

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
CSC_RetStatusType CSC0_SetReqToSMUGrp0(uint32_t u32Value, bool bLockStatus)
{
    CSC_RetStatusType eRetVal = CSC_E_PARAM;

	/* Check register bits invalid */
	if((u32Value & (~CSC_SMU_CTRL_GROUP0_MASK)) == 0U)
	{

		/* Check register lock status */
		if (0U == CSC0_HWA_SMU_CTRL0_GetLockStatus())
		{
			eRetVal = CSC_E_OK;
			/* Set value(do not involve lock bit) */
			CSC0_HWA_CTRL0_SetMultiReqToSMU(u32Value);
			if (true == bLockStatus)
			{
				/* Lock register */
				CSC0_HWA_LockSMU_CTRL0();
			}
		}
		else
		{
			eRetVal = CSC_E_LOCK;
		}
    }

    return eRetVal;
}

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
CSC_RetStatusType CSC0_SetReqToSMUGrp1(uint32_t u32Value, bool bLockStatus)
{
    CSC_RetStatusType eRetVal = CSC_E_PARAM;

    /* Check register bits invalid */
    if((u32Value & (~CSC_SMU_CTRL_GROUP1_MASK)) == 0U)
    {

		/* Check register lock status */
		if (0U == CSC0_HWA_SMU_CTRL1_GetLockStatus())
		{
			eRetVal = CSC_E_OK;
			/* Set value(do not involve lock bit) */
			CSC0_HWA_CTRL1_SetMultiReqToSMU(u32Value);
			if (true == bLockStatus)
			{
				/* Lock register */
				CSC0_HWA_LockSMU_CTRL1();
			}
		}
		else
		{
			eRetVal = CSC_E_LOCK;
		}
    }

    return eRetVal;
}

/**
 * @brief Set request to SMU of group 4.
 *
 * @param u32Value Value to be set(the or bits defined in CSC_SMU_CtrlGrp4Type,do not involve lock bit)
 * @param bLockStatus Lock the register.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  The u32Value contains invalid bits
 * 			CSC_E_LOCK:    The register has been locked
 */
CSC_RetStatusType CSC0_SetReqToSMUGrp4(uint32_t u32Value, bool bLockStatus)
{
    CSC_RetStatusType eRetVal = CSC_E_PARAM;

	/* Check register bits invalid */
	if((u32Value & (~CSC_SMU_CTRL_GROUP4_MASK)) == 0U)
	{

		/* Check register lock status */
		if (0U == CSC0_HWA_SMU_CTRL4_GetLockStatus())
		{
			eRetVal = CSC_E_OK;
			/* Set value(do not involve lock bit) */
			CSC0_HWA_CTRL4_SetMultiReqToSMU(u32Value);
			if (true == bLockStatus)
			{
				/* Lock register */
				CSC0_HWA_LockSMU_CTRL4();
			}
		}
		else
		{
			eRetVal = CSC_E_LOCK;
		}
	}

    return eRetVal;
}

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
CSC_RetStatusType CSC0_SetReqToSMUGrp5(uint32_t u32Value, bool bLockStatus)
{
    CSC_RetStatusType eRetVal = CSC_E_PARAM;

	/* Check register bits invalid */
	if((u32Value & (~CSC_SMU_CTRL_GROUP5_MASK)) == 0U)
	{

		/* Check register lock status */
		if (0U == CSC0_HWA_SMU_CTRL5_GetLockStatus())
		{
			eRetVal = CSC_E_OK;
			/* Set value(do not involve lock bit) */
			CSC0_HWA_CTRL5_SetMultiReqToSMU(u32Value);
			if (true == bLockStatus)
			{
				/* Lock register */
				CSC0_HWA_LockSMU_CTRL5();
			}
		}
		else
		{
			eRetVal = CSC_E_LOCK;
		}
	}

    return eRetVal;
}

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
CSC_RetStatusType CSC0_SetReqToSMU(CSC0_SmuCtrlGrpType eCtrlGrp, uint32_t u32Value, bool bLockStatus)
{
    CSC_RetStatusType eRetVal;

    if (CSC0_SMU_CTRL_GROUP_0 == eCtrlGrp)
    {
        eRetVal = CSC0_SetReqToSMUGrp0(u32Value, bLockStatus);
    }
    else if (CSC0_SMU_CTRL_GROUP_1 == eCtrlGrp)
    {
        eRetVal = CSC0_SetReqToSMUGrp1(u32Value, bLockStatus);
    }
    else if (CSC0_SMU_CTRL_GROUP_4 == eCtrlGrp)
    {
        eRetVal = CSC0_SetReqToSMUGrp4(u32Value, bLockStatus);
    }
    else if (CSC0_SMU_CTRL_GROUP_5 == eCtrlGrp)
    {
        eRetVal = CSC0_SetReqToSMUGrp5(u32Value, bLockStatus);
    }
    else
    {
    	eRetVal = CSC_E_NOT_OK;
    }

    return eRetVal;
}

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
CSC_RetStatusType CSC0_LP_WakeupPadOutputCfg(const CSC0_LPWakeupCfgType * const eLPWakeupCfg, bool bLockStatus)
{
	CSC_RetStatusType eRetVal;

	DEV_ASSERT(eLPWakeupCfg != NULL_PTR);
	DEV_ASSERT((uint32_t)eLPWakeupCfg->eCfgGrp0 <= (uint32_t)CSC_LP_WAKEUP_FCPIT0_TRIGGER_OUT3);
	DEV_ASSERT((uint32_t)eLPWakeupCfg->eCfgGrp1 <= (uint32_t)CSC_LP_WAKEUP_FCPIT0_TRIGGER_OUT3);
	DEV_ASSERT((uint32_t)eLPWakeupCfg->eCfgGrp2 <= (uint32_t)CSC_LP_WAKEUP_FCPIT0_TRIGGER_OUT3);
	DEV_ASSERT((uint32_t)eLPWakeupCfg->eCfgGrp3 <= (uint32_t)CSC_LP_WAKEUP_FCPIT0_TRIGGER_OUT3);
	DEV_ASSERT((uint32_t)eLPWakeupCfg->eCfgGrp4 <= (uint32_t)CSC_LP_WAKEUP_FCPIT0_TRIGGER_OUT3);
	DEV_ASSERT((uint32_t)eLPWakeupCfg->ePolGrp0 <= (uint32_t)CSC_LP_WAKEUP_POL_INVERT);
	DEV_ASSERT((uint32_t)eLPWakeupCfg->ePolGrp1 <= (uint32_t)CSC_LP_WAKEUP_POL_INVERT);
	DEV_ASSERT((uint32_t)eLPWakeupCfg->ePolGrp2 <= (uint32_t)CSC_LP_WAKEUP_POL_INVERT);
	DEV_ASSERT((uint32_t)eLPWakeupCfg->ePolGrp3 <= (uint32_t)CSC_LP_WAKEUP_POL_INVERT);
	DEV_ASSERT((uint32_t)eLPWakeupCfg->ePolGrp4 <= (uint32_t)CSC_LP_WAKEUP_POL_INVERT);

	if (0U == CSC0_HWA_LP_WAKEUP_GetLockStatus())
	{
		CSC0_HWA_SetLP_WAKEUPCfgSrc(CSC_LP_WAKEUP_GROUP_0,eLPWakeupCfg->eCfgGrp0);
		CSC0_HWA_SetLP_WAKEUPCfgSrc(CSC_LP_WAKEUP_GROUP_1,eLPWakeupCfg->eCfgGrp1);
		CSC0_HWA_SetLP_WAKEUPCfgSrc(CSC_LP_WAKEUP_GROUP_2,eLPWakeupCfg->eCfgGrp2);
		CSC0_HWA_SetLP_WAKEUPCfgSrc(CSC_LP_WAKEUP_GROUP_3,eLPWakeupCfg->eCfgGrp3);
		CSC0_HWA_SetLP_WAKEUPCfgSrc(CSC_LP_WAKEUP_GROUP_4,eLPWakeupCfg->eCfgGrp4);
		CSC0_HWA_SetLP_WAKEUPCfgPol(CSC_LP_WAKEUP_GROUP_0,eLPWakeupCfg->ePolGrp0);
		CSC0_HWA_SetLP_WAKEUPCfgPol(CSC_LP_WAKEUP_GROUP_1,eLPWakeupCfg->ePolGrp1);
		CSC0_HWA_SetLP_WAKEUPCfgPol(CSC_LP_WAKEUP_GROUP_2,eLPWakeupCfg->ePolGrp2);
		CSC0_HWA_SetLP_WAKEUPCfgPol(CSC_LP_WAKEUP_GROUP_3,eLPWakeupCfg->ePolGrp3);
		CSC0_HWA_SetLP_WAKEUPCfgPol(CSC_LP_WAKEUP_GROUP_4,eLPWakeupCfg->ePolGrp4);

		if(bLockStatus != false)
		{
			CSC0_HWA_LockLP_WAKEUP();
		}

		eRetVal = CSC_E_OK;
	}
	else
	{
		eRetVal = CSC_E_LOCK;
	}
	return eRetVal;
}


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
 * @param bLockStatus    Lock the WPB of CSCx_STOP_MODERy.Once locked, calling the API returns an error(CSC_E_LOCK).
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:      The API is successfully called
 * 			CSC_E_NOT_OK:  eTargetCpuType invalid
 * 			CSC_E_LOCK:    The WPB of CSCx_STOP_MODERx is already locked
 */
CSC_RetStatusType CSC_SetStopModeAckPermission(CSC_WPB_CpuType eTargetCpuType, CSC_WPB_CpuType eCtrlCpuType,
											   CSC_PeriphGrpType ePeriphGrp, bool bLockStatus)
{
    CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
    DEV_ASSERT((uint32_t)eCtrlCpuType < (uint32_t)CSC_WP_CPU_NONE);
    DEV_ASSERT((uint32_t)ePeriphGrp <= (uint32_t)CSC_STOP_CTRL_GROUP_2);

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		if (CSC_STOP_CTRL_GROUP_0 == ePeriphGrp)
		{
			eRetVal = CSC0_SetCpuCtrlGrp0(eCtrlCpuType, CSC_STOPACK, bLockStatus);
		}
		else if (CSC_STOP_CTRL_GROUP_1 == ePeriphGrp)
		{
			eRetVal = CSC0_SetCpuCtrlGrp1(eCtrlCpuType, CSC_STOPACK, bLockStatus);
		}
		else
		{
			eRetVal = CSC0_SetCpuCtrlGrp2(eCtrlCpuType, CSC_STOPACK, bLockStatus);
		}
	}

    return eRetVal;
}

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
											   CSC_PeriphGrpType ePeriphGrp, bool bLockStatus)
{
    CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
    DEV_ASSERT((uint32_t)eCtrlCpuType < (uint32_t)CSC_WP_CPU_NONE);
    DEV_ASSERT((uint32_t)ePeriphGrp <= (uint32_t)CSC_STOP_CTRL_GROUP_2);

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		if (CSC_STOP_CTRL_GROUP_0 == ePeriphGrp)
		{
			eRetVal = CSC0_SetCpuCtrlGrp0(eCtrlCpuType, CSC_STOPREQ, bLockStatus);
		}
		else if (CSC_STOP_CTRL_GROUP_1 == ePeriphGrp)
		{
			eRetVal = CSC0_SetCpuCtrlGrp1(eCtrlCpuType, CSC_STOPREQ, bLockStatus);
		}
		else
		{
			eRetVal = CSC0_SetCpuCtrlGrp2(eCtrlCpuType, CSC_STOPREQ, bLockStatus);
		}
	}

    return eRetVal;
}

/**
 * @brief Set the stop mode ACK of peripheral group 0 in CSC.
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
CSC_RetStatusType CSC_SetStopModeAckGrp0(CSC_WPB_CpuType eTargetCpuType, CSCx_Reg0_PeriphType ePeriphType, bool bEnable)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	CSC_WPB_CpuType eCtrlCpu;

	DEV_ASSERT((ePeriphType == CSC_STOPMODE_FLEXCAN1) ||
			   (ePeriphType == CSC_STOPMODE_FLEXCAN0) ||
			   (ePeriphType == CSC_STOPMODE_FREQM) ||
			   (ePeriphType == CSC_STOPMODE_FCUART3) ||
			   (ePeriphType == CSC_STOPMODE_FCUART2) ||
			   (ePeriphType == CSC_STOPMODE_FCUART1) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI2) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI1) ||
			   (ePeriphType == CSC_STOPMODE_SENT0) ||
			   (ePeriphType == CSC_STOPMODE_TMU) ||
			   (ePeriphType == CSC_STOPMODE_ADC1) ||
			   (ePeriphType == CSC_STOPMODE_ADC0) ||
			   (ePeriphType == CSC_STOPMODE_CMU4) ||
			   (ePeriphType == CSC_STOPMODE_WDOG0) ||
			   (ePeriphType == CSC_STOPMODE_ISM0) ||
			   (ePeriphType == CSC_STOPMODE_DMA0));

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		eCtrlCpu = CSC0_HWA_MODER0_GetCpuWritePermit();

		if((eCtrlCpu == CSC_GET_CPU_ID()) || (eCtrlCpu == CSC_WP_CPU_ALL))
		{
            /* Set peripheral stop ack enable */
			if(bEnable != false)
			{
				CSC0_HWA_MODER0_EnableStopAck(ePeriphType);
			}
			else
			{
				CSC0_HWA_MODER0_DisableStopAck(ePeriphType);
			}
            eRetVal = CSC_E_OK;
		}
		else
		{
			eRetVal = CSC_E_NO_PERM;
		}
	}

	return eRetVal;
}

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
CSC_RetStatusType CSC_SetStopRequestGrp0(CSC_WPB_CpuType eTargetCpuType, CSCx_Reg0_PeriphType ePeriphType, bool bEnable)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	CSC_WPB_CpuType eCtrlCpu;

	DEV_ASSERT((ePeriphType == CSC_STOPMODE_FLEXCAN1) ||
			   (ePeriphType == CSC_STOPMODE_FLEXCAN0) ||
			   (ePeriphType == CSC_STOPMODE_FREQM) ||
			   (ePeriphType == CSC_STOPMODE_FCUART3) ||
			   (ePeriphType == CSC_STOPMODE_FCUART2) ||
			   (ePeriphType == CSC_STOPMODE_FCUART1) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI2) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI1) ||
			   (ePeriphType == CSC_STOPMODE_SENT0) ||
			   (ePeriphType == CSC_STOPMODE_TMU) ||
			   (ePeriphType == CSC_STOPMODE_ADC1) ||
			   (ePeriphType == CSC_STOPMODE_ADC0) ||
			   (ePeriphType == CSC_STOPMODE_CMU4) ||
			   (ePeriphType == CSC_STOPMODE_WDOG0) ||
			   (ePeriphType == CSC_STOPMODE_ISM0) ||
			   (ePeriphType == CSC_STOPMODE_DMA0));

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		eCtrlCpu = CSC0_HWA_REQR0_GetCpuWritePermit();

		if((eCtrlCpu == CSC_GET_CPU_ID()) || (eCtrlCpu == CSC_WP_CPU_ALL))
		{
            /* Set peripheral stop ack enable */
			if(bEnable != false)
			{
				CSC0_HWA_REQR0_SetStopRequest(ePeriphType);
			}
			else
			{
				CSC0_HWA_REQR0_ClearStopRequest(ePeriphType);
			}
            eRetVal = CSC_E_OK;
		}
		else
		{
			eRetVal = CSC_E_NO_PERM;
		}
	}

	return eRetVal;
}

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
CSC_RetStatusType CSC_SetStopModeAckGrp1(CSC_WPB_CpuType eTargetCpuType, CSCx_Reg1_PeriphType ePeriphType, bool bEnable)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	CSC_WPB_CpuType eCtrlCpu;

	DEV_ASSERT((ePeriphType == CSC_STOPMODE_FLEXCAN3) ||
			   (ePeriphType == CSC_STOPMODE_FLEXCAN2) ||
			   (ePeriphType == CSC_STOPMODE_MSC0) ||
			   (ePeriphType == CSC_STOPMODE_FCUART7) ||
			   (ePeriphType == CSC_STOPMODE_FCUART6) ||
			   (ePeriphType == CSC_STOPMODE_FCUART5) ||
			   (ePeriphType == CSC_STOPMODE_FCUART4) ||
			   (ePeriphType == CSC_STOPMODE_FCIIC1) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI5) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI4) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI3) ||
			   (ePeriphType == CSC_STOPMODE_WDOG1));

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		eCtrlCpu = CSC0_HWA_MODER1_GetCpuWritePermit();

		if((eCtrlCpu == CSC_GET_CPU_ID()) || (eCtrlCpu == CSC_WP_CPU_ALL))
		{
            /* Set peripheral stop ack enable */
			if(bEnable != false)
			{
				CSC0_HWA_MODER1_EnableStopAck(ePeriphType);
			}
			else
			{
				CSC0_HWA_MODER1_DisableStopAck(ePeriphType);
			}
            eRetVal = CSC_E_OK;
		}
		else
		{
			eRetVal = CSC_E_NO_PERM;
		}
	}

	return eRetVal;
}

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
CSC_RetStatusType CSC_SetStopRequestGrp1(CSC_WPB_CpuType eTargetCpuType, CSCx_Reg1_PeriphType ePeriphType, bool bEnable)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	CSC_WPB_CpuType eCtrlCpu;

	DEV_ASSERT((ePeriphType == CSC_STOPMODE_FLEXCAN3) ||
			   (ePeriphType == CSC_STOPMODE_FLEXCAN2) ||
			   (ePeriphType == CSC_STOPMODE_MSC0) ||
			   (ePeriphType == CSC_STOPMODE_FCUART7) ||
			   (ePeriphType == CSC_STOPMODE_FCUART6) ||
			   (ePeriphType == CSC_STOPMODE_FCUART5) ||
			   (ePeriphType == CSC_STOPMODE_FCUART4) ||
			   (ePeriphType == CSC_STOPMODE_FCIIC1) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI5) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI4) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI3) ||
			   (ePeriphType == CSC_STOPMODE_WDOG1));

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		eCtrlCpu = CSC0_HWA_REQR1_GetCpuWritePermit();

		if((eCtrlCpu == CSC_GET_CPU_ID()) || (eCtrlCpu == CSC_WP_CPU_ALL))
		{
            /* Set peripheral stop ack enable */
			if(bEnable != false)
			{
				CSC0_HWA_REQR1_SetStopRequest(ePeriphType);
			}
			else
			{
				CSC0_HWA_REQR1_ClearStopRequest(ePeriphType);
			}
            eRetVal = CSC_E_OK;
		}
		else
		{
			eRetVal = CSC_E_NO_PERM;
		}
	}

	return eRetVal;
}

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
CSC_RetStatusType CSC_SetStopModeAckGrp2(CSC_WPB_CpuType eTargetCpuType, CSCx_Reg2_PeriphType ePeriphType, bool bEnable)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	CSC_WPB_CpuType eCtrlCpu;

	DEV_ASSERT((ePeriphType == CSC_STOPMODE_FCUART0) ||
			   (ePeriphType == CSC_STOPMODE_FCIIC0) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI0) ||
			   (ePeriphType == CSC_STOPMODE_CMP1) ||
			   (ePeriphType == CSC_STOPMODE_CMP0) ||
			   (ePeriphType == CSC_STOPMODE_CMU3) ||
			   (ePeriphType == CSC_STOPMODE_CMU2) ||
			   (ePeriphType == CSC_STOPMODE_CMU1) ||
			   (ePeriphType == CSC_STOPMODE_CMU0));

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		eCtrlCpu = CSC0_HWA_MODER2_GetCpuWritePermit();

		if((eCtrlCpu == CSC_GET_CPU_ID()) || (eCtrlCpu == CSC_WP_CPU_ALL))
		{
            /* Set peripheral stop ack enable */
			if(bEnable != false)
			{
				CSC0_HWA_MODER2_EnableStopAck(ePeriphType);
			}
			else
			{
				CSC0_HWA_MODER2_DisableStopAck(ePeriphType);
			}
            eRetVal = CSC_E_OK;
		}
		else
		{
			eRetVal = CSC_E_NO_PERM;
		}
	}

	return eRetVal;
}

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
CSC_RetStatusType CSC_SetStopRequestGrp2(CSC_WPB_CpuType eTargetCpuType, CSCx_Reg2_PeriphType ePeriphType, bool bEnable)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	CSC_WPB_CpuType eCtrlCpu;

	DEV_ASSERT((ePeriphType == CSC_STOPMODE_FCUART0) ||
			   (ePeriphType == CSC_STOPMODE_FCIIC0) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI0) ||
			   (ePeriphType == CSC_STOPMODE_CMP1) ||
			   (ePeriphType == CSC_STOPMODE_CMP0) ||
			   (ePeriphType == CSC_STOPMODE_CMU3) ||
			   (ePeriphType == CSC_STOPMODE_CMU2) ||
			   (ePeriphType == CSC_STOPMODE_CMU1) ||
			   (ePeriphType == CSC_STOPMODE_CMU0));

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		eCtrlCpu = CSC0_HWA_REQR2_GetCpuWritePermit();

		if((eCtrlCpu == CSC_GET_CPU_ID()) || (eCtrlCpu == CSC_WP_CPU_ALL))
		{
            /* Set peripheral stop ack enable */
			if(bEnable != false)
			{
				CSC0_HWA_REQR2_SetStopRequest(ePeriphType);
			}
			else
			{
				CSC0_HWA_REQR2_ClearStopRequest(ePeriphType);
			}
            eRetVal = CSC_E_OK;
		}
		else
		{
			eRetVal = CSC_E_NO_PERM;
		}
	}

	return eRetVal;
}

/**
 * @brief Set the stop mode ACK of all group peripherals in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the peripherals when entering stop mode.
 * @param ePeriphGrp the group of peripherals to set the stop mode ACK value
 * @param u32Value the CSCx_STOP_MODERx register value
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:     The API is successfully called
 * 			CSC_E_NOT_OK: eTargetCpuType invalid
 * 			CSC_E_PARAM:  ePeriphGrp or u32Value invalid
 * 			CSC_E_NO_PERM: Current CPU has no permission to access the register
 */
CSC_RetStatusType CSC_SetStopModeAck(CSC_WPB_CpuType eTargetCpuType, CSC_PeriphGrpType ePeriphGrp, uint32_t u32Value)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	uint32_t eGrpMask[CSC_STOP_PERIPH_GROUP_MAX] = {CSC_STOP_PERIPH_GROUP0_MASK,
													CSC_STOP_PERIPH_GROUP1_MASK,
													CSC_STOP_PERIPH_GROUP2_MASK
												   };

	if((uint32_t)ePeriphGrp >= (uint32_t)CSC_STOP_PERIPH_GROUP_MAX)
	{
		eRetVal = CSC_E_PARAM;
	}
	else if(((~eGrpMask[(uint32_t)ePeriphGrp]) & u32Value) != 0U)
	{
		eRetVal = CSC_E_PARAM;
	}
	else
	{
		if (CSC_WP_CPU_0 == eTargetCpuType)
		{
			eRetVal = CSC0_SetStopModeAck(ePeriphGrp,u32Value);
		}
	}

	return eRetVal;
}

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
 * 			CSC_E_NO_PERM: Current CPU has no permission
 */
CSC_RetStatusType CSC_SetStopRequest(CSC_WPB_CpuType eTargetCpuType, CSC_PeriphGrpType ePeriphGrp, uint32_t u32Value)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	uint32_t eGrpMask[CSC_STOP_PERIPH_GROUP_MAX] = {CSC_STOP_PERIPH_GROUP0_MASK,
													CSC_STOP_PERIPH_GROUP1_MASK,
													CSC_STOP_PERIPH_GROUP2_MASK
												   };

	if((uint32_t)ePeriphGrp >= (uint32_t)CSC_STOP_PERIPH_GROUP_MAX)
	{
		eRetVal = CSC_E_PARAM;
	}
	else if(((~eGrpMask[(uint32_t)ePeriphGrp]) & u32Value) != 0U)
	{
		eRetVal = CSC_E_PARAM;
	}
	else
	{
		if (CSC_WP_CPU_0 == eTargetCpuType)
		{
			eRetVal = CSC0_SetStopRequest(ePeriphGrp,u32Value);
		}
	}

	return eRetVal;
}

/**
 * @brief Get the stop Acknowledge status of peripherals group0 in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the peripherals when entering stop mode.
 * @param ePeriphType the peripheral to get stop acknowledge status
 * @param bool true:  Stop acknowledge is asserted (the module is in Stop mode)
 *			   false: Stop acknowledge is not asserted
 * @return Operation success/failed
 */
CSC_RetStatusType CSC_GetStopAckStatusGrp0(CSC_WPB_CpuType eTargetCpuType,CSCx_Reg0_PeriphType ePeriphType, bool * const pStatus)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	DEV_ASSERT((ePeriphType == CSC_STOPMODE_FLEXCAN1) ||
			   (ePeriphType == CSC_STOPMODE_FLEXCAN0) ||
			   (ePeriphType == CSC_STOPMODE_FREQM) ||
			   (ePeriphType == CSC_STOPMODE_FCUART3) ||
			   (ePeriphType == CSC_STOPMODE_FCUART2) ||
			   (ePeriphType == CSC_STOPMODE_FCUART1) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI2) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI1) ||
			   (ePeriphType == CSC_STOPMODE_SENT0) ||
			   (ePeriphType == CSC_STOPMODE_TMU) ||
			   (ePeriphType == CSC_STOPMODE_ADC1) ||
			   (ePeriphType == CSC_STOPMODE_ADC0) ||
			   (ePeriphType == CSC_STOPMODE_CMU4) ||
			   (ePeriphType == CSC_STOPMODE_WDOG0) ||
			   (ePeriphType == CSC_STOPMODE_ISM0) ||
			   (ePeriphType == CSC_STOPMODE_DMA0));

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		*pStatus = (bool)(0U != CSC0_HWA_ACKR0_GetStopAckStatus(ePeriphType));
		eRetVal = CSC_E_OK;
	}
	return eRetVal;
}

/**
 * @brief Get the stop Acknowledge status of peripherals group1 in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the peripherals when entering stop mode.
 * @param ePeriphType the peripheral to get stop acknowledge status
 * @param bool true:  Stop acknowledge is asserted (the module is in Stop mode)
 *			   false: Stop acknowledge is not asserted
 * @return Operation success/failed
 */
CSC_RetStatusType CSC_GetStopAckStatusGrp1(CSC_WPB_CpuType eTargetCpuType, CSCx_Reg1_PeriphType ePeriphType, bool * const pStatus)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	DEV_ASSERT((ePeriphType == CSC_STOPMODE_FLEXCAN3) ||
			   (ePeriphType == CSC_STOPMODE_FLEXCAN2) ||
			   (ePeriphType == CSC_STOPMODE_MSC0) ||
			   (ePeriphType == CSC_STOPMODE_FCUART7) ||
			   (ePeriphType == CSC_STOPMODE_FCUART6) ||
			   (ePeriphType == CSC_STOPMODE_FCUART5) ||
			   (ePeriphType == CSC_STOPMODE_FCUART4) ||
			   (ePeriphType == CSC_STOPMODE_FCIIC1) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI5) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI4) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI3) ||
			   (ePeriphType == CSC_STOPMODE_WDOG1));

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		*pStatus = (bool)(0U != CSC0_HWA_ACKR1_GetStopAckStatus(ePeriphType));
		eRetVal = CSC_E_OK;
	}
	return eRetVal;
}

/**
 * @brief Get the stop Acknowledge status of peripherals group2 in CSC.
 *
 * @param eTargetCpuType The target CPU which acknowledges the peripherals when entering stop mode.
 * @param ePeriphType the peripheral to get stop acknowledge status
 * @param bool true:  Stop acknowledge is asserted (the module is in Stop mode)
 *			   false: Stop acknowledge is not asserted
 * @return Operation success/failed
 */
CSC_RetStatusType CSC_GetStopAckStatusGrp2(CSC_WPB_CpuType eTargetCpuType,CSCx_Reg2_PeriphType ePeriphType, bool * const pStatus)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	DEV_ASSERT((ePeriphType == CSC_STOPMODE_FCUART0) ||
			   (ePeriphType == CSC_STOPMODE_FCIIC0) ||
			   (ePeriphType == CSC_STOPMODE_FCSPI0) ||
			   (ePeriphType == CSC_STOPMODE_CMP1) ||
			   (ePeriphType == CSC_STOPMODE_CMP0) ||
			   (ePeriphType == CSC_STOPMODE_CMU3) ||
			   (ePeriphType == CSC_STOPMODE_CMU2) ||
			   (ePeriphType == CSC_STOPMODE_CMU1) ||
			   (ePeriphType == CSC_STOPMODE_CMU0));

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		*pStatus = (bool)(0U != CSC0_HWA_ACKR2_GetStopAckStatus(ePeriphType));
		eRetVal = CSC_E_OK;
	}
	return eRetVal;
}

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
CSC_RetStatusType CSC_GetStopAckStatus(CSC_WPB_CpuType eTargetCpuType,CSC_PeriphGrpType ePeriphGrp, uint32_t * const pU32Status)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	DEV_ASSERT((uint32_t)ePeriphGrp <= (uint32_t)CSC_STOP_CTRL_GROUP_2);

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		*pU32Status = CSC0_GetStopAckStatus(ePeriphGrp);
		eRetVal = CSC_E_OK;
	}
	return eRetVal;
}

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
CSC_RetStatusType CSC_SetCCMCfgPermission(CSC_WPB_CpuType eTargetCpuType, CSC_WPB_CpuType eCtrlCpuType, bool bLockStatus)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	DEV_ASSERT((uint32_t)eCtrlCpuType < (uint32_t)CSC_WP_CPU_NONE);

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		if (0U == CSC0_HWA_CCM0_GetWPBLockStatus())
		{
			CSC0_HWA_CCM0_SetCpuWritePermit(eCtrlCpuType);

			if(bLockStatus != false)
			{
				CSC0_HWA_CCM0_LockWritePermit();
			}
			eRetVal = CSC_E_OK;
		}
		else
		{
			eRetVal = CSC_E_LOCK;
		}
	}
	return eRetVal;
}

/**
 * @brief Set the CCM configuration of CPUx indicated by eTargetCpuType.
 *
 * @param eTargetCpuType The target CPU controlled by CSCx_CCMx_CFG register.
 * @param pCCMCfg   Pointer to the configuration of CSCx_CCMx_CFG register.
 *
 * @return CSC_RetStatusType
 * 			CSC_E_OK:     The API is successfully called
 * 			CSC_E_NOT_OK: eTargetCpuType invalid
 * 			CSC_E_LOCK:   Current CPU has no permission
 */
CSC_RetStatusType CSC_SetCCMConfiguration(CSC_WPB_CpuType eTargetCpuType,const CSC_CCMCfgType *const pCCMCfg)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	CSC_WPB_CpuType eCtrlCpu;

	DEV_ASSERT(pCCMCfg != NULL_PTR);
	DEV_ASSERT(pCCMCfg->eHandShakeMode == CSC_WAIT_ALL_ACK ||
			   pCCMCfg->eHandShakeMode == CSC_WAIT_REQ_ACK);

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		eCtrlCpu = CSC0_HWA_CCM0_GetCpuWritePermit();

		if((eCtrlCpu == CSC_GET_CPU_ID()) || (eCtrlCpu == CSC_WP_CPU_ALL))
		{
			CSC0_HWA_HClockEnable(pCCMCfg->HclkEn);
			CSC0_HWA_SetHandShakeMode(pCCMCfg->eHandShakeMode);
			eRetVal = CSC_E_OK;
		}
		else
		{
			eRetVal = CSC_E_LOCK;
		}
	}
	return eRetVal;
}

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
CSC_RetStatusType CSC_GetCCMStopClockStatus(CSC_WPB_CpuType eTargetCpuType, CSCx_CCM_StopClockType eCCMType, bool * const pStatus)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;

	DEV_ASSERT(pStatus != NULL_PTR);
	DEV_ASSERT(eCCMType == CSC_CCM_STOPCLOCK_STATUS_SYS_SLAVE ||
			   eCCMType == CSC_CCM_STOPCLOCK_STATUS_MASTER ||
			   eCCMType == CSC_CCM_STOPCLOCK_STATUS_SLOW_SLAVE ||
			   eCCMType == CSC_CCM_STOPCLOCK_STATUS_BUS_SLAVE);

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		*pStatus = (bool)(0u != CSC0_HWA_CCM0_GetClockStatus(eCCMType));
		eRetVal = CSC_E_OK;
	}
	return eRetVal;
}

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
CSC_RetStatusType CSC_SetCpuIntPermission(CSC_WPB_CpuType eTargetCpuType, CSC_WPB_CpuType eCtrlCpuType, bool bLockStatus)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	DEV_ASSERT((uint32_t)eCtrlCpuType < (uint32_t)CSC_WP_CPU_NONE);

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		if (0U == CSC0_HWA_CPU0INT_GetWPBLockStatus())
		{
			CSC0_HWA_CPU0INT_SetCpuWritePermit(eCtrlCpuType);

			if(bLockStatus != false)
			{
				CSC0_HWA_CPU0INT_LockWritePermit();
			}
			eRetVal = CSC_E_OK;
		}
		else
		{
			eRetVal = CSC_E_LOCK;
		}
	}
	return eRetVal;
}

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
CSC_RetStatusType CSC_CpuSwInterruptGen(CSC_WPB_CpuType eTargetCpuType, bool bEnable)
{
	CSC_RetStatusType eRetVal = CSC_E_NOT_OK;
	CSC_WPB_CpuType eCtrlCpu;

	if (CSC_WP_CPU_0 == eTargetCpuType)
	{
		eCtrlCpu = CSC0_HWA_CPU0INT_GetCpuWritePermit();

		if((eCtrlCpu == CSC_GET_CPU_ID()) || (eCtrlCpu == CSC_WP_CPU_ALL))
		{
			if(bEnable != false)
			{
				CSC0_HWA_CPU0INT_EnableSWInterrupt();
			}
			else
			{
				CSC0_HWA_CPU0INT_DisableSWInterrupt();
			}
			eRetVal = CSC_E_OK;
		}
		else
		{
			eRetVal = CSC_E_LOCK;
		}
	}
	return eRetVal;
}
