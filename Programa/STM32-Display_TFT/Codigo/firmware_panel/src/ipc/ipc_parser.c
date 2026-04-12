/*=================================[ includes ]=================================*/

#include "ipc_parser.h"
#include <zephyr/logging/log.h>

/*===========================[ private declarations ]===========================*/

LOG_MODULE_REGISTER(ipc_parser, LOG_LEVEL_DBG);

/*=============================[ public functions ]=============================*/

bool ipc_packet_valid(const ipc_packet_t *pkt)
{
    if (pkt == NULL)                    {return false;}
    if (pkt->magic != IPC_MAGIC)        {return false;}
    if (pkt->version != IPC_VERSION)    {return false;}

    uint16_t crc = ipc_crc16((const uint8_t *)pkt,
                               sizeof(ipc_packet_t) - sizeof(uint16_t));
    if (crc != pkt->crc) {
        LOG_ERR("packet CRC invalid");
        return false;
    }

    return true;
}

bool ipc_response_valid(ipc_response_t *resp)
{
    if (resp == NULL)                   {return false;}
    if (resp->magic != IPC_MAGIC)       {return false;} // Descarta la rta basura
    if (resp->version != IPC_VERSION)   {return false;}

    uint16_t crc = ipc_crc16((const uint8_t *)resp, 
                            sizeof(ipc_response_t) - sizeof(uint16_t));

    if (crc != resp->crc)
    {
        LOG_ERR("response CRC invalid");
        return false;
    }

    return true;
}

uint16_t ipc_crc16(const uint8_t *data, uint16_t len)
{
    uint16_t crc = 0XFFFF;

    for (uint16_t i = 0; i < len; i++)
    {
        crc ^= data[i];
        for (int j = 0; j < 8; j ++)
        {
            if (crc & 0X0001)   {crc = (crc >> 1) ^ 0xA001;}
            else                {crc >>= 1;}
        }
    }

    return crc;
}