/*
 * image.h
 *
 *  Created on: Apr 9, 2022
 *      Author: Administrator
 */

#ifndef INC_IMAGE_H_
#define INC_IMAGE_H_

#include <stdint.h>

const uint8_t Test88[1152] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

#define CloudNormal 0
// 6 x 14
const uint8_t CloudAssets[84] = { 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00,
		0x00, 0x0f, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x00,
		0x00, 0x70, 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x00, 0xf0, 0x00, 0x00,
		0x00, 0x40, 0x00, 0x9f, 0x80, 0x00, 0x03, 0xc0, 0x01, 0x00, 0x80, 0x00,
		0x06, 0x00, 0x00, 0x00, 0xf8, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x18, 0x0c,
		0x00, 0x00, 0x00, 0x00, 0x1e, 0x08, 0x00, 0x00, 0x00, 0x00, 0x02, 0x30,
		0x40, 0x00, 0x00, 0x00, 0x01, 0x61, 0xa0, 0x00, 0x00, 0x00, 0x01, 0xcc,
		0x3f, 0xff, 0xff, 0xff, 0xff, };

#define PlantNormal 0
// 2 x 22
const uint8_t PlantAssets[5][44] = { { 0x0c, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e,
		0xc0, 0x1e, 0xc0, 0x1e, 0xc0, 0xde, 0xc0, 0xde, 0xc0, 0xde, 0xc0, 0xde,
		0xc0, 0xdf, 0xc0, 0xdf, 0x80, 0xdf, 0x00, 0xfe, 0x00, 0x7e, 0x00, 0x1e,
		0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e,
		0x00, }, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00,
		0x8f, 0x40, 0xde, 0xc0, 0x9e, 0xc0, 0x1f, 0xc0, 0x5f, 0x80, 0xdf, 0x00,
		0xfe, 0x00, 0x7e, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e, 0x00, }, { 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x3c, 0x80, 0x38,
		0x80, 0x39, 0x80, 0x3c, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x5f, 0xc0, 0xff,
		0x80, 0xff, 0x80, 0xff, 0x00, 0x7f, 0x00, }, { 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x46, 0x00, 0x1f, 0x80, 0x7f, 0x80, 0xfe, 0x00,
		0xfc, 0x00, 0x7e, 0x00, }, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x4f,
		0x00, } };

#define DinoNormalStand 0
#define DinoNormalL 1
#define DinoNormalR 2
#define DinoNormalDead 3
#define DinoFiringStand 4
#define DinoFiringL 5
#define DinoFiringR 6
#define DinoFiringDead 7
#define DinoDodgingStand 8
#define DinoDodgingL 9
#define DinoDodgingR 10
#define DinoDodgingDead 11
#define DinoGliding 12
#define DinoGlidingDead 13

