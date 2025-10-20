/**
 * @file fc7xxx_driver_hsm.c
 * @author Flagchip0103
 * @brief FC7xxx HSM driver source file
 * @version 0.1.0
 * @date 2023-12-20
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0      2023-12-20    Flagchip0103   N/A          First version for FC7240
   ******************************************************************************** */

#include "fc7xxx_driver_hsm.h"

/* ################################################################################## */
/* ##################################### Macros ##################################### */

typedef enum {
    HSM_CMD_ID_TRNG                         = 0xb55du,
    HSM_CMD_ID_SHA                          = 0xfce2u,
    HSM_CMD_ID_ECC_SIGN                     = 0xde41u,
    HSM_CMD_ID_ECC_VERIFY                   = 0xa522u,
    HSM_CMD_ID_SM2_GENKEYPAIR               = 0xc9ddu,
    HSM_CMD_ID_SM2_ENCRY                    = 0x30f1u,
    HSM_CMD_ID_SM2_DECRY                    = 0x6351u,
    HSM_CMD_ID_SM2_SIGN                     = 0xe814u,
    HSM_CMD_ID_SM2_VERIFY                   = 0x6e1eu,
    HSM_CMD_ID_SM2_GENZA                    = 0xdbbeu,
    HSM_CMD_ID_SM2_GENHASH                  = 0x5ce5u,
    HSM_CMD_ID_SM4_ENCRY                    = 0xfd5au,
    HSM_CMD_ID_SM4_DECRY                    = 0x4aedu,
    HSM_CMD_ID_ECC_ENCRY                    = 0x4d3fu,
    HSM_CMD_ID_ECC_DECRY                    = 0x97e4u,
    HSM_CMD_ID_REQUEST_AUTH                 = 0x33d9u,
    HSM_CMD_ID_LIFECYCLE_CHANGE             = 0xbe63u, /* prefa,fa not support in sdk */
    HSM_CMD_ID_DEBUG_AUTH                   = 0x3928u, // TODO: delete
    HSM_CMD_ID_ISP_AUTH                     = 0xAFBAu, // TODO: delete
    HSM_CMD_ID_REVOKE_MRK                   = 0x19bbu, // TODO: delete
    HSM_CMD_ID_REVOKE_UMRK                  = 0xfdb4u, // TODO: delete
    HSM_CMD_ID_USER_KEY_ERASE               = 0xac3au, // TODO: delete
    HSM_CMD_ID_FLASHTEST_VERIFY             = 0xcc29u, // TODO: delete
    HSM_CMD_ID_UESR_CODE_VERIFY             = 0x72d6u, // TODO: delete
    HSM_CMD_ID_CANCEL_JOB                   = 0x17c3u,
    HSM_CMD_ID_SELF_TEST                    = 0x4e93u,
    HSM_CMD_ID_NVR_OTP                      = 0x2cd8u,
    HSM_CMD_ID_LIFECYCLE_CHANGE_TAKE_EFFECT = 0x30fau,
    HSM_CMD_ID_USER_KEY_MANAGE              = 0xf4cfu,
    HSM_CMD_ID_SPACE_MANAGE                 = 0x4ac0u,
    HSM_CMD_ID_AES_ENCRY                    = 0xa2c6u,
    HSM_CMD_ID_AES_DECRY                    = 0x6576u,
    HSM_CMD_ID_CMAC_GEN                     = 0xf0b9u,
    HSM_CMD_ID_XMAC_GEN                     = 0x32acu,
    HSM_CMD_ID_CCM_ENCRY                    = 0x862fu,
    HSM_CMD_ID_CCM_DECRY                    = 0x79a4u,
    HSM_CMD_ID_GCM_ENCRY                    = 0xd1a6u,
    HSM_CMD_ID_GCM_DECRY                    = 0xc0a3u,
    HSM_CMD_ID_MD5                          = 0x9371u,
    HSM_CMD_ID_SM3                          = 0xcfe5u,
    HSM_CMD_ID_MONOTONIC_COUNTER            = 0xdc97u,
    HSM_CMD_ID_RSA                          = 0x866cu,
    HSM_CMD_ID_USRK_GEN                     = 0xddb7u, // TODO: delete
    HSM_CMD_ID_LOAD_FIRMWARE                = 0x503du,
    HSM_CMD_ID_DH_SM                        = 0x7F8Au,
    HSM_CMD_ID_ECDH                         = 0x4b06u,
    HSM_CMD_ID_DH                           = 0xb81bu,
    HSM_CMD_ID_DH_PBKDF2                    = 0xa47du,
    HSM_CMD_ID_DH_GMPBKDF                   = 0xbe1fu,
    HSM_CMD_ID_SCATTER_HASH                 = 0x465du,
    HSM_CMD_ID_RAW_AESM                     = 0x42fdu,
    HSM_CMD_ID_SCATTER_MAC                  = 0xa9e1u,
    HSM_CMD_ID_ECC_GENKEYPAIR               = 0x16b6u,
    HSM_CMD_ID_RSA_SSA_PKCS1V15_SIGN        = 0xd047u,
    HSM_CMD_ID_RSA_SSA_PSS_SIGN             = 0xd873u,
    HSM_CMD_ID_RSA_ES_PKCS1V15_ENCRYPT      = 0x3090u,
    HSM_CMD_ID_RSA_ES_OAEP_ENCRYPT          = 0x7F0Bu,
    HSM_CMD_ID_RSA_SSA_PKCS1V15_VERIFY      = 0x1577u,
    HSM_CMD_ID_RSA_SSA_PSS_VERIFY           = 0x0076u,
    HSM_CMD_ID_RSA_ES_PKCS1V15_DECRYPT      = 0x26d5u,
    HSM_CMD_ID_RSA_ES_OAEP_DECRYPT          = 0xc284u,
} HSM_CmdIdType;

