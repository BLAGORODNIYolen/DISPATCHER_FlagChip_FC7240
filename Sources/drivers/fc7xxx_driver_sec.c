/**
 * @file fc7xxx_driver_sec.c
 * @author FlagchipXXX
 * @brief FC7xxx SEC driver type definition and API
 * @version 0.1.0
 * @date 2024-1-12
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*     0.1.0    2024-1-12       Flagchip113    N/A         First version for FC7240
********************************************************************************/
#include "fc7xxx_driver_sec.h"




/**
 * @brief This function can be used to enable the Debug mode.
 * @return  true means enable debug success ,false means enable debug failed.
 * */
bool SEC_EnDebugMode(void)
{
    bool ret = false;
    if (SEC_HWA_GetWritePer())
    {
        SEC_HWA_EnDebug();
        ret = true;
    }
    return ret;
}

/**
 * @brief This function can be used to  re-enable the Debug mode by the re-enable keys.
 * @param keys The Debug mode re-enable keys.
 * @return true means re-enable success,false means re-enable failed.
 * */
bool SEC_ReEnDebugMode(ReEnDebug_Keys keys)
{
    bool ret = false;
    if (SEC_HWA_GetReEnDebug())
    {
    	SEC_HWA_ChangeDBK(0u, keys.Re_key0);
    	SEC_HWA_ChangeDBK(1u, keys.Re_key1);
    	SEC_HWA_ChangeDBK(2u, keys.Re_key2);
    	SEC_HWA_ChangeDBK(3u, keys.Re_key3);
        ret = true;
    }
    return ret;
}

/**
 * @brief This function can get the system state (secured or no secured).
 * */
Systemstate SEC_SystemSecureState(void)
{
    Systemstate  ret =  Securedstate ;
    uint16_t sskey0 = SEC_HWA_GetSScontrol0();
    uint16_t sskey1 = SEC_HWA_GetSScontrol1();
    if ((sskey0 == 0xC35AU) && (sskey1 == 0xFFFFU))
    {
        ret = UnSecuredstate;
    }
    return ret ;
}


/**
 * @brief This function can enable the test mode.
 * @return true means enable test mode success,false means enable test mode failed.
 * */
bool SEC_EnTestMode(void)
{

    bool ret = false;
    if (SEC_HWA_GetWritePer())
    {
        SEC_HWA_EnTest();
        ret = true;
    }
    return ret;
}



/**
 *@brief This function can Re-enable the test mode by the re-enable key.
 *@param key The test mode re-enable key.The key is up to the user to decide in advance.
 *@return true means re-enable success,false means re-enable failed.
 * */
bool SEC_ReEnTestMode(uint32_t key)
{
    bool ret = false;

    bool writeper = SEC_HWA_GetWritePer();
    bool reentest = SEC_HWA_GetReEnTest();
    if ((true == writeper) && (true == reentest))
    {
        SEC_HWA_ReEnTestKey(key);
        ret = true;
    }
    return ret;
}



/**
 * @brief This function can used to set the NVR write and read permission.
 * @return true means setPer success,false means setPer failed.
 * */
bool SEC_SetNvrPer(NVR_Per per)
{
    bool ret = false;
    if (SEC_HWA_GetWritePer())
    {

    	if (per.ReadEn == true)
		{
			SEC_HWA_EnReadB0NVR();
		}
		else
		{
			SEC_HWA_DisReadB0NVR();
		}
        if (per.WritEn == true)
        {
            SEC_HWA_EnWriteB0NVR();
        }
        else
        {
            SEC_HWA_DisWriteB0NVR();
        }

        if (per.EraseEn == true)
        {
            SEC_HWA_EnEraseB0NVR();
        }
        else
        {
            SEC_HWA_DisEraseB0NVR();
        }

        ret = true;
    }
    return ret;
}


/**
 * @brief Get Secure Boot Enable Status
 *
 * @return true is enable and false is disable
 */
bool SEC_GetSecureStatus(void)
{
    return SEC_HWA_GetSB();
}

