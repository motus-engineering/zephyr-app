/** @file actor.h
 *
 * @brief module description
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

#ifndef ACTOR_H
#define ACTOR_H

#ifdef __cplusplus
extern "C"
{
#endif //  __cplusplus

// SECTION: include statements
#include "event.h"

#include <stdbool.h>
#include <stdint.h>

// SECTION: public data types
typedef struct
{
    uint32_t handle;
    void (*fp_init)(void);
    void (*fp_run)(void);
    app_event_send_t fp_send;
} actor_t;

// SECTION: public constants

// SECTION: public macro definitions
#define ACTOR_DEFINE(_name, _fp_init, _fp_run, _fp_send, _type, _max_msgs)     \
    actor_t _name##_actor = {                                                  \
        .handle = 0,                                                           \
        .fp_init = _fp_init,                                                   \
        .fp_run = _fp_run,                                                     \
        .fp_send = _fp_send,                                                   \
    };                                                                         \
    K_MSGQ_DEFINE(_name##_queue, sizeof(_type), _max_msgs, 1)

// SECTION: public function prototypes

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // ACTOR_H
