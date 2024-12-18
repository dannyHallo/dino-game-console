/*
 * image.h
 *
 *  Created on: Apr 9, 2022
 *      Author: Administrator
 */

#ifndef INC_IMAGE_H_
#define INC_IMAGE_H_

const uint8_t Test88[1152] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

// 6 x 14
const uint8_t Cloud[84] = { 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00,
		0x0f, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00,
		0x70, 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x00, 0xf0, 0x00, 0x00, 0x00,
		0x40, 0x00, 0x9f, 0x80, 0x00, 0x03, 0xc0, 0x01, 0x00, 0x80, 0x00, 0x06,
		0x00, 0x00, 0x00, 0xf8, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x18, 0x0c, 0x00,
		0x00, 0x00, 0x00, 0x1e, 0x08, 0x00, 0x00, 0x00, 0x00, 0x02, 0x30, 0x40,
		0x00, 0x00, 0x00, 0x01, 0x61, 0xa0, 0x00, 0x00, 0x00, 0x01, 0xcc, 0x3f,
		0xff, 0xff, 0xff, 0xff, };

// 2 x 22
const uint8_t Plant1[44] =
		{ 0x0c, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e, 0xc0, 0x1e, 0xc0, 0x1e,
				0xc0, 0xde, 0xc0, 0xde, 0xc0, 0xde, 0xc0, 0xde, 0xc0, 0xdf,
				0xc0, 0xdf, 0x80, 0xdf, 0x00, 0xfe, 0x00, 0x7e, 0x00, 0x1e,
				0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e,
				0x00, 0x1e, 0x00, };

// 3 x 22
const uint8_t DinoDead[66] = { 0x00, 0x1f, 0xe0, 0x00, 0x37, 0xf0, 0x00, 0x2b,
		0xf0, 0x00, 0x37, 0xf0, 0x00, 0x3f, 0xf0, 0x00, 0x3f, 0xf0, 0x00, 0x3e,
		0x00, 0x00, 0x3f, 0xc0, 0x80, 0x7c, 0x00, 0x81, 0xfc, 0x00, 0xc3, 0xff,
		0x00, 0xe7, 0xfd, 0x00, 0xff, 0xfc, 0x00, 0xff, 0xfc, 0x00, 0x7f, 0xf8,
		0x00, 0x3f, 0xf8, 0x00, 0x1f, 0xf0, 0x00, 0x0f, 0xe0, 0x00, 0x07, 0x60,
		0x00, 0x06, 0x20, 0x00, 0x04, 0x20, 0x00, 0x06, 0x30, 0x00, };

// 3 x 22
const uint8_t DinoNormalRunning[2][66] = {
		{ 0x00, 0x1f, 0xe0, 0x00, 0x3f, 0xf0, 0x00, 0x37, 0xf0, 0x00, 0x3f,
				0xf0, 0x00, 0x3f, 0xf0, 0x00, 0x3f, 0xf0, 0x00, 0x3e, 0x00,
				0x00, 0x3f, 0xc0, 0x80, 0x7c, 0x00, 0x81, 0xfc, 0x00, 0xc3,
				0xff, 0x00, 0xe7, 0xfd, 0x00, 0xff, 0xfc, 0x00, 0xff, 0xfc,
				0x00, 0x7f, 0xf8, 0x00, 0x3f, 0xf8, 0x00, 0x1f, 0xf0, 0x00,
				0x0f, 0xe0, 0x00, 0x06, 0x60, 0x00, 0x03, 0x20, 0x00, 0x00,
				0x20, 0x00, 0x00, 0x30, 0x00, },
		{ 0x00, 0x1f, 0xe0, 0x00, 0x3f, 0xf0, 0x00, 0x37, 0xf0, 0x00, 0x3f,
				0xf0, 0x00, 0x3f, 0xf0, 0x00, 0x3f, 0xf0, 0x00, 0x3e, 0x00,
				0x00, 0x3f, 0xc0, 0x80, 0x7c, 0x00, 0x81, 0xfc, 0x00, 0xc3,
				0xff, 0x00, 0xe7, 0xfd, 0x00, 0xff, 0xfc, 0x00, 0xff, 0xfc,
				0x00, 0x7f, 0xf8, 0x00, 0x3f, 0xf8, 0x00, 0x1f, 0xf0, 0x00,
				0x0f, 0xe0, 0x00, 0x07, 0x30, 0x00, 0x06, 0x00, 0x00, 0x04,
				0x00, 0x00, 0x06, 0x00, 0x00, } };

