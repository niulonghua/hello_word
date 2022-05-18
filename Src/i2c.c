/**
  ******************************************************************************
  * File Name          : I2C.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
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
#include "ac78xx_i2c.h"
#include "i2c.h"

extern void Error_Handler(char *, int);

void MSP_I2C_Init(I2C_Type* I2Cx);

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* I2C1 init function */
void ATC_I2C1_Init(void)
{
    I2C_ConfigType i2cConfig;
    memset(&i2cConfig, 0, sizeof(i2cConfig));

    MSP_I2C_Init(I2C1);
    i2cConfig.sampleCNT = 11;
    i2cConfig.stepCNT = 19;
    i2cConfig.sclAdj = 0;
    i2cConfig.setting.i2cEn = ENABLE;
    i2cConfig.setting.intEn = DISABLE;
    i2cConfig.setting.master = I2C_MASTER;
    i2cConfig.setting.wakeUpEn = DISABLE;
    i2cConfig.setting.swRst = 0;
    i2cConfig.setting.gcaEn = DISABLE;
    i2cConfig.setting.addressExt = DISABLE;
    i2cConfig.setting.syncEn = ENABLE;
    i2cConfig.setting.arbEn = DISABLE;
    i2cConfig.setting.strEn = DISABLE;
    i2cConfig.setting.mntEn = DISABLE;
    i2cConfig.setting.mntIE = DISABLE;
    i2cConfig.setting.dmaRxEn = DISABLE;
    i2cConfig.setting.dmaTxEn = DISABLE;
    i2cConfig.setting.SSIE = DISABLE;
    i2cConfig.setting.rxOFIntEn = DISABLE;
    i2cConfig.setting.txUFIntEn = DISABLE;
    i2cConfig.setting.nackIntEn = ENABLE;
    i2cConfig.addr1 = 0x5a;
    I2C_Initialize(I2C1, &i2cConfig);
    I2C_EnableRxFInt(I2C1);
    I2C_EnableTxEInt(I2C1);

}

void MSP_I2C_Init(I2C_Type* I2Cx)
{

    if (I2Cx == I2C1)
    {
    /* USER CODE BEGIN MSP_I2C1_Init 0 */

    /* USER CODE END MSP_I2C1_Init 0 */
    
    /**
    GPIO Configuration for I2C1    
    PC12     --> I2C1_SCL
    PC13     --> I2C1_SDA 
    */
    GPIO_SetFunc(GPIO_PC12, GPIO_FUN1);

    GPIO_SetFunc(GPIO_PC13, GPIO_FUN1);

    /* USER CODE BEGIN MSP_I2C1_Init 1 */

    /* USER CODE END MSP_I2C1_Init 1 */
    }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT AutoChips *****END OF FILE****/
