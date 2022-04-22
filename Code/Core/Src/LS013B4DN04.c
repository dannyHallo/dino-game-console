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

//Display Commands
uint8_t clearCMD[2] = { 0x20, 0x00 }; // Display Clear 0x04 (HW_LSB)
uint8_t printCMD[2] = { 0x80, 0x00 }; // Display Bitmap (after issued display update) 0x01 (HW_LSB)
uint8_t emptyByte = 0x00;

//This buffer holds 50 Bytes * 240 Row = 12K of Display buffer
uint8_t *DispBuf; // entire display buffer.
uint8_t *DispBuf2;

//This buffer holds temporary 2 Command bytes
static uint8_t SendBuf[2];

//This buffer holds 1 Character bitmap image (8x8)
//static uint8_t chBuf[8];

//These variables required for print function
static uint8_t YLine = 1;
static uint8_t Xcol = 1;

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

	memset(DispBuf, 0x00, 1152);
	memset(DispBuf2, 0x00, 1152);

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
	YLine = 1;
	Xcol = 1;
	//At lease 3 + 13 clock is needed for Display clear (16 Clock = 8x2 bit = 2 byte)
	HAL_GPIO_WritePin(MemDisp->dispGPIO, MemDisp->LCDcs, GPIO_PIN_SET);
	HAL_SPI_Transmit(MemDisp->Bus, (uint8_t*) clearCMD, 2, 150); //According to Datasheet
	HAL_GPIO_WritePin(MemDisp->dispGPIO, MemDisp->LCDcs, GPIO_PIN_RESET);

}

// Buffer update (full 400*240 pixels)
void LCD_LoadFull(uint8_t *BMP) {
	/*for(uint16_t l; l < 1152; l++){
	 DispBuf[l] = (uint8_t)(__RBIT(BMP[l]) >> 24);
	 }*/
	memcpy(DispBuf, BMP, 1152);
}

// Buffer update (with X,Y Coordinate and image WxH) X,Y Coordinate start at (0,0) to (12,96)
void LCD_LoadPart(uint8_t *BMP, int Xcord, uint8_t Ycord, uint8_t bmpW,
		uint8_t bmpH, uint8_t drawMode, uint8_t repeatMode) {

	short displayRow;
	short displayRowOffset;

	//Counting from Y origin point to bmpH using for loop
	for (uint8_t y = 0; y < bmpH; y++) {
		displayRow = modulo(Ycord + y, 96);

		if ((repeatMode == REPEATMODE_NONE)
				&& (displayRow < 0 || displayRow >= 96)) {
			continue;
		}

		displayRowOffset = displayRow * 12;

		int firstXByte = floor((float) Xcord / 8);
		uint8_t leftOffset = modulo(Xcord, 8);

		uint8_t v1, v2 = 0x00;
		uint8_t *currentEditingBuf;

		for (uint8_t j = 0; j < bmpW + 1; j++) {
			if (j == bmpW)
				v2 = 0x00;
			else
				v2 = *(BMP + bmpW * y + j);

			if (repeatMode == REPEATMODE_NONE
					&& (firstXByte + j < 0 || firstXByte + j > 11)) {
				v1 = v2;
				continue;
			}

			currentEditingBuf = DispBuf + displayRowOffset
					+ (firstXByte + j) % 12;

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

			v1 = v2;
		}
	}
}

void LCD_LoadObjs(GameObj *header, uint8_t drawMode, uint8_t repeatMode) {
	GameObj *ptr = header;

	if (!ptr->full)
		return;

	for (;;) {
		LCD_LoadObj(ptr, drawMode, repeatMode);

		// If looped through all / next buffer is empty
		if (!ptr->next->full || ptr->next == header)
			return;
		ptr = ptr->next;
	}
}

void LCD_LoadObj(GameObj *gameObj, uint8_t drawMode, uint8_t repeatMode) {

	short displayRow;
	short displayRowOffset;

	//Counting from Y origin point to bmpH using for loop
	for (uint8_t y = 0; y < gameObj->height; y++) {
		displayRow = modulo(floor(gameObj->y) + y, 96);

		if ((repeatMode == REPEATMODE_NONE)
				&& (displayRow < 0 || displayRow >= 96)) {
			continue;
		}

		displayRowOffset = displayRow * 12;

		int firstXByte = floor(floor(gameObj->x) / 8);
		uint8_t leftOffset = modulo(floor(gameObj->x), 8);

		uint8_t v1, v2 = 0x00;
		uint8_t *currentEditingBuf;

		for (uint8_t j = 0; j < gameObj->width + 1; j++) {
			if (j == gameObj->width)
				v2 = 0x00;
			else
				v2 = *(gameObj->bmp + gameObj->width * y + j);

			if (repeatMode == REPEATMODE_NONE
					&& (firstXByte + j < 0 || firstXByte + j > 11)) {
				v1 = v2;
				continue;
			}

			currentEditingBuf = DispBuf + displayRowOffset
					+ (firstXByte + j) % 12;

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

			v1 = v2;
		}
	}
}

void LCD_DrawLine(uint8_t startingRow, int startingPoint, uint8_t length,
		uint8_t drawMode) {
	uint16_t rowOffset = (startingRow % 96) * 12;

	for (uint8_t j = 0; j < length; j++) {
		if (startingPoint + j < 0 || startingPoint + j > 95)
			continue;
		uint8_t additionalOffset = ((startingPoint + j) % 96) / 8;

		uint8_t *currentEditingBuf = DispBuf + rowOffset + additionalOffset;
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

//Invert color of Display memory buffer
void LCD_Invert(void) {
	uint16_t invt = 1152;
	do {
		invt--;
		DispBuf[invt] = ~DispBuf[invt];
	} while (invt);
}

//Fill screen with either black or white color
void LCD_Fill(bool fill) {
	memset(DispBuf, (fill ? 0 : 0xFF), 1152);
}

void LCD_DRAW_CIRCLE(short originX, short originY, uint8_t radius,
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

////Print 8x8 Text on screen
//void LCD_Print(char txtBuf[], size_t len){
//
//uint16_t strLen = len;
//uint16_t chOff = 0;
//
//for (uint16_t p = 0; p < strLen;p++){
//	// In case of reached 50 chars or newline detected , Do the newline
//	if ((Xcol > 50) || *txtBuf == 0x0A){
//		Xcol = 1;// Move cursor to most left
//		YLine += 8;// enter new line
//		txtBuf++;// move to next char
//	}
//
//	// Avoid printing Newline
//	if (*txtBuf != 0x0A){
//
//	chOff = (*txtBuf - 0x20) * 8;// calculate char offset (fist 8 pixel of character)
//
//	for(uint8_t i=0;i < 8;i++){// Copy the inverted color px to buffer
//	chBuf[i] = smallRbit(~font8x8_basic[i + chOff]);
//	}
//
//	LCD_LoadPart((uint8_t *)chBuf, Xcol, YLine, 1, 8);// Align the char with the 8n pixels
//
//	txtBuf++;// move to next char
//	Xcol++;// move cursor to next column
//	}
//  }
//}

