/**
 * @file fc7xxx_driver_sec.h
 * @author Flagchip
 * @brief FC7xxx sec driver type definition and API
 * @version 0.2.0
 * @date 2023-2-7
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
*   0.2.0       2023-2-7    Flagchip076    N/A          First version for FC7300
********************************************************************************/


#ifndef _DRIVER_SEC_H_
#define _DRIVER_SEC_H_

#include "HwA_sec.h"
#include "device_header.h"

/**
 * @addtogroup fc7xxx_driver_sec
 * @{
 */

/**
 * @brief Debug Re-Enable Key
 * @note  Only if four 32-bit writes match, it will set the DEN to 0x5 to enable
    debug and unlock SEC registers. The key is up to the user to decide in advance.
 * */
typedef struct
{
    uint32_t Re_key0;           /*!< The Debug Re-enable key 0*/
    uint32_t Re_key1;           /*!< The Debug Re-enable key 1*/
    uint32_t Re_key2;           /*!< The Debug Re-enable key 2*/
    uint32_t Re_key3;           /*!< The Debug Re-enable key 3*/

} ReEnDebug_Keys;

typedef enum
{
	SEC_STATUS_SUCCESS = 0U,	/*!< SEC status success */
	SEC_STATUS_FAILED = 1U		/*!< SEC status failed */
}SEC_RetType;

/**
 * @brief NVR write and read Permissions.
 * @*/
typedef struct
{
    bool WritEn;                /*!< The NVR write permission*/
    bool ReadEn;                /*!< The NVR read permission*/
    bool EraseEn;               /*!< The NVR Erase permission*/
} NVR_Per;

/**
 * @brief Indicate the system state
 *
 * */
typedef enum
{
    Securedstate = 0u,          /*!< The system is in secured state*/
    UnSecuredstate = 1u         /*!< The system is in no secured state*/
} Systemstate;

/**
 * @brief Indicate the ISP instance
 *
 * */
typedef enum
{
	ISP_FCUART1 = 0U,			/*!< The ISP instance is FCUART1 */
	ISP_FCUART3 = 1U,			/*!< The ISP instance is FCUART3 */
	ISP_FLEXCAN1 = 2U,			/*!< The ISP instance is FLEXCAN1 */
	ISP_FLEXCAN5 = 3U			/*!< The ISP instance is FLEXCAN3 */
}Isp_Instance;

/**
 * @brief Indicate the FCUART Baud Rate for ISP
 *
 * */
typedef enum
{
	ISP_FCUART_2MBPS =0u,		/*!< the FCUART Baud Rate is  2Mbps*/
	ISP_FCUART_1MBPS =1u,		/*!< the FCUART Baud Rate is  1Mbps*/
	ISP_FCUART_512KBPS =2u,		/*!< the FCUART Baud Rate is  512kbps*/
	ISP_FCUART_115200BPS =3u,	/*!< the FCUART Baud Rate is  115200bps*/
	ISP_FCUART_INVALID = 4u		/*!< the ISP instance is not FCUART*/
}FCUART_ISP_BAUDRATE;

/**
 * @brief Indicate the FLEXCAN Baud Rate for ISP
 *
 * */
typedef enum
{
	ISP_FLEXCANFD_4MBPS =0u,		/*!< the CANFD Baud Rate is  4Mbps*/
	ISP_FLEXCANFD_2MBPS =1u,		/*!< the CANFD Baud Rate is  2Mbps*/
	ISP_FLEXCAN_1MBPS =2u,			/*!< the CAN Baud Rate is  1Mbps*/
	ISP_FLEXCAN_500kBPS =3u,		/*!< the FCUART Baud Rate is  500kbps*/
	ISP_FLEXCAN_INVALID = 4u		/*!< the ISP instance is not FLEXCAN*/
}FLEXCAN_ISP_BAUDRATE;

/**
 * @brief Indicate the ISP information.
 *
 * */
typedef struct
{
	bool IspModeEn;        						/*!<  true means - ISP mode is active.*/
	bool IspPinEn; 								/*!<  true means - ISP pin is active.The associated pin defaults to internal pull up enabled.*/
	bool IspAuthEn;								/*!<*true means - ISP Auth Enable. Only valid in secure boot. (Value loaded from NVR sector)*/
	Isp_Instance Ispinstance;					/*!<  the Isp instance*/
	FCUART_ISP_BAUDRATE  Ispfcuartbaudrate;		/*!<  Indicate the FCUART Baud Rate for ISP*/
	FLEXCAN_ISP_BAUDRATE Ispflexcanbaudrate;	/*!<  Indicate the FLEXCAN Baud Rate for ISP*/

}SEC_IspInfo;

