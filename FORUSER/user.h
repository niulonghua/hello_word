#ifndef __USAR_H__
#define __USAR_H__


#define CAN1_RX_NUM  6  //CAN1���ܱ�������
#define CAN1_TX_NUM  9	//CAN1���ͱ�������
#define CAN2_RX_NUM  2	//CAN2���ܱ�������
#define CAN2_TX_NUM  2	//CAN2���ͱ�������

#define OUTPUT_NOLOAD_ERR_TIME_THRESHOLD 2000		//���ر�����ʱֵ ��λms
#define OUTPUT_OVERLOAD_ERR_TIME_THRESHOLD 500	//���ر�����ʱֵ ��λms
#define PWMFREQUENCY    120.0									//PWMƵ�� ��λHz

typedef struct 
{
	unsigned char SetMode;					//����ģʽ 0������ 1�߿���� 2PWM��� 3�߿ؼ�� 4�Ϳؼ�� 5�߿�Ƶ�ʼ�� 6�Ϳ�Ƶ�ʼ��
	unsigned int SetValue;					//����״̬ ����ģʽ=�߿��� 0����� 1�����
																	//				 ����ģʽ=PWM   ���ռ�ձ�0.1%/bit
	unsigned int GetValue;					//��ȡ״̬ ����ģʽ=�߿ؼ�⡢�Ϳؼ��ʱ  0���ź� 1���ź�
																	//					����ģʽ=�߿�Ƶ�ʼ�⡢�Ϳ�Ƶ�ʼ��   Ƶ��ֵ  1rmp/bit
	unsigned char EquStatus;				//��״̬ 0 off 1 on 2���� 3���� 
	unsigned int CurrentValue;		 //����ֵ	1mA/bit
	unsigned int NoLoadThreshold;		//���ط�ֵ  1mA/bit
	unsigned int OverLoadThreshold;	//���ط�ֵ 1mA/bit
}_X1_X12;

typedef struct
{
	unsigned char TestMode;					//����ģʽ  0��ѹ��� 1�������ģʽ
	unsigned int GetValue;					//��ȡ״̬  ����ģʽ=��ѹ���  ����ѹֵ1mV/bit
																	//          ����ģʽ=�������  ������ֵ0.1mA/bit
}_AI1_AI5;

typedef struct
{
	unsigned int CurrentValue;			//����ֵ 1mA/bit
}_FB1_FB3;

typedef struct
{
	unsigned char SetOnOffStatus;		//����״̬ 0����  1����
	unsigned int VoltageValue;			//��ѹֵ 1mV/bit
	unsigned int CurrentValue;			//����ֵ 1mA/bit
}_V_SENEOR;//+5V���״̬

typedef enum
{
	LED_OFF=0,
	GRENND_LED_ON=1,
	RED_LED_ON=2,
	YELLOW_LED_ON=3,
	RED_THEN_GREEN_FLICKER=4,
	RED_LED_FLICKER=5,
	GREEN_LED_FLICKER=6
}LED_Type;//��״̬

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

#define	X1	0	//�߿������PWM������߿ؼ�⡢�Ϳؼ��
#define	X2	1	//�߿������PWM������߿ؼ�⡢�Ϳؼ��
#define	X3	2	//�߿������PWM������߿ؼ�⡢�Ϳؼ��
#define	X4	3	//�߿������PWM������߿ؼ�⡢�Ϳؼ��
#define	X5	4	//�߿������PWM������߿ؼ�⡢�Ϳؼ��
#define	X6	5	//�߿������PWM������߿ؼ�⡢�Ϳؼ��
#define	X7	6	//�߿�������߿ؼ�⡢�Ϳؼ��
#define	X8	7	//�߿�������߿ؼ�⡢�Ϳؼ��
#define	X9	8	//�߿ؼ�⡢�Ϳؼ�⡢�߿�Ƶ�ʼ�⡢�Ϳ�Ƶ�ʼ��
#define	X10	9	//�߿ؼ�⡢�Ϳؼ�⡢�߿�Ƶ�ʼ�⡢�Ϳ�Ƶ�ʼ��
#define	X11	10//�߿ؼ�⡢�Ϳؼ�⡢�߿�Ƶ�ʼ�⡢�Ϳ�Ƶ�ʼ��
#define	X12	11//�߿ؼ�⡢�Ϳؼ�⡢�߿�Ƶ�ʼ�⡢�Ϳ�Ƶ�ʼ��

#define AI1	0//0-55V���
#define AI2	1//0-10V���
#define AI3	2//0-10V��⡢0-50mA���
#define AI4	3//0-10V��⡢0-50mA���
#define AI5	4//0-10V���

#define FB1 0//0-4A���
#define FB2 1//0-4A���
#define FB3 2//0-4A���


extern _X1_X12	 X[12];
extern _AI1_AI5	 AI[5];
extern _FB1_FB3  FB[3];
extern LED_Type  LED;
extern unsigned int PowerVoltageValue;//��Դ��ѹ1mV/bit
extern _V_SENEOR SensorPower;
extern unsigned int DacSetValue;			//0-20mA��� 0.1mA/bit

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
	unsigned int ID;						//��ַ. 
	CAN_IDE_TypeDef IDE;				//֡����	 ��׼֡��0 	��չ֡��1
	CAN_RTR_TypeDef RTR;				//��ʶ��  ����֡��0	Զ��֡��1
	unsigned int DLC;						//���ݳ��� 0-8
	unsigned char Data[8];
	unsigned short Time1msAcc;
	unsigned char ErrFlag;			//ͨѶ�쳣��־λ
	unsigned char GetDataFlag;	//�������ݱ�־λ
}_CAN_RX;

typedef struct 
{
	unsigned int ID;						//��ַ
	CAN_IDE_TypeDef IDE;				//֡����	 ��׼֡��0 	��չ֡��1
	CAN_RTR_TypeDef RTR;				//��ʶ��  ����֡��0	Զ��֡��1
	unsigned int DLC;						//���ݳ��� 0-8
	unsigned char Data[8];
	CAN_SendMode_TypeDef SendMode; //����ģʽ 0ѭ��  1����
	unsigned char SendFlag;			//���ͱ�־λ
	unsigned int SendCycle;			//�������� ��λ1ms
	unsigned int Time1msAcc;		//���ͼ�ʱ
}_CAN_TX;

extern LED_Type  LED;

extern _CAN_RX  CAN1Rx[CAN1_RX_NUM];
extern _CAN_TX  CAN1Tx[CAN1_TX_NUM];
extern _CAN_RX  CAN2Rx[CAN2_RX_NUM];
extern _CAN_TX  CAN2Tx[CAN2_TX_NUM];

/*****************************CAN*****************************************/
extern void App_Eeprom_Write(unsigned short Addr,unsigned short *DataBuffer,unsigned short WriteNum);//Addr:0-512 DataBuffer:��д������ WriteNum��д����������
extern void App_Epprom_Read(unsigned short Addr,unsigned short *DataBuffer,unsigned short ReadNum);//Addr:0-512 DataBuffer:����ȡ���� ReadNum����ȡ��������

extern void User_Init(void);
extern void User_1mm_Interrupt(void);
extern void User_Main(void);

#endif



