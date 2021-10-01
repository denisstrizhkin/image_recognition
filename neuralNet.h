#ifndef NEURAL_NET
#define	NEURAL_NET 

class Matrix
{
private:
  size_t m;
	size_t n;
	double** arr;

public:
	Matrix(int _m, int _n);
	Matrix();
	~Matrix();
	Matrix(Matrix* other);
	Matrix* operator=(Matrix* other);

	float Sum();
	void Ones();
	void rnd();
	Matrix* Plus(Matrix* M);
	Matrix* Plus(float num);
	Matrix* Mult(Matrix* M);
	Matrix* Mult(float num);
	Matrix* T();
	Matrix* Dot(Matrix* M);
	Matrix* Apply_f(float (*func)(float));

	void Print();
};

float sigmoid(float n);
float sigmoid_d(float n);
float relu(float n);
float relu_d(float n);
float tanhh(float n);
float tanh_d(float n);

float loss_f(float out, float target);
Matrix* loss_f_d(Matrix* out, Matrix* target);
void forward(Matrix** w, Matrix** b, Matrix* x, Matrix** z, Matrix** a);
void train(Matrix** w, Matrix** b, float alpha, int iter, Matrix* x, Matrix* y, int step);
void gen_weights(Matrix** w, int n);
void gen_bias(Matrix** b, int n);

#endif

#include "neuralNet.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

Matrix::Matrix()
{
	m = 0;
	n = 0;
	arr = nullptr;
}

Matrix::Matrix(Matrix* other)
{
	m = other->m;
	n = other->n;	
	arr = other->arr;
}

Matrix* Matrix::operator=(Matrix* other)
{
	Matrix::~Matrix();

	m = other->m;
	n = other->n;	
	arr = other->arr;

	other->m = 0;
	other->n = 0;
	other->arr = nullptr;
	
	return this;
}

Matrix::~Matrix()
{
	for (int i = 0; i < m; i++)
		delete[] arr[i];
	delete[] arr;
}

Matrix::Matrix(int _m, int _n)
{
	m = _m;
	n = _n;
	arr = new float*[m];
	for (int i = 0; i < m; i++)
		arr[i] = new float[n]; 
}

void Matrix::rnd()
{
	std::cout << "rnd start\n";
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			arr[i][j] = ((float)std::rand())/((float)RAND_MAX)-0.5f;
	std::cout << "rnd end";
}

void Matrix::Ones()
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			arr[i][j] = 1;
}

Matrix* Matrix::Plus(Matrix* M)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			arr[i][j] += M->arr[i][j];
	return this;
}

Matrix* Matrix::Plus(float num)
{	
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			arr[i][j] += num;
	return this;
}

Matrix* Matrix::Mult(float num)
{	
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			arr[i][j] *= num;
	return this;
}

Matrix* Matrix::Mult(Matrix* M)
{	
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			arr[i][j] *= M->arr[i][j];
	return this;
}

void Matrix::Print()
{
	std::cout << "+--+ m: " << m << " n: " << n << '\n';
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			std::cout << arr[i][j] << ' ';	
		std::cout << '\n';
	}
	std::cout << "+--+\n";
}

Matrix* Matrix::T()
{
	Matrix* res = new Matrix(n, m);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			res->arr[j][i] = arr[i][j];

	return res;
}

Matrix* Matrix::Dot(Matrix* M)
{
	Matrix* res = new Matrix(m, M->n);

	for (int i = 0; i < res->m; i++)
		for (int j = 0; j < res->n; j++)
		{
			res->arr[i][j] = 0;
			for (int k = 0; k < n; k++)
				res->arr[i][j] += arr[i][k] * M->arr[k][j];	
		}

	return res;
}

float sigmoid(float n) { return 1 / (1 + std::exp(-n)); }
float sigmoid_d(float n) { float sn = sigmoid(n); return sn * (1 - sn); }
float relu(float n) { return std::max(0.0f, n); }
float relu_d(float n) { return (n > 0 ? 1 : 0); }
float tanhh(float n) { return std::tanh(n); }
float tanh_d(float n) { float tn = std::tanh(n); return 1 - tn * tn;}

Matrix* Matrix::Apply_f(float (*func)(float))
{	
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			arr[i][j] = func(arr[i][j]);

	return this;
}

float loss_f(float out, float target)
{
	float diff = target - out;	
	return diff * diff;
}

Matrix* loss_f_d(Matrix* out, Matrix* target)
{	
	return target->Plus(out->Mult(-1))->Mult(-2);
}

void forward(Matrix** w, Matrix** b, Matrix* x, Matrix** z, Matrix** a)
{
	z[0] = w[0]->Dot(x)->Plus(b[0]);
	a[0] = z[0]->Apply_f(&sigmoid);

	z[1] = w[1]->Dot(a[0])->Plus(b[1]);
	a[1] = z[1];
}

float Matrix::Sum()
{
	float res = 0;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			res += arr[i][j];

	return res;
}

void train(Matrix** w, Matrix** b, float alpha, int iter, Matrix* x, Matrix* y, int step)
{
	Matrix** z = new Matrix*[2];
	Matrix** dz = new Matrix*[2];
	Matrix** a = new Matrix*[2];
	Matrix* in = new Matrix(1, 1);
	Matrix* target = new Matrix(1, 1);

	for (int i = 0; i < iter; i++)
	{
		bool cond = ((i + 1) % step) == 0;
		float loss = 0.0;

		for (int j = 0; j < x->m; j++)
		{	
			in->arr[0][0] = x->arr[j][0];
			target->arr[0][0] = y->arr[j][0];
			
			forward(w, b, x, z, a);
			loss += loss_f(a[1]->arr[0][0], y->arr[j][0]);

			dz[1] = loss_f_d(a[1], target);
			dz[0] = w[1]->T()->Dot(dz[1])->Mult(z[0]->Apply_f(&sigmoid_d));

			w[1] = w[1]->Plus(dz[1]->Dot(a[0]->T())->Mult(-alpha));
			b[1] = b[1]->Plus(dz[1]->Sum() * (-alpha));

			w[0] = w[0]->Plus(dz[0]->Dot(in)->Mult(-alpha));
			b[0] = b[0]->Plus(dz[0]->Sum() * (-alpha));
		}

		if (cond)
			std::cout<<"iteration #"<<i+1<<" - loss: "<<loss/x->m<<'\n';
	}
}

void gen_weights(Matrix** w, int n)
{
	w[0] = new Matrix(n, 1);
	w[0]->rnd();

	w[1] = new Matrix(1, n);
	w[1]->rnd();
}

void gen_bias(Matrix** b, int n)
{
	b[0] = new Matrix(n, 1);
	b[0]->rnd();
	
	b[1] = new Matrix(1, 1);
	b[1]->rnd();
}
