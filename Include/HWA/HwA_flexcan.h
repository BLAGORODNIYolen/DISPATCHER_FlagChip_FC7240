/**
 * @file fc7xxx_driver_flexcan.h
 * @author Flagchip
 * @brief FC7xxx FlexCAN register API
 * @version 0.1.0
 * @date 2024-1-13
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Author           Descriptions
   *   ---------   ----------    ------------     ---------------
   *   0.1.0       2024-1-13    Flagchip0112      First version for FC7240
   ******************************************************************************** */

#ifndef _HWA_FLEXCAN_H_
#define _HWA_FLEXCAN_H_

#include "device_header.h"





/* ################################################################################## */
/* ####################################### Macro #################################### */

/* ****************************** Message Buffer Structure ************************************* */

/* ************************************************ 8bytes data ******************************************************* */
/*         31    30    29    28   27 26 25 24   23   22    21    20   19 18 17 16  15 14 13 12 11 10 9 8 7 6 5 4 3 2 1  */
/* 0x00  | EDL | BRS | ESI |    |    CODE     |    | SRR | IDE | RTR |    DLC     |          TIME STAMP               | */
/* 0x04  |       PRIO      |         ID (STD/EXT high 11bits)              |           ID (EXT low 18bits)            | */
/* 0x08  |    Data Byte 0                     |     Data Byte 1                   |     Data Byte 2     | Data Byte 3 | */
/* 0x0C  |    Data Byte 4                     |     Data Byte 5                   |     Data Byte 6     | Data Byte 7 | */


/* ************************************************ 16bytes data ****************************************************** */
/*         31    30    29    28   27 26 25 24   23   22    21    20   19 18 17 16  15 14 13 12 11 10 9 8 7 6 5 4 3 2 1  */
/* 0x00  | EDL | BRS | ESI |    |    CODE     |    | SRR | IDE | RTR |    DLC     |          TIME STAMP               | */
/* 0x04  |       PRIO      |         ID (STD/EXT high 11bits)              |           ID (EXT low 18bits)            | */
/* 0x08  |    Data Byte 0                     |     Data Byte 1                   |     Data Byte 2     | Data Byte 3 | */
/* 0x0C  |    Data Byte 4                     |     Data Byte 5                   |     Data Byte 6     | Data Byte 7 | */
/*                                        ................................                                              */
/* 0x1C  |    Data Byte 12                    |     Data Byte 13                  |     Data Byte 14    | Data Byte 15| */


/* ************************************************ 32bytes data ****************************************************** */
/*         31    30    29    28   27 26 25 24   23   22    21    20   19 18 17 16  15 14 13 12 11 10 9 8 7 6 5 4 3 2 1  */
/* 0x00  | EDL | BRS | ESI |    |    CODE     |    | SRR | IDE | RTR |    DLC     |          TIME STAMP               | */
/* 0x04  |       PRIO      |         ID (STD/EXT high 11bits)               |           ID (EXT low 18bits)            | */
/* 0x08  |    Data Byte 0                     |     Data Byte 1                   |     Data Byte 2     | Data Byte 3 | */
/* 0x0C  |    Data Byte 4                     |     Data Byte 5                   |     Data Byte 6     | Data Byte 7 | */
/*                                        ................................                                              */
/* 0x30  |    Data Byte 28                    |     Data Byte 29                  |     Data Byte 30    | Data Byte 31| */


/* ************************************************ 64bytes data ****************************************************** */
/*         31    30    29    28   27 26 25 24   23   22    21    20   19 18 17 16  15 14 13 12 11 10 9 8 7 6 5 4 3 2 1  */
/* 0x00  | EDL | BRS | ESI |    |    CODE     |    | SRR | IDE | RTR |    DLC     |          TIME STAMP               | */
/* 0x04  |       PRIO      |         ID (STD/EXT high 11bits)              |           ID (EXT low 18bits)            | */
/* 0x08  |    Data Byte 0                     |     Data Byte 1                   |     Data Byte 2     | Data Byte 3 | */
/* 0x0C  |    Data Byte 4                     |     Data Byte 5                   |     Data Byte 6     | Data Byte 7 | */
/*                                        ................................                                              */
/* 0x44  |    Data Byte 60                    |     Data Byte 61                  |     Data Byte 62    | Data Byte 63| */


/**
 * @addtogroup HwA_flexcan
 * @{
 */


/** Register address with offset */
#define FLEXCAN_REGISTER_WITHOFFSET(reg,offset1,offset2)                ((uint32_t)(reg)+(uint32_t)(offset1)+(uint32_t)(offset2))
/** Get register value */
#define FLEXCAN_REG32_CONTENT(reg)                                        (*((uint32_t*)(reg)))




/** U32 value around */
#define FLEXCAN_U32MACRO(var)                                           ((uint32_t)(var))
#define FLEXCAN_U32SHIFT(var,mask,shift)                                ((uint32_t)((((uint32_t)(var))&(mask))<<(shift)))
#define FLEXCAN_U32NOTSHIFT(mask,shift)                                 ((uint32_t)(~(((uint32_t)(mask))<<(shift))))


/* legacy message buffer */

/** Legacy/EnHanced Message Buffer Header */
#define FLEXCAN_MB_HEADER_BYTELEN                                       8UL
/** Legacy Message Buffer Address */
#define FLEXCAN_MB_ADDR(mbOffset, mbIndex, dataLen)                     FLEXCAN_U32MACRO(FLEXCAN_U32MACRO(mbOffset)+FLEXCAN_U32MACRO(mbIndex)*(FLEXCAN_U32MACRO(dataLen)+FLEXCAN_MB_HEADER_BYTELEN))


