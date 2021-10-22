#include "matrix.h"

Matrix::Matrix() {}

Matrix::Matrix(size_t m, size_t n)
{
  m_ = m;
  n_ = n;
  array_ = new double[m_ * n_];
}

Matrix::Matrix(const std::vector<double>& vector, size_t m, size_t n)
{
  
}