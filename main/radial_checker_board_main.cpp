#include <iostream>
#include <vector>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

void draw_radial_checker_board(std::vector <unsigned char> &image, const int width, const int height);

int main(){
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 800;
    constexpr int comp = 1; 

    std::vector <unsigned char> image(WIDTH * HEIGHT, 0x00);
    draw_radial_checker_board(image, WIDTH, HEIGHT);
    stbi_write_png("output_radial_checker_board.png", WIDTH, HEIGHT, comp, image.data(), WIDTH * 1);
    return 0;
}