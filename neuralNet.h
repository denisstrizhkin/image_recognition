#ifndef NEURAL_NET
#define	NEURAL_NET 

#include <cstdint>
#include <iostream>

class Matrix
{
private:
  uint16_t m;
  uint16_t n;
	double* array;

public:
  // Constructors
	Matrix(const uint16_t in_m, const uint16_t in_n);
	Matrix(const double* in_array,
      const uint16_t in_m, const uint16_t in_n);
	Matrix();
  Matrix(const Matrix& in_matrix);

  // Destructor
  ~Matrix();


  // Operator overloading	
	Matrix operator=(const Matrix& in_matrix);
  void Print();

  // Functions
  uint16_t N();
  uint16_t M();

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
