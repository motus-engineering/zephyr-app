/** @file _states.h
 *
 * @brief module description
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

#ifndef _STATES_H
#define _STATES_H

#ifdef __cplusplus
extern "C"
{
#endif //  __cplusplus

// SECTION: include statements
#include "event.h"
#include "hsm.h"

#include <stdbool.h>
#include <stdint.h>
#include <zephyr/smf.h>

// SECTION: public data types
typedef enum
{
    ROOT,
    INIT,
    SUPERVISE,
    FAULT,
    PANIC
} m_supervisor_states_t;

HSM_DECLARE_STATE_MACHINE(m_supervisor_state, m_supervisor_states_t);

// SECTION: public constants

// SECTION: public macro definitions

// SECTION: public function prototypes
HSM_DECLARE_STATE_FUNCTIONS(supervisor_root);
HSM_DECLARE_STATE_FUNCTIONS(supervisor_init);
HSM_DECLARE_STATE_FUNCTIONS(supervisor_supervise);
HSM_DECLARE_STATE_FUNCTIONS(supervisor_fault);
HSM_DECLARE_STATE_FUNCTIONS(supervisor_panic);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // _STATES_H
