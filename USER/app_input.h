///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//Filename	:app_input.h
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

#ifndef APP_INPUT_H
#define APP_INPUT_H

#define INPUT_NUM   					12		//输入管脚数
#define INPUT_SCAN_ACC_VALUE 	20		//去抖次数
#define STARTDELAYTIME     		1000 	//启动延时时间 1bit/ms
#define CYCLETIME          		2			//检测循环周期  1bit/ms  设置为0时为跟随主循环运行

typedef enum
{
    INPUT_DISABLE = 0,
    INPUT_ENABLE=1
}INPUT_Enable_Type;

typedef enum
{
		INPUT_LOW =0,
    INPUT_HIGH = 1
    
}INPUT_Effection_Type;

typedef struct 
{
	INPUT_Enable_Type EnableFlag;						//是否检测IN标志 0 disable  1 enable
	INPUT_Effection_Type EffectionStatus;		//高低控选择 0低电平有效 1高电平有效
	unsigned char SignalStatus;							//获取对应PIN脚状态
	unsigned char ScanStatus;								//扫描状态
	unsigned char ScanAcc;									//防抖计数
	unsigned char Status;										//IN状态 0 无效   1 有效
	unsigned char PushDownFlag;							//按下标志位 1有效
	
	unsigned char CaptureMask;
	unsigned int NewCaptureValue;
	unsigned int OldCaptureCalue;
	unsigned int CaptureValue;
	unsigned char GetCaptureFlag;
	unsigned int SpeedValue;
	unsigned int SpeedTemp[30];
	unsigned char GetSpeedAcc;
	
	unsigned int Time1MsAcc;
}_Sig_Input;

extern _Sig_Input SigInput[INPUT_NUM];

void Get_Capture_Value(unsigned char Num,unsigned int NowCapture);
void App_Input_1ms_Interrupt(void);
void App_Input_Init(void);
void App_Input_Main(void);

#endif