/**
 * @brief Get ISP Status
 *
 * @return true is active and false is inactive
 */
bool SEC_GetISPModeStatus(void)
{
    return SEC_HWA_GetIspStatus();
}

/**
 * @brief Get User setting bootloader address
 *
 * @return bootloader address
 */
uint32_t SEC_GetBootAddress(void)
{
    return SEC_HWA_GetBLAddr();
}


///**
// * @brief Get the HSM Firmware Address
// *
// * @return the HSM Firmware address
// */
//uint32_t SEC_GetHsmFwAddress(void)
//{
//    return SEC_HWA_GetHsmAddr();
//}


/**
 * @brief Get the lifecycle.
 *
 * @return the lifecycle.
 */

SC_LifeCycle SEC_GetLifeCycle(void)
{
    SC_LifeCycle lifecycle  = LIFECYCLE_INVALID;

    uint8_t lifecycle_status;
    lifecycle_status = SEC_HWA_GetLCStaus();

    switch (lifecycle_status)
    {
    case 1u:
        lifecycle = LIFECYCLE_OEM_DEV;
        break;
    case 2u:
        lifecycle = LIFECYCLE_OEM_PDT;
        break;
    case 4u:
        lifecycle = LIFECYCLE_INFIELD;
        break;
    case 8u:
        lifecycle = LIFECYCLE_PREFA;
        break;
    case 16u:
        lifecycle = LIFECYCLE_FA;
        break;
    default:
        break;

    }
    return lifecycle;
}



/**
 * @brief User Key Access Enable. Only valid under non-secure boot
 * @return true means User key can be read/programmed/erased by host CPU
 * */
bool SEC_HostUKAccess(void)
{
    return SEC_HWA_GetUKAS();
}

/**
 * @brief get the Bootloader Verification Algorithm
 *  @return the Bootloader Verification Algorithm
 * */
BL_VerifyAlgorithm SEC_GetBLVerifyAlgorithm(void)
{

    return (BL_VerifyAlgorithm)(uint8_t)(SEC_HWA_GetBLVer());
}


/**
 * @brief get the Debug/ISP/PREFA Authentication and USRK decryption algorithm
 *  @return decryption algorithm
 * */
Decryption_Algorithm SEC_GetDecryptAlgorithm(void)
{
    return (Decryption_Algorithm)(uint8_t)(SEC_HWA_GetDecrypt());


}


/**
 * @brief Indicate the Host User Key Read/Write/Erase Protection
 * @param PHostUKAccess the structure for information
 *
 * */
void SEC_GetHostUKAccess(HostUKPermission *const PHostUKAccess)
{
    PHostUKAccess->HostUKEraseEn =  SEC_HWA_GetHUKErase();
    PHostUKAccess->HostUKReadEn = SEC_HWA_GetHUKRead();
    PHostUKAccess->HostUKWriteEn = SEC_HWA_GetHUKWrite();
}

/**
 * @brief Indicate the Host NVR Read/Write/Erase Protection
 *@param PHostNvrAccess the structure to initialize
 * */
void SEC_GetHostNVRAccess(HostNVRPermission *const PHostNVRAccess)
{
    PHostNVRAccess->HostNVREraseEn = SEC_HWA_GetHostNvrErase();
    PHostNVRAccess->HostNVRReadEn = SEC_HWA_GetHostNvrRead();
    PHostNVRAccess->HostNVRWriteEn = SEC_HWA_GetHostNvrWrite();

}



/**
 * @brief Get the HSM User Key Erase Protection
 * @return true - HSM erase access to User Key region is enabled
 *          false -HSM erase access to User Key region is disabled
 * */
bool SEC_GethsmUKEraseAccess(void)
{
    return SEC_HWA_GetHsmUKErase();

}


/**
 * @brief Get the HSM NVR Erase Protection
 * @return true - HSM erase access to NVR region is enabled
 *          false -HSM erase access to NVR region is disabled
 * */
