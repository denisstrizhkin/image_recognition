#ifndef IMAGE_RECOGNITION_RANDOM_H_
#define IMAGE_RECOGNITION_RANDOM_H_

#include <chrono>
#include <random>

class Random {
 private:
   std::default_random_engine rnd_engine_;
   std::uniform_real_distribution<float> distrib_ =
     std::uniform_real_distribution<float>(-0.5f, 0.5f);

 public:
  Random() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rnd_engine_ = std::default_random_engine(seed);
  }
  
  [[nodiscard]] float operator()() { return distrib_(rnd_engine_); }
};

#endif // IMAGE_RECOGNITION_RANDOM_H_
