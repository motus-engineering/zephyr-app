/** @file supervisor.h
* 
* @brief module description
*
* (c) 2023 Motus Design Group.  All rights reserved.
*/ 

#ifndef SUPERVISOR_H
#define SUPERVISOR_H

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
void supervisor_init(void);
void supervisor_start(void);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // SUPERVISOR_H