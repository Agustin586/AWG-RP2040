#ifndef EVENTS_H_
#define EVENTS_H_

#include <stdint.h>

typedef enum {
    /* encoder */
    EVENT_ENCODER_CW    = 0 ,
    EVENT_ENCODER_CCW       ,
    EVENT_ENCODER_CLICK     ,

    /* botones de cursor */
    EVENT_BTN_LEFT          ,
    EVENT_BTN_RIGHT         ,

    /* botones de parámetro */
    EVENT_BTN_FREQ          ,
    EVENT_BTN_AMPL          ,
    EVENT_BTN_OFFS          ,
    EVENT_BTN_DUTY          ,
    EVENT_BTN_PHAS          ,
    EVENT_BTN_WAVE          ,

    /* botones de canal */
    EVENT_BTN_CH1           ,
    EVENT_BTN_CH2           ,

    /* botones de acción */
    EVENT_BTN_OK            ,
    EVENT_BTN_BACK          ,

    /* input genérico */
    EVENT_INPUT             ,

    /* IPC */
    EVENT_IPC_ACK_OK        ,
    EVENT_IPC_ACK_ERR       ,
    EVENT_IPC_TIMEOUT       ,

    EVENT_COUNT             ,
} fsm_event_id_t;

typedef struct {
    fsm_event_id_t  id;
    int32_t         value;
} fsm_event_msg_t;


#endif