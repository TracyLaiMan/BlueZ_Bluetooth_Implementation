
/**
 * @file ms_hal_flash.h
 * @brief ms hal flash header file
 * @author
 * @version 1.0.0
 * @date 2020-05-16
 * @par Copyright  (c)
 * 		Midea
 */
#ifndef _MS_HAL_FLASH_H__
#define _MS_HAL_FLASH_H__

#include "ms_hal.h"
#include <stdbool.h>

/**
 * @brief enum OTA_AREA_STATUS_E
 */
typedef enum
{
    MS_BLE_OTA_AREA_VALID = 0,   //!< Current firmware area valid
    MS_BLE_OTA_AREA_INVALID = 1, //!< Current firmware area invalid
} ms_hal_ble_ota_area_state_e;

/**
 * @brief struct ms_hal_ble_ota_firmware_t
 */
#pragma pack(1)
typedef struct
{                                        //firmware
    uint8_t fwCurrentArea;               //!< current firmware area
    ms_hal_ble_ota_area_state_e fwState; //!< firmware state @see OTA_AREA_STATE_E
} ms_hal_ble_ota_firmware_t;
#pragma pack()

typedef enum
{
    MS_HAL_FLASH_ERR_FAIL = MS_HAL_RESULT_ERROR,       /**< flash data with specified typed not found*/
    MS_HAL_FLASH_ERR_SUCCESS = MS_HAL_RESULT_SUCCESS, /**< success*/
} ms_hal_flash_err_e;

typedef enum
{
    MS_HAL_FLASH_TYPE_LICENSE,

    MS_HAL_FLASH_TYPE_DEV_0, /**< dev data 0*/
    MS_HAL_FLASH_TYPE_DEV_1, /**< dev data 1*/

    MS_HAL_FLASH_TYPE_SDK_0,
    MS_HAL_FLASH_TYPE_SDK_1,
} ms_hal_flash_type_e;

/**
 * @brief User provided; flash init
 * @param void
 * @return void
 */
void ms_hal_flash_init(void);

/**
 * @brief User provided; flash write
 * @param [in]type flash type
 * @param [in]len data len
 * @param [in]p_data data
 * @return ms_hal_flash_err_e
 */
ms_hal_flash_err_e ms_hal_flash_write(ms_hal_flash_type_e type, uint16_t len, uint8_t *p_data);

/**
 * @brief User provided; flash read
 * @param [in]type flash type
 * @param [in][out]len data len
 * @param [in]p_data data
 * @return ms_hal_flash_err_e
 */
ms_hal_flash_err_e ms_hal_flash_read(ms_hal_flash_type_e type, uint16_t *len, uint8_t *p_data);

/**
 * @brief User provided; flash read cb
 * @param [in]size ota erase flash size
 * @return ms_hal_flash_err_e
 */
ms_hal_flash_err_e ms_hal_ble_ota_flash_erase(uint32_t size);

/**
 * @brief User provided; ota flash write
 * @param [in]offset ota flash addr offset
 * @param [in]len data len
 * @param [in]p_data data
 * @return ms_hal_flash_err_e
 */
ms_hal_flash_err_e ms_hal_ble_ota_flash_write(uint32_t offset, uint32_t len, const uint8_t *data);

// /**
//  * @brief User provided; ota flash read
//  * @param [in]offset ota flash addr offset
//  * @param [in]len data len
//  * @param [in]p_data data
//  * @return ms_hal_flash_err_e
//  */
// ms_hal_flash_err_e ms_hal_ble_ota_flash_read(uint32_t offset, uint32_t len, uint8_t *p_data);

void ms_hal_ble_ota_read_state(ms_hal_ble_ota_firmware_t *state);

/**
 * @brief User provided; ota change area,upgrade firmware
 * @param void
 * @return
 * @retval false    fail
 * @retval true     success
 */
bool ms_hal_ble_ota_change_code_area(void);

/**
 * @brief User provided; ota apply new firmware;restart after response if necessary;
 * @param void
 * @return
 * @retval false    fail
 * @retval true     success
 */
bool ms_hal_ble_ota_apply_new_fw(void);

/**
 * @brief User provided; ota cancel upgrade
 * @param void
 * @return
 * @retval false    fail
 * @retval true     success
 */
bool ms_hal_ble_ota_cancel(void);

/**
 * @brief User provided; get ota boot version
 * @param[out] boot_ver  boot version
 * @return void
 */
void ms_hal_ble_ota_get_boot_version(uint32_t *boot_ver);


#endif /* _MS_HAL_FLASH_H__ */

