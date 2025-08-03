#include <iostream>
#include <vector>
#include <cmath>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

void draw_circle(std::vector<unsigned char> &image, const int width, const int height, int radius);

int main()
{
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 600;
    constexpr int comp = 1;

    std::vector<unsigned char> image(WIDTH * HEIGHT, 0x00); // image
    draw_circle(image, WIDTH, HEIGHT, 50);
    stbi_write_png("output.png", WIDTH, HEIGHT, comp, image.data(), WIDTH * 1);
    return 0;
}
