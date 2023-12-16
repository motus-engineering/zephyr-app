/** @file test_ble_peripheral_hr.c
 *
 * @brief Unit tests for the ble_peripheral_hr driver
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

// SECTION: general includes

// SECTION: test framework includes
#include <stdlib.h>
#include <zephyr/fff.h>
#include <zephyr/ztest.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/sys/printk.h>
// SECTION: includes for application code under test
#include "ble_concurrent_roles.h"

// SECTION: private test data

// SECTION: mocks

// SECTION: test suite
FAKE_VALUE_FUNC(int,dummy_bt_enable,	bt_ready_cb_t);
FAKE_VALUE_FUNC(int,dummy_bt_le_adv_start,const struct bt_le_adv_param *, const struct bt_data *, 
    size_t,const struct bt_data *, size_t);
//FAKE_VALUE_FUNC(int,dummy_bt_le_scan_start,const struct bt_le_scan_param *, bt_le_scan_cb_t);


void *Multi_setup(void){

    RESET_FAKE(dummy_bt_enable);
    RESET_FAKE(dummy_bt_le_adv_start);
   // RESET_FAKE(dummy_bt_le_scan_start);
    return 0;
}

// SECTION: clean up of tests

// SECTION: tests
ZTEST_SUITE(ble_concurrent_roles_unit_tests, NULL, Multi_setup, NULL, NULL, NULL);
// SECTION: test suite

ZTEST(ble_concurrent_roles_unit_tests, test_ble_init){
    int result;
    dummy_bt_enable_fake.return_val=0;
    result = ble_init();
    zassert_equal(result, 0);
}
ZTEST(ble_concurrent_roles_unit_tests, test_ble_adv_no_dev){
    int result;
    //when there is no device 
    dummy_bt_enable_fake.return_val=-6;
    result = ble_init();
    printk("result: %d",result);
    zassert_not_equal(result, 0);
}
/*ZTEST(ble_concurrent_roles_unit_tests, test_ble_concurrent_start){
    int result;
    
    dummy_bt_le_scan_start_fake.return_val=0;
    dummy_bt_le_adv_start_fake.return_val=0;
    result = ble_concurrent_start();
    zassert_equal(result, 0);
}*/
