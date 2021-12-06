#ifndef NEURAL_NET
#define NEURAL_NET

#include <vector>

#include "matrix.h"

// Matrix* Dot(Matrix* M);
// Matrix* Apply_f(double (*func)(double));
// void Ones();
// void rnd();

struct Neurons {
  std::vector<Matrix> z;
  std::vector<Matrix> a;
};

double sigmoid(double n);
double sigmoid_d(double n);

double relu(double n);
double relu_d(double n);

double tanhh(double n);
double tanh_d(double n);

[[nodiscard]] Matrix softmax(const Matrix& matrix);

double loss_f(double out, double target);
Matrix loss_f_d(const Matrix& out, const Matrix& target);

Neurons forward(const std::vector<Matrix>& w, const std::vector<Matrix>& b,
                const Matrix& x);
void train(std::vector<Matrix>& w, std::vector<Matrix>& b, double alpha,
           int iter, const Matrix& x, const Matrix& y, int step);

[[nodiscard]] Matrix gen_weights(unsigned n_1, unsigned n_2);
[[nodiscard]] Matrix gen_biases(unsigned n);

#endif
