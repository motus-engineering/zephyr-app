/** @file supervisor.c
 *
 * @brief The is the supervisor Actor.
 *
 * This Actor monitors and manages all the other actors in the application.
 *
 * (c) 2023 Motus Design Group.  All rights reserved.
 */

// SECTION: include statements
#include "supervisor.h"

#include "_supervisor_states.h"
#include "actor.h"
#include "event.h"
#include "hsm.h"

#include <stdbool.h>
#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/smf.h>

LOG_MODULE_REGISTER(supervisor);

#define M_SUPERVISOR_STACK_SIZE (512)
#define M_SUPERVISOR_PRIORITY   (1)

// SECTION: private data types

// SECTION: private constants
#define M_MAX_NUM_MESSAGES 10

// SECTION: private macro definitions

// SECTION: private function prototypes
static void m_send(app_event_t *p_evt_msg);
static void m_supervisor_main_thread(void *, void *, void *);

// SECTION: static data declarations
ACTOR_DEFINE(m_supervisor, NULL, NULL, m_send, M_MAX_NUM_MESSAGES);

/**
 * @brief Define the supervisor thread.
 *
 * This thread is stared automatically.
 *
 */
K_THREAD_DEFINE(supervisor, M_SUPERVISOR_STACK_SIZE, m_supervisor_main_thread,
                NULL, NULL, NULL, M_SUPERVISOR_PRIORITY, K_ESSENTIAL, 0);

/**
 * @brief Create the supervisor state machine.
 *
 */
HSM_DEFINE_STATE_MACHINE(m_supervisor_state);
static const struct smf_state m_supervisor_states[] = {
    [ROOT] = SMF_CREATE_STATE(NULL, supervisor_root_state_run, NULL, NULL),
    [INIT] = SMF_CREATE_STATE(
        supervisor_init_state_entry, supervisor_init_state_run,
        supervisor_init_state_exit, &m_supervisor_states[ROOT]),
    [SUPERVISE] = SMF_CREATE_STATE(
        supervisor_supervise_state_entry, supervisor_supervise_state_run,
        supervisor_supervise_state_exit, &m_supervisor_states[ROOT]),
    [FAULT] = SMF_CREATE_STATE(
        supervisor_fault_state_entry, supervisor_fault_state_run,
        supervisor_fault_state_exit, &m_supervisor_states[ROOT]),
    [PANIC] = SMF_CREATE_STATE(
        supervisor_panic_state_entry, supervisor_panic_state_run,
        supervisor_panic_state_exit, &m_supervisor_states[ROOT])};

// SECTION: public function bodies

// SECTION: private function bodies
/**
 * @brief The callback receiving events that the Actor is subscribed to.
 *
 * @param p_evt_msg pointer to the event to queue
 */
static void m_send(app_event_t *p_evt_msg)
{
    int result = k_msgq_put(&m_supervisor_queue, p_evt_msg, K_NO_WAIT);
    // TODO: handle result
}

/**
 * @brief Changes the state of the state machine.
 *
 * @param next_state state to change to
 */
static void m_set_state(m_supervisor_states_t next_state)
{
    smf_set_state(SMF_CTX(&m_supervisor_state),
                  &m_supervisor_states[next_state]);
}

/**
 * @brief The supervisor Actor thread.
 *
 * Handles the Actor super loop to pop events from the queue and process them.
 *
 */
static void m_supervisor_main_thread(void *, void *, void *)
{
    app_event_subscribe(APP_EVENT_BUTTON_PRESSED, m_send);

    m_supervisor_state.evt_msg.event_name = 0U;
    m_supervisor_state.set_state = m_set_state;
    smf_set_initial(SMF_CTX(&m_supervisor_state), &m_supervisor_states[INIT]);

    while (true)
    {
        int result = k_msgq_get(&m_supervisor_queue,
                                &m_supervisor_state.evt_msg, K_FOREVER);
        // TODO: handle result
        int32_t ret = smf_run_state(SMF_CTX(&m_supervisor_state));
        // TODO: handle ret
    }
}
