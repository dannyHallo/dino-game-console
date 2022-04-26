/*
 * LS013B4DN04.c
 *
 *  Created on: Apr 8, 2022
 *      Author: TinLethax (Thipok Jiamjarapan) (2020)
 *      Minor modifications made by DannyHallo
 *      Original version: https://github.com/TiNredmc/SharpMEMDisp/blob/master/Core/Src/LS027B7DH01.c
 */

#include "LS013B4DN04.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "pressstart.h"

//Display Commands
uint8_t clearCMD[2] = { 0x20, 0x00 }; // Display Clear 0x04 (HW_LSB)
uint8_t printCMD[2] = { 0x80, 0x00 }; // Display Bitmap (after issued display update) 0x01 (HW_LSB)
uint8_t emptyByte = 0x00;

//This buffer holds 50 Bytes * 240 Row = 12K of Display buffer
uint8_t *DispBuf; // Ready-to-use display buffer.
uint8_t *DispBuf2; // Another disp buf for invert cover
uint8_t *TextBuf; // Holds a single text

//This buffer holds temporary 2 Command bytes
static uint8_t SendBuf[2];

//This buffer holds 1 Character bitmap image (8x8)
//static uint8_t chBuf[8];

uint8_t smallRbit(uint8_t re) {
	return (uint8_t) (__RBIT(re) >> 24);
}

int modulo(int x, int N) {
	return (x % N + N) % N;
}

// Display Initialization
void LCD_Init(LS013B4DN04 *MemDisp, SPI_HandleTypeDef *Bus,
		GPIO_TypeDef *dispGPIO, uint16_t LCDcs) {

	//Store params into our struct
	MemDisp->Bus = Bus;
	MemDisp->dispGPIO = dispGPIO;
	MemDisp->LCDcs = LCDcs;

	DispBuf = malloc(1152);
	DispBuf2 = malloc(1152);
	TextBuf = malloc(8);

	memset(DispBuf, 0x00, 1152);
	memset(DispBuf2, 0x00, 1152);
	memset(TextBuf, 0x00, 1152);

	//At lease 3 + 13 clock is needed for Display clear (16 Clock = 8x2 bit = 2 byte)
	HAL_GPIO_WritePin(MemDisp->dispGPIO, MemDisp->LCDcs, GPIO_PIN_SET);
	HAL_SPI_Transmit(MemDisp->Bus, (uint8_t*) clearCMD, 2, 150); //According to data sheet
	HAL_GPIO_WritePin(MemDisp->dispGPIO, MemDisp->LCDcs, GPIO_PIN_RESET);
}

// Display update (Transmit data)
void LCD_Update(LS013B4DN04 *MemDisp) {
	SendBuf[0] |= printCMD[0]; // M0 High, M2 Low
	SendBuf[0] ^= 1 << 6;
	HAL_GPIO_WritePin(MemDisp->dispGPIO, MemDisp->LCDcs, GPIO_PIN_SET); // Begin
	HAL_SPI_Transmit(MemDisp->Bus, SendBuf, 1, 150);

	for (uint8_t row = 0; row < 96; row++) {
		SendBuf[1] = smallRbit(row + 1); // counting from row number 1 to row number 96
		HAL_SPI_Transmit(MemDisp->Bus, SendBuf + 1, 1, 150);

		uint16_t offset = row * 12;
		HAL_SPI_Transmit(MemDisp->Bus, DispBuf + offset, 12, 150);

		HAL_SPI_Transmit(MemDisp->Bus, &emptyByte, 1, 150);
	}

	HAL_SPI_Transmit(MemDisp->Bus, &emptyByte, 1, 150);
	HAL_GPIO_WritePin(MemDisp->dispGPIO, MemDisp->LCDcs, GPIO_PIN_RESET); // Done
}

