#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cstdint>

class DynamicArray {
public:
	DynamicArray(){}
	explicit DynamicArray(const int32_t size);
	DynamicArray(const DynamicArray& obj);
	DynamicArray& operator=(const DynamicArray& obj);
	~DynamicArray();
	int Size() const;
	int& operator[] (const int number);
	int operator[] (const int number) const;
	void Resize();

private:
	int32_t* data_{ nullptr };
	int32_t size_{ 0 };
};

#endif