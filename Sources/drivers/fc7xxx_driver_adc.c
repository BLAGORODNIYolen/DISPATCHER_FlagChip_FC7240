/**
 * @file fc7xxx_driver_adc.c
 * @author Flagchip0126
 * @brief FC7xxx ADC driver source code
 * @version 0.1.0
 * @date 2024-01-15
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Author        CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-15    Flagchip0126  N/A          First version for FC7240
   ******************************************************************************** */

#include "fc7xxx_driver_adc.h"
#include "fc7xxx_driver_scg.h"
#include "fc7xxx_driver_pcc.h"
#include "fc7xxx_driver_dma.h"

/**
 * @name  ADC default values
 * @brief ADC default configuration parameters
 *
 * @{
 */

#define ADC_DEFAULT_SAMPLE_TIME_OPTION_0                  (0x04U)
#define ADC_DEFAULT_SAMPLE_TIME_OPTION_1                  (0x0AU)
#define ADC_DEFAULT_SAMPLE_TIME_OPTION_2                  (0x22U)
#define ADC_DEFAULT_SAMPLE_TIME_OPTION_3                  (0x82U)
#define ADC_DEFAULT_STARTUP_COUNTER                       (0xC0U)
#define ADC_DEFAULT_WATER_MARK                            (0x10U)
#define ADC_DEFAULT_COMPARE_HIGH_THRESHOLD                (0x000U)
#define ADC_DEFAULT_COMPARE_LOW_THRESHOLD                 (0x200U)
#define ADC_DEFAULT_SC_CHANNEL                            (0x3FU)
/** @}*/

/********* Local Variables ************/
static ADC_Type *const s_apAdcBase[ADC_INSTANCE_COUNT] = ADC_BASE_PTRS;
static ADC_ConvCompleteCallbackType s_apAdcCoCoNotify[ADC_INSTANCE_COUNT] = {NULL};
static ADC_OverRunInterruptCallbackType s_apAdcOvrNotify[ADC_INSTANCE_COUNT] = {NULL};
static ADC_CompareInterruptCallbackType s_apAdcCmpNotify[ADC_INSTANCE_COUNT] = {NULL};
static ADC_EndOfSeqGroupInterruptCallbackType s_apEndOfSeqGroupNotify[ADC_INSTANCE_COUNT] = {NULL};
static uint32_t *s_apAdcResultBuffer[ADC_INSTANCE_COUNT] = {NULL};
static uint32_t *s_apAdcSeqGroupResultBuffer[ADC_INSTANCE_COUNT][ADC_SEQUENCE_GROUP_CNT] = {NULL};
static uint8_t s_u8ChannelCnt[ADC_INSTANCE_COUNT] = {0U};
static uint8_t s_u8SeqGroupCnt[ADC_INSTANCE_COUNT] = {0U};

/******* Local Function Prototype *********/

/**
 * @brief The internal interrupt handler function for ADC instances
 *
 * @param eInstance the ADC instance selected
 */
static void ADCn_IRQHandler(const ADC_InstanceType eInstance);

/**
 * @brief The internal DMA handler function for ADC instances
 *
 * @param eInstance the ADC instance selected
 */
static void ADCn_DMAHandler(const ADC_InstanceType eInstance);

/**
 * @brief The internal DMA handler function for ADC instance 0
 *
 */
static void ADC0_DMAHandler(void);

/**
 * @brief The internal DMA handler function for ADC instance 1
 *
 */
static void ADC1_DMAHandler(void);

/**
 * @brief The interrupt handler function for ADC instance 0
 *
 */
void ADC0_IRQHandler(void);

/**
 * @brief The interrupt handler function for ADC instance 1
 *
 */
void ADC1_IRQHandler(void);

/********* Local Functions ************/

