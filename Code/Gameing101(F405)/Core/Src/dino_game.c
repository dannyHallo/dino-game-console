/*
 * dino_game.c
 *
 *  Created on: May 17, 2022
 *      Author: DannyHallo
 */

#include "dino_game.h"

#include "image.h"

#include "buttons.h"
#include "game_utilities.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define GLIDE_BUTTON 1
#define DODGE_BUTTON 2
#define FIRE_BUTTON 3
#define JUMP_BUTTON 4

// GRAVITY
const float gravity = 0.08;
const float initVel = 2;
const float dinoGroundPos = 58;
const float parachuteGrag = 0.3;
const float longPressGravityMul = 0.6;
const float dodgeGravityMul = 2;
static float dinoVel = 0;

// TICK
const uint8_t fireTickLength = 20;
const uint16_t softStartTickLength = 200;
static uint32_t tick, plantTick, cloudTick, fireTick, bumpOrDepressionTick,
		dirtTexTick;

static bool flipStatus;
static uint16_t nextPlantTickDel, nextCloudTickDel, nextBumpOrDepressionTickDel,
		nextDirtTexTickDel;

#define STANDING 0
#define RUNNING 1
#define FIRING 2
#define JUMPING 3
#define GLIDING 4
#define DODGING 5
#define DIED 6
static uint8_t dinoState;

static uint8_t groundLength;
static float overallSpeed;

static GameObj *ptr;
static GameObj *ptr2;

static GameObj *dinoHeader;
static GameObj *fireHeader;
static GameObj *lavaHeader;
static GameObj *cloudHeader;
static GameObj *plantHeader;
static GameObj *dirtTexHeader;
static GameObj *bumpAndDepressionHeader;

void RenderDino(GameObj *dino, uint8_t dinoState, bool isDead);
bool DinoGetsStuck();
void MeltPlants();

void GenerateGameBuffers() {
	dinoHeader = GenLoopBuf(1);
	fireHeader = GenLoopBuf(1);
	lavaHeader = GenLoopBuf(2);
	cloudHeader = GenLoopBuf(2);
	plantHeader = GenLoopBuf(4);
	dirtTexHeader = GenLoopBuf(12);
	bumpAndDepressionHeader = GenLoopBuf(4);
}

void GamePrep(LS013B4DN04 *display) {
	flipStatus = 0;

	nextPlantTickDel = 0;
	nextCloudTickDel = 0;
	nextDirtTexTickDel = 0;
	nextBumpOrDepressionTickDel = 0;

	plantTick = 0;
	cloudTick = 0;
	dirtTexTick = 0;
	bumpOrDepressionTick = 0;

	groundLength = 29;
	tick = 0;
	overallSpeed = 1;

	HeaderInit(dinoHeader, (uint8_t*) DinoAssets, 4, 22, 14);
	HeaderInit(fireHeader, (uint8_t*) FireAssets, 9, 25, 2);
	HeaderInit(cloudHeader, (uint8_t*) CloudAssets, 6, 14, 1);
	HeaderInit(plantHeader, (uint8_t*) PlantAssets, 2, 22, 5);
	HeaderInit(lavaHeader, (uint8_t*) LavaAssets, 9, 6, 4);
	HeaderInit(dirtTexHeader, (uint8_t*) DirtTextureAssets, 1, 1, 6);
	HeaderInit(bumpAndDepressionHeader, (uint8_t*) BumpAndDepressionAssets, 1,
			2, 2);

	dinoHeader = Append(dinoHeader, DinoNormalStand, DinoXPosDefault,
			dinoGroundPos);
	fireHeader = Append(fireHeader, CloudNormal, 24, 52);

	LCD_Fill(flipStatus);
	LCD_DrawLine(77, 0, 29, DRAWMODE_ADD, flipStatus);
	LCD_DrawLine(dinoHeader->y + 19, dinoHeader->x + 7, 10, DRAWMODE_CULL,
			flipStatus);
	LCD_LoadObjs(dinoHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);

	LCD_Print("dev\tver.", 40, 85, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);

	LCD_UpdateFull(display);
	while (!GetButtonDown(JUMP_BUTTON))
		;
	dinoVel = initVel;
	dinoState = JUMPING;
}

