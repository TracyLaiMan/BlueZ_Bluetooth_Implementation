

#ifndef _MS_HAL_BLE_DEV_H__
#define _MS_HAL_BLE_DEV_H__

#include "ms_hal.h"
#include <string.h>
#include "ms_hal_ble.h"
#define MS_HAL_BLE_HI_WORD(x)  ((uint8_t)((x & 0xFF00) >> 8))
#define MS_HAL_BLE_LO_WORD(x)  ((uint8_t)(x))

// #define MS_BLE_RESULT_SUCCESS 	1
// #define MS_BLE_RESULT_FAIL		0

typedef enum
{
	MS_HAL_BLE_DISCONNECTED, //!< ble disconnect
	MS_HAL_BLE_CONNECTED,	 //!< ble connect
} ms_hal_ble_conncet_state_e;

enum
{
    PRF_TASK_ID_MS = 0,
    PRF_TASK_ID_MS_TS,
};


///  Service Attributes Indexes ms
enum
{
	MS_IDX_SVC,	 
	MS_IDX_REVICE_VAL_CHAR,
	MS_IDX_REVICE_VAL_VALUE,
	MS_IDX_REVICE_VAL_USER_DESC,
	MS_IDX_SEND_VAL_CHAR,
	MS_IDX_SEND_VAL_VALUE,
	MS_IDX_SEND_VAL_IND_CFG,
	MS_IDX_SEND_VAL_USER_DESC,
	MS_IDX_NB,
};

///  Service Attributes Indexes ms_ts
enum
{
	MS_TS_IDX_SVC,	 
	MS_TS_IDX_REVICE_VAL_CHAR,
	MS_TS_IDX_REVICE_VAL_VALUE,
	MS_TS_IDX_REVICE_VAL_USER_DESC,
	MS_TS_IDX_SEND_VAL_CHAR,
	MS_TS_IDX_SEND_VAL_VALUE,
	MS_TS_IDX_SEND_VAL_IND_CFG,
	MS_TS_IDX_SEND_VAL_USER_DESC,
	MS_TS_IDX_NB,
};


typedef enum
{
    MS_HAL_BLE_STACK_INIT = 0,
    MS_HAL_BLE_STACK_CREATEDB_OK,
    MS_HAL_BLE_STACK_ADV_ON,
    MS_HAL_BLE_STACK_ADV_OFF,
    MS_HAL_BLE_STACK_CONNCET,
    MS_HAL_BLE_STACK_DISCONNCET,
    MS_HAL_BLE_STACK_MTU,
    MS_HAL_BLE_STACK_SCAN_ON,
    MS_HAL_BLE_STACK_SCAN_OFF,
    MS_HAL_BLE_STACK_SCAN,
    MS_HAL_BLE_STACK_ATTINFO_REQ
} ms_hal_ble_stack_state_e;

typedef struct
{
    uint16_t prf_id;
    uint8_t att_idx;
    uint8_t *value;
    uint16_t size;
} read_req_t;

typedef struct
{
    uint16_t ms_ind_cfg;
    uint16_t ms_ts_ind_cfg;
} midea_config_t;


typedef void (*ms_dev_ble_service_stack_callback_t)(ms_hal_ble_stack_state_e state, uint8_t *p_data, uint16_t len);
typedef void (*ms_app_ble_service_stack_callback_t)(ms_hal_ble_stack_state_e state, uint8_t *p_data, uint16_t len);

typedef uint8_t (*bk_ble_read_cb_t)(read_req_t *read_req);

typedef struct
{
    uint32_t	adv_intv_min; /// (in unit of 625us). Must be greater than 20ms
    uint32_t	adv_intv_max; /// (in unit of 625us). Must be greater than 20ms
} ms_hal_ble_gap_adv_params;


/**
 * @brief start/update ble adv data
 * @param void
 * @return void 
 */
ms_hal_result_t ms_hal_ble_nonconn_adv_start(ms_hal_ble_gap_adv_params* param, uint8_t *adv_data, uint16_t adv_len);

/**
 * @brief stop ble adv
 * @param void
 * @return void 
 */
ms_hal_result_t ms_hal_ble_nonconn_adv_stop(void);

/**
 * @brief hal interface, start ble stack
 * @param void
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_stack_start(void);

/**
 * @brief hal interface, stop ble stack
 * @param void
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_stack_stop(void);


/**
 * @brief hal interface, set ble stack callback
 * @param ms_hal_ble_stack_callback_t
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_set_stack_event_register(ms_dev_ble_service_stack_callback_t event_handler);

/**
 * @brief start/update ble adv data
 * @param void
 * @return void 
 */
