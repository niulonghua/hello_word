///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//Filename	:app_eeprom.c
//Project Code	:
//
//Version	:V0.0
//Autor	:NLH
//Accomplished Date:20200820
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

#include "app_eeprom.h"
#include "ac78Xx_sweeprom.h"


void App_Eeprom_Init(void)
{
	SWEEPROM_Init(512*10, 117);//
}


void App_Eeprom_Write(unsigned short Addr,unsigned short *DataBuffer,unsigned short WriteNum)
{
	SWEEPROM_Write(Addr,DataBuffer,WriteNum);
}

void App_Epprom_Read(unsigned short Addr,unsigned short *DataBuffer,unsigned short ReadNum)
{
	SWEEPROM_Read(Addr,DataBuffer,ReadNum);
}








