#pragma once
#ifndef STACK_ON_LIST
#define STACK_ON_LIST

#include <cstddef>
#include <iosfwd>

class StackOnList {
 public:
  StackOnList() = default;
  StackOnList(const StackOnList& obj);
  StackOnList& operator=(const StackOnList& obj);
  ~StackOnList();
  void Push(const int value);
  bool IsEmpty() const noexcept;
  void Pop() noexcept;
  int Top() const;
  void Clear() noexcept;
  std::ostream& WriteTo(std::ostream& ostrm) const;
 private:
  struct Node {
    Node* next{nullptr};
    int   data{0};

    Node(Node* p, const int v)
      : next(p), data(v) {
    }
  };
 private:
  Node* data_{nullptr};
};

inline std::ostream& operator<<(std::ostream& ostrm, const StackOnList& stack) {
  return stack.WriteTo(ostrm);
}

#endif