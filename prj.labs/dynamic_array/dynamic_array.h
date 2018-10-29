#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cstdint>

class DynamicArray {
public:
	DynamicArray(){}
	explicit DynamicArray(const int32_t size);
	explicit DynamicArray(const DynamicArray& obj);
	DynamicArray& operator=(const DynamicArray& obj);
	~DynamicArray();
	int Size() const;
	int& operator[] (const int i);

private:
	int32_t* data_{ nullptr };
	int32_t size_{ 0 };
};

#endif