/** Legacy Message Buffer word n Address */
#define FLEXCAN_MB_WORDN_ADDR(mbOffset, mbIndex, dataLen, offset)       (FLEXCAN_MB_ADDR((mbOffset), (mbIndex), (dataLen))+FLEXCAN_U32MACRO(offset))

/** Legacy Message Buffer Data Address */
/* #define FLEXCAN_MB_DATA_ADDR_GET(mbOffset, mbIndex, dataLen)            (FLEXCAN_MB_WORDN_ADDR((mbOffset), (mbIndex), (dataLen),2U)) */

/** Legacy Message Buffer EDL Get */
#define FLEXCAN_MB_EDL_GET(edlAddr)                                     ((FLEXCAN_REG32_CONTENT(edlAddr)>>31)&0x01U)
/** Legacy Message Buffer EDL Clear */
#define FLEXCAN_MB_EDL_CLR(edlAddr)                                     (FLEXCAN_REG32_CONTENT(edlAddr) &= FLEXCAN_U32NOTSHIFT(0x01U,31))
/** Legacy Message Buffer EDL Attach */
#define FLEXCAN_MB_EDL_ATTACH(edlAddr,var)                              (FLEXCAN_REG32_CONTENT(edlAddr) |= FLEXCAN_U32SHIFT(var,0x01U,31))
/** Legacy Message Buffer EDL Set */
#define FLEXCAN_MB_EDL_SET(edlAddr,var)                                 FLEXCAN_MB_EDL_CLR(edlAddr); FLEXCAN_MB_EDL_ATTACH(edlAddr,var)


/** Legacy Message Buffer BRS Get */
#define FLEXCAN_MB_BRS_GET(brsAddr)                                     (((FLEXCAN_REG32_CONTENT(brsAddr))>>30)&0x01U)
/** Legacy Message Buffer BRS Clear */
#define FLEXCAN_MB_BRS_CLR(brsAddr)                                     (FLEXCAN_REG32_CONTENT(brsAddr) &= FLEXCAN_U32NOTSHIFT(0x01U,30))
/** Legacy Message Buffer BRS Attach */
#define FLEXCAN_MB_BRS_ATTACH(brsAddr,var)                              (FLEXCAN_REG32_CONTENT(brsAddr) |= FLEXCAN_U32SHIFT(var,0x01U,30))
/** Legacy Message Buffer BRS set */
#define FLEXCAN_MB_BRS_SET(brsAddr,var)                                 FLEXCAN_MB_BRS_CLR(brsAddr); FLEXCAN_MB_BRS_ATTACH(brsAddr,var)

/** Legacy Message Buffer ESI Get */
#define FLEXCAN_MB_ESI_GET(esiAddr)                                     (((FLEXCAN_REG32_CONTENT(esiAddr))>>29)&0x01U)
/** Legacy Message Buffer ESI Clear */
#define FLEXCAN_MB_ESI_CLR(esiAddr)                                     (FLEXCAN_REG32_CONTENT(esiAddr) &= FLEXCAN_U32NOTSHIFT(0x01U,29))
/** Legacy Message Buffer ESI Attach */
#define FLEXCAN_MB_ESI_ATTACH(esiAddr,var)                              (FLEXCAN_REG32_CONTENT(esiAddr) |= FLEXCAN_U32SHIFT(var,0x01U,29))
/** Legacy Message Buffer ESI Set */
#define FLEXCAN_MB_ESI_SET(esiAddr,var)                                 FLEXCAN_MB_ESI_CLR(esiAddr);  FLEXCAN_MB_ESI_ATTACH(esiAddr,var)

/** Legacy Message Buffer CODE Get */
#define FLEXCAN_MB_CODE_GET(codeAddr)                                   (((FLEXCAN_REG32_CONTENT(codeAddr))>>24)&0x0FU)
/** Legacy Message Buffer CODE Clear */
#define FLEXCAN_MB_CODE_CLR(codeAddr)                                   (FLEXCAN_REG32_CONTENT(codeAddr) &= FLEXCAN_U32NOTSHIFT(0x0FU,24))
/** Legacy Message Buffer CODE Attach */
#define FLEXCAN_MB_CODE_ATTACH(codeAddr,var)                            (FLEXCAN_REG32_CONTENT(codeAddr) |= FLEXCAN_U32SHIFT(var,0x0FU,24))
/** Legacy Message Buffer CODE set */
#define FLEXCAN_MB_CODE_SET(codeAddr,var)                               FLEXCAN_MB_CODE_CLR(codeAddr); FLEXCAN_MB_CODE_ATTACH(codeAddr,var)


/** Legacy Message Buffer SRR Get */
#define FLEXCAN_MB_SRR_GET(srrAddr)                                     (((FLEXCAN_REG32_CONTENT(srrAddr)) >>22)&0x01U)
/** Legacy Message Buffer SRR Clear */
#define FLEXCAN_MB_SRR_CLR(srrAddr)                                     (FLEXCAN_REG32_CONTENT(srrAddr) &= FLEXCAN_U32NOTSHIFT(0x01U,22))
/** Legacy Message Buffer SRR Attach */
#define FLEXCAN_MB_SRR_ATTACH(srrAddr,var)                              (FLEXCAN_REG32_CONTENT(srrAddr) |= FLEXCAN_U32SHIFT(var,0x01U,22))
/** Legacy Message Buffer SRR set */
#define FLEXCAN_MB_SRR_SET(srrAddr,var)                                 FLEXCAN_MB_SRR_CLR(srrAddr); FLEXCAN_MB_SRR_ATTACH(srrAddr,var)

