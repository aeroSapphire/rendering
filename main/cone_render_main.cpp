#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

glm::mat3 ComputeCameraMatrix(const float verticalFOVDegrees,
                              const float imageWidth, const float imageHeight);

bool intersectRayCone(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 coneVertex, glm::vec3 coneAxis, float coneAngle, float &t){
	glm::vec3 L = rayOrigin - coneVertex;
	rayDirection = glm::normalize(rayDirection);

	float theta = glm::radians(coneAngle);
	float DV = glm::dot(rayDirection, coneAxis);
	float LV = glm::dot(L, coneAxis);
	float DL = glm::dot(rayDirection, L);
	float LL = glm::dot(L, L);
	float cos2 = (glm::cos(theta)*glm::cos(theta));
	
	float a = DV * DV - cos2;
	float b = 2 * ((DV * LV) - DL * cos2);
	float c = (LV * LV) - (LL * cos2);

	// Calculate Determinant
	float delta = (b*b) - 4*a*c;

	if (delta < 0.f) return false;

	float t0 = (-b + std::sqrt(delta))/(2*a);
	float t1 = (-b - std::sqrt(delta))/(2*a);

	if (t0 < 0.f && t1 < 0.f) return false;
	else if (t0 < 0.f && t1 > 0.f){
		t = t1;
		return true;
	}
	else if (t0 > 0.f && t1 < 0.f){
		t = t0;
		return true;
	}
	else if (t0 > 0.f && t1 > 0.f){
		t = std::min(t0,t1);
		return true;
	}

}

int main(){

	constexpr int comp =1;
	constexpr int WIDTH = 1280;
	constexpr int HEIGHT = 720;

	glm::vec3 rayOrigin(0,0,0);
	glm::vec3 coneOrigin(0,0,-10);
	glm::vec3 coneAxis(0,-1,0);
	float coneAngle = 20.0f;

	std::vector<unsigned char> image(WIDTH*HEIGHT, 0x00);
	glm::mat3 KK = ComputeCameraMatrix(60, WIDTH, HEIGHT);

	for (int i = 0; i < WIDTH * HEIGHT; ++i) {
	int py = i / WIDTH;
	int px = i % WIDTH;
	glm::vec3 pixel_h(px, py, 1.0);
	glm::vec3 rayDirection = -glm::normalize(glm::inverse(KK) * pixel_h);
	float t;
	bool is_intersecting =
		intersectRayCone(rayOrigin, rayDirection, coneOrigin, glm::normalize(coneAxis), coneAngle, t);

	if (is_intersecting) {

	glm::vec3 intersection_point = rayOrigin + rayDirection * t;

		// if (glm::dot(intersection_point-coneOrigin,coneAxis) > 0){
	glm::vec3 normal = glm::normalize(intersection_point - coneOrigin);
	float color_vector = glm::dot(-rayDirection, normal);
	image[i] = 255 * color_vector;
			// }	
		}
	// else{
	// 	std::cout << "No intersection" << std::endl;
	// }
	// std::cout << glm::to_string(rayDirection) << std::endl;
  

	}
	stbi_write_png("output_test.png", WIDTH, HEIGHT, comp, image.data(), WIDTH * 1);
	return 0;

	return 0;

}