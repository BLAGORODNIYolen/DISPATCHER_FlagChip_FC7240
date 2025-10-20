/**
 * @file HwA_sec.h
 * @author Flagchip
 * @brief FC7xxx sec hardware access layer
 * @version 0.2.0
 * @date 2023-2-7
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.2.0       2023-2-7     Flagchip076    N/A          First version for FC7300
   ******************************************************************************** */

#ifndef HWA_INCLUDE_HWA_SEC_H_
#define HWA_INCLUDE_HWA_SEC_H_
#include "device_header.h"

/**
 * @addtogroup HwA_SEC
 * @{
 *
 */

/* DEN Bit Fields */
/**
 *@brief Enable the debug module
 * */
LOCAL_INLINE void SEC_HWA_EnDebug(void)
{
    SEC->DEN = SEC_DEN_DEN(0X5) ;
}

/* FSEC0 Bit Fields */
/**
 * @brief Get the system security KEY0
 * */
LOCAL_INLINE uint16_t SEC_HWA_GetSScontrol0(void)
{
    return (uint16_t)((SEC->FSEC0) & (SEC_FSEC0_SSC0_MASK));
}

/* FSEC1 Bit Fields */
/**
 * @brief Get the system security KEY1
 * */
LOCAL_INLINE uint16_t SEC_HWA_GetSScontrol1(void)
{
    return (uint16_t)((SEC->FSEC1) & (SEC_FSEC1_SSC1_MASK));
}

/* DCWOR Bit Fields */
/**
 * @brief Re-enable the Debug mode.
 * @note  This register can only be write once. startup_fc4150.s has lock the register.
 * */
LOCAL_INLINE void SEC_HWA_ReEnDebug(void)
{
    SEC->DCWOR = ((SEC->DCWOR & (~SEC_DCWOR_DEA_MASK)) | SEC_DCWOR_DEA(0X5));
}

/**
 * @brief Get the Re-enable Debug permission.
 * */
LOCAL_INLINE bool SEC_HWA_GetReEnDebug(void)
{
    bool ret = false;
    uint8_t  dea = (uint8_t)((SEC->DCWOR & (SEC_DCWOR_DEA_MASK)) >> SEC_DCWOR_DEA_SHIFT);
    if (dea == 0x5U)
    {
        ret = true;
    }
    return ret;
}

/**
 * @brief Enable the write operation for SEC register.
 * @note  This register can only be write once. startup_fc4150.s has lock the register.
 * */
LOCAL_INLINE void SEC_HWA_WriteUnlock(void)
{
    SEC->DCWOR = ((SEC->DCWOR & (~SEC_DCWOR_RWL_MASK)) | SEC_DCWOR_RWL(0X5));
}

/**
 * @brief Get the sec write permission
 * @return true means allow write. false means  forbid write.
*/
LOCAL_INLINE bool SEC_HWA_GetWritePer(void)
{
    bool ret = false;
    uint8_t rwl = (uint8_t)((SEC->DCWOR & (SEC_DCWOR_RWL_MASK)) >> SEC_DCWOR_RWL_SHIFT);
    if ((rwl == 0x5U) || (rwl == 0xFU))
    {
        ret = true;
    }
    return ret;
}

/* DEK Bit Fields */
/**
 * @brief Enable the write operation for SEC register.
 * */
LOCAL_INLINE void SEC_HWA_ChangeDBK(uint8_t count, uint32_t key)
{
 
       SEC->DEK[count] = SEC_DEK_DEK(key) ;
  
}

/* TME Bit Fields */
/**
 *@brief Enable the Test module
 * */
LOCAL_INLINE void SEC_HWA_EnTest(void)
{
    SEC->TME = SEC_TME_TME(0X5) ;
}

/* TMEA Bit Fields */
/**
 * @brief Re-Enable Test mode
 * */
LOCAL_INLINE void SEC_HWA_ReEnTest(void)
{
    SEC->TMEA = SEC_TMEA_TMEA(0X5) ;
}

/**
 * @brief Get the Re-enable Test permission.
 * */
LOCAL_INLINE bool SEC_HWA_GetReEnTest(void)
{
    bool ret = false;
    uint8_t  tmea = (uint8_t)((SEC->TMEA & (SEC_TMEA_TMEA_MASK)) >> SEC_TMEA_TMEA_SHIFT);
    if ((tmea == 0x5U) || (tmea == 0xFU))
    {
        ret = true;
    }
    return ret;
}

