#pragma once

#include <glm/glm.hpp>
#include <vector>

// Camera matrix computation function
glm::mat3 ComputeCameraMatrix(const float verticalFOVDegrees,
                              const float imageWidth, const float imageHeight);

// Drawing functions
void draw_checker_board(std::vector<unsigned char>& image, int width,
                        int height);

void draw_circle(std::vector<unsigned char>& image, const int width,
                 const int height, int radius);

void draw_radial_checker_board(std::vector<unsigned char>& image,
                               const int width, const int height);