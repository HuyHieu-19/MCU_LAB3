/*
 * fsm_automatic.h
 *
 *  Created on: Nov 24, 2022
 *      Author: Huy Hieu
 */

#include "global.h"
#include "input_reading.h"
#include "fsm_manual.h"

#ifndef INC_FSM_AUTOMATIC_H_
#define INC_FSM_AUTOMATIC_H_

extern int status;
extern int SEG_buffer[4];
extern int mark_SEG;
extern int inMode;
void fsm_automatic_run();
void update_SEG_buffer(int val_1, int val_2);
void switchSEG(int *mark_SEG, int SEG_buffer[4]);

extern int count_mode;
extern int green_duration;
extern int yellow_duration;
extern int red_duration;
extern int counter_red;
extern int counter_yellow;
extern int counter_green;
#endif /* INC_FSM_AUTOMATIC_H_ */
