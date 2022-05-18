///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//Filename	:app_tool_function.c
//Project Code	:
//
//Version	:V0.0
//Autor	:niulonghua
//Accomplished Date:20200312
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


#include "app_tool_function.h"

unsigned int Tool_U8_To_U16(unsigned char char_h,unsigned char char_l)
{
	unsigned int temp;
	temp=char_h;
	temp<<=8;
	temp+=char_l;
	return temp;
}

unsigned char Tool_Get_H8Bit_From_U16(unsigned int int_16)
{
	unsigned int temp_int;
	unsigned char temp_char;
	temp_int=int_16;
	temp_char=(unsigned char)(temp_int>>8);
	return temp_char;
}

unsigned char Tool_Get_L8Bit_From_U16(unsigned int int_16)
{
	unsigned int temp_int;
	unsigned char temp_char;
	temp_int=int_16;
	temp_char=(unsigned char)(temp_int);
	return temp_char;
}

void TOOL_Tnsert(unsigned int *a,unsigned int n)
{
	unsigned int i,j,k,temp;
	for(i=0;i<n-1;i++) 
	{
		k=i; 
		for(j=i+1;j<n;j++)
			if(a[k]>a[j ]) 
				k=j; 
		if(i!=k) 
		{ 
			temp=a[i];
			a[i]=a[k];
			a[k]=temp;
		}
	}
}

unsigned int TOOL_Absolute(unsigned int data1,unsigned int data2)
{
	if(data1>data2)
		return data1-data2;
	else
		return data2-data1;
	
}


