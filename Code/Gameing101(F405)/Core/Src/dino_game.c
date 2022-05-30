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
static GameObj *smallPlantHeader;
static GameObj *birdHeader;
static GameObj *signsHeader;
static GameObj *dirtTexHeader;
static GameObj *bumpAndDepressionHeader;

void RenderDino(GameObj *dino, uint8_t dinoState, bool isDead);
bool DinoGetsStuck();
void MeltPlants();
void MeltBirds();
void RenderUI();
void GenerateGameElements();

void GenerateGameBuffers() {
	dinoHeader = GenLoopBuf((uint8_t*) DinoAssets, 4, 22, 14, 1);
	fireHeader = GenLoopBuf((uint8_t*) FireAssets, 9, 25, 2, 1);

	cloudHeader = GenLoopBuf((uint8_t*) CloudAssets, 6, 14, 1, 2);
	smallPlantHeader = GenLoopBuf((uint8_t*) SmallPlantAssets, 2, 22, 6, 4);
	birdHeader = GenLoopBuf((uint8_t*) BirdAssets, 3, 15, 3, 2);
	signsHeader = GenLoopBuf((uint8_t*) SignsAssets, 2, 19, 1, 2);
	dirtTexHeader = GenLoopBuf((uint8_t*) DirtTextureAssets, 1, 1, 6, 12);
	bumpAndDepressionHeader = GenLoopBuf((uint8_t*) BumpAndDepressionAssets, 1,
			2, 2, 4);
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

	DisableAll(dinoHeader);
	DisableAll(fireHeader);
	DisableAll(cloudHeader);
	DisableAll(smallPlantHeader);
	DisableAll(birdHeader);
	DisableAll(signsHeader);
	DisableAll(dirtTexHeader);
	DisableAll(bumpAndDepressionHeader);

	Append(dinoHeader, DinoNormalStand, DinoXPosDefault, dinoGroundPos, 0, 0);
	Append(fireHeader, CloudNormal, 24, 52, 0, 0);

	LCD_Fill(flipStatus);
	LCD_DrawLine(77, 0, 29, DRAWMODE_ADD, flipStatus);

	LCD_LoadObjs(dinoHeader, DRAWMODE_ADD, flipStatus);

	LCD_Print("So\there's\nphysics", 4, 2, DRAWMODE_ADD, flipStatus);

	LCD_UpdateFull(display);
	while (!GetButtonDown(BUTTON_2, 0))
		;

	dinoHeader->transform.velocity.y = -initVel;
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

		dinoHeader->transform.gravity.y =
				GetButton(BUTTON_2) ? (gravity * longPressGravityMul) : gravity;
		CalculatePosition(dinoHeader);

		if (GetButtonDown(BUTTON_1, 0))
			dinoState = FIRING;
		else if (GetButtonDown(BUTTON_2, 1))
			dinoState = GLIDING;

		// Dino landed
		if (dinoHeader->transform.position.y > dinoGroundPos)
			dinoState = RUNNING;

		break;

	case GLIDING:

		dinoHeader->transform.gravity.y = 0;
		dinoHeader->transform.velocity.y = 0.2;

		CalculatePosition(dinoHeader);

		if (!GetButton(BUTTON_2))
			dinoState = JUMPING;
		else if (GetButton(BUTTON_1))
			dinoState = FIRING;

		// Dino landed
		if (dinoHeader->transform.position.y > dinoGroundPos)
			dinoState = RUNNING;
		break;

//	case DODGING:
//
//		// In air
//		if (dinoHeader->transform.position.y <= dinoGroundPos) {
//			dinoVel -= gravity * dodgeGravityMul;
//			dinoHeader->transform.position.y -= dinoVel;
//		}
//
//		if (!GetButton(BUTTON_1))
//			dinoState = JUMPING;
//		else if (!GetButton(BUTTON_2))
//			dinoState = GLIDING;
//
//		// Dino landed
//		if (dinoHeader->transform.position.y > dinoGroundPos) {
//			dinoState = CRAWLING;
//		}
//
//		break;

	case FIRING:
		// In air
		if (dinoHeader->transform.position.y < dinoGroundPos) {
			dinoHeader->transform.gravity.y =
					GetButton(BUTTON_2) ?
							(gravity * longPressGravityMul) : gravity;
			CalculatePosition(dinoHeader);

			if (!GetButton(BUTTON_1))
				dinoState = JUMPING;
		}

		// On ground
		else {
			dinoHeader->transform.gravity.y = 0;
			dinoHeader->transform.velocity.y = 0;

			dinoHeader->transform.position.y = dinoGroundPos;

			if (!GetButton(BUTTON_1))
				dinoState = RUNNING;
			else if (GetButtonDown(BUTTON_2, 2)) {
				dinoHeader->transform.position.y -= 1;
			}

		}

		break;

//	case CRAWLING:
//		if (!GetButton(BUTTON_1)) {
//			dinoState = RUNNING;
//		} else if (!GetButton(BUTTON_2)) {
//			dinoState = RUNNING;
//		}
//		break;

	case RUNNING:

		dinoHeader->transform.gravity.y = 0;
		dinoHeader->transform.velocity.y = 0;

		dinoHeader->transform.position.y = dinoGroundPos;

		if (GetButtonDown(BUTTON_1, 1))
			dinoState = FIRING;
		else if (GetButtonDown(BUTTON_2, 3)) {
			dinoHeader->transform.velocity.y = -initVel;
			dinoState = JUMPING;
		}

		break;

	}

	GenerateGameElements();

	CalculatePositions(smallPlantHeader);
	CalculatePositions(dirtTexHeader);
	CalculatePositions(signsHeader);
	CalculatePositions(bumpAndDepressionHeader);
	CalculatePositions(birdHeader);
	CalculatePositions(cloudHeader);

	// Cull plant
	ptr = smallPlantHeader;
	for (;;) {
		if (ptr->isOccupied) {
			for (uint8_t y = 71; y <= 77; y++) {
				LCD_DrawLine(y, ptr->transform.position.x + 2, 6, DRAWMODE_CULL,
						flipStatus);
			}
		}
		// If looped through all / next buffer is empty
		if (!ptr->next->isOccupied || ptr->next == smallPlantHeader)
			break;

		ptr = ptr->next;
	}

	// Cull bumps
	ptr = bumpAndDepressionHeader;
	for (;;) {
		if (ptr->isOccupied) {

			LCD_DrawLine(77, ptr->transform.position.x + 1, 6, DRAWMODE_CULL,
					flipStatus);
		}
		// If looped through all / next buffer is empty
		if (!ptr->next->isOccupied || ptr->next == bumpAndDepressionHeader)
			break;

		ptr = ptr->next;
	}

	if (dinoState == FIRING) {
		fireHeader->transform.position.y = dinoHeader->transform.position.y - 6;
		UpdateHeaderBmpIndex(fireHeader,
				(tick / (int) (12 / overallSpeed)) % 2);
		LCD_LoadObjs(fireHeader, DRAWMODE_ADD, flipStatus);
	}

	UpdateAllBmpIndexs(birdHeader,
	BirdWithWingsDownwards + (tick / (int) (8 / overallSpeed)) % 2,
	CookedBird);

	LCD_LoadObjs(smallPlantHeader, DRAWMODE_ADD, flipStatus);
	LCD_LoadObjs(birdHeader, DRAWMODE_ADD, flipStatus);
	LCD_LoadObjs(signsHeader, DRAWMODE_ADD, flipStatus);
	LCD_LoadObjs(cloudHeader, DRAWMODE_ADD, flipStatus);
	LCD_LoadObjs(dirtTexHeader, DRAWMODE_ADD, flipStatus);
	LCD_LoadObjs(bumpAndDepressionHeader, DRAWMODE_ADD, flipStatus);

	MeltPlants();
	MeltBirds();

	if (DinoGetsStuck())
		goto Dead;

	RenderDino(dinoHeader, dinoState, 0);