/* TMEK Bit Fields */
/**
 *@brief write Test re-enable mode key
 *
 */
LOCAL_INLINE void SEC_HWA_ReEnTestKey(uint32_t testkey)
{
    SEC->TMEK = SEC_TMEK_TMEK(testkey) ;
}

/* FCR0 Bit Fields */
/**
 * @brief Enable the Mass Erase
 */
LOCAL_INLINE void SEC_HWA_EnME(void)
{
    SEC->FCR0 = ((SEC->FCR0 & (~SEC_FCR0_MED_MASK)) | SEC_FCR0_MED(0x5));
}

/**
 * @brief Enable the Block 0 NVR write .
 */
LOCAL_INLINE void SEC_HWA_EnWriteB0NVR(void)
{
    SEC->FCR0 = ((SEC->FCR0 & (~SEC_FCR0_NWP_MASK)) | SEC_FCR0_NWP(0x5)) ;
}

/**
 * @brief Disable the Block 0 NVR write .
 */
LOCAL_INLINE void SEC_HWA_DisWriteB0NVR(void)
{
    SEC->FCR0 = ((SEC->FCR0 & (~SEC_FCR0_NWP_MASK)) | SEC_FCR0_NWP(0xA)) ;
}

/**
 * @brief Enable the Block 0 NVR erase .
 */
LOCAL_INLINE void SEC_HWA_EnEraseB0NVR(void)
{
    SEC->FCR0 = ((SEC->FCR0 & (~SEC_FCR0_NEP_MASK)) | SEC_FCR0_NEP(0x5)) ;
}

/**
 * @brief Disable the Block 0 NVR erase .
 */
LOCAL_INLINE void SEC_HWA_DisEraseB0NVR(void)
{
    SEC->FCR0 = ((SEC->FCR0 & (~SEC_FCR0_NEP_MASK)) | SEC_FCR0_NEP(0xA)) ;
}

/* NKRP Bit Fields */
/**
 * @brief NVR Key Read Protection.
 * @brief Enable the Block 0 NVR read.
 */
LOCAL_INLINE void SEC_HWA_EnReadB0NVR(void)
{
    SEC->FCR0 = ((SEC->NKRP & (~SEC_NKRP_NKRP_MASK)) | SEC_NKRP_NKRP(0x5)) ;
}

/**
 * @brief Disable the Block 0 NVR read .
 */
LOCAL_INLINE void SEC_HWA_DisReadB0NVR(void)
{
    SEC->FCR0 = ((SEC->FCR0 & (~SEC_NKRP_NKRP_MASK)) | SEC_NKRP_NKRP(0xA)) ;
}


/* BCS Bit Fields */
/**
 * @brief Get the Fast Boot Select.
 * @return 0b - Select PLL0 as the core clock source; the core clock is 300MHz
 *          1b - Select FIRC as the core clock source; the core clock is 96MHz.
 * */
LOCAL_INLINE uint8_t SEC_HWA_GetFastBootClock(void)
{
    return (uint8_t)((SEC->BCS & SEC_BCS_FBS_MASK) >> SEC_BCS_FBS_SHIFT);
}

/**
 * @brief NMI Function Enable/Disable
 * @return  false - NMI pin function is disabled after reset.
 *          true - NMI pin function is enabled
 * */
LOCAL_INLINE bool SEC_HWA_GetNmiPin(void)
{
    return (bool)((SEC->BCS & SEC_BCS_NMIDIS_MASK) >> SEC_BCS_NMIDIS_SHIFT);
}

/**
 * @brief ISP Function Enable/Disable ISP Mode Status
 * @return  false - ISP mode is inactive.
 *          true -  ISP mode is active.
 * */
LOCAL_INLINE bool SEC_HWA_GetIspStatus(void)
{
    return (bool)((SEC->BCS & SEC_BCS_ISPMODE_MASK) >> SEC_BCS_ISPMODE_SHIFT);
}

/**
 * @brief Boot Rom Configuration
 * @return  false - Boot from GPR defined address (except ROM).
 *          true -  Boot from ROM.
 * */
LOCAL_INLINE bool SEC_HWA_GetBootRom(void)
{
    return (bool)((SEC->BCS & SEC_BCS_BOOTROM_MASK) >> SEC_BCS_BOOTROM_SHIFT);
}

