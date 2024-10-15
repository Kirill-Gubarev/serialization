#include "element.h"

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
std::vector<gui::Element>::size_type gui::Element::getChildsSize() const{
	return childs.size();
}
const std::vector<gui::Element*>& gui::Element::getChilds() const{
	return childs;
}
gui::Element& gui::Element::getChild(size_t index) const{
	return *childs[index];
}

gui::Element* gui::Element::operator()(int index){
	if(childs.size() == 0){
		func();
		return this;
	}
	return childs[index];
}
