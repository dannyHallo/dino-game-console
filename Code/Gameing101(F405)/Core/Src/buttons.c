/*
 * buttons.c
 *
 *  Created on: 2022年4月26日
 *      Author: DannyHallo
 */

#include "buttons.h"
#include "stm32f4xx_hal.h"

#define KEY1_Pin GPIO_PIN_0
#define KEY2_Pin GPIO_PIN_1
#define KEY3_Pin GPIO_PIN_2
#define KEY4_Pin GPIO_PIN_3

#define KEYS_GPIO_Port GPIOC

const uint8_t KeyPins[4] = { KEY1_Pin, KEY2_Pin, KEY3_Pin, KEY4_Pin };

static uint8_t KeyBuffer[4] = { 0, 0, 0, 0 };
static bool KeyStates[4] = { 0, 0, 0, 0 };
static bool KeysUsedToBeLow[4] = { 0, 0, 0, 0 };

uint8_t LookupKeyState(uint8_t n) {
	if (HAL_GPIO_ReadPin(KEYS_GPIO_Port, KeyPins[n])) {
		return 0xff;
	}
	return 0x00;
}

void KeyScan() {
	for (uint8_t j = 0; j < 4; j++) {
		KeyBuffer[j] = ((KeyBuffer[j] << 1) | (LookupKeyState(j) & 0x01));

		if ((KeyBuffer[j] | 0xf0) == 0xff) {
			KeyStates[j] = 1;
		} else if ((KeyBuffer[j] | 0xf0) == 0xf0) {
			KeyStates[j] = 0;
		}
	}
}

bool GetButton(uint8_t buttonIndex) {
	// To machine index
	buttonIndex--;
	return KeyStates[buttonIndex];
}

bool GetButtonDown(uint8_t buttonIndex) {
	// To machine index
	buttonIndex--;

	if(!KeyStates[buttonIndex]){
		KeysUsedToBeLow[buttonIndex] = true;
	}

	if (KeyStates[buttonIndex] && KeysUsedToBeLow[buttonIndex]) {
		KeysUsedToBeLow[buttonIndex] = false;
		return 1;
	}
	return 0;
}

