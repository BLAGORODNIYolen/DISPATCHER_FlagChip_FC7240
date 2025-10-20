/**
 * @file fc7xxx_driver_fciic.c
 * @author Flagchip
 * @brief FC7xxx FCIIC driver type definition and API
 * @version 0.1.0
 * @date 2022-12-31
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */

/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024/1/10    qxw0095      N/A          First version for FC7240
   ******************************************************************************** */

#include "fc7xxx_driver_fciic.h"
#include "interrupt_manager.h"

#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

/* #define FCIIC_RX_FIFO */


/* iic instance value */
static  FCIIC_Type *const s_aFCIIC_InstanceTable[FCIIC_INSTANCE_COUNT] = FCIIC_BASE_PTRS;

/* store notify callback function point */
static FCIIC_ErrorInterrupt_CallBackType   s_aFCIIC_ErrorNotifyTable[FCIIC_INSTANCE_COUNT] = {NULL};
static FCIIC_RxInterrupt_CallBackType      s_aFCIIC_RxNotifyTable[FCIIC_INSTANCE_COUNT] =    {NULL};

#ifdef FCIIC_RX_ALL_POLLING
    /* check every pFciic instance whether is used */
    static uint8_t s_aFCIIC_IicMasterUsed[FCIIC_INSTANCE_COUNT];
    static uint8_t s_aFCIIC_IicSlaveUsed[FCIIC_INSTANCE_COUNT];
#endif


/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */
#if 0
static void CheckAndClear(FCIIC_Type *pFciic);
#endif
static void FCIIC_LL_MasterIRQnHandler(uint8_t u8IicIndex);
static void FCIIC_LL_SlaveIRQnHandler(uint8_t u8IicIndex);
static uint8_t FCIIC_Init_Master(uint8_t u8IicIndex, FCIIC_InitType *pInitCfg);
static uint8_t FCIIC_Init_Slave(uint8_t u8IicIndex, FCIIC_InitType *pInitCfg);


/* ################################################################################## */
/* ########################### Global Prototype Functions ########################### */

void FCIIC0_IRQHandler(void);
void FCIIC1_IRQHandler(void);

/* ################################################################################## */
/* ################################ Local Functions ################################# */


#if 0
static void CheckAndClear(FCIIC_Type *pFciic)
{
    FCIIC_Master_HwA_CheckClearStatus(pFciic, FCIIC_MSR_EPF_STATUS);
    FCIIC_Master_HwA_CheckClearStatus(pFciic, FCIIC_MSR_SDF_STATUS);
    FCIIC_Master_HwA_CheckClearStatus(pFciic, FCIIC_MSR_NDF_STATUS);
    FCIIC_Master_HwA_CheckClearStatus(pFciic, FCIIC_MSR_FEF_STATUS);
    FCIIC_Master_HwA_CheckClearStatus(pFciic, FCIIC_MSR_ALF_STATUS);
}
#endif



/***************************************************
 * FCIIC_LL_MasterIRQnHandler
 *   @detail: Iic n interrupt process
 *
 * param in : u8IicIndex, 0,1,2,3
 * param out: none
 *
 * return   : none
 * ************************************************/
static void FCIIC_LL_MasterIRQnHandler(uint8_t u8IicIndex)
{
    /* uint8_t iic_status; */
    uint8_t          u8RetVal;
    FCIIC_RxDataType pRxData;
    uint32_t         u32ErrorValue;

    /* check pFciic receive data */
    u8RetVal = FCIIC_Master_Receive(u8IicIndex, &pRxData);

    if ((s_aFCIIC_RxNotifyTable[u8IicIndex] != NULL) && (u8RetVal == 0U))
    {
        s_aFCIIC_RxNotifyTable[u8IicIndex](u8IicIndex, &pRxData);
    }

    /* check error */
    u32ErrorValue = FCIIC_Master_GetError(u8IicIndex);
    if ((u32ErrorValue != 0U) && (s_aFCIIC_ErrorNotifyTable[u8IicIndex] != NULL))
    {
        s_aFCIIC_ErrorNotifyTable[u8IicIndex](u8IicIndex, 1U, u32ErrorValue);
        FCIIC_Master_ClrError(u8IicIndex);
    }

}


