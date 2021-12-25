#include "matrix.h"
#include "random.h"

#include <functional>
#include <iomanip>
#include <iostream>
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

float* Mat::begin() const { return &arr_[0]; }
float* Mat::end()   const { return &arr_[count_]; }

void Mat::SetDim(size_t m, size_t n) {
  m_ = m; n_ = n;
  count_ = m_ * n_;
}

Mat::Mat(size_t m, size_t n) {
  SetDim(m, n);
  arr_ = new float[count_];
}

Mat::Mat(const std::vector<float>& vec, size_t m, size_t n)
    : Mat(m, n) {
  if (vec.size() != count_) ThrowDim();
  std::copy(vec.begin(), vec.end(), begin());
}

Mat::Mat(const std::vector<std::vector<float>>& vec)
    : Mat(vec.size(), vec.at(0).size()) {
  for (size_t m_i = 0; m_i < m_; m_i++)
    std::copy(vec[m_i].begin(), vec[m_i].end(), begin() + m_i*n_);
}

Mat::Mat(const Mat& mat) : Mat(mat.m_, mat.n_) {
  std::copy(mat.begin(), mat.end(), this->begin());
}

Mat& Mat::operator=(const Mat& mat) {
  if (this == &mat) return *this;

  delete[] arr_;

  SetDim(mat.m_, mat.n_);
  arr_ = new float[count_];
  std::copy(mat.begin(), mat.end(), this->begin());

  return *this;
}

Mat& Mat::operator+=(const Mat& mat) {
  DimensionsMatch(mat, *this);
  std::transform(begin(), end(), mat.begin(), begin(), std::plus<float>());
  return *this;
}

Mat& Mat::operator*=(const Mat& mat) {
  DimensionsMatch(mat, *this);
  std::transform(begin(), end(), mat.begin(), begin(),
      std::multiplies<float>());
  return *this;
}

Mat& Mat::operator/=(const Mat& mat) {
  DimensionsMatch(mat, *this);
  std::transform(begin(), end(), mat.begin(), begin(), std::divides<float>());
  return *this;
}

Mat& Mat::operator-=(const Mat& mat) {
  DimensionsMatch(mat, *this);
  std::transform(begin(), end(), mat.begin(), begin(), std::minus<float>());
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
  std::fill(begin(), end(), num);
}

void Mat::Print() const {
  std::cout << "--- m(" << m_ << "):n(" << n_ << ")\n";
  for (float* p = begin(); p < end(); p+=n_) {
    std::for_each(p, p+n_, [](float n){ std::cout << std::setw(8) << n; });
    std::cout << '\n';
  }
  std::cout << "---\n";
}

void Mat::Randomize(Mat& mat) {
  Random rnd;
  std::for_each(mat.begin(), mat.end(), [&rnd](float& n){ n = rnd(); });
}

Mat Mat::ApplyFunc(float (*func)(float)) const {
  Mat result(*this);
  std::for_each(result.begin(), result.end(),
      [&func](float& n){ n = func(n); });
  return result;
}

Mat Mat::Dot(const Mat& mat) const {
  if (this->n_ != mat.m_) ThrowDim();

  Mat dot_result(this->m_, mat.n_);
  for (size_t i_new_m = 0; i_new_m < dot_result.m_; i_new_m++) {
    for (size_t i_new_n = 0; i_new_n < dot_result.n_; i_new_n++) {
      size_t i_new = i_new_m * dot_result.n_ + i_new_n;
      dot_result.arr_[i_new] = 0.0;
      for (size_t i_n = 0; i_n < n_; i_n++) {
        dot_result.arr_[i_new] += arr_[i_new_m * n_ + i_n] *
                                    mat.arr_[i_n * mat.n_ + i_new_n];
      }
    }
  }
  return dot_result;
}

Mat Mat::T() const {
  Mat result(n_, m_);
  for (size_t i_m = 0; i_m < m_; i_m++) {
    for (size_t i_n = 0; i_n < n_; i_n++) {
      result.arr_[i_n * m_ + i_m] = arr_[i_m * n_ + i_n];
    }
  }
  return result;
}

Mat operator+(const Mat& a, const Mat& b) {
  DimensionsMatch(a, b);
  Mat r(a);
  std::transform(r.begin(), r.end(), b.begin(), r.begin(), std::plus<float>());
  return r;
}

Mat operator+=(Mat& mat, float num) {
  std::for_each(mat.begin(), mat.end(), [num](float& n){ n+=num; });
  return mat;
}

Mat operator+(const Mat& mat, float num) {
  Mat r(mat.m_, mat.n_);
  std::transform(r.begin(), r.end(), mat.begin(), r.begin(),
      [num](float a, float b){ return num + b; });
  return r;
}

Mat operator+(float num, const Mat& mat) { return operator+(mat, num); }

Mat operator-(const Mat& a, const Mat& b) {
  DimensionsMatch(a, b);
  Mat r(a);
  std::transform(r.begin(), r.end(), b.begin(), r.begin(), std::minus<float>());
  return r;
}

Mat operator-=(Mat& mat, float num)      { return operator+=(mat, -num); }
Mat operator-(const Mat& mat, float num) { return operator+ (mat, -num); }

Mat operator-(float num, const Mat& mat) {
  Mat r(mat.m_, mat.n_);
  std::transform(r.begin(), r.end(), mat.begin(), r.begin(),
      [num](float a, float b){ return num - b; });
  return r;
}

Mat operator*(const Mat& a, const Mat& b) {
  DimensionsMatch(a, b);
  Mat r(a);
  std::transform(r.begin(), r.end(), b.begin(), r.begin(),
      std::multiplies<float>());
  return r;
}

Mat operator*=(Mat& mat, float num) {
  std::for_each(mat.begin(), mat.end(), [num](float& n){ n*=num; });
  return mat;
}

Mat operator*(const Mat& mat, float num) {
  Mat r(mat.m_, mat.n_);
  std::transform(r.begin(), r.end(), mat.begin(), r.begin(),
      [num](float a, float b){ return num * b; });
  return r;
}

Mat operator*(float num, const Mat& mat) { return operator*(mat, num); }

Mat operator/(const Mat& a, const Mat& b) {
  DimensionsMatch(a, b);
  Mat r(a);
  std::transform(r.begin(), r.end(), b.begin(), r.begin(),
      std::divides<float>());
  return r;
}

Mat operator/=(Mat& mat, float num)      { return operator*=(mat, 1/num); }
Mat operator/(const Mat& mat, float num) { return operator* (mat, 1/num); }

Mat operator/(float num, const Mat& mat) {
  Mat r(mat.m_, mat.n_);
  std::transform(r.begin(), r.end(), mat.begin(), r.begin(),
      [num](float a, float b){ return num / b; });
  return r;
}