/***************ADC IRQ Functions*****************/
static void ADCn_IRQHandler(const ADC_InstanceType eInstance)
{
    ADC_Type *const pAdc = s_apAdcBase[eInstance];
    bool bConvCompleted;
    bool bSeqGroupCompleted;
    uint32_t u32CurSeqGroupIdx;
    uint32_t u32SeqGroupStart;
    uint32_t u32SeqGroupEnd;
    uint8_t u8Idx;
    uint8_t u8BufferIdx;

    if (ADC_HWA_GetSeqGpEn(pAdc) == true)
    {
        bSeqGroupCompleted = false;
        for (u8Idx = 0U; u8Idx < ADC_SEQUENCE_GROUP_CNT; u8Idx++)
        {
            if (ADC_HWA_GetEndOfSequenceGroupInterruptFlag(pAdc, u8Idx) == true)
            {
                bSeqGroupCompleted = true;
                u32CurSeqGroupIdx = u8Idx;
                break;
            }
        }
        if (bSeqGroupCompleted)
        {
            DEV_ASSERT(s_apAdcSeqGroupResultBuffer[eInstance] != NULL);
            u8BufferIdx = 0U;
            u32SeqGroupStart = ADC_HWA_GetSeqGroupStartPoint(pAdc, u32CurSeqGroupIdx);
            u32SeqGroupEnd = ADC_HWA_GetSeqGroupEndPoint(pAdc, u32CurSeqGroupIdx);
            for (u8Idx = u32SeqGroupStart; u8Idx < u32SeqGroupEnd + 1U; u8Idx++)
            {
                s_apAdcSeqGroupResultBuffer[eInstance][u32CurSeqGroupIdx][u8BufferIdx++] = ADC_HWA_GetChannelData(pAdc, u8Idx);
            }
            if (s_apEndOfSeqGroupNotify[eInstance] != NULL)
            {
                s_apEndOfSeqGroupNotify[eInstance](u32CurSeqGroupIdx);
            }
        }
    }
    else if (ADC_HWA_GetSequenceMode(pAdc) == ADC_SEQMODE_DISCONTINUOUS_1)
    {
        bConvCompleted = true;
        for (u8Idx = 0U; u8Idx < s_u8ChannelCnt[eInstance]; u8Idx++)
        {
            if (ADC_HWA_GetChannelConvertComplete(pAdc, u8Idx) == false)
            {
                bConvCompleted = false;
                break;
            }
            if (u8Idx == s_u8ChannelCnt[eInstance] - 1 && ADC_HWA_GetChannelInterruptEnable(pAdc, u8Idx) == false)
            {
                bConvCompleted = false;
                break;
            }
        }
        if (bConvCompleted)
        {
            DEV_ASSERT(s_apAdcResultBuffer[eInstance] != NULL);
            for (u8Idx = 0U; u8Idx < s_u8ChannelCnt[eInstance]; u8Idx++)
            {
                s_apAdcResultBuffer[eInstance][u8Idx] = ADC_HWA_GetChannelData(pAdc, u8Idx);
            }
            if (s_apAdcCoCoNotify[eInstance] != NULL)
            {
                s_apAdcCoCoNotify[eInstance](s_apAdcResultBuffer[eInstance]);
            }
        }
    }
    else
    {
        bool bAdcSequenceComplete = ADC_HWA_GetEndOfSequence(pAdc);
        bool bAdcFifoFull = ADC_HWA_GetFull(pAdc);
        if ((bAdcSequenceComplete == true) ||
            (bAdcFifoFull == true))
        {
            DEV_ASSERT(s_apAdcResultBuffer[eInstance] != NULL);
            u8Idx = 0U;
            while ((ADC_HWA_GetEmpty(pAdc) == false) && (u8Idx != s_u8ChannelCnt[eInstance]))
            {
                s_apAdcResultBuffer[eInstance][u8Idx] = ADC_HWA_GetFIFOData(pAdc);
                u8Idx++;
            }
            if (ADC_HWA_GetEndOfSequence(pAdc))
            {
                ADC_HWA_ClearEndOfSequence(pAdc);
            }
            if (ADC_HWA_GetEndOfConversion(pAdc))
            {
                ADC_HWA_ClearEndOfConversion(pAdc);
            }
            if (ADC_HWA_GetEndOfSample(pAdc))
            {
                ADC_HWA_ClearEndOfSample(pAdc);
            }
            if (ADC_HWA_GetReady(pAdc))
            {
                ADC_HWA_ClearReady(pAdc);
            }
            if (s_apAdcCoCoNotify[eInstance] != NULL)
            {
                s_apAdcCoCoNotify[eInstance](s_apAdcResultBuffer[eInstance]);
            }
        }
    }

    if (ADC_HWA_GetOverRun(pAdc))
    {
        ADC_HWA_ClearOverRun(pAdc);
        if (s_apAdcOvrNotify[eInstance] != NULL)
        {
            s_apAdcOvrNotify[eInstance]();
        }
    }

    if (ADC_HWA_GetCompareFlag(pAdc))
    {
        ADC_HWA_ClearCompareFlag(pAdc);
        if (s_apAdcCmpNotify[eInstance] != NULL)
        {
            s_apAdcCmpNotify[eInstance]();
        }
    }
}

void ADC0_IRQHandler(void)
{
    ADCn_IRQHandler(ADC_INSTANCE_0);
}

void ADC1_IRQHandler(void)
{
    ADCn_IRQHandler(ADC_INSTANCE_1);
}

