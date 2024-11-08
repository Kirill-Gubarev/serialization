#include "ser.h"

#include <fstream>

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
void ser::write(uint8_t* data, uint64_t size){
	fsm.write(reinterpret_cast<const char*>(data), size);
}

ser::Point::Point(int x, int y) : x(x), y(y){}
void ser::Point::serialize(uint8_t* ptr){
	int* p = reinterpret_cast<int32_t*>(ptr);
	p[0] = x;
	p[1] = y;
}
void ser::Point::deserialize(){

}