/***************************************************
 * FCIIC_LL_SlaveIRQnHandler
 *   @detail: Iic n interrupt process
 *
 * param in : u8IicIndex, 0,1,2,3
 * param out: none
 *
 * return   : none
 * ************************************************/
static void FCIIC_LL_SlaveIRQnHandler(uint8_t u8IicIndex)
{
    /* uint8_t iic_status; */
    uint8_t          u8RetVal;
    FCIIC_RxDataType pRxData;
    uint32_t         u32ErrorValue;

    /* check pFciic receive data */
    u8RetVal = FCIIC_Slave_Receive(u8IicIndex, &pRxData);

    if ((s_aFCIIC_RxNotifyTable[u8IicIndex] != NULL) && (u8RetVal == 0U))
    {
        s_aFCIIC_RxNotifyTable[u8IicIndex](u8IicIndex, &pRxData);
    }

    /* check error */
    u32ErrorValue = FCIIC_Slave_GetError(u8IicIndex);
    if ((u32ErrorValue != 0U) && (s_aFCIIC_ErrorNotifyTable[u8IicIndex] != NULL))
    {
        s_aFCIIC_ErrorNotifyTable[u8IicIndex](u8IicIndex, 0U, u32ErrorValue);
        FCIIC_Slave_ClrError(u8IicIndex);
    }

}





/***************************************************
 * FCIIC_Init_Master
 *   @detail: Iic device master mode initial
 *
 * param in : pInitCfg, pFciic initial config parameters
 *             structure address
 * param out: none
 *
 * return   : 0 is ok, others are not ok
 * ************************************************/
