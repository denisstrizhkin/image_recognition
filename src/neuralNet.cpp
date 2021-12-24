#include "neuralNet.h"

#include <iomanip>
#include <cmath>
#include <iostream>

Mat NeuralNet::ReLu(const Mat& mat) {
  std::cout << "in relu\n";
  return mat.ApplyFunc([](float num){ return ( num > 0 ? num : 0 ); });
}

Mat NeuralNet::SoftMax(const Mat& mat) {
  Mat new_mat(mat.ApplyFunc([](float num) { return std::exp(num); }));

  for (size_t n_i = 0; n_i < new_mat.n(); n_i++) {
    float sum = 0.0f;
    for (size_t m_i = 0; m_i < new_mat.m(); m_i++)
      sum += new_mat.at(m_i, n_i);

    for (size_t m_i = 0; m_i < new_mat.m(); m_i++)
      new_mat.at(m_i, n_i) /= sum;
  }

  return new_mat;
}

void NeuralNet::ForwardAll(const Mat& x, std::vector<Mat>& z, std::vector<Mat>& a) {
  ForwardSingle(x, weights_.at(0), biases_.at(0), z.at(0), a.at(0), ReLu);
  std::cout << "imput layer: ok\n";

  size_t i = 1;
  for (; i < weights_.size() - 1; i++)
    ForwardSingle(a.at(i-1), weights_.at(i), biases_.at(i), z.at(i), a.at(i), ReLu);
  std::cout << "hidden layers: ok\n";

  ForwardSingle(a.at(i-1), weights_.at(i), biases_.at(i), z.at(i), a.at(i), SoftMax);
  std::cout << "softmax layer: ok\n";
}

void NeuralNet::ForwardSingle(const Mat& a_prev, const Mat& w, const Mat& b,
    Mat& z, Mat& a, Mat (*act_func)(const Mat&)) {
  Mat bt(b.m(), a_prev.n());
  for (size_t n_i = 0; n_i < bt.n(); n_i++)
    for (size_t m_i = 0; m_i < bt.m(); m_i++)
      bt.at(m_i, n_i) = b.at(m_i, 0);

  dim(a_prev, "a_p");
  dim(w, "w");
  dim(bt, "bt");

  z = w.Dot(a_prev) + bt;

  dim(z, "z");
  a = act_func(z);
  dim(a, "a");
}

NeuralNet::NeuralNet(const std::vector<size_t>& topology) : topology_(topology){
  for (size_t i = 1; i < topology_.size(); i++) {
    weights_.emplace_back(Mat(topology_.at(i), topology_.at(i-1)));
    biases_.emplace_back( Mat(topology_.at(i),                  1));

    Mat::Randomize(weights_.at(i-1));
    Mat::Randomize(biases_.at( i-1));
  }
}

double NeuralNet::GetAccuracy(const Mat& labels, const Mat& pred) {
  std::vector<float> result(labels.n());
  std::cout << "accuracy: " << result.size() << '\n';

  for (size_t n_i = 0; n_i < labels.n(); n_i++) {
    float max = 0.0f;
    size_t max_i = 0;

    for (size_t m_i = 0; m_i < pred.m(); m_i++)
      if (pred.at(m_i, n_i) > max) {
        max = pred.at(m_i, n_i);
        max_i = m_i;
      }

    result.at(n_i) = max_i;
  }

  double sum = 0.0;

  for (size_t n_i = 0; n_i < labels.n(); n_i++)
    if (labels.at(0, n_i) == result.at(n_i))
      sum += 1;

  std::cout << "sum: " << sum << '\n';
  return sum / pred.n();
}

void NeuralNet::dim(const Mat& mat, std::string name) {
  std::cout << name << ": " << mat.m() << ", " << mat.n() << '\n';
}


Mat NeuralNet::GetSumVector(const Mat& matrix) {
  Mat result(matrix.m(), 1);

  for (size_t m_i = 0; m_i < matrix.m(); m_i++) {
    result.at(m_i, 0) = 0.0f;
    for (size_t n_i = 0; n_i < matrix.n(); n_i++) {
      result.at(m_i, 0) += matrix.at(m_i, n_i);
    }
    result.at(m_i, 0) /= matrix.n();
  }

  return result;
}

void NeuralNet::Train(const Mat& x, const Mat& y, const Mat& labels,
    unsigned n_epoch, float alpha) {
  std::vector<Mat> d_z(topology_.size() - 1);
  std::vector<Mat> z(  topology_.size() - 1);
  std::vector<Mat> a(  topology_.size() - 1);

  for (unsigned epoch = 0; epoch < n_epoch; epoch++) {
    std::cout << "before forward\n";
    ForwardAll(x, z, a);
    std::cout << "after forward\n";

    double accuracy = GetAccuracy(labels, a.back());
    std::cout << "after loss\n";

    d_z.back() = a.back() - y;
    std::cout << "after 1st dz\n";
    std::cout << "d_z: " << d_z.size() << '\n';
    for (size_t i = d_z.size() - 1; i > 0; i--) {
      dim(weights_.at(i).T(), "w"+std::to_string(i)); dim(d_z.at(i), "dzi");
      d_z.at(i-1) = weights_.at(i).T().Dot(d_z.at(i)) *
        z.at(i-1).ApplyFunc([](float num){ return ( num > 0 ? 1.0f : 0.0f ); });
    }
    std::cout << "after d_z\n";

    for (size_t i = weights_.size() - 1; i > 0; i--)
      weights_.at(i) -= alpha * d_z.at(i).Dot(a.at(i-1).T());
    weights_.at(0) -= alpha * d_z.at(0).Dot(x.T());
    std::cout << "after dw\n";

    for (size_t i = weights_.size() - 1; i > 0; i--)
      biases_.at(i) -= alpha * GetSumVector(d_z.at(i));
    std::cout << "after db\n";

    //dim(w[0], "w[0]");
    //dim(d_z[0], "d_z[0]");
    //dim(x_data, "x_data");
    //
    std::cout << "epoch #" << std::setw(6) << epoch + 1
      << ": accuracy: " << std::setw(8)
                << accuracy << '\n';
  }
}
