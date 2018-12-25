#include <stdexcept>
#include <iostream>

#include "stack_on_list.h"

StackOnList::StackOnList(const StackOnList& obj) {
  if (nullptr != obj.data_) {
    data_ = new Node(nullptr, obj.data_->data);
    Node* copied_node(obj.data_->next);
    Node* inserted_node(data_);
    while (nullptr != copied_node) {
      inserted_node->next = new Node(nullptr, copied_node->data);
      inserted_node = inserted_node->next;
      copied_node = copied_node->next;
    }
  }
}



StackOnList::~StackOnList() {
  Clear();
}



StackOnList& StackOnList::operator=(const StackOnList& obj) {
  if (this != &obj) {
    if (nullptr != obj.data_) {
      if (nullptr != data_) {
        Node* copied_node(obj.data_);
        Node* inserted_node(data_);
        while (nullptr != inserted_node->next && nullptr != copied_node->next) {
          inserted_node->data = copied_node->data;
          inserted_node = inserted_node->next;
          copied_node = copied_node->next;
        }
        if (nullptr != copied_node->next) {
          inserted_node->data = copied_node->data;
          copied_node = copied_node->next;
          while (nullptr != copied_node) {
            inserted_node->next = new Node(nullptr, copied_node->data);
            inserted_node = inserted_node->next;
            copied_node = copied_node->next;
          }
        } else {
          inserted_node->data = copied_node->data;
          Node* deleted_node(inserted_node->next);
          inserted_node->next = nullptr;
          while (nullptr != deleted_node) {
            Node* node_delete(deleted_node);
            deleted_node = deleted_node->next;
            delete node_delete;
          }
        }
      } else {
        data_ = new Node(nullptr, obj.data_->data);
        Node* copied_node(obj.data_->next);
        Node* inserted_node(data_);
        while (nullptr != copied_node) {
          inserted_node->next = new Node(nullptr, copied_node->data);
          inserted_node = inserted_node->next;
          copied_node = copied_node->next;
        }
      }
    } else {
      data_ = nullptr;
    }
  }
  return *this;
}



int StackOnList::Top() const {
  if (nullptr == data_) {
    throw std::logic_error("Try get top from empty stack.");
  }
  return data_->data;
}



void StackOnList::Pop() noexcept {
  if (nullptr != data_) {
    Node* node_deleted(data_);
    data_ = data_->next;
    delete node_deleted;
  }
}



void StackOnList::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}



bool StackOnList::IsEmpty() const noexcept {
  return nullptr == data_;
}



void StackOnList::Push(const int value) {
  data_ = new Node(data_, value);
}



std::ostream& StackOnList::WriteTo(std::ostream& ostrm) const {
  Node* printed_node(data_);
  ostrm << '{';
  while (printed_node) {
    ostrm << printed_node->data;
    printed_node = printed_node->next;
    if (printed_node) {
      ostrm << ", ";
    }
  }
  ostrm << '}';
  return ostrm;
}