bool SEC_GethsmNVREraseAccess(void)
{
    return  SEC_HWA_GetHsmNvrErase();
}

/**
 * @brief Get Bootloader Verification Mask
 * @return Bootloader Verification Mask.
 * */
uint32_t SEC_GetBLVerMask(void)
{
    return SEC_HWA_GetBLMask();
}

/**
 * @brief Get whether Debug Backdoor Key Input Enable.
 * @return
 * 0011b - User can input DBK through debug mailbox, ISP is not valid.
 * 1100b - User can input DBK through ISP, debug mailbox is not valid.
 * 1111b - User can input DBK through both debug mailbox and ISP.
 * Other Values - User cannot input DBK through both debug mailbox andISP.
 * */
uint32_t SEC_GetDMBDkeyEn(void)
{
    return SEC_HWA_GetMBBKEN();
}


/**
 * @brief Host Debug Auth Enable. Only valid in secure boot. (Value loaded from NVR sector)
 * @return  true means Host debug authentication enable. false means Host debug authentication disable.
 */
bool SEC_GetDebugAuthEn(void)
{
    return SEC_HWA_GetDEAUEn();
}


/**
 * @brief Get the isp information.
 * @param pIspInfo the structure to information
 * @return Get whether operation is success.
 *
 * */
SEC_RetType SEC_GetIspInfo(SEC_IspInfo *const pIspInfo)
{

    SEC_RetType eRet ;

    if (NULL == pIspInfo)
    {
        eRet = SEC_STATUS_FAILED;
    }
    else
    {
        bool ispen =  SEC_HWA_GetIspStatus();
        if (!ispen)
        {
            eRet = SEC_STATUS_FAILED;
        }
        else
        {
            pIspInfo->IspModeEn = SEC_HWA_GetIspStatus();
            pIspInfo->IspPinEn = SEC_HWA_GetIspEn();
            pIspInfo->IspAuthEn = SEC_HWA_GetISPAU();
            Isp_Instance ispins = (Isp_Instance)(uint8_t)(SEC_HWA_GetIspIns());
            if ((ispins == ISP_FCUART1) || (ispins == ISP_FCUART3))
            {
                pIspInfo->Ispfcuartbaudrate = (FCUART_ISP_BAUDRATE)(uint8_t)(SEC_HWA_GetUartBR());
                pIspInfo->Ispflexcanbaudrate = ISP_FLEXCAN_INVALID;
            }
            else if ((ispins == ISP_FLEXCAN1) || (ispins == ISP_FLEXCAN5))
            {
                pIspInfo->Ispfcuartbaudrate = ISP_FCUART_INVALID;
                pIspInfo->Ispflexcanbaudrate = (FLEXCAN_ISP_BAUDRATE)(uint8_t)(SEC_HWA_GetCanBR());
            }
            else
            {
                /*do nothing*/
            }
            eRet = SEC_STATUS_SUCCESS;
        }
    }
    return eRet;
}

/**
 * @brief Get the boot information.
 * @param pBootInfo the structure for information
 * @return Get whether operation is success.
 *
 * */
SEC_RetType SEC_GetBootInfo(SEC_BootInfo *const pBootInfo)
{

    SEC_RetType eRet ;
    if (NULL == pBootInfo)
    {
        eRet = SEC_STATUS_FAILED;
    }
    else
    {
        pBootInfo->BootRom = SEC_HWA_GetBootRom();
        pBootInfo->NmiPinEn = SEC_HWA_GetNmiPin();
        pBootInfo->SecBootEn = SEC_HWA_GetSB();
        pBootInfo->OscEn = SEC_HWA_GetOSCAvail();
        pBootInfo->OscFreq = (Osc_FreqInfo)(uint8_t)(SEC_HWA_GetOSCFre());
        pBootInfo->FastBootSpeed = (FastBoot_Speed)(uint8_t)(SEC_HWA_GetFastBootClock());
        eRet = SEC_STATUS_SUCCESS;
    }
    return eRet;
}


