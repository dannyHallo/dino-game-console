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

#define RESERVED_BUTTON_1 1
#define BUTTON_1 2
#define BUTTON_2 3
#define RESERVED_BUTTON_2 4

// GRAVITY
const float gravity = 0.08;
const float initVel = 2;
const float dinoGroundPos = 58;
const float parachuteGrag = 0.3;
const float longPressGravityMul = 0.6;
const float dodgeGravityMul = 2;
static float dinoVel = 0;

// TICK
const uint16_t terrainGenPreTick = 100;
const uint16_t birdGenPreTick = 160;

static uint32_t tick;

static uint32_t plantTick;
static uint32_t cloudTick;
static uint32_t birdTick;
static uint32_t bumpOrDepressionTick;
static uint32_t dirtTexTick;

static bool flipStatus;
static uint16_t nextPlantTickDel;
static uint16_t nextCloudTickDel;
static uint16_t nextBirdTickDel;
static uint16_t nextBumpOrDepressionTickDel;
static uint16_t nextDirtTexTickDel;

#define STANDING 0
#define RUNNING 1
#define FIRING 2
#define JUMPING 3
#define GLIDING 4
#define DODGING 5
#define CRAWLING 6
#define DIED 7
static uint8_t dinoState;

static uint8_t groundLength;
static float overallSpeed;

static GameObj *ptr;

static GameObj *dinoHeader;
static GameObj *fireHeader;
static GameObj *cloudHeader;
static GameObj *plantHeader;
static GameObj *birdHeader;
static GameObj *signsHeader;
static GameObj *dirtTexHeader;
static GameObj *bumpAndDepressionHeader;

void RenderDino(GameObj *dino, uint8_t dinoState, bool isDead);
bool DinoGetsStuck();
void MeltPlants();
void RenderUI();

void GenerateGameBuffers() {
	dinoHeader = GenLoopBuf(1);
	fireHeader = GenLoopBuf(1);

	cloudHeader = GenLoopBuf(2);
	plantHeader = GenLoopBuf(4);
	birdHeader = GenLoopBuf(2);
	signsHeader = GenLoopBuf(2);
	dirtTexHeader = GenLoopBuf(12);
	bumpAndDepressionHeader = GenLoopBuf(4);
}

void GamePrep(LS013B4DN04 *display) {
	flipStatus = 1;

	nextPlantTickDel = 0;
	nextCloudTickDel = 0;
	nextDirtTexTickDel = 0;
	nextBirdTickDel = 0;
	nextBumpOrDepressionTickDel = 0;

	plantTick = 0;
	cloudTick = 0;
	dirtTexTick = 0;
	birdTick = 0;
	bumpOrDepressionTick = 0;

	groundLength = 29;
	tick = 0;
	overallSpeed = 1;

	HeaderInit(dinoHeader, (uint8_t*) DinoAssets, 4, 22, 14);
	HeaderInit(fireHeader, (uint8_t*) FireAssets, 9, 25, 2);
	HeaderInit(cloudHeader, (uint8_t*) CloudAssets, 6, 14, 1);
	HeaderInit(plantHeader, (uint8_t*) PlantAssets, 2, 22, 5);
	HeaderInit(birdHeader, (uint8_t*) BirdAssets, 3, 15, 2);
	HeaderInit(signsHeader, (uint8_t*) SignsAssets, 2, 19, 1);
	HeaderInit(dirtTexHeader, (uint8_t*) DirtTextureAssets, 1, 1, 6);
	HeaderInit(bumpAndDepressionHeader, (uint8_t*) BumpAndDepressionAssets, 1,
			2, 2);

	dinoHeader = Append(dinoHeader, DinoNormalStand, DinoXPosDefault,
			dinoGroundPos);
	fireHeader = Append(fireHeader, CloudNormal, 24, 52);

	LCD_Fill(flipStatus);
	LCD_DrawLine(77, 0, 29, DRAWMODE_ADD, flipStatus);

	LCD_LoadObjs(dinoHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);

	LCD_Print("a\tbit\tbetter", 6, 10, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);

	LCD_UpdateFull(display);
	while (!GetButtonDown(BUTTON_2, 1))
		;
//
//	// Flip screen
//	for (uint8_t i = 0; i < 3; i++) {
//		HAL_Delay(100);
//		LCD_Invert();
//		LCD_UpdateFull(display);
//	}

	dinoVel = initVel;
	dinoState = JUMPING;
}

