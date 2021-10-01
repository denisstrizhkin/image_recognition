#include <iostream>
#include <cmath>
#include "neuralNet.h"

float func(float num)
{
	return std::cos(num);
}

int main()
{
	int n = 10;
	Matrix** w = new Matrix*[2];
	Matrix** b = new Matrix*[2];

	gen_weights(w, n);
	gen_bias(b, n);

	float alpha = 0.01;
	int iter = 100000;
	int step = 100;

	float* x_data = new float[10] { -3.14159265f, -2.44346095f, -1.74532925f,
		-1.04719755f, -0.34906585f, 0.34906585f,  1.04719755f, 
		1.74532925f,  2.44346095f,  3.14159265f};
	Matrix* x = new Matrix(10, 1);
	for (int i = 0; i < 10; i++)
		x->arr[i][0] = x_data[i];
	Matrix* y = x->Apply_f(func);

	for (int i = 0; i < 10; i++)
		std::cout << y->arr[i][0] << ' ';

	train(w, b, alpha, iter, x, y, step);
}
