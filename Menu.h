#ifndef TEST_MENU_H_
#define TEST_MENU_H_
#include"CachedObj.h"
#include<string>
/**      this class is simulation main                   **/
/**      inherit this class and create a object          **/


class Menu : public CachedObj<Menu>{
public:
	Menu(const char *re=""):remarks(re){ }
	virtual int simulationMain()const { return 0 ;}
	Menu const* operator+(std::size_t sz)const;
	Menu * operator+(std::size_t );
	virtual ~Menu(){  }
	

public:
	std::string remarks;
};

#define CREATE_MAIN(class_name,str) \
	class class_name : public Menu { \
	public:\
		class_name(char const* re):Menu(re){};\
		int simulationMain()const;\
	};\
	class_name *menu = new class_name(str);\
	int class_name::simulationMain()const

#endif