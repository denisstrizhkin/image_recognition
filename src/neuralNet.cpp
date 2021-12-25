#include "neural_net.h"

#include <iomanip>
#include <cmath>
#include <iostream>

Mat NeuralNet::ReLu(const Mat& mat) {
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

void NeuralNet::ForwardAll(const Mat& x,
    std::vector<Mat>& z, std::vector<Mat>& a) const {
  ForwardSingle(x, weights_.at(0), biases_.at(0), z.at(0), a.at(0), ReLu);
  std::cout << "input layer: ok\n";

  size_t i = 1;
  for (; i < weights_.size() - 1; i++)
    ForwardSingle(a.at(i-1), weights_.at(i), biases_.at(i), z.at(i), a.at(i), ReLu);
  std::cout << "hidden layers: ok\n";

  ForwardSingle(a.at(i-1), weights_.at(i), biases_.at(i), z.at(i), a.at(i), SoftMax);
  std::cout << "softmax layer: ok\n";
}

void NeuralNet::ForwardSingle(const Mat& a_prev, const Mat& w, const Mat& b,
    Mat& z, Mat& a, Mat (*act_func)(const Mat&)) const {
  Mat bt(b.m(), a_prev.n());
  for (size_t n_i = 0; n_i < bt.n(); n_i++)
    for (size_t m_i = 0; m_i < bt.m(); m_i++)
      bt.at(m_i, n_i) = b.at(m_i, 0);

  z = w.Dot(a_prev) + bt;
  a = act_func(z);
}

void NeuralNet::Backward(const Mat& x, const Mat& y,
    const std::vector<Mat>& z, const std::vector<Mat>& a,
    std::vector<Mat>& dw, std::vector<Mat>& db) const {
  std::vector<Mat> dz(topology_.size() - 1);

  dz.back() = a.back()-y;
  for (size_t i = dz.size() - 1; i > 0; i--)
    dz.at(i-1) = weights_.at(i).T().Dot(dz.at(i)) *
      z.at(i-1).ApplyFunc([](float num){ return ( num > 0 ? 1.0f : 0.0f ); });

  for (size_t i = weights_.size() - 1; i > 0; i--)
    dw.at(i) = (1.0f/x.n()) * dz.at(i).Dot(a.at(i-1).T());
  dw.at(0) = (1.0f/x.n()) * dz.at(0).Dot(x.T());

  for (size_t i = 0; i < biases_.size(); i++)
    db.at(i) = (1.0f/x.n()) * GetSumVector(dz.at(i));
}

void NeuralNet::UpdateParameters(float alpha,
    const std::vector<Mat> &dw, const std::vector<Mat> &db) {
  for (size_t i = 0; i < weights_.size(); i++)
    weights_.at(i) -= alpha * dw.at(i);

  for (size_t i = 0; i < biases_.size(); i++)
    biases_.at(i) -= alpha * db.at(i);
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

  return sum / pred.n();
}

Mat NeuralNet::GetSumVector(const Mat& matrix) {
  Mat result(matrix.m(), 1);

  for (size_t m_i = 0; m_i < matrix.m(); m_i++) {
    result.at(m_i, 0) = 0.0f;
    for (size_t n_i = 0; n_i < matrix.n(); n_i++)
      result.at(m_i, 0) += matrix.at(m_i, n_i);
  }

  return result;
}

void NeuralNet::Train(const Mat& x, const Mat& y, const Mat& labels,
    unsigned n_epoch, float alpha) {
  std::vector<Mat> z(  topology_.size() - 1);
  std::vector<Mat> a(  topology_.size() - 1);

  std::vector<Mat> dw( topology_.size() - 1);
  std::vector<Mat> db( topology_.size() - 1);

  for (unsigned epoch = 0; epoch < n_epoch; epoch++) {
    ForwardAll(x, z, a);
    std::cout << "forward: ok\n";

    double accuracy = GetAccuracy(labels, a.back());
    std::cout << "accuracy: ok\n";

    Backward(x, y, z, a, dw, db);
    std::cout << "backward: ok\n";

    UpdateParameters(alpha, dw, db);
    std::cout << "update params: ok\n";

    std::cout << "epoch #" << std::setw(6) << epoch + 1
      << ": accuracy: " << std::setw(8)
                << accuracy << '\n';
  }
}

void NeuralNet::Test(const Mat& x, const Mat& y, const Mat& labels) const {
  std::vector<Mat> z(  topology_.size() - 1);
  std::vector<Mat> a(  topology_.size() - 1);

  ForwardAll(x, z, a);
  std::cout << "forward: ok\n";

  double accuracy = GetAccuracy(labels, a.back());
  std::cout << "accuracy: ok\n";

  std::cout << "test results: accuracy: " << std::setw(8) << accuracy << '\n';
}
