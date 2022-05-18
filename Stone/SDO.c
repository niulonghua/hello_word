#include "SDO.h"
int SDO(unsigned char Data[8],unsigned char *tD,unsigned  short *par,int len)
{
	unsigned short 	adr_Index=0;
	unsigned char 	madr_Index=0;
	unsigned  short *p1;
	if((Data[0]==0x40)||(Data[0]==0x2B))
	{
		adr_Index=Data[1]|(Data[2]<<8);
		madr_Index=Data[3];
			switch (adr_Index) 
				{
				case 0x2000:	p1=par;
				case 0x2001: 	p1=par+256*2;
				case 0x2002: 	p1=par;		//ÊäÈë
				case 0x2003: 	p1=par;		//Êä³ö
			}
			p1=p1+madr_Index;
			tD[1]=Data[1];  tD[2]=Data[2];  tD[3]=Data[3];
			
			if(Data[0]==0x40)
			{
				tD[0]=0x4B; tD[4]=*p1;  tD[5]=(*p1)>>8;
			}
			else
			{
				tD[0]=0x60;	tD[4]=0;  tD[5]=0;
				*p1=Data[4]|Data[5]<<8;
				App_Eeprom_Write(madr_Index,p1,1);
				
			}
		
	}
	return 1;
}


