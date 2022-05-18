/**
  ******************************************************************************
  * @file    ac78xx_irq_cb.c
  * @brief   IRQ callback.
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
#include "ac78xx_timer.h"
/* USER CODE BEGIN Includes */
#include "app_input.h"
#include "app_adc.h"
#include "app_can.h"
#include "app_led.h"
#include "app_output.h"
#include "ac78xx_timer.h"
#include "timer.h"
#include "ac78xx_pwm.h"
extern void App_User_1mm_Interrupt(void);
extern void User_1mm_Interrupt(void);
/* USER CODE END Includes */

/* --------------------------------- Typedefs ----------------------------------*/
/* USER CODE BEGIN Typedefs */

/* USER CODE END Typedefs */

/* --------------------------------- Defines -----------------------------------*/
/* USER CODE BEGIN Defines */
 extern unsigned char DMAScanOKFlag;
/* USER CODE END Defines */

/* --------------------------------- Macros ------------------------------------*/
/* USER CODE BEGIN Macros */

/* USER CODE END Macros */

/* --------------------------------- Variables ---------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* --------------------------------- Function Prototypes -----------------------*/
/* USER CODE BEGIN Function_Prototypes */

/* USER CODE END Function_Prototypes */

/* --------------------------------- User Code ---------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/******************************************************************************/
/* ac78xx Peripheral Interrupt Handlers callbacks                             */
/******************************************************************************/

/**
* @brief This function handle DMA Channel1 interrupt.
* @param[in] DMAx: DMA type pointer,x can be 1 to 12
* @param[in] wparam: DMA channel's status(Finish, Half Finish and Error Flags)
* @param[in] lparam: reserved
* @return 0: success, other: error value
*/
int32_t DMA1_IRQHandler_Callback(DMA_Type *DMAx, uint32_t wparam, uint32_t lparam)
{
    if ((wparam & 0x01) == 0x01)
    {
        /* USER CODE BEGIN DMA1 FINISH */
				DMAScanOKFlag=1;
        /* USER CODE END DMA1 FINISH */
    }

    if ((wparam & 0x02) == 0x02)
    {
        /* USER CODE BEGIN HALF DMA1 FINISH */

        /* USER CODE END HALF DMA1 FINISH */
    }

    if ((wparam & 0x04) == 0x04)
    {
        /* USER CODE BEGIN HALF DMA1 TRANSFER ERROR */

        /* USER CODE END HALF DMA1 TRANSFER ERROR */
    }

    /* USER CODE BEGIN DMA1_IRQHandler_Callback*/

    /* USER CODE END DMA1_IRQHandler_Callback*/
    return 0;
}

/**
* @brief This function handle Timer 0 interrupt.
* @param[in] arg: timer callback argument
* @return none
*/
void TIMER0_IRQHandler_Callback(uint8_t arg)
{
    TIMER_ClrIntFlag(TIMER_GetTimerCtrl(arg));

    /* USER CODE BEGIN TIMER0_IRQHandler_Callback*/

			TIMER_ClrIntFlag(TIMER0);
			App_User_1mm_Interrupt();
			App_ADC_1ms_Interrupt();
			App_CAN_1ms_Interrupt();
			App_Led_1ms_Interrupt();
			App_Output_1ms_Interrupt();
		 App_Input_1ms_Interrupt();
		 User_1mm_Interrupt();

	
    /* USER CODE END TIMER0_IRQHandler_Callback*/
}

/**
* @brief This function handle Timer 1 interrupt.
* @param[in] arg: timer callback argument
* @return none
*/
void TIMER1_IRQHandler_Callback(uint8_t arg)
{
    TIMER_ClrIntFlag(TIMER_GetTimerCtrl(arg));

    /* USER CODE BEGIN TIMER1_IRQHandler_Callback*/

		 TIMER_ClrIntFlag(TIMER1);
			App_Output_10us_Interrupt();

    /* USER CODE END TIMER1_IRQHandler_Callback*/
}

/**
* @brief This function handle PWM 0 interrupt.
* @param[in] none
* @return none
*/
void PWM0_IRQHandler_Callback(void)
{
    /* USER CODE BEGIN PWM0_IRQHandler_Callback*/
		if (PWM_GetOverFlowFlag(PWM0))
    {
        PWM_ClrOverFlowFlag(PWM0);
				
    }
		else
		{
			if(PWM_GetChannelIntFlag(PWM0, PWM_CHANNEL_CHANNEL0))
			{
				Get_Capture_Value(6,PWM0->CHANNELS[0].CHV);
				PWM_ClrChannelIntFlag(PWM0, PWM_CHANNEL_CHANNEL0);
				//X7
			}
			else if(PWM_GetChannelIntFlag(PWM0, PWM_CHANNEL_CHANNEL1))
			{
				//X10
				Get_Capture_Value(9,PWM0->CHANNELS[1].CHV);
			//	SigInput[9].CaptureValue=PWM0->CHANNELS[1].CHV;
				PWM_ClrChannelIntFlag(PWM0, PWM_CHANNEL_CHANNEL1);
			}
		}
    
    /* USER CODE END PWM0_IRQHandler_Callback*/
}

/**
* @brief This function handle PWM 1 interrupt.
* @param[in] none
* @return none
*/
void PWM1_IRQHandler_Callback(void)
{
    /* USER CODE BEGIN PWM1_IRQHandler_Callback*/
		if (PWM_GetOverFlowFlag(PWM1))
    {
        PWM_ClrOverFlowFlag(PWM1);
    }
    else
		{
			if(PWM_GetChannelIntFlag(PWM1, PWM_CHANNEL_CHANNEL0))
			{

				Get_Capture_Value(7,PWM1->CHANNELS[0].CHV);
				PWM_ClrChannelIntFlag(PWM1, PWM_CHANNEL_CHANNEL0);
				//X8
			}
			else if(PWM_GetChannelIntFlag(PWM1, PWM_CHANNEL_CHANNEL1))
			{
				
				Get_Capture_Value(8,PWM1->CHANNELS[1].CHV);
				PWM_ClrChannelIntFlag(PWM1, PWM_CHANNEL_CHANNEL1);
				//X9
			}
		}
    /* USER CODE END PWM1_IRQHandler_Callback*/
}

/**
* @brief This function handle PWM 3 interrupt.
* @param[in] none
* @return none
*/
void PWM3_IRQHandler_Callback(void)
{
    /* USER CODE BEGIN PWM3_IRQHandler_Callback*/
		if (PWM_GetOverFlowFlag(PWM3))
    {
        PWM_ClrOverFlowFlag(PWM3);
    }
    else
		{
			if(PWM_GetChannelIntFlag(PWM3, PWM_CHANNEL_CHANNEL0))
			{
				Get_Capture_Value(10,PWM3->CHANNELS[0].CHV);
				PWM_ClrChannelIntFlag(PWM3, PWM_CHANNEL_CHANNEL0);
				//X11
			}
			else if(PWM_GetChannelIntFlag(PWM3, PWM_CHANNEL_CHANNEL1))
			{
				Get_Capture_Value(11,PWM3->CHANNELS[1].CHV);
				PWM_ClrChannelIntFlag(PWM3, PWM_CHANNEL_CHANNEL1);
				//X12
			}
		}
    /* USER CODE END PWM3_IRQHandler_Callback*/
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT AutoChips *****END OF FILE****/
