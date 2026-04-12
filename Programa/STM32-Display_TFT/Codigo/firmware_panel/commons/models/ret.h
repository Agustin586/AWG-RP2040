#ifndef RET_H_
#define RET_H_

typedef enum {
    RET_OK          =  0,

    /* genéricos */
    RET_NULL        = -1,
    RET_INVALID     = -2,
    RET_TIMEOUT     = -3,
    RET_BUSY        = -4,
    RET_NOT_READY   = -5,
    RET_NOT_FOUND   = -6,

    /* hardware */
    RET_HW_ERR      = -10,
    RET_IO_ERR      = -11,

    /* IPC */
    RET_IPC_CRC     = -20,
    RET_IPC_TIMEOUT = -21,
    RET_IPC_VERSION = -22,

    /* storage */
    RET_SLOT_EMPTY  = -30,
    RET_SLOT_RANGE  = -31,
    RET_CRC_FAIL    = -32,

} ret_t;

#endif /* RET_H_ */