/** Legacy Message Buffer IDE Get */
#define FLEXCAN_MB_IDE_GET(ideAddr)                                     (((FLEXCAN_REG32_CONTENT(ideAddr))>>21)&0x01U)
/** Legacy Message Buffer IDE Clear */
#define FLEXCAN_MB_IDE_CLR(ideAddr)                                     (FLEXCAN_REG32_CONTENT(ideAddr) &= FLEXCAN_U32NOTSHIFT(0x01U,21))
/** Legacy Message Buffer IDE Attach */
#define FLEXCAN_MB_IDE_ATTACH(ideAddr,var)                              (FLEXCAN_REG32_CONTENT(ideAddr) |= FLEXCAN_U32SHIFT(var,0x01U,21))
/** Legacy Message Buffer IDE set */
#define FLEXCAN_MB_IDE_SET(ideAddr,var)                                 FLEXCAN_MB_IDE_CLR(ideAddr); FLEXCAN_MB_IDE_ATTACH(ideAddr,var)


/** Legacy Message Buffer RTR Get */
#define FLEXCAN_MB_RTR_GET(rtrAddr)                                     (((FLEXCAN_REG32_CONTENT(rtrAddr))>>20)&0x01U)
/** Legacy Message Buffer RTR Clear */
#define FLEXCAN_MB_RTR_CLR(rtrAddr)                                     (FLEXCAN_REG32_CONTENT(rtrAddr) &= FLEXCAN_U32NOTSHIFT(0x01U,20))
/** Legacy Message Buffer RTR Attach */
#define FLEXCAN_MB_RTR_ATTACH(rtrAddr,var)                              (FLEXCAN_REG32_CONTENT(rtrAddr) |= FLEXCAN_U32SHIFT(var,0x01U,20))
/** Legacy Message Buffer RTR set */
#define FLEXCAN_MB_RTR_SET(rtrAddr,var)                                 FLEXCAN_MB_RTR_CLR(rtrAddr); FLEXCAN_MB_RTR_ATTACH(rtrAddr,var)

/** Legacy Message Buffer DLC Get */
#define FLEXCAN_MB_DLC_GET(dlcAddr)                                     (((FLEXCAN_REG32_CONTENT(dlcAddr))>>16)&0x0FU)
/** Legacy Message Buffer DLC Clear */
#define FLEXCAN_MB_DLC_CLR(dlcAddr)                                     (FLEXCAN_REG32_CONTENT(dlcAddr) &= FLEXCAN_U32NOTSHIFT(0x0FU,16))
/** Legacy Message Buffer DLC Attach */
#define FLEXCAN_MB_DLC_ATTACH(dlcAddr,var)                              (FLEXCAN_REG32_CONTENT(dlcAddr) |= FLEXCAN_U32SHIFT(var,0x0FU,16))
/** Legacy Message Buffer DLC Set */
#define FLEXCAN_MB_DLC_SET(dlcAddr,var)                                 FLEXCAN_MB_DLC_CLR(dlcAddr); FLEXCAN_MB_DLC_ATTACH(dlcAddr,var)

/** Legacy Message Buffer TIME STAMP Get */
#define FLEXCAN_MB_TIMESTAMP_GET(timestampAddr)                         (FLEXCAN_REG32_CONTENT(timestampAddr)&0xFFFFU)
/** Legacy Message Buffer TIME STAMP Clear */
#define FLEXCAN_MB_TIMESTAMP_CLR(timestampAddr)                         (FLEXCAN_REG32_CONTENT(timestampAddr) &= FLEXCAN_U32NOTSHIFT(0xFFFFU,0))
/** Legacy Message Buffer TIME STAMP Attach */
#define FLEXCAN_MB_TIMESTAMP_ATTACH(timestampAddr,var)                  (FLEXCAN_REG32_CONTENT(timestampAddr) |= FLEXCAN_U32SHIFT(var,0xFFFFU,0))
/** Legacy Message Buffer TIME STAMP Set */
#define FLEXCAN_MB_TIMESTAMP_SET(timestampAddr,var)                     FLEXCAN_MB_TIMESTAMP_CLR(timestampAddr); FLEXCAN_MB_TIMESTAMP_ATTACH(timestampAddr,var)

/** Legacy Message Buffer PRIO Get */
#define FLEXCAN_MB_PRIO_GET(prioAddr)                                   (((FLEXCAN_REG32_CONTENT(prioAddr))>>29)&0x07U)
/** Legacy Message Buffer PRIO Clear */
#define FLEXCAN_MB_PRIO_CLR(prioAddr)                                   (FLEXCAN_REG32_CONTENT(prioAddr) &= FLEXCAN_U32NOTSHIFT(0x07U,29))
/** Legacy Message Buffer PRIO Attach */
#define FLEXCAN_MB_PRIO_ATTACH(prioAddr,var)                            (FLEXCAN_REG32_CONTENT(prioAddr) |= FLEXCAN_U32SHIFT(var,0x07U,29))
/** Legacy Message Buffer PRIO Set */
#define FLEXCAN_MB_PRIO_SET(prioAddr,var)                               FLEXCAN_MB_PRIO_CLR(prioAddr); FLEXCAN_MB_PRIO_ATTACH(prioAddr,var)

/** Legacy Message Buffer STD ID Get */
#define FLEXCAN_MB_STDID_GET(stdidAddr)                                 (((FLEXCAN_REG32_CONTENT(stdidAddr))>>18)&0x7FFU)
/** Legacy Message Buffer STD ID CLR */
#define FLEXCAN_MB_STDID_CLR(stdidAddr)                                 (FLEXCAN_REG32_CONTENT(stdidAddr) &= FLEXCAN_U32NOTSHIFT(0x7FFU,18))
/** Legacy Message Buffer STD ID Attach */
#define FLEXCAN_MB_STDID_ATTACH(stdidAddr,var)                          (FLEXCAN_REG32_CONTENT(stdidAddr) |= FLEXCAN_U32SHIFT(var,0x7FFU,18))
/** Legacy Message Buffer STD ID set */
#define FLEXCAN_MB_STDID_SET(stdidAddr,var)                             FLEXCAN_MB_STDID_CLR(stdidAddr); FLEXCAN_MB_STDID_ATTACH(stdidAddr,var)

