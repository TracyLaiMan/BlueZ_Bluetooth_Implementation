
/**
 * @file ms_hal_hw.h
 * @brief ms hal hardware header file,uart\reboot\printf
 * @author
 * @version 1.0.0
 * @date 2020-05-16
 * @par Copyright  (c)
 * 		Midea
 */
#ifndef _MS_HAL_HW_H__
#define _MS_HAL_HW_H__

#include "ms_hal.h"


/*
 * UART data width
 */
typedef enum {
    DATA_WIDTH_5BIT,
    DATA_WIDTH_6BIT,
    DATA_WIDTH_7BIT,
    DATA_WIDTH_8BIT,
    DATA_WIDTH_9BIT
} hal_uart_data_width_t;

/*
 * UART stop bits
 */
typedef enum {
    STOP_BITS_1,
    STOP_BITS_2
} hal_uart_stop_bits_t;

/*
 * UART flow control
 */
typedef enum {
    FLOW_CONTROL_DISABLED,
    FLOW_CONTROL_CTS,
    FLOW_CONTROL_RTS,
    FLOW_CONTROL_CTS_RTS
} hal_uart_flow_control_t;

/*
 * UART parity
 */
typedef enum {
    NO_PARITY,
    ODD_PARITY,
    EVEN_PARITY
} hal_uart_parity_t;

/*
 * UART mode
 */
typedef enum {
    MODE_TX,
    MODE_RX,
    MODE_TX_RX
} hal_uart_mode_t;


/*
 * UART configuration
 */
typedef struct {
    uint32_t                baud_rate;
    hal_uart_data_width_t   data_width;
    hal_uart_parity_t       parity;
    hal_uart_stop_bits_t    stop_bits;
    hal_uart_flow_control_t flow_control;
    hal_uart_mode_t         mode;
} ms_hal_uart_config_t;

typedef struct {
    uint8_t              port;   /* uart port */
    ms_hal_uart_config_t config; /* uart config */
    void                 *priv;   /* priv data */
} ms_hal_uart_dev_t;

/**
 * @brief User provided;get heap size
 * @param void
 * @return uint32_t 
 */
uint32_t ms_hal_hw_get_heap_size(void);


/**
 * @brief hw uart init
 * @param p_uart: the interface which should be initialised
 * @return void 
 */
void ms_hal_hw_uart_init(ms_hal_uart_dev_t *p_uart);

/**
 * @brief User provided;ctrl uart send
 * @param p_uart the UART interface
 * @param[in] p_data data 
 * @param[in] len buf len
 * @return void 
 */
void ms_hal_hw_uart_send(ms_hal_uart_dev_t *p_uart, uint8_t *p_data, uint16_t len);

/**
 * @brief User provided;hw reboot
 * @param void
 * @return void 
 */
void ms_hal_hw_reboot(void);

/**
 * @brief User provided;set ctrl uart recv callback
 * @param p_uart the UART interface
 * @param[in] cb 
 * @return void 
 */
void ms_hal_hw_set_uart_recv_cb(ms_hal_uart_dev_t *p_uart, void (*cb)(uint8_t *, uint16_t));

/**
 * @brief User provided;get random data
 * @param[out] data  data pointer
 * @param[in] len  data len
 */
void ms_hal_ble_get_random(uint8_t *p_data, uint16_t len);

/**
 * @brief User provided;get ble mac address.
 * @param[out] data  data pointer
 * @param[in] len  data len

 * @return void
 */
void ms_hal_ble_get_mac(uint8_t *p_data, uint16_t len);

/**
 * @brief User provided;log printf,like int printf(const char *format, ...);
 * @param[in] format  data poniter
 * @return void
 */
void ms_hal_ble_printf(const char *format, ...);

/**
 * @brief User provided; printf buf
 * @param[in] name buf name
 * @param[in] p_buf  buf pointer
 * @param[in] len  buf len 
 * @return void
 */
void ms_hal_ble_printf_buf(const char *name, unsigned char *p_buf, unsigned short len);

/**
 * @brief User provided;like void *malloc(unsigned int size)
 * @param [in] size  malloc size
 * @return void* poniter
 */
void *ms_hal_ble_malloc(uint32_t size);

/**
 * @brief User provided;like void free(void *ptr)
 * @param[in] ptr  ptr pointer
 * @return void
 */
void ms_hal_ble_free(void *ptr);

/**
 * @brief User provided;like void *memcpy(void *dest, const void *src, size_t n);
 * @param[in] dest  dest pointer
 * @param[in] src  src pointer
 * @param[in] size  copy len
 * @return void* dest pointer
 */
void *ms_hal_ble_memcpy(void *dest, const void *src, uint32_t size);

/**
 * @brief User provided;like void *memset(void *s, int ch, size_t n);
 * @param[in] s  dest pointer
 * @param[in] ch  set data
 * @param[in] n  set data len
 * @return void* dest pointer
 */
void *ms_hal_ble_memset(void *s, int ch, uint32_t n);

/**
 * @brief User provided;like  int memcmp(const void *str1, const void *str2, size_t n))
 * @param[in] str1 str1 data pointer
 * @param[in] str2 str2 data pointer
 * @param[in] n  Number of bytes to be compared.
 * @return void* dest pointer
 */
int ms_hal_ble_memcmp(const void *str1, const void *str2, uint32_t n);

#endif /* _MS_HAL_HW_H__ */

