#include "gui.h"

#include <iostream>
#include "terminal.h"

gui::GUI::GUI():mainElement(new Element()){
	mainElement->addChild({
			new Element(),
			new Element(),
			new Element(),
			new Element(),
			new Element(),
		});
}
gui::GUI::~GUI(){
	delete mainElement;
}

void gui::GUI::main_loop(){
	setNewTerSet();
	int ch = -1;
	while(ch != 4){ //ctrl + d
		ch = getOneChar();
		std::cout << ch << " " << (char)ch << std::endl;
	}

	setOldTerSet();
}
