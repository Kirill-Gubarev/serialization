#include "gui.h"

#include <iostream>
#include "terminal.h"
#include <vector>

gui::GUI::GUI():
	mainElement(new Element()),
	currentElement(mainElement),
	indexEl(0){

	mainElement->addChild({
			new Element("el1"),
			new Element("el2"),
			new Element("el3"),
			new Element("el4"),
			new Element("el5"),
		});
}
gui::GUI::~GUI(){
	delete mainElement;
}

void gui::GUI::main_loop(){
	ter::setAltTerminal(true);
	ter::setColor(ter::Color::bred);
	std::cout << "monkey";
	ter::setColor(ter::Color::reset);
	std::cout << '\n';
	ter::setColor(ter::Color::fred);
	std::cout << "monkey";
	ter::setColor(ter::Color::reset);
	std::cout << '\n';
	ter::setColor(ter::Color::bblue);
	std::cout << "monkey";
	ter::setColor(ter::Color::reset);
	std::cout << '\n';
	ter::setColor(ter::Color::fblue);
	std::cout << "monkey";
	ter::setColor(ter::Color::reset);
	std::cout << '\n';
	ter::setColor(ter::Color::bgreen);
	std::cout << "monkey";
	ter::setColor(ter::Color::reset);
	std::cout << '\n';
	ter::setColor(ter::Color::fgreen);
	std::cout << "monkey";
	ter::setColor(ter::Color::reset);
	std::cout << '\n';

	int ch = 0;
	while((ch = ter::instantGetChar()) != 4){ //ctrl + d
		if(ch == 'w')
			indexEl--;
		else if(ch == 's')
			indexEl++;

		//std::cout << ch << " " << (char) ch << '\n';
		printElements();
	}

	ter::setAltTerminal(false);
}
void gui::GUI::printElements() const{
	const std::vector<Element*>& childs = currentElement->getChilds();
	size_t numberChilds = childs.size();

	for(size_t i = 0; i < numberChilds; ++i){
		if(i == indexEl)
			ter::setColor(ter::Color::reverse);
		std::cout << childs[i]->getName();
		if(i == indexEl)
			ter::setColor(ter::Color::reset);
		std::cout << '\n';
	}
	std::cout << std::endl;
}
