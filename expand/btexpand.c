#include "hal/ble_api.h"
#include "hal/ms_hal_ble.h"
#include "hal/ms_hal.h"
#include "hal/ms_hal_hw.h"
#include "hal/ms_hal_flash.h"
#include "hal/ms_hal_timer.h"
#include "hal/ms_hal_watchdog.h"

#include <unistd.h>

static void ms_ble_service_stack_callback(ms_hal_ble_stack_state_e state, uint8_t *p_data, uint16_t len)
{
    switch (state)
    {
    case MS_HAL_BLE_STACK_INIT:
        ms_hal_ble_printf("stack evt: MS_HAL_BLE_STACK_INIT\n");
        break;

    case MS_HAL_BLE_STACK_CREATEDB_OK:
        ms_hal_ble_printf("stack evt: MS_HAL_BLE_STACK_CREATEDB_OK\n");
        break;

    case MS_HAL_BLE_STACK_ADV_ON:
        ms_hal_ble_printf("stack evt: MS_HAL_BLE_STACK_ADV_ON\n");
        break;

    case MS_HAL_BLE_STACK_ADV_OFF:
        ms_hal_ble_printf("stack evt: MS_HAL_BLE_STACK_ADV_OFF\n");
        break;

    case MS_HAL_BLE_STACK_CONNCET:
        ms_hal_ble_printf("stack evt: MS_HAL_BLE_STACK_CONNCET\n");
        break;

    case MS_HAL_BLE_STACK_DISCONNCET:
        ms_hal_ble_printf("stack evt: MS_HAL_BLE_STACK_DISCONNCET\n");
        break;

    case MS_HAL_BLE_STACK_MTU:
        ms_hal_ble_printf("stack evt: MS_HAL_BLE_STACK_MTU\n");
        break;

    case MS_HAL_BLE_STACK_SCAN_ON:
        ms_hal_ble_printf("stack evt: MS_HAL_BLE_STACK_SCAN_ON\n");
        break;

    case MS_HAL_BLE_STACK_SCAN_OFF:
        ms_hal_ble_printf("stack evt: MS_HAL_BLE_STACK_SCAN_OFF\n");
        break;

    case MS_HAL_BLE_STACK_SCAN:
        ms_hal_ble_printf("stack evt: MS_HAL_BLE_STACK_SCAN\n");
        break;

    case MS_HAL_BLE_STACK_ATTINFO_REQ:
        ms_hal_ble_printf("stack evt: MS_HAL_BLE_STACK_ATTINFO_REQ\n");
        break;

    default:
        break;
    }
}

static void ms_ble_service_write_callback(uint8_t *data, uint16_t size)
{
    ms_hal_ble_printf_buf("Written", data, size);
}

