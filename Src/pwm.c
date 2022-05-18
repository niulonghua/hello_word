/**
  ******************************************************************************
  * File Name          : PWM.c
  * Description        : This file provides code for the configuration
  *                      of the PWM instances.
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
#include "ac78xx.h"
#include "ac78xx_irq_cb.h"
#include "ac78xx_pwm.h"
#include "pwm.h"

extern void Error_Handler(char *, int);

void MSP_PWM_Init(PWM_Type* PWMx);

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* PWM0 init function */
void ATC_PWM0_Init(void)
{

    PWM_SetCallback(PWM0, PWM0_IRQHandler_Callback);
    MSP_PWM_Init(PWM0);
    PWM_InputCaptureInit(PWM0, PWM_CHANNEL_CHANNEL0, PWM_INPUTCAPTURE_RISINGEDGE);
    PWM_InputCaptureInit(PWM0, PWM_CHANNEL_CHANNEL1, PWM_INPUTCAPTURE_RISINGEDGE);
    PWM_EnableOverflowInt(PWM0);
    PWM_SetCapturePSCValue(PWM0, PWM_CHANNEL_CHANNEL0, 0);
    PWM_SetCapturePSCValue(PWM0, PWM_CHANNEL_CHANNEL1, 0);
    PWM_ClockSet(PWM0, PWM_CLOCK_SYSTEMCLOCK, 480-1);

}
/* PWM1 init function */
void ATC_PWM1_Init(void)
{

    PWM_SetCallback(PWM1, PWM1_IRQHandler_Callback);
    MSP_PWM_Init(PWM1);
    PWM_InputCaptureInit(PWM1, PWM_CHANNEL_CHANNEL0, PWM_INPUTCAPTURE_RISINGEDGE);
    PWM_InputCaptureInit(PWM1, PWM_CHANNEL_CHANNEL1, PWM_INPUTCAPTURE_RISINGEDGE);
    PWM_EnableOverflowInt(PWM1);
    PWM_SetCapturePSCValue(PWM1, PWM_CHANNEL_CHANNEL0, 0);
    PWM_SetCapturePSCValue(PWM1, PWM_CHANNEL_CHANNEL1, 0);
    PWM_ClockSet(PWM1, PWM_CLOCK_SYSTEMCLOCK, 48000-1);

}
/* PWM2 init function */
void ATC_PWM2_Init(void)
{

    MSP_PWM_Init(PWM2);
    PWM_PWMInit(PWM2, PWM_PWMMODE_EDGEALLIGNED, PWM_PWM_HIGHTRUEPULSE);
    PWM_SetModValue(PWM2, 1000);
    PWM_SetCntTOFNum(PWM2, 0);
    PWM_SetChannelValue(PWM2, PWM_CHANNEL_CHANNEL0, 0);
    PWM_SetChannelValue(PWM2, PWM_CHANNEL_CHANNEL1, 0);
    PWM_SetChannelValue(PWM2, PWM_CHANNEL_CHANNEL2, 0);
    PWM_SetChannelValue(PWM2, PWM_CHANNEL_CHANNEL3, 0);
    PWM_SetChannelValue(PWM2, PWM_CHANNEL_CHANNEL4, 0);
    PWM_SetChannelValue(PWM2, PWM_CHANNEL_CHANNEL5, 0);
    PWM_ClockSet(PWM2, PWM_CLOCK_SYSTEMCLOCK, 0);

}
/* PWM3 init function */
void ATC_PWM3_Init(void)
{

    PWM_SetCallback(PWM3, PWM3_IRQHandler_Callback);
    MSP_PWM_Init(PWM3);
    PWM_InputCaptureInit(PWM3, PWM_CHANNEL_CHANNEL0, PWM_INPUTCAPTURE_RISINGEDGE);
    PWM_InputCaptureInit(PWM3, PWM_CHANNEL_CHANNEL1, PWM_INPUTCAPTURE_RISINGEDGE);
    PWM_EnableOverflowInt(PWM3);
    PWM_SetCapturePSCValue(PWM3, PWM_CHANNEL_CHANNEL0, 0);
    PWM_SetCapturePSCValue(PWM3, PWM_CHANNEL_CHANNEL1, 0);
    PWM_ClockSet(PWM3, PWM_CLOCK_SYSTEMCLOCK, 480-1);

}

