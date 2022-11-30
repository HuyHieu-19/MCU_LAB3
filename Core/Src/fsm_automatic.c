/*
 * fsm_automatic.c
 *
 *  Created on: Nov 24, 2022
 *      Author: Huy Hieu
 */

#include "fsm_automatic.h"

int status = INIT;
int turn = 1; //for horizontal traffic light
int mark_SEG = 1;
int SEG_buffer[4] = {0,0,0,0};
int duration_half = 50;
int duration_1s = 100;

void update_SEG_buffer(int val_1, int val_2)
{
	SEG_buffer[0] = val_1 / 10;
	SEG_buffer[1] = val_1 % 10;
	SEG_buffer[2] = val_2 / 10;
	SEG_buffer[3] = val_2 % 10;
}
void switchSEG(int *mark_SEG, int SEG_buffer[4])
{

	if(*mark_SEG == 1)
	{
		HAL_GPIO_WritePin(GPIOA, EN1_Pin|EN3_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin|EN4_Pin, SET);
		display_both_7SEG(SEG_buffer[0], SEG_buffer[2]);
		*mark_SEG = 2;
	}
	else if(*mark_SEG == 2)
	{
		HAL_GPIO_WritePin(GPIOA, EN1_Pin|EN3_Pin, SET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin|EN4_Pin, RESET);
		display_both_7SEG(SEG_buffer[1], SEG_buffer[3]);
		*mark_SEG = 1;
	}

	setSEGTimer(duration_half);
}
int green_duration = 3;
int yellow_duration = 2;
int red_duration = 5;

int counter_green = 0;
int counter_yellow = 0;
int counter_red = 0;

int count_mode = 0;

void fsm_automatic_run()
{
	switch(status)
	{
		case INIT:
			if(check_button_flag(0) == 1)
			{
				counter_green = green_duration;
				counter_yellow = yellow_duration;
				counter_red = red_duration;

				setTimer(duration_1s);

				HAL_GPIO_WritePin(GPIOA, EN1_Pin|EN2_Pin|EN3_Pin|EN4_Pin, SET);
				status = AUTO_GREEN;
				count_mode++;
			}
			break;

		case AUTO_GREEN:
			update_SEG_buffer(counter_green, count_mode);
			if(seg_flag == 1)
			{
				switchSEG(&mark_SEG, SEG_buffer);
			}

			HAL_GPIO_WritePin(GPIOA, R1_Pin|Y1_Pin|Y2_Pin|G2_Pin, SET);
			HAL_GPIO_WritePin(GPIOA, G1_Pin|R2_Pin, RESET);

			if(timer_flag == 1)
			{
				counter_green--;
				if(counter_green == 0)
				{
					status = AUTO_YELLOW;
					counter_green = green_duration;
				}
				setTimer(duration);
			}
			if(check_button_flag(0) == 1)
			{
				status = MAN_RED;
				HAL_GPIO_WritePin(GPIOA, R1_Pin|Y1_Pin|G1_Pin|R2_Pin|Y2_Pin|G2_Pin, SET);
				setBlink2sTimer(duration/4);
				count_mode++;
			}
			break;

		case AUTO_YELLOW:
			update_SEG_buffer(counter_yellow, count_mode);
			if(seg_flag == 1)
			{
				switchSEG(&mark_SEG, SEG_buffer);
			}
			HAL_GPIO_WritePin(GPIOA, R1_Pin|G1_Pin|Y2_Pin|G2_Pin, SET);
			HAL_GPIO_WritePin(GPIOA, Y1_Pin|R2_Pin, RESET);

			if(timer_flag == 1)
			{
				counter_yellow--;
				if(counter_yellow == 0)
				{
					status = AUTO_RED;
					counter_yellow = yellow_duration;
				}
				setTimer(duration);
			}
			if(check_button_flag(0) == 1)
			{
				status = MAN_RED;
				HAL_GPIO_WritePin(GPIOA, R1_Pin|Y1_Pin|G1_Pin|R2_Pin|Y2_Pin|G2_Pin, SET);
				setBlink2sTimer(duration/4);
				count_mode++;
			}
			break;

		case AUTO_RED:
			update_SEG_buffer(counter_red, count_mode);
			if(seg_flag == 1)
			{
				switchSEG(&mark_SEG, SEG_buffer);
			}
			if(counter_red > yellow_duration) //dieu kien de bat den do
			{
				HAL_GPIO_WritePin(GPIOA, R2_Pin|Y1_Pin|Y2_Pin|G1_Pin, SET);
				HAL_GPIO_WritePin(GPIOA, R1_Pin|G2_Pin, RESET);
			}

			if(timer_flag == 1)
			{
				counter_red--;

				if(counter_red == 0)
				{
					status = AUTO_GREEN;
					counter_red = red_duration;
				}
				else if(counter_red <= yellow_duration)
				{
					HAL_GPIO_WritePin(GPIOA, G2_Pin, SET);
					HAL_GPIO_WritePin(GPIOA, R1_Pin|Y2_Pin, RESET);
				}

				setTimer(duration);
			}
			if(check_button_flag(0) == 1)
			{
				status = MAN_RED;
				HAL_GPIO_WritePin(GPIOA, R1_Pin|Y1_Pin|G1_Pin|R2_Pin|Y2_Pin|G2_Pin, SET);
				setBlink2sTimer(duration/4);
				count_mode++;
			}
			break;
		default:
			break;
	}
}
