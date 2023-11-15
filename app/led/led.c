/** @file led.c
 *
 * @brief module description
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

// SECTION: include statements
#include "led.h"

#include <stdbool.h>
#include <stdint.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

// SECTION: private data types

// SECTION: private constants
#define LED0_NODE DT_ALIAS(led0)

// SECTION: private macro definitions

// SECTION: static data declarations
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

// SECTION: private function prototypes

// SECTION: public function bodies

// SECTION: private function bodies
bool app_led_init(void)
{
    if (!gpio_is_ready_dt(&led))
    {
        return false;
    }
    int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
    {
        return false;
    }

    return true;
}

bool app_led_toggle(void)
{
    int ret = gpio_pin_toggle_dt(&led);
    if (ret < 0)
    {
        return false;
    }

    return true;
}