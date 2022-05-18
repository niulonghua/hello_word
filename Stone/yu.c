#include "user.h"
#include "yu.h"
		UINT16 tmp_yijiFan=0,tmp_erjiFan=0,tmp_GeTai=0;
		UINT16 Sth_yijiFan=0,Sth_erjiFan=0,Sth_GeTai=0;
_localData mData;
_Par Par;
_Senor SnorD;
_Temp mTemp;
static BYTE KeyTime[20];
static BYTE OldDang=0;
static UINT16 smoothData[6];
#define wavenub 20

/*
	说明：逻辑处理
*/
int yu_Cyc(void)
{
		////////////////////////主离合开关
		static BYTE Clutch=0,Shusqi=0;
		if(mData.In.DI_Open_zhulihe) 	Clutch=true;
		if(mData.In.DI_Clo_zhulihe) 	Clutch=false;
		mData.Out.Val_zhulihe=Clutch;					//主离合开关
		//////////////////////////割台输送器
		if(mData.In.DI_Open_shusqi & Clutch)		Shusqi=true;
		if((mData.In.DI_Clo_shusqi | (~Clutch))&1)	Shusqi=false;
		mData.Out.Val_shusqi=Shusqi;
		//////////////////一级风机  二级风机  割台泵////////////////////////////////////

		static  BYTE qiehuan=0;
		qiehuan=mData.Panel.DI_qiehuan;
		if(Clutch)
		{
			tmp_yijiFan=SnorD.pan_yijifan;
			tmp_erjiFan=SnorD.pan_erjifan;
			/////////////////////////////////割台泵
			//getai
			if(qiehuan)
			{
				UINT mSped=mTemp.Speed/100*Par.Rit_GtDv;
				if(mData.back)
					tmp_GeTai=Par.jbSpd1;
				else
				{
				if(mSped>30000)
					tmp_GeTai=30000;
				else
					tmp_GeTai=mSped+Par.jbSpd1;
				}
			}
			else
			{
				tmp_GeTai=SnorD.pan_getai;
			}
		}
		else
		{
			tmp_yijiFan	=0;
			tmp_erjiFan	=0;
			tmp_GeTai		=0;
		}
		static  BYTE GeTq=0;
		

		if(mData.In.DI_GetaiB!=GeTq)
		{
			tmp_GeTai=0;
			if(Sth_GeTai<Par.jixing)GeTq=mData.In.DI_GetaiB;
		}

		
		Sth_yijiFan	=smooth(tmp_yijiFan,	Par.Val_AccDcc[0][0],Par.Val_AccDcc[0][1],&smoothData[0]);
		Sth_erjiFan	=smooth(tmp_erjiFan,	Par.Val_AccDcc[1][0],Par.Val_AccDcc[1][1],&smoothData[1]);
		if(qiehuan)
			Sth_GeTai		=smooth(tmp_GeTai,		Par.Val_AccDcc[5][0],Par.Val_AccDcc[5][1],&smoothData[5]);
		else
			Sth_GeTai		=smooth(tmp_GeTai,		Par.Val_AccDcc[2][0],Par.Val_AccDcc[2][1],&smoothData[2]);
		
		
		mData.Out.PWM_yijifan	=PwmOutEx(Sth_yijiFan/30,Par.Val_MaxMinRes[0][0],Par.Val_MaxMinRes[0][1],Par.Val_MaxMinRes[0][2],PowerVoltageValue);
		mData.Out.PWM_erjifan	=PwmOutEx(Sth_erjiFan/30,Par.Val_MaxMinRes[1][0],Par.Val_MaxMinRes[1][1],Par.Val_MaxMinRes[1][2],PowerVoltageValue);
		
		UINT16 Sth_GeTai1=0,Sth_GeTai2=0;
		
		if(mData.In.DI_GetaiB!=GeTq)
		{
			if(mData.In.DI_GetaiB) {Sth_GeTai1=Sth_GeTai;Sth_GeTai2=0;}
			else {Sth_GeTai2=Sth_GeTai;Sth_GeTai1=0;}
				
		}
		else
		{
			if(mData.In.DI_GetaiB) {Sth_GeTai2=Sth_GeTai;Sth_GeTai1=0;}
			else {Sth_GeTai1=Sth_GeTai;Sth_GeTai2=0;}
		}

		
			mData.Out.PWM_getaiF		=PwmOutEx(Sth_GeTai2/30,	Par.Val_MaxMinRes[2][0],Par.Val_MaxMinRes[2][1],Par.Val_MaxMinRes[2][2],PowerVoltageValue);
		
			mData.Out.PWM_getai		=PwmOutEx(Sth_GeTai1/30,	Par.Val_MaxMinRes[2][0],Par.Val_MaxMinRes[2][1],Par.Val_MaxMinRes[2][2],PowerVoltageValue);

		
		if((mData.Out.PWM_getai>100)&&(mData.Out.PWM_getaiF>100)){mData.Out.PWM_getai=0;mData.Out.PWM_getaiF=0;}
		///////////////////////////////行走阀
		mData.Out.Val_drive=(mData.In.DI_break | (~mData.In.DI_Park))&1;

		/////////////////////////////刹车灯
		mData.Out.Val_break=mData.In.DI_break;

		//果穗箱升、果穗箱降,二级果穗箱升、二级果穗箱降，摘穗升、摘穗降
		mData.Out.Val_Up_guosui=mData.In.DI_Up_guosui;
		mData.Out.Val_Dw_guosui=mData.In.DI_Dw_guosui;
		mData.Out.Val_eUp_guosui=mData.In.DI_eUp_guosui;
		mData.Out.Val_eDw_guosui=mData.In.DI_eDw_guosui;
		mData.Out.Val_Up_zhaisui=mData.In.DI_Up_zhaisui;
		mData.Out.Val_Dw_zhaisui=mData.In.DI_Dw_zhaisui;
		
		//////////////////////////////辅助轮升降	打开仿形时，改功能无效 只有检测到仿形高度时，仿形开关才能打开
		//仿形
		static BYTE UPDW=0;
		if(mData.Panel.DI_UPDW==1)
		{
			if(Par.Hig_FX<4000)
			Par.Hig_FX++;
		}
		if(mData.Panel.DI_UPDW==2)
		{
			if(Par.Hig_FX>0)
			Par.Hig_FX--;
		}
		
		if((mData.Panel.DI_UPDW==0)&&(UPDW>0))
			App_Eeprom_Write( 3,&Par.Hig_FX,1);
		
		UPDW=mData.Panel.DI_UPDW;
		
		
		static BYTE FangX=0;
		if((mData.In.DI_Open_fangx)&&(mData.In.Hig_getai>100))FangX=1;
		if(mData.In.DI_Clo_fangx)					FangX=0;
		if(mData.In.DI_Up_getai||(Clutch==0))			FangX=0;//按全速上升时，关闭仿形
		
	//	UINT16 GTup=0,GTdw=0;
			
		if(FangX)
		{
			if(SnorD.Hig_getai>(Par.Hig_FX+Par.Hig_FxDead))mTemp.GeTaiDw=1;else mTemp.GeTaiDw=0;
			if(SnorD.Hig_getai<(Par.Hig_FX-Par.Hig_FxDead))mTemp.GeTaiUp=1;else mTemp.GeTaiUp=0;
			mData.Out.Val_Up_fuzhulun=0 ;//辅助轮升降
			mData.Out.Val_Dw_fuzhulun=0 ;
		}
		else
		{
			mTemp.GeTaiUp=mData.In.DI_Up_getai;				//割台点动升降
			mTemp.GeTaiDw=mData.In.DI_Dw_getai;				//
			mData.Out.Val_Up_fuzhulun=mData.In.DI_Up_fuzhulun ;//辅助轮升降
			mData.Out.Val_Dw_fuzhulun=mData.In.DI_Dw_fuzhulun ;
		}
		if(mTemp.GeTaiUp&mTemp.GeTaiDw){mTemp.GeTaiUp=0;mTemp.GeTaiDw=0;}
		
		UINT16 Out_GTup=0,Out_GTdw=0;
		if(FangX)
		{
			Out_GTup=mTemp.GeTaiUp*SnorD.pan_UD_getai;
			Out_GTdw=mTemp.GeTaiDw*SnorD.pan_UD_getai;
		}
		else
		{
			Out_GTup=mTemp.GeTaiUp*Par.diandsd;
			Out_GTdw=mTemp.GeTaiDw*Par.diandsd;
		}
		//if(mTemp.GeTaiUp|mTemp.GeTaiDw)mData.Out.Val_xiehe=1;
			
		UINT16 Sth_GTup=0,Sth_GTdw=0;
		Sth_GTup	=smooth(Out_GTup,	Par.Val_AccDcc[3][0],Par.Val_AccDcc[3][1],&smoothData[3]);
		Sth_GTdw	=smooth(Out_GTdw,	Par.Val_AccDcc[4][0],Par.Val_AccDcc[4][1],&smoothData[4]);
		////////////按键板指示灯
		if(mTemp.GeTaiUp){Sth_GTdw=0;mData.Panel.Led_UD=1;}
		if(mTemp.GeTaiDw){Sth_GTup=0;mData.Panel.Led_UD=3;}
		if((mTemp.GeTaiDw==0)&&(mTemp.GeTaiUp==0))mData.Panel.Led_UD=0;
		if(mTemp.GeTaiUp&mTemp.GeTaiDw)mData.Panel.Led_UD=4;
		
		
		
		mData.Out.PWM_Up_getai	=PwmOutEx(Sth_GTup/30,Par.Val_MaxMinRes[3][0],Par.Val_MaxMinRes[3][1],Par.Val_MaxMinRes[3][2],PowerVoltageValue);
		mData.Out.PWM_Dw_getai	=PwmOutEx(Sth_GTdw/30,Par.Val_MaxMinRes[4][0],Par.Val_MaxMinRes[4][1],Par.Val_MaxMinRes[4][2],PowerVoltageValue);
		if(SnorD.Hig_getai>Par.Snr_Start_Step[0][0])
		mData.Panel.Led_Hig_getai=(SnorD.Hig_getai)/300;
		else mData.Panel.Led_Hig_getai=0;
		
		CAN1Tx[4].Data[7]=FangX|(mData.In.DI_SW41<<6)|(mData.In.DI_SW42<<7);
		///////////////////////////////////////////////////行驶速度

		if(mData.In.DI_dang1)mTemp.DangW=1;
		if(mData.In.DI_dang2)mTemp.DangW=2;
		if(mData.In.DI_dang3)mTemp.DangW=3;
		if(mData.In.DI_dang4)mTemp.DangW=4;
		if(mTemp.DangW!=OldDang)
		{
			Par.DangW=mTemp.DangW;
			App_Eeprom_Write( 1,&Par.DangW,1);
		}
		OldDang=mTemp.DangW;
		UINT Speed=0;
		if(mTemp.DangW==1)
			Speed=mData.In.Spd_Drive*3/33.0/2.615/15.6*60*2.6376;
		else if(mTemp.DangW==2)
			Speed=mData.In.Spd_Drive*3/33.0/2.615/15.6*60*2.6376*2.0743;		
		else if(mTemp.DangW==3)
			Speed=mData.In.Spd_Drive*3/33.0/0.6786/15.6*60*2.6376;	
		else if(mTemp.DangW==4)
			Speed=mData.In.Spd_Drive*3/33.0/0.6786/15.6*60*2.6376*2.0743;	
		

		

		static UINT Spd[15];
		UINT Vtemp=0;
		for(int n=1;n<15;n++)
		{
			Spd[15-n]=Spd[15-n-1];
		}
		Spd[0]=Speed;
		for(int n=0;n<15;n++)
		{
			Vtemp+=(Spd[n]/15);
		}
		mTemp.Speed=Vtemp;
		
		////////////////////////////////licheng
		static long temp=0;
		static long templic=0;
		static UINT16 Nub=0;
		static UINT16 Nubbc=0;
		if(Nub<49)			//1s
		{
			Nub++;
			temp=temp+mTemp.Speed;
		}
		else
		{
			Nub=0;
			templic=(temp+mTemp.Speed)/3600.0/50.0+mTemp.lichengm;
			temp=0;
			mTemp.Licheng=mTemp.Licheng+templic/100;
			mTemp.lichengm=templic%100;
		
			if(Nubbc==29)
			{
				App_Eeprom_Write(50,&Par.Lichengm,1);
			}

			if(Nubbc<59)
			{
				Nubbc++;
			}
			else
			{
				Nubbc=0;
				Par.LichengL=mTemp.Licheng;
				
				App_Eeprom_Write(48,&Par.LichengL,1);
				if(Par.LichengH!=(mTemp.Licheng>>16))
				{
					Par.LichengH=mTemp.Licheng>>16;
						App_Eeprom_Write(49,&Par.LichengH,1);
				}
			}
		}
		

		
		
		
	return 0;
}