#define DinoXPosDefault 4
#define DinoXPosWhenDodging 2
#define DinoXPosWhenGliding 1
// 4 x 22
const uint8_t DinoAssets[14][88] = { { 0x00, 0x01, 0xfe, 0x00, 0x00, 0x03, 0xff,
		0x00, 0x00, 0x03, 0x7f, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x03, 0xff,
		0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x03, 0xfc,
		0x00, 0x08, 0x07, 0xc0, 0x00, 0x08, 0x1f, 0xc0, 0x00, 0x0c, 0x3f, 0xf0,
		0x00, 0x0e, 0x7f, 0xd0, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x0f, 0xff, 0xc0,
		0x00, 0x07, 0xff, 0x80, 0x00, 0x03, 0xff, 0x80, 0x00, 0x01, 0xff, 0x00,
		0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x62, 0x00,
		0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, }, { 0x00, 0x01,
		0xfe, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x03, 0x7f, 0x00, 0x00, 0x03,
		0xff, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x03,
		0xe0, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x08, 0x07, 0xc0, 0x00, 0x08, 0x1f,
		0xc0, 0x00, 0x0c, 0x3f, 0xf0, 0x00, 0x0e, 0x7f, 0xd0, 0x00, 0x0f, 0xff,
		0xc0, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x07, 0xff, 0x80, 0x00, 0x03, 0xff,
		0x80, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x66,
		0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03,
		0x00, 0x00, }, { 0x00, 0x01, 0xfe, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00,
		0x03, 0x7f, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00,
		0x03, 0xff, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x08,
		0x07, 0xc0, 0x00, 0x08, 0x1f, 0xc0, 0x00, 0x0c, 0x3f, 0xf0, 0x00, 0x0e,
		0x7f, 0xd0, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x07,
		0xff, 0x80, 0x00, 0x03, 0xff, 0x80, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00,
		0xfe, 0x00, 0x00, 0x00, 0x73, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
		0x40, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, },
		{ 0x00, 0x01, 0xfe, 0x00, 0x00, 0x03, 0x7f, 0x00, 0x00, 0x02, 0xbf,
				0x00, 0x00, 0x03, 0x7f, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00,
				0x03, 0xff, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x03, 0xfc,
				0x00, 0x08, 0x07, 0xc0, 0x00, 0x08, 0x1f, 0xc0, 0x00, 0x0c,
				0x3f, 0xf0, 0x00, 0x0e, 0x7f, 0xd0, 0x00, 0x0f, 0xff, 0xc0,
				0x00, 0x0f, 0xff, 0xc0, 0x00, 0x07, 0xff, 0x80, 0x00, 0x03,
				0xff, 0x80, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0xfe, 0x00,
				0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00,
				0x42, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, }, { 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00,
				0x00, 0x3f, 0xf0, 0x00, 0x00, 0x37, 0xf0, 0x00, 0x00, 0x3f,
				0xf0, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x3f, 0xf0, 0x02,
				0x00, 0xfe, 0x00, 0x06, 0x07, 0xfe, 0x00, 0x06, 0x1f, 0xfb,
				0x00, 0x0f, 0x7f, 0xf8, 0xc0, 0x0f, 0xff, 0xe4, 0x00, 0x0f,
				0xff, 0xcc, 0x00, 0x07, 0xff, 0x80, 0x00, 0x03, 0xff, 0x80,
				0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00,
				0x76, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x42, 0x00,
				0x00, 0x00, 0x63, 0x00, 0x00, }, { 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x3f,
				0xf0, 0x00, 0x00, 0x37, 0xf0, 0x00, 0x00, 0x3f, 0xf0, 0x00,
				0x00, 0x3f, 0xf0, 0x00, 0x00, 0x3f, 0xf0, 0x02, 0x00, 0xfe,
				0x00, 0x06, 0x07, 0xfe, 0x00, 0x06, 0x1f, 0xfb, 0x00, 0x0f,
				0x7f, 0xf8, 0xc0, 0x0f, 0xff, 0xe4, 0x00, 0x0f, 0xff, 0xcc,
				0x00, 0x07, 0xff, 0x80, 0x00, 0x03, 0xff, 0x80, 0x00, 0x01,
				0xff, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x66, 0x00,
				0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
				0x03, 0x00, 0x00, },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
				0xe0, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x37, 0xf0, 0x00,
				0x00, 0x3f, 0xf0, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x3f,
				0xf0, 0x02, 0x00, 0xfe, 0x00, 0x06, 0x07, 0xfe, 0x00, 0x06,
				0x1f, 0xfb, 0x00, 0x0f, 0x7f, 0xf8, 0xc0, 0x0f, 0xff, 0xe4,
				0x00, 0x0f, 0xff, 0xcc, 0x00, 0x07, 0xff, 0x80, 0x00, 0x03,
				0xff, 0x80, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0xfe, 0x00,
				0x00, 0x00, 0x73, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
				0x40, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, }, { 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00,
				0x00, 0x37, 0xf0, 0x00, 0x00, 0x2b, 0xf0, 0x00, 0x00, 0x37,
				0xf0, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x3f, 0xf0, 0x02,
				0x00, 0xfe, 0x00, 0x06, 0x07, 0xfe, 0x00, 0x06, 0x1f, 0xfb,
				0x00, 0x0f, 0x7f, 0xf8, 0xc0, 0x0f, 0xff, 0xe4, 0x00, 0x0f,
				0xff, 0xcc, 0x00, 0x07, 0xff, 0x80, 0x00, 0x03, 0xff, 0x80,
				0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00,
				0x76, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x42, 0x00,
				0x00, 0x00, 0x63, 0x00, 0x00, }, { 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x03, 0xfc, 0x3c,
				0x7f, 0xc7, 0xfe, 0x1f, 0xff, 0xfe, 0xfe, 0x0f, 0xff, 0xff,
				0xfe, 0x07, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xfe, 0x01,
				0xff, 0xff, 0xc0, 0x00, 0xff, 0xe7, 0xf8, 0x00, 0x76, 0x40,
				0x00, 0x00, 0x64, 0x20, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00,
				0x60, 0x00, 0x00, },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
				0x00, 0x03, 0xfc, 0x3c, 0x7f, 0xc7, 0xfe, 0x1f, 0xff, 0xfe,
				0xfe, 0x0f, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xfe, 0x03,
				0xff, 0xff, 0xfe, 0x01, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xe7,
				0xf8, 0x00, 0x46, 0x40, 0x00, 0x00, 0x64, 0x20, 0x00, 0x00,
				0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }, { 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x03,
				0xfc, 0x3c, 0x7f, 0xc7, 0xfe, 0x1f, 0xff, 0xfe, 0xfe, 0x0f,
				0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff,
				0xfe, 0x01, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xe7, 0xf8, 0x00,
				0x74, 0x40, 0x00, 0x00, 0x62, 0x20, 0x00, 0x00, 0x40, 0x00,
				0x00, 0x00, 0x60, 0x00, 0x00, }, { 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x03, 0xfc, 0x3c,
				0x7f, 0xc6, 0xfe, 0x1f, 0xff, 0xfd, 0x7e, 0x0f, 0xff, 0xfe,
				0xfe, 0x07, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xfe, 0x01,
				0xff, 0xff, 0xc0, 0x00, 0xff, 0xe7, 0xf8, 0x00, 0x76, 0x40,
				0x00, 0x00, 0x64, 0x20, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00,
				0x60, 0x00, 0x00, },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
				0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00,
				0x03, 0xe3, 0xfc, 0x00, 0x7f, 0xe7, 0xfe, 0x1f, 0xff, 0xfe,
				0xfe, 0x7f, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xfe, 0x03,
				0xff, 0xff, 0xfe, 0x01, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xe7,
				0xf8, 0x00, 0x72, 0x20, 0x00, 0x03, 0xc4, 0x40, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }, { 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0xfc, 0x00,
				0x0f, 0x80, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x03, 0xe3,
				0xfc, 0x00, 0x7f, 0xe6, 0xfe, 0x1f, 0xff, 0xfd, 0x7e, 0x7f,
				0xff, 0xfe, 0xfe, 0x07, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff,
				0xfe, 0x01, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xe7, 0xf8, 0x00,
				0x72, 0x20, 0x00, 0x03, 0xc4, 0x40, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, } };

