/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LS013B4DN04.h"
#include "image.h"
#include "gamelogic.h"
#include <stdlib.h>
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define CS_Pin GPIO_PIN_4
#define DISP_Pin GPIO_PIN_3
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PLANT_BUF_SIZE 4
#define CLOUD_BUF_SIZE 2

#define KEY0_STATE  HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin)
#define KEY1_STATE  HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)

#define LEDB_ON  HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET)
#define LEDB_OFF  HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET)
#define LEDB_TOGGLE  HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin)

#define FIRE_BUTTON_PRESSED KeyState[0]
#define JUMP_BUTTON_PRESSED KeyPressed[1]

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */
LS013B4DN04 MemDisp;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const float JumpTickMax = 80;
const float DinoJumpHeight = 40;
const float DinoGroundPos = 58;

unsigned long tick = 0;
static bool KeyState[2] = { 0, 0 };
static bool KeyPressed[2] = { 0, 0 };
static bool KeyReleased[2] = { 0, 0 };

//static int a, b;
//GameObj* plantHeader
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_SPI1_Init();
	MX_TIM1_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim1);

	// ALL GPIO AND BUSES MUST BE INITED BEFORE CALL THIS FUNCTION
	LCD_Init(&MemDisp, &hspi1, GPIOA, CS_Pin);

	static bool isJumping, dinoIsDead;
	static uint8_t jumpTick;
	static short dinoVerticalMovement;
	static float overallSpeed;

	GameObj *dinoHeader = GenLoopBuf(1);
	ObjInit(dinoHeader, NULL, 4, -1, 3, 22);

	GameObj *fireHeader = GenLoopBuf(1);
	ObjInit(fireHeader, NULL, 24, 52, 9, 25);

	GameObj *cloudHeader = GenLoopBuf(CLOUD_BUF_SIZE);
	ObjInit(cloudHeader, (uint8_t*) Cloud, -1, 18, 6, 14);

	GameObj *plantHeader = GenLoopBuf(PLANT_BUF_SIZE);
	ObjInit(plantHeader, (uint8_t*) Plant1, -1, 59, 2, 22);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
		/* USER CODE BEGIN 3 */
		LCD_LoadFull((uint8_t*) Title);
		LCD_Update(&MemDisp);
		while (!JUMP_BUTTON_PRESSED);
		JUMP_BUTTON_PRESSED= 0;

		isJumping = 0, dinoIsDead = 0;
		jumpTick = 0;
		overallSpeed = 1;

		dinoHeader->y = DinoGroundPos;
		plantHeader->x = 96;
		cloudHeader->x = 96;

		while (1) {
			tick++;

			// Speed Gradual Control
			if (overallSpeed < 1.2) {
				overallSpeed += 0.001;
			}

			if (JUMP_BUTTON_PRESSED) {
				if(!isJumping) {
					isJumping = 1;
				}
				JUMP_BUTTON_PRESSED = 0;
			}

			dinoVerticalMovement = DinoGroundPos;
			if (isJumping) {
				if (jumpTick < JumpTickMax / overallSpeed - 1) {
					jumpTick++;
					dinoVerticalMovement = jumpTick
							* (jumpTick - JumpTickMax / overallSpeed)
							* (4
									/ ((JumpTickMax / overallSpeed)
											* (JumpTickMax / overallSpeed)))
							* DinoJumpHeight + DinoGroundPos;
				} else {
					isJumping = 0;
					jumpTick = 0;
				}
			}

			if (tick % 80 == 0) {
				plantHeader = Append(plantHeader, 96);
			}
			if (tick % 800 == 0) {
				cloudHeader = Append(cloudHeader, 96);
			}

			plantHeader = ShiftX(plantHeader, -0.8 * overallSpeed);
			cloudHeader = ShiftX(cloudHeader, -0.1 * overallSpeed);
			dinoHeader->y = dinoVerticalMovement;

			// Reset canvas
			LCD_Fill(true);
			LCD_DrawLine(77, 0, 96, DRAWMODE_ADD);

			// Add culling masks
			// Plant
//			LCD_DrawLine(77, myPlant.x + 2, 6, DRAWMODE_CULL);
			// Dino
			LCD_DrawLine(dinoHeader->y + 19, dinoHeader->x + 3, 10,
					DRAWMODE_CULL);

			// Render fire
			if (!isJumping) {
				if (FIRE_BUTTON_PRESSED) {
					fireHeader->bmp = (uint8_t*) Fire[(tick / (int)(30 / overallSpeed)) % 2];
					LCD_LoadObj(fireHeader, DRAWMODE_ADD, REPEATMODE_NONE);
				}
			}

//			if (IsOverlapping(myDino.x + 3, myDino.y, myDino.x + 23 - 7,
//					myDino.y + 21 - 4, myPlant.x, 59, myPlant.x + 9, 59 + 21)) {
//				dinoIsDead = 1;
//			}

			// Render dino!
			// Dino is dead
			if (dinoIsDead) {
				dinoHeader->bmp = (uint8_t*) DinoDead;
			}
			// Dino is jumping
			else if (isJumping) {
				dinoHeader->bmp = (uint8_t*) DinoNormalS;
			}
			// Fire dino
			else if (FIRE_BUTTON_PRESSED) {
				dinoHeader->bmp = (uint8_t*) DinoFireRunning[(tick / (int)(30 / overallSpeed)) % 2];
			}
			// Dino is running normally
			else {
				dinoHeader->bmp = (uint8_t*) DinoNormalRunning[(tick / (int)(30 / overallSpeed)) % 2];
			}

			// Render dino
			LCD_LoadObjs(dinoHeader, DRAWMODE_ADD, REPEATMODE_NONE);

			// Render clouds
			LCD_LoadObjs(cloudHeader, DRAWMODE_ADD, REPEATMODE_NONE);

			// Render plants
			LCD_LoadObjs(plantHeader, DRAWMODE_ADD, REPEATMODE_NONE);

			LCD_Update(&MemDisp);

			if (dinoIsDead) {
				while (!JUMP_BUTTON_PRESSED);
				JUMP_BUTTON_PRESSED = 0;
				break;
			}
		}
	}

}
/* USER CODE END 3 */

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void) {

	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}

/**
 * @brief TIM1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM1_Init(void) {

	/* USER CODE BEGIN TIM1_Init 0 */

	/* USER CODE END TIM1_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM1_Init 1 */

	/* USER CODE END TIM1_Init 1 */
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 1000 - 1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 100 - 1;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM1_Init 2 */

	/* USER CODE END TIM1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : LED_B_Pin CS_Pin */
	GPIO_InitStruct.Pin = LED_B_Pin | CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : KEY0_Pin KEY1_Pin */
	GPIO_InitStruct.Pin = KEY0_Pin | KEY1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void KeyScan() {

	static uint8_t KeyBuffer[2] = { 0x00, 0x00 };

	KeyBuffer[0] = ((KeyBuffer[0] << 1) | (KEY0_STATE & 0x01));
	KeyBuffer[1] = ((KeyBuffer[1] << 1) | (KEY1_STATE & 0x01));

	for (uint8_t j = 0; j < 2; j++) {
		if ((KeyBuffer[j] | 0xf0) == 0xff) {
			if (!KeyState[j]) {
				KeyPressed[j] = 1;
			}
			KeyState[j] = 1;
		} else if ((KeyBuffer[j] | 0xf0) == 0xf0) {
			if (KeyState[j]) {
				KeyReleased[j] = 1;
			}
			KeyState[j] = 0;
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == &htim1) {
//		LEDB_TOGGLE;
		KeyScan();

	}
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
