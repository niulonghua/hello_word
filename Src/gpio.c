/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  * This software/firmware and related documentation ("AutoChips Software") are
  * protected under relevant copyright laws. The information contained herein is
  * confidential and proprietary to AutoChips Inc. and/or its licensors. Without
  * the prior written permission of AutoChips inc. and/or its licensors, any
  * reproduction, modification, use or disclosure of AutoChips Software, and
  * information contained herein, in whole or in part, shall be strictly
  * prohibited.
  *
  * AutoChips Inc. (C) 2021. All rights reserved.
  *
  * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
  * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AUTOCHIPS SOFTWARE")
  * RECEIVED FROM AUTOCHIPS AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
  * ON AN "AS-IS" BASIS ONLY. AUTOCHIPS EXPRESSLY DISCLAIMS ANY AND ALL
  * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
  * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
  * NONINFRINGEMENT. NEITHER DOES AUTOCHIPS PROVIDE ANY WARRANTY WHATSOEVER WITH
  * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
  * INCORPORATED IN, OR SUPPLIED WITH THE AUTOCHIPS SOFTWARE, AND RECEIVER AGREES
  * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
  * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
  * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN AUTOCHIPS
  * SOFTWARE. AUTOCHIPS SHALL ALSO NOT BE RESPONSIBLE FOR ANY AUTOCHIPS SOFTWARE
  * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
  * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AUTOCHIPS'S
  * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE AUTOCHIPS SOFTWARE
  * RELEASED HEREUNDER WILL BE, AT AUTOCHIPS'S OPTION, TO REVISE OR REPLACE THE
  * AUTOCHIPS SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
  * CHARGE PAID BY RECEIVER TO AUTOCHIPS FOR SUCH AUTOCHIPS SOFTWARE AT ISSUE.
  *
  ******************************************************************************  
  */

/* --------------------------------- Includes ---------------------------------*/
#include "gpio.h"
#include "ac78xx_irq_cb.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
              * Analog 
              * Input 
              * Output
              * EVENT_OUT
              * EXTI
