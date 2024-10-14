#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include <string>

namespace gui{
	class Element{
	private:
		std::string name;
		std::vector<Element*> childs;
		void (*func)();
	public:
		//constructors
		Element();
		Element(const std::string name);
		~Element();

		//adding child elements
		void addChild(Element* const el);
		void addChild(const std::initializer_list<Element*>& els);

		//getters
		std::string getName() const;
		const std::vector<Element*>& getChilds() const;

		Element* operator()(int index);
	};
}

#endif
