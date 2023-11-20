/** @file init_state.c
*
* @brief module description
*
* (c) 2023 Motus Design Group.  All rights reserved.
*/

// SECTION: include statements
#include <stdint.h>
#include <stdbool.h>

#include "led.h"
#include "button.h"
#include "_supervisor_states.h"

// SECTION: private data types

// SECTION: private constants

// SECTION: private macro definitions

// SECTION: static data declarations

// SECTION: private function prototypes

// SECTION: public function bodies
void supervisor_init_state_run(void *evt)
{
}

void supervisor_init_state_entry(void *evt)
{
    // TODO: setup platform and other actors
    app_led_init();
    app_button_init();

    ((m_supervisor_state_t*)evt)->set_state(SUPERVISE);
}

void supervisor_init_state_exit(void *evt)
{

}

// SECTION: private function bodies
