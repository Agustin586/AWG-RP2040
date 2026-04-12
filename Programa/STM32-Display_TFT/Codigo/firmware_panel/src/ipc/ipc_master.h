/**
 * @file    ipc_master.h
 * @brief   API que se encarga de procesar mensajes de transmision y recepcion
 *          desde el maestro.
 * @author  Agustin M. Zuliani
 * @date    26/03/26
 * @copyright   Agustin M. Zuliani (r)  2026
 */

#ifndef IPC_MASTER_H_
#define IPC_MSATER_H_

/*=================================[ includes ]=================================*/

#include "ipc_protocol.h"
#include <stdint.h>

/*============================[ macros and typdedef ]============================*/



/*=============================[ public functions ]============================*/

int ipc_master_init(void);
int ipc_master_send(const ipc_packet_t *pkt, ipc_response_t *resp);

#endif