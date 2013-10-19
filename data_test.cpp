#include"Menu.h"
#include<iostream>

class data_test:public Menu{
public:
	int simulationMain()const
	{
		
		int *np = new int(10);
		int a = 5;
		int *cp = &a;
		std::cout<<"\tvalue\t"<<"new value\n"
			<<"type\t"<<typeid(*cp).name()<<"\t"<<typeid(*np).name()<<"\n"
			<<"address\t"<<&cp<<"\t"<<&np<<std::endl;
		getchar();
		

		return 0;
	}
};

data_test *test = new data_test;