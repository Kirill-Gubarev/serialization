#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>

namespace gui{
	class Element{
	private:
		std::vector<Element*> childs;

	public:
		Element();
		~Element();

		void addChild(Element* el);
		void addChild(const std::initializer_list<Element*>& els);

		void operator()();
	
	public:
		static void main_loop();
	};
}

#endif
