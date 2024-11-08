#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include <string>
#include "gCode.h"

namespace gui{
	class Element{
	private:
		std::string name;
		std::vector<Element*> childs;
		Element* parent;
		gCode (*func)(const Element* self);

		void setParent(Element* el);
	public:
		//constructors
		Element();
		Element(const std::string name);
		Element(const std::string name, gCode (*func)(const Element* self));
		~Element();

		void setFunction(gCode (*func)(const Element* self));

		//adding child elements
		void addChild(Element* el);
		void addChild(const std::initializer_list<Element*>& els);

		//getters
		std::string getName() const;
		uint64_t getNumberChilds() const;
		Element* getParent() const;

		//getting child elements
		const std::vector<Element*>& getChilds() const;
		Element& getChild(size_t index) const;

		gCode exec() const;
		bool isEmpty() const;
	};
}

#endif
