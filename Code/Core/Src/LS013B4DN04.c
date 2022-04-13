/*
 * LS013B4DN04.c
 *
 *  Created on: Apr 8, 2022
 *      Author: TinLethax (Thipok Jiamjarapan), DannyHallo
 *      Github: https://github.com/TiNredmc/SharpMEMDisp/blob/master/Core/Src/LS027B7DH01.c
 */

#include "LS013B4DN04.h"
//#include "font8x8_basic.h"
#include <string.h>
#include <stdlib.h>

//Display Commands
uint8_t clearCMD[2] = { 0x20, 0x00 }; // Display Clear 0x04 (HW_LSB)
uint8_t printCMD[2] = { 0x80, 0x00 }; // Display Bitmap (after issued display update) 0x01 (HW_LSB)
uint8_t emptyByte = 0x00;

//This buffer holds 50 Bytes * 240 Row = 12K of Display buffer
uint8_t *DispBuf; // entire display buffer.

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

//// Display Initialization
//void LCD_Init(LS013B4DN04 *MemDisp, SPI_HandleTypeDef *Bus,
//		GPIO_TypeDef *dispGPIO,uint16_t LCDcs,uint16_t LCDon,
//		TIM_HandleTypeDef *TimerX, uint32_t COMpwm){
//
//	//Store params into our struct
//	MemDisp->Bus = Bus;
//	MemDisp->dispGPIO = dispGPIO;
//	MemDisp->TimerX = TimerX;
//	MemDisp->COMpwm = COMpwm;
//	MemDisp->LCDcs = LCDcs;
//	MemDisp->LCDon = LCDon;
//
//	DispBuf = malloc(1152);
//	memset(DispBuf, 0xFF, 1152);
//
//	HAL_GPIO_WritePin(MemDisp->dispGPIO,MemDisp->LCDon,GPIO_PIN_SET);// Turn display back on
//	//Start 50Hz PWM for COM inversion of the display
//	HAL_TIM_PWM_Start(MemDisp->TimerX,MemDisp->COMpwm);
//	MemDisp->TimerX->Instance->CCR1 = 5;
//
//
//	//At lease 3 + 13 clock is needed for Display clear (16 Clock = 8x2 bit = 2 byte)
//	HAL_GPIO_WritePin(MemDisp->dispGPIO,MemDisp->LCDcs,GPIO_PIN_SET);
//	HAL_SPI_Transmit(MemDisp->Bus, (uint8_t *)clearCMD, 2,150); //According to Datasheet
//	HAL_GPIO_WritePin(MemDisp->dispGPIO,MemDisp->LCDcs,GPIO_PIN_RESET);
//
//
//}

// Display Initialization
void LCD_Init(LS013B4DN04 *MemDisp, SPI_HandleTypeDef *Bus,
		GPIO_TypeDef *dispGPIO, uint16_t LCDcs) {

	//Store params into our struct
	MemDisp->Bus = Bus;
	MemDisp->dispGPIO = dispGPIO;
	MemDisp->LCDcs = LCDcs;

	DispBuf = malloc(1152);

	memset(DispBuf, 0x00, 1152);

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

//Clean the Buffer
void LCD_BufClean(void) {
	YLine = 1;
	Xcol = 1;
	memset(DispBuf, 0xFF, 1152);
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
void LCD_LoadPart(uint8_t *BMP, uint8_t Xcord, uint8_t Ycord, uint8_t bmpW,
		uint8_t bmpH, bool toggle) {

	uint8_t displayRow = 0;
	uint16_t displayRowOffset = 0;

	//Counting from Y origin point to bmpH using for loop
	for (uint8_t y = 0; y < bmpH; y++) {
		displayRow = (Ycord + y) % 96;
		displayRowOffset = displayRow * 12;

		uint8_t firstXByte = Xcord / 8;
		uint8_t leftOffset = Xcord % 8;

		uint8_t v1, v2 = 0x00;

		for (uint8_t j = 0; j < bmpW + 1; j++) {
			if (j == bmpW)
				v2 = 0x00;
			else
				v2 = *(BMP + bmpW * y + j);

			if (toggle) {
				*(DispBuf + displayRowOffset + (firstXByte + j) % 12) ^= ((v1
						<< (8 - leftOffset)) | (v2 >> leftOffset));
			} else {
				*(DispBuf + displayRowOffset + (firstXByte + j) % 12) |= ((v1
						<< (8 - leftOffset)) | (v2 >> leftOffset));
			}

			v1 = v2;
		}
	}
}

void LCD_DrawLine(uint8_t startingRow, uint8_t startingPoint, uint8_t length, bool negative) {
	uint16_t rowOffset = (startingRow % 96) * 12;

	for (uint8_t j = 0; j < length; j++) {
		uint8_t additionalOffset = ((startingPoint + j) % 96) / 8;
		if(negative){
			*(DispBuf + rowOffset + additionalOffset) &= ~(0x80
							>> ((startingPoint + j) % 8));
		}else{
			*(DispBuf + rowOffset + additionalOffset) |= (0x80
				>> ((startingPoint + j) % 8));
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
//	HAL_Delay(10);
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

