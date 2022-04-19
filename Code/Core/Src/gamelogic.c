/*
 * gamelogic.c
 *
 *  Created on: Apr 16, 2022
 *      Author: DannyHallo
 */

#include "gamelogic.h"

bool IsOverlapping(short x1, short y1, short x2, short y2, short x3, short y3,
		short x4, short y4) {
	if (x1 > x4 || x3 > x2 || y1 > y4 || y3 > y2) {
		return false;
	}
	return true;
}

bool IsFadedOutOfScene(struct GameObj *obj) {
	if (obj->x + obj->width * 8 < 0) {
		return true;
	} else {
		return false;
	}
}

void Append(struct GameObj *firstObj, short xPos) {
	struct GameObj nextObj = { .bmp = firstObj->bmp, .x = xPos,
			.y = firstObj->y, .height = firstObj->height, .width =
					firstObj->width, .next = NULL };

	// Move pointer to the last pos, and append
	struct GameObj *pointer = firstObj;
	while (pointer->next != NULL) {
		pointer = pointer->next;
	}
	*pointer->next = nextObj;
}

void DeleteHeader(struct GameObj *firstObj) {
	if (firstObj->next == NULL){
		firstObj->x = 96;
		return;
	}
	struct GameObj *temp = firstObj;
	firstObj = firstObj->next;
	free(temp);
}

void ShiftX(struct GameObj *firstObj, float byX) {
	struct GameObj *pointer = firstObj;
	pointer->x += byX;

	while (pointer->next != NULL) {
		pointer = pointer->next;
		pointer->x += byX;
	}

	if (IsFadedOutOfScene(firstObj)) {
		DeleteHeader(firstObj);
	}
}
