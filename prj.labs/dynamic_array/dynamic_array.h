#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cstdint>
#include <cstddef>
#include <iostream>

class DynamicArray {
 public:
  DynamicArray() = default;
  explicit DynamicArray(const int32_t size);
  DynamicArray(const DynamicArray& obj);
  DynamicArray& operator=(const DynamicArray& obj);
  ~DynamicArray();
  size_t Size() const;
  size_t Capacity() const;
  int32_t& operator[](const ptrdiff_t number);
  int32_t operator[](const ptrdiff_t number) const;
  void Resize(int32_t size);
  std::ostream& WriteTo(std::ostream& ostrm) const;

 private:
  size_t logic_size_{ 0 };
  size_t real_size_{ 0 };
  int32_t* data_{ nullptr };
};

inline std::ostream& operator<<(std::ostream& ostrm, DynamicArray& rhs) {
  return rhs.WriteTo(ostrm);
}

#endif
