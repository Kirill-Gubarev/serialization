#include "guiDefault.h"
#include <iostream>

gui::gCode gui::nothing(const Element* self){
	return gCode::_0;
}
gui::gCode gui::back(const Element* self){
	return gCode::BACK;
}
gui::gCode gui::iam(const Element* self){
	std::cout << "i am " << self->getName();
	return gCode::_0;
}
