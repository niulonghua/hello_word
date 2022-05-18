#include "user.h"
#include "yu.h"

//=====================系统变量========================
_X1_X12		X[12];
_AI1_AI5	AI[5];
_FB1_FB3  FB[3];
LED_Type  LED;
unsigned int PowerVoltageValue;
_V_SENEOR SensorPower;
unsigned int DacSetValue;
_CAN_RX  CAN1Rx[CAN1_RX_NUM];
_CAN_TX  CAN1Tx[CAN1_TX_NUM];
_CAN_RX  CAN2Rx[CAN2_RX_NUM];
_CAN_TX  CAN2Tx[CAN2_TX_NUM];
_TIME_SYS SysTime;
//=====================================================

//==================用户变量===========================

//=====================================================



void User_Init(void)
{
	SensorPower.SetOnOffStatus=1; 
	//X1-X12初始化
	X[X1].SetMode=2;							//工作模式 0不工作 1高控输出 2PWM输出 3高控检测 4低控检测 
	X[X1].SetValue=0;							//设置状态 工作模式=高控输 0不输出 1输出高
	X[X1].NoLoadThreshold=400;		//空载阀值  1mA/bit
	X[X1].OverLoadThreshold=5000;	//过载阀值 1mA/bit
	
	X[X2].SetMode=2;							//工作模式 0不工作 1高控输出 2PWM输出 3高控检测 4低控检测 
	X[X2].SetValue=0;							//设置状态 工作模式=高控输 0不输出 1输出高
	X[X2].NoLoadThreshold=400;		//空载阀值  1mA/bit
	X[X2].OverLoadThreshold=5000;	//过载阀值 1mA/bit
	X[X3].SetMode=2;							//工作模式 0不工作 1高控输出 2PWM输出 3高控检测 4低控检测 
	X[X3].SetValue=0;							//设置状态 工作模式=高控输 0不输出 1输出高
	X[X3].NoLoadThreshold=400;		//空载阀值  1mA/bit
	X[X3].OverLoadThreshold=5000;	//过载阀值 1mA/bit
	X[X4].SetMode=2;							//工作模式 0不工作 1高控输出 2PWM输出 3高控检测 4低控检测 
	X[X4].SetValue=0;							//设置状态 工作模式=高控输 0不输出 1输出高
	X[X4].NoLoadThreshold=400;		//空载阀值  1mA/bit
	X[X4].OverLoadThreshold=5000;	//过载阀值 1mA/bit
	X[X5].SetMode=2;							//工作模式 0不工作 1高控输出 2PWM输出 3高控检测 4低控检测 
	X[X5].SetValue=0;							//设置状态 工作模式=高控输 0不输出 1输出高
	X[X5].NoLoadThreshold=400;		//空载阀值  1mA/bit
	X[X5].OverLoadThreshold=5000;	//过载阀值 1mA/bit
	X[X6].SetMode=2;							//工作模式 0不工作 1高控输出 2PWM输出 3高控检测 4低控检测 
	X[X6].SetValue=0;							//设置状态 工作模式=高控输 0不输出 1输出高
	X[X6].NoLoadThreshold=400;		//空载阀值  1mA/bit
	X[X6].OverLoadThreshold=5000;	//过载阀值 1mA/bit
	X[X7].SetMode=3;							//工作模式 0不工作 1高控输出 3高控检测 4低控检测 5高控频率检测 6低控频率检测
	X[X7].SetValue=0;							//设置状态 工作模式=高控输 0不输出 1输出高
	X[X7].NoLoadThreshold=400;		//空载阀值  1mA/bit
	X[X7].OverLoadThreshold=5000;	//过载阀值 1mA/bit
	X[X8].SetMode=5;							//工作模式 0不工作 1高控输出 3高控检测 4低控检测 5高控频率检测 6低控频率检测
	X[X8].SetValue=0;							//设置状态 工作模式=高控输 0不输出 1输出高
	X[X8].NoLoadThreshold=400;		//空载阀值  1mA/bit
	X[X8].OverLoadThreshold=5000;	//过载阀值 1mA/bit
	
	X[X9].SetMode=5;							//工作模式 0不工作  3高控检测 4低控检测 5高控频率检测 6低控频率检测
	X[X10].SetMode=5;							//工作模式 0不工作  3高控检测 4低控检测 5高控频率检测 6低控频率检测
	X[X11].SetMode=5;							//工作模式 0不工作  3高控检测 4低控检测 5高控频率检测 6低控频率检测
	X[X12].SetMode=5;							//工作模式 0不工作  3高控检测 4低控检测 5高控频率检测 6低控频率检测

		X[X1].SetMode=2;
		X[X2].SetMode=2;
		X[X3].SetMode=2;
		X[X4].SetMode=2;
		X[X5].SetMode=2;
		X[X6].SetMode=2;
		X[X7].SetMode=3;
		//8-12
		X[X8].SetMode=5;
		X[X9].SetMode=5;
		X[X10].SetMode=5;
		X[X11].SetMode=5;
		X[X12].SetMode=5;
		
	//AI1-AI5初始化
	AI[AI1].TestMode=0;						//测试模式  0电压检测 
	AI[AI2].TestMode=0;						//测试模式  0电压检测 
	AI[AI3].TestMode=0;						//测试模式  0电压检测 1电流检测模式
	AI[AI4].TestMode=0;						//测试模式  0电压检测 1电流检测模式
	AI[AI5].TestMode=0;						//测试模式  0电压检测 
	
	//LED初始化
	LED=RED_THEN_GREEN_FLICKER;

	//CAN初始化
		//===========CAN1接收帧==================
	CAN1Rx[0].ID=0x201;
	CAN1Rx[0].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Rx[0].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Rx[0].DLC=8;
	CAN1Rx[0].Time1msAcc=50;

	CAN1Rx[1].ID=0x202;
	CAN1Rx[1].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Rx[1].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Rx[1].DLC=8;
	CAN1Rx[1].Time1msAcc=50;
	
	CAN1Rx[2].ID=0x301;
	CAN1Rx[2].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Rx[2].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Rx[2].DLC=8;
	CAN1Rx[2].Time1msAcc=50;
	
	CAN1Rx[3].ID=0x302;
	CAN1Rx[3].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Rx[3].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Rx[3].DLC=8;
	CAN1Rx[3].Time1msAcc=50;
	
	CAN1Rx[4].ID=0x601;
	CAN1Rx[4].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Rx[4].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Rx[4].DLC=8;
	CAN1Rx[4].Time1msAcc=50;
	
	CAN1Rx[5].ID=0x401;
	CAN1Rx[5].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Rx[5].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Rx[5].DLC=8;
	CAN1Rx[5].Time1msAcc=50;
	
	//===========CAN1发送帧==================
	CAN1Tx[0].ID=0x181;
	CAN1Tx[0].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[0].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[0].DLC=8;
	CAN1Tx[0].SendCycle=100;
	CAN1Tx[0].SendMode=CIRCULATION;//循环模式
	
	CAN1Tx[1].ID=0x281;
	CAN1Tx[1].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[1].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[1].DLC=8;
	CAN1Tx[1].SendCycle=100;
	CAN1Tx[1].SendMode=CIRCULATION;//循环模式
	
	CAN1Tx[2].ID=0x581;
	CAN1Tx[2].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[2].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[2].DLC=8;
	CAN1Tx[2].SendCycle=40;
	CAN1Tx[2].SendMode=TRIGGER;//触发模式
	
	CAN1Tx[3].ID=0x381;
	CAN1Tx[3].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[3].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[3].DLC=8;
	CAN1Tx[3].SendCycle=100;
	CAN1Tx[3].SendMode=CIRCULATION;//循环模式
	
	CAN1Tx[4].ID=0x382;
	CAN1Tx[4].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[4].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[4].DLC=8;
	CAN1Tx[4].SendCycle=100;
	CAN1Tx[4].SendMode=CIRCULATION;//循环模式
	
	CAN1Tx[5].ID=0x383;
	CAN1Tx[5].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[5].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[5].DLC=8;
	CAN1Tx[5].SendCycle=100;
	CAN1Tx[5].SendMode=CIRCULATION;//循环模式
	
	CAN1Tx[6].ID=0x384;
	CAN1Tx[6].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[6].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[6].DLC=8;
	CAN1Tx[6].SendCycle=100;
	CAN1Tx[6].SendMode=CIRCULATION;//循环模式
	
	CAN1Tx[7].ID=0x385;
	CAN1Tx[7].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[7].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[7].DLC=8;
	CAN1Tx[7].SendCycle=100;
	CAN1Tx[7].SendMode=CIRCULATION;//循环模式
	
	CAN1Tx[8].ID=0x386;
	CAN1Tx[8].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[8].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[8].DLC=8;
	CAN1Tx[8].SendCycle=100;
	CAN1Tx[8].SendMode=CIRCULATION;//循环模式
	/*	
	CAN1Tx[1].ID=0x103;
	CAN1Tx[1].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[1].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[1].DLC=8;
	CAN1Tx[1].SendCycle=40;
	CAN1Tx[1].SendMode=CIRCULATION; //循环模式
	
	//===========CAN2接收帧==================
	CAN2Rx[0].ID=0x01000000;
	CAN2Rx[0].IDE=CAN_IDE_EXT;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN2Rx[0].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN2Rx[0].DLC=8;
	
	CAN2Rx[1].ID=0x01000001;
	CAN2Rx[1].IDE=CAN_IDE_EXT;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN2Rx[1].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN2Rx[1].DLC=8;
	
	//===========CAN2发送帧==================
	CAN2Tx[0].ID=0x01000002;
	CAN2Tx[0].IDE=CAN_IDE_EXT;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN2Tx[0].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN2Tx[0].DLC=8;
	CAN2Tx[0].SendCycle=100;
	
	CAN2Tx[1].ID=0x01000003;
	CAN2Tx[1].IDE=CAN_IDE_EXT;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN2Tx[1].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN2Tx[1].DLC=8;
	CAN2Tx[1].SendCycle=100;
*/
	//App_Epprom_Read(0,EEPROMData,20);

}

