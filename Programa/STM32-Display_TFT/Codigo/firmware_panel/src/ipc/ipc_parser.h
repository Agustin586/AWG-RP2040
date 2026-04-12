/**
 * @file    ipc_parser.h
 * @brief   Se encarga de validar que el paquete es valido
 * @author  Agustin M. Zuliani
 * @date    26/03/26
 * @copyright   Agustin M. Zuliani (c) 2026
 */

#ifndef IPC_PARSER_H_
#define IPC_PARSER_H_

/*=================================[ includes ]=================================*/

#include "ipc_protocol.h"
#include <stdint.h>
#include <stdbool.h>

/*============================[ macros and typdedef ]============================*/

bool ipc_packet_valid(const ipc_packet_t *pkt);
bool ipc_response_valid(ipc_response_t *resp);
uint16_t ipc_crc16(const uint8_t *data, uint16_t len);

#endif