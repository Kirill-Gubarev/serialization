#ifndef TERMINAL_H
#define TERMINAL_H

#include "color.h"

namespace ter{
	void init();
	void setAltMode(bool enable);
	void setColor(Color color);
	//get a character without pressing the enter key.
	int instantGetChar();
}

#endif//TERMINAL_H
