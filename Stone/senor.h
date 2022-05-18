#ifndef __senor_H
#define __senor_H

#ifdef __cplusplus
 extern "C" {
#endif
	 						
	
typedef	unsigned int uint;
typedef	unsigned char u8;
unsigned short  PwmOutEx(unsigned short,unsigned short,unsigned short,unsigned short,unsigned short);
unsigned short SenorIn(unsigned short ,unsigned short  ,unsigned short  ,unsigned short  );
int Senor(unsigned short senordata,unsigned char turn);
unsigned short  CntOutEx(unsigned short  Ctrl,unsigned short SMin,unsigned short  SMax,unsigned short OMin,unsigned short OMax);
#ifdef __cplusplus
}
#endif

#endif 

