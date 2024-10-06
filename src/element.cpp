#include "element.h"
#include <iostream>

gui::Element::Element()
	:Element("NULL"){

}
gui::Element::Element(const std::string name):
	name(name){
			
}
gui::Element::~Element(){
	for(auto& el : childs){
		delete el;
	}
}

void gui::Element::addChild(Element* const el){
	childs.push_back(el);
}
void gui::Element::addChild(const std::initializer_list<Element*>& els){
	childs.insert(childs.end(), els.begin(), els.end());
}

std::string gui::Element::getName() const{
	return name;
}
const std::vector<gui::Element*>& gui::Element::getChilds() const{
	return childs;
}

void gui::Element::operator()(){
	if(childs.size() == 0)
		std::cout << "operator()" << std::endl;
	else
		std::cout << "monkey" << std::endl;
}