//	RenderUI();

	tick++;
	LCD_UpdateFull(display);
	return DINO_IS_ALIVE;

	Dead: LCD_SaveBuf();
	// Redraw Dino
	while (dinoHeader->transform.position.y < dinoGroundPos) {
		LCD_LoadBuf();
		dinoHeader->transform.position.y++;
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
		if (GetButtonDown(BUTTON_2, 4))
			break;
	}
	return DINO_IS_DEAD;
}

void RenderUI() {
	LCD_Print("gas", 2, 2, DRAWMODE_ADD, flipStatus);
	LCD_DrawRect(24, 3, 60, 8, DRAWMODE_ADD, flipStatus);
}

void GenerateGameElements() {
	// Plant generation
	if (tick - terrainGenPreTick - plantTick == nextPlantTickDel) {
		Append(smallPlantHeader,
				Random(tick, 0, SmallPlantShrinkStartIndex - 1), 96, 59,
				-1 * overallSpeed, 0);

		nextPlantTickDel = Random(tick, 80, 330);
		plantTick = tick - terrainGenPreTick;
	}

	// Cloud generation
	if (tick - terrainGenPreTick - cloudTick == nextCloudTickDel) {
		Append(cloudHeader, CloudNormal, 96, Random(tick, 12, 20),
				-0.1 * overallSpeed, 0);

		nextCloudTickDel = Random(tick, 1200, 2000);
		cloudTick = tick - terrainGenPreTick;
	}

	// Dirt texture generation
	if (tick - terrainGenPreTick - dirtTexTick == nextDirtTexTickDel) {

		Append(dirtTexHeader, Random(tick, 0, 5), 96, Random(tick, 83, 90),
				-1 * overallSpeed, 0);

		nextDirtTexTickDel = Random(tick, 8, 20);
		dirtTexTick = tick - terrainGenPreTick;
	}

	// Bumps and depressions generation
	if (tick - terrainGenPreTick - bumpOrDepressionTick
			== nextBumpOrDepressionTickDel) {
		if (Random(tick, 0, 1)) {
			Append(bumpAndDepressionHeader,
			Bump, 96, 75, -1 * overallSpeed, 0);
		} else {
			Append(bumpAndDepressionHeader,
			Depression, 96, 78, -1 * overallSpeed, 0);
		}

		nextBumpOrDepressionTickDel = Random(tick, 20, 150);
		bumpOrDepressionTick = tick - terrainGenPreTick;
	}

	// Bird Sign Generation
	if (tick - birdGenPreTick - birdTick == nextBirdTickDel) {
		Append(signsHeader, BirdSign, 96, Random(tick, 61, 62),
				-1 * overallSpeed, 0);
	}

	// Bird generation
	if (tick - birdGenPreTick - birdTick - 120 == nextBirdTickDel) {

		Append(birdHeader, BirdWithWingsDownwards, 96, Random(tick, 10, 51),
				-1.2 * overallSpeed, 0);

		nextBirdTickDel = Random(tick, 250, 800);
		birdTick = tick - birdGenPreTick;
	}
}

