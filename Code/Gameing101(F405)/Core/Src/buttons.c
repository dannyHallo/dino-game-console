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

static uint8_t KeysUsedToBeLow[4] = { 0, 0, 0, 0 };
static uint8_t KeysUsedToBeHigh[4] = { 0, 0, 0, 0 };

static uint16_t KeyCounters[4] = { 0, 0, 0, 0 };
static uint16_t KeyCounterOverflowEdge[4] = { 0, 0, 0, 0 };

uint8_t LookupKeyState(uint8_t n) {
	if (HAL_GPIO_ReadPin(KEYS_GPIO_Port, KeyPins[n])) {
		return 0xff;
	}
	return 0x00;
}

void KeyScan() {
	for (uint8_t j = 0; j < 4; j++) {
		KeyBuffer[j] = ((KeyBuffer[j] << 1) | (LookupKeyState(j) & 0x01));

		if (KeyBuffer[j] == 0xff) {
			KeyStates[j] = 1;
		} else if (KeyBuffer[j] == 0x00) {
			KeyStates[j] = 0;
		}
	}
}

void KeyCounterInit(uint8_t buttonIndex, uint16_t overflowEdge) {
	// To machine index
	buttonIndex--;

	KeyCounters[buttonIndex] = 0;
	KeyCounterOverflowEdge[buttonIndex] = overflowEdge;
}

void KeyCounterTick(uint8_t buttonIndex) {
	// To machine index
	buttonIndex--;

	if (KeyCounters[buttonIndex] < KeyCounterOverflowEdge[buttonIndex] - 1) {
		KeyCounters[buttonIndex]++;
	}
}

bool KeyCounterIsTicking(uint8_t buttonIndex) {
	// To machine index
	buttonIndex--;

	if (KeyCounters[buttonIndex] < KeyCounterOverflowEdge[buttonIndex] - 1)
		return true;
	else
		return false;
}

bool GetButton(uint8_t buttonIndex) {
	// To machine index
	buttonIndex--;
	return KeyStates[buttonIndex];
}

bool GetButtonUp(uint8_t buttonIndex, uint8_t identifier) {
	// To machine index
	buttonIndex--;

	if (KeyStates[buttonIndex]) {
		KeysUsedToBeHigh[buttonIndex] = identifier;
	}

	if (!KeyStates[buttonIndex]
			&& KeysUsedToBeHigh[buttonIndex] == identifier) {
		KeysUsedToBeHigh[buttonIndex] = 0;
		return 1;
	}
	return 0;
}

bool GetButtonDown(uint8_t buttonIndex, uint8_t identifier) {
	// To machine index
	buttonIndex--;

	if (!KeyStates[buttonIndex]) {
		KeysUsedToBeLow[buttonIndex] = identifier;
	}

	if (KeyStates[buttonIndex] && KeysUsedToBeLow[buttonIndex] == identifier) {
		KeysUsedToBeLow[buttonIndex] = 0;
		return 1;
	}
	return 0;
}

