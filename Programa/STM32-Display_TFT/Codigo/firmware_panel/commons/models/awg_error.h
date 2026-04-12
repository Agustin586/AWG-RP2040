#ifndef AWG_ERROR_H_
#define AWG_ERROR_H_

#include <errno.h>

typedef enum {
    AWG_OK              =  0,

    /* genéricos */
    AWG_ERR_NULL        = -1,
    AWG_ERR_INVALID     = -2,
    AWG_ERR_TIMEOUT     = -3,
    AWG_ERR_BUSY        = -4,
    AWG_ERR_NOT_READY   = -5,
    AWG_ERR_NOT_FOUND   = -6,

    /* hardware */
    AWG_ERR_HW          = -10,
    AWG_ERR_IO          = -11,

    /* IPC */
    AWG_ERR_IPC_CRC     = -20,
    AWG_ERR_IPC_TIMEOUT = -21,
    AWG_ERR_IPC_VERSION = -22,

    /* storage */
    AWG_ERR_SLOT_EMPTY  = -30,
    AWG_ERR_SLOT_RANGE  = -31,
    AWG_ERR_CRC_FAIL    = -32,

} awg_err_t;

#endif