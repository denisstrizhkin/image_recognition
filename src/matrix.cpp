#include "matrix.h"

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <algorithm>

void ThrowDim() {
  throw std::invalid_argument("Dimensions do not match!");
}

void DimensionsMatch(const Mat& a, const Mat& b) {
  if (a.m() != b.m() || b.n() != a.n())
    ThrowDim();
}

Mat::Mat() = default;
Mat::~Mat() { delete[] arr_; }
size_t Mat::m() const { return m_; }
size_t Mat::n() const { return n_; }

Mat::Mat(size_t m, size_t n) : m_(m), n_(n) {
  arr_ = new float[m_ * n_];
}

Mat::Mat(const std::vector<float>& vec, size_t m, size_t n)
    : Mat(m, n) {
  if (vec.size() != m_ * n_) ThrowDim();

  std::copy(vec.begin(), vec.end(), arr_);
}

Mat::Mat(const std::vector<std::vector<float>>& vec)
    : Mat(vec.size(), vec.at(0).size()) {
  for (size_t m_i = 0; m_i < m_; m_i++)
    std::copy(vec[m_i].begin(), vec[m_i].end(), arr_ + m_i*n_);
}

Mat::Mat(const Mat& mat) : Mat(mat.m_, mat.n_) {
  std::copy(&mat.arr_[0], &mat.arr_[mat.m_*mat.n_], this->arr_);
}

Mat& Mat::operator=(const Mat& mat) {
  if (this == &mat) return *this;

  delete[] this->arr_;

  this->m_ = mat.m_;
  this->n_ = mat.n_;

  this->arr_ = new float[this->m_ * this->n_];
  std::copy(&mat.arr_[0], &mat.arr_[mat.m_*mat.n_], this->arr_);
 
  return *this;
}

Mat& Mat::operator+=(const Mat& mat) {
  DimensionsMatch(mat, *this); 

  std::transform(&arr_[0], &arr_[m_*n_],
      &mat.arr_[0], &mat.arr_[m_*n_], std::plus<float>());

  return *this;
}

Mat& Mat::operator*=(const Mat& mat) {
  DimensionsMatch(mat, *this); 

  std::transform(&arr_[0], &arr_[m_*n_],
      &mat.arr_[0], &mat.arr_[m_*n_], std::multiplies<float>());

  return *this;
}

Mat& Mat::operator/=(const Mat& mat) {
  DimensionsMatch(mat, *this); 

  std::transform(&arr_[0], &arr_[m_*n_],
      &mat.arr_[0], &mat.arr_[m_*n_], std::divides<float>());

  return *this;
}

Mat& Mat::operator-=(const Mat& mat) {
  DimensionsMatch(mat, *this); 

  std::transform(&arr_[0], &arr_[m_*n_],
      &mat.arr_[0], &mat.arr_[m_*n_], std::minus<float>());

  return *this;
}

float Mat::at(size_t m_i, size_t n_i) const {
  if (m_i >= m_ || n_i >= n_) throw std::out_of_range("Wrong Index!");
  return arr_[m_i * n_ + n_i];
}

float& Mat::at(size_t m_i, size_t n_i) {
  if (m_i >= m_ || n_i >= n_) throw std::out_of_range("Wrong Index!");
  return arr_[m_i * n_ + n_i];
}

void Mat::Fill(float num) {
  std::fill(&arr_[0], &arr_[m_*n_], num);
}

void Mat::Print() {
  std::cout << "--- m(" << m_ << "):n(" << n_ << ")\n";
  for (float* p = &arr_[0]; p < &arr_[m_*n_]; p+=n_) {
    std::for_each(p, p+n_, [](float n){ std::cout << std::setw(8) << n; });
    std::cout << '\n';
  }
  std::cout << "---\n";
}

