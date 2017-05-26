#ifndef _FC_INIT_H
#define _FC_INIT_H

#include <stdint.h>
#include "stm32f30x.h"
#include "gpio.h"
#include "system.h"

typedef enum {
    SYSTEM_STATE_INITIALISING   = 0,
    SYSTEM_STATE_CONFIG_LOADED  = (1 << 0),
    SYSTEM_STATE_SENSORS_READY  = (1 << 1),
    SYSTEM_STATE_MOTORS_READY   = (1 << 2),
    SYSTEM_STATE_TRANSPONDER_ENABLED = (1 << 3),
    SYSTEM_STATE_READY          = (1 << 7)
} systemState_e;

extern uint8_t systemState;

void init(void);
void checkForBootLoaderRequest(void);
static void UART1_init(u32 bound);
static void mySystemInit(void);

#endif
