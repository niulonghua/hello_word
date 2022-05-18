#ifndef __YU_H__
#define __YU_H__

#include "senor.h"
#include "smooth_p.h"
#include "SDO.h"
#define true 1
#define false 0

typedef unsigned int UINT;
typedef unsigned short UINT16;	
typedef unsigned char BYTE;	

typedef struct 
{
	UINT16 Spd_shengyunqi;	//������ת��
	UINT16 Spd_getai;				//��̨ת��
	UINT16 Spd_yijifan;			//һ���缶
	UINT16 Spd_erjifan;			//�������
	UINT Spd_Drive;				//��ʻ�ٶ�
	UINT16 Hig_getai;				//��̨�߶�
	
		BYTE DI_Clo_zhulihe;		//����Ͽ��ع�
		BYTE DI_dang1;		//1��
		BYTE DI_dang2;		//2��
		BYTE DI_dang3;		//3��
		BYTE DI_dang4;		//4��
		BYTE DI_Open_zhulihe;		//����Ͽ��ؿ�
		BYTE DI_Open_shusqi;		//��̨��������
		BYTE DI_Clo_shusqi;			//��̨��������
		BYTE DI_Park;				//��ɲ
		BYTE DI_break;			//ɲ������
		BYTE DI_Up_fuzhulun;		//��������
		BYTE DI_Dw_fuzhulun;		//�����ֽ�
		BYTE DI_Up_guosui;		//��������
		BYTE DI_Dw_guosui;		//�����併
		BYTE DI_eUp_guosui;		//�����������
		BYTE DI_eDw_guosui;		//�����������
		BYTE DI_Open_fangx;		//���ο��ؿ�
		BYTE DI_Clo_fangx;		//���ο��ع�
		BYTE DI_Up_getai;		//��̨�㶯��
		BYTE DI_Dw_getai;		//��̨�㶯��
		BYTE DI_Up_zhaisui;					//ժ����		//12V 
		BYTE DI_Dw_zhaisui;					//ժ�뽵		//12V 
		BYTE DI_GetaiB;	
		BYTE DI_SW41;	
		BYTE DI_SW42;	
		
}_InData;

typedef struct 
{
	//������
	UINT16 PWM_Up_getai;		//��̨��
	UINT16 PWM_Dw_getai;		//��̨��
	UINT16 PWM_getai;				//��̨��
	UINT16 PWM_getaiF;				//��̨��
	UINT16 PWM_yijifan;			//һ�����
	UINT16 PWM_erjifan;			//�������
	
	//���ط�
	BYTE  Val_huandang;				//��������
	BYTE  Val_dang1;					//����1
	BYTE  Val_dang2;					//����2
	BYTE  Val_dang3;					//����3
	BYTE  Val_dang4;					//����4
	
	BYTE  Val_xiehe;					//ж�ɷ�
	BYTE  Val_zhulihe;				//����Ϸ�
	BYTE  Val_shusqi;					//��̨������
	BYTE  Val_drive;					//���߷�
	BYTE  Val_break;					//ɲ����
	BYTE  Val_Up_fuzhulun;					//��������
	BYTE  Val_Dw_fuzhulun;					//�����ֽ�
	BYTE  Val_Up_guosui;					//��������
	BYTE  Val_Dw_guosui;					//�����併
	BYTE  Val_eUp_guosui;					//�����������
	BYTE  Val_eDw_guosui;					//�����������
	BYTE  Val_spare1;					//��
	BYTE  Val_spare2;					//��
	BYTE  Val_Up_zhaisui;					//ժ����		//12V 
	BYTE  Val_Dw_zhaisui;					//ժ�뽵		//12V 
}_OutData;

typedef struct 
{
	//���ط�
	BYTE  Val_huandang;				//��������
	BYTE  Val_dang1;					//����1
	BYTE  Val_dang2;					//����2
	BYTE  Val_dang3;					//����3
	BYTE  Val_dang4;					//����4
	
	BYTE  Val_xiehe;					//ж�ɷ�
	BYTE  Val_zhulihe;				//����Ϸ�
	BYTE  Val_shusqi;					//��̨������
	BYTE  Val_drive;					//���߷�
	BYTE  Val_break;					//ɲ����
	BYTE  Val_Up_fuzhulun;					//��������
	BYTE  Val_Dw_fuzhulun;					//�����ֽ�
	BYTE  Val_Up_guosui;					//��������
	BYTE  Val_Dw_guosui;					//�����併
	BYTE  Val_eUp_guosui;					//�����������
	BYTE  Val_eDw_guosui;					//�����������
	BYTE  Val_spare1;					//��
	BYTE  Val_spare2;					//��
	BYTE  Val_Up_zhaisui;					//ժ����		//12V 
	BYTE  Val_Dw_zhaisui;					//ժ�뽵		//12V 
}_FBData;

typedef struct 
{
	UINT16 Knob_UD_getai;		//��̨��������
	UINT16 Knob_getai;			//��̨ת�ٿ���
	UINT16 Knob_yijifan;		//һ�����
	UINT16 Knob_erjifan;		//�������
	BYTE  Led_UD;						//����led
	BYTE 	DI_qiehuan;				//
	BYTE 	Led_qiehuan;			//
	BYTE 	DI_UPDW;					//
	BYTE  Led_Alarm;				//
	BYTE  Led_Hig_getai;		//
}_Panel;

typedef struct 
{
	UINT16 pan_UD_getai;		//��̨��������
	UINT16 pan_getai;				//��̨ת�ٿ���
	UINT16 pan_yijifan;			//һ�����
	UINT16 pan_erjifan;			//�������
	UINT16 Hig_getai;				//��̨�߶�
}_Senor;

typedef struct 
{
	UINT Speed;
	UINT16 DangW;
	BYTE	GeTaiUp;
	BYTE	GeTaiDw;
	UINT Sped[5];
	UINT Licheng;
	BYTE lichengm;
}_Temp;

typedef struct 
{
	_InData 	In;
	_OutData 	Out;
	_FBData 	Fb;	
	_Panel 		Panel;
		BYTE   back;
}_localData;


typedef struct 
{
	UINT16 INIT;
	UINT16 DangW;				//��λ����
	UINT16 Rit_GtDv;		//��̨ת���������ٶȱ���
	UINT16 Hig_FX;			//���θ߶�����
	UINT16 Hig_FxDead;			//���θ߶�����
	UINT16	Snr_Start_Step[5][3];	//Start End	Step
	UINT16	Val_MaxMinRes[5][3];	//Max Min	Res
	UINT16	Val_AccDcc[6][2];	//�Ӽ���
	UINT16 	KeySnak;			//����ȥ��
	UINT16 	LichengL;			//��4λ
	UINT16 	LichengH;			  		//gaowei
	UINT16 	Lichengm;			  		//mi
	UINT16  diandsd;						//�㶯�ٶ�
	UINT16  jixing;						//����
	UINT16  jbSpd1;						//��̨�����ٶ�
}_Par;



int stone(void);
int yu_Init(void);
int yu_Connect(BYTE);
int yu_IN_OUT(BYTE);
int yu_Cyc(void);
int lvbo(void);
unsigned char Key_to_shake(unsigned char ,unsigned char*);

#endif

