#include "ble_api.h"
#include "ms_hal_ble.h"
#include "ms_hal_hw.h"
#include "../impl/client.h"
#include "../impl/advertising.h"

struct {
    bk_ble_write_cb_t write_cb;
    struct bk_ble_db_cfg *db_cfg;
    ms_dev_ble_service_stack_callback_t service_stack_cb;
    ms_hal_ble_scan_callback_t scan_cb;
} hal_ble_data;


void ble_set_write_cb(bk_ble_write_cb_t func)
{
    hal_ble_data.write_cb = func;
}

ble_err_t bk_ble_create_db (struct bk_ble_db_cfg* ble_db_cfg)
{
    hal_ble_data.db_cfg = ble_db_cfg;
}


/**
 * @brief start/update ble adv data
 * @param void
 * @return void 
 */
ms_hal_result_t ms_hal_ble_nonconn_adv_start(ms_hal_ble_gap_adv_params* param, uint8_t *adv_data, uint16_t adv_len)
{

}

/**
 * @brief stop ble adv
 * @param void
 * @return void 
 */
ms_hal_result_t ms_hal_ble_nonconn_adv_stop(void)
{

}

/**
 * @brief hal interface, start ble stack
 * @param void
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_stack_start(void)
{
    int res = client_init();

    return res == 0 ? MS_HAL_RESULT_SUCCESS : MS_HAL_RESULT_ERROR;  
}

/**
 * @brief hal interface, stop ble stack
 * @param void
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_stack_stop(void)
{

}

/**
 * @brief hal interface, set ble stack callback
 * @param ms_hal_ble_stack_callback_t
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_set_stack_event_register(ms_dev_ble_service_stack_callback_t event_handler)
{

}

/**
 * @brief start/update ble adv data
 * @param void
 * @return void 
 */
void ms_hal_ble_adv_data(uint8_t *adv_buff, uint8_t adv_len, uint8_t *scan_rsp_buff, uint8_t scan_rsp_len)
{
    ad_advertise_data(adv_buff, adv_len);
    ad_scan_response(scan_rsp_buff, scan_rsp_len);
}

/**
 * @brief start ble adv
 * @param void
 * @return void 
 */
void ms_hal_ble_adv_start(void)
{
    ad_register("peripheral");
}

/**
 * @brief stop ble adv
 * @param void
 * @return void 
 */
void ms_hal_ble_adv_stop(void)
{

}

ms_hal_result_t ms_hal_ble_scan_start(ms_hal_ble_scan_params_t *params, ms_hal_ble_scan_callback_t function)
{

}

ms_hal_result_t ms_hal_ble_scan_stop(void)
{

}

/*end*/

/**
 * @brief User provided;get software version
 * @param[out] data  version data pointer
 * @param[in] len  data len
 * @return void
 */
void ms_hal_ble_get_software_version(uint8_t *p_data, uint8_t len)
{

}

/**
 * @brief User provided;get uint8_t ble rssi data
 * @param void
 * @return uint8_t 
 */
uint8_t ms_hal_ble_get_ble_rssi(void)
{

}

/**
 * @brief get advertising state
 * @param[in] void
 * @return
 * @retval MS_BLE_ADV_ON         ble advertising on
 * @retval MS_BLE_ADV_OFF        ble advertising off
 */
uint8_t ms_hal_ble_get_adv_state(void)
{

}

/**
 * @brief get scan state
 * @param[in] void
 * @return
 * @retval MS_BLE_SCAN_ON         ble scan on
 * @retval MS_BLE_SCAN_OFF        ble scan off
 */
uint8_t ms_hal_ble_get_scan_state(void)
{

}

/**
 * @brief disconnect ble
 * @param[in] void
 * @return
 * @retval MS_BLE_RESULT_SUCCESS    disconnect success
 * @retval MS_BLE_RESULT_FAIL       no more connection
 */
uint8_t ms_hal_set_ble_disconnect(void)
{

}

/**
 * @brief get connection state
 * @param[in] void
 * @return ms_hal_result_t
 * @retval MS_BLE_CONNECTED         ble connected
 * @retval MS_BLE_DISCONNECTED      no more connection
 */
ms_hal_result_t ms_hal_ble_get_connection_state(void)
{

}

/**
 * @brief hal interface, add ble gatt service
 * @param[in] handle
 * @param[in] *attrib_database
 * @param[in] attrib_database_count
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_gatt_service_add(ms_hal_ble_gatts_service_handle_t *handle, ms_hal_ble_service_attrib_t **attrib_database, uint16_t attrib_database_count)
{

}

/**
 * @brief hal interface, send ble gatt data
 * @param[in] handle
 * @param[in] attrib_offset
 * @param[in] data
 * @param[in] len
 * @return 
 */
ms_hal_result_t ms_hal_ble_gatt_data_send(ms_hal_ble_gatts_service_handle_t *handle, uint16_t attrib_offset, uint8_t *data, uint16_t len)
{

}

/**
 * @brief User provided; get public key and private key
 * @param[out] p_publicKey      public key pointer;64byte,little endian
 * @param[out] p_private_key     private key pointer;32byte,little endian
 * @return void
 */
void ms_hal_ble_ecdh_generate_keys_secp256r1(uint8_t *p_publicKey, uint8_t *p_private_key)
{

}

/**
 * @brief User provided;ecdh secp256r1 get secret key;
 * @param[in] p_publicKey       public key pointer;64byte,little endian
 * @param[in] p_private_key      private key pointer;32byte,little endian
 * @param[out] p_sessionKey     session key pointer;32byte,little endian
 * @return void
 */
void ms_hal_ble_ecdh_shared_secret_secp256r1(uint8_t *p_publicKey, uint8_t *p_private_key, uint8_t *p_sessionKey)
{
    
}