/**
 * @brief Get Chip Part Mode
 * @return  false - Chip is in FlexCore part mode.
 *          true  - Chip is in HSM part mode.
 * */
LOCAL_INLINE bool SEC_HWA_GetPartMode(void)
{
    return (bool)((SEC->BCS & SEC_BCS_PART_MODE_MASK) >> SEC_BCS_PART_MODE_SHIFT);
}

/**
 * @brief Get PF_128BIT_MODE
 * @return  false - Chip is in FlexCore part mode.
 *          true  - Chip is in HSM part mode.
 * */
LOCAL_INLINE bool SEC_HWA_GetPF128BitMode(void)
{
    return (bool)((SEC->BCS & SEC_BCS_PF_128BIT_MODE_MASK) >> SEC_BCS_PF_128BIT_MODE_SHIFT);
}

/* UKAC Bit Fields */

/**
 * @brief User Key Access Enable. Only valid under non-secure boot
 * @return true means User key can be read/programmed/erased by host CPU ,false means User key is not available for host cpu
 * */
LOCAL_INLINE bool SEC_HWA_GetUKAS(void)
{
    bool ret = false;
    uint8_t uake =(uint8_t)((SEC->UKAC & SEC_UKAC_UKAE_MASK) >> SEC_UKAC_UKAE_SHIFT);
    if ((uake == 0x5U) || (uake == 0xFU))
    {
        ret = true;
    }
    return ret;
}

/* BRC0 Bit Fields */
/**
 * @brief Secure Boot Disable (Value loaded from NVR sector)
 * @return  true means Secure boot mode , false means Non secure boot mode.
 */
LOCAL_INLINE bool SEC_HWA_GetSB(void)
{
    bool ret = false;
    uint8_t sbdis = (uint8_t)((SEC->BRC0 & SEC_BRC0_SECURE_BOOT_DIS_MASK) >> SEC_BRC0_SECURE_BOOT_DIS_SHIFT);
    if (sbdis == 0x0u)
    {
        ret = true;
    }
    return ret;
}

/**
 * @brief Host Debug Auth Enable. Only valid in secure boot. (Value loaded from NVR sector)
 * @return  true means Host debug authentication enable. false means Host debug authentication disable.
 */
LOCAL_INLINE bool SEC_HWA_GetDEAUEn(void)
{
    bool ret = false;
    uint8_t dean = (uint8_t)((SEC->BRC0 & SEC_BRC0_DEBUG_AUTH_EN_MASK) >> SEC_BRC0_DEBUG_AUTH_EN_SHIFT);
    if ((dean == 0x5u) || (dean == 0xFu))
    {
        ret = true;
    }
    return ret;
}

/**
 * @brief ISP Auth Enable. Only valid in secure boot. (Value loaded from NVR sector)
 * @return  true means ISP authentication enable, false means ISP authentication disable.
 */
LOCAL_INLINE bool SEC_HWA_GetISPAU(void)
{
    bool ret = false;
    uint8_t isp = (uint8_t)((SEC->BRC0 & SEC_BRC0_ISP_AUTH_EN_MASK) >> SEC_BRC0_ISP_AUTH_EN_SHIFT);
    if ((isp == 0x5u) || (isp == 0xFu))
    {
        ret = true;
    }
    return ret;
}

/* BRC1 Bit Fields */
/**
 * @brief Get the FCUART Baud Rate for ISP
 * @return FCUART Baud Rate for ISP
 * */
LOCAL_INLINE uint8_t SEC_HWA_GetUartBR(void)
{
    return (uint8_t)((SEC->BRC1 & SEC_BRC1_UARTBR_MASK) >> SEC_BRC1_UARTBR_SHIFT);
}

/**
 * @brief Get CAN Baud Rate for ISP
 * @return CAN Baud Rate for ISP
 * */
LOCAL_INLINE uint8_t SEC_HWA_GetCanBR(void)
{
    return (uint8_t)((SEC->BRC1 & SEC_BRC1_CANBR_MASK) >> SEC_BRC1_CANBR_SHIFT);
}

/**
 * @brief Get OSC Frequency
 * @return OSC Frequency
 * */
LOCAL_INLINE uint8_t SEC_HWA_GetOSCFre(void)
{
    return (uint8_t)((SEC->BRC1 & SEC_BRC1_OSCFREQ_MASK) >> SEC_BRC1_OSCFREQ_SHIFT);
}

