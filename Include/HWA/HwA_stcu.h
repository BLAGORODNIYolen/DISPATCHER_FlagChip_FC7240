/**
 * @file HwA_stcu.h
 * @author Flagchip
 * @brief Safety Test and Control Unit
 * @version 0.1.0
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       03/08/2022    Flagchip038   N/A          First version for FC7xxx
   ******************************************************************************** */

#ifndef _HWA_STCU_H_
#define _HWA_STCU_H_

#include "device_header.h"
#include "fc7xxx_driver_stcu.h"

/**
 * \brief Get Self Test Status
 *
 * \return Status, maybe more than one status, refer to "STCU_SelfTestStatusType"
 */
LOCAL_INLINE uint32_t STCU_HWA_GetSelfTestStatus(void)
{
    return STCU->SELF_TEST_STATUS;
}

/**
 * \brief Clear all Self Test Status
 */
LOCAL_INLINE void STCU_HWA_ClearSelfTestStatus(void)
{
	STCU->SELF_TEST_STATUS = 0x0UL;
}


/**
 * \brief Mbist select for self-test
 *
 * \param u32MbistSel maybe more than one
 */
LOCAL_INLINE void STCU_HWA_MbistSelect(uint32_t u32MbistSel)
{
    STCU->MBIST_SEL = u32MbistSel;
}

/**
 * \brief Get Mbist Done Flag
 *
 * \return All Mbist Done flags, refer to "STCU_MbistDoneType"
 */
LOCAL_INLINE uint32_t STCU_GetMbistDone(void)
{
    return STCU->MBIST_DONE_STATUS;
}

/**
 * \brief Get Mbist Fail Flag
 *
 * \return All Mbist Fail flags  "STCU_MbistFailedType"
 */
LOCAL_INLINE uint32_t STCU_GetMbistFail(void)
{
    return STCU->MBIST_FAIL_STATUS;
}

/**
 * \brief Check Lbist execution failed status
 *
 * \return LBIST status, refer to "STCU_LbistStatusType"
 */
LOCAL_INLINE uint32_t STCU_HWA_CheckLbistStatus(void)
{
    return STCU->LBIST_STATUS;
}


/**
 * \brief Get STCU Hardware Ram Initial Status
 *
 * \return Initial Status, refer to "STCU_HardwareInitRamStatusType"
 */
LOCAL_INLINE uint32_t STCU_HWA_GetHardwareRamInitStatus(void)
{
    return STCU->SRAM_INI_STATUS;
}

/**
 * \brief STCU RAM Init Mode set, can select more than one, for example: STCU_INIT_RAM_TYPE_SRAM0 | STCU_INIT_RAM_TYPE_SRAM1
 *
 * \param u32InitRamType Init Mode
 */
LOCAL_INLINE void STCU_HWA_SetRamInitType(uint32_t u32InitRamType)
{
    STCU->SRAM_INI_SEL = u32InitRamType;
}

/**
 * \brief Set STCU Interrupt
 *
 * \param bIntEn  Normal interrupt enable
 * \param bSequenceErrorIntEn Sequence error interrupt enable
 * \param bSizeErrorIntEn Size error interrupt enable
 */
LOCAL_INLINE void STCU_HWA_SetInterrupt(uint8_t bIntEn, uint8_t bSequenceErrorIntEn, uint8_t bSizeErrorIntEn)
{
    STCU->IRQ = STCU_IRQ_EN(bIntEn) | STCU_IRQ_SEQ_ERR(bSequenceErrorIntEn) | STCU_IRQ_SIZE_ERR(bSizeErrorIntEn);
}

/**
 * \brief STCU Ram Initial Start
 *
 * \param eInitRamMode Initial mode
 * \param bEnable Enable Initial
 * \param bLock Lock after initial
 */
LOCAL_INLINE void STCU_HWA_StartRamInit(STCU_InitRamModeType eInitRamMode, uint8_t bLock)
{
    STCU->SRAM_INI_CTRL = STCU_SRAM_INI_CTRL_MODE(eInitRamMode) | STCU_SRAM_INI_CTRL_EN_MASK  | STCU_SRAM_INI_CTRL_LOCK(bLock) ;
}

/**
 * \brief Get Ram Initial Done flag
 *
 * \return All Done flag, maybe more than one flag, refer to "STCU_InitRamDoneType"
 */
LOCAL_INLINE uint32_t STCU_HWA_GetRamInitDone(void)
{
    return STCU->SRAM_INI_DONE_STATUS;
}

