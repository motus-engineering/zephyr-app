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
#include <zephyr/sys/printk.h>
// SECTION: includes for application code under test
#include "ble_peripheral_hr.h"
// SECTION: private test data

// SECTION: mocks

// SECTION: test suite
FAKE_VALUE_FUNC(int,dummy_bt_hrs_notify, uint16_t);



void *setup(void){

    RESET_FAKE(dummy_bt_hrs_notify);
    return 0;
}

// SECTION: clean up of tests

// SECTION: tests
ZTEST_SUITE(ble_peripheral_hr_unit_tests, NULL, setup, NULL, NULL, NULL);
// SECTION: test suite

ZTEST(ble_peripheral_hr_unit_tests, test_hrs_notify){
    int result;
    dummy_bt_hrs_notify_fake.return_val=0;
    result = hrs_notify();
    zassert_equal(result, 0);
}
/*ZTEST(ble_peripheral_hr_unit_tests, test_hrs_notify_invalid_service){
    int result;
    dummy_bt_hrs_notify_fake.return_val=-22;
    result = hrs_notify();
    zassert_not_equal(result, 0);
}*/