uint8_t GameTick(LS013B4DN04 *display) {

	// Day and night invertion
//	flipStatus = ((tick / 800) % 3 == 2) ? 0 : 1;

	LCD_Fill(flipStatus);

	// Roll ground plane
	if (groundLength < 96) {

		LCD_DrawLine(77, 0, groundLength, DRAWMODE_ADD, flipStatus);
		groundLength++;
	} else {

		// Still ground plane
		LCD_DrawLine(77, 0, 96, DRAWMODE_ADD, flipStatus);
	}

	switch (dinoState) {

	case JUMPING:

		dinoVel -=
				GetButton(BUTTON_2) ? (gravity * longPressGravityMul) : gravity;
		dinoHeader->y -= dinoVel;

		if (GetButtonDown(BUTTON_1, 2))
			dinoState = GLIDING;

		// Dino landed
		if (dinoHeader->y > dinoGroundPos)
			dinoState = RUNNING;

		break;

	case GLIDING:

		if (dinoVel < 0) {
			dinoVel -= gravity;
			dinoVel += -dinoVel * parachuteGrag;
		} else {
			dinoVel -= gravity;
		}

		dinoHeader->y -= dinoVel;

		if (!GetButton(BUTTON_1))
			dinoState = JUMPING;
		else if (GetButton(BUTTON_2))
			dinoState = DODGING;

		// Dino landed
		if (dinoHeader->y > dinoGroundPos)
			dinoState = CRAWLING;
		break;

	case DODGING:

		// In air
		if (dinoHeader->y <= dinoGroundPos) {
			dinoVel -= gravity * dodgeGravityMul;
			dinoHeader->y -= dinoVel;
		}

		if (!GetButton(BUTTON_1))
			dinoState = JUMPING;
		else if (!GetButton(BUTTON_2))
			dinoState = GLIDING;

		// Dino landed
		if (dinoHeader->y > dinoGroundPos) {
			dinoState = CRAWLING;
		}

		break;

	case CRAWLING:
		if (!GetButton(BUTTON_1)) {
			dinoState = RUNNING;
		} else if (GetButtonDown(BUTTON_2, 5)) {
			dinoState = FIRING;
		}
		break;

	case RUNNING:
		dinoHeader->y = dinoGroundPos;
		dinoVel = 0;

		if (GetButton(BUTTON_1))
			dinoState = CRAWLING;
		else if (GetButtonDown(BUTTON_2, 4)) {
			dinoVel = initVel;
			dinoState = JUMPING;
		}

		break;

	case FIRING:
		dinoHeader->y = dinoGroundPos;
		dinoVel = 0;

		if (!GetButton(BUTTON_1))
			dinoState = RUNNING;
		else if (!GetButton(BUTTON_2))
			dinoState = CRAWLING;

		break;
	}

// Plant generation
	if (tick - terrainGenPreTick - plantTick == nextPlantTickDel) {
		plantHeader = Append(plantHeader, PlantNormal, 96, 59);
		nextPlantTickDel = Random(tick, 80, 330);
		plantTick = tick - terrainGenPreTick;
	}
// Cloud generation
	if (tick - terrainGenPreTick - cloudTick == nextCloudTickDel) {
		cloudHeader = Append(cloudHeader, CloudNormal, 96,
				Random(tick, 12, 20));
		nextCloudTickDel = Random(tick, 1200, 2000);
		cloudTick = tick - terrainGenPreTick;
	}
// Dirt texture generation
	if (tick - terrainGenPreTick - dirtTexTick == nextDirtTexTickDel) {

		dirtTexHeader = Append(dirtTexHeader, Random(tick, 2, 6), 96,
				Random(tick, 83, 90));

		nextDirtTexTickDel = Random(tick, 8, 20);
		dirtTexTick = tick - terrainGenPreTick;
	}
// Bumps and depressions generation
	if (tick - terrainGenPreTick - bumpOrDepressionTick
			== nextBumpOrDepressionTickDel) {
		if (Random(tick, 0, 1)) {
			bumpAndDepressionHeader = Append(bumpAndDepressionHeader,
			Bump, 96, 75);
		} else {
			bumpAndDepressionHeader = Append(bumpAndDepressionHeader,
			Depression, 96, 78);
		}

		nextBumpOrDepressionTickDel = Random(tick, 20, 150);
		bumpOrDepressionTick = tick - terrainGenPreTick;
	}

// Bird Sign Generation
	if (tick - birdGenPreTick - birdTick == nextBirdTickDel) {
		signsHeader = Append(signsHeader, BirdSign, 96, Random(tick, 61, 62));
	}
// Bird generation
	if (tick - birdGenPreTick - birdTick - 200 == nextBirdTickDel) {

		birdHeader = Append(birdHeader, BirdWithWingsDownwards, 96,
				Random(tick, 10, 51));

		nextBirdTickDel = Random(tick, 250, 800);
		birdTick = tick - birdGenPreTick;
	}

// Ground objs shift
	plantHeader = ShiftX(plantHeader, -1 * overallSpeed);
	dirtTexHeader = ShiftX(dirtTexHeader, -1 * overallSpeed);
	signsHeader = ShiftX(signsHeader, -1 * overallSpeed);
	bumpAndDepressionHeader = ShiftX(bumpAndDepressionHeader,
			-1 * overallSpeed);
	birdHeader = ShiftX(birdHeader, -1.2 * overallSpeed);

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

	if (dinoState == FIRING) {

		UpdateHeaderBmpIndex(fireHeader,
				(tick / (int) (12 / overallSpeed)) % 2);
		LCD_LoadObjs(fireHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);
	}

	UpdateAllBmpIndexs(birdHeader,
	BirdWithWingsDownwards + (tick / (int) (8 / overallSpeed)) % 2,
	NoIgnoringIndex);

	LCD_LoadObjs(plantHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);
	LCD_LoadObjs(birdHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);
	LCD_LoadObjs(signsHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);
	LCD_LoadObjs(cloudHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);
	LCD_LoadObjs(dirtTexHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);
	LCD_LoadObjs(bumpAndDepressionHeader, DRAWMODE_ADD, REPEATMODE_NONE,
			flipStatus);

	MeltPlants();
	if (DinoGetsStuck())
		goto Dead;

	RenderDino(dinoHeader, dinoState, 0);
	RenderUI();

	tick++;
	LCD_UpdateFull(display);
	return DINO_IS_ALIVE;

	Dead: LCD_SaveBuf();
	// Redraw Dino
	while (dinoHeader->y < dinoGroundPos) {
		LCD_LoadBuf();
		dinoHeader->y++;
		RenderDino(dinoHeader, dinoState, 1);
		LCD_UpdateFull(display);
	}

	LCD_LoadBuf();
	RenderDino(dinoHeader, dinoState, 1);

	LCD_UpdateFull(display);

	HAL_Delay(300);

	// Flip screen
	for (uint8_t i = 0; i < 2; i++) {
		HAL_Delay(100);
		LCD_Invert();
		LCD_UpdateFull(display);
	}

	for (uint8_t l = 96; l > 28; l--) {
		uint8_t delayTime = ceil((float) (96 - l) * 8 / 67);
		LCD_DrawLine(77, l, 1, DRAWMODE_CULL, flipStatus);
		LCD_UpdateLine(display, 77);
		HAL_Delay(delayTime);
		if (GetButtonDown(BUTTON_2, 6))
			break;
	}
	return DINO_IS_DEAD;
}

