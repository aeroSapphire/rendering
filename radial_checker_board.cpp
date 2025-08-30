#include <cmath>
#include <iostream>
#include <numbers>

#include "common.hpp"

void draw_radial_checker_board(std::vector<unsigned char> &image,
                               const int width, const int height) {
  double pi = std::numbers::pi;
  int center_x = width / 2;
  int center_y = height / 2;
  constexpr int S = 10;

  for (int i = 0; i <= width * height; i++) {
    int px = i % width;
    int py = i / width;

    int r = std::hypot(px - center_x, py - center_y);
    double theta = std::atan2(static_cast<double>(py - center_y),
                              static_cast<double>(px - center_x));
    int tile = theta / 10;
    if (r <= 50 && theta <= pi / 2) {
      image[i] = 255;
    }
  }
}