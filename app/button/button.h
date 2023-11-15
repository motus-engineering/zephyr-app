/** @file button.h
 *
 * @brief module description
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

#ifndef BUTTON_H
#define BUTTON_H

#ifdef __cplusplus
extern "C"
{
#endif //  __cplusplus

// SECTION: include statements
#include <stdbool.h>
#include <stdint.h>

// SECTION: public data types

// SECTION: public constants

// SECTION: public macro definitions

// SECTION: public function prototypes
/**
 * @brief  Initialzation of the button.
 *
 * Must be called prior to using the button.
 *
 * @return true
 * @return false
 */
bool app_button_init(void);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // BUTTON_H
