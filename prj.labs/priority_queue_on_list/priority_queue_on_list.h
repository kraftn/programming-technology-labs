#ifndef PRIORITY_QUEUE_ON_LIST
#define PRIORITY_QUEUE_ON_LIST

#include <cstdint>
#include <iostream>

class PriorityQueueOnList {
 public:
  PriorityQueueOnList() = default;
  PriorityQueueOnList(const PriorityQueueOnList& obj);
  PriorityQueueOnList& operator=(const PriorityQueueOnList& obj);
  ~PriorityQueueOnList();
  void Push(const int32_t value, const int32_t key);
  bool IsEmpty() const;
  void Pop();
  int32_t Top() const;
  void Clear();
  std::ostream& WriteTo(std::ostream& ostrm) const;
 private:
  struct Node {
    Node* next{nullptr};
    int32_t value{0};
    int32_t key{0};

    Node(Node* p, const int32_t v, const int32_t k)
      : next(p), value(v), key(k) {
    }
  };
 private:
  Node* head_{nullptr};
};

inline std::ostream& operator<<(std::ostream& ostrm,
                                const PriorityQueueOnList& stack) {
  return stack.WriteTo(ostrm);
}

#endif
