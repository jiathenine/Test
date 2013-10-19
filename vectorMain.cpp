
#include"Menu.h"
#include"Vector.h"
#include<vector>
#include<iostream>

CREATE_MAIN(vectorTest,"this is my vector")
{
	Vector<int>ivec;
	for(int i = 0; i != 20 ; ++i){
		ivec.push_back(i);
	}
	ivec.resize(100,-20);
	for(int i =0; i != 100;++i){
		std::cout<<ivec[i]<<"\t";
		if(i%10 == 0)
			std::cout<<std::endl;
	}
	std::cout<<std::endl;
	std::cout<<ivec.size()<<std::endl;
	std::cout<<ivec.capacity()<<std::endl;
	ivec.reserve(300);
	std::cout<<ivec.capacity()<<std::endl;
	getchar();
	return 0;
}