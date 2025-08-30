#include <glm/gtc/matrix_transform.hpp>

#include "common.hpp"

glm::mat3 ComputeCameraMatrix(const float verticalFOVDegrees,
                              const float imageWidth, const float imageHeight) {
  // Convert vertical FOV from degrees to radians
  const float verticalFOVRadians = glm::radians(verticalFOVDegrees);

  // Compute image plane distance and horizontal FOV
  const float baseDistance =
      (imageHeight / 2.0) /
      std::tan((verticalFOVRadians /
                2.0));  // distance of image plane from camera origin
  const float horizontalFOVRadians =
      2.0 * std::atan(((imageWidth / 2.0) / baseDistance));

  // Compute camera matrix parameters
  const float fy =
      (imageHeight - 1.0) / (2.0 * std::tan((verticalFOVRadians / 2.0)));
  const float fx =
      (imageWidth - 1.0) / (2.0 * std::tan(horizontalFOVRadians / 2.0));

  // Compute the image center
  const float cx = (imageWidth - 1.0) / 2.0;
  const float cy = (imageHeight - 1.0) / 2.0;

  // Intrinsic camera matrix
  glm::mat3 cameraMatrix =
      glm::transpose(glm::mat3(fx, 0.0f, cx, 0.0f, fy, cy, 0.0f, 0.0f, 1.0f));

  return cameraMatrix;
}