static uint8_t FCIIC_Init_Master(uint8_t u8IicIndex, FCIIC_InitType *pInitCfg)
{
    uint32_t u32TempMcr, u32TempMder, u32TempMcfgr0, u32TempMcfgr1, u32TempMcfgr2, u32TempMcfgr3, u32TempMccr0;
    uint32_t u32TempMFCR;

    FCIIC_Type *pFciic;
    uint32_t u32ClkSrcHz;
    uint32_t u32FreqDeltaCur, u32FreqDeltaOld;
    uint32_t u32FreqDesired, u32FreqCur;
    uint32_t u32Prescale, u8PrescaleTemp;
    uint32_t u32CLKHI, u32CLKHITemp;
    uint32_t u32CLKLO, u32CLKLOTemp;

    pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];

    u32ClkSrcHz = pInitCfg->u32ClkSrcHz;
    u32FreqDesired = pInitCfg->u32Frequency;
    u32FreqDeltaOld = u32FreqDesired;

    /* SCL_LATENCY is defined as ROUNDDOWN ((2 + FILTSCL + SCL_RISETIME) / (2 ^ PRESCALE)) */
    /* CLKLO: Minimum value is 0x3 */
    /* CLKHI: Minimum value is 0x1 */
    /* SCL clock period: (CLKHI + CLKLO + 2 + SCL_LATENCY) �� (2 ^ PRESCALE) �� function clock period */
	for(u32CLKHITemp=1U; (u32CLKHITemp < 63U); u32CLKHITemp++)
	{
		for(u32CLKLOTemp=3U; (u32CLKLOTemp < 63U); u32CLKLOTemp++)
		{
			/* get the linear prescale */
			for (u8PrescaleTemp = 0U; u8PrescaleTemp < 8U; u8PrescaleTemp++)
			{
				u32FreqCur = u32ClkSrcHz / Fc_Power(2U, (uint32_t)u8PrescaleTemp)/(u32CLKHITemp+u32CLKLOTemp+2U);
				/* If the current frequency is less than the desired frequency,
				 * compare the delta with the previous one and select the parameter with the smallest delta
				 * */
				if(u32FreqCur <= u32FreqDesired)
				{
					u32FreqDeltaCur = u32FreqDesired - u32FreqCur;
					if (u32FreqDeltaCur < u32FreqDeltaOld)
					{
						u32FreqDeltaOld = u32FreqDeltaCur;
						u32Prescale = u8PrescaleTemp;
						u32CLKHI = u32CLKHITemp;
						u32CLKLO = u32CLKLOTemp;
					}
					break;
				}
			}

			if(u32FreqDeltaOld == 0U)
			{
				break;
			}
		}

		if(u32FreqDeltaOld==0U)
		{
			break;
		}
	}

    u32TempMcr = FCIIC_MCR_RRF(0U)    |
                 FCIIC_MCR_RTF(0U)      |
                 FCIIC_MCR_DBGEN(0U)    |
                 FCIIC_MCR_RST(0U)      |
                 FCIIC_MCR_MEN(1U);         /* master enable */


    u32TempMder = FCIIC_MDER_RDDE(pInitCfg->bEnDma) |   /* enable receive dma */
                  FCIIC_MDER_TDDE(pInitCfg->bEnDma);    /* enable transmit dma */

    u32TempMcfgr0 = FCIIC_MCFGR0_RDMO(0U) |
                    FCIIC_MCFGR0_TRGEN(0U);

    u32TempMcfgr1 = FCIIC_MCFGR1_PINCFG(0U)  |   /* 0=open drain; 1=push-pull mode */
                    FCIIC_MCFGR1_MATCFG(0U)       |
                    FCIIC_MCFGR1_TIMECFG(0U)      |
                    FCIIC_MCFGR1_IGNACK(1U)       |
                    FCIIC_MCFGR1_AUTOSTOP(0U)     |
                    FCIIC_MCFGR1_PRESCALE(u32Prescale);         /* Prescaler = 2^n */

    u32TempMcfgr2 = FCIIC_MCFGR2_FILTSDA(0U)  |
                    FCIIC_MCFGR2_FILTSCL(0U)       |
                    FCIIC_MCFGR2_BUSIDLE(0U);

    u32TempMcfgr3 = FCIIC_MCFGR3_PINLOW(0U);


    u32TempMccr0 = FCIIC_MCCR_DATAVD(0x09U) |
                   FCIIC_MCCR_SETHOLD(0x13U)   |
                   FCIIC_MCCR_CLKHI(u32CLKHI) |
                   FCIIC_MCCR_CLKLO(u32CLKLO); /* 0x09131327; */

    u32TempMFCR = FCIIC_MFCR_TXWATER(pInitCfg->bTxFifoWMrk) | FCIIC_MFCR_RXWATER(pInitCfg->bRxFifoWMrk);

    FCIIC_HWA_SetMder(pFciic, u32TempMder);
    FCIIC_HWA_SetMCFGR0(pFciic, u32TempMcfgr0);
    FCIIC_HWA_SetMCFGR1(pFciic, u32TempMcfgr1);
    FCIIC_HWA_SetMCFGR2(pFciic, u32TempMcfgr2);
    FCIIC_HWA_SetMCFGR3(pFciic, u32TempMcfgr3);
    FCIIC_HWA_SetMCCR(pFciic, u32TempMccr0);
    FCIIC_HWA_SetMFCR(pFciic, u32TempMFCR);

    FCIIC_HWA_SetMcr(pFciic, u32TempMcr);   /* | FCIIC_MCR_RRF_MASK | FCIIC_MCR_RTF_MASK | FCIIC_MCR_DBGEN_MASK | FCIIC_MCR_RST_MASK; */

    #ifdef FCIIC_INIT_WAITRESET
    u8RetVal = 1;

    while (u8RetVal)
    {
        u8RetVal = (pFciic->MCR & FCIIC_MCR_RST_MASK) >> FCIIC_MCR_RST_SHIFT;
        pFciic->MCR = u32TempMcr;
    }
    #endif
    return 0U;
}



/***************************************************
 * FCIIC_DeInit_Master
 *   @detail: Iic device master mode de-initial
 *
 * param in : u8IicIndex
 * param out: none
 *
 * return   : 0 is ok, others are not ok
 * ************************************************/
