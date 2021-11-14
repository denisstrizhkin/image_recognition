#include <cmath>
#include <iostream>

#include "matrix.h"
#include "neuralNet.h"

double func(double num) { return std::cos(num); }

int main() {
  int n = 10;

  std::vector<Matrix> w = gen_weights(n);
  std::vector<Matrix> b = gen_bias(n);

  double alpha = 0.01;
  int iter = 1000;
  int step = 100;

  std::vector<double> x_data = {
      -3.14159265f, -2.44346095f, -1.74532925f, -1.04719755f, -0.34906585f,
      0.34906585f,  1.04719755f,  1.74532925f,  2.44346095f,  3.14159265f};

  Matrix x = Matrix(x_data, 10, 1);
  Matrix y = ApplyFunc(x, func);

  for (int i = 0; i < 10; i++) std::cout << y.at(i, 0) << ' ';
  std::cout << '\n';

  train(w, b, alpha, iter, x, y, step);
}
