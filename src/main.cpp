#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

#include "matrix.h"
#include "neuralNet.h"

struct Data {
  std::vector<char> labels;
  std::vector<std::vector<char>> pixels;

  bool empty() const {
    if (labels.size() == 0 || pixels.size() == 0)
      return true;
    else
      return false;
  }
};


[[nodiscard]] uint32_t swap_endian(uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}

[[nodiscard]] Data read_mnist(const std::string& image_filename,
    const std::string& label_filename) {
  // Open files
  std::ifstream image_file(image_filename, std::ios::in | std::ios::binary);
  std::ifstream label_file(label_filename, std::ios::in | std::ios::binary);

  // Read the magic and the meta data
  uint32_t magic;
  uint32_t num_items;
  uint32_t num_labels;
  uint32_t rows;
  uint32_t cols;

  Data data;

  image_file.read(reinterpret_cast<char*>(&magic), 4);
  magic = swap_endian(magic);
  if (magic != 2051) {
    std::cout << "Incorrect image file magic: " << magic << '\n';
    return data;
  }

  label_file.read(reinterpret_cast<char*>(&magic), 4);
  magic = swap_endian(magic);
  if (magic != 2049) {
    std::cout << "Incorrect image file magic: " << magic << '\n';
    return data;
  }

  image_file.read(reinterpret_cast<char*>(&num_items), 4);
  num_items = swap_endian(num_items);
  label_file.read(reinterpret_cast<char*>(&num_labels), 4);
  num_labels = swap_endian(num_labels);

  if (num_items != num_labels) {
    std::cout << "image file nums should equal to label num\n";
    return data;
  }

  image_file.read(reinterpret_cast<char*>(&rows), 4);
  rows = swap_endian(rows);
  image_file.read(reinterpret_cast<char*>(&cols), 4);
  cols = swap_endian(cols);

  std::cout << "image and label num is: " << num_items << '\n';
  std::cout << "image rows: " <<rows << ", cols: " << cols << '\n';

  data.labels.resize(num_items);
  data.pixels.resize(num_items);

  for (int item_id = 0; item_id < num_items; ++item_id) {
    // read image pixel
    data.pixels.at(item_id).resize(rows * cols);
    image_file.read(&data.pixels.at(item_id)[0], rows * cols);

    // read label
    label_file.read(&data.labels[item_id], 1);

    std::string label_str = std::to_string(data.labels.at(item_id));
    //std::cout<<"lable is: "<< label_str << '\n';

    //// convert it to cv Mat, and show it
    //cv::Mat image_tmp(rows, cols, CV_8UC1, &data.pixels.at(item_id)[0]);
    //// resize bigger for showing
    //cv::resize(image_tmp, image_tmp, cv::Size(100, 100));
    //cv::imshow(label_str, image_tmp);
    //cv::waitKey(0);
  }

  return data;
}

double func(double num) { return std::cos(num); }

int main(int argc, char** argv) {
  //int n = 10;

  //std::vector<Matrix> w = gen_weights(n);
  //std::vector<Matrix> b = gen_bias(n);

  //double alpha = 0.01;
  //int iter = 1000;
  //int step = 100;

  //std::vector<double> x_data = {
  //    -3.14159265f, -2.44346095f, -1.74532925f, -1.04719755f, -0.34906585f,
  //    0.34906585f,  1.04719755f,  1.74532925f,  2.44346095f,  3.14159265f};

  //Matrix x = Matrix(x_data, 10, 1);
  //Matrix y = ApplyFunc(x, func);
  //
  //for (int i = 0; i < 10; i++) std::cout << y.at(i, 0) << ' ';
  //std::cout << '\n';

  //train(w, b, alpha, iter, x, y, step);

  std::string base_dir =
    "/home/denis/programming/CLionProjects/image_recognition/data/";
  std::string img_path = base_dir + "train-images-idx3-ubyte";
  std::string label_path = base_dir + "train-labels-idx1-ubyte";

  Data data = read_mnist(img_path, label_path);

  unsigned n1 = 784;
  unsigned n2 = 10;
  unsigned n3 = 10;

  std::vector<Matrix> w(2);
  std::vector<Matrix> b(2);

  w.emplace(w.begin() + 0, gen_weights(n1, n2));
  b.emplace(b.begin() + 0, gen_biases(n2));

  w.emplace(w.begin() + 1, gen_weights(n2, n3));
  b.emplace(b.begin() + 1, gen_biases(n3));

  std::cout << "x_data cols: " << data.pixels.size() << '\n';
  std::cout << "x_data rows: " << data.pixels.at(0).size() << '\n';

  std::vector<std::vector<double>> x_data(data.pixels.size());

  for (size_t i = 0; i < x_data.size(); i++) {
    x_data.at(i).resize(data.pixels.at(i).size());

    for (size_t j = 0; j < x_data.at(i).size(); j++)
      x_data.at(i).at(j) = data.pixels.at(i).at(j);
  }

  std::vector<std::vector<double>> y_data(data.labels.size());
  
  for (size_t i = 0; i < y_data.size(); i++) {
    y_data.at(i).resize(10);
    for (double& num : y_data.at(i)) num = 0.0;
    y_data.at(i).at(data.labels.at(i)) = 1.0;
  }

  Matrix x(x_data);
  Matrix y(y_data);

  double alpha = 0.01;
  int iter = 100;
  int step = 10;

  train(w, b, alpha, iter, x, y, step);

  return 0;
}