static void ADCn_DMAHandler(const ADC_InstanceType eInstance)
{
    ADC_Type *const pAdc = s_apAdcBase[eInstance];
    uint8_t u8Idx;
    uint32_t u32CurSeqGroupIdx;

    for (u8Idx = 0U; u8Idx < ADC_SEQUENCE_GROUP_CNT; u8Idx++)
    {
        if (ADC_HWA_GetEndOfSequenceGroupInterruptFlag(pAdc, u8Idx) == true)
        {
            u32CurSeqGroupIdx = u8Idx;
            break;
        }
    }

    if (ADC_HWA_GetEndOfSequence(pAdc))
    {
        ADC_HWA_ClearEndOfSequence(pAdc);
    }
    if (ADC_HWA_GetEndOfConversion(pAdc))
    {
        ADC_HWA_ClearEndOfConversion(pAdc);
    }
    if (ADC_HWA_GetEndOfSample(pAdc))
    {
        ADC_HWA_ClearEndOfSample(pAdc);
    }
    if (ADC_HWA_GetFIFOReady(pAdc))
    {
        ADC_HWA_ClearFIFOReady(pAdc);
    }
    if (s_apAdcCoCoNotify[eInstance] != NULL)
    {
        s_apAdcCoCoNotify[eInstance](s_apAdcResultBuffer[eInstance]);
    }
    if (s_apEndOfSeqGroupNotify[eInstance] != NULL)
    {
        s_apEndOfSeqGroupNotify[eInstance](u32CurSeqGroupIdx);
    }
}

static void ADC0_DMAHandler(void)
{
    ADCn_DMAHandler(ADC_INSTANCE_0);
}

static void ADC1_DMAHandler(void)
{
    ADCn_DMAHandler(ADC_INSTANCE_1);
}

/***************** Global Functions *********************/
void ADC_InitStructure(ADC_InitType *const pInitCfg)
{
    DEV_ASSERT(pInitCfg != NULL);

    pInitCfg->eResolution     = ADC_RESOLUTION_12_BIT;      /* 12 bit Resolution */
    pInitCfg->eAlign          = ADC_ALIGN_RIGHT;            /* Align right */
    pInitCfg->eTriggerMode    = ADC_TRIGMODE_SW;            /* Software trigger */
    pInitCfg->bWaitEnable     = false;                      /* Disable wait conversion mode */
    pInitCfg->bSequenceGroupModeEnable = false;             /* Disable sequence group mode */
    pInitCfg->eTrgLatchUnitPri = TRG_LATCH_UNIT_PRI_ROUND_ROBIN;      /* Round Robin priority */
    pInitCfg->eClockDivider   = ADC_CLOCK_DIV_1;            /* Adc clock divided by 1 */
    pInitCfg->eSequenceMode   = ADC_SEQMODE_SINGLE;         /* Single sequence mode */
    pInitCfg->bAutoDis        = false;                      /* Disable auto disable mode */
    pInitCfg->eOverrunMode    = ADC_OVERRUN_MODE_PRESERVE;  /* Old conversion data preserved when overrun occured */
    pInitCfg->eVoltageRef     = ADC_REF_INTERNAL;                  /* Use internal reference */
    pInitCfg->bHwAvgEnable    = false;                             /* Disable averaging functionality */
    pInitCfg->eHwAverage      = ADC_AVERAGE_4;                     /* Average by 4 samples if average is enabled */
    pInitCfg->aSampleTimes[0] = ADC_DEFAULT_SAMPLE_TIME_OPTION_0;  /* Sample time option 0 is 4 ADC Clock */
    pInitCfg->aSampleTimes[1] = ADC_DEFAULT_SAMPLE_TIME_OPTION_1;  /* Sample time option 1 is 10 ADC Clock */
    pInitCfg->aSampleTimes[2] = ADC_DEFAULT_SAMPLE_TIME_OPTION_2;  /* Sample time option 2 is 34 ADC Clock */
    pInitCfg->aSampleTimes[3] = ADC_DEFAULT_SAMPLE_TIME_OPTION_3;  /* Sample time option 3 is 130 ADC Clock */
}

