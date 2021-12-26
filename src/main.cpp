#include <cmath>
#include <iostream>

#include "neural_net.h"
#include "prog_path.h"
#include "opencv.h"

int main(int argc, char** argv) {
  std::string data_path = ProgPath::Get() + "/../data/";

  std::string train_images = data_path + "train-images-idx3-ubyte";
  std::string train_labels = data_path + "train-labels-idx1-ubyte";

  std::string test_images = data_path + "t10k-images-idx3-ubyte";
  std::string test_labels = data_path + "t10k-labels-idx1-ubyte";

  OCV::Data train_data = OCV::ReadMNIST(train_images, train_labels, 10000);
  OCV::Data test_data  = OCV::ReadMNIST(test_images, test_labels, 10000); 

  NeuralNet nnet({784, 64, 10});

  nnet.Train(train_data.x.T()/255, train_data.y.T(),
      train_data.labels.T(), 200, 10);

  nnet.Test(test_data.x.T()/255, test_data.y.T(), test_data.labels.T());

  return 0;
}
