/**
 * @file fc7xxx_driver_hsm.h
 * @author Flagchip0103
 * @brief FC7xxx HSM driver type definition and API
 * @version 0.1.0
 * @date 2023-12-20
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0      2023-12-20    Flagchip0103   N/A          First version for FC7240
   ******************************************************************************** */

#ifndef DRIVER_HSM_H_
#define DRIVER_HSM_H_

#include "device_header.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup fc7xxx_driver_hsm
 * @{
 */


/**
 * @brief Status returned by HSM SDK CM7 side APIs
 *
 */
typedef enum
{
    HSM_STATUS_SUCCESS = 0U,    /*!< return this when HSM API execute successfully */
    HSM_STATUS_PARAM_ERR,       /*!< return this when parameter error */
    HSM_STATUS_AGAIN,           /*!< return this when need more API call to continue process */
    HSM_STATUS_FINISH,          /*!< return this when the process is finish */
} HSM_StatusType;


/**
 * @name definitions for HSM_MailboxApiRetType
 *
 */
/**@{*/
/**
 * @brief success status (HSM_MailboxApiRetType) returned by HSM subsystem APIs
 *
 */
#define MAILBOXAPI_RET_SUCCESS          (0u)

/**
 * @brief error status (HSM_MailboxApiRetType) returned by HSM subsystem APIs
 *
 */
#define MAILBOXAPI_RET_ERROR            (1u)

/**
 * @brief failure status (HSM_MailboxApiRetType) returned by HSM subsystem APIs
 *
 */
#define MAILBOXAPI_RET_FAIL             (2u)

/**
 * @brief verify pass status (HSM_MailboxApiRetType) returned by HSM subsystem APIs
 *
 */
#define MAILBOXAPI_RET_PASS             (3u)

/**
 * @brief function not support status (HSM_MailboxApiRetType) returned by HSM subsystem APIs
 *
 */
#define MAILBOXAPI_RET_NOT_SUPPORT      (4u)

/**
 * @brief hardware error status (HSM_MailboxApiRetType) returned by HSM subsystem APIs
 *
 */
#define MAILBOXAPI_RET_HW_ERROR         (5u)

/**
 * @brief have no permission status (HSM_MailboxApiRetType) returned by HSM subsystem APIs
 *
 */
#define MAILBOXAPI_RET_NO_PRIVILEGES    (6u)

/**
 * @brief parameters error status (HSM_MailboxApiRetType) returned by HSM subsystem APIs
 *
 */
#define MAILBOXAPI_RET_PARAMETER_ERROR  (7u)

/**
 * @brief authority error status (HSM_MailboxApiRetType) returned by HSM subsystem APIs
 *
 */
#define MAILBOXAPI_RET_AUTHORITY_ERROR  (8u)

/**
 * @brief hardware busy status (HSM_MailboxApiRetType) returned by HSM subsystem APIs
 *
 */
#define MAILBOXAPI_RET_BUSY             (9u)

/**
 * @brief flash ecc error status (HSM_MailboxApiRetType) returned by HSM subsystem APIs
 *
 */
#define MAILBOXAPI_RET_ECC_ERR          (10u)

/**
 * @brief time expire error status (HSM_MailboxApiRetType) returned by HSM subsystem APIs
 *
 */
#define MAILBOXAPI_RET_TIMEOUIT         (11u)

/**
 * @brief status type definition returned by HSM subsystem APIs
 *
 */
typedef uint32_t HSM_MailboxApiRetType;
/**@}*/


/**
 * @brief HSM 4bytes unit data format for HSM_DataFormatType
 * for example, if data is 0x000102030405060708090a0b0c0d0e0f, use this format, should be divided as following.
 * 0x00010203, 0x04050607, 0x08090a0b, 0x0c0d0e0f
 */
#define HSM_DATA_FORMAT_4B    0u

/**
 * @brief HSM 1byte unit data format for HSM_DataFormatType
 * for example, if data is 0x000102030405060708090a0b0c0d0e0f, use this format, should be divided as following.
 * 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
 */
#define HSM_DATA_FORMAT_1B    1u

/**
 * @brief HSM  data format
 * refer to HSM_DATA_FORMAT_4B, HSM_DATA_FORMAT_1B
 */
typedef uint32_t HSM_DataFormatType;


/**
 * @name Type definition for HSM Isr/Poll mode
 *
 */
/**@{*/

typedef struct
{
    uint32_t u32Cmd;     /*!< current command id to HSM core via mailbox */
    uint32_t u32Addr;    /*!< current parameter address to HSM core via mailbox */
} HSM_CmdType;


/**
 * @name definitions for HSM_BoolType
 *
 */
/**@{*/
/**
 * @brief Boolean false value definition for type HSM_BoolType used by HSM
 *
 */
#define HSM_FALSE (0u)

/**
 * @brief Boolean true value definition for type HSM_BoolType used by HSM
 *
 */
#define HSM_TRUE  (1u)

/**
 * @brief Boolean type for HSM
 *
 */
typedef uint32_t HSM_BoolType;
/**@}*/


/* ------------------------------------------------------------------------------- */
/**
 * @brief the true random count return by the API
 *
 */
#define HSM_TRNG_RAND_U32_CNT (16u)
/* ------------------------------------------------------------------------------- */
/**
 * @brief the true random source_0 definition for type HSMCom_TrueRandType.u32RandSrcType
 *
 */
#define HSM_TRNG_SRC_0 (0u)
/* ------------------------------------------------------------------------------- */
/**
 * @brief the true random source_1 definition for type HSMCom_TrueRandType.u32RandSrcType
 *
 */
#define HSM_TRNG_SRC_1 (1u)
/* ------------------------------------------------------------------------------- */
/**
 * @brief the true XOR random source_1 definition for type HSMCom_TrueRandType.u32RandSrcType
 *
 */
#define HSM_TRNG_SRC_XOR (2u)
/* ------------------------------------------------------------------------------- */
/**
 * @brief the true any random source_1 definition for type HSMCom_TrueRandType.u32RandSrcType
 *
 */
#define HSM_TRNG_SRC_ANY (3u)
/* ------------------------------------------------------------------------------- */
/**
 * @brief the pseudorandom source definition for type HSMCom_TrueRandType.u32RandSrcType
 *
 */
#define HSM_DRNG_SRC (4u)
typedef uint32_t HSM_RndSrcType;
/**
 * @brief the true random information passed to HSM core by mailbox
 *
 */
typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet;  /*!< HSM core write return status value in this */
    uint32_t              u32Timeout;      /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t              (*aRandom)[HSM_TRNG_RAND_U32_CNT]; /*!< the buffer address, HSM core will write random data to this buffer */
    HSM_RndSrcType        u32RandSrc;  /*!< which random source will be selected */
} HSMCom_TrueRandType;

/* ------------------------------------------------------------------------------- */


/**
 * @name definitions for HSM_HashAlgType
 *
 */
/**@{*/
/**
 * @brief  MD5 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_MD5           (0U)

/**
 * @brief  SHA160 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SHA160        (1U)

/**
 * @brief  SHA224 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SHA224        (2U)

/**
 * @brief  SHA256 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SHA256        (3U)

/**
 * @brief  SHA384 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SHA384        (4U)

/**
 * @brief  SHA512 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SHA512        (5U)

/**
 * @brief  SHA512_224 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SHA512_224    (6U)

/**
 * @brief  SHA512_256 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SHA512_256    (7U)

/**
 * @brief  SM3 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SM3           (8U)

/**
 * @brief type definition for HASH algorithm
 * refer to HSM_HASH_MD5,HSM_HASH_SHA160,HSM_HASH_SHA224,HSM_HASH_SHA256,HSM_HASH_SHA384,HSM_HASH_SHA512,HSM_HASH_SHA512_224,HSM_HASH_SHA512_256,HSM_HASH_SM3
 */
typedef uint32_t HSM_HashAlgType;
/**@}*/


/**
 * @name definitions for HSM_ShaAlgType
 *
 */
/**@{*/
/**
 * @brief SHA160 algorithm value for type "HSM_ShaAlgType"
 * @note  it's the so-called SHA1
 */
#define HSM_SHA_160     (1U)

/**
 * @brief SHA224 algorithm value for type "HSM_ShaAlgType"
 * @note  it's the so-called SHA2-224
 */
#define HSM_SHA_224     (2U)

/**
 * @brief SHA256 algorithm value for type "HSM_ShaAlgType"
 * @note  it's the so-called SHA2-256
 */
#define HSM_SHA_256     (3U)

/**
 * @brief SHA384 algorithm value for type "HSM_ShaAlgType"
 * @note  it's the so-called SHA2-384
 */
#define HSM_SHA_384     (4U)

/**
 * @brief SHA512 algorithm value for type "HSM_ShaAlgType"
 * @note  it's the so-called SHA2-512
 */
#define HSM_SHA_512     (5U)

/**
 * @brief SHA512/224 algorithm value for type "HSM_ShaAlgType"
 * @note  it's the so-called SHA2-512/224
 */
#define HSM_SHA_512_224 (6U)

/**
 * @brief SHA512/256 algorithm value for type "HSM_ShaAlgType"
 * @note  it's the so-called SHA2-512/256
 */
#define HSM_SHA_512_256 (7U)

/**
 * @brief type definition for SHA algorithm
 * refer to HSM_SHA_160,HSM_SHA_224,HSM_SHA_256,HSM_SHA_384,HSM_SHA_512,HSM_SHA_512_224,HSM_SHA_512_256
 */
typedef uint32_t HSM_ShaAlgType;
/**@}*/


/**
 * @name definitions for HSM_HfamMacType
 *
 */
/**@{*/
/**
 * @brief SMAC mode value for type "HSM_HfamMacType"
 *
 */
#define HSM_HFAM_MAC_SMAC (0U)

/**
 * @brief HMAC mode value for type "HSM_HfamMacType"
 *
 */
#define HSM_HFAM_MAC_HMAC (1U)

/**
 * @brief SM3/MD5/SHA can generate MAC, use this to select the type of MAC
 * SMAC refer to HSM_HFAM_MAC_SMAC
 * HMAC refer to HSM_HFAM_MAC_HMAC
 */
typedef uint32_t HSM_HfamMacType;
/**@}*/


/**
 * @brief SHA/MD5/SM3 context information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_BoolType          bGenerateMacEn;          /*!< whether generate MAC */
    HSM_HfamMacType       eMacType;                /*!< if enable generating MAC, this should configure */
    uint32_t              *pKeyData;                /*!< key to generate MAC, if enable generating MAC, this should configure */
    uint32_t              u32KeyByteCnt;           /*!< the byte count of key data */
    uint32_t              u32GenerateMacByteCnt;   /*!< the byte count of MAC data output */

    uint32_t              u32InputDataByteCnt;     /*!< the byte count of input data */
    const uint32_t        *pInputData;              /*!< point to the input data */
} HSM_SmsCfgType; /* sms is short for sha/md5/sm3 */

/**
 * @brief SHA context information used by driver when call specific API
 *
 */
typedef HSM_SmsCfgType HSM_ShaCtxType;

/**
 * @brief type definition for driver to store information
 *
 */
typedef struct
{
    uint32_t              aResult[0x10]; /*!< store the sha result, max size 0x10 is for SHA512 */
    uint32_t              u32ResultU32Cnt; /*!< store the result uint32_t count, it's set by driver */
} HSM_ShaResultBufType;

/**
 * @brief SHA information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_ShaAlgType        eAlg; /*!< select sha algorithm type */
    HSM_ShaCtxType        tCfg; /*!< sha algorithm parameter set by user */
    HSM_ShaResultBufType  *pResult; /*!< point to the memory that HSM core to write result */
} HSM_ShaType;

typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t              u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    HSM_ShaType           tCfg; /*!< sha algorithm parameter set by user */
} HSMCom_ShaType;

/**
 * @brief SHA information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_ShaAlgType        eAlg; /*!< select sha algorithm type */
    HSM_ShaCtxType        tCfg; /*!< sha algorithm parameter set by user */
    uint8_t               *pResult; /*!< point to the memory that HSM core to write result */
    HSM_DataFormatType    eInputFmt; /*!< input data organized format,uint8_t array or uint32_t array */
    HSM_DataFormatType    eOutputFmt; /*!< output data organized format,uint8_t array or uint32_t array  */
} HSM_Sha2Type;

typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t              u32Timeout; /*!< current command timeout Millisecond count, max 916000ms, if set to 0, means 1000ms */
    HSM_Sha2Type          tCfg; /*!< sha algorithm parameter set by user */
} HSMCom_Sha2Type;

typedef struct
{
    HSM_ShaAlgType        eAlg; /*!< select sha algorithm type */
    HSM_ShaCtxType        tCfg; /*!< sha algorithm parameter set by user */
    uint32_t              (*pResult)[18]; /*!< point to the memory that HSM core to write result */
} HSM_ScatterHashType;

typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t              u32Timeout; /*!< current command timeout Millisecond count, max 916000ms, if set to 0, means 1000ms */
    HSM_ScatterHashType   tCfg; /*!< sha algorithm parameter set by user */
} HSMCom_ScatterHashType;
/* ------------------------------------------------------------------------------- */
typedef struct {
  uint32_t                u32KeyType;
  uint32_t                u32KeySel;
  uint32_t                *pKeyData;
} HSM_AesmKeyCfgType;

typedef struct {
  HSM_AesmKeyCfgType       *pKeyCfg;
  uint32_t                 u32KeyCfgEn;
  uint32_t                 u32AesMode;
  uint32_t                 u32AesAs;
  uint32_t                 u32AesEncDecrypt;
  uint32_t                 u32EngSel;
  uint32_t                 u32AhbEn;
  uint32_t                 u32IcvEn;
  uint32_t                 u32DataLen;
  uint32_t                 u32IcvLen;
  uint32_t                 u32AadLen;
  uint32_t                 *pInput;
  uint32_t                 *pOutput;
  uint32_t                 *pIvData;
  uint32_t                 u32DbgWait;
  uint32_t                 u32IvLen;
} HSM_AesmHwEntryCfgType;

typedef struct {
    HSM_AesmHwEntryCfgType tCfg;
    HSM_AesmKeyCfgType     tKeyCfg;
    uint32_t               (*pCtx)[16];
} HSM_AesmRawApiType;

