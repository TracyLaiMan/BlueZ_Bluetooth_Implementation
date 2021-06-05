#ifndef _IMPL_PRIVATE_H_
#define _IMPL_PRIVATE_H_

#include "../hal/ms_hal_ble.h"

struct adapter {
	GDBusProxy *proxy;
	GDBusProxy *ad_proxy;
	GList *devices;
};

DBusConnection *get_dbus_connection(void);

struct adapter *get_adapter(void);

int stack_event_update(ms_hal_ble_stack_state_e event, void *data, uint16_t len);

void gatt_add_manager(GDBusProxy *proxy);
void gatt_remove_manager(GDBusProxy *proxy);

void gatt_add_service(GDBusProxy *proxy);
void gatt_remove_service(GDBusProxy *proxy);

void gatt_add_characteristic(GDBusProxy *proxy);
void gatt_remove_characteristic(GDBusProxy *proxy);

void gatt_add_descriptor(GDBusProxy *proxy);
void gatt_remove_descriptor(GDBusProxy *proxy);


#endif