void ADC_Init(const ADC_InstanceType eInstance, const ADC_InitType *const pInitCfg)
{
    DEV_ASSERT(eInstance < ADC_INSTANCE_COUNT);
    DEV_ASSERT(pInitCfg != NULL);

    ADC_Type *const pAdc = s_apAdcBase[eInstance];
    uint32_t u32TimeOut = 15000000U;
    uint32_t u32Cfg1;
    uint32_t u32Cfg2;
    uint32_t u32Cal;
    ADC_TrigSrcType eTriggerSrc;
    ADC_TrigModeType eTriggerMode;
    uint32_t u32ClockDiv;
    uint32_t u32StartupCnt;

    if (pInitCfg->bSequenceGroupModeEnable == false)
    {
        if (pInitCfg->eSequenceMode == ADC_SEQMODE_DISCONTINUOUS_1)
        {
            eTriggerSrc = ADC_TRIGSRC_PTIMER;
            eTriggerMode = ADC_TRIGMODE_RISING_EDGE;
        }
        else
        {
            eTriggerSrc = ADC_TRIGSRC_TRGSEL;
            eTriggerMode = pInitCfg->eTriggerMode;
        }
    }
    else
    {
        eTriggerSrc = ADC_TRIGSRC_TRIG_LATCH_UNIT;
        eTriggerMode = ADC_TRIGMODE_RISING_EDGE;
    }

    PCC_ClkSrcType eAdcClkName = PCC_CLK_ADC0;
    uint32_t u32AdcClk;

    switch (eInstance)
    {
        case ADC_INSTANCE_0:
        {
            eAdcClkName = PCC_CLK_ADC0;
            break;
        }

        case ADC_INSTANCE_1:
        {
            eAdcClkName = PCC_CLK_ADC1;
            break;
        }

        default:
            break;
    }
    u32ClockDiv = 1U << pInitCfg->eClockDivider;

    u32AdcClk = PCC_GetPccFunctionClock(eAdcClkName);

    /* The start up count shall be around 5us */
    u32StartupCnt = u32AdcClk / u32ClockDiv / 1000000U * 5U + 1U;
    if (u32StartupCnt < 2U)
    {
        u32StartupCnt = 2U;
    }
    else if (u32StartupCnt > 255U)
    {
        u32StartupCnt = 255U;
    }
    else
    {}

    ADC_HWA_Reset(pAdc);

    u32Cfg1 = ADC_CFG1_OVRMOD(pInitCfg->eOverrunMode) |
              ADC_CFG1_SEQGP_EN(pInitCfg->bSequenceGroupModeEnable)  |
              ADC_CFG1_SEQ_LEN(0) |
              ADC_CFG1_SEQ_MOD(pInitCfg->eSequenceMode) |
              ADC_CFG1_AUTO_DIS(pInitCfg->bAutoDis) |
              ADC_CFG1_WAIT(pInitCfg->bWaitEnable) |
              ADC_CFG1_TRIGSRC(eTriggerSrc) |
              ADC_CFG1_TRIGMODE(eTriggerMode) |
              ADC_CFG1_ALIGN(pInitCfg->eAlign) |
              ADC_CFG1_RES(pInitCfg->eResolution) |
              ADC_CFG1_DMAEN(false);
    ADC_HWA_SetConfig1(pAdc, u32Cfg1);

    u32Cfg2 = ADC_CFG2_FWMARK(ADC_DEFAULT_WATER_MARK) |
              ADC_CFG2_TRG_PRI(pInitCfg->eTrgLatchUnitPri) |
              ADC_CFG2_TRG_CLR(1U) |
              ADC_CFG2_AVG_EN(pInitCfg->bHwAvgEnable) |
              ADC_CFG2_AVG_LEN(pInitCfg->eHwAverage) |
              ADC_CFG2_REF_EXT(pInitCfg->eVoltageRef) |
              ADC_CFG2_STCNT(u32StartupCnt);
    ADC_HWA_SetConfig2(pAdc, u32Cfg2);

    u32Cal = ADC_CAL_CAL_EN(pInitCfg->bCalEnable) |
             ADC_CAL_OFFSET(pInitCfg->s32CalOffset) |
             ADC_CAL_GAIN(pInitCfg->s32CalGain);

    ADC_HWA_SetCal(pAdc, u32Cal);

    ADC_HWA_SetClockGatingEnableFlag(pAdc, true);
    while ((ADC_HWA_GetClockGatingAck(pAdc) != true) && (u32TimeOut != 0))
    {
        u32TimeOut--;
    }
    if (ADC_HWA_GetClockGatingAck(pAdc) == true)
    {
        ADC_HWA_SetClockDivider(pAdc, pInitCfg->eClockDivider);
    }
    u32TimeOut = 15000000U;
    ADC_HWA_SetClockGatingEnableFlag(pAdc, false);
    while ((ADC_HWA_GetClockGatingAck(pAdc) != false) && (u32TimeOut != 0))
    {
        u32TimeOut--;
    }

    uint8_t u8SmprIndex;
    for (u8SmprIndex = 0U; u8SmprIndex < ADC_SAMPLE_TIME_OPTION_CNT; u8SmprIndex++)
    {
        ADC_HWA_SetSampleTime(pAdc, u8SmprIndex, pInitCfg->aSampleTimes[u8SmprIndex] - 2U);
    }
}