static uint8_t FCIIC_DeInit_Master(uint8_t u8IicIndex)
{
    uint32_t u32TempMcr, u32TempMder;

    FCIIC_Type *pFciic;
    pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];


    u32TempMcr = FCIIC_MCR_RRF(0U)    |
                 FCIIC_MCR_RTF(0U)      |
                 FCIIC_MCR_DBGEN(0U)    |
                 FCIIC_MCR_RST(0U)      |
                 FCIIC_MCR_MEN(0U);         /* master enable */


    u32TempMder = FCIIC_MDER_RDDE(0U) |   /* disable receive dma */
                  FCIIC_MDER_TDDE(0U);          /* disable transmit dma */




    FCIIC_HWA_SetMder(pFciic, u32TempMder);

    FCIIC_HWA_SetMcr(pFciic, u32TempMcr);   /* | FCIIC_MCR_RRF_MASK | FCIIC_MCR_RTF_MASK | FCIIC_MCR_DBGEN_MASK | FCIIC_MCR_RST_MASK; */


    return 0U;
}



/***************************************************
 * FCIIC_Init_Slave
 *   @detail: Iic device master mode initial
 *
 * param in : u8IicIndex
 * param out: none
 *
 * return   : 0 is ok, others are not ok
 * ************************************************/
static uint8_t FCIIC_Init_Slave(uint8_t u8IicIndex, FCIIC_InitType *pInitCfg)
{
    uint32_t u32TempScr, u32TempSder, u32TempScfgr1, u32TempScfgr2, u32TempSamr;

    FCIIC_Type *pFciic;

    pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];


    u32TempScr = FCIIC_SCR_FILTEN(0U)    |
                 FCIIC_SCR_RST(0U)      |
                 FCIIC_SCR_SEN(1U);         /* slave enable */


    u32TempSder = FCIIC_SDER_AVDE(pInitCfg->bEnDma) |
                  FCIIC_SDER_RDDE(pInitCfg->bEnDma) |   /* enable receive dma */
                  FCIIC_SDER_TDDE(pInitCfg->bEnDma);       /* enable transmit dma */



    u32TempScfgr1 = FCIIC_SCFGR1_ADDRCFG(0U)  |   /* Address Configuration, 7bit */
                    FCIIC_SCFGR1_HSMEN(0U)       |
                    FCIIC_SCFGR1_IGNACK(1U)       |
                    FCIIC_SCFGR1_RXCFG(0U)     |
                    FCIIC_SCFGR1_TXCFG(0U)     |
                    FCIIC_SCFGR1_SAEN(0U)     |
                    FCIIC_SCFGR1_GCEN(0U)     |
                    FCIIC_SCFGR1_ACKSTALL(0U)     |
                    FCIIC_SCFGR1_TXDSTALL(0U)     |
                    FCIIC_SCFGR1_RXSTALL(0U)     |
                    FCIIC_SCFGR1_ADRSTALL(0U);

    u32TempScfgr2 = FCIIC_SCFGR2_FILTSDA(0U)  |
                    FCIIC_SCFGR2_FILTSCL(0U)       |
                    FCIIC_SCFGR2_DATAVD(0x09U)       |
                    FCIIC_SCFGR2_CLKHOLD(1U);




    u32TempSamr = FCIIC_SAMR_ADDR1(0U) |
                  FCIIC_SAMR_ADDR0(pInitCfg->u8SlaveAddr);



    FCIIC_HWA_SetSDER(pFciic, u32TempSder);
    FCIIC_HWA_SetSCFGR1(pFciic, u32TempScfgr1);
    FCIIC_HWA_SetSCFGR2(pFciic, u32TempScfgr2);
    FCIIC_HWA_SetSAMR(pFciic, u32TempSamr);


    FCIIC_HWA_SetSCR(pFciic, u32TempScr);

    return 0U;
}


/***************************************************
 * FCIIC_DeInit_Slave
 *   @detail: Iic device master mode de-initial
 *
 * param in : pInitCfg, pFciic initial config parameters
 *             structure address
 * param out: none
 *
 * return   : 0 is ok, others are not ok
 * ************************************************/
static uint8_t FCIIC_DeInit_Slave(uint8_t u8IicIndex)
{
    uint32_t u32TempScr, u32TempSder;

    FCIIC_Type *pFciic;

    pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];

    u32TempScr = FCIIC_SCR_FILTEN(0U)    |
                 FCIIC_SCR_RST(0U)      |
                 FCIIC_SCR_SEN(0U);         /* slave enable */


    u32TempSder = FCIIC_SDER_AVDE(0U) |
                  FCIIC_SDER_RDDE(0U) |   /* disable receive dma */
                  FCIIC_SDER_TDDE(0U);       /* disable transmit dma */

    FCIIC_HWA_SetSDER(pFciic, u32TempSder);


    FCIIC_HWA_SetSCR(pFciic, u32TempScr);

    return 0U;

}