// 9 x 25
const uint8_t FireAssets[2][225] = { { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x80,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x7f, 0x3b, 0x80, 0x00,
		0x00, 0x00, 0x00, 0x77, 0x10, 0x42, 0xc8, 0xc0, 0x00, 0x00, 0x00, 0x01,
		0x8c, 0x20, 0x04, 0x40, 0x30, 0x00, 0x00, 0x07, 0xfb, 0x10, 0x20, 0x04,
		0xe0, 0x08, 0x00, 0x00, 0x18, 0x0a, 0x20, 0x40, 0x04, 0x20, 0x04, 0x00,
		0x00, 0x20, 0x12, 0x20, 0x40, 0x0c, 0x20, 0x04, 0x00, 0x00, 0xc0, 0x20,
		0x20, 0x40, 0x00, 0x00, 0x04, 0x00, 0x03, 0x00, 0x20, 0x20, 0x00, 0x00,
		0x01, 0xe2, 0x00, 0x1f, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x00,
		0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x09, 0x03, 0x91, 0x10, 0x41,
		0x00, 0x00, 0x80, 0x00, 0x09, 0x00, 0x01, 0x88, 0x41, 0x01, 0x80, 0x80,
		0x08, 0x05, 0x00, 0xd0, 0xc8, 0x21, 0x01, 0x00, 0xc0, 0x08, 0x05, 0x00,
		0x38, 0x3c, 0x31, 0x86, 0x10, 0x60, 0x48, 0x09, 0x00, 0x07, 0x07, 0xc0,
		0xcc, 0x30, 0x30, 0xc4, 0x19, 0x00, 0x00, 0x00, 0x04, 0x38, 0x21, 0x0f,
		0x03, 0x03, 0x00, 0x00, 0x08, 0x04, 0x00, 0x21, 0x00, 0x00, 0xc2, 0x00,
		0x00, 0x0f, 0x1e, 0x00, 0x20, 0x80, 0x20, 0x04, 0x00, 0x00, 0x00, 0xf1,
		0x80, 0x30, 0x40, 0x30, 0x08, 0x00, 0x00, 0x00, 0x00, 0x60, 0x10, 0x30,
		0x18, 0x30, },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x3e, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x03,
				0xf0, 0xc3, 0x33, 0x8e, 0xe0, 0x00, 0x00, 0x00, 0x0c, 0x03,
				0x00, 0x23, 0x0c, 0x10, 0x00, 0x00, 0x00, 0x11, 0xcc, 0x05,
				0xc6, 0x04, 0x10, 0x00, 0x00, 0x07, 0xfb, 0x10, 0x40, 0x88,
				0x02, 0x58, 0x00, 0x00, 0x18, 0x04, 0x20, 0x80, 0x00, 0x00,
				0x02, 0x00, 0x00, 0x20, 0x18, 0x41, 0x00, 0x00, 0x03, 0xc3,
				0x00, 0x06, 0x40, 0x30, 0xe0, 0x00, 0x00, 0x00, 0x61, 0x00,
				0x08, 0x04, 0x40, 0x80, 0x00, 0x00, 0x00, 0x21, 0x00, 0x12,
				0x0c, 0x80, 0x03, 0x06, 0x00, 0x00, 0x01, 0x00, 0x7c, 0x10,
				0x80, 0x06, 0x08, 0x00, 0x00, 0x00, 0x01, 0xd0, 0x20, 0x00,
				0x04, 0x08, 0x00, 0x00, 0x04, 0x0e, 0x00, 0x40, 0x00, 0x80,
				0x08, 0x10, 0x00, 0x0c, 0x02, 0x00, 0x00, 0x00, 0x80, 0x08,
				0x08, 0x08, 0x18, 0x08, 0x04, 0x00, 0x20, 0xc0, 0x00, 0x08,
				0x08, 0x01, 0x04, 0xc6, 0x02, 0x20, 0x40, 0x20, 0x04, 0x10,
				0x02, 0x03, 0x73, 0x3e, 0x1c, 0x00, 0xc0, 0x03, 0xd8, 0x0a,
				0x00, 0xe3, 0x87, 0x04, 0x19, 0x80, 0x00, 0x28, 0x3e, 0x00,
				0x20, 0x01, 0xc6, 0x19, 0x00, 0x00, 0x06, 0xe8, 0x00, 0x1c,
				0x40, 0x31, 0x81, 0x00, 0x08, 0x03, 0x88, 0x00, 0x03, 0x20,
				0x18, 0xf1, 0x00, 0x0c, 0x40, 0x18, 0x00, 0x01, 0x1e, 0x38,
				0xc0, 0x82, 0x07, 0xb8, 0x30, 0x00, 0x00, 0xc3, 0x04, 0x30,
				0xc3, 0x1c, 0x8f, 0x80, } };