*/
void ATC_GPIO_Init(void)
{
    GPIO_SetFunc(X1_UP_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(X2_UP_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(X3_UP_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(X4_UP_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(X5_UP_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(X6_UP_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(PWM_DAC_Pin, GPIO_FUN0);
    GPIO_SetFunc(GPIO_PB1, GPIO_FUN0);
    GPIO_SetFunc(X12_UP_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(C_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(C_B_Pin, GPIO_FUN0);
    GPIO_SetFunc(C_A_Pin, GPIO_FUN0);
    GPIO_SetFunc(X8_OUT_Pin, GPIO_FUN0);
    GPIO_SetFunc(X11_UP_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(X7_OUT_Pin, GPIO_FUN0);
    GPIO_SetFunc(X7_X8_FR_Pin, GPIO_FUN0);
    GPIO_SetFunc(X5_X6_FR_Pin, GPIO_FUN0);
    GPIO_SetFunc(X3_X4_FR_Pin, GPIO_FUN0);
    GPIO_SetFunc(X1_X2_FR_Pin, GPIO_FUN0);
    GPIO_SetFunc(X6_IN_Pin, GPIO_FUN0);
    GPIO_SetFunc(X5_IN_Pin, GPIO_FUN0);
    GPIO_SetFunc(X4_IN_Pin, GPIO_FUN0);
    GPIO_SetFunc(X3_IN_Pin, GPIO_FUN0);
    GPIO_SetFunc(X2_IN_Pin, GPIO_FUN0);
    GPIO_SetFunc(X1_IN_Pin, GPIO_FUN0);
    GPIO_SetFunc(AI4_PD_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(AI3_PD_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(X9_UP_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(X8_UP_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(X10_UP_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(X7_UP_C_Pin, GPIO_FUN0);
    GPIO_SetFunc(LED_RED_Pin, GPIO_FUN0);
    GPIO_SetFunc(LED_GREEN_Pin, GPIO_FUN0);
    GPIO_SetDir(X1_UP_C_Pin, GPIO_OUT);
    GPIO_SetDir(X2_UP_C_Pin, GPIO_OUT);
    GPIO_SetDir(X3_UP_C_Pin, GPIO_OUT);
    GPIO_SetDir(X4_UP_C_Pin, GPIO_OUT);
    GPIO_SetDir(X5_UP_C_Pin, GPIO_OUT);
    GPIO_SetDir(X6_UP_C_Pin, GPIO_OUT);
    GPIO_SetDir(PWM_DAC_Pin, GPIO_OUT);
    GPIO_SetDir(GPIO_PB1, GPIO_OUT);
    GPIO_SetDir(X12_UP_C_Pin, GPIO_OUT);
    GPIO_SetDir(C_C_Pin, GPIO_OUT);
    GPIO_SetDir(C_B_Pin, GPIO_OUT);
    GPIO_SetDir(C_A_Pin, GPIO_OUT);
    GPIO_SetDir(X8_OUT_Pin, GPIO_OUT);
    GPIO_SetDir(X11_UP_C_Pin, GPIO_OUT);
    GPIO_SetDir(X7_OUT_Pin, GPIO_OUT);
    GPIO_SetDir(X7_X8_FR_Pin, GPIO_OUT);
    GPIO_SetDir(X5_X6_FR_Pin, GPIO_OUT);
    GPIO_SetDir(X3_X4_FR_Pin, GPIO_OUT);
    GPIO_SetDir(X1_X2_FR_Pin, GPIO_OUT);
    GPIO_SetDir(X6_IN_Pin, GPIO_IN);
    GPIO_SetDir(X5_IN_Pin, GPIO_IN);
    GPIO_SetDir(X4_IN_Pin, GPIO_IN);
    GPIO_SetDir(X3_IN_Pin, GPIO_IN);
    GPIO_SetDir(X2_IN_Pin, GPIO_IN);
    GPIO_SetDir(X1_IN_Pin, GPIO_IN);
    GPIO_SetDir(AI4_PD_C_Pin, GPIO_OUT);
    GPIO_SetDir(AI3_PD_C_Pin, GPIO_OUT);
    GPIO_SetDir(X9_UP_C_Pin, GPIO_OUT);
    GPIO_SetDir(X8_UP_C_Pin, GPIO_OUT);
    GPIO_SetDir(X10_UP_C_Pin, GPIO_OUT);
    GPIO_SetDir(X7_UP_C_Pin, GPIO_OUT);
    GPIO_SetDir(LED_RED_Pin, GPIO_OUT);
    GPIO_SetDir(LED_GREEN_Pin, GPIO_OUT);
    GPIO_SetPinValue(X1_UP_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X2_UP_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X3_UP_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X4_UP_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X5_UP_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X6_UP_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(PWM_DAC_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(GPIO_PB1, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X12_UP_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(C_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(C_B_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(C_A_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X8_OUT_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X11_UP_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X7_OUT_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X7_X8_FR_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X5_X6_FR_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X3_X4_FR_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X1_X2_FR_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(AI4_PD_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(AI3_PD_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X9_UP_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X8_UP_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X10_UP_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(X7_UP_C_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(LED_RED_Pin, GPIO_LEVEL_LOW);
    GPIO_SetPinValue(LED_GREEN_Pin, GPIO_LEVEL_LOW);
    GPIO_SetE4E2(X1_UP_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X2_UP_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X3_UP_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X4_UP_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X5_UP_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X6_UP_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(PWM_DAC_Pin, GPIO_DRIVING_16MA);
    GPIO_SetE4E2(GPIO_PB1, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X12_UP_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(C_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(C_B_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(C_A_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X8_OUT_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X11_UP_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X7_OUT_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X7_X8_FR_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X5_X6_FR_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X3_X4_FR_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X1_X2_FR_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(AI4_PD_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(AI3_PD_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X9_UP_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X8_UP_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X10_UP_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(X7_UP_C_Pin, GPIO_DRIVING_4MA);
    GPIO_SetE4E2(LED_RED_Pin, GPIO_DRIVING_16MA);
    GPIO_SetE4E2(LED_GREEN_Pin, GPIO_DRIVING_16MA);
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT AutoChips *****END OF FILE****/
