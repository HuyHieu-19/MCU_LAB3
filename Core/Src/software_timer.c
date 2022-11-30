/*
 * software_timer.c
 *
 *  Created on: Nov 24, 2022
 *      Author: Huy Hieu
 */


#include "software_timer.h"

int timer_flag = 0;
int timer_counter = 0;
int duration = 100;
int seg_flag = 1;
int seg_duration = 50;
int seg_counter = 0;
int longPressFlag = 0;
int longPressCounter = 0;
int blink2s_flag = 0;
int blink2s_counter = 0;
void setBlink2sTimer(int duration)
{
	blink2s_counter = duration;
	blink2s_flag = 0;
}
void setTimer(int duration)
{
	timer_counter = duration;
	timer_flag = 0;
}
void setSEGTimer(int seg_duration)
{
	seg_counter = seg_duration;
	seg_flag = 0;
}
void setPressTimer(int duration)
{
	longPressFlag = 0;
	longPressCounter = duration;
}
void timerRun()
{
	if(timer_counter > 0)
	{
		timer_counter--;
		if(timer_counter == 0)
		{
			timer_flag = 1;
		}
	}
	if(seg_counter > 0)
	{
		seg_counter--;
		if(seg_counter == 0)
		{
			seg_flag = 1;
		}
	}
	if(longPressCounter > 0)
	{
		longPressCounter--;
		if(longPressCounter == 0)
		{
			longPressFlag = 1;
		}
	}
	if(blink2s_counter > 0)
	{
		blink2s_counter--;
		if(blink2s_counter == 0)
		{
			blink2s_flag = 1;
		}
	}
}