#define Bump 0
#define Depression 1
// 1 x 2
const uint8_t BumpAndDepressionAssets[2][2] =
		{ { 0x3c, 0xe7, }, { 0xe7, 0x3c, } };

// 1 x 1
const uint8_t DirtTextureAssets[6][1] = { { 0x80, }, { 0xc0, }, { 0xe0, }, {
		0xf0, }, { 0xf8, }, { 0xfc, } };

// 9 x 6
const uint8_t LavaAssets[4][54] = { { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0x00, 0x40,
		0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x09, 0xe0, 0x03, 0x00,
		0x0f, 0xc0, 0x00, 0x00, 0x80, 0x1b, 0xfe, 0x47, 0xfb, 0xff, 0xf8, 0xf2,
		0xf9, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, }, {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
		0x00, 0x80, 0x10, 0x00, 0x00, 0x00, 0x08, 0x02, 0x00, 0x00, 0x00, 0x40,
		0x00, 0x00, 0x00, 0x04, 0x02, 0x1e, 0x03, 0x71, 0xc0, 0x18, 0x00, 0xc0,
		0x0e, 0x16, 0xff, 0x07, 0xff, 0xdf, 0x3f, 0x67, 0xde, 0xdf, 0x3f, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, }, { 0x00, 0x00, 0x00, 0x00, 0x20,
		0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x01, 0xd0,
		0x02, 0x38, 0x10, 0x20, 0x03, 0x04, 0x00, 0x0f, 0xfe, 0x43, 0xff, 0x1b,
		0x9e, 0x3f, 0xcf, 0x72, 0x3f, 0xff, 0xe7, 0xff, 0xbf, 0xff, 0xff, 0xff,
		0xff, }, { 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x20,
		0x00, 0x00, 0x80, 0x00, 0x20, 0x40, 0x00, 0x00, 0x18, 0x00, 0x10, 0x00,
		0x00, 0x10, 0x00, 0x00, 0x00, 0x5d, 0x00, 0x3e, 0x00, 0x10, 0x80, 0xc0,
		0x0f, 0x80, 0x0f, 0xf0, 0x7f, 0xde, 0x1f, 0xa7, 0xd0, 0xff, 0xd2, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, } };

