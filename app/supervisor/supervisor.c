/** @file supervisor.c
 *
 * @brief module description
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

// SECTION: include statements
#include "supervisor.h"

#include "actor.h"
#include "event.h"

#include <stdbool.h>
#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(supervisor);

#define M_SUPERVISOR_STACK_SIZE (512)
#define M_SUPERVISOR_PRIORITY   (1)

// SECTION: private data types

// SECTION: private constants
#define M_MAX_NUM_MESSAGES 10

// SECTION: private macro definitions

// SECTION: private function prototypes
static void m_init(void);
static void m_run(void);
static void m_post(app_event_t *p_evt_msg);
static void m_supervisor_main_thread(void *, void *, void *);

// SECTION: static data declarations
ACTOR_DEFINE(m_supervisor, m_init, m_run, m_post, app_event_t,
             M_MAX_NUM_MESSAGES);

K_THREAD_DEFINE(supervisor, M_SUPERVISOR_STACK_SIZE, m_supervisor_main_thread,
                NULL, NULL, NULL, M_SUPERVISOR_PRIORITY, K_ESSENTIAL, 0);

// SECTION: public function bodies

// SECTION: private function bodies
void m_init(void)
{
}

void m_run(void)
{
}

static void m_post(app_event_t *p_evt_msg)
{
    int result = k_msgq_put(&m_supervisor_queue, p_evt_msg, K_NO_WAIT);
    // TODO: handle result
}

static void m_supervisor_main_thread(void *, void *, void *)
{
    while (true)
    {
        app_event_t evt_msg = {0};
        int result = k_msgq_get(&m_supervisor_queue, &evt_msg, K_FOREVER);
        // TODO: handle result

        switch (evt_msg.event_name)
        {
            case 0:
                break;
            default:
                break;
        }
    }
}
