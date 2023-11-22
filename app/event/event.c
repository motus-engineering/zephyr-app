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
/**
 * @brief structure for registering subscribers to an event
 *
 */
typedef struct
{
    app_event_send_t fp_senders[M_MAX_NUM_REGISTERED_SENDERS];
    uint32_t         num_subscribers;
} m_subscribers_t;

// SECTION: private constants

// SECTION: private macro definitions

// SECTION: static data declarations

// SECTION: private function prototypes
/**
 * @brief Map of events to subscribers.
 *
 */
static m_subscribers_t m_subscribers[APP_EVENT_NUM] = {0};

// SECTION: public function bodies
void app_event_subscribe(app_event_events_t event, app_event_send_t send)
{
    __ASSERT(m_subscribers[event].num_subscribers <
                 M_MAX_NUM_REGISTERED_SENDERS,
             "Max number of registered events exceeded.");
    m_subscribers[event].fp_senders[m_subscribers[event].num_subscribers] =
        send;
    m_subscribers[event].num_subscribers++;
}

void app_event_publish(app_event_t *p_event)
{
    for (uint32_t sender_idx = 0;
         sender_idx < m_subscribers[p_event->event_name].num_subscribers;
         sender_idx++)
    {
        m_subscribers[p_event->event_name].fp_senders[sender_idx](p_event);
    }
}

// SECTION: private function bodies
