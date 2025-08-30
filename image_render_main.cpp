#include <iostream>

#include "common.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

template <typename T, glm::precision P, glm::length_t C, glm::length_t R>
std::ostream &operator<<(std::ostream &os, const glm::mat<C, R, T, P> &matrix) {
  for (glm::length_t row = 0; row < R; ++row) {
    os << "[ ";
    for (glm::length_t col = 0; col < C; ++col) {
      os << matrix[col][row] << " ";  // GLM is column-major
    }
    os << "]\n";
  }
  return os;
}

bool IntersectRayCone(const glm::vec3 rayOrigin, glm::vec3 rayDirection,
                      const glm::vec3 sphereCenter, const float sphereRadius,
                      float &t) {
  const glm::vec3 L = rayOrigin - sphereCenter;

  rayDirection = glm::normalize(rayDirection);

  const float a = glm::dot(rayDirection, rayDirection);
  const float b = 2.0f * glm::dot(rayDirection, L);
  const float c = glm::dot(L, L) - (sphereRadius * sphereRadius);

  // Calculate Determinant
  const float delta = (b * b) - 4 * a * c;

  if (delta < 0.f) return false;

  const float t0 = (-b + std::sqrt(delta)) / (2 * a);
  const float t1 = (-b - std::sqrt(delta)) / (2 * a);

  if (t0 < 0.f && t1 < 0.f) return false;
  if (t0 < 0.f && t1 > 0.f) {
    t = t1;
    return true;
  }
  if (t0 > 0.f && t1 < 0.f) {
    t = t0;
    return true;
  }
  if (t0 > 0.f && t1 > 0.f) {
    t = std::min(t0, t1);
    return true;
  }
  return false;
}
int main() {
  // Create Image
  constexpr int WIDTH = 1280;
  constexpr int HEIGHT = 720;
  constexpr float radius = 4.0;
  constexpr int comp = 1;

  glm::vec3 ray_origin(0, 0, 0);
  glm::vec3 obj_origin(0, 0, -10);
  glm::mat3 KK = ComputeCameraMatrix(60, WIDTH, HEIGHT);
  std::vector<unsigned char> image(WIDTH * HEIGHT, 0x00);

  for (int i = 0; i < WIDTH * HEIGHT; ++i) {
    int py = i / WIDTH;
    int px = i % WIDTH;
    glm::vec3 pixel_h(px, py, 1.0);
    glm::vec3 ray_direction = -glm::normalize(glm::inverse(KK) * pixel_h);
    float t;
    bool is_intersecting =
        IntersectRayCone(ray_origin, ray_direction, obj_origin, radius, t);

    if (is_intersecting) {
      glm::vec3 intersection_point = ray_origin + ray_direction * t;
      glm::vec3 normal = glm::normalize(intersection_point - obj_origin);
      float color_vector = glm::dot(-ray_direction, normal);
      image[i] = 255 * color_vector;
    }
    // else{
    // 	std::cout << "No intersection" << std::endl;
    // }
    // std::cout << glm::to_string(ray_direction) << std::endl;
  }
  stbi_write_png("output_test.png", WIDTH, HEIGHT, comp, image.data(),
                 WIDTH * 1);
  return 0;
}