/**
 * @brief  Get whether OSC Available.
 * @return true means OSC is available. false means -OSC is not available
 * */
LOCAL_INLINE bool SEC_HWA_GetOSCAvail(void)
{
    bool ret = false;
    uint8_t osc = (uint8_t)((SEC->BRC1 & SEC_BRC1_OSCA_MASK) >> SEC_BRC1_OSCA_SHIFT);
    if (osc ==  0x0U)
    {
        ret = true;
    }
    return ret;
}

/**
 * @brief Get Debug Backdoor Key Input Enable.
 * @return
 * 0011b - User can input DBK through debug mailbox, ISP is not valid
 * 1100b - User can input DBK through ISP, debug mailbox is not valid.
 * 1111b - User can input DBK through both debug mailbox and ISP.
 * Other Values - User cannot input DBK through both debug mailbox andISP
 * */
LOCAL_INLINE uint32_t SEC_HWA_GetMBBKEN(void)
{
    return (uint32_t)((SEC->BRC1 & SEC_BRC1_DBK_IN_EN_MASK) >> SEC_BRC1_DBK_IN_EN_SHIFT);
}

/**
 * @brief Get Debug Backdoor Key Encryption Algorithm
 * @return false-User code verification enable in non-secure boot mode
		   true- User code verification disable in non-secure boot mode.
 * */
LOCAL_INLINE bool SEC_HWA_GetNonSecVerifEN(void)
{
	bool ret = false;
	uint8_t dean = (uint8_t)((SEC->BRC0 & SEC_BRC1_NON_SEC_VERIF_EN_MASK) >> SEC_BRC1_NON_SEC_VERIF_EN_SHIFT);
	if (dean == 1u)
	{
		ret = true;
	}
	return ret;
}

/**
 * @brief Get User Code Verification Enable under Non-secure Boot Mode
 * @return  Bootloader Verification Algorithm
 * 000b - AES256-CBC
 * 111b - SM4-CBC.
 * */
LOCAL_INLINE uint8_t SEC_HWA_GetDBDkeyEncrypAlg(void)
{
    return (uint8_t)((SEC->BRC1 & SEC_BRC1_DBKEA_MASK) >> SEC_BRC1_DBKEA_SHIFT);
}

/**
 * @brief ISP Function Enable/Disable，Only valid in non-secure mode
 * @return  false - ISP pin function is disabled after reset.
 *          true -  ISP pin function is enabled.
 * */
LOCAL_INLINE bool SEC_HWA_GetIspEn(void)
{
    return (bool)((SEC->BRC1 & SEC_BRC1_ISP_PIN_EN_MASK) >> SEC_BRC1_ISP_PIN_EN_SHIFT);
}

/**
 * @brief GET ISP Mode whether Allowed in Recovery Mode
 * @return  false -  ISP mode is not allowed in recovery mode
 *          true -   ISP mode is allowed in recovery mode.
 * */
LOCAL_INLINE bool SEC_HWA_GetIspIsAllowedInRec(void)
{
    return (bool)((SEC->BRC1 & SEC_BRC1_ISPAIRM_MASK) >> SEC_BRC1_ISPAIRM_SHIFT);
}

/**
 * @brief GET Enable the Output of Plaintext Decrypted ROOT Key
 * @return  false - The output of plaintext decrypted ROOT key is enabled
 *          true - The output of plaintext decrypted ROOT key is disabled.
 * */
LOCAL_INLINE bool SEC_HWA_GetKeyPlaRoot(void)
{
    return (bool)((SEC->BRC1 & SEC_BRC1_KEY_PROT_MASK) >> SEC_BRC1_KEY_PROT_SHIFT);
}

/**
 * @brief Get ROM Loop Control Flag
 * @return  false - ROM executes normal run under VIRGIN and FT state.
 *          true - ROM enters debug loop under VIRGIN and FT state.
 * */
LOCAL_INLINE bool SEC_HWA_GetLoopCtrFlag(void)
{
    return (bool)((SEC->BRC1 & SEC_BRC1_ROM_LOOP_CTRL_MASK) >> SEC_BRC1_ROM_LOOP_CTRL_SHIFT);
}

/**
 * @brief Get Enable Software Configuration to Enter ISP
 * @return  false - Software configuration to enter ISP is enabled.
 *          true - Software configuration to enter ISP is disabled.
 * */
