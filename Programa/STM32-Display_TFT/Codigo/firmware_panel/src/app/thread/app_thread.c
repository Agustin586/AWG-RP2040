/**
 * @file    app_thread.c
 * @brief   Hilo que maneja la logica de la aplicaicon
 * @author  Agustin M. Zuliani
 * @date    03/04/26
 * @copyright   Agustin M. Zuliani (c)  2026
 */

/*=================================[ includes ]=================================*/

#include "fsm.h"
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "event_bus.h"
#include "events.h"
#include <stdbool.h>

/*============================[ macros and typedef ]============================*/

#define APP_THREAD_SIZE     1024
#define APP_THREAD_PRIORITY  3

#define MESSAGE_RECEIVED    0

/*===========================[ private declarations ]===========================*/

LOG_MODULE_REGISTER(app_thread, LOG_LEVEL_DBG);

static void app_thread(void *p1, void *p2, void *p3);

K_THREAD_DEFINE(app_thread_id, 
                APP_THREAD_SIZE, 
                app_thread,
                NULL, NULL, NULL,
                APP_THREAD_PRIORITY, 
                0, 0);

/*============================[ private functions ]=============================*/

static void app_thread(void *p1, void *p2, void *p3)
{
    bool new_event = false;     // Detecta cuando hay un nuevo evento

    fsm_event_msg_t msg = {0};

    LOG_DBG("app thread iniciado");

    fsm_init();

    msg.id     = EVENT_INPUT;
    msg.value  = 0;

    fsm_dispatch(&msg);     // RESET -> INIT_PRESET
    fsm_dispatch(&msg);     // INIT_PRESET -> IDLE

    while (1)
    {
        /* Espera mensaje de la cola de datos */
        if (k_msgq_get(event_bus_get_ipc_to_app(), &msg, K_NO_WAIT) == MESSAGE_RECEIVED)
        {new_event = true;}
        else 
        {
            if (k_msgq_get(event_bus_get_input_to_app(), &msg, K_NO_WAIT) == MESSAGE_RECEIVED)
            {new_event = true;}
        }

        /* Ejecuta en la fsm */
        if (new_event)
        {
            fsm_dispatch(&msg);

            /* Limpia la bandera */
            new_event = false;
        }

        k_sleep(K_MSEC(10));
    }

    return;
}
