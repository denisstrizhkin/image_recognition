#include <cmath>
#include <iostream>
#include <filesystem>


#include "neuralNet.h"
#include "opencv.h" // kinda works wow


int main(int argc, char** argv) {
  std::string base_dir = std::filesystem::current_path().generic_string()
    + "/../data/";
  std::string img_path = base_dir + "train-images-idx3-ubyte";
  std::string label_path = base_dir + "train-labels-idx1-ubyte";

  //Data data = ReadMNIST(img_path, label_path);


  //NeuralNet nnet({784, 10, 10});

  //for (size_t i = 0; i < y_data.size(); i++) {
  //  y_data.at(i).resize(10);
  //  for (float& num : y_data.at(i)) num = 0.0;
  //  y_data.at(i).at(data.labels.at(i)) = 1.0;
  //}

  //nnet.Train(x, y, lbls, step, alpha);

  return 0;
}
