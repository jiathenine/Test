#include"Menu.h"

Menu const* Menu::operator+(std::size_t sz)const
{
		Menu const* mu = this;
		for(std::size_t i = 0;i != sz ; ++i)
			mu = mu->getNext();
		return mu;
}
Menu* Menu::operator+(std::size_t sz)
{
	Menu * mu = this;
		for(std::size_t i = 0;i != sz ; ++i)
			mu = mu->getNext();
		return mu;
}