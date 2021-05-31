
/**
 * @file ms_hal_watchdog.h
 * @brief ms hal watch dog header file
 * @author
 * @version 1.0.0
 * @date 2020-05-16
 * @par Copyright  (c)
 * 		Midea
 */
#ifndef _MS_HAL_BLE_WATCHDOG_H__
#define _MS_HAL_BLE_WATCHDOG_H__

#include "ms_hal.h"

/**
 * @brief watch dog init
 * @param p_timeout_ms: watch dog timeout value
 * @return void
 */
void ms_hal_ble_watch_dog_init(uint32_t p_timeout_ms);

/**
 * @brief watch dog stop
 * @param void
 * @return void
 */
void ms_hal_ble_watchdog_stop(void);

/**
 * @brief watch dog feed
 * @param void
 * @return void
 */
void ms_hal_ble_watch_dog_feed(void);

#endif /* _MS_HAL_BLE_WATCHDOG_H__ */

