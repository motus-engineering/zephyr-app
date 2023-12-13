/** @file ble_concurrent_roles.h
 *
 * @brief module description
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

#ifndef BLE_CONCURRENT_ROLES_H
#define BLE_CONCURRENT_ROLES_H

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
int ble_init(void);
/**
 * @brief Called to start central and peripheral role aat the same time.
 *
 * 
 */
void ble_concurrent_start(void);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // BLE_PERIPHERAL_HR_H