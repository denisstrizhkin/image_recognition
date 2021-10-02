#include "neuralNet.h"

Matrix::Matrix() : m_(0), n_(0), array_(nullptr) {}
Matrix::~Matrix() { delete array_; }

size_t Matrix::M() { return m_; }
size_t Matrix::N() { return n_; }

const char* Matrix::DimensionsException::what() 
  const noexcept { return "Dimensions do not match!"; }
const char* Matrix::WrongIndexException::what()
  const noexcept { return "Wrong Index!"; }

Matrix::Matrix(size_t _m, size_t _n) : m_(_m), n_(_n)
{ 
  array_ = new double[m_ * n_];
}

Matrix::Matrix(const std::vector<double>& in_vector,
    size_t _m, size_t _n) : m_(_m), n_(_n)
{
  if (in_vector.size() != m_ * n_) throw DimensionsException();
  
  array_ = new double[m_ * n_];
  
  for (size_t i = 0; i < m_ * n_; i++) array_[i] = in_vector[i];
}

Matrix::Matrix(const Matrix& in_matrix) : m_(in_matrix.m_), n_(in_matrix.n_)
{
  array_ = new double[m_ * n_];
  
  for (size_t i = 0; i < m_ * n_; i++) array_[i] = in_matrix.array_[i];
}

Matrix Matrix::operator=(const Matrix& in_matrix)
{
  m_ = in_matrix.m_;
  n_ = in_matrix.n_;
  array_ = new double[m_ * n_];

  for (size_t i = 0; i < m_ * n_; i++) array_[i] = in_matrix.array_[i];

  return *this;
}

Matrix Matrix::operator+(const Matrix& mat)
{
  if (mat.n_ != n_ || mat.m_ != m_) throw DimensionsException();

  Matrix new_mat(m_, n_);
  
  for (size_t i = 0; i < n_ * m_; i++)
    new_mat.array_[i] = array_[i] + mat.array_[i];

  return new_mat;
}

Matrix operator+(double in_num, const Matrix& in_matrix)
{
  Matrix new_matrix(in_matrix.m_, in_matrix.n_);

  for (int i = 0; i < new_matrix.m_ * new_matrix.n_; i++)
    new_matrix.array_[i] = in_num + in_matrix.array_[i];

  return new_matrix;
}

Matrix operator+(const Matrix& in_matrix, double in_num)
{
  Matrix new_matrix(in_matrix.m_, in_matrix.n_);

  for (int i = 0; i < new_matrix.m_ * new_matrix.n_; i++)
    new_matrix.array_[i] = in_num + in_matrix.array_[i];

  return new_matrix;
}

Matrix Matrix::operator-(const Matrix& mat)
{
  if (mat.n_ != n_ || mat.m_ != m_) throw DimensionsException();

  Matrix new_mat(m_, n_);
  
  for (size_t i = 0; i < n_ * m_; i++)
    new_mat.array_[i] = array_[i] - mat.array_[i];

  return new_mat;
}

Matrix operator-(double in_num, const Matrix& in_matrix)
{
  Matrix new_matrix(in_matrix.m_, in_matrix.n_);

  for (int i = 0; i < new_matrix.m_ * new_matrix.n_; i++)
    new_matrix.array_[i] = in_num - in_matrix.array_[i];

  return new_matrix;
}

Matrix operator-(const Matrix& in_matrix, double in_num)
{
  Matrix new_matrix(in_matrix.m_, in_matrix.n_);

  for (int i = 0; i < new_matrix.m_ * new_matrix.n_; i++)
    new_matrix.array_[i] = in_matrix.array_[i] - in_num;

  return new_matrix;
}

Matrix Matrix::operator*(const Matrix& mat)
{
  if (mat.n_ != n_ || mat.m_ != m_) throw DimensionsException();

  Matrix new_mat(m_, n_);
  
  for (size_t i = 0; i < n_ * m_; i++)
    new_mat.array_[i] = array_[i] * mat.array_[i];

  return new_mat;
}

Matrix operator*(double in_num, const Matrix& in_matrix)
{
  Matrix new_matrix(in_matrix.m_, in_matrix.n_);

  for (int i = 0; i < new_matrix.m_ * new_matrix.n_; i++)
    new_matrix.array_[i] = in_num * in_matrix.array_[i];

  return new_matrix;
}

Matrix operator*(const Matrix& in_matrix, double in_num)
{
  Matrix new_matrix(in_matrix.m_, in_matrix.n_);

  for (int i = 0; i < new_matrix.m_ * new_matrix.n_; i++)
    new_matrix.array_[i] = in_num * in_matrix.array_[i];

  return new_matrix;
}

Matrix Matrix::operator/(const Matrix& mat)
{
  if (mat.n_ != n_ || mat.m_ != m_) throw DimensionsException();

  Matrix new_mat(m_, n_);
  
  for (size_t i = 0; i < n_ * m_; i++)
    new_mat.array_[i] = array_[i] / mat.array_[i];

  return new_mat;
}

Matrix operator/(double in_num, const Matrix& in_matrix)
{
  Matrix new_matrix(in_matrix.m_, in_matrix.n_);

  for (int i = 0; i < new_matrix.m_ * new_matrix.n_; i++)
    new_matrix.array_[i] = in_num / in_matrix.array_[i];

  return new_matrix;
}

Matrix operator/(const Matrix& in_matrix, double in_num)
{
  Matrix new_matrix(in_matrix.m_, in_matrix.n_);

  for (int i = 0; i < new_matrix.m_ * new_matrix.n_; i++)
    new_matrix.array_[i] = in_matrix.array_[i] / in_num;

  return new_matrix;
}

double& Matrix::At(size_t i_m, size_t i_n)
{
  if (i_m >= m_ || i_n >= n_) throw WrongIndexException();

  return array_[i_m * n_ + i_n];
}

Matrix Matrix::Dot(const Matrix& in_matrix)
{
  if (in_matrix.m_ != n_) throw DimensionsException();

  Matrix new_matrix(m_, in_matrix.n_);

  for (size_t new_i_m = 0; new_i_m < new_matrix.m_; new_i_m++)
    for (size_t new_i_n = 0; new_i_n < new_matrix.n_; new_i_n++)
    {
      size_t new_index = new_i_m * new_matrix.n_ + new_i_n;

      new_matrix.array_[new_index] = 0.0;
      for (size_t i_n = 0; i_n < n_; i_n++)
        new_matrix.array_[new_index] +=
          array_[new_i_m * n_ + i_n] *
          in_matrix.array_[i_n * in_matrix.n_ + new_i_n];
    }

  return new_matrix;
}

Matrix Matrix::T()
{
  Matrix new_matrix(n_, m_);

  for (size_t i_m = 0; i_m < m_; i_m++)
    for (size_t i_n = 0; i_n < n_; i_n++)
      new_matrix.array_[i_n * m_ + i_m] = array_[i_m * n_ + i_n];

  return new_matrix;
}

void Matrix::Print()
{
    for (size_t i = 0; i < 10; i++)
      std::cout << '*';
    std::cout << "\nm: " << m_ << " n: " << n_ << '\n';

    for (size_t i_m = 0; i_m < m_; i_m++)
    {
      for (size_t i_n = 0; i_n < n_; i_n++)
      {
        std::cout << array_[i_m * n_ + i_n] << ' ';
      }
      std::cout << '\n';
    }

    for (size_t i = 0; i < 10; i++)
      std::cout << '*';
    std::cout << '\n';
}
