/**
 * @file fc7xxx_driver_stcu.h
 * @author Flagchip
 * @brief FC4xxx stcu driver type definition and API
 * @version 0.1.0
 * @date 2022-02-20
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */

/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Author        CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       12/08/2022    Flagchip038  N/A          First version for FC7300
   ******************************************************************************** */

#ifndef _DRIVER_STCU_H_
#define _DRIVER_STCU_H_

/** @brief STCU self test status flag */
typedef enum
{
    STCU_SELFTEST_NONE            = 0x00U,       /**<! No any status flag. >*/
    STCU_SELFTEST_DONE            = 0x01U,       /**<! Self-test Done Flag. >*/
    STCU_SELFTEST_ABORT           = 0x02U,       /**<! Self-test Abort Flag. >*/
    STCU_SELFTEST_LBIST_ERROR     = 0x10U,       /**<! LBIST Error Flag. >*/
    STCU_SELFTEST_MBIST_ERROR     = 0x20U,       /**<! MBIST Error Flag. >*/
    STCU_SELFTEST_TIMEOUT_ERROR   = 0x40U,       /**<! Self-test Timeout Error Flag. >*/
    STCU_SELFTEST_NVRLOAD_ERROR   = 0x100U,      /**<! NVR Load Error Flag. >*/
    STCU_SELFTEST_SELFCHECK_ERROR = 0x200u       /**<! STCU Self Check Error Flag. >*/
}STCU_SelfTestStatusType;

/** @brief STCU interrupt flag */
typedef enum
{
    STCU_INTERRUPT_FLAG_NONE            = 0x00U,   /**<! No any Interrupt flag. >*/
	STCU_INTERRUPT_FLAG_SIZE_ERR        = 0x01U,   /**<! STCU Register Access Size Error IRQ Flag. >*/
	STCU_INTERRUPT_FLAG_SEQ_ERR         = 0x02U,   /**<! Illegal Register Access Sequence IRQ Flag. >*/
}STCU_InterruptFlagType;

/** @brief The items select for MBIST */
typedef enum
{
    STCU_MBIST_SEL_NONE        = 0x00U,        /**<! No any MBist item selected. >*/
    STCU_MBIST_SEL_SRAM        = 0x01U,        /**<! SRAM Select for MBIST. >*/
    STCU_MBIST_SEL_ITCM_CPU0   = 0x02U,        /**<! ITCM_CPU0 SRAM Select for MBIST. >*/
    STCU_MBIST_SEL_DTCM0_CPU0  = 0x04U,        /**<! DTCM0_CPU0 SRAM Select for MBIST. >*/
    STCU_MBIST_SEL_DTCM1_CPU0  = 0x08U,        /**<! DTCM1_CPU0 SRAM Select for MBIST. >*/
    STCU_MBIST_SEL_CACHE_CPU0  = 0x10U,        /**<! CACHE_CPU0 SRAM Select for MBIST. >*/
	STCU_MBIST_SEL_SUBSYS      = 0x20U,        /**<! SUBSYS SRAM Select for MBIST. >*/
    STCU_MBIST_SEL_SRAM_HSM    = 0x40U,        /**<! HSM SRAM Select for MBIST. >*/
    STCU_MBIST_SEL_SRAM_DMACAN = 0x80U,        /**<! DMA_FLEXCAN SRAM Select for MBIST. >*/
    STCU_MBIST_SEL_ROM_HOST    = 0x100U,       /**<! System ROM Select for MBIST. >*/
    STCU_MBIST_SEL_ROM_HSM     = 0x200U        /**<! HSM ROM Select for MBIST. >*/
}STCU_MbistSelType;

