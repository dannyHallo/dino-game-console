/*
 * buttons.c
 *
 *  Created on: 2022年4月26日
 *      Author: DannyHallo
 */

#include "buttons.h"
#include "stm32f4xx_hal.h"

#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOC
#define KEY2_Pin GPIO_PIN_1
#define KEY2_GPIO_Port GPIOC
#define KEY3_Pin GPIO_PIN_2
#define KEY3_GPIO_Port GPIOC
#define KEY4_Pin GPIO_PIN_3
#define KEY4_GPIO_Port GPIOC

#define KEY1_STATE  HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)
#define KEY2_STATE  HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)
#define KEY3_STATE  HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)
#define KEY4_STATE  HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin)

static bool KeyState[4] = { 0, 0, 0, 0 };
static bool KeyPressed[4] = { 0, 0, 0, 0 };
static bool KeyReleased[4] = { 0, 0, 0, 0 };

static uint8_t KeyBuffer[4] = { 0, 0, 0, 0 };
static bool ButtonDownDetectionEnable[4] = { 0, 0, 0, 0 };
static bool ButtonUpDetectionEnable[4] = { 0, 0, 0, 0 };

void KeyScan() {

	KeyBuffer[0] = ((KeyBuffer[0] << 1) | (KEY1_STATE & 0x01));
	KeyBuffer[1] = ((KeyBuffer[1] << 1) | (KEY2_STATE & 0x01));
	KeyBuffer[2] = ((KeyBuffer[2] << 1) | (KEY3_STATE & 0x01));
	KeyBuffer[3] = ((KeyBuffer[3] << 1) | (KEY4_STATE & 0x01));

	for (uint8_t j = 0; j < 4; j++) {
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