typedef struct
{
    HSM_MailboxApiRetType  u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t               u32Timeout; /*!< current command timeout Millisecond count, max 916000ms, if set to 0, means 1000ms */
    uint32_t               u32UserKeyId;
    HSM_AesmRawApiType     tCfg; /*!<  algorithm parameter set by user */
} HSMCom_AesmRawApiType;

/* ------------------------------------------------------------------------------- */
typedef struct {
    uint32_t               u32Flags;
    uint32_t               *pKeyData;
    uint32_t               *pMacOut;
    uint32_t               u32MacOutBufSz;
    uint32_t               *aData[8];
    uint32_t               aDataSize[8];
} HSM_ScatterMacType;

typedef struct
{
    HSM_MailboxApiRetType  u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t               u32Timeout; /*!< current command timeout Millisecond count, max 916000ms, if set to 0, means 1000ms */
    uint32_t               u32UserKeyId;
    HSM_ScatterMacType     tCfg; /*!<  algorithm parameter set by user */
} HSMCom_ScatterMacType;


/* ------------------------------------------------------------------------------- */
/**
 * @name definitions for HSM_DrvEccCurvePrmIndexType
 *
 */
/**@{*/
/**
 * @brief ECC curve NIST SECP224R1 value for type "HSM_DrvEccCurvePrmIndexType"
 *
 */
#define HSM_DRV_ECC_CURVE_PRM_IDX_SECP224R1     (0U)

/**
 * @brief ECC curve NIST SECP256R1 value for type "HSM_DrvEccCurvePrmIndexType"
 *
 */
#define HSM_DRV_ECC_CURVE_PRM_IDX_SECP256R1     (1U)

/**
 * @brief ECC curve NIST SECP384R1 value for type "HSM_DrvEccCurvePrmIndexType"
 *
 */
#define HSM_DRV_ECC_CURVE_PRM_IDX_SECP384R1     (2U)

/**
 * @brief ECC curve NIST SECP521R1 value for type "HSM_DrvEccCurvePrmIndexType"
 *
 */
#define HSM_DRV_ECC_CURVE_PRM_IDX_SECP521R1     (3U)

/**
 * @brief ECC curve NIST SECP224R1_FIX value for type "HSM_DrvEccCurvePrmIndexType"
 *
 */
#define HSM_DRV_ECC_CURVE_PRM_IDX_SECP224R1_FIX (4U)


/**
 * @brief max count of ECC curve supported for type "HSM_DrvEccCurvePrmIndexType"
 *
 */
#define HSM_DRV_ECC_CURVE_PRM_IDX_MAX           (5U)

/**
 * @brief type definition for ECC curve data that defined by NIST
 *
 */
typedef uint32_t HSM_DrvEccCurvePrmIndexType;
/**@}*/

/**
 * @brief ECC curve information used by driver when call specific API
 *
 */
typedef struct
{
    const uint32_t *pP;     /*!< ecc curve modulus */
    const uint32_t *pN;     /*!< ecc curve order; size; the count of all possible EC points */
    const uint32_t *pA;     /*!< the constant "a" in y^2 = x^3 + a*x + b (mod p) */
    const uint32_t *pB;     /*!< the constant "b" in y^2 = x^3 + a*x + b (mod p) */
    const uint32_t *pGx;    /*!< x of the curve generator point G {x, y} */
    const uint32_t *pGy;    /*!< y of the curve generator point G {x, y} */
} HSM_DrvEccCurveParamType;

/**
 * @brief ECC sign information used by driver when call specific API
 *
 */
typedef struct
{
    uint32_t                    u32ByteCount;   /*!< all the data size, it should contains all N data */
    HSM_DrvEccCurveParamType    tCurve;         /*!< ecc curve parameters */
    const uint32_t             *pPrivateKey;    /*!< private key  */
    const uint32_t             *pHashData;      /*!< hash of the data to verify */

    /* the following the sign output */
    uint32_t *pR;                       /*!< driver internal use this buffer to store the sign result R of the data to sign */
    uint32_t *pS;                       /*!< driver internal use this buffer to store the sign result S of the data to sign */
} HSM_EccSignType;

typedef struct
{
    HSM_MailboxApiRetType       u32HSMStatusRet;            /*!< HSM core write return status value in this */
    uint32_t                    u32Timeout;                 /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                    u32UserKeyID_PrivateKey;    /*!< 0 means use key from HSM internal key space, otherwise would load key with KEYID from key space */
    uint32_t                    u32BitCnt;                  /*!< ECC parameter N bit count */
    HSM_DrvEccCurvePrmIndexType u32EccCurve;                /*!< select hsm rom internal ecc curve parameters, if use user's self curve, set it to HSM_DRV_ECC_CURVE_PRM_IDX_MAX */
    HSM_EccSignType             tCfg;                       /*!< ecc sign parameters */
} HSMCom_EccSignType;

/* ------------------------------------------------------------------------------- */
/**
 * @brief ECC verify information used by driver when call specific API
 *
 */
typedef struct
{
    uint32_t                 u32DataByteCnt;    /*!< the byte count of all ecc curve parameter */
    HSM_DrvEccCurveParamType tCurve;            /*!< ecc curve parameters */
    const uint32_t          *pkG_x;             /*!< public key axis x */
    const uint32_t          *pkG_y;             /*!< public key axis y */
    const uint32_t          *pHashData;         /*!< hash of the data to verify */
    const uint32_t          *pR;                /*!< the sign result R of the data to verify */
    const uint32_t          *pS;                /*!< the sign result S of the data to verify */
} HSM_EccVerifyType;
typedef struct
{
    HSM_MailboxApiRetType       u32HSMStatusRet;        /*!< HSM core write return status value in this */
    uint32_t                    u32Timeout;             /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                    u32UserKeyID_PublicKey; /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    uint32_t                    u32BitCnt;              /*!< ECC parameter N bit count */
    HSM_DrvEccCurvePrmIndexType u32EccCurve;            /*!< select hsm rom internal ecc curve parameters, if use user's self curve, set it to HSM_DRV_ECC_CURVE_PRM_IDX_MAX */
    HSM_EccVerifyType           tCfg;                   /*!< ecc verify parameters */
} HSMCom_EccVerifyType;

/* ------------------------------------------------------------------------------- */
/**
 * @brief SM2 key pair generation information used by driver when call specific API
 *
 */
typedef struct
{
    uint32_t (*pPrivateKey)[8];  /*!< private key */
    uint32_t (*pPublicKey_X)[8]; /*!< the public key X */
    uint32_t (*pPublicKey_Y)[8]; /*!< the public key Y */
} HSM_Sm2GenKeyPairType;

typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet;  /*!< HSM core write return status value in this */
    uint32_t              u32Timeout;       /*!< current command timeout tick count, tick refer to the HSM bus clock */
    HSM_Sm2GenKeyPairType tCfg;             /*!< sm2 generate key pair  parameters */
} HSMCom_Sm2GenKeyPairType;

/* ------------------------------------------------------------------------------- */
/**
 * @brief SM2 encrypt information used by driver when call specific API
 *
 */
typedef struct
{
    uint32_t u32SM2InputByteCnt;    /*!< the length should be <= 32bytes */
    uint32_t *pSM2OutputByteCnt;    /*!< driver internal will set output byte count in the memory this pointer point to */
    uint32_t *pInputData;           /*!< length should be more than u32SM2InputByteCnt, and must be 4bytes align */
    uint32_t (*pPublicKey_x)[8];    /*!< public key axis x data */
    uint32_t (*pPublicKey_y)[8];    /*!< public key axis y data */
    uint32_t *pOutputData;          /*!< length should be more than u32SM2InputByteCnt+97, and must be 4bytes align */
} HSM_Sm2EncryptType;

typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet;        /*!< HSM core write return status value in this */
    uint32_t                u32Timeout;             /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID_PublicKey; /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_Sm2EncryptType      tCfg;                   /*!< sm2 encrypt parameters */
} HSMCom_Sm2EncryptType;

/* ------------------------------------------------------------------------------- */
/**
 * @brief SM2 decrypt information used by driver when call specific API
 *
 */
typedef struct
{
    uint32_t u32SM2InputByteCnt;    /*!< the length should be <= 129bytes */
    uint32_t *pSM2OutputByteCnt;    /*!< driver internal will set output byte count in the memory this pointer point to */
    uint32_t *pInputData;           /*!< length should be more than u32SM2InputByteCnt, and must be 4bytes align */
    uint32_t (*pPrivateKey)[8];     /*!< private key */
    uint32_t *pOutputData;          /*!< length should be more than u32SM2InputByteCnt-97, and must be 4bytes align */
} HSM_Sm2DecryptType;

typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t                u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID_PrivateKey; /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_Sm2DecryptType      tCfg;
} HSMCom_Sm2DecryptType;

/* ------------------------------------------------------------------------------- */
/**
 * @brief SM2 sign information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_BoolType bUseDefaultID;     /*!< TRUE means use default ID. FALSE means use specific ID with "pInputData_ID" and "u32SM2InputIDByteCnt" params. */
    HSM_BoolType bHashInput;        /*!< TRUE means process hash message. FALSE means process raw M message */
    uint32_t     u32SM2InputMByteCnt;   /*!< the length should be <= 32bytes */
    uint32_t     u32SM2InputIDByteCnt;  /*!< the length should be <= 32bytes note: If "bUseDefaultID" is FALSE, would use this specific ID length with byte unit. */
    uint32_t     *pInputData_ID;        /*!< note: If "bUseDefaultID" is FALSE, would use this specific ID. length should be more than u32SM2InputIDByteCnt, and must be 4bytes align */
    uint32_t     *pInputData_MOrHash;   /*!< length should be more than u32SM2InputMOrHashByteCnt, and must be 4bytes align */
    uint32_t     (*pPrivateKey)[8];     /*!< private key */
    uint32_t     (*pPublicKey_X)[8];    /*!< If bHashInput is false, the pointer must be not NULL */
    uint32_t     (*pPublicKey_Y)[8];    /*!< If bHashInput is false, the pointer must be not NULL */
    uint32_t     (*pOutputData_R)[8];   /*!< sign result R */
    uint32_t     (*pOutputData_S)[8];   /*!< sign result S */
} HSM_Sm2SignType;

typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t                u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID_PublicKey; /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    uint32_t                u32UserKeyID_PrivateKey; /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_Sm2SignType         tCfg;
} HSMCom_Sm2SignType;

/* ------------------------------------------------------------------------------- */
/**
 * @brief SM2 verify information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_BoolType bUseDefaultID;     /*!< TRUE means use default ID. FALSE means use specific ID with "pInputData_ID" and "u32SM2InputIDByteCnt" params. */
    HSM_BoolType bHashInput;        /*!< TRUE means process hash message. FALSE means process raw M message */
    uint32_t     u32SM2InputMByteCnt;   /*!< the length should be <= 32bytes */
    uint32_t     u32SM2InputIDByteCnt;  /*!< the length should be <= 32bytes note: If "bUseDefaultID" is FALSE, would use this specific ID length with byte unit. */
    uint32_t     *pInputData_MOrHash;   /*!< length should be more than u32SM2InputMOrHashByteCnt, and must be 4bytes align */
    uint32_t     *pInputData_ID;        /*!< note: If "bUseDefaultID" is FALSE, would use this specific ID. length should be more than u32SM2InputIDByteCnt, and must be 4bytes align */
    uint32_t     (*pInputData_R)[8];    /*!< the sign result R */
    uint32_t     (*pInputData_S)[8];    /*!< the sign result S */
    uint32_t     (*pPublicKey_X)[8];    /*!< the public key X */
    uint32_t     (*pPublicKey_Y)[8];    /*!< the public key Y */
} HSM_Sm2VerifyType;

typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t                u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID_PublicKey; /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_Sm2VerifyType       tCfg; /*!< sm2 verify parameters */
} HSMCom_Sm2VerifyType;

/* ------------------------------------------------------------------------------- */
/**
 * @brief SM2 ZA generation information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_BoolType bUseDefaultID; /*!< TRUE means use default ID. FALSE means use specific ID with "pInputData_ID" and "u32SM2InputIDByteCnt" params. */
    uint32_t     u32SM2InputIDByteCnt;/*!< the length should be <= 32bytes  note: If "bUseDefaultID" is FALSE, would use this specific ID length with byte unit.*/
    uint32_t     (*pPublicKey_X)[8];
    uint32_t     (*pPublicKey_Y)[8];
    uint32_t     *pInputData_ID; /*!< note: If "bUseDefaultID" is FALSE, would use this specific ID. length should be more than u32SM2InputIDByteCnt, and must be 4bytes align */
    uint32_t     (*pOutputData_Za)[8]; /*!< Length is 32bytes, SM3 always output 256bit */
} HSM_Sm2GenZaType;

typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t              u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t              u32UserKeyID_PublicKey; /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_Sm2GenZaType      tCfg;
} HSMCom_Sm2GenZaType;
/* ------------------------------------------------------------------------------- */
/**
 * @brief SM2 HASH generation information used by driver when call specific API
 *
 */
typedef struct
{
    uint32_t u32InputDataByteCnt;       /*!< input data byte count */
    uint32_t *pInputData_ZaAndM;        /*!< note: it should be ZA||M, the length should be more than u32InputDataByteCnt, and must be 4bytes align */
    uint32_t (*pOutputData_Hash)[8];    /*!< Length is 32bytes, SM3 always output 256bit */
} HSM_Sm2GenHashType;

typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t              u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    HSM_Sm2GenHashType    tCfg;
} HSMCom_Sm2GenHashType;
/* ------------------------------------------------------------------------------- */
/**
 * @name definitions for HSM_Sm4KeyType
 *
 */
/**@{*/
/**
 * @brief vendor key value for type "HSM_Sm4KeyType"
 *
 * HSM hardware support accessing the SM4 key stored in nvr flash directly,
 * chip user should program the key in flash already.
 * This way don't need software read data and write it to some place,
 * hardware will read the data itself automatically.
 */
#define HSM_SM4_KEY_CHIP_VENDOR_IFR (0U) /* key has existed in Flash IFR, it provided by chip, not changeable */