/** @brief MBIST done status flag. */
typedef enum
{
    STCU_MBIST_DONE_NONE        = 0x00U,       /**<! No any MBIST done flag. >*/
    STCU_MBIST_DONE_SRAM        = 0x01U,       /**<! SRAM MBIST Done Dlag. >*/
    STCU_MBIST_DONE_ITCM_CPU0   = 0x02U,       /**<! ITCM_CPU0 SRAM MBIST Done Dlag. >*/
    STCU_MBIST_DONE_DTCM0_CPU0  = 0x04U,       /**<! DTCM0_CPU0 SRAM MBIST Done Dlag. >*/
    STCU_MBIST_DONE_DTCM1_CPU0  = 0x08U,       /**<! DTCM1_CPU0 SRAM MBIST Done Dlag. >*/
    STCU_MBIST_DONE_CACHE_CPU0  = 0x10U,       /**<! CACHE_CPU0 SRAM MBIST Done Flag. >*/
	STCU_MBIST_DONE_SUBSYS      = 0x20U,       /**<! SUBSYS SRAM MBIST Done. >*/
    STCU_MBIST_DONE_SRAM_HSM    = 0x40U,       /**<! HSM SRAM MBIST Done Flag. >*/
    STCU_MBIST_DONE_SRAM_DMACAN = 0x80U,       /**<! DMA_FLEXCAN SRAM MBIST Done Flag. >*/
    STCU_MBIST_DONE_ROM_HOST    = 0x100U,      /**<! System ROM MBIST Done Dlag. >*/
    STCU_MBIST_DONE_ROM_HSM     = 0x200U       /**<! HSM ROM MBIST Done Dlag. >*/
}STCU_MbistDoneType;

/** @brief MBIST fail status flag. */
typedef enum
{
    STCU_MBIST_FAIL_NONE        = 0x00U,        /**<! No any MBIST fail flag. >*/
    STCU_MBIST_FAIL_SRAM        = 0x01U,        /**<! SRAM MBIST Fail Flag. >*/
    STCU_MBIST_FAIL_ITCM_CPU0   = 0x02U,        /**<! ITCM_CPU0 SRAM MBIST Fail Flag. >*/
    STCU_MBIST_FAIL_DTCM0_CPU0  = 0x04U,        /**<! DTCM0_CPU0 SRAM MBIST Fail Flag. >*/
    STCU_MBIST_FAIL_DTCM1_CPU0  = 0x08U,        /**<! DTCM1_CPU0 SRAM MBIST Fail Flag. >*/
    STCU_MBIST_FAIL_CACHE_CPU0  = 0x10U,        /**<! CACHE_CPU0 SRAM MBIST Fail Flag. >*/
	STCU_MBIST_FAIL_SUBSYS      = 0x20U,        /**<! SUBSYS SRAM MBIST Fail Flag. >*/
	STCU_MBIST_FAIL_SRAM_HSM    = 0x40U,        /**<! HSM SRAM MBIST Fail Flag. >*/
    STCU_MBIST_FAIL_SRAM_DMACAN = 0x80U,        /**<! DMA_FLEXCAN SRAM MBIST fail flag. >*/
    STCU_MBIST_FAIL_ROM_HOST    = 0x100U,    /**<! System ROM MBIST Fail Flag. >*/
    STCU_MBIST_FAIL_ROM_HSM     = 0x200U     /**<! HSM ROM MBIST Fail Flag. >*/
}STCU_MbistFailedType;

/** @brief Hardware SRAM initialization mode. */
typedef enum
{
    STCU_INIT_RAM_MODE_POR_OR_WAKEUP4STANDBY0 = 0U,   /**<! After POR or wakeup from STANDBY0, Hardware SRAM initialization. >*/
    STCU_INIT_RAM_MODE_AFTER_WAKEUP4STANDBY1,         /**<! After wakeup from STANDBY1, Hardware SRAM initialization. >*/
    STCU_INIT_RAM_MODE_AFTER_WAKEUP4STANDBY2,         /**<! After wakeup from STANDBY2, Hardware SRAM initialization. >*/
    STCU_INIT_RAM_MODE_AFTER_WAKEUP4STANDBY3          /**<! After wakeup from STANDBY3, Hardware SRAM initialization. >*/
}STCU_InitRamModeType;