void RenderDino(GameObj *dino, uint8_t dinoState, bool isDead) {
	if (!isDead) {
		switch (dinoState) {
		case RUNNING:
			LCD_DrawLine(77, 8, 8, DRAWMODE_CULL, flipStatus);
			UpdateHeaderBmpIndex(dino,
					(tick / (int) (12 / overallSpeed)) % 2 + 1);
			dinoHeader->transform.position.x = DinoXPosDefault;
			break;
		case JUMPING:
			UpdateHeaderBmpIndex(dino, DinoNormalStand);
			dinoHeader->transform.position.x = DinoXPosDefault;
			break;
		case GLIDING:
			UpdateHeaderBmpIndex(dino, DinoGliding);
			dinoHeader->transform.position.x = DinoXPosWhenGliding;
			break;
		case CRAWLING:
			LCD_DrawLine(77, 8, 8, DRAWMODE_CULL, flipStatus);
		case DODGING:
			UpdateHeaderBmpIndex(dino,
			DinoDodgingL + (tick / (int) (12 / overallSpeed)) % 2);
			dinoHeader->transform.position.x = DinoXPosWhenDodging;
			break;
		case FIRING:
			if (dinoHeader->transform.position.y == dinoGroundPos) {
				LCD_DrawLine(77, 8, 8, DRAWMODE_CULL, flipStatus);
			}
			UpdateHeaderBmpIndex(dino,
			DinoFiringL + (tick / (int) (12 / overallSpeed)) % 2);
			dinoHeader->transform.position.x = DinoXPosDefault;
			break;
		}
	} else if (isDead) {
		switch (dinoState) {
		case RUNNING:
			LCD_DrawLine(77, 8, 8, DRAWMODE_CULL, flipStatus);
		case JUMPING:
			UpdateHeaderBmpIndex(dino, DinoNormalDead);
			dinoHeader->transform.position.x = DinoXPosDefault;
			break;
		case GLIDING:
			UpdateHeaderBmpIndex(dino, DinoGlidingDead);
			dinoHeader->transform.position.x = DinoXPosWhenGliding;
			break;
		case CRAWLING:
			LCD_DrawLine(77, 8, 8, DRAWMODE_CULL, flipStatus);
		case DODGING:
			UpdateHeaderBmpIndex(dino, DinoDodgingDead);
			dinoHeader->transform.position.x = DinoXPosWhenDodging;
			break;
		case FIRING:
			LCD_DrawLine(77, 8, 8, DRAWMODE_CULL, flipStatus);
			UpdateHeaderBmpIndex(dino, DinoFiringDead);
			dinoHeader->transform.position.x = DinoXPosDefault;
			break;
		}
	}

	LCD_LoadObjs(dinoHeader, DRAWMODE_ADD, flipStatus);
}

