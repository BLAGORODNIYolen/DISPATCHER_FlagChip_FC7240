/**
 * @file fc7xxx_driver_cmu.c
 * @author Flagchip085
 * @brief FC7xxx CMU driver type definition and API
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
*   0.1.0       2024-01-12    Flagchip085    N/A          First version for FC7240
********************************************************************************/
#include "fc7xxx_driver_cmu.h"
#include "fc7xxx_driver_scg.h"
#include "fc7xxx_driver_csc.h"
#include "HwA_cmu.h"

#define CMU_MULTIPLY_FACTOR 100U
#define CMU_PERCENT_FACTOR 100U
#define CMU_DIVID_FACTOR_1K 1000U

/** @brief CMU Reference clock div type. */

/**
 * @brief Defines the CMU_ClkFrequenceType
 *
 * This structure is used to configure the CMU frequence include Reference clock and monitor clock
 *
 */
typedef struct
{
    uint32_t u32RefClk;                /*!< The Reference clock frequence */
    uint32_t u32MonitorClk;            /*!< The target monitored clock frequence. */
} CMU_ClkFrequenceType;

typedef struct
{
    uint32_t u32RefWindow;               /*!< CMU_REF_WINDOW (Reference Window). */
    uint32_t u32IdealMonitorCnts;        /*!< Ideal monitor counter value, used to calculate the MIN,Max threshold. */
    uint32_t u32MinThreshold;            /*!< CMU_MIN (Minimum threshold). */
    uint32_t u32MaxThreshold;            /*!< CMU_MAX (Maximum threshold). */
    uint32_t u32PerWindow;               /*!< CMU_PERIOD (Period monitor mode configuration). */
} CMU_RegMapType;


static CMU_Type *const s_apCmuBase[CMU_INSTANCE_COUNT] = CMU_BASE_PTRS;
static CMU_ISRCallbackType s_apCmuISRCallback[CMU_INSTANCE_COUNT] = {NULL};

void CMU0_IRQHandler(void);
void CMU1_IRQHandler(void);
void CMU2_IRQHandler(void);
void CMU3_IRQHandler(void);
void CMU4_IRQHandler(void);

/* Check Reference clock and monitor clock status.*/
static CMU_StatusType CMU_ClkStatusCheck(CMU_InstanceType eInstance, CMU_ClkFrequenceType *ptCmuFreq)
{
    CSC_RetStatusType bCscClkStatus;
    CMU_StatusType bCmuClkStatus = CMU_VALID;

    if (eInstance == CMU_INSTANCE_0)
    {
        /* Instance ---- Reference CLK  ---- Monitored CLK.*/
        /* CMU0     ---- SIRC            ---- RTC_CLK.*/
        ptCmuFreq->u32RefClk = SCG_GetScgClockFreq(SCG_SIRC_CLK);

        bCscClkStatus = CSC0_GetCSC0ClockFreq(CSC0_RTC_CLK, &(ptCmuFreq->u32MonitorClk));
        if (bCscClkStatus != CSC_E_OK)
        {
            bCmuClkStatus = CMU_CLK_ERROR;
        }
    }
    else if (eInstance == CMU_INSTANCE_1)
    {
        /* Instance ---- Reference CLK  ---- Monitored CLK.*/
        /* CMU1     ---- SIRC            ---- FOSC.*/
        ptCmuFreq->u32RefClk = SCG_GetScgClockFreq(SCG_SIRC_CLK);
        ptCmuFreq->u32MonitorClk = SCG_GetScgClockFreq(SCG_FOSC_CLK);
    }
    else if (eInstance == CMU_INSTANCE_2)
    {
        /* Instance ---- Reference CLK  ---- Monitored CLK.*/
        /* CMU2     ---- SIRC            ---- FIRC.*/
        ptCmuFreq->u32RefClk = SCG_GetScgClockFreq(SCG_SIRC_CLK);
        ptCmuFreq->u32MonitorClk = SCG_GetScgClockFreq(SCG_FIRC_CLK);
    }
    else if (eInstance == CMU_INSTANCE_3)
    {
        /* Instance ---- Reference CLK  ---- Monitored CLK.*/
        /* CMU3     ---- FIRC            ---- SIRC.*/
        ptCmuFreq->u32RefClk = SCG_GetScgClockFreq(SCG_FIRC_CLK);
        ptCmuFreq->u32MonitorClk = SCG_GetScgClockFreq(SCG_SIRC_CLK);
    }
    else if (eInstance == CMU_INSTANCE_4)
    {
        /* Instance ---- Reference CLK  ---- Monitored CLK.*/
        /* CMU4     ---- SIRC            ---- SLOW CLOCK.*/
        ptCmuFreq->u32MonitorClk = SCG_GetScgClockFreq(SCG_SLOW_CLK);
        ptCmuFreq->u32RefClk = SCG_GetScgClockFreq(SCG_CMU4REF_CLK);
    }
    else
    {
    	/* Never come here */
    	bCmuClkStatus = CMU_CLK_ERROR;
    }

    if(bCmuClkStatus == CMU_VALID)
    {
    	if ((ptCmuFreq->u32MonitorClk == 0U) || (ptCmuFreq->u32RefClk == 0U))
    	{
    		bCmuClkStatus = CMU_CLK_ERROR;
    	}
    }

    return bCmuClkStatus;
}

