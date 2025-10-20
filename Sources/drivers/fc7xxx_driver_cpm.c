 /* @file fc7xxx_driver_cpm.c
 * @author Flagchip
 * @brief FC7xxx CPM driver type definition and API
 * @version 0.1.0
 * @date 2024-01-5
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */

 /* ********************************************************************************
  *   Revision History:
  *
  *   Version     Date          Initials      CR#          Descriptions
  *   ---------   ----------    ------------  ----------   ---------------
  *   0.1.0       2024-1-5     Flagchip120    N/A          First version for FC7240
  ******************************************************************************** */
#include "fc7xxx_driver_cpm.h"
#include "interrupt_manager.h"
#include "fc7xxx_driver_fcuart.h"

/**
 *  @brief Cpm user defined interrupt function
 * */
static CPM_InterruptCallBackType s_pCpmNotifyPtr = NULL;

/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */
void CPM_IRQHandler(void);

/* ################################################################################## */
/* ################################ Global Functions ################################ */
/**
 *
 * @brief Configures the CPM module interrupts.
 *
 * This function configures the CPM module interrupts to enable/disable various interrupt sources.
 *
 * @param eIntSrc CPM FPU interrupt type. refer CPM FISCR register
 * @param bEnable 1: interrupt enable, 0:interrupt disable.
 */
void CPM_FpuIntMode(FPU_IntType eIntSrc, bool bEnable)
{
    switch (eIntSrc)
    {
        case CPM_FPU_FIO:
            CPM_HWA_SetFioceInt(bEnable);
            break;
        case CPM_FPU_FDZ:
            CPM_HWA_SetFdzceInt(bEnable);
            break;
        case CPM_FPU_FOF:
            CPM_HWA_SetFofceInt(bEnable);
            break;
        case CPM_FPU_FUF:
            CPM_HWA_SetFufceInt(bEnable);
            break;
        case CPM_FPU_FIX:
            CPM_HWA_SetFixceInt(bEnable);
            break;
        case CPM_FPU_FID:
            CPM_HWA_SetFidceInt(bEnable);
            break;
        default :
            /* Invalid parameter: return */
            break;
    }
}

/**
 * @brief Get CPM Interrupt occurred flag
 *
 *  This function returns the interrupt flag.
 *
 * @param eIntSrc CPM FPU interrupt type. refer CPM FISCR register
 * @return true interrupt occurred
 * @return false No interrupt
 */
bool CPM_GetFpuIntStatus(FPU_IntType eIntSrc)
{
    bool bRetVal = false;
    switch(eIntSrc){
    case CPM_FPU_FIO:
        bRetVal = CPM_HWA_GetFpuFiocFlag();
        break;
    case CPM_FPU_FDZ:
        bRetVal = CPM_HWA_GetFpuFdzcFlag();
        break;
    case CPM_FPU_FOF:
        bRetVal = CPM_HWA_GetFpuFofcFlag();
        break;
    case CPM_FPU_FUF:
        bRetVal = CPM_HWA_GetFpuFufcFlag();
        break;
    case CPM_FPU_FIX:
        bRetVal = CPM_HWA_GetFpuFixcFlag();
        break;
    case CPM_FPU_FID:
        bRetVal = CPM_HWA_GetFpuFidcFlag();
        break;
    default:
        break;

    }
    return bRetVal;
}


#ifdef FPU_USED_ENABLE
/**
 * @brief CPM_Read_FPSCR
 * Return the current value of FPSCR
 * @return u32RetVal 
 */
uint32_t CPM_Read_FPSCR(void)
{
    uint32_t u32RetVal = 0U;
    __asm(
            "vmrs %0, fpscr" : "=r" (u32RetVal)
    );
    return u32RetVal;
}

/**
 * @brief CPM_Write_FPSCR
 * 
 * @param u32SetVal set the value for FPSCR 
 */
void CPM_Write_FPSCR(uint32_t u32SetVal)
{
        __asm(
                "vmsr fpscr, %0" : : "r" (u32SetVal)
        );
}

/**
 * @brief Deinit Cpm set interrupt
 *
 * Restore the Cpm FISCR to its reset state
 */
void CPM_DeInitInterrupt(void)
{
	uint32_t u32RetVal;
    CPM_HWA_SetFiscr(0x0U);
    u32RetVal = CPM_Read_FPSCR();
    /* Clear FPSCR IDC/IXC/UFC/OPF/DZC/IOC flag*/
    u32RetVal &=0xFFFFFF90u;
    CPM_Write_FPSCR(u32RetVal);
}
#endif

/**
 * @brief CPM interrupt function
 * 
 */
void CPM_IRQHandler(void)
{
    if(s_pCpmNotifyPtr != NULL)
    {
    	s_pCpmNotifyPtr();
    }
}

/**
 * @brief Cpm set interrupt
 *
 * @param pIntStruct interrupt structure pointer
 * @return Cpm return type
 */
CPM_RetType CPM_InitInterrupt(const CPM_InterruptType *pIntStruct)
{
    CPM_RetType eRet = CPM_STATUS_SUCCESS;
    if(NULL == pIntStruct)
    {
        eRet = CPM_STATUS_PARAM_INVALID;
    }
    else
    {
        if(pIntStruct->u8CpmEnable != 0U)
        {
            if(((uint32_t)(pIntStruct->eFPU_IntType) & CPM_FISCR_FIOC_MASK) == CPM_FPU_FIO)
            {
                CPM_FpuIntMode(CPM_FPU_FIO,true);
            }
            if(((uint32_t)(pIntStruct->eFPU_IntType) & CPM_FISCR_FDZC_MASK) == CPM_FPU_FDZ)
            {
               	CPM_FpuIntMode(CPM_FPU_FDZ,true);
            }
            if(((uint32_t)(pIntStruct->eFPU_IntType) & CPM_FISCR_FUFC_MASK) == CPM_FPU_FUF)
            {
               	CPM_FpuIntMode(CPM_FPU_FUF,true);
            }
            if(((uint32_t)(pIntStruct->eFPU_IntType) & CPM_FISCR_FOFC_MASK) == CPM_FPU_FOF)
            {
              	CPM_FpuIntMode(CPM_FPU_FOF,true);
            }
            if(((uint32_t)(pIntStruct->eFPU_IntType) & CPM_FISCR_FIDC_MASK) == CPM_FPU_FID)
            {
                CPM_FpuIntMode(CPM_FPU_FID,true);
            }
            if(((uint32_t)(pIntStruct->eFPU_IntType) & CPM_FISCR_FIXC_MASK) == CPM_FPU_FIX)
            {
                CPM_FpuIntMode(CPM_FPU_FIX,true);
            }
        }
            s_pCpmNotifyPtr = pIntStruct->pIsrNotify;
    }
    return eRet;
}

