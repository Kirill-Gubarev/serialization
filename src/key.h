#ifndef KEY_H
#define KEY_H

#include <cstdint>

namespace evn{
	enum class Key : uint32_t{
		_			= 0,
		CTRL_C 		= 3,
		CTRL_D		= 4,

		w			= 'w',
		s			= 's',
		d			= 'd',
		a			= 'a',

		k			= 'k',
		j			= 'j',
		l			= 'l',
		h			= 'h',

		UP_ARROW	= 256 + 1,
		DOWN_ARROW	= 256 + 2,
		RIGHT_ARROW = 256 + 3,
		LEFT_ARROW	= 256 + 4
	};
}

#endif//KEY_H
