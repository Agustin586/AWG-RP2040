/**
 * @file    awg.c
 * @brief   Define el objeto awg cfg para su configuracion
 * @author  Agustin M. Zuliani
 * @date    08/04/26
 * @copyright   Agustin M. Zuliani
 */

/*=================================[ includes ]=================================*/

#include "awg.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/*============================[ private declarations ]==========================*/

LOG_MODULE_REGISTER(awg_cfg, LOG_LEVEL_DBG);

static awg_cfg_t awg;
static uint8_t channel = AWG_CH1;

/*=============================[ public functions ]============================*/

void awg_set_freq(uint32_t freq_hz)
{
    if (freq_hz > AWG_FREQ_HZ_MAX)
    {
        LOG_DBG("Se supera el maximo valor de frecuencia permitido.");
        freq_hz = AWG_FREQ_HZ_MAX;
    }

    awg.channel_cfg[channel].frequency_hz = freq_hz;

    return;
}

void awg_set_ampl(uint32_t ampl_mv)
{
    if (ampl_mv > AWG_AMPL_mVPP_MAX)
    {
        LOG_DBG("Se supera el maximo valor de amplitud permitido.");
        ampl_mv = AWG_AMPL_mVPP_MAX;
    }
    
    if (ampl_mv < AWG_AMPL_mVPP_MIN)
    {
        LOG_DBG("Se supara el minimo valor de amplitud permitido.");
        ampl_mv = AWG_AMPL_mVPP_MIN;
    }
    
    awg.channel_cfg[channel].amplitude_mv = ampl_mv;
    
    return;
}

void awg_set_offs(int16_t offs_mv)
{
    if (offs_mv > AWG_OFFS_mVP_MAX)
    {
        LOG_DBG("Se supera el maximo valor de offset permitido.");
        offs_mv = AWG_OFFS_mVP_MAX;
    }
    
    if (offs_mv < AWG_OFFS_mVPP_MIN)
    {
        LOG_DBG("Se supera el minimo valor de offset permitido.");
        offs_mv = AWG_OFFS_mVPP_MIN;
    }
    
    awg.channel_cfg[channel].offset_mv = offs_mv;
    
    return;
}

void awg_set_phas(int16_t phas_deg)
{
    if (phas_deg > 360)
    {
        LOG_DBG("Se superan los 360 grados.");
        phas_deg = phas_deg - 360;
    }
    
    awg.channel_cfg[channel].phase_deg = phas_deg;
    
    return;
}

void awg_set_duty(uint16_t duty_x_100)
{
    if (duty_x_100 > 100)
    {
        LOG_DBG("Ciclo de trabajo mayor a 100%%. Se setea en 100.");
        duty_x_100 = 100;
    }
    
    awg.channel_cfg[channel].duty_cycle_x_100 = duty_x_100;
    
    return;
}

void awg_set_output(bool output_enable)
{
    awg.channel_cfg[channel].output_enable = output_enable;
    
    return;
}

void awg_set_channel(uint8_t channel_awg)
{
    if (channel_awg >= SIGNAL_CH_COUNT) 
    {
        LOG_ERR("Canal seleccionado incorrecto");
        
        return;
    }
    
    channel = channel_awg;
    
    return;
}

void awg_set_wave(waveform_t wave)
{
    if (wave > WAVEFORM_COUNT-1)
    {
        LOG_ERR("Forma de onda no valida");
        wave = WAVEFORM_ARB;
    }

    awg.channel_cfg[channel].waveform = wave;

    return;
}

uint8_t awg_get_channel()
{
    return channel;
}

uint32_t awg_get_freq()
{
    return awg.channel_cfg[channel].frequency_hz;
}

uint32_t awg_get_ampl()
{
    return awg.channel_cfg[channel].amplitude_mv;
}

int16_t awg_get_offs()
{
    return awg.channel_cfg[channel].offset_mv;
}

int16_t awg_get_phas()
{
    return awg.channel_cfg[channel].phase_deg;
}

uint16_t awg_get_duty()
{
    return awg.channel_cfg[channel].duty_cycle_x_100;
}

waveform_t awg_get_wave()
{
    return awg.channel_cfg[channel].waveform;
}