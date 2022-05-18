#ifndef __SDO_H
#define __SDO_H
#include "user.h"

#ifdef __cplusplus
 extern "C" {
#endif
	
	int SDO(unsigned char Data[8],unsigned char *tD,unsigned  short *par,int len);

	 
#ifdef __cplusplus
}
#endif

#endif 