// Clear entire Display
void LCD_Clean(LS013B4DN04 *MemDisp) {
	//At lease 3 + 13 clock is needed for Display clear (16 Clock = 8x2 bit = 2 byte)
	HAL_GPIO_WritePin(MemDisp->dispGPIO, MemDisp->LCDcs, GPIO_PIN_SET);
	HAL_SPI_Transmit(MemDisp->Bus, (uint8_t*) clearCMD, 2, 150); //According to Datasheet
	HAL_GPIO_WritePin(MemDisp->dispGPIO, MemDisp->LCDcs, GPIO_PIN_RESET);
}

// Load full pic
void LCD_LoadFull(uint8_t *BMP) {
	memcpy(DispBuf, BMP, 1152);
}

void LCD_LoadObjs(GameObj *header, uint8_t drawMode, uint8_t repeatMode,
bool flip) {
	GameObj *ptr = header;

	if (!ptr->full)
		return;

	for (;;) {
		LCD_LoadObj(ptr->bmp, ptr->x, ptr->y, ptr->width, ptr->height, drawMode,
				repeatMode, flip);

		// If looped through all / next buffer is empty
		if (!ptr->next->full || ptr->next == header)
			return;
		ptr = ptr->next;
	}
}

void LCD_LoadObj(uint8_t *bmp, float posX, float posY, uint8_t width,
		uint8_t height, uint8_t drawMode, uint8_t repeatMode, bool flip) {
	short displayRow;
	short displayRowOffset;

	//Counting from Y origin point to bmpH using for loop
	for (uint8_t y = 0; y < height; y++) {
		displayRow = modulo(floor(posY) + y, 96);

		if ((repeatMode == REPEATMODE_NONE)
				&& (displayRow < 0 || displayRow >= 96)) {
			continue;
		}

		displayRowOffset = displayRow * 12;

		int firstXByte = floor(floor(posX) / 8);
		uint8_t leftOffset = modulo(floor(posX), 8);

		uint8_t v1 = 0x00, v2 = 0x00;
		uint8_t *currentEditingBuf;

		for (uint8_t j = 0; j < width + 1; j++) {
			if (j == width)
				v2 = 0x00;
			else
				v2 = *(bmp + width * y + j);

			if (repeatMode == REPEATMODE_NONE
					&& (firstXByte + j < 0 || firstXByte + j > 11)) {
				v1 = v2;
				continue;
			}

			currentEditingBuf = DispBuf + displayRowOffset
					+ (firstXByte + j) % 12;

			if (flip) {
				switch (drawMode) {
				case DRAWMODE_ADD:
					*currentEditingBuf &= ~((v1 << (8 - leftOffset))
							| (v2 >> leftOffset));
					break;
				case DRAWMODE_CULL:
					*currentEditingBuf |= ((v1 << (8 - leftOffset))
							| (v2 >> leftOffset));
					break;
				case DRAWMODE_TOGGLE:
					*currentEditingBuf ^= ((v1 << (8 - leftOffset))
							| (v2 >> leftOffset));
					break;
				}
			} else {
				switch (drawMode) {
				case DRAWMODE_ADD:
					*currentEditingBuf |= ((v1 << (8 - leftOffset))
							| (v2 >> leftOffset));
					break;
				case DRAWMODE_CULL:
					*currentEditingBuf &= ~((v1 << (8 - leftOffset))
							| (v2 >> leftOffset));
					break;
				case DRAWMODE_TOGGLE:
					*currentEditingBuf ^= ((v1 << (8 - leftOffset))
							| (v2 >> leftOffset));
					break;
				}
			}

			v1 = v2;
		}
	}
}

