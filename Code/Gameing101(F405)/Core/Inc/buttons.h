/*
 * buttons.h
 *
 *  Created on: 2022年4月26日
 *      Author: DannyHallo
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include <stdbool.h>
#include <stdint.h>

uint8_t LookupKeyState(uint8_t n);

void KeyScan();
bool GetButton(uint8_t buttonIndex);
bool GetButtonDown(uint8_t buttonIndex);

#endif /* INC_BUTTONS_H_ */
