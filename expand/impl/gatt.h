#ifndef _IMPL_GATT_H_
#define _IMPL_GATT_H_

#include <stdbool.h>

enum {
    DATA_OP_READ = 0,
    DATA_OP_WRITE,
};


typedef void (*data_operator_callback_t)(const char *uuid, uint8_t op, void *data, uint16_t len);

void gatt_set_data_op_callback(data_operator_callback_t cb);

void gatt_list_attributes(const char *device);

char *gatt_attribute_generator(const char *text, int state);

void gatt_read_update_attribute(const char *uuid, uint8_t *data, uint16_t length);
void gatt_notify_update_attribute(const char *uuid, uint8_t *data, uint16_t length);
void gatt_notify_attribute(const char *uuid, bool enable);

void gatt_acquire_write(const char *uuid, const char *arg);
void gatt_release_write(const char *uuid, const char *arg);

void gatt_acquire_notify(const char *uuid, const char *arg);
void gatt_release_notify(const char *uuid, const char *arg);

void gatt_register_app(const char *uuid_array[], int uuid_count);
void gatt_unregister_app(void);

void gatt_register_service(const char *uuid, uint16_t handle, bool isPrimary);
void gatt_unregister_service(const char *uuid);

void gatt_register_chrc(const char *uuid, const char *flags, uint16_t data_max_len);
void gatt_unregister_chrc(const char *uuid);

void gatt_register_desc(const char *uuid, const char *flags, uint16_t data_max_len);
void gatt_unregister_desc(const char *uuid);

void gatt_register_include(int argc, char *argv[]);
void gatt_unregister_include(int argc, char *argv[]);

#endif
