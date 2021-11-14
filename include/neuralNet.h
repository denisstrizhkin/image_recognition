#ifndef NEURAL_NET
#define NEURAL_NET

#include <iostream>
#include <vector>

class Matrix {
private:
  size_t m_;
  size_t n_;
  double *array_;

  class DimensionsException : public std::exception {
    [[nodiscard]] auto what() const noexcept -> const char * override;
  };

  class WrongIndexException : public std::exception {
    [[nodiscard]] auto what() const noexcept -> const char * override;
  };

public:
  // Constructors
  Matrix(size_t _m, size_t _n);
  Matrix(const std::vector<double> &in_vector, size_t _m, size_t _n);
  Matrix();
  Matrix(const Matrix &in_matrix);

  // Destructor
  ~Matrix();

  // Operator overloading
  // =
  auto operator=(const Matrix &in_matrix) -> Matrix &;
  // +
  auto operator+(const Matrix &in_matrix) -> Matrix;
  friend auto operator+(double in_num, const Matrix &in_matrix) -> Matrix;
  friend auto operator+(const Matrix &in_matrix, double in_num) -> Matrix;
  // -
  auto operator-(const Matrix &in_matrix) -> Matrix;
  friend auto operator-(double in_num, const Matrix &in_matrix) -> Matrix;
  friend auto operator-(const Matrix &in_matrix, double in_num) -> Matrix;
  // *
  auto operator*(const Matrix &in_matrix) -> Matrix;
  friend auto operator*(double in_num, const Matrix &in_matrix) -> Matrix;
  friend auto operator*(const Matrix &in_matrix, double in_num) -> Matrix;
  // /
  auto operator/(const Matrix &in_matrix) -> Matrix;
  friend auto operator/(double in_num, const Matrix &in_matrix) -> Matrix;
  friend auto operator/(const Matrix &in_matrix, double in_num) -> Matrix;

  // Functions
  auto At(size_t i_m, size_t i_n) -> double &;
  auto N() -> size_t;
  auto M() -> size_t;
  void Print();
  auto Sum() -> double;
  auto T() -> Matrix;
  auto Dot(const Matrix &in_matrix) -> Matrix;
};

// Matrix* Dot(Matrix* M);
// Matrix* Apply_f(float (*func)(float));
// void Ones();
// void rnd();

auto sigmoid(float n) -> float;
auto sigmoid_d(float n) -> float;
auto relu(float n) -> float;
auto relu_d(float n) -> float;
auto tanhh(float n) -> float;
auto tanh_d(float n) -> float;

auto loss_f(float out, float target) -> float;
auto loss_f_d(Matrix *out, Matrix *target) -> Matrix *;
void forward(Matrix **w, Matrix **b, Matrix *x, Matrix **z, Matrix **a);
void train(Matrix **w, Matrix **b, float alpha, int iter, Matrix *x, Matrix *y,
           int step);
void gen_weights(Matrix **w, int n);
void gen_bias(Matrix **b, int n);

#endif
