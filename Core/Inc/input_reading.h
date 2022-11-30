/*
 * input_reading.h
 *
 *  Created on: Nov 24, 2022
 *      Author: Huy Hieu
 */
#include "main.h"

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#define NO_OF_BUTTONS					3
#define DURATION_FOR_AUTO_INCREASING	300
#define BUTTON_IS_PRESSED				GPIO_PIN_RESET
#define BUTTON_IS_RELEASED				GPIO_PIN_SET

extern	uint8_t flagForButtonPress3s[NO_OF_BUTTONS];
extern	uint16_t counterForButtonPress3s[NO_OF_BUTTONS];

void button_reading(void);
int check_button_flag(int i);
unsigned char is_button_pressed(unsigned char index);
unsigned char is_button_pressed_1s(unsigned char index);

#endif /* INC_INPUT_READING_H_ */
