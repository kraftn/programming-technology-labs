#include <stdexcept>

#include "matrix.h"

Matrix::Matrix(const int32_t number_rows, const int32_t number_columns)
  : number_rows_(number_rows), number_columns_(number_columns),
    data_(new int32_t* [number_rows]) {
  for (ptrdiff_t i_rows(0); i_rows < number_rows; i_rows += 1) {
    data_[i_rows] = new int32_t[number_columns] { 0 };
  }
}



Matrix::Matrix(const Matrix& obj)
  : number_rows_(obj.number_rows_), number_columns_(obj.number_columns_),
    data_(new int32_t* [obj.number_rows_]) {
  for (ptrdiff_t i_rows(0); i_rows < obj.number_rows_; i_rows += 1) {
    data_[i_rows] = new int32_t[obj.number_columns_] { 0 };
  }

  for (ptrdiff_t i_rows(0); i_rows < obj.number_rows_; i_rows += 1) {
    for (ptrdiff_t i_columns(0); i_columns < obj.number_columns_;
        i_columns += 1) {
      data_[i_rows][i_columns] = obj.data_[i_rows][i_columns];
    }
  }
}



Matrix& Matrix::operator=(const Matrix& obj) {
  if (number_rows_ != obj.number_rows_
      || number_columns_ != obj.number_columns_) {
    throw std::invalid_argument("Sizes of Matrix aren't equal");
  }
  if (this != &obj) {
    for (ptrdiff_t i_rows(0); i_rows < number_rows_; i_rows += 1) {
      for (ptrdiff_t i_columns(0); i_columns < number_columns_;
          i_columns += 1) {
        data_[i_rows][i_columns] = obj.data_[i_rows][i_columns];
      }
    }
  }
  return *this;
}



Matrix::~Matrix() {
  for (ptrdiff_t i_rows(0); i_rows < number_rows_; i_rows += 1) {
    delete[] data_[i_rows];
  }
  delete[] data_;
}



size_t Matrix::GetNumberRows() const {
  return number_rows_;
}



size_t Matrix::GetNumberColumns() const {
  return number_columns_;
}



int32_t& Matrix::Value(const ptrdiff_t row, const ptrdiff_t column) {
  if (row < 0 || row >= number_rows_ || column < 0
      || column >= number_columns_) {
    throw std::out_of_range("Index is out of range of Matrix");
  }
  return data_[row][column];
}



int32_t Matrix::Value(const ptrdiff_t row, const ptrdiff_t column) const {
  if (row < 0 || row >= number_rows_ || column < 0
      || column >= number_columns_) {
    throw std::out_of_range("Index is out of range of Matrix");
  }
  return data_[row][column];
}



Matrix& Matrix::operator+=(const Matrix& rhs) {
  if (number_rows_ != rhs.number_rows_
      || number_columns_ != rhs.number_columns_) {
    throw std::invalid_argument("Sizes of Matrix aren't equal");
  }
  for (ptrdiff_t i_rows(0); i_rows < number_rows_; i_rows += 1) {
    for (ptrdiff_t i_columns(0); i_columns < number_columns_; i_columns += 1) {
      data_[i_rows][i_columns] += rhs.data_[i_rows][i_columns];
    }
  }
  return *this;
}



Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
  Matrix sum(lhs);
  sum += rhs;
  return sum;
}



Matrix& Matrix::operator-=(const Matrix& rhs) {
  if (number_rows_ != rhs.number_rows_
      || number_columns_ != rhs.number_columns_) {
    throw std::invalid_argument("Sizes of Matrix aren't equal");
  }
  for (ptrdiff_t i_rows(0); i_rows < number_rows_; i_rows += 1) {
    for (ptrdiff_t i_columns(0); i_columns < number_columns_; i_columns += 1) {
      data_[i_rows][i_columns] -= rhs.data_[i_rows][i_columns];
    }
  }
  return *this;
}



Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
  Matrix dif(lhs);
  dif -= rhs;
  return dif;
}



Matrix& Matrix::operator*=(const int32_t rhs) {
  for (ptrdiff_t i_rows(0); i_rows < number_rows_; i_rows += 1) {
    for (ptrdiff_t i_columns(0); i_columns < number_columns_; i_columns += 1) {
      data_[i_rows][i_columns] *= rhs;
    }
  }
  return *this;
}



Matrix operator*(const Matrix& lhs, const int32_t rhs) {
  Matrix comp(lhs);
  comp *= rhs;
  return comp;
}



Matrix operator*(const int32_t lhs, const Matrix& rhs) {
  Matrix comp(rhs);
  comp *= lhs;
  return comp;
}



Matrix Matrix::operator*(const Matrix& rhs) {
  if (number_columns_ != rhs.number_rows_) {
    throw std::invalid_argument("The number of columns of the first matrix isn't equal to the number of rows of the second matrix");
  }
  Matrix comp(number_rows_, rhs.number_columns_);
  for (ptrdiff_t i_rows(0); i_rows < number_rows_; i_rows += 1) {
    for (ptrdiff_t i_columns(0); i_columns < rhs.number_columns_;
        i_columns += 1) {
      for (ptrdiff_t i_equal_size(0); i_equal_size < number_columns_;
           i_equal_size += 1) {
        comp.data_[i_rows][i_columns] += data_[i_rows][i_equal_size] *
                                         rhs.data_[i_equal_size][i_columns];
      }
    }
  }
  return comp;
}



std::ostream& Matrix::WriteTo(std::ostream& ostrm) const {
  for (ptrdiff_t i_rows(0); i_rows < number_rows_; i_rows += 1) {
    for (ptrdiff_t i_columns(0); i_columns < number_columns_; i_columns += 1) {
      ostrm << data_[i_rows][i_columns] << ' ';
    }
    ostrm << '\n';
  }
  return ostrm;
}
