#include "queue_on_array.h"

#include <iostream>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

QueueOnArray::QueueOnArray()
  : data_(new int32_t[10] {0}), size_(10) {
}



QueueOnArray::QueueOnArray(const QueueOnArray& obj)
  : data_(new int32_t[obj.size_]), size_(obj.size_), i_head_(obj.i_head_),
    i_tail_(obj.i_tail_) {
  for (ptrdiff_t i(0); i < obj.size_; i += 1) {
    data_[i] = obj.data_[i];
  }
}



QueueOnArray::~QueueOnArray() {
  delete[] data_;
}



QueueOnArray& QueueOnArray::operator=(const QueueOnArray& rhs) {
  if (this != &rhs) {
    size_ = rhs.size_;
    delete[] data_;
    data_ = new int32_t[rhs.size_];
    for (ptrdiff_t i(0); i < rhs.size_; i += 1) {
      data_[i] = rhs.data_[i];
    }
    i_head_ = rhs.i_head_;
    i_tail_ = rhs.i_tail_;
  }
  return *this;
}



void QueueOnArray::Push(const int32_t& obj) {
  data_[i_tail_] = obj;
  i_tail_ = (i_tail_ + 1) % size_;
  if (i_tail_ == i_head_) {
    int32_t* copy = data_;
    data_ = new int32_t[size_ * 2];
    for (ptrdiff_t i_data(0), i_copy(i_head_); i_data < size_;
         i_data += 1, i_copy = (i_copy + 1) % size_) {
      data_[i_data] = copy[i_copy];
    }
    delete[] copy;
    i_head_ = 0;
    i_tail_ = size_;
    size_ *= 2;
  }
}



void QueueOnArray::Pop() {
  if (!IsEmpty()) {
    i_head_ = (i_head_ + 1) % size_;
  }
}



int32_t QueueOnArray::Top() const {
  if (!IsEmpty()) {
    return data_[i_head_];
  } else {
    throw std::logic_error("Queue is empty.");
  }
}



bool QueueOnArray::IsEmpty() const {
  return (i_head_ == i_tail_);
}



std::ostream& QueueOnArray::WriteTo(std::ostream& ostrm) const {
  for (ptrdiff_t i_data(i_head_); i_data != i_tail_;
       i_data = (i_data + 1) % size_) {
    ostrm << data_[i_data] << " ";
  }
  return ostrm;
}
