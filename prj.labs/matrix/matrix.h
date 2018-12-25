#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint>

class Matrix {
 public:
  Matrix() {}
  Matrix(const int32_t size1, const int32_t size2);
  explicit Matrix(const Matrix& obj);
  Matrix& operator=(const Matrix& obj);
  ~Matrix();
  int GetSize1() const;
  int GetSize2() const;
  int& Value(const int i, const int j);

 private:
  int32_t** data_{ nullptr };
  int32_t size1_{ 0 };
  int32_t size2_{ 0 };
};

#endif