void RenderUI(){
	LCD_Print("gas", 2, 2, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);
	LCD_DrawRect(24, 3, 60, 8, DRAWMODE_ADD, flipStatus);
}

void RenderDino(GameObj *dino, uint8_t dinoState, bool isDead) {
	if (!isDead) {
		switch (dinoState) {
		case RUNNING:
			LCD_DrawLine(77, 8, 8, DRAWMODE_CULL, flipStatus);
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
		case CRAWLING:
			LCD_DrawLine(77, 8, 8, DRAWMODE_CULL, flipStatus);
		case DODGING:
			UpdateHeaderBmpIndex(dino,
			DinoDodgingL + (tick / (int) (12 / overallSpeed)) % 2);
			dinoHeader->x = DinoXPosWhenDodging;
			break;
		case FIRING:
			LCD_DrawLine(77, 8, 8, DRAWMODE_CULL, flipStatus);
			UpdateHeaderBmpIndex(dino,
			DinoFiringL + (tick / (int) (12 / overallSpeed)) % 2);
			dinoHeader->x = DinoXPosDefault;
			break;
		}
	} else if (isDead) {
		switch (dinoState) {
		case RUNNING:
			LCD_DrawLine(77, 8, 8, DRAWMODE_CULL, flipStatus);
		case JUMPING:
			UpdateHeaderBmpIndex(dino, DinoNormalDead);
			dinoHeader->x = DinoXPosDefault;
			break;
		case GLIDING:
			UpdateHeaderBmpIndex(dino, DinoGlidingDead);
			dinoHeader->x = DinoXPosWhenGliding;
			break;
		case CRAWLING:
			LCD_DrawLine(77, 8, 8, DRAWMODE_CULL, flipStatus);
		case DODGING:
			UpdateHeaderBmpIndex(dino, DinoDodgingDead);
			dinoHeader->x = DinoXPosWhenDodging;
			break;
		case FIRING:
			LCD_DrawLine(77, 8, 8, DRAWMODE_CULL, flipStatus);
			UpdateHeaderBmpIndex(dino, DinoFiringDead);
			dinoHeader->x = DinoXPosDefault;
			break;
		}
	}

	LCD_LoadObjs(dinoHeader, DRAWMODE_ADD, REPEATMODE_NONE, flipStatus);
}

