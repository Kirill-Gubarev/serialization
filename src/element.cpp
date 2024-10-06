#include "element.h"
#include <iostream>

gui::Element::Element(){
		
}
gui::Element::~Element(){
	for(auto& el : childs){
		delete el;
	}
}

void gui::Element::addChild(Element* el){
	childs.push_back(el);
}
void gui::Element::addChild(const std::initializer_list<Element*>& els){
	childs.insert(childs.end(), els.begin(), els.end());
}

void gui::Element::operator()(){
	if(childs.size() == 0)
		std::cout << "operator()" << std::endl;
	else
		std::cout << "monkey" << std::endl;
}
