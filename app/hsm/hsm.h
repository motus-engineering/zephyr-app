/** @file hsm.h
 *
 * @brief module description
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

#ifndef HSM_H
#define HSM_H

#ifdef __cplusplus
extern "C"
{
#endif //  __cplusplus

// SECTION: include statements
#include <stdbool.h>
#include <stdint.h>

// SECTION: public data types
/**
 * @brief Macro to delcare a hierarchical state machine.
 * 
 * @param _name name of the state machine
 * @param _state_enum_type enum of the possible states
 * 
 */
#define HSM_DECLARE_STATE_MACHINE(_name, _state_enum_type)                     \
    typedef struct                                                             \
    {                                                                          \
        struct smf_ctx ctx;                                                    \
        app_event_t    evt_msg;                                                \
        void (*set_state)(_state_enum_type next_state);                        \
    } _name##_t

/**
 * @brief Convenience macro to declare the state machine api functions.
 * 
 */
#define HSM_DECLARE_STATE_FUNCTIONS(_name)                                     \
    void _name##_state_entry(void *evt);                                       \
    void _name##_state_run(void *evt);                                         \
    void _name##_state_exit(void *evt);

// SECTION: public constants

// SECTION: public macro definitions
/**
 * @brief Macro to define a new state machine.
 * 
 * @param _name name of the state machine to define
 * 
 */
#define HSM_DEFINE_STATE_MACHINE(_name) static _name##_t _name

// SECTION: public function prototypes

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // HSM_H