/* ################################################################################## */
/* ################################ Global Functions ################################ */



/**
 * \brief This Function is used to initial IIC instance
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pInitCfg is the structure address of IIC initial configuration parameters, and it contains IIC instance
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Init(uint8_t u8IicIndex, FCIIC_InitType *pInitCfg)
{
    /* master mode */
    if (pInitCfg->bMasterMode != 0U)
    {
        FCIIC_Init_Master(u8IicIndex, pInitCfg);
        #ifdef FCIIC_RX_ALL_POLLING
        s_aFCIIC_IicMasterUsed[u8IicIndex] = 1U;
        s_aFCIIC_IicSlaveUsed[u8IicIndex] = 0U;
        #endif
    }
    else /* slave mode */
    {
        FCIIC_Init_Slave(u8IicIndex, pInitCfg);
        #ifdef FCIIC_RX_ALL_POLLING
        s_aFCIIC_IicMasterUsed[u8IicIndex] = 0U;
        s_aFCIIC_IicSlaveUsed[u8IicIndex] = 1U;
        #endif
    }
    #if (defined(__ICCARM__))
    u8IicIndex = u8IicIndex;
    #elif defined __GNUC__
    (void)u8IicIndex;
    #endif

    return 0U;
}


/**
 * \brief This Function is used to de-initial IIC instance
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pInitCfg is the structure address of IIC initial configuration parameters, bMaster should be set
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_DeInit(uint8_t u8IicIndex, FCIIC_InitType *pInitCfg)
{

    /* master mode */
    if (pInitCfg->bMasterMode != 0U)
    {
        FCIIC_DeInit_Master(u8IicIndex);
        #ifdef FCIIC_RX_ALL_POLLING
        s_aFCIIC_IicMasterUsed[u8IicIndex] = 0U;
        s_aFCIIC_IicSlaveUsed[u8IicIndex] = 0U;
        #endif
    }
    else /* slave mode */
    {
        FCIIC_DeInit_Slave(u8IicIndex);
        #ifdef FCIIC_RX_ALL_POLLING
        s_aFCIIC_IicMasterUsed[u8IicIndex] = 0U;
        s_aFCIIC_IicSlaveUsed[u8IicIndex] = 0U;
        #endif
    }


    #if (defined(__ICCARM__))
    u8IicIndex = u8IicIndex;
    #elif defined __GNUC__
    (void)u8IicIndex;
    #endif

    return 0U;
}


/**
 * \brief This Function is used to configure IIC master interrupt
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pIntCfg contains IIC instance and interrupt callback functions
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Master_SetInterrupt(uint8_t u8IicIndex, FCIIC_InterruptType *pIntCfg)
{
    FCIIC_Type  *pFciic;

    pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];

    if ((pIntCfg->bEnErrorInterrupt != 0U) || (pIntCfg->bEnRxInterrupt != 0U))
    {
        /* enable global interrupt for pFciic */
        IntMgr_EnableInterrupt((IRQn_Type)((uint8_t)((uint8_t)FCIIC0_IRQn + u8IicIndex)));
        /* IntMag_ReplaceHandler(FCIIC0_IRQn+u8IicIndex,u8IicIndex==0?FCIIC0_IRQHandler:FCIIC1_IRQHandler); */
    }

    if (pIntCfg->bEnErrorInterrupt != 0U)
    {
        FCIIC_Master_HWA_EnableErrorInterrupt(pFciic);
        s_aFCIIC_ErrorNotifyTable[u8IicIndex] = pIntCfg->pErrorNotify;
    }

    if (pIntCfg->bEnRxInterrupt != 0U)
    {
        /* pFciic->MIER |= FCIIC_MIER_RDIE_MASK; */
        FCIIC_Master_HWA_EnableReceiveInterrupt(pFciic);
        s_aFCIIC_RxNotifyTable[u8IicIndex] = pIntCfg->pRxNotify;
    }

    return 0U;
}




