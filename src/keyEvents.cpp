#include "keyEvents.h"
#include "terminal.h"

namespace evn{
	static int(*callbackFunc)(Key) = nullptr;
	static bool isPrevEsc = false;

	static Key handleEscKey(int ch){
#if defined (__linux__)
		if(ch != '[')
			return static_cast<Key>(ch);
#endif

		ch = ter::instantGetChar();
		switch(ch){
#if defined (__linux__)
			case 'A': return Key::UP_ARROW;
			case 'B': return Key::DOWN_ARROW;
			case 'C': return Key::RIGHT_ARROW;
			case 'D': return Key::LEFT_ARROW;
#elif defined (_WIN32)
			case 'H': return Key::UP_ARROW;
			case 'P': return Key::DOWN_ARROW;
			case 'M': return Key::RIGHT_ARROW;
			case 'K': return Key::LEFT_ARROW;
#endif

			default: return Key::_;
		}
	}

	static Key handleKey(int ch){
#if defined (_WIN32)
		if(ch == 224)
			return handleEscKey(ch);
#elif defined (__linux__)
		if(isPrevEsc){
			isPrevEsc = false;
			return handleEscKey(ch);
		}
		if(ch == 27){ //esc secuence
			isPrevEsc = true;
			return Key::_;
		}
#endif

		return static_cast<Key>(ch);
	}
}

void evn::setCallback(int(*func)(Key k)){
	callbackFunc = func;
}
int evn::keyboardEvents(){
	Key k = handleKey(ter::instantGetChar());
	return callbackFunc(k);
}
