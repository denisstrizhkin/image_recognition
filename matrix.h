#ifndef IMAGE_RECOGNITION_MATRIX_H_
#define IMAGE_RECOGNITION_MATRIX_H_

#include <vector>

class Matrix {
private:
  size_t m_ = 0;
  size_t n_ = 0;
  double *array_ = nullptr;

  class WrongDimensions : public std::exception {
    virtual const char *what() const noexcept;
  };

  class WrongIndex : public std::exception {
    virtual const char *what() const noexcept;
  };

public:
  // Constructors
  Matrix();
  Matrix(size_t m, size_t n);
  Matrix(const std::vector<double> &vector, size_t m, size_t n);
  Matrix(const std::vector<std::vector<double>> &vector);
  Matrix(const Matrix &matrix);

  // Destructor
  ~Matrix();

};


#endif //IMAGE_RECOGNITION_MATRIX_H