/**
 * @brief driver user's new key value for type "HSM_Sm4KeyType"
 *
 * HSM use the key passed by driver API user.
 */
#define HSM_SM4_KEY_NEW             (1U) /* user should provide the new key */
typedef uint32_t HSM_Sm4KeyType;
/**@}*/

/**
 * @name definitions for HSM_Sm4EnDecryptAlgType
 *
 */
/**@{*/
/**
 * @brief SM4 CTR mode value for type "HSM_Sm4EnDecryptAlgType"
 *
 */
#define HSM_SM4_CTR (0U)

/**
 * @brief SM4 CBC mode value for type "HSM_Sm4EnDecryptAlgType"
 *
 */
#define HSM_SM4_CBC (1U)

/**
 * @brief SM4 ECB mode value for type "HSM_Sm4EnDecryptAlgType"
 *
 */
#define HSM_SM4_ECB (2U)

/**
 * @brief SM4 CFB mode value for type "HSM_Sm4EnDecryptAlgType"
 *
 */
#define HSM_SM4_CFB (3U)

/**
 * @brief SM4 OFB mode value for type "HSM_Sm4EnDecryptAlgType"
 *
 */
#define HSM_SM4_OFB (4U)

/**
 * @brief type definition for SM4 encrypt/decrypt mode
 *
 * HSM support CTR/CBC/ECB/CFB/OFB mode, driver api use this to select the encrypt/decrypt mode.
 */
typedef uint32_t HSM_Sm4EnDecryptAlgType;
/**@}*/

/**
 * @brief SM4 encrypt/decrypt information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_Sm4KeyType              eUseKeyType; /*!< the key source:vendor key programmed in nvr flash or new key in software */
    const uint32_t              (*pKeyAddr)[4]; /*!< when eUseKeyType is HSM_SM4_KEY_NEW, this MUST configure */
    HSM_Sm4EnDecryptAlgType     eSm4Alg; /*!< SM4 encrypt/decrypt mode */

    const uint32_t             *pDataInput;      /*!< address should align with 4bytes */
    uint32_t                    u32InputByteCnt; /*!< 128bit(16Bytes) align */
    uint32_t                   *pDataOutput; /*!< address should align with 4bytes */
    uint32_t                    u32OutputMemSize; /*!< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */

    uint32_t                    (*pIvData)[4]; /*!< 128bit(16Bytes) iv(initialization vector) data array, ECB not need configure this */
} HSM_Sm4EnDecryptType;

typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t                u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID; /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_Sm4EnDecryptType    tCfg;
} HSMCom_Sm4EnDecryptType;

typedef HSMCom_Sm4EnDecryptType HSMCom_Sm4DecryptType;

typedef HSMCom_Sm4EnDecryptType HSMCom_Sm4EncryptType;

typedef struct {
    HSMCom_Sm4EncryptType *pParam;
    uint32_t               u32Remain;
} HSMWrap_Sm4EncryptType;
/* ------------------------------------------------------------------------------- */
/**
 * @brief ECC encrypt information used by driver when call specific API
 *
 */
typedef struct
{
    uint32_t        u32ByteCount; /*!< all the data size, it should contains all N data */

    const uint32_t *pCoeffi_A; /*!< the constant "a" in y^2 = x^3 + a*x + b (mod p), all data 8 bytes aligned */
    const uint32_t *pCoeffi_B; /*!< the constant "b" in y^2 = x^3 + a*x + b (mod p) */
    const uint32_t *pP; /*!< ecc curve modulus */
    const uint32_t *pN; /*!< ecc curve order; size; the count of all possible EC points */
    const uint32_t *pOtherSidePublicKey_x; /*!< decrypt side's public key axis x data */
    const uint32_t *pOtherSidePublicKey_y; /*!< decrypt side's public key axis y data */
    const uint32_t *pPrivateKey; /*!< encrypt side private key */
    const uint32_t *pPlainData; /*!< data to be encrypted, its byte count should be same as u32ByteCount */

    uint32_t       *pEncryedData; /*!< driver internal write the result to this buffer */
} HSM_EccEasyEncryType;

typedef struct
{
    HSM_MailboxApiRetType       u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t                    u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                    u32UserKeyID_PrivateKey;/*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    uint32_t                    u32UserKeyID_PublicKey; /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    uint32_t                    u32BitCnt;
    HSM_DrvEccCurvePrmIndexType u32EccCurve;
    HSM_EccEasyEncryType        tCfg;
} HSMCom_EccEasyEncryType;

/* ------------------------------------------------------------------------------- */
/**
 * @brief ECC decrypt information used by driver when call specific API
 *
 */
typedef struct
{
    uint32_t       u32ByteCount; /*!< all the data size, it should contains all N data */
    const uint32_t *pCoeffi_A; /*!< the constant "a" in y^2 = x^3 + a*x + b (mod p), all data 8 bytes aligned */
    const uint32_t *pCoeffi_B; /*!< the constant "b" in y^2 = x^3 + a*x + b (mod p) */
    const uint32_t *pP; /*!< ecc curve modulus */
    const uint32_t *pN; /*!< ecc curve order; size; the count of all possible EC points */
    const uint32_t *pOtherSidePublicKey_x; /*!< encrypt side's public key axis x data */
    const uint32_t *pOtherSidePublicKey_y; /*!< encrypt side's public key axis y data */
    const uint32_t *pPrivateKey; /*!< decrypt side private key */
    const uint32_t *pEncryedData; /*!< data to be decrypted, its byte count should be same as u32ByteCount */
    uint32_t       *pPlainData; /*!< driver internal write the result to this buffer */
}  HSM_EccEasyDecryType;

typedef struct
{
    HSM_MailboxApiRetType       u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t                    u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                    u32UserKeyID_PrivateKey; /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    uint32_t                    u32UserKeyID_PublicKey; /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    uint32_t                    u32BitCnt;
    HSM_DrvEccCurvePrmIndexType u32EccCurve;
    HSM_EccEasyDecryType        tCfg;
} HSMCom_EccEasyDecryType;
/* ------------------------------------------------------------------------------- */
/**
 * @brief ECC generate key pair information used by driver when call specific API
 *
 */
typedef struct
{
    uint32_t                 u32ByteCount; /*!< all the data size, it should contains all N data */
    HSM_DrvEccCurveParamType tEccParam;
    uint32_t                 *pPrivateKey; /*!< decrypt side private key */
    uint32_t                 *pPublicKey_x; /*!< encrypt side's public key axis x data */
    uint32_t                 *pPublicKey_y; /*!< encrypt side's public key axis y data */
}  HSM_EccKeyPairGenType;

typedef struct
{
    HSM_MailboxApiRetType       u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t                    u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                    u32Bitcnt; /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_DrvEccCurvePrmIndexType u32EccCurve;
    HSM_EccKeyPairGenType       tCfg;
} HSMCom_EccKeyPairGenType;
/* ------------------------------------------------------------------------------- */


#define HSM_ECC_CALC_PADD  0xFC73F800
#define HSM_ECC_CALC_PDBL  0xFC73F801
#define HSM_ECC_CALC_PMUL  0xFC73F802
#define HSM_ECC_CALC_PCHK  0xFC73F803

/**
 * @brief ECC point calclulate used by driver when call specific API
 *
 */
typedef struct
{
    uint32_t       u32ByteCount; /*!< all the data size, it should contains all N data */
    const uint32_t *pCoeffi_A; /*!< address should align with 4bytes, the constant "a" in y^2 = x^3 + a*x + b (mod p), all data 8 bytes aligned */
    const uint32_t *pCoeffi_B; /*!< address should align with 4bytes, the constant "b" in y^2 = x^3 + a*x + b (mod p) */
    const uint32_t *pP; /*!< address should align with 4bytes, ecc curve modulus */
    const uint32_t *pN; /*!< address should align with 4bytes, ecc curve order; size; the count of all possible EC points */
    const uint32_t *pP1x; /*!< address should align with 4bytes, encrypt side's public key axis x data */
    const uint32_t *pP1y; /*!< address should align with 4bytes, encrypt side's public key axis y data */
    const uint32_t *pE; /*!< address should align with 4bytes, decrypt side private key */
    const uint32_t *pP2x; /*!< address should align with 4bytes, data to be decrypted, its byte count should be same as u32ByteCount */
    uint32_t       *pResultx; /*!< address should align with 4bytes, driver internal write the result to this buffer */
    uint32_t        u32CalcType;
    const uint32_t *pP2y;
    uint32_t       *pResulty;
}  HSM_EccCalcType;

typedef struct
{
    HSM_MailboxApiRetType       u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t                    u32Timeout; /*!< current command timeout Millisecond count, max 916000ms, if set to 0, means 1000ms */
    uint32_t                    u32UserKeyID_E; /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    uint32_t                    u32UserKeyID_P1; /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    uint32_t                    u32BitCnt; /*!<  ecc encrypt data bit count */
    HSM_DrvEccCurvePrmIndexType u32EccCurve; /*!< ecc curve */
    HSM_EccCalcType             tCfg; /*!< ecc decrypt parameters */
} HSMCom_EccCalcType;
/* ------------------------------------------------------------------------------- */

#define HSM_COM_REQUEST_AUTH_DATA_U32_CNT 8
typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t              u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t              (*pData)[HSM_COM_REQUEST_AUTH_DATA_U32_CNT];
} HSMCom_RequestAuthType;
/* ------------------------------------------------------------------------------- */
#define AUTH_CHECK_DATA_BYTE_CNT 32
typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t              u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    const uint32_t        *pkG_x;
    const uint32_t        *pkG_y;
    const uint32_t        *pR;
    const uint32_t        *pS;
    //For user code verify function
    const uint32_t        *pData;
    uint32_t              u32DataLength;
} HSMCom_LifeCycleChangeType;
/* ------------------------------------------------------------------------------- */
typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t              u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t              u32MailboxChannel;
} HSMCom_CancelJobType;
/* ------------------------------------------------------------------------------- */
/**
 * @name definitions for HSMCom_FirmwareLoadStatus
 *
 */
/**@{*/
/**
 * @brief no firmware detected in flash status
 *
 */
#define HSMCOM_FIRMWARE_LOAD_NONE       (0u)

/**
 * @brief status value represents firmware is loading now
 *
 */
#define HSMCOM_FIRMWARE_LOADING         (1u)

/**
 * @brief status value represents firmware waiting user to trigger load in CM7 side
 *
 */
#define HSMCOM_FIRMWARE_NEED_USER_LOAD  (2u)

/**
 * @brief status value represents firmware is loaded successfully
 *
 */
#define HSMCOM_FIRMWARE_LOAD_OK         (3u)

/**
 * @brief status value represents firmware load fail
 *
 */
#define HSMCOM_FIRMWARE_LOAD_FAIL       (4u)

typedef uint32_t HSMCom_FirmwareLoadStatus;
/**@}*/

typedef struct
{
    HSM_MailboxApiRetType     u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t                  u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                  u32Rng0CtrlAndNotFlag; // conf val, only ft mode, other mode REPO_COMMIT_ID
    uint32_t                  u32Rng0CtrlOrFlag;  //  conf val,only ft mode, other mode REPO_BUILD_DATA
    uint32_t                  u32FirmVersion; /*!<  firmware version */
    uint32_t                  u32Rng1CtrlOrFlag;  /*<  FIX to 0x4d6f0000 */
    uint32_t                  u32BusClk; /*!< the hsm bus clock */
    uint32_t                  u32EntropyDelay0;
    uint32_t                  u32FreqMax0;
    uint32_t                  u32EntropyDelay1;
    uint32_t                  u32FreqMax1;
    HSMCom_FirmwareLoadStatus u32FirmwareLoadStatus; /*!< the status of loading firmware, IF >= 4 FAIL */
} HSMCom_SelfTestType;
/* ------------------------------------------------------------------------------- */

#define HSMCOM_NVR_OTP_START_ADDR 0x04400400
#define HSMCOM_NVR_OTP_END_ADDR 0x04401fff

typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t              u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t              u32Addr; // 0x04400400 - 0x04401fff, 16bytes align
    uint32_t              aData[4];
} HSMCom_NvrOtpType;
/* ------------------------------------------------------------------------------- */
/**
 * @name definitions for KeyManager_BoolType
 *
 */
/**@{*/
#define KEYMANAGER_FALSE          (0u)
#define KEYMANAGER_TRUE           (1u)
typedef uint32_t KeyManager_BoolType;
/**@}*/

/**
 * @name definitions for KEYMANAGER_KeyExportType
 *
 */
/**@{*/
#define KEYMANAGER_KEY_EXPORT_FORBIRD  (0u)
#define KEYMANAGER_KEY_EXPORT_PLAIN    (1u)
#define KEYMANAGER_KEY_EXPORT_CIPHER   (2u)
#define KEYMANAGER_KEY_EXPORT_MAX      (3u)
typedef uint32_t KEYMANAGER_KeyExportType;
/**@}*/

/**
 * @name definitions for KeyManager_UserKeyEnDecryType
 *
 */
/**@{*/
#define KEYMANAGER_ENDECRY_NONE     (0u)/* For plain key, no need to encrypt or decrypt. */
#define KEYMANAGER_ENDECRY_AES256   (1u)
#define KEYMANAGER_ENDECRY_SM4      (2u)
#define KEYMANAGER_ENDECRY_MAX      (3u)
typedef uint32_t KeyManager_UserKeyEnDecryType;
/**@}*/

/**
 * @name definitions for KeyManager_UserKeyTypeType
 *
 */
