///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//Filename	:app_led.c
//Project Code	:
//
//Version	:V0.0
//Autor	:NLH
//Accomplished Date:202000820
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
#include "app_led.h"
#include "app_define.h"


_LED Led;

void Led_Running(void)
{
	switch(Led.WorkMode)
	{
		case 0:
			Led.RedLedOnOff=OFF;
			Led.GreenLedOnOff=OFF;
			break;
		case 1:
			Led.RedLedOnOff=OFF;
			Led.GreenLedOnOff=ON;
			break;
		case 2:
			Led.RedLedOnOff=ON;
			Led.GreenLedOnOff=OFF;
			break;
		case 3:
			if(Led.Time1msAcc>250)
			{
				Led.Time1msAcc=0;
				if(Led.RedLedOnOff==ON)
				{
					Led.RedLedOnOff=OFF;
					Led.GreenLedOnOff=OFF;
				}
				else
				{
					Led.RedLedOnOff=ON;
					Led.GreenLedOnOff=ON;
				}
			}
			break;
		case 4:
			if(Led.Time1msAcc>250)
			{
				Led.Time1msAcc=0;
				if(Led.RedLedOnOff==ON)
				{
					Led.RedLedOnOff=OFF;
					Led.GreenLedOnOff=ON;
				}
				else
				{
					Led.RedLedOnOff=ON;
					Led.GreenLedOnOff=OFF;
				}
			}
			break;
		case 5:
			if(Led.Time1msAcc>250)
			{
				Led.Time1msAcc=0;
				if(Led.RedLedOnOff==ON)
				{
					Led.RedLedOnOff=OFF;
				}
				else
				{
					Led.RedLedOnOff=ON;
				}
			}
			Led.GreenLedOnOff=OFF;
			break;
		case 6:
			if(Led.Time1msAcc>250)
			{
				Led.Time1msAcc=0;
				if(Led.GreenLedOnOff==ON)
				{
					Led.GreenLedOnOff=OFF;
				}
				else
				{
					Led.GreenLedOnOff=ON;
				}
			}
			Led.RedLedOnOff=OFF;
			break;
		default:break;
		
	}
	
	if(Led.GreenLedOnOff==ON)
		LED_GREEN_ON;
	else
		LED_GREEN_OFF;
	
	if(Led.RedLedOnOff==ON)
		LED_RED_ON;
	else
		LED_RED_OFF;
}

void App_Led_1ms_Interrupt(void)
{
	if(++Led.Time1msAcc>=1000)
		Led.Time1msAcc=1000;
}

void App_Led_Main(void)
{
	Led_Running();
}











