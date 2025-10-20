/**
 * @file fc7xxx_driver_port.h
 * @author Flagchip
 * @brief FC7xxx PORT driver type definition and API
 * @version 0.1.0
 * @date 2023-2-14
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
*   0.1.0       2022/12/31    Flagchip0121    N/A          First version for FC7240
********************************************************************************/
#ifndef _DRIVER_FC7XXX_DRIVER_PORT_H_
#define _DRIVER_FC7XXX_DRIVER_PORT_H_
#include "HwA_port.h"
#include <stddef.h>
/**
 * @addtogroup fc7xxx_driver_port
 * @{
 */

/********* global define ************/
/** @brief Max number of Port */
#define MAX_PORT_NUM 5U

/** @brief Max number of Port Pin  */
#define PORT_PIN_NUM_MAX  (uint32_t)(MAX_PORT_NUM*PORT_PCR_COUNT)

/** @brief number of Port Pin  */
#define PORT_PIN_NUM(port,pin) (((uint32_t)(port) << 5U)+(uint32_t)(pin))

#define PORT_PIN_0        ((uint32_t)0x00000001)    /**< PORT Pin 0 select */
#define PORT_PIN_1        ((uint32_t)0x00000002)    /**< PORT Pin 1 select */
#define PORT_PIN_2        ((uint32_t)0x00000004)    /**< PORT Pin 2 select */
#define PORT_PIN_3        ((uint32_t)0x00000008)    /**< PORT Pin 3 select */
#define PORT_PIN_4        ((uint32_t)0x00000010)    /**< PORT Pin 4 select */
#define PORT_PIN_5        ((uint32_t)0x00000020)    /**< PORT Pin 5 select */
#define PORT_PIN_6        ((uint32_t)0x00000040)    /**< PORT Pin 6 select */
#define PORT_PIN_7        ((uint32_t)0x00000080)    /**< PORT Pin 7 select */
#define PORT_PIN_8        ((uint32_t)0x00000100)    /**< PORT Pin 8 select */
#define PORT_PIN_9        ((uint32_t)0x00000200)    /**< PORT Pin 9 select */
#define PORT_PIN_10       ((uint32_t)0x00000400)    /**< PORT Pin 10 select */
#define PORT_PIN_11       ((uint32_t)0x00000800)    /**< PORT Pin 11 select */
#define PORT_PIN_12       ((uint32_t)0x00001000)    /**< PORT Pin 12 select */
#define PORT_PIN_13       ((uint32_t)0x00002000)    /**< PORT Pin 13 select */
#define PORT_PIN_14       ((uint32_t)0x00004000)    /**< PORT Pin 14 select */
#define PORT_PIN_15       ((uint32_t)0x00008000)    /**< PORT Pin 15 select */
#define PORT_PIN_16       ((uint32_t)0x00010000)    /**< PORT Pin 16 select */
#define PORT_PIN_17       ((uint32_t)0x00020000)    /**< PORT Pin 17 select */
#define PORT_PIN_18       ((uint32_t)0x00040000)    /**< PORT Pin 18 select */
#define PORT_PIN_19       ((uint32_t)0x00080000)    /**< PORT Pin 19 select */
#define PORT_PIN_20       ((uint32_t)0x00100000)    /**< PORT Pin 20 select */
#define PORT_PIN_21       ((uint32_t)0x00200000)    /**< PORT Pin 21 select */
#define PORT_PIN_22       ((uint32_t)0x00400000)    /**< PORT Pin 22 select */
#define PORT_PIN_23       ((uint32_t)0x00800000)    /**< PORT Pin 23 select */
#define PORT_PIN_24       ((uint32_t)0x01000000)    /**< PORT Pin 24 select */
#define PORT_PIN_25       ((uint32_t)0x02000000)    /**< PORT Pin 25 select */
#define PORT_PIN_26       ((uint32_t)0x04000000)    /**< PORT Pin 26 select */
#define PORT_PIN_27       ((uint32_t)0x08000000)    /**< PORT Pin 27 select */
#define PORT_PIN_28       ((uint32_t)0x10000000)    /**< PORT Pin 28 select */
#define PORT_PIN_29       ((uint32_t)0x20000000)    /**< PORT Pin 29 select */
#define PORT_PIN_30       ((uint32_t)0x40000000)    /**< PORT Pin 30 select */
#define PORT_PIN_31       ((uint32_t)0x80000000)    /**< PORT Pin 31 select */

#define PORT_DWP_CPU0_ALLOWED           ((uint32_t)0x00000001)    /**< Only CPU0 is allowed to write PCR and GPIO register corresponding to this pin. */
#define PORT_DWP_DMA0_ALLOWED           ((uint32_t)0x00000008)    /**< Only DMA0 is allowed to write PCR and GPIO register corresponding to this pin. */
#define PORT_DWP_FlexCore_ALLOWED       ((uint32_t)0x00000010)    /**< Only DMA1 is allowed to write PCR and GPIO register corresponding to this pin. */

/** @brief Port Alternate 0 Mode */
#define PORT_ALT0_FUNC_MODE             ((Port_PinModeType)0)
/** @brief Port GPIO Mode */
#define PORT_GPIO_MODE                  ((Port_PinModeType)1)
/** @brief Port Alternate 2 Mode */
#define PORT_ALT2_FUNC_MODE             ((Port_PinModeType)2)
/** @brief Port Alternate 3 Mode */
#define PORT_ALT3_FUNC_MODE             ((Port_PinModeType)3)
/** @brief Port Alternate 4 Mode */
#define PORT_ALT4_FUNC_MODE             ((Port_PinModeType)4)
/** @brief Port Alternate 5 Mode */
#define PORT_ALT5_FUNC_MODE             ((Port_PinModeType)5)
/** @brief Port Alternate 6 Mode */
#define PORT_ALT6_FUNC_MODE             ((Port_PinModeType)6)
/** @brief Port Alternate 7 Mode */
#define PORT_ALT7_FUNC_MODE             ((Port_PinModeType)7)


