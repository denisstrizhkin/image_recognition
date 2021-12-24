#ifndef IMAGE_RECOGNITION_OPENCV_H_
#define IMAGE_RECOGNITION_OPENCV_H_

#include "matrix.h"

#include <cstdint>
#include <string>

struct Data {
  Mat x;
  Mat y;
  Mat labels;
  uint32_t rows;
  uint32_t cols;
};

[[nodiscard]] uint32_t SwapEndian(uint32_t val);

[[nodiscard]] Data ReadMNIST(const std::string& image_filename,
    const std::string& label_filename);

void ShowImage(const Data& data, size_t index);

#endif
