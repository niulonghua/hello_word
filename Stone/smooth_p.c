
#include "smooth_p.h"

unsigned short smooth(unsigned short ctrl,unsigned short acc,unsigned short dcc,unsigned short*outTemp )
{
	int a,d,e;
	unsigned short out=*outTemp;
	a=14900/acc;
	d=14900/dcc+1;
	e=(ctrl-out)/2;
	if(out>=0){
		if(e>a)out=out+a; 
		else	if(e<-d) out=out+(e/d-1);
		else out=ctrl;
	}
	*outTemp=out;
	return out;
}


unsigned int smooth1(unsigned int ctrl,unsigned int acc,unsigned int dcc)
{
	int a,d,e;
	static int	out;
	a=16382.0/acc;
	d=16382.0/dcc+1;
	e=((int)ctrl-out)/2;
	if(out>=0){
	if(e>a)out=out+a; else	if(e<-d) out=out+(e/d-1);else out=ctrl;}
	return out;
	
}

unsigned int smooth2(unsigned int ctrl,unsigned int acc,unsigned int dcc)
{
	int a,d,e;
	static int	out;
	a=16382.0/acc;
	d=16382.0/dcc+1;
	e=((int)ctrl-out)/2;
	if(out>=0){
	if(e>a)out=out+a; else	if(e<-d) out=out+(e/d-1);else out=ctrl;}
	return out;
	
}

