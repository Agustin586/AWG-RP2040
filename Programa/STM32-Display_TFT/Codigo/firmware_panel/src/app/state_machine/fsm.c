/**
 * @file    fsm.c
 * @brief   Máquina de estados del panel frontal
 * @author  Agustin M. Zuliani
 * @date    27/03/26
 * @copyright   Agustin M. Zuliani
 */

/*=================================[ includes ]=================================*/

#include "fsm.h"
#include "fsm_actions.h"
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <string.h>

/*============================[ macros and typedef ]============================*/

LOG_MODULE_REGISTER(fsm, LOG_LEVEL_DBG);

/*============================[ private declarations ]==========================*/

static fsm_t s_fsm = {0};

static const fsm_state_def_t states[EST_COUNT] = {

    /* Estados para FSM_MAIN */
    [EST_RESET] = {
        .on_entry    = entry_reset,
        .on_exit     = NULL,
        .transitions = {
            [EVENT_INPUT] = { action_reset, EST_INIT_PRESET },
        },
    },

    [EST_INIT_PRESET] = {
        .on_entry    = entry_init_preset,
        .on_exit     = NULL,
        .transitions = {
            [EVENT_INPUT] = { action_init_preset, EST_IDLE },
        },
    },

    [EST_IDLE] = {
        .on_entry    = entry_idle,
        .on_exit     = exit_idle,
        .transitions = {
            [EVENT_BTN_FREQ] = { NULL               , EST_SET_FREQ },
            [EVENT_BTN_AMPL] = { NULL               , EST_SET_AMPL },
            [EVENT_BTN_OFFS] = { NULL               , EST_SET_OFFS },
            [EVENT_BTN_DUTY] = { NULL               , EST_SET_DUTY },
            [EVENT_BTN_PHAS] = { NULL               , EST_SET_PHAS },
            [EVENT_BTN_WAVE] = { NULL               , EST_SET_WAVE },
            [EVENT_BTN_CH1]  = { action_select_ch1  , EST_IDLE     },
            [EVENT_BTN_CH2]  = { action_select_ch2  , EST_IDLE     },
        },
    },

    /* Estados para FSM_SIGNAL_EDITINTG */
    [EST_SET_FREQ] = {
        .on_entry    = entry_set_freq,
        .on_exit     = exit_signal,
        .transitions = {
            [EVENT_ENCODER_CW]  = { action_st_freq_increment, EST_SET_FREQ },
            [EVENT_ENCODER_CCW] = { action_st_freq_decrement, EST_SET_FREQ },
            [EVENT_BTN_LEFT]    = { action_cursor_left      , EST_SET_FREQ },
            [EVENT_BTN_RIGHT]   = { action_cursor_right     , EST_SET_FREQ },
            [EVENT_BTN_CH1]     = { action_select_ch1       , EST_SET_FREQ },
            [EVENT_BTN_CH2]     = { action_select_ch2       , EST_SET_FREQ },
            [EVENT_BTN_OK]      = { action_send_ipc         , EST_IDLE     },
            [EVENT_BTN_BACK]    = { action_cancel           , EST_IDLE     },
            [EVENT_IPC_ACK_OK]  = { action_apply            , EST_SET_FREQ },
            [EVENT_IPC_ACK_ERR] = { action_show_error       , EST_SET_FREQ },
        },
    },

    [EST_SET_AMPL] = {
        .on_entry    = entry_set_ampl,
        .on_exit     = exit_signal,
        .transitions = {
            [EVENT_ENCODER_CW]  = { action_st_ampl_increment, EST_SET_AMPL },
            [EVENT_ENCODER_CCW] = { action_st_ampl_decrement, EST_SET_AMPL },
            [EVENT_BTN_LEFT]    = { action_cursor_left      , EST_SET_AMPL },
            [EVENT_BTN_RIGHT]   = { action_cursor_right     , EST_SET_AMPL },
            [EVENT_BTN_CH1]     = { action_select_ch1       , EST_SET_AMPL },
            [EVENT_BTN_CH2]     = { action_select_ch2       , EST_SET_AMPL },
            [EVENT_BTN_OK]      = { action_send_ipc         , EST_IDLE     },
            [EVENT_BTN_BACK]    = { action_cancel           , EST_IDLE     },
            [EVENT_IPC_ACK_OK]  = { action_apply            , EST_SET_AMPL },
            [EVENT_IPC_ACK_ERR] = { action_show_error       , EST_SET_AMPL },
        },
    },

    [EST_SET_OFFS] = {
        .on_entry    = entry_set_offs,
        .on_exit     = exit_signal,
        .transitions = {
            [EVENT_ENCODER_CW]  = { action_st_offs_increment, EST_SET_OFFS },
            [EVENT_ENCODER_CCW] = { action_st_offs_decrement, EST_SET_OFFS },
            [EVENT_BTN_LEFT]    = { action_cursor_left,       EST_SET_OFFS },
            [EVENT_BTN_RIGHT]   = { action_cursor_right,      EST_SET_OFFS },
            [EVENT_BTN_CH1]     = { action_select_ch1,        EST_SET_OFFS },
            [EVENT_BTN_CH2]     = { action_select_ch2,        EST_SET_OFFS },
            [EVENT_BTN_OK]      = { action_send_ipc,          EST_IDLE     },
            [EVENT_BTN_BACK]    = { action_cancel,            EST_IDLE     },
            [EVENT_IPC_ACK_OK]  = { action_apply,             EST_SET_OFFS },
            [EVENT_IPC_ACK_ERR] = { action_show_error,        EST_SET_OFFS },
        },
    },

    [EST_SET_DUTY] = {
        .on_entry    = entry_set_duty,
        .on_exit     = exit_signal,
        .transitions = {
            [EVENT_ENCODER_CW]  = { action_st_duty_increment, EST_SET_DUTY },
            [EVENT_ENCODER_CCW] = { action_st_duty_decrement, EST_SET_DUTY },
            [EVENT_BTN_LEFT]    = { action_cursor_left,       EST_SET_DUTY },
            [EVENT_BTN_RIGHT]   = { action_cursor_right,      EST_SET_DUTY },
            [EVENT_BTN_CH1]     = { action_select_ch1,        EST_SET_DUTY },
            [EVENT_BTN_CH2]     = { action_select_ch2,        EST_SET_DUTY },
            [EVENT_BTN_OK]      = { action_send_ipc,          EST_IDLE     },
            [EVENT_BTN_BACK]    = { action_cancel,            EST_IDLE     },
            [EVENT_IPC_ACK_OK]  = { action_apply,             EST_SET_DUTY },
            [EVENT_IPC_ACK_ERR] = { action_show_error,        EST_SET_DUTY },
        },
    },

    [EST_SET_PHAS] = {
        .on_entry    = entry_set_phas,
        .on_exit     = exit_signal,
        .transitions = {
            [EVENT_ENCODER_CW]  = { action_st_phas_increment, EST_SET_PHAS },
            [EVENT_ENCODER_CCW] = { action_st_phas_decrement, EST_SET_PHAS },
            [EVENT_BTN_LEFT]    = { action_cursor_left,       EST_SET_PHAS },
            [EVENT_BTN_RIGHT]   = { action_cursor_right,      EST_SET_PHAS },
            [EVENT_BTN_CH1]     = { action_select_ch1,        EST_SET_PHAS },
            [EVENT_BTN_CH2]     = { action_select_ch2,        EST_SET_PHAS },
            [EVENT_BTN_OK]      = { action_send_ipc,          EST_IDLE     },
            [EVENT_BTN_BACK]    = { action_cancel,            EST_IDLE     },
            [EVENT_IPC_ACK_OK]  = { action_apply,             EST_SET_PHAS },
            [EVENT_IPC_ACK_ERR] = { action_show_error,        EST_SET_PHAS },
        },
    },

    [EST_SET_WAVE] = {
        .on_entry    = entry_set_wave,
        .on_exit     = exit_signal,
        .transitions = {
            [EVENT_ENCODER_CW]  = { action_st_wave_increment, EST_SET_WAVE },
            [EVENT_ENCODER_CCW] = { action_st_wave_decrement, EST_SET_WAVE },
            [EVENT_BTN_CH1]     = { action_select_ch1,        EST_SET_WAVE },
            [EVENT_BTN_CH2]     = { action_select_ch2,        EST_SET_WAVE },
            [EVENT_BTN_OK]      = { action_send_ipc,          EST_IDLE     },
            [EVENT_BTN_BACK]    = { action_cancel,            EST_IDLE     },
            [EVENT_IPC_ACK_OK]  = { action_apply,             EST_SET_WAVE },
            [EVENT_IPC_ACK_ERR] = { action_show_error,        EST_SET_WAVE },
        },
    },
};

