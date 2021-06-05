#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "gdbus/gdbus.h"
#include "src/shared/util.h"
#include "advertising.h"
#include "impl_private.h"

#define AD_PATH "/org/bluez/advertising"
#define AD_IFACE "org.bluez.LEAdvertisement1"

/* #define ADV_DEBUG */

#ifdef ADV_DEBUG
#include "../hal/ms_hal_hw.h"
#define DEBUG(...)  ms_hal_ble_printf(__VA_ARGS__)
#define DEBUG_HEXDUMP(data, len) ms_hal_ble_printf_buf(#data, data, len)
#else 
#define DEBUG(...)
#define DEBUG_HEXDUMP(data, len) 
#endif


struct ad_data {
	uint8_t data[31];
	uint8_t len;
};

struct data {
	uint8_t type;
	struct ad_data data;
};

static struct ad {
	bool registered;
	char *type;
    struct data adv_data;
    struct data rsp_data;
} ad;

static void ad_release(DBusConnection *conn)
{
	ad.registered = false;

	g_dbus_unregister_interface(conn, AD_PATH, AD_IFACE);
}

static DBusMessage *release_advertising(DBusConnection *conn,
					DBusMessage *msg, void *user_data)
{
	DEBUG("Advertising released\n");

	ad_release(conn);

	return dbus_message_new_method_return(msg);
}

static const GDBusMethodTable ad_methods[] = {
	{ GDBUS_METHOD("Release", NULL, NULL, release_advertising) },
	{ }
};

static void register_setup(DBusMessageIter *iter, void *user_data)
{
	DBusMessageIter dict;
	const char *path = AD_PATH;

	dbus_message_iter_append_basic(iter, DBUS_TYPE_OBJECT_PATH, &path);
	dbus_message_iter_open_container(iter, DBUS_TYPE_ARRAY,
				DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
				DBUS_TYPE_STRING_AS_STRING
				DBUS_TYPE_VARIANT_AS_STRING
				DBUS_DICT_ENTRY_END_CHAR_AS_STRING, &dict);
	dbus_message_iter_close_container(iter, &dict);
}

static void print_ad(void)
{
}

static void register_reply(DBusMessage *message, void *user_data)
{
	DBusConnection *conn = user_data;
	DBusError error;

	dbus_error_init(&error);

	if (dbus_set_error_from_message(&error, message) == FALSE) {
		ad.registered = true;
		DEBUG("Advertising object registered\n");
		stack_event_update(MS_HAL_BLE_STACK_ADV_ON, NULL, 0);
		print_ad();
		/* Leave advertise running even on noninteractive mode */
	} else {
		DEBUG("Failed to register advertisement: %s\n", error.name);
		dbus_error_free(&error);

		if (g_dbus_unregister_interface(conn, AD_PATH,
						AD_IFACE) == FALSE)
			DEBUG("Failed to unregister advertising object\n");
		return ;
	}
}

static gboolean get_type(const GDBusPropertyTable *property,
				DBusMessageIter *iter, void *user_data)
{
	const char *type = "peripheral";

	if (ad.type && strlen(ad.type) > 0)
		type = ad.type;

	dbus_message_iter_append_basic(iter, DBUS_TYPE_STRING, &type);

	return TRUE;
}

static gboolean adv_raw_data_exists(const GDBusPropertyTable *property, void *data)
{
	return ad.adv_data.type != 0;
}

static gboolean get_adv_raw_data(const GDBusPropertyTable *property,
				DBusMessageIter *iter, void *user_data)
{
	DBusMessageIter dict;
	struct ad_data *data = &ad.adv_data.data;
	uint8_t *val = data->data;

    DEBUG("%s\n", __func__);

	dbus_message_iter_open_container(iter, DBUS_TYPE_ARRAY, "{yv}", &dict);

	g_dbus_dict_append_basic_array(&dict, DBUS_TYPE_BYTE, &ad.adv_data.type,
					DBUS_TYPE_BYTE, &val, data->len);

	dbus_message_iter_close_container(iter, &dict);

	return TRUE;
}

static gboolean rsp_raw_data_exists(const GDBusPropertyTable *property, void *data)
{
	return ad.rsp_data.type != 0;
}