CMU_StatusType CMU_Init(CMU_InstanceType eInstance, const CMU_CfgType *pInitCfg)
{
    CMU_StatusType eStatus;
    CMU_Type *pCmu;
    CMU_RefClockDivType eDiv;
    CMU_ClkFrequenceType tCmuFreq;
    uint32_t u32RefWindow, u32MaxRefWindow, u32MinRefWindow;
    uint32_t u32MonitorCnts, u32MinMonitorCnts, u32MaxMonitorCnts;
    uint32_t u32RefClk, u32MonitorClk;
    uint32_t u32Temp;

    DEV_ASSERT((uint8_t)eInstance < CMU_INSTANCE_COUNT);
    DEV_ASSERT(pInitCfg != NULL);
    pCmu = s_apCmuBase[(uint8_t)eInstance];
    eDiv = pInitCfg->eDiv;

	/* Check Reference clock and monitor clock status.*/
	eStatus = CMU_ClkStatusCheck(eInstance, &tCmuFreq);

	if (eStatus == CMU_VALID)
	{
        /* divide the clock value by 1K_factor */
        u32RefClk = (tCmuFreq.u32RefClk >> eDiv) / CMU_DIVID_FACTOR_1K;
        u32MonitorClk = tCmuFreq.u32MonitorClk / CMU_DIVID_FACTOR_1K;

        if (u32RefClk / u32MonitorClk <= 0x100U)
		{
			u32MaxRefWindow = (0xffffffU - 3U) / u32MonitorClk * u32RefClk / 105U * CMU_PERCENT_FACTOR - 2U;

			if (u32MaxRefWindow > 0xffffffU)
			{
				u32MaxRefWindow = 0xffffffU;
			}
		}
		else
		{
			u32MaxRefWindow = 0xffffffU;
		}

		u32MinRefWindow = 6U + 5U * u32RefClk / u32MonitorClk;
		u32RefWindow = 100U * u32MinRefWindow;

		if (u32RefWindow > u32MaxRefWindow)
		{
			u32RefWindow = u32MaxRefWindow;
		}

		u32MonitorCnts = u32MonitorClk * (u32RefWindow + 2U) / u32RefClk;
		u32MinMonitorCnts = u32MonitorCnts * 95U / CMU_PERCENT_FACTOR - 3U;
		u32MaxMonitorCnts = u32MonitorCnts * 105U / CMU_PERCENT_FACTOR + 3U;

		CMU_HWA_SetRefWindow(pCmu, u32RefWindow);
		CMU_HWA_SetMinCnts(pCmu, u32MinMonitorCnts);
		CMU_HWA_SetMaxCnts(pCmu, u32MaxMonitorCnts);

		/* Program program PERIOD[EN] and PERIOD[WINDOW]. */
		CMU_HWA_SetPeriodEnable(pCmu, false);
		if (pInitCfg->bPerMonitorEnable == true)
		{
			 uint8_t u8MaxPeriod = (uint8_t)(u32RefClk / u32RefWindow);

			if ((u8MaxPeriod >> (uint8_t)CMU_PERIOD_WINDOW_WIDTH) != 0U)
			{
				u8MaxPeriod = (1U << (uint8_t)CMU_PERIOD_WINDOW_WIDTH) - 1U;
			}

			if (u8MaxPeriod != 0U)
			{
				if (pInitCfg->u8PerMonitorWindow <= u8MaxPeriod)
				{
					CMU_HWA_SetPeriodWindow(pCmu, (uint32_t)(pInitCfg->u8PerMonitorWindow));
				}
				else
				{
					CMU_HWA_SetPeriodWindow(pCmu, (uint32_t)(u8MaxPeriod));
				}
				CMU_HWA_SetPeriodEnable(pCmu, pInitCfg->bPerMonitorEnable);
			}
		}

		/* Program DIV,IRQ_EN,LP_EN,STOP_EN,ENABLE */
		u32Temp = CMU_HWA_GetCTRL(pCmu);
		u32Temp &= ~(uint32_t)(CMU_CTRL_REF_DIV_MASK | CMU_CTRL_IRQ_EN_MASK | \
							   CMU_CTRL_LP_EN_MASK | CMU_CTRL_STOP_EN_MASK | CMU_CTRL_ENABLE_MASK);
		u32Temp |= (uint32_t)(CMU_CTRL_REF_DIV(eDiv) | CMU_CTRL_IRQ_EN(pInitCfg->bIntEnable) | \
							  CMU_CTRL_LP_EN(pInitCfg->bLpen) | CMU_CTRL_STOP_EN(pInitCfg->bSten) | \
							  CMU_CTRL_ENABLE(pInitCfg->bEnable));
		CMU_HWA_SETCTRL(pCmu, u32Temp);

		s_apCmuISRCallback[(uint8_t)eInstance] = pInitCfg->pIsrCallback;
	}
	else
	{
		/* clock status invalid, change, do nothing */
	}

    return eStatus;
}

