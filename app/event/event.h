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
typedef enum
{
    APP_EVENT_BUTTON_PRESSED,
    APP_EVENT_NUM
} app_event_events_t;

typedef struct
{
    app_event_events_t event_name;
} app_event_t;

typedef void (*app_event_send_t)(app_event_t *); // Must be re-entrant function

// SECTION: public constants

// SECTION: public macro definitions

// SECTION: public function prototypes
void app_event_register(app_event_events_t, app_event_send_t send);

void app_event_publish(app_event_t *p_event);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // EVENT_H
