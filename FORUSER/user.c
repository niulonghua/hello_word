#include "user.h"
#include "yu.h"

//=====================ϵͳ����========================
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

//==================�û�����===========================

//=====================================================



void User_Init(void)
{
	SensorPower.SetOnOffStatus=1; 
	//X1-X12��ʼ��
	X[X1].SetMode=2;							//����ģʽ 0������ 1�߿���� 2PWM��� 3�߿ؼ�� 4�Ϳؼ�� 
	X[X1].SetValue=0;							//����״̬ ����ģʽ=�߿��� 0����� 1�����
	X[X1].NoLoadThreshold=400;		//���ط�ֵ  1mA/bit
	X[X1].OverLoadThreshold=5000;	//���ط�ֵ 1mA/bit
	
	X[X2].SetMode=2;							//����ģʽ 0������ 1�߿���� 2PWM��� 3�߿ؼ�� 4�Ϳؼ�� 
	X[X2].SetValue=0;							//����״̬ ����ģʽ=�߿��� 0����� 1�����
	X[X2].NoLoadThreshold=400;		//���ط�ֵ  1mA/bit
	X[X2].OverLoadThreshold=5000;	//���ط�ֵ 1mA/bit
	X[X3].SetMode=2;							//����ģʽ 0������ 1�߿���� 2PWM��� 3�߿ؼ�� 4�Ϳؼ�� 
	X[X3].SetValue=0;							//����״̬ ����ģʽ=�߿��� 0����� 1�����
	X[X3].NoLoadThreshold=400;		//���ط�ֵ  1mA/bit
	X[X3].OverLoadThreshold=5000;	//���ط�ֵ 1mA/bit
	X[X4].SetMode=2;							//����ģʽ 0������ 1�߿���� 2PWM��� 3�߿ؼ�� 4�Ϳؼ�� 
	X[X4].SetValue=0;							//����״̬ ����ģʽ=�߿��� 0����� 1�����
	X[X4].NoLoadThreshold=400;		//���ط�ֵ  1mA/bit
	X[X4].OverLoadThreshold=5000;	//���ط�ֵ 1mA/bit
	X[X5].SetMode=2;							//����ģʽ 0������ 1�߿���� 2PWM��� 3�߿ؼ�� 4�Ϳؼ�� 
	X[X5].SetValue=0;							//����״̬ ����ģʽ=�߿��� 0����� 1�����
	X[X5].NoLoadThreshold=400;		//���ط�ֵ  1mA/bit
	X[X5].OverLoadThreshold=5000;	//���ط�ֵ 1mA/bit
	X[X6].SetMode=2;							//����ģʽ 0������ 1�߿���� 2PWM��� 3�߿ؼ�� 4�Ϳؼ�� 
	X[X6].SetValue=0;							//����״̬ ����ģʽ=�߿��� 0����� 1�����
	X[X6].NoLoadThreshold=400;		//���ط�ֵ  1mA/bit
	X[X6].OverLoadThreshold=5000;	//���ط�ֵ 1mA/bit
	X[X7].SetMode=3;							//����ģʽ 0������ 1�߿���� 3�߿ؼ�� 4�Ϳؼ�� 5�߿�Ƶ�ʼ�� 6�Ϳ�Ƶ�ʼ��
	X[X7].SetValue=0;							//����״̬ ����ģʽ=�߿��� 0����� 1�����
	X[X7].NoLoadThreshold=400;		//���ط�ֵ  1mA/bit
	X[X7].OverLoadThreshold=5000;	//���ط�ֵ 1mA/bit
	X[X8].SetMode=5;							//����ģʽ 0������ 1�߿���� 3�߿ؼ�� 4�Ϳؼ�� 5�߿�Ƶ�ʼ�� 6�Ϳ�Ƶ�ʼ��
	X[X8].SetValue=0;							//����״̬ ����ģʽ=�߿��� 0����� 1�����
	X[X8].NoLoadThreshold=400;		//���ط�ֵ  1mA/bit
	X[X8].OverLoadThreshold=5000;	//���ط�ֵ 1mA/bit
	
	X[X9].SetMode=5;							//����ģʽ 0������  3�߿ؼ�� 4�Ϳؼ�� 5�߿�Ƶ�ʼ�� 6�Ϳ�Ƶ�ʼ��
	X[X10].SetMode=5;							//����ģʽ 0������  3�߿ؼ�� 4�Ϳؼ�� 5�߿�Ƶ�ʼ�� 6�Ϳ�Ƶ�ʼ��
	X[X11].SetMode=5;							//����ģʽ 0������  3�߿ؼ�� 4�Ϳؼ�� 5�߿�Ƶ�ʼ�� 6�Ϳ�Ƶ�ʼ��
	X[X12].SetMode=5;							//����ģʽ 0������  3�߿ؼ�� 4�Ϳؼ�� 5�߿�Ƶ�ʼ�� 6�Ϳ�Ƶ�ʼ��

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
		
	//AI1-AI5��ʼ��
	AI[AI1].TestMode=0;						//����ģʽ  0��ѹ��� 
	AI[AI2].TestMode=0;						//����ģʽ  0��ѹ��� 
	AI[AI3].TestMode=0;						//����ģʽ  0��ѹ��� 1�������ģʽ
	AI[AI4].TestMode=0;						//����ģʽ  0��ѹ��� 1�������ģʽ
	AI[AI5].TestMode=0;						//����ģʽ  0��ѹ��� 
	
	//LED��ʼ��
	LED=RED_THEN_GREEN_FLICKER;

	//CAN��ʼ��
		//===========CAN1����֡==================
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
	
	//===========CAN1����֡==================
	CAN1Tx[0].ID=0x181;
	CAN1Tx[0].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[0].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[0].DLC=8;
	CAN1Tx[0].SendCycle=100;
	CAN1Tx[0].SendMode=CIRCULATION;//ѭ��ģʽ
	
	CAN1Tx[1].ID=0x281;
	CAN1Tx[1].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[1].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[1].DLC=8;
	CAN1Tx[1].SendCycle=100;
	CAN1Tx[1].SendMode=CIRCULATION;//ѭ��ģʽ
	
	CAN1Tx[2].ID=0x581;
	CAN1Tx[2].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[2].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[2].DLC=8;
	CAN1Tx[2].SendCycle=40;
	CAN1Tx[2].SendMode=TRIGGER;//����ģʽ
	
	CAN1Tx[3].ID=0x381;
	CAN1Tx[3].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[3].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[3].DLC=8;
	CAN1Tx[3].SendCycle=100;
	CAN1Tx[3].SendMode=CIRCULATION;//ѭ��ģʽ
	
	CAN1Tx[4].ID=0x382;
	CAN1Tx[4].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[4].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[4].DLC=8;
	CAN1Tx[4].SendCycle=100;
	CAN1Tx[4].SendMode=CIRCULATION;//ѭ��ģʽ
	
	CAN1Tx[5].ID=0x383;
	CAN1Tx[5].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[5].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[5].DLC=8;
	CAN1Tx[5].SendCycle=100;
	CAN1Tx[5].SendMode=CIRCULATION;//ѭ��ģʽ
	
	CAN1Tx[6].ID=0x384;
	CAN1Tx[6].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[6].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[6].DLC=8;
	CAN1Tx[6].SendCycle=100;
	CAN1Tx[6].SendMode=CIRCULATION;//ѭ��ģʽ
	
	CAN1Tx[7].ID=0x385;
	CAN1Tx[7].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[7].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[7].DLC=8;
	CAN1Tx[7].SendCycle=100;
	CAN1Tx[7].SendMode=CIRCULATION;//ѭ��ģʽ
	
	CAN1Tx[8].ID=0x386;
	CAN1Tx[8].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[8].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[8].DLC=8;
	CAN1Tx[8].SendCycle=100;
	CAN1Tx[8].SendMode=CIRCULATION;//ѭ��ģʽ
	/*	
	CAN1Tx[1].ID=0x103;
	CAN1Tx[1].IDE=CAN_IDE_STD;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN1Tx[1].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN1Tx[1].DLC=8;
	CAN1Tx[1].SendCycle=40;
	CAN1Tx[1].SendMode=CIRCULATION; //ѭ��ģʽ
	
	//===========CAN2����֡==================
	CAN2Rx[0].ID=0x01000000;
	CAN2Rx[0].IDE=CAN_IDE_EXT;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN2Rx[0].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN2Rx[0].DLC=8;
	
	CAN2Rx[1].ID=0x01000001;
	CAN2Rx[1].IDE=CAN_IDE_EXT;  //CAN_IDE_STD    CAN_IDE_EXT
	CAN2Rx[1].RTR=CAN_RTR_STD;	//CAN_RTR_STD   CAN_RTR_RMT
	CAN2Rx[1].DLC=8;
	
	//===========CAN2����֡==================
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



