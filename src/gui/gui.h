#ifndef GUI_H
#define GUI_H

#include "element.h"

namespace gui{
	void init();
	void main_loop();
	void terminate();
	void setMainElement(Element* el);
}

#endif//GUI_H
