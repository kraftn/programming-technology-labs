#include <stdexcept>
#include "matrix.h"

Matrix::Matrix(const int32_t size1, const int32_t size2) {
	if (size1 <= 0 || size2<=0) throw std::invalid_argument("Negative or null size in Matrix");
	size1_ = size1;
	size2_ = size2;
	data_ = new int*[size1_];
	for (int i = 0; i < size1_; i++) {
		data_[i] = new int[size2_] {0};
	}
}

Matrix::Matrix(const Matrix& obj) {
	if (obj.data_ == nullptr)throw std::invalid_argument("Empty Matrix in constructor");
	size1_ = obj.size1_;
	size2_ = obj.size2_;
	data_ = new int*[size1_];
	for (int i = 0; i < size1_; i++) {
		data_[i] = new int[size2_] {0};
	}
	for (int i = 0; i < size1_; i++) {
		for (int j = 0; j < size2_; j++) {
			data_[i][j] = obj.data_[i][j];
		}
	}
}

Matrix& Matrix::operator=(const Matrix& obj) {
	if (data_ == nullptr)throw std::invalid_argument("Left Matrix in empty");
	if (obj.data_ == nullptr)throw std::invalid_argument("Right Matrix in empty");
	if (size1_ != obj.size1_ || size2_ != obj.size2_)throw std::invalid_argument("Sizes of Matrix aren't equal");
	if (this != &obj) {
		for (int i = 0; i < size1_; i++) {
			for (int j = 0; j < size2_; j++) {
				data_[i][j] = obj.data_[i][j];
			}
		}
	}
	return *this;
}

Matrix::~Matrix() {
	for (int i = 0; i++; i < size1_) {
		delete[] data_[i];
	}
	delete[] data_;
	data_ = nullptr;
	size1_ = 0;
	size2_ = 0;
}

int Matrix::GetSize1()const {
	return size1_;
}

int Matrix::GetSize2()const {
	return size2_;
}

int& Matrix::Value(const int i, const int j) {
	if (i < 0 || i >= size1_ || j<0 || j>= size2_)throw std::out_of_range("Index is out of range of Matrix");
	return data_[i][j];
}