/*=============================[ private functions ]===========================*/

static void fsm_do_transition(fsm_state_t next)
{
    if (next == s_fsm.current)  {return;}
    
    /* Ejecuta funcion on exit */
    if (states[s_fsm.current].on_exit != NULL)
    {
        states[s_fsm.current].on_exit();
    }

    LOG_DBG("FSM: %d --> %d", s_fsm.current, next);
    s_fsm.current = next;

    /* Ejecuta funcion on entry*/
    if (states[s_fsm.current].on_entry != NULL)
    {
        states[s_fsm.current].on_entry();
    }

    return;
}

/*=============================[ public functions ]============================*/

void fsm_init(void)
{
    memset(&s_fsm, 0, sizeof(s_fsm));

    s_fsm.current           = EST_RESET;
    s_fsm.history_main      = EST_IDLE;
    s_fsm.history_signal    = EST_SET_FREQ;
    s_fsm.active_ch         = AWG_CH1;
    s_fsm.cursor_pos        = 0;
    
    if (states[EST_RESET].on_entry != NULL)
    {
        states[EST_RESET].on_entry();
    }

    return;
}

void fsm_dispatch(const fsm_event_msg_t *msg)
{
    // LOG_DBG("dispatch: estado=%d evento=%d", s_fsm.current, msg->id);

    const fsm_transition_t *t = &states[s_fsm.current].transitions[msg->id];

    /* Proteccion frente a eventos no contemplados */
    if (t->action == NULL && t->next_state == 0)
    {
        return;
    }

    /* Accion de transicion */
    if (t->action != NULL)
    {
        t->action(msg);
    }

    /* Ejecuta transicion */
    fsm_do_transition(t->next_state);

    return;
}

fsm_t *fsm_get(void)
{
    return &s_fsm;
}
