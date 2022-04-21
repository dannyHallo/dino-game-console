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

bool IsFadedOutOfScene(GameObj *obj) {
	if (obj->x + obj->width * 8 < 0) {
		return true;
	} else {
		return false;
	}
}

// Append buffer in loop, if buffers are all occupied, use the first buffer
GameObj* Append(GameObj *header, short xPos) {
	GameObj *ptr = header;

	while (ptr->full) {
		ptr = ptr->next;
		if (ptr == header) {
			break;
		}
	}
	ptr->bmp = header->bmp;
	ptr->x = xPos;
	ptr->y = header->y;
	ptr->width = header->width;
	ptr->height = header->height;
	ptr->full = 1;

	// Out of memory, append on the back
	if(ptr == header)
		return header->next;
	// Normal state
	else
		return header;
}

// Generate loop buffer given certain size
GameObj* GenLoopBuf(uint8_t size) {
	GameObj *head = NULL, *cyclic = NULL;
	head = (GameObj*) malloc(sizeof(GameObj));
	head->full = 0;
	cyclic = head;
	for (int i = 1; i < size; i++) {
		GameObj *body = (GameObj*) malloc(sizeof(GameObj));
		body->full = 0;
		cyclic->next = body;
		cyclic = body;
	}
	cyclic->next = head;
	return head;
}

// Initializes the pointer
void ObjInit(GameObj* obj, uint8_t* bmp, float x, float y, uint8_t width, uint8_t height){
	obj->bmp = bmp;
	obj->x = x;
	obj->y = y;
	obj->width = width;
	obj->height = height;
	obj->full = 1;
}


// Shift all buffers and return the first active pointer
GameObj* ShiftX(GameObj *header, float byX) {
	GameObj *ptr = header;

	for (;;) {
		if (ptr->full) {
			ptr->x += byX;
		}
		ptr = ptr->next;
		if(ptr == header)
			break;
	}

	while (IsFadedOutOfScene(ptr)) {
		ptr->full = 0;
		ptr = ptr->next;
		if (ptr == header) {
			break;
		}
	}
	return ptr;
}
