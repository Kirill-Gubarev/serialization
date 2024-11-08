#ifndef SER_H
#define SER_H

#include <cstdint>

namespace ser{
	void init();
	void write(uint8_t* data, uint64_t size);
	class ISerializable{
		public:
			virtual void serialize(uint8_t* ptr) = 0;
			virtual void deserialize() = 0;
	};
	typedef ISerializable ISer;

	//test data
	class Point : public ISerializable{
		private:
			int x, y;
		public:
			Point(int x, int y);
			void serialize(uint8_t* ptr) override;
			void deserialize() override;
	};
}

#endif//SER_H
