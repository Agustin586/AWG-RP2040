/**
 * @file    spi_ipc.h
 * @brief   Archivo de transmision y recepcion de SPI mediante IPC
 * @author  Agustin M. Zuliani
 * @date    27/03/26
 * @copyright   Agustin M. Zuliani (c)  2026
 */

#ifndef SPI_IPC_H_
#define SPI_IPC_H_

/*=================================[ includes ]=================================*/

#include "awg_error.h"
#include <stdint.h>

/*============================[ macros and typdedef ]============================*/

typedef struct 
{
    uint8_t  *tx_buf;
    uint8_t  *rx_buf;
    uint16_t len;
} spi_ipc_t;

/*=============================[ public functions ]==============================*/

/**
 * @brief   Inicializacion del SPI mediante el protocolo IPC
 *          definido entre ambas placas de comunicacion
 * @return  0 si no hubo error y valor negativo si hubo algun error
 *          presente
 */
int spi_ipc_init(void);

/**
 * @brief   Transferencia de informacion desde una placa a otra
 *          mediante SPI
 * @param   msg     Puntero a dispositivo
 * @return  0 si no hubo y valor negativo si hubo algun error
 *          presente
 */
int spi_ipc_transfer(spi_ipc_t *msg);

#endif