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
	static size_t indexEl = 0;
	static bool isExit = false;

	static void addIndexEl(size_t num){
		size_t childsSize = currentElement->getChildsSize();
		indexEl = (indexEl + num + childsSize) % childsSize;
	}

	static void printColoredText(const std::string& text, ter::Color color){
		std::cout << color << text << ter::Color::reset << '\n';
	}

	static void printElements(){
		const std::vector<Element*>& childs = currentElement->getChilds();
		size_t numberChilds = currentElement->getChildsSize();

		ter::setCursorPos(0, 0);
		for(size_t i = 0; i < numberChilds; ++i){
			if(i == indexEl){
				printColoredText(childs[i]->getName(), ter::Color::reverse);
			}
			else{
				std::cout << childs[i]->getName() << '\n';
			}
		}
		std::cout << std::endl;
	}

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
				addIndexEl(-1);
			break;

			case evn::Key::s:
			case evn::Key::j:
			case evn::Key::DOWN_ARROW:
				addIndexEl(1);
			break;

			default: return 0;
		}
		return 1;
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

	printElements();
	while(!isExit){
		if(evn::keyboardEvents()){//if the desired character has been read
			printElements();
		}
	}

	std::cout << "press any key to continue..." << std::endl;
	ter::instantGetChar();

	ter::setAltMode(false);
}
