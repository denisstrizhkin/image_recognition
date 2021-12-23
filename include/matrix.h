#ifndef IMAGE_RECOGNITION_MATRIX_H_
#define IMAGE_RECOGNITION_MATRIX_H_

#include <vector>

class Mat {
 private:
  size_t m_ = 0;
  size_t n_ = 0;
  size_t count_ = 0;

  float* arr_ = nullptr;

  [[nodiscard]] float* begin() const;
  [[nodiscard]] float* end()   const;

  void SetDim(size_t m, size_t n);

 public:
  // Constructors
  Mat();
  Mat(size_t m, size_t n);
  Mat(const std::vector<float>& vec, size_t m, size_t n);
  explicit Mat(const std::vector<std::vector<float>>& vec);
  Mat(const Mat& mat);

  // Main operators overloading
  Mat& operator =(const Mat& mat);
  Mat& operator*=(const Mat& mat);
  Mat& operator+=(const Mat& mat);
  Mat& operator-=(const Mat& mat);
  Mat& operator/=(const Mat& mat);

  // Other operator overloading variants
  // +
  friend Mat operator+(const Mat& a, const Mat& b);
  friend Mat operator+=(Mat& mat, float num);
  friend Mat operator+(const Mat& mat, float num);
  friend Mat operator+(float num, const Mat& mat);
  // -
  friend Mat operator-(const Mat& a, const Mat& b);
  friend Mat operator-=(Mat& mat, float num);
  friend Mat operator-(const Mat& mat, float num);
  friend Mat operator-(float num, const Mat& mat);
  // *
  friend Mat operator*(const Mat& a, const Mat& b);
  friend Mat operator*=(Mat& mat, float num);
  friend Mat operator*(const Mat& mat, float num);
  friend Mat operator*(float num, const Mat& mat);
  // /
  friend Mat operator/(const Mat& a, const Mat& b);
  friend Mat operator/=(Mat& mat, float num);
  friend Mat operator/(const Mat& mat, float num);
  friend Mat operator/(float num, const Mat& mat);

  // Other mat functions
  void Print();
  void Fill(float num);
  [[nodiscard]] Mat ApplyFunc(float (*func)(float));
  static void Randomize(Mat& mat);

  // Access functions
  float& at(size_t m_i, size_t n_i);
  [[nodiscard]] float at(size_t m_i, size_t n_i) const;
  [[nodiscard]] size_t m() const;
  [[nodiscard]] size_t n() const;

  // Other functions
  [[nodiscard]] Mat T() const;
  [[nodiscard]] Mat Dot(const Mat& mat) const;

  // Destructor
  ~Mat();
};

#endif  // IMAGE_RECOGNITION_MATRIX_H_
