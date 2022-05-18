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
	UINT16 Spd_shengyunqi;	//升运器转速
	UINT16 Spd_getai;				//割台转速
	UINT16 Spd_yijifan;			//一级风级
	UINT16 Spd_erjifan;			//二级风机
	UINT Spd_Drive;				//行驶速度
	UINT16 Hig_getai;				//割台高度
	
		BYTE DI_Clo_zhulihe;		//主离合开关关
		BYTE DI_dang1;		//1档
		BYTE DI_dang2;		//2档
		BYTE DI_dang3;		//3档
		BYTE DI_dang4;		//4档
		BYTE DI_Open_zhulihe;		//主离合开关开
		BYTE DI_Open_shusqi;		//割台输送器开
		BYTE DI_Clo_shusqi;			//割台输送器关
		BYTE DI_Park;				//手刹
		BYTE DI_break;			//刹车开关
		BYTE DI_Up_fuzhulun;		//辅助轮升
		BYTE DI_Dw_fuzhulun;		//辅助轮降
		BYTE DI_Up_guosui;		//果穗箱升
		BYTE DI_Dw_guosui;		//果穗箱降
		BYTE DI_eUp_guosui;		//果穗箱二级升
		BYTE DI_eDw_guosui;		//果穗箱二级降
		BYTE DI_Open_fangx;		//仿形开关开
		BYTE DI_Clo_fangx;		//仿形开关关
		BYTE DI_Up_getai;		//割台点动升
		BYTE DI_Dw_getai;		//割台点动降
		BYTE DI_Up_zhaisui;					//摘穗升		//12V 
		BYTE DI_Dw_zhaisui;					//摘穗降		//12V 
		BYTE DI_GetaiB;	
		BYTE DI_SW41;	
		BYTE DI_SW42;	
		
}_InData;

typedef struct 
{
	//比例阀
	UINT16 PWM_Up_getai;		//割台升
	UINT16 PWM_Dw_getai;		//割台降
	UINT16 PWM_getai;				//割台泵
	UINT16 PWM_getaiF;				//割台泵
	UINT16 PWM_yijifan;			//一级风机
	UINT16 PWM_erjifan;			//二级风机
	
	//开关阀
	BYTE  Val_huandang;				//换挡主阀
	BYTE  Val_dang1;					//换挡1
	BYTE  Val_dang2;					//换挡2
	BYTE  Val_dang3;					//换挡3
	BYTE  Val_dang4;					//换挡4
	
	BYTE  Val_xiehe;					//卸荷阀
	BYTE  Val_zhulihe;				//主离合阀
	BYTE  Val_shusqi;					//割台输送器
	BYTE  Val_drive;					//行走阀
	BYTE  Val_break;					//刹车灯
	BYTE  Val_Up_fuzhulun;					//辅助轮升
	BYTE  Val_Dw_fuzhulun;					//辅助轮降
	BYTE  Val_Up_guosui;					//果穗箱升
	BYTE  Val_Dw_guosui;					//果穗箱降
	BYTE  Val_eUp_guosui;					//果穗箱二级升
	BYTE  Val_eDw_guosui;					//果穗箱二级降
	BYTE  Val_spare1;					//备
	BYTE  Val_spare2;					//备
	BYTE  Val_Up_zhaisui;					//摘穗升		//12V 
	BYTE  Val_Dw_zhaisui;					//摘穗降		//12V 
}_OutData;

typedef struct 
{
	//开关阀
	BYTE  Val_huandang;				//换挡主阀
	BYTE  Val_dang1;					//换挡1
	BYTE  Val_dang2;					//换挡2
	BYTE  Val_dang3;					//换挡3
	BYTE  Val_dang4;					//换挡4
	
	BYTE  Val_xiehe;					//卸荷阀
	BYTE  Val_zhulihe;				//主离合阀
	BYTE  Val_shusqi;					//割台输送器
	BYTE  Val_drive;					//行走阀
	BYTE  Val_break;					//刹车灯
	BYTE  Val_Up_fuzhulun;					//辅助轮升
	BYTE  Val_Dw_fuzhulun;					//辅助轮降
	BYTE  Val_Up_guosui;					//果穗箱升
	BYTE  Val_Dw_guosui;					//果穗箱降
	BYTE  Val_eUp_guosui;					//果穗箱二级升
	BYTE  Val_eDw_guosui;					//果穗箱二级降
	BYTE  Val_spare1;					//备
	BYTE  Val_spare2;					//备
	BYTE  Val_Up_zhaisui;					//摘穗升		//12V 
	BYTE  Val_Dw_zhaisui;					//摘穗降		//12V 
}_FBData;

typedef struct 
{
	UINT16 Knob_UD_getai;		//割台升降控制
	UINT16 Knob_getai;			//割台转速控制
	UINT16 Knob_yijifan;		//一级风机
	UINT16 Knob_erjifan;		//二级风机
	BYTE  Led_UD;						//升降led
	BYTE 	DI_qiehuan;				//
	BYTE 	Led_qiehuan;			//
	BYTE 	DI_UPDW;					//
	BYTE  Led_Alarm;				//
	BYTE  Led_Hig_getai;		//
}_Panel;

typedef struct 
{
	UINT16 pan_UD_getai;		//割台升降控制
	UINT16 pan_getai;				//割台转速控制
	UINT16 pan_yijifan;			//一级风机
	UINT16 pan_erjifan;			//二级风机
	UINT16 Hig_getai;				//割台高度
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
	UINT16 DangW;				//档位保存
	UINT16 Rit_GtDv;		//割台转速与行走速度比例
	UINT16 Hig_FX;			//仿形高度设置
	UINT16 Hig_FxDead;			//仿形高度设置
	UINT16	Snr_Start_Step[5][3];	//Start End	Step
	UINT16	Val_MaxMinRes[5][3];	//Max Min	Res
	UINT16	Val_AccDcc[6][2];	//加减速
	UINT16 	KeySnak;			//按键去抖
	UINT16 	LichengL;			//低4位
	UINT16 	LichengH;			  		//gaowei
	UINT16 	Lichengm;			  		//mi
	UINT16  diandsd;						//点动速度
	UINT16  jixing;						//机型
	UINT16  jbSpd1;						//割台基本速度
}_Par;



int stone(void);
int yu_Init(void);
int yu_Connect(BYTE);
int yu_IN_OUT(BYTE);
int yu_Cyc(void);
int lvbo(void);
unsigned char Key_to_shake(unsigned char ,unsigned char*);

#endif

