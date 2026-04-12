/**
 * @file    fsm_actions.c
 * @brief   Implementación de acciones de la FSM
 * @author  Agustin M. Zuliani
 * @date    27/03/26
 */

/*=================================[ includes ]=================================*/

#include "fsm_actions.h"

#include "ipc_protocol.h"
#include "ipc_payloads.h"
#include "ipc_msg.h"
#include "awg_error.h"
#include "fsm.h"
#include "signal_actions.h"
#include "app/event_bus/event_bus.h"
#include <zephyr/logging/log.h>
#include <stdint.h>

/*============================[ macros and typedef ]============================*/

LOG_MODULE_REGISTER(fsm_actions, LOG_LEVEL_DBG);

/*============================[ private functions ]============================*/

/**
 * @brief   Carga la informacion de awg data desde otro archivo y realiza
 *          una copia con la nueva configuracion que luego sera cargada
 *          si se presiona BTN_OK o descartada si se presiona BTN_CANCEL
 */
static void load_awg_data();
static void set_digit();
static void move_digit_left();
static void move_digit_right();

static void load_awg_data()
{


    return;
}

static void set_digit()
{
    // digit[].cursor    = CURSOR_MAX;
    // digit.type      = type;

    return;
}

static void move_digit_left()
{

    return;
}

static void move_digit_right()
{
    // ui_move_digit_right();

    return;
}

/*=============================[ entry / exit ]================================*/

void entry_reset(void) 
{
    LOG_DBG("entry_reset");

    /* Display */
    // Reinicia el display y muestra screen de carga
}

void entry_init_preset(void) 
{
    LOG_DBG("entry_init_preset");

    /* Busca la informacion en la eeprom */
    // Carga toda la informacion guardada de configuracion
}

void entry_idle(void) 
{
    LOG_DBG("entry_idle");
    /* notifica a la UI que muestre pantalla principal */
}

void exit_idle(void) 
{
    fsm_get()->history_main = fsm_get()->current;
    LOG_DBG("exit_idle - historia: %d", fsm_get()->history_main);
}

void entry_set_freq(void) 
{
    LOG_DBG("entry_set_freq");
    /* notifica a la UI que muestre pantalla de frecuencia */

    /* Seteamos el parametro de cfg actual */
    signal_set_actual_param(SIGNAL_PARAM_ACTUAL_FREQ);
    signal_entry_set_freq();
}

void entry_set_ampl(void) 
{
    LOG_DBG("entry_set_ampl");

    signal_set_actual_param(SIGNAL_PARAM_ACTUAL_AMPL);
    signal_entry_set_ampl();
}

void entry_set_offs(void) 
{
    LOG_DBG("entry_set_offs");

    signal_set_actual_param(SIGNAL_PARAM_ACTUAL_OFFS);
    signal_entry_set_offs();
}

void entry_set_duty(void) 
{
    LOG_DBG("entry_set_duty");

    signal_set_actual_param(SIGNAL_PARAM_ACTUAL_DUTY);
    signal_entry_set_duty();
}

void entry_set_phas(void) 
{
    LOG_DBG("entry_set_phas");

    signal_set_actual_param(SIGNAL_PARAM_ACTUAL_PHAS);
    signal_entry_set_phas();
}

void entry_set_wave(void) 
{
    LOG_DBG("entry_set_wave");

    signal_set_actual_param(SIGNAL_PARAM_ACTUAL_WAVE);
    signal_entry_set_wave();
}

void exit_signal(void) 
{
    /* guarda historia de FSM_SIGNAL */
    fsm_get()->history_signal = fsm_get()->current;
    LOG_DBG("exit_signal - historia: %d", fsm_get()->history_signal);
    signal_exit();
}

/*=============================[ FSM_MAIN ]====================================*/

void action_reset(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action_reset");
}

void action_init_preset(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action_init_preset");
}

void action_enter_signal(const fsm_event_msg_t *msg) 
{
    /* guarda historia de FSM_MAIN */
    fsm_get()->history_main = fsm_get()->current;
    LOG_DBG("action_enter_signal - historia main: %d",
            fsm_get()->history_main);
}

void action_select_ch1(const fsm_event_msg_t *msg) 
{
    LOG_DBG("canal activo: CH1");

    /* Modificamos el canal activo */
    signal_action_sel_ch1();

    /* Enviamos la informacion al display */
    // Falta realizar

    return;
}

void action_select_ch2(const fsm_event_msg_t *msg) 
{
    LOG_DBG("canal activo: CH2");

    /* Modificamos el canal activo */
    signal_action_sel_ch2();

    /* Enviamos la información al display */
    // Falta realizar

    return;
}

/*=============================[ cursor ]=====================================*/

void action_cursor_left(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action cursor left");

    signal_action_mov_cursor(DIGIT_MOVE_CURSOR_LEFT);

    return;
}

void action_cursor_right(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action cursor right");

    signal_action_mov_cursor(DIGIT_MOVE_CURSOR_RIGHT);

    return;
}

/*=============================[ frecuencia ]=================================*/

void action_st_freq_increment(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action freq increment");

    /* Incrementamos la frecuencia y digito */
    signal_action_freq_increment();
    
    /* Enviamos la informacion al display*/
    // Falta realizar

    return;
}

void action_st_freq_decrement(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action freq decrement");
    
    /* Decrementamos la frecuencia y digito */
    signal_action_freq_decrement();

    /* Enviamos la informacion al dispay */
    // Falta realizar
}

/*=============================[ amplitud ]===================================*/

void action_st_ampl_increment(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action ampl increment");

    /* Incrementamos el valor del digito y amplitud */
    signal_action_ampl_increment();

    /* Enviamos la informacion al display */
    // Falta realizar

    return;
}

void action_st_ampl_decrement(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action ampl decrement");

    /* Decrementamos el valor del digito y amplitud */
    signal_action_ampl_decrement();

    /* Enviamos la informacion al display */
    // Fata realizar

    return;
}

/*=============================[ offset ]=====================================*/

void action_st_offs_increment(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action offs increment");

    /* Modificamos contandor y actualizamos offset */
    signal_action_offs_increment();

    /* Enviamos la informacion al display */
    // Falta

}

void action_st_offs_decrement(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action offs decrement");

    signal_action_offs_decrement();
}

/*=============================[ duty cycle ]=================================*/

void action_st_duty_increment(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action duty increment");

    signal_action_duty_increment();
}

void action_st_duty_decrement(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action duty decrement");

    signal_action_duty_decrement();
}

/*=============================[ fase ]=======================================*/

void action_st_phas_increment(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action phas increment");

    signal_action_phas_increment();
}

void action_st_phas_decrement(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action phas decrement");

    signal_action_phas_decrement();
}

/*=============================[ forma de onda ]==============================*/

void action_st_wave_increment(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action wave increment");

    
}

void action_st_wave_decrement(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action wave decrement");
}

/*=============================[ IPC ]========================================*/

void action_send_ipc(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action send ipc");

    ipc_msg_action_send(fsm_get()->current);
}

void action_apply(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action apply");
}

void action_show_error(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action show error");
}

void action_cancel(const fsm_event_msg_t *msg) 
{
    LOG_DBG("action cancel");
}