// 3 x 22
const uint8_t DinoNormalS[66] = { 0x00, 0x1f, 0xe0, 0x00, 0x3f, 0xf0, 0x00,
		0x37, 0xf0, 0x00, 0x3f, 0xf0, 0x00, 0x3f, 0xf0, 0x00, 0x3f, 0xf0, 0x00,
		0x3e, 0x00, 0x00, 0x3f, 0xc0, 0x80, 0x7c, 0x00, 0x81, 0xfc, 0x00, 0xc3,
		0xff, 0x00, 0xe7, 0xfd, 0x00, 0xff, 0xfc, 0x00, 0xff, 0xfc, 0x00, 0x7f,
		0xf8, 0x00, 0x3f, 0xf8, 0x00, 0x1f, 0xf0, 0x00, 0x0f, 0xe0, 0x00, 0x07,
		0x60, 0x00, 0x06, 0x20, 0x00, 0x04, 0x20, 0x00, 0x06, 0x30, 0x00, };

// 3 x 22, 2
const uint8_t DinoFireRunning[2][66] = {
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x03,
				0xff, 0x00, 0x03, 0x7f, 0x00, 0x03, 0xff, 0x00, 0x03, 0xff,
				0x00, 0x03, 0xff, 0x20, 0x0f, 0xe0, 0x60, 0x7f, 0xe0, 0x61,
				0xff, 0xb0, 0xf7, 0xff, 0x8c, 0xff, 0xfe, 0x40, 0xff, 0xfc,
				0xc0, 0x7f, 0xf8, 0x00, 0x2f, 0xf8, 0x00, 0x1f, 0xf0, 0x00,
				0x0f, 0xe0, 0x00, 0x06, 0x60, 0x00, 0x03, 0x20, 0x00, 0x00,
				0x20, 0x00, 0x00, 0x30, 0x00, },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x03,
				0xff, 0x00, 0x03, 0x7f, 0x00, 0x03, 0xff, 0x00, 0x03, 0xff,
				0x00, 0x03, 0xff, 0x20, 0x0f, 0xe0, 0x60, 0x7f, 0xe0, 0x61,
				0xff, 0xb0, 0xf7, 0xff, 0x8c, 0xff, 0xfe, 0x40, 0xff, 0xfc,
				0xc0, 0x7f, 0xf8, 0x00, 0x2f, 0xf8, 0x00, 0x1f, 0xf0, 0x00,
				0x0f, 0xe0, 0x00, 0x07, 0x30, 0x00, 0x06, 0x00, 0x00, 0x04,
				0x00, 0x00, 0x06, 0x00, 0x00, } };

// 3 x 22
const uint8_t DinoFireStand[66] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x01, 0xfe, 0x00, 0x03, 0xff, 0x00, 0x03, 0x7f, 0x00, 0x03, 0xff, 0x00,
		0x03, 0xff, 0x00, 0x03, 0xff, 0x20, 0x0f, 0xe0, 0x60, 0x7f, 0xe0, 0x61,
		0xff, 0xb0, 0xf7, 0xff, 0x8c, 0xff, 0xfe, 0x40, 0xff, 0xfc, 0xc0, 0x7f,
		0xf8, 0x00, 0x2f, 0xf8, 0x00, 0x1f, 0xf0, 0x00, 0x0f, 0xe0, 0x00, 0x07,
		0x60, 0x00, 0x06, 0x20, 0x00, 0x04, 0x20, 0x00, 0x06, 0x30, 0x00, };

