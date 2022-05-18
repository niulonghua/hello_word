///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//Filename	:app_can.h
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
#ifndef APP_ADC_H
#define APP_ADC_H

#define ADC_NUM  23
#define ADC_CHANNEL_NUM 15
#define ADC_ACC_VALUE 20


typedef struct 
{
	unsigned int NowValue;				
	unsigned int Value;						
	unsigned int AddTemp;	
	unsigned char Acc;		
	unsigned char GETADCFlag;
//	unsigned short TempValue[30];
}_ADC;

extern _ADC SigAdc[ADC_NUM];

void App_ADC_DMA_Interrupt(void);
void App_ADC_1ms_Interrupt(void);
void App_ADC_Init(void);
void App_ADC_Main(void);

#endif
