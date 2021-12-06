#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

#include "matrix.h"
#include "neuralNet.h"

uint32_t swap_endian(uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}

void read_mnist_cv(const char* image_filename, const char* label_filename){
    // Open files
    std::ifstream image_file(image_filename, std::ios::in | std::ios::binary);
    std::ifstream label_file(label_filename, std::ios::in | std::ios::binary);

    // Read the magic and the meta data
    uint32_t magic;
    uint32_t num_items;
    uint32_t num_labels;
    uint32_t rows;
    uint32_t cols;

    image_file.read(reinterpret_cast<char*>(&magic), 4);
    magic = swap_endian(magic);
    if(magic != 2051){
      std::cout<<"Incorrect image file magic: "<<magic<<std::endl;
      return;
    }

    label_file.read(reinterpret_cast<char*>(&magic), 4);
    magic = swap_endian(magic);
    if(magic != 2049){
      std::cout<<"Incorrect image file magic: "<<magic<<std::endl;
      return;
    }

    image_file.read(reinterpret_cast<char*>(&num_items), 4);
    num_items = swap_endian(num_items);
    label_file.read(reinterpret_cast<char*>(&num_labels), 4);
    num_labels = swap_endian(num_labels);
    if(num_items != num_labels){
      std::cout<<"image file nums should equal to label num"<<std::endl;
      return;
    }

    image_file.read(reinterpret_cast<char*>(&rows), 4);
    rows = swap_endian(rows);
    image_file.read(reinterpret_cast<char*>(&cols), 4);
    cols = swap_endian(cols);

    std::cout<<"image and label num is: "<<num_items<<std::endl;
    std::cout<<"image rows: "<<rows<<", cols: "<<cols<<std::endl;

    char label;
    char* pixels = new char[rows * cols];

    for (int item_id = 0; item_id < num_items; ++item_id) {
        // read image pixel
        image_file.read(pixels, rows * cols);
        // read label
        label_file.read(&label, 1);

        std::string sLabel = std::to_string(int(label));
        std::cout<<"lable is: "<<sLabel<<std::endl;
        // convert it to cv Mat, and show it
        cv::Mat image_tmp(rows,cols,CV_8UC1,pixels);
        // resize bigger for showing
        cv::resize(image_tmp, image_tmp, cv::Size(100, 100));
        cv::imshow(sLabel, image_tmp);
        cv::waitKey(0);
    }

    delete[] pixels;
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

  std::string base_dir = "/home/denis/programming/CLionProjects/image_recognition/data/";
  std::string img_path = base_dir + "train-images-idx3-ubyte";
  std::string label_path = base_dir + "train-labels-idx1-ubyte";

  read_mnist_cv(img_path.c_str(), label_path.c_str());

  return 0; 
}
