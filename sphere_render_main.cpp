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

bool IntersectRaySphere(const glm::vec3 &rayOrigin, const glm::vec3 &rayDir,
                        const glm::vec3 &sphereCenter, float sphereRadius,
                        float &t) {
  glm::vec3 L = rayOrigin - sphereCenter;

  float a = glm::dot(rayDir, rayDir);  // should be 1 if rayDir normalized
  float b = 2.0f * glm::dot(rayDir, L);
  float c = glm::dot(L, L) - sphereRadius * sphereRadius;

  float discriminant = b * b - 4.0f * a * c;

  if (discriminant < 0.0f) return false;  // no intersection

  float sqrtDiscriminant = glm::sqrt(discriminant);
  float t1 = (-b - sqrtDiscriminant) / (2.0f * a);
  float t2 = (-b + sqrtDiscriminant) / (2.0f * a);

  t = std::min(t1, t2);
  if (t < 0.0f) t = std::max(t1, t2);  // try the other one if first is behind
  if (t < 0.0f) return false;          // both behind the ray

  return true;
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
        IntersectRaySphere(ray_origin, ray_direction, obj_origin, radius, t);

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

  stbi_write_png("output.png", WIDTH, HEIGHT, comp, image.data(), WIDTH * 1);
  std::cout << KK;
  return 0;
}