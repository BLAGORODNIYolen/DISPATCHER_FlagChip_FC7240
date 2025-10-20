/**
 * @file fc7xxx_driver_scg.h
 * @author Flagchip085
 * @brief FC7xxx SCG driver type definition and API
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
   *   0.1.0       2024-01-12    Flagchip085   N/A          First version for FC7240
   ******************************************************************************** */
#ifndef _DRIVER_FC7XXX_DRIVER_SCG_H_
#define _DRIVER_FC7XXX_DRIVER_SCG_H_
#include "HWA_scg.h"
#include "HWA_csc.h"
/**
 * @addtogroup fc7xxx_driver_scg
 * @{
 */

/** @brief clock list for internal clock tree */
typedef enum
{
    /* Main clocks */
    SCG_CORE_CLK                       = 0U,       /*!< Core clock                 */
    SCG_BUS_CLK                        = 1U,       /*!< Bus clock                  */
    SCG_SLOW_CLK                       = 2U,       /*!< Slow clock                 */

    /* Other internal clocks used by peripherals. */
    SCG_FOSC_CLK                       = 3U,       /*!< FOSC clock                 */
    SCG_FIRC_CLK                       = 4U,       /*!< FIRC clock                 */
    SCG_PLL0_CLK                       = 5U,       /*!< PLL0 clock                 */
    SCG_PLL1_CLK                       = 6U,       /*!< PLL1 clock                 */
    SCG_SIRC_CLK                       = 7U,       /*!< SIRC clock                 */
    SCG_SIRC32K_CLK                    = 8U,       /*!< SIRC32K clock              */
    SCG_SOSC_CLK                       = 9U,       /*!< SOSC clock                 */
    SCG_SCG_CLKOUT_CLK                 = 10U,      /*!< SCG CLK_OUT clock          */
    SCG_SIRCDIVH_CLK                   = 11U,      /*!< SIRCDIVH functional clock  */
    SCG_SIRCDIVM_CLK                   = 12U,      /*!< SIRCDIVM functional clock  */
    SCG_SIRCDIVL_CLK                   = 13U,      /*!< SIRCDIVL functional clock  */
    SCG_FIRCDIVH_CLK                   = 14U,      /*!< FIRCDIVH functional clock  */
    SCG_FIRCDIVM_CLK                   = 15U,      /*!< FIRCDIVM functional clock  */
    SCG_FIRCDIVL_CLK                   = 16U,      /*!< FIRCDIVL functional clock  */
    SCG_FOSCDIVH_CLK                   = 17U,      /*!< FOSCDIVH functional clock  */
    SCG_FOSCDIVM_CLK                   = 18U,      /*!< FOSCDIVM functional clock  */
    SCG_FOSCDIVL_CLK                   = 19U,      /*!< FOSCDIVL functional clock  */
    SCG_PLL0DIVH_CLK                   = 20U,      /*!< PLL0DIVH functional clock  */
    SCG_PLL0DIVM_CLK                   = 21U,      /*!< PLL0DIVM functional clock  */
    SCG_PLL0DIVL_CLK                   = 22U,      /*!< PLL0DIVL functional clock  */
    SCG_PLL1DIVH_CLK                   = 23U,      /*!< PLL1DIVH functional clock  */
    SCG_PLL1DIVM_CLK                   = 24U,      /*!< PLL1DIVM functional clock  */
    SCG_PLL1DIVL_CLK                   = 25U,      /*!< PLL1DIVL functional clock  */
	SCG_NVMINIT_CLK                    = 26U,      /*!< NVM initial clock source   */
	SCG_CMU4REF_CLK                    = 27U,      /*!< CMU4 reference clock       */
    SCG_END_OF_CLOCKS                  = 28U       /*!< End of SCG clocks          */
} SCG_ClkSrcType;

/**
 * @brief PLL clock type
 */
typedef enum
{
    SCG_PLL0 = 0U,    /*!< PLL0 clock                 */
    SCG_PLL1 = 1U     /*!< PLL1 clock                 */
} SCG_PllClkType;

/**
 * @brief indicate the clock function status
 *
 */
typedef enum
{
    SCG_STATUS_SUCCESS = 0U,          /*!< function called success */
    SCG_STATUS_SEQUENCE_ERROR = 1U,   /*!< function called report sequence error */
    SCG_STATUS_TIMEOUT = 2U,          /*!< function called report timeout error */
    SCG_STATUS_IRC_ERROR = 3U,        /*!< function called report internal clock error */
    SCG_STATUS_PARAM_ERROR = 4U       /*!< function called report internal clock error */
} SCG_StatusType;

