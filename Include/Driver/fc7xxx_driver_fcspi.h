/**
 * @file fc7xxx_driver_fcspi.h
 * @author Flagchip
 * @brief FC7xxx FCSPI driver type definition and API
 * @version 0.1.0
 * @date 2024-1-12
 *
 * @copyright Copyright (c) 2023 Flagchip Semiconductors Co., Ltd.
 *
 */
/********************************************************************************
*   Revision History:
*
*   Version     Date          Initials       CR#          Descriptions
*   ---------   ----------    ------------   ----------   ---------------
*   0.1.0       2024/01/12    Flagchip071    N/A          First version for FC7240
********************************************************************************/
#ifndef _DRIVER_FC7XXX_DRIVER_FCSPI_H_
#define _DRIVER_FC7XXX_DRIVER_FCSPI_H_

#include "device_header.h"
#include "HwA_fcspi.h"
#include "fc7xxx_driver_dma.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup fc4xxx_driver_fcspi
 * @{
 */

/**
 * @brief Status returned by FCSpi APIs
 *
 */
typedef enum {
    FCSPI_STATUS_SUCCESS = 0,    /*!< API execute successfully */
    FCSPI_STATUS_INSTANCE_ERROR, /*!< FCSpi instance index parameter error */
    FCSPI_STATUS_PARAM_ERR,      /*!< parameter error */
    FCSPI_STATUS_ERROR,          /*!< some error occur in API */
    FCSPI_STATUS_NO_DATA,        /*!< user want to transfer nothing */
    FCSPI_STATUS_BUSY,           /*!< FCSpi hardware is busy, not available */
    FCSPI_STATUS_SYNC_TIMEOUT,   /*!< FCSpi synchronous transfer timeout */
    FCSPI_STATUS_TRANSFER_FAIL,  /*!< FCSpi transfer fail */

    FCSPI_STATUS_TRIGGER_OK,            /*!< FCSpi user trigger successfully */
    FCSPI_STATUS_TRIGGER_ABORT_TX_FAIL, /*!< FCSpi user trigger fail due to send underrun */
    FCSPI_STATUS_TRIGGER_ABORT_RX_FAIL, /*!< FCSpi user trigger fail due to receive overflow */
    FCSPI_STATUS_TRIGGER_FINISH         /*!< FCSpi user trigger finish, all data already send */
} FCSPI_StatusType;

/**
 * @name Type definition for FCSpi master/slave mode
 *
 */
/**@{*/

/**
 * @brief FCSpi hardware instances
 *
 * FCSpi consist of multiple hardware instances, for example, FCSPI0, FCSPI1...
 * Just as the enumeration type "FCSPI_InstanceType" definition shows.
 * We use variables of this type to indicate which hardware instance to use.
 */
typedef enum {
    FCSPI_0   = 0,
    FCSPI_1   = 1,
    FCSPI_2   = 2,
    FCSPI_3   = 3,
	FCSPI_4   = 4,
	FCSPI_5   = 5,
} FCSPI_InstanceType;


/**
 * @brief PCS(Peripheral Chip Select) pin select
 *
 * FCSPI has four PCS lines, in our driver code,
 * we use FCSPI_PCS_0/FCSPI_PCS_1/FCSPI_PCS_2/FCSPI_PCS_3 to present them.
 * Like the above, we use enumeration type "FCSPI_PCSType" to indicate
 * which PCS to connect to the external device,
 * "PCS" is short for Peripheral Chip Select,
 * which usually use low level voltage to select the external chip to communicate.
 */
typedef enum {
    FCSPI_PCS_0 = 0U,
    FCSPI_PCS_1 = 1U,
    FCSPI_PCS_2 = 2U,
    FCSPI_PCS_3 = 3U
} FCSPI_PCSType;

/**
 * @brief Valid PCS pin voltage polarity
 *
 * The external device determines the voltage polarity (low or high) of PCS to enable it.
 * So, FCSpi use enumeration type "FCSPI_PcsPolarityType" to indicate
 * the polarity the PCS output when select the external device
 */
typedef enum {
    FCSPI_PCS_POL_ACTIVE_HIGH = 1, /*!< pcs use high level to select external device */
    FCSPI_PCS_POL_ACTIVE_LOW  = 0  /*!< pcs use low level to select external device */
} FCSPI_PcsPolarityType;

/**
 * @brief SCK(serial clock) active phase
 *
 * Just as the SPI bus specification says, clock polarity (CPOL) and clock phase (CPHA) determine the sample point.
 * FCSpi use enumeration type "FCSPI_SckPolarityType" to present CPOL configuration.
 */
typedef enum {
    FCSPI_SCK_ACTIVE_HIGH = 0, /*!< sck is high level when active (idles low). */
    FCSPI_SCK_ACTIVE_LOW  = 1  /*!< sck is low level when active (idles high). */
} FCSPI_SckPolarityType;

/**
 * @brief SCK(serial clock) sample edge
 *
 * Just as the SPI bus specification says,
 * clock polarity (CPOL) and clock phase (CPHA) determine the sample point.
 * FCSpi use enumeration type "FCSPI_SckSamplePhaseType" to present CPHA configuration.
 */
typedef enum {
    FCSPI_SCK_SAMPLE_FIRST_EDGE  = 0, /*!< sample on first edge of sck active polarity, change on second */
    FCSPI_SCK_SAMPLE_SECOND_EDGE = 1  /*!< changed on first edge of sck active polarity, sample on second */
} FCSPI_SckSamplePhaseType;

/**
 * @brief The order of rx/tx handles bit
 *
 * When send or receive data, the MOSI and MISO handle only one bit at a time,
 * FCSpi map the bit data order according to the specific configuration.
 * FCSpi driver provides the enumeration type "FCSPI_BitFirstOrderType" to indicate the order.
 */
typedef enum {
    FCSPI_MSB_FIRST = 0, /*!< most significant bit first handle, from msb to lsb */
    FCSPI_LSB_FIRST = 1  /*!< least significant bit first handle, from lsb to msb */
} FCSPI_BitFirstOrderType;


/**
 * @brief Transfer method between memory and FCSpi's registers
 *
 * FCSpi support transferring data by ISR, DMA, or user poll.
 *
 * If use ISR method, in interrupt handler function,
 * the driver will write data to register "FCSPI_TX_DATA" to push it into Tx FIFO
 * and read the register "FCSPI_RX_DATA" to pop data from Rx FIFO.
 * When finish, the hardware will create an interrupt to notify the end.
 *
 * If use DMA, the DMA channel and priority should also be configured.
 * After configuring these, driver user doesn't need to take care of the detail of transferring.
 * Just send data or send & receive at same time. When finish, the hardware will create an interrupt to notify the end.
 *
 * If use User Poll mode, driver user should call
 * "FCSPI_SyncTransfer" API to move the data until it return error or finished.
 * In this mode, the interrupt in driver is disabled.
 */
typedef enum {
    FCSPI_TRANSFER_TRIGGER_SRC_ISR = 0,  /*!< software(interrupt function) move data between register and memory, when finish, notified by interrupt */
    FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR,  /*!< hardware(DMA) move data between register and memory, when finish, notified by interrupt */
    FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL /*!< NOT use ISR and DMA!!! driver user use API to move data between register and memory, notified by return value when finish */
} FCSPI_TriggerSrcType;


/**
 * @brief transfer stop callback function's prototype
 *
 * FCSpi use this type to define one function pointer variable,
 * which is called when the transfer is aborted or finished.
 */
typedef void (*FCSPI_StopCbType)(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInIsr);


/**
 * @brief Type return by semaphore callback function
 *
 * If want to use synchronous tranfer API, driver user need to provide semaphore callback,
 * these callback function should return value of this enumeration defined.
 */
typedef enum {
    FCSPI_SEMAPHORE_SUCCESS = 0,  /*!< semaphore function execute successfully */
    FCSPI_SEMAPHORE_FAIL    = 1,  /*!< semaphore function execute fail */
    FCSPI_SEMAPHORE_TIMEOUT = 2   /*!< wait to get semaphore until reaching deadline */
} FCSPI_SemaphoreStatType;

/**
 * @brief Callback function to reset semaphore
 *
 * After calling this function, the semaphore variable has a zero semaphore count.
 * Then if try to take the semaphore, the take API will blocks.
 *
 * If the RTOS is FreeRTOS, the reference code as following.
 *
 * @code
 * FCSPI_SemaphoreStatType SpiSemaphoreReset(FCSPI_InstanceType eInst)
 * {
 *     while ( xSemaphoreTake( xSemaphore, ( TickType_t ) 0 ) == pdTRUE );
 *     return FCSPI_SEMAPHORE_SUCCESS;
 * }
 * @endcode
 */
typedef FCSPI_SemaphoreStatType (*FCSPI_SemaphoreResetCbType)(FCSPI_InstanceType eInst);

/**
 * @brief Callback function to obtain semaphore
 *
 * This function will only try to obtain the semaphore before the time expires.
 *
 * If the RTOS is FreeRTOS, the reference code as following.
 *
 * @code
 * FCSPI_SemaphoreStatType SpiSemaphoreTake(FCSPI_InstanceType eInst, uint32_t u32Timeout)
 * {
 *     if ( xSemaphoreTake( xSemaphore, ( TickType_t ) u32Timeout ) == pdTRUE )
 *         return FCSPI_SEMAPHORE_SUCCESS;
 *     else
 *         return FCSPI_SEMAPHORE_TIMEOUT;
 * }
 * @endcode
 */
typedef FCSPI_SemaphoreStatType (*FCSPI_SemaphoreTakeCbType)(FCSPI_InstanceType eInst, uint32_t u32Timeout);


/**
 * @brief Callback function to release semaphore
 *
 * This function will only release semaphore.
 *
 * If the RTOS is FreeRTOS, the reference code as following.
 *
 * @code
 * static FCSPI_SemaphoreStatType SpiSemaphorePost(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInIsr)
 * {
 *     FCSPI_SemaphoreStatType eRet = FCSPI_SEMAPHORE_SUCCESS;
 *
 *     (void)eInst;
 *     if (FCSPI_TRUE == bIsInIsr)
 *     {
 *         BaseType_t tBase = pdFALSE;
 *
 *         if ( xSemaphoreGiveFromISR( xSemaphore, &tBase ) == pdPASS )
 *         {
 *             portYIELD_FROM_ISR(tBase);
 *             eRet = FCSPI_SEMAPHORE_SUCCESS;
 *         }
 *         else
 *         {
 *             eRet = FCSPI_SEMAPHORE_FAIL;
 *         }
 *     }
 *     else
 *     {
 *         if ( xSemaphoreGive( xSemaphore ) == pdPASS )
 *             eRet = FCSPI_SEMAPHORE_SUCCESS;
 *         else
 *             eRet = FCSPI_SEMAPHORE_FAIL;
 *     }
 *
 *     return eRet;
 * }
 * @endcode
 */
typedef FCSPI_SemaphoreStatType (*FCSPI_SemaphorePostCbType)(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInIsr);


/**
 * @brief Asynchronous Transfer data buffer information
 *
 * @note  @verbatim
if init frame bit count need N bytes to store, for example, 7bits need N=1 byte, 9bits need N=2bytes, 23bits need N=3bytes.
N = 1,  one frame data stored in pSendBuffer using uint8_t, driver read data using step 1byte.
N = 2,  one frame data stored in pSendBuffer using uint16_t, driver read data using step 2byte.
N = 3,  one frame data stored in pSendBuffer using uint32_t, driver read data using step 4byte.The highest byte is dropped.
N > 3,  byte count of frame data stored in the parameter pointer pSendBuffer aligned with 4bytes,
        for example, one frame uses 5bytes, it will need two uint32_t, the highest 3bytes are dropped,
        driver API user need declare as "uint32_t data[N]"; it use index 0 to 1, the next frame is 2 to 3.
 @endverbatim
 */
typedef struct {
    const uint8_t *pSendBuffer;    /*!< The buffer containing data to be send, must keep valid before sending is terminated or finished, can be NULL */
    uint8_t       *pReceiveBuffer; /*!< Optional, can be NULL. Buffer to store the data received.The data received is 1byte aligned, no dummy data insert. */
    uint16_t       u16FrameCount;  /*!< The frame count to be sent, the data stored in pSendBuffer is divided into many frames. */
} FCSPI_AsyncDataInfType;


/**
 * @brief Synchronous Transfer data buffer information
 *
 * @note  @verbatim
if init frame bit count need N bytes to store, for example, 7bits need N=1 byte, 9bits need N=2bytes, 23bits need N=3bytes.
N = 1,  one frame data stored in pSendBuffer using uint8_t, driver read data using step 1byte.
N = 2,  one frame data stored in pSendBuffer using uint16_t, driver read data using step 2byte.
N = 3,  one frame data stored in pSendBuffer using uint32_t, driver read data using step 4byte.The highest byte is dropped.
N > 3,  byte count of frame data stored in the parameter pointer pSendBuffer aligned with 4bytes,
        for example, one frame uses 5bytes, it will need two uint32_t, the highest 3bytes are dropped,
        driver API user need declare as "uint32_t data[N]"; it use index 0 to 1, the next frame is 2 to 3.
 @endverbatim
 */
typedef struct {
    const uint8_t *pSendBuffer;     /*!< The buffer containing data to be send, must keep valid before sending is terminated or finished, can be NULL */
    uint8_t       *pReceiveBuffer;  /*!< Optional, can be NULL. Buffer to store the data received.The data received is 1byte aligned, no dummy data insert. */
    uint16_t       u16FrameCount;   /*!< The frame count to be sent, the data stored in pSendBuffer is divided into many frames. */
    uint32_t       u32Timeout;      /*!< The timeout value, it will only be passed to the semaphore callback API configured by driver user */
} FCSPI_SyncDataInfType;

/**
 * @brief tx/rx remain information
 *
 *
 */
typedef struct {
    uint32_t u32ByteCountSendRemained; /*!< byte count remains to be sent */
    uint32_t u32ByteCountReceiveRemained;  /*!< byte count remains to be get */
} FCSPI_TransferRemainInfType;


/**
 * @brief configuration when use DMA
 *
 *
 */
typedef struct {
    DMA_InstanceType     eDMAInstance;           /*!< DMA Instance number, if DMA not used, this ignored */
    uint8_t              u8RxDMAChannel;         /*!< DMA channel number for Rx, if DMA not used, this ignored */
    uint8_t              u8TxDMAChannel;         /*!< DMA channel number for Tx, if DMA not used, this ignored */
    uint8_t              u8RxDMAChannelPriority; /*!< DMA channel priority for Rx, should differ from others in project scope */
    uint8_t              u8TxDMAChannelPriority; /*!< DMA channel priority for Tx, should differ from others in project scope */
} FCSPI_TriggerDmaInfType;
/**@}*/



/**
 * @name Type definition for FCSpi master mode
 *
 */
/**@{*/
/**
 * @brief FCSpi Master mode configuration
 *
 * When One FCSpi instance used as master side, API "FCSPI_Master_Init" need this parameter to configure the driver.
 *
 */
typedef struct {
    uint32_t                      u32FCSpiSrcClk;         /*!< fcspi hardware module source clock */

    /* peripheral chip select configuration */
    FCSPI_PCSType                 ePcs;                  /*!< chip select pin */
    FCSPI_PcsPolarityType         ePcsPolarity;          /*!< chip select pin polarity */
    FCSPI_AtomicBoolType          eIsPcsContinuous;      /*!< keep PCS select enable until transfer finish */

    /* about sample point, sample bit order */
    FCSPI_SckSamplePhaseType      eSckSamplePhase;       /*!< select which edge of active sck clock to capture data */
    FCSPI_SckPolarityType         eSckPolarity;          /*!< select output sclk clock polarity */
    FCSPI_BitFirstOrderType       eBitFirstOrder;        /*!< transmit LSB/MSB first */
    uint32_t                      u32BitCntPerSecond;    /*!< baud rate in bits per second, actual baudrate is calculated in driver, it's the nearest value to this parameter */
    uint16_t                      u16BitCountPerFrame;   /*!< bit count of one frame, should >= 8, we call the data after pcs select, before pcs become invalid, as a frame, */

    FCSPI_TriggerSrcType          eTransferTriggerSrc;    /*!< type of transfer data between memory and data register of FCSPI */

    /* if eTransferTriggerSrc is "FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR", these following fields should be set, or ingore */
    FCSPI_TriggerDmaInfType       tTriggerDmaInf; /*!< if trigger src is DMA, this MUST configure */

    /* if to be notified when transmittion successfully or aborted, need set these following fields */
    FCSPI_StopCbType              pStopNotifyCb;     /*!< transfer stop(transfer successfully or aborted) callback function, can be NULL */

    /* if want to use semaphore to synchronous transfer, the following need to be set */
    FCSPI_SemaphoreResetCbType    pSemaResetCb;   /*!< function to reset the semaphore to init state */
    FCSPI_SemaphoreTakeCbType     pSemaTakeCb;    /*!< function pointer to get the semaphore */
    FCSPI_SemaphorePostCbType     pSemaPostCb;    /*!< function pointer to release the semaphore */
} FCSPI_MasterCfgType;

/**
 * @brief parameters about the holding time (in us) between PCS and SCK
 *
 * Configure the duration (in us) of the clock voltage between PCS and SCK
 */
typedef struct {
    uint32_t u32PCStoPCSHoldUs; /*!< Configures the delay cycles from the PCS negation to the next PCS assertion, in microsecond(us) */
    uint32_t u32SCKtoPCSHoldUs; /*!< Configure the delay cycles from the last SCK edge to the PCS negation, in microsecond(us) */
    uint32_t u32PCStoSCKHoldUs; /*!< Configure the delay cycles from the PCS assertion to the first SCK edge, in microsecond(us) */
} FCSPI_MasterSckPcsHoldTimeType;

/**
 * @brief parameters about the holding time (in PCS/100) between PCS and SCK
 *
 * Configure the duration (in PCS/100) of the clock voltage between PCS and SCK
 */
typedef struct {
    uint32_t u32PCStoPCSHoldPercentage; /*!< Configure the delay cycles from the PCS negation to the next PCS assertion, in PCS/100 */
    uint32_t u32SCKtoPCSHoldPercentage; /*!< Configure the delay cycles from the last SCK edge to the PCS negation, in PCS/100 */
    uint32_t u32PCStoSCKHoldPercentage; /*!< Configure the delay cycles from the PCS assertion to the first SCK edge, in PCS/100 */
} FCSPI_MasterSckPcsHoldSckCycleType;

/**
 * @brief parameters about the PCS and its Polarity
 *
 * Configure the specific PCS to be used and its active polarity when FCSPI running as master side
 */
typedef struct {
    FCSPI_PCSType         ePcs; /*!< Which PCS pin to configure */
    FCSPI_PcsPolarityType ePolarity;  /*!< Pin's active polarity */
} FCSPI_MasterPcsConfType;
/**@}*/


/**
 * @name Type definition for FCSpi slave mode
 *
 */
/**@{*/
/**
 * @brief FCSpi Slave mode configuration
 *
 * When One FCSpi instance used as slave side, API "FCSPI_Slave_Init" need this parameter to configure the driver.
 */
typedef struct {
    FCSPI_BitFirstOrderType       eBitFirstOrder;     /*!< transmit LSB/MSB first */
    uint16_t                      u16BitCountPerFrame;  /*!< bit count of one frame, should >= 8 */

    FCSPI_PcsPolarityType         ePcsPolarity;       /*!< pcs polarity */
    FCSPI_PCSType                 ePcs;               /*!< chip select pin */


    FCSPI_SckSamplePhaseType      eSckSamplePhase;          /*!< select which edge of active sck clock to capture data */
    FCSPI_SckPolarityType         eSckPolarity;       /*!< selects clock polarity */



    FCSPI_TriggerSrcType  eTransferTriggerSrc; /*!< type of transfer data between memory and data register of FCSPI */

    /* if eTransferTriggerSrc is "FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR", these following fields should be set, or ingore */
    FCSPI_TriggerDmaInfType       tTriggerDmaInf; /*!< if trigger src is DMA, this MUST configure */

    /* if to be notified when transmittion stop(successfully, fail, aborted), need set these following fields */
    FCSPI_StopCbType              pStopNotifyCb;   /*!< transfer stop(successfully or fail, or aborted) callback function, can be NULL */

    /* if want to use semaphore to synchronous transfer, the following need to be set */
    FCSPI_SemaphoreResetCbType    pSemaResetCb; /*!< function to reset the semaphore to init state */
    FCSPI_SemaphoreTakeCbType     pSemaTakeCb;  /*!< function pointer to get the semaphore */
    FCSPI_SemaphorePostCbType     pSemaPostCb;  /*!< function pointer to release the semaphore  */
} FCSPI_SlaveCfgType;
/**@}*/

/**
 * @name API declaration for FCSpi master mode
 *
 */
/**@{*/
/**
 * @brief Init the FCSpi instance as spi master side
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Configuration of the FCSpi, MUST NOT NULL
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_Master_Init(const FCSPI_InstanceType eInst, const FCSPI_MasterCfgType *pCfg);

/**
 * @brief Configure the holding time (in us) between PCS and SCK
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Configure the delay parameters between PCS and SCK, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Master_SetSckPcsHoldTime(const FCSPI_InstanceType eInst, const FCSPI_MasterSckPcsHoldTimeType *pCfg);

/**
 * @brief Configure the holding time (in SCK/100) between PCS and SCK
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Configure the delay parameters between PCS and SCK, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Master_SetSckPcsHoldSckPercentage(const FCSPI_InstanceType eInst, const FCSPI_MasterSckPcsHoldSckCycleType *pCfg);
/**
 * @brief Select the PCS to use and configure
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Parameters about PCS configuration, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Master_SelectPcs(const FCSPI_InstanceType eInst, const FCSPI_MasterPcsConfType *pCfg);
/**@}*/

/**
 * @name API declaration for FCSpi slave mode
 *
 */
/**@{*/
/**
 * @brief Init the FCSpi instance as spi slave side
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Configuration of the FCSpi
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_Slave_Init(const FCSPI_InstanceType eInst, const FCSPI_SlaveCfgType *pCfg);
/**@}*/

/**
 * @name Type definition for FCSpi master/slave mode
 *
 */
/**@{*/
/**
 * @brief Send and receive asynchronously
 * 1) If the trigger source is driver user poll, this api not support this mode.
 * 2) If the trigger source is interrupt or DMA, this api will start the transmission, then return immediately.
 *    After transmission stop, it will trigger an interrupt.
 *    During the transmission, the send data buffer and receive data buffer
 *    should keep valid until the transmission stop.
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg the data information, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when start transfer successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_AsyncTransfer(const FCSPI_InstanceType eInst, const FCSPI_AsyncDataInfType *pCfg);

/**
 * @brief Send and receive synchronously
 * 1) If the semaphore callbacks are configured,
 *    and the driver is configured transmitting triggered by interrupt, or by DMA,
 *    the driver will use semaphore to wait the transmission stopped.
 *    In this case, the timeout value is passed to semaphore callback directly.
 * 2) If the semaphore callbacks are not configured,
 *    this api will poll the status when triggered by interrupt or DMA,
 *    or poll to trigger the transmission when the mode is "FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL".
 *    In this case, the timeout value has different meaning for different trigger mode.
 *    Read the source code for detail.
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg the data information, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when transfer successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_SyncTransfer(const FCSPI_InstanceType eInst, const FCSPI_SyncDataInfType *pCfg);

/**
 * @brief If it's in transfer, get its stat, or get the last transfer's stat.
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg the transfer information, can be null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when the last transfer is finish successfully. Others, busy or error occur.
 */
FCSPI_StatusType FCSPI_GetLatestTransferStat(const FCSPI_InstanceType eInst, FCSPI_TransferRemainInfType *pCfg);

/**
 * @brief Abort current transfer if exist, or just recovery the hardware.
 *
 * @param eInst Which FCSpi Hardware instance
 */
void FCSPI_AbortTransfer(const FCSPI_InstanceType eInst);

/**
 * @brief Deinit the FCSpi
 *
 * @param eInst Which FCSpi Hardware instance
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when deinit the FCSpi successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Deinit(const FCSPI_InstanceType eInst);

/**
 * @brief Select the trigger source(DMA with interrupt / interrupt / user poll)
 *
 * @param eInst Which FCSpi Hardware instance
 * @param eSrc three source, 1) DMA move data between memory and registers, notified when finish by interrupt; 2) purely by interrupt; 3) purely by user poll.
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when successfully. Others, error.
 */
FCSPI_StatusType FCSPI_SelectTriggerSrc(FCSPI_InstanceType eInst, FCSPI_TriggerSrcType eSrc);

/**
 * @brief fcspi 0 interrupt handler
 *
 * @note This function should be called as/in FCSPI 0 interrupt handler
 */
void FCSPI0_IRQHandler(void);

/**
 * @brief fcspi 1 interrupt handler
 *
 * @note This function should be called as/in FCSPI 1 interrupt handler
 */
void FCSPI1_IRQHandler(void);

/**
 * @brief fcspi 2 interrupt handler
 *
 * @note This function should be called as/in FCSPI 2 interrupt handler
 */
void FCSPI2_IRQHandler(void);

/**
 * @brief fcspi 3 interrupt handler
 *
 * @note This function should be called as/in FCSPI 3 interrupt handler
 */
void FCSPI3_IRQHandler(void);

/**
 * @brief fcspi 4 interrupt handler
 *
 * @note This function should be called as/in FCSPI 4 interrupt handler
 */
void FCSPI4_IRQHandler(void);

/**
 * @brief fcspi 5 interrupt handler
 *
 * @note This function should be called as/in FCSPI 5 interrupt handler
 */
void FCSPI5_IRQHandler(void);

/**@}*/

/** @}*/ /* fc7xxx_driver_fcspi */

#if defined(__cplusplus)
}
#endif
#endif /* _DRIVER_FC7XXX_DRIVER_FCSPI_H_ */
