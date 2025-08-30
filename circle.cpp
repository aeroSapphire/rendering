#include <cmath>

#include "common.hpp"

void draw_circle(std::vector<unsigned char> &image, const int width,
                 const int height, int radius) {
  const int center_x = width / 2;
  const int center_y = height / 2;
  for (int i = 0; i < width * height; ++i) {
    int py = i / width;
    int px = i % width;

    double distance = std::hypot(px - center_x, py - center_y);
    if (distance <= radius) {
      image[i] = 255;
    }
  }
}