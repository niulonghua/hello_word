#include "app_user.h"
#include "app_define.h"
#include "app_input.h"
#include "app_adc.h"
#include "app_can.h"
#include "app_led.h"
#include "app_output.h"
#include "app_tool_function.h"
#include "user.h"
#include "app_eeprom.h"





void App_User_Work(void)
{
	//==============电源电压=============
	if(SigAdc[0].GETADCFlag)
	{
		SigAdc[0].GETADCFlag=0;
		PowerVoltageValue=SigAdc[0].NowValue*38.116+600;
	}
	//==============4-20mA=================
	DACCurrtenValue=DacSetValue;
	//==============+5V输出===============
	if(SensorPower.SetOnOffStatus==1)
		GPIO_SetPinValue(GPIO_PB1,0);
	else
		GPIO_SetPinValue(GPIO_PB1,1);
	if(SigAdc[11].GETADCFlag)
	{
		SigAdc[11].GETADCFlag=0;
		SensorPower.VoltageValue=SigAdc[11].NowValue*4.8828;
	}
	if(SigAdc[10].GETADCFlag)
	{
		SigAdc[10].GETADCFlag=0;
		SensorPower.CurrentValue=SigAdc[10].NowValue/1.6384;
	}
	//==============指示灯====================
	Led.WorkMode=(unsigned char)LED;
	//=================FB================
	if(SigAdc[1].GETADCFlag)
	{
		SigAdc[1].GETADCFlag=0;
		FB[FB1].CurrentValue=SigAdc[1].NowValue*0.9;
	}
	if(SigAdc[2].GETADCFlag)
	{
		SigAdc[2].GETADCFlag=0;
		FB[FB2].CurrentValue=SigAdc[2].NowValue*0.9;
	}
	if(SigAdc[3].GETADCFlag)
	{
		SigAdc[3].GETADCFlag=0;
		FB[FB3].CurrentValue=SigAdc[3].NowValue*0.9137;
	}
	//===============AI======================
	if(SigAdc[8].GETADCFlag)
	{
		SigAdc[8].GETADCFlag=0;
		AI[AI1].GetValue=SigAdc[8].NowValue*13.05;
	}
	if(SigAdc[6].GETADCFlag)
	{
		SigAdc[6].GETADCFlag=0;
		AI[AI2].GetValue=SigAdc[6].NowValue*2.44;
	}
	if(SigAdc[5].GETADCFlag)
	{
		SigAdc[5].GETADCFlag=0;
		if(AI[AI3].TestMode==0)
			AI[AI3].GetValue=SigAdc[5].NowValue*2.44;
		else	
			AI[AI3].GetValue=SigAdc[5].NowValue/6.55;
	}
	if(SigAdc[4].GETADCFlag)
	{
		SigAdc[4].GETADCFlag=0;
		if(AI[AI4].TestMode==0)
			AI[AI4].GetValue=SigAdc[4].NowValue*2.44;
		else	
			AI[AI4].GetValue=SigAdc[4].NowValue/6.55;
	}
	if(SigAdc[7].GETADCFlag)
	{
		SigAdc[7].GETADCFlag=0;
		AI[AI5].GetValue=SigAdc[7].NowValue*2.44;
	}
	
	//===================X============================
	unsigned char i;
	for(i=0;i<8;i++)//OutPut
	{
		X[i].CurrentValue=OutPut[i].CurrentValue;
		X[i].EquStatus=OutPut[i].EquStatus;
		if(X[i].SetMode==1)
		{
			if(X[i].SetValue>1)
				OutPut[i].SetOnOffStatus=0;
			else
				OutPut[i].SetOnOffStatus=X[i].SetValue;
		}
		else if(X[i].SetMode==2)
		{
			if(X[i].SetValue>1000)
				OutPut[i].SetDutyValue=0;
			else
				OutPut[i].SetDutyValue=X[i].SetValue;
		}
	}
	for(i=0;i<12;i++)//InPut
	{
		if(X[i].SetMode<5)
			X[i].GetValue=SigInput[i].Status;
		else
			X[i].GetValue=SigInput[i].SpeedValue;
	}
		
}

