/**
 * @file    ipc_payloads.h
 * @brief   Define las estructuras necesarias para el envio del mensaje para la
 *          comunicacion SPI entre placas.
 * @author  Agustin M. Zuliani
 * @date    26/03/26
 * @copyright   Agustin M. Zuliani (c)  2026
 */

#ifndef IPC_PAYLOADS_H_
#define IPC_PAYLOADS_H_

/*=================================[ includes ]=================================*/

#include <stdint.h>
#include <stdbool.h>

/*============================[ macros and typdedef ]============================*/

typedef struct 
{
    uint32_t    frequency_hz;
    uint8_t     channel;
} payload_set_frequency_t;

typedef struct
{
    uint8_t     waveform;
    uint8_t     channel;
} payload_set_waveform_t;

typedef struct
{
    int16_t     amplitude_mv;
    int16_t     offset_mv;
    uint8_t     channel;
} payload_set_amp_offset_t;

typedef struct
{
    int16_t     phase_deg;
    uint8_t     channel;
} payload_set_phase_t;

typedef struct
{
    bool        enable;
    uint8_t     channel;
} payload_set_output_enable_t;

typedef struct
{
    uint8_t     slot;
} payload_preset_slot_t;

#endif