static gboolean get_rsp_raw_data(const GDBusPropertyTable *property,
				DBusMessageIter *iter, void *user_data)
{
	DBusMessageIter dict;
	struct ad_data *data = &ad.rsp_data.data;
	uint8_t *val = data->data;

    DEBUG("%s\n", __func__);

	dbus_message_iter_open_container(iter, DBUS_TYPE_ARRAY, "{yv}", &dict);

	g_dbus_dict_append_basic_array(&dict, DBUS_TYPE_BYTE, &ad.rsp_data.type,
					DBUS_TYPE_BYTE, &val, data->len);

	dbus_message_iter_close_container(iter, &dict);

	return TRUE;
}

static const GDBusPropertyTable ad_props[] = {
	{ "Type", "s", get_type },
	{ "AdvertisingRawData", "a{yv}", get_adv_raw_data, NULL, adv_raw_data_exists },
	{ "ResponseRawData", "a{yv}", get_rsp_raw_data, NULL, rsp_raw_data_exists },
	{ }
};

void ad_register(const char *type)
{
    DBusConnection *conn = get_dbus_connection();
    GDBusProxy *manager = get_adapter()->ad_proxy; 
     
    DEBUG("%s\n", __func__);

	if (ad.registered) {
		DEBUG("Advertisement is already registered\n");
		return ;
	}

	g_free(ad.type);
	ad.type = g_strdup(type);

	if (g_dbus_register_interface(conn, AD_PATH, AD_IFACE, ad_methods,
					NULL, ad_props, NULL, NULL) == FALSE) {
		DEBUG("Failed to register advertising object\n");
		return ;
	}

	if (g_dbus_proxy_method_call(manager, "RegisterAdvertisement",
					register_setup, register_reply,
					conn, NULL) == FALSE) {
		DEBUG("Failed to register advertising\n");
		return ;
	}
}

static void unregister_setup(DBusMessageIter *iter, void *user_data)
{
	const char *path = AD_PATH;

	dbus_message_iter_append_basic(iter, DBUS_TYPE_OBJECT_PATH, &path);
}

static void unregister_reply(DBusMessage *message, void *user_data)
{
	DBusConnection *conn = user_data;
	DBusError error;

	dbus_error_init(&error);

	if (dbus_set_error_from_message(&error, message) == FALSE) {
		ad.registered = false;
		DEBUG("Advertising object unregistered\n");
		if (g_dbus_unregister_interface(conn, AD_PATH,
							AD_IFACE) == FALSE)
			DEBUG("Failed to unregister advertising"
					" object\n");

		stack_event_update(MS_HAL_BLE_STACK_ADV_OFF, NULL, 0);
		return ;
	} else {
		DEBUG("Failed to unregister advertisement: %s\n",
								error.name);
		dbus_error_free(&error);
		return ;
	}
}

void ad_unregister(void)
{
    DBusConnection *conn = get_dbus_connection();
    GDBusProxy *manager = get_adapter()->ad_proxy;

	if (!manager)
		ad_release(conn);

	if (!ad.registered)
		return ;

	g_free(ad.type);
	ad.type = NULL;

	if (g_dbus_proxy_method_call(manager, "UnregisterAdvertisement",
					unregister_setup, unregister_reply,
					conn, NULL) == FALSE) {
		DEBUG("Failed to unregister advertisement method\n");
		return ;
	}
}

void ad_advertise_data(const uint8_t *data, uint16_t len)
{
    DBusConnection *conn = get_dbus_connection(); 
    DEBUG("%s\n", __func__);
    if(!data || !len)
    {
        DEBUG("%s: invaild param\n", __func__);
        return;
    }

    uint16_t adv_len = sizeof(ad.adv_data.data);
    adv_len = adv_len > len ? len : adv_len;

    memcpy(ad.adv_data.data.data, data, adv_len);
    ad.adv_data.data.len = adv_len;
    ad.adv_data.type = 'a';

	g_dbus_emit_property_changed(conn, AD_PATH, AD_IFACE, "AdvertisingRawData");

	return ;
}

void ad_scan_response(const uint8_t *data, uint16_t len)
{
    DBusConnection *conn = get_dbus_connection(); 
    DEBUG("%s\n", __func__);
    if(!data || !len)
    {
        DEBUG("%s: invaild param\n", __func__);
        return;
    }

    uint16_t rsp_len = sizeof(ad.rsp_data.data);
    rsp_len = rsp_len > len ? len : rsp_len;

    memcpy(ad.rsp_data.data.data, data, rsp_len);
    ad.rsp_data.data.len = rsp_len;
    ad.rsp_data.type = 'r';

	g_dbus_emit_property_changed(conn, AD_PATH, AD_IFACE, "ResponseRawData");

	return ;
}