/** Legacy Message Buffer EXT ID Get */
#define FLEXCAN_MB_EXTID_GET(extidAddr)                                 ((FLEXCAN_REG32_CONTENT(extidAddr))&0x1FFFFFFF)
/** Legacy Message Buffer EXT ID Clear */
#define FLEXCAN_MB_EXTID_CLR(extidAddr)                                 (FLEXCAN_REG32_CONTENT(extidAddr) &= FLEXCAN_U32NOTSHIFT(0x1FFFFFFF,0))
/** Legacy Message Buffer EXT ID Attach */
#define FLEXCAN_MB_EXTID_ATTACH(extidAddr,var)                          (FLEXCAN_REG32_CONTENT(extidAddr) |= FLEXCAN_U32SHIFT(var,0x1FFFFFFF,0))
/** Legacy Message Buffer EXT ID set */
#define FLEXCAN_MB_EXTID_SET(extidAddr,var)                             FLEXCAN_MB_EXTID_CLR(extidAddr); FLEXCAN_MB_EXTID_ATTACH(extidAddr,var)

/* enhanced fifo message buffer */

/** Enhanced FIFO Message Buffer EDL Get */
#define FLEXCAN_EFIFOMB_EDL_GET()                                     ((pCan->ERX_FIFO[0U]>>31)&0x01U)

/** Enhanced FIFO Message Buffer BRS Get */
#define FLEXCAN_EFIFOMB_BRS_GET()                                     ((pCan->ERX_FIFO[0U]>>30)&0x01U)

/** Enhanced FIFO Message Buffer ESI Get */
#define FLEXCAN_EFIFOMB_ESI_GET()                                     ((pCan->ERX_FIFO[0U]>>29)&0x01U)

/** Enhanced FIFO Message Buffer SRR Get */
#define FLEXCAN_EFIFOMB_SRR_GET()                                     ((pCan->ERX_FIFO[0U] >>22)&0x01U)

/** Enhanced FIFO Message Buffer IDE Get */
#define FLEXCAN_EFIFOMB_IDE_GET()                                     ((pCan->ERX_FIFO[0U]>>21)&0x01U)

/** Enhanced FIFO Message Buffer RTR Get */
#define FLEXCAN_EFIFOMB_RTR_GET()                                     ((pCan->ERX_FIFO[0U]>>20)&0x01U)

/** Enhanced FIFO Message Buffer DLC Get */
#define FLEXCAN_EFIFOMB_DLC_GET()                                     ((pCan->ERX_FIFO[0U]>>16)&0x0FU)

/** Enhanced FIFO Message Buffer TIME STAMP Get */
#define FLEXCAN_EFIFOMB_TIMESTAMP_GET()                               (pCan->ERX_FIFO[0U]&0xFFU)

/** Enhanced FIFO Message Buffer STD ID Get */
#define FLEXCAN_EFIFOMB_STDID_GET()                                   ((pCan->ERX_FIFO[1U]>>18)&0x7FFU)

/** Enhanced FIFO Message Buffer EXT ID Get */
#define FLEXCAN_EFIFOMB_EXTID_GET()                                   (pCan->ERX_FIFO[1U]&0x1FFFFFFF)

/** Enhanced FIFO Message Buffer Data Get */
#define FLEXCAN_EFIFOMB_DATAADDR_GET(wordIndex)                       (&(pCan->ERX_FIFO[2U+(wordIndex)]))

/** Enhanced FIFO Message Buffer IDHIT Get */
#define FLEXCAN_EFIFOMB_IDHIT_GET(dataWordLen)                        ((pCan->ERX_FIFO[2U+(dataWordLen)])&0x1FFU)

/** Enhanced FIFO Message Buffer HR Time Stamp Get */
#define FLEXCAN_EFIFOMB_HRTIMESTAMP_GET(dataWordLen)                  (pCan->ERX_FIFO[3U+(dataWordLen)])

/* enhanced fifo message buffer from user buffer*/

/** Enhanced FIFO Message Buffer EDL Get */
#define FLEXCAN_EFIFOMB_EDL_GET_FROM_BUFFER(Addr)                                     ((((uint32_t*)Addr)[0U]>>31)&0x01U)

/** Enhanced FIFO Message Buffer BRS Get */
#define FLEXCAN_EFIFOMB_BRS_GET_FROM_BUFFER(Addr)                                     ((((uint32_t*)Addr)[0U]>>30)&0x01U)

/** Enhanced FIFO Message Buffer ESI Get */
#define FLEXCAN_EFIFOMB_ESI_GET_FROM_BUFFER(Addr)                                     ((((uint32_t*)Addr)[0U]>>29)&0x01U)

/** Enhanced FIFO Message Buffer SRR Get */
#define FLEXCAN_EFIFOMB_SRR_GET_FROM_BUFFER(Addr)                                     ((((uint32_t*)Addr)[0U] >>22)&0x01U)

/** Enhanced FIFO Message Buffer IDE Get */
#define FLEXCAN_EFIFOMB_IDE_GET_FROM_BUFFER(Addr)                                     ((((uint32_t*)Addr)[0U]>>21)&0x01U)

/** Enhanced FIFO Message Buffer RTR Get */
#define FLEXCAN_EFIFOMB_RTR_GET_FROM_BUFFER(Addr)                                     ((((uint32_t*)Addr)[0U]>>20)&0x01U)

/** Enhanced FIFO Message Buffer DLC Get */
#define FLEXCAN_EFIFOMB_DLC_GET_FROM_BUFFER(Addr)                                     ((((uint32_t*)Addr)[0U]>>16)&0x0FU)

