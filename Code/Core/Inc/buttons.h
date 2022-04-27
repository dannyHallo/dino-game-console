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

void KeyScan();
bool GetButton(uint8_t buttonIndex);
bool GetButtonDown(uint8_t buttonIndex, bool autoRecovery);
bool GetButtonUp(uint8_t buttonIndex, bool autoRecovery);
void EnableButtonDownDetection(uint8_t buttonIndex);
void DisableButtonDownDetection(uint8_t buttonIndex);
void EnableButtonUpDetection(uint8_t buttonIndex);
void DisableButtonUpDetection(uint8_t buttonIndex);

#endif /* INC_BUTTONS_H_ */
