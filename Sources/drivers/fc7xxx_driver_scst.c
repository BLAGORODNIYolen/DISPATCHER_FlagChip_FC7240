/**
 * @file fc7xxx_driver_scst.c
 * @author Flagchip
 * @brief FC7xxx scst driver source code
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

#include "fc7xxx_driver_scst.h"

/**
 * @brief The address of the specific implementation of the M7ST API
 *
 */
#define M7ST_ROM_BASE 0x04812800

/**
 * @brief The SCST Atomic Test function prototype
 *
 */
typedef Type_M7ST_AtomicStatus (*Type_M7ST_RegressionTest) (uint32_t TestStart, uint32_t TestEnd, uint32_t InjectEnable, uint32_t RamBase);

/**
 * @brief The SCST Run selected tests function prototype
 *
 */
typedef Type_M7ST_AtomicStatus (*Type_M7ST_AtomicTest) (uint32_t TestID, uint32_t InjectEnable, uint32_t RamBase);

/**
 * @brief M7ST API structure
 *
 */
typedef struct Struct_M7ST_RomTable
{
    Type_M7ST_RegressionTest  RegressionTest;
    Type_M7ST_AtomicTest    AluTest;
    Type_M7ST_AtomicTest    AluMLATest;
    Type_M7ST_AtomicTest    AluSHIFTTest;
    Type_M7ST_AtomicTest    AluTest1;
    Type_M7ST_AtomicTest    AluTest2;
    Type_M7ST_AtomicTest    AluTest3;
    Type_M7ST_AtomicTest    AluTest4;
    Type_M7ST_AtomicTest    AluTest5;
    Type_M7ST_AtomicTest    AluTest6;
    Type_M7ST_AtomicTest    RegbankTest1;
    Type_M7ST_AtomicTest    RegbankTest2;
    Type_M7ST_AtomicTest    RegbankTest3;
    Type_M7ST_AtomicTest    RegbankTest4;
    Type_M7ST_AtomicTest    RegbankTest5;
    Type_M7ST_AtomicTest    RegbankTest6;
    Type_M7ST_AtomicTest    LoadStoreTest1;
    Type_M7ST_AtomicTest    LoadStoreTest2;
    Type_M7ST_AtomicTest    LoadStoreTest3;
    Type_M7ST_AtomicTest    LoadStoreTest4;
    Type_M7ST_AtomicTest    LoadStoreTest5;
    Type_M7ST_AtomicTest    LoadStoreTest6;
    Type_M7ST_AtomicTest    SimdSatTest1;
    Type_M7ST_AtomicTest    SimdSatTest2;
    Type_M7ST_AtomicTest    SimdSatTest3;
    Type_M7ST_AtomicTest    SimdSatTest4;
    Type_M7ST_AtomicTest    MacTest1;
    Type_M7ST_AtomicTest    MacTest2;
    Type_M7ST_AtomicTest    FetchTest;
    Type_M7ST_AtomicTest    StatusTest1;
    Type_M7ST_AtomicTest    StatusTest2;
    Type_M7ST_AtomicTest    BranchTest1;
    Type_M7ST_AtomicTest    BranchTest2;
} Type_M7ST_RomTable;

/**
 * @brief This function is used to get the result of the executed test
 *
 * @param test_index is test number,0U..32U
 * @param s_u32RamBase The first address of the 1k memory that the program needs to run
 * @return M7ST_ErrorM7ST_TestPass is ok, others are not ok
 */
Type_M7ST_AtomicStatus SCST_ExecuteTest(SCST_TestIndexType test_index,uint32_t *s_u32RamBase)
{
    Type_M7ST_AtomicStatus Status = M7ST_FaultInjectError;
    Type_M7ST_RomTable *M7ST_RomEntry = (Type_M7ST_RomTable *)M7ST_ROM_BASE;
    switch(test_index)
    {
        case M7ST_AluTest:
            Status = M7ST_RomEntry->AluTest(0,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_AluMLATest:
            Status = M7ST_RomEntry->AluMLATest(1,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_AluSHIFTTest:
            Status = M7ST_RomEntry->AluSHIFTTest(2,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_AluTes1t:
            Status = M7ST_RomEntry->AluTest1(3,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_AluTest2:
            Status = M7ST_RomEntry->AluTest2(4,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_AluTest3:
            Status = M7ST_RomEntry->AluTest3(5,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_AluTest4:
            Status = M7ST_RomEntry->AluTest4(6,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_AluTest5:
            Status = M7ST_RomEntry->AluTest5(7,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_AluTest6:
            Status = M7ST_RomEntry->AluTest6(8,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_RegbankTest1:
            Status = M7ST_RomEntry->RegbankTest1(9,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_RegbankTest2:
            Status = M7ST_RomEntry->RegbankTest2(10,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_RegbankTest3:
            Status = M7ST_RomEntry->RegbankTest3(11,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_RegbankTest4:
            Status = M7ST_RomEntry->RegbankTest4(12,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_RegbankTest5:
            Status = M7ST_RomEntry->RegbankTest5(13,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_RegbankTest6:
            Status = M7ST_RomEntry->RegbankTest6(14,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_LoadStoreTest1:
            Status = M7ST_RomEntry->LoadStoreTest1(15,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_LoadStoreTest2:
            Status = M7ST_RomEntry->LoadStoreTest2(16,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_LoadStoreTest3:
            Status = M7ST_RomEntry->LoadStoreTest3(17,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_LoadStoreTest4:
            Status = M7ST_RomEntry->LoadStoreTest4(18,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_LoadStoreTest5:
            Status = M7ST_RomEntry->LoadStoreTest5(19,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_LoadStoreTest6:
            Status = M7ST_RomEntry->LoadStoreTest6(20,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_SimdSatTest1:
            Status = M7ST_RomEntry->SimdSatTest1(21,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_SimdSatTest2:
            Status = M7ST_RomEntry->SimdSatTest2(22,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_SimdSatTest3:
            Status = M7ST_RomEntry->SimdSatTest3(23,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_SimdSatTest4:
            Status = M7ST_RomEntry->SimdSatTest4(24,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_MacTest1:
            Status = M7ST_RomEntry->MacTest1(25,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_MacTest2:
            Status = M7ST_RomEntry->MacTest2(26,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_FetchTest:
            Status = M7ST_RomEntry->FetchTest(27,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_StatusTest1:
            Status = M7ST_RomEntry->StatusTest1(28,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_StatusTest2:
            Status = M7ST_RomEntry->StatusTest2(29,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_BranchTest1:
            Status = M7ST_RomEntry->BranchTest1(30,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_BranchTest2:
            Status = M7ST_RomEntry->BranchTest2(31,0,(uint32_t)&s_u32RamBase[0]);
        break;

        case M7ST_RegressionTest:
            Status = M7ST_RomEntry->RegressionTest(0,31,0,(uint32_t)&s_u32RamBase[0]);
        break;

        default:
            break;
    }
    return Status;
}