#define HSMCOM_TRNG_SRC_0                       0x40cau
#define HSMCOM_TRNG_SRC_1                       0xc51cu
#define HSMCOM_TRNG_SRC_ANY                     0x359bu
#define HSMCOM_TRNG_SRC_XOR                     0x80a5u
#define HSMCOM_DRNG_SRC                         0x648Cu
#define HSMCOM_LIFECYCLE_OEM_DEV                0x4792u
#define HSMCOM_LIFECYCLE_OEM_PDT                0xA4F1u
#define HSMCOM_LIFECYCLE_IN_FIELD               0xaddcu
#define HSMCOM_INCREASE_COUNTER                 0xd27fu
#define HSMCOM_READ_COUNTER                     0x1875u
#define HSMCOM_SET_COUNTER_VAL                  0x439du
#define HSMCOM_INCREASE_COUNTER_WHEN_EQUAL      0x6834u
#define HSMCOM_READ_ALL_FLEX_COUNTERS           0x6a47u
#define HSMCOM_SET_SINGLE_CFG                   0x9e4du
#define HSMCOM_GET_SINGLE_CFG                   0xaf42u
#define HSMCOM_INCREASE_COUNTER2                0xd280u
#define HSMCOM_READ_COUNTER2                    0x1876u
#define HSMCOM_NVR_OTP_READ                     0x9C2Fu
#define HSMCOM_NVR_OTP_WRITE                    0x358Cu
#define HSMCOM_KEYMANAGER_IMPORT_USER_KEY       0xdcf1u
#define HSMCOM_KEYMANAGER_REVOKE_USER_KEY       0x7278u
#define HSMCOM_KEYMANAGER_EXPORT_USER_KEY       0xd8c9u
#define HSMCOM_KEYMANAGER_GEN_UESR_KEY          0x1853u
#define HSMCOM_KEYMANAGER_ENABLE_KEY_RAM_COPY   0x5ec5u
#define HSMCOM_KEYMANAGER_DISABLE_KEY_RAM_COPY  0x5918u
#define HSMCOM_KEYSPACE_GET_STATUS              0xe39cu
#define HSMCOM_KEYSPACE_NEATEN                  0xb12bu
#define HSMCOM_REVOK_UMRK0                      0x5edcu
#define HSMCOM_REVOK_UMRK1                      0x20d9u
#define HSMCOM_REVOK_UMRK2                      0x6ba1u
#define HSMCOM_REVOK_UMRK3                      0xac50u

/* ################################################################################## */
/* ################################# Local Variables ################################ */
#define AUTH_CHECK_DATA_BYTE_CNT 32
static uint32_t s_aHsmDat[8];
static HSMCom_AuthCheckType s_tHsmDummyCfg = {0, 0, &(s_aHsmDat[0]), &(s_aHsmDat[0]), &(s_aHsmDat[0]), &(s_aHsmDat[0]), &(s_aHsmDat[0]), AUTH_CHECK_DATA_BYTE_CNT};

