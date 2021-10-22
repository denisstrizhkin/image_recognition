#ifndef IMAGE_RECOGNITION_MATRIX_H_
#define IMAGE_RECOGNITION_MATRIX_H_

#include <vector>

class Matrix {
private:
  size_t m_ = 0;
  size_t n_ = 0;
  double* array_ = nullptr;

public:
  // Constructors
  Matrix();
  Matrix(size_t m, size_t n);
  Matrix(const std::vector<double>& vector, size_t m, size_t n);
  Matrix(const Matrix& matrix);

  // Destructor
  ~Matrix();

};



#endif //IMAGE_RECOGNITION_MATRIX_H
