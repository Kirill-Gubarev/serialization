#ifndef GUI_H
#define GUI_H

#include "terminal.h"
#include "element.h"
#include <cstdint>

namespace gui{
	class GUI{
	private:
		ter::Terminal terminal;
		Element* mainElement;
		Element* currentElement;
		uint32_t indexEl;
	public:
		GUI();
		~GUI();

		void main_loop();
	private:
		void printElements() const;
	};
}

#endif//GUI_H
