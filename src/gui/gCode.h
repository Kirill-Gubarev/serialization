#ifndef GCODE_H
#define GCODE_H

#include <cstdint>

namespace gui{
	enum class gCode : int8_t{
		ERROR = -1,
		_0 = 0,
		BACK = 2
	};
}

#endif//GCODE_H
