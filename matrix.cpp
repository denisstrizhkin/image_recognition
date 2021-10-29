#include "matrix.h"

Matrix::Matrix() {}

Matrix::Matrix(size_t m, size_t n) {
  m_ = m;
  n_ = n;
  array_ = new double[m_ * n_];
}

Matrix::Matrix(const std::vector<double> &vector, size_t m, size_t n)
    : Matrix(m, n) {
  if (vector.size() != m_ * n_) throw WrongDimensions();
  for (size_t i = 0; i < m_ * n_; i++) array_[i] = vector.at(i);
}

Matrix::Matrix(const std::vector<std::vector<double>> &vector)
    : Matrix(vector.size(), vector.at(0).size()) {
  for (size_t i_m = 0; i_m < m_; i_m++)
    for (size_t i_n = 0; i_n < n_; i_n++)
      array_[i_m * n_ + i_n] = vector.at(i_m).at(i_n);
}

Matrix::Matrix(const Matrix &matrix) : Matrix(matrix.m_, matrix.n_) {
  for (size_t i = 0; i < m_ * n_; i++) this->array_[i] = matrix.array_[i];
}