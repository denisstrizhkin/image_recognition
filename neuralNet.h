#ifndef NEURAL_NET
#define	NEURAL_NET 

class Matrix
{
private:
  size_t m;
	size_t n;
	double* array;

public:
	Matrix(const size_t in_m, const size_t in_n);
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
