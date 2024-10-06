#include "gui.h"
#include <iostream>

gui::Element gui::GUI::mainElement("main element");

void gui::GUI::init(){
	mainElement.addChild({
			new Element(),
			new Element(),
			new Element(),
			new Element(),
			new Element(),
		});
}
void gui::GUI::main_loop(){
	for(auto& el : mainElement.getChilds())
		std::cout << el->getName() << '\n';
	std::cout << std::endl;
}