void ADC_DeInit(const ADC_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < ADC_INSTANCE_COUNT);

    ADC_Type *const pAdc = s_apAdcBase[eInstance];
    uint32_t u32Cfg1;
    uint32_t u32Cfg2;

    ADC_HWA_Reset(pAdc);

    ADC_HWA_SetInterruptEnable(pAdc, 0U);

    u32Cfg1 = ADC_CFG1_OVRMOD(ADC_OVERRUN_MODE_PRESERVE) |
              ADC_CFG1_SEQGP_EN(false) |
              ADC_CFG1_SEQ_LEN(0U) |
              ADC_CFG1_SEQ_MOD(ADC_SEQMODE_SINGLE) |
              ADC_CFG1_AUTO_DIS(false) |
              ADC_CFG1_WAIT(false) |
              ADC_CFG1_TRIGSRC(ADC_TRIGSRC_PTIMER) |
              ADC_CFG1_TRIGMODE(ADC_TRIGMODE_SW) |
              ADC_CFG1_ALIGN(ADC_ALIGN_RIGHT) |
              ADC_CFG1_RES(ADC_RESOLUTION_12_BIT) |
              ADC_CFG1_DMAEN(false);
    ADC_HWA_SetConfig1(pAdc, u32Cfg1);

    u32Cfg2 = ADC_CFG2_FWMARK(ADC_DEFAULT_WATER_MARK) |
              ADC_CFG2_TRG_PRI(TRG_LATCH_UNIT_PRI_ROUND_ROBIN) |
              ADC_CFG2_TRG_CLR(1U) |
              ADC_CFG2_AVG_EN(false) |
              ADC_CFG2_AVG_LEN(ADC_AVERAGE_4) |
              ADC_CFG2_REF_EXT(ADC_REF_INTERNAL) |
              ADC_CFG2_STCNT(ADC_DEFAULT_STARTUP_COUNTER);
    ADC_HWA_SetConfig2(pAdc, u32Cfg2);

    ADC_HWA_SetSampleTime(pAdc, 0U, ADC_DEFAULT_SAMPLE_TIME_OPTION_0 - 2U);
    ADC_HWA_SetSampleTime(pAdc, 1U, ADC_DEFAULT_SAMPLE_TIME_OPTION_1 - 2U);
    ADC_HWA_SetSampleTime(pAdc, 2U, ADC_DEFAULT_SAMPLE_TIME_OPTION_2 - 2U);
    ADC_HWA_SetSampleTime(pAdc, 3U, ADC_DEFAULT_SAMPLE_TIME_OPTION_3 - 2U);

    ADC_HWA_SetHwCompareEnableFlag(pAdc, false);
    ADC_HWA_SetHwCompareChannel(pAdc, ADC_CMP_CHANNEL_ALL, 0U);

    ADC_HWA_SetHwCompareThreshold(pAdc, ADC_DEFAULT_COMPARE_LOW_THRESHOLD, ADC_DEFAULT_COMPARE_HIGH_THRESHOLD);

    uint8_t u8ChnIndex;
    for (u8ChnIndex = 0U; u8ChnIndex < ADC_SC_COUNT; u8ChnIndex++)
    {
        ADC_HWA_SetChannelSampleTimeIndex(pAdc, u8ChnIndex, 0U);
        ADC_HWA_SetChannelInterruptEnable(pAdc, u8ChnIndex, false);
        ADC_HWA_SetChannelInput(pAdc, u8ChnIndex, ADC_DEFAULT_SC_CHANNEL);
    }

    /* TODO : CAL Rregister */
}

void ADC_InitChannel(const ADC_InstanceType eInstance, const ADC_ChannelCfgType aChannels[],
                     const uint8_t u8ChnCnt)
{
    DEV_ASSERT(eInstance < ADC_INSTANCE_COUNT);
    DEV_ASSERT(u8ChnCnt < ADC_SC_COUNT);
    DEV_ASSERT(aChannels != NULL);

    ADC_Type *const pAdc = s_apAdcBase[eInstance];

    s_u8ChannelCnt[eInstance] = u8ChnCnt;

    uint8_t u8ChnIndex;
    for (u8ChnIndex = 0U; u8ChnIndex < u8ChnCnt; u8ChnIndex++)
    {
        ADC_HWA_SetChannelDiff(pAdc, u8ChnIndex, aChannels[u8ChnIndex].bDiff);
        ADC_HWA_SetChannelSampleTimeIndex(pAdc, u8ChnIndex, aChannels[u8ChnIndex].eSampleTimeOption);
        ADC_HWA_SetChannelInterruptEnable(pAdc, u8ChnIndex, false);
        ADC_HWA_SetChannelInput(pAdc, u8ChnIndex, aChannels[u8ChnIndex].eChannel);
    }

    if (ADC_HWA_GetSeqGpEn(pAdc) != true && ADC_HWA_GetSequenceMode(pAdc) != ADC_SEQMODE_DISCONTINUOUS_1)
    {
        ADC_HWA_SetSequenceLength(pAdc, u8ChnCnt - 1U);
        ADC_HWA_SetFIFOWaterMark(pAdc, u8ChnCnt - 1U);
    }
}