/* ################################################################################## */
/* ########################### Local Functions Prototype ############################ */

/* ################################################################################## */
/* ################################# Local Functions ############################### */
static HSM_StatusType hsm_assign_val(HSM_CmdType *pCmd, uint32_t u32Cmd, uint32_t u32Address)
{
    HSM_StatusType eRet = HSM_STATUS_SUCCESS;

    if (NULL != pCmd)
    {
        pCmd->u32Cmd  = u32Cmd;
        pCmd->u32Addr = u32Address;
    }
    else
    {
        eRet = HSM_STATUS_PARAM_ERR;
    }

    return eRet;
}

/* ################################################################################## */
/* ################################# Global Functions ############################### */
HSM_StatusType HSM_TrueRandGetSrc0(HSM_CmdType *pCmd, const HSMCom_TrueRandType*pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_TRNG << 16u) | HSMCOM_TRNG_SRC_0, (uint32_t)pCfg);
}

HSM_StatusType HSM_TrueRandGetSrc1(HSM_CmdType *pCmd, const HSMCom_TrueRandType*pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_TRNG << 16u) | HSMCOM_TRNG_SRC_1, (uint32_t)pCfg);
}

HSM_StatusType HSM_TrueRandGetSrcXor(HSM_CmdType *pCmd, const HSMCom_TrueRandType*pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_TRNG << 16) | HSMCOM_TRNG_SRC_XOR, (uint32_t)pCfg);
}

HSM_StatusType HSM_TrueRandGet(HSM_CmdType *pCmd, const HSMCom_TrueRandType*pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_TRNG << 16) | HSMCOM_TRNG_SRC_ANY, (uint32_t)pCfg);
}

HSM_StatusType HSM_PseudoRandGet(HSM_CmdType *pCmd, const HSMCom_TrueRandType*pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_TRNG << 16) | HSMCOM_DRNG_SRC, (uint32_t)pCfg);
}

HSM_StatusType HSM_Sha(HSM_CmdType *pCmd, const HSMCom_ShaType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SHA << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_ShaEx(HSM_CmdType *pCmd, const HSMCom_Sha2Type *pCfg)
{
    uint32_t u32CtrBits = (pCfg->tCfg.eInputFmt & 0x1) | ((pCfg->tCfg.eOutputFmt & 0x1) << 1);
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SHA << 16) | u32CtrBits, (uint32_t)pCfg);
}

HSM_StatusType HSM_HashInitEx(HSM_CmdType *pCmd, const HSMCom_ShaType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SCATTER_HASH << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_HashUpdateEx(HSM_CmdType *pCmd, const HSMCom_ShaType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SCATTER_HASH << 16) | 5u, (uint32_t)pCfg);
}

HSM_StatusType HSM_HashFinallyEx(HSM_CmdType *pCmd, const HSMCom_ShaType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SCATTER_HASH << 16) | 6u, (uint32_t)pCfg);
}

HSM_StatusType HSM_CmacAesm(HSM_CmdType *pCmd, const HSMCom_AesmRawApiType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_RAW_AESM << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_CmacScatter(HSM_CmdType *pCmd, const HSMCom_ScatterMacType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SCATTER_MAC << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_EccSign(HSM_CmdType *pCmd, const HSMCom_EccSignType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_ECC_SIGN << 16 | 1u), (uint32_t)pCfg);
}

HSM_StatusType HSM_EccVerify(HSM_CmdType *pCmd, const HSMCom_EccVerifyType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_ECC_VERIFY << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_EccGenKeyPair(HSM_CmdType *pCmd, const HSMCom_EccKeyPairGenType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_ECC_GENKEYPAIR << 16 | 1u), (uint32_t)pCfg);
}

HSM_StatusType HSM_Sm2GenKeyPair(HSM_CmdType *pCmd, const HSMCom_Sm2GenKeyPairType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SM2_GENKEYPAIR << 16 | 1u), (uint32_t)pCfg);
}

HSM_StatusType HSM_Sm2Encry(HSM_CmdType *pCmd, const HSMCom_Sm2EncryptType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SM2_ENCRY << 16 | 1u), (uint32_t)pCfg);
}

HSM_StatusType HSM_Sm2Decry(HSM_CmdType *pCmd, const HSMCom_Sm2DecryptType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SM2_DECRY << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_Sm2Sign(HSM_CmdType *pCmd, const HSMCom_Sm2SignType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SM2_SIGN << 16 | 1u), (uint32_t)pCfg);
}

