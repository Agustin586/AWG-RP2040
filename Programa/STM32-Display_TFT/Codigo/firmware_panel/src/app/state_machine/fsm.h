/**
 * @file    fsm.h
 * @brief   Mauiqna de estados principal del panel frontal
 * @author  Agusitn M. Zuliani
 * @date    31/03/26
 * @copyright   Agustin M. Zuliani (c)  2026
 */

#ifndef FSM_H_
#define FSM_H_

/*=================================[ includes ]=================================*/

#include "events.h"
#include "signal_config.h"

/*============================[ macros and typedef ]============================*/

typedef enum
{
    /* Sin definir */
    EST_NONE        = -1,

    /* FSM_MAIN */
    EST_RESET       = 0 ,
    EST_INIT_PRESET     ,
    EST_IDLE            ,

    /* FSM_SIGNAL_EDITTING */
    EST_SET_FREQ        ,
    EST_SET_AMPL        ,
    EST_SET_OFFS        ,
    EST_SET_DUTY        ,
    EST_SET_PHAS        ,
    EST_SET_WAVE        ,

    EST_COUNT           ,
} fsm_state_t;

typedef void (*fsm_action_fn)(const fsm_event_msg_t *msg);
typedef void (*fsm_state_fn)(void);

typedef struct 
{
    fsm_action_fn   action;
    fsm_state_t     next_state;
} fsm_transition_t;

typedef struct 
{
    fsm_state_fn        on_entry;
    fsm_state_fn        on_exit;
    fsm_transition_t    transitions[EVENT_COUNT];
} fsm_state_def_t;

/**
 * @brief   Tipo de estructura de fsm
 * @param   current         Estado actual
 * @param   history_main    Estado anterior de la fsm main
 * @param   history_signal  Estado anterior de la fsm signal
 * @param   live            
 * @param   editing         
 * @param   active_ch           
 * @param   cursor_pos          
 */
typedef struct 
{
    fsm_state_t         current;
    fsm_state_t         history_main;
    fsm_state_t         history_signal;
    awg_cfg_t           live;
    awg_cfg_t           editing;
    uint8_t             active_ch;
    uint8_t             cursor_pos;
} fsm_t;

/*==============================[ public functions ]============================*/

/**
 * @brief   Inicializacion de la fsm pricipal de app
 */
void fsm_init(void);

/**
 * @brief   Dispatch de la fsm principal de app
 * @param   msg Puntero al tipo de mensaje que produjo el evento
 */
void fsm_dispatch(const fsm_event_msg_t *msg);

/**
 * @brief   Devuelve la direccion de memoria del objeto de tipo fsm_t
 */
fsm_t *fsm_get(void);

#endif