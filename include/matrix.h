#ifndef IMAGE_RECOGNITION_MATRIX_H_
#define IMAGE_RECOGNITION_MATRIX_H_

#include <vector>

class Mat {
 private:
  size_t m_ = 0;
  size_t n_ = 0;
  size_t count_ = 0;

  double* arr_ = nullptr;

  void SetDim(size_t m, size_t n);

 public:
  // Constructors
  Mat();
  Mat(size_t m, size_t n);
  Mat(const std::vector<double>& vec, size_t m, size_t n);
  explicit Mat(const std::vector<std::vector<double>>& vec);
  Mat(const Mat& mat);

  // move constructors
  Mat(Mat&& mat);
  Mat& operator =(Mat&& mat);

  // Main operators overloading
  Mat& operator =(const Mat& mat);
  Mat& operator*=(const Mat& mat);
  Mat& operator+=(const Mat& mat);
  Mat& operator-=(const Mat& mat);
  Mat& operator/=(const Mat& mat);

  // Other operator overloading variants
  // +
  friend Mat operator+(const Mat& a, const Mat& b);
  friend Mat operator+=(Mat& mat, double num);
  friend Mat operator+(const Mat& mat, double num);
  friend Mat operator+(double num, const Mat& mat);
  // -
  friend Mat operator-(const Mat& a, const Mat& b);
  friend Mat operator-=(Mat& mat, double num);
  friend Mat operator-(const Mat& mat, double num);
  friend Mat operator-(double num, const Mat& mat);
  // *
  friend Mat operator*(const Mat& a, const Mat& b);
  friend Mat operator*=(Mat& mat, double num);
  friend Mat operator*(const Mat& mat, double num);
  friend Mat operator*(double num, const Mat& mat);
  // /
  friend Mat operator/(const Mat& a, const Mat& b);
  friend Mat operator/=(Mat& mat, double num);
  friend Mat operator/(const Mat& mat, double num);
  friend Mat operator/(double num, const Mat& mat);

  // Other mat functions
  void Print() const;
  void Fill(double num);
  [[nodiscard]] Mat ApplyFunc(double (*func)(double)) const;
  static void Randomize(Mat& mat);

  // Pointers
  [[nodiscard]] double* begin() const;
  [[nodiscard]] double* end()   const;

  // Access functions
  double& at(size_t m_i, size_t n_i);
  [[nodiscard]] double at(size_t m_i, size_t n_i) const;
  [[nodiscard]] size_t m() const;
  [[nodiscard]] size_t n() const;
  [[nodiscard]] size_t count() const;

  // Other functions
  [[nodiscard]] Mat T() const;
  [[nodiscard]] Mat Dot(const Mat& mat) const;

  // Destructor
  ~Mat();
};

#endif  // IMAGE_RECOGNITION_MATRIX_H_