void ADC_InitSequenceGroup(const ADC_InstanceType eInstance, const ADC_SequenceGroupType aSeqGroup[],
                           const uint8_t u8SeqGroupCnt)
{
    DEV_ASSERT(eInstance < ADC_INSTANCE_COUNT);
    DEV_ASSERT(u8SeqGroupCnt < ADC_SEQUENCE_GROUP_CNT);
    DEV_ASSERT(aSeqGroup != NULL);

    ADC_Type *const pAdc = s_apAdcBase[eInstance];

    s_u8SeqGroupCnt[eInstance] = u8SeqGroupCnt;

    uint8_t u8ChnIndex;
    for (u8ChnIndex = 0U; u8ChnIndex < u8SeqGroupCnt; u8ChnIndex++)
    {
        ADC_HWA_SetSeqGroupStartEndPoint(pAdc, u8ChnIndex, aSeqGroup[u8ChnIndex].u8Start, aSeqGroup[u8ChnIndex].u8Start + aSeqGroup[u8ChnIndex].u8Len);
        ADC_HWA_SetEndOfSequenceGroupInterruptEnable(pAdc, u8ChnIndex, false);
    }
}

void ADC_InitCompare(const ADC_InstanceType eInstance, const ADC_CompareType *const pCmpCfg)
{
    DEV_ASSERT(eInstance < ADC_INSTANCE_COUNT);
    DEV_ASSERT(pCmpCfg != NULL);

    ADC_Type *const pAdc = s_apAdcBase[eInstance];

    ADC_HWA_SetHwCompareChannel(pAdc, pCmpCfg->eCmpSingleChn, pCmpCfg->u8CmpChnSel);
    ADC_HWA_SetHwCompareThreshold(pAdc, pCmpCfg->u16LowThres, pCmpCfg->u16HighThres);
    ADC_HWA_SetHwCompareEnableFlag(pAdc, pCmpCfg->bCmpEnable);
}

void ADC_InitInterrupt(const ADC_InstanceType eInstance, const ADC_InterruptType *const pInterruptCfg)
{
    DEV_ASSERT(eInstance < ADC_INSTANCE_COUNT);
    DEV_ASSERT(pInterruptCfg != NULL);
    DEV_ASSERT(s_u8ChannelCnt[eInstance] > 0U);
    ADC_Type *const pAdc = s_apAdcBase[eInstance];
    uint32_t u32InterruptCfg;
    uint8_t u8SeqGroupIndex;

    if (ADC_HWA_GetSeqGpEn(pAdc) == false)
    {
        s_apAdcResultBuffer[eInstance] = pInterruptCfg->pResultBuffer;
        if (ADC_HWA_GetSequenceMode(pAdc) == ADC_SEQMODE_DISCONTINUOUS_1)
        {
            u32InterruptCfg = ADC_INT_ENABLE_TRGERR_IE(false) |
                              ADC_INT_ENABLE_FIFO_RDY_IE(false) |
                              ADC_INT_ENABLE_ACMP_IE(pInterruptCfg->bAnalogCmpIntEn) |
                              ADC_INT_ENABLE_OVRIE(false) |
                              ADC_INT_ENABLE_EOSEQIE(false) |
                              ADC_INT_ENABLE_EOCIE(false) |
                              ADC_INT_ENABLE_EOSMPIE(false) |
                              ADC_INT_ENABLE_ADRDYIE(false);
            ADC_HWA_SetInterruptEnable(pAdc, u32InterruptCfg);
            ADC_HWA_SetChannelInterruptEnable(pAdc, s_u8ChannelCnt[eInstance] - 1U, pInterruptCfg->bConversionCompleteIntEn);
        }
        else
        {
            u32InterruptCfg = ADC_INT_ENABLE_TRGERR_IE(false) |
                              ADC_INT_ENABLE_FIFO_RDY_IE(false) |
                              ADC_INT_ENABLE_ACMP_IE(pInterruptCfg->bAnalogCmpIntEn) |
                              ADC_INT_ENABLE_OVRIE(pInterruptCfg->bOverRunIntEn) |
                              ADC_INT_ENABLE_EOSEQIE(pInterruptCfg->bConversionCompleteIntEn) |
                              ADC_INT_ENABLE_EOCIE(false) |
                              ADC_INT_ENABLE_EOSMPIE(false) |
                              ADC_INT_ENABLE_ADRDYIE(false);
            ADC_HWA_SetInterruptEnable(pAdc, u32InterruptCfg);
        }
    }
    else
    {
        for (u8SeqGroupIndex = 0U; u8SeqGroupIndex < ADC_SEQUENCE_GROUP_CNT; u8SeqGroupIndex++)
        {
            s_apAdcSeqGroupResultBuffer[eInstance][u8SeqGroupIndex] = pInterruptCfg->pSequenceGroupResultBuffer[u8SeqGroupIndex];
        }
        u32InterruptCfg = ADC_INT_ENABLE_TRGERR_IE(false) |
                          ADC_INT_ENABLE_FIFO_RDY_IE(false) |
                          ADC_INT_ENABLE_ACMP_IE(pInterruptCfg->bAnalogCmpIntEn) |
                          ADC_INT_ENABLE_OVRIE(false) |
                          ADC_INT_ENABLE_EOSEQIE(false) |
                          ADC_INT_ENABLE_EOCIE(false) |
                          ADC_INT_ENABLE_EOSMPIE(false) |
                          ADC_INT_ENABLE_ADRDYIE(false);
        ADC_HWA_SetInterruptEnable(pAdc, u32InterruptCfg);
        for (u8SeqGroupIndex = 0U; u8SeqGroupIndex < s_u8SeqGroupCnt[eInstance]; u8SeqGroupIndex++)
        {
            ADC_HWA_SetEndOfSequenceGroupInterruptEnable(pAdc, u8SeqGroupIndex, true);
        }
    }

    s_apAdcCoCoNotify[eInstance] = pInterruptCfg->pConvCompleteNotify;
    s_apAdcOvrNotify[eInstance] = pInterruptCfg->pOverRunNotify;
    s_apAdcCmpNotify[eInstance] = pInterruptCfg->pCompareNotify;
    s_apEndOfSeqGroupNotify[eInstance] = pInterruptCfg->pEndOfSeqGroupNotify;
}

