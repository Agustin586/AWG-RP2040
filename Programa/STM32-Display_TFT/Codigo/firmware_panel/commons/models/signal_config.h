#ifndef SIGNAL_CONFIG_H_
#define SIGNAL_CONFIG_H_

/*=================================[ includes ]=================================*/

#include <stdint.h>
#include <stdbool.h>

/*============================[ macros and typdedef ]============================*/

#define AWG_NUM_CHANNELS    2
#define AWG_CH1             0
#define AWG_CH2             1

#define AWG_FREQ_HZ_MAX     10000000    // 10 MHz
#define AWG_AMPL_mVPP_MAX   20000       // 20 Vpp
#define AWG_OFFS_mVP_MAX    5000        // 5 Vp
#define AWG_DUTY_PORC_MAX   100         // 100 %

#define AWG_FREQ_HZ_MIN     1           // 1 Hz
#define AWG_AMPL_mVPP_MIN   250         // 250 mVpp
#define AWG_OFFS_mVPP_MIN   -5000       // -5 Vp 

typedef enum
{
    SIGNAL_CH_1 = 0,
    SIGNAL_CH_2    ,
    SIGNAL_CH_COUNT,
} signal_ch_t;

typedef enum
{
    WAVEFORM_SINE = 0       ,
    WAVEFORM_SQUARE         ,
    WAVEFORM_TRIANGLE       ,
    WAVEFORM_SAWTOOTH_UP    ,
    WAVEFORM_SAWTOOTH_DOWN  ,
    WAVEFORM_ARB            ,
    WAVEFORM_COUNT          ,
} waveform_t;

/**
 * @brief   Tipo de datos con las configuraciones de los parametros
 *          de cada canal de la senial
 * @param   frequency_hz        Valor de la frecuencia en Hz
 * @param   amplitude_mv        Valor de la amplitud en mV
 * @param   offset_mv           Valor del offset en mV
 * @param   phase_deg           Valor de la fase en grados
 * @param   duty_cycle_x_100    Valor del ciclo de trabajo en porcentaje
 * @param   waveform            Tipo de onda a mostrar
 * @param   output_enable       Estado de la salida
 * 
 */
typedef struct 
{
    uint32_t    frequency_hz;
    uint32_t    amplitude_mv;
    int16_t     offset_mv;
    int16_t     phase_deg;
    uint16_t    duty_cycle_x_100;
    waveform_t  waveform;
    bool        output_enable;
} channel_cfg_t;

/**
 * @brief   Tipo de dato para la configuracion del awg con todas sus
 *          funcionalidades
 * @param   channel_cfg         Configuracion del canal
 */
typedef struct 
{
    channel_cfg_t channel_cfg[AWG_NUM_CHANNELS];
} awg_cfg_t;

#endif