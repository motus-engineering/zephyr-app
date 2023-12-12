/** @file ble_hr.h
 *
 * @brief module description
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

#ifndef BLE_HR_H
#define BLE_HR_H

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
void ble_adv(void);
void hrs_notify(void);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // BLE_HR_H