#ifndef SER_H
#define SER_H

#include <cstddef>

namespace ser{
	void init();

	template<typename T>
	void write(const T* data, size_t size);
}

#endif//SER_H