int stone(void)
{
	yu_Init();					//用户初始化
	yu_Connect(true);		//数据接收
	yu_IN_OUT(true);		//输入
	yu_Cyc();
	yu_IN_OUT(false);		//输出
	yu_Connect(false);	//数据发送
	return 0;
}

/*PDO
	说明：通讯输入输出
*/
int yu_Connect(BYTE In)
{
	if(In)	//CAN输入
	{
		if(CAN1Rx[0].ErrFlag)
		{
			for(int i=0;i<8;i++)
			CAN1Rx[0].Data[i]=0;
			CAN1Rx[0].GetDataFlag=1;
			LED=RED_THEN_GREEN_FLICKER;
		}
		
		if(CAN1Rx[1].ErrFlag)
		{
			for(int i=0;i<8;i++)
			CAN1Rx[1].Data[i]=0;
			CAN1Rx[1].GetDataFlag=1;
			LED=RED_THEN_GREEN_FLICKER;
		}
		
			if(CAN1Rx[2].ErrFlag)
		{
			for(int i=0;i<8;i++)
			CAN1Rx[2].Data[i]=0;
			CAN1Rx[2].GetDataFlag=1;
			LED=RED_THEN_GREEN_FLICKER;
		}
			if(CAN1Rx[3].ErrFlag)
		{
			for(int i=0;i<8;i++)
			CAN1Rx[3].Data[i]=0;
			CAN1Rx[3].GetDataFlag=1;
			LED=RED_THEN_GREEN_FLICKER;
		}
		
		if(CAN1Rx[0].GetDataFlag)//////////////201
		{
				CAN1Rx[0].GetDataFlag=0;
		///////////////////////////////////////输出状态
				mData.Fb.Val_huandang					=(CAN1Rx[0].Data[0]>>0)&0x0f;		//1
				mData.Fb.Val_dang1						=(CAN1Rx[0].Data[0]>>4)&0x0f;		//2
				mData.Fb.Val_dang2						=(CAN1Rx[0].Data[1]>>0)&0x0f;   //3
				mData.Fb.Val_dang3						=(CAN1Rx[0].Data[1]>>4)&0x0f;   //4
				mData.Fb.Val_dang4						=(CAN1Rx[0].Data[2]>>0)&0x0f;   //5
				mData.Fb.Val_xiehe						=(CAN1Rx[0].Data[2]>>4)&0x0f;   //6
				mData.Fb.Val_zhulihe					=(CAN1Rx[0].Data[3]>>0)&0x0f;   //7
				mData.Fb.Val_shusqi						=(CAN1Rx[0].Data[3]>>4)&0x0f;   //8
				mData.Fb.Val_drive						=(CAN1Rx[0].Data[4]>>0)&0x0f;   //9
				mData.Fb.Val_break						=(CAN1Rx[0].Data[4]>>4)&0x0f;   //10
				mData.Fb.Val_Up_fuzhulun			=(CAN1Rx[0].Data[5]>>0)&0x0f;   //11
				mData.Fb.Val_Dw_fuzhulun			=(CAN1Rx[0].Data[5]>>4)&0x0f;   //12
				mData.Fb.Val_Up_guosui				=(CAN1Rx[0].Data[6]>>0)&0x0f;   //13
				mData.Fb.Val_Dw_guosui				=(CAN1Rx[0].Data[6]>>4)&0x0f;   //14
				mData.Fb.Val_eUp_guosui				=(CAN1Rx[0].Data[7]>>0)&0x0f;   //15
				mData.Fb.Val_eDw_guosui				=(CAN1Rx[0].Data[7]>>4)&0x0f;   //16
			for(int i=0;i<8;i++)
			{
					CAN1Tx[3].Data[i]=CAN1Rx[0].Data[i];
			}
		}
		
		if(CAN1Rx[1].GetDataFlag)////////////////202
		{
				CAN1Rx[1].GetDataFlag=0;
			  ///////////////////////////////////////////////输出状态
				mData.Fb.Val_spare1						=(CAN1Rx[1].Data[0]>>0)&0x0f;   //17
				mData.Fb.Val_spare2						=(CAN1Rx[1].Data[0]>>4)&0x0f;   //18
				mData.Fb.Val_Up_zhaisui				=(CAN1Rx[1].Data[1]>>0)&0x0f;   //19
				mData.Fb.Val_Dw_zhaisui				=(CAN1Rx[1].Data[1]>>4)&0x0f;   //20	
		    ///////////////////////////////////////输入状态

				mData.In.DI_Park					=(~(CAN1Rx[1].Data[2]>>4))&1;		//1
				mData.In.DI_Open_shusqi		=(CAN1Rx[1].Data[2]>>5)&1;		//2
				mData.In.DI_Open_zhulihe	=(CAN1Rx[1].Data[2]>>6)&1;   //3
				mData.In.DI_dang4					=(CAN1Rx[1].Data[2]>>7)&1;   //4
				mData.In.DI_dang3					=(CAN1Rx[1].Data[3]>>0)&1;   //5
				mData.In.DI_dang2					=(CAN1Rx[1].Data[3]>>1)&1;   //6
				mData.In.DI_dang1					=(CAN1Rx[1].Data[3]>>2)&1;   //7
				mData.In.DI_eUp_guosui		=(CAN1Rx[1].Data[3]>>3)&1;   //8
				mData.In.DI_Dw_guosui			=(CAN1Rx[1].Data[3]>>4)&1;   //9
				mData.In.DI_Up_guosui			=(CAN1Rx[1].Data[3]>>5)&1;   //10
				mData.In.DI_Dw_fuzhulun		=(CAN1Rx[1].Data[3]>>6)&1;   //11
				mData.In.DI_Up_fuzhulun		=(CAN1Rx[1].Data[3]>>7)&1;   //12
				mData.In.DI_Clo_shusqi		=(CAN1Rx[1].Data[4]>>0)&1;   //13
				mData.In.DI_break					=(CAN1Rx[1].Data[4]>>1)&1;   //14
				mData.In.DI_eDw_guosui		=(CAN1Rx[1].Data[4]>>2)&1;   //15
				mData.In.DI_Open_fangx		=(CAN1Rx[1].Data[4]>>3)&1;   //16
				mData.In.DI_Up_getai			=(CAN1Rx[1].Data[4]>>4)&1;   //17
				mData.In.DI_Dw_getai			=(CAN1Rx[1].Data[4]>>5)&1;   //18
				mData.In.DI_Clo_fangx			=(CAN1Rx[1].Data[4]>>6)&1;   //19
				mData.In.DI_Clo_zhulihe		=(CAN1Rx[1].Data[4]>>7)&1;   //20	
				mData.In.DI_Up_zhaisui		=(CAN1Rx[1].Data[5]>>0)&1;		//摘穗升
				mData.In.DI_Dw_zhaisui		=(CAN1Rx[1].Data[5]>>1)&1;		//摘穗降
				

				
				mData.In.DI_dang1					=Key_to_shake(mData.In.DI_dang1				,&KeyTime[0]);
				mData.In.DI_dang2					=Key_to_shake(mData.In.DI_dang2				,&KeyTime[1]);
				mData.In.DI_dang3					=Key_to_shake(mData.In.DI_dang3				,&KeyTime[2]);
				mData.In.DI_dang4					=Key_to_shake(mData.In.DI_dang4				,&KeyTime[3]);
				mData.In.DI_Open_zhulihe	=Key_to_shake(mData.In.DI_Open_zhulihe,&KeyTime[4]);
				mData.In.DI_Open_shusqi		=Key_to_shake(mData.In.DI_Open_shusqi	,&KeyTime[5]);
				mData.In.DI_eUp_guosui		=Key_to_shake(mData.In.DI_eUp_guosui	,&KeyTime[6]);
				mData.In.DI_Dw_guosui			=Key_to_shake(mData.In.DI_Dw_guosui		,&KeyTime[7]);
				mData.In.DI_Up_guosui			=Key_to_shake(mData.In.DI_Up_guosui		,&KeyTime[8]);
				mData.In.DI_Dw_fuzhulun		=Key_to_shake(mData.In.DI_Dw_fuzhulun	,&KeyTime[9]);
				mData.In.DI_Up_fuzhulun		=Key_to_shake(mData.In.DI_Up_fuzhulun	,&KeyTime[10]);
				mData.In.DI_Clo_shusqi		=Key_to_shake(mData.In.DI_Clo_shusqi	,&KeyTime[11]);
				mData.In.DI_eDw_guosui		=Key_to_shake(mData.In.DI_eDw_guosui	,&KeyTime[12]);
				mData.In.DI_Open_fangx		=Key_to_shake(mData.In.DI_Open_fangx	,&KeyTime[13]);
				mData.In.DI_Up_getai		  =Key_to_shake(mData.In.DI_Up_getai		,&KeyTime[14]);
				mData.In.DI_Dw_getai			=Key_to_shake(mData.In.DI_Dw_getai		,&KeyTime[15]);
				mData.In.DI_Clo_fangx		=Key_to_shake(mData.In.DI_Clo_fangx			,&KeyTime[16]);
				mData.In.DI_Clo_zhulihe		=Key_to_shake(mData.In.DI_Clo_zhulihe	,&KeyTime[17]);
				
			for(int i=0;i<5;i++)
			{
					CAN1Tx[4].Data[i]=CAN1Rx[1].Data[i];
			}
		}
		
		if(CAN1Rx[2].GetDataFlag)////////301
		{
			CAN1Rx[2].GetDataFlag=0;
			mData.Panel.DI_qiehuan	=(CAN1Rx[2].Data[0]>>6)&1;
			mData.Panel.DI_UPDW			=(CAN1Rx[2].Data[0]>>4)&3;
			mData.Panel.Knob_yijifan=CAN1Rx[2].Data[1]|(CAN1Rx[2].Data[2]<<8);
			mData.Panel.Knob_getai	=CAN1Rx[2].Data[3]|(CAN1Rx[2].Data[4]<<8);
			mData.Panel.Knob_erjifan=CAN1Rx[2].Data[5]|(CAN1Rx[2].Data[6]<<8);
		}
		
		if(CAN1Rx[3].GetDataFlag)////////302
		{
			CAN1Rx[3].GetDataFlag=0;
			mData.Panel.Knob_UD_getai=CAN1Rx[3].Data[0]|CAN1Rx[3].Data[1]<<8;
		}
			
		if(CAN1Rx[4].GetDataFlag)////////601
		{
				CAN1Rx[4].GetDataFlag=0;
			  SDO(CAN1Rx[4].Data,CAN1Tx[2].Data,(UINT16 *)&Par,sizeof(Par)/2);
				CAN1Tx[2].SendFlag=1;
		}
		
				if(CAN1Rx[5].GetDataFlag)////////401
		{
				CAN1Rx[5].GetDataFlag=0;
			  mData.back=CAN1Rx[5].Data[0];
		}
	}		//CAN输出
	else
	{
		CAN1Tx[0].Data[0]=((mData.Out.Val_huandang&1)<<0)|((mData.Out.Val_dang1&1)<<1)|((mData.Out.Val_dang2&1)<<2)|((mData.Out.Val_dang3&1)<<3)
										|((mData.Out.Val_dang4&1)<<4)|((mData.Out.Val_xiehe&1)<<5)|((mData.Out.Val_zhulihe&1)<<6)|((mData.Out.Val_shusqi&1)<<7);
		CAN1Tx[0].Data[1]=((mData.Out.Val_drive&1)<<0)|((mData.Out.Val_break&1)<<1)|((mData.Out.Val_Up_fuzhulun&1)<<2)|((mData.Out.Val_Dw_fuzhulun&1)<<3)
										|((mData.Out.Val_Up_guosui&1)<<4)|((mData.Out.Val_Dw_guosui&1)<<5)|((mData.Out.Val_eUp_guosui&1)<<6)|((mData.Out.Val_eDw_guosui&1)<<7);
		CAN1Tx[0].Data[2]=((mData.Out.Val_spare1&1)<<0)|((mData.Out.Val_spare2&1)<<1)|((mData.Out.Val_Up_zhaisui&1)<<2)|((mData.Out.Val_Dw_zhaisui&1)<<3);

		CAN1Tx[1].Data[0]=mData.Panel.Led_Hig_getai;
		CAN1Tx[1].Data[1]=(mData.Panel.Led_UD&0x07)|(mData.Panel.Led_Alarm&1)<<3;
		/////////////////////档位
		if(mData.In.DI_Park==0)
			CAN1Tx[4].Data[5]=0;
		else
			CAN1Tx[4].Data[5]=mTemp.DangW;
		
			CAN1Tx[4].Data[6]=mData.Panel.DI_qiehuan;
		
		CAN1Tx[5].Data[0]=mData.In.Spd_shengyunqi;
		CAN1Tx[5].Data[1]=mData.In.Spd_shengyunqi>>8;
	  CAN1Tx[5].Data[2]=mData.In.Spd_getai;
		CAN1Tx[5].Data[3]=mData.In.Spd_getai>>8;
		CAN1Tx[5].Data[4]=mData.In.Spd_Drive;
		CAN1Tx[5].Data[5]=mData.In.Spd_Drive>>8;
	  CAN1Tx[5].Data[6]=mData.In.Spd_yijifan;
		CAN1Tx[5].Data[7]=mData.In.Spd_yijifan>>8;
		
		CAN1Tx[6].Data[0]=mData.In.Spd_erjifan;
		CAN1Tx[6].Data[1]=mData.In.Spd_erjifan>>8;
	  CAN1Tx[6].Data[2]=mData.In.Hig_getai;
		CAN1Tx[6].Data[3]=mData.In.Hig_getai>>8;
		CAN1Tx[6].Data[4]=mData.Out.PWM_Up_getai;
		CAN1Tx[6].Data[5]=mData.Out.PWM_Up_getai>>8;
	  CAN1Tx[6].Data[6]=mData.Out.PWM_Dw_getai;
		CAN1Tx[6].Data[7]=mData.Out.PWM_Dw_getai>>8;
		
		CAN1Tx[7].Data[0]=mData.Out.PWM_getai;
		CAN1Tx[7].Data[1]=mData.Out.PWM_getai>>8;
	  CAN1Tx[7].Data[2]=mData.Out.PWM_yijifan;
		CAN1Tx[7].Data[3]=mData.Out.PWM_yijifan>>8;
		CAN1Tx[7].Data[4]=mData.Out.PWM_erjifan;
		CAN1Tx[7].Data[5]=mData.Out.PWM_erjifan>>8;
	  CAN1Tx[7].Data[6]=mTemp.Speed;
		CAN1Tx[7].Data[7]=mTemp.Speed>>8;
		
		CAN1Tx[8].Data[0]=mTemp.Licheng;
		CAN1Tx[8].Data[1]=mTemp.Licheng>>8;
		CAN1Tx[8].Data[2]=mTemp.Licheng>>16;
		CAN1Tx[8].Data[3]=mTemp.Licheng>>24;
		
		
		
		
	}
	return 0;
}



