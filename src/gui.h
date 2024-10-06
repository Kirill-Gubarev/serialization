#ifndef GUI_H
#define GUI_H

#include "element.h"

namespace gui{
	class GUI{
	private:
		static Element mainElement;	
	public:
		GUI() = delete;
		GUI(GUI&) = delete;
		void operator=(GUI&) = delete;

		static void init();
		static void main_loop();
	};
}

#endif//GUI_H
