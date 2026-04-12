#ifndef DIGIT_H_
#define DIGIT_H_

/*=================================[ includes ]=================================*/

#include <stdint.h>
#include "ret.h"

/*============================[ macros and typedefs ]===========================*/

#define CURSOR_MAX      6   ///< Maximo cursor para el digito
#define CURSOR_MIN      0   ///< Minimo cursor para el digito

#define DIGIT_COUNT_MAX 9   ///< Maximo valor del cursor
#define DIGIT_COUNT_MIN 0   ///< Minimo valor del cursor

typedef enum
{
    DIGIT_SEL_CH1 = 0,
    DIGIT_SEL_CH2    ,
    DIGIT_CH_COUNT   ,
} digit_ch_t;

typedef enum
{
    DIGIT_TYPE_FREQ = 0 ,
    DIGIT_TYPE_AMPL     ,
    DIGIT_TYPE_OFFS     ,
    DIGIT_TYPE_PHAS     ,
    DIGIT_TYPE_DUTY     ,
    DIGIT_TYPE_COUNT    ,
} digit_type_t;

/**
 * @brief   Tipo de dato para manejar el digito de la pantalla
 * @param   cursor  Posicion en la que se encuentra en digito
 * @param   count   Contador del cursos actual
 * @param   type    Tipo de configuracion para el digito
 */
typedef struct 
{
    uint8_t         cursor;
    uint8_t         count;
    uint8_t         max_count;
    uint8_t         max_cursor;
} digit_t;

/*=============================[ public functions ]=============================*/

/**
 * @brief   Incrementa el valor del contador del cursor
 * @param   channel Canal del digito
 * @param   type    Tipo de parametro
 */
ret_t digit_inc(digit_ch_t channel, digit_type_t type);

/**
 * @brief   Incrementa el valor del contador del cursor
 * @param   channel Canal del digito
 * @param   type    Tipo de parametro
 */
ret_t digit_dec(digit_ch_t channel, digit_type_t type);

ret_t digit_move_right(digit_ch_t channel, digit_type_t type);

ret_t digit_move_left(digit_ch_t channel, digit_type_t type);

uint8_t digit_get_cursor(digit_ch_t channel, digit_type_t type);

uint8_t digit_get_count(digit_ch_t channel, digit_type_t type);

#endif  /* DIGIT_H_ */