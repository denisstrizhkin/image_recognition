#include "neuralNet.h"

Matrix::Matrix(const uint16_t in_m, const uint16_t in_n)
{
  m = in_m;
  n = in_n;

  array = new double[m * n];
}

Matrix::Matrix()
{
  m = 0;
  n = 0;

  array = nullptr;
}

Matrix::Matrix(const double* in_array,
  const uint16_t in_m, const uint16_t in_n)
{
  m = in_m;
  n = in_n;

  array = new double[m * n];

  for (uint16_t i_m = 0; i_m < m; i_m++)
    for (uint16_t i_n = 0; i_n < n; i_n++)
    {
      uint16_t index = i_m * n + i_n;
      array[index] = in_array[index];
    }
}

Matrix::Matrix(const Matrix& in_matrix)
{
  m = in_matrix.m;
  n = in_matrix.n;
  
  array = new double[m * n];

  for (uint16_t i_m = 0; i_m < m; i_m++)
    for (uint16_t i_n = 0; i_n < n; i_n++)
    {
      uint16_t index = i_m * n + i_n;
      array[index] = in_matrix.array[index];
    }
}

Matrix::~Matrix()
{
  delete array;
}

Matrix Matrix::operator=(const Matrix& in_matrix)
{
  m = in_matrix.m;
  n = in_matrix.n;
  
  array = new double[m * n];

  for (uint16_t i_m = 0; i_m < m; i_m++)
    for (uint16_t i_n = 0; i_n < n; i_n++)
    {
      uint16_t index = i_m * n + i_n;
      array[index] = in_matrix.array[index];
    }

  return *this;
}

uint16_t Matrix::M()
{
  return m;
}

uint16_t Matrix::N()
{
  return n;
}

void Matrix::Print()
{
    for (uint16_t i = 0; i < 10; i++)
      std::cout << '*';
    std::cout << "\nm: " << m << " n: " << n << '\n';

    for (uint16_t i_m = 0; i_m < m; i_m++)
    {
      for (uint16_t i_n = 0; i_n < n; i_n++)
      {
        std::cout << array[i_m * n + i_n] << ' ';
      }
      std::cout << '\n';
    }

    for (uint16_t i = 0; i < 10; i++)
      std::cout << '*';
    std::cout << '\n';
}
