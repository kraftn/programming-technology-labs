#ifndef PRIORITY_QUEUE_ON_ARRAY
#define PRIORITY_QUEUE_ON_ARRAY

#include <cstdint>
#include <cstddef>
#include <iostream>

class PriorityQueueOnArray {
 public:
  PriorityQueueOnArray();
  PriorityQueueOnArray(const PriorityQueueOnArray& obj);
  ~PriorityQueueOnArray();
  PriorityQueueOnArray& operator=(const PriorityQueueOnArray&);
  void Push(const int32_t& value, const int32_t& key);
  void Pop();
  int32_t Top()const;
  bool IsEmpty()const;
  std::ostream& WriteTo(std::ostream& ostrm) const;
 private:
  int32_t* values_{ nullptr };
  int32_t* keys_{ nullptr };
  size_t size_{ 0 };
  ptrdiff_t i_head_{ 0 };
  ptrdiff_t i_tail_{ 0 };
};

inline std::ostream& operator<<(std::ostream& ostrm, const PriorityQueueOnArray& rhs) {
  return rhs.WriteTo(ostrm);
}

#endif