/*
 * fsm_uart_communiation.h
 *
 *  Created on: Dec 21, 2023
 *      Author: babyh
 */

#ifndef INC_FSM_UART_COMMUNIATION_H_
#define INC_FSM_UART_COMMUNIATION_H_
#include "global.h"

typedef enum {
    UART_INIT,
    UART_READ,
    UART_SHOW,
} UartState;

void uart_communiation_fsm();


#endif /* INC_FSM_UART_COMMUNIATION_H_ */
