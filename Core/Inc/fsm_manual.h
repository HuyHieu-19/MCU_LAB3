/*
 * fsm_manual.h
 *
 *  Created on: Nov 25, 2022
 *      Author: Huy Hieu
 */

#ifndef INC_FSM_MANUAL_H_
#define INC_FSM_MANUAL_H_

#include "fsm_automatic.h"

void fsm_manual();
void impl_INC_Button(int *color_duration, int *markLongPress);
void impl_MODE_Button(int color, int *markLongPress, int *status, int *count_mode, int *counter_red, int *counter_yellow, int* counter_green);
void impl_SET_Button(int color, int value, int count_mode, int *green_duration, int *yellow_duration, int *red_duration);
extern int markLongPress;
extern int markLongINC;

#endif /* INC_FSM_MANUAL_H_ */
