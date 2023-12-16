/** @file ble_peripheral_hr.h
 *
 * @brief module description
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

#ifndef BLE_PERIPHERAL_HR_H
#define BLE_PERIPHERAL_HR_H

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
 * @brief Called to initialize ble connection.
 *
 * 
 */
int ble_adv(void);
/**
 * @brief Called to advertise hr data.
 *
 * 
 */
int hrs_notify(void);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // BLE_PERIPHERAL_HR_H