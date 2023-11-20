/** @file led.h
* 
* @brief module description
*
* (c) 2023 Motus Design Group.  All rights reserved.
*/ 

#ifndef LED_H
#define LED_H

#ifdef __cplusplus
extern "C"
{
#endif //  __cplusplus

// SECTION: include statements
#include <stdint.h>
#include <stdbool.h>

// SECTION: public data types

// SECTION: public constants

// SECTION: public macro definitions

// SECTION: public function prototypes
bool app_led_init(void);
bool app_led_toggle(void);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // LED_H