/** @brief The items select for Hardware SRAM Initialization. */
typedef enum
{
    STCU_INIT_RAM_TYPE_NONE        = 0x00U,           /**<! No any SRAM need to be initialized. >*/
    STCU_INIT_RAM_TYPE_SRAM        = 0x01U,           /**<! SRAM Select for Hardware SRAM Initialization. >*/
    STCU_INIT_RAM_TYPE_ITCM_CPU0   = 0x02U,           /**<! ITCM_CPU0 SRAM Select for Hardware SRAM Initialization. >*/
    STCU_INIT_RAM_TYPE_DTCM0_CPU0  = 0x04U,           /**<! DTCM0_CPU0 SRAM Select for Hardware SRAM Initialization. >*/
    STCU_INIT_RAM_TYPE_DTCM1_CPU0  = 0x08U,           /**<! DTCM1_CPU0 SRAM Select for Hardware SRAM Initialization. >*/
}STCU_InitRamType;

/** @brief Init Ram done status flag. */
typedef enum
{
    STCU_INIT_RAM_DONE_TYPE_NONE        = 0x00U,       /**<! No any Init Ram done flag. >*/
    STCU_INIT_RAM_DONE_TYPE_SRAM        = 0x01U,       /**<! SRAM Initialization Done Flag. >*/
    STCU_INIT_RAM_DONE_TYPE_ITCM_CPU0   = 0x02U,       /**<! ITCM_CPU0 SRAM Initialization Done Flag. >*/
    STCU_INIT_RAM_DONE_TYPE_DTCM0_CPU0  = 0x04U,       /**<! DTCM0_CPU0 SRAM Initialization Done Flag. >*/
    STCU_INIT_RAM_DONE_TYPE_DTCM1_CPU0  = 0x08U,       /**<! DTCM1_CPU0 SRAM Initialization Done Flag. >*/
}STCU_InitRamDoneType;

/** @brief Init Ram status flag. */
typedef enum
{
    STCU_HARDWARE_INIT_RAM_STATUS_NONE  = 0U,        /**<! No any SRAN Initialization flag. >*/
    STCU_HARDWARE_INIT_RAM_STATUS_DONE  = 1U,        /**<! Hardware SRAM Initialization Done Flag. >*/
    STCU_HARDWARE_INIT_RAM_STATUS_BUSY  = 2U,        /**<! Hardware SRAM Initialization Busy Flag. >*/
    STCU_HARDWARE_INIT_RAM_STATUS_ABORT = 4U         /**<! Hardware SRAM Initialization Abort Flag. >*/
}STCU_HardwareInitRamStatusType;

/** @brief LBIST status flag. */
typedef enum
{
    STCU_LBIST_STATUS_NONE   = 0U,       /**<! No any LBIST flag. >*/
    STCU_LBIST_STATUS_DONE   = 1U,       /**<! LBIST Done Flag. >*/
    STCU_LBIST_STATUS_FAILED = 2U        /**<! LBIST Fail Flag. >*/
}STCU_LbistStatusType;

/** @brief LBIST Clock Divider. */
typedef enum
{
    STCU_LBIST_CLK_DIVIDER_BY_2 = 1U,     /**<! LBIST clock is Divided by 2. >*/
    STCU_LBIST_CLK_DIVIDER_BY_3 = 2U,     /**<! LBIST clock is Divided by 3. >*/
    STCU_LBIST_CLK_DIVIDER_BY_4 = 3U,     /**<! LBIST clock is Divided by 4. >*/
}STCU_LbistClkDivType;

/** @brief clock source of self-test. */
typedef enum
{
    STCU_CLK_SOURCE_FIRC = 0U,     /**<! FIRC clock source. >*/
	STCU_CLK_SOURCE_PLL  = 1U      /**<! PLL clock source. >*/
}STCU_ClkSourceType;

/** @brief Self-test Port Pull Selection. */
typedef enum
{
    STCU_PORT_PULL_DISABLE = 0U,   /**<! Disable self test port pull function. >*/
	STCU_PORT_PULL_DOWN,           /**<! self test port pull down. >*/
	STCU_PORT_PULL_UP              /**<! self test port pull up. >*/
}STCU_PortPullModeType;

/** @brief Stcu call back function type, the u32status should refer to "STCU_InterruptFlagType" */
typedef void (*Stcu_IRQCallback)(uint32_t u32Status);

