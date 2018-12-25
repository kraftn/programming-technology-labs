#ifndef QUEUE_ON_ARRAY
#define QUEUE_ON_ARRAY

#include <cstdint>
#include <cstddef>
#include <iostream>

class QueueOnArray {
 public:
  QueueOnArray();
  QueueOnArray(const QueueOnArray& obj);
  ~QueueOnArray();
  QueueOnArray& operator=(const QueueOnArray&);
  void Push(const int32_t& obj);
  void Pop();
  int32_t Top()const;
  bool IsEmpty()const;
  std::ostream& WriteTo(std::ostream& ostrm) const;
 private:
  int32_t* data_{nullptr};
  size_t size_{ 0 };
  ptrdiff_t i_head_{ 0 };
  ptrdiff_t i_tail_{ 0 };
};

inline std::ostream& operator<<(std::ostream& ostrm, const QueueOnArray& rhs) {
  return rhs.WriteTo(ostrm);
}

#endif