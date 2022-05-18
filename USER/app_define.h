///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//Filename	:app_define.h
//Project Code	:
//
//Version	:V0.0
//Autor	:nlh
//Accomplished Date:20200819
//Change Content:
//
//RVersions	:
//Autor	:
//Accomplished Date:
//Change Content:
//
//RVersions	:
//Autor	:
//Accomplished Date:
//Change Content:
//
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "ac78xx_gpio.h"


#define X1_UP_ON		GPIO_SetPinValue(X1_UP_C_Pin,1)
#define X1_UP_OFF		GPIO_SetPinValue(X1_UP_C_Pin,0)
#define X2_UP_ON		GPIO_SetPinValue(X2_UP_C_Pin,1)
#define X2_UP_OFF		GPIO_SetPinValue(X2_UP_C_Pin,0)
#define X3_UP_ON		GPIO_SetPinValue(X3_UP_C_Pin,1)
#define X3_UP_OFF		GPIO_SetPinValue(X3_UP_C_Pin,0)
#define X4_UP_ON		GPIO_SetPinValue(X4_UP_C_Pin,1)
#define X4_UP_OFF		GPIO_SetPinValue(X4_UP_C_Pin,0)
#define X5_UP_ON		GPIO_SetPinValue(X5_UP_C_Pin,1)
#define X5_UP_OFF		GPIO_SetPinValue(X5_UP_C_Pin,0)
#define X6_UP_ON		GPIO_SetPinValue(X6_UP_C_Pin,1)
#define X6_UP_OFF		GPIO_SetPinValue(X6_UP_C_Pin,0)
#define X7_UP_ON		GPIO_SetPinValue(X7_UP_C_Pin,1)
#define X7_UP_OFF		GPIO_SetPinValue(X7_UP_C_Pin,0)
#define X8_UP_ON		GPIO_SetPinValue(X8_UP_C_Pin,1)
#define X8_UP_OFF		GPIO_SetPinValue(X8_UP_C_Pin,0)
#define X9_UP_ON		GPIO_SetPinValue(X9_UP_C_Pin,1)
#define X9_UP_OFF		GPIO_SetPinValue(X9_UP_C_Pin,0)
#define X10_UP_ON		GPIO_SetPinValue(X10_UP_C_Pin,1)
#define X10_UP_OFF	GPIO_SetPinValue(X10_UP_C_Pin,0)
#define X11_UP_ON		GPIO_SetPinValue(X11_UP_C_Pin,1)
#define X11_UP_OFF	GPIO_SetPinValue(X11_UP_C_Pin,0)
#define X12_UP_ON		GPIO_SetPinValue(X12_UP_C_Pin,1)
#define X12_UP_OFF	GPIO_SetPinValue(X12_UP_C_Pin,0)

#define X1_X2_FR_H  GPIO_SetPinValue(X1_X2_FR_Pin,1)
#define X1_X2_FR_L  GPIO_SetPinValue(X1_X2_FR_Pin,0)
#define X3_X4_FR_H  GPIO_SetPinValue(X3_X4_FR_Pin,1)
#define X3_X4_FR_L  GPIO_SetPinValue(X3_X4_FR_Pin,0)
#define X5_X6_FR_H  GPIO_SetPinValue(X5_X6_FR_Pin,1)
#define X5_X6_FR_L  GPIO_SetPinValue(X5_X6_FR_Pin,0)
#define X7_X8_FR_H  GPIO_SetPinValue(X7_X8_FR_Pin,1)
#define X7_X8_FR_L  GPIO_SetPinValue(X7_X8_FR_Pin,0)

#define X1_OUT_ON 	GPIO_SetPinValue(X1_OUT_Pin,1)
#define X1_OUT_OFF 	GPIO_SetPinValue(X1_OUT_Pin,0)
#define X2_OUT_ON 	GPIO_SetPinValue(X2_OUT_Pin,1)
#define X2_OUT_OFF 	GPIO_SetPinValue(X2_OUT_Pin,0)
#define X3_OUT_ON 	GPIO_SetPinValue(X3_OUT_Pin,1)
#define X3_OUT_OFF 	GPIO_SetPinValue(X3_OUT_Pin,0)
#define X4_OUT_ON 	GPIO_SetPinValue(X4_OUT_Pin,1)
#define X4_OUT_OFF 	GPIO_SetPinValue(X4_OUT_Pin,0)
#define X5_OUT_ON 	GPIO_SetPinValue(X5_OUT_Pin,1)
#define X5_OUT_OFF 	GPIO_SetPinValue(X5_OUT_Pin,0)
#define X6_OUT_ON 	GPIO_SetPinValue(X6_OUT_Pin,1)
#define X6_OUT_OFF 	GPIO_SetPinValue(X6_OUT_Pin,0)
#define X7_OUT_ON 	GPIO_SetPinValue(X7_OUT_Pin,1)
#define X7_OUT_OFF 	GPIO_SetPinValue(X7_OUT_Pin,0)
#define X8_OUT_ON 	GPIO_SetPinValue(X8_OUT_Pin,1)
#define X8_OUT_OFF 	GPIO_SetPinValue(X8_OUT_Pin,0)

#define X1_IN				GPIO_GetPinValue(X1_IN_Pin)
#define X2_IN				GPIO_GetPinValue(X2_IN_Pin)
#define X3_IN				GPIO_GetPinValue(X3_IN_Pin)
#define X4_IN				GPIO_GetPinValue(X4_IN_Pin)
#define X5_IN				GPIO_GetPinValue(X5_IN_Pin)
#define X6_IN				GPIO_GetPinValue(X6_IN_Pin)
#define X7_IN				GPIO_GetPinValue(X7_IN_Pin)
#define X8_IN				GPIO_GetPinValue(X8_IN_Pin)
#define X9_IN				GPIO_GetPinValue(X9_IN_Pin)
#define X10_IN			GPIO_GetPinValue(X10_IN_Pin)
#define X11_IN			GPIO_GetPinValue(X11_IN_Pin)
#define X12_IN			GPIO_GetPinValue(X12_IN_Pin)

#define C_A_H				GPIO_SetPinValue(C_A_Pin,1)
#define C_A_L     	GPIO_SetPinValue(C_A_Pin,0)
#define C_B_H				GPIO_SetPinValue(C_B_Pin,1)
#define C_B_L     	GPIO_SetPinValue(C_B_Pin,0)
#define C_C_H				GPIO_SetPinValue(C_C_Pin,1)
#define C_C_L     	GPIO_SetPinValue(C_C_Pin,0)

#define AI3_PD_ON		GPIO_SetPinValue(AI3_PD_C_Pin,1)
#define AI3_PD_OFF	GPIO_SetPinValue(AI3_PD_C_Pin,0)
#define AI4_PD_ON		GPIO_SetPinValue(AI4_PD_C_Pin,1)
#define AI4_PD_OFF	GPIO_SetPinValue(AI4_PD_C_Pin,0)

#define LED_GREEN_ON GPIO_SetPinValue(LED_GREEN_Pin,0)
#define LED_GREEN_OFF GPIO_SetPinValue(LED_GREEN_Pin,1)
#define LED_RED_ON GPIO_SetPinValue(LED_RED_Pin,0)
#define LED_RED_OFF GPIO_SetPinValue(LED_RED_Pin,1)

#define PWM_DAC_H  GPIO_SetPinValue(PWM_DAC_Pin,1)
#define PWM_DAC_L  GPIO_SetPinValue(PWM_DAC_Pin,0)