void MeltPlants() {
	// Loop through GroundFires and Plants, shrink plants
	ptr = smallPlantHeader;
	for (;;) {
		if (ptr->isOccupied) {
			if (ptr->currentIndex >= SmallPlantShrinkStartIndex) {
				if (tick % 6 == 0)
					ImgIndexRightShift(ptr, 1);
			} else if (IsOverlapping(fireHeader->transform.position.x + 14,
					fireHeader->transform.position.y + 9,
					fireHeader->transform.position.x + 64,
					fireHeader->transform.position.y + 23,
					ptr->transform.position.x, ptr->transform.position.y,
					ptr->transform.position.x + 9,
					ptr->transform.position.y + 21) && dinoState == FIRING) {

				UpdateHeaderBmpIndex(ptr, SmallPlantShrinkStartIndex);
			}

		}

		// If looped through all / next buffer is empty
		if (!ptr->next->isOccupied || ptr->next == smallPlantHeader) {
			break;
		}
		ptr = ptr->next;
	}
}

void MeltBirds() {
	// Loop through GroundFires and Plants, shrink plants
	ptr = birdHeader;
	for (;;) {
		if (ptr->isOccupied && ptr->currentIndex != CookedBird) {
			if (IsOverlapping(fireHeader->transform.position.x + 14,
					fireHeader->transform.position.y + 9,
					fireHeader->transform.position.x + 64,
					fireHeader->transform.position.y + 23,
					ptr->transform.position.x, ptr->transform.position.y,
					ptr->transform.position.x + 18,
					ptr->transform.position.y + 12) && dinoState == FIRING) {

				UpdateHeaderBmpIndex(ptr, CookedBird);
				ptr->transform.gravity.y = gravity * 0.8;
				ptr->transform.velocity.y = -0.5;
				ptr->transform.velocity.x = -0.2;
			}
		}

		// If looped through all / next buffer is empty
		if (!ptr->next->isOccupied || ptr->next == birdHeader) {
			break;
		}
		ptr = ptr->next;
	}
}

bool DinoGetsStuck() {
// Stuck in plants?
	ptr = smallPlantHeader;
	for (;;) {
		if (ptr->isOccupied && ptr->currentIndex < SmallPlantShrinkStartIndex) {
			switch (dinoState) {
			case JUMPING:
			case RUNNING:
			case FIRING:
				if (IsOverlapping(dinoHeader->transform.position.x + 10,
						dinoHeader->transform.position.y + 2,
						dinoHeader->transform.position.x + 17,
						dinoHeader->transform.position.y + 17,
						ptr->transform.position.x, 59,
						ptr->transform.position.x + 9, 59 + 21)) {
					return 1;
				}
				break;

			case GLIDING:
			case DODGING:
			case CRAWLING:
				if (IsOverlapping(dinoHeader->transform.position.x + 9,
						dinoHeader->transform.position.y + 11,
						dinoHeader->transform.position.x + 30,
						dinoHeader->transform.position.y + 17,
						ptr->transform.position.x, 59,
						ptr->transform.position.x + 9, 59 + 21)) {
					return 1;
				}
				break;
			}

		}
		// If looped through all / next buffer is empty
		if (!ptr->next->isOccupied || ptr->next == smallPlantHeader) {
			break;
		}
		ptr = ptr->next;
	}

// Stuck in birds?
	ptr = birdHeader;
	for (;;) {
		if (ptr->isOccupied && ptr->currentIndex != CookedBird) {
			switch (dinoState) {
			case JUMPING:
			case RUNNING:
			case FIRING:
				if (IsOverlapping(dinoHeader->transform.position.x + 10,
						dinoHeader->transform.position.y + 2,
						dinoHeader->transform.position.x + 17,
						dinoHeader->transform.position.y + 17,
						ptr->transform.position.x + 2,
						ptr->transform.position.y + 3,
						ptr->transform.position.x + 14,
						ptr->transform.position.y + 12)) {
					return 1;
				}
				break;

			case GLIDING:
			case DODGING:
				if (IsOverlapping(dinoHeader->transform.position.x + 9,
						dinoHeader->transform.position.y + 11,
						dinoHeader->transform.position.x + 30,
						dinoHeader->transform.position.y + 17,
						ptr->transform.position.x + 2,
						ptr->transform.position.y + 3,
						ptr->transform.position.x + 14,
						ptr->transform.position.y + 12)) {
					return 1;
				}
				break;
			}

		}
		// If looped through all / next buffer is empty
		if (!ptr->next->isOccupied || ptr->next == birdHeader) {
			break;
		}
		ptr = ptr->next;
	}

	return 0;
}
