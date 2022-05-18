///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//Filename	:app_output.c
//Project Code	:
//
//Version	:V0.0
//Autor	:niulonghua
//Accomplished Date:20200312
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

#include "app_output.h"
#include "app_define.h"
#include "app_adc.h"
#include "ac78xx_pwm.h"
#include "user.h"



/*
typedef struct 
{
	unsigned char WorkMode;			//set 工作模式 0不工作 1开关 2 PWM 
	unsigned char SetOnOffStatus;		//write 设置状态 0 off 1开 
	unsigned char OnOffStatus;		//开关状态 0 off 1 on
	unsigned short SetDutyValue;
	unsigned short DutyValue;
	unsigned char EquStatus;		//read 设备状态 0 off 1 on 2空载 3过流 
	unsigned short CurrentValue;		//read 电流值	

	unsigned int Time1msFlag;
	unsigned int Time10usAcc;
	unsigned short Time1usAcc;
	
	unsigned int NoLoadThreshold;	//set 空载阀值
	unsigned short NoloadErrAcc;	//空载异常计数 1ms
	unsigned int OverLoadThreshold;	//set 过载阀值
	unsigned short OverLoadErrAcc;	//过载异常计数 1ms
	
}_OutPut;

*/


_OutPut OutPut[OUTPUT_NUM];
unsigned short DACCurrtenValue;//1bit/0.1mA;

unsigned  int modValue = 0;   //16 bits 计数器：0~65535
unsigned int PwmDacTime10UsAcc;

unsigned char Time10MsFlag;
unsigned char PwmDutyValue;



void Set_PWM_Fre(float Frequency)
{
	
  uint16_t preScale = 0;   //16 bits 预分频：1~65535
	if (0 == Frequency)
	{
			Frequency=1000;
			modValue = 100;
	}
	else if (Frequency >= 500) //高频的情况，设置较小的ModeValue，因为prescale也会较小；
	{
			modValue = 100;
	}
	else if (Frequency >= 50)
	{
			modValue = 1000;
	}
	else
	{
			modValue = 5000; //低频的情况，设置较大的ModeValue，否则prescale太大会溢出；
	}
	preScale = 48000000.0 / (Frequency * modValue);
	PWM_SetModValue(PWM2, (modValue - 1));
  PWM_ClockSet(PWM2, PWM_CLOCK_SYSTEMCLOCK, (preScale-1));
}
void Set_PWM_Duty(unsigned short Duty,unsigned char ChannelNum)
{
	unsigned int Temp;
	Temp=Duty;
	if(Temp>0)
		PWM_SetChannelValue(PWM2, ChannelNum, (modValue*Temp)/1000-1);
	else
		PWM_SetChannelValue(PWM2, ChannelNum, 0);
}

