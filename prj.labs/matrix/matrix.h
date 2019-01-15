#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint>
#include <cstddef>
#include <iostream>

class Matrix {
 public:
  Matrix() {}
  Matrix(const int32_t number_rows, const int32_t number_columns);
  Matrix(const Matrix& obj);
  Matrix& operator=(const Matrix& obj);
  ~Matrix();
  size_t GetNumberRows() const;
  size_t GetNumberColumns() const;
  int32_t& Value(const ptrdiff_t row, const ptrdiff_t column);
  const int32_t& Value(const ptrdiff_t row, const ptrdiff_t column) const;
  Matrix& operator+=(const Matrix& rhs);
  Matrix& operator-=(const Matrix& rhs);
  Matrix& operator*=(const int32_t rhs);
  Matrix operator*(const Matrix& rhs);
  std::ostream& WriteTo(std::ostream& ostrm) const;

 private:
  int32_t number_rows_{ 0 };
  int32_t number_columns_{ 0 };
  int32_t** data_{ nullptr };
};

Matrix operator+(const Matrix& lhs, const Matrix& rhs);
Matrix operator-(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const Matrix& lhs, const int32_t rhs);
Matrix operator*(const int32_t lhs, const Matrix& rhs);
inline std::ostream& operator<<(std::ostream& ostrm, const Matrix& rhs) {
  return rhs.WriteTo(ostrm);
}

#endif
