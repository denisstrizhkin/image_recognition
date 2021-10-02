#include <iostream>
#include <cmath>
#include "neuralNet.h"

float func(float num)
{
	return std::cos(num);
}

int main()
{
  for (int i = 0; i < 1000000; i++)
  {
    Matrix m1(10000, 1);
    Matrix m2(1, 10000);

    Matrix m3 = m1.Dot(m2).T().T().T().Dot(m1);

    std::cout << "i: " << i << '\n';
  }
}
