/*
 * fsm_uart_communiation.c
 *
 *  Created on: Dec 21, 2023
 *      Author: babyh
 */
#include "fsm_uart_communiation.h"

static uint32_t timeout_start;

void start_timeout(void) {
    timeout_start = HAL_GetTick();
}

uint8_t check_timeout(uint32_t duration) {
    return (HAL_GetTick() - timeout_start >= duration);
}

UartState uart_state = UART_INIT;
uint32_t adc_value = 0;

void uart_communiation_fsm(){
	switch(uart_state){
	case UART_INIT:
		uart_state = UART_READ;
		break;
	case UART_READ:
		if(rst_flag){//if flag indicate read adc is set
			rst_flag = 0 ;
			ok_flag = 0;//reset OK flag
			//TODO
			adc_value = HAL_ADC_GetValue(&hadc1); // read adc


			uint8_t adc_str[20];
			uint16_t size = sprintf(adc_str, "!%d#\r\n", adc_value);
			HAL_UART_Transmit(&huart2, adc_str, size, 1000);
			start_timeout();
			//set timer for print value of adc every 3 second unitl receive OK from uart
			if(check_timeout(3000)){
				uart_state = UART_SHOW;
			} // timeout 3000 ms

		}
		break;
	case UART_SHOW:
		if(ok_flag || rst_flag){
			uart_state = UART_READ;
			return;
		}
		start_timeout();
		if(check_timeout(3000)){
			uart_state = UART_SHOW;
			uint8_t adc_str[20];
			uint16_t size = sprintf(adc_str, "!%d#\r\n", adc_value);
			HAL_UART_Transmit(&huart2, adc_str, size, 1000);
		} // timeout 3000 ms

		break;
	default: break;
	}
}
