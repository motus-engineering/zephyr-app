// TODO start other actors
/** @file button.c
 *
 * @brief module description
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

// SECTION: include statements
#include "button.h"

#include "event.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

// SECTION: private data types

// SECTION: private constants
#define SW0_NODE DT_ALIAS(sw0)
#if !DT_NODE_HAS_STATUS(SW0_NODE, okay)
#error "Unsupported board: sw0 devicetree alias is not defined"
#endif

// SECTION: private macro definitions

// SECTION: static data declarations
static const struct gpio_dt_spec button =
    GPIO_DT_SPEC_GET_OR(SW0_NODE, gpios, {0});
static struct gpio_callback button_cb_data;

// SECTION: private function prototypes
static void button_pressed(const struct device *dev, struct gpio_callback *cb,
                           uint32_t pins);

// SECTION: public function bodies
bool app_button_init(void)
{
    int ret;

    if (!gpio_is_ready_dt(&button))
    {
        printk("Error: button device %s is not ready\n", button.port->name);
        return false;
    }

    ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
    if (ret != 0)
    {
        printk("Error %d: failed to configure %s pin %d\n", ret,
               button.port->name, button.pin);
        return false;
    }

    ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
    if (ret != 0)
    {
        printk("Error %d: failed to configure interrupt on %s pin %d\n", ret,
               button.port->name, button.pin);
        return false;
    }

    gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
    gpio_add_callback(button.port, &button_cb_data);
    printk("Set up button at %s pin %d\n", button.port->name, button.pin);

    return true;
}

// SECTION: private function bodies
/**
 * @brief Callback that publishes the @ref APP_EVENT_BUTTON_PRESSED event.
 * 
 * @param dev unused
 * @param cb unused
 * @param pins unused
 */
static void button_pressed(const struct device *dev, struct gpio_callback *cb,
                           uint32_t pins)
{
    printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
    app_event_publish(&(app_event_t) {.event_name = APP_EVENT_BUTTON_PRESSED});
}