void ADC_InitDmaChannel(const ADC_InstanceType eInstance, const ADC_DmaType *const pAdcDmaCfg)
{
    DEV_ASSERT(eInstance < ADC_INSTANCE_COUNT);
    DEV_ASSERT(pAdcDmaCfg != NULL);
    uint32_t u32ResultStart;
    uint32_t u32ResultEnd;

    ADC_Type *const pAdc = s_apAdcBase[eInstance];

    if (pAdcDmaCfg->bDmaEnable == true)
    {
        s_apAdcResultBuffer[eInstance] = pAdcDmaCfg->pResultBuffer;
        s_apAdcCoCoNotify[eInstance] = pAdcDmaCfg->pConvCompleteNotify;

        DMA_ChannelCfgType tDmaCfg;
        if (ADC_HWA_GetSeqGpEn(pAdc) == true)
        {
            u32ResultStart = ADC_HWA_GetSeqGroupStartPoint(pAdc, (uint8_t)pAdcDmaCfg->eSeqGroupIndex);
            u32ResultEnd = ADC_HWA_GetSeqGroupEndPoint(pAdc, (uint8_t)pAdcDmaCfg->eSeqGroupIndex);
            tDmaCfg.pSrcBuffer = &pAdc->RESULT[u32ResultStart];
            tDmaCfg.pDestBuffer = pAdcDmaCfg->pResultBuffer;
            tDmaCfg.u32BlockSize = 4U;
            tDmaCfg.u16BlockCount = u32ResultStart - u32ResultEnd;
            tDmaCfg.eSrcIncMode = DMA_INCREMENT_DATA_SIZE;
        }
        else if (ADC_HWA_GetSequenceMode(pAdc) == ADC_SEQMODE_DISCONTINUOUS_1)
        {
            tDmaCfg.pSrcBuffer = &pAdc->RESULT[0U];
            tDmaCfg.pDestBuffer = pAdcDmaCfg->pResultBuffer;
            tDmaCfg.u32BlockSize = 4U;
            tDmaCfg.u16BlockCount = s_u8ChannelCnt[eInstance];
            tDmaCfg.eSrcIncMode = DMA_INCREMENT_DATA_SIZE;
        }
        else
        {
            tDmaCfg.pSrcBuffer = &pAdc->FIFO_DATA;
            tDmaCfg.pDestBuffer = pAdcDmaCfg->pResultBuffer;
            tDmaCfg.u32BlockSize = 4U * s_u8ChannelCnt[eInstance];
            tDmaCfg.u16BlockCount = 1U;
            tDmaCfg.eSrcIncMode = DMA_INCREMENT_DISABLE;
        }
        tDmaCfg.eDestIncMode = DMA_INCREMENT_DATA_SIZE;
        tDmaCfg.eSrcDataSize = DMA_TRANSFER_SIZE_4B;
        tDmaCfg.eDestDataSize = DMA_TRANSFER_SIZE_4B;
        tDmaCfg.u8ChannelPriority = pAdcDmaCfg->u8ChannelPriority;
        tDmaCfg.bSrcBlockOffsetEn = false;
        tDmaCfg.bDestBlockOffsetEn = false;
        tDmaCfg.s32BlockOffset = 0;
        tDmaCfg.bSrcAddrLoopbackEn = true;
        tDmaCfg.bDestAddrLoopbackEn = true;
        tDmaCfg.bAutoStop = false;
        tDmaCfg.bSrcCircularBufferEn = false;
        tDmaCfg.u32SrcCircBufferSize = DMA_CIRCULAR_BUFFER_SIZE_1B;
        tDmaCfg.bDestCircularBufferEn = false;
        tDmaCfg.u32DestCircBufferSize = DMA_CIRCULAR_BUFFER_SIZE_1B;
        if (eInstance == ADC_INSTANCE_0)
        {
            tDmaCfg.eTriggerSrc = DMA_REQ_ADC0;
        }
        else if (eInstance == ADC_INSTANCE_1)
        {
            tDmaCfg.eTriggerSrc = DMA_REQ_ADC1;
        }
        else
        {}

        DMA_InterruptCfgType dmaIntCfg = {0};
        dmaIntCfg.bTransferCompleteIntEn = true;
        if (eInstance == ADC_INSTANCE_0)
        {
            dmaIntCfg.pTransferCompleteNotify = ADC0_DMAHandler;
        }
        else if (eInstance == ADC_INSTANCE_1)
        {
            dmaIntCfg.pTransferCompleteNotify = ADC1_DMAHandler;
        }
        else
        {}

        dmaIntCfg.bTransferErrorIntEn = false;
        dmaIntCfg.pTransferErrorNotify = NULL;

        ADC_HWA_SetDMAEnableFlag(pAdc, true);

        DMA_InitChannel(pAdcDmaCfg->eDmaInstance, pAdcDmaCfg->eDmaChannel, &tDmaCfg);
        DMA_InitChannelInterrupt(pAdcDmaCfg->eDmaInstance, pAdcDmaCfg->eDmaChannel, &dmaIntCfg);
    }
    else
    {
        ADC_HWA_SetDMAEnableFlag(pAdc, false);
    }
}

