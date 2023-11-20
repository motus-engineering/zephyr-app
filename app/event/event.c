/** @file event.c
 *
 * @brief module description
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

// SECTION: include statements
#include "event.h"

#include <stdbool.h>
#include <stdint.h>
#include <zephyr/sys/iterable_sections.h>

#define M_MAX_NUM_REGISTERED_SENDERS (5)

// SECTION: private data types
typedef struct
{
    app_event_send_t fp_senders[M_MAX_NUM_REGISTERED_SENDERS];
    uint32_t         num_sensders;
} m_senders_t;

// SECTION: private constants

// SECTION: private macro definitions

// SECTION: static data declarations

// SECTION: private function prototypes
static m_senders_t m_senders[APP_EVENT_NUM] = {0};

// SECTION: public function bodies

// TODO use sections for compile time registration
void app_event_register(app_event_events_t event, app_event_send_t send)
{
    __ASSERT(m_senders[event].num_sensders < M_MAX_NUM_REGISTERED_SENDERS,
             "Max number of registered events exceeded.");
    m_senders[event].fp_senders[m_senders[event].num_sensders] = send;
    m_senders[event].num_sensders++;
}

void app_event_publish(app_event_t *p_event)
{
    for (uint32_t sender_idx = 0;
         sender_idx < m_senders[p_event->event_name].num_sensders; sender_idx++)
    {
        m_senders[p_event->event_name].fp_senders[sender_idx](p_event);
    }
}

// SECTION: private function bodies
