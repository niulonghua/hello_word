#ifndef __USAR_H__
#define __USAR_H__


#define CAN1_RX_NUM  6  //CAN1接受报文数量
#define CAN1_TX_NUM  9	//CAN1发送报文数量
#define CAN2_RX_NUM  2	//CAN2接受报文数量
#define CAN2_TX_NUM  2	//CAN2发送报文数量

#define OUTPUT_NOLOAD_ERR_TIME_THRESHOLD 2000		//空载报警延时值 单位ms
#define OUTPUT_OVERLOAD_ERR_TIME_THRESHOLD 500	//过载报警延时值 单位ms
#define PWMFREQUENCY    120.0									//PWM频率 单位Hz

typedef struct 
{
	unsigned char SetMode;					//工作模式 0不工作 1高控输出 2PWM输出 3高控检测 4低控检测 5高控频率检测 6低控频率检测
	unsigned int SetValue;					//设置状态 工作模式=高控输 0不输出 1输出高
																	//				 工作模式=PWM   输出占空比0.1%/bit
	unsigned int GetValue;					//获取状态 工作模式=高控检测、低控检测时  0无信号 1有信号
																	//					工作模式=高控频率检测、低控频率检测   频率值  1rmp/bit
	unsigned char EquStatus;				//备状态 0 off 1 on 2空载 3过流 
	unsigned int CurrentValue;		 //电流值	1mA/bit
	unsigned int NoLoadThreshold;		//空载阀值  1mA/bit
	unsigned int OverLoadThreshold;	//过载阀值 1mA/bit
}_X1_X12;

typedef struct
{
	unsigned char TestMode;					//测试模式  0电压检测 1电流检测模式
	unsigned int GetValue;					//获取状态  测试模式=电压检测  检测电压值1mV/bit
																	//          测试模式=电流检测  检测电流值0.1mA/bit
}_AI1_AI5;

typedef struct
{
	unsigned int CurrentValue;			//电流值 1mA/bit
}_FB1_FB3;

typedef struct
{
	unsigned char SetOnOffStatus;		//开关状态 0：关  1：打开
	unsigned int VoltageValue;			//电压值 1mV/bit
	unsigned int CurrentValue;			//电流值 1mA/bit
}_V_SENEOR;//+5V输出状态

typedef enum
{
	LED_OFF=0,
	GRENND_LED_ON=1,
	RED_LED_ON=2,
	YELLOW_LED_ON=3,
	RED_THEN_GREEN_FLICKER=4,
	RED_LED_FLICKER=5,
	GREEN_LED_FLICKER=6
}LED_Type;//灯状态

typedef struct 
{
	unsigned int sys_1ms_acc;
	unsigned short T10msF1msAcc;
	unsigned char T10msFlag;
	unsigned short T20msF1msAcc;
	unsigned char T20msFlag;
	unsigned short T50msF1msAcc;
	unsigned char T50msFlag;
	unsigned short T100msF1msAcc;
	unsigned char T100msFlag;
	unsigned short T200msF1msAcc;
	unsigned char T200msFlag;
	unsigned short T500msF1msAcc;
	unsigned char T500msFlag;
	
}_TIME_SYS;

#define	X1	0	//高控输出、PWM输出、高控检测、低控检测
#define	X2	1	//高控输出、PWM输出、高控检测、低控检测
#define	X3	2	//高控输出、PWM输出、高控检测、低控检测
#define	X4	3	//高控输出、PWM输出、高控检测、低控检测
#define	X5	4	//高控输出、PWM输出、高控检测、低控检测
#define	X6	5	//高控输出、PWM输出、高控检测、低控检测
#define	X7	6	//高控输出、高控检测、低控检测
#define	X8	7	//高控输出、高控检测、低控检测
#define	X9	8	//高控检测、低控检测、高控频率检测、低控频率检测
#define	X10	9	//高控检测、低控检测、高控频率检测、低控频率检测
#define	X11	10//高控检测、低控检测、高控频率检测、低控频率检测
#define	X12	11//高控检测、低控检测、高控频率检测、低控频率检测

