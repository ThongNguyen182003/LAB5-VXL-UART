/*
 * fsm_command_parser.h
 *
 *  Created on: Dec 21, 2023
 *      Author: babyh
 */

#ifndef INC_FSM_COMMAND_PARSER_H_
#define INC_FSM_COMMAND_PARSER_H_
#include "global.h"

typedef enum {
    CMD_INIT,
    CMD_OK,
    CMD_RESET,
} CommandParserState;

extern int ok_flag;
extern int rst_flag;
void command_parser_fsm();

#endif /* INC_FSM_COMMAND_PARSER_H_ */
