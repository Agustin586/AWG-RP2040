#ifndef PRESET_H_
#define PRESET_H_

#include "signal_config.h"
#include <stdint.h>

#define PRESET_NAME_LEN     16
#define PRESET_MAX_SLOTS    16

typedef struct 
{
    char            name[PRESET_NAME_LEN];
    awg_cfg_t       config;
    uint8_t         crc;
} preset_t;

#endif