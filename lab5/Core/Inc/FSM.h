/*
 * FSM.h
 *
 *  Created on: Dec 12, 2024
 *      Author: TIEN DUY
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"
#include "string.h"
#include<stdio.h>
#include "software_timer.h"

#define MAX_BUFFER_SIZE 10

#define START 0
#define R_or_O 1
#define S 2
#define T 3
#define K 4
#define DONE 5
#define END 6
#define SENDING 7
#define STOP_SEND 8

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;

extern uint8_t cmd_flag;
extern int status;
extern uint32_t ADC_Value;

void command_parser_fsm();
void uart_communication_fsm();

#endif /* INC_FSM_H_ */