/**
 * \brief This Function is used to transmit data in master mode
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pTxData contains IIC instance and buffer address
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Master_Transmit(uint8_t u8IicIndex, FCIIC_TxDataType *pTxData)
{
    uint8_t    u8RetVal;
    FCIIC_Type *pFciic;

    pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];

    /* clear error flag */
    /* CheckAndClear(pFciic); */

    /* check tx data flag */
    u8RetVal = FCIIC_Master_HWA_GetStatus(pFciic, FCIIC_MSR_TDF_STATUS);

    /* pFciic->MSR |= FCIIC_MSR_FEF_MASK; */ /* clear fifo error error */
    if (u8RetVal == 1U)
    {
        FCIIC_Master_HWA_Transmit(pFciic, pTxData->eCmd, pTxData->u8Data);
    }

    return (uint8_t)(1U >> u8RetVal);
}



/**
 * \brief This Function is used to get master status
 *
 * \param u8IicIndex is IIC instance
 * \param eStatus is status type enumeration
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Master_GetStatus(uint8_t u8IicIndex, FCIIC_MasterStatusType eStatus)
{
    FCIIC_Type *pFciic  = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];
    return (uint8_t)(1U >> FCIIC_Master_HWA_GetStatus(pFciic, eStatus));
}


/**
 * \brief This Function is used to receive data when polling (not used when rx interrupt enabled) in master mode
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pRxData contains IIC instance
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Master_Receive(uint8_t u8IicIndex, FCIIC_RxDataType *pRxData)
{
    FCIIC_Type  *pFciic;
    uint8_t     u8RetVal;

    pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];

    /* CheckAndClear(pFciic); */


    /* check receive flag */
    u8RetVal = FCIIC_Master_HWA_GetStatus(pFciic, FCIIC_MSR_RDF_STATUS);

    /* u8RetVal = (pFciic->MRDR & FCIIC_MRDR_RXEMPTY_MASK)>>FCIIC_MRDR_RXEMPTY_SHIFT; */

    if (u8RetVal == 1U)
    {
        /* copy data */
        pRxData->u8Data = FCIIC_Master_HWA_Receive(pFciic);
    }

    return (uint8_t)(1U >> u8RetVal);
}

/**
 * \brief This Function is used to get master error value
 *
 * \param u8IicIndex Iic Index, 0,1
 * \return error value
 */
uint32_t FCIIC_Master_GetError(uint8_t u8IicIndex)
{
    FCIIC_Type  *pFciic;
    uint32_t     u32RetVal;

    pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];

    /* check receive flag */
    u32RetVal = FCIIC_Master_HWA_GetErrorFlag(pFciic);

    return u32RetVal;
}

/**
 * \brief This Function is used to clear master error value
 *
 * \param u8IicIndex Iic Index, 0,1
 */
void FCIIC_Master_ClrError(uint8_t u8IicIndex)
{
    FCIIC_Type  *pFciic;

    pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];

    /* clear receive flag */
    FCIIC_Master_HWA_ClrErrorFlag(pFciic);

}

/**
 * \brief This Function is used to configure IIC slave interrupt
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pIntCfg contains IIC instance and interrupt callback functions
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Slave_SetInterrupt(uint8_t u8IicIndex, FCIIC_InterruptType *pIntCfg)
{
    FCIIC_Type  *pFciic;

    pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];

    if ((pIntCfg->bEnErrorInterrupt != 0U) || (pIntCfg->bEnRxInterrupt != 0U))
    {
        /* enable global interrupt for pFciic */
        IntMgr_EnableInterrupt((IRQn_Type)((uint8_t)((uint8_t)FCIIC0_IRQn + u8IicIndex)));
        /* IntMag_ReplaceHandler(FCIIC0_IRQn+u8IicIndex,u8IicIndex==0?FCIIC0_IRQHandler:FCIIC1_IRQHandler); */
    }


    if (pIntCfg->bEnErrorInterrupt != 0U)
    {
        FCIIC_Slave_HWA_EnableErrorInterrupt(pFciic);
        s_aFCIIC_ErrorNotifyTable[u8IicIndex] = pIntCfg->pErrorNotify;
    }

    if (pIntCfg->bEnRxInterrupt != 0U)
    {
        FCIIC_Slave_HWA_EnableReceiveInterrupt(pFciic);

        s_aFCIIC_RxNotifyTable[u8IicIndex] = pIntCfg->pRxNotify;
    }

    return 0U;
}


