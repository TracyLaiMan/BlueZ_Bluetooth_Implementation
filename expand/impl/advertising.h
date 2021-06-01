#ifndef _ADVERTISING_H_
#define _ADVERTISING_H_
void ad_register(const char *type);
void ad_unregister(void);

void ad_advertise_data(const uint8_t *data, uint16_t len);
void ad_scan_response(const uint8_t *data, uint16_t len);

#endif
