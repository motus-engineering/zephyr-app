/** @file event.h
* 
* @brief module description
*
* (c) 2023 Motus Design Group.  All rights reserved.
*/ 

#ifndef EVENT_H
#define EVENT_H

#ifdef __cplusplus
extern "C"
{
#endif //  __cplusplus

// SECTION: include statements
#include <stdint.h>
#include <stdbool.h>

// SECTION: public data types
typedef struct
{
    uint32_t event_name;
} app_event_t;

// SECTION: public constants

// SECTION: public macro definitions

// SECTION: public function prototypes

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // EVENT_H