void OutPut_Running(void)
{
	for(unsigned char OutNum=0;OutNum<OUTPUT_NUM;OutNum++)
	{
		if(OutPut[OutNum].WorkMode==APP_DISABLE)//不启动
		{
			OutPut[OutNum].OnOffStatus=APP_OFF;
			OutPut[OutNum].EquStatus=APP_OFF;
		}
		else if(OutPut[OutNum].WorkMode==APP_ONOFF)//开关模式
		{
			if(OutPut[OutNum].Time1msFlag==1)//1ms cycle
			{
				OutPut[OutNum].Time1msFlag=0;
				if(OutPut[OutNum].EquStatus!=OVER_LOAD)//
				{
					OutPut[OutNum].OnOffStatus=OutPut[OutNum].SetOnOffStatus;
					if(OutPut[OutNum].EquStatus!=ON_LOAD)
						OutPut[OutNum].EquStatus=OutPut[OutNum].SetOnOffStatus;
				}
				else
				{
					OutPut[OutNum].OnOffStatus=APP_OFF;
				}
				
				if(OutPut[OutNum].OnOffStatus==APP_ON)
				{
					if(OutPut[OutNum].CurrentValue>OutPut[OutNum].OverLoadThreshold)//过流判断
					{
						++OutPut[OutNum].OverLoadErrAcc;
						if(OutPut[OutNum].OverLoadErrAcc>OUTPUT_OVERLOAD_ERR_TIME_THRESHOLD)
						{
							OutPut[OutNum].OverLoadErrAcc=OUTPUT_OVERLOAD_ERR_TIME_THRESHOLD;
							OutPut[OutNum].EquStatus=OVER_LOAD;
						}
					}
					else if(OutPut[OutNum].CurrentValue<OutPut[OutNum].NoLoadThreshold)//空载判断
					{
						++OutPut[OutNum].NoloadErrAcc;
						if(OutPut[OutNum].NoloadErrAcc>OUTPUT_NOLOAD_ERR_TIME_THRESHOLD)
						{
							OutPut[OutNum].NoloadErrAcc=OUTPUT_NOLOAD_ERR_TIME_THRESHOLD;
							OutPut[OutNum].EquStatus=ON_LOAD;
						}
					}
					else//正常判断
					{
						if(OutPut[OutNum].OverLoadErrAcc>0)
						{
							OutPut[OutNum].OverLoadErrAcc--;
						}
						
						if(OutPut[OutNum].NoloadErrAcc>0)
						{
							OutPut[OutNum].NoloadErrAcc--;
						}
						else//空载状态复位
						{
							if(OutPut[OutNum].EquStatus==ON_LOAD)
							{
								
								OutPut[OutNum].EquStatus=OutPut[OutNum].OnOffStatus;
							}
						}
					}
				}
			}
		}
		else if(OutPut[OutNum].WorkMode==APP_PWM)
		{
			if(OutPut[OutNum].Time1msFlag==1)//1ms cycle
			{
				OutPut[OutNum].Time1msFlag=0;
				if(OutPut[OutNum].CurrentValue>OutPut[OutNum].OverLoadThreshold)//过流判断
				{
					++OutPut[OutNum].OverLoadErrAcc;
					if(OutPut[OutNum].OverLoadErrAcc>OUTPUT_OVERLOAD_ERR_TIME_THRESHOLD)
					{
						OutPut[OutNum].OverLoadErrAcc=OUTPUT_OVERLOAD_ERR_TIME_THRESHOLD;
						OutPut[OutNum].EquStatus=OVER_LOAD;
					}
				}
				else//正常判断
				{
					if(OutPut[OutNum].OverLoadErrAcc>0)
					{
						OutPut[OutNum].OverLoadErrAcc--;
					}
				}
			}
		}
	}
}
void OutPut_Execute(void)
{
	unsigned char ChannelNum[6]={1,0,2,3,4,5};
	for(unsigned char i=0;i<6;i++)
	{
		 if(OutPut[i].WorkMode==APP_ONOFF)//开关模式
		 {
				if(OutPut[i].OnOffStatus==APP_ON)
					Set_PWM_Duty(1000,ChannelNum[i]);
				else
					Set_PWM_Duty(0,ChannelNum[i]);
		 }
		 else if(OutPut[i].WorkMode==APP_PWM)
		 {
			 if(OutPut[i].EquStatus!=OVER_LOAD)
			 {
				 OutPut[i].DutyValue=OutPut[i].SetDutyValue;
				Set_PWM_Duty(OutPut[i].DutyValue,ChannelNum[i]);
			 }
			 else
				 Set_PWM_Duty(0,ChannelNum[i]);
		 }
		 else
		 {
				Set_PWM_Duty(0,ChannelNum[i]);
		 }
	}
	if((OutPut[6].WorkMode==APP_ONOFF)&&(OutPut[6].OnOffStatus==APP_ON))
		X7_OUT_ON;
	else
		X7_OUT_OFF;
	if((OutPut[7].WorkMode==APP_ONOFF)&&(OutPut[7].OnOffStatus==APP_ON))
		X8_OUT_ON;
	else
		X8_OUT_OFF;
}	