/********* global typedef ************/
/** @brief Port return structure */
typedef enum
{
    PORT_STATUS_SUCCESS = 0U,
    PORT_STATUS_PARAM_INVALID = 1U
} PORT_StatusType;

/** @brief Port instance number */
typedef enum
{
    PORT_A = 0U,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E
} PORT_InstanceType;

typedef enum
{
    PORT_TRIGGER_DISABLE = 0U,
    PORT_TRIGGER_INPUT_CONSISTENT_WITH_PAD = 1U,
    PORT_TRIGGER_INPUT_OPPOSITE_WITH_PAD = 2U
} PORT_TriggerInputType;

/** @brief Port interrupt notification type */
typedef void (*PORT_PinInterruptCallBackType)(void);

/** @brief Port initialization structure */
typedef struct
{
    uint32_t u32PortPins;                       /**< Port pin, 0~31 bit indicates the pin 0~31 */
    Port_PinMuxType uPortPinMux;                /**< Port pin mode */
    PORT_TriggerInputType eTriggrtMode;         /**< Port trigger mode */
    bool bPullEn;                               /**< whether to pull the port pin */
    PORT_PullStatusType ePullSel;               /**< pull status, pull up or pull down */
    bool bDrvStrength0En;                        /**< whether to enable pad drive strength 0 , only hs PAD used */
    bool bDrvStrength1En;                        /**< whether to enable pad drive strength 1, only uhs PAD used */
    bool u8PassiveFilterEn;                     /**< whether to use passive filter, please refer to reference manual for details */
} PORT_InitType;

/** @brief Port interrupt configuration structure */
typedef struct
{
    uint32_t u32PortPins;                       /**< Port pin, 0~31 bit indicates the pin 0~31 */
    PORT_IntConfigType ePortIsrMode;            /**< Port interrupt mode */
    PORT_PinInterruptCallBackType pIsrNotify;   /**< Port interrupt notification pointer */
} PORT_InterruptType;

/** @brief Port digital filter configuration structure */
typedef struct
{
    uint32_t u32PortPinsEn;                 /**< Port pin, 0~31 bit indicates the pin 0~31 */
    PORT_DigitalFilterClkSrcType eClkSrc;   /**< Port clock source */
    uint8_t u8FilterLength;                 /**< digital filter length, the range is :0~31 */
} PORT_DigitalFilterType;


/********* global API ************/
/**
 * @brief Initialize port pins
 *
 * @param ePort Port instance
 * @param pInitStruct Initialization structure of port
 * @return Port return type.
 */
PORT_StatusType PORT_InitPins(const PORT_InstanceType ePort, const PORT_InitType *const pInitStruct);

/**
 * @brief De-initialize the Port instance
 *
 * @param ePort Port instance enumeration
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 * @return Port return type.
 */
PORT_StatusType PORT_Deinit(const PORT_InstanceType ePort, const uint32_t u32Pins);

/**
 * @brief Enable interrupt function of port
 *
 * @param ePort Port instance enumeration
 * @param pIntStruct Interrupt structure of port.
 * @return Port return type.
 */
PORT_StatusType PORT_InitInterrupt(const PORT_InstanceType ePort, const PORT_InterruptType *const pIntStruct);

/**
 * @brief Enable interrupt function of port
 *
 * @param ePort Port instance enumeration
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 * @return Port return type.
 */
PORT_StatusType PORT_EnableInterrupt(const PORT_InstanceType ePort, const uint32_t u32Pins);

/**
 * @brief Disable interrupt function of port
 *
 * @param ePort Port instance  enumeration
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 * @return Port return type.
 */
PORT_StatusType PORT_DisableInterrupt(const PORT_InstanceType ePort, const uint32_t u32Pins);

PORT_StatusType PORT_SetPinsDmaReqMode(const PORT_InstanceType ePort, const uint32_t u32Pins, const PORT_DMAReqType eDMAReqMode);
/**
 * @brief Initialize digital filter for Port instance
 *
 * @param ePort Port instance enumeration
 * @param pDFStruct Digital filter initialization structure of port
 * @return Port return type.
 */
PORT_StatusType PORT_InitDigitalFilterPort(const PORT_InstanceType ePort,
                                                  const PORT_DigitalFilterType *pDFStruct);

/**
 * @brief De-initialize digital filter for Port instance
 *
 * @param ePort Port instance enumeration
 * @return Port return type.
 */
PORT_StatusType PORT_DeinitDigitalFilterPort(const PORT_InstanceType ePort);

/**
 * @brief Enable the digital filter function for the specific pin.
 *
 * @param ePort Port instance enumeration
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 * @return Port return type.
 */
PORT_StatusType PORT_EnableDigitalFilterPin(const PORT_InstanceType ePort, const uint32_t u32Pins);

/**
 * @brief Disable the digital filter function for the specific pin.
 *
 * @param ePort Port instance enumeration
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 * @return Port return type.
 */
PORT_StatusType PORT_DisableDigitalFilterPin(const PORT_InstanceType ePort, const uint32_t u32Pins);



/** @}*/ /* fc7xxx_driver_port */

#endif

