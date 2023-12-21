/*
 * fsm_command_parser.c
 *
 *  Created on: Dec 21, 2023
 *      Author: babyh
 */
#include "fsm_command_parser.h"

int ok_flag = 0 ;
int rst_flag = 0;

CommandParserState command_state = CMD_INIT;
uint8_t ok_message[] = "!OK#"; // OK string message
uint8_t rst_message[] = "!RST#"; // RESET string message

uint8_t check_buffer_content(uint8_t *message, uint8_t message_length){
	uint8_t i;
	uint8_t buffer_index = index_buffer - 1;
	for (i = message_length - 2; i > 0; i--) {
	        if (buffer[buffer_index--] != message[i]) {

	            return 0; // Content doesn't match
	        }
	    }
	return 1; // Content matches
}

void command_parser_fsm(){
	switch(command_state){
	case CMD_INIT:
		command_state = CMD_RESET;
		break;
	case CMD_RESET:
		if(check_buffer_content(rst_message, sizeof(rst_message))){//if receive RST from uart
			//set rst flag
			rst_flag = 1;
			command_state = CMD_OK;
		}
		break;
	case CMD_OK:
		if(check_buffer_content(ok_message, sizeof(ok_message))){//if receive OK from uart
			//set okay flag
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			ok_flag = 1;
			command_state = CMD_RESET;
			return;
		}
		if(check_buffer_content(rst_message, sizeof(rst_message))){//if receive RST from uart
			//set rst flag
			rst_flag = 1;
			return;
		}
		break;
	default: break;
	}
}

