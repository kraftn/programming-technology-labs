#include <stdexcept>

#include "priority_queue_on_list.h"

PriorityQueueOnList::PriorityQueueOnList(const PriorityQueueOnList& obj) {
  if (nullptr != obj.head_) {
    head_ = new Node(nullptr, obj.head_->value, obj.head_->key);
    Node* copied_node(obj.head_->next);
    Node* inserted_node(head_);
    while (nullptr != copied_node) {
      inserted_node->next = new Node(nullptr, copied_node->value,
                                     copied_node->key);
      inserted_node = inserted_node->next;
      copied_node = copied_node->next;
    }
  }
}



PriorityQueueOnList::~PriorityQueueOnList() {
  Clear();
}



PriorityQueueOnList& PriorityQueueOnList::operator=(const PriorityQueueOnList& obj) {
  if (this != &obj) {
    Clear();
    if (nullptr != obj.head_) {
      head_ = new Node(nullptr, obj.head_->value, obj.head_->key);
      Node* copied_node(obj.head_->next);
      Node* inserted_node(head_);
      while (nullptr != copied_node) {
        inserted_node->next = new Node(nullptr, copied_node->value,
                                       copied_node->key);
        inserted_node = inserted_node->next;
        copied_node = copied_node->next;
      }
    }
  }
  return *this;
}



int32_t PriorityQueueOnList::Top() const {
  if (nullptr == head_) {
    throw std::logic_error("Try get top from empty queue.");
  }
  return head_->value;
}



void PriorityQueueOnList::Pop() {
  if (nullptr != head_) {
    Node* node_deleted(head_);
    head_ = head_->next;
    delete node_deleted;
  }
}



void PriorityQueueOnList::Clear() {
  while (!IsEmpty()) {
    Pop();
  }
}



bool PriorityQueueOnList::IsEmpty() const  {
  return nullptr == head_;
}



void PriorityQueueOnList::Push(const int32_t value, const int32_t key) {
  if (nullptr != head_) {
    if (head_->key <= key) {
      Node* take(head_);
      head_ = new Node(take, value, key);
    } else {
      Node* inserted_node(head_);
      while (nullptr != inserted_node->next && inserted_node->next->key > key) {
        inserted_node = inserted_node->next;
      }
      Node* take = inserted_node->next;
      inserted_node->next = new Node(take, value, key);
    }
  } else {
    head_ = new Node(nullptr, value, key);
  }
}



std::ostream& PriorityQueueOnList::WriteTo(std::ostream& ostrm) const {
  Node* printed_node(head_);
  while (nullptr != printed_node) {
    ostrm << '{' << printed_node->value << ", " << printed_node->key << "} ";
    printed_node = printed_node->next;
  }
  return ostrm;
}
