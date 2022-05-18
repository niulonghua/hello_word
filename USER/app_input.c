///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//Filename	:app_input.c
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

#include "app_input.h"
#include "app_define.h"
#include "ac78xx.h"
#include "ac78xx_irq_cb.h"
#include "ac78xx_pwm.h"
#include "pwm.h"
#include "app_tool_function.h"

_Sig_Input SigInput[INPUT_NUM];

static unsigned short StartDelayTime1MsAcc;
static unsigned short CycleTime1MsAcc;

void Get_Capture_Value(unsigned char Num,unsigned int NowCapture)
{
	if(SigInput[Num].CaptureMask==0)
	{
		SigInput[Num].OldCaptureCalue=NowCapture;
		SigInput[Num].CaptureMask=1;
	}
	else
	{
		SigInput[Num].NewCaptureValue=NowCapture;
		if(SigInput[Num].NewCaptureValue<SigInput[Num].OldCaptureCalue)
			SigInput[Num].NewCaptureValue+=0xffff;
		SigInput[Num].CaptureValue=SigInput[Num].NewCaptureValue-SigInput[Num].OldCaptureCalue;
		
		if(SigInput[Num].CaptureValue>5)
		{
			if((Num==7)||(Num==8))
				SigInput[Num].SpeedTemp[SigInput[Num].GetSpeedAcc]=60000/SigInput[Num].CaptureValue;
			else
				SigInput[Num].SpeedTemp[SigInput[Num].GetSpeedAcc]=6000000/SigInput[Num].CaptureValue;
			if(++SigInput[Num].GetSpeedAcc>=25)
				SigInput[Num].GetSpeedAcc=25;
			SigInput[Num].GetCaptureFlag=1;
		}
		SigInput[Num].Time1MsAcc=0;
		SigInput[Num].CaptureMask=0;
	}
	
	
}

void Scan_Input_Function(void)
{
	unsigned char sig_num;
	////////////////需要更改///////////////////////
	SigInput[0].SignalStatus=(unsigned char)X1_IN;
	SigInput[1].SignalStatus=(unsigned char)X2_IN;
	SigInput[2].SignalStatus=(unsigned char)X3_IN;
	SigInput[3].SignalStatus=(unsigned char)X4_IN;
	SigInput[4].SignalStatus=(unsigned char)X5_IN;
	SigInput[5].SignalStatus=(unsigned char)X6_IN;
	SigInput[6].SignalStatus=(unsigned char)X7_IN;
	SigInput[7].SignalStatus=(unsigned char)X8_IN;
	SigInput[8].SignalStatus=(unsigned char)X9_IN;
	SigInput[9].SignalStatus=(unsigned char)X10_IN;
	SigInput[10].SignalStatus=(unsigned char)X11_IN;
	SigInput[11].SignalStatus=(unsigned char)X12_IN;
	////////////////////////////////////////////////
	for(sig_num=0;sig_num<INPUT_NUM;sig_num++)
	{
		if(SigInput[sig_num].EnableFlag==INPUT_ENABLE)
		{
			switch(SigInput[sig_num].ScanStatus)
			{
				case 0:
					if(SigInput[sig_num].SignalStatus)
						SigInput[sig_num].ScanStatus=1;//高电平
					else
						SigInput[sig_num].ScanStatus=2;//低电平
					SigInput[sig_num].ScanAcc=0;
					break;
				case 1:
					if(SigInput[sig_num].SignalStatus)//高电平判定
					{
						if(++SigInput[sig_num].ScanAcc>INPUT_SCAN_ACC_VALUE)
						{
							if(SigInput[sig_num].EffectionStatus==INPUT_HIGH)
							{
								if(SigInput[sig_num].Status==0)
									SigInput[sig_num].PushDownFlag=1;
								SigInput[sig_num].Status=1;
							}
							else
							{
									SigInput[sig_num].Status=0;
							}
							SigInput[sig_num].ScanStatus=0;
						}
					}
					else
						SigInput[sig_num].ScanStatus=0;
					break;
				case 2:
					if(!SigInput[sig_num].SignalStatus)//低电平判定
					{
						if(++SigInput[sig_num].ScanAcc>INPUT_SCAN_ACC_VALUE)
						{
							if(SigInput[sig_num].EffectionStatus==INPUT_LOW)
							{
								if(SigInput[sig_num].Status==0)
									SigInput[sig_num].PushDownFlag=1;
								SigInput[sig_num].Status=1;
							}
							else
							{
									SigInput[sig_num].Status=0;
							}
							SigInput[sig_num].ScanStatus=0;
						}
					}
					else
						SigInput[sig_num].ScanStatus=0;
					break;
				default: break;
			}
		}
	}
}

void App_Input_1ms_Interrupt(void)
{
	
	if(++StartDelayTime1MsAcc>=10000)
	{
		StartDelayTime1MsAcc=10000;
	}
	if(++CycleTime1MsAcc>=10000)
	{
		CycleTime1MsAcc=10000;
	}
	for(unsigned char i=0;i<INPUT_NUM;i++)
	{
		if((i==7)||(i==8))
		{
			if(++SigInput[i].Time1MsAcc>=10000)
			{
				SigInput[i].Time1MsAcc=10000;
				SigInput[i].SpeedValue=0;
			}
		}
		else
		{
			if(++SigInput[i].Time1MsAcc>=2000)
			{
				SigInput[i].Time1MsAcc=2000;
				SigInput[i].SpeedValue=0;
			}
		}
	}
}

void App_Input_Init(void)
{
	PWM_EnableChannelInt(PWM0, PWM_CHANNEL_CHANNEL0);
	PWM_EnableChannelInt(PWM0, PWM_CHANNEL_CHANNEL1);
	PWM_EnableChannelInt(PWM1, PWM_CHANNEL_CHANNEL0);
	PWM_EnableChannelInt(PWM1, PWM_CHANNEL_CHANNEL1);
	PWM_EnableChannelInt(PWM3, PWM_CHANNEL_CHANNEL0);
	PWM_EnableChannelInt(PWM3, PWM_CHANNEL_CHANNEL1);
}

void App_Input_Main(void)
{
	unsigned int Temp32=0;
	if(StartDelayTime1MsAcc>=STARTDELAYTIME)
	{
		if(CycleTime1MsAcc>=CYCLETIME)
		{
			CycleTime1MsAcc=0;
			Scan_Input_Function();
			for(unsigned char i=0;i<INPUT_NUM;i++)
			{
				if(SigInput[i].GetCaptureFlag==1)
				{
					SigInput[i].GetCaptureFlag=0;
					if(SigInput[i].GetSpeedAcc>=5)
					{
						SigInput[i].GetSpeedAcc=0;
						TOOL_Tnsert(SigInput[i].SpeedTemp,5);
						Temp32=0;
						for(unsigned char j=0;j<=0;j++)
						{
							Temp32+=SigInput[i].SpeedTemp[j];
						}
						SigInput[i].SpeedValue=Temp32/1;
					}
				}
			}
		}
	}
	
}







