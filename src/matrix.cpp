#include "matrix.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

Matrix::Matrix() = default;
Matrix::~Matrix() { delete[] array_; }
size_t Matrix::m() const { return m_; }
size_t Matrix::n() const { return n_; }

Matrix::Matrix(size_t m, size_t n) {
  m_ = m;
  n_ = n;
  array_ = new double[m_ * n_];
}

Matrix::Matrix(const std::vector<double>& vector, size_t m, size_t n)
    : Matrix(m, n) {
  if (vector.size() != m_ * n_) throw WrongDimensions();
  for (size_t i = 0; i < m_ * n_; i++) array_[i] = vector.at(i);
}

Matrix::Matrix(const std::vector<std::vector<double>>& vector)
    : Matrix(vector.size(), vector.at(0).size()) {
  for (size_t i_m = 0; i_m < m_; i_m++) {
    for (size_t i_n = 0; i_n < n_; i_n++) {
      array_[i_m * n_ + i_n] = vector.at(i_m).at(i_n);
    }
  }
}

Matrix::Matrix(const Matrix& matrix) : Matrix(matrix.m_, matrix.n_) {
  for (size_t i = 0; i < m_ * n_; i++) this->array_[i] = matrix.array_[i];
}

Matrix& Matrix::operator=(const Matrix& matrix) {
  if (this == &matrix) return *this;
  delete[] this->array_;
  this->m_ = matrix.m_;
  this->n_ = matrix.n_;
  this->array_ = new double[this->m_ * this->n_];
  for (size_t i = 0; i < m_ * n_; i++) this->array_[i] = matrix.array_[i];
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& matrix) {
  if (this->m_ != matrix.m_ || this->n_ != matrix.n_) throw WrongDimensions();
  for (size_t i = 0; i < this->m_ * this->n_; i++) {
    this->array_[i] += matrix.array_[i];
  }
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& matrix) {
  if (this->m_ != matrix.m_ || this->n_ != matrix.n_) throw WrongDimensions();
  for (size_t i = 0; i < this->m_ * this->n_; i++) {
    this->array_[i] *= matrix.array_[i];
  }
  return *this;
}

Matrix& Matrix::operator/=(const Matrix& matrix) {
  if (this->m_ != matrix.m_ || this->n_ != matrix.n_) throw WrongDimensions();
  for (size_t i = 0; i < this->m_ * this->n_; i++) {
    this->array_[i] /= matrix.array_[i];
  }
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& matrix) {
  if (this->m_ != matrix.m_ || this->n_ != matrix.n_) throw WrongDimensions();
  for (size_t i = 0; i < this->m_ * this->n_; i++) {
    this->array_[i] -= matrix.array_[i];
  }
  return *this;
}

double Matrix::at(size_t i_m, size_t i_n) const {
  if (i_m >= m_ || i_n >= n_) throw WrongIndex();
  return array_[i_m * n_ + i_n];
}

double& Matrix::at(size_t i_m, size_t i_n) {
  if (i_m >= m_ || i_n >= n_) throw WrongIndex();
  return array_[i_m * n_ + i_n];
}

void FillMatrix(Matrix& matrix, double num) {
  for (size_t i_m = 0; i_m < matrix.m(); i_m++) {
    for (size_t i_n = 0; i_n < matrix.n(); i_n++) matrix.at(i_m, i_n) = num;
  }
}

void PrintMatrix(const Matrix& matrix) {
  std::cout << "--- m(" << matrix.m() << "):n(" << matrix.n() << ")\n";
  for (size_t i_m = 0; i_m < matrix.m(); i_m++) {
    for (size_t i_n = 0; i_n < matrix.n(); i_n++) {
      std::cout << std::setw(8) << matrix.at(i_m, i_n);
    }
    std::cout << '\n';
  }
  std::cout << "---\n";
}

void RandomizeMatrix(Matrix& matrix) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine rnd_engine(seed);
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  for (size_t i_m = 0; i_m < matrix.m(); i_m++) {
    for (size_t i_n = 0; i_n < matrix.n(); i_n++) {
      matrix.at(i_m, i_n) = distribution(rnd_engine);
    }
  }
}

Matrix Matrix::Dot(const Matrix& matrix) const {
  if (this->n_ != matrix.m_) throw WrongDimensions();
  Matrix dot_result(this->m_, matrix.n_);
  for (size_t i_new_m = 0; i_new_m < dot_result.m_; i_new_m++) {
    for (size_t i_new_n = 0; i_new_n < dot_result.n_; i_new_n++) {
      size_t i_new = i_new_m * dot_result.n_ + i_new_n;
      dot_result.array_[i_new] = 0.0;
      for (size_t i_n = 0; i_n < n_; i_n++) {
        dot_result.array_[i_new] += array_[i_new_m * n_ + i_n] *
                                    matrix.array_[i_n * matrix.n_ + i_new_n];
      }
    }
  }
  return dot_result;
}

Matrix Matrix::T() const {
  Matrix result(n_, m_);
  for (size_t i_m = 0; i_m < m_; i_m++) {
    for (size_t i_n = 0; i_n < n_; i_n++) {
      result.array_[i_n * m_ + i_m] = array_[i_m * n_ + i_n];
    }
  }
  return result;
}

double Matrix::Sum() const {
  double sum = 0.0;
  for (size_t i = 0; i < m_ * n_; i++) sum += array_[i];
  return sum;
}

Matrix operator+(const Matrix& matrix_1, const Matrix& matrix_2) {
  Matrix tmp_matrix_1 = matrix_1;
  return tmp_matrix_1 += matrix_2;
}

Matrix operator+(const Matrix& matrix, double num) {
  Matrix num_matrix(matrix.m(), matrix.n());
  FillMatrix(num_matrix, num);
  return matrix + num_matrix;
}

Matrix operator+(double num, const Matrix& matrix) {
  return operator+(matrix, num);
}

Matrix operator-(const Matrix& matrix_1, const Matrix& matrix_2) {
  Matrix tmp_matrix_1 = matrix_1;
  return tmp_matrix_1 -= matrix_2;
}

Matrix operator-(const Matrix& matrix, double num) {
  Matrix num_matrix(matrix.m(), matrix.n());
  FillMatrix(num_matrix, num);
  return matrix - num_matrix;
}

Matrix operator-(double num, const Matrix& matrix) {
  return operator-(matrix, num);
}

Matrix operator*(const Matrix& matrix_1, const Matrix& matrix_2) {
  Matrix tmp_matrix_1 = matrix_1;
  return tmp_matrix_1 *= matrix_2;
}

Matrix operator*(const Matrix& matrix, double num) {
  Matrix num_matrix(matrix.m(), matrix.n());
  FillMatrix(num_matrix, num);
  return matrix * num_matrix;
}

Matrix operator*(double num, const Matrix& matrix) {
  return operator*(matrix, num);
}

Matrix operator/(const Matrix& matrix_1, const Matrix& matrix_2) {
  Matrix tmp_matrix_1 = matrix_1;
  return tmp_matrix_1 /= matrix_2;
}

Matrix operator/(const Matrix& matrix, double num) {
  Matrix num_matrix(matrix.m(), matrix.n());
  FillMatrix(num_matrix, num);
  return matrix / num_matrix;
}

Matrix operator/(double num, const Matrix& matrix) {
  return operator/(matrix, num);
}

const char* Matrix::WrongDimensions::what() const noexcept {
  return "Dimensions do not match!";
}
const char* Matrix::WrongIndex::what() const noexcept { return "Wrong Index!"; }