/** Enhanced FIFO Message Buffer TIME STAMP Get */
#define FLEXCAN_EFIFOMB_TIMESTAMP_GET_FROM_BUFFER(Addr)                               (((uint32_t*)Addr)[0U]&0xFFU)

/** Enhanced FIFO Message Buffer STD ID Get */
#define FLEXCAN_EFIFOMB_STDID_GET_FROM_BUFFER(Addr)                                   ((((uint32_t*)Addr)[1U]>>18)&0x7FFU)

/** Enhanced FIFO Message Buffer EXT ID Get */
#define FLEXCAN_EFIFOMB_EXTID_GET_FROM_BUFFER(Addr)                                   (((uint32_t*)Addr)[1U]&0x1FFFFFFF)

/** Enhanced FIFO Message Buffer Data Get */
#define FLEXCAN_EFIFOMB_DATAADDR_GET_FROM_BUFFER(Addr, wordIndex)                      (&(((uint32_t*)Addr)[2U+(wordIndex)]))

/** Enhanced FIFO Message Buffer IDHIT Get */
#define FLEXCAN_EFIFOMB_IDHIT_GET_FROM_BUFFER(Addr, dataWordLen)                       ((((uint32_t*)Addr)[2U+(dataWordLen)])&0x1FFU)

/** Enhanced FIFO Message Buffer HR Time Stamp Get */
#define FLEXCAN_EFIFOMB_HRTIMESTAMP_GET_FROM_BUFFER(Addr, dataWordLen)                 (((uint32_t*)Addr)[3U+(dataWordLen)])

/* ################################################################################## */
/* ################################### Type define ################################## */

/**
 * \brief  FLEXCAN Clock Source Select Enumeration
 *
 */
typedef enum
{
    FLEXCAN_CLOCK_FUNCTION = 0x00U,/**< FLEXCAN_CLOCK_FUNCTION  clock from asynchronous clock */
    FLEXCAN_CLOCK_MODULE = 0x01U   /**< FLEXCAN_CLOCK_MODULE  clock from peripheral clock     */
} FLEXCAN_ClockSrcType;



/* ################################################################################## */
/* ################################## Local Inline ################################## */



/**
 * \brief Set Module Disable
 *
 * \param pCan FLEXCAN instance value
 * \param bDisable set whether disable
 */
LOCAL_INLINE void FLEXCAN_HWA_SetMcrDisable(FLEXCAN_Type *const pCan, uint8_t bDisable)
{
    if (bDisable == TRUE)
    {
        pCan->MCR |= FLEXCAN_MCR_MDIS_MASK;         /* bitMDIS=1: Disable module before selecting clock     */
    }
    else
    {
        pCan->MCR &= ~FLEXCAN_MCR_MDIS_MASK;
    }
}

/**
 * \brief Set Module Freeze
 *
 * \param pCan FLEXCAN instance value
 * \param bFreeze set whether freeze
 */
LOCAL_INLINE void FLEXCAN_HWA_SetMcrFreeze(FLEXCAN_Type *const pCan, uint8_t bFreeze)
{
    if (bFreeze == TRUE)
    {
        pCan->MCR |= FLEXCAN_MCR_FRZ_MASK;         /* bitMDIS=1: Disable module before selecting clock     */
    }
    else
    {
        pCan->MCR &= ~FLEXCAN_MCR_FRZ_MASK;
    }
}


/**
 * \brief Set Module Halt and Freeze
 *
 * \param pCan FLEXCAN instance value
 * \param bFreeze set whether freeze
 */
LOCAL_INLINE void FLEXCAN_HWA_SetHaltFreeze(FLEXCAN_Type *const pCan)
{
    pCan->MCR |= FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK;
}

/**
 * \brief Wait FLEXCAN Module Enter Freezen mode
 *
 * \param pCan FLEXCAN instance value
 * \param u32TimeoutTick Timeout tick
 * \return 0U is really in freezen mode
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_WaitMcrFreezen(FLEXCAN_Type *const pCan, uint32_t u32TimeoutTick)
{
    /* wait for bitFRZACK=1 on freeze mode entry/exit */
    while ( (!((pCan->MCR & FLEXCAN_MCR_FRZACK_MASK) >> FLEXCAN_MCR_FRZACK_SHIFT))  && (u32TimeoutTick-->0U) )
    {

    }

    return (u32TimeoutTick==0U);
}

/**
 * \brief Wait FLEXCAN Module Exit Freezen mode
 *
 * \param pCan FLEXCAN instance value
 * \param u32TimeoutTick Timeout tick
 * \return 1U is really in freezen mode
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_WaitMcrExitFreezen(FLEXCAN_Type *const pCan, uint32_t u32TimeoutTick)
{
    while ( ((pCan->MCR & FLEXCAN_MCR_FRZACK_MASK) >> FLEXCAN_MCR_FRZACK_SHIFT)   && (u32TimeoutTick-->0U) )
    {}
    /*  wait for bitFRZACK to clear (not in freeze mode) */

    return (u32TimeoutTick==0U);
}

/**
 * \brief Wait FLEXCAN Module Ready
 *
 * \param pCan FLEXCAN instance value
 * \param u32TimeoutTick Timeout tick
 * \return 1U is really ready
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_WaitMcrReady(FLEXCAN_Type *const pCan, uint32_t u32TimeoutTick)
{
    while ( ((pCan->MCR & FLEXCAN_MCR_NOTRDY_MASK) >> FLEXCAN_MCR_NOTRDY_SHIFT)    && (u32TimeoutTick-->0U) )
    {}
    /*  wait for bitNOTRDY to clear (module ready) */

    return (u32TimeoutTick==0U);
}

