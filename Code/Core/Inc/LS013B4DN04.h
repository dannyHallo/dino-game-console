/*
 * LS013B4DN04.h
 *
 *  Created on: Apr 8, 2022
 *      Author: TinLethax (Thipok Jiamjarapan), DannyHallo
 *      Github: https://github.com/TiNredmc/SharpMEMDisp/blob/master/Core/Inc/LS027B7DH01.h
 */

#ifndef INC_LS013B4DN04_H_
#define INC_LS013B4DN04_H_

#include "stm32f1xx_hal.h"
#include "gamelogic.h"
#include <stdbool.h>


// This typedef holds the hardware parameters. For GPIO and SPI
typedef struct {
	SPI_HandleTypeDef *Bus;
	GPIO_TypeDef *dispGPIO;
	uint16_t LCDcs;
} LS013B4DN04;

#define DRAWMODE_ADD 0
#define DRAWMODE_CULL 1
#define DRAWMODE_TOGGLE 2

#define REPEATMODE_NONE 0
#define REPEATMODE_REPEAT 1

void LCD_Init(LS013B4DN04 *MemDisp, SPI_HandleTypeDef *Bus,
		GPIO_TypeDef *dispGPIO, uint16_t LCDcs);

void LCD_Update(LS013B4DN04 *MemDisp);

void LCD_LoadFull(uint8_t *BMP);

void LCD_LoadObjs(GameObj *header, uint8_t drawMode, uint8_t repeatMode,
bool flip);

void LCD_LoadObj(uint8_t *bmp, float posX, float posY, uint8_t width,
		uint8_t height, uint8_t drawMode, uint8_t repeatMode, bool flip);

void LCD_DrawLine(uint8_t startingRow, int startingPoint, uint8_t length,
		uint8_t drawMode, bool flip);

void LCD_BufClean(void);

void LCD_Invert(void);

void LCD_Fill(bool flip);

void LCD_DrawCircle(short originX, short originY, uint8_t radius,
		uint8_t drawMode);

void LCD_Print(char *str, short xPos, short yPos, uint8_t drawMode,
		uint8_t repeatMode, bool flip);
#endif /* INC_LS013B4DN04_H_ */