LOCAL_INLINE bool SEC_HWA_GetIspSoftConfig(void)
{
    return (bool)((SEC->BRC1 & SEC_BRC1_SW_CFG_ISP_EN_MASK) >> SEC_BRC1_SW_CFG_ISP_EN_SHIFT);
}


/* SW_CFG_ISP_FLG  Bit Fields */
/**
 * @brief Software Configuration to Enter ISP Flag
 * @return ISP Flag.
 * */
LOCAL_INLINE uint8_t SEC_HWA_GetSwCfgIspFlg(void)
{
	return (uint8_t)((SEC->SW_CFG_ISP_FLG & SEC_SW_CFG_ISP_FLG_SW_CFG_ISP_FLG_MASK) >> SEC_SW_CFG_ISP_FLG_SW_CFG_ISP_FLG_SHIFT);
}


/* BRC2 Bit Fields */
/**
 * @brief Get USERCODE_VERIFY_MASK_MASK
 * @return USERCODE_VERIFY_MASK_MASK.
 * */
LOCAL_INLINE uint32_t SEC_HWA_GetBLMask(void)
{
    return (uint32_t)((SEC->BRC2 & SEC_BRC2_USERCODE_VERIFY_MASK_MASK) >> SEC_BRC2_USERCODE_VERIFY_MASK_SHIFT);
}

/**
 * @brief Get the ISP Instance Select.
 * @return  ISP Instance Select
 * */
LOCAL_INLINE uint8_t SEC_HWA_GetIspIns(void)
{
    return (uint8_t)((SEC->BRC2 & SEC_BRC2_ISP_INST_SEL_MASK) >> SEC_BRC2_ISP_INST_SEL_SHIFT);
}

/**
 * @brief Get Bootloader Verification Algorithm
 * @return  Bootloader Verification Algorithm
 * */
LOCAL_INLINE uint8_t SEC_HWA_GetBLVer(void)
{
    return (uint8_t)((SEC->BRC2 & SEC_BRC2_USERCODE_VERIFICATION_ALG_MASK) >> SEC_BRC2_USERCODE_VERIFICATION_ALG_SHIFT);
}

/**
 * @brief Get Debug/ISP/PREFA Authentication and USRK decryption algorithm
 * @return 1b - SM2, 0b - ECC256
 * */
LOCAL_INLINE uint8_t SEC_HWA_GetDecrypt(void)
{
    return (uint8_t)((SEC->BRC2 & SEC_BRC2_DECRP_ALG_MASK) >> SEC_BRC2_DECRP_ALG_SHIFT);
}

/* IMAGEA Bit Fields */
/**
 * @brief Get the bootloader address.
 * @return Bootloader Address.
 * */
LOCAL_INLINE uint32_t SEC_HWA_GetBLAddr(void)
{
    return (uint32_t)((SEC->IMGEA & SEC_IMGEA_IMAGE_ADDR_MASK) >> SEC_IMGEA_IMAGE_ADDR_SHIFT);
}


/* NVR VER Bit Fields */
/**
 * @brief Get C version.
 * @return C version.
 * */
LOCAL_INLINE uint32_t SEC_HWA_GetCVer(void)
{
    return (uint32_t)((SEC->NVR_VER & SEC_NVR_VER_C_VER_MASK) >> SEC_NVR_VER_C_VER_SHIFT);
}

/**
 * @brief Set C version.
 * @return C version.
 * */
LOCAL_INLINE void SEC_HWA_SetCVer(uint32_t C_Ver)
{
    SEC->NVR_VER=((SEC->NVR_VER & (~SEC_NVR_VER_C_VER_MASK)) | SEC_NVR_VER_C_VER(C_Ver));
}

/**
 * @brief Get R version.
 * @return R version.
 * */
LOCAL_INLINE uint32_t SEC_HWA_GetRVer(void)
{
    return (uint32_t)((SEC->NVR_VER & SEC_NVR_VER_R_VER_MASK) >> SEC_NVR_VER_R_VER_SHIFT);
}

/**
 * @brief Set R version.
 * */
LOCAL_INLINE void SEC_HWA_SetRVer(uint32_t R_Ver)
{
    SEC->NVR_VER=((SEC->NVR_VER & (~SEC_NVR_VER_R_VER_MASK)) | SEC_NVR_VER_R_VER(R_Ver));
}

