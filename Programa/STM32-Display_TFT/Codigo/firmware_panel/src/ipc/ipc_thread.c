/**
 * @file    ipc_thread.c
 * @brief   Hilo de ejecucion que maneja la transmision de datos desde spi
 * @author  Agustin M. Zuliani
 * @date    28/03/26
 * @copyright   Agustin M. Zuliani (c)  2026
 */

/*=================================[ includes ]=================================*/

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "ipc_master.h"
#include "ipc_parser.h"
#include "ipc_protocol.h"
#include "awg_error.h"
#include "event_bus.h"

/*============================[ macros and typdedef ]============================*/

#define IPC_THREAD_STACK_SIZE   1024
#define IPC_THREAD_PRIORITY     6

/*============================[ private declarations ]===========================*/

/**
 * @brief Hilo de transmision SPI mediante el protocolo IPC. Ingresa desde este
 * un mensaje en la cola de datos proveniente desde app que luego debe
 * transmitirse a la otra placa.
 * 
 * @param a Parametro de entrada
 * @param b Parametro de entrada
 * @param c Parametro de entrada
 */
void ipc_thread_fn(void *a, void *b, void *c);

LOG_MODULE_REGISTER(ipc_thread, LOG_LEVEL_DBG);

K_THREAD_DEFINE(ipc_thread_id, 
                IPC_THREAD_STACK_SIZE,
                ipc_thread_fn,
                NULL, NULL, NULL,
                IPC_THREAD_PRIORITY,
                0, 0);

/*=============================[ private functions ]=============================*/

void ipc_thread_fn(void *a, void *b, void *c)
{
    ipc_packet_t    pkt  = {0};
    ipc_response_t  resp = {0};
    fsm_event_msg_t ack  = {0};

    ipc_master_init();

    while (1)
    {
        /* Espera mensaje de app */
        k_msgq_get(event_bus_get_app_to_ipc(), &pkt, K_FOREVER);

        /* Envia y recibe datos */
        int ret = ipc_master_send(&pkt, &resp);

        // if (ret == AWG_OK)
        // {
        //     ack.id      = EVENT_IPC_ACK_OK;
        //     ack.value   = AWG_OK;
        // }
        // else 
        // {
        //     ack.id      = EVENT_IPC_ACK_ERR;
        //     ack.value   = ret;
        //     LOG_ERR("IPC fail: %d", ret);
        // }

        // /* Informa el resultado a la FSM */
        // k_msgq_put(event_bus_get_ipc_to_app(), &ack, K_NO_WAIT);
    }
}