#define AI1	0//0-55V检测
#define AI2	1//0-10V检测
#define AI3	2//0-10V检测、0-50mA检测
#define AI4	3//0-10V检测、0-50mA检测
#define AI5	4//0-10V检测

#define FB1 0//0-4A检测
#define FB2 1//0-4A检测
#define FB3 2//0-4A检测


extern _X1_X12	 X[12];
extern _AI1_AI5	 AI[5];
extern _FB1_FB3  FB[3];
extern LED_Type  LED;
extern unsigned int PowerVoltageValue;//电源电压1mV/bit
extern _V_SENEOR SensorPower;
extern unsigned int DacSetValue;			//0-20mA输出 0.1mA/bit

/*****************************CAN*****************************************/
typedef enum
{
	CAN_IDE_STD = 0,
	CAN_IDE_EXT
}CAN_IDE_TypeDef;

typedef enum
{
	CAN_RTR_STD = 0,
	CAN_RTR_RMT
}CAN_RTR_TypeDef;

typedef enum
{
	CAN_SEND_MSG_FILED = 0,
	CAN_SEND_MSG_SUCCS
}CAN_SendSts_TypeDef;

typedef enum
{
	FILTER_IDE_STD_ONLY 	= 0,
	FILTER_IDE_EXT_ONLY 	= 1,
	FILTER_IDE_STD_EXT_BOTH	= 2
}CAN_FilterMask_TypeDef;

typedef enum
{
	CAN_FILTER_CODE_MODE	= 0,
	CAN_FILTER_MASK_MODE	= 1,
}CAN_FilterMode_TypeDef;

typedef enum
{
	CIRCULATION	= 0,
	TRIGGER	= 1,
}CAN_SendMode_TypeDef;

typedef struct 
{
	unsigned int ID;						//地址. 
	CAN_IDE_TypeDef IDE;				//帧类型	 标准帧：0 	扩展帧：1
	CAN_RTR_TypeDef RTR;				//标识符  数据帧：0	远程帧：1
	unsigned int DLC;						//数据长度 0-8
	unsigned char Data[8];
	unsigned short Time1msAcc;
	unsigned char ErrFlag;			//通讯异常标志位
	unsigned char GetDataFlag;	//接受数据标志位
}_CAN_RX;

typedef struct 
{
	unsigned int ID;						//地址
	CAN_IDE_TypeDef IDE;				//帧类型	 标准帧：0 	扩展帧：1
	CAN_RTR_TypeDef RTR;				//标识符  数据帧：0	远程帧：1
	unsigned int DLC;						//数据长度 0-8
	unsigned char Data[8];
	CAN_SendMode_TypeDef SendMode; //发送模式 0循环  1触发
	unsigned char SendFlag;			//发送标志位
	unsigned int SendCycle;			//发送周期 单位1ms
	unsigned int Time1msAcc;		//发送计时
}_CAN_TX;

extern LED_Type  LED;

extern _CAN_RX  CAN1Rx[CAN1_RX_NUM];
extern _CAN_TX  CAN1Tx[CAN1_TX_NUM];
extern _CAN_RX  CAN2Rx[CAN2_RX_NUM];
extern _CAN_TX  CAN2Tx[CAN2_TX_NUM];

/*****************************CAN*****************************************/
extern void App_Eeprom_Write(unsigned short Addr,unsigned short *DataBuffer,unsigned short WriteNum);//Addr:0-512 DataBuffer:待写入数据 WriteNum：写入数据数量
extern void App_Epprom_Read(unsigned short Addr,unsigned short *DataBuffer,unsigned short ReadNum);//Addr:0-512 DataBuffer:待读取数据 ReadNum：读取数据数量

extern void User_Init(void);
extern void User_1mm_Interrupt(void);
extern void User_Main(void);

#endif