/**
 * @brief Get V version.
 * @return V version.
 * */
LOCAL_INLINE uint32_t SEC_HWA_GetVVer(void)
{
    return (uint32_t)((SEC->NVR_VER & SEC_NVR_VER_V_VER_MASK) >> SEC_NVR_VER_V_VER_SHIFT);
}

/**
 * @brief Set V version.
 * */
LOCAL_INLINE void SEC_HWA_SetVVer(uint32_t V_Ver)
{
    SEC->NVR_VER=((SEC->NVR_VER & (~SEC_NVR_VER_V_VER_MASK)) | SEC_NVR_VER_V_VER(V_Ver));
}

/**
 * @brief Get CHIP version.
 * @return CHIP version.
 * */
LOCAL_INLINE uint32_t SEC_HWA_GetChipVer(void)
{
    return (uint32_t)((SEC->NVR_VER & SEC_NVR_VER_CHIP_VER_MASK) >> SEC_NVR_VER_CHIP_VER_SHIFT);
}

/**
 * @brief Set CHIP version.
 * */
LOCAL_INLINE void SEC_HWA_SetChipVer(uint32_t CHIP_Ver)
{
    SEC->NVR_VER=((SEC->NVR_VER & (~SEC_NVR_VER_CHIP_VER_MASK)) | SEC_NVR_VER_V_VER(CHIP_Ver));
}

/* LCSTAT Bit Fields */
/**
 * @brief Get the life cycle  status of the chip.
 * @return The lifecycle status
 * */
LOCAL_INLINE uint8_t SEC_HWA_GetLCStaus(void)
{
    return (uint8_t)(SEC->LCSTAT & 0XFFU);
}

/**
 * @brief Get Lifecycle OEM Development
 * @return 0b - Chip is not in this lifecycle
 * 			1b - Chip is in this lifecycle
 * */
LOCAL_INLINE bool SEC_HWA_GetLCOemDev(void)
{
    return (bool)((SEC->LCSTAT & SEC_LCSTAT_LIFECYCLE_OEM_DEV_MASK) >> SEC_LCSTAT_LIFECYCLE_OEM_DEV_SHIFT);
}

/**
 * @brief Get Lifecycle OEM Production
 * @return  false - Chip is not in this lifecycle
 * 			true - Chip is in this lifecycle
 * */
LOCAL_INLINE bool SEC_HWA_GetLCOemPdt(void)
{
    return (bool)((SEC->LCSTAT & SEC_LCSTAT_LIFECYCLE_OEM_PDT_MASK) >> SEC_LCSTAT_LIFECYCLE_OEM_PDT_SHIFT);
}

/**
 * @brief Get Lifecycle In Field
 * @return  false - Chip is not in this lifecycle
 * 			true - Chip is in this lifecycle
 * */
LOCAL_INLINE bool SEC_HWA_GetLCInField(void)
{
    return (bool)((SEC->LCSTAT & SEC_LCSTAT_LIFECYCLE_IN_FIELD_MASK) >> SEC_LCSTAT_LIFECYCLE_IN_FIELD_SHIFT);
}

/**
 * @brief Get Lifecycle Software Fault Analysis
 * @return  false - Chip is not in this lifecycle
 * 			true - Chip is in this lifecycle
 * */
LOCAL_INLINE bool SEC_HWA_GetLCSwFa(void)
{
    return (bool)((SEC->LCSTAT & SEC_LCSTAT_LIFECYCLE_SWFA_MASK) >> SEC_LCSTAT_LIFECYCLE_SWFA_SHIFT);
}

/**
 * @brief Get Lifecycle Hardware Fault Analysis
 * @return  false - Chip is not in this lifecycle
 * 			true - Chip is in this lifecycle
 * */
LOCAL_INLINE bool SEC_HWA_GetLCHwFa(void)
{
    return (bool)((SEC->LCSTAT & SEC_LCSTAT_LIFECYCLE_HWFA_MASK) >> SEC_LCSTAT_LIFECYCLE_HWFA_SHIFT);
}

/* FAC Bit Fields */
/**
 * @brief Get the Host User Key Read Protection
 * @return true - Host read access to User Key region is enabled
 *         false - Host read access to User Key region is disabled
 * */
