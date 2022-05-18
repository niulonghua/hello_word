#include "senor.h"
const int Dead=0;
const	int maxout=65535;	 
const uint SnorStartStep[4]={300,7500,300,8000}; 	 

/*
说明：传感器标定
*/
unsigned short SenorIn(unsigned short In,unsigned short Start ,unsigned short End ,unsigned short Step )
{
	int e=0,temp=0;

	if(Start>End)
	{
			if(In>Start) 	In=Start;
			if(In<End) 		In=End;
			e=Start-End;
			temp=(e+End-In)*3000/(Step+1);
		return temp;
	}
	else if(Start<End)
	{
			if(In<Start) 	In=Start;
			if(In>End) 		In=End;
			e=End-Start;
			temp=(In-Start)*3000/(Step+1);
		return temp;
	}
	else
		return 0;
}

/*
说明：阀输出标定
*/
unsigned short  PwmOutEx(unsigned short  Ctrl,unsigned short MaxC,unsigned short  MinC,unsigned short Res,unsigned short Volt)
{
	unsigned int getMax=Volt/Res;
	unsigned int tmp=Ctrl*(MaxC-MinC);
	if(Ctrl>0)
	tmp=tmp+MinC*1000;
	else
		tmp=0;
	return (unsigned short)(tmp/getMax);
}


int Senor(unsigned short senordata,unsigned char turn)
{
	int e=0,temp=0;
		e=(int)senordata-(int)SnorStartStep[turn*2];
		if(((e>0)&&(e<Dead))||((e<0)&&(-e<Dead)))return 0;
		else 
			{
				if(e>0)e=e-Dead;else e=e+Dead;
				temp=(e<<15)/((int)SnorStartStep[turn*2+1]<<4);
				if(temp>maxout)temp=maxout;else if(temp<-maxout)temp=-maxout;
				if(temp>0)return temp;
				else return 0;				
			}		
}

unsigned short  CntOutEx(unsigned short  Ctrl,unsigned short SMin,unsigned short  SMax,unsigned short OMin,unsigned short OMax)
{
	unsigned short stepin=SMax-SMin;
	unsigned short stepout=OMax-OMin;
	unsigned short Temp=Ctrl*1.0*(stepout)*1.0/stepin*1.0;
	return  Temp+OMin;
}

