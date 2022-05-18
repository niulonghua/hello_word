///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//Filename	:app_can.c
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
#include "app_define.h"
#include "app_adc.h"
#include "ac78xx.h"
#include "ac78xx_adc.h"




_ADC SigAdc[ADC_NUM];
//0:VIN 1:FB1 2:FB2 3:FB3 4:AI4 5:AI3 6:AI2 7:AI5 8:AI1 9:X1-X8 10:VSENSOR_C 11:VSENSOR_V 12:XTR 13:NAMDGAP 14:TEMP
//15:X2 16:X3 17:X4 18:X1 19:X5 20:X8 21:X6 22:X7
//unsigned int GetNowADCValue[ADC_ACC_VALUE*ADC_CHANNEL_NUM];

extern uint16_t adcDmaBuffer[301];
unsigned char DMAScanOKFlag;

uint8_t  g_dmaFinish = 0;//DMA传输完成
uint8_t  g_halfDmaFinish = 0; //DMA传输半完成
uint8_t  g_dmaTransError = 0; //DMA传输错误
uint32_t g_bandgapVol;



void adcBandgapCali(void)
{
    uint32_t TsensorCali = 0;
    uint8_t  VbandgapRT  = 0;
    //uint16_t bgVol       = 0;
    
    TsensorCali = *((uint32_t*)0x40003050);  //标准值
    VbandgapRT = (uint8_t)(TsensorCali & 0x1F);  //低5位为bandgap的校准值
    /* BG calibration */
    if (VbandgapRT >> 4)//第5位为符号
    {
        g_bandgapVol = 1200 - (VbandgapRT & 0xF); //第5位为1, 1200mV 减去低4位值
    }
    else
    {
        g_bandgapVol = 1200 + (VbandgapRT & 0xF); //第5位为1, 1200mV 加上 低4位值
    } 
}

void App_ADC_DMA_Interrupt(void)
{
	DMAScanOKFlag=1;
	//ADC_DMACmd(ADC, DISABLE);
//	ADC_Cmd(ADC,DISABLE);
}


void Scan_4051(unsigned char Status)
{
	switch(Status)
	{
		case 0:C_A_L;C_B_L;C_C_L;break;
		case 1:C_A_H;C_B_L;C_C_L;break;
		case 2:C_A_L;C_B_H;C_C_L;break;
		case 3:C_A_H;C_B_H;C_C_L;break;
		case 4:C_A_L;C_B_L;C_C_H;break;
		case 5:C_A_H;C_B_L;C_C_H;break;
		case 6:C_A_L;C_B_H;C_C_H;break;
		case 7:C_A_H;C_B_H;C_C_H;break;
		default:break;
	}
}
	
void Get_ADC_Value(void)
{
	static unsigned char GetStatus=0;
	static unsigned char Scan4051Num=0;
	static unsigned int U32_Temp[ADC_CHANNEL_NUM];
	static unsigned char GetScanAdFlag=0;
	unsigned char i,j;
	switch(GetStatus)
	{
		case 0:
			if(GetScanAdFlag==0)
			{
				GetScanAdFlag=1;
				Scan_4051(Scan4051Num);
			}
			
			GetStatus++;
			break;
		case 1:
			if(DMAScanOKFlag==1)
			{
				DMAScanOKFlag=0;
				GetStatus=0;
				for(i=0;i<ADC_CHANNEL_NUM;i++)
				{
					U32_Temp[i]=0;
					for(j=0;j<ADC_ACC_VALUE;j++)
					{
					//	SigAdc[i].TempValue[j]=adcDmaBuffer[j*ADC_CHANNEL_NUM+i];
						U32_Temp[i]+=adcDmaBuffer[j*ADC_CHANNEL_NUM+i];
					}
					U32_Temp[i]/=ADC_ACC_VALUE;
					SigAdc[i].NowValue=U32_Temp[i];
					SigAdc[i].GETADCFlag=1;	
				}
				if(GetScanAdFlag==1)
				{
					GetScanAdFlag=2;
				}
				else if(GetScanAdFlag==2)
				{
					GetScanAdFlag=0;
					SigAdc[Scan4051Num+15].NowValue=SigAdc[9].NowValue;
					SigAdc[Scan4051Num+15].GETADCFlag=1;	
					if(++Scan4051Num>=8)
					{
						Scan4051Num=0;
					}
				}
			}
			break;	
	}
}

void App_ADC_1ms_Interrupt(void)
{
	static unsigned int time_1ms_acc;
	if(++time_1ms_acc>=1000)
		time_1ms_acc=1000;
}

void App_ADC_Init(void)
{
	adcBandgapCali();
	ADC_SoftwareStartRegularConvCmd(ADC,ENABLE);
}
void App_ADC_Main(void)
{
	Get_ADC_Value();
}



