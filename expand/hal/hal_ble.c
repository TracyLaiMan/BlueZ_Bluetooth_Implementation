#include "ble_api.h"
#include "ms_hal_ble.h"
#include "ms_hal_hw.h"
#include "../impl/client.h"
#include "../impl/advertising.h"
#include "../impl/gatt.h"

#include <glib.h>
#include <stdio.h>


struct gatt_db_t {
    ms_hal_ble_gatts_service_handle_t handle;
    uint16_t attrib_database_count;
    ms_hal_ble_service_attrib_t **attrib_database;
};

//#define HAL_BLE_DEBUG

#ifdef HAL_BLE_DEBUG
#include "../hal/ms_hal_hw.h"
#define DEBUG(...)  ms_hal_ble_printf(__VA_ARGS__)
#define DEBUG_HEXDUMP(data, len) ms_hal_ble_printf_buf(#data, data, len)
#else 
#define DEBUG(...)
#define DEBUG_HEXDUMP(data, len) 
#endif

static GList *gatt_db_list;

static void db_free(void *data)
{
    struct gatt_db_t *db = data;
    ms_hal_ble_free(db->attrib_database);
    ms_hal_ble_free(db);
}

static void ble_service_stack_callback(ms_hal_ble_stack_state_e state, uint8_t *p_data, uint16_t len)
{
    switch (state)
    {
    case MS_HAL_BLE_STACK_DISCONNCET:
        g_list_free_full(gatt_db_list, db_free);
        gatt_db_list = NULL;
        break;
    
    default:
        break;
    }
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
    client_unint();
    g_list_free_full(gatt_db_list, db_free);
    gatt_db_list = NULL;
    return MS_HAL_RESULT_SUCCESS;
}