/**@{*/
#define KEYMANAGER_USER_KEY_TYPE_NONE          (0u)//not configure the key type, HSM shall not check if the key type is matched with de/encrypt ALG.
#define KEYMANAGER_USER_KEY_TYPE_AES           (1u)
#define KEYMANAGER_USER_KEY_TYPE_SM4           (2u)
#define KEYMANAGER_USER_KEY_TYPE_ECC_PRIVATE   (3u)
#define KEYMANAGER_USER_KEY_TYPE_ECC_PUBLIC    (4u)
#define KEYMANAGER_USER_KEY_TYPE_SM2_PRIVATE   (5u)
#define KEYMANAGER_USER_KEY_TYPE_SM2_PUBLIC    (6u)
#define KEYMANAGER_USER_KEY_TYPE_RSA_E         (7u)
#define KEYMANAGER_USER_KEY_TYPE_RSA_N         (8u)
#define KEYMANAGER_USER_KEY_TYPE_XMAC          (9u)
#define KEYMANAGER_USER_KEY_TYPE_CMAC          (10u)
#define KEYMANAGER_USER_KEY_TYPE_CCM           (11u)
#define KEYMANAGER_USER_KEY_TYPE_GCM           (12u)
typedef uint32_t KeyManager_UserKeyTypeType;
/**@}*/

/**
 * @name definitions for KEYMANAGER_EnDecryAlgType
 *
 */
/**@{*/

#define KEYMANAGER_ENDECRY_ALG_CTR  (0u)
#define KEYMANAGER_ENDECRY_ALG_CBC  (1u)
#define KEYMANAGER_ENDECRY_ALG_ECB  (2u)
#define KEYMANAGER_ENDECRY_ALG_CFB  (3u)
#define KEYMANAGER_ENDECRY_ALG_OFB  (4u)
#define KEYMANAGER_ENDECRY_ALG_MAX  (5u)

typedef uint32_t KEYMANAGER_EnDecryAlgType;
/**@}*/

typedef struct
{
    uint32_t                      *pDataAddr;
    uint32_t                      *pDataLength;
    uint32_t                      u32KeyID;
    KeyManager_UserKeyEnDecryType eEncryType; //indicate if the key exported is need to be encrypted
    //if the key exported need to be encrypted, below Param need to configure
    uint32_t                      u32EncryKeyID; //0 means use USRK as encrykey, otherwise load decrykey with KEYID from hsm key space
    KEYMANAGER_EnDecryAlgType     eAlgType;
    uint32_t                      (*pIV)[4];
    uint32_t                      *pCiperKeyLength;
} KeyManager_ExportUserKeyType;

typedef struct
{
    KeyManager_BoolType           bStoreInFlash; //true means store the key in flash, false means store the key in ram
    KEYMANAGER_KeyExportType      eExportType;
    uint32_t                      *pDataAddr; //the address of key imported
    uint32_t                      u32DataLength; // the length of key imported
    uint32_t                      *pKeyID;
    KeyManager_UserKeyEnDecryType eDecryType; //indicate if the key imported is plain
    //if the key imported is encrypted, below Param need to configure
    uint32_t                      u32DecryKeyID; //0 means use USRK as decrykey, otherwise load decrykey with KEYID from hsm key space
    KeyManager_UserKeyTypeType    eUserKeyType;
    KEYMANAGER_EnDecryAlgType     eAlgType;
    uint32_t                      (*pIV)[4];
} KeyManager_ImportUserKeyType;

#define KEYMANAGER_GEN_KEYPAIR_SM2 (0u)
#define KEYMANAGER_GEN_KEYPAIR_ECC (1u)
#define KEYMANAGER_GEN_KEYPAIR_MAX (2u)
typedef uint32_t KeyManager_GeNKeyPairType;

typedef struct
{
    KeyManager_GeNKeyPairType eKeyPairType;
    KEYMANAGER_KeyExportType  eExportType;
    KeyManager_BoolType       bStoreInFlash;
    uint32_t                  *pPrivateKeyID;
    uint32_t                  *pPublicKeyID;
} KeyManager_GenAsymmetricUserKeyType;

typedef struct
{
    KEYMANAGER_KeyExportType eExportType;
    KeyManager_BoolType      bStoreInFlash;
    uint32_t                 u32KeyLength;
    uint32_t                 *pKeyID;
} KeyManager_GenSymmetricUserKeyType;

typedef struct
{
    union{
        KeyManager_GenAsymmetricUserKeyType tGenKeyPairCfg;
        KeyManager_GenSymmetricUserKeyType  tGenKeyCfg;
    };
    HSM_DrvEccCurveParamType                tEccParam; //only for generate ECC key pair
    uint32_t                                u32EccBitLength; //only for generate ECC key pair
    HSM_BoolType                            bGenSymmetricKey;
    HSM_DrvEccCurvePrmIndexType             u32EccCurve;
} HSMCom_GenUserKeyType;

typedef struct
{
    HSM_MailboxApiRetType            u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t                         u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    union
    {
        uint32_t                     u32RevokeUserKeyID;/* For revoke UserKey function*/
        KeyManager_ImportUserKeyType tImportUserKeyCfg;/* For import User Key function*/
        KeyManager_ExportUserKeyType tExportUserKeyCfg;/* For export user key function */
        HSMCom_GenUserKeyType        tGenUserKeyCfg;/* For generate key pair function */
    };
} HSMCom_UserKeyManageType;
/* ------------------------------------------------------------------------------- */
typedef struct
{
    //For Key Flash Space
    KeyManager_BoolType bCriticalError;
    KeyManager_BoolType bKMLackKeyHeadSpace;
    KeyManager_BoolType bKMLackKeyDataSpace;
    uint32_t            u32KeyHeadRestSpace;   //The unit is number
    uint32_t            u32KeyDataRestSpace;   //The unit is page
    uint32_t            u32InvalidKeyCounter;
    //For Key ram space
    uint32_t            u32KeyRamSpaceUsed;
} KeyManager_SpaceStatusType;

typedef struct
{
    HSM_MailboxApiRetType      u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t                   u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    KeyManager_SpaceStatusType *pKMSpaceStatus;
} HSMCom_KeySpaceStatusType;
/* ------------------------------------------------------------------------------- */

/**
 * @name definitions for HSM_AesKeyType
 *
 */
/**@{*/

/**
 * @brief vendor key value for type "HSM_AesKeyType"
 *
 * HSM hardware support accessing the aes key stored in nvr flash directly,
 * chip user should program the key in flash already.
 * This way don't need software read data and write it to some place,
 * hardware will read the data itself automatically.
 */
#define HSM_AES_KEY_CHIP_VENDOR_IFR (0U) /* key has existed in Flash IFR, it provided by chip hardware, not changeable */

/**
 * @brief driver user's new key value for type "HSM_AesKeyType"
 *
 * HSM use the key passed by driver API user.
 */
#define HSM_AES_KEY_NEW             (1U) /* user should provide the new key */

/**
 * @brief type definition for the key source
 *
 * key from the nvr refer to HSM_AES_KEY_CHIP_VENDOR_IFR
 * key from driver user's parameters refer to HSM_AES_KEY_NEW
 */
typedef uint32_t HSM_AesKeyType;
/**@}*/

/**
 * @name definitions for HSM_AesKeyBitCntType
 *
 */
/**@{*/

/**
 * @brief AES128 key type value for type "HSM_AesKeyBitCntType"
 *
 */
#define HSM_AES_KEY128  (0U)

/**
 * @brief AES192 key type value for type "HSM_AesKeyBitCntType"
 *
 */
#define HSM_AES_KEY192  (1U)

/**
 * @brief AES256 key type value for type "HSM_AesKeyBitCntType"
 *
 */
#define HSM_AES_KEY256  (2U)

/**
 * @brief type definition for AES key
 *
 * HSM support AES128/192/256, driver api use this to select the algorithm.
 */
typedef uint32_t HSM_AesKeyBitCntType;
/**@}*/


/**
 * @brief key information used by AES when use one key in software
 *
 */
typedef struct
{
    HSM_AesKeyBitCntType  eKeyType; /*!< the key bit count, which determine the AES algorithm type */
    const uint32_t        *pKeyAddr; /*!< the key data pointer, the address should 4bytes align, the buffer array should declared by uint32_t */
} HSM_AesNewKeyInfType;

/**
 * @brief key information used by AES when use one key in nvr flash
 *
 */
typedef struct
{
    HSM_AesKeyBitCntType eKeyType; /*!< the key bit count, which determine the AES algorithm type */
} HSM_AesVendorKeyInfType;

/**
 * @name definitions for HSM_AesEnDecryptAlgType
 *
 */
/**@{*/

/**
 * @brief AES CTR mode value for type "HSM_AesEnDecryptAlgType"
 *
 */
#define HSM_AES_CTR  (0U)

/**
 * @brief AES CBC mode value for type "HSM_AesEnDecryptAlgType"
 *
 */
#define HSM_AES_CBC  (1U)

/**
 * @brief AES ECB mode value for type "HSM_AesEnDecryptAlgType"
 *
 */
#define HSM_AES_ECB  (2U)

/**
 * @brief AES CFB mode value for type "HSM_AesEnDecryptAlgType"
 *
 */
#define HSM_AES_CFB  (3U)

/**
 * @brief AES OFB mode value for type "HSM_AesEnDecryptAlgType"
 *
 */
#define HSM_AES_OFB  (4U)

/**
 * @brief type definition for AES encrypt/decrypt mode
 *
 * HSM support CTR/CBC/ECB/CFB/OFB mode, driver api use this to select the encrypt/decrypt mode.
 */
typedef uint32_t HSM_AesEnDecryptAlgType;
/**@}*/

/**
 * @brief AES encrypt/decrypt information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_AesKeyType              eUseKeyType;        /*!< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf;         /*!< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf;      /*!< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */
    HSM_AesEnDecryptAlgType     eAesAlg;            /*!< encrypt/decrypt mode */

    const uint32_t              *pDataInput;         /*!< address should align with 4bytes */
    uint32_t                    u32InputByteCnt;    /*!< 128bit(16Bytes) align */
    uint32_t                    *pDataOutput;        /*!< address should align with 4bytes */
    uint32_t                    u32OutputMemSize;   /*!< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */

    uint32_t                    (*pIvData)[4]; /*!< 128bit(16Bytes) iv(initialization vector) data array, ECB not need configure this */

} HSM_AesEnDecryptType;

/**
 * @brief Flexiable AES zero padding type for type "HSM_FlexAesPadType"
 * if input data is not aligned with 16bytes, this configuration will make append byte data 0 to keep 16bytes align.
 */
#define HSM_FLEXAES_PAD_ZERO  0u

/**
 * @brief Flexiable AES PKCS7 padding type for type "HSM_FlexAesPadType"
 * if input data is not aligned with 16bytes, this configuration will make append bytes by PKCS7 method to keep 16bytes align.
 */
#define HSM_FLEXAES_PAD_PKCS7 1u

/**
 * @brief Flexiable AES padding type definition
 * if use zero padding, refer to HSM_FLEXAES_PAD_ZERO, after decrypt, user should remove the zero manually
 * if use PKCS7 padding, refer to HSM_FLEXAES_PAD_PKCS7
 */
typedef uint32_t HSM_FlexAesPadType;

/* ------------------------------------------------------------------------------- */
/**
 * @brief AES hardware backend for AES for type "HSM_AesBackendType"
 *
 */
#define HSM_AES_BACKEND_AES 0u

/**
 * @brief SM4 hardware backend for AES for type "HSM_AesBackendType"
 *
 */
#define HSM_AES_BACKEND_SM4 1u

/**
 * @brief type definition for GCM's hardware backend
 * AES backend refer to HSM_AES_BACKEND_AES
 * SM4 backend refer to HSM_GCM_BACKEND_SM4
 */
typedef uint32_t  HSM_AesBackendType;

/**
 * @brief Flex AES encrypt/decrypt information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_AesKeyType              eUseKeyType;        /*!< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf;         /*!< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf;      /*!< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */
    HSM_AesEnDecryptAlgType     eAesAlg;            /*!< encrypt/decrypt mode */

    const uint32_t              *pDataInput;         /*!< address should align with 4bytes */
    uint32_t                    u32InputByteCnt;    /*!< 128bit(16Bytes) align */
    uint32_t                    *pDataOutput;        /*!< address should align with 4bytes */
    uint32_t                    u32OutputMemSize;   /*!< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */

    uint32_t                    (*pIvData)[4]; /*!< address should align with 4bytes, 128bit(16Bytes) iv(initialization vector) data array, ECB not need configure this */

    uint32_t                    *pGenerateOutByteCnt; /*!< point to the uint32_t variable to store the result byte count, can't be NULL */

    HSM_FlexAesPadType          epad;
    HSM_DataFormatType          eInputFmt;
    HSM_DataFormatType          eOutputFmt;
    HSM_AesBackendType          eBackend;
} HSM_FlexAesEnDecryptType;

/**
 * @brief AES decrypt information used by driver when call specific API
 *
 */
typedef HSM_AesEnDecryptType HSM_AesEncryptType;
typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                u32Timeout;         /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_AesEncryptType      tCfg;               /*!< aes parameters */
} HSMCom_AesEncryptType;
/* ------------------------------------------------------------------------------- */
/**
 * @brief AES encrypt information used by driver when call specific API
 *
 */
typedef HSM_AesEnDecryptType HSM_AesDecryptType;

typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                u32Timeout;         /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_AesDecryptType      tCfg;               /*!< AES decrypt parameters */
} HSMCom_AesDecryptType;
/* ------------------------------------------------------------------------------- */

/**
 * @brief Flex AES decrypt information used by driver when call specific API
 *
 */
typedef HSM_FlexAesEnDecryptType HSM_FlexAesEncryptType;
typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                u32Timeout;         /*!< current command timeout Millisecond count, max 916000ms, if set to 0, means 1000ms */
    uint32_t                u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_FlexAesEncryptType  tCfg;               /*!< aes parameters */
} HSMCom_FlexAesEncryptType;
/* ------------------------------------------------------------------------------- */
/**
 * @brief AES encrypt information used by driver when call specific API
 *
 */
typedef HSM_FlexAesEnDecryptType HSM_FlexAesDecryptType;

typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                u32Timeout;         /*!< current command timeout Millisecond count, max 916000ms, if set to 0, means 1000ms */
    uint32_t                u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_FlexAesDecryptType  tCfg;               /*!< AES decrypt parameters */
} HSMCom_FlexAesDecryptType;
/* ------------------------------------------------------------------------------- */

/**
 * @brief CMAC/XMAC information used by driver when call specific API
 *
 */

#define HSM_XCMAC_BACKEND_AES 0u
#define HSM_XCMAC_BACKEND_SM4 1u

