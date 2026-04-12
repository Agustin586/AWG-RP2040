/**
 * @file    event_bus.h
 * @brief   Declara y devuelve puntero a las diferentes cola de datos declaradas
 * @author  Agustin M. Zuliani
 * @date    28/03/26
 * @copyright   Agustin M. Zuliani (c)  2026
 */

#ifndef EVENT_BUS_H_
#define EVENT_BUS_H_

/*=================================[ includes ]=================================*/

#include <zephyr/kernel.h>
#include "ipc_protocol.h"
#include "events.h"

/*=============================[ public functions ]==============================*/

struct k_msgq *event_bus_get_input_to_app(void);
struct k_msgq *event_bus_get_app_to_ipc(void);
struct k_msgq *event_bus_get_ipc_to_app(void);
struct k_msgq *event_bus_get_app_to_ui(void);

#endif /*EVENT_BUS_H_*/