void ms_hal_ble_adv_data(uint8_t *adv_buff, uint8_t adv_len, uint8_t *scan_rsp_buff, uint8_t scan_rsp_len);

/**
 * @brief start ble adv
 * @param void
 * @return void 
 */
void ms_hal_ble_adv_start(void);

/**
 * @brief stop ble adv
 * @param void
 * @return void 
 */
void ms_hal_ble_adv_stop(void);

/*HAL ble scan*/
typedef enum
{
    MS_HAL_BLE_ADDR_TYPE_PUBLIC = 0,
    MS_HAL_BLE_ADDR_TYPE_RANDOM_STATIC = 1, 
    MS_HAL_BLE_ADDR_TYPE_RANDOM_RESOLVABLE = 2, 
    MS_HAL_BLE_ADDR_TYPE_RANDOM_NON_RESOLVABLE =3, 
}ms_hal_ble_addr_type;

typedef struct
{
    ms_hal_ble_addr_type addr_type;
    uint8_t                addr[6]; 
} ms_hal_ble_addr_t;

typedef enum
{
    MS_HAL_BLE_REPORT_TYPE_IND = 0x00,
    MS_HAL_BLE_REPORT_TYPE_DIRECT_IND = 0x01,
    MS_HAL_BLE_REPORT_TYPE_SCAN_IND = 0x02,
    MS_HAL_BLE_REPORT_TYPE_NONCONN_IND  = 0x03,
    MS_HAL_BLE_REPORT_TYPE_SCAN_RSP = 0x04          
}ms_hal_ble_report_type;

typedef struct
{
    ms_hal_ble_report_type     type;                            
    ms_hal_ble_addr_t     peer_addr; 
    int8_t                   tx_pwr;
    int8_t                     rssi;
    uint16_t                    len;     
    uint8_t                   *data;         
}ms_hal_ble_scan_t;

/*scan callback*/
typedef void (*ms_hal_ble_scan_callback_t)(ms_hal_ble_scan_t *data);

typedef struct
{
    uint8_t                 addr_count; 
    ms_hal_ble_addr_t *        p_addrs; 
} ms_hal_ble_whitelist_t;

typedef enum
{
    MS_HAL_BLE_SCAN_FP_ACCEPT_ALL                          = 0x00,                                                                    
    MS_HAL_BLE_SCAN_FP_WHITELIST                           = 0x01,                                                                    
    MS_HAL_BLE_SCAN_FP_ALL_NOT_RESOLVED_DIRECTED           = 0x02,  
    MS_HAL_BLE_SCAN_FP_WHITELIST_NOT_RESOLVED_DIRECTED     = 0x03,  
}ms_hal_ble_scan_filter_policy_t;

typedef struct
{
    uint8_t    active;			      
    uint8_t    filter_duplicated;              
    ms_hal_ble_scan_filter_policy_t     filter_policy;
    ms_hal_ble_whitelist_t *              p_whitelist;         
    uint16_t                               scan_intvl;         
    uint16_t                              scan_window;         
} ms_hal_ble_scan_params_t;

ms_hal_result_t ms_hal_ble_scan_start(ms_hal_ble_scan_params_t *params,ms_hal_ble_scan_callback_t function);
ms_hal_result_t ms_hal_ble_scan_stop(void);

/*end*/

/**
 * @brief User provided;get software version
 * @param[out] data  version data pointer
 * @param[in] len  data len
 * @return void
 */
void ms_hal_ble_get_software_version(uint8_t *p_data, uint8_t len);

/**
 * @brief User provided;get uint8_t ble rssi data
 * @param void
 * @return uint8_t 
 */
uint8_t ms_hal_ble_get_ble_rssi(void);

/**
 * @brief get advertising state
 * @param[in] void
 * @return
 * @retval MS_BLE_ADV_ON         ble advertising on
 * @retval MS_BLE_ADV_OFF        ble advertising off
 */
uint8_t ms_hal_ble_get_adv_state(void);

/**
 * @brief get scan state
 * @param[in] void
 * @return
 * @retval MS_BLE_SCAN_ON         ble scan on
 * @retval MS_BLE_SCAN_OFF        ble scan off
 */
uint8_t ms_hal_ble_get_scan_state(void);

// /**
//  * @brief User provided;sdk send to ble
//  * @param[in] data     data pointer
//  * @param[in] len      data len
//  * @param[in] pServer   GATT server @see ms_ble_service_e
//  * @return  void
//  */
// void ms_hal_ble_send_ble_data(uint8_t *p_data, uint16_t len, ms_ble_service_e pService);

