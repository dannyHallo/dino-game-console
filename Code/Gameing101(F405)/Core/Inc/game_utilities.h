/*
 * gamelogic.h
 *
 *  Created on: 2022年4月16日
 *      Author: Administrator
 */

#ifndef INC_GAME_UTILITIES_H_
#define INC_GAME_UTILITIES_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct GameObj {
	uint8_t *bmpAsset;
	float x, y;
	uint8_t width, height;
	uint8_t assetSize, index;
	bool full;
	struct GameObj *next;
} GameObj;

#define NoIgnoringIndex 255

bool IsOverlapping(short x1, short y1, short x2, short y2, short x3, short y3,
		short x4, short y4);

bool IsFadedOutOfScene(struct GameObj *obj);

GameObj* Append(struct GameObj *header, uint8_t index, short xPos, short yPos);

void UpdateHeaderBmpIndex(GameObj *header, uint8_t toIndex);

void UpdateAllBmpIndexs(GameObj *header, uint8_t toIndex, uint8_t ignoreIndex);

void DisableAll(GameObj *header);

GameObj* GenLoopBuf(uint8_t size);

void HeaderInit(GameObj *header, uint8_t *bmpAsset, uint8_t width,
		uint8_t height, uint8_t size);

GameObj* ShiftX(GameObj *header, float byX);

GameObj* DisableCurrent(GameObj *header);

void ImgIndexRightShift(GameObj *header, bool disableWhenEnd);

short Random(unsigned long seed, short lowerLim, short upperLim);

#endif /* INC_GAME_UTILITIES_H_ */