/**
 * @brief indicate the CRC check result
 *
 */
typedef enum
{
    SCG_CRC_CHECK_SUCCESS = 0U,       /*!< CRC check success *//**< SCG_CRC_CHECK_SUCCESS */
	SCG_CRC_GEN_TIMEOUT = 1U,       	/*!< CRC Generate Timeout *//**< SCG_CRC_GEN_TIMEOUT */
    SCG_CRC_CHECK_FAILED = 2U         /*!< CRC check failed */ /**< SCG_CRC_CHECK_FAILED */
} SCG_CrcCheckResType;

/**
 * @brief SCG xxxIRC TRIMSRC type.
*/
typedef enum
{
    SCG_IRC_TRIMSRC_RESERVE0   = 0U,   /*!< Clock Trim source reserve0  */
    SCG_IRC_TRIMSRC_RESERVE1   = 1U,   /*!< Clock Trim source reserve1  */
    SCG_IRC_TRIMSRC_FOSC       = 2U,   /*!< Clock Trim source FOSC      */
    SCG_IRC_TRIMSRC_SOSC       = 3U,   /*!< Clock Trim source SOSC      */
} SCG_IrcTrimSrcType;

/**
 * @brief SCG_CCR [SCS]  to Select system clock source
 *
 */
typedef enum
{
    SCG_CLOCK_SRC_FOSC     = 1U,       /*!< System OSC. 	*/
	SCG_CLOCK_SRC_SIRC     = 2U,       /*!< Slow IRC 12MHz. */
    SCG_CLOCK_SRC_FIRC     = 3U,       /*!< Fast IRC.   	*/
    SCG_CLOCK_SRC_PLL0     = 6U,       /*!< System PLL. 	*/
    SCG_CLOCK_SRC_NONE     = 255U      /*!< MAX value.  	*/
} SCG_ClockSrcType;

/**
 * @brief SCG_CCR [DIVCORE ]/ SCG_CCR [DIVBUS ]/ SCG_CCR [DIVSLOW ]  to Select system clock source.
 *
 */
typedef enum
{
    SCG_CLOCK_DIV_BY1   = 0U,     /*!< Divided by 1.    */
    SCG_CLOCK_DIV_BY2   = 1U,     /*!< Divided by 2.    */
    SCG_CLOCK_DIV_BY3   = 2U,     /*!< Divided by 3.    */
    SCG_CLOCK_DIV_BY4   = 3U      /*!< Divided by 4.    */
} SCG_ClockDivType;

/**
 * @brief SCG_ CLKOUTCFG [CLKOUTSEL]  to Select system clock source.
 */
typedef enum
{
    SCG_CLOCKOUT_SRC_OFF      = 0U,   /*!< SCG OFF.   */
    SCG_CLOCKOUT_SRC_FOSC     = 1U,   /*!< Fast OSC.   */
    SCG_CLOCKOUT_SRC_SIRC     = 2U,   /*!< Slow IRC.   */
    SCG_CLOCKOUT_SRC_FIRC     = 3U,   /*!< Fast IRC.   */
    SCG_CLOCKOUT_SRC_SOSC     = 4U,   /*!< Slow OSC.   */
    SCG_CLOCKOUT_SRC_PLL1     = 5U,   /*!< System PLL1.   */
    SCG_CLOCKOUT_SRC_PLL0     = 6U,   /*!< System PLL0. */
    SCG_CLOCKOUT_SRC_SIRC32K  = 7U,   /*!< SIRC32K_CLK.*/
} SCG_ClockoutSrcType;

/**
 * @brief NVM clock source enumeration
 */
typedef enum
{
    SCG_NVMCLK_SRC_SIRC = 30u,   /*!< NVM source choose SIRC.   */
    SCG_NVMCLK_SRC_FIRC = 31u   /*!< NVM source choose FIRC.   */
} SCG_NvmClkSrcType;

/**
 * @brief CMU4 clock source enumeration
 */
typedef enum
{
    SCG_CMU4CLK_SRC_SIRC = 28u,   /*!< NVM source choose SIRC.   */
    SCG_CMU4CLK_SRC_FOSC = 29u   /*!< NVM source choose FORC.   */
} SCG_Cmu4ClkSrcType;

/**
 * @brief SCG registers CRC trigger mode
 */
