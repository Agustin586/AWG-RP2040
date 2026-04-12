/**
 * @file    signal_actions.c
 * @brief   Acciones relacionadas con las seniales y sus configuraciones
 * @author  Agustin M. Zuliani
 * @date    08/04/26
 * @copyright   Agustin M. Zuliani
 */

/*=================================[ includes ]=================================*/

#include "signal_actions.h"

#include "awg.h"
#include "digit.h"
#include "ret.h"
#include <math.h>
#include <zephyr/logging/log.h>

/*============================[ macros and typedefs ]===========================*/


/*===========================[ private declarations ]===========================*/

LOG_MODULE_REGISTER(signal_actions, LOG_LEVEL_DBG);

static uint8_t channel = AWG_CH1;
static signal_param_t signal_cfg_current = SIGNAL_PARAM_ACTUAL_NONE;

/*=============================[ private functions ]============================*/



/*=============================[ public functions ]=============================*/

void signal_set_actual_param(signal_param_t actual_param)
{
    if (actual_param >= SIGNAL_PARAM_ACTUAL_COUNT || actual_param < SIGNAL_PARAM_ACTUAL_NONE)
    {
        LOG_ERR("No se puede seleccionar ese parametro de configuracion");
        return;
    }

    signal_cfg_current = actual_param;

    return;
}

void signal_entry_set_freq(void)
{

    return;
}

void signal_entry_set_ampl(void)
{

    return;
}

void signal_entry_set_offs(void)
{

    return;
}

void signal_entry_set_duty(void)
{

    return;
}

void signal_entry_set_phas(void)
{

    return;
}

void signal_entry_set_wave(void)
{

    return;
}


void signal_exit(void)
{

    return;
}

void signal_action_freq_increment()
{
    uint32_t freq_hz = 0;
    ret_t ret = RET_OK;

    /* Obtiene el canal activo */
    channel = awg_get_channel();

    /* Obtiene la frecuencia actual */
    freq_hz = awg_get_freq();

    /* Incrementamos el digito */
    ret = digit_inc(channel, DIGIT_TYPE_FREQ);
    
    /* Modificamos la frecuencia */
    freq_hz += pow(10, digit_get_cursor(channel, DIGIT_TYPE_FREQ)) * digit_get_count(channel, DIGIT_TYPE_FREQ);

    /* Cargamos la nueva frecuencia */
    awg_set_freq(freq_hz);

    return;
}

void signal_action_freq_decrement()
{
    uint32_t freq_hz;
    ret_t ret = RET_OK;

    /* Obtiene el canal activo */
    channel = awg_get_channel();

    /* Obtiene la frecuencia actual */
    freq_hz = awg_get_freq();

    /* Decrementamos el digito */
    ret = digit_dec(channel, DIGIT_TYPE_FREQ);

    /* Modificamos la frecuencia */
    freq_hz -= pow(10, digit_get_cursor(channel, DIGIT_TYPE_FREQ)) * digit_get_count(channel, DIGIT_TYPE_FREQ);

    /* Cargamos la nueva frecuencia */
    awg_set_freq(freq_hz);

    return;
}

void signal_action_ampl_increment()
{
    uint32_t ampl_mv = 0;
    ret_t ret = RET_OK;

    /* Obtiene el canal activo */
    channel = awg_get_channel();

    /* Obtiene la amplitud actual */
    ampl_mv = awg_get_ampl();

    /* Incrementamos el digito de amplitud  */
    ret = digit_inc(channel, DIGIT_TYPE_AMPL);

    /* Modificamos la amplitud */
    ampl_mv += pow(10, digit_get_count(channel, DIGIT_TYPE_AMPL)) * digit_get_count(channel, DIGIT_TYPE_AMPL);

    /* Cargamos la nueva amplitud */
    awg_set_ampl(ampl_mv);

    return;
}

void signal_action_ampl_decrement()
{
    uint32_t ampl_mv = 0;
    ret_t ret = RET_OK;

    /* Obtiene el canal activo */
    channel = awg_get_channel();

    /* Obtiene la amplitud actual */
    ampl_mv = awg_get_ampl();

    /* Decrementamos el digito de amplitud */
    ret = digit_dec(channel, DIGIT_TYPE_AMPL);

    /* Modificamos la amplitud */
    ampl_mv -= pow(10, digit_get_cursor(channel, DIGIT_TYPE_AMPL)) * digit_get_count(channel, DIGIT_TYPE_AMPL);

    /* Cargamos la nueva amplitud */
    awg_set_ampl(ampl_mv);

    return;
}

void signal_action_offs_increment()
{
    int16_t offs_mv = 0;
    ret_t ret = RET_OK;

    /* Obtiene el canal activo */
    channel = awg_get_channel();

    /* Obtiene el offset actual */
    offs_mv = awg_get_offs();

    /* Incrementamos el digito de offset */
    ret = digit_inc(channel, DIGIT_TYPE_OFFS);

    /* Modificamos el offset */
    offs_mv += pow(10, digit_get_cursor(channel, DIGIT_TYPE_OFFS)) * digit_get_count(channel, DIGIT_TYPE_OFFS);

    /* Cargamos el nuevo offset */
    awg_set_offs(offs_mv);

    return;
}

