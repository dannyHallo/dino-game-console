/*
 * gamelogic.h
 *
 *  Created on: 2022年4月16日
 *      Author: Administrator
 */

#ifndef INC_GAMELOGIC_H_
#define INC_GAMELOGIC_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct GameObj {
	uint8_t *bmp;
	float x, y;
	uint8_t width, height;
	bool full;
	struct GameObj *next;
} GameObj;

bool IsOverlapping(short x1, short y1, short x2, short y2, short x3, short y3,
		short x4, short y4);
bool IsFadedOutOfScene(struct GameObj *obj);
GameObj* Append(struct GameObj *header, short xPos, short yPos);
GameObj* GenLoopBuf(uint8_t size);
void HeaderInit(GameObj *header, uint8_t *bmp, float x, float y, uint8_t width,
		uint8_t height);
GameObj* ShiftX(GameObj *header, float byX);
short Random(unsigned long seed, short lowerLim, short upperLim);

#endif /* INC_GAMELOGIC_H_ */