/**
 * \brief Wait FLEXCAN Module Not Ready
 *
 * \param pCan FLEXCAN instance value
 * \param u32TimeoutTick Timeout tick
 * \return 1U is really not ready
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_WaitMcrNoReady(FLEXCAN_Type *const pCan, uint32_t u32TimeoutTick)
{
    while ( (!((pCan->MCR & FLEXCAN_MCR_NOTRDY_MASK) >> FLEXCAN_MCR_NOTRDY_SHIFT))  && (u32TimeoutTick-->0U) )
    {}
    /*  wait for bitNOTRDY to set (module ready) */

    return (u32TimeoutTick==0U);
}

/**
 * \brief Set FLEXCAN MCR value
 *
 * \param pCan FLEXCAN instance value
 * \param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetMCR(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->MCR = u32Value;
}

/**
 * \brief Get FLEXCAN MCR value
 *
 * \param pCan FLEXCAN instance value
 * \return MCR value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetMCR(FLEXCAN_Type *const pCan)
{
    return (uint32_t)pCan->MCR;
}

/**
 * \brief Attach FLEXCAN MCR value
 *
 * \param pCan FLEXCAN instance value
 * \param u32Value attached value
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachMCR(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->MCR |= u32Value;
}


/**
 * \brief Set FLEXCAN baudrate clock source
 *
 * \param pCan FLEXCAN instance value
 * \param tBaudClk Baudrate clock source
 */
LOCAL_INLINE void FLEXCAN_HWA_SetCtrl1BaudSrc(FLEXCAN_Type *const pCan, FLEXCAN_ClockSrcType tBaudClk)
{
    if (tBaudClk == FLEXCAN_CLOCK_MODULE)
    {
        pCan->CTRL1 |= FLEXCAN_CTRL1_CLKSRC_MASK;
    }
    else
    {
        pCan->CTRL1 &= ~FLEXCAN_CTRL1_CLKSRC_MASK;
    }
}

/**
 * \brief Set FLEXCAN ctrl1 value
 *
 * \param pCan FLEXCAN instance value
 * \param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetCtrl1(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->CTRL1 = u32Value;
}

/**
 * \brief Attach FLEXCAN ctrl1 value
 *
 * \param pCan FLEXCAN instance value
 * \param u32Value attached value
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachCtrl1(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->CTRL1 |= u32Value;
}


/**
 * \brief Get IFLAG1 Flag
 *
 * \param pCan FLEXCAN instance value
 * \return flag1 value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetFlag1(FLEXCAN_Type *const pCan)
{
    return pCan->IFLAG1;
}


/**
 * \brief Clear IFLAG1 Flag
 *
 * \param pCan FLEXCAN instance value
 * \param u32W1cFlag write clear value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetFlag1(FLEXCAN_Type *const pCan, uint32_t u32W1cFlag)
{
    pCan->IFLAG1 = u32W1cFlag;
}

/**
 * \brief Clear Rx Flag and unlock MB
 *
 * \param pCan FLEXCAN instance value
 * \param u32MbIndex Message Buffer Index
 */
LOCAL_INLINE void FLEXCAN_HWA_UnlockMbNoFifoFlag(FLEXCAN_Type *const pCan, uint32_t u32MbIndex)
{
    (void)pCan->TIMER;     /* Read TIMER to unlock message buffers */
    pCan->IFLAG1 = 1U << u32MbIndex;
}

/**
 * \brief Clear MB Flag
 *
 * \param pCan FLEXCAN instance value
 * \param u32MbIndex Message Buffer Index
 */
LOCAL_INLINE void FLEXCAN_HWA_W1cFlag1NoFifoFlag(FLEXCAN_Type *const pCan, uint32_t u32MbIndex)
{
    pCan->IFLAG1 = 1U << u32MbIndex;
}

/**
 * \brief Get MB Flag
 *
 * \param pCan FLEXCAN instance value
 * \param u32MbIndex Message Buffer Index
 * \return flag value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetFlag1NoFifoFlag(FLEXCAN_Type *const pCan, uint32_t u32MbIndex)
{
    return (pCan->IFLAG1 >> u32MbIndex) & 0x01U;
}

/**
 * \brief Get Legacy Fifo Rx Flag
 *
 * \param pCan FLEXCAN instance value
 * \return flag fifo value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetIFLAG1FifoFlag(FLEXCAN_Type *const pCan)
{
    /* IFLAG1[BIT5] (Frames available in Rx FIFO) is asserted when there is at least one frame available to be read from the FIFO. */
    return (pCan->IFLAG1 >> 5) & 0x01U;
}

/**
 * \brief Clear Legacy Fifo Rx Flag
 *
 * \param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_ClearIFLAG1FifoFlag(FLEXCAN_Type *const pCan)
{
    /* Read TIMER to unlock message buffers */
    (void)pCan->TIMER;

    pCan->IFLAG1 = 1U << 5;
}

