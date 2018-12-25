#include "priority_queue_on_array.h"

#include <iostream>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

PriorityQueueOnArray::PriorityQueueOnArray()
  : values_(new int32_t[10] {0}), keys_(new int32_t[10] { 0 }), size_(10) {

}



PriorityQueueOnArray::PriorityQueueOnArray(const PriorityQueueOnArray& obj)
  : values_(new int32_t[obj.size_]), keys_(new int32_t[obj.size_]), size_(obj.size_), i_head_(obj.i_head_),
    i_tail_(obj.i_tail_) {
  for (ptrdiff_t i(0); i < obj.size_; i += 1) {
    values_[i] = obj.values_[i];
    keys_[i] = obj.keys_[i];
  }
}



PriorityQueueOnArray::~PriorityQueueOnArray() {
  delete[] values_;
  delete[] keys_;
}



PriorityQueueOnArray& PriorityQueueOnArray::operator=(const PriorityQueueOnArray& rhs) {
  if (this != &rhs) {
    size_ = rhs.size_;
    delete[] values_;
    delete[] keys_;
    values_ = new int32_t[rhs.size_];
    keys_ = new int32_t[rhs.size_];
    for (ptrdiff_t i(0); i < rhs.size_; i += 1) {
      values_[i] = rhs.values_[i];
      keys_[i] = rhs.keys_[i];
    }
    i_head_ = rhs.i_head_;
    i_tail_ = rhs.i_tail_;
  }
  return *this;
}



void PriorityQueueOnArray::Push(const int32_t& value, const int32_t& key) {
  ptrdiff_t i_insert(i_head_);
  while (i_insert != i_tail_ && key < keys_[i_insert]) {
    i_insert = (i_insert + 1) % size_;
  }

  ptrdiff_t i_replaced(i_tail_);
  ptrdiff_t i_if(i_insert - 1);
  if (i_insert == 0) {
    i_if = size_ - 1;
  }

  while (i_replaced != i_if) {
    values_[(i_replaced + 1) % size_] = values_[i_replaced];
    keys_[(i_replaced + 1) % size_] = keys_[i_replaced];
    if (i_replaced != 0) {
      i_replaced -= 1;
    }
    else {
      i_replaced = size_ - 1;
    }
  }

  values_[i_insert] = value;
  keys_[i_insert] = key;

  i_tail_ = (i_tail_ + 1) % size_;

  if (i_tail_ == i_head_) {
    int32_t* copy_values = values_;
    int32_t* copy_keys = keys_;
    values_ = new int32_t[size_ * 2];
    keys_ = new int32_t[size_ * 2];
    for (ptrdiff_t i_data(0), i_copy(i_head_); i_data < size_;
         i_data += 1, i_copy = (i_copy + 1) % size_) {
      values_[i_data] = copy_values[i_copy];
      keys_[i_data] = copy_keys[i_copy];
    }
    delete[] copy_values;
    delete[] copy_keys;
    i_head_ = 0;
    i_tail_ = size_;
    size_ *= 2;
  }
}



void PriorityQueueOnArray::Pop() {
  if (!IsEmpty()) {
    i_head_ = (i_head_ + 1) % size_;
  }
}



int32_t PriorityQueueOnArray::Top() const {
  if (!IsEmpty()) {
    return values_[i_head_];
  }
  else {
    throw std::logic_error("Queue is empty.");
  }
}



bool PriorityQueueOnArray::IsEmpty() const {
  return (i_head_ == i_tail_);
}



std::ostream& PriorityQueueOnArray::WriteTo(std::ostream& ostrm) const {
  for (ptrdiff_t i_data(i_head_); i_data != i_tail_;
       i_data = (i_data + 1) % size_) {
    ostrm << '{' << values_[i_data] << ", " << keys_[i_data] << "} ";
  }
  return ostrm;
}