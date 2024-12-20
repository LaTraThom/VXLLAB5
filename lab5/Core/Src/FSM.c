/*
 * FSM.c
 *
 *  Created on: Dec 12, 2024
 *      Author: TIEN DUY
 */

#include "FSM.h"
ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart2;

uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;

uint8_t cmd_flag;
uint32_t ADC_Value = 0;

int status = START;

void command_parser_fsm(){
	switch (status) {
	case START:
		if (buffer[index_buffer - 1] == '!') {
			status = R_or_O;
		}
		break;
	case R_or_O:
		if (buffer[index_buffer - 1] == 'R') {
			status = S;
		} else if (buffer[index_buffer - 1] == 'O') {
			status = K;
			} else status = START;
		break;
	case S:
		if (buffer[index_buffer - 1] == 'S') {
			status = T;
		} else status = START;
		break;
	case T:
		if (buffer[index_buffer - 1] == 'T') {
			status = DONE;
		} else status = START;
		break;
	case K:
		if (buffer[index_buffer - 1] == 'K') {
			status = END;
		} else status = START;
		break;
	case DONE:
		if (buffer[index_buffer - 1] == '#') {
			cmd_flag = SENDING;
			status = START;
		}
		break;
	case END:
		if (buffer[index_buffer - 1] == '#') {
			cmd_flag = STOP_SEND;
			status = START;
		}
		break;
	}
}

void uart_communication_fsm() {
	char Str[50];
	if (timer1_flag == 1 && cmd_flag == SENDING) {
			HAL_UART_Transmit(&huart2, (void*)Str, sprintf(Str, "!ADC=%ld#", ADC_Value), 1000);
			setTimer1(500);
	}
}