typedef enum
{
	SCG_CRC_SW_MODE       = 0U,   /*!< SCG registers CRC software mode. */
	SCG_CRC_TRIGGER_MODE  = 1U    /*!< SCG registers CRC trigger mode. */
} SCG_CrcModeType;

/** @brief [DIVL]/[DIVM]/[DIVH] bit field definition for SCG_SIRC/ SCG_FIRC/ SCG_FOSC/ SCG_PLL0 registers */
typedef enum
{
    SCG_ASYNC_CLOCK_DISABLE  = 0U,        /*!< Clock output is disabled.  */
    SCG_ASYNCCLOCKDIV_BY1    = 1U,        /*!< Divided by 1.              */
    SCG_ASYNCCLOCKDIV_BY2    = 2U,        /*!< Divided by 2.              */
    SCG_ASYNCCLOCKDIV_BY4    = 3U,        /*!< Divided by 4.              */
    SCG_ASYNCCLOCKDIV_BY8    = 4U,        /*!< Divided by 8.              */
    SCG_ASYNCCLOCKDIV_BY16   = 5U,        /*!< Divided by 16.             */
    SCG_ASYNCCLOCKDIV_BY32   = 6U,        /*!< Divided by 32.             */
    SCG_ASYNCCLOCKDIV_BY64   = 7U         /*!< Divided by 64.             */
} SCG_AsyncClockDivType;

/** @brief SCG_ PLLCFG[PREDIV]  for PLL clock calculation. The pre-div value range is 0 ~ 31 */
typedef uint8_t SCG_PllPredivType;

/** @brief SCG_ PLLCFG[PSTDIV]  for PLL clock calculation */
typedef enum
{
    SCG_PLLPSTDIV_BY2 = 1U,
    SCG_PLLPSTDIV_BY4 = 2U,
    SCG_PLLPSTDIV_BY8 = 3U
} SCG_PllPstdivType;

/** @brief SCG_ PLLCFG[SOURCE] to Select PLL clock source */
typedef enum
{
    SCG_PLLSOURCE_FOSC = 0U,
    SCG_PLLSOURCE_FIRC = 1U
} SCG_PllSourceType;

/** @brief SCG_ PLLCFG [MULT]  for PLL clock calculation. The mult value range is 96 ~ 512 */
typedef uint16_t SCG_PllMultiplyType;

/** @brief FOSC initial definition, include register SCG_FOSCCSR/SCG_FOSCDIV/SCG_FOSCCFG. */
typedef struct
{
    bool bLock;                       /*!< SCG_FOSCCSR[LK] bit, Write to set the register can be written or not */
    bool bCm;                         /*!< SCG_FOSCCSR[CM] bit, Clock Monitor is enable */
    bool bCmre;                       /*!< SCG_FOSCCSR[CMRE] bit, Clock Monitor Reset Enable
                                           0 Generates interrupt, 1 Generates rese         */
    bool bSten;                       /*!< SCG_FOSCCSR[STEN] bit, Clock Stop in Stop modes */
    bool bBypass;                     /*!< SCG_FOSCCFG[BYPASS] bit, Configures FOSC for bypassing the internal oscillator.*/
    SCG_AsyncClockDivType eDivH;      /*!< SCG_FOSCDIV[DIVH] bit field definition, 0 means disable. */
    SCG_AsyncClockDivType eDivM;      /*!< SCG_FOSCDIV[DIVM] bit field definition, 0 means disable. */
    SCG_AsyncClockDivType eDivL;      /*!< SCG_FOSCDIV[DIVL] bit field definition, 0 means disable. */
} SCG_FoscType;

/** @brief SIRC initial definition, include register SCG_ SIRCCSR/ SCG_ SIRCDIV/ SCG_ SIRCTCCFG. */
typedef struct
{
    bool bLock;                        /*!< SCG_SIRCCSR[LK] bit, Write to set the register can be written or not  */
    bool bCm;                          /*!< SCG_SIRCCSR[CM] bit, SIRC Clock Monitor Enable */
    bool bTrEn;                        /*!< SCG_SIRCCSR[TREN] bit, IRC software trim enable (auto trim) */
    bool bLpen;                        /*!< SCG_SIRCCSR[LPEN] bit, Clock Stop Enable */
    bool bSten;                        /*!< SCG_SIRCCSR[STEN] bit, Clock Standby Enable */
    SCG_AsyncClockDivType eDivH;       /*!< SCG_SIRCDIV[DIVH] bit field definition.*/
    SCG_AsyncClockDivType eDivM;       /*!< SCG_SIRCDIV[DIVM] bit field definition.*/
    SCG_AsyncClockDivType eDivL;       /*!< SCG_SIRCDIV[DIVL] bit field definition.*/
    uint8_t u8TrimSrc;                 /*!< SCG_SIRCTCFG[TRIMSRC] IRC clock auto trim reference clock source select.*/
} SCG_SircType;

