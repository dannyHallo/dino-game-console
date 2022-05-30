/*
 * gamelogic.c
 *
 *  Created on: Apr 16, 2022
 *      Author: DannyHallo
 */

#include "game_utilities.h"

bool IsOverlapping(short x1, short y1, short x2, short y2, short x3, short y3,
		short x4, short y4) {
	if (x1 > x4 || x3 > x2 || y1 > y4 || y3 > y2) {
		return false;
	}
	return true;
}

// Append buffer in loop, if buffers are all occupied, use the first buffer
void Append(GameObj *header, uint8_t index, float xPos, float yPos, float xVel,
		float yVel) {
	GameObj *ptr = header;

// If the current pointer is occupied, look for the next pos
	while (ptr->isOccupied) {
		ptr = ptr->next;
		// Have cycled for a whole loop
		if (ptr == header) {
			break;
		}
	}

	ptr->currentIndex = index;
	ptr->isOccupied = 1;
	ptr->transform.position.x = xPos;
	ptr->transform.position.y = yPos;
	ptr->transform.velocity.x = xVel;
	ptr->transform.velocity.y = yVel;
	ptr->transform.gravity.x = 0;
	ptr->transform.gravity.y = 0;
}

void UpdateHeaderBmpIndex(GameObj *header, uint8_t toIndex) {
	header->currentIndex = toIndex;
}

void UpdateAllBmpIndexs(GameObj *header, uint8_t toIndex, uint8_t ignoreIndex) {
	GameObj *ptr = header;

// If the current pointer is occupied, look for the next pos
	for (;;) {
		if (ptr->currentIndex != ignoreIndex)
			ptr->currentIndex = toIndex;
		ptr = ptr->next;

		// Have cycled for a whole loop
		if (ptr == header)
			return;
	}
}

// Set all buffers to empty
void DisableAll(GameObj *header) {
	GameObj *ptr = header;

// If the current pointer is occupied, look for the next pos
	for (;;) {
		ptr->isOccupied = 0;
		ptr = ptr->next;

		// Have cycled for a whole loop
		if (ptr == header)
			return;
	}
}

// Generate loop buffer given certain size
GameObj* GenLoopBuf(uint8_t *bmpAsset, uint8_t width, uint8_t height,
		uint8_t assetSize, uint8_t bufferSize) {

	GameObj *header = NULL, *cyclic = NULL;
	header = (GameObj*) malloc(sizeof(GameObj));

	header->imageProperty.assetSize = assetSize;
	header->imageProperty.bmpAsset = bmpAsset;
	header->imageProperty.resolution.x = width;
	header->imageProperty.resolution.y = height;

	header->currentIndex = 0;

	header->transform.position.x = 0;
	header->transform.position.y = 0;
	header->transform.gravity.x = 0;
	header->transform.gravity.y = 0;
	header->transform.velocity.x = 0;
	header->transform.velocity.y = 0;

	header->isOccupied = 0;

	cyclic = header;
	for (int i = 1; i < bufferSize; i++) {
		GameObj *body = (GameObj*) malloc(sizeof(GameObj));

		body->imageProperty.assetSize = assetSize;
		body->imageProperty.bmpAsset = bmpAsset;
		body->imageProperty.resolution.x = width;
		body->imageProperty.resolution.y = height;

		body->currentIndex = 0;

		body->transform.position.x = 0;
		body->transform.position.y = 0;
		body->transform.gravity.x = 0;
		body->transform.gravity.y = 0;
		body->transform.velocity.x = 0;
		body->transform.velocity.y = 0;

		body->isOccupied = 0;

		cyclic->next = body;
		cyclic = body;
	}
	cyclic->next = header;
	return header;
}

void CalculatePositions(GameObj *header) {
	GameObj *ptr = header;

	CalculatePosition(ptr);

	while (ptr->next != header) {
		ptr = ptr->next;
		CalculatePosition(ptr);
	}
}

void CalculatePosition(GameObj *header) {

	header->transform.velocity.x += header->transform.gravity.x;
	header->transform.velocity.y += header->transform.gravity.y;

	header->transform.position.x += header->transform.velocity.x;
	header->transform.position.y += header->transform.velocity.y;
}

//// Shift all buffers and return the first active pointer
//GameObj* ShiftX(GameObj *header, float byX) {
//	GameObj *ptr = header;
//
//	// Cycle through all valid buffers once and apply the drift
//	for (;;) {
//		if (ptr->isOccupied) {
//			ptr->x += byX;
//		}
//		// Have cycled through the buffer
//		if (!ptr->next->isOccupied || ptr->next == header)
//			break;
//		ptr = ptr->next;
//	}
//
//	ptr = header;
//	// Return the first available buffer, if no buf is available, return header
//	while (IsFadedOutOfScene(ptr)) {
//		ptr->isOccupied = 0;
//		if (!ptr->next->isOccupied || ptr->next == header) {
//			break;
//		}
//		ptr = ptr->next;
//	}
//	return ptr;
//}

void ImgIndexRightShift(GameObj *header, bool disableWhenEnd) {
	if (header->currentIndex < header->imageProperty.assetSize - 1) {
		header->currentIndex++;
		return;
	}
	if (disableWhenEnd) {
		header->currentIndex = 0;
		header->isOccupied = false;
	}

}

short Random(unsigned long seed, short lowerLim, short upperLim) {
	srand(seed);
	return rand() % (upperLim - lowerLim + 1) + lowerLim;
}
