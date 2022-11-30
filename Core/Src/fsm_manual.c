/*
 * fsm_manual.c
 *
 *  Created on: Nov 25, 2022
 *      Author: Huy Hieu
 */
#include "fsm_manual.h"

int markLongPress = 0;
int markLongINC = 0;

void impl_INC_Button(int *color_duration, int *markLongPress)
{
	if(flagForButtonPress3s[1] == 1 && *markLongPress == 0)
	{
		setPressTimer(duration);
		*markLongPress = 1;
	}
	else if(check_button_flag(1) == 1)
	{
		(*color_duration)++;
		if(*color_duration > 99) *color_duration = 99;
		update_SEG_buffer(*color_duration, count_mode);
		if(seg_flag == 1)
		{
			switchSEG(&mark_SEG, SEG_buffer);
		}
	}

	if(flagForButtonPress3s[1] == 0)
	{
		*markLongPress = 0;
	}

	if(longPressFlag == 1 && flagForButtonPress3s[1] == 1)
	{
		(*color_duration)++;
		if(*color_duration > 99) *color_duration = 99;
		update_SEG_buffer(*color_duration, count_mode);
		if(seg_flag == 1)
		{
			switchSEG(&mark_SEG, SEG_buffer);
		}
		setPressTimer(duration);
	}
}

void impl_MODE_Button(int color, int *markLongPress, int *status, int *count_mode, int *counter_red, int *counter_yellow, int* counter_green)
{
	if(flagForButtonPress3s[0] == 1 && markLongPress == 0)
	{
		setPressTimer(duration);
	}

	if((longPressFlag == 1 && flagForButtonPress3s[0] == 1) || check_button_flag(0) == 1)
	{
		(*status)++;
		if(*status > MAN_GREEN) *status = AUTO_RED;
		(*count_mode)++;
		setPressTimer(duration);
	}

	if(flagForButtonPress3s[0] == 0)
	{
		*markLongPress = 0;
	}

	if(*count_mode == 5)
	{
		if(flagForButtonPress3s[0] == 0 && color == MAN_GREEN)
		{
			*status = AUTO_RED;
			*counter_red = red_duration;
			*counter_yellow = yellow_duration;
			*counter_green = green_duration;
			setTimer(duration);
			setSEGTimer(duration/2);
			//setPressTimer(duration);
		}
		*count_mode = 1;
	}
}

void impl_SET_Button(int color, int value, int count_mode, int *green_duration, int *yellow_duration, int *red_duration)
{
	if(check_button_flag(2) == 1)
	{
		update_SEG_buffer(value, count_mode);
		switchSEG(&mark_SEG, SEG_buffer);
		if(color == MAN_GREEN) *green_duration = value;
		else if(color == MAN_YELLOW) *yellow_duration = value;
		else *red_duration = value;
	}
}
void fsm_manual()
{
	switch(status)
	{
		case MAN_GREEN:
			HAL_GPIO_WritePin(GPIOA, R1_Pin|Y1_Pin|R2_Pin|Y2_Pin, SET);
			if(blink2s_flag == 1)
			{
				HAL_GPIO_TogglePin(GPIOA, G1_Pin|G2_Pin);
				setBlink2sTimer(duration/4);
			}

			update_SEG_buffer(green_duration, count_mode);
			if(seg_flag == 1)
			{
				switchSEG(&mark_SEG, SEG_buffer);
			}
			impl_MODE_Button(MAN_GREEN, &markLongPress, &status, &count_mode, &counter_red, &counter_yellow, &counter_green);
			impl_INC_Button(&green_duration, &markLongINC);
			impl_SET_Button(MAN_GREEN, 12, count_mode, &green_duration, &yellow_duration, &red_duration);

			break;
		case MAN_YELLOW:
			HAL_GPIO_WritePin(GPIOA, G1_Pin|R1_Pin|G2_Pin|R2_Pin, SET);
			if(blink2s_flag == 1)
			{
				HAL_GPIO_TogglePin(GPIOA, Y1_Pin|Y2_Pin);
				setBlink2sTimer(duration/4);
			}

			update_SEG_buffer(yellow_duration, count_mode);
			if(seg_flag == 1)
			{
				switchSEG(&mark_SEG, SEG_buffer);
			}

			impl_MODE_Button(MAN_YELLOW, &markLongPress, &status, &count_mode, &counter_red, &counter_yellow, &counter_green);
			impl_INC_Button(&yellow_duration, &markLongINC);
			impl_SET_Button(MAN_YELLOW, 3, count_mode, &green_duration, &yellow_duration, &red_duration);
			break;
		case MAN_RED:
			HAL_GPIO_WritePin(GPIOA, G1_Pin|Y1_Pin|G2_Pin|Y2_Pin, SET);
			if(blink2s_flag == 1)
			{
				HAL_GPIO_TogglePin(GPIOA, R1_Pin|R2_Pin);
				setBlink2sTimer(duration/4);
			}

			update_SEG_buffer(red_duration, count_mode);
			if(seg_flag == 1)
			{
				switchSEG(&mark_SEG, SEG_buffer);
			}
			impl_MODE_Button(MAN_RED, &markLongPress, &status, &count_mode, &counter_red, &counter_yellow, &counter_green);
			impl_INC_Button(&red_duration, &markLongINC);
			impl_SET_Button(MAN_RED, 15, count_mode, &green_duration, &yellow_duration, &red_duration);
			break;
		default:
			break;
	}
}