/**
 * \brief Set special message buffer interrupt
 *
 * \param pCan FLEXCAN instance value
 * \param u32Mask Message Buffer interrupt mask value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetMaskMbInterrupt(FLEXCAN_Type *const pCan, uint32_t u32Mask)
{
    pCan->IMASK1 = u32Mask;
}

/**
 * \brief Attach special message buffer interrupt
 *
 * \param pCan FLEXCAN instance value
 * \param u32MbIndex Message Buffer index
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachMaskMbInterrupt(FLEXCAN_Type *const pCan, uint32_t u32Mask)
{
    pCan->IMASK1 |= u32Mask;
}

/**
 * \brief Attach special message buffer interrupt
 *
 * \param pCan FLEXCAN instance value
 * \param u32MbIndex Message Buffer index
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachMbIndexInterrupt(FLEXCAN_Type *const pCan, uint32_t u32MbIndex)
{
    pCan->IMASK1 |= 1U << u32MbIndex;
}

/**
 * \brief Set Legacy Fifo Rx interrupt
 *
 * \param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetMaskFifoInterrupt(FLEXCAN_Type *const pCan)
{
    pCan->IMASK1 = 1U << 5U;
}

/**
 * \brief Set CTRL2 value
 *
 * \param pCan FLEXCAN instance value
 * \param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetCtrl2(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->CTRL2 = u32Value;
}

/**
 * \brief Attach FLEXCAN ctrl2 value
 *
 * \param pCan FLEXCAN instance value
 * \param u32Value attached value
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachCtrl2(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->CTRL2 |= u32Value;
}

/**
 * \brief Set CBT value
 *
 * \param pCan FLEXCAN instance value
 * \param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetCBT(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->CBT = u32Value;
}

/**
 * \brief Set FDCBT value
 *
 * \param pCan FLEXCAN instance value
 * \param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetFDCBT(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->FDCBT = u32Value;
}

/**
 * \brief Set FDCTRL value
 *
 * \param pCan FLEXCAN instance value
 * \param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetFDCTRL(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->FDCTRL = u32Value;
}


/**
 * \brief This Function is used to get FLEXCAN rx timestamp
 *
 * \param pCan is FLEXCAN instance value
 * \return timestamp Register Value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetTimeStamp(FLEXCAN_Type *const pCan)
{
    return pCan->TIMER;
}

/**
 * \brief This Function is used to get FLEXCAN error
 *
 * \param pCan is FLEXCAN instance value
 * \return ESR1 Register Value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetErrorInfo(FLEXCAN_Type *const pCan)
{
    return pCan->ESR1;
}

/**
 * \brief This Function is used to get FLEXCAN error with interrupt
 *
 * \param pCan is FLEXCAN instance value
 * \return ESR1 Register Value with interrupt mask
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetErrorIntInfo(FLEXCAN_Type *const pCan)
{
	uint32_t u32IntMask = 0U;

	u32IntMask = ((0U == (pCan->CTRL1 & FLEXCAN_CTRL1_ERRMSK_MASK))?0U:FLEXCAN_ESR1_ERRINT_MASK);
	u32IntMask |= ((0U == (pCan->CTRL1 & FLEXCAN_CTRL1_BOFFMSK_MASK))?0U:FLEXCAN_ESR1_BOFFINT_MASK);
	u32IntMask |= ((0U == (pCan->CTRL2 & FLEXCAN_CTRL2_ERRMSK_FAST_MASK))?0U:FLEXCAN_ESR1_ERRINT_FAST_MASK);
	u32IntMask |= ((0U == (pCan->CTRL2 & FLEXCAN_CTRL2_BOFFDONEMSK_MASK))?0U:FLEXCAN_ESR1_BOFFDONEINT_MASK);

    return (pCan->ESR1 & u32IntMask);
}

/**
 * \brief Clear Error Info
 *
 * \param pCan FLEXCAN instance value
 * \param u32ErrorEsr1 is read from FLEXCAN_GetErrorInfo
 */
LOCAL_INLINE void FLEXCAN_HWA_ClrErrorInfo(FLEXCAN_Type *const pCan, uint32_t u32ErrorEsr1)
{
    pCan->ESR1 = u32ErrorEsr1;
}

/**
 * \brief This Function is used to get FLEXCAN error count
 *
 * \param pCan is FLEXCAN instance value
 * \return ECR Register Value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetErrorCount(FLEXCAN_Type *const pCan)
{
    return pCan->ECR;
}

/**
 * \brief Enable FLEXCAN Legacy Fifo
 *
 * \param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_EnableLegacyFifo(FLEXCAN_Type *const pCan)
{
    /* if enable legacy fifo, FD fifo must be disabled */
    pCan->MCR |= FLEXCAN_MCR_RFEN_MASK;       /* set legacy fifo */
}

/**
 * \brief Disable FLEXCAN Legacy Fifo
 *
 * \param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_DisableLegacyFifo(FLEXCAN_Type *const pCan)
{
    /* if enable legacy fifo, FD fifo must be disabled */
    pCan->MCR &= ~FLEXCAN_MCR_RFEN_MASK;      /* clear legacy fifo */
}

/**
 * \brief Enable FLEXCAN FD Fifo
 *
 * \param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_EnableFDFifo(FLEXCAN_Type *const pCan)
{
    /* if enable fd fifo, legacy fifo must be disabled */
    pCan->ERFCR |= FLEXCAN_ERFCR_ERFEN_MASK;  /* set enhanced fifo */
}

/**
 * \brief Disable FLEXCAN FD Fifo
 *
 * \param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_DisableFDFifo(FLEXCAN_Type *const pCan)
{
    /* if enable fd fifo, legacy fifo must be disabled */
    pCan->ERFCR &= ~FLEXCAN_ERFCR_ERFEN_MASK; /* clear enhanced fifo */
}



/**
 * \brief Check FLEXCAN legacy fifo if enabled
 *
 * \param pCan FLEXCAN instance value
 * \return 1 is legacy fifo enabled, 0 is disabled
 */
LOCAL_INLINE uint8_t FLEXCAN_HWA_CheckLegacyFifoEnabled(FLEXCAN_Type *const pCan)
{
    uint8_t  u8RetVal;
    uint32_t u32Value;

    /* get legacy fifo */
    u32Value = (pCan->MCR & FLEXCAN_MCR_RFEN_MASK) >> FLEXCAN_MCR_RFEN_SHIFT;

    u8RetVal = u32Value == 0U ? (uint8_t)0x0U : (uint8_t)0x1U;

    return u8RetVal;
}

/**
 * \brief Check FLEXCAN FD fifo if enabled
 *
 * \param pCan FLEXCAN instance value
 * \return 1 is legacy fifo enabled, 0 is disabled
 */