void LCD_DrawLine(uint8_t startingRow, int startingPoint, uint8_t length,
		uint8_t drawMode, bool flip) {
	uint16_t rowOffset = (startingRow % 96) * 12;

	for (uint8_t j = 0; j < length; j++) {
		if (startingPoint + j < 0 || startingPoint + j > 95)
			continue;
		uint8_t additionalOffset = ((startingPoint + j) % 96) / 8;

		uint8_t *currentEditingBuf = DispBuf + rowOffset + additionalOffset;
		if (flip) {
			switch (drawMode) {
			case DRAWMODE_ADD:
				*currentEditingBuf &= ~(0x80 >> ((startingPoint + j) % 8));
				break;
			case DRAWMODE_CULL:
				*currentEditingBuf |= (0x80 >> ((startingPoint + j) % 8));
				break;
			case DRAWMODE_TOGGLE:
				*currentEditingBuf ^= (0x80 >> ((startingPoint + j) % 8));
				break;
			}
		} else {
			switch (drawMode) {
			case DRAWMODE_ADD:
				*currentEditingBuf |= (0x80 >> ((startingPoint + j) % 8));
				break;
			case DRAWMODE_CULL:
				*currentEditingBuf &= ~(0x80 >> ((startingPoint + j) % 8));
				break;
			case DRAWMODE_TOGGLE:
				*currentEditingBuf ^= (0x80 >> ((startingPoint + j) % 8));
				break;
			}
		}

	}
}

// Inverts color, WILL CAUSE PERFORMANCE LOSS
void LCD_Invert(void) {
	uint16_t invt = 1152;
	do {
		invt--;
		DispBuf[invt] = ~DispBuf[invt];
	} while (invt);
}

//Fill screen with either black or white color
void LCD_Fill(bool flip) {
	memset(DispBuf, (flip ? 0xFF : 0x00), 1152);
}

// BAD PERFORMANCE WHEN DRAWING BIGGER CIRCLE
void LCD_DrawCircle(short originX, short originY, uint8_t radius,
		uint8_t drawMode) {
	if (true) {
		memset(DispBuf2, 0x00, 1152);
		uint16_t innerSquareSideHalfLen = floor(radius * 0.707);

		for (uint8_t y = 0; y < 96; y++) {
			uint16_t rowOffset = y * 12;

			bool somePointIsInside = 0;
			for (uint8_t x = 0; x < 96; x++) {

				// Cull points outside of the square
				if (abs(x - originX) > radius || abs(y - originY) > radius)
					continue;

				// If the point is in circle
				if ((abs(x - originX) < innerSquareSideHalfLen
						&& abs(y - originY) < innerSquareSideHalfLen)
						|| (pow(abs(x - originX), 2) + pow(abs(y - originY), 2)
								< pow(radius, 2))) {
					somePointIsInside = 1;
					uint8_t additionalOffset = x / 8;
					uint8_t bitOffset = 7 - x % 8;
					uint8_t *currentEditingBuf = DispBuf2 + rowOffset
							+ additionalOffset;
					*currentEditingBuf |= (0x01 << bitOffset);
					continue;
				}

				// Some points are already inside, but no longer
				if (somePointIsInside)
					break;
			}

		}
		for (uint16_t offset = 0; offset < 12 * 96; offset++) {
			*(DispBuf + offset) |= ~*(DispBuf2 + offset);
		}

	}

}

void LCD_Print(char *str, short xPos, short yPos, uint8_t drawMode,
		uint8_t repeatMode, bool flip) {
	short strLength = strlen(str);
	short lineSpacing = 1;
	short charSpacing = -1;
	short spaceSpacing = 4;
	short tabSpacing = 8 + charSpacing;

	short lineOff = 0;
	short charOff = 0;

	for (short i = 0; i < strLength; i++) {
		if (str[i] == '\n') {
			lineOff += (8 + lineSpacing);
			charOff = 0;
			continue;
		}
		if (str[i] == ' ') {
			charOff += spaceSpacing;
			continue;
		}
		if (str[i] == '\t') {
			charOff += tabSpacing;
			continue;
		}

		FetchText(TextBuf, str[i]);
		LCD_LoadObj(TextBuf, xPos + charOff, yPos + lineOff, 1, 8, drawMode,
				repeatMode, flip);
		charOff += (8 + charSpacing);
	}
}

