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
GameObj* Append(GameObj *header, short xPos, short yPos) {
	GameObj *ptr = header;

	// If the current pointer is occupied, look for the next pos
	while (ptr->full) {
		ptr = ptr->next;
		// Have cycled for a whole loop
		if (ptr == header) {
			ptr->bmp = header->bmp;
			ptr->x = xPos;
			ptr->y = yPos;
			ptr->width = header->width;
			ptr->height = header->height;
			ptr->full = 1;
			return header->next;
		}
	}

	ptr->bmp = header->bmp;
	ptr->x = xPos;
	ptr->y = yPos;
	ptr->width = header->width;
	ptr->height = header->height;
	ptr->full = 1;
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

// Initializes the head pointer with the given values, n resets other buffers
void HeaderInit(GameObj *header, uint8_t *bmp, uint8_t width, uint8_t height) {
	GameObj *ptr = header;

	ptr->bmp = bmp;
	ptr->x = 0;
	ptr->y = 0;
	ptr->width = width;
	ptr->height = height;
	ptr->full = 0;

	for (;;) {
		if (ptr->next == header)
			return;
		ptr = ptr->next;
		ptr->full = 0;
	}
}

// Shift all buffers and return the first active pointer
GameObj* ShiftX(GameObj *header, float byX) {
	GameObj *ptr = header;

	// Cycle through all valid buffers once and apply the drift
	for (;;) {
		if (ptr->full) {
			ptr->x += byX;
		}
		// Have cycled through the buffer
		if (!ptr->next->full || ptr->next == header)
			break;
		ptr = ptr->next;
	}

	ptr = header;
	// Return the first available buffer, if no buf is available, return header
	while (IsFadedOutOfScene(ptr)) {
		ptr->full = 0;
		if (!ptr->next->full || ptr->next == header) {
			break;
		}
		ptr = ptr->next;
	}
	return ptr;
}

short Random(unsigned long seed, short lowerLim, short upperLim) {
	srand(seed);
	return rand() % (upperLim - lowerLim + 1) + lowerLim;
}