LOCAL_INLINE bool SEC_HWA_GetHUKRead(void)
{
    return (bool)(~(((SEC->FAC) & SEC_FAC_HOST_UKEY_RPROT_MASK) >> SEC_FAC_HOST_UKEY_RPROT_SHIFT));
}

/**
 * @brief Get the Host User Key write Protection
 * @return true - Host write access to User Key region is enabled
 *          false - Host write access to User Key region is disabled
 * */
LOCAL_INLINE bool SEC_HWA_GetHUKWrite(void)
{
    return (bool)(~(((SEC->FAC) & SEC_FAC_HOST_UKEY_WPROT_MASK) >> SEC_FAC_HOST_UKEY_WPROT_SHIFT));
}

/**
 * @brief Get the Host User Key erase Protection
 * @return true - Host erase access to User Key region is enabled
 *          false - Host erase access to User Key region is disabled
 * */
LOCAL_INLINE bool SEC_HWA_GetHUKErase(void)
{
    return (bool)(~(((SEC->FAC) & SEC_FAC_HOST_UKEY_EPROT_MASK) >> SEC_FAC_HOST_UKEY_EPROT_SHIFT));
}

/**
 * @brief Get the Host NVR Read Protection
 * @return true - Host read access to NVR region is enabled
 *          false - Host read access to NVR region is disabled
 * */
LOCAL_INLINE bool SEC_HWA_GetHostNvrRead(void)
{
    return (bool)(~(((SEC->FAC) & SEC_FAC_HOST_NVR_RPROT_MASK) >> SEC_FAC_HOST_NVR_RPROT_SHIFT));
}

/**
 * @brief Get the Host NVR write Protection
 * @return true - Host write access to NVR region is enabled
 *          false - Host write access to NVR region is disabled
 * */
LOCAL_INLINE bool SEC_HWA_GetHostNvrWrite(void)
{
    return (bool)(~(((SEC->FAC) & SEC_FAC_HOST_NVR_WPROT_MASK) >> SEC_FAC_HOST_NVR_WPROT_SHIFT));
}

/**
 * @brief Get the Host NVR erase Protection
 * @return true - Host erase access to NVR region is enabled
 *          false - Host erase access to NVR region is disabled-
 * */
LOCAL_INLINE bool SEC_HWA_GetHostNvrErase(void)
{
    return (bool)(~(((SEC->FAC) & SEC_FAC_HOST_NVR_EPROT_MASK) >> SEC_FAC_HOST_NVR_EPROT_SHIFT));
}

/**
 * @brief Get HSM User Key Read Protection
 * @return  true - HSM Read access to User Key region is disabled
 *          false - HSM Read access to User Key region is enabled
 * */
LOCAL_INLINE bool SEC_HWA_GetHsmUKRead(void)
{
    return (bool)(~(((SEC->FAC) & SEC_FAC_HSM_UKEY_RPROT_MASK) >> SEC_FAC_HSM_UKEY_RPROT_SHIFT));
}

/**
 * @brief Get HSM User Key Program Protection
 * @return  true - HSM Program access to User Key region is disabled
 *          false - HSM Program access to User Key region is enabled
 * */
LOCAL_INLINE bool SEC_HWA_GetHsmUKProg(void)
{
    return (bool)(~(((SEC->FAC) & SEC_FAC_HSM_UKEY_WPROT_MASK) >> SEC_FAC_HSM_UKEY_WPROT_SHIFT));
}

/**
 * @brief Get the HSM User Key Erase Protection
 * @return true - HSM erase access to User Key region is enabled
 *          false -HSM erase access to User Key region is disabled
 * */
LOCAL_INLINE bool SEC_HWA_GetHsmUKErase(void)
{
    return (bool)(~(((SEC->FAC) & SEC_FAC_HSM_UKEY_EPROT_MASK) >> SEC_FAC_HSM_UKEY_EPROT_SHIFT));
}

/**
 * @brief Get HSM NVR Key Read Protection
 * @return  true - HSM Read access to NVR key region is disabled
 *          false - HSM Read access to NVR key region is enabled
 * */
LOCAL_INLINE bool SEC_HWA_GetHsmNvrKRead(void)
{
    return (bool)(~(((SEC->FAC) & SEC_FAC_HSM_NVR_RPROT_MASK) >> SEC_FAC_HSM_NVR_RPROT_SHIFT));
}

/**
 * @brief Get HSM NVR Program Protection
 * @return  true - HSM Program access to NVR region is disabled
 *          false - HSM Program access to NVR region is enabled
 * */
