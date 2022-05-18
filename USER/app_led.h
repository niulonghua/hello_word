///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//Filename	:app_led.h
//Project Code	:
//
//Version	:V0.0
//Autor	:NLH
//Accomplished Date:20200820
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
#ifndef APP_LED_H
#define APP_LED_H
#include "main.h"


#define OFF 0
#define ON 1

typedef struct 
{
	unsigned char WorkMode;		
	unsigned char RedLedOnOff;
	unsigned char GreenLedOnOff;
	unsigned short Time1msAcc;
	
}_LED;

extern _LED Led;

void App_Led_1ms_Interrupt(void);
void App_Led_Main(void);


#endif