void User_1mm_Interrupt(void)
{
	if(++SysTime.T10msF1msAcc>=10)
	{
		SysTime.T10msFlag=1;
		SysTime.T10msF1msAcc=0;
	}
	if(++SysTime.T20msF1msAcc>=20)
	{
		SysTime.T20msFlag=1;
		SysTime.T20msF1msAcc=0;
	}
	if(++SysTime.T50msF1msAcc>=50)
	{
		SysTime.T50msFlag=1;
		SysTime.T50msF1msAcc=0;
	}
	if(++SysTime.T100msF1msAcc>=100)
	{
		SysTime.T100msFlag=1;
		SysTime.T100msF1msAcc=0;
	}
	if(++SysTime.T200msF1msAcc>=200)
	{
		SysTime.T200msFlag=1;
		SysTime.T200msF1msAcc=0;
	}
	if(++SysTime.T500msF1msAcc>=500)
	{
		SysTime.T500msFlag=1;
		SysTime.T500msF1msAcc=0;
	}
	
}

void User_Main(void)
{
	if(SysTime.T20msFlag)
	{
		SysTime.T20msFlag=0;
			LED=GRENND_LED_ON;
		if((PowerVoltageValue<21000)||(PowerVoltageValue>29000))LED=RED_LED_FLICKER;
		stone();
	}
}



