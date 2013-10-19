#include"main.h"

//Menu::begin only pointer to someone when you create more than one Menu object 
//so i create a NULL Menu object
Menu *menu = new Menu("NULL");
Menu::const_iterator place(Menu::getBegin());
std::size_t page = 0;
int main()
{
	/*for(int i = 0;i!= 100;++i){
		char val[] = {char('0' +i),NULL};
		new Menu( val );
	}*/
	displayMenu(place.t);
	std::string order;
	while(std::getline(std::cin,order)){
		try{
			disposeOrder(order);
		}catch(const std::runtime_error &e){
			std::cerr<<e.what()<<"(input help to query order:)\n"<<std::endl;
			displayMenu(place.t);
		}
	}
	
	getchar();
	return 0;
}

void displayMenu(Menu const* start)
{
	std::cout<<"/**********************************/\n";
	Menu const* s = start;
	for(std::size_t i = 0;i != maxLine;++i){
		std::cout<<"\t"<<i<<"."<<typeid(*s).name();
		if(s->remarks != "")
			std::cout<<"("<<s->remarks<<")";
		std::cout<<"\n";
		s = s->getNext();
		if(s == Menu::getFreeStore())break;
	}
	//display page number
	std::size_t const maxPage = Menu::getSize()/maxLine + 1;
	for(std::size_t i = 0;i != maxPage;++i){
		if(::page == i)
			std::cout<<"->"<<i;
		else
			std::cout<<" "<<i;
	}
	std::cout<<std::endl;
}

void disposeOrder(std::string const& o)
{
	std::istringstream stream(o);
	std::pair<std::string,std::string> order;
	stream >> order.first;
	stream >> order.second;
	if(order.first == "run"){
		Menu::const_iterator it(place);
		it += std::stoi(order.second,0,10);
		it->simulationMain();
	}else if(order.first == "next"){
		if(Menu::getSize() <= (page + 1) * maxLine )//if haven't more object to page down
			throw std::runtime_error("this is last page");
		place += maxLine;
		page++;
	}else if(order.first == "front"){
		if(page == 0)
			throw std::runtime_error("this is first page");
		page--;
		place = Menu::const_iterator(Menu::getBegin()) + page * maxLine;
	}else if(order.first == "page"){
		if(Menu::getSize() <= std::stoi(order.second) * maxLine)
			throw std::runtime_error("haven't so many page");
		page = std::stoi(order.second);
		place = Menu::const_iterator(Menu::getBegin()) + page * maxLine;
	}else if(order.first == "help"){
		std::cout<<"order:\t\t"<<"function:\n"
			<<"run n\t\t"<<"run the n number function main\n"
			<<"next\t\t"<<"next page\n"
			<<"front\t\t"<<"front page\n"
			<<"page n\t\t"<<"look up the n number page\n"<<std::endl;
	}
	else if(order.first == "\n" || order.first == ""){
		displayMenu(place.t);
	}
	else{
		throw std::runtime_error("please input a right order");
	}
}