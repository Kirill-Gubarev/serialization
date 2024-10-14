#include "gui.h"
#include "element.h"
#include "terminal.h"
#include "keyEvents.h"
#include "tHandler.h"

#include <iostream>
#include <memory>

namespace gui{
	static std::unique_ptr<Element> mainElement = nullptr;
	static Element* currentElement = nullptr;
	static uint32_t indexEl = 0;
	static bool isExit = false;

	static int keyboardCallBack(evn::Key k){
		switch(k){
			case evn::Key::CTRL_C:
				std::cout << "\nctrl + c pressed" << std::endl;
				isExit = true;
			return 0;

			case evn::Key::CTRL_D:
				std::cout << "\nctrl + d pressed" << std::endl;
				isExit = true;
			return 0;

			case evn::Key::w:
			case evn::Key::k:
			case evn::Key::UP_ARROW:
				indexEl--;
			break;

			case evn::Key::s:
			case evn::Key::j:
			case evn::Key::DOWN_ARROW:
				indexEl++;
			break;

			default: return 0;
		}
		return 1;
	}

	static void printElements(){
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
}
void gui::init(){
	thd::init();
	ter::init();

	mainElement.reset(new Element());
	currentElement = mainElement.get();

	mainElement->addChild({
			new Element("el1"),
			new Element("el2"),
			new Element("el3"),
			new Element("el4"),
			new Element("el5"),
		});
}

void gui::main_loop(){
	thd::addTermination(std::bind(&ter::setAltMode, false));
	thd::addSuspension(std::bind(&ter::setAltMode, false));
	thd::addRestoration(std::bind(&ter::setAltMode, true));
	ter::setAltMode(true);

	evn::setCallback(keyboardCallBack);

	while(!isExit){
		if(evn::keyboardEvents())//if the desired character has been read
			printElements();
	}

	std::cout << "press any key to continue..." << std::endl;
	ter::instantGetChar();

	ter::setAltMode(false);
}
