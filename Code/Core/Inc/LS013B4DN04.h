/*
 * LS013B4DN04.h
 *
 *  Created on: Apr 8, 2022
 *      Author: TinLethax (Thipok Jiamjarapan), DannyHallo
 *      Github: https://github.com/TiNredmc/SharpMEMDisp/blob/master/Core/Inc/LS027B7DH01.h
 */

#ifndef INC_LS013B4DN04_H_
#define INC_LS013B4DN04_H_

#include <stdbool.h>
#include "stm32f1xx_hal.h"

//// This typedef holds the hardware parameters. For GPIO and SPI
//typedef struct {
//	SPI_HandleTypeDef 	*Bus;
//	GPIO_TypeDef 		*dispGPIO;
//	TIM_HandleTypeDef	*TimerX;
//	uint32_t			 COMpwm;
//	uint16_t 			 LCDcs;
//	uint16_t			 LCDon;
//}LS013B4DN04;

// This typedef holds the hardware parameters. For GPIO and SPI
typedef struct {
	SPI_HandleTypeDef 	*Bus;
	GPIO_TypeDef 		*dispGPIO;
	uint16_t 			 LCDcs;
}LS013B4DN04;


//void LCD_Init(LS013B4DN04 *MemDisp, SPI_HandleTypeDef *Bus,
//		GPIO_TypeDef *dispGPIO,uint16_t LCDcs,uint16_t LCDon,
//		TIM_HandleTypeDef *TimerX, uint32_t COMpwm);

void LCD_Init(LS013B4DN04 *MemDisp, SPI_HandleTypeDef *Bus,
		GPIO_TypeDef *dispGPIO,uint16_t LCDcs);
void LCD_Clean(LS013B4DN04 *MemDisp);
void LCD_Update(LS013B4DN04 *MemDisp);
void LCD_LoadFull(uint8_t * BMP);
void LCD_LoadPart(uint8_t* BMP, uint8_t Xcord, uint8_t Ycord, uint8_t bmpW, uint8_t bmpH, bool toggle);
void LCD_DrawLine(uint8_t startingRow, uint8_t startingPoint, uint8_t length, bool negative);
void LCD_Print(char txtBuf[],size_t len);
void LCD_BufClean(void);
void LCD_Invert(void);
void LCD_Fill(bool fill);

#endif /* INC_LS013B4DN04_H_ */