typedef uint32_t HSM_XCMAC_BackendType;

typedef struct
{
    HSM_AesKeyType              eUseKeyType;        /*!< fix to HSM_AES_KEY_NEW */
    HSM_AesNewKeyInfType        tNewKeyInf;         /*!< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf;      /*!< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */
    uint32_t                    u32GenMacByteCnt;   /*!< XCMAC API generate MAC data, it's "u32GenMacByteCnt" size ICV data */
    HSM_BoolType                bCheckMacEn;        /*!< if enable this check, user should place the data after the input data, hsm will check the generated data and it, if fail, hsm generate a interrupt, and if user get hw status, will get a error status */
    const uint32_t              *pDataInput;         /*!< address should align with 4bytes */
    uint32_t                    u32InputByteCnt;    /*!< 128bit(16Bytes) align */
    uint32_t                    *pDataOutput;        /*!< address should align with 4bytes */
    uint32_t                    u32OutputMemSize;   /*!< 4bytes align, the output data buffer "pDataOutput" size, should >= "u32GenMacByteCnt" */
} HSM_XCMacType;

/**
 * @brief CMAC information used by driver when call specific API
 *
 */
typedef HSM_XCMacType HSM_CMacType;


typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                u32Timeout;         /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_CMacType            tCfg;               /*!< CMAC parameters */
} HSMCom_CMacType;

typedef struct
{
    HSM_AesKeyType              eUseKeyType;        /*!< fix to HSM_AES_KEY_NEW */
    HSM_AesNewKeyInfType        tNewKeyInf;         /*!< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf;      /*!< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */
    uint32_t                    u32GenMacByteCnt;   /*!< XCMAC API generate MAC data, it's "u32GenMacByteCnt" size ICV data */
    HSM_BoolType                bCheckMacEn;        /*!< if enable this check, user should place the data after the input data, hsm will check the generated data and it, if fail, hsm generate a interrupt, and if user get hw status, will get a error status */
    const uint32_t              *pDataInput;         /*!< address should align with 4bytes */
    uint32_t                    u32InputByteCnt;    /*!< 128bit(16Bytes) align */
    uint32_t                    *pDataOutput;        /*!< address should align with 4bytes */
    uint32_t                    u32OutputMemSize;   /*!< 4bytes align, the output data buffer "pDataOutput" size, should >= "u32GenMacByteCnt" */

    HSM_XCMAC_BackendType       eBackend;
    HSM_DataFormatType          eInputFmt;
    HSM_DataFormatType          eOutputFmt;
} HSM_XCMacExType;

typedef HSM_XCMacExType HSM_CMacExType;
typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                u32Timeout;         /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_CMacExType          tCfg;               /*!< CMAC parameters */
} HSMCom_CMacExType;


/* ------------------------------------------------------------------------------- */
/**
 * @brief XMAC information used by driver when call specific API
 *
 */
typedef HSM_XCMacType HSM_XMacType;
typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                u32Timeout;         /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_XMacType            tCfg;               /*!< XMAC parameter */
} HSMCom_XMacType;

typedef HSM_XCMacExType HSM_XMacExType;
typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                u32Timeout;         /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_XMacExType          tCfg;               /*!< XMAC parameter */
} HSMCom_XMacExType;

/* ------------------------------------------------------------------------------- */
/**
 * @brief AES hardware backend for CCM for type "HSM_CcmBackendType"
 *
 */
#define HSM_CCM_BACKEND_AES 0u

/**
 * @brief SM4 hardware backend for CCM for type "HSM_CcmBackendType"
 *
 */
#define HSM_CCM_BACKEND_SM4 1u

/**
 * @brief type definition for CCM's hardware backend
 * AES backend refer to HSM_CCM_BACKEND_AES
 * SM4 backend refer to HSM_CCM_BACKEND_SM4
 */
typedef uint32_t  HSM_CcmBackendType;


/**
 * @brief CCM Encrypt information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_AesKeyType              eUseKeyType;    /*!< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf;     /*!< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf;  /*!< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */
    uint32_t                    *pAllData;           /*!< address should align with 4bytes, place AAD data(16bytes align) first, then input data */
    uint32_t                    u32AadByteCnt;      /*!< the byte count contain the 2bytes in the head, it's the valid data size, not after aligned, 128bit(16Bytes) align, if not, only the aligned data treat as AAD, the left AAD bytes will be treated as input data  */
    uint32_t                    u32InputByteCnt;    /*!< 128bit(16Bytes) align, ONLY represent data */
    uint32_t                    u32GenMacByteCnt;   /*!< output mac size */
    uint32_t                    *pDataOutput;        /*!< address should align with 4bytes */
    uint32_t                    u32OutputMemSize;   /*!< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */
    uint32_t                    (*pIvData)[8];  /*!< iv data, consist of 16bytes B0 data, and 16bytes CTR,  MUST configure */
    uint32_t                    (*pMacOut)[4];  /*!< HSM generated MAC data */
    uint32_t                    (*pEmacOut)[4]; /*!< HSM generated encrypted MAC data */
} HSM_CcmEncryptType;

typedef struct
{
    HSM_MailboxApiRetType       u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                    u32Timeout;         /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                    u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_CcmEncryptType          tCfg;               /*!< CCM encrypt parameters */
} HSMCom_CcmEncryptType;

typedef struct
{
    HSM_AesKeyType              eUseKeyType;    /*!< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf;     /*!< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf;  /*!< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */
    uint32_t                    *pAllData;           /*!< address should align with 4bytes, place AAD data(16bytes align) first, then input data */
    uint32_t                    u32AadByteCnt;      /*!< the byte count contain the 2bytes in the head, it's the valid data size, not after aligned, 128bit(16Bytes) align, if not, only the aligned data treat as AAD, the left AAD bytes will be treated as input data  */
    uint32_t                    u32InputByteCnt;    /*!< 128bit(16Bytes) align, ONLY represent data */
    uint32_t                    u32GenMacByteCnt;   /*!< output mac size */
    uint32_t                    *pDataOutput;        /*!< address should align with 4bytes */
    uint32_t                    u32OutputMemSize;   /*!< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */
    uint32_t                    (*pIvData)[8];  /*!< iv data, consist of 16bytes B0 data, and 16bytes CTR,  MUST configure */
    uint32_t                    (*pMacOut)[4];  /*!< HSM generated MAC data */
    uint32_t                    (*pEmacOut)[4]; /*!< HSM generated encrypted MAC data */
    HSM_CcmBackendType          eBackend;
} HSM_CcmEncryptExType;

typedef struct
{
    HSM_MailboxApiRetType       u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                    u32Timeout;         /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                    u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_CcmEncryptExType        tCfg;               /*!< CCM encrypt parameters */
} HSMCom_CcmEncryptExType;

/* ------------------------------------------------------------------------------- */
/**
 * @brief CCM Decrypt information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_AesKeyType              eUseKeyType; /*!< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf; /*!< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf; /*!< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */
    uint32_t                    *pAllData; /*!< address should align with 4bytes, place AAD data(if exist, 16bytes align) first, then input data, then MAC data(if exist) */
    uint32_t                    u32AadByteCnt; /*!< 128bit(16Bytes) align, if not, only the aligned data treat as AAD, the left AAD bytes will be treated as input data  */
    uint32_t                    u32InputByteCnt; /*!< 128bit(16Bytes) align */
    HSM_BoolType                bCheckMacEn; /*!< check the MAC data in input or not */
    uint32_t                    u32MacByteCnt; /*!< 128bit(16Bytes) align */
    uint32_t                    *pDataOutput; /*!< point to the buffer that store the result */
    uint32_t                    u32OutputMemSize; /*!< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */
    uint32_t                    (*pIvData)[8]; /*!< iv data, consist of 16bytes B0 data, and 16bytes CTR,  MUST configure */
} HSM_CcmDecryptType;

typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                u32Timeout;         /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_CcmDecryptType      tCfg;               /*!< CCM decrypt parameter */
} HSMCom_CcmDecryptType;

typedef struct
{
    HSM_AesKeyType              eUseKeyType; /*!< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf; /*!< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf; /*!< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */
    uint32_t                    *pAllData; /*!< address should align with 4bytes, place AAD data(if exist, 16bytes align) first, then input data, then MAC data(if exist) */
    uint32_t                    u32AadByteCnt; /*!< 128bit(16Bytes) align, if not, only the aligned data treat as AAD, the left AAD bytes will be treated as input data  */
    uint32_t                    u32InputByteCnt; /*!< 128bit(16Bytes) align */
    HSM_BoolType                bCheckMacEn; /*!< check the MAC data in input or not */
    uint32_t                    u32MacByteCnt; /*!< 128bit(16Bytes) align */
    uint32_t                    *pDataOutput; /*!< point to the buffer that store the result */
    uint32_t                    u32OutputMemSize; /*!< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */
    uint32_t                    (*pIvData)[8]; /*!< iv data, consist of 16bytes B0 data, and 16bytes CTR,  MUST configure */
    HSM_CcmBackendType          eBackend;
} HSM_CcmDecryptExType;

typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                u32Timeout;         /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_CcmDecryptExType    tCfg;               /*!< CCM decrypt parameter */
} HSMCom_CcmDecryptExType;

/* ------------------------------------------------------------------------------- */
/**
 * @brief AES hardware backend for GCM for type "HSM_GcmBackendType"
 *
 */
#define HSM_GCM_BACKEND_AES 0u

/**
 * @brief SM4 hardware backend for GCM for type "HSM_GcmBackendType"
 *
 */
#define HSM_GCM_BACKEND_SM4 1u

/**
 * @brief type definition for GCM's hardware backend
 * AES backend refer to HSM_GCM_BACKEND_AES
 * SM4 backend refer to HSM_GCM_BACKEND_SM4
 */
typedef uint32_t  HSM_GcmBackendType;

/**
 * @brief GCM Encrypt information used by driver when call specific API
 *
 */
typedef  struct
{
    HSM_AesKeyType              eUseKeyType; /*!< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf; /*!< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf; /*!< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */
    uint32_t                    *pAllData; /*!< address should align with 4bytes, place IV data first, then AAD data(16bytes align), then input data */
    uint32_t                    u32IvDataByteCnt; /*!< 64bit(8Bytes) align, if not, only the aligned data treat as IV, the left IV bytes will be treated as AAD data  */
    uint32_t                    u32AadByteCnt; /*!< 64bit(8Bytes) align, if not, only the aligned data treat as AAD, the left AAD bytes will be treated as input data  */
    uint32_t                    u32InputByteCnt; /*!< 128bit(16Bytes) align */
    uint32_t                    u32GenMacByteCnt; /*!< set the MAC result byte count */
    uint32_t                    *pDataOutput; /*!< address should align with 4bytes */
    uint32_t                    u32OutputMemSize; /*!< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */
    uint32_t                    (*pMacOut)[4]; /*!< buffer address, this buffer store the result */
}  HSM_GcmEncryptType;

typedef struct
{
    HSM_MailboxApiRetType       u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                    u32Timeout;         /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                    u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_GcmEncryptType          tCfg;               /*!< GCM parameters */
} HSMCom_GcmEncryptType;

/**
 * @brief GCM Encrypt information used by driver when call specific API
 *
 */
typedef  struct
{
    HSM_AesKeyType              eUseKeyType; /*!< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf; /*!< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf; /*!< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */
    uint32_t                    *pAllData; /*!< address should align with 4bytes, place IV data first, then AAD data(16bytes align), then input data */
    uint32_t                    u32IvDataByteCnt; /*!< 64bit(8Bytes) align, if not, only the aligned data treat as IV, the left IV bytes will be treated as AAD data  */
    uint32_t                    u32AadByteCnt; /*!< 64bit(8Bytes) align, if not, only the aligned data treat as AAD, the left AAD bytes will be treated as input data  */
    uint32_t                    u32InputByteCnt; /*!< 128bit(16Bytes) align */
    uint32_t                    u32GenMacByteCnt; /*!< set the MAC result byte count */
    uint32_t                    *pDataOutput; /*!< address should align with 4bytes */
    uint32_t                    u32OutputMemSize; /*!< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */
    uint32_t                    (*pMacOut)[4]; /*!< buffer address, this buffer store the result */
    HSM_GcmBackendType          eBackend;
}  HSM_GcmEncryptExType;

typedef struct
{
    HSM_MailboxApiRetType       u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                    u32Timeout;         /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                    u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_GcmEncryptExType        tCfg;               /*!< GCM parameters */
} HSMCom_GcmEncryptExType;

/* ------------------------------------------------------------------------------- */
/**
 * @brief GCM Decrypt information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_AesKeyType              eUseKeyType; /*!< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf; /*!< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf; /*!< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */
    uint32_t                    *pAllData; /*!< address should align with 4bytes, place IV data first, then AAD data(if exist, 16bytes align), then input data, then MAC data(if exist) */
    uint32_t                    u32IvDataByteCnt; /*!< 64bit(8Bytes) align, if not, only the aligned data treat as IV, the left IV bytes will be treated as AAD data  */
    uint32_t                    u32AadByteCnt; /*!< 64bit(8Bytes) align, if not, only the aligned data treat as AAD, the left AAD bytes will be treated as input data  */
    uint32_t                    u32InputByteCnt; /*!< 128bit(16Bytes) align */
    HSM_BoolType                bCheckMacEn; /*!< check the MAC data in input or not */
    uint32_t                    u32MacByteCnt; /*!< 128bit(16Bytes) align */
    uint32_t                    *pDataOutput; /*!< point to the buffer that store the result */
    uint32_t                    u32OutputMemSize; /*!< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */
} HSM_GcmDecryptType;

typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                u32Timeout;         /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_GcmDecryptType      tCfg;               /*!< GCM decrypt parameter */
} HSMCom_GcmDecryptType;

