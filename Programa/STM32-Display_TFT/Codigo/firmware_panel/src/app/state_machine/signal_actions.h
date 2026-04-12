/**
 * @file    signal_actions.h
 * @brief   Acciones relacionadas con las seniales y sus configuraciones
 * @author  Agustin M. Zuliani
 * @date    08/04/26
 * @copyright   Agustin M. Zuliani
 */

#ifndef SIGNAL_ACTIONS_H_
#define SIGNAL_ACTIONS_H_

/*=================================[ includes ]=================================*/

#include "signal_config.h"

/*============================[ macros and typedef ]============================*/

typedef enum
{
    DIGIT_MOVE_CURSOR_LEFT  = -1,
    DIGIT_MOVE_CURSOR_RIGHT =  1,
} digit_move_cursor_t;

typedef enum
{
    SIGNAL_PARAM_ACTUAL_NONE = -1,
    SIGNAL_PARAM_ACTUAL_FREQ     ,
    SIGNAL_PARAM_ACTUAL_AMPL     ,
    SIGNAL_PARAM_ACTUAL_OFFS     ,
    SIGNAL_PARAM_ACTUAL_PHAS     ,
    SIGNAL_PARAM_ACTUAL_DUTY     ,
    SIGNAL_PARAM_ACTUAL_WAVE     ,
    SIGNAL_PARAM_ACTUAL_COUNT    ,
} signal_param_t;

/*=============================[ public functions ]=============================*/

void signal_set_actual_param(signal_param_t actual_param);

void signal_entry_set_freq(void);
void signal_entry_set_ampl(void);
void signal_entry_set_offs(void);
void signal_entry_set_duty(void);
void signal_entry_set_phas(void);
void signal_entry_set_wave(void);

void signal_exit(void);

void signal_action_freq_increment();
void signal_action_freq_decrement();

void signal_action_ampl_increment();
void signal_action_ampl_decrement();

void signal_action_offs_increment();
void signal_action_offs_decrement();

void signal_action_phas_increment();
void signal_action_phas_decrement();

void signal_action_duty_increment();
void signal_action_duty_decrement();

void signal_action_wave_increment();
void signal_action_wave_decrement();

void signal_action_sel_ch1();
void signal_action_sel_ch2();

void signal_action_mov_cursor(int8_t move);

#endif /* SIGNAL_ACTIONS_H_ */