void CMU_Enable(CMU_InstanceType eInstance)
{
	DEV_ASSERT((uint8_t)eInstance < CMU_INSTANCE_COUNT);
    CMU_HWA_Enable(s_apCmuBase[(uint8_t)eInstance]);
}

void CMU_Disable(CMU_InstanceType eInstance)
{
	CMU_Type *pCmu;

	DEV_ASSERT((uint8_t)eInstance < CMU_INSTANCE_COUNT);
    pCmu = s_apCmuBase[(uint8_t)eInstance];

    CMU_HWA_Disable(pCmu);
    CMU_HWA_ClearST(pCmu);
}

void CMU_EnableInterrupt(CMU_InstanceType eInstance)
{
	DEV_ASSERT((uint8_t)eInstance < CMU_INSTANCE_COUNT);
    CMU_HWA_IrqEnable(s_apCmuBase[(uint8_t)eInstance],true);
}

void CMU_DisableInterrupt(CMU_InstanceType eInstance)
{
	DEV_ASSERT((uint8_t)eInstance < CMU_INSTANCE_COUNT);
    CMU_HWA_IrqEnable(s_apCmuBase[(uint8_t)eInstance],false);
}

CMU_InterruptType CMU_GetInterruptType(CMU_InstanceType eInstance)
{
    uint32_t u32Temp;
    CMU_InterruptType eStatus;

    DEV_ASSERT((uint8_t)eInstance < CMU_INSTANCE_COUNT);

    u32Temp = CMU_HWA_GetST(s_apCmuBase[(uint8_t)eInstance]);
    if ((u32Temp & CMU_ST_LOC_MASK) != 0U)
    {
        eStatus = CMU_INTERRUPT_LOC;
    }
    else if ((u32Temp & CMU_ST_MIS_MASK) != 0U)
    {
        eStatus = CMU_INTERRUPT_MIS;
    }
    else
    {
    	eStatus = CMU_INTERRUPT_NONE;
    }

    return eStatus;
}