ADC_StatusType ADC_Enable(const ADC_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < ADC_INSTANCE_COUNT);
    ADC_StatusType eRet = ADC_STATUS_SUCCESS;
    uint32_t u32TimeOut = 15000000U;
    ADC_Type *const pAdc = s_apAdcBase[eInstance];

    ADC_HWA_Enable(pAdc);
    while ((ADC_HWA_GetReady(pAdc) != true) && (u32TimeOut != 0U))
    {
        u32TimeOut--;
    }
    if (u32TimeOut != 0U)
    {
        ADC_HWA_ClearReady(pAdc);
        eRet = ADC_STATUS_SUCCESS;
    }
    else
    {
        eRet = ADC_STATUS_TIMEOUT;
    }
    return eRet;
}

ADC_StatusType ADC_Disable(const ADC_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < ADC_INSTANCE_COUNT);
    ADC_StatusType eRet = ADC_STATUS_SUCCESS;
    uint32_t u32TimeOut = 15000000U;
    ADC_Type *const pAdc = s_apAdcBase[eInstance];

    if (ADC_HWA_GetStart(pAdc) == true)
    {
        eRet = ADC_Stop(eInstance);
    }

    if (eRet == ADC_STATUS_SUCCESS)
    {
        ADC_HWA_Disable(pAdc);
        while ((ADC_HWA_GetEnable(pAdc) == true) && (u32TimeOut != 0U))
        {
            u32TimeOut--;
        }
        if (u32TimeOut != 0U)
        {
            eRet = ADC_STATUS_SUCCESS;
        }
        else
        {
            eRet = ADC_STATUS_TIMEOUT;
        }
    }
    return eRet;
}

void ADC_Start(const ADC_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < ADC_INSTANCE_COUNT);
    ADC_Type *const pAdc = s_apAdcBase[eInstance];
    ADC_HWA_Start(pAdc);
}

ADC_StatusType ADC_Stop(const ADC_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < ADC_INSTANCE_COUNT);
    ADC_StatusType eRet = ADC_STATUS_ERROR;
    uint32_t u32TimeOut = 15000000U;
    ADC_Type *const pAdc = s_apAdcBase[eInstance];

    ADC_HWA_Stop(pAdc);

    while ((ADC_HWA_GetStop(pAdc) == true) && (u32TimeOut != 0U))
    {
        u32TimeOut--;
    }
    if (u32TimeOut != 0U)
    {
        eRet = ADC_STATUS_SUCCESS;
    }
    else
    {
        eRet = ADC_STATUS_TIMEOUT;
    }
    return eRet;
}

void ADC_Reset(const ADC_InstanceType eInstance)
{
    DEV_ASSERT(eInstance < ADC_INSTANCE_COUNT);
    ADC_Type *const pAdc = s_apAdcBase[eInstance];
    ADC_HWA_Reset(pAdc);
}
