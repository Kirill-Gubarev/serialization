#ifndef KEYEVENTS_H
#define KEYEVENTS_H

#include "key.h"

namespace evn{
	void setCallback(int(*func)(Key k));
	int keyboardEvents();
}

#endif//KEYEVENTS_H