/**
 * @brief GCM Decrypt information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_AesKeyType              eUseKeyType; /*!< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf; /*!< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf; /*!< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */
    uint32_t                    *pAllData; /*!< address should align with 4bytes, place IV data first, then AAD data(if exist, 16bytes align), then input data, then MAC data(if exist) */
    uint32_t                    u32IvDataByteCnt; /*!< 64bit(8Bytes) align, if not, only the aligned data treat as IV, the left IV bytes will be treated as AAD data  */
    uint32_t                    u32AadByteCnt; /*!< 64bit(8Bytes) align, if not, only the aligned data treat as AAD, the left AAD bytes will be treated as input data  */
    uint32_t                    u32InputByteCnt; /*!< 128bit(16Bytes) align */
    HSM_BoolType                bCheckMacEn; /*!< check the MAC data in input or not */
    uint32_t                    u32MacByteCnt; /*!< 128bit(16Bytes) align */
    uint32_t                    *pDataOutput; /*!< point to the buffer that store the result */
    uint32_t                    u32OutputMemSize; /*!< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */
    HSM_GcmBackendType          eBackend;
} HSM_GcmDecryptExType;

typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet;    /*!< HSM core write return status value in this */
    uint32_t                u32Timeout;         /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t                u32UserKeyID;       /*!< 0 means don't use key from HSM internal key space, otherwise would load key with KEYID from HSM */
    HSM_GcmDecryptExType    tCfg;               /*!< GCM decrypt parameter */
} HSMCom_GcmDecryptExType;

/* ------------------------------------------------------------------------------- */
/**
 * @brief MD5 context information used by driver when call specific API
 *
 */
typedef HSM_SmsCfgType HSM_Md5CtxType;
/**
 * @brief MD5 information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_Md5CtxType      tCfg; /*!< MD5 algorithm parameter set by user */
    uint32_t            (*pRet)[4]; /*!< point to the memory that driver to store result */
    HSM_DataFormatType  eIntputFmt;
    HSM_DataFormatType  eOutputFmt;
} HSM_Md5Type;

typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t              u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    HSM_Md5Type           tCfg;
} HSMCom_Md5Type;
/* ------------------------------------------------------------------------------- */
/**
 * @brief SM3 context information used by driver when call specific API
 *
 */
typedef HSM_SmsCfgType HSM_Sm3CtxType;
/**
 * @brief SM3 information used by driver when call specific API
 *
 */
typedef struct
{
    HSM_Sm3CtxType      tCfg; /*!< sm3 algorithm parameter set by user */
    uint32_t            (*pRet)[8]; /*!< point to the memory that driver to store result */
    HSM_DataFormatType  eIntputFmt;
    HSM_DataFormatType  eOutputFmt;
} HSM_Sm3Type;

typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t              u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    HSM_Sm3Type           tCfg;
} HSMCom_Sm3Type;

/* ------------------------------------------------------------------------------- */
#define HSMCOM_MONOTOIC_COUNTER_FLEX_REG_CNT 8
typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t              u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t              u32MonotonicIndex; // 0-13
    uint32_t              u32CurrentValue;
    uint32_t              (*u32ExtraValue)[HSMCOM_MONOTOIC_COUNTER_FLEX_REG_CNT - 1];
    uint32_t              (*u32ExtraAdd)[HSMCOM_MONOTOIC_COUNTER_FLEX_REG_CNT];
} HSMCom_MonCountType;
/* ------------------------------------------------------------------------------- */
/**
 * @brief RSA information used by driver when call specific API
 *
 */
typedef struct
{
    uint32_t *pInputData; /*!< input data, if not 64bytes align, the last uint64_t's high byte left to patch 0 to align */
    uint32_t u32InputDataByteCount; /*!< the byte count of input data */
    uint32_t *pKey_E; /*!< input key E data for "A = (input data)^E mod N", if not 64bytes align, the last uint64_t's high byte left to patch 0 to align */
    uint32_t u32Key_E_ByteCount; /*!< the byte count of key E */
    uint32_t *pKey_N; /*!< input key N data for "A = (input data)^E mod N", if not 64bytes align, the last uint64_t's high byte left to patch 0 to align */
    uint32_t u32Key_N_ByteCount; /*!< hw will get the actual key data bit count according to the non-zero bit count, it means key not generate by multiply 2 */
    uint32_t *pResult; /*!< output buffer, the buffer size should >= "u32Key_N_ByteCount" */
    uint32_t u32ResultBufByteCnt; /*!< the result buffer size */
} HSM_RsaType;

typedef struct
{
    HSM_MailboxApiRetType u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t              u32Timeout; /*!< current command timeout tick count, tick refer to the HSM bus clock */
    uint32_t              u32UserKeyID_KEY_E; //0 means don't load key from HSM, otherwise would load key with KEYID from HSM
    uint32_t              u32UserKeyID_KEY_N; //0 means don't load key from HSM, otherwise would load key with KEYID from HSM
    uint32_t              u32RsaBitCnt;
    HSM_RsaType           tCfg;
} HSMCom_RsaType;
/* ------------------------------------------------------------------------------- */
#define HSM_BIGNUMBER_CALC_A_ADD_B  0xFC730002
#define HSM_BIGNUMBER_CALC_A_SUB_B  0xFC730003
#define HSM_BIGNUMBER_CALC_B_SUB_A  0xFC730004
#define HSM_BIGNUMBER_CALC_A_MUL_B  0xFC730005
#define HSM_BIGNUMBER_CALC_A_EXP_E  0xFC730006
#define HSM_BIGNUMBER_CALC_A_RED_N  0xFC730007
#define HSM_BIGNUMBER_CALC_A_INV    0xFC730008

/**
 * @brief RSA information used by driver when call specific API
 *
 */
typedef struct
{
    uint32_t *pA; /*!< address is 4bytes aligned, input data, if not 64bytes align, the last uint64_t's high byte left to patch 0 to align */
    uint32_t u32AByteCount; /*!< the byte count of input data */
    uint32_t *pE; /*!< address is 4bytes aligned, input key E data for "A = (input data)^E mod N", if not 64bytes align, the last uint64_t's high byte left to patch 0 to align */
    uint32_t u32EByteCount; /*!< the byte count of key E */
    uint32_t *pN; /*!< address is 4bytes aligned, input key N data for "A = (input data)^E mod N", if not 64bytes align, the last uint64_t's high byte left to patch 0 to align */
    uint32_t u32NByteCount; /*!< hw will get the actual key data bit count according to the non-zero bit count, it means key not generate by multiply 2 */
    uint32_t *pResult; /*!< address is 4bytes aligned, output buffer, the buffer size should >= "u32Key_N_ByteCount" */
    uint32_t u32ResultBufByteCnt; /*!< the result buffer size */
    uint32_t u32CalcType;
    uint32_t *pB;
    uint32_t u32BByteCount;
} HSM_BigNumberCalcType;

typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t                u32Timeout; /*!< current command timeout Millisecond count, max 916000ms, if set to 0, means 1000ms */
    uint32_t                u32UserKeyID_KEY_E; /*!< means don't load key from HSM, otherwise would load key with KEYID from HSM */
    uint32_t                u32UserKeyID_KEY_N; /*!< means don't load key from HSM, otherwise would load key with KEYID from HSM */
    uint32_t                u32BitCnt; /*!< the bit count of numbers used of N */
    HSM_BigNumberCalcType   tCfg; /*!< RSA parameters */
} HSMCom_BigNumberCalcType;
/* ------------------------------------------------------------------------------- */


typedef struct
{
    HSM_MailboxApiRetType   u32HSMStatusRet; /*!< HSM core write return status value in this */
    uint32_t                u32Timeout; /*!< current command timeout Millisecond count, max 916000ms, if set to 0, means 1000ms */
} HSMCom_LoadFirmwareType;

/* ------------------------------------------------------------------------------- */

typedef HSMCom_LoadFirmwareType HSMCom_BasicType;

/* #define AUTH_CHECK_DATA_BYTE_CNT 32 */

typedef struct {
    uint32_t        u32HSMStatusRet;
    uint32_t        u32Timeout;
    const uint32_t *pkG_x;  /*!< address should align with 4bytes */
    const uint32_t *pkG_y;  /*!< address should align with 4bytes */
    const uint32_t *pR;     /*!< address should align with 4bytes */
    const uint32_t *pS;     /*!< address should align with 4bytes */
    //For user code verify function
    const uint32_t *pData;  /*!< address should align with 4bytes */
    uint32_t       u32DataLength;
} HSMCom_AuthCheckType;

typedef struct {
    HSM_BoolType bStoreInFlash;
    HSM_BoolType bUseDefaultID; //TRUE means use default ID. FALSE means use specific ID with "pInputData_ID" and "u32SM2InputIDByteCnt" params.
    uint32_t     u32SM2InputIDByteCnt;//the length should be <= 32bytes  note: If "bUseDefaultID" is FALSE, would use this specific ID length with byte unit.
    uint32_t     *pInputData_ID; //note: If "bUseDefaultID" is FALSE, would use this specific ID. length should be more than u32SM2InputIDByteCnt, and must be 4bytes align
    uint32_t     (*pRaPublicKey_X)[8];
    uint32_t     (*pRaPublicKey_Y)[8];
    uint32_t     (*pPaPublicKey_X)[8];
    uint32_t     (*pPaPublicKey_Y)[8];
    uint32_t     (*pPublicKey_X)[8];
    uint32_t     (*pPublicKey_Y)[8];
    uint32_t     (*PrivateKey)[8];
    uint32_t     (*pRbPublicKey_X)[8];
    uint32_t     (*pRbPublicKey_Y)[8];
    uint32_t     *pOutputKeyID;
}HSM_SmDHType;

typedef struct {
    uint32_t     u32HSMStatusRet;
    uint32_t     u32Timeout;
    HSM_SmDHType tCfg;
} HSMCom_SmDHType;

typedef struct {
    uint32_t                 u32ByteCount; /*!< all the data size, it should contains all N data */
    HSM_DrvEccCurveParamType tCurve;
    const uint32_t           *pASidePublicKey_x; /*!< A side's public key axis x data */
    const uint32_t           *pASidePublicKey_y; /*!< A side's public key axis y data */
    const uint32_t           *pBSidePrivateKey; /*!< B side private key */
    /* Below is output data */
    uint32_t                 *pBSidePublicKey_x; /*!< B side's public key axis x data */
    uint32_t                 *pBSidePublicKey_y; /*!< B side's public key axis y data */
    uint32_t                 *pSharedPublicKey_x;
    uint32_t                 *pSharedPublicKey_y;
}HSM_ECDHType;

typedef struct {
    uint32_t                      u32HSMStatusRet;
    uint32_t                      u32Timeout;
    uint32_t                      u32UserKeyID_BSidePrivateKey; //0 means don't load key from HSM, otherwise would load key with KEYID from HSM
    uint32_t                      u32UserKeyID_BSidePublicKey;  //0 means don't load key from HSM, otherwise would load key with KEYID from HSM
    uint32_t                      u32BitCnt;
    HSM_DrvEccCurvePrmIndexType   u32EccCurve;
    HSM_ECDHType                  tCfg;
} HSMCom_ECDHType;

typedef struct {
    uint32_t *pInputKey_a; /*!< input private key b data, if not 64bytes align, the last uint64_t's high byte left to patch 0 to align */
    uint32_t u32Key_a_ByteCount; /*!< the byte count of key b */
    uint32_t *pInputKey_B; /*!< input public key A data, if not 64bytes align, the last uint64_t's high byte left to patch 0 to align */
    uint32_t u32Key_B_ByteCount; /*!< the byte count of key A */
    uint32_t *pPublicParam_g; /*!< Param g data for "A = g^a mod p", if not 64bytes align, the last uint64_t's high byte left to patch 0 to align */
    uint32_t u32PublicParam_g_ByteCount; /*!< the byte count of param g */
    uint32_t *pPublicParam_p; /*!< Param p data for "A = g^a mod p", if not 64bytes align, the last uint64_t's high byte left to patch 0 to align */
    uint32_t u32PublicParam_p_ByteCount; /*!< the byte count of param p */
    uint32_t *pOutputKey_A; /*!< output public key B data, if not 64bytes align, the last uint64_t's high byte left to patch 0 to align */
    uint32_t *pOutputKey_S;
} HSM_RsaDHType;

typedef struct {
    uint32_t      u32HSMStatusRet;
    uint32_t      u32Timeout;
    uint32_t      u32UserKeyID_a; //0 means don't load key from HSM, otherwise would load key with KEYID from HSM
    uint32_t      u32UserKeyID_B;  //0 means don't load key from HSM, otherwise would load key with KEYID from HSM
    HSM_RsaDHType tCfg;
} HSMCom_RsaDHType;

typedef struct {
    HSM_HashAlgType eHashAlg;
    uint32_t        u32Counter;
    uint32_t        u32dkLen;
    uint32_t        u32PasswordByteLength;
    const uint32_t  *pPassword;
    uint32_t        u32SaltByteLength;
    const uint32_t  *pSalt;
    uint32_t        *pKdfOutput;
} HSM_PBKDF2Type;

/**
 * @brief RSA SSA input data is the raw message for HSM_RsaSsaInputType
 *
 */
#define HSM_RSA_SSA_INPUT_RAW_MESSAGE  0u

/**
 * @brief RSA SSA input data is the hash value of raw message for HSM_RsaSsaInputType
 *
 */
#define HSM_RSA_SSA_INPUT_HASH_DATA    1u

/**
 * @brief type definition for rsa ssa input data type
 * refer to HSM_RSA_SSA_INPUT_RAW_MESSAGE, HSM_RSA_SSA_INPUT_HASH_DATA
 */
typedef uint32_t HSM_RsaSsaInputType;


/**
 * @brief RSA PSS signature information used by driver when call specific API
 *
 */