// 3 x 20
const uint8_t BirdAssets[2][60] = { { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x3e,
		0x00, 0x00, 0x7e, 0x00, 0x00, 0xfe, 0x00, 0x00, 0xff, 0xff, 0x00, 0x03,
		0xff, 0x80, 0x01, 0xff, 0xfe, 0x00, 0xff, 0xe0, 0x00, 0xff, 0xc0, 0x00,
		0xff, 0xf8, 0x00, 0xff, 0x80, 0x00, 0xf0, 0x00, 0x00, 0xe0, 0x00, 0x00,
		0xe0, 0x00, 0x00, 0x40, 0x00, }, { 0x01, 0x00, 0x00, 0x01, 0x80, 0x00,
		0x01, 0xc0, 0x00, 0x00, 0xe0, 0x00, 0x0c, 0xf0, 0x00, 0x1e, 0xf8, 0x00,
		0x3e, 0xfc, 0x00, 0x7e, 0xfe, 0x00, 0xfe, 0xff, 0x00, 0xff, 0xff, 0x00,
		0x03, 0xff, 0x80, 0x01, 0xff, 0xfe, 0x00, 0xff, 0xe0, 0x00, 0x7f, 0xc0,
		0x00, 0x3f, 0xf8, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, } };

#endif /* INC_IMAGE_H_ */