LOCAL_INLINE bool SEC_HWA_GetHsmNvrProg(void)
{
    return (bool)(~(((SEC->FAC) & SEC_FAC_HSM_NVR_WPROT_MASK) >> SEC_FAC_HSM_NVR_WPROT_SHIFT));
}

/**
 * @brief Get the HSM NVR Erase Protection
 * @return true - HSM erase access to NVR region is enabled
 *          false -HSM erase access to NVR region is disabled
 * */
LOCAL_INLINE bool SEC_HWA_GetHsmNvrErase(void)
{
    return (bool)(~(((SEC->FAC) & SEC_FAC_HSM_NVR_EPROT_MASK) >> SEC_FAC_HSM_NVR_EPROT_SHIFT));
}

/* FLEXCORE_EN Bit Fields */
/**
 * @brief Get the FlexCore Enable.
 * @return true means enable ,false means disable.
 * */
LOCAL_INLINE bool SEC_HWA_GetFlexCoreEn(void)//?
{
    bool ret = false;
    uint8_t srk = (uint8_t)((SEC->FLEXCORE_EN & SEC_FLEXCORE_EN_FLEXCORE_EN_MASK) >> SEC_FLEXCORE_EN_FLEXCORE_EN_SHIFT);
    if (srk == 0xFU||srk == 0x5U)
    {
        ret = true;
    }
    return ret;
}
/**
 * @brief Set the FlexCore Enable.
 * @return true means set sucess ,false means set fail,0x5 and 0xf is enable,others is disable.
 * */
LOCAL_INLINE bool SEC_HWA_SetFlexCoreEn(uint8_t CoreEn)
{
	if(CoreEn>0xF)
		return false;
    SEC->FLEXCORE_EN = ((SEC->FLEXCORE_EN & (~SEC_FLEXCORE_EN_FLEXCORE_EN_MASK)) | SEC_FLEXCORE_EN_FLEXCORE_EN(CoreEn));
    return true;
}

/**
 * @brief Get SEC_FLEXCORE_EN FLEXCORE_DBG.
 * @return true means enable ,false means disable.
 * */
LOCAL_INLINE bool SEC_HWA_GetFlexCoreDbgEn(void)
{
    return (bool)((SEC->FLEXCORE_EN & SEC_FLEXCORE_EN_FLEXCORE_DBG_EN_MASK) >> SEC_FLEXCORE_EN_FLEXCORE_DBG_EN_SHIFT);
}

/**
 * @brief Set SEC_FLEXCORE_EN FLEXCORE_DBG.
 * */
LOCAL_INLINE void SEC_HWA_SetFlexCoreDbgEn(uint8_t DbgEn)
{
	SEC->FLEXCORE_EN=((SEC->FLEXCORE_EN & (~SEC_FLEXCORE_EN_FLEXCORE_DBG_EN_MASK)) | SEC_FLEXCORE_EN_FLEXCORE_DBG_EN(DbgEn));
}

/* FLEX_CODE_ADDR Bit Fields */
/**
 * @brief Get Code Header Address for FlexCore Always 4-byte aligned
 * @return FLEX Code Header Address.
 * */
LOCAL_INLINE uint32_t SEC_HWA_GetFlexCodeHeadAddr(void)
{
	return (uint32_t)((SEC->FLEX_CODE_ADDR & SEC_FLEX_CODE_ADDR_FLEX_CODE_ADDR_MASK) >> SEC_FLEX_CODE_ADDR_FLEX_CODE_ADDR_SHIFT);
}

/* PFLASH_PRLLL_EN Bit Fields */
/**
 * @brief Get PFLASH Parallel Enable
 * @return
 * 0101b - Disable
 * Others - Enable
 * */
LOCAL_INLINE bool SEC_HWA_GetPflashPrlllEn(void)
{
	bool ret = false;
	uint32_t srk=(uint32_t)((SEC->PFLASH_PRLLL_EN & SEC_PFLASH_PRLLL_EN_PFLASH_PRLLL_EN_MASK) >> SEC_PFLASH_PRLLL_EN_PFLASH_PRLLL_EN_SHIFT);
	if (srk !=0x5U)
	{
		ret =true ;
	}
	return ret;
}

/** @}*/ /* HwA_SEC */
#endif /* HWA_INCLUDE_HWA_SEC_H_ */
