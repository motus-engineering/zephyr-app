/** @file supervise_state.c
 *
 * @brief module description
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

// SECTION: include statements
#include "led.h"

#include <stdbool.h>
#include <stdint.h>

// SECTION: private data types

// SECTION: private constants

// SECTION: private macro definitions

// SECTION: static data declarations

// SECTION: private function prototypes

// SECTION: public function bodies
void supervisor_supervise_state_run(void *evt)
{
    app_led_toggle();
}

void supervisor_supervise_state_entry(void *evt)
{
    // TODO start other actors
}

void supervisor_supervise_state_exit(void *evt)
{
}

// SECTION: private function bodies
