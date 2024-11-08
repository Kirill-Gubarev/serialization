#include "app.h"
#include "gui/gui.h"
//#include "ser/ser.h"
#include "gui/guiDefault.h"

namespace app{
	void init();
	void terminate();
	void createGui();
}

void app::exec(){
	init();
	createGui();
	gui::main_loop();
	terminate();
}

void app::init(){
	gui::init();
/*
	ser::init();

	ser::Point p(48, 48);
	ser::ISer* s = &p;

	uint8_t* data = reinterpret_cast<uint8_t*>(malloc(8));
	s->serialize(data);
	ser::write(data, 8);
	*/
}

void app::terminate(){
	gui::terminate();
}

void app::createGui(){
	gui::Element* mainEl = new gui::Element();
	gui::Element* elCE = new gui::Element("i'm containing elements");

	elCE->addChild({
		new gui::Element("back", gui::back),
		new gui::Element("EL2", gui::iam),
		new gui::Element("EL3", gui::iam)
	});

	mainEl->addChild({
		new gui::Element("back", gui::back),
		elCE,
		new gui::Element("element 3", gui::iam),
		new gui::Element("element 4", gui::iam),
		new gui::Element("element 5", gui::iam),
	});

	gui::setMainElement(mainEl);
}
