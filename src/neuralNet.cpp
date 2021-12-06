#include "neuralNet.h"

#include <cmath>
#include <iomanip>
#include <iostream>

double sigmoid(double n) { return 1 / (1 + std::exp(-n)); }
double sigmoid_d(double n) {
  double sn = sigmoid(n);
  return sn * (1 - sn);
}

double relu(double n) { return std::max(0.0, n); }
double relu_d(double n) { return (n > 0 ? 1 : 0); }

double tanhh(double n) { return std::tanh(n); }
double tanh_d(double n) {
  double tn = std::tanh(n);
  return 1 - tn * tn;
}

double loss_f(double out, double target) {
  double diff = target - out;
  return diff * diff;
}

Matrix loss_f_d(const Matrix& out, const Matrix& target) {
  return (-2) * (target - out);
}

Matrix softmax(const Matrix& matrix) {
  Matrix result = ApplyFunc(matrix, [](double n){return std::exp(n);});
  double sum = result.Sum();

  return result / sum;
}

Neurons forward(const std::vector<Matrix>& w, const std::vector<Matrix>& b,
                const Matrix& x) {
  std::vector<Matrix> z;
  std::vector<Matrix> a;

  std::cout << "w: " << w[0].m() << ", " << w[0].n() << '\n';
  std::cout << "w: " << x.m() << ", " << x.n() << '\n';
  z.push_back(w[0].Dot(x) + b[0]);
  a.push_back(ApplyFunc(z[0], relu));
  std::cout << "after 1st weights\n";

  z.push_back(w[1].Dot(a[0]) + b[1]);
  a.push_back(softmax(z[1]));
  std::cout << "after 2nd weights\n";

  return {z, a};
}

void train(std::vector<Matrix>& w, std::vector<Matrix>& b, double alpha,
           int num_of_iterations, const Matrix& x, const Matrix& y, int step) {
  for (int i = 0; i < num_of_iterations; i++) {
    double loss = 0.0;

    for (int j = 0; j < x.m(); j++) {
      Matrix x_batch(x.n(), 1);
      for (int i_n = 0; i_n < x.n(); i_n++) {
        x_batch.at(i_n, 0) = x.at(j, i_n);
      }
      std::cout << "got x_batch\n";

      Matrix y_batch(y.n(), 1);
      for (int i_n = 0; i_n < y.n(); i_n++) {
        y_batch.at(i_n, 0) = y.at(j, i_n);
      }
      std::cout << "got y_batch\n";

      Neurons neurons = forward(w, b, x_batch);
      std::cout << "forward completed\n";
      std::vector<Matrix> a = neurons.a;
      std::vector<Matrix> z = neurons.z;

      loss += loss_f(a[1].at(0, 0), y_batch.at(0, 0));

      std::vector<Matrix> d_z = {Matrix(0, 0), Matrix(0, 0)};
      d_z[1] = loss_f_d(a[1], y_batch);
      d_z[0] = w[1].T().Dot(d_z[1]) * ApplyFunc(z[0], sigmoid_d);

      w[1] = w[1] - alpha * d_z[1].Dot(a[0].T());
      b[1] = b[1] - alpha * d_z[1].Sum();

      w[0] = w[0] - alpha * d_z[0].Dot(x_batch);
      b[0] = b[0] - alpha * d_z[0].Sum();
    }
    if ((i + 1) % step == 0) {
      std::cout << "iteration #" << std::setw(6) << i + 1 << ": loss: " << std::setw(8)
                << loss / x.m() << '\n';
    }
  }
}

Matrix gen_weights(unsigned n1, unsigned n2) {
  Matrix w(n2, n1);
  RandomizeMatrix(w);

  return w - 0.5;
}

Matrix gen_biases(unsigned n) {
  Matrix b(n, 1);
  RandomizeMatrix(b); 

  return b - 0.5;
}
