/*=================================[ includes ]=================================*/

#include "ipc_master.h"
#include "ipc_parser.h"
#include <zephyr/drivers/spi.h>
#include <zephyr/logging/log.h>
#include "awg_error.h"
#include "spi_ipc.h"

/*===========================[ private declarations ]==========================*/

LOG_MODULE_REGISTER(ipc_master, LOG_LEVEL_DBG);

spi_ipc_t msg = {0};

/*=============================[ private functions ]===========================*/



/*=============================[ public functions ]===========================*/

int ipc_master_init(void)
{
    spi_ipc_init();
    
    return 0;
}

int ipc_master_send(const ipc_packet_t *pkt, ipc_response_t *resp)
{
    int ret = 0;
    uint8_t rx_dummy[sizeof(ipc_packet_t)]      = {0};

    if (pkt == NULL || resp == NULL)    {return -EINVAL;}

    msg.tx_buf  = (uint8_t *)pkt;
    msg.rx_buf  = rx_dummy;
    msg.len     = sizeof(ipc_packet_t);

    /* Transaccion 1 - envia el comando */
    ret = spi_ipc_transfer(&msg);
    if (ret != 0)   {return -EIO;}

    /* Delay de respuesta */
    k_sleep(K_MSEC(2));

    /* Transaccion 2 - recibe respuesta del RP2040 */
    uint8_t tx_dummy[sizeof(ipc_response_t)]    = {0};

    msg.tx_buf  = tx_dummy;
    msg.rx_buf  = (uint8_t *)resp;
    msg.len     = sizeof(ipc_packet_t);

    ret = spi_ipc_transfer(&msg);
    if (ret != 0)   {return -EIO;}

    if (!ipc_response_valid(resp)) {return AWG_ERR_IPC_CRC;}

    return AWG_OK;
}