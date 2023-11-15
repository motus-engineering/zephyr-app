/** @file supervisor.c
*
* @brief module description
*
* (c) 2023 Motus Design Group.  All rights reserved.
*/

// SECTION: include statements
#include <stdint.h>
#include <stdbool.h>

#include "supervisor.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(supervisor);

#define M_SUPERVISOR_STACK_SIZE (512)
#define M_SUPERVISOR_PRIORITY   (1)

// SECTION: private data types

// SECTION: private constants

// SECTION: private macro definitions

// SECTION: static data declarations

// SECTION: private function prototypes
static void m_supervisor_main_thread(void *, void *, void *);
K_THREAD_DEFINE(state_machine_thread,
                M_SUPERVISOR_STACK_SIZE,
                m_supervisor_main_thread,
                NULL,
                NULL,
                NULL,
                M_SUPERVISOR_PRIORITY,
                K_ESSENTIAL,
                K_TICKS_FOREVER);


// SECTION: public function bodies
void supervisor_init(void)
{

}

void supervisor_start(void)
{
    // Start threads
    k_thread_start(state_machine_thread);
}
// SECTION: private function bodies

static void m_supervisor_main_thread(void *, void *, void *)
{
    while(true)
    {
        k_msleep(1000);
    }
}
