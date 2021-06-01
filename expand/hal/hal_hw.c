#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "ms_hal_hw.h"

/**
 * @brief User provided;get heap size
 * @param void
 * @return uint32_t 
 */
uint32_t ms_hal_hw_get_heap_size(void)
{
    ms_hal_ble_printf("!!! %s: unimplemented\n", __func__);
    return 0;
}

/**
 * @brief hw uart init
 * @param p_uart: the interface which should be initialised
 * @return void 
 */
void ms_hal_hw_uart_init(ms_hal_uart_dev_t *p_uart)
{
    ms_hal_ble_printf("!!! %s: unimplemented\n", __func__);
    (void)p_uart;
}

/**
 * @brief User provided;ctrl uart send
 * @param p_uart the UART interface
 * @param[in] p_data data 
 * @param[in] len buf len
 * @return void 
 */
void ms_hal_hw_uart_send(ms_hal_uart_dev_t *p_uart, uint8_t *p_data, uint16_t len)
{
    ms_hal_ble_printf("!!! %s: unimplemented\n", __func__);
    (void)p_uart;
    (void)p_data;
    (void)len;
}

/**
 * @brief User provided;hw reboot
 * @param void
 * @return void 
 */
void ms_hal_hw_reboot(void)
{
    ms_hal_ble_printf("!!! %s: unimplemented\n", __func__);
}

/**
 * @brief User provided;set ctrl uart recv callback
 * @param p_uart the UART interface
 * @param[in] cb 
 * @return void 
 */
void ms_hal_hw_set_uart_recv_cb(ms_hal_uart_dev_t *p_uart, void (*cb)(uint8_t *, uint16_t))
{
    ms_hal_ble_printf("!!! %s: unimplemented\n", __func__);
    (void)p_uart;
    (void)cb;
}

/**
 * @brief User provided;get random data
 * @param[out] data  data pointer
 * @param[in] len  data len
 */
void ms_hal_ble_get_random(uint8_t *p_data, uint16_t len)
{
    if(!p_data || !len)
    {
        ms_hal_ble_printf("%s: invalid param\n");
        return;
    }
    srand(time(0));
    for(uint16_t i = 0; i < len; i++)
        p_data[i] = (uint8_t)(rand() & 0xff);
}

/**
 * @brief User provided;get ble mac address.
 * @param[out] data  data pointer
 * @param[in] len  data len

 * @return void
 */
void ms_hal_ble_get_mac(uint8_t *p_data, uint16_t len)
{
    if(!p_data || len < 6)
    {
        ms_hal_ble_printf("%s: invalid param('len' must >= 6)\n");
        return;
    }
    ms_hal_ble_memset(p_data, 0, len);
    ms_hal_ble_get_random(p_data, 6);
}

/**
 * @brief User provided;log printf,like int printf(const char *format, ...);
 * @param[in] format  data poniter
 * @return void
 */
void ms_hal_ble_printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
}

/**
 * @brief User provided; printf buf
 * @param[in] name buf name
 * @param[in] p_buf  buf pointer
 * @param[in] len  buf len 
 * @return void
 */
void ms_hal_ble_printf_buf(const char *name, unsigned char *p_buf, unsigned short len)
{
    if(!name)
        ms_hal_ble_printf("unknown data hexdump:\n");
    else
        ms_hal_ble_printf("%s data hexdump:\n", name);

    if(!p_buf || !len)
    {
        ms_hal_ble_printf("\tno data\n");
        return;
    }

    int count_16 = len >> 4;
    int mod_16 = len & 0xf;
    
    for(int i = 0; i < count_16; i++)
    {
        int index = i << 4;
        ms_hal_ble_printf("\t%04x: %02X %02X %02X %02X %02X %02X %02X %02X  %02X %02X %02X %02X %02X %02X %02X %02X\n", 
                          index, p_buf[index + 0], p_buf[index + 1], p_buf[index + 2], p_buf[index + 3], 
                                 p_buf[index + 4], p_buf[index + 5], p_buf[index + 6], p_buf[index + 7],
                                 p_buf[index + 8], p_buf[index + 9], p_buf[index + 10], p_buf[index + 11],
                                 p_buf[index + 12], p_buf[index + 13], p_buf[index + 14], p_buf[index + 15]);

    }

    if(mod_16)
    {
        int index = count_16 << 4;
        ms_hal_ble_printf("\t%04x: ", index);
        for(int i = 0; i < mod_16; i++)
        {
            ms_hal_ble_printf("%02X ", p_buf[index + i]);
            if(8 == i)
                ms_hal_ble_printf(" ");
        }
        ms_hal_ble_printf("\n");
    }
}

/**
 * @brief User provided;like void *malloc(unsigned int size)
 * @param [in] size  malloc size
 * @return void* poniter
 */
void *ms_hal_ble_malloc(uint32_t size)
{
    if(size)
        return malloc(size);
    else 
        return NULL;
}

/**
 * @brief User provided;like void free(void *ptr)
 * @param[in] ptr  ptr pointer
 * @return void
 */
void ms_hal_ble_free(void *ptr)
{
    if(ptr)
        free(ptr);
}

/**
 * @brief User provided;like void *memcpy(void *dest, const void *src, size_t n);
 * @param[in] dest  dest pointer
 * @param[in] src  src pointer
 * @param[in] size  copy len
 * @return void* dest pointer
 */
void *ms_hal_ble_memcpy(void *dest, const void *src, uint32_t size)
{
    return memcpy(dest, src, size);
}

/**
 * @brief User provided;like void *memset(void *s, int ch, size_t n);
 * @param[in] s  dest pointer
 * @param[in] ch  set data
 * @param[in] n  set data len
 * @return void* dest pointer
 */
void *ms_hal_ble_memset(void *s, int ch, uint32_t n)
{
    return memset(s, ch, n);
}

/**
 * @brief User provided;like  int memcmp(const void *str1, const void *str2, size_t n))
 * @param[in] str1 str1 data pointer
 * @param[in] str2 str2 data pointer
 * @param[in] n  Number of bytes to be compared.
 * @return void* dest pointer
 */
int ms_hal_ble_memcmp(const void *str1, const void *str2, uint32_t n)
{
    return memcmp(str1, str2, n);
}
