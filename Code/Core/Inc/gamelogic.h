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

typedef struct GameObj{
	uint8_t* bmp;
	float x, y;
	uint8_t width, height;
	struct GameObj* next;
};

bool IsOverlapping(short x1, short y1, short x2, short y2, short x3, short y3,
		short x4, short y4);
bool IsFadedOutOfScene(struct GameObj *obj);
void Append(struct GameObj *firstObj, short xPos);
void DeleteHeader(struct GameObj *firstObj);
void ShiftX(struct GameObj *firstObj, float byX);


#endif /* INC_GAMELOGIC_H_ */
