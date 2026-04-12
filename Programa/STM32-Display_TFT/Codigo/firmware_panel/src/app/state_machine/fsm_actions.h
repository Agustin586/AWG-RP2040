/**
 * @file    fsm_actions.h
 * @brief   Acciones de la maquia de estados
 * @author  Agustin M. Zuliani
 * @date    02/04/26
 * @copyright   Agustin M. Zuliani (c)  2026
 */

#ifndef FSM_ACTIONS_H_
#define FSM_ACTIONS_H_

/*=================================[ includes ]=================================*/

#include "events.h"

/*==============================[ entry / exit ]================================*/

/* FSM_MAIN */
void entry_reset       (void);
void entry_init_preset (void);
void entry_idle        (void);
void exit_idle         (void);

/* FSM_SIGNAL_EDITING */
void entry_set_freq    (void);
void entry_set_ampl    (void);
void entry_set_offs    (void);
void entry_set_duty    (void);
void entry_set_phas    (void);
void entry_set_wave    (void);
void exit_signal       (void);

/*==============================[ acciones ]====================================*/

/* FSM_MAIN */
void action_reset         (const fsm_event_msg_t *msg);
void action_init_preset   (const fsm_event_msg_t *msg);
void action_enter_signal  (const fsm_event_msg_t *msg);
void action_select_ch1    (const fsm_event_msg_t *msg);
void action_select_ch2    (const fsm_event_msg_t *msg);

/* cursor */
void action_cursor_left   (const fsm_event_msg_t *msg);
void action_cursor_right  (const fsm_event_msg_t *msg);

/* frecuencia */
void action_st_freq_increment (const fsm_event_msg_t *msg);
void action_st_freq_decrement (const fsm_event_msg_t *msg);

/* amplitud */
void action_st_ampl_increment (const fsm_event_msg_t *msg);
void action_st_ampl_decrement (const fsm_event_msg_t *msg);

/* offset */
void action_st_offs_increment (const fsm_event_msg_t *msg);
void action_st_offs_decrement (const fsm_event_msg_t *msg);

/* duty cycle */
void action_st_duty_increment (const fsm_event_msg_t *msg);
void action_st_duty_decrement (const fsm_event_msg_t *msg);

/* fase */
void action_st_phas_increment (const fsm_event_msg_t *msg);
void action_st_phas_decrement (const fsm_event_msg_t *msg);

/* forma de onda */
void action_st_wave_increment (const fsm_event_msg_t *msg);
void action_st_wave_decrement (const fsm_event_msg_t *msg);

/* IPC */
void action_send_ipc    (const fsm_event_msg_t *msg);
void action_apply       (const fsm_event_msg_t *msg);
void action_show_error  (const fsm_event_msg_t *msg);
void action_cancel      (const fsm_event_msg_t *msg);

#endif /*FSM_ACTIONS_H_*/