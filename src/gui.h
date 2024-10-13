#ifndef GUI_H
#define GUI_H

#include "element.h"
#include <stdint.h>

namespace gui{
	class GUI{
	private:
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
