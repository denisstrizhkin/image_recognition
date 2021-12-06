#ifndef IMAGE_RECOGNITION_MATRIX_H_
#define IMAGE_RECOGNITION_MATRIX_H_

#include <vector>

class Matrix {
 private:
  size_t m_ = 0;
  size_t n_ = 0;
  double* array_ = nullptr;

  class WrongDimensions : public std::exception {
    [[nodiscard]] const char* what() const noexcept override;
  };

  class WrongIndex : public std::exception {
    [[nodiscard]] const char* what() const noexcept override;
  };

 public:
  // Constructors
  Matrix();
  Matrix(size_t m, size_t n);
  Matrix(const std::vector<double>& vector, size_t m, size_t n);
  explicit Matrix(const std::vector<std::vector<double>>& vector);
  Matrix(const Matrix& matrix);

  // Main operators overloading
  Matrix& operator=(const Matrix& matrix);
  Matrix& operator*=(const Matrix& matrix);
  Matrix& operator+=(const Matrix& matrix);
  Matrix& operator-=(const Matrix& matrix);
  Matrix& operator/=(const Matrix& matrix);

  // Access functions
  double& at(size_t i_m, size_t i_n);
  [[nodiscard]] double at(size_t i_m, size_t i_n) const;
  [[nodiscard]] size_t m() const;
  [[nodiscard]] size_t n() const;

  // Other functions
  [[nodiscard]] Matrix T() const;
  [[nodiscard]] Matrix Dot(const Matrix& matrix) const;
  [[nodiscard]] double Sum() const;

  // Destructor
  ~Matrix();
};

// Other operator overloading variants
// +
Matrix operator+(const Matrix& matrix_1, const Matrix& matrix_2);
Matrix operator+=(Matrix& matrix, double num);
Matrix operator+(const Matrix& matrix, double num);
Matrix operator+(double num, const Matrix& matrix);
// -
Matrix operator-(const Matrix& matrix_1, const Matrix& matrix_2);
Matrix operator-=(Matrix& matrix, double num);
Matrix operator-(const Matrix& matrix, double num);
Matrix operator-(double num, const Matrix& matrix);
// *
Matrix operator*(const Matrix& matrix_1, const Matrix& matrix_2);
Matrix operator*=(Matrix& matrix, double num);
Matrix operator*(const Matrix& matrix, double num);
Matrix operator*(double num, const Matrix& matrix);

// /
Matrix operator/(const Matrix& matrix_1, const Matrix& matrix_2);
Matrix operator/=(Matrix& matrix, double num);
Matrix operator/(const Matrix& matrix, double num);
Matrix operator/(double num, const Matrix& matrix);

// Other matrix functions
void PrintMatrix(const Matrix& matrix);
void FillMatrix(Matrix& matrix, double num);
Matrix ApplyFunc(const Matrix& matrix, double (*func)(double));
void RandomizeMatrix(Matrix& matrix);

#endif  // IMAGE_RECOGNITION_MATRIX_H_