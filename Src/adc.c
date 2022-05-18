/**
  ******************************************************************************
  * File Name          : ADC.c
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
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
#include "ac78xx_adc.h"
#include "adc.h"
#include "ac78xx_dma.h"

uint16_t adcDmaBuffer[301] = {0};

extern void Error_Handler(char *, int);

void MSP_ADC_Init(ADC_Type* ADCx);

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* ADC init function */
void ATC_ADC_Init(void)
{
    ADC_InitType adcConfig;
    memset(&adcConfig, 0, sizeof(adcConfig));
    ADC_TrigSourceType adcTrigSourceConfig;
    memset(&adcTrigSourceConfig, 0, sizeof(adcTrigSourceConfig));

    MSP_ADC_Init(ADC);
    adcConfig.dataAlign = ADC_DataAlign_Right;
    adcConfig.scanMode = ENABLE;
    adcConfig.continousMode = ENABLE;
    adcConfig.disContinousModeOnRegularGroup = DISABLE;
    adcConfig.disContinousModeOnInjectGroup = DISABLE;
    adcConfig.injectAutoMode = DISABLE;
    adcConfig.discNum = 0;
    ADC_Init(ADC, &adcConfig);
    ADC_SetClockPrescaler(ADC, 15);
    adcTrigSourceConfig.regularTrigSource = ADC_TrigSource_Internal;
    adcTrigSourceConfig.injectTrigSource = ADC_TrigSource_Internal;
    ADC_TrigSourceInit(ADC, &adcTrigSourceConfig);
    ADC_DMACmd(ADC, ENABLE);
    ADC_SetRegularGroupLength(ADC, 15);
    ADC_SetRegularGroupSequence(ADC, 1, ADC_CHANNEL_AD0);
    ADC_SetRegularGroupSequence(ADC, 2, ADC_CHANNEL_AD1);
    ADC_SetRegularGroupSequence(ADC, 3, ADC_CHANNEL_AD2);
    ADC_SetRegularGroupSequence(ADC, 4, ADC_CHANNEL_AD3);
    ADC_SetRegularGroupSequence(ADC, 5, ADC_CHANNEL_AD4);
    ADC_SetRegularGroupSequence(ADC, 6, ADC_CHANNEL_AD5);
    ADC_SetRegularGroupSequence(ADC, 7, ADC_CHANNEL_AD6);
    ADC_SetRegularGroupSequence(ADC, 8, ADC_CHANNEL_AD7);
    ADC_SetRegularGroupSequence(ADC, 9, ADC_CHANNEL_AD8);
    ADC_SetRegularGroupSequence(ADC, 10, ADC_CHANNEL_AD9);
    ADC_SetRegularGroupSequence(ADC, 11, ADC_CHANNEL_AD10);
    ADC_SetRegularGroupSequence(ADC, 12, ADC_CHANNEL_AD12);
    ADC_SetRegularGroupSequence(ADC, 13, ADC_CHANNEL_AD13);
    ADC_SetRegularGroupSequence(ADC, 14, ADC_CHANNEL_AD16_BANDGAP);
    ADC_SetRegularGroupSequence(ADC, 15, ADC_CHANNEL_AD17_TEMPSENSOR);
    ADC_SetInjectGroupLength(ADC, 1);
    ADC_SetInjectGroupSequence(ADC, 1, ADC_CHANNEL_AD16_BANDGAP);
    ADC_AnalogWatchDogOnRegularChannelModeEnable(ADC);
    ADC_AnalogWatchDogOnInjectChannelModeEnable(ADC);
    ADC_AnalogWatchDogSingleChannelModeEnable(ADC);
    ADC_AnalogWatchDogInterruptEnable(ADC);
    ADC_Cmd(ADC, ENABLE);
    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD0, ADC_SampleTime_6Cycle);
    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD1, ADC_SampleTime_6Cycle);
    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD2, ADC_SampleTime_6Cycle);
    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD3, ADC_SampleTime_6Cycle);
    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD4, ADC_SampleTime_6Cycle);
    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD5, ADC_SampleTime_6Cycle);
    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD6, ADC_SampleTime_6Cycle);
    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD7, ADC_SampleTime_6Cycle);
    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD8, ADC_SampleTime_6Cycle);
    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD9, ADC_SampleTime_6Cycle);
    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD10, ADC_SampleTime_6Cycle);
    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD12, ADC_SampleTime_6Cycle);
    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD13, ADC_SampleTime_6Cycle);

}

