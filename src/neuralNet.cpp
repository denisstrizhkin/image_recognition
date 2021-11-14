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

Neurons forward(const std::vector<Matrix>& w, const std::vector<Matrix>& b,
                const Matrix& x) {
  std::vector<Matrix> z;
  std::vector<Matrix> a;

  z.push_back(w[0].Dot(x) + b[0]);
  a.push_back(ApplyFunc(z[0], sigmoid));

  z.push_back(w[1].Dot(a[0]) + b[1]);
  a.push_back(z[1]);

  return {z, a};
}

void train(std::vector<Matrix>& w, std::vector<Matrix>& b, double alpha,
           int num_of_iterations, const Matrix& x, const Matrix& y, int step) {
  for (int i = 0; i < num_of_iterations; i++) {
    double loss = 0.0;

    for (int j = 0; j < x.m(); j++) {
      Matrix x_batch(1, x.n());
      for (int i_n = 0; i_n < x.n(); i_n++) {
        x_batch.at(0, i_n) = x.at(j, i_n);
      }

      Matrix y_batch(1, y.n());
      for (int i_n = 0; i_n < y.n(); i_n++) {
        y_batch.at(0, i_n) = y.at(j, i_n);
      }

      Neurons neurons = forward(w, b, x_batch);
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
      std::cout << "iteration #" << i + 1 << ": loss: " << std::setw(8)
                << loss / x.m() << '\n';
    }
  }
}

std::vector<Matrix> gen_weights(int n) {
  std::vector<Matrix> w;

  Matrix m_1(n, 1);
  RandomizeMatrix(m_1);
  m_1 -= 0.5;

  w.push_back(m_1);

  Matrix m_2(1, n);
  RandomizeMatrix(m_2);
  m_2 -= 0.5;

  w.push_back(m_2);

  return w;
}

std::vector<Matrix> gen_bias(int n) {
  std::vector<Matrix> b;

  Matrix m_1(n, 1);
  RandomizeMatrix(m_1);
  m_1 -= 0.5;

  b.push_back(m_1);

  Matrix m_2(1, 1);
  RandomizeMatrix(m_2);
  m_2 -= 0.5;

  b.push_back(m_2);

  return b;
}