// 9 x 25, 2
const uint8_t Fire[2][225] = { { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f,
		0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x98, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x40,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x77, 0x10, 0x02, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x01, 0x8c,
		0x20, 0x04, 0x40, 0x40, 0x00, 0x00, 0x07, 0xfb, 0x10, 0x20, 0x04, 0xe0,
		0x20, 0x00, 0x00, 0x18, 0x0a, 0x20, 0x40, 0x04, 0x20, 0x40, 0x00, 0x00,
		0x20, 0x12, 0x20, 0x40, 0x0c, 0x20, 0x60, 0x00, 0x00, 0xc0, 0x20, 0x20,
		0x40, 0x00, 0x00, 0x19, 0x00, 0x03, 0x00, 0x20, 0x20, 0x00, 0x00, 0x00,
		0x0e, 0x00, 0x1f, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0xe0,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x03, 0x91, 0x10, 0x41, 0x00,
		0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x88, 0x41, 0x01, 0x80, 0x80, 0x08,
		0x00, 0x00, 0xd0, 0xc8, 0x21, 0x01, 0x00, 0xc0, 0x08, 0x00, 0x00, 0x38,
		0x3c, 0x31, 0x86, 0x10, 0x60, 0x48, 0x00, 0x00, 0x07, 0x07, 0xc0, 0xcc,
		0x30, 0x30, 0xc4, 0x08, 0x00, 0x00, 0x00, 0x04, 0x38, 0x21, 0x0f, 0x07,
		0x08, 0x00, 0x00, 0x08, 0x04, 0x00, 0x21, 0x00, 0x02, 0xf8, 0x00, 0x00,
		0x0f, 0x1e, 0x00, 0x20, 0x80, 0x00, 0x07, 0x00, 0x00, 0x00, 0xf1, 0x80,
		0x30, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x10, 0x30, 0x00,
		0x80, }, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x07, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x98, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x3e, 0x18, 0x30, 0x54, 0x00, 0x00, 0x00, 0x03, 0xf0, 0xc3, 0x30,
		0x0e, 0x0c, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x00, 0x23, 0x0c, 0x03, 0x00,
		0x00, 0x00, 0x11, 0xcc, 0x05, 0xc6, 0x04, 0x28, 0x00, 0x00, 0x07, 0xfb,
		0x10, 0x40, 0x88, 0x02, 0x48, 0x00, 0x00, 0x18, 0x04, 0x20, 0x80, 0x00,
		0x00, 0x06, 0x00, 0x00, 0x20, 0x18, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x06, 0x40, 0x30, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0x40,
		0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0c, 0x80, 0x03, 0x06, 0x00,
		0x00, 0x00, 0x00, 0x70, 0x10, 0x80, 0x06, 0x08, 0x00, 0x00, 0x10, 0x01,
		0x9c, 0x20, 0x00, 0x04, 0x08, 0x00, 0x00, 0x10, 0x0e, 0xe0, 0x40, 0x00,
		0x80, 0x08, 0x10, 0x00, 0x20, 0x03, 0x80, 0x00, 0x00, 0x80, 0x08, 0x08,
		0x08, 0x40, 0x08, 0x04, 0x00, 0x20, 0xc0, 0x00, 0x08, 0x08, 0x00, 0x04,
		0xc6, 0x02, 0x20, 0x40, 0x00, 0x04, 0x10, 0x00, 0x03, 0x73, 0x3e, 0x1c,
		0x00, 0x10, 0x03, 0xd0, 0x04, 0x00, 0xe3, 0x87, 0x04, 0x18, 0x30, 0x00,
		0x20, 0x38, 0x00, 0x20, 0x01, 0xc6, 0x18, 0x61, 0x00, 0x04, 0x00, 0x00,
		0x1c, 0x40, 0x35, 0x81, 0xe1, 0x08, 0x02, 0x01, 0x00, 0x03, 0x20, 0x1e,
		0xf0, 0xa0, 0x8c, 0x40, 0x02, 0x00, 0x01, 0x1e, 0x31, 0xc0, 0x30, 0x47,
		0xb9, 0x06, 0x00, 0x00, 0xc3, 0x00, 0x3f, 0x90, 0x30, 0x88, 0x98, } };

// 12 x 96
const uint8_t Title[1152] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x00, 0x00,
		0x03, 0x30, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x00, 0x00,
		0x03, 0x30, 0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x01, 0xe0, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x01, 0xe0, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x67, 0xe0,
		0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x67, 0xe0,
		0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x78, 0x1e, 0x07, 0xe0, 0x1e, 0x78,
		0x3c, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x78, 0x1e, 0x07, 0xe0, 0x1e, 0x78,
		0x3c, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x78, 0x1e, 0x01, 0xe0, 0x1e, 0x78,
		0x3c, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x78, 0x1e, 0x01, 0xe0, 0x1e, 0x78,
		0x3c, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x01, 0xe0, 0x1e, 0x78,
		0x3c, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x01, 0xe0, 0x1e, 0x78,
		0x3c, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x01, 0xe0, 0x1e, 0x78,
		0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x01, 0xe0, 0x1e, 0x78,
		0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff,
		0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xcf, 0xff,
		0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xcf, 0xff,
		0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff,
		0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff,
		0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff,
		0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff,
		0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff,
		0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff,
		0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x00,
		0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x00,
		0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfc,
		0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfc,
		0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x0f, 0xfc, 0x00,
		0x0f, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x0f, 0xfc, 0x00,
		0x0f, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x7f, 0xfc, 0x00,
		0x0f, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x7f, 0xfc, 0x00,
		0x0f, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x03, 0xff, 0xff, 0xc0,
		0x8f, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x03, 0xff, 0xff, 0xc1,
		0xcf, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x0f, 0xff, 0xfc, 0xc1,
		0xcf, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x0f, 0xff, 0xfc, 0xc1,
		0xcf, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0x01,
		0xcf, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0x01,
		0xcf, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0x01,
		0xcf, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0x01,
		0xcf, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xfc, 0x01,
		0xcf, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x01,
		0xcf, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf0, 0x01,
		0xcf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf0, 0x01,
		0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0x00,
		0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0x00,
		0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x00, 0x00,
		0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x00, 0x00,
		0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc3, 0xe0, 0x00,
		0x0f, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xc3, 0xe1, 0xff,
		0xef, 0xbf, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
		0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
		0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0f, 0x00, 0x00,
		0x0f, 0x80, 0x00, 0x00, 0x00, 0x02, 0x30, 0x00, 0xcc, 0x00, 0x00, 0x00,
		0x0f, 0x9e, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
		0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
		0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70,
		0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, };

#endif /* INC_IMAGE_H_ */
