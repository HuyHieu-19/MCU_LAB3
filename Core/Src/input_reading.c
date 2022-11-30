/*
 * input_reading.c
 *
 *  Created on: Nov 24, 2022
 *      Author: Huy Hieu
 */

#include "input_reading.h"


static	GPIO_PinState buttonBuffer[NO_OF_BUTTONS];

//3 state of button
static	GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static	GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
static	GPIO_PinState debounceButtonBuffer3[NO_OF_BUTTONS];

uint8_t flagForButtonPress3s[NO_OF_BUTTONS];
uint16_t counterForButtonPress3s[NO_OF_BUTTONS];
int button_flag[NO_OF_BUTTONS];

int check_button_flag(int i) {
	if (button_flag[i] == 1) {
		button_flag[i] = 0;
		return 1;
	}
	return 0;
}

void button_reading(void) {
	for (char i=0; i<NO_OF_BUTTONS; i++) {
		debounceButtonBuffer3[i] = debounceButtonBuffer2[i];
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		switch (i) {
			case 0:
				debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin);
				break;
			case 1:
				debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(INC_GPIO_Port, INC_Pin);
				break;
			case 2:
				debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(SET_BUTTON_GPIO_Port, SET_BUTTON_Pin);
				break;
			default:
				break;
		}
		if ((debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) && (debounceButtonBuffer1[i] == debounceButtonBuffer3[i])) {
			if (buttonBuffer[i] == BUTTON_IS_RELEASED && debounceButtonBuffer1[i] == BUTTON_IS_PRESSED) {
				button_flag[i] = 1;  //if previous state = released and current state is pressed
				//=> state of button is pressed
			}
			buttonBuffer[i] = debounceButtonBuffer1[i]; //update previous state button
		}
		if (buttonBuffer[i] == BUTTON_IS_PRESSED) { //case long pressed
			if (counterForButtonPress3s[i] < DURATION_FOR_AUTO_INCREASING) {
				counterForButtonPress3s[i]++;
			} else {
				//case of 1 second
				flagForButtonPress3s[i] = 1;
			}
		} else { //case released
			button_flag[i] = 0;
			counterForButtonPress3s[i] = 0;
			flagForButtonPress3s[i] = 0;
		}
	}
}

unsigned char is_button_pressed(uint8_t index) {
	if (index >= NO_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_pressed_1s(unsigned char index) {
	if (index >= NO_OF_BUTTONS) return 0xff;
	return (flagForButtonPress3s[index] == 1);
}