/**
 * \brief Get Ram Initial status
 *
 * \return All Done flag, maybe more than one flag, refer to "STCU_HardwareInitRamStatusType"
 */
LOCAL_INLINE uint32_t STCU_HWA_GetRamInitStatus(void)
{
    return STCU->SRAM_INI_STATUS;
}

/**
 * \brief Set the LBIST pattern amount control value N.
 *
 * \param u32Amount  LBIST pattern amount control value N. (pattern amount = N * 256)
 */
LOCAL_INLINE void STCU_HWA_SetLBISTPatternAmount(uint32_t u32Amount)
{
    STCU->LBIST_PAT_CTRL = u32Amount;
}

/**
 * \brief Set the MBIST algorithm for SW trigger self-test
 *
 * \param bFullTest  Enable Full test for MBIST.
 * \param bSRAMInit  Enable SRAM initialization at the end of software trigger self-test.
 */
LOCAL_INLINE void STCU_HWA_SetMBISTSWAlg(bool bFullTest, bool bSRAMInit)
{
    STCU->MBIST_ALG = (STCU->MBIST_ALG & ~(STCU_MBIST_ALG_TRIG_ALG_SEL_MASK | STCU_MBIST_ALG_TRIG_INI_EN_MASK)) | \
    		(STCU_MBIST_ALG_TRIG_ALG_SEL(bFullTest?0X1FU:0x19U) | STCU_MBIST_ALG_TRIG_INI_EN(bSRAMInit?0x1U:0x0U));
}

/**
 * \brief Set safety key
 *
 * \param u32Key   Safety Key.
 */
LOCAL_INLINE void STCU_HWA_SetSafetyKey(uint32_t u32Key)
{
	STCU->SELF_TEST_KEY = u32Key;
}

/**
 * \brief Enable A self-test software trigger.
 */
LOCAL_INLINE void STCU_HWA_SwTriggerA(void)
{
    STCU->SELF_TEST_TRIG_A = STCU_SELF_TEST_TRIG_A_MASK;
}

/**
 * \brief Enable B self-test software trigger.
 */
LOCAL_INLINE void STCU_HWA_SwTriggerB(void)
{
    STCU->SELF_TEST_TRIG_B = STCU_SELF_TEST_TRIG_B_MASK;
}

/**
 * \brief Set self test ctrl register
 *
 * \param u32Reg   Register value.
 */
LOCAL_INLINE void STCU_HWA_SetSelfTestCTRL(uint32_t u32Reg)
{
	STCU->SELF_TEST_CTRL = u32Reg;
}

/**
 * \brief Enable interrupt
 */
LOCAL_INLINE void STCU_HWA_EnableInterrupt(void)
{
	STCU->IRQ |= STCU_IRQ_EN_MASK;
}

/**
 * \brief Disable interrupt
 */
LOCAL_INLINE void STCU_HWA_DisableInterrupt(void)
{
	STCU->IRQ &= ~STCU_IRQ_EN_MASK;
}

/**
 * \brief Get STCU interrupt flags
 *
 * \return Status, maybe more than one status, refer to "STCU_InterruptFlagType"
 */
LOCAL_INLINE uint32_t STCU_HWA_GetInterruptFlag(void)
{
    return ((STCU->IRQ) & (STCU_IRQ_SEQ_ERR_MASK | STCU_IRQ_SIZE_ERR_MASK));
}

/**
 * \brief Clear STCU interrupt flags
 */
LOCAL_INLINE void STCU_HWA_ClearInterruptFlag(void)
{
	STCU->IRQ &= ~(STCU_IRQ_SEQ_ERR_MASK | STCU_IRQ_SIZE_ERR_MASK);
}

/**
 * \brief Set STCU LBIST expected misr value
 */
LOCAL_INLINE void STCU_HWA_SetExpectedMisr(uint32_t u32Misr)
{
	STCU->LBIST_EXP_MISR = STCU_LBIST_EXP_MISR_MISR(u32Misr);
}

/**
 * \brief Get STCU LBIST expected misr value
 */
LOCAL_INLINE uint32_t STCU_HWA_GetExpectedMisr(void)
{
	return STCU->LBIST_EXP_MISR;
}

/**
 * \brief Get STCU LBIST actual misr value
 */
LOCAL_INLINE uint32_t STCU_HWA_GetActualMisr(void)
{
	return STCU->LBIST_ACT_MISR;
}

#endif  /*#ifndef _HWA_STCU_H_*/