typedef struct {
    HSM_BoolType        bUsePseudoRand;
    HSM_HashAlgType     eMgfHashType;
    HSM_DataFormatType  eInputFmt; /*!< input data organized format, uint8_t array, or uint32_t array */
    HSM_DataFormatType  eOutputFmt; /*!< output data organized format, uint8_t array, or uint32_t array */
    uint32_t            u32EmBitCnt; /* RFC8017 require set it to (N's bit count - 1).the em data bit count, it MUST < N's bit count */
    HSM_HashAlgType     eHashType; /*!< the hash type used by signature */
    HSM_RsaSsaInputType eInputType; /*!< input data type, may raw input message, or the hash data of raw message */
    const uint8_t       *pInputData; /*!< input data */
    uint32_t            u32InputDataByteCount; /*!< the byte count of input data */
    const uint8_t       *pPrivateKey; /*!< private key, input key E data for "A = (input data)^E mod N" */
    uint32_t            u32PrivateKeyByteCnt; /*!< the byte count of key E */
    HSM_BoolType        bUseInputSaltData;  /*!< use input salt data or not, , suggest set to HSM_FALSE to use internal random data */
    const uint8_t       *pSalt; /*!< input salt data, , suggest set to NULL. if use hsm internal random data, just set it to NULL */
    uint32_t            u32SaltByteCount; /*!< the byte count of salt data, it must > 0, suggest use hash length, for example, if eHashType is HSM_SHA_256, set this to 256/8=32bytes */
    const uint8_t       *pKeyN; /*!< input key N data for "A = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /*!< key N's data byte count */
    uint8_t             *pResult; /*!< output buffer, the buffer size should >= "u32KeyNByteCount" */
    uint32_t            u32ResultBufByteCnt; /*!< the result buffer size */
    uint32_t            *pResultByteCnt; /*!< the result data byte count */
} HSM_RsaSsaPssSignType;

typedef struct {
    uint32_t               u32HSMStatusRet;
    uint32_t               u32Timeout;
    uint32_t               u32UserKeyID_KEY_E;
    uint32_t               u32UserKeyID_KEY_N;
    uint32_t               u32RsaBitCnt;
    HSM_RsaSsaPssSignType  tCfg;
}HSMCom_RsaSsaPssSignType;

/**
 * @brief RSA PSS signature verify information used by driver when call specific API
 *
 */
typedef struct {
    uint32_t            u32EmBitCnt; /* RFC8017 require set it to (N's bit count - 1). the em data bit count, it MUST < N's bit count, should keep same with the signature generate configuration */
    HSM_HashAlgType     eMgfHashType;
    HSM_HashAlgType     eHashType; /*!< the hash type used by signature */
    uint32_t            u32SaltByteCount; /*!< the byte count of salt data, it must > 0, suggest use hash length, for example, if eHashType is HSM_SHA_256, set this to 256/8=32bytes */
    HSM_DataFormatType  eInputDataFmt; /*!< input data(raw message or hash data) organized format, uint8_t array, or uint32_t array */
    HSM_RsaSsaInputType eInputType; /*!< input data type, may raw input message, or the hash data of raw message */
    const uint8_t       *pInputData; /*!< input data */
    uint32_t            u32InputDataByteCount; /*!< the byte count of input data, when the eInputType is HSM_RSA_SSA_INPUT_RAW_MESSAGE */
    HSM_DataFormatType  eSignDataFmt; /*!< Signature/Public key/N input data organized format, uint8_t array, or uint32_t array */
    const uint8_t       *pSignData; /*!< input signature data */
    uint32_t            u32SignDataByteCount; /*!< the byte count of signature data, it must > 0 */
    HSM_DataFormatType  ePublicKeyDataFmt;
    const uint8_t       *pPublicKey; /*!< public key, input key E data for "A = (input data)^E mod N" */
    uint32_t            u32PublicKeyByteCnt; /*!< the byte count of key E */
    HSM_DataFormatType  eKeyNDataFmt;
    const uint8_t       *pKeyN; /*!< input key N data for "A = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /*!< key N data byte count */
} HSM_RsaSsaPssVerifyType;

typedef struct {
    uint32_t                 u32HSMStatusRet;
    uint32_t                 u32Timeout;
    uint32_t                 u32UserKeyID_KEY_E;
    uint32_t                 u32UserKeyID_KEY_N;
    uint32_t                 u32RsaBitCnt;
    HSM_RsaSsaPssVerifyType  tCfg;
}HSMCom_RsaSsaPssVerifyType;

/**
 * @brief RSA PKCS1 V1.5 signature information used by driver when call specific API
 *
 */
typedef struct {
    HSM_DataFormatType  eInputFmt; /*!< input data organized format, uint8_t array, or uint32_t array */
    HSM_DataFormatType  eOutputFmt; /*!< output data organized format, uint8_t array, or uint32_t array */
    uint32_t            u32EmByteCnt; /* RFC8017 require set it to N'byte count, equal to u32KeyNByteCount. the em data byte count, itx8 MUST < N's bit count, should keep same with the signature generate configuration */
    HSM_HashAlgType     eHashType; /*!< the hash type used by signature */
    const uint8_t       *pInputData; /*!< input data */
    uint32_t            u32InputDataByteCount; /*!< the byte count of input data */
    const uint8_t       *pPrivateKey; /*!< private key, input key E data for "A = (input data)^E mod N" */
    uint32_t            u32PrivateKeyByteCnt; /*!< the byte count of key E */
    HSM_BoolType        bUseInputDer; /*!< set to HSM_TRUE when RFC8017 not support some hash algorithm, for example SM3 Hash type, DER encoding of the DigestInfo value, if use hsm internal data, just set it to HSM_FALSE */
    const uint8_t       *pDer; /*!< when bUseInputDer is HSM_TRUE, this field point to the DER encoding of the DigestInfo value, others, ignore */
    uint32_t            u32DerByteCount; /*!< when bUseInputDer is HSM_TRUE, this field represent the byte count of DER data,  if bUseInputDer is HSM_FALSE, ignore this field */
    const uint8_t       *pKeyN; /*!< input key N data for "A = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /*!< key N's data byte count */
    uint8_t             *pResult; /*!< output buffer, the buffer size should >= "u32KeyNByteCount" */
    uint32_t            u32ResultBufByteCnt; /*!< the result buffer size */
    uint32_t            *pResultByteCnt; /*!< the result data byte count */
} HSM_RsaSsaPkcs1V15SignType;

typedef struct {
    uint32_t                    u32HSMStatusRet;
    uint32_t                    u32Timeout;
    uint32_t                    u32UserKeyID_KEY_E;
    uint32_t                    u32UserKeyID_KEY_N;
    uint32_t                    u32RsaBitCnt;
    HSM_RsaSsaPkcs1V15SignType  tCfg;
}HSMCom_RsaSsaPkcs1V15SignType;

/**
 * @brief RSA PKCS1 V1.5 signature verify information used by driver when call specific API
 *
 */
typedef struct {
    HSM_DataFormatType  eInputFmt; /*!< input data organized format, uint8_t array, or uint32_t array */
    uint32_t            u32EmByteCnt; /* RFC8017 require set it to N'byte count, equal to u32KeyNByteCount. the em data byte count, itx8 MUST < N's bit count, should keep same with the signature generate configuration */
    HSM_HashAlgType     eHashType; /*!< the hash type used by signature */
    const uint8_t       *pInputData; /*!< input data */
    uint32_t            u32InputDataByteCount; /*!< the byte count of input data */
    const uint8_t       *pSignData; /*!< input signature data */
    uint32_t            u32SignDataByteCount; /*!< the byte count of signature data, it must > 0 */
    const uint8_t       *pPublicKey; /*!< public key, input key E data for "A = (input data)^E mod N" */
    uint32_t            u32PublicKeyByteCnt; /*!< the byte count of key E */
    HSM_BoolType        bUseInputDer; /*!< set to HSM_TRUE when RFC8017 not support some hash algorithm, for example SM3 Hash type, DER encoding of the DigestInfo value, if use hsm internal data, just set it to HSM_FALSE */
    const uint8_t       *pDer; /*!< when bUseInputDer is HSM_TRUE, this field point to the DER encoding of the DigestInfo value, others, ignore */
    uint32_t            u32DerByteCount; /*!< when bUseInputDer is HSM_TRUE, this field represent the byte count of DER data,  if bUseInputDer is HSM_FALSE, ignore this field */
    const uint8_t       *pKeyN; /*!< input key N data for "A = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /*!< key N's data byte count */
} HSM_RsaSsaPkcs1V15VerifyType;

typedef struct {
    uint32_t                      u32HSMStatusRet;
    uint32_t                      u32Timeout;
    uint32_t                      u32UserKeyID_KEY_E;
    uint32_t                      u32UserKeyID_KEY_N;
    uint32_t                      u32RsaBitCnt;
    HSM_RsaSsaPkcs1V15VerifyType  tCfg;
}HSMCom_RsaSsaPkcs1V15VerifyType;

typedef struct {

    HSM_BoolType        bUsePseudoRand;
    const uint8_t       *pInputData; /*!< input data */
    uint32_t            u32InputDataByteCount;
    HSM_DataFormatType  eInputDataFmt;
    const uint8_t       *pKeyE;
    uint32_t            u32KeyEByteCount;
    HSM_DataFormatType  eKeyEFmt;
    const uint8_t       *pKeyN;
    uint32_t            u32KeyNByteCount;
    HSM_DataFormatType  eKeyNFmt;
    uint8_t             *pResult;
    uint32_t            u32ResultBufByteCnt;
    HSM_DataFormatType  eOutputFmt;
    uint32_t            *pResultByteCnt;
} HSM_RsaEsPkcs1V15EnDecryptType;

typedef struct {
    uint32_t                        u32HSMStatusRet;
    uint32_t                        u32Timeout;
    uint32_t                        u32UserKeyID_KEY_E;
    uint32_t                        u32UserKeyID_KEY_N;
    uint32_t                        u32RsaBitCnt;
    HSM_RsaEsPkcs1V15EnDecryptType  tCfg;
}HSMCom_RsaEsPkcs1V15EnDecryptType;

typedef HSMCom_RsaEsPkcs1V15EnDecryptType HSMCom_RsaEsPkcs1V15EncryptType;

typedef HSMCom_RsaEsPkcs1V15EnDecryptType HSMCom_RsaEsPkcs1V15DecryptType;

typedef struct {
    HSM_BoolType        bUsePseudoRand;
    HSM_HashAlgType     eHashType; /*!< the hash type used by signature */
    HSM_HashAlgType     eMgfHashType;
    const uint8_t      *pLabel; /*!< input data */
    uint32_t            u32LabelByteCount;
    HSM_DataFormatType  eLabelFmt;
    const uint8_t      *pInputData; /*!< input data */
    uint32_t            u32InputDataByteCount;
    HSM_DataFormatType  eInputDataFmt;
    const uint8_t      *pKeyE;
    uint32_t            u32KeyEByteCount;
    HSM_DataFormatType  eKeyEFmt;
    const uint8_t      *pKeyN;
    uint32_t            u32KeyNByteCount;
    HSM_DataFormatType  eKeyNFmt;
    uint8_t             *pResult;
    uint32_t            u32ResultBufByteCnt;
    HSM_DataFormatType  eOutputFmt;
    uint32_t            *pResultByteCnt;
} HSM_RsaEsOaepEnDecryptType;

typedef struct {
    uint32_t                    u32HSMStatusRet;
    uint32_t                    u32Timeout;
    uint32_t                    u32UserKeyID_KEY_E;
    uint32_t                    u32UserKeyID_KEY_N;
    uint32_t                    u32RsaBitCnt;
    HSM_RsaEsOaepEnDecryptType  tCfg;
}HSMCom_RsaEsOaepEnDecryptType;


typedef HSMCom_RsaEsOaepEnDecryptType HSMCom_RsaEsOaepEncryptType;

typedef HSMCom_RsaEsOaepEnDecryptType HSMCom_RsaEsOaepDecryptType;


typedef struct {
    uint32_t          u32HSMStatusRet;
    uint32_t          u32Timeout;
    uint32_t          u32UserKeyID_Password; //0 means don't load key from HSM, otherwise would load key with KEYID from HSM
    HSM_PBKDF2Type    tCfg;
} HSMCom_Pbkdf2Type;

typedef struct {
    uint32_t        u32Counter;
    uint32_t        u32dkLen;
    uint32_t        u32PasswordByteLength;
    const uint32_t  *pPassword;
    uint32_t        u32SaltByteLength;
    const uint32_t  *pSalt;
    uint32_t        *pKdfOutput;
} HSM_GMPBKDFType;

typedef struct {
    uint32_t        u32HSMStatusRet;
    uint32_t        u32Timeout;
    uint32_t        u32UserKeyID_Password; //0 means don't load key from HSM, otherwise would load key with KEYID from HSM
    HSM_GMPBKDFType tCfg;
} HSMCom_GMpbkdfType;
/* ------------------------------------------------------------------------------- */

/**@}*/


/**
 * @name API declaration for HSM
 *
 */
/**@{*/

