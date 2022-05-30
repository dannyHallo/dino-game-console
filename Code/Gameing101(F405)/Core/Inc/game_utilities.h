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

struct Vector2Uint8 {
	uint8_t x;
	uint8_t y;
};

struct Vector2Float {
	float x;
	float y;
};

struct ImageProperty {
	uint8_t *bmpAsset;
	struct Vector2Uint8 resolution;
	uint8_t assetSize;
};

struct Transform {
	struct Vector2Float position;
	struct Vector2Float velocity;
	struct Vector2Float gravity;
};

typedef struct GameObj {
	struct ImageProperty imageProperty;
	struct Transform transform;
	struct GameObj *next;

	uint8_t currentIndex;
	bool isOccupied;
} GameObj;

#define NoIgnoringIndex 255

bool IsOverlapping(short x1, short y1, short x2, short y2, short x3, short y3,
		short x4, short y4);

void Append(GameObj *header, uint8_t index, float xPos, float yPos, float xVel,
		float yVel);

void UpdateHeaderBmpIndex(GameObj *header, uint8_t toIndex);

void UpdateAllBmpIndexs(GameObj *header, uint8_t toIndex, uint8_t ignoreIndex);

void DisableAll(GameObj *header);

GameObj* GenLoopBuf(uint8_t *bmpAsset, uint8_t width, uint8_t height,
		uint8_t assetSize, uint8_t bufferSize);
GameObj* ShiftX(GameObj *header, float byX);
GameObj* DisableCurrent(GameObj *header);
void ImgIndexRightShift(GameObj *header, bool disableWhenEnd);

void CalculatePosition(GameObj *header);
void CalculatePositions(GameObj *header);

short Random(unsigned long seed, short lowerLim, short upperLim);

#endif /* INC_GAME_UTILITIES_H_ */
