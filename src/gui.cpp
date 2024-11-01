#include "gui.h"
#include "element.h"
#include "ter/terminal.h"
#include "ter/keyEvents.h"
#include "ter/tHandler.h"

#include <iostream>
#include <memory>

namespace gui{
	static std::unique_ptr<Element> mainEl = nullptr;
	static Element* currentEl = nullptr;
	static size_t indexEl = 0;
	static bool isExit = false;

	static int keyboardCallBack(evn::Key k);
	static void printColoredText(const std::string& text, ter::Color color);
	static void printElements();
	static void addIndexEl(size_t num);
	static void executeEl();
}

void gui::init(){
	thd::init();
	ter::init();

	mainEl.reset(new Element());
	currentEl = mainEl.get();

	Element* elCE = new Element("contains elements");
	elCE->addChild({
			new Element("back", []()->gCode{
					return gCode::BACK;
				}),
			new Element("EL2"),
			new Element("EL3")
		});

	mainEl->addChild({
			new Element(),
			elCE,
			new Element("el3", []()->gCode {
					std::cout<<"i am element 3";
					return gCode::_0;
				}),
			new Element("el4"),
			new Element(),
		});
	mainEl->getChild(3).setFunction([]()->gCode {
			std::cout<<"i am element 4";
			return gCode::_0;
		});

	thd::addTermination(std::bind(&ter::setAltMode, false));
	thd::addSuspension(std::bind(&ter::setAltMode, false));
	thd::addRestoration(std::bind(&ter::setAltMode, true));
	ter::setAltMode(true);

	evn::setCallback(keyboardCallBack);
}
void gui::main_loop(){
	printElements();
	while(!isExit){
		if(evn::keyboardEvents()){//if the desired character has been read
			printElements();
		}
	}
}
void gui::terminate(){
	std::cout << "press any key to continue..." << std::endl;
	ter::instantGetChar();
	ter::setAltMode(false);
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
	size_t numberChilds = currentEl->getChildsSize();

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
void gui::addIndexEl(size_t num){
	size_t childsSize = currentEl->getChildsSize();
	indexEl = (indexEl + num + childsSize) % childsSize;
}
void gui::executeEl(){
	Element* selectedEl = &currentEl->getChild(indexEl);

	if(selectedEl->isEmpty()){
		if(selectedEl->exec() == gCode::BACK){
			currentEl = currentEl->getParent();
		}
	}
	else{
		currentEl = selectedEl;
		indexEl = 0;
		ter::clear();
	}
}
