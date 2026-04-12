/**
 * @file    msg_app_to_ipc.h
 * @brief   Realiza un testeo del mensaje formado por app hacia ipc y debe
 *          verificarse con el analizador logico si el mensaje enviado
 *          por el bus es correcto
 * @author  Agustin M. Zuliani
 * @date    29/03/26
 * @copyright   Agustin M. Zuliani (c)  2026
 */

#ifndef MSG_APP_TO_IPC_H_
#define MSG_APP_TO_IPC_H_

/*=================================[ includes ]=================================*/

#include "ipc_protocol.h"

/*=============================[ public functions ]==============================*/

int ztest_msg_app_to_ipc(void);

#endif