uint8_t GameTick(LS013B4DN04 *display) {

	// Day and night invertion
	flipStatus = ((tick / 800) % 3 == 2) ? 1 : 0;
	LCD_Fill(flipStatus);

	switch (dinoState) {
	case JUMPING:
	case GLIDING:
	case DODGING:
		// Dino above ground
		if (dinoHeader->y <= dinoGroundPos) {

			dinoHeader->y -= dinoVel;
			if (GetButton(GLIDE_BUTTON) && dinoVel < 0) {
				dinoState = GLIDING;
				dinoVel -= gravity;
				dinoVel += -dinoVel * parachuteGrag;
			}
			if (GetButton(DODGE_BUTTON)) {
				dinoState = DODGING;
				dinoVel -= gravity * dodgeGravityMul;
			} else {
				dinoState = JUMPING;
				dinoVel -=
						GetButton(JUMP_BUTTON) ?
								(gravity * longPressGravityMul) : gravity;
			}
			break;
		}
		// First land continue

	default:
		dinoHeader->y = dinoGroundPos;
		dinoVel = 0;

		if (GetButtonDown(JUMP_BUTTON)) {
			dinoVel = initVel;
			dinoState = JUMPING;
		} else if (GetButton(DODGE_BUTTON)) {
			dinoState = DODGING;
		} else if (GetButtonDown(FIRE_BUTTON)) {
			fireTick = fireTickLength;
			lavaHeader = Append(lavaHeader, 0, 57, 71);
		} else if (GetButton(FIRE_BUTTON)) {
			dinoState = FIRING;
		} else {
			dinoState = RUNNING;
		}

		break;
	}

	// Plant generation
	if (tick - softStartTickLength - plantTick == nextPlantTickDel) {
		plantHeader = Append(plantHeader, PlantNormal, 96, 59);
		nextPlantTickDel = Random(tick, 80, 330);
		plantTick = tick - softStartTickLength;
	}
	// Cloud generation
	if (tick - softStartTickLength - cloudTick == nextCloudTickDel) {
		cloudHeader = Append(cloudHeader, CloudNormal, 96,
				Random(tick, 12, 20));
		nextCloudTickDel = Random(tick, 1200, 2000);
		cloudTick = tick - softStartTickLength;
	}
	// Dirt texture generation
	if (tick - softStartTickLength - dirtTexTick == nextDirtTexTickDel) {

		dirtTexHeader = Append(dirtTexHeader, Random(tick, 2, 6), 96,
				Random(tick, 83, 87));

		nextDirtTexTickDel = Random(tick, 8, 30);
		dirtTexTick = tick - softStartTickLength;
	}
	// Bumps and depressions generation
	if (tick - softStartTickLength - bumpOrDepressionTick
			== nextBumpOrDepressionTickDel) {
		if (Random(tick, 0, 1)) {
			bumpAndDepressionHeader = Append(bumpAndDepressionHeader,
			Bump, 96, 75);
		} else {
			bumpAndDepressionHeader = Append(bumpAndDepressionHeader,
			Depression, 96, 78);
		}

		nextBumpOrDepressionTickDel = Random(tick, 20, 150);
		bumpOrDepressionTick = tick - softStartTickLength;
	}

	// Roll ground plane
	if (groundLength < 96) {

		LCD_DrawLine(77, 0, groundLength, DRAWMODE_ADD, flipStatus);
		groundLength++;
	} else {

		// Still ground plane
		LCD_DrawLine(77, 0, 96, DRAWMODE_ADD, flipStatus);
	}

	// Ground objs shift
	plantHeader = ShiftX(plantHeader, -1 * overallSpeed);
	lavaHeader = ShiftX(lavaHeader, -1 * overallSpeed);
	dirtTexHeader = ShiftX(dirtTexHeader, -1 * overallSpeed);
	bumpAndDepressionHeader = ShiftX(bumpAndDepressionHeader,
			-1 * overallSpeed);

	// Air objs shift
	cloudHeader = ShiftX(cloudHeader, -0.1 * overallSpeed);

	// Cull plant
	ptr = plantHeader;
	for (;;) {
		if (ptr->full) {
			for (uint8_t y = 71; y <= 77; y++) {
				LCD_DrawLine(y, ptr->x + 2, 6, DRAWMODE_CULL, flipStatus);
			}
		}
		// If looped through all / next buffer is empty
		if (!ptr->next->full || ptr->next == plantHeader)
			break;

		ptr = ptr->next;
	}

	// Cull bumps
	ptr = bumpAndDepressionHeader;
	for (;;) {
		if (ptr->full) {

			LCD_DrawLine(77, ptr->x + 1, 6, DRAWMODE_CULL, flipStatus);
		}
		// If looped through all / next buffer is empty
		if (!ptr->next->full || ptr->next == bumpAndDepressionHeader)
			break;

		ptr = ptr->next;
	}

	// Cull dino
	LCD_DrawLine(dinoHeader->y + 19, dinoHeader->x + 7, 10, DRAWMODE_CULL,
			flipStatus);

	if (fireTick > 0) {
		fireTick--;

		UpdateHeaderBmpIndex(fireHeader,
				((fireTickLength - fireTick) / (int) (12 / overallSpeed)) % 2);
		LCD_LoadObjs(fireHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);

	}

	UpdateAllBmpIndexs(lavaHeader, (tick / (int) (16 / overallSpeed)) % 4);

	LCD_LoadObjs(lavaHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);

	LCD_LoadObjs(plantHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);
	LCD_LoadObjs(cloudHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);
	LCD_LoadObjs(dirtTexHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);
	LCD_LoadObjs(bumpAndDepressionHeader, DRAWMODE_ADD, REPEATMODE_NONE,
			flipStatus);

	MeltPlants();

	if (DinoGetsStuck())
		goto Dead;

	RenderDino(dinoHeader, dinoState, 0);

	tick++;
	LCD_UpdateFull(display);
	return DINO_IS_ALIVE;

	Dead: LCD_DrawLine(dinoHeader->y + 19, dinoHeader->x + 7, 10,
	DRAWMODE_CULL, flipStatus);

	RenderDino(dinoHeader, dinoState, 1);

	LCD_UpdateFull(display);

	HAL_Delay(200);

	// Flip screen
	for (uint8_t i = 0; i < 2; i++) {
		HAL_Delay(80);
		LCD_Invert();
		LCD_UpdateFull(display);
	}

	// Redraw Dino
	while (dinoHeader->y < dinoGroundPos) {
		LCD_Fill(flipStatus);
		LCD_DrawLine(77, 0, 96, DRAWMODE_ADD, flipStatus);
		dinoHeader->y++;
		LCD_DrawLine(dinoHeader->y + 19, dinoHeader->x + 3, 10,
		DRAWMODE_CULL, flipStatus);
		LCD_LoadObjs(dinoHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);
		HAL_Delay(5);
		LCD_UpdateFull(display);

	}

	for (uint8_t l = 96; l > 28; l--) {
		uint8_t delayTime = ceil((float) (96 - l) * 8 / 67);
		LCD_DrawLine(77, l, 1, DRAWMODE_CULL, flipStatus);
		LCD_UpdateLine(display, 77);
		HAL_Delay(delayTime);
		if (GetButtonDown(JUMP_BUTTON))
			break;
	}
	return DINO_IS_DEAD;
}

