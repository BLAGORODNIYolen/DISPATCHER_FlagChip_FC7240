/**
 * @file fc7xxx_driver_mam.c
 * @author Flagchip
 * @brief FC7xxx MAM driver source code
 * @version 0.1.0
 * @date 2023-02-08
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2024-01-10    Flagchip095   N/A          First version for FC7240
   ******************************************************************************** */

#include "fc7xxx_driver_mam.h"
#include "interrupt_manager.h"


#define MAM0_MIN_ADDR   0x01000000U
#define MAM0_MAX_ADDR   0x4049FFFFU

#define ROM_START_ADDR             0x04800000U
#define ROM_END_ADDR               0x0481FFFFU
#define ROM_BLOCK_SIZE             0x20000U

#define FLASH0_START_ADDR          0x01000000U
#define FLASH0_END_ADDR            0x011FFFFFU
#define FLASH0_BLOCK_SIZE          0x20000U

#define NVR_START_ADDR             0x04400000U
#define NVR_END_ADDR               0x04411FFFU
#define NVR_BLOCK_SIZE             0x20000U

#define NVR_CFG_START_ADDR         0x04420000U
#define NVR_CFG_END_ADDR           0x04431FFFU
#define NVR_CFG_BLOCK_SIZE         0x20000U

#define FLASH1_START_ADDR          0x04000000U
#define FLASH1_END_ADDR            0x0401FFFFU
#define FLASH1_BLOCK_SIZE          0x2000U

#define SRAM_START_ADDR            0x21000000U
#define SRAM_END_ADDR              0x21017FFFU
#define SRAM_BLOCK_SIZE            0x4000U

#define CPU0_DTCM_START_ADDR       0x20000000U
#define CPU0_DTCM_END_ADDR         0x2001FFFFU
#define CPU0_DTCM_BLOCK_SIZE       0x4000U

#define CPU0_ITCM_START_ADDR       0x00000000U
#define CPU0_ITCM_END_ADDR         0x00007FFFU
#define CPU0_ITCM_BLOCK_SIZE       0x4000U

#define AFCB0_START_ADDR           0x40000000U
#define AFCB0_END_ADDR             0x4009FFFFU
#define AFCB0_BLOCK_SIZE           0x1000U

#define AFCB1_START_ADDR           0x40400000U
#define AFCB1_END_ADDR             0x4049FFFFU
#define AFCB1_BLOCK_SIZE           0x1000U

/**
 * @brief Get mam information according to the address
 *
 * @param u32Addr Input address
 */
static MAM_Inf_Type MAM_Get_MAM_Inf(uint32_t u32Addr);


