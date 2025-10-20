/**
 * @file fc7xxx_driver_scst.h
 * @author Flagchip
 * @brief FC7xxx scst driver type definition and API
 * @version 0.1.0
 * @date 2023-12-29
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*   Revision History:
*
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   0.1.0       2023-12-29    qxw074        N/A          First version for FC7240
******************************************************************************** */

#ifndef _DRIVER_FC7XXX_DRIVER_SCST_H_
#define _DRIVER_FC7XXX_DRIVER_SCST_H_

#include "device_header.h"

/**
 * @addtogroup fc7xxx_driver_scst
 * @{
 */

/**
 * @brief typed of test result returned
 *
 */
typedef enum
{
    M7ST_FaultInjectError,
    M7ST_ErrorAluTest,
    M7ST_ErrorAluMLATest,
    M7ST_ErrorAluSHIFTTest,
    M7ST_ErrorAluTes1t,
    M7ST_ErrorAluTest2,
    M7ST_ErrorAluTest3,
    M7ST_ErrorAluTest4,
    M7ST_ErrorAluTest5,
    M7ST_ErrorAluTest6,
    M7ST_ErrorRegbankTest1,
    M7ST_ErrorRegbankTest2,
    M7ST_ErrorRegbankTest3,
    M7ST_ErrorRegbankTest4,
    M7ST_ErrorRegbankTest5,
    M7ST_ErrorRegbankTest6,
    M7ST_ErrorLoadStoreTest1,
    M7ST_ErrorLoadStoreTest2,
    M7ST_ErrorLoadStoreTest3,
    M7ST_ErrorLoadStoreTest4,
    M7ST_ErrorLoadStoreTest5,
    M7ST_ErrorLoadStoreTest6,
    M7ST_ErrorSimdSatTest1,
    M7ST_ErrorSimdSatTest2,
    M7ST_ErrorSimdSatTest3,
    M7ST_ErrorSimdSatTest4,
    M7ST_ErrorMacTest1,
    M7ST_ErrorMacTest2,
    M7ST_ErrorFetchTest,
    M7ST_ErrorStatusTest1,
    M7ST_ErrorStatusTest2,
    M7ST_ErrorBranchTest1,
    M7ST_ErrorBranchTest2,
    M7ST_ErrorIntSvcTest,
    M7ST_ErrorIntBusFaultTest,
    M7ST_ErrorIntHardFaultTest1,
    M7ST_ErrorIntHardFaultTest2,
    M7ST_ErrorIntUsageFaultTest,
    M7ST_ErrorIntSystickTest,
    M7ST_ErrorIntPendSvTest,
    M7ST_ErrorIntMemFaultTest,
    M7ST_ErrorIntMaskingTest,
    M7ST_ErrorIntHandlerThreadsTest,
    M7ST_ErrorIntNMIHfTest,
    M7ST_ErrorIntTailChainTest,
    M7ST_ErrorIntAluTest,
    M7ST_ErrorIntBranchTest,
    M7ST_ErrorIntStatusTest,
    M7ST_ErrorM7ST_TestPass
} Type_M7ST_AtomicStatus;

/**
 * @brief typed of test index
 *
 */
typedef enum
{
    M7ST_AluTest,
    M7ST_AluMLATest,
    M7ST_AluSHIFTTest,
    M7ST_AluTes1t,
    M7ST_AluTest2,
    M7ST_AluTest3,
    M7ST_AluTest4,
    M7ST_AluTest5,
    M7ST_AluTest6,
    M7ST_RegbankTest1,
    M7ST_RegbankTest2,
    M7ST_RegbankTest3,
    M7ST_RegbankTest4,
    M7ST_RegbankTest5,
    M7ST_RegbankTest6,
    M7ST_LoadStoreTest1,
    M7ST_LoadStoreTest2,
    M7ST_LoadStoreTest3,
    M7ST_LoadStoreTest4,
    M7ST_LoadStoreTest5,
    M7ST_LoadStoreTest6,
    M7ST_SimdSatTest1,
    M7ST_SimdSatTest2,
    M7ST_SimdSatTest3,
    M7ST_SimdSatTest4,
    M7ST_MacTest1,
    M7ST_MacTest2,
    M7ST_FetchTest,
    M7ST_StatusTest1,
    M7ST_StatusTest2,
    M7ST_BranchTest1,
    M7ST_BranchTest2,
    M7ST_RegressionTest
} SCST_TestIndexType;

/**
 * @brief This function is used to get the result of the executed test
 *
 * @param test_index is test number,0U..32U
 * @param s_u32RamBase The first address of the 1k memory that the program needs to run
 * @return M7ST_ErrorM7ST_TestPass is ok, others are not ok
 */
Type_M7ST_AtomicStatus SCST_ExecuteTest(SCST_TestIndexType test_index,uint32_t *s_u32RamBase);

/** @}*/ /* fc7xxx_driver_scst */
#endif
