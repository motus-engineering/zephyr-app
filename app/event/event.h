/** @file event.h
 *
 * @brief module description
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

#ifndef EVENT_H
#define EVENT_H

#ifdef __cplusplus
extern "C"
{
#endif //  __cplusplus

// SECTION: include statements
#include <stdbool.h>
#include <stdint.h>
#include <zephyr/sys/iterable_sections.h>

// SECTION: public data types
/**
 * @brief List of possible event for the whole application
 *
 * @note This enum contains all possible events and thus is global in nature.
 *
 */
typedef enum
{
    APP_EVENT_BUTTON_PRESSED,
    APP_EVENT_NUM
} app_event_events_t;

/**
 * @brief Event object structure used when publishing and event.
 *
 */
typedef struct
{
    app_event_events_t event_name;
} app_event_t;

/**
 * @brief Signature for publishing an event.
 *
 */
typedef void (*app_event_send_t)(app_event_t *); // Must be re-entrant function

// SECTION: public constants

// SECTION: public macro definitions

// SECTION: public function prototypes
/**
 * @brief
 *
 * @param event the event to subscribe to
 * @param send  the function to call when dispatching the event
 */
void app_event_subscribe(app_event_events_t event, app_event_send_t send);

/**
 * @brief Called to publish and event to subscribers.
 *
 * @param p_event pointer to an event object
 */
void app_event_publish(app_event_t *p_event);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // EVENT_H
