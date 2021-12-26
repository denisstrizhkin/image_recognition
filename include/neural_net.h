#ifndef IMAGE_RECOGNITION_NEURAL_NET_H_
#define IMAGE_RECOGNITION_NEURAL_NET_H_

#include "matrix.h"
#include "string"

class NeuralNet {
 private:
  std::vector<size_t> topology_;
  std::vector<Mat> weights_;
  std::vector<Mat> biases_;

  [[nodiscard]] static Mat ReLu(const Mat& mat);
  [[nodiscard]] static Mat SoftMax(const Mat& mat);

  [[nodiscard]] static Mat GetSumVector(const Mat& matrix);

  [[nodiscard]] static double GetAccuracy(const Mat& labels, const Mat& pred);

  void ForwardAll(const Mat& x, std::vector<Mat>& z, std::vector<Mat>& a) const;

  void ForwardSingle(const Mat& a_prev, const Mat& w, const Mat& b,
      Mat& z, Mat& a, Mat (*act_func)(const Mat&)) const;

  void Backward(const Mat& x, const Mat& dz,
      const std::vector<Mat>& z, const std::vector<Mat>& a,
      std::vector<Mat>& dw, std::vector<Mat>& db) const;

  void UpdateParameters(double alpha,
      const std::vector<Mat>& dw, const std::vector<Mat>& db);

 public:
  NeuralNet(const std::vector<size_t>& topology);

  void Train(const Mat& x, const Mat& y, const Mat& labels,
      unsigned n_epoch, double alpha);

  void Test(const Mat& x, const Mat& y, const Mat& labels) const;
};

#endif // IMAGE_RECOGNITION_NEURAL_NET_H_

