#include "gui.h"

#include "ter/terminal.h"
#include "ter/keyEvents.h"
#include "ter/tHandler.h"

#include <iostream>
#include <stdexcept>

namespace gui{
	static Element* mainEl = nullptr;
	static Element* currentEl = nullptr;
	static uint64_t indexEl = 0;
	static bool isExit = false;

	static int keyboardCallBack(evn::Key k);
	static void printColoredText(const std::string& text, ter::Color color);
	static void printElements();
	static void addIndexEl(uint64_t num);
	static void executeEl();
}

void gui::init(){
	thd::init();
	ter::init();

	thd::addTermination(std::bind(&ter::setAltMode, false));
	thd::addSuspension(std::bind(&ter::setAltMode, false));
	thd::addRestoration(std::bind(&ter::setAltMode, true));
	ter::setAltMode(true);

	evn::setCallback(keyboardCallBack);
}
void gui::main_loop(){
	if(!mainEl)
		throw std::runtime_error("ERROR: the main element was not initialized");
	else if(mainEl->isEmpty())
		throw std::runtime_error("ERROR: the main element contains nothing");

	printElements();
	while(!isExit){
		if(evn::keyboardEvents()){//if the desired character has been read
			printElements();
		}
	}
}
void gui::terminate(){
	if(mainEl)
		delete mainEl;

	std::cout << "press any key to continue..." << std::endl;
	ter::instantGetChar();
	ter::setAltMode(false);
}
void gui::setMainElement(Element* el){
	mainEl = el;
	currentEl = el;
}

int gui::keyboardCallBack(evn::Key k){
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

		case evn::Key::ENTER:
			executeEl();
		break;

		default: return 0;
	}
	return 1;
}
void gui::printColoredText(const std::string& text, ter::Color color){
	std::cout << color << text << ter::Color::reset << '\n';
}
void gui::printElements(){
	const std::vector<Element*>& childs = currentEl->getChilds();
	uint64_t numberChilds = currentEl->getNumberChilds();

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
void gui::addIndexEl(uint64_t num){
	uint64_t childsSize = currentEl->getNumberChilds();
	indexEl = (indexEl + num + childsSize) % childsSize;
}
void gui::executeEl(){
	Element* selectedEl = &currentEl->getChild(indexEl);

	if(selectedEl->isEmpty()){
		if(selectedEl->exec() == gCode::BACK && currentEl != mainEl){
			currentEl = currentEl->getParent();
		}
	}
	else{
		currentEl = selectedEl;
		indexEl = 0;
		ter::clear();
	}
}