LOCAL_INLINE uint8_t FLEXCAN_HWA_CheckFdFifoEnabled(FLEXCAN_Type *const pCan)
{
    uint8_t  u8RetVal;
    uint32_t u32Value;
    /* get enhanced fifo */
    u32Value = (pCan->ERFCR & FLEXCAN_ERFCR_ERFEN_MASK) >> FLEXCAN_ERFCR_ERFEN_SHIFT;

    u8RetVal = u32Value == 0U ? (uint8_t)0x0U : (uint8_t)0x1U;

    return u8RetVal;
}

/**
 * \brief Set legacy fifo filter number number
 *
 * \param pCan FLEXCAN instance value
 * \param u32FilterNum is total filter number
 */
LOCAL_INLINE void FLEXCAN_HWA_SetLegacyFifoFilterNum(FLEXCAN_Type *const pCan, uint32_t u32FilterNum)
{
    pCan->CTRL2 &= ~FLEXCAN_CTRL2_RFFN_MASK; /* clear fifo filter number */
    pCan->CTRL2 |= ((u32FilterNum - 1U) << FLEXCAN_CTRL2_RFFN_SHIFT)&FLEXCAN_CTRL2_RFFN_MASK;
}


/**
 * \brief Check FLEXCAN FD enable
 *
 * \param pCan FLEXCAN instance value
 * \return 1 is fd enabled, 0 is disabled
 */
LOCAL_INLINE uint8_t FLEXCAN_HWA_CheckFd(FLEXCAN_Type *const pCan)
{
    uint8_t  u8RetVal;
    uint32_t u32Value;

    /* get fd enable */
    u32Value = (pCan->MCR & FLEXCAN_MCR_FDEN_MASK) >> FLEXCAN_MCR_FDEN_SHIFT;

    u8RetVal = u32Value == 0U ? (uint8_t)0x0U : (uint8_t)0x1U;

    return u8RetVal;
}


/**
 * \brief Set RXIMR for FLEXCAN
 *
 * \param pCan FLEXCAN instance value
 * \param u32MbIndex Message Buffer Index
 * \param u32Mask ID Mask
 */
LOCAL_INLINE void FLEXCAN_HWA_SetIndividualMask(FLEXCAN_Type *const pCan, uint32_t u32MbIndex, uint32_t u32Mask)
{
    pCan->RXIMR[u32MbIndex] = u32Mask;
}

/**
 * \brief Set global mask value
 *
 * \param pCan FLEXCAN instance value
 * \param u32Mask mask value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetGlobalMask(FLEXCAN_Type *const pCan, uint32_t u32Mask)
{
    pCan->RXMGMASK = u32Mask;
}

/**
 * \brief Set rx14 mask value
 *
 * \param pCan FLEXCAN instance value
 * \param u32Mask mask value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetRx14Mask(FLEXCAN_Type *const pCan, uint32_t u32Mask)
{
    pCan->RX14MASK = u32Mask;
}

/**
 * \brief Set rx15 mask value
 *
 * \param pCan FLEXCAN instance value
 * \param u32Mask mask value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetRx15Mask(FLEXCAN_Type *const pCan, uint32_t u32Mask)
{
    pCan->RX15MASK = u32Mask;
}

/**
 * \brief Set value to FLEXCAN RAM
 *
 * \param pCan FLEXCAN instance value
 * \param u32RamIndex RAM index for FLEXCAN
 * \param u32Value written value
 */
LOCAL_INLINE void FLEXCAN_HWA_MbRam(FLEXCAN_Type *const pCan, uint32_t u32RamIndex, uint32_t u32Value)
{
    pCan->RAM[u32RamIndex] = u32Value;
}


/**
 * \brief Set ERFCR value
 *
 * \param pCan FLEXCAN instance value
 * \param u32Value written value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetERFCR(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->ERFCR = u32Value;
}

/**
 * \brief Reset Enhanced FIFO Engine
 *
 * \param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_ERFSRResetEnhancedFifo(FLEXCAN_Type *const pCan)
{
    /* Write one to ERFSR[ERFCLR] to reset Enhanced Rx FIFO engine */
    pCan->ERFSR |= FLEXCAN_ERFSR_ERFCLR_MASK;
}


/**
 * \brief Clear Enhanced Fifo Flag with mask
 *
 * \param pCan FLEXCAN instance value
 * \param u32Shift flag shift
 * \param u32Mask flag mask
 * \return flag value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_ERFSRGetEnhancedFifoFlag(FLEXCAN_Type *const pCan, uint32_t u32Shift, uint32_t u32Mask)
{
    /* Write one clear status */
    return ((pCan->ERFSR & u32Mask) >> u32Shift);
}

/**
 * \brief Clear Enhanced Fifo status
 *
 * \param pCan FLEXCAN instance value
 * \param u32ClearMask clear mask value
 */
LOCAL_INLINE void FLEXCAN_HWA_ERFSRClearEnhancedFifoFlag(FLEXCAN_Type *const pCan, uint32_t u32ClearMask)
{
    /* Write one clear status */
    pCan->ERFSR |= u32ClearMask;
}



/**
 * \brief Set Enhance Fifo interrupt value
 *
 * \param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetERFIERDataInterrupt(FLEXCAN_Type *const pCan)
{
    pCan->ERFIER |= FLEXCAN_ERFIER_ERFDAIE_MASK;
}

/**
 * \brief Set Enhanced Fifo filter value
 *
 * \param pCan FLEXCAN instance value
 * \param u32FilterIndex Filter index
 * \param u32Value filter value
 */
LOCAL_INLINE void FLEXCAN_HWA_EnhancedFifoFilter(FLEXCAN_Type *const pCan, uint32_t u32FilterIndex, uint32_t u32Value)
{
    pCan->ERFFEL[u32FilterIndex] = u32Value;
}

/** @}*/

#endif
