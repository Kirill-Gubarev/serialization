#ifndef TERMINAL_H
#define TERMINAL_H

#include "color.h"
#include <iostream>

namespace ter{
	void init();
	void setAltMode(bool enable);

	//setting the terminal color
	std::ostream& operator<<(std::ostream& os, const Color color);
	void setColor(Color color);

	void setCursorPos(int x, int y);
	//get a character without pressing the enter key.
	int instantGetChar();
}

#endif//TERMINAL_H
