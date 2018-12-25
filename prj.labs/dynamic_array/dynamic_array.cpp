#include <stdexcept>

#include "dynamic_array.h"

DynamicArray::DynamicArray(const int32_t size)
  : logic_size_(size), real_size_(2 * logic_size_),
    data_(new int32_t[real_size_] {0}) {
}



DynamicArray::DynamicArray(const DynamicArray& obj)
  : logic_size_(obj.logic_size_), real_size_(2 * logic_size_),
    data_(new int32_t[real_size_] {0}) {
  for (ptrdiff_t i_data(0); i_data < obj.logic_size_; i_data += 1) {
    data_[i_data] = obj.data_[i_data];
  }
}



DynamicArray& DynamicArray::operator=(const DynamicArray& obj) {
  if (this != &obj) {
    Resize(obj.logic_size_);
    for (ptrdiff_t i_data(0); i_data < obj.logic_size_; i_data++) {
      data_[i_data] = obj.data_[i_data];
    }
  }
  return *this;
}



DynamicArray::~DynamicArray() {
  delete[] data_;
}



size_t DynamicArray::Capacity() const {
  return real_size_;
}



size_t DynamicArray::Size() const {
  return logic_size_;
}



int32_t& DynamicArray::operator[](const ptrdiff_t number) {
  if (number < 0 || number >= logic_size_) {
    throw std::out_of_range("Index is out of range of DynamicArray.");
  }
  return data_[number];
}



int32_t DynamicArray::operator[](const ptrdiff_t number) const {
  if (number < 0 || number >= logic_size_) {
    throw std::out_of_range("Index is out of range of DynamicArray.");
  }
  return data_[number];
}



void DynamicArray::Resize(int32_t size) {
  if (size < 0) {
    throw std::length_error("Invalid size of DynamicArray.");
  } else {
    if (size <= real_size_) {
      for (ptrdiff_t i_data(logic_size_); i_data < (size - 1); i_data += 1) {
        data_[i_data] = 0;
      }
      logic_size_ = size;
    } else {
      int32_t* data_old = data_;
      data_ = new int32_t[2 * size] { 0 };
      for (ptrdiff_t i_data(0); i_data < logic_size_; i_data += 1) {
        data_[i_data] = data_old[i_data];
      }
      logic_size_ = size;
      real_size_ = 2 * logic_size_;
      delete[] data_old;
    }
  }
}



std::ostream& DynamicArray::WriteTo(std::ostream& ostrm) const {
  ostrm << "{ ";
  for (ptrdiff_t i_data(0); i_data < logic_size_; i_data += 1) {
    ostrm << data_[i_data] << ' ';
  }
  ostrm << '}';
  return ostrm;
}
