/**
 * @file fc7xxx_driver_erm.c
 * @author Flagchip
 * @brief FC7xxx ERM driver type definition and API
 * @version 0.1.0
 * @date 2024-01-14
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2024-01-14    qxw0100        N/A          First version for FC7240
********************************************************************************/

#include "fc7xxx_driver_erm.h"
#include "fc7xxx_driver_pcc.h"
#include "interrupt_manager.h"

/* ##############################   Local Variables ################################ */
/**
 *  @brief Erm user defined interrupt function
 * */
static ERM_InterruptCallBackType s_pErmNotifyPtr = NULL;

/* ################################################################################## */
/* ########################### Global Prototype Functions ########################### */

void ERM_fault_IRQHandler(void);

/* ################################################################################## */
/* ################################ Local Functions ################################# */
/**
 * @brief Initialize ERM function
 *
 * @param pErmInt_cfg Initialization structure of ERM
 * @return return 0: initialize successful. 1: invalid parameter
 */

ERM_RetType Erm_Init(const ERM_MemorytInitType *pErmInt_cfg)
{
    ERM_RetType eRet = ERM_STATUS_SUCCESS;
    uint32_t u32ErmCrVal = 0U;
    ERM_ClearSRnRegister();

    if (NULL == pErmInt_cfg)
    {
        eRet = ERM_STATUS_PARAM_INVALID;
    }
    else
    {
        if(pErmInt_cfg->u8ErmEnable != 0U)
        {
            if ((uint32_t)pErmInt_cfg->eChannel < 8U)
            {
                u32ErmCrVal |= (uint32_t)((uint32_t)pErmInt_cfg->eInt << (30UL - (uint32)pErmInt_cfg->eChannel*4U));
                ERM_HWA_Set_CRn(0, u32ErmCrVal);
            }
            else if (((uint32_t)pErmInt_cfg->eChannel >= 8U) && ((uint32_t)pErmInt_cfg->eChannel < 16U))
            {
                u32ErmCrVal |= (uint32_t)((uint32_t)pErmInt_cfg->eInt << (62UL - (uint32)pErmInt_cfg->eChannel*4U));
                ERM_HWA_Set_CRn(1, u32ErmCrVal);
            }
            else if (((uint32_t)pErmInt_cfg->eChannel >= 16U) && ((uint32_t)pErmInt_cfg->eChannel < 24U))
            {
                u32ErmCrVal |= (uint32_t)((uint32_t)pErmInt_cfg->eInt << (94UL - (uint32)pErmInt_cfg->eChannel*4U));
                ERM_HWA_Set_CRn(2, u32ErmCrVal);
            }
            else if (((uint32_t)pErmInt_cfg->eChannel >= 24U) && ((uint32_t)pErmInt_cfg->eChannel < 32U))
            {
                u32ErmCrVal |= (uint32_t)((uint32_t)pErmInt_cfg->eInt << (126UL - (uint32)pErmInt_cfg->eChannel*4U));
                ERM_HWA_Set_CRn(3, u32ErmCrVal);
            }
            else
            {
                 eRet = ERM_STATUS_PARAM_INVALID;
            }
            if(eRet == ERM_STATUS_SUCCESS)
            {
                s_pErmNotifyPtr = pErmInt_cfg->pIsrNotify;
            }
        }
        
    }
    return eRet;
}
/**
 * @brief De-initialize ERM function
 * Restore the ERM instance to its reset state
 */
void Erm_DeInit(void)
{
    uint8_t u8loop;
    for (u8loop = 0U; u8loop < 4U; u8loop++)
    {
        ERM_HWA_Set_CRn(u8loop, 0x0U);
        ERM_HWA_Set_SRn(u8loop, 0x0U);
    }
}
/**
 * @brief ERM Clear SR0 register.
 *
 * This function Clear ERM SR0 register.
 */
void ERM_ClearSRnRegister(void)
{
    uint8_t u8loop;
    for (u8loop = 0U; u8loop < 4U; u8loop++)
    {
        ERM_HWA_Set_SRn(u8loop, ERM_SR_MASK);
    }
}

/**
 * @brief ERM read SRn register.
 *
 * This function Clear ERM SRn register.
 * @param u8Index the SRn channel
 */
uint32_t ERM_ReadSRnVal(uint8_t u8Index)
{
    uint32_t u32Val;
    u32Val = ERM_HWA_Get_SRn(u8Index);
    return u32Val;
}
/**
 * @brief ERM clear CRn register.
 *
 * This function Clear ERM CRn register.
 * @param u8Index of the CRn channel
 */
void ERM_ClearCRnVal(uint8_t u8Index)
{
    ERM_HWA_Set_CRn(u8Index, 0UL);
}

/**
 * @brief ERM clear SRn register.
 *
 * This function Clear ERM SR0 register.
 * @param u8Index the SRn channel
 */
uint32_t ERM_ClearSRnVal(uint8_t u8Index)
{
    uint32_t u32Val;
    u32Val = ERM_HWA_Get_SRn(u8Index);
    ERM_HWA_Set_SRn(u8Index, u32Val);
    return u32Val;
}
/**
 * @brief ERM interrupt function
 */
void ERM_fault_IRQHandler(void)
{
    if(s_pErmNotifyPtr != NULL)
    {
        s_pErmNotifyPtr();
    }
}
/**
 * @brief ERM Read EARn address.
 * @param eChannel The channel type
 * @return u32Address The error address
 */
/*
uint32_t ERM_ReadAddress(ERM_channelType eChannel)
{
   uint32_t u32Address = 0U;
   u32Address = ERM_HWA_GetEARn(eChannel);
   return u32Address;
}*/