CMU_StatusType CMU_SetCmu4RefSrc(CMU_Cmu4ClkSrcType eSrc)
{
	SCG_StatusType eStatus;

    SCG_HWA_SetCmu4Clk(0U);

    if (CMU_CMU4_REF_CLK_FOSC == eSrc)
    {
        eStatus = SCG_SetCmu4Clk(SCG_CMU4CLK_SRC_FOSC);
    }
    else if (CMU_CMU4_REF_CLK_SIRC == eSrc)
    {
        eStatus = SCG_SetCmu4Clk(SCG_CMU4CLK_SRC_SIRC);
    }
    else
    {
    	eStatus = SCG_STATUS_PARAM_ERROR;
    }

    return (eStatus == SCG_STATUS_SUCCESS) ? CMU_VALID : CMU_CLK_ERROR;
}

uint32_t CMU_GetCount(CMU_InstanceType eInstance)
{
	DEV_ASSERT((uint8_t)eInstance < CMU_INSTANCE_COUNT);

    return CMU_HWA_GetCount(s_apCmuBase[(uint8_t)eInstance]);
}

uint32_t CMU_GetMinCount(CMU_InstanceType eInstance)
{
	DEV_ASSERT((uint8_t)eInstance < CMU_INSTANCE_COUNT);

    return CMU_HWA_GetMinCnts(s_apCmuBase[(uint8_t)eInstance]);
}

uint32_t CMU_GetMaxCount(CMU_InstanceType eInstance)
{
	DEV_ASSERT((uint8_t)eInstance < CMU_INSTANCE_COUNT);

    return CMU_HWA_GetMaxCnts(s_apCmuBase[(uint8_t)eInstance]);
}

void CMU_LowPowerModeEnable(CMU_InstanceType eInstance, CMU_LowpowerModeType eMode, bool bModeEnable, bool bRestartEnable)
{
	CMU_Type *pCmu;

	DEV_ASSERT((uint8_t)eInstance < CMU_INSTANCE_COUNT);
    pCmu = s_apCmuBase[(uint8_t)eInstance];

    if (eMode == CMU_STANDBY_MODE)
    {
        CMU_HWA_StopModeEnable(pCmu, bModeEnable);
        CMU_HWA_StanbyModeEnable(pCmu, bModeEnable);
    }
    else if (eMode == CMU_STOP_MODE)
    {
        CMU_HWA_StopModeEnable(pCmu, bModeEnable);
    }
    else
    {

    }

    CMU_HWA_LPRestartEnable(pCmu, bRestartEnable);
}


/***************CMU IRQ Functions*****************/

static void CMU_IRQHandler(CMU_InstanceType eInstance)
{
	CMU_Type *pCmu;
    CMU_InterruptType eStatus;

    DEV_ASSERT((uint8_t)eInstance < CMU_INSTANCE_COUNT);
    pCmu = s_apCmuBase[(uint8_t)eInstance];

    eStatus = CMU_GetInterruptType(eInstance);

    if (s_apCmuISRCallback[(uint8_t)eInstance] != NULL)
    {
        s_apCmuISRCallback[(uint8_t)eInstance](eInstance, eStatus);
    }

    CMU_HWA_ClearST(pCmu);
}

void CMU0_IRQHandler(void)
{
    CMU_IRQHandler(CMU_INSTANCE_0);
}

void CMU1_IRQHandler(void)
{
    CMU_IRQHandler(CMU_INSTANCE_1);
}

void CMU2_IRQHandler(void)
{
    CMU_IRQHandler(CMU_INSTANCE_2);
}

void CMU3_IRQHandler(void)
{
    CMU_IRQHandler(CMU_INSTANCE_3);
}

void CMU4_IRQHandler(void)
{
    CMU_IRQHandler(CMU_INSTANCE_4);
}
