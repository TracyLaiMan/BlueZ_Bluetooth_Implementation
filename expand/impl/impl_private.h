#ifndef _IMPL_PRIVATE_H_
#define _IMPL_PRIVATE_H_

struct adapter {
	GDBusProxy *proxy;
	GDBusProxy *ad_proxy;
	GList *devices;
};

DBusConnection *get_dbus_connection(void);

struct adapter *get_adapter(void);

void gatt_add_manager(GDBusProxy *proxy);
void gatt_remove_manager(GDBusProxy *proxy);

void gatt_add_service(GDBusProxy *proxy);
void gatt_remove_service(GDBusProxy *proxy);

void gatt_add_characteristic(GDBusProxy *proxy);
void gatt_remove_characteristic(GDBusProxy *proxy);

void gatt_add_descriptor(GDBusProxy *proxy);
void gatt_remove_descriptor(GDBusProxy *proxy);

#endif
