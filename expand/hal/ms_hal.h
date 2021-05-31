/*
 * Copyright (c) 2019 - 2021 IoT of Midea Group.
 *
 * File Name 	    : 
 * Description	    : HAL adaptor
 *
 * Version	        : v0.2
 * Author			: 
 * Date	            : 2021/04/20
 * History	        : 
 */

#ifndef __MS_HAL_H__
#define __MS_HAL_H__

#ifdef __cplusplus
extern "C" {
#endif

/*************************  typedef  **********************************/
#ifdef __GNUC__ 
#include <stdint.h>
#else
typedef signed char int8_t;          //!<typedef int8_t
typedef unsigned char uint8_t;       //!<typedef uint8_t
typedef signed short int16_t;        //!<typedef int16_t
typedef unsigned short uint16_t;     //!<typedef uint16_t
typedef signed long int32_t;         //!<typedef int32_t
typedef unsigned long uint32_t;      //!<typedef uint32_t
typedef signed long long int64_t;      //!<typedef int64
typedef unsigned long long uint64_t;   //!<typedef uint64
#endif
typedef enum
{
    MS_HAL_RESULT_ERROR              = 0x00,
	MS_HAL_RESULT_SUCCESS             = 0x01,
	MS_HAL_RESULT_FLASH_ITEM_EMPTY   = 0x02,
}ms_hal_result_t;

#ifndef NULL
#define NULL ((void *)0) //!<defince NULL
#endif

#ifndef BOOL
#undef FALSE
#undef TRUE
	typedef enum { FALSE = 0, TRUE } BOOL;
#endif

#ifdef __cplusplus
}
#endif

#endif

