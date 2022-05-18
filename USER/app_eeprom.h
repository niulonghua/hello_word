///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//Filename	:app_eeprom.h
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

#ifndef APP_EEPROM_H
#define APP_EEPROM_H

void App_Eeprom_Init(void);
void App_Eeprom_Write(unsigned short Addr,unsigned short *DataBuffer,unsigned short WriteNum);
void App_Epprom_Read(unsigned short Addr,unsigned short *DataBuffer,unsigned short ReadNum);

#endif

