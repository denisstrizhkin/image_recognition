#include <iostream>
#include <cmath>
#include "neuralNet.h"

float func(float num)
{
	return std::cos(num);
}

int main()
{
  Matrix m;

  std::cout << m.N() << '\n';
  std::cout << m.M() << '\n';

  double numbers[6] = { 0.5, 0.3, 0.4, 0.6, 0.8, 0.2 };
  Matrix num_matrix(numbers, 3, 2);
  num_matrix.Print();

  for (unsigned i = 0; i < 10000000; i++)
  {
    std::cout << "i: " << i << '\n';
    Matrix temp(10000, 10000);
    Matrix a;

    a = temp;

    Matrix b = temp;
  }
}
