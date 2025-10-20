/**
 * @file fc7xxx_driver_dsp.h
 * @author Flagchip051
 * @brief FC4xxx DSP driver type definition and API
 * @version 0.1.0
 * @date 2024-01-11
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details @verbatim
If only want use FPU,
1) configure FCIDE to enable FPU compiler support, "Properties" -> C/C++ Build -> Settings -> Tool Settings -> Target Processor -> Float ABI -> FP instructions(hard) -> FPU Type set to "fpv5-sp-d16"
2) configure FCIDE to enable FPU compiler support, "Properties" -> C/C++ Build -> Settings -> Tool Settings -> GNU Arm Cross C Compiler -> Preprocessor -> Defined symbols(-D) -> Add "__FPU_PRESENT=1" (without ")
3) and call FPU_Enable to enable FPU at the beginning of program.

If want to use DSP,
1) configure FCIDE to enable FPU compiler support,  Properties -> C/C++ Build -> Settings -> Tool Settings -> Target Processor -> Float ABI -> FP instructions(hard)
2) add MACRO "DRIVER_CM7_DSP_ENABLE" in FCIDE Properties -> C/C++ General -> Paths and Symbols -> Symbols -> GNU C and GNU C++ and Assembly
3) add Include Path to project Properties -> C/C++ General -> Paths and Symbols -> Includes -> GNU C and GNU C++ and Assembly:
   ../../../../../Template/Device/CMSIS5_590/DSP/Include
   ../../../../../Template/Device/CMSIS5_590/Core/Include
   ../../../../../Template/Device/CMSIS5_590/DSP/PrivateInclude
4) and call FPU_Enable to enable FPU at the beginning of program.
 @endverbatim
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-11    Flagchip054   N/A          First version for FC7240
   ******************************************************************************** */
#ifndef _DRIVER_FC4XXX_DRIVER_DSP_H_
#define _DRIVER_FC4XXX_DRIVER_DSP_H_

#include "device_header.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__cplusplus)
}
#endif
#endif /* _DRIVER_FC4XXX_DRIVER_DSP_H_ */
