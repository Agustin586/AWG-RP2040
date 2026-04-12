/**
 * @file    spi_ipc.c
 * @brief   Archivo de transmision y recepcion de SPI mediante IPC
 * @author  Agustin M. Zuliani
 * @date    27/03/26
 * @copyright   Agustin M. Zuliani (c)  2026
 */

/*=================================[ includes ]=================================*/

#include "spi_ipc.h"
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/kernel.h>

/*============================[ macros and typdedef ]============================*/

#define SPI_IPC_NODE    DT_NODELABEL(ipc_bus)
#define SPI_IPC_OP      (SPI_OP_MODE_MASTER | \
                        SPI_WORD_SET(8)     | \
                        SPI_LINES_SINGLE)

/*============================[ private declarations ]===========================*/

LOG_MODULE_REGISTER(IPC_BUS, LOG_LEVEL_DBG);

// static const struct spi_dt_spec spi_ipc = SPI_DT_SPEC_GET(
//     SPI_IPC_NODE,
//     SPI_IPC_OP,
//     0
// );

static const struct device *spi_dev =
    DEVICE_DT_GET(DT_NODELABEL(spi1));

static const struct gpio_dt_spec cs_gpio =
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(spi1), cs_gpios, 0);

static const struct spi_config spi_cfg = {
    .frequency = 1000000,
    .operation = SPI_OP_MODE_MASTER |
                 SPI_WORD_SET(8)    |
                 SPI_LINES_SINGLE,
    .slave     = 0,
    .cs        = {
        .gpio  = GPIO_DT_SPEC_GET_BY_IDX(
                     DT_NODELABEL(spi1), cs_gpios, 0),
        .delay = 0,
    },
};

/*=============================[ private functions ]=============================*/



/*=============================[ public functions ]==============================*/

int spi_ipc_init(void)
{
    // if (!spi_is_ready(&spi_ipc)) {
    //     LOG_ERR("SPI no disponible");
    //     return -ENODEV;
    // }

    // LOG_INF("SPI bus: %s", spi_ipc.bus->name);
    // LOG_INF("CS gpio port: %s pin: %d",
    //         spi_ipc.config.cs.gpio.port->name,
    //         spi_ipc.config.cs.gpio.pin);

    return AWG_OK;
}

int spi_ipc_transfer(spi_ipc_t *msg)
{
    if (msg == NULL)            {return -EINVAL;}
    if (msg->tx_buf == NULL)    {return -EINVAL;}
    if (msg->rx_buf == NULL)    {return -EINVAL;}
    if ((msg->len) == 0)           {return -EINVAL;}

    struct spi_buf tx_buf       = {.buf = (void *) msg->rx_buf, .len = msg->len};
    struct spi_buf rx_buf       = {.buf = (void *) msg->rx_buf, .len = msg->len};
    struct spi_buf_set tx_set   = {.buffers = &tx_buf, .count = 1};
    struct spi_buf_set rx_set   = {.buffers = &rx_buf, .count = 1};

    // int ret = spi_transceive_dt(&spi_ipc, &tx_set, &rx_set);
    int ret = spi_transceive(spi_dev, &spi_cfg, &tx_set, &rx_set);
    if (ret != 0)
    {
        LOG_ERR("spi transceive error: %d", ret);
        return -EIO;
    }

    return AWG_OK;
}