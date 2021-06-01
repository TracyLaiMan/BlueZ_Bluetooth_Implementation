/**
 * @file ms_hal_timer.h
 * @brief ms hal system timer init
 * @author
 * @version 1.0.0
 * @date 2021-04-22
 * @par Copyright  (c)
 * 		Midea
 */
#ifndef _MS_HAL_TIMER_H__
#define _MS_HAL_TIMER_H__

#include "ms_hal.h"

typedef void (*ms_hal_timer_isr_callback_t)(void);

/**
 * @brief system timer init
 * @param p_time: period of system timer
 * @param cb: callback of system timer timeout
 * @param p_repeat: timer repeat or not
 * @return void
 */
uint8_t ms_hal_timer_init(uint32_t p_time, ms_hal_timer_isr_callback_t cb, BOOL p_repeat);


#endif /* _MS_HAL_TIMER_H__ */