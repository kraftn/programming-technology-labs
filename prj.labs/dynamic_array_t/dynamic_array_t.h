#ifndef DYNAMIC_ARRAY_T_H
#define DYNAMIC_ARRAY_T_H

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
class DynamicArrayT {
 public:
  DynamicArrayT() = default;
  explicit DynamicArrayT(const int32_t size);
  DynamicArrayT(const DynamicArrayT<T>& obj);
  DynamicArrayT<T>& operator=(const DynamicArrayT<T>& obj);
  ~DynamicArrayT();
  size_t Size() const;
  size_t Capacity() const;
  T& operator[](const ptrdiff_t number);
  T operator[](const ptrdiff_t number) const;
  void Resize(int32_t size);
  std::ostream& WriteTo(std::ostream& ostrm) const;

 private:
  size_t logic_size_{ 0 };
  size_t real_size_{ 0 };
  T* data_{ nullptr };
};



template <typename T>
DynamicArrayT<T>::DynamicArrayT(const int32_t size)
  : logic_size_(size), real_size_(2 * logic_size_), data_(new T[real_size_]{ 0 }) {

}



template <typename T>
DynamicArrayT<T>::DynamicArrayT(const DynamicArrayT<T>& obj)
  : logic_size_(obj.logic_size_), real_size_(2 * logic_size_), data_(new T[real_size_]{ 0 }) {
  for (ptrdiff_t i_data(0); i_data < obj.logic_size_; i_data += 1) {
    data_[i_data] = obj.data_[i_data];
  }
}



template<typename T>
DynamicArrayT<T>& DynamicArrayT<T>::operator=(const DynamicArrayT<T>& obj) {
  if (this != &obj) {
    Resize(obj.logic_size_);
    for (ptrdiff_t i_data(0); i_data < obj.logic_size_; i_data++) {
      data_[i_data] = obj.data_[i_data];
    }
  }
  return *this;
}


template<typename T>
DynamicArrayT<T>::~DynamicArrayT() {
  delete[] data_;
}



template<typename T>
size_t DynamicArrayT<T>::Capacity() const {
  return real_size_;
}


template<typename T>
size_t DynamicArrayT<T>::Size() const {
  return logic_size_;
}



template<typename T>
T& DynamicArrayT<T>::operator[](const ptrdiff_t number) {
  if (number < 0 || number >= logic_size_) {
    throw std::out_of_range("Index is out of range of DynamicArray.");
  }
  return data_[number];
}


template<typename T>
T DynamicArrayT<T>::operator[](const ptrdiff_t number) const {
  if (number < 0 || number >= logic_size_) {
    throw std::out_of_range("Index is out of range of DynamicArray.");
  }
  return data_[number];
}



template<typename T>
void DynamicArrayT<T>::Resize(int32_t size) {
  if (size < 0) {
    throw std::length_error("Invalid size of DynamicArray.");
  }
  else {
    if (size <= real_size_) {
      for (ptrdiff_t i_data(logic_size_); i_data < (size - 1); i_data += 1) {
        data_[i_data] = 0;
      }
      logic_size_ = size;
    }
    else {
      T* data_old = data_;
      data_ = new T[2 * size]{ 0 };
      for (ptrdiff_t i_data(0); i_data < logic_size_; i_data += 1) {
        data_[i_data] = data_old[i_data];
      }
      logic_size_ = size;
      real_size_ = 2 * logic_size_;
      delete[] data_old;
    }
  }
}



template<typename T>
std::ostream& DynamicArrayT<T>::WriteTo(std::ostream& ostrm) const {
  ostrm << "{ ";
  for (ptrdiff_t i_data(0); i_data < logic_size_; i_data += 1) {
    ostrm << data_[i_data] << ' ';
  }
  ostrm << '}';
  return ostrm;
}



template <typename T>
inline std::ostream& operator<<(std::ostream& ostrm, DynamicArrayT<T>& rhs) {
  return rhs.WriteTo(ostrm);
}

#endif