/**
 * @brief Indicate the fast boot speed.
 *
 * */
typedef enum
{
	FASTBOOT_300MHZ = 0u,						/*!< Select PLL0 as the core clock source; the core clock is 300MHz.*/
	FASTBOOT_96MHZ = 1u						    /*!< Select FIRC as the core clock source; the core clock is 96MHz.*/
}FastBoot_Speed;

/**
 * @brief Indicate the OSC Frequency
 *
 * */
typedef enum
{
	OSC_8MHZ = 0u,								/*!<OSC Frequency is 8 MHZ*/
	OSC_12MHZ = 1u,								/*!<OSC Frequency is 12 MHZ*/
	OSC_16MHZ = 2u,								/*!<OSC Frequency is 16 MHZ*/
	OSC_24MHZ = 3u,								/*!<OSC Frequency is 24 MHZ*/
	OSC_25MHZ = 4u,								/*!<OSC Frequency is 25 MHZ*/
	OSC_32MHZ = 5u,								/*!<OSC Frequency is 32 MHZ*/
	OSC_48MHZ =	6u,								/*!<OSC Frequency is 48 MHZ*/
	OSC_40MHZ = 7u								/*!<OSC Frequency is 40 MHZ*/

}Osc_FreqInfo;

/**
 * @brief Indicate the lifecycle of the chip.
 *
 * */
typedef enum
{
	LIFECYCLE_INVALID = 0U,						/*!<no Lifcycle */
	LIFECYCLE_OEM_DEV = 0X1U,					/*!<Lifcycle OEM Development*/
	LIFECYCLE_OEM_PDT = 0X2U,					/*!<Lifcycle OEM  Production*/
	LIFECYCLE_INFIELD = 0X4U,					/*!<Lifcycle In Field*/
	LIFECYCLE_PREFA   = 0X8U,					/*!<Lifcycle Pre Fault Analysis*/
	LIFECYCLE_FA 	  = 0X10U					/*!<Lifcycle Analysis*/
}SC_LifeCycle;

/**
 * @brief Indicate the boot information.
 *
 * */
typedef struct
{
	bool BootRom; 								/*!<  true means -  boot from rom.*/
	bool NmiPinEn;								/*!<  true means - nmi pin is active.The associated pin defaults to internal pull up enabled.*/
	bool SecBootEn;								/*!<  true means - secure boot enable  false means no secure boot mode..*/
	bool OscEn;									/*!<  true means -  OSC is available.*/
	FastBoot_Speed FastBootSpeed;				/*!<  the fast boot speed.*/
	Osc_FreqInfo OscFreq;						/*!<Indicate the OSC Frequency*/

}SEC_BootInfo;

/**
 * @brief Indicate the Host User Key Read/Write/Erase Protection
 *
 * */
typedef struct
{
	bool HostUKReadEn;						/*!<  true means  - Host read access to User Key region is enabled.*/
	bool HostUKWriteEn;						/*!<  true means  - Host write access to User Key region is enabled.*/
	bool HostUKEraseEn;						/*!<  true means  - Host eraseaccess to User Key region is enabled.*/
}HostUKPermission;

/**
 * @brief Indicate the Host NVR Read/Write/Erase Protection
 *
 * */
typedef struct
{
	bool HostNVRReadEn;						/*!<  true means  - Host read access to NVRregion is enabled.*/
	bool HostNVRWriteEn;						/*!<  true means  - Host write access to NVR region is enabled.*/
	bool HostNVREraseEn;						/*!<  true means  - Host eraseaccess to NVR region is enabled.*/
}HostNVRPermission;

/**
 * @brief Indicate the Bootloader Verification Algorithm
 *
 * */
typedef enum
{
	BL_ALGORITHM_CMAC = 0U,						/*!<  the Bootloader Verification Algorithm is CMAC*/
	BL_ALGORITHM_ECC256_SHA256 = 1U,			/*!<  the Bootloader Verification Algorithm is ECC256/SHA256*/
	BL_ALGORITHM_SM2_SM3 = 7U					/*!<  the Bootloader Verification Algorithm is SM2/SM3*/
}BL_VerifyAlgorithm;

/**
 * @brief Indicate the Debug/ISP/PREFA Authentication and USRK decryption algorithm
 *
 * */
typedef enum
{
	DECRYPTTION_ECC256 = 0U,					/*!< the Debug/ISP/PREFA Authentication and USRK decryption algorithm is ecc256*/
	DECRYPTTION_SM2 = 1U,						/*!< the Debug/ISP/PREFA Authentication and USRK decryption algorithm is sm2*/
}Decryption_Algorithm;