void App_Set_Equ_State(void)
{
	unsigned char i;
	//=======================INPUT_INIT==========================
	//工作模式 0不工作 1高控输出 2PWM输出 3高控检测 4低控检测 5高控频率检测 6低控频率检测
	for(i=0;i<12;i++)
	{
		if(X[i].SetMode==0)
			SigInput[i].EnableFlag=INPUT_DISABLE;
		else if((X[i].SetMode==1)||(X[i].SetMode==2)||(X[i].SetMode==3)||(X[i].SetMode==5))
		{
			SigInput[i].EnableFlag=INPUT_ENABLE;
			SigInput[i].EffectionStatus=INPUT_LOW;
		}
		else
		{
			SigInput[i].EnableFlag=INPUT_ENABLE;
			SigInput[i].EffectionStatus=INPUT_HIGH;
		}
	}
	if((X[X1].SetMode==4)||(X[X1].SetMode==6)) 	X1_UP_ON; else X1_UP_OFF;
	if((X[X2].SetMode==4)||(X[X2].SetMode==6)) 	X2_UP_ON; else X2_UP_OFF;
	if((X[X3].SetMode==4)||(X[X3].SetMode==6)) 	X3_UP_ON; else X3_UP_OFF;
	if((X[X4].SetMode==4)||(X[X4].SetMode==6)) 	X4_UP_ON; else X4_UP_OFF;
	if((X[X5].SetMode==4)||(X[X5].SetMode==6)) 	X5_UP_ON; else X5_UP_OFF;
	if((X[X6].SetMode==4)||(X[X6].SetMode==6)) 	X6_UP_ON; else X6_UP_OFF;
	if((X[X7].SetMode==4)||(X[X7].SetMode==6)) 	X7_UP_ON; else X7_UP_OFF;
	if((X[X8].SetMode==4)||(X[X8].SetMode==6)) 	X8_UP_ON; else X8_UP_OFF;
	if((X[X9].SetMode==4)||(X[X9].SetMode==6)) 	X9_UP_ON; else X9_UP_OFF;
	if((X[X10].SetMode==4)||(X[X10].SetMode==6)) 	X10_UP_ON; else X10_UP_OFF;
	if((X[X11].SetMode==4)||(X[X11].SetMode==6)) 	X11_UP_ON; else X11_UP_OFF;
	if((X[X12].SetMode==4)||(X[X12].SetMode==6)) 	X12_UP_ON; else X12_UP_OFF;

	//========================OUTPUT_INIT=======================
	for(i=0;i<8;i++)
	{
		switch(X[i].SetMode)
		{
			case 0:
				OutPut[i].WorkMode=0;break;
			case 1:
				OutPut[i].WorkMode=1;break;
			case 2:
				OutPut[i].WorkMode=2;break;
			default:
				OutPut[i].WorkMode=0;break;
		}
		OutPut[i].NoLoadThreshold=X[i].NoLoadThreshold;
		OutPut[i].OverLoadThreshold=X[i].OverLoadThreshold;
	}
	if((X[X1].SetMode==1)||(X[X1].SetMode==2)||(X[X2].SetMode==1)||(X[X2].SetMode==2))
		X1_X2_FR_H;
	else
		X1_X2_FR_L;
	
	if((X[X3].SetMode==1)||(X[X3].SetMode==2)||(X[X4].SetMode==1)||(X[X4].SetMode==2))
		X3_X4_FR_H;
	else
		X3_X4_FR_L;
	
	if((X[X5].SetMode==1)||(X[X5].SetMode==2)||(X[X6].SetMode==1)||(X[X6].SetMode==2))
		X5_X6_FR_H;
	else
		X5_X6_FR_L;
	
	if((X[X7].SetMode==1)||(X[X7].SetMode==2)||(X[X8].SetMode==1)||(X[X8].SetMode==2))
		X7_X8_FR_H;
	else
		X7_X8_FR_L;
	
	
	//=======================ADC_INIT=================================
	if(AI[AI3].TestMode==1)
		AI3_PD_ON;
	else
		AI3_PD_OFF;
	
	if(AI[AI4].TestMode==1)
		AI4_PD_ON;
	else
		AI4_PD_OFF;
	
}




void App_User_1mm_Interrupt(void)
{


}
void App_User_Init(void)
{

	App_Set_Equ_State();
	
	App_Input_Init();
	App_ADC_Init();
	App_CAN_Init();
	App_Output_Init();
	
	
}
void App_User_Main(void)
{
	App_User_Work();
	App_Input_Main();
	App_ADC_Main();
	App_CAN_Main();
	App_Led_Main();
	App_Output_Main();

}


