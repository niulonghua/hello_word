///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//Filename	:app_input.h
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







#define OUTPUT_NUM 8   

#define APP_OFF 0
#define APP_ON 1
#define ON_LOAD 2
#define OVER_LOAD 3

#define APP_DISABLE 0
#define APP_ONOFF 1
#define APP_PWM 2



typedef struct 
{
	unsigned char WorkMode;			//set 工作模式 0不工作 1开关 2 PWM 
	unsigned char SetOnOffStatus;		//write 设置状态 0 off 1开 
	unsigned char OnOffStatus;		//开关状态 0 off 1 on
	unsigned short SetDutyValue;
	unsigned  int DutyValue;
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

extern _OutPut OutPut[OUTPUT_NUM];
extern unsigned short DACCurrtenValue;//1bit/0.1mA;
void App_Output_1us_Interrupt(void);
void App_Output_10us_Interrupt(void);
void App_Output_1ms_Interrupt(void);
void App_Output_Init(void);
void App_Output_Main(void);


