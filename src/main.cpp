#include "gui/gui.h"

int main(int argc, char* argv[]){
	gui::init();
	gui::main_loop();
	gui::terminate();
    return 0;
}
