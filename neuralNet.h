#ifndef NEURAL_NET
#define	NEURAL_NET 

#include <iostream>
#include <vector>

class Matrix
{
private:
  size_t m_;
  size_t n_;
	double* array_;

  class DimensionsException : public std::exception
  {
    virtual const char* what() const noexcept;
  };

  class WrongIndexException : public std::exception
  {
    virtual const char* what() const noexcept;
  };

public:
  // Constructors
  Matrix(size_t _m, size_t _n);
  Matrix(const std::vector<double>& in_vector, size_t _m, size_t _n);
  Matrix();
  Matrix(const Matrix& in_matrix);
  
  // Destructor
  ~Matrix();
  
  // Operator overloading	
  // =
  Matrix operator=(const Matrix& in_matrix);
  // + 
  Matrix operator+(const Matrix& in_matrix);
  friend Matrix operator+(double in_num, const Matrix& in_matrix);
  friend Matrix operator+(const Matrix& in_matrix, double in_num);
  // -
  Matrix operator-(const Matrix& in_matrix);
  friend Matrix operator-(double in_num, const Matrix& in_matrix);
  friend Matrix operator-(const Matrix& in_matrix, double in_num);
  // *
  Matrix operator*(const Matrix& in_matrix);
  friend Matrix operator*(double in_num, const Matrix& in_matrix);
  friend Matrix operator*(const Matrix& in_matrix, double in_num); 
  // /
  Matrix operator/(const Matrix& in_matrix);
  friend Matrix operator/(double in_num, const Matrix& in_matrix);
  friend Matrix operator/(const Matrix& in_matrix, double in_num); 
  
  // Functions
  double& At(size_t i_m, size_t i_n); 
  size_t N();
  size_t M();  
  void Print(); 
  double Sum();
  Matrix T();
  Matrix Dot(const Matrix& in_matrix);
};

//Matrix* Dot(Matrix* M);
//Matrix* Apply_f(float (*func)(float));
//void Ones();
//void rnd();

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
