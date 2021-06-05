#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "../hal/ms_hal_ble.h"

int client_init(void);
int client_unint(void);


int client_set_event_handler(ms_dev_ble_service_stack_callback_t *callback, uint16_t callbak_count);

#endif
