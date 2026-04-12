/**
 * @file    msg_app_to_ipc.c
 * @brief   Realiza un testeo del mensaje formado por app hacia ipc y debe
 *          verificarse con el analizador logico si el mensaje enviado
 *          por el bus es correcto
 * @author  Agustin M. Zuliani
 * @date    29/03/26
 * @copyright   Agustin M. Zuliani (c)  2026
 */

/*=================================[ includes ]=================================*/

#include "msg_app_to_ipc.h"
#include "ipc_parser.h"
#include "event_bus.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/*============================[ macros and typdedef ]============================*/

#define ZTEST_MSG_APP_TO_IPC    0X1F

/*===========================[ private declarations ]===========================*/

LOG_MODULE_REGISTER(ztest, LOG_LEVEL_INF);

/*=============================[ public functions ]=============================*/

int ztest_msg_app_to_ipc(void)
{
    static ipc_packet_t msg_pkt = {
        .magic          = IPC_MAGIC             ,
        .version        = IPC_VERSION           ,
        .seq            = 0X01                  ,
        .cmd            = CMD_PING              ,
        .payload_len    = 0                     ,
        .payload        = {0}                   ,
    };

    msg_pkt.crc = ipc_crc16((const uint8_t *)&msg_pkt,
                            sizeof(ipc_packet_t) - sizeof(uint16_t));

    LOG_HEXDUMP_INF(&msg_pkt, sizeof(msg_pkt), "pkt a enviar:");

    k_msgq_put(event_bus_get_app_to_ipc(), &msg_pkt, K_NO_WAIT);
    
    LOG_INF("Packetage send");
    LOG_INF("sizeof ipc_packet_t:  %d bytes", sizeof(ipc_packet_t));
    LOG_INF("sizeof ipc_response_t: %d bytes", sizeof(ipc_response_t));

    return 0;
}