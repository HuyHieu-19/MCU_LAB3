/*
 * software_timer.h
 *
 *  Created on: Nov 24, 2022
 *      Author: Huy Hieu
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

//extern int red_flag;
//extern int yellow_flag;
//extern int green_flag;
//extern int green_duration;
//extern int yellow_duration;
//extern int red_duration;
//
//void setTimerGreen(int green_duration);
//void setTimerYellow(int yellow_duration);
//void setTimerRed(int red_duration);
extern int timer_flag;
extern int seg_flag;
extern int duration;
extern int seg_duration;
extern int longPressFlag;
extern int blink2s_flag;

void setTimer(int duration);
void timerRun();
void setSEGTimer(int duration);
void setPressTimer(int duration);
void setBlink2sTimer(int duration);

#endif /* INC_SOFTWARE_TIMER_H_ */
