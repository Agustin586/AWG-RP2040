/**
 * @file    awg.h
 * @brief   Define el objeto awg cfg para su configuracion
 * @author  Agustin M. Zuliani
 * @date    08/04/26
 * @copyright   Agustin M. Zuliani
 */

#ifndef AWG_H_
#define AWG_H_

/*=================================[ includes ]=================================*/

#include "signal_config.h"
#include <stdint.h>

/*============================[ macros and typedef ]============================*/



/*=============================[ public functions ]============================*/

void awg_set_freq(uint32_t freq_hz);

void awg_set_ampl(uint32_t ampl_mv);

void awg_set_offs(int16_t offs_mv);

void awg_set_phas(int16_t phas_deg);

void awg_set_duty(uint16_t duty_x_100);

void awg_set_wave(waveform_t wave);

void awg_set_output(bool output_enable);

void awg_set_channel(uint8_t channel_awg);

void awg_set_wave(waveform_t wave);

uint8_t awg_get_channel();

uint32_t awg_get_freq();

uint32_t awg_get_ampl();

int16_t awg_get_offs();

int16_t awg_get_phas();

uint16_t awg_get_duty();

waveform_t awg_get_wave();

#endif /* AWG_H_ */