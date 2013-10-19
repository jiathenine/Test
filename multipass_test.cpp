
#include"Menu.h"

#include<cstdarg>

#include<iostream>


void test(int *a , ...)
{
	va_list va_beg;
	va_start(va_beg,a);
	int *i=  va_arg(va_beg,int*);
	do{
		
		std::cout<< *i <<std::endl;
		i  = va_arg(va_beg,int*);
	}while(i != 0);
	va_end(va_beg);
}
class MultiPass:public Menu{
	 int  simulationMain()const
	 {
		 test(new int(57),new int(34),new int(321),new int(13),new int(42),0);
		 return 0;
	 }
};
MultiPass *obj = new MultiPass;