/**
 * @file    event_bus.c
 * @brief   Se encuentran declaradas todas las colas de datos para eventos
 * @author  Agustin M. Zuliani
 * @date    28/03/26
 * @copyright   Agustin M. Zuliani (c)  2026
 */

/*=================================[ includes ]=================================*/

#include "event_bus.h"

/*===========================[ private declarations ]============================*/

K_MSGQ_DEFINE(q_input_to_app, sizeof(fsm_event_msg_t), 16, 4);
K_MSGQ_DEFINE(q_app_to_ipc,   sizeof(ipc_packet_t),     4, 4);
K_MSGQ_DEFINE(q_ipc_to_app,   sizeof(ipc_response_t),   4, 4);
K_MSGQ_DEFINE(q_app_to_ui,    sizeof(uint8_t),          8, 4);

/*=============================[ public functions ]==============================*/

struct k_msgq *event_bus_get_input_to_app(void) { return &q_input_to_app; }
struct k_msgq *event_bus_get_app_to_ipc(void)   { return &q_app_to_ipc;   }
struct k_msgq *event_bus_get_ipc_to_app(void)   { return &q_ipc_to_app;   }
struct k_msgq *event_bus_get_app_to_ui(void)    { return &q_app_to_ui;    }