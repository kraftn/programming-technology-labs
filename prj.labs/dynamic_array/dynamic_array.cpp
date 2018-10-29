#include <stdexcept>
#include "dynamic_array.h"

DynamicArray::DynamicArray(const int32_t size) {
	if (size <= 0) throw std::invalid_argument("Negative or null size in DynamicArray");
	size_ = size;
	data_ = new int[size_] {0};
}

DynamicArray::DynamicArray(const DynamicArray& obj) {
	if (obj.data_ == nullptr)throw std::invalid_argument("Empty DynamicArray in constructor");
	size_ = obj.size_;
	data_ = new int[size_] {0};
	for (int i = 0; i < size_; i++) {
		data_[i] = obj.data_[i];
	}
}

DynamicArray& DynamicArray::operator=(const DynamicArray& obj) {
	if (data_ == nullptr)throw std::invalid_argument("Left DynamicArray in empty");
	if (obj.data_ == nullptr)throw std::invalid_argument("Right DynamicArray in empty");
	if (size_ != obj.size_)throw std::invalid_argument("Sizes of DynamicArray aren't equal");
	if (this != &obj) {
		for (int i = 0; i < size_; i++) {
			data_[i] = obj.data_[i];
		}
	}
	return *this;
}

DynamicArray::~DynamicArray() {
	delete data_;
	data_ = nullptr;
	size_ = 0;
}

int DynamicArray::Size() const {
	return size_;
}

int& DynamicArray::operator[](const int i) {
	if (i < 0 || i >= size_)throw std::out_of_range("Index is out of range of DynamicArray");
	return data_[i];
}