void signal_action_offs_decrement()
{
    int16_t offs_mv = 0;
    ret_t ret = RET_OK;

    /* Obtiene el canal activo */
    channel = awg_get_channel();

    /* Obtiene el offset actual */
    offs_mv = awg_get_offs();

    /* Decrementamos el digito de offset */
    ret = digit_dec(channel, DIGIT_TYPE_OFFS);

    /* Modificamos el offset */
    offs_mv -= pow(10, digit_get_cursor(channel, DIGIT_TYPE_OFFS)) * digit_get_count(channel, DIGIT_TYPE_OFFS);

    /* Cargamos el nuevo offset */
    awg_set_offs(offs_mv);

    return;
}

void signal_action_phas_increment()
{
    int16_t phas_deg = 0;
    ret_t ret = RET_OK;

    /* Obtiene el canal activo */
    channel = awg_get_channel();

    /* Obtiene la fase actual */
    phas_deg = awg_get_phas();

    /* Incrementamos el digito de fase */
    ret = digit_inc(channel, DIGIT_TYPE_PHAS);

    /* Modificamos la fase */
    phas_deg += pow(10, digit_get_cursor(channel, DIGIT_TYPE_PHAS)) * digit_get_count(channel, DIGIT_TYPE_PHAS);

    /* Cargamos la nueva fase */
    awg_set_phas(phas_deg);

    return;
}

void signal_action_phas_decrement()
{
    int16_t phas_deg = 0;
    ret_t ret = RET_OK;

    /* Obtiene el canal activo */
    channel = awg_get_channel();

    /* Obtiene la fase actual */
    phas_deg = awg_get_phas();

    /* Decrementamos el digito de fase */
    ret = digit_dec(channel, DIGIT_TYPE_PHAS);

    /* Modificamos la fase */
    phas_deg -= pow(10, digit_get_cursor(channel, DIGIT_TYPE_PHAS)) * digit_get_count(channel, DIGIT_TYPE_PHAS);

    /* Cargamos la nueva fase */
    awg_set_phas(phas_deg);

    return;
}

void signal_action_duty_increment()
{
    uint16_t duty_x_100 = 0;
    ret_t ret = RET_OK;

    /* Obtiene el canal activo */
    channel = awg_get_channel();

    /* Obtiene el ciclo de trabajo actual */
    duty_x_100 = awg_get_duty();

    /* Incrementamos el digito de duty */
    ret = digit_inc(channel, DIGIT_TYPE_AMPL);

    /* Modificamos el ciclo de trabajo */
    duty_x_100 += pow(10, digit_get_cursor(channel, DIGIT_TYPE_AMPL)) * digit_get_count(channel, DIGIT_TYPE_AMPL);

    /* Cargamos el nuevo ciclo de trabajo */
    awg_set_duty(duty_x_100);

    return;
}

void signal_action_duty_decrement()
{
    uint16_t duty_x_100 = 0;
    ret_t ret = RET_OK;

    /* Obtiene el canal activo */
    channel = awg_get_channel();

    /* Obtiene el ciclo de trabajo actual */
    duty_x_100 = awg_get_duty();

    /* Decrementamos el digito de duty */
    ret = digit_dec(channel, DIGIT_TYPE_AMPL);

    /* Modificamos el ciclo de trabajo */
    duty_x_100 -= pow(10, digit_get_cursor(channel, DIGIT_TYPE_AMPL)) * digit_get_count(channel, DIGIT_TYPE_AMPL);

    /* Cargamos el nuevo ciclo de trabajo */
    awg_set_duty(duty_x_100);

    return;
}

void signal_action_wave_increment()
{
    waveform_t wave = WAVEFORM_SINE;

    /* Obtiene el canal activo */
    channel = awg_get_channel();

    /* Obtiene la forma de onda actual */
    wave = awg_get_channel();

    /* Modificamos la forma de onda */
    wave += 1;

    /* Cargamos la nueva forma de onda */
    awg_set_wave(wave);

    return;
}

void signal_action_wave_decrement()
{
    waveform_t wave = WAVEFORM_SINE;

    /* Obtiene el canal activo */
    channel = awg_get_channel();

    /* Obtiene la forma de onda actual */
    wave = awg_get_channel();

    /* Modificamos la forma de onda */
    wave -= 1;

    /* Cargamos la nueva forma de onda */
    awg_set_wave(wave);

    return;
}

void signal_action_sel_ch1()
{
    awg_set_channel(SIGNAL_CH_1);

    return;
}

void signal_action_sel_ch2()
{
    awg_set_channel(SIGNAL_CH_2);

    return;
}

void signal_action_mov_cursor(int8_t move)
{
    digit_type_t digit_type = DIGIT_TYPE_FREQ;

    switch (signal_cfg_current)
    {
        case SIGNAL_PARAM_ACTUAL_FREQ:
            digit_type = DIGIT_TYPE_FREQ;
            break;

        case SIGNAL_PARAM_ACTUAL_AMPL:
            digit_type = DIGIT_TYPE_AMPL;
            break;
        
        case SIGNAL_PARAM_ACTUAL_DUTY:
            digit_type = DIGIT_TYPE_DUTY;
            break;
        
        case SIGNAL_PARAM_ACTUAL_PHAS:
            digit_type = DIGIT_TYPE_PHAS;
            break;

        case SIGNAL_PARAM_ACTUAL_OFFS:
            digit_type = DIGIT_TYPE_OFFS;
            break;
        
        default:
            return;
            break;
    }

    if (move == DIGIT_MOVE_CURSOR_LEFT)
    {
        digit_move_left(channel, digit_type);
    }
    else if (move == DIGIT_MOVE_CURSOR_RIGHT)
    {
        digit_move_right(channel, digit_type);
    }

    return;
}
