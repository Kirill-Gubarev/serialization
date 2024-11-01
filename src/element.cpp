#include "element.h"

gui::Element::Element():Element("NULL"){}
gui::Element::Element(const std::string name):Element(name, nullptr){}
gui::Element::Element(const std::string name, gCode (*func)()):
	name(name),	func(func), parent(nullptr){

}

void gui::Element::setFunction(gCode (*func)()){
	this->func = func;
}

gui::Element::~Element(){
	for(auto& el : childs){
		delete el;
	}
}

void gui::Element::setParent(Element* el){
	parent = el;
}
void gui::Element::addChild(Element* el){
	el->setParent(this);
	childs.push_back(el);
}
void gui::Element::addChild(const std::initializer_list<Element*>& els){
	for(auto& el : els)
		el->setParent(this);
	childs.insert(childs.end(), els.begin(), els.end());
}

std::string gui::Element::getName() const{
	return name;
}
std::vector<gui::Element>::size_type gui::Element::getChildsSize() const{
	return childs.size();
}
gui::Element* gui::Element::getParent() const{
	return parent;
}

const std::vector<gui::Element*>& gui::Element::getChilds() const{
	return childs;
}
gui::Element& gui::Element::getChild(size_t index) const{
	return *childs[index];
}

gui::gCode gui::Element::exec() const{
	if(func)
		return func();
	return gCode::ERROR;
}

bool gui::Element::isEmpty(){
	return childs.size() == 0;
}