/**
 * \brief This Function is used to transmit data in slave mode
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pTxData contains IIC instance and buffer address
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Slave_Transmit(uint8_t u8IicIndex, FCIIC_TxDataType *pTxData)
{
    #ifdef FCIIC_TX_CHECK
    uint8_t u8RetVal;
    uint32_t u32TryTick;
    uint32_t u32TryCount;
    #endif
    FCIIC_Type *pFciic;

    pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];

    #ifdef FCIIC_TX_CHECK
    /* u8RetVal = (pFciic->SSR & FCIIC_SSR_TDF_MASK)>> FCIIC_SSR_TDF_SHIFT; */

    /* pFciic->SSR |= FCIIC_SSR_TREF_MASK; */ /* clear receive & transmit error error */
    /* if(u8RetVal) */
    {
    #endif
        FCIIC_Slave_HWA_Transmit(pFciic, pTxData->u8Data);
        #ifdef FCIIC_TX_CHECK
        /* after transmit completed, close TE */
        /*         u8RetVal = 0; */
        /*         u32TryCount = 0; */
        /*         while(u8RetVal==0 && u32TryCount++<100) */
        /*         { */
        /*             u8RetVal = (pFciic->SSR & FCIIC_SSR_TDF_MASK)>> FCIIC_SSR_TDF_SHIFT; */
        /*             u32TryTick = 0; */
        /*             while(u32TryTick++<100){} */

        /*         } */
    }
        #endif

    return 0U;
}



/**
 * \brief This Function is used to receive data when polling (not used when rx interrupt enabled) in slave mode
 *
 * \param u8IicIndex Iic Index, 0,1
 * \param pRxData contains IIC instance and buffer address
 * \return 0 is ok, others are not ok
 */
uint8_t FCIIC_Slave_Receive(uint8_t u8IicIndex, FCIIC_RxDataType *pRxData)
{
    FCIIC_Type  *pFciic;
    uint8_t     u8RetVal;

    pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];


    /* check slave receive flag */
    u8RetVal = FCIIC_Slave_HWA_GetStatus(pFciic, FCIIC_SSR_RDF_STATUS);

    /* u8RetVal = (pFciic->MRDR & FCIIC_MRDR_RXEMPTY_MASK)>>FCIIC_MRDR_RXEMPTY_SHIFT; */

    if (u8RetVal != 0U)
    {
        /* get received data */
        pRxData->u8Data = FCIIC_Slave_HWA_Receive(pFciic);
    }

    return (uint8_t)(1U >> u8RetVal);
}


/**
 * \brief This Function is used to get slave error value
 *
 * \param u8IicIndex Iic Index, 0,1
 * \return error value
 */
uint32_t FCIIC_Slave_GetError(uint8_t u8IicIndex)
{
    FCIIC_Type  *pFciic;
    uint32_t     u32RetVal;

    pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];

    /* check receive flag */
    u32RetVal = FCIIC_Slave_HWA_GetErrorFlag(pFciic);

    return u32RetVal;
}

/**
 * \brief This Function is used to clear slave error value
 *
 * \param u8IicIndex Iic Index, 0,1
 */
void FCIIC_Slave_ClrError(uint8_t u8IicIndex)
{
    FCIIC_Type  *pFciic;

    pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[u8IicIndex];

    /* clear receive flag */
    FCIIC_Slave_HWA_ClrErrorFlag(pFciic);
}


/* ################################################################################## */
/* ############################## Interrupt Services ################################ */


void FCIIC0_IRQHandler(void)
{
    FCIIC_LL_MasterIRQnHandler(0U);
    FCIIC_LL_SlaveIRQnHandler(0U);
}

void FCIIC1_IRQHandler(void)
{
    FCIIC_LL_MasterIRQnHandler(1U);
    FCIIC_LL_SlaveIRQnHandler(1U);
}