/**
 * @brief hal interface, set ble stack callback
 * @param ms_hal_ble_stack_callback_t
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_set_stack_event_register(ms_dev_ble_service_stack_callback_t event_handler)
{
    if(!event_handler)
        return MS_HAL_RESULT_ERROR;
    ms_dev_ble_service_stack_callback_t cb[] = { event_handler, ble_service_stack_callback };
    client_set_event_handler(cb, sizeof(cb) / sizeof(cb[0]));
    return MS_HAL_RESULT_SUCCESS;
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
    ad_unregister();
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


#define UUID_STR_FULL_LEN (36 + 1)  //strlen("00000000-0000-1000-8000-00805F9B34FB")

static char *uuid_to_str(const uint8_t *uuid, uint8_t uuid_type, char *uuid_str)
{
    if(!uuid || !uuid_str)
        return NULL;

    uint8_t len = UUID_STR_FULL_LEN - 1;
    
    if(ENUM_MS_HAL_BLE_UUID_TYPE_16_BIT == uuid_type)
    {
        sprintf(uuid_str, "0000%02X%02X-0000-1000-8000-00805F9B34FB", uuid[1], uuid[0]);
        uuid_str[len] = '\0';
        return uuid_str;
    }
    else if(ENUM_MS_HAL_BLE_UUID_TYPE_128_bit == uuid_type)
    {
        sprintf(uuid_str, "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X", 
                uuid[15], uuid[14], uuid[13], uuid[12], uuid[11], uuid[10], uuid[9], uuid[8], 
                uuid[7], uuid[6], uuid[5], uuid[4], uuid[3], uuid[2], uuid[1], uuid[0]);
        uuid_str[len] = '\0';
        return uuid_str;
    }

    memset(uuid_str, 0, len);
    return NULL;
}

static struct gatt_db_t *gatt_db_find_by_uuid(GList *db_list, const char *uuid)
{
    if(!db_list || !uuid)
        return NULL;
    
    struct gatt_db_t *db = NULL;
    char db_uuid_str[UUID_STR_FULL_LEN] = "";
    for (GList *l =  db_list ; l; l = g_list_next(l)) 
    {
        db = l->data;
        uuid_to_str(db->attrib_database[0]->uuid, db->attrib_database[0]->uuid_type, db_uuid_str);
        if(!strcmp(db_uuid_str, db_uuid_str))
            return db;
    }

    return NULL;
}

static struct gatt_db_t *gatt_db_find_by_handle(GList *db_list, ms_hal_ble_gatts_service_handle_t handle)
{
    if(!db_list)
        return NULL;

    struct gatt_db_t *db;
    for (GList *l =  db_list ; l; l = g_list_next(l)) 
    {
        db = l->data;
        if(db->handle == handle)
            return db;
    }
    return NULL;
}

static ms_hal_ble_service_attrib_t *attrib_find_by_uuid(GList *db_list, const char *uuid)
{
    if(!db_list || !uuid)
        return NULL;
    
    struct gatt_db_t *db = NULL;

    char att_uuid_str[UUID_STR_FULL_LEN] = "";

    for (GList *l =  db_list ; l; l = g_list_next(l)) 
    {
        db = l->data;
        for(int i = 1; i < db->attrib_database_count; i++)
        {
            uuid_to_str(db->attrib_database[i]->uuid, db->attrib_database[i]->uuid_type, att_uuid_str);
            if(!strcmp(att_uuid_str, uuid))
                return db->attrib_database[i];
        }
        
    }
}

static bool gatt_db_is_vaild(ms_hal_ble_service_attrib_t **attrib_database, uint16_t attrib_database_count)
{
    if(!attrib_database || !attrib_database_count)
        return false;

    if(!attrib_database[0] || ENUM_MS_HAL_BLE_ATTRIB_TYPE_SERVICE != attrib_database[0]->att_type)
        return false;

    if(!attrib_database[0]->uuid || 
                (ENUM_MS_HAL_BLE_UUID_TYPE_16_BIT != attrib_database[0]->uuid_type && 
                ENUM_MS_HAL_BLE_UUID_TYPE_128_bit != attrib_database[0]->uuid_type))
        return false;
    
    for(int i = 1; i < attrib_database_count; i++)
    {
        if(!attrib_database[i] || ENUM_MS_HAL_BLE_ATTRIB_TYPE_SERVICE == attrib_database[i]->att_type)
            return false;
        if(!attrib_database[i]->uuid || 
                (ENUM_MS_HAL_BLE_UUID_TYPE_16_BIT != attrib_database[i]->uuid_type && 
                ENUM_MS_HAL_BLE_UUID_TYPE_128_bit != attrib_database[i]->uuid_type))
            return false;
        if(attrib_database[i]->perm == MS_HAL_BLE_ATTRIB_PERM_NONE)
            return false;
    }

    return true;    
}

static char *permission_to_str(uint8_t perm, char *perm_str)
{
    if(!perm_str)
        return NULL;

    if(MS_HAL_BLE_ATTRIB_PERM_READ & perm)
        strcpy(perm_str + strlen(perm_str), "read");
    
    if(MS_HAL_BLE_ATTRIB_PERM_WRITE & perm)
        strcpy(perm_str + strlen(perm_str), ",write");
    
    if(MS_HAL_BLE_ATTRIB_PERM_NOTIF_IND & perm)
        strcpy(perm_str + strlen(perm_str), ",notify");

    return perm_str;
}

static void ble_data_operator_callback(const char *uuid, uint8_t op, void *data, uint16_t len)
{
    if(!uuid)
    {
        DEBUG("UUID is null\n");
        return ;
    }
        
    
    ms_hal_ble_service_attrib_t *attrib = attrib_find_by_uuid(gatt_db_list, uuid);
    if(!attrib)
    {
        DEBUG("Attribute: %s not found\n", uuid);
        return ;
    }

    switch (op)
    {
    case DATA_OP_READ:
        if(attrib->callback.read_cb)
            attrib->callback.read_cb(data, len);
        break;
    
    case DATA_OP_WRITE:
        if(attrib->callback.write_cb)
            attrib->callback.write_cb(data, len);
        break;
    
    default:
        DEBUG("Unkown operator: 0x%02x\n", op);
        break;
    }
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
    if(!gatt_db_is_vaild(attrib_database, attrib_database_count))
    {
        DEBUG("Invalid database\n");
        return MS_HAL_RESULT_ERROR;
    }

    struct gatt_db_t *db = gatt_db_find_by_handle(gatt_db_list, *handle);
    if(db)
    {
        DEBUG("Hande %d already exist\n", handle);
        return MS_HAL_RESULT_ERROR;
    }

    char att_db_uuid_str[UUID_STR_FULL_LEN] = "";
    uuid_to_str(attrib_database[0]->uuid, attrib_database[0]->uuid_type, att_db_uuid_str);
    db = gatt_db_find_by_uuid(gatt_db_list, att_db_uuid_str);
    if(db)
    {
        DEBUG("Service already exist\n");
        return MS_HAL_RESULT_ERROR;
    }

    db = ms_hal_ble_malloc(sizeof(struct gatt_db_t));
    if(!db)
    {
        DEBUG("Out of memory\n");
        goto end;
    }

    memset(db, 0, sizeof(struct gatt_db_t));
    db->handle = *handle;
    db->attrib_database_count = attrib_database_count;
    db->attrib_database = ms_hal_ble_malloc(sizeof(ms_hal_ble_service_attrib_t*) * attrib_database_count);
    if(!db->attrib_database)
    {
        DEBUG("Out of memory\n");
        goto end;
    }
    memset(db->attrib_database, 0, sizeof(ms_hal_ble_service_attrib_t*) * attrib_database_count);

    char uuid_str[UUID_STR_FULL_LEN] = "";
    for(int i = 0; i < attrib_database_count; i++)
    {
        db->attrib_database[i] = attrib_database[i];
        uuid_to_str(attrib_database[i]->uuid, attrib_database[i]->uuid_type, uuid_str);
        switch(attrib_database[i]->att_type)
        {
            case ENUM_MS_HAL_BLE_ATTRIB_TYPE_SERVICE:
                DEBUG("%s\n", uuid_str);
                gatt_register_service(uuid_str, 0, true);
                break;

            case ENUM_MS_HAL_BLE_ATTRIB_TYPE_CHAR:
            {
                char perm_str[64] = "";
                permission_to_str(attrib_database[i]->perm, perm_str);
                DEBUG("%s %s\n", uuid_str, perm_str);
                if(strlen(perm_str))
                    gatt_register_chrc(uuid_str, perm_str, 512);
                else 
                    goto end;
                break;
            }
            
            case ENUM_MS_HAL_BLE_ATTRIB_TYPE_CHAR_CLIENT_CONFIG:
            case ENUM_MS_HAL_BLE_ATTRIB_TYPE_CHAR_USER_DESCR:
            {
                char perm_str[64] = "";
                permission_to_str(attrib_database[i]->perm, perm_str);
                DEBUG("%s %s\n", uuid_str, perm_str);
                if(strlen(perm_str))
                    gatt_register_desc(uuid_str, perm_str, 512);
                else 
                    goto end;
                break;
            }
            
            default:
                goto end;
                break;
        }
    }
    if(!gatt_db_list)
    {
        gatt_set_data_op_callback(ble_data_operator_callback);
        gatt_register_app(NULL, 0);
    }
        

    gatt_db_list = g_list_append(gatt_db_list, db);

    return MS_HAL_RESULT_SUCCESS;

end:
    if(db)
    {
        if(db->attrib_database)
            ms_hal_ble_free(db->attrib_database);
        ms_hal_ble_free(db);
    }
  
    return MS_HAL_RESULT_ERROR;
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
    struct gatt_db_t *db = gatt_db_find_by_handle(gatt_db_list, *handle);
    if(!db)
    {
        DEBUG("Handle %d does not exist\n", *handle);
        return MS_HAL_RESULT_ERROR;
    }

    if(attrib_offset >= db->attrib_database_count)
    {
        DEBUG("Offset %d out of range, offset range: 0 ~ %d\n", attrib_offset, db->attrib_database_count);
        return MS_HAL_RESULT_ERROR;
    }

    if(!(db->attrib_database[attrib_offset]->perm & (MS_HAL_BLE_ATTRIB_PERM_NOTIF_IND | MS_HAL_BLE_ATTRIB_PERM_READ)))
    {
        DEBUG("No send permission: 0x%x\n", db->attrib_database[attrib_offset]->perm);
        return MS_HAL_RESULT_ERROR;
    }

    char uuid_str[UUID_STR_FULL_LEN] = "";
    uuid_to_str(db->attrib_database[attrib_offset]->uuid, db->attrib_database[attrib_offset]->uuid_type, uuid_str);
    if(db->attrib_database[attrib_offset]->perm & MS_HAL_BLE_ATTRIB_PERM_NOTIF_IND)
        gatt_notify_update_attribute(uuid_str, data, len);

    if(db->attrib_database[attrib_offset]->perm & MS_HAL_BLE_ATTRIB_PERM_READ) 
        gatt_read_update_attribute(uuid_str, data, len);

    return MS_HAL_RESULT_SUCCESS;
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

