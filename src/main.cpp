#include "element.h"
#include <iostream>

int main(int argc, char* argv[]){
	gui::Element el;
	el();
	
	gui::Element el2;
	el2.addChild(new gui::Element());
	el2();

	gui::Element el3;
	el3.addChild({new gui::Element(), new gui::Element(), new gui::Element()});
	el3();

	std::cout << "press enter to continue" << std::endl;
	std::cin.get();
    return 0;
}