HSM_StatusType HSM_Sm2Verify(HSM_CmdType *pCmd, const HSMCom_Sm2VerifyType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SM2_VERIFY << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_Sm2GenZa(HSM_CmdType *pCmd, const HSMCom_Sm2GenZaType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SM2_GENZA << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_Sm2GenHash(HSM_CmdType *pCmd, const HSMCom_Sm2GenHashType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SM2_GENHASH << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_Sm4Encrypt(HSM_CmdType *pCmd, const HSMCom_Sm4EncryptType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SM4_ENCRY << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_Sm4Decrypt(HSM_CmdType *pCmd, const HSMCom_Sm4DecryptType *pCfg)
{
    return hsm_assign_val(pCmd, (HSM_CMD_ID_SM4_DECRY << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_EccEasyEncry(HSM_CmdType *pCmd, const HSMCom_EccEasyEncryType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_ECC_ENCRY << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_EccEasyDecry(HSM_CmdType *pCmd, const HSMCom_EccEasyDecryType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_ECC_DECRY << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_EccPointCalc(HSM_CmdType *pCmd, const HSMCom_EccCalcType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_ECC_DECRY << 16) | 1u, (uint32_t)pCfg);
}

HSM_StatusType HSM_ScatterHashInit(HSM_CmdType *pCmd, const HSMCom_ScatterHashType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SCATTER_HASH << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_ScatterHashUpdate(HSM_CmdType *pCmd, const HSMCom_ScatterHashType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SCATTER_HASH << 16) | 5u, (uint32_t)pCfg);
}

HSM_StatusType HSM_ScatterHashFinally(HSM_CmdType *pCmd, const HSMCom_ScatterHashType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SCATTER_HASH << 16) | 6u, (uint32_t)pCfg);
}

HSM_StatusType HSM_RequestAuthorization(HSM_CmdType *pCmd, const HSMCom_RequestAuthType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_REQUEST_AUTH << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_OemDevEnter(HSM_CmdType *pCmd)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_LIFECYCLE_CHANGE << 16) | HSMCOM_LIFECYCLE_OEM_DEV, (uint32_t)(&s_tHsmDummyCfg));
}

HSM_StatusType HSM_OemPdtEnter(HSM_CmdType *pCmd)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_LIFECYCLE_CHANGE << 16) | HSMCOM_LIFECYCLE_OEM_PDT, (uint32_t)(&s_tHsmDummyCfg));
}

HSM_StatusType HSM_InFieldEnter(HSM_CmdType *pCmd)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_LIFECYCLE_CHANGE << 16) | HSMCOM_LIFECYCLE_IN_FIELD, (uint32_t)(&s_tHsmDummyCfg));
}

HSM_StatusType HSM_CancelJob(HSM_CmdType *pCmd, const HSMCom_CancelJobType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_CANCEL_JOB << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_SelfTest(HSM_CmdType *pCmd, const HSMCom_SelfTestType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SELF_TEST << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_NvrOtpProgram(HSM_CmdType *pCmd, const HSMCom_NvrOtpType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_NVR_OTP << 16) | HSMCOM_NVR_OTP_WRITE, (uint32_t)pCfg);
}

HSM_StatusType HSM_NvrOtpRead(HSM_CmdType *pCmd, const HSMCom_NvrOtpType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_NVR_OTP << 16) | HSMCOM_NVR_OTP_READ, (uint32_t)pCfg);
}

HSM_StatusType HSM_TakeEffect(HSM_CmdType *pCmd)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_LIFECYCLE_CHANGE_TAKE_EFFECT << 16), (uint32_t)0);
}

HSM_StatusType HSM_UserKeyRevoke(HSM_CmdType *pCmd, const HSMCom_UserKeyManageType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_USER_KEY_MANAGE << 16) | HSMCOM_KEYMANAGER_REVOKE_USER_KEY, (uint32_t)pCfg);
}

HSM_StatusType HSM_UserKeyImport(HSM_CmdType *pCmd, const HSMCom_UserKeyManageType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_USER_KEY_MANAGE << 16) | HSMCOM_KEYMANAGER_IMPORT_USER_KEY, (uint32_t)pCfg);
}

HSM_StatusType HSM_UserKeyExport(HSM_CmdType *pCmd, const HSMCom_UserKeyManageType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_USER_KEY_MANAGE << 16) | HSMCOM_KEYMANAGER_EXPORT_USER_KEY, (uint32_t)pCfg);
}