/**
 * @brief disconnect ble
 * @param[in] void
 * @return
 * @retval MS_BLE_RESULT_SUCCESS    disconnect success
 * @retval MS_BLE_RESULT_FAIL       no more connection
 */
uint8_t ms_hal_set_ble_disconnect(void);

/**
 * @brief get connection state
 * @param[in] void
 * @return ms_hal_result_t
 * @retval MS_BLE_CONNECTED         ble connected
 * @retval MS_BLE_DISCONNECTED      no more connection
 */
ms_hal_result_t ms_hal_ble_get_connection_state(void);

/**
 * \ingroup     GATT_ATTRIBUTE
 */
#define MS_BLE_GATT_UUID_CHAR_EXTENDED_PROP                    0x2900  /**<  Characteristic Extended Properties. */
#define MS_BLE_GATT_UUID_CHAR_USER_DESCR                       0x2901  /**<  Characteristic User Description. */
#define MS_BLE_GATT_UUID_CHAR_CLIENT_CONFIG                    0x2902  /**<  Client Characteristic Configuration. */
#define MS_BLE_GATT_UUID_CHAR_SERVER_CONFIG                    0x2903  /**<  Server Characteristic Configuration. */
#define MS_BLE_GATT_UUID_CHAR_FORMAT                           0x2904  /**<  Characteristic Presentation Format. */
#define MS_BLE_GATT_UUID_CHAR_AGGR_FORMAT                      0x2905  /**<  Characteristic Aggregate Format. */
#define MS_BLE_GATT_UUID_CHAR_VALID_RANGE                      0x2906  /**<  Valid Range. */
#define MS_BLE_GATT_UUID_CHAR_EXTERNAL_REPORT_REFERENCE        0x2907  /**<  External Report Reference. */
#define MS_BLE_GATT_UUID_CHAR_REPORT_REFERENCE                 0x2908  /**<  Report Reference. */
#define MS_BLE_GATT_UUID_CHAR_DESCRIPTOR_NUM_OF_DIGITALS       0x2909  /**<  Number of Digitals. */
#define MS_BLE_GATT_UUID_CHAR_DESCRIPTOR_VALUE_TRIGGER_SETTING 0x290A  /**<  Value Trigger Setting. */
#define MS_BLE_GATT_UUID_CHAR_SENSING_CONFIGURATION            0x290B  /**<  Environmental Sensing Configuration. */
#define MS_BLE_GATT_UUID_CHAR_SENSING_MEASUREMENT              0x290C  /**<  Environmental Sensing Measurement. */
#define MS_BLE_GATT_UUID_CHAR_SENSING_TRIGGER_SETTING          0x290D  /**<  Environmental Sensing Trigger Setting. */
#define MS_BLE_GATT_UUID_CHAR_DESCRIPTOR_TIME_TRIGGER_SETTING  0x290E  /**<  Time Trigger Setting. */

#define MS_BLE_GATT_UUID_PRIMARY_SERVICE       0x2800  /**<  GATT Primary Service Declaration. */
#define MS_BLE_GATT_UUID_SECONDARY_SERVICE     0x2801  /**<  GATT Secondary Service Declaration. */
#define MS_BLE_GATT_UUID_INCLUDE               0x2802  /**<  GATT Include Declaration. */
#define MS_BLE_GATT_UUID_CHARACTERISTIC        0x2803  /**<  GATT Characteristic Declaration. */

#define MS_BLE_CFG_SERVICE_UUID 0xFF80  //!< ble config service UUID;Little-Endian
#define MS_BLE_CFG_DATA_IN_UUID 0xFF81  //!< ble config service in UUID;Little-Endian
#define MS_BLE_CFG_DATA_OUT_UUID 0xFF82 //!< ble config service out UUID;Little-Endian

// UUID Service
// service +characteristic +charc_user_description +client_charc_config
typedef void (*ms_hal_ble_service_null_cb)(void);
typedef void (*ms_hal_ble_service_read_cb)(uint8_t *data, uint16_t size);
typedef void (*ms_hal_ble_service_write_cb)(uint8_t *data, uint16_t size);
typedef void (*ms_hal_ble_service_indicate_cb)(void);

