/**
 * @file    ipc_msg.h
 * @author  Agustin M. Zuliani (amzuliani02@gmail.com)
 * @brief   Se encarga de generar el mensaje que luego se transmite
 *          por spi hacia la placa de control
 * @version 1.0
 * @date    2026-04-11
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef IPC_MSG_H_
#define IPC_MSG_H_

/*=================================[ includes ]=================================*/

#include "awg.h"

#include <zephyr/logging/log.h>
#include "events.h"
#include "fsm.h"

/*============================[ macros and typedefs ]===========================*/



/*=============================[ public functions ]=============================*/

void ipc_msg_action_send(fsm_state_t state_current);

#endif /* IPC_MSG_H_ */