typedef struct
{
    bool bLock;                        /*!< SIRC32KCSR[LK] bit, Write to set the register can be written or not  */
} SCG_Sirc32kType;

/** @brief FIRC initial definition, include register SCG_ FIRCCSR/ SCG_ FIRCDIV/ SCG_ FIRCFG. */
typedef struct
{
    bool bLock;                        /*!< SCG_FIRCCSR[LK] bit, Write to set the register can be written or not  */
    bool bCm;                          /*!< SCG_FIRCCSR[CM] bit, FIRC Clock Monitor Enable */
    bool bTrEn;                        /*!< SCG_FIRCCSR[TREN] bit, IRC software trim enable (auto trim) */
    bool bSten;                        /*!< SCG_FIRCCSR[STEN] bit, Clock Standby Enable */
    SCG_AsyncClockDivType eDivH;       /*!< SCG_FIRCDIV[DIVH] bit field definition.*/
    SCG_AsyncClockDivType eDivM;       /*!< SCG_FIRCDIV[DIVM] bit field definition.*/
    SCG_AsyncClockDivType eDivL;       /*!< SCG_FIRCDIV[DIVL] bit field definition.*/
    uint8_t u8TrimSrc;                 /*!< SCG_FIRCTCFG[TRIMSRC] IRC clock auto trim reference clock source select.*/
} SCG_FircType;

/** @brief SOSC definition, include register SCG_SOSCCFG. */
typedef struct
{
    bool bLock;                        /*!< SCG_SOSCCSR[LK] bit, Write to set the register can be written or not.*/
    bool bBypass;                      /*!< SCG_SOSCCSR[BYPASS] bit, Configures SOSC for bypassing the internal oscillator.*/
    bool bCm;                          /*!< SCG_SOSCCSR[CM] bit,Clock Monitor enable.*/
    bool bCmre;                        /*!< SCG_SOSCCSR[CMRE] bit, 1:Clock Monitor Reset, 0: interrupt*/
} SCG_SoscType;

/** @brief PLL definition, include register SCG_PLLCSR/ SCG_PLLDIV/SCG_PLL0CFG. */
typedef struct
{
    bool bLock;                        /*!< SCG_PLLCSR[LK] bit, Write to set the register can be written or not.*/
    bool bCm;                          /*!< SCG_PLLCSR[CM] bit,Clock Monitor enable.*/
    bool bCmre;                        /*!< SCG_PLLCSR[CMRE] bit, 1:Clock Monitor Reset, 0: interrupt*/
    bool bSten;                        /*!< SCG_PLLCSR[STEN] bit, Clock Standby Enable */
    SCG_AsyncClockDivType eDivH;       /*!< SCG_PLLDIV[DIVH] bit field definition.*/
    SCG_AsyncClockDivType eDivM;       /*!< SCG_PLLDIV[DIVM] bit field definition.*/
    SCG_AsyncClockDivType eDivL;       /*!< SCG_PLLDIV[DIVL] bit field definition.*/
    SCG_PllPredivType u8Prediv;        /*!< SCG_PLLCFG[PREDIV] bit field definition, the range is 0~31. [Pre-divider = u8Prediv + 1] */
    SCG_PllPstdivType ePstDiv;         /*!< SCG_PLLCFG[PSTDIV] bit field definition. [Post Divider = (ePstDiv == 0 ? 2 : 2^ePstDiv)] */
    SCG_PllMultiplyType u16Mult;       /*!< SCG_PLLCFG[MULT] bit field definition, this value need to be greater than 95.
    										[Multiplier = u16Mult + 1] */
    SCG_PllSourceType eSrc;           /*!< SCG_PLLCFG[SOURCE] bit field definition.*/
} SCG_PllType;

/** @brief Current system clock definition, include register SCG_CCR. */
typedef struct
{
    bool bSysClkMonitor;               /*!< SCG_CCR[SYSCLK_CME], System Clock monitor bit.*/
    SCG_ClockSrcType eSrc;             /*!< SCG_CCR[SCS], System Clock Source.*/
    SCG_ClockDivType eDivSlow;         /*!< SCG_CCR[DIVSLOW], Slow Clock Divide Ratio.*/
    SCG_ClockDivType eDivBus;          /*!< SCG_CCR[DIVBUS], Bus Clock Divide Ratio.*/
    SCG_ClockDivType eDivCore;         /*!< SCG_CCR[DIVCORE], Core Clock Divide Ratio.*/
} SCG_ClockCtrlType;