void RenderDino(GameObj *dino, uint8_t dinoState, bool isDead) {
	if (!isDead) {
		switch (dinoState) {
		case RUNNING:
			UpdateHeaderBmpIndex(dino,
					(tick / (int) (12 / overallSpeed)) % 2 + 1);
			dinoHeader->x = DinoXPosDefault;
			break;
		case JUMPING:
			UpdateHeaderBmpIndex(dino, DinoNormalStand);
			dinoHeader->x = DinoXPosDefault;
			break;
		case GLIDING:
			UpdateHeaderBmpIndex(dino, DinoGliding);
			dinoHeader->x = DinoXPosWhenGliding;
			break;
		case DODGING:
			UpdateHeaderBmpIndex(dino,
			DinoDodgingL + (tick / (int) (12 / overallSpeed)) % 2);
			dinoHeader->x = DinoXPosWhenDodging;
			break;
		case FIRING:
			UpdateHeaderBmpIndex(dino,
			DinoFiringL + (tick / (int) (12 / overallSpeed)) % 2);
			dinoHeader->x = DinoXPosDefault;
			break;
		}
	} else if (isDead) {
		switch (dinoState) {
		case RUNNING:
		case JUMPING:
			UpdateHeaderBmpIndex(dino, DinoNormalDead);
			dinoHeader->x = DinoXPosDefault;
			break;
		case GLIDING:
			UpdateHeaderBmpIndex(dino, DinoGlidingDead);
			dinoHeader->x = DinoXPosWhenGliding;
			break;
		case DODGING:
			UpdateHeaderBmpIndex(dino, DinoDodgingDead);
			dinoHeader->x = DinoXPosWhenDodging;
			break;
		case FIRING:
			UpdateHeaderBmpIndex(dino, DinoFiringDead);
			dinoHeader->x = DinoXPosDefault;
			break;
		}
	}

	LCD_LoadObjs(dinoHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);
}