int main(int argc, char *argv[])
{
    ms_hal_ble_set_stack_event_register(ms_ble_service_stack_callback);
    ms_hal_ble_stack_start();

    usleep(1 * 1000 * 1000);

    uint8_t adv_data[] = {
        0x02, 0x01, 0x06,
        0x1A, 0xFF, 0x4C, 0x00, 0x02, 0x15, 0x02, 0x12, 0x23, 0x34, 0x54, 0x56, 0x67, 0x78, 0x89, 0x9A, 0xAB, 0xBC, 0xCD, 0xDE, 0xEF, 0xF0, 0x10, 0x00, 0x10, 0x80, 0xC3
    };

    uint8_t scan_rsp[] = {
        0x03, 0x19, 0x00, 0x00,
        0x02, 0x0A, 0x04,
        0x03, 0x03, 0x12, 0x18,
        0x13, 0x08, 0x48, 0x42, 0x33, 0x31, 0x30, 0x30, 0x30, 0x39, 0x35, 0x33, 0x35, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31
    };
    
    ms_hal_ble_adv_data(adv_data, sizeof(adv_data), scan_rsp, sizeof(scan_rsp));

    ms_hal_ble_adv_start();

    ms_hal_ble_gatts_service_handle_t handle = 0;
    ms_hal_ble_service_attrib_t *attrib[3];

    attrib[0] = ms_hal_ble_malloc(sizeof(ms_hal_ble_service_attrib_t));
    memset(attrib[0], 0, sizeof(ms_hal_ble_service_attrib_t));
    attrib[0]->att_type = ENUM_MS_HAL_BLE_ATTRIB_TYPE_SERVICE;
    attrib[0]->uuid_type = ENUM_MS_HAL_BLE_UUID_TYPE_16_BIT;
    attrib[0]->uuid[0] = MS_HAL_BLE_LO_WORD(MS_BLE_CFG_SERVICE_UUID);
    attrib[0]->uuid[1] = MS_HAL_BLE_HI_WORD(MS_BLE_CFG_SERVICE_UUID);
    attrib[0]->prop = MS_HAL_BLE_ATTRIB_CHAR_PROP_NONE;
    attrib[0]->value_len = 0;
    attrib[0]->value_context = NULL;
    attrib[0]->perm = MS_HAL_BLE_ATTRIB_PERM_READ;
    attrib[0]->callback.null_cb = NULL;

    attrib[1] = ms_hal_ble_malloc(sizeof(ms_hal_ble_service_attrib_t));
    memset(attrib[1], 0, sizeof(ms_hal_ble_service_attrib_t));
    attrib[1]->att_type = ENUM_MS_HAL_BLE_ATTRIB_TYPE_CHAR;
    attrib[1]->uuid_type = ENUM_MS_HAL_BLE_UUID_TYPE_16_BIT;
    attrib[1]->uuid[0] = MS_HAL_BLE_LO_WORD(MS_BLE_CFG_DATA_OUT_UUID);
    attrib[1]->uuid[1] = MS_HAL_BLE_HI_WORD(MS_BLE_CFG_DATA_OUT_UUID);
    attrib[1]->prop = MS_HAL_BLE_ATTRIB_CHAR_PROP_WRITE;
    attrib[1]->value_len = 0;
    attrib[1]->value_context = NULL;
    attrib[1]->perm = MS_HAL_BLE_ATTRIB_PERM_READ | MS_HAL_BLE_ATTRIB_PERM_WRITE;
    attrib[1]->callback.null_cb = NULL;
    attrib[1]->callback.write_cb = ms_ble_service_write_callback;

    attrib[2] = ms_hal_ble_malloc(sizeof(ms_hal_ble_service_attrib_t));
    memset(attrib[2], 0, sizeof(ms_hal_ble_service_attrib_t));
    attrib[2]->att_type = ENUM_MS_HAL_BLE_ATTRIB_TYPE_CHAR;
    attrib[2]->uuid_type = ENUM_MS_HAL_BLE_UUID_TYPE_16_BIT;
    attrib[2]->uuid[0] = MS_HAL_BLE_LO_WORD(MS_BLE_CFG_DATA_IN_UUID);
    attrib[2]->uuid[1] = MS_HAL_BLE_HI_WORD(MS_BLE_CFG_DATA_IN_UUID);
    attrib[2]->prop = MS_HAL_BLE_ATTRIB_CHAR_PROP_WRITE;
    attrib[2]->value_len = 0;
    attrib[2]->value_context = NULL;
    attrib[2]->perm = MS_HAL_BLE_ATTRIB_PERM_READ | MS_HAL_BLE_ATTRIB_PERM_NOTIF_IND;
    attrib[2]->callback.null_cb = NULL;

    ms_hal_ble_gatt_service_add(&handle, attrib, 3);

    while(1)
    {
        usleep(1 * 1000 * 1000);

        adv_data[sizeof(adv_data)-1]++;
        scan_rsp[sizeof(scan_rsp)-1] = (scan_rsp[sizeof(scan_rsp)-1] + 1) % 10 + '0';

        ms_hal_ble_adv_data(adv_data, sizeof(adv_data), scan_rsp, sizeof(scan_rsp));

        ms_hal_ble_gatt_data_send(&handle, 2, scan_rsp, sizeof(scan_rsp));
        ms_hal_ble_gatt_data_send(&handle, 1, scan_rsp, sizeof(scan_rsp));
    }

    return 0;
}

