/**
 * @file    ipc_protocol.h
 * @brief   Protocolo de comunicación SPI entre las dos placas.
 * @author  Agustin M. Zuliani
 * @date    26/03/26
 * @copyright   Agustin M. Zuliani (c)  2026
 */

#ifndef IPC_PROTOCOL_H_
#define IPC_PROTOCOL_H_

/*=================================[ includes ]=================================*/

#include <stdint.h>

/*============================[ macros and typdedef ]============================*/

#define IPC_MAGIC       0XAF
#define IPC_VERSION     0X01
#define IPC_MAX_PAYLOAD  32

typedef enum __attribute__((packed)) 
{
    CMD_SET_FREQUENCY   = 0x01,
    CMD_SET_WAVEFORM    = 0x02,
    CMD_SET_AMPLITUDE   = 0x03,
    CMD_SET_OFFSET      = 0x04,
    CMD_SET_PHASE       = 0x05,
    CMD_SET_DUTY        = 0x06,   
    CMD_OUTPUT_ENABLE   = 0x07,   
    CMD_SAVE_PRESET     = 0x10,
    CMD_LOAD_PRESET     = 0x11,
    CMD_GET_STATUS      = 0xF0,
    CMD_PING            = 0xF1,
} ipc_cmd_t;

typedef enum __attribute__((packed)) 
{
    IPC_STATUS_OK       = 0X00,
    IPC_STATUS_ERR_CRC  = 0X01,
    IPC_STATUS_ERR_CMD  = 0X02,
    IPC_STATUS_ERR_BUSY = 0X03,
    IPC_STATUS_ERR_HW   = 0X04,
} ipc_status_t;

typedef struct __attribute__((packed))
{
    uint8_t     magic;
    uint8_t     version;
    uint8_t     seq;
    ipc_cmd_t   cmd;
    uint8_t     payload_len;
    uint8_t     payload[IPC_MAX_PAYLOAD];
    uint16_t     crc;
} ipc_packet_t;

typedef struct __attribute__((packed))
{
    uint8_t     magic;
    uint8_t     version;
    uint8_t     seq;
    ipc_cmd_t   cmd;
    uint8_t     payload_len;
    uint8_t     payload[IPC_MAX_PAYLOAD];
    uint16_t     crc;
} ipc_response_t;

#endif