bool DinoGetsStuck() {
	// Loop through plants, check death
	ptr = plantHeader;
	for (;;) {
		if (ptr->full && ptr->index == PlantNormal) {
			switch (dinoState) {
			case RUNNING:
				if (IsOverlapping(dinoHeader->x + 10, dinoHeader->y + 2,
						dinoHeader->x + 17, dinoHeader->y + 17, ptr->x, 59,
						ptr->x + 9, 59 + 21)) {
					return 1;
				}
				break;

			case GLIDING:
			case DODGING:
				if (IsOverlapping(dinoHeader->x + 9, dinoHeader->y + 11,
						dinoHeader->x + 30, dinoHeader->y + 17, ptr->x, 59,
						ptr->x + 9, 59 + 21)) {
					return 1;
				}
				break;

			case FIRING:
				if (IsOverlapping(dinoHeader->x + 10, dinoHeader->y + 2,
						dinoHeader->x + 18, dinoHeader->y + 17, ptr->x, 59,
						ptr->x + 9, 59 + 21)) {
					return 1;
				}
				break;
			}

		}
		// If looped through all / next buffer is empty
		if (!ptr->next->full || ptr->next == plantHeader) {
			break;
		}
		ptr = ptr->next;
	}

	return 0;
}

void MeltPlants() {
	// Loop through GroundFires and Plants, shrink plants
	ptr = lavaHeader;
	ptr2 = plantHeader;
	for (;;) {
		for (;;) {
			if (ptr->full && ptr2->full) {
				if (IsOverlapping(ptr->x, ptr->y, ptr->x + 72, ptr->y + 25,
						ptr2->x, ptr2->y, ptr2->x + 9, ptr2->y + 21)) {
					if (tick % 10 == 0) {
						ImgIndexRightShift(ptr2, 1);
					}
				}
			}
			// If looped through all / next buffer is empty
			if (!ptr2->next->full || ptr2->next == plantHeader) {
				break;
			}
			ptr2 = ptr2->next;
		}
		// If looped through all / next buffer is empty
		if (!ptr->next->full || ptr->next == lavaHeader) {
			break;
		}
		ptr = ptr->next;
	}
}
