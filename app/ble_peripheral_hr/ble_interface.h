/** @file ble_interface.h
* 
* @brief Compiler barrier for SPI device interfaces
*
* (c) 2023 Motus Design Group.  All rights reserved.
*/ 

#ifndef BLE_INTERFACE_H
#define BLE_INTERFACE_H

#ifdef __cplusplus
extern "C"
{
#endif //  __cplusplus

// SECTION: include statements
#include <stdint.h>
#include <stdbool.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/services/hrs.h>
// SECTION: public data types

// SECTION: public constants

// SECTION: public function prototypes
/**
 * @brief Placeholder for unit testing mock. Replaces bt_enable() when BLE driver not configured. 
*/
int dummy_bt_enable(bt_ready_cb_t cb);

/**
 * @brief Placeholder for unit testing mock. Replaces bt_le_adv_start() when BLE driver not configured. 
*/
int dummy_bt_le_adv_start(const struct bt_le_adv_param *param,
		    const struct bt_data *ad, size_t ad_len,
		    const struct bt_data *sd, size_t sd_len);
/**
 * @brief Placeholder for unit testing mock. Replaces bt_hrs_notify() when BLE driver not configured. 
*/
int dummy_bt_hrs_notify(uint16_t heartrate);
// SECTION: public macro definitions
/*
* These functions are defined in zephyr/blutooth, preventing them from being mocked for unit testing.
* Remove them from the build when BLE driver not configured.
*/
#if CONFIG_BT //Wrappers for BLE functions...
#define BT_ENABLE(w) bt_enable(w)
#define BT_LE_ADV_START(w,x,y,z,t) bt_le_adv_start(w,x,y,z,t)   
#else //Placeholders for mock SPI functions...
#define BT_ENABLE(w) dummy_bt_enable(w)
#define BT_LE_ADV_START(w,x,y,z,t) dummy_bt_le_adv_start(w,x,y,z,t)  
#endif
#if CONFIG_BT_HRS
#define BT_HRS_NOTIFY(x) bt_hrs_notify(x);
#else
#define BT_HRS_NOTIFY(x) dummy_bt_hrs_notify(x)
#endif

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // BLE_INTERFACE_H