typedef struct
{
    bool                  bLbistEn;            /**<! LBIST Enable >*/
	bool                  bMbistLPC;           /**<! MBIST Low Power Control Enable >*/
    bool                  bMbistEn;            /**<! MBIST Enable >*/
    bool                  bMbistFullTest;      /**<! MBIST Full test Enable >*/
    bool                  bMbistSramInit;      /**<! Enable SRAM initialization at the end of power on self-test. >*/
    bool                  bInterruptEn;        /**<! STCU Interrupt Enable >*/
    STCU_PortPullModeType ePortPullMode;       /**<! Self-test Port Pull Selection >*/
    STCU_ClkSourceType    eClkSource;          /**<! Select the clock source of self-test >*/
    STCU_LbistClkDivType  eLbistClkDivider;    /**<! LBIST Clock Divider Control. Note:A slower LBIST clock will cause less power consumption but a longer test time. >*/
    uint16_t              u16MaxTime;          /**<! The maximum time allowed for self-test execution.(unit : ms) >*/
    uint32_t              u32MbistSel;         /**<! Refer to "STCU_MbistSelType", use OR to select the MBIST range. */
    Stcu_IRQCallback      pIrqCallback;        /**<! Callback function for STCU IRQ >*/
}STCU_ConfigType;


typedef struct
{
    STCU_InitRamModeType     eInitMode;        /**< RAM Initial Mode */
    uint8_t                  bLockAfterEn;     /**< Lock STCU after RAM Initial */
    uint32_t                 u32InitRamType;   /**< RAM Type, DTCM, ITCM, SRAM, refer to "STCU_InitRamType" and use OR to combine them */
}STCU_InitRamConfigType;


/**
 * \brief Init the STCU module
 *
 * \param pConfig the configuration structure
 */
void STCU_Init(STCU_ConfigType *pConfig);

/**
 * \brief Trigger to start Software self test
 *
 */
void STCU_StartSelfTest(void);

/**
 * \brief Check Software Trigger Self-test result
 *
 * \return refer to "STCU_SelfTestStatusType" enum.
 */
uint32_t STCU_CheckTriggerResult(void);

/**
 * \brief Initial RAM with hardware
 *
 * \param pConfig the configuration structure
 */
void STCU_StartRamInit(STCU_InitRamConfigType *pInitCfg);

/**
 * \brief Get status of RAM initialize action
 *
 * \return the status of ram initialize action, refer to "STCU_HardwareInitRamStatusType"
 */
uint32_t STCU_GetRamInitStatus(void);

/**
 * \brief Get if the LBIST test result is Fail
 *
 * \return true means LBIST fail. false means LBIST pass.
 */
bool STCU_GetLbistFailResult(void);
/**
 * \brief Get each MBIST Fail result
 *
 * \return refer to "STCU_MbistFailedType" enum.
 */
uint32_t STCU_GetMbistFailResult(void);

/**
 * \brief Get each done status of SRAM initialize
 *
 * \return the done status of SRAM initialize action, refer to "STCU_InitRamDoneType"
 */
uint32_t STCU_GetRamInitDoneStatus(void);

/**
 * \brief Set the LBIST Pattern value and expected misr value.
 *        The two value should be load from NVR, but also can reconfigure by this API.
 *        The expected misr value is calculated from pattern, so please make sure this two value is right, or the LBST would fail.
 *
 * \param u16Pattern the LBIST Pattern value
 * \param u16Pattern the LBIST expected misr value
 */
void STCU_LBIST_Set_Pattern_Misr(uint16_t u16Pattern, uint32_t u32ExpectedMisr);

/**
 * \brief Get LBIST actual MISR value, the value should be read and use DFT tool to decode it, if LBIST test resault is fail.
 *
 * \return the LBIST actual MISR value
 */
uint32_t STCU_GetLbistAcutalMisr(void);

/**
 * @brief STCU 0 interrupt handler
 *
 * @note This function should be called as/in STCU 0 interrupt handler
 */
void STCU0_IRQHandler(void);
#endif /* end of _DRIVER_STCU_H_ */
