/**
 * @file    input_thread.c
 * @brief   Se encarga de detectar cualquier tipo de interaccion con el usuario
 *          ya sean botones, encoder, etc. Luego mandar la informacion detectada
 *          como evento hacia otros hilos, mediante una cola de datos.
 * @author  Agustin M. Zuliani
 * @date    04/04/26
 * @copyright   Agustin M. Zuliani
 */

/*=================================[ includes ]=================================*/

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>
#include "events.h"
#include "event_bus.h"

/*============================[ macros and typdedef ]============================*/

#define INPUT_THREAD_STACK_SIZE     1024
#define INPUT_THREAD_PRIORITY       2

#define INPUT_THREAD_MAX_BTN        5
#define BTN_TIMEOUT_DEBOUNCE        150
#define BTN_READ_READY              0

#define INPUT_THREAD_TIMER_MS       10

/*============================[ private declarations ]===========================*/

typedef enum
{
    RET_INPUT_OK = 0,
    RET_INPUT_NULL  ,
    RET_INPUT_ERR   ,
    RET_INPUT_COUNT ,
} ret_input_t;

typedef struct
{
    uint8_t timeout_ms;                 ///< Tiempo del antirrebote
    uint8_t timer_count;                ///< Conteo del tiempo
    const struct gpio_dt_spec *spec;    ///< Puntero al boton del dt
    fsm_event_id_t event_id;            ///< Tipo de evento que produce dicho boton
} input_btn_table_t;

static void input_thread(void *p1, void *p2, void *p3);
static void error_fn(void);
static ret_input_t btn_init(void);
static ret_input_t enc_init(void);
static ret_input_t dt_init(void);
static void scan_btn(void);

static void debounce_timer_cb(struct k_timer *timer);

// Botones desde el device tree
static const struct gpio_dt_spec btn_freq = GPIO_DT_SPEC_GET(DT_NODELABEL(btn_freq), gpios);
static const struct gpio_dt_spec btn_ampl = GPIO_DT_SPEC_GET(DT_NODELABEL(btn_ampl), gpios);
static const struct gpio_dt_spec btn_offs = GPIO_DT_SPEC_GET(DT_NODELABEL(btn_offs), gpios);
static const struct gpio_dt_spec btn_phas = GPIO_DT_SPEC_GET(DT_NODELABEL(btn_phas), gpios);
static const struct gpio_dt_spec btn_ok   = GPIO_DT_SPEC_GET(DT_NODELABEL(btn_ok), gpios);

LOG_MODULE_REGISTER(input_thread, LOG_LEVEL_DBG);

K_THREAD_DEFINE(input_thread_id,
                INPUT_THREAD_STACK_SIZE,
                input_thread,
                NULL, NULL, NULL,
                INPUT_THREAD_PRIORITY,
                0, 0);

static input_btn_table_t input_btn_table[INPUT_THREAD_MAX_BTN] = 
{
    {.timeout_ms = BTN_TIMEOUT_DEBOUNCE/INPUT_THREAD_TIMER_MS, .timer_count = BTN_READ_READY, .spec = &btn_freq, .event_id = EVENT_BTN_FREQ},
    {.timeout_ms = BTN_TIMEOUT_DEBOUNCE/INPUT_THREAD_TIMER_MS, .timer_count = BTN_READ_READY, .spec = &btn_ampl, .event_id = EVENT_BTN_AMPL},
    {.timeout_ms = BTN_TIMEOUT_DEBOUNCE/INPUT_THREAD_TIMER_MS, .timer_count = BTN_READ_READY, .spec = &btn_offs, .event_id = EVENT_BTN_OFFS},
    {.timeout_ms = BTN_TIMEOUT_DEBOUNCE/INPUT_THREAD_TIMER_MS, .timer_count = BTN_READ_READY, .spec = &btn_phas, .event_id = EVENT_BTN_PHAS},
    {.timeout_ms = BTN_TIMEOUT_DEBOUNCE/INPUT_THREAD_TIMER_MS, .timer_count = BTN_READ_READY, .spec = &btn_ok  , .event_id = EVENT_BTN_OK  },
};

static struct k_timer debounce_timer;

/*=============================[ private functions ]=============================*/

static void input_thread(void *p1, void *p2, void *p3)
{
    ret_input_t ret = RET_INPUT_OK;

    ret = dt_init();
    if (ret != RET_INPUT_OK)
    {
        LOG_ERR("Error al inicializar el device tree de los perifericos");
        error_fn();
    }

    k_timer_init(&debounce_timer, debounce_timer_cb, NULL);
    k_timer_start(&debounce_timer, K_MSEC(INPUT_THREAD_TIMER_MS), K_MSEC(INPUT_THREAD_TIMER_MS));

    while (1)
    {
        scan_btn();

        k_sleep(K_MSEC(10));
    }

    return;
}

static void scan_btn(void)
{
    int ret_msg = 0;

    for(uint8_t i = 0; i < INPUT_THREAD_MAX_BTN; i++)
    {
        if (gpio_pin_get_dt(input_btn_table[i].spec) && input_btn_table[i].timer_count == BTN_READ_READY)
        {
            fsm_event_msg_t msg = {
                msg.id      = input_btn_table[i].event_id,
                msg.value   = 1,
            };

            ret_msg = k_msgq_put(event_bus_get_input_to_app(), &msg, K_NO_WAIT);
            if (ret_msg != 0)
            {
                LOG_ERR("No se pudo enviar el mensaje input to app");
            }

            input_btn_table[i].timer_count = input_btn_table[i].timeout_ms;
        }
    }

    return;
}

static ret_input_t btn_init(void)
{
    if(!gpio_is_ready_dt(&btn_freq))
    {
        LOG_ERR("Boton de freq. no listo");
        return RET_INPUT_ERR;
    }

    gpio_pin_configure_dt(&btn_freq, GPIO_INPUT);

    return RET_INPUT_OK;
}

static ret_input_t enc_init(void)
{


    return RET_INPUT_OK;
}

static ret_input_t dt_init(void)
{
    if (btn_init() != RET_INPUT_OK)
    {
        LOG_ERR("Error al inicializar los botones");
        return RET_INPUT_ERR;
    }

    if (enc_init() != RET_INPUT_OK)
    {
        LOG_ERR("Erro al inicializar el encoder");
        return RET_INPUT_ERR;
    }

    return RET_INPUT_OK;
}

static void error_fn(void)
{
    while (1)
    {
        
    }
}

static void debounce_timer_cb(struct k_timer *timer)
{
    for (uint8_t i = 0; i < INPUT_THREAD_MAX_BTN; i++)
    {
        if (input_btn_table[i].timer_count)
        {
            input_btn_table[i].timer_count--;
        }
    }

    return;
}