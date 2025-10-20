#include "Clock.h"

/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */

/* ################################################################################## */
/* ################################ Local Functions ################################# */

/**
 * \brief Local SCG initial
 *
 */
#define USED_PCC_NUMBER  3U //SPI1+CAN0+UART2

PCC_CtrlType BSP_PCC_Config_arr[USED_PCC_NUMBER] =
{
    {PCC_CLK_FCSPI1, true, PCC_CLKGATE_SRC_FOSCDIV, PCC_CLK_DIV_BY1},
	{PCC_CLK_FLEXCAN0, true, PCC_CLKGATE_SRC_FOSCDIV, PCC_CLK_DIV_BY1},
	{PCC_CLK_FCUART2, true, PCC_CLKGATE_SRC_FOSCDIV, PCC_CLK_DIV_BY1}
};

static void Bsp_SCG_Init(void)
{
    /* Enable FOSC, frequency is 24M, DIVH=DIV1(24M), DIVM=DIV1(24M), DIVL=DIV2(12M)*/
    SCG_FoscType tFoscStruct = {
        .bLock   = false,
        .bCm     = false,
        .bCmre   = false,
        .bSten   = false,
        .bBypass = false,
        .eDivH   = SCG_ASYNCCLOCKDIV_BY1,
        .eDivM   = SCG_ASYNCCLOCKDIV_BY1,
        .eDivL   = SCG_ASYNCCLOCKDIV_BY2,
    };
    SCG_EnableFOSC(&tFoscStruct);

    /* Enable PLL0, frequency is 240M, DIVH=DIV2(120M), DIVM=DIV2(120M), DIVL=DIV4(60M), src=FOSC*/
    /* The value of multiplier factor(FOSC/u8Prediv) between 2 ~ 4 is better*/
    SCG_PllType tPll0Struct = {.bLock    = false,
                               .bCm      = false,
                               .bCmre    = false,
                               .bSten    = false,
                               .eDivH    = SCG_ASYNCCLOCKDIV_BY2,
                               .eDivM    = SCG_ASYNCCLOCKDIV_BY2,
                               .eDivL    = SCG_ASYNCCLOCKDIV_BY4,
                               .u8Prediv = 11U,
                               .ePstDiv  = SCG_PLLPSTDIV_BY2,
                               .u16Mult  = 239U,
                               .eSrc     = SCG_PLLSOURCE_FOSC};
    SCG_EnablePLL(SCG_PLL0, &tPll0Struct);

    /* Enable PLL1, frequency is 300M, DIVH=DIV2(150M), DIVM=DIV2(150M), DIVL=DIV4(75M), src=FOSC*/
    /* The value of multiplier factor(FOSC/u8Prediv) between 2 ~ 4 is better*/
    SCG_PllType tPll1Struct = {.bLock    = false,
                               .bCm      = false,
                               .bCmre    = false,
                               .bSten    = false,
                               .eDivH    = SCG_ASYNCCLOCKDIV_BY2,
                               .eDivM    = SCG_ASYNCCLOCKDIV_BY2,
                               .eDivL    = SCG_ASYNCCLOCKDIV_BY4,
                               .u8Prediv = 11U,
                               .ePstDiv  = SCG_PLLPSTDIV_BY2,
                               .u16Mult  = 299U,
                               .eSrc     = SCG_PLLSOURCE_FOSC};
    SCG_EnablePLL(SCG_PLL1, &tPll1Struct);

    /* Enable SIRC DIV, DIVH=DIV1(12M), DIVM=DIV1(12M), DIVL=DIV2(6M) */
    SCG_SircType tSircStruct = {.bLock     = false,
                                .bCm       = false,
                                .bTrEn     = false,
                                .bLpen     = false,
                                .bSten     = false,
                                .eDivH     = SCG_ASYNCCLOCKDIV_BY1,
                                .eDivM     = SCG_ASYNCCLOCKDIV_BY1,
                                .eDivL     = SCG_ASYNCCLOCKDIV_BY2,
                                .u8TrimSrc = 0U};
    SCG_SetSIRC(&tSircStruct);

    /* Set core clock source from PLL0, DIV_CORE=DIV1(240M), DIV_BUS=DIV2(120M), DIV_SLOW=DIV4(60M)*/
    SCG_ClockCtrlType tClockStruct = {.bSysClkMonitor = false,
                                      .eSrc           = SCG_CLOCK_SRC_PLL0,
                                      .eDivSlow       = SCG_CLOCK_DIV_BY2,
                                      .eDivBus        = SCG_CLOCK_DIV_BY2,
                                      .eDivCore       = SCG_CLOCK_DIV_BY1};
    SCG_SetClkCtrl(&tClockStruct);
}

/**
 * \brief Local PCC Initial
 *
 */
static void Bsp_PCC_Init(void)
{
    for(uint8_t i=0; i<USED_PCC_NUMBER; i++)
    {
       PCC_SetPcc(&BSP_PCC_Config_arr[i]);
    }
}

/* ################################################################################## */
/* ################################# Global Functions ############################### */

/**
 * \brief General Clock Initial
 *
 */
void Bsp_CLOCK_Init(void)
{
    SCG_Deinit();
    Bsp_SCG_Init();
    Bsp_PCC_Init();
}