void MSP_PWM_Init(PWM_Type* PWMx)
{

    if (PWMx == PWM0)
    {
        /* USER CODE BEGIN MSP_PWM0_Init 0 */

        /* USER CODE END MSP_PWM0_Init 0 */
    
        /**
        GPIO Configuration for PWM0        
        PB9         --> PWM0_CH0
        PB10         --> PWM0_CH1 
        */
        GPIO_SetFunc(X7_IN_Pin, GPIO_FUN1);

        GPIO_SetFunc(X10_IN_Pin, GPIO_FUN1);

        /* PWM0 interrupt Init */
        NVIC_SetPriority(PWM0_IRQn, 0);
        NVIC_EnableIRQ(PWM0_IRQn);

        /* USER CODE BEGIN MSP_PWM0_Init 1 */

        /* USER CODE END MSP_PWM0_Init 1 */
    }
    else if (PWMx == PWM1)
    {
        /* USER CODE BEGIN MSP_PWM1_Init 0 */

        /* USER CODE END MSP_PWM1_Init 0 */
    
        /**
        GPIO Configuration for PWM1        
        PD3         --> PWM1_CH0
        PD4         --> PWM1_CH1 
        */
        GPIO_SetFunc(X8_IN_Pin, GPIO_FUN1);

        GPIO_SetFunc(X9_IN_Pin, GPIO_FUN1);

        /* PWM1 interrupt Init */
        NVIC_SetPriority(PWM1_IRQn, 0);
        NVIC_EnableIRQ(PWM1_IRQn);

        /* USER CODE BEGIN MSP_PWM1_Init 1 */

        /* USER CODE END MSP_PWM1_Init 1 */
    }
    else if (PWMx == PWM2)
    {
        /* USER CODE BEGIN MSP_PWM2_Init 0 */

        /* USER CODE END MSP_PWM2_Init 0 */
    
        /**
        GPIO Configuration for PWM2        
        PB11         --> PWM2_CH2
        PB12         --> PWM2_CH3
        PB13         --> PWM2_CH4
        PB14         --> PWM2_CH5
        PB15         --> PWM2_CH0
        PC0         --> PWM2_CH1 
        */
        GPIO_SetFunc(X3_OUT_Pin, GPIO_FUN2);

        GPIO_SetFunc(X4_OUT_Pin, GPIO_FUN2);

        GPIO_SetFunc(X5_OUT_Pin, GPIO_FUN2);

        GPIO_SetFunc(X6_OUT_Pin, GPIO_FUN2);

        GPIO_SetFunc(X2_OUT_Pin, GPIO_FUN1);

        GPIO_SetFunc(X1_OUT_Pin, GPIO_FUN1);

        /* USER CODE BEGIN MSP_PWM2_Init 1 */

        /* USER CODE END MSP_PWM2_Init 1 */
    }
    else if (PWMx == PWM3)
    {
        /* USER CODE BEGIN MSP_PWM3_Init 0 */

        /* USER CODE END MSP_PWM3_Init 0 */
    
        /**
        GPIO Configuration for PWM3        
        PD8         --> PWM3_CH1
        PB6         --> PWM3_CH0 
        */
        GPIO_SetFunc(X12_IN_Pin, GPIO_FUN3);

        GPIO_SetFunc(X11_IN_Pin, GPIO_FUN3);

        /* PWM3 interrupt Init */
        NVIC_SetPriority(PWM3_IRQn, 0);
        NVIC_EnableIRQ(PWM3_IRQn);

        /* USER CODE BEGIN MSP_PWM3_Init 1 */

        /* USER CODE END MSP_PWM3_Init 1 */
    }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT AutoChips *****END OF FILE****/
