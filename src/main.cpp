#include "gui.h"
#include <iostream>

int main(int argc, char* argv[]){
	gui::GUI::init();
	gui::GUI::main_loop();

	std::cout << "press enter to continue" << std::endl;
	std::cin.get();
    return 0;
}
