/** @file test_supervisor.c
*
* @brief Unit tests for the supervisor module
*
* (c) 2023 Motus Design Group.  All rights reserved.
*/

// SECTION: general includes

// SECTION: test framework includes
#include <stdlib.h>
#include <zephyr/fff.h>
#include <zephyr/ztest.h>

// SECTION: includes for application code under test
#include "supervisor.h"

// SECTION: private test data

// SECTION: mocks

// SECTION: test suite
struct my_suite_fixture {
     size_t max_size;
     size_t size;
     uint8_t buff[1];
};

void* setup(void)
{
    // Allocate the fixture with 256 byte buffer
    struct my_suite_fixture *fixture = malloc(sizeof(struct my_suite_fixture) + 255);

    zassume_not_null(fixture, NULL);
    fixture->max_size = 256;

    return fixture;
}

void before(void *p_fixture)
{
    p_fixture = p_fixture;
}

void after(void *p_fixture)
{
    p_fixture = p_fixture;
}

void teardown(void *p_fixture)
{
    free(p_fixture);
}

ZTEST_SUITE(supervisor_unit_tests, NULL, setup, before, after, teardown);

// SECTION: tests
ZTEST(supervisor_unit_tests, test_place_holder)
{
    zassert_equal(0, 0);
}