/**
 * @brief This function can be used to enable the Debug mode.
 * @return  true means enable debug success ,false means enable debug failed.
 * */
bool SEC_EnDebugMode(void);

/**
 * @brief This function can be used to  re-enable the Debug mode by the re-enable keys.
 * @param keys  The Debug mode re-enable keys.The key is up to the user to decide in advance.
 * @return true means re-enable success,false means re-enable failed.
 * */
bool SEC_ReEnDebugMode(ReEnDebug_Keys keys);

/**
 * @brief This function can get the system state (secured or no secured).
 * */
Systemstate SEC_SystemSecureState(void);

/**
 * @brief This function can enable the test mode.
 * @return true means enable test mode success,false means enable test mode failed.
 * */
bool SEC_EnTestMode(void);

/**
 *@brief This function can Re-enable the test mode by the re-enable key.
 *@param key The test mode re-enable key.
 *@return true means re-enable success,false means re-enable failed.
 * */
bool SEC_ReEnTestMode(uint32_t key);

/**
 * @brief This function can used to set the NVR write and read permission.
 * @return true means setPer success,false means setPer failed.
 * */
bool SEC_SetNvrPer(NVR_Per per);

/**
 * @brief Get Secure Boot Enable Status
 *
 * @return true is enable and false is disable
 */
bool SEC_GetSecureStatus(void);

/**
 * @brief Get ISP Status
 *
 * @return true is active and false is inactive
 */
bool SEC_GetISPModeStatus(void);

/**
 * @brief Get User setting bootloader address
 *
 * @return bootloader address
 */
uint32_t SEC_GetBootAddress(void);

/**
 * @brief Get the lifecycle.
 *
 * @return the lifecycle.
 */
SC_LifeCycle SEC_GetLifeCycle(void);

/**
 * @brief User Key Access Enable. Only valid under non-secure boot
 * @return true means User key can be read/programmed/erased by host CPU
 * */
bool SEC_HostUKAccess(void);

/**
 * @brief get the Bootloader Verification Algorithm
 *	@return the Bootloader Verification Algorithm
 * */
BL_VerifyAlgorithm SEC_GetBLVerifyAlgorithm(void);

/**
 * @brief get the Debug/ISP/PREFA Authentication and USRK decryption algorithm
 *	@return decryption algorithm
 * */
Decryption_Algorithm SEC_GetDecryptAlgorithm(void);

/**
 * @brief Indicate the Host User Key Read/Write/Erase Protection
 * @param PHostUKAccess the structure for information
 * */
void SEC_GetHostUKAccess(HostUKPermission *const PHostUKAccess);

/**
 * @brief Indicate the Host NVR Read/Write/Erase Protection
 * @param PHostNvrAccess the structure for information
 * */
void SEC_GetHostNVRAccess(HostNVRPermission *const PHostNvrAccess);

/**
 * @brief Get the HSM User Key Erase Protection
 * @return true - HSM erase access to User Key region is enabled
 *          false -HSM erase access to User Key region is disabled
 * */
bool SEC_GethsmUKEraseAccess(void);

/**
 * @brief Get the HSM NVR Erase Protection
 * @return true - HSM erase access to NVR region is enabled
 *          false -HSM erase access to NVR region is disabled
 * */
bool SEC_GethsmNVREraseAccess(void);

/**
 * @brief Get Bootloader Verification Mask
 * @return Bootloader Verification Mask.
 * */
uint32_t SEC_GetBLVerMask(void);

/**
 * @brief Get whether Debug Mailbox Backdoor Key Enable.
 * @return  true means  user can enable debug by writing debug backdoor key, false means user can  not enable debug
 * */
uint32_t SEC_GetDMBDkeyEn(void);

/**
 * @brief Host Debug Auth Enable. Only valid in secure boot. (Value loaded from NVR sector)
 * @return  true means Host debug authentication enable. false means Host debug authentication disable.
 */
bool SEC_GetDebugAuthEn(void);

/**
 * @brief Get the isp information.
 * @param pIspInfo the structure for information
 * @return Get whether operation is success.
 *
 * */
SEC_RetType SEC_GetIspInfo(SEC_IspInfo *const pIspInfo);

/**
 * @brief Get the boot information.
 * @param pBootInfo the structure for information.
 * @return Get whether operation is success.
 *
 * */
SEC_RetType SEC_GetBootInfo(SEC_BootInfo *const pBootInfo);



/** @}*/ /* fc4xxx_driver_sec */

#endif /* end of _DRIVER_SEC_H_ */
