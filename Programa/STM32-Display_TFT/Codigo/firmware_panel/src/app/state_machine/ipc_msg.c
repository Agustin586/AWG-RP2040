/*=================================[ includes ]=================================*/

#include "ipc_msg.h"

#include "event_bus.h"
#include "ipc_protocol.h"
#include "ipc_payloads.h"
#include "ipc_parser.h"
#include "awg.h"
#include <string.h>
#include <zephyr/kernel.h>

/*===========================[ private declarations ]===========================*/

LOG_MODULE_REGISTER(ipc_msg, LOG_LEVEL_DBG);

static const ipc_cmd_t state_to_cmd[EST_COUNT] = {
    [EST_SET_FREQ] = CMD_SET_FREQUENCY,
    [EST_SET_AMPL] = CMD_SET_AMPLITUDE,
    [EST_SET_OFFS] = CMD_SET_OFFSET,
    [EST_SET_DUTY] = CMD_SET_DUTY,
    [EST_SET_PHAS] = CMD_SET_PHASE,
    [EST_SET_WAVE] = CMD_SET_WAVEFORM,
};

/*=============================[ public functions ]=============================*/

void ipc_msg_action_send(fsm_state_t state_current)
{
    ipc_packet_t pkt = {0};

    pkt.magic   = IPC_MAGIC  ;
    pkt.version = IPC_VERSION;
    pkt.seq++                ;
    pkt.cmd     = state_to_cmd[state_current];

    switch (pkt.cmd)
    {
        case CMD_SET_FREQUENCY:
        {
            payload_set_frequency_t p = {
                .frequency_hz   = awg_get_freq(),
                .channel        = awg_get_channel(),
            };
            memcpy(pkt.payload, &p, sizeof(p));
            pkt.payload_len = sizeof(p);
            break;
        }
        case CMD_SET_AMPLITUDE:
        case CMD_SET_OFFSET:
        {
            payload_set_amp_offset_t p = {
                .amplitude_mv   = awg_get_ampl(),
                .offset_mv      = awg_get_offs(),
                .channel        = awg_get_channel(),
            };
            memcpy(pkt.payload, &p, sizeof(p));
            pkt.payload_len = sizeof(p);
            break;
        }
        case CMD_SET_PHASE:
        {
            payload_set_phase_t p = {
                .phase_deg      = awg_get_phas(),
                .channel        = awg_get_channel(),
            };
            memcpy(pkt.payload, &p, sizeof(p));
            pkt.payload_len = sizeof(p);
            break;
        }
        default:
            LOG_ERR("comando desconocido: %d", pkt.cmd);
            break;
    }

    pkt.crc = ipc_crc16((const uint8_t *)&pkt,
                        sizeof(ipc_packet_t) - sizeof(uint16_t));

    k_msgq_put(event_bus_get_app_to_ipc(), &pkt, K_NO_WAIT);

    LOG_DBG("IPC enviado cmd: %d ch: %d", pkt.cmd, awg_get_channel());
}