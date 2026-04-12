/**
 * @file 	main.c
 * @brief 	Archivo principal
 * @author	Agustin M. Zuliani
 * @date	26/03/26
 * @copyright	Agustin M. Zuliani (c) 2026
 */

/*=================================[ includes ]=================================*/

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <string.h>

#include "msg_app_to_ipc.h"

/*============================[ macros and typedefs ]==========================*/

#define LED0_NODE	DT_ALIAS(led0)

/*===========================[ private declarations ]==========================*/

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

/*=============================[ private functions ]===========================*/

static void led_init(void);
static void led_blink(void);

static void led_init(void)
{
	/* Verificar que el device está listo */
    if (!gpio_is_ready_dt(&led)) {
		LOG_ERR("GPIO device no listo");
        return;
    }

	int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0)
	{
		LOG_ERR("Error al inicializar el led");
	}

	ret = gpio_pin_set_dt(&led, true);
	if (ret < 0)
	{
		LOG_ERR("Error al prender el led");
	}

	return;
}

static void led_blink(void)
{
	static int ret= 0;

	ret = gpio_pin_toggle_dt(&led);
	if (ret < 0)
	{
		LOG_ERR("Error al togglear el led");
	}
}

/*=============================[ public functions ]===========================*/

int main(void)
{
	LOG_DBG("main() iniciado");
	led_init();

    while (1) 
	{
		led_blink();
        k_sleep(K_MSEC(1000));
		// ztest_msg_app_to_ipc();
    }

    return 0;
}
