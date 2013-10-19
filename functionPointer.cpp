
#include"Menu.h"
#include<iostream>


int test(int ia,char ca)
{
	std::cout<<ia<<"\t"<<ca<<std::endl;
	return 0;
}
typedef int (*ptf)(int ,char);
#define Test_ptf(_val) (ptf)(&_val)


CREATE_MAIN(FunctionPointer,"ff")
{
	Test_ptf(test);
	getchar();
	return 0;
}

//class FunctionPointer:public Menu{
//public:
//	int simulationMain()const
//	{
//		Test_ptf(test);
//		
//		getchar();
//		return 0;
//	}
//};
//FunctionPointer *menu = new FunctionPointer;