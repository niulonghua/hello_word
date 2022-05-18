
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* --------------------------------- Includes ---------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* --------------------------------- Exported Types ---------------------------------*/
/* USER CODE BEGIN Exported_Types */

/* USER CODE END Exported_Types */

/* --------------------------------- Exported Constants ---------------------------------*/
/********** GPIO Enum ***********/
typedef enum
{
    GPIO_DRIVING_4MA = 0,
    GPIO_DRIVING_8MA,
    GPIO_DRIVING_12MA,
    GPIO_DRIVING_16MA
}GPIO_DrivingType;	
	
typedef enum
{
    GPIO_IN = 0,
    GPIO_OUT
}GPIO_DirType;

/*!< GPIO pin level enumeration */
typedef enum
{
    GPIO_LEVEL_LOW = 0,
    GPIO_LEVEL_HIGH
}GPIO_LevelType;

typedef enum
{
    GPIO_FUN0 = 0,
    GPIO_FUN1,
    GPIO_FUN2,
    GPIO_FUN3
}GPIO_FunType;

/* USER CODE BEGIN Exported_Constants */

/* USER CODE END Exported_Constants */

/* --------------------------------- Exported Macros ---------------------------------*/
/* USER CODE BEGIN Exported_Macros */

/* USER CODE END Exported_Macros */

/* --------------------------------- Defines ---------------------------------*/

#define X1_UP_C_Pin GPIO_PA0
#define X2_UP_C_Pin GPIO_PA1
#define X3_UP_C_Pin GPIO_PA2
#define X4_UP_C_Pin GPIO_PA3
#define X5_UP_C_Pin GPIO_PA4
#define X6_UP_C_Pin GPIO_PA5
#define X8_IN_Pin GPIO_PD3
#define X9_IN_Pin GPIO_PD4
#define PWM_DAC_Pin GPIO_PD5
#define X12_IN_Pin GPIO_PD8
#define X12_UP_C_Pin GPIO_PD9
#define C_C_Pin GPIO_PB3
#define C_B_Pin GPIO_PB4
#define C_A_Pin GPIO_PB5
#define X11_IN_Pin GPIO_PB6
#define X8_OUT_Pin GPIO_PB7
#define X11_UP_C_Pin GPIO_PD10
#define X7_OUT_Pin GPIO_PB8
#define X7_IN_Pin GPIO_PB9
#define X10_IN_Pin GPIO_PB10
#define X3_OUT_Pin GPIO_PB11
#define X4_OUT_Pin GPIO_PB12
#define X5_OUT_Pin GPIO_PB13
#define X6_OUT_Pin GPIO_PB14
#define X7_X8_FR_Pin GPIO_PD11
#define X5_X6_FR_Pin GPIO_PD12
#define X3_X4_FR_Pin GPIO_PD13
#define X1_X2_FR_Pin GPIO_PD14
#define X2_OUT_Pin GPIO_PB15
#define X1_OUT_Pin GPIO_PC0
#define X6_IN_Pin GPIO_PC1
#define X5_IN_Pin GPIO_PC2
#define X4_IN_Pin GPIO_PC3
#define X3_IN_Pin GPIO_PC4
#define X2_IN_Pin GPIO_PC5
#define X1_IN_Pin GPIO_PC6
#define AI4_PD_C_Pin GPIO_PC8
#define AI3_PD_C_Pin GPIO_PD15
#define X9_UP_C_Pin GPIO_PE0
#define X8_UP_C_Pin GPIO_PE1
#define X10_UP_C_Pin GPIO_PE2
#define X7_UP_C_Pin GPIO_PD0
#define LED_RED_Pin GPIO_PD1
#define LED_GREEN_Pin GPIO_PD2

/* USER CODE BEGIN Defines */

/* USER CODE END Defines */

#ifdef __cplusplus
 extern "C" {
#endif
/* --------------------------------- Exported Function Prototypes ---------------------------------*/
/* USER CODE BEGIN Exported_Function_Prototypes */

/* USER CODE END Exported_Function_Prototypes */
void Error_Handler(char *, int);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT AutoChips *****END OF FILE****/
