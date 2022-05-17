/*
 * dino_game.h
 *
 *  Created on: May 17, 2022
 *      Author: DannyHallo
 */

#ifndef INC_DINO_GAME_H_
#define INC_DINO_GAME_H_

#include <stdint.h>
#include "LS013B4DN04.h"

#define DINO_IS_ALIVE 0
#define DINO_IS_DEAD 1

void GenerateGameBuffers();
void GamePrep(LS013B4DN04 *display);
uint8_t GameTick(LS013B4DN04 *display);

#endif /* INC_DINO_GAME_H_ */
