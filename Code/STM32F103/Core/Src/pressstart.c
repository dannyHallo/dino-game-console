/*
 * pressstart.c
 *
 *  Created on: 2022年4月25日
 *      Author: DannyHallo
 */

#include "pressstart.h"
#include <string.h>

// # -> lov;  $ -> music; changed U, i
const char CharList[96] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'A', 'V', 'W', 'X',
		'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'A', 'j', 'k', 'l',
		'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '@', 'x', 'x',
		'%', '^', '&', '*', '+', '-', '=', '/', '\\', '_', '(', ')', '{', '}',
		'[', ']', ';', ':', '\'', '\"', ',', '.', '\?', 'A', '~', '|', '#', '$',
		'U', 'i' };

// 8 x 96
const uint8_t PressStartStandard96[768] = { 0x38, 0xfc, 0x3c, 0xf8, 0x7e, 0xfe, 0x3e, 0xc6,
		0x6c, 0xc6, 0x66, 0xcc, 0x60, 0xc0, 0x60, 0xc6, 0xc6, 0xc6, 0xc0, 0xc6,
		0x60, 0xc0, 0xc0, 0xc6, 0xc6, 0xfc, 0xc0, 0xc6, 0x7c, 0xfc, 0xce, 0xfe,
		0xfe, 0xc6, 0xc0, 0xc6, 0x60, 0xc0, 0xc6, 0xc6, 0xc6, 0xc6, 0x66, 0xcc,
		0x60, 0xc0, 0x66, 0xc6, 0xc6, 0xfc, 0x3c, 0xf8, 0x7e, 0xc0, 0x3e, 0xc6,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x06, 0xc6, 0x60,
		0xc6, 0xc6, 0x7c, 0xfc, 0x18, 0x06, 0xcc, 0x60, 0xee, 0xe6, 0xc6, 0xc6,
		0x18, 0x06, 0xd8, 0x60, 0xfe, 0xf6, 0xc6, 0xc6, 0x18, 0x06, 0xf0, 0x60,
		0xfe, 0xfe, 0xc6, 0xc6, 0x18, 0x06, 0xf8, 0x60, 0xd6, 0xde, 0xc6, 0xfc,
		0x18, 0xc6, 0xdc, 0x60, 0xc6, 0xce, 0xc6, 0xc0, 0x7e, 0x7c, 0xce, 0x7e,
		0xc6, 0xc6, 0x7c, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x7c, 0xfc, 0x78, 0x7e, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xcc, 0x18,
		0xc6, 0xc6, 0xc6, 0xee, 0xc6, 0xc6, 0xc0, 0x18, 0xc6, 0xc6, 0xd6, 0x7c,
		0xc6, 0xce, 0x7c, 0x18, 0xc6, 0xee, 0xfe, 0x38, 0xde, 0xf8, 0x06, 0x18,
		0xc6, 0x7c, 0xfe, 0x7c, 0xcc, 0xdc, 0xc6, 0x18, 0xc6, 0x38, 0xee, 0xee,
		0x7a, 0xce, 0x7c, 0x18, 0x7c, 0x10, 0x44, 0xc6, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x66, 0xfe, 0x00, 0x60, 0x00, 0x0c, 0x00, 0x18,
		0x66, 0x0e, 0x00, 0x60, 0x00, 0x0c, 0x00, 0x34, 0x66, 0x1c, 0x3c, 0x60,
		0x38, 0x0c, 0x38, 0x30, 0x3c, 0x38, 0x6c, 0x78, 0x6c, 0x3c, 0x64, 0x78,
		0x18, 0x70, 0x6c, 0x6c, 0x40, 0x6c, 0x7c, 0x30, 0x18, 0xe0, 0x6c, 0x6c,
		0x64, 0x6c, 0x60, 0x30, 0x18, 0xfe, 0x36, 0x78, 0x38, 0x36, 0x38, 0x30,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00,
		0x60, 0x38, 0x00, 0x00, 0x34, 0x60, 0x18, 0x0c, 0x60, 0x18, 0x00, 0x00,
		0x68, 0x60, 0x00, 0x00, 0x64, 0x18, 0xec, 0xb8, 0x78, 0x78, 0x38, 0x0c,
		0x68, 0x18, 0xd6, 0x6c, 0x20, 0x6c, 0x18, 0x0c, 0x70, 0x18, 0xd6, 0x6c,
		0x7c, 0x6c, 0x18, 0x0c, 0x78, 0x18, 0xd6, 0x6c, 0x4c, 0x6c, 0x18, 0x4c,
		0x6c, 0x18, 0xd6, 0x6c, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x30, 0x00, 0x00, 0x38, 0x5c, 0x3a, 0x5c, 0x38, 0x7c, 0x6c, 0x62,
		0x6c, 0x36, 0x6c, 0x3a, 0x60, 0x30, 0x6c, 0x62, 0x6c, 0x36, 0x6c, 0x30,
		0x38, 0x30, 0x6c, 0x36, 0x6c, 0x3c, 0x3c, 0x30, 0x0c, 0x30, 0x6c, 0x3c,
		0x38, 0x30, 0x0c, 0x30, 0x78, 0x18, 0x36, 0x18, 0x00, 0x30, 0x0c, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x18, 0x7c, 0x7e,
		0x00, 0x00, 0x00, 0x00, 0x4c, 0x38, 0xc6, 0x0c, 0xc6, 0x62, 0x62, 0x7e,
		0xc6, 0x18, 0x0e, 0x18, 0xc6, 0x74, 0x34, 0x0c, 0xc6, 0x18, 0x3c, 0x3c,
		0xd6, 0x38, 0x1c, 0x18, 0xc6, 0x18, 0x78, 0x06, 0xd6, 0x1c, 0x08, 0x30,
		0x64, 0x18, 0xe0, 0xc6, 0x6c, 0x6e, 0x10, 0x7e, 0x38, 0x7e, 0xfe, 0x7c,
		0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xfc, 0x3c, 0xfe,
		0x78, 0x7c, 0x0c, 0x3c, 0x3c, 0xc0, 0x60, 0xc6, 0xc4, 0xc6, 0x1c, 0x42,
		0x6c, 0xfc, 0xc0, 0x0c, 0xe4, 0xc6, 0x18, 0x02, 0xcc, 0x06, 0xfc, 0x18,
		0x78, 0x7e, 0x30, 0x72, 0xfe, 0x06, 0xc6, 0x30, 0x9e, 0x06, 0x20, 0x92,
		0x0c, 0xc6, 0xc6, 0x30, 0x86, 0x0c, 0x00, 0x92, 0x0c, 0x7c, 0x7c, 0x30,
		0x7c, 0x78, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x28, 0x10, 0xc0, 0x10, 0x30, 0x00, 0x00, 0x00, 0x28, 0x3c, 0xc8, 0x28,
		0x48, 0x10, 0x10, 0x00, 0x7c, 0x50, 0x10, 0x44, 0x68, 0x54, 0x10, 0x00,
		0x28, 0x38, 0x20, 0x82, 0x70, 0x38, 0x7c, 0x7c, 0x7c, 0x14, 0x40, 0x00,
		0x9a, 0x54, 0x10, 0x00, 0x28, 0x78, 0x98, 0x00, 0x8c, 0x10, 0x10, 0x00,
		0x28, 0x10, 0x18, 0x00, 0x7a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x80, 0x00, 0x18, 0x30, 0x18, 0x30,
		0x00, 0x04, 0x40, 0x00, 0x30, 0x18, 0x30, 0x18, 0x7c, 0x08, 0x20, 0x00,
		0x30, 0x18, 0x30, 0x18, 0x00, 0x10, 0x10, 0x00, 0x30, 0x18, 0xe0, 0x0e,
		0x7c, 0x20, 0x08, 0x00, 0x30, 0x18, 0x30, 0x18, 0x00, 0x40, 0x04, 0x00,
		0x30, 0x18, 0x30, 0x18, 0x00, 0x80, 0x02, 0xfe, 0x18, 0x30, 0x18, 0x30,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x78, 0x00, 0x00,
		0x30, 0x6c, 0x00, 0x00, 0x30, 0x18, 0x30, 0x30, 0x30, 0x6c, 0x00, 0x00,
		0x30, 0x18, 0x30, 0x30, 0x10, 0xd8, 0x00, 0x00, 0x30, 0x18, 0x00, 0x00,
		0x20, 0x00, 0x00, 0x00, 0x30, 0x18, 0x30, 0x30, 0x00, 0x00, 0x30, 0x00,
		0x30, 0x18, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x3c, 0x78, 0x60, 0x00,
		0x00, 0x00, 0x60, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x7c, 0x38, 0x00, 0x10, 0x6c, 0x18, 0x28, 0x00, 0xc6, 0x00, 0x00, 0x10,
		0xfe, 0x14, 0x00, 0x28, 0xc6, 0x38, 0x60, 0x10, 0xfe, 0x12, 0xc6, 0x00,
		0x0c, 0x60, 0x92, 0x00, 0xfe, 0x14, 0xc6, 0x38, 0x38, 0xc6, 0x0c, 0x10,
		0x7c, 0x30, 0xc6, 0x18, 0x00, 0xc6, 0x00, 0x10, 0x38, 0x70, 0xc6, 0x18,
		0x38, 0x7c, 0x00, 0x10, 0x10, 0x20, 0x7c, 0x18, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, };

void FetchText(uint8_t *TextBuf, char chr) {
	uint8_t charSerialNum = -1;

	for (uint8_t i = 0; i < 96; i++) {
		if (chr == CharList[i]) {
			charSerialNum = i;
			break;
		}
	}

	if (charSerialNum == -1) {
		memset(TextBuf, 0x00, 8);
		return;
	}

	uint8_t charLookupX = charSerialNum % 8;
	uint8_t charLookupY = 8 * (charSerialNum / 8);
	uint8_t n = 0;

	for (uint8_t y = charLookupY; y < charLookupY + 8; y++) {
		TextBuf[n] = *((uint8_t*) PressStartStandard96 + y * 8 + charLookupX);
		n++;
	}
}
