#include "Menu.h"
#include <ctime>
#include <iostream>
#include <cassert>


long long powerFunc(long long X ,int N);
CREATE_MAIN(OnePointOne,"test at page 12")
{
	long long count = 30;
	long long compareNum = 100000;
	for(int i = 0; i != count;++i )
	{
		long long n = powerFunc(2,i);
		clock_t time = std::clock();
		long long k = n / 2;
		for(long long j = 0; j != compareNum ; ++j) {//compare is too fast 
			k = n / 2;
		}
		std::cout <<"number is "<<n << "\t"<<"half number is "<<k <<"\t"
			<<"used time "<<std::clock() - time<<std::endl;
	}
	return 0;
}

long long powerFunc(long long X ,int N)
{
	assert( N >= 0 );
	if(N == 0)
		return 1;
	if(N == 1)
		return X;
	if( N % 2 ) { //is even
		return powerFunc(X * X , N/2 ) * X;
	}else {
		return powerFunc(X * X , N/2 );
	}

}
