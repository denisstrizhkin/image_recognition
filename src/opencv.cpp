#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

#include "opencv.h"

uint32_t OCV::SwapEndian(uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}

OCV::Data OCV::ReadMNIST(const std::string& image_filename,
    const std::string& label_filename, unsigned num_items_assigned) {
  // Open files
  std::ifstream image_file(image_filename, std::ios::in | std::ios::binary);
  std::ifstream label_file(label_filename, std::ios::in | std::ios::binary);

  // Read the magic and the meta data
  uint32_t magic;
  uint32_t num_items;
  uint32_t num_labels;

  Data data;

  image_file.read(reinterpret_cast<char*>(&magic), 4);
  label_file.read(reinterpret_cast<char*>(&magic), 4);


  image_file.read(reinterpret_cast<char*>(&num_items), 4);
  num_items = SwapEndian(num_items);
  label_file.read(reinterpret_cast<char*>(&num_labels), 4);
  num_labels = SwapEndian(num_labels);

  image_file.read(reinterpret_cast<char*>(&data.rows), 4);
  data.rows = SwapEndian(data.rows);
  image_file.read(reinterpret_cast<char*>(&data.cols), 4);
  data.cols = SwapEndian(data.cols);

  num_items = std::min(num_items, num_items_assigned);
  std::cout << "image and label num is: " << num_items << '\n';
  std::cout << "image rows: " << data.rows << ", cols: " << data.cols << '\n';

  uint32_t num_pixels = data.rows * data.cols;

  data.x = Mat(num_items, num_pixels);
  data.labels = Mat(num_items, 1);

  std::vector<char> pixels(num_pixels);
  for (int item_id = 0; item_id < num_items; ++item_id) {
    // read image pixel
    image_file.read(&pixels[0], num_pixels);
    std::copy(pixels.begin(), pixels.end(),
        data.x.begin() + item_id*num_pixels);

    // read label
    char label;
    label_file.read(&label, 1);
    data.labels.at(item_id, 0) = label;
  }

  data.y = Mat(data.x.m(), 10);
  for (size_t m_i = 0; m_i < data.y.m(); m_i++)
    data.y.at(m_i, data.labels.at(m_i, 0)) = 1.0f;

  return data;
}

void OCV::ShowImage(const Data& data, size_t index) {
    std::vector<char> pixels(data.x.n());
    float* p = data.x.begin() + index*data.x.n();
    std::copy(p, p+data.x.n(), pixels.begin());

    unsigned label = data.labels.at(index, 0);

    // convert it to cv Mat, and show it
    cv::Mat image(data.rows, data.cols, CV_8UC1, &pixels[0]);
    // resize bigger for showing
    cv::resize(image, image, cv::Size(100, 100));
    cv::imshow(std::to_string(label), image);
    cv::waitKey(0);
}
