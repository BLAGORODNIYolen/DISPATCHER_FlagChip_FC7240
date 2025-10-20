/**
 * @file fc7xxx_driver_stcu.c
 * @author Flagchip
 * @brief FC4xxx stcu driver type definition and API
 * @version 0.1.0
 * @date 2023-02-15
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */

/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Author        CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       1/10/2024    Flagchip0095       N/A          First version for FC7240
   ******************************************************************************** */
#include "HwA_stcu.h"
#include "fc7xxx_driver_stcu.h"



/* ################################################################################## */
/* ##################################### Macros ##################################### */
#define STCU_SAFETY_KEY             (0xBB40E64DU)
#define STCU_RECOMMENDED_PATTERN    (0xBUL)


/* ################################################################################## */
/* ################################# Local Variables ################################ */

/* ################################################################################## */
/* ########################### Local Functions Prototype ############################ */

/* ################################################################################## */
/* ######################### Global Functions prototype ############################ */
void STCU0_IRQHandler(void);

/* ################################################################################## */
/* ################################# Local Functions ############################### */
static Stcu_IRQCallback sIRQCallback = NULL;

/* ################################################################################## */
/* ################################# Global Functions ############################### */

/**
 * \brief Init the STCU module
 *
 * \param pConfig the configuration structure
 */
void STCU_Init(STCU_ConfigType *pConfig)
{
    uint32_t u32Reg;

    STCU_HWA_MbistSelect(pConfig->u32MbistSel);

	STCU_HWA_SetMBISTSWAlg(pConfig->bMbistFullTest, pConfig->bMbistSramInit);

	pConfig->bInterruptEn?STCU_HWA_EnableInterrupt():STCU_HWA_DisableInterrupt();

	sIRQCallback = pConfig->pIrqCallback;

	u32Reg = STCU_SELF_TEST_CTRL_LBIST_CLKDIV((uint32_t)(pConfig->eLbistClkDivider))  |
             STCU_SELF_TEST_CTRL_LBIST_EN(pConfig->bLbistEn?1UL:0UL)       |
             STCU_SELF_TEST_CTRL_MBIST_LP(pConfig->bMbistLPC?1UL:0UL)      |
             STCU_SELF_TEST_CTRL_MBIST_EN(pConfig->bMbistEn?1UL:0UL)   |
             STCU_SELF_TEST_CTRL_CLK_SEL((uint32_t)(pConfig->eClkSource))  |
             STCU_SELF_TEST_CTRL_MT(pConfig->u16MaxTime)                   |
			 STCU_SELF_TEST_CTRL_PE(STCU_PORT_PULL_DISABLE == pConfig->ePortPullMode?0UL:1UL)  |
			 STCU_SELF_TEST_CTRL_PS(STCU_PORT_PULL_UP == pConfig->ePortPullMode?1UL:0UL)  |
             STCU_SELF_TEST_CTRL_FCSMU_TRIG(0U)    |  /* FCSMU reset will trigger self-test   */
             STCU_SELF_TEST_CTRL_LBIST_TD(1U)      |  /* enable LBIST at-speed test */
             STCU_SELF_TEST_CTRL_SCHK_EN(1U)       |  /* self check enable */
             STCU_SELF_TEST_CTRL_STEST_BYPASS(0U);/* self-test will be not bypassed */

	STCU_HWA_SetSelfTestCTRL(u32Reg);
}

/**
 * \brief Set the LBIST Pattern value and expected misr value.
 *        The two value should be load from NVR, but also can reconfigure by this API.
 *        The expected misr value is calculated from pattern, so please make sure this two value is right, or the LBST would fail.
 *
 * \param u16Pattern the LBIST Pattern value
 * \param u16Pattern the LBIST expected misr value
 */
void STCU_LBIST_Set_Pattern_Misr(uint16_t u16Pattern, uint32_t u32ExpectedMisr)
{
	STCU_HWA_SetLBISTPatternAmount(u16Pattern);
	STCU_HWA_SetExpectedMisr(u32ExpectedMisr);
}

/**
 * \brief Trigger to start Software self test
 *
 */
void STCU_StartSelfTest(void)
{
	/* clear STCU_SELF_TEST_STATUS. */
	STCU_HWA_ClearSelfTestStatus();

	STCU_HWA_SetSafetyKey(STCU_SAFETY_KEY); /* enable STCU_SELF_TEST_CTRL A/B access */

    /* set the TRIG bits in both STCU_SELF_TEST_TRIG_A and STCU_SELF_TEST_TRIG_B. */
	STCU_HWA_SwTriggerA();
	STCU_HWA_SwTriggerB();
}

/**
 * \brief Check Software Trigger Self-test result. If the LBIST is done, could call "STCU_GetLbistFailResult" to check the test result.
 *        If the MBIST is done, could call "STCU_GetMbistFailResult" to check the test result.
 *
 * \return refer to "STCU_SelfTestStatusType" enum.
 */
uint32_t STCU_CheckTriggerResult(void)
{
    return STCU_HWA_GetSelfTestStatus();
}

/**
 * \brief Get each MBIST Fail result
 *
 * \return refer to "STCU_MbistFailedType" enum.
 */
uint32_t STCU_GetMbistFailResult(void)
{
	uint32_t u32Done, u32Fail;

	u32Done = STCU_GetMbistDone();
	u32Fail = STCU_GetMbistFail();

	return (u32Done & u32Fail);
}

/**
 * \brief Get if the LBIST test result is Fail
 *
 * \return true means LBIST fail. false means LBIST pass.
 */
bool STCU_GetLbistFailResult(void)
{
	uint32_t u32status;

	u32status = STCU_HWA_CheckLbistStatus();

	u32status = (u32status >> STCU_LBIST_STATUS_FAIL_SHIFT) & (u32status & STCU_LBIST_STATUS_DONE_MASK);

	return (0UL == u32status?false:true);
}

/**
 * \brief Initial DTCM with hardware
 */
void STCU_StartRamInit(STCU_InitRamConfigType *pInitCfg)
{
    STCU_HWA_SetRamInitType( pInitCfg->u32InitRamType);
    STCU_HWA_StartRamInit(pInitCfg->eInitMode,pInitCfg->bLockAfterEn);
}

/**
 * \brief Get status of RAM initialize action, for more detail, could call "STCU_GetRamInitDoneStatus"
 *        to get more info for each SRAM
 * \return the status of ram initialize action, refer to "STCU_HardwareInitRamStatusType"
 */
uint32_t STCU_GetRamInitStatus(void)
{
	return STCU_HWA_GetRamInitStatus();
}

/**
 * \brief Get each done status of SRAM initialize
 *
 * \return the done status of SRAM initialize action, refer to "STCU_InitRamDoneType"
 */
uint32_t STCU_GetRamInitDoneStatus(void)
{
	return STCU_HWA_GetRamInitDone();
}

/**
 * \brief Get LBIST actual MISR value, the value should be read and use DFT tool to decode it, if LBIST test resault is fail.
 *
 * \return the LBIST actual MISR value
 */
uint32_t STCU_GetLbistAcutalMisr(void)
{
	return STCU_HWA_GetActualMisr();
}


void STCU0_IRQHandler(void)
{
	uint32_t u32Flag;

	u32Flag = STCU_HWA_GetInterruptFlag();
	STCU_HWA_ClearInterruptFlag();
	if(NULL != sIRQCallback)
	{
		sIRQCallback(u32Flag);
	}
}