//void RandomizeMat(Mat& mat) {
//  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//  std::default_random_engine rnd_engine(seed);
//  std::uniform_real_distribution<float> distribution(0.0, 1.0);
//  for (size_t i_m = 0; i_m < mat.m(); i_m++) {
//    for (size_t i_n = 0; i_n < mat.n(); i_n++) {
//      mat.at(i_m, i_n) = distribution(rnd_engine);
//    }
//  }
//}
//
//Mat ApplyFunc(const Mat& mat, float (*func)(float)) {
//  Mat result = mat;
//  for (size_t i_m = 0; i_m < mat.m(); i_m++) {
//    for (size_t i_n = 0; i_n < mat.n(); i_n++) {
//      result.at(i_m, i_n) = func(mat.at(i_m, i_n));
//    }
//  }
//  return result;
//}
//
//Mat Mat::Dot(const Mat& mat) const {
//  if (this->n_ != mat.m_) throw WrongDimensions();
//  Mat dot_result(this->m_, mat.n_);
//  for (size_t i_new_m = 0; i_new_m < dot_result.m_; i_new_m++) {
//    for (size_t i_new_n = 0; i_new_n < dot_result.n_; i_new_n++) {
//      size_t i_new = i_new_m * dot_result.n_ + i_new_n;
//      dot_result.arr_[i_new] = 0.0;
//      for (size_t i_n = 0; i_n < n_; i_n++) {
//        dot_result.arr_[i_new] += arr_[i_new_m * n_ + i_n] *
//                                    mat.arr_[i_n * mat.n_ + i_new_n];
//      }
//    }
//  }
//  return dot_result;
//}
//
//Mat Mat::T() const {
//  Mat result(n_, m_);
//  for (size_t i_m = 0; i_m < m_; i_m++) {
//    for (size_t i_n = 0; i_n < n_; i_n++) {
//      result.arr_[i_n * m_ + i_m] = arr_[i_m * n_ + i_n];
//    }
//  }
//  return result;
//}
//
//float Mat::Sum() const {
//  float sum = 0.0;
//  for (size_t i = 0; i < m_ * n_; i++) sum += arr_[i];
//  return sum;
//}
//
//Mat operator+(const Mat& mat_1, const Mat& mat_2) {
//  Mat tmp_mat_1 = mat_1;
//  return tmp_mat_1 += mat_2;
//}
//
//Mat operator+=(Mat& mat, float num) {
//  Mat num_mat(mat.m(), mat.n());
//  FillMat(num_mat, num);
//  return mat += num_mat;
//}
//
//Mat operator+(const Mat& mat, float num) {
//  Mat num_mat(mat.m(), mat.n());
//  FillMat(num_mat, num);
//  return mat + num_mat;
//}
//
//Mat operator+(float num, const Mat& mat) {
//  return operator+(mat, num);
//}
//
//Mat operator-(const Mat& mat_1, const Mat& mat_2) {
//  Mat tmp_mat_1 = mat_1;
//  return tmp_mat_1 -= mat_2;
//}
//
//Mat operator-=(Mat& mat, float num) {
//  Mat num_mat(mat.m(), mat.n());
//  FillMat(num_mat, num);
//  return mat -= num_mat;
//}
//
//Mat operator-(const Mat& mat, float num) {
//  Mat num_mat(mat.m(), mat.n());
//  FillMat(num_mat, num);
//  return mat - num_mat;
//}
//
//Mat operator-(float num, const Mat& mat) {
//  return operator-(mat, num);
//}
//
//Mat operator*(const Mat& mat_1, const Mat& mat_2) {
//  Mat tmp_mat_1 = mat_1;
//  return tmp_mat_1 *= mat_2;
//}
//
//Mat operator*=(Mat& mat, float num) {
//  Mat num_mat(mat.m(), mat.n());
//  FillMat(num_mat, num);
//  return mat *= num_mat;
//}
//
//Mat operator*(const Mat& mat, float num) {
//  Mat num_mat(mat.m(), mat.n());
//  FillMat(num_mat, num);
//  return mat * num_mat;
//}
//
//Mat operator*(float num, const Mat& mat) {
//  return operator*(mat, num);
//}
//
//Mat operator/(const Mat& mat_1, const Mat& mat_2) {
//  Mat tmp_mat_1 = mat_1;
//  return tmp_mat_1 /= mat_2;
//}
//
//Mat operator/=(Mat& mat, float num) {
//  Mat num_mat(mat.m(), mat.n());
//  FillMat(num_mat, num);
//  return mat /= num_mat;
//}
//
//Mat operator/(const Mat& mat, float num) {
//  Mat num_mat(mat.m(), mat.n());
//  FillMat(num_mat, num);
//  return mat / num_mat;
//}
//
//Mat operator/(float num, const Mat& mat) {
//  return operator/(mat, num);
//}
//
//const char* Mat::WrongDimensions::what() const noexcept {
//  return "Dimensions do not match!";
//}
//const char* Mat::WrongIndex::what() const noexcept { return "Wrong Index!"; }
