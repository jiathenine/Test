#include"Menu.h"
#include<iostream>
class Test_test :public Menu{
public:
	Test_test(){  }
	int simulationMain()const { std::cout<<"hello world"<<std::endl;return 0;}
};
Test_test * tt = new Test_test;