/*IN_OUT
	说明：数据输入输出
*/
int yu_IN_OUT(BYTE In)
{
	if(In)		///////////////输入
	{
		
		mData.In.Hig_getai=AI[2].GetValue;
		
		SnorD.Hig_getai			= SenorIn(mData.In.Hig_getai					,Par.Snr_Start_Step[0][0],Par.Snr_Start_Step[0][1],Par.Snr_Start_Step[0][2]);
		SnorD.pan_UD_getai	= SenorIn(mData.Panel.Knob_UD_getai		,Par.Snr_Start_Step[1][0],Par.Snr_Start_Step[1][1],Par.Snr_Start_Step[1][2]);
		SnorD.pan_getai			= SenorIn(mData.Panel.Knob_getai			,Par.Snr_Start_Step[2][0],Par.Snr_Start_Step[2][1],Par.Snr_Start_Step[2][2]);
		SnorD.pan_yijifan		= SenorIn(mData.Panel.Knob_yijifan		,Par.Snr_Start_Step[3][0],Par.Snr_Start_Step[3][1],Par.Snr_Start_Step[3][2]);
		SnorD.pan_erjifan		= SenorIn(mData.Panel.Knob_erjifan		,Par.Snr_Start_Step[4][0],Par.Snr_Start_Step[4][1],Par.Snr_Start_Step[4][2]);
		mData.In.DI_GetaiB=(AI[0].GetValue>5000);
		
		lvbo();
		mData.In.Spd_shengyunqi			=mTemp.Sped[0];
		mData.In.Spd_getai					=mTemp.Sped[1];
		mData.In.Spd_yijifan				=mTemp.Sped[2];
		mData.In.Spd_erjifan				=mTemp.Sped[4];
		mData.In.Spd_Drive					=mTemp.Sped[3]/3;
		
		mData.In.DI_SW41						=X[5].GetValue;		//
		mData.In.DI_SW42						=X[6].GetValue;		//
		
		
		
	}
	else										///////////////输出
	{
		X[0].SetValue=mData.Out.PWM_Up_getai;
		X[1].SetValue=mData.Out.PWM_Dw_getai;
		X[2].SetValue=mData.Out.PWM_getai;
		X[3].SetValue=mData.Out.PWM_yijifan;
		X[4].SetValue=mData.Out.PWM_erjifan;
		

		///////////////////////////////////档位控制
		// I档 电磁阀1、4		II档 电磁阀2、4		III档 电磁阀1、3		IV档  电磁阀2、3
		mData.Out.Val_huandang	=mData.In.DI_dang1|mData.In.DI_dang2|mData.In.DI_dang3|mData.In.DI_dang4;
		mData.Out.Val_dang1			=mData.In.DI_dang1|mData.In.DI_dang3;
		mData.Out.Val_dang2			=mData.In.DI_dang2|mData.In.DI_dang4;
		mData.Out.Val_dang3			=mData.In.DI_dang3|mData.In.DI_dang4;
		mData.Out.Val_dang4			=mData.In.DI_dang1|mData.In.DI_dang2;
		
		//卸荷阀	割台升降	果穗箱升降	摘穗箱升降	辅助轮升降	果穗箱二次升降
		mData.Out.Val_xiehe=mData.In.DI_Dw_getai|mData.In.DI_Up_getai|mData.In.DI_Up_guosui|mData.In.DI_Dw_guosui
												|mData.In.DI_eUp_guosui|mData.In.DI_eDw_guosui|mData.In.DI_Up_zhaisui|mData.In.DI_Dw_zhaisui
												|mData.In.DI_Up_fuzhulun|mData.In.DI_Dw_fuzhulun|mTemp.GeTaiDw|mTemp.GeTaiUp;
		
	
			if(mData.In.DI_SW42==0)
			{
				mData.Out.PWM_getai				=0;
				mData.Out.Val_Dw_zhaisui	=0;
				mData.Out.Val_Up_zhaisui	=0;
				mData.Out.Val_Dw_fuzhulun	=0;
				mData.Out.Val_Up_fuzhulun	=0;
				mData.Out.Val_shusqi			=0;
				mData.Out.Val_xiehe				=0;
			}
			

	}
	return 0;
}