/**
 * @brief Get the true random data
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pRandom  the array address to store the result
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_TrueRandGetSrc0(HSM_CmdType *pCmd, const HSMCom_TrueRandType*pCfg);


/**
 * @brief Get the true random data
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pRandom  the array address to store the result
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_TrueRandGetSrc1(HSM_CmdType *pCmd, const HSMCom_TrueRandType*pCfg);


/**
 * @brief Get the true random data
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pRandom  the array address to store the result
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_TrueRandGetSrcXor(HSM_CmdType *pCmd, const HSMCom_TrueRandType*pCfg);


/**
 * @brief Get the true random data
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pRandom  the array address to store the result
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_TrueRandGet(HSM_CmdType *pCmd, const HSMCom_TrueRandType*pCfg);


/**
 * @brief Get the pseudo random data
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pRandom  the array address to store the result
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_PseudoRandGet(HSM_CmdType *pCmd, const HSMCom_TrueRandType*pCfg);


/**
 * @brief SHA
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sha(HSM_CmdType *pCmd, const HSMCom_ShaType *pCfg);


/**
 * @brief SHAEx
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ShaEx(HSM_CmdType *pCmd, const HSMCom_Sha2Type *pCfg);


/**
 * @brief Md5Ex
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  MD5 parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Md5Ex(HSM_CmdType *pCmd, const HSMCom_Md5Type *pCfg);


/**
 * @brief Sm3Ex
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  SM3 parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm3Ex(HSM_CmdType *pCmd, const HSMCom_Sm3Type *pCfg);


/**
 * @brief HashEx Init
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  HashEx parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_HashInitEx(HSM_CmdType *pCmd, const HSMCom_ShaType *pCfg);


/**
 * @brief HashEx Update
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  HashEx parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_HashUpdateEx(HSM_CmdType *pCmd, const HSMCom_ShaType *pCfg);


/**
 * @brief HashEx Finally
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  HashEx parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_HashFinallyEx(HSM_CmdType *pCmd, const HSMCom_ShaType *pCfg);


/**
 * @brief Scatter Hash Init
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  scatter hash parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterHashInit(HSM_CmdType *pCmd, const HSMCom_ScatterHashType *pCfg);


/**
 * @brief Scatter Hash Update
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  scatter hash parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterHashUpdate(HSM_CmdType *pCmd, const HSMCom_ScatterHashType *pCfg);


/**
 * @brief Scatter Hash Finally
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  scatter hash parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterHashFinally(HSM_CmdType *pCmd, const HSMCom_ScatterHashType *pCfg);

/**
 * @brief ECC Sign
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  ECC sign parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccSign(HSM_CmdType *pCmd, const HSMCom_EccSignType *pCfg);


/**
 * @brief EccPointCalc
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  EccPointCalc parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccPointCalc(HSM_CmdType *pCmd, const HSMCom_EccCalcType *pCfg);


/**
 * @brief ECC Verify
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  ECC verify parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccVerify(HSM_CmdType *pCmd, const HSMCom_EccVerifyType *pCfg);


/**
 * @brief ECC key pair generate
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  ECC key pair parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccGenKeyPair(HSM_CmdType *pCmd, const HSMCom_EccKeyPairGenType *pCfg);


/**
 * @brief SM2 key pair generate
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  SM2 key pair parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenKeyPair(HSM_CmdType *pCmd, const HSMCom_Sm2GenKeyPairType *pCfg);


/**
 * @brief SM2 encrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  SM2 encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2Encry(HSM_CmdType *pCmd, const HSMCom_Sm2EncryptType *pCfg);


/**
 * @brief SM2 decrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  SM2 decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2Decry(HSM_CmdType *pCmd, const HSMCom_Sm2DecryptType *pCfg);


/**
 * @brief SM2 sign
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  SM2 sign parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2Sign(HSM_CmdType *pCmd, const HSMCom_Sm2SignType *pCfg);


/**
 * @brief SM2 verify
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  SM2 verify parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2Verify(HSM_CmdType *pCmd, const HSMCom_Sm2VerifyType *pCfg);


/**
 * @brief SM2 ZA
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  SM2 ZA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenZa(HSM_CmdType *pCmd, const HSMCom_Sm2GenZaType *pCfg);


/**
 * @brief SM2 Hash generate
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  SM2 HASH parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenHash(HSM_CmdType *pCmd, const HSMCom_Sm2GenHashType *pCfg);


/**
 * @brief SM4 encrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  SM4 encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm4Encrypt(HSM_CmdType *pCmd, const HSMCom_Sm4EncryptType *pCfg);


/**
 * @brief SM4 decrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  SM4 decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm4Decrypt(HSM_CmdType *pCmd, const HSMCom_Sm4DecryptType *pCfg);


/**
 * @brief ECC easy encrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  ECC encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccEasyEncry(HSM_CmdType *pCmd, const HSMCom_EccEasyEncryType *pCfg);


/**
 * @brief ECC easy decrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  ECC decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccEasyDecry(HSM_CmdType *pCmd, const HSMCom_EccEasyDecryType *pCfg);


/**
 * @brief RequestAuthorization
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  ECC decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RequestAuthorization(HSM_CmdType *pCmd, const HSMCom_RequestAuthType *pCfg);


/**
 * @brief TakeEffect
 *
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_TakeEffect(HSM_CmdType *pCmd);


/**
 * @brief OemDevEnter
 *
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_OemDevEnter(HSM_CmdType *pCmd);


/**
 * @brief HSM_OemPdtEnter
 *
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_OemPdtEnter(HSM_CmdType *pCmd);

/**
 * @brief HSM_InFieldEnter
 *
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_InFieldEnter(HSM_CmdType *pCmd);


/**
 * @brief CancelJob
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CancelJob(HSM_CmdType *pCmd, const HSMCom_CancelJobType *pCfg);


/**
 * @brief SelfTest
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  self test parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_SelfTest(HSM_CmdType *pCmd, const HSMCom_SelfTestType *pCfg);


/**
 * @brief NvrOtpProgram
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_NvrOtpProgram(HSM_CmdType *pCmd, const HSMCom_NvrOtpType *pCfg);


/**
 * @brief NvrOtpRead
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_NvrOtpRead(HSM_CmdType *pCmd, const HSMCom_NvrOtpType *pCfg);


/**
 * @brief Revoke UserKey
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  UserKeyManage parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_UserKeyRevoke(HSM_CmdType *pCmd, const HSMCom_UserKeyManageType *pCfg);


/**
 * @brief Revoke Umrk0
 *
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RevokeUmrk0(HSM_CmdType *pCmd);


/**
 * @brief Revoke Umrk1
 *
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RevokeUmrk1(HSM_CmdType *pCmd);


/**
 * @brief Revoke Umrk2
 *
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RevokeUmrk2(HSM_CmdType *pCmd);


/**
 * @brief Revoke Umrk3
 *
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RevokeUmrk3(HSM_CmdType *pCmd);


/**
 * @brief UserKeyImport
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_UserKeyImport(HSM_CmdType *pCmd, const HSMCom_UserKeyManageType *pCfg);


/**
 * @brief UserKeyExport
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_UserKeyExport(HSM_CmdType *pCmd, const HSMCom_UserKeyManageType *pCfg);


/**
 * @brief Generate User Key
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_UserKeyGen(HSM_CmdType *pCmd, const HSMCom_UserKeyManageType *pCfg);


/**
 * @brief Generate Usrk
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_GenUsrk(HSM_CmdType *pCmd,const HSMCom_RsaType *pCfg);


/**
 * @brief Erase Key in Flash
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EraseKeyFlash(HSM_CmdType *pCmd, HSMCom_BasicType *pCfg);


/**
 * @brief Enable Ram Key Copy
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EnableKeyRamCopy(HSM_CmdType *pCmd, const HSMCom_UserKeyManageType *pCfg);


/**
 * @brief Disable Ram Key Copy
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_DisableKeyRamCopy(HSM_CmdType *pCmd, const HSMCom_UserKeyManageType *pCfg);


/**
 * @brief GetKeySpaceStatus
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  ECC decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_GetKeySpaceStatus(HSM_CmdType *pCmd, const HSMCom_KeySpaceStatusType *pCfg);


/**
 * @brief TidyUpKeySpace
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  ECC decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_TidyUpKeySpace(HSM_CmdType *pCmd, const HSMCom_KeySpaceStatusType *pCfg);


/**
 * @brief AES encrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  AES encrypt parameters.
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_AesEncrypt(HSM_CmdType *pCmd, const HSMCom_AesEncryptType *pCfg);


/**
 * @brief AES decrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  AES decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_AesDecrypt(HSM_CmdType *pCmd, const HSMCom_AesDecryptType *pCfg);


/**
 * @brief AES FlexEncrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  AES encrypt parameters.
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Aes_FlexEncrypt(HSM_CmdType *pCmd, const HSMCom_FlexAesEncryptType *pCfg);


/**
 * @brief AES FlexDecrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  AES decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_Aes_FlexDecrypt(HSM_CmdType *pCmd, const HSMCom_FlexAesDecryptType *pCfg);


/**
 * @brief CMAC
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  CMAC parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CMac(HSM_CmdType *pCmd, const HSMCom_CMacType *pCfg);


/**
 * @brief CmacAesm
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CmacAesm(HSM_CmdType *pCmd, const HSMCom_AesmRawApiType *pCfg);


/**
 * @brief CmacEx
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  CMAC parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CmacEx(HSM_CmdType *pCmd, const HSMCom_CMacExType *pCfg);


/**
 * @brief Scatter Cmac
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  CMAC parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CmacScatter(HSM_CmdType *pCmd, const HSMCom_ScatterMacType *pCfg);


/**
 * @brief XMAC
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  XMAC parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_XMac(HSM_CmdType *pCmd, const HSMCom_XMacType *pCfg);


/**
 * @brief XMacEx
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  XMAC parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_XMacEx(HSM_CmdType *pCmd, const HSMCom_XMacExType *pCfg);


/**
 * @brief CCM encrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  CCM encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CcmEncry(HSM_CmdType *pCmd, const HSMCom_CcmEncryptType *pCfg);


/**
 * @brief CCM decrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  CCM decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CcmDecry(HSM_CmdType *pCmd, const HSMCom_CcmDecryptType *pCfg);


/**
 * @brief CcmEncryEx
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  Ccm encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CcmEncryEx(HSM_CmdType *pCmd, const HSMCom_CcmEncryptExType *pCfg);


/**
 * @brief CcmDecryEx
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  Ccm decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CcmDecryEx(HSM_CmdType *pCmd, const HSMCom_CcmDecryptExType *pCfg);


/**
 * @brief GCM encrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  GCM encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_GcmEncry(HSM_CmdType *pCmd, const HSMCom_GcmEncryptType *pCfg);


/**
 * @brief GCM decrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  GCM decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_GcmDecry(HSM_CmdType *pCmd, const HSMCom_GcmDecryptType *pCfg);



/**
 * @brief GcmEncryEx
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  Gcm encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_GcmEncryEx(HSM_CmdType *pCmd, const HSMCom_GcmEncryptExType *pCfg);


/**
 * @brief GcmDecryEx
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  Gcm decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_GcmDecryEx(HSM_CmdType *pCmd, const HSMCom_GcmDecryptExType *pCfg);

/**
 * @brief MD5
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  MD5 parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Md5(HSM_CmdType *pCmd, const HSMCom_Md5Type *pCfg);


/**
 * @brief SM3
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  SM3 parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm3(HSM_CmdType *pCmd, const HSMCom_Sm3Type *pCfg);


/**
 * @brief Increase Monotonic Counter
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  MonotonicCounter parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_MonotonicCounterIncrease(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg);


/**
 * @brief Read Monotonic Counter
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  MonotonicCounter parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_MonotonicCounterRead(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg);


/**
 * @brief Set Monotonic Counter Value
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  MonotonicCounter parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_MonotonicCounterSetValue(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg);


/**
 * @brief Read All Flex Counters
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  MonotonicCounter parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_MonotonicReadAllFlexCounters(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg);


/**
 * @brief Set Single Config
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  MonotonicCounter parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_MonotonicCounterSetSingleCfg(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg);


/**
 * @brief Get Single Config
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  MonotonicCounter parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_MonotonicCounterGetSingleCfg(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg);


/**
 * @brief Increase Monotonic Counter 2
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  MonotonicCounter parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_MonotonicIncreaseCounter2(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg);


/**
 * @brief Read Monotonic Counter 2
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  MonotonicCounter parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_MonotonicReadCounter2(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg);


/**
 * @brief Increase Monotonic Counter when equal
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  MonotonicCounter parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_MonotonicIncCountWhenEqu(HSM_CmdType *pCmd, const HSMCom_MonCountType *pCfg);


/**
 * @brief LoadFirmware
 *
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_LoadFirmware(HSM_CmdType *pCmd);


/**
 * @brief RSA
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  RSA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_Rsa(HSM_CmdType *pCmd, const HSMCom_RsaType *pCfg);


/**
 * @brief RSA PSS Sign
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  RSA Sign parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RSA_SSA_PSS_Sign(HSM_CmdType *pCmd, const HSMCom_RsaSsaPssSignType *pCfg);


/**
 * @brief RSA PSS Verify
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  RSA Verify parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RSA_SSA_PSS_Verify(HSM_CmdType *pCmd, const HSMCom_RsaSsaPssVerifyType *pCfg);


/**
 * @brief RSA ES_PKCS1V15 Encrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  RSA encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RSA_SSA_ES_PKCS1V15_Encrypt(HSM_CmdType *pCmd, const HSMCom_RsaEsPkcs1V15EncryptType *pCfg);


/**
 * @brief RSA ES_PKCS1V15 Decrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  RSA decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RSA_SSA_ES_PKCS1V15_Decrypt(HSM_CmdType *pCmd, const HSMCom_RsaEsPkcs1V15DecryptType *pCfg);


/**
 * @brief RSA ES_PKCS1V15 Verify
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  RSA Verify parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RSA_SSA_ES_PKCS1V15_Verify(HSM_CmdType *pCmd, const HSMCom_RsaSsaPkcs1V15VerifyType *pCfg);


/**
 * @brief RSA ES PKCS1V15 Sign
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  RSA Verify parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RSA_SSA_ES_PKCS1V15_Sign(HSM_CmdType *pCmd, const HSMCom_RsaSsaPkcs1V15SignType *pCfg);


/**
 * @brief RSA ES OAEP Encrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  RSA encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RSA_SSA_ES_OAEP_Encrypt(HSM_CmdType *pCmd, const HSMCom_RsaEsOaepEncryptType *pCfg);


/**
 * @brief RSA ES OAEP Decrypt
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  RSA decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RSA_SSA_ES_OAEP_Decrypt(HSM_CmdType *pCmd, const HSMCom_RsaEsOaepDecryptType *pCfg);


/**
 * @brief BigNumberCalc
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_BigNumberCalc(HSM_CmdType *pCmd, const HSMCom_BigNumberCalcType *pCfg);


/**
 * @brief SMDH
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_SMDH(HSM_CmdType *pCmd, HSMCom_SmDHType *pCfg);


/**
 * @brief ECDH
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ECDH(HSM_CmdType *pCmd, HSMCom_ECDHType *pCfg);


/**
 * @brief DH
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_DH(HSM_CmdType *pCmd, HSMCom_RsaDHType *pCfg);


/**
 * @brief PBKDF2
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_PBKDF2(HSM_CmdType *pCmd, HSMCom_Pbkdf2Type *pCfg);


/**
 * @brief GMPBKDF
 * @param pCmd  point to the struct variable used to configure the mailbox information send to HSM core
 * @param pCfg  parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_GMPBKDF(HSM_CmdType *pCmd, HSMCom_GMpbkdfType *pCfg);


/**@}*/

/** @}*/ /* fc7xxx_driver_hsm */

#if defined(__cplusplus)
}
#endif

#endif /* end of DRIVER_HSM_H_ */