void OutPut_Get_Current(void)
{
//_ADC SigAdc[ADC_NUM];
//0:VIN 1:FB1 2:FB2 3:FB3 4:AI4 5:AI3 6:AI2 7:AI5 8:AI1 9:X1-X8 10:VSENSOR_C 11:VSENSOR_V 12:XTR 13:NAMDGAP 14:TEMP
//15:X2 16:X3 17:X4 18:X1 19:X5 20:X8 21:X6 22:X7

		if(SigAdc[18].GETADCFlag==1)
		{
			SigAdc[18].GETADCFlag=0;
			if(SigAdc[18].NowValue>=12)
				OutPut[0].CurrentValue=SigAdc[18].NowValue*3.663-44;
			else 
				OutPut[0].CurrentValue=0;
		}
		if(SigAdc[15].GETADCFlag==1)
		{
			SigAdc[15].GETADCFlag=0;
			if(SigAdc[15].NowValue>=12)
				OutPut[1].CurrentValue=SigAdc[15].NowValue*3.57;
			else
				OutPut[1].CurrentValue=0;
		}
		if(SigAdc[16].GETADCFlag==1)
		{
			SigAdc[16].GETADCFlag=0;
			if(SigAdc[16].NowValue>=12)
				OutPut[2].CurrentValue=SigAdc[16].NowValue*3.57;
			else
				OutPut[2].CurrentValue=0;
		}
		if(SigAdc[17].GETADCFlag==1)
		{
			SigAdc[17].GETADCFlag=0;
			if(SigAdc[17].NowValue>=12)
				OutPut[3].CurrentValue=SigAdc[17].NowValue*3.57;
			else
				OutPut[3].CurrentValue=0;
		}
		if(SigAdc[19].GETADCFlag==1)
		{
			SigAdc[19].GETADCFlag=0;
			if(SigAdc[19].NowValue>=12)
				OutPut[4].CurrentValue=SigAdc[19].NowValue*3.57;
			else
				OutPut[4].CurrentValue=0;
		}
		if(SigAdc[21].GETADCFlag==1)
		{
			SigAdc[21].GETADCFlag=0;
			if(SigAdc[21].NowValue>=12)
				OutPut[5].CurrentValue=SigAdc[21].NowValue*3.57;
			else
				OutPut[5].CurrentValue=0;
		}
		if(SigAdc[22].GETADCFlag==1)
		{
			SigAdc[22].GETADCFlag=0;
			if(SigAdc[22].NowValue>=12)
				OutPut[6].CurrentValue=SigAdc[22].NowValue*3.57;
			else
				OutPut[6].CurrentValue=0;
		}
		if(SigAdc[20].GETADCFlag==1)
		{
			SigAdc[20].GETADCFlag=0;
			if(SigAdc[20].NowValue>=12)
				OutPut[7].CurrentValue=SigAdc[20].NowValue*3.57;
			else
				OutPut[7].CurrentValue=0;
		}
}

void Set_DAC(void)
{
	
	if(PwmDutyValue>PwmDacTime10UsAcc)
		PWM_DAC_H;
	else
		PWM_DAC_L;
}

void App_Output_1us_Interrupt(void)
{
	
}

void App_Output_10us_Interrupt(void)
{
	if(++PwmDacTime10UsAcc>=100)
	{
		PwmDacTime10UsAcc=0;
	}
	Set_DAC();
}
void App_Output_1ms_Interrupt(void)
{
	for(unsigned char OutNum=0;OutNum<OUTPUT_NUM;OutNum++)
	{
		if(OutPut[OutNum].WorkMode!=APP_DISABLE)
			OutPut[OutNum].Time1msFlag=1;
	}
	static unsigned short Time1MsAcc;
	if(++Time1MsAcc>=10)
	{
		Time1MsAcc=0;
		Time10MsFlag=1;
	}
}

void App_Output_Init(void)
{
	Set_PWM_Fre(PWMFREQUENCY);
	
}

void App_Output_Main(void)
{
	OutPut_Get_Current();
	OutPut_Running();
	OutPut_Execute();
	if(Time10MsFlag)
	{
		Time10MsFlag=0;
		PwmDutyValue=DACCurrtenValue*0.404;
	}
	
}