#define MS_HAL_BLE_ATTRIB_CHAR_PROP_NONE                0x00
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_BROADCAST           0x01
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_READ                0x02
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_WRITE_NO_RSP        0x04
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_WRITE               0x08
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_NOTIFY              0x10
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_INDICATE            0x20
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_WRITE_AUTHEN_SIGNED 0x40
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_EXT_PROP            0x80

#define MS_HAL_BLE_ATTRIB_PERM_NONE              0x00
#define MS_HAL_BLE_ATTRIB_PERM_READ              0x01
#define MS_HAL_BLE_ATTRIB_PERM_WRITE             0x02
#define MS_HAL_BLE_ATTRIB_PERM_NOTIF_IND         0x04

#define MS_BLE_CFG_CHAR_INDICATE_OFFSET  5

typedef enum _ms_hal_ble_uuid_type_
{
    ENUM_MS_HAL_BLE_UUID_TYPE_NULL = 0,
    ENUM_MS_HAL_BLE_UUID_TYPE_16_BIT,
    ENUM_MS_HAL_BLE_UUID_TYPE_128_bit,
} ms_hal_ble_uuid_type_t;

typedef enum _ms_hal_ble_attrib_type_
{
    ENUM_MS_HAL_BLE_ATTRIB_TYPE_SERVICE = 1,
    ENUM_MS_HAL_BLE_ATTRIB_TYPE_CHAR,
    ENUM_MS_HAL_BLE_ATTRIB_TYPE_CHAR_VALUE,
    ENUM_MS_HAL_BLE_ATTRIB_TYPE_CHAR_CLIENT_CONFIG,
    ENUM_MS_HAL_BLE_ATTRIB_TYPE_CHAR_USER_DESCR,
} ms_hal_ble_attrib_type_t;

typedef union _ms_hal_ble_attrib_callback_
{
    ms_hal_ble_service_null_cb null_cb;
    ms_hal_ble_service_read_cb read_cb;
    ms_hal_ble_service_write_cb write_cb;
    ms_hal_ble_service_indicate_cb indicate_cb;
}ms_hal_ble_attrib_callback_t;

typedef struct _ms_hal_ble_service_attrib_
{
    uint8_t att_type;
    uint8_t uuid_type;
    uint8_t uuid[2 + 14];
    uint8_t prop;
    uint16_t value_len;
    uint8_t *value_context;
    uint8_t perm;
    ms_hal_ble_attrib_callback_t callback;
} ms_hal_ble_service_attrib_t;

/**
 * att_type is service/characteristic/characteristic_value/char_client_config/char_user_descr, see ms_hal_ble_attrib_type_t
 * uuid_type : see ms_hal_ble_uuid_type_t
 * uuid : 16bit/128bit uuid
 * prop : if att_type is characteristic, you need to choose MS_HAL_BLE_ATTRIB_CHAR_PROP_XXX
 *        if att_type is characteristic_value, you need to check the last characteristic->prop
 * value_len : len of value_context
 * value_context : normal for char_user_descr
 * perm : you need to choose MS_HAL_BLE_ATTRIB_PERM_XXX
 */
typedef int ms_hal_ble_gatts_service_handle_t;

/**
 * @brief hal interface, add ble gatt service
 * @param[in] handle
 * @param[in] *attrib_database
 * @param[in] attrib_database_count
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_gatt_service_add(ms_hal_ble_gatts_service_handle_t *handle, ms_hal_ble_service_attrib_t **attrib_database, uint16_t attrib_database_count);

/**
 * @brief hal interface, send ble gatt data
 * @param[in] handle
 * @param[in] attrib_offset
 * @param[in] data
 * @param[in] len
 * @return 
 */
ms_hal_result_t ms_hal_ble_gatt_data_send(ms_hal_ble_gatts_service_handle_t *handle, uint16_t attrib_offset, uint8_t *data, uint16_t len);

/**
 * @brief User provided; get public key and private key
 * @param[out] p_publicKey      public key pointer;64byte,little endian
 * @param[out] p_private_key     private key pointer;32byte,little endian
 * @return void
 */
void ms_hal_ble_ecdh_generate_keys_secp256r1(uint8_t *p_publicKey, uint8_t *p_private_key);

/**
 * @brief User provided;ecdh secp256r1 get secret key;
 * @param[in] p_publicKey       public key pointer;64byte,little endian
 * @param[in] p_private_key      private key pointer;32byte,little endian
 * @param[out] p_sessionKey     session key pointer;32byte,little endian
 * @return void
 */
void ms_hal_ble_ecdh_shared_secret_secp256r1(uint8_t *p_publicKey, uint8_t *p_private_key, uint8_t *p_sessionKey);

#endif
