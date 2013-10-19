#include "Menu.h"
#include <vector>
#include <functional>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <ctime>

typedef std::vector<int> IntArray;
typedef std::vector<bool> BooleanArray;

IntArray* randArray_1(int min,int max);
IntArray* randArray_2(int min,int max);
IntArray* randArray_3(int min,int max);
typedef std::function<int(int,int)>fp;

class randBetween {
public:
	int operator()(int min,int max)
	{
		++m_nUseCount;
		return ( rand() % (max - min) ) + min;
	}
	static long long m_nUseCount;
};

long long randBetween::m_nUseCount = 0;
CREATE_MAIN(TwoPointSeven,"")
{
	int const min  = 0;
	int const max = 20000;
	std::srand(284);
	auto printFunc = [](IntArray const* pTestArray ,int const wordCount ) {
		/*int wordNum = 0;
		for(IntArray::const_iterator cit = pTestArray->begin();cit != pTestArray->end();++cit){
			std::cout<<*cit<<",";
			if(++wordNum == wordCount) {
				std::cout<<std::endl;
				wordNum = 0;
			}
		}*/
	};
	//1
	{
		clock_t t = std::clock();

		IntArray *pTestArray = randArray_1(min,max);

		t = std::clock() - t;
		
		printFunc(pTestArray,10);

		std::cout<<"use time =" <<t<<"\tuse rand count ="<<randBetween::m_nUseCount<<std::endl;
	}
	randBetween::m_nUseCount = 0;
	//2
	{

		clock_t t = std::clock();

		IntArray *pTestArray = randArray_2(min,max);

		t = std::clock() - t;
		
		printFunc(pTestArray,10);

		std::cout<<"use time =" <<t<<"\tuse rand count ="<<randBetween::m_nUseCount<<std::endl;
	}
	randBetween::m_nUseCount = 0;
	//3
	{

		clock_t t = std::clock();

		IntArray *pTestArray = randArray_3(min,max);

		t = std::clock() - t;
		
		printFunc(pTestArray,10);

		std::cout<<"use time =" <<t<<"\tuse rand count ="<<randBetween::m_nUseCount<<std::endl;
	}

	return 0;
}




IntArray* randArray_1(int min,int max)
{
	assert(max > min);
	int size = max - min;
	IntArray *pVec = new IntArray;
	IntArray &nVec = *pVec;
	auto randFunc = std::bind(fp(randBetween()),min,max);
	auto func = [&]()->int {
		int n = randFunc();
		while(std::find(nVec.begin(),nVec.end(),n) != nVec.end()){
			n = randFunc();
		}
		return n;
	};
	for(int i = 0; i != size;++i){
		nVec.push_back( func() );
	}
	return pVec;
}

IntArray* randArray_2(int min,int max)
{
	assert(max > min);
	int size = max - min;
	IntArray *pVec = new IntArray;
	IntArray &nVec = *pVec;
	BooleanArray bVec(size);//save 
	auto randFunc = std::bind(randBetween(),min,max);
	auto func = [&]()->int {
		int n = randFunc();
		while( bVec[n - min] ){
			n = randFunc();
		}
		bVec[n - min] = 1;
		return n;
	};
	for(int i = 0; i != max - min;++i){
		nVec.push_back( func() );
	}
	return pVec;
}

IntArray* randArray_3(int min,int max)
{
	assert(max > min);
	int size = max - min;
	IntArray *pVec = new IntArray;
	IntArray &nVec = *pVec;
	for(int i = 0; i != size ; ++i){
		nVec.push_back( i + min );
	}
	for(IntArray::iterator it = nVec.begin();it != nVec.end();++it) {
		int r = randBetween()(0,size);
		std::swap(*it,*(nVec.begin() + r));
	}
	return pVec;
}



