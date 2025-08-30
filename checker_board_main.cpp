#include "common.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

int main() {
  constexpr int comp = 1;
  constexpr int WIDTH = 800;
  constexpr int HEIGHT = 800;
  std::vector<unsigned char> image(WIDTH * HEIGHT, 0x00);
  draw_checker_board(image, WIDTH, HEIGHT);
  stbi_write_png("output_checker.png", WIDTH, HEIGHT, comp, image.data(),
                 WIDTH * 1);

  return 0;
}