/**
 * @brief Enable SOSC
 *
 * @param pSoscConfig SOSC configuration
 * @return SCG_StatusType Function status
 */
SCG_StatusType SCG_EnableSOSC(const SCG_SoscType *const pSoscConfig);

/**
 * @brief Disable SOSC
 *
 * @return SCG_StatusType Funtion status
 */
SCG_StatusType SCG_DisableSOSC(void);

/**
 * @brief Enable FOSC clock with input configuration
 *
 * @param pFoscConfig FOSC configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnableFOSC(const SCG_FoscType *const pFoscConfig);

/**
 * @brief Disable FOSC
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisableFOSC(void);

/**
 * @brief Set SIRC configuration and configure SIRC DIV
 *
 * @param pSircConfig SIRC configuation
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_SetSIRC(const SCG_SircType *const pSircConfig);

/**
 * @brief Disable SIRC DIV and clear DIV configuration
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_ClearSIRC(void);

/**
 * @brief Enable SIRC32K
 *
 * @param pSirc32kConfig SIRC32K configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnableSIRC32K(const SCG_Sirc32kType *const pSirc32kConfig);

/**
 * @brief Disable SIRC32K
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisableSIRC32K(void);

/**
 * @brief Enable FIRC
 *
 * @param pFircConfig FIRC configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnableFIRC(const SCG_FircType *const pFircConfig);

/**
 * @brief Disable FIRC
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisableFIRC(void);

/**
 * @brief Enable PLL
 *
 * @param ePll PLL instance
 * @param pPllConfig PLL configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnablePLL(const SCG_PllClkType ePll, const SCG_PllType *const pPllConfig);

/**
 * @brief Disable PLL
 *
 * @param ePll PLL instance
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisablePLL(const SCG_PllClkType ePll);

/**
 * @brief Set system run time clock and related CORE/BUS/SLOW clock.
 *
 * @param pSysClkConfig pointer to the clockCtrlType structure data instance,which defined for system clock selection.
 * @return SCG_StatusType function status
 *		   SCG_STATUS_SUCCESS : clock source and dividers are valid,and switch system clock successfully
 *         SCG_STATUS_SEQUENCE_ERROR: new clock source is not enabled
 *         SCG_STATUS_PARAM_ERROR: the core bus slow divider are invalid
 *         SCG_STATUS_TIMEOUT: switch system clock procedure time out
 */
SCG_StatusType SCG_SetClkCtrl(const SCG_ClockCtrlType *const pSysClkConfig);

/**
 * @brief Get clock frequency
 *
 * @param eScgClockName Clock source type
 * @return uint32_t frequency value
 */
uint32_t SCG_GetScgClockFreq(const SCG_ClkSrcType eScgClockName);

/**
 * @brief Select clock out source
 *
 * @param eClkoutSel clock out source
 */
void SCG_SetClkOut(const SCG_ClockoutSrcType eClkoutSel);

/**
 * @brief Select NVM clock source
 *
 * @param eNvmClkSrc NVM clock source
 * @return uint32_t function status
 */
SCG_StatusType SCG_SetNvmClk(const SCG_NvmClkSrcType eNvmClkSrc);

/**
 * @brief Select CMU4 clock source
 *
 * @param eCmu4ClkSrc CMU4 clock source
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_SetCmu4Clk(const SCG_Cmu4ClkSrcType eCmu4ClkSrc);

/**
 * @brief Generate the origion SCG register CRC result, and configure the SCG register CRC option.
 *
 * @param eMode The SCG register CRC trigger mode
 * @return CRC configure status
 *  SCG_STATUS_SUCCESS : CRC configure successfully
 *  SCG_STATUS_TIMEOUT : CRC configure time out
 */
SCG_StatusType SCG_RegCrcConfig(SCG_CrcModeType eMode);

/**
 * @brief Trigger the SCG register CRC generation by software
 *
 */
void SCG_RegCrcGenerate(void);

/**
 * @brief Trigger the SCG register CRC generation by software,and wait the CRC check result
 *
 * @return CRC check result
 */
SCG_CrcCheckResType SCG_RegCrcGenerateWaitResult(void);

/**
 * @brief Clock source De-init
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_Deinit(void);



/** @}*/ /* fc7xxx_driver_scg */
#endif