HSM_StatusType HSM_EraseKeyFlash(HSM_CmdType *pCmd, HSMCom_BasicType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_USER_KEY_ERASE << 16) | 0xa80f, (uint32_t)pCfg);
}

HSM_StatusType HSM_UserKeyGen(HSM_CmdType *pCmd, const HSMCom_UserKeyManageType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_USER_KEY_MANAGE << 16) | HSMCOM_KEYMANAGER_GEN_UESR_KEY, (uint32_t)pCfg);
}

HSM_StatusType HSM_EnableKeyRamCopy(HSM_CmdType *pCmd, const HSMCom_UserKeyManageType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_USER_KEY_MANAGE << 16) | HSMCOM_KEYMANAGER_ENABLE_KEY_RAM_COPY, (uint32_t)pCfg);
}

HSM_StatusType HSM_DisableKeyRamCopy(HSM_CmdType *pCmd, const HSMCom_UserKeyManageType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_USER_KEY_MANAGE << 16) | HSMCOM_KEYMANAGER_DISABLE_KEY_RAM_COPY, (uint32_t)pCfg);
}

HSM_StatusType HSM_GetKeySpaceStatus(HSM_CmdType *pCmd, const HSMCom_KeySpaceStatusType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SPACE_MANAGE << 16) | HSMCOM_KEYSPACE_GET_STATUS, (uint32_t)pCfg);
}

HSM_StatusType HSM_TidyUpKeySpace(HSM_CmdType *pCmd, const HSMCom_KeySpaceStatusType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SPACE_MANAGE << 16) | HSMCOM_KEYSPACE_NEATEN, (uint32_t)pCfg);
}

HSM_StatusType HSM_AesEncrypt(HSM_CmdType *pCmd, const HSMCom_AesEncryptType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_AES_ENCRY << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_Aes_FlexEncrypt(HSM_CmdType *pCmd, const HSMCom_FlexAesEncryptType *pCfg)
{
    uint32_t u32CtrBits =0x1 |
            ((pCfg->tCfg.epad & 0x1) << 1) | ((pCfg->tCfg.eInputFmt & 0x1) << 2) |
            ((pCfg->tCfg.eOutputFmt & 0x1) << 3) | ((pCfg->tCfg.eBackend & 0x1) << 4) ;
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_AES_ENCRY << 16) | u32CtrBits, (uint32_t)pCfg);
}

HSM_StatusType HSM_AesDecrypt(HSM_CmdType *pCmd, const HSMCom_AesDecryptType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_AES_DECRY << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_Aes_FlexDecrypt(HSM_CmdType *pCmd, const HSMCom_FlexAesDecryptType *pCfg)
{
    uint32_t u32CtrBits = 0x1 |
            ((pCfg->tCfg.epad & 0x1) << 1) | ((pCfg->tCfg.eInputFmt & 0x1) << 2) |
            ((pCfg->tCfg.eOutputFmt & 0x1) << 3) | ((pCfg->tCfg.eBackend & 0x1) << 4) ;
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_AES_DECRY << 16) | u32CtrBits, (uint32_t)pCfg);
}

HSM_StatusType HSM_CMac(HSM_CmdType *pCmd, const HSMCom_CMacType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_CMAC_GEN << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_CmacEx(HSM_CmdType *pCmd, const HSMCom_CMacExType *pCfg)
{
    uint32_t u32CtrBits = (pCfg->tCfg.eBackend & 0x1) | ((pCfg->tCfg.eInputFmt & 0x1) << 1) | ((pCfg->tCfg.eOutputFmt & 0x1) << 2);
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_CMAC_GEN << 16) | u32CtrBits, (uint32_t)pCfg);
}

HSM_StatusType HSM_XMac(HSM_CmdType *pCmd, const HSMCom_XMacType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_XMAC_GEN << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_XMacEx(HSM_CmdType *pCmd, const HSMCom_XMacExType *pCfg)
{
    uint32_t u32CtrBits = (pCfg->tCfg.eBackend & 0x1) | ((pCfg->tCfg.eInputFmt & 0x1) << 1) | ((pCfg->tCfg.eOutputFmt & 0x1) << 2);
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_XMAC_GEN << 16) | u32CtrBits, (uint32_t)pCfg);
}

