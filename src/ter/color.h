#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

namespace ter{
	enum class Color : uint8_t{
		reset	= 0,
		reverse = 7,
		fred	= 31,
		fgreen	= 32,
		fyellow	= 33,
		fblue	= 34,
		fpurple	= 35,
		fcyan	= 36,
		fwhite	= 37,
		bred	= 41,
		bgreen	= 42,
		byellow	= 43,
		bblue	= 44,
		bpurple	= 45,
		bcyan	= 46,
		bwhite	= 47
	};
}

#endif//COLOR_H
