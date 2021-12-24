#ifndef NEURAL_NET
#define NEURAL_NET

#include "matrix.h"
#include "string"

class NeuralNet {
 private:
  std::vector<size_t> topology_;
  std::vector<Mat> weights_;
  std::vector<Mat> biases_;

  static Mat ReLu(const Mat& mat);
  static Mat SoftMax(const Mat& mat);

  void ForwardAll(const Mat& x, std::vector<Mat>& z, std::vector<Mat>& a);

  void ForwardSingle(const Mat& a_prev, const Mat& w, const Mat& b,
      Mat& z, Mat& a, Mat (*act_func)(const Mat&));

 public:
  NeuralNet(const std::vector<size_t>& topology);

  double GetAccuracy(const Mat& labels, const Mat& pred);

  void dim(const Mat& mat, std::string name);

  Mat GetSumVector(const Mat& matrix);

  void Train(const Mat& x, const Mat& y, const Mat& labels,
      unsigned n_epoch, float alpha);
};

#endif // NEURAL_NET