HSM_StatusType HSM_CcmEncry(HSM_CmdType *pCmd, const HSMCom_CcmEncryptType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_CCM_ENCRY << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_CcmEncryEx(HSM_CmdType *pCmd, const HSMCom_CcmEncryptExType *pCfg)
{
    uint32_t u32CtrBits = (pCfg->tCfg.eBackend & 0x1);
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_CCM_ENCRY << 16) | u32CtrBits, (uint32_t)pCfg);
}

HSM_StatusType HSM_CcmDecry(HSM_CmdType *pCmd, const HSMCom_CcmDecryptType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_CCM_DECRY << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_CcmDecryEx(HSM_CmdType *pCmd, const HSMCom_CcmDecryptExType *pCfg)
{
    uint32_t u32CtrBits = (pCfg->tCfg.eBackend & 0x1);
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_CCM_DECRY << 16) |  u32CtrBits, (uint32_t)pCfg);
}

HSM_StatusType HSM_GcmEncry(HSM_CmdType *pCmd, const HSMCom_GcmEncryptType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_GCM_ENCRY << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_GcmEncryEx(HSM_CmdType *pCmd, const HSMCom_GcmEncryptExType *pCfg)
{
    uint32_t u32CtrBits = (pCfg->tCfg.eBackend & 0x1);
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_GCM_ENCRY << 16) | u32CtrBits, (uint32_t)pCfg);
}

HSM_StatusType HSM_GcmDecry(HSM_CmdType *pCmd, const HSMCom_GcmDecryptType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_GCM_DECRY << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_GcmDecryEx(HSM_CmdType *pCmd, const HSMCom_GcmDecryptExType *pCfg)
{
    uint32_t u32CtrBits = (pCfg->tCfg.eBackend & 0x1);
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_GCM_DECRY << 16) | u32CtrBits, (uint32_t)pCfg);
}

HSM_StatusType HSM_Md5(HSM_CmdType *pCmd, const HSMCom_Md5Type *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_MD5 << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_Md5Ex(HSM_CmdType *pCmd, const HSMCom_Md5Type *pCfg)
{
    uint32_t u32CtrBits = (pCfg->tCfg.eIntputFmt & 0x1) | ((pCfg->tCfg.eOutputFmt & 0x1) << 1);
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_MD5 << 16) | u32CtrBits, (uint32_t)pCfg);
}

HSM_StatusType HSM_Sm3(HSM_CmdType *pCmd, const HSMCom_Sm3Type *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SM3 << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_Sm3Ex(HSM_CmdType *pCmd, const HSMCom_Sm3Type *pCfg)
{
    uint32_t u32CtrBits = (pCfg->tCfg.eIntputFmt & 0x1) | ((pCfg->tCfg.eOutputFmt & 0x1) << 1);
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_SM3 << 16) | u32CtrBits, (uint32_t)pCfg);
}

HSM_StatusType HSM_MonotonicCounterIncrease(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_MONOTONIC_COUNTER << 16) | HSMCOM_INCREASE_COUNTER, (uint32_t)pCfg);
}

HSM_StatusType HSM_MonotonicCounterRead(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_MONOTONIC_COUNTER << 16) | HSMCOM_READ_COUNTER, (uint32_t)pCfg);
}

HSM_StatusType HSM_MonotonicCounterSetValue(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_MONOTONIC_COUNTER << 16) | HSMCOM_SET_COUNTER_VAL, (uint32_t)pCfg);
}

HSM_StatusType HSM_MonotonicIncCountWhenEqu(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_MONOTONIC_COUNTER << 16) | HSMCOM_INCREASE_COUNTER_WHEN_EQUAL, (uint32_t)pCfg);
}

HSM_StatusType HSM_MonotonicReadAllFlexCounters(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_MONOTONIC_COUNTER << 16) | HSMCOM_READ_ALL_FLEX_COUNTERS, (uint32_t)pCfg);
}

HSM_StatusType HSM_MonotonicCounterSetSingleCfg(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_MONOTONIC_COUNTER << 16) | HSMCOM_SET_SINGLE_CFG, (uint32_t)pCfg);
}

HSM_StatusType HSM_MonotonicCounterGetSingleCfg(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_MONOTONIC_COUNTER << 16) | HSMCOM_GET_SINGLE_CFG, (uint32_t)pCfg);
}

HSM_StatusType HSM_MonotonicIncreaseCounter2(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_MONOTONIC_COUNTER << 16) | HSMCOM_INCREASE_COUNTER2, (uint32_t)pCfg);
}

