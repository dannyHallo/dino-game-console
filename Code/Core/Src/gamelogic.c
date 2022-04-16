/*
 * gamelogic.c
 *
 *  Created on: Apr 16, 2022
 *      Author: DannyHallo
 */

#include "gamelogic.h"

bool IsOverlapping(short x1, short y1, short x2, short y2, short x3, short y3,
		short x4, short y4) {
	if(x1 > x4 || x3 > x2 || y1 > y4 || y3 > y2){
		return false;
	}
	return true;
}

