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

/**
 * @brief Structure for an Actor object
 *
 */
typedef struct
{
    uint32_t handle;
    void (*fp_init)(void);
    void (*fp_run)(void);
    app_event_send_t fp_send;
} actor_t;

// SECTION: public constants

// SECTION: public macro definitions
/**
 * @brief Macro to statically define an Actor.
 * 
 * @param _name name of the Actor
 * @param _fp_init function pointer to initialize the Actor
 * @param _fp_run funtion pointer to process a new event
 * @param _fp_send funtion pointer to send an event to the Actor queue
 * @param _max_msgs queue depth of the Actor
 * 
 */
#define ACTOR_DEFINE(_name, _fp_init, _fp_run, _fp_send, _max_msgs)     \
    actor_t _name##_actor = {                                                  \
        .handle = 0,                                                           \
        .fp_init = _fp_init,                                                   \
        .fp_run = _fp_run,                                                     \
        .fp_send = _fp_send,                                                   \
    };                                                                         \
    K_MSGQ_DEFINE(_name##_queue, sizeof(app_event_t), _max_msgs, 1)

// SECTION: public function prototypes

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // ACTOR_H