void MSP_ADC_Init(ADC_Type* ADCx)
{

    DMA_ConfigType dmaConfig;
    memset(&dmaConfig, 0, sizeof(dmaConfig));
    /* USER CODE BEGIN MSP_ADC_Init 0 */

    /* USER CODE END MSP_ADC_Init 0 */
    
    /**
    GPIO Configuration for ADC    
    PA6     --> ADC_IN10
    PD6     --> ADC_IN12
    PA7     --> ADC_IN0
    PA8     --> ADC_IN1
    PA9     --> ADC_IN2
    PA10     --> ADC_IN3
    PA11     --> ADC_IN4
    PA12     --> ADC_IN5
    PA13     --> ADC_IN6
    PA14     --> ADC_IN7
    PA15     --> ADC_IN8
    PB0     --> ADC_IN9
    PD7     --> ADC_IN13 
    */
    GPIO_SetFunc(GPIO_PA6, GPIO_FUN1);

    GPIO_SetFunc(GPIO_PD6, GPIO_FUN1);

    GPIO_SetFunc(GPIO_PA7, GPIO_FUN1);

    GPIO_SetFunc(GPIO_PA8, GPIO_FUN1);

    GPIO_SetFunc(GPIO_PA9, GPIO_FUN1);

    GPIO_SetFunc(GPIO_PA10, GPIO_FUN1);

    GPIO_SetFunc(GPIO_PA11, GPIO_FUN1);

    GPIO_SetFunc(GPIO_PA12, GPIO_FUN1);

    GPIO_SetFunc(GPIO_PA13, GPIO_FUN1);

    GPIO_SetFunc(GPIO_PA14, GPIO_FUN1);

    GPIO_SetFunc(GPIO_PA15, GPIO_FUN1);

    GPIO_SetFunc(GPIO_PB0, GPIO_FUN1);

    GPIO_SetFunc(GPIO_PD7, GPIO_FUN1);

    /* ADC DMA Init */
    /* ADC Init */
    /* USER CODE BEGIN INIT DMA BUFFER ARRAY */

    /* USER CODE END INIT DMA BUFFER ARRAY */
    dmaConfig.memStartAddr = (uint32_t)&adcDmaBuffer[0];
    dmaConfig.memEndAddr = (uint32_t)&adcDmaBuffer[301];
    dmaConfig.periphStartAddr = (uint32_t)&(ADC->RDR);
    dmaConfig.setting.transferNum = 300;
    dmaConfig.setting.finishIntEn = ENABLE;
    dmaConfig.setting.halfFinishIntEn = DISABLE;
    dmaConfig.setting.errorIntEn = DISABLE;
    dmaConfig.setting.channelEn = ENABLE;
    dmaConfig.setting.MEM2MEM = DISABLE;
    dmaConfig.setting.channelPriority = 1;
    dmaConfig.setting.memSize = 1;
    dmaConfig.setting.periphSize = 2;
    dmaConfig.setting.memIncrement = 1;
    dmaConfig.setting.periphIncrement = 0;
    dmaConfig.setting.circular = ENABLE;
    dmaConfig.setting.direction = 0;
    dmaConfig.setting.memByteMode = 0;
    DMA_Initialize(DMA1, &dmaConfig);

    /* ADC interrupt Init */
    DMA_SetEventCallback(DMA1, DMA1_IRQHandler_Callback);
    NVIC_SetPriority(DMA1_IRQn, 0);
    NVIC_EnableIRQ(DMA1_IRQn);

    /* USER CODE BEGIN MSP_ADC_Init 1 */

    /* USER CODE END MSP_ADC_Init 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT AutoChips *****END OF FILE****/