HSM_StatusType HSM_MonotonicReadCounter2(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_MONOTONIC_COUNTER << 16) | HSMCOM_READ_COUNTER2, (uint32_t)pCfg);
}

HSM_StatusType HSM_Rsa(HSM_CmdType *pCmd, const HSMCom_RsaType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_RSA << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_RSA_SSA_PSS_Sign(HSM_CmdType *pCmd, const HSMCom_RsaSsaPssSignType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_RSA_SSA_PSS_SIGN << 16), (uint32_t)pCfg);
}
HSM_StatusType HSM_RSA_SSA_PSS_Verify(HSM_CmdType *pCmd, const HSMCom_RsaSsaPssVerifyType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_RSA_SSA_PSS_VERIFY << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_RSA_SSA_ES_PKCS1V15_Encrypt(HSM_CmdType *pCmd, const HSMCom_RsaEsPkcs1V15EncryptType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_RSA_ES_PKCS1V15_ENCRYPT << 16), (uint32_t)pCfg);
}
HSM_StatusType HSM_RSA_SSA_ES_PKCS1V15_Decrypt(HSM_CmdType *pCmd, const HSMCom_RsaEsPkcs1V15DecryptType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_RSA_ES_PKCS1V15_DECRYPT << 16), (uint32_t)pCfg);
}
HSM_StatusType HSM_RSA_SSA_ES_PKCS1V15_Verify(HSM_CmdType *pCmd, const HSMCom_RsaSsaPkcs1V15VerifyType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_RSA_SSA_PKCS1V15_VERIFY << 16), (uint32_t)pCfg);
}
HSM_StatusType HSM_RSA_SSA_ES_PKCS1V15_Sign(HSM_CmdType *pCmd, const HSMCom_RsaSsaPkcs1V15SignType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_RSA_SSA_PKCS1V15_SIGN << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_RSA_SSA_ES_OAEP_Encrypt(HSM_CmdType *pCmd, const HSMCom_RsaEsOaepEncryptType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_RSA_ES_OAEP_ENCRYPT << 16), (uint32_t)pCfg);
}
HSM_StatusType HSM_RSA_SSA_ES_OAEP_Decrypt(HSM_CmdType *pCmd, const HSMCom_RsaEsOaepDecryptType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_RSA_ES_OAEP_DECRYPT << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_BigNumberCalc(HSM_CmdType *pCmd, const HSMCom_BigNumberCalcType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_RSA << 16) | 1u, (uint32_t)pCfg);
}

HSM_StatusType HSM_LoadFirmware(HSM_CmdType *pCmd)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_LOAD_FIRMWARE << 16), (uint32_t)0);
}

HSM_StatusType HSM_SMDH(HSM_CmdType *pCmd, HSMCom_SmDHType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_DH_SM << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_ECDH(HSM_CmdType *pCmd, HSMCom_ECDHType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_ECDH << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_DH(HSM_CmdType *pCmd, HSMCom_RsaDHType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_DH << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_PBKDF2(HSM_CmdType *pCmd, HSMCom_Pbkdf2Type *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_DH_PBKDF2 << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_GMPBKDF(HSM_CmdType *pCmd, HSMCom_GMpbkdfType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_DH_GMPBKDF << 16), (uint32_t)pCfg);
}

HSM_StatusType HSM_RevokeUmrk0(HSM_CmdType *pCmd)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_REVOKE_UMRK << 16)|HSMCOM_REVOK_UMRK0, (uint32_t)0);
}

HSM_StatusType HSM_RevokeUmrk1(HSM_CmdType *pCmd)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_REVOKE_UMRK << 16)|HSMCOM_REVOK_UMRK1, (uint32_t)0);
}

HSM_StatusType HSM_RevokeUmrk2(HSM_CmdType *pCmd)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_REVOKE_UMRK << 16)|HSMCOM_REVOK_UMRK2, (uint32_t)0);
}

HSM_StatusType HSM_RevokeUmrk3(HSM_CmdType *pCmd)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_REVOKE_UMRK << 16)|HSMCOM_REVOK_UMRK3, (uint32_t)0);
}

HSM_StatusType HSM_GenUsrk(HSM_CmdType *pCmd,const HSMCom_RsaType *pCfg)
{
    return hsm_assign_val(pCmd,(uint32_t)(HSM_CMD_ID_USRK_GEN << 16), (uint32_t)pCfg);
}