/*************** Local Functions ***************/
static MAM_Inf_Type MAM_Get_MAM_Inf(uint32_t u32Addr)
{
	MAM_Inf_Type inf = {.error = 0};
	if(MAM0_MIN_ADDR <= u32Addr && u32Addr < MAM0_MAX_ADDR)
	{
		if(ROM_START_ADDR == u32Addr)
		{
			inf.block_num = 0;
		}
		else if(FLASH0_START_ADDR <= u32Addr && u32Addr < FLASH0_END_ADDR)
		{
			if((u32Addr - FLASH0_START_ADDR)%FLASH0_BLOCK_SIZE == 0U)
			{
				inf.block_num = (u32Addr - FLASH0_START_ADDR) / FLASH0_BLOCK_SIZE + 1U;
			}
			else
			{
				inf.error = 1;
			}
		}
		else if(NVR_START_ADDR <= u32Addr && u32Addr < NVR_END_ADDR)
		{
			if((u32Addr - NVR_START_ADDR)%NVR_BLOCK_SIZE == 0U)
			{
				inf.block_num = (u32Addr - NVR_START_ADDR) / NVR_BLOCK_SIZE + 17U;
			}
			else
			{
				inf.error = 1;
			}
		}
		else if(NVR_CFG_START_ADDR <= u32Addr && u32Addr < NVR_CFG_END_ADDR)
		{
			if((u32Addr - NVR_CFG_START_ADDR)%NVR_CFG_BLOCK_SIZE == 0U)
			{
				inf.block_num = (u32Addr - NVR_CFG_START_ADDR) / NVR_CFG_BLOCK_SIZE + 18U;
			}
			else
			{
				inf.error = 1;
			}
		}	
		else if(FLASH1_START_ADDR <= u32Addr && u32Addr < FLASH1_END_ADDR)
		{
			if((u32Addr - FLASH1_START_ADDR)%FLASH1_BLOCK_SIZE == 0U)
			{
				inf.block_num = (u32Addr - FLASH1_START_ADDR) / FLASH1_BLOCK_SIZE + 19U;
			}
			else
			{
				inf.error = 1;
			}
		}	
		else if(SRAM_START_ADDR <= u32Addr && u32Addr < SRAM_END_ADDR)
		{
			if((u32Addr - SRAM_START_ADDR)%SRAM_BLOCK_SIZE == 0U)
			{
				inf.block_num = (u32Addr - SRAM_START_ADDR) / SRAM_BLOCK_SIZE + 35U;
			}
			else
			{
				inf.error = 1;
			}
		}
		else if(CPU0_DTCM_START_ADDR <= u32Addr && u32Addr < CPU0_DTCM_END_ADDR)
		{
			if((u32Addr - CPU0_DTCM_START_ADDR)%SRAM_BLOCK_SIZE == 0U)
			{
				inf.block_num = (u32Addr - CPU0_DTCM_START_ADDR) / CPU0_DTCM_BLOCK_SIZE + 43U;
			}
			else
			{
				inf.error = 1;
			}
		}
		else if(u32Addr < CPU0_ITCM_END_ADDR)
		{
			if((u32Addr - CPU0_ITCM_START_ADDR)%CPU0_ITCM_BLOCK_SIZE == 0U)
			{
				inf.block_num = (u32Addr - CPU0_ITCM_START_ADDR) / CPU0_ITCM_BLOCK_SIZE + 41U;
			}
			else
			{
				inf.error = 1;
			}
		}
		else if(AFCB0_START_ADDR <= u32Addr && u32Addr < AFCB0_END_ADDR)
		{
			if((u32Addr - AFCB0_START_ADDR)%AFCB0_BLOCK_SIZE == 0U)
			{
				inf.block_num = (u32Addr - AFCB0_START_ADDR) / AFCB0_BLOCK_SIZE + 51U;
			}
			else
			{
				inf.error = 1;
			}
		}
		else if(AFCB1_START_ADDR <= u32Addr && u32Addr < AFCB1_END_ADDR)
		{
			if((u32Addr - AFCB1_START_ADDR)%AFCB1_BLOCK_SIZE == 0U)
			{
				inf.block_num = (u32Addr - AFCB1_START_ADDR) / AFCB1_BLOCK_SIZE + 211U;
			}
			else
			{
				inf.error = 1;
			}
		}
		else
		{
			inf.error = 1;
		}	
	}
	else
	{
		inf.error = 1;
	}
	return inf;
}


/*****************  Global Functions *******************/
uint8_t MAM_Config(MAM_Master_Type Master, uint32_t u32Addr, uint32_t u32Val)
{
	MAM_Inf_Type inf = MAM_Get_MAM_Inf(u32Addr);
	uint32_t reg_idx = 0U;
	uint32_t bit_idx = 0U;
	uint8_t status = 0U;
    if(inf.error == 1U)
    {
    	status = 1;
    }
    else
    {
		reg_idx = inf.block_num / 8U + 47U*(uint32_t)Master; /* 371 block , 371/8 + 1*/
		bit_idx = inf.block_num % 8U;
		Mam_HWA_Set_ACR(MAM, reg_idx, u32Val << (bit_idx * 4U));
		reg_idx = inf.block_num / 32U + 12U*(uint32_t)Master; /* 371 block , 371/32 + 1*/
		bit_idx = inf.block_num % 32U;
		Mam_HWA_Set_ACLR(MAM, reg_idx, 1UL << bit_idx);
    }
    return status;
}

uint8_t MAM_Enable_Wdg(MAM_Master_Type Master,uint32_t u32Addr)
{
	uint8_t status = 0U;
	uint32_t bit_idx = 0U;
	uint32_t regval = 0U;
	MAM_Inf_Type inf = MAM_Get_MAM_Inf(u32Addr);

	if(Master >= MAM_MASTER_NUM || inf.error == 1U)
	{
		status = 1;
	}
	else
	{
		bit_idx = (uint32_t)Master;
		regval = Mam_HWA_Get_Wdgctr(MAM);
		regval |= 1UL << bit_idx;
		Mam_HWA_Set_Wdgctr(MAM, regval);
	}
	return status;
}

uint8_t MAM_Disable_Wdg(MAM_Master_Type Master,uint32_t u32Addr)
{
	uint8_t status = 0U;
	uint32_t regval = 0U;
	uint32_t bit_idx = 0U;
	MAM_Inf_Type inf = MAM_Get_MAM_Inf(u32Addr);

	if(Master >= MAM_MASTER_NUM || inf.error == 1U)
	{
		status = 1;
	}
	else
	{
		bit_idx = (uint32_t)Master;
		regval = Mam_HWA_Get_Wdgctr(MAM);
		regval &= ~(1U << bit_idx);
		Mam_HWA_Set_Wdgctr(MAM, regval);
	}
	return status;
}
