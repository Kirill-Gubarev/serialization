#include "gui.h"
#include "tHandler.h"

int main(int argc, char* argv[]){
	thd::init();

	gui::GUI gui;
	gui.main_loop();

    return 0;
}