/*INIT
////////
初始化配置
*/
int yu_Init(void)
{
	static BYTE Booting=true;
	if(Booting)
	{
		Booting=false;
		///////////////参数读取
		App_Epprom_Read(0,(UINT16 *)&Par,sizeof(Par)/2);
		
		if(Par.INIT!=1234)
		{
			Par.INIT=1234;
			Par.DangW=1;
			Par.KeySnak=3;
			Par.Rit_GtDv=75;
			Par.Hig_FX=15000;
			Par.Hig_FxDead=500;
			Par.Snr_Start_Step[0][0]=500;
			Par.Snr_Start_Step[0][1]=45000;
			Par.Snr_Start_Step[0][2]=450;
			
			Par.Snr_Start_Step[1][0]=905;
			Par.Snr_Start_Step[1][1]=110;
			Par.Snr_Start_Step[1][2]=79;
			
			Par.Snr_Start_Step[2][0]=900;
			Par.Snr_Start_Step[2][1]=110;
			Par.Snr_Start_Step[2][2]=78;
			
			Par.Snr_Start_Step[3][0]=720;
			Par.Snr_Start_Step[3][1]=240;
			Par.Snr_Start_Step[3][2]=48;
			
			Par.Snr_Start_Step[4][0]=710;
			Par.Snr_Start_Step[4][1]=255;
			Par.Snr_Start_Step[4][2]=45;
			//一级风机
			Par.Val_MaxMinRes[0][0]	=600;
			Par.Val_MaxMinRes[0][1]	=200;
			Par.Val_MaxMinRes[0][2]	=26;
			//二级风机
			Par.Val_MaxMinRes[1][0]	=600;
			Par.Val_MaxMinRes[1][1]	=200;
			Par.Val_MaxMinRes[1][2]	=26;
			//割台泵
			Par.Val_MaxMinRes[2][0]	=600;
			Par.Val_MaxMinRes[2][1]	=200;
			Par.Val_MaxMinRes[2][2]	=26;
						//割台泵
			Par.Val_MaxMinRes[3][0]	=600;
			Par.Val_MaxMinRes[3][1]	=200;
			Par.Val_MaxMinRes[3][2]	=26;
						//割台泵
			Par.Val_MaxMinRes[4][0]	=600;
			Par.Val_MaxMinRes[4][1]	=200;
			Par.Val_MaxMinRes[4][2]	=26;
			
			Par.Val_AccDcc[0][0]		=100;
			Par.Val_AccDcc[0][1]		=2000;
			
			Par.Val_AccDcc[1][0]		=100;
			Par.Val_AccDcc[1][1]		=2000;
			
			Par.Val_AccDcc[2][0]		=100;
			Par.Val_AccDcc[2][1]		=2000;
		
			Par.Val_AccDcc[3][0]		=15;
			Par.Val_AccDcc[3][1]		=2500;

			Par.Val_AccDcc[4][0]		=15;
			Par.Val_AccDcc[4][1]		=2500;
			
			Par.Val_AccDcc[5][0]		=100;
			Par.Val_AccDcc[5][1]		=10;

	
			Par.LichengL=0;
			Par.LichengH=0;
			Par.Lichengm=0;
			Par.diandsd=30000;
			App_Eeprom_Write(0,(UINT16 *)&Par,sizeof(Par)/2);
		}

		mTemp.DangW	=Par.DangW;
		OldDang			=Par.DangW;
		
		//licheng
		mTemp.Licheng=Par.LichengL|Par.LichengH<<16;
		mTemp.lichengm=Par.Lichengm;
		///////////////////////////按键去抖时间
		for(int i=0;i<20;i++)
		{
			KeyTime[i]=(BYTE)Par.KeySnak;
		}
		//X1-X5PWM输出
		//AI1-AI5初始化
	AI[AI1].TestMode=0;						//测试模式  0电压检测 
	AI[AI2].TestMode=0;						//测试模式  0电压检测 
	AI[AI3].TestMode=0;						//测试模式  0电压检测 1电流检测模式
	AI[AI4].TestMode=0;						//测试模式  0电压检测 1电流检测模式
	AI[AI5].TestMode=0;						//测试模式  0电压检测 
	}
	return 0;
}


unsigned char Key_to_shake(BYTE In,BYTE* Time)
{
	UINT16 Temp=*Time;
	if(In)
	{
		if(Temp>0)
		{
				*Time=Temp-1;
				return 0;
		}
		else
			return 1;
	}
	else
	{
		*Time=(BYTE)Par.KeySnak;
		return 0;
	}
}

int lvbo(void)
{
	static UINT sped[5][wavenub];
	for(int j=0;j<5;j++)
	{
	 for(int i=1;i<wavenub;i++)
	 {
		 sped[j][wavenub-i]=sped[j][wavenub-i-1];
	 }
	 sped[j][0]=X[7+j].GetValue;
	 UINT a=0,b=0,c=0;
	 a=X[7+j].GetValue;
	 for(int n=0;n<wavenub;n++)
	 {
		 if(sped[j][n]<a) a=sped[j][n];
		 if(sped[j][n]>b) b=sped[j][n];
		 c+=sped[j][n];
	 }
	 mTemp.Sped[j]=(c-a-b)/(wavenub-2);
	}
	return 0;
}
