/*=================================[ includes ]=================================*/

#include "digit.h"

#include <zephyr/logging/log.h>

/*============================[ macros and typedefs ]===========================*/

#define CURSOR_MAX_AMPL 5
#define CURSOR_MAX_OFFS 4
#define CURSOR_MAX_PHAS 3

/*============================[ private declarations ]==========================*/

LOG_MODULE_REGISTER(digit, LOG_LEVEL_DBG);

digit_t digit[DIGIT_CH_COUNT][DIGIT_TYPE_COUNT] = {
    // Canal 1
    {
        {0, 0, DIGIT_COUNT_MAX, CURSOR_MAX     }, // FREQ
        {0, 0, DIGIT_COUNT_MAX, CURSOR_MAX_AMPL}, // AMPL
        {0, 0, DIGIT_COUNT_MAX, CURSOR_MAX_OFFS}, // OFFS
        {0, 0, DIGIT_COUNT_MAX, CURSOR_MAX_PHAS}  // PHAS
    },
    // Canal 2
    {
        {0, 0, DIGIT_COUNT_MAX, CURSOR_MAX     }, // FREQ
        {0, 0, DIGIT_COUNT_MAX, CURSOR_MAX_AMPL}, // AMPL
        {0, 0, DIGIT_COUNT_MAX, CURSOR_MAX_OFFS}, // OFFS
        {0, 0, DIGIT_COUNT_MAX, CURSOR_MAX_PHAS}  // PHAS
    }
};

/*=============================[ private functions ]============================*/

ret_t digit_verf(digit_ch_t channel, digit_type_t type);

ret_t digit_verf(digit_ch_t channel, digit_type_t type)
{
    if (channel > DIGIT_CH_COUNT || channel < DIGIT_SEL_CH1)
    {
        LOG_ERR("Canal invalido");
        return RET_INVALID;
    }

    if (type > DIGIT_TYPE_COUNT || type < DIGIT_TYPE_FREQ)
    {
        LOG_ERR("Tipo de parametro invalido");
        return RET_INVALID;
    }

    return RET_OK;
}

/*=============================[ public functions ]=============================*/

ret_t digit_inc(digit_ch_t channel, digit_type_t type)
{
    ret_t ret = RET_OK;

    ret = digit_verf(channel, type);

    if (ret != RET_OK)
    {
        return ret; 
    }

    if (digit[channel][type].count >= digit[channel][type].max_count)
    {
        return RET_OK;
    }

    digit[channel][type].count += 1;

    return RET_OK;
}

ret_t digit_dec(digit_ch_t channel, digit_type_t type)
{
    ret_t ret = RET_OK;

    ret = digit_verf(channel, type);

    if (ret != RET_OK)
    {
        return ret; 
    }

    if (digit[channel][type].count <= DIGIT_COUNT_MIN)
    {
        return RET_OK;
    }

    digit[channel][type].count -= 1;

    return RET_OK;
}

ret_t digit_move_right(digit_ch_t channel, digit_type_t type)
{
    ret_t ret = RET_OK;

    ret = digit_verf(channel, type);

    if (ret != RET_OK)
    {
        return ret; 
    }

    if (digit[channel][type].cursor <= CURSOR_MIN)
    {
        return RET_OK;
    }

    digit[channel][type].cursor -= 1;

    return RET_OK;
}

ret_t digit_move_left(digit_ch_t channel, digit_type_t type)
{
    ret_t ret = RET_OK;

    ret = digit_verf(channel, type);

    if (ret != RET_OK)
    {
        return ret; 
    }

    if (digit[channel][type].cursor >= digit[channel][type].max_cursor)
    {
        return RET_OK;
    }

    digit[channel][type].cursor += 1;

    return RET_OK;
}

uint8_t digit_get_cursor(digit_ch_t channel, digit_type_t type)
{
    ret_t ret = RET_OK;

    ret = digit_verf(channel, type);

    if (ret != RET_OK)
    {
        return ret; 
    }

    return digit[channel][type].cursor;
}

uint8_t digit_get_count(digit_ch_t channel, digit_type_t type)
{
    ret_t ret = RET_OK;

    ret = digit_verf(channel, type);

    if (ret != RET_OK)
    {
        return ret; 
    }

    return digit[channel][type].count;
}

