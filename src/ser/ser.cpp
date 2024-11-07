#include "ser.h"

#include <fstream>
#include <cstdint>
#include <ios>

typedef uint8_t byte;

namespace ser{
	static std::fstream fsm;
}

void ser::init(){
	fsm.open("data.bin",
			std::ios::trunc |
			std::ios::binary |
			std::ios::in |
			std::ios::out
	);
}

template<typename T>
void ser::write(const T* data, size_t size){

}
