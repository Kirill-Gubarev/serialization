#include "element.h"

gui::Element::Element():Element("NULL"){}
gui::Element::Element(const std::string name):Element(name, nullptr){}
gui::Element::Element(const std::string name, void (*func)()):
	name(name),	func(func){

}

void gui::Element::setFunction(void (*func)()){
	this->func = func;
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
std::vector<gui::Element>::size_type gui::Element::getChildsSize() const{
	return childs.size();
}
const std::vector<gui::Element*>& gui::Element::getChilds() const{
	return childs;
}
gui::Element& gui::Element::getChild(size_t index) const{
	return *childs[index];
}

void gui::Element::exec() const{
	if(func) func();
}

bool gui::Element::isEmpty(){
	return childs.size() == 0;
}
