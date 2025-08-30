#include <cmath>

#include "common.hpp"

void draw_checker_board(std::vector<unsigned char> &image, int width,
                        int height) {
  int tile_size = width / 100;

  for (int i = 0; i < (width) * (height); ++i) {
    int py = i / width;
    int px = i % width;
    int tx = px / 100;
    int ty = py / 100;
    if ((tx + ty) % 2 == 0) {
      image[i] = 255;
    }
  }
}