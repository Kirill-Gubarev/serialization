#include "element.h"

gui::Element::Element():Element("NULL"){}
gui::Element::Element(const std::string name):Element(name, nullptr){}
gui::Element::Element(const std::string name, gCode (*func)(const Element* self)):
	name(name),	func(func), parent(nullptr){

}
gui::Element::~Element(){
	for(auto& el : childs){
		if(el)
			delete el;
	}
}

void gui::Element::setParent(Element* el){
	parent = el;
}


void gui::Element::setFunction(gCode (*func)(const Element* self)){
	this->func = func;
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
uint64_t gui::Element::getNumberChilds() const{
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
		return func(this);
	return gCode::ERROR;
}
bool gui::Element::isEmpty() const{
	return childs.size() == 0;
}
