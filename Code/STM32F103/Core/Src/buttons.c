/*
 * buttons.c
 *
 *  Created on: 2022年4月26日
 *      Author: DannyHallo
 */

#include "buttons.h"
#include "stm32f1xx_hal.h"

#define KEY0_Pin GPIO_PIN_0
#define KEY0_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_1
#define KEY1_GPIO_Port GPIOB

#define KEY0_STATE  HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin)
#define KEY1_STATE  HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)

static bool KeyState[2] = { 0, 0 };
static bool KeyPressed[2] = { 0, 0 };
static bool KeyReleased[2] = { 0, 0 };

static uint8_t KeyBuffer[2] = { 0x00, 0x00 };
static bool ButtonDownDetectionEnable[2] = { 0, 0 };
static bool ButtonUpDetectionEnable[2] = { 0, 0 };

void KeyScan() {
	KeyBuffer[0] = ((KeyBuffer[0] << 1) | (KEY0_STATE & 0x01));
	KeyBuffer[1] = ((KeyBuffer[1] << 1) | (KEY1_STATE & 0x01));

	for (uint8_t j = 0; j < 2; j++) {
		if ((KeyBuffer[j] | 0xf0) == 0xff) {
			if (!KeyState[j] && ButtonDownDetectionEnable[j]) {
				KeyPressed[j] = 1;
			}
			KeyState[j] = 1;
		} else if ((KeyBuffer[j] | 0xf0) == 0xf0) {
			if (KeyState[j] && ButtonUpDetectionEnable[j]) {
				KeyReleased[j] = 1;
			}
			KeyState[j] = 0;
		}
	}
}

bool GetButton(uint8_t buttonIndex) {
	return KeyState[buttonIndex];
}

bool GetButtonDown(uint8_t buttonIndex, bool autoRecovery) {
	EnableButtonDownDetection(buttonIndex);
	if (KeyPressed[buttonIndex]) {
		if (autoRecovery)
			KeyPressed[buttonIndex] = 0;
		DisableButtonDownDetection(buttonIndex);
		return 1;
	}
	return 0;
}

bool GetButtonUp(uint8_t buttonIndex, bool autoRecovery) {
	EnableButtonUpDetection(buttonIndex);
	if (KeyReleased[buttonIndex]) {
		if (autoRecovery)
			KeyReleased[buttonIndex] = 0;
		DisableButtonUpDetection(buttonIndex);
		return 1;
	}
	return 0;
}

void EnableButtonDownDetection(uint8_t buttonIndex) {
	ButtonDownDetectionEnable[buttonIndex] = 1;
}

void DisableButtonDownDetection(uint8_t buttonIndex) {
	ButtonDownDetectionEnable[buttonIndex] = 0;
}

void EnableButtonUpDetection(uint8_t buttonIndex) {
	ButtonUpDetectionEnable[buttonIndex] = 1;
}

void DisableButtonUpDetection(uint8_t buttonIndex) {
	ButtonUpDetectionEnable[buttonIndex] = 0;
}