void MeltPlants() {
	// Loop through GroundFires and Plants, shrink plants
	ptr = plantHeader;
	for (;;) {
		if (ptr->full) {
			if (ptr->index != PlantNormal) {
				if (tick % 6 == 0)
					ImgIndexRightShift(ptr, 1);
			} else if (IsOverlapping(24, 52, 95, 76, ptr->x, ptr->y, ptr->x + 9,
					ptr->y + 21) && dinoState == FIRING) {
				ImgIndexRightShift(ptr, 1);
			}

		}

		// If looped through all / next buffer is empty
		if (!ptr->next->full || ptr->next == plantHeader) {
			break;
		}
		ptr = ptr->next;
	}
}

bool DinoGetsStuck() {
// Stuck in plants?
ptr = plantHeader;
for (;;) {
	if (ptr->full && ptr->index == PlantNormal) {
		switch (dinoState) {
		case JUMPING:
		case RUNNING:
		case FIRING:
			if (IsOverlapping(dinoHeader->x + 10, dinoHeader->y + 2,
					dinoHeader->x + 17, dinoHeader->y + 17, ptr->x, 59,
					ptr->x + 9, 59 + 21)) {
				return 1;
			}
			break;

		case GLIDING:
		case DODGING:
		case CRAWLING:
			if (IsOverlapping(dinoHeader->x + 9, dinoHeader->y + 11,
					dinoHeader->x + 30, dinoHeader->y + 17, ptr->x, 59,
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

// Stuck in birds?
ptr = birdHeader;
for (;;) {
	if (ptr->full) {
		switch (dinoState) {
		case JUMPING:
		case RUNNING:
		case FIRING:
			if (IsOverlapping(dinoHeader->x + 10, dinoHeader->y + 2,
					dinoHeader->x + 17, dinoHeader->y + 17, ptr->x + 2,
					ptr->y + 3, ptr->x + 14, ptr->y + 12)) {
				return 1;
			}
			break;

		case GLIDING:
		case DODGING:
			if (IsOverlapping(dinoHeader->x + 9, dinoHeader->y + 11,
					dinoHeader->x + 30, dinoHeader->y + 17, ptr->x + 2,
					ptr->y + 3, ptr->x + 14, ptr->y + 12)) {
				return 1;
			}
			break;
		}

	}
	// If looped through all / next buffer is empty
	if (!ptr->next->full || ptr->next == birdHeader) {
		break;
	}
	ptr = ptr->next;
}

return 0;
}
